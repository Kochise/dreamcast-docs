/*
 -  X P S T A T U S . H
 -
 *  Purpose:
 *      Definitions, typedefs and prototypes used by the Sample Transport
 *      Provider status interface.
 *
 *  Copyright 1992-1995 Microsoft Corporation.  All Rights Reserved.
 */

/* Local (not exported) functions */

/*  Called at TransportLogon() time to register the Status 
    Table row for this transport session. */

HRESULT HrBuildTransportStatus (LPXPL lpSession, ULONG ulFlags);

/*  Called at various times (send, receive, notify) to cause
    the PR_STATUS_CODE property in the Status Table to be 
    updated with a new value. */

HRESULT HrUpdateTransportStatus (LPXPL lpSession, ULONG ulFlags);

/* Status Object method prototypes */

#undef  INTERFACE
#define INTERFACE   struct _SOB

#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   MAPIMETHOD_DECLARE(type, method, SOB_)
        MAPI_IUNKNOWN_METHODS(IMPL)
        MAPI_IMAPIPROP_METHODS(IMPL)
        MAPI_IMAPISTATUS_METHODS(IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   MAPIMETHOD_TYPEDEF(type, method, SOB_)
        MAPI_IUNKNOWN_METHODS(IMPL)
        MAPI_IMAPIPROP_METHODS(IMPL)
        MAPI_IMAPISTATUS_METHODS(IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   STDMETHOD_(type, method)

DECLARE_MAPI_INTERFACE(SOB_)
{
    MAPI_IUNKNOWN_METHODS(IMPL)
    MAPI_IMAPIPROP_METHODS(IMPL)
    MAPI_IMAPISTATUS_METHODS(IMPL)
};

/* Actual status object memory structure */

typedef struct _SOB
{
    SOB_Vtbl FAR *      lpVtbl;         /* Call Table                           */
    LONG                lcInit;         /* Usage Count                          */
    struct _SOB *       lpsobMyAddress; /* Pointer to myself, used to validate  */
    HRESULT             hrLastError;    /* Saved last error                     */
    ULONG               ulOpenFlags;    /* Flags used to open the object        */
    LPXPL               lpxpl;          /* XP Session associated with object    */
    LPALLOCATEBUFFER    AllocateBuffer; /* MAPIAllocateBuffer func pointer      */
    LPALLOCATEMORE      AllocateMore;   /* MAPIAllocateMore func pointer        */
    LPFREEBUFFER        FreeBuffer;     /* MAPIFreeBuffer func pointer          */
    LPMAPISUP           lpMAPISup;      /* Support object. So we can release it */
} SOB, *LPSOB;

STDMETHODIMP SOB_Reserved (LPSOB lpSOB);    /* All MAPI_E_NO_SUPPORT */
STDMETHODIMP SOB_AccessDenied(LPSOB);       /* All MAPI_NO_ACCESS */
