/////////////////////////////////////////////////////////////////////////////
// Config.h : header file
//
// This is a part of the Webster HTTP Server application
// for Microsoft Systems Journal
//

#ifndef __CONFIG_H__
#define __CONFIG_H__

/////////////////////////////////////////////////////////////////////////////
// CServer dialog

class CServer : public CPropertyPage
{
	DECLARE_DYNCREATE(CServer)

// Construction
public:
	CServer();
	~CServer();

// Dialog Data
	//{{AFX_DATA(CServer)
	enum { IDD = IDD_SERVER };
	UINT	m_nPort;
	UINT	m_nMaxConnects;
	UINT	m_nSanityTime;
	UINT	m_nTimeOut;
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CServer)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CServer)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////
// CHTML dialog

class CHTML : public CPropertyPage
{
	DECLARE_DYNCREATE(CHTML)

// Construction
public:
	CHTML();
	~CHTML();

// Dialog Data
	//{{AFX_DATA(CHTML)
	enum { IDD = IDD_HTML };
	CString	m_DefaultName;
	CString	m_DefaultPath;
	int		m_nTagType;
	CString	m_TagFile;
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CHTML)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CHTML)
	afx_msg void OnHtmlBrowse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////
// CLogging dialog

class CLogging : public CPropertyPage
{
	DECLARE_DYNCREATE(CLogging)

// Construction
public:
	CLogging();
	~CLogging();

// Dialog Data
	//{{AFX_DATA(CLogging)
	enum { IDD = IDD_LOGGING };
	BOOL	m_bLogEnable;
	CString	m_LogPath;
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CLogging)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CLogging)
	afx_msg void OnLogBrowse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////
// CStatus dialog

class CStatus : public CPropertyPage
{
	DECLARE_DYNCREATE(CStatus)

// Construction
public:
	CStatus();
	~CStatus();

// Dialog Data
	//{{AFX_DATA(CStatus)
	enum { IDD = IDD_STATUS };
	BOOL	m_bStatusEnable;
	BOOL	m_bDebugEnable;
	BOOL	m_bHostName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CStatus)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CStatus)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////
// CAlert dialog

class CAlert : public CPropertyPage
{
	DECLARE_DYNCREATE(CAlert)

// Construction
public:
	CAlert();
	~CAlert();

// Dialog Data
	//{{AFX_DATA(CAlert)
	enum { IDD = IDD_ALERT };
	BOOL	m_bEnableSound;
	BOOL	m_bEnableIcon;
	//}}AFX_DATA

// User defined data
	HICON	m_hIdle ;
	HICON	m_hActive ;

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CAlert)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CAlert)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};



#endif // __CONFIG_H__
