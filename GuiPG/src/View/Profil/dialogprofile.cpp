#include "dialogprofile.h"
#include "profilecreation.h"
#include "ui_dialogprofile.h"
#include <QPushButton>
#include "../../Profile/profile.h"
#include "../../Configuration/configuration.h"
#include <QMessageBox>
#include <QDebug>


DialogProfile::DialogProfile(Configuration* config, Launcher* launcher) :
    QDialog(),
    ui(new Ui::DialogProfile), m_conf(config), m_launcher(launcher)
{
    createAndPlaceWidget();
}

DialogProfile::~DialogProfile()
{
    delete m_loadButton;
    delete m_createButton;
    delete m_deleteButton;
    delete m_setDefaultButton;
    delete ui;
}

void DialogProfile::createAndPlaceWidget() {
    ui->setupUi(this);

    // Configure la buttonBox
    m_loadButton = new QPushButton("&Charger", this);
    ui->buttonBox->addButton(m_loadButton, QDialogButtonBox::AcceptRole);
    connect(m_loadButton, &QAbstractButton::clicked, this, &DialogProfile::loadSelectProfile);

    m_createButton = new QPushButton("&Créer", this);
    ui->buttonBox->addButton(m_createButton, QDialogButtonBox::ActionRole);
    connect(m_createButton, &QAbstractButton::clicked, this, &DialogProfile::showDialogCreateProfile);

    m_editButton = new QPushButton("&Editer", this);
    ui->buttonBox->addButton(m_editButton, QDialogButtonBox::ActionRole);
    connect(m_editButton, &QAbstractButton::clicked, this, &DialogProfile::showDialogEditProfile);

    m_setDefaultButton = new QPushButton("&Par défaut", this);
    m_setDefaultButton->setToolTip("Enregistrer le profil sélectionné comme celui par défaut");
    ui->buttonBox->addButton(m_setDefaultButton, QDialogButtonBox::ActionRole);
    connect(m_setDefaultButton, &QAbstractButton::clicked, this, &DialogProfile::setDefaultSelectProfile);

    m_deleteButton = new QPushButton("&Supprimer", this);
    ui->buttonBox->addButton(m_deleteButton, QDialogButtonBox::ActionRole);
    connect(m_deleteButton, &QAbstractButton::clicked, this, &DialogProfile::deleteSelectProfile);

    m_loadButton->setEnabled(false);
    m_editButton->setEnabled(false);
    m_setDefaultButton->setEnabled(false);
    m_deleteButton->setEnabled(false);

    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("&Fermer");

    // Configure les en-têtes du tableau
    ui->tableWidgetProfil->setColumnCount(3);
    ui->tableWidgetProfil->setColumnWidth(0,20);
    QStringList m_TableHeader;
    m_TableHeader<<"N°"<<"Nom"<<"Dossier de configuration";
    ui->tableWidgetProfil->setHorizontalHeaderLabels(m_TableHeader);

    // Rempli la tableau de profil
    refreshTableWidget();

    ui->tableWidgetProfil->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(ui->tableWidgetProfil, &QTableWidget::itemSelectionChanged, this, &DialogProfile::enableAtionButton);
}

void DialogProfile::refreshTableWidget() {
    ui->tableWidgetProfil->clearContents();
    QList<Profile*> profileList = m_conf->getProfiles();
    ui->tableWidgetProfil->setRowCount(profileList.size());
    Profile* profile;
    int i = 0;
    foreach (profile, profileList) {
        ui->tableWidgetProfil->setItem(i, 0, new QTableWidgetItem(QString::number(profile->getId())));
        ui->tableWidgetProfil->setItem(i, 1, new QTableWidgetItem(profile->getName()));
        ui->tableWidgetProfil->setItem(i, 2, new QTableWidgetItem(profile->getConfigurationPath()));
        ui->tableWidgetProfil->setRowHeight(i, 20);
        if (profile->getId() == m_conf->getDefaultProfileId()) {
            QFont font;
            font.setBold(true);
            ui->tableWidgetProfil->item(i,0)->setFont(font);
            ui->tableWidgetProfil->item(i,1)->setFont(font);
            ui->tableWidgetProfil->item(i,2)->setFont(font);
        }
        ++i;
    }
}

Configuration* DialogProfile::getConfig() const {
    return m_conf;
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

void DialogProfile::showDialogCreateProfile() {
    ProfileCreation d(this);
    d.exec();
}

void DialogProfile::showDialogEditProfile() {
    bool ok;
    unsigned id = ui->tableWidgetProfil->selectedItems().first()->text().toUInt(&ok);
    if(ok){
        ProfileCreation d(this, id);
        d.exec();
    } else {
      qDebug() << "erreur de conversion sur id profil selectionné";
    }
}

void DialogProfile::deleteSelectProfile() {
    bool ok;
    unsigned id = ui->tableWidgetProfil->selectedItems().first()->text().toUInt(&ok);
    if(ok){
        Profile* p = m_conf->getProfileById(id);
        if (m_launcher->profileIsLoad(p) != nullptr) {
            QMessageBox::critical(this, tr("Suppression impossible"),
                                            tr("Le profil que vous souhaitez supprimer est actuellement utilisé.\n"
                                               "Veuillez quitter la fenêtre qui l'utilise actuellement ou y charger un autre profil."),
                                            QMessageBox::Ok);
        } else {
            m_conf->deleteProfile(id);
            refreshTableWidget();
        }
    } else {
      qDebug() << "erreur de conversion sur id profil selectionné";
    }
}

void DialogProfile::setDefaultSelectProfile() {
    bool ok;
    unsigned id = ui->tableWidgetProfil->selectedItems().first()->text().toUInt(&ok);
    if(ok){
        m_conf->setDefaultProfileId(id);
        refreshTableWidget();
    } else {
      qDebug() << "erreur de conversion sur id profil selectionné";
    }
}

void DialogProfile::enableAtionButton() {
    if (ui->tableWidgetProfil->selectionModel()->hasSelection()) {
        m_loadButton->setEnabled(true);
        m_editButton->setEnabled(true);
        m_setDefaultButton->setEnabled(true);
        m_deleteButton->setEnabled(true);
    } else {
        m_loadButton->setEnabled(false);
        m_editButton->setEnabled(false);
        m_setDefaultButton->setEnabled(false);
        m_deleteButton->setEnabled(false);
    }
}
