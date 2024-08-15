#include "reshandle.h"
#include"client.h"
#include "index.h"

#include <QMessageBox>
reshandle::reshandle()
{

}

void reshandle::rigster(PDU *pdu)
{
    if(*pdu->caData)
     {
         QMessageBox::information(&Client::getInstance(),"注册","注册成功");
     }
      else{QMessageBox::information(&Client::getInstance(),"注册","注册失败");}
}

void reshandle::Login(PDU *pdu)
{
    if(*pdu->caData)
     {
        Index::getinstance().show();
        Client::getInstance().hide();
         QMessageBox::information(&Client::getInstance(),"登录","登录成功");
            return;
     }
      else{QMessageBox::information(&Client::getInstance(),"登录","登录失败");
       return;}
}

void reshandle::Finduser(PDU *pdu)
{
    char caName[32]={'\0'};
    memcpy(caName,pdu->caData,32);
    int ret;
    memcpy(&ret,pdu->caData+32,sizeof(int));
    Friend *friendpage=Index::getinstance().getFriend();
  if(ret==-1)
   {
       QMessageBox::information(friendpage,"搜索",QString("%1 不存在").arg(caName));
       return;
   }
  if(ret==1)
  {
    int ret= QMessageBox::information(friendpage,"搜索",QString("%1 在线").arg(caName),"添加好友","取消");
    if(ret!=0)
    {
      return;
    }
    PDU *pdu=mkPDU(0);
    pdu->uiMsgType=ENUM_MSG_ADDFRIEND_REQUEST;
    memcpy(pdu->caData,Client::getInstance().m_username.toStdString().c_str(),32);
    memcpy(pdu->caData+32,caName,32);
    Client::getInstance().getsocket().write((char*)pdu,pdu->uiPDUlen);
    free(pdu);
    pdu=NULL;
       return;
  }
  else
  {
    QMessageBox::information(friendpage,"搜索",QString("%1 离线").arg(caName));
       return;
  }
}

void reshandle::Onlineuser(PDU *pdu,QString m_username)
{
    uint uiSize=pdu->uiMsglen/32;
    QStringList userlist;
    char caTmp[32]={'\0'};
    for(uint i=0;i<uiSize;i++)
    {
        memcpy(caTmp,pdu->caMsg+i*32,32);
        if(QString(caTmp)==m_username)
        {
            continue;
        }
        userlist.append(QString(caTmp));
    }
    Index::getinstance().getFriend()->getonlineuser()->update_onlineuser_WigdetList(userlist);
}

void reshandle::Addfriend(PDU *pdu)
{
    int ret;
    memcpy(&ret,pdu->caData,sizeof(int));

  if(ret==-2)
   {
       QMessageBox::information(&Index::getinstance(),"添加好友","您有他的好友");
       return;
   }
  if(ret==-1)
  {
    QMessageBox::information(&Index::getinstance(),"添加好友","服务器内部错误");
       return;
  }
  if(ret==0)
  {
    QMessageBox::information(&Index::getinstance(),"添加好友","离线");
       return;
  }
}

void reshandle::Agreeaddfriendrequst(PDU *pdu)
{
       char caName[32]={'\0'};
       memcpy(caName,pdu->caData,32);
       int ret=QMessageBox::question(&Index::getinstance(),"添加好友",QString("是否同意%1的添加好友请求？").arg(caName));
       if(ret!=QMessageBox::Yes)
       {
           return;
       }
       PDU *respdu=mkPDU(0);
       memcpy(respdu->caData,pdu->caData,64);
       respdu->uiMsgType=ENUM_MSG_ADDFRIEND_AGREE_REQUEST;
       Client::getInstance().getsocket().write((char*)respdu,respdu->uiPDUlen);
       free(respdu);
       respdu=NULL;
}

void reshandle::Agreeaddfriendres(PDU *pdu)
{
    QMessageBox::information(&Index::getinstance(),"添加好友","添加成功");
    Index::getinstance().getFriend()->flushfriend();
}

void reshandle::Flushonlinefriend(PDU *pdu)
{
    uint uiSize=pdu->uiMsglen/32;
    QStringList userlist;
    char caTmp[32]={'\0'};
    for(uint i=0;i<uiSize;i++)
    {
        memcpy(caTmp,pdu->caMsg+i*32,32);

        userlist.append(QString(caTmp));
    }
    Index::getinstance().getFriend()->updatafriend(userlist);
}

void reshandle::mkdirfile(PDU *pdu)
{
    bool ret;
    memcpy(&ret,pdu->caData,sizeof(bool));
    if(ret)
     {
       \
        QMessageBox::information(Index::getinstance().getFile(),"新建文件","新建成功");
        Index::getinstance().getFile()->flushfile();
            return;
     }
      else
    {
        QMessageBox::information(Index::getinstance().getFile(),"新建文件","新建失败");
       return;
    }
}

void reshandle::flushfile(PDU *pdu)
{
    int icount=pdu->uiMsglen/sizeof(FileInfo);
    qDebug()<<"icount"<<icount<<"uimsglen"<<pdu->uiMsglen<<"sizeof(fileinfo)"<<sizeof(FileInfo);
    QList<FileInfo  *>pfilelist;
    for(int i=0;i<icount;i++)
    {
        FileInfo *pfileinfo=new FileInfo;
        memcpy(pfileinfo,pdu->caMsg+i*sizeof(FileInfo),sizeof(FileInfo));
        qDebug()<<pfileinfo;
        pfilelist.append(pfileinfo);
    }
    Index::getinstance().getFile()->updateFilelist(pfilelist);
}

