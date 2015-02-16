#ifndef PROFILECREATION_H
#define PROFILECREATION_H

#include <QDialog>
#include "../mainwindow.h"

namespace Ui {
class ProfileCreation;
}

class ProfileCreation : public QDialog
{
    Q_OBJECT

public:
    explicit ProfileCreation(MainWindow *parent = 0);
    ~ProfileCreation();

private slots:
    void on_cancelButton_clicked();

    void on_gpgPathButton_clicked();

    void on_storagePathButton_clicked();

    void on_acceptButton_clicked();

private:
    Ui::ProfileCreation *ui;
};

#endif // PROFILECREATION_H
