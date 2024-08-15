#include "client.h"
#include "file.h"
#include "ui_file.h"
#include"protocol.h"
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>

File::File(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::File)
{
    ui->setupUi(this);
    m_strcurpath=QString("%1/%2").
            arg(Client::getInstance().getpath())
            .arg(Client::getInstance().m_username);
    m_userpath=m_strcurpath;
    m_bupload=false;
    flushfile();
    m_pShareFile=new ShareFile;
}

File::~File()
{
    delete ui;
    delete m_pShareFile;
}

void File::flushfile()
{
    PDU *pdu=mkPDU(m_strcurpath.toStdString().size()+1);
    pdu->uiMsgType=ENUM_MSG_FLUSHFILE_REQUEST;
    memcpy(pdu->caMsg,m_strcurpath.toStdString().c_str(),m_strcurpath.toStdString().size());
    Client::getInstance().getsocket().write((char*)pdu,pdu->uiPDUlen);
    free(pdu);
    pdu=NULL;
}

void File::uploadfile()
{
    QFile file(m_uploadpath);
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::warning(this,"上传文件","打开文件失败");
        return;
    }
    m_bupload=true;
    PDU *datapdu=mkPDU(4096);
    datapdu->uiMsgType=ENUM_MSG_UPLOADFILE_DATA_REQUEST;
    qint64 ret=0;
    while(true)
    {
        ret=file.read(datapdu->caMsg,4096);
        if(ret==0)
        {
            break;
        }
        if(ret<0)
        {
            QMessageBox::warning(this,"上传文件","打开文件失败");

        }
        datapdu->uiMsglen=ret;
        datapdu->uiPDUlen=ret+sizeof(PDU);
        Client::getInstance().getsocket().write((char*)datapdu,datapdu->uiPDUlen);
    }
    m_bupload=false;
    file.close();
    free(datapdu);
    datapdu=NULL;
}

ShareFile *File::getsharefile()
{
    return m_pShareFile;
}

void File::updateFilelist(QList<FileInfo *> pFilelist)
{
    foreach(FileInfo *pFileinfo,m_filelist)
    {
        delete pFileinfo;
    }
    m_filelist.clear();
    m_filelist=pFilelist;
    ui->listWidget_file->clear();
    foreach(FileInfo *pFileinfo,pFilelist)
    {
        QListWidgetItem *pitem=new QListWidgetItem;
        if(pFileinfo->iFileType==0)
        {
            pitem->setIcon(QIcon(QPixmap(":/contents.png")));
        }
        else if(pFileinfo->iFileType==1)
        {
            pitem->setIcon(QIcon(QPixmap(":/file.png")));
        }
        pitem->setText(pFileinfo->name);
        qDebug()<<pFileinfo->name;
        ui->listWidget_file->addItem(pitem);
    }

}

void File::on_mkdir_PB_clicked()
{
    QString strnewdir=QInputDialog::getText(this,"新建文件夹","文件夹名");
    if(strnewdir.isEmpty()||strnewdir.toStdString().size()>32)
        {
            QMessageBox::warning(this,"创建错误","请输入文件名或文件名过长");
            return;
        }
        PDU *pdu=mkPDU(m_strcurpath.toStdString().size());
        pdu->uiMsgType=ENUM_MSG_MKDIRFILE_REQUEST;
        memcpy(pdu->caData,strnewdir.toStdString().c_str(),32);
        memcpy(pdu->caMsg,m_strcurpath.toStdString().c_str(),m_strcurpath.toStdString().size());
        Client::getInstance().getsocket().write((char*)pdu,pdu->uiPDUlen);
        free(pdu);
        pdu=NULL;
}



void File::on_delfile_PB_clicked()
{
    flushfile();
}

