/*
 *  _ S M H . H
 *
 *  Sample mail handling hook
 *  Copyright 1992-95 Microsoft Corporation.  All Rights Reserved.
 */

/* RICHEDIT OLE callback object method definitions */
/* IRichEditOleCallback Interface --------------------------------------------- */

#define MAPI_IRICHEDITOLECALLBACK_METHODS(IPURE)                        \
    MAPIMETHOD(GetNewStorage)                                           \
        (THIS_  LPSTORAGE FAR * lppstg) IPURE;                          \
    MAPIMETHOD(GetInPlaceContext)                                       \
        (THIS_  LPOLEINPLACEFRAME FAR * ppipframe,                      \
                LPOLEINPLACEUIWINDOW FAR * ppipuiDoc,                   \
                LPOLEINPLACEFRAMEINFO pipfinfo) IPURE;                  \
    MAPIMETHOD(ShowContainerUI)                                         \
        (THIS_  BOOL fShow) IPURE;                                      \
    MAPIMETHOD(QueryInsertObject)                                       \
        (THIS_  LPCLSID pclsid,                                         \
                LPSTORAGE pstg,                                         \
                LONG cp) IPURE;                                         \
    MAPIMETHOD(DeleteObject)                                            \
        (THIS_  LPOLEOBJECT poleobj) IPURE;                             \
    MAPIMETHOD(QueryAcceptData)                                         \
        (THIS_  LPDATAOBJECT lpdataobj,                                 \
                CLIPFORMAT FAR * lpcfFormat,                            \
                DWORD reco,                                             \
                BOOL fReally,                                           \
                HGLOBAL hMetaPict) IPURE;                               \
    MAPIMETHOD(ContextSensitiveHelp)                                    \
        (THIS_  BOOL fEnterMode) IPURE;                                 \
    MAPIMETHOD(GetClipboardData)                                        \
        (THIS_  CHARRANGE FAR * lpchrg,                                 \
                DWORD reco,                                             \
                LPDATAOBJECT FAR * lppdataobj);                         \
    MAPIMETHOD(GetDragDropEffect)                                       \
        (THIS_  BOOL fDrag,                                             \
                DWORD grfKeyState,                                      \
                LPDWORD pdwEffect) IPURE;                               \
    MAPIMETHOD(GetContextMenu)                                          \
        (THIS_  WORD seltype,                                           \
                LPOLEOBJECT lpoleobj,                                   \
                CHARRANGE FAR * lpchrg,                                 \
                HMENU FAR * lphmenu) IPURE;                             \
                                                                        
/*
/*  Object Vtable definition and declairation
 */
