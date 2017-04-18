// ===========================================================================
// File: C O M P E R F . C P P
#define PURPOSE "This is the reference performance sample for COM/DCOM run on local\n\
and remote machines. This program is both a client and a server.\n\
It launches as a client by default, registering its executable as a\n\
server with COM and creating other instances of itself on a remote and\n\
local machine to be servers. A single command-line argument is allowed\n\
for a remote server name. Performance numbers in calls/sec are output\n\
in tabular form. Tests COM and IDispatch method calls with two security\n\
levels: default/min and full. Use DCOMCNFG to set default security to \n\
Authn Lvl to NONE for best comparison. Parameter sizes are varied to see\n\
effect on security levels(~4/50/4k bytes). Uses psoleperf.dll MIDL generated\n\
proxy/stub implementation. Put pscomperf.dll in same dir as this exe on\n\
all machines. Run exe on each machine to automatically register class code\n\
and proxy/stub dll. You can then run on either machine and pass a remote\n\
machine name (DNS or IP address) as single cmd-line parameter.\n\n" 

// Instructions:
// Install on one or more machines as described above. Run on command-line as "comperf".
// A single command-line argument is allowed for a remote server name. E.g.
// "comperf MyComputer" or "comperf 123.44.44.234" using IP address.
// This sample may be compiled as UNICODE or ANSI
// 
// Copyright 1996 Microsoft Corporation.  All Rights Reserved.
// ===========================================================================

// %%Includes: ---------------------------------------------------------------
#define INC_OLE2
#define STRICT
#define LOOPS 2000  // default number of test function calls
#include <windows.h>
#include <initguid.h>
#include <tchar.h>
#include <stdio.h>
#include "psperf.h" // MIDL generated header

// %%Constants: --------------------------------------------------------------
#define cServerThreads  3 // number support threads each server will generate
#define dispidICOMPerformance_Test1  11
#define dispidICOMPerformance_Test23  12
#define szTitleServer   TEXT("SERVER: COM Performance Sample")
#define szTitleClient   TEXT("COM Performance Sample")
const LARGE_INTEGER     bZero = {0,0};

// %%IDispatch support
PARAMDATA paramdata[2] = {{L"i", VT_I4},{L"bstr", VT_BSTR}}; 
METHODDATA methoddata[2] = {{L"Test1", &paramdata[0], 11, 3, CC_CDECL, 1, DISPATCH_METHOD, VT_I4},
			{L"Test23", &paramdata[1], 12, 4, CC_CDECL, 1, DISPATCH_METHOD, VT_I4}};
INTERFACEDATA interfacedata = { methoddata, 2 };

// %%Guids: ------------------------------------------------------------------
// {DDC68870-E08E-11cf-A535-00AA00615B03}
DEFINE_GUID(CLSID_CTestCOMPerformance,0xddc68870,0xe08e,0x11cf,0xa5,0x35,0x0,0xaa,0x0,0x61,0x5b,0x3);

// %%typedefs: --------------------------------------------------------------
typedef HRESULT (WINAPI *LPFNREG)();
typedef struct  perf 
{
    TCHAR   *szTest;
    float    sec[3]; // time for all three methods in ICOMPerformance
} PERF;

// %%Globals: ----------------------------------------------------------------
BOOL        vfServer = FALSE;               // is this instance a server or client?
BOOL        vfRemote = FALSE;               // is there a remote server?
HANDLE      vrghThread[cServerThreads];     // worker thread handles
DWORD       vrgtid[cServerThreads];         // worker thread id's
HANDLE      vrghEvent[cServerThreads];      // creation event for each worker
HANDLE          vhEventCliDone;
HANDLE      vhEventServer;                  // creation-complete event for class-factory
HANDLE          vhEventCliStart;
HANDLE          hKillSvr;                       // shuts down the server  
UINT        viNextThread;                   // next worker to create an object on
UINT            g_cObjectCount = 0;
LPSTREAM    vpstmMarshalling;               // scratch stream used for cross-apt marshalling
HRESULT     vhrThreadStatus;                // signals status to class-factory

LPWSTR pszDesc1 = L"String is passed to Test methd of ICOMPerformance";

PERF    vrgperfloc[] = {
    { TEXT("COM FreeToApt"), {-1.0f,-1.0f,-1.0f}},
    { TEXT("IDisp FreeToApt"), {-1.0f,-1.0f,-1.0f}},
    { TEXT("COM FreeTo Free"), {-1.0f,-1.0f,-1.0f}},
    { TEXT("IDispFreeToFree"), {-1.0f,-1.0f,-1.0f}},
    { TEXT("COM AptToApt"), {-1.0f,-1.0f,-1.0f}},
    { TEXT("IDispAptToApt"), {-1.0f,-1.0f,-1.0f}},
    { NULL, {-1.0f,-1.0f,-1.0f}} };

PERF    vrgperfrmt[] = {
    { TEXT("COM FreeToApt"), {-1.0f,-1.0f,-1.0f}},
    { TEXT("IDisp FreeToApt"), {-1.0f,-1.0f,-1.0f}},
    { TEXT("COM FreeTo Free"), {-1.0f,-1.0f,-1.0f}},
    { TEXT("IDispFreeToFree"), {-1.0f,-1.0f,-1.0f}},
    { TEXT("COM AptToApt"), {-1.0f,-1.0f,-1.0f}},
    { TEXT("IDispAptToApt"), {-1.0f,-1.0f,-1.0f}},
    { NULL, {-1.0f,-1.0f,-1.0f}} };         

// %%Prototypes: -------------------------------------------------------------
LRESULT     ServerThreadProc(LPARAM lParam);
LRESULT     ClientThreadProc(LPARAM lParam);
BOOL        FAutoRegister();
void            Message(LPTSTR szPrefix, HRESULT hr);
void            FPrintResults(void);
BOOL        AptFreeCOMTest(int cLoops);
BOOL            AptFreeAutoTest(int cLoops);
BOOL            FreeFreeCOMTest(int cLoops);
BOOL            FreeFreeAutoTest(int cLoops);
BOOL            DoTests(void);
void            Usage(void);

typedef IClientSecurity *LPCLIENTSECURITY;
typedef ICOMPerformance *LPCOMPERFORMANCE;
LPCOMPERFORMANCE pCOMApt, pCOMFree, pCOMAptRmt, pCOMFreeRmt; 
LPDISPATCH pAutoApt, pAutoFree, pAutoAptRmt, pAutoFreeRmt; 

// %%Classes: ----------------------------------------------------------------
// the class-factory object exists in the main application apartment/thread
// and is used to create instances of the worker objects on worker threads.
class CClassFactory : public IClassFactory
{
public:  
	// IClassFactory
    STDMETHODIMP            QueryInterface(REFIID iid, void **ppv);
    STDMETHODIMP_(ULONG)    AddRef(void)  { return m_cRef++; }
    STDMETHODIMP_(ULONG)    Release(void) { if (--m_cRef == 0){ delete this; return 0; } return m_cRef;}
    STDMETHODIMP            CreateInstance(LPUNKNOWN punkOuter, REFIID iid, void **ppv);
    STDMETHODIMP            LockServer(BOOL fLock);
    
    CClassFactory() { m_cRef = 1; }
private:
	ULONG   m_cRef;
};

// this worker object is simple: it simply supports IUnknown. more interesting
// interfaces can be readily added here and implemented for the worker.
class CTestCOMPerformance : public ICOMPerformance , public IDispatch
{
public:
	// IUnknown
    STDMETHODIMP            QueryInterface(REFIID iid, void **ppv);
    STDMETHODIMP_(ULONG)    AddRef(void)    { return m_cRef++; }
    STDMETHODIMP_(ULONG)    Release(void);

	// ICOMPerformance
	STDMETHODIMP                    Test1(int l);
    STDMETHODIMP                        Test23(BSTR szDesc);
	
