#include "mytcpsever.h"
mytcpsever &mytcpsever::getInstance()
{
    static mytcpsever instance;
    return instance;
}

void mytcpsever::incomingConnection(qintptr handle)
{
    qDebug()<<"新客户端连接";
    mytcpsocket  *PTcpSocket=new mytcpsocket;
    PTcpSocket->setSocketDescriptor(handle);
    m_tcpSocketList.append(PTcpSocket);
    connect(PTcpSocket,&mytcpsocket::clientoffice_singal,this,&mytcpsever::deletesocket);
}

void mytcpsever::resend(QString name, PDU *pdu)
{
    if(name==NULL||pdu==NULL)
    {
        return;
    }
    for(int i=0;i<m_tcpSocketList.size();i++)
    {
        if(m_tcpSocketList.at(i)->m_socketusername==name)
        {
            qDebug()<<"resend"<<m_tcpSocketList.at(i)->m_socketusername;
            m_tcpSocketList.at(i)->write((char*)pdu,pdu->uiPDUlen);
    }
}
}
mytcpsever::mytcpsever()
{

}

void mytcpsever::deletesocket(mytcpsocket *mysoket)
{
    m_tcpSocketList.removeOne(mysoket);
    mysoket->deleteLater();
//    for(int i=0;i<m_tcpSocketList.size();i++)
//    {
//        qDebug()<<m_tcpSocketList.at(i)->m_socketusername;
//    }
}

