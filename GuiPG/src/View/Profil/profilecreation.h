#ifndef PROFILECREATION_H
#define PROFILECREATION_H

#include <QDialog>
#include "../mainwindow.h"
#include "../../View/Profil/dialogprofile.h"

namespace Ui {
class ProfileCreation;
}

class ProfileCreation : public QDialog
{
    Q_OBJECT

public:
    explicit ProfileCreation(DialogProfile* parent, unsigned profileId = 0);
    ~ProfileCreation();

signals:
    void updateDialogProfile();

private slots:
    void on_cancelButton_clicked();

    void on_gpgPathButton_clicked();

    void on_storagePathButton_clicked();

    void on_acceptButton_clicked();

private:
    Ui::ProfileCreation *ui;
    DialogProfile* m_parent;
    unsigned m_profileId;
};

#endif // PROFILECREATION_H
