/*
    store.c

    File new/open/close functions

    This uses the OLE2 structured storage system.

    A storage object is kept active all the time the application
    is open. This is rather different to the way we used MS-DOS
    file handles.

    The error handling here is very weak.  If anything goes wrong
    no cleanup is done.

*/

#include "global.h"


//
// local data
//

static char *szUntitled = "(Untitled)";
static char *szOpenFilter = "Bucket Files (*.bkt)\0*.bkt\0"
                            "\0";
static char *szCloseFilter = "Bucket Files (*.bkt)\0*.bkt\0"
                            "\0";
//
// Set the caption of the main window to show the current file name
//

void UpdateCaption(void)
{
    char achCaption[_MAX_PATH + 30]; // caption
    char achDrive[_MAX_DRIVE];    // drive
    char achDir[_MAX_DIR];    // directory path
    char achFname[_MAX_PATH];    // file name
    char achExt[_MAX_EXT];    // file name extension

    if (lstrlen(gachFileName)) {
        _splitpath(gachFileName, achDrive, achDir, achFname, achExt);
        lstrcat(achFname, achExt);
    } else {
        lstrcpy(achFname, "(untitled)");
    }

    wsprintf(achCaption, "%s - %s", (LPSTR) gszAppName, (LPSTR) achFname);
    SetWindowText(ghwndMain, achCaption);
}

//
// If the current data has changed, ask the user if they want to save it
// before we do something else like opening another file or exiting.
// Return TRUE if it's okay to continue, FALSE if the caller should cancel
// whatever it's doing.
// 

