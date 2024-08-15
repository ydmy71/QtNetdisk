/********************************************************************************
** Form generated from reading UI file 'sharefile.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHAREFILE_H
#define UI_SHAREFILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ShareFile
{
public:
    QListWidget *listWidget;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QPushButton *ALLSelect_PB;
    QPushButton *cancelselect_PB;
    QSpacerItem *verticalSpacer;
    QPushButton *ok_PB;

    void setupUi(QWidget *ShareFile)
    {
        if (ShareFile->objectName().isEmpty())
            ShareFile->setObjectName(QString::fromUtf8("ShareFile"));
        ShareFile->resize(683, 518);
        listWidget = new QListWidget(ShareFile);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(30, 40, 391, 431));
        listWidget->setSelectionMode(QAbstractItemView::MultiSelection);
        widget = new QWidget(ShareFile);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(500, 50, 141, 401));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        ALLSelect_PB = new QPushButton(widget);
        ALLSelect_PB->setObjectName(QString::fromUtf8("ALLSelect_PB"));

        verticalLayout->addWidget(ALLSelect_PB);

        cancelselect_PB = new QPushButton(widget);
        cancelselect_PB->setObjectName(QString::fromUtf8("cancelselect_PB"));

        verticalLayout->addWidget(cancelselect_PB);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        ok_PB = new QPushButton(widget);
        ok_PB->setObjectName(QString::fromUtf8("ok_PB"));

        verticalLayout->addWidget(ok_PB);


        retranslateUi(ShareFile);

        QMetaObject::connectSlotsByName(ShareFile);
    } // setupUi

    void retranslateUi(QWidget *ShareFile)
    {
        ShareFile->setWindowTitle(QCoreApplication::translate("ShareFile", "Form", nullptr));
        ALLSelect_PB->setText(QCoreApplication::translate("ShareFile", "\345\205\250\351\200\211", nullptr));
        cancelselect_PB->setText(QCoreApplication::translate("ShareFile", "\345\217\226\346\266\210\345\267\262\351\200\211", nullptr));
        ok_PB->setText(QCoreApplication::translate("ShareFile", "\347\241\256\345\256\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ShareFile: public Ui_ShareFile {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHAREFILE_H
