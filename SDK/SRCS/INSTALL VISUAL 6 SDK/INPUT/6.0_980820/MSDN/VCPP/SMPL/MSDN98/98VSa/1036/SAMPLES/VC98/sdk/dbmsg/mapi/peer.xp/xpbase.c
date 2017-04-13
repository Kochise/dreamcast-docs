/*
 -  X P B A S E . C
 -
 *  Purpose:
 *      The sample transport provider illustrates the use of the MAPI
 *      Transport Service Provider Interface and those parts of the
 *      general SPI involved with the Provider Status, Notification,
 *      and some other stuff.
 *
 *      This module contains the following SPI entry points:
 *
 *          XPProviderInit()
 *          Shutdown()
 *          TransportLogon()
 *          AddressTypes()
 *          RegisterOptions()
 *          TransportLogoff()
 *          TransportNotify()
 *          ValidateState()
 *          FlushQueues()
 *          IUnknown methods for IXPProvider (XPP) & IXPLogon (XPL) objects
 *
 *      Additional support functions found here:
 *
 *          FIsValidSession()
 *          CleanupSession()
 *          ScCheckLogonProps()
 *          HrCheckSpoolerYield()
 *          ScCopySessionProps()
 *          ServiceEntry()
 *          HrOpenSingleProvider()
 *          ScMergeLogonProps()
 *
 *  NOTE:
 *  We have a luxury which most providers don't share: our SPI operations
 *  all occur on a single process context.  This means we don't have to
 *  worry a lot about DLL context, etc. like other providers.
 *
 *  Copyright 1992-1995 Microsoft Corporation.  All Rights Reserved.
 */

#include "xppch.h"
#include "xpresrc.h"

/* On 32-bit, we want MB_SETFOREGROUND on MessageBoxes. */

#ifndef MB_SETFOREGROUND
#define MB_SETFOREGROUND 0
#endif

/*
 *  No bitness in the name of this DLL.  MAPI will handle that.
 */

#define szDLLName   "smpxp.dll"

/* Property Tags of Profile/UI information for a transport session. */

/* NOTE!!! THE ORDERING OF THIS ARRAY MUST BE EXACTLY THE SAME AS THE
   ORDERING OF PROP ID'S IN SMPLXPT.H!!!! */

SizedSPropTagArray(MAX_LOGON_PROPERTIES, sptLogonArray) =
{
    MAX_LOGON_PROPERTIES,
    {
        /* Properties stored in Profile */
        PR_SAMPLE_DISPLAY_NAME,
        PR_SAMPLE_EMAIL_ADDR_TYPE,
        PR_SAMPLE_EMAIL_ADDRESS,
        PR_SAMPLE_INBOUND_DIR,
        PR_SAMPLE_OUTBOUND_DIR,
        PR_SAMPLE_FILENAME,
        PR_SAMPLE_DIRECTORY,
        PR_SAMPLE_FLAGS,
        PR_SAMPLE_LOGFILE,
        PR_SAMPLE_LOGHIGHWATER,
        PR_SAMPLE_LOGLOWWATER,

        /* UI Temporary properties */
        PR_TEMP_PEER_TO_PEER,
        PR_TEMP_UI_ALWAYS,
        PR_TEMP_LOG_EVENTS,
        PR_TEMP_SAVE_DATA,
        PR_TEMP_LOGHIGHWATER,
        PR_TEMP_LOGLOWWATER
    }
};


/* MessageOption & RecipientOption Default Property Value */

static SPropValue spvMsgOpt = {PR_SAMPLE_PER_MSG_DEFER, 0L, FALSE};
static SPropValue spvRecipOpt = {PR_SAMPLE_PER_RECIP_DEFER, 0L, FALSE};

/* Wizard configuration items */
static LPMAPIPROP lpmpWizard = NULL;
enum
{
    ipDispName,
    ipEmailType,
    ipEmailAddress,
    ipInbox,
    ipOutbox,
    ipFilename,
    ipDirectory,
    ipFlags,
    ipLogFile,
    ipLogHigh,
    ipLogLow,
    cWizProps
};
#define cchNameMax  40
#define cchTypeMax  8

/* Virtual Table for the IXPProvider object */

XPP_Vtbl vtblXPP =
{
    XPP_QueryInterface,
    XPP_AddRef,
    XPP_Release,
    XPP_Shutdown,
    XPP_TransportLogon,
};

/* Virtual Table for the IXPLogon object */

XPL_Vtbl vtblXPL =
{
    XPL_QueryInterface,
    XPL_AddRef,
    XPL_Release,
    XPL_AddressTypes,
    XPL_RegisterOptions,
    XPL_TransportNotify,
    XPL_Idle,
    XPL_TransportLogoff,
    XPL_SubmitMessage,
    XPL_EndMessage,
    XPL_Poll,
    XPL_StartMessage,
    XPL_OpenStatusEntry,
    XPL_ValidateState,
    XPL_FlushQueues
};

/* Miscellaneous function prototypes. */

HRESULT HrDeleteDeferred(LPXPL lpxpl, LPSBinary lpsbinEID);
static void CleanupSession(LPXPL lpxpl);

MSGSERVICEENTRY ServiceEntry;
WIZARDENTRY WizardEntry;
SERVICEWIZARDDLGPROC WizardWndProc;

HRESULT HrOpenSingleProvider(LPPROVIDERADMIN, LPPROFSECT FAR *);
SCODE ScMergeLogonProps(ULONG, LPSPropValue, ULONG, LPSPropValue,
    LPALLOCATEBUFFER, LPALLOCATEMORE, LPSPropValue FAR *);

/*
 -  XPProviderInit
 -
 *  Purpose:
 *      Called by the Spooler prior to initiating actual Transport operations.
 *      Only needs to be called once, regardless of the number of sessions
 *      which the Spooler might establish with this Transport provider.
 *
 *  Parameters:
 *      hInstance           Instance of this library
 *      lpMalloc            OLE2 PMALLOC memory allocator
 *      lpAllocateBuffer    MAPIAllocateBuffer
 *      lpAllocateMore      MAPIAllocateMore
 *      lpFreeBuffer        MAPIFreeBuffer
 *      ulFlags             Reserved for now. Should be zero.
 *      ulSpoolerVer        MAPI version the Spooler is implemented to
 *      lpulTransportVer    Transport puts its MAPI version here
 *      lppXPProvider       Transport returns Transport Init Object here
 *
 *  Returns:
 *      SUCCESS_SUCCESS     Transport thinks all is well. Transport's
 *                          version of MAPI has been stored in
 *                          *lpulTransportVer. Transport's Init Object
 *                          address has been stored in *lppEntryPoints.
 *
 *      MAPI_E_VERSION      Transport doesn't like version of Spooler.
 *                          Contents of lpulTransportVer and
 *                          lppXPProvider are untouched by the Transport.
 *
 *      MAPI_E_CALL_FAILED  Transport already inited or session table
 *                          non-empty. Contents of lpulTransportVer and
 *                          lppXPProvider are untouched by the Transport.
 *
 *  Operation:
 *      In the call, the Spooler will tell the Transport what version of MAPI
 *      it normally expects to support. If the Transport knows that it cannot
 *      handle this version, it should return an error on this call. If it
 *      doesn't know, it should trust the Spooler to handle the problem.
 *
 *      The Transport puts the version of MAPI it expects to support back into
 *      lpulTransportVer and the Spooler should Shutdown if it cannot or
 *      doesn't want to handle this version.
 *
 *      Besides the information which the Spooler will use for its half of the
 *      MAPI version handshake, the Transport will return a valid Init Object
 *      address into the location pointed to by lppXPProvider.
 */

STDINITMETHODIMP
XPProviderInit(HINSTANCE hInstance,
    LPMALLOC lpMalloc,
    LPALLOCATEBUFFER lpAllocateBuffer,
    LPALLOCATEMORE lpAllocateMore,
    LPFREEBUFFER lpFreeBuffer,
    ULONG ulFlags,
    ULONG ulSpoolerVer,
    ULONG * lpulTransportVer,
    LPXPPROVIDER * lppXPProvider)
{
    SCODE sc = S_OK;
    LPXPP lpxpp;

    /*  Test Spooler Version. As we are a MAPI 1.0 transport, we'll
        accept any MAPI version over 1.0 (and trust the Spooler to
        refuse to handle 1.0 if he's too far advanced!)
    */

    if (ulSpoolerVer < CURRENT_SPI_VERSION)
    {
        sc = MAPI_E_VERSION;
        DebugTrace("Spooler version check failed.\n");
        goto ret;
    }

    /*  Allocate space for the XPP structure */

    sc = (*lpAllocateBuffer) (sizeof(XPP), (LPVOID *) &lpxpp);

    if (sc)
    {
        DebugTrace("XPProvider allocation failed.\n");
        goto ret;
    }

    /*  Fill in the data members and the jump table. */

    lpxpp->lpVtbl = &vtblXPP;
    lpxpp->lcInit = 1;
    lpxpp->lpxppMyAddress = lpxpp;
    lpxpp->hInst = hInstance;
    lpxpp->XPSessionList = (LPXPL) NULL;
    lpxpp->fInited = TRUE;
    lpxpp->lpMalloc = lpMalloc;
    lpxpp->lpFreeBuffer = lpFreeBuffer;

    /* We're keeping it, we need to AddRef it! */

    UlAddRef(lpMalloc);

    /*  Initialize a critical section to be used while:
            1. Accessing the Status Object
            2. Doing session list management
            3. Initializing the logging sub-system
            4. Processing a TransportNotify call

        These are areas where the potential for re-entrancy
        is high and we need to protect ourselves.
    */

    InitializeCriticalSection(&lpxpp->csTransport);

    /*  Return version number and IXPProvider object to the Spooler. */

    *lpulTransportVer = CURRENT_SPI_VERSION;
    *lppXPProvider = (LPXPPROVIDER) lpxpp;

ret:
    DebugTraceSc(XPProviderInit, sc);
    return ResultFromScode(sc);
}


/*
 -  lpxpp->lpVtbl->Shutdown
 -
 *  Purpose:
 *      Called by the Spooler when all operations on a Transport are complete.
 *      Only needs to be called once, regardless of the number of sessions
 *      which the Spooler might have established with this Transport provider.
 *
 *  Parameters:
 *      lpulFlags           Contains flags passed from Spooler:
 *
 *                          DEINIT_NORMAL indicates a normal
 *                          operation. All cleanup should proceed
 *                          at whatever pace is required for
 *                          completeness.
 *
 *                          DEINIT_HURRY indicates rapid shutdown.
 *                          Anything that can be done very quickly
 *                          should be done; time-consuming operations
 *                          are to be avoided.
 *
 *                          In the absence of these flag bits, the
 *                          Transport should assume DEINIT_NORMAL.
 *
 *  Returns:
 *      SUCCESS_SUCCESS     Transport has done all cleanup. Go ahead
 *                          and release it.
 *
 *      MAPI_E_CALL_FAILED  Transport hasn't been inited or has
 *                          already been deinited.
 *
 *  Operation:
 *      This call normally will happen if the Spooler doesn't like the
 *      Transport version passed in from XPProviderInit; if the Spooler
 *      attempts to log into the Transport and fails; and after a
 *      TransportLogoff.
 *
 *      If there are any sessions active in this process, the Transport
 *      should clean them up (propagating the DEINIT_HURRY down to
 *      LOGOFF_HURRY in the TransportLogoff flags) before returning.
 *
 *      The Spooler guarantees non-reentrancy on this call.
 */

STDMETHODIMP
XPP_Shutdown(LPXPP lpxpp, ULONG FAR * lpulFlags)
{
    LPXPL lpxpl = NULL;
    ULONG ulFlags;
    HRESULT hResult = hrSuccess;

    /*  Walk down the session list. Log off any active sessions.

        NOTE: IT IS *REALLY* IMPORTANT THAT ANY WORK DONE TO CHANGE
        THE WAY THIS LIST IS WALKED OR RELINKED BY LOGOFF BE DONE IN
        SUCH A WAY THAT BOTH THIS CODE AND THE TRANSPORTLOGOFF CODE
        CONTINUE TO WORK CORRECTLY!!
    */

    /* Get the Critical Section */

    EnterCriticalSection(&lpxpp->csTransport);

    lpxpl = lpxpp->XPSessionList;
    ulFlags = (*lpulFlags & DEINIT_HURRY) ? LOGOFF_HURRY : LOGOFF_NORMAL;

    while (lpxpl)
    {
        LPXPL lpNext = lpxpl->lpNextSession;

        hResult = XPL_TransportLogoff(lpxpl, ulFlags);

        if (hResult)
        {
            DebugTrace("Logging off session failed.\n");

            /*
             * A logoff failed. If we are in HURRY mode, we'll let it
             * go. Otherwise, we pass the error along and get out!
             */

            if (!(*lpulFlags & DEINIT_HURRY))
            {
                DebugTrace("Returning Logoff result to caller.\n");

                /*
                 * Relink the listhead so that everything has some
                 * degree of internal consistency.
                 */

                lpxpp->XPSessionList = lpxpl;
                goto ret;
            }

            DebugTrace("DEINIT_HURRY set, deallocating session and proceeding.\n");
            CleanupSession(lpxpl);
        }
        lpxpl->lpVtbl->Release(lpxpl);
        lpxpl = lpNext;
    }

    /* Release the Critical Section */

    LeaveCriticalSection(&lpxpp->csTransport);

    /* Delete critical section which XPProviderInit() initialized. */

    DeleteCriticalSection(&lpxpp->csTransport);

    lpxpp->XPSessionList = NULL;
    lpxpp->fInited = FALSE;

    *lpulFlags = 0;

ret:
    /* Turn off logging if active */

    DeInitTransportLog((*lpulFlags & DEINIT_HURRY) ? LOG_DEINIT_HURRY : 0L);

    DebugTraceResult(XPP_Shutdown, hResult);
    return hResult;
}


