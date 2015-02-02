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

    private:
        Ui::MainWindow* ui;
        Configuration* m_config;
        Profile* m_profil;
};

#endif // MAINWINDOW_H
