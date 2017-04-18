/*-----------------------------------------------------------------------------
    This is a part of the Microsoft Source Code Samples. 
    Copyright (C) 1995 Microsoft Corporation.
    All rights reserved. 
    This source code is only intended as a supplement to 
    Microsoft Development Tools and/or WinHelp documentation.
    See these sources for detailed information regarding the 
    Microsoft samples programs.

    MODULE: mttty.c

    PURPOSE: Program entry point and window management

    FUNCTIONS:
        WinMain            - Program entry point
        VersionCheck       - Checks OS version to make sure we can run
        InitializeApp      - Global program initialization and window class
                             creation
        MTTTYWndProc       - main window procedure
        CmdDispatch        - Carries out menu commands
        OpenTTYChildWindow - Creates the tty child window
        ScrollTTYVert      - Scroll TTY window vertically
        ScrollTTYHorz      - Scrolls TTY window horizontally
        PaintTTY           - Paints the TTY window
        MoveTTYCursor      - moves the tty cursor
        SetTTYFocus        - responds to tty window getting focus
        KillTTYFocus       - responds to tty window losing focus
        SizeTTY            - responds to tty window size changes
        TTYChildProc       - window procedure for TTY child window

-----------------------------------------------------------------------------*/

#include <windows.h>
#include "mttty.h"

/*
    Prototypes for functions called only within this file
*/
BOOL InitializeApp( HINSTANCE, int);
int WINAPI MTTTYWndProc( HWND, UINT, WPARAM, LPARAM );
int WINAPI TTYChildProc( HWND, UINT, WPARAM, LPARAM );
void CmdDispatch( int, HWND, LPARAM );
void OpenTTYChildWindow( HWND );
BOOL ScrollTTYVert( HWND, WORD, WORD );
BOOL ScrollTTYHorz( HWND, WORD, WORD );
BOOL VersionCheck();
BOOL PaintTTY( HWND );


