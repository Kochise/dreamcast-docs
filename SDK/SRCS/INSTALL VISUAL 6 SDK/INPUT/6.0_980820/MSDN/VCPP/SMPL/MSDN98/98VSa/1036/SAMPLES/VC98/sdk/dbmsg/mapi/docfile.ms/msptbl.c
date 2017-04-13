/*
 *  M S P T B L . C
 *
 *  Functions to manage a hierarchy and contents tables cached on disk.
 *
 *  Copyright 1992-1995 Microsoft Corporation.  All Rights Reserved.
 */

#include "msp.h"

static SCODE ScCreateFile(LPTSTR szFile, ULONG ulAccess, ULONG ulShare,
    ULONG ulCreate, HANDLE * lphFile);
static HRESULT HrOpenTblFileRetry(LPTSTR szFile, ULONG ulAccess, ULONG ulShare,
    ULONG ulCreate, HANDLE * lphFile);
static HRESULT HrNewCounts(PIFLD pifld, LPTABLEDATA lptbl);
static HRESULT HrReadBytes(HANDLE hFile, LPVOID lpBuffer, ULONG cbToRead,
    BOOL * pfEOF);
static HRESULT HrWriteBytes(HANDLE hFile, LPVOID lpBuffer, ULONG cbToWrite);
static HRESULT HrWriteRow(HANDLE hFile, LPSRow prw);
static VOID TranslateFileError(BOOL fSuccess, ULONG cbIn, ULONG cbOut,
    BOOL * pfEOF, SCODE * pscFile);
static HRESULT HrGetTime(LPSRow prw, FILETIME * pfiletime);
static HRESULT HrRemoveBadTableRows(LPTABLEDATA lptbl, PIFLD pifldParent,
    PIMS pims, BOOL * pfTableChanged);
static HRESULT HrAddMissingTableRows(LPTABLEDATA lptbl, PIFLD pifld,
    LPSTR szTemplate, LPSPropTagArray ptaga, BOOL * pfTableChanged);



/* format of a row of table data on disk (DRW) */
typedef struct _DRW
{
    ULONG   cbRow;
    SRow    rw;
    BYTE    ab[MAPI_DIM];
} DRW, *PDRW;

#define CbNewDRW(_cb)       (offsetof(DRW,ab) + (_cb))
#define CbDRW(_pdrw)        (offsetof(DRW,ab) + (UINT)((_pdrw)->cbRow))


/****************************************************************************
 * ScCreateFile
 *
 * Purpose      Open or create a file
 *
 * Parameters
 *  szFile          name of the file
 *  ulAccess        read/write access desired see CreateFile
 *  ulShare         sharing desired see CreateFile
 *  ulCreate        creation disposition see CreateFile
 *  lphFile         returns handle of open file, undefined if call fails
 *
 */
static SCODE 
ScCreateFile(LPTSTR szFile, ULONG ulAccess, ULONG ulShare,
    ULONG ulCreate, HANDLE * lphFile)
{
    HANDLE hFile;
    SCODE sc = S_OK;

    hFile = CreateFile(szFile, ulAccess, ulShare, NULL,
        ulCreate, FILE_FLAG_SEQUENTIAL_SCAN, NULL);

    if (hFile == INVALID_HANDLE_VALUE)
    {
        switch (GetLastError())
        {
        case ERROR_FILE_NOT_FOUND:
            sc = MAPI_E_NOT_FOUND;
            break;

        case ERROR_SHARING_VIOLATION:
        case ERROR_LOCK_VIOLATION:
            sc = MAPI_E_BUSY;
            break;

        default:
            sc = MAPI_E_NO_ACCESS;
            break;
        }
    }
    else
    {
        AssertSz(!IsBadWritePtr(lphFile, sizeof(HANDLE)), "Bad parameter"
            " (lphFile) given to ScCreateFile");

        *lphFile = hFile;
    }

    DebugTraceSc(ScCreateFile, sc);
    return sc;
}

/*
 * HrOpenTblFileRetry
 *
 * Purpose      Open or create a file, but retry if it is busy
 *
 * Parameters
 *  szFile          name of the file
 *  ulAccess        read/write access desired see CreateFile
 *  ulShare         sharing desired see CreateFile
 *  ulCreate        creation disposition see CreateFile
 *  lphFile         returns handle of open file, undefined if call fails
 *
 */
