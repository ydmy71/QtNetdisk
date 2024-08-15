#include "client.h"
#include "ui_client.h"
#include "protocol.h"
#include <QMessageBox>
#include<QMessageBox>
#include <qinputdialog.h>
#include"index.h"
Client::Client(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Client)
{
    ui->setupUi(this);
    loadConfig();
    ConnectServer();
    rh =new reshandle;
    QObject::connect(&m_TcpSocket,&QTcpSocket::readyRead,this,&Client::revMsg);
}
Client::~Client()
{
    delete ui;
    delete rh;
}
void Client::loadConfig()
{
    //获取配置文件 ip地址和端口号
    QFile file(":/client.config");
    if(file.open(QIODevice::ReadOnly))
    {
        QByteArray data=file.readAll();
        QString strdata=QString(data);
        QStringList datalist=strdata.split("\r\n");
        m_strIp=datalist.at(0);
        m_usPort=datalist.at(1).toUShort();
        m_strcurpath=datalist.at(2);
        qDebug()<<"打开客户端配置文件"<<"Ip:"<<m_strIp<<"Port:"<<m_usPort<<"m_strRootPath"<<m_strcurpath;
         file.close();
    }else
    {
        qDebug()<<"打开失败";
    }
}

PDU *Client::readpdu()
{
    uint uiPDULen=0;
    m_TcpSocket.read((char*)&uiPDULen,sizeof(uint));
    PDU *pdu=mkPDU(uiPDULen);
    m_TcpSocket.read((char*)pdu+sizeof(uint),uiPDULen-sizeof(uint));
    qDebug()<<"实际类型："<<pdu->uiMsgType
           <<"实际消息："<<pdu->caMsg
           <<"参数1"<<pdu->caData
           <<"参数2"<<pdu->caData+32
           <<"UIMSGLEN"<<pdu->uiMsglen;
    return pdu;
}

void Client::handlepdu(PDU *pdu)
{
    qDebug()<<"实际类型："<<pdu->uiMsgType
           <<"实际消息："<<pdu->caMsg
           <<"参数1"<<pdu->caData
           <<"参数2"<<pdu->caData+32
           <<"UIMSGLEN"<<pdu->uiMsglen;
    switch(pdu->uiMsgType)
    {
      case ENUM_MSG_REGIST_RESPEND:
    {
        rh->rigster(pdu);
        break;
    }
    case ENUM_MSG_LOGIN_RESPEND:
  {

    rh->Login(pdu);
       break;
  }
    case ENUM_MSG_FINDUSER_RESPEND:
  {
       rh->Finduser(pdu);
          break;
  }
         case ENUM_MSG_ONLINEUSER_RESPEND:
    {
         rh->Onlineuser(pdu,m_username);
            break;
    }
    case ENUM_MSG_ADDFRIEND_RESPEND:
{
    rh->Addfriend(pdu);
       break;
}
    case ENUM_MSG_ADDFRIEND_REQUEST:
{
    rh->Agreeaddfriendrequst(pdu);
       break;
}
    case ENUM_MSG_ADDFRIEND_AGREE_RESPEND:
    {
        rh->Agreeaddfriendres(pdu);
        break;
    }
    case ENUM_MSG_FLUSHFRIEND_AGREE_RESPEND:
    {
        rh->Flushonlinefriend(pdu);
        break;
    }
    case ENUM_MSG_MKDIRFILE_RESPEND:
    {
        rh->mkdirfile(pdu);
        break;
    }
    case ENUM_MSG_FLUSHFILE_RESPEND:
    {
        rh->flushfile(pdu);
        break;
    }
    case ENUM_MSG_DELDIR_RESPEND:
    {
        rh->deldir(pdu);
        break;
    }
    case ENUM_MSG_DELFILE_RESPEND:
    {
        rh->Delfile(pdu);
        break;
    }
    case ENUM_MSG_RENAMEFILE_RESPEND:
    {
        rh->renamefile(pdu);
        break;
    }
    case ENUM_MSG_DELFRIEND_RESPEND:
    {
        rh->Delfriend(pdu);
        break;
    }
    case ENUM_MSG_MOVEFILE_RESPEND:
    {
        rh->movefile(pdu);
        break;
    }
    case ENUM_MSG_UPLOADFILE_RESPEND:
    {
        rh->uploadfile(pdu);
        break;
    }
    case ENUM_MSG_UPLOADFILE_DATA_RESPEND:
    {
        rh->uploaddata(pdu);
        break;
    }
    case ENUM_MSG_SHAREFILE_RESPEND:
    {
        rh->sharefile(pdu);
        break;
    }
    case ENUM_MSG_SHAREFILE_REQUEST:
    {
        rh->sharefileRequest(pdu);
        break;
    }
    case ENUM_MSG_SHAREFILE_AGREE_REQUEST:
    {
        rh->sharefileAgree(pdu);
        break;
    }
    case ENUM_MSG_CHATFRIEND_REQUEST:
    {
        rh->chat(pdu);
        break;
    }
    }
}


