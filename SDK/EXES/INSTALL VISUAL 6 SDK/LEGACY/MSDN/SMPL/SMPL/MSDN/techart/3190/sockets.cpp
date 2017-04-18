#include "stdafx.h"
#include "comclass.h"

#include <windows.h>

#ifdef SECURITY

#include "sec.h"

#endif

#include "sockets.h"


#define READ_PORT 5001
#define WRITE_PORT 5002
#define BI_PORT 5003

// Buffers and pipe symbolic constants.
#define MAX_PENDING_CONNECTS 4  /* The backlog allowed for listen() */

int iObjectCount = 0;
BOOL bAreWeInitialized = FALSE;

CClientSocket::CClientSocket() : CClientCommunication()
{
 WSADATA WSAData;
 m_bWeAreDuplicated = FALSE;
 if (iObjectCount == 0 && WSAStartup(MAKEWORD(1,1), &WSAData) == 0)
   bAreWeInitialized = TRUE;
 iObjectCount++;
};

CClientSocket::~CClientSocket()
{
 iObjectCount--;
 if (!iObjectCount)
  {
   WSACleanup();
   bAreWeInitialized = FALSE;
  };
};



BOOL CClientSocket::Open(const char* pszFileName, UINT nOpenFlags,
		CFileException* pError)
// currently we only support the READ and WRITE open flags...
{
 BOOL bReturn;
 if (!bAreWeInitialized) 
    return FALSE;
   m_iStatusPending = STATUS_NOT_CONNECTED;
  m_iErrorCode = 0;

 m_theSocket = socket( AF_INET, SOCK_STREAM, 0);
 if (m_theSocket == INVALID_SOCKET)
 {
  WSAGetLastError();     // convenience for the debugger
  return FALSE;
 };
SOCKADDR_IN saTemp;
saTemp.sin_family = AF_INET;
switch (nOpenFlags)
{
 case modeRead:
  saTemp.sin_port = htons(WRITE_PORT);
  break;
 case modeWrite:
  saTemp.sin_port = htons(READ_PORT);
  break;
 default:     // assume bidirectional
  saTemp.sin_port = htons(BI_PORT);
};


if (!pszFileName) return FALSE;        // NULL means we want to be the server
// m_bWeAreServer = FALSE;
 m_phe = gethostbyname(pszFileName);
 if (m_phe == NULL)
 { 
  WSAGetLastError();
  bReturn = FALSE;
 }
 else
 {
  memcpy((char FAR *)&(saTemp.sin_addr), m_phe->h_addr,
      m_phe->h_length); 
  if (connect(m_theSocket,(PSOCKADDR)&saTemp,sizeof(saTemp)) == SOCKET_ERROR)
  { 
   WSAGetLastError();
   bReturn = FALSE;
  }
  else
  {
   m_bIsCommunicationEstablished = TRUE;
   m_CommSocket = m_theSocket;          
   bReturn = TRUE;
   };
  };
 if (!bReturn)
 { 
  closesocket(m_theSocket);
  return FALSE;
 }
  else  
  return TRUE; 
};

CServerCommunication *CServerSocket::Duplicate()
{
 CServerSocket *csResult = new CServerSocket();
 csResult->m_theSocket = m_theSocket;   // let's take the preventively allocated socket...
 csResult->m_CommSocket = m_CommSocket;
// csResult->m_bWeAreServer = m_bWeAreServer;
 csResult->m_sa = m_sa;
 csResult->m_bWeAreDuplicated = TRUE;
 csResult->m_bIsCommunicationEstablished = m_bIsCommunicationEstablished;
 return csResult;
}


void CClientSocket::Close(void)
{
 if (m_bIsCommunicationEstablished)
  closesocket(m_CommSocket);
 if (!m_bWeAreDuplicated)
  closesocket(m_theSocket);
};


void CClientSocket::Write(const void FAR* pBuf, UINT iCount)
{
 if (send(m_CommSocket,(const char *)pBuf,iCount,0) == SOCKET_ERROR)
     WSAGetLastError();
};

UINT CClientSocket::Read(void FAR* lpBuf, UINT nCount)
{ 
 UINT iResult;
 iResult = recv(m_CommSocket,(char *)lpBuf,nCount,0);
 if (iResult == 0 || iResult == SOCKET_ERROR)
  {
   WSAGetLastError();
   return 0;
  };
 return iResult;
};

BOOL CClientSocket::ReConnect(void)
{	
 return FALSE;
};

// derived classes

CServerSocket::CServerSocket() : CClientSocket()
{
};

BOOL CServerSocket::Open(const char* pszFileName, UINT nOpenFlags,
		CFileException* pError)
// currently we only support the READ and WRITE open flags...
{
 BOOL bReturn;
 if (!bAreWeInitialized) 
    return FALSE;
   m_iStatusPending = STATUS_NOT_CONNECTED;
 m_iErrorCode = 0;
 m_theSocket = socket( AF_INET, SOCK_STREAM, 0);
 if (m_theSocket == INVALID_SOCKET)
 {
  WSAGetLastError();     // convenience for the debugger
  return FALSE;
 };
SOCKADDR_IN saTemp;
saTemp.sin_family = AF_INET;
switch (nOpenFlags)
{
 case modeRead:
  saTemp.sin_port = htons(READ_PORT);
  break;
 case modeWrite:
  saTemp.sin_port = htons(WRITE_PORT);
  break;
 default:     // assume bidirectional
  saTemp.sin_port = htons(BI_PORT);
};


if (pszFileName)         // NULL means we want to be the server
 return FALSE;
// m_bWeAreServer = TRUE;
 saTemp.sin_addr.s_addr= INADDR_ANY;	  // bind to any address 4 multihomed machines
 if (bind(m_theSocket,(PSOCKADDR)&saTemp, sizeof(saTemp)) == SOCKET_ERROR)
 {
  WSAGetLastError();
  bReturn = FALSE;
 }
 else
 if (listen(m_theSocket, MAX_PENDING_CONNECTS ) == SOCKET_ERROR)
 {
  WSAGetLastError();
  bReturn = FALSE;
 }
 else
 {
  m_bIsCommunicationEstablished = FALSE;
  bReturn = TRUE;
 };
 if (!bReturn)
 { 
  closesocket(m_theSocket);
  return FALSE;
 }
  else  
  return TRUE; 
};


BOOL CServerSocket::AwaitCommunicationAttempt(void)
{
 m_iStatusPending = STATUS_CONNECTION_PENDING;
 
 m_CommSocket = accept(m_theSocket,&m_sa,0);  // Block until a client connects.
 if (m_CommSocket == INVALID_SOCKET)
 {
  WSAGetLastError();
  return FALSE;
 };
 m_bIsCommunicationEstablished = TRUE;
 m_iStatusPending = STATUS_CONNECTED;
 return TRUE;
};

BOOL CServerSocket::CancelCommunicationAttempt(void)
{
 m_iStatusPending = STATUS_NOT_CONNECTED;
 return (WSACancelBlockingCall() == 0);
};

#ifdef SECURITY

BOOL CSecuredSocket::Open(const char* pszFileName, UINT nOpenFlags,CFileException* pError)
{
 if (!CServerSocket::Open(pszFileName,nOpenFlags,pError)) // must resolve ambiguity here
   return FALSE;
 if (!SetTheDescriptor()) return FALSE;
 return TRUE;
}

#endif