/*
 -  lpxpp->lpVtbl->TransportLogon
 -
 *  Purpose:
 *      Called by the Spooler to establish a session with a Transport.
 *      This call might be made many times, once for each session the Spooler
 *      wants to establish with an external messaging system through this
 *      Transport. These multiple sessions will usually be established on a
 *      one-for-one basis with the number of identities which the current
 *      profile has established for the given messaging system.
 *
 *  Parameters:
 *      lpxpp               The parent XPProvider object who will
 *                          own this new session.
 *
 *      lpMAPISup           A pointer to a MAPI Support Object which
 *                          is uniquely associated with this session
 *                          by the Spooler. Any MAPI Support calls
 *                          associated with this session should be
 *                          done using this Support Object.
 *
 *      ulUIParam           The hWnd who will become the parent of any
 *                          UI we decide to put up (like a logon dialog).
 *
 *      lpszProfileName     Contains a display name associated with the
 *                          current user's profile.  Expected to be
 *                          used by the Transport primarily to make
 *                          any UI easier for the user to decipher.
 *
 *      lpulFlags           (In)
 *
 *                          Flags passed from Spooler to Transport:
 *
 *                          LOGON_NO_DIALOG instructs the Transport
 *                          not to put any UI up during this operation.
 *                          If the operation cannot be completed
 *                          without UI, an error should be returned.
 *
 *                          LOGON_NO_CONNECT is set by the Spooler
 *                          when the transport connection is being
 *                          made in order to do things like get
 *                          per-message/per-recipient options; using
 *                          preprocessor stuff, etc -- but to do so
 *                          "offline". The Transport is not to connect
 *                          to the outside world, and if there are
 *                          insufficient credentials to allow the
 *                          Transport to operate as if the user should
 *                          be permitted access, the Transport may
 *                          wish to fail without presenting UI.
 *
 *                          LOGON_NO_INBOUND is set by the Spooler
 *                          to signal the Transport not to accept
 *                          incoming mail on this session. The Spooler
 *                          will ignore the NOTIFY_NEWMAIL flag on
 *                          SpoolerNotify() and it will not Poll()
 *                          the Transport on this session. It's OK
 *                          to make external connections for reasons
 *                          other than mail reception. The Spooler
 *                          may TransportNotify() to enable inbound.
 *
 *                          LOGON_NO_OUTBOUND is set by the Spooler
 *                          to signal the Transport that outgoing
 *                          mail won't be sent right now on this
 *                          session. The Spooler will ignore the
 *                          NOTIFY_READYTOSEND flag on SpoolerNotify()
 *                          and will not be calling SubmitMessage().
 *                          It's OK to make external connections for
 *                          reasons other than mail transmission. The
 *                          Spooler may TransportNotify() to signal
 *                          the start of outbound operations.
 *  Returns:
 *      lpulFlags           (Out)
 *
 *                          Flags passed from Transport to Spooler:
 *
 *                          LOGON_SP_IDLE tells the Spooler to call
 *                          the Idle() entry point with this logon
 *                          handle as part of its idle processing.
 *                          The transport may use this to check its
 *                          underlying messaging system for incoming
 *                          mail, to do special processing outside
 *                          of the SPI, or maybe some kind of network
 *                          link maintenance, for example.
 *
 *                          LOGON_SP_POLL instructs the Spooler to
 *                          call the Transport at its Poll() entry
 *                          point on a regular basis to see if any
 *                          new mail is ready for import into the
 *                          MAPI subsystem.
 *
 *                          LOGON_SP_RESOLVE instructs the Spooler
 *                          and MAPI to ensure that all addresses in
 *                          an outgoing message's recipient table are
 *                          fully resolved before this transport is
 *                          given the message. This could be used by
 *                          a transport to make a best-guess routing
 *                          from a recipient's system to allow a given
 *                          recipient to include all other recipients
 *                          of a message in a reply ("Reply-All").
 *
 *      lppXPLogon          Contains a pointer to the Transport
 *                          Logon object (an instance of IXPLogon)
 *                          that is used to access the session we
 *                          just created.
 *
 *      MAPI_E_UNCONFIGURED Something's wrong with credentials or
 *                          other things needed for logon. We're
 *                          not really saying what.
 *
 *  Operation:
 *      The Spooler makes this call when it wants to establish a session with
 *      the Transport provider. When called here, the Transport will need to
 *      perform several actions:
 *
 *  1) Get credentials out of the profile.
 *
 *  2)  Determine if credentials are sufficient. Some providers may choose
 *      to just send along what they have to the host and let validation
 *      happen there; others will want to determine that credentials have
 *      some validity before setting off breakin alarms on a mail host system.
 *
 *  3) If credentials are insufficient, return MAPI_E_UNCONFIGURED.
 *
 *  4) Validate credentials. This may involve establishing a connection to the
 *     underlying messaging system and allowing it to determine that the
 *     credentials are OK.
 *
 *  5) If credentials not OK, the Transport provider should return
 *     MAPI_E_UNCONFIGURED.  This will reuqest that MAPI calls the ServiceEntry
 *     point to obtain the missing configuration information.
 *
 *  6) Save credentials. The profile section made available to the Transport
 *     Provider can be used to store this information if so indicated.
 *
 *      Transports that are less concerned about security may leave out any or
 *      all of the above.
 *
 *  7) Build the logon object.
 *
 *  8) Construct a Status Table row and call ModifyStatusRow().
 *
 *  9) Link the logon object into the list for the transport.
 *
 * 10) Start up logger if need be
 *
 * 11) Log completion of logon operation.
 *
 *
 *  Note:
 *      There are some parameters stored at the session level (in the
 *      profile) that are more global in nature, such as the logging stuff
 *      and peer-to-peer. The way we will resolve this is to interpret new
 *      information in the light of old stuff, favoring the "on" state. So
 *      a session that says "no logging" will in fact not be logged only if
 *      not preceded by a session with logging on, and the session will be
 *      logged as soon as a session that specifies logging comes online. The
 *      inbound and outbound paths will be respected; the first logfile name
 *      will rule.  A session that didn't want to be peer-to-peer could have
 *      its way among lots of peer-to-peer transports by specifying a
 *      different outbound path.
 *
 */

