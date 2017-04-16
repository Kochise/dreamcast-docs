// dldetect.h : main header file for the DLDETECT application
//

#include "matrix.hpp"
#include "classes.h"

#include "mainfrm.h"
#include "pntdoc.h"
#include "netview.h"
#include "matview.h"
#include "invarian.h"


#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDldetectApp:
// See dldetect.cpp for the implementation of this class
//

class CDldetectApp : public CWinApp
{
public:
	CDldetectApp();

	CMultiDocTemplate *m_pMatrixTemplate, *m_pNetTemplate, *m_pInvTemplate;


// Overrides
	virtual BOOL InitInstance();

// Implementation

	//{{AFX_MSG(CDldetectApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CDldetectApp NEAR theApp;

/***************************************************************************/
/*                 SYMBOLIC CONSTANTS                                      */
/***************************************************************************/

#define IDM_FILEOPEN         100
#define IDM_FILENEW 		 101
#define IDM_FILESAVE		 102
#define IDM_NEWPLACE		 103
#define IDM_NEWTRANSITION	 104
#define IDM_CONVERTTOMATRIX	 105
#define IDM_FINDINVARIANTS	 106
#define IDM_LOCATEDEADLOCKS	 107
#define IDM_ENTERMARKING	 108
#define IDM_SIMULATE		 109
#define IDM_DETERMINE		 110

