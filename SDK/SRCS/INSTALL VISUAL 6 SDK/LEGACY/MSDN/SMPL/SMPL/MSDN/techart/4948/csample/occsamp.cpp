// OCCSamp.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "winreg.h"
#include "OCCSamp.h"
#include "winnls.h"

#include "MainFrm.h"
#include "OCCDoc.h"
#include "OCCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COCCSampApp

BEGIN_MESSAGE_MAP(COCCSampApp, CWinApp)
	//{{AFX_MSG_MAP(COCCSampApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_TOOLS_AUTOCORRECT, OnToolsAutocorrect)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COCCSampApp construction

COCCSampApp::COCCSampApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only COCCSampApp object

COCCSampApp theApp;

/////////////////////////////////////////////////////////////////////////////
// LoadOffice

#define MSOC97DLL _T("msoc.dll")

/////////////////////////////////////////////////////////////////////////////
// COCCSampApp initialization

BOOL COCCSampApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(COCCSampDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(COCCSampView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	LoadOfficeCompatible();

#ifdef _MAC
	// Enable drag/drop open.  We don't call this in Win32, since a
	//  document file extension wasn't chosen while running AppWizard.
	m_pMainWnd->DragAcceptFiles();
#endif

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void COCCSampApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// COCCSampApp commands


#ifndef UNICODE
LPCSTR ConvertToAnsi(LPCWSTR szW)
{
  static char achA[256]; 
  
  WideCharToMultiByte(CP_ACP, 0, szW, -1, achA, sizeof(achA), NULL, NULL);  
  return achA; 
} 

LPCWSTR ConvertToUnicode(LPCSTR szA)
{
  static OLECHAR achW[256]; 

  MultiByteToWideChar(CP_ACP, 0, szA, -1, achW, sizeof(achW));  
  return achW; 
}
#endif

int COCCSampApp::ExitInstance() 
{

	UnloadOfficeCompatible();

	return CWinApp::ExitInstance();
}

IOfficeCompatible *vpOC = NULL;

void COCCSampApp::UnloadOfficeCompatible()
{
	if (vpOC != NULL)
	{
		vpOC->Release();
		vpOC = NULL;
	}

	if (m_hinstOC != NULL)
	{
		FreeLibrary(m_hinstOC);
		m_hinstOC = NULL;
	}
}

void COCCSampApp::LoadOfficeCompatible()
{
	LPCWSTR pszAppName = ConvertToUnicode(AfxGetApp()->m_pszAppName);
	LPCWSTR pszExeName = ConvertToUnicode(AfxGetApp()->m_pszExeName);

	vpOC = NULL;
	
	// Find Msoc.dll
	HKEY hkResult;
	char szDLLPath[MAX_PATH];

	szDLLPath[0] = 0;
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Shared Tools\\msoc.dll", 
		0, KEY_READ, &hkResult) == ERROR_SUCCESS)
	{
		DWORD cchPath = MAX_PATH;

		if (RegQueryValueEx(hkResult, (LPSTR) "Path", NULL, NULL, 
				(LPBYTE)szDLLPath, &cchPath) != ERROR_SUCCESS)
		{
			szDLLPath[0] = 0;
		}
		
		RegCloseKey(hkResult);
	}

	// Try to load msoc.dll from the directory specified by registry setting
	if ((m_hinstOC = LoadLibrary(szDLLPath)) == NULL)
	{
		// Try to find msoc.dll on the path
		if ((m_hinstOC = LoadLibrary(MSOC97DLL)) == NULL)
			return; // failed to load library
	}

	HRESULT (__stdcall *pfnCreateOfficeCompatible)(LPCWSTR, LPCWSTR, IOfficeCompatible**);

	pfnCreateOfficeCompatible = 
		(HRESULT (__stdcall *)(LPCWSTR, LPCWSTR, IOfficeCompatible**)) 
		GetProcAddress(m_hinstOC, "_CreateOfficeCompatible@12");

	if (pfnCreateOfficeCompatible == NULL)
		goto error;
	
	if (FAILED(pfnCreateOfficeCompatible(pszAppName, pszExeName, &vpOC)))
	{
error:
		FreeLibrary(m_hinstOC);
		m_hinstOC = NULL;
		vpOC = NULL;
		return;
	}
}

void COCCSampApp::OnToolsAutocorrect() 
{
	if (vpOC == NULL)
		return;

	IMsocAutoCorrect *pAutoCorrect = vpOC->PiacGetAutoCorrect();

	if (pAutoCorrect != NULL)
		pAutoCorrect->ShowDialog(AfxGetMainWnd()->m_hWnd);
}
