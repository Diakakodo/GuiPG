#ifndef KEYEXPORT_H
#define KEYEXPORT_H

#include <QDialog>

namespace Ui {
class KeyExport;
}

class KeyExport : public QDialog
{
    Q_OBJECT

public:
    explicit KeyExport(QWidget *parent = 0);
    ~KeyExport();

private slots:
    void on_cancelButton_clicked();

private:
    Ui::KeyExport *ui;
};

#endif // KEYEXPORT_H