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
**  OLE Automation Lines object
**
**  lines.cpp
**
**  CLines collection implementation
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
 * CLines::Create
 *
 * Purpose:
 *  Creates an instance of a Lines collection object and initializes it.
 *
 * Parameters:
 *  lMaxSize   Maximum number of items that can added to collection.
 *  lLBound    Lower bound of index of collection.  
 *  pPane      Pointer to pane that contains this collection. Required because the pane coordinates 
 *             the lines and points collection.
 *  ppLines    Returns Lines collection object.
 *
 * Return Value:
 *  HRESULT
 *
 */
HRESULT
CLines::Create(ULONG lMaxSize, long lLBound, CPane FAR* pPane, CLines FAR* FAR* ppLines) 
{   
    HRESULT hr;
    CLines FAR* pLines = NULL;
    SAFEARRAYBOUND sabound[1];
     
    *ppLines = NULL;
    
    // Create new collection
    pLines = new CLines();
    if (pLines == NULL)
        goto error;

    pLines->m_cMax = lMaxSize;
    pLines->m_cElements = 0; 
    pLines->m_lLBound = lLBound;
    pLines->m_pPane = pPane;      
    
    // Load type information for the Lines collection from type library. 
    hr = LoadTypeInfo(&pLines->m_ptinfo, IID_ILines);
    if (FAILED(hr))
        goto error;
    
    // Create a safe array of variants which is used to implement the collection.            
    sabound[0].cElements = lMaxSize;
    sabound[0].lLbound = lLBound;        
    pLines->m_psa = SafeArrayCreate(VT_VARIANT, 1, sabound);
    if (pLines->m_psa == NULL)
    {
        hr = E_OUTOFMEMORY;
        goto error;
    }             

    *ppLines = pLines;
    return NOERROR;
    
error: 
    if (pLines == NULL)
        return E_OUTOFMEMORY;
    if (pLines->m_ptinfo)
        pLines->m_ptinfo->Release();                            
    if (pLines->m_psa) 
        SafeArrayDestroy(pLines->m_psa); 
  
    pLines->m_psa = NULL;
    pLines->m_ptinfo = NULL; 
    
    delete pLines;
    return hr;
}

/*
 * CLines::CLines
 *
 * Purpose:
 *  Constructor for CLines object. Initializes members to NULL.
 *
 */
#pragma warning (disable : 4355)
CLines::CLines() : m_SupportErrorInfo(this, IID_ILines)
#pragma warning (default : 4355)
{    
    m_cRef = 0;
    m_psa = NULL;
    m_ptinfo = NULL; 
}

/*
 * CLines::~CLines
 *
 * Purpose:
 *  Destructor for CLines object. 
 *
 */
CLines::~CLines()
{    
     if (m_ptinfo) m_ptinfo->Release();                   
     if (m_psa) SafeArrayDestroy(m_psa);
}

/*
 * CLines::QueryInterface, AddRef, Release
 *
 * Purpose:
 *  Implements IUnknown::QueryInterface, AddRef, Release
 *
 */
STDMETHODIMP
CLines::QueryInterface(REFIID iid, void FAR* FAR* ppv) 
{    
    *ppv = NULL;
        
    if (iid == IID_IUnknown || iid == IID_ILines || iid == IID_IDispatch)
        *ppv = this;     
    else if (iid == IID_ISupportErrorInfo)
        *ppv = &m_SupportErrorInfo;
    else return E_NOINTERFACE; 

    AddRef();
    return NOERROR;    
}


STDMETHODIMP_(ULONG)
CLines::AddRef(void)
{ 

#ifdef _DEBUG  
    TCHAR ach[50];
    wsprintf(ach, TEXT("Ref = %ld, Lines\r\n"), m_cRef+1); 
    OutputDebugString(ach); 
#endif  
    
    return ++m_cRef;
}


