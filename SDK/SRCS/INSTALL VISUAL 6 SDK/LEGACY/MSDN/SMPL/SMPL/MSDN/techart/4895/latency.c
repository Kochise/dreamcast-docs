//THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
//ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
//THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//
// Copyright  1994-1995  Microsoft Corporation.  All Rights Reserved.
//
//  PROGRAM:    Latency.exe
//              Based on Generic sample application in Visual C++ 4.0
//
//  PURPOSE:    Illustrates differences in multimedia timer latency between
//              using 32-bit and 16-bit timer procedures.
//
//  PLATFORMS:  Windows 95, Windows NT
//              (Win32s does not support multimedia callbacks)
//
//  FUNCTIONS:  
//      WinMain() - calls initialization function, processes message loop
//      InitApplication() - Initializes window data nd registers window
//      InitInstance() -saves instance handle and creates main window
//      WindProc() Processes messages
//      About() - Process menssages for "About" dialog box
//      MyRegisterClass() - Registers the application's window class
//      CenterWindow() -  Centers one window over another
//

// Windows Header Files:
#include <windows.h>

// Local Header Files
#include "latency.h"
#include "resource.h"
#include "timer.h"
#include "timer32.h"
//#include "thk3216.h"


// Macros to determine platform-specific code paths:
#define IS_NT       (dwPlatformId == VER_PLATFORM_WIN32_NT)
#define IS_WIN32S   (dwPlatformId == VER_PLATFORM_WIN32s)
#define IS_WIN95    (dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)

// Global Variables:
HINSTANCE hInst; // current instance
char szAppName[] = APPNAME; // name of this application
char szTitle[]   = APPNAME; // title bar text
DWORD dwPlatformId;         // from GetVersionEx ()
BOOL bShowTimerCaps = TRUE;
FARPROC pStartTimer3216;    // ptrs to procs dynamically
FARPROC pStopTimer3216;     // linked from THK3216.DLL
FARPROC pResetMaxMin3216;   //
FARPROC pEnableSound3216;   //
FARPROC pDisableSound3216;  //

//
//  FUNCTION: WinMain(HANDLE, HANDLE, LPSTR, int)
//
//  PURPOSE: Entry point for the application.
//
//  COMMENTS:
//
//  This function initializes the application and processes the
//  message loop.
//
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    MSG msg;
    HANDLE hAccelTable;
    HMODULE hmodThunkDll;
    OSVERSIONINFO osversioninfo;

    // Determine platform now; platform-dependent code follows
    osversioninfo.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
    GetVersionEx (&osversioninfo);
    dwPlatformId = osversioninfo.dwPlatformId;

    if (!hPrevInstance)
    {
        // Perform instance initialization:
        if (!InitApplication(hInstance))
        {
            return (FALSE);
        }
    }

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return (FALSE);
    }

    // Load DLL containing 32-bit side of thunk
    if (IS_WIN95)
    {
        if (hmodThunkDll = (HMODULE) LoadLibrary ("THK3216"))
        {
            // Dynamically link to thunked functions
            pStartTimer3216  = GetProcAddress (hmodThunkDll, "StartTimer3216");
            pStopTimer3216   = GetProcAddress (hmodThunkDll, "StopTimer3216");
            pResetMaxMin3216 = GetProcAddress (hmodThunkDll, "ResetMaxMin3216");
            pEnableSound3216 = GetProcAddress (hmodThunkDll, "EnableSound3216");
            pDisableSound3216 = GetProcAddress (hmodThunkDll, "DisableSound3216");
        }
        if (!(hmodThunkDll && pStartTimer3216 && pStopTimer3216 && pResetMaxMin3216))
        {
            // Problem loading or linking to DLL, clean up and scram
            MessageBox (NULL, "Unable to load THK3216.DLL",
                        NULL, MB_ICONERROR | MB_TASKMODAL);
            if (hmodThunkDll)
            {
                FreeLibrary (hmodThunkDll);
            }
            return (FALSE);
        }
    }
    
    // Load accelerator table
    hAccelTable = LoadAccelerators (hInstance, szAppName);

