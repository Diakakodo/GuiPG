#include "deleteuiddialog.h"
#include "ui_deleteuiddialog.h"
#include <QDebug>

DeleteUidDialog::DeleteUidDialog(Profile* profile, PrimaPubKey* pub, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteUidDialog)
{

    ui->setupUi(this);
    m_profile = profile;
    m_pub = pub;

    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QStringList m_TableHeader;
    m_TableHeader   <<"Nom"
                    <<"Email";
    ui->tableWidget->setHorizontalHeaderLabels(m_TableHeader);
    ui->tableWidget->setColumnWidth(0,150);
    ui->tableWidget->setColumnWidth(1,150);

    int i = 0;

    for (Uid* u : m_pub->getUidList()) {
        ui->tableWidget->setRowCount(i+1);
        ui->tableWidget->setRowHeight(i, 20);
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(u->getName()));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(u->getMail()));
        i++;
    }
}


DeleteUidDialog::~DeleteUidDialog()
{
    delete ui;
}

void DeleteUidDialog::on_exitButton_clicked()
{
    close();
}

void DeleteUidDialog::onDeleteCompleted(){
    ui->warningLabel->setText("Suppression terminé !");
    ui->exitButton->setText("Fermer");
}

#include <QDebug>
void DeleteUidDialog::on_deleteButton_clicked()
{

    int number = ui->tableWidget->currentIndex().row() + 1;
    QString uidNumber = QString::number(number);

    m_gpg = new GPGManager(m_profile);

    QStringList opt;
    opt << "--status-fd=1"
        << "--command-fd=0"
        << "--with-colons"
        << "--fixed-list-mode";
    QStringList args;
    args << m_pub->getKeyId();
    QStringList interactions;
    QString uidSelection = "uid " + uidNumber;
    interactions << uidSelection
                 << "deluid"
                 << "y"
                 << "save";

    Action delUidAction(QString("--edit-key"), args, opt, interactions);

    m_gpg->setAction(delUidAction);
    connect(m_gpg, &GPGManager::finished, this, &DeleteUidDialog::finished);
    m_gpg->execute();
}


void DeleteUidDialog::on_revokeButton_clicked()
{
    int number = ui->tableWidget->currentIndex().row() + 1;
    QString uidNumber = QString::number(number);

    m_gpg = new GPGManager(m_profile);

    QStringList opt;
    opt << "--status-fd=1"
        << "--command-fd=0"
        << "--with-colons"
        << "--fixed-list-mode";
    QStringList args;
    args << m_pub->getKeyId();
    QStringList interactions;
    QString uidSelection = "uid " + uidNumber;
    interactions << uidSelection
                 << "revuid"
                 << "y"
                 << "4"
                 << "Identité plus valide"
                 << ""
                 << "y"
                 << "save";

    Action delUidAction(QString("--edit-key"), args, opt, interactions);

    m_gpg->setAction(delUidAction);
    connect(m_gpg, &GPGManager::finished, this, &DeleteUidDialog::finished);
    m_gpg->execute();
}