	// IDispatch
	STDMETHODIMP  GetTypeInfoCount(unsigned int  *pcti);
    STDMETHODIMP  GetTypeInfo(unsigned int iti, LCID lcid, LPTYPEINFO  *ppti);
    STDMETHODIMP  GetIDsOfNames(REFIID riid, WCHAR  *  *rgszNames, unsigned int cNames, LCID lcid, DISPID  *pdispid);
    STDMETHODIMP  Invoke(DISPID dispidMember, REFIID riid, LCID lcid, unsigned short wFlags,
 		DISPPARAMS  *pdispparams, VARIANT  *pvarResult, EXCEPINFO  *pexcepinfo, unsigned int  *puArgErr);

    CTestCOMPerformance() { m_cRef = 1;}
private:
    ULONG   m_cRef;
};

class CTIMER 
{
  public:
    inline CTIMER()              { memset(this, 0, sizeof(*this)); }
    inline void Start()  { QueryPerformanceCounter(&m_sStart); }
    inline void Stop()   { QueryPerformanceCounter(&m_sStop); }
	inline float OutputTime()       { QueryPerformanceFrequency(&m_liFreq); 
			return (float)(( m_sStop.LowPart - m_sStart.LowPart)/(float)m_liFreq.LowPart);}
    // data members
    LARGE_INTEGER   m_sStart, m_sStop, m_liFreq;
};

// ---------------------------------------------------------------------------
// %%Function: Message
// 
//  Formats and displays a message to the console.
// ---------------------------------------------------------------------------
 void
Message(LPTSTR szPrefix, HRESULT hr)
{
    LPTSTR   szMessage;

    if (hr == S_OK)
    {
	_tprintf(szPrefix);
	_tprintf(TEXT("\n"));
	return;
    }
 
    if (HRESULT_FACILITY(hr) == FACILITY_WINDOWS)
	hr = HRESULT_CODE(hr);
 
    FormatMessage(
	FORMAT_MESSAGE_ALLOCATE_BUFFER |
	FORMAT_MESSAGE_FROM_SYSTEM,
	NULL,
	hr,
	MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), //The user default language
	(LPTSTR)&szMessage,
	0,
	NULL );

	_tprintf(TEXT("%s: %s(%lx)\n"), szPrefix, szMessage, hr);
    LocalFree(szMessage);
}  // Message

// ---------------------------------------------------------------------------
// %%Function: main 
// ---------------------------------------------------------------------------
 int __cdecl
