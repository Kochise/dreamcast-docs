/*
 * OLEOBJ.C
 *
 * Contains all callback functions in the OLEOBJECTVTBL struture:
 *      ObjDoVerb
 *      ObjEnumFormats
 *      ObjGetData
 *      ObjQueryProtocol
 *      ObjRelease
 *      ObjSetBounds
 *      ObjSetColorScheme
 *      ObjSetData
 *      ObjSetTargetDevice
 *      ObjShow
 *
 * There are additional callbacks in the OLEOBJECTVTBL.
 * Also contains PObjectAllocate, a constructor for the object.
 *
 * Copyright(c) Microsoft Corp. 1992-1994 All Rights Reserved
 * Win32 version, January 1994
 */

#ifdef MAKEOLESERVER

#include <windows.h>
#include <ole.h>
#include "cosmo.h"
#include "oleglobl.h"
#include "oleinst.h"    //OBJVERB_* defines for ObjDoVerb

/*
 * PObjectAllocate
 *
 * Purpose:
 *  Allocates a COSMOOBJECT structure and sets the defaults in its fields.
 *  Used from DocGetObject.
 *
 * Parameters:
 *  pVtblObj        LPOLESERVERDOCVTBL used to initialize the pvtbl field.
 *
 * Return Value:
 *  LPCOSMOOBJECT   Pointer to the allocated structure in local memory.
 *                  The hMem field will contain a handle to the structure
 *                  to pass to LocalFree.
 */

LPCOSMOOBJECT WINAPI PObjectAllocate(LPOLEOBJECTVTBL pVtblObj)
    {
    HLOCAL          hMem;
    LPCOSMOOBJECT   pObj;

    hMem=LocalAlloc(LPTR, sizeof(COSMOOBJECT));
    pObj=(LPCOSMOOBJECT)(PSTR)hMem;

    //Initialize the object.
    pObj->hMem=hMem;
    pObj->pvtbl=pVtblObj;
    pObj->fRelease=TRUE;

    return pObj;
    }




/*
 * ObjDoVerb
 *
 * Purpose:
 *  Performs actions on an object when the user opens an object
 *  according to the verb given.
 *
 * Parameters:
 *  pObj            LPCOSMOOBJECT specifying the object affected.
 *  iVerb           UINT index to the verb chosen, zero based.
 *  fShow           BOOL--TRUE if the application should show
 *                  itself with ShowWindow.  FALSE means no change.
 *  fFocus          BOOL--TRUE if the server should get the focus.
 *
 * Return Value:
 *  OLESTATUS       OLE_OK if all is well, otherwise an OLE_* error value.
 */

OLESTATUS WINAPI ObjDoVerb(LPCOSMOOBJECT pObj, UINT iVerb
    , BOOL fShow, BOOL fFocus)
    {
    /*
     * 1.   Execute the verb.
     *        a.  For a 'Play' verb, a server does not generally show
     *            its window or affect the focus.
     *
     *        b.  For an 'Edit' verb, show the server's window and the
     *            object if fShow is TRUE, and take the focus if fFocus
     *            is TRUE.  An ideal way to accomplish this is to call
     *            the ObjShow method through the OLEOBJECTVTBL since that
     *            method will handle showing the object and taking the
     *            focus itself.
     *
     *        c.  An 'Open' verb is not clearly defined; depending on the
     *            application it may mean the same as 'Play' or 'Edit.'
     *            The Cosmo server, if it had an 'Open' verb, would treat
     *            it like 'Edit.'
     *
     * 2.  Return OLE_OK if the verb was successfully executed, otherwise
     *     OLE_ERROR_DOVERB.
     */

    switch (iVerb)
        {
        case OBJVERB_EDIT:
            /*
             * On edit, simply show yourself and expect a SetData.
             * Best strategy is to use the Show method for this
             * object if necessary, reducing redundancy.
             */
            if (fShow)
                return (pObj->pvtbl->Show)((LPOLEOBJECT)pObj, fShow);

            //Return OLE_OK
            break;


        case OBJVERB_PLAY:
            //Unsupported at this time.
            return OLE_ERROR_DOVERB;

        default:
            return OLE_ERROR_DOVERB;
        }

    return OLE_OK;
    }





