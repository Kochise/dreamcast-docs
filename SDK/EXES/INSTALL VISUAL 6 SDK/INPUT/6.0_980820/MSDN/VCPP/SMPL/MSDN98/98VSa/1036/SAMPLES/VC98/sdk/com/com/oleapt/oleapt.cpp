// ===========================================================================
// File: O L E A P T . C P P
// 
//  Demonstrates OLE Apartment model threading. "Apartment" is essentially
// just a way of describing a thread with a message queue that supports OLE/COM
// objects. Objects within an apartment are reentrant in only the traditional
// Windows sense, identically to single-threaded OLE. That is to say that
// operations which yield to the message queue can cause further messages to
// be sent to any objects within the apartment. Apartment model threading simply
// allows there to be more than one "apartment" where previously there was
// only one: the main application thread.
// 
//  This program is both a client and an server. It launches as a client
// by default, registering its executable as a server and creating another
// instance of itself to be the server.
// 
//  The client does nothing interesting and is always shown as a minimized
// window. It simply creates an instance of its worker COM object in the
// server. When it shuts down, it releases its reference to the object,
// which is reflected in the server's UI.
// 
//  The server registers a class-factory on the main application thread and
// also spawns several worker threads. When requests arrive from clients to
// create instances of the class, the server class-factory picks a worker
// thread for the object (simply allocating them round-robin to the workers)
// and then goes through the process of having the object created within the
// thread and properly marshalled from the worker thread back to the class-
// factory where it can be returned to the caller. Note that this marshalling
// to the main thread is fairly transient, it lasts for creation only:
// subsequent calls from the client to the object go straight from the client's
// process into the worker apartment.
// 
//  The only mechanisms used here above-and-beyond NT 3.5 are:
//   * Ability to call CoInitialize() in multiple threads
//   * The use of the new marshalling flag, MSHCTX_INPROC, to marshall
//     pointers between threads
//
//  This sample may be compiled as UNICODE for the NT 3.51 beta, or as Ansi
// (listed here) to run on both the NT 3.51 beta and the Windows 95 M8 Beta.
// 
// Copyright 1995 - 1997 Microsoft Corporation.  All Rights Reserved.
// ===========================================================================

// %%Includes: ---------------------------------------------------------------
#define INC_OLE2
#define STRICT
#include <windows.h>
#include <initguid.h>
#include <stdio.h>

// %%Constants: --------------------------------------------------------------
#define cServerThreads  5
#define szWindowClass   TEXT("OLEAPT_CLASS")
#define szTitleServer   TEXT("SERVER: OLE Apartment Sample")
#define szTitleClient   TEXT("CLIENT: OLE Apartment Sample")
#define szCloseQuery    TEXT("Client references still exist. Are you sure you want to close?")
#define COINIT_APARTMENTTHREADED    2
const LARGE_INTEGER     bZero = {0,0};

// %%Guids: ------------------------------------------------------------------
DEFINE_GUID(CLSID_CObject, 0x5c06abc0, 0x2dcd, 0x11ce, 0x84, 0x17, 0x00, 0xaa, 0x00, 0x38, 0x9b, 0x71);

// %%Classes: ----------------------------------------------------------------
// the class-factory object exists in the main application apartment/thread
// and is used to create instances of the worker objects on worker threads.
class CClassFactory : public IClassFactory
    {
  // IClassFactory
    STDMETHODIMP            QueryInterface(REFIID iid, void **ppv);
    STDMETHODIMP_(ULONG)    AddRef(void)    { return mcRef++; }
    STDMETHODIMP_(ULONG)    Release(void)   { if (--mcRef == 0) { delete this; return 0; } return mcRef; }
    STDMETHODIMP            CreateInstance(LPUNKNOWN punkOuter, REFIID iid, LPVOID FAR *ppv);
    STDMETHODIMP            LockServer(BOOL fLock);

  // data members
    ULONG   mcRef;

  // constructors/destructors
  public:
    CClassFactory() { mcRef = 1; }
    };

// this worker object is simple: it simply supports IUnknown. more interesting
// interfaces can be readily added here and implemented for the worker.
class CObject : public IUnknown
    {
  // IUnknown
    STDMETHODIMP            QueryInterface(REFIID iid, void **ppv);
    STDMETHODIMP_(ULONG)    AddRef(void)    { return mcRef++; }
    STDMETHODIMP_(ULONG)    Release(void);

  // data members
    ULONG   mcRef;

  // constructors/destructors
  public:
    CObject() { mcRef = 1; }
    };

