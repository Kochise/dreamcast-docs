//**********************************************************************
// File name: app.cpp
//
//    Implementation file for the CPDSvrApp Class
//
// Functions:
//    See app.h for a list of member functions.
//
// Copyright (c) 1994 Microsoft Corporation. All rights reserved.
//**********************************************************************

#include "pre.h"
#include "obj.h"
#include "app.h"
#include "icf.h"

#include <initguid.h>
#include "..\guids.h"


//**********************************************************************
//
// CPDSvrApp::CPDSvrApp()
//
// Purpose:      Constructor for CPDSvrApp
// Parameters:   None
// Return Value: None
//
// Function Calls:
//      Function                    Location
//      OutputDebugString           Windows API
//
//********************************************************************

CPDSvrApp::CPDSvrApp()
{
	OutputDebugString(TEXT("In CPDSvrApp's Constructor \r\n"));

	// Initialize member variables
	m_nObjCount = 0;
	m_fInitialized = FALSE;
}

//**********************************************************************
// CPDSvrApp::~CPDSvrApp()
//
// Purpose:      Destructor for CPDSvrApp Class
// Parameters:   None
// Return Value: None
//
// Function Calls:
//      Function                    Location
//      OutputDebugString           Windows API
//      OleUninitialize             OLE API
//
//********************************************************************

CPDSvrApp::~CPDSvrApp()
{
	OutputDebugString(TEXT("In CPDSvrApp's Destructor\r\n"));

	// Unregister our class
	CoRevokeClassObject( m_dwRegisterClass ) ;

	// Uninitialize OLE libraries
	if (m_fInitialized)
		OleUninitialize();

}

// ObjectCreated and ObjectDestroyed are useful 
// for apps that support multiple objects; since
// ours doesn't they are useful, but not 
// necessary//  
void CPDSvrApp::ObjectCreated() 
{
    m_nObjCount++ ;
}

void CPDSvrApp::ObjectDestroyed() 
{
    m_nObjCount-- ;
    if (m_nObjCount == 0)
        PostQuitMessage(0) ;
}


//**********************************************************************
// CPDSvrApp::fInitInstance
//
// Purpose:  Instance initialization
//
// Parameters:
//      HANDLE hInstance    -   App. Instance Handle
//      int nCmdShow        -   Show parameter from WinMain
//
// Return Value:
//      TRUE    -   Initialization Successful
//      FALSE   -   Initialization Failed.
//
// Function Calls:
//      Function                    Location
//      CoRegisterClassObject       OLE API
//      OleBuildVersion             OLE API
//      OleInitialize               OLE API
//
// Comments:
//      Note that successful Initalization of the OLE libraries
//      is remembered so the UnInit is only called if needed.
//********************************************************************

BOOL CPDSvrApp::fInitInstance (HANDLE hInstance, int nCmdShow, CClassFactory FAR * lpClassFactory)
{
    // Get current running OLE version
	DWORD dwVer = OleBuildVersion();

	// make sure app was built with compatible version
	if (HIWORD(dwVer) != rmm || LOWORD(dwVer) < rup)
		OutputDebugString(TEXT("*** WARNING:  Not compatible with current libs ***\r\n"));

	// initialize the libraries
	if (OleInitialize(NULL) == NOERROR)
		m_fInitialized = TRUE;

    // Create an instance of our class factory object; we pass this
    // pointer to CoRegisterClassObject.
    lpClassFactory = new CClassFactory(this);
        
    // inc our ref count to hold the CF alive during CoRegisterClassObject
	lpClassFactory->AddRef();

    // Register our class factory with COM so that instances of our
    // class can be created.
	CoRegisterClassObject(CLSID_PHONEBOOK,
                          (IUnknown FAR *)lpClassFactory, 
                          CLSCTX_LOCAL_SERVER, 
	                      REGCLS_SINGLEUSE, 
                          &m_dwRegisterClass);

    // match our AddRef
	lpClassFactory->Release();

	return m_fInitialized;
}


//**********************************************************************
// WinMain
//
// Purpose: Program entry point
//
// Parameters:
//      HANDLE hInstance        - Instance handle for this instance
//      HANDLE hPrevInstance    - Instance handle for the last instance
//      LPSTR lpCmdLine         - Pointer to the command line
//      int nCmdShow            - Window State
//
// Return Value: msg.wParam
//********************************************************************
int PASCAL WinMain(HANDLE hInstance,HANDLE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)

{
    MSG msg;
    CPDSvrApp FAR * lpCPDSvrApp;
    CClassFactory FAR * lpClassFactory;
	BOOL fContinue = TRUE;

    // Create new instance of our application object
    lpCPDSvrApp = new CPDSvrApp;

    // instance initialization
    if (!lpCPDSvrApp->fInitInstance(hInstance, nCmdShow, lpClassFactory))
       return (FALSE);

    // message loop
	while (fContinue)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (WM_QUIT == msg.message)
			{
				fContinue = FALSE;
				break;
			}
			TranslateMessage(&msg);    /* Translates virtual key codes           */
			DispatchMessage(&msg);     /* Dispatches message to window           */
		}
	}

	// Delete our app object
	delete lpCPDSvrApp ;

	return (msg.wParam);           /* Returns the value from PostQuitMessage */
}

