#include "profilecreation.h"
#include "ui_profilecreation.h"

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
