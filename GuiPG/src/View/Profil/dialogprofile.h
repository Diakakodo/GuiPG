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
    explicit DialogProfile(MainWindow *parent = 0);
    ~DialogProfile();
    void fillTableWidget();

signals:
    void selectProfile(unsigned id);

public slots:
    void loadSelectProfile();
    void deleteSelectProfile();
    void enableAtionButton();

private:
    Ui::DialogProfile *ui;
    MainWindow* m_parent;
    QAbstractButton* m_loadButton;
    QAbstractButton* m_createButton;
    QAbstractButton* m_deleteButton;
    QAbstractButton* m_setDefaultButton;
};

#endif // DIALOGPROFILE_H
