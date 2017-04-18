/*==========================================================================
 *
 *  Copyright (C) 1995 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       dinstall.c
 *  Content:    Game SDK sample setup program
 ***************************************************************************/

#include <stdio.h>      // for sprintf
#include <windows.h>
#include <shellapi.h>   // for SHFileOperation
#include <shlobj.h>     // for SHBroweForFolder
#include "dsetup.h"
#include "dinstall.h"

/*
 * global constants and macros
 */
#define BUFFER_SIZE 512

#define LoadStrFromRes(uID,lpBuffer) \
LoadString (GetModuleHandle(NULL),\
            (uID),\
            (lpBuffer),\
            sizeof((lpBuffer)));


/*
 * list of files that will be copied from the source directory to
 * to the directory the game is created in
 */
static char* copy_list [] =
{
        "ROCKEM3D.EXE",
        "ARENA.X",
        "BLOCK1.WAV",
        "BLOCK2.WAV",
        "BLOCK3.WAV",
        "CBOO.WAV",
        "CLOOP.WAV",
        "CYEAH.WAV",
        "DEBRIS_B.X",
        "DEBRIS_R.X",
        "DEFEND1.WAV",
        "DEFEND2.WAV",
        "DEMECH.X",
        "DEMECHBK.PPM",
        "DEMECHBT.PPM",
        "DEMECHCH.PPM",
        "DEMECHGR.PPM",
        "DEMECHH1.PPM",
        "DEMECHH2.PPM",
        "DEMECHHD.PPM",
        "DEMECHHN.PPM",
        "DEMECHLA.PPM",
        "DEMECHLL.PPM",
        "DEMECHUA.PPM",
        "DEMECHUL.PPM",
        "GDK_FILL.PPM",
        "HEAD.WAV",
        "INTRO.WAV",
        "PUNCH.WAV",
        "PUNCH1.WAV",
        "PUNCH2.WAV",
        "PUNCH3.WAV",
        "PUNCH4.WAV",
        "REVDN1.WAV",
        "REVDN2.WAV",
        "REVDN3.WAV",
        "REVUP1.WAV",
        "REVUP2.WAV",
        "REVUP3.WAV",
        "RANDOM1.WAV",
        "RANDOM2.WAV",
        "RANDOM3.WAV",
        "RANDOM4.WAV",
        "RANDOM5.WAV",
        "RANDOM6.WAV",
        "ROCKEM3D.BIN",
        "ROCKEM3D.MID",
        "ROCKEM3D.PAL",
        "SKMECH.X",
        "SKMECHBK.PPM",
        "SKMECHBT.PPM",
        "SKMECHCH.PPM",
        "SKMECHGR.PPM",
        "SKMECHHN.PPM",
        "SKMECHJD.PPM",
        "SKMECHLA.PPM",
        "SKMECHLL.PPM",
        "SKMECHUA.PPM",
        "SKMECHUL.PPM",
        "SPLASH.PAL",
        "WALK0.WAV",
        "WALK1.WAV",
        "WHOOSH1.WAV",
        "WHOOSH2.WAV",
};

static char       szTitle[BUFFER_SIZE];

/*
 * prototypes
 */
BOOL FAR PASCAL masterDlgProc( HWND hdlg,DWORD message,DWORD wparam,DWORD lparam );

/*
 * globals
 */
static HANDLE   hinst;
static char     GameDirectory[MAX_PATH];    // where the user wants the game
static char     SetupDirectory[MAX_PATH];     // where the user ran setup from

/*
 * support functions
 */
void catpath(char *dst, char *src)
{
        int len = lstrlen(dst);
        if (len > 0 && (dst[len-1] != '\\' && dst[len-1] != '/'))
                lstrcat(dst,"\\");
        lstrcat(dst,src);

        // SHFileOperation needs a double null string.
        len = lstrlen(dst);
        dst[len+1] = 0;
}

/*
 * set a bitmap into a static control
 */
void SetBitmap(HWND hDlg, int id, char *szBitmap, int w, int h)
{
        HBITMAP hbm;
        HWND hwnd;

        hwnd = GetDlgItem(hDlg, id);

        if (hwnd == NULL)
                return;

        hbm = (HBITMAP)LoadImage(hinst, szBitmap, IMAGE_BITMAP, w, h,
                LR_LOADTRANSPARENT | LR_LOADMAP3DCOLORS | LR_CREATEDIBSECTION);

        if (hbm)
                hbm = (HBITMAP)SendMessage(hwnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hbm);

        if (hbm)
                DeleteObject(hbm);
}