STDMETHODIMP
XPP_TransportLogon(LPXPP lpxpp,
    LPMAPISUP lpMAPISup,
    ULONG ulUIParam,
    LPTSTR lpszProfileName,
    ULONG * lpulFlags,
    LPMAPIERROR * lppMapiError,
    LPXPLOGON FAR * lppXPLogon)
{
    LPSPropValue lpPropArray = NULL;
    LPSPropValue lpMyIDArray = NULL;
    LPVOID lpvT, lpvT2;
    ULONG ulCount = 0;
    ULONG ulT;
    SCODE sc = 0;
    HRESULT hResult = 0;
    LPXPL lpxpl = NULL;
    LPPROFSECT lpProfileObj = NULL;
    LPOPTIONDATA lpOptData = NULL;

    LPALLOCATEBUFFER lpAllocBuffer;
    LPALLOCATEMORE lpAllocMore;
    LPFREEBUFFER lpFreeBuffer;

    BOOL fNeedUI = FALSE;
    BOOL fInitialParamsOk = TRUE;

    *lppMapiError = NULL;

    if ( *lpulFlags & MAPI_UNICODE )
        return ResultFromScode( MAPI_E_BAD_CHARWIDTH ) ;

    /*  Get the memory allocation routines we'll be needing. */

    hResult = lpMAPISup->lpVtbl->GetMemAllocRoutines(lpMAPISup,
        &lpAllocBuffer, &lpAllocMore, &lpFreeBuffer);

    if (hResult)
    {
        DebugTrace("GetMemAllocRoutines failed in XP Logon.\n");
        goto ret;
    }

    /* Try to open our profile. */

    hResult = lpMAPISup->lpVtbl->OpenProfileSection(lpMAPISup,
        (LPMAPIUID) NULL, MAPI_MODIFY, &lpProfileObj);

    if (hResult)
    {
        DebugTrace("OpenProfileSection failed in XP Logon.\n");
        goto ret;
    }

    /* Profile is open, get the properties out of it. */

    hResult = lpProfileObj->lpVtbl->GetProps(lpProfileObj,
        (LPSPropTagArray) &sptLogonArray, 0, /* ansi */
        &ulCount, &lpPropArray);

    if (hResult)
    {
#ifdef DEBUG
        LPMAPIERROR lpMapiError = NULL;

        DebugTrace("GetProps failed in XP Logon.\n");

        lpProfileObj->lpVtbl->GetLastError(lpProfileObj, hResult,
            0L, &lpMapiError);

        if ( lpMapiError && lpMapiError->lpszError )
        {
            DebugTrace(lpMapiError->lpszError);
            DebugTrace("\n");

            lpFreeBuffer((LPVOID) lpMapiError);
        }
#endif
        /* Couldn't read all of the properties. We'll recover
           from the error by just bringing up UI if allowed. */

        hResult = hrSuccess;
    }

    /* Profile is open. Get all of our expected properties. */

    Assert(ulCount == MAX_LOGON_PROPERTIES);
    ulCount -= TEMP_LOGON_PROPERTIES;

    Assert(ulCount < MAX_LOGON_PROPERTIES);

    /* Make sure that we have the properties we want. If not, signal the
       need for UI.

       We could also check that network paths etc. exist at this point. */

    if (lpPropArray)
    {
        XPDLG       XPDialog;

        fNeedUI = FALSE;        /* Default to saying we have what we need */

        for (ulT = 0; ulT < ulCount; ulT++)
        {
            /* If any of the properties is PT_ERROR, we need to
               bring up UI. */

            if (PROP_TYPE(lpPropArray[ulT].ulPropTag) == PT_ERROR)
            {
                fNeedUI = TRUE;
                break;
            }
        }

        /* The configuration checking assumes that the information came from
           a dialog box, so we have to look like a dialog box to use it. */
        XPDialog.hInst = NULL;
        XPDialog.hwnd = (HWND) ulUIParam;
        XPDialog.lppPropArray = &lpPropArray;
        XPDialog.lpPTArray = (LPSPropTagArray) &sptLogonArray;
        XPDialog.AllocateBuffer = lpAllocBuffer;
        XPDialog.AllocateMore = lpAllocMore;
        XPDialog.FreeBuffer = lpFreeBuffer;
        XPDialog.lpMalloc = NULL;
        XPDialog.lpMAPISup = lpMAPISup;
        XPDialog.fLogon = TRUE;
        XPDialog.ulFlags = 0;

        /* Do some simple validation of the Logon Props */
        sc = ScCheckLogonProps(&XPDialog, FALSE);
        if ((sc == MAPI_E_USER_CANCEL) || (sc == MAPI_E_UNCONFIGURED))
            fNeedUI = TRUE;
    }
    else
        fNeedUI = TRUE;         /* No prop array means we need UI */

    /* Now we have a local flag that will tell us whether UI must be
       presented. We should consider it a "I require data to complete
       logon" state as well. At this point, act on the LOGON_NO_DIALOG
       flag and error out if we are not allowed to present UI but we
       have some reason for wanting it. */

    if (fNeedUI)
    {
        /* Fill in the logon UI structure */
        hResult = ResultFromScode(MAPI_E_UNCONFIGURED);
        DebugTrace("Need UI, returning MAPI_E_UNCONFIGURED to get some.\n");
        goto ret;
    }

    /* Create the session structure and copy important data into it */
    sc = lpAllocBuffer(sizeof(XPL), (LPVOID *) &lpxpl);

    if (sc)
    {
        hResult = ResultFromScode(sc);
        DebugTrace("Allocating XPLogon object failed in XP Logon.\n");
        goto ret;
    }

    memset(lpxpl, 0, sizeof(XPL));

    lpxpl->lpVtbl = &vtblXPL;
    lpxpl->lcInit = 1;

    lpxpl->lpMySession = lpxpl; /* Used to validate structure */
    lpxpl->lpxppParent = lpxpp;
    lpxpl->lpMAPISup = lpMAPISup;   /* Copy of our support object */
    lpxpl->AllocateBuffer = lpAllocBuffer;
    lpxpl->AllocateMore = lpAllocMore;
    lpxpl->FreeBuffer = lpFreeBuffer;
    lpxpl->ulSessionFlags = *lpulFlags; /* Important session flags*/

    lpxpl->cLogonPropValues = ulCount;  /* Count of logon properties */
    lpxpl->lpPropArray = lpPropArray;   /* Array of properties */

    lpxpl->lpMyIDArray = NULL;  /* Transport ID */
    lpxpl->fRefSupport = FALSE;

    /* Figure out what the initial status of the transport will be */

    if ((*lpulFlags & LOGON_NO_CONNECT))
    {
        lpxpl->ulTransportStatus = STATUS_OFFLINE;
    }
    else
    {
        lpxpl->ulTransportStatus = STATUS_AVAILABLE;

        if (!(*lpulFlags & LOGON_NO_INBOUND))
            lpxpl->ulTransportStatus |= STATUS_INBOUND_ENABLED;

        if (!(*lpulFlags & LOGON_NO_OUTBOUND))
            lpxpl->ulTransportStatus |= STATUS_OUTBOUND_ENABLED;
    }

    /* Initialize Status object ResourceMethods.  FlushQueues
       and SettingsDialog are currently implemented */

    lpxpl->ulResourceMethods = STATUS_SETTINGS_DIALOG | STATUS_FLUSH_QUEUES;

    /* Initialize message send/receive state */

    lpxpl->fFoundInMessage = FALSE;
    lpxpl->hInFindHandle = INVALID_HANDLE_VALUE;
    lpxpl->hOutFindHandle = INVALID_HANDLE_VALUE;

    /* Allocate and initialize the Message & Recipient OptionData struct */

    sc = lpAllocBuffer(2 * sizeof(OPTIONDATA), (LPVOID *) &lpOptData);

    if (sc)
    {
        hResult = ResultFromScode(sc);
        DebugTrace("Allocating OPTIONDATA failed in XP Logon.\n");
        goto ret;
    }

    /* Option Data is registered by Address Type.  In the SettingsDialog()
       call on the Status object we force the email address type field to
       be read-only.  This ensures that this OptionData remains valid for
       the duration of this session.

       NOTE:    The ulOrdinal must match the value assigned in the .DEF file.
                If this value changes, it must be changed here and in the
                .DEF file to the same value! */

    lpOptData[0].ulFlags = OPTION_TYPE_MESSAGE;
    lpOptData[0].lpRecipGUID = NULL;
    lpOptData[0].lpszAdrType = ArrayIndex(PR_SAMPLE_EMAIL_ADDR_TYPE, lpPropArray).Value.LPSZ;
    lpOptData[0].lpszDLLName = szDLLName;
    lpOptData[0].ulOrdinal = 3;
    lpOptData[0].cbOptionsData = 0;
    lpOptData[0].lpbOptionsData = NULL;
    lpOptData[0].cOptionsProps = 1;
    lpOptData[0].lpOptionsProps = &spvMsgOpt;

    lpOptData[1].ulFlags = OPTION_TYPE_RECIPIENT;
    lpOptData[1].lpRecipGUID = NULL;
    lpOptData[1].lpszAdrType = ArrayIndex(PR_SAMPLE_EMAIL_ADDR_TYPE, lpPropArray).Value.LPSZ;
    lpOptData[1].lpszDLLName = szDLLName;
    lpOptData[1].ulOrdinal = 3;
    lpOptData[1].cbOptionsData = 0;
    lpOptData[1].lpbOptionsData = NULL;
    lpOptData[1].cOptionsProps = 1;
    lpOptData[1].lpOptionsProps = &spvRecipOpt;

    lpxpl->cOptData = 2;
    lpxpl->lpOptData = lpOptData;
    lpOptData = NULL;

    /* Allocate initial property array for transport ID. */

    sc = lpAllocBuffer(sizeof(SPropValue) * NUM_SENDER_PROPS,
            (LPVOID *) &lpMyIDArray);

    if (sc)
    {
        hResult = ResultFromScode(sc);
        DebugTrace("Allocating Sender ID array failed in XP Logon.\n");
        goto ret;
    }

    /* Zero the memory and hook it into the logon object now.  That
       way, if we get a failure between here and ret: then this
       memory will be freed in CleanupSession(). */

    memset(lpMyIDArray, 0, sizeof(SPropValue) * NUM_SENDER_PROPS);
    lpxpl->lpMyIDArray = lpMyIDArray;

    /* Create the One-Off directly into the property value structure. */

    lpMyIDArray[0].ulPropTag = PR_SENDER_ENTRYID;

    hResult = lpMAPISup->lpVtbl->CreateOneOff(lpMAPISup,
        ArrayIndex(PR_SAMPLE_DISPLAY_NAME, lpPropArray).Value.LPSZ,
        ArrayIndex(PR_SAMPLE_EMAIL_ADDR_TYPE, lpPropArray).Value.LPSZ,
        ArrayIndex(PR_SAMPLE_EMAIL_ADDRESS, lpPropArray).Value.LPSZ,
        fMapiUnicode,
        &lpMyIDArray[0].Value.bin.cb,
        (LPENTRYID *) &lpMyIDArray[0].Value.bin.lpb);

    if (hResult)
    {
        DebugTrace("CreateOneOff failed in XP Logon.\n");
        lpMyIDArray[0].Value.bin.lpb = NULL;
        goto ret;
    }

    /* Create the PR_SENDER_NAME property value. */

    lpMyIDArray[1].ulPropTag = PR_SENDER_NAME;
    lpvT2 = ArrayIndex(PR_SAMPLE_DISPLAY_NAME, lpPropArray).Value.LPSZ;
    ulT = (lstrlen((LPCTSTR) lpvT2) + 1) * sizeof(TCHAR);

    sc = lpAllocMore(ulT, (LPVOID) lpMyIDArray, &lpvT);

    if (sc)
    {
        hResult = ResultFromScode(sc);
        DebugTrace("Allocating user DisplayName failed in XP Logon.\n");
        goto ret;
    }

    lstrcpy((LPTSTR) lpvT, (LPCTSTR) lpvT2);
    lpMyIDArray[1].Value.LPSZ = (LPTSTR) lpvT;

    /* Create the PR_SENDER_SEARCH_KEY value. */

    lpMyIDArray[2].ulPropTag = PR_SENDER_SEARCH_KEY;

    /* Size of property = type plus colon plus address plus null. */

    ulT = 2 + lstrlen(ArrayIndex(PR_SAMPLE_EMAIL_ADDR_TYPE, lpPropArray).Value.LPSZ) +
          lstrlen(ArrayIndex(PR_SAMPLE_EMAIL_ADDRESS, lpPropArray).Value.LPSZ);
    ulT *= sizeof(TCHAR);

    sc = lpAllocMore(ulT, (LPVOID) lpMyIDArray, &lpvT);

    if (sc)
    {
        hResult = ResultFromScode(sc);
        DebugTrace("Allocating SearchKey failed in XP Logon.\n");
        goto ret;
    }

    /* PR_SENDER_SEARCH_KEY is "TYPE:ADDRESS" folded to uppercase. */

    wsprintf((LPTSTR) lpvT, TEXT("%s:%s"),
            ArrayIndex(PR_SAMPLE_EMAIL_ADDR_TYPE, lpPropArray).Value.LPSZ,
            ArrayIndex(PR_SAMPLE_EMAIL_ADDRESS, lpPropArray).Value.LPSZ);

    CharUpperBuff((LPTSTR) lpvT, (UINT) ulT-sizeof(TCHAR));
    lpMyIDArray[2].Value.bin.cb = ulT;
    lpMyIDArray[2].Value.bin.lpb = lpvT;

    /* Register the preprocessor */

    hResult = lpMAPISup->lpVtbl->RegisterPreprocessor (lpMAPISup, NULL,
        ArrayIndex(PR_SAMPLE_EMAIL_ADDR_TYPE, lpPropArray).Value.LPSZ,
#ifdef  WIN16
        "SMPXP.DLL",
#else
        "SMPXP32.DLL",
#endif
        "PreprocessMessage", "RemovePreprocessInfo", 0L);

    if (hResult)
    {
        DebugTrace("RegisterPreprocessor failed in XP Logon.\n");
        goto ret;
    }

    /* Get the Critical Section */

    EnterCriticalSection(&lpxpp->csTransport);

    /* Build the status row and register it */

    hResult = HrBuildTransportStatus(lpxpl, 0L);

    if (hResult)
    {
        DebugTrace("HrBuildTransportStatus failed in XP Logon.\n");
        LeaveCriticalSection(&lpxpp->csTransport);
        goto ret;
    }

    /* Link the session structure into the list. */

    lpxpl->lpNextSession = lpxpp->XPSessionList;
    lpxpp->XPSessionList = lpxpl;

    /* AddRef() the support object. */

    lpMAPISup->lpVtbl->AddRef(lpMAPISup);
    lpxpl->fRefSupport = TRUE;

    /* Release the Critical Section. */

    LeaveCriticalSection(&lpxpp->csTransport);

    /* Start up logfile stuff if this session indicates it. */

    InitTransportLog(lpxpl, 0L);

    /* OK, we were successful. Set the return values. */

    *lppXPLogon = (LPXPLOGON) lpxpl;

    /* No flags necessary if no connect ... */

    if (lpxpl->ulSessionFlags & LOGON_NO_CONNECT)
    {
        *lpulFlags = 0;
    }
    else
    {
        /* Idle and resolve for transmit; Poll for receive */

        *lpulFlags = LOGON_SP_IDLE | LOGON_SP_RESOLVE | LOGON_SP_POLL;
    }

ret:
    UlRelease(lpProfileObj);

    /*  Make sure we have an hResult.

        Assumptions:
            if hResult is set, it reflects the last error.
            if sc is set and hResult is not, we want hResult to be set.
    */

    if (hResult)
    {
        /* Error. Get rid of anything already on the session object. */
        /* If no session object, free data that could have been      */
        /* allocated before session object creation.                 */

        if (lpxpl)
        {
            CleanupSession(lpxpl);
            lpxpl->lpVtbl->Release(lpxpl);
        }
        else lpFreeBuffer (lpPropArray);
    }

    DebugTraceResult(XPP_TransportLogon, hResult);
    return hResult;
}


/*
 -  lpxpl->lpVtbl->AddressTypes
 -
 *  Purpose:
 *      Called by the Spooler to find out what recipients it should expect
 *      this transport to handle.
 *
 *  Parameters:
 *      ulFlags             Ignored for now.
 *      lpcAdrType          Pointer: where to store number of address types
 *      lpppAdrTypeArray    Pointer: where to store list of address types
 *      lpcMAPIUID          Pointer: where to store number of UID's
 *      lpppMAPIUIDArray    Pointer: where to store list of MAPI UID's
 *
 *  Returns:
 *      (HRESULT)           Errors encountered if any.
 *
 *  Operation:
 *      Returns the Address Type entered at Logon time in the address type
 *      array. Makes no use of the UID array.
 */

STDMETHODIMP
XPL_AddressTypes(LPXPL lpxpl,
    ULONG * lpulFlags,
    ULONG * lpcAdrType, LPTSTR * *lpppAdrTypeArray,
    ULONG * lpcMAPIUID, LPMAPIUID * *lpppMAPIUIDArray)
{
    ULONG cb;
    SCODE sc;
    LPTSTR lpsz;

    /* We are returning an array with exactly one value.  We first need
       to AllocateMore a buffer (that is linked to the lpxpl object) and
       copy our Email Address Type into there.  We then return the address
       of this copy of our AddressType.  */

    if ( *lpulFlags & ~(MAPI_UNICODE) )
        return ResultFromScode( MAPI_E_UNKNOWN_FLAGS );

    if ( *lpulFlags & MAPI_UNICODE )
        return ResultFromScode( MAPI_E_BAD_CHARWIDTH ) ;

    *lpcAdrType = 1;

    lpsz = ArrayIndex(PR_SAMPLE_EMAIL_ADDR_TYPE, lpxpl->lpPropArray).Value.LPSZ;

    cb = (lstrlen(lpsz) + 1) * sizeof(TCHAR);

    sc = lpxpl->AllocateMore(cb, (LPVOID) lpxpl, (LPVOID *) &lpxpl->lpszAdrType);

    if (FAILED(sc))
    {
        DebugTrace("AllocateMore in XPL_AddressType failed!\n");
        return ResultFromScode(sc);
    }

    lstrcpy(lpxpl->lpszAdrType, lpsz);

    *lpppAdrTypeArray = &(lpxpl->lpszAdrType);

    /* Routing by UID has no particular meaning for this transport. */

    *lpcMAPIUID = 0;
    *lpppMAPIUIDArray = NULL;

    return hrSuccess;
}


/*
 -  lpxpl->lpVtbl->RegisterOptions
 -
 *  Purpose:
 *      Called by the Spooler to find out what per-message or per-recipient
 *      options this transport might wish supported.
 *
 *  Parameters:
 *      lpulFlags           Indicates whether strings are UNICODE or not.
 *      lpcOptions          Pointer: where to store number of address
 *                          types for which options are being requested
 *      lppOptions          Pointer: where to store a list of display
 *                          names associated with each address type
 *
 *  Returns:
 *      (HRESULT)           Errors encountered if any.
 */

STDMETHODIMP
XPL_RegisterOptions(LPXPL lpxpl,
    ULONG * lpulFlags,
    ULONG * lpcOptions,
    LPOPTIONDATA * lppOptions)
{
    /* Just give them what we have in our XPLogon object.       */
    /* These options were initialized at TransportLogon() time. */

    if ( *lpulFlags & ~(MAPI_UNICODE) )
        return ResultFromScode( MAPI_E_UNKNOWN_FLAGS );

    if ( *lpulFlags & MAPI_UNICODE )
        return ResultFromScode( MAPI_E_BAD_CHARWIDTH ) ;

    *lpcOptions = lpxpl->cOptData;
    *lppOptions = lpxpl->lpOptData;

    return 0;
}


/*
 -  lpxpl->lpVtbl->TransportLogoff
 -
 *  Purpose:
 *      Called by the Spooler to log off a particular Transport session.
 *
 *  Parameters:
 *      ulFlags             May contain LOGOFF_HURRY, which tells
 *                          the transport to close this session
 *                          as quickly as possible.
 *
 *  Returns:
 *      (HRESULT)           Errors encountered if any.
 *
 *  Operation:
 *      Find the session. Tell MAPI the session's going away, unlink it from
 *      the list, close open handles and deallocate session memory.
 */

