/*
 * OLEDOC.C
 *
 * Contains all callback functions in the OLESERVERDOCVTBL struture:
 *      DocClose
 *      DocGetObject
 *      DocExecute
 *      DocRelease
 *      DocSave
 *      DocSetColorScheme
 *      DocSetDocDimensions
 *      DocSetHostNames
 *
 * Also contains two helper functions, PDocumentAllocate and DocumentClean.
 * PDocumentAllocate acts like a C++ constructor.
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
 * PDocumentAllocate
 *
 * Purpose:
 *  Allocates a COSMODOC structure and sets the defaults in its fields.
 *  Used from application initialization and various server methods that
 *  create a document.
 *
 * Parameters:
 *  pVtblDoc        LPOLESERVERDOCVTBL used to initialize the pvtbl field.
 *
 * Return Value:
 *  LPCOSMODOC      Pointer to the allocated structure in local memory.
 *                  The hMem field will contain a handle to the structure
 *                  to pass to LocalFree.
 *
 */

LPCOSMODOC WINAPI PDocumentAllocate(LPOLESERVERDOCVTBL pVtblDoc)
    {
    HLOCAL      hMem;
    LPCOSMODOC  pDoc;

    hMem=LocalAlloc(LPTR, CBCOSMODOC);

    if (NULL==hMem)
        return NULL;

    pDoc=(LPCOSMODOC)(PSTR)hMem;

    pDoc->hMem=hMem;
    pDoc->fRelease=TRUE;
    pDoc->pvtbl=pVtblDoc;

    return pDoc;
    }




/*
 * DocClose
 *
 * Purpose:
 *  Instructs the server to unconditionally close the document.  OLESVR
 *  calls DocClose when the client initiates a shutdown.  OLESVR always
 *  calls this function before calling ServerRelease.
 *
 * Parameters:
 *  pDoc            LPCOSMODOC identifying the document affected.
 *
 * Return Value:
 *  OLESTATUS       OLE_OK if all is well, otherwise an OLE_* error value.
 */

OLESTATUS WINAPI DocClose(LPCOSMODOC pDoc)
    {
    OLESTATUS       os;

    /*
     * Take no action to notify user--Client will take care of that.
     *
     * 1.   Call OleRevokeServerDoc; resources are freed when OLESVR
     *      calls DocRelease.
     * 2.   Return the return value of OleRevokeServerDoc, which will
     *      generally be OLE_OK.
     */

    os=OleRevokeServerDoc(pDoc->lh);
    return os;
    }






/*
 * DocGetObject
 *
 * Purpose:
 *  Requests the server application to create an OLEOBJECT structure.
 *
 * Parameters:
 *  pDoc            LPCOSMODOC identifying the document affected.
 *  pszItem         OLE_LPCSTR specifying the name of the item in a document
 *                  for which the object is to be created.  If NULL, then
 *                  the entire document is requested.  This could be a
 *                  range of spreadsheet cells like "R1:C3-R10:C50"
 *  ppObj           LPLPOLEOBJECT at which to store a pointer to the
 *                  OLEOBJECT structure.
 *  pClient         LPOLECLIENT that should be associated with
 *                  the object in order to notify OLECLI when the object
 *                  changes.
 *
 * Return Value:
 *  OLESTATUS       OLE_OK if all is well, otherwise an OLE_* error value.
 */

