/***********************************************************************
 *
 *  ABP.H
 *
 *  Definitions for Sample Address Book Provider
 *
 *  Copyright 1992-1995 Microsoft Corporation.  All Rights Reserved.
 *
 ***********************************************************************/


#ifdef _WIN32
#define INC_OLE2                /* Get the OLE2 stuff */
#define INC_RPC                 /* harmless on Windows NT; Windows 95 needs it */
#endif
#include <windows.h>
#include <windowsx.h>
#include <limits.h>
#include <mapiwin.h>
#include <mapidbg.h>

#include <mapidefs.h>
#include <mapicode.h>
#include <mapitags.h>
#include <mapiguid.h>
#include <mapispi.h>
#include <mapiutil.h>
#include <mapival.h>

#include <memory.h>
#include <commdlg.h>

/*
 *  IUnknown base members
 */
#define SAB_IUnknown                    \
    LONG                lcInit;         \
    HRESULT             hResult;        \
    UINT                idsLastError;   \
    HINSTANCE           hLibrary;       \
    LPALLOCATEBUFFER    lpAllocBuff;    \
    LPALLOCATEMORE      lpAllocMore;    \
    LPFREEBUFFER        lpFreeBuff;     \
    LPMALLOC            lpMalloc;       \
    CRITICAL_SECTION    cs

#define SAB_IUnkWithLogon               \
    SAB_IUnknown;                       \
    LPABLOGON           lpABLogon

#define SAB_Wrapped                     \
    SAB_IUnkWithLogon;                  \
    LPMAPIPROP          lpPropData

/*
 *  Definition of all the objects referred to in the various source modules
 *  of this provider.
 */

/*
 *  Declaration of IABProvider object implementation
 *  Code for this is in ABP.C
 */
#undef  INTERFACE
#define INTERFACE struct _ABP

