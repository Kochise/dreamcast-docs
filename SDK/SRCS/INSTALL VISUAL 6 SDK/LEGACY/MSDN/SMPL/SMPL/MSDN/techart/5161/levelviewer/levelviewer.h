// LevelViewer.h : main header file for the LEVELVIEWER application
//

#if !defined(AFX_LEVELVIEWER_H__7423445C_F528_11D0_A980_0020182A7050__INCLUDED_)
#define AFX_LEVELVIEWER_H__7423445C_F528_11D0_A980_0020182A7050__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CLevelViewerApp:
// See LevelViewer.cpp for the implementation of this class
//

class CLevelViewerApp : public CWinApp
{
public:
	CLevelViewerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLevelViewerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CLevelViewerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEVELVIEWER_H__7423445C_F528_11D0_A980_0020182A7050__INCLUDED_)