/*-----------------------------------------------------------------------------

FUNCTION: WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
 
PURPOSE: Start application and process all window messages

PARAMETERS:
    hInstance     - this apps hinstance
    hPrevInstance - previous instance of this app - always NULL
    lpCmdLine     - command line parameters
    nCmdShow      - code for showing window

RETURN:
    1 for success
    0 for failure to start app

HISTORY:   Date:      Author:     Comment:
           10/27/95   AllenD      Wrote it

/*-----------------------------------------------------------------------------*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    MSG msg;

    if (!VersionCheck()) {
        MessageBox(NULL, "MTTTY can't run on this version of Windows.", NULL, MB_OK);
        return 0;
    }

    if (!InitializeApp(hInstance, nShowCmd)) {
        MessageBox(NULL, "MTTTY couldn't start!", NULL, MB_OK);
        return 0;
    }

    while (GetMessage(&msg, NULL, 0, 0)) {
        if (!TranslateAccelerator( ghwndMain, ghAccel, &msg )) {
            TranslateMessage( &msg ) ;
            DispatchMessage( &msg ) ;
        }
    }

    return 1;
}


/*-----------------------------------------------------------------------------

FUNCTION: VersionCheck(void)

PURPOSE: Verifies that the correct version of Windows is running

RETURN:
    TRUE  - success version for running this app
    FALSE - correct version not verified

HISTORY:   Date:      Author:     Comment:
           11/20/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
BOOL VersionCheck()
{
    gOSV.dwOSVersionInfoSize = sizeof(gOSV);
    if (!GetVersionEx(&gOSV))
        return FALSE;

    if (gOSV.dwPlatformId == VER_PLATFORM_WIN32s)
        return FALSE;

    return TRUE ;
}


/*-----------------------------------------------------------------------------

FUNCTION: InitializeApp(HINSTANCE, int)

PURPOSE: GlobalInitialize, Register window classes 
         and create main window

PARAMETERS:
    hInst    - HINSTANCE of this app
    nShowCmd - code for showing this window

RETURN:
    TRUE  - successful inititialization of this app
    FALSE - failure to init app

HISTORY:   Date:      Author:     Comment:
           10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
BOOL InitializeApp(HINSTANCE hInst, int nShowCmd)
{
    WNDCLASS wc = {0};

    GlobalInitialize();     // get all global variables initialized to defaults

    //
    // setup program's main window class
    //
    wc.lpfnWndProc      = (WNDPROC) MTTTYWndProc;
    wc.hInstance        = hInst;
    wc.hIcon            = LoadIcon(hInst,MAKEINTRESOURCE(IDI_APPICON));
    wc.hCursor          = LoadCursor(NULL, IDC_ARROW);
    wc.lpszMenuName     = MAKEINTRESOURCE(IDR_MTTTYMENU);
    wc.hbrBackground    = (HBRUSH) (COLOR_WINDOW + 1) ;
    wc.lpszClassName    = "MTTTYClass";

    if (!RegisterClass(&wc)) {
        GlobalCleanup();
        return FALSE;
    }

    //
    // setup program's tty child window class
    //
    wc.lpfnWndProc      = (WNDPROC) TTYChildProc;
    wc.hInstance        = hInst;
    wc.hCursor          = LoadCursor(NULL, IDC_IBEAM);
    wc.hbrBackground    = (HBRUSH) (COLOR_WINDOW + 1);
    wc.lpszClassName    = "MTTTYChildClass";
    wc.lpszMenuName     = NULL;
    wc.hIcon            = NULL;

    if (!RegisterClass(&wc)) {
        GlobalCleanup();
        return FALSE;
    }

    //
    // create main window
    //
    ghwndMain = CreateWindow("MTTTYClass", "Multi-threaded TTY",
            WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
            STARTXWINDOW, STARTYWINDOW,
            MAXXWINDOW, MAXYWINDOW,
            NULL, NULL, hInst, NULL);

    if (ghwndMain == NULL) {
        GlobalCleanup();
        return FALSE;
    }

    ShowWindow( ghwndMain, nShowCmd ) ;   
    UpdateWindow( ghwndMain ) ;

    ghInst = hInst;
    ghAccel = LoadAccelerators( hInst, MAKEINTRESOURCE( IDR_MTTTYACCELERATOR) ) ;

    return TRUE;
}


/*-----------------------------------------------------------------------------

FUNCTION: MTTTYWndProc(HWND, UINT, WPARAM, LPARAM)

PURPOSE: Window Procedure for main window

PARAMETERS:
    hwnd    - window handle
    message - window message
    wParam  - window message parameter (depends on message)
    lParam  - window message parameter (depends on message)

RETURN:
    If message is process, return value is 0
    If message is not processed, then it is passed to DefWindowProc
    and the return value from that function is returned
    
HISTORY:   Date:      Author:     Comment:
           10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
int WINAPI MTTTYWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) 
    {
        case WM_CREATE:
            //
            // since main window is created, I can now open all other windows
            //
            InitTTYInfo();
            OpenTTYChildWindow(hwnd);
            OpenSettingsToolbar(hwnd);
            OpenStatusToolbar(hwnd);
            ChangeConnection(hwnd, CONNECTED(TTYInfo));
            break;

        case WM_DESTROY: 
            //
            // since main windows is being destroyed, so same to other windows
            //
            DestroyTTYInfo();
            DestroyWindow(ghWndToolbarDlg);
            DestroyWindow(ghWndStatusDlg);
            DestroyWindow(ghWndTTY);
				
            GlobalCleanup();
            PostQuitMessage(0);
            break;

        case WM_GETMINMAXINFO:
            {
                //
                // make sure that main window doesn't get smaller than
                // the minimum child windows.
                //
                LPMINMAXINFO lpTemp;
                POINT        ptTemp;

                lpTemp = (LPMINMAXINFO) lParam;
      
                ptTemp.x = (long) lpTemp->ptMinTrackSize.x;
                ptTemp.y = (long) gcyMinimumWindowHeight;

                lpTemp->ptMinTrackSize = ptTemp;
            }
        
            break;

        case WM_SIZE:
            {
                //
                // main window size has changed,
                // so I need to change the positions of child windows
                //
                WORD wTop;
                WORD wHeight;
                WORD wWidth = LOWORD(lParam);

                //
                // put Settings window at top
                //
                wHeight = SETTINGSFACTOR*gwBaseY;
                wTop = 0;
                MoveWindow(ghWndToolbarDlg, 0,wTop, wWidth, wHeight, TRUE);

                //
                // put Status window at bottom
                //
                wHeight = STATUSFACTOR*gwBaseY;
                wTop = HIWORD(lParam) - wHeight;
                MoveWindow(ghWndStatusDlg, 0, wTop, wWidth, wHeight, TRUE);

                //
                // put TTTY window right in the middle
                // height = whole window - height of two previous windows
                //
                wHeight = HIWORD(lParam) - ((STATUSFACTOR + SETTINGSFACTOR)*gwBaseY);
                wTop = SETTINGSFACTOR*gwBaseY;
                MoveWindow(ghWndTTY, 0, wTop, wWidth, wHeight, TRUE);
            }
         
            break;

      case WM_COMMAND:       
            CmdDispatch(LOWORD(wParam), hwnd, lParam);        
            break;

      case WM_CHAR:
            SetFocus(ghWndTTY);
            SendMessage(ghWndTTY, WM_CHAR, wParam, lParam);
            break;

      case WM_CLOSE:
            if (DisconnectOK()) {
                if (CONNECTED(TTYInfo)) {
                    if (TRANSFERRING(TTYInfo))
                        TransferFileTextEnd();
                    BreakDownCommPort();
                }
                DestroyWindow(hwnd);
            }
            break;

      default:
            return DefWindowProc(hwnd, message, wParam, lParam);
    }

    return 0L;
}

/*-----------------------------------------------------------------------------

FUNCTION: CmdDispatch(int, HWND)

PURPOSE: Responds to menu selections

PARAMETERS:
    iMenuChoice - ID of menu choice (from resource file)
    hwnd        - window handle of menu owner

HISTORY:   Date:      Author:     Comment:
           10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
void CmdDispatch(int iMenuChoice, HWND hwnd, LPARAM lParam)
{
    static char szFileName[MAX_PATH] = {0};

    switch (iMenuChoice) 
    {
        case ID_HELP_ABOUTMTTTY:
            CmdAbout(hwnd);
            break;

        case ID_TRANSFER_SENDFILETEXT:
            {
                char * szFilter = "Text Files\0*.TXT\0";
                OPENFILENAME ofn = {0};

                ofn.lStructSize = sizeof(OPENFILENAME);
                ofn.hwndOwner = hwnd;
                ofn.lpstrFilter = szFilter;
                ofn.lpstrFile = szFileName;
                ofn.nMaxFile = MAX_PATH;
                ofn.lpstrTitle = "Send File";
                ofn.Flags = OFN_FILEMUSTEXIST;

                if (!GetOpenFileName(&ofn))
                    break;
                
                if (TRUE)
                    TransferFileTextStart(szFileName);
            }
            break;

        case ID_TRANSFER_RECEIVEFILETEXT:
            {
                char * szFilter = "Text Files\0*.TXT\0";
                OPENFILENAME ofn = {0};

                ofn.lStructSize = sizeof(OPENFILENAME);
                ofn.hwndOwner = hwnd;
                ofn.lpstrFilter = szFilter;
                ofn.lpstrFile = szFileName;
                ofn.nMaxFile = MAX_PATH;
                ofn.lpstrTitle = "Receive File";
                ofn.Flags = OFN_OVERWRITEPROMPT;

                if (!GetSaveFileName(&ofn))
                    break;

                ReceiveFileText(szFileName);
            }
            break;

        case ID_TRANSFER_ABORTSENDING:
            // was abort sent from the abort button?
            if (LOWORD(lParam) == IDC_ABORTBTN) {
                // am I in a transfer repeat?
                if (REPEATING(TTYInfo))
                    TransferRepeatDestroy();
                // am I in a normal recieve state, then stop sending
                else if (gdwReceiveState == RECEIVE_TTY)
                    TransferFileTextEnd();
                // if I am not in a normal receive state, then stop capturing
                else
                    gfAbortTransfer = TRUE;
            }
            else
                // transfer abort was sent by transfer thread   
                TransferFileTextEnd();
            break;

        case ID_TRANSFER_SENDREPEATEDLY:
            {
                DWORD dwFreq;
                char * szFilter = "Text Files\0*.TXT\0";
                OPENFILENAME ofn = {0};

                ofn.lStructSize = sizeof(OPENFILENAME);
                ofn.hwndOwner = hwnd;
                ofn.lpstrFilter = szFilter;
                ofn.lpstrFile = szFileName;
                ofn.nMaxFile = MAX_PATH;
                ofn.lpstrTitle = "Send File Repeatedly";
                ofn.Flags = OFN_FILEMUSTEXIST;

                if (!GetOpenFileName(&ofn))
                    break;

                dwFreq = GetAFrequency();
                
                TransferRepeatCreate(szFileName, dwFreq);
            }
            break;

        case ID_TRANSFER_ABORTREPEATEDSENDING:
            TransferRepeatDestroy();
            break;

        case ID_TTY_CLEAR:
            ClearTTYContents();
            InvalidateRect(ghWndTTY, NULL, TRUE);
            break;

        // The following correspond to menu choices and buttons in the settings dlog
        case IDC_FONTBTN:
        case IDC_COMMEVENTSBTN:
        case IDC_FLOWCONTROLBTN:
        case IDC_TIMEOUTSBTN:
            SendMessage(ghWndToolbarDlg, WM_COMMAND, (WPARAM) iMenuChoice, (LPARAM) GetDlgItem(ghWndToolbarDlg, iMenuChoice));
            break;

        case ID_FILE_CONNECT:
            if (SetupCommPort() != NULL)
                ChangeConnection(hwnd, CONNECTED(TTYInfo));
            break;

        case ID_FILE_DISCONNECT:
            if (BreakDownCommPort())
                ChangeConnection(hwnd, CONNECTED(TTYInfo));
            break;

        case ID_FILE_EXIT:
            PostMessage(hwnd, WM_CLOSE, 0, 0);
            break;
    }
    return;
}


/*-----------------------------------------------------------------------------

FUNCTION: OpenTTYChildWindow(HWND)

PURPOSE: Creates the TTY Child Window

PARAMETERS:
    hWnd - parent window handle of TTY child window

COMMENTS: This window is actually the TTY Screen

HISTORY:   Date:      Author:     Comment:
           10/27/95   AllenD      Wrote it

/*-----------------------------------------------------------------------------*/
void OpenTTYChildWindow(HWND hWnd)
{
    ghWndTTY = CreateWindow( "MTTTYChildClass", "TTY Window", 
                             WS_CHILD | WS_VISIBLE | WS_VSCROLL,
                             0,0,
                             0,0,
                             hWnd, (HMENU)ID_TTYWINDOW, ghInst, NULL);
    if (ghWndTTY == NULL)
        ErrorReporter("Can't Create TTY Child Window");

    return;
}


