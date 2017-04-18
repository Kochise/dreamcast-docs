// TextView.cpp : implementation file
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1995 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and Microsoft
// QuickHelp and/or WinHelp documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include "$$root$$.h"
#include "textview.h"
#include "svrdoc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextView

IMPLEMENT_DYNCREATE(CTextView, CEditView)

CTextView::CTextView()
{
}

CTextView::~CTextView()
{
}


BEGIN_MESSAGE_MAP(CTextView, CEditView)
	//{{AFX_MSG_MAP(CTextView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTextView drawing

void CTextView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CTextView diagnostics

#ifdef _DEBUG
void CTextView::AssertValid() const
{
	CEditView::AssertValid();
}

void CTextView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTextView message handlers

void CTextView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	RedrawText() ;
}

void CTextView::RedrawText()
{
	CString TextBuf ;
	// Get the text from the hierView
	CServerDoc* pServerDoc = (CServerDoc * ) GetDocument();
	pServerDoc->GetTreeText(&TextBuf,NULL) ;
	GetEditCtrl().SetTabStops(10) ;
	GetEditCtrl().SetWindowText(TextBuf) ;
	GetEditCtrl().SetReadOnly(TRUE) ;
}

void CTextView::OnInitialUpdate()
{
	// TODO: Add your specialized code here and/or call the base class

	CEditView::OnInitialUpdate();
}
