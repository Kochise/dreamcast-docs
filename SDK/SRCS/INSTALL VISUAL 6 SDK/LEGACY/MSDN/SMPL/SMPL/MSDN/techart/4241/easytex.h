// EasyTex.h : main header file for the EASYTEX application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEasyTexApp:
// See EasyTex.cpp for the implementation of this class
//
class CSceneView;

class CEasyTexApp : public CWinApp
{
public:
	CEasyTexApp();

 	//
	// OnIdle Support
	//
    CSceneView* m_pIdleView;
    void SetIdleEvent(CSceneView* pView)	//from Nigel's Animation library
        {m_pIdleView = pView;}


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEasyTexApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL OnIdle(LONG lCount);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEasyTexApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
