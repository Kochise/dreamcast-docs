//////////////////////////////////////////////////////////////////////////////
//
//  FILE:           MAIN.CPP
//
//  DESCRIPTION:    This file contains the code for the entry function and
//                      the main window for this form
//
//
//  Copyright (c) 1995, Microsoft Corporation.
//  All rights reserved.
//
//--

#include "precomp.h"
#include <wrap3d.h>

// Just to make it easier to determine appropriate code paths:
#if defined (_WIN32) // This had better be true, but just in case...
    #define IS_WIN32 TRUE
#else
    #define IS_WIN32 FALSE
#endif
#define IS_NT      IS_WIN32 && (BOOL)(GetVersion() < 0x80000000)
#define IS_WIN32S  IS_WIN32 && (BOOL)(!(IS_NT) && (LOBYTE(LOWORD(GetVersion()))<4))
#define IS_CHICAGO (BOOL)(!(IS_NT) && !(IS_WIN32S)) && IS_WIN32

///////////////////////// Global Variables /////////////////////////////////

extern CClassFactory   ClassFactory;
HINSTANCE       g_hinst;
char            SzAppName[] = "SimpFrm";  // The name of this application
char            g_szSendWinClass[] = "SampleFormSend";
char            g_szReadWinClass[] = "SampleFormRead";
char            g_szFormName[] = "Simple Sample Form";
char            g_szWindowCaption[] = "Sample Form";
CBaseForm *     g_PfrmFirst = NULL;
LPVOID          g_lpCtl3d = NULL;           //  CTL3D context

//// Internal Flags

ULONG           UlCoRegForm = 0;
BOOL            FMapiInitialized = FALSE;

//we have to create an atom containig string representation of
// the class id;  the atom has to have the same live time as the
//ClassFactory object
static ATOM     atmCFAlive; 

//////////////////////////// Extern and forward declarations //////////////

