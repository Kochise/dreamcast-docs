/***************************************************************************
 *									   *
 *  PROGRAM	: MultiPad.c						   *
 *									   *
 *  PURPOSE	: To give a multi-Notepad demonstration of the new MDI	   *
 *		  API in Windows 3.0					   *
 *									   *
 *  FUNCTIONS	: WinMain()	      - Calls the initialization function  *
 *					and processes message loop	   *
 *									   *
 *		  MPFrameWndProc()    - Window function for the "frame"    *
 *					window, which controls the menu    *
 *					and contains the MDI document	   *
 *					windows as child windows.	   *
 *									   *
 *		  MPMDIChildWndProc() - Window function for the individual *
 *					document windows		   *
 *									   *
 *		  InitializeMenu()    - Handles enabling/greying of menu   *
 *					items according to the app's state.*
 *									   *
 *		  CloseAllChildren    - Destroys all MDI child windows.    *
 *									   *
 *		  CommandHandler()    - Processes the "frame" window's     *
 *					WM_COMMAND messages.		   *
 *									   *
 *		  InstallDlgProc()    - Dialog function for the install    *
 *					dialog which appears when the	   *
 *					application is first launched.	   *
 *									   *
 *		  AboutDlgProc()      - Dialog function for the ubiquitous *
 *					About.. dialog. 		   *
 *									   *
 *		  SetWrap()	      - Alters word wrapping in the edit   *
 *					control.			   *
 *									   *
 *		  MPError()	      - Flashes an error messagebox.	   *
 *									   *
 *		  QueryCloseChild     - Prompts for saving current MDI	   *
 *					child window.			   *
 *									   *
 *		  QueryCloseAllChildren() - Asks whether it is OK to close *
 *					    down app.			   *
 *									   *
 ***************************************************************************/

#include "multipad.h"
#include <string.h>
#define _MBCS
#include <mbstring.h>
#include <stdio.h>
#include "regdb.h"

/* global variables used in this module or among more than one module */
HANDLE hInst;			    /* Program instance handle		     */
HANDLE hAccel;			    /* Main accelerator resource	     */
HWND hwndFrame		 = NULL;    /* Handle to main window		     */
HWND hwndMDIClient	 = NULL;    /* Handle to MDI client		     */
HWND hwndActive 	 = NULL;    /* Handle to currently activated child   */
HWND hwndActiveEdit	 = NULL;    /* Handle to edit control		     */
LONG styleDefault        = 0;       /* Default style bits for child windows  */
				    /* The first window is created maximized */
				    /* to resemble Notepad.  Later children  */
				    /* are normal windows.		     */
LPSTR lpMenu	     = IDMULTIPAD;  /* Contains the resource id of the	     */
				    /* current frame menu		     */


/* Forward declarations of helper functions in this module */
VOID NEAR PASCAL InitializeMenu (HANDLE);
VOID NEAR PASCAL CommandHandler (HWND, UINT, LONG);
BOOL NEAR PASCAL SetWrap (HWND,BOOL);
BOOL NEAR PASCAL QueryCloseAllChildren ( VOID );
INT  NEAR PASCAL QueryCloseChild (HWND);
LPSTR GetCmdLine( VOID );

/****************************************************************************
 *									    *
 *  FUNCTION   : WinMain(HANDLE, HANDLE, LPSTR, int)			    *
 *									    *
 *  PURPOSE    : Creates the "frame" window, does some initialization and   *
 *		 enters the message loop.				    *
 *									    *
 ****************************************************************************/
int PASCAL WinMain(hInstance, hPrevInstance, lpCmdLine, nCmdShow)
HINSTANCE hInstance;			     /* current instance	     */
HINSTANCE hPrevInstance;			     /* previous instance	     */
LPSTR lpCmdLine;			     /* command line		     */
int nCmdShow;				     /* show-window type (open/icon) */
{
    MSG msg;

    //
    // Detect platform and exit gracefully if not Windows NT.
    //

    {
      OSVERSIONINFO osvi;
	  CHAR szBuffer1[128];
	  CHAR szBuffer2[128];
      osvi.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
      
	  LoadString(hInst, IDS_WRONGOSMSG1, szBuffer1, sizeof (szBuffer1));
	  LoadString(hInst, IDS_WRONGOSMSG2, szBuffer2, sizeof (szBuffer2));

      GetVersionEx (&osvi);
      if (osvi.dwPlatformId != VER_PLATFORM_WIN32_NT) {
        MessageBox (NULL, szBuffer1, szBuffer2, MB_OK | MB_ICONSTOP);
        return 0;
      }
    }


    hInst = hInstance;

    /* If this is the first instance of the app. register window classes */
    if (!hPrevInstance){
	if (!InitializeApplication ())
	    return 0;
    }

    lpCmdLine = GetCmdLine();

    /* Create the frame and do other initialization */
    if (!InitializeInstance (lpCmdLine, nCmdShow))
	return 0;

    /* Enter main message loop */
    while (GetMessage (&msg, NULL, 0, 0)){
	/* If a keyboard message is for the MDI , let the MDI client
	 * take care of it.  Otherwise, check to see if it's a normal
	 * accelerator key (like F3 = find next).  Otherwise, just handle
	 * the message as usual.
	 */
	if ( !TranslateMDISysAccel (hwndMDIClient, &msg) &&
	     !TranslateAccelerator (hwndFrame, hAccel, &msg)){
	    TranslateMessage (&msg);
	    DispatchMessage (&msg);
	}
    }
    return 0;
}

