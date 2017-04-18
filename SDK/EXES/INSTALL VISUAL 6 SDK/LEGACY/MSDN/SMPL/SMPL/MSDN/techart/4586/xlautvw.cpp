/*****************************************************************************
  File: xlautvw.cpp

  Purpose: Implementation of the CXLAutoView class

  Functions: void CXlAutoView::OnDraw(CDC* pDC)
             void CXlAutoView::OnInsertObject()
			 void CXlAutoView::OnLButtonDown(UINT nFlags, CPoint point) 
			 void CXlAutoView::OnAddstuffAdddata() 
			 void CXlAutoView::OnAddstuffAddchart() 

  Development Team: Steve Roeder

  Written by Microsoft Product Support Services, Languages Developer Support
  Copyright (c) 1995 Microsoft Corporation. All rights reserved.
\****************************************************************************/

// XlAutvw.cpp : implementation of the CXlAutoView class
//

#include "stdafx.h"
#include "XlAuto.h"

#include "XlAutdoc.h"
#include "cntritem.h"
#include "XlAutvw.h"

#include "chartdlg.h"
#include "xlchtobs.h"
#include "xlchtobj.h"
#include "xlchart.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CXlAutoView

IMPLEMENT_DYNCREATE(CXlAutoView, CView)

BEGIN_MESSAGE_MAP(CXlAutoView, CView)
	//{{AFX_MSG_MAP(CXlAutoView)
	ON_WM_SETFOCUS()
	ON_WM_SIZE()
	ON_COMMAND(ID_OLE_INSERT_NEW, OnInsertObject)
	ON_COMMAND(ID_CANCEL_EDIT_CNTR, OnCancelEditCntr)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_ADDSTUFF_ADDDATA, OnAddstuffAdddata)
	ON_COMMAND(ID_ADDSTUFF_ADDCHART, OnAddstuffAddchart)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CXlAutoView construction/destruction

CXlAutoView::CXlAutoView()
{
	m_pSelection = NULL;
	// TODO: add construction code here

}

CXlAutoView::~CXlAutoView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CXlAutoView drawing

/************************************************************************
  Function: CXlAutoView::OnDraw

  Purpose: Render an image of the document and OLE client 

  Parameters: pDC - pointer to the view's device context

  Returns: void

  Comments: Mostly AppWizard generated code with modifications made to
            draw the size of the OLE client to m_rect.

  History:

  Date     Comment                                           Initials
  ======== ================================================= ========
  04/13/95 Created                                             SJR
\***********************************************************************/
void CXlAutoView::OnDraw(CDC* pDC)
{
	CXlAutoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
	// TODO: also draw all OLE items in the document

	// Draw the selection at an arbitrary position.  This code should be
	//  removed once your real drawing code is implemented.  This position
	//  corresponds exactly to the rectangle returned by CXlAutoCntrItem,
	//  to give the effect of in-place editing.

	// TODO: remove this code when final draw code is complete.

	if (m_pSelection == NULL)
	{
		POSITION pos = pDoc->GetStartPosition();
		m_pSelection = (CXlAutoCntrItem*)pDoc->GetNextClientItem(pos);
	}
	if (m_pSelection != NULL)
		m_pSelection->Draw(pDC, m_pSelection->m_rect);
}

void CXlAutoView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: remove this code when final selection model code is written
	m_pSelection = NULL;    // initialize selection

}

/////////////////////////////////////////////////////////////////////////////
// CXlAutoView printing

BOOL CXlAutoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CXlAutoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CXlAutoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// OLE Client support and commands

BOOL CXlAutoView::IsSelected(const CObject* pDocItem) const
{
	// The implementation below is adequate if your selection consists of
	//  only CXlAutoCntrItem objects.  To handle different selection
	//  mechanisms, the implementation here should be replaced.

	// TODO: implement this function that tests for a selected OLE client item

	return pDocItem == m_pSelection;
}

