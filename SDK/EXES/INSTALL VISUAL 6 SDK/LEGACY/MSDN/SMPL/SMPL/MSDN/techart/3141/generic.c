#define APPNAME "Generic"

/******************************************************************************\
    PROGRAM:    Generic.C
    Author:     Robert B. Hess
    Date:       1-Sep-94
\******************************************************************************/
// This is a sample application to illustrate the 'minimum' functionality
// that should be expected of a well behaved Win32 application. Other
// then that, this application has virtually no actual functionality of
// its own. This makes it easier for you to use this as a starting point
// for your own application development, or investigation of the Win32
// API.

/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright (C) 1994 Microsoft Corporation.
*       All rights reserved.
*
*       THE INFORMATION AND CODE PROVIDED HEREUNDER (COLLECTIVELY REFERRED TO
*       AS "SOFTWARE") IS PROVIDED AS IS WITHOUT WARRANTY OF ANY KIND, EITHER
*       EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
*       WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. IN
*       NO EVENT SHALL MICROSOFT CORPORATION OR ITS SUPPLIERS BE LIABLE FOR
*       ANY DAMAGES WHATSOEVER INCLUDING DIRECT, INDIRECT, INCIDENTAL,
*       CONSEQUENTIAL, LOSS OF BUSINESS PROFITS OR SPECIAL DAMAGES, EVEN IF
*       MICROSOFT CORPORATION OR ITS SUPPLIERS HAVE BEEN ADVISED OF THE
*       POSSIBILITY OF SUCH DAMAGES. SOME STATES DO NOT ALLOW THE EXCLUSION OR
*       LIMITATION OF LIABILITY FOR CONSEQUENTIAL OR INCIDENTAL DAMAGES SO THE
*       FOREGOING LIMITATION MAY NOT APPLY.
*
\******************************************************************************/

// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>

// Local Header Files
#include "generic.h"

// Just to make it easier to determine appropriate code paths:
#if defined (WIN32) // This had better be true, but just in case...
	#define IS_WIN32 TRUE
#else
	#define IS_WIN32 FALSE
#endif
#define IS_NT      IS_WIN32 && (BOOL)(GetVersion() < 0x80000000)
#define IS_WIN32S  IS_WIN32 && (BOOL)(!(IS_NT) && (LOBYTE(LOWORD(GetVersion()))<4))
#define IS_CHICAGO (BOOL)(!(IS_NT) && !(IS_WIN32S)) && IS_WIN32

/////////////////////////////////////////////////////////////////////////
// Global Variables:

HINSTANCE hInst; // current instance
char szAppName[] = APPNAME; // The name of this application
char szTitle[]   = APPNAME": Sample Application"; // The title bar text

/////////////////////////////////////////////////////////////////////////
// Foward declarations of functions included in this code module:

