/* QuickCase:W KNB Version 1.00 */
#include "STYLES.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
 /***********************************************************************/
 /* HANDLE hInstance;       handle for this instance                    */
 /* HANDLE hPrevInstance;   handle for possible previous instances      */
 /* LPSTR  lpszCmdLine;     long pointer to exec command line           */
 /* int    nCmdShow;        Show code for main window display           */
 /***********************************************************************/

 MSG        msg;           /* MSG structure to store your messages        */
 int        nRc;           /* return value from Register Classes          */

 /* Seed the random number generator with current time. */
 srand( (unsigned)time( NULL ) );

 lstrcpy(szAppName, "STYLES");
 hInst = hInstance;
 if(!hPrevInstance)
   {
    /* register window classes if first instance of application         */
    if ((nRc = nCwRegisterClasses()) == -1)
      {
       /* registering one of the windows failed                         */
       lstrcpy(szString, "Error registering window class");
       MessageBox(NULL, szString, NULL, MB_ICONEXCLAMATION);
       return nRc;
      }
   }

 //
 // Name
 //
 LoadString(hInst, getrandom(0, LASTNAME), szString, sizeof(szString));
 /* create application's Main window                                    */
 hWndMain = CreateWindow(
                szAppName,               /* Window class name           */
                szString,                /* Window's title              */
                WS_CAPTION      |        /* Title and Min/Max           */
                WS_SYSMENU      |        /* Add system menu box         */
                WS_MINIMIZEBOX  |        /* Add minimize box            */
                WS_MAXIMIZEBOX  |        /* Add maximize box            */
                WS_THICKFRAME   |        /* thick sizeable frame        */
		WS_CLIPCHILDREN |	 /* don't draw in child windows areas */
                WS_OVERLAPPED,
                CW_USEDEFAULT, 0,        /* Use default X, Y            */
                CW_USEDEFAULT, 0,        /* Use default X, Y            */
                NULL,                    /* Parent window's handle      */
                NULL,                    /* Default to Class Menu       */
                hInst,                   /* Instance of window          */
                NULL);                   /* Create struct for WM_CREATE */


 if(hWndMain == NULL)
   {
    lstrcpy(szString, "Window creation failed");
    MessageBox(NULL, szString, NULL, MB_ICONEXCLAMATION);
    return ERR_CREATE_WINDOW;
   }

 ShowWindow(hWndMain, nCmdShow);            /* display main window      */

 lpTLWndList = NULL;
 AddTLWnd(szString, hWndMain);

 while(GetMessage(&msg, NULL, 0, 0))        /* Until WM_QUIT message    */
   {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
   }

 /* Do clean up before exiting from the application                     */
 CwUnRegisterClasses();
 return (int) msg.wParam;
} /*  End of WinMain                                                    */

/************************************************************************/
/*                                                                      */
/* Main Window Procedure                                                */
/*                                                                      */
/* This procedure provides service routines for the Windows events      */
/* (messages) that Windows sends to the window, as well as the user     */
/* initiated events (messages) that are generated when the user selects */
/* the action bar and pulldown menu controls or the corresponding       */
/* keyboard accelerators.                                               */
/*                                                                      */
/************************************************************************/