/************************************************************************
  Function:	CXlAutoView::OnInsertObject

  Purpose: Create a new Excel client item connect to the document

  Parameters: none

  Returns: void

  Comments:

  History:

  Date     Comment                                           Initials
  ======== ================================================= ========
  04/13/95 Created                                             SJR
\***********************************************************************/
void CXlAutoView::OnInsertObject()
{
	BeginWaitCursor();

	CXlAutoCntrItem* pItem = NULL;
	TRY
	{
		// Create new item connected to this document.
		CXlAutoDoc* pDoc = GetDocument();
		ASSERT_VALID(pDoc);
		pItem = new CXlAutoCntrItem(pDoc);
		ASSERT_VALID(pItem);

		// Get Class ID for Excel sheet
		// This is used in creation        
		CLSID clsid;
		if (FAILED(::CLSIDFromProgID("Excel.Sheet", &clsid)))
			AfxThrowMemoryException();

		//Create the Excel embedded item
		if(!pItem->CreateNewItem(clsid))
			AfxThrowMemoryException();  // any exception will do
		ASSERT_VALID(pItem);

		// launch the server to edit the item.
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
void CXlAutoView::OnCancelEditCntr()
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
void CXlAutoView::OnSetFocus(CWnd* pOldWnd)
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

void CXlAutoView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	COleClientItem* pActiveItem = GetDocument()->GetInPlaceActiveItem(this);
	if (pActiveItem != NULL)
		pActiveItem->SetItemRects();
}

/////////////////////////////////////////////////////////////////////////////
// CXlAutoView diagnostics

#ifdef _DEBUG
void CXlAutoView::AssertValid() const
{
	CView::AssertValid();
}

void CXlAutoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CXlAutoDoc* CXlAutoView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CXlAutoDoc)));
	return (CXlAutoDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CXlAutoView message handlers

/************************************************************************
  Function: CXlAutoView::OnLButtonDown

  Purpose: Set focus to or away from the OLE client area

  Parameters: nFlags -  Indicates whether various virtual keys are down.
              point - Specifies the x- and y-coordinate of the cursor.
		 
  Returns: void

  Comments:

  History:

  Date     Comment                                           Initials
  ======== ================================================= ========
  04/13/95 Created                                             SJR
\***********************************************************************/
void CXlAutoView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CXlAutoDoc* pDoc = GetDocument();
	CXlAutoCntrItem* pItemHit = NULL;
	POSITION pos = pDoc->GetStartPosition();
	while (pos != NULL)
	{
		CXlAutoCntrItem* pItem = (CXlAutoCntrItem*)pDoc->GetNextItem(pos);
		if (pItem->m_rect.PtInRect(point))
			pItemHit = pItem;
	}	

	// close in-place active item
	if (pItemHit == NULL || m_pSelection != pItemHit)
	{
		COleClientItem* pActiveItem
			= GetDocument()->GetInPlaceActiveItem(this);
		if (pActiveItem != NULL && pActiveItem != pItemHit)
			pActiveItem->Close();
	}
	Invalidate();
	m_pSelection = pItemHit;

	CView::OnLButtonDown(nFlags, point);
}

/************************************************************************
  Function:	CXlAutoView::OnAddstuffAdddata

  Purpose: Handler for the corresponding menu item for the OLE client.

  Parameters: none

  Returns: void

  Comments:	Adds some data to the embedded Excel worksheet. The column
            and row headings are taken from static strings, and the 
			data for the cells are random.

  History:

  Date     Comment                                           Initials
  ======== ================================================= ========
  04/13/95 Created                                             SJR
\***********************************************************************/
void CXlAutoView::OnAddstuffAdddata() 
{
int i, j;
char *strMonths[5] = {"Jan", "Feb", "Mar", "Apr", "May"};
char *strHeadings[4] = {"Sales", "COGS", "Wages", "Misc"};
long rndData[5][4];
Range range1, range2, range3;

	Worksheet sheet;
	sheet.AttachDispatch(m_pSelection->GetIDispatch());

	m_pSelection->GetRange(&sheet, &range1, "A3", "A7");
	m_pSelection->GetRange(&sheet, &range2, "B2", "E2");
	m_pSelection->GetRange(&sheet, &range3, "B3", "E7");

	for (i = 0 ; i < 5 ; i++)
		for (j = 0 ; j < 4 ; j++)
			rndData[i][j] = rand(); //i * 4 + j;
	
	m_pSelection->SetRowHeadings(&range1, strMonths, 5);
	m_pSelection->SetColHeadings(&range2, strHeadings, 4);
	m_pSelection->SetData(&range3, (long*)rndData, 5, 4);
	m_pSelection->SetYTDTotals(&sheet);
}

