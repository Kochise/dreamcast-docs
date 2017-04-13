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
**  OLE Automation Points object
**
**  points.cpp
**
**  CPoints collection implementation
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
#include "lines.h"  

/*
 * CPoints::Create
 *
 * Purpose:
 *  Creates an instance of a collection object and initializes it.
 *
 * Parameters:
 *  lMaxSize   Maximum number of items that can added to collection.
 *  lLBound    Lower bound of index of collection.  
 *  pPane      Pointer to pane that contains this collection. Required because the pane coordinates 
 *             the lines and points collection.
 *  ppPoints    Returns collection object.
 *
 * Return Value:
 *  HRESULT
 *
 */
HRESULT 
CPoints::Create(ULONG lMaxSize, long lLBound, CPane FAR* pPane, CPoints FAR* FAR* ppPoints) 
{   
    HRESULT hr;
    CPoints FAR* pPoints = NULL;
    SAFEARRAYBOUND sabound[1];
     
    *ppPoints = NULL;
    
    // Create new collection
    pPoints = new CPoints();
    if (pPoints == NULL)
        goto error;
    
    pPoints->m_cMax = lMaxSize;
    pPoints->m_cElements = 0; 
    pPoints->m_lLBound = lLBound;     
    pPoints->m_pPane = pPane;  
    
    // Load type information for the points collection from type library. 
    hr = LoadTypeInfo(&pPoints->m_ptinfo, IID_IPoints);
    if (FAILED(hr))
        goto error;
    
    // Create a safe array which is used to implement the collection.            
    sabound[0].cElements = lMaxSize;
    sabound[0].lLbound = lLBound;        
    pPoints->m_psa = SafeArrayCreate(VT_VARIANT, 1, sabound);
    if (pPoints->m_psa == NULL)
    {
        hr = E_OUTOFMEMORY;
        goto error;
    }             

    *ppPoints = pPoints;
    return NOERROR;
    
error: 
    if (pPoints == NULL)
        return E_OUTOFMEMORY;
    if (pPoints->m_ptinfo)
        pPoints->m_ptinfo->Release();                            
    if (pPoints->m_psa) 
        SafeArrayDestroy(pPoints->m_psa); 
  
    pPoints->m_psa = NULL;
    pPoints->m_ptinfo = NULL; 
    
    delete pPoints;
    return hr;
}

/*
 * CPoints::CPoints
 *
 * Purpose:
 *  Constructor for CPoints object. Initializes members to NULL.
 *
 */
#pragma warning (disable : 4355)
CPoints::CPoints() : m_SupportErrorInfo(this, IID_IPoints)
#pragma warning (default : 4355)
{    
    m_cRef = 0;
    m_psa = NULL;
    m_ptinfo = NULL; 
}

/*
 * CPoints::~CPoints
 *
 * Purpose:
 *  Destructor for CPoints object. 
 *
 */
CPoints::~CPoints()
{    
     if (m_ptinfo) m_ptinfo->Release();                   
     if (m_psa) SafeArrayDestroy(m_psa);
}

/*
 * CPoints::QueryInterface, AddRef, Release
 *
 * Purpose:
 *  Implements IUnknown::QueryInterface, AddRef, Release
 *
 */
STDMETHODIMP
CPoints::QueryInterface(REFIID iid, void FAR* FAR* ppv) 
{    
    *ppv = NULL;
        
    if (iid == IID_IUnknown || iid == IID_IPoints || iid == IID_IDispatch)
        *ppv = this;        
    else if (iid == IID_ISupportErrorInfo)
        *ppv = &m_SupportErrorInfo;
    else return E_NOINTERFACE; 

    AddRef();
    return NOERROR;    
}


STDMETHODIMP_(ULONG)
CPoints::AddRef(void)
{ 

#ifdef _DEBUG  
    TCHAR ach[50];
    wsprintf(ach, TEXT("Ref = %ld, Points\r\n"), m_cRef+1); 
    OutputDebugString(ach); 
#endif  
    
    return ++m_cRef;
}


