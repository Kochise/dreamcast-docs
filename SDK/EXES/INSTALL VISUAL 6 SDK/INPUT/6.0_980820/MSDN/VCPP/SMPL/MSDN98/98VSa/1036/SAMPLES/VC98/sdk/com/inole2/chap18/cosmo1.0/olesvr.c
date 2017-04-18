/*
 * OLESVR.C
 *
 * Contains all callback functions in the OLESERVERVTBL struture:
 *      ServerCreate
 *      ServerCreateFromTemplate
 *      ServerEdit
 *      ServerExecute
 *      ServerExit
 *      ServerOpen
 *      ServerRelease
 *
 * Also includes the constructor function PServerAllocate.
 *
 * Copyright(c) Microsoft Corp. 1992-1994 All Rights Reserved
 * Win32 version, January 1994
 */


#ifdef MAKEOLESERVER

#include <windows.h>
#include <ole.h>
#include "cosmo.h"
#include "oleglobl.h"



/*
 * PServerAllocate
 *
 * Purpose:
 *  Allocates a COSMOSERVER structure and sets the defaults in its fields.
 *  Used from application initialization.
 *
 * Parameters:
 *  pVtblSvr        LPOLESERVERVTBL used to initialize the pvtbl field.
 *
 * Return Value:
 *  LPCOSMOSERVER   Pointer to the allocated structure in local memory.
 *                  The hMem field will contain a handle to the structure
 *                  to pass to LocalFree.
 *
 */

LPCOSMOSERVER WINAPI PServerAllocate(LPOLESERVERVTBL pVtblSvr)
    {
    HLOCAL            hMem;
    LPCOSMOSERVER     pSvr;

    hMem=LocalAlloc(LPTR, CBCOSMOSERVER);

    if (NULL==hMem)
        return FALSE;

    pSvr=(LPCOSMOSERVER)(PSTR)hMem;

    //All fields are initially NULL from LMEM_ZEROINIT.
    pSvr->hMem=hMem;
    pSvr->pvtbl=pVtblSvr;
    pSvr->fRelease=TRUE;            //Indicate a released state.

    return pSvr;
    }



/*
 * ServerCreate
 *
 * Purpose:
 *  Creates a new object of the class in pszClass which will be
 *  embedded in a client application document whose name is in
 *  pszDoc.
 *
 * Parameters:
 *  pSvr            LPCOSMOSERVER to structure identifying the server.
 *  lhDoc           LHSERVERDOC identifying the document.
 *  pszClass        OLE_LPCSTR specifying the class of document to create.
 *  pszDoc          OLE_LPCSTR specifying the document for use in window titles.
 *  ppServerDoc     LPLPOLESERVERDOC in which to store a pointer
 *                  to the OLESERVERDOC structure for this new document.
 *
 * Return Value:
 *  OLESTATUS       OLE_OK if all is well, otherwise an OLE_* error value.
 */

OLESTATUS WINAPI ServerCreate(LPCOSMOSERVER pSvr, LHSERVERDOC lhDoc
    , OLE_LPCSTR pszClass, OLE_LPCSTR pszDoc, LPLPOLESERVERDOC ppServerDoc)
    {
    LPCOSMODOC      pDoc;

    /*
     * 1.   Create a document of the specified class.
     * 2.   Allocate and initialize an OLESERVERDOC structure.
     * 3.   Store lhDoc in the OLESERVERDOC structure.
     * 4.   Store a pointer to the new OLESERVERDOC structure in ppServerDoc.
     * 5.   Return OLE_OK if successful, OLE_ERROR_NEW otherwise.
     */

    /*
     * If this were an MDI application, then we would want to create
     * a new window and a new document, including a new OLESERVERDOC
     * structure.  The protocol supports this, however, this application
     * is single-document.
     */

    pDoc=PDocumentAllocate(&pOLE->vtblDoc);

    if ((LPCOSMODOC)NULL==pDoc)
        return OLE_ERROR_NEW;

    pSvr->pDoc=pDoc;

    pDoc->lh=lhDoc;
    *ppServerDoc=(LPOLESERVERDOC)pDoc;
    return OLE_OK;
    }




