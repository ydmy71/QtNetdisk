#include "friend.h"
#include "ui_friend.h"
#include<QDebug>
#include<QInputDialog>
#include <qmessagebox.h>
#include<QTcpSocket>
#include"protocol.h"
#include"client.h"
#include"onlineuser.h"
Friend::Friend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Friend)
{
    m_pOnlienuser=new Onlineuser();
    m_pchat=new Chat();
    ui->setupUi(this);
    flushfriend();
}

Onlineuser *Friend::getonlineuser()
{
    return m_pOnlienuser;
}

Friend::~Friend()
{
    delete ui;
    delete m_pOnlienuser;
    delete m_pchat;
}

void Friend::flushfriend()
{
    PDU *pdu=mkPDU(0);
    pdu->uiMsgType= ENUM_MSG_FLUSHFRIEND_AGREE_REQUEST;
    memcpy(pdu->caData,Client::getInstance().m_username.toStdString().c_str(),32);
    Client::getInstance().getsocket().write((char*)pdu,pdu->uiPDUlen);
    free(pdu);
    pdu=NULL;
}

Chat *Friend::getchat()
{
    return m_pchat;
}

void Friend::updatafriend(QStringList friendlist)
{
    ui->listWidget->clear();
    ui->listWidget->addItems(friendlist);
}

QListWidget *Friend::getfriend_lw()
{
    return ui->listWidget;
}

void Friend::on_finduser_PB_clicked()
{
    QString name=QInputDialog::getText(this,"搜索","用户名");

    if(name.isEmpty()||name.toStdString().size()>32)
        {
            QMessageBox::information(this,"搜索错误","请输入用户名或用户名过长");
            return;
        }
        PDU *pdu=mkPDU(0);
        pdu->uiMsgType=ENUM_MSG_FINDUSER_REQUEST;
        memcpy(pdu->caData,name.toStdString().c_str(),32);
        Client::getInstance().getsocket().write((char*)pdu,pdu->uiPDUlen);
        free(pdu);
        pdu=NULL;
}


void Friend::on_onlineuser_PB_clicked()
{
    if(m_pOnlienuser->isHidden())
    {
        m_pOnlienuser->show();
    }
    PDU *pdu=mkPDU(0);
    pdu->uiMsgType=ENUM_MSG_ONLINEUSER_REQUEST;
    Client::getInstance().getsocket().write((char*)pdu,pdu->uiPDUlen);
    free(pdu);
    pdu=NULL;
}

void Friend::on_flushUser_PB_clicked()
{
    flushfriend();
}

void Friend::on_delFriend_PB_clicked()
{
    QListWidgetItem *pitem=ui->listWidget->currentItem();
    if(pitem==NULL)
    {
        QMessageBox::information(this,"删除好友","请选择要删除的好友");
        return;
    }
    QString strdelname=pitem->text();
        int ret=QMessageBox::question(this,"删除好友",QString("是否确定删除%1好友").arg(strdelname));
        if(ret!=QMessageBox::Yes)
        {
            return;
        }
        PDU *pdu=mkPDU(0);
        pdu->uiMsgType=ENUM_MSG_DELFRIEND_REQUEST;
        memcpy(pdu->caData,Client::getInstance().m_username.toStdString().c_str(),32);
        memcpy(pdu->caData+32,strdelname.toStdString().c_str(),32);
        Client::getInstance().getsocket().write((char*)pdu,pdu->uiPDUlen);
        free(pdu);
        pdu=NULL;
}

void Friend::on_chat_PB_clicked()
{
    QListWidgetItem *pitem=ui->listWidget->currentItem();
    if(pitem==NULL)
    {
        QMessageBox::information(this,"聊天","请选择要聊天的好友");
        return;
    }
    if(m_pchat->isHidden())
    {
        m_pchat->show();
    }
    m_pchat->m_strchatname=pitem->text();

}