#undef  INTERFACE
#define INTERFACE struct _REOC
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   MAPIMETHOD_DECLARE(type, method, REOC_)
        MAPI_IUNKNOWN_METHODS (IMPL)
        MAPI_IRICHEDITOLECALLBACK_METHODS (IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   MAPIMETHOD_TYPEDEF(type, method, REOC_)
        MAPI_IUNKNOWN_METHODS (IMPL)
        MAPI_IRICHEDITOLECALLBACK_METHODS (IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   STDMETHOD_(type, method)
DECLARE_MAPI_INTERFACE (REOC_)
{
    MAPI_IUNKNOWN_METHODS (IMPL)
    MAPI_IRICHEDITOLECALLBACK_METHODS (IMPL)
};


/*
 *  Object Vtable definition and declairation
 */
#undef  INTERFACE
#define INTERFACE struct _SMH
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   MAPIMETHOD_DECLARE(type, method, SMH_)
        MAPI_IUNKNOWN_METHODS (IMPL)
        MAPI_ISPOOLERHOOK_METHODS (IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   MAPIMETHOD_TYPEDEF(type, method, SMH_)
        MAPI_IUNKNOWN_METHODS (IMPL)
        MAPI_ISPOOLERHOOK_METHODS (IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   STDMETHOD_(type, method)
DECLARE_MAPI_INTERFACE (SMH_)
{
    MAPI_IUNKNOWN_METHODS (IMPL)
    MAPI_ISPOOLERHOOK_METHODS (IMPL)
};

/*
 *  Misc. Defines
 *
 *  GROW_SIZE is the incremental amount to grow buffers that hold arrays
 *  of structures.  This is used to reduce the number of allocations in
 *  certain situations (ie. configuration)
 */
#define GROW_SIZE   4

/*
 *  cStoMax is the maximum number of stores per profile supported by SMH.
 *  This limit is purely an imposed limit and can be increased or
 *  decreased with no other changes required.
 */
#define cStoMax     64

/*
 *  cchNameMax is used to limit the names and values of filters.
 */
#define cchNameMax  MAX_PATH

/*
 *  Store table structure definitions
 *
 *  STOENTRY
 *      This structure is used as a part of the STOTABLE structure.
 *      The union component to the structure allows SMH to cast an
 *      LPSPropValue pointer to a LPSTOENTRY where the first property
 *      is dropped in favor of storing an LPMDB.
 *
 *  STO
 *      This stucture is defined such that SMH can cast an SRow pointer
 *      to an LPSTO.  Again, this construct is used extensively by the
 *      STOTABLE implementation.
 *
 *  STOTABLE
 *      This stucture can be mapped to an SRowSet.  The store table
 *      implementation uses this to let MAPI allocate the memory needed
 *      for keeping pointers to open stores.
 */
typedef struct _STOENTRY
{
    union
    {
        LPMDB           lpmdb;
        SPropValue      valPad;
    };
    SPropValue          lpProps[];

} STOENTRY, FAR * LPSTOENTRY;

typedef struct _STO
{
    ULONG               ulReserved;
    ULONG               cValues;
    union
    {
        LPSTOENTRY      lpstoe;
        LPSPropValue    lpProps;
    };

} STO, FAR * LPSTO;

typedef struct _STOTABLE
{
    ULONG               cSto;
    STO                 aSto[cStoMax];

} STOTABLE, FAR * LPSTOTABLE;


/*
 *  Archive bucket structures definitions
 *
 *  DFT
 *      The DFT structure contains two FILETIMEs that define the delta of
 *      time supported by the archive folder.
 *
 *  BKIT
 *      The BKIT structure contains all the information required to
 *      process the archival of a message into that bucket.
 *
 *      The EntryID of the parent folder, the year folder, and the
 *      monthly folder are all cashed as is the MAPIFOLDER object.  The
 *      DFT for the year and month are cached as well.
 */
typedef struct _DFT
{
    FILETIME            ftStart;
    FILETIME            ftEnd;

} DFT, FAR * LPDFT;

typedef struct _BKIT
{
    ULONG               cbeid;
    LPENTRYID           lpeid;
    LPMAPIFOLDER        lpfldr;
    DFT                 dft;

    ULONG               cbeidYr;
    LPENTRYID           lpeidYr;
    LPMAPIFOLDER        lpfldrYr;
    DFT                 dftYr;

    ULONG               cbeidParent;
    LPENTRYID           lpeidParent;
    LPMAPIFOLDER        lpfldrParent;

} BKIT, FAR * LPBKIT;


/*
 *  SMH stucture definitions
 *  
 *  WB
 *      The WB (wastebasket) structure contains the information
 *      required to archive deleted mail on any given message store
 *  
 *  RULE
 *      The RULE structure contains the information required to filter an
 *      inbound message into the desired target folder
 *  
 *  OOF
 *      The OOF structure contains the information required to generate
 *      out-of-office responses to incoming messages
 *  
 *  SMH
 *      The SMH object is supports the ISpoolerHook interface and is the
 *      object handed to mapi to facilitate all message filtering.
 *  
 */
typedef struct _WB
{
    struct _WB FAR *    wbNext;         /* next pointer */
    struct _SMH FAR *   lpsmh;          /* owning SMH object */

    LPMDB               lpmdb;          /* MDB on which this WB applies */
    LPMAPITABLE         lptbl;          /* contents table of the wastebasket */
    LPMAPIFOLDER        lpfldr;         /* folder object of the wastebasket */
    LPSPropValue        lpvalEid;       /* entryid of the wastebasket */
    ULONG               ulAdvz;         /* connection ID returned from Advise() */
    BKIT                bkit;           /* bucket cache for this WB */
    HANDLE              ht;             /* filtering thread */
    BOOL                fBail;          /* bailout flag */

} WB, FAR * LPWB;

typedef struct _RULE
{
    struct _RULE FAR *  rlNext;         /* next pointer */

    MAPIUID             muid;           /* profile section UID */
    UINT                rlTyp;          /* rule type */
    ULONG               ulFlags;        /* rule attributes */
    SRestriction FAR *  lpres;          /* recipient rule restriction */
    LPTSTR              lpszData;       /* value to filter against */
    LPTSTR              rgszSnd[3];     /* sound to play */
    LPMDB               lpmdb;          /* MDB owning the target folder */
    LPMAPIFOLDER        lpfldr;         /* target folder for filter */
    LPSPropValue        lpvalEid;       /* entryid of target folder */
    LPTSTR              lpszAnno;       /* auto-response annotation */
    LPBYTE              lpbRTF;         /* auto-response RTF */
    ULONG               cbRTF;          /* auto-response RTF size */
    ULONG               cvalRecip;      /* auto-response recip prop count */
    LPSPropValue        lpvalRecip;     /* auto-response recip */
    BKIT                bkit;           /* bucket cache for rule */

} RULE, FAR * LPRULE;

typedef struct _OOF
{
    LPTABLEDATA         lptad;          /* Table data object */
    LPMAPITABLE         lptbl;          /* Table data view */
    ULONG               cRecips;        /* Count of recips */
    LPTSTR              lpszBody;       /* Oof Body Text */
    LPBYTE              lpbRTF;         /* Body RTF */
    ULONG               cbRTF;          /* RTF size */

} OOF, FAR * LPOOF;

typedef struct _SMH
{
    SMH_Vtbl FAR *      lpVtbl;
    ULONG               lcInit;         /* object refcount */
    HINSTANCE           hinst;          /* DLL instance */
    HANDLE              hevtCfg;        /* configuration event */

    LPMAPISESSION       lpsess;         /* client session */
    LPALLOCATEBUFFER    lpfnAlloc;      /* MAPIAllocateBuffer */
    LPALLOCATEMORE      lpfnAllocMore;  /* MAPIAllocateMore */
    LPFREEBUFFER        lpfnFree;       /* MAPIFreeBuffer */
    MAPIUID             muid;           /* hook provider section UID */

    unsigned int        fCatSm:1;       /* options flags */
    unsigned int        fCatSmByYr:1;
    unsigned int        fCatWb:1;
    unsigned int        fOof:1;
    unsigned int        fAtp:1;
    LPSTOTABLE          lpstotbl;       /* store table */
    SPropValue          valEx;          /* msg class exclustions */
    LPWB                lstWb;          /* list pointer of WBs */
    LPRULE              lstRl;          /* list pointer of rules */
    BKIT                bkitSm;         /* bucket cache for sent mail */
    OOF                 oof;            /* OOF information */

} SMH, FAR * LPSMH;

/*
 *  Configuration dialog structure definition
 *  
 *  REOC
 *      The Richedit OLE Callback structure refers to an object that is
 *      used by the configuration dialogs that support RTF edit controls
 *  
 *  SCD (SMH Configuration Dialog)
 *      The SMH Configuration Dialog structure is used to pass
 *      important information in and out of the configuration dialogs
 *      and property sheets.
 */
typedef struct _SCD
{
    HINSTANCE           hinst;          /* DLL instance */
    HWND                hwnd;           /* parent window */

    LPALLOCATEBUFFER    lpfnAlloc;      /* MAPIAllocateBuffer */
    LPALLOCATEMORE      lpfnAllocMore;  /* MAPIAllocateMore */
    LPFREEBUFFER        lpfnFree;       /* MAPIFreeBuffer */
    LPMALLOC            lpmalloc;       /* pointer to LPMALLOC obj */
    LPMAPISUP           lpsup;          /* pointer to support obj */
    LPPROVIDERADMIN     lpadmin;        /* pointer to profile admin obj */
    LPPROFSECT          lpsec;          /* profile section obj */

    LPMAPISESSION       lpsess;         /* session pointer used in filters */

    TCHAR               rgch[cchNameMax];
    LPSPropValue        lpval;          /* current set of property values */

    UINT                crl;            /* count of current rules */
    UINT                crlMax;         /* count of maximum rules */
    LPTSTR FAR *        lppsz;          /* pointer to array of names */
    LPSBinary           lpbin;          /* pointer to array of muids */

    ULONG               ulFlags;        /* configuration flags */
    SCODE               sc;             /* dialog failure error code */

} SCD, FAR * LPSCD;

typedef struct _FORMATBAR
{
    LPSCD               lpscd;          /* owning config dialog */
    CHARFORMAT          cf;             /* character format */
    HBRUSH              hbrBtnFace;     /* button face color brush */
    HDC                 hdc;            /* device context */
    HMENU               hmnuColor;      /* color picker menu */
    HWND                hwndEdit;       /* associated edit control */
    HWND                hwndFont;       /* font name combo */
    HWND                hwndFrame;      /* toolbar HWND */
    HWND                hwndSize;       /* font size combo */
    HWND                hwndTb;         /* toolbar */
    HANDLE              hfnt;           /* toolbar font */
    PARAFORMAT          pf;             /* paragraph format */
    UINT                cSize;          /* font entry count */
    WNDPROC             lpfnToolbar;    /* subclassed toolbar proc */
    struct _REOC FAR *  lpreoc;         /* richedit ole callback */

} FORMATBAR, FAR * LPFORMATBAR;

typedef struct _REOC
{
    REOC_Vtbl FAR *     lpVtbl;
    ULONG               lcInit;         /* object refcount */
    LPSTORAGE           lpstg;          /* root storage obj */
    UINT                cSub;           /* count of sub obj's */
    LPALLOCATEBUFFER    lpfnAlloc;      /* MAPIAllocateBuffer */
    LPALLOCATEMORE      lpfnAllocMore;  /* MAPIAllocateMore */
    LPFREEBUFFER        lpfnFree;       /* MAPIFreeBuffer */
    LPFORMATBAR         lpfb;           /* formatting bar */

} REOC, FAR * LPREOC;

typedef struct _RTFS
{
    LPALLOCATEBUFFER    lpfnAlloc;      /* MAPIAllocateBuffer */
    LPFREEBUFFER        lpfnFree;       /* MAPIFreeBuffer */
    LPBYTE              lpb;            /* stream data */
    LONG                cb;             /* stream data size */
    LONG                cbMax;          /* max stream size */
    
} RTFS, FAR * LPRTFS;

/*
 *  SMH proptags
 */
#define PR_SMH_FLAGS                    PROP_TAG(PT_LONG,       0x6600)
#define PR_SMH_RULES                    PROP_TAG(PT_MV_BINARY,  0x6601)
#define PR_SMH_EXCLUSIONS               PROP_TAG(PT_MV_TSTRING, 0x6602)
#define PR_SMH_EXCLUSIONS_A             PROP_TAG(PT_MV_STRING8, 0x6602)
#define PR_SMH_EXCLUSIONS_W             PROP_TAG(PT_MV_UNICODE, 0x6602)
#define PR_SMH_RULE_NAMES               PROP_TAG(PT_MV_TSTRING, 0x6603)
#define PR_SMH_RULE_NAMES_A             PROP_TAG(PT_MV_STRING8, 0x6603)
#define PR_SMH_RULE_NAMES_W             PROP_TAG(PT_MV_UNICODE, 0x6603)
#define PR_SMH_OOF_ENABLED              PROP_TAG(PT_BOOLEAN,    0x6604)
#define PR_SMH_OOF_TEXT                 PROP_TAG(PT_TSTRING,    0x6605)
#define PR_SMH_OOF_TEXT_A               PROP_TAG(PT_STRING8,    0x6605)
#define PR_SMH_OOF_TEXT_W               PROP_TAG(PT_UNICODE,    0x6605)
#define PR_SMH_OOF_RTF                  PROP_TAG(PT_BINARY,     0x6606)
#define PR_SMH_SOUND_SCHEMES            PROP_TAG(PT_MV_BINARY,  0x6607)
#define PR_SMH_REPFWD_SCHEMES           PROP_TAG(PT_MV_BINARY,  0x6608)

/*
 *  Value for PR_SMH_VERSION
 */
#define MAKE_SMH_VERSION(_mj,_mn)       (((ULONG)(0x0000FFFF & _mj) << 16) | \
                                            (ULONG)(0x0000FFFF & _mn))
#define SMH_VERSION                     MAKE_SMH_VERSION (1,0)

/*
 *  Values for PR_SMH_FLAGS
 */
#define SMH_ADD_TO_PAB                  ((ULONG)0x00000001)
#define SMH_FILTER_DELETED              ((ULONG)0x00000010)
#define SMH_FILTER_DELETED_YR           ((ULONG)0x00000020)
#define SMH_FILTER_INBOUND              ((ULONG)0x00000100)
#define SMH_FILTER_SENTMAIL             ((ULONG)0x00001000)
#define SMH_FILTER_SENTMAIL_YR          ((ULONG)0x00002000)
#define SMH_UNREAD_VIEWER               ((ULONG)0x00010000)

/*
 *  Filtering rule proptags
 */
#define PR_RULE_TYPE                    PROP_TAG(PT_LONG,       0x6610)
#define PR_RULE_DATA                    PROP_TAG(PT_BINARY,     0x6611)
#define PR_RULE_FLAGS                   PROP_TAG(PT_LONG,       0x6612)
#define PR_RULE_TARGET_ENTRYID          PROP_TAG(PT_BINARY,     0x6613)
#define PR_RULE_TARGET_PATH             PROP_TAG(PT_TSTRING,    0x6614)
#define PR_RULE_TARGET_PATH_A           PROP_TAG(PT_STRING8,    0x6614)
#define PR_RULE_TARGET_PATH_W           PROP_TAG(PT_UNICODE,    0x6614)
#define PR_RULE_STORE_ENTRYID           PROP_TAG(PT_BINARY,     0x6615)
#define PR_RULE_STORE_DISPLAY_NAME      PROP_TAG(PT_TSTRING,    0x6616)
#define PR_RULE_STORE_DISPLAY_NAME_A    PROP_TAG(PT_STRING8,    0x6616)
#define PR_RULE_STORE_DISPLAY_NAME_W    PROP_TAG(PT_UNICODE,    0x6616)
#define PR_RULE_SOUND_NORMAL            PROP_TAG(PT_TSTRING,    0x6617)
#define PR_RULE_SOUND_NORMAL_A          PROP_TAG(PT_STRING8,    0x6617)
#define PR_RULE_SOUND_NORMAL_W          PROP_TAG(PT_UNICODE,    0x6617)
#define PR_RULE_SOUND_HIPRI             PROP_TAG(PT_TSTRING,    0x6618)
#define PR_RULE_SOUND_HIPRI_A           PROP_TAG(PT_STRING8,    0x6618)
#define PR_RULE_SOUND_HIPRI_W           PROP_TAG(PT_UNICODE,    0x6618)
#define PR_RULE_SOUND_LOPRI             PROP_TAG(PT_TSTRING,    0x6619)
#define PR_RULE_SOUND_LOPRI_A           PROP_TAG(PT_STRING8,    0x6619)
#define PR_RULE_SOUND_LOPRI_W           PROP_TAG(PT_UNICODE,    0x6619)

#define PR_RULE_FORWARD_RECIP           PROP_TAG(PT_TSTRING,    0x6620)
#define PR_RULE_FORWARD_RECIP_A         PROP_TAG(PT_STRING8,    0x6620)
#define PR_RULE_FORWARD_RECIP_W         PROP_TAG(PT_UNICODE,    0x6620)
#define PR_RULE_FORWARD_RECIP_ENTRYID   PROP_TAG(PT_BINARY,     0x6621)
#define PR_RULE_REP_FWD_TEXT            PROP_TAG(PT_TSTRING,    0x6624)
#define PR_RULE_REP_FWD_TEXT_A          PROP_TAG(PT_STRING8,    0x6624)
#define PR_RULE_REP_FWD_TEXT_W          PROP_TAG(PT_UNICODE,    0x6624)
#define PR_RULE_REP_FWD_RTF             PROP_TAG(PT_BINARY,     0x6625)

/*
 *  Values for PR_RULE_TYPE
 */
#define RL_ANY_RECIP                    ((UINT)0x0001)
#define RL_BCC_RECIP                    ((UINT)0x0002)
#define RL_BODY                         ((UINT)0x0003)
#define RL_CC_RECIP                     ((UINT)0x0004)
#define RL_HAS_ATTACH                   ((UINT)0x0005)
#define RL_MSG_CLASS                    ((UINT)0x0006)
#define RL_SENDER                       ((UINT)0x0007)
#define RL_SUBJECT                      ((UINT)0x0008)
#define RL_TO_RECIP                     ((UINT)0x0009)
#define RL_TYPE_MAX                     ((UINT)0x0010)

/*
 *  Values for PR_RULE_FLAGS
 */
#define RULE_ARCHIVED                   ((ULONG)0x00000001)
#define RULE_ARCHIVED_BY_YEAR           ((ULONG)0x00000002)
#define RULE_NOT                        ((ULONG)0x00000004)
#define RULE_DELETE                     ((ULONG)0x00000008)
#define RULE_AUTO_RESPONSE              ((ULONG)0x00000010)
#define RULE_AUTO_REPLY                 ((ULONG)0x00000020)
#define RULE_AUTO_FORWARD               ((ULONG)0x00000040)
#define RULE_AUTO_APPEND_ORIG           ((ULONG)0x00000080)
#define RULE_PLAY_SOUNDS                ((ULONG)0x00000100)
#define RULE_NO_MOVE                    ((ULONG)0x10000000)
#define RULE_TERMINAL                   ((ULONG)0x80000000)

/*
 *  Rule configuration flags
 */
#define NEW_RULE                        ((UINT)1)
#define EDIT_RULE                       ((UINT)2)

/* Logon properties */

enum {
    ipProfile,
    ipFlags,
    ipRules,
    ipNames,
    ipOof,
    ipOofEnabled,
    ipOofRtf,
    ipSounds,
    ipRepFwd,
    ipExc,
    cpMax
};

/* Rule properties */

enum {
    ipRLDisp,
    ipRLType,
    ipRLData,
    ipRLFlags,
    ipRLEid,
    ipRLPath,
    ipRLSEid,
    ipRLStore,
    ipRLLoPri,
    ipRLSound,
    ipRLHiPri,
    ipRLFwdRecip,
    ipRLFwdEid,
    ipRLRepFwdRTF,
    ipRLRepFwd,
    cpRLMax
};

enum {
    isndLo,         /*  IMPORTANCE_LOW      */
    isndNorm,       /*  IMPORTANCE_NORMAL   */
    isndHi,         /*  IMPORTANCE_HIGH     */
    csndMax
};

/* Message properties */

enum {
    ipMsgFlgs,
    ipMsgSubj,
    ipMsgSentRep,
    ipMsgSentRepEA,
    ipPriority,
    cpMsgPrps
};

/* Recipient restriction enums */

enum {ivRecip, ivEmail, ivDispNm, cvMax };
enum {iresAnd, iresRecip, iresOr, iresEmail, iresDispNm, cresMax };


/*
 *  Configuration dialogs
 */

typedef HRESULT (STDMETHODCALLTYPE FAR * LPOPENPROFSECT) (
    LPVOID              lpvOPSCtxt,
    LPMAPIUID           lpUID,
    LPCIID              lpInterface,
    ULONG               ulFlags,
    LPPROFSECT FAR *    lppProfSect);

HRESULT
HrUpdateProfileFormat (LPVOID lpvOPSCtxt,
    LPOPENPROFSECT lpfnOpenProfSect,
    LPALLOCATEMORE lpfnMore,
    LPFREEBUFFER lpfnFree,
    LPSPropValue lpvalNew,
    LPSPropValue lpvalOld);

extern LPVOID lpCtl3D;
#if 0
#if !defined (_WIN95)
#define RegDlg3D(_inst)         Ctl3dRegister (_inst);
#define MakeDlg3D(_dlg)         Ctl3dSubclassDlgEx(_dlg, CTL3D_ALL)
#define UnregDlg3D(_inst)       Ctl3dUnregister (_inst);
#else
#define RegDlg3D(_inst)
#define MakeDlg3D(_dlg)
#define UnregDlg3D(_inst)
#endif
#endif

#ifdef  WIN32
#define FWin4Shell()    ((GetVersion() & 0x000000FF) >= 0x04)
#else
#define FWin4Shell()    (FALSE)
#endif

#define FHandleWm(_fn,_dlg,_wm,_wp,_lp) HANDLE_WM_##_wm(_dlg,_wp,_lp,_fn##_##_wm)
HRESULT HrDisplayPropSheets (HINSTANCE hinst, HWND hwnd, LPSCD lpscd);
STDMETHODIMP_(SCODE) ScCreateToolbar (LPSCD lpscd, HWND hwnd, UINT idPeg, BOOL fPropsheet, LPFORMATBAR FAR *);
STDMETHODIMP_(BOOL) EXPORT FDoRTFCommand (HWND hctrl, UINT id, UINT command);
void UpdateFormatBar (HWND hdlg);

SCODE ScExportFilters (LPSCD lpscd, HWND hwnd);
SCODE ScImportFilters (LPSCD lpscd, HWND hwnd, HWND hctrl);

DWORD CALLBACK WriteRTFToBuffer (DWORD dwCookie, LPBYTE lpb, LONG cb, LONG FAR * lpcb);
DWORD CALLBACK ReadRTFFromBuffer (DWORD dwCookie, LPBYTE lpb, LONG cb, LONG FAR * lpcb);

HRESULT HrInitOof (LPSMH lpsmh, LPSPropValue lpvalAnno, LPSPropValue lpvalRTF);


/*
 *  Configuration Events
 */
#ifdef  _WIN32
HRESULT HrGetConfigEvent (HANDLE FAR *);
VOID SignalConfigChanged (VOID);
BOOL FConfigChanged (HANDLE);
#endif

/*
 *  FLpszContainsLpsz()
 *
 *  Purpose:
 *
 *      Finds the given sub-string in the passed in string.
 *
 *  Arguments:
 *
 *      _s  source string
 *      _p  pattern string
 *
 *  Returns:
 *
 *      FALSE iff the string was not found, TRUE otherwise.
 */
#define FLpszContainsLpsz(_s,_p) FRKFindSubpsz(_s,lstrlen(_s),_p,lstrlen(_p),FL_IGNORECASE)


/*
 *  Message Archive Functions
 */
HRESULT
HrArchiveMessage (LPSMH lpsmh,
    LPMESSAGE lpmsg,
    LPMAPIFOLDER lpfldrDef,
    LPMDB lpmdbDef,
    LPBKIT lpbkit,
    BOOL fCatByYear,
    ULONG FAR * lpcbeid,
    LPBYTE FAR * lppeid);

HRESULT
HrArchiveByDate (LPSMH lpsmh,
    FILETIME FAR * lpft,
    LPMAPIFOLDER lpfldrDef,
    LPMDB lpmdbDef,
    LPBKIT lpbkit,
    BOOL fCatByYear,
    ULONG cbeid,
    LPBYTE lpeid);


HRESULT HrInitDeletedMailFilter (LPSMH lpsmh);

BOOL
FRKFindSubpsz (LPSTR pszTarget,
    ULONG cbTarget,
    LPSTR pszPattern,
    ULONG cbPattern,
    ULONG ulFuzzyLevel);

/*
 *  Stores table
 */
HRESULT HrInitStoresTable (LPSMH, LPMAPISESSION);
HRESULT HrOpenMdbFromEid (LPSMH, ULONG, LPENTRYID, LPMDB FAR *);
HRESULT HrOpenMdbFromName (LPSMH, LPTSTR, LPMDB FAR *);
HRESULT HrOpenStoEntry (LPMAPISESSION, LPSTO, LPMDB FAR *);
VOID ReleaseStoresTable (LPSMH);


/*
 *  Automated Response Functions
 */
HRESULT HrGenerateResponse (LPSMH lpsmf, LPRULE lprl, LPMAPIFOLDER lpfldr, LPMESSAGE lpmsg);
VOID ReleaseOof (LPOOF lpoof);


/*
 *  Automated PAB additions
 */
HRESULT HrAddEntriesToPab (LPSMH, LPMESSAGE);


/*
 *  RTF\Richedit Components
 */
#ifdef  _WIN32
#define RICHEDIT_LIB    "RICHED32.DLL"
#else
#define RICHEDIT_LIB    "RICHED.DLL"
#endif

STDMETHODIMP_(SCODE)
ScNewRicheditCallback (LPFORMATBAR lpfb,
    LPALLOCATEBUFFER lpfnAlloc,
    LPALLOCATEMORE lpfnMore,
    LPFREEBUFFER lpfnFree,
    LPREOC FAR * lppreoc);

/*
 *  WM_NOTIFY #defines (taken from WINUSER.H)
 */
#ifdef  WIN16
#define WM_NOTIFY   0x004E
#define HANDLE_WM_NOTIFY(hwnd,wParam,lParam,fn) (fn)((hwnd),(int)(wParam),(NMHDR FAR*)(lParam))

/*
 *  Mapped bitmapi #defines (taken from COMMCTRL.H)
 */
typedef struct
{
    COLORREF from;
    COLORREF to;
} COLORMAP, FAR * LPCOLORMAP;

/*
 *  Toolbar button #defines (taken from COMMCTRL.H)
 */
typedef struct _TBBUTTON {
    int iBitmap;
    int idCommand;
    BYTE fsState;
    BYTE fsStyle;
    BYTE bReserved[2];
    DWORD dwData;
    int iString;
} TBBUTTON, NEAR* PTBBUTTON, FAR* LPTBBUTTON;
typedef const TBBUTTON FAR* LPCTBBUTTON;
#define TBSTATE_ENABLED         0x04
#define TBSTYLE_BUTTON          0x00
#define TBSTYLE_SEP             0x01
#define TBSTYLE_CHECK           0x02
#define TB_CHECKBUTTON      (WM_USER + 2)
#define TB_GETITEMRECT      (WM_USER + 29)
#define CCS_TOP         0x00000001L

WINCOMMCTRLAPI HWND WINAPI CreateToolbarEx (HWND hwnd, DWORD ws, UINT wID, int nBitmaps,
    HINSTANCE hBMInst, UINT wBMID, LPCTBBUTTON lpButtons,
    int iNumButtons, int dxButton, int dyButton,
    int dxBitmap, int dyBitmap, UINT uStructSize);

HBITMAP WINAPI CreateMappedBitmap (HINSTANCE hInstance, INT idBitmap, BOOL bDiscardable,
    LPCOLORMAP lpColorMap, INT iNumMaps);
#endif  /* WIN16 */
