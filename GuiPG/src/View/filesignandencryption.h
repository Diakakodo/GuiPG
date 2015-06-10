#ifndef FILESIGNANDENCRYPTION_H
#define FILESIGNANDENCRYPTION_H

#include <QDialog>

namespace Ui {
class FileSignAndEncryption;
}

class FileSignAndEncryption : public QDialog
{
    Q_OBJECT

public:
    explicit FileSignAndEncryption(QWidget *parent = 0);
    ~FileSignAndEncryption();

private:
    Ui::FileSignAndEncryption *ui;
};

#endif // FILESIGNANDENCRYPTION_H
