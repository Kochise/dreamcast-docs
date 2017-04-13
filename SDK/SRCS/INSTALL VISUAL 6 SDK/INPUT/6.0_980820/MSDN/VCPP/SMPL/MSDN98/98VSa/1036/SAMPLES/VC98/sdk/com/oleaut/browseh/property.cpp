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
**  OLE Automation Property Browse Helper Sample
**
**  property.cpp
**
**  CProperty implementation
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
 * CProperty::Create
 *
 * Purpose:
 *  Creates an instance of the Property automation object and initializes it.
 *
 * Parameters:   
 *  ptinfo        TypeInfo in which this property/variable is contained.
 *  pvardesc      VARDESC that descrribes this property/variable.
 *  ppProperty    Returns Property automation object.
 *
 * Return Value:
 *  HRESULT
 *
 */
HRESULT 
CProperty::Create(LPTYPEINFO ptinfo, LPVARDESC pvardesc, CProperty FAR* FAR* ppProperty) 
{   
    HRESULT hr;
    CProperty FAR* pProperty = NULL;   
    BSTR bstr;  
    unsigned int cNames;
    CTypeDesc FAR* pTypeDesc = NULL;
     
    *ppProperty = NULL;
    
    // Create object.
    pProperty = new CProperty();
    if (pProperty == NULL)
    {
        hr = E_OUTOFMEMORY; 
        goto error;
    }   
    
   // Load type information for the object from type library. 
    hr = pProperty->LoadTypeInfo(IID_IProperty);
    if (FAILED(hr))
        goto error; 
    
    pProperty->m_memid = pvardesc->memid; 
    ptinfo->GetNames(pvardesc->memid, &bstr, 1, &cNames);    
    pProperty->m_bstrName = bstr;
    
    // Property type
    hr = CTypeDesc::Create(ptinfo, &pvardesc->elemdescVar.tdesc, &pTypeDesc);
    if (FAILED(hr))
        goto error;
    pTypeDesc->QueryInterface(IID_IDispatch, (LPVOID FAR*)&pProperty->m_pdispTypeDesc);
    
    hr = ptinfo->GetDocumentation(pvardesc->memid, NULL, &pProperty->m_bstrDocumentation,
             &pProperty->m_ulHelpContext, &pProperty->m_bstrHelpFile);    
    if (FAILED(hr))
        goto error;

#ifdef _DEBUG  
    lstrcpyn(pProperty->m_szClassName, TEXT("Property"), 100);
#endif 
        
    *ppProperty = pProperty;
    return NOERROR;
    
error:                        
    if (pProperty == NULL) return E_OUTOFMEMORY;
    if (pProperty->m_bstrName) SysFreeString(pProperty->m_bstrName);
    if (pProperty->m_bstrDocumentation) SysFreeString(pProperty->m_bstrDocumentation);
    if (pProperty->m_bstrHelpFile) SysFreeString(pProperty->m_bstrHelpFile);   
    
    // Set to NULL to prevent destructor from attempting to free again
    pProperty->m_bstrName = NULL;
    pProperty->m_bstrDocumentation = NULL;
    pProperty->m_bstrHelpFile = NULL;    

    delete pProperty;
    return hr;
}

/*
 * CProperty::CProperty
 *
 * Purpose:
 *  Constructor for CProperty object. Initializes members to NULL.
 *
 */
CProperty::CProperty()
{   
    m_bstrName = NULL;
    m_bstrDocumentation = NULL;
    m_bstrHelpFile = NULL;      
    m_pdispTypeDesc = NULL;
}

/*
 * CProperty::~CProperty
 *
 * Purpose:
 *  Destructor for CProperty object. 
 *
 */
CProperty::~CProperty()
{    
     if (m_bstrName) SysFreeString(m_bstrName);
     if (m_bstrDocumentation) SysFreeString(m_bstrDocumentation);
     if (m_bstrHelpFile) SysFreeString(m_bstrHelpFile);    
     if (m_pdispTypeDesc) m_pdispTypeDesc->Release();
}

STDMETHODIMP_(REFCLSID)
CProperty::GetInterfaceID()
{
    return IID_IProperty;
}

STDMETHODIMP_(BSTR)
CProperty::get_Name()
{
    return SysAllocString(m_bstrName);
}   

STDMETHODIMP_(BSTR)
CProperty::get_Documentation()     
{
    return SysAllocString(m_bstrDocumentation);
}  

STDMETHODIMP_(long)
CProperty::get_HelpContext()     
{
    return (long)m_ulHelpContext;
}

STDMETHODIMP_(BSTR)
CProperty::get_HelpFile()     
{
    return SysAllocString(m_bstrHelpFile);
}   


STDMETHODIMP_(ITypeDesc FAR*)
CProperty::get_Type()
{
    m_pdispTypeDesc->AddRef();
    return (ITypeDesc FAR*)m_pdispTypeDesc;
}   

STDMETHODIMP_(MEMBERID)
CProperty::get_Memberid()
{
    return m_memid;
} 

STDMETHODIMP_(OBJTYPE)
CProperty::get_Kind()
{   
    return TYPE_PROPERTY;
}
