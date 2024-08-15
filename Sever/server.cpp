#include "server.h"
#include "ui_server.h"
#include"mytcpsever.h"
Server::Server(QWidget *parent) : QWidget(parent), ui(new Ui::Server)
{
    ui->setupUi(this);
    loadConfig();
    mytcpsever::getInstance().listen(QHostAddress(m_strIp),m_usPort);
}
void Server::loadConfig()
{
    //获取配置文件 ip地址和端口号
    QFile file(":/server.config");
    if(file.open(QIODevice::ReadOnly))
    {
        QByteArray data=file.readAll();
        QString strdata=QString(data);
        QStringList datalist=strdata.split("\r\n");
        m_strIp=datalist.at(0);
        m_usPort=datalist.at(1).toUShort();
        m_strRootPath=datalist.at(2);
        qDebug()<<"打开客户端配置文件"<<"Ip:"<<m_strIp<<"Port:"<<m_usPort<<"m_strRootPath"<<m_strRootPath;
         file.close();
    }else
    {
        qDebug()<<"打开失败";
    }
}

Server &Server::getinstance()
{
    static Server instance;
    return instance;
}

QString Server::getRootPath()
{
    return m_strRootPath;
}
Server::~Server()
{
    delete ui;
}

