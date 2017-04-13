// msdevcmd.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "msdevcmd.h"
#include "msdevcmdDlg.h"
#include "CommandWindow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMsdevcmdApp
CComModule _Module;

class COleInit
{
public:
	COleInit()
	{
#if _WIN32_WINNT >= 0x0400 & defined(_ATL_FREE_THREADED)
		HRESULT hRes = CoInitializeEx(NULL, COINIT_MULTITHREADED);
#else
		HRESULT hRes = CoInitialize(NULL);
#endif
		_ASSERTE(SUCCEEDED(hRes));
	}

	~COleInit()
	{
		CoUninitialize();
	}
};


COleInit g_OleInit;

BEGIN_OBJECT_MAP(ObjectMap)
OBJECT_ENTRY(CLSID_CommandWindow, CCommandWindow)
END_OBJECT_MAP()

BEGIN_MESSAGE_MAP(CMsdevcmdApp, CWinApp)
	//{{AFX_MSG_MAP(CMsdevcmdApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMsdevcmdApp construction

CMsdevcmdApp::CMsdevcmdApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMsdevcmdApp object

CMsdevcmdApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMsdevcmdApp initialization

BOOL CMsdevcmdApp::InitInstance()
{
	HRESULT hr;

    _Module.Init(ObjectMap, m_hInstance, &LIBID_devcmdLib);

#ifdef _DEBUGOLE
	int iRes;
	iRes = AfxMessageBox(IDS_DEBUGBREAK, MB_YESNO, 0);
	if (iRes == IDYES)
		DebugBreak(); // do this so you can catch the process as it starts. It will bring up a MessageBox. Press Cancel to debug.
#endif

	CString strFile(m_lpCmdLine);
	BOOL fRun;

	fRun = TRUE;
	strFile.TrimLeft();
	if (!strFile.IsEmpty() && (strFile.GetAt(0) == _T('/') || strFile.GetAt(0) == _T('-')))
	{
		strFile = strFile.Mid(1); // get rid of switch command...
		if (strFile.CompareNoCase(_T("Regserver")) == 0)
		{
            _Module.UpdateRegistryFromResource(IDR_COMMANDWINDOW, TRUE);
            hr = _Module.RegisterServer(TRUE);
#ifdef FEEDBACK
			if (SUCCEEDED(hr))
			{
				AfxMessageBox(IDS_REGOK, MB_OK, 0);
			}
			else
			{
				AfxMessageBox(IDS_NOREG, MB_OK, 0);
			}
#endif
			fRun = FALSE;
		}
		else if (strFile.CompareNoCase(_T("Unregserver")) == 0)
		{
            _Module.UpdateRegistryFromResource(IDR_COMMANDWINDOW, FALSE);
            hr = _Module.UnregisterServer();

#if _WIN32_WINNT >= 0x0400
            hr = UnRegisterTypeLib(LIBID_CommandWindowXLib, 1, 0, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), SYS_WIN32);
#endif
			fRun = FALSE;
		}
		else if (strFile.CompareNoCase(_T("Embedded")) == 0)
		{
			// ignore command line.
			strFile.Empty();
		}
		else
		{
			strFile = m_lpCmdLine; // reset
		}
	}
	if (fRun)
	{
#if _WIN32_WINNT >= 0x0400 & defined(_ATL_FREE_THREADED)
        hr = _Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER, 
            REGCLS_MULTIPLEUSE | REGCLS_SUSPENDED);
        _ASSERTE(SUCCEEDED(hRes));
        hr = CoResumeClassObjects();
#else
        hr = _Module.RegisterClassObjects(CLSCTX_LOCAL_SERVER, 
            REGCLS_MULTIPLEUSE);
#endif
        _ASSERTE(SUCCEEDED(hr));

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

		m_pDlgCommandWindow = new CMsdevcmdDlg();
		m_pMainWnd = m_pDlgCommandWindow;
		int nResponse = m_pDlgCommandWindow->DoModal();
		if (nResponse == IDOK)
		{
			// TODO: Place code here to handle when the dialog is
			//  dismissed with OK
		}
		else if (nResponse == IDCANCEL)
		{
			// TODO: Place code here to handle when the dialog is
			//  dismissed with Cancel
		}
	}
	if (m_pCommandWindow)
	{
		m_pCommandWindow->DoFireClose();
		m_pCommandWindow.Release();
		m_pCommandWindow = NULL;
	}
    _Module.Term();

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

void CMsdevcmdApp::SetCommandWindow(CCommandWindow *pCommandWindow)
{
	if (m_pCommandWindow)
	{
		m_pCommandWindow.Release(); // don't have two!
	}
	m_pCommandWindow = pCommandWindow;
}

CCommandWindow *CMsdevcmdApp::GetCmd() // only derived dialog(s) should do this.
{
	HRESULT hr = S_OK;
	if (m_pCommandWindow == NULL)
	{
		CComObject<CCommandWindow> *pCommandWindow;
		
		hr = CComObject<CCommandWindow>::CreateInstance(&pCommandWindow);
		if (SUCCEEDED(hr) && pCommandWindow)
		{
			pCommandWindow->AddRef();
			hr = pCommandWindow->FindApp();
			m_pCommandWindow = pCommandWindow;
		}


	}
	return((CCommandWindow *)m_pCommandWindow.p);
}


CMsdevcmdApp::~CMsdevcmdApp()
{
	if (m_pCommandWindow)
	{
		m_pCommandWindow.Release();
	}
	if (m_pDlgCommandWindow)
	{
		delete m_pDlgCommandWindow;
	}
}

