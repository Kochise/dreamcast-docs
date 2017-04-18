/*
    file.c

    File loading functions and corresponding object delete functions

*/

#include "global.h"

//
// local data
//

char *szOpenFilter = "DIB Files (*.dib)\0*.dib\0"
                     "Bitmap files (*.bmp)\0*.bmp\0"
                     "All Files (*.*)\0*.*\0"
                     "\0";
char *szIniFilter  = "INI Files (*.ini)\0*.ini\0"
                            "All Files (*.*)\0*.*\0"
                            "\0";

//
// Put up a dialog to get a filename
//

BOOL 
PromptForFileName(hwndOwner, hInst, achFileName, cchFileName,
    szCaption, szFilter, szDefExt, dwFlags)
HWND        hwndOwner;        // window that will own dialog box
HANDLE        hInst;            // module that contains the resources
LPSTR        achFileName;        // where to put file name
WORD        cchFileName;        // size of <achFileName>
LPSTR       szCaption;        // caption string
LPSTR       szFilter;        // file filter
LPSTR       szDefExt;        // default extension
DWORD        dwFlags;        // random flags
{
    OPENFILENAME    ofname;        // parameter block
    BOOL        f;

    /* the initial file name is "" unless PFFN_SHOWDEFAULT is given */
    if (!(dwFlags & PFFN_SHOWDEFAULT))
        achFileName[0] = 0;

    /* fill in the other fields of <ofname> */
    ofname.lpstrFilter = szFilter;
    ofname.lpstrTitle = szCaption;
    ofname.lpstrDefExt = szDefExt;
    ofname.lStructSize = sizeof(ofname);
    ofname.hwndOwner = hwndOwner;
    ofname.hInstance = hInst;
    ofname.lpstrCustomFilter = NULL;
    ofname.nMaxCustFilter = 0;
    ofname.nFilterIndex = 1;
    ofname.lpstrFile = achFileName;
    ofname.nMaxFile = cchFileName;
    ofname.lpstrFileTitle = NULL;
    ofname.nMaxFileTitle = 0;
    ofname.lpstrInitialDir = NULL;
    ofname.Flags = OFN_HIDEREADONLY |
        (dwFlags & PFFN_OVERWRITEPROMPT ? OFN_OVERWRITEPROMPT : 0);
    ofname.lCustData = NULL;
    ofname.lpfnHook = NULL;
    ofname.lpTemplateName = NULL;

    /* prompt the user for the file name */
    if (dwFlags & PFFN_OPENFILE)
        f = GetOpenFileName(&ofname);
    else
        f = GetSaveFileName(&ofname);

    /* make the name uppercase if requested */
    if (f && (dwFlags & PFFN_UPPERCASE))
        AnsiUpper(achFileName);

    return f;
}


