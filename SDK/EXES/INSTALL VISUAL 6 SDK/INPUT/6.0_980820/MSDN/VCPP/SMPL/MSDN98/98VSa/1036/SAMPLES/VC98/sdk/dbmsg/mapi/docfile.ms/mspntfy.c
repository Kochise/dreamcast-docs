/*
 *  M S P N T F Y . C
 *
 *  Code for doing internal cross-process notifications within the 
 *  Sample Message Store provider.
 *
 *  Copyright 1992-1995 Microsoft Corporation.  All Rights Reserved.
 */

#include "msp.h"
#include <stdarg.h>

/* INTERNAL Function prototypes. */

long STDAPICALLTYPE LSMSOQNotifCallback(LPVOID lpvContext, ULONG cNotif,
    LPNOTIFICATION lpNotifs);
static void EmptyTable(LPTABLEDATA lptbl, PLMR plmr);
static HRESULT HrApplyOQNotifChanges(LPTABLEDATA lptbl, PONB ponbIn);
static HRESULT HrGetOutgoingNotificationKey(PIMS pims, LPNOTIFKEY * lppKey);
static HRESULT HrNotifyOnOutgoingQueue(PIMS pims, PEID peid, LPSRow prw,
    ULONG ulTableEvent, FILETIME *pftBeforeUpdate);

long STDAPICALLTYPE LSMSTblNotifCallback(LPVOID lpvContext, ULONG cNotif,
    LPNOTIFICATION lpNotifs);
HRESULT HrApplyTblNotifChanges(PIMS pims, PTNB ptnbIn);
static HRESULT HrGetTableNotificationKey(PIMS pims, LPNOTIFKEY * lppKey);

/*
 *  EXTERNAL FUNCTIONS (called from outside this file).
 */

/* 
 * HrCreateOGQueueMutex
 *
 *  Purpose
 *      Create the outgoing queue mutex, and return it to the caller.
 *
 *  Arguments
 *      phQMutex: Pointer to the location to return the new mutex.
 *
 *  Returns:
 *      HRESULT: Will return an error only if the CreateMutex call fails.
 */
HRESULT HrCreateOGQueueMutex(HANDLE *phQMutex)
{
    HRESULT hr = hrSuccess;
    HANDLE hMutex;
    LPTSTR szMutexName = "SMS_OGQUEUEFILE_MUTEX";

    hMutex = CreateMutex(NULL, FALSE, szMutexName);

    if (hMutex)
        *phQMutex = hMutex;

    #ifndef WIN16
    else
    {
        TraceSz1("SampleMS: HrCreateOGQueueMutex: call to"
            " CreateMutex failed (error %08lX)", GetLastError());
        
        hr = ResultFromScode(MAPI_E_CALL_FAILED);
    }
    #endif

    DebugTraceResult(HrCreateOGQueueMutex, hr);
    return hr;
}

/*
 * HrSetupPrivateNotifications
 *
 *  Purpose
 *      Setup two private channels via the MAPI notification engine to
 *      tell other processes running against this store when 1) the 
 *      outgoing queue changes and 2) when contents and hierarchy tables
 *      change. We communicate between the multiple client processes and
 *      the one spooler process. For the outgoing queue, we use a key that
 *      is the full pathname to the outgoing queue file. For the other
 *      tables, we use a unique 16-byte ID. Remember the connections so
 *      that we can Unsubscribe when we shutdown the store.
 *
 *  Arguments
 *      pims: a pointer to the message store object.
 *
 *  Side Effects
 *      Fills in the ulOQConn and ulTblConn members of pims.
 *
 *  Returns
 *      HRESULT
 */
HRESULT HrSetupPrivateNotifications(PIMS pims)
{
    HRESULT hr;
    LPMAPIADVISESINK lpAdvise;
    ULONG ulOQConn = 0;
    ULONG ulTblConn = 0;
    LPNOTIFKEY lpKey = NULL;

    /* Use the MAPI notification engine to tell myself */
    /* (across processes) when to update outgoing queue. */

    /* The key is the path to the disk cache of the outbound queue */
    hr = HrGetOutgoingNotificationKey(pims, &lpKey);
    if (hr != hrSuccess)
        goto exit;

    hr = HrAllocAdviseSink(&LSMSOQNotifCallback, (LPVOID) pims, &lpAdvise);
    if (hr != hrSuccess)
        goto exit;

    hr = pims->psup->lpVtbl->Subscribe(pims->psup, lpKey,
        fnevExtended, 0L, lpAdvise, &ulOQConn);

    /* Always release; mapi will have addref'ed it during Subscribe */
    UlRelease(lpAdvise);

    if (hr != hrSuccess)
        goto exit;

    FreeNull(lpKey);
    lpKey = NULL;

    /* Now, setup notifications for the other tables. */

    hr = HrGetTableNotificationKey(pims, &lpKey);
    if (hr != hrSuccess)
        goto exit;

    hr = HrAllocAdviseSink(&LSMSTblNotifCallback, (LPVOID) pims, &lpAdvise);
    if (hr != hrSuccess)
        goto exit;

    hr = pims->psup->lpVtbl->Subscribe(pims->psup, lpKey,
        fnevExtended, 0L, lpAdvise, &ulTblConn);

    /* Always release; mapi will have addref'ed it during Subscribe */
    UlRelease(lpAdvise);

    if (hr != hrSuccess)
        goto exit;

exit:
    FreeNull(lpKey);

    if (hr == hrSuccess)
    {
        /* Remember our use of the notification engine. */
        pims->ulOQConn = ulOQConn;
        pims->ulTblConn = ulTblConn;
    }
    else if (ulOQConn != 0)
        (void) pims->psup->lpVtbl->Unsubscribe(pims->psup, ulOQConn);

    DebugTraceResult(HrSetupPrivateNotifications, hr);
    return hr;
}