OLESTATUS WINAPI DocGetObject(LPCOSMODOC pDoc, OLE_LPCSTR pszItem
    , LPLPOLEOBJECT ppObj, LPOLECLIENT pClient)
    {
    LPCOSMOOBJECT   pObj;

    /*
     * 1.   Allocate and initialize an OLEOBJECT structure.
     * 2.   Store pClient in the object's OLEOBJECT structure for use
     *      in sending notifications to the client.
     * 3.   Store a pointer to the new OLEOBJECT structure in ppObj.
     * 4.   Return OLE_OK if successful, OLE_ERROR_NAME if pszObj is
     *      not recognized, or OLE_ERROR_MEMORY if the object could not
     *      be allocated.
     *
     * This function is called in response to a client calling
     * OleGetObject.
     */

    //Allocate one from local FIXED memory.
    pObj=PObjectAllocate(&pOLE->vtblObj);

    if (NULL==pObj)
        return OLE_ERROR_MEMORY;

    //Remember who we created for freeing in DocRelease.
    pDoc->pObj=pObj;

    //Must save this for sending notifications.
    pObj->pClient=pClient;

    //Pass back the pointer to this object.
    *ppObj=(LPOLEOBJECT)pObj;
    return OLE_OK;
    }



/*
 * DocExecute
 *
 * Purpose:
 *  Passes DDE Execute strings related to the document to the server
 *  application.
 *
 * Parameters:
 *  pDoc            LPCOSMODOC identifying the document affected.
 *  hCommands       HGLOBAL to memory containing DDE execute strings.
 *
 * Return Value:
 *  OLESTATUS       OLE_OK if all is well, otherwise an OLE_* error value.
 */

OLESTATUS WINAPI DocExecute(LPCOSMODOC pDoc, HGLOBAL hCommands)
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
 * DocRelease
 *
 * Purpose:
 *  Notifies the server when a revoked document may be destroyed.
 *
 * Parameters:
 *  pDoc            LPCOSMODOC identifying the document affected.
 *
 * Return Value:
 *  OLESTATUS       OLE_OK if all is well, otherwise an OLE_* error value.
 */

OLESTATUS WINAPI DocRelease(LPCOSMODOC pDoc)
    {
    /*
     * 1.   Free any resources allocated for this document, but
     *      DO NOT free the OLESERVERDOC structure itself.  This could
     *      include freeing objects, however.
     * 2.   Set a flag to indicate that Release has been called.
     * 3.   Return OLE_OK if successful, OLE_ERROR_GENERIC otherwise.
     */

    if (0!=pDoc->aObject)
        {
        DeleteAtom(pDoc->aObject);
        pDoc->aObject=0;
        }

    if (0!=pDoc->aClient)
        {
        DeleteAtom(pDoc->aClient);
        pDoc->aClient=0;
        }


    //Release any object stored in this document.
    if (0!=pDoc->pObj)
        {
        if (NULL!=pDoc->pObj->hMem)
            LocalFree(pDoc->pObj->hMem);
        }

    pDoc->pObj=NULL;

    pDoc->fRelease=TRUE;
    return OLE_OK;
    }





/*
 * DocSave
 *
 * Purpose:
 *  Instructs the server application to save the document.  If DocSave is
 *  called you are assumed to have a know filename to which you can save
 *  since this method is only used in linking.
 *
 * Parameters:
 *  pDoc            LPCOSMODOC identifying the document affected.
 *
 * Return Value:
 *  OLESTATUS       OLE_OK if all is well, otherwise an OLE_* error value.
 */

OLESTATUS WINAPI DocSave(LPCOSMODOC pDoc)
    {
    /*
     * 1.   Save the document to the known filename.  How you save
     *      documents is application-specific.
     * 2.   Return OLE_OK if the save is successful, OLE_ERROR_GENERIC
     *      otherwise.
     */

    SendMessage(pGlob->hWnd, WM_COMMAND, IDM_FILESAVE, 0L);
    return OLE_OK;
    }





/*
 * DocSetColorScheme
 *
 * Purpose:
 *  Provides a color scheme that the client application recommends for
 *  rendering graphical data.
 *
 * Parameters:
 *  pDoc            LPCOSMODOC identifying the document affected.
 *  pPal            LPLOGPALETTE describing the recommended palette.
 *
 * Return Value:
 *  OLESTATUS       OLE_OK if all is well, otherwise an OLE_* error value.
 */