LRESULT FAR PASCAL WndProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
 HDC         hDC;                /* handle for the display device       */
 PAINTSTRUCT ps;                 /* holds PAINT information             */
 TEXTMETRIC  tm;
 static int  nCharHeight;

 switch (Message)
   {
    case WM_COMMAND:
         /* The Windows messages for action bar and pulldown menu items */
         /* are processed here.                                         */
         switch ((int)wParam)
           {
                case IDM_CLOSE:
                        RemoveTLWnd(hWnd);
                        DestroyWindow(hWnd);
                        if (hWnd == hWndMain) {
                           PostQuitMessage(0);  /* Quit the application                 */
                        }
                 break;

            case IDM_CREATEORAMA:
                 /* Place User Code to respond to the                   */
                 /* Menu Item Named "&Create-O-Rama" here.              */
                 {
                  FARPROC lpfnCREATEMsgProc;

                  hWndCurrent = hWnd;
                  lpfnCREATEMsgProc = MakeProcInstance((FARPROC)CREATEMsgProc, hInst);
                                  DialogBox(hInst, (LPCSTR) MAKEINTRESOURCE(100), hWnd, (DLGPROC) lpfnCREATEMsgProc);
                  FreeProcInstance(lpfnCREATEMsgProc);
                 }
                 break;

            default:
                return DefWindowProc(hWnd, Message, wParam, lParam);
           }
         break;        /* End of WM_COMMAND                             */

    case WM_CREATE:
         // Put Close / Create Buttons on the window
         hDC = GetDC(hWnd);
         SelectObject( hDC, GetStockObject (SYSTEM_FIXED_FONT));
         GetTextMetrics( hDC, &tm);
         ReleaseDC(hWnd, hDC);
         nCharHeight = tm.tmHeight+tm.tmExternalLeading;

         CreateWindow("BUTTON","Close",
		BS_DEFPUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS,
                1, 1, tm.tmAveCharWidth * 15, nCharHeight * 2,
                hWnd, (HMENU)IDM_CLOSE, hInst, NULL);

         CreateWindow("BUTTON","Create-O-Rama",
		BS_DEFPUSHBUTTON | WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS,
                1, nCharHeight*3, tm.tmAveCharWidth * 15, nCharHeight * 2,
		hWnd, (HMENU)IDM_CREATEORAMA, hInst, NULL);

         break;       /*  End of WM_CREATE                              */

    case WM_MOVE:     /*  code for moving the window                    */
         break;

    case WM_SIZE:     /*  code for sizing client area                   */
         break;       /* End of WM_SIZE                                 */

    case WM_LBUTTONDOWN:

         hDC = GetDC(hWnd);
	 lstrcpy(szString,"Some Text...Click on Window to Redraw");
	 TextOut(hDC,1,nCharHeight*6,szString,lstrlen(szString));
	 ReleaseDC(hWnd, hDC);

         break;       /* End of WM_SIZE                                 */

    case WM_PAINT:    /* code for the window's client area              */
         /* Obtain a handle to the device context                       */
         /* BeginPaint will sends WM_ERASEBKGND if appropriate          */
         memset(&ps, 0x00, sizeof(PAINTSTRUCT));
         hDC = BeginPaint(hWnd, &ps);

         /* Included in case the background is not a pure color         */
	 SetBkMode(hDC, TRANSPARENT);

	 lstrcpy(szString,"Some Text...Click on Window to Redraw");
	 TextOut(hDC,1,nCharHeight*6,szString,lstrlen(szString));

         /* Inform Windows painting is complete                         */
         EndPaint(hWnd, &ps);
         break;       /*  End of WM_PAINT                               */

    case WM_CLOSE:  /* close the window                                 */
         /* Destroy child windows, modeless dialogs, then, this window  */
         RemoveTLWnd(hWnd);
         DestroyWindow(hWnd);
         if (hWnd == hWndMain) {
           // Free the menu
           PostQuitMessage(0);  /* Quit the application                 */
         }
        break;

    default:
         /* For any message for which you don't specifically provide a  */
         /* service routine, you should return the message to Windows   */
         /* for default message processing.                             */
         return DefWindowProc(hWnd, Message, wParam, lParam);
   }
 return 0L;
}     /* End of WndProc                                         */

static BOOL  bFirstTime = TRUE;
static char  szOwnerName[128]; // Owner or parent name
static char  szWindowName[128]; // Window Name
static char  szWindowTitle[128]; // Window Title
static HWND  hWndOwner;
static DWORD dStyle,dExtendedStyle;
static int   x,y, nWidth, nHeight;
static BOOL  bAddMenu;
static BOOL  bUseDefaultPos  = TRUE;
static BOOL  bUseDefaultSize = TRUE;

/************************************************************************/
/*                                                                      */
/* Dialog Window Procedure                                              */
/*                                                                      */
/* This procedure is associated with the dialog box that is included in */
/* the function name of the procedure. It provides the service routines */
/* for the events (messages) that occur because the end user operates   */
/* one of the dialog box's buttons, entry fields, or controls.          */
/*                                                                      */
/************************************************************************/

