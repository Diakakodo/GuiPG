#include "adduiddialog.h"
#include "ui_adduiddialog.h"

AddUidDialog::AddUidDialog(Profile* profile, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUidDialog)
{
    ui->setupUi(this);
    m_profile = profile;
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
}

AddUidDialog::~AddUidDialog()
{
    delete ui;
}

void AddUidDialog::accept() {
    if (ui->nameEdit->text().length() < 5) {
        ui->warningLabel->setText(ui->warningLabel->text() + "Le nom doit contenir au moins 5 caractères.\n");
    }
    QRegExp mailREX("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
    mailREX.setCaseSensitivity(Qt::CaseInsensitive);
    mailREX.setPatternSyntax(QRegExp::RegExp);
    if (!mailREX.exactMatch(ui->mailEdit->text())) {
        ui->warningLabel->setText(ui->warningLabel->text() + "Adresse email incorrecte.\n");
    }
    if (ui->commentEdit->text().contains('(') || ui->commentEdit->text().contains(')')) {
        ui->warningLabel->setText(ui->warningLabel->text() + "Les parenthèses ne sont pas autorisées dans un commentaire.\n");
    }
    if (ui->warningLabel->text() == "") {
        m_gpg = new GPGManager(m_profile);

    }
}
