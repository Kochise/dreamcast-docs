
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright (C) 1995-1997 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

//
//    PROGRAM:	InfInst.c
//
//    PURPOSE:	Demonstrates how create a wizard based install
//              using win32 functions in setupapi.dll
//
//    PLATFORMS:	Windows 95 and NT 4.0
//
//    FUNCTIONS:	
//    	WinMain() - calls initialization function, processes message loop
//    	InitApplication() - Initializes window data nd registers window
//    	InitInstance() - saves instance handle and creates main window
//    	MainWindProc() - Processes messages
//    	RuntimeRegistration() - Add runtime data to registry
//      RegisterString() - adds a string to registry, simple win32 registry api wrapper
//      GetRegString() - gets a string from registry, simple win32 registry api wrapper
//      GetPlatformInfo () - not used but this is an exampleof what you can do in
//             a win32 or win16 setup stub program to get your setup started
//             NOTE: In this sample we are assuming the autorun.inf takes care of this
//
//    CALLS:
//    	DoInstallation() - Does the resulting installation options in doinst.c
//
//    SPECIAL INSTRUCTIONS: N/A
//

#include <windows.h>    // includes basic windows functionality
#include <string.h>     // includes the string functions
#include <prsht.h>      // includes the property sheet functionality
#include "setupapi.h"   // includes the inf setup api 
#include "resource.h"   // includes the definitions for the resources
#include "instwiz.h"     // includes the application-specific information
#include "infinst.h"     // includes the application-specific information
#include "infdesc.h"

INSTALLINFO setupInfo;      // a structure containing the review information
HWND hwndEdit;          // handle to the main MLE
TCHAR lpReview[MAX_BUF]; // Buffer for the review

BOOL bCreated = FALSE;  // Keep us minimized once we are created

//
//
//   FUNCTION: WinMain(HANDLE, HANDLE, LPSTR, int)
//
//   PURPOSE: Main entry point for the application. 
//
//   COMMENTS:
//    
//    This function calls the initialization functions and processes
//    the main message loop.
// 
int APIENTRY WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow
    )
{
        MSG msg;                       

        // save off the current instance
        setupInfo.hInst = hInstance;

        // if the initialization fails, return.
        if (!InitApplication(hInstance))
            return (FALSE);     

        // Perform initializations that apply to a specific instance 
        if (!InitInstance(hInstance, nCmdShow))
            return (FALSE);

       // Acquire and dispatch messages until a WM_QUIT message is received. 
       while (GetMessage(&msg, NULL, 0,0))                
       {
    	  TranslateMessage(&msg);
    	  DispatchMessage(&msg); 
       }
       
       return (msg.wParam);  
}


//
//
//   FUNCTION: InitApplication(HANDLE) 
//
//   PURPOSE: Initializes window data and registers window class 
//
//   COMMENTS:
//
//    	This function registers the window class for the main window.	
// 
BOOL InitApplication(HANDLE hInstance)
{
        WNDCLASS  wcSample;
    
        // Fill in window class structure with parameters that describe the       
        // main window.                                                           

        wcSample.style = 0;                     
        wcSample.lpfnWndProc = (WNDPROC)MainWndProc; 
        wcSample.cbClsExtra = 0;              
        wcSample.cbWndExtra = 0;              
        wcSample.hInstance = hInstance;       
        wcSample.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(EXE_ICON));
        wcSample.hCursor = LoadCursor(NULL, IDC_ARROW);
        wcSample.hbrBackground = GetStockObject(WHITE_BRUSH); 
        wcSample.lpszMenuName =  NULL;  
        wcSample.lpszClassName = TEXT("SampleWClass");

        return (RegisterClass(&wcSample));

}


//
//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Creates the main window.
//
//   COMMENTS: N/A
//    
// 
BOOL InitInstance(
    HANDLE          hInstance,
    int             nCmdShow) 
{
    HWND hWndMain;

    hWndMain = CreateWindow(
        TEXT("SampleWClass"),
        TEXT("Install Sample"), 
    	WS_OVERLAPPEDWINDOW, 
    	CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
    	NULL,               
    	NULL,               
    	hInstance,          
    	NULL);

    /* If window could not be created, return "failure" */
    if (!hWndMain)
    	return (FALSE);

    /* Make the window visible; update its client area; and return "success" */
    ShowWindow(hWndMain, SW_MINIMIZE);
    UpdateWindow(hWndMain); 
    return (TRUE);      

}

