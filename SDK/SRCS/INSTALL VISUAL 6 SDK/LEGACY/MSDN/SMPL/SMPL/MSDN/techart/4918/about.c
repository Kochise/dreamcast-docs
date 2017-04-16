/*-----------------------------------------------------------------------------

    This is a part of the Microsoft Source Code Samples. 
    Copyright (C) 1995 Microsoft Corporation.
    All rights reserved. 
    This source code is only intended as a supplement to 
    Microsoft Development Tools and/or WinHelp documentation.
    See these sources for detailed information regarding the 
    Microsoft samples programs.

    MODULE:   About.c

    PURPOSE:  Implement the About dialog box for the program.

    FUNCTIONS:
        CmdAbout     - Creates the About dialog in response to menu selection
        AboutDlgProc - Processes messages for the About dialog
        InitAboutDlg - Initialzes about dialog controls

-----------------------------------------------------------------------------*/


#include <windows.h>
#include "mttty.h"

/*
    Prototypes for functions called only in this file
*/
BOOL CALLBACK AboutDlgProc( HWND, UINT, WPARAM, LPARAM );
UINT InitAboutDlg( HWND );

/*-----------------------------------------------------------------------------

FUNCTION: CmdAbout( HWND )

PARAMETERS:
    hwnd - Owner of the window

PURPOSE: Creates the modal About dialog

-----------------------------------------------------------------------------*/
BOOL CmdAbout(HWND hwnd)
{
    DialogBox(ghInst, MAKEINTRESOURCE(IDD_ABOUT), hwnd, AboutDlgProc);
    return 0;
}

/*-----------------------------------------------------------------------------

FUNCTION: InitAboutDlg( HWND )

PURPOSE: Initializes the modal About dialog

PARMATETERS:
    hDlg - Dialog window handle

COMMENTS: Sets the icon animation timer and the version info.

HISTORY:   Date:      Author:     Comment:
           10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
UINT InitAboutDlg(HWND hDlg)
{
    UINT uTimer;
    char * szFormat = "Microsoft Windows %s\r\nVersion %d.%d\r\nBuild %d ";
    char szVersion[256];
    
    /*    
        create timer and set initial icon id
    */
    uTimer = SetTimer(hDlg, 1, 100, NULL);
    if (uTimer == 0)
        ErrorReporter("SetTimer");
    wsprintf(szVersion, szFormat, 
                    gOSV.dwPlatformId == VER_PLATFORM_WIN32_NT ? "NT" : "95",
                    gOSV.dwMajorVersion, 
                    gOSV.dwMinorVersion, 
                    LOWORD( gOSV.dwBuildNumber ) );

    if (strlen(gOSV.szCSDVersion))
        strcat(szVersion, gOSV.szCSDVersion);
                            
    SetDlgItemText(hDlg, IDC_OSVERSIONINFO, szVersion);

    return uTimer;
}

/*-----------------------------------------------------------------------------

FUNCTION: AboutDlgProc(HWND, UINT, WPARAM, LPARAM)

PURPOSE: Dialog procedure for the "About Box"

PARAMETERS:
    hdlg     - dialog window handle
    uMessage - window message
    wparam   - message parameter (depends on message value)
    lparam   - message prarmeter (depends on message value)

HISTORY:    Date:      Author:     Comment:
            10/27/95   AllenD      Wrote it

-----------------------------------------------------------------------------*/
BOOL CALLBACK AboutDlgProc(HWND hdlg, UINT uMessage, WPARAM wparam, LPARAM lparam)
{
    static UINT uTimer;
    static WORD wCurrentIconId;

    switch(uMessage)
    {
        case WM_INITDIALOG:
            uTimer = InitAboutDlg(hdlg);
            wCurrentIconId = IDI_APPICON;
            break;

        case WM_TIMER:
            /*
                when timer goes off, then change to next icon
            */
            {
                HICON hIcon;

                switch(wCurrentIconId)
                {
                    case IDI_APPICON:   wCurrentIconId = IDI_APPICON2;  break;
                    case IDI_APPICON2:  wCurrentIconId = IDI_APPICON3;  break;
                    case IDI_APPICON3:  wCurrentIconId = IDI_APPICON4;  break;
                    case IDI_APPICON4:  wCurrentIconId = IDI_APPICON;   break;
                }
            
                hIcon = LoadIcon(ghInst, MAKEINTRESOURCE(wCurrentIconId));
                SendMessage(GetDlgItem(hdlg, IDC_PICTURE), STM_SETICON, (WPARAM) hIcon, 0);
            }
            break;

        case WM_COMMAND:
            if (LOWORD(wparam) == IDOK) {
                KillTimer(hdlg, uTimer);
                EndDialog(hdlg, TRUE);
                return TRUE;
            }
            break;
    }

    return FALSE;
}