/*
 * ServerCreateFromTemplate
 *
 * Purpose:
 *  Creates a new document initialized with the data in a specified
 *  file.  Thw new document is opened for editing and is embedded
 *  within the client when the server is updated or closed.
 *
 * Parameters:
 *  pSvr            LPCOSMOSERVER to structure identifying the server.
 *  lhDoc           LHSERVERDOC identifying the document.
 *  pszClass        OLE_LPCSTR specifying the class of document to create.
 *  pszDoc          OLE_LPCSTR to the permanent name of the document to open.
 *  pszTemp         OLE_LPCSTR to the file to use as a template.
 *  ppServerDoc     LPLPOLESERVERDOC in which to store a pointer
 *                  to the OLESERVERDOC structure for this new document.
 *
 * Return Value:
 *  OLESTATUS       OLE_OK if all is well, otherwise an OLE_* error value.
 */

OLESTATUS WINAPI ServerCreateFromTemplate(LPCOSMOSERVER pSvr
    , LHSERVERDOC lhDoc, OLE_LPCSTR pszClass, OLE_LPCSTR pszDoc
    , OLE_LPCSTR pszTemp, LPLPOLESERVERDOC ppServerDoc)
    {
    POLYLINE        pl;
    LPCOSMODOC      pDoc;

    /*
     * 1.   Create a document of the specified class.
     * 2.   Read the contents of the specified file and initialize the document.
     * 3.   Allocate and initialize an OLESERVERDOC structure.
     * 4.   Store lhDoc in the OLESERVERDOC structure.
     * 5.   Store a pointer to the new OLESERVERDOC structure in ppServerDoc.
     * 6.   Return OLE_OK if successful, OLE_ERROR_TEMPLATE otherwise.
     */

    //pszTemp contains a filename.
    if (!FCosFileRead(pGlob, (LPSTR)pszTemp, &pl))
        return OLE_ERROR_TEMPLATE;

    pDoc=PDocumentAllocate(&pOLE->vtblDoc);

    if ((LPCOSMODOC)NULL==pDoc)
        return OLE_ERROR_TEMPLATE;

    pSvr->pDoc=pDoc;

    pDoc->lh=lhDoc;
    *ppServerDoc=(LPOLESERVERDOC)pDoc;

    SendMessage(pGlob->hWndPolyline, PLM_POLYLINESET, TRUE, (LONG)(LPSTR)&pl);

    //The titles in this window will be set later through SetHostNames.
    pGlob->fOpenFile=TRUE;
    return OLE_OK;
    }




/*
 * ServerEdit
 *
 * Purpose:
 *  Creates a document initialized with data from a subsequent call
 *  to the SetData function.  The object is embedded in the client
 *  application and the server is not visible.
 *
 * Parameters:
 *  pSvr            LPCOSMOSERVER to structure identifying the server.
 *  lhDoc           LHSERVERDOC identifying the document.
 *  pszClass        OLE_LPCSTR specifying the class of document to create.
 *  pszDoc          OLE_LPCSTR specifying the document for use in window titles.
 *  ppServerDoc     LPLPOLESERVERDOC in which to store a pointer
 *                  to the OLESERVERDOC structure for this new document.
 *
 * Return Value:
 *  OLESTATUS       OLE_OK if all is well, otherwise an OLE_* error value.
 */