ATOM MyRegisterClass(CONST WNDCLASS*);
BOOL InitApplication(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CenterWindow (HWND, HWND);
LRESULT CALLBACK About(HWND, UINT, WPARAM, LPARAM);


/************************************************************************\
 *    FUNCTION: WinMain
\************************************************************************/

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	HANDLE hAccelTable;

	if (!hPrevInstance) {
		// Perform instance initialization:
		if (!InitApplication(hInstance)) {
			return (FALSE);
		}
	}

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow)) {
		return (FALSE);
	}

	hAccelTable = LoadAccelerators (hInstance, szAppName);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)) {
		if (!TranslateAccelerator (msg.hwnd, hAccelTable, &msg)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (msg.wParam);

	lpCmdLine; // This will prevent 'unused formal parameter' warnings
}

/************************************************************************\
 *    FUNCTION: MyRegisterClass
\************************************************************************/
//
// This function and its usage is only necessary if you want this code
// to be compatible with Win32 systems prior to the 'RegisterClassEx'
// call added for Windows 95. Since it is important to call this function
// so that the application will get 'well formed' small icons aassociated
// with it. We will take the time to look for the function, and call it
// manually:

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


/************************************************************************\
 *    FUNCTION: InitApplication
\************************************************************************/

BOOL InitApplication(HINSTANCE hInstance)
{
	WNDCLASS  wc;
    HWND      hwnd;

    // Win32 will always set hPrevInstance to NULL, so lets check
    // things a little closer. This is because we only want a single
	// version of this app to run at a time
    hwnd = FindWindow (szAppName, NULL);
    if (hwnd) {
		// We found another version of ourself. Lets defer to it:
        if (IsIconic(hwnd)) {
            ShowWindow(hwnd, SW_RESTORE);
        }
        SetForegroundWindow (hwnd);
		// If this app actually had any functionality, we would
		// also want to communicate any action that our 'twin'
		// should now perform based on how the user tried to
		// execute us.
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

	// Since Windows 95 has a slightly different recommended
	// format for the 'Help' menu, lets just quickly slide
	// in the alternate menu like this:
	if (IS_CHICAGO) {
		wc.lpszMenuName  = "CHICAGO";
	} else {
		wc.lpszMenuName  = szAppName;
	}

	// And set the all-important class name:
	wc.lpszClassName = szAppName;

	// Register the window class and return success/failure code.
	// 'MyRegisterClass' will appropriately set the SmallIcon for
	// this class if we are running on Windows 95. Once you know that
	// all Win32 system properly deal with 'RegisterClassEx', you
	// can get rid of MyRegisterClass, and modify this code to
	// appropriately call 'RegisterClassEx'
	if (IS_CHICAGO) {
		return MyRegisterClass(&wc);
	} else {
		return RegisterClass(&wc);
	}
}


/************************************************************************\
 *    FUNCTION: InitInstance
\************************************************************************/

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	
	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindow(szAppName, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
		NULL, NULL, hInstance, NULL);

	if (!hWnd) {
		return (FALSE);
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return (TRUE);
}


/************************************************************************\
 *    FUNCTION: WndProc
\************************************************************************/

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
    POINT pnt;
    HMENU hMenu;
    BOOL bGotHelp;

	switch (message) { 

		case WM_COMMAND:
			wmId    = LOWORD(wParam); // Remember, these are...
			wmEvent = HIWORD(wParam); // ...different for Win32!

			// Deal with the menu selections:
			switch (wmId) {

				case IDM_ABOUT:
					// Make and FreeProcInstance aren't needed on Win32!
					//lpProcAbout = MakeProcInstance((FARPROC)About, hInst);
                    DialogBox(hInst, "AboutBox", hWnd, (DLGPROC)About);
					//FreeProcInstance(lpProcAbout);
					break;

				case IDM_EXIT:
					DestroyWindow (hWnd);
					break;

                case IDM_HELPTOPICS: // Only called on Windows 95
                    bGotHelp = WinHelp (hWnd, APPNAME".HLP", HELP_FINDER,(DWORD)0);
                    if (!bGotHelp) {
                        MessageBox (GetFocus(),"Unable to activate help",
                            szAppName, MB_OK|MB_ICONHAND);
					}
					break;

				case IDM_HELPCONTENTS: // Not called on Windows 95
                    bGotHelp = WinHelp (hWnd, APPNAME".HLP", HELP_CONTENTS,(DWORD)0);
                    if (!bGotHelp) {
                        MessageBox (GetFocus(),"Unable to activate help",
                            szAppName, MB_OK|MB_ICONHAND);
					}
					break;

				case IDM_HELPSEARCH: // Not called on Windows 95
                    if (!WinHelp(hWnd, APPNAME".HLP", HELP_PARTIALKEY, (DWORD)(LPSTR)"")) {
						MessageBox (GetFocus(), "Unable to activate help",
							szAppName, MB_OK|MB_ICONHAND);
					}
					break;

				case IDM_HELPHELP: // Not called on Windows 95
					if(!WinHelp(hWnd, (LPSTR)NULL, HELP_HELPONHELP, 0)) {
						MessageBox (GetFocus(), "Unable to activate help",
							szAppName, MB_OK|MB_ICONHAND);
					}
					break;

				// Here are all the other possible menu options,
				// all of these are currently disabled:
				case IDM_NEW:
				case IDM_OPEN:
				case IDM_SAVE:
				case IDM_SAVEAS:
				case IDM_UNDO:
				case IDM_CUT:
				case IDM_COPY:
				case IDM_PASTE:
				case IDM_LINK:
				case IDM_LINKS:

				default:
					return (DefWindowProc(hWnd, message, wParam, lParam));
			}
			break;

        case WM_LBUTTONDOWN:
			{
				// This would be one good place to put 'test' code. Thus
				// when you click the left button in the client area,
				// it would fire off the test code that you are wanting
				// to check out.
			}
            break;

        case WM_NCRBUTTONUP: // RightClick on windows non-client area...
			if (IS_CHICAGO && SendMessage(hWnd, WM_NCHITTEST, 0, lParam) == HTSYSMENU) {
				// The user has clicked the right button on the applications
				// 'System Menu'. Here is where you would alter the default
				// system menu to reflect your application. Notice how the
				// explorer deals with this. For this app, we aren't doing
				// anything
				return (DefWindowProc(hWnd, message, wParam, lParam));
			} else {
				// Nothing we are interested in, allow default handling...
				return (DefWindowProc(hWnd, message, wParam, lParam));
			}
            break;

        case WM_RBUTTONDOWN: // RightClick in windows client area...
            pnt.x = LOWORD(lParam);
            pnt.y = HIWORD(lParam);
            ClientToScreen(hWnd, (LPPOINT) &pnt);

			// This is where you would determine the appropriate 'context'
			// menu to bring up. Since this app has no real functionality,
			// we will just bring up the 'Help' menu:
            hMenu = GetSubMenu (GetMenu (hWnd), 2);
            if (hMenu) {
                TrackPopupMenu (hMenu, 0, pnt.x, pnt.y, 0, hWnd, NULL);
            } else {
				// Couldn't find the menu...
                MessageBeep(0);
            }
            break;


		case WM_DISPLAYCHANGE: // This is a Plug'n'Play message
		{
			SIZE szScreen;
			BOOL fChanged = (BOOL)wParam;

			szScreen.cx = LOWORD(lParam);
			szScreen.cy = HIWORD(lParam);
			
			if (fChanged) {
				// The display 'has' changed. szScreen reflects the
				// new size.
				MessageBox (GetFocus(), "Display Changed", szAppName, 0);
			} else {
				// The display 'is' changing. szScreen reflects the
				// original size.
				MessageBeep(0);
			}
		}
		break;

		case WM_PAINT:
			hdc = BeginPaint (hWnd, &ps);
			// Add any drawing code here...
			EndPaint (hWnd, &ps);
			break;        

		case WM_DESTROY:
			// Tell WinHelp we don't need it any more...
            WinHelp (hWnd, APPNAME".HLP", HELP_QUIT,(DWORD)0);
			PostQuitMessage(0);
			break;

		default:
			return (DefWindowProc(hWnd, message, wParam, lParam));
	}
	return (0);
}


//////////////////////////////////////////////////////////////////////////
//
// Extra Credit:
//
// The following routines are just the 'something extra' that programs
// should do in order to give the user a good experience.
//
//////////////////////////////////////////////////////////////////////////


/************************************************************************\
 *    FUNCTION: CenterWindow
\************************************************************************/
// This is a 'utility' function I find usefull. It will center one
// window over another. It also makes sure that the placement is within
// the 'working area', meaning that it is both within the display limits
// of the screen, -and- not obscured by the tray or other frameing
// elements of the desktop.
BOOL CenterWindow (HWND hwndChild, HWND hwndParent)
{
	RECT    rChild, rParent, rWorkArea = {0,0,0,0};
	int     wChild, hChild, wParent, hParent;
	int     xNew, yNew;
	BOOL	bResult;

	// Get the Height and Width of the child window
	GetWindowRect (hwndChild, &rChild);
	wChild = rChild.right - rChild.left;
	hChild = rChild.bottom - rChild.top;

	// Get the Height and Width of the parent window
	GetWindowRect (hwndParent, &rParent);
	wParent = rParent.right - rParent.left;
	hParent = rParent.bottom - rParent.top;

	// Get the limits of the 'workarea'
	bResult = SystemParametersInfo( SPI_GETWORKAREA, sizeof(RECT), &rWorkArea, 0);
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


/************************************************************************\
 *    FUNCTION: About
\************************************************************************/
// To allow us better flexibility over the contents of the 'About' box,
// lets go the extra mile and pull out values from the 'Version' resource.
// This means that by properly keeping that information up-to-date, it
// will automatically keep your about box information current. Remember,
// that the 'version' strings can also be seen from the 'Properties'
// page of FileManager on Windows NT, or the Explorer on Windows 95.

LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static  HFONT hfontDlg;		// Font for dialog text
	static	HFONT hFinePrint;	// Font for 'fine print' in dialog

	DWORD   dwVerInfoSize;		// Size of version information block
	LPSTR   lpVersion;			// String pointer to 'version' text
	DWORD   dwVerHnd=0;			// An 'ignored' parameter, always '0'
	UINT    uVersionLen;		// Current length of full version string
	WORD    wRootLen;			// length of the 'root' portion of string
	BOOL    bRetCode;			// Boolean returned value
	int     i;					// for the for loop
	char    szFullPath[256];	// full path of module
	char    szResult[256];		// Temporary result string
	char    szGetName[256];		// String to use for extracting version info
	DWORD	dwVersion;			// To hold return value from GetVersion
	char	szVersion[40];		// Temporary string for building output
	DWORD	dwResult;			// DWORD return value

	switch (message) {
		// When the dialog is first being initialized, we want to do a number
		// of things to 'customize' the look of this 'About' box.
		// 1. Substitute a 'non-bold' font for most of the text
		// 2. Substitute a 'fine print' font for the legal text at the
		//    bottom.
		// 3. Center the dialog over the parent window, and keep it within
		//    the limits of the screen.
		// 4. Substitute strings from the 'version' section of the resource
		//    for various strings in the dialog
		// 5. Display information regarding the 'version' of Windows that
		//    we are running on
		//
        case WM_INITDIALOG:
			ShowWindow (hDlg, SW_HIDE); // This probably doesn't really affect anything

			// Create some replacement fonts:
			hfontDlg = CreateFont(14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				VARIABLE_PITCH | FF_SWISS, "");
			hFinePrint = CreateFont(11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				VARIABLE_PITCH | FF_SWISS, "");

			// Reposition the dialog:
			CenterWindow (hDlg, GetWindow (hDlg, GW_OWNER));

			// Now lets dive in and pull out the version information:
			GetModuleFileName (hInst, szFullPath, sizeof(szFullPath));
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

			// Get the version information about Windows:
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
                wsprintf (szVersion, "Microsoft Windows 95  (osv: %u.%u)",
                    (DWORD)(LOBYTE(LOWORD(dwVersion))),
                    (DWORD)(HIBYTE(LOWORD(dwVersion))) );
			}

		    SetWindowText (GetDlgItem(hDlg, IDC_OSVERSION), szVersion);

			ShowWindow (hDlg, SW_SHOW);

			return (TRUE);

		case WM_COMMAND:
			// Only possible option is to close down. Make sure we
			// clean things up on our way out...
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
