#ifndef FileEncryptionEditor_H
#define FileEncryptionEditor_H

#include <QDialog>
#include "mainwindow.h"
#include "../GPG/gpgmanager.h"

namespace Ui {
class FileEncryptionEditor;
}

class FileEncryptionEditor : public QDialog
{
    Q_OBJECT

public:
    explicit FileEncryptionEditor(MainWindow *parent, KeyManager *keyManager);
    ~FileEncryptionEditor();

private slots:
    void on_exitButton_clicked();

    void on_okButton_clicked();

    void onEncryptionCompleted();

    void on_outputButton_clicked();

private:
    Ui::FileEncryptionEditor *ui;
    Profile* m_profile;
    GPGManager* m_manager;
    MainWindow* m_parent;
    KeyManager* m_keyManager;

};

#endif // FILEENCRYPTIONEDITOR_H

