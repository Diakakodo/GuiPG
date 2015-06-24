#ifndef EDITOR_H
#define EDITOR_H

#include <QDialog>
#include "mainwindow.h"
#include "../GPG/gpgmanager.h"

namespace Ui {
class Editor;
}

class Editor : public QDialog
{
    Q_OBJECT

public:
    explicit Editor(MainWindow *parent, KeyManager *keyManager);
    ~Editor();

private slots:
    void on_encryptButton_clicked();

    void onEncryptionCompleted();

    void on_exitButton_clicked();

private:
    Ui::Editor *ui;
    Profile* m_profile;
    GPGManager* m_manager;
    MainWindow* m_parent;
    KeyManager* m_keyManager;
};

#endif // EDITOR_H
