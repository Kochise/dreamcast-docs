#define APPNAME "AutoRun"

/******************************************************************************\
    PROGRAM:    AutoRun.C
    Author:     Robert B. Hess
    Date:       1-Oct-94
\******************************************************************************/
// The program will be executed relative to the root of the CD,
// no drive letter is necessary.  We strongly recommend that the
// autorun application be a small fast loading executable that
// immediatly presents the option to discontiue execution of the
// autorun.  This is to give the user an easy way out if they did
// not expect, or intend to launch an application.  Autorun CD's
// should always present an uninstall option to clean up the
// hardrive at the users request.  In general Autorun CD's should
// be very cautious about leaving anything on the users hardrive
// on closing.

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
#include "AUTORUN.h"

/////////////////////////////////////////////////////////////////////////
// Global Variables:

HINSTANCE hInst; // current instance
char szAppName[] = APPNAME; // The name of this application
char szTitle[]   = APPNAME": Sample"; // The title bar text
char szHelpFileName[] = APPNAME".HLP";

/////////////////////////////////////////////////////////////////////////
// Foward declarations of functions included in this code module:

BOOL InitApplication(HINSTANCE);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL CenterWindow (HWND, HWND);
LRESULT CALLBACK About(HWND, UINT, WPARAM, LPARAM);

// The following functions were added to Generic for this AutoRun sample app:
int OnCreate (HWND hWnd);
BOOL LaunchApplication(void);


/************************************************************************\
 *    FUNCTION: WinMain
\************************************************************************/

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	HANDLE hAccelTable;

	if (!hPrevInstance) { // Will always be TRUE on Windows 95
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
		SetForegroundWindow (GetLastActivePopup (hwnd));	
		// If this app actually had any functionality, we would
		// also want to communicate any action that our 'twin'
		// should now perform based on how the user tried to
		// execute us.
		return FALSE;
	}

	// Fill in window class structure with parameters that describe
	// the main window.
	wc.lpszClassName = szAppName;
	wc.style         = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc   = (WNDPROC)WndProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = 0;
	wc.hInstance     = hInstance;
	wc.lpszMenuName  = NULL;
	wc.hIcon         = LoadIcon (hInstance, szAppName);
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);

	return RegisterClass(&wc);
}


/************************************************************************\
 *    FUNCTION: InitInstance
\************************************************************************/

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	
	hInst = hInstance; // Store instance handle in our global variable

	// Lets replace the default window title, with the name of the
	// actual application we want to launch...
	LoadString (hInst, ID_APPNAME, szTitle, sizeof(szTitle));

	hWnd = CreateWindow(szAppName, szTitle, 
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
		0, 0,
		0, 0,
		NULL, NULL, hInstance, NULL);

	if (!hWnd) {
		return (FALSE);
	}

	// Set the small icon
#if !defined(WM_SETICON)
#define WM_SETICON 0x0080
#endif
	SendMessage(hWnd, WM_SETICON, FALSE, (LPARAM)LoadIcon(hInst, "SMALL"));

	ShowWindow(hWnd, nCmdShow);

	return UpdateWindow(hWnd);
}


/************************************************************************\
 *    FUNCTION: WndProc
\************************************************************************/

