#include "keyexport.h"
#include "ui_keyexport.h"
#include "../GPG/action.h"
#include "../GPG/gpgmanager.h"
#include "QFileDialog"
#include "iostream"
#include "QDebug"
#include "QEventLoop"

KeyExport::KeyExport(MainWindow*parent, Type mode, QStringList keys) :
    QDialog(parent),
    ui(new Ui::KeyExport),
    m_mode(mode),
    m_keys(keys),
    m_profile(parent->getProfil())
{

    ui->setupUi(this);
    if (keys.length() == 0 || mode == SECRET_KEYS) {
        ui->keyServerRadioButton->hide();
        ui->keyServerList->hide();
    }
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
        exportFunction(KEYSERVER, ui->keyServerList->currentText(), "");
    } else
        if (ui->fileRadioButton->isChecked()) {
            exportFunction(FILE, "", ui->pathEdit->text());
        }
}

void KeyExport::on_keyServerList_activated(const QString &arg1)
{
    ui->keyServerRadioButton->click();
}

void KeyExport::on_pathEdit_textChanged(const QString &arg1)
{
    ui->fileRadioButton->click();
}

void KeyExport::exportFunction(ExportMode mode, QString keyserver, QString path) {
    QStringList keyList;
    for (QString key : m_keys) {
        keyList << key;
    }
    GPGManager* manager = new GPGManager(m_profile);
    if (mode == KEYSERVER) {
        if (keyserver != "") {
            Action keyExport(QString("--send-keys"), keyList, QStringList() << "--keyserver" << keyserver);
            manager->setAction(keyExport);
        } else {
            Action keyExport(QString("--send-keys"), keyList, QStringList());
            manager->setAction(keyExport);
        }
    } else
        if (mode == FILE && path != "") {

            Action keyExport(m_mode == PUBLIC_KEYS ? QString("--export") : QString("--export-secret-keys"), keyList, QStringList() << "--with-colons" << "-a" << "--output " + path);

            manager->setAction(keyExport);
        }

    QEventLoop loop;
    connect(manager, &GPGManager::finished, &loop, &QEventLoop::quit);
    manager->execute();
    loop.exec();

    close();
}