/*
 * HrUpdateOutgoingQueue
 *
 *  Purpose
 *      Updates the outgoing queue based on the information given. If the
 *      outgoing queue table is not open, or is out-of-date with respect to
 *      the outgoing queue file on disk, initializes the table. The function
 *      then applies the change requested to the table, writes the table on
 *      disk, and notifies other processes of the change.
 *
 *  Arguments
 *      pims: A pointer to the message store object.
 *      pimsg: For a TABLE_ROW_ADDED event, a pointer to the message being
 *          added to the queue; otherwise, this parameter should be NULL.
 *      peid: For a TABLE_ROW_DELETED event, a pointer to the entryid of the
 *          message being deleted from the queue; otherwise, this parameter
 *          should be NULL.
 *      ulTableEvent: The type of update event: Either TABLE_ROW_ADDED or
 *          TABLE_ROW_DELETED.
 *
 *  Returns
 *      HRESULT
 */
HRESULT HrUpdateOutgoingQueue(PIMS pims, PIMSG pimsg, PEID peid,
    ULONG ulTableEvent)
{
    HRESULT hr = hrSuccess;
    LPTABLEDATA lptbl;
    SRow srNewRow = {0, 0, NULL};
    LPSRow prw;
    BOOL fInMutex = FALSE;
    FILETIME ftBeforeUpdate;

    /* If the file mutex doesn't yet exist on this process, create it. */

    if (pims->hOGQueueMutex == NULL)
    {
        hr = HrCreateOGQueueMutex(&pims->hOGQueueMutex);
        if (hr != hrSuccess)
            goto exit;
    }

    /* Get the file mutex so that we can use the file (and change it) */
    /* without crossing paths with another process. */

    WaitForSingleObject(pims->hOGQueueMutex, INFINITE);
    fInMutex = TRUE;

    /* This routine will open the outgoing queue table if it's not already */
    /* open in this process, and will leave the opened copy around in pims. */

    if (pims->lptblOutgoing == NULL)
    {
        hr = HrNewOutgoingTableData(pims);
        if (hr != hrSuccess)
            goto exit;
    }

    lptbl = pims->lptblOutgoing;
    ftBeforeUpdate = pims->ftOGQueue;

    if (ulTableEvent == TABLE_ROW_ADDED)
    {
        ULONG cValues;

        AssertSz(pimsg, "A msg should be provided on an add");
        AssertSz(peid == NULL, "No entryid should be provided on an add");

        hr = pimsg->lpVtbl->GetProps(pimsg, (LPSPropTagArray) &sptaOutgoing,
            0, /* ansi */
            &cValues, &srNewRow.lpProps);
    
        if (HR_FAILED(hr))          /* Ignore warnings from GetProps. */
            goto exit;
    
        srNewRow.cValues = cValues;
    
        hr = lptbl->lpVtbl->HrModifyRow(lptbl, &srNewRow);
        if (hr != hrSuccess)
            goto exit;

        prw = &srNewRow;
    }
    else
    {
        AssertSz(ulTableEvent == TABLE_ROW_DELETED,
            "Bad event type received");
        AssertSz(pimsg == NULL, "No msg should be provided on a delete");
        AssertSz(peid, "An entryid should be provided on a delete");

        /* remove it from the outgoing queue */
        hr = HrRemoveRow(lptbl, peid);
        if (hr != hrSuccess)
            goto exit;

        prw = NULL;
    }

    hr = HrWriteTableOnDisk(lptbl, (POBJ) pims, NULL, szOutgoingFileName);
    if (hr != hrSuccess)
        goto exit;

    /* Update the last mod time of the table inside this process's */
    /* message store object. */

    hr = HrGetFileModTime(pims->szStorePath, szOutgoingFileName,
        &pims->ftOGQueue);
    if (hr != hrSuccess)
        goto exit;

    hr = HrNotifyOnOutgoingQueue(pims, peid, prw, ulTableEvent,
        &ftBeforeUpdate);

exit:
    if (fInMutex)
        ReleaseMutex(pims->hOGQueueMutex);

    LMFree(&pims->lmr, srNewRow.lpProps);

    DebugTraceResult(HrUpdateOutgoingQueue, hr);
    return hr;
}

/*
 * HrNewOutgoingTableData
 *
 * Purpose  Checks the outgoing table data object in the message store.
 *          If there isn't one, creates it and initializes it from disk.
 *          If there is one, empties it, and re-initializes it from disk.
 *          Should be inside the outgoing queue mutex during this function.
 *
 * Parameters
 *  pims    A pointer to the message store object.
 *
 * Side Effects
 *          Fills in the lptblOutgoing member of the pims.
 *          Updates pims->ftOGQueue with the last mod time of the 
 *          outgoing queue file.
 */