/****************************************************************************
 *									    *
 *  FUNCTION   : MPFrameWndProc (hwnd, msg, wParam, lParam )		    *
 *									    *
 *  PURPOSE    : The window function for the "frame" window, which controls *
 *		 the menu and encompasses all the MDI child windows. Does   *
 *		 the major part of the message processing. Specifically, in *
 *		 response to:						    *
 *									    *
 *		     WM_CREATE		: Creates and displays the "frame". *
 *									    *
 *		     WM_INITMENU	: Sets up the state of the menu.    *
 *									    *
 *		     WM_WININICHANGE &	: If default printer characteristics*
 *		     WM_DEVMODECHANGE	  have been changed, reinitialises  *
 *					  printer DC.			    *
 *									    *
 *		     WM_COMMAND 	: Passes control to a command-	    *
 *					  handling function.		    *
 *									    *
 *		     WM_CLOSE		: Quits the app. if all the child   *
 *					  windows agree.		    *
 *									    *
 *		     WM_QUERYENDSESSION : Checks that all child windows     *
 *					  agree to quit.		    *
 *									    *
 *		     WM_DESTROY 	: Destroys frame window and quits   *
 *					  app.				    *
 *									    *
 ****************************************************************************/
LONG APIENTRY MPFrameWndProc (
	register HWND	 hwnd,
	UINT		 msg,
	UINT		 wParam,
	LONG		 lParam)

{
    switch (msg){
	case WM_CREATE:{

	    CLIENTCREATESTRUCT ccs;
	    HDC hdc;

	    /* Find window menu where children will be listed */
	    ccs.hWindowMenu = GetSubMenu (GetMenu(hwnd),WINDOWMENU);
	    ccs.idFirstChild = IDM_WINDOWCHILD;

	    /* Create the MDI client filling the client area */
	    hwndMDIClient = CreateWindow ("mdiclient",
					  NULL,
					  WS_CHILD | WS_CLIPCHILDREN |
					  WS_VSCROLL | WS_HSCROLL,
					  0,
					  0,
					  0,
					  0,
					  hwnd,
					  (HMENU)0xCAC,
					  hInst,
					  (LPSTR)&ccs);


	    ShowWindow (hwndMDIClient,SW_SHOW);

	    /* Check if printer can be initialized */
	    if (hdc = GetPrinterDC (TRUE)){
		DeleteDC (hdc);
	    }

	    break;
	}

	case WM_INITMENU:
	    /* Set up the menu state */
	    InitializeMenu ((HMENU)wParam);
	    break;

	case WM_WININICHANGE:
	case WM_DEVMODECHANGE:{

	    /*	If control panel changes default printer characteristics,
	     *	reinitialize our printer information...
	     */
	    HDC hdc;

	    if (hdc = GetPrinterDC (TRUE)){
		DeleteDC (hdc);
	    }
	    break;
	}


	case WM_COMMAND:
	    /* Direct all menu selection or accelerator commands to another
	     * function
	     */
	    CommandHandler(hwnd, wParam, lParam);
	    break;

	case WM_CLOSE:
	    /* don't close if any children cancel the operation */
	    if (!QueryCloseAllChildren ()) break;

            SaveConfiguration();

	    DestroyWindow (hwnd);
	    break;

	case WM_QUERYENDSESSION:
	    /*	Before session ends, check that all files are saved */
	    return QueryCloseAllChildren ();

	case WM_DESTROY:
	    PostQuitMessage (0);
	    break;

	default:
	    /*	use DefFrameProc() instead of DefWindowProc() since there
	     *	are things that have to be handled differently because of MDI
	     */
	    return DefFrameProc (hwnd,hwndMDIClient,msg,wParam,lParam);
    }
    return 0;
}

/****************************************************************************
 *									    *
 *  FUNCTION   : MPMDIWndProc ( hwnd, msg, wParam, lParam )		    *
 *									    *
 *  PURPOSE    : The window function for the individual document windows,   *
 *		 each of which has a "note". Each of these windows contain  *
 *		 one multi-line edit control filling their client area.     *
 *		 In response to the following:				    *
 *									    *
 *		     WM_CREATE		: Creates & diplays an edit control *
 *					  and does some initialization.     *
 *									    *
 *		     WM_MDIACTIVATE	: Activates/deactivates the child.  *
 *									    *
 *		     WM_SETFOCUS	: Sets focus on the edit control.   *
 *									    *
 *		     WM_SIZE		: Resizes the edit control.	    *
 *									    *
 *		     WM_COMMAND 	: Processes some of the edit	    *
 *					  commands, saves files and alters  *
 *					  the edit wrap state.		    *
 *									    *
 *		     WM_CLOSE		: Closes child if it is ok to do so.*
 *									    *
 *		     WM_QUERYENDSESSION : Same as above.		    *
 *									    *
 ****************************************************************************/

