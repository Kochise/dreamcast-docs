/*
 * IADVSINK.CPP
 * Data Object User Chapter 10
 *
 * Implementation of an object with IAdviseSink.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "datauser.h"


/*
 * CAdviseSink::CAdviseSink
 * CAdviseSink::~CAdviseSink
 *
 * Parameters (Constructor):
 *  pApp            PAPP to the application
 *
 */

CAdviseSink::CAdviseSink(PAPP pApp)
    {
    m_cRef=0;
    m_pApp=pApp;
    return;
    }

CAdviseSink::~CAdviseSink(void)
    {
    return;
    }




/*
 * CAdviseSink::QueryInterface
 * CAdviseSink::AddRef
 * CAdviseSink::Release
 *
 * Purpose:
 *  IUnknown members for CAdviseSink object.
 */

STDMETHODIMP CAdviseSink::QueryInterface(REFIID riid, PPVOID ppv)
    {
    *ppv=NULL;

    if (IID_IUnknown==riid || IID_IAdviseSink==riid)
        *ppv=this;

    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }


STDMETHODIMP_(ULONG) CAdviseSink::AddRef(void)
    {
    return ++m_cRef;
    }


STDMETHODIMP_(ULONG) CAdviseSink::Release(void)
    {
    if (0!=--m_cRef)
        return m_cRef;

    delete this;
    return 0;
    }




/*
 * CAdviseSink::OnDataChange
 *
 * Purpose:
 *  Notifes the advise sink that data changed in a data object.
 *  On this message you may request a new data rendering and update
 *  your displays as necessary.  Any data sent to this function is
 *  owned by the caller, not by this advise sink.
 *
 *  All Advise Sink methods are asynchronous and therefore we
 *  should attempt no synchronous calls from within them to an EXE
 *  object.  If we do, we'll get RPC_E_CALLREJECTED as shown below.
 *
 * Parameters:
 *  pFEIn           LPFORMATETC describing format that changed
 *  pSTM            LPSTGMEDIUM providing the medium in which the
 *                  data is provided.
 *
 * Return Value:
 *  None
 */


STDMETHODIMP_(void) CAdviseSink::OnDataChange(LPFORMATETC pFE
    , LPSTGMEDIUM pSTM)
    {
    BOOL        fUsable=TRUE;
    UINT        cf;
    STGMEDIUM   stm;

    /*
     * We first check that the changed data is, in fact, a format
     * we're interested in, either CF_TEXT, CF_BITMAP, or
     * CF_METAFILEPICT, then only in the aspects we want.  We check
     * if pSTM->tymed is TYMED_NULL or something else.  If NULL, we
     * just exit so the data object can time ADVF_NODATA trans-
     * actions.  Otherwise we verify that the data is useful and
     * repaint. If there is data in pSTM we are responsible for it.
     */

    //Ignore the m_fGetData flag for EXE objects (we can't GetData)
    if (!m_pApp->m_fGetData && !m_pApp->m_fEXE)
        return;

    //See if we're interested in the format and aspect that changed
    cf=pFE->cfFormat;

    if ((CF_TEXT!=cf && CF_BITMAP!=cf && CF_METAFILEPICT!=cf)
        || !(DVASPECT_CONTENT & pFE->dwAspect))
        return;

    //Check the medium if we got data
    switch (cf)
        {
        case CF_TEXT:
            fUsable=(BOOL)(TYMED_HGLOBAL & pFE->tymed);
            break;

        case CF_BITMAP:
            fUsable=(BOOL)(TYMED_GDI & pFE->tymed);
            break;

        case CF_METAFILEPICT:
            fUsable=(BOOL)(TYMED_MFPICT & pFE->tymed);
            break;

        default:
            break;
        }

    if (!fUsable)
        return;

    if (NULL==m_pApp->m_pIDataObject)
        return;

    /*
     * When dealing with EXE objects, invalidate ourselves
     * after setting TYMED_NULL in our STGMEDIUM that causes
     * CAppVars::Paint to request new data.  We cannot call
     * GetData in here because this is an async call when we're
     * dealing with an EXE.
     */
    if (m_pApp->m_fEXE)
        {
        ReleaseStgMedium(&(m_pApp->m_stm));
        m_pApp->m_cf=cf;
        m_pApp->m_stm.tymed=TYMED_NULL;

        InvalidateRect(m_pApp->m_hWnd, NULL, TRUE);
        return;
        }

    if (FAILED(m_pApp->m_pIDataObject->GetData(pFE, &stm)))
        return;

    //Get rid of old data and update.
    ReleaseStgMedium(&(m_pApp->m_stm));

    m_pApp->m_cf=cf;
    m_pApp->m_stm=stm;

    InvalidateRect(m_pApp->m_hWnd, NULL, TRUE);

    if (m_pApp->m_fRepaint)
        UpdateWindow(m_pApp->m_hWnd);

    return;
    }




/*
 * CAdviseSink::OnViewChange
 * CAdviseSink::OnRename
 * CAdviseSink::OnSave
 * CAdviseSink::OnClose
 *
 * Unimplemented members
 */

STDMETHODIMP_(void) CAdviseSink::OnViewChange(DWORD dwAspect
    , LONG lindex)
    {
    return;
    }

STDMETHODIMP_(void) CAdviseSink::OnRename(LPMONIKER pmk)
    {
    return;
    }

STDMETHODIMP_(void) CAdviseSink::OnSave(void)
    {
    return;
    }

STDMETHODIMP_(void) CAdviseSink::OnClose(void)
    {
    return;
    }
