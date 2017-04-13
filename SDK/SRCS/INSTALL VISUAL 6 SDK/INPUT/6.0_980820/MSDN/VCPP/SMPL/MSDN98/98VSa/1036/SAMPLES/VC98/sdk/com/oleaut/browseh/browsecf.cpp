/*************************************************************************
**
**  This is a part of the Microsoft Source Code Samples.
**
**  Copyright (C) 1992-1997 Microsoft Corporation. All rights reserved.
**
**  This source code is only intended as a supplement to Microsoft Development
**  Tools and/or WinHelp documentation.  See these sources for detailed
**  information regarding the Microsoft samples programs.
**
**  OLE Automation TypeLibrary Browse Helper Sample
**
**  BrowseHelpercf.cpp
**
**  CBrowseHelperCF (class factory) implementation
**
**  Written by Microsoft Product Support Services, Windows Developer Support
**
*************************************************************************/
#include <windows.h>
#include <windowsx.h>
#ifdef WIN16   
  #include <ole2.h>
  #include <compobj.h>    
  #include <dispatch.h> 
  #include <variant.h>
  #include <olenls.h>  
#endif         
#include "browseh.h" 

CBrowseHelperCF::CBrowseHelperCF(void)
{    
    m_cRef = 0; 
}

/*
 * CBrowseHelperCF::QueryInterface, AddRef, Release
 *
 * Purpose:
 *  Implements IUnknown::QueryInterface, AddRef, Release
 *
 */
STDMETHODIMP
CBrowseHelperCF::QueryInterface(REFIID iid, void FAR* FAR* ppv) 
{   
    *ppv = NULL;
    
    if (iid == IID_IUnknown || iid == IID_IClassFactory)
        *ppv = this;
    else 
        return E_NOINTERFACE; 

    AddRef();
    return NOERROR;    
}


STDMETHODIMP_(ULONG)
CBrowseHelperCF::AddRef(void)
{
    return ++m_cRef;
}


STDMETHODIMP_(ULONG)
CBrowseHelperCF::Release(void)
{   
    if(--m_cRef == 0)
    {
        delete this;
        return 0;
    }
    return m_cRef;
}

/*
 * CBrowseHelperCF::CreateInstance, LockServer
 *
 * Purpose:
 *  Implements IClassFactory::CreateInstance, LockServer
 *
 */
STDMETHODIMP
CBrowseHelperCF::CreateInstance(IUnknown FAR* punkOuter,
                         REFIID riid,
                         void FAR* FAR* ppv)
{    
    CBrowseHelper FAR* pBrowseHelper;
    HRESULT hr;
    
    *ppv = NULL;
    
    // This implementation does not allow aggregation
    if (punkOuter)
        return CLASS_E_NOAGGREGATION;

    // Create an instance of the BrowseHelper automation object. 
    hr = CBrowseHelper::Create(&pBrowseHelper);       
    if (FAILED(hr))
        return hr;    
             
    hr = pBrowseHelper->QueryInterface(riid, ppv);
    if (FAILED(hr)) 
    {
        delete pBrowseHelper;
        return hr;
    }  
    return NOERROR;
}

STDMETHODIMP
CBrowseHelperCF::LockServer(BOOL fLock)
{
    extern ULONG g_cLock;
    
    if (fLock)
        g_cLock++;
    else
        g_cLock--;

    return NOERROR;       
}
