#include "subkeycreation.h"
#include "ui_subkeycreation.h"
#include <QDialogButtonBox>
#include <QPushButton>
#include <QScrollBar>

#define MIN_DSA_LEN 1024
#define MIN_ELG_LEN 1024
#define MIN_RSA_LEN 1024

#define MAX_DSA_LEN 3072
#define MAX_ELG_LEN 4096
#define MAX_RSA_LEN 4096

#define DEFAULT_DSA_LEN 2048
#define DEFAULT_ELG_LEN 2048
#define DEFAULT_RSA_LEN 2048

SubKeyCreation::SubKeyCreation(Profile *profile, PrimaPubKey *pub, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SubKeyCreation)
{
    setModal(true);
    ui->setupUi(this);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("Ajouter");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Annuler");
    connect(ui->buttonBox->button(QDialogButtonBox::Ok), &QPushButton::clicked, this, &SubKeyCreation::onOkClicked);
    connect(ui->buttonBox->button(QDialogButtonBox::Cancel), &QPushButton::clicked, this, &SubKeyCreation::onCancelClicked);
    m_pub = pub;
    m_profile = profile;
    m_gpg = new GPGManager(m_profile);
    connect(ui->sliderSize, &QSlider::sliderMoved, this, &SubKeyCreation::on_sliderSize_sliderMoved);
    on_rButtonDSASign_clicked();
}

SubKeyCreation::~SubKeyCreation()
{
    delete ui;
    delete m_gpg;
}

void SubKeyCreation::on_rButtonDSASign_clicked() {
    ui->sliderSize->setMinimum(MIN_DSA_LEN);
    ui->sliderSize->setMaximum(MAX_DSA_LEN);
    ui->sliderSize->setValue(DEFAULT_DSA_LEN);
    ui->spinBoxSize->setValue(ui->sliderSize->value());
}
void SubKeyCreation::on_rButtonRSASign_clicked() {
    ui->sliderSize->setMinimum(MIN_RSA_LEN);
    ui->sliderSize->setMaximum(MAX_RSA_LEN);
    ui->sliderSize->setValue(DEFAULT_RSA_LEN);
    ui->spinBoxSize->setValue(ui->sliderSize->value());
}
void SubKeyCreation::on_rButtonElgCiph_clicked() {
    ui->sliderSize->setMinimum(MIN_ELG_LEN);
    ui->sliderSize->setMaximum(MAX_ELG_LEN);
    ui->sliderSize->setValue(DEFAULT_ELG_LEN);
    ui->spinBoxSize->setValue(ui->sliderSize->value());
}
void SubKeyCreation::on_rButtonRSACiph_clicked() {
    ui->sliderSize->setMinimum(MIN_RSA_LEN);
    ui->sliderSize->setMaximum(MAX_RSA_LEN);
    ui->sliderSize->setValue(DEFAULT_RSA_LEN);
    ui->spinBoxSize->setValue(ui->sliderSize->value());

}

void SubKeyCreation::on_spinBoxSize_valueChanged(int arg1)
{
    ui->sliderSize->setValue(arg1);
}

void SubKeyCreation::on_sliderSize_sliderMoved(int position)
{
    ui->spinBoxSize->setValue(position);
}


void SubKeyCreation::onOkClicked() {
    ui->labelStatus->setText("");
    if (ui->spinBoxExpiration->value() == 0 && ui->comboBoxExpiration->currentIndex() != 0) {
        ui->labelStatus->setText(ui->labelStatus->text() + "Durée de la clé incorrecte.\n");
        return;
    }
    if (ui->labelStatus->text() == "") {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
        QStringList interactions;
        interactions << "addkey";
        if (ui->rButtonDSASign->isChecked()) {
            interactions << "3";
        } else if (ui->rButtonRSASign->isChecked()) {
            interactions << "4";
        } else if (ui->rButtonElgCiph->isChecked()) {
            interactions << "5";
        } else { // i.e.  : ui->rButtonRSACiph->isChecked()
            interactions << "6";
        }
        interactions  << QString::number(ui->sliderSize->value());

        switch(ui->comboBoxExpiration->currentIndex()) {
            case 0 :
                interactions << "0";
                break;
            case 1 :
                interactions <<  QString::number(ui->spinBoxExpiration->value()) + "d";
                break;
            case 2 :
                interactions << QString::number(ui->spinBoxExpiration->value()) + "w";
                break;
            case 3 :
                interactions << QString::number(ui->spinBoxExpiration->value()) + "m";
                break;
            case 5 :
                interactions << QString::number(ui->spinBoxExpiration->value()) + "y";
                break;
        }
        interactions << "y";
        interactions << "y";
        interactions << "save";

        QStringList opt;
        opt << "--status-fd=1" << "--command-fd=0";
        Action subKeyCreationAction(QString("--edit-key"), QStringList(m_pub->getKeyId()), opt, interactions);

        connect(m_gpg, &GPGManager::newData, this, &SubKeyCreation::addData);
        m_gpg->setAction(subKeyCreationAction);
        connect(m_gpg, &GPGManager::finished, this, &SubKeyCreation::onSubKkeyCreationFinished);
        m_gpg->execute();
        ui->labelStatus->setText("Veuillez patienter pendant la création de la clé...\n");
    }
}

void SubKeyCreation::onSubKkeyCreationFinished() {
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("Fermer");
    emit finished(1);
}

void SubKeyCreation::addData(QString data) {
    // On ajoute les nouvelles données
    ui->dataBrowserSubKeyCreation->setText(ui->dataBrowserSubKeyCreation->toPlainText() + data);
    // On scroll vers le bas.
    ui->dataBrowserSubKeyCreation->verticalScrollBar()->setValue(ui->dataBrowserSubKeyCreation->verticalScrollBar()->maximum());
}


void SubKeyCreation::onCancelClicked() {
    if (m_gpg->isRunning()) {
        m_gpg->cancelProcess();
    }
    setVisible(false);
}
