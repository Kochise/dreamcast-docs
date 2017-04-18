// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993-1997  Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:   dialdlg.c
//
//  PURPOSE:   Displays the "DialDlg" dialog box
//
//  FUNCTIONS:
//    DialDlg           - Processes messages for "DialDlg" dialog box.
//    MsgDialDlgInit    - To initialize the dialdlg box and make the
//                        RasDial call.
//    MsgDialDlgEvent   - Process WM_RASDIALEVENT message.
//    MsgDialDlgCommand - Process WM_COMMAND message.
//    CmdDialDlgCancel  - Free the dialdlg box and related data.
//    RasDialFunc       - RasDial callback function for Win32.
//
//  COMMENTS:
//    Dialog box to display status of connection attempt
//
//

#include <windows.h>            // required for all Windows applications
#include <windowsx.h>
#ifdef WIN16
#include "win16ext.h"           // required only for win16 applications
#endif
#include "globals.h"            // prototypes specific to this application
#include <ras.h>
#include <raserror.h>
#include "rasutil.h"
#include "dialdlg.h"
#include "phbkdlg.h"

LRESULT MsgDialDlgInit(HWND, UINT, WPARAM, LPARAM);
LRESULT MsgDialDlgEvent(HWND, UINT, WPARAM, LPARAM);
LRESULT MsgDialDlgCommand(HWND, UINT, WPARAM, LPARAM);
LRESULT CmdDialDlgCancel(HWND, WORD, WORD, HWND);



#ifdef WIN32
VOID WINAPI RasDialFunc( UINT unMsg, RASCONNSTATE rasconnstate, DWORD dwError );
#endif

// DialDlg dialog message table definition.
MSD rgmsdDialDlg[] =
{
    {WM_RASDIALEVENT, MsgDialDlgEvent},
    {WM_COMMAND,      MsgDialDlgCommand},
    {WM_INITDIALOG,   MsgDialDlgInit}
};

MSDI msdiDialDlg =
{
    sizeof(rgmsdDialDlg) / sizeof(MSD),
    rgmsdDialDlg,
    edwpNone
};

// DialDlg dialog command table definition.
CMD rgcmdDialDlg[] =
{
    {IDCANCEL,  CmdDialDlgCancel}
};

CMDI cmdiDialDlg =
{
    sizeof(rgcmdDialDlg) / sizeof(CMD),
    rgcmdDialDlg,
    edwpNone
};

// Module specific "globals"  Used when a variable needs to be
// accessed in more than on handler function.
HRASCONN hRasConn;

#ifdef WIN32
HWND   g_hDlg;
#endif

//
//  FUNCTION: DialDlg(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for "DialDlg" dialog box.
//
//  PARAMETERS:
//    hdlg - window handle of the dialog box
//    wMessage - type of message
//    wparam - message-specific information
//    lparam - message-specific information
//
//  RETURN VALUE:
//    TRUE - message handled
//    FALSE - message not handled
//
//  COMMENTS:
//
//

LRESULT CALLBACK DialDlg(HWND hdlg, UINT uMessage, WPARAM wparam, LPARAM lparam)
{
    return DispMessage(&msdiDialDlg, hdlg, uMessage, wparam, lparam);
}


//
//  FUNCTION: MsgDialDlgInit(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: To initialize the dialdlg box and dial
//
//  PARAMETERS:
//    hwnd - The window handing the message.
//    uMessage - WM_INITDLG.
//    wparam - Message specific data (unused).
//    lparam - Message specific data (unused).
//
//  RETURN VALUE:
//    Always returns TRUE - message handled.
//
//  COMMENTS:
//    Registers window message for RAS event.
//    Makes call to RasDial with appropriate params.
//

LRESULT MsgDialDlgInit(HWND hdlg, UINT uMessage, WPARAM wparam, LPARAM lparam)
{
    RASDIALPARAMS rdParams;
    char szEntry[RAS_MaxEntryName+1];
    DWORD dwRet;
    char  szBuf[256];
    HWND  hwndEntry;
    UINT  ndx;

    hwndEntry = GetDlgItem( GetParent(hdlg), IDL_ENTRY);
    ndx = (UINT) SendMessage( hwndEntry, LB_GETCURSEL, 0,  0L );
    SendMessage( hwndEntry, LB_GETTEXT, ndx, (LPARAM)(LPSTR)szEntry );
    wsprintf( (LPSTR) szBuf, "Dialing %s...", (LPSTR) szEntry );
    SetWindowText( hdlg, (LPSTR)szBuf );

    // setup RAS Dial Parameters
    rdParams.dwSize = sizeof(RASDIALPARAMS);
    lstrcpy(rdParams.szEntryName, szEntry );
    rdParams.szPhoneNumber[0] = '\0';
    rdParams.szCallbackNumber[0] = '*';
    rdParams.szCallbackNumber[0] = '\0';

    if ( g_bUseCurrent )
    {
        rdParams.szUserName[0] = '\0';
        rdParams.szPassword[0] = '\0';
        rdParams.szDomain[0] = '*';
        rdParams.szDomain[1] = '\0';
    }
    else
    {  
        lstrcpy(rdParams.szUserName, g_szUserName );
        lstrcpy(rdParams.szPassword, g_szPassword );
        lstrcpy(rdParams.szDomain,   g_szDomain );
    }

    hRasConn = NULL;

#ifdef WIN16
    rgmsdDialDlg[0].uMessage = RegisterWindowMessage(RASDIALEVENT);
    dwRet = RasDial( NULL, NULL, &rdParams, NULL, hdlg, &hRasConn );    
#else
    g_hDlg = hdlg;
    dwRet = RasDial( NULL, NULL, &rdParams, 0L, (RASDIALFUNC) RasDialFunc, &hRasConn );
#endif

    if ( dwRet )
    {
        if ( RasGetErrorString( (UINT)dwRet, (LPSTR)szBuf, 256 ) != 0 )
            wsprintf( (LPSTR)szBuf, "Undefined RAS Dial Error (%ld).", dwRet );

        MessageBox(hdlg, (LPSTR)szBuf, szAppName, MB_OK | MB_ICONSTOP );
        EndDialog(hdlg, FALSE);
        return TRUE;
    }
    // Center the dialog over the application window
    CenterWindow(hdlg, GetWindow(hdlg, GW_OWNER));

    return TRUE;
}