main(int argc, CHAR **argv)
{
    HRESULT hr;
    int     i;
    DWORD   dwRegister = 0;
    COSERVERINFO csi, *pcsi=NULL;
    WCHAR wsz [MAX_PATH];
	CClassFactory   *pcf = NULL;
	LPCLASSFACTORY pcflocal = NULL;
	LPCLASSFACTORY pcfrmt = NULL;
	LPCLIENTSECURITY pclntsec = NULL; 
	TCHAR    rgch[32];      
	
	DWORD AuthnSvc, AuthzSvc, AuthnLvl, ImpLvl, Capabilities;

	
	if(!FAutoRegister())
	{
		exit(-1);
	}
	// parse command-line
    if (argc > 1)
    {
	// either started as server or passing in server name
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, argv[1], -1,
	    wsz, MAX_PATH);

		// register the CTestCOMPerformance class in the registry so
		// that the client can create instances of the server
		if((!lstrcmpW(L"-?", wsz)) || (!lstrcmpW(L"/?", wsz)))
		{
			Usage();
			return 0;
		}
		if(!lstrcmpW(L"-Embedding", wsz))
			vfServer = TRUE;
		else
		{
			// allow a machine-name as the command-line argument
			csi.dwReserved1 = 0;
			csi.pAuthInfo = NULL;
			csi.dwReserved2 = 0;
			csi.pwszName = wsz;
			pcsi = &csi;
			vfRemote = TRUE;
		}
    }
	if(vfServer)
		Message(szTitleServer, S_OK);
	else
		Message(szTitleClient, S_OK);
		
    // initialize COM
    hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    if (FAILED(hr))
    {
	Message(TEXT("CoInitializeEx"), hr);
		exit(hr);
    }

	// create an IStream to be used for marshalling interfaces
    hr = CreateStreamOnHGlobal(NULL, TRUE, &vpstmMarshalling);
    if (FAILED(hr))
	{
		Message(TEXT("CreateStreamOnHGlobal"), hr);
	goto LCleanup;
	}

    if (vfServer)
    {
	// create the threads and synchronization events
	// which the server will need
	for (i=0; i<cServerThreads; i++)
	{
	    // create the thread suspended so its event can be
	    // created using its thread-id and it will be able to
	    // use it as soon as it runs
	    vrghThread[i] = CreateThread(NULL,
		0,
		(LPTHREAD_START_ROUTINE)&ServerThreadProc,
		0,
		CREATE_SUSPENDED,
		&vrgtid[i]);
	    if (vrghThread[i] == NULL)
		{
		hr = GetLastError();
		goto LCleanup;
		}

	    // this event signals to a worker thread to create a new CTestCOMPerformance
	    wsprintf(rgch, TEXT("Thread_%d"), vrgtid[i]);
	    vrghEvent[i] = CreateEvent(NULL, FALSE, FALSE, rgch);
	    if (vrghEvent[i] == NULL)
	    {
		hr = GetLastError();
		goto LCleanup;
	    }
	    // now that the event is available, let the thread run
	    ResumeThread(vrghThread[i]);
		}
		hKillSvr = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (hKillSvr == NULL)
	    {
	    hr = GetLastError();
	    goto LCleanup;
	 }

	// this signals the status of a worker threads creation after
	// receiving its create signal via vrghEvent[i]
	vhEventServer = CreateEvent(NULL, FALSE, FALSE, TEXT("Server"));
	if (vhEventServer == NULL)
	{
	    hr = GetLastError();
	    goto LCleanup;
	}
		pcf = new CClassFactory;
		if(pcf == NULL)
	{
	    hr = E_OUTOFMEMORY;
	    goto LCleanup;
	}

	// register the class-factory with COM
	hr = CoRegisterClassObject(CLSID_CTestCOMPerformance,
	    (IUnknown *)pcf,
	    CLSCTX_LOCAL_SERVER,
	    REGCLS_MULTIPLEUSE,
	    &dwRegister);
	if (FAILED(hr))
		{
			Message(TEXT("CoRegisterClassObject"), hr);
	    goto LCleanup;
		}
		
		Message(TEXT("Server waiting"), S_OK);
		WaitForSingleObject(hKillSvr, INFINITE);
		Sleep(7000); // allow time for last Release call processing
 		delete pcf;
		pcf = NULL;
	}

    else // client case 
    {
		pCOMApt = pCOMFree = pCOMAptRmt =pCOMFreeRmt = NULL; 
		pAutoFree = pAutoFree = pAutoAptRmt = pAutoFreeRmt = NULL; 
		
		// get local class factory
	hr = CoGetClassObject(CLSID_CTestCOMPerformance, CLSCTX_LOCAL_SERVER, NULL,
			IID_IClassFactory, (void**)&pcflocal);
		if(FAILED(hr))
		{
			Message(TEXT("CoGetClassObject:"), hr);
			goto LCleanup;
		}
		// apt-model obj
		hr = pcflocal->CreateInstance(NULL, IID_ICOMPerformance, (void**)&pCOMApt);
	if (FAILED(hr))
		{
			Message(TEXT("Create Local Apt Instance:"), hr);
			goto LCleanup;
		}
		hr = pCOMApt->QueryInterface(IID_IDispatch, (void**)&pAutoApt);
		if (FAILED(hr))
		{
			Message(TEXT("QI for pAutoApt:"), hr);
			goto LCleanup;
		}
		// get free-threaded obj
		hr = pcflocal->CreateInstance(NULL, IID_ICOMPerformance, (void**)&pCOMFree);
	if (FAILED(hr))
		{
			Message(TEXT("Create Local Free Instance"), hr);
			goto LCleanup;
		}               
		hr = pCOMFree->QueryInterface(IID_IDispatch, (void**)&pAutoFree);
		if (FAILED(hr))
		{
			Message(TEXT("QI for pAutoFree"), hr);
			goto LCleanup;
		}
		hr = pcflocal->Release();
		pcflocal = NULL;
		if(vfRemote)
		{
			hr = CoGetClassObject(CLSID_CTestCOMPerformance, CLSCTX_REMOTE_SERVER, pcsi,
				IID_IClassFactory, (void**)&pcfrmt);
			if(FAILED(hr))
			{
				Message(TEXT("CoGetClassObject for remote CF"), hr);
				vfRemote = FALSE;
				goto LContinue;
			}
			// apt-model obj
			hr = pcfrmt->CreateInstance(NULL, IID_ICOMPerformance, (void**)&pCOMAptRmt);
			if (FAILED(hr))
			{
				Message(TEXT("Create Remote Instance"), hr);
				goto LCleanup;
			}
			hr = pCOMAptRmt->QueryInterface(IID_IDispatch, (void**)&pAutoAptRmt);
			if (FAILED(hr))
			{
				Message(TEXT("QI for pAutoAptFreeRmt"), hr);
				goto LCleanup;
			}
			// get free-threaded obj
			hr = pcfrmt->CreateInstance(NULL, IID_ICOMPerformance, (void**)&pCOMFreeRmt);
			if (FAILED(hr))
			{
				Message(TEXT("Create Remote Free Instance"), hr);
				goto LCleanup;
			}
			hr = pCOMFreeRmt->QueryInterface(IID_IDispatch, (void**)&pAutoFreeRmt);
			if (FAILED(hr))
			{
				Message(TEXT("QI for pAutoFreeFreeRmt"), hr);
				goto LCleanup;
			}
			hr = pcfrmt->Release();
			pcfrmt = NULL;
		}
LContinue:
		// create apartment thread for client
		DWORD   dwClienttid;
	// create the thread suspended so its event can be
	// created using its thread-id and it will be able to
	// use it as soon as it runs
	HANDLE hClientThread = CreateThread(NULL,
	    0,
	    (LPTHREAD_START_ROUTINE)&ClientThreadProc,
	    0,
	    CREATE_SUSPENDED,
	    &dwClienttid);
	if (hClientThread == NULL)
	{
	    hr = GetLastError();
			goto LCleanup;
	}
		wsprintf(rgch, TEXT("Thread_%d"), dwClienttid);
	
		vhEventCliStart = CreateEvent(NULL, FALSE, FALSE, rgch);
	if (vhEventCliStart == NULL)
	{
	    hr = GetLastError();
	    goto LCleanup;
	}
		vhEventCliDone = CreateEvent(NULL, FALSE, FALSE, NULL);
	if (vhEventCliDone == NULL)
	{
	    hr = GetLastError();
	    goto LCleanup;
	}       
		// Marshall local apt thread
		hr = vpstmMarshalling->Seek(bZero, STREAM_SEEK_SET, NULL);
	if (FAILED(hr))
	    throw hr;
	hr = CoMarshalInterface(vpstmMarshalling,
	    IID_IUnknown,
	    (ICOMPerformance*)pCOMApt,
	    MSHCTX_INPROC,
	    NULL,
	    MSHLFLAGS_NORMAL);
	if (FAILED(hr))
	    throw hr;
		// now that the event is available, let the thread run
	ResumeThread(hClientThread);
		SetEvent(vhEventCliStart);
		WaitForSingleObject(vhEventCliDone, INFINITE);
		
		if(vfRemote && NULL != pCOMAptRmt)
		{
			// Marshall local apt thread
			hr = vpstmMarshalling->Seek(bZero, STREAM_SEEK_SET, NULL);
			if (FAILED(hr))
				throw hr;
			hr = CoMarshalInterface(vpstmMarshalling,
				IID_IUnknown,
				(ICOMPerformance*)pCOMAptRmt,
				MSHCTX_INPROC,
				NULL,
				MSHLFLAGS_NORMAL);
			if (FAILED(hr))
				throw hr;
			SetEvent(vhEventCliStart);
			WaitForSingleObject(vhEventCliDone, INFINITE);
		}
		
		// Test
		_tprintf(TEXT("Output in Calls per sec\n"));
		_tprintf(TEXT("DEF Sec:\t\tLOCAL\t\t\tREMOTE\n"));
		// Do all tests
		if(!DoTests())
			goto LCleanup;
		// Up security on proxies
		// Get current security
		hr = pCOMApt->QueryInterface(IID_IClientSecurity, (void**)&pclntsec);
		hr = pclntsec->QueryBlanket(pCOMApt, &AuthnSvc, &AuthzSvc, NULL, &AuthnLvl, &ImpLvl, NULL,
			&Capabilities);

		_tprintf(TEXT("Increasing local security from AuthnLvl:%d  ImpLvl:%d\n"), AuthnLvl, ImpLvl);

		hr = pclntsec->SetBlanket(pCOMApt, AuthnSvc, AuthzSvc, NULL, 6,
				4, NULL, Capabilities);
		hr = pclntsec->QueryBlanket(pCOMApt, &AuthnSvc, &AuthzSvc, NULL, &AuthnLvl, &ImpLvl, NULL,
			&Capabilities);

		_tprintf(TEXT("Local security is now AuthnLvl:%d  ImpLvl:%d\n"), AuthnLvl, ImpLvl);

		pclntsec->Release();
		pclntsec = NULL;
		hr = pCOMFree->QueryInterface(IID_IClientSecurity, (void**)&pclntsec);  
		hr = pclntsec->SetBlanket(pCOMFree, AuthnSvc, AuthzSvc, NULL, 6,
				4, NULL, Capabilities);
		pclntsec->Release();
		pclntsec = NULL;
		hr = pAutoApt->QueryInterface(IID_IClientSecurity, (void**)&pclntsec);  
		hr = pclntsec->SetBlanket(pAutoApt, AuthnSvc, AuthzSvc, NULL, 6,
				4, NULL, Capabilities);
		pclntsec->Release();
		pclntsec = NULL;
		hr = pAutoFree->QueryInterface(IID_IClientSecurity, (void**)&pclntsec); 
		hr = pclntsec->SetBlanket(pAutoFree, AuthnSvc, AuthzSvc, NULL, 6,
				4, NULL, Capabilities);
		pclntsec->Release();
		pclntsec = NULL;
		if(vfRemote)
		{
			hr = pCOMAptRmt->QueryInterface(IID_IClientSecurity, (void**)&pclntsec);        
			hr = pclntsec->QueryBlanket(pCOMAptRmt, &AuthnSvc, &AuthzSvc, NULL, &AuthnLvl, &ImpLvl, NULL,
			&Capabilities);

			_tprintf(TEXT("Increasing remote security from AuthnLvl:%d  ImpLvl:%d\n"), AuthnLvl, ImpLvl);

			hr = pclntsec->SetBlanket(pCOMAptRmt, AuthnSvc, AuthzSvc, NULL, 6,
				4, NULL, Capabilities);

			_tprintf(TEXT("Remote security is now AuthnLvl:%d  ImpLvl:%d\n"), AuthnLvl, ImpLvl);

			pclntsec->Release();
			pclntsec = NULL;
			hr = pCOMFreeRmt->QueryInterface(IID_IClientSecurity, (void**)&pclntsec);       
			hr = pclntsec->SetBlanket(pCOMFreeRmt, AuthnSvc, AuthzSvc, NULL, 6,
				4, NULL, Capabilities);
			pclntsec->Release();
			pclntsec = NULL;
			hr = pAutoAptRmt->QueryInterface(IID_IClientSecurity, (void**)&pclntsec);       
			hr = pclntsec->SetBlanket(pAutoAptRmt, AuthnSvc, AuthzSvc, NULL, 6,
				4, NULL, Capabilities);
			pclntsec->Release();
			pclntsec = NULL;
			hr = pAutoFreeRmt->QueryInterface(IID_IClientSecurity, (void**)&pclntsec);
			hr = pclntsec->SetBlanket(pAutoFreeRmt, AuthnSvc, AuthzSvc, NULL, 6,
				4, NULL, Capabilities);
			pclntsec->Release();
			pclntsec = NULL;
		}
		// Do all tests with FULL sec
		// Apt to Apt first
		// Marshall local apt thread
		hr = vpstmMarshalling->Seek(bZero, STREAM_SEEK_SET, NULL);
	if (FAILED(hr))
	    throw hr;
	hr = CoMarshalInterface(vpstmMarshalling,
	    IID_IUnknown,
	    (ICOMPerformance*)pCOMApt,
	    MSHCTX_INPROC,
	    NULL,
	    MSHLFLAGS_NORMAL);
	if (FAILED(hr))
	    throw hr;
		// now that the event is available, let the thread run
	ResumeThread(hClientThread);
		SetEvent(vhEventCliStart);
		WaitForSingleObject(vhEventCliDone, INFINITE);
		
		if(vfRemote && NULL != pCOMAptRmt)
		{
			// Marshall local apt thread
			hr = vpstmMarshalling->Seek(bZero, STREAM_SEEK_SET, NULL);
			if (FAILED(hr))
				throw hr;
			hr = CoMarshalInterface(vpstmMarshalling,
				IID_IUnknown,
				(ICOMPerformance*)pCOMAptRmt,
				MSHCTX_INPROC,
				NULL,
				MSHLFLAGS_NORMAL);
			if (FAILED(hr))
				throw hr;
			SetEvent(vhEventCliStart);
			WaitForSingleObject(vhEventCliDone, INFINITE);
		}
		_tprintf(TEXT("Modified Sec:\t\tLOCAL\t\t\tREMOTE\n"));
		DoTests();
    }
