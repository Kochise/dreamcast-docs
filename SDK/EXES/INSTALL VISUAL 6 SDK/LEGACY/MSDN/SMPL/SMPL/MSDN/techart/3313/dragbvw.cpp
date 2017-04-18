// dragbvw.cpp : implementation of the CDragbezView class
//

#include "stdafx.h"
#include "dragbez.h"
#include "ccables.h"

#include "dragbdoc.h"
#include "dragbvw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDragbezView

IMPLEMENT_DYNCREATE(CDragbezView, CView)

BEGIN_MESSAGE_MAP(CDragbezView, CView)
	//{{AFX_MSG_MAP(CDragbezView)
	ON_WM_LBUTTONDOWN()
	ON_WM_DESTROY()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_VIEW_LANDMARKS, OnViewLandmarks)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDragbezView construction/destruction

CDragbezView::CDragbezView()
{
  m_pCables = NULL;
  m_bConnectorHit = FALSE;
  m_ViewLandmarks = 0;
}

CDragbezView::~CDragbezView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CDragbezView drawing

void CDragbezView::OnDraw(CDC* pDC)
{
	CDragbezDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CCables Cable;
	CString szStr;
	//instructions
	szStr.LoadString(IDS_LBUTTONHELP);
	pDC->TextOut(0, 0, szStr);
	szStr.LoadString(IDS_RBUTTONHELP);
	pDC->TextOut(0, 20, szStr);
	//draw the connectors and cables
	m_pos = m_connectorlist.GetHeadPosition();
	while (m_pos) {
      Cable = m_connectorlist.GetNext(m_pos);
  	  Cable.OnDrawConnector(pDC, Cable.FIRSTCONNECT);
      Cable.OnDrawConnector(pDC, Cable.SECONDCONNECT);
	  Cable.OnDrawCable(pDC, m_ViewLandmarks);
	}
}

/////////////////////////////////////////////////////////////////////////////
// CDragbezView diagnostics

#ifdef _DEBUG
void CDragbezView::AssertValid() const
{
	CView::AssertValid();
}

void CDragbezView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDragbezDoc* CDragbezView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDragbezDoc)));
	return (CDragbezDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDragbezView message handlers

void CDragbezView::OnLButtonDown(UINT nFlags, CPoint point) 
{
    CDC *pdc = GetDC();
	//if m_pCables then user probably released Lbutton
	//outside of client area so delete dangling pointer
	if (m_pCables)
	  delete(m_pCables);

	m_pCables = new(CCables);
    m_bGestureSet = FALSE;

	if (m_pCables && pdc)
	{
  	  m_pCables->SetConnectorPoint(point, m_pCables->FIRSTCONNECT);
  	  m_pCables->OnDrawConnector(pdc, m_pCables->FIRSTCONNECT);
	  ReleaseDC(pdc);
	}
}

void CDragbezView::OnLButtonUp(UINT nFlags, CPoint point) 
{
    CDC *pdc = GetDC();
	if (m_pCables && pdc)
	{
	  if (!m_bGestureSet)
	    m_bGestureSet = m_pCables->SetGestureLimit(point);
  	  m_pCables->SetConnectorPoint(point, m_pCables->SECONDCONNECT);
  	  m_pCables->OnDrawConnector(pdc, m_pCables->SECONDCONNECT);

	  //m_pCables->OnDrawConnector(pdc, m_pCables->SECONDCONNECT, point);
	  m_pCables->OnDrawCable(pdc, m_ViewLandmarks);

	  m_connectorlist.AddTail(*m_pCables);
	  delete(m_pCables);
	  m_pCables = NULL;
	  ReleaseDC(pdc);
	}
}

void CDragbezView::OnDestroy() 
{
	CView::OnDestroy();
	
	m_connectorlist.RemoveAll();	
}


void CDragbezView::OnMouseMove(UINT nFlags, CPoint point) 
{
    if (nFlags & MK_LBUTTON)
	{
      if (m_pCables)
        m_bGestureSet = m_pCables->SetGestureLimit(point);
	}
    if (nFlags & MK_RBUTTON)
	{
	  if (m_bConnectorHit && m_pos)
	  {
        CDC *pdc = GetDC();

  	    if (pdc)
	    {
		  
		  DWORD nConnect = (m_nConnector & m_PickedCable.FIRSTCONNECT) 
		                    ? m_PickedCable.FIRSTCONNECT 
		                    : m_PickedCable.SECONDCONNECT;

		  int oldrop = pdc->SetROP2(R2_NOT);
  		  m_PickedCable.SetConnectorPoint(m_OldMousePos, nConnect);
  	      m_PickedCable.OnDrawConnector(pdc, nConnect);
	      m_PickedCable.OnDrawCable(pdc, m_ViewLandmarks);
		  
		  point.Offset(m_szHitPointDiff);
  		  m_PickedCable.SetConnectorPoint(point, nConnect);
  	      m_PickedCable.OnDrawConnector(pdc, nConnect);
	      m_PickedCable.OnDrawCable(pdc, m_ViewLandmarks);
		  m_OldMousePos = point;

		  pdc->SetROP2(oldrop);

          ReleaseDC(pdc);
	    }
	  }
	}
}

void CDragbezView::OnViewLandmarks() 
{
	CMenu *cmenu = AfxGetMainWnd()->GetMenu();
	CMenu *submenu = cmenu->GetSubMenu(2);

	if (submenu->GetMenuState(ID_VIEW_LANDMARKS, MF_BYCOMMAND) == MF_CHECKED)
	{
	  m_ViewLandmarks = 0;	
	  submenu->CheckMenuItem(ID_VIEW_LANDMARKS, MF_UNCHECKED);
	}
	else
	{
	  m_ViewLandmarks = 1;
	  submenu->CheckMenuItem(ID_VIEW_LANDMARKS, MF_CHECKED);
	}
	InvalidateRect(NULL);
}

void CDragbezView::OnEditClear() 
{
	m_connectorlist.RemoveAll();	
    m_pCables = NULL;
	m_pos = (POSITION)NULL;
	InvalidateRect(NULL);
}

void CDragbezView::OnRButtonDown(UINT nFlags, CPoint point) 
{
    POSITION pos;
	pos = m_connectorlist.GetHeadPosition();
	while (pos) {
	  m_pos = pos;
      m_PickedCable = m_connectorlist.GetNext(pos);
	  if ((m_nConnector = m_PickedCable.HittestConnector(point)))
	  {
	    m_bConnectorHit = TRUE;
        m_OldMousePos = m_PickedCable.GetConnectorPoint(m_nConnector);
		m_szHitPointDiff = m_OldMousePos - point;
	    break;
	  }
	  else
	  {
	    m_bConnectorHit = FALSE;
	  }
	}
}

void CDragbezView::OnRButtonUp(UINT nFlags, CPoint point) 
{	 
    if (m_pos)
	{
      m_connectorlist.SetAt(m_pos, m_PickedCable);
	  InvalidateRect(NULL);
	}
	else
	  MessageBeep(0);
}