//
//  FUNCTION: MsgDialDlgEvent(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: To display messages during dialdlg
//
//  PARAMETERS:
//    hwnd - The window handing the message.
//    uMessage - WM_RASDIALEVENT.
//    wparam - Message specific data (unused).
//    lparam - Message specific data (unused).
//
//  RETURN VALUE:
//    Always returns TRUE - message handled.
//
//  COMMENTS:
//    Updates the text of IDT_MESSAGE to indicate the current
//    state in the connection.  The dialog is closed upon
//    connect or disconnect status.
//

LRESULT MsgDialDlgEvent(HWND hdlg, UINT uMessage, WPARAM wparam, LPARAM lparam)
{
    char szMessage[256];
        
    LoadString(hInst, GetRasConnState( (RASCONNSTATE) wparam ), szMessage, 64 );
    SetDlgItemText( hdlg, IDT_MESSAGE, (LPCSTR) szMessage );
                      
    if ( lparam )  // error occurred
    {
        if ( RasGetErrorString( (UINT)lparam, szMessage, 256 ) != 0 )
            wsprintf( (LPSTR)szMessage, "Undefined RAS Dial Error." );

        MessageBox(hdlg, (LPSTR)szMessage, szAppName, MB_OK | MB_ICONSTOP );
        PostMessage( hdlg, WM_COMMAND, (WPARAM) IDCANCEL, 0L );
    }                                                                                                               
    else if ( RASCS_DONE & wparam )
    {
        EndDialog(hdlg, TRUE);          // Exit the dialog
    }

    return TRUE;
}

//
//  FUNCTION: MsgDialDlgCommand(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Process WM_COMMAND message sent to the dialdlg box.
//
//  PARAMETERS:
//    hwnd - The window handing the message.
//    uMessage - The message number. (unused).
//    wparam - Message specific data (unused).
//    lparam - Message specific data (unused).
//
//  RETURN VALUE:
//    Always returns TRUE - message handled.
//
//  COMMENTS:
//    Uses this DispCommand function defined in wndproc.c combined
//    with the cmdiDialDlg structure defined in this file to handle
//    the command messages for the dialdlg dialog box.
//

LRESULT MsgDialDlgCommand(HWND   hwnd, 
                        UINT   uMessage, 
                        WPARAM wparam, 
                        LPARAM lparam)
{
    return DispCommand(&cmdiDialDlg, hwnd, wparam, lparam);
}

//
//  FUNCTION: CmdDialDlgCancel(HWND, WORD, WORD,  HWND)
//
//  PURPOSE: Free the dialdlg box and related data.
//
//  PARAMETERS:
//    hwnd - The window handling the command.
//    wCommand - IDCANCEL.
//    wNotify - The notification to be handled (unused).
//    hwndCtrl - NULL (unused).
//
//  RETURN VALUE:
//    Always returns TRUE.
//
//  COMMENTS:    
//    Closes current connection attempt and calls EndDialog
//    to finish the dialog session.
//

LRESULT CmdDialDlgCancel(HWND hdlg, WORD wCommand, WORD wNotify, HWND hwndCtrl)
{
    RasHangUp( hRasConn );
    EndDialog(hdlg, FALSE);          // Exit the dialog
    return TRUE;
}


#ifdef WIN32
//  FUNCTION: RasDialFunc( UINT, RASCONNSTATE, DWORD )
//
//  PURPOSE: Called by RasDial, passes params onto dialog box
//
//  PARAMETERS:
//    unMsg        - Yype of RAS event that occurred.
//    rasconnstate - Connection state about to be entered. 
//    dwError      - Error code that may have occurred.
//
//  COMMENTS:
//    appropriate action is taken in the WM_RASDIALMESSAGE handler

VOID WINAPI RasDialFunc( UINT unMsg, RASCONNSTATE rasconnstate, DWORD dwError )
{
    PostMessage( g_hDlg,
                 rgmsdDialDlg[0].uMessage,
                 (WPARAM) rasconnstate,
                 (LPARAM) dwError );

}

#endif