static HRESULT HrOpenTblFileRetry(LPTSTR szFile, ULONG ulAccess, ULONG ulShare,
    ULONG ulCreate, HANDLE * lphFile)
{
    UINT iRetry;
    SCODE sc = S_OK;
    HANDLE hFile;

    iRetry = 0;
    while (TRUE)
    {
        sc = ScCreateFile(szFile, ulAccess, ulShare, ulCreate, &hFile);

        if (sc != MAPI_E_BUSY || ++iRetry >= NUM_RETRIES)
            break;

        Sleep(500);
    }

    if (sc == S_OK)
        *lphFile = hFile;

    #ifdef DEBUG
    if (iRetry >= NUM_RETRIES)
        TraceSz("HrOpenTblFileRetry: Failing open. Too many tries.");
    #endif

    DebugTraceSc(HrOpenTblFileRetry, sc);
    return ResultFromScode(sc);
}

/*
 * HrWriteCounts
 *
 *  Purpose
 *      This function writes the counts of messages and unread messages
 *      in a folder to the folder's property file. After the code 
 *      validates what the counts should be, this function writes the
 *      counts so that they are correct.
 *
 *  Parameters
 *      pifld: A pointer to the folder object to update.
 *      ulMsgs: The number of messages in the folder.
 *      ulUnread: The number of unread messages in the folder.
 *
 */
static HRESULT HrWriteCounts(PIFLD pifld, ULONG ulMsgs, ULONG ulUnread)
{
    HRESULT hr;
    LPMESSAGE lpmsg = NULL;
    PLMR plmr = &pifld->pims->lmr;
    ULONG ulMsgsCopy = ulMsgs;      /* workaround - MS C code-gen bug */

    hr = HrOpenPropertyMessageRetry(pifld->peid, pifld->pims, TRUE, &lpmsg);
    if (hr != hrSuccess)
        goto exit;

    hr = HrSetOneROProp(lpmsg, plmr, PR_CONTENT_COUNT, &ulMsgsCopy);
    if (hr != hrSuccess)
        goto exit;

    hr = HrSetOneROProp(lpmsg, plmr, PR_CONTENT_UNREAD, &ulUnread);
    if (hr != hrSuccess)
        goto exit;

    hr = lpmsg->lpVtbl->SaveChanges(lpmsg, FORCE_SAVE);

exit:
    UlRelease(lpmsg);

    DebugTraceResult(HrWriteCounts, hr);
    return hr;
}

/*
 * HrNewCounts
 *
 * Purpose  Make the contents count and unread count of the folder in pifld
 *          agree with the data in the contents table lptbl
 *
 * Parameters
 *      pifld       the folder
 *      lptbl       the table
 */
static HRESULT HrNewCounts(PIFLD pifld, LPTABLEDATA lptbl)
{
    HRESULT hr = hrSuccess;
    ULONG cMessages = 0;
    ULONG cUnread = 0;
    LPSRow lpsRow = NULL;
    ULONG ulRow = 0;
    PLMR plmr = &pifld->pims->lmr;
    LPMESSAGE lpmsg = NULL;

    /* check each row in the table to see if the message has been read */

    while (TRUE)
    {
        LPSPropValue pval;
        LPSPropValue pvalMax;

        hr = lptbl->lpVtbl->HrEnumRow(lptbl, ulRow++, &lpsRow);
        if (hr != hrSuccess)
            goto exit;

        if (lpsRow == NULL)
            break;

        cMessages++;

        pval = lpsRow->lpProps;
        pvalMax = pval + lpsRow->cValues;

        /* check PR_MESSAGE_FLAGS to see if this message is unread */
        while (pval < pvalMax)
        {
            if (pval->ulPropTag == PR_MESSAGE_FLAGS)
            {
                if (!(pval->Value.l & MSGFLAG_READ))
                    cUnread++;
                break;
            }
            pval++;
        }

        LMFree(&pifld->pims->lmr, lpsRow);
        lpsRow = NULL;
    }

    hr = HrWriteCounts(pifld, cMessages, cUnread);

exit:
    LMFree(&pifld->pims->lmr, lpsRow);

    DebugTraceResult(HrNewCounts, hr);
    return hr;
}

/**********************************************************************
 * HrGetTableName
 *
 * Purpose
 *      Given an open object and the kind of table
 *      returns the full path name of the file that caches that table's data.
 *      Must be freed with FreeNull.
 *
 * Parameters
 *  pobj        object whose table is needed
 *  szEIDPath   EID path (may be NULL)
 *  szFileName  Name of the file that holds the table.
 *  lppszTable  pointer to storage for the path name of the table file
 */
