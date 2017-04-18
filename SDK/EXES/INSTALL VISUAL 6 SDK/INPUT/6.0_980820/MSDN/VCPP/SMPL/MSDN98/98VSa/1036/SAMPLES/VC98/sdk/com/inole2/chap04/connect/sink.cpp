/*
 * SINK.CPP
 *
 * Implementation of a sink with the IDuckEvents interface.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "connect.h"


/*
 * CDuckEvents::CDuckEvents
 * CDuckEvents::~CDuckEvents
 *
 * Parameters (Constructor):
 *  pApp            PAPP to the app object.
 *  uID             UINT identifier for this sink.
 */

CDuckEvents::CDuckEvents(PAPP pApp, UINT uID)
    {
    m_cRef=0;
    m_pApp=pApp;    //No AddRef needed, we're nested
    m_uID=uID;
    m_dwCookie=0;
    return;
    }

CDuckEvents::~CDuckEvents(void)
    {
    return;
    }



/*
 * CDuckEvents::QueryInterface
 * CDuckEvents::AddRef
 * CDuckEvents::Release
 *
 * Purpose:
 *  Non-delegating IUnknown members for CDuckEvents.
 */

STDMETHODIMP CDuckEvents::QueryInterface(REFIID riid
    , LPVOID *ppv)
    {
    *ppv=NULL;

    if (IID_IUnknown==riid || IID_IDuckEvents==riid)
        *ppv=this;

    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }

STDMETHODIMP_(ULONG) CDuckEvents::AddRef(void)
    {
    return ++m_cRef;
    }

STDMETHODIMP_(ULONG) CDuckEvents::Release(void)
    {
    if (0!=--m_cRef)
        return m_cRef;

    delete this;
    return 0;
    }



/*
 * CDuckEvents::Quack
 *
 * Purpose:
 *  Event handler for Quacks
 */

STDMETHODIMP CDuckEvents::Quack(void)
    {
    TCHAR       szTemp[100];

    wsprintf(szTemp, TEXT("Sink #%u received Quack"), m_uID+1);
    m_pApp->Message(szTemp);

   #ifdef WIN32
    PlaySound(TEXT("quack.wav"), NULL, SND_SYNC);
   #endif

    return NOERROR;
    }



/*
 * CDuckEvents::Flap
 *
 * Purpose:
 *  Event handler for Flapping
 */

STDMETHODIMP CDuckEvents::Flap(void)
    {
    TCHAR       szTemp[100];

    wsprintf(szTemp, TEXT("Sink #%u received Flap"), m_uID+1);
    m_pApp->Message(szTemp);

   #ifdef WIN32
    PlaySound(TEXT("flap.wav"), NULL, SND_SYNC);
   #endif

    return NOERROR;
    }



/*
 * CDuckEvents::Paddle
 *
 * Purpose:
 *  Event handler for Paddling
 */

STDMETHODIMP CDuckEvents::Paddle(void)
    {
    TCHAR       szTemp[100];

    wsprintf(szTemp, TEXT("Sink #%u received Paddle"), m_uID+1);
    m_pApp->Message(szTemp);

   #ifdef WIN32
    PlaySound(TEXT("paddle.wav"), NULL, SND_SYNC);
   #endif

    return NOERROR;
    }
