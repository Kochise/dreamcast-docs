/*
 * IDATAOBJ.CPP
 * Cosmo Chapter 18
 *
 * Implementation of the IDataObject interface.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "cosmo.h"


/*
 * CImpIDataObject::CImpIDataObject
 * CImpIDataObject::~CImpIDataObject
 *
 * Parameters (Constructor):
 *  pObj            PCFigure of the object we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIDataObject::CImpIDataObject(PCFigure pObj
    , LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pObj=pObj;
    m_pUnkOuter=pUnkOuter;
    return;
    }

CImpIDataObject::~CImpIDataObject(void)
    {
    return;
    }




/*
 * CImpIDataObject::QueryInterface
 * CImpIDataObject::AddRef
 * CImpIDataObject::Release
 */

STDMETHODIMP CImpIDataObject::QueryInterface(REFIID riid, PPVOID ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }

STDMETHODIMP_(ULONG) CImpIDataObject::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIDataObject::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }





/*
 * CImpIDataObject::GetData
 *
 * Purpose:
 *  Retrieves data described by a specific FormatEtc into a StgMedium
 *  allocated by this function.  Used like GetClipboardData.
 *
 * Parameters:
 *  pFE             LPFORMATETC describing the desired data.
 *  pSTM            LPSTGMEDIUM in which to return the data.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIDataObject::GetData(LPFORMATETC pFE
    , LPSTGMEDIUM pSTM)
    {
    UINT            cf=pFE->cfFormat;
    BOOL            fRet=FALSE;

    //Another part of us already knows if the format is good.
    if (NOERROR!=QueryGetData(pFE))
        return ResultFromScode(DATA_E_FORMATETC);

    if (CF_METAFILEPICT==cf || CF_BITMAP==cf || m_pObj->m_cf==cf)
        {
        if (CF_METAFILEPICT==cf)
            {
            pSTM->tymed=TYMED_MFPICT;
            }
        else
            pSTM->tymed=TYMED_HGLOBAL;

        pSTM->pUnkForRelease=NULL;
        pSTM->hGlobal=m_pObj->m_pDoc->RenderFormat(cf);
        fRet=(NULL!=pSTM->hGlobal);
        }
    else
        fRet=m_pObj->m_pDoc->RenderMedium(cf, pSTM);

    return fRet ? NOERROR : ResultFromScode(DATA_E_FORMATETC);
    }




/*
 * CImpIDataObject::GetDataHere
 *
 * Purpose:
 *  Renders the specific FormatEtc into caller-allocated medium
 *  provided in pSTM.
 *
 * Parameters:
 *  pFE             LPFORMATETC describing the desired data.
 *  pSTM            LPSTGMEDIUM providing the medium into which
 *                  wer render the data.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIDataObject::GetDataHere(LPFORMATETC pFE
    , LPSTGMEDIUM pSTM)
    {
    UINT        cf;
    LONG        lRet;

    /*
     * The only reasonable time this is called is for
     * CFSTR_EMBEDSOURCE and TYMED_ISTORAGE (and later for
     * CFSTR_LINKSOURCE).  This means the same as
     * IPersistStorage::Save.
     */

    cf=RegisterClipboardFormat(CFSTR_EMBEDSOURCE);

    //Aspect is unimportant to us here, as is lindex and ptd.
    if (cf==pFE->cfFormat && (TYMED_ISTORAGE & pFE->tymed))
        {
        //We have an IStorage we can write into.
        pSTM->tymed=TYMED_ISTORAGE;
        pSTM->pUnkForRelease=NULL;
        lRet=m_pObj->m_pPL->WriteToStorage(pSTM->pstg
            , VERSIONCURRENT);

        if (lRet >= 0)
            return NOERROR;

        return ResultFromScode(STG_E_WRITEFAULT);
        }

    return ResultFromScode(DATA_E_FORMATETC);
    }






