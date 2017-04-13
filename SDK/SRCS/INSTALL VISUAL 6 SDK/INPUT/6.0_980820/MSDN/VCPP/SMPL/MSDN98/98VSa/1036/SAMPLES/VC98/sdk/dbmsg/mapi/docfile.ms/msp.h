/*
 *  M S P . H
 *
 *  Definitions for the MAPI Sample Message Store Provider.
 *
 *  Copyright 1992-1995 Microsoft Corporation.  All Rights Reserved.
 */

#ifdef _WIN32
#define _INC_OLE
#define INC_OLE2 /* Get the OLE2 stuff */
#define INC_RPC  /* harmless on NT 3.5; Win95 needs it */
#endif

#include <windows.h>
#include <ole2.h>

#include <mapispi.h>
#include <mapidbg.h>
#include <mapiwin.h>
#include <mapiutil.h>
#include <mapival.h>
#include <smpms.h>

#include <mapidefs.h>
#include <mapicode.h>
#include <mapitags.h>
#include <mapiguid.h>

#include <imessage.h>

#include <limits.h>
#include <memory.h>

#if defined(_WIN32)
#define OLE_CHAR WCHAR
#else
#define OLE_CHAR char
#endif

#define VALIDATE

#ifdef VALIDATE
#define OBJ_ValidateParameters(pobj, intf, method, cbObj, _lpVtbl, arglist) \
    {                                                                       \
        Validate##_##intf##_##method arglist;                               \
        if (IsBadWritePtr(pobj, cbObj) || (pobj)->lpVtbl != _lpVtbl)        \
            return(ResultFromScode(MAPI_E_INVALID_PARAMETER)); }

#define OBJ_CheckParameters(pobj, intf, method, cbObj, _lpVtbl, arglist)    \
    {                                                                       \
        CheckParameters##_##intf##_##method arglist;                        \
        AssertSz(!IsBadWritePtr(pobj, cbObj) && (pobj)->lpVtbl == _lpVtbl,  \
            "Bad object pointer"); }
#else
#define OBJ_ValidateParameters(pobj, intf, method, cbObj, _lpVtbl, arglist)
#define OBJ_CheckParameters(pobj, intf, method, cbObj, _lpVtbl, arglist)
#endif /* VALIDATE */

typedef LPVOID *PPV;

#define NUM_RETRIES 6           /* number of times to retry opening a file */

/* Per-instance data. */
typedef struct
{
    UINT        cRef;
    LPMALLOC    lpmalloc;
} INST, *PINST;

/* Linked Memory Routines */
typedef struct _lmr
{
    LPALLOCATEBUFFER    lpAllocBuf;
    LPALLOCATEMORE      lpAllocMore;
    LPFREEBUFFER        lpFreeBuf;
}   LMR, *PLMR;

#define         LMAlloc(plmr, lcb, ppv)             ((plmr)->lpAllocBuf(lcb, ppv))
#define         LMAllocMore(plmr, lcb, pvLink, ppv) ((plmr)->lpAllocMore(lcb, pvLink, ppv))
#define         LMFree(plmr, pv)                    ((plmr)->lpFreeBuf(pv))

