/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLineEdit *leipAddress;
    QLineEdit *leport;
    QPushButton *connectBtn;
    QTextBrowser *textReceive;
    QListWidget *listWidget;
    QPlainTextEdit *textSend;
    QPushButton *sendBtn;
    QLabel *label_2;
    QLabel *label;
    QLineEdit *leport_2;
    QLabel *label_3;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(788, 424);
        leipAddress = new QLineEdit(Widget);
        leipAddress->setObjectName(QString::fromUtf8("leipAddress"));
        leipAddress->setGeometry(QRect(90, 20, 151, 21));
        leport = new QLineEdit(Widget);
        leport->setObjectName(QString::fromUtf8("leport"));
        leport->setGeometry(QRect(350, 20, 81, 21));
        connectBtn = new QPushButton(Widget);
        connectBtn->setObjectName(QString::fromUtf8("connectBtn"));
        connectBtn->setGeometry(QRect(680, 15, 81, 28));
        textReceive = new QTextBrowser(Widget);
        textReceive->setObjectName(QString::fromUtf8("textReceive"));
        textReceive->setGeometry(QRect(20, 60, 541, 301));
        listWidget = new QListWidget(Widget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(590, 60, 171, 341));
        textSend = new QPlainTextEdit(Widget);
        textSend->setObjectName(QString::fromUtf8("textSend"));
        textSend->setGeometry(QRect(20, 380, 441, 31));
        sendBtn = new QPushButton(Widget);
        sendBtn->setObjectName(QString::fromUtf8("sendBtn"));
        sendBtn->setGeometry(QRect(480, 380, 81, 28));
        label_2 = new QLabel(Widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 20, 72, 15));
        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(280, 20, 72, 15));
        leport_2 = new QLineEdit(Widget);
        leport_2->setObjectName(QString::fromUtf8("leport_2"));
        leport_2->setGeometry(QRect(550, 20, 81, 21));
        label_3 = new QLabel(Widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(480, 20, 72, 15));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "TCP\345\256\242\346\210\267\347\253\257", nullptr));
        leipAddress->setText(QApplication::translate("Widget", "10.148.41.88", nullptr));
        leport->setText(QApplication::translate("Widget", "8888", nullptr));
        connectBtn->setText(QApplication::translate("Widget", "\350\277\236\346\216\245", nullptr));
        sendBtn->setText(QApplication::translate("Widget", "\345\217\221\351\200\201", nullptr));
        label_2->setText(QApplication::translate("Widget", "IP\345\234\260\345\235\200\357\274\232", nullptr));
        label->setText(QApplication::translate("Widget", "\347\253\257\345\217\243\345\217\267\357\274\232", nullptr));
        leport_2->setText(QString());
        label_3->setText(QApplication::translate("Widget", "\346\230\265\347\247\260\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