#if 0
    SetPriorityClass (GetCurrentProcess (), REALTIME_PRIORITY_CLASS);
    SetThreadPriority (GetCurrentThread (), THREAD_PRIORITY_TIME_CRITICAL);
#endif
    
    // Main message loop:
    while (GetMessage(&msg, NULL, 0, 0))
    {
        if (!TranslateAccelerator (msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    if (IS_WIN95)
    {
        FreeLibrary (hmodThunkDll);
    }
    
    return (msg.wParam);

    lpCmdLine; // This will prevent 'unused formal parameter' warnings
}

//
//  FUNCTION: MyRegisterClass(CONST WNDCLASS*)
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//  This function and its usage is only necessary if you want this code
//  to be compatible with Win32 systems prior to the 'RegisterClassEx'
//  function that was added to Windows 95. It is important to call this function
//  so that the application will get 'well formed' small icons associated
//  with it.
//
ATOM MyRegisterClass(CONST WNDCLASS *lpwc)
{
    HANDLE  hMod;
    FARPROC proc;
    WNDCLASSEX wcex;

    hMod = GetModuleHandle ("USER32");
    if (hMod != NULL) {

#if defined (UNICODE)
        proc = GetProcAddress (hMod, "RegisterClassExW");
#else
        proc = GetProcAddress (hMod, "RegisterClassExA");
#endif

        if (proc != NULL) {

            wcex.style         = lpwc->style;
            wcex.lpfnWndProc   = lpwc->lpfnWndProc;
            wcex.cbClsExtra    = lpwc->cbClsExtra;
            wcex.cbWndExtra    = lpwc->cbWndExtra;
            wcex.hInstance     = lpwc->hInstance;
            wcex.hIcon         = lpwc->hIcon;
            wcex.hCursor       = lpwc->hCursor;
            wcex.hbrBackground = lpwc->hbrBackground;
                        wcex.lpszMenuName  = lpwc->lpszMenuName;
            wcex.lpszClassName = lpwc->lpszClassName;

            // Added elements for Windows 95:
            wcex.cbSize = sizeof(WNDCLASSEX);
            wcex.hIconSm = LoadIcon(wcex.hInstance, "SMALL");
            
            return (*proc)(&wcex);//return RegisterClassEx(&wcex);
        }
    }
    return (RegisterClass(lpwc));
}


//
//  FUNCTION: InitApplication(HANDLE)
//
//  PURPOSE: Initializes window data and registers window class 
//
//  COMMENTS:
//
//       In this function, we initialize a window class by filling out a data
//       structure of type WNDCLASS and calling either RegisterClass or 
//       the internal MyRegisterClass.
//
BOOL InitApplication(HINSTANCE hInstance)
{
    WNDCLASS  wc;

    // Win32s does not support multimedia callbacks, bow out gracefully
    if (IS_WIN32S)
    {
        MessageBox (NULL, "Multimedia timer callbacks are not supported on Win32s. Unable to run "APPNAME,
                    NULL, MB_ICONERROR | MB_TASKMODAL);
        return FALSE;
    }
    

    // Fill in window class structure with parameters that describe
    // the main window.
    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = (WNDPROC)WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon (hInstance, szAppName);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);

    // Load different menus for Win95 and WinNT:
    //   Win95 has a slightly different recommended format for the 'Help' menu
    //   NT doesn't support 16-bit timer procs
    if (IS_WIN95)
    {
        wc.lpszMenuName  = "WIN95MENU";
    }
    else
    {
        wc.lpszMenuName  = "WINNTMENU";
    }
    wc.lpszClassName = szAppName;

    // Register the window class and return success/failure code.
    if (IS_WIN95)
    {
        return MyRegisterClass(&wc);
    }
    else
    {
        return RegisterClass(&wc);
    }
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window 
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    HWND hWnd;
    
    hInst = hInstance; // Store instance handle in our global variable

    hWnd = CreateWindow(szAppName, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
        NULL, NULL, hInstance, NULL);

    if (!hWnd)
    {
        return (FALSE);
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return (TRUE);
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  MESSAGES:
//
//  WM_COMMAND - process the application menu
//  WM_PAINT - Paint the main window
//  WM_DESTROY - post a quit message and return
//    WM_DISPLAYCHANGE - message sent to Plug & Play systems when the display changes
//    WM_RBUTTONDOWN - Right mouse click -- put up context menu here if appropriate
//    WM_NCRBUTTONUP - User has clicked the right button on the application's system menu
//
//
typedef struct _TSTATE
{
    BOOL bTimerStarted;
    BOOL bSoundEnabled;
    UINT uiPeriod;
    DWORD dwMinPeriod;
    DWORD dwMaxPeriod;
} TSTATE, * LPTSTATE;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId, wmEvent;
    PAINTSTRUCT ps;
    HDC hdc;
    TIMECAPS timecaps;
    TCHAR szTextOut[1024];

    // Timer state data (app side)
    static TSTATE tstate32 = { FALSE, FALSE, 1000, 0xffff, 0 };
    static TSTATE tstate16 = { FALSE, FALSE, 1000, 0xffff, 0 };
    
    // UI state data
    static UINT uiPeriodMenuMap [6] = {1000, 500, 100, 50, 10, 5};
    static UINT uiChecked16 = IDM_TIMER16_T1000;
    static UINT uiChecked32 = IDM_TIMER32_T1000;

    switch (message) { 

        case WM_COMMAND:
            wmId    = LOWORD(wParam); // Remember, these are...
            wmEvent = HIWORD(wParam); // ...different for Win32!

            //Parse the menu selections:
            switch (wmId) {

                case IDM_ABOUT:
                    DialogBox(hInst, "AboutBox", hWnd, (DLGPROC)About);
                    break;

                case IDM_TIMER16_START:
                    // Once timer started, no longer show timer capabilities
                    if (bShowTimerCaps)
                    {
                        bShowTimerCaps = FALSE;
                    }

                    // Toggle between start/stop
                    tstate16.bTimerStarted = !tstate16.bTimerStarted;
                    
                    if (tstate16.bTimerStarted)
                    {
                        // Reset and start timer
                        (*pResetMaxMin3216) ();
                        tstate16.bTimerStarted = (*pStartTimer3216) (tstate16.uiPeriod, hWnd);
                    }
                    else
                    {
                        // Stop timer
                        (*pStopTimer3216) ();
                    }

                    // Update menu
                    ModifyMenu (GetMenu (hWnd), wmId, MF_STRING, wmId, tstate16.bTimerStarted ? "Stop" : "Start");
                    DrawMenuBar (hWnd);
                    break;


                case IDM_TIMER32_START:
                    // Once timer started, no longer show timer capabilities
                    if (bShowTimerCaps)
                    {
                        bShowTimerCaps = FALSE;
                    }

                    // Toggle between start/stop
                    tstate32.bTimerStarted = !tstate32.bTimerStarted;
                    
                    if (tstate32.bTimerStarted)
                    {
                        // Reset and start timer
                        ResetMaxMin32 ();
                        tstate32.bTimerStarted = StartTimer32 (tstate32.uiPeriod, hWnd);
                    }
                    else
                    {
                        // Stop timer
                        StopTimer32 ();
                    }

                    // Update menu
                    ModifyMenu (GetMenu (hWnd), wmId, MF_STRING, wmId, tstate32.bTimerStarted ? "Stop" : "Start");
                    DrawMenuBar (hWnd);
                    break;

                case IDM_TIMER16_CLEAR:
                    (*pResetMaxMin3216) ();
                    break;

                case IDM_TIMER32_CLEAR:
                    ResetMaxMin32 ();
                    break;

                case IDM_TIMER32_T1000:
                case IDM_TIMER32_T500:
                case IDM_TIMER32_T100:
                case IDM_TIMER32_T50:
                case IDM_TIMER32_T10:
                case IDM_TIMER32_T5:
                    CheckMenuItem (GetMenu (hWnd), uiChecked32, MF_UNCHECKED);
                    CheckMenuItem (GetMenu (hWnd), uiChecked32 = wmId, MF_CHECKED);
                    tstate32.uiPeriod = uiPeriodMenuMap [wmId - IDM_TIMER32_T1000];

                    // If timer started, stop, reset, and restart with new period
                    if (tstate32.bTimerStarted)
                    {
                        StopTimer32 ();
                        ResetMaxMin32 ();
                        StartTimer32 (tstate32.uiPeriod, hWnd);
                    }
                    break;

                case IDM_TIMER16_T1000:
                case IDM_TIMER16_T500:
                case IDM_TIMER16_T100:
                case IDM_TIMER16_T50:
                case IDM_TIMER16_T10:
                case IDM_TIMER16_T5:
                    CheckMenuItem (GetMenu (hWnd), uiChecked16, MF_UNCHECKED);
                    CheckMenuItem (GetMenu (hWnd), uiChecked16 = wmId, MF_CHECKED);
                    tstate16.uiPeriod = uiPeriodMenuMap [wmId - IDM_TIMER16_T1000];

                    // If timer started, stop, reset, and restart with new period
                    if (tstate16.bTimerStarted)
                    {
                        (*pStopTimer3216) ();
                        (*pResetMaxMin3216) ();
                        (*pStartTimer3216) (tstate16.uiPeriod, hWnd);
                    }
                    break;

                // Only one of the timer procedures can have the Midi Mapper open.
                // Cannot open the mapper here and share between 16- and 32-bit timer
                // procedures as size of handle varies (32 bits in Win32, 16 bits in Win16).
                case IDM_TIMER16_SOUND:
                    tstate16.bSoundEnabled = !tstate16.bSoundEnabled;
                    CheckMenuItem (GetMenu (hWnd), wmId, tstate16.bSoundEnabled ? MF_CHECKED : MF_UNCHECKED);

                    if (tstate16.bSoundEnabled)
                    {
                        // First disable sound on 32-bit proc
                        if (tstate32.bSoundEnabled)
                        {
                            DisableSound32 ();
                            tstate32.bSoundEnabled = FALSE;
                            CheckMenuItem (GetMenu (hWnd), IDM_TIMER32_SOUND, MF_UNCHECKED);
                        }
                        // Enable sound on 16-bit proc

                        (*pEnableSound3216) ();
                    }
                    else
                    {
                        // Disable sound on 16-bit proc
                        (*pDisableSound3216) ();
                    }
                    break;
                case IDM_TIMER32_SOUND:
                    tstate32.bSoundEnabled = !tstate32.bSoundEnabled;
                    CheckMenuItem (GetMenu (hWnd), wmId, tstate32.bSoundEnabled ? MF_CHECKED : MF_UNCHECKED);

                    if (tstate32.bSoundEnabled)
                    {
                        // First disable sound on 16-bit proc
                        if (tstate16.bSoundEnabled)
                        {
                            (*pDisableSound3216) ();
                            tstate16.bSoundEnabled = FALSE;
                            CheckMenuItem (GetMenu (hWnd), IDM_TIMER16_SOUND, MF_UNCHECKED);
                        }
                        // Enable sound on 32-bit proc
                        EnableSound32 ();
                    }
                    else
                    {
                        // Disable sound on 32-bit proc
                        DisableSound32 ();
                    }
                    break;
                    
                case IDM_EXIT:
                    DestroyWindow (hWnd);
                    break;

                default:
                    return (DefWindowProc(hWnd, message, wParam, lParam));
            }
            // Force redraw of client area
            InvalidateRect (hWnd, NULL, TRUE);
            break;


        case WM_CREATE:
            // Check for availability of Midi
            if (midiOutGetNumDevs () == 0)
            {
                // No Midi output devices, disable sound options
                EnableMenuItem (GetMenu (hWnd), IDM_TIMER16_SOUND, MF_BYCOMMAND | MF_GRAYED);
                EnableMenuItem (GetMenu (hWnd), IDM_TIMER32_SOUND, MF_BYCOMMAND | MF_GRAYED);
            }
            
            break;

        case WM_DESTROY:
            // Make sure timers are killed and MIDI output devices are closed
            StopTimer32 ();
            DisableSound32 ();

            if (IS_WIN95)
            {
                (*pStopTimer3216) ();
                (*pDisableSound3216) ();
            }
            
            PostQuitMessage(0);
            break;

        // My secret little messages to myself
        case WM_MAX_PERIOD32:
            tstate32.dwMaxPeriod = lParam;
            InvalidateRect (hWnd, NULL, TRUE);
            break;

        case WM_MIN_PERIOD32:
            tstate32.dwMinPeriod = lParam;
            InvalidateRect (hWnd, NULL, TRUE);
            break;

        case WM_MAX_PERIOD16:
            tstate16.dwMaxPeriod = lParam;
            InvalidateRect (hWnd, NULL, TRUE);
            break;

        case WM_MIN_PERIOD16:
            tstate16.dwMinPeriod = lParam;
            InvalidateRect (hWnd, NULL, TRUE);
            break;

        case WM_REENTERED32:
        case WM_REENTERED16:
            break;

        case WM_PAINT:
            hdc = BeginPaint (hWnd, &ps);
            SetBkMode (hdc, TRANSPARENT);

            if (bShowTimerCaps)
            {
                // Display timer capabilities
                timeGetDevCaps (&timecaps, sizeof (TIMECAPS));
                wsprintf (szTextOut, "Timer Capabilities:\nMinimum supported period is %d msec\nMaximum supported period is %d msec",
                          timecaps.wPeriodMin, timecaps.wPeriodMax);
                MyTextOut (hdc, 0, 0, szTextOut);
            }

            else
            {
                if (IS_NT)
                {
                    // Display min/max period data for 32-bit timer proc
                    wsprintf (szTextOut, "32-bit timer proc: %s\nPeriod = %d msec\nMaximum period = %d msec\nMinimum period = %d msec",
                              tstate32.bTimerStarted ? "Started" : "Stopped", tstate32.uiPeriod, tstate32.dwMaxPeriod, tstate32.dwMinPeriod);
                }
                else
                {
                    // Display min/max period data for 16- and 32-bit timer procs
                    wsprintf (szTextOut, "32-bit timer proc: %s\nPeriod = %d msec\nMaximum period = %d msec\nMinimum period = %d msec\n\n16-bit timer proc: %s\nPeriod = %d msec\nMaximum period = %d msec\nMinimum period = %d msec",
                              tstate32.bTimerStarted ? "Started" : "Stopped", tstate32.uiPeriod, tstate32.dwMaxPeriod, tstate32.dwMinPeriod,
                              tstate16.bTimerStarted ? "Started" : "Stopped", tstate16.uiPeriod, tstate16.dwMaxPeriod, tstate16.dwMinPeriod);
                }
                MyTextOut (hdc, 0, 0, szTextOut);
            }

            EndPaint (hWnd, &ps);
            break;

        default:
            return (DefWindowProc(hWnd, message, wParam, lParam));
    }
    return (0);
}

// Multiline text out function similar to TextOut.
// Breaks lines at newline character.
// Not robust by any means.

void MyTextOut (HDC hdc, int nXStart, int nYStart, LPCTSTR lpString)
{
    TCHAR szTextOut[256];
    LPCTSTR lptstrIn;
    LPTSTR lptstrOut;
    int nX, nY, nCh;
    SIZE sizeText;

    lptstrIn = lpString;
    nX = nXStart;
    nY = nYStart;

    while (*lptstrIn != '\0')
    {
        // Copy string until newline or NULL encountered
        lptstrOut = szTextOut;
        while ((*lptstrIn != '\n') && (*lptstrIn != '\0'))
        {
            *lptstrOut++ = *lptstrIn++;
        }

        // Null-terminate and output current line
        *lptstrOut++ = '\0';
        nCh = strlen (szTextOut);
        TextOut (hdc, nX, nY, szTextOut, nCh);

        // Adjust y-pos for next line of text
        if (*lptstrIn != '\n')
        {
            // Get extent for this line of text
            GetTextExtentPoint32 (hdc, szTextOut, nCh, &sizeText);
        }
        else
        {
            // Get extent for blank line
            GetTextExtentPoint32 (hdc, " ", 1, &sizeText);
        }
        nY += sizeText.cy;

        // Skip newline character
        if (*lptstrIn == '\n')
        {
            ++lptstrIn;
        }
    }
}


//
//  FUNCTION: About(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for "About" dialog box
//      This version allows greater flexibility over the contents of the 'About' box,
//      by pulling out values from the 'Version' resource.
//
//  MESSAGES:
//
//  WM_INITDIALOG - initialize dialog box
//  WM_COMMAND    - Input received
//
//
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    static  HFONT hfontDlg;     // Font for dialog text
    static  HFONT hFinePrint;   // Font for 'fine print' in dialog
    DWORD   dwVerInfoSize;      // Size of version information block
    LPSTR   lpVersion;          // String pointer to 'version' text
    DWORD   dwVerHnd=0;         // An 'ignored' parameter, always '0'
    UINT    uVersionLen;
    WORD    wRootLen;
    BOOL    bRetCode;
    int     i;
    char    szFullPath[256];
    char    szResult[256];
    char    szGetName[256];
    DWORD   dwVersion;
    char    szVersion[40];
    DWORD   dwResult;

    switch (message) {
        case WM_INITDIALOG:
            ShowWindow (hDlg, SW_HIDE);
            hfontDlg = CreateFont(14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                VARIABLE_PITCH | FF_SWISS, "");
            hFinePrint = CreateFont(11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                VARIABLE_PITCH | FF_SWISS, "");
            CenterWindow (hDlg, GetWindow (hDlg, GW_OWNER));
            GetModuleFileName (hInst, szFullPath, sizeof(szFullPath));

            // Now lets dive in and pull out the version information:
            dwVerInfoSize = GetFileVersionInfoSize(szFullPath, &dwVerHnd);
            if (dwVerInfoSize) {
                LPSTR   lpstrVffInfo;
                HANDLE  hMem;
                hMem = GlobalAlloc(GMEM_MOVEABLE, dwVerInfoSize);
                lpstrVffInfo  = GlobalLock(hMem);
                GetFileVersionInfo(szFullPath, dwVerHnd, dwVerInfoSize, lpstrVffInfo);
                // The below 'hex' value looks a little confusing, but
                // essentially what it is, is the hexidecimal representation
                // of a couple different values that represent the language
                // and character set that we are wanting string values for.
                // 040904E4 is a very common one, because it means:
                //   US English, Windows MultiLingual characterset
                // Or to pull it all apart:
                // 04------        = SUBLANG_ENGLISH_USA
                // --09----        = LANG_ENGLISH
                // ----04E4 = 1252 = Codepage for Windows:Multilingual
                lstrcpy(szGetName, "\\StringFileInfo\\040904E4\\");  
                wRootLen = lstrlen(szGetName); // Save this position
            
                // Set the title of the dialog:
                lstrcat (szGetName, "ProductName");
                bRetCode = VerQueryValue((LPVOID)lpstrVffInfo,
                    (LPSTR)szGetName,
                    (LPVOID)&lpVersion,
                    (UINT *)&uVersionLen);
                lstrcpy(szResult, "About ");
                lstrcat(szResult, lpVersion);
                SetWindowText (hDlg, szResult);

                // Walk through the dialog items that we want to replace:
                for (i = DLG_VERFIRST; i <= DLG_VERLAST; i++) {
                    GetDlgItemText(hDlg, i, szResult, sizeof(szResult));
                    szGetName[wRootLen] = (char)0;
                    lstrcat (szGetName, szResult);
                    uVersionLen   = 0;
                    lpVersion     = NULL;
                    bRetCode      =  VerQueryValue((LPVOID)lpstrVffInfo,
                        (LPSTR)szGetName,
                        (LPVOID)&lpVersion,
                        (UINT *)&uVersionLen);

                    if ( bRetCode && uVersionLen && lpVersion) {
                    // Replace dialog item text with version info
                        lstrcpy(szResult, lpVersion);
                        SetDlgItemText(hDlg, i, szResult);
                    } else {
                        dwResult = GetLastError();
                        wsprintf (szResult, "Error %lu", dwResult);
                        SetDlgItemText (hDlg, i, szResult);
                    }
                    SendMessage (GetDlgItem (hDlg, i), WM_SETFONT, 
                        (UINT)((i==DLG_VERLAST)?hFinePrint:hfontDlg),
                        TRUE);
                } // for (i = DLG_VERFIRST; i <= DLG_VERLAST; i++)


                GlobalUnlock(hMem);
                GlobalFree(hMem);

            } else {
                // No version information available.
            } // if (dwVerInfoSize)

            SendMessage (GetDlgItem (hDlg, IDC_LABEL), WM_SETFONT,
                (WPARAM)hfontDlg,(LPARAM)TRUE);

            // We are  using GetVersion rather then GetVersionEx
            // because earlier versions of Windows NT and Win32s
            // didn't include GetVersionEx:
            dwVersion = GetVersion();

            if (dwVersion < 0x80000000) {
                // Windows NT
                wsprintf (szVersion, "Microsoft Windows NT %u.%u (Build: %u)",
                    (DWORD)(LOBYTE(LOWORD(dwVersion))),
                    (DWORD)(HIBYTE(LOWORD(dwVersion))),
                    (DWORD)(HIWORD(dwVersion)) );
            } else if (LOBYTE(LOWORD(dwVersion))<4) {
                // Win32s
                wsprintf (szVersion, "Microsoft Win32s %u.%u (Build: %u)",
                    (DWORD)(LOBYTE(LOWORD(dwVersion))),
                    (DWORD)(HIBYTE(LOWORD(dwVersion))),
                    (DWORD)(HIWORD(dwVersion) & ~0x8000) );
            } else {
                // Windows 95
                wsprintf (szVersion, "Microsoft Windows 95 %u.%u",
                    (DWORD)(LOBYTE(LOWORD(dwVersion))),
                    (DWORD)(HIBYTE(LOWORD(dwVersion))) );
            }

            SetWindowText (GetDlgItem(hDlg, IDC_OSVERSION), szVersion);
            ShowWindow (hDlg, SW_SHOW);
            return (TRUE);

        case WM_COMMAND:
            if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
                EndDialog(hDlg, TRUE);
                DeleteObject (hfontDlg);
                DeleteObject (hFinePrint);
                return (TRUE);
            }
            break;
    }

    return FALSE;
}

