// OCCSamp.h : main header file for the OCCSAMP application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "msoc97.h"

extern IOfficeCompatible *vpOC; // Main Office Compatible Interface

// Forward References
LPCSTR ConvertToAnsi(LPCWSTR szW);
LPCWSTR ConvertToUnicode(LPCSTR szA);

/////////////////////////////////////////////////////////////////////////////
// COCCSampApp:
// See OCCSamp.cpp for the implementation of this class
//

class COCCSampApp : public CWinApp
{
public:
	void LoadOfficeCompatible();
	void UnloadOfficeCompatible();
	HINSTANCE m_hinstOC;
	IOfficeCompatible *m_pOC;
	COCCSampApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COCCSampApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(COCCSampApp)
	afx_msg void OnAppAbout();
	afx_msg void OnToolsAutocorrect();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
