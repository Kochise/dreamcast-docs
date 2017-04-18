/*
 * COMMDLG.C
 *
 * Routines to interface to the COMMDLG library for File Open and
 * File Save/Save As functions.
 *
 * Copyright(c) Microsoft Corp. 1992-1994 All Rights Reserved
 * Win32 version, January 1994
 */

#include <windows.h>
#include <commdlg.h>
#include "cosmo.h"



/*
 * FSaveOpenDialog
 *
 * Purpose:
 *  Invokes the COMMDLG.DLL GetOpenFileName dialog and retrieves
 *  a filename for saving or opening.
 *
 * Parameters:
 *  hWnd            HWND of the owning application.
 *  hInst           HINSTANCE of the application instance.
 *  pszExt          LPSTR of the default extension
 *  pszFilter       LPSTR of the filter desciption.
 *  pszFile         LPSTR buffer to receive the entered filename.
 *                  Must be at least CCHPATHMAX long.
 *  fOpen           BOOL indicating if we want file open or save.
 *
 * Return Value:
 *  BOOL            TRUE if the function retrieved a filename,
 *                  FALSE if the user pressed CANCEL.
 */

BOOL WINAPI FSaveOpenDialog(HWND hWnd, HINSTANCE hInst, LPSTR pszExt
    , LPSTR pszFilter, LPSTR pszFile, LPSTR pszCaption, BOOL fOpen)
    {
    OPENFILENAME    ofn;
    char            szTitle[CCHFILENAMEMAX];
    char            szFilter[80];
    UINT            cch1;
    UINT            cch2;

    ofn.lStructSize      =sizeof(OPENFILENAME);
    ofn.hwndOwner        =hWnd;
    ofn.hInstance        =hInst;

    ofn.lpstrFilter      =szFilter;
    ofn.lpstrCustomFilter=NULL;
    ofn.nMaxCustFilter   =0L;
    ofn.nFilterIndex     =1L;                //We only have 1 extension.

    ofn.lpstrFile        =pszFile;
    ofn.nMaxFile         =CCHPATHMAX;
    ofn.lpstrFileTitle   =(LPSTR)szTitle;
    ofn.nMaxFileTitle    =CCHFILENAMEMAX;

    ofn.lpstrInitialDir  =NULL;
    ofn.lpstrTitle       =pszCaption;

    ofn.Flags            =OFN_HIDEREADONLY;
    ofn.nFileOffset      =0;
    ofn.nFileExtension   =0;
    ofn.lpstrDefExt      =pszExt;
    ofn.lCustData        =0;
    ofn.lpfnHook         =NULL;
    ofn.lpTemplateName   =NULL;


    //Modify the flags as appropriate.
    if (fOpen)
        ofn.Flags        |= OFN_FILEMUSTEXIST;
    else
        ofn.Flags        |= OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;


    //Build a filter like "pszFilter\0*.pszExt\0\0"
    lstrcpy(szFilter, pszFilter);
    cch1=1+lstrlen(szFilter);

    cch2=wsprintf(pszFile, "*.%s", pszExt);  //Initial edit control contents.
    lstrcpy(szFilter+cch1, pszFile);         //Append to filter.

    //Add the second null-terminator.
    *(szFilter+cch1+cch2+1)=0;

    return GetOpenFileName(&ofn);
    }
