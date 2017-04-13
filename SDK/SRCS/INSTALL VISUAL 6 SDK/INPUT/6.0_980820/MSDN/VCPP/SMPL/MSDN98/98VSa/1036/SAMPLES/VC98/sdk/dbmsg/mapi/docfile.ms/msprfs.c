/*
 *  M S P R F S . C
 *
 *  Code for implementing Get/SetReceiveFolder for the Message
 *  Store object.
 *
 *  Hungarian shorthand:
 *      To avoid excessively long identifier names, throughout this
 *      file, RFS is used to mean "Receive Folder Settings", and RFN
 *      is used to mean an RFS Node.
 *
 *  Copyright 1992-1995 Microsoft Corporation.  All Rights Reserved.
 */

#include "msp.h"

/* Manifest constants */

TCHAR szRFSStreamName[] = TEXT("RFS_STREAM");

/* GRoup of Flags (grf):
 *
 * grfStorageOpen:      Flags used to open a read/write OLE IStorage object.
 * grfStorageOpenRO:    Flags used to open a read only OLE IStorage object.
 * grfStorageCreate:    Flags used to create an OLE IStorage object.
 * grfStreamOpen:       Flags used to open a read/write OLE IStream object.
 * grfStreamOpenRO:     Flags used to open a read only OLE IStream object.
 * grfStreamCreate:     Flags used to create an OLE IStream object.
 *
 * See the OLE 2 Programmer's Reference for details on these flags.
 */

#define grfStorageOpen      STGM_READWRITE | STGM_SHARE_EXCLUSIVE | \
                                STGM_TRANSACTED
#define grfStorageOpenRO    STGM_READ | STGM_SHARE_EXCLUSIVE | \
                                STGM_TRANSACTED
#define grfStorageCreate    grfStorageOpen | STGM_FAILIFTHERE | STGM_CREATE

#define grfStreamOpen       STGM_SHARE_EXCLUSIVE | STGM_READWRITE
#define grfStreamOpenRO     STGM_SHARE_EXCLUSIVE | STGM_READ
#define grfStreamCreate     grfStreamOpen | STGM_FAILIFTHERE

/* Function prototypes */

static HRESULT OpenRFSStream(PRFS prfs, BOOL fModify, IStream **lppstream,
    LPSTORAGE *lppstg);
static void CloseRFSStream(IStream * lpstream, LPSTORAGE lpstg);

/*
 *  Exported functions
 */

/*
 *  FIsValidMessageClass
 *
 *  Purpose:
 *      Checks to see if a message class is valid.  A valid message
 *      class is defined to be a series of one or more
 *      period-delimited tokens with each token being a series of
 *      one or more ASCII characters in the range 32-126
 *      (inclusive) excluding period.  Note that this definition
 *      excludes message classes with a leading or trailing
 *      period, or two or more consecutive periods, because this
 *      would imply the existence of a zero-length token.
 *
 *      We put this function in the RFS module because dealing with
 *      receive folders is the primary place in the Sample Store where we
 *      care about message class.
 *
 *  Arguments:
 *      szMessageClass  String identifying the message class.
 *
 *  Returns:
 *      BOOL.  TRUE if szMessage is valid, FALSE if not.
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      None.
 */
BOOL FIsValidMessageClass(LPTSTR szMessageClass)
{
    TCHAR *pch = szMessageClass;
    BOOL fWasPeriod = TRUE;

    if (szMessageClass && IsBadStringPtr(szMessageClass, (UINT) -1))
        return FALSE;

    /* Handle the default message class */

    if (!szMessageClass || *szMessageClass == '\0')
        return TRUE;

    /* disallow things:bad chars and cases where */
    /* period is not a delim(.1, 1., and 1. .1 bad) */
    while (*pch)
    {
        if (*pch < 32 || *pch > 126)
            return FALSE;
        if (*pch == '.')
        {
            if (fWasPeriod)
                return FALSE;
            fWasPeriod = TRUE;
        }
        else
            fWasPeriod = FALSE;
        pch++;
    }

    return !fWasPeriod;
}

