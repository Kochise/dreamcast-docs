// oleobjct.cpp : implementation of the DocObject OLE server
//	document class IOleObject interface

// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1996 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include "afxbind.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

STDMETHODIMP_(ULONG) CDocObjectServerDoc::XDocOleObject::AddRef()
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, DocOleObject)
	return pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) CDocObjectServerDoc::XDocOleObject::Release()
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, DocOleObject)
	return pThis->ExternalRelease();
}

STDMETHODIMP CDocObjectServerDoc::XDocOleObject::QueryInterface(
	REFIID iid, LPVOID* ppvObj)
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, DocOleObject)
	return pThis->ExternalQueryInterface(&iid, ppvObj);
}

STDMETHODIMP CDocObjectServerDoc::XDocOleObject::SetClientSite(
	LPOLECLIENTSITE pClientSite)
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, DocOleObject)
	ASSERT_VALID(pThis);
	HRESULT hr = NOERROR;

	// Perform normal SetClientSite processing.
	hr = pThis->m_xOleObject.SetClientSite(pClientSite);
	if (hr != S_OK)
		return hr;

	// If we currently have a document site pointer, 
	// release it.
	if (pThis->m_pDocSite != NULL)
	{
		pThis->m_pDocSite->Release();
		pThis->m_pDocSite = NULL;
	}

	// Check to see whether this object should act
	// as a document object by querying for 
	// IOleDocumentSite.
	if (pClientSite != NULL)
		hr = pClientSite->QueryInterface(IID_IOleDocumentSite,
			(LPVOID*)&pThis->m_pDocSite);
	return hr;
}

STDMETHODIMP CDocObjectServerDoc::XDocOleObject::GetClientSite(
	LPOLECLIENTSITE* ppClientSite)
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, DocOleObject)
	ASSERT_VALID(pThis);
	return pThis->m_xOleObject.GetClientSite(ppClientSite);
}

STDMETHODIMP CDocObjectServerDoc::XDocOleObject::SetHostNames(
	LPCOLESTR lpszContainerApp, LPCOLESTR lpszContainerObj)
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, DocOleObject)
	ASSERT_VALID(pThis);
   return pThis->m_xOleObject.SetHostNames(lpszContainerApp,
                                           lpszContainerObj);
}

STDMETHODIMP CDocObjectServerDoc::XDocOleObject::Close(DWORD dwSaveOption)
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, DocOleObject)
	ASSERT_VALID(pThis);
	return pThis->m_xOleObject.Close(dwSaveOption);
}

STDMETHODIMP CDocObjectServerDoc::XDocOleObject::SetMoniker(
	DWORD dwWhichMoniker, LPMONIKER pmk)
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, DocOleObject)
	ASSERT_VALID(pThis);
	return pThis->m_xOleObject.SetMoniker(dwWhichMoniker, pmk);
}

STDMETHODIMP CDocObjectServerDoc::XDocOleObject::GetMoniker(
	DWORD dwAssign, DWORD dwWhichMoniker, LPMONIKER* ppMoniker)
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, DocOleObject)
	ASSERT_VALID(pThis);
	return pThis->m_xOleObject.GetMoniker(dwAssign, dwWhichMoniker,
                                         ppMoniker);
}

STDMETHODIMP CDocObjectServerDoc::XDocOleObject::InitFromData(
	LPDATAOBJECT pDataObject, BOOL bCreation, DWORD dwReserved)
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, DocOleObject)
	ASSERT_VALID(pThis);
	return pThis->m_xOleObject.InitFromData(pDataObject, bCreation,
                                           dwReserved);
}

STDMETHODIMP CDocObjectServerDoc::XDocOleObject::GetClipboardData(
	DWORD dwReserved, LPDATAOBJECT* ppDataObject)
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, DocOleObject)
	ASSERT_VALID(pThis);
	return pThis->m_xOleObject.GetClipboardData(dwReserved, 
                                               ppDataObject);

}

