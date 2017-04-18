// EmpDlg.h : header file
//

#include "EmpBiz.h"

/////////////////////////////////////////////////////////////////////////////
// CEmpDlg dialog

class CEmpDlg : public CDialog
{
// Construction
public:
	CEmpDlg(CWnd* pParent = NULL);	// standard constructor
	~CEmpDlg();

// Dialog Data
	//{{AFX_DATA(CEmpDlg)
	enum { IDD = IDD_EMP_DIALOG };
	long	m_nEmpNum;
	CString	m_strFirstName;
	CString	m_strHomePhone;
	CString	m_strLastName;
	CString	m_strTitle;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEmpDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

// Operations
public:
	BOOL CommitAlteredEmpRec();	
	void SetFieldStates() ;
	CString PrepareCriteria();



// Implementation
protected:
	HICON		m_hIcon;
	CEmpBiz*	m_pBiz;

	// Generated message map functions
	//{{AFX_MSG(CEmpDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnEditAdd();
	afx_msg void OnEditDelete();
	afx_msg void OnEditNext();
	afx_msg void OnEditPrevious();
	afx_msg void OnEditFirst();
	afx_msg void OnEditLast();
	afx_msg void OnEditFindF();
	afx_msg void OnAppOpenRecord();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


#define EMP_EMPLOYEE_ID		L"EmployeeID"
#define	EMP_LAST_NAME		L"LastName"
#define	EMP_FIRST_NAME		L"FirstName"
#define EMP_TITLE			L"Title"
#define EMP_HOME_PHONE		L"HomePhone"