/*
 *  OpenRFS
 *
 *  Purpose:
 *      Given an OLE2 storage object, opens a stream on it and
 *      prepares it for handling receive folder settings.  OpenRFS
 *      returns to the caller a pointer to the RFS structure which
 *      is then used for access to the settings.  The stream format
 *      of the receive folder settings is extremely simple:  the
 *      first ULONG is a count of the number of RFNs in the
 *      stream, and the nodes themselves follow sequentially
 *      afterward.  A node on disk is not the same as an RFN in
 *      memory.  On disk, it is a variable-sized structure
 *      containing a ULONG which is the size (in bytes) of the
 *      node not including this field, then a ULONG which is the
 *      length (in bytes) of a
 *      string containing the message class (NULL inclusive), which
 *      immediately follows.  After that is a ULONG which is the
 *      size (in bytes) of a string containing the relative path
 *      name of the receive folder (NULL inclusive), which also
 *      immediately follows.  Visually, a node looks like the
 *      following:
 *
 *          +--------------------+
 *          | ULONG cbNode       |
 *          +--------------------+
 *          | ULONG cbClass      |
 *          +--------------------+
 *          | TCHAR szClass[]    |
 *          |   .                |
 *          |   .                |
 *          |   .                |
 *          +--------------------+
 *          | ULONG cbPath       |
 *          +--------------------+
 *          | TCHAR szPath[]     |
 *          |   .                |
 *          |   .                |
 *          |   .                |
 *          +--------------------+
 *
 *      The size of the message class name, cbClass, will always be
 *      > 0 for "valid" nodes (the default message class will be a
 *      NULL string of size 1 TCHAR).  Thus, a value of 0 for
 *      cbClass will signify a "free" node.  Free nodes are created
 *      in the normal use of the stream by DeleteRFN, which
 *      SetReceiveFolder calls, and are removed at close time (see
 *      CloseRFS, below).
 *
 *      Note that, because string lengths are byte-sized but the
 *      strings themselves are made of TCHARs, translation between
 *      BYTE and TCHAR sizes must be done.
 *
 *  Arguments:
 *      szStoreRoot Full path to the sample store "root"
 *                      directory.
 *      szFile      Relative path name of docfile containing
 *                      receive folder settings.
 *      ulFlags         Flags.  The following are defined:
 *                      RFS_CREATE  Create the docfile containing
 *                                  receive folder settings
 *                                  (default opens existing).
 *      pprfs           Location in which to return a pointer to
 *                      the newly created RFS structure.
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      Various.
 */
HRESULT OpenRFS(LPTSTR szStoreRoot, LPTSTR szFile, ULONG ulFlags, PRFS *pprfs)
{
    HRESULT hr = hrSuccess;
    HRESULT hrStg = hrSuccess;
    SCODE sc;
    LPTSTR szFullPath = NULL;
    ULONG cRFN = 0L;
    LPSTORAGE lpstg = NULL;
    IStream *lpstream = NULL;
    PRFS prfs = NULL;

#ifdef _WIN32
    OLE_CHAR szOle[MAX_PATH];
    int cbOle = 0L;

#else
    OLE_CHAR *szOle;

#endif
    LARGE_INTEGER liBeg;

    /* initial default receive folder settings */
    ULONG cInitRFNs = 1;        /* number of default nodes */

#pragma pack(1)
    struct RFN
    {
        ULONG cbNode;
        ULONG cbClass;
        TCHAR szClass;
        ULONG cbFolder;
        TCHAR szFolderPath;
    } DefaultNode =
    {
        (2 * sizeof(ULONG)) + (2 * sizeof(TCHAR)),
        sizeof(TCHAR),
        '\0',
        sizeof(TCHAR),
        '\0'
    };
#pragma pack()

    LISet32(liBeg, 0);  /* This is an OLE initializer macro */

    AssertSz(szStoreRoot, "Bad szStoreRoot");
    AssertSz(szFile, "Bad szFile");
    AssertSz(pprfs, "Bad pprfs");

    hr = HrAppendPath(szStoreRoot, szFile, &szFullPath);
    if (hr != hrSuccess)
        goto exit;

    sc = ScAllocZ(sizeof(RFS), &prfs);
    if (sc != S_OK)
    {
        hr = ResultFromScode(sc);
        goto exit;
    }

    prfs->szFile = szFullPath;

#ifdef _WIN32
    cbOle = 1 + lstrlen(szFullPath);
    Assert(cbOle < MAX_PATH);
    MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szFullPath, cbOle, szOle, cbOle);
