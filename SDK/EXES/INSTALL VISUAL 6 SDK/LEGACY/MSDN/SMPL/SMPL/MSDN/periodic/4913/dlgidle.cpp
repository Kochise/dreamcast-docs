////////////////////////////////////////////////////////////////
// DLGIDLE Copyright 1996 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
// DLGIDLE illustrates how to implement a dialog-based app that
// does OnIdle processing. Compiles with VC++ 4.0 or greater.

#include "stdafx.h"
#include "resource.h"
#include "tracewin.h"
#include <afxpriv.h>		// For WM_KICKIDLE

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////////////////////////////////////////////////////
// Dialog class
//
class CMyDlg : public CDialog {
public:
	CMyDlg() : CDialog(IDD_ABOUTBOX) {	}
	afx_msg LRESULT OnKickIdle(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CMyDlg, CDialog)
	ON_MESSAGE(WM_KICKIDLE, OnKickIdle)
END_MESSAGE_MAP()

//////////////////
// Handle MFC private message WM_KICKIDLE. LPARAM is the idle count. 
// Return TRUE/FALSE continue/discontinue idle processing.
//
LRESULT CMyDlg::OnKickIdle(WPARAM, LPARAM lCount)
{
	// Do idle processing here, just like CWinApp::OnIdle
	//
	TRACE("CMyDlg::OnKickIdle, do priority %d stuff\n", lCount);
	return (lCount <= 2);
}

////////////////////////////////////////////////////////////////
// Application class with OnIdle function.
//
class CMyApp : public CWinApp {
public:
	CMyApp();
	virtual BOOL InitInstance();
	DECLARE_MESSAGE_MAP()
};

CMyApp NEAR theApp;

BEGIN_MESSAGE_MAP(CMyApp, CWinApp)
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

CMyApp::CMyApp()
{
}

BOOL CMyApp::InitInstance()
{
	MfxTraceInit();
	CMyDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();
	return FALSE;
}


