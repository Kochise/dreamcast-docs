// bindview.cpp : implementation of the Binder-aware DocObject OLE
//				server document class IOleDocumentView interface
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1995 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.
//

//BINDER
// The DocObjectServerDoc class implements the binder document interface.
// The code here makes the binder aware of our document and helps the
// binder create and initialize views associated with the document.
// The most important aspect of the binder document, though, is properly
// managing the activation and deactivation of the view associated with
// the document.
//END_BINDER

#include "stdafx.h"
#include <afxpriv.h>	 // for COleCntrFrameWnd
#include "afxbind.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

void CDocObjectServerDoc::OnApplyViewState(CArchive& ar)
{
}

HRESULT CDocObjectServerDoc::OnActivateView()
{
	USES_CONVERSION;
	ASSERT_VALID(this);
	ASSERT(IsDocObject());

	HRESULT hr = E_FAIL;

	// Can't in-place activate without a client site
	if (m_lpClientSite == NULL)
		return NOERROR;

	ASSERT(m_pInPlaceFrame == NULL);

	// build object title/name (the container may use this in its caption)
	CString strFileType, strTitle;
	if (!GetFileTypeString(strFileType))
		return E_FAIL;
	AfxFormatString2(strTitle, AFX_IDS_OBJ_TITLE_INPLACE,
		AfxGetAppName(), strFileType);

	// Find our view site
	LPOLEINPLACESITE lpInPlaceSite = NULL;
	lpInPlaceSite = m_pViewSite;
	if (lpInPlaceSite == NULL)
		return E_FAIL;
	lpInPlaceSite->AddRef();

	// start activation sequence...
 	if ((hr = lpInPlaceSite->OnInPlaceActivate()) != NOERROR)
		goto ReleaseAndFail;

	// we'll need the parent window to create the CDocObjectIPFrameWnd
	HWND hWnd;
	VERIFY(lpInPlaceSite->GetWindow(&hWnd) == NOERROR);
	CWnd* pParentWnd;
	pParentWnd = CWnd::FromHandle(hWnd);

	// create the inplace frame window
	CDocObjectIPFrameWnd* pFrameWnd;
	pFrameWnd = (CDocObjectIPFrameWnd*)CreateInPlaceFrame(pParentWnd);
	if (pFrameWnd == NULL)
	{
		ASSERT(lpInPlaceSite != NULL);
		lpInPlaceSite->OnInPlaceDeactivate();
		goto ReleaseAndFail;
	}

	// DocObjects need some special work done in the in-place
	// frame window.  It should be derived from CDocObjectIPFrameWnd
	ASSERT(pFrameWnd->IsKindOf(RUNTIME_CLASS(CDocObjectIPFrameWnd)));

	ASSERT(pFrameWnd->GetParent() == pParentWnd);
	m_pInPlaceFrame = pFrameWnd;

	// need to get frame & doc window interfaces as well as other info
	RECT rcPosRect, rcClipRect;
	if ((hr = lpInPlaceSite->GetWindowContext(
		&pFrameWnd->m_lpFrame, &pFrameWnd->m_lpDocFrame,
		&rcPosRect, &rcClipRect, &pFrameWnd->m_frameInfo)) != NOERROR)
	{
		goto DestroyFrameAndFail;
	}
	ASSERT(pFrameWnd->m_lpFrame != NULL);

	// TODO: Retrieve pointer to IDocObjectCommandTarget from
	//		 pFrameWnd->m_lpFrame, and save it somewhere

	// send activate notification
	if ((hr = lpInPlaceSite->OnUIActivate()) != NOERROR)
		goto DestroyFrameAndFail;

	// setup the shared menu
	if (!pFrameWnd->BuildSharedMenu())
		goto DeactivateUIAndFail;

	// allow server to install frame controls in container
	VERIFY(pFrameWnd->m_lpFrame->GetWindow(&hWnd) == NOERROR);
	pFrameWnd->m_pMainFrame = new COleCntrFrameWnd(pFrameWnd);
	pFrameWnd->m_pMainFrame->Attach(hWnd);
	if (pFrameWnd->m_lpDocFrame != NULL)
	{
		VERIFY(pFrameWnd->m_lpDocFrame->GetWindow(&hWnd) == NOERROR);
		pFrameWnd->m_pDocFrame = new COleCntrFrameWnd(pFrameWnd);
		pFrameWnd->m_pDocFrame->Attach(hWnd);
	}
	// update zoom factor information before creating control bars
	pFrameWnd->m_rectPos.CopyRect(&rcPosRect);
	pFrameWnd->m_rectClip.CopyRect(&rcClipRect);
	if (!pFrameWnd->OnCreateControlBars(pFrameWnd->m_pMainFrame,
		pFrameWnd->m_pDocFrame))
	{
		goto DeactivateUIAndFail;
	}

	// set the active object
	ASSERT(pFrameWnd->m_lpFrame != NULL);
	LPOLEINPLACEACTIVEOBJECT lpActiveObject;
	lpActiveObject = (LPOLEINPLACEACTIVEOBJECT)
		GetInterface(&IID_IOleInPlaceActiveObject);
	pFrameWnd->m_lpFrame->SetActiveObject(lpActiveObject, T2OLE(strTitle));
	if (pFrameWnd->m_lpDocFrame != NULL)
		pFrameWnd->m_lpDocFrame->SetActiveObject(lpActiveObject, T2OLE(strTitle));

	// add frame & document level frame controls
	ASSERT(m_pInPlaceFrame == pFrameWnd);
	ASSERT(pFrameWnd->m_lpFrame != NULL);
	OnShowControlBars(pFrameWnd->m_pMainFrame, TRUE);
	if (pFrameWnd->m_lpDocFrame != NULL)
		OnShowControlBars(pFrameWnd->m_pDocFrame, TRUE);

	// show any hidden modeless dialogs as well...
	pFrameWnd->ShowOwnedWindows(TRUE);

	// attempt toolbar negotiation
	OnResizeBorder(NULL, pFrameWnd->m_lpFrame, TRUE);
	if (pFrameWnd->m_lpDocFrame != NULL)
		OnResizeBorder(NULL, pFrameWnd->m_lpDocFrame, FALSE);

	// install the menu (also installs a hook which forwards messages from
	//  the menu to the inplace frame window)
	pFrameWnd->m_lpFrame->SetMenu(pFrameWnd->m_hSharedMenu,
		pFrameWnd->m_hOleMenu, pFrameWnd->m_hWnd);

	// finally -- show the inplace frame window and set focus
	pFrameWnd->ShowWindow(SW_SHOW);
	pFrameWnd->SetFocus();
	pFrameWnd->UpdateWindow();

	// allow the main window to be set
	OnFrameWindowActivate(TRUE);
	pFrameWnd->m_bUIActive = TRUE;

	// cleanup and return
	lpInPlaceSite->Release();
	return hr;

DeactivateUIAndFail:
	ASSERT(lpInPlaceSite != NULL);
	lpInPlaceSite->OnUIDeactivate(FALSE);

DestroyFrameAndFail:
	if (m_pInPlaceFrame != NULL)
	{
		ASSERT(pFrameWnd != NULL);
		DestroyInPlaceFrame(pFrameWnd);
		m_pInPlaceFrame = NULL;

		// also need to send OnInPlaceDeactivate notification
		ASSERT(lpInPlaceSite != NULL);
		lpInPlaceSite->OnInPlaceDeactivate();
	}
ReleaseAndFail:
	ASSERT(lpInPlaceSite != NULL);
	lpInPlaceSite->Release();

	return hr;
}

