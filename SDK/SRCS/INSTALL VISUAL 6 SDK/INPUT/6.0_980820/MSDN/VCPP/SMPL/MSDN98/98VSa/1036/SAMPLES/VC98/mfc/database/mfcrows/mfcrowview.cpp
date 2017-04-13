// MFCRowView.cpp : implementation of the CMFCRowView class
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include "MFCRow.h"

#include "MFCRowSet.h"
#include "MFCRowDoc.h"
#include "MFCRowView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMFCRowView

IMPLEMENT_DYNCREATE(CMFCRowView, COleDBRecordView)

BEGIN_MESSAGE_MAP(CMFCRowView, COleDBRecordView)
	//{{AFX_MSG_MAP(CMFCRowView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, COleDBRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, COleDBRecordView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, COleDBRecordView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMFCRowView construction/destruction

CMFCRowView::CMFCRowView()
	: COleDBRecordView(CMFCRowView::IDD)
{
	//{{AFX_DATA_INIT(CMFCRowView)
	m_pSet = NULL;
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CMFCRowView::~CMFCRowView()
{
}

BOOL CMFCRowView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return COleDBRecordView::PreCreateWindow(cs);
}

void CMFCRowView::OnInitialUpdate()
{
	m_pSet = &GetDocument()->m_mFCRowSet;
	{
		CWaitCursor wait;
		m_pSet->Open();
	}
	COleDBRecordView::OnInitialUpdate();
}

void CMFCRowView::DoDataExchange(CDataExchange* pDX)
{
	COleDBRecordView::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CMFCRowView)
	DDX_Text(pDX, IDC_ID, m_pSet->m_nProductID);
	DDV_MaxChars(pDX, m_pSet->m_szName, 40);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_NAME, m_pSet->m_szName, 40);
}

/////////////////////////////////////////////////////////////////////////////
// CMFCRowView printing

BOOL CMFCRowView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCRowView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFCRowView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMFCRowView diagnostics

#ifdef _DEBUG
void CMFCRowView::AssertValid() const
{
	COleDBRecordView::AssertValid();
}

void CMFCRowView::Dump(CDumpContext& dc) const
{
	COleDBRecordView::Dump(dc);
}

CMFCRowDoc* CMFCRowView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCRowDoc)));
	return (CMFCRowDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMFCRowView database support
CRowset* CMFCRowView::OnGetRowset()
{
	return m_pSet;
}


/////////////////////////////////////////////////////////////////////////////
// CMFCRowView message handlers
