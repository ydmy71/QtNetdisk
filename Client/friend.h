#ifndef FRIEND_H
#define FRIEND_H

#include <QWidget>
#include <QTcpSocket>
#include"onlineuser.h"
#include"chat.h"
namespace Ui {
class Friend;
}

class Friend : public QWidget
{
    Q_OBJECT

public:
    explicit Friend(QWidget *parent = nullptr);
     Onlineuser *getonlineuser();
    ~Friend();
     void flushfriend();
     Chat * getchat();
     void updatafriend(QStringList friendlist);
     QListWidget* getfriend_lw();
private slots:
    void on_finduser_PB_clicked();
    void on_onlineuser_PB_clicked();

    void on_flushUser_PB_clicked();

    void on_delFriend_PB_clicked();

    void on_chat_PB_clicked();

private:
    Ui::Friend *ui;
    Onlineuser* m_pOnlienuser;
    Chat* m_pchat;
};

#endif // FRIEND_H