LRESULT FAR PASCAL CREATEMsgProc(HWND hWndDlg, WORD Message, WPARAM wParam, LPARAM lParam)
{
    int   state;
    char  szString[32];
    HWND  hWndSub;
    TLWnd FAR *lpTLItem;
    BOOL bCaption;

    switch(Message) {
        case WM_INITDIALOG:
            cwCenter(hWndDlg, 0);

            if ( bFirstTime )
               SetDefaults(hWndDlg);

            for ( lpTLItem = lpTLWndList; lpTLItem != NULL; lpTLItem = lpTLItem->lpTLWndNext ) {
                ComboBox_AddString(GetDlgItem(hWndDlg, 132), lpTLItem->szName);
            }

            ComboBox_LimitText(GetDlgItem(hWndDlg, 132), 0);
            UpdateDlgDisplay(hWndDlg);

            break; /* End of WM_INITDIALOG                                 */

        case WM_CLOSE:
            /* Closing the Dialog behaves the same as Cancel               */
            PostMessage(hWndDlg, WM_COMMAND, (WPARAM) IDCANCEL, 0L);
            break; /* End of WM_CLOSE                                      */

        case WM_COMMAND:
            switch((int)wParam) {
                case 105: /* Checkbox text: "Child"   */
                    state = Button_GetCheck(GetDlgItem(hWndDlg, 105));
                    if ( state ) {
                        dStyle &= ~WS_POPUP;
                        dStyle |=  WS_CHILD;
                        UpdateDlgDisplay(hWndDlg);
                        ComboBox_SetText(GetDlgItem(hWndDlg, 132), "");
                        ComboBox_Enable(GetDlgItem(hWndDlg, 132), FALSE);
                    }
                    else {
                        Button_SetCheck(GetDlgItem(hWndDlg, 105), 1 );
                        MessageBeep(0);
                    }
                    break;

                case 106: /* Checkbox text: "Overlapped"   */
                    state = Button_GetCheck(GetDlgItem(hWndDlg, 106));
                    if ( state ) {
                        dStyle &= ~WS_CHILD;
                        dStyle &= ~WS_POPUP;
                        UpdateDlgDisplay(hWndDlg);
                        ComboBox_Enable(GetDlgItem(hWndDlg, 132), TRUE);
                    }
                    else {
                        Button_SetCheck(GetDlgItem(hWndDlg, 106), 1 );
                        MessageBeep(0);
                    }
                    break;

                case 107: /* Checkbox text: "Popup"   */
                    state = Button_GetCheck(GetDlgItem(hWndDlg, 107));
                    if ( state ) {
                        dStyle &= ~WS_CHILD;
                        dStyle |=  WS_POPUP;
                        UpdateDlgDisplay(hWndDlg);
                        ComboBox_Enable(GetDlgItem(hWndDlg, 132), TRUE);
                    }
                    else {
                        Button_SetCheck(GetDlgItem(hWndDlg, 107), 1 );
                        MessageBeep(0);
                    }
                    break;

                case 102: /* Checkbox text: "Top Most"   */
                    state = Button_GetCheck(GetDlgItem(hWndDlg, 102));
                    if ( state )
                        dExtendedStyle |= WS_EX_TOPMOST;
                    else
                        dExtendedStyle &= ~WS_EX_TOPMOST;
                    break;

                case 103: /* Checkbox text: "No Parent Notify"   */
                    state = Button_GetCheck(GetDlgItem(hWndDlg, 103));
                    if ( state )
                        dExtendedStyle |= WS_EX_NOPARENTNOTIFY;
                    else
                        dExtendedStyle &= ~WS_EX_NOPARENTNOTIFY;
                    break;

                case 104: /* Checkbox text: "Modal Dialog Frame"   */
                    state = Button_GetCheck(GetDlgItem(hWndDlg, 104));
                    if ( state )
                        dExtendedStyle |= WS_EX_DLGMODALFRAME;
                    else
                        dExtendedStyle &= ~WS_EX_DLGMODALFRAME;
                    break;

                case 114: /* Checkbox text: "Border"   */
                    state = Button_GetCheck(GetDlgItem(hWndDlg, 114));
                    if ( state ) {
                        dStyle &= ~WS_DLGFRAME;
                        dStyle |= WS_BORDER;
                        dStyle &= ~WS_THICKFRAME;
                        Button_SetCheck(GetDlgItem(hWndDlg, 115), 0 );
                        Button_SetCheck(GetDlgItem(hWndDlg, 117), 0 );
		    }
		    else
			dStyle &= ~WS_BORDER;
                    break;

                case 115: /* Checkbox text: "Dialog Frame"   */
                    state = Button_GetCheck(GetDlgItem(hWndDlg, 115));
                    if ( state ) {
                        dStyle &= ~WS_BORDER;
                        dStyle &= ~WS_THICKFRAME;
                        dStyle |= WS_DLGFRAME;
                        Button_SetCheck(GetDlgItem(hWndDlg, 114), 0 );
                        Button_SetCheck(GetDlgItem(hWndDlg, 117), 0 );
		    }
		    else
			dStyle &= ~WS_DLGFRAME;
                    break;

                case 117: /* Checkbox text: "Thick Frame"   */
                    state = Button_GetCheck(GetDlgItem(hWndDlg, 117));
		    if ( state ) {
			//
			// Check for a caption. If there is one then dont clear
			// WS_BORDER or WS_DLGFRAME since that equals caption
			//
			bCaption = ((dStyle & WS_BORDER) && (dStyle & WS_DLGFRAME));
			if ( ! bCaption ) {
			   dStyle &= ~WS_DLGFRAME;
			   dStyle &= ~WS_BORDER;
			}
                        dStyle |= WS_THICKFRAME;
                        Button_SetCheck(GetDlgItem(hWndDlg, 114), 0 );
                        Button_SetCheck(GetDlgItem(hWndDlg, 115), 0 );
		    }
		    else
			dStyle &= ~WS_THICKFRAME;
                    break;

                case 108: /* Checkbox text: "Minimize Box"   */
                    state = Button_GetCheck(GetDlgItem(hWndDlg, 108));
                    if ( state )
                        dStyle |= WS_MINIMIZEBOX;
                    else
                        dStyle &= ~WS_MINIMIZEBOX;
                    break;

                case 109: /* Checkbox text: "Maximize Box"   */
                    state = Button_GetCheck(GetDlgItem(hWndDlg, 109));
                    if ( state )
                        dStyle |= WS_MAXIMIZEBOX;
                    else
                        dStyle &= ~WS_MAXIMIZEBOX;
                     break;

                case 110: /* Checkbox text: "Caption"   */
                    state = Button_GetCheck(GetDlgItem(hWndDlg, 110));
                    if ( state ) {
                        //
                        // If there is no caption you can't have a dialog frame
                        // with WS_DLGFRAME use WS_EX_MODALDLGFRAME for a dialog frame and caption.
                        //
                        // Button_Enable(GetDlgItem(hWndDlg, 115) , 0);
                        //
                        // If there is a Thickframe then nothing to do otherwise
                        // indicate the default a thin frame (WS_BORDER)
                        // but don't add WS_BORDER to the stlye because WS_CAPTION will cause it.
                        //
                        // if ( !(dStyle & WS_DLGFRAME) )
                        //    Button_SetCheck(GetDlgItem(hWndDlg, 114) , 1);

                        dStyle |= WS_CAPTION;
                        UpdateDlgDisplay(hWndDlg);
                    }
                    else {
                        //
                        // Allow for a dialog frame.
                        //
                        // Button_Enable(GetDlgItem(hWndDlg, 115) , 1);
                        //
                        // If there is a specifcally a WS_BORDER then it must be there for the caption
                        //
                        // if ( !( dStyle & WS_BORDER) )
                        //     Button_SetCheck(GetDlgItem(hWndDlg, 114) , 0);

                        dStyle &= ~WS_CAPTION;
                        UpdateDlgDisplay(hWndDlg);
                    }
                    break;

                case 111: /* Checkbox text: "System Menu"   */
                    state = Button_GetCheck(GetDlgItem(hWndDlg, 111));
                    if ( state )
                        dStyle |= WS_SYSMENU;
                    else
                        dStyle &= ~WS_SYSMENU;
                    break;

                case 112: /* Checkbox text: "Veritcal Scroll Bar"   */
                    state = Button_GetCheck(GetDlgItem(hWndDlg, 112));
                    if ( state )
                        dStyle |= WS_VSCROLL;
                    else
                        dStyle &= ~WS_VSCROLL;
                    break;

                case 113: /* Checkbox text: "Horizontal Scroll Bar"   */
                    state = Button_GetCheck(GetDlgItem(hWndDlg, 112));
                    if ( state )
                        dStyle |= WS_HSCROLL;
                    else
                        dStyle &= ~WS_HSCROLL;
                    break;

                case 118: /* Checkbox text: "Clip Children"   */
                    state = Button_GetCheck(GetDlgItem(hWndDlg, 118));
                    if ( state )
                        dStyle |= WS_CLIPCHILDREN;
                    else
                        dStyle &= ~WS_CLIPCHILDREN;
                    break;

                case 119: /* Checkbox text: "Clip Siblings"   */
                    state = Button_GetCheck(GetDlgItem(hWndDlg, 119));
                    if ( state )
                        dStyle |= WS_CLIPSIBLINGS;
                    else
                        dStyle &= ~WS_CLIPSIBLINGS;
                    break;

                case 135: /* Checkbox text: "Default Top Left"   */
                    state = Button_GetCheck(GetDlgItem(hWndDlg, 135));
                    Edit_Enable(GetDlgItem(hWndDlg, 129), !state);
                    Edit_Enable(GetDlgItem(hWndDlg, 128), !state);
                    break;

                case 136: /* Checkbox text: "Default Width Height"   */
                    state = Button_GetCheck(GetDlgItem(hWndDlg, 136));
                    Edit_Enable(GetDlgItem(hWndDlg, 130), !state);
                    Edit_Enable(GetDlgItem(hWndDlg, 131), !state);
                    break;

                case 137: /* Checkbox text: "Maximised"   */
                    state = Button_GetCheck(GetDlgItem(hWndDlg, 137));
		    if ( state ) {
			dStyle |=  WS_MAXIMIZE;
                        dStyle &= ~WS_MINIMIZE;
			Button_SetCheck(GetDlgItem(hWndDlg, 138), 0 );
		    }
		    else
                        dStyle &= ~WS_MAXIMIZE;
                    break;

                case 138: /* Checkbox text: "Minimised"   */
                    state = Button_GetCheck(GetDlgItem(hWndDlg, 138));
		    if ( state ) {
			dStyle |=  WS_MINIMIZE;
			dStyle &= ~WS_MAXIMIZE;
			Button_SetCheck(GetDlgItem(hWndDlg, 137), 0 );
		    }
		    else
                        dStyle &= ~WS_MINIMIZE;
                    break;

                case 139: /* Checkbox text: "Menu"   */
                    state = Button_GetCheck(GetDlgItem(hWndDlg, 139));
                    if ( state )
                        bAddMenu = TRUE;
                    else
                        bAddMenu = FALSE;
                    break;

                case 140: /* Push Button "Overlapped Window" */
                    dStyle = WS_OVERLAPPEDWINDOW;
                    dExtendedStyle = 0L;
                    UpdateDlgDisplay(hWndDlg);
                    break;

                case 141: /* Push Button "Child Window" */
                    dStyle = WS_CHILDWINDOW;
                    dExtendedStyle = 0L;
                    UpdateDlgDisplay(hWndDlg);
                    break;

                case 142: /* Push Button "Popup Window" */
                    dStyle = WS_POPUPWINDOW;
                    dExtendedStyle = 0L;
                    UpdateDlgDisplay(hWndDlg);
                    break;

                case 143: /* Push Button "DialogBox Style" */
                    dStyle = WS_POPUP | WS_SYSMENU | WS_CAPTION;
                    dExtendedStyle = WS_EX_DLGMODALFRAME;
                    UpdateDlgDisplay(hWndDlg);
                    break;

		case 144: /* Checkbox text: "Accept Files" */
		    state = Button_GetCheck(GetDlgItem(hWndDlg, 144));
                    if ( state )
			dExtendedStyle |= WS_EX_ACCEPTFILES;
                    else
			dExtendedStyle &= ~WS_EX_ACCEPTFILES;
                    break;

		case 145: /* Checkbox text: "Transparent" */
		    state = Button_GetCheck(GetDlgItem(hWndDlg, 145));
                    if ( state )
			dExtendedStyle |= WS_EX_TRANSPARENT;
                    else
			dExtendedStyle &= ~WS_EX_TRANSPARENT;
                    break;

                case 132: /* Combo Box                                         */
                    {
                        switch(HIWORD(lParam)) {
                            case CBN_SELCHANGE:
                                break;
                            case CBN_DBLCLK:
                                 break;
                        }
                    }
                    break;

                case 123: /* Button text: "Create Window"                   */
                    // x,y
                    state = Button_GetCheck(GetDlgItem(hWndDlg, 135));
		    if ( state ) {
			// This must be an overlapped window
			// ( This program enforces that )
			// Since we are using CW_USEDEFAULT
			// the Y value to CreateWindow should be
			// SW_SHOW or some other SW_*

			// SW_HIDE
			// SW_SHOWNORMAL
			// SW_NORMAL
			// SW_SHOWMINIMIZED
			// SW_SHOWMAXIMIZED
			// SW_MAXIMIZE
			// SW_SHOWNOACTIVATE
			// SW_SHOW
			// SW_MINIMIZE
			// SW_SHOWMINNOACTIVE
			// SW_SHOWNA
			// SW_RESTORE
			//
                        x = CW_USEDEFAULT;
			y = SW_SHOW;
                    }
                    else {
                        Edit_GetText(GetDlgItem(hWndDlg, 128),szString, 32);
                        x = atoi(szString);
                        Edit_GetText(GetDlgItem(hWndDlg, 129),szString, 32);
                        y = atoi(szString);
                    }

                    // Width, Height
                    state = Button_GetCheck(GetDlgItem(hWndDlg, 136));
                    if ( state ) {
                        nWidth = CW_USEDEFAULT;
                        nHeight = 0;
                    }
                    else {
                       Edit_GetText(GetDlgItem(hWndDlg, 130),szString, 32);
                       nWidth = atoi(szString);
                       Edit_GetText(GetDlgItem(hWndDlg, 131),szString, 32);
                       nHeight = atoi(szString);
                       if ( nWidth == 0 || nHeight == 0 ) {
                          MessageBox(hWndDlg, "Going to Use 200 by 200", "No Size For Window", MB_ICONINFORMATION);
                          nWidth  = 200;
                          nHeight = 200;
                       }
                    }

                    // Add a Menu ?
                    if ( bAddMenu )
                        hMenu = LoadMenu(hInst, szAppName);
                    else
                        hMenu = NULL;

                    //
                    // Name
                    //
                    LoadString(hInst, getrandom(0, LASTNAME),
			       szWindowName, sizeof(szWindowName));
		    lstrcpy(szWindowTitle,szWindowName);

                    // WS_CHILD needs an Owner Handle
                    if ( dStyle & WS_CHILD ) {
			hWndOwner = hWndCurrent;
			lstrcat(szWindowTitle," Child of ");
			FindTLWndByHWnd(hWndCurrent, szString);
			lstrcat(szWindowTitle,szString);
                    }
                    else {
                        //
                        // Is this an owned Window
                        //
                        ComboBox_GetText(GetDlgItem(hWndDlg, 132), szString, sizeof(szString));
			if (lstrlen(szString) != 0 ) {
                        // if ( ComboBox_GetTextLength(GetDlgItem(hWndDlg, 132)) != 0 ) {
			    hWndOwner = FindTLWndByName(szString);
			    lstrcat(szWindowTitle," Owned by ");
			    lstrcat(szWindowTitle,szString);
                        }
                        else
                            hWndOwner = NULL;
                    }

                    //
                    // Create the window
                    //
                    hWndSub = CreateWindowEx(
                            dExtendedStyle,
                            szAppName,
			    szWindowTitle,
			    dStyle | WS_VISIBLE,  // Forcing WS_VISIBLE ON
                            x, y,
                            nWidth, nHeight,
                            hWndOwner,
                            hMenu,
                            hInst,
                            NULL);
		    //
		    // if not a child window add to our top level list
		    //
                    if ( !(dStyle & WS_CHILD) )
			AddTLWnd(szWindowName, hWndSub);

                    EndDialog(hWndDlg, FALSE);
                    break;

                case IDCANCEL:
                    /* Ignore data values entered into the controls        */
                    /* and dismiss the dialog window returning FALSE       */
                    EndDialog(hWndDlg, FALSE);
                    break;
            }
            break;    /* End of WM_COMMAND                                 */

        default:
            return FALSE;
    }

    return (LRESULT) TRUE;

} /* End of CREATEMsgProc                                      */

