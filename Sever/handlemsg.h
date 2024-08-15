#ifndef HANDLEMSG_H
#define HANDLEMSG_H
#include"protocol.h"
#include "operatedb.h"
#include"QFile"
class HandleMsg
{
public:
    HandleMsg();
    PDU *  rigster(PDU* pdu);
    PDU *  Login(PDU* pdu,QString &m_socketusername);
    PDU *  Finduser(PDU* pdu);
    PDU *  Onlineuser();
    PDU *  Addfriend(PDU *pdu);
    PDU *  Agreefriend(PDU *pdu);
    PDU *  Flushfriend(PDU *pdu);
    PDU *  Newmkdirfile(PDU *pdu);
    PDU *  Flushfile(PDU *pdu);
    PDU *  Deldir(PDU *pdu);
    PDU *  Delfile(PDU *pdu);
    PDU *  Renamefile(PDU *pdu);
    PDU *  Delfriend(PDU *pdu);
    PDU *  Movefile(PDU *pdu);
    PDU *  uploadfile(PDU *pdu);
    PDU *  uploadfiledata(PDU *pdu);
    PDU *  Sharefile(PDU *pdu);
    PDU *  Sharefileagree(PDU *pdu);
    void  Chatfriend(PDU *pdu);
    QFile m_uploadfile;
    qint64 m_iuploadtotal;
    qint64 m_iuploadreceived;
    bool m_bupload;
};

#endif // HANDLEMSG_H
