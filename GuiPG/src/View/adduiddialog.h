#ifndef ADDUIDDIALOG_H
#define ADDUIDDIALOG_H

#include <QDialog>
#include "../GPG/gpgmanager.h"
#include "../Profile/profile.h"

namespace Ui {
class AddUidDialog;
}

class AddUidDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddUidDialog(Profile* profile, QWidget *parent = 0);
    ~AddUidDialog();

public slots:
    void accept();


private:
    Ui::AddUidDialog *ui;
    GPGManager* m_gpg;
    Profile* m_profile;
};

#endif // ADDUIDDIALOG_H