void File::on_deletefile_PB_clicked()
{
    QListWidgetItem *pitem=ui->listWidget_file->currentItem();
    if(pitem==NULL)
    {
        QMessageBox::warning(this,"删除文件夹","请选择要删除的文件");
        return;
    }
    QString strDelfilename=pitem->text();
    foreach(FileInfo *pfileinfo,m_filelist)
    {
        if(pfileinfo->name==strDelfilename &&pfileinfo->iFileType!=0)
        {
            QMessageBox::warning(this,"删除文件夹","选择的不是文件夹");
            return;
        }
    }
    int ret=QMessageBox::question(this,"删除文件夹",QString("是否确定删除%1文件夹").arg(strDelfilename));
    if(ret!=QMessageBox::Yes)
    {
        return;
    }
    QString strpath=m_strcurpath+"/"+strDelfilename;
    PDU *pdu=mkPDU(strpath.toStdString().size()+1);
    pdu->uiMsgType=ENUM_MSG_DELDIR_REQUEST;
    memcpy(pdu->caMsg,strpath.toStdString().c_str(),strpath.toStdString().size());
    Client::getInstance().getsocket().write((char*)pdu,pdu->uiPDUlen);
    free(pdu);
    pdu=NULL;
}

void File::on_delfile_PB_2_clicked()
{
    QListWidgetItem *pitem=ui->listWidget_file->currentItem();
    if(pitem==NULL)
    {
        QMessageBox::warning(this,"删除文件","请选择要删除的文件");
        return;
    }
    QString strDelfilename=pitem->text();
    foreach(FileInfo *pfileinfo,m_filelist)
    {
        if(pfileinfo->name==strDelfilename &&pfileinfo->iFileType!=1)
        {
            QMessageBox::warning(this,"删除文件","选择的不是文件");
            return;
        }
    }
    int ret=QMessageBox::question(this,"删除文件",QString("是否确定删除%1文件").arg(strDelfilename));
    if(ret!=QMessageBox::Yes)
    {
        return;
    }
    QString strpath=m_strcurpath+"/"+strDelfilename;
    PDU *pdu=mkPDU(strpath.toStdString().size()+1);
    pdu->uiMsgType=ENUM_MSG_DELFILE_REQUEST;
    memcpy(pdu->caMsg,strpath.toStdString().c_str(),strpath.toStdString().size());
    Client::getInstance().getsocket().write((char*)pdu,pdu->uiPDUlen);
    free(pdu);
    pdu=NULL;
}

void File::on_rename_PB_clicked()
{
    QListWidgetItem *Pitem=ui->listWidget_file->currentItem();
    if(Pitem==NULL)
    {
        QMessageBox::warning(this,"重命名文件","请选择要重命名的文件");
        return;
    }
    QString stroldfilename=Pitem->text();
    QString strnewfilename=QInputDialog::getText(this,"重命名文件","文件名");
    if(strnewfilename.isEmpty()||strnewfilename.toStdString().size()>32)
    {
        QMessageBox::warning(this,"重命名文件","文件命名非法");
        return;
    }
    PDU *pdu=mkPDU(m_strcurpath.toStdString().size()+1);
    pdu->uiMsgType=ENUM_MSG_RENAMEFILE_REQUEST;
    memcpy(pdu->caData,stroldfilename.toStdString().c_str(),32);
    memcpy(pdu->caData+32,strnewfilename.toStdString().c_str(),32);
    qDebug()<<"stroldfilename"<<stroldfilename<<"strnewfilename"<<strnewfilename;
    memcpy(pdu->caMsg,m_strcurpath.toStdString().c_str(),m_strcurpath.toStdString().size());
    Client::getInstance().getsocket().write((char*)pdu,pdu->uiPDUlen);
    free(pdu);
    pdu=NULL;
}

void File::on_listWidget_file_itemDoubleClicked(QListWidgetItem *item)
{
    QString strdirname=item->text();
    foreach(FileInfo *pfileinfo,m_filelist)
    {
        if(pfileinfo->name==strdirname&&pfileinfo->iFileType!=0)
        {
            QMessageBox::warning(this,"提示","选择的不是文件夹");
            return;
        }
    }
    m_strcurpath=m_strcurpath+"/"+strdirname;
    flushfile();
}

void File::on_return_PB_clicked()
{
    if(m_strcurpath==m_userpath)
    {
        QMessageBox::warning(this,"返回","返回失败:已在顶层目录");
        return;
    }
    int index=m_strcurpath.lastIndexOf('/');
    m_strcurpath.remove(index,m_strcurpath.size()-index);
    flushfile();
}

