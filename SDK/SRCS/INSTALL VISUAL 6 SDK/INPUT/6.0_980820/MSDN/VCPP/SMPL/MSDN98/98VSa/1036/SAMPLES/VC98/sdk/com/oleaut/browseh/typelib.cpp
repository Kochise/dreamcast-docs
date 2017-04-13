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
**  typelib.cpp
**
**  CTypeLibrary implementation
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
 * CTypeLibrary::Create
 *
 * Purpose:
 *  Creates an instance of the TypeLibrary automation object and initializes it.
 *
 * Parameters:       
 *  ptlib            ITypeLib interface that corresponds to this CTypeLibrary object.
 *  ppTypeLibrary    Returns TypeLibrary automation object.
 *
 * Return Value:
 *  HRESULT
 *
 */
HRESULT 
CTypeLibrary::Create(LPTYPELIB ptlib, CTypeLibrary FAR* FAR* ppTypeLibrary ) 
{   
    HRESULT hr;
    CTypeLibrary FAR* pTypeLibrary = NULL;    
    LPTLIBATTR ptlibattr;
     
    *ppTypeLibrary = NULL;
    
    // Create typelibrary object.
    pTypeLibrary = new CTypeLibrary();
    if (pTypeLibrary == NULL)
    {
        hr = E_OUTOFMEMORY; 
        goto error;
    }
    
    // Load type information for the typelibrary object from type library. 
    hr = pTypeLibrary->LoadTypeInfo(IID_ITypeLibrary);
    if (FAILED(hr))
        goto error;
    
    hr = ptlib->GetDocumentation(-1, &pTypeLibrary->m_bstrName, &pTypeLibrary->m_bstrDocumentation,
             &pTypeLibrary->m_ulHelpContext, &pTypeLibrary->m_bstrHelpFile);  
    if (FAILED(hr))
        goto error;    
        
    hr = ptlib->GetLibAttr(&ptlibattr);
    if (FAILED(hr))
        goto error;
    pTypeLibrary->m_guid = ptlibattr->guid;
    pTypeLibrary->m_lcid = ptlibattr->lcid;
    pTypeLibrary->m_wMajorVer = ptlibattr->wMajorVerNum;  
    pTypeLibrary->m_wMinorVer = ptlibattr->wMinorVerNum;
    ptlib->ReleaseTLibAttr(ptlibattr);
        
    ptlib->AddRef();
    pTypeLibrary->m_ptlib = ptlib;  
    
#ifdef _DEBUG  
    lstrcpyn(pTypeLibrary->m_szClassName, TEXT("TypeLibrary"), 100);
#endif
        
    *ppTypeLibrary = pTypeLibrary;
    return NOERROR;
    
error:                        
    if (pTypeLibrary == NULL) return E_OUTOFMEMORY;
    if (pTypeLibrary->m_ptlib) pTypeLibrary->m_ptlib->Release();
    if (pTypeLibrary->m_bstrName) SysFreeString(pTypeLibrary->m_bstrName);
    if (pTypeLibrary->m_bstrDocumentation) SysFreeString(pTypeLibrary->m_bstrDocumentation);
    if (pTypeLibrary->m_bstrHelpFile) SysFreeString(pTypeLibrary->m_bstrHelpFile);
         
    // Set to NULL to prevent destructor from attempting to free again  
    pTypeLibrary->m_ptlib = NULL;
    pTypeLibrary->m_bstrName = NULL;
    pTypeLibrary->m_bstrDocumentation = NULL;
    pTypeLibrary->m_bstrHelpFile = NULL;
    
    delete pTypeLibrary;
    return hr;
}

/*
 * CTypeLibrary::CTypeLibrary
 *
 * Purpose:
 *  Constructor for CTypeLibrary object. Initializes members to NULL.
 *
 */
