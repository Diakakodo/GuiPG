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

private slots:
    void on_tableWidgetProfil_activated(const QModelIndex &index);

private:
    Ui::DialogProfil *ui;
};

#endif // DIALOGPROFIL_H
