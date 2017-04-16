/*
    file.c

    File new/open/close functions

    The file consists of a file header (FILEHEADER) followed by
    zero or more packed objects.  A Packed object consists of
    an OBJECT structure immediately followed by its data.

*/

#include "global.h"


//
// local data
//

static char *szUntitled = "(Untitled)";
static char *szOpenFilter = "Text Box Files (*.tbx)\0*.tbx\0"
                            "\0";

//
// If the file is dirty (modified), ask the user "Save before closing?".
// Return TRUE if it's okay to continue, FALSE if the caller should cancel
// whatever it's doing.
// 

BOOL PromptToSave()
{
    WORD        wID;
    char buf[256];

    if (!gfDirty) return TRUE;

    wsprintf(buf, "Save the changes to %s ?", (LPSTR)gachFileName);
    wID = MessageBox(ghwndMain,
                     buf,
                     gszAppName,
                     MB_ICONQUESTION | MB_YESNOCANCEL);
    if (wID == IDCANCEL) return FALSE;
    if (wID == IDYES) {
        if (!FileSave(FALSE)) return FALSE;
    }
    return TRUE;
}

//
// Set the caption of the app window.
//

void UpdateCaption(void)
{
    char achCaption[_MAX_PATH + 30]; // caption
    char achDrive[_MAX_DRIVE];    // drive
    char achDir[_MAX_DIR];    // directory path
    char achFname[_MAX_PATH];    // file name
    char achExt[_MAX_EXT];    // file name extension

    /* put file name (or "(Untitled)") in <achFname> */
    if (gfUntitled) {
        lstrcpy(achFname, gachFileName);
    } else {
        _splitpath(gachFileName, achDrive, achDir, achFname, achExt);
        lstrcat(achFname, achExt);
    }

    /* set the caption */
    wsprintf(achCaption, "%s - %s", (LPSTR) gszAppName, (LPSTR) achFname);
    SetWindowText(ghwndMain, achCaption);
}


/* fOK = FileNew(fPrompt, fUpdateDisplay)
 *
 * Make a blank document, after asking the user to save modifications
 * (if any).  If <fPrompt> is TRUE, then prompt to save changes before
 * destroying file.  If <fUpdateDisplay> is TRUE, then update the display
 * after creating a new file.
 */

// Flags:
//      FILE_PROMPT_FOR_SAVE
//      FILE_UPDATE_CAPTION
//

BOOL FileNew(WORD wFlags)
{
    dprintf2("FileNew");
    if (wFlags & FILE_PROMPT_FOR_SAVE)
    {
        if (!PromptToSave()) return FALSE;
    }

    //
    // Nuke the object list
    //

    while (gpObjList) DeleteObj(gpObjList);

    //
    // update state variables 
    //

    gfDirty = FALSE;        // untitled document is not dirty yet
    gfUntitled = TRUE;      // file has no name
    gachFileName[0] = 0;    // in case of error
    lstrcpy(gachFileName, szUntitled);

    //
    // update the display 
    //

    if (wFlags & FILE_UPDATE_CAPTION) {
        UpdateCaption();
    }
    InvalidateRect(ghwndMain, NULL, TRUE);
    return TRUE;
}


/* fOK = FileOpen(szFileName)
 *
 * If <szFileName> is NULL, do a File/Open command.  Otherwise, open
 * <szFileName>.  Return TRUE unless the user cancelled or the operation
 * failed.
 */