STDMETHODIMP
XPL_TransportLogoff(LPXPL lpxpl, ULONG ulFlags)
{
    SCODE sc = S_OK;
    LPXPL lpxplCurr;
    LPXPL lpxplPrev = NULL;
    LPXPP lpxpp = lpxpl->lpxppParent;

    /* Get the critical section */

    EnterCriticalSection(&lpxpp->csTransport);

    /* Find the session in the list. */

    lpxplCurr = lpxpp->XPSessionList;

    while (lpxplCurr)
    {
        if (lpxpl == lpxplCurr)
        {
            /* Unlink the session from the list. */

            if (lpxplPrev == NULL)
                lpxpp->XPSessionList = lpxpl->lpNextSession;
            else
                lpxplPrev->lpNextSession = lpxpl->lpNextSession;

            break;
        }

        lpxplPrev = lpxplCurr;
        lpxplCurr = lpxplCurr->lpNextSession;
    }

    /* Release the critical section */

    LeaveCriticalSection(&lpxpp->csTransport);

    /* lpxplCurr must be non-NULL if we found the session. */

    if (!lpxplCurr)
    {
        sc = MAPI_E_INVALID_PARAMETER;
        goto ret;
    }

    /* Clean up the stuff inside the session structure. This may
       cause the XPP object to be released. */

    CleanupSession(lpxpl);

ret:
    DebugTraceSc(TransportLogoff, sc);
    return ResultFromScode(sc);
}


/*
 -  lpxpl->lpVtbl->TransportNotify
 -
 *  Purpose:
 *      Called by the Spooler to call some event to the Transport's attention.
 *
 *  Parameters:
 *      lpulFlags           Flags passed bidirectionally.
 *                          This transport pays attention to the
 *                          (BEGIN/END/FLUSH)(INBOUND/OUTBOUND)
 *                          flags and ignores the others.
 *      lppvData            Data passed bidirectionally. Not
 *                          used by this transport.
 *
 *  Returns:
 *      (HRESULT)           Errors encountered if any.
 *
 *  Operation:
 *      If the flag has any bearing on inbound/outbound startup/shutdown,
 *      then the appropriate change is made to the transport status in the
 *      XPLogon object and the HrUpdateTransportStatus routine is called to
 *      ModifyStatusRow() the change.
 */

STDMETHODIMP
XPL_TransportNotify(LPXPL lpxpl,
    ULONG * lpulFlags,
    LPVOID * lppvData)
{
    HRESULT hResult = hrSuccess;
    LPXPP lpxpp = lpxpl->lpxppParent;

#define TRANSPORT_NOTIFY_FLAGS  (NOTIFY_BEGIN_INBOUND       | \
                                NOTIFY_END_INBOUND          | \
                                NOTIFY_BEGIN_INBOUND_FLUSH  | \
                                NOTIFY_END_INBOUND_FLUSH    | \
                                NOTIFY_BEGIN_OUTBOUND       | \
                                NOTIFY_END_OUTBOUND         | \
                                NOTIFY_BEGIN_OUTBOUND_FLUSH | \
                                NOTIFY_END_OUTBOUND_FLUSH   | \
                                NOTIFY_CANCEL_MESSAGE       | \
                                NOTIFY_ABORT_DEFERRED)

    /* Validate we were passed a legal flag. */

    Assert(*lpulFlags & TRANSPORT_NOTIFY_FLAGS);

    /* Make sure we have a good session. */

    if (!FIsValidSession(lpxpl))
    {
        hResult = ResultFromScode(E_INVALIDARG);
        DebugTrace("FIsValidSession  failed in TransportNotify.\n");
        goto ret;
    }

    /* Get the Critical Section */

    EnterCriticalSection(&lpxpp->csTransport);

    /* Set appropriate status flags and re-register status row */

    if (*lpulFlags & NOTIFY_BEGIN_INBOUND)
    {
        DebugTrace("NOTIFY_BEGIN_INBOUND received and handled\n");
        lpxpl->ulTransportStatus |= STATUS_INBOUND_ENABLED;
    }

    if (*lpulFlags & NOTIFY_END_INBOUND)
    {
        DebugTrace("NOTIFY_END_INBOUND received and handled\n");
        lpxpl->ulTransportStatus &= ~STATUS_INBOUND_ENABLED;
    }

    if (*lpulFlags & NOTIFY_END_INBOUND_FLUSH)
    {
        DebugTrace("NOTIFY_END_INBOUND_FLUSH received and handled\n");
        lpxpl->ulTransportStatus &= ~STATUS_INBOUND_FLUSH;
    }

    if (*lpulFlags & NOTIFY_BEGIN_OUTBOUND)
    {
        DebugTrace("NOTIFY_BEGIN_OUTBOUND received and handled\n");
        lpxpl->ulTransportStatus |= STATUS_OUTBOUND_ENABLED;
    }

    if (*lpulFlags & NOTIFY_END_OUTBOUND)
    {
        DebugTrace("NOTIFY_END_OUTBOUND received and handled\n");
        lpxpl->ulTransportStatus &= ~STATUS_OUTBOUND_ENABLED;
    }

    if (*lpulFlags & NOTIFY_END_OUTBOUND_FLUSH)
    {
        DebugTrace("NOTIFY_END_OUTBOUND_FLUSH received and handled\n");
        lpxpl->ulTransportStatus &= ~STATUS_OUTBOUND_FLUSH;
    }

    if (*lpulFlags & NOTIFY_ABORT_DEFERRED)
    {
        DebugTrace("NOTIFY_ABORT_DEFERRED received and handled\n");

        hResult = HrDeleteDeferred(lpxpl, (LPSBinary)*lppvData);
    }

    /* We're just going to ignore NOTIFY_CANCEL_MESSAGE for now. */

    if (*lpulFlags & NOTIFY_CANCEL_MESSAGE)
    {
        DebugTrace("NOTIFY_CANCEL_MESSAGE received and ignored\n");
    }

    HrUpdateTransportStatus(lpxpl, 0L);

    /* Release the critical section. */

    LeaveCriticalSection(&lpxpp->csTransport);

ret:

    DebugTraceResult(XPL_TransportNotify, hResult);
    return hResult;
}


/*
 -  XPL_ValidateState
 -
 *  Purpose:
 *      Logon object method used by Spooler if ValidateState is called on
 *      the spooler status object.
 *
 *  Parameters:
 *      lpxpl               This pointer for logon object
 *      ulUIParam           Window handle
 *      ulFlags
 *
 *  Returns:
 *      (HRESULT)           E_INVALIDARG if object doesn't
 *                          look like a XPL; MAPI_E_NO_SUPPORT
 *                          otherwise.
 *
 *  Operation:
 *      Compare the PR_ADDRTYPE found in the profile to the one I am
 *      currently using.  If it has changed, then SpoolerNotify() to
 *      ask to be reloaded so MAPI will call AddressTypes() and
 *      RegisterOptions() on us again!
 *
 *  Note: We could check all the properties in our profile and be a
 *        better implementation of this call.  But for now, AddrType
 *        is the most important property to check.
 */

STDMETHODIMP
XPL_ValidateState(LPXPL lpxpl,
    ULONG ulUIParam,
    ULONG ulFlags)
{
    SCODE sc = S_OK;
    HRESULT hResult;
    LPPROFSECT lpProf = NULL;
    LPSPropValue lpspvAddrType = NULL;
    LPMAPISUP lpMAPISup = lpxpl->lpMAPISup;
    LPSPropValue lpPropArray = NULL;
    LPTSTR lpszAddrType = NULL;

    /*  If it doesn't seem to be an object or refcount is zero, return zero */

    if (IsBadReadPtr(lpxpl, sizeof(XPL)) ||
        lpxpl->lcInit == 0 ||
        lpxpl->lpMySession != lpxpl)
    {
        DebugTraceSc(XPL_ValidateState, E_INVALIDARG);
        return ResultFromScode(E_INVALIDARG);
    }

    if (ulFlags & ~SUPPRESS_UI)
    {
        DebugTraceSc(XPL_ValidateState, MAPI_E_UNKNOWN_FLAGS);
        return ResultFromScode(MAPI_E_UNKNOWN_FLAGS);
    }

    sc = ScCopySessionProps(lpxpl, &lpPropArray, NULL);

    if (FAILED(sc))
    {
        hResult = ResultFromScode(sc);
        DebugTrace("ScCopySessionProps failed in ValidateState.\n");
        goto ret;
    }

    lpszAddrType = ArrayIndex(PR_SAMPLE_EMAIL_ADDR_TYPE, lpPropArray).Value.LPSZ;

    /* Try to open our profile. */

    hResult = lpMAPISup->lpVtbl->OpenProfileSection(lpMAPISup,
        (LPMAPIUID) NULL, MAPI_MODIFY, &lpProf);

    if (hResult)
    {
        DebugTrace("OpenProfileSection  failed in ValidateState.\n");
        goto ret;
    }

    hResult = HrGetOneProp((LPMAPIPROP)lpProf,
            PR_SAMPLE_EMAIL_ADDR_TYPE, &lpspvAddrType);

    if (HR_FAILED(hResult))
    {
        DebugTrace("HrGetOneProp failed in ValidateState.\n");
        goto ret;
    }

    /* Now, compare what I think my AddrType is to that in the profile.
       If they are different, tell the spooler I'd like to be reloaded. */

    if (lpspvAddrType->ulPropTag == PR_SAMPLE_EMAIL_ADDR_TYPE)
    {
        if (lstrcmp(lpszAddrType, lpspvAddrType->Value.LPSZ))
        {
            hResult = lpMAPISup->lpVtbl->SpoolerNotify(lpMAPISup,
                NOTIFY_CONFIG_CHANGE, NULL);

            if (HR_FAILED(hResult))
            {
                DebugTrace("SpoolerNotify failed  in ValidateState.\n");
                goto ret;
            }
        }
    }

    hResult = hrSuccess;

ret:
    UlRelease(lpProf);

    lpxpl->FreeBuffer(lpPropArray);
    lpxpl->FreeBuffer(lpspvAddrType);

    DebugTraceResult(XPL_ValidateState, hResult);
    return hResult;
}


/*
 -  XPL_FlushQueues
 -
 *  Purpose:
 *      Logon object method used by Spooler if FlushQueues is called on
 *      the spooler status object.
 *
 *  Parameters:
 *      lpxpl               This pointer for logon object
 *      ulUIParam           Window handle
 *      cbTargetTransport   Count of bytes in Entryid. Zero.
 *      lpTargetTransport   Entryid of transport. NULL.
 *      ulFlags
 *
 *  Returns:
 *      (HRESULT)           E_INVALIDARG if object doesn't
 *                          look like a XPL; MAPI_E_NO_SUPPORT
 *                          otherwise.
 *
 *  Operation:
 *      Validate the object pointer. Return MAPI_E_NO_SUPPORT.
 */

STDMETHODIMP
XPL_FlushQueues(LPXPL lpxpl,
    ULONG ulUIParam,
    ULONG cbTargetTransport,
    LPENTRYID lpTargetTransport,
    ULONG ulFlags)
{
    HRESULT hResult;

    /*  Validate the object */

    /*  If it doesn't seem to be an object or refcount is zero, return zero */

    if (IsBadReadPtr(lpxpl, sizeof(XPL)) ||
        lpxpl->lcInit == 0 ||
        lpxpl->lpMySession != lpxpl)
    {
        DebugTraceSc(XPL_FlushQueues, E_INVALIDARG);
        return ResultFromScode(E_INVALIDARG);
    }

    /*  There is nothing special the sample transport
        needs to do before signaling its readiness for
        flushing */

    /*  Update our status row to inform the spooler
        that we are ready for flushing */

    if (ulFlags & FLUSH_UPLOAD)
        lpxpl->ulTransportStatus |= STATUS_OUTBOUND_FLUSH;
    if (ulFlags & FLUSH_DOWNLOAD)
        lpxpl->ulTransportStatus |= STATUS_INBOUND_FLUSH;

    hResult = HrUpdateTransportStatus(lpxpl, 0L);

    DebugTraceResult(XPL_FlushQueues, hResult);
    return hResult;
}


/*
 -  FIsValidSession
 -
 *  Purpose:
 *      Called from several places in the Transport to verify a session.
 *
 *  Parameters:
 *      lpxpl               handle which is to be confirmed
 *
 *  Returns:
 *      (BOOL)              TRUE if a valid session, FALSE if not.
 *
 *  Operation:
 *      Get the critical section, look for lpxpl in the session list,
 *      release the critical section, return boolean result.
 */

BOOL
FIsValidSession(LPXPL lpxpl)
{
    LPXPL lpxplT;
    LPXPP lpxpp;
    BOOL fIsValid = FALSE;

    /*  First make sure that it can possibly be a session; then
        Take advantage of the internal consistency check ... does
        it point to itself? then validate the parent XPP. */

    if ((IsBadWritePtr(lpxpl, sizeof(XPL))) ||
        (lpxpl->lpMySession != lpxpl) ||
        (IsBadWritePtr(lpxpl->lpxppParent, sizeof(XPP))))
        return FALSE;

    /*  Maybe it's a session ... see if it's in the list.
        Lock out session data structure during the check. */

    lpxpp = lpxpl->lpxppParent;
    EnterCriticalSection(&lpxpp->csTransport);

    /*  Look in the session list for the session */

    lpxplT = lpxpp->XPSessionList;

    while (lpxplT)
    {
        if (lpxplT == lpxpl)
        {
            fIsValid = TRUE;
            break;
        }
        lpxplT = lpxplT->lpNextSession;
    }

    /*  Release the critical section and return the result. */

    LeaveCriticalSection(&lpxpp->csTransport);

    return fIsValid;
}