void reshandle::deldir(PDU *pdu)
{
    bool ret;
    memcpy(&ret,pdu->caData,sizeof(bool));
    if(ret)
     {
       \
        QMessageBox::information(Index::getinstance().getFile(),"删除文件夹","删除成功");
        Index::getinstance().getFile()->flushfile();
            return;
     }
      else
    {
        QMessageBox::information(Index::getinstance().getFile(),"删除文件夹","删除失败");
       return;
    }
}

void reshandle::Delfile(PDU *pdu)
{
    bool ret;
    memcpy(&ret,pdu->caData,sizeof(bool));
    if(ret)
     {

        QMessageBox::information(Index::getinstance().getFile(),"删除文件","删除成功");
        Index::getinstance().getFile()->flushfile();
            return;
     }
      else
    {
        QMessageBox::information(Index::getinstance().getFile(),"删除文件","删除失败");
       return;
    }
}

void reshandle::renamefile(PDU *pdu)
{
    bool ret;
    memcpy(&ret,pdu->caData,sizeof(bool));
    if(ret)
     {
        Index::getinstance().getFile()->flushfile();
            return;
     }
      else
    {
        QMessageBox::information(Index::getinstance().getFile(),"重命名文件","重命名失败");
       return;
    }
}

void reshandle::Delfriend(PDU *pdu)
{
    bool ret;
    memcpy(&ret,pdu->caData,sizeof(bool));
    if(ret)
     {

        QMessageBox::information(Index::getinstance().getFriend(),"删除好友","删除成功");
       Client::getInstance().hide();
     }
      else
    {
        QMessageBox::information(Index::getinstance().getFriend(),"删除好友","删除失败");
    }
    Index::getinstance().getFriend()->flushfriend();

}

void reshandle::movefile(PDU *pdu)
{
    bool ret;
    memcpy(&ret,pdu->caData,sizeof(bool));
    if(ret)
     {
        qDebug()<<"ydwj";
        Index::getinstance().getFile()->flushfile();
                return;
     }
      else
    {
        QMessageBox::information(Index::getinstance().getFile(),"移动文件","移动失败");
       return;
    }
}

void reshandle::uploadfile(PDU *pdu)
{
    int ret;
    memcpy(&ret,pdu->caData,sizeof(int));
    if(ret==0)
    {
        Index::getinstance().getFile()->uploadfile();
        return;
    }
  if(ret==1)
   {
       QMessageBox::information(&Index::getinstance(),"上传文件","已有文件上传");
       return;
   }
  if(ret==-1)
  {
    QMessageBox::information(&Index::getinstance(),"上传文件","打开文件失败");
       return;
  }
}

void reshandle::uploaddata(PDU *pdu)
{
    bool ret;
    memcpy(&ret,pdu->caData,sizeof(bool));
    if(ret)
     {
         QMessageBox::information(Index::getinstance().getFile(),"上传文件","上传文件成功");
        Index::getinstance().getFile()->flushfile();
     }
      else
    {
        QMessageBox::information(Index::getinstance().getFile(),"移动文件","移动失败");
       return;
    }
    Index::getinstance().getFile()->m_bupload=false;
}

void reshandle::sharefile(PDU *pdu)
{
    QMessageBox::information(Index::getinstance().getFile(),"分享文件","文件已分享");
}

void reshandle::sharefileRequest(PDU *pdu)
{
    QString strsharepath=pdu->caMsg;
    int index=strsharepath.lastIndexOf('/');
    QString strfilename=strsharepath.right(strsharepath.size()-index-1);
    int ret=QMessageBox::question(
                Index::getinstance().getFile()->getsharefile(),
                "分享文件",
                QString("%1分享文件/%2\n是否接收文件").arg(pdu->caData).arg(strfilename)
                );
    if(ret!=QMessageBox::Yes)
    {
        return;
    }
    PDU *respdu=mkPDU(pdu->uiMsglen);
    respdu->uiMsgType=ENUM_MSG_SHAREFILE_AGREE_REQUEST;
    memcpy(respdu->caData,Client::getInstance().m_username.toStdString().c_str(),32);
    memcpy(respdu->caMsg,pdu->caMsg,pdu->uiMsglen);
    Client::getInstance().getsocket().write((char*)respdu,respdu->uiPDUlen);
    free(respdu);
    respdu=NULL;
}

void reshandle::sharefileAgree(PDU *pdu)
{
    bool ret;
    memcpy(&ret,pdu->caData,sizeof(bool));
    if(ret)
     {
         QMessageBox::information(Index::getinstance().getFile(),"分享文件","分享文件成功");
        Index::getinstance().getFile()->flushfile();
     }
      else
    {
        QMessageBox::information(Index::getinstance().getFile(),"分享文件","分享文件失败");
       return;
    }
}

void reshandle::chat(PDU *pdu)
{
    Chat * c=Index::getinstance().getFriend()->getchat();
    if(c->isHidden())
    {
        c->show();
    }
    char cachatname[32]={'\0'};
    memcpy(cachatname,pdu->caData,32);
    QString strmsg=QString("%1;%2").arg(cachatname).arg((pdu->caMsg));
    c->m_strchatname=cachatname;
    c->update_le(strmsg);
}


