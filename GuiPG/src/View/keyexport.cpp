#include "keyexport.h"
#include "ui_keyexport.h"

KeyExport::KeyExport(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeyExport)
{
    ui->setupUi(this);
}

KeyExport::~KeyExport()
{
    delete ui;
}
