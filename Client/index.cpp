#include "index.h"
#include "ui_index.h"

Index::Index(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Index)
{
    ui->setupUi(this);
}

Index::~Index()
{
    delete ui;
}

Friend *Index::getFriend()
{
    return ui->friend_page;
}

File *Index::getFile()
{
    return ui->file_page;
}

Index &Index::getinstance()
{
     static Index instance;
     return instance;
}

void Index::on_friend_push_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->file_push->setStyleSheet ("QPushButton {border : none ;background-color:rgb(255，255， 255) ipadding:20px; }") ;
    ui->friend_push->setStyleSheet("QPushButton {border :none; padding:20px; } ");
}

void Index::on_file_push_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
     ui->file_push->setStyleSheet("QPushButton {border :none; padding:20px; } ");
     ui->friend_push->setStyleSheet ("QPushButton {border : none ;background-color:rgb(255，255， 255) ipadding:20px;}") ;
}
