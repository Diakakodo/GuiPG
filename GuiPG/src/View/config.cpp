#include "config.h"
#include "ui_config.h"
#include <QFileDialog>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

config::config(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::config)
{
    ui->setupUi(this);

    struct passwd *pw = getpwuid(getuid());
    QString homedir = pw->pw_dir;
    QString home = "home/";

    ui->lineEdit_2->setText((homedir).append(".gnugp"));

}
config::~config()

{
    delete ui;
}

void config::on_pushButton_clicked()
{
  struct passwd *pw = getpwuid(getuid());
  const char *homedir = pw->pw_dir;
  QString home = "home/";

  QString filename=QFileDialog::getOpenFileName(this,tr("Open File"),homedir,"All files (*.*)" );
  ui->lineEdit_2->setText(filename);

};

void config::on_lineEdit_cursorPositionChanged(int arg1, int arg2)
{
    ui->lineEdit->setText("gpg.config");
}
