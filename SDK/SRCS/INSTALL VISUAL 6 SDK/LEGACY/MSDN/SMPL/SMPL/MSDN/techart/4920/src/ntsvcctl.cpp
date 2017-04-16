// NtSvcCtl.cpp : Implementation of the CNtSvcCtrl OLE control class.

#include "stdafx.h"
#include "NtSvc.h"
#include "NtSvcCtl.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CNtSvcCtrl, COleControl)

// private window messages
#define CWM_START   WM_USER+10
#define CWM_HANDLER	WM_USER+11

/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CNtSvcCtrl, COleControl)
	//{{AFX_MSG_MAP(CNtSvcCtrl)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	ON_MESSAGE(CWM_START, OnStart)
	ON_MESSAGE(CWM_HANDLER, OnHandler)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CNtSvcCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CNtSvcCtrl)
	DISP_PROPERTY_NOTIFY(CNtSvcCtrl, "Account", m_account, OnAccountChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY(CNtSvcCtrl, "ControlsAccepted", m_controlsAccepted, OnControlsAcceptedChanged, VT_I4)
	DISP_PROPERTY_NOTIFY(CNtSvcCtrl, "LoadOrderGroup", m_LoadOrderGroup, OnLoadOrderGroupChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY(CNtSvcCtrl, "Dependencies", m_Dependencies, OnDependenciesChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY(CNtSvcCtrl, "DisplayName", m_displayName, OnDisplayNameChanged, VT_BSTR)
	DISP_PROPERTY_NOTIFY(CNtSvcCtrl, "Interactive", m_interactive, OnInteractiveChanged, VT_BOOL)
	DISP_PROPERTY_NOTIFY(CNtSvcCtrl, "Password", m_password, OnPasswordChanged, VT_BSTR)
	DISP_PROPERTY_EX(CNtSvcCtrl, "Debug", GetDebug, SetDebug, VT_BOOL)
	DISP_PROPERTY_EX(CNtSvcCtrl, "ServiceName", GetServiceName, SetServiceName, VT_BSTR)
	DISP_PROPERTY_EX(CNtSvcCtrl, "StartMode", GetStartMode, SetStartMode, VT_I2)
	DISP_FUNCTION(CNtSvcCtrl, "Install", Install, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CNtSvcCtrl, "LogEvent", LogEvent, VT_BOOL, VTS_I2 VTS_I4 VTS_BSTR)
	DISP_FUNCTION(CNtSvcCtrl, "Running", Running, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CNtSvcCtrl, "Uninstall", Uninstall, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CNtSvcCtrl, "StopService", StopService, VT_EMPTY, VTS_NONE)
	DISP_FUNCTION(CNtSvcCtrl, "StartService", StartService, VT_BOOL, VTS_NONE)
	DISP_FUNCTION(CNtSvcCtrl, "GetAllSettings", GetAllSettings, VT_VARIANT, VTS_BSTR)
	DISP_FUNCTION(CNtSvcCtrl, "SaveSetting", SaveSetting, VT_EMPTY, VTS_BSTR VTS_BSTR VTS_BSTR)
	DISP_FUNCTION(CNtSvcCtrl, "DeleteSetting", DeleteSetting, VT_EMPTY, VTS_BSTR VTS_VARIANT)
	DISP_FUNCTION(CNtSvcCtrl, "GetSetting", GetSetting, VT_BSTR, VTS_BSTR VTS_BSTR VTS_VARIANT)
	DISP_DEFVALUE(CNtSvcCtrl, "DisplayName")
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CNtSvcCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CNtSvcCtrl, COleControl)
	//{{AFX_EVENT_MAP(CNtSvcCtrl)
	EVENT_CUSTOM("Continue", FireContinue, VTS_PBOOL)
	EVENT_CUSTOM("Control", FireControl, VTS_I4)
	EVENT_CUSTOM("Pause", FirePause, VTS_PBOOL)
	EVENT_CUSTOM("Start", FireStart, VTS_PBOOL)
	EVENT_CUSTOM("Stop", FireStop, VTS_NONE)
	//}}AFX_EVENT_MAP
END_EVENT_MAP()



/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CNtSvcCtrl, "NTService.Control.1",
	0xe7bc34a3, 0xba86, 0x11cf, 0x84, 0xb1, 0xcb, 0xc2, 0xda, 0x68, 0xbf, 0x6c)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CNtSvcCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DNtSvc =
		{ 0xe7bc34a1, 0xba86, 0x11cf, { 0x84, 0xb1, 0xcb, 0xc2, 0xda, 0x68, 0xbf, 0x6c } };
const IID BASED_CODE IID_DNtSvcEvents =
		{ 0xe7bc34a2, 0xba86, 0x11cf, { 0x84, 0xb1, 0xcb, 0xc2, 0xda, 0x68, 0xbf, 0x6c } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

static const DWORD BASED_CODE _dwNtSvcOleMisc =
	OLEMISC_INVISIBLEATRUNTIME |	// control has no GUI
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_SIMPLEFRAME |			// Guarantees that the control window exists and messages can be posted
	OLEMISC_ALWAYSRUN |				// The control generates events without being visible
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE /* |
	OLEMISC_RECOMPOSEONRESIZE */	// Disabled because control doesn't resize
	;

IMPLEMENT_OLECTLTYPE(CNtSvcCtrl, IDS_NTSVC, _dwNtSvcOleMisc)


class CNtSvcCtrl* CNtSvcCtrl::m_pThis;


/////////////////////////////////////////////////////////////////////////////
// CNtSvcCtrl::CNtSvcCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CNtSvcCtrl

BOOL CNtSvcCtrl::CNtSvcCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_NTSVC,
			IDB_NTSVC,
			FALSE,                      //  Not insertable
			_dwNtSvcOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// Helper painting functions
//
static void CreateMask(CBitmap *pbmp, CBitmap *pbmpMask)
{
	BITMAP bmp;
	pbmp->GetObject(sizeof (BITMAP), &bmp);
	pbmpMask->CreateBitmap(bmp.bmWidth, bmp.bmHeight, 1, 1, NULL);

	CDC dcDst;
	dcDst.CreateCompatibleDC(NULL);
	CDC dcSrc;
	dcSrc.CreateCompatibleDC(NULL);
	CBitmap* pbmpSaveDst = dcDst.SelectObject(pbmpMask);
	CBitmap* pbmpSaveSrc = dcSrc.SelectObject(pbmp);

	COLORREF oldBkColor = dcSrc.SetBkColor(dcSrc.GetPixel(0, 0));
	dcDst.BitBlt(0, 0, bmp.bmWidth, bmp.bmHeight, &dcSrc, 0, 0, NOTSRCCOPY);
	dcSrc.SetBkColor(oldBkColor);
}

#define DSx     0x00660046L
#define DSna    0x00220326L

static void DrawMaskedBitmap(CDC* pDC, CBitmap* pbmp, CBitmap* pbmpMask,
	int x, int y, int cx, int cy)
{
	COLORREF oldBkColor = pDC->SetBkColor(RGB(255, 255, 255));
	COLORREF oldTextColor = pDC->SetTextColor(RGB(0, 0, 0));

	CDC dcCompat;
	dcCompat.CreateCompatibleDC(pDC);
	CBitmap* pbmpSave = dcCompat.SelectObject(pbmp);
	pDC->BitBlt(x, y, cx, cy, &dcCompat, 0, 0, DSx);
	dcCompat.SelectObject(pbmpMask);
	pDC->BitBlt(x, y, cx, cy, &dcCompat, 0, 0, DSna);
	dcCompat.SelectObject(pbmp);
	pDC->BitBlt(x, y, cx, cy, &dcCompat, 0, 0, DSx);
	dcCompat.SelectObject(pbmpSave);

	pDC->SetBkColor(oldBkColor);
	pDC->SetTextColor(oldTextColor);
}

/////////////////////////////////////////////////////////////////////////////
// CNtSvcCtrl::CNtSvcCtrl - Constructor

CNtSvcCtrl::CNtSvcCtrl()
{
	InitializeIIDs(&IID_DNtSvc, &IID_DNtSvcEvents);

	EnableSimpleFrame();

	// Initialize control's instance data.
    m_pThis = this;			// WARNING: Only one service per application


	m_hStopEvent = NULL;
	m_hServiceThread = NULL;

	m_hEventSource = NULL;

	ZeroMemory (&m_Status, sizeof(SERVICE_STATUS));	
	ZeroMemory (m_szServiceName, sizeof(m_szServiceName));
    m_hServiceStatus = NULL;
    m_bIsRunning = FALSE;
	m_LoadOrderGroup = "";
	m_Dependencies = "";
	m_controlsAccepted = 0;
	m_bIsDebug = -1;
	m_interactive = FALSE;
	m_account = "";
	m_password = "";
	m_Dependencies = "";
	m_LoadOrderGroup = "";


	// keep fixed control size
	m_bmIcon.LoadBitmap(IDB_NTSVC);
	CreateMask (&m_bmIcon, &m_bmMask);

	BITMAP bmInfo;
	m_bmIcon.GetObject(sizeof(bmInfo), &bmInfo);
	m_pixSize.cx = bmInfo.bmWidth;
	m_pixSize.cy = bmInfo.bmHeight;

	SetInitialSize(28, 28);
	m_Size.cx = m_cxExtent;
	m_Size.cy = m_cyExtent;

	m_brBkgnd.CreateSolidBrush(GetSysColor(COLOR_3DFACE));
}


/////////////////////////////////////////////////////////////////////////////
// CNtSvcCtrl::~CNtSvcCtrl - Destructor

CNtSvcCtrl::~CNtSvcCtrl()
{
    if (m_hEventSource) {
        ::DeregisterEventSource(m_hEventSource);
    }
}


/////////////////////////////////////////////////////////////////////////////
// CNtSvcCtrl::OnDraw - Drawing function

void CNtSvcCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	CRect rc(rcBounds);
	// draw the control icon
	::DrawEdge(pdc->m_hDC, &rc, BDR_INNER,
		BF_RECT | BF_ADJUST | BF_FLAT );

	::DrawEdge(pdc->m_hDC, &rc, EDGE_RAISED, BF_RECT | BF_ADJUST);

	rc.left += (rc.Width() - m_pixSize.cx) / 2;
	rc.top += (rc.Height() - m_pixSize.cy) / 2;
	DrawMaskedBitmap(pdc, &m_bmIcon, &m_bmMask, rc.left, rc.top, m_pixSize.cx, m_pixSize.cy);
}


BOOL CNtSvcCtrl::OnEraseBkgnd(CDC* pDC) 
{
	CRect rc;
	GetClientRect (&rc);
	pDC->FillRect (&rc, &m_brBkgnd);

	return COleControl::OnEraseBkgnd(pDC);
}


BOOL CNtSvcCtrl::OnSetExtent(LPSIZEL lpSizeL)
{
	*lpSizeL = m_Size;

	return COleControl::OnSetExtent (lpSizeL);
}

/////////////////////////////////////////////////////////////////////////////
// CNtSvcCtrl::DoPropExchange - Persistence support

void CNtSvcCtrl::DoPropExchange(CPropExchange* pPX)
{
	BOOL bLoading = pPX->IsLoading();

	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	PX_String(pPX, _T("DisplayName"), m_displayName, "Simple Service");
	PX_String(pPX, _T("Dependencies"), m_Dependencies, "");
	PX_String(pPX, _T("LoadOrderGroup"), m_LoadOrderGroup, "");
	PX_Bool(pPX, _T("Debug"), m_bIsDebug, 0);
	PX_Long(pPX, _T("ControlsAccepted"), m_controlsAccepted, 0);
	PX_String(pPX, _T("Account"), m_account, "");
	PX_String(pPX, _T("Password"), m_password, "");
	PX_Bool(pPX, _T("Interactive"), m_interactive, 0);

	if (bLoading)
	{
		CString strProp;
		PX_String(pPX, _T("ServiceName"), strProp, "Simple");
		InternalSetService (strProp);

		long lProp;
		PX_Long(pPX, _T("StartMode"), lProp, SERVICE_DEMAND_START);
		m_dwStartMode = (DWORD) lProp;
	}
	else
	{
		long lProp;

		PX_String(pPX, _T("ServiceName"), CString(m_szServiceName));
		
		lProp = m_dwStartMode;
		PX_Long(pPX, _T("StartMode"), lProp);
	}
}


/////////////////////////////////////////////////////////////////////////////
// CNtSvcCtrl::OnResetState - Reset control to default state

void CNtSvcCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CNtSvcCtrl::AboutBox - Display an "About" box to the user

void CNtSvcCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_NTSVC);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CNtSvcCtrl property handlers

