#include "handlemsg.h"
#include<QDebug>
#include <QDir>
#include "mytcpsever.h"
#include "server.h"
HandleMsg::HandleMsg()
{
   m_bupload=false;
}

PDU *HandleMsg::rigster(PDU *pdu)
{
    char username_regist[32]={'\0'};
            char password_regist[32]={'\0'};
            memcpy(username_regist,pdu->caData,32);
            memcpy(password_regist,pdu->caData+32,32);
            qDebug()<<"用户名:"<<username_regist<<"密码:"<<password_regist;

            PDU *regist_resPdu=mkPDU(0);
            regist_resPdu->uiMsgType=ENUM_MSG_REGIST_RESPEND;
            bool ret;
            ret=OperateDB::get_instance().handleregist(username_regist,password_regist);
            if(ret>0)
            {
               QDir dir;
               dir.mkdir(QString("%1/%2").arg(Server::getinstance().getRootPath()).arg(username_regist));
            }
            memcpy(regist_resPdu->caData,&ret,sizeof(bool));
            return regist_resPdu;
}

PDU *HandleMsg::Login(PDU *pdu,QString &m_socketusername)
{
    char username_login[32]={'\0'};
    char password_login[32]={'\0'};
    memcpy(username_login,pdu->caData,32);
    memcpy(password_login,pdu->caData+32,32);
    qDebug()<<"用户名:"<<username_login<<"密码:"<<password_login;
    m_socketusername=username_login;
    PDU *login_resPdu=mkPDU(0);
    login_resPdu->uiMsgType=ENUM_MSG_LOGIN_RESPEND;
    bool ret_login;
    ret_login=OperateDB::get_instance().handlelogin(username_login,password_login);
    memcpy(login_resPdu->caData,&ret_login,sizeof(bool));
    return login_resPdu;
}

PDU *HandleMsg::Finduser(PDU *pdu)
{
    char username_find[32]={'\0'};
    qDebug()<<"---------------------------------";
    memcpy(username_find,pdu->caData,32);
    qDebug()<<"用户名:"<<username_find;
    PDU *finduser_resPdu=mkPDU(0);
    finduser_resPdu->uiMsgType=ENUM_MSG_FINDUSER_RESPEND;
    int ret_finduser;
    ret_finduser=OperateDB::get_instance().handlefinduser(username_find);
    qDebug()<<ret_finduser<<"---------------------------------";
    memcpy(finduser_resPdu->caData,username_find,32);
    memcpy(finduser_resPdu->caData+32,&ret_finduser,sizeof(int));

    return finduser_resPdu;
}

PDU *HandleMsg::Onlineuser()
{
    QStringList socketonlineuser=OperateDB::get_instance().handleonlineuser();
    uint uiMsglen=socketonlineuser.size()*32;
    PDU *onlineuser_resPdu=mkPDU(uiMsglen);
        onlineuser_resPdu->uiMsgType=ENUM_MSG_ONLINEUSER_RESPEND;
    for(int i=0;i<socketonlineuser.size();i++)
    {
        //qDebug()<<socketonlineuser.at(i);

         memcpy(onlineuser_resPdu->caMsg+i*32,socketonlineuser.at(i).toStdString().c_str(),32);
    }
    return onlineuser_resPdu;
}

PDU *HandleMsg::Addfriend(PDU *pdu)
{
    char curname[32]={'\0'};
    char tarname[32]={'\0'};
    qDebug()<<"------------------11";
    memcpy(curname,pdu->caData,32);
    memcpy(tarname,pdu->caData+32,32);
    qDebug()<<"目标用户:"<<tarname<<"当前用户:"<<curname;
    PDU *resPdu=mkPDU(0);
    resPdu->uiMsgType=ENUM_MSG_ADDFRIEND_RESPEND;
    int ret;
    ret=OperateDB::get_instance().handleaddfriend(curname,tarname);
    qDebug()<<ret;
    if(ret>0)
    {
        mytcpsever::getInstance().resend(tarname,pdu);
    }
    memcpy(resPdu->caData,&ret,sizeof(int));
    return resPdu;
}

PDU *HandleMsg::Agreefriend(PDU *pdu)
{
    char curname[32]={'\0'};
    char tarname[32]={'\0'};
    qDebug()<<"------------------11";
    memcpy(curname,pdu->caData,32);
    memcpy(tarname,pdu->caData+32,32);
    qDebug()<<"目标用户:"<<tarname<<"当前用户:"<<curname;
    PDU *resPdu=mkPDU(0);
    OperateDB::get_instance().agreeaddfriend(curname,tarname);
    resPdu->uiMsgType=ENUM_MSG_ADDFRIEND_AGREE_RESPEND;
    mytcpsever::getInstance().resend(curname,pdu);
    return resPdu;
}

