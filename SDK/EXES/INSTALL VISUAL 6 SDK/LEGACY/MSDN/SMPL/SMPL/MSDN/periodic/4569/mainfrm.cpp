////////////////////////////////////////////////////////////////
// Main frame window for TRACEWIN applet
//
#include "stdafx.h"
#include "app.h"
#include "mainfrm.h"
#include "tracewin.h"
#include <direct.h>

// Registry key for profile settings
//
const char PROFILE[] = "Settings";

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_MESSAGE(WM_COPYDATA, OnTraceMsg)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()

	ON_COMMAND(ID_FILE_SAVE_AS,					OnFileSaveAs)
	ON_COMMAND(ID_OUTPUT_OFF,						OnOutputOff)
	ON_COMMAND(ID_OUTPUT_TO_FILE,					OnOutputToFile)
	ON_COMMAND(ID_OUTPUT_TO_WINDOW,				OnOutputToWindow)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS,		OnUpdateFileSaveAs)
	ON_UPDATE_COMMAND_UI(ID_OUTPUT_OFF,			OnUpdateOutputOff)
	ON_UPDATE_COMMAND_UI(ID_OUTPUT_TO_FILE,	OnUpdateOutputToFile)
	ON_UPDATE_COMMAND_UI(ID_OUTPUT_TO_WINDOW, OnUpdateOutputToWindow)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CMainFrame::CMainFrame() 
{
	// Load state from profile
	m_nOutputWhere = ID_OUTPUT_TO_WINDOW;
	CString dir = AfxGetApp()->GetProfileString(PROFILE,"Directory");
	if (!dir.IsEmpty())
		_chdir(dir);
}

CMainFrame::~CMainFrame()
{
}

/////////////////
// Override pre-create function to use "MfxTraceWindow" as 
// class name so applications can find us.
//
BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	static LPCSTR className = NULL;

	if (!CFrameWnd::PreCreateWindow(cs))
		return FALSE;

	if (className==NULL) {
		// One-time class registration
		// The only purpose is to make the class name something meaningful
		// instead of "Afx:0x4d:27:32:hup1hup:hike!"
		//
		WNDCLASS wndcls;
		::GetClassInfo(AfxGetInstanceHandle(), cs.lpszClass, &wndcls);
		wndcls.lpszClassName = TRACEWND_CLASSNAME;
		wndcls.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
		VERIFY(AfxRegisterClass(&wndcls));
		className=TRACEWND_CLASSNAME;
	}
	cs.lpszClass = className;

	// Load window position from profile
	CWinApp *pApp = AfxGetApp();
	cs.x = pApp->GetProfileInt(PROFILE, "x", CW_USEDEFAULT);
	cs.y = pApp->GetProfileInt(PROFILE, "y", CW_USEDEFAULT);
	cs.cx = pApp->GetProfileInt(PROFILE, "cx", CW_USEDEFAULT);
	cs.cy = pApp->GetProfileInt(PROFILE, "cy", CW_USEDEFAULT);

	return TRUE;
}

//////////////////
// Main frame created.
//
int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Create buffer window
	if (!m_wndBuffer.Create(this, AFX_IDW_PANE_FIRST)) {
		TRACE("Failed to create buffer window\n");
		return -1;      // fail to create
	}
	TRACE("Created TRACE Window.\n");
	return 0;
}

//////////////////
// If I get focus, give to buffer
//
void CMainFrame::OnSetFocus(CWnd* pOldWnd)
{
	m_wndBuffer.SetFocus();
}

