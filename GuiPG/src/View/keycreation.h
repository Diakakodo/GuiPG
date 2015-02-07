#ifndef KEYCREATION_H
#define KEYCREATION_H

#include <QDialog>

namespace Ui {
class KeyCreation;
}

class KeyCreation : public QDialog
{
    Q_OBJECT

public:
    explicit KeyCreation(QWidget *parent = 0);
    ~KeyCreation();

private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_horizontalSlider_sliderMoved(int position);

    void on_spinBox_2_valueChanged(int arg1);

    void on_pushButton_2_clicked();

private:
    Ui::KeyCreation *ui;
};

#endif // KEYCREATION_H
