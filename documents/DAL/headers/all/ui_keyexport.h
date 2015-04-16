/********************************************************************************
** Form generated from reading UI file 'keyexport.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KEYEXPORT_H
#define UI_KEYEXPORT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
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

class Ui_KeyExport
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_4;
    QRadioButton *keyServerRadioButton;
    QHBoxLayout *horizontalLayout_3;
    QComboBox *keyServerList;
    QHBoxLayout *horizontalLayout;
    QRadioButton *fileRadioButton;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *pathEdit;
    QPushButton *browseButton;
    QHBoxLayout *horizontalLayout_6;
    QLabel *warningLabel;
    QWidget *horizontalLayoutWidget_5;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer;
    QPushButton *cancelButton;
    QPushButton *exportButton;

    void setupUi(QWidget *KeyExport)
    {
        if (KeyExport->objectName().isEmpty())
            KeyExport->setObjectName(QStringLiteral("KeyExport"));
        KeyExport->resize(400, 300);
        verticalLayoutWidget = new QWidget(KeyExport);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 10, 381, 231));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        keyServerRadioButton = new QRadioButton(verticalLayoutWidget);
        keyServerRadioButton->setObjectName(QStringLiteral("keyServerRadioButton"));

        horizontalLayout_4->addWidget(keyServerRadioButton);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        keyServerList = new QComboBox(verticalLayoutWidget);
        keyServerList->setObjectName(QStringLiteral("keyServerList"));
        keyServerList->setEditable(true);

        horizontalLayout_3->addWidget(keyServerList);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        fileRadioButton = new QRadioButton(verticalLayoutWidget);
        fileRadioButton->setObjectName(QStringLiteral("fileRadioButton"));

        horizontalLayout->addWidget(fileRadioButton);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pathEdit = new QLineEdit(verticalLayoutWidget);
        pathEdit->setObjectName(QStringLiteral("pathEdit"));

        horizontalLayout_2->addWidget(pathEdit);

        browseButton = new QPushButton(verticalLayoutWidget);
        browseButton->setObjectName(QStringLiteral("browseButton"));

        horizontalLayout_2->addWidget(browseButton);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        warningLabel = new QLabel(verticalLayoutWidget);
        warningLabel->setObjectName(QStringLiteral("warningLabel"));
        QPalette palette;
        QBrush brush(QColor(217, 42, 42, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush1(QColor(133, 133, 133, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        warningLabel->setPalette(palette);

        horizontalLayout_6->addWidget(warningLabel);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayoutWidget_5 = new QWidget(KeyExport);
        horizontalLayoutWidget_5->setObjectName(QStringLiteral("horizontalLayoutWidget_5"));
        horizontalLayoutWidget_5->setGeometry(QRect(10, 250, 381, 41));
        horizontalLayout_5 = new QHBoxLayout(horizontalLayoutWidget_5);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        cancelButton = new QPushButton(horizontalLayoutWidget_5);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        horizontalLayout_5->addWidget(cancelButton);

        exportButton = new QPushButton(horizontalLayoutWidget_5);
        exportButton->setObjectName(QStringLiteral("exportButton"));

        horizontalLayout_5->addWidget(exportButton);

        verticalLayoutWidget->raise();
        horizontalLayoutWidget_5->raise();

        retranslateUi(KeyExport);

        QMetaObject::connectSlotsByName(KeyExport);
    } // setupUi

    void retranslateUi(QWidget *KeyExport)
    {
        KeyExport->setWindowTitle(QApplication::translate("KeyExport", "Export de cl\303\251s", 0));
        keyServerRadioButton->setText(QApplication::translate("KeyExport", "Vers un serveur de cl\303\251s :", 0));
        keyServerList->clear();
        keyServerList->insertItems(0, QStringList()
         << QApplication::translate("KeyExport", "http://keys.gnupg.net", 0)
         << QApplication::translate("KeyExport", "http://keyserver.ubuntu.com", 0)
         << QApplication::translate("KeyExport", "hkp://subkeys.pgp.net", 0)
         << QApplication::translate("KeyExport", "hkp://pgp.mit.edu", 0)
        );
        fileRadioButton->setText(QApplication::translate("KeyExport", "Vers un fichier :", 0));
        browseButton->setText(QApplication::translate("KeyExport", "Parcourir", 0));
        warningLabel->setText(QString());
        cancelButton->setText(QApplication::translate("KeyExport", "Annuler", 0));
        exportButton->setText(QApplication::translate("KeyExport", "Exporter", 0));
    } // retranslateUi

};

namespace Ui {
    class KeyExport: public Ui_KeyExport {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KEYEXPORT_H