void CNtSvcCtrl::OnDisplayNameChanged() 
{
	SetModifiedFlag();
}


void CNtSvcCtrl::OnDependenciesChanged() 
{
	SetModifiedFlag();
}

void CNtSvcCtrl::OnLoadOrderGroupChanged() 
{
	SetModifiedFlag();
}

long CNtSvcCtrl::GetStartMode() 
{
	return m_dwStartMode;
}

void CNtSvcCtrl::SetStartMode(long nNewValue) 
{
	m_dwStartMode = (DWORD) nNewValue;

	SetModifiedFlag();
}


BSTR CNtSvcCtrl::GetServiceName() 
{
	CString strResult;

	strResult = m_szServiceName;

	return strResult.AllocSysString();
}

void CNtSvcCtrl::SetServiceName(LPCTSTR lpszNewValue) 
{
	InternalSetService(lpszNewValue);

	SetModifiedFlag();
}


BOOL CNtSvcCtrl::GetDebug() 
{
	return m_bIsDebug;

}

void CNtSvcCtrl::SetDebug(BOOL bNewValue) 
{
	m_bIsDebug = bNewValue;

	SetModifiedFlag();
}

void CNtSvcCtrl::OnControlsAcceptedChanged() 
{
	SetModifiedFlag();
}



/////////////////////////////////////////////////////////////////////////////
// CNtSvcCtrl message handlers

