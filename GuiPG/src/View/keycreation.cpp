#include "keycreation.h"
#include "ui_keycreation.h"
#include <QRegExp>
#include "../action.h"

KeyCreation::KeyCreation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KeyCreation)
{
    ui->setupUi(this);
}

KeyCreation::~KeyCreation()
{
    delete ui;
}

void KeyCreation::on_comboBox_currentIndexChanged(int index)
{
    if (index == 0) {
        ui->spinBox->hide();
    } else {
        ui->spinBox->show();
    }
}

void KeyCreation::on_horizontalSlider_sliderMoved(int position)
{
    ui->spinBox_2->setValue(position);
}

void KeyCreation::on_spinBox_2_valueChanged(int arg1)
{
    ui->horizontalSlider->setValue(arg1);
}

void KeyCreation::on_pushButton_2_clicked()
{
    QLabel* errorLabel = ui->label_5;
    errorLabel->setText("");
    if (ui->lineEdit->text().length() < 5) {
        errorLabel->setText("Le nom doit contenir au moins 5 caractères.\n");
    }
    QRegExp mailREX("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
    mailREX.setCaseSensitivity(Qt::CaseInsensitive);
    mailREX.setPatternSyntax(QRegExp::RegExp);
    mailREX.exactMatch("me@me.com");
    if (!mailREX.exactMatch(ui->lineEdit_3->text())) {
        errorLabel->setText(errorLabel->text() + "Adresse email incorrecte.\n");
    }
    if (ui->spinBox->value() == 0 && ui->comboBox->currentIndex() != 0) {
        errorLabel->setText(errorLabel->text() + "Durée de la clé incorrecte.\n");
    }

    if (errorLabel->text() == "") {
        QStringList interactions;
        if (ui->radioButton->isChecked()) {
            interactions << "1";
        } else {
            if (ui->radioButton_2->isChecked()) {
                interactions << "2";
            } else {
                if (ui->radioButton_3->isChecked()) {
                    interactions << "3";
                } else {
                    interactions << "4";
                }
            }
        }

        interactions << QString::number(ui->horizontalSlider->value());
        switch(ui->comboBox->currentIndex()) {
            case 0 :
                interactions << "0";
                break;
            case 1 :
                interactions << QString::number(ui->spinBox->value()) + "d";
                break;
            case 2 :
                interactions << QString::number(ui->spinBox->value()) + "w";
                break;
            case 3 :
                interactions << QString::number(ui->spinBox->value()) + "m";
                break;
            case 5 :
                interactions << QString::number(ui->spinBox->value()) + "y";
                break;
        }
        interactions << "o";
        interactions << ui->lineEdit->text();
        interactions << ui->lineEdit_3->text();
        interactions << ui->lineEdit_2->text();
        interactions << "O";

        Action keyCreation(QString("--gen-key"), QStringList(), QStringList(), interactions);
        // TODO Donner l'action à gpg
        // TODO Comment rentrer la phrase de passe ?
        errorLabel->setText("Veuillez patienter pendant la création de la clé...\n");

        // TODO Attendre que GPG ait fini de générer la clé
        //close();
    }
}


void KeyCreation::on_pushButton_clicked()
{
    close();
}
