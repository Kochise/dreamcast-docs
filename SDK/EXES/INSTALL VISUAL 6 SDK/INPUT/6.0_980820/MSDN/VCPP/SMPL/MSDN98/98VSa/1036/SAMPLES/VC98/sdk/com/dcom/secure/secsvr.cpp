// ===========================================================================
// File: S E C S V R . C P P
// 
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Description:
// 
//  This is the server-portion of the SECURE Network OLE sample. This
// application implements several different server capabilities:
//   * Free-threaded server implemented as a Service. The application
//     implements a "LocalService" (CLSID_SecureObjectService) class.
//   * Free-threaded server implemented as a standard executable. The
//     application implements a "LocalServer32" (CLSID_SecureObject) class
//     and runs without user-interface.
//   * Apartment-threaded server implemented as a standard executable. The
//     application implements a "LocalServer32" (CLSID_SecureObject) class
//     and runs with a dialog-box user-interface showing the status of the
//     objects that it has handed out to clients.
// 
//  The purpose of this sample is to demonstrate the different packaging
// options available to server writers, and to demonstrate call-security
// capabilities.
// 
// Instructions:
// 
//  To use this sample:
//   * build the samples using the NMAKE command. NMAKE will create SECCLNT.EXE,
//     SECSVR.EXE, and PSMYPROP.DLL. PSMYPROP.DLL is the remoting proxies and
//     stubs for the custom interface used between the client and the server.
//   * install the server on the current machine or on a remote machine
//     by running INSTALL.BAT in the same directory with SECSVR.EXE and
//     PSMYPROP.DLL. This program registers the proxy-stub DLL using the
//     REGSVR32 tool (included in the \mstools\bin directory of the SDK) and
//     runs the SECSVR.EXE program with "-AutoRegister" on the command-line,
//     which forces it to install itself.
//   * to run the apartment-threaded server, use "SECSVR -Interactive" to launch
//     the server from the command-line. the application will present UI allowing
//     you to choose how to initialize security for the server process, and
//     to view objects currently being used by clients.
//   * In Section 1, choose the security parameters to CoInitializeSecurity from
//     the two drop-down lists, and press the Initialize button.
//   * next, run SECCLNT.EXE from the same machine or from a remote machine. Follow
//     the instructions listed in SECCLNT.CPP to connect to this instance of the
//     SECSVR.EXE application.
//   * once a client has created an instance of the CLSID_SecureObject class, the
//     object will be listed in the drop-down list in Section 2 of the SECSVR.EXE
//     UI. Select the object to be viewed from this list. The current color and
//     "name" established by the client will be displayed in Section 2.
//   * use the "Lock" button to prevent the client from setting the color or "UserName"
//     of the object. the client will display an "access-denied" message if it
//     fails to set the color or "UserName". in the future this sample will include
//     the ability to establish a security-descriptor on the color and Name, and
//     will demonstrate impersonating the client and performing an AccessCheck()
//     during the PutColor and PutUserName methods.
//   * Push the "Exit" button in Section 1 to shut the server down.
// 
// Copyright 1996 Microsoft Corporation. All Rights Reserved.
// ===========================================================================

// %%Includes: ---------------------------------------------------------------
#define INC_OLE2
#define STRICT
#define UNICODE
#include <windows.h>
#include <initguid.h>
#include "myprop.h"
#include "secsvr.h"

// %%Macros: -----------------------------------------------------------------
#define ENTRY(sz, val)      { sz, val }
#define RGSIZEOF(rg)        (sizeof(rg)/sizeof((rg)[0]))

// %%Constants: --------------------------------------------------------------
const TCHAR szServiceName[] = TEXT("SecSvr");
const TCHAR szDescription[] = TEXT("Network OLE Security Sample");
#define cAuthnLevelEntries  RGSIZEOF(rgAuthnLevelEntries)
#define cImpLevelEntries    RGSIZEOF(rgImpLevelEntries)

// %%Types: ------------------------------------------------------------------
typedef struct tagENTRY{
    TCHAR   *szName;
    DWORD   dwVal;
} ENTRY, *PENTRY;

// %%Classes: ----------------------------------------------------------------
class CClassFactory : public IClassFactory
    {
  // IClassFactory
    STDMETHODIMP            QueryInterface(REFIID iid, void **ppv);
    STDMETHODIMP_(ULONG)    AddRef(void)    { return 1; }
    STDMETHODIMP_(ULONG)    Release(void)   { return 1; }
    STDMETHODIMP            CreateInstance(LPUNKNOWN punkOuter, REFIID iid, LPVOID FAR *ppv);
    STDMETHODIMP            LockServer(BOOL fLock);
    };

