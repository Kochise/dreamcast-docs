//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This source code is a part of BCGControlBar library.
// You may use, compile or redistribute it as part of your application 
// for free. You cannot redistribute it as a part of a software development 
// library without the agreement of the author. If the sources are 
// distributed along with the application, you should leave the original 
// copyright notes in the source code without any changes.
// This code can be used WITHOUT ANY WARRANTIES on your own risk.
// 
// For the latest updates to this library, check my site:
// http://welcome.to/bcgsoft
// 
// Stas Levin <bcgsoft@yahoo.com>
//*******************************************************************************

#if !defined(AFX_BCGMAINCLIENTAREAWND_H__08B9EC05_DCE3_11D1_A64F_00A0C93A70EC__INCLUDED_)
#define AFX_BCGMAINCLIENTAREAWND_H__08B9EC05_DCE3_11D1_A64F_00A0C93A70EC__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// BCGMainClientAreaWnd.h : header file
//

#include "bcgcontrolbar.h"

class CBCGMDIFrameWnd;

/////////////////////////////////////////////////////////////////////////////
// CBCGMainClientAreaWnd window

class BCGCONTROLBARDLLEXPORT CBCGMainClientAreaWnd : public CWnd
{
// Construction
public:
	CBCGMainClientAreaWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBCGMainClientAreaWnd)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBCGMainClientAreaWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CBCGMainClientAreaWnd)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	afx_msg LRESULT OnSetMenu (WPARAM wp, LPARAM);
	afx_msg LRESULT OnMDIRefreshMenu (WPARAM wp, LPARAM);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGMAINCLIENTAREAWND_H__08B9EC05_DCE3_11D1_A64F_00A0C93A70EC__INCLUDED_)
