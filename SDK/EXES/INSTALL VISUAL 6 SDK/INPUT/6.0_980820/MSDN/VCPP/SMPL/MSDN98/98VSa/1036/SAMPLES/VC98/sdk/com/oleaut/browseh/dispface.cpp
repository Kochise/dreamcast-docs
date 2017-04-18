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
**  dispface.cpp
**
**  CDispinterface implementation
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
 * CDispinterface::Create
 *
 * Purpose:
 *  Creates an instance of the Dispinterface automation object and initializes it.
 *
 * Parameters:       
 *  ptinfo             TypeInfo of dispinterface.
 *  ppDispinterface    Returns Dispinterface automation object.
 *
 * Return Value:
 *  HRESULT
 *
 */
HRESULT 
CDispinterface::Create(LPTYPEINFO ptinfo, CDispinterface FAR* FAR* ppDispinterface) 
{   
    HRESULT hr;
    CDispinterface FAR* pDispinterface = NULL;
     
    *ppDispinterface = NULL;
    
    // Create object.
    pDispinterface = new CDispinterface();
    if (pDispinterface == NULL)
    {
        hr = E_OUTOFMEMORY; 
        goto error;
    }   
    // Load type information for the object from type library. 
    hr = pDispinterface->LoadTypeInfo(IID_IDispinterface);
    if (FAILED(hr))
        goto error;  
    
    // Ask base class (CTypeInfo) to initialize.    
    hr = pDispinterface->_InitTypeInfo(ptinfo);
    if (FAILED(hr))
        goto error;
    
    ptinfo->AddRef();
    pDispinterface->m_ptinfo = ptinfo;

#ifdef _DEBUG  
    lstrcpyn(pDispinterface->m_szClassName, TEXT("Dispinterface"), 100);
#endif
        
    *ppDispinterface = pDispinterface;
    return NOERROR;
    
error:
    if (pDispinterface == NULL) return E_OUTOFMEMORY;
    if (pDispinterface->m_ptinfo) pDispinterface->m_ptinfo->Release();
         
    // Set to NULL to prevent destructor from attempting to free again  
    pDispinterface->m_ptinfo = NULL;
    
    delete pDispinterface;
    return hr;
}

/*
 * CDispinterface::CDispinterface
 *
 * Purpose:
 *  Constructor for CDispinterface object. Initializes members to NULL.
 *
 */
CDispinterface::CDispinterface()
{
    m_pdispProperties = NULL;
    m_pdispMethods = NULL;
	m_pdispInterface = NULL;
    m_ptinfo = NULL;
}

/*
 * CDispinterface::~CDispinterface
 *
 * Purpose:
 *  Destructor for CDispinterface object. 
 *
 */
CDispinterface::~CDispinterface()
{
    if (m_pdispProperties) m_pdispProperties->Release();
    if (m_pdispMethods) m_pdispMethods->Release();
	if (m_pdispInterface) m_pdispInterface->Release();
    if (m_ptinfo) m_ptinfo->Release();
}  

STDMETHODIMP_(REFCLSID)
CDispinterface::GetInterfaceID()
{
    return IID_IDispinterface;
}

STDMETHODIMP_(ICollection FAR*)
CDispinterface::get_Methods()    
{      
    HRESULT hr;
    CFunction FAR* pFunction;
    CCollection FAR* pCollection = NULL;
    LPDISPATCH pdisp;  
    LPTYPEATTR ptypeattr = NULL;
    unsigned short n;
    
    if (m_pdispMethods == NULL)
    {
        hr = m_ptinfo->GetTypeAttr(&ptypeattr); 
        if (FAILED(hr))
            {RaiseException(IDS_Unexpected); return NULL;}   
        hr = CCollection::Create(ptypeattr->cFuncs, 0, &pCollection);
        if (FAILED(hr))
            {RaiseException(IDS_Unexpected); goto error;}  
        // Enumerate methods and return a collection of these.    
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
        m_pdispMethods = pdisp; 
        m_ptinfo->ReleaseTypeAttr(ptypeattr);
    }
    m_pdispMethods->AddRef();
    return (ICollection FAR*)m_pdispMethods;     
    
error:    
    if (ptypeattr) m_ptinfo->ReleaseTypeAttr(ptypeattr);   
    if (pCollection) delete pCollection;  
    return NULL;
}  

STDMETHODIMP_(ICollection FAR*)
CDispinterface::get_Properties()     
{    
    HRESULT hr;
    CProperty FAR* pProperty;
    CCollection FAR* pCollection = NULL;
    LPDISPATCH pdisp;
    LPVARDESC pvardesc = NULL;   
    LPTYPEATTR ptypeattr = NULL;
    unsigned short n;
    
    if (m_pdispProperties == NULL)
    {    
        hr = m_ptinfo->GetTypeAttr(&ptypeattr);
        if (FAILED(hr))
            {RaiseException(IDS_Unexpected); return NULL;}       
        hr = CCollection::Create(ptypeattr->cVars, 0, &pCollection);  
        if (FAILED(hr))
            {RaiseException(IDS_Unexpected); goto error;}  
        // Enumerate properties and return a collection of these.   
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
        m_pdispProperties = pdisp;    
        m_ptinfo->ReleaseTypeAttr(ptypeattr); 
    }
    m_pdispProperties->AddRef();
    return (ICollection FAR*)m_pdispProperties;

error:  
    if (ptypeattr) m_ptinfo->ReleaseTypeAttr(ptypeattr);   
    if (pCollection) delete pCollection;   
    if (pvardesc) m_ptinfo->ReleaseVarDesc(pvardesc);   
    return NULL;
}   

STDMETHODIMP_(IInterface FAR*)
CDispinterface::get_Interface() 
{ 
	HRESULT hr;
	CInterface FAR* pInterface = NULL;
	LPTYPEINFO ptinfoInterface = NULL;
	HREFTYPE hreftype;

	// Check if this dispinterface is part of a dual interface.
	// (A dual interface has an interface and a dispinterface.)
	if ((m_wTypeFlags & TYPEFLAG_FDUAL) == 0)
        {RaiseException(IDS_NotDualInterface); return NULL;}
    if(m_pdispInterface == NULL)
    {
		// Get interface part of dual interface
#ifdef WIN32
        hr = m_ptinfo->GetRefTypeOfImplType(0xFFFFFFFF, &hreftype);
#else
        hr = m_ptinfo->GetRefTypeOfImplType(0xFFFF, &hreftype);
#endif 
		if (FAILED(hr))
            {RaiseException(IDS_Unexpected); return NULL;}
		hr = m_ptinfo->GetRefTypeInfo(hreftype, &ptinfoInterface);
		if (FAILED(hr))
            {RaiseException(IDS_Unexpected); return NULL;}
		hr = CInterface::Create(ptinfoInterface, &pInterface); 
        if (FAILED(hr))
            {RaiseException(IDS_Unexpected); goto error;}
		pInterface->QueryInterface(IID_IDispatch, (void FAR* FAR*)&m_pdispInterface);
        ptinfoInterface->Release();
	}
	m_pdispInterface->AddRef();
	return (IInterface FAR*)m_pdispInterface;

error:
	if (ptinfoInterface) ptinfoInterface->Release();
	if (pInterface) delete pInterface;
    return NULL;
}