OLESTATUS WINAPI ServerEdit(LPCOSMOSERVER pSvr, LHSERVERDOC lhDoc
    , OLE_LPCSTR pszClass, OLE_LPCSTR pszDoc, LPLPOLESERVERDOC ppServerDoc)
    {
    LPCOSMODOC      pDoc;

    /*
     * This is the same as Open, but tells the server to expect
     * a SetData call and that the server is initially hidden.
     *
     * 1.   Create a document of the specified class.
     * 2.   Allocate and initialize an OLESERVERDOC structure.
     * 3.   Store lhDoc in the OLESERVERDOC structure.
     * 4.   Store pointer to the new OLESERVERDOC structure in ppServerDoc.
     * 5.   Return OLE_OK if successful, OLE_ERROR_EDIT otherwise.
     */

    pDoc=PDocumentAllocate(&pOLE->vtblDoc);

    if ((LPCOSMODOC)NULL==pDoc)
        return OLE_ERROR_EDIT;

    pSvr->pDoc=pDoc;

    pDoc->lh=lhDoc;
    *ppServerDoc=(LPOLESERVERDOC)pDoc;

    return OLE_OK;
    }




/*
 * ServerExecute
 *
 * Purpose:
 *  Handles DDE Execute commands sent from the server library
 *  from the client application.  Not all applications need to support
 *  DDE Execute.
 *
 * Parameters:
 *  pSvr            LPCOSMOSERVER identifying the server closing.
 *  hCommands       HGLOBAL to memory containing the DDE execute
 *                  string.
 *
 * Return Value:
 *  OLESTATUS       OLE_OK if all is well, otherwise an OLE_* error value.
 *                  This functions returns OLE_ERROR_COMMAND to indicate
 *                  that it is not implemented.
 */

OLESTATUS WINAPI ServerExecute(LPCOSMOSERVER pSvr, HGLOBAL hCommands)
    {
    /*
     * 1.   Lock the hCommands handle to access the execute strings.
     * 2.   Parse and execute the commands as necessary.
     * 3.   DO NOT FREE hCommands.
     * 4.   Return OLE_OK if successful, OLE_ERROR_COMMAND otherwise.
     */

    return OLE_ERROR_COMMAND;
    }





/*
 * ServerExit
 *
 * Purpose:
 *  Instructs the server application to close documents and shut down.
 *
 * Parameters:
 *  pSvr            LPCOSMOSERVER identifying the server closing.
 *
 * Return Value:
 *  OLESTATUS       OLE_OK if all is well, otherwise an OLE_* error value.
 */

OLESTATUS WINAPI ServerExit(LPCOSMOSERVER pSvr)
    {

    /*
     * 1.   Hide the window to prevent any user interaction.
     * 2.   Call OleRevokeServer.  Ignore an OLE_WAIT_FOR_RELEASE return value.
     * 3.   Perform whatever action is necessary to cause the application
     *      to terminate, such as DestroyWindow.
     * 4.   Return OLE_OK if successful, OLE_ERROR_GENERIC otherwise.
     */

    ShowWindow(pGlob->hWnd, SW_HIDE);

    pSvr->fRelease=FALSE;
    OleRevokeServer(pSvr->lh);

    DestroyWindow(pGlob->hWnd);
    return OLE_OK;
    }





/*
 * ServerOpen
 *
 * Purpose:
 *  Opens an exiting file (document) and prepares the document for
 *  editing, generally done when a user double-clicks a linked
 *  object in the client.  Note that the server is hidden at this
 *  point.
 *
 * Parameters:
 *  pSvr            LPCOSMOSERVER to structure identifying the server.
 *  lhDoc           LHSERVERDOC identifying the document.
 *  pszDoc          OLE_LPCSTR to the permanent name of the document to
 *                  be opened.
 *  ppServerDoc     LPLPOLESERVERDOC in which to store a pointer
 *                  to the OLESERVERDOC structure for this new document.
 *
 * Return Value:
 *  OLESTATUS       OLE_OK if all is well, otherwise an OLE_* error value.
 */