/*
 -  CleanupSession
 -
 *  Purpose:
 *      Called from TransportLogoff() and error cases of TransportLogon()
 *      to cleanup session data.
 *
 *  Parameters:
 *      lpxpl           handle which is to be confirmed
 *
 *  Returns:
 *      none.
 *
 *  Operation:
 *      Close any open search handles, deallocate associated structures.
 *      We assume that if we need the critical section, we already have it.
 */

static void
CleanupSession(LPXPL lpxpl)
{
    LPMAPISUP lpMAPISup = lpxpl->lpMAPISup;
    BOOL fRefSupport = lpxpl->fRefSupport;

    /* Get rid of any open handle hanging around from Poll() or
    StartMessage() */

    if (lpxpl->hInFindHandle != INVALID_HANDLE_VALUE)
        CloseHandle(lpxpl->hInFindHandle);

    if (lpxpl->hOutFindHandle != INVALID_HANDLE_VALUE)
        CloseHandle(lpxpl->hOutFindHandle);

    /* OK, Deallocate the memory. */

    /* Session User Display Name and Entry-ID */

    if (lpxpl->lpMyIDArray)
    {
        lpxpl->FreeBuffer(lpxpl->lpMyIDArray[0].Value.bin.lpb);
        lpxpl->FreeBuffer(lpxpl->lpMyIDArray);
    }

    /* Free the session property array */

    lpxpl->FreeBuffer(lpxpl->lpPropArray);

    /* Free the Message OptionData struct */

    lpxpl->FreeBuffer(lpxpl->lpOptData);

    /* Release() the support object if need be. Do this last,
       since it could cause spooler to call XPP_Release. */

    if (fRefSupport)
        lpMAPISup->lpVtbl->Release(lpMAPISup);
}


/*
 -  lpxpp->lpVtbl->QueryInterface
 -
 *  Purpose:
 *
 *  Parameters:
 *      lpxpp               Pointer to object
 *      lpiid               New interface to Query to
 *      lppUnk              Where to store pointer to new object
 *
 *  Returns:
 *      (SCODE)             E_INVALIDARG if the input
 *                          object doesn't look like a XPP;
 *                          E_INVALIDARG if the IID
 *                          isn't readable or lppNewObj isn't
 *                          writable; E_NOINTERFACE
 *                          if we don't know the IID.
 *
 *  Operation:
 *      Validate parameters. See if the caller wants IUnknown or IXPProvider.
 *      If so, increment the usage count and return a new object.
 */

STDMETHODIMP
XPP_QueryInterface(LPXPP lpxpp,
    REFIID lpiid,
    LPVOID FAR * lppUnk)
{
    /*  Validate the parameters: 1) Does it seem to be an object?
        2) is the refcount nonzero? 3) Is there enough there for
        an interface ID? 4) Is there enough there for a new object? */

    if ((IsBadWritePtr(lpxpp, sizeof(XPP))) ||
        (lpxpp->lcInit == 0) ||
        (lpxpp->lpxppMyAddress != lpxpp) ||
        (IsBadReadPtr(lpiid, sizeof(IID))) ||
        (IsBadWritePtr(lppUnk, sizeof(LPXPP))))
    {
        DebugTraceSc(XPP_QueryInterface, E_INVALIDARG);
        return ResultFromScode(E_INVALIDARG);
    }

    /*  See if the requested interface is one of ours */

    if (memcmp(lpiid, &IID_IUnknown, sizeof(IID)) &&
        memcmp(lpiid, &IID_IXPProvider, sizeof(IID)))
    {
        *lppUnk = NULL;         /* OLE requires zeroing [out] parameters */
        DebugTraceSc(XPP_QueryInterface, E_NOINTERFACE);
        return ResultFromScode(E_NOINTERFACE);
    }

    /*  We'll do this one. Bump the usage count and return a new pointer. */

    ++lpxpp->lcInit;
    *lppUnk = lpxpp;

    return hrSuccess;
}


/*
 -  lpxpp->lpVtbl->AddRef
 -
 *  Purpose:
 *      Increment reference count if nonzero.
 *
 *  Parameters:
 *      lpxpp               Pointer to object (should be XPP)
 *
 *
 *  Returns:
 *      (ULONG)             Current reference count or zero if
 *                          it doesn't seem to be XPP.
 *
 *  Operation:
 *      Make sure it looks like a XPP, and if so, bump the reference count
 *      and return the result to the caller.
 */

STDMETHODIMP_(ULONG)
XPP_AddRef(LPXPP lpxpp)
{
    /*  If it doesn't seem to be an object or refcount is zero, return zero */

    if (IsBadWritePtr(lpxpp, sizeof(XPP)) ||
        lpxpp->lcInit == 0 ||
        lpxpp->lpxppMyAddress != lpxpp)
        return 0;

    return ++lpxpp->lcInit;
}


/*
 -  lpxpp->lpVtbl->Release
 -
 *  Purpose:
 *      Decrement lcInit. If it's zero, release the object.
 *
 *  Parameters:
 *      lpxpp               Pointer to object (should be XPP)
 *
 *  Returns:
 *      (ULONG)             Current reference count or zero if
 *                                  it doesn't seem to be XPP.
 *
 *  Operation:
 *      Make sure it looks like a XPP, and if so, decrement the reference
 *      count. If the count is now zero, deallocate the object.
 *
 *      Return the reference count to the caller.
 */

STDMETHODIMP_(ULONG)
XPP_Release(LPXPP lpxpp)
{
    /*  If it doesn't seem to be an object or refcount is zero, return zero */

    if (IsBadWritePtr(lpxpp, sizeof(XPP)) ||
        lpxpp->lcInit == 0 ||
        lpxpp->lpxppMyAddress != lpxpp)
        return 0;

    --lpxpp->lcInit;

    if (lpxpp->lcInit == 0)
    {
        ULONG ulT;

        DebugTrace("XPP_Release() freeing XPP.\n");

        /* If we've inited and not deinited, do it now */

        if (lpxpp->fInited)
        {
            ulT = DEINIT_HURRY;
            lpxpp->lpVtbl->Shutdown(lpxpp, &ulT);
        }

        lpxpp->lpVtbl = NULL;
        (*lpxpp->lpFreeBuffer) (lpxpp);
        return 0;
    }

    return lpxpp->lcInit;
}


/*
 -  lpxpl->lpVtbl->QueryInterface
 -
 *  Purpose:
 *
 *  Parameters:
 *      lpxpl               Pointer to object
 *      lpiid               New interface to Query to
 *      lppUnk              Where to store pointer to new object
 *
 *  Returns:
 *      (SCODE)             E_INVALIDARG if the input
 *                          object doesn't look like a XPL;
 *                          E_INVALIDARG if the IID
 *                          isn't readable or lppNewObj isn't
 *                          writable; E_NOINTERFACE
 *                          if we don't know the IID.
 *
 *  Operation:
 *      Validate parameters. See if the caller wants IUnknown or IXPLogon.
 *      If so, increment the usage count and return a new object.
 */

STDMETHODIMP
XPL_QueryInterface(LPXPL lpxpl,
    REFIID lpiid,
    LPVOID FAR * lppUnk)
{
    /*  Validate the parameters: 1) Does it seem to be an object?
        2) is the refcount nonzero? 3) Is there enough there for
        an interface ID? 4) Is there enough there for a new object? */

    if ((IsBadWritePtr(lpxpl, sizeof(XPL))) ||
        (lpxpl->lcInit == 0) ||
        (lpxpl->lpMySession != lpxpl) ||
        (IsBadReadPtr(lpiid, sizeof(IID))) ||
        (IsBadWritePtr(lppUnk, sizeof(LPXPL))))
    {
        DebugTraceSc(XPL_QueryInterface, E_INVALIDARG);
        return ResultFromScode(E_INVALIDARG);
    }

    /*  See if the requested interface is one of ours */

    if (memcmp(lpiid, &IID_IUnknown, sizeof(IID)) &&
        memcmp(lpiid, &IID_IXPLogon, sizeof(IID)))
    {
        *lppUnk = NULL;         /* OLE requires zeroing [out] parameters */
        DebugTraceSc(XPL_QueryInterface, E_NOINTERFACE);
        return ResultFromScode(E_NOINTERFACE);
    }

    /*  We'll do this one. Bump the usage count and return a new pointer. */

    ++lpxpl->lcInit;
    *lppUnk = lpxpl;

    return hrSuccess;
}


/*
 -  lpxpl->lpVtbl->AddRef
 -
 *  Purpose:
 *      Increment reference count if nonzero.
 *
 *  Parameters:
 *      lpxpl               Pointer to object (should be XPL)
 *
 *  Returns:
 *      (ULONG)             Current reference count or zero if
 *                          it doesn't seem to be XPL.
 *
 *  Operation:
 *      Make sure it looks like a XPL, and if so, bump the reference count
 *      and return the result to the caller.
 */

STDMETHODIMP_(ULONG)
XPL_AddRef(LPXPL lpxpl)
{
    /*  If it doesn't seem to be an object or refcount is zero, return zero */

    if (IsBadWritePtr(lpxpl, sizeof(XPL)) ||
        lpxpl->lcInit == 0 ||
        lpxpl->lpMySession != lpxpl)
        return 0;

    return ++lpxpl->lcInit;
}


/*
 -  lpxpl->lpVtbl->Release
 -
 *  Purpose:
 *      Decrement lcInit. If it's zero, release the object.
 *
 *  Parameters:
 *      lpxpl               Pointer to object (should be XPL)
 *
 *  Returns:
 *      (ULONG)             Current reference count or zero if
 *                          it doesn't seem to be XPL.
 *
 *  Operation:
 *      Make sure it looks like a XPL, and if so, decrement the reference
 *      count. If the count is now zero, deallocate the object.
 *
 *      Return the reference count to the caller.
 */

STDMETHODIMP_(ULONG)
XPL_Release(LPXPL lpxpl)
{
    /*  If it doesn't seem to be an object or refcount is zero, return zero */

    if (IsBadWritePtr(lpxpl, sizeof(XPL)) ||
        lpxpl->lcInit == 0 ||
        lpxpl->lpMySession != lpxpl)
        return 0;

    --lpxpl->lcInit;

    if (lpxpl->lcInit == 0)
    {
        DebugTrace("XPL_Release() freeing XPL.\n");

        /* Ignore return code; we're going away reguardless! */

        XPL_TransportLogoff(lpxpl, LOGOFF_HURRY);
        lpxpl->lpVtbl = NULL;
        (*lpxpl->FreeBuffer) (lpxpl);

        return 0;
    }

    return lpxpl->lcInit;
}


/*
 -  ScCheckLogonProps
 -
 *  Purpose:
 *      Looks at the properties returned from the XP Logon property
 *      sheet and does some 'lite' validation of the values.  Users
 *      of this function must accept the symantics associated with
 *      the three possible return values.  That is, if the caller
 *      is displaying UI and MAPI_E_INVALID_PARAMETER is returned
 *      then the UI must be re-displayed.  If the caller is NOT
 *      displaying UI and MAPI_E_UNCONFIGURED is returned then
 *      they should pass this error back up the call stack, as MAPI
 *      will call the Service Entry point to get this info.
 *      MAPI_E_USER_CANCEL will only be returned if UI is allowed,
 *      in which case this should be treated the same a when the
 *      user presses <Cancel> in the Logon dialog.
 *
 *  Parameters:
 *      lpXPDialog          - Contains everything I need
 *      fUIAllowed          - Indicates if MessageBox's are allowed
 *
 *  Returns:
 *      S_OK                        - All data appears valid
 *      MAPI_E_USER_CANCEL          - Bad data and the user wants to abort
 *      MAPI_E_UNCONFIGURED         - Bad data and the user wants to try again
 */

