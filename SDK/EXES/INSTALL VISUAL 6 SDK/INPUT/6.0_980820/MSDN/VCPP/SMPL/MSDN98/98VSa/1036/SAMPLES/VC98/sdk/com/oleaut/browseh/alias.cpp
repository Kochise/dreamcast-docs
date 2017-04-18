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
**  alias.cpp
**
**  CAlias implementation
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
 * CAlias::Create
 *
 * Purpose:
 *  Creates an instance of the Alias automation object and initializes it.
 *
 * Parameters:       
 *  ptinfo     Typeinfo of Alias.
 *  ppAlias    Returns Alias automation object.
 *
 * Return Value:
 *  HRESULT
 *
 */
HRESULT
CAlias::Create(LPTYPEINFO ptinfo, CAlias FAR* FAR* ppAlias) 
{   
    HRESULT hr;
    CAlias FAR* pAlias = NULL;       
    LPTYPEATTR ptypeattr = NULL; 
    CTypeDesc FAR* pTypeDesc;
     
    *ppAlias = NULL;
    
    // Create alias object.
    pAlias = new CAlias();
    if (pAlias == NULL)
    {
        hr = E_OUTOFMEMORY; 
        goto error;
    }   
    // Load type information for the object from type library. 
    hr = pAlias->LoadTypeInfo(IID_IAlias);
    if (FAILED(hr))
        goto error;  
    
    // Ask base class (CTypeInfo) to initialize    
    hr = pAlias->_InitTypeInfo(ptinfo);
    if (FAILED(hr))
        goto error;        
    
    // Get base type of this alias.
    hr = ptinfo->GetTypeAttr(&ptypeattr); 
    if (FAILED(hr))
        return NULL;     
    hr = CTypeDesc::Create(ptinfo, &ptypeattr->tdescAlias, &pTypeDesc);
    if (FAILED(hr))
        goto error;
    pTypeDesc->QueryInterface(IID_IDispatch, (LPVOID FAR*)&pAlias->m_pdispTypeDescBase);
    ptinfo->ReleaseTypeAttr(ptypeattr);
    
#ifdef _DEBUG  
    lstrcpyn(pAlias->m_szClassName, TEXT("Alias"), 100);
#endif
        
    *ppAlias = pAlias;
    return NOERROR;
    
error:
    if (pAlias == NULL) return E_OUTOFMEMORY;
    if (pAlias->m_pdispTypeDescBase) pAlias->m_pdispTypeDescBase->Release();    
    if (ptypeattr) ptinfo->ReleaseTypeAttr(ptypeattr); 
         
    // Set to NULL to prevent destructor from attempting to free again
    pAlias->m_pdispTypeDescBase = NULL;
    
    delete pAlias;
    return hr;
}

/*
 * CAlias::CAlias
 *
 * Purpose:
 *  Constructor for CAlias object. Initializes members to NULL.
 *
 */
CAlias::CAlias()
{
    m_pdispTypeDescBase = NULL;
}

/*
 * CAlias::~CAlias
 *
 * Purpose:
 *  Destructor for CAlias object. 
 *
 */
CAlias::~CAlias()
{
    if (m_pdispTypeDescBase) m_pdispTypeDescBase->Release();
}  

STDMETHODIMP_(REFCLSID)
CAlias::GetInterfaceID()
{
    return IID_IAlias;
}
 
STDMETHODIMP_(ITypeDesc FAR*)
CAlias::get_BaseType()
{
    m_pdispTypeDescBase->AddRef();
    return (ITypeDesc FAR*)m_pdispTypeDescBase;
}