OLESTATUS WINAPI ServerOpen(LPCOSMOSERVER pSvr, LHSERVERDOC lhDoc
    , OLE_LPCSTR pszDoc, LPLPOLESERVERDOC ppServerDoc)
    {
    POLYLINE        pl;
    LPCOSMODOC      pDoc;

    /*
     * 1.   Create a document of the specified class.
     * 2.   Read the contents of the specified file and initialize the document.
     * 3.   Save the filename of the loaded file with this document,
     *      if necessary.
     * 4.   Allocate and initialize an OLESERVERDOC structure.
     * 5.   Store lhDoc in the OLESERVERDOC structure.
     * 6.   Store a pointer to the new OLESERVERDOC structure in ppServerDoc.
     * 7.   Return OLE_OK if successful, OLE_ERROR_OPEN otherwise.
     */

    if (!FCosFileRead(pGlob, (LPSTR)pszDoc, &pl))
        return OLE_ERROR_OPEN;

    pDoc=PDocumentAllocate(&pOLE->vtblDoc);

    if ((LPCOSMODOC)NULL==pDoc)
        return OLE_ERROR_OPEN;

    //Save the document in the server for later access in ServerRelease.
    pSvr->pDoc=pDoc;

    pDoc->lh=lhDoc;
    *ppServerDoc=(LPOLESERVERDOC)pDoc;

    WindowTitleSet(pGlob->hWnd, (LPSTR)pszDoc);
    SendMessage(pGlob->hWndPolyline, PLM_POLYLINESET, TRUE, (LONG)(LPSTR)&pl);
    pGlob->fOpenFile=TRUE;

    return OLE_OK;
    }





/*
 * ServerRelease
 *
 * Purpose:
 *  Notifies a server that all connections to it have been closed and
 *  that the server application can terminate.  This function should
 *  change the state of a global flag that causes any PeekMessage
 *  waiting loop to exit.
 *
 * Parameters:
 *  pSvr            LPCOSMOSERVER identifying the server.
 *
 * Return Value:
 *  OLESTATUS       OLE_OK if all is well, otherwise an OLE_* error value.
 */

OLESTATUS WINAPI ServerRelease(LPCOSMOSERVER pSvr)
    {
    /*
     * 1.   Set a flag to indicate that Release has been called.
     * 2.   If the application is hidden, we must use ServerRelease to
     *      instruct the application to terminate, by posting a WM_CLOSE
     *      or otherwise effective message, then exit the method with OLE_OK.
     * 3.   Free any resources allocated for this server, like documents,
     *      but DO NOT free the OLESERVER structure itself.
     * 4.   Return OLE_OK if successful, OLE_ERROR_GENERIC otherwise.
     */

    pSvr->fRelease=TRUE;

    /*
     * If we are invisible when we get ServerRelease, that's a flag
     * to us meaning exit.  Posting a WM_CLOSE takes care of all
     * this.  Note that even though WM_CLOSE processing in COSMO.C
     * checks for a dirty file and asks to save if necessary, the
     * file cannot be dirty because there has been no chance for
     * the user to make any changes.
     *
     * ServerRelease may be called twice when the server is opened invisible
     * for an update of a client object.  In this case, we'll get
     * ServerRelease once, where we should post a message to terminate the
     * application.  The second time around we need to handle free resources
     * associated with the server.  We detect this through the validity
     * pOLE->pSvr->lh which we set to 0L in FFileExit before calling
     * OleRevokeServer.  0L in lh signals us that we're in the final
     * revoke and we can free documents.
     *
     */
    if (!IsWindowVisible(pGlob->hWnd) && 0L!=pOLE->pSvr->lh)
        {
        PostMessage(pGlob->hWnd, WM_CLOSE, 0, 0L);
        return OLE_OK;
        }

    /*
     * Free the document if we are closing from OleRevokeServer, not through
     * a client releasing the server.
     */
    if (0L==pOLE->pSvr->lh)
        {
        //Free the document we're holding.
        if (NULL!=pSvr->pDoc)
            {
            if (NULL!=pSvr->pDoc->hMem)
                LocalFree(pSvr->pDoc->hMem);
            }

        pSvr->pDoc=NULL;
        }

    return OLE_OK;
    }


#endif //MAKEOLESERVER
