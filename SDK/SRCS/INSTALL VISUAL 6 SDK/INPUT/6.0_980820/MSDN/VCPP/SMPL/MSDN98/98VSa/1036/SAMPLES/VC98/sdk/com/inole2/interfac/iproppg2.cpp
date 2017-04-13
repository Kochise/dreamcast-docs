/*
 * IPROPPG2.CPP
 *
 * Template IPropertyPage2 interface implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "iproppg2.h"


/*
 * CImpIPropertyPage2::CImpIPropertyPage2
 * CImpIPropertyPage2::~CImpIPropertyPage2
 *
 * Parameters (Constructor):
 *  pObj            LPVOID of the object we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIPropertyPage2::CImpIPropertyPage2(LPVOID pObj
    , LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    return;
    }

CImpIPropertyPage2::~CImpIPropertyPage2(void)
    {
    return;
    }



/*
 * CImpIPropertyPage2::QueryInterface
 * CImpIPropertyPage2::AddRef
 * CImpIPropertyPage2::Release
 *
 * Purpose:
 *  Delegating IUnknown members for CImpIPropertyPage2.
 */

STDMETHODIMP CImpIPropertyPage2::QueryInterface(REFIID riid
    , LPVOID *ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }

STDMETHODIMP_(ULONG) CImpIPropertyPage2::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIPropertyPage2::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }



/*
 * CImpIPropertyPage2::SetPageSite
 *
 * Purpose:
 *  Provides the property page with the IPropertyPageSite
 *  that contains it.  SetPageSite(NULL) will be called as
 *  part of the close sequence.
 *
 * Parameters:
 *  pPageSite       LPPROPERTYPAGESITE pointer to the site.
 */

STDMETHODIMP CImpIPropertyPage2::SetPageSite
    (LPPROPERTYPAGESITE pPageSite)
    {
    return ResultFromScode(E_NOTIMPL);
    }



/*
 * CImpIPropertyPage2::Activate
 *
 * Purpose:
 *  Instructs the property page to create a window in which to
 *  display its contents, using the given parent window and
 *  rectangle.  The window should be initially visible.
 *
 * Parameters:
 *  hWndParent      HWND of the parent window.
 *  prc             LPCRECT of the rectangle to use.
 *  fModal          BOOL indicating whether the frame is modal.
 */

STDMETHODIMP CImpIPropertyPage2::Activate(HWND hWndParent
    , LPCRECT prc, BOOL fModal)
    {
    return ResultFromScode(E_NOTIMPL);
    }



/*
 * CImpIPropertyPage2::Deactivate
 *
 * Purpose:
 *  Instructs the property page to destroy its window that was
 *  created in Activate.
 *
 * Parameters:
 *  None
 */

STDMETHODIMP CImpIPropertyPage2::Deactivate(void)
    {
    return ResultFromScode(E_NOTIMPL);
    }



/*
 * CImpIPropertyPage2::GetPageInfo
 *
 * Purpose:
 *  Fills a PROPPAGEINFO structure describing the page's size,
 *  contents, and help information.
 *
 * Parameters:
 *  pPageInfo       LPPROPPAGEINFO to the structure to fill.
 */

STDMETHODIMP CImpIPropertyPage2::GetPageInfo(LPPROPPAGEINFO pPageInfo)
    {
    return ResultFromScode(E_NOTIMPL);
    }



/*
 * CImpIPropertyPage2::SetObjects
 *
 * Purpose:
 *  Identifies the objects that are being affected by this property
 *  page (and all other pages in the frame).  These are the object
 *  to which to send new property values in the Apply member.
 *
 * Parameters:
 *  cObjects        ULONG number of objects
 *  ppUnk           IUnknown ** to the array of objects being
 *                  passed to the page.
 */

STDMETHODIMP CImpIPropertyPage2::SetObjects(ULONG cObjects
    , IUnknown **ppunk)
    {
    return ResultFromScode(E_NOTIMPL);
    }



/*
 * CImpIPropertyPage2::Show
 *
 * Purpose:
 *  Instructs the page to show or hide its window created in
 *  Activate.
 *
 * Parameters:
 *  nCmdShow        UINT to pass to ShowWindow.
 */

STDMETHODIMP CImpIPropertyPage2::Show(UINT nCmdShow)
    {
    return ResultFromScode(E_NOTIMPL);
    }



/*
 * CImpIPropertyPage2::Move
 *
 * Purpose:
 *  Instructs the property page to change its position.
 *
 * Parameters:
 *  prc             LPCRECT containing the new position.
 */

STDMETHODIMP CImpIPropertyPage2::Move(LPCRECT prc)
    {
    return ResultFromScode(E_NOTIMPL);
    }



/*
 * CImpIPropertyPage2::IsPageDirty
 *
 * Purpose:
 *  Asks the page if anything's changed in it, that is, if the
 *  property values in the page are out of sync with the objects
 *  under consideration.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  HRESULT         NOERROR if dirty, S_FALSE if not.
 */

STDMETHODIMP CImpIPropertyPage2::IsPageDirty(void)
    {
    return ResultFromScode(E_NOTIMPL);
    }




/*
 * CImpIPropertyPage2::Apply
 *
 * Purpose:
 *  Instructs the page to send changes in its page to whatever
 *  objects it knows about through SetObjects.  This is the only
 *  time the page should change the objects' properties, and not
 *  when the value is changed on the page.
 *
 * Parameters:
 *  None
 */

STDMETHODIMP CImpIPropertyPage2::Apply(void)
    {
    return ResultFromScode(E_NOTIMPL);
    }



/*
 * CImpIPropertyPage2::Help
 *
 * Purpose:
 *  Invokes help for this property page.
 *
 * Parameters:
 *  pszHelpDir      LPCOLESTR identifying the default location of
 *                  the help information
 */

STDMETHODIMP CImpIPropertyPage2::Help(LPCOLESTR pszHelpDir)
    {
    return ResultFromScode(E_NOTIMPL);
    }




/*
 * CImpIPropertyPage2::TranslateAccelerator
 *
 * Purpose:
 *  Provides the page with the messages that occur in the frame.
 *  This gives the page to do whatever it wants with the message,
 *  such as handle keyboard mnemonics.
 *
 * Parameters:
 *  pMsg            LPMSG containing the message of the accelerator.
 */

STDMETHODIMP CImpIPropertyPage2::TranslateAccelerator(LPMSG lpMsg)
    {
    return ResultFromScode(E_NOTIMPL);
    }




/*
 * CImpIPropertyPage2::EditProperty
 *
 * Purpose:
 *  Informs the property page to speifically set focus to a
 *  particular property identified with dispID.  Support for this
 *  method is optional.
 *
 * Parameters:
 *  dispID          DISPID of the property to highlight.
 */

STDMETHODIMP CImpIPropertyPage2::EditProperty(DISPID dispid)
    {
    return ResultFromScode(E_NOTIMPL);
    }
