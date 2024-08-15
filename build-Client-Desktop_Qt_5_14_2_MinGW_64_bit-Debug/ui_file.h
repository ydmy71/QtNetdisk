/********************************************************************************
** Form generated from reading UI file 'file.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILE_H
#define UI_FILE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_File
{
public:
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QPushButton *deletefile_PB;
    QPushButton *return_PB;
    QPushButton *mkdir_PB;
    QPushButton *rename_PB;
    QPushButton *delfile_PB;
    QPushButton *sharefile_PB;
    QPushButton *delfile_PB_2;
    QPushButton *download_PB;
    QPushButton *movefile_PB;
    QPushButton *upload_PB;
    QListWidget *listWidget_file;

    void setupUi(QWidget *File)
    {
        if (File->objectName().isEmpty())
            File->setObjectName(QString::fromUtf8("File"));
        File->resize(738, 477);
        formLayoutWidget = new QWidget(File);
        formLayoutWidget->setObjectName(QString::fromUtf8("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(480, 30, 201, 321));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        deletefile_PB = new QPushButton(formLayoutWidget);
        deletefile_PB->setObjectName(QString::fromUtf8("deletefile_PB"));

        formLayout->setWidget(0, QFormLayout::LabelRole, deletefile_PB);

        return_PB = new QPushButton(formLayoutWidget);
        return_PB->setObjectName(QString::fromUtf8("return_PB"));

        formLayout->setWidget(0, QFormLayout::FieldRole, return_PB);

        mkdir_PB = new QPushButton(formLayoutWidget);
        mkdir_PB->setObjectName(QString::fromUtf8("mkdir_PB"));

        formLayout->setWidget(1, QFormLayout::LabelRole, mkdir_PB);

        rename_PB = new QPushButton(formLayoutWidget);
        rename_PB->setObjectName(QString::fromUtf8("rename_PB"));

        formLayout->setWidget(1, QFormLayout::FieldRole, rename_PB);

        delfile_PB = new QPushButton(formLayoutWidget);
        delfile_PB->setObjectName(QString::fromUtf8("delfile_PB"));

        formLayout->setWidget(2, QFormLayout::LabelRole, delfile_PB);

        sharefile_PB = new QPushButton(formLayoutWidget);
        sharefile_PB->setObjectName(QString::fromUtf8("sharefile_PB"));

        formLayout->setWidget(2, QFormLayout::FieldRole, sharefile_PB);

        delfile_PB_2 = new QPushButton(formLayoutWidget);
        delfile_PB_2->setObjectName(QString::fromUtf8("delfile_PB_2"));

        formLayout->setWidget(3, QFormLayout::LabelRole, delfile_PB_2);

        download_PB = new QPushButton(formLayoutWidget);
        download_PB->setObjectName(QString::fromUtf8("download_PB"));

        formLayout->setWidget(3, QFormLayout::FieldRole, download_PB);

        movefile_PB = new QPushButton(formLayoutWidget);
        movefile_PB->setObjectName(QString::fromUtf8("movefile_PB"));

        formLayout->setWidget(4, QFormLayout::LabelRole, movefile_PB);

        upload_PB = new QPushButton(formLayoutWidget);
        upload_PB->setObjectName(QString::fromUtf8("upload_PB"));

        formLayout->setWidget(4, QFormLayout::FieldRole, upload_PB);

        listWidget_file = new QListWidget(File);
        listWidget_file->setObjectName(QString::fromUtf8("listWidget_file"));
        listWidget_file->setGeometry(QRect(170, 30, 291, 431));

        retranslateUi(File);

        QMetaObject::connectSlotsByName(File);
    } // setupUi

    void retranslateUi(QWidget *File)
    {
        File->setWindowTitle(QCoreApplication::translate("File", "Form", nullptr));
        deletefile_PB->setText(QCoreApplication::translate("File", "\345\210\240\351\231\244\346\226\207\344\273\266\345\244\271", nullptr));
        return_PB->setText(QCoreApplication::translate("File", "\350\277\224\345\233\236\344\270\212\344\270\200\347\272\247", nullptr));
        mkdir_PB->setText(QCoreApplication::translate("File", "\345\210\233\345\273\272\346\226\207\344\273\266\345\244\271", nullptr));
        rename_PB->setText(QCoreApplication::translate("File", "\351\207\215\345\221\275\345\220\215", nullptr));
        delfile_PB->setText(QCoreApplication::translate("File", "\345\210\267\346\226\260\346\226\207\344\273\266\345\244\271", nullptr));
        sharefile_PB->setText(QCoreApplication::translate("File", "\345\210\206\344\272\253\346\226\207\344\273\266", nullptr));
        delfile_PB_2->setText(QCoreApplication::translate("File", "\345\210\240\351\231\244\346\226\207\344\273\266", nullptr));
        download_PB->setText(QCoreApplication::translate("File", "\344\270\213\350\275\275\346\226\207\344\273\266", nullptr));
        movefile_PB->setText(QCoreApplication::translate("File", "\347\247\273\345\212\250\346\226\207\344\273\266", nullptr));
        upload_PB->setText(QCoreApplication::translate("File", "\344\270\212\344\274\240\346\226\207\344\273\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class File: public Ui_File {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILE_H
