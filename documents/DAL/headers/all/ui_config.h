/********************************************************************************
** Form generated from reading UI file 'config.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIG_H
#define UI_CONFIG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_config
{
public:
    QLabel *label_3;
    QLabel *label_5;
    QTextEdit *textEdit;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QLineEdit *lineEdit_3;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;

    void setupUi(QDialog *config)
    {
        if (config->objectName().isEmpty())
            config->setObjectName(QStringLiteral("config"));
        config->resize(682, 454);
        label_3 = new QLabel(config);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(50, 190, 151, 31));
        label_5 = new QLabel(config);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(50, 60, 261, 31));
        textEdit = new QTextEdit(config);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(53, 10, 611, 51));
        layoutWidget = new QWidget(config);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(50, 250, 501, 29));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_3->addWidget(label_4);

        lineEdit_3 = new QLineEdit(layoutWidget);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));

        horizontalLayout_3->addWidget(lineEdit_3);

        layoutWidget1 = new QWidget(config);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 400, 271, 29));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        pushButton_2 = new QPushButton(layoutWidget1);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_4->addWidget(pushButton_2);

        pushButton_3 = new QPushButton(layoutWidget1);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        horizontalLayout_4->addWidget(pushButton_3);

        layoutWidget2 = new QWidget(config);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(50, 139, 591, 29));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget2);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        lineEdit = new QLineEdit(layoutWidget2);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout_2->addWidget(lineEdit);

        layoutWidget3 = new QWidget(config);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(50, 100, 591, 29));
        horizontalLayout = new QHBoxLayout(layoutWidget3);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget3);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEdit_2 = new QLineEdit(layoutWidget3);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        horizontalLayout->addWidget(lineEdit_2);

        pushButton = new QPushButton(layoutWidget3);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_4 = new QPushButton(config);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(460, 400, 80, 23));
        pushButton_5 = new QPushButton(config);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(570, 400, 80, 23));

        retranslateUi(config);

        QMetaObject::connectSlotsByName(config);
    } // setupUi

    void retranslateUi(QDialog *config)
    {
        config->setWindowTitle(QApplication::translate("config", "Dialog", 0));
        label_3->setText(QApplication::translate("config", "Binaire de GnuPG", 0));
        label_5->setText(QApplication::translate("config", "Repertoire GnuPG", 0));
        textEdit->setHtml(QApplication::translate("config", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Sans Serif'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Ubuntu'; font-size:14pt;\">Parametre GnuPG </span></p></body></html>", 0));
        label_4->setText(QApplication::translate("config", "Chemin du programme", 0));
        pushButton_2->setText(QApplication::translate("config", "Aide", 0));
        pushButton_3->setText(QApplication::translate("config", "Defaut", 0));
        label_2->setText(QApplication::translate("config", "Fichier de configuration", 0));
        lineEdit->setText(QApplication::translate("config", "gpg.config", 0));
        label->setText(QApplication::translate("config", "Repertoire ", 0));
        lineEdit_2->setText(QApplication::translate("config", "/home/user/.gnupg", 0));
        pushButton->setText(QApplication::translate("config", "Charger", 0));
        pushButton_4->setText(QApplication::translate("config", "Cancel", 0));
        pushButton_5->setText(QApplication::translate("config", "OK", 0));
    } // retranslateUi

};

namespace Ui {
    class config: public Ui_config {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIG_H
