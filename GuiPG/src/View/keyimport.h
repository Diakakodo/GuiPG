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

private:
    Ui::KeyImport *ui;
};

#endif // KEYIMPORT_H
