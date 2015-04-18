#include "profilecreation.h"
#include "ui_profilecreation.h"
#include <QFileDialog>
#include <iostream>
#include "unistd.h"

ProfileCreation::ProfileCreation(DialogProfile *parent, unsigned profileId) :
    QDialog(parent), ui(new Ui::ProfileCreation), m_parent(parent), m_profileId(profileId)
{
    ui->setupUi(this);
    if (m_profileId != 0) {
        ui->acceptButton->setText("Editer");
        ui->nameEdit->setText(m_parent->getConfig()->getProfileById(m_profileId)->getName());
        ui->gpgPathEdit->setText(m_parent->getConfig()->getProfileById(m_profileId)->getGPGExecutable());
        ui->storagePathEdit->setText(m_parent->getConfig()->getProfileById(m_profileId)->getConfigurationPath());
    }
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
    if (m_profileId != 0) {
        m_parent->getConfig()->getProfileById(m_profileId)->setGPGExecutable(ui->gpgPathEdit->text());
        m_parent->getConfig()->getProfileById(m_profileId)->setConfigurationPath(ui->storagePathEdit->text());
    } else {
        QList<Profile*> profileList = m_parent->getConfig()->getProfiles();
        unsigned max = 0;
        for (Profile* l : profileList) {
            if (l->getId() > max) {
                max = l->getId();
            }
        }
        QByteArray ba = ui->storagePathEdit->text().toLocal8Bit();
        const char *directory = ba.data();
        if  (access(directory, W_OK) != 0) {
           ui->warningLabel->setText("Vous n'avez pas le droit d'écrire à cet emplacement.");
           return;
        }
        Profile* p = new Profile(max + 1, ui->nameEdit->text());
        p->setConfigurationPath(ui->storagePathEdit->text());
        p->setGPGExecutable(ui->gpgPathEdit->text());
        m_parent->getConfig()->addProfile(p);
    }
    m_parent->getConfig()->save();
    m_parent->refreshTableWidget();
    close();
}