HRESULT HrNewOutgoingTableData(PIMS pims)
{
    HRESULT hr = hrSuccess;
    LPTABLEDATA lptbl = pims->lptblOutgoing;
    BOOL fTableCreated = FALSE;

    if (!lptbl)
    {
        PINST pinst;
        SCODE sc = S_OK;
    
        /* The table doesn't exist. Create it. */

        pinst = (PINST) PvGetInstanceGlobals();
    
        if (pinst == NULL)
        {
            hr = ResultFromScode(MAPI_E_CALL_FAILED);
            goto exit;
        }
    
        sc = CreateTable((LPIID) &IID_IMAPITableData, pims->lmr.lpAllocBuf,
            pims->lmr.lpAllocMore, pims->lmr.lpFreeBuf, pinst->lpmalloc,
            TBLTYPE_DYNAMIC, PR_INSTANCE_KEY, (LPSPropTagArray) &sptaOutgoing,
            &lptbl);
    
        if (sc != S_OK)
        {
            hr = ResultFromScode(sc);
            goto exit;
        }

        fTableCreated = TRUE;
    }
    else
    {
        /* The table exists already. Delete all rows from it. */
        EmptyTable(lptbl, &pims->lmr);
    }

    /* read the table in from disk */
    /* outgoing queue tables can't be regenerated, so any error reading */
    /* the table is fatal. We lose all messages in the OG queue if this */
    /* function has an error. */

    hr = HrReadTableFromDisk(lptbl, (POBJ) pims, NULL, OUTGOING_COLUMNS,
        szOutgoingFileName);
    if (hr != hrSuccess)
    {
        TraceSz("SMS: Bad OG Queue data on disk.");
        goto exit;
    }

    /* Verify that all messages in the table actually exist on disk. If */
    /* not, remove the row(s) and re-write the table to disk. */
    hr = HrSyncOutgoingTable(lptbl, pims);
    if (hr != hrSuccess)
        goto exit;

    /* Save away the last mod time of the table inside this process's */
    /* message store object. */

    hr = HrGetFileModTime(pims->szStorePath, szOutgoingFileName,
        &pims->ftOGQueue);
    if (hr != hrSuccess)
        goto exit;

    pims->lptblOutgoing = lptbl;

exit:
    if (hr != hrSuccess && fTableCreated)
        UlRelease(lptbl);

    DebugTraceResult(HrNewOutgoingTableData, hr);
    return hr;
}

/*
 * INTERNAL Functions (called from within this file ONLY).
 *
 */

/*----------------------------------------------------------------------+
|                                                                       |
|           CONTENTS AND HIERARCHY TABLE NOTIFICATION HANDLING          |
|                                                                       |
+----------------------------------------------------------------------*/

/*
 * LSMSTblNotifCallback
 *
 *  Purpose
 *      Update the contents or hierarchy table associated with the folder eid
 *      passed across. We should receive a notification when the tabledata
 *      object needs to have a row added, deleted or modified. Calls
 *      ChangeTable after decoding the notification.
 *
 *  Arguments
 *      lpvContext: A pointer to the message store object to use. We need
 *          to verify that the object is still valid before using it.
 *      cNotif: The number of notifications to process.
 *      lpNotif: A pointer to an array of NOTIFICATION structures.
 *
 *  Returns
 *      LONG: Always returns 0.
 */
long STDAPICALLTYPE LSMSTblNotifCallback(LPVOID lpvContext, ULONG cNotif,
    LPNOTIFICATION lpNotif)
{
    PIMS pims = (PIMS) lpvContext;
    SCODE sc = S_OK;
    HRESULT hr = hrSuccess;
    PTNB ptnb;

    /*
     * Our code sends one extended notification at a time.
     * The notification consists of the table event that occurred along with
     * an object notification containing the entryids we need. We only use
     * two of the entryids in the object notification. The ParentID fields
     * refer to the parent folder of the table we need to update. The EntryID
     * fields refer to the object that changed within the folder. The
     * ulObjType field will be either MAPI_MESSAGE (for contents table
     * changes) or MAPI_FOLDER (for hierarchy table changes).  All other
     * fields in the structure are unused and should be set to 0.
     */
    if (IMS_IsInvalid(pims)
        || cNotif != 1
        || (IsBadReadPtr(lpNotif, ((UINT) cNotif) * sizeof(NOTIFICATION)))
        || lpNotif->ulEventType != fnevExtended
        || lpNotif->info.ext.ulEvent != 0)
        return 0;

    ptnb = (PTNB) lpNotif->info.ext.pbEventParameters;

    if (IsBadReadPtr(ptnb, CbNewTNB(0))
        || IsBadReadPtr(ptnb, CbTNB(ptnb)))
        return 0;

    IMS_EnterCriticalSection(pims);

    hr = HrApplyTblNotifChanges(pims, ptnb);

    IMS_LeaveCriticalSection(pims);

    if (hr != hrSuccess)
        sc = GetScode(hr);

    return sc;
}

/* 
 * HrApplyTblNotifChanges
 *
 * Purpose
 *  This function relocates and validates the internal object notification
 *  passed in, and then calls ChangeTable to actually update any open tables
 *  within this process with the change given. The notification needs to be
 *  relocated because the pointers from the other process may not be valid
 *  on this process.
 *
 * Parameters
 *  pims: A pointer to the message store object.
 *  ptnbIn: A pointer to the table notification block (TNB) containing the
 *      data we need in order to update any open tables om this process.
 *
 * Returns: validation errors or hrSuccess.
 */
