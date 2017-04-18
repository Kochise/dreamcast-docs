/*
 *  M S P M I S C . C
 *
 *  Utility functions needed by the MAPI Sample Store Provider.
 *
 *  Copyright 1992-1995 Microsoft Corporation.  All Rights Reserved.
 */

#include "msp.h"

/*
 *  Memory allocation and release functions.  They use the lpMalloc
 *  interface supplied by MAPI during provider initialization.
 *
 *  For internal memory allocations the Sample Store Provider uses
 *  the lpMalloc passed by MAPI on MSProviderInit().  For simplicity
 *  of coding we keep the pointer to the lpMalloc in a
 *  per-process global (which requires mucho work on Win16) instead
 *  of forcing ScAlloc() calls to pass in the pointer on each and every
 *  allocation.  We trade off code size with speed (on Win16) because
 *  of the searching necessary in finding the per-instance globals.
 *
 *  When multiple MSProviderInit's are done on the same process
 *  (by opening one or more stores on two different MAPI Profiles
 *  on the same process) we use the lpMalloc from the first init
 *  for all allocations, keeping a refcount of MSProviderInit's
 *  that have been done in order to know when to free the lpMalloc.
 *
 *  As a result we don't necessary use the lpMalloc for store X that
 *  was passed in when store X was opened, but as long as MAPI gives
 *  us the Component Object's lpMalloc on each open we're fine.
 */

SCODE ScAlloc(ULONG lcb, LPVOID * ppv)
{
    PINST pinst = (PINST) PvGetInstanceGlobals();

    Assert(pinst);
    Assert(pinst->lpmalloc);

    *ppv = pinst->lpmalloc->lpVtbl->Alloc(pinst->lpmalloc, lcb);
    if (*ppv != NULL)
        return S_OK;

    DebugTraceSc(ScAlloc, MAPI_E_NOT_ENOUGH_MEMORY);
    return (MAPI_E_NOT_ENOUGH_MEMORY);
}

SCODE ScAllocZ(ULONG lcb, LPVOID * ppv)
{
    PINST pinst = (PINST) PvGetInstanceGlobals();

    Assert(pinst);
    Assert(pinst->lpmalloc);

    *ppv = pinst->lpmalloc->lpVtbl->Alloc(pinst->lpmalloc, lcb);
    if (*ppv != NULL)
    {
        memset(*ppv, 0, (size_t) lcb);
        return S_OK;
    }

    DebugTraceSc(ScAllocZ, MAPI_E_NOT_ENOUGH_MEMORY);
    return (MAPI_E_NOT_ENOUGH_MEMORY);
}

SCODE ScRealloc(ULONG lcb, LPVOID pvOrig, LPVOID * ppv)
{
    PINST pinst = (PINST) PvGetInstanceGlobals();
    LPVOID pvNew;

    Assert(pinst);
    Assert(pinst->lpmalloc);

    pvNew = pinst->lpmalloc->lpVtbl->Realloc(pinst->lpmalloc, pvOrig, lcb);
    if (pvNew != NULL)
    {
        *ppv = pvNew;
        return S_OK;
    }

    DebugTraceSc(ScRealloc, MAPI_E_NOT_ENOUGH_MEMORY);
    return (MAPI_E_NOT_ENOUGH_MEMORY);
}

void FreeNull(LPVOID pv)
{
    if (pv)
    {
        PINST pinst = (PINST) PvGetInstanceGlobals();

        Assert(pinst);
        Assert(pinst->lpmalloc);

        pinst->lpmalloc->lpVtbl->Free(pinst->lpmalloc, pv);
    }
}

/* Linked Memory Utilities ------------------------------------------------- */

SCODE LMAllocZ(PLMR plmr, ULONG lcb, LPVOID * ppv)
{
    SCODE sc;

    sc = LMAlloc(plmr, lcb, ppv);
    if (sc != S_OK)
        return (sc);

    memset(*ppv, 0, (size_t) lcb);
    return (S_OK);
}

/*
 *  ScInitMSInstance
 *
 *  Remember the given lpMalloc in a per-instance variable that
 *  can be looked up again in ScAlloc and FreeNull.
 */
SCODE ScInitMSInstance(LPMALLOC lpmalloc)
{
    PINST pinst = (PINST) PvGetInstanceGlobals();
    SCODE sc;

    Assert(lpmalloc);

    if (pinst)
    {
        /* A usable allocator is already set.   */
        /* Ignore the one we were passed in     */
        /* and instead bump the refcount on the */
        /* one we're going to use.              */
        ++(pinst->cRef);
        return S_OK;
    }

    /* In our debugging version wrap the allocator for
     * extra help locating memory leaks or other problems.
     * In both debug and non-debug versions, this statement
     * addrefs the allocator, and the DBGMEM_Shutdown at the
     * end does a release on the allocator.
     */
    lpmalloc = DBGMEM_Encapsulate(lpmalloc, "Sample Store", 0);

    pinst = (PINST) lpmalloc->lpVtbl->Alloc(lpmalloc, sizeof(INST));

    if (pinst == NULL)
    {
        sc = MAPI_E_NOT_ENOUGH_MEMORY;
        goto ret;
    }

    sc = ScSetInstanceGlobals(pinst);
    if (sc != S_OK)
        goto ret;

    pinst->cRef = 1;
    pinst->lpmalloc = lpmalloc;

    return S_OK;

ret:
    if (pinst)
        lpmalloc->lpVtbl->Free(lpmalloc, pinst);

    DBGMEM_Shutdown(lpmalloc);
    DebugTraceSc(ScInitMSInstance, sc);
    return sc;
}

void DeinitMSInstance(void)
{
    PINST pinst = (PINST) PvGetInstanceGlobals();
    LPMALLOC lpmalloc;

    if (!pinst || --(pinst->cRef) > 0)
        return;

    (void)ScSetInstanceGlobals(NULL);
    lpmalloc = pinst->lpmalloc;
    lpmalloc->lpVtbl->Free(lpmalloc, pinst);
    DBGMEM_Shutdown(lpmalloc);
}