LONG APIENTRY MPMDIChildWndProc (
	register HWND	hwnd,
	UINT		msg,
	register UINT wParam,
	LONG		lParam)

{
    HWND hwndEdit;

    switch (msg){
	case WM_CREATE:
        {
            DWORD dws= WS_CHILD | WS_MAXIMIZE | WS_VISIBLE
                                | WS_VSCROLL  | ES_AUTOVSCROLL
                                | ES_MULTILINE;

            if (!fTextWrapDefault) dws |= WS_HSCROLL | ES_AUTOHSCROLL;

	    /* Create an edit control */
	    hwndEdit = CreateWindow ("edit",
				     NULL,
				     dws,
				     0,
				     0,
				     0,
				     0,
				     hwnd,
				     (HMENU)ID_EDIT,
				     hInst,
				     NULL);

	    /* Remember the window handle and initialize some window attributes */
	    SetWindowLong (hwnd, GWL_HWNDEDIT, (LONG) hwndEdit);
	    SetWindowWord (hwnd, GWW_CHANGED, FALSE);
	    SetWindowWord (hwnd, GWL_WORDWRAP, (WORD) fTextWrapDefault);
	    SetWindowWord (hwnd, GWW_UNTITLED, TRUE);
	    SetFocus (hwndEdit);
	    break;
        }

	case WM_MDIACTIVATE:
	    /* If we're activating this child, remember it */
	    if (GET_WM_MDIACTIVATE_FACTIVATE(hwnd, wParam, lParam)){
		hwndActive     = hwnd;
		hwndActiveEdit = (HWND)GetWindowLong (hwnd, GWL_HWNDEDIT);
	    }
	    else{
		hwndActive     = NULL;
		hwndActiveEdit = NULL;
	    }
	    break;

	case WM_QUERYENDSESSION:
	    /* Prompt to save the child */
	    return !QueryCloseChild (hwnd);

	case WM_CLOSE:
	    /* If its OK to close the child, do so, else ignore */
	    if (QueryCloseChild (hwnd))
		goto CallDCP;
	    else
		break;

	case WM_SIZE:{
	    RECT rc;

	    /* On creation or resize, size the edit control. */
	    hwndEdit = (HWND)GetWindowLong (hwnd, GWL_HWNDEDIT);
	    GetClientRect (hwnd, &rc);
	    MoveWindow (hwndEdit,
			rc.left,
			rc.top,
			rc.right-rc.left,
			rc.bottom-rc.top,
			TRUE);
	    goto CallDCP;
	}

	case WM_SETFOCUS:
	    SetFocus ((HWND)GetWindowLong (hwnd, GWL_HWNDEDIT));
	    break;

	case WM_COMMAND:
	    switch (LOWORD(wParam)){
		case ID_EDIT:
		    switch (GET_WM_COMMAND_CMD(wParam, lParam)){
			case EN_CHANGE:

			    /* If the contents of the edit control have changed,
			       set the changed flag
			     */
			    SetWindowWord (hwnd, GWW_CHANGED, TRUE);
			    break;

			case EN_ERRSPACE:
			    /* If the control is out of space, honk */
			    MessageBeep (0);
			    break;

			default:
			    goto CallDCP;
		    }
		    break;

		case IDM_FILESAVE:
		    /* If empty file, ignore save */
		    if ((GetWindowWord(hwnd, GWW_UNTITLED)) && (!ChangeFile(hwnd)))
			break;

		    /* Save the contents of the edit control and reset the
		     * changed flag
		     */
		    SaveFile (hwnd);
		    SetWindowWord (hwnd, GWW_CHANGED, FALSE);
		    break;

		case IDM_EDITWRAP: {
		    INT fWrap = GetWindowWord (hwnd, GWL_WORDWRAP);

		    /* Set the wrap state, or report it */
		    if (GET_WM_COMMAND_HWND(wParam, lParam)){
			    fWrap = !fWrap;
			    if(!SetWrap (hwnd, fWrap)){
    			    fWrap = !fWrap;  /* call failed, restore original fWrap */
                }
		    }

		    /* return wrap state */
		    return fWrap;
		}

		default:
		    goto CallDCP;
	    }
	    break;

	default:
CallDCP:
	    /* Again, since the MDI default behaviour is a little different,
	     * call DefMDIChildProc instead of DefWindowProc()
	     */
	    return DefMDIChildProc (hwnd, msg, wParam, lParam);
    }
    return FALSE;
}


/****************************************************************************
 *									    *
 *  FUNCTION   : AboutDlgProc ( hwnd, msg, wParam, lParam )		    *
 *									    *
 *  PURPOSE    : Dialog function for the About MultiPad... dialog.	    *
 *									    *
 ****************************************************************************/
