/*
 * IADVSINK.CPP
 *
 * Template IAdviseSink interface implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "iadvsink.h"


/*
 * CImpIAdviseSink::CImpIAdviseSink
 * CImpIAdviseSink::~CImpIAdviseSink
 *
 * Parameters (Constructor):
 *  pObj            LPVOID of the object we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIAdviseSink::CImpIAdviseSink(LPVOID pObj, LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    return;
    }

CImpIAdviseSink::~CImpIAdviseSink(void)
    {
    return;
    }




/*
 * CImpIAdviseSink::QueryInterface
 * CImpIAdviseSink::AddRef
 * CImpIAdviseSink::Release
 *
 * Purpose:
 *  Delegating IUnknown members for CImpIAdviseSink.
 */

STDMETHODIMP CImpIAdviseSink::QueryInterface(REFIID riid
    , LPVOID *ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }


STDMETHODIMP_(ULONG) CImpIAdviseSink::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIAdviseSink::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }




/*
 * CImpIAdviseSink::OnDataChange
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

STDMETHODIMP_(void) CImpIAdviseSink::OnDataChange(LPFORMATETC pFEIn
    , LPSTGMEDIUM pSTM)
    {
    return;
    }







/*
 * CImpIAdviseSink::OnViewChange
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

STDMETHODIMP_(void) CImpIAdviseSink::OnViewChange(DWORD dwAspect
    , LONG lindex)
    {
    return;
    }





/*
 * CImpIAdviseSink::OnRename
 *
 * Purpose:
 *  Informs the advise sink that a linked object has been renamed.
 *  Generally only the OLE default handler cares about this.
 *
 * Parameters:
 *  pmk             LPMONIKER providing the new name of the object
 *
 * Return Value:
 *  None
 */

STDMETHODIMP_(void) CImpIAdviseSink::OnRename(LPMONIKER pmk)
    {
    return;
    }






/*
 * CImpIAdviseSink::OnSave
 *
 * Purpose:
 *  Informs the advise sink that the OLE object has been saved
 *  persistently.  The primary purpose of this is for containers
 *  that want to make optimizations for objects that are not in a
 *  saved state, so on this you have to disable such optimizations.
 *  Generally only the OLE default handler cares about this.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */

STDMETHODIMP_(void) CImpIAdviseSink::OnSave(void)
    {
    return;
    }





/*
 * CImpIAdviseSink::OnClose
 *
 * Purpose:
 *  Informs the advise sink that the OLE object has closed and is
 *  no longer bound in any way.  Generally only of interest to the
 *  OLE default handler.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */

STDMETHODIMP_(void) CImpIAdviseSink::OnClose(void)
    {
    return;
    }
