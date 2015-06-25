#include "filedecryptionandverifyeditor.h"
#include "ui_filedecryptionandverifyeditor.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>
#include "../Launcher/launcher.h"
#include "mainwindow.h"
#include <QMimeDatabase>
#include <string>

FileDecryptionAndVerifyEditor::FileDecryptionAndVerifyEditor(Profile* profile, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileDecryptionAndVerifyEditor)
{
    ui->setupUi(this);
    m_profile = profile;
    /*if (Launcher::m_profileMainWindowHash.contains(profile)) {
        MainWindow* window = Launcher::m_profileMainWindowHash.value(profile);
    }*/
    ui->cancelButton2->setText("Fermer");
}

FileDecryptionAndVerifyEditor::~FileDecryptionAndVerifyEditor()
{
    delete ui;
}

void FileDecryptionAndVerifyEditor::on_acceptButton2_clicked() {
    ui->warningLabel->setText("");
    if (ui->destinationFileEdit2->text().startsWith("~/")) {
        ui->warningLabel->setText("Seul les chemins absolus sont autorisés.");
        return;
    }

    QStringList opt;

    if (ui->destinationFileEdit2->text() != "") {
        QFile destinationfile(ui->destinationFileEdit2->text());
        if (destinationfile.exists()) {
            if (!destinationfile.remove()) {
                ui->warningLabel->setText("Impossible d'écraser le fichier existant. Veuillez modifier la destination.");
                return;
            }
        }

        QFileInfo destinationFileInfo(destinationfile);
        QFileInfo destinationDirInfo(destinationFileInfo.absoluteDir().path());
        if (!destinationDirInfo.isWritable()) {
            ui->warningLabel->setText("Vous n'avez pas les droits d'écriture sur le dossier destination.");
            return;
        }

        opt << "--status-fd=1"
            << "--command-fd=0"
            << "--output"
            << ui->destinationFileEdit2->text();
    }
    else {
        opt << "--status-fd=1"
            << "--command-fd=0";
    }

    ui->acceptButton2->setEnabled(false);

    QStringList args;
    args << "/tmp/tmpFile";

    Action decryptAndVerifyAction("", args, opt, QStringList("y"));
    m_gpg = new GPGManager(m_profile);
    m_gpg->setAction(decryptAndVerifyAction);
    connect(m_gpg, &GPGManager::finished, this, &FileDecryptionAndVerifyEditor::onGpgFinished);
    m_gpg->execute();
}

void FileDecryptionAndVerifyEditor::on_browseDestinationFileButton2_clicked()
{
    QString pathName = QFileDialog::getSaveFileName(this, "Fichier destination");
    ui->destinationFileEdit2->setText(pathName);
}

void FileDecryptionAndVerifyEditor::onGpgFinished(int s, QString output) {
    if (s) {
        // not used;
    }
    delete m_gpg;
    if (output.contains("[GNUPG:] NODATA")) {
        ui->warningLabel->setText(ui->warningLabel->text() + "Aucune donnée OpenPGP valable n'a été trouvée.\nRien à déchiffrer ou vérifier.");
        ui->acceptButton2->setEnabled(true);
        return;
    }
    if (output.contains("[GNUPG:] NO_SECKEY") && !output.contains("[GNUPG:] DECRYPTION_OKAY")) {
        ui->warningLabel->setText(ui->warningLabel->text() + "Échec du déchiffrement : la clef secrète n'est pas disponible.\n");
        ui->acceptButton2->setEnabled(true);
        return;
    }
    if (output.contains("[GNUPG:] NO_PUBKEY")) {
        ui->warningLabel->setText(ui->warningLabel->text() + "Impossible de vérifier la signature : la clef publique est introuvable dans votre trousseau de clefs.\n");
        ui->acceptButton2->setEnabled(true);
        return;
    }

    QPalette palette(ui->warningLabel->palette());
    QBrush brush(QColor(55, 212, 55));
    brush.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::All, QPalette::WindowText, brush);
    ui->warningLabel->setPalette(palette);
    ui->warningLabel->setText("Déchiffrement / Vérification terminé.\n");
    if (output.contains("anonyme")) {
        ui->warningLabel->setText(ui->warningLabel->text() + "Destinataire(s) : Anonyme.\n");
    } else {
        QStringList split = output.split("«");
        QString dest;
        int nbDest;
        if (output.contains("[GNUPG:] GOODSIG")) {
            nbDest = split.size() - 1;
        } else {
            nbDest = split.size();
        }
        for (int i = 2; i < nbDest; i++) {
            QString tmp = split.at(i);
            QStringList split2 = tmp.split("»");
            QString name = split2.at(0);
            dest += name + "\n";
        }
        ui->warningLabel->setText(ui->warningLabel->text() + "Destinataire(s) : " + dest);
    }

    if (output.contains("[GNUPG:] GOODSIG")) {
        //Split permettant de récupérer l'uid de la signature dans le retour de gpg
        QStringList split1 = output.split("Bonne signature de «");
        QString tmp = split1.at(1);
        QStringList split2 = tmp.split("»");
        QString name = split2.at(0);
        ui->warningLabel->setText(ui->warningLabel->text() + "Signature correct de : " + name + "\n");
    }
    if (output.contains("[GNUPG:] DECRYPTION_OKAY")) {
        ui->warningLabel->setText(ui->warningLabel->text() + "Le fichier est correctement déchiffré.\n");
    }

    QFile file(ui->destinationFileEdit2->text());
    QString infos = "";
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        while(!in.atEnd()) {
            infos += in.readLine() + "\n";
        }
        file.close();
    }
    QMessageBox::question(0, "Fichier chiffré", infos, QMessageBox::Cancel);

    ui->acceptButton2->setEnabled(true);
}

void FileDecryptionAndVerifyEditor::on_cancelButton2_clicked() {
    close();
}


