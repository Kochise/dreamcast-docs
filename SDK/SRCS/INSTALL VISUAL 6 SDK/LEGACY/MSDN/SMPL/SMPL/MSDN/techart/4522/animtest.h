// animtest.h : main header file for the ANIMTEST application
//

#ifndef __AFXWIN_H__
    #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CAnimTestApp:
// See animtest.cpp for the implementation of this class
//

class CAnimTestView;

class CAnimTestApp : public CWinApp
{
public:
    CAnimTestApp();
    void SetIdleView(CAnimTestView* pView)
        {m_pIdleView = pView;}

// Overrides
    virtual BOOL InitInstance();
    virtual BOOL OnIdle(LONG lCount);

// Implementation
private:
    CAnimTestView* m_pIdleView;

    //{{AFX_MSG(CAnimTestApp)
    afx_msg void OnAppAbout();
        // NOTE - the ClassWizard will add and remove member functions here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};

extern CAnimTestApp theApp;
/////////////////////////////////////////////////////////////////////////////
