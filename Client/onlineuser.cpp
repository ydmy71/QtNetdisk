#include "onlineuser.h"
#include "ui_onlineuser.h"
#include<QListWidgetItem>
#include"client.h"
Onlineuser::Onlineuser(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Onlineuser)
{
    ui->setupUi(this);
}

Onlineuser::~Onlineuser()
{
    delete ui;
}

void Onlineuser::update_onlineuser_WigdetList(QStringList userlist)
{
    ui->onlineuser_LW->clear();
    ui->onlineuser_LW->addItems(userlist);
}



void Onlineuser::on_onlineuser_LW_itemDoubleClicked(QListWidgetItem *item)
{
   QString strCurname=Client::getInstance().userMsg;
   QString strIndexname=item->text();
   PDU *pdu=mkPDU(0);
   pdu->uiMsgType=ENUM_MSG_ADDFRIEND_REQUEST;
   memcpy(pdu->caData,strCurname.toStdString().c_str(),32);
   memcpy(pdu->caData+32,strIndexname.toStdString().c_str(),32);
   Client::getInstance().getsocket().write((char*)pdu,pdu->uiPDUlen);
   free(pdu);
   pdu=NULL;
}