class CSecureObject : public IMyProperties
    {
  // IUnknown
    STDMETHODIMP    QueryInterface(REFIID iid, void **ppv);
    STDMETHODIMP_(ULONG) AddRef(void)    { return InterlockedIncrement(&m_cRef); }
    STDMETHODIMP_(ULONG) Release(void)   { if (InterlockedDecrement(&m_cRef) == 0) { delete this; return 0; } return 1; }

  // IMyProperties
    STDMETHODIMP    GetColor(COLORREF* pcr);
    STDMETHODIMP    PutColor(COLORREF cr);
    STDMETHODIMP    GetUserName(WCHAR szUserName[20]);
    STDMETHODIMP    PutUserName(WCHAR szUserName[20]);

  // data members
    LONG        m_cRef;
  public:
    COLORREF    m_crColor;
    BOOL        m_fDenyPutColor;
    WCHAR       m_rgchUserName[20];
    BOOL        m_fDenyPutUserName;

  // constructors/destructors
    CSecureObject();
    ~CSecureObject();
    };

// %%Prototypes: -------------------------------------------------------------
void    MyServiceMain(DWORD cArg, LPTSTR *rgszArg);
void    MyServiceHandler(DWORD dwControl);
void    ErrorMessage(HWND hwnd, LPTSTR szFunction, HRESULT hr);

// %%Globals: ----------------------------------------------------------------
CClassFactory   s_ClassFactory;
struct {
    SERVICE_STATUS          Status;
    SERVICE_STATUS_HANDLE   hStatus;
    DWORD                   dwRegister;
    } s_Service;
SERVICE_TABLE_ENTRY     s_rgsteServices[2] = { { (TCHAR*)szServiceName, MyServiceMain },
					      { NULL, NULL } };
HWND            s_hwndDlg;
UINT            s_cInstances;
HANDLE          s_hevtDone;
CRITICAL_SECTION s_csDone;
BOOL            s_fDone, s_fServer, s_fService;
ENTRY   rgAuthnLevelEntries[] = {
    ENTRY(TEXT("Default    "), RPC_C_AUTHN_DEFAULT),
    ENTRY(TEXT("None       "), RPC_C_AUTHN_LEVEL_NONE),
    ENTRY(TEXT("Connect    "), RPC_C_AUTHN_LEVEL_CONNECT),
    ENTRY(TEXT("Call       "), RPC_C_AUTHN_LEVEL_CALL),
    ENTRY(TEXT("Packet     "), RPC_C_AUTHN_LEVEL_PKT),
    ENTRY(TEXT("Integrity  "), RPC_C_AUTHN_LEVEL_PKT_INTEGRITY),
    ENTRY(TEXT("Privacy    "), RPC_C_AUTHN_LEVEL_PKT_PRIVACY),
    };

ENTRY   rgImpLevelEntries[] = {
    ENTRY(TEXT("Anonymous  "), RPC_C_IMP_LEVEL_ANONYMOUS),
    ENTRY(TEXT("Identify   "), RPC_C_IMP_LEVEL_IDENTIFY),
    ENTRY(TEXT("Impersonate"), RPC_C_IMP_LEVEL_IMPERSONATE),
    ENTRY(TEXT("Delegate   "), RPC_C_IMP_LEVEL_DELEGATE),
    };


// ===========================================================================
//                          C C L A S S F A C T O R Y
// ===========================================================================

// ---------------------------------------------------------------------------
// %%Function: CClassFactory::QueryInterface
// ---------------------------------------------------------------------------
 STDMETHODIMP
CClassFactory::QueryInterface(REFIID iid, void **ppv)
{
    if (iid == IID_IClassFactory || iid == IID_IUnknown)
	{
	*ppv = (IClassFactory *)this;
	AddRef();
	return S_OK;
	}
    *ppv = NULL;
    return E_NOINTERFACE;
}  // CClassFactory::QueryInterface

// ---------------------------------------------------------------------------
// %%Function: CClassFactory::CreateInstance
// ---------------------------------------------------------------------------
 STDMETHODIMP
CClassFactory::CreateInstance(LPUNKNOWN punkOuter, REFIID riid, void **ppv)
{
    LPUNKNOWN   punk;
    HRESULT     hr;

    *ppv = NULL;

    if (punkOuter != NULL)
	return CLASS_E_NOAGGREGATION;

    if (s_fServer)
	{
	EnterCriticalSection(&s_csDone);
	if (s_fDone == TRUE)
	    {
	    LeaveCriticalSection(&s_csDone);
	    return E_FAIL;
	    }
	LeaveCriticalSection(&s_csDone);
	}

    punk = new CSecureObject;
    if (punk == NULL)
	return E_OUTOFMEMORY;

    hr = punk->QueryInterface(riid, ppv);
    punk->Release();
    return hr;
}  // CClassFactory::CreateInstance

// ---------------------------------------------------------------------------
// %%Function: CClassFactory::LockServer
// ---------------------------------------------------------------------------
 STDMETHODIMP
CClassFactory::LockServer(BOOL fLock)
{
    // LockServer not supported by the GUI server -- shutdown is
    // completely controlled by the UI's Exit command
    if (!s_fServer)
	return E_FAIL;

    // LockServer acts like having an artificial object outstanding:
    // this code mimics the lifetime management found in the constructor
    // and destructor of CSecureObject
    EnterCriticalSection(&s_csDone);
    if (fLock)
	s_cInstances++;
    else
	{
	if (!--s_cInstances && !s_fService) /* could perform other shutdown management here */
	    {
	    s_fDone = TRUE;
	    SetEvent(s_hevtDone);
	    }
	}
    LeaveCriticalSection(&s_csDone);
    return S_OK;
}  // CClassFactory::LockServer


