/********************************************************************************
** Form generated from reading UI file 'keycreation.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KEYCREATION_H
#define UI_KEYCREATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_KeyCreation
{
public:
    QLabel *label;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;
    QSlider *horizontalSlider;
    QLabel *label_2;
    QLabel *label_3;
    QComboBox *comboBox;
    QSpinBox *spinBox;
    QLabel *label_4;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_3;
    QSpinBox *spinBox_2;
    QLabel *label_5;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLineEdit *lineEdit_2;
    QLabel *label_8;
    QLineEdit *lineEdit_4;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QTextBrowser *dataBrowser;

    void setupUi(QDialog *KeyCreation)
    {
        if (KeyCreation->objectName().isEmpty())
            KeyCreation->setObjectName(QStringLiteral("KeyCreation"));
        KeyCreation->resize(489, 492);
        label = new QLabel(KeyCreation);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 0, 71, 16));
        radioButton = new QRadioButton(KeyCreation);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(20, 20, 102, 22));
        radioButton->setChecked(true);
        radioButton_2 = new QRadioButton(KeyCreation);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setGeometry(QRect(20, 50, 111, 22));
        radioButton_3 = new QRadioButton(KeyCreation);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));
        radioButton_3->setGeometry(QRect(20, 80, 161, 22));
        radioButton_4 = new QRadioButton(KeyCreation);
        radioButton_4->setObjectName(QStringLiteral("radioButton_4"));
        radioButton_4->setGeometry(QRect(20, 110, 151, 22));
        horizontalSlider = new QSlider(KeyCreation);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(20, 170, 131, 21));
        horizontalSlider->setToolTipDuration(5);
        horizontalSlider->setAutoFillBackground(false);
        horizontalSlider->setMinimum(1024);
        horizontalSlider->setMaximum(4096);
        horizontalSlider->setSingleStep(1024);
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider->setTickPosition(QSlider::TicksBelow);
        horizontalSlider->setTickInterval(1024);
        label_2 = new QLabel(KeyCreation);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 150, 71, 17));
        label_3 = new QLabel(KeyCreation);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 210, 55, 17));
        comboBox = new QComboBox(KeyCreation);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setEnabled(true);
        comboBox->setGeometry(QRect(70, 230, 91, 27));
        spinBox = new QSpinBox(KeyCreation);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setEnabled(true);
        spinBox->setGeometry(QRect(20, 230, 41, 27));
        spinBox->setMaximum(99);
        label_4 = new QLabel(KeyCreation);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(230, 0, 55, 17));
        label_6 = new QLabel(KeyCreation);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(230, 70, 55, 17));
        label_7 = new QLabel(KeyCreation);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(230, 140, 91, 17));
        lineEdit = new QLineEdit(KeyCreation);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(230, 20, 231, 27));
        lineEdit_3 = new QLineEdit(KeyCreation);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(230, 90, 231, 27));
        spinBox_2 = new QSpinBox(KeyCreation);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setGeometry(QRect(160, 170, 51, 27));
        spinBox_2->setMinimum(1024);
        spinBox_2->setMaximum(4096);
        spinBox_2->setValue(1024);
        label_5 = new QLabel(KeyCreation);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 260, 441, 41));
        QPalette palette;
        QBrush brush(QColor(245, 18, 18, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(188, 183, 183, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(255, 255, 255, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(221, 219, 219, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(94, 91, 91, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(125, 122, 122, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        QBrush brush6(QColor(0, 0, 0, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush6);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush6);
        palette.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush6);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush3);
        QBrush brush7(QColor(255, 255, 220, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush6);
        label_5->setPalette(palette);
        pushButton = new QPushButton(KeyCreation);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(140, 450, 85, 27));
        pushButton_2 = new QPushButton(KeyCreation);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(230, 450, 85, 27));
        lineEdit_2 = new QLineEdit(KeyCreation);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(230, 160, 231, 31));
        label_8 = new QLabel(KeyCreation);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(230, 210, 111, 17));
        lineEdit_4 = new QLineEdit(KeyCreation);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(230, 230, 231, 27));
        lineEdit_4->setEchoMode(QLineEdit::Password);
        verticalLayoutWidget = new QWidget(KeyCreation);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 311, 491, 131));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        dataBrowser = new QTextBrowser(verticalLayoutWidget);
        dataBrowser->setObjectName(QStringLiteral("dataBrowser"));
        dataBrowser->setAutoFillBackground(false);
        dataBrowser->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        verticalLayout->addWidget(dataBrowser);


        retranslateUi(KeyCreation);

        comboBox->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(KeyCreation);
    } // setupUi

    void retranslateUi(QDialog *KeyCreation)
    {
        KeyCreation->setWindowTitle(QApplication::translate("KeyCreation", "Cr\303\251ation de cl\303\251", 0));
        label->setText(QApplication::translate("KeyCreation", "QStringe", 0));
        radioButton->setText(QApplication::translate("KeyCreation", "RSA - RSA", 0));
        radioButton_2->setText(QApplication::translate("KeyCreation", "DSA - Elgamal", 0));
        radioButton_3->setText(QApplication::translate("KeyCreation", "DSA (signature seule)", 0));
        radioButton_4->setText(QApplication::translate("KeyCreation", "RSA (signature seule)", 0));
#ifndef QT_NO_TOOLTIP
        horizontalSlider->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        label_2->setText(QApplication::translate("KeyCreation", "Taille", 0));
        label_3->setText(QApplication::translate("KeyCreation", "Dur\303\251e", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("KeyCreation", "Illimit\303\251e", 0)
         << QApplication::translate("KeyCreation", "Jour(s)", 0)
         << QApplication::translate("KeyCreation", "Semaine(s)", 0)
         << QApplication::translate("KeyCreation", "Mois", 0)
         << QApplication::translate("KeyCreation", "Ann\303\251e(s)", 0)
        );
        comboBox->setCurrentText(QApplication::translate("KeyCreation", "Jour(s)", 0));
        label_4->setText(QApplication::translate("KeyCreation", "Nom", 0));
        label_6->setText(QApplication::translate("KeyCreation", "Email", 0));
        label_7->setText(QApplication::translate("KeyCreation", "Commentaire", 0));
        label_5->setText(QString());
        pushButton->setText(QApplication::translate("KeyCreation", "Annuler", 0));
        pushButton_2->setText(QApplication::translate("KeyCreation", "G\303\251n\303\251rer", 0));
        label_8->setText(QApplication::translate("KeyCreation", "Phrase de passe", 0));
    } // retranslateUi

};

namespace Ui {
    class KeyCreation: public Ui_KeyCreation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KEYCREATION_H
