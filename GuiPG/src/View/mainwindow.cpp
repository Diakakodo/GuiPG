
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"
#include <QApplication>
#include "Profil/dialogprofil.h"
#include "../Keys/keymanager.h"

MainWindow::MainWindow(Profile* p, Configuration* config)
    : ui(new Ui::MainWindow), m_profil(p), m_config(config) {

    ui->setupUi(this);
    ui->textBrowser->setVisible(false);

    QStringList m_TreeHeader;
    m_TreeHeader<<"Nom"<<"Email"<<"Validité"<<"Confiance"<<"Expiration"<<"Taille"<<"Création"<<"Identifiant";
    ui->treeWidgetKey->setHeaderLabels(m_TreeHeader);

    connect(ui->toolButton, &QAbstractButton::toggled, this, &MainWindow::setGpgCommandsVisible);
    connect(ui->actionChanger_de_profile, &QAction::triggered, this, &MainWindow::showDialogSelectProfil);
    connect(ui->actionSupprimer_un_profile, &QAction::triggered, this, &MainWindow::showDialogDeleteProfil);

    if (p == nullptr) {
        showDialogSelectProfil();
    }

    KeyManager* m = new KeyManager(p);
    m->load();
}

Profile* MainWindow::getProfil() const {
    return m_profil;
}

Configuration* MainWindow::getConfiguration() const {
    return m_config;
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setGpgCommandsVisible(bool b) {
    ui->textBrowser->setVisible(b);
    if (b == true) {
        ui->toolButton->setArrowType(Qt::DownArrow);
    } else {
        ui->toolButton->setArrowType(Qt::UpArrow);
    }
}

void MainWindow::showDialogSelectProfil() {
    DialogProfil* d = new DialogProfil(DialogProfil::DIALOG_TYPE::SELECT, this);
    QObject::connect(d, SIGNAL(selectProfil(uint*)), this, SLOT(changeProfil(uint*)));
    d->exec();
}

void MainWindow::showDialogDeleteProfil() {
    DialogProfil d(DialogProfil::DIALOG_TYPE::DELETE, this);
    d.exec();
}

void MainWindow::changeProfil(uint* idProfil) {
    qDebug() << "un profil selectionné";
}

void MainWindow::on_actionG_n_rer_une_paire_de_clefs_triggered()
{
    KeyCreation keyCreationGui;
    keyCreationGui.show();
    keyCreationGui.exec();
}
