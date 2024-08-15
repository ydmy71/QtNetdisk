#include "mytcpsocket.h"
#include"protocol.h"
#include "operatedb.h"
mytcpsocket::mytcpsocket()
{
   mh=new HandleMsg;
   QObject::connect(this,&QTcpSocket::readyRead,this,&mytcpsocket::revMsg);
   QObject::connect(this,&QTcpSocket::disconnected,this,&mytcpsocket::clientoffice);
}

PDU *mytcpsocket::readpdu()
{
    uint uiPDULen=0;
    this->read((char*)&uiPDULen,sizeof(uint));
    PDU *pdu=mkPDU(uiPDULen);
    this->read((char*)pdu+sizeof(uint),uiPDULen-sizeof(uint));
    qDebug()<<"实际类型："<<pdu->uiMsgType
           <<"实际消息："<<pdu->caMsg
           <<"参数1"<<pdu->caData
           <<"参数2"<<pdu->caData+32;
    return pdu;
}

 PDU* mytcpsocket::handlepdu(PDU *pdu)
{
     qDebug()<<"实际类型："<<pdu->uiMsgType
            <<"实际消息："<<pdu->caMsg
            <<"参数1"<<pdu->caData
            <<"参数2"<<pdu->caData+32
            <<"UIMSGLEN"<<pdu->uiMsglen;
     switch(pdu->uiMsgType){
     case ENUM_MSG_REGIST_REQUEST:
    {
        return mh->rigster(pdu);
     }
       case ENUM_MSG_LOGIN_REQUEST:
     {
       return mh->Login(pdu, m_socketusername);
     }
       case ENUM_MSG_FINDUSER_REQUEST:
     {
         qDebug()<<"---------------------------------";
        return mh->Finduser(pdu);
     }
     case ENUM_MSG_ONLINEUSER_REQUEST:
 {
        return  mh->Onlineuser();
     }
     case ENUM_MSG_ADDFRIEND_REQUEST:
    {
       return mh->Addfriend(pdu);
     }
     case ENUM_MSG_ADDFRIEND_AGREE_REQUEST:
    {
       return mh->Agreefriend(pdu);
     }

     case ENUM_MSG_FLUSHFRIEND_AGREE_REQUEST:
     {
         return mh->Flushfriend(pdu);
     }
     case ENUM_MSG_MKDIRFILE_REQUEST:
     {
         return mh->Newmkdirfile(pdu);
     }
     case ENUM_MSG_FLUSHFILE_REQUEST:
     {
         return mh->Flushfile(pdu);
     }
     case ENUM_MSG_DELDIR_REQUEST:
     {
         return mh->Deldir(pdu);
     }
     case ENUM_MSG_DELFILE_REQUEST:
     {
         return mh->Delfile(pdu);
     }
     case ENUM_MSG_RENAMEFILE_REQUEST:
     {
         return mh->Renamefile(pdu);
     }
     case ENUM_MSG_DELFRIEND_REQUEST:
     {
         return mh->Delfriend(pdu);
     }
     case ENUM_MSG_MOVEFILE_REQUEST:
     {
         return mh->Movefile(pdu);
     }
     case ENUM_MSG_UPLOADFILE_REQUEST:
     {
         return mh->uploadfile(pdu);
     }
     case ENUM_MSG_UPLOADFILE_DATA_REQUEST:
     {
         return mh->uploadfiledata(pdu);
     }
     case ENUM_MSG_SHAREFILE_REQUEST:
     {
         return mh->Sharefile(pdu);
     }
     case ENUM_MSG_SHAREFILE_AGREE_REQUEST:
     {
         return mh->Sharefileagree(pdu);
     }
     case ENUM_MSG_CHATFRIEND_REQUEST:
     {
         mh->Chatfriend(pdu);
     }
     default:
     {

     }
     }
 return NULL;
 }
 void mytcpsocket::writepdu(PDU *pdu)
 {
     if(pdu==NULL)
     {
         return;
     }
     write((char*)pdu,pdu->uiPDUlen);
     free(pdu);
     pdu=NULL;
 }
mytcpsocket::~mytcpsocket()
{
    delete mh;
}
void mytcpsocket::revMsg()
{
    QByteArray data=readAll();
    buffer.append(data);
    while (buffer.size()>=int(sizeof(PDU))) {
        PDU *pdu=(PDU*)buffer.data();
        if(buffer.size()<int(pdu->uiPDUlen))
        {
                break;
    }
        PDU* respdu=handlepdu(pdu);
        writepdu(respdu);
        buffer.remove(0,pdu->uiPDUlen);
    }
}

void mytcpsocket::clientoffice()
{
    OperateDB::get_instance().handleOffline(m_socketusername.toStdString().c_str());
    emit clientoffice_singal(this);
}
