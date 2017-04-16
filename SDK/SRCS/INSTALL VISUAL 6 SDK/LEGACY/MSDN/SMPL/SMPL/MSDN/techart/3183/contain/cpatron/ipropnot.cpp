/*
 * IPROPNOT.CPP
 * Patron Control Containter
 *
 * Implementation of the IPropertyNotifySink interface for the
 * tenant control site.
 *
 * Copyright (c)1994 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "patron.h"


/*
 * CImpIPropertyNotifySink::CImpIPropertyNotifySink
 * CImpIPropertyNotifySink::~CImpIPropertyNotifySink
 *
 * Parameters (Constructor):
 *  pTen            PCTenant of the tenant we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIPropertyNotifySink::CImpIPropertyNotifySink(PCTenant pTen
    , LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pTen=pTen;
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
 *  IUnknown members for CImpIPropertyNotifySink object.
 */

STDMETHODIMP CImpIPropertyNotifySink::QueryInterface(REFIID riid, PPVOID ppv)
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
    m_cRef--;
    return m_pUnkOuter->Release();
    }




/*
 * CImpIPropertyNotifySink::OnChanged
 *
 * Purpose:
 *  Informs the container that a property changed in the control.
 *  For properties changes that can be canceled, the control will
 *  generally call OnRequestEdit first.  If the change cannot be
 *  canceled, then OnChanged here is called without any prior
 *  warning, and the property has already changed.
 *
 * Parameters:
 *  dispID          DISPID of the property in question
 *
 * Return Value:
 *  HRESULT         NOERROR
 */

STDMETHODIMP CImpIPropertyNotifySink::OnChanged(DISPID dispID)
    {
    return NOERROR;
    }




/*
 * CImpIPropertyNotifySink::OnRequestEdit
 *
 * Purpose:
 *  Asks the container if it will allow a change in a property
 *  before any change takes place.  The container can save a
 *  copy of the old property or veto the change completely.
 *
 * Parameters:
 *  dispID          DISPID of the property in question
 *
 * Return Value:
 *  HRESULT         NOERROR if the property can be modified,
 *                  S_FALSE otherwise.
 */

STDMETHODIMP CImpIPropertyNotifySink::OnRequestEdit(DISPID dispID)
    {
    return NOERROR;
    }
