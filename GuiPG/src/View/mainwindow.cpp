#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(const Profile* p) : ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}
