/*
 *  M S P G L E . C
 *
 *  Code for implementing the GetLastError method of all store
 *  objects.
 *
 *  Copyright 1992-1995 Microsoft Corporation.  All Rights Reserved.
 */

#include "msp.h"
#include "msprc.h"

/* Manifest constants */

#define STRING_MAX      128

/* Global variables */

/* The following array maps a string identifier (IDS) to status code */
/* (SCODE).  The order of SCODEs in the array has an external        */
/* dependency:  the order of elements in the array is dictated by    */
/* the IDS definitions in msprc.h.  This implicit association must   */
/* be maintained for the strings associated with string identifiers  */
/* to make sense.  Thus, if either this structure or the one in      */
/* msprc.h changes, the other must change to match it.               */

SCODE mpIdsScode[] =
{
    S_OK,
    MAPI_E_NO_ACCESS,
    E_NOINTERFACE,
    E_INVALIDARG,
    MAPI_E_CALL_FAILED,
    MAPI_E_NOT_FOUND,
    MAPI_E_NO_SUPPORT,
    MAPI_W_ERRORS_RETURNED,
    MAPI_W_PARTIAL_COMPLETION,
    MAPI_E_BAD_CHARWIDTH,
    MAPI_E_BAD_VALUE,
    MAPI_E_BUSY,
    MAPI_E_COLLISION,
    MAPI_E_COMPUTED,
    MAPI_E_CORRUPT_DATA,
    MAPI_E_CORRUPT_STORE,
    MAPI_E_DISK_ERROR,
    MAPI_E_HAS_FOLDERS,
    MAPI_E_HAS_MESSAGES,
    MAPI_E_INVALID_ENTRYID,
    MAPI_E_INVALID_OBJECT,
    MAPI_E_LOGON_FAILED,
    MAPI_E_NETWORK_ERROR,
    MAPI_E_NON_STANDARD,
    MAPI_E_NOT_ENOUGH_DISK,
    MAPI_E_NOT_ENOUGH_MEMORY,
    MAPI_E_NOT_ENOUGH_RESOURCES,
    MAPI_E_NOT_IN_QUEUE,
    MAPI_E_OBJECT_CHANGED,
    MAPI_E_OBJECT_DELETED,
    MAPI_E_STRING_TOO_LONG,
    MAPI_E_SUBMITTED,
    MAPI_E_TOO_BIG,
    MAPI_E_UNABLE_TO_ABORT,
    MAPI_E_UNCONFIGURED,
    MAPI_E_UNEXPECTED_TYPE,
    MAPI_E_UNKNOWN_FLAGS,
    MAPI_E_USER_CANCEL,
    MAPI_E_VERSION
};

/*
 *  Exported functions
 */

/*
 *  MapScodeSz
 *
 *  Purpose:
 *      Look up an SCODE in a mapping of IDS <-> SCODE to find its
 *      associated informational string and return it (with memory
 *      allocated by this function) to the caller.
 *
 *  Arguments:
 *      scArg       The SCODE to look up.
 *      pims        Pointer to the message store object (where we
 *                  obtain the memory allocation functions).
 *      lppszError  Location in which to place an address to a
 *                  newly allocated buffer containing the
 *                  informational string associated with scArg.
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      MAPI_E_NOT_ENOUGH_MEMORY    Could not allocate space for
 *                                  the return string.
 */
HRESULT MapScodeSz(SCODE scArg, PIMS pims, LPTSTR * lppszError)
{
    HRESULT hr = hrSuccess;
    SCODE sc = SUCCESS_SUCCESS;
    UINT ui = 0;
    UINT uiMax = 0;
    LPTSTR szErr = NULL;
    TCHAR rgch[STRING_MAX];

    AssertSz(lppszError, "Bad lppszError\n");

    /* Linear search in mpIdsScode for scArg.  When found, index is IDS. */

    uiMax = sizeof mpIdsScode / sizeof mpIdsScode[0];
    for (ui = 0; ui < uiMax; ui++)
    {
        if (mpIdsScode[ui] == scArg)
            break;
    }

    /* If we didn't find the string, return a NULL string. */

    if (ui == uiMax)
        rgch[0] = (TCHAR) 0;
    else
    {
        /* Get the string from the resource.  Note:  the assumption that   */
        /* rgch is large enough to hold the largest string that LoadString */
        /* could return can be checked by looking at the resource strings  */
        /* file, msp.rc                                                    */

        int iLS = 0;
    
        Assert(pims->pmsp);
    
        iLS = LoadString(pims->pmsp->hInst, ui, rgch, STRING_MAX);
        AssertSz(iLS, "Unknown string identifier!");
        AssertSz(iLS < STRING_MAX-1, "String resource truncated!");
    }

    /* Allocate memory for return variable and set it */

    sc = LMAlloc(&pims->lmr, Cbtszsize(rgch), &szErr);
    if (sc != S_OK)
    {
        hr = ResultFromScode(sc);
        goto exit;
    }

    lstrcpy(szErr, rgch);
    *lppszError = szErr;

exit:
    DebugTraceResult(MapScodeSz, hr);
    return hr;
}
