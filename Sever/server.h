#ifndef SERVER_H
#define SERVER_H
#include<QFile>
#include<QDebug>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Server; }
QT_END_NAMESPACE

class Server : public QWidget
{
    Q_OBJECT

public:
    Server(QWidget *parent = nullptr);
    ~Server();
    void loadConfig();
    static Server &getinstance();
    QString getRootPath();
private:
    QString m_strIp;
    quint16 m_usPort;
    Ui::Server *ui;
    QString m_strRootPath;
};
#endif // SERVER_H