LRESULT CNtSvcCtrl::OnStart(WPARAM wParam, LPARAM lParam)
{
    // Get a pointer to the C++ object
    CNtSvcCtrl* pService = m_pThis;

	// Start the initialisation
	BOOL bSuccess = FALSE;

	pService->FireStart(&bSuccess);
	if (bSuccess) 
	{
		// Do the real work. 
		pService->m_bIsRunning = TRUE;
        pService->SetStatus(SERVICE_RUNNING);

		if (!m_bIsDebug)
			LogEvent(EVENTLOG_INFORMATION_TYPE, EVMSG_STARTED, "");
	}
	else
	{
		pService->m_bIsRunning = FALSE;
        pService->SetStatus(SERVICE_STOPPED);

		if (!m_bIsDebug)
			LogEvent(EVENTLOG_INFORMATION_TYPE, EVMSG_FAILEDINIT, "");
	}

	// report status to service control manager
	ReportStatus();

	return 0L;
}

LRESULT CNtSvcCtrl::OnHandler(WPARAM wParam, LPARAM lParam)
{
    // Get a pointer to the C++ object
    CNtSvcCtrl* pService = m_pThis;
	BOOL bSuccess = FALSE;

	// Report current status
    ReportStatus();

	switch (wParam)
	{
    case SERVICE_CONTROL_STOP: // 1
		m_pThis->StopService();
        break;

    case SERVICE_CONTROL_PAUSE: // 2
		pService->FirePause(&bSuccess);
		if (bSuccess)
			SetStatus (SERVICE_PAUSED);
        break;

    case SERVICE_CONTROL_CONTINUE: // 3
		pService->FireContinue(&bSuccess);
		if (bSuccess)
			SetStatus (SERVICE_RUNNING);
        break;

    case SERVICE_CONTROL_INTERROGATE: // 4
        break;

    case SERVICE_CONTROL_SHUTDOWN: // 5
		break;

	default:
		pService->FireControl(wParam);
		break;
	}

	// Report current status
    ReportStatus();

	return 0L;
}