// %%Globals: ----------------------------------------------------------------
BOOL        vfServer;                       // is this instance a server or client?
HANDLE      vrghThread[cServerThreads];     // worker thread handles
DWORD       vrgtid[cServerThreads];         // worker thread id's
HANDLE      vrghEvent[cServerThreads];      // creation event for each worker
INT         vrgcObjects[cServerThreads];    // # of objects created on each thread
HANDLE      vhEventServer;                  // creation-complete event for class-factory
CClassFactory   vclassfactory;
UINT        viNextThread;                   // next worker to create an object on
LPUNKNOWN   vpunkService;                   // client's x-process reference to its
                                            //  worker object in the server
HWND        vhwndMain;
LPSTREAM    vpstmMarshalling;               // scratch stream used for cross-apt marshalling
HRESULT     vhrThreadStatus;                // signals status to class-factory

// %%Prototypes: -------------------------------------------------------------
LRESULT CALLBACK    MainWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT             ServerThreadProc(LPARAM lParam);
BOOL                FAutoRegister(HINSTANCE hinst);

// ---------------------------------------------------------------------------
// %%Function: MainWndProc
//  Window procedure for both client and server versions of the sample. Clients
// display nothing, server displays statistics about
// ---------------------------------------------------------------------------
 LRESULT CALLBACK
MainWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT lresult = TRUE;

    switch (message)
        {
        case WM_QUERYOPEN:
            // clients must stay minimized
            return vfServer;

        case WM_PAINT:
            {
            HDC hdc;
            PAINTSTRUCT ps;
            int i;

            if ((hdc = BeginPaint(hwnd, &ps)) != NULL)
                {
                if (vfServer)
                    {
                    for (i=0; i<cServerThreads; i++)
                        {
                        TCHAR    rgch[200];

                        wsprintf(rgch, TEXT("Thread #%d: %d objects"), i, vrgcObjects[i]);
                        TextOut(hdc, 20, 10+(i*25), rgch, lstrlen(rgch));
                        }
                    }
                }
            EndPaint(hwnd, &ps);
            }
            break;


        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        case WM_CLOSE:
            // check for clients and prompt in the UI.
            if (vfServer)
                {
                for (int i=0; i<cServerThreads; i++)
                    {
                    if (vrgcObjects[i] > 0)
                        {
                        if (MessageBox(hwnd, szCloseQuery,
                                szTitleServer, MB_YESNO) == IDNO)
                            return FALSE;
                        else
                            break;
                        }
                    }
                }

        default:
            return DefWindowProc(hwnd, message, wParam, lParam);
        }

    return lresult;
}  // MainWndProc

// ---------------------------------------------------------------------------
// %%Function: WinMain
//  Initialization, main message-pump for clients and servers.
// ---------------------------------------------------------------------------
 int PASCAL
WinMain(HINSTANCE hinst, HINSTANCE hinstPrev, LPSTR szCmdLine, int nCmdShow)
{
    WNDCLASS wndclass;
    HRESULT hr;
    int     i;
    DWORD   dwRegister = 0;
    MSG     msg;

    // parse the command-line
    if (szCmdLine)
        {
        LPSTR   sz = strtok(szCmdLine, " \t");

        vfServer = (sz && !strcmpi(sz, "-Embedding"));
        }
 		
    // initialize COM
    hr = CoInitialize(NULL);
    if (FAILED(hr))
        {
        MessageBeep(0);
        return hr;
        }

    // register the CObject class in the registry so
    // that the client can create instances of the server
    if (!FAutoRegister(hinst))
        {
        hr = GetLastError();
        goto LCleanup;
        }

    if (vfServer)
        {
        // create the threads and synchronization events
        // which the server will need
        for (i=0; i<cServerThreads; i++)
            {
            TCHAR    rgch[32];

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

            // a thread can use its thread-id to OpenEvent this existing
            // event at any time. it can also look for its thread-id in
            // vrgtid[] to determine its index for use with vrghEvent.
            // this event signals to a worker thread to create a new CObject
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

        // this signals the status of a worker threads creation after
        // receiving its create signal via vrghEvent[i]
        vhEventServer = CreateEvent(NULL, FALSE, FALSE, TEXT("Server"));
        if (vhEventServer == NULL)
            {
            hr = GetLastError();
            goto LCleanup;
            }

        // register the class-factory with COM
        hr = CoRegisterClassObject(CLSID_CObject,
            (IUnknown *)&vclassfactory,
            CLSCTX_LOCAL_SERVER,
            REGCLS_MULTIPLEUSE,
            &dwRegister);
        if (FAILED(hr))
            goto LCleanup;

        // create an IStream to be used for marshalling new objects between
        // the worker and the CClassFactory
        hr = CreateStreamOnHGlobal(NULL, TRUE, &vpstmMarshalling);
        if (FAILED(hr))
            goto LCleanup;
        }
    else
        {
        // this is the client case: create an instance of the service object
        // in the server
        hr = CoCreateInstance(CLSID_CObject,
            NULL,
            CLSCTX_LOCAL_SERVER,
            IID_IUnknown,
            (void**)&vpunkService);
        if (FAILED(hr))
            goto LCleanup;
        }

    // create the client and server UI
    memset(&wndclass, 0, sizeof(wndclass));
    wndclass.lpszClassName = szWindowClass;
    wndclass.style = CS_HREDRAW | CS_VREDRAW;
    wndclass.lpfnWndProc = MainWndProc;
    wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE + 1);
    wndclass.hInstance = hinst;

    if (!RegisterClass(&wndclass) ||
        (vhwndMain = CreateWindow(szWindowClass,
            vfServer ? szTitleServer : szTitleClient,
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
            HWND_DESKTOP, NULL, hinst, NULL)) == NULL)
        {
        hr = GetLastError();
        goto LCleanup;
        }

    // display clients as minimized, server as a normal window
    ShowWindow(vhwndMain, vfServer ? nCmdShow : SW_SHOWMINNOACTIVE);

    while (GetMessage(&msg, NULL, 0, 0))
        {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        }
    hr = msg.wParam;

LCleanup:
    if (hr != S_OK)
        MessageBeep(0);
    if (vfServer)
        {
        // we explicitly don't clean up threads and events
        if (dwRegister != 0)
            CoRevokeClassObject(dwRegister);
        if (vpstmMarshalling != NULL)
            vpstmMarshalling->Release();
        }
    else
        {
        // this is the client case: make sure to release the service
        if (vpunkService != NULL)
            vpunkService->Release();
        }

    CoUninitialize();
    return hr;
}  // WinMain

