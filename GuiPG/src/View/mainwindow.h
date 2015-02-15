#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../Profile/profile.h"
#include "../Configuration/configuration.h"
#include "../Model/mainwindowmodel.h"
class MainWindowModel;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit MainWindow(MainWindowModel* model);
        ~MainWindow();
        Profile* getProfil() const;
        Configuration* getConfiguration() const;

    public slots:
        void setGpgCommandsVisible(bool b);
        void showDialogSelectProfile();
        void showDialogDeleteProfil();
        void changeProfil(unsigned profileId);
        void showDialogConfiguration();

private slots:
        void on_actionG_n_rer_une_paire_de_clefs_triggered();
        void on_actionCreer_un_nouveau_profile_triggered();

protected:
     void closeEvent(QCloseEvent *event);

private:
        Ui::MainWindow* ui;
        MainWindowModel* m_model;
};

#endif // MAINWINDOW_H