#else
    szOle = szFullPath;
#endif

    if (ulFlags & RFS_CREATE)
    {
        hrStg = StgCreateDocfile(szOle, grfStorageCreate, 0, &lpstg);

        if (hrStg != hrSuccess)
            goto stg_err;

#ifdef _WIN32
        cbOle = 1 + lstrlen(szRFSStreamName);
        Assert(cbOle < MAX_PATH);
        MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szRFSStreamName, cbOle,
                szOle, cbOle);
#else
        szOle = szRFSStreamName;
#endif
        hrStg = lpstg->lpVtbl->CreateStream(lpstg, szOle, grfStreamCreate,
                0, 0, &lpstream);
        if (hrStg != hrSuccess)
            goto stg_err;

        /* Initialize the newly created stream */
        hrStg = lpstream->lpVtbl->Seek(lpstream, liBeg, STREAM_SEEK_SET, NULL);
        if (hrStg != hrSuccess)
            goto stg_err;

        /* add the default RFS setting of the root (path = '\0') */
        hrStg = lpstream->lpVtbl->Write(lpstream, (LPVOID) &cInitRFNs,
                sizeof cInitRFNs, NULL);
        if (hrStg != hrSuccess)
            goto stg_err;

        hrStg = lpstream->lpVtbl->Write(lpstream, (LPVOID) &DefaultNode,
                DefaultNode.cbNode + sizeof(ULONG), NULL);
        if (hrStg != hrSuccess)
            goto stg_err;

        /* Commit docfile changes.  If we don't do this now, the file on  */
        /* disk will NOT be a docfile (i.e. OLE2 will not recognize it as */
        /* a docfile) if opened again with no other changes made to it.   */

        hrStg = lpstg->lpVtbl->Commit(lpstg, 0);
        if (hrStg != hrSuccess)
            goto stg_err;
    }
    else        /* Open an existing stream */
    {
        hr = OpenRFSStream(prfs, FALSE, &lpstream, &lpstg);
        if (hr != hrSuccess)
            goto exit;

        hrStg = lpstream->lpVtbl->Seek(lpstream, liBeg, STREAM_SEEK_SET, NULL);
        if (hrStg != hrSuccess)
            goto stg_err;

        hrStg = lpstream->lpVtbl->Read(lpstream, (LPVOID) &cRFN,
                sizeof cRFN, NULL);

        /* fall through to error handler */
    }

stg_err:
    if (hrStg != hrSuccess)
        hr = ResultFromScode(MapStorageSCode(GetScode(hrStg)));

exit:
    if (lpstream)
    {
        CloseRFSStream(lpstream, lpstg);
        lpstg = NULL;
    }

    if (hr != hrSuccess)
    {
        FreeNull(szFullPath);
        FreeNull(prfs);
        UlRelease(lpstg);
    }
    else
        *pprfs = prfs;

    DebugTraceResult(OpenRFS, hr);
    return hr;
}

/*
 *  GetRFN
 *
 *  Purpose:
 *      Returns an RFN containing the receive folder setting
 *      for the message class that is passed in as a parameter.  If
 *      there is not a receive folder setting for this particular
 *      message class, the "best match" is returned, with best
 *      match being defined in GetReceiveFolder (see msgstobj.c).
 *      the way we measure this best match is to have a match index
 *      which is incremented every time a section of the message
 *      class is matched.  These values begin at 2 because 1 is
 *      reserved for the default message class.  For example, the
 *      message class "IPM.Note.Phone" matches against the
 *      following receive folder settings in the following way:
 *
 *          "" (default)        1
 *          "IPM"               2
 *          "IPM.Note"          3
 *          "IPM.Note.Phone"    4
 *          "IPC"               0
 *
 *  Arguments:
 *      prfs            Pointer to the RFS context.
 *      szClassName     Name of the message class for which to
 *                      search for a receive folder setting.
 *      pprfn           Address of location in which to return a
 *                      pointer to an RFN structure containing
 *                      the message class and folder name of the
 *                      "best match" receive folder setting.
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      Various.
 *
 *  Notes:
 *      Use FreeRFN() to release the memory of the returned
 *      RFN structure in *pprfn.
 */
