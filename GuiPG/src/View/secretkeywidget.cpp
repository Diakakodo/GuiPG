#include "secretkeywidget.h"
#include "ui_secretkeywidget.h"
#include "../Keys/primaseckey.h"
#include "../Keys/primapubkey.h"
#include "../Keys/uid.h"
#include "../Configuration/configuration.h"

SecretKeyWidget::SecretKeyWidget(QList<PrimaSecKey*> keys, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SecretKeyWidget)
{
    setAttribute( Qt::WA_DeleteOnClose );
    ui->setupUi(this);
    ui->tableWidget->verticalHeader()->setVisible(false);
    QStringList tableHeader;
    tableHeader   <<"Nom"
                    <<"Email"
                    <<"Empreinte utilisateur"
                    <<"Validité utilisateur"
                    <<"Identifiant clef"
                    <<"Validitié clef"
                    <<"Confiance";
    ui->tableWidget->setColumnCount(tableHeader.count());
    ui->tableWidget->setHorizontalHeaderLabels(tableHeader);
    for (int i = 0; i < tableHeader.count(); ++i) {
        ui->tableWidget->setColumnWidth(i,150);
    }

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
        ui->tableWidget->setItem(i, 5, new QTableWidgetItem(GpgObject::validityToStr(pub->getValidity())));
        ui->tableWidget->setItem(i, 6, new QTableWidgetItem(PrimaPubKey::trustToStr(pub->getTrust())));

        ui->tableWidget->item(i, 3)->setBackgroundColor(Configuration::getDefaultValidityColor(uid->getValidity()));
        ui->tableWidget->item(i, 5)->setBackgroundColor(Configuration::getDefaultValidityColor(pub->getValidity()));
        ui->tableWidget->item(i, 6)->setBackgroundColor(Configuration::getDefaultValidityColor(pub->getTrust()));
    }
    if (keys.count() > 0) ui->tableWidget->selectRow(0);
}
#include <QDebug>
SecretKeyWidget::~SecretKeyWidget()
{
    qDebug() << "close";
    delete ui;
}

void SecretKeyWidget::on_selectButton_clicked()
{
    this->setVisible(false);
    emit selectedSecretKey(ui->tableWidget->item(ui->tableWidget->selectedItems()[0]->row(), 4)->text());
}

void SecretKeyWidget::on_cancelButton_clicked()
{

}
