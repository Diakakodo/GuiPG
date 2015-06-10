#include "filesignandencryption.h"
#include "ui_filesignandencryption.h"
#include "mainwindow.h"
#include <QFileDialog>
#include "../Keys/uid.h"
#include "../Keys/primapubkey.h"
#include <fstream>
#include "sys/types.h"
#include "sys/stat.h"

FileSignAndEncryption::FileSignAndEncryption(MainWindow *parent, KeyManager* keyManager) :
    QDialog(parent),
    ui(new Ui::FileSignAndEncryption)
{
    ui->setupUi(this);
    m_profile = parent->getProfil();
    m_manager = new GPGManager(m_profile);
    m_parent = parent;
    m_keyManager = keyManager;

    ui->tableWidgetRecipient2->setColumnCount(7);
    ui->tableWidgetRecipient2->verticalHeader()->setVisible(false);
    ui->tableWidgetRecipient2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QStringList m_TableHeader;
    m_TableHeader   <<"Nom"
                    <<"Email"
                    <<"Empreinte utilisateur"
                    <<"Validité utilisateur"
                    <<"Identifiant clef"
                    <<"Validitié clef"
                    <<"Confiance";
    ui->tableWidgetRecipient2->setHorizontalHeaderLabels(m_TableHeader);
    ui->tableWidgetRecipient2->setColumnWidth(0,150);
    ui->tableWidgetRecipient2->setColumnWidth(1,150);
    ui->tableWidgetRecipient2->setColumnWidth(2,150);
    ui->tableWidgetRecipient2->setColumnWidth(3,130);
    ui->tableWidgetRecipient2->setColumnWidth(4,150);
    ui->tableWidgetRecipient2->setColumnWidth(5,100);
    ui->tableWidgetRecipient2->setColumnWidth(6,90);

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

                if (uid->getValidity() == VALIDITY_NO_VALUE ||
                        key->getValidity() == VALIDITY_UNKNOWN ||
                        key->getValidity() == VALIDITY_UNDEFINED ||
                        key->getValidity() == VALIDITY_MARGINAL ||
                        key->getValidity() == VALIDITY_FULLY ||
                        key->getValidity() == VALIDITY_ULTIMATELY) {

                    ui->tableWidgetRecipient2->setRowCount(i+1);
                    ui->tableWidgetRecipient2->setRowHeight(i, 20);
                    ui->tableWidgetRecipient2->setItem(i, 0, new QTableWidgetItem(uid->getName()));
                    ui->tableWidgetRecipient2->setItem(i, 1, new QTableWidgetItem(uid->getMail()));
                    ui->tableWidgetRecipient2->setItem(i, 2, new QTableWidgetItem(uid->getFpr().right(16)));
                    ui->tableWidgetRecipient2->setItem(i, 3, new QTableWidgetItem(GpgObject::validityToStr(uid->getValidity())));
                    ui->tableWidgetRecipient2->setItem(i, 4, new QTableWidgetItem(key->getKeyId()));
                    ui->tableWidgetRecipient2->setItem(i, 5, new QTableWidgetItem(GpgObject::validityToStr(key->getValidity())));
                    ui->tableWidgetRecipient2->setItem(i, 6, new QTableWidgetItem(PrimaPubKey::trustToStr(key->getTrust())));
                    ui->tableWidgetRecipient2->item(i, 6)->setBackgroundColor(Configuration::getDefaultValidityColor(key->getTrust()));

                    ui->tableWidgetRecipient2->item(i, 3)->setBackgroundColor(Configuration::getDefaultValidityColor(uid->getValidity()));
                    ui->tableWidgetRecipient2->item(i, 5)->setBackgroundColor(Configuration::getDefaultValidityColor(key->getValidity()));
                    i++;
                }
            }
        }
    }
}

FileSignAndEncryption::~FileSignAndEncryption()
{
    delete ui;
}

void FileSignAndEncryption::on_browseButton2_clicked()
{
    QString pathName = QFileDialog::getOpenFileName(this, "Selection du fichier à chiffrer");
    ui->sourceFileEdit2->setText(pathName);
}

void FileSignAndEncryption::on_exitButton2_clicked()
{
    m_manager->cancelProcess();
    close();
}