HRESULT HrApplyTblNotifChanges(PIMS pims, PTNB ptnbIn)
{
    HRESULT hr = hrSuccess;
    SCODE sc = S_OK;
    LPNOTIFICATION lpntf;
    PTNB ptnb = NULL;
    OBJECT_NOTIFICATION *pon;
    ULONG cb;

    /* Allocate a new notification block, and copy the data over before */
    /* relocation. */

    hr = HrAlloc(CbNewTNB(ptnbIn->cbNtf), &ptnb);
    if (hr != hrSuccess)
        goto ret;

    memcpy(ptnb, ptnbIn, (UINT) CbNewTNB(ptnbIn->cbNtf));

    lpntf = (LPNOTIFICATION) ptnb->abNtf;

    if (lpntf->ulEventType != fnevObjectModified)
    {
        TraceSz1("SMS: HrApplyTblNotifChanges: Bad ulEventType %08lX "
            "received", lpntf->ulEventType);
        hr = ResultFromScode(MAPI_E_CALL_FAILED);
        goto ret;
    }

    /* Relocate the notification into the address space of this process. */
    /* We passed along the memory offset of the originating process to allow */
    /* this code to work. Note that ScRelocNotifications currently only */
    /* works from "bad" addresses to "good" addresses. The code assumes that */
    /* pointers are "bad" inside the notification, and that after conversion, */
    /* they are valid. */

    sc = ScRelocNotifications(1, lpntf, ptnb->pvRef, (LPVOID) lpntf, &cb);
    if (sc != S_OK)
    {
        hr = ResultFromScode(sc);
        goto ret;
    }

    if (ptnb->cbNtf != cb)
    {
        hr = ResultFromScode(MAPI_E_CALL_FAILED);
        goto ret;
    }

    pon = (OBJECT_NOTIFICATION *) &(lpntf->info.obj);

    if (pon->ulObjType != MAPI_MESSAGE && pon->ulObjType != MAPI_FOLDER)
    {
        TraceSz1("SMS: HrApplyTblNotifChanges: unexpected Object Type %08lX",
            pon->ulObjType);
        hr = ResultFromScode(MAPI_E_CALL_FAILED);
        goto ret;
    }

    if (    FIsInvalidEID(pon->cbParentID, (PEID) pon->lpParentID, pims)
        ||  !FIsFolder((PEID) pon->lpParentID))
    {
        TraceSz("SMS: HrApplyTblNotifChanges: invalid parent entryid");
        hr = ResultFromScode(MAPI_E_CALL_FAILED);
        goto ret;
    }

    /* TABLE_CHANGED events don't require a lpEntryID, because multiple
     * objects have changed. ChangeTable() simply validates all rows in
     * the table against the files on disk.
     */
    if (    ptnb->ulTableEvent != TABLE_CHANGED
        &&  FIsInvalidEID(pon->cbEntryID, (PEID) pon->lpEntryID, pims))
    {
        TraceSz("SMS: HrApplyTblNotifChanges: invalid entryid");
        hr = ResultFromScode(MAPI_E_CALL_FAILED);
        goto ret;
    }

    ChangeTable(pims, (PEID) pon->lpParentID, (PEID) pon->lpEntryID,
        pon->ulObjType, ptnb->ulTableEvent, FALSE);

ret:
    FreeNull(ptnb);

    DebugTraceResult(HrApplyTblNotifChanges, hr);
    return hr;
}

/* 
 * HrSendNotif
 *
 * Purpose
 *  This function constructs and sends a notification to other active Sample
 *  Message Store processes open on this message store file. The notification
 *  describes a change (add, delete, or modify) to either a message (contents
 *  table) or folder (hierarchy table). The receiver will need to get two
 *  entryids, one for the parent folder of the changed object, and one for
 *  the changed object itself. The receiver also needs to know whether the
 *  changed object is a message or a folder, and what type of change occurred:
 *  add, delete, modify, or change (contents tables only).
 *
 * Parameters
 *  pims: Pointer to the message store object.
 *  peidParent: The entryid of the folder containing the table to update and
 *              the object that changed.
 *  peidObject: The entryid of the object that changed. May be NULL when
 *              sending a TABLE_CHANGED notification (contents tables only).
 *  ulTableEvent: TABLE_ROW_ADDED, TABLE_ROW_DELETED, TABLE_ROW_MODIFIED, or
 *              TABLE_CHANGED (TABLE_CHANGED only works on contents tables).
 *  ulObjType: The type of object that changed. This implies the type of table
 *              to update. May be MAPI_MESSAGE (contents table) or MAPI_FOLDER
 *              (hierarchy table).
 *
 * Returns: Memory and disk errors or success.
 */