//
//   FUNCTION: MainWndProc(HWND, UINT, UINT, LONG)
//
//  PURPOSE:  Processes messages for the main window procedure 
//
//    MESSAGES:
//    
//    WM_CREATE - creates the main MLE for the window
//    WM_COMMAND - processes the menu commands for the application
//    WM_SIZE - sizes the MLE to fill the client area of the window
//    WM_DESTROY - posts a quit message and returns
//
LONG APIENTRY MainWndProc(
    HWND hWnd,                // window handle                   
    UINT message,             // type of message                 
    UINT wParam,              // additional information          
    LONG lParam)              // additional information          
{

    switch (message) 
    {
        case WM_CREATE:
            // TODO: put in a Bitmap for a splash window );
            
            GetRegString(MYPRODUCT_KEY, USER_NAME_KEY,  setupInfo.pszUserName);
            GetRegString(MYPRODUCT_KEY, COMPANY_KEY,    setupInfo.pszCompany);
            GetRegString(MYPRODUCT_KEY, PRODUCT_ID_KEY, setupInfo.pszProductIdString);
            GetRegString(MYPRODUCT_KEY, EMAIL_KEY,      setupInfo.pszEmailAddress);
            GetRegString(MYPRODUCT_KEY, TEXT("DestinationPath"),  setupInfo.pszDestPath);

            // Start up the install 
            PostMessage(hWnd, WM_COMMAND, ID_INSTALL, 0 );
            return 0;
 
         case WM_WINDOWPOSCHANGING:
             if (bCreated)
             {  
                 LPWINDOWPOS lpwp;

                 lpwp = (LPWINDOWPOS) lParam; // points to size and position data 
                 lpwp->flags = SWP_NOMOVE    | SWP_NOOWNERZORDER |
                               SWP_NOSIZE | SWP_NOREDRAW | 
                               SWP_NOREPOSITION;

              } 
              else
              { 
                 bCreated = TRUE;
              }
              break;

        case WM_COMMAND:
            switch( LOWORD( wParam ))
    		{
                /*******************************************************\
                *
                *  Here is where the real work takes place
                *     Do the wizard to collect the user information
                *     Do the installation with the setupapis
                *     Update the registry with runtime user data
                *     
                \*******************************************************/
                case ID_INSTALL:
                    // Do installation
                    DoInstallation(hWnd, &setupInfo);

                    //installs done so go away
                    PostMessage(hWnd, WM_DESTROY, 0, 0 );
                    break;

                 default:
                    return (DefWindowProc(hWnd, message, wParam, lParam));

    	}
    	break;

    	case WM_DESTROY:                  /* message: window being destroyed */
    		PostQuitMessage(0);
    		break;

    	default:
    		return (DefWindowProc(hWnd, message, wParam, lParam));
    }
    return (0);
}


void RuntimeRegistration(INSTALLINFO *si)
{
    //
    // The setupapi calls have completed
    // now we will finish up by updating the user information
    // and uninstall in the registry
    //

    char buf[MAX_PATH];

    //
    // Stuff for out product
    // fixed application values are done by the inf
    // We are only doing runtime values here
    //

    RegisterString(MYPRODUCT_KEY,
             USER_NAME_KEY,
             si->pszUserName);

    RegisterString(MYPRODUCT_KEY,
             COMPANY_KEY,
             si->pszCompany);
    
    RegisterString(MYPRODUCT_KEY,
             PRODUCT_ID_KEY,
             si->pszProductIdString);
    
    RegisterString(MYPRODUCT_KEY,
             EMAIL_KEY,
             si->pszEmailAddress);
    

    wsprintf(buf, "%s", si->pszDestPath);
    
    RegisterString(MYPRODUCT_KEY,
                TEXT("DestinationPath"),
                buf);

/*
    //
    // Setup up Add/Remove Programs Control Panel Applet
    // We need to set Display name and how to uninstall
    //
    // UNINSTALL Info
    //

    RegisterString(UNINSTALL_KEY,
                TEXT("DisplayName"),
                TEXT("MyProduct Version 1.0"));

    wsprintf(buf, "%s\\setup.exe Uninstall", si->pszDestPath);
    
    RegisterString(UNINSTALL_KEY,
                TEXT("UninstallString"),
                buf);

*/    
    return;
}


