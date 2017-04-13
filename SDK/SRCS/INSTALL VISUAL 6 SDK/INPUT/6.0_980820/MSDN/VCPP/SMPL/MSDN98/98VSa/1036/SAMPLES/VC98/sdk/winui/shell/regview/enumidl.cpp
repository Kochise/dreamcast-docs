/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1997 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          EnumIDL.cpp
   
   Description:   Implements IEnumIDList.

**************************************************************************/

/**************************************************************************
   #include statements
**************************************************************************/

#include "EnumIDL.h"
#include "ShlFldr.h"

/**************************************************************************

   CEnumIDList::CEnumIDList

**************************************************************************/

CEnumIDList::CEnumIDList(HKEY hKeyRoot, LPCTSTR lpszSubKey, DWORD dwFlags, HRESULT *pResult)
{
if(pResult)
   *pResult = S_OK;

m_pFirst = m_pLast = m_pCurrent = NULL;

m_pPidlMgr = new CPidlMgr();
if(!m_pPidlMgr)
   {
   if(pResult)
      *pResult = E_OUTOFMEMORY;

   delete this;
   return;
   }

//get the shell's IMalloc pointer
//we'll keep this until we get destroyed
if(FAILED(SHGetMalloc(&m_pMalloc)))
   {
   if(pResult)
      *pResult = E_OUTOFMEMORY;

   delete this;
   return;
   }

if(!CreateEnumList(hKeyRoot, lpszSubKey, dwFlags))
   {
   if(pResult)
      *pResult = E_OUTOFMEMORY;

   delete this;
   return;
   }

m_ObjRefCount = 1;

g_DllRefCount++;
}

/**************************************************************************

   CEnumIDList::~CEnumIDList

**************************************************************************/

CEnumIDList::~CEnumIDList()
{
DeleteList();

if(m_pMalloc)
   m_pMalloc->Release();

if(m_pPidlMgr)
   delete m_pPidlMgr;

g_DllRefCount--;
}

/**************************************************************************

   CEnumIDList::QueryInterface

**************************************************************************/

STDMETHODIMP CEnumIDList::QueryInterface(REFIID riid, LPVOID *ppReturn)
{
*ppReturn = NULL;

//IUnknown
if(IsEqualIID(riid, IID_IUnknown))
   {
   *ppReturn = this;
   }
   
//IEnumIDList
else if(IsEqualIID(riid, IID_IEnumIDList))
   {
   *ppReturn = (IEnumIDList*)this;
   }   

if(*ppReturn)
   {
   (*(LPUNKNOWN*)ppReturn)->AddRef();
   return S_OK;
   }

return E_NOINTERFACE;
}                                             

/**************************************************************************

   CEnumIDList::AddRef

**************************************************************************/

STDMETHODIMP_(DWORD) CEnumIDList::AddRef()
{
return ++m_ObjRefCount;
}


/**************************************************************************

   CEnumIDList::Release

**************************************************************************/

STDMETHODIMP_(DWORD) CEnumIDList::Release()
{
if(--m_ObjRefCount == 0)
   {
   delete this;
   return 0;
   }
   
return m_ObjRefCount;
}

/**************************************************************************

   CEnumIDList::Next()
   
**************************************************************************/

STDMETHODIMP CEnumIDList::Next(DWORD dwElements, LPITEMIDLIST apidl[], LPDWORD pdwFetched)
{
DWORD    dwIndex;
HRESULT  hr = S_OK;

if(dwElements > 1 && !pdwFetched)
   return E_INVALIDARG;

for(dwIndex = 0; dwIndex < dwElements; dwIndex++)
   {
   //is this the last item in the list?
   if(!m_pCurrent)
      {
      hr =  S_FALSE;
      break;
      }

   apidl[dwIndex] = m_pPidlMgr->Copy(m_pCurrent->pidl);

   m_pCurrent = m_pCurrent->pNext;
   }

if(pdwFetched)
   *pdwFetched = dwIndex;

return hr;
}

/**************************************************************************

   CEnumIDList::Skip()
   
**************************************************************************/

STDMETHODIMP CEnumIDList::Skip(DWORD dwSkip)
{
DWORD    dwIndex;
HRESULT  hr = S_OK;

for(dwIndex = 0; dwIndex < dwSkip; dwIndex++)
   {
   //is this the last item in the list?
   if(!m_pCurrent)
      {
      hr = S_FALSE;
      break;
      }

   m_pCurrent = m_pCurrent->pNext;
   }

return hr;
}

/**************************************************************************

   CEnumIDList::Reset()
   
**************************************************************************/

STDMETHODIMP CEnumIDList::Reset(void)
{
m_pCurrent = m_pFirst;

return S_OK;
}

/**************************************************************************

   CEnumIDList::Clone()
   
**************************************************************************/

