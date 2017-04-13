/*
 * IADVSNK2.CPP
 *
 * Template IAdviseSink2 interface implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "iadvsnk2.h"


/*
 * CImpIAdviseSink2::CImpIAdviseSink2
 * CImpIAdviseSink2::~CImpIAdviseSink2
 *
 * Parameters (Constructor):
 *  pObj            LPVOID of the object we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIAdviseSink2::CImpIAdviseSink2(LPVOID pObj, LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    return;
    }

CImpIAdviseSink2::~CImpIAdviseSink2(void)
    {
    return;
    }




/*
 * CImpIAdviseSink2::QueryInterface
 * CImpIAdviseSink2::AddRef
 * CImpIAdviseSink2::Release
 *
 * Purpose:
 *  Delegating IUnknown members for CImpIAdviseSink2.
 */

STDMETHODIMP CImpIAdviseSink2::QueryInterface(REFIID riid
    , LPVOID *ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }


STDMETHODIMP_(ULONG) CImpIAdviseSink2::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIAdviseSink2::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }




/*
 * CImpIAdviseSink2::OnDataChange
 *
 * Purpose:
 *  Notifes the advise sink that data changed in a data object.
 *  On this message you may request a new data rendering and update
 *  your displays as necessary.
 *
 * Parameters:
 *  pFEIn           LPFORMATETC describing format that changed
 *  pSTM            LPSTGMEDIUM providing the medium in which the
 *                  data is provided.
 *
 * Return Value:
 *  None
 */

STDMETHODIMP_(void) CImpIAdviseSink2::OnDataChange(LPFORMATETC pFEIn
    , LPSTGMEDIUM pSTM)
    {
    return;
    }







/*
 * CImpIAdviseSink2::OnViewChange
 *
 * Purpose:
 *  Notifes the advise sink that presentation data changed in the
 *  data object to which we're connected providing the right time
 *  to update displays using such presentations.
 *
 * Parameters:
 *  dwAspect        DWORD indicating which aspect has changed.
 *  lindex          LONG indicating the piece that changed.
 *
 * Return Value:
 *  None
 */

STDMETHODIMP_(void) CImpIAdviseSink2::OnViewChange(DWORD dwAspect
    , LONG lindex)
    {
    return;
    }





/*
 * CImpIAdviseSink2::OnRename
 *
 * Purpose:
 *  Informs the advise sink that a linked compound document object
 *  has been renamed.  Generally only the OLE default handler cares
 *  about this.
 *
 * Parameters:
 *  pmk             LPMONIKER providing the new name of the object
 *
 * Return Value:
 *  None
 */

STDMETHODIMP_(void) CImpIAdviseSink2::OnRename(LPMONIKER pmk)
    {
    return;
    }






/*
 * CImpIAdviseSink2::OnSave
 *
 * Purpose:
 *  Informs the advise sink that the compound document object has
 *  been saved persistently.  The primary purpose of this is for
 *  containers that want to make optimizations for objects that are
 *  not in a saved state, so on this you have to disable such
 *  optimizations.  Generally only the OLE default handler
 *  cares about this.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */

STDMETHODIMP_(void) CImpIAdviseSink2::OnSave(void)
    {
    return;
    }





/*
 * CImpIAdviseSink2::OnClose
 *
 * Purpose:
 *  Informs the advise sink that the compound document object has
 *  closed and is no longer bound in any way.  Generally only of
 *  interest to the OLE default handler.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */

STDMETHODIMP_(void) CImpIAdviseSink2::OnClose(void)
    {
    return;
    }





/*
 * CImpIAdviseSink2::OnLinkSrcChange
 *
 * Purpose:
 *  Informs the advise sink that a linked compound document object
 *  has changed its link source to the object identified by the
 *  given moniker.  This is generally only of interest to the OLE
 *  default handler's implementation of linked objects.
 *
 * Parameters:
 *  pmk             LPMONIKER specifying the new link source.
 *
 * Return Value:
 *  None
 */

STDMETHODIMP_(void) CImpIAdviseSink2::OnLinkSrcChange(LPMONIKER pmk)
    {
    return;
    }
