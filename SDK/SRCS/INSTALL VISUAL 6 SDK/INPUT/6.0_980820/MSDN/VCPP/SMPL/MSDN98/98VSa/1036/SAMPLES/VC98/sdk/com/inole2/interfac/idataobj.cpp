/*
 * IDATAOBJ.CPP
 *
 * Template IDataObject interface implementation.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "idataobj.h"


/*
 * CImpIDataObject::CImpIDataObject
 * CImpIDataObject::~CImpIDataObject
 *
 * Parameters (Constructor):
 *  pObj            LPVOID of the object we're in.
 *  pUnkOuter       LPUNKNOWN to which we delegate.
 */

CImpIDataObject::CImpIDataObject(LPVOID pObj, LPUNKNOWN pUnkOuter)
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
 *  Delegating IUnknown members for CImpIDataObject.
 */

STDMETHODIMP CImpIDataObject::QueryInterface(REFIID riid
    , LPVOID *ppv)
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
 */

STDMETHODIMP CImpIDataObject::GetData(LPFORMATETC pFE
    , LPSTGMEDIUM pSTM)
    {
    return ResultFromScode(DATA_E_FORMATETC);
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
 */

STDMETHODIMP CImpIDataObject::GetDataHere(LPFORMATETC pFE
    , LPSTGMEDIUM pSTM)
    {
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
 */

STDMETHODIMP CImpIDataObject::QueryGetData(LPFORMATETC pFE)
    {
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
 */

STDMETHODIMP CImpIDataObject::GetCanonicalFormatEtc(LPFORMATETC pFEIn
    , LPFORMATETC pFEOut)
    {
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
 */

STDMETHODIMP CImpIDataObject::SetData(LPFORMATETC pFE
    , LPSTGMEDIUM pSTM, BOOL fRelease)
    {
    return ResultFromScode(DATA_E_FORMATETC);
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
 */

STDMETHODIMP CImpIDataObject::EnumFormatEtc(DWORD dwDir
    , LPENUMFORMATETC *ppEnum)
    {
    return ResultFromScode(E_FAIL);
    }





/*
 * CImpIDataObject::DAdvise
 *
 * Purpose:
 *  Provides the data object with an IAdviseSink object that we are
 *  responsible to notify when the data changes.
 *
 * Parameters:
 *  ppFE            LPFORMATETC
 *  dwFlags         DWORD carrying flags indicating how the advise
 *                  sink wants to be treated.
 *  pIAdviseSink    LPADVISESINK to the object to notify
 *  pdwConn         LPDWORD into which we store a DWORD key
 *                  identifying the advise connection.
 */

STDMETHODIMP CImpIDataObject::DAdvise(LPFORMATETC pFE, DWORD dwFlags
    , LPADVISESINK pIAdviseSink, LPDWORD pdwConn)
    {
    return ResultFromScode(E_OUTOFMEMORY);
    }






/*
 * CImpIDataObject::DUnadvise
 *
 * Purpose:
 *  Turns off advising previously set up with Advise.
 *
 * Parameters:
 *  dwConn          DWORD connection key returned from Advise.
 */

STDMETHODIMP CImpIDataObject::DUnadvise(DWORD dwConn)
    {
    return ResultFromScode(E_FAIL);
    }






/*
 * CImpIDataObject::EnumDAdvise
 *
 * Purpose:
 *  Returns an enumerator object through which the caller can find
 *  all the agents currently receiving advises on this data object.
 *
 * Parameters:
 *  ppEnum          LPENUMSTATDATA * in which to return the
 *                  enumerator.
 */

STDMETHODIMP CImpIDataObject::EnumDAdvise(LPENUMSTATDATA *ppEnum)
    {
    return ResultFromScode(E_FAIL);
    }
