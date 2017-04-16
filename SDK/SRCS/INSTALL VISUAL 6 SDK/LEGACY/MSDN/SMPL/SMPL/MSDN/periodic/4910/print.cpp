// print.cpp : implementation of the IPrint interface
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

#include "stdafx.h"
#include "afxbind.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

STDMETHODIMP_(ULONG) CDocObjectServerDoc::XPrint::AddRef()
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, Print)
	return pThis->ExternalAddRef();
}

STDMETHODIMP_(ULONG) CDocObjectServerDoc::XPrint::Release()
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, Print)
	return pThis->ExternalRelease();
}

STDMETHODIMP CDocObjectServerDoc::XPrint::QueryInterface(
	REFIID iid, LPVOID* ppvObj)
{
	METHOD_PROLOGUE_EX(CDocObjectServerDoc, Print)
   return pThis->ExternalQueryInterface(&iid, ppvObj);
}

STDMETHODIMP CDocObjectServerDoc::XPrint::SetInitialPageNum(
   LONG nFirstPage)
{
   METHOD_PROLOGUE_EX(CDocObjectServerDoc, Print)
   ASSERT_VALID(pThis);

   return E_NOTIMPL;
}

STDMETHODIMP CDocObjectServerDoc::XPrint::GetPageInfo(
   LPLONG pnFirstPage, LPLONG pcPages)
{
   METHOD_PROLOGUE_EX(CDocObjectServerDoc, Print)
   ASSERT_VALID(pThis);

   return E_NOTIMPL;
}

STDMETHODIMP CDocObjectServerDoc::XPrint::Print(
   DWORD grfFlags, DVTARGETDEVICE** pptd,
   PAGESET** pppageset, LPSTGMEDIUM pstgmOptions,
   LPCONTINUECALLBACK pcallback, LONG nFirstPage,
   LPLONG pcPagesPrinted, LPLONG pnLastPage)
{
   METHOD_PROLOGUE_EX(CDocObjectServerDoc, Print)
   ASSERT_VALID(pThis);

   return E_NOTIMPL;
}