STDMETHODIMP_(ULONG)
CLines::Release(void)
{ 

#ifdef _DEBUG  
    TCHAR ach[50];
    wsprintf(ach, TEXT("Ref = %ld, Lines\r\n"), m_cRef-1); 
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
 * CLines::GetTypeInfoCount
 *
 * Purpose:
 *  Implements IDispatch::GetTypeInfoCount.
 *
 */
STDMETHODIMP
CLines::GetTypeInfoCount(UINT FAR* pctinfo)
{
    *pctinfo = 1;
    return NOERROR;
}

/*
 * CLines::GetTypeInfo
 *
 * Purpose:
 *  Implements IDispatch::GetTypeInfo. 
 *
 */
STDMETHODIMP
CLines::GetTypeInfo(
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
 * CLines::GetIDsOfNames
 *
 * Purpose:
 *  Implements IDispatch::GetIDsOfNames.  The standard implementation, DispGetIDsOfNames,
 *  is used.
 *
 */
STDMETHODIMP 
CLines::GetIDsOfNames(
      REFIID riid,
      OLECHAR FAR* FAR* rgszNames,
      UINT cNames,
      LCID lcid,
      DISPID FAR* rgdispid)
{
    return DispGetIDsOfNames(m_ptinfo, rgszNames, cNames, rgdispid);
}

/*
 * CLines::Invoke
 *
 * Purpose:
 *  Implements IDispatch::Invoke.  The standard implementation, DispInvoke,
 *  is used.
 *
 */
STDMETHODIMP
CLines::Invoke(
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
 * 
 * Properties and methods exposed through automation.
 *
 */

/*
 * CLines::Add
 *
 * Purpose:
 *  Adds a line to the lines collection. 
 *
 * Parameters:
 *  pLineNew    IDispatch of line to be added to collection.
 *
 */
STDMETHODIMP  
CLines::Add(ILine FAR* pLineNew)
{ 
    HRESULT hr;   
    LONG l;
    CLine FAR* pLine = NULL;
    VARIANT v;       
    HDC hdc;
    
    // Is the collection full?
    if (m_cElements == m_cMax) 
        return RaiseException(IDS_CollectionFull, IID_ILines);

    hr = pLineNew->QueryInterface(IID_ILine, (void FAR* FAR*)&pLine);
    if (FAILED(hr))
        return RaiseException(IDS_LineFromOtherInstance, IID_ILines);
    
    // Add end points of line to the pane's point collection    
    if (FALSE == pLine->AddEndPointsToPane(m_pPane))     
        {hr = RaiseException(IDS_CantAddEndPoints, IID_ILines); goto error;}  
    
    // Add new line to collection
    l = m_lLBound+m_cElements; 
    VariantInit(&v);
    V_VT(&v) = VT_DISPATCH;
    V_DISPATCH(&v) = pLineNew;    
    hr = SafeArrayPutElement(m_psa, &l, &v);
    if (FAILED(hr))
        {hr = RaiseException(IDS_Unexpected, IID_ILines); goto error;}  
    m_cElements++;   
    
    // Draw the new line
    hdc = m_pPane->GetDC();    
    pLine->Draw(hdc);
    m_pPane->ReleaseDC(hdc);  
    
    pLine->Release();                    
    return NOERROR;    
    
error:  
    if (pLine)
        pLine->Release();      
    return hr;   
}

/*
 * CLines::get_Count
 *
 * Purpose:
 *  Returns number of items in collection.
 *
 */
STDMETHODIMP    
CLines::get_Count(long FAR* lCount)  
{
    *lCount = m_cElements;
    return NOERROR;             
}

/*
 * CLines::get_Item
 *
 * Purpose:
 *  Retrieves item from collection, given an index. 
 *
 * Parameters:   
 *   lIndex   Index of item to be retrieved. 
 *   ppLine   Returns IDispatch of item retrieved from collection.
 *
 */
STDMETHODIMP
CLines::get_Item(long lIndex, ILine FAR* FAR* ppLine)
{ 
    HRESULT hr;                                            
    VARIANT v;
   
    // Check if index is within range         
    if (lIndex < m_lLBound || lIndex >= (long)(m_lLBound+m_cElements)) 
        return RaiseException(IDS_InvalidIndex, IID_ILines); 
    
    // Retrieve and return item. Note that SafeArrayGetElement AddRefs, so an additional AddRef
    // is not required.
    VariantInit(&v);
    hr = SafeArrayGetElement(m_psa, &lIndex, &v);
    if (FAILED(hr))
        return RaiseException(IDS_Unexpected, IID_ILines);
    *ppLine = (ILine FAR*) V_DISPATCH(&v);  
    return NOERROR;
}

/*
 * CLines::get_NewEnum
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
CLines::get__NewEnum(IUnknown FAR* FAR* ppunkEnum)
{
    CEnumVariant FAR* penum = NULL;;
    HRESULT hr;
    
    *ppunkEnum = NULL;
    
    // Create new enumerator for items currently in collection and QI for IUnknown
    hr = CEnumVariant::Create(m_psa, m_cElements, &penum);
    if (FAILED(hr))
        {hr = RaiseException(IDS_OutOfMemory, IID_ILines); goto error;}        
    hr = penum->QueryInterface(IID_IUnknown, (VOID FAR* FAR*)ppunkEnum);    
    if (FAILED(hr)) 
        {hr = RaiseException(IDS_Unexpected, IID_ILines); goto error;}  
    return NOERROR; 
    
error:
    if (penum)
        delete penum;   
    return hr;              
}

/*
 * CLines::Remove
 *
 * Purpose:
 *  Removes specified item from collection. 
 *
 * Parameters:   
 *   lIndex   Index of item to be removed. 
 *
 */
STDMETHODIMP
CLines::Remove(long lIndex)
{
    HRESULT hr;
    long l;
    VARIANT HUGEP *pvar;
    CLine FAR* pLine = NULL;  
    RECT rc;
    
    // Check if integer index is within range. 
    if (lIndex < m_lLBound || lIndex >= (long)(m_lLBound+m_cElements))
        return RaiseException(IDS_InvalidIndex, IID_ILines);    

    hr = SafeArrayAccessData(m_psa, (void HUGEP* FAR*)&pvar);
    if (FAILED(hr))
        return RaiseException(IDS_Unexpected, IID_ILines); 
    V_DISPATCH(&pvar[lIndex-m_lLBound])->QueryInterface(IID_ILine, (void FAR* FAR*)&pLine);         
     
    // Ask the pane to invalidate the area where the line is drawn.
    pLine->GetInvalidateRect(&rc);
    m_pPane->InvalidateRect(&rc);
    
    // Remove end points of line from the pane's point collection.   
    pLine->RemoveEndPointsFromPane(m_pPane);    
    // Remove Line  
    V_DISPATCH(&pvar[lIndex-m_lLBound])->Release();    
    // Move up the array elements, after the element to be removed.        
    for (l=lIndex-m_lLBound; l<(long)(m_cElements-1); l++)  
        pvar[l] = pvar[l+1];    
    // Remove last element.    
    V_VT(&pvar[l]) = VT_EMPTY;
    
    pLine->Release();        
    hr = SafeArrayUnaccessData(m_psa);
    if (FAILED(hr))
       return RaiseException(IDS_Unexpected, IID_ILines); 
       
    m_cElements--;  
    m_pPane->Update();     // Ask the pane to repaint invalidated areas caused by removal of line.
    return NOERROR;
}

/* 
 *
 * The following methods are not exposed through Automation
 *
 */  
 
/*
 * CLines::Draw
 *
 * Purpose:
 *  Draws all lines in collection.
 *
 */
STDMETHODIMP_(void)
CLines::Draw(HDC hdc)
{
    HRESULT hr;
    long l;
    CLine FAR* pLine = NULL;
    VARIANT HUGEP *pvar;
    
    // Draw each line in the Lines collection
    hr = SafeArrayAccessData(m_psa, (void HUGEP* FAR*)&pvar);
    if (FAILED(hr))
       return;           
    for (l=0; l<(long)m_cElements; l++)
    {        
        hr = V_DISPATCH(&pvar[l])->QueryInterface(IID_ILine, (void FAR* FAR*)&pLine);
        if (FAILED(hr))
            continue;          
        pLine->Draw(hdc);
        pLine->Release();        
    }   
    hr = SafeArrayUnaccessData(m_psa);
    if (FAILED(hr))
        return;
    return;
}

/*
 * CLines::Clear
 *
 * Purpose:
 *  Removes all items from collection.
 *
 */
STDMETHODIMP_(void)
CLines::Clear(void)
{
    SafeArrayDestroyData(m_psa);   
    SafeArrayAllocData(m_psa);
    m_cElements = 0;
}