HPALETTE hpal;
HBITMAP hbmAutoRun;
BITMAP bmAutoRun;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	UINT uMappedColors; // Used in WM_QUERYNEWPALETTE
	RECT rect; // Used in WM_PAINT
	HDC  hdcSrc; // Used in WM_PAINT
	HBITMAP hbmOld; // Used in WM_PAINT


	switch (message) {

		case WM_CREATE:
			return OnCreate (hWnd);

		case WM_PALETTECHANGED:
			if ((HWND)wParam == hWnd) {
				break;
			}

			// fall through to WM_QUERYNEWPALETTE

		case WM_QUERYNEWPALETTE:
			hdc = GetDC(hWnd);

			if (hpal) {
				SelectPalette(hdc, hpal, FALSE);
			}

			uMappedColors = RealizePalette(hdc);
			ReleaseDC(hWnd,hdc);

			if (uMappedColors>0) {
				InvalidateRect(hWnd,NULL,TRUE);
				return TRUE;
			} else {
				return FALSE;
			}
			break;

		case WM_COMMAND:
			wmId    = LOWORD(wParam); // Remember, these are...
			wmEvent = HIWORD(wParam); // ...different for Win32!
		
			switch (wmId) {

				case IDM_CONTINUE:
					if (!LaunchApplication()) {
						// Failed to launch your application, you need
						// to decide what to do in this case and add code
						// to do that here. You can use GetLastError() to
						// determine the cause of this failure.
					} else {
						PostMessage (hWnd, WM_CLOSE, 0, 0);
					}
					break;

				case IDM_EXIT:
					DestroyWindow (hWnd);
					break;

				case IDM_ABOUT:
					DialogBox(hInst, "AboutBox", hWnd, (DLGPROC)About);
					break;

				case IDM_HELPCONTENTS:
					WinHelp (hWnd, szHelpFileName, HELP_CONTENTS,(DWORD)0);
					break;

				default:
					return (DefWindowProc(hWnd, message, wParam, lParam));
			}
			break;

		case WM_PAINT:
			hdc = BeginPaint (hWnd, &ps);
			SelectPalette(hdc, hpal, FALSE);
			RealizePalette(hdc);
			
			GetClientRect (hWnd, &rect);
			hdcSrc = CreateCompatibleDC (hdc);
			hbmOld = SelectObject (hdcSrc, hbmAutoRun);
			SelectPalette(hdcSrc, hpal, FALSE);
			RealizePalette(hdcSrc);
			if (!BitBlt (hdc, 0, 0, bmAutoRun.bmWidth, bmAutoRun.bmHeight, hdcSrc, 0, 0, SRCCOPY)) {
				MessageBeep(0);
			}
			SelectObject (hdcSrc, hbmOld);
			DeleteDC (hdcSrc);
			EndPaint (hWnd, &ps);
			break;        

		case WM_DESTROY:
			// Tell WinHelp we don't need it any more...
			WinHelp (hWnd, APPNAME".HLP", HELP_QUIT,(DWORD)0);
			DeleteObject (hpal);
			DeleteObject (hbmAutoRun);
			PostQuitMessage(0);
			break;

		default:
			return (DefWindowProc(hWnd, message, wParam, lParam));
	}
	return (0);
}


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
	int     wScreen, hScreen, xScreen, yScreen, xNew, yNew;
	BOOL bResult;

	// Get the Height and Width of the child window
	GetWindowRect (hwndChild, &rChild);
	wChild = rChild.right - rChild.left;
	hChild = rChild.bottom - rChild.top;

	// Get the Height and Width of the parent window
	GetWindowRect (hwndParent, &rParent);
	wParent = rParent.right - rParent.left;
	hParent = rParent.bottom - rParent.top;

	// Get the limits of the 'workarea'
