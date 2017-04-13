//--------------------------------------------------------------------
// Microsoft ADO Samples
//
// (c) 1996 Microsoft Corporation.  All Rights Reserved.
//
// @doc ADORead Sample
//
// @module	ADOrddlg.h
//
// @devnote None
//--------------------------------------------------------------------
// ADOReadDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CADOReadDlg dialog

class CADOReadDlg : public CDialog
{
// Construction
public:
	CADOReadDlg(CWnd* pParent = NULL);	// standard constructor
	~CADOReadDlg();

	//Display results of query
	void CADOReadDlg::DisplayQueryTime(int iControlID, int iUnitsID, DWORD dwDuration);
	void CADOReadDlg::AddFieldToList(LONG lRecordNum, COleVariant *pdbVar);
	void CADOReadDlg::Execute(CursorTypeEnum cursorType, int iControlID, int iUnitsID); 
// Dialog Data
	//{{AFX_DATA(CADOReadDlg)
	enum { IDD = IDD_DAOREAD_DIALOG };
	CComboBox	m_comboBoxMode;
	CComboBox	m_comboBoxOption;		 	
	long	m_lCacheSize;	
	CString	m_strTableQuery;
	long	m_lNumRows;
	BOOL	m_bDynamic;
	BOOL	m_bKeyset;
	BOOL	m_bStatic;
	BOOL	m_bForwardOnly;
	CString	m_strSource; 
	CString	m_strUser;
	CString	m_strPassword;
	CString	m_strProvider;
	long	m_lConnectOption;	
	long	m_lConnectMode;
//	BOOL	m_bReadOnly;
	//}}AFX_DATA

//	CADODefaultWorkspace m_cDefaultWorkspace;
	ADOConnection *		m_piConnection;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CADOReadDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	HICON m_hIcon;
	CComboBox m_ComboBoxOption;

	// Generated message map functions
	//{{AFX_MSG(CADOReadDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDatabase();
	afx_msg void OnExecute();
	afx_msg void OnSelchangeConnectMode();
	afx_msg void OnSelchangeConnectOption();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};



