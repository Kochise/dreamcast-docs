/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1997 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          DataObj.cpp
   
   Description:   CDataObject and CEnumForamtEtc implementation.

**************************************************************************/

/**************************************************************************
   #include statements
**************************************************************************/

#include "DataObj.h"

/**************************************************************************

   CDataObject::CDataObject()
   
**************************************************************************/

CDataObject::CDataObject(COleDocument *pOleDoc)
{
OutputDebugString(TEXT("CDataObject's constructor\n"));
   
m_pOleDoc = pOleDoc;

m_pDataAdviseHolder = NULL;

m_cfEmbedSource = RegisterClipboardFormat(CF_EMBEDSOURCE);
}

/**************************************************************************

   CDataObject::~CDataObject()
   
**************************************************************************/

CDataObject::~CDataObject(void) 
{
if(m_pDataAdviseHolder)
   m_pDataAdviseHolder->Release();

OutputDebugString(TEXT("CDataObject's destructor\n"));
}

/**************************************************************************

   CDataObject::QueryInterface()
   
**************************************************************************/

STDMETHODIMP CDataObject::QueryInterface(REFIID riid, LPVOID *ppReturn)
{
OutputDebugString(TEXT("CDataObject::QueryInterface\n"));

return m_pOleDoc->QueryInterface(riid, ppReturn);
}

/**************************************************************************

   CDataObject::AddRef()
   
**************************************************************************/

STDMETHODIMP_(ULONG) CDataObject::AddRef()
{
OutputDebugString(TEXT("CDataObject::AddRef\n"));

return m_pOleDoc->AddRef();
}

/**************************************************************************

   CDataObject::Release()
   
**************************************************************************/

STDMETHODIMP_(ULONG) CDataObject::Release()
{
OutputDebugString(TEXT("CDataObject::Release\n"));
   
return m_pOleDoc->Release();
}

/**************************************************************************

   CDataObject::QueryGetData()
   
**************************************************************************/

STDMETHODIMP CDataObject::QueryGetData(LPFORMATETC pformatetc)
{
OutputDebugString(TEXT("CDataObject::QueryGetData\n"));

HRESULT  hr = DATA_E_FORMATETC;

// check the validity of the formatetc.
if( (pformatetc->cfFormat == m_cfEmbedSource)  &&
    (pformatetc->dwAspect == DVASPECT_CONTENT) &&
    (pformatetc->tymed == TYMED_ISTORAGE))
   {
   hr = S_OK;
   }

return hr;
}

/**************************************************************************

   CDataObject::DAdvise()
   
**************************************************************************/

STDMETHODIMP CDataObject::DAdvise(  LPFORMATETC pFormatetc, 
                                    DWORD advf,
                                    LPADVISESINK pAdvSink, 
                                    LPDWORD pdwConnection)
{
OutputDebugString(TEXT("CDataObject::DAdvise\n"));

// if no DataAdviseHolder has been created, then create one.
if(!m_pDataAdviseHolder)
   CreateDataAdviseHolder(&m_pDataAdviseHolder);

if(m_pDataAdviseHolder)
   {
   // pass on to the DataAdviseHolder
   return m_pDataAdviseHolder->Advise(this, pFormatetc, advf, pAdvSink, pdwConnection);
   }

return E_FAIL;
}

/**************************************************************************

   CDataObject::DUnadvise()
   
**************************************************************************/

STDMETHODIMP CDataObject::DUnadvise(DWORD dwConnection)
{
OutputDebugString(TEXT("CDataObject::DUnadvise\n"));

if(m_pDataAdviseHolder)
   {
   // pass on to the DataAdviseHolder
   return m_pDataAdviseHolder->Unadvise(dwConnection);
   }

return E_FAIL;
}

/**************************************************************************

   CDataObject::GetData()
   
**************************************************************************/

STDMETHODIMP CDataObject::GetData(LPFORMATETC pFE, LPSTGMEDIUM pStgMedium)
{
OutputDebugString(TEXT("CDataObject::GetData\n"));

HRESULT  hr = E_NOTIMPL;

return hr;
}

