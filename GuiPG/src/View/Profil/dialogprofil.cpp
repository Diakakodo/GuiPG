#include "dialogprofil.h"
#include "ui_dialogprofil.h"
#include <QPushButton>
#include "../../Profile/profile.h"
#include "../../Profile/profile.h"
#include "../../Configuration/configuration.h"
#include <QDebug>


DialogProfil::DialogProfil(DIALOG_TYPE dialog_type, MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::DialogProfil)
{
    ui->setupUi(this);
    QAbstractButton* actionButton;
    if (dialog_type == SELECT) {
        actionButton = new QPushButton("&Charger", this);
        ui->buttonBox->addButton(actionButton, QDialogButtonBox::AcceptRole);
        connect(actionButton, SIGNAL(clicked()), this, SLOT(loadSelectProfil()));
    } else if (dialog_type == DELETE) {
        actionButton = new QPushButton("&Supprimer", this);
        ui->buttonBox->addButton(actionButton, QDialogButtonBox::ActionRole);
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

    ui->tableWidgetProfil->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

DialogProfil::~DialogProfil()
{
    delete ui;
}

void DialogProfil::loadSelectProfil() {
    bool ok;
    uint id = ui->tableWidgetProfil->selectedItems().first()->text().toUInt(&ok);
    if(ok){
        qDebug() << id;
        emit selectProfil(&id);
    } else {
      qDebug() << "erreur de conversion sur id profil selectionné";
    }
}
