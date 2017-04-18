// containerMFCView.cpp : implementation of the CContainerMFCView class
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
#include "containerMFC.h"

#include "containerMFCDoc.h"
#include "CntrItem.h"
#include "containerMFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CContainerMFCView

IMPLEMENT_DYNCREATE(CContainerMFCView, CView)

BEGIN_MESSAGE_MAP(CContainerMFCView, CView)
	//{{AFX_MSG_MAP(CContainerMFCView)
	ON_WM_DESTROY()
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_COMMAND(ID_OLE_INSERT_NEW, OnInsertObject)
	ON_COMMAND(ID_CANCEL_EDIT_CNTR, OnCancelEditCntr)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CContainerMFCView construction/destruction

CContainerMFCView::CContainerMFCView()
{
	m_pSelection = NULL;
	// TODO: add construction code here
}

CContainerMFCView::~CContainerMFCView()
{
}

BOOL CContainerMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CContainerMFCView drawing

void CContainerMFCView::OnDraw(CDC* pDC)
{
	CContainerMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
	// TODO: also draw all OLE items in the document

	// Draw the selection at an arbitrary position.  This code should be
	//  removed once your real drawing code is implemented.  This position
	//  corresponds exactly to the rectangle returned by CContainerMFCCntrItem,
	//  to give the effect of in-place editing.

	// TODO: remove this code when final draw code is complete.

	if (m_pSelection == NULL)
	{
		POSITION pos = pDoc->GetStartPosition();
		m_pSelection = (CContainerMFCCntrItem*)pDoc->GetNextClientItem(pos);
	}
	if (m_pSelection != NULL)
	{
		CRect   r;
		GetClientRect(&r);
		m_pSelection->Draw(pDC, r);
	}
}

void CContainerMFCView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// Add "About..." menu item to system menu.
	// also add "Stay On Top" menu item to system menu.

	// ID_APP_ABOUT must be in the system command range.
	ASSERT((ID_APP_ABOUT & 0xFFF0) == ID_APP_ABOUT);
	ASSERT(ID_APP_ABOUT < 0xF000);

	CMenu* pSysMenu = AfxGetMainWnd()->GetSystemMenu(FALSE);
	ASSERT(pSysMenu);
	if (pSysMenu)
	{
		CString str;

		pSysMenu->AppendMenu(MF_SEPARATOR);
		str.LoadString(IDS_STAY_ON_TOP);
		if (str.IsEmpty())
			str = _T("&Stay On Top");
		pSysMenu->AppendMenu(MF_STRING, ID_STAY_ON_TOP, str);

		str.LoadString(IDS_ABOUT_APP);
		if (str.IsEmpty())
			str = _T("&About Stock Ticker..");
		pSysMenu->AppendMenu(MF_STRING, ID_APP_ABOUT, str);
	}
	// request document to create control.
	//
	CRect   r;
	GetClientRect(&r);
	GetDocument()->CreateControl(this, r);
}

void CContainerMFCView::OnDestroy()
{
	// Deactivate the item on destruction; this is important
	// when a splitter view is being used.
	GetDocument()->Save();      // save state.
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL && pActiveItem->GetActiveView() == this)
	{
	  pActiveItem->Deactivate();
	  ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
	}
	CView::OnDestroy();
}


/////////////////////////////////////////////////////////////////////////////
// OLE Client support and commands

BOOL CContainerMFCView::IsSelected(const CObject* pDocItem) const
{
	// The implementation below is adequate if your selection consists of
	//  only CContainerMFCCntrItem objects.  To handle different selection
	//  mechanisms, the implementation here should be replaced.

	// TODO: implement this function that tests for a selected OLE client item

	return pDocItem == m_pSelection;
}

void CContainerMFCView::OnInsertObject()
{
	// Invoke the standard Insert Object dialog box to obtain information
	//  for new CContainerMFCCntrItem object.
	COleInsertDialog dlg;
	if (dlg.DoModal() != IDOK)
		return;

	BeginWaitCursor();

	CContainerMFCCntrItem* pItem = NULL;
	TRY
	{
		// Create new item connected to this document.
		CContainerMFCDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pItem = new CContainerMFCCntrItem(pDoc);
		ASSERT_VALID(pItem);

		// Initialize the item from the dialog data.
		if (!dlg.CreateItem(pItem))
			AfxThrowMemoryException();  // any exception will do
		ASSERT_VALID(pItem);

		// If item created from class list (not from file) then launch
		//  the server to edit the item.
		if (dlg.GetSelectionType() == COleInsertDialog::createNewItem)
			pItem->DoVerb(OLEIVERB_SHOW, this);

		ASSERT_VALID(pItem);

		// As an arbitrary user interface design, this sets the selection
		//  to the last item inserted.

		// TODO: reimplement selection as appropriate for your application

		m_pSelection = pItem;   // set selection to last inserted item
		pDoc->UpdateAllViews(NULL);
	}
	CATCH(CException, e)
	{
		if (pItem != NULL)
		{
			ASSERT_VALID(pItem);
			pItem->Delete();
		}
		AfxMessageBox(IDP_FAILED_TO_CREATE);
	}
	END_CATCH

	EndWaitCursor();
}

// The following command handler provides the standard keyboard
//  user interface to cancel an in-place editing session.  Here,
//  the container (not the server) causes the deactivation.
void CContainerMFCView::OnCancelEditCntr()
{
	// Close any in-place active item on this view.
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
	{
		pActiveItem->Close();
	}
	ASSERT(GetDocument()->GetInPlaceActiveItem(this) == NULL);
}

// Special handling of OnSetFocus and OnSize are required for a container
//  when an object is being edited in-place.
void CContainerMFCView::OnSetFocus(CWnd* pOldWnd)
{
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL &&
		pActiveItem->GetItemState() == COleClientItem::activeUIState)
	{
		// need to set focus to this item if it is in the same view
		CWnd* pWnd = pActiveItem->GetInPlaceWindow();
		if (pWnd != NULL)
		{
			pWnd->SetFocus();   // don't call the base class
			return;
		}
	}

	CView::OnSetFocus(pOldWnd);
}

// Resize control to fit client area.
//
void CContainerMFCView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	CStockTickerCtrl*   pCtrl = GetDocument()->GetControl();
	if (pCtrl->GetSafeHwnd())
	{
		CRect   r(0, 0, cx, cy);
		pCtrl->MoveWindow(r);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CContainerMFCView diagnostics

#ifdef _DEBUG
void CContainerMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CContainerMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CContainerMFCDoc* CContainerMFCView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CContainerMFCDoc)));
	return (CContainerMFCDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CContainerMFCView message handlers

int CContainerMFCView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

void CContainerMFCView::Serialize(CArchive& ar)
{
	CView::Serialize(ar);
	if (ar.IsStoring())
	{   // storing code
	}
	else
	{   // loading code
	}
}
