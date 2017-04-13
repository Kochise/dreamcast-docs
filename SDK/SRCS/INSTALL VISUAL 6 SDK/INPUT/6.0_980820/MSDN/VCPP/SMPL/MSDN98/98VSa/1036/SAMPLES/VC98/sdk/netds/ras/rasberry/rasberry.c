// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993-1997  Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:   rasberry.c
//
//  PURPOSE:  Implement the windows procedure for the main application
//            windows.  
//
//  FUNCTIONS:
//    WndProc      - Processes messages for the main window.
//    MsgCreate    - Handle the WM_CREATE messages for the main window.
//    MsgSize      - Handle the WM_SIZE messages for the main window.
//    MsgCommand   - Handle the WM_COMMAND messages for the main window.
//    MsgDestroy   - Handles the WM_DESTROY message by calling 
//                   PostQuitMessage().
//    CmdPhbkDlg   - Displays entries in default phonebook.
//    CmdStatDlg   - Displays status of the selected connection.
//    CmdRefresh   - Refreshes list of connections in listbox.         
//    CmdHangup    - Hangs up the selected connection.
//    CmdConnNotify- Handles notification messages for connection listbox.
//    CmdExit      - Handles the file exit command by calling destory 
//                   window on the main window.
//
//  COMMENTS:
//
//

#include <windows.h>            // required for all Windows applications
#include <windowsx.h>
#ifdef WIN16
#include "win16ext.h"           // required only for win16 applications
#endif

#include "globals.h"            // prototypes specific to this application
#include <stdlib.h>
#include <malloc.h>
#include <ras.h>
#include <raserror.h>
#include "rasutil.h"
#include "phbkdlg.h"
#include "statdlg.h"

// Main window message table definition.
MSD rgmsd[] =
{
    {WM_CREATE,   MsgCreate},
    {WM_SIZE,     MsgSize},
    {WM_COMMAND,  MsgCommand},
    {WM_DESTROY,  MsgDestroy}
};

MSDI msdiMain =
{
    sizeof(rgmsd) / sizeof(MSD),
    rgmsd,
    edwpWindow
};


// Main window command table definition.
CMD rgcmd[] =
{
    {IDM_PHONEBOOK, CmdPhbkDlg},
    {IDM_STATUS,    CmdStatDlg},
    {IDM_EXIT,      CmdExit},
    {IDM_REFRESH,   CmdRefresh},
    {IDM_HANGUP,    CmdHangUp},
    {IDM_ABOUT,     CmdAbout},
    {IDL_CONN,      CmdConnNotify}
};

CMDI cmdiMain =
{
    sizeof(rgcmd) / sizeof(CMD),
    rgcmd,
    edwpWindow
};

// Application "globals"
char g_szUserName[UNLEN+1];
char g_szPassword[PWLEN+1];
char g_szDomain[DNLEN+1];

LPHRASCONN g_lphRasConn = NULL;

// Module specific "globals"  Used when a variable needs to be
// accessed in more than on handler function.

HWND hwndConn;  // handle of listbox of connections

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  PARAMETERS:
//    hwnd     - window handle
//    uMessage - message number
//    wparam   - additional information (dependant on message number)
//    lparam   - additional information (dependant on message number)
//
//  RETURN VALUE:
//    The return value depends on the message number.  If the message
//    is implemented in the message dispatch table, the return value is
//    the value returned by the message handling function.  Otherwise,
//    the return value is the value returned by the default window procedure.
//
//  COMMENTS:
//    Call the DispMessage() function with the main window's message dispatch
//    information (msdiMain) and the message specific information.
//

LRESULT CALLBACK WndProc(HWND   hwnd, 
                         UINT   uMessage, 
                         WPARAM wparam, 
                         LPARAM lparam)
{
    return DispMessage(&msdiMain, hwnd, uMessage, wparam, lparam);
}


//
//  FUNCTION: MsgCreate(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Initialized main window
//
//  PARAMETERS:
//
//    hwnd      - Window handle
//    uMessage  - Message number (Unused)
//    wparam    - Extra data     (Unused)
//    lparam    - Extra data     (Unused)
//
//  RETURN VALUE:
//
//    Always returns 0 - Message handled
//
//  COMMENTS:
//    Creates a listbox the size of the window and fills it
//    with a list of RAS connections.  
//