HRESULT GetRFN(PRFS prfs, LPTSTR szClassName, PRFN *pprfn)
{
    HRESULT hr = hrSuccess;
    HRESULT hrStg = hrSuccess;
    SCODE sc = S_OK;
    LPSTORAGE lpstg = NULL;
    LPSTREAM lpstream = NULL;
    PRFN prfn = NULL;
    ULONG ibNextNode = 0L;
    ULONG ibMatchNode = 0L;
    ULONG cbNode = 0L;
    ULONG cbClass = 0L;
    ULONG cRFN = 0L;
    UINT uiMatchLvl = 0;
    UINT ui = 0;
    TCHAR rgch[1024];
    LARGE_INTEGER li;
    ULONG cbCls = 0L;
    ULONG cbName = 0L;

    AssertSz(prfs, "Bad prfs");
    AssertSz(szClassName, "Bad szClassName");
    AssertSz(pprfn, "Bad pprfn");

    hr = OpenRFSStream(prfs, FALSE, &lpstream, &lpstg);
    if (hr != hrSuccess)
        goto exit;

    /* Read the count of RFS nodes from the stream. */

    LISet32(li, 0);     /* This is an OLE initializer macro */
    hrStg = lpstream->lpVtbl->Seek(lpstream, li, STREAM_SEEK_SET, NULL);
    if (hrStg != hrSuccess)
        goto stg_err;

    hrStg = lpstream->lpVtbl->Read(lpstream, (LPVOID) &cRFN,
            sizeof cRFN, NULL);
    if (hrStg != hrSuccess)
        goto stg_err;

    /* Loop over nodes, looking for the best message class match */

    for (ui = 0, ibNextNode = sizeof cRFN; ui < cRFN; ui++)
    {
        /* Set seek pointer to beginning of this node */

        LISet32(li, ibNextNode);
        hrStg = lpstream->lpVtbl->Seek(lpstream, li, STREAM_SEEK_SET, NULL);
        if (hrStg != hrSuccess)
            goto stg_err;

        /* Need to have an absolute index to the NEXT node. */
        /* Remember:  cbNode is not self-inclusive, so the  */
        /* next node is (cbNode + sizeof cbNode) from the   */
        /* current node.                                    */

        hrStg = lpstream->lpVtbl->Read(lpstream, (LPVOID) &cbNode,
                sizeof cbNode, NULL);
        if (hrStg != hrSuccess)
            goto stg_err;

        ibNextNode += cbNode + sizeof cbNode;

        /* Get and compare message class */

        hrStg = lpstream->lpVtbl->Read(lpstream, (LPVOID) &cbClass,
                sizeof cbClass, NULL);
        if (hrStg != hrSuccess)
            goto stg_err;

        AssertSz(sizeof rgch >= cbClass, "Message class too big!");

        if (cbClass > 0L)       /* If it's not a free node */
        {
            UINT uiMatchCur = 0;

            hrStg = lpstream->lpVtbl->Read(lpstream, (LPVOID) rgch, 
                    cbClass, NULL);
            if (hrStg != hrSuccess)
                goto stg_err;

            if (rgch[0] == '\0')
            {
                uiMatchCur = 1;
            }
            else
                /* count the matching message class sections */
            {
                TCHAR *pch1 = rgch;
                TCHAR *pch1Ahead = NULL;
                TCHAR *pch2 = szClassName;
                TCHAR *pch2Ahead = NULL;

                /* if matching against a class that is less refined than */
                /* what we are searching for return 0 */
                if (lstrlen(szClassName) >= lstrlen(rgch))
                {
                    while (*pch1 && *pch2)
                    {
                        for (pch1Ahead = pch1 + 1; *pch1Ahead &&
                            *pch1Ahead != '.'; pch1Ahead++)
                            ;
                        for (pch2Ahead = pch2 + 1; *pch2Ahead &&
                            *pch2Ahead != '.'; pch2Ahead++)
                            ;
                        if (pch1Ahead - pch1 == pch2Ahead - pch2 &&
                            !memcmp(pch1, pch2, pch1Ahead - pch1))
                        {
                            uiMatchCur++;
                            pch1 = pch1Ahead;
                            pch2 = pch2Ahead;
                        }
                        else
                            break;
                    }
                }
                /* We want to match a "real" setting higher than the */
                /* default, so we increment a real match to be > 1.  */

                if (uiMatchCur > 0)
                {
                    uiMatchCur++;
                }
            }

            if (uiMatchCur > uiMatchLvl)
            {
                /* Here we set ibMatchNode to be the absolute index of */
                /* the cbClass member of the node (NOT the cbNode      */
                /* member.  When we seek back to this position, we can */
                /* begin reading the cbClass immediately (see below).  */

                ibMatchNode = ibNextNode - cbNode;
                uiMatchLvl = uiMatchCur;
            }
        }
    }

    if (uiMatchLvl == 0)
    {
        hr = ResultFromScode(MAPI_E_NOT_FOUND);
        goto exit;
    }

    /* Set the return variable w/best match */

    sc = ScAllocZ(sizeof(RFN), (PPV) &prfn);
    if (sc != S_OK)
        goto sc_err;

    /* Goto best match node, but seek pointer will be past cbNode */

    LISet32(li, ibMatchNode);
    hrStg = lpstream->lpVtbl->Seek(lpstream, li, STREAM_SEEK_SET, NULL);
    if (hrStg != hrSuccess)
        goto stg_err;

    /* Read in class name */

    hrStg = lpstream->lpVtbl->Read(lpstream, (LPVOID) &cbCls,
            sizeof cbCls, NULL);
    if (hrStg != hrSuccess)
        goto stg_err;

    sc = ScAlloc(cbCls, (PPV) &prfn->szClass);
    if (sc != S_OK)
        goto sc_err;

    hrStg = lpstream->lpVtbl->Read(lpstream,
            (LPVOID) prfn->szClass, cbCls, NULL);
    if (hrStg != hrSuccess)
        goto stg_err;

    /* Read in folder name */

    hrStg = lpstream->lpVtbl->Read(lpstream, (LPVOID) &cbName,
            sizeof cbName, NULL);
    if (hrStg != hrSuccess)
        goto stg_err;

    sc = ScAlloc(cbName, (PPV) &prfn->szName);
    if (sc != S_OK)
        goto sc_err;

    hrStg = lpstream->lpVtbl->Read(lpstream,
            (LPVOID) prfn->szName, cbName, NULL);
    if (hrStg != hrSuccess)
        goto stg_err;

sc_err:
    if (sc != S_OK)
    {
        Assert(hr == hrSuccess);
        Assert(hrStg == hrSuccess);
        hr = ResultFromScode(sc);
    }

stg_err:
    if (hrStg != hrSuccess)
    {
        Assert(sc == S_OK);
        Assert(hr == hrSuccess);
        hr = ResultFromScode(MapStorageSCode(GetScode(hrStg)));
    }

exit:
    if (lpstream)
        CloseRFSStream(lpstream, lpstg);

    if (hr != hrSuccess)
        FreeRFN(prfn);
    else
        *pprfn = prfn;

    DebugTraceResult(GetRFN, hr);
    return hr;
}