HRESULT HrGetTableName(POBJ pobj, LPSTR szEIDPath, LPSTR szFileName,
    LPSTR *pszTable)
{
    LPTSTR szDir = NULL;        /* Full Path name of directory containing table */
    HRESULT hr = hrSuccess;
    PIMS pims = pobj->pims;

    Assert(!IsBadWritePtr(pszTable, sizeof(LPTSTR)));

    hr = HrFullPathName(pims->szStorePath, szEIDPath, NULL, &szDir);
    if (hr != hrSuccess)
        goto exit;

    /* get memory to hold the filename that contains the table. */
    /* Add 1 char for the backslash before the filename. */

    hr = HrAlloc(CCH_NAME * sizeof(TCHAR)
        + ((lstrlen(szDir) + 1) * sizeof(TCHAR)), (PPV) pszTable);
    if (hr != hrSuccess)
        goto exit;

    lstrcpy(*pszTable, szDir);
    lstrcat(*pszTable, "\\");
    lstrcat(*pszTable, szFileName);

exit:
    FreeNull(szDir);
    DebugTraceResult(HrGetTableName, hr);
    return hr;
}

/**********************************************************************
 * HrReadBytes
 *
 * Read a number of bytes from a file into a buffer, checking for errors and
 * end-of-file.
 *
 * Parameters:
 *
 * hFile:       File handle to read from.
 * lpBuffer:    Pointer to a buffer to read into. The buffer should be big
 *              enough to hold the incoming data.
 * cbToRead:    The number of bytes to read. Should be <= UINT_MAX.
 * pfEOF:       A pointer to the location to return a boolean specifying
 *              whether the read encountered an end-of-file. If it did, the
 *              buffer will return with no data in it. This pointer may be NULL,
 *              in which case end-of-file will be treated as an error.
 *
 * Returns:
 *  HRESULT     (either a file read error, or MAPI_E_CALL_FAILED when either
 *              EOF is encountered and pfEOF is NULL, or when the number of
 *              bytes read is less than the number requested).
 */
static HRESULT HrReadBytes(HANDLE hFile, LPVOID lpBuffer, ULONG cbToRead,
    BOOL *pfEOF)
{
    SCODE sc = S_OK;
    ULONG cbRead = 0;
    BOOL fSuccess;

    AssertSz(cbToRead <= UINT_MAX && !IsBadWritePtr(lpBuffer, (UINT) cbToRead),
        "Bad buffer");

    fSuccess = ReadFile(hFile, lpBuffer, cbToRead, &cbRead, NULL);

    TranslateFileError(fSuccess, cbToRead, cbRead, pfEOF, &sc);

    DebugTraceSc(HrReadBytes, sc);
    return ResultFromScode(sc);
}

/**********************************************************************
 * HrWriteBytes
 *
 * Write a number of bytes from a buffer into a file, checking for errors.
 *
 * Parameters:
 *
 * hFile:       File handle to write into.
 * lpBuffer:    Pointer to a buffer containing the data to write.
 * cbToRead:    The number of bytes to write. Should be <= UINT_MAX.
 *
 * Returns:
 *  HRESULT     (either a file write error, or MAPI_E_CALL_FAILED when the
 *              number of bytes written is less than the number requested).
 */
static HRESULT HrWriteBytes(HANDLE hFile, LPVOID lpBuffer, ULONG cbToWrite)
{
    SCODE sc = S_OK;
    ULONG cbWritten = 0;
    BOOL fSuccess;

    AssertSz(cbToWrite <= UINT_MAX && !IsBadReadPtr(lpBuffer, (UINT) cbToWrite),
        "Bad buffer");

    fSuccess = WriteFile(hFile, lpBuffer, cbToWrite, &cbWritten, NULL);

    TranslateFileError(fSuccess, cbToWrite, cbWritten, NULL, &sc);

    DebugTraceSc(HrWriteBytes, sc);
    return ResultFromScode(sc);
}

