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
**  enum.cpp
**
**  CEnum implementation
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
 * CEnum::Create
 *
 * Purpose:
 *  Creates an instance of the Enum automation object and initializes it.
 *
 * Parameters:       
 *  ptinfo    TypeInfo of Enum.
 *  ppEnum    Returns Enum automation object.
 *
 * Return Value:
 *  HRESULT
 *
 */
HRESULT 
CEnum::Create(LPTYPEINFO ptinfo, CEnum FAR* FAR* ppEnum) 
{   
    HRESULT hr;
    CEnum FAR* pEnum = NULL;
     
    *ppEnum = NULL;
    
    // Create object.
    pEnum = new CEnum();
    if (pEnum == NULL)
    {
        hr = E_OUTOFMEMORY; 
        goto error;
    }   
    // Load type information for the object from type library. 
    hr = pEnum->LoadTypeInfo(IID_IEnum);
    if (FAILED(hr))
        goto error;  
    // Ask base class (CTypeInfo) to initialize.        
    hr = pEnum->_InitTypeInfo(ptinfo);
    if (FAILED(hr))
        goto error;
    
    ptinfo->AddRef();
    pEnum->m_ptinfo = ptinfo;

#ifdef _DEBUG  
    lstrcpyn(pEnum->m_szClassName, TEXT("Enum"), 100);
#endif
        
    *ppEnum = pEnum;
    return NOERROR;
    
error:
    if (pEnum == NULL) return E_OUTOFMEMORY;
    if (pEnum->m_ptinfo) pEnum->m_ptinfo->Release();
         
    // Set to NULL to prevent destructor from attempting to free again  
    pEnum->m_ptinfo = NULL;
    
    delete pEnum;
    return hr;
}

/*
 * CEnum::CEnum
 *
 * Purpose:
 *  Constructor for CEnum object. Initializes members to NULL.
 *
 */
CEnum::CEnum()
{
    m_pdispElements = NULL;      
    m_ptinfo = NULL;
}

/*
 * CEnum::~CEnum
 *
 * Purpose:
 *  Destructor for CEnum object. 
 *
 */
CEnum::~CEnum()
{
    if (m_pdispElements) m_pdispElements->Release();
    if (m_ptinfo) m_ptinfo->Release();
}  

STDMETHODIMP_(REFCLSID)
CEnum::GetInterfaceID()
{
    return IID_IEnum;
}

STDMETHODIMP_(ICollection FAR*)
CEnum::get_Elements()     
{    
    HRESULT hr;
    CConstant FAR* pConstant;
    CCollection FAR* pCollection = NULL;
    LPDISPATCH pdisp;
    LPVARDESC pvardesc = NULL;   
    LPTYPEATTR ptypeattr = NULL;
    unsigned short n;
    
    if (m_pdispElements == NULL)
    {    
        hr = m_ptinfo->GetTypeAttr(&ptypeattr);
        if (FAILED(hr))
            {RaiseException(IDS_Unexpected); return NULL;}       
        hr = CCollection::Create(ptypeattr->cVars, 0, &pCollection);  
        if (FAILED(hr))
            {RaiseException(IDS_Unexpected); goto error;}     
        // Enumerate enum constants and return a collection of these.
        for (n=0; n<ptypeattr->cVars; n++)
        {       
            hr = m_ptinfo->GetVarDesc(n, &pvardesc);   
            if (FAILED(hr))
                {RaiseException(IDS_Unexpected); goto error;}   
            hr = CConstant::Create(m_ptinfo, pvardesc, &pConstant);
            if (FAILED(hr))
                {RaiseException(IDS_Unexpected); goto error;}    
            m_ptinfo->ReleaseVarDesc(pvardesc); 
            pvardesc = NULL;
            pConstant->QueryInterface(IID_IDispatch, (void FAR* FAR*)&pdisp);
            pCollection->Add(pdisp);   
            pdisp->Release();
        }
        pCollection->QueryInterface(IID_IDispatch, (void FAR* FAR*)&pdisp);
        m_pdispElements = pdisp;    
        m_ptinfo->ReleaseTypeAttr(ptypeattr); 
    }
    m_pdispElements->AddRef();
    return (ICollection FAR*)m_pdispElements;

error:  
    if (ptypeattr) m_ptinfo->ReleaseTypeAttr(ptypeattr);   
    if (pCollection) delete pCollection;   
    if (pvardesc) m_ptinfo->ReleaseVarDesc(pvardesc);   
    return NULL;
}    
