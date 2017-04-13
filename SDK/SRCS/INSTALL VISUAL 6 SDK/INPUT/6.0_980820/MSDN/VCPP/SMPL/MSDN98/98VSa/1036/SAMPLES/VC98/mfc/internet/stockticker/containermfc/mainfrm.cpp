// MainFrm.cpp : implementation of the CMainFrame class
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
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_INITMENUPOPUP()
	//}}AFX_MSG_MAP
	ON_WM_SYSCOMMAND()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here

}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.cy = 60;
	cs.cx = 300;
	cs.hMenu = 0;       // don't want a menu.
	return CFrameWnd::PreCreateWindow(cs);
}

void CMainFrame::OnUpdateFrameTitle(BOOL bAddToTitle)
{
	// don't call base class version so "Untitled -" is not prepended.
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{   // storing code
	}
	else
	{   // loading code
	}
}

void CMainFrame::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == ID_APP_ABOUT)     // pass onto app.
		((CContainerMFCApp*)AfxGetApp())->OnAppAbout();
	else if ((nID & 0xFFF0) == ID_STAY_ON_TOP)
	{
		CMenu* pSysMenu = AfxGetMainWnd()->GetSystemMenu(FALSE);
		ASSERT(pSysMenu);
		if (pSysMenu)
		{
			bool    bChecked = pSysMenu->GetMenuState(ID_STAY_ON_TOP, MF_BYCOMMAND) == MF_CHECKED;
			((CContainerMFCDoc*)GetActiveDocument())->SetStayOnTop(this, !bChecked);
		}
	}
	else
		CFrameWnd::OnSysCommand(nID, lParam);
}


void CMainFrame::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
	CFrameWnd::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);

	bool    bChecked = pPopupMenu->GetMenuState(ID_STAY_ON_TOP, MF_BYCOMMAND) == MF_CHECKED;
	pPopupMenu->CheckMenuItem(ID_STAY_ON_TOP,
		MF_BYCOMMAND | (bChecked ? MF_UNCHECKED : MF_CHECKED));
}