/*
 *  SzBaseName
 *
 *  Purpose
 *      return the base name of the object with the given eid
 *
 *  Parameters
 *      peid                Pointer to entryID of object
 *
 *  Returns
 *      LPTSTR              base name, ie sequence number and extension
 *
 *  Note                    no memory is allocated, returned value must be
 *                          copied if it is to be saved.
 */
LPTSTR SzBaseName(PEID peid)
{
    LPTSTR szName;              /* local name of object in lpEntryID */
    LPTSTR szLastSlash;         /* position of last slash in peid */

    Assert(peid);

    /* Note that the entryid pathname is always relative to the root of */
    /* the store, and will therefore never contain a drive letter. */

    szLastSlash = SzFindLastCh(peid->szPath, '\\');

    if (NULL == szLastSlash)
    {
        szName = (LPTSTR) peid->szPath;
    }
    else
    {
        szName = szLastSlash + 1;
    }

    return szName;
}

/*
 * FCheckEIDType
 *
 *  Purpose
 *      This function checks the pathname extension portion of the given
 *      entryid against the string given. Since files in the sample store
 *      have extensions that depend on the type of object within, comparing
 *      the extension will tell the caller whether the entryid is of the type
 *      specified by the extension passed in.
 *
 *  Parameters
 *      peid: A pointer to the entryid to check.
 *      szExt: A pointer to the string containing the extension to compare.
 *
 *  Returns: TRUE if the extensions matched, FALSE otherwise.
 */
BOOL FCheckEIDType(PEID peid, LPSTR szExt)
{
    BYTE *pb;

    if (peid == NULL)
        return FALSE;

    pb = (BYTE *) peid;
    pb += CbEID(peid);
    pb -= ((CCH_EXT + 1) * sizeof(TCHAR));

    return (lstrcmpi((LPTSTR) pb, szExt) == 0);
}

/*
 *  FIsRoot
 *
 *  Purpose     Determine if an EID is one for the root folder
 *
 *  Parameters  peid
 *
 *  Returns     TRUE or FALSE
 */
BOOL FIsRoot(PEID peid)
{
    return (NULL == peid) || *(peid->szPath) == '\0';
}

/*
 *  FIsFolder
 *
 *  Parameters  peid    pointer to entryid of object
 *
 *  Purpose     return TRUE if the entryID is one for a folder
 *
 *  Returns     TRUE If the entryID is one for a folder, FALSE otherwixe
 *
 */
BOOL FIsFolder(PEID peid)
{
    /* root is a folder */
    if (FIsRoot(peid))
        return TRUE;

    return (FCheckEIDType(peid, FOLDER_EXT));
}

/*
 *  FIsUnsavedMsg
 *
 *  Purpose     Determine if a message has had changes saved
 *
 *  Parameters  pimsg: A pointer to the message object to check.
 *
 *  SideEffect
 *              Will say that a message is saved if another open version
 *              has saved it.
 *
 *  Returns     TRUE or FALSE
 */
BOOL FIsUnsavedMsg(PIMSG pimsg)
{
    return (FIsUnsavedEID((PEID) pimsg->peid));
}

/*
 *  HrDeconstructEID
 *
 *  Purpose:
 *      Given an EID, return its component parts (MAPIUID, path to
 *      file, and file name).  This is NOT a general path parser.
 *      Instead, because we know the exact structure of the EIDs
 *      and paths we construct, we can directly access the
 *      individual components.
 *
 *  Parameters
 *      peid        EID to deconstruct.
 *      ppuid       Location in which to return a pointer to the
 *                  EID's MAPIUID.
 *      pszPath     Location in which to return a pointer to the
 *                  EID's file path.
 *      pszFile     Location in which to return a pointer to the
 *                  EID's file name.
 *
 *  Returns:
 *      HRESULT
 *
 *  Size effects:
 *      None.
 *
 *  Errors:
 *      MAPI_E_NOT_ENOUGH_MEMORY    Could not allocate memory for
 *                                  some or all of the return
 *                                  parameters.
 */
HRESULT HrDeconstructEID(PEID peid, LPMAPIUID *ppuid, LPTSTR *pszPath,
    LPTSTR *pszFile)
{
    SCODE sc;
    LPMAPIUID puid = NULL;
    LPTSTR szPath = NULL;
    LPTSTR szFile = NULL;
    LPTSTR szT = NULL;
    LPTSTR szEnd = NULL;

    AssertSz(!IsBadReadPtr(peid, CbNewEID(0)), "Bad peid #1");
    AssertSz(!IsBadReadPtr(peid, CbEID(peid)), "Bad peid #2");
    AssertSz(!IsBadWritePtr(ppuid, sizeof(LPMAPIUID)), "Bad ppuid");
    AssertSz(!IsBadWritePtr(pszPath, sizeof(LPTSTR)), "Bad pszPath");
    AssertSz(!IsBadWritePtr(pszFile, sizeof(LPTSTR)), "Bad pszFile");

    *ppuid = NULL;
    *pszPath = NULL;
    *pszFile = NULL;

    /* Get the UID out */

    sc = ScAlloc(sizeof(MAPIUID), &puid);
    if (sc != S_OK)
        goto exit;
    *puid = peid->uidResource;

    /* Get the path and file name out */
    szT = SzFindLastCh(peid->szPath, '\\');
    if (szT)
        szT++;
    else
        szT = peid->szPath;

    szEnd = (TCHAR *) ((BYTE *) peid + CbEID(peid));
    sc = ScAlloc((szEnd - szT) * sizeof(TCHAR), &szFile);
    if (sc != S_OK)
        goto exit;

    if ((LPBYTE) szEnd - (LPBYTE) szT)
        memcpy(szFile, szT, (LPBYTE) szEnd - (LPBYTE) szT);

    if (szT != peid->szPath)
    {
        sc = ScAlloc((LPBYTE) szT - (LPBYTE) (peid->szPath), &szPath);
        if (sc != S_OK)
            goto exit;

        /* We copy the trailing backslash along with the rest of   */
        /* the string, then overwrite it with the NULL terminator. */
        memcpy(szPath, peid->szPath, (LPBYTE) szT - (LPBYTE) (peid->szPath));
        *(szPath + (szT - peid->szPath) - 1) = '\0';
    }
    else
    {
        sc = ScAlloc(sizeof(TCHAR), (PPV) &szPath);
        if (sc != S_OK)
            goto exit;

        *szPath = '\0';
    }

exit:
    if (sc)
    {
        (void)FreeNull((LPVOID) puid);
        (void)FreeNull((LPVOID) szPath);
        (void)FreeNull((LPVOID) szFile);
    }
    else
    {
        *ppuid = puid;
        *pszPath = szPath;
        *pszFile = szFile;
    }

    DebugTraceSc(HrDeconstructEID, sc);
    return ResultFromScode(sc);
}

