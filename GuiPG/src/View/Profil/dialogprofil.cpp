#include "dialogprofil.h"
#include "ui_dialogprofil.h"
#include <QPushButton>
#include "../../Profile/profile.h"
#include "../../Profile/profile.h"
#include "../../Configuration/configuration.h"


DialogProfil::DialogProfil(DIALOG_TYPE dialog_type, MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::DialogProfil)
{
    ui->setupUi(this);
    if (dialog_type == SELECT) {
        ui->buttonBox->addButton("&Charger", QDialogButtonBox::ActionRole);
    } else if (dialog_type == DELETE) {
        ui->buttonBox->addButton("&Supprimer", QDialogButtonBox::ActionRole);
    }
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("&Annuler");

    QStringList m_TableHeader;
    m_TableHeader<<"N°"<<"Nom"<<"Dossier de configuration";
    ui->tableWidgetProfil->setHorizontalHeaderLabels(m_TableHeader);

    QList<Profile*> profilList = parent->getConfiguration()->getProfiles();
    ui->tableWidgetProfil->setRowCount(profilList.size());

    Profile* profil;
    int i = 0;
    foreach (profil, profilList) {
        ui->tableWidgetProfil->setItem(i, 0, new QTableWidgetItem(QString::number(profil->getId())));
        ui->tableWidgetProfil->setItem(i, 1, new QTableWidgetItem(profil->getName()));
        ui->tableWidgetProfil->setItem(i, 2, new QTableWidgetItem(profil->getConfigurationPath()));
        ui->tableWidgetProfil->setRowHeight(i, 20);
        ++i;
    }
}

DialogProfil::~DialogProfil()
{
    delete ui;
}