// ===========================================================================
//                        C S e c u r e O b j e c t
// ===========================================================================

// ---------------------------------------------------------------------------
// %%Function: CSecureObject::CSecureObject
// ---------------------------------------------------------------------------
CSecureObject::CSecureObject()
{
    static int s_ID = 0;

    // initialize the object's state
    m_cRef = 1;
    m_crColor = 0;
    m_fDenyPutColor = FALSE;
    lstrcpyW(m_rgchUserName, L"Default");
    m_fDenyPutUserName = FALSE;

    if (!s_fServer)
	{
	TCHAR   rgchName[20];
	HWND    hwnd;
	int     iPos;

	// insert the object into the server UI. put our this-pointer into the item
	// data field of the entry so that we can remove the entry in our destructor
	wsprintf(rgchName, TEXT("Object %d"), s_ID++);
	hwnd = GetDlgItem(s_hwndDlg, IDC_OBJECTS);
	iPos = SendMessage(hwnd, CB_ADDSTRING, 0, (LPARAM)rgchName);
	SendMessage(hwnd, CB_SETITEMDATA, iPos, (LPARAM)this);
	}
    else
	{
	EnterCriticalSection(&s_csDone);
	s_cInstances++;
	LeaveCriticalSection(&s_csDone);
	}
}  // CSecureObject::CSecureObject

CSecureObject::~CSecureObject()
{
    if (!s_fServer)
	{
	HWND    hwnd;
	int     i, iSel, iMac;

	// remove the reference to us from the server UI. our this-pointer is in
	// the item-data field of the entry -- find it.
	hwnd = GetDlgItem(s_hwndDlg, IDC_OBJECTS);
	iSel = SendMessage(hwnd, CB_GETCURSEL, 0, 0);
	iMac = SendMessage(hwnd, CB_GETCOUNT, 0, 0);
	for (i=0; i<iMac; i++)
	    {
	    if ((LRESULT)this == SendMessage(hwnd, CB_GETITEMDATA, i, 0))
		{
		SendMessage(hwnd, CB_DELETESTRING, i, 0);

		// if the item being deleted is the current selection,
		// change the selection
		if (i == iSel)
		    {
		    SendMessage(hwnd, CB_SETCURSEL, 0, 0);
		    PostMessage(s_hwndDlg, WM_COMMAND, MAKELONG(IDC_OBJECTS, CBN_SELCHANGE),
			(LPARAM)hwnd);
		    }
		break;
		}
	    }
	}
    else
	{
	EnterCriticalSection(&s_csDone);
	if (!--s_cInstances && !s_fService) /* could perform other shutdown management here */
	    {
	    s_fDone = TRUE;
	    SetEvent(s_hevtDone);
	    }
	LeaveCriticalSection(&s_csDone);
	}
}  // CSecureObject::~CSecureObject

// ---------------------------------------------------------------------------
// %%Function: CSecureObject::QueryInterface
// ---------------------------------------------------------------------------
 STDMETHODIMP
CSecureObject::QueryInterface(REFIID iid, void **ppv)
{
    if (iid == IID_IMyProperties || iid == IID_IUnknown)
	{
	*ppv = (IMyProperties *)this;
	AddRef();
	return S_OK;
	}
    *ppv = NULL;
    return E_NOINTERFACE;
}  // CSecureObject::QueryInterface

// ---------------------------------------------------------------------------
// %%Function: CSecureObject::GetColor
// ---------------------------------------------------------------------------
 STDMETHODIMP
CSecureObject::GetColor(COLORREF* pcr)
{
    *pcr = m_crColor;
    return S_OK;
}  // CSecureObject::GetColor

// ---------------------------------------------------------------------------
// %%Function: CSecureObject::PutColor
// ---------------------------------------------------------------------------
 STDMETHODIMP
CSecureObject::PutColor(COLORREF cr)
{
    // a naive security check under control of the local-server's UI
    if (m_fDenyPutColor == TRUE)
	return E_ACCESSDENIED;

    m_crColor = cr;

    // update the UI to reflect a valid PutColor occurred
    if (!s_fServer)
	PostMessage(s_hwndDlg, WM_COMMAND, MAKELONG(IDC_OBJECTS,CBN_SELCHANGE),
	    (LPARAM)GetDlgItem(s_hwndDlg, IDC_OBJECTS));

    return S_OK;
}  // CSecureObject::PutColor

// ---------------------------------------------------------------------------
// %%Function: CSecureObject::GetUserName
// ---------------------------------------------------------------------------
 STDMETHODIMP
CSecureObject::GetUserName(WCHAR szUserName[20])
{
    lstrcpynW(szUserName, m_rgchUserName, 20);
    return S_OK;
}  // CSecureObject::GetUserName

// ---------------------------------------------------------------------------
// %%Function: CSecureObject::PutUserName
// ---------------------------------------------------------------------------
 STDMETHODIMP
