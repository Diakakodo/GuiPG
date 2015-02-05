#ifndef DIALOGPROFIL_H
#define DIALOGPROFIL_H

#include <QDialog>
#include "../mainwindow.h"

namespace Ui {
class DialogProfil;
}

class DialogProfil : public QDialog
{
    Q_OBJECT

public:
    enum DIALOG_TYPE {SELECT, DELETE};
    explicit DialogProfil(DIALOG_TYPE dialog_type, MainWindow *parent = 0);
    ~DialogProfil();

signals:
    void selectProfil(uint* id);

public slots:
    void loadSelectProfil();

private:
    Ui::DialogProfil *ui;
};

#endif // DIALOGPROFIL_H
