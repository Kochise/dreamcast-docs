// MFCBind.h : main header file for the MFCBIND application
//

#if !defined(AFX_MFCBIND_H__CBD34997_B780_11D1_9580_0060088F4223__INCLUDED_)
#define AFX_MFCBIND_H__CBD34997_B780_11D1_9580_0060088F4223__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMFCBindApp:
// See MFCBind.cpp for the implementation of this class
//

class CMFCBindApp : public CWinApp
{
public:
	CMFCBindApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCBindApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMFCBindApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCBIND_H__CBD34997_B780_11D1_9580_0060088F4223__INCLUDED_)