CSecureObject::PutUserName(WCHAR szUserName[20])
{
    // a naive security check under control of the local-server's UI
    if (m_fDenyPutUserName == TRUE)
	return E_ACCESSDENIED;

    lstrcpynW(m_rgchUserName, szUserName, 20);

    // update the UI to reflect a valid PutUserName occurred
    if (!s_fServer)
	PostMessage(s_hwndDlg, WM_COMMAND, MAKELONG(IDC_OBJECTS,CBN_SELCHANGE),
	    (LPARAM)GetDlgItem(s_hwndDlg, IDC_OBJECTS));

    return S_OK;
}  // CSecureObject::PutUserName


// ---------------------------------------------------------------------------
// %%Function: FAutoRegister
// ---------------------------------------------------------------------------
 BOOL
FAutoRegister(HINSTANCE hinst)
{
    static const TCHAR szCLSIDEntryServer[]     = TEXT("CLSID\\{28f64ee0-4656-11cf-8110-00aa00389b71}");
    static const TCHAR szLocalServer32[]        = TEXT("LocalServer32");
    static const TCHAR szAllowRemoteActivation[] = TEXT("AllowRemoteActivation");
    static const TCHAR szCLSIDEntryService[]    = TEXT("CLSID\\{28f64ee2-4656-11cf-8110-00aa00389b71}");
    static const TCHAR szLocalService[]         = TEXT("LocalService");
    static const TCHAR szServiceParameters[]    = TEXT("ServiceParameters");
    static const TCHAR szParameters[]           = TEXT("-Service");
    static const TCHAR szEmpty[]                = TEXT("");
    SC_HANDLE   hManager = NULL, hService = NULL;
    TCHAR       szPath[MAX_PATH], *szError = TEXT("Registry Manipulation");
    HKEY        hkeyT = NULL, hkey2;

    // install the CLSID_SecureObject key and get the FQP to this executable
    if ((RegSetValue(HKEY_CLASSES_ROOT, szCLSIDEntryServer, REG_SZ, szDescription,
	    lstrlen(szDescription)) != ERROR_SUCCESS) ||
	(RegCreateKey(HKEY_CLASSES_ROOT, szCLSIDEntryServer, &hkeyT) != ERROR_SUCCESS) ||
	!GetModuleFileName(hinst, szPath, sizeof(szPath)/sizeof(TCHAR)))
	goto LErrExit;

    // install the LocalServer32 key and the AllowRemoteActivation key
    if ((RegSetValue(hkeyT, szLocalServer32, REG_SZ, szPath, lstrlen(szPath))
	    != ERROR_SUCCESS) ||
	(RegSetValue(hkeyT, szAllowRemoteActivation, REG_SZ, szEmpty, lstrlen(szEmpty))
	    != ERROR_SUCCESS))
	goto LErrExit;
    RegCloseKey(hkeyT);
    hkeyT = NULL;

    // install the CLSID_SecureObjectService key
    if ((RegSetValue(HKEY_CLASSES_ROOT, szCLSIDEntryService, REG_SZ, szDescription,
	    lstrlen(szDescription)) != ERROR_SUCCESS) ||
	(RegCreateKey(HKEY_CLASSES_ROOT, szCLSIDEntryService, &hkeyT) != ERROR_SUCCESS))
	goto LErrExit;

    // install the LocalService key and the ServiceParameters named-value
    if ((RegSetValue(hkeyT, szLocalService, REG_SZ, szServiceName, lstrlen(szServiceName))
	    != ERROR_SUCCESS) ||
	(RegOpenKey(hkeyT, szLocalService, &hkey2) != ERROR_SUCCESS))
	goto LErrExit;
    RegCloseKey(hkeyT);
    hkeyT = hkey2;
    if (RegSetValueEx(hkeyT, szServiceParameters, 0, REG_SZ, (const BYTE*)szParameters,
	    (lstrlen(szParameters)+1) * sizeof(TCHAR)) != ERROR_SUCCESS)
	goto LErrExit;

    RegCloseKey(hkeyT);
    hkeyT = NULL;

    // install the application to run as a service
    hManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if (hManager == NULL)
	{
	szError = TEXT("OpenSCManager");
	goto LErrExit;
	}

    hService = OpenService(hManager, szServiceName, SERVICE_ALL_ACCESS);
    if (hService != NULL)
	{
	if (!ChangeServiceConfig(hService,
	    SERVICE_WIN32_OWN_PROCESS,
	    SERVICE_DEMAND_START, SERVICE_ERROR_NORMAL, szPath,
	    NULL, NULL, NULL, NULL, NULL, szDescription))
	    {
	    szError = TEXT("ChangeServiceConfig");
	    goto LErrExit;
	    }
	return TRUE;
	}

    hService = CreateService(hManager, szServiceName, szDescription,
	SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS,
	SERVICE_DEMAND_START, SERVICE_ERROR_NORMAL, szPath,
	NULL, NULL, NULL,  NULL, NULL);
    if (hService == NULL)
	{
	szError = TEXT("CreateService");
	goto LErrExit;
	}

    CloseServiceHandle(hService);
    CloseServiceHandle(hManager);
    return TRUE;

LErrExit:
    ErrorMessage(GetDesktopWindow(), szError, GetLastError());
    if (hkeyT != NULL)
	RegCloseKey(hkeyT);
    if (hService != NULL)
	CloseServiceHandle(hService);
    if (hManager != NULL)
	CloseServiceHandle(hManager);
    return FALSE;
}  // FAutoRegister

