#include "config.h"
#include "ui_config.h"
#include <QFileDialog>
#include <unistd.h>
#include <sys/types.h>
#include "mainwindow.h"
#include "../Profile/profile.h"

config::config(MainWindow *parent) : //QWidget
    QDialog(parent),
    ui(new Ui::config)
{
    ui->setupUi(this);


    m_profil = parent->getProfil();
    if(m_profil->getConfigurationPath() != ""){
        ui->lineEdit_2->setText(m_profil->getConfigurationPath());
    }else{
        /*
        struct passwd *pw = getpwuid(getuid());
        QString homedir = pw->pw_dir;
        QString home = "home/";
        ui->lineEdit_2->setText((homedir).append(".gnugp/"));
        */
    }
}

config::~config()

{
    delete ui;
}

void config::on_pushButton_clicked()
{
    /*
  struct passwd *pw = getpwuid(getuid());
  const char *homedir = pw->pw_dir;
  QString home = "home/";

  location=QFileDialog::getOpenFileName(this,tr("Open File"),homedir,"All files (*.*)" );
  ui->lineEdit_2->setText(location);
  */
}

void config::on_pushButton_4_clicked()
{
    close();
}

void config::on_pushButton_5_clicked()
{
    m_profil->setConfigurationPath(location);
    close();
}