/**********************************************************************
 * TranslateFileError
 *
 * Checks for errors from a windows ReadFile or WriteFile call, translating
 * windows error codes to MAPI errors, and, if requested, checking for end-of-
 * file. Also checks to make sure the number of bytes read or written equals
 * the number given as input.
 *
 * Parameters:
 *
 * fSuccess:    The return value from ReadFile or WriteFile.
 * cbIn:        The number of bytes given as input to ReadFile or WriteFile.
 * cbOut:       The number of bytes returned from ReadFile or WriteFile.
 * pfEOF:       A pointer to the location to return a BOOL specifying
 *              whether cbOut was 0 and fSuccess was TRUE. This condition
 *              indicates end-of-file when reading, and should not be treated
 *              as an error. The pointer may be NULL, in which case, this
 *              condition is treated as an error, and *psc is returned with
 *              MAPI_E_CALL_FAILED.
 * psc:         A pointer to the location to return an SCODE indicating
 *              the success or failure of the ReadFile or WriteFile.
 *
 * Returns: VOID
 */
static VOID TranslateFileError(BOOL fSuccess, ULONG cbIn, ULONG cbOut,
    BOOL *pfEOF, SCODE *pscFile)
{
    SCODE sc = S_OK;
    BOOL fEOF = FALSE;
    BOOL fCheckEOF = (pfEOF != NULL);

    if (!fSuccess)
    {
        DWORD dwError = GetLastError();

        if (dwError != 0)

            switch (dwError)
            {
            case 0:
                TraceSz("SampleMS: ScTranslateFileError found unexpected "
                    "success\n");
                break;

            case ERROR_SHARING_VIOLATION:
            case ERROR_LOCK_VIOLATION:
                sc = MAPI_E_BUSY;
                break;

            case ERROR_FILE_NOT_FOUND:
                sc = MAPI_E_NOT_FOUND;
                break;

            case ERROR_TOO_MANY_OPEN_FILES:
                sc = MAPI_E_NOT_ENOUGH_RESOURCES;
                break;

            case ERROR_ACCESS_DENIED:
            case ERROR_INVALID_ACCESS:
            case ERROR_INVALID_DRIVE:
                sc = MAPI_E_NO_ACCESS;
                break;

            default:
                sc = MAPI_E_CALL_FAILED;
                break;
            }
    }
    else if (cbOut != cbIn)
    {
        sc = MAPI_E_CALL_FAILED;

        /* If the caller wants to discriminate end-of-file from other */
        /* errors, and the file call returned zero bytes, return EOF, */
        /* and don't return an error. */

        if (fCheckEOF && cbOut == 0)
        {
            sc = S_OK;
            fEOF = TRUE;
        }
    }

    AssertSz(!IsBadWritePtr(pscFile, sizeof(SCODE)), "Bad parameter (pscFile) "
        "given to TranslateFileError");

    *pscFile = sc;

    if (pfEOF)
    {
        AssertSz(!IsBadWritePtr(pfEOF, sizeof(BOOL)), "Bad parameter (pfEOF) "
            "given to TranslateFileError");
        *pfEOF = fEOF;
    }

    return;
}

/*
 * HrWriteRow
 *
 *  Purpose
 *      Writes one row of data to the file handle given.
 *
 *  Arguments
 *      hFile: File handle to update.
 *      prw: Pointer to the row to write.
 *
 *  RETURNS: HRESULT
 */
static HRESULT HrWriteRow(HANDLE hFile, LPSRow prw)
{
    HRESULT hr = hrSuccess;
    SCODE sc;
    ULONG cb;
    PDRW pdrw = NULL;

    sc = ScCountProps((UINT) prw->cValues, prw->lpProps, &cb);
    if (sc != S_OK)
    {
        hr = ResultFromScode(sc);
        goto exit;
    }

    /* Allocate space for the disk row */
    hr = HrAlloc(CbNewDRW(cb), &pdrw);
    if (hr != hrSuccess)
        goto exit;

    /* fill in the disk row structure */

    pdrw->cbRow = cb;
    pdrw->rw.cValues = prw->cValues;

    /* The lpProps field of the row we write should be point at the */
    /* row we are writing (i.e., pdrw->ab). We will use that pointer */
    /* value when we read the data off disk to fixup the pointers via */
    /* ScRelocProps. */
    pdrw->rw.lpProps = (LPSPropValue) pdrw->ab;

    sc = ScCopyProps((UINT) prw->cValues, prw->lpProps, &(pdrw->ab), NULL);
    if (sc != S_OK)
    {
        hr = ResultFromScode(sc);
        goto exit;
    }

    /* write the row */
    hr = HrWriteBytes(hFile, pdrw, CbDRW(pdrw));
    if (hr != hrSuccess)
        goto exit;

exit:
    FreeNull(pdrw);
    
    DebugTraceResult(HrWriteRow, hr);
    return hr;
}

