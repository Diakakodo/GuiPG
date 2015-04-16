/********************************************************************************
** Form generated from reading UI file 'profilecreation.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROFILECREATION_H
#define UI_PROFILECREATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProfileCreation
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_5;
    QHBoxLayout *horizontalLayout_4;
    QLabel *nameLabel;
    QLineEdit *nameEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *gpgPathLabel;
    QLineEdit *gpgPathEdit;
    QPushButton *gpgPathButton;
    QHBoxLayout *horizontalLayout_3;
    QLabel *storagePathLabel;
    QLineEdit *storagePathEdit;
    QPushButton *storagePathButton;
    QLabel *warningLabel;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *cancelButton;
    QPushButton *acceptButton;

    void setupUi(QWidget *ProfileCreation)
    {
        if (ProfileCreation->objectName().isEmpty())
            ProfileCreation->setObjectName(QStringLiteral("ProfileCreation"));
        ProfileCreation->resize(400, 300);
        verticalLayout_2 = new QVBoxLayout(ProfileCreation);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));

        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        nameLabel = new QLabel(ProfileCreation);
        nameLabel->setObjectName(QStringLiteral("nameLabel"));
        nameLabel->setTextFormat(Qt::PlainText);
        nameLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(nameLabel);

        nameEdit = new QLineEdit(ProfileCreation);
        nameEdit->setObjectName(QStringLiteral("nameEdit"));

        horizontalLayout_4->addWidget(nameEdit);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        gpgPathLabel = new QLabel(ProfileCreation);
        gpgPathLabel->setObjectName(QStringLiteral("gpgPathLabel"));

        horizontalLayout_2->addWidget(gpgPathLabel);

        gpgPathEdit = new QLineEdit(ProfileCreation);
        gpgPathEdit->setObjectName(QStringLiteral("gpgPathEdit"));

        horizontalLayout_2->addWidget(gpgPathEdit);

        gpgPathButton = new QPushButton(ProfileCreation);
        gpgPathButton->setObjectName(QStringLiteral("gpgPathButton"));

        horizontalLayout_2->addWidget(gpgPathButton);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        storagePathLabel = new QLabel(ProfileCreation);
        storagePathLabel->setObjectName(QStringLiteral("storagePathLabel"));

        horizontalLayout_3->addWidget(storagePathLabel);

        storagePathEdit = new QLineEdit(ProfileCreation);
        storagePathEdit->setObjectName(QStringLiteral("storagePathEdit"));

        horizontalLayout_3->addWidget(storagePathEdit);

        storagePathButton = new QPushButton(ProfileCreation);
        storagePathButton->setObjectName(QStringLiteral("storagePathButton"));

        horizontalLayout_3->addWidget(storagePathButton);


        verticalLayout->addLayout(horizontalLayout_3);

        warningLabel = new QLabel(ProfileCreation);
        warningLabel->setObjectName(QStringLiteral("warningLabel"));
        QPalette palette;
        QBrush brush(QColor(233, 18, 18, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush1(QColor(133, 133, 133, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        warningLabel->setPalette(palette);

        verticalLayout->addWidget(warningLabel);


        verticalLayout_2->addLayout(verticalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        cancelButton = new QPushButton(ProfileCreation);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        horizontalLayout->addWidget(cancelButton);

        acceptButton = new QPushButton(ProfileCreation);
        acceptButton->setObjectName(QStringLiteral("acceptButton"));

        horizontalLayout->addWidget(acceptButton);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(ProfileCreation);

        QMetaObject::connectSlotsByName(ProfileCreation);
    } // setupUi

    void retranslateUi(QWidget *ProfileCreation)
    {
        ProfileCreation->setWindowTitle(QApplication::translate("ProfileCreation", "Cr\303\251er un nouveau profil", 0));
        nameLabel->setText(QApplication::translate("ProfileCreation", "Nom du profil", 0));
        gpgPathLabel->setText(QApplication::translate("ProfileCreation", "Chemin vers gpg ", 0));
        gpgPathButton->setText(QApplication::translate("ProfileCreation", "Parcourir", 0));
        storagePathLabel->setText(QApplication::translate("ProfileCreation", "Stockage du profil", 0));
        storagePathButton->setText(QApplication::translate("ProfileCreation", "Parcourir", 0));
        warningLabel->setText(QString());
        cancelButton->setText(QApplication::translate("ProfileCreation", "Annuler", 0));
        acceptButton->setText(QApplication::translate("ProfileCreation", "Cr\303\251er", 0));
    } // retranslateUi

};

namespace Ui {
    class ProfileCreation: public Ui_ProfileCreation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROFILECREATION_H
