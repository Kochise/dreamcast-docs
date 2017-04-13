/*
 * OLEFILE.C
 *
 * Functions for handling special case OLE functions for operations
 * on a File menu such as New, Open, Save, SaveAs, and Exit.
 *
 * Functions:
 *  PDocRevokeAndCreate
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
 * PDocRevokeAndCreate
 *
 * Purpose:
 *  Standard sequence of calling OleRevokeServerDoc, allocating and
 *  initializing a new OLESERVERDOC structure, and calling
 *  OleRegisterServerDoc.
 *
 * Parameters:
 *  pOLE            LPXOLEGLOBALS pointer to OLE global variables.
 *
 * Return Value:
 *  LPCOSMODOC      Pointer to the new document, or NULL if it fails.
 *
 */

LPCOSMODOC WINAPI PDocRevokeAndCreate(LPXOLEGLOBALS pOLE)
    {
    LPCOSMODOC      pDoc;
    OLESTATUS       os;

    os=OleRevokeServerDoc(pOLE->pSvr->pDoc->lh);

    /*
     * Even through we are revoking the document, the server will also
     * be Released (through not revoked) since no OLE connections will
     * exist to the server.  Since ServerRelease in this application
     * frees the allocated document, we need to wait until we pass
     * ServerRelease before allocating a new document.  Otherwise we'd
     * allocate a new one and ServerRelease would immediately free it.
     *
     * So in calling FOLEReleaseWait we watch the server's fRelease flag.
     */

    if (OLE_WAIT_FOR_RELEASE==os)
        {
        pOLE->pSvr->fRelease=FALSE;
        FOLEReleaseWait(&pOLE->pSvr->fRelease, pOLE->pSvr->lh);
        }

    pDoc=PDocumentAllocate(&pOLE->vtblDoc);
    pOLE->pSvr->pDoc=pDoc;

    if (NULL==pDoc)
        return NULL;

    os=OleRegisterServerDoc(pOLE->pSvr->lh, pGlob->szFile,
                            (LPOLESERVERDOC)pOLE->pSvr->pDoc,
                            &pOLE->pSvr->pDoc->lh);

    pOLE->pSvr->fLink=FALSE;
    pOLE->pSvr->fEmbed=FALSE;

    MenuEmbeddingSet(pGlob->hWnd, NULL, FALSE);
    return pDoc;
    }


#endif //MAKEOLESERVER
