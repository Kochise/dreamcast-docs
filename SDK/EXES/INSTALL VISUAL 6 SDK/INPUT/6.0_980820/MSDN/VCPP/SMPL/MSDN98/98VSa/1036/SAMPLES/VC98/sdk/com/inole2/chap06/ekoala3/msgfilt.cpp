/*
 * MSGFILT.CPP
 * Koala Object for EXE Servers, Chapter 6
 *
 * Implementation of a message filter object to block or delay
 * calls.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "ekoala3.h"


/*
 * CMessageFilter::CMessageFilter
 * CMessageFilter::~CMessageFilter
 *
 * Parameters (Constructor):
 *  pApp            PAPP of the application we're in
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
    if (m_pApp->m_fBlock)
        return SERVERCALL_REJECTED;

    if (m_pApp->m_fDelay)
        return SERVERCALL_RETRYLATER;

    return SERVERCALL_ISHANDLED;
    }





/*
 * CMessageFilter::RetryRejectedCall
 * CMessageFilter::MessagePending
 *
 * Not implemented:  no outgoing calls from this process.
 */

STDMETHODIMP_(DWORD) CMessageFilter::RetryRejectedCall
    (HTASK htaskCallee, DWORD dwTickCount, DWORD dwRejectType)
    {
    return 0;
    }

STDMETHODIMP_(DWORD) CMessageFilter::MessagePending
    (HTASK htaskCallee, DWORD dwTickCount, DWORD dwPendingType)
    {
    return PENDINGMSG_WAITDEFPROCESS;
    }
