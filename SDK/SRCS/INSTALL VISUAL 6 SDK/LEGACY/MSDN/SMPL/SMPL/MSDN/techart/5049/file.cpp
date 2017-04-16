/*==========================================================================
 *
 *  Copyright (C) 1995, 1996, 1997 Microsoft Corporation. 
 *  All Rights Reserved.
 *
 *  File: file.cpp
 *
 ***************************************************************************/

#include <d3drmwin.h>
#include "rmtex.h"
#include <windows.h>
#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

BOOL bX;
int slen;
char szTFile[32];
char szTExt[32];
char* OpenNewFile( HWND hwnd, const char *wndTitle )
{
    static char file[256];
    static char fileTitle[256];
    static char filter[] = "BMP files (*.BMP)\0*.BMP\0"
                           "PPM files (*.PPM)\0*.PPM\0"
                           "X files (*.X)\0*.X\0"
                           "All Files (*.*)\0*.*\0";
    OPENFILENAME ofn;

    lstrcpy( file, "");
    lstrcpy( fileTitle, "");

    ofn.lStructSize       = sizeof(OPENFILENAME);
    ofn.hwndOwner         = hwnd;
#ifdef WIN32
    ofn.hInstance         = (HINSTANCE) GetWindowLong(hwnd, GWL_HINSTANCE);
#else
    ofn.hInstance         = (HINSTANCE) GetWindowWord(hwnd, GWW_HINSTANCE);
#endif
    ofn.lpstrFilter       = filter;
    ofn.lpstrCustomFilter = (LPSTR) NULL;
    ofn.nMaxCustFilter    = 0L;
    ofn.nFilterIndex      = 1L;
    ofn.lpstrFile         = file;
    ofn.nMaxFile          = sizeof(file);
    ofn.lpstrFileTitle    = fileTitle;
    ofn.nMaxFileTitle     = sizeof(fileTitle);
    ofn.lpstrInitialDir   = NULL;
    ofn.lpstrTitle        = wndTitle;
    ofn.nFileOffset       = 0;
    ofn.nFileExtension    = 0;
    ofn.lpstrDefExt       = "*.bmp";
    ofn.lCustData         = 0;

    ofn.Flags = OFN_SHOWHELP | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn))
    {
        slen = strlen(ofn.lpstrFile);
        strncpy(szTFile,ofn.lpstrFile+ofn.nFileOffset,slen-ofn.nFileOffset);
        strncpy(szTExt,ofn.lpstrFile+ofn.nFileExtension,slen-ofn.nFileExtension);
        if ( _strnicmp(szTExt,"X",1)== 0 )
          bX = TRUE;
        else
          bX = FALSE;
        return (char*)ofn.lpstrFile;
    }
    else
        return NULL;
}
#ifdef __cplusplus
}
#endif
