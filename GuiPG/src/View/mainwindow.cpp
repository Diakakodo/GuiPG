#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"
#include <QApplication>
#include "Profil/dialogprofil.h"
#include "../GPG/gpgmanager.h"

MainWindow::MainWindow(Profile* p, Configuration* config)
    : ui(new Ui::MainWindow), m_profil(p), m_config(config) {

    ui->setupUi(this);
    ui->textBrowser->setVisible(false);

    if (p == nullptr) {
        showDialogSelectProfil();
    }

    connect(ui->toolButton, SIGNAL(toggled(bool)), this, SLOT(setGpgCommandsVisible(bool)));
    connect(ui->actionChanger_de_profile, SIGNAL(triggered()), this, SLOT(showDialogSelectProfil()));
    connect(ui->actionSupprimer_un_profile, SIGNAL(triggered()), this, SLOT(showDialogDeleteProfil()));
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
    DialogProfil d(DialogProfil::DIALOG_TYPE::SELECT, this);
    d.exec();
}

void MainWindow::showDialogDeleteProfil() {
    DialogProfil d(DialogProfil::DIALOG_TYPE::DELETE, this);
    d.exec();
}
