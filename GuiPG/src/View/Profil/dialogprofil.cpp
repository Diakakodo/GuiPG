#include "dialogprofil.h"
#include "ui_dialogprofil.h"
#include <QPushButton>
#include "../../Profile/profile.h"
#include "../../Configuration/configuration.h"
#include <QDebug>


DialogProfil::DialogProfil(DIALOG_TYPE dialog_type, MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::DialogProfil), m_actionButton(NULL)
{
    ui->setupUi(this);

    // Configure la buttonBox
    if (dialog_type == SELECT) {
        m_actionButton = new QPushButton("&Charger", this);
        ui->buttonBox->addButton(m_actionButton, QDialogButtonBox::AcceptRole);
        connect(m_actionButton, &QAbstractButton::clicked, this, &DialogProfil::loadSelectProfil);
    } else if (dialog_type == DELETE) {
        m_actionButton = new QPushButton("&Supprimer", this);
        ui->buttonBox->addButton(m_actionButton, QDialogButtonBox::ActionRole);
    }
    m_actionButton->setEnabled(false);

    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("&Annuler");

    // Configure les en-tête du tableau
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
    connect(ui->tableWidgetProfil, &QTableWidget::itemSelectionChanged, this, &DialogProfil::enableAtionButton);
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

void DialogProfil::deleteSelectProfil() {

}

void DialogProfil::enableAtionButton() {
    m_actionButton->setEnabled(true);
}
