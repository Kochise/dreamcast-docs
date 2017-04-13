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
**  struct.cpp
**
**  CStruct implementation
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
 * CStruct::Create
 *
 * Purpose:
 *  Creates an instance of the Struct automation object and initializes it.
 *
 * Parameters:       
 *  ptinfo      TypeInfo of struct..
 *  ppStruct    Returns Struct automation object.
 *
 * Return Value:
 *  HRESULT
 *
 */
HRESULT 
CStruct::Create(LPTYPEINFO ptinfo, CStruct FAR* FAR* ppStruct) 
{   
    HRESULT hr;
    CStruct FAR* pStruct = NULL;
     
    *ppStruct = NULL;
    
    // Create object.
    pStruct = new CStruct();
    if (pStruct == NULL)
    {
        hr = E_OUTOFMEMORY; 
        goto error;
    }   
    // Load type information for the object from type library. 
    hr = pStruct->LoadTypeInfo(IID_IStruct);
    if (FAILED(hr))
        goto error;  
    // Initialize base class, CTypeInfo    
    hr = pStruct->_InitTypeInfo(ptinfo);
    if (FAILED(hr))
        goto error;
    
    ptinfo->AddRef();
    pStruct->m_ptinfo = ptinfo;

#ifdef _DEBUG  
    lstrcpyn(pStruct->m_szClassName, TEXT("Struct"), 100);
#endif
        
    *ppStruct = pStruct;
    return NOERROR;
    
error:
    if (pStruct == NULL) return E_OUTOFMEMORY;
    if (pStruct->m_ptinfo) pStruct->m_ptinfo->Release();
         
    // Set to NULL to prevent destructor from attempting to free again  
    pStruct->m_ptinfo = NULL;
    
    delete pStruct;
    return hr;
}

/*
 * CStruct::CStruct
 *
 * Purpose:
 *  Constructor for CStruct object. Initializes members to NULL.
 *
 */
CStruct::CStruct()
{
    m_pdispMembers = NULL;      
    m_ptinfo = NULL;
}

/*
 * CStruct::~CStruct
 *
 * Purpose:
 *  Destructor for CStruct object. 
 *
 */
CStruct::~CStruct()
{
    if (m_pdispMembers) m_pdispMembers->Release();
    if (m_ptinfo) m_ptinfo->Release();
}  

STDMETHODIMP_(REFCLSID)
CStruct::GetInterfaceID()
{
    return IID_IStruct;
}

STDMETHODIMP_(ICollection FAR*)
CStruct::get_Members()     
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
        // Create a collection of structure members 
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