PDU *HandleMsg::Flushfriend(PDU *pdu)
{
    char curname[32]={'\0'};
    memcpy(curname,pdu->caData,32);
    qDebug()<<"目标用户:"<<curname;
    QStringList socketonlineuser=OperateDB::get_instance().handleflushonlineuser(curname);
    uint uiMsglen=socketonlineuser.size()*32;
    PDU *onlineuser_resPdu=mkPDU(uiMsglen);
        onlineuser_resPdu->uiMsgType= ENUM_MSG_FLUSHFRIEND_AGREE_RESPEND;
    for(int i=0;i<socketonlineuser.size();i++)
    {
        //qDebug()<<socketonlineuser.at(i);

         memcpy(onlineuser_resPdu->caMsg+i*32,socketonlineuser.at(i).toStdString().c_str(),32);
    }
    return onlineuser_resPdu;
}

PDU *HandleMsg::Newmkdirfile(PDU *pdu)
{
    QString strcurpath=pdu->caMsg;
    PDU *respdu=mkPDU(0);
    respdu->uiMsgType=ENUM_MSG_MKDIRFILE_RESPEND;
    bool res=false;
    QDir dir;
    if(!dir.exists(strcurpath))
    {
        memcpy(respdu->caData,&res,sizeof(bool));
        return respdu;
    }
    QString strNewpath=QString("%1/%2").arg(strcurpath).arg(pdu->caData);
    qDebug()<<"新路径"<<strNewpath;
    if(dir.exists(strNewpath)||!dir.mkdir(strNewpath))
    {
        memcpy(respdu->caData,&res,sizeof(bool));
        return respdu;
    }
    res=true;
    memcpy(respdu->caData,&res,sizeof(bool));
    return respdu;
}

PDU *HandleMsg::Flushfile(PDU *pdu)
{
    QString strPath=pdu->caMsg;
    QDir dir(strPath);
    QFileInfoList fileInfoList=dir.entryInfoList();
    int Ifilecount=fileInfoList.size();

    PDU *respdu=mkPDU(sizeof(FileInfo)*(Ifilecount-2));
    respdu->uiMsgType=ENUM_MSG_FLUSHFILE_RESPEND;
    FileInfo* Pfileinfo=NULL;
    QString strFilename;
    for(int i=0,j=0;i<Ifilecount;i++)
    {
        strFilename=fileInfoList[i].fileName();
        if(strFilename==QString(".")||strFilename==QString(".."))
        {
                continue;
        }
        Pfileinfo=(FileInfo*)(respdu->caMsg)+j++;
        memcpy(Pfileinfo->name,strFilename.toStdString().c_str(),32);
        if(fileInfoList[i].isDir())
        {
            Pfileinfo->iFileType=0;//目录
        }
        else if(fileInfoList[i].isFile())
        {
            Pfileinfo->iFileType=1;

        }
        qDebug()<<Pfileinfo->name
               <<Pfileinfo->iFileType;
    }
    return respdu;
}

PDU *HandleMsg::Deldir(PDU *pdu)
{
    QFileInfo fileinfo(pdu->caMsg);
     bool ret;
    if(fileinfo.isDir())
    {
        QDir dir;
        dir.setPath(pdu->caMsg);
        ret=dir.removeRecursively();
    }
    PDU *respdu=mkPDU(0);
    respdu->uiMsgType=ENUM_MSG_DELDIR_RESPEND;
    memcpy(respdu->caData,&ret,sizeof(bool));
    return respdu;
}

PDU *HandleMsg::Delfile(PDU *pdu)
{
    QFileInfo fileinfo(pdu->caMsg);
     bool ret;
    if(fileinfo.isFile())
    {
        QDir dir;
        ret=dir.remove(pdu->caMsg);
    }
    PDU *respdu=mkPDU(0);
    respdu->uiMsgType=ENUM_MSG_DELFILE_RESPEND;
    memcpy(respdu->caData,&ret,sizeof(bool));
    return respdu;
}

PDU *HandleMsg::Renamefile(PDU *pdu)
{
    char caoldfilename[32]={'\0'};
    char canewfilename[32]={'\0'};
    memcpy(caoldfilename,pdu->caData,32);
    memcpy(canewfilename,pdu->caData+32,32);
    char *path=pdu->caMsg;
    QString strOldpath=QString("%1/%2").arg(path).arg(caoldfilename);
    QString strNewpath=QString("%1/%2").arg(path).arg(canewfilename);
    qDebug()<<"strOldpath"<<strOldpath<<"strNewpath"<<strNewpath;
    QDir dir;
    bool ret=dir.rename(strOldpath,strNewpath);

    PDU *respdu=mkPDU(0);
    respdu->uiMsgType=ENUM_MSG_RENAMEFILE_RESPEND;
    memcpy(respdu->caData,&ret,sizeof(bool));
    return respdu;

}

PDU *HandleMsg::Delfriend(PDU *pdu)
{
    char curname[32]={'\0'};
    char tarname[32]={'\0'};
    memcpy(curname,pdu->caData,32);
    memcpy(tarname,pdu->caData+32,32);
    PDU *resPdu=mkPDU(0);
    resPdu->uiMsgType=ENUM_MSG_DELFRIEND_RESPEND;
    bool ret;
    ret=OperateDB::get_instance().handledelfriend(curname,tarname);
    memcpy(resPdu->caData,&ret,sizeof(int));
    return resPdu;
}

