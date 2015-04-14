#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../Profile/profile.h"
#include "../Configuration/configuration.h"
#include "../Model/mainwindowmodel.h"
#include <QTreeWidget>
#include "../Keys/subseckey.h"

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
        void showManuel();
        void showDialogConfiguration();
        void updateBigBrother(QString cmd, QString output);

private slots:
        void on_actionG_n_rer_une_paire_de_clefs_triggered();

        void on_actionImporter_triggered();

        void on_actionCl_s_publiques_triggered();

        void on_actionCl_s_priv_es_triggered();

protected:
     void closeEvent(QCloseEvent *event);

private:
        QTreeWidgetItem* createKeyItem(Key* k, QTreeWidget* tree = nullptr);
        void createSignatureItem(Key* k, QTreeWidgetItem* item);
        void setItemColor(QTreeWidgetItem* item, const QColor& color);

        Ui::MainWindow* ui;
        MainWindowModel* m_model;
};

#endif // MAINWINDOW_H

