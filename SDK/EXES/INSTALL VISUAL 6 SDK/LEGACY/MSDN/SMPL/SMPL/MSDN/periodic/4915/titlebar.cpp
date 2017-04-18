////////////////////////////////////////////////////////////////
// Implementation for title bar
//
#include "stdafx.h"
#include "titlebar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(CTitleBar, CCmdTarget)

//////////////////
// One of these for each inidicator
//
struct TITLEPANE {
	CString	m_sText;			// current text
	UINT		m_nID;			// indicator ID
	BOOL		m_bEnabled;		// enabled?
};

CTitleBar::CTitleBar()
{
	m_nCount  = 0;
	m_arPanes = NULL;
}

CTitleBar::~CTitleBar()
{
	delete [] m_arPanes;			// OK if NULL
}

//////////////////
// Call this when your frame is constructed, i.e., from OnCreate, to
// create the indicators.
//
BOOL CTitleBar::SetIndicators(const UINT* lpIDs, int nCount)
{
	// Allocate indicator array
	ASSERT(nCount>0);
	m_arPanes = new TITLEPANE[nCount];
	ASSERT(m_arPanes);

	// Initialize panes
	for (int i=0; i<nCount; i++) {
		TITLEPANE& pane = m_arPanes[i];
		pane.m_nID = lpIDs[i];
		pane.m_bEnabled = TRUE;
	}
	m_nCount = nCount;
	return TRUE;
}

//////////////////
// This class is private to this file.
//
class CTitleCmdUI : public CCmdUI {
public: 
	TITLEPANE*	m_pPane;		// ptr to associate title pane

	// re-implementations:
	virtual void Enable(BOOL bOn);
	virtual void SetCheck(int nCheck);
	virtual void SetText(LPCTSTR lpszText);
};

void CTitleCmdUI::Enable(BOOL bOn)
{
	m_bEnableChanged = TRUE;	// used by MFC
	m_pPane->m_bEnabled = bOn;
}

void CTitleCmdUI::SetCheck(int nCheck)
{
	// no-op
}

void CTitleCmdUI::SetText(LPCTSTR lpszText)
{
	m_pPane->m_sText = lpszText;
}

//////////////////
// Do idle update of all title bar indicators
// You must handle WM_IDLEUPDATEUI from your frame window and
// call this method from your handler.
//
void CTitleBar::OnIdleUpdate(CFrameWnd* pFrame, BOOL bDisableIfNoHndler)
{
	m_sTitle.Empty();

	CTitleCmdUI cmdui;
	cmdui.m_nIndexMax = m_nCount;
	for (UINT i=0; i<cmdui.m_nIndexMax; i++) {
		TITLEPANE& pane = m_arPanes[i];
		cmdui.m_nIndex  = i;
		cmdui.m_pPane   = &pane;
		cmdui.m_nID     = pane.m_nID;
		cmdui.DoUpdate(pFrame, FALSE);
		if (pane.m_bEnabled)
			m_sTitle += pane.m_sText;
	}
	if (m_sPrevTitle != m_sTitle) {
		pFrame->OnUpdateFrameTitle(TRUE);
		CString title;
		pFrame->GetWindowText(title);
		title += m_sTitle;
		pFrame->SetWindowText(title);
		m_sPrevTitle = m_sTitle;
	}
}
