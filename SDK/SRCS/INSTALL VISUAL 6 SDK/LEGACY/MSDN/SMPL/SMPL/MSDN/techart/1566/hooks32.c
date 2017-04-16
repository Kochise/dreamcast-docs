//---------------------------------------------------------------------------
//  Windows hooks Sample Application
//
//  This sample application demonstrates how to use Windows hooks.
//
//  Author:	Kyle Marsh
//              Windows Developer Technology Group
//              Microsoft Corp.
//
//---------------------------------------------------------------------------


#include "windows.h"
#include "string.h"
#include "hooks32.h"

//---------------------------------------------------------------------------
// Function declarations
//---------------------------------------------------------------------------

int PASCAL WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, LPSTR lpstrCmdLine, int cmdShow);
LONG FAR PASCAL HookSampleWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL FAR PASCAL About(HWND hDlg, unsigned message, WORD wParam, LONG lParam);
int FAR PASCAL MsgFilterFunc (int nCode, WORD wParam, DWORD lParam );
char FAR *szMessageString(int ID);

//---------------------------------------------------------------------------
// Global Variables...
//---------------------------------------------------------------------------

HINSTANCE hInstance;		  // Global instance handle for application
HWND	hwndMain;		// Main hwnd.  Needed in callback
int	nLineHeight;		// Heigth of lines in window

//
// Filter Function Addresses
//
FARPROC lpfnMsgFilterProc;

//
// Previous Hook Filter Function Pointers
//
HHOOK hhookMsgFilterHook;

//
// Output Lines
//
char szMsgFilterLine[128];

//---------------------------------------------------------------------------
// WinMain
//---------------------------------------------------------------------------

int PASCAL WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, LPSTR lpstrCmdLine, int cmdShow)
{
    MSG        msgMain;
    WNDCLASS   wc;
    HDC        hDC;
    TEXTMETRIC tm;

    //
    // Set the global instance variable
    //
    hInstance = hInst;

    //
    // Register the window class if this is the first instance.
    //
    if (hInstPrev == NULL)
    {
		wc.lpszMenuName		= "HookSampleMenu";
		wc.lpszClassName	= "HookSampleApp";
        wc.hInstance        = hInst;
		wc.hIcon			= LoadIcon(hInst, "HooksIcon");
        wc.hCursor          = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
        wc.style            = 0;
		wc.lpfnWndProc		= HookSampleWndProc;
        wc.cbClsExtra       = 0;
        wc.cbWndExtra       = 0;

        if (!RegisterClass(&wc))
            return(0);
    }

    //
    // Create the main window
    //
    if ((hwndMain = CreateWindow("HookSampleApp",
				 "Sample Hook Application",
                                 WS_OVERLAPPEDWINDOW,
                                 CW_USEDEFAULT, 0,
                                 CW_USEDEFAULT, CW_USEDEFAULT,
                                 NULL, NULL, hInst, NULL)) == NULL)
        return(0);

    //
    // Show the window and make sure it is updated.
    //
    ShowWindow(hwndMain, cmdShow);
    UpdateWindow(hwndMain);

    //
    // Work Out The height of lines
    //
    hDC = GetDC(hwndMain);
    GetTextMetrics(hDC, &tm);
    ReleaseDC(hwndMain, hDC);
    nLineHeight = tm.tmHeight+tm.tmExternalLeading;

    //
    // Let's pass the hwndMain to the DLL so it can update the Window
    //
    InitHooksDll(hwndMain, nLineHeight);

    //
    // Main message "pump"
    //
    while (GetMessage((LPMSG) &msgMain, NULL, 0, 0))
    {
       TranslateMessage((LPMSG) &msgMain);
       DispatchMessage((LPMSG) &msgMain);
    }


    return(0);
}



//---------------------------------------------------------------------------
// HookSampleWndProc
//
// Window procedure for the sample application's window.
//
//---------------------------------------------------------------------------