HRESULT HrSendNotif(PIMS pims, PEID peidParent, PEID peidObject,
    ULONG ulTableEvent, ULONG ulObjType)
{
    HRESULT hr = hrSuccess;
    SCODE sc;
    LPNOTIFKEY lpKey = NULL;
    NOTIFICATION ntfTemp;
    NOTIFICATION ntf;
    PTNB ptnb = NULL;
    ULONG cbNtf;
    ULONG cbOut;
    ULONG ulFlags = 0;

    /* Get the key */
    hr = HrGetTableNotificationKey(pims, &lpKey);
    if (hr != hrSuccess)
        goto ret;

    /*
     * Our code sends one extended notification at a time. The notification
     * consists of the table event that occurred along with an object
     * notification containing the entryids we need. We send the type of
     * table event as part of our extended notification structure, and
     * package the object notification always as "fnevObjectModified". We
     * only use two of the entryids in the object notification. The ParentID
     * fields refer to the parent folder of the table we need to update. The
     * EntryID fields refer to the object that changed within the folder. The
     * ulObjType field will be either MAPI_MESSAGE (for contents table
     * changes) or MAPI_FOLDER (for hierarchy table changes).  All other
     * fields in the structure are unused and should be set to 0.
     */
    memset(&ntfTemp, 0, sizeof(NOTIFICATION));

    /* We always send the same type of event here. This is enough to get the
     * notification code to count and relocate what we send. We send the real
     * table event in ptnb->ulTableEvent (see below).
     */
    ntfTemp.ulEventType = fnevObjectModified;

    ntfTemp.info.obj.ulObjType  = ulObjType;

    ntfTemp.info.obj.lpParentID = (LPENTRYID) peidParent;
    ntfTemp.info.obj.cbParentID = CbEID(peidParent);

    if (ulTableEvent != TABLE_CHANGED)
    {
        ntfTemp.info.obj.lpEntryID  = (LPENTRYID) peidObject;
        ntfTemp.info.obj.cbEntryID  = CbEID(peidObject);
    }

    sc = ScCountNotifications(1, &ntfTemp, &cbNtf);
    if (sc != S_OK)
    {                   
        hr = ResultFromScode(sc);
        goto ret;
    }

    hr = HrAlloc(CbNewTNB(cbNtf), &ptnb);
    if (hr != hrSuccess)
        goto ret;

    /* Here's where we send the table event. It's either TABLE_ROW_ADDED,
     * TABLE_ROW_DELETED, TABLE_ROW_MODIFIED, or TABLE_CHANGED.
     */
    ptnb->ulTableEvent = ulTableEvent;
    ptnb->cbNtf = cbNtf;

    sc = ScCopyNotifications(1, &ntfTemp, (LPVOID) ptnb->abNtf, &cbOut);
    if (sc != S_OK)
    {
        hr = ResultFromScode(sc);
        goto ret;
    }

    AssertSz(cbOut == cbNtf, "ScCopyNotifications used a different # of bytes "
        "than ScCountNotifications returned.");

    /* Pass across the notification's memory offset so that the receiving */
    /* process can relocate the notification to its address space. */
    ptnb->pvRef = (LPVOID) ptnb->abNtf;
    
    ntf.ulEventType = fnevExtended;
    ntf.info.ext.ulEvent = 0;
    ntf.info.ext.cb = CbTNB(ptnb);
    ntf.info.ext.pbEventParameters = (LPBYTE) ptnb;

    hr = pims->psup->lpVtbl->Notify(pims->psup, lpKey, 1, &ntf, &ulFlags);

ret:
    FreeNull(lpKey);
    FreeNull(ptnb);

    DebugTraceResult(HrSendNotif, hr);
    return hr;
}

/*
 * HrGetTableNotificationKey
 *
 * Purpose
 *  Generate and return the notification key that will allow cross-process
 *  notifications for changes to any contents or hierarchy tables within a
 *  store. The memory returned should be freed with FreeNull. This
 *  notification key needs to work for processes attached to this particular
 *  message store, and should only receive notifications having to do with
 *  changes to tables. The key contains the store guid (unique for this store)
 *  preceeded by a ULONG with 0x0000ABCD in it. Note that the choice of
 *  0x0000ABCD is arbitrary. As long as the sender sends to the same key as
 *  the receiver listens to, and no unexpected sender sends to that key,
 *  we're fine.
 *
 * Parameters
 *  pims        pointer to the message store object.
 *  lppKey      pointer to the location to return the new key.
 */
static HRESULT HrGetTableNotificationKey(PIMS pims, LPNOTIFKEY * lppKey)
{
    HRESULT hr = hrSuccess;
    LPNOTIFKEY lpKey = NULL;
    ULONG cb;                   /* number of bytes in the key */

    /* allocate space for the key */
    cb = sizeof(ULONG) + sizeof(MAPIUID);
    hr = HrAlloc(CbNewNOTIFKEY(cb), (PPV) &lpKey);
    if (hr != hrSuccess)
        goto exit;

    *((ULONG *) &(lpKey->ab[0])) = 0x0000ABCD;
    GetResourceUID(pims, (MAPIUID *) &(lpKey->ab[sizeof(ULONG)]));
    lpKey->cb = cb;

exit:
    if (HR_FAILED(hr))
    {
        FreeNull(lpKey);
        lpKey = NULL;
    }

    *lppKey = lpKey;

    DebugTraceResult(HrGetTableNotificationKey, hr);
    return hr;
}

/*----------------------------------------------------------------------+
|                                                                       |
|               OUTGOING QUEUE NOTIFICATION HANDLING                    |
|                                                                       |
+----------------------------------------------------------------------*/

