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
**  type.cpp
**
**  CTypeDesc implementation
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
 * CTypeDesc::Create
 *
 * Purpose:
 *  Creates an instance of the TypeDesc automation object and initializes it.
 *
 * ArrayBounds:       
 *  ptinfo        TypeInfo in which the element which this type describes is contained.    
 *  ptypedesc     TYPDESC that describes this type.
 *  ppTypeDesc    Returns TypeDesc automation object.
 *
 * Return Value:
 *  HRESULT
 *
 */
HRESULT 
CTypeDesc::Create(LPTYPEINFO ptinfo, TYPEDESC FAR* ptypedesc, CTypeDesc FAR* FAR* ppTypeDesc) 
{   
    HRESULT hr;
    CTypeDesc FAR* pTypeDesc = NULL; 
    CTypeDesc FAR* pTypeDescPointedAt = NULL;
    CArrayDesc FAR* pArrayDesc = NULL;    
    CTypeInfo FAR* pTypeInfo = NULL;
    LPTYPEINFO ptinfoUserDefined;  
     
    *ppTypeDesc = NULL;

    pTypeDesc = new CTypeDesc();
    if (pTypeDesc == NULL)
    {
        hr = E_OUTOFMEMORY; 
        goto error;
    }   
    // Load type information for the object from type library. 
    hr = pTypeDesc->LoadTypeInfo(IID_ITypeDesc);
    if (FAILED(hr))
        goto error;  
        
    pTypeDesc->m_vartype = ptypedesc->vt;
    if (ptypedesc->vt == VT_USERDEFINED)
    {
        hr = ptinfo->GetRefTypeInfo(ptypedesc->hreftype, &ptinfoUserDefined); 
        if (FAILED(hr))
            goto error;
        hr = CTypeInfo::Create(ptinfoUserDefined, &pTypeInfo);    
        if (FAILED(hr))
            goto error; 
        pTypeInfo->QueryInterface(IID_IDispatch, (void FAR* FAR*)&pTypeDesc->m_pdispUserDefinedDesc);
    }
    else if (ptypedesc->vt == VT_CARRAY)
    { 
        hr = CArrayDesc::Create(ptinfo, ptypedesc->lpadesc, &pArrayDesc);    
        if (FAILED(hr))
            goto error;  
        pArrayDesc->QueryInterface(IID_IDispatch, (void FAR* FAR*)&pTypeDesc->m_pdispArrayDesc);
    }
    else if (ptypedesc->vt == VT_PTR)
    {
        hr = CTypeDesc::Create(ptinfo, ptypedesc->lptdesc, &pTypeDescPointedAt);    
        if (FAILED(hr))
            goto error;  
        pTypeDescPointedAt->QueryInterface(IID_IDispatch, (void FAR* FAR*)&pTypeDesc->m_pdispPointerDesc);                                                                                      
    }

#ifdef _DEBUG  
    lstrcpyn(pTypeDesc->m_szClassName, TEXT("TypeDesc"), 100);
#endif
        
    *ppTypeDesc = pTypeDesc;
    return NOERROR;
    
error:
    if (pTypeDesc == NULL) return E_OUTOFMEMORY;
         
    // Set to NULL to prevent destructor from attempting to free again
    
    delete pTypeDesc;
    return hr;
}

/*
 * CTypeDesc::CTypeDesc
 *
 * Purpose:
 *  Constructor for CTypeDesc object. Initializes members to NULL.
 *
 */
CTypeDesc::CTypeDesc()
{
    m_pdispUserDefinedDesc = NULL;
    m_pdispArrayDesc = NULL;
    m_pdispPointerDesc = NULL;
}

/*
 * CTypeDesc::~CTypeDesc
 *
 * Purpose:
 *  Destructor for CTypeDesc object. 
 *
 */
