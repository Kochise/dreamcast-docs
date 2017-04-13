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
**  OLE Simple InProc Automation Object.
**
**  Applicationcf.cpp
**
**  CApplicationCF (class factory) implementation
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
#include "lines.h" 

CApplicationCF::CApplicationCF(void)
{    
    m_cRef = 0; 
}

/*
 * CApplicationCF::QueryInterface, AddRef, Release
 *
 * Purpose:
 *  Implements IUnknown::QueryInterface, AddRef, Release
 *
 */
STDMETHODIMP
CApplicationCF::QueryInterface(REFIID iid, void FAR* FAR* ppv) 
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
CApplicationCF::AddRef(void)
{
    return ++m_cRef;
}


STDMETHODIMP_(ULONG)
CApplicationCF::Release(void)
{   
    if(--m_cRef == 0)
    {
        delete this;
        return 0;
    }
    return m_cRef;
}

/*
 * CApplicationCF::CreateInstance, LockServer
 *
 * Purpose:
 *  Implements IClassFactory::CreateInstance, LockServer
 *
 */
STDMETHODIMP
CApplicationCF::CreateInstance(IUnknown FAR* punkOuter,
                         REFIID riid,
                         void FAR* FAR* ppv)
{
    HRESULT hr;
    
    *ppv = NULL;
    
    // This implementation does'nt allow aggregation
    if (punkOuter)
        return CLASS_E_NOAGGREGATION;
    
    // This is REGCLS_SINGLEUSE class factory, so CreateInstance will be
    // called atmost once. An application objects has a REGCLS_SINGLEUSE class
    // factory. The global application object has already been created when 
    // CreateInstance is called. A REGCLS_MULTIPLEUSE class factory's 
    // CreateInstance would be called multiple times and would create a new 
    // object each time. An MDI application would have a REGCLS_MULTIPLEUSE 
    // class factory for it's document objects.             
    hr = g_pApplication->QueryInterface(riid, ppv);
    if (FAILED(hr)) 
    {
        g_pApplication->Quit();
        return hr;
    }   
    return NOERROR;
}

STDMETHODIMP
CApplicationCF::LockServer(BOOL fLock)
{
    CoLockObjectExternal(g_pApplication, fLock, TRUE); 
    return NOERROR;     
}