void SetInfoText(HWND hDlg, char *sz, ...)
{
        char ach[128];
        va_list marker;
        va_start (marker,sz);
        wvsprintf(ach, sz, marker);
        SetDlgItemText(hDlg, IDC_INFO, ach);
}

void _SHFree(void *p)
{
        IMalloc *pm;
        SHGetMalloc(&pm);
        if (pm)
        {
                pm->lpVtbl->Free(pm,p);
                pm->lpVtbl->Release(pm);
        }
}

/*
 * build a shortcut in the start menu
 */
void MakeShortcut()
{
        char buf[512];
        char szSetupIni[MAX_PATH];
        char szExeFile[MAX_PATH];
        int len;
        int fh;
        char szGroupName[BUFFER_SIZE];
        char szLinkName[BUFFER_SIZE];

        static char setup_ini[] =
                "[progman.groups]\r\n"
                "groupX=%s\r\n"
                "[groupX]\r\n"
                "\"%s\",\"%s\",,,,\"%s\"\r\n";

        GetWindowsDirectory(szSetupIni, sizeof(szSetupIni));
        catpath(szSetupIni, "SETUP.INI");

        lstrcpy(buf, GameDirectory);
        catpath(buf, copy_list[0]);
        GetShortPathName(buf, szExeFile, sizeof(szExeFile));

//  lstrcpy(buf, GameDirectory);
//  GetShortPathName(buf, szWork, sizeof(szWork));

        LoadStrFromRes( IDS_GROUP_NAME, szGroupName );
        LoadStrFromRes( IDS_LINK_NAME, szLinkName );
        len = wsprintf(buf, setup_ini, szGroupName, szLinkName,
                szExeFile, GameDirectory);

        fh = _lcreat(szSetupIni, 0);

        if (fh != -1)
        {
                _lwrite(fh, buf, len);
                _lclose(fh);
                WinExec("grpconv -o", SW_HIDE);
        }
}

/*
 * dlg proc for wizard dialog box, the setup is controlled from here.
 */