CTypeDesc::~CTypeDesc()
{
    if (m_pdispUserDefinedDesc) m_pdispUserDefinedDesc->Release();
    if (m_pdispArrayDesc) m_pdispArrayDesc->Release(); 
    if (m_pdispPointerDesc) m_pdispPointerDesc->Release();
}  

STDMETHODIMP_(REFCLSID)
CTypeDesc::GetInterfaceID()
{
    return IID_ITypeDesc;
}

STDMETHODIMP_(short)
CTypeDesc::get_Type()
{ 
    return (short)m_vartype;
}

STDMETHODIMP_(ITypeInformation FAR*)
CTypeDesc::get_UserDefinedDesc()
{
    if (NULL == m_pdispUserDefinedDesc)
    {
        RaiseException(IDS_WrongType);    
        return NULL;
    }
    m_pdispUserDefinedDesc->AddRef();
    return (ITypeInformation FAR*)m_pdispUserDefinedDesc;
}

STDMETHODIMP_(IArrayDesc FAR*)
CTypeDesc::get_ArrayDesc()
{
    if (NULL == m_pdispArrayDesc)
    {
        RaiseException(IDS_WrongType);    
        return NULL;
    }
    m_pdispArrayDesc->AddRef();
    return (IArrayDesc FAR*)m_pdispArrayDesc;
}

STDMETHODIMP_(ITypeDesc FAR*)
CTypeDesc::get_PointerDesc()
{  
    if (NULL == m_pdispPointerDesc)
    {
        RaiseException(IDS_WrongType);    
        return NULL;
    }
    m_pdispPointerDesc->AddRef();
    return (ITypeDesc FAR*)m_pdispPointerDesc;
}   

/*
 * CArrayDesc::Create
 *
 * Purpose:
 *  Creates an instance of the ArrayDesc automation object and initializes it. 
 *  An ArrayDesc describes a C-style array.
 *
 * ArrayBounds:       
 *  ptinfo        TypeInfo in which the element which this type describes is contained.    
 *  parraydesc    ARRAYDESC that describes this ArrayDesc object.
 *  ppArrayDesc   Returns ArrayDesc automation object.
 *
 * Return Value:
 *  HRESULT
 *
 */
HRESULT 
CArrayDesc::Create(LPTYPEINFO ptinfo, ARRAYDESC FAR* parraydesc, CArrayDesc FAR* FAR* ppArrayDesc) 
{   
    HRESULT hr;
    CArrayDesc FAR* pArrayDesc = NULL;      
    CTypeDesc FAR* pTypeDesc = NULL;  
    CCollection FAR* pCollection = NULL;  
    CArrayBound FAR* pArrayBound;
    USHORT n;
    LPDISPATCH pdisp;
     
    *ppArrayDesc = NULL;
    
    // Create object.
    pArrayDesc = new CArrayDesc();
    if (pArrayDesc == NULL)
    {
        hr = E_OUTOFMEMORY; 
        goto error;
    }    
    
    // Load type information for the object from type library. 
    hr = pArrayDesc->LoadTypeInfo(IID_IArrayDesc);
    if (FAILED(hr))
        goto error;
        
    hr = CTypeDesc::Create(ptinfo, &parraydesc->tdescElem, &pTypeDesc);
    if (FAILED(hr))
        goto error;
    pTypeDesc->QueryInterface(IID_IDispatch, (LPVOID FAR*)&pArrayDesc->m_pdispTypeDescElement);  
    
    // Create collection of array bounds. One array bound per dimension.
    hr = CCollection::Create(parraydesc->cDims, 0, &pCollection);  
    if (FAILED(hr))
        goto error;  
    for (n=0; n<parraydesc->cDims; n++)
    {
        hr = CArrayBound::Create(parraydesc->rgbounds[n].cElements, parraydesc->rgbounds[n].lLbound, &pArrayBound);
        if (FAILED(hr))
            goto error;
        pArrayBound->QueryInterface(IID_IDispatch, (void FAR* FAR*)&pdisp);
        pCollection->Add(pdisp);
        pdisp->Release();  
    }
    pCollection->QueryInterface(IID_IDispatch, (void FAR* FAR*)&pdisp);
    pArrayDesc->m_pdispArrayBounds = pdisp;

#ifdef _DEBUG  
    lstrcpyn(pArrayDesc->m_szClassName, TEXT("ArrayDesc"), 100);
#endif 
        
    *ppArrayDesc = pArrayDesc;
    return NOERROR;
    
error:                        
    if (pArrayDesc == NULL) return E_OUTOFMEMORY;

    // Set to NULL to prevent destructor from attempting to free again
    pArrayDesc->m_pdispTypeDescElement = NULL;
    pArrayDesc->m_pdispArrayBounds = NULL;
    delete pArrayDesc;
    return hr;
}

