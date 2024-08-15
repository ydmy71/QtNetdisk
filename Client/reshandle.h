#ifndef RESHANDLE_H
#define RESHANDLE_H
#include"protocol.h"
#include <QString>
class reshandle
{
public:
    reshandle();
    void  rigster(PDU* pdu);
    void Login(PDU* pdu);
    void  Finduser(PDU* pdu);
    void  Onlineuser(PDU* pdu,QString m_username);
    void  Addfriend(PDU *pdu);
    void Agreeaddfriendrequst(PDU *pdu);
    void Agreeaddfriendres(PDU *pdu);
    void Flushonlinefriend(PDU *pdu);
    void mkdirfile(PDU *pdu);
    void flushfile(PDU *pdu);
    void deldir(PDU *pdu);
    void Delfile(PDU *pdu);
    void renamefile(PDU * pdu);
    void Delfriend(PDU *pdu);
    void movefile(PDU *pdu);
    void uploadfile(PDU *pdu);
    void uploaddata(PDU *pdu);
    void sharefile(PDU *pdu);
    void sharefileRequest(PDU *pdu);
    void sharefileAgree(PDU *pdu);
    void chat(PDU *pdu);
};

#endif // RESHANDLE_H
