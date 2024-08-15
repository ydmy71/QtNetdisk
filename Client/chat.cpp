#include "chat.h"
#include "ui_chat.h"
#include"protocol.h"
#include"client.h"
Chat::Chat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Chat)
{
    ui->setupUi(this);
}

Chat::~Chat()
{
    delete ui;
}

void Chat::update_le(QString strmsg)
{
    ui->show_te->append(strmsg);
}

void Chat::on_send_PB_clicked()
{
    QString strmsg=ui->inout_le->text();

    if(strmsg.isEmpty())
    {
        return;
    }
    PDU *pdu=mkPDU(strmsg.toStdString().size()+1);
    pdu->uiMsgType=ENUM_MSG_CHATFRIEND_REQUEST;
    memcpy(pdu->caData,Client::getInstance().m_username.toStdString().c_str(),32);
    memcpy(pdu->caData+32,m_strchatname.toStdString().c_str(),32);
    memcpy(pdu->caMsg,strmsg.toStdString().c_str(),strmsg.toStdString().size());
    Client::getInstance().getsocket().write((char*)pdu,pdu->uiPDUlen);
    free(pdu);
    pdu=NULL;
    ui->inout_le->clear();
}
