/*
 * IADVSINK.CPP
 * Component Cosmo Chapter 10
 *
 * Implementation of the CPolylineAdviseSink and CImpIAdviseSink
 * interfaces for Component Cosmo.  CPolylineAdviseSink moved
 * here from document.cpp to live with all the advise stuff.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "cocosmo.h"


/*
 * CPolylineAdviseSink::CPolylineAdviseSink
 * CPolylineAdviseSink::~CPolylineAdviseSink
 *
 * Constructor Parameters:
 *  pDoc            PCCosmoDoc to store in this object
 */

CPolylineAdviseSink::CPolylineAdviseSink(PCCosmoDoc pDoc)
    {
    m_pDoc=pDoc;
    m_cRef=0;
    AddRef();
    return;
    }


CPolylineAdviseSink::~CPolylineAdviseSink(void)
    {
    return;
    }




/*
 * CPolylineAdviseSink::QueryInterface
 * CPolylineAdviseSink::AddRef
 * CPolylineAdviseSink::Release
 *
 * Purpose:
 *  IUnknown members for this IPolylineAdviseSink implementations.
 */

STDMETHODIMP CPolylineAdviseSink::QueryInterface(REFIID riid
    , PPVOID ppv)
    {
    //CHAPTER10MOD
    return m_pDoc->QueryInterface(riid, ppv);
    //End CHAPTER10MOD
    }


STDMETHODIMP_(ULONG) CPolylineAdviseSink::AddRef(void)
    {
    return ++m_cRef;
    }


STDMETHODIMP_(ULONG) CPolylineAdviseSink::Release(void)
    {
    if (0L!=--m_cRef)
        return m_cRef;

    delete this;
    return 0;
    }




/*
 * CPolylineAdviseSink::OnPointChange
 *
 * Purpose:
 *  Informs the document that the polyline added or removed a point.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */

STDMETHODIMP_(void) CPolylineAdviseSink::OnPointChange(void)
    {
    m_pDoc->FDirtySet(TRUE);
    return;
    }






/*
 * CPolylineAdviseSink::OnSizeChange
 *
 * Purpose:
 *  Informs the document that the polyline changed size.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */

STDMETHODIMP_(void) CPolylineAdviseSink::OnSizeChange(void)
    {
    RECT            rc;
    DWORD           dwStyle;
    HWND            hWnd;

    /*
     * Polyline window is informing us that it changed size in
     * response to setting it's data.  Therefore we have to
     * size ourselves accordingly but without moving the screen
     * position of the polyline window.
     */

    m_pDoc->m_fNoSize=TRUE;

    //Set the document window size.
    m_pDoc->m_pPL->Window(&hWnd);
    GetWindowRect(hWnd, &rc);
    InflateRect(&rc, 8, 8);

    //Adjust for a window sans menu
    dwStyle=GetWindowLong(m_pDoc->m_hWnd, GWL_STYLE);
    AdjustWindowRect(&rc, dwStyle, FALSE);

    SetWindowPos(m_pDoc->m_hWnd, NULL, 0, 0, rc.right-rc.left
        , rc.bottom-rc.top, SWP_NOMOVE | SWP_NOZORDER);

    if (NULL!=m_pDoc->m_pAdv)
        m_pDoc->m_pAdv->OnSizeChange(m_pDoc, &rc);

    m_pDoc->m_fNoSize=FALSE;
    m_pDoc->FDirtySet(TRUE);

    return;
    }




//CHAPTER10MOD
//OnDataChange in CImpIAdviseSink now
//End CHAPTER10MOD



/*
 * CPolylineAdviseSink::OnColorChange
 *
 * Purpose:
 *  Informs the document that the polyline data changed a color.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */

STDMETHODIMP_(void) CPolylineAdviseSink::OnColorChange(void)
    {
    m_pDoc->FDirtySet(TRUE);
    return;
    }





/*
 * CPolylineAdviseSink::OnLineStyleChange
 *
 * Purpose:
 *  Informs the document that the polyline changed its line style.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */

STDMETHODIMP_(void) CPolylineAdviseSink::OnLineStyleChange(void)
    {
    m_pDoc->FDirtySet(TRUE);
    return;
    }






//CHAPTER10MOD
/*
 * CImpIAdviseSink::CImpIAdviseSink
 * CImpIAdviseSink::~CImpIAdviseSink
 *
 * Parameters (Constructor):
 *  pObj            LPVOID of the object we're in.
 *  pUnkOuter       LPUNKNOWN for delegation of IUnknown members.
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
 *  IUnknown members for CImpIAdviseSink object.
 */

STDMETHODIMP CImpIAdviseSink::QueryInterface(REFIID riid
    , PPVOID ppv)
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
 *  On this message you may request a new data rendering and
 *  update your displays as necessary.
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
    PCCosmoDoc      m_pDoc=(PCCosmoDoc)m_pObj;

    /*
     * This code is from former CPolylineAdviseSink::OnDataChange.
     * The only advise we asked for was on the Polyline native
     * format which is all we'll be notified for.
     */
    if (NULL!=m_pDoc->m_pAdv)
        m_pDoc->m_pAdv->OnDataChange(m_pDoc);

    m_pDoc->FDirtySet(TRUE);
    return;
    }




STDMETHODIMP_(void) CImpIAdviseSink::OnViewChange(DWORD dwAspect
    , LONG lindex)
    {
    return;
    }


STDMETHODIMP_(void) CImpIAdviseSink::OnRename(LPMONIKER pmk)
    {
    return;
    }


STDMETHODIMP_(void) CImpIAdviseSink::OnSave(void)
    {
    return;
    }


STDMETHODIMP_(void) CImpIAdviseSink::OnClose(void)
    {
    return;
    }


//End CHAPTER10MOD