BOOL FileOpen(LPSTR szFileName)
{
    BOOL        fOK = TRUE;    // function succeeded?
    char        achFileName[_MAX_PATH]; // user-specified file name
    int        fh = -1;    // DOS file handle
    HCURSOR        hcurPrev = NULL; // cursor before hourglass
    FILEHEADER FileHead;
    OBJECT O;
    RECT rc;
    LPSTR pMem;
    POBJECT pObj;

    dprintf2("FileOpen");

    /* give user a chance to save this file (if it was modified) */
    if (!PromptToSave())
        goto RETURN_ERROR;

    /* put file name into <achFileName> (get from user or <szFileName>) */
    if (szFileName == NULL)
    {
        /* prompt the user for the name of the file to open */
        if (!PromptForFileName(ghwndMain, 
                               ghAppInstance, 
                               achFileName,
                               sizeof(achFileName), 
                               "Open File", 
                               szOpenFilter,
                               "txt",
                               PFFN_OPENFILE | PFFN_UPPERCASE))
            goto RETURN_ERROR;
    }
    else
        lstrcpy(achFileName, szFileName);

    /* empty the file */
    if (!FileNew(0))
        goto RETURN_ERROR;

    /* switch to new file */
    lstrcpy(gachFileName, achFileName);
    gfUntitled = FALSE;

    /* show hourglass cursor */
    hcurPrev = SetCursor(LoadCursor(NULL, IDC_WAIT));

    /* open the file */
    dprintf3("Opening %s", (LPSTR)gachFileName);
    if ((fh = _lopen(gachFileName, READ)) < 0) {
        dprintf1("Failed to open %s", (LPSTR)gachFileName);
        goto ERROR_OPENING;
    }

    //
    // Read the file header and validate it's one of ours
    //

    if (_lread(fh, &FileHead, sizeof(FileHead)) != sizeof(FileHead)) {
        dprintf1("Failed to read file header");
        goto ERROR_OPENING;
    }

    if (FileHead.dwMagic != FILEMAGIC) {
        Message(0, "File header missing or file is wrong type");
        goto ERROR_OPENING;
    }

    //
    // Try to read object headers and data until we fail
    //

    while (_lread(fh, &O, sizeof(O)) == sizeof(O)) {

        dprintf3(" object header read");
        pMem = ALLOCATE(O.uiSize);
        if (!pMem) goto ERROR_OPENING;

        if (_lread(fh, pMem, O.uiSize) != O.uiSize) {
            dprintf1("Failed to read %u bytes of object data");
            goto ERROR_OPENING;
        }

        pObj = CreateObj(O.rc.left, O.rc.top,
                         O.rc.right - O.rc.left, O.rc.bottom - O.rc.top,
                         O.uiType,
                         O.uiSize,
                         pMem);
        if (!pObj) goto ERROR_OPENING;
        AppendObj(pObj);

        FREE(pMem);
    }

    gfDirty = FALSE;

    //
    // Adjust the window size to fit
    //

    rc.top = 0;
    rc.left = 0;
    rc.right = max (FileHead.iWidth, 150);
    rc.bottom = max(FileHead.iHeight, 100);
    AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, TRUE);
    SetWindowPos(ghwndMain,
                 NULL,
                 0,
                 0,
                 rc.right-rc.left,
                 rc.bottom-rc.top,
                 SWP_NOACTIVATE | SWP_NOMOVE);

    goto RETURN_SUCCESS;

ERROR_OPENING:                // display generic error message

    Message(0, "Error opening %s", (LPSTR) gachFileName);
    FileNew(FILE_DONT_PROMPT_FOR_SAVE | FILE_DONT_UPDATE_CAPTION);
    goto RETURN_ERROR;

RETURN_ERROR:                // do error exit without error message

    fOK = FALSE;

RETURN_SUCCESS:                // normal exit

    if (hcurPrev != NULL)
        SetCursor(hcurPrev);

    if (fh >= 0)
        _lclose(fh);

    UpdateCaption();

    return fOK;
}


/* fOK = FileSave(fSaveAs)
 *
 * Do a File/Save operation (if <fSaveAs> is FALSE) or a File/SaveAs
 * operation (if <fSaveAs> is TRUE).  Return TRUE unless the user cancelled
 * or the operation failed.
 */
