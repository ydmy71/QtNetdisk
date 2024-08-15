#ifndef CLIENT_H
#define CLIENT_H
#include <QWidget>
#include<QTcpSocket>
#include<QFile>
#include<QDebug>
#include<QHostAddress>
#include "protocol.h"
#include"reshandle.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Client; }
QT_END_NAMESPACE
class Client : public QWidget
{
    Q_OBJECT
public:

    ~Client();
    void loadConfig();
    PDU *readpdu();
    void handlepdu(PDU *pdu);
    void ConnectServer();
     QTcpSocket& getsocket();
     QString getpath();
    static Client& getInstance();
    void sendpdu(PDU *pdu);
    reshandle *rh;
    QString userMsg;
    QString m_username;
    QByteArray buffer;
private:
    Client(QWidget *parent = nullptr);
    Client(const Client&instance)=delete;
    Client operator=(const Client&)=delete;
    Ui::Client *ui;
    QString m_strIp;
    quint16 m_usPort;
    QTcpSocket m_TcpSocket;
    QString m_strcurpath;
public slots:
    void ShowConnect();
private slots:
//  void on_pushButton_clicked();
    void revMsg();
    void on_login_PB_clicked();
    void on_register_PB_clicked();

};
#endif // CLIENT_H
