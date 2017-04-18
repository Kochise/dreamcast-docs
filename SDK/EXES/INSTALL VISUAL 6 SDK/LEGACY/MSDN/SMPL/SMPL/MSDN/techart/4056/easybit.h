// EasyBit.h : main header file for the EASYBIT application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEasyBitApp:
// See EasyBit.cpp for the implementation of this class
//
class CSceneView;

class CEasyBitApp : public CWinApp
{
public:
	CEasyBitApp();
	//
	// OnIdle Support
	//
    CSceneView* m_pIdleView;
    void SetIdleEvent(CSceneView* pView)	//from Nigel's Animation library
        {m_pIdleView = pView;}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEasyBitApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL OnIdle(LONG lCount);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEasyBitApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