void File::on_movefile_PB_clicked()
{
    if(ui->movefile_PB->text()=="移动文件"){
     QListWidgetItem *Pitem=ui->listWidget_file->currentItem();
     if(Pitem==NULL)
     {
         QMessageBox::warning(this,"移动文件","请选择要移动的文件");
         return;
     }
     QMessageBox::information(this,"移动文件","请选择要移动的目录");
     ui->movefile_PB->setText("确认/取消");
     m_strmvfilename= Pitem->text();
     qDebug()<<"Pitem->text()"<<Pitem->text();
     m_strmvpath=m_strcurpath+"/"+m_strmvfilename;
     qDebug()<<"m_strmvpath"<<m_strmvpath;
     return;
}
    QListWidgetItem *pitem=ui->listWidget_file->currentItem();
    QString strtarpath;
    QString boxmsg;
    if(pitem==NULL)
    {
        strtarpath=m_strcurpath+"/"+m_strmvfilename;
         qDebug()<<"目标目录1"<<strtarpath;
        boxmsg=QString("是否移动到当前目录下");
    }else{
        foreach(FileInfo *pfileinfo,m_filelist)
        {
            if(pfileinfo->name==pitem->text()&&pfileinfo->iFileType!=0)
            {
                QMessageBox::warning(this,"提示","选择的不是文件夹");
                return;
            }
        }
    strtarpath=m_strcurpath+"/"+pitem->text()+"/"+m_strmvfilename;
    boxmsg=QString("是否移动到已选目录下");
    qDebug()<<"目标目录"<<strtarpath;
    }
    int ret=QMessageBox::information(this,"移动文件",boxmsg,"确认","取消");
    ui->movefile_PB->setText("移动文件");
    if(ret!=0)
    {
        return;
    }
   int srclen=m_strmvpath.toStdString().size();
   int tarlen=strtarpath.toStdString().size();
   PDU *pdu=mkPDU(srclen+tarlen+1);
   pdu->uiMsgType=ENUM_MSG_MOVEFILE_REQUEST;
   memcpy(pdu->caData,&srclen,sizeof(int));
   memcpy(pdu->caData+sizeof(int),&tarlen,sizeof(int));
   memcpy(pdu->caMsg,m_strmvpath.toStdString().c_str(),srclen);
   memcpy(pdu->caMsg+srclen,strtarpath.toStdString().c_str(),srclen);
   Client::getInstance().getsocket().write((char*)pdu,pdu->uiPDUlen);
   free(pdu);
   pdu=NULL;

}
void File::on_upload_PB_clicked()
{
    if(m_bupload)
    {
        QMessageBox::warning(this,"上传文件","已有文件上传请稍等");
    }
    m_uploadpath=QFileDialog::getOpenFileName();
    int index=m_uploadpath.lastIndexOf('/');
    QString filename=m_uploadpath.right(m_uploadpath.toStdString().size()-index-1);
    QFile file(m_uploadpath);
    qint64 filesize=file.size();
    PDU *pdu =mkPDU(m_strcurpath.toStdString().size());
    pdu->uiMsgType=ENUM_MSG_UPLOADFILE_REQUEST;
    memcpy(pdu->caData,filename.toStdString().c_str(),32);
    memcpy(pdu->caData+32,&filesize,32);
    memcpy(pdu->caMsg,m_strcurpath.toStdString().c_str(),m_strcurpath.toStdString().size());

    Client::getInstance().getsocket().write((char*)pdu,pdu->uiPDUlen);
    free(pdu);
    pdu=NULL;
}

void File::on_sharefile_PB_clicked()
{
    QListWidgetItem *pitem=ui->listWidget_file->currentItem();
    if(pitem==NULL)
    {
        QMessageBox::warning(this,"分享文件","请选择要分享的文件");
        return;
    }
    m_strsharefile=pitem->text();
    m_pShareFile->updatefriend_LW();
    if(m_pShareFile->isHidden())
    {
        m_pShareFile->show();
    }
}
