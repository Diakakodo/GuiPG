#ifndef DIALOGPROFIL_H
#define DIALOGPROFIL_H

#include <QDialog>

namespace Ui {
class DialogProfil;
}

class DialogProfil : public QDialog
{
    Q_OBJECT

public:
    enum DIALOG_TYPE {SELECT, DELETE};
    explicit DialogProfil(DIALOG_TYPE dialog_type, QWidget *parent = 0);
    ~DialogProfil();

private:
    Ui::DialogProfil *ui;
};

#endif // DIALOGPROFIL_H
