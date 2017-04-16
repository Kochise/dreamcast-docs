/////////////////////////////////////////////////////////////////////////////
// MainFrm.h : interface of the CMainFrame class
//
// This is a part of the Webster HTTP Server application
// for Microsoft Systems Journal
//

#include "TrayNot.h"

class CMainFrame : public CFrameWnd
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
protected:
	CSplitterWnd m_wndSplitter;
	// these are used for icon notification
	CTrayNot*	m_pTray ;
	BOOL			m_bWin95 ;		// local indicator of O/S type
	BOOL			m_bHidden ;		// Windows 95: visible or hidden?
public:
	UINT			m_nSanityTime ;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:	// internal helper functions
	void NotifyHandler ( BOOL bShowActive );

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnProperties();
	afx_msg void OnUnHide();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg LONG OnNewClient(UINT,LONG);
	afx_msg LONG OnKillSocket(WPARAM wParam, LPARAM lParam); 
	afx_msg LONG OnNewLogfile(WPARAM wParam, LPARAM lParam); 
	afx_msg LONG OnMyNotify(UINT,LONG);
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg LRESULT OnIdleUpdateCmdUI(WPARAM wParam, LPARAM);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