/*
 *  HrAppendPath
 *
 *  Purpose:
 *      Concatenate a path onto another, allocating space for the
 *      result.
 *
 *  Parameters
 *      szBase          Beginning of concatenated path.
 *      szAppend        End of concatenated path.
 *      pszFullPath     Pointer in which to place a pointer to the
 *                      newly allocated concatenated path.
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      MAPI_E_NOT_ENOUGH_MEMORY    Unable to allocate memory for
 *                                  the return variable.
 */
HRESULT HrAppendPath(LPTSTR szBase, LPTSTR szAppend, LPTSTR * pszFullPath)
{
    SCODE sc = S_OK;
    TCHAR rgch[512];

    AssertSz(szBase, "Bad szBase");
    AssertSz(szAppend, "Bad szAppend");
    AssertSz(pszFullPath, "Bad pszFullPath");
    AssertSz(szAppend[0] != '\\',
        "szAppend not relative path");

    if (!FAppendPathNoMem(szBase, szAppend, sizeof rgch / sizeof rgch[0],
            rgch))
    {
        sc = MAPI_E_STRING_TOO_LONG;
        goto exit;
    }

    sc = ScAlloc(Cbtszsize(rgch), (PPV) pszFullPath);
    if (sc != S_OK)
        goto exit;

    lstrcpy(*pszFullPath, rgch);

exit:
    DebugTraceSc(HrAppendPath, sc);
    return ResultFromScode(sc);
}

/*
 *  FAppendPathNoMem
 *
 *  Purpose:
 *      Concatenate two parts of a file path, returning result in a
 *      preallocated buffer.
 *
 *  Parameters
 *      szBase          First part of path to concatenate.
 *      szAppend        Second part of path to concatenate.
 *      cchFullPath     Size of return buffer.
 *      szFullPath      Return buffer.
 *
 *  Returns:
 *      BOOL.  TRUE if the return buffer is large enough to hold
 *      the resultant string, FALSE if the buffer is not large
 *      enough (value in szFullPath is undefined).
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      None.
 */
BOOL FAppendPathNoMem(LPTSTR szBase, LPTSTR szAppend, ULONG cchFullPath,
    LPTSTR szFullPath)
{
    UINT cchBase = 0;
    UINT cchAppend = 0;
    UINT cchFull = 0;
    BOOLEAN fPostSlash = FALSE;

    AssertSz(szBase, "Bad szBase");
    AssertSz(szAppend, "Bad szAppend");
    AssertSz(szFullPath, "Bad szFullPath");
    AssertSz(szAppend[0] != '\\',
        "szAppend not relative path");

    cchBase = lstrlen(szBase);
    cchAppend = lstrlen(szAppend);

    /* Check if szBase has trailing backslash, else we'll need to add it */

    if (*(szBase + cchBase - 1) == '\\')
    {
        fPostSlash = TRUE;
        cchFull = cchBase + cchAppend + 1;
    }
    else
    {
        fPostSlash = FALSE;
        cchFull = cchBase + cchAppend + 2;
    }

    if (cchFull <= cchFullPath)
    {
        lstrcpy(szFullPath, szBase);
        if (!fPostSlash)
        {
            lstrcat(szFullPath, TEXT("\\"));
        }
        lstrcat(szFullPath, szAppend);

        return TRUE;
    }

    return FALSE;
}

/*
 *  ReplaceExt
 *
 *  Purpose:
 *      Substitute the filename extension in szFile with the new
 *      one passed in as szExt.  It is the caller's
 *      responsibility to ensure that the filename has room for the
 *      new extension.  Also, the extension must include the
 *      period.
 *
 *  Parameters
 *      szFile      Filename on which to operate.
 *      szExt       New extension.
 *
 *  Returns:
 *      void.
 */
void ReplaceExt(LPTSTR szFile, LPTSTR szExt)
{
    LPTSTR szT = NULL;

    AssertSz(!IsBadStringPtr(szFile, (UINT) -1), "Bad szFile");
    AssertSz(!IsBadStringPtr(szExt, (UINT) -1), "Bad szExt");

    szT = SzFindLastCh(szFile, '.');

    if (szT)
        lstrcpy(szT, szExt);
    #ifdef DEBUG
    else
        TrapSz("No extension found on szFile. Not replacing extension.");
    #endif

    return;
}

/*
 *  HrConstructEID
 *
 *  Purpose     return an new EntryID for an object
 *
 *  Parameters
 *      puidStore       UID for the store containing the object
 *      plmr            Pointer to the MAPI linked memory allocators.
 *      szNewName       new root relative path name of the object
 *      ppeidNew        address of pointer to new entryID
 *
 *  Returns:
 *      ULONG, PEID
 */
HRESULT HrConstructEID(LPMAPIUID puidStore, PLMR plmr, LPSTR szNewName,
    PEID *ppeidNew)
{
    PEID peidNew;               /* new entry id */
    ULONG cbEID;                /* number of bytes in the new entry id */
    ULONG cbNewName;
    SCODE sc;

    cbNewName = lstrlen(szNewName) + 1; /* we count the NULL terminator */
    cbEID = CbNewEID(cbNewName);

    /* allocate space for the new entry id */
    /* Use the MAPI allocator because it may be returned to the client */
    /* Note that we zero-fill this allocation so that the entryid produced */
    /* by identical input parameters will always be the same. If we didn't */
    /* zero fill, the pad bytes after the version would be randomly filled. */

    sc = LMAllocZ(plmr, cbEID, (PPV) &peidNew);
    if (sc != S_OK)
        goto exit;

    *(DWORD *) (peidNew->abFlags) = (DWORD) 0;
    peidNew->uidResource = *puidStore;
    peidNew->bVersion = SMPMS_VERSION;

    lstrcpy(peidNew->szPath, szNewName);

    if (peidNew->szPath[0])
        AnsiLowerBuff(peidNew->szPath, lstrlen(peidNew->szPath));

    *ppeidNew = peidNew;

exit:
    DebugTraceSc(HrConstructEID, sc);
    return ResultFromScode(sc);
}