LRESULT CALLBACK WndProcMain(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProcForm(HWND, UINT, WPARAM, LPARAM);

////    InitApplication
//

BOOL InitApplication(HINSTANCE hInstance)
{
    WNDCLASSEX  wc;

    //  Fill in the window class structure with parameters that describe
    //  the main window.  This window will never be displayed and exists
    //  so that OLE can talk to us.

    wc.cbSize           = sizeof(wc);
    wc.style            = 0;
    wc.lpfnWndProc      = (WNDPROC) WndProcMain;
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hInstance        = hInstance;
    wc.hIcon            = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor          = ::LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground    = (HBRUSH) (COLOR_WINDOW+1);
    wc.lpszMenuName     = NULL;
    wc.lpszClassName    = SzAppName;
    wc.hIconSm          = LoadIcon(hInstance, "SmallIcon");
    
    //  Register the window class.
    if (!RegisterClassEx(&wc))
    {
        return FALSE;
    }

    //  Now setup and register the acutual window class used for the
    //  form.

    wc.style            = CS_HREDRAW | CS_VREDRAW;
    wc.lpszClassName    = g_szSendWinClass;
    wc.lpfnWndProc      = (WNDPROC) WndProcForm;
    wc.cbWndExtra       = 4;
    wc.hIcon            = LoadIcon(hInstance, "IconL");
//    if (IS_CHICAGO) {
//        wc.lpszMenuName = "CHICAGO";
//    }
//    else {
        wc.lpszMenuName = MAKEINTRESOURCE(IDR_SEND_FORM);
//    }

    if (!RegisterClassEx(&wc))
    {
        return FALSE;
    }

    //  Now setup and register the acutual window class used for the
    //  form.

    wc.style            = CS_HREDRAW | CS_VREDRAW;
    wc.lpszClassName    = g_szReadWinClass;
    wc.lpfnWndProc      = (WNDPROC) WndProcForm;
    wc.cbWndExtra       = 4;
    wc.hIcon            = LoadIcon(hInstance, "IconL");
//    if (IS_CHICAGO) {
//        wc.lpszMenuName = "CHICAGO";
//    }
//    else {
        wc.lpszMenuName = MAKEINTRESOURCE(IDR_READ_FORM);
//    }

    return RegisterClassEx(&wc);
}

////    InitInstance
//

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    HRESULT             hr;
    ULONG               ulVer;
    HWND                hWnd;
    BOOL                f;

    ///////////////////////////////////////////////////////////////////////
    //
    //  Initialize OLE and MAPI

    ulVer = CoBuildVersion ();
#if 0          
    if (HIWORD (ulVer) != rmm)
    {
        return FALSE;
    }
#endif // 0
                     
    //
    //  Initialize MAPI -- this implies a successfull initialization of
    //  OLE on success
    //
        
    hr = MAPIInitialize (NULL);
    if (HR_FAILED(hr))
    {
        return FALSE;
    }
    FMapiInitialized = TRUE;

    //
    //  Give ourselves the 3D look
    //
    
    if (!g_lpCtl3d)
    {
        g_lpCtl3d = CTL3D_Initialize(hInstance);
        if (g_lpCtl3d)
            CTL3D_AutoSubclass(g_lpCtl3d, hInstance, &f);
    }
        
        
    //Create global atom with string representaton of our class id
    if(0 == FindAtom(szGUID))
        atmCFAlive = GlobalAddAtom(szGUID);
    
    
    //
    //  Register our class factory for the form
    //
    
    hr = CoRegisterClassObject(CLSID_IPM_NOTE_SAMPLE, &ClassFactory,
                               CLSCTX_LOCAL_SERVER, REGCLS_MULTIPLEUSE,
                               &UlCoRegForm);
    if (FAILED(hr))
    {
        return FALSE;
    }
        
    //
    //  Create a main window -- This window is used for dealing with
    //          messages coming from the top of the work and consitutes
    //          our main window.  We create this window of size zero and
    //          not visible since it is not the window the user
    //          interacts with

    hWnd = CreateWindow(SzAppName, NULL, WS_OVERLAPPEDWINDOW,
                        0, 0, 0, 0, NULL, NULL, hInstance, NULL);
    if (!hWnd)
    {
        return FALSE;
    }

    ClassFactory.ms_hWndMain = hWnd;
    g_hinst = hInstance;

    return TRUE;
}


int ExitInstance ()
{
    //
    //  Revoke all classes factories here so we don't get any new
    //  creates

    if (UlCoRegForm != 0)
    {
        CoRevokeClassObject (UlCoRegForm);
        UlCoRegForm = 0;
    }

    //
    //  Shut down CTL3D

    if (g_lpCtl3d)
    {
        CTL3D_Uninitialize(g_lpCtl3d);
        g_lpCtl3d = NULL;
    }

    //
    //  Uninitialize MAPI

    if (FMapiInitialized)
    {
        MAPIUninitialize();
        FMapiInitialized = FALSE;
    }

    GlobalDeleteAtom(atmCFAlive);

    return 0;
}


////    WinMain
//

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                     LPSTR /*lpCmdLine*/, int nCmdShow)
{
    MSG         msg;

    if (!hPrevInstance)
    {
        // Perform instance initialization
        if (!InitApplication(hInstance))
        {
            return FALSE;
        }
    }

    // Perform application initialization
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    
    //  Main message loop
    while (GetMessage(&msg, NULL, 0, 0))
    {
        CBaseForm *     pfrm;
        
        //
        //  Find which top level window this message is for
        //

        for (pfrm = g_PfrmFirst; pfrm != NULL; pfrm = pfrm->GetNext())
        {
            if (pfrm->TranslateMessage(msg))
            {
                break;
            }
        }

        if (pfrm == NULL)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    ExitInstance();

    return msg.wParam;
}



////  A specialized version of the window proc which plays how messages
//      are going to be handled.
//   

LRESULT CALLBACK WndProcMain(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
   switch (msg)
   {
   case WM_DESTROY:
       PostQuitMessage(0);
       break;

   default:
       return DefWindowProc (hwnd, msg, wParam, lParam);
   }

   return 0;
}

