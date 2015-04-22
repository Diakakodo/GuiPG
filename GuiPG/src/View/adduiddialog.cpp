#include "adduiddialog.h"
#include "ui_adduiddialog.h"
#include <QDebug>
AddUidDialog::AddUidDialog(Profile* profile, PrimaPubKey* pub, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUidDialog)
{
    ui->setupUi(this);
    m_profile = profile;
    m_pub = pub;
}

AddUidDialog::~AddUidDialog()
{
    delete ui;
}

void AddUidDialog::accept() {
    qDebug() << "pouet";
    ui->warningLabel->clear();
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
        QStringList opt;
        opt << "--status-fd=1"
            << "--command-fd=0"
            << "--with-colons"
            << "--fixed-list-mode";
        QStringList args;
        args << m_pub->getKeyId();
        QStringList interactions;
        interactions << "adduid"
                      << ui->nameEdit->text()
                      << ui->mailEdit->text()
                      << ui->commentEdit->text()
                      << "y"
                      << "save";

        Action addUidAction(QString("--edit-key"), args, opt, interactions);

        m_gpg->setAction(addUidAction);
        connect(m_gpg, &GPGManager::finished, this, &AddUidDialog::finished);
        m_gpg->execute();
        done(1);
    }
}
