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
**  pane.cpp
**
**  CPane implementation
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
 * CPane::Create
 *
 * Purpose:
 *  Creates an instance of the Pane automation object and initializes it.
 *
 * Parameters:  
 *  hwnd      Handle of the window of the pane.
 *  ppPane    Returns Pane automation object.
 *
 * Return Value:
 *  HRESULT
 *
 */
HRESULT 
CPane::Create(HWND hwnd, CPane FAR* FAR* ppPane ) 
{   
    HRESULT hr;
    CPane FAR* pPane = NULL;
     
    *ppPane = NULL;
    
    pPane = new CPane();
    if (pPane == NULL)
        goto error;
        
    pPane->m_hwnd = hwnd;        
    
    // Create an empty Lines collection of size 100
    hr = CLines::Create(100, 1, pPane, &pPane->m_pLines);    
    if (FAILED(hr))
       goto error;    
    pPane->m_pLines->AddRef();  
    
    // Create an empty Points collection of size 200   
    hr = CPoints::Create(200, 1, pPane, &pPane->m_pPoints);  
    if (FAILED(hr))
       goto error;      
    pPane->m_pPoints->AddRef(); 
    
    // Load type information for the pane object from type library. 
    hr = LoadTypeInfo(&pPane->m_ptinfo, IID_IPane);
    if (FAILED(hr))
        goto error;

    *ppPane = pPane;
    return NOERROR;
    
error:                        
    if (pPane == NULL)
        return E_OUTOFMEMORY; 
                    
    if (pPane->m_ptinfo)
        pPane->m_ptinfo->Release();        
    if (pPane->m_pLines)
        pPane->m_pLines->Release();
    if (pPane->m_pPoints)
        pPane->m_pPoints->Release();
    
    // Set to NULL to prevent destructor from attempting to free again
    pPane->m_ptinfo = NULL; 
    pPane->m_pLines = NULL;
    pPane->m_pPoints = NULL;
    
    delete pPane;
    return hr;
}

/*
 * CPane::CPane
 *
 * Purpose:
 *  Constructor for CPane object. Initializes members to NULL.
 *
 */
#pragma warning (disable : 4355)
CPane::CPane() : m_SupportErrorInfo(this, IID_IPane)
#pragma warning (default : 4355)
{   
    m_cRef = 0;
    m_hwnd = NULL;
    m_ptinfo = NULL;  
    m_pLines = NULL;
    m_pPoints = NULL;  
    m_nMaxX = -1;
    m_nMaxY = -1;
}

/*
 * CPane::~CPane
 *
 * Purpose:
 *  Destructor for CPane object. 
 *
 */
CPane::~CPane()
{            
     if (m_ptinfo) m_ptinfo->Release(); 
     if (m_pLines) m_pLines->Release();
     if (m_pPoints) m_pPoints->Release(); 
}

/*
 * CPane::QueryInterface, AddRef, Release
 *
 * Purpose:
 *  Implements IUnknown::QueryInterface, AddRef, Release
 *
 */
STDMETHODIMP
CPane::QueryInterface(REFIID iid, void FAR* FAR* ppv) 
{   
    *ppv = NULL;
    
    if (iid == IID_IUnknown || iid == IID_IDispatch || iid == IID_IPane)
        *ppv = this; 
    else if (iid == IID_ISupportErrorInfo)
        *ppv = &m_SupportErrorInfo;
    else return E_NOINTERFACE; 

    AddRef();
    return NOERROR;    
}


STDMETHODIMP_(ULONG)
CPane::AddRef(void)
{   
#ifdef _DEBUG  
    TCHAR ach[50];
    wsprintf(ach, TEXT("Ref = %ld, Pane\r\n"), m_cRef+1); 
    OutputDebugString(ach); 
#endif    

    return ++m_cRef;
}

