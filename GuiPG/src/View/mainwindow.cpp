#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"
#include <QApplication>
#include "Profil/dialogprofil.h"

MainWindow::MainWindow(const Profile* p) : ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->textBrowser->setVisible(false);
    connect(ui->toolButton, SIGNAL(toggled(bool)), this, SLOT(setGpgCommandsVisible(bool)));
    connect(ui->actionChanger_de_profile, SIGNAL(triggered()), this, SLOT(showDialogSelectProfil()));
    connect(ui->actionSupprimer_un_profile, SIGNAL(triggered()), this, SLOT(showDialogDeleteProfil()));
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
