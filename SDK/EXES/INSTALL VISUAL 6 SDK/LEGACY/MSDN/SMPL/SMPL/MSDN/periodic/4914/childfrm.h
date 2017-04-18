#include "TitleBar.h"

class CChildFrame : public CMDIChildWnd {
	DECLARE_DYNCREATE(CChildFrame)
	CTitleBar	m_titleBar;		// **MOD** title bar info
	BOOL	m_bViewTitleInfo;		// **MOD** whether to display pane info

public:
	CChildFrame();
	virtual ~CChildFrame();
	//{{AFX_VIRTUAL(CChildFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CChildFrame)
	// **MOD** new functions
	afx_msg LRESULT OnIdleUpdateCmdUI(WPARAM wParam, LPARAM);
	afx_msg void OnViewTitleInfo();
	afx_msg void OnUpdateUIViewTitleInfo(CCmdUI* pCmdUI);
	afx_msg void OnUpdateUINumStrokes(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
