// $$root$$.h : main header file for the TBASIC application
//

#if !defined(AFX_TBASIC_H__4201C6E7_B268_11D0_88D2_00C04FD235A5__INCLUDED_)
#define AFX_TBASIC_H__4201C6E7_B268_11D0_88D2_00C04FD235A5__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// C$$root$$App:
// See $$root$$.cpp for the implementation of this class
//

class C$$root$$App : public CWinApp
{
public:
	C$$root$$App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C$$root$$App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(C$$root$$App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TBASIC_H__4201C6E7_B268_11D0_88D2_00C04FD235A5__INCLUDED_)