//---------------------------------------------------------------------------
//  BOOL NEAR ScrollTTYVert( HWND hWnd, WORD wScrollCmd, WORD wScrollPos )
//
//  Description:
//     Scrolls TTY window vertically.
//
//  Parameters:
//     HWND hWnd
//        handle to TTY window
//
//     WORD wScrollCmd
//        type of scrolling we're doing
//
//     WORD wScrollPos
//        scroll position
//
//  History:   Date       Author      Comment
//              5/ 8/91   BryanW      Wrote it.
//             10/27/95   AllenD      Included it for MTTTY Sample.
//
//---------------------------------------------------------------------------
BOOL NEAR ScrollTTYVert( HWND hWnd, WORD wScrollCmd, WORD wScrollPos )
{
   int  nScrollAmt ;

   switch (wScrollCmd)
   {
      case SB_TOP:
         nScrollAmt = -YOFFSET( TTYInfo ) ;
         break ;

      case SB_BOTTOM:
         nScrollAmt = YSCROLL( TTYInfo ) - YOFFSET( TTYInfo ) ;
         break ;

      case SB_PAGEUP:
         nScrollAmt = -YSIZE( TTYInfo ) ;
         break ;

      case SB_PAGEDOWN:
       nScrollAmt = YSIZE( TTYInfo ) ;
         break ;

      case SB_LINEUP:
         nScrollAmt = -YCHAR( TTYInfo ) ;
         break ;

      case SB_LINEDOWN:
         nScrollAmt = YCHAR( TTYInfo ) ;
         break ;

      case SB_THUMBPOSITION:
         nScrollAmt = wScrollPos - YOFFSET( TTYInfo ) ;
         break ;

      default:
         return ( FALSE ) ;
   }

   if ((YOFFSET( TTYInfo ) + nScrollAmt) > YSCROLL( TTYInfo ))
      nScrollAmt = YSCROLL( TTYInfo ) - YOFFSET( TTYInfo ) ;

   if ((YOFFSET( TTYInfo ) + nScrollAmt) < 0)
      nScrollAmt = -YOFFSET( TTYInfo ) ;

   ScrollWindowEx( hWnd, 0, -nScrollAmt, NULL, NULL, NULL, NULL, SW_INVALIDATE | SW_ERASE) ;

   YOFFSET( TTYInfo ) = YOFFSET( TTYInfo ) + nScrollAmt ;

   SetScrollPos( hWnd, SB_VERT, YOFFSET( TTYInfo ), TRUE ) ;

   return ( TRUE ) ;

} // end of ScrollTTYVert()

