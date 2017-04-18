/*
 -  X P O P T I O N . H
 -
 *  Purpose:
 *      Defines a wrapped implementation of an IMAPIProp interface
 *      to be used by ScOptionDataCallBack() to wrap the IMAPIProp passed 
 *      in.  This object is wrapped so we can effect the behavior of the 
 *      OpenProperty() call.  Specifically, we wish to put up a Property 
 *      Sheet when the user tries to open the PR_DETAILS_TABLE property.
 *
 *  Copyright 1992-1995 Microsoft Corporation.  All Rights Reserved.
 */

/*
 *  Wrapped IMAPIProp Interface declaration.
 */

#undef  INTERFACE
#define INTERFACE   struct _WMPROP

#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   MAPIMETHOD_DECLARE(type, method, WMPROP_)
        MAPI_IUNKNOWN_METHODS(IMPL)
        MAPI_IMAPIPROP_METHODS(IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   MAPIMETHOD_TYPEDEF(type, method, WMPROP_)
        MAPI_IUNKNOWN_METHODS(IMPL)
        MAPI_IMAPIPROP_METHODS(IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   STDMETHOD_(type, method)

DECLARE_MAPI_INTERFACE(WMPROP_)
{
    MAPI_IUNKNOWN_METHODS(IMPL)
    MAPI_IMAPIPROP_METHODS(IMPL)
};


typedef struct _WMPROP 
{
    WMPROP_Vtbl *       lpVtbl;

    /* Need to be the same as other objects */
    
    LONG                lcInit;

    /* MAPI memory routines */
    
    LPALLOCATEBUFFER    lpAllocBuff;
    LPALLOCATEMORE      lpAllocMore;
    LPFREEBUFFER        lpFreeBuff;

    /* Private data */
    
    HINSTANCE           hInst;
    LPMALLOC            lpMalloc;
    ULONG               ulType;
    ULONG               cbOptionData;
    LPBYTE              lpbOptionData;
    LPMAPIPROP          lpMAPIProp;

} WMPROP, FAR *LPWMPROP;


