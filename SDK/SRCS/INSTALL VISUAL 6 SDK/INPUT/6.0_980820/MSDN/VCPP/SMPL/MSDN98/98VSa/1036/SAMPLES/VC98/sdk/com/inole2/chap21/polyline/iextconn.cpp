/*
 * IEXTCONN.CPP
 * Polyline Component Chapter 21
 *
 * Implementation of IExternalConnection as required for an
 * in-process object that supports linking to embedding.
 * Specifically, this will call IOleObject::Close when there
 * are no more strong locks on the object.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "polyline.h"


/*
 * CImpIExternalConnection::CImpIExternalConnection
 * CImpIExternalConnection::~CImpIExternalConnection
 *
 * Parameters (Constructor):
 *  pObj            PCPolyline of the object we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIExternalConnection::CImpIExternalConnection(PCPolyline pObj
    , LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    m_cLockStrong=0L;
    return;
    }

CImpIExternalConnection::~CImpIExternalConnection(void)
    {
    return;
    }



/*
 * CImpIExternalConnection::QueryInterface
 * CImpIExternalConnection::AddRef
 * CImpIExternalConnection::Release
 *
 * Purpose:
 *  Delegating IUnknown members for CImpIExternalConnection.
 */

STDMETHODIMP CImpIExternalConnection::QueryInterface(REFIID riid
    , LPVOID *ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }


STDMETHODIMP_(ULONG) CImpIExternalConnection::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIExternalConnection::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }




/*
 * CImpIExternalConnection::AddConnection
 *
 * Purpose:
 *  Informs the object that a strong connection has been made to it.
 *
 * Parameters:
 *  dwConn          DWORD identifying the type of connection, taken
 *                  from the EXTCONN enumeration.
 *  dwReserved      DWORD reserved.  This is used inside OLE and
 *                  should not be validated.
 *
 * Return Value:
 *  DWORD           The number of connection counts on the
 *                  object, used for debugging purposes only.
 */

STDMETHODIMP_(DWORD) CImpIExternalConnection::AddConnection
    (DWORD dwConn, DWORD dwReserved)
    {
    if (EXTCONN_STRONG & dwConn)
        return ++m_cLockStrong;

    return 0;
    }






/*
 * CImpIExternalConnection::ReleaseConnection
 *
 * Purpose:
 *  Informs an object that a connection has been taken away from
 *  it in which case the object may need to shut down.
 *
 * Parameters:
 *  dwConn              DWORD identifying the type of connection,
 *                      taken from the EXTCONN enumeration.
 *  dwReserved          DWORD reserved.  This is used inside OLE and
 *                      should not be validated.
 *  dwRerved            DWORD reserved
 *  fLastReleaseCloses  BOOL indicating if the last call to this
 *                      function should close the object.
 *
 * Return Value:
 *  DWORD           The number of remaining connection counts on
 *                  the object, used for debugging purposes only.
 */

STDMETHODIMP_(DWORD) CImpIExternalConnection::ReleaseConnection
    (DWORD dwConn, DWORD dwReserved, BOOL fLastReleaseCloses)
    {
    if (EXTCONN_STRONG==dwConn)
        {
        if (0==--m_cLockStrong && fLastReleaseCloses)
            m_pObj->m_pImpIOleObject->Close(OLECLOSE_SAVEIFDIRTY);

        return m_cLockStrong;
        }

    return 0L;
    }
