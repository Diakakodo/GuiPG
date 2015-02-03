#include "key_creation.h"
#include "ui_key_creation.h"

Key_creation::Key_creation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Key_creation)
{
    ui->setupUi(this);
}

Key_creation::~Key_creation()
{
    delete ui;
}
