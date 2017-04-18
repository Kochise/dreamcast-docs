// binditem.cpp : implementation of the DocObject OLE
//	server item class
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
//  The DocObjectServerItem class implements interfaces that help
// the application  control its activation state.
//BINDER_END

#include "stdafx.h"
#include "afxbind.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDocObjectServerItem implementation

IMPLEMENT_DYNAMIC(CDocObjectServerItem, COleServerItem)

CDocObjectServerItem::CDocObjectServerItem(COleServerDoc* pServerDoc, BOOL bAutoDelete)
	: COleServerItem(pServerDoc, bAutoDelete)
{
}

CDocObjectServerItem::~CDocObjectServerItem()
{
}

void CDocObjectServerItem::OnHide()
{
   CDocObjectServerDoc* pDoc = GetDocument();
   ASSERT_VALID(pDoc);

   if (pDoc->IsDocObject())
      AfxThrowOleException(OLEOBJ_E_INVALIDVERB);
   else
      COleServerItem::OnHide();
}

void CDocObjectServerItem::OnOpen()
{
   CDocObjectServerDoc* pDoc = GetDocument();
   ASSERT_VALID(pDoc);

   if (pDoc->IsDocObject())
      pDoc->ActivateDocObject();
   else
      COleServerItem::OnOpen();
}

void CDocObjectServerItem::OnShow()
{
   CDocObjectServerDoc* pDoc = GetDocument();
   ASSERT_VALID(pDoc);

   if (pDoc->IsDocObject())
      pDoc->ActivateDocObject();
   else
      COleServerItem::OnShow();
}

#ifdef _DEBUG
void CDocObjectServerItem::AssertValid() const
{
	COleServerItem::AssertValid();
}

void CDocObjectServerItem::Dump(CDumpContext& dc) const
{
	COleServerItem::Dump(dc);
}
#endif