BOOL FileSave(WORD wFlags)
{
    BOOL        fOK = TRUE;    // function succeeded?
    int        fh = -1;    // DOS file handle
    char        achFileName[_MAX_PATH]; // user-specified file name
    HCURSOR        hcurPrev = NULL; // cursor before hourglass
    FILEHEADER FileHead;
    RECT rc;
    POBJECT pObj;

    dprintf2("FileSave");

    if ((wFlags & FILE_SAVE_AS) || gfUntitled)
    {
        /* set up the default file name */
        if (gfUntitled)
            achFileName[0] = 0;
        else
            lstrcpy(achFileName, gachFileName);

        /* prompt the user for the name of the file to save to */
        if (!PromptForFileName(ghwndMain, 
                               ghAppInstance,
                               achFileName,
                               sizeof(achFileName), 
                               "Save File",
                               szOpenFilter,
                               "OA1",
                               PFFN_SAVEFILE | PFFN_SHOWDEFAULT |
                                PFFN_OVERWRITEPROMPT | PFFN_UPPERCASE))
            goto RETURN_ERROR;

        /* switch to the new file name */
        lstrcpy(gachFileName, achFileName);
        gfUntitled = FALSE;
        UpdateCaption();
    }

    /* show hourglass cursor */
    hcurPrev = SetCursor(LoadCursor(NULL, IDC_WAIT));

    /* open the file -- if it already exists, truncate it to zero bytes */
    if ((fh = _lcreat(gachFileName, 0)) < 0)
        goto ERROR_SAVING;

    /* write the file... */

    //
    // Create and write out a file header
    //

    FileHead.dwMagic = FILEMAGIC;
    GetClientRect(ghwndMain, &rc);
    FileHead.iWidth = rc.right - rc.left + 1;
    FileHead.iHeight = rc.bottom - rc.top + 1;

    dprintf3(" writing file header");
    if (_lwrite(fh, &FileHead, sizeof(FILEHEADER)) != sizeof(FILEHEADER)) {
        goto ERROR_SAVING;
    }

    //
    // For each object in the list write its object structure
    // followed by its data.
    // BUGBUG: We only support 64k objects - no bigger
    //

    pObj = gpObjList;
    while (pObj) {

        dprintf3(" writing object header");
        if (_lwrite(fh, pObj, sizeof(OBJECT)) != sizeof(OBJECT)) {
            goto ERROR_SAVING;
        }

        dprintf3(" writing %u bytes of object data", pObj->uiSize);
        if (_lwrite(fh, 
                    pObj->pInfo, 
                    pObj->uiSize) != pObj->uiSize) {
            goto ERROR_SAVING;
        }

        pObj = pObj->pNext;
    }

    goto RETURN_SUCCESS;

ERROR_SAVING:                // display generic error message

    Message(0, "Error saving %s", (LPSTR) gachFileName);
    goto RETURN_ERROR;

RETURN_ERROR:                // do error exit without error message

    fOK = FALSE;

RETURN_SUCCESS:                // normal exit

    if (hcurPrev != NULL)
        SetCursor(hcurPrev);

    if (fh >= 0)
        _lclose(fh);
    if (fOK)
        gfDirty = FALSE;

    return fOK;
}


/* fOK = PromptForFileName(hwndOwner, hInst, achFileName, cchFileName,
 *                         idCaption, idFilter, idDefExt, dwFlags)
 *
 * Prompt the user for the name of a file to open or save to.  <hwndOwner>
 * is the window that will own the dialog.  <hInst> is the module that the
 * string resources and RCDATA resource (see below) will be loaded from.
 *
 * The returned file name will be placed in <achFileName>, which must
 * have a capacity of at least <cchFileName> bytes.
 *
 * <idCaption> is the string resource id of the caption to display.
 * <idFilter> is the RCDATA resource id that contains the filter spec
 * (in the format used by COMMDLG).  <idDefExt> is the string resource id
 * of the default extension (without the period).  Any or all of these
 * three parameters may be NULL, for default behaviour.
 *
 * <dwFlags> are used as follows:
 *   -- PFFN_OPENFILE: prompt the user for the name of a file to open
 *   -- PFFN_SAVEFILE: prompt the user for the name of a file to save to
 *   -- PFFN_SHOWDEFAULT: on entry, <achFileName> will contain the name
 *      of a file to display as the "default file name"
 *   -- PFFN_OVERWRITEPROMPT: prompt the user before accepting allowing them
 *      to choose an existing file
 *   -- PFFN_UPPERCASE: make <achFileName> uppercase before returning
 */
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
