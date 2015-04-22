#include "fileencryption.h"
#include "ui_fileencryption.h"
#include "mainwindow.h"
#include <QFileDialog>
#include "../Keys/uid.h"
#include "../Keys/primapubkey.h"
#include <fstream>
#include "sys/types.h"
#include "sys/stat.h"

FileEncryption::FileEncryption(MainWindow *parent, KeyManager* keyManager) :
    QDialog(parent),
    ui(new Ui::FileEncryption)
{
    ui->setupUi(this);
    m_profile = parent->getProfil();
    m_manager = new GPGManager(m_profile);
    m_parent = parent;
    m_keyManager = keyManager;
    QList<PrimaPubKey *> pubKeys = keyManager->getPubKeys();
    QList<Uid *>* uids = new QList<Uid *>();
    for (PrimaPubKey* key : pubKeys) {
        uids->append(key->getUidList());
    }
    for (Uid* uid : *uids) {
        ui->comboBox->addItem(uid->getName());
    }
}

FileEncryption::~FileEncryption()
{
    delete ui;
}

void FileEncryption::on_browseButton_clicked()
{
    QString pathName = QFileDialog::getOpenFileName(this, "Fichier cible");
    ui->pathEdit->setText(pathName);
}

void FileEncryption::on_exitButton_clicked()
{
    m_manager->cancelProcess();
    close();
}

void FileEncryption::onEncryptionCompleted()
{
    ui->errorLabel->setText("Chiffrement terminé");
    ui->exitButton->setText("Fermer");
}

void FileEncryption::on_okButton_clicked()
{
    struct stat st;
    QByteArray ba = ui->outputEdit->text().toLocal8Bit();
    const char *file = ba.data();
    if(stat(file, &st) == 0) {
        remove(file);
    }
    Action action(QString("-e"), QStringList() << ui->pathEdit->text(), QStringList("--command-fd=0") << "--status-fd=1" << "--output" << ui->outputEdit->text(), QStringList(ui->comboBox->currentText()) << "");
    m_manager->setAction(action);
    connect(m_manager, &GPGManager::finished, this, &FileEncryption::onEncryptionCompleted);
    m_manager->execute();
}

void FileEncryption::on_outputButton_clicked()
{
    QString pathName = QFileDialog::getSaveFileName(this, "Fichier chiffré");
    ui->outputEdit->setText(pathName);
}
