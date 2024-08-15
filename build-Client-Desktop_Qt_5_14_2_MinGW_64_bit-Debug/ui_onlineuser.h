/********************************************************************************
** Form generated from reading UI file 'onlineuser.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ONLINEUSER_H
#define UI_ONLINEUSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Onlineuser
{
public:
    QListWidget *onlineuser_LW;

    void setupUi(QWidget *Onlineuser)
    {
        if (Onlineuser->objectName().isEmpty())
            Onlineuser->setObjectName(QString::fromUtf8("Onlineuser"));
        Onlineuser->resize(591, 470);
        onlineuser_LW = new QListWidget(Onlineuser);
        onlineuser_LW->setObjectName(QString::fromUtf8("onlineuser_LW"));
        onlineuser_LW->setGeometry(QRect(-10, 0, 611, 481));

        retranslateUi(Onlineuser);

        QMetaObject::connectSlotsByName(Onlineuser);
    } // setupUi

    void retranslateUi(QWidget *Onlineuser)
    {
        Onlineuser->setWindowTitle(QCoreApplication::translate("Onlineuser", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Onlineuser: public Ui_Onlineuser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ONLINEUSER_H
