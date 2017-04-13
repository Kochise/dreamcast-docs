/*
 * IDATAOBJ.CPP
 * Data Transfer Object Chapter 12
 *
 * Implementation of the IDataObject interface for CDataObject.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "dataobj.h"


/*
 * CImpIDataObject::CImpIDataObject
 * CImpIDataObject::~CImpIDataObject
 *
 * Parameters (Constructor):
 *  pObj            PCDataObject of the object we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIDataObject::CImpIDataObject(PCDataObject pObj
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
 *
 * Purpose:
 *  IUnknown members for CImpIDataObject object.
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
    UINT        i, cItems;
    PRENDERING  pRen;
    DWORD       cb;
    HWND        hList;

    if (NULL==m_pObj->m_hList || NULL==pFE || NULL==pSTM)
        return ResultFromScode(DATA_E_FORMATETC);

    hList=m_pObj->m_hList;
    cItems=(UINT)SendMessage(hList, LB_GETCOUNT, 0, 0L);

    for (i=0; i < cItems; i++)
        {
        cb=SendMessage(hList, LB_GETTEXT, i, (LPARAM)&pRen);

        if (LB_ERR!=cb)
            {
            /*
             * Check if the requested FORMATETC is the same as one
             * that we already have. If so, then copy that STGMEDIUM
             * to pSTM and AddRef ourselves for pUnkForRelease.
             */
            if (pFE->cfFormat==pRen->fe.cfFormat
                && (pFE->tymed & pRen->fe.tymed)
                && pFE->dwAspect==pRen->fe.dwAspect)
                {
                /*
                 * ReleaseStgMedium will Release both storage
                 * and stream elements regardless of the value
                 * of pUnkForRelease, so we have to AddRef the
                 * element and bump our own ref count here.
                 */
                if (TYMED_ISTORAGE==pRen->fe.tymed)
                      pRen->stm.pstg->AddRef();

                if (TYMED_ISTREAM==pRen->fe.tymed)
                      pRen->stm.pstm->AddRef();

                *pSTM=pRen->stm;
                AddRef();
                return NOERROR;
                }
            }
        }

    return ResultFromScode(DATA_E_FORMATETC);
    }



/*
 * CImpIDataObject::GetDataHere
 *
 * Purpose:
 *  Copies a piece of data in this data object to another
 *  STGMEDIUM.  This is only supported for TYMED_ISTORAGE
 *  and TYMED_ISTREAM.
 *
 * Parameters:
 *  pFE             LPFORMATETC describing the desired data.
 *  pSTM            LPSTGMEDIUM pointing to the medium into which
 *                  we copy.
 *
 * Return Value:
 *  HRESULT         NOERROR or a general error value.
 */