#if !defined(SPI_GETWORKAREA)
#define SPI_GETWORKAREA 48
#endif
	bResult = SystemParametersInfo(
    	SPI_GETWORKAREA,	// system parameter to query or set
    	sizeof(RECT),	// depends on action to be taken
    	&rWorkArea,	// depends on action to be taken
    	0);	

	wScreen = rWorkArea.right - rWorkArea.left;
	hScreen = rWorkArea.bottom - rWorkArea.top;
	xScreen = rWorkArea.left;
	yScreen = rWorkArea.top;

	// On Windows NT, the above metrics aren't valid (yet), so they all return
	// '0'. Lets deal with that situation properly:
	if (wScreen==0 && hScreen==0) {
		wScreen = GetSystemMetrics(SM_CXSCREEN);
		hScreen = GetSystemMetrics(SM_CYSCREEN);
		xScreen = 0; // These values should already be '0', but just in case
		yScreen = 0;
	}

	// Calculate new X position, then adjust for screen
	xNew = rParent.left + ((wParent - wChild) /2);
	if (xNew < xScreen) {
		xNew = xScreen;
	} else if ((xNew+wChild) > wScreen) {
		xNew = (xScreen + wScreen) - wChild;
	}

	// Calculate new Y position, then adjust for screen
	yNew = rParent.top  + ((hParent - hChild) /2);
	if (yNew < yScreen) {
		yNew = yScreen;
	} else if ((yNew+hChild) > hScreen) {
		yNew = (yScreen + hScreen) - hChild;
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
	UINT    uVersionLen;
	WORD    wRootLen;
	BOOL    bRetCode;
	int     i;
	char    szFullPath[256];
	char    szResult[256];
	char    szGetName[256];
	DWORD	dwVersion;
	char	szVersion[40];
	DWORD	dwResult;

	switch (message) {
		case WM_INITDIALOG:
			ShowWindow (hDlg, SW_HIDE);
			hfontDlg = GetStockObject (ANSI_VAR_FONT);
			hFinePrint = CreateFont(11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
				VARIABLE_PITCH | FF_SWISS, "");
			CenterWindow (hDlg, GetWindow (hDlg, GW_OWNER));
			GetModuleFileName (hInst, szFullPath, sizeof(szFullPath));

			// Now lets dive in and pull out the version information:
			dwVerInfoSize = GetFileVersionInfoSize(szFullPath, &dwVerHnd);
			if (dwVerInfoSize) {
				LPSTR   lpstrVffInfo = (LPVOID)LocalAlloc (LPTR, dwVerInfoSize);
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
				LocalFree ((HLOCAL)lpstrVffInfo);

			} else {
				// No version information available.
			} // if (dwVerInfoSize)

			SendMessage (GetDlgItem (hDlg, IDC_LABEL), WM_SETFONT, (WPARAM)hfontDlg,(LPARAM)TRUE);

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
				wsprintf (szVersion, "Microsoft Windows 95 (osv:%u.%u)",
					(DWORD)(LOBYTE(LOWORD(dwVersion))),
					(DWORD)(HIBYTE(LOWORD(dwVersion))) );
			}

			SetWindowText (GetDlgItem(hDlg, IDC_OSVERSION), szVersion);
			ShowWindow (hDlg, SW_SHOW);
			return (TRUE);

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) {
				EndDialog(hDlg, TRUE);
				return (TRUE);
			}
			break;

		case WM_DESTROY:
			DeleteObject (hFinePrint);
			break;			
	}

	return FALSE;
}


/************************************************************************\
 *    FUNCTION: OnCreate
\************************************************************************/
// This function will be called when the WM_CREATE message is processed
// by our application. This is where we will load the bitmap to be
// displayed, create a palette for the image, resize the window to fit
// the bitmap, and put in our control buttons that will allow the user
// to tell us how to proceed.

