// comclass. cpp -- implementation of the base communication class

#include "stdafx.h"
#include <windows.h>

#include "comclass.h"

#include "protocol.h"

// Buffers and pipe symbolic constants.


  CProtocol::CProtocol()
  {m_bIsCommunicationEstablished = FALSE;};

  CProtocol::~CProtocol()
  {};

  BOOL CProtocol::CheckOnResponse(void)
  { char szBuf[3];
    m_cInBound->Read(szBuf,2);
	szBuf[2] = '\0';
	if (strcmp(szBuf,"ok")==0)
	  return TRUE;
	  else return FALSE;
  };
	    
  void CProtocol::Acknowledge()
  { 
   m_cOutBound->Write("ok",2);
  };
  void CProtocol::Reject()
  { 
   m_cOutBound->Write("no",2);
  };

CChatProtocol::CChatProtocol() : CProtocol()
{ 
}


CServerChatProtocol::CServerChatProtocol(CServerCommunication *cInBound, CServerCommunication *cOutBound) : CChatProtocol()
{ 
 m_cInBound = cInBound;
 m_cOutBound = cOutBound;
}

CChatProtocol::~CChatProtocol()
{
//  Write("",0);    // to terminate the conversation...  
  m_cOutBound->Close();
  m_cInBound->Close();
  delete m_cOutBound;
  delete m_cInBound;

  };

 CClientChatProtocol::CClientChatProtocol(CClientCommunication *cInBound, CClientCommunication *cOutBound) : CChatProtocol()
 { 
  m_cInBound = cInBound;
  m_cOutBound = cOutBound;
 }


// The derived protocol

// protocol functions
  BOOL CServerChatProtocol::InitiateConversationAsServer(CString **csArg)
  {char szResponse[MAX_COMPUTERNAME_LENGTH+1];
   int iOtherMachineNameSize;
   m_cInBound->Read(szResponse,1);
   if (szResponse[0]=='?')    // request for existence not implemented yet
      return FALSE;
   if (szResponse[0]!=':') return FALSE;  // unknown request
   Acknowledge();    // always succeed here...
   iOtherMachineNameSize=m_cInBound->Read(szResponse,MAX_COMPUTERNAME_LENGTH+1);
   szResponse[iOtherMachineNameSize]='\0';
   MessageBeep(-1);
   if (::MessageBox(GetFocus(),szResponse,"Do you wish to respond?",MB_OKCANCEL) == IDOK)
    {*csArg = new CString(szResponse);
     Acknowledge();
     return TRUE;
    }
	else Reject();
   return FALSE;
  };
     
  BOOL CClientChatProtocol::InitiateConversationAsClient(const char *szMachineName, int iMachineName)
  {m_cOutBound->Write(":",strlen(":"));
   if (!CheckOnResponse()) return FALSE;
   m_cOutBound->Write(szMachineName,iMachineName);
   if (!CheckOnResponse()) return FALSE;
   return TRUE;
  };


  BOOL CChatProtocol::Open(const char* pszFileName, UINT nOpenFlags,
		CFileException* pError)
{

// we assume that a communication object passed into CChatProtocol is
// already opened correctly...

  return TRUE;
};




  void CChatProtocol::Close(void)
  {	
// for symmetry reasons, we use the ctor and dtor to clean up the objects...
  };


  void CChatProtocol::Write(const void FAR* pBuf, UINT iCount)
  {
  char szBuf[sizeof(int)+sizeof(char)+sizeof(char)];
  szBuf[sizeof(int)]='\0';

  ((int *)szBuf)[0] = iCount;
  m_cOutBound->Write(szBuf,sizeof(int)+sizeof(char));      
  m_cOutBound->Write(pBuf,iCount); 
  };

  UINT CChatProtocol::Read(void FAR* lpBuf, UINT nCount)
  {//	UINT iLoop,iBytesReceived;
   char szBuf[sizeof(int)+sizeof(char)];
   szBuf[sizeof(int)]='\0';

   UINT iBytesRequested= m_cInBound->Read(szBuf,sizeof(int)+sizeof(char));
   if (iBytesRequested == 0) 
        return 0;
   iBytesRequested = ((int *)szBuf)[0];
   if (iBytesRequested > nCount) 
         return 0;
	   iBytesRequested = m_cInBound->Read(((char *)lpBuf),iBytesRequested);
 	   if (iBytesRequested == 0)
	      return 0;
	   return iBytesRequested;

  };  //CChatProtocol::Read

CFileTransferProtocol::CFileTransferProtocol() : CProtocol()
{ 
}


CServerFileTransferProtocol::CServerFileTransferProtocol(CServerCommunication *cInBound, CServerCommunication *cOutBound) : CFileTransferProtocol()
{ 
 m_cInBound = cInBound;
 m_cOutBound = cOutBound;
 m_bWeAreServer = (cOutBound == (CServerCommunication *)NULL);
}

CClientFileTransferProtocol::CClientFileTransferProtocol(CClientCommunication *cInBound, CClientCommunication *cOutBound) : CFileTransferProtocol()
{ 
 m_cInBound = cInBound;
 m_cOutBound = cOutBound;
 m_bWeAreServer = (cOutBound == (CClientCommunication *)NULL);
}