SCODE
ScCheckLogonProps(LPXPDLG lpXPDialog, BOOL fUIAllowed)
{
    SCODE sc = MAPI_E_UNCONFIGURED;
    LPTSTR lpszT = NULL;
    HINSTANCE hInst = lpXPDialog->hInst;
    HWND hWnd = lpXPDialog->hwnd;
    LPSPropValue lpProps = *(lpXPDialog->lppPropArray);
    HANDLE hf = INVALID_HANDLE_VALUE;
    ULONG ulT;
    BOOL fDeleteFile = FALSE;
    LPTSTR szFuBar = TEXT("fubar");
    TCHAR szFooUNC[MAX_PATH];
    TCHAR szFooPath[MAX_PATH];
    UINT ids = 0;
    LONG lFlags;

#ifdef _WINNT
    ULONG cb;
    TCHAR szBuff[16];
#endif  /* _WINNT */

    /* Check Display Name */

    lpszT = ArrayIndex(PR_SAMPLE_DISPLAY_NAME, lpProps).Value.LPSZ;

    if (PROP_TYPE(ArrayIndex(PR_SAMPLE_DISPLAY_NAME, lpProps).ulPropTag) == PT_ERROR ||
        !lpszT || (*lpszT == '\0'))
    {
        ids = IDS_NO_DISPLAY_NAME;
        goto ret;
    }

    /* Check Address Type */

    lpszT = ArrayIndex(PR_SAMPLE_EMAIL_ADDR_TYPE, lpProps).Value.LPSZ;

    if (PROP_TYPE(ArrayIndex(PR_SAMPLE_EMAIL_ADDR_TYPE, lpProps).ulPropTag) == PT_ERROR ||
        !lpszT || (*lpszT == '\0'))
    {
        ids = IDS_NO_ADDR_TYPE;
        goto ret;
    }

    /* Check Email Address */

    lpszT = ArrayIndex(PR_SAMPLE_EMAIL_ADDRESS, lpProps).Value.LPSZ;

    if (PROP_TYPE(ArrayIndex(PR_SAMPLE_EMAIL_ADDRESS, lpProps).ulPropTag) == PT_ERROR ||
        !lpszT || (*lpszT == '\0'))
    {
        ids = IDS_NO_EMAIL_ADDRESS;
        goto ret;
    }

    /* Save this, we'll need it later */

    lstrcpy(szFooUNC, lpszT);

    if (szFooUNC[lstrlen(szFooUNC)-1] != '\\')
        lstrcat(szFooUNC, TEXT("\\"));

    lstrcat(szFooUNC, TEXT("foo.txt"));

    /* Check Inbound Directory */

    lpszT = ArrayIndex(PR_SAMPLE_INBOUND_DIR, lpProps).Value.LPSZ;

    if (PROP_TYPE(ArrayIndex(PR_SAMPLE_INBOUND_DIR, lpProps).ulPropTag) == PT_ERROR ||
        !lpszT || (*lpszT == '\0'))
    {
        ids = IDS_NO_INBOUND_DIR;
        goto ret;
    }

    lstrcpy(szFooPath, lpszT);

    if (szFooPath[lstrlen(szFooPath)-1] != '\\')
        lstrcat(szFooPath, TEXT("\\"));

    lstrcat(szFooPath, TEXT("foo.txt"));

    /* Check Outbound Directory */

    lFlags = ArrayIndex(PR_SAMPLE_FLAGS, lpProps).Value.l;

    if (PROP_TYPE(ArrayIndex(PR_SAMPLE_FLAGS, lpProps).ulPropTag) == PT_ERROR ||
        !(lFlags & PR_SAMPLE_FLAG_PEER_TO_PEER))
    {
        lpszT = ArrayIndex(PR_SAMPLE_OUTBOUND_DIR, lpProps).Value.LPSZ;

        if (!lpszT || (*lpszT == '\0'))
        {
            ids = IDS_NO_OUTBOUND_DIR;
            goto ret;
        }
    }


#ifdef _WINNT

    /* Do a little loop-back test to validate PR_SAMPLE_EMAIL_ADDRESS
       and PR_SAMPLE_INBOUND_DIR point to the same place and are valid.
       The WFW and Windows 95 Redirector can't talk to itself, so we only
       do this on NT.  Shouldn't be done on platforms whose redirector
       cannot do the loop-back thang. */

    if ((hf = CreateFile(szFooUNC, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
                FILE_FLAG_WRITE_THROUGH, NULL)) == INVALID_HANDLE_VALUE)
    {
        ids = IDS_BAD_EMAIL_ADDRESS;
        goto ret;
    }

    if (!WriteFile(hf, szFuBar, lstrlen(szFuBar), &cb, NULL))
    {
        ids = IDS_BAD_EMAIL_ADDRESS;
        goto ret;
    }

    CloseHandle(hf);

    fDeleteFile = TRUE;

    /* Now, read the file */

    if ((hf = CreateFile(szFooPath, GENERIC_READ, 0, NULL, OPEN_EXISTING,
                FILE_ATTRIBUTE_READONLY, NULL)) == INVALID_HANDLE_VALUE)
    {
        ids = IDS_BAD_INBOUND_DIR;
        goto ret;
    }

    if (!ReadFile(hf, szBuff, lstrlen(szFuBar), &cb, NULL))
    {
        ids = IDS_BAD_INBOUND_DIR;
        goto ret;
    }

    szBuff[lstrlen(szFuBar)] = '\0';

    CloseHandle(hf);
    hf = INVALID_HANDLE_VALUE;

    if (lstrcmp(szFuBar, szBuff))
    {
        ids = IDS_UNC_DIR_MISMATCH;
        goto ret;
    }

#endif  /* _WINNT */

    /*  If there's a high water mark, make sure there's a low water
        mark at least 1K less than high water and no more than 32K. */

    ulT = ArrayIndex(PR_SAMPLE_LOGHIGHWATER, lpProps).Value.ul;
    if (PROP_TYPE(ArrayIndex(PR_SAMPLE_LOGHIGHWATER, lpProps).ulPropTag) == PT_ERROR ||
        ulT)
    {
        /* It looks like we'll be doing size adjustment. See what
        the current "low water" mark is. */

        ULONG ulLow;

        ulLow = ArrayIndex(PR_SAMPLE_LOGLOWWATER, lpProps).Value.ul;

        /* Make sure it's not more than 32K. If so, trim it down. */

        if (ulLow > 32)
            ulLow = 32;

        /* Make sure there's at least 1K between high and low water. If
        not, increase high water mark to satisfy this. */

        if (ulLow > (ulT - 1))
            ulT = ulLow + 1;

        /* Save this stuff into the logon property array. */

        ArrayIndex(PR_SAMPLE_LOGLOWWATER, lpProps).Value.ul = ulLow;
        ArrayIndex(PR_SAMPLE_LOGHIGHWATER, lpProps).Value.ul = ulT;
    }

    sc = S_OK;

ret:
    if (fDeleteFile)
        DeleteFile(szFooUNC);

    if (hf != INVALID_HANDLE_VALUE)
        CloseHandle(hf);

    /*  OK, the following block goes something like this:
        We initialized sc to MAPI_E_UNCONFIGURED at the top
        and only set it to S_OK if we make it all the way through
        the validation stuff.  If, along the way, we find bad data
        we set ids to the appropriate error string (this is Assert'd
        below).  Then, if UI is allowed, we get a bunch of string
        resources via LoadString and format an error message that
        will be displayed in a MessageBox.  If we are running the
        debug version of the transport, then the MessageBox will
        have an Abort/Retry/Ignore button selection, else, it will
        only have a Yes/No button selection.  These buttons carry
        with them the following meaning:

        DEBUG
            Abort   Return MAPI_E_USER_CANCEL; causes Logon to fail;
                    indicates that data is not to be saved in the profile.

            Retry   Return MAPI_E_UNCONFIGURED; re-display
                    Logon UI so user can fix problem.

            Ignore  Return S_OK; we accept the data as is and will
                    write it into the profile (if asked to save).

        !DEBUG
            Yes     Same as Retry above.

            No      Same as Abort above.

        Since we are using MessageBox for our error dialog, we are
        limited to this confusing choice of buttons.
    */

    if (FAILED(sc) && fUIAllowed)
    {
        TCHAR szErrTitle[64];
        TCHAR szErrFormat[128];
        TCHAR szErrStr[128];
        TCHAR szErrMsg[256];
        UINT fuButtons = MB_ICONEXCLAMATION | MB_SETFOREGROUND;
        int rc;

        Assert(ids);

        if (!LoadString(hInst, ids, szErrStr, sizeof(szErrStr) - 1) ||
            !LoadString(hInst, IDS_BAD_LOGON_PROPS_TITLE,
                        szErrTitle, sizeof(szErrTitle) - 1) ||
            !LoadString(hInst, IDS_BAD_LOGON_PROPS_FORMAT,
                        szErrFormat, sizeof(szErrFormat) - 1))
        {
            DebugTrace("Unable to do a LoadString in ScCheckLogonProps.\n");
            return sc;
        }

        wsprintf(szErrMsg, szErrFormat, szErrStr);

#ifdef DEBUG
        fuButtons |= MB_ABORTRETRYIGNORE;
#else
        fuButtons |= MB_YESNO;
#endif

        rc = MessageBox(hWnd, szErrMsg, szErrTitle, fuButtons);

        if (rc == IDRETRY || rc == IDYES)
            sc = MAPI_E_UNCONFIGURED;
        else if (rc == IDABORT || rc == IDNO)
            sc = MAPI_E_USER_CANCEL;
        else
            sc = S_OK;
    }

    return sc;
}


/*
 -  HrCheckSpoolerYield
 -
 *  Purpose:
 *      Used to enforce the .2 second rule.  Called periodically while
 *      processing a message to determine if we have used more than .2
 *      seconds.  If so, then call SpoolerYield(), else just continue.
 *      This is called with fReset set to TRUE when we first enter one
 *      of the Transport Logon methods (usually one that is known to
 *      take a long time like StartMessage() or SubmitMessage(). )
 *
 *  Parameters:
 *      lpMAPISup           - The Transports support object
 *      fReset              - Sets dwStart to current TickCount and returns
 *
 */

HRESULT
HrCheckSpoolerYield(LPMAPISUP lpMAPISup, BOOL fReset)
{
    HRESULT hr = hrSuccess;
    DWORD dwStop;
    static DWORD dwStart;

    if (fReset)
    {
        dwStart = GetTickCount();
        return hr;
    }

    dwStop = GetTickCount();

    if ((dwStop - dwStart) > 200)
    {
        hr = lpMAPISup->lpVtbl->SpoolerYield(lpMAPISup, 0);
        dwStart = GetTickCount();
    }

    return hr;
}

/*
 -  ScCopySessionProps
 -
 *  Purpose:
 *      Used to make a working copy of the session properties associated
 *      with a particular logon object.  This is done to protect us from
 *      having our data change out from under us due to a call to some
 *      transport UI.  This is done instead of mutexing to avoid the chance
 *      of deadlock conditions and to avoid having to create an elaborate
 *      mutex object that suits our special needs.
 *
 *  Parameters:
 *      lpxpl               - The Transports logon object
 *      lppPropArray        - Receives the new PropArray set
 *      lppMyIdArray        - Receives the new IdArray
 */

SCODE
ScCopySessionProps(
    LPXPL lpxpl,
    LPSPropValue FAR * lppPropArray,
    LPSPropValue FAR * lppMyIDArray)
{
    SCODE sc = S_OK;
    ULONG cProps;
    LPSPropValue lpPropArray = lpxpl->lpPropArray;
    LPSPropValue lpMyIDArray = lpxpl->lpMyIDArray;
    LPALLOCATEBUFFER lpAllocBuff = lpxpl->AllocateBuffer;

    if (lppPropArray)
    {
        cProps = MAX_LOGON_PROPERTIES - TEMP_LOGON_PROPERTIES;

        sc = ScDupPropset((int)cProps, lpPropArray, lpAllocBuff, lppPropArray);

        if (FAILED(sc))
            goto ret;
    }

    if (lppMyIDArray)
    {
        cProps = NUM_SENDER_PROPS;

        sc = ScDupPropset((int)cProps, lpMyIDArray, lpAllocBuff, lppMyIDArray);

        if (FAILED(sc) && lppPropArray)
        {
            lpxpl->FreeBuffer(*lppPropArray);
            *lppPropArray = NULL;
        }
    }

ret:
    return sc;
}

/*
 -  ServiceEntry
 -
 *  Purpose:
 *      This is the service entry point for the MAPI Configuration
 *      application.  This function uses the XP Logon dialog to allow
 *      the user to configure the provider.  If asked to, through the
 *      UI, the new settings will be saved in the profile.
 *
 *  Parameters:
 *      hInstance           [IN] Instance handle of the calling process
 *      lpMalloc            [IN] OLE style allocator to be used by PropSheet.
 *      lpMAPISup           [IN] MAPI Support object - used to get memory
 *                          allocators, BuildDisplayTable, etc.
 *      ulUIParam           [IN] hWnd of the caller who is parent of my UI.
 *      ulFlags             [IN] UI_SERVICE indicates that the caller wants
 *                          UI to help in configuring this provider.
 *                          MSG_SERVICE_UI_READ_ONLY indicates the caller
 *                          does not want write access to the configuration
 *                          property sheet.  No other flags are supported.
 *      ulContext           [IN] MSG_SERVICE_DELETE, MSG_SERVICE_INSTALL, and
 *                          MSG_SERVICE_UNINSTALL are noops and simply return
 *                          hrSuccess.  MSG_SERVICE_CONFIGURE and
 *                          MSG_SERVICE_CREATE allow the caller to create
 *                          or update the Logon properties in this providers
 *                          profile section.
 *      cValues             [IN] The caller may supply an array of property
 *                          values to configure this provider with.  This is
 *                          the number of values found in the array.
 *      lpProps             [IN] Caller supplied configuration properties.
 *      lpAdminProviders    [IN] An IProviderAdmin object used to retrieve a
 *                          ProfileSection object for this provider.
 *      lppMapiError        [OUT] Extended error information optionally
 *                          returned when the call fails.
 */

