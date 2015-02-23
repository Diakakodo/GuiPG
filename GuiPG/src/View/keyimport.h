#ifndef KEYIMPORT_H
#define KEYIMPORT_H

#include <QDialog>

namespace Ui {
class KeyImport;
}

class KeyImport : public QDialog
{
    Q_OBJECT

public:
    explicit KeyImport(QWidget *parent = 0);
    ~KeyImport();

private:
    Ui::KeyImport *ui;
};

#endif // KEYIMPORT_H
