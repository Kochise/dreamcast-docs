// cncb.h -- defines the data type CNCB as a helper for CNetBIOS

#include <nb30.h>

#define MAXMACHINENAME 16


#define LANA_NUM 0

// compound structures

typedef struct ADAPTER_STATUS_BLOCK
{ADAPTER_STATUS asb_header;
 NAME_BUFFER asb_Names[NCBNAMSZ];
} ADAPTER_STATUS_BLOCK, *PADAPTER_STATUS_BLOCK;

typedef struct SESSION_INFO_BLOCK
{SESSION_HEADER sib_header;
 SESSION_BUFFER sib_Names[NCBNAMSZ];
} SESSION_INFO_BLOCK, *PSESSION_INFO_BLOCK;

class CNCB
{ 
private:
NCB m_NCB;
public:
// constructor
CNCB();
// helper function
void ClearNCB();
UCHAR GetLSN();
WORD GetLength();
void Fill(CNCB ncbSource);
UCHAR GetCommand();
// Name Management Services
UCHAR AddName(PSTR pName);
UCHAR AddGroupName(PSTR pName);
UCHAR DeleteName(PSTR pName);
UCHAR FindName();

// Data Transfer Services
UCHAR Call(PSTR pWe,PSTR pTheOther,UCHAR wSendTO,UCHAR wRecvTO);   // fill in parameters later;;;
UCHAR Listen(PSTR pWe,PSTR pTheOther,UCHAR wSendTO,UCHAR wRecvTO);
UCHAR Hangup(UCHAR wSessionNumber);
// Connectionless Data Transfer
UCHAR Cancel();
UCHAR Send(UCHAR wSessionNumber,LPSTR lpPacket, UINT wLength);
UCHAR SendNoAck();
UCHAR SendDatagram(UCHAR wSessionNumber,LPSTR lpPacket, WORD wLength);
UCHAR SendBroadcastDatagram();
UCHAR Receive(UCHAR wSessionNumber,LPSTR lpPacket, UINT wLength);
UCHAR ReceiveAny();
UCHAR ReceiveDatagram(UCHAR wSessionNumber,LPSTR lpPacket, WORD wLength);
UCHAR ReceiveBroadcastDatagram();
UCHAR ChainSend();
UCHAR ChainSendNoAck();

// General Purpose Services
UCHAR Reset(UCHAR wSessions, UCHAR wNCBs);
UCHAR GetAdapterStatus(PSTR pName);
UCHAR GetSessionStatus(PSTR pName);
UCHAR EnumerateAdapters();
UCHAR StatusAlert();
UCHAR Action();
};
