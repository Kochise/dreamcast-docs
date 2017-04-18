// mfctrvw.cpp : implementation of the CMfctrackView class
//

#include "stdafx.h"
#include "mfcprop.h"

#include "mfctrdoc.h"
#include "mfctrvw.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMfctrackView

IMPLEMENT_DYNCREATE(CMfctrackView, CView)

BEGIN_MESSAGE_MAP(CMfctrackView, CView)
	//{{AFX_MSG_MAP(CMfctrackView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_HSCROLL()
	ON_COMMAND(IDM_PROPERTIES, OnProperties)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMfctrackView construction/destruction

CMfctrackView::CMfctrackView()
{
	// TODO: add construction code here

}

CMfctrackView::~CMfctrackView()
{
}

/////////////////////////////////////////////////////////////////////////////
// CMfctrackView drawing

void CMfctrackView::OnDraw(CDC* pDC)
{
	CMfctrackDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

/////////////////////////////////////////////////////////////////////////////
// CMfctrackView diagnostics

#ifdef _DEBUG
void CMfctrackView::AssertValid() const
{
	CView::AssertValid();
}

void CMfctrackView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMfctrackDoc* CMfctrackView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMfctrackDoc)));
	return (CMfctrackDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMfctrackView message handlers

int CMfctrackView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Create the sliders
	m_Slider.Create(WS_CHILD | WS_VISIBLE | TBS_AUTOTICKS | TBS_TOP | TBS_ENABLESELRANGE,
				CRect(10,100,200,130),
				this,         
				ID_SLIDER);         

	// set the default range
	m_Min = 1;
	m_Max = 25;
	m_Slider.SetRange(m_Min, m_Max, TRUE);

	// set the selection 
	m_Slider.SetSelection(10, 20);

	// set the page size
	m_PageSize = 5;
	m_Slider.SetPageSize(m_PageSize);

	// set the line size
	m_LineSize = 2;
	m_Slider.SetLineSize(m_LineSize);
	
	return 0;
}

void CMfctrackView::OnDestroy() 
{
	CView::OnDestroy();
	
	// TODO: Add your message handler code here

	
}


// This function checks to see if a trackbar notification is being sent
// and, if so, updates the status bar with the notification message.
void CMfctrackView::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	BOOL bMsg = TRUE;
	char szMsg[32];
	char szBuf[256];

	switch(nSBCode)
	{
		case TB_BOTTOM:
			lstrcpy(szMsg,"TB_BOTTOM");
			break;

		case TB_ENDTRACK:
			lstrcpy(szMsg,"TB_ENDTRACK");
			break;

		case TB_LINEDOWN:
			lstrcpy(szMsg,"TB_LINEDOWN");
			break;

		case TB_LINEUP:
			lstrcpy(szMsg,"TB_LINEUP");
			break;

		case TB_PAGEDOWN:
			lstrcpy(szMsg,"TB_PAGEDOWN");
			break;

		case TB_PAGEUP:
			lstrcpy(szMsg,"TB_PAGEUP");
			break;

		case TB_THUMBPOSITION:
			lstrcpy(szMsg,"TB_THUMPOSITION");
			break;

		case TB_THUMBTRACK:
			lstrcpy(szMsg,"TB_THUMBTRACK");
			break;

		default:
			bMsg = FALSE;
			break;

	}
	if (bMsg == TRUE)
	{
		CStatusBar *pStatus  = (CStatusBar *)GetParentFrame()->
			GetDescendantWindow(ID_VIEW_STATUS_BAR);

  		sprintf(szBuf,"Trackbar message: %s",szMsg);

		pStatus->SetPaneText(0, szBuf);
		pStatus->UpdateWindow();
	}
	
	CView::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CMfctrackView::OnProperties() 
{
   // Create a property sheet object.
   CPropertySheet dlgPropertySheet("Slider Properties",this);
   CPage sizePage;
   CRange rangePage;

   dlgPropertySheet.AddPage(&sizePage);
   dlgPropertySheet.AddPage(&rangePage);

   rangePage.m_Min = m_Min;
   rangePage.m_Max = m_Max;
   sizePage.m_PageSize = m_PageSize;
   sizePage.m_LineSize = m_LineSize;

   if (dlgPropertySheet.DoModal() == IDOK)
   {
   		m_Slider.SetRange(rangePage.m_Min, rangePage.m_Max);
		m_Slider.SetPageSize(sizePage.m_PageSize);
		m_Slider.SetLineSize(sizePage.m_LineSize);
        GetDocument()->SetModifiedFlag();
        GetDocument()->UpdateAllViews(NULL);
   }
}

/////////////////////////////////////////////////////////////////////////////
// propsheet

IMPLEMENT_DYNAMIC(propsheet, CPropertySheet)

propsheet::propsheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

propsheet::propsheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

propsheet::~propsheet()
{
}


BEGIN_MESSAGE_MAP(propsheet, CPropertySheet)
	//{{AFX_MSG_MAP(propsheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// propsheet message handlers
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CPage property page

IMPLEMENT_DYNCREATE(CPage, CPropertyPage)

CPage::CPage() : CPropertyPage(CPage::IDD)
{
	//{{AFX_DATA_INIT(CPage)
	m_LineSize = 0;
	m_PageSize = 0;
	//}}AFX_DATA_INIT
}

CPage::~CPage()
{
}

void CPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPage)
	DDX_Text(pDX, IDC_LINESIZE, m_LineSize);
	DDV_MinMaxInt(pDX, m_LineSize, 1, 10);
	DDX_Text(pDX, IDC_PAGESIZE, m_PageSize);
	DDV_MinMaxInt(pDX, m_PageSize, 1, 10);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPage, CPropertyPage)
	//{{AFX_MSG_MAP(CPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CPage message handlers
/////////////////////////////////////////////////////////////////////////////
// CRange property page

IMPLEMENT_DYNCREATE(CRange, CPropertyPage)

CRange::CRange() : CPropertyPage(CRange::IDD)
{
	//{{AFX_DATA_INIT(CRange)
	m_Max = 0;
	m_Min = 0;
	//}}AFX_DATA_INIT
}

CRange::~CRange()
{
}

void CRange::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRange)
	DDX_Text(pDX, IDC_MAX, m_Max);
	DDV_MinMaxInt(pDX, m_Max, 1, 100);
	DDX_Text(pDX, IDC_MIN, m_Min);
	DDV_MinMaxInt(pDX, m_Min, 1, 100);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRange, CPropertyPage)
	//{{AFX_MSG_MAP(CRange)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CRange message handlers

