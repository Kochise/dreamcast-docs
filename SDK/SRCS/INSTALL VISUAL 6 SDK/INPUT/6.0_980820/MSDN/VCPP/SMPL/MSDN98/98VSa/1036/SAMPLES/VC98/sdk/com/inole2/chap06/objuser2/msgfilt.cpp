/*
 * MSGFILT.CPP
 * Koala Client #2, Chapter 6
 *
 * Implementation of a message filter object.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "objuser2.h"


/*
 * CMessageFilter::CMessageFilter
 * CMessageFilter::~CMessageFilter
 *
 * Parameters (Constructor):
 *  pApp            PAPP of the application
 */

CMessageFilter::CMessageFilter(PAPP pApp)
    {
    m_cRef=0;
    m_pApp=pApp;
    return;
    }

CMessageFilter::~CMessageFilter(void)
    {
    return;
    }



/*
 * CMessageFilter::QueryInterface
 * CMessageFilter::AddRef
 * CMessageFilter::Release
 *
 * Purpose:
 *  Delegating IUnknown members for CMessageFilter.
 */

STDMETHODIMP CMessageFilter::QueryInterface(REFIID riid
    , LPVOID *ppv)
    {
    *ppv=NULL;

    if (IID_IUnknown==riid || IID_IMessageFilter==riid)
        *ppv=this;

    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }

STDMETHODIMP_(ULONG) CMessageFilter::AddRef(void)
    {
    return ++m_cRef;
    }

STDMETHODIMP_(ULONG) CMessageFilter::Release(void)
    {
    if (0!=--m_cRef)
        return m_cRef;

    delete this;
    return 0;
    }






/*
 * CMessageFilter::HandleInComingCall
 *
 * Purpose:
 *  Requests that the container call OleSave for the object that
 *  lives here.  Typically this happens on server shutdown.
 *
 * Parameters:
 *  dwCallType      DWORD indicating the type of call received, from
 *                  the CALLTYPE enumeration
 *  hTaskCaller     HTASK of the caller
 *  dwTickCount     DWORD elapsed tick count since the outgoing call
 *                  was made if dwCallType is not CALLTYPE_TOPLEVEL.
 *                  Ignored for other call types.
 *  pInterfaceInfo  LPINTERFACEINFO providing information about the
 *                  call.  Can be NULL.
 *
 * Return Value:
 *  DWORD           One of SERVERCALL_ISHANDLED (if the call might
 *                  be handled), SERVERCALL_REJECTED (call cannot
 *                  be handled), or SERVERCALL_RETRYLATER (try
 *                  again sometime).
 */

STDMETHODIMP_(DWORD) CMessageFilter::HandleInComingCall
    (DWORD dwCallType, HTASK htaskCaller, DWORD dwTickCount
#ifdef WIN32
    , LPINTERFACEINFO pInterfaceInfo)
#else
    , DWORD dwReserved)
#endif
    {
    /*
     * Because ObjectUser2 doesn't serve any objects itself,
     * this should never occur in this message filter.
     */
    m_pApp->Message(TEXT("CMessageFilter::HandleInComingCall called"));
    return SERVERCALL_ISHANDLED;
    }





/*
 * CMessageFilter::RetryRejectedCall
 *
 * Purpose:
 *  Informs the message filter that an call from this process has
 *  been rejected or delayed from a local or remote server, thus
 *  asking the message filter what to do.
 *
 * Parameters:
 *  hTaskCallee     HTASK of the caller
 *  dwTickCount     DWORD elapsed tick count since the call was made
 *  dwRejectType    DWORD either SERVERCALL_REJECTED or
 *                  SERVERCALL_RETRYLATER as returned by
 *                  HandleInComingCall.
 *
 * Return Value:
 *  DWORD           (DWORD)-1 to cancel the call, any number between
 *                  0 and 100 to try the call again immediately, or
 *                  a value over 100 (but not (DWORD)-1) to instruct
 *                  COM to wait that many milliseconds before trying
 *                  again.
 */

