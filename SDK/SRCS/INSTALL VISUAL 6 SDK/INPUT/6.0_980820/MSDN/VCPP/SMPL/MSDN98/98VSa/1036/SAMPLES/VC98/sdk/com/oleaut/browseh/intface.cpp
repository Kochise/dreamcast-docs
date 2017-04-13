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
**  intface.cpp
**
**  CInterface implementation
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
 * CInterface::Create
 *
 * Purpose:
 *  Creates an instance of the Interface automation object and initializes it.
 *
 * Parameters:       
 *  ptinfo         TypeInfo of interface.
 *  ppInterface    Returns Interface automation object.
 *
 * Return Value:
 *  HRESULT
 *
 */
HRESULT 
CInterface::Create(LPTYPEINFO ptinfo, CInterface FAR* FAR* ppInterface) 
{   
    HRESULT hr;
    CInterface FAR* pInterface = NULL;
     
    *ppInterface = NULL;
    
    // Create object.
    pInterface = new CInterface();
    if (pInterface == NULL)
    {
        hr = E_OUTOFMEMORY; 
        goto error;
    }    
    // Load type information for the object from type library. 
    hr = pInterface->LoadTypeInfo(IID_IInterface);
    if (FAILED(hr))
        goto error;
    // Intialize base class, CTypeInfo
    hr = pInterface->_InitTypeInfo(ptinfo);
    if (FAILED(hr))
        goto error;
    
    ptinfo->AddRef();
    pInterface->m_ptinfo = ptinfo;

#ifdef _DEBUG  
    lstrcpyn(pInterface->m_szClassName, TEXT("Interface"), 100);
#endif 
        
    *ppInterface = pInterface;
    return NOERROR;
    
error:
    if (pInterface == NULL) return E_OUTOFMEMORY;
    if (pInterface->m_ptinfo) pInterface->m_ptinfo->Release();
         
    // Set to NULL to prevent destructor from attempting to free again  
    pInterface->m_ptinfo = NULL;
    
    delete pInterface;
    return hr;
}

/*
 * CInterface::CInterface
 *
 * Purpose:
 *  Constructor for CInterface object. Initializes members to NULL.
 *
 */
CInterface::CInterface()
{ 
    m_pdispFunctions = NULL;
	m_pdispBaseInterface = NULL;
    m_ptinfo = NULL;
}

/*
 * CInterface::~CInterface
 *
 * Purpose:
 *  Destructor for CInterface object. 
 *
 */
CInterface::~CInterface()
{
    if (m_pdispFunctions) m_pdispFunctions->Release();
	if (m_pdispBaseInterface) m_pdispBaseInterface->Release();
    if (m_ptinfo) m_ptinfo->Release();
} 

STDMETHODIMP_(REFCLSID)
CInterface::GetInterfaceID()
{
    return IID_IInterface;
}

STDMETHODIMP_(ICollection FAR*)
CInterface::get_Functions()     
{  
    HRESULT hr;
    CFunction FAR* pFunction;
    CCollection FAR* pCollection = NULL;
    LPDISPATCH pdisp;
    LPTYPEATTR ptypeattr = NULL;
    unsigned short n;
    
    if (m_pdispFunctions == NULL)
    {   
        // Create collection of functions in interface.
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

STDMETHODIMP_(IInterface FAR*)
CInterface::get_BaseInterface()
{
	HRESULT hr;
	CInterface FAR* pInterface = NULL;
	LPTYPEINFO ptinfoInterface = NULL;
	HREFTYPE hreftype;

    if(m_pdispBaseInterface == NULL)
    {
	    hr = m_ptinfo->GetRefTypeOfImplType(0, &hreftype);
		if (FAILED(hr))
            {RaiseException(IDS_Unexpected); return NULL;}
		hr = m_ptinfo->GetRefTypeInfo(hreftype, &ptinfoInterface);
		if (FAILED(hr))
            {RaiseException(IDS_Unexpected); return NULL;}
		hr = CInterface::Create(ptinfoInterface, &pInterface); 
        if (FAILED(hr))
            {RaiseException(IDS_Unexpected); goto error;}
		pInterface->QueryInterface(IID_IDispatch, (void FAR* FAR*)&m_pdispBaseInterface);
        ptinfoInterface->Release();
	}
	m_pdispBaseInterface->AddRef();
	return (IInterface FAR*)m_pdispBaseInterface;

error:
	if (ptinfoInterface) ptinfoInterface->Release();
	if (pInterface) delete pInterface;
    return NULL;
    
}
