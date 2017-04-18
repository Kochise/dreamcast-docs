/*
 * OLEEXIT.C
 *
 * Functions for final OLE cleanup.
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
 * FOLEExit
 *
 * Purpose:
 *  Handles OLE-server specific shutdown
 *    1.  Free the OLESERVER structure.
 *    2.  Free the procedure instances the server's VTBLs.
 *
 * Parameters:
 *  pOLE            LPXOLEGLOBALS to OLE-specific global variable block.
 *
 * Return Value:
 *  BOOL            FALSE if an error occurred, otherwise TRUE.
 */

BOOL WINAPI FOLEExit(LPXOLEGLOBALS pOLE)
    {
    /*
     * Dump the server.  We depend on ServerRelease and DocRelease to
     * clean up documents and objects.  Choosing File/Exit has already
     * revoked the server.  This is simply final cleanup.
     */
    if (NULL!=pOLE)
        {
        if (NULL!=pOLE->pSvr)
            LocalFree(pOLE->pSvr->hMem);
        }

    OLEVtblFreeServer  (&pOLE->vtblSvr);
    OLEVtblFreeDocument(&pOLE->vtblDoc);
    OLEVtblFreeObject  (&pOLE->vtblObj);

    return TRUE;
    }


#endif //MAKEOLESERVER
