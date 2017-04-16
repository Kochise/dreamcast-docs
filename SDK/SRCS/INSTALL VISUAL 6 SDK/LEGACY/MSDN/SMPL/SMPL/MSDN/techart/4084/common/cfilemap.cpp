// CFileMapping.cpp -- implements a mutex as a shared, secureable object...

#include "stdafx.h"
#include <windows.h>
#ifdef SERVER
#include "sec.h"
#endif
#include "CFileMap.h"



CFileMapping::CFileMapping()
{
 m_iErrorCode = ERROR_SUCCESS;
// this is for the Open call to generate an "empty" mutex...
};


BOOL CFileMapping::Open(PSTR pName)
{
 m_hMap = OpenFileMapping(FILE_MAP_ALL_ACCESS,FALSE,pName);
 if (!m_hMap)
 {
  m_iErrorCode=GetLastError();
  return FALSE;
 };
 return TRUE;
}

CFileMapping::~CFileMapping()
{
};

LPVOID CFileMapping::ObtainPointer()
{
 m_lpMapping = MapViewOfFile(m_hMap,FILE_MAP_ALL_ACCESS,0,0,0);
 if (!m_lpMapping)
  m_iErrorCode=GetLastError();
 return m_lpMapping;
};

BOOL CFileMapping::ReleasePointer()
{
 BOOL bResult = UnmapViewOfFile(m_lpMapping);
 if (!bResult) m_iErrorCode=GetLastError();
 return bResult;
};



BOOL CFileMapping::Close()
{ 
if (!CloseHandle(m_hMap))
 {
  m_iErrorCode=GetLastError();
  return FALSE;
 };
return TRUE;
};

#ifdef SERVER

CSecuredFileMapping::CSecuredFileMapping(PSTR pName,DWORD dwSize)
{
 m_iErrorCode = ERROR_SUCCESS;
 m_hMap = CreateFileMapping((HANDLE)0xffffffff,NULL,PAGE_READWRITE,0,dwSize,pName);
 if (!m_hMap) m_iErrorCode=GetLastError();
 if (!SetTheDescriptor()) m_iErrorCode=m_iSecErrorCode;
};

BOOL CSecuredFileMapping::SetTheDescriptor(void)
{
 HANDLE hNewHandle;
 BOOL bReturn=FALSE;
 SetPrivilegeInAccessToken(TRUE);

 if (!DuplicateHandle(GetCurrentProcess(),m_hMap,GetCurrentProcess(),&hNewHandle,WRITE_DAC|ACCESS_SYSTEM_SECURITY,NULL,NULL))
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


BOOL CSecuredFileMapping::GetTheDescriptor(void)							  
{
 HANDLE hNewHandle;
 BOOL bReturn=FALSE;
 SetPrivilegeInAccessToken(TRUE);
 if (!DuplicateHandle(GetCurrentProcess(),m_hMap,GetCurrentProcess(),&hNewHandle,READ_CONTROL|ACCESS_SYSTEM_SECURITY,NULL,NULL))
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
