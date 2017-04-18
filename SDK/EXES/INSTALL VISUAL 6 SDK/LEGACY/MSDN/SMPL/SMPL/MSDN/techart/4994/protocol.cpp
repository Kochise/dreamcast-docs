// comclass. cpp -- implementation of the base communication class

#include "stdafx.h"
#include <windows.h>

#include "common.h"

#include "comclass.h"

#include "dbcode.h"

#include "npipe.h"

#include "protocol.h"

#ifdef SERVER

#include "client.h"

#endif

// Buffers and pipe symbolic constants.


CProtocol::CProtocol()
{
 m_bIsCommunicationEstablished = FALSE;
};

CProtocol::~CProtocol()
{
};

BOOL CDatabaseProtocol::Open(const char* pszFileName, UINT nOpenFlags,
		CFileException* pError)
{
 return TRUE; // don't need to do anything here...
};

UINT CDatabaseProtocol::Read(void FAR* lpBuf, UINT nCount)
{	
 return m_cBothways->Read(lpBuf,nCount);
};

void CDatabaseProtocol::Write(const void FAR* lpBuf, UINT nCount)
{
 m_cBothways->Write(lpBuf,nCount);
};
  
void CDatabaseProtocol::Close()
{
};

CDatabaseProtocol::CDatabaseProtocol(CClientCommunication *cpChannel)
{
 m_cBothways = cpChannel;
};


#ifndef SERVER
 
CClientDatabaseProtocol::CClientDatabaseProtocol(CClientCommunication *cpChannel) : CDatabaseProtocol (cpChannel)
{
};

  
BOOL CClientDatabaseProtocol::Terminate()
{
 BOOL bReturn;
 int iData;
 iData = CMD_EXIT;
 _try
 {
  Write((char *)&iData,sizeof(int));
  bReturn = TRUE;
 }
 _except (EXCEPTION_EXECUTE_HANDLER)
 {
  bReturn = FALSE;
  m_iErrorCode = GetExceptionCode();
 };
  return bReturn;
};

BOOL CClientDatabaseProtocol::GetEntries(int *iNumber)
{ 
 int iData;
 iData = CMD_GETENTRIES;
 _try
 {
  Write((char *)&iData,sizeof(int));
  Read((char *)&iData,sizeof(int));
  if (iData == CMD_SUCCESS)
  {
   Read ((char *)iNumber,sizeof(int));
   return TRUE;
  }
  else
  {
   Read((char *)&m_iErrorCode,sizeof(int));
   return FALSE;
  };
 }
 _except (EXCEPTION_EXECUTE_HANDLER)
 {
  m_iErrorCode = GetExceptionCode();
 };
 return FALSE;
};
  
BOOL CClientDatabaseProtocol::AddData(int *iIndex, CHAINLIST *clElement)
{ 
 int iData;
 // first write the stuff out
 iData = CMD_ADDRECORD;
 _try
 {
  Write((char *)&iData,sizeof(int));
  Write((char *)&clElement->iSecuredElement,sizeof(int));
  Write((char *)&clElement->iInsecuredElement,sizeof(int));
  // then wait for the response
  Read((char *)&iData,sizeof(int));
  if (iData == CMD_SUCCESS) 
  {
   Read ((char *)iIndex,sizeof(int));
   return TRUE;
  }
  else 
  {
   Read((char *)&m_iErrorCode,sizeof(int));
   return FALSE;
  };
 }
 _except (EXCEPTION_EXECUTE_HANDLER)
 {
  m_iErrorCode = GetExceptionCode();
 };
 return FALSE;
};
  
BOOL CClientDatabaseProtocol::RemoveData(int iIndex)
{	
 int iData;
 // first send the stuff out
 iData = CMD_DELETERECORD;
 _try
 {
  Write((char *)&iData,sizeof(int));
  Write((char *)&iIndex,sizeof(int));
  // then wait for the response
  Read((char *)&iData,sizeof(int));
  if (iData == CMD_SUCCESS)
  {
   Read ((char *)&iData,sizeof(int)); // discard the dummy ack data
   return TRUE;
  }
  else 
  {
   Read((char *)&m_iErrorCode,sizeof(int));
   return FALSE;
  };
 }
 _except (EXCEPTION_EXECUTE_HANDLER)
 {
  m_iErrorCode = GetExceptionCode();
 };
  return FALSE;
};
  
