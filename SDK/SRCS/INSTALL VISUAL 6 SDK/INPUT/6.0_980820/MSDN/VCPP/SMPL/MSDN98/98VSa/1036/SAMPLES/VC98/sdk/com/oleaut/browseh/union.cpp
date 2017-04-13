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
**  union.cpp
**
**  CUnion implementation
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
 * CUnion::Create
 *
 * Purpose:
 *  Creates an instance of the Union automation object and initializes it.
 *
 * Parameters:       
 *  ptinfo     TypeInfo of Union.
 *  ppUnion    Returns Union automation object.
 *
 * Return Value:
 *  HRESULT
 *
 */
HRESULT 
CUnion::Create(LPTYPEINFO ptinfo, CUnion FAR* FAR* ppUnion) 
{   
    HRESULT hr;
    CUnion FAR* pUnion = NULL;
     
    *ppUnion = NULL;
    
    // Create application object.
    pUnion = new CUnion();
    if (pUnion == NULL)
    {
        hr = E_OUTOFMEMORY; 
        goto error;
    }   
    // Load type information for the object from type library. 
    hr = pUnion->LoadTypeInfo(IID_IUnion);
    if (FAILED(hr))
        goto error;  
    // Initialise base class, CTypeInfo.    
    hr = pUnion->_InitTypeInfo(ptinfo);
    if (FAILED(hr))
        goto error;
    
    ptinfo->AddRef();
    pUnion->m_ptinfo = ptinfo;

#ifdef _DEBUG  
    lstrcpyn(pUnion->m_szClassName, TEXT("Union"), 100);
#endif
        
    *ppUnion = pUnion;
    return NOERROR;
    
error:
    if (pUnion == NULL) return E_OUTOFMEMORY;
    if (pUnion->m_ptinfo) pUnion->m_ptinfo->Release();
         
    // Set to NULL to prevent destructor from attempting to free again  
    pUnion->m_ptinfo = NULL;
    
    delete pUnion;
    return hr;
}

/*
 * CUnion::CUnion
 *
 * Purpose:
 *  Constructor for CUnion object. Initializes members to NULL.
 *
 */
CUnion::CUnion()
{
    m_pdispMembers = NULL;      
    m_ptinfo = NULL;
}

/*
 * CUnion::~CUnion
 *
 * Purpose:
 *  Destructor for CUnion object. 
 *
 */
CUnion::~CUnion()
{
    if (m_pdispMembers) m_pdispMembers->Release();
    if (m_ptinfo) m_ptinfo->Release();
}  

STDMETHODIMP_(REFCLSID)
CUnion::GetInterfaceID()
{
    return IID_IUnion;
}

/*
 * CUnion::
 *
 * Purpose:
 *  
 *
 */

STDMETHODIMP_(ICollection FAR*)
CUnion::get_Members()     
{    
    HRESULT hr;
    CProperty FAR* pProperty;
    CCollection FAR* pCollection = NULL;
    LPDISPATCH pdisp;
    LPVARDESC pvardesc = NULL;   
    LPTYPEATTR ptypeattr = NULL;
    unsigned short n;
    
    if (m_pdispMembers == NULL)
    {   
        // Create collection of union memebers. 
        hr = m_ptinfo->GetTypeAttr(&ptypeattr);
        if (FAILED(hr))
            {RaiseException(IDS_Unexpected); return NULL;}       
        hr = CCollection::Create(ptypeattr->cVars, 0, &pCollection);  
        if (FAILED(hr))
            {RaiseException(IDS_Unexpected); goto error;}   
        for (n=0; n<ptypeattr->cVars; n++)
        {       
            hr = m_ptinfo->GetVarDesc(n, &pvardesc);   
            if (FAILED(hr))
                {RaiseException(IDS_Unexpected); goto error;}   
            hr = CProperty::Create(m_ptinfo, pvardesc, &pProperty);
            if (FAILED(hr))
                {RaiseException(IDS_Unexpected); goto error;}    
            m_ptinfo->ReleaseVarDesc(pvardesc); 
            pvardesc = NULL;
            pProperty->QueryInterface(IID_IDispatch, (void FAR* FAR*)&pdisp);
            pCollection->Add(pdisp);   
            pdisp->Release();
        }
        pCollection->QueryInterface(IID_IDispatch, (void FAR* FAR*)&pdisp);
        m_pdispMembers = pdisp;    
        m_ptinfo->ReleaseTypeAttr(ptypeattr); 
    }
    m_pdispMembers->AddRef();
    return (ICollection FAR*)m_pdispMembers;

error:  
    if (ptypeattr) m_ptinfo->ReleaseTypeAttr(ptypeattr);   
    if (pCollection) delete pCollection;   
    if (pvardesc) m_ptinfo->ReleaseVarDesc(pvardesc);   
    return NULL;
}    