STDMETHODIMP CDocObjectServerDoc::XDocOleObject::DoVerb(
	LONG iVerb, LPMSG lpmsg, LPOLECLIENTSITE pActiveSite, LONG lindex,
	HWND hwndParent, LPCRECT lpPosRect)
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, DocOleObject)
	ASSERT_VALID(pThis);
	return pThis->m_xOleObject.DoVerb(iVerb, lpmsg, 
                                     pActiveSite, lindex,
	                                  hwndParent, lpPosRect);
}

STDMETHODIMP CDocObjectServerDoc::XDocOleObject::EnumVerbs(
	IEnumOLEVERB** ppenumOleVerb)
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, DocOleObject)
	ASSERT_VALID(pThis);
	return pThis->m_xOleObject.EnumVerbs(ppenumOleVerb);
}

STDMETHODIMP CDocObjectServerDoc::XDocOleObject::Update()
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, DocOleObject)
	ASSERT_VALID(pThis);
	return pThis->m_xOleObject.Update();
}

STDMETHODIMP CDocObjectServerDoc::XDocOleObject::IsUpToDate()
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, DocOleObject)
	ASSERT_VALID(pThis);
	return pThis->m_xOleObject.IsUpToDate();
}

STDMETHODIMP CDocObjectServerDoc::XDocOleObject::GetUserClassID(CLSID* lpClassID)
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, DocOleObject)
	ASSERT_VALID(pThis);
	return pThis->m_xOleObject.GetUserClassID(lpClassID);
}

STDMETHODIMP CDocObjectServerDoc::XDocOleObject::GetUserType(
	DWORD dwFormOfType, LPOLESTR* ppszUserType)
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, DocOleObject)
	ASSERT_VALID(pThis);
	return pThis->m_xOleObject.GetUserType(dwFormOfType, ppszUserType);
}

STDMETHODIMP CDocObjectServerDoc::XDocOleObject::SetExtent(
	DWORD dwDrawAspect, LPSIZEL lpsizel)
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, DocOleObject)
	ASSERT_VALID(pThis);

   // DocObjects ignore SetExtent calls, so returne E_FAIL
   if (pThis->IsDocObject())
      return E_FAIL;

   // Otherwise, just do the normal processing
   return pThis->m_xOleObject.SetExtent(dwDrawAspect, lpsizel);
}

STDMETHODIMP CDocObjectServerDoc::XDocOleObject::GetExtent(
	DWORD dwDrawAspect, LPSIZEL lpsizel)
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, DocOleObject)
	ASSERT_VALID(pThis);
	return pThis->m_xOleObject.GetExtent(dwDrawAspect, lpsizel);
}

STDMETHODIMP CDocObjectServerDoc::XDocOleObject::Advise(
	LPADVISESINK pAdvSink, DWORD* pdwConnection)
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, DocOleObject)
	ASSERT_VALID(pThis);
	return pThis->m_xOleObject.Advise(pAdvSink, pdwConnection);
}

STDMETHODIMP CDocObjectServerDoc::XDocOleObject::Unadvise(DWORD dwConnection)
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, DocOleObject)
	ASSERT_VALID(pThis);
	return pThis->m_xOleObject.Unadvise(dwConnection);
}

STDMETHODIMP CDocObjectServerDoc::XDocOleObject::EnumAdvise(
	LPENUMSTATDATA* ppenumStatData)
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, DocOleObject)
	ASSERT_VALID(pThis);
	return pThis->m_xOleObject.EnumAdvise(ppenumStatData);
}

STDMETHODIMP CDocObjectServerDoc::XDocOleObject::GetMiscStatus(
	DWORD dwAspect, DWORD* pdwStatus)
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, DocOleObject)
	ASSERT_VALID(pThis);
	return pThis->m_xOleObject.GetMiscStatus(dwAspect, pdwStatus);
}

STDMETHODIMP CDocObjectServerDoc::XDocOleObject::SetColorScheme(LPLOGPALETTE lpLogpal)
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, DocOleObject)
	ASSERT_VALID(pThis);
	return pThis->m_xOleObject.SetColorScheme(lpLogpal);
}