STDMETHODIMP_(DWORD) CMessageFilter::RetryRejectedCall
    (HTASK htaskCallee, DWORD dwTickCount, DWORD dwRejectType)
    {
    UINT    uRet;
    TCHAR   szMsg[256];

    /*
     * A message is pointless as ObjectUserWndProc will
     * output a message as soon as the call returns, overwriting
     * anything we might print here.
     */
    if (SERVERCALL_REJECTED==dwRejectType)
        return (DWORD)-1;

    wsprintf(szMsg, TEXT("RetryRejectedCall waiting %lu")
        , dwTickCount);
    m_pApp->Message(szMsg);


    /*
     * If we've waited over 5 seconds, put up the busy dialog.
     * Otherwise continue waiting.
     */
    if (dwTickCount < 5000)
        return 200;

    m_pApp->Message
        (TEXT("CMessageFilter::RetryRejectedCall showing busy dialog"));

    uRet=DisplayBusyDialog(htaskCallee, 0L);

    switch (uRet)
        {
        case OLEUI_CANCEL:
            return (DWORD)-1;

        case OLEUI_BZ_SWITCHTOSELECTED:
            /*
             * This case won't happen without BZ_NOTRESPONDINGDIALOG,
             * but we would wait maybe 10 seconds if it did.
             */
            return 10000;

        case OLEUI_BZ_RETRYSELECTED:
            m_pApp->Message(TEXT("Waiting another second"));
            return 1000;

        default:
            break;
        }

    return 0;
    }



/*
 * CMessageFilter::MessagePending
 *
 * Purpose:
 *  Gives the caller a chance to process messages while waiting for
 *  a call to an object to complete, to handle things like focus
 *  changes and input.  Usually returning PENDINGMSG_DEFPROCESS
 *  takes care of most things, except that it discards input.  This
 *  function is really useful is you want to process input while
 *  a call is in progress.
 *
 * Parameters:
 *  hTaskCallee     HTASK of the caller
 *  dwTickCount     DWORD elapsed tick count since the call was made
 *  dwPendingType   DWORD with the type of call made from the
 *                  PENDINGTYPE enumeration.
 *
 * Return Value:
 *  DWORD           One of PENDINGMSG_CANCELCALL (cancels the call
 *                  under extreme conditions), PENDINGMSG_WAITNO-
 *                  PROCESS (continue waiting), or PENDINGMSG_WAIT-
 *                  DEFPROCESS (invoke default handling).
 */

STDMETHODIMP_(DWORD) CMessageFilter::MessagePending
    (HTASK htaskCallee, DWORD dwTickCount, DWORD dwPendingType)
    {
    return PENDINGMSG_WAITDEFPROCESS;
    }







/*
 * CMessageFilter::DisplayBusyDialog
 *
 * Purpose:
 *  Invokes the standard Busy dialog using hTask to find the
 *  window handle of the server that's busy.
 *
 * Parameters:
 *  hTask           HTASK received in the message filter.
 *  dwFlags         DWORD flags to use when invoking the dialog
 *
 * Return Value:
 *  UINT            Result of the dialog, one of OLEUI_BZ_:
 *                  SWITCHTOSELECTED, RETRYSELECTED, CALLUNBLOCKED.
 */

UINT CMessageFilter::DisplayBusyDialog(HTASK hTask, DWORD dwFlags)
    {
    OLEUIBUSY   bz;

    //Clear out everything we don't use
    memset(&bz, 0, sizeof(bz));

    bz.cbStruct=sizeof(OLEUIBUSY);
    bz.dwFlags=dwFlags;
    bz.hWndOwner=m_pApp->m_hWnd;
    bz.hTask=hTask;
    bz.lphWndDialog=NULL;

    return OleUIBusy(&bz);
    }
