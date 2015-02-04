#include "keycreation.h"
#include "ui_keycreation.h"

KeyCreation::KeyCreation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeyCreation)
{
    ui->setupUi(this);
}

KeyCreation::~KeyCreation()
{
    delete ui;
}