STDMETHODIMP_(ULONG) CDocObjectServerDoc::XOleDocumentView::AddRef()
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, OleDocumentView)
	return pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) CDocObjectServerDoc::XOleDocumentView::Release()
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, OleDocumentView)
	return pThis->ExternalRelease();
}

STDMETHODIMP CDocObjectServerDoc::XOleDocumentView::QueryInterface(REFIID iid, LPVOID* ppvObj)
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, OleDocumentView)
	return pThis->ExternalQueryInterface(&iid, ppvObj);
}

STDMETHODIMP CDocObjectServerDoc::XOleDocumentView::SetInPlaceSite(
	LPOLEINPLACESITE pIPSite)
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, OleDocumentView)
	ASSERT_VALID(pThis);

	// if currently inplace active, then do normal inplace deactivation
	if (pThis->IsInPlaceActive())
		pThis->m_xOleInPlaceObject.InPlaceDeactivate();

	// release the view site pointer
	if (pThis->m_pViewSite)
		pThis->m_pViewSite->Release();

	// remember the new view site pointer and addref it, if it is non-NULL
	pThis->m_pViewSite = pIPSite;
	if (pThis->m_pViewSite != NULL)
		pThis->m_pViewSite->AddRef();

	return NOERROR;
}

STDMETHODIMP CDocObjectServerDoc::XOleDocumentView::GetInPlaceSite(LPOLEINPLACESITE* ppIPSite)
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, OleDocumentView)
	ASSERT_VALID(pThis);
	ASSERT(ppIPSite != NULL);

	if (pThis->m_pViewSite)
		pThis->m_pViewSite->AddRef();
	*ppIPSite = pThis->m_pViewSite;

	return NOERROR;
}

