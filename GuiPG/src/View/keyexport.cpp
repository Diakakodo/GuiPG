#include "keyexport.h"
#include "ui_keyexport.h"
#include "../GPG/action.h"
#include "../GPG/gpgmanager.h"
#include "QFileDialog"
#include "iostream"
#include "QDebug"
#include "QEventLoop"
#include "unistd.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "stdio.h"


KeyExport::KeyExport(MainWindow*parent, Type mode, QStringList keys) :
    QDialog(parent),
    ui(new Ui::KeyExport),
    m_mode(mode),
    m_keys(keys),
    m_profile(parent->getProfil())
{

    ui->setupUi(this);
    ui->keyServerRadioButton->hide();
    ui->keyServerList->hide();
}

KeyExport::~KeyExport()
{
    delete ui;
}

void KeyExport::on_cancelButton_clicked()
{
    close();
}

void KeyExport::on_browseButton_clicked()
{
    QString pathName = QFileDialog::getSaveFileName(this, "Fichier cible");
    ui->pathEdit->setText(pathName);
}

void KeyExport::on_exportButton_clicked()
{

    if (ui->keyServerRadioButton->isChecked()) {
        exportFunction(EXPORT_KEYSERVER, ui->keyServerList->currentText(), "");
    } else
        if (ui->fileRadioButton->isChecked()) {
            exportFunction(EXPORT_FILE, "", ui->pathEdit->text());
        }
}

void KeyExport::on_keyServerList_activated(const QString &arg1)
{
    if (arg1 == ""){
        // not used.
    }
    ui->keyServerRadioButton->click();
}

void KeyExport::on_pathEdit_textChanged(const QString &arg1)
{
    if (arg1 == ""){
        // not used.
    }
    ui->fileRadioButton->click();
}

int KeyExport::exportFunction(ExportMode mode, QString keyserver, QString path) {
    QStringList keyList;
    for (QString key : m_keys) {
        keyList << key;
    }
    GPGManager* manager = new GPGManager(m_profile);
    if (mode == EXPORT_KEYSERVER) {
        if (keyserver != "") {
            Action keyExport(QString("--send-keys"), keyList, QStringList() << "--keyserver" << keyserver);
            manager->setAction(keyExport);
        } else {
            Action keyExport(QString("--send-keys"), keyList, QStringList());
            manager->setAction(keyExport);
        }
    } else
        if (mode == EXPORT_FILE && path != "") {

            Action keyExport(m_mode == PUBLIC_KEYS ? QString("--export") : QString("--export-secret-keys"), keyList, QStringList() << "--with-colons" << "-a" << "--output " + path);
            manager->setAction(keyExport);
            struct stat st;
            QByteArray ba = path.toLocal8Bit();
            const char *file = ba.data();
            if(stat(file, &st) == 0) {
                ui->warningLabel->setText("Ce fichier existe déjà.");
                return -1;
            }
            path.chop(path.length() - path.lastIndexOf("/"));
            ba = path.toLocal8Bit();
            const char *directory = ba.data();
            if  (access(directory, W_OK) != 0) {
               ui->warningLabel->setText("Vous n'avez pas le droit d'écrire à cet emplacement.");
               return -1;
            }

        }
    ui->warningLabel->setText("Exportation en cours...");
    manager->execute();
    delete manager;
    close();
    return 0;
}