/*
 -  FreeRFN
 -
 *  Release the memory of an RFN allocated and returned
 *  by the GetRFN() procedure.
 */
void FreeRFN(PRFN prfn)
{
    if (prfn)
    {
        (void)FreeNull((LPVOID) prfn->szClass);
        (void)FreeNull((LPVOID) prfn->szName);
        (void)FreeNull((LPVOID) prfn);
    }
}

/*
 *  DeleteRFN
 *
 *  Purpose:
 *      Delete the receive folder setting associated with a
 *      particular message class.  We do this by "zeroing out" the
 *      node on disk, rather than actually removing it and
 *      compacting the stream.  We can easily zero out the node
 *      once we've found the right one by setting the length of the
 *      message class string contained in it to be zero (an invalid
 *      value).
 *
 *  Arguments:
 *      prfs            Pointer to the RFS context to use.
 *      szClassName     Buffer containing the name of the message
 *                      class for which to remove the receive
 *                      folder setting.  We do a linear search
 *                      through the stream to find the node on disk
 *                      with a matching message class.
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      Various.
 */
HRESULT DeleteRFN(PRFS prfs, LPTSTR szClassName)
{
    HRESULT hr = hrSuccess;
    HRESULT hrStg = hrSuccess;
    LPSTORAGE lpstg = NULL;
    IStream *lpstream = NULL;
    ULONG ibNextNode = 0L;
    ULONG cbNode = 0L;
    ULONG cbClass = 0L;
    ULONG cRFN = 0L;
    UINT ui = 0;
    TCHAR rgch[1024];
    LARGE_INTEGER li;

    AssertSz(prfs, "Bad prfs");
    AssertSz(szClassName, "Bad szClassName");

    hr = OpenRFSStream(prfs, TRUE, &lpstream, &lpstg);
    if (hr != hrSuccess)
        goto exit;

    /* Read the count of RFS nodes from the stream. */

    LISet32(li, 0);     /* This is an OLE initializer macro */
    hrStg = lpstream->lpVtbl->Seek(lpstream, li, STREAM_SEEK_SET, NULL);
    if (hrStg != hrSuccess)
        goto stg_err;

    hrStg = lpstream->lpVtbl->Read(lpstream, (LPVOID) &cRFN,
            sizeof cRFN, NULL);
    if (hrStg != hrSuccess)
        goto stg_err;

    /* Loop over nodes, looking for a message class match */

    for (ui = 0, ibNextNode = sizeof cRFN; ui < cRFN; ui++)
    {
        /* Set seek pointer to beginning of first node */

        LISet32(li, ibNextNode);
        hrStg = lpstream->lpVtbl->Seek(lpstream, li, STREAM_SEEK_SET, NULL);
        if (hrStg != hrSuccess)
            goto stg_err;

        /* Need to have an absolute index to the NEXT node. */
        /* Remember:  cbNode is not self-inclusive, so the  */
        /* next node is (cbNode + sizeof cbNode) from the   */
        /* current node.                                    */

        hrStg = lpstream->lpVtbl->Read(lpstream, (LPVOID) &cbNode,
                sizeof cbNode, NULL);
        if (hrStg != hrSuccess)
            goto stg_err;

        ibNextNode += cbNode + sizeof cbNode;

        /* Get and compare message class */

        hrStg = lpstream->lpVtbl->Read(lpstream, (LPVOID) &cbClass,
                sizeof cbClass, NULL);
        if (hrStg != hrSuccess)
            goto stg_err;

        AssertSz(sizeof rgch >= cbClass * sizeof(TCHAR),
            "Message class too big!");

        if (cbClass > 0L)       /* If it's not a free node */
        {
            hrStg = lpstream->lpVtbl->Read(lpstream, (LPVOID) rgch,
                    cbClass, NULL);
            if (hrStg != hrSuccess)
                goto stg_err;

            if (cbClass == Cbtszsize(szClassName)
                && !memcmp(szClassName, rgch, (UINT) cbClass))
            {
                LONG ibClass = 0L;

                /* Seek back to cbClass */

                ibClass -= (LONG) (cbClass + sizeof cbClass);
                LISet32(li, ibClass);
                hrStg = lpstream->lpVtbl->Seek(lpstream, li,
                        STREAM_SEEK_CUR, NULL);
                if (hrStg != hrSuccess)
                    goto stg_err;

                /* Zero out the node */

                cbClass = 0L;
                hrStg = lpstream->lpVtbl->Write(lpstream,
                        (LPVOID) &cbClass, sizeof cbClass, NULL);
                if (hrStg != hrSuccess)
                    goto stg_err;

                /* Commit the change */

                hrStg = lpstg->lpVtbl->Commit(lpstg, 0);
                if (hrStg != hrSuccess)
                    goto stg_err;

                break;
            }
        }
    }

stg_err:
    if (hrStg)
        hr = ResultFromScode(MapStorageSCode(GetScode(hrStg)));

exit:
    if (lpstream)
        CloseRFSStream(lpstream, lpstg);

    DebugTraceResult(DeleteRFN, hr);
    return hr;
}

