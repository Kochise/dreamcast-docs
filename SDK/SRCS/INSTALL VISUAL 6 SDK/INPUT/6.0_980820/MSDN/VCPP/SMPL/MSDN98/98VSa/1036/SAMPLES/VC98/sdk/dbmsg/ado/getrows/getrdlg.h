//--------------------------------------------------------------------
// Microsoft ADO Samples
//
// (c) 1996 Microsoft Corporation.  All Rights Reserved.
//
// @doc GetRows Sample
//
// @module	getrdlg.h
//
// @devnote None
//--------------------------------------------------------------------

/////////////////////////////////////////////////////////////////////////////
// CGetRowsDlg dialog

class CGetRowsDlg : public CDialog
{
// Construction
public:
	CGetRowsDlg(CWnd* pParent = NULL);	// standard constructor
	~CGetRowsDlg();

	//Performs the standard DAO GetRows
	HRESULT DoGetRows();
				

// Dialog Data
	//{{AFX_DATA(CGetRowsDlg)
	enum { IDD = IDD_MAINFORM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGetRowsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	ADOConnection*			m_piConnection;
	ADORecordset*			m_piEmpRecordSet;
	CString					m_strSource;
	CString					m_strUser;
	CString					m_strPassword;
	CString					m_strSQL;

	void OnExecute();
	// Generated message map functions
	//{{AFX_MSG(CGetRowsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

// Field numbers for employee table
#define	EMP_ID			0L // Must use LONG or compiler gets confused with NULL
#define	EMP_LNAME		1
#define	EMP_FNAME		2
#define MAX_EMP_REC		10 // Arbitrary maximum


