// usreditc.h : header file
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
// CUsrEditClass window
#ifndef __USREDIT__
#define __USREDIT__

class CUsrEditClass : public CEdit
{
// Construction
public:
	CUsrEditClass();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUsrEditClass)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CUsrEditClass();
	// Generated message map functions
protected:
	//{{AFX_MSG(CUsrEditClass)
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#endif //__USREDIT__
/////////////////////////////////////////////////////////////////////////////
