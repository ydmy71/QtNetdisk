#include "operatedb.h"
#include<QDebug>
#include<QSqlError>
#include <QSqlQuery>
OperateDB &OperateDB::get_instance()
{
    static OperateDB instance;
    return instance;
}

void OperateDB::connect()
{
    my_db.setHostName("localhost");
    my_db.setDatabaseName("whwx");
    my_db.setPort(3307);
    my_db.setUserName("root");
    my_db.setPassword("123456");
    if(my_db.open())
    {
        qDebug()<<"数据库连接成功";
    }else
    {
        qDebug()<<"数据库连接失败"<<my_db.lastError().text();
    }

}

bool OperateDB::handleregist(char *name, char *pwd)
{
      if(name==NULL||pwd==NULL)
      {
          return false;
      }
      QString sql=QString("select * from user_info where name='%1'").arg(name);
      QSqlQuery q;
      if(!q.exec(sql)||q.next())
      {
          return false;
      }
      sql=QString("insert into user_info(name,pwd) values('%1','%2')").arg(name).arg(pwd);
      return q.exec(sql);

}

bool OperateDB::handlelogin(char *name, char *pwd)
{
    if(name==NULL||pwd==NULL)
    {
        return false;
    }
    QString sql=QString("select * from user_info where name='%1' and pwd='%2'").arg(name).arg(pwd);
    QSqlQuery q;
    if(!q.exec(sql)||!q.next())
    {
        return false;
    }
    QString sql1=QString("update user_info set online=1 where name='%1' and pwd='%2'").arg(name).arg(pwd);
    q.exec(sql1);
    return q.exec(sql);
}

void OperateDB::handleOffline(const char *name)
{
    if(name==NULL)
    {
        return;
    }
    QSqlQuery q;
    QString sql=QString("update user_info set online=0 where name='%1'").arg(name);
    q.exec(sql);
}

int OperateDB::handlefinduser(const char *name)
{
    if(name==NULL)
    {
        return -1;
    }
    QSqlQuery q;
    QString sql=QString("select online from user_info where name='%1'").arg(name);
    q.exec(sql);
    if(!q.next())
    {
        return -1;
    }
    return q.value(0).toUInt();
}

int OperateDB::handleaddfriend(char*curname,char*tarname)
{
    if(curname==NULL||tarname==NULL)
    {
        return -1;
    }
    QSqlQuery q;
    QString sql=QString("select *from friend where(user_id=(select id from user_info where name='%1')and friend_id=(select id from user_info where name='%2')) or (friend_id=(select id from user_info where name='%3')and user_id=(select id from user_info where name='%4'))")
            .arg(curname).arg(tarname).arg(curname).arg(tarname);
    q.exec(sql);
    if(q.next())
    {
        return -2;
    }
    QString sql1=QString("select online from user_info where name='%1'").arg(tarname);
    q.exec(sql1);
    if(!q.next())
    {
        return -1;
    }
    return q.value(0).toUInt();
}

bool OperateDB::handledelfriend(char *curname, char *tarname)
{
    if(curname==NULL||tarname==NULL)
    {
        return false;
    }
    QSqlQuery q;
    QString sql=QString(R"(select *from friend where
                        (user_id=(select id from user_info where name='%1')
                        and friend_id=(select id from user_info
                        where name='%2'))
                        or (friend_id=(select id from user_info where name='%3')
                        and user_id=(select id from user_info where name='%4'));)")
                .arg(curname).arg(tarname).arg(curname).arg(tarname);
    q.exec(sql);
    if(!q.next())
    {
        return false;
    }
    sql=QString(R"(delete from friend where
                (user_id=(select id from user_info where name='%1')
                and friend_id=(select id from user_info where name='%2'))
                or (friend_id=(select id from user_info where name='%3')
                and user_id=(select id from user_info where name='&4'));)")
                 .arg(curname).arg(tarname).arg(curname).arg(tarname);
    q.exec(sql);
    return true;
}

void OperateDB::agreeaddfriend(char *curname, char *tarname)
{
    if(curname==NULL||tarname==NULL)
    {
        return ;
    }
    QSqlQuery q;
    QString sql=QString(R"(
                        insert into friend(user_id,friend_id)
                        select u1.id,u2.id from user_info u1 ,user_info u2 where u1.name='%1' and u2.name='%2'
                        )").arg(curname).arg(tarname).arg(curname).arg(tarname);
    q.exec(sql);

}


QStringList OperateDB::handleonlineuser()
{
    QSqlQuery q;
    QString sql=QString("select name from user_info where online=1");
    q.exec(sql);
    QStringList result;
    result.clear();
    while(q.next())
    {
      result.append(q.value(0).toStringList());
    }


    return result;
}

QStringList OperateDB::handleflushonlineuser(char *curname)
{
    QStringList result;
    result.clear();
    if (curname==NULL)
    {
        return result;
    }
    QSqlQuery q;
    QString sql=QString(R"(
                        select name from user_info where id in
                        (select user_id from friend where friend_id=(select id from user_info where name='%1')
                        union
                        select friend_id from friend where user_id=(select id from user_info where name='%1'))and online=1)").arg(curname);
    q.exec(sql);

    while(q.next())
    {
      result.append(q.value(0).toStringList());
    }


    return result;
}
OperateDB::~OperateDB()
{
    my_db.close();
}

OperateDB::OperateDB(QObject *parent) : QObject(parent)
{
    my_db=QSqlDatabase::addDatabase("QMYSQL");
}
