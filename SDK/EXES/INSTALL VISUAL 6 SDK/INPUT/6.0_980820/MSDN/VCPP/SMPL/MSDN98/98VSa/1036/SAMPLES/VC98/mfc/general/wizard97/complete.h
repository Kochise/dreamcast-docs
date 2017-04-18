// Completion.h : header file
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

#if !defined(AFX_COMPLETION_H__99E7B195_4A5C_11D1_BF2C_00C04FC99F83__INCLUDED_)
#define AFX_COMPLETION_H__99E7B195_4A5C_11D1_BF2C_00C04FC99F83__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCompletion dialog

class CCompletion : public CPropertyPageEx
{
	DECLARE_DYNCREATE(CCompletion)

// Construction
public:
	CCompletion();
	~CCompletion();

// Dialog Data
	//{{AFX_DATA(CCompletion)
	enum { IDD = IDD_COMPLETION_NEW };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CCompletion)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CCompletion)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMPLETION_H__99E7B195_4A5C_11D1_BF2C_00C04FC99F83__INCLUDED_)