/*************************************************************************
 * HrWriteTableOnDisk
 *
 * Purpose
 *      write the table in lptbl to the disk image of lpvObjects table
 *      of type ulType
 *
 *  lptbl       Table to be written
 *  pobj        object whose table is to be written
 *  szEIDPath   Pathname of the EID of the folder, or NULL
 *  szFileName  Name of the file that holds this table type.
 *
 */
HRESULT HrWriteTableOnDisk(LPTABLEDATA lptbl, POBJ pobj, LPSTR szEIDPath,
    LPSTR szFileName)
{
    LPTSTR szFile = NULL;
    HANDLE hFile = INVALID_HANDLE_VALUE; /* handle to open file */
    LPSRow lpsRow = NULL;               /* next row to be written */
    ULONG ulRowNumber;          /* number of the row being written */
    HRESULT hr = hrSuccess;
    PLMR plmr = &pobj->pims->lmr;

    /* get the name of the file holding the table */
    hr = HrGetTableName(pobj, szEIDPath, szFileName, &szFile);
    if (hr != hrSuccess)
        goto exit;

    /* open the file with exclusive access */

    hr = HrOpenTblFileRetry(szFile, GENERIC_WRITE, 0L, CREATE_ALWAYS, &hFile);
    if (hr != hrSuccess)
        goto exit;

    /* write the table data to the file */
    ulRowNumber = 0;
    while (TRUE)
    {
        hr = lptbl->lpVtbl->HrEnumRow(lptbl, ulRowNumber, &lpsRow);
        if (hr != hrSuccess)
            goto exit;
        if (lpsRow == NULL)
            break;

        hr = HrWriteRow(hFile, lpsRow);
        if (hr != hrSuccess)
            goto exit;

        LMFree(plmr, lpsRow);
        lpsRow = NULL;
        ulRowNumber++;
    }

exit:
    AssertSz(GetScode(hr) != MAPI_W_ERRORS_RETURNED,
        "Unexpected warning return");

    /* Set the end of file marker, in case we shrank the file. */
    if (hr == hrSuccess && SetEndOfFile(hFile) == FALSE)
        hr = ResultFromScode(MAPI_E_DISK_ERROR);

    if (hFile != INVALID_HANDLE_VALUE)
        CloseHandle(hFile);

    /* erase the file if in error */
    if (hr != hrSuccess && szFile)
        DeleteFile(szFile);

    FreeNull(szFile);
    LMFree(plmr, lpsRow);

    DebugTraceResult(HrWriteTableOnDisk, hr);
    return hr;
}

/*************************************************************************
 * HrReadTableFromDisk
 *
 * Purpose
 *      Read a table from this disk cache into the table lptbl
 *
 *  lptbl       the table to be built
 *  pobj        object whose table is to be read
 *  szEIDPath   Pathname of the EID of the folder, or NULL
 *  cCols       Number of columns in this type of table
 *  szFileName  Name of the file that holds this table type.
 */
