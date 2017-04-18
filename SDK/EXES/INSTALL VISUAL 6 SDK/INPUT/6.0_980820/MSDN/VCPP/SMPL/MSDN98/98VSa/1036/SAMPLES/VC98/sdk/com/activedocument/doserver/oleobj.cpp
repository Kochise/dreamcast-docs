/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1997 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          OleObj.cpp
   
   Description:   COleObject implementation.

**************************************************************************/

/**************************************************************************
   #include statements
**************************************************************************/

#include "OleObj.h"

/**************************************************************************

   COleObject::COleObject()
   
**************************************************************************/

COleObject::COleObject(COleDocument *pOleDoc)
{
OutputDebugString(TEXT("COleObject's constructor\n"));

m_pOleDoc = pOleDoc;

m_fOpen = FALSE;
}

/**************************************************************************

   COleObject::~COleObject()
   
**************************************************************************/

COleObject::~COleObject()
{
OutputDebugString(TEXT("COleObject's destructor\n"));
}

/**************************************************************************

   COleObject::QueryInterface()
   
**************************************************************************/

STDMETHODIMP COleObject::QueryInterface(REFIID riid, LPVOID *ppReturn)
{
OutputDebugString(TEXT("COleObject::QueryInterface\n"));

return m_pOleDoc->QueryInterface(riid, ppReturn);
}

/**************************************************************************

   COleObject::AddRef()
   
**************************************************************************/

STDMETHODIMP_(ULONG) COleObject::AddRef()
{
OutputDebugString(TEXT("COleObject::AddRef\n"));

return m_pOleDoc->AddRef();
}

/**************************************************************************

   COleObject::Release()
   
**************************************************************************/

STDMETHODIMP_(ULONG) COleObject::Release()
{
OutputDebugString(TEXT("COleObject::Release\n"));

return m_pOleDoc->Release();
}

/**************************************************************************

   COleObject::DoVerb()
   
**************************************************************************/

STDMETHODIMP COleObject::DoVerb( LONG iVerb,
                                 LPMSG lpmsg,
                                 LPOLECLIENTSITE pActiveSite,
                                 LONG lindex,
                                 HWND hwndParent,
                                 LPCRECT lprcPosRect)
{
OutputDebugString(TEXT("COleObject::DoVerb\n"));

HRESULT  hr = E_FAIL;

switch (iVerb)
   {
   case OLEIVERB_SHOW:
   case OLEIVERB_PRIMARY:
   case OLEIVERB_UIACTIVATE:
      {
      //try to get the IOleDocumentSite pointer
      LPOLEDOCUMENTSITE pOleDocSite;
      hr = pActiveSite->QueryInterface(IID_IOleDocumentSite, (LPVOID*)&pOleDocSite);
      if(SUCCEEDED(hr))
         {
         //passing NULL to this will cause the site to call our CreateView method
         hr = pOleDocSite->ActivateMe(NULL);
         }
      }
      break;

   default:
      break;
   }

return hr;
}

/**************************************************************************

   COleObject::GetClientSite()
   
**************************************************************************/

STDMETHODIMP COleObject::GetClientSite(LPOLECLIENTSITE *ppClientSite)
{
OutputDebugString(TEXT("COleObject::GetClientSite\n"));

*ppClientSite = m_pOleDoc->m_pOleClientSite;

return S_OK;
}

/**************************************************************************

   COleObject::SetClientSite()
   
**************************************************************************/

STDMETHODIMP COleObject::SetClientSite(LPOLECLIENTSITE pClientSite)
{
OutputDebugString(TEXT("COleObject::SetClientSite\n"));

// if we already have a client site, release it.
if(m_pOleDoc->m_pOleClientSite)
   {
   m_pOleDoc->m_pOleClientSite->Release();
   m_pOleDoc->m_pOleClientSite = NULL;
   }

// store copy of the client site.
m_pOleDoc->m_pOleClientSite = pClientSite;

// AddRef it so it doesn't go away.
if(m_pOleDoc->m_pOleClientSite)
   m_pOleDoc->m_pOleClientSite->AddRef();

return S_OK;
}

