#include "keysuppression.h"
#include "ui_keysuppression.h"

KeySuppression::KeySuppression(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeySuppression)
{
    ui->setupUi(this);
}

KeySuppression::~KeySuppression()
{
    delete ui;
}
