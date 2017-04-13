// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993-1997  Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:   phbkdlg.c
//
//  PURPOSE:   Displays the "Phonebox Entries" dialog box
//
//  FUNCTIONS:
//    PhbkDlg           - Processes messages for "PhbkDlg" dialog box.
//    MsgPhbkDlgInit    - To initialize the phbkdlg box with version info
//                      from resources.
//    MsgPhbkDlgCommand - Process WM_COMMAND message sent to the phbkdlg box.
//    CmdPhbkDlgCancel  - Free the phbkdlg box and related data.
//    CmdPhbkDlgEntry   - Process LBN_DBLCLK for the entry list box
//    CmdPhbkDlgDial    - Calls AUTHDLG and/or DIALDLG boxes.
//
//  COMMENTS:
//    Displays and allow user to dial an entry from the default phonebook
//
//

#include <windows.h>            // required for all Windows applications
#include <windowsx.h>
#ifdef WIN16
#include "win16ext.h"           // required only for win16 applications
#endif
#include "globals.h"            // prototypes specific to this application
#include <malloc.h>
#include <ras.h>
#include <raserror.h>
#include "phbkdlg.h"
#include "dialdlg.h"
#include "authdlg.h"

LRESULT MsgPhbkDlgInit(HWND, UINT, WPARAM, LPARAM);
LRESULT MsgPhbkDlgCommand(HWND, UINT, WPARAM, LPARAM);
LRESULT CmdPhbkDlgCancel(HWND, WORD, WORD, HWND);
LRESULT CmdPhbkDlgEntry(HWND, WORD, WORD, HWND);
LRESULT CmdPhbkDlgDial(HWND, WORD, WORD, HWND);

 
// PhbkDlg dialog message table definition.
MSD rgmsdPhbkDlg[] =
{
    {WM_COMMAND,    MsgPhbkDlgCommand},
    {WM_INITDIALOG, MsgPhbkDlgInit}
};

MSDI msdiPhbkDlg =
{
    sizeof(rgmsdPhbkDlg) / sizeof(MSD),
    rgmsdPhbkDlg,
    edwpNone
};

// PhbkDlg dialog command table definition.
CMD rgcmdPhbkDlg[] =
{
    {IDB_DIAL,  CmdPhbkDlgDial},
    {IDCANCEL,  CmdPhbkDlgCancel},
    {IDL_ENTRY, CmdPhbkDlgEntry}
};

CMDI cmdiPhbkDlg =
{
    sizeof(rgcmdPhbkDlg) / sizeof(CMD),
    rgcmdPhbkDlg,
    edwpNone
};

// Module specific "globals"  Used when a variable needs to be
// accessed in more than on handler function.

#ifdef WIN16                     // for Win16 we require that the user
    BOOL g_bUseCurrent = FALSE;  // always enters username and password
#else
    BOOL g_bUseCurrent = TRUE;
#endif

//
//  FUNCTION: PhbkDlg(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for "PhbkDlg" dialog box.
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
//    Dispatches messages for dialog box
//

LRESULT CALLBACK PhbkDlg(HWND hdlg, UINT uMessage, WPARAM wparam, LPARAM lparam)
{
    return DispMessage(&msdiPhbkDlg, hdlg, uMessage, wparam, lparam);
}


//
//  FUNCTION: MsgPhbkDlgInit(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: To initialize the phbkdlg box.
//
//  PARAMETERS:
//    hwnd - The window handing the message.
//    uMessage - The message number. WM_INITDIALOG.
//    wparam - Message specific data (unused).
//    lparam - Message specific data (unused).
//
//  RETURN VALUE:
//    Always returns TRUE - message handled.
//
//  COMMENTS:
//    Displays default phone book by calling RasEnumEntries
//

LRESULT MsgPhbkDlgInit(HWND hdlg, UINT uMessage, WPARAM wparam, LPARAM lparam)
{
    LPRASENTRYNAME lpRasEntry;
    LPRASENTRYNAME lpTemp;
    DWORD cbBuf;
    DWORD cEntry;
    DWORD dwRet;
    UINT  ndx;
    char  szMessage[256];

    cbBuf = sizeof(RASENTRYNAME);
    if ((lpRasEntry = ( LPRASENTRYNAME ) _fmalloc((UINT)cbBuf)) != NULL ) 
    {
        lpRasEntry->dwSize = sizeof(RASENTRYNAME);
        dwRet = RasEnumEntries( NULL, NULL, lpRasEntry, &cbBuf, &cEntry );
        if ( dwRet == ERROR_BUFFER_TOO_SMALL )
        {
            if ((lpTemp = ( LPRASENTRYNAME ) _frealloc ( lpRasEntry, (UINT)cbBuf )) != NULL )
            {
                lpRasEntry = lpTemp;
                dwRet = RasEnumEntries( NULL, NULL, lpRasEntry, &cbBuf, &cEntry );
            }
            else
            {
                dwRet = ERROR_NOT_ENOUGH_MEMORY;
            }
        }
        else if ( dwRet != 0 ) // other error
        {
            if ( RasGetErrorString( (UINT)dwRet, szMessage, 256 ) != 0 )
                wsprintf( (LPSTR)szMessage, "Undefined RasEnumEntries Error." );

            MessageBox(hdlg, (LPSTR)szMessage, szAppName, MB_OK | MB_ICONSTOP );
        }

        if ( dwRet == 0 )  // No errors
        {
            for ( ndx = 0; ndx < cEntry; ndx++ ) 
                SendDlgItemMessage( hdlg,
                                    IDL_ENTRY,
                                    LB_ADDSTRING,
                                    0,
                                    (LPARAM)(LPCSTR) lpRasEntry[ndx].szEntryName);

            if ( ndx > 0 ) // at least one item was added
            {
                SendDlgItemMessage( hdlg, IDL_ENTRY, LB_SETCURSEL, 0, 1L );
                EnableWindow( GetDlgItem( hdlg, IDB_DIAL ), TRUE );
            }
        }

        _ffree( lpRasEntry );
    } 
    
#ifdef WIN16
    // for Win16, we require that the user enters their username
    ShowWindow( GetDlgItem( hdlg, IDC_USECURRENT ), SW_HIDE );
#endif

    CheckDlgButton( hdlg, IDC_USECURRENT, g_bUseCurrent );

    // Center the dialog over the application window
    CenterWindow(hdlg, GetWindow(hdlg, GW_OWNER));

    return TRUE;
}