/**************************************************************************

   COleObject::Advise()
   
**************************************************************************/

STDMETHODIMP COleObject::Advise(LPADVISESINK pAdvSink, LPDWORD pdwConnection)
{
OutputDebugString(TEXT("COleObject::Advise\n"));

// if we haven't made an OleAdviseHolder yet, make one.
if(!m_pOleDoc->m_pOleAdviseHolder)
   CreateOleAdviseHolder(&m_pOleDoc->m_pOleAdviseHolder);

// pass this call onto the OleAdviseHolder.
return m_pOleDoc->m_pOleAdviseHolder->Advise(pAdvSink, pdwConnection);
}

/**************************************************************************

   COleObject::Unadvise()
   
**************************************************************************/

STDMETHODIMP COleObject::Unadvise(DWORD dwConnection)
{
OutputDebugString(TEXT("COleObject::Unadvise\n"));

// pass on to OleAdviseHolder.
return m_pOleDoc->m_pOleAdviseHolder->Unadvise(dwConnection);
}

/**************************************************************************

   COleObject::SetHostNames()
   
**************************************************************************/

STDMETHODIMP COleObject::SetHostNames(LPCOLESTR szContainerApp, LPCOLESTR szContainerObj)
{
OutputDebugString(TEXT("COleObject::SetHostNames\n"));

return S_OK;
}

/**************************************************************************

   COleObject::GetExtent()
   
**************************************************************************/

STDMETHODIMP COleObject::GetExtent(DWORD dwDrawAspect, LPSIZEL lpsizel)
{
OutputDebugString(TEXT("COleObject::GetExtent\n"));

return E_NOTIMPL;
}

/**************************************************************************

   COleObject::SetExtent()
   
**************************************************************************/

STDMETHODIMP COleObject::SetExtent(DWORD dwDrawAspect, LPSIZEL lpsizel)
{
OutputDebugString(TEXT("COleObject::SetExtent\n"));

return E_NOTIMPL;
}

/**************************************************************************

   COleObject::Update()
   
**************************************************************************/

STDMETHODIMP COleObject::Update()
{
OutputDebugString(TEXT("COleObject::Update\n"));

return S_OK;
}

/**************************************************************************

   COleObject::Close()
   
**************************************************************************/

STDMETHODIMP COleObject::Close(DWORD dwSaveOption)
{
OutputDebugString(TEXT("COleObject::Close\n"));

switch(dwSaveOption)
   {
   case OLECLOSE_SAVEIFDIRTY:
      if(m_pOleDoc->m_fDirty)
         {
         m_pOleDoc->m_pPersistStorage->Save(NULL, TRUE);
         }
      break;

   case OLECLOSE_NOSAVE:
      break;

   case OLECLOSE_PROMPTSAVE:
      break;
   }

//close the view
m_pOleDoc->m_pOleDocView->CloseView(0);

return S_OK;
}

/**************************************************************************

   COleObject::EnumVerbs()
   
**************************************************************************/

STDMETHODIMP COleObject::EnumVerbs(LPENUMOLEVERB *ppenumOleVerb)
{
OutputDebugString(TEXT("COleObject::EnumVerbs\n"));

return OLE_S_USEREG;
}

/**************************************************************************

   COleObject::SetMoniker()
   
**************************************************************************/