/**************************************************************************

   CDataObject::GetDataHere()
   
**************************************************************************/

STDMETHODIMP CDataObject::GetDataHere(LPFORMATETC pFormatEtc, LPSTGMEDIUM pStgMedium)
{
OutputDebugString(TEXT("CDataObject::GetDataHere\n"));

HRESULT  hr = DATA_E_FORMATETC;

if(pFormatEtc->cfFormat == m_cfEmbedSource)
   {
   hr = GetOleObjectDataHere( m_pOleDoc->m_pPersistStorage,
                              pFormatEtc,
                              pStgMedium);
   }

return hr;
}

/**************************************************************************

   CDataObject::GetCanonicalFormatEtc()
   
**************************************************************************/

STDMETHODIMP CDataObject::GetCanonicalFormatEtc(LPFORMATETC pformatetc, LPFORMATETC pformatetcOut)
{
OutputDebugString(TEXT("CDataObject::GetCanonicalFormatEtc\n"));

HRESULT hr;

if(!pformatetcOut)
   return E_INVALIDARG;

//set all out parameters to NULL.
pformatetcOut->ptd = NULL;

if(!pformatetc)
   return E_INVALIDARG;

// OLE2NOTE: we must validate that the format requested is supported
if(NOERROR != (hr = QueryGetData(pformatetc)))
   return hr;

/* OLE2NOTE: an app that is insensitive to target device (as
**    SimpSvr is) should fill in the lpformatOut parameter
**    but NULL out the "ptd" field; it should return NOERROR if the
**    input formatetc->ptd what non-NULL. this tells the caller
**    that it is NOT necessary to maintain a separate screen
**    rendering and printer rendering. if should return
**    DATA_S_SAMEFORMATETC if the input and output formatetc's are
**    identical.
*/

*pformatetcOut = *pformatetc;

if(NULL == pformatetc->ptd)
   return DATA_S_SAMEFORMATETC;

pformatetcOut->ptd = NULL;

return NOERROR;
}

/**************************************************************************

   CDataObject::SetData()
   
**************************************************************************/

STDMETHODIMP CDataObject::SetData(  LPFORMATETC pformatetc, 
                                    LPSTGMEDIUM pmedium,
                                    BOOL fRelease)
{
OutputDebugString(TEXT("CDataObject::SetData\n"));

return DATA_E_FORMATETC;
}

/**************************************************************************

   CDataObject::EnumFormatEtc()
   
**************************************************************************/

STDMETHODIMP CDataObject::EnumFormatEtc(  DWORD dwDirection,
                                          LPENUMFORMATETC *ppenumFormatEtc)
{
OutputDebugString(TEXT("CDataObject::EnumFormatEtc\n"));

// need to NULL the out parameter
*ppenumFormatEtc = NULL;

if(DATADIR_SET == dwDirection)
   return E_NOTIMPL;

*ppenumFormatEtc = new CEnumFormatEtc();

if(*ppenumFormatEtc)
   {
   (*ppenumFormatEtc)->AddRef();
   return S_OK;
   }

return E_OUTOFMEMORY;
}

/**************************************************************************

   CDataObject::EnumDAdvise()
   
**************************************************************************/

STDMETHODIMP CDataObject::EnumDAdvise(LPENUMSTATDATA *ppenumAdvise)
{
OutputDebugString(TEXT("CDataObject::EnumDAdvise\n"));

// need to NULL the out parameter
*ppenumAdvise = NULL;

return m_pDataAdviseHolder->EnumAdvise(ppenumAdvise);
}

//////////////////////////////////////////////////////////////////////////////
//
// CEnumFormatEtc Implementation
//

/**************************************************************************

   CEnumFormatEtc::CEnumFormatEtc()
   
**************************************************************************/

CEnumFormatEtc::CEnumFormatEtc()
{
OutputDebugString(TEXT("CEnumFormatEtc's constructor\n"));

m_ObjRefCount = 0;

m_iCur = 0;

m_cfEmbedSource = RegisterClipboardFormat(CF_EMBEDSOURCE);
}

