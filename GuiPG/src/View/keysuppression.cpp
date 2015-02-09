#include "keysuppression.h"
#include "ui_keysuppression.h"
#include "../action.h"


KeySuppression::KeySuppression(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeySuppression)
{
    ui->setupUi(this);
}

KeySuppression::~KeySuppression()
{
    delete ui;
}


void KeySuppression::on_pushButton_clicked()
{
    close();
}


void KeySuppression::on_pushButton_2_clicked()
{
    //Action KeySuppression(QString("--delete-keys"), QStringList(), QStringList(), interactions);
    // TODO Donner l'action à gpg
    // TODO Comment rentrer la phrase de passe ?
    //errorLabel->setText("Veuillez patienter pendant la suppression de la clef...\n");

    // TODO Attendre que GPG ait fini de supprimer la clef
    //close();
}