LONG FAR PASCAL HookSampleWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HMENU       hMenu;
    PAINTSTRUCT ps;
    HDC 	hDC;
    int 	nHookIndex;
    int 	i,State;

    switch(msg) {

	//
	// Handle menu selections
	//

		case WM_COMMAND:

			switch (LOWORD(wParam) ) {

			case IDM_MSGFILTER:
				//
				// Handle Application Message Filter
				// Change the checkmark to the proper item
				//
				hMenu = GetMenu(hwnd);
				State = CheckMenuItem(hMenu, wParam, MF_UNCHECKED | MF_BYCOMMAND);
				if ( State == MF_CHECKED ) {
				   UnhookWindowsHookEx(hhookMsgFilterHook);
				   strcpy(szMsgFilterLine,"                                                                   ");
				   hDC = GetDC(hwndMain);
				   TabbedTextOut(hDC, 1,nLineHeight * MSGFILTERINDEX,
					(LPSTR)szMsgFilterLine, strlen(szMsgFilterLine), 0, NULL, 1);
				   ReleaseDC(hwndMain, hDC);
				}
				else {
				   CheckMenuItem(hMenu, wParam, MF_CHECKED | MF_BYCOMMAND);
				   //
				   // Install the Hook
				   //
				   hhookMsgFilterHook = SetWindowsHookEx(WH_MSGFILTER,
														 MsgFilterFunc,
														 hInstance,
														 (DWORD)GetCurrentThreadId());
				}
				break;

			case IDM_CALLWNDPROC:
			case IDM_CBT:
			case IDM_GETMESSAGE:
			case IDM_JOURNALPLAYBACK:
			case IDM_JOURNALRECORD:
			case IDM_KEYBOARD:
			case IDM_MOUSE:
			case IDM_SYSMSGFILTER:
			case IDM_DEBUG:
				//
				// Handle the System Wide Filter
				// Change the checkmark to the proper item
				//
				nHookIndex = wParam - IDM_CALLWNDPROC;
				hMenu = GetMenu(hwnd);
				State = CheckMenuItem(hMenu, wParam, MF_UNCHECKED | MF_BYCOMMAND);
				if ( State == MF_CHECKED ) {
				   InstallFilter(nHookIndex, FALSE);
				   if (wParam == IDM_JOURNALRECORD )
				  EnableMenuItem(hMenu, IDM_JOURNALPLAYBACK, MF_ENABLED | MF_BYCOMMAND);
				}
				else {
				   CheckMenuItem(hMenu, wParam, MF_CHECKED | MF_BYCOMMAND);
				   //
				   // Install the Hook
				   //
				   InstallFilter(nHookIndex, TRUE);
				}
			break;

			case IDM_ABOUT:
				//
				// Display About Box
				//
				DialogBox(hInstance,		 // current instance
				"AboutBox",			 // resource to use
				hwndMain,			 // parent handle
				(DLGPROC)About);			  // About() instance address

		    break;

			}

	    break;

	case WM_PAINT:
	    hDC = BeginPaint(hwndMain, &ps);
	    TabbedTextOut(hDC, 1,nLineHeight * MSGFILTERINDEX,
		      (LPSTR)szMsgFilterLine, strlen(szMsgFilterLine), 0, NULL, 1);
	    PaintHooksDll( hDC );
	    EndPaint(hwndMain, &ps);
            break;

        case WM_DESTROY:
	    //
	    // Clean up all the Hooks Left
	    //
	    hMenu = GetMenu(hwndMain);
	    for (i = 0; i < NUMOFHOOKS; i++ ) {
		State = CheckMenuItem(hMenu, i+IDM_CALLWNDPROC, MF_UNCHECKED | MF_BYCOMMAND);
		if ( State )
		   if ( i == MSGFILTERINDEX ) {
		       UnhookWindowsHook(WH_MSGFILTER, (HOOKPROC)lpfnMsgFilterProc);
		   }
		   else
		       InstallFilter(i, FALSE);
	    }
            PostQuitMessage(0);
            break;

        default:
            return(DefWindowProc(hwnd, msg, wParam, lParam));
    }

    return(0);
}



//---------------------------------------------------------------------------
// About
//
// Dialog procedure for the sample application's about box
//
//---------------------------------------------------------------------------
BOOL FAR PASCAL About(HWND hDlg, unsigned message, WORD wParam, LONG lParam)
{
    switch (message) {
	case WM_INITDIALOG:		  // message: initialize dialog box
	    return (TRUE);

	case WM_COMMAND:		  // message: received a command
		if ( LOWORD(wParam) == IDOK		  // "OK" box selected?
		||	 LOWORD(wParam) == IDCANCEL) {	// System menu close command?

		EndDialog(hDlg, TRUE);	  // Exits the dialog box
		return (TRUE);
	    }
	    break;
    }
    return (FALSE);			  // Didn't process a message
}



//---------------------------------------------------------------------------
// MsgFilterFunc
//
// Filter function fot the WH_MSGFILTER -- Task Specific so not in DLL
//
//---------------------------------------------------------------------------
int FAR PASCAL MsgFilterFunc (int nCode, WORD wParam, DWORD lParam )
{
   char szType[16];
   MSG FAR *lpMsg;
   HDC	       hDC;

   if ( nCode >= 0 ) {
      if ( nCode == MSGF_DIALOGBOX )
	 strcpy(szType,"Dialog");
      else
	 strcpy(szType,"Menu");

      lpMsg = (MSG FAR *) lParam;
      wsprintf((LPSTR)szMsgFilterLine,
		   "MSGFILTER\t%s\tWnd:%d Time:%d  Point:%d %d %s            ",
	       (LPSTR)szType, lpMsg->hwnd, lpMsg->time,
	       lpMsg->pt.x, lpMsg->pt.y, szMessageString(lpMsg->message));

      hDC = GetDC(hwndMain);
      TabbedTextOut(hDC, 1,nLineHeight * MSGFILTERINDEX,
	       (LPSTR)szMsgFilterLine, strlen(szMsgFilterLine), 0, NULL, 1);
      ReleaseDC(hwndMain, hDC);
   }

//	return( (int)CallNextHookEx(hhookMsgFilterHook, nCode, wParam, lParam ) );
   return( (int)CallNextHookEx(NULL, nCode, wParam, lParam ) );
}


//---------------------------------------------------------------------------
// MessageString
//
// Function to load string from the STRINGTABLE
//
//---------------------------------------------------------------------------
char FAR *szMessageString(int ID)
{
   static char szBuffer[256];

   if ( LoadString(hInstance, ID, szBuffer, 255) == 0)
	  wsprintf(szBuffer,"Message:%hH",ID);

   return (szBuffer);

}
