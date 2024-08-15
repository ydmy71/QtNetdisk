#include "sharefile.h"
#include "ui_sharefile.h"
#include"index.h"
#include"client.h"
ShareFile::ShareFile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShareFile)
{
    ui->setupUi(this);
}

ShareFile::~ShareFile()
{
    delete ui;
}

void ShareFile::updatefriend_LW()
{
    ui->listWidget->clear();
    QListWidget* friend_lw=Index::getinstance().getFriend()->getfriend_lw();
            for(int i=0;i<friend_lw->count();i++)
    {
        QListWidgetItem * frienditem=friend_lw->item(i);
        QListWidgetItem *newitem=new QListWidgetItem(*frienditem);
        ui->listWidget->addItem(newitem); 
    }
}

void ShareFile::on_ALLSelect_PB_clicked()
{
    for(int i=0;i<ui->listWidget->count();i++)
    {
        ui->listWidget->item(i)->setSelected(true);
    }
}

void ShareFile::on_cancelselect_PB_clicked()
{
    for(int i=0;i<ui->listWidget->count();i++)
    {
        ui->listWidget->item(i)->setSelected(false);
    }
}

void ShareFile::on_ok_PB_clicked()
{
    QString strcurpath=Index::getinstance().getFile()->m_strcurpath;
    QString strpath=strcurpath+"/"+Index::getinstance().getFile()->m_strsharefile;
    QString strcurname=Client::getInstance().m_username;
    QList<QListWidgetItem*> pItems=ui->listWidget->selectedItems();
    int friendNum=pItems.size();
    PDU *pdu=mkPDU(friendNum*32+strpath.toStdString().size()+1);
    pdu->uiMsgType=ENUM_MSG_SHAREFILE_REQUEST;
    memcpy(pdu->caData,strcurname.toStdString().c_str(),32);
    memcpy(pdu->caData+32,&friendNum,sizeof(int));
    for(int i=0;i<friendNum;i++)
    {
        memcpy(pdu->caMsg+i*32,pItems.at(i)->text().toStdString().c_str(),32);

    }
    memcpy(pdu->caMsg+friendNum*32,strpath.toStdString().c_str(),32);
    Client::getInstance().getsocket().write((char*)pdu,pdu->uiPDUlen);
    free(pdu);
    pdu=NULL;

}
