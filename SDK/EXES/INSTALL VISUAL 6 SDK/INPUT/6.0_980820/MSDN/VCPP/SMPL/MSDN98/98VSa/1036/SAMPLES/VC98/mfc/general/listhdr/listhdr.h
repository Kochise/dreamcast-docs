// ListHdr.h : main header file for the ListHdr application
//

#if !defined(AFX_ListHdr_H__31281826_D350_11D0_8286_00C04FD73634__INCLUDED_)
#define AFX_ListHdr_H__31281826_D350_11D0_8286_00C04FD73634__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CListHdrApp:
// See ListHdr.cpp for the implementation of this class
//

class CListHdrApp : public CWinApp
{
public:
	CListHdrApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListHdrApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CListHdrApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ListHdr_H__31281826_D350_11D0_8286_00C04FD73634__INCLUDED_)