//
// Update Dialog Box Display
//
void UpdateDlgDisplay(HWND hWndDlg)
{
    if ( (dStyle & WS_CHILD) || (dStyle & WS_POPUP) ) {
        if ( (dStyle & WS_CHILD) ) {
            Button_SetCheck(GetDlgItem(hWndDlg, 105), 1 );
            Button_SetCheck(GetDlgItem(hWndDlg, 107), 0 );
            ComboBox_Enable(GetDlgItem(hWndDlg, 132), FALSE);
        }
        else {
            Button_SetCheck(GetDlgItem(hWndDlg, 105), 0 );
            Button_SetCheck(GetDlgItem(hWndDlg, 107), 1 );
            ComboBox_Enable(GetDlgItem(hWndDlg, 132), TRUE);
        }
        Button_SetCheck(GetDlgItem(hWndDlg, 106), 0 );

        //
        // Captions are optional on child and popup
        //
        Button_Enable(GetDlgItem(hWndDlg, 110), TRUE);
	Button_SetCheck(GetDlgItem(hWndDlg, 110),
	    ((dStyle & WS_BORDER) && (dStyle & WS_DLGFRAME)) ? 1 : 0 );

        //
        // Popup and Child windows must have specific top,left,width and height
        //
        // Uncheck and Disable the Default check buttons
        //
        Button_SetCheck(GetDlgItem(hWndDlg, 135), 0 );
        Button_SetCheck(GetDlgItem(hWndDlg, 136), 0 );
        Button_Enable(GetDlgItem(hWndDlg, 135), FALSE);
        Button_Enable(GetDlgItem(hWndDlg, 136), FALSE);

        //
        // Enable the Edit boxes
        //
        Edit_Enable(GetDlgItem(hWndDlg, 129), TRUE);
        Edit_Enable(GetDlgItem(hWndDlg, 128), TRUE);
        Edit_Enable(GetDlgItem(hWndDlg, 130), TRUE);
        Edit_Enable(GetDlgItem(hWndDlg, 131), TRUE);
    }
    else {
        Button_SetCheck(GetDlgItem(hWndDlg, 105), 0 );
        Button_SetCheck(GetDlgItem(hWndDlg, 107), 0 );
        Button_SetCheck(GetDlgItem(hWndDlg, 106), 1 );
        ComboBox_Enable(GetDlgItem(hWndDlg, 132), TRUE);

        //
        // Overlapped Windows must have a caption disable the check box
        //
        Button_SetCheck(GetDlgItem(hWndDlg, 110), 1);
        Button_Enable(GetDlgItem(hWndDlg, 110), FALSE);

        // Button_SetCheck(GetDlgItem(hWndDlg, 114), 0 );
        // Button_Enable(GetDlgItem(hWndDlg, 114), FALSE);

        //
        // Overlapped windows may have default top,left,width and height
        //
        // Check and Enable the Default check buttons
        //
        Button_SetCheck(GetDlgItem(hWndDlg, 135), 1 );
        Button_SetCheck(GetDlgItem(hWndDlg, 136), 1 );
        Button_Enable(GetDlgItem(hWndDlg, 135), TRUE);
        Button_Enable(GetDlgItem(hWndDlg, 136), TRUE);

        //
        // disable the Edit boxes until the check boxes unchecked
        //
        Edit_Enable(GetDlgItem(hWndDlg, 130), FALSE);
        Edit_Enable(GetDlgItem(hWndDlg, 131), FALSE);
        Edit_Enable(GetDlgItem(hWndDlg, 129), FALSE);
        Edit_Enable(GetDlgItem(hWndDlg, 128), FALSE);
    }


    if ( ((dStyle & WS_BORDER) && (dStyle & WS_DLGFRAME))
       || (Button_GetCheck(GetDlgItem(hWndDlg, 110))) ) {

        Button_SetCheck(GetDlgItem(hWndDlg, 110), 1 );

        //
        // Enable the styles that must have a caption to appear
        //
        Button_Enable(GetDlgItem(hWndDlg, 108), TRUE);
        Button_Enable(GetDlgItem(hWndDlg, 109), TRUE);
        Button_Enable(GetDlgItem(hWndDlg, 111), TRUE);

        //
        // Windows with captions can't have dialog frames
        //
        Button_Enable(GetDlgItem(hWndDlg, 115), FALSE );
	Button_SetCheck(GetDlgItem(hWndDlg, 115), 0 );

	//
	// if a thick frame is specified fine otherwise default a
	// regular border.
	//
	if ( (dStyle & WS_THICKFRAME) ) {
	   Button_SetCheck(GetDlgItem(hWndDlg, 117), 1);
	   Button_SetCheck(GetDlgItem(hWndDlg, 114), 0);
	}
	else {
	   Button_SetCheck(GetDlgItem(hWndDlg, 117), 0);
	   Button_SetCheck(GetDlgItem(hWndDlg, 114), 1);
	}
    }
    else {
        Button_SetCheck(GetDlgItem(hWndDlg, 110), 0 );

        //
        // Disable the styles that must have a caption to appear
        //
        Button_Enable(GetDlgItem(hWndDlg, 108), FALSE);
        Button_Enable(GetDlgItem(hWndDlg, 109), FALSE);
        Button_Enable(GetDlgItem(hWndDlg, 111), FALSE);

        //
	// Dialoge frames are possible
        //
        Button_Enable(GetDlgItem(hWndDlg, 115), TRUE );
        Button_SetCheck(GetDlgItem(hWndDlg, 114), (dStyle & WS_BORDER) ? 1 : 0 );
        Button_SetCheck(GetDlgItem(hWndDlg, 115), (dStyle & WS_DLGFRAME) ? 1 : 0 );
    }

    //
    // If the Style bit is on ... check the button
    //
    Button_SetCheck(GetDlgItem(hWndDlg, 108), (dStyle & WS_MINIMIZEBOX) ? 1 : 0 );
    Button_SetCheck(GetDlgItem(hWndDlg, 109), (dStyle & WS_MAXIMIZEBOX) ? 1 : 0 );
    Button_SetCheck(GetDlgItem(hWndDlg, 111), (dStyle & WS_SYSMENU) ? 1 : 0 );
    Button_SetCheck(GetDlgItem(hWndDlg, 112), (dStyle & WS_VSCROLL) ? 1 : 0 );
    Button_SetCheck(GetDlgItem(hWndDlg, 113), (dStyle & WS_HSCROLL) ? 1 : 0 );
    Button_SetCheck(GetDlgItem(hWndDlg, 137), (dStyle & WS_MAXIMIZE) ? 1 : 0 );
    Button_SetCheck(GetDlgItem(hWndDlg, 138), (dStyle & WS_MINIMIZE) ? 1 : 0 );

    Button_SetCheck(GetDlgItem(hWndDlg, 117), (dStyle & WS_BORDER) ? 1 : 0 );
    Button_SetCheck(GetDlgItem(hWndDlg, 117), (dStyle & WS_THICKFRAME) ? 1 : 0 );

    //
    // Are we adding a menu?
    //
    Button_SetCheck(GetDlgItem(hWndDlg, 139), bAddMenu );


    //
    // Set Up top, left
    //
    if ( x == CW_USEDEFAULT ) {
       Edit_SetText(GetDlgItem(hWndDlg, 129), "10");
       Edit_SetText(GetDlgItem(hWndDlg, 128), "10");
    }
    else {
       sprintf(szString,"%d",x);
       Edit_SetText(GetDlgItem(hWndDlg, 129), szString);
       sprintf(szString,"%d",y);
       Edit_SetText(GetDlgItem(hWndDlg, 128), szString);
    }

    //
    // Set Up width, height
    //
    if ( nWidth == CW_USEDEFAULT ) {
        Edit_SetText(GetDlgItem(hWndDlg, 130), "200");
        Edit_SetText(GetDlgItem(hWndDlg, 131), "200");
    }
    else {
        sprintf(szString,"%d",nWidth);
        Edit_SetText(GetDlgItem(hWndDlg, 130), szString);
        sprintf(szString,"%d",nHeight);
        Edit_SetText(GetDlgItem(hWndDlg, 131), szString);
    }

    //
    // If the Style bit is on ... check the button
    //
    Button_SetCheck(GetDlgItem(hWndDlg, 118),
          (dStyle & WS_CLIPCHILDREN) ? 1 : 0 );
    Button_SetCheck(GetDlgItem(hWndDlg, 119),
          (dStyle & WS_CLIPSIBLINGS) ? 1 : 0 );

    //
    // If the Extended Style bit is on ... check the button
    //
    Button_SetCheck(GetDlgItem(hWndDlg, 102),
          (dExtendedStyle & WS_EX_TOPMOST) ? 1 : 0 );
    Button_SetCheck(GetDlgItem(hWndDlg, 103),
          (dExtendedStyle & WS_EX_NOPARENTNOTIFY) ? 1 : 0 );
    Button_SetCheck(GetDlgItem(hWndDlg, 104),
          (dExtendedStyle & WS_EX_DLGMODALFRAME) ? 1 : 0 );
    Button_SetCheck(GetDlgItem(hWndDlg, 144),
	  (dExtendedStyle & WS_EX_ACCEPTFILES) ? 1 : 0 );
    Button_SetCheck(GetDlgItem(hWndDlg, 145),
	  (dExtendedStyle & WS_EX_TRANSPARENT) ? 1 : 0 );

}