LRESULT MsgCreate(HWND hwnd, UINT uMessage, WPARAM wparam, LPARAM lparam)
{
    RECT rc;
    
    GetClientRect( hwnd, &rc );
    
    hwndConn  = CreateWindow( "LISTBOX",
                             "Connections",
                             WS_CHILD | WS_VISIBLE | WS_HSCROLL |
                             WS_VSCROLL | LBS_USETABSTOPS | LBS_NOINTEGRALHEIGHT | LBS_SORT,
                             0,   
                             0,
                             rc.right,
                             rc.bottom,
                             hwnd,
                             (HMENU) IDL_CONN,
                             hInst,
                             NULL );

    SendMessage( hwnd, WM_COMMAND, IDM_REFRESH, 0L );

    // initialize global variables   
    g_szUserName[0] = '\0';
    g_szPassword[0] = '\0';
    g_szDomain[0] = '*';
    g_szDomain[1] = '\0';
    
    return 0;
}


//
//  FUNCTION: MsgSize(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Resize listbox to client area size
//
//  PARAMETERS:
//
//    hwnd      - Window handle
//    uMessage  - Message number (Unused)
//    wparam    - Extra data     (Unused)
//    lparam    - Extra data     (Unused)
//
//  RETURN VALUE:
//
//    Always returns 0 - Message handled
//
//  COMMENTS:
//
//

LRESULT MsgSize(HWND hwnd, UINT uMessage, WPARAM wparam, LPARAM lparam)
{
    MoveWindow(hwndConn, 0, 0, LOWORD(lparam), HIWORD(lparam), TRUE);
    return 0;
}



//
//  FUNCTION: MsgCommand(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Handle the WM_COMMAND messages for the main window.
//
//  PARAMETERS:
//    hwnd     - window handle
//    uMessage - WM_COMMAND (Unused)
//    GET_WM_COMMAND_ID(wparam, lparam)   - Command identifier
//    GET_WM_COMMAND_HWND(wparam, lparam) - Control handle
//
//  RETURN VALUE:
//    The return value depends on the message number.  If the message
//    is implemented in the message dispatch table, the return value is
//    the value returned by the message handling function.  Otherwise,
//    the return value is the value returned by the default window procedure.
//
//  COMMENTS:
//    Call the DispCommand() function with the main window's command dispatch
//    information (cmdiMain) and the command specific information.
//

LRESULT MsgCommand(HWND hwnd, UINT uMessage, WPARAM wparam, LPARAM lparam)
{
    return DispCommand(&cmdiMain, hwnd, wparam, lparam);
}


//
//  FUNCTION: MsgDestroy(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Calls PostQuitMessage().
//
//  PARAMETERS:
//
//    hwnd      - Window handle  (Unused)
//    uMessage  - Message number (Unused)
//    wparam    - Extra data     (Unused)
//    lparam    - Extra data     (Unused)
//
//  RETURN VALUE:
//
//    Always returns 0 - Message handled
//
//  COMMENTS:
//
//

LRESULT MsgDestroy(HWND hwnd, UINT uMessage, WPARAM wparam, LPARAM lparam)
{
    if ( g_lphRasConn != NULL )
    {
        _ffree((LPVOID) g_lphRasConn );
        g_lphRasConn = NULL;
    }

    PostQuitMessage(0);
#ifdef WIN32
    Sleep(3000);  // let RAS state machine clean up
#endif
    return 0;
}



//
//  FUNCTION: CmdPhbkDlg(HWND, WORD, WORD, HWND)
//
//  PURPOSE: Displays the "PhbkDlg" dialog box
//
//  PARAMETERS:
//    hwnd      - Window handle
//    wCommand  - IDM_ENTRY (unused)
//    wNotify   - Notification number (unused)
//    hwndCtrl  - NULL (unused)
//
//  RETURN VALUE:
//
//    Always returns 0 - Message handled
//
//  COMMENTS:
//    To process the IDM_ENTRY message, call DialogBox() to display the
//    phbkdlg dialog box.

