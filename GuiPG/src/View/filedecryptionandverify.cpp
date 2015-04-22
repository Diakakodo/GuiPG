#include "filedecryptionandverify.h"
#include "ui_filedecryptionandverify.h"
#include <QFile>
#include <QFileDialog>
#include "../Launcher/launcher.h"
#include "mainwindow.h"

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
    ui->acceptButton->setEnabled(false);

    if (ui->sourceFileEdit->text() == ui->destinationFileEdit->text()) {
        ui->warningLabel->setText("Vous ne pouvez pas utiliser le même fichier source et destination.");
        ui->acceptButton->setEnabled(true);
        return;
    }

    QFile sourcefile(ui->sourceFileEdit->text());
    if (!sourcefile.exists()) {
        ui->warningLabel->setText("Le fichier source n'existe pas.");
        ui->acceptButton->setEnabled(true);
        return;
    }
    QFileInfo sourceFileInfo(sourcefile);
    if (!sourceFileInfo.isReadable()) {
        ui->warningLabel->setText("Vous n'avez pas les droits de lecture sur le fichier source.");
        ui->acceptButton->setEnabled(true);
        return;
    }

    QFile destinationfile(ui->destinationFileEdit->text());
    if (destinationfile.exists()) {
        if (!destinationfile.remove()) {
            ui->warningLabel->setText("Impossible d'écraser le fichier existant. Veuillez modifier la destination.");
            ui->acceptButton->setEnabled(true);
            return;
        }
    }

    QStringList opt;
    opt << "--status-fd=1"
        << "--command-fd=0"
        << "--output"
        << ui->destinationFileEdit->text();
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
        return;
    }
    if (output.contains("[GNUPG:] NO_SECKEY")) {
        ui->warningLabel->setText(ui->warningLabel->text() + "Échec du déchiffrement : la clef secrète n'est pas disponible.\n");
        return;
    }
    if (output.contains("[GNUPG:] NO_PUBKEY")) {
        ui->warningLabel->setText(ui->warningLabel->text() + "Impossible de vérifier la signature : la clef publique est introuvable dans votre trousseau de clefs.\n");
        return;
    }

    QPalette palette(ui->warningLabel->palette());
    QBrush brush(QColor(55, 212, 55));
    brush.setStyle(Qt::SolidPattern);
    palette.setBrush(QPalette::All, QPalette::WindowText, brush);
    ui->warningLabel->setPalette(palette);
    ui->warningLabel->setText("Déchiffrement / Vérification terminé.\n");
    if (output.contains("[GNUPG:] GOODSIG")) {
        ui->warningLabel->setText(ui->warningLabel->text() + "La signature est valide.\n");
    }
    if (output.contains("[GNUPG:] DECRYPTION_OKAY")) {
        ui->warningLabel->setText(ui->warningLabel->text() + "Le fichier est correctement déchiffré.\n");
    }
    QFile file(ui->destinationFileEdit->text());
    if (file.exists()) {
        file.open(QFile::ReadOnly);
        emit fileDecrypt(QFileInfo(file).baseName(), QString(file.readAll()));
    }
    ui->acceptButton->setEnabled(true);
}


