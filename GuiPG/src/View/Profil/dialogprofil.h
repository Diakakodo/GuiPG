#ifndef DIALOGPROFIL_H
#define DIALOGPROFIL_H

#include <QDialog>
#include "../mainwindow.h"
#include <QAbstractButton>

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
    void deleteSelectProfil();
    void enableAtionButton();

private:
    Ui::DialogProfil *ui;
    QAbstractButton* m_actionButton;
};

#endif // DIALOGPROFIL_H