//---------------------------------------------------------------------------
//  BOOL NEAR ScrollTTYHorz( HWND hWnd, WORD wScrollCmd, WORD wScrollPos )
//
//  Description:
//     Scrolls TTY window horizontally.
//
//  Parameters:
//     HWND hWnd
//        handle to TTY window
//
//     WORD wScrollCmd
//        type of scrolling we're doing
//
//     WORD wScrollPos
//        scroll position
//
//  History:   Date       Author      Comment
//              5/ 8/91   BryanW      Wrote it.
//             10/27/95   AllenD      Included it for MTTTY Sample.
//
//---------------------------------------------------------------------------
BOOL NEAR ScrollTTYHorz( HWND hWnd, WORD wScrollCmd, WORD wScrollPos )
{
   int  nScrollAmt ;

   switch (wScrollCmd)
   {
      case SB_TOP:
         nScrollAmt = -XOFFSET( TTYInfo ) ;
         break ;

      case SB_BOTTOM:
         nScrollAmt = XSCROLL( TTYInfo ) - XOFFSET( TTYInfo ) ;
         break ;

      case SB_PAGEUP:
         nScrollAmt = -XSIZE( TTYInfo ) ;
         break ;

      case SB_PAGEDOWN:
         nScrollAmt = XSIZE( TTYInfo ) ;
         break ;

      case SB_LINEUP:
         nScrollAmt = -XCHAR( TTYInfo ) ;
         break ;

      case SB_LINEDOWN:
         nScrollAmt = XCHAR( TTYInfo ) ;
         break ;

      case SB_THUMBPOSITION:
         nScrollAmt = wScrollPos - XOFFSET( TTYInfo ) ;
         break ;

      default:
         return ( FALSE ) ;
   }
   if ((XOFFSET( TTYInfo ) + nScrollAmt) > XSCROLL( TTYInfo ))
      nScrollAmt = XSCROLL( TTYInfo ) - XOFFSET( TTYInfo ) ;
   if ((XOFFSET( TTYInfo ) + nScrollAmt) < 0)
      nScrollAmt = -XOFFSET( TTYInfo ) ;
   ScrollWindowEx( hWnd, -nScrollAmt, 0, NULL, NULL, NULL, NULL, SW_INVALIDATE | SW_ERASE) ;
   XOFFSET( TTYInfo ) = XOFFSET( TTYInfo ) + nScrollAmt ;
   SetScrollPos( hWnd, SB_HORZ, XOFFSET( TTYInfo ), TRUE ) ;

   return ( TRUE ) ;

} // end of ScrollTTYHorz()