STDMETHODIMP_(ULONG)
CPane::Release(void)
{  
#ifdef _DEBUG  
    TCHAR ach[50];
    wsprintf(ach, TEXT("Ref = %ld, Pane\r\n"), m_cRef-1); 
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
 * CPane::GetTypeInfoCount
 *
 * Purpose:
 *  Implements IDispatch::GetTypeInfoCount.
 *
 */
STDMETHODIMP
CPane::GetTypeInfoCount(UINT FAR* pctinfo)
{
    *pctinfo = 1;
    return NOERROR;
}

/*
 * CPane::GetTypeInfo
 *
 * Purpose:
 *  Implements IDispatch::GetTypeInfo. 
 *
 */
STDMETHODIMP
CPane::GetTypeInfo(
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
 * CPane::GetIDsOfNames
 *
 * Purpose:
 *  Implements IDispatch::GetIDsOfNames.  The standard implementation, DispGetIDsOfNames,
 *  is used.
 *
 */
STDMETHODIMP 
CPane::GetIDsOfNames(
      REFIID riid,
      OLECHAR FAR* FAR* rgszNames,
      UINT cNames,
      LCID lcid,
      DISPID FAR* rgdispid)
{
    return DispGetIDsOfNames(m_ptinfo, rgszNames, cNames, rgdispid);
}

/*
 * CPane::Invoke
 *
 * Purpose:
 *  Implements IDispatch::Invoke.  The standard implementation, DispInvoke,
 *  is used.
 *
 */
STDMETHODIMP
CPane::Invoke(
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
 * CPane::get_Lines
 *
 * Purpose:
 *  Returns the collection of all line objects in the drawing.
 *
 */
STDMETHODIMP
CPane::get_Lines(ILines FAR* FAR* ppLines)
{
    HRESULT hr;
    
    hr = m_pLines->QueryInterface(IID_IDispatch, (void FAR* FAR*)ppLines); 
    if (FAILED(hr))
        return RaiseException(IDS_Unexpected, IID_IPane); 
    return NOERROR;
}

/*
 * CPane::get_Points
 *
 * Purpose:
 *  Returns the collection of all point objects in the drawing.
 *
 */
STDMETHODIMP
CPane::get_Points(IPoints FAR* FAR* ppPoints)
{
    HRESULT hr;
    
    hr = m_pPoints->QueryInterface(IID_IDispatch, (void FAR* FAR*)ppPoints); 
    if (FAILED(hr))
        return RaiseException(IDS_Unexpected, IID_IPane);
    return NOERROR;
}

/*
 * CPane::get_MaxX, get_MaxY
 *
 * Purpose:
 *  Returns the maximum visible X & Y coordinate values in twips.
 *
 */
STDMETHODIMP
CPane::get_MaxX(int FAR* pnMaxX)
{   
     *pnMaxX = m_nMaxX; 
    if (m_nMaxX == -1)
        return RaiseException(IDS_NoVisibleXCoordinate, IID_IPane);    
    return NOERROR;
}

STDMETHODIMP
CPane::get_MaxY(int FAR* pnMaxY)
{   
    *pnMaxY = m_nMaxY; 
    if (m_nMaxY == -1)
        return RaiseException(IDS_NoVisibleYCoordinate, IID_IPane);   
    return NOERROR;
}

/*
 * CPane::Clear
 *
 * Purpose:
 *  Removes all the Lines and Points from the drawing and refreshes the client area.
 *  The result is a blank slate as if the application had just been launched.
 *
 */
STDMETHODIMP
CPane::Clear()
{
    m_pLines->Clear();
    m_pPoints->Clear();
    ::InvalidateRect(m_hwnd, NULL, TRUE);
    UpdateWindow(m_hwnd);  
    m_nMaxX = m_nMaxY = -1;  
    return NOERROR;    
}

/*
 * CPane::Refresh
 *
 * Purpose:
 *  Invalidates the entire drawing window so the drawing is cleared
 *  and each of the lines in the Lines collection is redrawn.
 *
 */
STDMETHODIMP
CPane::Refresh()
{
    ::InvalidateRect(m_hwnd, NULL, TRUE);
    UpdateWindow(m_hwnd);
    return NOERROR;    
}

/* 
 *
 * The following methods are not exposed through Automation
 *
 */

STDMETHODIMP_(void)
CPane::Draw(void)
{
    PAINTSTRUCT ps;
    
    BeginPaint(m_hwnd, &ps);
    SetMapMode(ps.hdc, MM_TWIPS);   
    SetWindowOrgEx(ps.hdc, 0, m_nHeight, NULL);
    m_pLines->Draw(ps.hdc);
    EndPaint(m_hwnd, &ps);
}  

/*
 * CPane::OnSize
 *
 * Purpose:
 *  Called when the pane is resized. Remembers the new size and gets the new maximum visible
 *  x and y coordinates.
 *
 */ 
STDMETHODIMP_(void)
CPane::OnSize(unsigned int nWidth, unsigned int nHeight) 
{
   HDC hdc;
   POINT pt;      
   RECT rc;
   
   // Translate the height and width of pane from device units to twips.
   hdc = ::GetDC(m_hwnd);
   SetMapMode(hdc, MM_TWIPS); 
   pt.x = nWidth; pt.y = nHeight;
   DPtoLP(hdc, &pt, 1);
   m_nWidth = pt.x;
   m_nHeight = -pt.y;
   ::ReleaseDC(m_hwnd, hdc); 
   
   // Get the new max visible x and y coordinates   
   SetRect(&rc, 0, 0, m_nWidth, m_nHeight);
   m_pPoints->GetMaxXMaxY(&m_nMaxX, &m_nMaxY, &rc);   
}

STDMETHODIMP_(HDC)
CPane::GetDC()
{
    HDC hdc;        
    
    hdc = ::GetDC(m_hwnd);  
    SetMapMode(hdc, MM_TWIPS);    
    SetWindowOrgEx(hdc, 0, m_nHeight, NULL);
    return hdc;
}    

STDMETHODIMP_(void)
CPane::ReleaseDC(HDC hdc)
{    
    ::ReleaseDC(m_hwnd, hdc);
}  

STDMETHODIMP_(void)
CPane::InvalidateRect(LPRECT prc)
{   
    RECT rc;
    HDC hdc;  
    int t;
    
   // Translate the area to be invalidated from twips to device units
   hdc = ::GetDC(m_hwnd);
   SetMapMode(hdc, MM_TWIPS); 
   SetWindowOrgEx(hdc, 0, m_nHeight, NULL);   
   rc = *prc;
   LPtoDP(hdc, (LPPOINT)&rc.left, 1);     
   LPtoDP(hdc, (LPPOINT)&rc.right, 1);   
   
   // Make sure left is not greater than right and top is not greater than bottom. Otherwise
   // InvalidateRect will not invalidate.
   if (rc.right < rc.left)
   {
       t = rc.right;
       rc.right = rc.left;
       rc.left = t;
   }
   if (rc.bottom < rc.top)
   {
       t = rc.bottom;
       rc.bottom = rc.top;
       rc.top = t;
   }  
   
   ::InvalidateRect(m_hwnd, &rc, TRUE);    
   ::ReleaseDC(m_hwnd, hdc);
} 

STDMETHODIMP_(void)
CPane::Update(void)
{
    UpdateWindow(m_hwnd);
}

/*
 * CPane::AddPoint
 *
 * Purpose:
 *  Adds a point to the point collection. Updates max visible coordinates is required.
 *
 */
STDMETHODIMP_(BOOL)
CPane::AddPoint(CPoint FAR* pPoint)
{
    int nX, nY;
 
    nX = pPoint->get_x();
    nY = pPoint->get_y();
    
    if (nX > m_nMaxX && nX <= m_nWidth)
        m_nMaxX = nX;
    if (nY > m_nMaxY && nY <= m_nHeight)
        m_nMaxY = nY;
        
    return m_pPoints->Add(pPoint);
}

/*
 * CPane::RemovePoint
 *
 * Purpose:
 *  Removes point from point collection. Updates max visible coordinates is required.
 *
 */
STDMETHODIMP_(void)
CPane::RemovePoint(CPoint FAR* pPoint)
{   
    RECT rc;    
    
    // If point was removed from the collection, update max visible X & Y coordinates     
    if (m_pPoints->Remove(pPoint)) 
    {
        SetRect(&rc, 0, 0, m_nWidth, m_nHeight);
        m_pPoints->GetMaxXMaxY(&m_nMaxX, &m_nMaxY, &rc);   
    }
}   
