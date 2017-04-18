// viewfile.h : main header file for the VIEWFILE application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CViewfileApp:
// See viewfile.cpp for the implementation of this class
//

class CPViewDoc;   // forward declaration

class CViewfileApp : public CWinApp
{

// friend class CViewFileDoc;
private:

CPViewDoc *m_ProcessList;


public:

CMultiDocTemplate* m_pRawTemplate;
CMultiDocTemplate* m_pDOSTemplate;
CMultiDocTemplate* m_pNETemplate;
CMultiDocTemplate* m_pLETemplate;
CMultiDocTemplate* m_pPETemplate;
//CMultiDocTemplate* m_pCustomTemplate;
CMultiDocTemplate* m_pPViewTemplate;


public:
	CViewfileApp();

	void SetStatusBarText(char *szText);
	void RefreshProcessList();


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewfileApp)
	public:
	virtual BOOL InitInstance();
	virtual CDocument* OpenDocumentFile(LPCTSTR lpszFileName);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CViewfileApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
