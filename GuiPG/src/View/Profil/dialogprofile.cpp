#include "dialogprofile.h"
#include "ui_dialogprofile.h"
#include <QPushButton>
#include "../../Profile/profile.h"
#include "../../Configuration/configuration.h"
#include <QDebug>


DialogProfile::DialogProfile(DIALOG_TYPE dialog_type, MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::DialogProfile), m_actionButton(NULL)
{
    ui->setupUi(this);

    // Configure la buttonBox
    if (dialog_type == SELECT) {
        m_actionButton = new QPushButton("&Charger", this);
        ui->buttonBox->addButton(m_actionButton, QDialogButtonBox::AcceptRole);
        connect(m_actionButton, &QAbstractButton::clicked, this, &DialogProfile::loadSelectProfile);
    } else if (dialog_type == DELETE) {
        m_actionButton = new QPushButton("&Supprimer", this);
        ui->buttonBox->addButton(m_actionButton, QDialogButtonBox::ActionRole);
    }
    m_actionButton->setEnabled(false);

    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("&Annuler");

    // Configure les en-têtes du tableau
    QStringList m_TableHeader;
    m_TableHeader<<"N°"<<"Nom"<<"Dossier de configuration";
    ui->tableWidgetProfil->setHorizontalHeaderLabels(m_TableHeader);

    // Rempli la tableau de profil
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

    ui->tableWidgetProfil->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(ui->tableWidgetProfil, &QTableWidget::itemSelectionChanged, this, &DialogProfile::enableAtionButton);
}

DialogProfile::~DialogProfile()
{
    delete ui;
}

void DialogProfile::loadSelectProfile() {
    bool ok;
    unsigned id = ui->tableWidgetProfil->selectedItems().first()->text().toUInt(&ok);
    if(ok){
        qDebug() << id;
        emit selectProfile(id);
    } else {
      qDebug() << "erreur de conversion sur id profil selectionné";
    }
}

void DialogProfile::deleteSelectProfile() {

}

void DialogProfile::enableAtionButton() {
    m_actionButton->setEnabled(true);
}
