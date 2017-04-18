#ifndef __WELCOME_H__
#define __WELCOME_H__

// Welcome.h : header file
//

// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.


/////////////////////////////////////////////////////////////////////////////
// CWelcome dialog

class CWelcome : public CDialog
{
// Construction
public:
	CWelcome(CString APIFunc, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWelcome)
	enum { IDD = IDD_WELCOME };
	CEdit   m_Selected;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWelcome)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString m_strSelected;

	// Generated message map functions
	//{{AFX_MSG(CWelcome)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // __WELCOME_H__