STDMETHODIMP CDocObjectServerDoc::XOleDocumentView::GetDocument(LPUNKNOWN* ppUnk)
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, OleDocumentView)
	ASSERT_VALID(pThis);
	ASSERT(ppUnk != NULL);

	HRESULT hr = pThis->m_xOleDocument.QueryInterface(IID_IUnknown, 
		(LPVOID*)ppUnk);
	ASSERT(*ppUnk != NULL);

	return hr;
}

STDMETHODIMP CDocObjectServerDoc::XOleDocumentView::SetRect(LPRECT lprcView)
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, OleDocumentView)
	ASSERT_VALID(pThis);
	ASSERT(lprcView != NULL);

	HRESULT hr = E_UNEXPECTED;
	TRY
	{
		pThis->OnSetItemRects(lprcView, lprcView);
		hr = NOERROR;
	}
	END_TRY

	return hr;
}

STDMETHODIMP CDocObjectServerDoc::XOleDocumentView::GetRect(LPRECT lprcView)
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, OleDocumentView)
	ASSERT_VALID(pThis);
	ASSERT(lprcView != NULL);

	pThis->GetItemPosition(lprcView);
	return NOERROR;
}

STDMETHODIMP CDocObjectServerDoc::XOleDocumentView::SetRectComplex(
	LPRECT lprcView, LPRECT lprcHScroll, 
	LPRECT lprcVScroll, LPRECT lprcSizeBox)
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, OleDocumentView)
	ASSERT_VALID(pThis);

	// We don't support complex rectangles, so return error
	return E_NOTIMPL;
}

STDMETHODIMP CDocObjectServerDoc::XOleDocumentView::Show(BOOL bShow)
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, OleDocumentView)
	ASSERT_VALID(pThis);

	return E_NOTIMPL;
}

STDMETHODIMP CDocObjectServerDoc::XOleDocumentView::UIActivate(BOOL bUIActivate)
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, OleDocumentView)
	ASSERT_VALID(pThis);

	HRESULT hr = NOERROR;

	if (bUIActivate)
	{
		// UI Activate the view then take focus and bring the view forward
		hr = pThis->OnActivateView();
	}
	else
	{
		// Call IOleInPlaceObject::UIDeactivate on this view
		hr = pThis->m_xOleInPlaceObject.UIDeactivate();
	}
	return hr;
}

STDMETHODIMP CDocObjectServerDoc::XOleDocumentView::Open()
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, OleDocumentView)
	ASSERT_VALID(pThis);

	return E_NOTIMPL;
}

STDMETHODIMP CDocObjectServerDoc::XOleDocumentView::CloseView(DWORD dwReserved)
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, OleDocumentView)
	ASSERT_VALID(pThis);

	// Call IOleDocumentView::Show(FALSE) to hide the view
	Show(FALSE);

	// Call IOleDocumentView::SetInPlaceSite(NULL) to deactivate the object
	HRESULT hr = SetInPlaceSite(NULL);

	return hr;
}

STDMETHODIMP CDocObjectServerDoc::XOleDocumentView::SaveViewState(LPSTREAM pstm)
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, OleDocumentView)
	ASSERT_VALID(pThis);
	return E_NOTIMPL;
}

STDMETHODIMP CDocObjectServerDoc::XOleDocumentView::ApplyViewState(LPSTREAM pstm)
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, OleDocumentView)
	ASSERT_VALID(pThis);

	HRESULT hr = NOERROR;

	// Attach the stream to an MFC file object
	COleStreamFile file;
	file.Attach(pstm);
	CFileException fe;

	// load it with CArchive
	CArchive loadArchive(&file, CArchive::load | CArchive::bNoFlushOnDelete);
	TRY
	{
		pThis->OnApplyViewState(loadArchive);
		loadArchive.Close();
		file.Detach();
	}
	CATCH(COleException, pOE)
	{
		hr = pOE->m_sc;
	}
	AND_CATCH_ALL(e)
	{
		hr = E_UNEXPECTED;
	}
	END_CATCH_ALL

	return hr;
}

STDMETHODIMP CDocObjectServerDoc::XOleDocumentView::Clone(
	LPOLEINPLACESITE pipsiteNew, LPOLEDOCUMENTVIEW* ppviewNew)
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, OleDocumentView)
	ASSERT_VALID(pThis);

	// In order to support this, we would need to support multiple views,
	// which we do not.  So we will return an error.
	return E_NOTIMPL;
}