BOOL 
RegisterString (
   LPSTR pszKey, 
   LPSTR pszValue, 
   LPSTR pszData
   )
{

    HKEY hKey;
    DWORD dwDisposition;

    //
    // Create the key, if it exists it will be opened
    //

    if (ERROR_SUCCESS != 
        RegCreateKeyEx(
          HKEY_LOCAL_MACHINE,       // handle of an open key 
          pszKey,                  // address of subkey name 
          0,                       // reserved 
          NULL,                    // address of class string 
          REG_OPTION_NON_VOLATILE, // special options flag 
          KEY_ALL_ACCESS,           // desired security access 
          NULL,                       // address of key security structure 
          &hKey,                   // address of buffer for opened handle  
          &dwDisposition))            // address of disposition value buffer 
    {
        return FALSE;
    }

    //
    // Write the value and it's data to the key
    //

    if (ERROR_SUCCESS != 
        RegSetValueEx(
            hKey,                 // handle of key to set value for  
            pszValue,             // address of value to set 
            0,                     // reserved 
            REG_SZ,                 // flag for value type 
            pszData,             // address of value data 
            strlen(pszData) ))      // size of value data 
    {
        
        RegCloseKey(hKey);
        return FALSE;
    }

    //
    // Close the key
    //
    
    RegCloseKey(hKey);
    
    return TRUE;
}

BOOL
GetRegString (
  LPSTR pszKey,
  LPSTR pszValue,
  LPSTR pszData
  )
{

    HKEY hKey;
    DWORD dwDataSize = MAX_PATH - 1;
    DWORD dwValueType = REG_SZ;

    RegOpenKeyEx(
       HKEY_LOCAL_MACHINE,    // handle of open key 
       pszKey,                // address of name of subkey to open 
       0,                    // reserved 
       KEY_QUERY_VALUE,        // security access mask 
       &hKey                 // address of handle of open key 
       );    

    RegQueryValueEx(
        hKey,         // handle of key to query 
        pszValue,     // address of name of value to query 
        0,             // reserved 
        &dwValueType,// address of buffer for value type 
        pszData,     // address of data buffer 
        &dwDataSize  // address of data buffer size 
        );

    if (pszData[dwDataSize] != '\0')
        pszData[dwDataSize] = '\0';

    return TRUE;
}

/*

//      GetPlatformInfo () - not used but this is an example of what you can do in
//             a win32 or win16 setup stub program to get your setup started
//             NOTE: In this sample we are assuming the autorun.inf takes care of this
//                   for us. See the autorun.inf which shows this
//
//      The core of this could be your entire WinMain in a win16 stub 
//
int GetPlatformInfo(HINSTANCE hInstance)
{
    char szCpu[64], szPath[_MAX_PATH], szExeStr[128];
    char szSystemDir[_MAX_PATH];
    
    GetModuleFileName(hInstance, szPath, _MAX_PATH);
    *(strrchr(szPath, '\\') + 1) = '\0';	// Strip SETUPPROG off path
    GetSystemDirectory(szSystemDir, _MAX_PATH);

	                                                        
    if (getenv("PROCESSOR_ARCHITECTURE") != NULL)
    {
    	lstrcpyn(szCpu, getenv("PROCESSOR_ARCHITECTURE"), 63);
    }
    else
    {   	// Not defined, guess x86
    	lstrcpy(szCpu, "x86");
    }

        if (HIBYTE(LOWORD(GetVersion())) > 11) 		// Check if Win95 
	{
	    //Win95
            sprintf(szExeStr, "%s\\Bin\\I386\\infinst.exe CmdLineOptions", szPath);
	} 
        // Else pick the NT platform
        else if (!lstrcmp(szCpu, "MIPS"))
	{                           
            sprintf(szExeStr, "%s\\Bin\\MIPS\\infinst.exe CmdLineOptions", szPath);
	}
	else if (!lstrcmp(szCpu, "ALPHA"))
	{
            sprintf(szExeStr, "%s\\Bin\\ALPHA\\infinst.exe CmdLineOptions", szPath);
	}
	else if (!lstrcmp(szCpu, "PPC"))
	{
            sprintf(szExeStr, "%s\\Bin\\PPC\\infinst.exe CmdLineOptions", szPath);
	}                                         		
	else   // x86 NT box
	{
            sprintf(szExeStr, "%s\\Bin\\I386\\infinst.exe CmdLineOptions", szPath);
        }

    //    MessageBox ( NULL, szExeStr,szCpu,MB_OK);

    //    WinExec(szExeStr, SW_SHOW);

    if (wReturn < 32) {
             //Failed
    }
    else {
              //Worked
    }

    return(0);
}
*/