/*
 * HrGetParentEID
 *
 *  Purpose         construct an entry id for the parent of peid. This
 *                  assumes that all files in the sample message store 
 *                  are CCH_NAME chars long (including NULL).
 *
 *  Parameters
 *      plmr        Pointer to the MAPI linked memory allocators.
 *      peid        entry id of object whose parent is requested
 *      ppeidParent pointer to parent's peid
 *
 */
HRESULT HrGetParentEID(PLMR plmr, PEID peid, PEID *ppeidParent)
{
    HRESULT hr;
    ULONG cbParentName = sizeof(TCHAR); /* number of bytes in szParentName */
    LPTSTR szParentName = NULL; /* name of parent */

    if (CbEIDPath(peid) > (CCH_NAME * sizeof(TCHAR)))
        cbParentName = CbEIDPath(peid) - (CCH_NAME * sizeof(TCHAR));

    hr = HrAlloc(cbParentName, (PPV) &szParentName);
    if (hr != hrSuccess)
        goto exit;

    if (cbParentName > sizeof(TCHAR))
        memcpy(szParentName, peid->szPath, (UINT) cbParentName);
    szParentName[cbParentName - sizeof(TCHAR)] = 0;

    hr = HrConstructEID(&(peid->uidResource), plmr, szParentName,
        ppeidParent);

exit:
    FreeNull(szParentName);
    DebugTraceResult(HrGetParentEID, hr);
    return hr;
}

/*
 * HrOpenParent
 *
 * Purpose  open the parent folder of the given entry id
 *
 * Parameters
 *  pims    store in which the object is
 *  peid    entry id of object whose parent is to be opened
 *  ulFlags MAPI_MODIFY if you want write permission on the store
 *  ppifld  pointer to variable to hold open parent
 */
HRESULT HrOpenParent(PIMS pims, PEID peid, ULONG ulFlags, PIFLD * ppifld)
{
    HRESULT hr = hrSuccess;
    PEID peidParent = NULL;
    ULONG ulObjectType;

    Assert(pims);
    Assert(peid);
    Assert(ppifld);

    *ppifld = NULL;
    hr = HrGetParentEID(&pims->lmr, peid, &peidParent);
    if (hr != hrSuccess)
        goto exit;

    hr = pims->lpVtbl->OpenEntry(pims, CbEID(peidParent),
        (LPENTRYID) peidParent, NULL, ulFlags, &ulObjectType,
        (LPUNKNOWN *) ppifld);
    if (hr != hrSuccess)
        goto exit;

    Assert(ulObjectType == MAPI_FOLDER);

exit:
    LMFree(&pims->lmr, peidParent);

    DebugTraceResult(HrOpenParent, hr);
    return hr;
}

/*
 * FreePropArrays
 *
 * Purpose      deallocate space for PropTag, PropValue and PropAttr arrays
 *              allocated with HrAllocPropArrays
 * Parameters
 *  ppval       address of property value array
 *  pptaga  address of the property tag array
 *  ppatra  address of the property attribute array
 */
void FreePropArrays(LPSPropValue *ppval, LPSPropTagArray *pptaga,
    LPSPropAttrArray *ppatra)
{
    Assert(ppval);
    Assert(pptaga);
    Assert(ppatra);

    FreeNull(*ppval);
    FreeNull(*pptaga);
    FreeNull(*ppatra);

    *ppval = NULL;
    *pptaga = NULL;
    *ppatra = NULL;
}

/*
 * HrAllocPropArrays
 *
 * Purpose      allocate space for PropTag, PropValue and PropAttr arrays
 *              Free with FreeNull or FreePropArrays
 * Parameters
 *  cProps  number of properties in the arrays
 *  ppval   address of property value array
 *  pptaga  address of the property tag array
 *  ppatra  address of the property attribute array
 */
HRESULT HrAllocPropArrays(ULONG cProps, LPSPropValue *ppval,
    LPSPropTagArray *pptaga, LPSPropAttrArray *ppatra)
{
    HRESULT hr;

    /* All three pointers must be provided. */
    Assert(!IsBadWritePtr(ppval, sizeof(LPSPropValue)));
    Assert(!IsBadWritePtr(pptaga, sizeof(LPSPropTagArray)));
    Assert(!IsBadWritePtr(ppatra, sizeof(LPSPropAttrArray)));

    /* All must be zero on entry for our cleanup mechanism. */
    AssertSz(!*ppval, "bad ppval");
    AssertSz(!*pptaga, "bad pptaga");
    AssertSz(!*ppatra, "bad ppatra");

    hr = HrAlloc(cProps * sizeof(SPropValue), ppval);
    if (hr != hrSuccess)
        goto exit;

    hr = HrAlloc(CbNewSPropTagArray(cProps), pptaga);
    if (hr != hrSuccess)
        goto exit;

    hr = HrAlloc(CbNewSPropAttrArray(cProps), ppatra);
    if (hr != hrSuccess)
        goto exit;

exit:
    if (hr != hrSuccess)
        FreePropArrays(ppval, pptaga, ppatra);

    DebugTraceResult(HrAllocPropArrays, hr);
    return hr;
}

