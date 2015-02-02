#include "dialogprofil.h"
#include "ui_dialogprofil.h"
#include <QPushButton>
#include "../../Profile/profile.h"
#include "../../Profile/profile.h"
#include "../../Configuration/configuration.h"


DialogProfil::DialogProfil(DIALOG_TYPE dialog_type, QWidget *parent) :
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
    ui->tableWidgetProfil->setColumnCount(3);
    QStringList m_TableHeader;
    m_TableHeader<<"N°"<<"Nom"<<"Dossier de configuration";
    ui->tableWidgetProfil->setHorizontalHeaderLabels(m_TableHeader);

}

DialogProfil::~DialogProfil()
{
    delete ui;
}
