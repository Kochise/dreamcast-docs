// ddlist.h : main header file for the DDLIST application
//

#ifndef __AFXWIN_H__
    #error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDdlistApp:
// See ddlist.cpp for the implementation of this class
//

class CDdlistApp : public CWinApp
{
public:
    CDdlistApp();

// Overrides
    virtual BOOL InitInstance();

// Implementation
public:
    UINT m_uiStrListClipFormat;

    //{{AFX_MSG(CDdlistApp)
    afx_msg void OnAppAbout();
        // NOTE - the ClassWizard will add and remove member functions here.
        //    DO NOT EDIT what you see in these blocks of generated code !
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

extern CDdlistApp NEAR theApp;