/*
 * CArrayDesc::CArrayDesc
 *
 * Purpose:
 *  Constructor for CArrayDesc object. Initializes members to NULL.
 *
 */
CArrayDesc::CArrayDesc()
{
    m_pdispTypeDescElement = NULL;
    m_pdispArrayBounds = NULL;
}

/*
 * CArrayDesc::~CArrayDesc
 *
 * Purpose:
 *  Destructor for CArrayDesc object. 
 *
 */
CArrayDesc::~CArrayDesc()
{
     if (m_pdispTypeDescElement) m_pdispTypeDescElement->Release();      
     if (m_pdispArrayBounds) m_pdispArrayBounds->Release();
}

STDMETHODIMP_(REFCLSID)
CArrayDesc::GetInterfaceID()
{
    return IID_IArrayDesc;
}

STDMETHODIMP_(ITypeDesc FAR*)
CArrayDesc::get_ElementType()
{   
    m_pdispTypeDescElement->AddRef();
    return (ITypeDesc FAR*)m_pdispTypeDescElement;
}


STDMETHODIMP_(ICollection FAR*)
CArrayDesc::get_ArrayBounds()
{   
    m_pdispArrayBounds->AddRef();
    return (ICollection FAR*)m_pdispArrayBounds;
}  


/*
 * CArrayBound::Create
 *
 * Purpose:
 *  Creates an instance of the ArrayBound automation object and initializes it.
 *
 * ArrayBounds:       
 *  cElements       Number of elements in Array.
 *  lLBound         Lower bound of array.
 *  ppArrayBound    Returns ArrayBound automation object.
 *
 * Return Value:
 *  HRESULT
 *
 */
HRESULT 
CArrayBound::Create(unsigned long cElements, long lLBound, CArrayBound FAR* FAR* ppArrayBound) 
{   
    HRESULT hr;
    CArrayBound FAR* pArrayBound = NULL;
     
    *ppArrayBound = NULL;
    
    // Create object.
    pArrayBound = new CArrayBound();
    if (pArrayBound == NULL)
    {
        hr = E_OUTOFMEMORY; 
        goto error;
    }    
   // Load type information for the application object from type library. 
    hr = pArrayBound->LoadTypeInfo(IID_IArrayBound);
    if (FAILED(hr))
        goto error; 

    pArrayBound->m_cElements = cElements;   
    pArrayBound->m_lLBound = lLBound;

#ifdef _DEBUG  
    lstrcpyn(pArrayBound->m_szClassName, TEXT("ArrayBound"), 100);
#endif
        
    *ppArrayBound = pArrayBound;
    return NOERROR;
    
error:                        
    if (pArrayBound == NULL) return E_OUTOFMEMORY;
    
    delete pArrayBound;
    return hr;
}

STDMETHODIMP_(REFCLSID)
CArrayBound::GetInterfaceID()
{
    return IID_IArrayBound;
}

STDMETHODIMP_(long)
CArrayBound::get_ElementsCount()
{
    return (long)m_cElements;
}


STDMETHODIMP_(long)
CArrayBound::get_LowerBound()
{
    return m_lLBound;
}  
