/********************************************************************************
** Form generated from reading UI file 'chat.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHAT_H
#define UI_CHAT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Chat
{
public:
    QPushButton *send_PB;
    QLineEdit *inout_le;
    QTextEdit *show_te;

    void setupUi(QWidget *Chat)
    {
        if (Chat->objectName().isEmpty())
            Chat->setObjectName(QString::fromUtf8("Chat"));
        Chat->resize(617, 501);
        send_PB = new QPushButton(Chat);
        send_PB->setObjectName(QString::fromUtf8("send_PB"));
        send_PB->setGeometry(QRect(482, 380, 101, 51));
        inout_le = new QLineEdit(Chat);
        inout_le->setObjectName(QString::fromUtf8("inout_le"));
        inout_le->setGeometry(QRect(80, 380, 351, 51));
        show_te = new QTextEdit(Chat);
        show_te->setObjectName(QString::fromUtf8("show_te"));
        show_te->setGeometry(QRect(80, 40, 471, 301));
        show_te->setReadOnly(true);

        retranslateUi(Chat);

        QMetaObject::connectSlotsByName(Chat);
    } // setupUi

    void retranslateUi(QWidget *Chat)
    {
        Chat->setWindowTitle(QCoreApplication::translate("Chat", "Form", nullptr));
        send_PB->setText(QCoreApplication::translate("Chat", "\345\217\221\351\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Chat: public Ui_Chat {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHAT_H
