#include "keycreation.h"
#include "ui_keycreation.h"
#include "QRegExp"

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
    if (ui->lineEdit->text() == "") {
        errorLabel->setText("Nom incorrect.\n");
    }
    QRegExp mailREX("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
    mailREX.setCaseSensitivity(Qt::CaseInsensitive);
    mailREX.setPatternSyntax(QRegExp::RegExp);
    mailREX.exactMatch("me@me.com");
    if (!mailREX.exactMatch(ui->lineEdit_3->text())) {
        errorLabel->setText(errorLabel->text() + "Adresse email incorrecte.\n");
    }
    if (ui->spinBox->value() == 0 && ui->comboBox->currentText() != "Illimitée") {
        errorLabel->setText(errorLabel->text() + "Durée incorrecte.\n");
    }

}

void KeyCreation::on_pushButton_clicked()
{
    close();
}
