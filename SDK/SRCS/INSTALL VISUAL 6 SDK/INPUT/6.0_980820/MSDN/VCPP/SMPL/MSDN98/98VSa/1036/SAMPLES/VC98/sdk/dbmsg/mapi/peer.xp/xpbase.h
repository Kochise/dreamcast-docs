/*
 -  X P B A S E . H
 -
 *
 *  Definitions, typedefs and prototypes used by the Sample Transport
 *  Provider modules.
 *
 *  Copyright 1992-1995 Microsoft Corporation.  All Rights Reserved.
 */

/* Make sure that we are thinking "C" here... */
#ifdef __cplusplus
extern "C"
{
#endif


/*
 *  Linked-List of deferred messages
 */

typedef struct _DEFMSG *LPDEFMSG;

typedef struct _DEFMSG
{
    ULONG ulMsgRef;
    SBinary sbinEIDDef;
    LPDEFMSG lpNext;

} DEFMSG;

/*
 *  Sample Transport Provider DLL exported entry points.
 */

/* Transport Init Object */

#undef  INTERFACE
#define INTERFACE struct _XPP

#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   MAPIMETHOD_DECLARE(type, method, XPP_)
        MAPI_IUNKNOWN_METHODS(IMPL)
        MAPI_IXPPROVIDER_METHODS(IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   STDMETHOD_(type, method)

DECLARE_MAPI_INTERFACE(XPP_)
{
    MAPI_IUNKNOWN_METHODS(IMPL)
    MAPI_IXPPROVIDER_METHODS(IMPL)
};

typedef struct _XPP {
    XPP_Vtbl FAR *      lpVtbl;         /* Methods                          */
    LONG                lcInit;         /* Usage Count                      */
    struct _XPP FAR *   lpxppMyAddress; /* Pointer to myself, for validation*/
    CRITICAL_SECTION    csTransport;    /* Critical section for this object */
    struct _XPL FAR *   XPSessionList;  /* List of logon sessions on obj    */
    BOOL                fInited;        /* Are we in an inited state?       */
    HINSTANCE           hInst;          /* Instance of our library          */
    LPMALLOC            lpMalloc;       /* IMalloc object                   */
    LPFREEBUFFER        lpFreeBuffer;   /* Need this to free the object     */
} XPP, FAR *LPXPP;

/* Transport Logon Object */

#undef  INTERFACE
#define INTERFACE struct _XPL

#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   MAPIMETHOD_DECLARE(type, method, XPL_)
        MAPI_IUNKNOWN_METHODS(IMPL)
        MAPI_IXPLOGON_METHODS(IMPL)
#undef  MAPIMETHOD_
#define MAPIMETHOD_(type, method)   STDMETHOD_(type, method)

DECLARE_MAPI_INTERFACE(XPL_)
{
    MAPI_IUNKNOWN_METHODS(IMPL)
    MAPI_IXPLOGON_METHODS(IMPL)
};

/*
 *  Logon object structure.
 */

typedef struct _XPL
{
    XPL_Vtbl FAR *      lpVtbl;             /* Methods                                  */
    LONG                lcInit;             /* Usage Count                              */
    struct _XPL FAR *   lpNextSession;      /* Link to next session                 */
    struct _XPL FAR *   lpMySession;        /* My address, used to validate         */
    LPXPP               lpxppParent;        /* Parent XPP object                        */
    LPMAPISTATUS        lpXPStatus;         /* Child Status Object                      */
    ULONG               ulSessionFlags;     /* Session flags                            */
    LPMAPISUP           lpMAPISup;          /* Support object for this session          */
    LPALLOCATEBUFFER    AllocateBuffer;     /* MAPIAllocateBuffer pointer           */
    LPALLOCATEMORE      AllocateMore;       /* MAPIAllocateMore pointer             */
    LPFREEBUFFER        FreeBuffer;         /* MAPIFreeBuffer function pointer          */
    ULONG               cLogonPropValues;   /* Number of Logon property values          */
    LPSPropValue        lpPropArray;        /* Logon property array                     */
    LPSPropValue        lpMyIDArray;        /* Properties to set on transmit            */
    ULONG               cOptData;           /* Number of Options we support             */
    LPOPTIONDATA        lpOptData;          /* Per-Message & Recip OptionData           */
    LPTSTR              lpszAdrType;        /* Used to pass back on AddressType call    */
    ULONG               ulTransportStatus;  /* Howzit going? Used by status             */
    ULONG               ulResourceMethods;  /* Methods supported by our status object   */
    
    /* Deferred message handling elements */
    ULONG               ulDeferredMsgRef;
    BOOL                fResendDeferred;
    LPDEFMSG            lpDeferredList;
    
    BOOL                fRefSupport;        /* We AddRef'd the support object */
    BOOL                fFoundInMessage;    /* Found a inbound message flag   */
    HANDLE              hInFindHandle;      /* Used in Poll(), StartMessage() */
    WIN32_FIND_DATA     wfdInFindData;      /* Used in Poll(), StartMessage() */
    HANDLE              hOutFindHandle;     /* Used in Outbound Queue         */
    WIN32_FIND_DATA     wfdOutFindData;     /* Used in Outbound Queue         */
} XPL, FAR *LPXPL;

/*
 *  Properties we store in the Profile.
 *
 * NOTE!!! THE ORDERING OF THE PROPERTY ID'S HERE MUST BE THE SAME
 * AS THE ORDERING OF PROP TAG ARRAY sptLogonArray IN SMPLXPT.C, WITH
 * SEQUENTIAL NUMBERING!!!!
 *
 */

#define BASE_PROVIDER_ID    0x6600  /* From MAPITAGS.H comments */
#define BASE_MSG_OPT_ID     0x4000  /* From MAPITAGS.H comments */
#define BASE_RECIP_OPT_ID   0x5800  /* From MAPITAGS.H comments */

/* Display name of user. Optional property. If not present we will use
   the email address as the display name -- ugly but effective.            */

#define PR_SAMPLE_DISPLAY_NAME      PROP_TAG (PT_TSTRING,   (BASE_PROVIDER_ID + 0x0001))

/* Address type of sample transport. This will be used to construct inbound
   and outbound addresses where needed. It also will be used to tell the
   Spooler what address types we should get.                               */

#define PR_SAMPLE_EMAIL_ADDR_TYPE   PROP_TAG (PT_TSTRING,   (BASE_PROVIDER_ID + 0x0002))

/* Email address. This will usually be the same as the inbound directory,
   although this may tend to have a more canonical form for remote access. */

#define PR_SAMPLE_EMAIL_ADDRESS     PROP_TAG (PT_TSTRING,   (BASE_PROVIDER_ID + 0x0003))

/* Inbound directory. This is where the transport will look in order to
   determine whether it has received any mail.                             */

#define PR_SAMPLE_INBOUND_DIR       PROP_TAG (PT_TSTRING,   (BASE_PROVIDER_ID + 0x0004))

/* Outbound directory. The transport will store its message files here
   while it is in the process of sending them. The presence of a file
   in this directory implies that the transport still has work to do.      */

#define PR_SAMPLE_OUTBOUND_DIR      PROP_TAG (PT_TSTRING,   (BASE_PROVIDER_ID + 0x0005))

/* Filename. This is an 8-character root for use by mail-enabled or
   workgroup applications to build a complete file specification (by
   adding an extension) for data they wish to store for this user.         */

#define PR_SAMPLE_FILENAME          PROP_TAG (PT_TSTRING,   (BASE_PROVIDER_ID + 0x0006))

/* Directory. This is a directory in which workgroup applications may
   wish to store their files pertaining to this user.                      */

#define PR_SAMPLE_DIRECTORY         PROP_TAG (PT_TSTRING,   (BASE_PROVIDER_ID + 0x0007))

/* Flags. Contain various options for this transport provider.             */

#define PR_SAMPLE_FLAGS             PROP_TAG (PT_LONG,      (BASE_PROVIDER_ID + 0x0008))

#define PR_SAMPLE_FLAG_PEER_TO_PEER ((ULONG) 0x00000001)
#define PR_SAMPLE_FLAG_UI_ALWAYS    ((ULONG) 0x00000002)
#define PR_SAMPLE_FLAG_LOG_EVENTS   ((ULONG) 0x00000004)
#define PR_SAMPLE_FLAG_SAVE_DATA    ((ULONG) 0x00000008)

/* Logfile. This is where logging information will be written. If this
   property is not present, we will use (PR_SAMPLE_FILENAME)".LOG"         */

#define PR_SAMPLE_LOGFILE           PROP_TAG (PT_TSTRING,   (BASE_PROVIDER_ID + 0x0009))

/* Logfile high water mark. This is the point at which the log writer will
   truncate the logfile so as not to fill up the disk.                     */

#define PR_SAMPLE_LOGHIGHWATER      PROP_TAG (PT_LONG,      (BASE_PROVIDER_ID + 0x000A))

/* Logfile low water mark. This is the approximate size that the logfile
   writer will truncate the logfile to (modulo a line ending).             */

#define PR_SAMPLE_LOGLOWWATER       PROP_TAG (PT_LONG,      (BASE_PROVIDER_ID + 0x000B))

/* The following property tags are temporaries. They are here because
   the configuration property sheets want one property tag for every
   control; after we run the dialogs, we roll them back up into
   PR_SAMPLE_FLAGS.                                                        */

#define PR_TEMP_PEER_TO_PEER        PROP_TAG (PT_BOOLEAN,   (BASE_PROVIDER_ID + 0x000C))
#define PR_TEMP_UI_ALWAYS           PROP_TAG (PT_BOOLEAN,   (BASE_PROVIDER_ID + 0x000D))
#define PR_TEMP_LOG_EVENTS          PROP_TAG (PT_BOOLEAN,   (BASE_PROVIDER_ID + 0x000E))
#define PR_TEMP_SAVE_DATA           PROP_TAG (PT_BOOLEAN,   (BASE_PROVIDER_ID + 0x000F))

#define PR_TEMP_LOGHIGHWATER        PROP_TAG (PT_TSTRING,   (BASE_PROVIDER_ID + 0x0010))
#define PR_TEMP_LOGLOWWATER         PROP_TAG (PT_TSTRING,   (BASE_PROVIDER_ID + 0x0011))

/* This property is a per-message option.  If TRUE, the message will be
   deferred until the next message comes along that is not to be deferred.
   At that point, the Transport will SpoolerNotify() to have all currently
   deferred messages submitted to it for sending.                           */

#define PR_SAMPLE_PER_MSG_DEFER     PROP_TAG (PT_BOOLEAN,   (BASE_MSG_OPT_ID + 0x0001))

/* This property is a per-recipient option.  If TRUE, the message will be
   deferred until the next message comes along that is not to be deferred.
   At that point, the Transport will SpoolerNotify() to have all currently
   deferred messages submitted to it for sending.  This property is ignored
   if PR_SAMPLE_PER_MSG_DEFER is set.

   This property is also used as a flag on the message that says - we've seen
   this message before and have deferred it due to some recipients with their
   property PR_SAMPLE_PER_RECIP_DEFER flag set.  When we run across this, we'll
   delete it from the message and send to the remaining recipients that
   have not been handled.                                                  */

#define PR_SAMPLE_PER_RECIP_DEFER   PROP_TAG (PT_BOOLEAN,   (BASE_RECIP_OPT_ID + 0x0001))

/* The following is used to access the properties in the logon array.      */

#define MAX_LOGON_PROPERTIES        17
#define TEMP_LOGON_PROPERTIES       6
#define ArrayIndex(PROP, ARRAY) (ARRAY)[(PROP_ID(PROP) - BASE_PROVIDER_ID - 1)]
#define NUM_SENDER_PROPS            3   /* How many sender ID properties?  */


/* Display name for my transport. Used for the status row. */

#ifdef DEBUG
#define MYDISPLAYNAME "Sample Transport Provider (Debug)"
#elif defined (TEST)
#define MYDISPLAYNAME "Sample Transport Provider (Test)"
#else
#define MYDISPLAYNAME "Sample Transport Provider"
#endif

/* Common global data/code. */

BOOL    FIsValidSession(LPXPL);
SCODE   ScCheckLogonProps(LPXPDLG lpXPDialog, BOOL fUIAllowed);
HRESULT MapScodeSz(SCODE sc, LPXPL lpxpl, LPTSTR * lppszMessage);
HRESULT HrCheckSpoolerYield(LPMAPISUP lpMAPISup, BOOL fReset);
SCODE   ScCopySessionProps(LPXPL lpxpl, LPSPropValue FAR *lppPropArray, LPSPropValue FAR *lppMyIDArray);

#ifdef __cplusplus
}
#endif