/////////////////////////////////////////////////////////////////////////////
// CNtSvcCtrl support member functions
//

void CNtSvcCtrl::InternalSetService(LPCTSTR lpszNewValue)
{
	_tcsncpy(m_szServiceName, lpszNewValue, sizeof(m_szServiceName));
	m_szServiceName[SERVICE_NAME_LEN] = '\0';

    wsprintf(m_szSvcRegKey, TEXT("SYSTEM\\CurrentControlSet\\Services\\%s\\"), m_szServiceName);
}

long CNtSvcCtrl::GetStatus() 
{
	return m_Status.dwCurrentState;
}

void CNtSvcCtrl::SetStatus(long nNewValue) 
{
	m_Status.dwCurrentState = (DWORD) nNewValue;
}

void CNtSvcCtrl::ReportStatus()
{
	// Report current status
	if (m_hServiceStatus)
	    ::SetServiceStatus(m_hServiceStatus, &m_Status);
}


void CNtSvcCtrl::DebugMsg(const TCHAR* pszFormat, ...)
{
    TCHAR buf[1024];
#ifdef UNICODE
#define DBG_FMT TEXT("[%ls](%lu): ")
#else
#define DBG_FMT TEXT("[%s](%lu): ")
#endif
    wsprintf(buf, DBG_FMT, m_szServiceName, GetCurrentThreadId());
	va_list arglist;
	va_start(arglist, pszFormat);
    _vstprintf(&buf[_tcslen(buf)], pszFormat, arglist);
	va_end(arglist);
    _tcscat(buf, TEXT("\n"));
    OutputDebugString(buf);
}