HRESULT HrReadTableFromDisk(LPTABLEDATA lptbl, POBJ pobj, LPSTR szEIDPath,
    ULONG cCols, LPSTR szFileName)
{
    HRESULT hr;
    PLMR    plmr;
    BOOL    fBadTableData   = FALSE;
    LPTSTR  szFile          = NULL;
    HANDLE  hFile           = INVALID_HANDLE_VALUE;
    PDRW    pdrw            = NULL;

    plmr = &pobj->pims->lmr;

    /* get the name of the file holding the table */
    hr = HrGetTableName(pobj, szEIDPath, szFileName, &szFile);
    if (hr != hrSuccess)
        goto exit;

    /* open the file */
    hr = HrOpenTblFileRetry(szFile, GENERIC_READ, FILE_SHARE_READ,
        OPEN_ALWAYS, &hFile);
    if (hr != hrSuccess)
    {
        /* If the file wasn't found, then simply leave the table empty, */
        /* and return success. */

        if (GetScode(hr) == MAPI_E_NOT_FOUND)
            hr = hrSuccess;

        goto exit;
    }

    while (TRUE)
    {
        BOOL fEOF;
        DRW drwTemp;
        ULONG cbOut;
        SCODE sc;

        /* Read the beginning of the disk row. */
        hr = HrReadBytes(hFile, &drwTemp, CbNewDRW(0), &fEOF);
        if (hr != hrSuccess)
            goto exit;

        if (fEOF)
            break;

        /* Sanity check for bad data. */
        /* Note that the number of columns in the disk version of the */
        /* table can be less than the number of columns in the in-memory */
        /* table due to properties that were missing from the message */
        /* when it was written to disk. */

        if (    drwTemp.rw.cValues > cCols
            ||  drwTemp.rw.cValues == 0
            ||  drwTemp.cbRow < drwTemp.rw.cValues * sizeof(SPropValue))
        {
            hr = ResultFromScode(MAPI_E_CORRUPT_DATA);
            fBadTableData = TRUE;
            goto exit;
        }

        hr = HrAlloc(CbNewDRW(drwTemp.cbRow), &pdrw);
        if (hr != hrSuccess)
            goto exit;

        memcpy(pdrw, &drwTemp, CbNewDRW(0));

        /* read the rest of the row */
        hr = HrReadBytes(hFile, &pdrw->ab, pdrw->cbRow, NULL);
        if (hr != hrSuccess)
        {
            fBadTableData = TRUE;
            goto exit;
        }

        sc = ScRelocProps((UINT) pdrw->rw.cValues, (LPSPropValue) pdrw->ab,
            pdrw->rw.lpProps, &pdrw->ab, &cbOut);
        if (sc != S_OK || cbOut != pdrw->cbRow)
        {
            hr = ResultFromScode(MAPI_E_CORRUPT_DATA);
            fBadTableData = TRUE;
            goto exit;
        }

        pdrw->rw.lpProps = (LPSPropValue) pdrw->ab;

        /* add this row to the table */
        hr = lptbl->lpVtbl->HrModifyRow(lptbl, &pdrw->rw);
        if (hr != hrSuccess)
            goto exit;

        FreeNull(pdrw);
        pdrw = NULL;
    }

exit:
    if (hFile != INVALID_HANDLE_VALUE)
        CloseHandle(hFile);

    /* erase the file if it is bogus. We will regenerate it if we can. */
    if (fBadTableData)
        DeleteFile(szFile);

    FreeNull(szFile);
    FreeNull(pdrw);

    DebugTraceResult(HrReadTableFromDisk, hr);
    return hr;
}

/************************************************************************
 * HrGetTime
 *
 * Purpose  return the value of PR_LAST_MODIFICATION_TIME from the properties
 *          in the given property array
 *
 * Parameters
 *  prw         pointer to the table row to search
 *  pfiletime   pointer to last modification time
 */
static HRESULT HrGetTime(LPSRow prw, FILETIME *pfiletime)
{
    LPSPropValue pvalT;
    LPSPropValue pvalMax;
    SCODE sc = MAPI_E_NOT_FOUND;

    Assert(!IsBadReadPtr(prw, sizeof(SRow)));
    Assert(prw->cValues <= UINT_MAX / sizeof(SPropValue));
    Assert(!IsBadReadPtr(prw->lpProps, ((UINT) prw->cValues) * sizeof(SPropValue)));
    Assert(!IsBadWritePtr(pfiletime, sizeof(FILETIME)));

    pvalT = prw->lpProps;
    pvalMax = pvalT + prw->cValues;

    while (pvalT < pvalMax)
    {
        if (pvalT->ulPropTag == PR_LAST_MODIFICATION_TIME)
        {
            sc = S_OK;
            *pfiletime = pvalT->Value.ft;
            break;
        }
        pvalT++;
    }

    DebugTraceSc(HrGetTime, sc);
    return ResultFromScode(sc);
}

/*************************************************************************
 * HrSyncOutgoingTable
 *
 * Purpose
 *      Verifies that every table row in memory actually corresponds to
 *      a message on disk. If bad rows are found, removes them and
 *      rewrites the disk version of the table data. Note that this code
 *      does not verify that the message on disk actually is in the queue,
 *      nor does it check for messages that are somehow missing from the table.
 *
 *  lptbl           pointer to the outgoing table data object.
 *  pims            a pointer to the message store object.
 *
 */
HRESULT HrSyncOutgoingTable(LPTABLEDATA lptbl, PIMS pims)
{
    HRESULT hr;
    BOOL fRowsRemoved;

    hr = HrRemoveBadTableRows(lptbl, NULL, pims, &fRowsRemoved);

    if (hr == hrSuccess && fRowsRemoved)
        hr = HrWriteTableOnDisk(lptbl, (POBJ) pims, NULL, szOutgoingFileName);

    DebugTraceResult(HrSyncOutgoingTable, hr);
    return hr;
}

