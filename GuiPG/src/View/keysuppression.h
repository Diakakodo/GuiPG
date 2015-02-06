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

private:
    Ui::KeySuppression *ui;
};

#endif // KEYSUPPRESSION_H
