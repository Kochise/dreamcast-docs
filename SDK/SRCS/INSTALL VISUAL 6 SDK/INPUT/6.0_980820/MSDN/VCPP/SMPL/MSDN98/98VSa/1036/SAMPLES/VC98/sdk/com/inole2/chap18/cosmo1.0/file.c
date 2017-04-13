/*
 * FILE.C
 *
 * Functions for handling dirty files and processing File menu commands.
 *
 * Functions:
 *  FDirtySet, FCleanVerify
 *  FFileNew, FFileOpen, FFileSave, FFileSaveAs, FFileExit
 *
 * This file contains the only functions that manipulate the fDirty flag.
 *
 * Copyright(c) Microsoft Corp. 1992-1994 All Rights Reserved
 * Win32 version, January 1994
 */


#include <windows.h>
#include <ole.h>
#include "cosmo.h"
#include "oleglobl.h"





/*
 * FDirtySet
 *
 * Purpose:
 *  Sets or clears the global 'dirty' flag returning the previous state
 *  of that same flag.  Even though the non-OLE part of this function
 *  is trivial, it isolates handling changes, providing a single point
 *  to notify a client app with OLE_CHANGED.
 *
 *  This function does exits if pGlob->fNoDirty is set.
 *
 * Parameters:
 *  fDirty          BOOL used to set the value of the pGLob->fDirty flag.
 *                  This allows us to use this function to both set and
 *                  clear the flag.  OLE_CHANGED is only sent if the
 *                  flag is set to TRUE.
 *
 * Return Value:
 *  BOOL            Previous value of the dirty flag.
 */

BOOL WINAPI FDirtySet(BOOL fDirty)
    {
    BOOL        fPrevious;

#ifdef MAKEOLESERVER
    /*
     * If we are a hidden window, then there's nothing that could make
     * us dirty since there cannot be any user interaction here.  Therefore
     * ignore any changes to the dirty flag, leaving it FALSE.
     */
    if (!IsWindowVisible(pGlob->hWnd))
        return pGlob->fDirty;

#endif //MAKEOLESERVER

    if (pGlob->fNoDirty)
        return pGlob->fDirty;

    fPrevious=pGlob->fDirty;
    pGlob->fDirty=fDirty;

#ifdef MAKEOLESERVER
    if (fDirty)
        //Fun indirection, huh?  That what you get with an OOP.
        OLEClientNotify(pOLE->pSvr->pDoc->pObj, OLE_CHANGED);
#endif //MAKEOLESERVER

    return fPrevious;
    }





/*
 * FCleanVerify
 *
 * Purpose:
 *  Checks the pGLob->fDirty flag, and if set, displays a message
 *  box informing the user that the file is dirty and asking if
 *  the file should be saved or updated.  If YES is chosen, the file
 *  is saved or updated.
 *
 * Parameters:
 *  pGlob           LPGLOBALS to global variable block.
 *
 * Return Value:
 *  BOOL            TRUE if it's safe to proceed with the operation (file
 *                  is clean, user answered NO, or file was saved).
 *                  FALSE if the user wants to cancel the operation or there
 *                  was an error.
 */

BOOL WINAPI FCleanVerify(LPGLOBALS pGlob)
    {
    BOOL        fRet=TRUE;
    UINT        uRet;
    char       *psz;

#ifdef MAKEOLESERVER
    char        szClient[40];
#endif //MAKEOLESERVER

    //Nothing to do if we're clean.
    if (!pGlob->fDirty)
        return TRUE;

    if (!pGlob->fOLE)
        {
        uRet=MessageBox(pGlob->hWnd, rgpsz[IDS_FILEDIRTY]
            , rgpsz[IDS_CAPTION], MB_YESNOCANCEL | MB_ICONEXCLAMATION);
        }
#ifdef MAKEOLESERVER
    if (pGlob->fOLE)
        {
        //Linking case, use the same message as before.
        if (pOLE->pSvr->fLink)
            {
            uRet=MessageBox(pGlob->hWnd, rgpsz[IDS_FILEDIRTY],
                            rgpsz[IDS_CAPTION], MB_YESNOCANCEL);
            }

        //Embedding: Ask the user about updating instead of saving.
        if (pOLE->pSvr->fEmbed)
            {
            //Build the standard string for Updating.
            psz=(PSTR)LocalAlloc(LPTR, 1024);

            if (NULL==psz)
                return FALSE;

            GetAtomName(pOLE->pSvr->pDoc->aClient, szClient, sizeof(szClient));

            lstrcpy(psz, rgpsz[IDS_CLOSEALERT1]);
            lstrcat(psz, szClient);
            lstrcat(psz, rgpsz[IDS_CLOSEALERT2]);

            uRet=MessageBox(pGlob->hWnd, psz, rgpsz[IDS_CAPTION],
                            MB_YESNOCANCEL | MB_ICONEXCLAMATION);

            LocalFree((HLOCAL)psz);
            }
        }
#endif //MAKEOLESERVER

    switch (uRet)
        {
        case IDCANCEL:
            fRet=FALSE;
            break;

        case IDNO:
            fRet=TRUE;
            break;

        case IDYES:
            if (!pGlob->fOLE)
                fRet=FFileSave(pGlob);

#ifdef MAKEOLESERVER
            //Linking same as stand-alone.
            if (pOLE->pSvr->fLink)
                fRet=FFileSave(pGlob);

            if (pOLE->pSvr->fEmbed)
                OLEClientNotify(pOLE->pSvr->pDoc->pObj, OLE_CLOSED);

#endif //MAKEOLESERVER
            break;
        }

    return fRet;
    }