//////////////////
// Got command message: pass to trace buffer
// Without this, m_wndBuffer doesn't get a chance to handle 
// menu commands with ON_COMMAND, etc.
//
BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra,
	AFX_CMDHANDLERINFO* pHandlerInfo)
{
	if (m_wndBuffer.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;	// handled by buffer window

	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

//////////////////
// Someone sent me a WM_COPYDATA message: display it
//
LRESULT CMainFrame::OnTraceMsg(WPARAM wParam, LPARAM lParam)
{
	COPYDATASTRUCT* pcds = (COPYDATASTRUCT*)lParam;
	if (m_nOutputWhere==ID_OUTPUT_OFF || pcds->dwData!=ID_COPYDATA_TRACEMSG)
		return 0;

	const char* lpText = (const char*)pcds->lpData;
	DWORD len = pcds->cbData;

	if (m_nOutputWhere==ID_OUTPUT_TO_WINDOW) {
		// Convert \n to \n\r for Windows brain-damaged edit control
		// It's 1995, and I'm still writing code like this!
		//
		const char* src = lpText;
		const char* endsrc = lpText + len;

		char buf[1024];
		char* dst = buf;
		char* endbuf = buf + sizeof(buf) - 1;

		while (src < endsrc && dst < endbuf) {
			if (*src == '\n')
				*dst++ = '\r';
			*dst++ = *src++;
		}
		*dst = 0;

		// Append string to contents of trace buffer
		m_wndBuffer.SetSel(-1, -1);		// end of edit text
		m_wndBuffer.ReplaceSel(buf);		// append string..
		m_wndBuffer.SendMessage(EM_SCROLLCARET);	// ..and show caret

	} else if (m_nOutputWhere==ID_OUTPUT_TO_FILE) {
		m_file.Write(lpText, len);

	}

	return 0;
}

//////////////////
// Save contents of trace buffer to a file
//
void CMainFrame::OnFileSaveAs() 
{
	CFileDialog dlg(FALSE);
	if (dlg.DoModal()!=IDOK) 
		return;

	CFile f;
	if (OpenFile(f, dlg.GetPathName())) {
		char buf[256];
		int count = m_wndBuffer.GetLineCount();
		for (int line=0; line<count; line++) {
			int len = m_wndBuffer.GetLine(line, buf, sizeof(buf)-1);
			buf[len++]='\n';
			f.Write(buf, len);
		}
		f.Close();
	}
}

//////////////////
// Helper to open a file
//
BOOL CMainFrame::OpenFile(CFile& f, LPCSTR lpszPathName)
{
	BOOL bOpen = FALSE;
	TRY {
		bOpen = f.Open(lpszPathName,
			CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite);

	} CATCH_ALL(e) {
	} END_CATCH_ALL

	if (!bOpen) {
		MessageBox("Failed to open file.","TRACEWIN", MB_OK|MB_ICONEXCLAMATION);
		MessageBeep(MB_ICONEXCLAMATION);
	}

	return bOpen;
}

void CMainFrame::CloseTraceFile()
{
	if (m_file.m_hFile != CFile::hFileNull)
		m_file.Close();
}

void CMainFrame::OnUpdateFileSaveAs(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!m_wndBuffer.IsEmpty());
}

void CMainFrame::OnOutputOff() 
{
	CloseTraceFile();
	m_nOutputWhere = ID_OUTPUT_OFF;
}

void CMainFrame::OnUpdateOutputOff(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(m_nOutputWhere==ID_OUTPUT_OFF);
}

void CMainFrame::OnOutputToFile() 
{
	CFileDialog dlg(TRUE);
	dlg.m_ofn.lpstrTitle = "Output to File";
	if (dlg.DoModal()!=IDOK) 
		return;

	CloseTraceFile();
	if (OpenFile(m_file, dlg.GetPathName()))
		m_nOutputWhere = ID_OUTPUT_TO_FILE;
}

void CMainFrame::OnUpdateOutputToFile(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(m_nOutputWhere==ID_OUTPUT_TO_FILE);
}

void CMainFrame::OnOutputToWindow() 
{
	CloseTraceFile();
	m_nOutputWhere = ID_OUTPUT_TO_WINDOW;
}

void CMainFrame::OnUpdateOutputToWindow(CCmdUI* pCmdUI) 
{
	pCmdUI->SetRadio(m_nOutputWhere==ID_OUTPUT_TO_WINDOW);
}

//////////////////
// Frame window closed: save position, size in profile.
//
void CMainFrame::OnClose() 
{
	SaveSettings();
	CFrameWnd::OnClose();
}

//////////////////
// Save window pos, etc. in registration file.
//
void CMainFrame::SaveSettings()
{
	CRect rc;
	GetWindowRect(&rc);
	
	CWinApp *pApp = AfxGetApp();
	pApp->WriteProfileInt(PROFILE, "x", rc.left);
	pApp->WriteProfileInt(PROFILE, "y", rc.top);
	pApp->WriteProfileInt(PROFILE, "cx", rc.Width());
	pApp->WriteProfileInt(PROFILE, "cy", rc.Height());
	pApp->WriteProfileInt(PROFILE, "TraceWhere", m_nOutputWhere);

	char buf[_MAX_PATH];
	_getcwd(buf, sizeof(buf));
	pApp->WriteProfileString(PROFILE, "Directory", buf);
}