/*
 * ProcessGetProps
 *
 *  Purpose
 *      Helper routine from HrWrap_GetProps. Folder and message objects in
 *      the sample store keep a few property values in memory so that when
 *      we move or copy a folder or message, the entryid, parent entryid,
 *      and (for copied messages) record key are correct. This routine 
 *      overrides the value returned from IMessage for any in-memory 
 *      properties. We keep a very small placeholder property for each
 *      of the in-memory properties on disk and mark it read-only and 
 *      not deletable. This keeps SetProps from succeeding on these
 *      properties. All properties that we override in this function are
 *      PT_BINARY property types, so HrWrap_GetProps only calls this 
 *      function if the property it is looking for is a PT_BINARY.
 *
 *      This function tries to find the property that the client is 
 *      requesting in the in-memory array of properties stored with the
 *      object. If the routine finds the property, then it tries to allocate
 *      and copy the correct data into the client's array. If the allocation
 *      fails, the routine fills in a PT_ERROR into the client's property
 *      value. Note that HrWrap_GetProps needs to watch for PT_ERROR coming
 *      back and return the appropriate warning to the client. 
 *      If the routine doesn't find the property, then it returns to
 *      HrWrap_GetProps without modifying the client's array at all.
 *
 *  Parameters
 *      pvalClient: A pointer to the property value to search for in our
 *          in-memory property array. This function may MODIFY this value.
 *      cvalInt: The number of in-memory properties on this object. If the
 *          object has no in-memory properties, this value will be zero.
 *      pvalInt: A pointer to the object's array of in-memory properties.
 *      plmr: A pointer to the linked memory allocation routines.
 *      pvOrig: The original allocated pointer (AllocateMore needs this).
 *
 *  Returns
 *      None. May have modified the client's property value if there was
 *      a matching entry in the in-memory array.
 */
static void ProcessGetProps(LPSPropValue pvalClient, ULONG cvalInt,
    LPSPropValue pvalInt, PLMR plmr, LPVOID pvOrig)
{
    ULONG ulClientID = PROP_ID(pvalClient->ulPropTag);
    ULONG ulClientType = PROP_TYPE(pvalClient->ulPropTag);
    LPSPropValue pvalT;
    LPSPropValue pvalTMac;

    pvalT = pvalInt;
    pvalTMac = pvalT + cvalInt;

    for (; pvalT < pvalTMac; ++pvalT)
    {
        LPVOID pv;
        ULONG cb;
        SCODE sc;

        AssertSz(PROP_TYPE(pvalT->ulPropTag) == PT_BINARY,
            "Code assumes all internal props are PT_BINARY");

        if (ulClientID == PROP_ID(pvalT->ulPropTag))
        {
            cb = pvalT->Value.bin.cb;
            pv = pvalT->Value.bin.lpb;

            /* Link onto returned data our extra info. */
            sc = LMAllocMore(plmr, cb, pvOrig, &pvalClient->Value.bin.lpb);
            if (sc != S_OK)
            {
                pvalClient->Value.err = sc;
                pvalClient->ulPropTag = PROP_TAG(PT_ERROR, ulClientID);
            }
            else
            {
                pvalClient->Value.bin.cb = cb;
                if (cb)
                    memcpy(pvalClient->Value.bin.lpb, pv, (UINT) cb);
                pvalClient->ulPropTag = PROP_TAG(PT_BINARY, ulClientID);
            }

            break;
        }
    }

    return;
}

/*
 * HrWrap_GetProps
 *
 * Purpose
 *  Adjust return from GetProps (Store, Folder, Message, etc) for wrapped
 *  values of PR_STORE_ENTRYID, PR_STORE_RECORD_KEY and (if a store)
 *  PR_ENTRYID. Doesn't allow the return of PR_ENTRYID for an unsaved
 *  message. Also overwrites values for properties that the object has
 *  cached in memory using the helper routine ProcessGetProps.
 *              
 * Parameters
 *  hr              HRESULT from the original GetProps call.
 *  pims            pointer to the message store object
 *  cvalInt         the number of property values that are held in memory 
 *                  associated with the object.
 *  pvalInt         a pointer to the array of in-memory properties associated
 *                  with the object. May be NULL if cvalInt is 0.
 *  pcValues        The number of values in client's PropValue array
 *  ppval           a pointer to the client's PropValue array
 *  fStore          TRUE if the object given the GetProps call was the
 *                  message store object.
 *  fTagsSpecified  TRUE if the client specified a proptag array on the call;
 *                  FALSE if the client passed NULL for the proptag array.
 *
 * Coding comments:
 *  The objects must contain these properties, of the appropriate
 *  type, but it isn't necessary that their values IN the objects be
 *  accurate. The KEYS, for example, don't even have to be 16 bytes.
 *
 *  The result code may be adjusted depending on whether this routine
 *  or the underlying property implementation, ran out of memory
 *  while dealing with one of these.
 *
 *  The PR_RECORD_KEY (a UID) in a Store IS the right value,
 *  and does not need to be wrapped.
 */
