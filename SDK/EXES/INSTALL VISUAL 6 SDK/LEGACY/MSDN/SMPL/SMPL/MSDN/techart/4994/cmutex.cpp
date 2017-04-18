// cmutex.cpp -- implements a mutex as a shared, secureable object...

#include "stdafx.h"
#include <windows.h>
#include "cmutex.h"



CMutex::CMutex()
{
 m_iErrorCode=ERROR_SUCCESS;
// this is for the Open call to generate an "empty" mutex...
};


BOOL CMutex::Open(PSTR pName)
{
 m_hMutex = OpenMutex(MUTEX_ALL_ACCESS,FALSE,pName);
 if (!m_hMutex)
 {
  m_iErrorCode=GetLastError();
  return FALSE;
 };
 return TRUE;
}



CMutex::~CMutex()
{
if (!CloseHandle(m_hMutex))
 m_iErrorCode=GetLastError();

};
void CMutex::Claim()
{
 WaitForSingleObject(m_hMutex,INFINITE);
};
BOOL CMutex::Release()
{
 if (!ReleaseMutex(m_hMutex))
  {
   m_iErrorCode=GetLastError();
   return FALSE;
  };
 return TRUE;
};

BOOL CMutex::Close()
{ 
 if (!CloseHandle(m_hMutex))
 {m_iErrorCode=GetLastError();
  return FALSE;
 };
 return TRUE;
};

#ifdef SERVER
CServerMutex::CServerMutex(PSTR pName)
{
 m_iErrorCode=ERROR_SUCCESS;
 m_hMutex = CreateMutex(NULL,FALSE,pName);
 if (!m_hMutex)  m_iErrorCode=GetLastError();

};
#endif
