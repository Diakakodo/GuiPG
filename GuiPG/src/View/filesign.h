#ifndef FileSign_H
#define FileSign_H

#include <QDialog>
#include "mainwindow.h"
#include "../GPG/gpgmanager.h"

namespace Ui {
class FileSign;
}

class FileSign : public QDialog
{
    Q_OBJECT

public:
    explicit FileSign(MainWindow *parent, KeyManager *keyManager);
    ~FileSign();

private slots:
    void on_browseButton_clicked();

    void on_exitButton_clicked();

    void on_okButton_clicked();

    void onEncryptionCompleted();

    void on_outputButton_clicked();

private:
    Ui::FileSign *ui;
    Profile* m_profile;
    GPGManager* m_manager;
    MainWindow* m_parent;
    KeyManager* m_keyManager;

};

#endif // FILESIGN_H

