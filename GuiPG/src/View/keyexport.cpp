#include "keyexport.h"
#include "ui_keyexport.h"
#include "../GPG/action.h"
#include "../GPG/gpgmanager.h"
#include "QFileDialog"
#include "iostream"
#include "QDebug"

KeyExport::KeyExport(QWidget *parent, Type mode) :
    QDialog(parent),
    ui(new Ui::KeyExport),
    m_mode(mode)
{
    ui->setupUi(this);
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


        close();
    } else
        if (ui->fileRadioButton->isChecked() && ui->pathEdit->text() != "") {
            Action keyExport(m_mode == PUBLIC_KEYS ? QString("--export") : QString("--export-secret-keys"), QStringList(), QStringList() << "-a" << "--output " + ui->pathEdit->text());

            GPGManager* manager = new GPGManager(new Profile());

            qDebug() << keyExport.getCmd();
            qDebug() << keyExport.getArgs();
            qDebug() << keyExport.getOptions();
            manager->setAction(keyExport);
            manager->execute();
            qDebug() << manager->getOutput();
            close();
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
