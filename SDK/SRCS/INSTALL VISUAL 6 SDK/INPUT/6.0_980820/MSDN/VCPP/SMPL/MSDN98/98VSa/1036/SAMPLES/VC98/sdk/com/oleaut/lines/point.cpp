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
**  OLE Automation Points Object.
**
**  point.cpp
**
**  CPoint implementation
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
 * CPoint::Create
 *
 * Purpose:
 *  Creates an instance of the Point automation object and initializes it.
 *
 * Parameters:
 *  ppPoint    Returns Point automation object.
 *
 * Return Value:
 *  HRESULT
 *
 */
HRESULT 
CPoint::Create(CPoint FAR* FAR* ppPoint ) 
{   
    HRESULT hr;
    CPoint FAR* pPoint = NULL;
     
    *ppPoint = NULL;
    
    pPoint = new CPoint();
    if (pPoint == NULL)
        goto error;
    
    // Load type information for the point from type library. 
    hr = LoadTypeInfo(&pPoint->m_ptinfo, IID_IPoint);
    if (FAILED(hr))
        goto error;

    *ppPoint = pPoint;
    return NOERROR;
    
error:                        
    if (pPoint == NULL)
        return E_OUTOFMEMORY; 
                    
    if (pPoint->m_ptinfo)
        pPoint->m_ptinfo->Release();
    
    // Set to NULL to prevent destructor from attempting to free again
    pPoint->m_ptinfo = NULL; 
    
    delete pPoint;
    return hr;
}

/*
 * CPoint::CPoint
 *
 * Purpose:
 *  Constructor for CPoint object. Initializes members to NULL.
 *
 */
#pragma warning (disable : 4355)
CPoint::CPoint() : m_SupportErrorInfo(this, IID_IPoint)
#pragma warning (default : 4355)
{   
    m_cRef = 0;   
    m_cInternalRef = 0;
    m_ptinfo = NULL;
    m_nX = -1;
    m_nY = -1;    
}

/*
 * CPoint::~CPoint
 *
 * Purpose:
 *  Destructor for CPoint object. Frees Point message BSTR and default
 *  IDispatch implementation. Closes the aplication.
 *
 */
CPoint::~CPoint()
{            
     if (m_ptinfo) m_ptinfo->Release();  
}

/*
 * CPoint::QueryInterface, AddRef, Release
 *
 * Purpose:
 *  Implements IUnknown::QueryInterface, AddRef, Release
 *
 */
STDMETHODIMP
CPoint::QueryInterface(REFIID iid, void FAR* FAR* ppv) 
{   
    *ppv = NULL;
    
    if (iid == IID_IUnknown || iid == IID_IDispatch || iid == IID_IPoint)
        *ppv = this;   
    else if (iid == IID_ISupportErrorInfo)
        *ppv = &m_SupportErrorInfo;
    else return E_NOINTERFACE; 

    AddRef();
    return NOERROR;    
}


STDMETHODIMP_(ULONG)
CPoint::AddRef(void)
{ 
#ifdef _DEBUG  
    TCHAR ach[50];
    wsprintf(ach, TEXT("Ref = %ld, Point\r\n"), m_cRef+1); 
    OutputDebugString(ach); 
#endif  

    return ++m_cRef;
}

STDMETHODIMP_(ULONG)
CPoint::Release(void)
{
#ifdef _DEBUG  
    TCHAR ach[50];
    wsprintf(ach, TEXT("Ref = %ld, Point\r\n"), m_cRef-1); 
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
 * CPoint::GetTypeInfoCount
 *
 * Purpose:
 *  Implements IDispatch::GetTypeInfoCount.
 *
 */
STDMETHODIMP
CPoint::GetTypeInfoCount(UINT FAR* pctinfo)
{
    *pctinfo = 1;
    return NOERROR;
}

/*
 * CPoint::GetTypeInfo
 *
 * Purpose:
 *  Implements IDispatch::GetTypeInfo. 
 *
 */
STDMETHODIMP
CPoint::GetTypeInfo(
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
 * CPoint::GetIDsOfNames
 *
 * Purpose:
 *  Implements IDispatch::GetIDsOfNames.  The standard implementation, DispGetIDsOfNames,
 *  is used.
 *
 */
STDMETHODIMP 
CPoint::GetIDsOfNames(
      REFIID riid,
      OLECHAR FAR* FAR* rgszNames,
      UINT cNames,
      LCID lcid,
      DISPID FAR* rgdispid)
{
    return DispGetIDsOfNames(m_ptinfo, rgszNames, cNames, rgdispid);
}

/*
 * CPoint::Invoke
 *
 * Purpose:
 *  Implements IDispatch::Invoke.  The standard implementation, DispInvoke,
 *  is used.
 *
 */
STDMETHODIMP
CPoint::Invoke(
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

STDMETHODIMP
CPoint::get_x(int FAR* pnX)
{
    *pnX = m_nX;   
    return NOERROR;
}

STDMETHODIMP
CPoint::put_x(int nX)
{
    m_nX = nX;
    return NOERROR;
}

STDMETHODIMP
CPoint::get_y(int FAR* pnY)
{
    *pnY = m_nY; 
    return NOERROR;
}

STDMETHODIMP
CPoint::put_y(int nY)
{
    m_nY = nY;  
    return NOERROR;
}  

/* 
 *
 * The following methods are not exposed through Automation
 *
 */

/*
 * CPoint::InternalAddRef, InternalRelease
 *
 * Purpose:  
 *  Implements an internal ref count for the use of the points collection.
 *  The points collection does not have duplicates, instead a reference count is incremented.
 *  A point is removed from the collection when the reference count drops to 0.
 *
 */
STDMETHODIMP_(ULONG)
CPoint::InternalAddRef(void)
{ 
#ifdef _DEBUG  
    TCHAR ach[50];
    wsprintf(ach, TEXT("Internal Ref = %ld, Point\r\n"), m_cInternalRef+1); 
    OutputDebugString(ach); 
#endif  

    return ++m_cInternalRef;
}

STDMETHODIMP_(ULONG)
CPoint::InternalRelease(void)
{
#ifdef _DEBUG  
    TCHAR ach[50];
    wsprintf(ach, TEXT("Internal Ref = %ld, Point\r\n"), m_cInternalRef-1); 
    OutputDebugString(ach);   
#endif
    
    return --m_cInternalRef;
}    

STDMETHODIMP_(int)
CPoint::get_x(void)
{
    return m_nX;
}


STDMETHODIMP_(int)
CPoint::get_y(void)
{
    return m_nY;
}
