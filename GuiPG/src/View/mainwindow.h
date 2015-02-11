#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../Profile/profile.h"
#include "../Configuration/configuration.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit MainWindow(Profile* p, Configuration* config);
        ~MainWindow();
        Profile* getProfil() const;
        Configuration* getConfiguration() const;

    public slots:
        void setGpgCommandsVisible(bool b);
        void showDialogSelectProfil();
        void showDialogDeleteProfil();
        void changeProfil(uint* idProfil);
         void showDialogConfiguration();

private slots:
        void on_actionG_n_rer_une_paire_de_clefs_triggered();

        void on_actionCreer_un_nouveau_profile_triggered();

private:
        Ui::MainWindow* ui;
        Configuration* m_config;
        Profile* m_profil;
};

#endif // MAINWINDOW_H