/*
 * ObjEnumFormats
 *
 * Purpose:
 *  Requests the server to produce the 'next' supported clipboard
 *  format.  Each format is returned in sequence until the terminator
 *  (a NULL) is returned.
 *
 * Parameters:
 *  pObj            LPCOSMOOBJECT specifying the object affected.
 *  cf              OLECLIPFORMAT the last clipboard format returned by
 *                  this function.  0 indicates the first.
 *
 * Return Value:
 *  OLESTATUS       OLE_OK if all is well, otherwise an OLE_* error value.
 */

OLECLIPFORMAT WINAPI ObjEnumFormats(LPCOSMOOBJECT pObj, OLECLIPFORMAT cf)
    {
    /*
     * 1.   Depending on cf, return the 'next' clipboard format in which
     *      the server can render the object's data.
     * 2.   If there are no more supported formats after the format in cf,
     *      return NULL.
     *
     * We must use multiple if's instead of a switch statement because
     * all the cf* values are not constants.
     */

    if (0==cf)
       return pOLE->cfNative;

    if (pOLE->cfNative==cf)
       return pOLE->cfOwnerLink;

    if (pOLE->cfOwnerLink==cf)
       return CF_METAFILEPICT;

    if (CF_METAFILEPICT==cf)
       return CF_BITMAP;

    if (CF_BITMAP==cf)
       return pOLE->cfObjectLink;

    //This IF is here just to be explicit.
    if (pOLE->cfObjectLink==cf)
       return 0;

    return 0;
    }






/*
 * ObjGetData
 *
 * Purpose:
 *  Retrieves data from the object in a specified format, where the
 *  server should allocate memory (GlobalAlloc with GMEM_DDESHARE),
 *  fill the memory, and return the handle.
 *
 * Parameters:
 *  pObj            LPCOSMOOBJECT specifying the object affected.
 *  cf              OLECLIPFORMAT format to return data in, may be "Native."
 *  phData          HGLOBAL FAR * in which to store the allocated handle.
 *
 * Return Value:
 *  OLESTATUS       OLE_OK if all is well, otherwise an OLE_* error value.
 */

OLESTATUS WINAPI ObjGetData(LPCOSMOOBJECT pObj, OLECLIPFORMAT cf
    , HGLOBAL FAR * phData)
    {
    HGLOBAL             hMem;

    /*
     * 1.   Allocate the requested data throguh GlobalAlloc (with
     *      GMEM_MOVEABLE and GMEM_DDESHARE).  The exception is data for
     *      CF_BITMAP which uses a call like CreateBitmap.
     * 2.   Lock and fill the memory with the appropriate data.
     * 3.   Unlock the memory and store the handle in *phData.
     * 4.   Return OLE_OK if successful, OLE_ERROR_MEMORY otherwise.
     */

    //Return Native, metafile, or bitmap as requested.
    if (pOLE->cfNative==cf)
        hMem=HGetPolyline(pGlob->hWndPolyline);

    if (CF_METAFILEPICT==cf)
        hMem=HGetMetafilePict(pGlob->hWndPolyline);

    if (CF_BITMAP==cf)
        hMem=HGetBitmap(pGlob->hWndPolyline);


    //Use filename
    if (pOLE->cfObjectLink==cf)
         hMem=HLinkConstruct(rgpsz[IDS_CLASSCOSMO], "", "");

    /*
     * Even though this is exactly like ObjectLink, this is coded as
     * a separate case just in case it changes in the future.
     */
    if (pOLE->cfOwnerLink==cf)
        hMem=HLinkConstruct(rgpsz[IDS_CLASSCOSMO], "", "");


    if (NULL==hMem)
        return OLE_ERROR_MEMORY;

    *phData=hMem;
    return OLE_OK;
    }





