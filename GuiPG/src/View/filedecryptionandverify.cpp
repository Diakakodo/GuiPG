#include "filedecryptionandverify.h"
#include "ui_filedecryptionandverify.h"
#include <QFile>
#include <QFileDialog>
#include "../Launcher/launcher.h"
#include "mainwindow.h"
#include <QMimeDatabase>
#include <string>

FileDecryptionAndVerify::FileDecryptionAndVerify(Profile* profile, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileDecryptionAndVerify)
{
    ui->setupUi(this);
    m_profile = profile;
    if (Launcher::m_profileMainWindowHash.contains(profile)) {
        MainWindow* window = Launcher::m_profileMainWindowHash.value(profile);
        connect(this, &FileDecryptionAndVerify::fileDecrypt, window, &MainWindow::addTab);
    }
    ui->cancelButton->setText("Fermer");
}

FileDecryptionAndVerify::~FileDecryptionAndVerify()
{
    delete ui;
}

void FileDecryptionAndVerify::accept() {
    ui->warningLabel->setText("");
    if (ui->sourceFileEdit->text().startsWith("~/") || ui->destinationFileEdit->text().startsWith("~/")) {
        ui->warningLabel->setText("Seul les chemins absolus sont autorisés.");
        return;
    }

    if (ui->sourceFileEdit->text() == ui->destinationFileEdit->text()) {
        ui->warningLabel->setText("Vous ne pouvez pas utiliser le même fichier source et destination.");
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

    QStringList opt;

    if (ui->destinationFileEdit->text() != "") {
        QFile destinationfile(ui->destinationFileEdit->text());
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
            << ui->destinationFileEdit->text();
    }
    else {
        opt << "--status-fd=1"
            << "--command-fd=0";
    }

    ui->acceptButton->setEnabled(false);

    QStringList args;
    args << ui->sourceFileEdit->text();

    Action decryptAndVerifyAction("", args, opt, QStringList("y"));
    m_gpg = new GPGManager(m_profile);
    m_gpg->setAction(decryptAndVerifyAction);
    connect(m_gpg, &GPGManager::finished, this, &FileDecryptionAndVerify::onGpgFinished);
    m_gpg->execute();
}

void FileDecryptionAndVerify::on_browseSourceFileButton_clicked()
{
    QString pathName = QFileDialog::getOpenFileName(this, "Fichier à déchiffrer / vérifier");
    ui->sourceFileEdit->setText(pathName);
}

void FileDecryptionAndVerify::on_browseDestinationFileButton_clicked()
{
    QString pathName = QFileDialog::getSaveFileName(this, "Fichier destination");
    ui->destinationFileEdit->setText(pathName);
}

void FileDecryptionAndVerify::onGpgFinished(int s, QString output) {
    if (s) {
        // not used;
    }
    delete m_gpg;
    if (output.contains("[GNUPG:] NODATA")) {
        ui->warningLabel->setText(ui->warningLabel->text() + "Aucune donnée OpenPGP valable n'a été trouvée.\nRien à déchiffrer ou vérifier.");
        ui->acceptButton->setEnabled(true);
        return;
    }
    if (output.contains("[GNUPG:] NO_SECKEY")) {
        ui->warningLabel->setText(ui->warningLabel->text() + "Échec du déchiffrement : la clef secrète n'est pas disponible.\n");
        ui->acceptButton->setEnabled(true);
        return;
    }
    if (output.contains("[GNUPG:] NO_PUBKEY")) {
        ui->warningLabel->setText(ui->warningLabel->text() + "Impossible de vérifier la signature : la clef publique est introuvable dans votre trousseau de clefs.\n");
        ui->acceptButton->setEnabled(true);
        return;
    }

    QPalette palette(ui->warningLabel->palette());
    QBrush brush(QColor(55, 212, 55));
    brush.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::All, QPalette::WindowText, brush);
    ui->warningLabel->setPalette(palette);
    ui->warningLabel->setText("Déchiffrement / Vérification terminé.\n");
    if (output.contains("[GNUPG:] GOODSIG")) {
        //Split permettant de récupérer l'uid de la signature dans le retour de gpg
        QStringList split1 = output.split("«");
        QString tmp = split1.at(1);
        QStringList split2 = tmp.split("»");
        QString name = split2.at(0);
        //ui->warningLabel->setText(ui->warningLabel->text() + "La signature est valide.\n" + output + "YOLOOOOOOOO:" + name);
        ui->warningLabel->setText(ui->warningLabel->text() + "Signature correct de : " + name);
    }
    if (output.contains("[GNUPG:] DECRYPTION_OKAY")) {
        ui->warningLabel->setText(ui->warningLabel->text() + "Le fichier est correctement déchiffré.\n");
    }
    QFile file(ui->destinationFileEdit->text());
    if (file.exists() && QFileInfo(file).isReadable()) {
        file.open(QFile::ReadOnly);
        QFileInfo fileInfo(file);
        QMimeDatabase mimedb;
        if (mimedb.mimeTypeForFile(fileInfo).name().startsWith("text/")) {
            // On n'affiche le contenu uniquement si le type/MIME est de type text.
            emit fileDecrypt(file.fileName().split(QDir::separator()).last(), QString(file.readAll()));
        }
    }
    ui->acceptButton->setEnabled(true);
}


