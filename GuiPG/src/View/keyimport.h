#ifndef KEYIMPORT_H
#define KEYIMPORT_H

#include <QDialog>

namespace Ui {
class KeyImport;
}

class KeyImport : public QDialog
{
    Q_OBJECT

public:
    explicit KeyImport(QWidget *parent = 0);
    ~KeyImport();

private slots:
    void on_cancelButton_clicked();

    void on_browseButton_clicked();

    void on_pathEdit_textChanged(const QString &arg1);

    void on_keyIdEdit_textChanged(const QString &arg1);

private:
    Ui::KeyImport *ui;
};

#endif // KEYIMPORT_H