LCleanup:
	if (vpstmMarshalling != NULL)
			vpstmMarshalling->Release();
	if (vfServer)
    {
		// we explicitly don't clean up threads and events
		if (dwRegister != 0)
			CoRevokeClassObject(dwRegister);
		if(NULL != pcf)
			delete pcf;
    }
    else // client
	{
		// client case: release objects
		if(NULL != pcflocal)
			hr = pcflocal->Release();
		if(NULL != pcfrmt)
			hr = pcfrmt->Release();
		if(NULL != pCOMFree)
			hr = pCOMFree->Release();
		if(NULL != pAutoFree)
			hr = pAutoFree->Release();
		if(NULL != pCOMApt)
			hr = pCOMApt->Release();
		if(NULL != pAutoApt)
			hr = pAutoApt->Release();
		if(NULL != pCOMFreeRmt)
			hr = pCOMFreeRmt->Release();
		if(NULL != pAutoFreeRmt)
			hr = pAutoFreeRmt->Release();
		if(NULL != pCOMAptRmt)
			hr = pCOMAptRmt->Release();
		if(NULL != pAutoAptRmt)
			hr = pAutoAptRmt->Release();
    }
    CoUninitialize();
    return hr;
}  // main

// ---------------------------------------------------------------------------
// %%Function: FAutoRegister
//  Registers the CTestCOMPerformance class in the registry.
// ---------------------------------------------------------------------------
 BOOL
FAutoRegister()
{
    static TCHAR szClassDesc[] = TEXT("COM Performance Sample");
	static TCHAR szCLSIDEntry[] = TEXT("CLSID\\{DDC68870-E08E-11cf-A535-00AA00615B03}");
    TCHAR       szBuf[512];
    TCHAR       szPath[512];
    HKEY        hkeyT = NULL;


	HRESULT hr;
	LPFNREG lpfn = NULL;
	HINSTANCE hLib = NULL;

    // register class code
    if ((RegSetValue(HKEY_CLASSES_ROOT, szCLSIDEntry, REG_SZ, szClassDesc,
	    lstrlen(szClassDesc)) != ERROR_SUCCESS) ||
	(RegCreateKey(HKEY_CLASSES_ROOT, szCLSIDEntry, &hkeyT)
	    != ERROR_SUCCESS) ||
	!GetModuleFileName(NULL, szBuf, sizeof(szBuf)))
	return FALSE;
    lstrcpy(szPath, szBuf);
    if (RegSetValue(hkeyT, TEXT("LocalServer32"), REG_SZ, szBuf, lstrlen(szBuf))
	    != ERROR_SUCCESS)
	goto LErrExit;
    RegCloseKey(hkeyT);
	hkeyT = NULL;
	// Register the ICOMPerformance MIDL-generated proxy-stub component
	hLib = LoadLibrary(TEXT("psperf.dll"));
	if (NULL == hLib)
	{	
		goto  LErrExit;
	}
	// Find entry point.
	lpfn = (LPFNREG)GetProcAddress(hLib, TEXT("DllRegisterServer"));
	if (lpfn == NULL)
	{
		//Message(_T("Couldn't find entry point in DLL"), S_OK); //unable to locate entry point
		goto LErrExit;
	}
	hr = (*lpfn)();

	FreeLibrary(hLib);
	if(SUCCEEDED(hr))
		return TRUE;
LErrExit:
	if(NULL != hkeyT)
		RegCloseKey(hkeyT);
	return FALSE;
}  // FAutoRegister

// ===========================================================================
//                          C C L A S S F A C T O R Y
// ===========================================================================

// ---------------------------------------------------------------------------
// %%Function: CClassFactory::QueryInterface
//  Returns a new reference of the specified iid-type to a CClassFactory.
// ---------------------------------------------------------------------------
 STDMETHODIMP
CClassFactory::QueryInterface(REFIID iid, void **ppv)
{
    *ppv = NULL;

    if (iid == IID_IClassFactory || iid == IID_IUnknown)
	{
	*ppv = (IClassFactory *)this;
	}
    if (*ppv != NULL)
	{
	AddRef();
	return S_OK;
	}
    return E_NOINTERFACE;
}  // CClassFactory::QueryInterface

// ---------------------------------------------------------------------------
// %%Function: CClassFactory::CreateInstance
//  Creates a new instance of a CTestCOMPerformance on the next worker thread.
// ---------------------------------------------------------------------------
 STDMETHODIMP
CClassFactory::CreateInstance(LPUNKNOWN punkOuter, REFIID iid, void **ppv)
{
    LPUNKNOWN   punk;
    HRESULT     hr;

    *ppv = NULL;
    if (punkOuter != NULL)
	return CLASS_E_NOAGGREGATION;

    // trigger the worker thread that we want to create an object
    SetEvent(vrghEvent[viNextThread]);

    // now wait for the object to signal its completion
    WaitForSingleObject(vhEventServer, INFINITE);

    // once the worker thread signals completion, vhrThreadStatus
    // lets us know if the creation process was successful, and if
    // vpstmMarshalling creates a marshalled interface pointer
    if (FAILED(vhrThreadStatus))
	return vhrThreadStatus;

    // unmarshal an IUnknown from the scratch stream. if unmarshaling
    // fails, it takes care of releasing the object inside the marshal-data
    hr = vpstmMarshalling->Seek(bZero, STREAM_SEEK_SET, NULL);
    if (FAILED(hr))
	return hr;
    hr = CoUnmarshalInterface(vpstmMarshalling, IID_IUnknown, (void **)&punk);
    if (FAILED(hr))
	return hr;

    // get a reference to the interface asked for
    hr = punk->QueryInterface(iid, ppv);
    punk->Release();
	++g_cObjectCount;
    viNextThread++;
//    viNextThread %= cServerThreads;

    return hr;
}  // CClassFactory::CreateInstance

 STDMETHODIMP
CClassFactory::LockServer(BOOL fLock)
{
    // there's no need to support this for this sample
    return E_FAIL;
}  // CClassFactory::LockServer


// ===========================================================================
//                               C O B J E C T
// ===========================================================================

// ---------------------------------------------------------------------------
// %%Function: ServerThreadProc
//  The worker thread function. Handles messages for objects of its thread/apt
// and creates new objects.
// ---------------------------------------------------------------------------
 LRESULT