BOOL CClientDatabaseProtocol::RetrieveData(int iIndex, CHAINLIST *cpResult)
{	
 int iData;
 // first send the stuff out
 iData = CMD_RETRIEVERECORD;
 _try
 {
  Write((char *)&iData,sizeof(int));
  Write((char *)&iIndex,sizeof(int));
  // then wait for the response
  Read((char *)&iData,sizeof(int));
  if (iData == CMD_SUCCESS)
  {
   Read ((char *)&cpResult->iInsecuredElement,sizeof(int));
   Read ((char *)&iData,sizeof(int));  // for the time being, ignore...
   Read ((char *)&cpResult->iSecuredElement,sizeof(int)); 
   return TRUE;
  }
  else 
  {
   Read((char *)&m_iErrorCode,sizeof(int));
   return FALSE;
  };
 }
 _except (EXCEPTION_EXECUTE_HANDLER)
 { 
  m_iErrorCode = GetExceptionCode();
 };
 return FALSE;
};

#else

long WINAPI WorkerThreadFunction(void *vArg)
{
 CServerDatabaseProtocol *csdp=(CServerDatabaseProtocol *)vArg;
 DWORD nBytes;
 DWORD WorkIndex;
 OVERLAPPED ovl;
 LPOVERLAPPED pOvl=&ovl;
 CClientObject *cpCurrentContext;
 BOOL b;
 while (csdp->bActive)
 {
  b = GetQueuedCompletionStatus(csdp->m_hPort,
                                &nBytes,
                                &WorkIndex,
                                &pOvl,
                                INFINITE);
  if (!b || !pOvl)
  { // something has gone wrong here...
   GetLastError();
   continue; 
  };
  cpCurrentContext=csdp->m_coClients[WorkIndex];
  if (cpCurrentContext->DispatchFn((STATE_ENUMERATOR)cpCurrentContext->m_se,&ovl)
      == CMD_CLIENT_TERMINATED)
    csdp->DeAssociate(WorkIndex); 
};
 return 0;
}; 


CServerDatabaseProtocol::CServerDatabaseProtocol(int iThreadCount) 
{
  bActive=TRUE;
  m_iThreadCount=iThreadCount;
  if (iThreadCount>MAXTHREADCOUNT)
  m_iThreadCount=MAXTHREADCOUNT;
  DWORD id;
  m_hPort=::CreateIoCompletionPort(INVALID_HANDLE_VALUE,NULL,NULL,m_iThreadCount);
  for (int iLoop=0;iLoop<m_iThreadCount;iLoop++)
   {

// now create the worker threads.
    m_coThreads[iLoop]= ::CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)WorkerThreadFunction,(void *)this,CREATE_SUSPENDED,&id);
    ::SetThreadPriority(m_coThreads[iLoop],THREAD_PRIORITY_BELOW_NORMAL);
    ::ResumeThread(m_coThreads[iLoop]);
    m_coClients[iLoop]=NULL;
   };
};

CServerDatabaseProtocol::~CServerDatabaseProtocol()
{
 bActive = FALSE; // this will make the workers fall through
 for (int iLoop=0;iLoop<m_iThreadCount;iLoop++)
  {
   PostQueuedCompletionStatus(m_hPort,NULL,NULL,NULL);
   DeAssociate(iLoop);
  };
 CloseHandle(m_hPort);
 WaitForMultipleObjects(m_iThreadCount,m_coThreads,TRUE,INFINITE);
};

int CServerDatabaseProtocol::Associate (HANDLE hComm, int iIndex)
{
// first, create the instances of the IOCP.
// note that we can disregard the return values
// here because the port handle is always the
// same.
  CreateIoCompletionPort (hComm,
                        m_hPort,
                        (DWORD)iIndex,
                        m_iThreadCount);

 return 1;
}

int CServerDatabaseProtocol::Associate (CClientObject *coNextClient, int iIndex)
{
 m_coClients[iIndex]=coNextClient;
 coNextClient->Trigger();
return 0;

};


BOOL CServerDatabaseProtocol::DeAssociate(int iIndex)
{if (m_coClients[iIndex])
 delete m_coClients[iIndex];
 m_coClients[iIndex]=NULL;
 return 0;
};

#endif
