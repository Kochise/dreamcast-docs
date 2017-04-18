#include "stdafx.h"
#include "Scribble.h"

#include "ChildFrm.h"
#include <afxpriv.h>		// **MOD** for WM_IDLEUPDATECMDUI

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	ON_MESSAGE(WM_IDLEUPDATECMDUI, OnIdleUpdateCmdUI) // **MOD**
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CChildFrame::CChildFrame()
{
	m_bModLast = -1;			// **MOD** initialize mod-state memory
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	return CMDIChildWnd::PreCreateWindow(cs);
}

//////////////////
// **MOD**
// Override to add asterisk if doc is modified.
//
void CChildFrame::OnUpdateFrameTitle(BOOL bAddToTitle)
{
	CMDIChildWnd::OnUpdateFrameTitle(bAddToTitle);
	CDocument* pDoc = GetActiveDocument();
	if (pDoc && pDoc->IsModified()) {
		// if doc modified, append * to normal title
		CString title;
		GetWindowText(title);
		title += '*';
		SetWindowText(title);
	}
}

//////////////////
// **MOD**
// Handle WM_IDLEUPDATECMDUI to update modified indicator if necessary.
//
LRESULT CChildFrame::OnIdleUpdateCmdUI(WPARAM wParam, LPARAM)
{
	// Only update the title if the modified state has changed.
	// Otherwise, the title bar will flicker.
	// 
	CDocument* pDoc = GetActiveDocument();
	if (m_bModLast != pDoc->IsModified()) {
		// mod state has changed: set flag telling MFC to update title
		m_nIdleFlags |= idleTitle;	
		m_bModLast = pDoc->IsModified();
	}

	// do the default thing
	CMDIChildWnd::OnIdleUpdateCmdUI();

	return 0L;
}

