/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1997 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          ExtrIcon.cpp
   
   Description:   Implements CExtractIcon.

**************************************************************************/

/**************************************************************************
   #include statements
**************************************************************************/

#include "ExtrIcon.h"

/**************************************************************************

   CExtractIcon::CExtractIcon()

**************************************************************************/

CExtractIcon::CExtractIcon(LPCITEMIDLIST pidl)
{
m_pPidlMgr = new CPidlMgr();
if(!m_pPidlMgr)
   {
   delete this;
   return;
   }

m_pidl = m_pPidlMgr->Copy(pidl);

m_ObjRefCount = 1;

g_DllRefCount++;
}

/**************************************************************************

   CExtractIcon::~CExtractIcon()

**************************************************************************/

CExtractIcon::~CExtractIcon()
{
if(m_pidl)
   {
   m_pPidlMgr->Delete(m_pidl);
   m_pidl = NULL;
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

   CExtractIcon::QueryInterface

**************************************************************************/

STDMETHODIMP CExtractIcon::QueryInterface(REFIID riid, LPVOID *ppReturn)
{
*ppReturn = NULL;

//IUnknown
if(IsEqualIID(riid, IID_IUnknown))
   {
   *ppReturn = this;
   }

//IExtractIcon
else if(IsEqualIID(riid, IID_IExtractIcon))
   {
   *ppReturn = (IExtractIcon*)this;
   }

if(*ppReturn)
   {
   (*(LPUNKNOWN*)ppReturn)->AddRef();
   return S_OK;
   }

return E_NOINTERFACE;
}                                             

/**************************************************************************

   CExtractIcon::AddRef

**************************************************************************/

STDMETHODIMP_(DWORD) CExtractIcon::AddRef()
{
return ++m_ObjRefCount;
}

/**************************************************************************

   CExtractIcon::Release

**************************************************************************/

STDMETHODIMP_(DWORD) CExtractIcon::Release()
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
// IExtractIcon Implementation
//

/**************************************************************************

   CExtractIcon::GetIconLocation()
   
**************************************************************************/

STDMETHODIMP CExtractIcon::GetIconLocation(  UINT uFlags, 
                                             LPTSTR szIconFile, 
                                             UINT cchMax, 
                                             LPINT piIndex, 
                                             LPUINT puFlags)
{
//tell the shell to always call Extract
*puFlags = GIL_NOTFILENAME;

//the pidl is either a value or a folder, so find out which it is
if(m_pPidlMgr->IsValue(m_pPidlMgr->GetLastItem(m_pidl)))
   {
   //its a value
   DWORD dwType;

   //get the data type to determine which icon to get
   m_pPidlMgr->GetValueType(m_pidl, &dwType);

   switch(dwType)
      {
      case REG_BINARY:
      case REG_DWORD:
      case REG_DWORD_BIG_ENDIAN:
         *piIndex = ICON_INDEX_BINARY;
         break;

      default:
         *piIndex = ICON_INDEX_STRING;
         break;
         }
   }
else
   {
   //its a key
   if(uFlags & GIL_OPENICON)
      {
      *piIndex = ICON_INDEX_FOLDEROPEN;  //tell Extract to return the open icon
      }
   else
      {
      *piIndex = ICON_INDEX_FOLDER;  //tell Extract to return the open icon
      }
   }

return S_OK;
}

/**************************************************************************

   CExtractIcon::Extract()
   
**************************************************************************/

STDMETHODIMP CExtractIcon::Extract( LPCTSTR pszFile, 
                                    UINT nIconIndex, 
                                    HICON *phiconLarge, 
                                    HICON *phiconSmall, 
                                    UINT nIconSize)
{
*phiconLarge = ImageList_GetIcon(g_himlLarge, nIconIndex, ILD_TRANSPARENT);
*phiconSmall = ImageList_GetIcon(g_himlSmall, nIconIndex, ILD_TRANSPARENT);

/*
if(nIconIndex)
   {
   *phiconLarge = ImageList_GetIcon(g_himlLarge, ICON_INDEX_FOLDEROPEN, ILD_TRANSPARENT);
   *phiconSmall = ImageList_GetIcon(g_himlSmall, ICON_INDEX_FOLDEROPEN, ILD_TRANSPARENT);
   }
else
   {
   *phiconLarge = ImageList_GetIcon(g_himlLarge, ICON_INDEX_FOLDER, ILD_TRANSPARENT);
   *phiconSmall = ImageList_GetIcon(g_himlSmall, ICON_INDEX_FOLDER, ILD_TRANSPARENT);
   }
*/
return S_OK;
}

