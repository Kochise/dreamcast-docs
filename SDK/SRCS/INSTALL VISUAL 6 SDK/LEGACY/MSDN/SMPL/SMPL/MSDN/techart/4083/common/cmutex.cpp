// cmutex.cpp -- implements a mutex as a shared, secureable object...

#include "stdafx.h"
#include <windows.h>
#ifdef SERVER
#include "sec.h"
#endif
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
CSecuredMutex::CSecuredMutex(PSTR pName)
{
 m_iErrorCode=ERROR_SUCCESS;
 m_hMutex = CreateMutex(NULL,FALSE,pName);
 if (!m_hMutex)  m_iErrorCode=GetLastError();
 if (!SetTheDescriptor()) m_iErrorCode=m_iSecErrorCode;

};

BOOL CSecuredMutex::SetTheDescriptor(void)
{
 HANDLE hNewHandle;
 BOOL bReturn=FALSE;
 SetPrivilegeInAccessToken(TRUE);

 if (!DuplicateHandle(GetCurrentProcess(),m_hMutex,GetCurrentProcess(),&hNewHandle,WRITE_DAC|ACCESS_SYSTEM_SECURITY,NULL,NULL))
 {
  GetLastError();
  goto ErrorExit;
 };

 bReturn = SetObjectSecurity(hNewHandle);
 CloseHandle(hNewHandle);
 ErrorExit:
 SetPrivilegeInAccessToken(FALSE);
 return bReturn;

};


BOOL CSecuredMutex::GetTheDescriptor(void)
{
 HANDLE hNewHandle;
 BOOL bReturn=FALSE;
 SetPrivilegeInAccessToken(TRUE);

 if (!DuplicateHandle(GetCurrentProcess(),m_hMutex,GetCurrentProcess(),&hNewHandle,READ_CONTROL|ACCESS_SYSTEM_SECURITY,NULL,NULL))
 {
  GetLastError();
  goto ErrorExit;
 };

 bReturn = GetObjectSecurity(hNewHandle);
 CloseHandle(hNewHandle);
 ErrorExit:
 SetPrivilegeInAccessToken(FALSE);
 return bReturn;


};

#endif
