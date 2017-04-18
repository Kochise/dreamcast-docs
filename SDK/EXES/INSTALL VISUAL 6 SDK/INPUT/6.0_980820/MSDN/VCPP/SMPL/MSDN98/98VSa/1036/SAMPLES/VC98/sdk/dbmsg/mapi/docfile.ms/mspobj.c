/*
 * M S P O B J . C
 *
 * Common code for implementation of objects in the sample message store
 * provider.
 *
 * Copyright (C) 1992-1995 Microsoft Corporation. All Rights Reserved.
 */

#include "msp.h"

/* Object Type to Neuter Function Map -------------------------------------- */

LPFNNEUTER rgfnNeuter[] =
{
    (LPFNNEUTER) 0,             /* IMSProvider */
    (LPFNNEUTER) 0,             /* IMSLogon */
    (LPFNNEUTER) IMS_Neuter,    /* IMsgStore */
    (LPFNNEUTER) IFLD_Neuter,   /* IMAPIFolder */
    (LPFNNEUTER) IMSG_Neuter,   /* IMessage */
    (LPFNNEUTER) IATCH_Neuter,  /* IAttach */
    (LPFNNEUTER) 0,             /* IStream */
    (LPFNNEUTER) 0,             /* IMAPITable */
};

/* Object Type to Interfaces Supported Map --------------------------------- */

REFIID MSP_IIDs[] =
{
    &IID_IMSProvider,
    &IID_IUnknown
};

REFIID MSL_IIDs[] =
{
    &IID_IMSLogon,
    &IID_IUnknown
};

REFIID MS_IIDs[] =
{
    &IID_IMsgStore,
    &IID_IMAPIProp,
    &IID_IUnknown
};

REFIID FLD_IIDs[] =
{
    &IID_IMAPIFolder,
    &IID_IMAPIContainer,
    &IID_IMAPIProp,
    &IID_IUnknown
};

REFIID MSG_IIDs[] =
{
    &IID_IMessage,
    &IID_IMAPIProp,
    &IID_IUnknown
};

REFIID ATCH_IIDs[] =
{
    &IID_IAttachment,
    &IID_IMAPIProp,
    &IID_IUnknown
};

REFIID STM_IIDs[] =
{
    &IID_IStream,
    &IID_IUnknown
};

REFIID TBL_IIDs[] =
{
    &IID_IMAPITable,
    &IID_IUnknown
};

REFIID *rgpriid[] =
{
    MSP_IIDs,
    MSL_IIDs,
    MS_IIDs,
    FLD_IIDs,
    MSG_IIDs,
    ATCH_IIDs,
    STM_IIDs,
    TBL_IIDs
};

#define OBJ_IsInvalid(pobj, f)                                  \
    (IsBadWritePtr(pobj, sizeof(OBJ))                           \
    || IsBadReadPtr((pobj)->lpVtbl, sizeof(OBJ_Vtbl))           \
    || (pobj)->lpVtbl->f != OBJ_##f                             \
    || (pobj)->wType >= OT_MAX)

/* OBJ_QueryInterface ------------------------------------------------------ */

BOOL 
FQueryInterface(int wType, REFIID riid)
{
    REFIID *priid = rgpriid[wType];

    while (1)
    {
        if (IsEqualGUID(riid, *priid))
            return (TRUE);

        if (*priid == &IID_IUnknown)
            break;

        priid += 1;
    }

    return (FALSE);
}

STDMETHODIMP 
OBJ_QueryInterface(POBJ pobj, REFIID riid, LPVOID * ppvObj)
{
    if (    OBJ_IsInvalid(pobj, QueryInterface)
        ||  IsBadReadPtr(riid, sizeof(IID))
        ||  IsBadWritePtr(ppvObj, sizeof(LPVOID)))
        return ResultFromScode(E_INVALIDARG);

    /* Even if an error is returned, must zero *ppvObj */
    *ppvObj = 0;

    if (FQueryInterface(pobj->wType, riid))
    {
        UlAddRef(pobj);
        *ppvObj = pobj;
        return (0);
    }

    return (ResultFromScode(E_NOINTERFACE));
}

/* OBJ_AddRef -------------------------------------------------------------- */

STDMETHODIMP_(ULONG) OBJ_AddRef(POBJ pobj)
{
    LONG cRef;

    if (OBJ_IsInvalid(pobj, AddRef))
    {
        TraceSz1("Sample MS: OBJ_AddRef(pobj=%08lX): Object is invalid and "
            "is being ignored", pobj);
        return (0);
    }

    OBJ_EnterCriticalSection(pobj);

#ifdef DEBUG
    if (pobj->wType == OT_MSGSTORE)
        Assert(!OBJ_TestFlag(pobj, MSF_BEINGDESTROYED));
#endif

    AssertSz1(      pobj->wType == OT_MSGSTORE
              ||    pobj->cRef >= 1, "OBJ_AddRef(): Bogus cRef (%08lX)", pobj->cRef);

    cRef = ++pobj->cRef;

    OBJ_LeaveCriticalSection(pobj);

    return (cRef);
}

