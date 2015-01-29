#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"
#include <QApplication>

MainWindow::MainWindow(const Profile* p) : ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->textBrowser->setVisible(false);
    connect(ui->toolButton,
                SIGNAL(toggled(bool)),
                this,
                SLOT(setGpgCommandsVisible(bool)));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setGpgCommandsVisible(bool b) {
    ui->textBrowser->setVisible(b);
    if (b == true) {
        ui->toolButton->setArrowType(Qt::UpArrow);
    } else {
        ui->toolButton->setArrowType(Qt::DownArrow);
    }
}