//
//   FUNCTION: CenterWindow(HWND, HWND)
//
//   PURPOSE: Centers one window over another. 
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
//      This functionwill center one window over another ensuring that 
//      the placement of the window is within the 'working area', meaning 
//      that it is both within the display limits of the screen, and not 
//      obscured by the tray or other framing elements of the desktop.
BOOL CenterWindow (HWND hwndChild, HWND hwndParent)
{
    RECT    rChild, rParent, rWorkArea;
    int     wChild, hChild, wParent, hParent;
    int     xNew, yNew;
    BOOL    bResult;

    // Get the Height and Width of the child window
    GetWindowRect (hwndChild, &rChild);
    wChild = rChild.right - rChild.left;
    hChild = rChild.bottom - rChild.top;

    // Get the Height and Width of the parent window
    GetWindowRect (hwndParent, &rParent);
    wParent = rParent.right - rParent.left;
    hParent = rParent.bottom - rParent.top;

    // Get the limits of the 'workarea'
    bResult = SystemParametersInfo(
        SPI_GETWORKAREA,    // system parameter to query or set
        sizeof(RECT),
        &rWorkArea,
        0);
    if (!bResult) {
        rWorkArea.left = rWorkArea.top = 0;
        rWorkArea.right = GetSystemMetrics(SM_CXSCREEN);
        rWorkArea.bottom = GetSystemMetrics(SM_CYSCREEN);
    }

    // Calculate new X position, then adjust for workarea
    xNew = rParent.left + ((wParent - wChild) /2);
    if (xNew < rWorkArea.left) {
        xNew = rWorkArea.left;
    } else if ((xNew+wChild) > rWorkArea.right) {
        xNew = rWorkArea.right - wChild;
    }

    // Calculate new Y position, then adjust for workarea
    yNew = rParent.top  + ((hParent - hChild) /2);
    if (yNew < rWorkArea.top) {
        yNew = rWorkArea.top;
    } else if ((yNew+hChild) > rWorkArea.bottom) {
        yNew = rWorkArea.bottom - hChild;
    }

    // Set it, and return
    return SetWindowPos (hwndChild, NULL, xNew, yNew, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}
