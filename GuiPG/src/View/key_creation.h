#ifndef KEY_CREATION_H
#define KEY_CREATION_H

#include <QDialog>

namespace Ui {
class Key_creation;
}

class Key_creation : public QDialog
{
    Q_OBJECT

public:
    explicit Key_creation(QWidget *parent = 0);
    ~Key_creation();

private:
    Ui::Key_creation *ui;
};

#endif // KEY_CREATION_H
