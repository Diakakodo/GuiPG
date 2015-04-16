#ifndef KEYEDITION_H
#define KEYEDITION_H

#include <QDialog>

namespace Ui {
class KeyEdition;
}

class KeyEdition : public QDialog
{
    Q_OBJECT

public:
    explicit KeyEdition(QWidget *parent = 0);
    ~KeyEdition();

private:
    Ui::KeyEdition *ui;
};

#endif // KEYEDITION_H