BOOL APIENTRY AboutDlgProc (
	HWND	      hwnd,
	register UINT msg,
	register UINT wParam,
	LONG	      lParam)
{
    switch (msg){
	case WM_INITDIALOG:
        {
           PSZ pszInstallName= NULL, pszInstallOrg= NULL;

           LONG cbName= 0, cbOrg= 0, lResult;

           DWORD dwType;

           lResult= RegQueryValueEx(hkGlobal, KEY_VALUE_INSTALL_NAME, NULL,
                                    &dwType, NULL, &cbName
                                   );

           if (   lResult == ERROR_SUCCESS && dwType == REG_SZ)
           if     (pszInstallName= _alloca(cbName))
           if     (ERROR_SUCCESS != RegQueryValueEx
                                     (hkGlobal, KEY_VALUE_INSTALL_NAME, NULL,
                                      &dwType, (LPBYTE) pszInstallName, &cbName
                                     )
              ) pszInstallName= NULL;

	   lResult= RegQueryValueEx(hkGlobal, KEY_VALUE_INSTALL_ORG, NULL,
                                    &dwType, NULL, &cbOrg
                                   );

           if (   lResult == ERROR_SUCCESS && dwType == REG_SZ)
           if     (pszInstallOrg= _alloca(cbOrg))
           if     (ERROR_SUCCESS != RegQueryValueEx
                                     (hkGlobal, KEY_VALUE_INSTALL_ORG, NULL,
                                      &dwType, (LPBYTE) pszInstallOrg, &cbOrg
                                     )
              ) pszInstallOrg= NULL;

	    // Need to setup the "Installed by..." strings in the dialog.

            if (pszInstallName)
	       SendDlgItemMessage(hwnd, EB_NAME, WM_SETTEXT, 0,
                                  (LPARAM) pszInstallName
			         );

            if (pszInstallOrg)
	       SendDlgItemMessage(hwnd, EB_ORGANIZATION, WM_SETTEXT, 0,
				  (LPARAM) pszInstallOrg
			         );

	    break;
        }

	case WM_COMMAND:
	    switch (LOWORD(wParam)){
		case IDOK:
		case IDCANCEL:
		    EndDialog(hwnd, 0);
		    break;

		default:
		    return FALSE;
	    }
	    break;

	default:
	    return FALSE;
    }

    return TRUE;
	UNREFERENCED_PARAMETER(lParam);
}

/****************************************************************************
 *									    *
 *  FUNCTION   : InstallDlgProc ( hwnd, msg, wParam, lParam )		    *
 *									    *
 *  PURPOSE    : Dialog function for Installing RegMpad in the registry     *
 *									    *
 ****************************************************************************/
BOOL APIENTRY InstallDlgProc (
	HWND	      hwnd,
	register UINT msg,
	register UINT wParam,
	LONG	      lParam)
{

    switch (msg){
	case WM_INITDIALOG:

            SetWindowLong(hwnd, DWL_USER, lParam);

	    break;

	case WM_COMMAND:

	    switch (LOWORD(wParam)){
		case PB_INSTALL:

		{
		    PSZ pszNewName, pszNewOrg;
		    int     cbName,	cbOrg;
		    HWND  hwndName,   hwndOrg;
                    char  *pc, c;

                    BOOL fNameGiven, fOrgGiven;

		    hwndName = GetDlgItem(hwnd, EB_NAME);
		    hwndOrg  = GetDlgItem(hwnd, EB_ORGANIZATION);

		    if (   !(cbName = GetWindowTextLength(hwndName))
			|| !(cbOrg  = GetWindowTextLength(hwndOrg ))
		       )
		    {
                       MPError(hwnd, MB_OK | MB_ICONHAND,
                               IDS_NEED_NAME_ORG,
		               NULL
			      );

		       break;
		    }

		    pszNewName = _alloca(cbName + 1);
		    pszNewOrg  = _alloca(cbOrg  + 1);

		    GetWindowText(hwndName, pszNewName, cbName+1);
		    GetWindowText(hwndOrg , pszNewOrg , cbOrg +1);

                    for (fNameGiven= FALSE, pc= pszNewName; c= *pc++; )
                       if (c != ' ')
                       {
                          fNameGiven= TRUE; break;
                       }

                    for (fOrgGiven= FALSE, pc= pszNewOrg; c= *pc++; )
                       if (c != ' ')
                       {
                          fOrgGiven= TRUE; break;
                       }

                    if (!fOrgGiven || !fNameGiven)
		    {
		       MPError(hwnd, MB_OK | MB_ICONHAND,
                               IDS_NEED_NAME_ORG,
		               NULL
			      );

		       break;
		    }

		    if (StoreAppConfig(hwnd,
                                       (PSZ) GetWindowLong(hwnd, DWL_USER),
                                       pszNewName, pszNewOrg,
                                       1 == IsDlgButtonChecked
                                              (hwnd, CB_DEFAULT_WRAP)
                                      )
                       ) EndDialog(hwnd, 1);

		    break;
		}


		case IDCANCEL:
		    EndDialog(hwnd, 0);
		    break;

		default:
		    return FALSE;
	    }
	    break;

	default:
	    return FALSE;
    }

    return TRUE;
}