LRESULT CmdPhbkDlg(HWND hwnd, WORD wCommand, WORD wNotify, HWND hwndCtrl)
{
    DialogBox(hInst, "PhbkDlgBox", hwnd, (DLGPROC)PhbkDlg);
    SendMessage( hwnd, WM_COMMAND, IDM_REFRESH, 0L );

    return 0;
}

//
//  FUNCTION: CmdStatDlg(HWND, WORD, WORD, HWND)
//
//  PURPOSE: Displays the "StatDlg" dialog box
//
//  PARAMETERS:
//    hwnd      - Window handle
//    wCommand  - IDM_STATDLG (unused)
//    wNotify   - Notification number (unused)
//    hwndCtrl  - NULL (unused)
//
//  RETURN VALUE:
//
//    Always returns 0 - Message handled
//
//  COMMENTS:
//    To process the IDM_STATDLG message, call DialogBox() to display the
//    statdlg dialog box.

LRESULT CmdStatDlg(HWND hwnd, WORD wCommand, WORD wNotify, HWND hwndCtrl)
{
    DialogBox(hInst, "StatDlgBox", hwnd, (DLGPROC)StatDlg);
    SendMessage( hwnd, WM_COMMAND, IDM_REFRESH, 0L );
    return 0;
}



//
//  FUNCTION: CmdRefesh(HWND, WORD, WORD, HWND)
//
//  PURPOSE: Refreshes the connection list
//
//  PARAMETERS:
//    hwnd     - The window.
//    wCommand - IDM_REFRESH (unused)
//    wNotify  - Notification number (unused)
//    hwndCtrl - NULL (unused)
//
//  RETURN VALUE:
//    Always returns 0 - command handled.
//
//  COMMENTS:
//     Calls RasEnumConnections to get a list of current connections
//

LRESULT CmdRefresh(HWND hwnd, WORD wCommand, WORD wNotify, HWND hwndCtrl)
{
    LPRASCONN  lpRasConn = NULL;
    LPRASCONN  lpTemp = NULL;
    LPHRASCONN lphTemp = NULL;
    DWORD cbBuf = 0;
    DWORD cConn = 0;
    DWORD dwRet = 0;
    UINT  ndx;
    char  szMessage[256];
    HMENU hmenu = GetMenu( hwnd );

    // remove any connections currently in listbox                                 
    SendMessage( hwndConn, LB_RESETCONTENT, 0, 0L );

    if ( g_lphRasConn != NULL )
    {
        _ffree( (LPVOID) g_lphRasConn );
        g_lphRasConn = NULL;
    }

    // enumerate connections
    cbBuf = sizeof(RASCONN);
    if ( ((lpRasConn = ( LPRASCONN ) _fmalloc((UINT)cbBuf)) != NULL ) &&
         ((g_lphRasConn = ( LPHRASCONN ) _fmalloc(sizeof(HRASCONN))) != NULL ) )
    {            
        lpRasConn->dwSize = sizeof( RASCONN );                      
        dwRet = RasEnumConnections( lpRasConn, &cbBuf, &cConn );
        if ( dwRet == ERROR_BUFFER_TOO_SMALL )
        {
            if ( (lpTemp = ( LPRASCONN ) _frealloc(lpRasConn, (UINT)cbBuf) ) != NULL )
            {
                lpRasConn = lpTemp;
                dwRet = RasEnumConnections( lpRasConn, &cbBuf, &cConn );
                
                if ( NULL != (lphTemp = ( LPHRASCONN )
                              _frealloc((LPVOID)g_lphRasConn, (UINT)(sizeof(HRASCONN)*cConn))) )
                    g_lphRasConn = lphTemp;
                else
                    dwRet = ERROR_NOT_ENOUGH_MEMORY;

            }
            else
            {
                dwRet = ERROR_NOT_ENOUGH_MEMORY;
            }
        }
        else if ( dwRet != 0 ) // other error
        {
            if ( RasGetErrorString( (UINT)dwRet, szMessage, 256 ) != 0 )
                wsprintf( (LPSTR)szMessage, (LPSTR)"Undefined RAS Dial Error." );

            MessageBox(hwnd, szMessage, szAppName, MB_OK | MB_ICONSTOP );                            
        }

        if ( dwRet == 0 )  // No errors, so populate listbox
        {
            for ( ndx = 0; ndx < cConn; ndx++ ) 
            {
                g_lphRasConn[ndx] = lpRasConn[ndx].hrasconn;
                SendMessage( hwndConn,
                             LB_ADDSTRING,
                             0,
                             (LPARAM)(LPCSTR) lpRasConn[ndx].szEntryName);
            }

            // update states of menu items
            if ( ndx > 0 ) // at least one item was added
            {             
                SendMessage( hwndConn, LB_SETCURSEL, 0, 1L );
                EnableMenuItem( hmenu, IDM_STATUS, MF_ENABLED );
                EnableMenuItem( hmenu, IDM_HANGUP, MF_ENABLED );
            }
            else 
            {
                EnableMenuItem( hmenu, IDM_STATUS, MF_GRAYED );
                EnableMenuItem( hmenu, IDM_HANGUP, MF_GRAYED );
            }
        }
        else
        {
            EnableMenuItem( hmenu, IDM_STATUS, MF_GRAYED );
            EnableMenuItem( hmenu, IDM_HANGUP, MF_GRAYED );
        }

        _ffree( lpRasConn );
    }
    else
    {
        if ( g_lphRasConn != NULL )
        {
            _ffree((LPVOID) g_lphRasConn );
            g_lphRasConn = NULL;
        }

        if ( lpRasConn != NULL )
        {
            _ffree( lpRasConn );
        }
    }                


    return 0;
}

