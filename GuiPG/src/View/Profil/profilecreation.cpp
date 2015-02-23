#include "profilecreation.h"
#include "ui_profilecreation.h"
#include <QFileDialog>
#include <iostream>

ProfileCreation::ProfileCreation(DialogProfile *parent) :
    QDialog(parent), ui(new Ui::ProfileCreation), m_parent(parent)
{
    ui->setupUi(this);
}

ProfileCreation::~ProfileCreation()
{
    delete ui;
}

void ProfileCreation::on_cancelButton_clicked()
{
    close();
}

void ProfileCreation::on_gpgPathButton_clicked()
{
    QString filename=QFileDialog::getOpenFileName(this,tr("Open File"),
        "/home","All files (*)" );
    ui->gpgPathEdit->setText(filename);
}

void ProfileCreation::on_storagePathButton_clicked()
{
    QString pathName = QFileDialog::getExistingDirectory(this,
        tr("Open Directory"),
        "/home",
        QFileDialog::ShowDirsOnly);
    ui->storagePathEdit->setText(pathName);
}

void ProfileCreation::on_acceptButton_clicked()
{
    QList<Profile*> profileList = m_parent->getConfig()->getProfiles();
    unsigned max = 0;
    for (Profile* l : profileList) {
        if (l->getId() > max) {
            max = l->getId();
        }
    }
    Profile* p = new Profile(max + 1, ui->nameEdit->text());
    p->setConfigurationPath(ui->storagePathEdit->text());
    p->setGPGExecutable(ui->gpgPathEdit->text());
    m_parent->getConfig()->addProfile(p);
    m_parent->getConfig()->save();
    m_parent->refreshTableWidget();
    close();
}
