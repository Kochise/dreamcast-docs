#include "stdafx.h"
#include "comclass.h"

#ifdef SECURITY

#include "sec.h"

#endif

#include "netbios.h"


#include <windows.h>

char achLocalMachineName[MAXMACHINENAME];
int iNBObjectCount = 0;
BOOL bAddNameWorked = TRUE;

// helper functions

#define UNIQUECHARACTER '!'				   

void MakeNetBIOSName(PSTR pszName, PSTR pszPaddedName)
{ int iLen;
  if (pszName) strcpy(pszPaddedName,pszName);
  iLen = strlen(pszPaddedName);
  _strupr(pszPaddedName);
  pszPaddedName[iLen] = UNIQUECHARACTER;
  pszPaddedName[iLen+1] = '\0';  
  unsigned int iLoop;
  for (iLoop=strlen(pszPaddedName);iLoop<MAXMACHINENAME;iLoop++)
    pszPaddedName[iLoop]=' ';
  pszPaddedName[MAXMACHINENAME-1]='\0';
 };


CClientNetBIOS::CClientNetBIOS() : CClientCommunication()
{
m_iErrorCode = 0;
};

CClientNetBIOS::~CClientNetBIOS()
{
};



BOOL CClientNetBIOS::Open(const char* pszFileName, UINT nOpenFlags,
		CFileException* pError)
  {
  // first of all, register the new NetBIOS name and fail for good if this doesn't work
   m_iStatusPending = STATUS_NOT_CONNECTED;
   if (!bAddNameWorked) return FALSE;
   if (iNBObjectCount == 0)
// the first object to be created initializes the machine name string...
// this way, we won't have to do it every time...
   {
    unsigned long iMachineNameLength;
    GetComputerName(achLocalMachineName,&iMachineNameLength);
    MakeNetBIOSName((char *)0,achLocalMachineName);
    CNCB ncbNameAdder;
    ncbNameAdder.Reset(0,0);
	UINT uReturn = ncbNameAdder.AddName(achLocalMachineName);
	if ((uReturn != NRC_GOODRET)) // && (uReturn != NRC_DUPNAME)) 
     {															 
      bAddNameWorked = FALSE;
      return FALSE;
     };

  };
  iNBObjectCount++; 
  if (!pszFileName)
  {	  // we are server
	  // nothing to do here, believe it or not!!! :-)
	  // the name table already contains the entry for our machine...
  }	  
  else
  {
   int iLen = strlen(pszFileName);
   MakeNetBIOSName((char *)pszFileName,m_pszPaddedFileName); 
   m_thisNCB.Call(achLocalMachineName,m_pszPaddedFileName,(UCHAR)0,(UCHAR)0);
   m_lsn = m_thisNCB.GetLSN();
  };
  return TRUE;
 };

 void CClientNetBIOS::Close(void)
{
 m_thisNCB.Hangup(m_lsn);

// this code invoked to clean up after the last object...

 iNBObjectCount--;
 if (!iNBObjectCount)
  {
   CNCB ncbNameDeleter;
   ncbNameDeleter.DeleteName(achLocalMachineName);
  };

};


void CClientNetBIOS::Write(const void FAR* pBuf, UINT iCount)
{ 
 m_thisNCB.Send(m_lsn,(char *)pBuf,iCount);
};

UINT CClientNetBIOS::Read(void FAR* lpBuf, UINT nCount)
{ 
 if (m_thisNCB.Receive(m_lsn,(char *)lpBuf,nCount) != NRC_GOODRET)
      return 0;
 return (UINT)m_thisNCB.GetLength();
};

BOOL CClientNetBIOS::ReConnect(void)
{	
 return FALSE;
};

CServerNetBIOS::CServerNetBIOS() : CClientNetBIOS()
{
};


CServerCommunication *CServerNetBIOS::Duplicate()
{
 CServerNetBIOS *cNew;
 cNew = new(CServerNetBIOS);
 cNew->m_lsn = m_lsn;
 cNew->m_thisNCB.Fill(m_thisNCB);
 iNBObjectCount++; 
 return cNew; 
}

BOOL CServerNetBIOS::AwaitCommunicationAttempt(void)
{
 m_iStatusPending = STATUS_CONNECTION_PENDING;
 if (m_thisNCB.Listen(achLocalMachineName,"*              \0",(UCHAR)0,(UCHAR)0)
   !=NRC_GOODRET) return FALSE;
//when listen returns, we'll need to store the lsn...
  m_lsn = m_thisNCB.GetLSN();
  m_iStatusPending = STATUS_CONNECTED;
 return TRUE;
};

BOOL CServerNetBIOS::CancelCommunicationAttempt(void)
{
 BOOL bResult;
 m_iErrorCode = 0;
 if (m_iStatusPending != STATUS_CONNECTION_PENDING) return FALSE;
 if (m_thisNCB.GetCommand() != NCBLISTEN)
 return FALSE;
 bResult = m_thisNCB.Cancel();
 if (bResult == NRC_GOODRET)
 { 
   m_iStatusPending = STATUS_NOT_CONNECTED;
   return TRUE;
 };
 m_iErrorCode = bResult;
 return FALSE;
};

void CServerNetBIOS::CloseInstance()
{
 m_iStatusPending = STATUS_NOT_CONNECTED;
};


#ifdef SECURITY

BOOL CSecuredNetBIOS::Open(const char* pszFileName, UINT nOpenFlags,CFileException* pError)
{
 if (!CServerNetBIOS::Open(pszFileName,nOpenFlags,pError)) // must resolve ambiguity here
   return FALSE;
 if (!SetTheDescriptor()) return FALSE;
 return TRUE;
}

#endif
