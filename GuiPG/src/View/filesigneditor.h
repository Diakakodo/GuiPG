#ifndef FileSignEditor_H
#define FileSignEditor_H

#include <QDialog>
#include "mainwindow.h"
#include "../GPG/gpgmanager.h"

namespace Ui {
class FileSignEditor;
}

class FileSignEditor : public QDialog
{
    Q_OBJECT

public:
    explicit FileSignEditor(MainWindow *parent, KeyManager *keyManager);
    ~FileSignEditor();

private slots:
    void on_browseButton_clicked();

    void on_exitButton_clicked();

    void on_okButton_clicked();

    void onSignatureCompleted();

private:
    Ui::FileSignEditor *ui;
    Profile* m_profile;
    GPGManager* m_manager;
    MainWindow* m_parent;
    KeyManager* m_keyManager;

};

#endif // FILESIGNEDITOR_H

