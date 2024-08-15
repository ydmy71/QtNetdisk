#ifndef OPERATEDB_H
#define OPERATEDB_H

#include "protocol.h"

#include <QObject>
#include<QSqlDatabase>
class OperateDB : public QObject
{
    Q_OBJECT
public:
    QSqlDatabase my_db;//数据库对象
    QStringList onlineuserL;
    static OperateDB& get_instance();
    void  connect();
   bool  handleregist(char *name,char *pwd);
   bool  handlelogin(char *name,char *pwd);
   void  handleOffline(const char*name);
   int   handlefinduser(const char*name);
   int   handleaddfriend(char*curname,char*tarname);
   bool  handledelfriend(char*curname,char*tarname);
   void agreeaddfriend(char*curname,char*tarname);
   QStringList handleonlineuser();
   QStringList handleflushonlineuser(char * curname);
     ~OperateDB();
private:
    explicit OperateDB(QObject *parent = nullptr);
    OperateDB(const OperateDB&instance)=delete;
    OperateDB operator=(const OperateDB&)=delete;
signals:

};

#endif // OPERATEDB_H