/*
 * FFileNew
 *
 * Purpose:
 *  Confirms the new file with the user and cleans out the Polyline
 *  image.
 *
 * Parameters:
 *  pGlob           LPGLOBALS to the global variable block.
 *
 * Return Value:
 *  BOOL            TRUE if the function succeeded, FALSE otherwise.
 *
 */

BOOL WINAPI FFileNew(LPGLOBALS pGlob)
    {
    if (!FCleanVerify(pGlob))
        return FALSE;

#ifdef MAKEOLESERVER
    PDocRevokeAndCreate(pOLE);
#endif //MAKEOLESERVER

    pGlob->fOLE=FALSE;

    SendMessage(pGlob->hWndPolyline, PLM_POLYLINENEW, 0, 0L);
    pGlob->fDirty=FALSE;
    pGlob->fOpenFile=FALSE;

    WindowTitleSet(pGlob->hWnd, rgpsz[IDS_UNTITLED]);
    return TRUE;
    }




/*
 * FFileOpen
 *
 * Purpose:
 *  Confirms that the user wants to open a new file and invokes the
 *  common dialog file open to get the filename, then reads the
 *  contents of the file.  If the fImport flag is TRUE, then we
 *  import the contents of the file into the current document,
 *  not changing the document name or any of the UI.
 *
 * Parameters:
 *  pGlob           LPGLOBALS to the global variable block.
 *  fImport         BOOL indicates if we're importing from a file,
 *                  not affecting the current filename.
 *
 * Return Value:
 *  BOOL            TRUE if the function succeeded, FALSE otherwise.
 *
 */

BOOL WINAPI FFileOpen(LPGLOBALS pGlob, BOOL fImport)
    {
    POLYLINE        pl;
    BOOL            fOK;
    LPSTR           psz;
    char            szTemp[CCHPATHMAX];
    LPSTR           pszFile;

    if (!fImport)
        {
        if (!FCleanVerify(pGlob))
            return FALSE;
        }

    psz=(fImport) ? rgpsz[IDS_FILEIMPORT] : rgpsz[IDS_FILEOPEN];

    //We have to use a temp for Import or else we'll wipe out a real filename.
    pszFile=(fImport) ? (LPSTR)szTemp : (LPSTR)pGlob->szFile;

    fOK=FSaveOpenDialog(pGlob->hWnd, pGlob->hInst, rgpsz[IDS_DEFEXT]
        , rgpsz[IDS_FILEOPENFILTER], pszFile, psz, TRUE);


    if (fOK)
        {
        //Attempt to read the file in and display it.
        if (!FCosFileRead(pGlob, pszFile, &pl))
            return FALSE;

#ifdef MAKEOLESERVER
        if (!fImport)
            PDocRevokeAndCreate(pOLE);
#endif //MAKEOLESERVER

        SendMessage(pGlob->hWndPolyline, PLM_POLYLINESET,
                    TRUE, (LONG)(LPSTR)&pl);

        if (!fImport)
            {
            WindowTitleSet(pGlob->hWnd, pszFile);
            pGlob->fOLE=FALSE;

            pGlob->fOpenFile=TRUE;
            pGlob->fDirty=FALSE;
            }
        else
            pGlob->fDirty=TRUE;
        }

    return fOK;
    }






/*
 * FFileSave
 *
 * Purpose:
 *  Writes the file to a known filename, requiring that the user has
 *  previously used FileOpen or FileSaveAs in order to have a filename.
 *
 * Parameters:
 *  pGlob           LPGLOBALS to the global variable block.
 *
 * Return Value:
 *  BOOL            TRUE if the function succeeded, FALSE otherwise.
 *
 */

