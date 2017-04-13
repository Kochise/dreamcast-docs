/*
 *  M S P I N I T . C
 *
 *  Initialize the MAPI Sample Message Store Provider.
 *
 *  Copyright 1992-1995 Microsoft Corporation.  All Rights Reserved.
 */

#include "msp.h"

CHAR szFolderTemplate[]         = "*.fld";
CHAR szMessageTemplate[]        = "*.msg";
CHAR szPropertyFileName[]       = "folder.prp";
CHAR szHierarchyFileName[]      = "hierarch.tbl";
CHAR szContentsFileName[]       = "contents.tbl";
CHAR szOutgoingFileName[]       = "outgoing.tbl";

#define MSP_CheckParameters(pobj, intf, method, arglist)        \
        OBJ_CheckParameters(pobj, intf, method, sizeof(MSP), &vtblMSP, arglist)

MSP_Vtbl vtblMSP =
{
    (MSP_QueryInterface_METHOD *)   OBJ_QueryInterface,
    (MSP_AddRef_METHOD *)           OBJ_AddRef,
    MSP_Release,
    MSP_Shutdown,
    MSP_Logon,
    MSP_SpoolerLogon,
    MSP_CompareStoreIDs
};

/*
 *  Exported functions
 */

/*
 *  MSProviderInit
 *
 *  Purpose:
 *      Message Store Provider initialization and version handshake
 *      with MAPI.  Called once for each MAPI Session that uses this
 *      store provider DLL on this process.  Passes back an init
 *      object (LPMSPROVIDER) used for further access to this provider.
 *
 *  Arguments:
 *      ulFlags         Reserved for future use.  Ignored.
 *      ulMAPIVersion   Version of Message Store SPI used by MAPI.
 *      lpulMDBVersion  [out] Version of SPI supported by the provider.
 *      ppmsp   [out] MS Provider object for further access.
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      MAPI_E_VERSION              Require a higher version of MAPI
 *      MAPI_E_NOT_ENOUGH_MEMORY    Insufficient memory
 *      Any errors from ScInitMSInstance()
 */
STDINITMETHODIMP
MSProviderInit(HINSTANCE hInstance, LPMALLOC pmalloc,
    LPALLOCATEBUFFER pfnAllocBuf, LPALLOCATEMORE pfnAllocMore,
    LPFREEBUFFER pfnFreeBuf, ULONG ulFlags, ULONG ulMAPIVersion,
    ULONG * pulMDBVersion, LPMSPROVIDER * ppmsp)
{
    SCODE sc = S_OK;
    PMSP pmsp = NULL;

    AssertSz(pmalloc, "Bad pmalloc");
    AssertSz(pfnAllocBuf, "Bad pfnAllocBuf");
    AssertSz(pfnAllocMore, "Bad pfnAllocMore");
    AssertSz(pfnFreeBuf, "Bad pfnFreeBuf");
    NFAssertSz(!ulFlags, "Unknown flags, bug in MAPI DLL");
    AssertSz(pulMDBVersion, "Bad pulMDBVersion");
    AssertSz(ppmsp, "Bad ppmsp");

    /* This provider requires MAPI to be at least the version
     * of the SPI defined at the time this provider was compiled.
     */
    if (ulMAPIVersion < CURRENT_SPI_VERSION)
    {
        sc = MAPI_E_VERSION;
        goto exit;
    }

    /* Initialize the per-instance global data */
    sc = ScInitMSInstance(pmalloc);
    if (sc != S_OK)
        goto exit;

    /* Allocate and initialize the MSPROVIDER object. */
    sc = ScAllocZ(sizeof(MSP), (PPV) &pmsp);
    if (sc != S_OK)
    {
        DeinitMSInstance();
        goto exit;
    }

    OBJ_Initialize(pmsp, &vtblMSP, OT_MSPROVIDER, 0, &pmsp->cs);

    pmsp->hInst = hInstance;
    pmsp->lmr.lpAllocBuf = pfnAllocBuf;
    pmsp->lmr.lpAllocMore = pfnAllocMore;
    pmsp->lmr.lpFreeBuf = pfnFreeBuf;

    InitializeCriticalSection(&pmsp->cs);

    /* Pass back [out] parameters. */
    *pulMDBVersion = CURRENT_SPI_VERSION;
    *ppmsp = (LPMSPROVIDER) pmsp;

exit:
    DebugTraceSc(MSProviderInit, sc);
    return ResultFromScode(ScCheckSc(sc, IMSProvider_Init));
}

