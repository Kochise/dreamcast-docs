// cncb.cpp -- implements the data type CNCB as a helper for CNetBIOS
#include <windows.h>
#include "cncb.h"

CNCB::CNCB()
{
};

void CNCB::ClearNCB()
{memset((void *)&m_NCB,0,sizeof(NCB));
};

UCHAR CNCB::GetLSN()
{ return m_NCB.ncb_lsn;
};

WORD CNCB::GetLength()
{ return m_NCB.ncb_length;
};

void CNCB::Fill(CNCB ncbSource)
{memcpy(&m_NCB,&ncbSource.m_NCB,sizeof(NCB));
};

UCHAR CNCB::GetCommand()
{
 return m_NCB.ncb_command;
};


/*********************************************************/
UCHAR CNCB::AddName(PSTR pName)
{ClearNCB();
 m_NCB.ncb_command = NCBADDNAME;
 m_NCB.ncb_lana_num = LANA_NUM;
 strcpy((char *)&m_NCB.ncb_name,pName);
 return (Netbios(&m_NCB));
};
/*********************************************************/
UCHAR CNCB::AddGroupName(PSTR pName)
{ClearNCB();
 m_NCB.ncb_command = NCBADDGRNAME;
 m_NCB.ncb_lana_num = LANA_NUM;
 strcpy((char *)&m_NCB.ncb_name,pName);
 return (Netbios(&m_NCB));
};
/*********************************************************/
UCHAR CNCB::DeleteName(PSTR pName)
{ClearNCB();
 m_NCB.ncb_command = NCBDELNAME;
 m_NCB.ncb_lana_num = LANA_NUM;
 strcpy((char *)&m_NCB.ncb_name,pName);
 return (Netbios(&m_NCB));
};

/*********************************************************/
UCHAR CNCB::FindName()
{ return 0;};

// Data Transfer Services
/*********************************************************/
UCHAR CNCB::Call(PSTR pWe,PSTR pTheOther,UCHAR wSendTO,UCHAR wRecvTO)
{ClearNCB();
 strncpy((char *)&m_NCB.ncb_name,pWe,MAXMACHINENAME);
 strncpy((char *)&m_NCB.ncb_callname,pTheOther,MAXMACHINENAME);
 m_NCB.ncb_rto = wRecvTO;
 m_NCB.ncb_sto = wSendTO;
 m_NCB.ncb_command = NCBCALL;
 return (Netbios(&m_NCB));
};

/*********************************************************/
UCHAR CNCB::Listen(PSTR pWe,PSTR pTheOther,UCHAR wSendTO,UCHAR wRecvTO)
{ClearNCB();
 strncpy((char *)&m_NCB.ncb_name,pWe,MAXMACHINENAME);
 strncpy((char *)&m_NCB.ncb_callname,pTheOther,MAXMACHINENAME);
 m_NCB.ncb_rto = (UCHAR)wRecvTO;
 m_NCB.ncb_sto = (UCHAR)wSendTO;
 m_NCB.ncb_command = NCBLISTEN;
 return (Netbios(&m_NCB));
};
/*********************************************************/
UCHAR CNCB::Hangup(UCHAR wSessionNumber)
{ClearNCB();
 m_NCB.ncb_command = NCBHANGUP;
 m_NCB.ncb_lsn = wSessionNumber;
 return (Netbios(&m_NCB));
};
// Connectionless Data Transfer
/*********************************************************/
UCHAR CNCB::Cancel()
{
 CNCB cbCanceller;
 cbCanceller.ClearNCB();
 cbCanceller.m_NCB.ncb_buffer = (unsigned char *)&m_NCB;
 cbCanceller.m_NCB.ncb_length = sizeof(NCB);
 cbCanceller.m_NCB.ncb_command = NCBCANCEL;
 return (Netbios(&cbCanceller.m_NCB));

};
/*********************************************************/
UCHAR CNCB::Send(UCHAR wSessionNumber,LPSTR lpPacket, UINT wLength)
{ClearNCB();
 if (wLength > 0xffff) RaiseException(EXCEPTION_ACCESS_VIOLATION,0,0,NULL);
 m_NCB.ncb_command = NCBSEND;
 m_NCB.ncb_lsn = wSessionNumber;
 m_NCB.ncb_length = wLength;
 m_NCB.ncb_buffer = (unsigned char *)lpPacket;
 return (Netbios(&m_NCB));
};
/*********************************************************/
 UCHAR CNCB::SendNoAck()
 { return 0;};
