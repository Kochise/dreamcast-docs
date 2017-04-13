// zapdlg.h : header file.  This dialog allows you to enter which project
//             off of which to base the custom AppWizard.
//
// Copyright (c) 1985-1998, Microsoft Corporation. All rights reserved.
//

/////////////////////////////////////////////////////////////////////////////
// CZapDlg dialog

class CZapDlg : public CAppWizStepDlg
{
// Construction
public:
	CZapDlg();   // standard constructor
	virtual BOOL OnDismiss();

// Dialog Data
	//{{AFX_DATA(CZapDlg)
	enum { IDD = IDD_ZAP };
	CString m_strProjName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZapDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CZapDlg)
	afx_msg void OnBrowse();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

enum enProjType { projUnknown, projExe, projDLL, projJava };

enProjType GetProjectType(LPCTSTR lpszProjName);
