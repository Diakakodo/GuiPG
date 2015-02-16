#include "profilecreation.h"
#include "ui_profilecreation.h"
#include <QFileDialog>

ProfileCreation::ProfileCreation(MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::ProfileCreation)
{
    ui->setupUi(this);
}

ProfileCreation::~ProfileCreation()
{
    delete ui;
}

void ProfileCreation::on_cancelButton_clicked()
{
    close();
}

void ProfileCreation::on_gpgPathButton_clicked()
{
    QString filename=QFileDialog::getOpenFileName(this,tr("Open File"),"","All files (*.*)" );
    ui->gpgPathEdit->setText(filename);
}

void ProfileCreation::on_storagePathButton_clicked()
{
    QString filename=QFileDialog::getOpenFileName(this,tr("Open File"),"","All files (*.*)" );
    ui->storagePathEdit->setText(filename);
}

void ProfileCreation::on_acceptButton_clicked()
{

    close();
}
