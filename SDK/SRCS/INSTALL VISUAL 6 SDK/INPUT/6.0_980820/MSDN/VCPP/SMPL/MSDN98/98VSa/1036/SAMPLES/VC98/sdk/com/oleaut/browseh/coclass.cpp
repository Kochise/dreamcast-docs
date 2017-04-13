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
**  coclass.cpp
**
**  CCoClass implementation
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
 * CCoClass::Create
 *
 * Purpose:
 *  Creates an instance of the CoClass automation object and initializes it.
 *
 * Parameters:       
 *  ptinfo       TypeInfo of coclass.
 *  ppCoClass    Returns CoClass automation object.
 *
 * Return Value:
 *  HRESULT
 *
 */
HRESULT 
CCoClass::Create(LPTYPEINFO ptinfo, CCoClass FAR* FAR* ppCoClass) 
{   
    HRESULT hr;
    CCoClass FAR* pCoClass = NULL;
     
    *ppCoClass = NULL;
    
    // Create object.
    pCoClass = new CCoClass();
    if (pCoClass == NULL)
    {
        hr = E_OUTOFMEMORY; 
        goto error;
    }   
    // Load type information for the object from type library.
    hr = pCoClass->LoadTypeInfo(IID_ICoClass);
    if (FAILED(hr))
        goto error;
    
    // Ask base class (CTypeInfo) to initialize.
    hr = pCoClass->_InitTypeInfo(ptinfo);
    if (FAILED(hr))
        goto error;
    
    ptinfo->AddRef();
    pCoClass->m_ptinfo = ptinfo; 

#ifdef _DEBUG  
    lstrcpyn(pCoClass->m_szClassName, TEXT("CoClass"), 100);
#endif 
        
    *ppCoClass = pCoClass;
    return NOERROR;
    
error:                        
    if (pCoClass == NULL) return E_OUTOFMEMORY;
    if (pCoClass->m_ptinfo) pCoClass->m_ptinfo->Release();
         
    // Set to NULL to prevent destructor from attempting to free again  
    pCoClass->m_ptinfo = NULL;
    
    delete pCoClass;
    return hr;
}

/*
 * CCoClass::CCoClass
 *
 * Purpose:
 *  Constructor for CCoClass object. Initializes members to NULL.
 *
 */
CCoClass::CCoClass()
{
    m_pdispInterfaces = NULL;  
    m_ptinfo = NULL;
}

/*
 * CCoClass::~CCoClass
 *
 * Purpose:
 *  Destructor for CCoClass object. 
 *
 */
CCoClass::~CCoClass()
{
    if (m_pdispInterfaces) m_pdispInterfaces->Release(); 
    if (m_ptinfo) m_ptinfo->Release();
}

STDMETHODIMP_(REFCLSID)
CCoClass::GetInterfaceID()
{
    return IID_ICoClass;
}

STDMETHODIMP_(ICollection FAR*)
CCoClass::get_Interfaces()     
{   
    HRESULT hr;
    CCollection FAR* pCollection = NULL;     
    CInterface FAR* pInterface;
    CCoClass FAR* pCoClass;
    LPDISPATCH pdisp;    
    HREFTYPE hreftype;  
    LPTYPEATTR ptypeattr = NULL;
    LPTYPEINFO ptinfoInterface = NULL;  
    LPTYPELIB ptlib = NULL;
    unsigned int nIndex;    
    unsigned short n;   
    TYPEKIND typekind;    
    
    if (m_pdispInterfaces == NULL)
    {
        hr = m_ptinfo->GetTypeAttr(&ptypeattr);  
        if (FAILED(hr))
            {RaiseException(IDS_Unexpected); return NULL;}   
        hr = CCollection::Create(ptypeattr->cImplTypes, 0, &pCollection); 
        if (FAILED(hr))
            {RaiseException(IDS_Unexpected); goto error;} 
        
        // Enumerate interfaces/dispinterfaces in coclass and return a collection of these.
        for (n=0; n<ptypeattr->cImplTypes; n++)
        {       
            hr = m_ptinfo->GetRefTypeOfImplType(n, &hreftype);  
            if (FAILED(hr))
                {RaiseException(IDS_Unexpected); goto error;}   
            hr = m_ptinfo->GetRefTypeInfo(hreftype, &ptinfoInterface);   
            if (FAILED(hr))
                {RaiseException(IDS_Unexpected); goto error;} 
            hr = ptinfoInterface->GetContainingTypeLib(&ptlib, &nIndex); 
            if (FAILED(hr))
                {RaiseException(IDS_Unexpected); goto error;}        
            hr = ptlib->GetTypeInfoType(nIndex, &typekind);    
            if (FAILED(hr))
                {RaiseException(IDS_Unexpected); goto error;} 
            ptlib->Release(); 
            ptlib = NULL;
        
            switch (typekind)
            {
                case TKIND_INTERFACE:
                    hr = CInterface::Create(ptinfoInterface, &pInterface);     
                    if (FAILED(hr))
                        {RaiseException(IDS_Unexpected); goto error;}     
                    pInterface->QueryInterface(IID_IDispatch, (void FAR* FAR*)&pdisp);
                    break;
             
                case TKIND_DISPATCH:
                    hr = CCoClass::Create(ptinfoInterface, &pCoClass);
                    if (FAILED(hr))
                        {RaiseException(IDS_Unexpected); goto error;}        
                    pCoClass->QueryInterface(IID_IDispatch, (void FAR* FAR*)&pdisp);
                    break;
            }
        
            ptinfoInterface->Release();   
            ptinfoInterface = NULL;
            pCollection->Add(pdisp); 
            pdisp->Release(); 
        }
        pCollection->QueryInterface(IID_IDispatch, (void FAR* FAR*)&pdisp);
        m_pdispInterfaces = pdisp; 
        m_ptinfo->ReleaseTypeAttr(ptypeattr);   
    }
    m_pdispInterfaces->AddRef();
    return (ICollection FAR*)m_pdispInterfaces; 

error:    
    if (ptypeattr) m_ptinfo->ReleaseTypeAttr(ptypeattr);   
    if (pCollection) delete pCollection;
    if (ptlib) ptlib->Release();   
    if (ptinfoInterface) ptinfoInterface->Release(); 
    return NULL;
}