#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   MAPIMETHOD_DECLARE(type, method, ABP_)
        MAPI_IUNKNOWN_METHODS(IMPL)
        MAPI_IABPROVIDER_METHODS(IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   MAPIMETHOD_TYPEDEF(type, method, ABP_)
        MAPI_IUNKNOWN_METHODS(IMPL)
        MAPI_IABPROVIDER_METHODS(IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   STDMETHOD_(type, method)

DECLARE_MAPI_INTERFACE(ABP_)
{
    MAPI_IUNKNOWN_METHODS(IMPL)
    MAPI_IABPROVIDER_METHODS(IMPL)
};


/*
 *  Declaration of IABLogon object implementation
 *  Code for this is in ABP.C
 */
#undef  INTERFACE
#define INTERFACE struct _ABPLOGON

#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   MAPIMETHOD_DECLARE(type, method, ABPLOGON_)
        MAPI_IUNKNOWN_METHODS(IMPL)
        MAPI_IABLOGON_METHODS(IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   MAPIMETHOD_TYPEDEF(type, method, ABPLOGON_)
        MAPI_IUNKNOWN_METHODS(IMPL)
        MAPI_IABLOGON_METHODS(IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   STDMETHOD_(type, method)

DECLARE_MAPI_INTERFACE(ABPLOGON_)
{
    MAPI_IUNKNOWN_METHODS(IMPL)
    MAPI_IABLOGON_METHODS(IMPL)
};


/*
 *  Declaration of IABContainer object implementation
 *  Code for this is in ROOT.C
 */
#undef  INTERFACE
#define INTERFACE   struct _ROOT

#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   MAPIMETHOD_DECLARE(type, method, ROOT_)
        MAPI_IUNKNOWN_METHODS(IMPL)
        MAPI_IMAPIPROP_METHODS(IMPL)
        MAPI_IMAPICONTAINER_METHODS(IMPL)
        MAPI_IABCONTAINER_METHODS(IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   MAPIMETHOD_TYPEDEF(type, method, ROOT_)
        MAPI_IUNKNOWN_METHODS(IMPL)
        MAPI_IMAPIPROP_METHODS(IMPL)
        MAPI_IMAPICONTAINER_METHODS(IMPL)
        MAPI_IABCONTAINER_METHODS(IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   STDMETHOD_(type, method)

DECLARE_MAPI_INTERFACE(ROOT_)
{
    MAPI_IUNKNOWN_METHODS(IMPL)
    MAPI_IMAPIPROP_METHODS(IMPL)
    MAPI_IMAPICONTAINER_METHODS(IMPL)
    MAPI_IABCONTAINER_METHODS(IMPL)
};

#define ROOT_ValidateObject(Method, pThis)          \
{                                                   \
    HRESULT hResult;                                \
    if (IsBadReadPtr(pThis, sizeof(ROOT)))          \
    {                                               \
        hResult = ResultFromScode(E_INVALIDARG);    \
        DebugTraceResult(ROOT##_##Method, hResult); \
        return hResult;                             \
    }                                               \
                                                    \
    if (pThis->lpVtbl != &vtblROOT)                 \
    {                                               \
        hResult = ResultFromScode(E_INVALIDARG);    \
        DebugTraceResult(ROOT##_##Method, hResult); \
        return hResult;                             \
    }                                               \
}



/*
 *  Declaration of IABContainer object implementation
 *  Code for this is in ABCONT.C
 */
#undef  INTERFACE
#define INTERFACE   struct _ABCNT

#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   MAPIMETHOD_DECLARE(type, method, ABC_)
        MAPI_IUNKNOWN_METHODS(IMPL)
        MAPI_IMAPIPROP_METHODS(IMPL)
        MAPI_IMAPICONTAINER_METHODS(IMPL)
        MAPI_IABCONTAINER_METHODS(IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   MAPIMETHOD_TYPEDEF(type, method, ABC_)
        MAPI_IUNKNOWN_METHODS(IMPL)
        MAPI_IMAPIPROP_METHODS(IMPL)
        MAPI_IMAPICONTAINER_METHODS(IMPL)
        MAPI_IABCONTAINER_METHODS(IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   STDMETHOD_(type, method)

DECLARE_MAPI_INTERFACE(ABC_)
{
    MAPI_IUNKNOWN_METHODS(IMPL)
    MAPI_IMAPIPROP_METHODS(IMPL)
    MAPI_IMAPICONTAINER_METHODS(IMPL)
    MAPI_IABCONTAINER_METHODS(IMPL)
};

#define ABC_ValidateObject(Method, pThis)           \
{                                                   \
    HRESULT hResult;                                \
    if (IsBadReadPtr(pThis, sizeof(ABC)))           \
    {                                               \
        hResult = ResultFromScode(E_INVALIDARG);    \
        DebugTraceResult(ABC##_##Method, hResult);  \
        return hResult;                             \
    }                                               \
                                                    \
    if (pThis->lpVtbl != &vtblABC)                  \
    {                                               \
        hResult = ResultFromScode(E_INVALIDARG);    \
        DebugTraceResult(ABC##_##Method, hResult);  \
        return hResult;                             \
    }                                               \
}


/*
 *  Declaration of IMAPIContainer object implementation
 *  Code for this is in ABSEARCH.C
 */
#undef  INTERFACE
#define INTERFACE   struct _ABSRCH

#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   MAPIMETHOD_DECLARE(type, method, ABSRCH_)
        MAPI_IUNKNOWN_METHODS(IMPL)
        MAPI_IMAPIPROP_METHODS(IMPL)
        MAPI_IMAPICONTAINER_METHODS(IMPL)
        MAPI_IABCONTAINER_METHODS(IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   MAPIMETHOD_TYPEDEF(type, method, ABSRCH_)
        MAPI_IUNKNOWN_METHODS(IMPL)
        MAPI_IMAPIPROP_METHODS(IMPL)
        MAPI_IMAPICONTAINER_METHODS(IMPL)
        MAPI_IABCONTAINER_METHODS(IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   STDMETHOD_(type, method)

DECLARE_MAPI_INTERFACE(ABSRCH_)
{
    MAPI_IUNKNOWN_METHODS(IMPL)
    MAPI_IMAPIPROP_METHODS(IMPL)
    MAPI_IMAPICONTAINER_METHODS(IMPL)
};

#define ABSRCH_ValidateObject(Method, pThis)        \
{                                                   \
    HRESULT hResult;                                \
    if (IsBadReadPtr(pThis, sizeof(ABSRCH)))        \
    {                                               \
        hResult = ResultFromScode(E_INVALIDARG);    \
        DebugTraceResult(ABSRCH##_##Method, hResult);   \
        return hResult;                             \
    }                                               \
                                                    \
    if (pThis->lpVtbl != &vtblABSRCH)                   \
    {                                               \
        hResult = ResultFromScode(E_INVALIDARG);    \
        DebugTraceResult(ABSRCH##_##Method, hResult);   \
        return hResult;                             \
    }                                               \
}



/*
 *  Declaration of IMailUser object implementation
 *  Code for this is in ABUSER.C
 */
#undef  INTERFACE
#define INTERFACE   struct _ABUSER

#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   MAPIMETHOD_DECLARE(type, method, ABU_)
        MAPI_IUNKNOWN_METHODS(IMPL)
        MAPI_IMAPIPROP_METHODS(IMPL)
        MAPI_IMAILUSER_METHODS(IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   MAPIMETHOD_TYPEDEF(type, method, ABU_)
        MAPI_IUNKNOWN_METHODS(IMPL)
        MAPI_IMAPIPROP_METHODS(IMPL)
        MAPI_IMAILUSER_METHODS(IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   STDMETHOD_(type, method)

DECLARE_MAPI_INTERFACE(ABU_)
{
    MAPI_IUNKNOWN_METHODS(IMPL)
    MAPI_IMAPIPROP_METHODS(IMPL)
    MAPI_IMAILUSER_METHODS(IMPL)
};

#define ABU_ValidateObject(Method, pThis)       \
{                                                   \
    HRESULT hResult;                                \
    if (IsBadReadPtr(pThis, sizeof(ABUSER)))        \
    {                                               \
        hResult = ResultFromScode(E_INVALIDARG);    \
        DebugTraceResult(ABU##_##Method, hResult);  \
        return hResult;                             \
    }                                               \
                                                    \
    if (pThis->lpVtbl != &vtblABU)                  \
    {                                               \
        hResult = ResultFromScode(E_INVALIDARG);    \
        DebugTraceResult(ABU##_##Method, hResult);  \
        return hResult;                             \
    }                                               \
}

/*
 *  Declaration of IMAPIProp object implementation
 *  Code for this is in WRAP.C
 */
#undef  INTERFACE
#define INTERFACE   struct _WRAP

#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   MAPIMETHOD_DECLARE(type, method, WRAP_)
        MAPI_IUNKNOWN_METHODS(IMPL)
        MAPI_IMAPIPROP_METHODS(IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   MAPIMETHOD_TYPEDEF(type, method, WRAP_)
        MAPI_IUNKNOWN_METHODS(IMPL)
        MAPI_IMAPIPROP_METHODS(IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   STDMETHOD_(type, method)

DECLARE_MAPI_INTERFACE(WRAP_)
{
    MAPI_IUNKNOWN_METHODS(IMPL)
    MAPI_IMAPIPROP_METHODS(IMPL)
};



#undef  INTERFACE
#define INTERFACE   struct _IVTABC

#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   MAPIMETHOD_DECLARE(type, method, IVTABC_)
        MAPI_IUNKNOWN_METHODS(IMPL)
        MAPI_IMAPITABLE_METHODS(IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   MAPIMETHOD_TYPEDEF(type, method, IVTABC_)
        MAPI_IUNKNOWN_METHODS(IMPL)
        MAPI_IMAPITABLE_METHODS(IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   STDMETHOD_(type, method)

DECLARE_MAPI_INTERFACE(IVTABC_)
{
    MAPI_IUNKNOWN_METHODS(IMPL)
    MAPI_IMAPITABLE_METHODS(IMPL)
};


/*
 *  Internal utility functions that allow access to data stored in the Init object
 */
void
RemoveLogonObject(LPABPROVIDER lpABProvider, LPVOID lpvABLogon, LPFREEBUFFER lpFreeBuff);

void
FindLogonObject(LPABPROVIDER lpABProvider, LPMAPIUID lpMuidToFind, LPABLOGON * lppABLogon);

/*
 *  Internal utility functions that allow access to data stored in the logon object
 */

LPMAPIUID
LpMuidFromLogon(LPABLOGON lpABLogon);

HRESULT
HrLpszGetCurrentFileName(LPABLOGON lpABLogon, LPSTR * lppszFileName);

HRESULT
HrReplaceCurrentFileName(LPABLOGON lpABLogon, LPSTR lpstrT);

void
GenerateContainerDN(LPABLOGON lpABLogon, LPSTR lpszName);

BOOL
FEqualSABFiles( LPABLOGON lpABLogon,
                LPSTR lpszFileName);

/*
 *
 *  Functions that return new objects
 *
 */

/*
 *  Creates a new ABPLogon object  (see ABLOGON.C)
 */
HRESULT
HrNewABLogon(   LPABLOGON *         lppABLogon,
                LPABPROVIDER        lpABP,
                LPMAPISUP           lpMAPISup,
                LPSTR               lpszSABFile,
                LPMAPIUID           lpmuid,
                HINSTANCE           hLibrary,
                LPALLOCATEBUFFER    lpAllocBuff,
                LPALLOCATEMORE      lpAllocMore,
                LPFREEBUFFER        lpFreeBuff,
                LPMALLOC            lpMalloc );

/*
 *  Creates a new ROOT container object  (see ROOT.C)
 */
HRESULT
HrNewROOT(LPABCONT *        lppROOT,
          ULONG *           lpulObjType,
          LPABLOGON         lpABPLogon,
          LPCIID            lpInterface,
          HINSTANCE         hLibrary,
          LPALLOCATEBUFFER  lpAllocBuff,
          LPALLOCATEMORE    lpAllocMore,
          LPFREEBUFFER      lpFreeBuff,
          LPMALLOC          lpMalloc );

/*
 *  Creates a new directory container object (see ABCONT.C)
 */
HRESULT 
HrNewSampDirectory( LPABCONT *          lppABC,
                    ULONG *             lpulObjType,
                    LPABLOGON           lpABPLogon,
                    LPCIID              lpInterface,
                    HINSTANCE           hLibrary,
                    LPALLOCATEBUFFER    lpAllocBuff,
                    LPALLOCATEMORE      lpAllocMore,
                    LPFREEBUFFER        lpFreeBuff,
                    LPMALLOC            lpMalloc );

/*
 *  Creates the search object associated with the SampDirectory (see ABSEARCH.C)
 */
HRESULT
HrNewSearch(LPMAPICONTAINER *   lppABSearch,
            LPABLOGON           lpABLogon,
            LPCIID              lpInterface,
            HINSTANCE           hLibrary,
            LPALLOCATEBUFFER    lpAllocBuff,
            LPALLOCATEMORE      lpAllocMore,
            LPFREEBUFFER        lpFreeBuff,
            LPMALLOC            lpMalloc );

/*
 *  Creates a new Mail User object  (see ABUSER.C)
 */
HRESULT
HrNewSampUser(  LPMAILUSER *        lppMAPIPropEntry,
                ULONG *             lpulObjectType,
                ULONG               cbEntryID,
                LPENTRYID           lpEntryID,
                LPABLOGON           lpABPLogon,
                LPCIID              lpInterface,
                HINSTANCE           hLibrary,
                LPALLOCATEBUFFER    lpAllocBuff,
                LPALLOCATEMORE      lpAllocMore,
                LPFREEBUFFER        lpFreeBuff,
                LPMALLOC            lpMalloc );

/*
 *  Creates a new one-off templateID object (see TID.C)
 */
HRESULT 
HrNewOOTID( LPMAPIPROP *        lppMAPIPropNew,
            ULONG               cbTemplateId,
            LPENTRYID           lpTemplateId,
            ULONG               ulTemplateFlags,
            LPMAPIPROP          lpMAPIPropData,
            LPABLOGON           lpABPLogon,
            LPCIID              lpInterface,
            HINSTANCE           hLibrary,
            LPALLOCATEBUFFER    lpAllocBuff,
            LPALLOCATEMORE      lpAllocMore,
            LPFREEBUFFER        lpFreeBuff,
            LPMALLOC            lpMalloc );

/*
 *  Creates a new one-off mail user object (see OOUSER.C)
 */
HRESULT
HrNewSampOOUser(LPMAILUSER *        lppMAPIPropEntry,
                ULONG *             lpulObjectType,
                ULONG               cbEntryID,
                LPENTRYID           lpEntryID,
                LPABLOGON           lpABPLogon,
                LPCIID              lpInterface,
                HINSTANCE           hLibrary,
                LPALLOCATEBUFFER    lpAllocBuff,
                LPALLOCATEMORE      lpAllocMore,
                LPFREEBUFFER        lpFreeBuff,
                LPMALLOC            lpMalloc );

/*
 *  Creates a new status object for this provider (see STATUS.C)
 */
HRESULT 
HrNewStatusObject(LPMAPISTATUS *    lppABS,
                ULONG *             lpulObjType,
                ULONG               ulFlags,
                LPABLOGON           lpABPLogon,
                LPCIID              lpInterface,
                HINSTANCE           hLibrary,
                LPALLOCATEBUFFER    lpAllocBuff,
                LPALLOCATEMORE      lpAllocMore,
                LPFREEBUFFER        lpFreeBuff,
                LPMALLOC            lpMalloc );

/*
 * Creates a new templateID object that's associated with
 * a SAB mailuser object.
 */
HRESULT
HrNewTID (  LPMAPIPROP *        lppMAPIPropNew,
            ULONG               cbTemplateId,
            LPENTRYID           lpTemplateId,
            ULONG               ulTemplateFlags,
            LPMAPIPROP          lpMAPIPropData,
            LPABLOGON           lpABPLogon,
            LPCIID              lpInterface,
            HINSTANCE           hLibrary,
            LPALLOCATEBUFFER    lpAllocBuff,
            LPALLOCATEMORE      lpAllocMore,
            LPFREEBUFFER        lpFreeBuff,
            LPMALLOC            lpMalloc );


/*
 *  Creates a new contents table object
 */
HRESULT
HrNewIVTAbc (LPMAPITABLE *      lppIVTAbc,
             LPABLOGON          lpABLogon,
             LPABCONT           lpABC,
             HINSTANCE          hLibrary,
             LPALLOCATEBUFFER   lpAllocBuff,
             LPALLOCATEMORE     lpAllocMore,
             LPFREEBUFFER       lpFreeBuff,
             LPMALLOC           lpMalloc );

/*
 *  Creates/Updates the SAB's root hierarchy
 */
HRESULT
HrBuildRootHier(LPABLOGON lpABLogon, LPMAPITABLE * lppMAPITable);


/*
 *  Sets an error string associated with a particular hResult on an object.
 *  It's used in conjunction with the method GetLastError.
 */
VOID SetErrorIDS (LPVOID lpObject, HRESULT hResult, UINT ids);


/*
 *  Loads a string from a resource.  Optionally allocates room for the string
 *  if lpAllocBuff is not NULL.  See ABP.C.
 */
SCODE ScLoadString( UINT                ids,
                    ULONG               ulcch,
                    LPALLOCATEBUFFER    lpAllocBuff,
                    HINSTANCE           hLibrary,
                    LPSTR *             lppsz);

/*
 *  The sample ABPs MAPIUID
 *
 *  This MAPIUID must be unique (see the Service Provider Writer's Guide on
 *  Constructing Entry IDs)
 */
#define MUIDABSAMPLE {0x81,0x2b,0x1f,0x40,0xbe,0xa3,0x10,0x19,0x9d,0x6e,0x00,0xdd,0x01,0x0f,0x54,0x02}

#define SZEMAILTYPE                         "MSPEER"
#define MAX_DISPLAY_NAME                    45

/*
 *  Browse record
 *
 *  The .SAB files are made up of the following records.
 */

#define MAX_NAME_SIZE   30
#define MAX_EMA_SIZE    50

#pragma pack(4)
typedef struct _ABCREC
{

    char rgchDisplayName[MAX_NAME_SIZE + 1];
    char rgchEmailAddress[MAX_EMA_SIZE + 1];

} ABCREC, *LPABCREC;
#pragma pack()

/*
 *  Defines of various entryid types
 */
#define SAMP_DIRECTORY  0x00000000
#define SAMP_USER       0x00000001
#define SAMP_UNKNOWN    0x00000002
#define SAMP_OOUSER     0x00000003

/*
 *  The version of this ABPs entryids
 */
#define SAMP_VERSION    0x000000002

/*
 *  Directory entry id structure
 *
 *  This entryid is permanent.
 */
typedef struct _dir_entryid
{

    BYTE abFlags[4];
    MAPIUID muid;
    ULONG ulVersion;
    ULONG ulType;
    MAPIUID muidID;

} DIR_ENTRYID, *LPDIR_ENTRYID;

/*
 *  Mail user entry id structure
 *
 *  This entryid is permanent.
 */
#pragma pack(4)
typedef struct _usr_entryid
{

    BYTE abFlags[4];
    MAPIUID muid;
    ULONG ulVersion;
    ULONG ulType;
    ABCREC abcrec;

} USR_ENTRYID, *LPUSR_ENTRYID;
#pragma pack()

/*
 *  One off user entry id structure
 *
 *  This entryid is permanent.
 */
typedef struct _oousr_entryid
{
    BYTE abFlags[4];
    MAPIUID muid;
    ULONG ulVersion;
    ULONG ulType;

} OOUSR_ENTRYID, *LPOOUSR_ENTRYID;


/*
 *  Externs used throughout various modules within this provider.
 *  They actually get defined in abp.c
 */

extern LCID lcidUser;

extern MAPIUID muidABSample;

extern MAPIUID muidSABProviderID;

extern DTBLLABEL dtbllabel;

extern DTBLPAGE dtblpage;

extern DTBLGROUPBOX dtblgroupbox;

extern CHAR szNoFilter[];

extern LPSTR lpszEMT;

extern CHAR szAddrTypeFilter[];

extern CHAR szFileNameFilter[];

#define PR_LISTBOX_TABLE                PROP_TAG(PT_OBJECT,0x6605)
#define PR_COMBOBOX_TABLE               PROP_TAG(PT_OBJECT,0x6607)
#define PR_DDLISTBOX_TABLE              PROP_TAG(PT_OBJECT,0x6609)


/*
 *  Properties defined for our one-off entry
 */
#define     PR_SERVER_NAME              PROP_TAG(PT_TSTRING,0x660b)
#define     PR_SHARE_NAME               PROP_TAG(PT_TSTRING,0x660c)
#define     PR_PATH_NAME                PROP_TAG(PT_TSTRING,0x660d)

#define MAX_SERVER_NAME                 15
#define MAX_SHARE_NAME                  12

/*
 *  MACROs for Win16
 */

#ifdef WIN16


#define lstrcatA        lstrcat
#define wsprintfA       wsprintf
#define CharUpperBuffA  CharUpperBuff

#endif /*WIN16*/