/*
 * ObjQueryProtocol
 *
 * Purpose:
 *  Returns a pointer to an COSMOOBJECT with the appropriate VTBL for
 *  the protocol, either StdFileEditing or StdExecute.  Returns NULL
 *  if that protocol is not supported.
 *
 * Parameters:
 *  pObj            LPCOSMOOBJECT specifying the object affected.
 *  pszProtocol     OLE_LPCSTR, the protocol name.
 *
 * Return Value:
 *  OLESTATUS       OLE_OK if all is well, otherwise an OLE_* error value.
 */

LPVOID WINAPI ObjQueryProtocol(LPCOSMOOBJECT pObj, OLE_LPCSTR pszProtocol)
    {

    /*
     * 1.   If the protocol in pszProtocol is supported, return a pointer
     *      to an object that contains an appropriate VTBL fot that protocol,
     *      such as the pObj passed to this method.
     * 2.   If the protocol is not supported, return NULL.
     */

    //Check if OLESVR is asking for "StdFileEditing"
    if (0==lstrcmp(pszProtocol, rgpsz[IDS_STDFILEEDITING]))
        return (LPVOID)pObj;

    return (LPVOID)NULL;
    }






/*
 * ObjRelease
 *
 * Purpose:
 *  Notifies a server that is can free any resources associated with an
 *  object.
 *
 * Parameters:
 *  pObj            LPCOSMOOBJECT specifying the object affected.
 *
 * Return Value:
 *  OLESTATUS       OLE_OK if all is well, otherwise an OLE_* error value.
 */

OLESTATUS WINAPI ObjRelease(LPCOSMOOBJECT pObj)
    {
    /*
     * 1.   Free any resources allocated for this object, but
     *      DO NOT free the OLEOBJECT structure itself.
     * 2.   Set a flag to indicate that Release has been called.
     * 3.   NULL any saved LPOLECLIENT stores in the OLEOBJECT structure.
     * 4.   Return OLE_OK if successful, OLE_ERROR_GENERIC otherwise.
     *
     * Do not use the Release method to free the memory containing
     * the object since you still need to use its pClient and fRelease.
     * This method simply notifies the object that no one is using it
     * anymore so we don't try to send notifications.
     */

    pObj->fRelease=TRUE;
    pObj->pClient=NULL;
    return OLE_OK;
    }





/*
 * ObjSetBounds
 *
 * Purpose:
 *  Specifies a new boundary rectangle for the object in MM_HIMETRIC
 *  units.  Only useful for embedded objects since a linked object
 *  depends on the file loaded.
 *
 * Parameters:
 *  pObj            LPCOSMOOBJECT specifying the object affected.
 *  pRect           LPRECT containing the new bounds.
 *
 * Return Value:
 *  OLESTATUS       OLE_OK if all is well, otherwise an OLE_* error value.
 */

OLESTATUS WINAPI ObjSetBounds(LPCOSMOOBJECT pObj, OLE_CONST RECT FAR *pRect)
    {
    //Unused in OLE1.x
    return OLE_OK;
    }




/*
 * ObjSetColorScheme
 *
 * Purpose:
 *  Provides a color scheme that the client application recommends for
 *  rendering graphical data.
 *
 * Parameters:
 *  pDoc            LPCOSMOOBJECT specifying the object affected.
 *  pPal            LPLOGPALETTE describing the recommended palette.
 *
 * Return Value:
 *  OLESTATUS       OLE_OK if all is well, otherwise an OLE_* error value.
 */