HRESULT STDAPICALLTYPE
ServiceEntry(
    HINSTANCE hInstance,
    LPMALLOC lpMalloc,
    LPMAPISUP lpMAPISup,
    ULONG ulUIParam,
    ULONG ulFlags,
    ULONG ulContext,
    ULONG cValues,
    LPSPropValue lpProps,
    LPPROVIDERADMIN lpAdminProviders,
    LPMAPIERROR FAR *lppMapiError)
{
    SCODE sc = S_OK;
    HRESULT hResult = hrSuccess;
    ULONG ulT;
    ULONG ulCount = 0;
    LPSPropValue lpPropArray = NULL;
    LPSPropValue lpLogonProps = NULL;
    LPALLOCATEBUFFER lpAllocBuff;
    LPALLOCATEMORE lpAllocMore;
    LPFREEBUFFER lpFreeBuff;
    LPPROFSECT lpProfileObj = NULL;
    XPDLG XPDialog;
    BOOL fNeedUI = FALSE;
    BOOL fAllowUI = FALSE;
    BOOL fInitialParamsOk = TRUE;

    /* Validate parameters */
    //$BUG: No parameter checking....

    /* Check the Support Object */

    if (FBadUnknown(lpMAPISup))
    {
        DebugTraceSc(Bad lpMAPISup in XP ServiceEntry, E_INVALIDARG);
        return ResultFromScode(E_INVALIDARG);
    }

    /* Check for context */

    if ((ulContext == MSG_SERVICE_DELETE) ||
        (ulContext == MSG_SERVICE_INSTALL) ||
        (ulContext == MSG_SERVICE_UNINSTALL))
        return hrSuccess;

    if (ulContext != MSG_SERVICE_CONFIGURE && ulContext != MSG_SERVICE_CREATE)
    {
        DebugTraceSc(ServiceEntry unsupported context, MAPI_E_NO_SUPPORT);
        return ResultFromScode(MAPI_E_NO_SUPPORT);
    }

    if ( ulFlags & MAPI_UNICODE )
    {
        DebugTraceSc(ServiceEntry Bad character width, MAPI_E_BAD_CHARWIDTH);
        return ResultFromScode(MAPI_E_BAD_CHARWIDTH);
    }

    /* Check for UI */

    if (ulFlags & SERVICE_UI_ALWAYS)
        fAllowUI = fNeedUI = TRUE;
    else
        if (ulFlags & SERVICE_UI_ALLOWED)
            fAllowUI = TRUE;

    if (ulFlags & MSG_SERVICE_UI_READ_ONLY)
        ulFlags = UI_READONLY;

    /* Get the memory allocation routines we'll be needing. */

    hResult = lpMAPISup->lpVtbl->GetMemAllocRoutines(lpMAPISup,
        &lpAllocBuff, &lpAllocMore, &lpFreeBuff);

    if (hResult)
    {
        DebugTrace("GetMemAllocRoutines failed in ServiceEntry.\n");
        goto ret;
    }

    /* Open the Profile Section for this Transport Provider. */

    hResult = HrOpenSingleProvider(lpAdminProviders, &lpProfileObj);

    if (hResult)
    {
        DebugTrace("Unable to open the profile.\n");
        goto ret;
    }

    /* Profile is open, get the properties out of it. */

    hResult = lpProfileObj->lpVtbl->GetProps(lpProfileObj,
        (LPSPropTagArray) &sptLogonArray, ulFlags & MAPI_UNICODE, &ulCount, &lpPropArray);

    if (HR_FAILED(hResult))
    {
        DebugTrace("GetProps failed in XP ServiceEntry.\n");
        goto ret;
    }

    hResult = hrSuccess;

    /*  If the user passed in a property array to configure our profile
        with, then we'll merge this array with that from the profile
        section.  This merged array will, conditionally, be used in our
        Logon UI and, conditionally,  written out to the profile section.
        Also, lpLogonProps becomes our alias for the array no matter where
        the properties come from. */

    if (lpProps)
    {
        sc = ScMergeLogonProps(cValues, lpProps, ulCount,
            lpPropArray, lpAllocBuff, lpAllocMore, &lpLogonProps);

        if (FAILED(sc))
        {
            hResult = ResultFromScode(sc);
            DebugTrace("ScMergeLogonProps failed in XP ServiceEntry.\n");
            goto ret;
        }
    }
    else
    {
        lpLogonProps = lpPropArray;
        lpPropArray = NULL;
    }

    Assert(ulCount == MAX_LOGON_PROPERTIES);
    ulCount -= TEMP_LOGON_PROPERTIES;

    /* Find out if the stored SAMPLE_FLAGS say we should have UI.
       But, only if we aren't already forcing UI to be presented. */

    if (fAllowUI && !fNeedUI && lpLogonProps)
    {
        if ((ArrayIndex(PR_SAMPLE_FLAGS, lpLogonProps).ulPropTag == PR_SAMPLE_FLAGS) &&
            (ArrayIndex(PR_SAMPLE_FLAGS, lpLogonProps).Value.l & PR_SAMPLE_FLAG_UI_ALWAYS))
                fNeedUI = TRUE;
    }

    /* Fill in the logon UI structure */

    XPDialog.hInst = hInstance;
    XPDialog.hwnd = (HWND) ulUIParam;
    XPDialog.lppPropArray = &lpLogonProps;
    XPDialog.lpPTArray = (LPSPropTagArray) &sptLogonArray;
    XPDialog.AllocateBuffer = lpAllocBuff;
    XPDialog.AllocateMore = lpAllocMore;
    XPDialog.FreeBuffer = lpFreeBuff;
    XPDialog.lpMalloc = lpMalloc;
    XPDialog.lpMAPISup = lpMAPISup;
    XPDialog.fLogon = TRUE;
    XPDialog.ulFlags = ulFlags;

    /* Check the logon props BEFORE the dialog call, as the props will
       be freed if Cancel is selected, and we will want to know if the
       provider configuration information was valid */

    sc = ScCheckLogonProps(&XPDialog, FALSE);
    if ((sc == MAPI_E_USER_CANCEL) || (sc == MAPI_E_UNCONFIGURED))
    {
        if (fAllowUI)
        {
            fNeedUI = TRUE;
            fInitialParamsOk = FALSE;
        }
        else
            goto ret;
    }

    while (fAllowUI && fNeedUI)
    {
        sc = ScDoLogonDlg(&XPDialog);

        if (FAILED(sc))
        {
            hResult = ResultFromScode(sc);

            if (sc != MAPI_E_USER_CANCEL)
            {
                DebugTrace("ScDoLogonDlg failed in XP ServiceEntry.\n");
            }
            else
                if (!fInitialParamsOk)
                    hResult = ResultFromScode(MAPI_E_UNCONFIGURED);

            goto ret;
        }

        if (!lpLogonProps)
        {
            hResult = ResultFromScode(MAPI_E_CALL_FAILED);
            DebugTrace("No Logon Props returned in XP ServiceEntry.\n");
            goto ret;
        }

        /* Got a prop array, make sure everything in it is good */

        for (ulT = 0; ulT < ulCount; ulT++)
        {
            if (PROP_TYPE((lpLogonProps)[ulT].ulPropTag) == PT_ERROR)
            {
                hResult = ResultFromScode(MAPI_E_UNCONFIGURED);
                DebugTrace("Property %x not available, returning MAPI_E_UNCONFIGURED\n", PROP_ID((lpLogonProps)[ulT].ulPropTag));
                goto ret;
            }
        }

        /* Do some simple validation of the Logon Props */

        sc = ScCheckLogonProps(&XPDialog, TRUE);

        if (sc == MAPI_E_USER_CANCEL)
            goto ret;
        else if (sc == MAPI_E_UNCONFIGURED)
            continue;
        else
            fNeedUI = FALSE;
    }

    /*  If the user passed in properties and didn't request UI, then
        we need to check the array of Logon Props now.  If they are
        bad, then we'll simply return an error. */

    if (lpProps && !(ulFlags & SERVICE_UI_ALWAYS))
    {
        if (sc = ScCheckLogonProps(&XPDialog, FALSE))
        {
            hResult = ResultFromScode(sc);
            DebugTrace("User supplied properties did not pass validation.\n");
            goto ret;
        }
    }

    /*  If we get here, everything is fine and we can proceed. But first
        we should write the properties out if the user is willing. */

    ulT = ArrayIndex(PR_SAMPLE_FLAGS, lpLogonProps).ulPropTag;
    Assert(PROP_TYPE(ulT) != PT_ERROR);

    ulT = ArrayIndex(PR_SAMPLE_FLAGS, lpLogonProps).Value.ul;

    if (ulT & PR_SAMPLE_FLAG_SAVE_DATA)
    {
        hResult = lpProfileObj->lpVtbl->SetProps(lpProfileObj,
            ulCount, lpLogonProps, NULL);

        if (hResult)
        {
            DebugTrace("SetProps failed in XP ServiceEntry.\n");
            goto ret;
        }

        lpProfileObj->lpVtbl->SaveChanges(lpProfileObj, 0);
    }

ret:
    UlRelease(lpProfileObj);
    lpFreeBuff(lpPropArray);
    lpFreeBuff(lpLogonProps);

    DebugTraceResult(ServiceEntry, hResult);
    return hResult;
};


/*
 -  HrOpenSingleProvider
 -
 *  Purpose:
 *      Gets the IProfileSect object for a single provider from the
 *      ProviderTable in the IProviderAdmin object.  My entry in the
 *      table is supposed to be in the first row - this better be true.
 *
 */

HRESULT
HrOpenSingleProvider(LPPROVIDERADMIN lpAdminProviders,
    LPPROFSECT FAR * lppProfSect)
{
    HRESULT hResult;
    LPMAPITABLE lpTable = NULL;
    LPSRowSet lpRows = NULL;
    LPSPropValue lpProp;
    SPropTagArray sptaProvider = {1, {PR_PROVIDER_UID}};

    hResult = lpAdminProviders->lpVtbl->GetProviderTable(
        lpAdminProviders, 0, &lpTable);

    if (hResult)
        goto ret;

    hResult = lpTable->lpVtbl->SetColumns(lpTable, &sptaProvider, 0L);

    if (hResult)
        goto ret;

    hResult = lpTable->lpVtbl->QueryRows(lpTable, 1, 0, &lpRows);

    if (hResult || !lpRows || !lpRows->cRows)
    {
        hResult = ResultFromScode(MAPI_E_NOT_FOUND);
        goto ret;
    }

    Assert(lpRows->aRow[0].cValues == 1);
    lpProp = lpRows->aRow[0].lpProps;
    Assert(lpProp);
    Assert(lpProp->ulPropTag == PR_PROVIDER_UID);

    /* Found the right property; use it to open our section */

    hResult = lpAdminProviders->lpVtbl->OpenProfileSection(
        lpAdminProviders, (LPMAPIUID) lpProp->Value.bin.lpb,
        NULL, MAPI_MODIFY, lppProfSect);

ret:
    FreeProws(lpRows);
    UlRelease(lpTable);

    DebugTraceResult(HrOpenSingleProvider, hResult);
    return hResult;
}

/*
 -  ScMergeLogonProps
 -
 *  Purpose:
 *      This function merges a property array that the user passed into
 *      ServiceEntry with the property array of Transport Logon props
 *      found in the Profile.  This merged array is what either gets
 *      passed into the XP Logon dialog (in the case when UI is requested)
 *      or simply gets written out to the profile section for the
 *      Transport Provider.
 *
 *  Parameters:
 *      cProps1             - count of properties in the users array
 *      lpProps1            - the users property array
 *      cProps2             - count of properties from the XP profile
 *      lpProps2            - property array from the XP profile
 *      lpAllocBuff         - MAPI allocator used by ScDupPropset
 *      lppPropsDest        - receives the newly built prop array
 */

SCODE
ScMergeLogonProps(
    ULONG cProps1,
    LPSPropValue lpProps1,
    ULONG cProps2,
    LPSPropValue lpProps2,
    LPALLOCATEBUFFER lpAllocBuff,
    LPALLOCATEMORE lpAllocMore,
    LPSPropValue FAR * lppPropsDest)
{
    SCODE sc;
    ULONG ulTag;
    TCHAR szEmpty[1] = "";
    ULONG cT = cProps2;
    UINT cch;
    UINT id;
    LPTSTR lpszT;

    /*  If any of the properties that we tried to read from the
        profile didn't exist, then the profile provider would return
        them to us as type PT_ERROR.  We will convert these to either
        empty strings or zeros before we try to merge in the user
        supplied values.  This will allow us to do parameter validation
        on the properties even if the user didn't ask for UI. */

    while (cT--)
    {
        ulTag = lpProps2[cT].ulPropTag;

        if (PROP_TYPE(ulTag) == PT_ERROR)
        {
            id = (UINT)PROP_ID(ulTag);

            switch (id)
            {
            case (UINT)PROP_ID(PR_SAMPLE_DISPLAY_NAME):
            case (UINT)PROP_ID(PR_SAMPLE_EMAIL_ADDR_TYPE):
            case (UINT)PROP_ID(PR_SAMPLE_EMAIL_ADDRESS):
            case (UINT)PROP_ID(PR_SAMPLE_INBOUND_DIR):
            case (UINT)PROP_ID(PR_SAMPLE_OUTBOUND_DIR):
            case (UINT)PROP_ID(PR_SAMPLE_FILENAME):
            case (UINT)PROP_ID(PR_SAMPLE_DIRECTORY):
            case (UINT)PROP_ID(PR_SAMPLE_LOGFILE):
            case (UINT)PROP_ID(PR_TEMP_LOGHIGHWATER):
            case (UINT)PROP_ID(PR_TEMP_LOGLOWWATER):
                lpProps2[cT].ulPropTag = PROP_TAG(PT_TSTRING, id);
                lpProps2[cT].Value.LPSZ = szEmpty;
                break;

            case (UINT)PROP_ID(PR_SAMPLE_LOGHIGHWATER):
            case (UINT)PROP_ID(PR_SAMPLE_LOGLOWWATER):
            case (UINT)PROP_ID(PR_SAMPLE_FLAGS):
                lpProps2[cT].ulPropTag = PROP_TAG(PT_LONG, id);
                lpProps2[cT].Value.l = 0;
                break;

            case (UINT)PROP_ID(PR_TEMP_PEER_TO_PEER):
            case (UINT)PROP_ID(PR_TEMP_UI_ALWAYS):
            case (UINT)PROP_ID(PR_TEMP_LOG_EVENTS):
            case (UINT)PROP_ID(PR_TEMP_SAVE_DATA):
                lpProps2[cT].ulPropTag = PROP_TAG(PT_BOOLEAN, id);
                lpProps2[cT].Value.b = FALSE;
                break;

            default:
                DebugTrace("Got a bad PropTag in ScMergeLogonProps.\n");
            }
        }
    }

    /*  Now, replace the profile properties with those passed in by the
        user.  Check the ones of the type "File Path" to see that they
        have a slash as their last character.  If not, then add one. */

    while (cProps1--)
    {
        ulTag = lpProps1[cProps1].ulPropTag;

        switch (ulTag)
        {
            /* Do the String properties first */

        case PR_SAMPLE_INBOUND_DIR:
        case PR_SAMPLE_OUTBOUND_DIR:
        case PR_SAMPLE_DIRECTORY:
            if (lpProps1[cProps1].Value.LPSZ)
            {
                cch = lstrlen(lpProps1[cProps1].Value.LPSZ);

                if (cch && lpProps1[cProps1].Value.LPSZ[cch - 1] != '\\')
                {
                    sc = lpAllocMore((cch + 2) * sizeof(TCHAR),
                        lpProps2, (LPVOID FAR *) &lpszT);

                    if (!FAILED(sc))
                    {
                        lstrcpy(lpszT, lpProps1[cProps1].Value.LPSZ);
                        lpszT[cch] = '\\';
                        lpszT[cch + 1] = '\0';
                        ArrayIndex(ulTag, lpProps2).Value.LPSZ = lpszT;
                    }
                }
                else
                    ArrayIndex(ulTag, lpProps2).Value.LPSZ = lpProps1[cProps1].Value.LPSZ;
            }
            else
                ArrayIndex(ulTag, lpProps2).Value.LPSZ = szEmpty;

            break;

        case PR_SAMPLE_DISPLAY_NAME:
        case PR_SAMPLE_EMAIL_ADDR_TYPE:
        case PR_SAMPLE_EMAIL_ADDRESS:
        case PR_SAMPLE_FILENAME:
        case PR_SAMPLE_LOGFILE:
            if (lpProps1[cProps1].Value.LPSZ)
                ArrayIndex(ulTag, lpProps2).Value.LPSZ = lpProps1[cProps1].Value.LPSZ;
            else
                ArrayIndex(ulTag, lpProps2).Value.LPSZ = szEmpty;

            break;

            /* Then the long values */

        case PR_SAMPLE_LOGHIGHWATER:
        case PR_SAMPLE_LOGLOWWATER:
        case PR_SAMPLE_FLAGS:
            ArrayIndex(ulTag, lpProps2).Value.l = lpProps1[cProps1].Value.l;
            break;

            /* We have a bad value, lets return an error! */

        default:
            DebugTrace("Got a bad PropTag in ScMergeLogonProps()");
            return E_INVALIDARG;
        }
    }

    return ScDupPropset((int)cProps2, lpProps2, lpAllocBuff, lppPropsDest);
}


