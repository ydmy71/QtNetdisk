/********************************************************************************
** Form generated from reading UI file 'friend.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRIEND_H
#define UI_FRIEND_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Friend
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *flushUser_PB;
    QPushButton *delFriend_PB;
    QPushButton *finduser_PB;
    QPushButton *onlineuser_PB;
    QPushButton *chat_PB;
    QListWidget *listWidget;

    void setupUi(QWidget *Friend)
    {
        if (Friend->objectName().isEmpty())
            Friend->setObjectName(QString::fromUtf8("Friend"));
        Friend->resize(717, 433);
        verticalLayoutWidget = new QWidget(Friend);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(550, 10, 160, 401));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        flushUser_PB = new QPushButton(verticalLayoutWidget);
        flushUser_PB->setObjectName(QString::fromUtf8("flushUser_PB"));

        verticalLayout->addWidget(flushUser_PB);

        delFriend_PB = new QPushButton(verticalLayoutWidget);
        delFriend_PB->setObjectName(QString::fromUtf8("delFriend_PB"));

        verticalLayout->addWidget(delFriend_PB);

        finduser_PB = new QPushButton(verticalLayoutWidget);
        finduser_PB->setObjectName(QString::fromUtf8("finduser_PB"));

        verticalLayout->addWidget(finduser_PB);

        onlineuser_PB = new QPushButton(verticalLayoutWidget);
        onlineuser_PB->setObjectName(QString::fromUtf8("onlineuser_PB"));

        verticalLayout->addWidget(onlineuser_PB);

        chat_PB = new QPushButton(verticalLayoutWidget);
        chat_PB->setObjectName(QString::fromUtf8("chat_PB"));

        verticalLayout->addWidget(chat_PB);

        listWidget = new QListWidget(Friend);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(210, 50, 256, 311));

        retranslateUi(Friend);

        QMetaObject::connectSlotsByName(Friend);
    } // setupUi

    void retranslateUi(QWidget *Friend)
    {
        Friend->setWindowTitle(QCoreApplication::translate("Friend", "Form", nullptr));
        flushUser_PB->setText(QCoreApplication::translate("Friend", "\345\210\267\346\226\260\345\245\275\345\217\213", nullptr));
        delFriend_PB->setText(QCoreApplication::translate("Friend", "\345\210\240\351\231\244\345\245\275\345\217\213", nullptr));
        finduser_PB->setText(QCoreApplication::translate("Friend", "\346\237\245\346\211\276\347\224\250\346\210\267", nullptr));
        onlineuser_PB->setText(QCoreApplication::translate("Friend", "\345\234\250\347\272\277\347\224\250\346\210\267", nullptr));
        chat_PB->setText(QCoreApplication::translate("Friend", "\350\201\212\345\244\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Friend: public Ui_Friend {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRIEND_H
