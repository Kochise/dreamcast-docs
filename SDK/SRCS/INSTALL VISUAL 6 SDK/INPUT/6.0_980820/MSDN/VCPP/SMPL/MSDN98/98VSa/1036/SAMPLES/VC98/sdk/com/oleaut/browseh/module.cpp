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
**  module.cpp
**
**  CModule implementation
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
 * CModule::Create
 *
 * Purpose:
 *  Creates an instance of the Module automation object and initializes it.
 *
 * Parameters:       
 *  ptinfo      TypeInfo of module.
 *  ppModule    Returns Module automation object.
 *
 * Return Value:
 *  HRESULT
 *
 */
HRESULT 
CModule::Create(LPTYPEINFO ptinfo, CModule FAR* FAR* ppModule) 
{   
    HRESULT hr;
    CModule FAR* pModule = NULL;
     
    *ppModule = NULL;
    
    // Create object.
    pModule = new CModule();
    if (pModule == NULL)
    {
        hr = E_OUTOFMEMORY; 
        goto error;
    }    
    // Load type information for the object from type library. 
    hr = pModule->LoadTypeInfo(IID_IModule);
    if (FAILED(hr))
        goto error;
    // Intialize base class, CTypeInfo
    hr = pModule->_InitTypeInfo(ptinfo);
    if (FAILED(hr))
        goto error;
    
    ptinfo->AddRef();
    pModule->m_ptinfo = ptinfo;

#ifdef _DEBUG  
    lstrcpyn(pModule->m_szClassName, TEXT("Module"), 100);
#endif 
        
    *ppModule = pModule;
    return NOERROR;
    
error:
    if (pModule == NULL) return E_OUTOFMEMORY;
    if (pModule->m_ptinfo) pModule->m_ptinfo->Release();
         
    // Set to NULL to prevent destructor from attempting to free again  
    pModule->m_ptinfo = NULL;
    
    delete pModule;
    return hr;
}

/*
 * CModule::CModule
 *
 * Purpose:
 *  Constructor for CModule object. Initializes members to NULL.
 *
 */
CModule::CModule()
{ 
    m_pdispFunctions = NULL;
    m_ptinfo = NULL;
}

/*
 * CModule::~CModule
 *
 * Purpose:
 *  Destructor for CModule object. 
 *
 */
CModule::~CModule()
{
    if (m_pdispFunctions) m_pdispFunctions->Release();   
    if (m_ptinfo) m_ptinfo->Release();
} 

STDMETHODIMP_(REFCLSID)
CModule::GetInterfaceID()
{
    return IID_IModule;
}

STDMETHODIMP_(ICollection FAR*)
CModule::get_Functions()     
{  
    HRESULT hr;
    CFunction FAR* pFunction;
    CCollection FAR* pCollection = NULL;
    LPDISPATCH pdisp;
    LPTYPEATTR ptypeattr = NULL;
    unsigned short n;
    
    if (m_pdispFunctions == NULL)
    {   
        // Create collection of functions of the interface.
        hr = m_ptinfo->GetTypeAttr(&ptypeattr); 
        if (FAILED(hr))
            {RaiseException(IDS_Unexpected); return NULL;}   
        hr = CCollection::Create(ptypeattr->cFuncs, 0, &pCollection);
        if (FAILED(hr))
            {RaiseException(IDS_Unexpected); goto error;}      
        for (n=0; n<ptypeattr->cFuncs; n++)
        {                
            hr = CFunction::Create(m_ptinfo, n, &pFunction); 
            if (FAILED(hr))
                {RaiseException(IDS_Unexpected); goto error;}
            pFunction->QueryInterface(IID_IDispatch, (void FAR* FAR*)&pdisp);
            pCollection->Add(pdisp);  
            pdisp->Release();
        }
        pCollection->QueryInterface(IID_IDispatch, (void FAR* FAR*)&pdisp);
        m_pdispFunctions = pdisp; 
        m_ptinfo->ReleaseTypeAttr(ptypeattr);
    }
    m_pdispFunctions->AddRef();
    return (ICollection FAR*)m_pdispFunctions;     
    
error:    
    if (ptypeattr) m_ptinfo->ReleaseTypeAttr(ptypeattr);   
    if (pCollection) delete pCollection;  
    return NULL;
}    
