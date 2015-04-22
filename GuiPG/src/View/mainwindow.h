#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../Profile/profile.h"
#include "../Configuration/configuration.h"
#include "../Model/mainwindowmodel.h"
#include <QTreeWidget>
#include "../Keys/subseckey.h"
#include "../GPG/gpgmanager.h"

#define ICON_BIG_BROTHER_SIZE QSize(16, 16)
#define ICON_BIG_BROTHER_LOAD_PATH "Icones/chargement.gif"
#define DATE_BIG_BROTHER_FORMAT "hh:mm:ss.z"

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
        MainWindowModel* getModel() const;
        void refreshKeys();


    public slots:
        void buildTree();
        void setGpgCommandsVisible(bool b);
        void showDialogProfile();
        void changeProfil(unsigned profileId);
        void updateBigBrother(GPGManager* gpg, bool fisrt, int id);
        void onCustomContextMenuRequested(const QPoint& pos);
        int getNbCmd();
        void setNbCmd(int nb);
        void addTab(QString name, QString content);

private slots:
        void on_actionG_n_rer_une_paire_de_clefs_triggered();

        void on_actionImporter_triggered();

        void on_actionCl_s_publiques_triggered();

        void on_actionCl_s_priv_es_triggered();

        void on_action_GenKey_Toolbar_triggered();

        void on_action_Refresh_Toolbar_triggered();

        void on_action_Import_Toolbar_triggered();

        void on_actionChiffrer_un_fichier_triggered();

        void on_actionDechiffrer_Verifier_un_fichier_triggered();

        void on_tabWidget_tabCloseRequested(int index);

    protected:
     void closeEvent(QCloseEvent *event);

private:
        void setItemColor(QTreeWidgetItem* item, const QColor& color);

        Ui::MainWindow* ui;
        MainWindowModel* m_model;
        int currentBigBrotherHeight;
        int m_bigBrotherCmdMaxWidht = 0;
        int NB_CMD = 0;

};

#endif // MAINWINDOW_H