//
// Set Defaults for Create-O-Rama Dialog Box
//
void SetDefaults(HWND hWndDlg)
{
    /* initialize working variables                                */

    hWndOwner      = NULL;
    dStyle         = WS_OVERLAPPED;
    dExtendedStyle = 0L;
    x              = CW_USEDEFAULT;
    y              = 0;
    nWidth         = CW_USEDEFAULT;
    nHeight        = 0;
    bAddMenu       = NULL;
    bFirstTime     = FALSE;
}

//
// Add window to top level name list
//
void AddTLWnd(char *szName, HWND hWnd)
{
    TLWnd FAR *lpTLNew;
    TLWnd FAR *lpTLItem;

    if ( (lpTLNew = (TLWnd FAR *)GlobalAllocPtr(GHND, sizeof(struct _TLWnd))) == NULL ) {
        lstrcpy(szString,"Not Enough Memory");
        MessageBox(NULL, szString, NULL, MB_ICONEXCLAMATION);
        return;
    }

    lpTLNew->lpTLWndNext = NULL;
    lpTLNew->hWnd        = hWnd;
    lstrcpy(lpTLNew->szName, szName);

    if ( lpTLWndList == NULL )
        lpTLWndList = lpTLNew;
    else {
        for ( lpTLItem = lpTLWndList; lpTLItem->lpTLWndNext != NULL;
          lpTLItem = lpTLItem->lpTLWndNext );

        lpTLItem->lpTLWndNext = lpTLNew;
    }
}

