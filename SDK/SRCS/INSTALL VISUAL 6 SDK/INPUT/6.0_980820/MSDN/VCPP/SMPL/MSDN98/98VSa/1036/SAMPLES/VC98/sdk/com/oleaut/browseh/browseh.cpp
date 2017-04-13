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
**  browse.cpp
**
**  CBrowseHelper implementation
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
 * CBrowseHelper::Create
 *
 * Purpose:
 *  Creates an instance of the BrowseHelper automation object and initializes it.
 *
 * Parameters:
 *  ppBrowseHelper   Returns BrowseHelper automation object.
 *
 * Return Value:
 *  HRESULT
 *
 */
HRESULT 
CBrowseHelper::Create(CBrowseHelper FAR* FAR* ppBrowseHelper ) 
{   
    HRESULT hr;
    CBrowseHelper FAR* pBrowseHelper = NULL;
     
    *ppBrowseHelper = NULL;
    
    // Create object.
    pBrowseHelper = new CBrowseHelper();
    if (pBrowseHelper == NULL)
    {
        hr = E_OUTOFMEMORY; 
        goto error;
    }

    // Load type information for the application object from type library. 
    hr = pBrowseHelper->LoadTypeInfo(IID_IBrowseHelper);
    if (FAILED(hr))
        goto error;    
        
#ifdef _DEBUG  
    lstrcpyn(pBrowseHelper->m_szClassName, TEXT("BrowseHelper"), 100);
#endif
        
    *ppBrowseHelper = pBrowseHelper;
    return NOERROR;
    
error:                        
    if (pBrowseHelper == NULL)
        return E_OUTOFMEMORY;

    delete pBrowseHelper;
    return hr;
}

/*
 * CBrowseHelper::CBrowseHelper
 *
 * Purpose:
 *  Constructor for CBrowseHelper object. Initializes members to NULL.
 *
 */
CBrowseHelper::CBrowseHelper()
{   
    extern ULONG g_cObj;
    g_cObj++;     
}

/*
 * CBrowseHelper::~CBrowseHelper
 *
 * Purpose:
 *  Destructor for CBrowseHelper object. Frees BrowseHelper message BSTR and default
 *  IDispatch implementation. Closes the aplication.
 *
 */
CBrowseHelper::~CBrowseHelper()
{ 
     extern ULONG g_cObj;

     g_cObj--;
}

STDMETHODIMP_(REFCLSID)
CBrowseHelper::GetInterfaceID()
{
    return IID_IBrowseHelper;
}

/*
 * CBrowseHelper::BrowseTypeLibrary
 *
 * Purpose:
 *  Opens and browses type library. Creates and returns a TypeLibrary object.
 *
 */
STDMETHODIMP_(ITypeLibrary FAR*)
CBrowseHelper::BrowseTypeLibrary(BSTR bstrPath)
{
    LPTYPELIB ptlib = NULL;
    LPDISPATCH pdisp;
    HRESULT hr;     
    CTypeLibrary FAR* pTypeLibrary;
    
    hr = LoadTypeLib(bstrPath, &ptlib);
    if (FAILED(hr))
        {RaiseException(IDS_CannotFindTypeLibrary); return NULL;} 
        
    hr = CTypeLibrary::Create(ptlib, &pTypeLibrary);
    if (FAILED(hr))
         {RaiseException(IDS_TypeLibraryCreationFailed); goto error;}
    hr = pTypeLibrary->QueryInterface(IID_IDispatch, (void FAR* FAR*)&pdisp); 
    if (FAILED(hr))
        {RaiseException(IDS_Unexpected); goto error;}
        
    ptlib->Release();
    return (ITypeLibrary FAR*)pdisp;
    
error:
    if (ptlib)
        ptlib->Release();
    return NULL;
}