/*
 * CImpIDataObject::QueryGetData
 *
 * Purpose:
 *  Tests if a call to GetData with this FormatEtc will provide
 *  any rendering; used like IsClipboardFormatAvailable.
 *
 * Parameters:
 *  pFE             LPFORMATETC describing the desired data.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIDataObject::QueryGetData(LPFORMATETC pFE)
    {
    UINT            cf=pFE->cfFormat;
    UINT            i;

    //Check the aspects we support.
    if (!(DVASPECT_CONTENT & pFE->dwAspect))
        return ResultFromScode(S_FALSE);

    for (i=0; i < m_pObj->m_cfeGet; i++)
        {
        if (pFE->cfFormat==m_pObj->m_rgfeGet[i].cfFormat
            && pFE->tymed & m_pObj->m_rgfeGet[i].tymed)
            {
            return NOERROR;
            }
        }

    return ResultFromScode(S_FALSE);
    }





/*
 * CImpIDataObject::GetCanonicalFormatEtc
 *
 * Purpose:
 *  Provides the caller with an equivalent FormatEtc to the one
 *  provided when different FormatEtcs will produce exactly the
 *  same renderings.
 *
 * Parameters:
 *  pFEIn            LPFORMATETC of the first description.
 *  pFEOut           LPFORMATETC of the equal description.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIDataObject::GetCanonicalFormatEtc
    (LPFORMATETC pFEIn, LPFORMATETC pFEOut)
    {
    if (NULL==pFEOut)
        return ResultFromScode(E_INVALIDARG);

    pFEOut->ptd=NULL;
    return ResultFromScode(DATA_S_SAMEFORMATETC);
    }






/*
 * CImpIDataObject::SetData
 *
 * Purpose:
 *  Places data described by a FormatEtc and living in a StgMedium
 *  into the object.  The object may be responsible to clean up the
 *  StgMedium before exiting.
 *
 * Parameters:
 *  pFE             LPFORMATETC describing the data to set.
 *  pSTM            LPSTGMEDIUM containing the data.
 *  fRelease        BOOL indicating if this function is responsible
 *                  for freeing the data.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIDataObject::SetData(LPFORMATETC pFE
    , LPSTGMEDIUM pSTM, BOOL fRelease)
    {
    LONG            lRet;

    /*
     * Data can only come from global memory containing a
     * POLYLINEDATA structure that we send to the Polyline's
     * DataSetMem.
     */
    if ((pFE->cfFormat!=m_pObj->m_cf)
        || !(DVASPECT_CONTENT & pFE->dwAspect)
        || (TYMED_HGLOBAL!=pSTM->tymed))
        return ResultFromScode(DATA_E_FORMATETC);

    lRet=m_pObj->m_pPL->DataSetMem(pSTM->hGlobal, FALSE, TRUE
        , TRUE);

    if (fRelease)
        ReleaseStgMedium(pSTM);

    return (POLYLINE_E_NONE==lRet) ?
        NOERROR : ResultFromScode(DATA_E_FORMATETC);
    }






/*
 * CImpIDataObject::EnumFormatEtc
 *
 * Purpose:
 *  Returns an IEnumFORMATETC object through which the caller can
 *  iterate to learn about all the data formats this object can
 *  provide through either GetData[Here] or SetData.
 *
 * Parameters:
 *  dwDir           DWORD describing a data direction, either
 *                  DATADIR_SET or DATADIR_GET.
 *  ppEnum          LPENUMFORMATETC * in which to return the
 *                  pointer to the enumerator.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIDataObject::EnumFormatEtc(DWORD dwDir
    , LPENUMFORMATETC *ppEnum)
    {
    return ResultFromScode(OLE_S_USEREG);
    }





/*
 * CImpIDataObject::DAdvise
 * CImpIDataObject::DUnadvise
 * CImpIDataObject::EnumDAdvise
 *
 * Pass-throughs to IDataAdviseHolder.
 */

STDMETHODIMP CImpIDataObject::DAdvise(LPFORMATETC pFE, DWORD dwFlags
    , LPADVISESINK pIAdviseSink, LPDWORD pdwConn)
    {
    HRESULT         hr;

    if (NULL==m_pObj->m_pIDataAdviseHolder)
        {
        hr=CreateDataAdviseHolder(&m_pObj->m_pIDataAdviseHolder);

        if (FAILED(hr))
            return ResultFromScode(E_OUTOFMEMORY);
        }

    hr=m_pObj->m_pIDataAdviseHolder->Advise(this, pFE
        , dwFlags, pIAdviseSink, pdwConn);

    return hr;
    }


STDMETHODIMP CImpIDataObject::DUnadvise(DWORD dwConn)
    {
    if (NULL==m_pObj->m_pIDataAdviseHolder)
        return ResultFromScode(E_FAIL);

    return m_pObj->m_pIDataAdviseHolder->Unadvise(dwConn);
    }



STDMETHODIMP CImpIDataObject::EnumDAdvise(LPENUMSTATDATA *ppEnum)
    {
    if (NULL==m_pObj->m_pIDataAdviseHolder)
        return ResultFromScode(E_FAIL);

    return m_pObj->m_pIDataAdviseHolder->EnumAdvise(ppEnum);
    }