//
// Find window from top level list
//
HWND FindTLWndByName(char *szName)
{
    TLWnd FAR *lpTLItem;

    for ( lpTLItem = lpTLWndList; lpTLItem != NULL; lpTLItem = lpTLItem->lpTLWndNext ) {
        if ( lstrcmp(lpTLItem->szName,szName) == 0 )
           return lpTLItem->hWnd;
    }

    return NULL;
}

//
// Find window from top level list
//
void FindTLWndByHWnd(HWND hWnd, char *szName)
{
    TLWnd FAR *lpTLItem;


    szName[0] = '\0';
    for ( lpTLItem = lpTLWndList; lpTLItem != NULL; lpTLItem = lpTLItem->lpTLWndNext ) {
	if ( lpTLItem->hWnd == hWnd ) {
	   lstrcpy(szName,lpTLItem->szName);
	   return ;
	}
    }

    return ;
}

//
// Delete window for top level list
//
void RemoveTLWnd(HWND hWnd)
{
    TLWnd FAR *lpTLItem;
    TLWnd FAR * FAR *lpTLPrev;

    for ( lpTLItem = lpTLWndList, lpTLPrev = &(lpTLWndList->lpTLWndNext); lpTLItem != NULL; lpTLItem = lpTLItem->lpTLWndNext ) {
        if ( lpTLItem->hWnd == hWnd ) {
            *(lpTLPrev) = lpTLItem->lpTLWndNext;
            GlobalFreePtr(lpTLItem);
            return;
        }
        else
            lpTLPrev = &(lpTLItem->lpTLWndNext);
    }

    return ;
}

