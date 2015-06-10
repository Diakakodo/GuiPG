#include "filesign.h"
#include "ui_filesign.h"
#include "mainwindow.h"
#include <QFileDialog>
#include "../Keys/uid.h"
#include "../Keys/primapubkey.h"
#include <fstream>
#include "sys/types.h"
#include "sys/stat.h"

FileSign::FileSign(MainWindow *parent, KeyManager* keyManager) :
    QDialog(parent),
    ui(new Ui::FileSign)
{
    ui->setupUi(this);
    m_profile = parent->getProfil();
    m_manager = new GPGManager(m_profile);
    m_parent = parent;
    m_keyManager = keyManager;

    ui->tableWidgetRecipient->setColumnCount(7);
    ui->tableWidgetRecipient->verticalHeader()->setVisible(false);
    ui->tableWidgetRecipient->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QStringList m_TableHeader;
    m_TableHeader   <<"Nom"
                    <<"Email"
                    <<"Empreinte utilisateur"
                    <<"Validité utilisateur"
                    <<"Identifiant clef"
                    <<"Validitié clef"
                    <<"Confiance";
    ui->tableWidgetRecipient->setHorizontalHeaderLabels(m_TableHeader);
    ui->tableWidgetRecipient->setColumnWidth(0,150);
    ui->tableWidgetRecipient->setColumnWidth(1,150);
    ui->tableWidgetRecipient->setColumnWidth(2,150);
    ui->tableWidgetRecipient->setColumnWidth(3,130);
    ui->tableWidgetRecipient->setColumnWidth(4,150);
    ui->tableWidgetRecipient->setColumnWidth(5,100);
    ui->tableWidgetRecipient->setColumnWidth(6,90);

    int i = 0;

    for (PrimaPubKey* key : keyManager->getPubKeys()) {

        if ((key->getValidity() == VALIDITY_NO_VALUE ||
                    key->getValidity() == VALIDITY_UNKNOWN ||
                    key->getValidity() == VALIDITY_UNDEFINED ||
                    key->getValidity() == VALIDITY_MARGINAL ||
                    key->getValidity() == VALIDITY_FULLY ||
                    key->getValidity() == VALIDITY_ULTIMATELY) &&
                    (key->getCapabilities().contains("e") ||
                     key->getCapabilities().contains("E"))) {

            for (Uid* uid : key->getUidList()) {

                if (key->hasPrimaSecKey()) {

                    if (uid->getValidity() == VALIDITY_NO_VALUE ||
                            key->getValidity() == VALIDITY_UNKNOWN ||
                            key->getValidity() == VALIDITY_UNDEFINED ||
                            key->getValidity() == VALIDITY_MARGINAL ||
                            key->getValidity() == VALIDITY_FULLY ||
                            key->getValidity() == VALIDITY_ULTIMATELY) {

                        ui->tableWidgetRecipient->setRowCount(i+1);
                        ui->tableWidgetRecipient->setRowHeight(i, 20);
                        ui->tableWidgetRecipient->setItem(i, 0, new QTableWidgetItem(uid->getName()));
                        ui->tableWidgetRecipient->setItem(i, 1, new QTableWidgetItem(uid->getMail()));
                        ui->tableWidgetRecipient->setItem(i, 2, new QTableWidgetItem(uid->getFpr().right(16)));
                        ui->tableWidgetRecipient->setItem(i, 3, new QTableWidgetItem(GpgObject::validityToStr(uid->getValidity())));
                        ui->tableWidgetRecipient->setItem(i, 4, new QTableWidgetItem(key->getKeyId()));
                        ui->tableWidgetRecipient->setItem(i, 5, new QTableWidgetItem(GpgObject::validityToStr(key->getValidity())));
                        ui->tableWidgetRecipient->setItem(i, 6, new QTableWidgetItem(PrimaPubKey::trustToStr(key->getTrust())));
                        ui->tableWidgetRecipient->item(i, 6)->setBackgroundColor(Configuration::getDefaultValidityColor(key->getTrust()));

                        ui->tableWidgetRecipient->item(i, 3)->setBackgroundColor(Configuration::getDefaultValidityColor(uid->getValidity()));
                        ui->tableWidgetRecipient->item(i, 5)->setBackgroundColor(Configuration::getDefaultValidityColor(key->getValidity()));
                        i++;
                    }
                 }
            }
        }
    }
}

FileSign::~FileSign()
{
    delete ui;
}

void FileSign::on_browseButton_clicked()
{
    QString pathName = QFileDialog::getOpenFileName(this, "Selection du fichier à signer");
    ui->sourceFileEdit->setText(pathName);
}

void FileSign::on_exitButton_clicked()
{
    m_manager->cancelProcess();
    close();
}

void FileSign::onSignatureCompleted()
{
    ui->warningLabel->setText("Signature terminé !");
    ui->exitButton->setText("Fermer");
}
#include <QDebug>
void FileSign::on_okButton_clicked()
{
    ui->warningLabel->setText("");
    if (ui->sourceFileEdit->text().startsWith("~/")) {
        ui->warningLabel->setText("Seul les chemins absolus sont autorisés.");
        return;
    }


    QFile sourcefile(ui->sourceFileEdit->text());
    if (!sourcefile.exists()) {
        ui->warningLabel->setText("Le fichier source n'existe pas.");
        return;
    }

    QFileInfo sourceFileInfo(sourcefile);
    if (!sourceFileInfo.isReadable()) {
        ui->warningLabel->setText("Vous n'avez pas les droits de lecture sur le fichier source.");
        return;
    }

    QFile signaturefile(ui->sourceFileEdit->text()+".sig");
    if (signaturefile.exists()) {
        ui->warningLabel->setText("La signature de ce fichier existe déjà.");
        return;

    }



    // On récupère l'indice des lignes selectionnées
    QModelIndexList selectedIndex = ui->tableWidgetRecipient->selectionModel()->selectedIndexes();
    QList<int> rowIndexes;
    for (QModelIndex index : selectedIndex) {
        if (!rowIndexes.contains(index.row())) {
            rowIndexes.append(index.row());
        }
    }

    if (rowIndexes.count() == 0) {
        ui->warningLabel->setText("Vous devez sélectionnez au moins un destinaire.");
        return;
    }

    /* Utilisé pour paramétré les intéractions car gpg est tellement
     * intelligent qu'il les demandes dans l'ordre inverse pour le cas anonyme
     */
    QList<int> reverseRowIndexes;
    reverseRowIndexes.reserve(rowIndexes.size());
    std::reverse_copy(rowIndexes.begin(), rowIndexes.end(), std::back_inserter(reverseRowIndexes));

    QStringList opt;
    opt << "--command-fd=0"
        << "--status-fd=1"
        << "--default-key " + ui->tableWidgetRecipient->item(rowIndexes[0], 0)->text();
    QString cmd = "--detach-sign";
    QStringList arg;
    arg << ui->sourceFileEdit->text();
    QStringList interactions;

    Action action(cmd, arg, opt, interactions);
    m_manager->setAction(action);
    connect(m_manager, &GPGManager::finished, this, &FileSign::onSignatureCompleted);
    m_manager->execute();
}
