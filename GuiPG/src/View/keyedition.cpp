#include "keyedition.h"
#include "ui_keyedition.h"

KeyEdition::KeyEdition(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeyEdition)
{
    ui->setupUi(this);
}

KeyEdition::~KeyEdition()
{
    delete ui;
}
