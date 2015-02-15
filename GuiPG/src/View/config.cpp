#include "config.h"
#include "ui_config.h"
#include <QFileDialog>

config::config(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::config)
{
    ui->setupUi(this);
}

config::~config()
{
    delete ui;
}

void config::on_pushButton_clicked()
{
  QString filename=QFileDialog::getOpenFileName(this,tr("Open File"),"home/ibrahima","All files (*.*)" );
  ui->lineEdit_2->setText(filename);

};

void config::on_lineEdit_cursorPositionChanged(int arg1, int arg2)
{
    ui->lineEdit->setText("gpg.config");
}