CTypeLibrary::CTypeLibrary()
{  
    m_ptlib = NULL; 
    m_bstrName = NULL;
    m_bstrDocumentation = NULL;
    m_bstrHelpFile = NULL;   
    m_pdispTypeInfos = NULL;
        m_pszGUID = NULL;
}

/*
 * CTypeLibrary::~CTypeLibrary
 *
 * Purpose:
 *  Destructor for CTypeLibrary object. Frees TypeLibrary message BSTR and default
 *  IDispatch implementation. Closes the aplication.
 *
 */
CTypeLibrary::~CTypeLibrary()
{    
    if (m_ptlib) m_ptlib->Release();    
    if (m_bstrName) SysFreeString(m_bstrName);
    if (m_bstrDocumentation) SysFreeString(m_bstrDocumentation);
    if (m_bstrHelpFile) SysFreeString(m_bstrHelpFile);  
    if (m_pdispTypeInfos) m_pdispTypeInfos->Release();
#ifdef WIN32
    if (m_pszGUID) CoTaskMemFree(m_pszGUID);
#else
    HRESULT hr;
    LPMALLOC pmalloc;
    if (m_pszGUID)
    {
       hr = CoGetMalloc(MEMCTX_TASK, &pmalloc);
       if (SUCCEEDED(hr))
       {
           pmalloc->Free(m_pszGUID);
           pmalloc->Release();
       }
    }
#endif 
    
} 

STDMETHODIMP_(REFCLSID)
CTypeLibrary::GetInterfaceID()
{
    return IID_ITypeLibrary;
}
 
STDMETHODIMP_(BSTR)
CTypeLibrary::get_Name()     
{
    return SysAllocString(m_bstrName);
}  

STDMETHODIMP_(BSTR)
CTypeLibrary::get_Documentation()    
{
    return SysAllocString(m_bstrDocumentation);
}  

STDMETHODIMP_(long)
CTypeLibrary::get_HelpContext()     
{
    return (long)m_ulHelpContext;
}

STDMETHODIMP_(BSTR)
CTypeLibrary::get_HelpFile()     
{
    return SysAllocString(m_bstrHelpFile);
}  

STDMETHODIMP_(int)
CTypeLibrary::get_MajorVersion()     
{
    return (int)m_wMajorVer;
} 

STDMETHODIMP_(int)
CTypeLibrary::get_MinorVersion()     
{
    return (int)m_wMinorVer;
}

STDMETHODIMP_(long)
CTypeLibrary::get_LocaleID()     
{
    return (long)m_lcid;
} 

