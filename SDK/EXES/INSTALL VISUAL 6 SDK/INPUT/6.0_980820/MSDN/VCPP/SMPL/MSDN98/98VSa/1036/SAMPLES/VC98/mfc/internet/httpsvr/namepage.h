// NamePage.h : interface of the CNamePage class
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1997-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

/////////////////////////////////////////////////////////////////////////////
// CNamePage dialog

class CHttpSvrDoc;

class CNamePage : public CPropertyPage
{
	DECLARE_DYNCREATE(CNamePage)

// Construction
public:
	 CNamePage( CHttpSvrDoc* pDoc );
	CHttpSvrDoc* m_pDoc;
	CNamePage();
	~CNamePage();

// Dialog Data
	//{{AFX_DATA(CNamePage)
	enum { IDD = IDD_NAMEPAGE };
	CString m_strName;
	int     m_nNameSetting;
	UINT    m_uPort;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CNamePage)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CNamePage)
	virtual BOOL OnInitDialog();
	afx_msg void OnDefName();
	afx_msg void OnUseName();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