/************************************************************************/
/*                                                                      */
/* nCwRegisterClasses Function                                          */
/*                                                                      */
/* The following function registers all the classes of all the windows  */
/* associated with this application. The function returns an error code */
/* if unsuccessful, otherwise it returns 0.                             */
/*                                                                      */
/************************************************************************/

int nCwRegisterClasses(void)
{
 WNDCLASS   wndclass;    /* struct to define a window class             */
 memset(&wndclass, 0x00, sizeof(WNDCLASS));


 /* load WNDCLASS with window's characteristics                         */
 wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_BYTEALIGNWINDOW;
 wndclass.lpfnWndProc = WndProc;
 /* Extra storage for Class and Window objects                          */
 wndclass.cbClsExtra = 0;
 wndclass.cbWndExtra = 0;
 wndclass.hInstance = hInst;
 wndclass.hIcon = LoadIcon(hInst, "STYLES");
 wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
 /* Create brush for erasing background                                 */
 wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
 wndclass.lpszMenuName = NULL;   /* None By Default */
 wndclass.lpszClassName = szAppName; /* Class Name is App Name */
 if(!RegisterClass(&wndclass))
   return -1;

 return(0);
} /* End of nCwRegisterClasses                                          */

/************************************************************************/
/*  cwCenter Function                                                   */
/*                                                                      */
/*  centers a window based on the client area of its parent             */
/*                                                                      */
/************************************************************************/

void cwCenter(hWnd, top)
HWND hWnd;
int top;
{
 POINT      pt;
 RECT       swp;
 int        iwidth;
 int        iheight;

 /* get the rectangles for the parent and the child                     */
 GetWindowRect(hWnd, &swp);

 /* calculate the height and width for MoveWindow                       */
 iwidth = swp.right - swp.left;
 iheight = swp.bottom - swp.top;

 // Since This dialog is so big put it a 1,1
 pt.y = 1;
 pt.x = 1;

 /* move the window                                                     */
 MoveWindow(hWnd, pt.x, pt.y, iwidth, iheight, FALSE);
}

/************************************************************************/
/*  CwUnRegisterClasses Function                                        */
/*                                                                      */
/*  Deletes any refrences to windows resources created for this         */
/*  application, frees memory, deletes instance, handles and does       */
/*  clean up prior to exiting the window                                */
/*                                                                      */
/************************************************************************/

void CwUnRegisterClasses(void)
{
 UnregisterClass(szAppName, hInst);
}    /* End of CwUnRegisterClasses                                      */