BOOL WINAPI FFileSave(LPGLOBALS pGlob)
    {
    POLYLINE        pl;

#ifdef MAKEOLESERVER
    OLESTATUS       os;

    //In OLE cases, this may be Update; call OleSavedServerDoc
    if (pGlob->fOLE)
        {
        if (pOLE->pSvr->fLink)
            {
            SendMessage(pGlob->hWndPolyline, PLM_POLYLINEGET, 0,
                        (LONG)(LPSTR)&pl);

            if (!FCosFileWrite(pGlob, pGlob->szFile, &pl))
                return FALSE;
            }

        //This notifies the client for us.
        os=OleSavedServerDoc(pOLE->pSvr->pDoc->lh);

        pGlob->fDirty=(BOOL)(OLE_OK!=os);
        return !pGlob->fDirty;
        }

#endif //MAKEOLESERVER

    if (!pGlob->fOpenFile)
        return FFileSaveAs(pGlob);

    SendMessage(pGlob->hWndPolyline, PLM_POLYLINEGET, 0, (LONG)(LPSTR)&pl);

    if (!FCosFileWrite(pGlob, pGlob->szFile, &pl))
        return FALSE;

    pGlob->fOpenFile=TRUE;
    pGlob->fDirty=FALSE;
    return TRUE;
    }






/*
 * FFileSaveAs
 *
 * Purpose:
 *  Invokes the common dialog for Save As to get a filename then
 *  writes the polyline data to that file, creating if necessary.
 *
 * Parameters:
 *  pGlob           LPGLOBALS to the global variable block.
 *
 * Return Value:
 *  BOOL            TRUE if the function succeeded, FALSE otherwise.
 *
 */

BOOL WINAPI FFileSaveAs(LPGLOBALS pGlob)
    {
    POLYLINE        pl;
    BOOL            fOK;

    fOK=FSaveOpenDialog(pGlob->hWnd, pGlob->hInst, rgpsz[IDS_DEFEXT]
        , rgpsz[IDS_FILEOPENFILTER], pGlob->szFile, rgpsz[IDS_FILESAVEAS]
        , FALSE);

    if (fOK)
        {
        SendMessage(pGlob->hWndPolyline, PLM_POLYLINEGET
            , 0, (LONG)(LPSTR)&pl);

        fOK=FCosFileWrite(pGlob, pGlob->szFile, &pl);

#ifdef MAKEOLESERVER
        /*
         * In the Save Copy As case, when an object is embedded, we
         * don't need to call Rename or Saved since we just saved a
         * silent copy of the data.
         */
        if (pGlob->fOLE && pOLE->pSvr->fEmbed)
            return fOK;

        if (fOK && pGlob->fOLE && pOLE->pSvr->fLink)
            {
            OleRenameServerDoc(pOLE->pSvr->pDoc->lh, pGlob->szFile);
            OleSavedServerDoc(pOLE->pSvr->pDoc->lh);
            }
#endif //MAKEOLESERVER

        pGlob->fOpenFile=fOK;
        WindowTitleSet(pGlob->hWnd, pGlob->szFile);
        pGlob->fDirty=FALSE;
        }

    return fOK;
    }



/*
 * FFileExit
 *
 * Purpose:
 *  Handles the File/Exit menu command, verifying dirty files as necessary
 *  and revoking the server.
 *
 * Parameters:
 *  pGlob           LPGLOBALS to the global variable block.
 *
 * Return Value:
 *  BOOL            TRUE if the application can exit, FALSE otherwise.
 */

BOOL WINAPI FFileExit(LPGLOBALS pGlob)
    {
    BOOL            fRet;
#ifdef MAKEOLESERVER
    OLESTATUS       os;
    LHSERVER        lhT;
#endif //MAKEOLESERVER

    if (!FCleanVerify(pGlob))
        return FALSE;

#ifdef MAKEOLESERVER
    lhT=pOLE->pSvr->lh;
    pOLE->pSvr->lh=0L;
    os=OleRevokeServer(lhT);

    if (OLE_WAIT_FOR_RELEASE==os)
        {
        pOLE->pSvr->fRelease=FALSE;
        FOLEReleaseWait(&pOLE->pSvr->fRelease, lhT);
        fRet=TRUE;
        }
    else
        fRet=(OLE_OK==os);
#endif //MAKEOLESERVER

    return fRet;
    }
