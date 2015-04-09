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
#include <QCloseEvent>

MainWindow::MainWindow(MainWindowModel* model)
    : ui(new Ui::MainWindow), m_model(model) {

    ui->setupUi(this);
    ui->textBrowser->setVisible(false);
    this->setWindowTitle("GuiPG - " + m_model->getProfile()->getName());

    connect(ui->toolButton, &QAbstractButton::toggled, this, &MainWindow::setGpgCommandsVisible);
    connect(ui->actionProfil, &QAction::triggered, this, &MainWindow::showDialogProfile);
    connect(ui->actionConfiguration, SIGNAL(triggered()), this, SLOT(showDialogConfiguration()));
    connect(ui->actionManuel_utilisateur_de_GuiPG, &QAction::triggered, this, &MainWindow::showManuel);

    QStringList m_TreeHeader;
    m_TreeHeader
            << "ID"
            << "Propriétaire"
            << "Taille"
            << "Création"
            << "Expiration"
            << "Validité"
            << "Confiance";
    ui->treeWidgetKey->setHeaderLabels(m_TreeHeader);
    connect(m_model, &MainWindowModel::keysChanged, this, &MainWindow::buildTree);
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
    ui->textBrowser->setVisible(b);
    if (b == true) {
        ui->toolButton->setArrowType(Qt::DownArrow);
    } else {
        ui->toolButton->setArrowType(Qt::UpArrow);
    }
}

void MainWindow::showDialogProfile() {
    DialogProfile d(m_model->getConf(), m_model->getLauncher());
    QObject::connect(&d, &DialogProfile::selectProfile, this, &MainWindow::changeProfil);
    d.exec();
}

void MainWindow::changeProfil(unsigned profileId) {
    m_model->loadProfile(profileId, this);
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
    //ui->treeWidgetKey->clear();
    //const QList<Key*>& keys = m_model->getKeyManager()->getKeys();
    //for (Key* k : keys) {
    //    QTreeWidgetItem* item = createKeyItem(k, ui->treeWidgetKey);
    //    for (Key* sk : k->getSubKeys()) {
    //        QTreeWidgetItem* sub = createKeyItem(sk);
    //        createSignatureItem(sk, sub);
    //        item->addChild(sub);
    //    }
    //    createSignatureItem(k, item);
    //}
}

QTreeWidgetItem* MainWindow::createKeyItem(Key *k, QTreeWidget* tree) {
    QStringList infos;
    //const QDate& e = k->getExpirationDate();
    //infos
    //        << k->getId()
    //        << k->getOwner()
    //        << QString::number(k->getLength())
    //        << k->getCreationDate().toString("dd/MM/yyyy")
    //        << (e.isNull() ? "Aucune" : k->getExpirationDate().toString("dd/MM/yyyy"))
    //        << Key::validityToStr(k->getValidity())
    //        << Key::validityToStr(k->getTrust())
    //;
    QTreeWidgetItem* item = tree == nullptr ? new QTreeWidgetItem(infos) : new QTreeWidgetItem(tree, infos);
    setItemColor(item, m_model->getProfile()->getValidityColor(k->getValidity()));
    return item;
}

void MainWindow::createSignatureItem(Key* k, QTreeWidgetItem* item) {
    //for (Signature* s : k->getSignatures()) {
    //    QStringList infos;
    //    infos
    //            << s->getId()
    //            << s->getOwner()
    //            << ""
    //            << s->getCreationDate().toString("dd/MM/yyyy")
    //            << ""
    //            << ""
    //            << ""
    //    ;
    //    QTreeWidgetItem* sig = new QTreeWidgetItem(infos);
    //    setItemColor(sig, m_model->getProfile()->getSignatureColor());
    //    item->addChild(sig);
    //}
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
