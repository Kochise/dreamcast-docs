// bindtarg.cpp : implementation of the DocObject OLE
// 		server document class IOleCommandTarget interface
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
// The COleCmdTarget class implements a command-handler for the binder.
// The interface may be queried by the binder to see what commands and
// menu items are available.  This file also defines a COleCmdUI class
// which lets the binder understand what menu items and tool bars must
// be disabled or marked selected based on the state of hte document.
//BINDER_END

#include "stdafx.h"
#include "afxbind.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COleCmdUI   (private class)

class COleCmdUI : public CCmdUI 
{
public:
   COleCmdUI(OLECMD* rgCmds, ULONG cCmds);
   virtual void Enable(BOOL bOn);
   virtual void SetCheck(int nCheck);
   virtual void SetText(LPCTSTR lpszText);

protected:
   OLECMD* m_rgCmds;
};

COleCmdUI::COleCmdUI(OLECMD* rgCmds, ULONG cCmds)
{
   m_rgCmds    = rgCmds;
   m_nIndexMax = cCmds;
}

void COleCmdUI::Enable(BOOL bOn)
{
   if (m_rgCmds != NULL)
   {
      ASSERT(m_nIndex < m_nIndexMax);
      
      if (bOn)
         m_rgCmds[m_nIndex].cmdf |= OLECMDF_ENABLED;
      else
         m_rgCmds[m_nIndex].cmdf &= ~OLECMDF_ENABLED;
      m_bEnableChanged = TRUE;
   }
}

void COleCmdUI::SetCheck(int nCheck)
{
   if (m_rgCmds != NULL)
   {
      ASSERT(m_nIndex < m_nIndexMax);
      
      m_rgCmds[m_nIndex].cmdf &= ~(OLECMDF_LATCHED|OLECMDF_NINCHED);
      if (nCheck == 1)
         m_rgCmds[m_nIndex].cmdf |= OLECMDF_LATCHED;
      else if (nCheck == 2)
         m_rgCmds[m_nIndex].cmdf |= OLECMDF_NINCHED;
   }
}

void COleCmdUI::SetText(LPCSTR lpszText)
{
   // ignore it...
}

STDMETHODIMP_(ULONG) CDocObjectServerDoc::XOleCommandTarget::AddRef()
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, OleCommandTarget)
	return pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) CDocObjectServerDoc::XOleCommandTarget::Release()
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, OleCommandTarget)
	return pThis->ExternalRelease();
}

STDMETHODIMP CDocObjectServerDoc::XOleCommandTarget::QueryInterface(
	REFIID iid, LPVOID* ppvObj)
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, OleCommandTarget)
	return pThis->ExternalQueryInterface(&iid, ppvObj);
}

STDMETHODIMP CDocObjectServerDoc::XOleCommandTarget::QueryStatus(
   const GUID* pguidCmdGroup, ULONG cCmds, OLECMD rgCmds[], 
   OLECMDTEXT* pcmdtext)
{
   METHOD_PROLOGUE_EX(CDocObjectServerDoc, OleCommandTarget)
   ASSERT_VALID(pThis);

   HRESULT hr = NOERROR;

   // this implementation only supports the standard Office95 commands

   if (pguidCmdGroup != NULL)
      hr = OLECMDERR_E_UNKNOWNGROUP;
   else if (rgCmds == NULL)
      hr = E_INVALIDARG;

   // TODO: determine the state of requested commands 
   hr = E_FAIL;
   
   // TODO: get command name or status bar text for first supported command
   if (pcmdtext)
   {   
      hr = E_FAIL;
   }

   return hr;
}

STDMETHODIMP CDocObjectServerDoc::XOleCommandTarget::Exec(
   const GUID* pguidCmdGroup, DWORD nCmdID, DWORD nCmdExecOpt, 
   VARIANTARG* pvarargIn, VARIANTARG* pvarargOut)
{
   METHOD_PROLOGUE_EX(CDocObjectServerDoc, OleCommandTarget)
   ASSERT_VALID(pThis);

   HRESULT hr = NOERROR;

   // this implementation only supports standard Office95 commands
   if (pguidCmdGroup != NULL)
	   hr = OLECMDERR_E_UNKNOWNGROUP;
   else
   {
   // TODO: figure out what is supposed to be done based on nCmdExecOpt
   //       and do it
	   hr = E_FAIL;
   }

   return hr;
}

