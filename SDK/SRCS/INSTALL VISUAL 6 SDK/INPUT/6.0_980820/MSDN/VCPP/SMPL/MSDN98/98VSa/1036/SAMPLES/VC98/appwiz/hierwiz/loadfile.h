// loadfile.h : header file.  This dialog allows you to enter the sample file path
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1995 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and Microsoft
// QuickHelp and/or WinHelp documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

/////////////////////////////////////////////////////////////////////////////
// CLoadFileDlg dialog

class CLoadFileDlg : public CAppWizStepDlg
{
// Construction
public:
	CLoadFileDlg();   // standard constructor
	virtual BOOL OnDismiss();

// Dialog Data
	//{{AFX_DATA(CLoadFileDlg)
	enum { IDD = IDD_LOADFILE };
	CString m_strProjName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLoadFileDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLoadFileDlg)
	afx_msg void OnBrowse();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