/*********************************************************/
UCHAR CNCB::SendDatagram(UCHAR wSessionNumber,LPSTR lpPacket, WORD wLength)
{ClearNCB();
 m_NCB.ncb_command = NCBDGSEND;
 m_NCB.ncb_lsn = wSessionNumber;
 m_NCB.ncb_length = wLength;
 m_NCB.ncb_buffer = (unsigned char *)lpPacket;
 return (Netbios(&m_NCB));
}; 
/*********************************************************/
UCHAR CNCB::SendBroadcastDatagram()
{ return 0;};
/*********************************************************/
UCHAR CNCB::Receive(UCHAR wSessionNumber,LPSTR lpPacket, UINT wLength)
{ClearNCB();
 m_NCB.ncb_command = NCBRECV;
 m_NCB.ncb_lsn = wSessionNumber;
 // do not hardcode that!!!
 if (wLength > 0xffff) m_NCB.ncb_length = 0xffff; else
 m_NCB.ncb_length = wLength;
 m_NCB.ncb_buffer = (unsigned char *)lpPacket;
 return (Netbios(&m_NCB));
};


UCHAR CNCB::ReceiveDatagram(UCHAR wSessionNumber,LPSTR lpPacket, WORD wLength)
{ClearNCB();
 m_NCB.ncb_command = NCBDGRECV;
 m_NCB.ncb_lsn = wSessionNumber;
 m_NCB.ncb_length = wLength;
 m_NCB.ncb_buffer = (unsigned char *)lpPacket;
 return (Netbios(&m_NCB));
};
/*********************************************************/
UCHAR CNCB::ReceiveBroadcastDatagram()
{ return 0;};
/*********************************************************/
UCHAR CNCB::ChainSend()
{ return 0;};
/*********************************************************/
UCHAR CNCB::ChainSendNoAck()
{ return 0;};

// General Purpose Services
UCHAR CNCB::Reset(UCHAR wSessions, UCHAR wNCBs)
{ClearNCB();
 m_NCB.ncb_command = NCBRESET;
 m_NCB.ncb_lsn = wSessions;
 m_NCB.ncb_num = wNCBs;
 return (Netbios(&m_NCB));
};
/*********************************************************/
UCHAR CNCB::GetAdapterStatus(PSTR pName)
{ClearNCB();
 ADAPTER_STATUS_BLOCK asStatus;
 memset(&asStatus,0,sizeof(ADAPTER_STATUS_BLOCK));
 strncpy((char *)&m_NCB.ncb_callname,pName,MAXMACHINENAME);
 m_NCB.ncb_command = NCBASTAT;
 m_NCB.ncb_lana_num = LANA_NUM;
 m_NCB.ncb_length = sizeof(ADAPTER_STATUS_BLOCK);
 m_NCB.ncb_buffer = (unsigned char *)&asStatus;
 return (Netbios(&m_NCB));
};
/*********************************************************/
UCHAR CNCB::GetSessionStatus(PSTR pName)
{ClearNCB();
 SESSION_INFO_BLOCK sibSession;
 memset(&sibSession,0,sizeof(SESSION_INFO_BLOCK));
 strncpy((char *)&m_NCB.ncb_name,pName,MAXMACHINENAME);
 m_NCB.ncb_command = NCBSSTAT;
 m_NCB.ncb_lana_num = LANA_NUM;
 m_NCB.ncb_buffer = (unsigned char *)&sibSession;
 m_NCB.ncb_length = sizeof(SESSION_INFO_BLOCK);
 return(Netbios(&m_NCB));
};
/*********************************************************/
UCHAR CNCB::EnumerateAdapters()
{ return 0;};
/*********************************************************/
UCHAR CNCB::StatusAlert()
{ return 0;};
/*********************************************************/
UCHAR CNCB::Action()
{ return 0;};
