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
**  OLE Automation Lines Object.
**
**  line.cpp
**
**  CLine implementation
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
 * CLine::Create
 *
 * Purpose:
 *  Creates an instance of the Line automation object and initializes it.
 *
 * Parameters:
 *  ppLine    Returns Line automation object.
 *
 * Return Value:
 *  HRESULT
 *
 */
HRESULT 
CLine::Create(CLine FAR* FAR* ppLine ) 
{   
    HRESULT hr;
    CLine FAR* pLine = NULL;
     
    *ppLine = NULL;
    
    pLine = new CLine();
    if (pLine == NULL)
        goto error;        
    
    // Load type information for the line from type library. 
    hr = LoadTypeInfo(&pLine->m_ptinfo, IID_ILine);
    if (FAILED(hr))
        goto error;

    *ppLine = pLine;
    return NOERROR;
    
error:                        
    if (pLine == NULL)
        return E_OUTOFMEMORY; 
                    
    if (pLine->m_ptinfo)
        pLine->m_ptinfo->Release();
    
    // Set to NULL to prevent destructor from attempting to free again
    pLine->m_ptinfo = NULL; 
    
    delete pLine;
    return hr;
}

/*
 * CLine::CLine
 *
 * Purpose:
 *  Constructor for CLine object. Initializes members to NULL.
 *
 */
#pragma warning (disable : 4355)
CLine::CLine() : m_SupportErrorInfo(this, IID_ILine)
#pragma warning (default : 4355)
{   
    m_ptinfo = NULL;
    m_pPointStart = NULL;
    m_pPointEnd = NULL;
    m_nThickness = 0;  
    m_colorref = 0;    
    m_cRef = 0;  
}

/*
 * CLine::~CLine
 *
 * Purpose:
 *  Destructor for CLine object.
 *
 */
CLine::~CLine()
{            
     if (m_ptinfo) m_ptinfo->Release(); 
     if (m_pPointStart) m_pPointStart->Release();
     if (m_pPointEnd) m_pPointEnd->Release(); 
}

/*
 * CLine::QueryInterface, AddRef, Release
 *
 * Purpose:
 *  Implements IUnknown::QueryInterface, AddRef, Release
 *
 */
STDMETHODIMP
CLine::QueryInterface(REFIID iid, void FAR* FAR* ppv) 
{   
    *ppv = NULL;
    
    if (iid == IID_IUnknown || iid == IID_IDispatch || iid == IID_ILine)
        *ppv = this; 
    else if (iid == IID_ISupportErrorInfo)
        *ppv = &m_SupportErrorInfo;
    else return E_NOINTERFACE; 

    AddRef();
    return NOERROR;    
}


STDMETHODIMP_(ULONG)
CLine::AddRef(void)
{  

#ifdef _DEBUG  
    TCHAR ach[50];
    wsprintf(ach, TEXT("Ref = %ld, Line\r\n"), m_cRef+1); 
    OutputDebugString(ach); 
#endif  

    return ++m_cRef;
}