//---------------------------------------------------------------------------
//  BOOL NEAR PaintTTY( HWND hWnd )
//
//  Description:
//     Paints the rectangle determined by the paint struct of
//     the DC.
//
//  Parameters:
//     HWND hWnd
//        handle to TTY window (as always)
//
//  History:   Date       Author      Comment
//              5/ 9/91   BryanW      Wrote it.
//             10/22/91   BryanW      Problem with background color
//                                    and "off by one" fixed.
//
//              2/25/92   BryanW      Off-by-one not quite fixed...
//                                    also resolved min/max problem
//                                    for windows extended beyond
//                                    the "TTY display".
//
//             10/27/95   AllenD      Included it for MTTTY Sample.
//
//---------------------------------------------------------------------------
BOOL NEAR PaintTTY( HWND hWnd )
{
   PAINTSTRUCT  ps ;
   HFONT        hOldFont ;
   RECT         rect ;
   HDC          hDC ;
   int          nRow, nCol, nEndRow, nEndCol;
   int          nCount, nHorzPos, nVertPos ;

   hDC = BeginPaint( hWnd, &ps ) ;
   hOldFont = SelectObject( hDC, HTTYFONT( TTYInfo ) ) ;
   SetTextColor( hDC, FGCOLOR( TTYInfo ) ) ;
   SetBkColor( hDC, GetSysColor( COLOR_WINDOW ) ) ;
   rect = ps.rcPaint ;
   nRow =
      min( MAXROWS - 1,
           max( 0, (rect.top + YOFFSET( TTYInfo )) / YCHAR( TTYInfo ) ) ) ;
   nEndRow =
      min( MAXROWS - 1,
           ((rect.bottom + YOFFSET( TTYInfo ) - 1) / YCHAR( TTYInfo ) ) ) ;
   nCol =
      min( MAXCOLS - 1,
           max( 0, (rect.left + XOFFSET( TTYInfo )) / XCHAR( TTYInfo ) ) ) ;
   nEndCol =
      min( MAXCOLS - 1,
           ((rect.right + XOFFSET( TTYInfo ) - 1) / XCHAR( TTYInfo ) ) ) ;
   nCount = nEndCol - nCol + 1 ;
   for (; nRow <= nEndRow; nRow++)
   {
      nVertPos = (nRow * YCHAR( TTYInfo )) - YOFFSET( TTYInfo ) ;
      nHorzPos = (nCol * XCHAR( TTYInfo )) - XOFFSET( TTYInfo ) ;
      rect.top = nVertPos ;
      rect.bottom = nVertPos + YCHAR( TTYInfo ) ;
      rect.left = nHorzPos ;
      rect.right = nHorzPos + XCHAR( TTYInfo ) * nCount ;
      SetBkMode( hDC, OPAQUE ) ;
      ExtTextOut( hDC, nHorzPos, nVertPos, ETO_OPAQUE | ETO_CLIPPED, &rect,
                  (LPSTR)( SCREEN( TTYInfo ) + nRow * MAXCOLS + nCol ),
                  nCount, NULL ) ;
   }
   SelectObject( hDC, hOldFont ) ;
   EndPaint( hWnd, &ps ) ;
   MoveTTYCursor( hWnd ) ;
   return ( TRUE ) ;

} // end of PaintTTY()

