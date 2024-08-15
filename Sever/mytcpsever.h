#ifndef MYTCPSEVER_H
#define MYTCPSEVER_H
#include <QTcpServer>
#include<QDebug>
#include<mytcpsocket.h>
class mytcpsever:public QTcpServer
{
    Q_OBJECT
public:
     static mytcpsever& getInstance();
     void incomingConnection(qintptr handle);
     void resend(QString name,PDU *pdu);
private:
     mytcpsever();
     mytcpsever(const mytcpsever&instance)=delete;
     mytcpsever operator=(const mytcpsever&)=delete;
     //mytcpsever(QWidget *parent = nullptr);
     QList<mytcpsocket*>m_tcpSocketList;
public slots:
     void deletesocket(mytcpsocket *mysoket);
};

#endif // MYTCPSEVER_H