// ---------------------------------------------------------------------------
// %%Function: ErrorMessage
// ---------------------------------------------------------------------------
 void
ErrorMessage(HWND hwnd, LPTSTR szFunction, HRESULT hr)
{
    LPTSTR   szMessage;

    if (HRESULT_FACILITY(hr) == FACILITY_WINDOWS)
	hr = HRESULT_CODE(hr);

    if (!FormatMessage(
	FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
	NULL, hr,
	MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), //The user default language
	(LPTSTR)&szMessage, 0, NULL))
	return;

    if (hwnd == NULL)
	{
	OutputDebugString(szFunction);
	OutputDebugString(TEXT(": "));
	OutputDebugString(szMessage);
	OutputDebugString(TEXT("\n"));
	}
    else
	MessageBox(hwnd, szMessage, szFunction, MB_OK);
    
    LocalFree(szMessage);
}  // ErrorMessage

// ---------------------------------------------------------------------------
// %%Function: SelectEntry
// ---------------------------------------------------------------------------
 void
SelectEntry(HWND hwnd, ENTRY* rgEntries, int cEntries, DWORD dwVal)
{
    for (int i=0; i<cEntries; i++)
	{
	if (rgEntries[i].dwVal == dwVal)
	    {
	    SendMessage(hwnd, CB_SETCURSEL, i, 0);
	    return;
	    }
	}
}  // SelectEntry

// ---------------------------------------------------------------------------
// %%Function: GetField
// ---------------------------------------------------------------------------
 DWORD
GetField(HWND hwndDlg, UINT idItem)
{
    HWND    hwnd;
    int     iCur;

    hwnd = GetDlgItem(hwndDlg, idItem);
    iCur = SendMessage(hwnd, CB_GETCURSEL, 0, 0);
    return SendMessage(hwnd, CB_GETITEMDATA, iCur, 0);
}  // GetField

// ---------------------------------------------------------------------------
// %%Function: ServerDialogProc
// ---------------------------------------------------------------------------
 BOOL CALLBACK
