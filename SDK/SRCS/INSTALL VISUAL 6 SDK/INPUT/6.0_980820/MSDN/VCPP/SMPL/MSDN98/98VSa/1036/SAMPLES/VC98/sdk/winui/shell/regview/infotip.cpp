/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1997 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          InfoTip.cpp
   
   Description:   Implements CQueryInfo.

**************************************************************************/

#include "InfoTip.h"

#if (_WIN32_IE >= 0x0400)

/**************************************************************************
   #include statements
**************************************************************************/

#include "Guid.h"
#include "Utility.h"

/**************************************************************************

   CQueryInfo::CQueryInfo()

**************************************************************************/

CQueryInfo::CQueryInfo(LPCITEMIDLIST pidl)
{
m_pPidlMgr = new CPidlMgr();
if(!m_pPidlMgr)
   {
   delete this;
   return;
   }

//get the shell's IMalloc pointer
//we'll keep this until we get destroyed
if(FAILED(SHGetMalloc(&m_pMalloc)))
   {
   delete this;
   return;
   }

m_pidl = m_pPidlMgr->Copy(pidl);

m_ObjRefCount = 1;

g_DllRefCount++;
}

/**************************************************************************

   CQueryInfo::~CQueryInfo()

**************************************************************************/

CQueryInfo::~CQueryInfo()
{
if(m_pidl)
   {
   m_pPidlMgr->Delete(m_pidl);
   m_pidl = NULL;
   }

if(m_pMalloc)
   {
   m_pMalloc->Release();
   }

if(m_pPidlMgr)
   {
   delete m_pPidlMgr;
   }

g_DllRefCount--;
}

///////////////////////////////////////////////////////////////////////////
//
// IUnknown Implementation
//

/**************************************************************************

   CQueryInfo::QueryInterface

**************************************************************************/

STDMETHODIMP CQueryInfo::QueryInterface(REFIID riid, LPVOID *ppReturn)
{
*ppReturn = NULL;

//IUnknown
if(IsEqualIID(riid, IID_IUnknown))
   {
   *ppReturn = this;
   }

//IQueryInfo
else if(IsEqualIID(riid, IID_IQueryInfo))
   {
   *ppReturn = (IQueryInfo*)this;
   }

if(*ppReturn)
   {
   (*(LPUNKNOWN*)ppReturn)->AddRef();
   return S_OK;
   }

return E_NOINTERFACE;
}                                             

/**************************************************************************

   CQueryInfo::AddRef

**************************************************************************/

STDMETHODIMP_(DWORD) CQueryInfo::AddRef()
{
return ++m_ObjRefCount;
}

/**************************************************************************

   CQueryInfo::Release

**************************************************************************/

STDMETHODIMP_(DWORD) CQueryInfo::Release()
{
if(--m_ObjRefCount == 0)
   {
   delete this;
   return 0;
   }
   
return m_ObjRefCount;
}

///////////////////////////////////////////////////////////////////////////
//
// IQueryInfo Implementation
//

/**************************************************************************

   CQueryInfo::GetInfoTip()
   
**************************************************************************/

STDMETHODIMP CQueryInfo::GetInfoTip(DWORD dwFlags, WCHAR **ppwszTip)
{
TCHAR szTipText[MAX_PATH];
int   cchOleStr;

*ppwszTip = NULL;

//get the entire text for the item
m_pPidlMgr->GetPidlPath(m_pidl, szTipText, sizeof(szTipText));

//get the number of characters required
cchOleStr = lstrlen(szTipText) + 1;

//allocate the wide character string
*ppwszTip = (LPWSTR)m_pMalloc->Alloc(cchOleStr * sizeof(WCHAR));
if(!*ppwszTip)
   return E_OUTOFMEMORY;

LocalToWideChar(*ppwszTip, szTipText, cchOleStr);

return S_OK;
}

/**************************************************************************

   CQueryInfo::GetInfoFlags()
   
**************************************************************************/

STDMETHODIMP CQueryInfo::GetInfoFlags(LPDWORD pdwFlags)
{
return E_NOTIMPL;
}

#endif   //(_WIN32_IE >= 0x0400)