#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QApplication>
#include "Profil/dialogprofile.h"
#include "../Keys/keymanager.h"
#include "keycreation.h"
#include "Profil/profilecreation.h"
#include "config.h"
#include <QDebug>

MainWindow::MainWindow(MainWindowModel* model)
    : ui(new Ui::MainWindow), m_model(model) {

    ui->setupUi(this);
    ui->textBrowser->setVisible(false);

    QStringList m_TreeHeader;
    m_TreeHeader<<"Nom"<<"Email"<<"Validité"<<"Confiance"<<"Expiration"<<"Taille"<<"Création"<<"Identifiant";
    ui->treeWidgetKey->setHeaderLabels(m_TreeHeader);

    connect(ui->toolButton, &QAbstractButton::toggled, this, &MainWindow::setGpgCommandsVisible);
    connect(ui->actionChanger_de_profile, &QAction::triggered, this, &MainWindow::showDialogSelectProfile);
    connect(ui->actionSupprimer_un_profile, &QAction::triggered, this, &MainWindow::showDialogDeleteProfil);

    connect(ui->actionConfiguration, SIGNAL(triggered()), this, SLOT(showDialogConfiguration()));
    while (m_model->getProfile() == nullptr) {
        showDialogSelectProfile();
    }

    KeyManager* m = new KeyManager(m_model->getProfile());
    m->load();
}

Profile* MainWindow::getProfil() const {
    return m_model->getProfile();
}

Configuration* MainWindow::getConfiguration() const {
    return m_model->getConf();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event) {
    m_model->getLauncher()->UnloadProfileWithWindow(m_model->getProfile());
}

void MainWindow::setGpgCommandsVisible(bool b) {
    ui->textBrowser->setVisible(b);
    if (b == true) {
        ui->toolButton->setArrowType(Qt::DownArrow);
    } else {
        ui->toolButton->setArrowType(Qt::UpArrow);
    }
}

void MainWindow::showDialogSelectProfile() {
    DialogProfile d(DialogProfile::DIALOG_TYPE::SELECT, this);
    QObject::connect(&d, &DialogProfile::selectProfile, this, &MainWindow::changeProfil);
    d.exec();
}

void MainWindow::showDialogDeleteProfil() {
    DialogProfile d(DialogProfile::DIALOG_TYPE::DELETE, this);
    d.exec();
}

void MainWindow::changeProfil(unsigned profileId) {
    m_model->loadProfile(profileId, this);
}

void MainWindow::on_actionG_n_rer_une_paire_de_clefs_triggered()
{
    KeyCreation keyCreationGui;
    keyCreationGui.show();
    keyCreationGui.exec();
}

void MainWindow::on_actionCreer_un_nouveau_profile_triggered()
{
    ProfileCreation profileCreationGui(this);
    profileCreationGui.show();
    profileCreationGui.exec();
}

void MainWindow::showDialogConfiguration(){
    config c(this);
    c.exec();
}
