#include "profilecreation.h"
#include "ui_profilecreation.h"
#include <QFileDialog>
#include <iostream>

ProfileCreation::ProfileCreation(MainWindow *parent) :
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
    QString filename=QFileDialog::getOpenFileName(this,tr("Open File"),"","All files (*.*)" );
    ui->gpgPathEdit->setText(filename);
}

void ProfileCreation::on_storagePathButton_clicked()
{
    QString filename=QFileDialog::getOpenFileName(this,tr("Open File"),"","All files (*.*)" );
    ui->storagePathEdit->setText(filename);
}

void ProfileCreation::on_acceptButton_clicked()
{
    QList<Profile*> profileList = m_parent->getConfiguration()->getProfiles();
    unsigned max = 0;
    for (Profile* l : profileList) {
        if (l->getId() > max) {
            max = l->getId();
        }
    }
    Profile* p = new Profile(max + 1, ui->nameEdit->text());
    p->setConfigurationPath(ui->storagePathEdit->text());
    p->setGPGExecutable(ui->gpgPathEdit->text());
    m_parent->getConfiguration()->addProfile(p);
    m_parent->getConfiguration()->save();
    m_parent->changeProfil(max + 1);

    close();
}