STDMETHODIMP_(ULONG)
CPoints::Release(void)
{ 

#ifdef _DEBUG  
    TCHAR ach[50];
    wsprintf(ach, TEXT("Ref = %ld, Points\r\n"), m_cRef-1); 
    OutputDebugString(ach);   
#endif
    
    if(--m_cRef == 0)
    {
        delete this;
        return 0;
    }
    return m_cRef;
} 

/*
 * CPoints::GetTypeInfoCount
 *
 * Purpose:
 *  Implements IDispatch::GetTypeInfoCount.
 *
 */
STDMETHODIMP
CPoints::GetTypeInfoCount(UINT FAR* pctinfo)
{
    *pctinfo = 1;
    return NOERROR;
}

/*
 * CPoints::GetTypeInfo
 *
 * Purpose:
 *  Implements IDispatch::GetTypeInfo. 
 *
 */
STDMETHODIMP
CPoints::GetTypeInfo(
      UINT itinfo,
      LCID lcid,
      ITypeInfo FAR* FAR* pptinfo)
{    
    *pptinfo = NULL;
     
    if(itinfo != 0)
        return DISP_E_BADINDEX;
    
    m_ptinfo->AddRef(); 
    *pptinfo = m_ptinfo;
    
    return NOERROR;
}

/*
 * CPoints::GetIDsOfNames
 *
 * Purpose:
 *  Implements IDispatch::GetIDsOfNames.  The standard implementation, DispGetIDsOfNames,
 *  is used.
 *
 */
STDMETHODIMP 
CPoints::GetIDsOfNames(
      REFIID riid,
      OLECHAR FAR* FAR* rgszNames,
      UINT cNames,
      LCID lcid,
      DISPID FAR* rgdispid)
{
    return DispGetIDsOfNames(m_ptinfo, rgszNames, cNames, rgdispid);
}

/*
 * CPoints::Invoke
 *
 * Purpose:
 *  Implements IDispatch::Invoke.  The standard implementation, DispInvoke,
 *  is used. 
 *
 */
STDMETHODIMP
CPoints::Invoke(
      DISPID dispidMember,
      REFIID riid,
      LCID lcid,
      WORD wFlags,
      DISPPARAMS FAR* pdispparams,
      VARIANT FAR* pvarResult,
      EXCEPINFO FAR* pexcepinfo,
      UINT FAR* puArgErr)
{  
    return DispInvoke(
        this, m_ptinfo,
        dispidMember, wFlags, pdispparams,
        pvarResult, pexcepinfo, puArgErr);   
}

/*
 * CPoints::get_Count
 *
 * Purpose:
 *  Returns number of items in collection.
 *
 */
STDMETHODIMP   
CPoints::get_Count(long FAR* plCount)  
{
    *plCount = m_cElements;
    return NOERROR;             
}

/*
 * CPoints::get_Item
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
STDMETHODIMP
CPoints::get_Item(long lIndex, IPoint FAR* FAR* ppPoint)
{ 
    HRESULT hr;
    VARIANT v;
    LPDISPATCH pdisp = NULL;
   
    // Check if integer index is within range         
    if (lIndex < m_lLBound || lIndex >= (long)(m_lLBound+m_cElements)) 
        return RaiseException(IDS_InvalidIndex, IID_IPoints); 
    
    // Retrieve and return item. Note that SafeArrayGetElement AddRefs so an additional AddRef
    // is not required.
    VariantInit(&v);
    hr = SafeArrayGetElement(m_psa, &lIndex, &v);
    if (FAILED(hr))
        return RaiseException(IDS_Unexpected, IID_IPoints); 
    *ppPoint = (IPoint FAR*) V_DISPATCH(&v);    
    return NOERROR;
}

/*
 * CPoints::get_NewEnum
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
STDMETHODIMP
CPoints::get__NewEnum(IUnknown FAR* FAR* ppunkEnum)
{
    CEnumVariant FAR* penum = NULL;
    HRESULT hr;
    
    // Create new enumerator for items currently in collection and QI for IUnknown
    hr = CEnumVariant::Create(m_psa, m_cElements, &penum);
    if (FAILED(hr))
        {hr = RaiseException(IDS_OutOfMemory, IID_IPoints); goto error;}       
    hr = penum->QueryInterface(IID_IUnknown, (VOID FAR* FAR*)ppunkEnum);    
    if (FAILED(hr)) 
        {hr = RaiseException(IDS_Unexpected, IID_IPoints); goto error;}         
    return NOERROR; 
    
error:
    if (penum)
        delete penum;    
    return hr;              
}

/* 
 *
 * The following methods are not exposed through Automation
 *
 */

