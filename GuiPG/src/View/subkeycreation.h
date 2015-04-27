#ifndef SUBKEYCREATION_H
#define SUBKEYCREATION_H

#include <QDialog>
#include "../GPG/gpgmanager.h"
#include "../Profile/profile.h"
#include "../Keys/primapubkey.h"

namespace Ui {
class SubKeyCreation;
}

class SubKeyCreation : public QDialog
{
        Q_OBJECT

    public:
        explicit SubKeyCreation(Profile* profile, PrimaPubKey* pub, QWidget *parent = 0);
        ~SubKeyCreation();

    private slots:
        void onOkClicked();
        void onCancelClicked();
        void on_rButtonDSASign_clicked();
        void on_rButtonRSASign_clicked();
        void on_rButtonElgCiph_clicked();
        void on_rButtonRSACiph_clicked();
        void on_sliderSize_sliderMoved(int position);
        void on_spinBoxSize_valueChanged(int arg1);
        void addData(QString data);
        void onSubKkeyCreationFinished();

    private:
        Ui::SubKeyCreation *ui;
        GPGManager* m_gpg = nullptr;
        Profile* m_profile = nullptr;
        PrimaPubKey* m_pub = nullptr;
};

#endif // SUBKEYCREATION_H