/////////////////////////////////////////////////////////////////////////////
// CNtSvcCtrl static members

DWORD CNtSvcCtrl::ServiceThread(LPVOID)
{
	BOOL b;

    // Get a pointer to the C++ object
    CNtSvcCtrl* pService = m_pThis;

    SERVICE_TABLE_ENTRY st[] = {
        {m_pThis->m_szServiceName, ServiceMain},
        {NULL, NULL}
    };

    m_pThis->DebugMsg(TEXT("Calling StartServiceCtrlDispatcher()"));

	// Call the services dispatcher. This call blocks
    // until the service stops
    b = ::StartServiceCtrlDispatcher(st);

    m_pThis->DebugMsg(TEXT("Returned from StartServiceCtrlDispatcher()"));

    return b;
}


// 
void CNtSvcCtrl::ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv)
{
    // Get a pointer to the C++ object
    CNtSvcCtrl* pService = m_pThis;

    pService->DebugMsg(TEXT("Entering CNtSvcCtrl::ServiceMain()"));

    // Register the control request handler
    pService->m_Status.dwCurrentState = SERVICE_START_PENDING;
    pService->m_hServiceStatus = RegisterServiceCtrlHandler(pService->m_szServiceName,
                                                           Handler);
    if (pService->m_hServiceStatus == NULL) 
	{
        pService->LogEvent(EVENTLOG_ERROR_TYPE, EVMSG_CTRLHANDLERNOTINSTALLED, NULL);
        return;
    }

	pService->m_hStopEvent = CreateEvent(
        NULL,    // no security attributes
        TRUE,    // manual reset event
        FALSE,   // not-signalled
        NULL);   // no name

	// notify the user that the service is starting
	m_pThis->PostMessage(CWM_START, 0, 0);

	// The service thread will wait indefinately until
	// the service control manager or the user signals
	// the stop event. This event is set inside the StopService
	// method.
	WaitForSingleObject(m_pThis->m_hStopEvent, INFINITE);

    // Tell the service manager we are stopped
    pService->SetStatus(SERVICE_STOPPED);
	pService->ReportStatus();

    pService->DebugMsg(TEXT("Leaving CNtSvcCtrl::ServiceMain()"));
}


void CNtSvcCtrl::Handler(DWORD dwOpcode)
{
    // Get a pointer to the object
    CNtSvcCtrl* pService = m_pThis;


    pService->DebugMsg("CNTService::Handler(%lu)", dwOpcode);
    switch (dwOpcode) {
    case SERVICE_CONTROL_STOP: // 1
        pService->SetStatus(SERVICE_STOP_PENDING);
        break;

    case SERVICE_CONTROL_PAUSE:
        pService->SetStatus(SERVICE_PAUSE_PENDING);
        break;

    default:
		// custom service control
        break;
    }
	
	// Report current status
    m_pThis->ReportStatus();

	// deffer message
	m_pThis->PostMessage (CWM_HANDLER,dwOpcode, 0);
}



