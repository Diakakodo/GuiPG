/********************************************************************************
** Form generated from reading UI file 'dialogprofile.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGPROFILE_H
#define UI_DIALOGPROFILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogProfile
{
public:
    QHBoxLayout *horizontalLayout;
    QDialogButtonBox *buttonBox;
    QTableWidget *tableWidgetProfil;

    void setupUi(QDialog *DialogProfile)
    {
        if (DialogProfile->objectName().isEmpty())
            DialogProfile->setObjectName(QStringLiteral("DialogProfile"));
        DialogProfile->resize(462, 272);
        DialogProfile->setModal(true);
        horizontalLayout = new QHBoxLayout(DialogProfile);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        buttonBox = new QDialogButtonBox(DialogProfile);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel);
        buttonBox->setCenterButtons(false);

        horizontalLayout->addWidget(buttonBox);

        tableWidgetProfil = new QTableWidget(DialogProfile);
        tableWidgetProfil->setObjectName(QStringLiteral("tableWidgetProfil"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableWidgetProfil->sizePolicy().hasHeightForWidth());
        tableWidgetProfil->setSizePolicy(sizePolicy);
        tableWidgetProfil->setAlternatingRowColors(true);
        tableWidgetProfil->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidgetProfil->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidgetProfil->setSortingEnabled(true);
        tableWidgetProfil->setColumnCount(0);
        tableWidgetProfil->horizontalHeader()->setStretchLastSection(true);
        tableWidgetProfil->verticalHeader()->setVisible(false);

        horizontalLayout->addWidget(tableWidgetProfil);


        retranslateUi(DialogProfile);
        QObject::connect(buttonBox, SIGNAL(accepted()), DialogProfile, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), DialogProfile, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogProfile);
    } // setupUi

    void retranslateUi(QDialog *DialogProfile)
    {
        DialogProfile->setWindowTitle(QApplication::translate("DialogProfile", "Charger ou supprimer un profile", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogProfile: public Ui_DialogProfile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGPROFILE_H