/*************************************************************************
 * HrSyncContentsTable
 *
 * Purpose
 *      Verifies that the table in memory agrees with what's on disk.
 *      If discrepancies are found, fixes them, and rewrites the disk
 *      version of the table data.
 *
 *  pifld           the parent folder of the contents table.
 *  fWriteTable     if TRUE, write the disk version of the table if the
 *                  in-memory table is out of sync.
 *
 */
HRESULT HrSyncContentsTable(PIFLD pifld, BOOL fWriteTable)
{
    HRESULT hr;
    BOOL fRowsRemoved;
    BOOL fRowsAdded;
    LPTABLEDATA lptbl;

    lptbl = pifld->lptblContents;

    hr = HrRemoveBadTableRows(lptbl, pifld, pifld->pims, &fRowsRemoved);
    if (hr != hrSuccess)
        goto exit;

    hr = HrAddMissingTableRows(lptbl, pifld, szMessageTemplate,
        (LPSPropTagArray) &sPropTagsContents, &fRowsAdded);
    if (hr != hrSuccess)
        goto exit;

    /* update folder's content count and unread count if */
    /* the table was out of ssync */

    if (fRowsRemoved || fRowsAdded)
    {
        hr = HrNewCounts(pifld, lptbl);
        if (hr != hrSuccess)
            goto exit;

        if (fWriteTable)
        {
            hr = HrWriteTableOnDisk(lptbl, (POBJ) pifld, pifld->peid->szPath,
                szContentsFileName);
            if (hr != hrSuccess)
                goto exit;
        }
    }
    else
    {
        /* If there aren't any rows in the table, we still need to
         * update the folder's count of messages, because the counts 
         * may not be zero, even though there aren't any messages on disk.
         */
        LPSRow lpSRow = NULL;

        hr = lptbl->lpVtbl->HrEnumRow(lptbl, 0, &lpSRow);
        if (hr != hrSuccess)
            goto exit;

        if (lpSRow == NULL)
            hr = HrWriteCounts(pifld, 0, 0);

        LMFree(&pifld->pims->lmr, lpSRow);
    }

exit:
    DebugTraceResult(HrSyncContentsTable, hr);
    return hr;
}

/*************************************************************************
 * HrRemoveBadTableRows
 *
 * Purpose
 *      Verifies that every row in the table given has a corresponding
 *      file on disk. If the file on disk does not exist, the routine
 *      removes the row from the table.
 *
 *  lptbl           pointer to table
 *  pifldParent     the folder that all objects should be in. May be NULL.
 *  pims            the message store object
 *  pfTableChanged  Pointer to a location to return a BOOL that, when TRUE,
 *                  indicates that a bad row was found, and the table was changed
 *
 */
static HRESULT HrRemoveBadTableRows(LPTABLEDATA lptbl, PIFLD pifldParent,
    PIMS pims, BOOL *pfTableChanged)
{
    HRESULT hr = hrSuccess;
    LPSRow lpSRow = NULL;
    BOOL fTableChanged = FALSE; /* TRUE if lptbl was changed */
    ULONG iRow = 0;

    while (TRUE)
    {
        LPSTR szPath;
        BOOL fIsParent = TRUE;
        PEID peid;

        hr = lptbl->lpVtbl->HrEnumRow(lptbl, iRow++, &lpSRow);

        if (hr != hrSuccess || lpSRow == NULL)
            break;

        peid = (PEID) lpSRow->lpProps->Value.bin.lpb;

        /* If the caller gave us a parent folder, verify that the message */
        /* is in that folder. For example, if the caller is checking the */
        /* contents table, we can check that all messages are in the folder */
        /* they should be, but for the outgoing queue table, we can't. */

        if (pifldParent)
        {
            hr = HrIsParent(pifldParent->peid, peid, &fIsParent);
            if (hr != hrSuccess)
                goto exit;
        }

        hr = HrFullPathName(pims->szStorePath, peid->szPath, NULL, &szPath);
        if (hr != hrSuccess)
            goto exit;

        /* Delete the row if it no longer exists on disk */
        /* or isn't in the correct folder */
        if ((GetFileAttributes(szPath) == -1) || !fIsParent)
        {
            HRESULT hrT;

            hrT = lptbl->lpVtbl->HrDeleteRow(lptbl, lpSRow->lpProps);

            if (hrT != hrSuccess)
            {
                TraceSz1("SampleMS: HrSyncTableWithDisk: error %s "
                    "deleting out-of-date table entry\n",
                    SzDecodeScode(GetScode(hrT)));
            }

            fTableChanged = TRUE;
        }

        LMFree(&pims->lmr, lpSRow);
        lpSRow = NULL;
        FreeNull(szPath);
    }

    AssertSz(!IsBadWritePtr(pfTableChanged, sizeof(BOOL)), "Bad parameter"
        " (pfTableChanged) given to HrRemoveBadTableRows");
    *pfTableChanged = fTableChanged;

exit:
    LMFree(&pims->lmr, lpSRow);
    DebugTraceResult(HrRemoveBadTableRows, hr);
    return hr;
}