#define IsBadIfacePtr(param, iface)                 \
            (IsBadReadPtr((param), sizeof(iface))   \
        ||  IsBadReadPtr((param)->lpVtbl, sizeof(iface##Vtbl)))

#define SMPMS_VERSION   (0x03)  /* For MAPI 1.0 */

typedef struct _EID             /* Sample Message Store EntryID */
{
    BYTE abFlags[4];
    MAPIUID uidResource;
    BYTE bVersion;
    BYTE bVerPad[3];
    TCHAR szPath[1];
} EID, *PEID;

#define CbNewEID(_cbPath) \
    (offsetof(EID,szPath) + (_cbPath)*sizeof(CHAR))

/* This includes the NULL terminator */
#define CbEID(_peid) \
    (offsetof(EID,szPath) + \
    (((UINT)(lstrlen((_peid)->szPath)))*sizeof(CHAR)) + sizeof(CHAR))

/* This includes the NULL */
#define CbEIDPath(peid) (CbEID(peid)-CbNewEID(0))

#define PR_FILENAME_SEQUENCE_NUMBER PROP_TAG(PT_LONG,       0x6600)
#define PR_SMS_CONTENTS_SORT_ORDER  PROP_TAG(PT_MV_LONG,    0x6601)

#if defined(_WIN32)
#define CRITICAL_SECTION_MEMBERS    CRITICAL_SECTION cs;
#define CRITICAL_SECTION_MEMBERS_P  CRITICAL_SECTION *pcs;
#else
#define CRITICAL_SECTION_MEMBERS
#define CRITICAL_SECTION_MEMBERS_P
#endif

/* Object typedefs ------------------------------------------------------- */

typedef struct _OBJ     OBJ,        * POBJ,     ** PPOBJ;
typedef struct _MSP     MSP,        * PMSP,     ** PPMSP;
typedef struct _MSL     MSL,        * PMSL,     ** PPMSL;
typedef struct _IMS     IMS,        * PIMS,     ** PPIMS;
typedef struct _IFLD    IFLD,       * PIFLD,    ** PPIFLD;
typedef struct _IMSG    IMSG,       * PIMSG,    ** PPIMSG;
typedef struct _IATCH   IATCH,      * PIATCH,   ** PPIATCH;
typedef struct _STM     STM,        * PSTM,     ** PPSTM;
typedef struct _STG     STG,        * PSTG,     ** PPSTG;

/* Standard Object --------------------------------------------------------- */

#undef  INTERFACE
#define INTERFACE struct _OBJ

#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   MAPIMETHOD_DECLARE(type, method, OBJ_)
        MAPI_IUNKNOWN_METHODS(IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   STDMETHOD_(type, method)

DECLARE_MAPI_INTERFACE(OBJ_)
{
    MAPI_IUNKNOWN_METHODS(IMPL)
};

#define STANDARD_OBJECT_MEMBERS     \
    LONG                cRef;       \
    WORD                wType;      \
    WORD                wFlags;     \
    POBJ                pobjParent; \
    POBJ                pobjNext;   \
    POBJ                pobjHead;   \
    PIMS                pims;       \
    CRITICAL_SECTION_MEMBERS_P      \

/* NOTE: If you modify this enumeration, you must also update various */
/* structures in mspobj.c which use the type as an index into lookup tables */
enum {
    OT_MSPROVIDER,
    OT_MSLOGON,
    OT_MSGSTORE,
    OT_FOLDER,
    OT_MESSAGE,
    OT_ATTACH,
    OT_STREAM,
    OT_TABLE,
    OT_MAX
};

#define OBJF_MODIFY     ((WORD)0x0001)

struct _OBJ
{
    OBJ_Vtbl *      lpVtbl;
    STANDARD_OBJECT_MEMBERS
};

typedef void (*LPFNNEUTER)(POBJ);
extern LPFNNEUTER rgfnNeuter[];

#define OBJ_SetFlag(pobj, f)    ((pobj)->wFlags |=  (f))
#define OBJ_ClearFlag(pobj, f)  ((pobj)->wFlags &= ~(f))
#define OBJ_TestFlag(pobj, f)   ((pobj)->wFlags &   (f))

#ifdef _WIN32
#define OBJ_Initialize(pobj, _vtbl, _wType, _pims, _pcs)    \
    (pobj)->lpVtbl      = _vtbl;    \
    (pobj)->cRef        = 1;        \
    (pobj)->wType       = _wType;   \
    (pobj)->pims        = _pims;    \
    (pobj)->pcs         = _pcs;
#else
#define OBJ_Initialize(pobj, _vtbl, _wType, _pims, _pcs)    \
    (pobj)->lpVtbl      = _vtbl;    \
    (pobj)->cRef        = 1;        \
    (pobj)->wType       = _wType;   \
    (pobj)->pims        = _pims;
#endif

#define OBJ_EnterCriticalSection(pobj)  EnterCriticalSection((pobj)->pcs)
#define OBJ_LeaveCriticalSection(pobj)  LeaveCriticalSection((pobj)->pcs)
#define MSP_EnterCriticalSection(pmsp)  OBJ_EnterCriticalSection((POBJ)pmsp)
#define MSP_LeaveCriticalSection(pmsp)  OBJ_LeaveCriticalSection((POBJ)pmsp)
#define IMS_EnterCriticalSection(pims)  OBJ_EnterCriticalSection((POBJ)pims)
#define IMS_LeaveCriticalSection(pims)  OBJ_LeaveCriticalSection((POBJ)pims)

/*
 *  MSPOBJ.C
 */

BOOL    FQueryInterface(int wType, REFIID riid);

void    OBJ_Enqueue(POBJ pobj, POBJ pobjParent);
void    OBJ_Dequeue(POBJ pobj);
void    OBJ_Destroy(POBJ pobj);

extern CHAR szFolderTemplate[];         /*  "*.fld"         */
extern CHAR szMessageTemplate[];        /*  "*.msg"         */
extern CHAR szPropertyFileName[];       /*  "folder.prp"    */
extern CHAR szHierarchyFileName[];      /*  "hierarch.tbl"  */
extern CHAR szContentsFileName[];       /*  "contents.tbl"  */
extern CHAR szOutgoingFileName[];       /*  "outgoing.tbl"  */

/*
 *  MSPRFS.C
 */

/* Manifest constants */

#define RFS_CREATE      ((ULONG) 0x00000001)

/* Typedefs */

typedef struct _RFS         /* Receive Folder Storage */
{
    LPTSTR szFile;          /* Name of docfile containing RecFldr settings */
} RFS, * PRFS;

typedef struct _RFN         /* A single RFS Node */
{
    LPTSTR szClass;         /* Name of the message class */
    LPTSTR szName;          /* Relative path name of receive folder, i.e. */
                            /* EntryID minus the GUID                     */
} RFN, * PRFN;

/* Exported functions */

BOOL FIsValidMessageClass(LPTSTR szMessageClass);
HRESULT OpenRFS (LPTSTR szStoreRoot, LPTSTR szFile, ULONG ulFlags,
    PRFS * lpprfs);
HRESULT GetRFN (PRFS prfs, LPTSTR szClassName, PRFN * pprfn);
VOID    FreeRFN (PRFN prfn);
HRESULT DeleteRFN (PRFS prfs, LPTSTR szClassName);
HRESULT AddRFN (PRFS, PRFN prfn);
HRESULT CloseRFS (PRFS prfs);

/*
 *  MSPMS.C
 */

/* Manifest constants */

#define IMS_CREATE      ((WORD) 0x0002)
#define IMS_INVALID     ((WORD) 0x0004)

/* Typedefs */

#undef  INTERFACE
#define INTERFACE   struct _IMS

#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   MAPIMETHOD_DECLARE(type, method, IMS_)
        MAPI_IUNKNOWN_METHODS(IMPL)
        MAPI_IMAPIPROP_METHODS(IMPL)
        MAPI_IMSGSTORE_METHODS(IMPL)    
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   MAPIMETHOD_TYPEDEF(type, method, IMS_)
        MAPI_IUNKNOWN_METHODS(IMPL)
        MAPI_IMAPIPROP_METHODS(IMPL)
        MAPI_IMSGSTORE_METHODS(IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   STDMETHOD_(type, method)

DECLARE_MAPI_INTERFACE(IMS_)
{
    MAPI_IUNKNOWN_METHODS(IMPL)
    MAPI_IMAPIPROP_METHODS(IMPL)
    MAPI_IMSGSTORE_METHODS(IMPL)    
};

struct _IMS             /* Implementation of IMsgStore */
{
    IMS_Vtbl *      lpVtbl;     /* -> vtblIMS */
    STANDARD_OBJECT_MEMBERS
    LPTSTR      szStorePath;    /* Full path to the store root */
    MAPIUID     uidResource;    /* Message Store unique identifier */
    LPTSTR      szProps;        /* Full path to property docfile */
    PMSL        pmsl;           /* Logon object (MAPI session stuff) */
    PMSP        pmsp;           /* Provider object (global stuff) */
    LMR         lmr;            /* Linked memory routines */
    PRFS        prfs;           /* Struct handling access to receive folder */
    LPMAPISUP   psup;           /* MAPI Support object */
    SBinary     eidStore;       /* PR_STORE_ENTRYID */
    LPTABLEDATA lptblOutgoing;  /* outgoing queue for this store */
    HANDLE      hOGQueueMutex;  /* Mutex for reading/writing the OG Queue */
    FILETIME    ftOGQueue;      /* The time of the OQ file when we read it */
    ULONG       cOutgoingViews; /* number of views open on the outgoing queue */
    ULONG       ulOQConn;       /* Connection for OQ unadvise */
    HANDLE      hContTblMutex;  /* Mutex for reading/writing ALL cont tbls */
    ULONG       ulTblConn;      /* Connection for Tbl unadvise */
    LPMSGSESS   pmsgsess;       /* IMSG Session to create all messages within */
    ULONG       ulFlagsSLT;     /* Flags for StoreLogoffTransports */
};

#define MSF_SPOOLER         ((WORD)0x8000)
#define MSF_BEINGDESTROYED  ((WORD)0x4000)

#define SMS_SUPPORTMASK     (STORE_ENTRYID_UNIQUE |     \
                            STORE_ATTACH_OK |           \
                            STORE_OLE_OK |              \
                            STORE_NOTIFY_OK |           \
                            STORE_MV_PROPS_OK |         \
                            STORE_RESTRICTION_OK |      \
                            STORE_SORT_OK |             \
                            STORE_MODIFY_OK |           \
                            STORE_CREATE_OK |           \
                            STORE_SUBMIT_OK)

/* Outgoing Queue Notification Block (ONB) */
/* This is the format of our extended cross-process notification for the */
/* outgoing queue table. We use this to update the table data in other */
/* processes after we change it in the originating process. The changes */
/* that we pass across are either deleting a row (for example, when the */
/* spooler calls FinishedMsg), or adding a row (for example, when the */
/* client submits a message). */

typedef struct _ONB
{
    FILETIME ftBeforeUpdate;    /* time of the file before updating */
    FILETIME ftAfterUpdate;     /* time of the file after applying the update */
    LPVOID  pvRef;              /* memory offset from originating process */
    ULONG   cbNtf;              /* # of bytes in abNtf (the flat notif below) */
    BYTE    abNtf[1];           /* the update to apply to the table */
} ONB, * PONB;

#define CbNewONB(_cb)       (offsetof(ONB,abNtf) + (_cb))
#define CbONB(_ponb) \
    (offsetof(ONB,abNtf) + (UINT)((_ponb)->cbNtf))


/* Table Notification Block (TNB) */
/* This is the format of our extended cross-process notification for */
/* Contents and Hierarchy Tables. We use this notification to update a */
/* table in other processes after we change it in the originating process. */
/* The notification consists of an object notification containing the */
/* entryids we need. The fnev tells the event type. We only use two of */
/* the entryids in the object notification. The ParentID fields refer to */
/* the parent folder of the table we need to update. The EntryID fields */
/* refer to the object that changed within the folder. The ulObjType field */
/* will be either MAPI_MESSAGE (for contents table changes) or MAPI_FOLDER */
/* (for hierarchy table changes).  All other fields in the structure are */
/* unused and should be set to 0. */

typedef struct _TNB
{
    ULONG   ulTableEvent;   /* TABLE_ROW_ (ADDED, DELETED, MODIFIED) */
    LPVOID  pvRef;          /* memory offset from originating process */
    ULONG   cbNtf;          /* # of bytes in abNtf (the flat notif below) */
    BYTE    abNtf[1];       /* an object notification */
} TNB, * PTNB;

#define CbNewTNB(_cb)       (offsetof(TNB,abNtf) + (_cb))
#define CbTNB(_ptnb) \
    (offsetof(TNB,abNtf) + (UINT)((_ptnb)->cbNtf))


/* Exported functions */
HRESULT HrOpenIMSPropsFileRetry(LPMSGSESS pmsgsess, LPTSTR szFile, PLMR plmr,
    LPMAPISUP psup, BOOL fModify, LPMESSAGE * lppmsg);
BOOL IMS_IsInvalid(PIMS pims);

/* Constructors */

HRESULT HrNewIMS(LPTSTR szStorePath, LPTSTR szStoreProps, PMSP pmsp,
    PMSL pmsl, PRFS prfs, LPPROFSECT pps, LPMAPISUP psup, BOOL fCreate,
    PIMS *ppims);

/* Non-virtual public methods */

void IMS_Neuter(PIMS pims);
HRESULT HrInitIMSProps (PIMS pims, LPTSTR szPswd);
VOID GetResourceUID (PIMS pims, LPMAPIUID lpuid);
HRESULT HrUniqueFileName (PIMS pims, ULONG * lpulSeqNumber, LPTSTR *
    lppszNewName);
BOOL FIsInvalidEID (ULONG, PEID, PIMS);
/* Others */

STDAPI_(void) MsgReleaseStg (ULONG ulCallerData, LPMESSAGE lpMessage);
long STDAPICALLTYPE LSMSNotifCallback (LPVOID lpvContext,
    ULONG cNotif, LPNOTIFICATION lpNotifs);

/* column properties for outgoing queue */
#define OUTGOING_COLUMNS    13      /* number of columns in outgoing queue */
static const SizedSPropTagArray(OUTGOING_COLUMNS, sptaOutgoing) =
{
    OUTGOING_COLUMNS,
    {
        PR_ENTRYID,
        PR_SUBMIT_FLAGS,
        PR_INSTANCE_KEY,    /* the index column */
        PR_DISPLAY_TO,
        PR_DISPLAY_CC,
        PR_DISPLAY_BCC,
        PR_SENDER_NAME,
        PR_SUBJECT,
        PR_CLIENT_SUBMIT_TIME,
        PR_PRIORITY,
        PR_MESSAGE_FLAGS,
        PR_MESSAGE_SIZE,
        PR_SPOOLER_STATUS
    }
};


/*
 *  MSPFLD.C
 */

#define FAILED_SEARCH   (INVALID_HANDLE_VALUE)

#define MODIFY_INDEX    1       /* index of LAST_MODIFICATION_TIME in tables */

/* column properties for contents tables */
#define CONTENTS_COLUMNS    22      /* number of columns in a table of messages */
static const SizedSPropTagArray(CONTENTS_COLUMNS, sPropTagsContents) =
{
    CONTENTS_COLUMNS,
    {
        PR_ENTRYID,
        PR_LAST_MODIFICATION_TIME,  /* must be in position MODIFY_INDEX */
        PR_INSTANCE_KEY,            /* the index column */
        PR_HASATTACH,
        PR_SUBJECT,
        PR_SENDER_NAME,
        PR_DISPLAY_TO,
        PR_DISPLAY_CC,
        PR_CLIENT_SUBMIT_TIME,
        PR_MESSAGE_DELIVERY_TIME,
        PR_MESSAGE_FLAGS,
        PR_PRIORITY,
        PR_CONVERSATION_KEY,
        PR_SEARCH_KEY,
        PR_ICON,
        PR_MINI_ICON,
        PR_SENSITIVITY,
        PR_MESSAGE_CLASS,
        PR_RECORD_KEY,
        PR_SPOOLER_STATUS,
        PR_SENT_REPRESENTING_NAME,
        PR_MSG_STATUS
    }
};

/* column properties for hierarchy tables */
#define HIERARCHY_COLUMNS   12
static const SizedSPropTagArray(HIERARCHY_COLUMNS, sPropTagsHierarchy) =
{
    HIERARCHY_COLUMNS,
    {
        PR_ENTRYID,
        PR_LAST_MODIFICATION_TIME, /* must be in postion MODIFY_INDEX */
        PR_DISPLAY_NAME,    /* the folder name */
        PR_INSTANCE_KEY,    /* the index column */
        PR_OBJECT_TYPE,
        PR_COMMENT,
        PR_CONTENT_COUNT,
        PR_CONTENT_UNREAD,
        PR_STATUS,
        PR_SUBFOLDERS,
        PR_FOLDER_TYPE,
        PR_DEPTH            /* depth in hierarchy, must be last */
    }
} ;

#undef  INTERFACE
#define INTERFACE struct _IFLD
    
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   MAPIMETHOD_DECLARE(type, method, IFLD_)
        MAPI_IUNKNOWN_METHODS(IMPL)
        MAPI_IMAPIPROP_METHODS(IMPL)
        MAPI_IMAPICONTAINER_METHODS(IMPL)
        MAPI_IMAPIFOLDER_METHODS(IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   MAPIMETHOD_TYPEDEF(type, method, IFLD_)
        MAPI_IUNKNOWN_METHODS(IMPL)
        MAPI_IMAPIPROP_METHODS(IMPL)
        MAPI_IMAPICONTAINER_METHODS(IMPL)
        MAPI_IMAPIFOLDER_METHODS(IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   STDMETHOD_(type, method)

DECLARE_MAPI_INTERFACE(IFLD_)
{
    MAPI_IUNKNOWN_METHODS(IMPL)
    MAPI_IMAPIPROP_METHODS(IMPL)
    MAPI_IMAPICONTAINER_METHODS(IMPL)
    MAPI_IMAPIFOLDER_METHODS(IMPL)
};

extern IFLD_Vtbl    vtblIFLD;

/* we store PR_ENTRYID, PR_PARENT_ENTRYID and PR_INSTANCE_KEY internally */
#define cpropIFLDInternal       3

/* Folder's instance data */
struct _IFLD
{
    IFLD_Vtbl *     lpVtbl; /* -> vtblIFLD */
    STANDARD_OBJECT_MEMBERS
    PEID peid;                  /* EntryID of this folder */
    ULONG           cval;       /* # of internal props */
    LPSPropValue    pval;       /* internal prop values */
    LPTABLEDATA lptblContents;  /* contents table for this folder */
    ULONG cContentsViews;       /* number of views open on contents table*/
    LPTABLEDATA lptblHierarchy; /* hierarchy table for this folder */
    ULONG cHierarchyViews;      /* number of views open on hierarchy table */
};

HRESULT HrNewIFLD(PEID peid, PIMS pims, BOOL fModify, PIFLD * ppifld);
HRESULT HrCreateFolderStorage(PIFLD pifld, ULONG ulFolderType,
    LPSTR szFolderName, LPSTR szFolderComment, BOOL fCreateDir,
    PIMS pims, PEID *ppeid);
HRESULT HrNewEID (PIFLD, PIMS, LPTSTR, ULONG *, PEID *);
HRESULT HrIncrementOneROProp(PIFLD pifld, LONG lDelta, ULONG ulPT);
HRESULT HrIsParent(PEID peidParent, PEID peidChild, BOOL *pfIsParent);
HRESULT HrGetFileModTime(LPTSTR szStorePath, LPTSTR szFileName,
    FILETIME *pft);
HRESULT HrFullPathName (LPSTR, LPSTR, LPSTR, LPSTR *);
HRESULT HrFullToRelative(LPTSTR, PIMS, LPTSTR *);
HRESULT HrOpenPropertyMessageRetry(PEID peid, PIMS pims,
    BOOL fModifyExclusive, LPMESSAGE *lppmsg);
HRESULT HrFindFirstID( PIFLD, LPTSTR, ULONG *, LPTSTR *, HANDLE *,
                    WIN32_FIND_DATA *, PEID *);
HRESULT HrFindNextID( PIFLD, ULONG, LPTSTR, HANDLE, WIN32_FIND_DATA *, PEID *);
void CloseIDSearch( HANDLE *, LPTSTR *);
HRESULT HrFullToRelative( LPTSTR, PIMS, LPTSTR *);
HRESULT HrUpdateRow(PIMS pims, LPTABLEDATA lptbl, PEID peid,
    LPSPropTagArray pPTA, FILETIME *pft, ULONG ulObjType);
void    IFLD_Neuter (PIFLD);
void ChangeTable(PIMS pims, PEID peidTable, PEID peidObject,
    ULONG ulObjType, ULONG ulTableEvent, BOOL fSendNotif);
HRESULT HrRemoveRow( LPTABLEDATA lptbl, PEID peid);

/*
 *  MSPMSG.C
 */

#undef  INTERFACE
#define INTERFACE struct _IMSG
    
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   MAPIMETHOD_DECLARE(type, method, IMSG_)
        MAPI_IUNKNOWN_METHODS(IMPL)
        MAPI_IMAPIPROP_METHODS(IMPL)
        MAPI_IMESSAGE_METHODS(IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   MAPIMETHOD_TYPEDEF(type, method, IMSG_)
        MAPI_IUNKNOWN_METHODS(IMPL)
        MAPI_IMAPIPROP_METHODS(IMPL)
        MAPI_IMESSAGE_METHODS(IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   STDMETHOD_(type, method)

DECLARE_MAPI_INTERFACE(IMSG_)
{
    MAPI_IUNKNOWN_METHODS(IMPL)
    MAPI_IMAPIPROP_METHODS(IMPL)
    MAPI_IMESSAGE_METHODS(IMPL)
};

extern IMSG_Vtbl    vtblIMSG;

struct _IMSG            /* Implementation of IMessage */
{
    IMSG_Vtbl * lpVtbl; /* -> vtblIMSG */
    STANDARD_OBJECT_MEMBERS
    LPMESSAGE       lpmsg;
    PEID            peid;
    ULONG           cval;
    LPSPropValue    pval;
};

#define MSGF_NEWLYCREATED           ((WORD)0x4000)
#define MSGF_MSGINMSG               ((WORD)0x2000)
#define MSGF_FRESH                  ((WORD)0x1000)
#define MSGF_CREATEDSTORAGE         ((WORD)0x0800)

#define SET         1
#define UNSET       2
#define DONT_SAVE   4

/* Exported functions */

HRESULT HrNewIMSG(PEID peid, PIMS pims, BOOL fCreate, BOOL fModify,
    ULONG ulSeqNum, LPSTR *pszFull, PIMSG *ppimsg);
HRESULT HrSetFlags(PIMSG, ULONG, ULONG, ULONG); 
HRESULT NewIMSGInIATCH (LPMESSAGE lpmsg, POBJ pobj, ULONG ulFlags, PIMSG * ppimsg);
HRESULT InitIMSGProps(PIMSG pimsg);
void IMSG_Neuter (PIMSG);
HRESULT HrSetInternalProps(PLMR plmr, ULONG cprop, LPSPropValue *ppval,
    ULONG *pcval, PEID peid, PEID peidParent, ULONG ulSeqNum);

/*
 *  MSPATCH.C
 */

#undef  INTERFACE
#define INTERFACE struct _IATCH
    
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   MAPIMETHOD_DECLARE(type, method, IATCH_)
        MAPI_IUNKNOWN_METHODS(IMPL)
        MAPI_IMAPIPROP_METHODS(IMPL)
        MAPI_IATTACH_METHODS(IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   MAPIMETHOD_TYPEDEF(type, method, IATCH_)
        MAPI_IUNKNOWN_METHODS(IMPL)
        MAPI_IMAPIPROP_METHODS(IMPL)
        MAPI_IATTACH_METHODS(IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   STDMETHOD_(type, method)

DECLARE_MAPI_INTERFACE(IATCH_)
{
    MAPI_IUNKNOWN_METHODS(IMPL)
    MAPI_IMAPIPROP_METHODS(IMPL)
    MAPI_IATTACH_METHODS(IMPL)
};

extern IATCH_Vtbl   vtblIATCH;

struct _IATCH           /* Implementation of IAttach */
{
    IATCH_Vtbl *    lpVtbl; /* -> vtblIATCH */
    STANDARD_OBJECT_MEMBERS
    LPATTACH lpattach;
};

/* Exported functions */

HRESULT HrNewIATCH(LPATTACH lpattach, PIMSG pimsg, BOOL fModify,
    PIATCH * ppiatch);
void IATCH_Neuter (PIATCH piatch);

/*
 *  MSPGLE.C
 */

HRESULT MapScodeSz (SCODE scArg, PIMS pims, LPTSTR * lppszError);

/*
 *  MSPMISC.C
 */

/* length in chars of file extension including . (no NULL) */
#define CCH_EXT         4

/* length in chars of the base portion of a local name (no NULL) */
#define CCH_BASE        8

/* length in chars of a local name of a message or folder, including NULL */
#define CCH_NAME            (CCH_BASE + CCH_EXT + 1)

#define FOLDER_EXT      TEXT( ".fld" )  /* extension for folder directory names */
#define MESSAGE_EXT     TEXT( ".msg" )  /* File name extension for messages */
#define TEMP_EXT        TEXT( ".tmp" )  /* File name extension for messages */

/* Filename extension for read-receipt messages   */
#define READRECEIPT_EXT TEXT( ".rrt" )

SCODE ScAlloc(ULONG lcb, LPVOID *ppv);
SCODE ScAllocZ(ULONG lcb, LPVOID *ppv);
SCODE ScRealloc(ULONG lcb, LPVOID pvOrig, LPVOID * ppv);
void FreeNull(LPVOID pv);
SCODE LMAllocZ(PLMR plmr, ULONG lcb, LPVOID *ppv);
SCODE ScInitMSInstance(LPMALLOC lpmalloc);
void DeinitMSInstance(void);

#define HrAlloc(a,b)        ResultFromScode(ScAlloc((a), (b)))
#define HrAllocZ(a,b)       ResultFromScode(ScAllocZ((a), (b)))
#define HrRealloc(a,b,c)    ResultFromScode(ScRealloc((a), (b), (c)))

LPTSTR SzBaseName (PEID);

BOOL FCheckEIDType(PEID peid, LPSTR szExt);
BOOL FIsRoot (PEID peid);
BOOL FIsFolder (PEID peid);
BOOL FIsUnsavedMsg (PIMSG pimsg);
#define FIsMessage(_peid)       FCheckEIDType((_peid), MESSAGE_EXT)
#define FIsUnsavedEID(_peid)    FCheckEIDType((_peid), TEMP_EXT)

HRESULT HrDeconstructEID (PEID peid, LPMAPIUID * lppuid,
    LPTSTR * lppszPath, LPTSTR * lppszFile);
HRESULT HrAppendPath (LPTSTR szBase, LPTSTR szAppend, LPTSTR *
    lppszFullPath);
BOOL FAppendPathNoMem (LPTSTR szBase, LPTSTR szAppend,
    ULONG cchFullPath, LPTSTR szFullPath);
void ReplaceExt(LPTSTR szFile, LPTSTR szExt);
HRESULT HrConstructEID(LPMAPIUID lpuidStore, PLMR plmr, LPSTR szNewName,
    PEID *ppeidNew);
HRESULT HrGetParentEID (PLMR, PEID, PEID *);
HRESULT HrOpenParent(PIMS pims, PEID peid, ULONG ulFlags, PIFLD *ppifld);

void FreePropArrays (LPSPropValue *,
    LPSPropTagArray *, LPSPropAttrArray *);
HRESULT HrAllocPropArrays (ULONG, LPSPropValue *,
    LPSPropTagArray *, LPSPropAttrArray *);

HRESULT HrWrap_GetProps(HRESULT hr, PIMS pims, ULONG cvalInt,
    LPSPropValue pvalInt, ULONG * lpcValues, LPSPropValue * ppval,
    BOOL fStore, BOOL fTagsSpecified, POBJ pobj);

BOOL FIsSubmittedMessage(PIMS pims, PEID peid);

HRESULT HrOpenIMsgSession(LPMSGSESS *ppmsgsess);
HRESULT HrOpenIMsg(LPMSGSESS pmsgsess, LPSTR szFile, PLMR plmr, LPMAPISUP psup,
    BOOL fCreate, BOOL fModify, BOOL fExclusive, LPMESSAGE *lppmsg);

HRESULT HrSetOneROProp(LPMESSAGE lpmsg, PLMR plmr, ULONG ulPT, LPVOID pv);
HRESULT HrGetSingleProp(LPMAPIPROP pmprop, PLMR plmr, ULONG ulPT, LPVOID pv);
HRESULT HrSetSingleProp(LPMAPIPROP pmprop, PLMR plmr, ULONG ulPT, LPVOID pv);

BOOL FContainsProp(ULONG ulPropTag, LPSPropTagArray ptaga);


/*
 *  MSPROVIDER object.
 *  Returned by MSProviderInit() routine.
 *  One is created for each Session logged
 *  into this store provider on this process.
 */

#undef  INTERFACE
#define INTERFACE struct _MSP

#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   MAPIMETHOD_DECLARE(type, method, MSP_)
        MAPI_IUNKNOWN_METHODS(IMPL)
        MAPI_IMSPROVIDER_METHODS(IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   MAPIMETHOD_TYPEDEF(type, method, MSP_)
        MAPI_IUNKNOWN_METHODS(IMPL)
        MAPI_IMSPROVIDER_METHODS(IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   STDMETHOD_(type, method)

DECLARE_MAPI_INTERFACE(MSP_)
{
    MAPI_IUNKNOWN_METHODS(IMPL)
    MAPI_IMSPROVIDER_METHODS(IMPL)
};

extern MSP_Vtbl vtblMSP;

struct _MSP
{
    MSP_Vtbl *  lpVtbl;         /* -> vtblMSP */
    STANDARD_OBJECT_MEMBERS
    CRITICAL_SECTION_MEMBERS        /* Critical section (_WIN32 only) */
    HINSTANCE       hInst;          /* Instance handle */
    LMR             lmr;            /* Linked memory routines */
    IFDBG(BOOL      fInvalid;)      /* TRUE if invalid (DEBUG only) */
};

/*
 *  LOGON object.
 *  Returned from MSP_Logon().
 *  Called by MAPI.DLL.  Equivalent to the IMSGSTORE object
 *  returned on the same call but is used by MAPI instead of the client.
 */

#undef  INTERFACE
#define INTERFACE struct _MSL

#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   MAPIMETHOD_DECLARE(type, method, MSL_)
        MAPI_IUNKNOWN_METHODS(IMPL)
        MAPI_IMSLOGON_METHODS(IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   MAPIMETHOD_TYPEDEF(type, method, MSL_)
        MAPI_IUNKNOWN_METHODS(IMPL)
        MAPI_IMSLOGON_METHODS(IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   STDMETHOD_(type, method)

DECLARE_MAPI_INTERFACE(MSL_)
{
    MAPI_IUNKNOWN_METHODS(IMPL)
    MAPI_IMSLOGON_METHODS(IMPL)
};

extern MSL_Vtbl vtblMSL;
extern MAPIUID uidProvider;

struct _MSL
{
    MSL_Vtbl *      lpVtbl;     /* -> vtblMSL */
    STANDARD_OBJECT_MEMBERS
    CRITICAL_SECTION_MEMBERS        /* Critical section (_WIN32) */
    LMR                 lmr;        /* Linked memory routines */
    IFDBG(BOOL          fInvalid;)  /* TRUE if invalid (DEBUG only) */
};


/*
 *  MSPTBL.C
 */
 
HRESULT HrGetTableName(POBJ, LPSTR, LPSTR, LPSTR *);
HRESULT HrSyncOutgoingTable(LPTABLEDATA lptbl, PIMS pims);
HRESULT HrSyncContentsTable(PIFLD pifld, BOOL fWriteTable);
HRESULT HrReadTableFromDisk(LPTABLEDATA, POBJ, LPSTR, ULONG, LPSTR);
HRESULT HrWriteTableOnDisk(LPTABLEDATA, POBJ, LPSTR, LPSTR);

/*
 *  MSPNTFY.C
 */

HRESULT HrUpdateOutgoingQueue(PIMS pims, PIMSG pimsg, PEID peid,
    ULONG ulTableEvent);
HRESULT HrSetupPrivateNotifications(PIMS pims);
HRESULT HrNewOutgoingTableData(PIMS pims);
HRESULT HrCreateOGQueueMutex(HANDLE *phQMutex);

HRESULT HrSendNotif(PIMS pims, PEID peidParent, PEID peidObject,
    ULONG ulTableEvent, ULONG ulObjType);

