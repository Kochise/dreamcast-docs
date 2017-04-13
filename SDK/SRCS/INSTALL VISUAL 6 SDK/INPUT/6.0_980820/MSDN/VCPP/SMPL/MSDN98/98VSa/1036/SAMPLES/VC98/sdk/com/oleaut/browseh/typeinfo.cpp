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
**  typeinfo.cpp
**
**  CTypeInfo implementation
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
 * CTypeInfo::Create
 *
 * Purpose:
 *  Creates an instance of the TypeInfo automation object and initializes it.
 *
 * Parameters:       
 *  ptinfo        TypeInfo in type library..
 *  ppTypeInfo    Returns TypeInfo automation object.
 *
 * Return Value:
 *  HRESULT
 *
 */
HRESULT 
CTypeInfo::Create(LPTYPEINFO ptinfo, CTypeInfo FAR* FAR* ppTypeInfo) 
{   
    HRESULT hr;
    CTypeInfo FAR* pTypeInfo = NULL;
     
    *ppTypeInfo = NULL;
    
    // Create application object.
    pTypeInfo = new CTypeInfo();
    if (pTypeInfo == NULL)
    {
        hr = E_OUTOFMEMORY; 
        goto error;
    }    
    // Load type information for the application object from type library. 
    hr = pTypeInfo->LoadTypeInfo(IID_ITypeInformation);
    if (FAILED(hr))
        goto error;    
    hr = pTypeInfo->_InitTypeInfo(ptinfo);
    if (FAILED(hr))
        goto error;

#ifdef _DEBUG  
    lstrcpyn(pTypeInfo->m_szClassName, TEXT("TypeInfo"), 100);
#endif
        
    *ppTypeInfo = pTypeInfo;
    return NOERROR;
    
error:
    if (pTypeInfo == NULL) return E_OUTOFMEMORY;
    
    delete pTypeInfo;
    return hr;
}

/*
 * CTypeInfo::CTypeInfo
 *
 * Purpose:
 *  Constructor for CTypeInfo object. Initializes members to NULL.
 *
 */
CTypeInfo::CTypeInfo()
{   
    m_bstrName = NULL;
    m_bstrDocumentation = NULL;
    m_bstrHelpFile = NULL;
        m_pszGUID = NULL;
}

/*
 * CTypeInfo::~CTypeInfo
 *
 * Purpose:
 *  Destructor for CTypeInfo object. 
 *
 */
CTypeInfo::~CTypeInfo()
{    
     if (m_bstrName) SysFreeString(m_bstrName);
     if (m_bstrDocumentation) SysFreeString(m_bstrDocumentation);
     if (m_bstrHelpFile) SysFreeString(m_bstrHelpFile);

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
CTypeInfo::GetInterfaceID()
{
    return IID_ITypeInformation;
}    

STDMETHODIMP
CTypeInfo::_InitTypeInfo(LPTYPEINFO ptinfo)
{   
    HRESULT hr;
    LPTYPELIB ptlib = NULL;
    unsigned int nIndex; 
    LPTYPEATTR ptypeattr;
    
    // Get information from TYPEATTR
    hr = ptinfo->GetTypeAttr(&ptypeattr);
    if (FAILED(hr))
        return hr;
    m_typekind = ptypeattr->typekind;
    m_guid = ptypeattr->guid; 
        m_wTypeFlags = ptypeattr->wTypeFlags;
    ptinfo->ReleaseTypeAttr(ptypeattr);
           
    hr = ptinfo->GetContainingTypeLib(&ptlib, &nIndex);  
    if (FAILED(hr))  
    {   
        if (hr == E_NOTIMPL)  //Supportes runtime typeinfo browsing. (Type info
                                        //obtained from IDispatch::GetTypeInfo does not have a containing
                                        //type library).        
           return NOERROR;
        else return hr;
    }
    hr = ptlib->GetDocumentation(nIndex, &m_bstrName, &m_bstrDocumentation,
             &m_ulHelpContext, &m_bstrHelpFile);  
    if (FAILED(hr))
        goto error;
    ptlib->Release();
    return NOERROR; 

error: 
    if (ptlib) ptlib->Release(); 
    if (m_bstrName) SysFreeString(m_bstrName);
    if (m_bstrDocumentation) SysFreeString(m_bstrDocumentation);
    if (m_bstrHelpFile) SysFreeString(m_bstrHelpFile);       
    m_bstrName = NULL;
    m_bstrDocumentation = NULL;
    m_bstrHelpFile = NULL;
    return hr; 
}
 
STDMETHODIMP_(BSTR)
CTypeInfo::get_Name()     
{
    return SysAllocString(m_bstrName);
}  

STDMETHODIMP_(BSTR)
CTypeInfo::get_Documentation()     
{
    return SysAllocString(m_bstrDocumentation);
}  

STDMETHODIMP_(long)
CTypeInfo::get_HelpContext()     
{
    return (long)m_ulHelpContext;
}

STDMETHODIMP_(BSTR)
CTypeInfo::get_HelpFile()     
{
    return SysAllocString(m_bstrHelpFile);
}   

STDMETHODIMP_(TYPEKIND)
CTypeInfo::get_TypeInfoKind()     
{
    return m_typekind;
}

STDMETHODIMP_(short)
CTypeInfo::get_TypeFlags()     
{
    return m_wTypeFlags;
}

STDMETHODIMP_(BSTR)
CTypeInfo::get_GUIDAsString()     
{
        if (m_pszGUID == NULL)
            StringFromCLSID(m_guid, &m_pszGUID);
    return SysAllocString(m_pszGUID);
} 
