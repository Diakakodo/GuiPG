#ifndef DELETEUIDDIALOG_H
#define DELETEUIDDIALOG_H

#include <QDialog>
#include "../GPG/gpgmanager.h"
#include "../Profile/profile.h"
#include "../Keys/primapubkey.h"

namespace Ui {
class DeleteUidDialog;
}

class DeleteUidDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteUidDialog(Profile* profile, PrimaPubKey* pub, QWidget *parent = 0);
    ~DeleteUidDialog();

private slots:
    void on_exitButton_clicked();

    void onDeleteCompleted();

    void on_deleteButton_clicked();

    void on_revokeButton_clicked();

signals:
    void finished();

private:
    Ui::DeleteUidDialog *ui;
    GPGManager* m_gpg;
    Profile* m_profile;
    PrimaPubKey* m_pub;
};

#endif // DELETEUIDDIALOG_H