/*
 * CPoints::Add
 *
 * Purpose:
 *  Adds an item to the collection. The points collection does not have duplicates.
 *
 * Parameters:
 *  pPointAdd    Point to be added to collection.
 *
 */
STDMETHODIMP_(BOOL)   
CPoints::Add(CPoint FAR* pPointAdd)
{ 
    HRESULT hr;   
    LONG l;
    VARIANT v;  
    VARIANT HUGEP *pvar;
    int nX, nY;
    BOOL bFound = FALSE;     
    LPDISPATCH pdispPointAdd = NULL;
    CPoint FAR *pPoint;
    LPDISPATCH pdispPoint;   
    
    // Is the collection full?
    if (m_cElements == m_cMax) 
        goto error;              
       
    // Get coordinates of point to be added to collection 
    nX = pPointAdd->get_x();
    nY = pPointAdd->get_y();
          
    hr = SafeArrayAccessData(m_psa, (void HUGEP* FAR*)&pvar);
    if (FAILED(hr))
        goto error; 
              
    // Check if point to be added is already in the collection.       
    for (l=0; l<(long)m_cElements; l++)
    {   
        pdispPoint = V_DISPATCH(&pvar[l]);      
        hr = pdispPoint->QueryInterface(IID_IPoint, (void FAR* FAR*)&pPoint);
        if (FAILED(hr))
            continue;                
        if (nX == pPoint->get_x() &&  nY == pPoint->get_y())
        {   
            // Point is already in the collection. AddRef it.   
            // Internal AddRef keeps track of number of times this point was added to this collection. When
            //    this internal ref count drops to 0, this point can be removed from this collection.  
            pPoint->InternalAddRef();        
            pdispPoint->AddRef();  
            
            bFound = TRUE;
            pPoint->Release(); 
            break; 
        }             
        pPoint->Release();        
    }   
    hr = SafeArrayUnaccessData(m_psa);
    if (FAILED(hr))
       goto error;
           
    // Add point if it was not in the collection.
    if (!bFound)
    {
        l = m_lLBound+m_cElements;    

        hr = pPointAdd->QueryInterface(IID_IDispatch, (void FAR* FAR*)&pdispPointAdd);
        if (FAILED(hr))
            goto error;              
        VariantInit(&v);
        V_VT(&v) = VT_DISPATCH;
        V_DISPATCH(&v) = pdispPointAdd;    
        hr = SafeArrayPutElement(m_psa, &l, &v);
        if (FAILED(hr))
            goto error;   
            
        // Internal AddRef keeps track of number of times this point was added to this collection. When
        //    this internal ref count drops to 0, this point can be removed from this collection.       
        pPointAdd->InternalAddRef();  
        pdispPointAdd->Release();   
          
        m_cElements++;
    }                    
    return TRUE;    
    
error:
    if (pdispPointAdd)
        pdispPointAdd->Release();     
    return FALSE;   
}

