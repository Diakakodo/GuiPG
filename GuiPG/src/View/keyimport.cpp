#include "keyimport.h"
#include "ui_keyimport.h"

KeyImport::KeyImport(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeyImport)
{
    ui->setupUi(this);
}

KeyImport::~KeyImport()
{
    delete ui;
}

void KeyImport::on_cancelButton_clicked()
{
    close();
}
