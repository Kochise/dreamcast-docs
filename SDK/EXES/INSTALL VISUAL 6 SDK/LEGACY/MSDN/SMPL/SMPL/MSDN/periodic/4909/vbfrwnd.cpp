// VBFrWnd.cpp : implementation file
//

#include "stdafx.h"
#include "msjdrag.h"
#include "VBFrWnd.h"
#include "MSJDragCtl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVBFrameWnd

WNDPROC CVBFrameWnd::pfnSuperWndProc = NULL;

CVBFrameWnd::CVBFrameWnd()
{
}

CVBFrameWnd::~CVBFrameWnd()
{
}


BEGIN_MESSAGE_MAP(CVBFrameWnd, CWnd)
	//{{AFX_MSG_MAP(CVBFrameWnd)
	ON_WM_DROPFILES()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CVBFrameWnd message handlers

void CVBFrameWnd::OnDropFiles(HDROP hDropInfo) 
{
	char lpszFile[128];
	UINT numFiles;

	numFiles = 	DragQueryFile(hDropInfo, 0xFFFF, NULL, 0);

	::DragQueryFile(hDropInfo, 0, lpszFile, 127);
	::DragFinish(hDropInfo);
	m_ctrlwnd->FireFileDrop((OLE_HANDLE) m_hWnd, (LPCTSTR) lpszFile);
	
	CWnd::OnDropFiles(hDropInfo);
}
