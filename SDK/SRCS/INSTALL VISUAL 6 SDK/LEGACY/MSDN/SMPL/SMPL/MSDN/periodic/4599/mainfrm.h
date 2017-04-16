#include "trayicon.h"

//////////////////
// Main frame for TRAYTEST.
//
class CMainFrame : public CFrameWnd {
public:
	CMainFrame();
	virtual ~CMainFrame();
protected:
	DECLARE_DYNAMIC(CMainFrame)
	CStatusBar	m_wndStatusBar;

	CTrayIcon	m_trayIcon;		// my tray icon
	CEdit			m_wndEdit;		// to display tray notifications
	int			m_iWhichIcon;	// 0/1 which HICON to use
	BOOL			m_bShutdown;	// OK to terminate TRAYTEST
	BOOL			m_bShowTrayNotifications;	// display info in main window

	//{{AFX_MSG(CMainFrame)
	afx_msg LRESULT OnTrayNotification(WPARAM wp, LPARAM lp);
	afx_msg int	 OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnToggleIcon();
	afx_msg void OnViewClear();
	afx_msg void OnViewNotifications();
	afx_msg void OnUpdateViewClear(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewNotifications(CCmdUI* pCmdUI);
	afx_msg void OnClose();
	afx_msg void OnAppOpen();
	afx_msg void OnAppSuspend();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
