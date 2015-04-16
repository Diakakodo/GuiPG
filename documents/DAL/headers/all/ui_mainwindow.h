/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "src/View/gpgtreewidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionConfiguration;
    QAction *actionManuel_utilisateur_de_GuiPG;
    QAction *actionA_propos;
    QAction *actionG_n_rer_une_paire_de_clefs;
    QAction *actionEditeur_de_texte;
    QAction *actionToile_de_confiance_graphique;
    QAction *actionVue_des_commandes_GPG;
    QAction *actionQuitter;
    QAction *actionChanger_de_profile;
    QAction *actionSupprimer_un_profile;
    QAction *actionCreer_un_nouveau_profile;
    QAction *actionProfil;
    QAction *actionImporter;
    QAction *actionCl_s_publiques;
    QAction *actionCl_s_priv_es;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QSplitter *splitter_2;
    QSplitter *splitter;
    GpgTreeWidget *treeWidgetKey;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QTreeWidget *bigBrother;
    QHBoxLayout *horizontalLayout;
    QToolButton *toolButton;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QMenuBar *menubar;
    QMenu *menuFichier;
    QMenu *menuAffichage;
    QMenu *menuClefs;
    QMenu *menuExporter;
    QMenu *menuConfiguration;
    QMenu *menuAide;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1099, 749);
        MainWindow->setAnimated(true);
        actionConfiguration = new QAction(MainWindow);
        actionConfiguration->setObjectName(QStringLiteral("actionConfiguration"));
        actionManuel_utilisateur_de_GuiPG = new QAction(MainWindow);
        actionManuel_utilisateur_de_GuiPG->setObjectName(QStringLiteral("actionManuel_utilisateur_de_GuiPG"));
        actionA_propos = new QAction(MainWindow);
        actionA_propos->setObjectName(QStringLiteral("actionA_propos"));
        actionG_n_rer_une_paire_de_clefs = new QAction(MainWindow);
        actionG_n_rer_une_paire_de_clefs->setObjectName(QStringLiteral("actionG_n_rer_une_paire_de_clefs"));
        actionEditeur_de_texte = new QAction(MainWindow);
        actionEditeur_de_texte->setObjectName(QStringLiteral("actionEditeur_de_texte"));
        actionToile_de_confiance_graphique = new QAction(MainWindow);
        actionToile_de_confiance_graphique->setObjectName(QStringLiteral("actionToile_de_confiance_graphique"));
        actionVue_des_commandes_GPG = new QAction(MainWindow);
        actionVue_des_commandes_GPG->setObjectName(QStringLiteral("actionVue_des_commandes_GPG"));
        actionQuitter = new QAction(MainWindow);
        actionQuitter->setObjectName(QStringLiteral("actionQuitter"));
        actionChanger_de_profile = new QAction(MainWindow);
        actionChanger_de_profile->setObjectName(QStringLiteral("actionChanger_de_profile"));
        actionSupprimer_un_profile = new QAction(MainWindow);
        actionSupprimer_un_profile->setObjectName(QStringLiteral("actionSupprimer_un_profile"));
        actionCreer_un_nouveau_profile = new QAction(MainWindow);
        actionCreer_un_nouveau_profile->setObjectName(QStringLiteral("actionCreer_un_nouveau_profile"));
        actionProfil = new QAction(MainWindow);
        actionProfil->setObjectName(QStringLiteral("actionProfil"));
        actionImporter = new QAction(MainWindow);
        actionImporter->setObjectName(QStringLiteral("actionImporter"));
        actionCl_s_publiques = new QAction(MainWindow);
        actionCl_s_publiques->setObjectName(QStringLiteral("actionCl_s_publiques"));
        actionCl_s_priv_es = new QAction(MainWindow);
        actionCl_s_priv_es->setObjectName(QStringLiteral("actionCl_s_priv_es"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        splitter_2 = new QSplitter(centralwidget);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(splitter_2->sizePolicy().hasHeightForWidth());
        splitter_2->setSizePolicy(sizePolicy);
        splitter_2->setOrientation(Qt::Vertical);
        splitter = new QSplitter(splitter_2);
        splitter->setObjectName(QStringLiteral("splitter"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(100);
        sizePolicy1.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy1);
        splitter->setOrientation(Qt::Horizontal);
        treeWidgetKey = new GpgTreeWidget(splitter);
        treeWidgetKey->setObjectName(QStringLiteral("treeWidgetKey"));
        treeWidgetKey->setSortingEnabled(true);
        treeWidgetKey->setColumnCount(0);
        splitter->addWidget(treeWidgetKey);
        tabWidget = new QTabWidget(splitter);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tabWidget->addTab(tab_2, QString());
        splitter->addWidget(tabWidget);
        splitter_2->addWidget(splitter);
        layoutWidget = new QWidget(splitter_2);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        bigBrother = new QTreeWidget(layoutWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        bigBrother->setHeaderItem(__qtreewidgetitem);
        bigBrother->setObjectName(QStringLiteral("bigBrother"));
        bigBrother->setSelectionBehavior(QAbstractItemView::SelectItems);
        bigBrother->setAnimated(true);
        bigBrother->setHeaderHidden(true);

        verticalLayout->addWidget(bigBrother);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetFixedSize);
        toolButton = new QToolButton(layoutWidget);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        toolButton->setMinimumSize(QSize(15, 15));
        toolButton->setMaximumSize(QSize(15, 15));
        toolButton->setBaseSize(QSize(15, 15));
        toolButton->setCheckable(true);
        toolButton->setArrowType(Qt::UpArrow);

        horizontalLayout->addWidget(toolButton);

        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);
        label->setMaximumSize(QSize(200, 15));
        label->setBaseSize(QSize(0, 15));

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(958, 15, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        splitter_2->addWidget(layoutWidget);

        verticalLayout_2->addWidget(splitter_2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1099, 19));
        menuFichier = new QMenu(menubar);
        menuFichier->setObjectName(QStringLiteral("menuFichier"));
        menuAffichage = new QMenu(menubar);
        menuAffichage->setObjectName(QStringLiteral("menuAffichage"));
        menuClefs = new QMenu(menubar);
        menuClefs->setObjectName(QStringLiteral("menuClefs"));
        menuExporter = new QMenu(menuClefs);
        menuExporter->setObjectName(QStringLiteral("menuExporter"));
        menuConfiguration = new QMenu(menubar);
        menuConfiguration->setObjectName(QStringLiteral("menuConfiguration"));
        menuAide = new QMenu(menubar);
        menuAide->setObjectName(QStringLiteral("menuAide"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuFichier->menuAction());
        menubar->addAction(menuAffichage->menuAction());
        menubar->addAction(menuClefs->menuAction());
        menubar->addAction(menuConfiguration->menuAction());
        menubar->addAction(menuAide->menuAction());
        menuFichier->addAction(actionQuitter);
        menuAffichage->addAction(actionEditeur_de_texte);
        menuAffichage->addAction(actionToile_de_confiance_graphique);
        menuAffichage->addAction(actionVue_des_commandes_GPG);
        menuClefs->addAction(actionG_n_rer_une_paire_de_clefs);
        menuClefs->addAction(actionImporter);
        menuClefs->addAction(menuExporter->menuAction());
        menuExporter->addAction(actionCl_s_publiques);
        menuExporter->addAction(actionCl_s_priv_es);
        menuConfiguration->addAction(actionConfiguration);
        menuConfiguration->addAction(actionProfil);
        menuAide->addAction(actionManuel_utilisateur_de_GuiPG);
        menuAide->addAction(actionA_propos);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "GuiPG", 0));
        actionConfiguration->setText(QApplication::translate("MainWindow", "&Configuration", 0));
        actionManuel_utilisateur_de_GuiPG->setText(QApplication::translate("MainWindow", "&Manuel utilisateur de GuiPG", 0));
        actionA_propos->setText(QApplication::translate("MainWindow", "&A propos", 0));
        actionG_n_rer_une_paire_de_clefs->setText(QApplication::translate("MainWindow", "&G\303\251n\303\251rer une paire de clefs", 0));
        actionEditeur_de_texte->setText(QApplication::translate("MainWindow", "&Editeur de texte", 0));
        actionToile_de_confiance_graphique->setText(QApplication::translate("MainWindow", "&Toile de confiance graphique", 0));
        actionVue_des_commandes_GPG->setText(QApplication::translate("MainWindow", "&Vue des commandes GPG", 0));
        actionQuitter->setText(QApplication::translate("MainWindow", "&Quitter", 0));
        actionChanger_de_profile->setText(QApplication::translate("MainWindow", "&Changer de profile", 0));
        actionSupprimer_un_profile->setText(QApplication::translate("MainWindow", "&Supprimer un profile", 0));
        actionCreer_un_nouveau_profile->setText(QApplication::translate("MainWindow", "Cr\303\251er &un nouveau profile", 0));
        actionProfil->setText(QApplication::translate("MainWindow", "Profil", 0));
        actionImporter->setText(QApplication::translate("MainWindow", "Importer", 0));
        actionCl_s_publiques->setText(QApplication::translate("MainWindow", "Cl\303\251s publiques", 0));
        actionCl_s_priv_es->setText(QApplication::translate("MainWindow", "Cl\303\251s priv\303\251es", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Tab 1", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Tab 2", 0));
        toolButton->setText(QApplication::translate("MainWindow", "...", 0));
        label->setText(QApplication::translate("MainWindow", "Commandes GPG", 0));
        menuFichier->setTitle(QApplication::translate("MainWindow", "Fic&hier", 0));
        menuAffichage->setTitle(QApplication::translate("MainWindow", "Afficha&ge", 0));
        menuClefs->setTitle(QApplication::translate("MainWindow", "C&lefs", 0));
        menuExporter->setTitle(QApplication::translate("MainWindow", "Exporter", 0));
        menuConfiguration->setTitle(QApplication::translate("MainWindow", "Pa&ram\303\250tres", 0));
        menuAide->setTitle(QApplication::translate("MainWindow", "A&ide", 0));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
