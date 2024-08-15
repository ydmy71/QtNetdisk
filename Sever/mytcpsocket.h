#ifndef MYTCPSOCKET_H
#define MYTCPSOCKET_H
#include <QTcpSocket>
#include"protocol.h"
#include"handlemsg.h"
class mytcpsocket : public QTcpSocket
{
    Q_OBJECT
public:
    mytcpsocket();
    PDU *  readpdu();
  PDU * handlepdu(PDU *pdu);
    void writepdu(PDU *pdu);
    ~mytcpsocket();
    HandleMsg *mh;
    QString m_socketusername;
    QByteArray buffer;
private:
public slots:
    void revMsg();
    void clientoffice();
signals:
    void clientoffice_singal(mytcpsocket *mysocket);
};

#endif // MYTCPSOCKET_H