/*
 * LSMSOQNotifCallback
 *
 *  Purpose
 *      Update the outgoing queue table associated with the process that
 *      the spooler is using. We should receive a notification when the
 *      tabledata object needs to have a row added or deleted. If the
 *      tabledata object exists on the message store object, then call
 *      HrModifyRow (when a row is added), or HrRemoveRow (when a row is
 *      deleted) to update the table appropriately.
 *
 *  Arguments
 *      lpvContext: A pointer to the message store object to use. We need
 *          to verify that the object is still valid before using it.
 *      cNotif: The number of notifications to process.
 *      lpNotif: A pointer to an array of NOTIFICATION structures.
 *
 *  Returns
 *      LONG: Always returns 0.
 */
long STDAPICALLTYPE LSMSOQNotifCallback(LPVOID lpvContext, ULONG cNotif,
    LPNOTIFICATION lpNotif)
{
    PIMS pims = (PIMS) lpvContext;
    SCODE sc = S_OK;
    HRESULT hr = hrSuccess;
    FILETIME ftCurrent;
    BOOL fInMutex = FALSE;
    PONB ponb;

    /* Our code sends one extended notification at a time. This */
    /* extended notification contains two filetimes (the time */
    /* before the outgoing queue file was modified, and the time after */
    /* the change was made), and a standard notification with the change */
    /* to apply to the table. It should be an fnevTableModified, and */
    /* should be either TABLE_ROW_ADDED or TABLE_ROW_DELETED. If we ever */
    /* receive anything other than this, the code must change. */
    if (IMS_IsInvalid(pims)
        || cNotif != 1
        || (IsBadReadPtr(lpNotif, ((UINT) cNotif) * sizeof(NOTIFICATION)))
        || lpNotif->ulEventType != fnevExtended
        || lpNotif->info.ext.ulEvent != 0)
        return 0;

    ponb = (PONB) lpNotif->info.ext.pbEventParameters;

    if (IsBadReadPtr(ponb, CbNewONB(0))
        || IsBadReadPtr(ponb, CbONB(ponb)))
        return 0;

    IMS_EnterCriticalSection(pims);

    /* Check to see if the outgoing queue table data is open. If it isn't, */
    /* there is nothing to do, because the current table will be read and */
    /* initialized from disk when the spooler opens it. We're done. */

    if (!pims->lptblOutgoing)
        goto exit;

    /* If the file mutex doesn't yet exist on this process, create it. */

    if (pims->hOGQueueMutex == NULL)
    {
        hr = HrCreateOGQueueMutex(&pims->hOGQueueMutex);
        if (hr != hrSuccess)
            goto exit;
    }

    /* Get the file mutex so that we can use the file (and change it) */
    /* without crossing paths with another process. */

    WaitForSingleObject(pims->hOGQueueMutex, INFINITE);
    fInMutex = TRUE;

    /* Get time that the file was last modified */
    hr = HrGetFileModTime(pims->szStorePath, szOutgoingFileName, &ftCurrent);
    if (hr != hrSuccess)
        goto exit;

    /* If the time that this process last read the file is the same as */
    /* the time that the file was last modified, then don't do anything */
    /* because we already have all changes, including the one sent to us */
    /* in this notification. This can happen because we picked up two */
    /* changes at once, or because this process is actually the same */
    /* process that sent the notification. */
    if (CompareFileTime(&ftCurrent, &pims->ftOGQueue) == 0)
        goto exit;

    /* If the time that this process last read the file is the same as */
    /* the time that the other process read the file, then we can simply */
    /* apply the changes sent in the notification itself, and update our */
    /* time to the time after update sent in the notification. */
    /* If the times are different, or there is a problem applying the */
    /* changes, then reconstruct the table from the on-disk copy. */

    if ((CompareFileTime(&ponb->ftBeforeUpdate, &pims->ftOGQueue) == 0)
        && (HrApplyOQNotifChanges(pims->lptblOutgoing, ponb) == hrSuccess))
    {
        pims->ftOGQueue = ponb->ftAfterUpdate;
    }
    else
    {
        hr = HrNewOutgoingTableData(pims);
        if (hr != hrSuccess)
            goto exit;
    }

exit:
    if (fInMutex)
        ReleaseMutex(pims->hOGQueueMutex);

    IMS_LeaveCriticalSection(pims);

    if (hr != hrSuccess)
        sc = GetScode(hr);

    return sc;
}

/*
 * EmptyTable
 *
 *  Purpose
 *      Deletes all rows from the table data object given.
 *      Helper function for the outgoing queue table notification callback
 *      routine.
 *
 *  Arguments
 *      lptbl: A pointer to the tabledata object to empty.
 *      plmr: A pointer to the linked memory routines.
 *
 *  Returns
 *      void.
 */
