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
**  param.cpp
**
**  CParameter implementation
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

/*
 * CParameter::Create
 *
 * Purpose:
 *  Creates an instance of the Parameter automation object and initializes it.
 *
 * Parameters:   
 *  ptinfo         TypeInfo in which the function of this parameter is contained.
 *  bstrName       Name of parameter
 *  ptypedesc      Type of parameter.
 *  pidldesc       IDLDESC of parameter.
 *  ppParameter    Returns Parameter automation object.
 *
 * Return Value:
 *  HRESULT
 *
 */
HRESULT 
CParameter::Create(LPTYPEINFO ptinfo, BSTR bstrName, TYPEDESC FAR* ptypedesc, 
     IDLDESC FAR* pidldesc, CParameter FAR* FAR* ppParameter) 
{   
    HRESULT hr;
    CParameter FAR* pParameter = NULL; 
    CTypeDesc FAR* pTypeDesc = NULL;
     
    *ppParameter = NULL;
    
    // Create object.
    pParameter = new CParameter();
    if (pParameter == NULL)
    {
        hr = E_OUTOFMEMORY; 
        goto error;
    }    
   // Load type information for the object from type library. 
    hr = pParameter->LoadTypeInfo(IID_IParameter);
    if (FAILED(hr))
        goto error; 

    pParameter->m_bstrName = SysAllocString(bstrName);   
    
    // Parameter type.     
    hr = CTypeDesc::Create(ptinfo, ptypedesc, &pTypeDesc);
    if (FAILED(hr))
        goto error;
    pTypeDesc->QueryInterface(IID_IDispatch, (LPVOID FAR*)&pParameter->m_pdispTypeDesc);
    
    pParameter->m_wIDLFlags = pidldesc->wIDLFlags;
#ifdef _DEBUG  
    lstrcpyn(pParameter->m_szClassName, TEXT("Parameter"), 100);
#endif
        
    *ppParameter = pParameter;
    return NOERROR;
    
error:                        
    if (pParameter == NULL) return E_OUTOFMEMORY;
    
    delete pParameter;
    return hr;
}

/*
 * CParameter::CParameter
 *
 * Purpose:
 *  Constructor for CParameter object. Initializes members to NULL.
 *
 */
CParameter::CParameter()
{   
    m_bstrName = NULL;  
    m_pdispTypeDesc = NULL;
}

/*
 * CParameter::~CParameter
 *
 * Purpose:
 *  Destructor for CParameter object. 
 *
 */
CParameter::~CParameter()
{    
     if (m_bstrName) SysFreeString(m_bstrName);
     if (m_pdispTypeDesc) m_pdispTypeDesc->Release();
}

STDMETHODIMP_(REFCLSID)
CParameter::GetInterfaceID()
{
    return IID_IParameter;
}

STDMETHODIMP_(BSTR)
CParameter::get_Name()
{
    return SysAllocString(m_bstrName);
}


STDMETHODIMP_(ITypeDesc FAR*)
CParameter::get_Type()
{
    m_pdispTypeDesc->AddRef();
    return (ITypeDesc FAR*)m_pdispTypeDesc;
} 

STDMETHODIMP_(int)
CParameter::get_IDLFlags()
{
    return (int)m_wIDLFlags;
}

STDMETHODIMP_(OBJTYPE)
CParameter::get_Kind()
{   
    return TYPE_PARAMETER;
}