void Client::ConnectServer()
{
    connect(&m_TcpSocket,&QTcpSocket::connected,this,&Client::ShowConnect);
    m_TcpSocket.connectToHost(QHostAddress(m_strIp),m_usPort);
}

QTcpSocket &Client::getsocket()
{
    return m_TcpSocket;
}

QString Client::getpath()
{
    return m_strcurpath;
}

Client &Client::getInstance()
{
    static Client instance;
    return instance;
}

void Client::sendpdu(PDU *pdu)
{

}
void Client::ShowConnect()
{
    qDebug()<<"服务器连接成功";
}

void Client::revMsg()
{
    QByteArray data=m_TcpSocket.readAll();
    buffer.append(data);
    while (buffer.size()>=int(sizeof(PDU))) {
        PDU *pdu=(PDU*)buffer.data();
        if(buffer.size()<int(pdu->uiPDUlen))
        {
                break;
    }
       handlepdu(pdu);
        buffer.remove(0,pdu->uiPDUlen);
    }
}
void Client::on_login_PB_clicked()
{
    {
        userMsg=ui->username->text();
        QString passwordMsg=ui->password->text();
        if(userMsg.isEmpty()||userMsg.toStdString().size()>32)
            {
                QMessageBox::information(this,"登录错误","请输入用户名或用户名过长");
                return;
            }
        if(passwordMsg.isEmpty()||passwordMsg.toStdString().size()>32)
            {
                QMessageBox::information(this,"登录错误","请输入密码或密码过长");
                return;
            }
            PDU *pdu=mkPDU(0);
            pdu->uiMsgType=ENUM_MSG_LOGIN_REQUEST;
            memcpy(pdu->caData,userMsg.toStdString().c_str(),32);
            memcpy(pdu->caData+32,passwordMsg.toStdString().c_str(),32);
            m_TcpSocket.write((char*)pdu,pdu->uiPDUlen);
            m_username=userMsg;
            free(pdu);
            pdu=NULL;
    }
}
void Client::on_register_PB_clicked()
{
    {
        QString userMsg=ui->username->text();
        QString passwordMsg=ui->password->text();
        if(userMsg.isEmpty()||userMsg.toStdString().size()>32)
            {
                QMessageBox::information(this,"注册错误","请输入用户名或用户名过长");
                return;
            }
        if(passwordMsg.isEmpty()||passwordMsg.toStdString().size()>32)
            {
                QMessageBox::information(this,"注册错误","请输入密码或密码过长");
                return;
            }
            PDU *pdu=mkPDU(0);
            pdu->uiMsgType=ENUM_MSG_REGIST_REQUEST;
            memcpy(pdu->caData,userMsg.toStdString().c_str(),32);
            memcpy(pdu->caData+32,passwordMsg.toStdString().c_str(),32);
            m_TcpSocket.write((char*)pdu,pdu->uiPDUlen);
            free(pdu);
            pdu=NULL;
    }
}