/****************************************************************************
 *									    *
 *  FUNCTION   : OptionsDlgProc ( hwnd, msg, wParam, lParam )		    *
 *									    *
 *  PURPOSE    : Dialog function for Setting per-user options               *
 *									    *
 ****************************************************************************/
BOOL APIENTRY OptionsDlgProc (
	HWND	      hwnd,
	register UINT msg,
	register UINT wParam,
	LONG	      lParam)
{

    switch (msg){
	case WM_INITDIALOG:

            CheckDlgButton(hwnd, CB_DEFAULT_WRAP, fTextWrapDefault? 1 : 0);

            break;

	case WM_COMMAND:

	    switch (LOWORD(wParam)){
		case IDOK:

                    fTextWrapDefault= 1 == IsDlgButtonChecked
                                             (hwnd, CB_DEFAULT_WRAP);

                    RegSetValueEx(hkPerUser, WORD_WRAP_DEFAULT, 0,
                                  REG_DWORD, (LPBYTE) &fTextWrapDefault,
                                  sizeof(fTextWrapDefault)
                                 );

                    EndDialog(hwnd, 1);

                    break;

		case IDCANCEL:
		    EndDialog(hwnd, 0);
		    break;

		default:
		    return FALSE;
	    }
	    break;

	default:
	    return FALSE;
    }

    return TRUE;
	UNREFERENCED_PARAMETER(lParam);
}

/****************************************************************************
 *									    *
 *  FUNCTION   : Initializemenu ( hMenu )				    *
 *									    *
 *  PURPOSE    : Sets up greying, enabling and checking of main menu items  *
 *		 based on the app's state.                                  *
 *									    *
 ****************************************************************************/
VOID NEAR PASCAL InitializeMenu (register HANDLE hmenu)
{
    register WORD status;
    WORD	  i;
    INT 	  j;
    LONG	  l;

    /* Is there any active child to talk to? */
    if (hwndActiveEdit){
	/* If edit control can respond to an undo request, enable the
	 * undo selection.
	 */
	if (SendMessage (hwndActiveEdit, EM_CANUNDO, 0, 0L))

	    status = MF_ENABLED;
	else
	    status = MF_GRAYED;
	EnableMenuItem (hmenu, IDM_EDITUNDO, status);

	/* If edit control is non-empty, allow cut/copy/clear */
        l = (LONG)SendMessage(hwndActiveEdit, EM_GETSEL, 0, 0);


	status = (WORD) ((HIWORD(l) == LOWORD(l)) ? MF_GRAYED : MF_ENABLED);
	EnableMenuItem (hmenu, IDM_EDITCUT, status);
	EnableMenuItem (hmenu, IDM_EDITCOPY, status);
	EnableMenuItem (hmenu, IDM_EDITCLEAR, status);

	status=MF_GRAYED;
	/* If the clipboard contains some CF_TEXT data, allow paste */
	if (OpenClipboard (hwndFrame)){
	    UINT wFmt = 0;

	    while (wFmt = EnumClipboardFormats (wFmt))
		if (wFmt == CF_TEXT){
		    status = MF_ENABLED;
		    break;
		}

	    CloseClipboard ();
	}
	EnableMenuItem (hmenu, IDM_EDITPASTE, status);

	/* Set the word wrap state for the window */
	if ((WORD) SendMessage(hwndActive, WM_COMMAND, GET_WM_COMMAND_MPS(IDM_EDITWRAP, 0, 0)))
	    status = MF_CHECKED;
	else
	    status = MF_UNCHECKED;
	CheckMenuItem (hmenu, IDM_EDITWRAP, status);

	/* Enable search menu items only if there is a search string */
	if (*szSearch)
	    status = MF_ENABLED;
	else
	    status = MF_GRAYED;
	EnableMenuItem (hmenu, IDM_SEARCHNEXT, status);
	EnableMenuItem (hmenu, IDM_SEARCHPREV, status);

	/* Enable File/Print only if a printer is available */
	status = (WORD) (iPrinter ? MF_ENABLED : MF_GRAYED);
	EnableMenuItem (hmenu, IDM_FILEPRINT, status);
	EnableMenuItem ( hmenu, IDM_FILESETUP, status);

	/* select all and wrap toggle always enabled */
	status = MF_ENABLED;
	EnableMenuItem(hmenu, IDM_EDITSELECT, status);
	EnableMenuItem(hmenu, IDM_EDITWRAP, status);
	EnableMenuItem(hmenu, IDM_SEARCHFIND, status);
    }
    else {
	/* There are no active child windows */
	status = MF_GRAYED;

	/* No active window, so disable everything */
	for (i = IDM_EDITFIRST; i <= IDM_EDITLAST; i++)
	    EnableMenuItem (hmenu, i, status);

	CheckMenuItem (hmenu, IDM_EDITWRAP, MF_UNCHECKED);

	for (i = IDM_SEARCHFIRST; i <= IDM_SEARCHLAST; i++)
	    EnableMenuItem (hmenu, i, status);

	EnableMenuItem (hmenu, IDM_FILEPRINT, status);
    }

    /* The following menu items are enabled if there is an active window */
    EnableMenuItem (hmenu, IDM_FILESAVE, status);
    EnableMenuItem (hmenu, IDM_FILESAVEAS, status);
    EnableMenuItem (hmenu, IDM_WINDOWTILE, status);
    EnableMenuItem (hmenu, IDM_WINDOWCASCADE, status);
    EnableMenuItem (hmenu, IDM_WINDOWICONS, status);
    EnableMenuItem (hmenu, IDM_WINDOWCLOSEALL, status);

	UNREFERENCED_PARAMETER(j);

}