BOOL PromptToSave()
{
    WORD wID;
    char buf[256];

    if (!gfDirty) return TRUE;

    if (gachFileName && lstrlen(gachFileName)) {

        wsprintf(buf, "Save the changes to %s ?", (LPSTR)gachFileName);

    } else {

        wsprintf(buf, "Save the changes to %s ?", (LPSTR)szUntitled);
    }


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
// Create a new document and a new storage object.
// Flags:
//      FILE_PROMPT_FOR_SAVE
//      FILE_UPDATE_CAPTION
//

BOOL FileNew(WORD wFlags)
{
    HRESULT hResult;

    dprintf2("FileNew");

    if (wFlags & FILE_PROMPT_FOR_SAVE)
    {
        if (!PromptToSave()) return FALSE;
    }

    //
    // It's ok to blow away any existing data now.
    // Nuke the object list
    //

    while (gpObjList) DeleteObj(gpObjList);

    //
    // update state variables 
    //

    if (gpStorage) {
        gpStorage->lpVtbl->Release(gpStorage);
        gpStorage = NULL;       // no current storage
    }

    gfDirty = FALSE;        // document is not dirty yet

    //
    // Create the default storage object (as a temp file)
    //

    gachFileName[0] = '\0';
    hResult = StgCreateDocfile(NULL,
                               STGM_READWRITE | STGM_SHARE_EXCLUSIVE
                                | STGM_DIRECT | STGM_CREATE,
                               NULL,
                               &gpStorage);

    if (!MyTestOleResult(hResult)) {
        dprintf1("Failed to create %s as a temp. structured storage file (%8.8lXH)",
                 (LPSTR)gachFileName ,GetScode(hResult));
        gpStorage = NULL;
        return FALSE;
    }

    //
    // update the display 
    //

    if (wFlags & FILE_UPDATE_CAPTION) {
        UpdateCaption();
    }

    //
    // Repaint to remove any existing junk
    //

    InvalidateRect(ghwndMain, NULL, TRUE);
    return TRUE;
}



//
// FileOpen(szFileName)
//
// If <szFileName> is NULL, do a File/Open command.  Otherwise, open
// <szFileName>.  Return TRUE unless the user cancelled or the operation
// failed.
// Note that if the open succeeds, we will replace the current storage
// object with the one created here.
//

BOOL FileOpen(LPSTR szFileName)
{
    BOOL        fOK = TRUE;    // function succeeded?
    char        achFileName[_MAX_PATH]; // user-specified file name
    HCURSOR        hcurPrev = NULL; // cursor before hourglass
    FILEHEADER FileHead;
    OBJECT O;
    RECT rc;
    POBJECT pObj;
    HRESULT hResult;
    LPSTREAM pInfoStream = NULL;
    LPSTREAM pObjInfoStream = NULL;
    LPSTREAM pObjStream = NULL;
    LPSTORAGE pStor = NULL;
    LPSTORAGE pObjStorage;
    ULONG cb;
    char szStorageName[32];

    dprintf2("FileOpen");

    //
    // give the user a chance to save the current state
    //

    if (!PromptToSave()) {
        goto RETURN_ERROR; // they canceled the operation
    }

    //
    // See if we were supplied the file name and if not get 
    // one from the user
    //

    if (szFileName == NULL) {

        if (!PromptForFileName(ghwndMain, 
                               ghAppInstance, 
                               achFileName,
                               sizeof(achFileName), 
                               "Open File", 
                               szOpenFilter,
                               "txt",
                               PFFN_OPENFILE | PFFN_UPPERCASE)) {
            goto RETURN_ERROR;
        }
    } else {
        lstrcpy(achFileName, szFileName);
    }

    //
    // Set up a new document and as a side effect create a 
    // temporary storage object
    //

    if (!FileNew(0)) {
        goto RETURN_ERROR;
    }

    //
    // show hourglass cursor while we do the disk access
    //

    hcurPrev = SetCursor(LoadCursor(NULL, IDC_WAIT));

    //
    // open the file 
    //

    dprintf3("Opening %s", (LPSTR)achFileName);

    //
    // See if this is a valid storage file and if it is open it
    // and see if it's ours.  We don't support old DOS files here
    //

    if (StgIsStorageFile(achFileName) != S_OK) {

        dprintf1("%s is not a structured storage file", (LPSTR)achFileName);
        goto ERROR_OPENING;

    }

    //
    // try opening it as a structured storage file
    //

    hResult = StgOpenStorage(achFileName,
                             NULL,
                             STGM_READWRITE | STGM_SHARE_EXCLUSIVE
                                | STGM_DIRECT,
                             NULL,
                             NULL,
                             &pStor);

    if (!MyTestOleResult(hResult)) {
        dprintf1("Failed to open %s as a structured storage file (%8.8lXH)",
                 (LPSTR)achFileName, GetScode(hResult));
        goto ERROR_OPENING;
    }

    //
    // open the info stream and validate it's one of ours
    //
    
    hResult = pStor->lpVtbl->OpenStream(pStor,
                                        INFO_STREAM,
                                        NULL,
                                        STGM_READWRITE | STGM_SHARE_EXCLUSIVE
                                           | STGM_DIRECT,
                                        NULL,
                                        &pInfoStream);

    if (!MyTestOleResult(hResult)) {
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

    dprintf3(" reading object list");

    //
    // Open the object list stream and read it, loading each object
    // found in the list.
    //

    hResult = pStor->lpVtbl->OpenStream(pStor,
                                           OBJLIST_STREAM,
                                           NULL,
                                           STGM_READWRITE | STGM_SHARE_EXCLUSIVE
                                              | STGM_DIRECT,
                                           NULL,
                                           &pInfoStream);

    if (!MyTestOleResult(hResult)) {
        Message(0, "The structured storage file does not contain an %s stream",
                (LPSTR) OBJLIST_STREAM);
        goto ERROR_OPENING;
    }

    do {

        //
        // read a name from the object list
        //

        hResult = pInfoStream->lpVtbl->Read(pInfoStream,
                                            szStorageName,
                                            sizeof(szStorageName),
                                            &cb);

        if (!MyTestOleResult(hResult) || (cb != sizeof(szStorageName))) break;

        dprintf4("  found %s", (LPSTR)szStorageName);

        //
        // Open the object storage
        //

        hResult = pStor->lpVtbl->OpenStorage(pStor,
                                             szStorageName,
                                             NULL,
                                             STGM_READWRITE | STGM_SHARE_EXCLUSIVE
                                                | STGM_DIRECT,
                                             NULL,
                                             NULL,
                                             &pObjStorage);

        if (!MyTestOleResult(hResult)) {

            dprintf1("Failed to open %s", (LPSTR) szStorageName);
            goto ERROR_OPENING;

        }

        //
        // Open and read the object info stream
        //

        dprintf3(" reading object header");

        hResult = pObjStorage->lpVtbl->OpenStream(pObjStorage,
                                          INFO_STREAM,
                                          NULL,
                                           STGM_READWRITE | STGM_SHARE_EXCLUSIVE
                                              | STGM_DIRECT,
                                          NULL,
                                          &pObjInfoStream);
    
        if (!MyTestOleResult(hResult)) {
            Message(0, "Failed to open %s stream (%8.8lXH)",
                    (LPSTR) INFO_STREAM,
                    GetScode(hResult));
            goto ERROR_OPENING;
        }
    
        //
        // read the info
        //
    
        hResult = pObjInfoStream->lpVtbl->Read(pObjInfoStream,
                                             &O,
                                             sizeof(O),
                                             &cb);
    
        //
        // close the stream
        //
    
        pObjInfoStream->lpVtbl->Release(pObjInfoStream);
    
        //
        // See if we got what we expected
        //
    
        if (cb != sizeof(O)) {
            dprintf1("Failed to read object info");
            goto ERROR_OPENING;
        }

        dprintf3(" loading object");

        //
        // Create one of our own objects to contain the OLE object
        //

        pObj = CreateObj(O.rc.left, O.rc.top,
                         O.rc.right - O.rc.left, O.rc.bottom - O.rc.top,
                         pObjStorage,
                         NULL,
                         NULL,
                         FROM_STORAGE);

        if (!pObj) goto ERROR_OPENING;

        lstrcpy(pObj->szStorageName, szStorageName);

        //
        // Close the object storage
        //

        pObjStorage->lpVtbl->Release(pObjStorage);

        //
        // Add it to our internal object list
        //

        AppendObj(pObj);

    } while (1);

    //
    // close the object list stream
    //

    pInfoStream->lpVtbl->Release(pInfoStream);

    gfDirty = FALSE;

    //
    // Get the next free object number
    //

    gdwNextObject = FileHead.dwNextObject;

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

    Message(0, "Error opening %s", (LPSTR) achFileName);
    FileNew(FILE_DONT_PROMPT_FOR_SAVE | FILE_DONT_UPDATE_CAPTION);
    goto RETURN_ERROR;

RETURN_ERROR:                // do error exit without error message

    fOK = FALSE;

RETURN_SUCCESS:                // normal exit

    if (hcurPrev != NULL) {
        SetCursor(hcurPrev); // restore the cursor
    }

    //
    // If we opened a structured storage file, set the caption
    // to the new name and blow away any old storage object
    //

    if (pStor) {
        if (gpStorage) {
            gpStorage->lpVtbl->Release(gpStorage);
        }
        gpStorage = pStor;
        lstrcpy(gachFileName, achFileName);
        UpdateCaption();
    }

    return fOK;
}


//
// Do a File/Save operation (if <fSaveAs> is FALSE) or a File/SaveAs
// operation (if <fSaveAs> is TRUE).  Return TRUE unless the user cancelled
// or the operation failed.
//

BOOL FileSave(WORD wFlags)
{
    BOOL        fOK = TRUE;    // function succeeded?
    char        achFileName[_MAX_PATH]; // user-specified file name
    HCURSOR        hcurPrev = NULL; // cursor before hourglass
    FILEHEADER FileHead;
    RECT rc;
    POBJECT pObj;
    HRESULT hResult;
    LPSTORAGE pStor = NULL;
    LPSTREAM pInfoStream = NULL;
    LPSTREAM pObjStream = NULL;
    ULONG cb;
    LPPERSISTSTORAGE pPersist;

    dprintf2("FileSave");

    if ((wFlags & FILE_SAVE_AS)
    || (gachFileName == NULL)
    || (!lstrlen(gachFileName))) {

        achFileName[0] = '\0';
        //
        // prompt the user for the name of the file to save to 
        //

        if (!PromptForFileName(ghwndMain, 
                               ghAppInstance,
                               achFileName,
                               sizeof(achFileName), 
                               "Save File",
                               szCloseFilter,
                               FILEEXT,
                               PFFN_SAVEFILE | PFFN_SHOWDEFAULT |
                                PFFN_OVERWRITEPROMPT | PFFN_UPPERCASE)) {
            dprintf1("Failed to get file name");
            goto RETURN_ERROR;
        }

        //
        // open the storage and if it already exists, truncate it to zero bytes
        //
    
        hResult = StgCreateDocfile(achFileName,
                                   STGM_READWRITE | STGM_SHARE_EXCLUSIVE
                                    | STGM_DIRECT | STGM_CREATE,
                                   NULL,
                                   &pStor);
    
        if (!MyTestOleResult(hResult)) {
            dprintf1("Failed to open/create %s as a structured storage file (%8.8lXH)",
                     (LPSTR)achFileName ,GetScode(hResult));
            goto ERROR_SAVING;
        }

        //
        // Copy all the stuff we have in the current storage object to
        // the new one
        //

        hResult = gpStorage->lpVtbl->CopyTo(gpStorage,
                                            NULL,
                                            NULL,
                                            NULL,
                                            pStor);
        if (!MyTestOleResult(hResult)) {
            Message(0, "Failed to copy temp info");
            goto ERROR_SAVING;
        }

        //
        // All the pStorage values of our objects are invalid now since
        // they are child storages of the storage we just closed so
        // we need to release and reopen each one - boring!
        //


        pObj = gpObjList;
        while (pObj) {

            if (pObj->pStorage) {
                pObj->pStorage->lpVtbl->Release(pObj->pStorage);
            }

            hResult = pStor->lpVtbl->OpenStorage(pStor,
                                             pObj->szStorageName,
                                             NULL,
                                             STGM_READWRITE | STGM_SHARE_EXCLUSIVE
                                                | STGM_DIRECT,
                                             NULL,
                                             NULL,
                                             &pObj->pStorage);

            if (!MyTestOleResult(hResult)) {
                dprintf1("Failed to re-open %s", (LPSTR) pObj->szStorageName);
            }
            pObj = pObj->pNext;
        }

    } else {
        pStor = gpStorage; // use the current one
    }

    //
    // show hourglass cursor 
    //

    hcurPrev = SetCursor(LoadCursor(NULL, IDC_WAIT));

    //
    // Create and write out the info stream
    //

    FileHead.dwMagic = FILEMAGIC;
    GetClientRect(ghwndMain, &rc);
    FileHead.iWidth = rc.right - rc.left + 1;
    FileHead.iHeight = rc.bottom - rc.top + 1;
    FileHead.dwNextObject = gdwNextObject;

    dprintf3(" writing file header");

    hResult = pStor->lpVtbl->CreateStream(pStor,
                                          INFO_STREAM,
                                          STGM_READWRITE | STGM_SHARE_EXCLUSIVE
                                           | STGM_DIRECT | STGM_CREATE,
                                          NULL,
                                          NULL,
                                          &pInfoStream);

    if (!MyTestOleResult(hResult)) {
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
    // Create and write out the object list stream
    //

    dprintf3(" writing object list");

    hResult = pStor->lpVtbl->CreateStream(pStor,
                                          OBJLIST_STREAM,
                                          STGM_READWRITE | STGM_SHARE_EXCLUSIVE
                                           | STGM_DIRECT | STGM_CREATE,
                                          NULL,
                                          NULL,
                                          &pInfoStream);

    if (!MyTestOleResult(hResult)) {
        Message(0, "Failed to create %s stream",
                (LPSTR) OBJLIST_STREAM);
        goto ERROR_SAVING;
    }

    //
    // walk down the object list saving the storage names
    //

    pObj = gpObjList;
    while (pObj) {

        hResult = pInfoStream->lpVtbl->Write(pInfoStream,
                                             pObj->szStorageName,
                                             sizeof(pObj->szStorageName),
                                             &cb);

        if (cb != sizeof(pObj->szStorageName)) {
            dprintf1("Failed to write object name");
            goto ERROR_SAVING;
        }

        pObj = pObj->pNext;
    }

    //
    // close the object list stream
    //

    pInfoStream->lpVtbl->Release(pInfoStream);

    //
    // for each object, we have open/create a storage and write
    // the object header and then ask the object to save itself
    //

    pObj = gpObjList;
    while (pObj) {

        dprintf3(" writing object header");

        hResult = pObj->pStorage->lpVtbl->CreateStream(pObj->pStorage,
                                              INFO_STREAM,
                                              STGM_READWRITE | STGM_SHARE_EXCLUSIVE
                                               | STGM_DIRECT | STGM_CREATE,
                                              NULL,
                                              NULL,
                                              &pInfoStream);
    
        if (!MyTestOleResult(hResult)) {
            dprintf1("Failed to create %s stream (%8.8lXH)",
                    (LPSTR) INFO_STREAM, GetScode(hResult));
            goto ERROR_SAVING;
        }
    
        //
        // write the info
        //
    
        hResult = pInfoStream->lpVtbl->Write(pInfoStream,
                                             pObj,
                                             sizeof(OBJECT),
                                             &cb);
    
        //
        // close the stream
        //
    
        pInfoStream->lpVtbl->Release(pInfoStream);
    
        //
        // See if we got what we expected
        //
    
        if (cb != sizeof(OBJECT)) {
            dprintf1("Failed to write info stream");
            goto ERROR_SAVING;
        }

        dprintf3(" saving object");

        //
        // Get a pointer to the OLE objects persistent storage interface
        //

        pPersist = (LPPERSISTSTORAGE) OleStdQueryInterface(
    	                (LPUNKNOWN) pObj->pOleObj,
                        &IID_IPersistStorage);

        if (!pPersist) {

            Message(0, "One of the OLE objects does not support being saved");

        } else {

            //
            // We use one of the OLE helper functions to perform
            // this particular piece of black magic.
            //
    
            hResult = OleSave(pPersist,
                                  pObj->pStorage,
                              TRUE);
    
            if (!MyTestOleResult(hResult)) {
                Message(0, "Failed to save OLE object");
                goto ERROR_SAVING;
            }
        }


        pObj = pObj->pNext;
    }

    //
    // make sure everything else is saved
    //

    gpStorage->lpVtbl->Commit(gpStorage, STGC_DEFAULT);



    goto RETURN_SUCCESS;

ERROR_SAVING:                // display generic error message

    Message(0, "Error saving %s", (LPSTR) gachFileName);

RETURN_ERROR:                // do error exit without error message

    dprintf1("Save failed");
    fOK = FALSE;

RETURN_SUCCESS:                // normal exit

    if (hcurPrev != NULL) {
        SetCursor(hcurPrev);
    }

    if ((wFlags & FILE_SAVE_AS) && pStor) {
        if (gpStorage) {
            gpStorage->lpVtbl->Release(gpStorage);
        }
        gpStorage = pStor;
        lstrcpy(gachFileName, achFileName);
        UpdateCaption();
    }

    if (fOK) {
        gfDirty = FALSE;
    }


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

    ASSERT(hInst);
    ASSERT(hwndOwner);

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

    if (!f) dprintf1("Dialog failed");


    /* make the name uppercase if requested */
    if (f && (dwFlags & PFFN_UPPERCASE))
        AnsiUpper(achFileName);

    return f;
}
