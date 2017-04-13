// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993-1997  Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:   authdlg.c
//
//  PURPOSE:   Displays the "AuthDlg" dialog box
//
//  FUNCTIONS:
//    AuthDlg           - Processes messages for "AuthDlg" dialog box.
//    MsgAuthDlgInit    - To initialize the authdlg box with version info
//                      from resources.
//    MsgAuthDlgCommand - Process WM_COMMAND message sent to the authdlg box.
//    CmdAuthDlgOK      - Free the authdlg box and signal continue with dial.
//    CmdAuthDlgCancel  - Free the authdlg box.
//
//  COMMENTS:
//    Dialog Box to get authentication information
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
#include "authdlg.h"

LRESULT MsgAuthDlgInit(HWND, UINT, WPARAM, LPARAM);
LRESULT MsgAuthDlgCommand(HWND, UINT, WPARAM, LPARAM);
LRESULT CmdAuthDlgOK(HWND, WORD, WORD, HWND);
LRESULT CmdAuthDlgCancel(HWND, WORD, WORD, HWND);


// AuthDlg dialog message table definition.
MSD rgmsdAuthDlg[] =
{
    {WM_COMMAND,      MsgAuthDlgCommand},
    {WM_INITDIALOG,   MsgAuthDlgInit}
};

MSDI msdiAuthDlg =
{
    sizeof(rgmsdAuthDlg) / sizeof(MSD),
    rgmsdAuthDlg,
    edwpNone
};

// AuthDlg dialog command table definition.
CMD rgcmdAuthDlg[] =
{
    {IDOK,     CmdAuthDlgOK},
    {IDCANCEL, CmdAuthDlgCancel}
};

CMDI cmdiAuthDlg =
{
    sizeof(rgcmdAuthDlg) / sizeof(CMD),
    rgcmdAuthDlg,
    edwpNone
};

// Module specific "globals"  Used when a variable needs to be
// accessed in more than on handler function.

//
//  FUNCTION: AuthDlg(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for "AuthDlg" dialog box.
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
//    Dispatches message to appropriate handler
//

LRESULT CALLBACK AuthDlg(HWND hdlg, UINT uMessage, WPARAM wparam, LPARAM lparam)
{
    return DispMessage(&msdiAuthDlg, hdlg, uMessage, wparam, lparam);
}


//
//  FUNCTION: MsgAuthDlgInit(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: To initialize the authdlg box
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
//    Registers window message for RAS event.
//    Makes call to RasDial with appropriate params.
//

LRESULT MsgAuthDlgInit(HWND hdlg, UINT uMessage, WPARAM wparam, LPARAM lparam)
{
    // Set text limits on edit controls
    SendDlgItemMessage(hdlg, IDE_USERNAME, EM_LIMITTEXT, (WPARAM) UNLEN, 0L );
    SendDlgItemMessage(hdlg, IDE_PASSWORD, EM_LIMITTEXT, (WPARAM) PWLEN, 0L );
    SendDlgItemMessage(hdlg, IDE_DOMAIN,   EM_LIMITTEXT, (WPARAM) DNLEN, 0L );

    // reset password
    g_szPassword[0] = '\0';

    // Set default text in edit controls
    SendDlgItemMessage(hdlg, IDE_USERNAME, WM_SETTEXT, (WPARAM) 0, (LPARAM)(LPSTR) g_szUserName );
    SendDlgItemMessage(hdlg, IDE_PASSWORD, WM_SETTEXT, (WPARAM) 0, (LPARAM)(LPSTR) g_szPassword );
    SendDlgItemMessage(hdlg, IDE_DOMAIN,   WM_SETTEXT, (WPARAM) 0, (LPARAM)(LPSTR) g_szDomain );

    // Center the dialog over the application window
    CenterWindow(hdlg, GetWindow(hdlg, GW_OWNER));

    return TRUE;
}


//
//  FUNCTION: MsgAuthDlgCommand(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Process WM_COMMAND message sent to the authdlg box.
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
//    with the cmdiAuthDlg structure defined in this file to handle
//    the command messages for the authdlg dialog box.
//

LRESULT MsgAuthDlgCommand(HWND   hwnd,
                        UINT   uMessage,
                        WPARAM wparam,
                        LPARAM lparam)
{
    return DispCommand(&cmdiAuthDlg, hwnd, wparam, lparam);
}

//
//  FUNCTION: CmdAuthDlgOK(HWND, WORD, WORD,  HWND)
//
//  PURPOSE: Free the authdlg box and related data.
//
//  PARAMETERS:
//    hwnd - The window handling the command.
//    wCommand - The command to be handle. IDOK.
//    wNotify - The notification to be handled (unused).
//    hwndCtrl - NULL (unused).
//
//  RETURN VALUE:
//    Always returns TRUE.
//
//  COMMENTS:
//    Calls EndDialog to finish the dialog session.
//

LRESULT CmdAuthDlgOK(HWND hdlg, WORD wCommand, WORD wNotify, HWND hwndCtrl)
{
    // Get text entered by the user
    SendDlgItemMessage(hdlg, IDE_USERNAME, WM_GETTEXT, (WPARAM) UNLEN+1, (LPARAM)(LPSTR) g_szUserName );
    SendDlgItemMessage(hdlg, IDE_PASSWORD, WM_GETTEXT, (WPARAM) PWLEN+1, (LPARAM)(LPSTR) g_szPassword );
    SendDlgItemMessage(hdlg, IDE_DOMAIN,   WM_GETTEXT, (WPARAM) DNLEN+1, (LPARAM)(LPSTR) g_szDomain );

    EndDialog(hdlg, TRUE);          // Exit the dialog
    return TRUE;
}

//
//  FUNCTION: CmdAuthDlgCancel(HWND, WORD, WORD,  HWND)
//
//  PURPOSE: Free the authdlg box and related data.
//
//  PARAMETERS:
//    hwnd - The window handling the command.
//    wCommand - The command to be handled. IDCANCEL.
//    wNotify - The notification to be handled (unused).
//    hwndCtrl - NULL (unused).
//
//  RETURN VALUE:
//    Always returns TRUE.
//
//  COMMENTS:
//    Calls EndDialog to finish the dialog session.
//

LRESULT CmdAuthDlgCancel(HWND hdlg, WORD wCommand, WORD wNotify, HWND hwndCtrl)
{
    EndDialog(hdlg, FALSE);          // Exit the dialog
    return TRUE;
}