int OnCreate(HWND hWnd)
{
	HDC hdc;
	RECT rect;
	HFONT hfontBtn;
	HWND hwndBtnOk, hwndBtnExit;

	int i;
	LPBITMAPINFO lpbmi;

	LPVOID lpv;
	HRSRC hrsrc;
	DWORD dwSize;

	LOGPALETTE *plgpl;
	int cColors;
	LPVOID pimage;
	TEXTMETRIC tm;
	int iHeight, iWidth, x, y;

	BOOL fPalette = FALSE;
	BOOL fTrueColor = FALSE;

	char szString[20];

	hdc = GetDC(hWnd);

	hpal = NULL;

	fPalette = GetDeviceCaps (hdc, RASTERCAPS) & RC_PALETTE;
	fTrueColor = ((GetDeviceCaps(hdc, BITSPIXEL) * GetDeviceCaps(hdc, PLANES))>=32);

	// At this point, 'fPalette' will be true if we are running
	// on a display that supports (and -needs- to support) the
	// palette manager. 'fTrueColor' will be true if the display
	// we are running on can handle any color we can throw at
	// it, thus doesn't need to use the palette manager. If
	// either of these are true, then we can display our full
	// color image, otherwise, we need to shift down to our
	// 16 color version.

	if (fPalette || fTrueColor) {
		// Locate the resource:
		hrsrc = FindResource(hInst, "AUTORUN", RT_BITMAP);
		// Lock it down. This will give us a memory pointer:
		lpv = LockResource(LoadResource(hInst,hrsrc));
		// Find out how big the resource was:
		dwSize = SizeofResource(hInst,hrsrc);
		// Allocate enough memory:
		lpbmi = (LPBITMAPINFO)LocalAlloc (LPTR, dwSize);
		if (!lpbmi) return -1; // failure
		// And make our own private copy of the data:
		memcpy (lpbmi, lpv, dwSize);

		// How many colors does it use?:
		cColors = lpbmi->bmiHeader.biClrUsed;
		if (cColors == 0) {
			cColors = (1 << (int)(lpbmi)->bmiHeader.biBitCount);
		}

		// Use that to determine where the actual bitmap image starts:
		pimage = &(lpbmi->bmiColors[cColors]);

		// Now lets create a palette based on the image we loaded:
		plgpl = (LPVOID)LocalAlloc (LPTR, sizeof(LOGPALETTE) + (cColors-1)*sizeof(PALETTEENTRY));
		if (!plgpl) return -1; // failure

		plgpl->palVersion = 0x300;
		plgpl->palNumEntries = cColors;
		for (i=0; i<cColors; i++) {
			plgpl->palPalEntry[i].peRed   = lpbmi->bmiColors[i].rgbRed;
			plgpl->palPalEntry[i].peGreen = lpbmi->bmiColors[i].rgbGreen;
			plgpl->palPalEntry[i].peBlue  = lpbmi->bmiColors[i].rgbBlue;
			//plgpl->palPalEntry[i].peFlags = PC_NOCOLLAPSE; // is this needed?
		}
		hpal = CreatePalette(plgpl);

		// And free up the memory we allocated:
		LocalFree ((HLOCAL)plgpl);

		if (!hpal) return -1; // Fail on no palette

		// Now create a true DIBitmap from all of this:
		// First assign the palette to the DC:
		SelectPalette(hdc, hpal, FALSE);
		RealizePalette(hdc);

		// Now create a DIB based off the the DC with the bitmap image from the resource:
		hbmAutoRun = CreateDIBitmap (hdc, (BITMAPINFOHEADER *)lpbmi,
			CBM_INIT, pimage, lpbmi, DIB_RGB_COLORS);

		LocalFree (lpbmi);

	} else {
		// At this point, you know that the current display
		// device does not support palettes. So you may want
		// to keep track of this and later warn the user that
		// they may not get the full visual impact of your
		// application...
		hbmAutoRun = NULL; // just to make sure we force load the 16 color version
	}

	if (!hbmAutoRun) {
		hbmAutoRun = LoadBitmap (hInst, "AUTO16"); // whimpy 16 color version...
		if (!hbmAutoRun) {
			return -1;
		}
	}

	// And get the header data:
	GetObject (hbmAutoRun, sizeof(BITMAP), &bmAutoRun);

	SetWindowPos (hWnd, NULL, 0, 0, bmAutoRun.bmWidth, bmAutoRun.bmHeight,
		SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
	// Since what we really want to do is size the 'Client' window,
	// Lets find out how far off we were, adjust our values, and
	// try it again...
	GetClientRect (hWnd, &rect);
	x = bmAutoRun.bmWidth - (rect.right-rect.left);
	y = bmAutoRun.bmHeight - (rect.bottom-rect.top);
	SetWindowPos (hWnd, NULL, 0, 0, bmAutoRun.bmWidth+x,
		bmAutoRun.bmHeight+y, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);

	CenterWindow (hWnd, GetDesktopWindow ());

	// Ok, our image is loaded, and our window properly sized
	// Lets add in some controls: The text to use for these
	// buttons is coming out of the resource of this app
	LoadString (hInst, IDM_CONTINUE, szString, sizeof(szString));
	hwndBtnOk = CreateWindow ("BUTTON", szString,
		WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE | BS_DEFPUSHBUTTON,
		0, 0, 0, 0,
		hWnd, (HMENU)IDM_CONTINUE, hInst, NULL);

	LoadString (hInst, IDM_EXIT, szString, sizeof(szString));
	hwndBtnExit = CreateWindow ("BUTTON", szString, 
		WS_CHILD | WS_CLIPSIBLINGS | WS_VISIBLE | BS_PUSHBUTTON,
		0, 0, 0, 0,
		hWnd, (HMENU)IDM_EXIT, hInst, NULL);

	hfontBtn = GetStockObject (ANSI_VAR_FONT);
	SendMessage (hwndBtnOk, WM_SETFONT, (WPARAM)hfontBtn,(LPARAM)TRUE);
	SendMessage (hwndBtnExit, WM_SETFONT, (WPARAM)hfontBtn, (LPARAM)TRUE);
	SelectObject (hdc, hfontBtn);
	GetTextMetrics (hdc, &tm);

	iHeight = (tm.tmHeight + tm.tmExternalLeading) * 2;
	iWidth = (bmAutoRun.bmWidth / 2) - (iHeight * 2);
			
	x = ((bmAutoRun.bmWidth/2) / 2) - (iWidth/2);
	y = bmAutoRun.bmHeight - iHeight - (iHeight/2);

	SetWindowPos (hwndBtnExit, NULL, x, y, iWidth, iHeight,
		SWP_NOZORDER | SWP_NOACTIVATE);

	x += bmAutoRun.bmWidth/2;
	SetWindowPos (hwndBtnOk, NULL, x, y, iWidth, iHeight,
		SWP_NOZORDER | SWP_NOACTIVATE);

	ShowWindow (hWnd, SW_SHOW);

	ReleaseDC (hWnd, hdc);

	return 0; // Sucess
	
}

/************************************************************************\
 *    FUNCTION: 
\************************************************************************/
// This function is called to launch the 'real' application when the
// user instructs us to. The name of the application to be run is coming
// out of the resource of this app.
BOOL LaunchApplication(void)
{
	char szCompany[40];
	char szImageName[40];
	char szCmdLine[40];

	STARTUPINFO         si;
	PROCESS_INFORMATION pi;

	LoadString (hInst, ID_COMPANY, szCompany, sizeof(szCompany));
	LoadString (hInst, ID_APPNAME, szImageName, sizeof(szImageName));
	strcat (szImageName, ".EXE");
	LoadString (hInst, ID_CMDLINE, szCmdLine, sizeof(szCmdLine));

	si.cb = sizeof(STARTUPINFO);
	// Yeah, this could be done with a 'memset', but this is more illustrative:
	si.lpReserved =
		si.lpDesktop =
		si.lpTitle	=
		si.dwX	=
		si.dwY =
		si.dwXSize	=
		si.dwYSize =
		si.dwXCountChars =
		si.dwYCountChars =
		si.dwFillAttribute =
		si.dwFlags =
		si.wShowWindow =
		si.cbReserved2 =
		si.lpReserved2 =
		si.hStdInput =
		si.hStdOutput =
		si.hStdError =
		NULL;

	return CreateProcess (szImageName, szCmdLine, NULL, NULL, FALSE,
		CREATE_NEW_PROCESS_GROUP, NULL, NULL, &si, &pi);
}
