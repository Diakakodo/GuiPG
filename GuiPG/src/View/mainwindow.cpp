#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QApplication>
#include "Profil/dialogprofile.h"
#include "keycreation.h"
#include "keyimport.h"
#include "keyexport.h"
#include "Profil/profilecreation.h"
#include "config.h"
#include "GpgItems/gpgitem.h"
#include "GpgItems/primapubkeyitem.h"
#include <QCloseEvent>
#include <QTextEdit>
#include <QLineEdit>
#include <QMovie>
#include <QDebug>
MainWindow::MainWindow(MainWindowModel* model)
    : ui(new Ui::MainWindow), m_model(model) {

    ui->setupUi(this);
    QList<int> splitterSize = ui->splitter->sizes();
    splitterSize[1]=0;
    ui->splitter->setSizes(splitterSize);

    ui->bigBrother->setVisible(false);
    this->setWindowTitle("GuiPG - " + m_model->getProfile()->getName());
    connect(ui->toolButton, &QAbstractButton::toggled, this, &MainWindow::setGpgCommandsVisible);
    connect(ui->actionProfil, &QAction::triggered, this, &MainWindow::showDialogProfile);
    connect(ui->actionConfiguration, SIGNAL(triggered()), this, SLOT(showDialogConfiguration()));
    connect(ui->actionManuel_utilisateur_de_GuiPG, &QAction::triggered, this, &MainWindow::showManuel);

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
    ui->splitter_2->widget(1)->setMaximumHeight(currentBigBrotherHeight);

    ui->bigBrother->setColumnWidth(0, ICON_BIG_BROTHER_SIZE.width() * 3);
    ui->bigBrother->setHeaderLabels(QStringList() << "" << "Commandes" << "Début" << "Fin");
    model->initKeyManager(this);
    ui->treeWidgetKey->setKeyManager(model->getKeyManager());
    qDebug() << m_model->getProfile()->getConfigurationPath();
    ui->treeWidgetKey->setProfile(m_model->getProfile());
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
}

void MainWindow::closeEvent(QCloseEvent *event) {
    m_model->getLauncher()->UnloadProfileWithWindow(m_model->getProfile());
    event->accept();
}

void MainWindow::setGpgCommandsVisible(bool b) {
    ui->bigBrother->setVisible(b);
    if (b == true) {
        ui->toolButton->setArrowType(Qt::DownArrow);
        ui->splitter_2->widget(1)->setMaximumHeight(this->height());
    } else {
        ui->toolButton->setArrowType(Qt::UpArrow);
        ui->splitter_2->widget(1)->setMaximumHeight(currentBigBrotherHeight);
    }
    QList<int> currentSizes = ui->splitter_2->sizes();
    currentSizes[0] += ui->bigBrother->height();
    currentSizes[1] -= ui->bigBrother->height();
    ui->splitter_2->setSizes(currentSizes);
}

void MainWindow::showDialogProfile() {
    DialogProfile d(m_model->getConf(), m_model->getLauncher());
    QObject::connect(&d, &DialogProfile::selectProfile, this, &MainWindow::changeProfil);
    d.exec();
}

void MainWindow::changeProfil(unsigned profileId) {
    m_model->loadProfile(profileId, this);
    ui->treeWidgetKey->setProfile(m_model->getProfile());
    buildTree();
}

void MainWindow::on_actionG_n_rer_une_paire_de_clefs_triggered()
{
    KeyCreation keyCreationGui(this);
    keyCreationGui.show();
    keyCreationGui.exec();
}

void MainWindow::showManuel()
{
    system("evince manuel.pdf&");
}

void MainWindow::showDialogConfiguration(){
    config c(this);
    c.exec();
}

void MainWindow::buildTree() {
    ui->treeWidgetKey->clear();
    const QList<PrimaPubKey*> pubKeys = m_model->getKeyManager()->getPubKeys();
    for (PrimaPubKey* pub : pubKeys) {
        ui->treeWidgetKey->addTopLevelItem(new PrimaPubKeyItem(pub));
    }
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
        QMovie* movie = new QMovie(":/icones/res/"ICON_BIG_BROTHER_LOAD_PATH);
        movie->setScaledSize(ICON_BIG_BROTHER_SIZE);
        label->setMovie(movie);
        ui->bigBrother->addTopLevelItem(cmdItem);
        ui->bigBrother->setItemWidget(cmdItem, 0, label);
        QLineEdit* textCmd = new QLineEdit();
        textCmd->setReadOnly(true);
        textCmd->setText(cmd);
        textCmd->setFixedWidth(textCmd->fontMetrics().boundingRect(cmd).width() + 20);
        ui->bigBrother->setItemWidget(cmdItem, 1, textCmd);
        movie->start();
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
        ui->bigBrother->setItemWidget(cmdItem, 0, NULL);
    }
    ui->bigBrother->resizeColumnToContents(1);
}