ServerThreadProc(LPARAM lParam)
{
    HRESULT hr;
    MSG     msg;
    int     iThread;

    // figure out which thread this is: it needs its synchronization event
    for (iThread=0; iThread<cServerThreads; iThread++)
	{
	if (vrgtid[iThread] == GetCurrentThreadId())
	    break;
	}
    if (iThread==cServerThreads)
	return E_UNEXPECTED;

    // initialize COM
	if((0 == iThread) || (2 == iThread))
	{
		hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
		Message(TEXT("Apartment Thread"), hr);
	}
	else
	{
		hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
		Message(TEXT("Free-threaded Model"), hr);
	}
    if (FAILED(hr))
	{
	MessageBeep(0);
	return hr;
	}

    // apartment message/event loop
    // here worker message loops last forever. in situations without a
    // static number of worker threads, the loop could easily be terminated by
    // WM_QUITs sent from the main thread which might manage the worker thread
    // pool more carefully.
    while (TRUE)
	{
	DWORD dwWaitResult;

	// wait for any message sent or posted to this queue
	// or for one of the passed handles to become signaled
	dwWaitResult = MsgWaitForMultipleObjects(1, &vrghEvent[iThread],
	    FALSE, INFINITE, QS_ALLINPUT);

	// result tells us the type of event we have:
	// a message or a signaled handle

	// if there are one or more messages in the queue ...
	if (dwWaitResult == (WAIT_OBJECT_0 + 1))
	    {
	    // dispatch all of the messages in this next loop
	    // (here is where we'd check for WM_QUITs to end this
	    // worker thread if we wanted to)
	    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		DispatchMessage(&msg);
	    }
	else
	    {
	    // this thread was signaled to create a new object
	    try
		{
		LPUNKNOWN   punk;

		// create a new CTestCOMPerformance
		punk = (ICOMPerformance *)new CTestCOMPerformance;
		if (punk == NULL)
		    throw E_OUTOFMEMORY;

		hr = vpstmMarshalling->Seek(bZero, STREAM_SEEK_SET, NULL);
		if (FAILED(hr))
		    throw hr;
		hr = CoMarshalInterface(vpstmMarshalling,
		    IID_IUnknown,
		    punk,
		    MSHCTX_INPROC,
		    NULL,
		    MSHLFLAGS_NORMAL);
		if (FAILED(hr))
		    throw hr;

		// punk is now referenced by its marshal-data in vpstmMarshalling.
		// we release our local reference here so the unmarshaller will
		// have the sole reference. a common mistake is to forget this
		// release and end up with orphaned objects in the server.
		punk->Release();
		vhrThreadStatus = S_OK;
		}
	    catch (HRESULT hr)
		{
		vhrThreadStatus = hr;
		}
	    SetEvent(vhEventServer);
	    }

	}

    CoUninitialize();
    return msg.wParam;
}  // ServerThreadProc

// ---------------------------------------------------------------------------
// %%Function: ServerThreadProc
//  The worker thread function. Handles messages for objects of its thread/apt
// and creates new objects.
// ---------------------------------------------------------------------------
 LRESULT
ClientThreadProc(LPARAM lParam)
{
    HRESULT hr;
    MSG     msg;
	UINT cCount = 0;
	hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
    if (FAILED(hr))
    {
	return hr;
    }
    while (TRUE)
    {
	DWORD dwWaitResult;

	// wait for any message sent or posted to this queue
	// or for one of the passed handles to become signaled
	dwWaitResult = MsgWaitForMultipleObjectsEx(1, &vhEventCliStart,
	    INFINITE, QS_SENDMESSAGE, 0);
		
	// result tells us the type of event we have:
	// a message or a signaled handle

	// if there are one or more messages in the queue ...
	if (dwWaitResult == (WAIT_OBJECT_0 + 1))
	{
	    // dispatch all of the messages in this next loop
	    // (here is where we'd check for WM_QUITs to end this
	    // worker thread if we wanted to)
	    while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		DispatchMessage(&msg);
	}
	else
	{
	    // this thread was signaled to test Apt to Apt
	    try
	    {
			//Message(TEXT("Testing Apt to Apt"), hr);
			LPUNKNOWN   punk;
			LPDISPATCH   pdisp;
			// unmarshal an IUnknown from the scratch stream. if unmarshaling
			// fails, it takes care of releasing the object inside the marshal-data
			hr = vpstmMarshalling->Seek(bZero, STREAM_SEEK_SET, NULL);
			if (FAILED(hr))
				return hr;
			hr = CoUnmarshalInterface(vpstmMarshalling, IID_IUnknown, (void **)&punk);
			if (FAILED(hr))
				return hr;
			ICOMPerformance *pcomperf = NULL;
			// get a reference to ICOMPerformance and IDispatch interface
			hr = punk->QueryInterface(IID_ICOMPerformance, (void**)&pcomperf);
			hr = punk->QueryInterface(IID_IDispatch, (void**)&pdisp);
			LONG    i, k;
			CTIMER  tmElapsed;
			BSTR bstr1, bstr2;
			bstr1 = SysAllocString(pszDesc1);
			bstr2 = SysAllocStringByteLen((const char *)pszDesc1, 4096);
			// Test1
			tmElapsed.Start();
			for (i=0; i<LOOPS; i++)
				k = (LONG)pcomperf->Test1(i);
			tmElapsed.Stop();
			if(cCount && vfRemote)
				vrgperfrmt[4].sec[0] = tmElapsed.OutputTime();
			else 
				vrgperfloc[4].sec[0] = tmElapsed.OutputTime();
			// Test2
			tmElapsed.Start();
			for (i=0; i<LOOPS; i++)
				k = (LONG)pcomperf->Test23(bstr1);
			tmElapsed.Stop();
			if(cCount && vfRemote)
				vrgperfrmt[4].sec[1] = tmElapsed.OutputTime();
			else
				vrgperfloc[4].sec[1] = tmElapsed.OutputTime();
			// Test3
			tmElapsed.Start();
			for (i=0; i<LOOPS; i++)
				k = (LONG)pcomperf->Test23(bstr2);
			tmElapsed.Stop();
			if(cCount && vfRemote)
				vrgperfrmt[4].sec[2] = tmElapsed.OutputTime();
			else
				vrgperfloc[4].sec[2] = tmElapsed.OutputTime();
			// Now IDispatch
			VARIANTARG  rgvt[1];
			DISPPARAMS  dispparams = { rgvt, NULL, 1, 0 };
			EXCEPINFO  excepinfo;
			
			VARIANT vtResult;
			UINT    argerr;
			// Test1
			tmElapsed.Start();
			V_VT(&vtResult) = VT_HRESULT;
			for (i=0; i<LOOPS; i++)
			{
				V_VT(&rgvt[0]) = VT_I4;
				V_I4(&rgvt[0]) = i;
				hr = pdisp->Invoke(dispidICOMPerformance_Test1, IID_NULL, 0, DISPATCH_METHOD, &dispparams,
					&vtResult, &excepinfo, &argerr);
				k = V_I4(&vtResult);
			}
			tmElapsed.Stop();
			if(cCount && vfRemote)
				vrgperfrmt[5].sec[0] = tmElapsed.OutputTime();
			else
				vrgperfloc[5].sec[0] = tmElapsed.OutputTime();
			// Test2
			tmElapsed.Start();
			V_VT(&vtResult) = VT_HRESULT;
			for (i=0; i<LOOPS; i++)
			{
				V_VT(&rgvt[0]) = VT_BSTR;
				V_BSTR(&rgvt[0]) = bstr1;       
				hr = pdisp->Invoke(dispidICOMPerformance_Test23, IID_NULL, 0, DISPATCH_METHOD, &dispparams,
					&vtResult, &excepinfo, &argerr);
				k = V_I4(&vtResult);
			}
			tmElapsed.Stop();
			if(cCount && vfRemote)
				vrgperfrmt[5].sec[1] = tmElapsed.OutputTime();
			else
				vrgperfloc[5].sec[1] = tmElapsed.OutputTime();
			// Test3
			tmElapsed.Start();
			V_VT(&vtResult) = VT_HRESULT;
			for (i=0; i<LOOPS; i++)
			{
				V_VT(&rgvt[0]) = VT_BSTR;
				V_BSTR(&rgvt[0]) = bstr2;
				hr = pdisp->Invoke(dispidICOMPerformance_Test23, IID_NULL, 0, DISPATCH_METHOD, &dispparams,
					&vtResult, &excepinfo, &argerr);
				k = V_I4(&vtResult);
			}
			tmElapsed.Stop();
			if(cCount && vfRemote)
				vrgperfrmt[5].sec[2] = tmElapsed.OutputTime();
			else
				vrgperfloc[5].sec[2] = tmElapsed.OutputTime();
			SysFreeString(bstr1);
			SysFreeString(bstr2);
			hr = pcomperf->Release();
			hr = pdisp->Release();
			hr = punk->Release();

			vhrThreadStatus = S_OK;
	    }
	    catch (HRESULT hr)
	    {
		vhrThreadStatus = hr;
			}
	    SetEvent(vhEventCliDone);
			if(cCount)
				--cCount;
			else
				++cCount;
	}
    }
    CoUninitialize();
    return msg.wParam;
}  // ClientThreadProc
// ---------------------------------------------------------------------------
// %%Function: CTestCOMPerformance::QueryInterface
//  Returns a new reference of the specified iid-type to a CTestCOMPerformance.
// ---------------------------------------------------------------------------
 STDMETHODIMP
