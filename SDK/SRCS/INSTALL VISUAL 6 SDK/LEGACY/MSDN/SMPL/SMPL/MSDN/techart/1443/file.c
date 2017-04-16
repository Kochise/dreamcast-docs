/*
    file.c

    File new/open/close functions

    This uses the OLE2 structured storage system.  The storage contains
    two streams from the root storage called INFO and TEXTOBJECTS.

    The INFO stream contains general info and the TEXTOBJECTS stream
    contains the packed object data.

*/

#include "global.h"


//
// local data
//

static char *szUntitled = "(Untitled)";
static char *szOpenFilter = "TBSS Files (*.tbs)\0*.tbs\0"
                            "Text Box Files (*.tbx)\0*.tbx\0"
                            "\0";
static char *szCloseFilter = "TBSS Files (*.tbs)\0*.tbs\0"
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
    HCURSOR        hcurPrev = NULL; // cursor before hourglass
    FILEHEADER FileHead;
    OBJECT O;
    RECT rc;
    LPSTR pMem;
    POBJECT pObj;
    int fh = -1;
    HRESULT hResult;
    LPSTORAGE pStorage = NULL;  // pointer to a storage object
    LPSTREAM pInfoStream = NULL;
    LPSTREAM pObjStream = NULL;
    ULONG cb;

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

    //
    // See if this is a valid storage file and if it is open it
    // and see if it's ours.  If not try opening it as a DOS file
    //

    if (StgIsStorageFile(gachFileName) != S_OK) {

        dprintf3("%s is not a structured storage file", (LPSTR)gachFileName);

        //
        // try opening it as a DOS file
        //

        if ((fh = _lopen(gachFileName, READ)) < 0) {
            dprintf1("Failed to open %s as a DOS file", (LPSTR)gachFileName);
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

    } else {

        //
        // try opening it as a structured storage file
        //

        hResult = StgOpenStorage(gachFileName,
                                 NULL,
                                 STGM_READ | STGM_SHARE_EXCLUSIVE
                                    | STGM_DIRECT,
                                 NULL,
                                 NULL,
                                 &pStorage);

        if (FAILED(hResult)) {
            dprintf1("Failed to open %s as a structured storage file (%8.8lXH)",
                     (LPSTR)gachFileName, GetScode(hResult));
            goto ERROR_OPENING;
        }

        //
        // open the info stream and validate it's one of ours
        //
    
        hResult = pStorage->lpVtbl->OpenStream(pStorage,
                                               INFO_STREAM,
                                               NULL,
                                               STGM_READ | STGM_SHARE_EXCLUSIVE
                                                  | STGM_DIRECT,
                                               NULL,
                                               &pInfoStream);

        if (FAILED(hResult)) {
            Message(0, "The structured storage file does not contain an %s stream",
                    (LPSTR) INFO_STREAM);
            goto ERROR_OPENING;
        }

        //
        // read the info stream and validate it
        //

        hResult = pInfoStream->lpVtbl->Read(pInfoStream,
                                            &FileHead,
                                            sizeof(FileHead),
                                            &cb);

        //
        // close the stream
        //

        pInfoStream->lpVtbl->Release(pInfoStream);

        //
        // See if we got what we expected
        //

        if (cb != sizeof(FileHead)) {
            dprintf1("Failed to read file header");
            goto ERROR_OPENING;
        }
        
        if (FileHead.dwMagic != FILEMAGIC) {
            Message(0, "File header missing or file is wrong type");
            goto ERROR_OPENING;
        }
        

        //
        // open the object data stream
        //
    
        hResult = pStorage->lpVtbl->OpenStream(pStorage,
                                               OBJECT_STREAM,
                                               NULL,
                                               STGM_READ | STGM_SHARE_EXCLUSIVE
                                                  | STGM_DIRECT,
                                               NULL,
                                               &pObjStream);

        if (FAILED(hResult)) {
            Message(0, "The structured storage file does not contain an %s stream",
                    (LPSTR) OBJECT_STREAM);
            goto ERROR_OPENING;
        }

        //
        // Try to read object headers and data until we fail
        //
        
        do {

            hResult = pObjStream->lpVtbl->Read(pObjStream,
                                               &O,
                                               sizeof(O),
                                               &cb);

            if (cb != sizeof(O)) {
                break;
            }

            dprintf3(" object header read");
            pMem = ALLOCATE(O.uiSize);
            if (!pMem) goto ERROR_OPENING;
        
            hResult = pObjStream->lpVtbl->Read(pObjStream,
                                               pMem,
                                               O.uiSize,
                                               &cb);

            if (cb != O.uiSize) {
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

        } while(1);

        //
        // Close the stream
        //
    
        pObjStream->lpVtbl->Release(pObjStream);

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

    if (pStorage) {
        pStorage->lpVtbl->Release(pStorage);
    }

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
    char        achFileName[_MAX_PATH]; // user-specified file name
    HCURSOR        hcurPrev = NULL; // cursor before hourglass
    FILEHEADER FileHead;
    RECT rc;
    POBJECT pObj;
    HRESULT hResult;
    LPSTORAGE pStorage = NULL;  // pointer to a storage object
    LPSTREAM pInfoStream = NULL;
    LPSTREAM pObjStream = NULL;
    ULONG cb;
    char achDrive[_MAX_DRIVE];    // drive
    char achDir[_MAX_DIR];    // directory path
    char achFname[_MAX_PATH];    // file name
    char achExt[_MAX_EXT];    // file name extension

    dprintf2("FileSave");

    if ((wFlags & FILE_SAVE_AS) || gfUntitled)
    {
        /* set up the default file name */
        if (gfUntitled) {
            achFileName[0] = 0;
        } else {
            lstrcpy(achFileName, gachFileName);
        }

        //
        // Change the extension to our default
        //

        _splitpath(achFileName, achDrive, achDir, achFname, achExt);
        _makepath(achFileName, achDrive, achDir, achFname, "TBS");

        /* prompt the user for the name of the file to save to */
        if (!PromptForFileName(ghwndMain, 
                               ghAppInstance,
                               achFileName,
                               sizeof(achFileName), 
                               "Save File",
                               szCloseFilter,
                               "TBS",
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

    //
    // open the storage and if it already exists, truncate it to zero bytes
    //

    hResult = StgCreateDocfile(gachFileName,
                               STGM_READWRITE | STGM_SHARE_EXCLUSIVE
                                | STGM_DIRECT | STGM_CREATE,
                               NULL,
                               &pStorage);

    if (FAILED(hResult)) {
        dprintf1("Failed to open/create %s as a structured storage file (%8.8lXH)",
                 (LPSTR)gachFileName ,GetScode(hResult));
        goto ERROR_SAVING;
    }

    /* write the file... */

    //
    // Create and write out the info stream
    //

    FileHead.dwMagic = FILEMAGIC;
    GetClientRect(ghwndMain, &rc);
    FileHead.iWidth = rc.right - rc.left + 1;
    FileHead.iHeight = rc.bottom - rc.top + 1;

    dprintf3(" writing file header");

    hResult = pStorage->lpVtbl->CreateStream(pStorage,
                                             INFO_STREAM,
                                             STGM_READWRITE | STGM_SHARE_EXCLUSIVE
                                              | STGM_DIRECT | STGM_CREATE,
                                             NULL,
                                             NULL,
                                             &pInfoStream);

    if (FAILED(hResult)) {
        Message(0, "Failed to create %s stream",
                (LPSTR) INFO_STREAM);
        goto ERROR_SAVING;
    }

    //
    // write the info
    //

    hResult = pInfoStream->lpVtbl->Write(pInfoStream,
                                         &FileHead,
                                         sizeof(FileHead),
                                         &cb);

    //
    // close the stream
    //

    pInfoStream->lpVtbl->Release(pInfoStream);

    //
    // See if we got what we expected
    //

    if (cb != sizeof(FileHead)) {
        dprintf1("Failed to write info stream");
        goto ERROR_SAVING;
    }

    //
    // open the object stream
    //

    hResult = pStorage->lpVtbl->CreateStream(pStorage,
                                             OBJECT_STREAM,
                                             STGM_READWRITE | STGM_SHARE_EXCLUSIVE
                                              | STGM_DIRECT | STGM_CREATE,
                                             NULL,
                                             NULL,
                                             &pObjStream);

    if (FAILED(hResult)) {
        Message(0, "Failed to create %s stream",
                (LPSTR) OBJECT_STREAM);
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

        hResult = pObjStream->lpVtbl->Write(pObjStream,
                                            pObj,
                                            sizeof(OBJECT),
                                            &cb);

        if (cb != sizeof(OBJECT)) {
            dprintf1("Failed to write object header");
            goto ERROR_SAVING;
        }

        dprintf3(" writing %u bytes of object data", pObj->uiSize);
        hResult = pObjStream->lpVtbl->Write(pObjStream,
                                            pObj->pInfo,
                                            pObj->uiSize,
                                            &cb);

        if (cb != pObj->uiSize) {
            dprintf1("Failed to write object data");
            goto ERROR_SAVING;
        }

        pObj = pObj->pNext;
    }

    //
    // close the stream
    //

    pInfoStream->lpVtbl->Release(pInfoStream);


    goto RETURN_SUCCESS;

ERROR_SAVING:                // display generic error message

    Message(0, "Error saving %s", (LPSTR) gachFileName);
    goto RETURN_ERROR;

RETURN_ERROR:                // do error exit without error message

    fOK = FALSE;

RETURN_SUCCESS:                // normal exit

    if (hcurPrev != NULL)
        SetCursor(hcurPrev);

    if (pStorage) 
        pStorage->lpVtbl->Release(pStorage);

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
