#include "secretkeywidget.h"
#include "ui_secretkeywidget.h"
#include "../Keys/primaseckey.h"
#include "../Keys/primapubkey.h"
#include "../Keys/uid.h"

SecretKeyWidget::SecretKeyWidget(QList<PrimaSecKey*> keys, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SecretKeyWidget)
{
    ui->setupUi(this);
    ui->tableWidget->setRowCount(keys.count());

    for (int i = 0; i < keys.count(); ++i) {
        PrimaSecKey* sec = keys.at(i);
        PrimaPubKey* pub = sec->getPrimaryPubKey();
        Uid* uid = pub->getPrimaryUid();
        ui->tableWidget->setRowHeight(i, 20);
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(uid->getName()));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(uid->getMail()));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(uid->getFpr()));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(GpgObject::validityToStr(uid->getValidity())));
        ui->tableWidget->setItem(i, 4, new QTableWidgetItem(pub->getKeyId()));
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem());
    }
    //PrimaPubKey* p = new PrimaPubKey();
}

SecretKeyWidget::~SecretKeyWidget()
{
    delete ui;
}

void SecretKeyWidget::on_selectButton_clicked()
{
    emit selectedSecretKey("plop");
}

void SecretKeyWidget::on_cancelButton_clicked()
{

}
