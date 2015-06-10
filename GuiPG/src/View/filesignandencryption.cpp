#include "filesignandencryption.h"
#include "ui_filesignandencryption.h"

FileSignAndEncryption::FileSignAndEncryption(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileSignAndEncryption)
{
    ui->setupUi(this);
}

FileSignAndEncryption::~FileSignAndEncryption()
{
    delete ui;
}
