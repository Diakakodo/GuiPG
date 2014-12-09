/********************************************************************************
** Form generated from reading UI file 'maquette.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAQUETTE_H
#define UI_MAQUETTE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Maquette
{
public:
    QAction *action_propos;
    QAction *actionImport_cl;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_3;
    QSplitter *splitter_2;
    QTreeView *treeView;
    QWidget *widget;
    QVBoxLayout *verticalLayout_4;
    QSplitter *splitter;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_5;
    QPlainTextEdit *plainTextEdit;
    QWidget *tab_2;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QTextBrowser *textBrowser;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QMenuBar *menubar;
    QMenu *menuFichier;
    QMenu *menuAide;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *Maquette)
    {
        if (Maquette->objectName().isEmpty())
            Maquette->setObjectName(QStringLiteral("Maquette"));
        Maquette->resize(800, 600);
        action_propos = new QAction(Maquette);
        action_propos->setObjectName(QStringLiteral("action_propos"));
        actionImport_cl = new QAction(Maquette);
        actionImport_cl->setObjectName(QStringLiteral("actionImport_cl"));
        centralwidget = new QWidget(Maquette);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout_3 = new QVBoxLayout(centralwidget);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        splitter_2 = new QSplitter(centralwidget);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        treeView = new QTreeView(splitter_2);
        treeView->setObjectName(QStringLiteral("treeView"));
        splitter_2->addWidget(treeView);
        widget = new QWidget(splitter_2);
        widget->setObjectName(QStringLiteral("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        verticalLayout_4 = new QVBoxLayout(widget);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        splitter = new QSplitter(widget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Vertical);
        splitter->setOpaqueResize(true);
        splitter->setChildrenCollapsible(false);
        tabWidget = new QTabWidget(splitter);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy1);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayout_5 = new QVBoxLayout(tab);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        plainTextEdit = new QPlainTextEdit(tab);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));

        verticalLayout_5->addWidget(plainTextEdit);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tabWidget->addTab(tab_2, QString());
        splitter->addWidget(tabWidget);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        textBrowser = new QTextBrowser(layoutWidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        verticalLayout_2->addWidget(textBrowser);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setCheckable(true);
        pushButton->setChecked(true);

        horizontalLayout_2->addWidget(pushButton);


        verticalLayout_2->addLayout(horizontalLayout_2);

        splitter->addWidget(layoutWidget);

        verticalLayout_4->addWidget(splitter);

        splitter_2->addWidget(widget);

        verticalLayout_3->addWidget(splitter_2);

        Maquette->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Maquette);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 19));
        menuFichier = new QMenu(menubar);
        menuFichier->setObjectName(QStringLiteral("menuFichier"));
        menuAide = new QMenu(menubar);
        menuAide->setObjectName(QStringLiteral("menuAide"));
        Maquette->setMenuBar(menubar);
        statusbar = new QStatusBar(Maquette);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        Maquette->setStatusBar(statusbar);
        toolBar = new QToolBar(Maquette);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        Maquette->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menuFichier->menuAction());
        menubar->addAction(menuAide->menuAction());
        menuFichier->addAction(actionImport_cl);
        menuAide->addAction(action_propos);
        toolBar->addAction(actionImport_cl);

        retranslateUi(Maquette);
        QObject::connect(pushButton, SIGNAL(toggled(bool)), textBrowser, SLOT(setVisible(bool)));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Maquette);
    } // setupUi

    void retranslateUi(QMainWindow *Maquette)
    {
        Maquette->setWindowTitle(QApplication::translate("Maquette", "MainWindow", 0));
        action_propos->setText(QApplication::translate("Maquette", "\303\200 propos ...", 0));
        actionImport_cl->setText(QApplication::translate("Maquette", "Import cl\303\251", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Maquette", "Editeur", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("Maquette", "Toile de confiance", 0));
        pushButton->setText(QApplication::translate("Maquette", "PushButton", 0));
        menuFichier->setTitle(QApplication::translate("Maquette", "Fichier", 0));
        menuAide->setTitle(QApplication::translate("Maquette", "Aide", 0));
        toolBar->setWindowTitle(QApplication::translate("Maquette", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class Maquette: public Ui_Maquette {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAQUETTE_H
