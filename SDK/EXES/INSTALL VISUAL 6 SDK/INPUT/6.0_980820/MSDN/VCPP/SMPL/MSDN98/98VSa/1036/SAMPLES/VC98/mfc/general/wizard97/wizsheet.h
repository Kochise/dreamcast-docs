// WizSheet.h : header file
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

#if !defined(AFX_SAMPWIZP_H__99E7B18F_4A5C_11D1_BF2C_00C04FC99F83__INCLUDED_)
#define AFX_SAMPWIZP_H__99E7B18F_4A5C_11D1_BF2C_00C04FC99F83__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IntroPg.h"
#include "Int1.h"
#include "Int2.h"
#include "Complete.h"

/////////////////////////////////////////////////////////////////////////////
// CWizard97Sheet

class CWizard97Sheet : public CPropertySheetEx
{
	DECLARE_DYNAMIC(CWizard97Sheet)

// Construction
public:
	CWizard97Sheet(UINT nIDCaption, CWnd* pParentWnd = NULL,
			UINT iSelectPage = 0, HBITMAP hbmWatermark = NULL,
			HPALETTE hpalWatermark = NULL, HBITMAP hbmHeader = NULL);
	CWizard97Sheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL,
			UINT iSelectPage = 0, HBITMAP hbmWatermark = NULL,
			HPALETTE hpalWatermark = NULL, HBITMAP hbmHeader = NULL);

// Attributes
public:
	CIntroPage m_Intro;
	CInterior1 m_Interior1;
	CInterior2 m_Interior2;
	CCompletion m_Completion;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWizard97Sheet)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CWizard97Sheet();

	// Generated message map functions
protected:
	//{{AFX_MSG(CWizard97Sheet)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SAMPWIZP_H__99E7B18F_4A5C_11D1_BF2C_00C04FC99F83__INCLUDED_)
