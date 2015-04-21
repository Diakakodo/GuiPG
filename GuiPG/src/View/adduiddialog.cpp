#include "adduiddialog.h"
#include "ui_adduiddialog.h"

AddUidDialog::AddUidDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUidDialog)
{
    ui->setupUi(this);
}

AddUidDialog::~AddUidDialog()
{
    delete ui;
}