/****************************************************************************
 *									    *
 *  FUNCTION   : CloseAllChildren ()					    *
 *									    *
 *  PURPOSE    : Destroys all MDI child windows.			    *
 *									    *
 ****************************************************************************/
VOID NEAR PASCAL CloseAllChildren ()
{
    register HWND hwndT;

    /* hide the MDI client window to avoid multiple repaints */
    ShowWindow(hwndMDIClient,SW_HIDE);

    /* As long as the MDI client has a child, destroy it */
    while ( hwndT = GetWindow (hwndMDIClient, GW_CHILD)){

	/* Skip the icon title windows */
	while (hwndT && GetWindow (hwndT, GW_OWNER))
	    hwndT = GetWindow (hwndT, GW_HWNDNEXT);

	if (!hwndT)
	    break;

	SendMessage (hwndMDIClient, WM_MDIDESTROY, (UINT)hwndT, 0L);
    }
}

/****************************************************************************
 *									    *
 *  FUNCTION   : CommandHandler ()					    *
 *									    *
 *  PURPOSE    : Processes all "frame" WM_COMMAND messages.                 *
 *									    *
 ****************************************************************************/
VOID NEAR PASCAL CommandHandler (
	register HWND hwnd,
	register UINT wParam,
	LONG lParam)

{
    switch (LOWORD(wParam)){
	case IDM_FILENEW:
	    /* Add a new, empty MDI child */
	    AddFile (NULL);
	    break;

	case IDM_FILEOPEN:
	    MyReadFile (hwnd);
	    break;

	case IDM_FILESAVE:

            // If the window hasn't been given a name yet, we treat
            // The File/Save command as File/Save As...

            if (!GetWindowWord(hwndActive, GWW_UNTITLED))
            {
	       /* Save the active child MDI */
	       SendMessage(hwndActive, WM_COMMAND,
                           GET_WM_COMMAND_MPS(IDM_FILESAVE, 0, 0)
                          );
	       break;
            }

	case IDM_FILESAVEAS:
	    /* Save active child MDI under another name */
	    if (ChangeFile (hwndActive))
		SendMessage(hwndActive, WM_COMMAND, GET_WM_COMMAND_MPS(IDM_FILESAVE, 0, 0));
	    break;

	case IDM_FILEPRINT:
	    /* Print the active child MDI */
	    PrintFile (hwndActive);
	    break;

	case IDM_FILESETUP:
	    /* Set up the printer environment for this app */
	    GetInitializationData (hwnd);
	    break;

	case IDM_FILEMENU:{

	      /* lengthen / shorten the size of the MDI menu */
	      HMENU hMenu;
	      HMENU hWindowMenu;
	      INT i;

	      if (lpMenu == IDMULTIPAD){
		  lpMenu = IDMULTIPAD2;
		  i	 = SHORTMENU;
	      }
	      else{
		  lpMenu = IDMULTIPAD;
		  i	 = WINDOWMENU;
	      }

	      hMenu = LoadMenu (hInst, lpMenu);
	      hWindowMenu = GetSubMenu (hMenu, i);

	      /* Set the new menu */
	      hMenu = (HMENU)SendMessage (hwndMDIClient,
					  WM_MDISETMENU,
					  (UINT)hMenu,
					  (LONG)hWindowMenu);

	      DestroyMenu (hMenu);
	      DrawMenuBar (hwndFrame);
	      break;
	}

	case IDM_FILEEXIT:
	    /* Close Multipad */
	    SendMessage (hwnd, WM_CLOSE, 0, 0L);
	    break;

	case IDM_HELPABOUT:{

	    DialogBox(hInst, (LPSTR)IDD_ABOUT, hwnd, AboutDlgProc);
	    break;
	}

	/* The following are edit commands. Pass these off to the active
	 * child's edit control window.
	 */
	case IDM_EDITCOPY:
	    SendMessage (hwndActiveEdit, WM_COPY, 0, 0L);
	    break;

	case IDM_EDITPASTE:
	    SendMessage (hwndActiveEdit, WM_PASTE, 0, 0L);
	    break;

	case IDM_EDITCUT:
	    SendMessage (hwndActiveEdit, WM_CUT, 0, 0L);
	    break;

	case IDM_EDITCLEAR:
	    SendMessage (hwndActiveEdit, EM_REPLACESEL, 0,( LONG)(LPSTR)"");
	    break;

	case IDM_EDITSELECT:
	    SendMessage(hwndActiveEdit, EM_SETSEL, GET_EM_SETSEL_MPS(0, 0xe000));
	    break;

	case IDM_EDITUNDO:
	    SendMessage (hwndActiveEdit, EM_UNDO, 0, 0L);
	    break;

	case IDM_EDITWRAP:
	    SendMessage(hwndActive, WM_COMMAND, GET_WM_COMMAND_MPS(IDM_EDITWRAP, 1, 0));
	    break;

        case IDM_OPTIONS:
	    DialogBox(hInst, (LPSTR)DLG_PER_USER_CONFIG, hwnd, OptionsDlgProc);
            break;

	case IDM_SEARCHFIND:
	    /* Put up the find dialog box */
	    Find ();
	    break;

	case IDM_SEARCHNEXT:
	    /* Find next occurence */
	    FindNext ();
	    break;

	case IDM_SEARCHPREV:
	    /* Find previous occurence */
	    FindPrev ();
	    break;

	/* The following are window commands - these are handled by the
	 * MDI Client.
	 */
	case IDM_WINDOWTILE:
	    /* Tile MDI windows */
	    SendMessage (hwndMDIClient, WM_MDITILE, 0, 0L);
	    break;

	case IDM_WINDOWCASCADE:
	    /* Cascade MDI windows */
	    SendMessage (hwndMDIClient, WM_MDICASCADE, 0, 0L);
	    break;

	case IDM_WINDOWICONS:
	    /* Auto - arrange MDI icons */
	    SendMessage (hwndMDIClient, WM_MDIICONARRANGE, 0, 0L);
	    break;

	case IDM_WINDOWCLOSEALL:
	    /* Abort operation if something is not saved */
	    if (!QueryCloseAllChildren())
		break;

	    CloseAllChildren();

	    /* Show the window since CloseAllChilren() hides the window
	     * for fewer repaints.
	     */
	    ShowWindow( hwndMDIClient, SW_SHOW);

	    break;

	default:
	   /*
	    * This is essential, since there are frame WM_COMMANDS generated
	    * by the MDI system for activating child windows via the
	    * window menu.
	    */
	    DefFrameProc(hwnd, hwndMDIClient, WM_COMMAND, wParam, lParam);
    }
}
/****************************************************************************
 *									    *
 *  FUNCTION   : SetWrap ()						    *
 *									    *
 *  PURPOSE    : Changes the word wrapping in an edit control. Since this   *
 *		 cannot be done by direct means, the function creates a new *
 *		 edit control, moves data from the old control to the new   *
 *		 control and destroys the original control. Note that the   *
 *		 function assumes that the child being modified is currently*
 *		 active.						    *	    *
 *									    *
 ****************************************************************************/