/**************************************************************************

   CEnumFormatEtc::~CEnumFormatEtc()
   
**************************************************************************/

CEnumFormatEtc::~CEnumFormatEtc(void)
{
OutputDebugString(TEXT("CEnumFormatEtc's destructor\n"));
}

/**************************************************************************

   CEnumFormatEtc::QueryInterface()
   
**************************************************************************/

STDMETHODIMP CEnumFormatEtc::QueryInterface(REFIID riid, LPVOID *ppReturn)
{
OutputDebugString(TEXT("CEnumFormatEtc::QueryInterface\n"));

*ppReturn = NULL;

if(IsEqualIID(riid, IID_IUnknown))
   {
   *ppReturn = (LPVOID)this;
   }
else if(IsEqualIID(riid, IID_IEnumFORMATETC))
   {
   *ppReturn = (LPVOID)this;
   }

if(NULL != *ppReturn)
   {
   ((LPUNKNOWN)*ppReturn)->AddRef();
   return NOERROR;
   }

return E_NOINTERFACE;
}

/**************************************************************************

   CEnumFormatEtc::AddRef()
   
**************************************************************************/

STDMETHODIMP_(ULONG) CEnumFormatEtc::AddRef(void)
{
OutputDebugString(TEXT("CEnumFormatEtc::AddRef\n"));

return ++m_ObjRefCount;
}

/**************************************************************************

   CEnumFormatEtc::Release()
   
**************************************************************************/

STDMETHODIMP_(ULONG) CEnumFormatEtc::Release(void)
{
TCHAR szText[MAX_PATH];
wsprintf(szText, TEXT("CEnumFormatEtc::Release - ref count will be %d\n"), m_ObjRefCount - 1);
OutputDebugString(szText);
   
if(0 == --m_ObjRefCount)
   {
   delete this;
   return 0;
   }

return m_ObjRefCount;
}

/**************************************************************************

   CEnumFormatEtc::Next()
   
**************************************************************************/

STDMETHODIMP CEnumFormatEtc::Next(ULONG cRequested, LPFORMATETC pFE, ULONG* puFetched)
{
OutputDebugString(TEXT("CEnumFormatEtc::Next\n"));

if(m_iCur > 0)
   {
   *puFetched = 0;
   return S_FALSE;
   }

pFE->cfFormat = m_cfEmbedSource;
pFE->dwAspect = DVASPECT_CONTENT;
pFE->tymed == TYMED_ISTORAGE;

*puFetched = 1;

m_iCur++;

return S_OK;
}

/**************************************************************************

   CEnumFormatEtc::Skip()
   
**************************************************************************/

STDMETHODIMP CEnumFormatEtc::Skip(ULONG cSkip)
{
OutputDebugString(TEXT("CEnumFormatEtc::Skip\n"));

if((m_iCur + cSkip) > 1)
   return S_FALSE;

m_iCur += cSkip;

return S_OK;
}

/**************************************************************************

   CEnumFormatEtc::Reset()
   
**************************************************************************/

STDMETHODIMP CEnumFormatEtc::Reset(void)
{
OutputDebugString(TEXT("CEnumFormatEtc::Reset\n"));

m_iCur = 0;

return S_OK;
}

/**************************************************************************

   CEnumFormatEtc::Clone()
   
**************************************************************************/

STDMETHODIMP CEnumFormatEtc::Clone(LPENUMFORMATETC* ppEnum)
{
OutputDebugString(TEXT("CEnumFormatEtc::Clone\n"));

CEnumFormatEtc* pNew;

*ppEnum = NULL;

// Create the clone.
pNew = new CEnumFormatEtc();
if (NULL == pNew)
   return (ResultFromScode(E_OUTOFMEMORY));

pNew->AddRef();
pNew->m_iCur = m_iCur;

*ppEnum = pNew;

return S_OK;
}