/*
 -  HrDeleteDeferred
 -
 *  Purpose:
 *      Removes a deferred message node from the list when the Spooler
 *      does a NOTIFY_ABORT_DEFERRED.
 *
 *  Parameters:
 *      lpxpl           The session owning the deferred message
 *      lpsbinEID       EntryID of the deferred message to delete
 *
 *  Returns:
 *      hResult         Indicating Success/Faailure
 */

HRESULT
HrDeleteDeferred(LPXPL lpxpl, LPSBinary lpsbinEID)
{
    LPDEFMSG lpDefMsg;
    LPDEFMSG *lppDefMsg = &(lpxpl->lpDeferredList);

    while (lpDefMsg = *lppDefMsg)
    {
        if ((lpDefMsg->sbinEIDDef.cb == lpsbinEID->cb) &&
            !memcmp(lpDefMsg->sbinEIDDef.lpb,
                    lpsbinEID->lpb,
                    (UINT)lpsbinEID->cb))
        {
            *lppDefMsg = lpDefMsg->lpNext;
            break;
        }
        else
            lppDefMsg = &(lpDefMsg->lpNext);
    }

    lpxpl->FreeBuffer(lpDefMsg);

    return hrSuccess;
}


/*
 *  WizardEntry()
 *
 *  Purpose:
 *
 *      This is the initial entrypoint for the MAPI 1.0 configuration
 *      wizard.  This function tells the wizard DLL how many pages the
 *      configuration for this service requires as well as the dialog
 *      procedure to call for each individual event.
 *
 *  Arguments:
 *
 *      hInstance       the instance of my dll, this can be used to
 *                      retrieve resources out of my DLL, etc.
 *
 *      lppszRsrcName   [OUT]   on return, this buffer is filled with
 *                              the full name of the dialog resource ID.
 *                              Note that this requires the name to be a
 *                              text value and not something generated
 *                              with the MAKEINTRESOURCE() macro
 *
 *      lpfnDlgProc     [OUT]   on return, holds a function pointer to
 *                              the dialog proc to call for each event
 *
 *      lpMapiProp      the pointer to a IMAPIProp object that is my
 *                      interface to the profile.
 *
 *      lpsup           A profile suport object that can be used to
 *                      get MAPI allocators
 *
 *  Returns:
 *
 *      (SCODE)         S_OK
 */

ULONG STDAPICALLTYPE
WizardEntry (HINSTANCE hInstance,
    LPTSTR FAR * lppszRsrcName,
    DLGPROC FAR * lpfnDlgProc,
    LPMAPIPROP lpMapiProp,
    LPVOID lpsup)
{
    const static TCHAR szWizTemplate[] = "SampleTransportWizard";

    Unreferenced (lpsup);
    
    /*  Should probably mutex access here */

    *lppszRsrcName = (LPTSTR)szWizTemplate;
    *lpfnDlgProc = (DLGPROC) WizardWndProc;
    lpmpWizard = lpMapiProp;
    UlAddRef (lpMapiProp);

    return S_OK;
}

/*
 *  TogglePage()
 *
 *  Purpose:
 *
 *      Loops through the controls on a wizard page and eiter
 *      enables/shows the control or hides/disables it.
 */

VOID
TogglePage (HWND hdlg, UINT ipage, BOOL fEnable)
{
    UINT ictl = 0;
    HANDLE hctl;

    while (hctl = GetDlgItem (hdlg, (WIZ_BASE + (ipage * 10) + ictl++)))
    {
        EnableWindow(hctl, fEnable);
        ShowWindow (hctl, (fEnable ? SW_SHOW : SW_HIDE));
    }
}

BOOL STDAPICALLTYPE
WizardWndProc (HWND hDlg,
    UINT wMsgID,
    WPARAM wParam,
    LPARAM lParam)
{
    UINT cb;
    UINT cpageJump = 1;
    UINT idFocus = 0;

    static fInited = FALSE;
    static UINT ipWiz = 0;
    static SPropValue rgvalWiz[cWizProps] = {0};
    static CHAR rgchName[cchNameMax + 1] = {0};
    static CHAR rgchType[cchTypeMax + 1] = {0};
    static CHAR rgchUNC[MAX_PATH] = {0};
    static CHAR rgchPath[MAX_PATH] = {0};

    switch (wMsgID)
    {
      case WM_INITDIALOG:

        if (!fInited)
        {
            fInited = TRUE;
            SetWindowText (GetDlgItem (hDlg, IDC_TypeEdit), "MSPEER");
            SendMessage (GetDlgItem (hDlg, IDC_TypeEdit), EM_LIMITTEXT, (WPARAM)cchTypeMax, 0);
            SendMessage (GetDlgItem (hDlg, IDC_NameEdit), EM_LIMITTEXT, (WPARAM)cchNameMax, 0);
            SendMessage (GetDlgItem (hDlg, IDC_UNCEdit), EM_LIMITTEXT, (WPARAM)MAX_PATH - 1, 0);
            SendMessage (GetDlgItem (hDlg, IDC_PathEdit), EM_LIMITTEXT, (WPARAM)MAX_PATH - 1, 0);
            rgvalWiz[ipDispName].ulPropTag = PR_NULL;
            rgvalWiz[ipEmailType].ulPropTag = PR_NULL;
            rgvalWiz[ipEmailAddress].ulPropTag = PR_NULL;
            rgvalWiz[ipInbox].ulPropTag = PR_NULL;
            rgvalWiz[ipOutbox].ulPropTag = PR_SAMPLE_OUTBOUND_DIR;
            rgvalWiz[ipOutbox].Value.lpszA = "\\TEMP";
            rgvalWiz[ipFilename].ulPropTag = PR_NULL;
            rgvalWiz[ipDirectory].ulPropTag = PR_NULL;
            rgvalWiz[ipFlags].ulPropTag = PR_SAMPLE_FLAGS;
            rgvalWiz[ipFlags].Value.l = PR_SAMPLE_FLAG_PEER_TO_PEER | PR_SAMPLE_FLAG_SAVE_DATA;
            rgvalWiz[ipLogFile].ulPropTag = PR_SAMPLE_LOGFILE;
            rgvalWiz[ipLogFile].Value.lpszA = "SMPXP.LOG";
            rgvalWiz[ipLogHigh].ulPropTag = PR_SAMPLE_LOGHIGHWATER;
            rgvalWiz[ipLogHigh].Value.l = 0;
            rgvalWiz[ipLogLow].ulPropTag = PR_SAMPLE_LOGLOWWATER;
            rgvalWiz[ipLogLow].Value.l = 0;
            DebugTrace ("MSPEER: Wizard page initialized\n");
        }
        break;

      case WIZ_QUERYNUMPAGES:

        DebugTrace ("MSPEER: Wizard page count %d\n", cpageMax);
        return (BOOL)cpageMax;

      case WM_CLOSE:

        UlRelease (lpmpWizard);
        lpmpWizard = NULL;
        break;

      case WM_COMMAND:

        switch (LOWORD(wParam))
        {
          case WIZ_NEXT:

            switch (ipWiz)
            {
              case 0:
                idFocus = IDC_NameEdit;
                break;

              case 1:

                /*  Going from name page to address type */

                if (!(cb = (UINT)GetWindowText (GetDlgItem (hDlg, IDC_NameEdit),
                                        rgchName, cchNameMax + 1)))
                {
                    /*  We require a display name */

                    MessageBeep (0);
                    return 0;
                }
                rgvalWiz[ipDispName].ulPropTag = PR_SAMPLE_DISPLAY_NAME;
                rgvalWiz[ipDispName].Value.lpszA = rgchName;
                idFocus = IDC_TypeEdit;
                break;

              case 2:

                /* Going from type page to inbox */

                if (!(cb = (UINT)GetWindowText (GetDlgItem (hDlg, IDC_TypeEdit),
                                        rgchType, cchTypeMax + 1)))
                {
                    /*  We require an address type */

                    MessageBeep (0);
                    return 0;
                }
                rgvalWiz[ipEmailType].ulPropTag = PR_SAMPLE_EMAIL_ADDR_TYPE;
                rgvalWiz[ipEmailType].Value.lpszA = rgchType;
                idFocus = IDC_UNCEdit;
                break;

              case 3:

                /* Going from inbox page to path page */

                if (!(cb = (UINT)GetWindowText (GetDlgItem (hDlg, IDC_UNCEdit),
                                        rgchUNC, MAX_PATH)))
                {
                    /*  We require an address type */

                    MessageBeep (0);
                    return 0;
                }
                rgvalWiz[ipEmailAddress].ulPropTag = PR_SAMPLE_EMAIL_ADDRESS;
                rgvalWiz[ipEmailAddress].Value.lpszA = rgchUNC;
                idFocus = IDC_PathEdit;
                break;

              case 4:

                /* Going from the path page to completion*/

                rgvalWiz[ipInbox].ulPropTag = PR_SAMPLE_INBOUND_DIR;
                if ((cb = (UINT)GetWindowText (GetDlgItem (hDlg, IDC_PathEdit), rgchPath, MAX_PATH)))
                    rgvalWiz[ipInbox].Value.lpszA = rgchPath;
                else
                    rgvalWiz[ipInbox].Value.lpszA = rgvalWiz[ipEmailAddress].Value.lpszA;

                Assert (lpmpWizard);
                lpmpWizard->lpVtbl->SetProps (lpmpWizard, cWizProps, rgvalWiz, NULL);
                break;

              default:
                Assert (FALSE);
                break;
            }

            /*  Disable Current Page */
            TogglePage (hDlg, ipWiz, FALSE);

            /*  Enable Next Page */
            TogglePage (hDlg, ++ipWiz, TRUE);
            SetFocus (GetDlgItem (hDlg, idFocus));
#ifdef  _WIN32
            SendDlgItemMessage (hDlg, idFocus, EM_SETSEL, 0, -1);
#else
            SendDlgItemMessage (hDlg, idFocus, EM_SETSEL, 0, MAKELONG(0,-1));
#endif
            return (BOOL)cpageJump;

          case WIZ_PREV:

            /*  Disable Current Page */
            TogglePage (hDlg, ipWiz, FALSE);
            
            /*  Enable Previous Page */
            TogglePage (hDlg, --ipWiz, TRUE);

            switch (ipWiz)
            {
              case 1:
                idFocus = IDC_NameEdit;
                break;

              case 2:
                idFocus = IDC_TypeEdit;
                break;

              case 3:
                idFocus = IDC_UNCEdit;
                break;

              case 4:
                idFocus = IDC_PathEdit;
                break;

              default:
                break;
            }
            SetFocus (GetDlgItem (hDlg, idFocus));
#ifdef  _WIN32
            SendDlgItemMessage (hDlg, idFocus, EM_SETSEL, 0, -1);
#else
            SendDlgItemMessage (hDlg, idFocus, EM_SETSEL, 0, MAKELONG(0,-1));
#endif
            return (BOOL)cpageJump;

          default:

            return FALSE;
        }
        break;

      default:

        return FALSE;
    }

    return TRUE;
}
