#ifndef DELETESUBKEYDIALOG_H
#define DELETESUBKEYDIALOG_H

#include <QDialog>
#include "../GPG/gpgmanager.h"
#include "../Profile/profile.h"
#include "../Keys/primapubkey.h"

namespace Ui {
class DeleteSubKeyDialog;
}

class DeleteSubKeyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteSubKeyDialog(Profile* profile, PrimaPubKey* pub, QWidget *parent = 0);
    ~DeleteSubKeyDialog();

private slots:
    void on_exitButton_clicked();

    void onDeleteCompleted();

    void on_deleteButton_clicked();

    void on_revokeButton_clicked();

private:
    Ui::DeleteSubKeyDialog *ui;
    GPGManager* m_gpg;
    Profile* m_profile;
    PrimaPubKey* m_pub;
};

#endif // DELETESUBKEYDIALOG_H