STDMETHODIMP_(ICollection FAR*)
CTypeLibrary::get_TypeInfos()     
{   
    HRESULT hr;
    CTypeInfo FAR* pTypeInfo;
    CInterface FAR* pInterface;
    CDispinterface FAR* pDispinterface;
    CModule FAR* pModule;
    CCoClass FAR* pCoClass;    
    CEnum FAR* pEnum;   
    CAlias FAR* pAlias;
    CStruct FAR* pStruct;
    CUnion FAR* pUnion;
    CCollection FAR* pCollection = NULL;
    LPDISPATCH pdisp; 
    LPTYPEINFO ptinfo = NULL;
    unsigned int cTypeInfo;    
    unsigned int n;      
    TYPEKIND typekind;
    
    if (m_pdispTypeInfos == NULL)
    {
        cTypeInfo = m_ptlib->GetTypeInfoCount();     
        hr = CCollection::Create(cTypeInfo, 0, &pCollection);
        if (FAILED(hr))
            {RaiseException(IDS_Unexpected); goto error;}  
        
        // Enumerate the typeinfos in this type library
        for (n=0; n<cTypeInfo; n++)
        {
            hr = m_ptlib->GetTypeInfo(n, &ptinfo);  
            if (FAILED(hr))
                {RaiseException(IDS_Unexpected); goto error;}    
            hr = m_ptlib->GetTypeInfoType(n, &typekind);
            if (FAILED(hr))
                {RaiseException(IDS_Unexpected); goto error;}      
            switch (typekind)
            {
                case TKIND_INTERFACE:
                    hr = CInterface::Create(ptinfo, &pInterface); 
                    if (FAILED(hr))
                        {RaiseException(IDS_Unexpected); goto error;}  
                    pInterface->QueryInterface(IID_IDispatch, (void FAR* FAR*)&pdisp);
                    break;
             
                case TKIND_DISPATCH:
                    hr = CDispinterface::Create(ptinfo, &pDispinterface);  
                    if (FAILED(hr))
                        {RaiseException(IDS_Unexpected); goto error;}   
                    pDispinterface->QueryInterface(IID_IDispatch, (void FAR* FAR*)&pdisp);
                    break;  
                    
                case TKIND_MODULE:
                    hr = CModule::Create(ptinfo, &pModule);  
                    if (FAILED(hr))
                        {RaiseException(IDS_Unexpected); goto error;}   
                    pModule->QueryInterface(IID_IDispatch, (void FAR* FAR*)&pdisp);
                    break;
                
                case TKIND_COCLASS:
                    hr = CCoClass::Create(ptinfo, &pCoClass);  
                    if (FAILED(hr))
                        {RaiseException(IDS_Unexpected); goto error;}    
                    pCoClass->QueryInterface(IID_IDispatch, (void FAR* FAR*)&pdisp);
                    break; 
                    
                case TKIND_ENUM:
                    hr = CEnum::Create(ptinfo, &pEnum);  
                    if (FAILED(hr))
                        {RaiseException(IDS_Unexpected); goto error;}    
                    pEnum->QueryInterface(IID_IDispatch, (void FAR* FAR*)&pdisp);
                    break;  
                    
                case TKIND_ALIAS:
                    hr = CAlias::Create(ptinfo, &pAlias);  
                    if (FAILED(hr))
                        {RaiseException(IDS_Unexpected); goto error;}    
                    pAlias->QueryInterface(IID_IDispatch, (void FAR* FAR*)&pdisp);
                    break; 
                    
                 case TKIND_RECORD:
                    hr = CStruct::Create(ptinfo, &pStruct);  
                    if (FAILED(hr))
                        {RaiseException(IDS_Unexpected); goto error;}    
                    pStruct->QueryInterface(IID_IDispatch, (void FAR* FAR*)&pdisp);
                    break; 
                    
                 case TKIND_UNION:
                    hr = CUnion::Create(ptinfo, &pUnion);  
                    if (FAILED(hr))
                        {RaiseException(IDS_Unexpected); goto error;}    
                    pUnion->QueryInterface(IID_IDispatch, (void FAR* FAR*)&pdisp);
                    break; 
                    
                default:       
                    // Currently unsupported TKINDs
                    hr = CTypeInfo::Create(ptinfo, &pTypeInfo); 
                    if (FAILED(hr))
                        {RaiseException(IDS_Unexpected); goto error;}  
                    pTypeInfo->QueryInterface(IID_IDispatch, (void FAR* FAR*)&pdisp);
                    break;
            } 
            // Add typeinfo to collection of typeinfos.
            pCollection->Add(pdisp);  
            pdisp->Release();
            ptinfo->Release();   
            ptinfo = NULL;
        } 
    
        pCollection->QueryInterface(IID_IDispatch, (void FAR* FAR*)&pdisp);
        m_pdispTypeInfos = pdisp;
    }
    m_pdispTypeInfos->AddRef();
    return (ICollection FAR*)m_pdispTypeInfos;

error:   
    if (ptinfo) ptinfo->Release();     
    if (pCollection) delete pCollection;    
    return NULL;
}

STDMETHODIMP_(BSTR)
CTypeLibrary::get_GUIDAsString()     
{
        if (m_pszGUID == NULL)
            StringFromCLSID(m_guid, &m_pszGUID);
    return SysAllocString(m_pszGUID);
} 
