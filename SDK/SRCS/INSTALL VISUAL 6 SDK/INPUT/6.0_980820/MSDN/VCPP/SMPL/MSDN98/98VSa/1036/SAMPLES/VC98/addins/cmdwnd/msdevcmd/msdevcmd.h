// msdevcmd.h : main header file for the MSDEVCMD application
//

#if !defined(AFX_MSDEVCMD_H__B772028B_B6B0_11D1_8320_00A0C91BC942__INCLUDED_)
#define AFX_MSDEVCMD_H__B772028B_B6B0_11D1_8320_00A0C91BC942__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "devcmd.h"

//-------------------
// FORWARDS
class CCommandWindow;
class CMsdevcmdDlg;

/////////////////////////////////////////////////////////////////////////////
// CMsdevcmdApp:
// See msdevcmd.cpp for the implementation of this class
//

class CMsdevcmdApp : public CWinApp
{
public:
	CMsdevcmdApp();
	~CMsdevcmdApp();
	void SetCommandWindow(CCommandWindow *pCommandWindow);
	CCommandWindow *GetCmd(); // only derived dialog(s) should do this.

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMsdevcmdApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMsdevcmdApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	CMsdevcmdDlg * m_pDlgCommandWindow;
	CComPtr<ICommandWindow> m_pCommandWindow;
};

extern CMsdevcmdApp theApp;


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSDEVCMD_H__B772028B_B6B0_11D1_8320_00A0C91BC942__INCLUDED_)
