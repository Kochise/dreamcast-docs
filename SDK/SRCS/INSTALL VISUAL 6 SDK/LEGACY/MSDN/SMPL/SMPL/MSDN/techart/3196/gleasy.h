// gleasy.h : main header file for the GLEASY application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGLEasyApp:
// See gleasy.cpp for the implementation of this class
//
class CGLEasyView ;

class CGLEasyApp : public CWinApp
{
public:
	CGLEasyApp();
	//
	// OnIdle Support
	//
    CGLEasyView* m_pIdleView;
    void SetIdleEvent(CGLEasyView* pView)	//from Nigel's Animation library
        {m_pIdleView = pView;}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGLEasyApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL OnIdle(LONG lCount);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGLEasyApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