CTestCOMPerformance::QueryInterface(REFIID iid, void **ppv)
{
    *ppv = NULL;

    if (iid == IID_IUnknown || iid == IID_ICOMPerformance)
    {
	*ppv = (ICOMPerformance *)this;
    }
	else if (iid == IID_IDispatch)
		*ppv = (IDispatch *)this;
    if (*ppv == NULL)
    {
		return E_NOINTERFACE;
    }
	AddRef();
    return S_OK;
}  // CTestCOMPerformance::QueryInterface

// ---------------------------------------------------------------------------
// %%Function: CTestCOMPerformance::Release
//  Handles releases of references to a CTestCOMPerformance. Purpose here is to have code
// which alters the global state which is displayed in the servers UI.
// ---------------------------------------------------------------------------
 STDMETHODIMP_(ULONG)
CTestCOMPerformance::Release(void)
{
	if (--m_cRef == 0)
    {
		--g_cObjectCount;
		delete this;
	Message(TEXT("Object Deleted"), S_OK);
		if(g_cObjectCount == 0) SetEvent(hKillSvr);
		return 0;
    }
    return m_cRef;
}  // CTestCOMPerformance::Release

// ---------------------------------------------------------------------------
// %%Function: CTestCOMPerformance::GetTypeInfoCount
// ---------------------------------------------------------------------------
 STDMETHODIMP
CTestCOMPerformance::GetTypeInfoCount(UINT  *pctInfo)
{
    *pctInfo = 1;
    return S_OK;
}  // CTestCOMPerformance::GetTypeInfoCount

// ---------------------------------------------------------------------------
// %%Function: CTestCOMPerformance::GetTypeInfo
// ---------------------------------------------------------------------------
 STDMETHODIMP
CTestCOMPerformance::GetTypeInfo(unsigned int itInfo, LCID lcid, LPTYPEINFO  *ppti)
{
	HRESULT hr;

    if (ppti == NULL)
		return E_POINTER;
	hr = CreateDispTypeInfo( &interfacedata, 0, ppti);
    return hr;
}  // CTestCOMPerformance::GetTypeInfo

// ---------------------------------------------------------------------------
// %%Function: CTestCOMPerformance::GetIDsOfNames
// ---------------------------------------------------------------------------
 STDMETHODIMP
CTestCOMPerformance::GetIDsOfNames(REFIID riid, WCHAR  *  *rgszNames, unsigned int cNames, LCID lcid, DISPID  *pdispid)
{
    return E_NOTIMPL;
}  // CTestCOMPerformance::GetIDsOfNames

// ---------------------------------------------------------------------------
// %%Function: CTestCOMPerformance::Invoke
// ---------------------------------------------------------------------------
 STDMETHODIMP
CTestCOMPerformance::Invoke(DISPID dispidMember, REFIID riid, LCID lcid, unsigned short wFlags, DISPPARAMS  *pdispparams, VARIANT  *pvarResult,
		  EXCEPINFO  *pexcepinfo, unsigned int  *puArgErr)
{
    LPTYPEINFO pti = NULL;
	HRESULT hr = GetTypeInfo(0, lcid, &pti);
	if(FAILED(hr))
		return hr;

	hr =  pti->Invoke((ICOMPerformance*)this, dispidMember,
	    wFlags, pdispparams, pvarResult,
	    pexcepinfo, puArgErr);
	hr = pti->Release();
	return hr;
}  // CTestCOMPerformance::Invoke


 STDMETHODIMP                   
CTestCOMPerformance::Test1(int l)
{
	 return S_OK;
}

 STDMETHODIMP                   
CTestCOMPerformance::Test23(BSTR bstr)
{
	 return S_OK;
}

// Tests
 BOOL        
AptFreeCOMTest(int cLoops)
{
	LONG    i, k;
    CTIMER  tmElapsed;
	BSTR bstr1, bstr2;
	bstr1 = SysAllocString(pszDesc1);
	bstr2 = SysAllocStringByteLen((const char *)pszDesc1, 4096);
	// Local
	// Test1
    tmElapsed.Start();
    for (i=0; i<cLoops; i++)
		k = (LONG)pCOMApt->Test1(i);
    tmElapsed.Stop();
    vrgperfloc[0].sec[0] = tmElapsed.OutputTime();
	// Test2
    tmElapsed.Start();
    for (i=0; i<cLoops; i++)
		k = (LONG)pCOMApt->Test23(bstr1);
    tmElapsed.Stop();
    vrgperfloc[0].sec[1] = tmElapsed.OutputTime();
	// Test3
    tmElapsed.Start();
	for (i=0; i<cLoops; i++)
		k = (LONG)pCOMApt->Test23(bstr2);
    tmElapsed.Stop();
    vrgperfloc[0].sec[2] = tmElapsed.OutputTime();
	
	// Remote
	if(vfRemote)
	{
		tmElapsed.Start();
		for (i=0; i<cLoops; i++)
			k = (LONG)pCOMAptRmt->Test1(i);
		tmElapsed.Stop();
		vrgperfrmt[0].sec[0] = tmElapsed.OutputTime();
		// Test2
		tmElapsed.Start();
		for (i=0; i<cLoops; i++)
			k = (LONG)pCOMAptRmt->Test23(bstr1);
		tmElapsed.Stop();
		vrgperfrmt[0].sec[1] = tmElapsed.OutputTime();
		// Test3
		tmElapsed.Start();
		for (i=0; i<cLoops; i++)
			k = (LONG)pCOMAptRmt->Test23(bstr2);
		tmElapsed.Stop();
		vrgperfrmt[0].sec[2] = tmElapsed.OutputTime();

	}
	SysFreeString(bstr1);
	SysFreeString(bstr2);
	return TRUE;
}

 BOOL           
