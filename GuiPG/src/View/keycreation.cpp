#include "keycreation.h"
#include "ui_keycreation.h"
#include <QRegExp>
#include "../GPG/action.h"
#include "../Profile/profile.h"
#include "../GPG/gpgmanager.h"

KeyCreation::KeyCreation(MainWindow*parent) :
    QDialog(parent),
    ui(new Ui::KeyCreation)
{
    m_profile = parent->getProfil();
    m_model = parent->getModel();
    m_window = parent;
    ui->setupUi(this);
    if (true) {
        ui->lineEdit_4->hide();
        ui->label_8->hide();
    }
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
        interactions << ui->lineEdit->text();
        interactions << ui->lineEdit_3->text();
        interactions << ui->lineEdit_2->text();
        if (!m_profile->getGPGExecutable().endsWith("2")) {
            interactions << ui->lineEdit_4->text();
        }


        QStringList opt;
        opt << "--status-fd=1" << "--command-fd=0";
        Action keyCreation(QString("--gen-key"), QStringList(), opt, interactions);

        GPGManager* manager = new GPGManager(m_profile);
        manager->setAction(keyCreation);
        connect(manager, &GPGManager::finished, this, &KeyCreation::keyCreationFinished);
        manager->execute();
        errorLabel->setText("Veuillez patienter pendant la création de la clé...\n");

    }
}

void KeyCreation::keyCreationFinished()
{
    m_window->refreshKeys();
    close();
}

void KeyCreation::on_pushButton_clicked()
{
    close();
}

void KeyCreation::on_radioButton_2_clicked()
{
    ui->horizontalSlider->setMaximum(3072);
    if (ui->horizontalSlider->value() > 3072) {
        ui->horizontalSlider->setValue(3072);
    }
    ui->spinBox_2->setValue(ui->horizontalSlider->value());
    ui->spinBox_2->setMaximum(3072);
}

void KeyCreation::on_radioButton_3_clicked()
{
    ui->horizontalSlider->setMaximum(3072);
    if (ui->horizontalSlider->value() > 3072) {
        ui->horizontalSlider->setValue(3072);
    }
    ui->spinBox_2->setValue(ui->horizontalSlider->value());
    ui->spinBox_2->setMaximum(3072);
}

void KeyCreation::on_radioButton_clicked()
{
    ui->horizontalSlider->setMaximum(4096);
    ui->spinBox_2->setValue(ui->horizontalSlider->value());
    ui->spinBox_2->setMaximum(4096);
}

void KeyCreation::on_radioButton_4_clicked()
{
    ui->horizontalSlider->setMaximum(4096);
    ui->spinBox_2->setValue(ui->horizontalSlider->value());
    ui->spinBox_2->setMaximum(4096);
}