// ---------------------------------------------------------------------------
// %%Function: FAutoRegister
//  Registers the CObject class in the registry.
// ---------------------------------------------------------------------------
 BOOL
FAutoRegister(HINSTANCE hinst)
{
    static TCHAR szClassDesc[] = TEXT("Ole Apartments Sample");
    static TCHAR szCLSIDEntry[] = TEXT("CLSID\\{5c06abc0-2dcd-11ce-8417-00aa00389b71}");
    TCHAR       szBuf[512];
    TCHAR       szPath[512];
    HKEY        hkeyT = NULL;

    // install the OLEPerf OLE1/OLE2 compatibility sections
    if ((RegSetValue(HKEY_CLASSES_ROOT, szCLSIDEntry, REG_SZ, szClassDesc,
            lstrlen(szClassDesc)) != ERROR_SUCCESS) ||
        (RegCreateKey(HKEY_CLASSES_ROOT, szCLSIDEntry, &hkeyT)
            != ERROR_SUCCESS) ||
        !GetModuleFileName(hinst, szBuf, sizeof(szBuf)))
        return FALSE;
    lstrcpy(szPath, szBuf);
    if (RegSetValue(hkeyT, TEXT("LocalServer32"), REG_SZ, szBuf, lstrlen(szBuf))
            != ERROR_SUCCESS)
        goto LErrExit;
    RegCloseKey(hkeyT);
    return TRUE;
LErrExit:
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
//  Creates a new instance of a CObject on the next worker thread.
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

    viNextThread++;
    viNextThread %= cServerThreads;

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
    hr = CoInitialize(NULL);
    if (FAILED(hr))
        {
        MessageBeep(0);
        return hr;
        }

    // apartment message/event loop
    // (see SDK documentation for MsgWaitForMultipleObjects)
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

                // create a new CObject
                punk = (IUnknown *)new CObject;
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

                // modify the global state -- the # of objects/thread -- which is
                // displayed in the server UI
                vrgcObjects[iThread]++;
                InvalidateRect(vhwndMain, NULL, TRUE);

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
// %%Function: CObject::QueryInterface
//  Returns a new reference of the specified iid-type to a CObject.
// ---------------------------------------------------------------------------
 STDMETHODIMP
CObject::QueryInterface(REFIID iid, void **ppv)
{
    *ppv = NULL;

    if (iid == IID_IUnknown)
        {
        *ppv = (IUnknown *)this;
        }
    if (*ppv != NULL)
        {
        AddRef();
        return S_OK;
        }
    return E_NOINTERFACE;
}  // CObject::QueryInterface

// ---------------------------------------------------------------------------
// %%Function: CObject::Release
//  Handles releases of references to a CObject. Purpose here is to have code
// which alters the global state which is displayed in the servers UI.
// ---------------------------------------------------------------------------
 STDMETHODIMP_(ULONG)
CObject::Release(void)
{
    if (--mcRef == 0)
        {
        // change the global server state -- the # of objects/thread --
        // reflected in the server UI
        for (int i=0; i<cServerThreads; i++)
            {
            if (vrgtid[i] == GetCurrentThreadId())
                {
                vrgcObjects[i]--;
                InvalidateRect(vhwndMain, NULL, TRUE);
                break;
                }
            }

        delete this;
        return 0;
        }
    return mcRef;
}  // CObject::Release

// EOF =======================================================================
