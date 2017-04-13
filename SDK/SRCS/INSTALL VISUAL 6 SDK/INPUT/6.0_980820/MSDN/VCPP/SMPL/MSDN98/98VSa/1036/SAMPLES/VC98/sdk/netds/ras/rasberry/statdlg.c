// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993-1997  Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:   statdlg.c
//
//  PURPOSE:   Displays the "StatDlg" dialog box
//
//  FUNCTIONS:
//    StatDlg           - Processes messages for "StatDlg" dialog box.
//    MsgStatDlgInit    - To initialize the statdlg box.
//    MsgStatDlgCommand - Process WM_COMMAND message sent to the statdlg box.
//    CmdStatDlgRefresh - Display the connection status.
//    CmdStatDlgOK      - Free the statdlg box and related data.
//
//  COMMENTS:
//    Dialog box to display the status of the selected connection
//

#include <windows.h>            // required for all Windows applications
#include <windowsx.h>

#ifdef WIN16
#include "win16ext.h"           // required only for win16 applications
#endif

#include "globals.h"            // prototypes specific to this application
#include <stdlib.h>
#include <ras.h>
#include <raserror.h>
#include "rasutil.h"
#include "statdlg.h"

LRESULT MsgStatDlgInit(HWND, UINT, WPARAM, LPARAM);
LRESULT MsgStatDlgCommand(HWND, UINT, WPARAM, LPARAM);
LRESULT CmdStatDlgRefresh(HWND, WORD, WORD, HWND);
LRESULT CmdStatDlgOK(HWND, WORD, WORD, HWND);

// StatDlg dialog message table definition.
MSD rgmsdStatDlg[] =
{
    {WM_COMMAND,    MsgStatDlgCommand},
    {WM_INITDIALOG, MsgStatDlgInit}
};

MSDI msdiStatDlg =
{
    sizeof(rgmsdStatDlg) / sizeof(MSD),
    rgmsdStatDlg,
    edwpNone
};

// StatDlg dialog command table definition.
CMD rgcmdStatDlg[] =
{
    {IDB_REFRESH, CmdStatDlgRefresh},
    {IDOK,        CmdStatDlgOK}
};

CMDI cmdiStatDlg =
{
    sizeof(rgcmdStatDlg) / sizeof(CMD),
    rgcmdStatDlg,
    edwpNone
};

// Module specific "globals"  Used when a variable needs to be
// accessed in more than on handler function.


//
//  FUNCTION: StatDlg(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for "StatDlg" dialog box.
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
//    Dispatch messages
//

LRESULT CALLBACK StatDlg(HWND hdlg, UINT uMessage, WPARAM wparam, LPARAM lparam)
{
    return DispMessage(&msdiStatDlg, hdlg, uMessage, wparam, lparam);
}


//
//  FUNCTION: MsgStatDlgInit(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: To initialize the statdlg box.
//
//  PARAMETERS:
//    hwnd - The window handing the message.
//    uMessage - The message number. WM_INITDLG.
//    wparam - Message specific data (unused).
//    lparam - Message specific data (unused).
//
//  RETURN VALUE:
//    Always returns 0 - message handled.
//
//  COMMENTS:
//

LRESULT MsgStatDlgInit(HWND hdlg, UINT uMessage, WPARAM wparam, LPARAM lparam)
{
    // Center the dialog over the application window
    CenterWindow(hdlg, GetWindow(hdlg, GW_OWNER));

    SendMessage(hdlg, WM_COMMAND, (WPARAM) IDB_REFRESH, 0L );

    return TRUE;
}

//
//  FUNCTION: MsgStatDlgCommand(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Process WM_COMMAND message sent to the statdlg box.
//
//  PARAMETERS:
//    hwnd - The window handing the message.
//    uMessage - The message number. WM_COMMAND.
//    wparam - Message specific data (unused).
//    lparam - Message specific data (unused).
//
//  RETURN VALUE:
//    TRUE for message handled.
//    FALSE for message not handled.
//
//  COMMENTS:
//    Uses this DispCommand function defined in wndproc.c combined
//    with the cmdiStatDlg structure defined in this file to handle
//    the command messages for the statdlg dialog box.
//

