#include "TitleBar.h"

/////////////////
// My own title bar derived from generic title bar
// Handles View title bar command and enable/disable of indicators
//
class CMyTitleBar : public CTitleBar {
public:
	DECLARE_DYNAMIC(CMyTitleBar)
	CMyTitleBar();
	~CMyTitleBar();
	BOOL	m_bViewTitleInfo;
protected:	
	//{{AFX_MSG(CMyTitleBar)
	afx_msg void OnViewTitleInfo();
	afx_msg void OnUpdateUIViewTitleInfo(CCmdUI* pCmdUI);
	afx_msg void OnUpdateUINumStrokes(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

class CChildFrame : public CMDIChildWnd {
	DECLARE_DYNCREATE(CChildFrame)
	CMyTitleBar	m_titleBar;	// title bar "window"
public:
	CChildFrame();
	virtual ~CChildFrame();
	//{{AFX_VIRTUAL(CChildFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

	// **MOD** Overrride
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra,
		AFX_CMDHANDLERINFO* pHandlerInfo);

protected:
	//{{AFX_MSG(CChildFrame)
	afx_msg LRESULT OnIdleUpdateCmdUI(WPARAM wParam, LPARAM);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