BOOL NEAR PASCAL SetWrap(
	HWND hwnd,
	BOOL fWrap)

{
    LONG    dws;
    HANDLE  hT;
    HANDLE  hTT;
    HWND    hwndOld;
    HWND    hwndNew;
    RECT    rc;
	CHAR    szBuffer[128];
	
	/* Change word wrap mode */
    SetWindowLong (hwnd, GWL_WORDWRAP, fWrap);

    /* Create the appropriate window style, adding a horizontal scroll
     * facility if wrapping is not present.
     */
    dws = WS_CHILD | WS_VSCROLL | ES_AUTOVSCROLL | ES_MULTILINE;
    if (!fWrap)
	dws |= WS_HSCROLL | ES_AUTOHSCROLL;

    /* Create a new child window */
    hwndNew = CreateWindow ( "edit",
			     NULL,
			     dws,
			     0,
			     SW_SHOW,
			     0,
			     0,
			     hwnd,
			     (HMENU)ID_EDIT,
			     hInst,
			     NULL);

    /* Get handle to current edit control */
    hwndOld = (HWND)GetWindowLong (hwnd, GWL_HWNDEDIT);

    /* Get the data handle of the old control */
    hT = (HANDLE)SendMessage (hwndOld, EM_GETHANDLE, 0, 0L);

    /* Create a dummy data handle and make it the handle to
     * the old edit control( hT still references the text of
     * old control).
     */
    hTT = LocalAlloc (LHND, 0);
    if(!hTT){        
		LoadString(hInst, IDS_FAILWRAP, szBuffer, sizeof (szBuffer));
		MessageBox(hwnd, szBuffer, NULL, MB_OK | MB_ICONHAND);
        return(FALSE);
    }

    SendMessage (hwndOld, EM_SETHANDLE, (UINT)hTT, 0L);

    /* Make the new window the window of interest and destroy the
     * old control.
     */
    SetWindowLong (hwnd, GWL_HWNDEDIT, (LONG)hwndNew);
    hwndActiveEdit = hwndNew;
    DestroyWindow (hwndOld);

    /* Cause the window to be properly sized */
    SendMessage (hwnd, WM_SIZE, 0, 0L);

    /* Free the new window's old data handle and set it to
     * hT (text of old edit control)
     */
    LocalFree ((HANDLE)SendMessage (hwndNew, EM_GETHANDLE, 0, 0L));
    SendMessage (hwndNew, EM_SETHANDLE, (UINT)hT, 0L);

    ShowWindow (hwndNew, SW_SHOW);

    /* Set focus to the new edit control */
    SetFocus (hwndNew);

	UNREFERENCED_PARAMETER(rc);
}


