// crsform.h : header file
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1998 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

/////////////////////////////////////////////////////////////////////////////
// CCourseForm record view

class CCourseForm : public CAddForm
{
	DECLARE_DYNCREATE(CCourseForm)
public:
	CCourseForm();          // protected constructor used by dynamic creation

// Form Data
public:
	//{{AFX_DATA(CCourseForm)
	enum { IDD = IDD_COURSE_FORM };
	CEdit   m_ctlCourseID;
	CCourseSet* m_pSet;
	//}}AFX_DATA

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CSectionForm)
	public:
	virtual CDaoRecordset* OnGetRecordset();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnMove(UINT nIDMoveCommand);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CCourseForm();

	// Generated message map functions
	//{{AFX_MSG(CCourseForm)
	afx_msg void OnRecordAdd();
	afx_msg void OnRecordDelete();
	afx_msg void OnRecordRefresh();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