/*
 * CPoints::Remove
 *
 * Purpose:
 *  Removes specified item from collection. The points collection does not have duplicates.
 *
 * Parameters:   
 *   pPointRemove    Point to be removed from collection.
 *
 */
STDMETHODIMP_(BOOL)
CPoints::Remove(CPoint FAR* pPointRemove)
{
    HRESULT hr;
    long l, lIndex;
    VARIANT HUGEP *pvar;
    ULONG cRef;
    int nX, nY;
    CPoint FAR* pPoint = NULL;
    BOOL bFound = FALSE;    
    BOOL bRet = FALSE;
    
    // Get coordinates of point to be removed from collection
    nX = pPointRemove->get_x();
    nY = pPointRemove->get_y();
          
    hr = SafeArrayAccessData(m_psa, (void HUGEP* FAR*)&pvar);
    if (FAILED(hr))
       goto error; 

              
    // Check if point to be removed is in the collection.       
    for (l=0; l<(long)m_cElements; l++)
    {        
        hr = V_DISPATCH(&pvar[l])->QueryInterface(IID_IPoint, (void FAR* FAR*)&pPoint);
        if (FAILED(hr))
            continue;
                  
        if (nX == pPoint->get_x() &&  nY == pPoint->get_y())
        {
            // Release point. Note that this collection does not have duplicates. Duplicate
            // points are handled by increasing the ref count.
            V_DISPATCH(&pvar[l])->Release();     
            cRef = pPoint->InternalRelease();  
            bFound = TRUE;
            lIndex = l;
            pPoint->Release(); 
            break; 
        }             
        pPoint->Release();        
    }   
    
    // If the internal ref count of point to be removed has dropped to 0, move up the array elements
    // after the element to be removed.     
    if (bFound && cRef == 0)
    {           
        for (l=lIndex; l<(long)(m_cElements-1); l++)  
            pvar[l] = pvar[l+1];
    
        // Remove last element.    
        V_VT(&pvar[l]) = VT_EMPTY;
        m_cElements--; 
        bRet = TRUE;
    }
            
    hr = SafeArrayUnaccessData(m_psa);
    if (FAILED(hr))
       goto error;          
    return bRet; 
       
error: 
    return FALSE;
}

/*
 * CPoints::Clear
 *
 * Purpose:
 *  Removes all items from collection.
 *
 */
STDMETHODIMP_(void)
CPoints::Clear(void)
{
    SafeArrayDestroyData(m_psa);     
    SafeArrayAllocData(m_psa);
    m_cElements = 0;
}    

/*
 * CPoints::GetMaxXMaxY
 *
 * Purpose:
 *  Get the maximum X and Y coordinates that are in the rectangle, prc.
 *
 */
STDMETHODIMP_(void)
CPoints::GetMaxXMaxY(int FAR *pnX, int FAR *pnY, LPRECT prc)
{   
    HRESULT hr;
    long l;
    VARIANT HUGEP *pvar;
    int nMaxX, nMaxY;       
    CPoint FAR* pPoint;
    POINT pt;
    
    hr = SafeArrayAccessData(m_psa, (void HUGEP* FAR*)&pvar);
    if (FAILED(hr))
       return; 

    nMaxX = -1; nMaxY = -1;
    
    // Find the maximume X and Y coordinates that are in the prc rectangle.    
    for (l=0; l<(long)m_cElements; l++)
    {        
        V_DISPATCH(&pvar[l])->QueryInterface(IID_IPoint, (void FAR* FAR*)&pPoint);
        pt.x = pPoint->get_x(); 
        pt.y = pPoint->get_y();
         
        if (PtInRect(prc, pt))
        {   
            if (pt.x > nMaxX)
                nMaxX = pt.x;
            
            if (pt.y > nMaxY)
                nMaxY = pt.y;
        }        
        pPoint->Release();
    }
    
    *pnX = nMaxX;
    *pnY = nMaxY;    
    
    SafeArrayUnaccessData(m_psa);  
    return;
}  

