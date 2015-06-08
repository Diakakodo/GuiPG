#ifndef FILESIGN_H
#define FILESIGN_H

#include <QDialog>

namespace Ui {
class Filesign;
}

class Filesign : public QDialog
{
    Q_OBJECT

public:
    explicit Filesign(QWidget *parent = 0);
    ~Filesign();

private:
    Ui::Filesign *ui;
};

#endif // FILESIGN_H