AptFreeAutoTest(int cLoops)
{
	HRESULT hr;
	static VARIANTARG  rgvt[1];
    static DISPPARAMS  dispparams = { rgvt, NULL, 1, 0 };
    static EXCEPINFO  excepinfo;
    VARIANT vtResult;
    UINT    argerr;
    LONG    i, k;
    CTIMER  tmElapsed;
	BSTR bstr1, bstr2;
	bstr1 = SysAllocString(pszDesc1);
	bstr2 = SysAllocStringByteLen((const char *)pszDesc1, 4096);

	// Test1
    tmElapsed.Start();
    V_VT(&vtResult) = VT_HRESULT;
    for (i=0; i<cLoops; i++)
	{
		V_VT(&rgvt[0]) = VT_I4;
		V_I4(&rgvt[0]) = i;
		hr = pAutoApt->Invoke(dispidICOMPerformance_Test1, IID_NULL, 0, DISPATCH_METHOD, &dispparams,
			&vtResult, &excepinfo, &argerr);
		k = V_I4(&vtResult);
	}
    tmElapsed.Stop();
    vrgperfloc[1].sec[0] = tmElapsed.OutputTime();
	// Test2
	tmElapsed.Start();
    V_VT(&vtResult) = VT_HRESULT;
    for (i=0; i<cLoops; i++)
	{
		V_VT(&rgvt[0]) = VT_BSTR;
		V_BSTR(&rgvt[0]) = bstr1;       
		hr = pAutoApt->Invoke(dispidICOMPerformance_Test23, IID_NULL, 0, DISPATCH_METHOD, &dispparams,
			&vtResult, &excepinfo, &argerr);
		k = V_I4(&vtResult);
	}
    tmElapsed.Stop();
    vrgperfloc[1].sec[1] = tmElapsed.OutputTime();
	// Test3
	tmElapsed.Start();
    V_VT(&vtResult) = VT_HRESULT;
    for (i=0; i<cLoops; i++)
	{
		V_VT(&rgvt[0]) = VT_BSTR;
		V_BSTR(&rgvt[0]) = bstr2;
		hr = pAutoApt->Invoke(dispidICOMPerformance_Test23, IID_NULL, 0, DISPATCH_METHOD, &dispparams,
			&vtResult, &excepinfo, &argerr);
		k = V_I4(&vtResult);
	}
    tmElapsed.Stop();
    vrgperfloc[1].sec[2] = tmElapsed.OutputTime();
	// Remote
	if(vfRemote)
	{
		// Test1
		tmElapsed.Start();
		V_VT(&vtResult) = VT_HRESULT;
		for (i=0; i<cLoops; i++)
		{
			V_VT(&rgvt[0]) = VT_I4;
			V_I4(&rgvt[0]) = i;
			hr = pAutoAptRmt->Invoke(dispidICOMPerformance_Test1, IID_NULL, 0, DISPATCH_METHOD, &dispparams,
				&vtResult, &excepinfo, &argerr);
			k = V_I4(&vtResult);
		}
		tmElapsed.Stop();
		vrgperfrmt[1].sec[0] = tmElapsed.OutputTime();
		// Test2
		tmElapsed.Start();
		V_VT(&vtResult) = VT_HRESULT;
		for (i=0; i<cLoops; i++)
		{
			V_VT(&rgvt[0]) = VT_BSTR;
			V_BSTR(&rgvt[0]) = bstr1;       
			hr = pAutoAptRmt->Invoke(dispidICOMPerformance_Test23, IID_NULL, 0, DISPATCH_METHOD, &dispparams,
				&vtResult, &excepinfo, &argerr);
			k = V_I4(&vtResult);
		}
		tmElapsed.Stop();
		vrgperfrmt[1].sec[1] = tmElapsed.OutputTime();
		// Test3
		tmElapsed.Start();
		V_VT(&vtResult) = VT_HRESULT;
		for (i=0; i<cLoops; i++)
		{
			V_VT(&rgvt[0]) = VT_BSTR;
			V_BSTR(&rgvt[0]) = bstr2;
			hr = pAutoAptRmt->Invoke(dispidICOMPerformance_Test23, IID_NULL, 0, DISPATCH_METHOD, &dispparams,
				&vtResult, &excepinfo, &argerr);
			k = V_I4(&vtResult);
		}
		tmElapsed.Stop();
		vrgperfrmt[1].sec[2] = tmElapsed.OutputTime();
	}

	SysFreeString(bstr1);
	SysFreeString(bstr2);
	return TRUE;
}

 BOOL           
FreeFreeCOMTest(int cLoops)
{
	LONG    i, k;
    CTIMER  tmElapsed;
	BSTR bstr1, bstr2;
	bstr1 = SysAllocString(pszDesc1);
	bstr2 = SysAllocStringByteLen((const char *)pszDesc1, 4096);

	// Test1
    tmElapsed.Start();
    for (i=0; i<cLoops; i++)
		k = (LONG)pCOMFree->Test1(i);
    tmElapsed.Stop();
    vrgperfloc[2].sec[0] = tmElapsed.OutputTime();
	// Test2
    tmElapsed.Start();
    for (i=0; i<cLoops; i++)
		k = (LONG)pCOMFree->Test23(bstr1);
    tmElapsed.Stop();
    vrgperfloc[2].sec[1] = tmElapsed.OutputTime();
	// Test3
    tmElapsed.Start();
	for (i=0; i<cLoops; i++)
	{
		k = (LONG)pCOMFree->Test23(bstr2);
	}
    tmElapsed.Stop();
    vrgperfloc[2].sec[2] = tmElapsed.OutputTime();
	
	// Remote
	if(vfRemote)
	{
		// Test1
    tmElapsed.Start();
    for (i=0; i<cLoops; i++)
		k = (LONG)pCOMFreeRmt->Test1(i);
		tmElapsed.Stop();
		vrgperfrmt[2].sec[0] = tmElapsed.OutputTime();
		// Test2
		tmElapsed.Start();
		for (i=0; i<cLoops; i++)
			k = (LONG)pCOMFreeRmt->Test23(bstr1);
		tmElapsed.Stop();
		vrgperfrmt[2].sec[1] = tmElapsed.OutputTime();
		// Test3
		tmElapsed.Start();
		for (i=0; i<cLoops; i++)
		{
			k = (LONG)pCOMFreeRmt->Test23(bstr2);
		}
		tmElapsed.Stop();
		vrgperfrmt[2].sec[2] = tmElapsed.OutputTime();
	}

	SysFreeString(bstr1);
	SysFreeString(bstr2);
	return TRUE;
}
 
 BOOL           
FreeFreeAutoTest(int cLoops)
{
	HRESULT hr;
	static VARIANTARG  rgvt[1];
    static DISPPARAMS  dispparams = { rgvt, NULL, 1, 0 };
    static EXCEPINFO  excepinfo;
    VARIANT vtResult;
    UINT    argerr;
    LONG    i, k;
    CTIMER  tmElapsed;
	BSTR bstr1, bstr2;
	bstr1 = SysAllocString(pszDesc1);
	bstr2 = SysAllocStringByteLen((const char *)pszDesc1, 4096);

	// Local
	// Test1
    tmElapsed.Start();
    V_VT(&vtResult) = VT_HRESULT;
    for (i=0; i<cLoops; i++)
	{
		V_VT(&rgvt[0]) = VT_I4;
		V_I4(&rgvt[0]) = i;
		hr = pAutoFree->Invoke(dispidICOMPerformance_Test1, IID_NULL, 0, DISPATCH_METHOD, &dispparams,
			&vtResult, &excepinfo, &argerr);
		k = V_I4(&vtResult);
	}
    tmElapsed.Stop();
    vrgperfloc[3].sec[0] = tmElapsed.OutputTime();
	// Test2
	tmElapsed.Start();
    V_VT(&vtResult) = VT_HRESULT;
    for (i=0; i<cLoops; i++)
	{
		V_VT(&rgvt[0]) = VT_BSTR;
		V_BSTR(&rgvt[0]) = bstr1;       
		hr = pAutoFree->Invoke(dispidICOMPerformance_Test23, IID_NULL, 0, DISPATCH_METHOD, &dispparams,
			&vtResult, &excepinfo, &argerr);
		k = V_I4(&vtResult);
	}
    tmElapsed.Stop();
    vrgperfloc[3].sec[1] = tmElapsed.OutputTime();
	// Test3
	tmElapsed.Start();
    V_VT(&vtResult) = VT_HRESULT;
    for (i=0; i<cLoops; i++)
	{
		V_VT(&rgvt[0]) = VT_BSTR;
		V_BSTR(&rgvt[0]) = bstr2;
		hr = pAutoFree->Invoke(dispidICOMPerformance_Test23, IID_NULL, 0, DISPATCH_METHOD, &dispparams,
			&vtResult, &excepinfo, &argerr);
		k = V_I4(&vtResult);
	}
    tmElapsed.Stop();
    vrgperfloc[3].sec[2] = tmElapsed.OutputTime();
	
	// Remote
	if(vfRemote)
	{
		// Test1
		tmElapsed.Start();
		V_VT(&vtResult) = VT_HRESULT;
		for (i=0; i<cLoops; i++)
		{
			V_VT(&rgvt[0]) = VT_I4;
			V_I4(&rgvt[0]) = i;
			hr = pAutoFreeRmt->Invoke(dispidICOMPerformance_Test1, IID_NULL, 0, DISPATCH_METHOD, &dispparams,
				&vtResult, &excepinfo, &argerr);
			k = V_I4(&vtResult);
		}
		tmElapsed.Stop();
		vrgperfrmt[3].sec[0] = tmElapsed.OutputTime();
		// Test2
		tmElapsed.Start();
		V_VT(&vtResult) = VT_HRESULT;
		for (i=0; i<cLoops; i++)
		{
			V_VT(&rgvt[0]) = VT_BSTR;
			V_BSTR(&rgvt[0]) = bstr1;       
			hr = pAutoFreeRmt->Invoke(dispidICOMPerformance_Test23, IID_NULL, 0, DISPATCH_METHOD, &dispparams,
				&vtResult, &excepinfo, &argerr);
			k = V_I4(&vtResult);
		}
		tmElapsed.Stop();
		vrgperfrmt[3].sec[1] = tmElapsed.OutputTime();
		// Test3
		tmElapsed.Start();
		V_VT(&vtResult) = VT_HRESULT;
		for (i=0; i<cLoops; i++)
		{
			V_VT(&rgvt[0]) = VT_BSTR;
			V_BSTR(&rgvt[0]) = bstr2;
			hr = pAutoFreeRmt->Invoke(dispidICOMPerformance_Test23, IID_NULL, 0, DISPATCH_METHOD, &dispparams,
				&vtResult, &excepinfo, &argerr);
			k = V_I4(&vtResult);
		}
		tmElapsed.Stop();
		vrgperfrmt[3].sec[2] = tmElapsed.OutputTime();
	}
	SysFreeString(bstr1);
	SysFreeString(bstr2);
	return TRUE;
}

 void