HRESULT HrWrap_GetProps(HRESULT hr, PIMS pims, ULONG cvalInt,
    LPSPropValue pvalInt, ULONG * pcValues, LPSPropValue * ppval,
    BOOL fStore, BOOL fTagsSpecified, POBJ pobj)
{
    /* Warning: pcValues and ppval parameters may not           */
    /* have been validated.  Do not dereference them unless     */
    /* the "hr" says everything succeeded so far.               */

    BOOL fErrors = FALSE;
    LPSPropValue pval;
    LPSPropValue pvalMac;

    /* No work to do unless the GetProps() generally succeeded. */
    if (HR_FAILED(hr))
        goto exit;

    pval = *ppval;
    pvalMac = pval + *pcValues;

    for (; pval < pvalMac; ++pval)
    {
        UINT ulType = (UINT) PROP_TYPE(pval->ulPropTag);
        UINT ulID;
        LPVOID pv;
        ULONG cb;
        SCODE sc;

        if(pval->ulPropTag == PR_ACCESS_LEVEL)
        {
            pval->Value.l = OBJ_TestFlag(pobj, OBJF_MODIFY) ? MAPI_MODIFY : 0;
        }
        
        if(pval->ulPropTag == PR_ACCESS)
        {
            if(OT_FOLDER == pobj->wType)
            {
                pval->Value.l = MAPI_ACCESS_READ;
            
                if(OBJ_TestFlag(pobj, OBJF_MODIFY))
                    pval->Value.l |= MAPI_ACCESS_MODIFY |
                                    MAPI_ACCESS_CREATE_CONTENTS |
                                    MAPI_ACCESS_CREATE_HIERARCHY;

                if(OBJ_TestFlag(pobj->pobjParent, OBJF_MODIFY))
                    pval->Value.l |= MAPI_ACCESS_DELETE;
            }
            else if(OT_MESSAGE == pobj->wType)
            {
                pval->Value.l = MAPI_ACCESS_READ;
            
                if(OBJ_TestFlag(pobj, OBJF_MODIFY))
                    pval->Value.l |= MAPI_ACCESS_MODIFY;

                if(OBJ_TestFlag(pobj->pobjParent, OBJF_MODIFY))
                    pval->Value.l |= MAPI_ACCESS_DELETE;
            }
            else
            {
                pval->ulPropTag = PROP_TAG(PT_ERROR, PROP_ID(PR_ACCESS));
                pval->Value.err = MAPI_E_NOT_FOUND;
            }
        }

        if (ulType != PT_BINARY && ulType != PT_ERROR)
            continue;

        if (ulType == PT_ERROR && pval->Value.err == MAPI_E_UNEXPECTED_TYPE)
        {
            fErrors = TRUE;
            continue;
        }

        if (cvalInt != 0)
        {
            ProcessGetProps(pval, cvalInt, pvalInt, &pims->lmr,
                (LPVOID) *ppval);

            /* Recompute the prop type in case ProcessGetProps changed it. */
            ulType = (UINT) PROP_TYPE(pval->ulPropTag);
        }

        /* These values should be computed here just in case ProcessGetProps */
        /* modifies pval. */

        ulID = (UINT) PROP_ID(pval->ulPropTag);

        if (ulID == PROP_ID(PR_STORE_RECORD_KEY))
        {
            cb = sizeof(pims->uidResource);
            pv = &pims->uidResource;
        }
        else if (ulID == PROP_ID(PR_STORE_ENTRYID)
            || (fStore && ulID == PROP_ID(PR_ENTRYID)))
        {
            cb = pims->eidStore.cb;
            pv = pims->eidStore.lpb;
        }
        else if (ulID == PROP_ID(PR_ENTRYID) && ulType != PT_ERROR)
        {
            /* entryid of a message doesn't exist until SaveChanges(). */
            if (FIsUnsavedEID((PEID) pval->Value.bin.lpb))
            {
                if (fTagsSpecified)
                {
                    fErrors = TRUE;
                    pval->ulPropTag = PROP_TAG(PT_ERROR, ulID);
                    pval->Value.err = MAPI_E_NOT_FOUND;
                }
                else
                {
                    /* The client wants all properties, and did not */
                    /* specify a prop tag array. The client therefore */
                    /* doesn't want NOT_FOUND errors. */
                    /* Overwrite the error entry with the last SPropValue */
                    /* in the array. */

                    (*pcValues)--;
                    pvalMac--;

                    if (pval < pvalMac)
                    {
                        memcpy(pval, pvalMac, sizeof(SPropValue));
                        --pval; /* redo this value, since we just changed it */
                    }
                }
            }
            continue;
        }
        else
        {
            /* Remember if any errors occur in final array. */
            if (ulType == PT_ERROR)
            {
                if (    pval->Value.err == MAPI_E_NOT_FOUND
                    &&  !fTagsSpecified)
                {
                    /* The client wants all properties, and did not */
                    /* specify a prop tag array. The client therefore */
                    /* doesn't want NOT_FOUND errors. */
                    /* Overwrite the error entry with the last SPropValue */
                    /* in the array. */

                    (*pcValues)--;
                    pvalMac--;

                    if (pval < pvalMac)
                    {
                        memcpy(pval, pvalMac, sizeof(SPropValue));
                        --pval; /* redo this value, since we just changed it */
                    }
                }
                else
                    fErrors = TRUE;
            }
            continue;
        }

        /* Link onto returned data our extra info. */
        sc = LMAllocMore(&pims->lmr, cb, (LPVOID) *ppval,
            &pval->Value.bin.lpb);
        if (sc != S_OK)
        {
            fErrors = TRUE;
            pval->Value.err = sc;
            pval->ulPropTag = PROP_TAG(PT_ERROR, ulID);
        }
        else
        {
            pval->Value.bin.cb = cb;
            if (cb)
                memcpy(pval->Value.bin.lpb, pv, (UINT) cb);
            pval->ulPropTag = PROP_TAG(PT_BINARY, ulID);
        }
    }

    /* Adjust HRESULT based on PT_ERRORs now. */
    if (!fErrors)
        hr = hrSuccess;
    else if (hr == hrSuccess)
        hr = ResultFromScode(MAPI_W_ERRORS_RETURNED);

exit:
    #ifdef DEBUG
    if (GetScode(hr) != MAPI_W_ERRORS_RETURNED)
        DebugTraceResult(HrWrap_GetProps, hr);
    #endif

    return hr;
}

/*
 * FIsSubmittedMessage
 *
 * Purpose      return TRUE if the message (specified by entryid) is submitted.
 *
 * Parameters
 *  pims        A pointer to the message store object.
 *  peid        The entryid of message to check.
 */
BOOL FIsSubmittedMessage(PIMS pims, PEID peid)
{
    HRESULT hr;
    PIMSG pimsgT = NULL;
    ULONG ulObjType;

    hr = pims->lpVtbl->OpenEntry(pims, CbEID(peid), (LPENTRYID) peid,
        NULL, MAPI_MODIFY, &ulObjType, (LPUNKNOWN *) &pimsgT);

    UlRelease(pimsgT);

    return (GetScode(hr) == MAPI_E_SUBMITTED);
}

/*
 *  HrOpenIMsgSession
 *
 *  Purpose:
 *      Open an IMsgSession, and return the pointer to the caller.
 *
 *  Parameters
 *      ppmsgsess: Pointer to the location to return the opened msg session.
 *
 *  Returns:
 *      HRESULT
 */