STDMETHODIMP_(ULONG)
CLine::Release(void)
{    
#ifdef _DEBUG  
    TCHAR ach[50];
    wsprintf(ach, TEXT("Ref = %ld, Line\r\n"), m_cRef-1); 
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
 * CLine::GetTypeInfoCount
 *
 * Purpose:
 *  Implements IDispatch::GetTypeInfoCount.
 *
 */
STDMETHODIMP
CLine::GetTypeInfoCount(UINT FAR* pctinfo)
{
    *pctinfo = 1;
    return NOERROR;
}

/*
 * CLine::GetTypeInfo
 *
 * Purpose:
 *  Implements IDispatch::GetTypeInfo. 
 *
 */
STDMETHODIMP
CLine::GetTypeInfo(
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
 * CLine::GetIDsOfNames
 *
 * Purpose:
 *  Implements IDispatch::GetIDsOfNames.  The standard implementation, DispGetIDsOfNames,
 *  is used.
 *
 */
STDMETHODIMP 
CLine::GetIDsOfNames(
      REFIID riid,
      OLECHAR FAR* FAR* rgszNames,
      UINT cNames,
      LCID lcid,
      DISPID FAR* rgdispid)
{
    return DispGetIDsOfNames(m_ptinfo, rgszNames, cNames, rgdispid);
}

/*
 * CLine::Invoke
 *
 * Purpose:
 *  Implements IDispatch::Invoke.  The standard implementation, DispInvoke,
 *  is used. 
 *
 */
STDMETHODIMP
CLine::Invoke(
      DISPID dispidMember,
      REFIID riid,
      LCID lcid,
      WORD wFlags,
      DISPPARAMS FAR* pdispparams,
      VARIANT FAR* pvarResult,
      EXCEPINFO FAR* pexcepinfo,
      UINT FAR* puArgErr)
{  
    // VB 3.0/Disptest have a bug in which they pass DISPATCH_PROPERTYPUT
    // instead of DISPATCH_PROPERTYPUTREF for the EndPoint and StartPoint
    // properties. Future versions of VB will correctly pass DISPATCH_PROPERTYPUTREF.
    // EndPoint has DISPID == 1 and StartPoint has DISPID == 2 - see lines.odl. 
    // The following code works around the VB 3.0/Disptest bug. 
    if ((dispidMember == 1 || dispidMember == 2)
        && wFlags == DISPATCH_PROPERTYPUT)
        wFlags = DISPATCH_PROPERTYPUTREF;

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
STDMETHODIMP
CLine::get_Color(long FAR* plColorref)
{
    *plColorref =  m_colorref;   
    return NOERROR;
}

STDMETHODIMP
CLine::put_Color(long lColorref)
{
    m_colorref = (COLORREF)lColorref;  
    return NOERROR;
}

STDMETHODIMP
CLine::get_EndPoint(IPoint FAR* FAR* ppPoint)
{   
    HRESULT hr;       
    
    *ppPoint = NULL;
    
    if (NULL == m_pPointEnd)  
        return RaiseException(IDS_NoStartPoint, IID_ILine);                      
    
    hr = m_pPointEnd->QueryInterface(IID_IDispatch, (void FAR* FAR*)ppPoint);
    if (FAILED(hr))
        return RaiseException(IDS_Unexpected, IID_ILine); 
    return NOERROR; 
}

STDMETHODIMP
CLine::putref_EndPoint(IPoint FAR* pPointNew)
{   
    HRESULT hr;
    CPoint FAR* pPoint;
    
    // Save the IPoint interface so we can easily access private data
    hr = pPointNew->QueryInterface(IID_IPoint, (void FAR* FAR*)&pPoint);
    if (FAILED(hr))
        return RaiseException(IDS_PointFromOtherInstance, IID_ILine);    
        
    // Replace the old point with the new
    if (m_pPointEnd)
       m_pPointEnd->Release();    

    m_pPointEnd = pPoint;   
    return NOERROR;
}          

STDMETHODIMP
CLine::get_StartPoint(IPoint FAR* FAR* ppPoint)
{   
    HRESULT hr;     
    
    *ppPoint = NULL;
    
    if (NULL == m_pPointStart)  
        return RaiseException(IDS_NoStartPoint, IID_ILine);              
    
    hr = m_pPointStart->QueryInterface(IID_IDispatch, (void FAR* FAR*)ppPoint);
    if (FAILED(hr))
        return RaiseException(IDS_Unexpected, IID_ILine); 

    return NOERROR;
}

STDMETHODIMP
CLine::putref_StartPoint(IPoint FAR* pPointNew)
{
    HRESULT hr;
    CPoint FAR* pPoint;
    
    // Save the IPoint interface so we can easily access private data
    hr = pPointNew->QueryInterface(IID_IPoint, (void FAR* FAR*)&pPoint);
    if (FAILED(hr))
        return RaiseException(IDS_PointFromOtherInstance, IID_ILine);   
        
    // Replace the old point with the new
    if (m_pPointStart)
       m_pPointStart->Release();    

    m_pPointStart = pPoint;   
    return NOERROR;
}

STDMETHODIMP
CLine::get_Thickness(int FAR* pnThickness)
{
    *pnThickness = m_nThickness;
    return NOERROR;
}

STDMETHODIMP
CLine::put_Thickness(int nThickness)
{
    m_nThickness = nThickness;  
    return NOERROR;
}

/* 
 *
 * The following methods are not exposed through Automation
 *
 */  

STDMETHODIMP_(void)
CLine::Draw(HDC hdc)
{
    HPEN hpen, hpenOld;
    
    if (m_pPointStart == NULL)
        return;
    if (m_pPointEnd == NULL)
        return;
    
    hpen = CreatePen(PS_SOLID, m_nThickness, m_colorref);
    hpenOld = (HPEN) (HGDIOBJ)SelectObject(hdc, (HGDIOBJ)hpen);          
      
    MoveToEx(hdc, m_pPointStart->get_x(), m_pPointStart->get_y(), NULL);
    LineTo(hdc, m_pPointEnd->get_x(), m_pPointEnd->get_y());
    
    SelectObject(hdc, (HGDIOBJ)hpenOld);
    DeleteObject((HGDIOBJ)hpen);     
    return;                 
}

/*
 * CLine::GetInvalidateRect
 *
 * Purpose:
 *  Get the rectangle that cicumscribes the line. This rectangle is used to invalidate the area
 *  of the window where the line is to be draw or erased.
 *
 */
STDMETHODIMP_(void)
CLine::GetInvalidateRect(LPRECT prc)
{    
    int nX1, nY1, nX2, nY2;
   
    nX1 = m_pPointStart->get_x();
    nY1 = m_pPointStart->get_y();
  
    nX2 = m_pPointEnd->get_x();
    nY2 = m_pPointEnd->get_y();
    
    if (nX1 < nX2)
    {
        prc->left = nX1;
        prc->right = nX2;
    }
    else 
    {    
        prc->left = nX2;
        prc->right = nX1;     
    }
    if (nY1 < nY2)
    {
        prc->top = nY1;
        prc->bottom = nY2;
    }
    else 
    {    
        prc->top = nY2;
        prc->bottom = nY1;     
    }  

    InflateRect(prc, m_nThickness, m_nThickness);
} 

STDMETHODIMP_(BOOL)
CLine::AddEndPointsToPane(CPane FAR* pPane)
{ 
    // Does the line have end points?
    if (NULL == m_pPointStart)
       return FALSE;
    if (NULL == m_pPointEnd)
       return FALSE;
    
    // Add points to Point collection in the Pane object.
    if (pPane->AddPoint(m_pPointStart))
        return pPane->AddPoint(m_pPointEnd); 
    return FALSE;

}

STDMETHODIMP_(void)
CLine::RemoveEndPointsFromPane(CPane FAR* pPane)
{    
    // Remove the end points of the line to be removed from the Points collection in the Pane.      
    if (NULL != m_pPointStart)
        pPane->RemovePoint(m_pPointStart);
    if (NULL != m_pPointEnd)
       pPane->RemovePoint(m_pPointEnd);   

}    
