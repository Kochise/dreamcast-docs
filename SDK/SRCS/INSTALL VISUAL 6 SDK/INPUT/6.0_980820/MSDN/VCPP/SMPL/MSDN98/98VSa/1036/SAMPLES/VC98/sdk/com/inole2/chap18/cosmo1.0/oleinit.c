/*
 * OLEINIT.C
 *
 * Handles all application and instance-specific initialization that
 * is also specific to OLE.  That which is specific only to the
 * application or instance resides in INIT.C
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
 * FOLEInstanceInit
 *
 * Purpose:
 *  Handles OLE-server specific initialziation:
 *      1.  Register clipboard formats for "Native", "OwnerLink",
 *          and "ObjectLink."
 *      2.  Initialize VTBLs for server, document, and object.
 *      3.  Register the server with OLESVR.
 *      4.  Parse the command line to determine initial window state.
 *      5.  Register a document depending on contents of command line.
 *
 * Parameters:
 *  pOLE            LPXOLEGLOBALS to OLE-specific global variable block.
 *  hInstance       HINSTANCE of the application instance.
 *  pszClass        LPSTR to classname of the server.
 *  ppszCmds        LPSTR FAR to command line argument strings.
 *  nCmdShow        UINT initial ShowWindow command passed to WinMain.
 *
 * Return Value:
 *  BOOL            FALSE if an error occurred, otherwise TRUE and
 *                  pOLE->wCmdShow contains a valid ShowWindow command
 *                  for the initial state of the window.
 */

BOOL WINAPI FOLEInstanceInit(LPXOLEGLOBALS pOLE, HINSTANCE hInstance
    , LPSTR pszClass, LPSTR FAR *ppszCmds, UINT nCmdShow)
    {
    OLESTATUS       os;
    LPSTR           pszT;
    LPCOSMOSERVER   pSvr;
    LPCOSMODOC      pDoc;
    BOOL            fTemp;


    //1. Register clipboard formats.
    pOLE->cfNative    =RegisterClipboardFormat(rgpsz[IDS_NATIVE]);
    pOLE->cfOwnerLink =RegisterClipboardFormat(rgpsz[IDS_OWNERLINK]);
    pOLE->cfObjectLink=RegisterClipboardFormat(rgpsz[IDS_OBJECTLINK]);

    if (0==pOLE->cfNative || 0==pOLE->cfOwnerLink || 0==pOLE->cfObjectLink)
        return FALSE;


    /*
     * 2. Initialize the method tables with functions in OLEVTBL.C
     *    and mark the vtbl's as initialized.
     */
    fTemp=TRUE;
    fTemp&=FOLEVtblInitServer  (hInstance, &pOLE->vtblSvr);
    fTemp&=FOLEVtblInitDocument(hInstance, &pOLE->vtblDoc);
    fTemp&=FOLEVtblInitObject  (hInstance, &pOLE->vtblObj);

    if (!fTemp)
        return FALSE;   //Cleanup will follow through FApplicationExit.


    /*
     * 3. Allocate and initialize the OLESERVER structure, in this
     *    application we call it COSMOSERVER.  Uses the server
     *    constructor in OLESVR.C.
     */

    pSvr=PServerAllocate(&pOLE->vtblSvr);

    if ((LPCOSMOSERVER)NULL==pSvr)
        return FALSE;

    pOLE->pSvr=pSvr;
    pSvr->nCmdShow=nCmdShow;        //By default, use what the app was given.


    //4. Register the server application with OLESVR.DLL
    os=OleRegisterServer(pszClass, (LPOLESERVER)pSvr, &pSvr->lh,
                         hInstance, OLE_SERVER_MULTI);

    if (OLE_OK!=os)
        {
        //ServerRelease will NOT be called so we must free the memory.
        LocalFree(pSvr->hMem);
        return FALSE;
        }



    /*
     * 5. Given the pointer to the command-line strings, ppszCmds,
     *    check if we have "[/ | -]Embedding" and a possible filename.
     *
     * NOTE:  We trust whoever called us to find a filename in
     *        the command line, ignoring anything that starts with
     *        a - or / as an argument.
     */

    pszT=*ppszCmds++;

    //Assume stand-alone configuration.
    pGlob->fOLE=FALSE;
    pSvr->fEmbed=FALSE;
    pSvr->fLink=FALSE;

    if (NULL!=pszT)
        {
        /*
         * If the first parameter has - or / leading, skip that character
         * so we can check for "Embedding"
         */
        if('-'==*pszT || '/'==*pszT)
            pszT++;

        //See if we have Embedding at all, in which case we're doing OLE.
        pGlob->fOLE=!lstrcmp(pszT, rgpsz[IDS_EMBEDDING]);

        //Change the ShowWindow command appropriately if we're doing OLE.
        if (pGlob->fOLE)
            pSvr->nCmdShow=SW_HIDE;


        /*
         * Set fLink if there is an additional filename on the
         * command-line, and point pszT there if so.
         */
        if (NULL!=*ppszCmds)
            {
            pSvr->fLink=TRUE;
            pszT=*ppszCmds;
            }
        else
            {
            pSvr->fEmbed=TRUE;
            pszT=NULL;
            }

        //pszT is either NULL or points to a filename.
        }

    /*
     * 6.  Allocate an OLESERVERDOC (COSMODOC) and initialize.  LPTR
     *     to LocalAlloc initializes everything to NULL.
     */
    pDoc=PDocumentAllocate(&pOLE->vtblDoc);

    if ((LPCOSMODOC)NULL==pDoc)
        {
        //DocRelease will not be called, but ServerRelease will.
        LocalFree(pDoc->hMem);
        OleRevokeServer(pSvr->lh);
        return FALSE;
        }

    pSvr->pDoc=pDoc;


    /*
     * 7.  Register documents as necessary.  Remember to register any
     *     stand-alone or linked document regardless of what you are
     *     doing with OLE.  The only case where you do NOT register is
     *     for starting the application as embedded.
     *
     *     In step 5 we set pszT equal to either NULL (embedding or no
     *     file) or to a filename (linking or stand-alone with a file).
     *     So we only have to point pszT to "(Untitled)" if it's NULL
     *     then call OleRegisterServerDoc.
     */

    //Register a document in any case except embedding.
    if (!pSvr->fEmbed)
        {
        pszT=(NULL==pszT) ? rgpsz[IDS_UNTITLED] : pszT;
        os=OleRegisterServerDoc(pSvr->lh, pszT, (LPOLESERVERDOC)pDoc, &pDoc->lh);

        //Must revoke on any error.
        if (OLE_OK!=os)
            {
            OleRevokeServer(pSvr->lh);
            return FALSE;
            }
        }

    //All done!
    return TRUE;
    }


#endif //MAKEOLESERVER