OLESTATUS WINAPI ObjSetColorScheme(LPCOSMOOBJECT pObj
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
 * ObjSetData
 *
 * Purpose:
 *  Instructs the object to take the given data as current and copy it
 *  to the object's internal data, use when a client opens an embedded
 *  object or if the client calls OleSetData.
 *
 *  *NOTE: This function MUST be supported even if the registration
 *         database does not contain an entry for SetDataFormats for
 *         this server, because the callback is still used when opening
 *         an embedded object for editing.
 *
 * Parameters:
 *  pObj            LPCOSMOOBJECT specifying the object affected.
 *  cf              OLECLIPFORMAT format to return data in, may be "Native."
 *  hData           HGLOBAL to memory containing the data.
 *
 * Return Value:
 *  OLESTATUS       OLE_OK if all is well, otherwise an OLE_* error value.
 */

OLESTATUS WINAPI ObjSetData(LPCOSMOOBJECT pObj, OLECLIPFORMAT cf
    , HGLOBAL hData)
    {
    LPPOLYLINE          lppl;

    /*
     * 1.   If the data format is not supported, return OLE_ERROR_FORMAT.
     * 2.   Attempt to GlobalLock the memory to get a pointer to the data.
     *      If GlobalLock returns NULL, return OLE_ERROR_MEMORY.
     * 3.   Copy the data to the object identified by pObj.
     * 4.   Unlock and GlobalFree the data handle.  The ObjSetData method
     *      is responsible for the memory.
     * 5.   Return OLE_OK.
     */

    //Check if we were given Native data.  We don't support anything else.
    if (pOLE->cfNative!=cf)
        return OLE_ERROR_FORMAT;

    lppl=(LPPOLYLINE)GlobalLock(hData);

    /*
     * CHECK the return from GlobalLock since we don't know where this
     * handle has been.
     */
    if (NULL==lppl)
        return OLE_ERROR_MEMORY;

    //Set the data through the editing window.
    SendMessage(pGlob->hWndPolyline, PLM_POLYLINESET, TRUE, (LONG)lppl);

    //Make sure we are not dirty--no updating is yet necessary.
    FDirtySet(FALSE);

    //Server is responsible for freeing the data.
    GlobalUnlock(hData);
    GlobalFree(hData);
    return OLE_OK;
    }






/*
 * ObjSetTargetDevice
 *
 * Purpose:
 *  Communicates information from the client application to the server
 *  about the device on which the object is drawn.
 *
 * Parameters:
 *  pObj            LPCOSMOOBJECT specifying the object affected.
 *  hData           HGLOBAL containing a STDTARGETDEVICE structure.
 *
 * Return Value:
 *  OLESTATUS       OLE_OK if all is well, otherwise an OLE_* error value.
 */

OLESTATUS WINAPI ObjSetTargetDevice(LPCOSMOOBJECT pObj, HGLOBAL hData)
    {

    /*
     * The server is responsible for freeing the the data handle
     * once it has finished using that data.
     *
     * If NULL==hData, then rendering is necessary for the screen.
     */

    if (NULL!=hData)
        GlobalFree(hData);

    return OLE_OK;
    }







/*
 * ObjShow
 *
 * Purpose:
 *  Causes the server to show an object, showing the window and
 *  scrolling it's client area if necessary.
 *
 * Parameters:
 *  pObj            LPCOSMOOBJECT specifying the object affected.
 *  fTakeFocus      BOOL:  TRUE if the server should get the focus,
 *                  FALSE if not.
 *
 * Return Value:
 *  OLESTATUS       OLE_OK if all is well, otherwise an OLE_* error value.
 */

OLESTATUS WINAPI ObjShow(LPCOSMOOBJECT pObj, BOOL fTakeFocus)
    {
    /*
     * 1.   Show the application window(s) if not already visible.
     * 2.   Scroll the object identified by pObj into view, if necessary.
     * 3.   Select the object if possible.
     * 4.   If fTakeFocus is TRUE, call SetFocus with the main window handle.
     * 5.   Return OLE_OK if successful, OLE_ERROR_GENERIC otherwise.
     */

    //Keep WM_SIZE on the ShowWindow from making us dirty.
    pGlob->fNoDirty=TRUE;

    //Since we only have one object, we don't care what's in pObj.
    ShowWindow(pGlob->hWnd, SW_NORMAL);

    pGlob->fNoDirty=FALSE;

    if (fTakeFocus)
        SetFocus(pGlob->hWnd);

    return OLE_OK;
    }


#endif //MAKEOLESERVER
