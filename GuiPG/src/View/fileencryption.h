#ifndef FILEENCRYPTION_H
#define FILEENCRYPTION_H

#include <QDialog>
#include "mainwindow.h"
#include "../GPG/gpgmanager.h"

namespace Ui {
class FileEncryption;
}

class FileEncryption : public QDialog
{
    Q_OBJECT

public:
    explicit FileEncryption(MainWindow *parent, KeyManager *keyManager);
    ~FileEncryption();

private slots:
    void on_browseButton_clicked();

    void on_exitButton_clicked();

    void on_okButton_clicked();

    void onEncryptionCompleted();

private:
    Ui::FileEncryption *ui;
    Profile* m_profile;
    GPGManager* m_manager;
    MainWindow* m_parent;
    KeyManager* m_keyManager;

};

#endif // FILEENCRYPTION_H

