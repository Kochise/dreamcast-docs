/////////////////
// Buffer window for TRACEWIN.
//
// CBufWnd implements the trace buffer. 
// Implements its own editing commands commands: Copy, Clear, Select All. 
// In order to work, the CBufWnd must be connected to the app's command 
// route by overriding CMainFrame::OnCmdMsg.
//
class CBufWnd : public CEdit {
	CFont	m_font;				// monotype font
public:
	CBufWnd();
public:
	virtual ~CBufWnd();
	BOOL Create(CWnd* pParentWnd, UINT nID);
	BOOL IsEmpty();
protected:
	//{{AFX_MSG(CBufWnd)
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnEditClearAll();
	afx_msg void OnEditCopy();
	afx_msg void OnEditSelectAll();
	afx_msg void OnUpdateEditClearAll(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditCopy(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditSelectAll(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
