// CFileMap.cpp -- implements a mutex as a shared, secureable object...

#include "stdafx.h"
#include <windows.h>
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

CServerFileMapping::CServerFileMapping(PSTR pName,DWORD dwSize)
{
 m_iErrorCode = ERROR_SUCCESS;
 m_hMap = CreateFileMapping((HANDLE)0xffffffff,NULL,PAGE_READWRITE,0,dwSize,pName);
 if (!m_hMap) m_iErrorCode=GetLastError();
};
#endif