PDU *HandleMsg::Movefile(PDU *pdu)
{
    int srclen=0;
    int tarlen=0;
    memcpy(&srclen,pdu->caData,sizeof(int));
    memcpy(&tarlen,pdu->caData+sizeof(int),sizeof(int));
    char *psrcpath=new char[srclen+1];
    char *ptarpath=new char[tarlen+1];
    memset(psrcpath,'\0',srclen+1);
    memset(ptarpath,'\0',tarlen+1);
    memcpy(psrcpath,pdu->caMsg,srclen);
    memcpy(ptarpath,pdu->caMsg+srclen,tarlen);
    bool ret=QFile::rename(psrcpath,ptarpath);
    PDU *respdu=mkPDU(0);
    respdu->uiMsgType=ENUM_MSG_MOVEFILE_RESPEND;
    memcpy(respdu->caData,&ret,sizeof(bool));
    delete [] psrcpath;
    delete [] ptarpath;
    psrcpath=NULL;
    ptarpath=NULL;
    return respdu;
}

PDU *HandleMsg::uploadfile(PDU *pdu)
{
    PDU *respdu=mkPDU(0);
    respdu->uiMsgType=ENUM_MSG_UPLOADFILE_RESPEND;
    int ret=0;
    if(m_bupload)
    {
        qDebug()<<"m_bupload";
        ret=1;
        memcpy(respdu->caData,&ret,sizeof(int));
        return respdu;
    }
    char cafilename[32]={'\0'};
    qint64 filesize=0;
    memcpy(cafilename,pdu->caData,32);
    memcpy(&filesize,pdu->caData+32,sizeof(qint64));
    QString strpath=QString("%1/%2").arg(pdu->caMsg).arg(cafilename);
    qDebug()<<"uploadstrpath"<<strpath;
    m_uploadfile.setFileName(strpath);
    if(m_uploadfile.open(QIODevice::WriteOnly))
    {
        m_bupload=true;
        m_iuploadtotal=filesize;
        m_iuploadreceived=0;
    }else
    {
        qDebug()<<"打开文件失败";
        ret=-1;
    }
    memcpy(respdu->caData,&ret,sizeof(int));
    return respdu;
}

PDU *HandleMsg::uploadfiledata(PDU *pdu)
{
    m_uploadfile.write(pdu->caMsg,pdu->uiMsglen);
    m_iuploadreceived+=pdu->uiMsglen;
    if(m_iuploadreceived<m_iuploadtotal)
    {
        return NULL;
    }
    m_uploadfile.close();
    m_bupload=false;
    PDU *respdu=mkPDU(0);
    respdu->uiMsgType=ENUM_MSG_UPLOADFILE_DATA_RESPEND;
    bool ret=m_iuploadreceived==m_iuploadtotal;
    memcpy(respdu->caData,&ret,sizeof(bool));
    return respdu;
}

PDU *HandleMsg::Sharefile(PDU *pdu)
{
    char cacurname[32]={'\0'};
    int friendnum=0;
    memcpy(cacurname,pdu->caData,32);
    memcpy(&friendnum,pdu->caData+32,sizeof(int));
    int size=friendnum*32;
    PDU *resendpdu=mkPDU(pdu->uiMsglen-size);
    resendpdu->uiMsgType=pdu->uiMsgType;
    memcpy(resendpdu->caData,cacurname,32);
    memcpy(resendpdu->caMsg,pdu->caMsg+size,pdu->uiMsglen-size);
    char carecvname[32]={'\0'};
    for(int i=0;i<friendnum;i++)
    {
        memcpy(carecvname,pdu->caMsg+i*32,32);
        mytcpsever::getInstance().resend(carecvname,resendpdu);
    }
    free(resendpdu);
    resendpdu=NULL;
    PDU *respdu=mkPDU(0);
    respdu->uiMsgType=ENUM_MSG_SHAREFILE_RESPEND;
    return respdu;
}

PDU *HandleMsg::Sharefileagree(PDU *pdu)
{
    QString strSharepath=pdu->caMsg;
    QString strrecvpath=QString("%1/%2").arg(Server::getinstance().getRootPath()).arg(pdu->caData);
    int index=strSharepath.lastIndexOf('/');
    QString filename=strSharepath.right(strSharepath.toStdString().size()-index-1);\
    strrecvpath=strrecvpath+"/"+filename;
    bool ret=QFile::copy(strSharepath,strrecvpath);
    PDU * respdu=mkPDU(0);
    memcpy(pdu->caData,&ret,sizeof(bool));
    respdu->uiMsgType= ENUM_MSG_SHAREFILE_AGREE_RESPEND;
    return respdu;
}

void HandleMsg::Chatfriend(PDU *pdu)
{
    char tarname[32]={'\0'};
    memcpy(tarname,pdu->caData+32,32);
    mytcpsever::getInstance().resend(tarname,pdu);

}
