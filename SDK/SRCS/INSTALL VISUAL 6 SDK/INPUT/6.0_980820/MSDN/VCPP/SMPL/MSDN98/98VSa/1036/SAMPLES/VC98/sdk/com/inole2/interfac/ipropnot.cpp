/*
 * IPROPNOT.CPP
 *
 * Template implementation of IPropertyNotifySink
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "ipropnot.h"


/*
 * CImpIPropertyNotifySink::CImpIPropertyNotifySink
 * CImpIPropertyNotifySink::~CImpIPropertyNotifySink
 *
 * Constructor Parameters:
 *  pObj            LPVOID of the object containing us.
 *  pUnkOuter       LPUNKNOWN to which we blindly delegate
 *                  all IUnknown calls.
 */

CImpIPropertyNotifySink::CImpIPropertyNotifySink(LPVOID pObj
    , LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    return;
    }

CImpIPropertyNotifySink::~CImpIPropertyNotifySink(void)
    {
    return;
    }


/*
 * CImpIPropertyNotifySink::QueryInterface
 * CImpIPropertyNotifySink::AddRef
 * CImpIPropertyNotifySink::Release
 *
 * Purpose:
 *  Delegating IUnknown members for CImpIPropertyNotifySink.
 */

STDMETHODIMP CImpIPropertyNotifySink::QueryInterface(REFIID riid
    , LPVOID *ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }

STDMETHODIMP_(ULONG) CImpIPropertyNotifySink::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIPropertyNotifySink::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }



/*
 * CImpIPropertyNotifySink::OnChanged
 *
 * Purpose:
 *  Notifies this sink that the property identified with dispID
 *  has changed in whatever object this sink is connected to.
 *
 * Parameters:
 *  dispID          DISPID of the property that changed,
 *                  which can be DISPID_UNKNOWN for unspecified
 *                  changes to multiple properties.
 *
 * Return Value:
 *  HRESULT         NOERROR always.
 */

STDMETHODIMP CImpIPropertyNotifySink::OnChanged(DISPID dispID)
    {
    return NOERROR;
    }



/*
 * CImpIPropertyNotifySink::OnRequestEdit
 *
 * Purpose:
 *  Notifies this sink that the property identified with dispID
 *  is about to change and that the sink can prevent the change
 *  if desired.  This can be used to enforce read-only states or
 *  to save prior states before the change occurs.
 *
 * Parameters:
 *  dispID          DISPID of the property that is changing
 *                  which can be DISPID_UNKNOWN for multiple
 *                  properties.
 *
 * Return Value:
 *  HRESULT         NOERROR if the property can change, S_FALSE
 *                  if it cannot change, error code otherwise.
 */

STDMETHODIMP CImpIPropertyNotifySink::OnRequestEdit(DISPID dispID)
    {
    return NOERROR;
    }