//---------------------------------------------------------------------------
//  BOOL NEAR MoveTTYCursor( HWND hWnd )
//
//  Description:
//     Moves caret to current position.
//
//  Parameters:
//     HWND hWnd
//        handle to TTY window
//
//  History:   Date       Author      Comment
//              5/ 9/91   BryanW      Wrote it.
//             10/27/95   AllenD      Included it for MTTTY Sample.
//
//---------------------------------------------------------------------------
BOOL NEAR MoveTTYCursor( HWND hWnd )
{
   if (CONNECTED( TTYInfo ) && (CURSORSTATE( TTYInfo ) & CS_SHOW))
      SetCaretPos( (COLUMN( TTYInfo ) * XCHAR( TTYInfo )) -
                   XOFFSET( TTYInfo ),
                   (ROW( TTYInfo ) * YCHAR( TTYInfo )) -
                   YOFFSET( TTYInfo ) ) ;
   
   return ( TRUE ) ;

} // end of MoveTTYCursor()

//---------------------------------------------------------------------------
//  BOOL NEAR SetTTYFocus( HWND hWnd )
//
//  Description:
//     Sets the focus to the TTY window also creates caret.
//
//  Parameters:
//     HWND hWnd
//        handle to TTY window
//
//  History:   Date       Author      Comment
//              5/ 9/91   BryanW      Wrote it.
//             10/27/95   AllenD      Included it for MTTTY Sample.
//
//---------------------------------------------------------------------------
BOOL NEAR SetTTYFocus( HWND hWnd )
{
   if (CONNECTED(TTYInfo) && (CURSORSTATE( TTYInfo ) != CS_SHOW) )
   {
      CreateCaret( hWnd, NULL, XCHAR( TTYInfo ), YCHAR( TTYInfo ) ) ;
      ShowCaret( hWnd ) ;
      CURSORSTATE( TTYInfo ) = CS_SHOW ;
   }

   MoveTTYCursor( hWnd ) ;
   return ( TRUE ) ;

} // end of SetTTYFocus()