ServerDialogProc(HWND hwndDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    static DWORD    s_dwRegister = 0;
    static BOOL     s_fInitialized = FALSE;
    static CSecureObject* s_pcso = NULL;
    static COLORREF s_rgcrCustom[16];
    static HBRUSH   s_hbrCurrent = NULL;
    HRESULT hr;

    switch (message)
	{
	case WM_INITDIALOG:
	    {
	    HWND    hwnd;
	    int     cxScreen, cyScreen, i;
	    RECT    rcDlg;

	    // save the hwndDlg into a global
	    s_hwndDlg = hwndDlg;

	    // Center the UI on screen
	    cxScreen = GetSystemMetrics(SM_CXFULLSCREEN);
	    cyScreen = GetSystemMetrics(SM_CYFULLSCREEN);
	    GetWindowRect(hwndDlg, &rcDlg);
	    OffsetRect(&rcDlg,
		(cxScreen - rcDlg.right - rcDlg.left)/2,
		(cyScreen - rcDlg.bottom - rcDlg.top)/2);
	    MoveWindow(hwndDlg, rcDlg.left, rcDlg.top,
		rcDlg.right-rcDlg.left, rcDlg.bottom-rcDlg.top, TRUE);

	    // build the lists of authentication levels. choose None for the
	    // process default.
	    hwnd = GetDlgItem(hwndDlg, IDC_SERVER_AUTHNLEVEL);
	    for (i=0; i<cAuthnLevelEntries; i++)
		{
		SendMessage(hwnd, CB_INSERTSTRING, i, (LPARAM)rgAuthnLevelEntries[i].szName);
		SendMessage(hwnd, CB_SETITEMDATA, i, rgAuthnLevelEntries[i].dwVal);
		}
	    SelectEntry(hwnd, rgAuthnLevelEntries, cAuthnLevelEntries, RPC_C_AUTHN_LEVEL_NONE);

	    // build the lists of impersonation levels. choose Anonymous for the
	    // process default.
	    hwnd = GetDlgItem(hwndDlg, IDC_SERVER_IMPLEVEL);
	    for (i=0; i<cImpLevelEntries; i++)
		{
		SendMessage(hwnd, CB_INSERTSTRING, i, (LPARAM)rgImpLevelEntries[i].szName);
		SendMessage(hwnd, CB_SETITEMDATA, i, rgImpLevelEntries[i].dwVal);
		}
	    SelectEntry(hwnd, rgImpLevelEntries, cImpLevelEntries, RPC_C_IMP_LEVEL_ANONYMOUS);
	    return 1;
	    }

	case WM_SYSCOMMAND:
	    if (wParam == SC_CLOSE)
		goto LClose;
	    break;

	case WM_COMMAND:
	    switch (LOWORD(wParam))
		{
		case IDCANCEL:
LClose:
		    if (s_hbrCurrent != NULL)
			{
			DeleteObject(s_hbrCurrent);
			s_hbrCurrent = NULL;
			}
		    if (s_dwRegister != 0)
			{
			CoRevokeClassObject(s_dwRegister);
			s_dwRegister = 0;
			}
		    if (s_fInitialized == TRUE)
			{
			CoUninitialize();
			s_fInitialized = FALSE;
			}
		    EndDialog(hwndDlg, 0);
		    break;

		case IDC_INITIALIZE:
		    // initialize as apartment-threaded to synchronize the UI
		    // with calls to the objects
		    hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
		    if (FAILED(hr))
			{
			ErrorMessage(hwndDlg, TEXT("CoInitialize"), hr);
			break;
			}

                    // initialize security layer with our choices
		    hr = CoInitializeSecurity(NULL,
                        -1,
                        NULL,
                        NULL,
			GetField(hwndDlg, IDC_SERVER_AUTHNLEVEL),
			GetField(hwndDlg, IDC_SERVER_IMPLEVEL),
                        NULL,
                        0,
			NULL);
		    if (FAILED(hr))
			{
			ErrorMessage(hwndDlg, TEXT("CoInitializeSecurity"), hr);
			break;
			}

		    hr = CoRegisterClassObject(CLSID_SecureObject, &s_ClassFactory, 
			CLSCTX_SERVER, REGCLS_MULTIPLEUSE, &s_dwRegister);
		    if (FAILED(hr))
			{
			ErrorMessage(hwndDlg, TEXT("CoRegisterClassObject"), hr);
			CoUninitialize();
			break;
			}
		    
		    // Disable Initialization Step (#1)
		    EnableWindow(GetDlgItem(hwndDlg, IDC_INITIALIZE), FALSE);
		    EnableWindow(GetDlgItem(hwndDlg, IDC_SERVER_AUTHNLEVEL), FALSE);
		    EnableWindow(GetDlgItem(hwndDlg, IDC_SERVER_IMPLEVEL), FALSE);

		    // Enable Object Viewing Steps (#2)
		    // (choosing a valid object in the list box will enable the
		    //  other controls)
		    EnableWindow(GetDlgItem(hwndDlg, IDC_OBJECTS), TRUE);

		    s_fInitialized = TRUE;
		    break;

		case IDC_OBJECTS:
		    {
		    int     iCur;

		    if (HIWORD(wParam) != CBN_SELCHANGE)
			break;

		    // a different object was chosen, or a property has changed.
		    // retrieve the object's pointer from the item-data of the
		    // current list-box item and update the UI.
		    iCur = SendMessage(GetDlgItem(hwndDlg, IDC_OBJECTS),
			CB_GETCURSEL, 0, 0);
		    if (iCur == CB_ERR)
			s_pcso = NULL;
		    else
			{
			s_pcso = (CSecureObject*)SendMessage(GetDlgItem(hwndDlg, IDC_OBJECTS),
			    CB_GETITEMDATA, iCur, 0);
			if (s_pcso == (LPVOID)CB_ERR)
			    s_pcso = NULL;
			}

		    if (s_hbrCurrent != NULL)
			{
			DeleteObject(s_hbrCurrent);
			s_hbrCurrent = NULL;
			}
		    SetWindowText(GetDlgItem(hwndDlg, IDC_USERNAME), TEXT(""));
		    InvalidateRect(GetDlgItem(hwndDlg, IDC_CHOOSECOLOR), NULL, TRUE);
		    InvalidateRect(GetDlgItem(hwndDlg, IDC_COLOR), NULL, TRUE);
		    InvalidateRect(GetDlgItem(hwndDlg, IDC_USERNAME), NULL, TRUE);
		    InvalidateRect(GetDlgItem(hwndDlg, IDC_NOPUTCOLOR), NULL, TRUE);
		    InvalidateRect(GetDlgItem(hwndDlg, IDC_NOPUTUSERNAME), NULL, TRUE);

		    if (s_pcso != NULL)
			{
			SetWindowTextW(GetDlgItem(hwndDlg, IDC_USERNAME), s_pcso->m_rgchUserName);
			s_hbrCurrent = CreateSolidBrush(s_pcso->m_crColor);
			}

		    // enable/disable the object-specific windows
		    EnableWindow(GetDlgItem(hwndDlg, IDC_CHOOSECOLOR), s_pcso != NULL);
		    EnableWindow(GetDlgItem(hwndDlg, IDC_COLOR), s_pcso != NULL);
		    EnableWindow(GetDlgItem(hwndDlg, IDC_USERNAME), s_pcso != NULL);
		    EnableWindow(GetDlgItem(hwndDlg, IDC_NOPUTCOLOR), s_pcso != NULL);
		    EnableWindow(GetDlgItem(hwndDlg, IDC_NOPUTUSERNAME), s_pcso != NULL);
		    break;
		    }

		case IDC_NOPUTCOLOR:
		    s_pcso->m_fDenyPutColor = SendMessage(
			GetDlgItem(hwndDlg, IDC_NOPUTCOLOR), BM_GETCHECK, 0, 0);
		    break;

		case IDC_NOPUTUSERNAME:
		    s_pcso->m_fDenyPutUserName = SendMessage(
			GetDlgItem(hwndDlg, IDC_NOPUTUSERNAME), BM_GETCHECK, 0, 0);
		    break;

		case IDC_CHOOSECOLOR:
		    {
		    CHOOSECOLOR cc;

		    cc.lStructSize = sizeof(CHOOSECOLOR);
		    cc.hwndOwner = hwndDlg;
		    cc.rgbResult = s_pcso->m_crColor;
		    cc.lpCustColors = s_rgcrCustom;
		    cc.Flags = CC_RGBINIT | CC_SHOWHELP;

		    if (ChooseColor(&cc))
			{
			s_pcso->m_crColor = cc.rgbResult;
			if (s_hbrCurrent != NULL)
			    DeleteObject(s_hbrCurrent);
			s_hbrCurrent = CreateSolidBrush(cc.rgbResult);
			InvalidateRect((HWND)lParam, NULL, TRUE);
			}
		    break;
		    }

		case IDC_USERNAME:
		    {
		    static s_fDirty = FALSE;

		    if (HIWORD(wParam) == EN_CHANGE)
			{
			s_fDirty = TRUE;
			}
		    else if (HIWORD(wParam) == EN_KILLFOCUS && s_fDirty)
			{
			GetWindowTextW(GetDlgItem(hwndDlg, IDC_USERNAME),
			    s_pcso->m_rgchUserName, 20);
			s_fDirty = FALSE;
			}
		    break;
		    }
		}
	    break;

	case WM_DRAWITEM:
	    {
	    LPDRAWITEMSTRUCT lpdis = (LPDRAWITEMSTRUCT)lParam;

	    FillRect(lpdis->hDC, &lpdis->rcItem,
		s_hbrCurrent != NULL ? s_hbrCurrent : (HBRUSH)GetStockObject(WHITE_BRUSH));
	    FrameRect(lpdis->hDC, &lpdis->rcItem, (HBRUSH)GetStockObject(BLACK_BRUSH));
	    if (lpdis->itemState & ODS_SELECTED)
		InvertRect(lpdis->hDC, (LPRECT)&lpdis->rcItem);
	    if (lpdis->itemState & ODS_FOCUS)
		DrawFocusRect(lpdis->hDC, (LPRECT) &lpdis->rcItem);
	    return TRUE;
	    }
	}
    return FALSE;
}  // ServerDialogProc

