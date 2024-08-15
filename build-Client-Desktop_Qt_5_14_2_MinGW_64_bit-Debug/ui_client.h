/********************************************************************************
** Form generated from reading UI file 'client.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_H
#define UI_CLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Client
{
public:
    QLabel *label;
    QLabel *label_2;
    QLineEdit *username;
    QLineEdit *password;
    QPushButton *login_PB;
    QPushButton *register_PB;

    void setupUi(QWidget *Client)
    {
        if (Client->objectName().isEmpty())
            Client->setObjectName(QString::fromUtf8("Client"));
        Client->resize(439, 384);
        label = new QLabel(Client);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(100, 90, 131, 81));
        label_2 = new QLabel(Client);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(100, 170, 111, 41));
        username = new QLineEdit(Client);
        username->setObjectName(QString::fromUtf8("username"));
        username->setGeometry(QRect(210, 120, 113, 21));
        password = new QLineEdit(Client);
        password->setObjectName(QString::fromUtf8("password"));
        password->setGeometry(QRect(210, 180, 113, 21));
        password->setEchoMode(QLineEdit::Password);
        login_PB = new QPushButton(Client);
        login_PB->setObjectName(QString::fromUtf8("login_PB"));
        login_PB->setGeometry(QRect(90, 240, 93, 28));
        register_PB = new QPushButton(Client);
        register_PB->setObjectName(QString::fromUtf8("register_PB"));
        register_PB->setGeometry(QRect(270, 240, 93, 28));

        retranslateUi(Client);

        QMetaObject::connectSlotsByName(Client);
    } // setupUi

    void retranslateUi(QWidget *Client)
    {
        Client->setWindowTitle(QCoreApplication::translate("Client", "Client", nullptr));
        label->setText(QCoreApplication::translate("Client", "\347\224\250\346\210\267\345\220\215:", nullptr));
        label_2->setText(QCoreApplication::translate("Client", "\345\257\206\347\240\201:", nullptr));
        login_PB->setText(QCoreApplication::translate("Client", "\347\231\273\345\275\225", nullptr));
        register_PB->setText(QCoreApplication::translate("Client", "\346\263\250\345\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Client: public Ui_Client {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_H
