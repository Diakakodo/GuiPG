#include "filesign.h"
#include "ui_filesign.h"

Filesign::Filesign(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Filesign)
{
    ui->setupUi(this);
}

Filesign::~Filesign()
{
    delete ui;
}