//
//  FUNCTION: MsgPhbkDlgCommand(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Process WM_COMMAND message sent to the phbkdlg box.
//
//  PARAMETERS:
//    hwnd - The window handing the message.
//    uMessage - The message number. WM_COMMAND.
//    wparam - Message specific data (unused).
//    lparam - Message specific data (unused).
//
//  RETURN VALUE:
//    TRUE for message handled
//    FALSE for message not handled
//
//  COMMENTS:
//    Uses this DispCommand function defined in wndproc.c combined
//    with the cmdiPhbkDlg structure defined in this file to handle
//    the command messages for the phbkdlg dialog box.
//

LRESULT MsgPhbkDlgCommand(HWND   hwnd, 
                          UINT   uMessage,
                          WPARAM wparam,
                          LPARAM lparam)
{
    return DispCommand(&cmdiPhbkDlg, hwnd, wparam, lparam);
}

//
//  FUNCTION: CmdPhbkDlgCancel(HWND, WORD, WORD, HWND)
//
//  PURPOSE: Free the phbkdlg box and related data.
//
//  PARAMETERS:
//    hwnd - The window handling the command.
//    wCommand - The command to be handled IDCANCEL.
//    wNotify  - The notification code to be handled (unused).
//    hwndCtrl - NULL (unused).
//
//  RETURN VALUE:
//    Always returns TRUE.
//
//  COMMENTS:
//    Calls EndDialog to finish the dialog session.
//

LRESULT CmdPhbkDlgCancel(HWND hdlg, WORD wCommand, WORD wNotify, HWND hwndCtrl)
{
    // save the state of the check box
    g_bUseCurrent = IsDlgButtonChecked( hdlg, IDC_USECURRENT );
    EndDialog(hdlg, FALSE);          // Exit the dialog
    return TRUE;
}


//
//  FUNCTION: CmdPhbkDlgEntry(HWND, WORD, WORD, HWND)
//
//  PURPOSE: Dial selected phonebook phbkdlg
//
//  PARAMETERS:
//    hwnd - The window handling the command.
//    wCommand - The command to be handled IDL_ENTRY.
//    wNotify  - The notification code to be handled LBN_DBLCLK.
//    hwndCtrl - NULL (unused).
//
//  RETURN VALUE:
//    TRUE if message is processed.
//
//  COMMENTS:
//    Double click on an entry signifies a dial command.
//

LRESULT CmdPhbkDlgEntry(HWND hdlg, WORD wCommand, WORD wNotify, HWND hwndCtrl)
{
    if ( wNotify == LBN_DBLCLK )
    {
        SendMessage( hdlg, WM_COMMAND, IDB_DIAL, 0 );
        return TRUE;
    }
    return FALSE;
}

//
//  FUNCTION: CmdPhbkDialDlg(HWND, WORD, WORD, HWND)
//
//  PURPOSE: Displays the "DialDlg" dialog box
//
//  PARAMETERS:
//    hdlg      - Window handle
//    wCommand  - IDB_DIAL(unused)
//    wNotify   - Notification number (unused)
//    hwndCtrl  - NULL (unused)
//
//  RETURN VALUE:
//
//    Always returns TRUE - Message handled
//
//  COMMENTS:
//    Calls authentication and dialing dialog boxes
//

LRESULT CmdPhbkDlgDial(HWND hdlg, WORD wCommand, WORD wNotify, HWND hwndCtrl)
{
    g_bUseCurrent = IsDlgButtonChecked( hdlg, IDC_USECURRENT );

    // short circut evaluation will cause the AuthDlg box not to be
    // displayed if g_bUseCurrent is true
    if ( g_bUseCurrent || DialogBox(hInst, "AuthDlgBox", hdlg, (DLGPROC)AuthDlg) )
    {
        if( DialogBox(hInst, "DialDlgBox", hdlg, (DLGPROC)DialDlg))
            EndDialog(hdlg, TRUE);          // Exit Phonebook dialog
                                            // if connection established
    }
    return TRUE;
}
