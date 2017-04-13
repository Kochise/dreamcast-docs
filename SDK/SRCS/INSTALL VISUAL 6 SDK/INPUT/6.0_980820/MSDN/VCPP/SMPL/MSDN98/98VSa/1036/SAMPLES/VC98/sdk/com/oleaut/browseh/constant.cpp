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
**  OLE Automation Constant Browse Helper Sample
**
**  Constant.cpp
**
**  CConstant implementation
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
 * CConstant::Create
 *
 * Purpose:
 *  Creates an instance of the Constant automation object and initializes it.
 *
 * Parameters: 
 *  ptinfo        TypeInfo of which this constant is an element.
 *  pvardesc      VARDESC that describes this constant.
 *  ppConstant    Returns Constant automation object.
 *
 * Return Value:
 *  HRESULT
 *
 */
HRESULT 
CConstant::Create(LPTYPEINFO ptinfo, LPVARDESC pvardesc, CConstant FAR* FAR* ppConstant) 
{   
    HRESULT hr;
    CConstant FAR* pConstant = NULL;   
    BSTR bstr;  
    unsigned int cNames;        
    CTypeDesc FAR* pTypeDesc = NULL;
     
    *ppConstant = NULL;
    
    // Create object.
    pConstant = new CConstant();
    if (pConstant == NULL)
    {
        hr = E_OUTOFMEMORY; 
        goto error;
    }   
    
    // Load type information for the application object from type library. 
    hr = pConstant->LoadTypeInfo(IID_IConstant);
    if (FAILED(hr))
        goto error; 
    
    pConstant->m_memid = pvardesc->memid; 
    ptinfo->GetNames(pvardesc->memid, &bstr, 1, &cNames);    
    pConstant->m_bstrName = bstr;        
    
    // Type of constant.    
    hr = CTypeDesc::Create(ptinfo, &pvardesc->elemdescVar.tdesc, &pTypeDesc);
    if (FAILED(hr))
        goto error;
    pTypeDesc->QueryInterface(IID_IDispatch, (LPVOID FAR*)&pConstant->m_pdispTypeDesc);  
    
    // Constant value.
    if (pvardesc->varkind == VAR_CONST)
        pConstant->m_vValue = *pvardesc->lpvarValue;
    else goto error; 
    
    hr = ptinfo->GetDocumentation(pvardesc->memid, NULL, &pConstant->m_bstrDocumentation,
             &pConstant->m_ulHelpContext, &pConstant->m_bstrHelpFile);    
    if (FAILED(hr))
        goto error;

#ifdef _DEBUG  
    lstrcpyn(pConstant->m_szClassName, TEXT("Constant"), 100);
#endif 
        
    *ppConstant = pConstant;
    return NOERROR;
    
error:                        
    if (pConstant == NULL) return E_OUTOFMEMORY;
    if (pConstant->m_bstrName) SysFreeString(pConstant->m_bstrName);
    if (pConstant->m_bstrDocumentation) SysFreeString(pConstant->m_bstrDocumentation);
    if (pConstant->m_bstrHelpFile) SysFreeString(pConstant->m_bstrHelpFile);   
    
    // Set to NULL to prevent destructor from attempting to free again
    pConstant->m_bstrName = NULL;
    pConstant->m_bstrDocumentation = NULL;
    pConstant->m_bstrHelpFile = NULL;    

    delete pConstant;
    return hr;
}

/*
 * CConstant::CConstant
 *
 * Purpose:
 *  Constructor for CConstant object. Initializes members to NULL.
 *
 */
CConstant::CConstant()
{   
    m_bstrName = NULL;
    m_bstrDocumentation = NULL;
    m_bstrHelpFile = NULL;   
    m_pdispTypeDesc = NULL;
}

/*
 * CConstant::~CConstant
 *
 * Purpose:
 *  Destructor for CConstant object. 
 *
 */
CConstant::~CConstant()
{    
     if (m_bstrName) SysFreeString(m_bstrName);
     if (m_bstrDocumentation) SysFreeString(m_bstrDocumentation);
     if (m_bstrHelpFile) SysFreeString(m_bstrHelpFile); 
     if (m_pdispTypeDesc) m_pdispTypeDesc->Release();
}

STDMETHODIMP_(REFCLSID)
CConstant::GetInterfaceID()
{
    return IID_IConstant;
}


STDMETHODIMP_(BSTR)
CConstant::get_Name()
{
    return SysAllocString(m_bstrName);
}   

STDMETHODIMP_(BSTR)
CConstant::get_Documentation()     
{
    return SysAllocString(m_bstrDocumentation);
}  

STDMETHODIMP_(long)
CConstant::get_HelpContext()     
{
    return (long)m_ulHelpContext;
}

STDMETHODIMP_(BSTR)
CConstant::get_HelpFile()     
{
    return SysAllocString(m_bstrHelpFile);
}   

STDMETHODIMP_(ITypeDesc FAR*)
CConstant::get_Type()
{
    m_pdispTypeDesc->AddRef();
    return (ITypeDesc FAR*)m_pdispTypeDesc;
} 

STDMETHODIMP_(VARIANT)
CConstant::get_Value()
{
    return m_vValue;
}    

STDMETHODIMP_(MEMBERID)
CConstant::get_Memberid()
{
    return m_memid;
}

STDMETHODIMP_(OBJTYPE)
CConstant::get_Kind()
{   
    return TYPE_CONSTANT;
}