STDMETHODIMP COleObject::SetMoniker(DWORD dwWhichMoniker, LPMONIKER pMoniker)
{
OutputDebugString(TEXT("COleObject::SetMoniker\n"));

LPMONIKER pTempMoniker;

if(!m_pOleDoc->m_pOleClientSite)
   return E_FAIL;

if(NOERROR != m_pOleDoc->m_pOleClientSite->GetMoniker(OLEGETMONIKER_ONLYIFTHERE, OLEWHICHMK_OBJFULL, &pTempMoniker))
   return E_FAIL;

if(m_pOleDoc->m_pOleAdviseHolder)
   m_pOleDoc->m_pOleAdviseHolder->SendOnRename(pTempMoniker);

LPRUNNINGOBJECTTABLE pRot;

if(NOERROR == GetRunningObjectTable(0, &pRot))
   {
   if(m_pOleDoc->m_dwRegister)
      pRot->Revoke(m_pOleDoc->m_dwRegister);

   pRot->Register(0, m_pOleDoc, pTempMoniker, &m_pOleDoc->m_dwRegister);

   pRot->Release();
   }

return S_OK;
}

/**************************************************************************

   COleObject::GetMoniker()
   
**************************************************************************/

STDMETHODIMP COleObject::GetMoniker(   DWORD dwAssign, 
                                       DWORD dwWhichMoniker,
                                       LPMONIKER *ppmk)
{
OutputDebugString(TEXT("COleObject::GetMoniker\n"));

*ppmk = NULL;

return m_pOleDoc->m_pOleClientSite->GetMoniker(OLEGETMONIKER_ONLYIFTHERE, OLEWHICHMK_OBJFULL, ppmk);
}

/**************************************************************************

   COleObject::InitFromData()
   
**************************************************************************/

STDMETHODIMP COleObject::InitFromData( LPDATAOBJECT pDataObject,
                                       BOOL fCreation,
                                       DWORD dwReserved)
{
OutputDebugString(TEXT("COleObject::InitFromData\n"));

return E_NOTIMPL;
}

/**************************************************************************

   COleObject::GetClipboardData()
   
**************************************************************************/

STDMETHODIMP COleObject::GetClipboardData(   DWORD dwReserved,
                                             LPDATAOBJECT *ppDataObject)
{
OutputDebugString(TEXT("COleObject::GetClipboardData\n"));

*ppDataObject = NULL;

return E_NOTIMPL;
}

/**************************************************************************

   COleObject::IsUpToDate()
   
**************************************************************************/

STDMETHODIMP COleObject::IsUpToDate()
{
OutputDebugString(TEXT("COleObject::IsUpToDate\n"));

return S_OK;
}

/**************************************************************************

   COleObject::GetUserClassID()
   
**************************************************************************/

STDMETHODIMP COleObject::GetUserClassID(CLSID *pClsid)
{
OutputDebugString(TEXT("COleObject::GetUserClassID\n"));

return m_pOleDoc->m_pPersistStorage->GetClassID(pClsid);
}

/**************************************************************************

   COleObject::GetUserType()
   
**************************************************************************/

STDMETHODIMP COleObject::GetUserType(DWORD dwFormOfType, LPOLESTR *pszUserType)
{
OutputDebugString(TEXT("COleObject::GetUserType\n"));

return OLE_S_USEREG;
}

/**************************************************************************

   COleObject::EnumAdvise()
   
**************************************************************************/

STDMETHODIMP COleObject::EnumAdvise(LPENUMSTATDATA *ppenumAdvise)
{
OutputDebugString(TEXT("COleObject::EnumAdvise\n"));

*ppenumAdvise = NULL;

// pass on to the OLE Advise holder.
return m_pOleDoc->m_pOleAdviseHolder->EnumAdvise(ppenumAdvise);
}

/**************************************************************************

   COleObject::GetMiscStatus()
   
**************************************************************************/

STDMETHODIMP COleObject::GetMiscStatus(DWORD dwAspect, DWORD *pdwStatus)
{
OutputDebugString(TEXT("COleObject::GetMiscStatus\n"));

*pdwStatus = NULL;

return OLE_S_USEREG;
}

/**************************************************************************

   COleObject::SetColorScheme()
   
**************************************************************************/

STDMETHODIMP COleObject::SetColorScheme(LPLOGPALETTE lpLogpal)
{
OutputDebugString(TEXT("COleObject::SetColorScheme\n"));

return S_OK;
}