/* OBJ_Release ------------------------------------------------------------- */

/* Used by Message Store, Message, and Attachment objects. All other objects */
/* have their own implementations of Release. */

STDMETHODIMP_(ULONG) OBJ_Release(POBJ pobj)
{
    LONG cRef;

    if (!pobj)
        return (0);

    if (OBJ_IsInvalid(pobj, Release))
    {
        TraceSz1("SampleMS: OBJ_Release(pobj=%08lX): Object is invalid and is "
            "being ignored", pobj);
        return (0);
    }

    OBJ_EnterCriticalSection(pobj);

    AssertSz(pobj->cRef > 0, "OBJ_Release(): Too many releases");

    cRef = --pobj->cRef;

    if (cRef == 0)
    {
        if (pobj->wType != OT_MSGSTORE)
            pobj->lpVtbl = 0;

        if (pobj->pobjHead == 0)
        {
            OBJ_Destroy(pobj);
            return (0);
        }
    }

    OBJ_LeaveCriticalSection(pobj);

    return (cRef);
}

/* OBJ_Enqueue / OBJ_Dequeue / OBJ_Destroy --------------------------------- */

void OBJ_Enqueue(POBJ pobj, POBJ pobjParent)
{
    pobj->pobjParent = pobjParent;
    pobj->pobjNext = pobjParent->pobjHead;
    pobjParent->pobjHead = pobj;
}

void OBJ_Dequeue(POBJ pobj)
{
    if (pobj->pobjParent != NULL)
    {
        POBJ *ppobj = &pobj->pobjParent->pobjHead;

        while (TRUE)
        {
            POBJ pobjCur = *ppobj;

            if (pobjCur == NULL)
                break;

            if (pobjCur == pobj)
            {
                *ppobj = pobj->pobjNext;
                break;
            }

            ppobj = &pobjCur->pobjNext;
        }

        pobj->pobjParent = 0;
    }
}

/* 
 * OBJ_Destroy
 * 
 * Destroy an object. If this object was the last thing causing the parent to
 * exist, then we should destroy the parent, and so on up the chain. There are
 * two actual critical sections in the sample store. One is in the msp (message
 * store provider) object. The other is in the msl (message store logon) object.
 * All other objects in the sample store contain a pointer to the msl object's 
 * critical section (they all share it). When we arrive at this routine, we 
 * should have the object's critical section locked, i.e., the msl critical
 * section should be locked. That's why there are calls to leave a critical
 * section that aren't balanced with an enter.
 */

void OBJ_Destroy(POBJ pobj)
{
    PIMS pims;
    POBJ pobjParent;
    LPFNNEUTER lpfnNeuter;
    LPMAPISUP psup;

    pims = pobj->pims;

    while (1)
    {
        /* Call a routine to make the object free any memory */
        /* or other structures it has. (We call this "neutering" the object.) */

        if ((lpfnNeuter = rgfnNeuter[pobj->wType]) != 0)
            lpfnNeuter(pobj);

        pobjParent = pobj->pobjParent;

        if (pobj == (POBJ) pims)
        {
            if (pobjParent != NULL)
            {
                /* The parent in this case is the msp (message store provider) */
                /* object. We need to get its critical section in order to */
                /* safely dequeue the message store object. */

                OBJ_EnterCriticalSection(pobjParent);
                OBJ_Dequeue(pobj);
                OBJ_LeaveCriticalSection(pobjParent);
            }

            pobjParent = (POBJ) pims->pmsl;
            psup = pims->psup;

            pobj->lpVtbl = 0;
            LMFree(&pims->lmr, pobj);

            /* This leave balances the enter in the calling function. */
            /* Since we just freed the message store object, we can't leave */
            /* critical section using that pointer. Therefore, use the msl */
            /* (message store logon) object's critical section instead. They */
            /* are the same (see header comment at top of function). */

            OBJ_LeaveCriticalSection(pobjParent);

            UlRelease(psup);    /* do this last */
            break;
        }

        OBJ_Dequeue(pobj);

        pobj->lpVtbl = 0;
        LMFree(&pims->lmr, pobj);

        pobj = pobjParent;

        if (pobj == 0 || pobj->cRef || pobj->pobjHead)
        {
            /* This leave balances the enter in the calling function. */

            OBJ_LeaveCriticalSection((POBJ) pims);
            break;
        }
    }
}
