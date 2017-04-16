// anim32.h : main header file for the ANIM32 application
//

#ifndef __AFXWIN_H__
    #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "dbgwnd.h"         // debug macros

/////////////////////////////////////////////////////////////////////////////
// CAnimApp:
// See anim32.cpp for the implementation of this class
//

class CAnimApp : public CWinApp
{
public:
    CAnimApp();

// Overrides
    virtual BOOL InitInstance();
    virtual int ExitInstance();
    virtual BOOL OnIdle(LONG lCount);

// Implementation
#ifdef _DEBUG
    CDbgWnd m_wndDbg;         // debug window
#endif // _DEBUG

    //{{AFX_MSG(CAnimApp)
    afx_msg void OnAppAbout();
        // NOTE - the ClassWizard will add and remove member functions here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
