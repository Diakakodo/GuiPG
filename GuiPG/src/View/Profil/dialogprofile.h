#ifndef DIALOGPROFILE_H
#define DIALOGPROFILE_H

#include <QDialog>
#include "../mainwindow.h"
#include <QAbstractButton>

namespace Ui {
class DialogProfile;
}

class DialogProfile : public QDialog
{
    Q_OBJECT

public:
    enum DIALOG_TYPE {SELECT, DELETE};
    explicit DialogProfile(DIALOG_TYPE dialog_type, MainWindow *parent = 0);
    ~DialogProfile();

signals:
    void selectProfile(unsigned id);

public slots:
    void loadSelectProfile();
    void deleteSelectProfile();
    void enableAtionButton();

private:
    Ui::DialogProfile *ui;
    QAbstractButton* m_actionButton;
};

#endif // DIALOGPROFILE_H
