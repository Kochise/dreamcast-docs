/*
 * IENUMFE.CPP
 * Data Tranfer Object for Chapter 12
 *
 * IEnumFORMATETC implementation specifically for the Data Tranfer
 * objects.  This enumerator copies the state of the data list in
 * the data object and uses that to maintain what FORMATETCs it
 * knows.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "dataobj.h"


extern HINSTANCE g_hInst;


/*
 * CEnumFormatEtc::CEnumFormatEtc
 * CEnumFormatEtc::~CEnumFormatEtc
 *
 * Parameters (Constructor):
 *  pUnkRef         LPUNKNOWN to use for reference counting.
 */

CEnumFormatEtc::CEnumFormatEtc(LPUNKNOWN pUnkRef)
    {
    m_cRef=0;
    m_pUnkRef=pUnkRef;
    m_iCur=0;
    m_cItems=0;
    return;
    }


CEnumFormatEtc::~CEnumFormatEtc(void)
    {
    if (NULL!=m_prgfe)
        {
        LPMALLOC    pIMalloc;

        if (SUCCEEDED(CoGetMalloc(MEMCTX_TASK, &pIMalloc)))
            {
            pIMalloc->Free(m_prgfe);
            pIMalloc->Release();
            }
        }

    return;
    }



/*
 * CEnumFormatEtc::Init
 *
 * Purpose:
 *  Copies the FORMATETCs in the data object's listbox into our
 *  own, that is, we make a snapshot for this enumerator.
 *
 * Parameters:
 *  hList           HWND of the listbox containing RENDERINGs
 *
 * Return Value:
 *  BOOL            TRUE if initialization worked,
 *                  FALSE otherwise.
 */
BOOL CEnumFormatEtc::Init(HWND hList)
    {
    UINT        i, cItems;
    LPMALLOC    pIMalloc;
    PRENDERING  pRen;
    LPFORMATETC pFE;
    DWORD       cb;

    if (NULL==hList)
        return FALSE;

    cItems=(UINT)SendMessage(hList, LB_GETCOUNT, 0, 0L);

    if (FAILED(CoGetMalloc(MEMCTX_TASK, &pIMalloc)))
        return FALSE;

    m_prgfe=(LPFORMATETC)pIMalloc->Alloc(cItems*sizeof(FORMATETC));
    pIMalloc->Release();

    if (NULL!=m_prgfe)
        {
        pFE=m_prgfe;

        for (i=0; i < cItems; i++)
            {
            cb=SendMessage(hList, LB_GETTEXT, i, (LPARAM)&pRen);

            if (LB_ERR!=cb)
                {
                //Copy just the FORMATETC
                *pFE++=pRen->fe;
                m_cItems++;
                }
            }
        }

    return TRUE;
    }



/*
 * CEnumFormatEtc::QueryInterface
 * CEnumFormatEtc::AddRef
 * CEnumFormatEtc::Release
 *
 * Purpose:
 *  IUnknown members for CEnumFormatEtc object.  For QueryInterface
 *  we only return out own interfaces and not those of the data
 *  object.  However, since enumerating formats only makes sense
 *  when the data object is around, we insure that it stays as
 *  long as we stay by calling an outer IUnknown for AddRef and
 *  Release.  But since we are not controlled by the lifetime of
 *  the outer object, we still keep our own reference count in
 *  order to free ourselves.
 */

STDMETHODIMP CEnumFormatEtc::QueryInterface(REFIID riid, PPVOID ppv)
    {
    *ppv=NULL;

    /*
     * Enumerators are separate objects, not the data object, so
     * we only need to support out IUnknown and IEnumFORMATETC
     * interfaces here with no concern for aggregation.
     */
    if (IID_IUnknown==riid || IID_IEnumFORMATETC==riid)
        *ppv=this;

    if (NULL!=*ppv)
        {
        ((LPUNKNOWN)*ppv)->AddRef();
        return NOERROR;
        }

    return ResultFromScode(E_NOINTERFACE);
    }


STDMETHODIMP_(ULONG) CEnumFormatEtc::AddRef(void)
    {
    ++m_cRef;
    m_pUnkRef->AddRef();
    return m_cRef;
    }

STDMETHODIMP_(ULONG) CEnumFormatEtc::Release(void)
    {
    m_pUnkRef->Release();

    if (0!=--m_cRef)
        return m_cRef;

    delete this;
    return 0;
    }







/*
 * CEnumFormatEtc::Next
 * CEnumFormatEtc::Skip
 * CEnumFormatEtc::Reset
 * CEnumFormatEtc::Clone
 *
 * Standard enumerator members for IEnumFORMATETC
 */

STDMETHODIMP CEnumFormatEtc::Next(ULONG cFE, LPFORMATETC pFE
    , ULONG *pulFE)
    {
    ULONG           cReturn=0L;

    if (NULL==m_prgfe)
        return ResultFromScode(S_FALSE);

    if (NULL==pulFE)
        {
        if (1L!=cFE)
            return ResultFromScode(E_POINTER);
        }
    else
        *pulFE=0L;

    if (NULL==pFE || m_iCur >= m_cItems)
        return ResultFromScode(S_FALSE);

    while (m_iCur < m_cItems && cFE > 0)
        {
        *pFE++=m_prgfe[m_iCur++];
        cReturn++;
        cFE--;
        }

    if (NULL!=pulFE)
        *pulFE=cReturn;

    return NOERROR;
    }


STDMETHODIMP CEnumFormatEtc::Skip(ULONG cSkip)
    {
    if ((m_iCur+cSkip) >= m_cItems)
        return ResultFromScode(S_FALSE);

    m_iCur+=cSkip;
    return NOERROR;
    }


STDMETHODIMP CEnumFormatEtc::Reset(void)
    {
    m_iCur=0;
    return NOERROR;
    }


STDMETHODIMP CEnumFormatEtc::Clone(LPENUMFORMATETC *ppEnum)
    {
    PCEnumFormatEtc     pNew;
    LPMALLOC            pIMalloc;
    LPFORMATETC         prgfe;
    BOOL                fRet=TRUE;
    ULONG               cb;

    *ppEnum=NULL;

    //Copy the memory for the list.
    if (FAILED(CoGetMalloc(MEMCTX_TASK, &pIMalloc)))
        return ResultFromScode(E_OUTOFMEMORY);

    cb=m_cItems*sizeof(FORMATETC);
    prgfe=(LPFORMATETC)pIMalloc->Alloc(cb);

    if (NULL!=prgfe)
        {
        //Copy the formats
        memcpy(prgfe, m_prgfe, (int)cb);

        //Create the clone
        pNew=new CEnumFormatEtc(m_pUnkRef);

        if (NULL!=pNew)
            {
            pNew->m_iCur=m_iCur;
            pNew->m_prgfe=prgfe;
            pNew->AddRef();
            fRet=TRUE;
            }
        }

    pIMalloc->Release();

    *ppEnum=pNew;
    return fRet ? NOERROR : ResultFromScode(E_OUTOFMEMORY);
    }
