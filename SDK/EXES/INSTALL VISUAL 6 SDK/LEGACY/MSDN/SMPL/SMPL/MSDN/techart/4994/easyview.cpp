// fileview.cpp : implementation file
//

#include "stdafx.h"
#include "easyview.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEasyOutputView

IMPLEMENT_DYNCREATE(CEasyOutputView, CView)

CEasyOutputView::CEasyOutputView()
{
}

CEasyOutputView::~CEasyOutputView()
{
}

#define ID_LB 0xd000

BEGIN_MESSAGE_MAP(CEasyOutputView, CView)
    ON_LBN_DBLCLK(ID_LB,OnLBDoubleClicked)
	//{{AFX_MSG_MAP(CEasyOutputView)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// CEasyOutputView diagnostics

#ifdef _DEBUG
void CEasyOutputView::AssertValid() const
{
	CView::AssertValid();
}

void CEasyOutputView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEasyOutputView message handlers


void CEasyOutputView::OnSize(UINT nType, int cx, int cy) 
{
 CView::OnSize(nType, cx, cy);
 m_LB.SetHorizontalExtent(m_iLongestStringSizeInPixels);
 if (m_LB.m_hWnd)
 m_LB.SetWindowPos(NULL,0,0,cx,cy,SWP_NOZORDER);
}

int CEasyOutputView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
 if (CView::OnCreate(lpCreateStruct) == -1)
  return -1;
 m_LB.Create(LBS_NOINTEGRALHEIGHT|WS_VISIBLE|/*WS_CHILD|*/WS_HSCROLL|WS_VSCROLL|LBS_NOTIFY,CRect(20,20,20,20),this,ID_LB);
 m_cfFixedFont = new CFont();
 m_cfFixedFont->CreateStockObject(ANSI_FIXED_FONT);
 m_LB.SetFont(m_cfFixedFont);
 LOGFONT lfCurrentFont;
 m_cfFixedFont->GetObject(sizeof(LOGFONT),&lfCurrentFont);
 m_iFontWidth = lfCurrentFont.lfWidth;  // should be good enough...
 m_iLongestStringSizeInPixels = 0;
 InitializeCriticalSection(&m_csAddString);
 return 0;
}

void CEasyOutputView::ClearWindow()
{
 m_LB.ResetContent();
};

void CEasyOutputView::AddStringandAdjust(char *cString)
{   
 ComputeNewHorizontalExtent(m_iFontWidth*strlen(cString));
 m_LB.AddString(cString);
};

void CEasyOutputView::OnDestroy() 
{   
 delete m_cfFixedFont;
 DeleteCriticalSection(&m_csAddString);
 CView::OnDestroy();
}

afx_msg void CEasyOutputView::OnLBDoubleClicked()
{ 
 DispatchDoubleClick(m_LB.GetText(m_LB.GetCurSel(),m_Selection));
};

// just to satisfy the IMPLEMENT_DYNACREATE macro...

void CEasyOutputView::DispatchDoubleClick(int iVal)
{
}; 


void CEasyOutputView::OnDraw(CDC* pDC) 
{
}
