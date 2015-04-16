#ifndef KEYCREATION_H
#define KEYCREATION_H

#include <QDialog>
#include "mainwindow.h"
#include "../GPG/gpgmanager.h"

namespace Ui {
class KeyCreation;
}

class KeyCreation : public QDialog
{
    Q_OBJECT

public:
    explicit KeyCreation(MainWindow *parent = 0);
    ~KeyCreation();

private:
    void keyCreationFinished();

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_horizontalSlider_sliderMoved(int position);

    void on_spinBox_2_valueChanged(int arg1);

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_clicked();

    void on_radioButton_4_clicked();

    void addData(const QString& data);

private:
    Ui::KeyCreation *ui;
    Profile* m_profile;
    MainWindowModel* m_model;
    MainWindow* m_window;
    GPGManager* m_manager;
};

#endif // KEYCREATION_H
