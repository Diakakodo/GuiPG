#include "dialogprofile.h"
#include "ui_dialogprofile.h"
#include <QPushButton>
#include "../../Profile/profile.h"
#include "../../Configuration/configuration.h"
#include <QDebug>


DialogProfile::DialogProfile(MainWindow *parent) :
    QDialog(parent),
    ui(new Ui::DialogProfile), m_parent(parent)
{
    ui->setupUi(this);

    // Configure la buttonBox
    m_loadButton = new QPushButton("&Charger", this);
    ui->buttonBox->addButton(m_loadButton, QDialogButtonBox::AcceptRole);
    connect(m_loadButton, &QAbstractButton::clicked, this, &DialogProfile::loadSelectProfile);

    m_createButton = new QPushButton("&Créer", this);
    ui->buttonBox->addButton(m_createButton, QDialogButtonBox::ActionRole);
    connect(m_createButton, &QAbstractButton::clicked, parent, &MainWindow::showDialogCreateProfile);

    m_deleteButton = new QPushButton("&Supprimer", this);
    ui->buttonBox->addButton(m_deleteButton, QDialogButtonBox::ActionRole);
    //connect(m_deleteButton, &QAbstractButton::clicked, this, &DialogProfile::deleteSelectProfile);

    m_setDefaultButton = new QPushButton("&Profil par défaut", this);
    ui->buttonBox->addButton(m_setDefaultButton, QDialogButtonBox::ActionRole);
    //connect(m_setDefaultButton, &QAbstractButton::clicked, this, &DialogProfile::setDefaultSelectProfile);

    m_loadButton->setEnabled(false);
    m_deleteButton->setEnabled(false);
    m_setDefaultButton->setEnabled(false);

    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("&Fermer");

    // Configure les en-têtes du tableau
    ui->tableWidgetProfil->setColumnCount(3);
    ui->tableWidgetProfil->setColumnWidth(0,20);
    QStringList m_TableHeader;
    m_TableHeader<<"N°"<<"Nom"<<"Dossier de configuration";
    ui->tableWidgetProfil->setHorizontalHeaderLabels(m_TableHeader);

    // Rempli la tableau de profil
    fillTableWidget();

    ui->tableWidgetProfil->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(ui->tableWidgetProfil, &QTableWidget::itemSelectionChanged, this, &DialogProfile::enableAtionButton);
}

DialogProfile::~DialogProfile()
{
    delete ui;
}

void DialogProfile::fillTableWidget() {
    ui->tableWidgetProfil->clearContents();
    QList<Profile*> profileList = m_parent->getConfiguration()->getProfiles();
    ui->tableWidgetProfil->setRowCount(profileList.size());
    Profile* profile;
    int i = 0;
    foreach (profile, profileList) {
        ui->tableWidgetProfil->setItem(i, 0, new QTableWidgetItem(QString::number(profile->getId())));
        ui->tableWidgetProfil->setItem(i, 1, new QTableWidgetItem(profile->getName()));
        ui->tableWidgetProfil->setItem(i, 2, new QTableWidgetItem(profile->getConfigurationPath()));
        ui->tableWidgetProfil->setRowHeight(i, 20);
        if (profile->isDefault()) {
            QFont font;
            font.setBold(true);
            ui->tableWidgetProfil->item(i,0)->setFont(font);
            ui->tableWidgetProfil->item(i,1)->setFont(font);
            ui->tableWidgetProfil->item(i,2)->setFont(font);
        }
        ++i;
    }
}

void DialogProfile::loadSelectProfile() {
    bool ok;
    unsigned id = ui->tableWidgetProfil->selectedItems().first()->text().toUInt(&ok);
    if(ok){
        emit selectProfile(id);
    } else {
      qDebug() << "erreur de conversion sur id profil selectionné";
    }
}

void DialogProfile::deleteSelectProfile() {

}

void DialogProfile::enableAtionButton() {
    m_loadButton->setEnabled(true);
    m_deleteButton->setEnabled(true);
    m_setDefaultButton->setEnabled(true);
}
