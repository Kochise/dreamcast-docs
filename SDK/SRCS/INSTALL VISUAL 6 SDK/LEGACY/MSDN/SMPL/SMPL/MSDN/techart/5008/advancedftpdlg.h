#ifndef __CADVANCEDFTPDLG__
#define __CADVANCEDFTPDLG__

// AdvancedFTPDlg.h : header file
//
#include <WinINet.h>


/////////////////////////////////////////////////////////////////////////////
// CAdvancedFTPDlg dialog

class CAdvancedFTPDlg : public CDialog
{
// Construction
public:
	CAdvancedFTPDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAdvancedFTPDlg)
	enum { IDD = IDD_ADVANCEDFTP_DIALOG };
	CProgressCtrl	m_TotalProgress;
	CListCtrl	m_FTPList;
	CListCtrl	m_DownloadList;
	CString	m_DownloadDirectory;
	CString	m_FTPSite;
	CString	m_Password;
	CString	m_Username;
	CString	m_ProxyServer;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAdvancedFTPDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAdvancedFTPDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnDestroy();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAddall();
	afx_msg void OnHelp();
	afx_msg void OnAddselected();
	afx_msg void OnBrowsedir();
	afx_msg void OnDownload();
	afx_msg void OnGetdirectorylisting();
	afx_msg void OnRemoveall();
	afx_msg void OnRemoveselected();
	afx_msg void OnCanceloperation();
	afx_msg void OnDblclkFtplistng(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSiteconnect();
	afx_msg void OnSitedisconnect();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	//
	// My functions
	//

protected:
	BOOL ConnectToInternet();			// routine to connect to Internet
	BOOL ConnectToSite();				// routine to connect to FTP Server
	BOOL EnumerateDirectory();			// routine to enumerate directory into list view
	BOOL CloseSiteConnection();			// routine to close connection to ftp server
	BOOL CloseInternetConnection();		// routine to close connection to Internet

	CStatusBarCtrl StatusBar;			// our status bar
	WIN32_FIND_DATA m_sWFD;				// structure for dir enumeration data

	HANDLE hWaitForHandleCreation;		// class handle for event tracking
	
	HWND m_hStatusBarCtrl;				// handle to status window

	BOOL m_CancelOperation;				// boolean to force cancelation of an operation

	// THREAD STUFF
	CWinThread * Callback_Thread;		// thread class for WinINet callback
	CWinThread * Status_Thread;			// thread class for status display
	CWinThread * SiteConnect_Thread;	// thread class for FTP server connection

	BOOL SetupSiteThreads();			// routine to set up server connection threads
	BOOL SetupWorkerThreads();			// routine to set up threads
	static UINT CallbackThread_Proc(LPVOID lParm);		// callback thread proc
	static UINT StatusThread_Proc(LPVOID lParm);		// status thread proc
	static UINT SiteConnectThread_Proc(LPVOID lParm);	// FTP server connection thread proc

public:
	// routine to copy 
	BOOL CopyListCtrlLine(CListCtrl * pListCtrlTo, int iToLine, CListCtrl * pListCtrlFrom, int iFromLine, BOOL bDelete);
	void TransferLines(CListCtrl * pListCtrlTo, CListCtrl * pListCtrlFrom, int iFlags);
	long DownloadFile(HINTERNET hSession, CString InputFileSpec, CString OutputFileSpec, DWORD dwContext);
};

#endif //#ifndef __CADVANCEDFTPDLG__