OLESTATUS WINAPI DocSetColorScheme(LPCOSMODOC pDoc
    , OLE_CONST LOGPALETTE FAR *pPal)
    {
    /*
     * Servers are not required to use this palette.  The LPLOGPALETTE
     * only is a convenient structure to contain the color scheme; IT DOES
     * not REPRESENT A PALETTE IN STRICT TERMS!  Do NOT call CreatePalette
     * and try to realize it.
     *
     * The color scheme contained in the LOGPALETTE structure contains
     * a number of colors where the first color is the suggested foreground,
     * the second the suggested background, then the first HALF of those
     * remaining are suggested fill colors and the last half suggested
     * line colors.  If there are an odd number of colors, give the extra
     * color to the fill colors, that is, there is one less line color than
     * fill colors.
     */

    return OLE_ERROR_PALETTE;
    }



/*
 * DocSetDocDimensions
 *
 * Purpose:
 *  Specifies the rectangle on the target device for which EMBEDDED
 *  objects should be formatted.
 *
 * Parameters:
 *  pDoc            LPCOSMODOC identifying the document affected.
 *  pRect           LPRECT to the device rectangle in MM_HIMETRIC units.
 *
 * Return Value:
 *  OLESTATUS       OLE_OK if all is well, otherwise an OLE_* error value.
 */

OLESTATUS WINAPI DocSetDocDimensions(LPCOSMODOC pDoc
    , OLE_CONST RECT FAR *pRect)
    {
    /*
     * OLESVR will call this method when the client has resized the
     * object.
     *
     * In this case we try to make the parent window the correct size
     * to just contain the object.
     */

    //First, convert the rectangle to units we can deal with MM_TEXT.
    RectConvertToDevice(pGlob->hWnd, (LPRECT)pRect);

    /*
     * Tell the Polyline document to use this rectangle, also notifying
     * the parent which will then resize itself.
     */
    SendMessage(pGlob->hWndPolyline, PLM_RECTSET, TRUE, (LONG)pRect);

    return OLE_OK;
    }





/*
 * DocSetHostNames
 *
 * Purpose:
 *  Set names that should be used for window titles, only for
 *  embedded objects; linked objects have their own titles as they
 *  are loaded through the server application's usual file loading
 *  mechanism.
 *
 * Parameters:
 *  pDoc            LPCOSMODOC identifying the document affected.
 *  pszClient       OLE_LPCSTR to the name of the client application.
 *  pszObj          OLE_LPCSTR to the name of the embedded object.
 *
 * Return Value:
 *  OLESTATUS       OLE_OK if all is well, otherwise an OLE_* error value.
 */

OLESTATUS WINAPI DocSetHostNames(LPCOSMODOC pDoc, OLE_LPCSTR pszClient
    , OLE_LPCSTR pszObj)
    {
    char        szTemp[256];

    /*
     * 1.   Change the title bar to reflect the embedded state with the
     *      appropriate names.
     * 2.   Change the File menu to reflect the embedded state and the name
     *      of the client application.
     * 3.   Store the object and client names in teh OLESERVERDOC structure.
     *      These will be needed later for message boxes where the name of
     *      the client application must be displayed.
     * 4.   Return OLE_OK if successful, OLE_ERROR_GENERIC otherwise.
     */

    wsprintf(szTemp, "%s in %s", pszObj, pszClient);
    WindowTitleSet(pGlob->hWnd, szTemp);
    MenuEmbeddingSet(pGlob->hWnd, (LPSTR)pszClient, TRUE);

    if (0!=pDoc->aObject)
        DeleteAtom(pDoc->aObject);

    pDoc->aObject=AddAtom(pszObj);

    if (0!=pDoc->aClient)
        DeleteAtom(pDoc->aClient);

    pDoc->aClient=AddAtom(pszClient);

    return OLE_OK;
    }





#endif //MAKEOLESERVER
