#include "keycreation.h"
#include "ui_keycreation.h"
#include <QRegExp>
#include <QScrollBar>
#include "../GPG/action.h"
#include "../Profile/profile.h"
#include "../GPG/gpgmanager.h"

KeyCreation::KeyCreation(MainWindow*parent) :
    QDialog(parent),
    ui(new Ui::KeyCreation)
{
    m_profile = parent->getProfil();
    m_manager = new GPGManager(m_profile);
    m_model = parent->getModel();
    m_window = parent;
    ui->setupUi(this);
    if (false) {
        ui->lineEdit_4->hide();
        ui->label_8->hide();
    }
}

KeyCreation::~KeyCreation()
{
    delete m_manager;
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

    if(ui->lineEdit_4->text() == "" || ui->lineEdit_5->text() == "") {
        errorLabel->setText(errorLabel->text() + "Passphrase incomplète.\n");
    }

    if (ui->lineEdit_4->text() != ui->lineEdit_5->text()) {
        errorLabel->setText(errorLabel->text() + "Votre confirmation de passphrase est incorrecte.\n");
    }

    if (errorLabel->text() == "") {
        ui->pushButton_2->setEnabled(false);
        QStringList interactions;
        if (ui->radioButton->isChecked()) {
            interactions << "Key-Type: RSA";//"1";
            interactions << "Subkey-Type: RSA";
        } else {
            if (ui->radioButton_2->isChecked()) {
                interactions << "Key-Type: DSA";//"2";
                interactions << "Subkey-Type: ELG-E";
            } else {
                if (ui->radioButton_3->isChecked()) {
                    interactions << "Key-Type: DSA";//"3";
                } else {
                    interactions << "Key-Type: RSA";//"4";
                }
            }
        }

        interactions << "Key-Length: " + QString::number(ui->horizontalSlider->value());
        interactions << "Subkey-Length: " + QString::number(ui->horizontalSlider->value());

        switch(ui->comboBox->currentIndex()) {
            case 0 :
                interactions << "Expire-Date: 0";
                break;
            case 1 :
                interactions << "Expire-Date: " + QString::number(ui->spinBox->value()) + "d";
                break;
            case 2 :
                interactions << "Expire-Date: " + QString::number(ui->spinBox->value()) + "w";
                break;
            case 3 :
                interactions << "Expire-Date: " + QString::number(ui->spinBox->value()) + "m";
                break;
            case 5 :
                interactions << "Expire-Date: " + QString::number(ui->spinBox->value()) + "y";
                break;
        }
        interactions << "Name-Real: " + ui->lineEdit->text();
        interactions << "Name-Comment: " + ui->lineEdit_2->text();
        interactions << "Name-Email: " + ui->lineEdit_3->text();
        interactions << "Passphrase: " + ui->lineEdit_4->text();


        QStringList opt;
        opt << "--batch" << "--verbose" << "--status-fd=1" << "--command-fd=0";
        Action keyCreation(QString("--gen-key"), QStringList(), opt, interactions);

        connect(m_manager, &GPGManager::newData, this, &KeyCreation::addData);
        m_manager->setAction(keyCreation);
        connect(m_manager, &GPGManager::finished, this, &KeyCreation::keyCreationFinished);
        m_manager->execute();
        errorLabel->setText("Veuillez patienter pendant la création de la clé...\n");
    }
}

void KeyCreation::addData(const QString& data) {
    // On ajoute les nouvelles données
    ui->dataBrowser->setText(ui->dataBrowser->toPlainText() + data);
    // On scroll vers le bas.
    ui->dataBrowser->verticalScrollBar()->setValue(ui->dataBrowser->verticalScrollBar()->maximum());
}

void KeyCreation::keyCreationFinished()
{
    m_window->getModel()->getKeyManager()->load();
    ui->pushButton->setText("Fermer");
    //close();
}

void KeyCreation::on_pushButton_clicked()
{
    // On ne refresh pas la liste si on annule.
    disconnect(m_manager, &GPGManager::finished, this, &KeyCreation::keyCreationFinished);
    m_manager->cancelProcess();
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
