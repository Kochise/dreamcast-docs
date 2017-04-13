/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1997 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          ShlFldr.cpp
   
   Description:   Implements CShellFolder.

**************************************************************************/

/**************************************************************************
   #include statements
**************************************************************************/

#include "ShlFldr.h"
#include "ShlView.h"
#include "InfoTip.h"
#include "ExtrIcon.h"
#include "Guid.h"
#include "resource.h"

/**************************************************************************

   CShellFolder::CShellFolder()

**************************************************************************/

CShellFolder::CShellFolder(CShellFolder *pParent, LPCITEMIDLIST pidl)
{
m_hKeyRoot = NULL;
m_lpszSubKey = NULL;

m_pSFParent = pParent;
if(m_pSFParent)
   m_pSFParent->AddRef();

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

if(m_pidl)
   {
   //determine if this PIDL has an HKEY or a sub key string
   if(m_pPidlMgr->IsRootKey(m_pidl))
      {
      //this is a root key
      m_pPidlMgr->GetRootKey(m_pidl, &m_hKeyRoot);
      }

   DWORD dwSize = m_pPidlMgr->GetSubKeyText(m_pidl, NULL, 0);
   m_lpszSubKey = new TCHAR[dwSize];
   if(m_lpszSubKey)
      {
      m_pPidlMgr->GetSubKeyText(m_pidl, m_lpszSubKey, dwSize);
      }
   }

m_ObjRefCount = 1;

g_DllRefCount++;
}

/**************************************************************************

   CShellFolder::~CShellFolder()

**************************************************************************/