HRESULT HrOpenIMsgSession(LPMSGSESS *ppmsgsess)
{
    PINST pinst = (PINST) PvGetInstanceGlobals();

    Assert(pinst);
    Assert(pinst->lpmalloc);

    if (pinst == NULL)
        return ResultFromScode(MAPI_E_CALL_FAILED);

    return ResultFromScode(OpenIMsgSession(pinst->lpmalloc, 0L, ppmsgsess));
}

/*
 *  HrOpenIMsg
 *
 *  Purpose:
 *      Open the file given as a docfile, and then create an IMSG.DLL
 *      object on top of the storage.
 *
 *  Parameters
 *      pmsgsess    The message session to open the message within.
 *                  May be NULL (for ConfirmCred in msplogon to work).
 *      szFile      The file to open.
 *      plmr        a pointer to the linked memory routines.
 *      psup        a pointer to the MAPI support object.
 *      fCreate     TRUE means the caller wants to create the storage.
 *                  FALSE means open an existing storage.
 *      fModify     TRUE means the caller wants read/write access.
 *                  FALSE means read-only access. (This argument is 
 *                  ignored when fCreate is TRUE; in that case, the
 *                  file is always opened read/write.)
 *      fExclusive  TRUE means the caller wants exclusive access to the
 *                  storage, and to fail creation if the storage already
 *                  exists.
 *      ppmsg       Address of a location in which to return a
 *                  pointer to the newly opened IMessage instance.
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      IMessage on IStorage opening errors.
 */
HRESULT HrOpenIMsg(LPMSGSESS pmsgsess, LPSTR szFile, PLMR plmr, LPMAPISUP psup,
    BOOL fCreate, BOOL fModify, BOOL fExclusive, LPMESSAGE *ppmsg)
{
    HRESULT hr;
    SCODE sc;
    DWORD grfMode;
    LPSTORAGE lpstg = NULL;
    PINST pinst = (PINST) PvGetInstanceGlobals();

#ifdef _WIN32
    OLE_CHAR szOle[MAX_PATH];
    int cbFile = 0L;
#else
    OLE_CHAR *szOle = NULL;
#endif

    Assert(pinst);
    Assert(pinst->lpmalloc);

#ifdef _WIN32
    cbFile = 1 + lstrlen(szFile);
    Assert(cbFile < MAX_PATH);

    MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szFile, cbFile, szOle, cbFile);
#else
    szOle = szFile;
#endif

    grfMode = STGM_TRANSACTED;

    if (fExclusive)
    {
        grfMode |= STGM_SHARE_EXCLUSIVE;

        if (fCreate)
            grfMode |= STGM_FAILIFTHERE;
    }
    else
        grfMode |= STGM_SHARE_DENY_NONE;

    if (fCreate)
    {
        grfMode |= (STGM_READWRITE | STGM_CREATE);

        hr = StgCreateDocfile(szOle, grfMode, 0, &lpstg);

        /* Commit docfile changes.  If we don't do this now, the file on  */
        /* disk will NOT be a docfile (i.e. OLE2 will not recognize it as */
        /* a docfile) if opened again with no other changes made to it.   */

        if (hr == hrSuccess)
            hr = lpstg->lpVtbl->Commit(lpstg, 0);
    }
    else
    {
        if (fModify)
            grfMode |= STGM_READWRITE;
        else
            grfMode |= STGM_READ;

        hr = StgOpenStorage(szOle, NULL, grfMode, NULL, 0, &lpstg);
    }

    if (hr != hrSuccess)
    {
        sc = MapStorageSCode(GetScode(hr));
        goto exit;
    }

    sc = OpenIMsgOnIStg(pmsgsess, plmr->lpAllocBuf, plmr->lpAllocMore,
        plmr->lpFreeBuf, pinst->lpmalloc, psup, lpstg, NULL, 0, 0, ppmsg);

    UlRelease(lpstg);

exit:
    if (sc != S_OK && fCreate)
        DeleteFile(szFile);

    DebugTraceSc(HrOpenIMsg, sc);
    return ResultFromScode(sc);
}

/*
 * HrSetOneROProp
 *
 *  Purpose
 *      The sample store needs to change properties that the client isn't
 *      allowed to change. This function allows the sample store to change
 *      a single property in the underlying IMessage object by first
 *      setting the attributes on that property to allow it to be written,
 *      then writing the property, and finally, setting the attributes back
 *      to once again only allow reading. Note that if the sample store 
 *      calls this routine on a property that is writable, this routine
 *      will make it non-writable.
 *
 *  Parameters
 *      lpmsg: A pointer to the IMessage object in which to set the property.
 *      plmr: A pointer to the linked memory allocation routines.
 *      ulPT: The property tag to set within the object.
 *      pv: A pointer to the property value to set.
 */
HRESULT HrSetOneROProp(LPMESSAGE lpmsg, PLMR plmr, ULONG ulPT, LPVOID pv)
{
    HRESULT hr;
    LPSPropAttrArray patra = NULL;
    LPSPropProblemArray pprba = NULL;

    SizedSPropTagArray(1, spta);

    /* Should be changing the pval array inside the object. */

    AssertSz(   ulPT != PR_ENTRYID
            &&  ulPT != PR_PARENT_ENTRYID
            &&  ulPT != PR_RECORD_KEY
            &&  ulPT != PR_INSTANCE_KEY, "Changing internal props in IMSG");

    spta.cValues = 1;
    spta.aulPropTag[0] = ulPT;

    /* Get current attributes and make the properties writable */

    hr = GetAttribIMsgOnIStg(lpmsg, (LPSPropTagArray) &spta, &patra);
    if (hr != hrSuccess)
        goto exit;

    patra->aPropAttr[0] |= PROPATTR_WRITEABLE;

    hr = SetAttribIMsgOnIStg(lpmsg, (LPSPropTagArray) &spta, patra, &pprba);
    if (hr != hrSuccess || pprba)
        goto exit;

    hr = HrSetSingleProp((LPMAPIPROP) lpmsg, plmr, ulPT, pv);
    if (hr != hrSuccess)
        goto exit;

    /* Restore the attribute */

    patra->aPropAttr[0] &= ~PROPATTR_WRITEABLE;

    hr = SetAttribIMsgOnIStg(lpmsg, (LPSPropTagArray) &spta, patra, &pprba);
    if (hr != hrSuccess || pprba)
        goto exit;

exit:
    if (pprba)
    {
        LMFree(plmr, pprba);
        hr = ResultFromScode(MAPI_E_CALL_FAILED);
    }

    LMFree(plmr, patra);

    DebugTraceResult(HrSetOneROProp, hr);
    return hr;
}

