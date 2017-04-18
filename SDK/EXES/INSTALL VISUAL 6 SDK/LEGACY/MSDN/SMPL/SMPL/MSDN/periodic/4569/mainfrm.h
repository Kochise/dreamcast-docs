#include "bufwnd.h"

/////////////////
// Main frame window for TRACEWIN contains trace buffer as child window, 
// not a view.
//
class CMainFrame : public CFrameWnd {
	DECLARE_DYNAMIC(CMainFrame)
	CBufWnd		m_wndBuffer;		// TRACE buffer
	CFile			m_file;				// if outputting to file
	UINT			m_nOutputWhere;	// where to output

	// helpers
	BOOL OpenFile(CFile& f, LPCSTR lpszPathName);	// helper
	void CloseTraceFile();
	void SaveSettings();

public:
	CMainFrame();
	virtual ~CMainFrame();

protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra,
		AFX_CMDHANDLERINFO* pHandlerInfo);

	//{{AFX_MSG(CMainFrame)
	afx_msg LRESULT OnTraceMsg(WPARAM wp, LPARAM lp);
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnClose();

	afx_msg void OnFileSaveAs();
	afx_msg void OnUpdateFileSaveAs(CCmdUI* pCmdUI);
	afx_msg void OnOutputOff();
	afx_msg void OnUpdateOutputOff(CCmdUI* pCmdUI);
	afx_msg void OnOutputToFile();
	afx_msg void OnUpdateOutputToFile(CCmdUI* pCmdUI);
	afx_msg void OnOutputToWindow();
	afx_msg void OnUpdateOutputToWindow(CCmdUI* pCmdUI);

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