/*************************************************************************
 * HrAddMissingTableRows
 *
 * Purpose
 *      Searches a folder for objects of the specified type, and verifies
 *      that each object exists in the table given, and is up-to-date.
 *      If the object does not exist or is out-of-date, the routine
 *      adds or updates the table row with current information from the object.
 *      This routine only works for contents tables currently.
 *
 *  lptbl           pointer to table
 *  pifld           the folder that all objects should be in.
 *  szTemplate      type of files to search for for this table type
 *  ptaga           list of proptags for this type of table
 *  pfTableChanged  Pointer to a location to return a BOOL that, when TRUE,
 *                  indicates that the table was changed to match the disk
 *
 */
static HRESULT HrAddMissingTableRows(LPTABLEDATA lptbl, PIFLD pifld,
    LPSTR szTemplate, LPSPropTagArray ptaga, BOOL * pfTableChanged)
{
    HRESULT hr;
    WIN32_FIND_DATA ffd;
    HANDLE hFindFile = INVALID_HANDLE_VALUE;
    ULONG ulOffset;
    LPTSTR szFile = NULL;       /* full path name of next file in the table */
    PEID peid = NULL;
    BOOL fTableChanged = FALSE;
    LPSRow lpSRow = NULL;
    SPropValue pvInstKey;
    PLMR plmr = &pifld->pims->lmr;

    /* for each file of the right kind ( message or folder ) on disk */
    /* make sure its entry in the cache is up to date */

    pvInstKey.ulPropTag = PR_INSTANCE_KEY;

    /* get the next file */
    hr = HrFindFirstID(pifld, szTemplate, &ulOffset, &szFile, &hFindFile,
        &ffd, &peid);

    while (hr == hrSuccess)
    {
        FILETIME ftTableTime;   /* modify time of szFile in lptbl */

        /* get its row in the table */
        pvInstKey.Value.bin.cb = CbEID(peid);
        pvInstKey.Value.bin.lpb = (LPBYTE) peid;

        hr = lptbl->lpVtbl->HrQueryRow(lptbl, &pvInstKey, &lpSRow, NULL);

        if (GetScode(hr) == MAPI_E_NOT_ENOUGH_MEMORY)
            goto exit;

        /* update the row if necessary */
        /* store in ftTableTime, the modify time of this object */
        /* as stored in the lptbl */
        if (hr == hrSuccess && lpSRow)
            hr = HrGetTime(lpSRow, &ftTableTime);

        if (hr != hrSuccess
            || lpSRow == NULL
            || CompareFileTime(&ftTableTime, &(ffd.ftLastWriteTime)) == -1)
        {
            fTableChanged = TRUE;

            HrUpdateRow(pifld->pims, lptbl, peid, ptaga, &(ffd.ftLastWriteTime),
                MAPI_MESSAGE);
        }

        LMFree(plmr, peid);
        peid = NULL;
        LMFree(plmr, lpSRow);
        lpSRow = NULL;

        hr = HrFindNextID(pifld, ulOffset, szFile, hFindFile, &ffd, &peid);
    }

    if (GetScode(hr) == MAPI_E_NOT_FOUND)
        hr = hrSuccess;

    if (hr == hrSuccess)
    {
        AssertSz(!IsBadWritePtr(pfTableChanged, sizeof(BOOL)), "Bad parameter"
            " (pfTableChanged) given to HrAddMissingTableRows");
        *pfTableChanged = fTableChanged;
    }

exit:
    CloseIDSearch(&hFindFile, &szFile);
    LMFree(plmr, lpSRow);
    LMFree(plmr, peid);

    DebugTraceResult(HrAddMissingTableRows, hr);
    return hr;
}