/*
 *  AddRFN
 *
 *  Purpose:
 *      Adds a node (on disk) to the stream that holds receive
 *      folder settings for a message store.  Does this by creating
 *      a new node at the current End-Of-Stream (at the end of all
 *      other nodes).
 *
 *  Arguments:
 *      prfs        Pointer to the receive folder storage context.
 *      prfn    Pointer to the new node to add.
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      Various.
 */
HRESULT AddRFN(PRFS prfs, PRFN prfn)
{
    HRESULT hr = hrSuccess;
    HRESULT hrStg = hrSuccess;
    LPSTORAGE lpstg = NULL;
    IStream *lpstream = NULL;
    UINT ui = 0;
    ULONG cb = 0L;
    ULONG cbNode = 0L;
    ULONG cbClass = 0L;
    ULONG cbName = 0L;
    ULONG cRFN = 0L;
    LARGE_INTEGER liEOS;

    AssertSz(prfs, "Bad prfs");
    AssertSz(prfn, "Bad prfn");
    AssertSz(prfn->szClass, "Bad prfn->szClass");
    AssertSz(prfn->szName, "Bad prfn->szName");

    hr = OpenRFSStream(prfs, TRUE, &lpstream, &lpstg);
    if (hr != hrSuccess)
        goto exit;

    /* Find the end of the stream.  Strictly speaking, we can't just seek */
    /* the current End-Of-Stream (what the IStream thinks is it's current */
    /* EOS), because we really want to be at the end of the last node,    */
    /* and there may have been stuff written after (from a failed write). */
    /* First, read the count of RFS nodes from the stream. */

    LISet32(liEOS, 0);      /* This is an OLE initializer macro */
    hrStg = lpstream->lpVtbl->Seek(lpstream, liEOS, STREAM_SEEK_SET, NULL);
    if (hrStg != hrSuccess)
        goto stg_err;

    hrStg = lpstream->lpVtbl->Read(lpstream, (LPVOID) &cRFN,
            sizeof cRFN, NULL);
    if (hrStg != hrSuccess)
        goto stg_err;

    for (ui = 0; ui < cRFN; ui++)
    {
        hrStg = lpstream->lpVtbl->Read(lpstream, (LPVOID) &cb,
                sizeof cb, NULL);
        if (hrStg != hrSuccess)
            goto stg_err;

        LISet32(liEOS, (LONG) cb);

        hrStg = lpstream->lpVtbl->Seek(lpstream, liEOS, STREAM_SEEK_CUR, NULL);
        if (hrStg != hrSuccess)
            goto stg_err;
    }

    /* Write out the node */

    /* Size of node: length of 2 strings + 2 NULL characters + 2 times */
    /* the size of the space needed to hold the string lengths.        */

    cbClass = Cbtszsize(prfn->szClass);
    cbName = Cbtszsize(prfn->szName);
    cbNode = 2 * sizeof(ULONG) + cbClass + cbName;

    hrStg = lpstream->lpVtbl->Write(lpstream, (LPVOID) &cbNode,
            sizeof cbNode, NULL);
    if (hrStg != hrSuccess)
        goto stg_err;

    hrStg = lpstream->lpVtbl->Write(lpstream, (LPVOID) &cbClass,
            sizeof cbClass, NULL);
    if (hrStg != hrSuccess)
        goto stg_err;

    hrStg = lpstream->lpVtbl->Write(lpstream, (LPVOID) prfn->szClass,
            cbClass, NULL);
    if (hrStg != hrSuccess)
        goto stg_err;

    hrStg = lpstream->lpVtbl->Write(lpstream, (LPVOID) &cbName,
            sizeof cbName, NULL);
    if (hrStg != hrSuccess)
        goto stg_err;

    hrStg = lpstream->lpVtbl->Write(lpstream, (LPVOID) prfn->szName,
            cbName, NULL);
    if (hrStg != hrSuccess)
        goto stg_err;

    /* Keep cRFN, the in-memory and on-disk */
    /* copies, in sync with each other.     */

    LISet32(liEOS, 0L);
    hrStg = lpstream->lpVtbl->Seek(lpstream, liEOS, STREAM_SEEK_SET, NULL);
    if (hrStg != hrSuccess)
        goto stg_err;

    cRFN++;
    hrStg = lpstream->lpVtbl->Write(lpstream, (LPVOID) &cRFN,
            sizeof cRFN, NULL);
    if (hrStg != hrSuccess)
    {
        cRFN--;
        goto stg_err;
    }

    /* Commit the change */

    hrStg = lpstg->lpVtbl->Commit(lpstg, 0);
    /* if ( hrStg ), fall through to stg_err */

stg_err:
    if (hrStg)
        hr = ResultFromScode(MapStorageSCode(GetScode(hrStg)));

exit:
    if (lpstream)
        CloseRFSStream(lpstream, lpstg);

    DebugTraceResult(AddRFN, hr);
    return hr;
}