STDMETHODIMP CEnumIDList::Clone(LPENUMIDLIST *ppEnum)
{
return E_NOTIMPL;
}

/**************************************************************************

   CEnumIDList::CreateEnumList()
   
**************************************************************************/

BOOL CEnumIDList::CreateEnumList(HKEY hKeyRoot, LPCTSTR lpszSubKey, DWORD dwFlags)
{
LPITEMIDLIST   pidl;
DWORD          dwIndex;

//enumerate the folders (keys)
if(dwFlags & SHCONTF_FOLDERS)
   {
   /*
   special case - we can't enumerate the root level keys (HKEY_CLASSES_ROOT, etc.), 
   so if both of these are NULL, then we need to fake an enumeration of those.
   */
   if((!hKeyRoot) && (!lpszSubKey))
      {
      HKEY  ahKey[] = { HKEY_CLASSES_ROOT,
                        HKEY_CURRENT_USER,
                        HKEY_LOCAL_MACHINE,
                        HKEY_USERS,
                        HKEY_PERFORMANCE_DATA,
                        HKEY_CURRENT_CONFIG,
                        HKEY_DYN_DATA,
                        (HKEY)-1};
      
      for(dwIndex = 0; ahKey[dwIndex] != (HKEY)-1; dwIndex++)
         {
         //only add the root keys that actually exists on this system
         if(RootKeyExists(ahKey[dwIndex]))
            {
            //create the pidl for this item
            pidl = m_pPidlMgr->CreateRootKey(ahKey[dwIndex]);
            if(pidl)
               {
               if(!AddToEnumList(pidl))
                  return FALSE;
               }
            else
               {
               return FALSE;
               }
            }   
         }
      }
   else
      {
      TCHAR    szKey[REGSTR_MAX_VALUE_LENGTH];

      dwIndex = 0;

      //get the next item
      while(GetKeyName(hKeyRoot, lpszSubKey, dwIndex++, szKey, sizeof(szKey)))
         {
         //create the pidl for this item
         pidl = m_pPidlMgr->CreateSubKey(szKey);
         if(pidl)
            {
            if(!AddToEnumList(pidl))
               return FALSE;
            }
         else
            {
            return FALSE;
            }   
         }
      }
   }   

//enumerate the non-folder items (values)
if(dwFlags & SHCONTF_NONFOLDERS)
   {
   TCHAR    szValue[REGSTR_MAX_VALUE_LENGTH];

   dwIndex = 0;

   /*
   There is a special case here. All keys have a default value, but if the 
   default value is empty, then it won't be enumerated. If it has data, then 
   it will be enumerated but the name will be NULL. 
   
   To work around this, we will add a default item here and then not add it 
   if it shows up in the enumeration in the loop below.
   */
   //create the default item
   pidl = m_pPidlMgr->CreateValue(TEXT(""));
   if(pidl)
      {
      if(!AddToEnumList(pidl))
         return FALSE;
      }
   else
      {
      return FALSE;
      }   
   
   //get the items
   while(GetValueName(hKeyRoot, lpszSubKey, dwIndex++, szValue, sizeof(szValue)))
      {
      //don't add a default value that may have shown up in the enumeration
      if(!szValue[0])
         continue;

      //create the pidl for this item
      pidl = m_pPidlMgr->CreateValue(szValue);

      if(pidl)
         {
         if(!AddToEnumList(pidl))
            return FALSE;
         }
      else
         {
         return FALSE;
         }   
      }
   }
   
return TRUE;
}

/**************************************************************************

   CEnumIDList::AddToEnumList()
   
**************************************************************************/

BOOL CEnumIDList::AddToEnumList(LPITEMIDLIST pidl)
{
LPENUMLIST  pNew;

pNew = (LPENUMLIST)m_pMalloc->Alloc(sizeof(ENUMLIST));

if(pNew)
   {
   //set the next pointer
   pNew->pNext = NULL;
   pNew->pidl = pidl;

   //is this the first item in the list?
   if(!m_pFirst)
      {
      m_pFirst = pNew;
      m_pCurrent = m_pFirst;
      }
   
   if(m_pLast)
      {
      //add the new item to the end of the list
      m_pLast->pNext = pNew;
      }
   
   //update the last item pointer
   m_pLast = pNew;

   return TRUE;
   }

return FALSE;
}

/**************************************************************************

   CEnumIDList::DeleteList()
   
**************************************************************************/

BOOL CEnumIDList::DeleteList(void)
{
LPENUMLIST  pDelete;

while(m_pFirst)
   {
   pDelete = m_pFirst;
   m_pFirst = pDelete->pNext;

   //free the pidl
   //m_pMalloc->Free(pDelete->pidl);
   m_pPidlMgr->Delete(pDelete->pidl);
   
   //free the list item
   m_pMalloc->Free(pDelete);
   }

m_pFirst = m_pLast = m_pCurrent = NULL;

return TRUE;
}