//---------------------------------------------------------------------------
//  BOOL NEAR KillTTYFocus( HWND hWnd )
//
//  Description:
//     Kills TTY focus and destroys the caret.
//
//  Parameters:
//     HWND hWnd
//        handle to TTY window
//
//  History:   Date       Author      Comment
//              5/ 9/91   BryanW      Wrote it.
//             10/27/95   AllenD      Included it for MTTTY Sample.
//
//---------------------------------------------------------------------------
BOOL NEAR KillTTYFocus( HWND hWnd )
{
   if (CURSORSTATE( TTYInfo ) != CS_HIDE)
   {
      HideCaret( hWnd ) ;
      DestroyCaret() ;
      CURSORSTATE( TTYInfo ) = CS_HIDE ;
   }
   return ( TRUE ) ;

} // end of KillTTYFocus()


//---------------------------------------------------------------------------
//  BOOL NEAR SizeTTY( HWND hWnd, WORD wVertSize, WORD wHorzSize )
//
//  Description:
//     Sizes TTY and sets up scrolling regions.
//
//  Parameters:
//     HWND hWnd
//        handle to TTY window
//
//     WORD wVertSize
//        new vertical size
//
//     WORD wHorzSize
//        new horizontal size
//
//  History:   Date       Author      Comment
//              5/ 8/ 91  BryanW      Wrote it
//             10/27/95   AllenD      Included it for MTTTY Sample.
//
//---------------------------------------------------------------------------
BOOL NEAR SizeTTY( HWND hWnd, WORD wWidth, WORD wHeight )
{
   int nScrollAmt ;

   //
   // adjust vert settings
   //
   YSIZE( TTYInfo ) = (int) wHeight ;
   YSCROLL( TTYInfo ) = max( 0, (MAXROWS * YCHAR( TTYInfo )) -
                               YSIZE( TTYInfo ) ) ;
   nScrollAmt = min( YSCROLL( TTYInfo ), YOFFSET( TTYInfo ) ) -
                     YOFFSET( TTYInfo ) ;
   ScrollWindow( hWnd, 0, -nScrollAmt, NULL, NULL ) ;

   YOFFSET( TTYInfo ) = YOFFSET( TTYInfo ) + nScrollAmt ;
   SetScrollPos( hWnd, SB_VERT, YOFFSET( TTYInfo ), FALSE ) ;
   SetScrollRange( hWnd, SB_VERT, 0, YSCROLL( TTYInfo ), TRUE ) ;

   //
   // adjust horz settings
   //
   XSIZE( TTYInfo ) = (int) wHeight ;
   XSCROLL( TTYInfo ) = max( 0, (MAXCOLS * XCHAR( TTYInfo )) -
                                XSIZE( TTYInfo ) ) ;
   nScrollAmt = min( XSCROLL( TTYInfo ), XOFFSET( TTYInfo )) -
                     XOFFSET( TTYInfo ) ;
   ScrollWindow( hWnd, nScrollAmt, 0, NULL, NULL );
   XOFFSET( TTYInfo ) = XOFFSET( TTYInfo ) + nScrollAmt ;
   SetScrollRange( hWnd, SB_HORZ, 0, XSCROLL( TTYInfo ), FALSE ) ;
   SetScrollPos( hWnd, SB_HORZ, XOFFSET( TTYInfo ), TRUE ) ;

   InvalidateRect( hWnd, NULL, FALSE ) ;   // redraw entire window

   return ( TRUE ) ;

} // end of SizeTTY()