// ---------------------------------------------------------------------------
// %%Function: MyServiceMain
// ---------------------------------------------------------------------------
 void
MyServiceMain(DWORD dwArgc, LPTSTR *pszArgv)
{
    HRESULT hr;
 
    s_Service.Status.dwServiceType        = SERVICE_WIN32_OWN_PROCESS;
    s_Service.Status.dwCurrentState       = SERVICE_START_PENDING;
    s_Service.Status.dwControlsAccepted   = SERVICE_ACCEPT_STOP;
    s_Service.Status.dwWin32ExitCode      = 0;
    s_Service.Status.dwServiceSpecificExitCode = 0;
    s_Service.Status.dwCheckPoint         = 0;
    s_Service.Status.dwWaitHint           = 0;

    s_Service.hStatus = RegisterServiceCtrlHandler(szServiceName, MyServiceHandler);

    if (s_Service.hStatus == NULL)
	return;

    // used to gaurd the s_fDone variable that prevents new instances
    // from being created in IClassFactory::CreateInstance during shutdown
    InitializeCriticalSection(&s_csDone);

    // event used to signal the service has stopped
    s_hevtDone = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (s_hevtDone == NULL)
	{
	ErrorMessage(NULL, TEXT("CreateEvent"), GetLastError());
	goto LErrExit;
	}

    hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    if (FAILED(hr))
	{
	ErrorMessage(NULL, TEXT("CoInitialize"), hr);
	goto LErrExit;
	}

    // the Service CLSID is used here, different from the LocalServer case
    hr = CoRegisterClassObject(CLSID_SecureObjectService, &s_ClassFactory, 
	CLSCTX_SERVER, REGCLS_MULTIPLEUSE, &s_Service.dwRegister);
	
    if (FAILED(hr))
	{
	ErrorMessage(NULL, TEXT("CoRegisterClassObject"), hr);
	CoUninitialize();
	goto LErrExit;
	}

    // Initialization complete - report running status 
    s_Service.Status.dwCurrentState       = SERVICE_RUNNING; 
    s_Service.Status.dwCheckPoint         = 0; 
    s_Service.Status.dwWaitHint           = 0; 

    // notify the service-manager that the service is running
    if (!SetServiceStatus(s_Service.hStatus, &s_Service.Status))
	ErrorMessage(NULL, TEXT("SetServiceStatus(SERVICE_RUNNING)"), GetLastError());

    // wait for the signal from MyServiceHandler:SERVICE_CONTROL_STOP
    WaitForSingleObject(s_hevtDone, INFINITE);

    CloseHandle(s_hevtDone);
    s_hevtDone = NULL;

    CoRevokeClassObject(s_Service.dwRegister);
    CoUninitialize();

    // notify the service-manager that the service has totally stopped
    s_Service.Status.dwCurrentState = SERVICE_STOPPED;
    if (!SetServiceStatus(s_Service.hStatus, &s_Service.Status))
	ErrorMessage(NULL, TEXT("SetServiceStatus(SERVICE_STOPPED)"), GetLastError());
    return;

LErrExit:
    if (s_hevtDone != NULL)
	{
	CloseHandle(s_hevtDone);
	s_hevtDone = NULL;
	}
    s_Service.Status.dwCurrentState       = SERVICE_STOPPED;
    s_Service.Status.dwCheckPoint         = 0;
    s_Service.Status.dwWaitHint           = 0;
    s_Service.Status.dwWin32ExitCode      = hr;
    s_Service.Status.dwServiceSpecificExitCode = hr;
    SetServiceStatus(s_Service.hStatus, &s_Service.Status); 
    return;
}  // MyServiceMain

