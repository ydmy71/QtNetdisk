#include"protocol.h"
#include<stdlib.h>
#include<string.h>
PDU *mkPDU(uint uiMsglen)
{
    uint uiPDUlen=sizeof (PDU)+uiMsglen;
    PDU *pdu=(PDU*)malloc(uiPDUlen);
    if(pdu==NULL)
    {
        exit(1);
    }
    memset(pdu,0,uiPDUlen);
    pdu->uiPDUlen=uiPDUlen;
    pdu->uiMsglen=uiMsglen;
    return pdu;
}