STDMETHODIMP CImpIDataObject::GetDataHere(LPFORMATETC pFE
    , LPSTGMEDIUM pSTM)
    {
    UINT        i, cItems;
    PRENDERING  pRen;
    DWORD       cb;
    HWND        hList;

    if (NULL==m_pObj->m_hList || NULL==pFE || NULL==pSTM)
        return ResultFromScode(DATA_E_FORMATETC);

    //We only support IStorage and IStream
    if (!(TYMED_ISTORAGE & pFE->tymed)
        && !(TYMED_ISTREAM & pFE->tymed))
        return ResultFromScode(DATA_E_FORMATETC);

    hList=m_pObj->m_hList;
    cItems=(UINT)SendMessage(hList, LB_GETCOUNT, 0, 0L);

    for (i=0; i < cItems; i++)
        {
        cb=SendMessage(hList, LB_GETTEXT, i, (LPARAM)&pRen);

        if (LB_ERR!=cb)
            {
            /*
             * When we find a matching FORMATETC, we know we're
             * only looking for IStorage or IStream (we checked
             * above), so use IStorage::CopyTo or IStream::CopyTo
             * to make the copy.
             */
            if (pFE->cfFormat==pRen->fe.cfFormat
                && (pFE->tymed & pRen->fe.tymed)
                && pFE->dwAspect==pRen->fe.dwAspect)
                {
                if (TYMED_ISTORAGE==pFE->tymed)
                    {
                    pSTM->tymed=TYMED_ISTORAGE;
                    return pRen->stm.pstg->CopyTo(NULL, NULL
                        , NULL, pSTM->pstg);
                    }
                else
                    {
                    STATSTG     st;

                    pRen->stm.pstm->Stat(&st, STATFLAG_NONAME);
                    pSTM->tymed=TYMED_ISTREAM;

                    return pRen->stm.pstm->CopyTo(pSTM->pstm
                        , st.cbSize, NULL, NULL);
                    }
                }
            }
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
    UINT        i, cItems;
    PRENDERING  pRen;
    DWORD       cb;
    HWND        hList;

    if (NULL==m_pObj->m_hList || NULL==pFE)
        return ResultFromScode(S_FALSE);

    hList=m_pObj->m_hList;
    cItems=(UINT)SendMessage(hList, LB_GETCOUNT, 0, 0L);

    for (i=0; i < cItems; i++)
        {
        cb=SendMessage(hList, LB_GETTEXT, i, (LPARAM)&pRen);

        if (LB_ERR!=cb)
            {
            /*
             * Check if the requested FORMATETC is the same as one
             * that we already have.
             */
            if (pFE->cfFormat==pRen->fe.cfFormat
                && (pFE->tymed & pRen->fe.tymed)
                && pFE->dwAspect==pRen->fe.dwAspect)
                {
                return NOERROR;
                }
            }
        }

    return ResultFromScode(S_FALSE);
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
    PRENDERING      prn;

    //We have to remain responsible for the data.
    if (!fRelease)
        return ResultFromScode(E_FAIL);

    //If we're handed NULLs, that means clean out the list.
    if (NULL==pFE || NULL==pSTM)
        {
        m_pObj->Purge();
        return NOERROR;
        }

    /*
     * Here we take the rendering we're given and attach it to the
     * end of the list.  We save the original pSTM->pUnkForRelease
     * and replace it with our own such that each 'copy' of this
     * data is actually just a reference count.
     */

    prn=new RENDERING;

    if (NULL==prn)
        return ResultFromScode(E_OUTOFMEMORY);

    prn->fe=*pFE;
    prn->stm=*pSTM;
    prn->pUnkOrg=pSTM->pUnkForRelease;
    prn->stm.pUnkForRelease=this;

    SendMessage(m_pObj->m_hList, LB_ADDSTRING, 0, (LONG)prn);
    return NOERROR;
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
    PCEnumFormatEtc     pEnum;

    *ppEnum=NULL;

    /*
     * From an external point of view there are no SET formats,
     * because we want to allow the user of this component object
     * to be able to stuff ANY format in via Set.  Only external
     * users will call EnumFormatEtc and they can only Get.
     */

    switch (dwDir)
        {
        case DATADIR_GET:
             pEnum=new CEnumFormatEtc(m_pUnkOuter);
             break;

        case DATADIR_SET:
        default:
            pEnum=NULL;
            break;
        }

    if (NULL==pEnum)
        return ResultFromScode(E_FAIL);
    else
        {
        //Let the enumerator copy our format list.
        if (!pEnum->Init(m_pObj->m_hList))
            {
            delete pEnum;
            return ResultFromScode(E_FAIL);
            }

        pEnum->AddRef();
        }

    *ppEnum=pEnum;
    return NOERROR;
    }





/*
 * CImpIDataObject::GetCanonicalFormatEtc
 * CImpIDataObject::DAdvise
 * CImpIDataObject::DUnadvise
 * CImpIDataObject::EnumDAdvise
 *
 * Trivial member functions.
 */

STDMETHODIMP CImpIDataObject::GetCanonicalFormatEtc
    (LPFORMATETC pFEIn, LPFORMATETC pFEOut)
    {
    return ResultFromScode(DATA_S_SAMEFORMATETC);
    }

STDMETHODIMP CImpIDataObject::DAdvise(LPFORMATETC pFE
    , DWORD dwFlags, LPADVISESINK pIAdviseSink, LPDWORD pdwConn)
    {
    return ResultFromScode(E_FAIL);
    }

STDMETHODIMP CImpIDataObject::DUnadvise(DWORD dwConn)
    {
    return ResultFromScode(E_FAIL);
    }

STDMETHODIMP CImpIDataObject::EnumDAdvise(LPENUMSTATDATA *ppEnum)
    {
    return ResultFromScode(E_FAIL);
    }
