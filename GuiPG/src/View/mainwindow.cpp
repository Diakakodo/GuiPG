#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QApplication>
#include "Profil/dialogprofile.h"
#include "keycreation.h"
#include "keyimport.h"
#include "keyexport.h"
#include "Profil/profilecreation.h"
#include "fileencryption.h"
#include "filesignandencryption.h"
#include "filesign.h"
#include "../Keys/keydeletion.h"
#include "GpgItems/gpgitem.h"
#include "GpgItems/primapubkeyitem.h"
#include <QCloseEvent>
#include <QTextEdit>
#include <QLineEdit>
#include <QMovie>
#include "filedecryptionandverify.h"


MainWindow::MainWindow(MainWindowModel* model)
    : QMainWindow(), ui(new Ui::MainWindow), m_model(model) {
    setAttribute( Qt::WA_DeleteOnClose );
    ui->setupUi(this);
    QList<int> splitterSize = ui->splitter->sizes();
    splitterSize[1]=0;
    ui->splitter->setSizes(splitterSize);

    ui->bigBrother->setVisible(false);
    this->setWindowTitle("GuiPG - " + m_model->getProfile()->getName());
    connect(ui->toolButton, &QAbstractButton::toggled, this, &MainWindow::setGpgCommandsVisible);
    connect(ui->actionProfil, &QAction::triggered, this, &MainWindow::showDialogProfile);
    connect(ui->actionQuitter, SIGNAL(triggered()), this, SLOT(close()));

    QStringList m_TreeHeader;
    for (int i = 0; i < GpgItem::NB_COLUMNS; ++i) {
        m_TreeHeader << GpgItem::columns.value(i);
    }
    ui->treeWidgetKey->setHeaderLabels(m_TreeHeader);
    ui->treeWidgetKey->setColumnWidth(GpgItem::COL_NAME, 150);
    ui->treeWidgetKey->setColumnWidth(GpgItem::COL_MAIL, 150);
    ui->treeWidgetKey->setProfile(model->getProfile());
    ui->treeWidgetKey->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->treeWidgetKey, &QTreeWidget::customContextMenuRequested,
            this, &MainWindow::onCustomContextMenuRequested);

    ui->bigBrother->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);

    connect(m_model, &MainWindowModel::keysChanged, this, &MainWindow::buildTree);

    currentBigBrotherHeight = ui->splitter_2->widget(1)->height();
    ui->splitter_2->widget(1)->setMaximumHeight(ui->toolButton->height());

    ui->bigBrother->setColumnWidth(0, ICON_BIG_BROTHER_SIZE.width() * 3);
    ui->bigBrother->setHeaderLabels(QStringList() << "" << "Commandes" << "Début" << "Fin");
    model->initKeyManager(this);
    ui->treeWidgetKey->setKeyManager(model->getKeyManager());
    ui->treeWidgetKey->setProfile(m_model->getProfile());
    ui->treeWidgetKey->sortByColumn(GpgItem::COL_NAME, Qt::AscendingOrder);

}

void MainWindow::addTab(QString name, QString content) {

    QTextEdit* textEdit = new QTextEdit(this);
    textEdit->setText(content);
    ui->tabWidget->addTab(textEdit, name);
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
    QList<int> sizes = ui->splitter->sizes();
    if (sizes[1] == 0) {
        sizes[1] = (this->width() / 4);
        ui->splitter->setSizes(sizes);
    }
}

void MainWindow::onCustomContextMenuRequested(const QPoint& pos) {
    GpgItem* item = (GpgItem*) ui->treeWidgetKey->itemAt(pos);
    if (item) {
        item->showMenu(pos);
    }
}

Profile* MainWindow::getProfil() const {
    return m_model->getProfile();
}

Configuration* MainWindow::getConfiguration() const {
    return m_model->getConf();
}

MainWindowModel* MainWindow::getModel() const {
    return m_model;
}

MainWindow::~MainWindow() {
    delete ui;
    delete m_model;
}

void MainWindow::closeEvent(QCloseEvent *event) {
    m_model->getLauncher()->UnloadProfileWithWindow(m_model->getProfile());
    event->accept();
}

void MainWindow::setGpgCommandsVisible(bool b) {
    ui->bigBrother->setVisible(b);
    QList<int> currentSizes = ui->splitter_2->sizes();
    if (b == true) {
        ui->toolButton->setArrowType(Qt::DownArrow);
        ui->splitter_2->widget(1)->setMaximumHeight(this->height());
        currentSizes[1] = currentBigBrotherHeight;
    } else {
        currentBigBrotherHeight = ui->splitter_2->widget(1)->height();
        ui->toolButton->setArrowType(Qt::UpArrow);
        ui->splitter_2->widget(1)->setMaximumHeight(ui->toolButton->height());
        currentSizes[1] = ui->toolButton->height();
    }
    ui->splitter_2->setSizes(currentSizes);
}