/////////////////////////////////////////////////////////////////////////////
// CNtSvcCtrl methods
//
BOOL CNtSvcCtrl::Install() 
{
    // Open the Service Control Manager
    SC_HANDLE hSCM = ::OpenSCManager(NULL, // local machine
                                     NULL, // ServicesActive database
                                     SC_MANAGER_ALL_ACCESS); // full access
    if (!hSCM) return FALSE;

    // Get the executable file path
    TCHAR szFilePath[_MAX_PATH];
    ::GetModuleFileName(NULL, szFilePath, sizeof(szFilePath));

	DWORD dwDesiredAccess = SERVICE_WIN32_OWN_PROCESS;
	if (m_interactive)
		dwDesiredAccess |= SERVICE_INTERACTIVE_PROCESS;

	LPSTR lpServiceAccount = NULL;
	if (m_account.GetLength() > 0 )
		lpServiceAccount = m_account.GetBuffer(m_account.GetLength()+1);

	LPSTR lpPassword = NULL;
	if (m_password.GetLength() > 0)
		lpPassword = m_password.GetBuffer(m_password.GetLength()+1);

    // Create the service
    SC_HANDLE hService = ::CreateService(hSCM,
                                         m_szServiceName,
                                         m_displayName,
                                         SERVICE_ALL_ACCESS,
                                         dwDesiredAccess,
                                         m_dwStartMode,        // start condition
                                         SERVICE_ERROR_NORMAL,
                                         szFilePath,
                                         NULL,
                                         NULL,
                                         NULL,
                                         lpServiceAccount,
                                         lpPassword);

	if (lpServiceAccount)
		m_account.ReleaseBuffer();

	if (lpPassword)
		m_password.ReleaseBuffer();

    if (!hService) {
        ::CloseServiceHandle(hSCM);
        return FALSE;
    }

    // make registry entries to support logging messages
    // Add the source name as a subkey under the Application
    // key in the EventLog service portion of the registry.
	
	// this time, we get the path of the control
    ::GetModuleFileName(AfxGetInstanceHandle(), szFilePath, sizeof(szFilePath));

    TCHAR szKey[256];
    HKEY hKey = NULL;
    _tcscpy(szKey, TEXT("SYSTEM\\CurrentControlSet\\Services\\EventLog\\Application\\"));
    _tcscat(szKey, m_szServiceName);
    if (::RegCreateKey(HKEY_LOCAL_MACHINE, szKey, &hKey) != ERROR_SUCCESS) {
        ::CloseServiceHandle(hService);
        ::CloseServiceHandle(hSCM);
        return FALSE;
    }

    // Add the Event ID message-file name to the 'EventMessageFile' subkey.
    ::RegSetValueEx(hKey,
                    TEXT("EventMessageFile"),
                    0,
                    REG_EXPAND_SZ, 
                    (CONST BYTE*)szFilePath,
                    _tcslen(szFilePath) + 1);     

    // Set the supported types flags.
    DWORD dwData = EVENTLOG_ERROR_TYPE | EVENTLOG_WARNING_TYPE | EVENTLOG_INFORMATION_TYPE;
    ::RegSetValueEx(hKey,
                    TEXT("TypesSupported"),
                    0,
                    REG_DWORD,
                    (CONST BYTE*)&dwData,
                     sizeof(DWORD));
    ::RegCloseKey(hKey);

    LogEvent(EVENTLOG_INFORMATION_TYPE, EVMSG_INSTALLED, m_displayName);

    // tidy up
    ::CloseServiceHandle(hService);
    ::CloseServiceHandle(hSCM);

    return TRUE;
}

BOOL CNtSvcCtrl::Uninstall() 
{
    BOOL bResult = FALSE;

    // Open the Service Control Manager
    SC_HANDLE hSCM = ::OpenSCManager(NULL, // local machine
                                     NULL, // ServicesActive database
                                     SC_MANAGER_ALL_ACCESS); // full access
    if (!hSCM) return FALSE;

    SC_HANDLE hService = ::OpenService(hSCM,
                                       m_szServiceName,
                                       DELETE);
    if (hService) {
        if (::DeleteService(hService)) {
            LogEvent(EVENTLOG_INFORMATION_TYPE, EVMSG_REMOVED, m_szServiceName);
            bResult = TRUE;
        } else {
            LogEvent(EVENTLOG_ERROR_TYPE, EVMSG_NOTREMOVED, m_szServiceName);
        }
        ::CloseServiceHandle(hService);
    }
    
    ::CloseServiceHandle(hSCM);
    
	return bResult;
}