/*
 *  CloseRFS
 *
 *  Purpose:
 *      Frees and invalidates an open context for accessing receive
 *      folder settings.
 *
 *  Arguments:
 *      prfs        Pointer to the object to close.
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      Various.
 */
HRESULT CloseRFS(PRFS prfs)
{
    HRESULT hr = hrSuccess;

    AssertSz(prfs, "Bad prfs");

    FreeNull(prfs->szFile);
    FreeNull(prfs);

    DebugTraceResult(CloseRFS, hr);
    return hr;
}

/*
 *  Internal functions
 */

/*
 *  OpenRFSStream
 *
 *  Purpose:
 *      Open the stream within a docfile that contains receive
 *      folder settings.
 *
 *  Arguments:
 *      prfs        Receive folder settings context.
 *      fModify     TRUE indicates the caller wants write access.
 *      lppstream   Address in which to return a pointer to the
 *                  newly opened stream.
 *
 *  Returns:
 *      HRESULT
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      Various storage errors.
 */
static HRESULT OpenRFSStream(PRFS prfs, BOOL fModify, IStream **lppstream,
    LPSTORAGE *lppstg)
{
    HRESULT hr = hrSuccess;
    HRESULT hrStg = hrSuccess;
    DWORD grfMode;

#ifdef _WIN32
    OLE_CHAR szOle[MAX_PATH];
    int cbOle = 0L;
#else
    OLE_CHAR *szOle;
#endif

    LPSTORAGE lpstg = NULL;
    IStream *lpstream = NULL;

    AssertSz(prfs, "Bad prfs");
    AssertSz(lppstream, "Bad lppstream");

#ifdef _WIN32
    cbOle = 1 + lstrlen(prfs->szFile);
    Assert(cbOle < MAX_PATH);
    MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, prfs->szFile, cbOle, szOle, cbOle);
