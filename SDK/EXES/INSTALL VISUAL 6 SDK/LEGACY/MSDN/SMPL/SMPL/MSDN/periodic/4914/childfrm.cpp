#include "stdafx.h"
#include "Scribble.h"
#include "ChildFrm.h"
#include <afxpriv.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
	//{{AFX_MSG_MAP(CChildFrame)
	ON_MESSAGE(WM_IDLEUPDATECMDUI, OnIdleUpdateCmdUI)
	ON_COMMAND(ID_VIEW_TITLE_INFO, OnViewTitleInfo)
	ON_UPDATE_COMMAND_UI(ID_VIEW_TITLE_INFO,  OnUpdateUIViewTitleInfo)
	ON_UPDATE_COMMAND_UI(ID_TITLE_NUMSTROKES, OnUpdateUINumStrokes)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CChildFrame::CChildFrame()
{
	// By default, don't display title pane info
	m_bViewTitleInfo = FALSE;

	// Create title bar indicators
	static UINT indicators[] = { ID_TITLE_MOD, ID_TITLE_NUMSTROKES };
	m_titleBar.SetIndicators(indicators, 
		sizeof(indicators)/sizeof(indicators[0]));
}

CChildFrame::~CChildFrame()
{
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	return CMDIChildWnd::PreCreateWindow(cs);
}

//////////////////
// **MOD** Handle idle command update
//
LRESULT CChildFrame::OnIdleUpdateCmdUI(WPARAM wParam, LPARAM)
{
	m_titleBar.OnIdleUpdate(this, (BOOL)wParam);	// pass to title bar
	CMDIChildWnd::OnIdleUpdateCmdUI();				// pass to default handler
	return 0L;
}

//////////////////
// **MOD** command and command update handlers
//
void CChildFrame::OnViewTitleInfo()
{
	m_bViewTitleInfo = !m_bViewTitleInfo;
}

void CChildFrame::OnUpdateUIViewTitleInfo(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bViewTitleInfo);
}

void CChildFrame::OnUpdateUINumStrokes(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(m_bViewTitleInfo);
}
