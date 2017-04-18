/*
 * EXIT.C
 *
 * Functions for final cleanup of the COSMO application.  Calls any
 * OLE specific functions.
 *
 * Copyright(c) Microsoft Corp. 1992-1994 All Rights Reserved
 * Win32 version, January 1994
 */

#include <windows.h>
#include <ole.h>
#include "cosmo.h"
#include "oleglobl.h"


/*
 * FApplicationExit
 *
 * Purpose:
 *  Provides final cleanup of any objects and other actions that
 *  must occur at closing time.
 *
 * Parameters:
 *  pGlob           LPGLOBALS to global variable block.
 *
 * Return Value:
 *  BOOL            TRUE if everything succeeds, FALSE otherwise.
 */

BOOL WINAPI FApplicationExit(LPGLOBALS pGlob)
    {
    BOOL        fRet=TRUE;

    //Free the stringtable.
    if (NULL!=pGlob->hStringMem)
        LocalFree(pGlob->hStringMem);

#ifdef MAKEOLESERVER

    fRet=FOLEExit(pOLE);

#endif //MAKEOLESERVER

    return fRet;
    }