/*-----------------------------------------------------------------------------

FUNCTION: TTYChildProc(HWND, UINT, WPARAM, LPARAM)

PURPOSE: Window Procedure to process message for the TTY Child Window

PARAMETERS:
    hwnd    - window handle
    message - window message
    wParam  - window message parameter (depends on message)
    lParam  - window message parameter (depends on message)

HISTORY:   Date:      Author:     Comment:
           10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
int WINAPI TTYChildProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
    switch(uMessage)
    {
        case WM_VSCROLL:
            ScrollTTYVert( hWnd, LOWORD( wParam ), HIWORD( wParam ) ) ;
            break ;

        case WM_HSCROLL:
            ScrollTTYHorz( hWnd, LOWORD( wParam ), HIWORD( wParam ) ) ;
            break ;

        case WM_SIZE:
            SizeTTY(hWnd, LOWORD(lParam), HIWORD(lParam));
            break;

        case WM_PAINT:
            PaintTTY(hWnd);
            break;

        case WM_CHAR:
            {
                //
                // keyboard activity in TTY Window 
                //
                if (CONNECTED(TTYInfo)) {

                    if (!WriterAddNewNode(WRITE_CHAR, 0, (char) wParam, NULL, NULL, NULL))
                        return FALSE;

                    if (LOCALECHO(TTYInfo))
                        OutputABufferToWindow(ghWndTTY, (CHAR *) &wParam, 1);
                }
            }
            break;

        case WM_SETFOCUS:
            SetTTYFocus( ghWndTTY ) ;
            break ;

        case WM_KILLFOCUS:
            KillTTYFocus( ghWndTTY ) ;
            break ;

        case WM_MOUSEACTIVATE:
            /*
                If mouse is clicked in me (the tty child window)
                then I need to get the focus.
            */
            SetFocus(hWnd);
            return MA_ACTIVATE;
            break;

        default:
            return DefWindowProc(hWnd, uMessage, wParam, lParam);
    }
    return 0L;
}