void MainWindow::showDialogProfile() {
    DialogProfile d(m_model->getConf(), m_model->getLauncher());
    QObject::connect(&d, &DialogProfile::selectProfile, this, &MainWindow::changeProfil);
    d.exec();
}

void MainWindow::changeProfil(unsigned profileId) {
    m_model->loadProfile(profileId, this);
    m_model->getKeyManager()->setMainWindow(this);
    ui->treeWidgetKey->setProfile(m_model->getProfile());
}

void MainWindow::on_actionG_n_rer_une_paire_de_clefs_triggered()
{
    KeyCreation keyCreationGui(this);
    keyCreationGui.show();
    keyCreationGui.exec();
}

void MainWindow::on_action_GenKey_Toolbar_triggered() {
    KeyCreation keyCreationGui(this);
    keyCreationGui.show();
    keyCreationGui.exec();
}

void MainWindow::on_action_Refresh_Toolbar_triggered() {
    getModel()->getKeyManager()->load();
}

void MainWindow::on_action_Import_Toolbar_triggered() {
    KeyImport keyImportGui(this);
    keyImportGui.show();
    keyImportGui.exec();
}


void MainWindow::buildTree() {
    const QList<PrimaPubKey*> pubKeys = m_model->getKeyManager()->getPubKeys();
    QList<QString> hash;
    for (PrimaPubKey* pub : pubKeys) {
        hash.append(pub->getFpr());
    }
    QHash<QString, QTreeWidgetItem*> hashItem;
    QTreeWidget tmpTree;
    int count = ui->treeWidgetKey->topLevelItemCount();
    for (int i = 0; i < count; i++) {
        if (hash.contains(((PrimaPubKeyItem*) ui->treeWidgetKey->topLevelItem(0))->getFpr())) {
            QTreeWidgetItem* item = new QTreeWidgetItem(&tmpTree);
            for (int i = 0; i < ui->treeWidgetKey->topLevelItem(0)->childCount(); ++i) {
                QTreeWidgetItem* child = ui->treeWidgetKey->topLevelItem(0)->child(i)->clone();
                item->addChild(child);
                child->setExpanded(ui->treeWidgetKey->topLevelItem(0)->child(i)->isExpanded());
                child->setSelected(ui->treeWidgetKey->topLevelItem(0)->child(i)->isSelected());
                for (int j = 0; j < ui->treeWidgetKey->topLevelItem(0)->child(i)->childCount(); ++j) {
                    QTreeWidgetItem* subChild = ui->treeWidgetKey->topLevelItem(0)->child(i)->child(j)->clone();
                    child->addChild(subChild);
                    item->child(i)->child(j)->setSelected(ui->treeWidgetKey->topLevelItem(0)->child(i)->child(j)->isSelected());
                }
            }
            tmpTree.addTopLevelItem(item);
            if (ui->treeWidgetKey->topLevelItem(0)->isSelected() && tmpTree.selectedItems().count() < 1) {
                item->setSelected(true);
            }
            item->setExpanded(ui->treeWidgetKey->topLevelItem(0)->isExpanded());
            hashItem.insert(((PrimaPubKeyItem*) ui->treeWidgetKey->topLevelItem(0))->getFpr(), item);
        }
        delete ui->treeWidgetKey->topLevelItem(0);
    }
    for (PrimaPubKey* pub : pubKeys) {
        PrimaPubKeyItem* newItem = new PrimaPubKeyItem(pub);
        ui->treeWidgetKey->addTopLevelItem(newItem);
        if (hashItem.contains(pub->getFpr())) {
            QTreeWidgetItem* item = hashItem.value(pub->getFpr());
            newItem->setExpanded(item->isExpanded());
            newItem->setSelected(item->isSelected());
            for (int i = 0; i < item->childCount() && i < newItem->childCount(); ++i) {
                newItem->child(i)->setExpanded(item->child(i)->isExpanded());
                newItem->child(i)->setSelected(item->child(i)->isSelected());
                for (int j = 0; j < newItem->child(i)->childCount() && j < item->child(i)->childCount(); ++j) {
                    newItem->child(i)->child(j)->setSelected(item->child(i)->child(j)->isSelected());
                }
            }
        }
    }
    tmpTree.clear();
}

void MainWindow::on_actionImporter_triggered()
{
    KeyImport keyImportGui(this);
    keyImportGui.show();
    keyImportGui.exec();
}