void FileSignAndEncryption::onEncryptionCompleted()
{
    ui->warningLabel2->setText("Chiffrement terminé !");
    ui->exitButton2->setText("Fermer");
}
#include <QDebug>
void FileSignAndEncryption::on_okButton2_clicked()
{
    ui->warningLabel2->setText("");
    if (ui->sourceFileEdit2->text().startsWith("~/") || ui->destinationFileEdit2->text().startsWith("~/")) {
        ui->warningLabel2->setText("Seul les chemins absolus sont autorisés.");
        return;
    }

    if (ui->sourceFileEdit2->text() == ui->destinationFileEdit2->text()) {
        ui->warningLabel2->setText("Vous ne pouvez pas utiliser le même fichier source et destination.");
        return;
    }

    QFile sourcefile(ui->sourceFileEdit2->text());
    if (!sourcefile.exists()) {
        ui->warningLabel2->setText("Le fichier source n'existe pas.");
        return;
    }

    QFileInfo sourceFileInfo(sourcefile);
    if (!sourceFileInfo.isReadable()) {
        ui->warningLabel2->setText("Vous n'avez pas les droits de lecture sur le fichier source.");
        return;
    }

    QFile destinationfile(ui->destinationFileEdit2->text());
    if (destinationfile.exists()) {
        if (!destinationfile.remove()) {
            ui->warningLabel2->setText("Impossible d'écraser le fichier existant. Veuillez modifier la destination.");
            return;
        }
    }

    QFileInfo destinationFileInfo(destinationfile);
    QFileInfo destinationDirInfo(destinationFileInfo.absoluteDir().path());
    if (!destinationDirInfo.isWritable()) {
        ui->warningLabel2->setText("Vous n'avez pas les droits d'écriture sur le dossier destination.");
        return;
    }

    // On récupère l'indice des lignes selectionnées
    QModelIndexList selectedIndex = ui->tableWidgetRecipient2->selectionModel()->selectedIndexes();
    QList<int> rowIndexes;
    for (QModelIndex index : selectedIndex) {
        if (!rowIndexes.contains(index.row())) {
            rowIndexes.append(index.row());
        }
    }

    if (rowIndexes.count() == 0) {
        ui->warningLabel2->setText("Vous devez sélectionnez au moins un destinaire.");
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
        << "--output" << ui->destinationFileEdit2->text();
    QString cmd = "-e";
    QStringList arg;
    arg << ui->sourceFileEdit2->text();
    QStringList interactions;

    if (ui->anonymousCheckBox2->isChecked()) {
        for (int i : rowIndexes) {
            opt << "-R \""
                   + ui->tableWidgetRecipient2->item(i, 0)->text()
                   + " <"
                   + ui->tableWidgetRecipient2->item(i, 1)->text()
                   + ">\"";
        }

        for (int i : reverseRowIndexes) {
            if (ui->tableWidgetRecipient2->item(i, 3)->text() == GpgObject::validityToStr(VALIDITY_NO_VALUE) ||
                    ui->tableWidgetRecipient2->item(i, 3)->text() == GpgObject::validityToStr(VALIDITY_UNDEFINED)) {
                interactions << "y";
            }
        }
    } else {
        for (int i : rowIndexes) {
            interactions << ui->tableWidgetRecipient2->item(i, 0)->text()
                           + " <"
                           + ui->tableWidgetRecipient2->item(i, 1)->text()
                           + ">";
            if (ui->tableWidgetRecipient2->item(i, 3)->text() == GpgObject::validityToStr(VALIDITY_NO_VALUE) ||
                    ui->tableWidgetRecipient2->item(i, 3)->text() == GpgObject::validityToStr(VALIDITY_UNDEFINED)) {
                interactions << "y";
            }
        }
        interactions << "";
    }

    Action action(cmd, arg, opt, interactions);
    m_manager->setAction(action);
    connect(m_manager, &GPGManager::finished, this, &FileSignAndEncryption::onEncryptionCompleted);
    m_manager->execute();
}

void FileSignAndEncryption::on_outputButton2_clicked()
{
    QString pathName = QFileDialog::getSaveFileName(this, "Sauvegarde du fichier chiffré");
    ui->destinationFileEdit2->setText(pathName);
}