//
//  FUNCTION: CmdHangUp(HWND, WORD, WORD, HWND)
//
//  PURPOSE: Hangs up the selected connection
//
//  PARAMETERS:
//    hwnd     - The window.
//    wCommand - IDM_HANGUP (unused)
//    wNotify  - Notification number (unused)
//    hwndCtrl - NULL (unused)
//
//  RETURN VALUE:
//    Always returns 0 - command handled.
//
//  COMMENTS:
//
//

LRESULT CmdHangUp(HWND hwnd, WORD wCommand, WORD wNotify, HWND hwndCtrl)
{
    CHAR  szBuf[256];
    CHAR  szBuf2[256];
    UINT  ndx;

    // get the connection text from previous window
    ndx = (UINT) SendMessage( hwndConn, LB_GETCURSEL, 0,  0L );
    SendMessage( hwndConn, LB_GETTEXT, ndx, (LPARAM)(LPSTR)szBuf );

    wsprintf( (LPSTR) szBuf2, "HangUp %s?", (LPSTR) szBuf );
    if ( IDYES == MessageBox( hwnd, (LPSTR)szBuf2, szAppName, MB_ICONQUESTION | MB_YESNO ) )
    {
        RasHangUp( g_lphRasConn[ndx] );

        SendMessage( hwnd, WM_COMMAND, IDM_REFRESH, 0L );
    }
    return 0;
}

//
//  FUNCTION: CmdConnNotify(HWND, WORD, WORD, HWND)
//
//  PURPOSE: notfication from Connection Listbox
//
//  PARAMETERS:
//    hwnd - The window handling the command.
//    wCommand - The command to be handled (unused).
//    wNotify  - The notification code to be handled (LBN_DBLCLK).
//    hwndCtrl - NULL (unused).
//
//  RETURN VALUE:
//    0 if message is processed.
//
//  COMMENTS:
//    Catches DBL_CLK to cause connection status dialog to appear
//

LRESULT CmdConnNotify(HWND hwnd, WORD wCommand, WORD wNotify, HWND hwndCtrl)
{
    if ( wNotify == LBN_DBLCLK )
    {
        SendMessage( hwnd, WM_COMMAND, IDM_STATUS, 0 );
        return 0;
    }
    return 1;
}

//
//  FUNCTION: CmdExit(HWND, WORD, WORD, HWND)
//
//  PURPOSE: Exit the application.
//
//  PARAMETERS:
//    hwnd     - The window.
//    wCommand - IDM_EXIT
//    wNotify  - Notification number (unused)
//    hwndCtrl - NULL (unused)
//
//  RETURN VALUE:
//    Always returns 0 - command handled.
//
//  COMMENTS:
//
//

LRESULT CmdExit(HWND hwnd, WORD wCommand, WORD wNotify, HWND hwndCtrl)
{
    DestroyWindow(hwnd);
    return 0;
}
