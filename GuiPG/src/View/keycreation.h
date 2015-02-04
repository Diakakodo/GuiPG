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

private:
    Ui::KeyCreation *ui;
};

#endif // KEYCREATION_H
