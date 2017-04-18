/*
 * IADVSINK.CPP
 * Cosmo Handler Chapter 19
 *
 * Implementation of the IAdviseSink interface for the Cosmo Handler
 * such that it is notified when data is modified in the server.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "hcosmo.h"


/*
 * CImpIAdviseSink::CImpIAdviseSink
 * CImpIAdviseSink::~CImpIAdviseSink
 *
 * Parameters (Constructor):
 *  pObj            PCFigure of the object we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIAdviseSink::CImpIAdviseSink(PCFigure pObj
    , LPUNKNOWN pUnkOuter)
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
 */

STDMETHODIMP CImpIAdviseSink::QueryInterface(REFIID riid, PPVOID ppv)
    {
    /*
     * Conceptually, and from the view of the container and the
     * local server, the IAdviseSink interface is implemented
     * on a different object than the rest of the handler's
     * interfaces.  For that reason, this QueryInterface only
     * exposes IUnknown and IAdviseSink.  That makes it appear
     * as a separate object although it doesn't have to be an
     * explicitly separate object inside this handler (no one
     * outside the handler cares about our implementation).  Note
     * that reference counting still affects the entire object.
     */
    if (IID_IUnknown==riid || IID_IAdviseSink==riid)
        {
        *ppv=this;
        AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }


STDMETHODIMP_(ULONG) CImpIAdviseSink::AddRef(void)
    {
    return ++m_cRef;
    }

STDMETHODIMP_(ULONG) CImpIAdviseSink::Release(void)
    {
    return --m_cRef;
    }




/*
 * CImpIAdviseSink::OnViewChange
 *
 * Purpose:
 *  We don't do anything here because we generate OnViewChange for
 *  the container inside OnDataChange.  The problem is that
 *  OnViewChange will come before OnDataChange, so if we called the
 *  container's OnViewChange here it would turn around and call our
 *  IViewObject::Draw which would draw with outdated data. Therefore
 *  we ignore this notification and wait for OnDataChange, since
 *  that implies a view change as well.  Then we can retrieve the
 *  new data first, then send OnViewChange to the container such
 *  that we'll repaint with the new data.
 */

STDMETHODIMP_(void) CImpIAdviseSink::OnViewChange(DWORD dwAspect
    , LONG lindex)
    {
    return;
    }



/*
 * CImpIAdviseSink::OnDataChange
 *
 * Purpose:
 *  Tells us that things changed in the server.  We asked for data
 *  on the advise so we can copy it from here into our own structure
 *  such that on the next OnViewChange we can repaint with it.
 */

STDMETHODIMP_(void) CImpIAdviseSink::OnDataChange(LPFORMATETC pFE
    , LPSTGMEDIUM pSTM)
    {
    //Get the new data first, then notify the container to repaint.
    if ((pFE->cfFormat==m_pObj->m_cf)
        && (TYMED_HGLOBAL & pSTM->tymed))
        {
        PPOLYLINEDATA      ppl;

        ppl=(PPOLYLINEDATA)GlobalLock(pSTM->hGlobal);
        memcpy(&m_pObj->m_pl, ppl, CBPOLYLINEDATA);
        GlobalUnlock(pSTM->hGlobal);

        /*
         * Now tell the container that the view changed, but only
         * if the view is not frozen.'
         */
        if (pFE->dwAspect & m_pObj->m_dwAdviseAspects
            && !(pFE->dwAspect & m_pObj->m_dwFrozenAspects))
            {
            //Pass this on to the container.
            if (NULL!=m_pObj->m_pIAdvSinkView)
                {
                m_pObj->m_pIAdvSinkView->OnViewChange(pFE->dwAspect
                    , pFE->lindex);
                }
            }
        }

    return;
    }



/*
 * All others are uninteresting because if the container wants these
 * it will have called IOleObject::Advise which we passed on through
 * to the default handler.  IViewObject::SetAdvise is the only one
 * we override.
 */

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