CShellFolder::~CShellFolder()
{
if(m_pidl)
   {
   m_pPidlMgr->Delete(m_pidl);
   m_pidl = NULL;
   }

if(m_lpszSubKey)
   delete m_lpszSubKey;

if(m_pSFParent)
   m_pSFParent->Release();

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

   CShellFolder::QueryInterface

**************************************************************************/

STDMETHODIMP CShellFolder::QueryInterface(REFIID riid, LPVOID *ppReturn)
{
*ppReturn = NULL;

//IUnknown
if(IsEqualIID(riid, IID_IUnknown))
   {
   *ppReturn = this;
   }

//IPersistFolder
else if(IsEqualIID(riid, IID_IPersistFolder))
   {
   *ppReturn = (IPersistFolder*)this;
   }

//IShellFolder
else if(IsEqualIID(riid, IID_IShellFolder))
   {
   *ppReturn = (IShellFolder*)this;
   }

if(*ppReturn)
   {
   (*(LPUNKNOWN*)ppReturn)->AddRef();
   return S_OK;
   }

return E_NOINTERFACE;
}                                             

/**************************************************************************

   CShellFolder::AddRef

**************************************************************************/

STDMETHODIMP_(DWORD) CShellFolder::AddRef()
{
return ++m_ObjRefCount;
}

/**************************************************************************

   CShellFolder::Release

**************************************************************************/

STDMETHODIMP_(DWORD) CShellFolder::Release()
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
// IPersist Implementation
//

/**************************************************************************

   CShellView::GetClassID()
   
**************************************************************************/

STDMETHODIMP CShellFolder::GetClassID(LPCLSID lpClassID)
{
*lpClassID = CLSID_RegViewNameSpace;

return S_OK;
}

///////////////////////////////////////////////////////////////////////////
//
// IPersistFolder Implementation
//

/**************************************************************************

   CShellView::Initialize()
   
**************************************************************************/

STDMETHODIMP CShellFolder::Initialize(LPCITEMIDLIST pidl)
{
return S_OK;
}

///////////////////////////////////////////////////////////////////////////
//
// IShellFolder Implementation
//

/**************************************************************************

   CShellFolder::BindToObject()
   
**************************************************************************/

STDMETHODIMP CShellFolder::BindToObject(  LPCITEMIDLIST pidl, 
                                          LPBC pbcReserved, 
                                          REFIID riid, 
                                          LPVOID *ppvOut)
{
*ppvOut = NULL;

CShellFolder   *pShellFolder = new CShellFolder(this, pidl);
if(!pShellFolder)
   return E_OUTOFMEMORY;

HRESULT  hr = pShellFolder->QueryInterface(riid, ppvOut);

pShellFolder->Release();

return hr;
}

/**************************************************************************

   CShellFolder::BindToStorage()
   
**************************************************************************/

STDMETHODIMP CShellFolder::BindToStorage( LPCITEMIDLIST pidl, 
                                          LPBC pbcReserved, 
                                          REFIID riid, 
                                          LPVOID *ppvOut)
{
*ppvOut = NULL;

return E_NOTIMPL;
}

/**************************************************************************

   CShellFolder::CompareIDs()
   
**************************************************************************/

STDMETHODIMP CShellFolder::CompareIDs( LPARAM lParam, 
                                       LPCITEMIDLIST pidl1, 
                                       LPCITEMIDLIST pidl2)
{
TCHAR szString1[MAX_PATH] = TEXT("");
TCHAR szString2[MAX_PATH] = TEXT("");
HKEY  hkey1 = NULL,
      hkey2 = NULL;
int   nReturn;

/*
Special case - If one of the items is a key and the other is a value, always 
make the key come before the value.
*/
LPCITEMIDLIST  pidlTemp1 = pidl1,
               pidlTemp2 = pidl2;

//get the last item in each list
while((m_pPidlMgr->GetNextItem(pidlTemp1))->mkid.cb)
   pidlTemp1 = m_pPidlMgr->GetNextItem(pidlTemp1);
while((m_pPidlMgr->GetNextItem(pidlTemp2))->mkid.cb)
   pidlTemp2 = m_pPidlMgr->GetNextItem(pidlTemp2);

//at this point, both pidlTemp1 and pidlTemp2 point to the last item in the list
if(m_pPidlMgr->IsValue(pidlTemp1) != m_pPidlMgr->IsValue(pidlTemp2))
   {
   if(m_pPidlMgr->IsValue(pidlTemp1))
      return 1;

   return -1;
   }

//get the numeric value of the root key
m_pPidlMgr->GetRootKey(pidl1, &hkey1);
m_pPidlMgr->GetRootKey(pidl2, &hkey2);

//compare the root keys
if(hkey1 != hkey2)
   {
   return (int)((DWORD)hkey1 - (DWORD)hkey2);
   }

//now compare the subkey strings
m_pPidlMgr->GetSubKeyText( pidl1, 
                           szString1, 
                           sizeof(szString1));
m_pPidlMgr->GetSubKeyText( pidl2, 
                           szString2, 
                           sizeof(szString2));
nReturn = lstrcmpi(szString1, szString2);
if(nReturn)
   return nReturn;

//now compare the value strings
m_pPidlMgr->GetValueText(  pidl1, 
                           szString1, 
                           sizeof(szString1));
m_pPidlMgr->GetValueText(  pidl2, 
                           szString2, 
                           sizeof(szString2));
return lstrcmpi(szString1, szString2);
}

/**************************************************************************

   CShellFolder::CreateViewObject()
   
**************************************************************************/

STDMETHODIMP CShellFolder::CreateViewObject( HWND hwndOwner, 
                                             REFIID riid, 
                                             LPVOID *ppvOut)
{
HRESULT     hr;
CShellView  *pShellView;

*ppvOut = NULL;

pShellView = new CShellView(this, m_pidl);
if(!pShellView)
   return E_OUTOFMEMORY;

hr = pShellView->QueryInterface(riid, ppvOut);

pShellView->Release();

return hr;
}

/**************************************************************************

   CShellFolder::EnumObjects()
   
**************************************************************************/

STDMETHODIMP CShellFolder::EnumObjects(   HWND hwndOwner, 
                                          DWORD dwFlags, 
                                          LPENUMIDLIST *ppEnumIDList)
{
HRESULT  hr;

*ppEnumIDList = NULL;

*ppEnumIDList = new CEnumIDList(GetRootKey(), m_lpszSubKey, dwFlags, &hr);
if(!*ppEnumIDList)
   return hr;

return S_OK;
}

/**************************************************************************

   CShellFolder::GetAttributesOf()
   
**************************************************************************/

STDMETHODIMP CShellFolder::GetAttributesOf(  UINT uCount, 
                                             LPCITEMIDLIST aPidls[], 
                                             LPDWORD pdwAttribs)
{
UINT  i;

*pdwAttribs = (DWORD)-1;

for(i = 0; i < uCount; i++)
   {
   DWORD dwAttribs = 0;

   //flags common to all items
   dwAttribs |= 0;

   //is this item a key?
   if(!m_pPidlMgr->IsValue(m_pPidlMgr->GetLastItem(aPidls[i])))
      {
      dwAttribs |= SFGAO_FOLDER;

      //does this item have a sub folder?
      if(m_pPidlMgr->HasSubKeys(GetRootKey(), m_lpszSubKey, aPidls[i]))
         dwAttribs |= SFGAO_HASSUBFOLDER;
      }
   
   *pdwAttribs &= dwAttribs;
   }

return S_OK;
}

/**************************************************************************

   CShellFolder::GetUIObjectOf()
   
**************************************************************************/

STDMETHODIMP CShellFolder::GetUIObjectOf( HWND hwndOwner, 
                                          UINT uCount, 
                                          LPCITEMIDLIST *pPidl, 
                                          REFIID riid, 
                                          LPUINT puReserved, 
                                          LPVOID *ppvReturn)
{
*ppvReturn = NULL;

if(uCount != 1)
   return E_FAIL;

if(IsEqualIID(riid, IID_IExtractIcon))
   {
   CExtractIcon   *pei;
   LPITEMIDLIST   pidl;

   pidl = m_pPidlMgr->Concatenate(m_pidl, pPidl[0]);

   pei = new CExtractIcon(pidl);

   /*
   The temp PIDL can be deleted because the new CExtractIcon either failed or 
   made its own copy of it.
   */
   m_pPidlMgr->Delete(pidl);

   if(pei)
      {
      *ppvReturn = pei;
      return S_OK;
      }
   
   return E_OUTOFMEMORY;
   }

#if (_WIN32_IE >= 0x0400)
if(IsEqualIID(riid, IID_IQueryInfo))
   {
   CQueryInfo     *pqit;
   LPITEMIDLIST   pidl;

   pidl = m_pPidlMgr->Concatenate(m_pidl, pPidl[0]);

   pqit = new CQueryInfo(pidl);

   /*
   The temp PIDL can be deleted because the new CQueryInfo either failed or 
   made its own copy of it.
   */
   m_pPidlMgr->Delete(pidl);

   if(pqit)
      {
      *ppvReturn = pqit;
      return S_OK;
      }
   
   return E_OUTOFMEMORY;
   }
#endif   //#if (_WIN32_IE >= 0x0400)

return E_NOINTERFACE;
}

/**************************************************************************

   CShellFolder::GetDisplayNameOf()
   
**************************************************************************/

#define GET_SHGDN_FOR(dwFlags)         ((DWORD)dwFlags & (DWORD)0x0000FF00)
#define GET_SHGDN_RELATION(dwFlags)    ((DWORD)dwFlags & (DWORD)0x000000FF)

STDMETHODIMP CShellFolder::GetDisplayNameOf( LPCITEMIDLIST pidl, 
                                             DWORD dwFlags, 
                                             LPSTRRET lpName)
{
TCHAR szText[MAX_PATH];
int   cchOleStr;

switch(GET_SHGDN_FOR(dwFlags))
   {
   case SHGDN_FORPARSING:
   case SHGDN_FORADDRESSBAR:
   case SHGDN_NORMAL:
      switch(GET_SHGDN_RELATION(dwFlags))
         {
         case SHGDN_NORMAL:
            //get the full name
            m_pPidlMgr->GetPidlPath(pidl, szText, sizeof(szText));

            //If the text is NULL and this is a value, get the default item name.
            if(!*szText && m_pPidlMgr->IsValue(m_pPidlMgr->GetLastItem(pidl)))
               {
               LoadString(g_hInst, IDS_DEFAULT, szText, sizeof(szText));
               }
            break;

         case SHGDN_INFOLDER:
            {
            LPITEMIDLIST   pidlTemp = m_pPidlMgr->GetLastItem(pidl);

            //get the relative name
   	      m_pPidlMgr->GetItemText(pidlTemp, szText, sizeof(szText));

            //If the text is NULL and this is a value, get the default item name.
            if(!*szText && m_pPidlMgr->IsValue(pidlTemp))
               {
               LoadString(g_hInst, IDS_DEFAULT, szText, sizeof(szText));
               }
            }
            break;

         default:
            return E_INVALIDARG;
         }
      break;
   
   default:
      return E_INVALIDARG;
   }

//get the number of characters required
cchOleStr = lstrlen(szText) + 1;

//allocate the wide character string
lpName->pOleStr = (LPWSTR)m_pMalloc->Alloc(cchOleStr * sizeof(WCHAR));
if(!lpName->pOleStr)
   return E_OUTOFMEMORY;

lpName->uType = STRRET_WSTR;

LocalToWideChar(lpName->pOleStr, szText, cchOleStr);

return S_OK;
}

/**************************************************************************

   CShellFolder::ParseDisplayName()
   
**************************************************************************/

STDMETHODIMP CShellFolder::ParseDisplayName( HWND hwndOwner, 
                                             LPBC pbcReserved, 
                                             LPOLESTR lpDisplayName, 
                                             LPDWORD pdwEaten, 
                                             LPITEMIDLIST *pPidlNew, 
                                             LPDWORD pdwAttributes)
{
return E_NOTIMPL;
}

/**************************************************************************

   CShellFolder::SetNameOf()
   
**************************************************************************/

STDMETHODIMP CShellFolder::SetNameOf(  HWND hwndOwner, 
                                       LPCITEMIDLIST pidl, 
                                       LPCOLESTR lpName, 
                                       DWORD dw, 
                                       LPITEMIDLIST *pPidlOut)
{
return E_NOTIMPL;
}

/**************************************************************************

   CShellFolder::GetFolderPath()
   
**************************************************************************/

BOOL CShellFolder::GetFolderPath(LPTSTR lpszOut, DWORD dwOutSize)
{
TCHAR    szTemp[MAX_PATH] = TEXT("");
DWORD    dwSize;

if(!lpszOut)
   return FALSE;

*lpszOut = 0;

//get the text for the root key
GetRootKeyText(m_hKeyRoot, szTemp, sizeof(szTemp));

dwSize = lstrlen(szTemp);
if(m_lpszSubKey)
   dwSize += lstrlen(m_lpszSubKey) + 1;

//is the output buffer big enough?
if(dwSize > dwOutSize)
   return FALSE;

//add the text we already have
lstrcpy(lpszOut, szTemp);

//add this folder's text if present
if(m_lpszSubKey && *m_lpszSubKey)
   {
   lstrcat(lpszOut, TEXT("\\"));
   lstrcat(lpszOut, m_lpszSubKey);
   }

return TRUE;
}

/**************************************************************************

   CShellFolder::GetFolderText()
   
**************************************************************************/

BOOL CShellFolder::GetFolderText(LPTSTR lpszOut, DWORD dwOutSize)
{
if(!lpszOut)
   return FALSE;

*lpszOut = 0;

//add this folder's text if present
if(m_lpszSubKey && *m_lpszSubKey)
   {
   lstrcpyn(lpszOut, m_lpszSubKey, dwOutSize);
   }

return TRUE;
}

/**************************************************************************

   CShellFolder::GetRootKey()
   
**************************************************************************/

HKEY CShellFolder::GetRootKey(void)
{
HKEY  hkReturn = NULL;
CShellFolder   *pTemp = this;

while(pTemp)
   {
   if(pTemp->m_hKeyRoot)
      {
      hkReturn = pTemp->m_hKeyRoot;
      break;
      }
   
   pTemp = pTemp->m_pSFParent;
   }

return hkReturn;
}

