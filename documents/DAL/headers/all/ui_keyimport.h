/********************************************************************************
** Form generated from reading UI file 'keyimport.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KEYIMPORT_H
#define UI_KEYIMPORT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_KeyImport
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *fileRadioButton;
    QLineEdit *pathEdit;
    QPushButton *browseButton;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *keyServerButton;
    QLineEdit *keyIdEdit;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_4;
    QLabel *warningLabel;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *cancelButton;
    QPushButton *importButton;

    void setupUi(QWidget *KeyImport)
    {
        if (KeyImport->objectName().isEmpty())
            KeyImport->setObjectName(QStringLiteral("KeyImport"));
        KeyImport->resize(400, 300);
        verticalLayoutWidget = new QWidget(KeyImport);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 381, 231));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        fileRadioButton = new QRadioButton(verticalLayoutWidget);
        fileRadioButton->setObjectName(QStringLiteral("fileRadioButton"));

        horizontalLayout_2->addWidget(fileRadioButton);

        pathEdit = new QLineEdit(verticalLayoutWidget);
        pathEdit->setObjectName(QStringLiteral("pathEdit"));

        horizontalLayout_2->addWidget(pathEdit);

        browseButton = new QPushButton(verticalLayoutWidget);
        browseButton->setObjectName(QStringLiteral("browseButton"));

        horizontalLayout_2->addWidget(browseButton);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        keyServerButton = new QRadioButton(verticalLayoutWidget);
        keyServerButton->setObjectName(QStringLiteral("keyServerButton"));

        horizontalLayout_3->addWidget(keyServerButton);

        keyIdEdit = new QLineEdit(verticalLayoutWidget);
        keyIdEdit->setObjectName(QStringLiteral("keyIdEdit"));

        horizontalLayout_3->addWidget(keyIdEdit);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        warningLabel = new QLabel(verticalLayoutWidget);
        warningLabel->setObjectName(QStringLiteral("warningLabel"));
        QPalette palette;
        QBrush brush(QColor(203, 11, 11, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush1(QColor(133, 133, 133, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        warningLabel->setPalette(palette);

        horizontalLayout_4->addWidget(warningLabel);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayoutWidget = new QWidget(KeyImport);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 250, 381, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        cancelButton = new QPushButton(horizontalLayoutWidget);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        horizontalLayout->addWidget(cancelButton);

        importButton = new QPushButton(horizontalLayoutWidget);
        importButton->setObjectName(QStringLiteral("importButton"));

        horizontalLayout->addWidget(importButton);


        retranslateUi(KeyImport);

        QMetaObject::connectSlotsByName(KeyImport);
    } // setupUi

    void retranslateUi(QWidget *KeyImport)
    {
        KeyImport->setWindowTitle(QApplication::translate("KeyImport", "Importation de cl\303\251s", 0));
        fileRadioButton->setText(QApplication::translate("KeyImport", "Depuis un fichier :", 0));
        browseButton->setText(QApplication::translate("KeyImport", "Parcourir", 0));
        keyServerButton->setText(QApplication::translate("KeyImport", "Depuis un serveur de cl\303\251s :", 0));
        warningLabel->setText(QString());
        cancelButton->setText(QApplication::translate("KeyImport", "Annuler", 0));
        importButton->setText(QApplication::translate("KeyImport", "Importer", 0));
    } // retranslateUi

};

namespace Ui {
    class KeyImport: public Ui_KeyImport {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KEYIMPORT_H