void MainWindow::on_actionCl_s_publiques_triggered()
{
    KeyExport keyExportGui(this, KeyExport::PUBLIC_KEYS);
    keyExportGui.show();
    keyExportGui.exec();
}

void MainWindow::on_actionCl_s_priv_es_triggered()
{
    KeyExport keyExportGui(this, KeyExport::SECRET_KEYS);
    keyExportGui.show();
    keyExportGui.exec();
}

void MainWindow::refreshKeys() {
    m_model->initKeyManager();
}

void MainWindow::setItemColor(QTreeWidgetItem* item, const QColor& color) {
    for (int i = 0; i < ui->treeWidgetKey->columnCount(); ++i) {
        item->setTextColor(i, color);
    }
}

void MainWindow::updateBigBrother(GPGManager* gpg, bool fisrt, int id) {
    QString cmd = gpg->getCmd();
    QString output = gpg->getOutput();
    if (fisrt) {
        QTreeWidgetItem* cmdItem = new QTreeWidgetItem();
        cmdItem->setText(2, gpg->getStartTime().toString(DATE_BIG_BROTHER_FORMAT));
        QLabel* label = new QLabel();
        QMovie* movie = new QMovie(":/icones/res/" ICON_BIG_BROTHER_LOAD_PATH);
        movie->setScaledSize(ICON_BIG_BROTHER_SIZE);
        label->setMovie(movie);
        ui->bigBrother->addTopLevelItem(cmdItem);
        ui->bigBrother->setItemWidget(cmdItem, 0, label);
        QLineEdit* textCmd = new QLineEdit();
        textCmd->setReadOnly(true);
        textCmd->setText(cmd);
        int cmdWidth = textCmd->fontMetrics().boundingRect(cmd).width() + 20;
        if (cmdWidth > m_bigBrotherCmdMaxWidht) {
            m_bigBrotherCmdMaxWidht = cmdWidth;
        }
        textCmd->setMinimumWidth(cmdWidth);
        ui->bigBrother->setItemWidget(cmdItem, 1, textCmd);
        movie->start();
        if (ui->bigBrother->columnWidth(1) < m_bigBrotherCmdMaxWidht) {
            ui->bigBrother->resizeColumnToContents(1);
        }
    } else {
        QTreeWidgetItem* cmdItem;
        cmdItem = ui->bigBrother->topLevelItem(id);
        if (output != "") {
            QTextEdit* textOutput = new QTextEdit();
            textOutput->setReadOnly(true);
            textOutput->setAcceptRichText(true);
            textOutput->setText(output);
            QTreeWidgetItem* outputItem = new QTreeWidgetItem();
            cmdItem->insertChild(0, outputItem);
            ui->bigBrother->setItemWidget(outputItem, 1, textOutput);
        }
        cmdItem->setText(3, gpg->getEndTime().toString(DATE_BIG_BROTHER_FORMAT));
        QLabel* label = (QLabel*) ui->bigBrother->itemWidget(cmdItem, 0);
        QMovie* movie = label->movie();
        movie->stop();
        movie->deleteLater();
        label->deleteLater();
        ui->bigBrother->setItemWidget(cmdItem, 0, NULL);
    }
    ui->bigBrother->scrollToBottom();
}

int MainWindow::getNbCmd() {
    return NB_CMD;
}

void MainWindow::setNbCmd(int nb) {
    NB_CMD = nb;
}

void MainWindow::on_actionChiffrer_un_fichier_triggered() {
    FileEncryption encryption(this, m_model->getKeyManager());
    encryption.exec();
}

void MainWindow::on_actionDechiffrer_Verifier_un_fichier_triggered() {
    FileDecryptionAndVerify decryptAndVerify(m_model->getProfile(), this);
    decryptAndVerify.exec();
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    ui->tabWidget->widget(index)->deleteLater();
    ui->tabWidget->removeTab(index);
    if (ui->tabWidget->count() == 0) {
        QList<int> splitterSize = ui->splitter->sizes();
        splitterSize[1]=0;
        ui->splitter->setSizes(splitterSize);
    }
}

void MainWindow::on_actionVider_historique_des_commandes_triggered() {
    ui->bigBrother->clear();
    setNbCmd(0);
}

void MainWindow::on_actionSigner_un_fichier_triggered() {
    FileSign filesign(this, m_model->getKeyManager());
    filesign.exec();
}

void MainWindow::on_actionChiffrer_et_signer_un_fichier_triggered() {
    FileSignAndEncryption filesignandencryption(this, m_model->getKeyManager());
    filesignandencryption.exec();
}
