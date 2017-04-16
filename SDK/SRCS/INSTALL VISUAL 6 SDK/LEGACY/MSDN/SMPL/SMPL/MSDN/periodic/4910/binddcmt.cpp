// binddcmt.cpp : implementation of the DocObject OLE
//		server document class IOleDocument interface
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

//BINDER
// This file contains the core implementation of the binder document.
// The IOleDocument interface can manage views of the document.
//BINDER_END

#include "stdafx.h"
#include "afxbind.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

STDMETHODIMP_(ULONG) CDocObjectServerDoc::XOleDocument::AddRef()
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, OleDocument)
	return pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) CDocObjectServerDoc::XOleDocument::Release()
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, OleDocument)
	return pThis->ExternalRelease();
}

STDMETHODIMP CDocObjectServerDoc::XOleDocument::QueryInterface(
	REFIID iid, LPVOID* ppvObj)
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, OleDocument)
	return pThis->ExternalQueryInterface(&iid, ppvObj);
}

STDMETHODIMP CDocObjectServerDoc::XOleDocument::CreateView(
   LPOLEINPLACESITE pipsite, LPSTREAM pstm, 
   DWORD dwReserved, LPOLEDOCUMENTVIEW* ppview)
{
   METHOD_PROLOGUE_EX(CDocObjectServerDoc, OleDocument)
   ASSERT_VALID(pThis);

   *ppview = NULL;

   HRESULT hr = E_FAIL;

   if (dwReserved == 0 && pThis->m_pDocSite != NULL)
   {
      // We only support a single view...so if view site is already
      // set, fail.
      if (pThis->m_pViewSite == NULL)
      {
         LPOLEDOCUMENTVIEW pView =
			(LPOLEDOCUMENTVIEW)pThis->GetInterface(&IID_IOleDocumentView);
         ASSERT(pView != NULL);

         // Set the site for the view
         hr = pView->SetInPlaceSite(pipsite);
         if (hr == NOERROR)
         {
            // Return the IOleDocumentView pointer 
            pView->AddRef();
            *ppview = pView;
         }

         // If a saved view state is provided, restore the view state
         if (pstm)
            hr = pView->ApplyViewState(pstm);
      }
      else
         TRACE0("CDocObjectServerDoc::XOleDocument::CreateView view already exists!\n");
   }

   return hr;
}

STDMETHODIMP CDocObjectServerDoc::XOleDocument::GetDocMiscStatus( 
   LPDWORD pdwStatus)
{
   METHOD_PROLOGUE_EX(CDocObjectServerDoc, OleDocument)
   ASSERT_VALID(pThis);
   ASSERT(pdwStatus != NULL);

   // Our implementation of DocObjects can't create multiple views,
   // does not support complex rectangles, supports open editing,
   // and supports read/write to a file. Thus DOCMISC == 0.
   *pdwStatus = 0;

   return NOERROR;
}
        
STDMETHODIMP CDocObjectServerDoc::XOleDocument::EnumViews( 
   LPENUMOLEDOCUMENTVIEWS* ppEnumView, LPOLEDOCUMENTVIEW* ppView)
{
   METHOD_PROLOGUE_EX(CDocObjectServerDoc, OleDocument)
   ASSERT_VALID(pThis);
   ASSERT(ppEnumView != NULL);
   ASSERT(ppView != NULL);

   // We only support a single view
   *ppEnumView = NULL;
   HRESULT hr = QueryInterface(IID_IOleDocumentView, (LPVOID*)ppView);

   return hr;
}
        