/*
 * HrGetSingleProp
 *
 *  Purpose
 *      Gets a property from an object, and returns the value by stuffing
 *      it into a separately passed pointer. This function is nice because
 *      it doesn't require the caller to have an SPropValue around simply
 *      to retrieve the value of a property that is a known size.
 *
 *  Parameters
 *      pmprop  The property object to get the property from.
 *      plmr    Pointer to MAPI's linked memory routines.
 *      ulPT    The property tag to get.
 *      pv      A pointer to the location to place the value of the property.
 *
 *  Returns
 *      HRESULT. No warnings are returned because this function retrieves
 *      only one property at a time.
 */
HRESULT HrGetSingleProp(LPMAPIPROP pmprop, PLMR plmr, ULONG ulPT, LPVOID pv)
{
    LPSPropValue pval = NULL;
    SCODE sc;
    HRESULT hr;
    ULONG cValues;

    SizedSPropTagArray(1, spta);

    spta.cValues = 1;
    spta.aulPropTag[0] = ulPT;

    hr = pmprop->lpVtbl->GetProps(pmprop, (LPSPropTagArray) &spta, 0, /* ansi */
        &cValues, &pval);

    sc = GetScode(hr);

    if ((sc != S_OK)
        && (sc != MAPI_W_ERRORS_RETURNED))
        goto exit;

    switch (PROP_TYPE(pval->ulPropTag))
    {
    case PT_I2:
    case PT_BOOLEAN:
        Assert(!IsBadWritePtr(pv, sizeof(short)));
        *(short *)pv = pval->Value.i;
        break;

    case PT_LONG:
    case PT_R4:
        Assert(!IsBadWritePtr(pv, sizeof(LONG)));
        *(LONG *) pv = pval->Value.l;
        break;

    case PT_DOUBLE:
    case PT_APPTIME:
    case PT_SYSTIME:
    case PT_I8:
    case PT_CURRENCY:
        Assert(!IsBadWritePtr(pv, sizeof(LARGE_INTEGER)));
        *(LARGE_INTEGER *) pv = pval->Value.li;
        break;

    case PT_ERROR:
        sc = pval->Value.err;
        break;

    default:
        TrapSz1("Unimplemented PROP_TYPE %08lX passed in.",
            PROP_TYPE(pval->ulPropTag));
    }

    LMFree(plmr, pval);

exit:
    AssertSz1(sc <= 0, "Logic error: sc %s returned from HrGetSingleProp.",
        SzDecodeScode(sc));

    DebugTraceSc(HrGetSingleProp, sc);
    return (ResultFromScode(sc));
}

/*
 *  HrSetSingleProp
 *
 *  Purpose:
 *      Sets one property and its separately passed value. This function
 *      is nice because it doesn't require the caller to have a SPropValue
 *      to pass in.
 *
 *  Parameters
 *      pmprop  The property object to set the property into.
 *      plmr    Pointer to MAPI's linked memory routines.
 *      ulPT    The property to set
 *      pv      A pointer to the value of the property
 *
 *  Returns:
 *  Any errors from SetProps. Note that no warnings or problem arrays are
 *      returned because this routine only sets one property.
 */
HRESULT HrSetSingleProp(LPMAPIPROP pmprop, PLMR plmr, ULONG ulPT, LPVOID pv)
{
    HRESULT hr;
    SPropValue sval;
    LPSPropProblemArray pprba = NULL;

    sval.ulPropTag = ulPT;

    switch (PROP_TYPE(ulPT))
    {
    case PT_I2:
    case PT_BOOLEAN:
        sval.Value.i = *(short *)pv;
        break;

    case PT_LONG:
    case PT_R4:
    case PT_UNICODE:
    case PT_STRING8:
    case PT_CLSID:
        AssertSz(sizeof(LPVOID) == sizeof(LONG),
            "Pointers are not the size of a long on this machine");
        sval.Value.l = *(LONG *) pv;
        break;

    case PT_DOUBLE:
    case PT_APPTIME:
    case PT_SYSTIME:
    case PT_I8:
    case PT_CURRENCY:
    case PT_OBJECT:
    case PT_BINARY:
        sval.Value.li = *(LARGE_INTEGER *) pv;
        break;

    default:
        TrapSz1("Unimplemented PROP_TYPE %08lX passed in.", PROP_TYPE(ulPT));
    }

    hr = pmprop->lpVtbl->SetProps(pmprop, 1, &sval, &pprba);

    if (hr == hrSuccess && pprba)
        hr = ResultFromScode(pprba->aProblem[0].scode);

    LMFree(plmr, pprba);

    DebugTraceResult(HrSetSingleProp, hr);
    return hr;
}

/*
 *  FContainsProp
 *
 *  Purpose:
 *      returns whether or not a PropTag exists in a PropTagArray
 *
 *  Parameters
 *      ulPropTag   The property to search for.
 *      ptaga       A pointer to the SPropTagArray to search. May be null,
 *                  in which case, the function will return FALSE.
 *
 *  Returns:
 *      TRUE    if ulPropTag is in ptaga
 *      FALSE   if not
 */
BOOL FContainsProp(ULONG ulPropTag, LPSPropTagArray ptaga)
{
    ULONG *pulPropTag;
    ULONG *pulPropMax;

    if (!ptaga)
        return FALSE;

    pulPropTag = ptaga->aulPropTag;
    pulPropMax = pulPropTag + ptaga->cValues;

    while (pulPropTag < pulPropMax)
    {
        if (ulPropTag == *pulPropTag)
            return TRUE;

        pulPropTag++;
    }

    return FALSE;
}