CFileTransferProtocol::~CFileTransferProtocol()
{
 m_cInBound->Close();
 m_cOutBound->Close();
 delete m_cInBound;
 delete m_cOutBound;
};



  BOOL CFileTransferProtocol::Open(const char* pszFileName, UINT nOpenFlags,
		CFileException* pError)
{   if (pszFileName == NULL)           // we are server
  {char szResponse[MAX_COMPUTERNAME_LENGTH+1];
   int iOtherMachineNameSize;
   m_cInBound->Read(szResponse,1);
   if (szResponse[0]=='?')    // request for existence not implemented yet
      return FALSE;
   if (szResponse[0]!=':') return FALSE;  // unknown request
   Acknowledge();    // always succeed here...
   iOtherMachineNameSize = m_cInBound->Read(szResponse,MAX_COMPUTERNAME_LENGTH+1);
   szResponse[iOtherMachineNameSize]='\0';
   if (::MessageBox(GetFocus(),szResponse,"Do you wish to receive a file from",MB_OKCANCEL) == IDOK)
 	{Acknowledge();
     return TRUE;
	}
	else Reject();
   return FALSE;
  }
  else			                     // we are client
 {m_cOutBound->Write(":",strlen(":"));
   if (!CheckOnResponse()) return FALSE;
   m_cOutBound->Write(pszFileName,nOpenFlags); //we overload the parameters here
   if (!CheckOnResponse()) return FALSE;
   return TRUE;
  };
};

void CFileTransferProtocol::Close(void)
{	
};

void CFileTransferProtocol::Write(const void FAR* pBuf, UINT iCount)
{
 WriteHelper(pBuf,iCount);
 if (!CheckOnResponse()) AfxMessageBox("Receiver reports error..."); 
}

void CFileTransferProtocol::WriteHelper(const void FAR* pBuf, UINT iCount)
{
// this is kind of fishy here... we simply assume that an error is caught on both sides 
// we must handle error_lost_connection differently...
   _try
    {
    m_cOutBound->Write(pBuf,iCount);
	}
   _except (EXCEPTION_EXECUTE_HANDLER)
    {UINT iHalfway = iCount/2;
	 WriteHelper(pBuf,iHalfway);
	 WriteHelper(&((char *)pBuf)[iHalfway],iCount-iHalfway);
	}

   
  };

// watch out for the twisted semantics of those two functions!!!
  void CFileTransferProtocol::SetLength(DWORD dwNewLen)
  {
    dwFileLength = dwNewLen;
     char szBuf[sizeof(int)+sizeof(char)];
   ((int *)szBuf)[0]= dwFileLength;
   szBuf[sizeof(int)]='\0';
   m_cOutBound->Write(szBuf,sizeof(int));
  };

  DWORD CFileTransferProtocol::GetLength(void)
  {char szResponse[sizeof(int)+sizeof(char)];
   m_cInBound->Read(szResponse,sizeof(int));
   dwFileLength = ((int *)szResponse)[0];
   return dwFileLength;
  };

 UINT CFileTransferProtocol::Read(void FAR* pBuf, UINT iCount)
 { UINT iBytesReceived;
   iBytesReceived = ReadHelper(pBuf,iCount); 
   if (iBytesReceived < iCount) Reject(); else Acknowledge();
   return iBytesReceived;
 };

  UINT CFileTransferProtocol::ReadHelper(void FAR* pBuf, UINT iCount)
  {	UINT iBytesReceived=0;
while (iBytesReceived <iCount)
{ UINT iResult;
  iResult = m_cInBound->Read(&((char *)pBuf)[iBytesReceived],iCount-iBytesReceived);
  iBytesReceived+=iResult;
	}; // while
return iBytesReceived;
   
};  //CFileTransferProtocol::Read

BOOL CFileTransferProtocol::LastMinuteCheckReceiver(BOOL bArg)
{if (bArg) Acknowledge(); else Reject();
 return CheckOnResponse() && bArg;
};
BOOL CFileTransferProtocol::LastMinuteCheckSender(BOOL bArg)
{ BOOL bReturn = CheckOnResponse();
  if (bArg) Acknowledge(); else Reject();
  return bReturn && bArg;
};

CSelectorProtocol::CSelectorProtocol() : CProtocol()
{
};

CClientSelectorProtocol::CClientSelectorProtocol(CClientCommunication *cInBound, CClientCommunication *cOutBound) : CSelectorProtocol()
{ 
  m_cInBound = cInBound;
  m_cOutBound = cOutBound;
};
CServerSelectorProtocol::CServerSelectorProtocol(CServerCommunication *cInBound, CServerCommunication *cOutBound) : CSelectorProtocol()
{ 
 m_cInBound = cInBound;
 m_cOutBound = cOutBound;
};


int CSelectorProtocol::GetCommunicationType(void)
{ char szBuf[2];
  m_cInBound->Read(szBuf,sizeof(char));
  switch(szBuf[0])
  { case 't': return TRANSFERTYPE;
    case 'c': return CHATTYPE;
  };
  return -1;
 
};
void CSelectorProtocol::SetCommunicationType(int iType)
{switch (iType)
 { case TRANSFERTYPE:  m_cOutBound->Write("t",sizeof(char)); break;
   case CHATTYPE: m_cOutBound->Write("c",sizeof(char)); break;
 };
};

BOOL CSelectorProtocol::Open(const char* pszFileName, UINT nOpenFlags,
		CFileException *csEx)
{ return FALSE;
};

UINT CSelectorProtocol::Read(void FAR* lpBuf, UINT nCount)
{ return 0;
};
void CSelectorProtocol::Write(const void FAR* lpBuf, UINT nCount)
{ return;
};
void CSelectorProtocol::Close()
{ return;
};

