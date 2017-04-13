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
**  collect.cpp
**
**  CCollection implementation
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
 * CCollection::Create
 *
 * Purpose:
 *  Creates an instance of a collection object and initializes it.
 *
 * Parameters:
 *  lMaxSize   Maximum number of items that can added to collection.
 *  lLBound    Lower bound of index of collection.  
 *  ppCollection    Returns collection object.
 *
 * Return Value:
 *  HRESULT
 *
 */
HRESULT 
CCollection::Create(ULONG lMaxSize, long lLBound, CCollection FAR* FAR* ppCollection) 
{   
    HRESULT hr;
    CCollection FAR* pCollection = NULL;
    SAFEARRAYBOUND sabound[1];
     
    *ppCollection = NULL;
    
    // Create new collection
    pCollection = new CCollection();
    if (pCollection == NULL)
        goto error; 
    // Load type information for the collection from type library. 
    hr = pCollection->LoadTypeInfo(IID_ICollection);
    if (FAILED(hr))
        goto error;
    
    // If lMaxSize is 0 increment it to 1 or SafeArrayCreate will fail
    if (lMaxSize == 0)   
       lMaxSize = 1;       
    pCollection->m_cMax = lMaxSize;
    pCollection->m_cElements = 0; 
    pCollection->m_lLBound = lLBound;

    // Create a safe array which is used to implement the collection   
    sabound[0].cElements = lMaxSize;
    sabound[0].lLbound = lLBound;        
    pCollection->m_psa = SafeArrayCreate(VT_VARIANT, 1, sabound);
    if (pCollection->m_psa == NULL)
    {
        hr = E_OUTOFMEMORY;
        goto error;
    }
    
#ifdef _DEBUG  
    lstrcpyn(pCollection->m_szClassName, TEXT("Collection"), 100);
#endif          

    *ppCollection = pCollection;
    return NOERROR;
    
error: 
    if (pCollection == NULL)
        return E_OUTOFMEMORY;                       
    if (pCollection->m_psa) 
        SafeArrayDestroy(pCollection->m_psa); 
  
    pCollection->m_psa = NULL;
    
    delete pCollection;
    return hr;
}

/*
 * CCollection::CCollection
 *
 * Purpose:
 *  Constructor for CCollection object. Initializes members to NULL.
 *
 */
CCollection::CCollection()
{
    m_psa = NULL;
}

/*
 * CCollection::~CCollection
 *
 * Purpose:
 *  Destructor for CCollection object. 
 *
 */
CCollection::~CCollection()
{                  
     if (m_psa) SafeArrayDestroy(m_psa);
}

STDMETHODIMP_(REFCLSID)
CCollection::GetInterfaceID()
{
    return IID_ICollection;
}

/*
 * CCollection::get_Count
 *
 * Purpose:
 *  Returns number of items in collection.
 *
 */
STDMETHODIMP_(long)     
CCollection::get_Count(void)  
{
    return m_cElements;             
}

/*
 * CCollection::get_Item
 *
 * Purpose:
 *  Retrieves item from collection, given an index.
 *
 * Parameters:   
 *   lIndex   Index of item to be retrieved. 
 *
 * Returns
 *  IDispatch of item retrieved from collection.
 *
 */
STDMETHODIMP_(LPDISPATCH)
CCollection::get_Item(long lIndex)
{ 
    HRESULT hr;
    VARIANT v;
    LPDISPATCH pdisp = NULL;
   
    // Check if integer index is within range         
    if (lIndex < m_lLBound || lIndex >= (long)(m_lLBound+m_cElements)) 
        {RaiseException(IDS_InvalidIndex); return NULL;}
    
    // Retrieve and return item. Note that SafeArrayGetElement AddRefs so an additional AddRef
    // is not required.
    VariantInit(&v);
    hr = SafeArrayGetElement(m_psa, &lIndex, &v);
    if (FAILED(hr))
        {RaiseException(IDS_Unexpected); return NULL;}
    return V_DISPATCH(&v); 
}

/*
 * CCollection::get_NewEnum
 *
 * Purpose:
 *  Returns an enumerator (IEnumVARIANT) for the items curently in the collection. 
 *  The NewEnum property is restricted and so is invisible to users of an 
 *  automation controller's scripting language. Automation controllers that support
 *  a 'For Each' statement to iterate through the elements of a collection will use
 *  the enumerator returned by NewEnum. The enumerator creates a snapshot of the
 *  the current state of the collection.
 *
 */
STDMETHODIMP_(LPUNKNOWN)
CCollection::get__NewEnum(void)
{
    CEnumVariant FAR* penum = NULL;;
    LPUNKNOWN punkEnumVariant = NULL;
    HRESULT hr;

    // Create new enumerator for items currently in collection and QI for IUnknown
    hr = CEnumVariant::Create(m_psa, m_cElements, &penum);
    if (FAILED(hr))
        {RaiseException(IDS_OutOfMemory); goto error;}       
    hr = penum->QueryInterface(IID_IUnknown, (VOID FAR* FAR*)&punkEnumVariant);    
    if (FAILED(hr)) 
        {RaiseException(IDS_Unexpected); goto error;}         
    return punkEnumVariant; 
    
error:
    if (penum)
        delete penum;    
    return NULL;              
}

/*
 * CCollection::Add
 *
 * Purpose:
 *  Adds an item to the collection. 
 *
 * Parameters:
 *  pdispItemAdd    Item to be added to collection.
 *
 */
STDMETHODIMP_(void)   
CCollection::Add(LPDISPATCH pdispItem)
{ 
    HRESULT hr;   
    LONG l;
    VARIANT v;  
    
    // Is the collection full?
    if (m_cElements == m_cMax) 
        {RaiseException(IDS_CollectionFull); return;}             
       
    l = m_lLBound+m_cElements;              
    VariantInit(&v);
    V_VT(&v) = VT_DISPATCH;
    V_DISPATCH(&v) = pdispItem; 
       
    hr = SafeArrayPutElement(m_psa, &l, &v);
    if (FAILED(hr))
        {RaiseException(IDS_Unexpected); return;}               
          
    m_cElements++;                      
}