/****************************************************************************
 *									    *
 *  FUNCTION   : MPError ( hwnd, flags, id, ...)			    *
 *									    *
 *  PURPOSE    : Flashes a Message Box to the user. The format string is    *
 *		 taken from the STRINGTABLE.				    *
 *									    *
 *  RETURNS    : Returns value returned by MessageBox() to the caller.	    *
 *									    *
 ****************************************************************************/
SHORT MPError(
	HWND hwnd,
	WORD bFlags,
	WORD id,
	char *psz )
	{
    CHAR sz[160];
    CHAR szFmt[128];

    LoadString (hInst, id, szFmt, sizeof (szFmt));
    sprintf (sz, szFmt, psz );
    LoadString (hInst, (WORD)IDS_APPNAME, (LPSTR)szFmt, sizeof (szFmt));
    return( (SHORT)MessageBox (hwnd, sz, szFmt, bFlags));
	UNREFERENCED_PARAMETER(hwnd);
}


/****************************************************************************
 *									    *
 *  FUNCTION   : QueryCloseAllChildren()				    *
 *									    *
 *  PURPOSE    : Asks the child windows if it is ok to close up app. Nothing*
 *		 is destroyed at this point. The z-order is not changed.    *
 *									    *
 *  RETURNS    : TRUE - If all children agree to the query.		    *
 *		 FALSE- If any one of them disagrees.			    *
 *									    *
 ****************************************************************************/

BOOL NEAR PASCAL QueryCloseAllChildren()
{
    register HWND hwndT;

    for ( hwndT = GetWindow (hwndMDIClient, GW_CHILD);
	  hwndT;
	  hwndT = GetWindow (hwndT, GW_HWNDNEXT)       ){

	/* Skip if an icon title window */
	if (GetWindow (hwndT, GW_OWNER))
	    continue;

	if (SendMessage (hwndT, WM_QUERYENDSESSION, 0, 0L))
	    return FALSE;
    }
    return TRUE;
}

/****************************************************************************
 *									    *
 *  FUNCTION   : QueryCloseChild (hwnd) 				    *
 *									    *
 *  PURPOSE    : If the child MDI is unsaved, allow the user to save, not   *
 *		 save, or cancel the close operation.			    *
 *									    *
 *  RETURNS    : TRUE  - if user chooses save or not save, or if the file   *
 *			 has not changed.				    *
 *		 FALSE - otherwise.					    *
 *									    *
 ****************************************************************************/

BOOL NEAR PASCAL QueryCloseChild(register HWND hwnd)
{
    CHAR	 sz [MAX_PATH];
    register INT i;

    /* Return OK if edit control has not changed. */
    if (!GetWindowWord (hwnd, GWW_CHANGED))
	return TRUE;

    GetWindowText (hwnd, sz, sizeof(sz));

    /* Ask user whether to save / not save / cancel */
    i = MPError (hwnd,
		 MB_YESNOCANCEL|MB_ICONQUESTION,IDS_CLOSESAVE,
		 (LPSTR)sz);

    switch (i){
	case IDYES:
	    /* User wants file saved */
            if (   !GetWindowWord(hwnd, GWW_UNTITLED)
                || ChangeFile(hwnd)
               ) SaveFile(hwnd);

	    break;

	case IDNO:
	    /* User doesn't want file saved */
	    break;

	default:
	    /* We couldn't do the messagebox, or not ok to close */
	    return FALSE;
    }
    return TRUE;
}


LPSTR GetCmdLine( VOID )
{
    LPSTR lpCmdLine, lpT;

    lpCmdLine = GetCommandLine();

    // on Win32, lpCmdLine's first string includes its own name, remove this
    // to make it exactly like the windows command line.

    if (*lpCmdLine) {
        lpT = _mbschr(lpCmdLine, ' ');   // skip self name
        if (lpT) {
            lpCmdLine = lpT;
            while (*lpCmdLine == ' ') {
                lpCmdLine++;            // skip spaces to end or first cmd
            }
        } else {
            lpCmdLine += strlen(lpCmdLine);   // point to NULL
        }
    }
    return(lpCmdLine);
}

