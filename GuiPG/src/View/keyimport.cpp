#include "keyimport.h"
#include "ui_keyimport.h"
#include "QFileDialog"

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

void KeyImport::on_browseButton_clicked()
{
    QString filename=QFileDialog::getOpenFileName(this,tr("Open File"),
        "~","All files (*)" );
    ui->pathEdit->setText(filename);
    ui->fileRadioButton->click();
}

void KeyImport::on_pathEdit_textChanged(const QString &arg1)
{
    ui->fileRadioButton->click();
}

void KeyImport::on_keyIdEdit_textChanged(const QString &arg1)
{
    ui->keyServerButton->click();
}
