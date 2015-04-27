#ifndef KEYIMPORT_H
#define KEYIMPORT_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class KeyImport;
}

class KeyImport : public QDialog
{
    Q_OBJECT

public:
    explicit KeyImport(MainWindow *parent = 0);
    ~KeyImport();

private slots:
    void on_cancelButton_clicked();

    void on_browseButton_clicked();

    void on_pathEdit_textChanged(const QString &arg1);

    void on_keyIdEdit_textChanged(const QString &arg1);

    void on_importButton_clicked();

    void keyImportFinished(int a, QString s);

    void checkFinished(int a, QString s);

private:
    Ui::KeyImport *ui = nullptr;
    MainWindow* m_window = nullptr;
    Profile* m_profile = nullptr;
    GPGManager* m_gpg = nullptr;
};

#endif // KEYIMPORT_H