static void EmptyTable(LPTABLEDATA lptbl, PLMR plmr)
{
    HRESULT hr;
    LPSRow lpsRow;
    LPSPropValue pval;
    LPSPropValue pvalMac;

    while (TRUE)
    {
        /* Get the first row. Note that as we delete rows, this will */
        /* keep giving us a new row. */

        hr = lptbl->lpVtbl->HrEnumRow(lptbl, 0, &lpsRow);
        if (hr != hrSuccess)
        {
            TraceSz1("Sample MS: EmptyTable: HrEnumRow failed with"
                " sc == %s", SzDecodeScode(GetScode(hr)));
            break;
        }

        /* The table is empty when no row is returned */
        if (!lpsRow)
            break;

        /* find the entryid in the property value array */
        pval = lpsRow->lpProps;
        pvalMac = pval + lpsRow->cValues;

        for (; pval < pvalMac; ++pval)
            if (pval->ulPropTag == PR_INSTANCE_KEY)
                break;

        /* Every row should contain an inst key. It is the index property. */
        if (pval == pvalMac)
        {
            TrapSz("No PR_INSTANCE_KEY found in the table row");
            break;
        }

        /* delete this row from the table */
        hr = lptbl->lpVtbl->HrDeleteRow(lptbl, pval);

        LMFree(plmr, lpsRow);
        lpsRow = NULL;

        if (hr != hrSuccess)
        {
            TraceSz1("Sample MS: EmptyTable: HrDeleteRow failed with"
                " error %s", SzDecodeScode(GetScode(hr)));
            break;
        }
    }

    return;
}

/*
 * HrApplyOQNotifChanges
 *
 *  Purpose
 *      Helper function of the notification callback routine. If the 
 *      table on disk hasn't changed except for the notification given,
 *      then we can update the outgoing queue table data directly instead
 *      of re-reading the table from disk. This function modifies the
 *      table data directly by calling HrModifyRow (when a row is added),
 *      or HrRemoveRow (when a row is deleted).
 *      Note that we have to convert the notification inside the ONB so
 *      that the pointers are valid. Also note that we may NOT modify the
 *      notification data at all; therefore, we must copy the data before
 *      changing it.
 *
 *  Arguments
 *      lptbl: a pointer to the table data object to update.
 *      ponbIn: a pointer to the ONB received in the callback.
 *
 *  Returns
 *      HRESULT
 */
static HRESULT HrApplyOQNotifChanges(LPTABLEDATA lptbl, PONB ponbIn)
{
    HRESULT hr = hrSuccess;
    SCODE sc;
    ULONG cb;
    LPNOTIFICATION lpntf;
    PONB ponb = NULL;

    /* Allocate a new notification block, and copy the data over before */
    /* relocation. */

    hr = HrAlloc(CbNewONB(ponbIn->cbNtf), &ponb);
    if (hr != hrSuccess)
        goto exit;

    memcpy(ponb, ponbIn, (UINT) CbNewONB(ponbIn->cbNtf));

    lpntf = (LPNOTIFICATION) ponb->abNtf;

    /* Relocate the notification into the address space of this process. */
    /* We passed along the memory offset of the originating process to allow */
    /* this code to work. Note that ScRelocNotifications currently only */
    /* works from "bad" addresses to "good" addresses. The code assumes that */
    /* pointers are "bad" inside the notification, and that after conversion, */
    /* they are valid. */

    sc = ScRelocNotifications(1, lpntf, ponb->pvRef, (LPVOID) lpntf, &cb);
    if (sc != S_OK)
    {
        hr = ResultFromScode(sc);
        goto exit;
    }

    if (ponb->cbNtf != cb)
    {
        hr = ResultFromScode(MAPI_E_CALL_FAILED);
        goto exit;
    }

    /* We don't expect any events other than those for a table. */

    if (lpntf->ulEventType != fnevTableModified)
    {
        TraceSz1("SMS: HrApplyOQNotifChanges: unexpected ulEventType %08lX",
            lpntf->ulEventType);
        hr = ResultFromScode(MAPI_E_CALL_FAILED);
        goto exit;
    }

    switch (lpntf->info.tab.ulTableEvent)
    {
    case TABLE_ROW_DELETED:

        /* delete the row from the table according to the index */
        /* property value in the notification structure */
        hr = lptbl->lpVtbl->HrDeleteRow(lptbl, &lpntf->info.tab.propIndex);
        if (hr != hrSuccess)
        {
            TraceSz1("SMS: HrApplyOQNotifChanges: HrDeleteRow returns sc == %s",
                SzDecodeScode(GetScode(hr)));
            goto exit;
        }
        break;

    case TABLE_ROW_ADDED:

        /* add the row to the table. We don't care where in the table */
        /* it goes, because the row will be sorted by the spooler in */
        /* its view anyway. */

        hr = lptbl->lpVtbl->HrModifyRow(lptbl, &lpntf->info.tab.row);
        if (hr != hrSuccess)
        {
            TraceSz1("SMS: HrApplyOQNotifChanges: HrModifyRow returns sc == %s",
                SzDecodeScode(GetScode(hr)));
            goto exit;
        }
        break;

    default:

        /* We don't expect any other table events than the */
        /* two above. */

        TraceSz1("SMS: HrApplyOQNotifChanges: unexpected ulTableEvent %08lX",
            lpntf->info.tab.ulTableEvent);
        break;
    }

exit:
    FreeNull(ponb);

    DebugTraceResult(HrApplyOQNotifChanges, hr);
    return hr;
}

/*
 * HrGetOutgoingNotificationKey
 *
 * Purpose  return the nofication key for the outgoing queue
 *          memory should be freed with FreeNull
 *          The key we use contains the full pathname to the outgoing
 *          queue file on disk. This should be unique for the store
 *          that we're running against.
 *
 * Parameters
 * pims         the store whose outgoing queue is being referred to
 * lppKey       pointer to the key
 */