// ---------------------------------------------------------------------------
// %%Function: MyServiceHandler
// ---------------------------------------------------------------------------
 void
MyServiceHandler(DWORD dwControl)
{
    switch (dwControl)
	{
	case SERVICE_CONTROL_STOP:
	    s_Service.Status.dwWin32ExitCode = 0;
	    s_Service.Status.dwCurrentState  = SERVICE_STOP_PENDING;
	    s_Service.Status.dwCheckPoint    = 0;
	    s_Service.Status.dwWaitHint      = 0;
	    if (!SetServiceStatus (s_Service.hStatus, &s_Service.Status))
		ErrorMessage(NULL, TEXT("SetServiceStatus"), GetLastError());

	    EnterCriticalSection(&s_csDone);

	    // prevent further instances from being created in IClassFactory::CreateInstance
	    s_fDone = TRUE;

	    // restart the waiting MyServiceMain thread and allow it to uninitialize and exit.
	    SetEvent(s_hevtDone);

	    LeaveCriticalSection(&s_csDone);
	    return;

	case SERVICE_CONTROL_INTERROGATE:
	    // fall out and send the current status of s_Service.Status
	    break;

	default:
	    break;
	}
 
    // send current status.
    if (!SetServiceStatus(s_Service.hStatus,  &s_Service.Status))
	ErrorMessage(NULL, TEXT("SetServiceStatus"), GetLastError());

    return; 
}  // MyServiceHandler

// ---------------------------------------------------------------------------
// %%Function: WinMain
// ---------------------------------------------------------------------------
 int WINAPI
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdLine, int nCmdShow)
{
    HRESULT hr;

    // DebugBreak();

    // parse the command-line
    if (szCmdLine)
	{
	char    *sz = strtok(szCmdLine, " \t");
	if (sz)
	    {
	    if (!strcmpi(sz, "-Embedding"))
		s_fServer = TRUE;

	    // Auto-register, display success or failure, and exit
	    else if (!strcmpi(sz, "-AutoRegister"))
		{
		if (FAutoRegister(hInstance))
		    MessageBox(GetDesktopWindow(),
			TEXT("Registered Successfully!"),
			szDescription,
			MB_OK);
		return S_OK;
		}

	    // any other argument besides interactive causes help to be displayed
	    else if (strcmpi(sz, "-Interactive"))
		{
		// MessageBox some help here
		}
	    }
	else
	    {
	    s_fService = TRUE;
	    s_fServer = TRUE;
	    }
	}

    // when launched without command-line args, run as a service, without any UI
    // and running multi-threaded
    if (s_fService)
	return StartServiceCtrlDispatcher(s_rgsteServices) ? 0 : GetLastError();

    // when launched with -Embedding, come up
    // without any UI and run multi-threaded
    else if (s_fServer)
	{
	DWORD   dwRegister;

	InitializeCriticalSection(&s_csDone);

	s_hevtDone = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (s_hevtDone == NULL)
	    return HRESULT_FROM_WIN32(GetLastError());

	hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (FAILED(hr))
	    return hr;

	hr = CoRegisterClassObject(CLSID_SecureObject, &s_ClassFactory, 
	    CLSCTX_SERVER, REGCLS_MULTIPLEUSE, &dwRegister);
	if (FAILED(hr))
	    goto LServerExit;

	// wait for all open connections to the server to go away
	WaitForSingleObject(s_hevtDone, INFINITE);

	// Destroy the event handle
	CloseHandle(s_hevtDone);
	s_hevtDone = NULL;

	// destroy the critsec used to determine when we're done
	DeleteCriticalSection(&s_csDone);

	CoRevokeClassObject(dwRegister);

LServerExit:
	CoUninitialize();
	return hr;
	}

    // when launched with -Interactive, run with UI.
    // this allows the user to adjust the exact security parameters of the
    // process and to monitor individual client objects. in this case, we will
    // eventually initialize COM (once the user selects security parameters
    // and hits the Initialize button) to use the apartment model in order
    // to synchronize calls with our UI.
    DialogBox(hInstance, MAKEINTRESOURCE(IDD_SECSVR), GetDesktopWindow(),
	(DLGPROC)ServerDialogProc);

    return 0;
} // WinMain

// EOF =======================================================================

