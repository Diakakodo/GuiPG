#ifndef KEYSUPPRESSION_H
#define KEYSUPPRESSION_H

#include <QDialog>

namespace Ui {
class KeySuppression;
}

class KeySuppression : public QDialog
{
    Q_OBJECT

public:
    explicit KeySuppression(QWidget *parent = 0);
    ~KeySuppression();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::KeySuppression *ui;
};

#endif // KEYSUPPRESSION_H