FPrintResults()
{
	_tprintf(TEXT("Data Size\t\t4\t50\t4k\t4\t50\t4k\n"));
	_tprintf(TEXT("%s\t\t"), vrgperfloc[0].szTest);
	_tprintf(TEXT("%4.2f\t"), LOOPS/vrgperfloc[0].sec[0]);
	_tprintf(TEXT("%4.2f\t"), LOOPS/vrgperfloc[0].sec[1]);
	_tprintf(TEXT("%4.2f\t"), LOOPS/vrgperfloc[0].sec[2]);
	if(vfRemote)       
	{
		_tprintf(TEXT("%4.2f\t"), LOOPS/vrgperfrmt[0].sec[0]);
		_tprintf(TEXT("%4.2f\t"), LOOPS/vrgperfrmt[0].sec[1]);
		_tprintf(TEXT("%4.2f\n"), LOOPS/vrgperfrmt[0].sec[2]);
	}
	else
	{
		_tprintf(TEXT("--\t"));
		_tprintf(TEXT("--\t"));
		_tprintf(TEXT("--\n"));
	}
	_tprintf(TEXT("%s\t\t"), vrgperfloc[1].szTest);
	_tprintf(TEXT("%4.2f\t"), LOOPS/vrgperfloc[1].sec[0]);
	_tprintf(TEXT("%4.2f\t"), LOOPS/vrgperfloc[1].sec[1]);
	_tprintf(TEXT("%4.2f\t"), LOOPS/vrgperfloc[1].sec[2]);
	if(vfRemote)   
	{
		_tprintf(TEXT("%4.2f\t"), LOOPS/vrgperfrmt[1].sec[0]);
		_tprintf(TEXT("%4.2f\t"), LOOPS/vrgperfrmt[1].sec[1]);
		_tprintf(TEXT("%4.2f\n"), LOOPS/vrgperfrmt[1].sec[2]);
	}
	else
	{
		_tprintf(TEXT("--\t"));
		_tprintf(TEXT("--\t"));
		_tprintf(TEXT("--\n"));
	}
	_tprintf(TEXT("%s\t\t"), vrgperfloc[2].szTest);
	_tprintf(TEXT("%4.2f\t"), LOOPS/vrgperfloc[2].sec[0]);
	_tprintf(TEXT("%4.2f\t"), LOOPS/vrgperfloc[2].sec[1]);
	_tprintf(TEXT("%4.2f\t"), LOOPS/vrgperfloc[2].sec[2]);
	if(vfRemote)    
	{
		_tprintf(TEXT("%4.2f\t"), LOOPS/vrgperfrmt[2].sec[0]);
		_tprintf(TEXT("%4.2f\t"), LOOPS/vrgperfrmt[2].sec[1]);
		_tprintf(TEXT("%4.2f\n"), LOOPS/vrgperfrmt[2].sec[2]);
	}
	else
	{
		_tprintf(TEXT("--\t"));
		_tprintf(TEXT("--\t"));
		_tprintf(TEXT("--\n"));
	}
	_tprintf(TEXT("%s\t\t"), vrgperfloc[3].szTest);
	_tprintf(TEXT("%4.2f\t"), LOOPS/vrgperfloc[3].sec[0]);
	_tprintf(TEXT("%4.2f\t"), LOOPS/vrgperfloc[3].sec[1]);
	_tprintf(TEXT("%4.2f\t"), LOOPS/vrgperfloc[3].sec[2]);
	if(vfRemote)    
	{
		_tprintf(TEXT("%4.2f\t"), LOOPS/vrgperfrmt[3].sec[0]);
		_tprintf(TEXT("%4.2f\t"), LOOPS/vrgperfrmt[3].sec[1]);
		_tprintf(TEXT("%4.2f\n"), LOOPS/vrgperfrmt[3].sec[2]);
	}
	else
	{
		_tprintf(TEXT("--\t"));
		_tprintf(TEXT("--\t"));
		_tprintf(TEXT("--\n"));
	}
	_tprintf(TEXT("%s\t\t"), vrgperfloc[4].szTest);
	_tprintf(TEXT("%4.2f\t"), LOOPS/vrgperfloc[4].sec[0]);
	_tprintf(TEXT("%4.2f\t"), LOOPS/vrgperfloc[4].sec[1]);
	_tprintf(TEXT("%4.2f\t"), LOOPS/vrgperfloc[4].sec[2]);
	if(vfRemote)    
	{
		_tprintf(TEXT("%4.2f\t"), LOOPS/vrgperfrmt[4].sec[0]);
		_tprintf(TEXT("%4.2f\t"), LOOPS/vrgperfrmt[4].sec[1]);
		_tprintf(TEXT("%4.2f\n"), LOOPS/vrgperfrmt[4].sec[2]);
	}
	else
	{
		_tprintf(TEXT("--\t"));
		_tprintf(TEXT("--\t"));
		_tprintf(TEXT("--\n"));
	}
	_tprintf(TEXT("%s\t\t"), vrgperfloc[5].szTest);
	_tprintf(TEXT("%4.2f\t"), LOOPS/vrgperfloc[5].sec[0]);
	_tprintf(TEXT("%4.2f\t"), LOOPS/vrgperfloc[5].sec[1]);
	_tprintf(TEXT("%4.2f\t"), LOOPS/vrgperfloc[5].sec[2]);
	if(vfRemote)    
	{
		_tprintf(TEXT("%4.2f\t"), LOOPS/vrgperfrmt[5].sec[0]);
		_tprintf(TEXT("%4.2f\t"), LOOPS/vrgperfrmt[5].sec[1]);
		_tprintf(TEXT("%4.2f\n"), LOOPS/vrgperfrmt[5].sec[2]);
	}
	else
	{
		_tprintf(TEXT("--\t"));
		_tprintf(TEXT("--\t"));
		_tprintf(TEXT("--\n"));
	}

  
}

 BOOL 
DoTests(void)
{
	if(!AptFreeCOMTest(LOOPS))
		return FALSE;
	if(!AptFreeAutoTest(LOOPS))
		return FALSE;
	if(!FreeFreeCOMTest(LOOPS))
		return FALSE;
	if(!FreeFreeAutoTest(LOOPS))
		return FALSE;
	FPrintResults();
	return TRUE;
} // DoTests

void Usage()
{
	_tprintf(TEXT("Usage: COMPERF [machine name | IP address | /? | -?]\n\n"));
	_tprintf(TEXT("/?\t\t\tDisplays this help screen.\n"));
	_tprintf(TEXT("machine name\t\tName of remote machine.\n"));
	_tprintf(TEXT("IP address\t\tIP address of remote machine.\n\n"));
	_tprintf("%s", PURPOSE);
}

// EOF =======================================================================
