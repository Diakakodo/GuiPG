#include "deletesubkeydialog.h"
#include "ui_deletesubkeydialog.h"
#include <QMessageBox>

DeleteSubKeyDialog::DeleteSubKeyDialog(Profile* profile, PrimaPubKey* pub, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteSubKeyDialog)
{
    ui->setupUi(this);
    m_profile = profile;
    m_pub = pub;

    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QStringList m_TableHeader;
    m_TableHeader   << "Création"
                    << "Expiration"
                    << "Algo"
                    << "Fingerprint";
    ui->tableWidget->setHorizontalHeaderLabels(m_TableHeader);
    ui->tableWidget->setColumnWidth(0,100);
    ui->tableWidget->setColumnWidth(1,100);
    ui->tableWidget->setColumnWidth(2,50);
    ui->tableWidget->setColumnWidth(3,264);

    int i = 0;

    for (SubPubKey* spk : m_pub->getSubPubKeyList()) {
        ui->tableWidget->setRowCount(i+1);
        ui->tableWidget->setRowHeight(i, 20);
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(spk->getCreationDate().toString("dd.MM.yyyy")));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(spk->getExpirationDate().toString("dd.MM.yyyy")));

        if(spk->getAlgo() == "17") {
            ui->tableWidget->setItem(i, 2, new QTableWidgetItem("DSA"));
        } else if (spk->getAlgo() == "1") {
            ui->tableWidget->setItem(i, 2, new QTableWidgetItem("RSA"));
        } else if (spk->getAlgo() == "16") {
            ui->tableWidget->setItem(i, 2, new QTableWidgetItem("Elgamal"));
        }
        else {
            ui->tableWidget->setItem(i, 2, new QTableWidgetItem(spk->getAlgo()));
        }

        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(spk->getFpr()));
        i++;
    }

}

DeleteSubKeyDialog::~DeleteSubKeyDialog()
{
    delete ui;
}

void DeleteSubKeyDialog::on_exitButton_clicked()
{
    close();
}


void DeleteSubKeyDialog::onDeleteCompleted()
{
    close();
}

void DeleteSubKeyDialog::on_deleteButton_clicked()
{
    QString infos = "Voulez vous vraiment supprimer cette sous-clef ?\n\n";
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(0, "Confirmation de suppression", infos, QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        int number = ui->tableWidget->currentIndex().row() + 1;
        QString keyNumber = QString::number(number);

        m_gpg = new GPGManager(m_profile);

        QStringList opt;
        opt << "--status-fd=1"
            << "--command-fd=0"
            << "--with-colons"
            << "--fixed-list-mode";
        QStringList args;
        args << m_pub->getKeyId();
        QStringList interactions;

        QString keySelection = "key " + keyNumber;

        interactions << keySelection
                     << "delkey"
                     << "y"
                     << "save";

        Action delSubKeydAction(QString("--edit-key"), args, opt, interactions);

        m_gpg->setAction(delSubKeydAction);
        connect(m_gpg, &GPGManager::finished, this, &DeleteSubKeyDialog::finished);
        m_gpg->execute();
    }
}

void DeleteSubKeyDialog::on_revokeButton_clicked()
{
    QString infos = "Voulez vous vraiment révoquer cette sous-clef ?\n\n";
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(0, "Confirmation de révocation", infos, QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        int number = ui->tableWidget->currentIndex().row() + 1;
        QString keyNumber = QString::number(number);

        m_gpg = new GPGManager(m_profile);

        QStringList opt;
        opt << "--status-fd=1"
            << "--command-fd=0"
            << "--with-colons"
            << "--fixed-list-mode";
        QStringList args;
        args << m_pub->getKeyId();
        QStringList interactions;

        QString keySelection = "key " + keyNumber;

        interactions << keySelection
                     << "revkey"
                     << "y"
                     << "0"
                     << "Identité plus valide"
                     << ""
                     << "y"
                     << "save";

        Action RevokeSubKeyAction(QString("--edit-key"), args, opt, interactions);

        m_gpg->setAction(RevokeSubKeyAction);
        connect(m_gpg, &GPGManager::finished, this, &DeleteSubKeyDialog::finished);
        m_gpg->execute();
    }
}