LRESULT MsgStatDlgCommand(HWND   hwnd, 
                        UINT   uMessage, 
                        WPARAM wparam, 
                        LPARAM lparam)
{
    return DispCommand(&cmdiStatDlg, hwnd, wparam, lparam);
}

//
//  FUNCTION: CmdStatDlgRefresh(HWND, WORD, WORD, HWND)
//
//  PURPOSE: Refresh the information displayed in the dialog box.
//
//  PARAMETERS:
//    hwnd - The window handling the command.
//    wCommand - The command to be handled IDB_REFRESH.
//    wNotify  - The notifcation message (unused).
//    hwndCtrl - NULL (unused).
//
//  RETURN VALUE:
//    Always returns TRUE.
//
//  COMMENTS:
//    Calls RasGetConnectStatus to populate dialog box.
//

LRESULT CmdStatDlgRefresh(HWND hdlg, WORD wCommand, WORD wNotify, HWND hwndCtrl)
{
    HRASCONN hrasconn;
    RASCONNSTATUS rasStatus;
    DWORD dwRet;
    CHAR  szBuf[256];
    HWND  hwndConn;
    UINT  ndx;

    // get the connection text from previous window
    hwndConn = GetDlgItem( GetParent(hdlg), IDL_CONN);
    ndx = (UINT) SendMessage( hwndConn, LB_GETCURSEL, 0,  0L );
    SendMessage( hwndConn, LB_GETTEXT, ndx, (LPARAM)(LPSTR)szBuf );
    SetDlgItemText(hdlg, IDE_CONNECTION, (LPSTR)szBuf );

    // get to HRASCONN
    hrasconn = g_lphRasConn[ndx];
       
    // get connection status
    rasStatus.dwSize = sizeof(RASCONNSTATUS);
    dwRet = RasGetConnectStatus( hrasconn, &rasStatus );
    if ( dwRet )
    {
        if ( RasGetErrorString( (UINT)dwRet, (LPSTR)szBuf, 256 ) != 0 )
            wsprintf( (LPSTR)szBuf, "Undefined RAS Connect Status Error (%ld).", dwRet );

        MessageBox(hdlg, (LPSTR)szBuf, szAppName, MB_OK | MB_ICONSTOP );
        EndDialog(hdlg, FALSE);
        return TRUE;
    }
    else 
    {
        LoadString( hInst,
                    GetRasConnState( rasStatus.rasconnstate ),
                    (LPSTR)szBuf,
                    256 );
        SetDlgItemText(hdlg, IDE_STATUS, (LPSTR)szBuf);

        if ( rasStatus.dwError ) // there is an error
        {
            if ( RasGetErrorString( (UINT)rasStatus.dwError, (LPSTR)szBuf, 256 ) != 0 )
                wsprintf( (LPSTR)szBuf, "Undefined Connection Error (%ld).", rasStatus.dwError );
        }
        else
        {
            wsprintf( (LPSTR)szBuf, "No Error" );
        }
        SetDlgItemText(hdlg, IDE_ERROR, (LPSTR)szBuf);

        SetDlgItemText(hdlg, IDE_DEVICE, rasStatus.szDeviceName);

        SetDlgItemText(hdlg, IDE_TYPE, rasStatus.szDeviceType);

    }

    return TRUE;
}

//
//  FUNCTION: CmdStatDlgOK(HWND, WORD, HWND)
//
//  PURPOSE: Free the statdlg box and related data.
//
//  PARAMETERS:
//    hwnd - The window handling the command.
//    wCommand - The command to be handled (unused).
//    wNotify  - The notifcation message (unused).
//    hwndCtrl - NULL (unused).
//
//  RETURN VALUE:
//    Always returns TRUE.
//
//  COMMENTS:
//    Calls EndDialog to finish the dialog session.
//

LRESULT CmdStatDlgOK(HWND hdlg, WORD wCommand, WORD wNotify, HWND hwndCtrl)
{
    EndDialog(hdlg, TRUE);          // Exit the dialog
    return TRUE;
}