static HRESULT HrGetOutgoingNotificationKey(PIMS pims, LPNOTIFKEY * lppKey)
{
    HRESULT hr = hrSuccess;
    LPNOTIFKEY lpKey = NULL;
    ULONG cb;                   /* number of bytes in the key */
    LPSTR szPath = NULL;        /* path to outgoing queue */

    hr = HrGetTableName((POBJ) pims, NULL, szOutgoingFileName, &szPath);
    if (HR_FAILED(hr))
        goto exit;

    /* allocate space for the key */
    cb = Cbtszsize(szPath);
    hr = HrAlloc(CbNewNOTIFKEY(cb), (PPV) &lpKey);
    if (hr != hrSuccess)
        goto exit;

    lstrcpy(lpKey->ab, szPath);
    lpKey->cb = cb;

exit:
    FreeNull(szPath);
    if (HR_FAILED(hr))
    {
        FreeNull(lpKey);
        lpKey = NULL;
    }
    *lppKey = lpKey;
    return hr;
}

/*
 * HrNotifyOnOutgoingQueue
 *
 * Purpose
 *  Send out a notification that the Outgoing Queue has had a row added
 *  or deleted. Also send the filetime of the queue file before and after
 *  the modification.
 *
 * Parameters
 *  pims: A pointer to the message store object.
 *  peid: (For TABLE_ROW_DELETED) The entryid of the message in the
 *          queue that was deleted.
 *  prw: (For TABLE_ROW_ADDED) A pointer to the row of data added
 *          to the OG Queue.
 *  ulTableEvent: Either TABLE_ROW_ADDED or TABLE_ROW_DELETED.
 *  pftBeforeUpdate: A pointer to the filetime of the queue file before the
 *          update was performed.
 */
static HRESULT HrNotifyOnOutgoingQueue(PIMS pims, PEID peid, LPSRow prw,
    ULONG ulTableEvent, FILETIME *pftBeforeUpdate)
{
    HRESULT hr;
    LPNOTIFKEY lpKey = NULL;
    ULONG ulFlags = 0;
    NOTIFICATION ntf;
    NOTIFICATION ntfTemp;
    PONB ponb = NULL;
    ULONG cbNtf;
    ULONG cbOut;
    SCODE sc;

    /* get the key */
    hr = HrGetOutgoingNotificationKey(pims, &lpKey);
    if (HR_FAILED(hr))
        goto exit;

    /* Assemble the notification. */
    ntfTemp.ulEventType = fnevTableModified;
    ntfTemp.info.tab.ulTableEvent = ulTableEvent;
    ntfTemp.info.tab.hResult = hrSuccess;

    if (ulTableEvent == TABLE_ROW_DELETED)
    {
        /* Send across the index property for the row: PR_INSTANCE_KEY */
        ntfTemp.info.tab.propIndex.ulPropTag = PR_INSTANCE_KEY;
        ntfTemp.info.tab.propIndex.Value.bin.cb = CbEID(peid);
        ntfTemp.info.tab.propIndex.Value.bin.lpb = (BYTE *) peid;
        memset(&(ntfTemp.info.tab.propPrior), 0, sizeof(SPropValue));
        ntfTemp.info.tab.row.cValues = 0;
        ntfTemp.info.tab.row.lpProps = NULL;
    }
    else
    {
        AssertSz(ulTableEvent == TABLE_ROW_ADDED,
            "Bad event type: about to send bogus internal notification");

        memset(&(ntfTemp.info.tab.propIndex), 0, sizeof(SPropValue));
        memset(&(ntfTemp.info.tab.propPrior), 0, sizeof(SPropValue));
        ntfTemp.info.tab.row = *prw;
    }

    sc = ScCountNotifications(1, &ntfTemp, &cbNtf);
    if (sc != S_OK)
    {
        hr = ResultFromScode(sc);
        goto exit;
    }

    hr = HrAlloc(CbNewONB(cbNtf), &ponb);
    if (hr != hrSuccess)
        goto exit;

    ponb->cbNtf = cbNtf;

    sc = ScCopyNotifications(1, &ntfTemp, (LPVOID) ponb->abNtf, &cbOut);
    if (sc != S_OK)
    {
        hr = ResultFromScode(sc);
        goto exit;
    }

    AssertSz(cbOut == cbNtf, "ScCopyNotifications used a different # of bytes "
        "than ScCountNotifications returned.");

    ponb->ftBeforeUpdate = *pftBeforeUpdate;
    ponb->ftAfterUpdate = pims->ftOGQueue;

    /* Pass across the notification's memory offset so that the receiving */
    /* process can relocate the notification to its address space. */
    ponb->pvRef = (LPVOID) ponb->abNtf;
    
    ntf.ulEventType = fnevExtended;
    ntf.info.ext.ulEvent = 0;
    ntf.info.ext.cb = CbONB(ponb);
    ntf.info.ext.pbEventParameters = (LPBYTE) ponb;

    hr = pims->psup->lpVtbl->Notify(pims->psup, lpKey, 1, &ntf, &ulFlags);

exit:
    FreeNull(lpKey);
    FreeNull(ponb);

    DebugTraceResult(HrNotifyOnOutgoingQueue, hr);
    return hr;
}


