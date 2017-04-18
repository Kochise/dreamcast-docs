// GenPage.h : header file
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1997-1998 Microsoft Corporation
// All rights reserved.

/////////////////////////////////////////////////////////////////////////////
// CGenPage dialog

class CHttpSvrDoc;

class CGenPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CGenPage)

// Construction
public:
	 CGenPage( CHttpSvrDoc* pDoc );
	CHttpSvrDoc* m_pDoc;
	CGenPage();
	~CGenPage();

// Dialog Data
	//{{AFX_DATA(CGenPage)
	enum { IDD = IDD_GENPAGE };
	BOOL    m_bListIcon;
	BOOL    m_bAllowListing;
	BOOL    m_bLoggingOn;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CGenPage)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CGenPage)
	afx_msg void OnAllowList();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
