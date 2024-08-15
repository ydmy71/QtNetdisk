/********************************************************************************
** Form generated from reading UI file 'index.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INDEX_H
#define UI_INDEX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>
#include "file.h"
#include "friend.h"

QT_BEGIN_NAMESPACE

class Ui_Index
{
public:
    QStackedWidget *stackedWidget;
    File *file_page;
    Friend *friend_page;
    QPushButton *friend_push;
    QPushButton *file_push;

    void setupUi(QWidget *Index)
    {
        if (Index->objectName().isEmpty())
            Index->setObjectName(QString::fromUtf8("Index"));
        Index->resize(1215, 720);
        stackedWidget = new QStackedWidget(Index);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(360, 130, 941, 411));
        file_page = new File();
        file_page->setObjectName(QString::fromUtf8("file_page"));
        stackedWidget->addWidget(file_page);
        friend_page = new Friend();
        friend_page->setObjectName(QString::fromUtf8("friend_page"));
        stackedWidget->addWidget(friend_page);
        friend_push = new QPushButton(Index);
        friend_push->setObjectName(QString::fromUtf8("friend_push"));
        friend_push->setGeometry(QRect(90, 80, 93, 211));
        friend_push->setStyleSheet(QString::fromUtf8("border : none;\n"
"background-color:rgb(255\357\274\214255\357\274\214 255) \n"
""));
        file_push = new QPushButton(Index);
        file_push->setObjectName(QString::fromUtf8("file_push"));
        file_push->setGeometry(QRect(90, 290, 93, 211));
        file_push->setStyleSheet(QString::fromUtf8("border :none; padding:20px;"));

        retranslateUi(Index);

        QMetaObject::connectSlotsByName(Index);
    } // setupUi

    void retranslateUi(QWidget *Index)
    {
        Index->setWindowTitle(QCoreApplication::translate("Index", "Form", nullptr));
        friend_push->setText(QCoreApplication::translate("Index", "\345\245\275\345\217\213", nullptr));
        file_push->setText(QCoreApplication::translate("Index", "\346\226\207\344\273\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Index: public Ui_Index {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INDEX_H
