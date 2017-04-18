// comclass. cpp -- implementation of the base communication class

#include "stdafx.h"
#include <windows.h>

#include "common.h"

#include "comclass.h"

#ifdef SECURITY

#include "sec.h"

#endif

#include "dbcode.h"

#include "protocol.h"

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

CServerDatabaseProtocol::CServerDatabaseProtocol(CServerCommunication *cpChannel) : CDatabaseProtocol (cpChannel)
{
};

BOOL CServerDatabaseProtocol::AcceptCommand(int *iCommand, CHAINLIST *cpElement, int *iIndex)
{
 _try
 {	
  if (Read((char *)iCommand,sizeof(int))!=sizeof(int)) return FALSE;  // fetch the command first
  switch (*iCommand)
  { 
   case CMD_ADDRECORD:
    if (Read ((char *)&cpElement->iSecuredElement,sizeof(int)) !=sizeof(int)) return FALSE;
    if (Read ((char *)&cpElement->iInsecuredElement,sizeof(int)) !=sizeof(int)) return FALSE;
    return TRUE;
   case CMD_DELETERECORD:
    if (Read((char *)iIndex,sizeof(int))!=sizeof(int)) return FALSE;
    return TRUE;
   case CMD_RETRIEVERECORD:
    if (Read((char *)iIndex,sizeof(int))!=sizeof(int)) return FALSE;
	return TRUE;
   case CMD_GETENTRIES:
    return TRUE;
  }; // switch 
  return TRUE;
 }
 _except (EXCEPTION_EXECUTE_HANDLER)
 {
  m_iErrorCode = GetExceptionCode();
 };
 return FALSE;
};
  
BOOL CServerDatabaseProtocol::Fail(int iErrorCode)
{
 int iData;
 iData = CMD_FAILURE;
 _try
 {
  Write((char *)&iData,sizeof(int));
  iData = iErrorCode;
  Write((char *)&iData,sizeof(int));
  return TRUE;
 }
 _except (EXCEPTION_EXECUTE_HANDLER)
 {
  m_iErrorCode = GetExceptionCode();
 };
 return FALSE;
};

BOOL CServerDatabaseProtocol::Acknowledge(int iIndex)
{
 int iData;
 iData = CMD_SUCCESS;
 _try
 {
  Write((char *)&iData,sizeof(int));
  iData = iIndex;
  Write((char *)&iData,sizeof(int));
  return TRUE;
 }
 _except (EXCEPTION_EXECUTE_HANDLER)
 {
  m_iErrorCode = GetExceptionCode();
 };
 return FALSE;
};

#endif
