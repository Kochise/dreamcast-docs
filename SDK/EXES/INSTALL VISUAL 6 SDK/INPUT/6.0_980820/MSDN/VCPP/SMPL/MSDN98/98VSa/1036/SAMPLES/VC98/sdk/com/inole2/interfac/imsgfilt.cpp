/*
 * IMSGFILT.CPP
 *
 * Template IMessageFilter object.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "imsgfilt.h"


/*
 * CMessageFilter::CMessageFilter
 * CMessageFilter::~CMessageFilter
 *
 * Parameters (Constructor):
 *  None
 */

CMessageFilter::CMessageFilter(void)
    {
    m_cRef=0;
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
    , LPINTERFACEINFO pInterfaceInfo)
    {
    return SERVERCALL_ISHANDLED;
    }





/*
 * CMessageFilter::RetryRejectedCall
 *
 * Purpose:
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
    return 0;
    }



/*
 * CMessageFilter::MessagePending
 *
 * Purpose:
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
 *                  PROCESS (continue waiting), or PENDINGMSG_-
 *                  WAITDEFPROCESS (invoke default handling).
 */

STDMETHODIMP_(DWORD) CMessageFilter::MessagePending
    (HTASK htaskCallee, DWORD dwTickCount, DWORD dwPendingType)
    {
    return PENDINGMSG_WAITDEFPROCESS;
    }
