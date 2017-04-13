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
**  mydisp.cpp
**
**  CMyDispatch implementation
**
**  Written by Microsoft Product Support Services, Windows Developer Support
**
**  The CMyDispatch object implement IUnknown & IDispatch for all the automation
**  objects in this sample. All objects derive from CMyDispatch.
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
 
/*
 * CMyDispatch::CMyDispatch
 *
 * Purpose:
 *  Constructor for CMyDispatch object. Initializes members to NULL.
 *
 */
CMyDispatch::CMyDispatch()
{    
    m_ptinfo = NULL;
    m_cRef = 0;
}

/*
 * CMyDispatch::~CMyDispatch
 *
 * Purpose:
 *  Destructor for CMyDispatch object. 
 *
 */
CMyDispatch::~CMyDispatch()
{    
     if (m_ptinfo) m_ptinfo->Release();                   
}

/*
 * CMyDispatch::QueryInterface, AddRef, Release
 *
 * Purpose:
 *  Implements IUnknown::QueryInterface, AddRef, Release
 *
 */
 
STDMETHODIMP
CMyDispatch::QueryInterface(REFIID iid, void FAR* FAR* ppv) 
{   
    *ppv = NULL;
        
    if (iid == IID_IUnknown) 
        *ppv = this;   
    else if (iid == IID_IDispatch)
        *ppv = this;     
    else if (iid == GetInterfaceID())
        *ppv = this;
    else return E_NOINTERFACE; 

    AddRef();
    return NOERROR;    
}


STDMETHODIMP_(ULONG)
CMyDispatch::AddRef(void)
{
#ifdef _DEBUG  
    TCHAR ach[150];
    wsprintf(ach, TEXT("Ref = %ld, Object = %s\r\n"), m_cRef+1, m_szClassName); 
    OutputDebugString(ach); 
#endif    
    return ++m_cRef;
}


STDMETHODIMP_(ULONG)
CMyDispatch::Release(void)
{
#ifdef _DEBUG  
    TCHAR ach[150];
    wsprintf(ach, TEXT("Ref = %ld, Object = %s\r\n"), m_cRef-1, m_szClassName); 
    OutputDebugString(ach);
#endif  
    if(--m_cRef == 0)
    {
        delete this;
        return 0;
    }
    return m_cRef;
} 

/*
 * CMyDispatch::GetTypeInfoCount
 *
 * Purpose:
 *  Implements IDispatch::GetTypeInfoCount.
 *
 */
STDMETHODIMP
CMyDispatch::GetTypeInfoCount(UINT FAR* pctinfo)
{
    *pctinfo = 1;
    return NOERROR;
}

/*
 * CMyDispatch::GetTypeInfo
 *
 * Purpose:
 *  Implements IDispatch::GetTypeInfo. 
 *
 */
STDMETHODIMP
CMyDispatch::GetTypeInfo(
      UINT itinfo,
      LCID lcid,
      ITypeInfo FAR* FAR* pptinfo)
{    
    *pptinfo = NULL;
     
    if(itinfo != 0)
        return DISP_E_BADINDEX;
    
    m_ptinfo->AddRef(); 
    *pptinfo = m_ptinfo;
    
    return NOERROR;
}

/*
 * CMyDispatch::GetIDsOfNames
 *
 * Purpose:
 *  Implements IDispatch::GetIDsOfNames.  The standard implementation, DispGetIDsOfNames,
 *  is used.
 *
 */
STDMETHODIMP 
CMyDispatch::GetIDsOfNames(
      REFIID riid,
      OLECHAR FAR* FAR* rgszNames,
      UINT cNames,
      LCID lcid,
      DISPID FAR* rgdispid)
{
    return DispGetIDsOfNames(m_ptinfo, rgszNames, cNames, rgdispid);
}

/*
 * CMyDispatch::Invoke
 *
 * Purpose:
 *  Implements IDispatch::Invoke.  The standard implementation, DispInvoke,
 *  is used. Properties and methods  will
 *  set m_bRaiseException to raise an exception. 
 *
 */
STDMETHODIMP
CMyDispatch::Invoke(
      DISPID dispidMember,
      REFIID riid,
      LCID lcid,
      WORD wFlags,
      DISPPARAMS FAR* pdispparams,
      VARIANT FAR* pvarResult,
      EXCEPINFO FAR* pexcepinfo,
      UINT FAR* puArgErr)
{  
    HRESULT hr;
   
    m_bRaiseException = FALSE;         
    hr =  DispInvoke(
        this, m_ptinfo,
        dispidMember, wFlags, pdispparams,
        pvarResult, pexcepinfo, puArgErr); 
    if (m_bRaiseException) 
    {
       if (NULL != pexcepinfo)
           _fmemcpy(pexcepinfo, &m_excepinfo, sizeof(EXCEPINFO));  
       return DISP_E_EXCEPTION; 
    }
    else return hr;   
} 

/*
 * CMyDispatch::LoadTypeInfo
 *
 *  Purpose:
 *   Gets type information of an object's interface from type library.
 *
 * Parameters:
 *  clsid               Interface id of object in type library. 
 *
 * Return Value:
 *  HRESULT
 *
 */
STDMETHODIMP
CMyDispatch::LoadTypeInfo(REFCLSID clsid)
{                          
    HRESULT hr;
    LPTYPELIB ptlib = NULL;
    LPTYPEINFO ptinfo = NULL;
    
    // Load Type Library. If required, notify user on failure.
    hr = LoadRegTypeLib(LIBID_BrowseHelper, 1, 0, 0x09, &ptlib);
    if (FAILED(hr))
        return hr; 
    
    // Get type information for interface of the object.      
    hr = ptlib->GetTypeInfoOfGuid(clsid, &ptinfo);
    if (FAILED(hr))  
    { 
        ptlib->Release();
        return hr;
    }   

    ptlib->Release();
    m_ptinfo = ptinfo;
    return NOERROR;
}

/*
 * CMyDispatch::RaiseException
 *
 *  Purpose:
 *   Raises exception so CMyDispatch::Invoke will return DISP_E_EXCEPTION
 *
 * Parameters:
 *  nID               ID of exception to be raised.
 *
 */
STDMETHODIMP_(void)
CMyDispatch::RaiseException(int nID)
{   
    extern HINSTANCE g_hinst;
    extern TCHAR g_szServerName[];     
    TCHAR szError[STR_LEN];
    
    _fmemset(&m_excepinfo, 0, sizeof(EXCEPINFO));
    
    m_excepinfo.wCode = nID;
    if (LoadString(g_hinst, nID, szError, sizeof(szError)))
        m_excepinfo.bstrDescription = SysAllocString(TO_OLE_STRING(szError));    
    m_excepinfo.bstrSource = SysAllocString(TO_OLE_STRING(g_szServerName));
    
    m_bRaiseException = TRUE; 
}