/*
 -  MSP_Release
 -
 */

STDMETHODIMP_(ULONG) MSP_Release(PMSP pmsp)
{
    LONG cRef;

    MSP_EnterCriticalSection(pmsp);

    cRef = --pmsp->cRef;

    AssertSz2(cRef >= 0, "MSP_Release(pmsp=%08lX): Bogus cRef (%08lX)",
        pmsp, cRef);

    AssertSz(cRef > 0 || pmsp->pobjHead == NULL, "There are still valid logons");

    MSP_LeaveCriticalSection(pmsp);

    if (cRef == 0)
    {
        DeleteCriticalSection(&pmsp->cs);
        FreeNull(pmsp);
        DeinitMSInstance();
    }

    return (cRef);
}

/*
 *  MSP_Shutdown
 *
 *  Purpose:
 *      Allow MAPI to specify flags related to the Release().
 *
 *  Arguments:
 *      pulFlags        Reserved for future use.  Ignored.
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      None.
 */
STDMETHODIMP
MSP_Shutdown(PMSP pmsp, ULONG * pulFlags)
{
    MSP_CheckParameters(
            pmsp, 
            IMSProvider, 
            Shutdown,
            (pmsp,
            pulFlags));

    MSP_EnterCriticalSection(pmsp);

    /* MAPI says it will never call Release with valid logons, */
    /* let's make sure.                                        */

    AssertSz(pmsp->pobjHead == NULL, "There are still valid logons");

#ifdef DEBUG
    pmsp->fInvalid = TRUE;
#endif

    MSP_LeaveCriticalSection(pmsp);

    return 0;
}

/*
 *  MSP_CompareStoreIDs
 *
 *  Purpose:
 *      Compare the EntryIDs of two message stores.
 *
 *  Arguments:
 *      pmsp                MSPROVIDER object returned by MSProviderInit.
 *      lcbEntryID1         Size of first EntryID.
 *      lpEntryID1          First EntryID to compare.
 *      lcbEntryID2         Size of second EntryID.
 *      lpEntryID2          Second EntryID to compare.
 *      ulFlags             Flags.  Reserved for future use.
 *      pulResult           Address in which to place the result of
 *                          the comparison (TRUE or FALSE).
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      None.
 */
STDMETHODIMP
MSP_CompareStoreIDs(PMSP pmsp, ULONG lcbEntryID1, LPENTRYID lpEntryID1,
    ULONG lcbEntryID2, LPENTRYID lpEntryID2, ULONG ulFlags,
    ULONG *pulResult)
{
    PEID peid1 = (PEID) lpEntryID1;
    PEID peid2 = (PEID) lpEntryID2;

    MSP_CheckParameters(
            pmsp, 
            IMSProvider,
            CompareStoreIDs,
            (pmsp,
            lcbEntryID1, 
            lpEntryID1,
            lcbEntryID2, 
            lpEntryID2, 
            ulFlags,
            pulResult));

    AssertSz(!pmsp->fInvalid,
        "This MSProvider has already been shutdown");

    /* The Sample Store's method of deriving and comparing   */
    /* store EntryIDs has the quirky behavior that if any    */
    /* OTHER store's EntryIDs are binary-comparable, this    */
    /* function will return a successful match, without ever */
    /* knowing that the EntryIDs were not Sample Store       */
    /* EntryIDs.  A subsequent logon would, of course, fail. */

    /* Case-insensitive string compare on part, binary on rest. */
    if (    lcbEntryID1 >= offsetof(EID, szPath) + sizeof(TCHAR)
        &&  lcbEntryID1 == lcbEntryID2
        &&  memcmp(peid1, peid2, offsetof(EID, szPath)) == 0
        &&  peid1->bVersion == SMPMS_VERSION
        &&  lstrcmpi(peid1->szPath, peid2->szPath) == 0)
    {
        *pulResult = TRUE;
    }
    else
    {
        *pulResult = FALSE;
    }

    return hrSuccess;
}