#else
    szOle = prfs->szFile;
#endif

    if (fModify)
        grfMode = STGM_SHARE_EXCLUSIVE | STGM_READWRITE;
    else
        grfMode = STGM_SHARE_EXCLUSIVE | STGM_READ;

    hrStg = StgOpenStorage(szOle, NULL, grfMode | STGM_TRANSACTED, NULL,
            0, &lpstg);
    if (hrStg != hrSuccess)
        goto stg_err;

#ifdef _WIN32
    cbOle = 1 + lstrlen(szRFSStreamName);
    Assert(cbOle < MAX_PATH);
    MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, szRFSStreamName, cbOle, szOle, cbOle);
#else
    szOle = szRFSStreamName;
#endif

    hrStg = lpstg->lpVtbl->OpenStream(lpstg, szOle, NULL, grfMode, 0, &lpstream);
    if (hrStg != hrSuccess)
        goto stg_err;

    /* WARNING:  If any code is added between here and the error handler */
    /* that can fail, a check in the error handler must be added to free */
    /* the open stream in the event of an error.                         */

    *lppstream = lpstream;
    *lppstg = lpstg;

stg_err:
    if (hrStg != hrSuccess)
        hr = ResultFromScode(MapStorageSCode(GetScode(hrStg)));

    if (hr != hrSuccess)
        UlRelease(lpstg);

    DebugTraceResult(OpenRFSStream, hr);
    return hr;
}

/*
 *  CloseRFSStream
 *
 *  Purpose:
 *      Close the stream within a docfile that holds receive folder
 *      settings.
 *
 *  Arguments:
 *      lpstream    Pointer to the stream.
 *      lpstg       Pointer to the storage instance in which this
 *                  stream resides.
 *
 *  Returns:
 *      void
 *
 *  Side effects:
 *      None.
 *
 *  Errors:
 *      None.
 */
static void CloseRFSStream(IStream *lpstream, LPSTORAGE lpstg)
{
    AssertSz(lpstream, "Bad lpstream");
    AssertSz(lpstg, "Bad lpstg");

    NFSideAssertSz(UlRelease(lpstream) == 0L, "lpstream not released");
    NFSideAssertSz(UlRelease(lpstg) == 0L, "lpstg not released");

    return;
}
