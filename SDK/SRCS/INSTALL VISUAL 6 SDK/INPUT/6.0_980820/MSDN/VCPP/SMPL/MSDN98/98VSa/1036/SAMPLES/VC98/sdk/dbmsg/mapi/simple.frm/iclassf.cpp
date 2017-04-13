//////////////////////////////////////////////////////////////////////////////
//
//  FILE:           ICLASSF.CPP
//
//  DESCRIPTION:    Sample form's class factory
//
//
//  Copyright (c) 1994, Microsoft Corporation.
//  All rights reserved.
//
//--

#include "precomp.h"

CClassFactory           ClassFactory;

HWND  CClassFactory::ms_hWndMain;
ULONG CClassFactory::ms_cLocks= 0;
ULONG CClassFactory::ms_cObjs = 0;


///////////////////////////////////////////////////////////////////////////////
//
//  Constructor and destructor

CClassFactory::CClassFactory()
{
    m_cRef   = 1;
}

CClassFactory::~CClassFactory (void)
{
    ASSERT(m_cRef == 1);
}


///////////////////////////////////////////////////////////////////////////////
//
//  IUnknown methods

STDMETHODIMP CClassFactory::QueryInterface(REFIID riid, void ** ppvObj)
{

    if ((IID_IClassFactory == riid) || (IID_IUnknown == riid))
    {
        *ppvObj = (IClassFactory*) this;
        AddRef ();
        return NOERROR;
    }

    *ppvObj = 0;

    return ResultFromScode (E_NOINTERFACE);
}


STDMETHODIMP_ (ULONG)CClassFactory::AddRef()
{
    return ++ m_cRef;
}

STDMETHODIMP_(ULONG) CClassFactory::Release()
{
    ULONG cRef = -- m_cRef;

    //We quit when cRef == 1 (as oppossed to == 0) because OLE
    //will not release its reference until after we call
    // CoRevokeClassObject(). So if cRef==1 we know that only
    //OLE has a reference to as, and it's time to go...
    if ((cRef == 1) && (ms_cLocks == 0) && (ms_cObjs == 0))
    {
        if (ms_hWndMain)
        {
            PostMessage (ms_hWndMain, WM_CLOSE, 0, 0L);
        }
    }

    return cRef;
}


///////////////////////////////////////////////////////////////////////////////
//

STDMETHODIMP CClassFactory::CreateInstance(LPUNKNOWN pUnkOuter, REFIID riid,
                                           LPVOID FAR* ppvObject)
{
    HRESULT     hr  = ResultFromScode (E_NOINTERFACE);
    CBaseForm * pbf = NULL;

    if (!ppvObject)
        return ResultFromScode (E_INVALIDARG);
    
    *ppvObject = 0;

    //
    //  We don't support aggregation.

    if (pUnkOuter != NULL)
        return  ResultFromScode (CLASS_E_NOAGGREGATION);

    pbf = new CBaseForm (this);

    if(NULL == pbf)
        return ResultFromScode(E_OUTOFMEMORY);

    hr = pbf -> QueryInterface (riid, ppvObject);
    if (HR_FAILED(hr))
        goto err;

    ms_cObjs ++;

    hr = hrSuccess;

err:
    if (pbf)
    {
        pbf -> Release ();
    }
    return hr;
}


///////////////////////////////////////////////////////////////////////////////
//

STDMETHODIMP CClassFactory::LockServer(BOOL fLock)
{
    if (fLock)
    {
        ++ ms_cLocks;
    }
    else
    {
        ASSERT (ms_cLocks > 0);
        -- ms_cLocks;

        if ((ms_cLocks == 0) && (ms_cObjs == 0))
        {
            if (ms_hWndMain)
            {
                PostMessage (ms_hWndMain, WM_CLOSE, 0, 0L);
            }
        }
    }
    return NOERROR;
}


void FAR PASCAL CClassFactory::ObjDestroyedCallback (void)
{
    ASSERT (ms_cObjs > 0);
    ms_cObjs --;

    if ((ms_cLocks == 0) && (ms_cObjs == 0))
    {
        if (ms_hWndMain)
        {
            PostMessage (ms_hWndMain, WM_CLOSE, 0, 0L);
        }
    }
}