/************************************************************************
  Function:	CXlAutoView::OnAddstuffAddChart

  Purpose: Create a chart on the embedded Excel worksheet using the 
           ChartWizard object from Excel. 

  Parameters: none

  Returns: void

  Comments:

  History:

  Date     Comment                                           Initials
  ======== ================================================= ========
  04/13/95 Created                                             SJR
\***********************************************************************/
void CXlAutoView::OnAddstuffAddchart() 
{
VARIANT vLeft, vTop, vWidth, vHeight;
VARIANT vSource, vGallery, vFormat, vPlotBy, vCategoryLabels, vSeriesLabels, 
		vHasLegend, vTitle, vCategoryTitle, vValueTitle, vExtraTitle;

	CChartDlg chartDlg;
	chartDlg.DoModal();

	Worksheet sheet;
	sheet.AttachDispatch(m_pSelection->GetIDispatch());

	Range range;
	m_pSelection->GetRange(&sheet, &range, "A2", "E7");
	
	VARIANT vRet;
	VariantInit(&vRet);
	ChartObjects chartobjects;
	vRet = sheet.ChartObjects();
	if (V_VT(&vRet) == VT_DISPATCH)	chartobjects.AttachDispatch(vRet.pdispVal);

	VariantInit(&vLeft);
	VariantInit(&vTop);
	VariantInit(&vWidth);
	VariantInit(&vHeight);
	VariantInit(&vRet);
	V_VT(&vLeft) = VT_I2;
	V_VT(&vTop) = VT_I2;
	V_VT(&vWidth) = VT_I2;
	V_VT(&vHeight) = VT_I2;
	V_VT(&vRet) = VT_DISPATCH;
	V_I2(&vLeft) = 10;
	V_I2(&vTop) = 140;
	V_I2(&vWidth) = 280;
	V_I2(&vHeight) = 100;
	vRet = chartobjects.Add(vLeft, vTop, vWidth, vHeight);
	ChartObject chartobject;
	chartobject.AttachDispatch(vRet.pdispVal); 

	VariantInit(&vRet);
	Chart chart;
	vRet = chartobject.GetChart();
	chart.AttachDispatch(vRet.pdispVal);

	VariantInit(&vSource);
	VariantInit(&vGallery);
	VariantInit(&vFormat);
	VariantInit(&vPlotBy);
	VariantInit(&vCategoryLabels);
	VariantInit(&vSeriesLabels);
	VariantInit(&vHasLegend);
	VariantInit(&vTitle);
	VariantInit(&vCategoryTitle);
	VariantInit(&vValueTitle);
	VariantInit(&vExtraTitle);

	V_VT(&vSource) = VT_DISPATCH;
	V_VT(&vGallery) = VT_I4;
	V_VT(&vFormat) = VT_I2;
	V_VT(&vPlotBy) = VT_I2;
	V_VT(&vCategoryLabels) = VT_I2;
	V_VT(&vSeriesLabels) = VT_I2;
	V_VT(&vHasLegend) = VT_I2;

	V_DISPATCH(&vSource) = range.m_lpDispatch;
	V_I4(&vGallery) = chartDlg.m_cbIndex + 1;
	V_I2(&vFormat) = 1;
	V_I2(&vPlotBy) = 1;
	V_I2(&vCategoryLabels) = 1;
	V_I2(&vSeriesLabels) = 1;
	V_I2(&vHasLegend) = 1;

	chart.ChartWizard(vSource, vGallery, vFormat, vPlotBy, vCategoryLabels, 
					  vSeriesLabels, vHasLegend, vTitle, vCategoryTitle,
					  vValueTitle, vExtraTitle);
}
