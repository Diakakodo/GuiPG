#ifndef CONFIG_H
#define CONFIG_H

#include <QDialog>
#include "mainwindow.h"
#include "../Profile/profile.h"


namespace Ui {
class config;
}

class config : public QDialog
{
    Q_OBJECT

public:
    explicit config(MainWindow *parent = 0);
    ~config();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::config *ui;
    Profile *m_profil;
    QString location;
};

#endif // CONFIG_H