BOOL CNtSvcCtrl::StartService()
{
	BOOL bSuccess = FALSE;

	// initialize service status
    m_Status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    m_Status.dwCurrentState = SERVICE_STOPPED;
    m_Status.dwControlsAccepted = SERVICE_ACCEPT_STOP | m_controlsAccepted;
    m_Status.dwWin32ExitCode = 0;
    m_Status.dwServiceSpecificExitCode = 0;
    m_Status.dwCheckPoint = 0;
    m_Status.dwWaitHint = 0;

    // in debug mode, don’t create a service thread
	if (m_bIsDebug)
	{
		m_pThis->PostMessage(CWM_START, 0, 0);
		bSuccess = TRUE;
	}
	else
	{
		DWORD dwThreadId;
		
        // create a service thread that to communicate with
        // the services dispatcher

		m_hServiceThread = CreateThread(
			NULL,		// pointer to thread security attributes  
			0,			// initial thread stack size, in bytes 
			ServiceThread,	// pointer to thread function 
			NULL,		// argument for new thread 
			0,			// creation flags 
			&dwThreadId 	// pointer to returned thread identifier 
		);	

		if (m_hServiceThread)
		{
			bSuccess = TRUE;
		}
	}

	return bSuccess;
}

void CNtSvcCtrl::StopService() 
{
    FireStop();

	m_bIsRunning = FALSE;

	// Keep service contorl manager informed
	ReportStatus();

	// Release the thread created by the
	// service control manager. When that thread exits,
	// the service will be considered as 'stopped'
    if ( m_hStopEvent )
        SetEvent(m_hStopEvent);

	// Wait for the service thread to exit. This ensures
	// that service control manager gets all its notifications
	// before the container frees the control
	if ( m_hServiceThread)
	{
		WaitForSingleObject (m_hServiceThread, INFINITE);
		CloseHandle (m_hServiceThread);
		m_hServiceThread = NULL;
	}

	// Signal that the user wants to end the service.
	if (!m_bIsDebug)
		LogEvent(EVENTLOG_INFORMATION_TYPE, EVMSG_STOPPED, "");

	PostQuitMessage(0);

}

BOOL CNtSvcCtrl::Running() 
{
	return m_bIsRunning;
}


BOOL CNtSvcCtrl::LogEvent(short wType, long dwID, LPCTSTR Message) 
{
    // Check the event source has been registered and if
    // not then register it now
    if (!m_hEventSource) {
        m_hEventSource = ::RegisterEventSource(NULL,  // local machine
                                               m_szServiceName); // source name
    }

    if (m_hEventSource) {
        ::ReportEvent(m_hEventSource,
                      wType,
                      0,
                      dwID,
                      NULL, // sid
                      1,
                      0,
                      &Message,
                      NULL);
    }
	else {
		return FALSE;
	}

	return TRUE;
}


VARIANT CNtSvcCtrl::GetAllSettings(LPCTSTR section) 
{
	VARIANT vaResult;
	VariantInit(&vaResult);

	SAFEARRAYBOUND rgsaBounds[2];
	SAFEARRAY* psaSettings;

	DWORD cbValue;
	DWORD cbData;
	DWORD dwType;
    HKEY hKey = NULL;
	TCHAR szKey[256];
	TCHAR szValue [256];
	int n;

	HRESULT hr;

	rgsaBounds[0].lLbound = 0;
	rgsaBounds[0].cElements = 2;
	rgsaBounds[1].lLbound = 0;
	rgsaBounds[1].cElements = 0;

	psaSettings = SafeArrayCreate (VT_BSTR, 2, rgsaBounds);

	wsprintf (szKey, "%s%s\\", m_szSvcRegKey, section);
    if (::RegOpenKey(HKEY_LOCAL_MACHINE, szKey, &hKey) == ERROR_SUCCESS )
	{
		n = 0;

		cbValue = sizeof(szValue) - 1;
		while (::RegEnumValue(hKey, n, szValue, &cbValue, 0, &dwType, NULL, &cbData) == ERROR_SUCCESS )
		{
			// terminate value string
			szValue [cbValue] = '\0';

			CString strValue (szValue);

			// get data
			CString strData;
			LPSTR szBuffer = strData.GetBuffer(cbData + 1);

			if (szBuffer)
			{
				::RegEnumValue(hKey, n, szValue, &cbValue, 0, &dwType, (BYTE*)szBuffer, &cbData);
				strData.ReleaseBuffer();
			}

			// re-dimension least significant dimension (rows)
			rgsaBounds[1].cElements = n + 1;
			hr = SafeArrayRedim (psaSettings, &rgsaBounds[1]);

			if (SUCCEEDED(hr))
			{
				long rgIndices[2];
				BSTR bstrElement;
				rgIndices[1] = n;

				rgIndices[0] = 0;
				bstrElement = strValue.AllocSysString();
				hr = SafeArrayPutElement (psaSettings, rgIndices, bstrElement);

				rgIndices[0] = 1;
				bstrElement = strData.AllocSysString();
				hr = SafeArrayPutElement (psaSettings, rgIndices, bstrElement);
			}
			else
			{
				// TODO: should throw error
				break;
			}


			// increment enum counter
			n ++;

			// reset input parameters for while loop
			cbValue = sizeof(szValue) - 1;
		}
	}
    
    ::RegCloseKey(hKey);
	
	vaResult.vt = VT_ARRAY|VT_BSTR;
	vaResult.parray = psaSettings;

	return vaResult;
}

