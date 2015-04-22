#ifndef FILEDECRYPTIONANDVERIFY_H
#define FILEDECRYPTIONANDVERIFY_H

#include <QDialog>
#include "../Profile/profile.h"
#include "../GPG/gpgmanager.h"

namespace Ui {
class FileDecryptionAndVerify;
}

class FileDecryptionAndVerify : public QDialog
{
    Q_OBJECT

public:
    explicit FileDecryptionAndVerify(Profile* profile, QWidget *parent = 0);
    ~FileDecryptionAndVerify();

private slots:
    void on_browseSourceFileButton_clicked();

    void on_browseDestinationFileButton_clicked();

    void onGpgFinished(int s, QString output);

    void accept();

private:
    Ui::FileDecryptionAndVerify *ui;
    Profile* m_profile = nullptr;
    GPGManager* m_gpg = nullptr;
};

#endif // FILEDECRYPTIONANDVERIFY_H
