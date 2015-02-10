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
};