void CNtSvcCtrl::SaveSetting(LPCTSTR section, LPCTSTR key, LPCTSTR setting) 
{
    HKEY hKey = NULL;
	TCHAR szKey[256];

	wsprintf (szKey, "%s%s\\", m_szSvcRegKey, section);
    if (::RegCreateKey(HKEY_LOCAL_MACHINE, szKey, &hKey) != ERROR_SUCCESS) 
	{
		// cannot create key
		ThrowError(ERROR_ACCESS_DENIED);
        return;
    }

    // Add the Event ID message-file name to the 'EventMessageFile' subkey.
    ::RegSetValueEx(hKey,
                    key,
                    0,
                    REG_EXPAND_SZ, 
                    (CONST BYTE*)setting,
                    _tcslen(setting) + 1);     

    ::RegCloseKey(hKey);
}


void CNtSvcCtrl::DeleteSetting(LPCTSTR section, const VARIANT FAR& key) 
{
    HKEY hKey = NULL;
	SCODE sc = 0;

	if (::RegOpenKey(HKEY_LOCAL_MACHINE, m_szSvcRegKey, &hKey) != ERROR_SUCCESS)
		ThrowError(ERROR_ACCESS_DENIED);

	if (key.vt != VT_ERROR)
	{
		if (key.vt == VT_BSTR)
		{
			HKEY hSubKey;
			CString strKey = key.bstrVal;
			if (::RegOpenKey(hKey, m_szSvcRegKey, &hSubKey) == ERROR_SUCCESS)
			{
				RegDeleteKey (hSubKey, strKey);
				RegCloseKey (hKey);
			}
			else
			{
				sc = ERROR_ACCESS_DENIED;
			}
		}
		else
		{
			sc = DISP_E_TYPEMISMATCH;
		}
	}
	else
	{
		::RegDeleteKey (hKey, section);
	}
    ::RegCloseKey (hKey);

	if (sc)
	{
		ThrowError(sc);
	}
}

BSTR CNtSvcCtrl::GetSetting(LPCTSTR section, LPCTSTR key, const VARIANT FAR& def) 
{
	CString strResult;

	DWORD cbValue;
	DWORD dwType;
    HKEY hKey = NULL;
	TCHAR szKey[256];

	wsprintf (szKey, "%s%s\\", m_szSvcRegKey, section);
    if (::RegOpenKey(HKEY_LOCAL_MACHINE, szKey, &hKey) == ERROR_SUCCESS
		&& ::RegQueryValueEx(hKey, key, 0, &dwType, NULL, &cbValue) == ERROR_SUCCESS )
	{
		LPSTR szBuffer = strResult.GetBuffer(cbValue + 1);

		if (szBuffer)
		{
			::RegQueryValueEx(hKey, key, 0, &dwType, (BYTE*)szBuffer, &cbValue);
			strResult.ReleaseBuffer();
		}
    }
	else
	{
		if (def.vt == VT_BSTR)
			strResult = def.bstrVal;
		else
			ThrowError(DISP_E_TYPEMISMATCH);
	}
    
    ::RegCloseKey(hKey);
	
	return strResult.AllocSysString();
}



void CNtSvcCtrl::OnInteractiveChanged() 
{
	// TODO: Add notification handler code

	SetModifiedFlag();
}

void CNtSvcCtrl::OnAccountChanged() 
{
	// TODO: Add notification handler code

	SetModifiedFlag();
}

void CNtSvcCtrl::OnPasswordChanged() 
{
	// TODO: Add notification handler code

	SetModifiedFlag();
}