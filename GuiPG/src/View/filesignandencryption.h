#ifndef FILESIGNANDENCRYPTION_H
#define FILESIGNANDENCRYPTION_H

#include <QDialog>
#include "mainwindow.h"
#include "../GPG/gpgmanager.h"

namespace Ui {
class FileSignAndEncryption;
}

class FileSignAndEncryption : public QDialog
{
    Q_OBJECT

public:
    explicit FileSignAndEncryption(MainWindow *parent, KeyManager *keyManager);
    ~FileSignAndEncryption();

private slots:
    void on_browseButton2_clicked();

    void on_exitButton2_clicked();

    void on_okButton2_clicked();

    void onEncryptionCompleted();

    void on_outputButton2_clicked();

private:
    Ui::FileSignAndEncryption *ui;
    Profile* m_profile;
    GPGManager* m_manager;
    MainWindow* m_parent;
    KeyManager* m_keyManager;

};

#endif // FILESIGNANDENCRYPTION_H

