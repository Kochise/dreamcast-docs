/*
 * IDESCRIP.CPP
 * Link Source Chapter 9
 *
 * Implementation the IDescription interface that doesn't care
 * what object it works with in this LinkSource sample.  It
 * is given a storage in which it expects to find a stream
 * called "Description" containing the text relevant to the
 * object showing the instance of this interface.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "linksrc.h"

/*
 * CImpIDescription:CImpIDescription
 * CImpIDescription::~CImpIDescription
 * CImpIDescription::QueryInterface
 * CImpIDescription::AddRef
 * CImpIDescription::Release
 *
 * Basic object members.
 */

CImpIDescription::CImpIDescription(LPUNKNOWN pUnkOuter)
    {
    m_cRef=0;
    m_pUnkOuter=pUnkOuter;
    m_pIStorage=NULL;
    return;
    }

CImpIDescription::~CImpIDescription(void)
    {
    return;
    }

STDMETHODIMP CImpIDescription::QueryInterface(REFIID riid
    , LPVOID *ppv)
    {
    return m_pUnkOuter->QueryInterface(riid, ppv);
    }

STDMETHODIMP_(ULONG) CImpIDescription::AddRef(void)
    {
    ++m_cRef;
    return m_pUnkOuter->AddRef();
    }

STDMETHODIMP_(ULONG) CImpIDescription::Release(void)
    {
    --m_cRef;
    return m_pUnkOuter->Release();
    }


/*
 * CImpIDescription::GetText
 *
 * Purpose:
 *  Fills a buffer with our text description.
 *
 * Parameters:
 *  pszText         LPOLESTR to the buffer to fill
 *  cch             ULONG specifying the length of pszText
 *
 * Return Value:
 *  HRESULT         NOERROR if successful, error otherwise.
 */

HRESULT CImpIDescription::GetText(LPOLESTR pszText, ULONG cch)
    {
    HRESULT     hr;
    IStream    *pIStream;

    /*
     * The description text for this object is contained in
     * a stream called "Description" (constant SZDESCRIPTION
     * has this string) found in whatever storage we happen
     * to have.  This implementation is ignorant of the actual
     * object that is exposing it.
     */

    if (NULL==m_pIStorage)
        return ResultFromScode(E_FAIL);

    hr=m_pIStorage->OpenStream(SZDESCRIPTION, 0, STGM_DIRECT
        | STGM_READ | STGM_SHARE_EXCLUSIVE, 0, &pIStream);

    if (FAILED(hr))
        return ResultFromScode(E_FAIL);

   #ifdef WIN32ANSI
    char sz[512];
    hr=pIStream->Read((void *)sz, cch*sizeof(TCHAR), NULL);	
	MultiByteToWideChar(CP_ACP, 0, sz, -1, pszText, cch);    
   #else
    hr=pIStream->Read((void *)pszText, cch*sizeof(WCHAR), NULL);
   #endif
    pIStream->Release();

    return SUCCEEDED(hr) ? NOERROR : ResultFromScode(E_FAIL);
    }




/*
 * (Internal)
 * CImpIDescription::SetStorage
 *
 * Purpose:
 *  Provides objects using this interface implementation to
 *  inform us of the storage in which to look for the
 *  description stream.
 *
 * Parameters:
 *  pIStorage       IStorage * to hold.
 *
 * Return Value:
 *  None
 */

void CImpIDescription::SetStorage(IStorage *pIStorage)
    {
    /*
     * This may be the root storage for the File object, the
     * sub-storage for the first level object, or a sub-storage
     * for a second-level object.  Since the object exposing
     * this interface holds the storage itself, no AddRef is
     * required.
     */
    m_pIStorage=pIStorage;
    return;
    }