BOOL FAR PASCAL masterDlgProc(HWND hDlg,DWORD dwMessage,DWORD wParam,DWORD lParam)
{
        int             result;
        static int  system_restart;
        static int      current_dialog;
        static int  busy;

        char        src[MAX_PATH];
        char        dst[MAX_PATH];
        SHFILEOPSTRUCT fileop;

        char       szBuffer[BUFFER_SIZE];

    switch(dwMessage)
    {
    case WM_INITDIALOG:
                busy = 0;
                current_dialog = 0;

                LoadStrFromRes( IDS_TITLE, szTitle );
                SetWindowText( hDlg, szTitle );
                EnableWindow( GetDlgItem(hDlg, IDC_B), FALSE );
                EnableWindow( GetDlgItem(hDlg, IDC_H), FALSE );

                /*
                 * set the signon bitmap into our static control
                 */
                LoadStrFromRes( IDS_SIGNON_BITMAP_NAME, szBuffer );
                SetBitmap( hDlg, IDC_STATIC, szBuffer, 175, 195 );

                /*
                 * limit the size of the input of this text field to the length of a path
                 * put the default directory to install the game into in it
                 * select the whole thing to make it easy for people to replace it
                 * set the focus to it
                 */
                SendDlgItemMessage( hDlg, IDC_EDIT, EM_LIMITTEXT, MAX_PATH, 0L);
                LoadStrFromRes( IDS_DEFAULT_GAME_DIR, szBuffer );
                        SetDlgItemText( hDlg, IDC_EDIT, szBuffer );
                SendDlgItemMessage( hDlg, IDC_EDIT, EM_SETSEL, 0, MAKELONG(256, 256) );
                        SetFocus( GetDlgItem(hDlg, IDC_EDIT) );
                /*
                 * return 0 here indicating we have set the focus for the dialog box
                 * and it doesn't need to help us
                 */
                return 0;

    case WM_SETCURSOR:
        if (busy)
        {
            SetCursor(LoadCursor(NULL, IDC_WAIT));
            return TRUE;
        }
        break;

    case WM_COMMAND:
                switch(wParam)
                {
                case IDOK:
                        if( busy > 0 )
                        {
                                /*
                                 * busy bit keeps us from taking input while we are off doing
                                 * things that can create other dialog boxes and end up causing
                                 * us to be reentered.
                                 */
                                break;
                        }
                        else if( current_dialog == 0 )
                        {
                                        int     i;

                                        busy++;
                                        EnableWindow(GetDlgItem(hDlg,IDOK), FALSE);
                                        EnableWindow(GetDlgItem(hDlg,IDCANCEL), FALSE);
                                        SetCursor(LoadCursor(NULL, IDC_WAIT));

                                        /*
                                         * get the directory the user typed
                                         */
                                        GetWindowText( GetDlgItem( hDlg,IDC_EDIT ), GameDirectory, sizeof(GameDirectory));

                                        /*
                                         * verify that the typed in directory is valid
                                         * by having the SHELL copy WIN.INI to this directory
                                         * it will also create the directory for us.
                                         */
                                        LoadStrFromRes( IDS_CREATE_MSG, szBuffer );
                                        SetInfoText(hDlg, szBuffer);

                                        GetWindowsDirectory(src, sizeof(src));
                                        catpath(src,"WIN.INI");

                                        lstrcpy(dst,GameDirectory);
                                        catpath(dst,"SMAG.INI");

                                        fileop.hwnd     = hDlg;
                                        fileop.wFunc    = FO_COPY;
                                        fileop.pFrom    = src;
                                        fileop.pTo      = dst;
                                        fileop.fFlags   = FOF_SILENT | FOF_NOCONFIRMATION;

                                        if (SHFileOperation(&fileop) != 0)
                                        {
                                                // failed, the shell gave the user a error.
                                                SetInfoText(hDlg, "");
                                                EnableWindow(GetDlgItem(hDlg,IDOK), TRUE);
                                                EnableWindow(GetDlgItem(hDlg,IDCANCEL), TRUE);
                                                busy--;
                                                break;
                                        }

                                        /*
                                         * the directory is valid now delete the bogus file
                                         */
                                        fileop.hwnd     = hDlg;
                                        fileop.wFunc    = FO_DELETE;
                                        fileop.pFrom    = dst;
                                        fileop.pTo      = NULL;
                                        fileop.fFlags   = FOF_SILENT | FOF_NOCONFIRMATION;

                                        SHFileOperation(&fileop);
                                        SetInfoText(hDlg, "");

                                        /*
                                         * check if there is enough space to install the game
                                         * NOTE: there is always enough space at the moment :-)
                                         */

                                        LoadStrFromRes( IDS_DISK_MSG, szBuffer );
                                        SetInfoText(hDlg, szBuffer);

                                        if( 0 )
                                        {
                                                /* your code goes here */
                                        }
                                        SetInfoText(hDlg, "");

                                        /*
                                         * now setup DirectX
                                         */
                                        LoadStrFromRes( IDS_INSTALL_MSG, szBuffer );
                                        SetInfoText(hDlg, szBuffer);

                                        result = DirectXSetup( hDlg, NULL, DSETUP_DIRECTX );

                                        SetInfoText(hDlg, "");

                                        if( result < 0 )
                                        {
                                                if (result == DSETUPERR_NOTPREINSTALLEDONNT)
                                                {
                                                        /*
                                                         *  DirectX comes preinstalled on NT, and can only
                                                         *  be installed in an NT release or Service Pack.
                                                         *  If this error code is returned, then the required
                                                         *  version of DirectX is not preinstalled on this
                                                         *  NT machine.  The user will have to go get
                                                         *  the NT version or Service Pack required, or this
                                                         *  game will not run.  Note that any application
                                                         *  can redistribute an NT Service Pack as long as
                                                         *  it is distributed in its entirety.  Check out
                                                         *  ftp://ftp.microsoft.com/bussys/winnt/winnt-public/fixes
                                                         */
                                                        LoadStrFromRes( IDS_NTFAILED_MSG, szBuffer );
                                                        MessageBox( hDlg, szBuffer, szTitle, 0 );
                                                }
                                                else
                                                {
                                                        LoadStrFromRes( IDS_FAILED_MSG, szBuffer );
                                                        MessageBox( hDlg, szBuffer, szTitle, 0 );
                                                }
                                                EndDialog(hDlg, result);
                                                break;
                                        }
                                        else if( result == 0 )
                                        {
                                                /*
                                                 *  Check the post-install DirectX Version number,
                                                 *  to check if the game will be able to run.
                                                 *
                                                 *  DirectXSetupGetVersion will get the version
                                                 *  and revision info about the current installation.
                                                 *  Note that since we're calling this after
                                                 *  DirectXSetup, the "current" installation is the
                                                 *  post-install version of DirectX.
                                                 *
                                                 *  Since we don't care about the revision number,
                                                 *  we're leaving that parameter as NULL.
                                                 */

                                                DWORD dwVersion;

                                                if( DirectXSetupGetVersion(&dwVersion, NULL) )
                                                {
                                                        /*  we need DirectX 3.0 or better, so we're going
                                                         *  to make sure that dwVersion is at least equal
                                                         *  to 0x00040003.  If we needed DirectX 5.0
                                                         *  functionality, we'd check for 0x00040005.
                                                         *
                                                         *  If your game needs specific DX functionality,
                                                         *  this is a good place to check to ensure that
                                                         *  the correct version of DirectX is available.
                                                         *
                                                         *  On Windows NT, DirectX is pre-installed, so
                                                         *  this check will allow notification of NT users
                                                         *  that they'll need to update through a service
                                                         *  pack, or they won't be able to run the game.
                                                         */

                                                        if( dwVersion < (DWORD)0x00040003 )
                                                        {
                                                                sprintf(szBuffer,
                                                                        "Your system is preinstalled with version %d.%d "
                                                                        "of DirectX.  This game requires DirectX version "
                                                                        "4.3 or better to run.\n\n"
                                                                        "Do you want to install the game anyway?",
                                                                        HIWORD(dwVersion), LOWORD(dwVersion));

                                                                result = MessageBox( hDlg, szBuffer, szTitle, MB_YESNO);

                                                                if( result == IDNO )
                                                                {
                                                                        MessageBox( hDlg,
                                                                        "You've chosen not to install the game.\n\n"
                                                                        "Click \"OK\" to end Setup.",
                                                                        szTitle, MB_OK);
                                                                        EndDialog( hDlg, 0 );
                                                                        break;
                                                                }
                                                        }
                                                }
                                        }

                                        /*
                                         * check if there is enough space to install the game
                                         * NOTE: there is always enough space at the moment :-)
                                         */
                                        LoadStrFromRes( IDS_DISK_MSG, szBuffer );
                                        SetInfoText(hDlg, szBuffer);
                                        if( 0 )
                                        {
                                                /* your code goes here */
                                        }
                                        SetInfoText(hDlg, "");

                                        /*
                                         * now copy the files.
                                         */
                                        system_restart = result;

                                        LoadStrFromRes( IDS_COPYING_MSG, szBuffer );
                                        SetInfoText(hDlg, szBuffer);

                                        for( i = 0; i < sizeof( copy_list )/sizeof( copy_list[0] ); i++ )
                                        {
                                                lstrcpy( src, SetupDirectory );
                                                catpath( src, copy_list[i] );

                                                lstrcpy( dst, GameDirectory );
                                                catpath( dst, copy_list[i] );

                                                LoadStrFromRes( IDS_CURRENT_FILE_MSG, szBuffer );
                                                SetInfoText(hDlg, szBuffer, copy_list[i]);

                                                fileop.hwnd     = hDlg;
                                                fileop.wFunc    = FO_COPY;
                                                fileop.pFrom    = src;
                                                fileop.pTo      = dst;
                                                fileop.fFlags   = FOF_SILENT | FOF_NOCONFIRMATION;

                                                while (result = SHFileOperation(&fileop))
                                                {
                                                        char errorText[MAX_PATH+BUFFER_SIZE];

                                                        LoadStrFromRes( IDS_SETUP_FAILURE_MSG, szBuffer );
                                                        wsprintf(errorText, szBuffer, copy_list[i] );
                                                        result = MessageBox( hDlg, errorText, szTitle, MB_RETRYCANCEL );

                                                        if( result == IDCANCEL )
                                                        {
                                                                result = -1;
                                                                break;
                                                        }
                                                }

                                                if( result == 0 )
                                                {
                                                        SetFileAttributes( dst, FILE_ATTRIBUTE_NORMAL );
                                                }
                                        }
                                        SetInfoText(hDlg, "");

                                        LoadStrFromRes( IDS_STARTUP_MSG, szBuffer );
                                        SetInfoText(hDlg, szBuffer);
                                        MakeShortcut();
                                        SetInfoText(hDlg, "");

                                        if( result >= 0 )
                                        {
                                                /*
                                                 * hide current controls
                                                 */
                                                ShowWindow( GetDlgItem(hDlg, IDC_EDIT), SW_HIDE );
                                                ShowWindow( GetDlgItem(hDlg, IDC_DIRECTIONS1), SW_HIDE );
                                                ShowWindow( GetDlgItem(hDlg, IDC_DIRECTIONS2), SW_HIDE );
                                                ShowWindow( GetDlgItem(hDlg, IDC_EDITTEXT), SW_HIDE );
                                                ShowWindow( GetDlgItem(hDlg, IDC_INFO), SW_HIDE );
                                                ShowWindow( GetDlgItem(hDlg, IDC_BROWSE), SW_HIDE );

                                                if( system_restart )
                                                {
                                                        /*
                                                         * show new dialogs
                                                         */
                                                        ShowWindow( GetDlgItem(hDlg, IDC_REBOOT1), SW_SHOW );
                                                        ShowWindow( GetDlgItem(hDlg, IDC_REBOOT2), SW_SHOW );
                                                        LoadStrFromRes( IDS_REBOOT_BUTTON, szBuffer );
                                                        SetWindowText( GetDlgItem(hDlg, IDOK), szBuffer );

                                                        /*
                                                         * set the reboot bitmap into our static control
                                                         */
                                                        LoadStrFromRes( IDS_REBOOT_BITMAP_NAME, szBuffer );
                                                        SetBitmap(hDlg, IDC_STATIC, szBuffer, 270, 195);
                                                        current_dialog++;
                                                }
                                                else
                                                {
                                                        ShowWindow( GetDlgItem(hDlg, IDC_SUCCESS), SW_SHOW );
                                                        LoadStrFromRes( IDS_FINISH_BUTTON, szBuffer );
                                                        SetWindowText( GetDlgItem(hDlg, IDOK), szBuffer );
                                                        current_dialog++;
                                                        EnableWindow(GetDlgItem(hDlg,IDOK), TRUE);
                                                        busy--;
                                                        break;
                                                }
                                        }

                                        EnableWindow(GetDlgItem(hDlg,IDOK), TRUE);
                                        EnableWindow(GetDlgItem(hDlg,IDCANCEL), TRUE);
                                        busy--;

                                        if( result < 0 )
                                        {
                                                EndDialog( hDlg, result );
                                        }
                                }
                                else if (current_dialog == 1)
                                {
                                        /*
                                         * restart windows, kill apps that aren't responding, reboot
                                         */
                                        if( system_restart )
                                        {
                                                ExitWindowsEx( EWX_REBOOT, 0 );
                                        }
                                        else
                                        {
                                                EndDialog( hDlg, 0 );
                                        }
                                }
                                break;

                        case IDCANCEL:
                                if( !busy )
                                {
                                        /*
                                         * only allow cancel if we aren't doing anything else
                                         */
                                        EndDialog( hDlg, -1 );
                                }
                                break;

                        case IDC_BROWSE:
                                if( current_dialog == 0 )
                                {
                                        BROWSEINFO bi;
                                        LPITEMIDLIST pidl;
                                        char ach[MAX_PATH];

                                        bi.hwndOwner      = hDlg;
                                        bi.pidlRoot       = NULL;
                                        bi.pszDisplayName = ach;
                                        bi.lpszTitle      = NULL;
                                        bi.ulFlags        = BIF_RETURNONLYFSDIRS;
                                        bi.lpfn           = NULL;
                                        bi.lParam         = 0;
                                        bi.iImage         = 0;

                                        pidl = SHBrowseForFolder(&bi);

                                        if (pidl)
                                        {
                                                SHGetPathFromIDList(pidl, ach);
                                                SetDlgItemText(hDlg, IDC_EDIT, ach);
                                                _SHFree(pidl);
                                        }
                                }
                                break;
                }
    }
    return 0;
}

/* **************************************************************** */
int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrev, LPSTR szCmdLine, int nCmdShow)
{
        TCHAR * p;
        TCHAR * x;
        hinst = hInstance;

        /*
         * get our fullpath name and strip the file name
         */
        GetModuleFileName(hInstance, SetupDirectory, sizeof(SetupDirectory));

        for (x=p=SetupDirectory; *p; p=AnsiNext(p))
        {
                if ((*p == '\\') || (*p == '/'))
                        x = p;
        }
        *x = 0;

        /*
         * do the setup thing, it is all one big dialog box that you show
         * and hide things from depending on the screen
         * we just sign on, ask where to install, and install
         */
        DialogBox( hInstance, "DLG_MASTER", NULL, (DLGPROC)masterDlgProc );

        return 0;
} /* WinMain */
