#ifndef ADDUIDDIALOG_H
#define ADDUIDDIALOG_H

#include <QDialog>
#include "../GPG/gpgmanager.h"
#include "../Profile/profile.h"
#include "../Keys/primapubkey.h"

namespace Ui {
class AddUidDialog;
}

class AddUidDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddUidDialog(Profile* profile, PrimaPubKey* pub, QWidget *parent = 0);
    ~AddUidDialog();

public slots:
    void accept();

signals:
    void finished();

private:
    Ui::AddUidDialog *ui;
    GPGManager* m_gpg;
    Profile* m_profile;
    PrimaPubKey* m_pub;
};

#endif // ADDUIDDIALOG_H
