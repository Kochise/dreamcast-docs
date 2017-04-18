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
**  app.cpp
**
**  CApplication implementation
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
 * CApplication::Create
 *
 * Purpose:
 *  Creates an instance of the Application automation object and initializes it.
 *
 * Parameters:       
 *  hinst            HINSTANCE of application.
 *  ppApplication    Returns Application automation object.
 *
 * Return Value:
 *  HRESULT
 *
 */
HRESULT
CApplication::Create(HINSTANCE hinst, CApplication FAR* FAR* ppApplication ) 
{   
    TCHAR ach[STR_LEN];   
    TCHAR achFullName[260];
    HRESULT hr;
    CApplication FAR* pApplication = NULL;  
    HWND hwnd;
     
    *ppApplication = NULL;
    
    // Create application object.
    pApplication = new CApplication();
    if (pApplication == NULL)
    {
        hr = E_OUTOFMEMORY; 
        goto error;
    }
    
    LoadString(hinst, IDS_Name, ach, sizeof(ach));
    hwnd = CreateWindow(TEXT("MainWndClass"), ach,
                       WS_OVERLAPPEDWINDOW,
                       CW_USEDEFAULT, CW_USEDEFAULT,
                       650, 650,
                       NULL, NULL, hinst, NULL);
    if (!hwnd)
    {
       hr = E_OUTOFMEMORY;  
       goto error;
    }  
    pApplication->m_hwnd = hwnd;
    pApplication->m_hinst = hinst;
    
    // Set name and fullname of application.  
    pApplication->m_bstrName = SysAllocString(TO_OLE_STRING(ach));
    if (NULL == pApplication->m_bstrName)
    {
        hr = E_OUTOFMEMORY;    
        goto error;
    } 
    GetModuleFileName(hinst, achFullName, sizeof(achFullName));
    pApplication->m_bstrFullName = SysAllocString(TO_OLE_STRING(achFullName));
    if (NULL == pApplication->m_bstrFullName)
    {
        hr = E_OUTOFMEMORY;    
        goto error;
    }
    // ProgID 
    LoadString(hinst, IDS_ProgID, ach, sizeof(ach));  
    pApplication->m_bstrProgID = SysAllocString(TO_OLE_STRING(ach));
    if (NULL == pApplication->m_bstrProgID)
    {
        hr = E_OUTOFMEMORY;    
        goto error;
    }      
    
    // Load type information for the application object from type library.
    // If required, notify user on failure. 
    hr = LoadTypeInfo(&pApplication->m_ptinfo, IID_IApplication);
    if (FAILED(hr)) 
    {       
        LoadString(hinst, IDS_ErrorLoadingTypeLib, ach, sizeof(ach));
        MessageBox(NULL, ach, FROM_OLE_STRING(pApplication->m_bstrName), MB_OK);
        goto error;
    }
        
    // Create Pane    
    hr = CPane::Create(hwnd, &pApplication->m_pPane);
    if (FAILED(hr))
       goto error;    
    pApplication->m_pPane->AddRef();    

    *ppApplication = pApplication;
    return NOERROR;
    
error:                        
    if (pApplication == NULL)
        return E_OUTOFMEMORY; 
    
    if (pApplication->m_bstrFullName)
        SysFreeString(pApplication->m_bstrFullName);  
    if (pApplication->m_bstrName)
        SysFreeString(pApplication->m_bstrName);
    if (pApplication->m_bstrProgID) 
        SysFreeString(pApplication->m_bstrProgID);                       
    if (pApplication->m_ptinfo)
        pApplication->m_ptinfo->Release();        
    if (pApplication->m_pPane)
        pApplication->m_pPane->Release();
    
    // Set to NULL to prevent destructor from attempting to free again
    pApplication->m_bstrFullName = NULL;
    pApplication->m_bstrName = NULL;
        pApplication->m_bstrProgID = NULL;
    pApplication->m_ptinfo = NULL;
    pApplication->m_pPane = NULL;
    
    delete pApplication;
    return hr;
}

/*
 * CApplication::CApplication
 *
 * Purpose:
 *  Constructor for CApplication object. Initializes members to NULL.
 *
 */
#pragma warning (disable : 4355)
CApplication::CApplication() : m_SupportErrorInfo(this, IID_IApplication)
#pragma warning (default : 4355)
{   
    extern ULONG g_cObj;
     
    m_hwnd = NULL;
    m_bstrFullName = NULL;
    m_bstrName = NULL;
    m_bstrProgID = NULL;
    m_ptinfo = NULL;
    m_pPane = NULL;
    m_cRef = 0;   
    m_bVisible = 0;
    m_bUserClosing = FALSE;
}

/*
 * CApplication::~CApplication
 *
 * Purpose:
 *  Destructor for CApplication object. Frees Application message BSTR and default
 *  IDispatch implementation. Closes the aplication.
 *
 */
CApplication::~CApplication()
{ 
     extern ULONG g_cObj;
     
     if (m_bstrFullName) SysFreeString(m_bstrFullName);
     if (m_bstrName) SysFreeString(m_bstrName);
     if (m_bstrProgID) SysFreeString(m_bstrProgID);          
     if (m_ptinfo) m_ptinfo->Release();  
     if (m_pPane) m_pPane->Release();
     if (!m_bUserClosing && IsWindow(m_hwnd)) DestroyWindow(m_hwnd);     
}

/*
 * CApplication::QueryInterface, AddRef, Release
 *
 * Purpose:
 *  Implements IUnknown::QueryInterface, AddRef, Release
 *
 */
STDMETHODIMP
CApplication::QueryInterface(REFIID iid, void FAR* FAR* ppv) 
{   
    *ppv = NULL;
    
    if (iid == IID_IUnknown || iid == IID_IDispatch || iid == IID_IApplication)
        *ppv = this; 
    else if (iid == IID_ISupportErrorInfo)
        *ppv = &m_SupportErrorInfo;
    else return E_NOINTERFACE; 

    AddRef();
    return NOERROR;    
}


STDMETHODIMP_(ULONG)
CApplication::AddRef(void)
{    
#ifdef _DEBUG  
    TCHAR ach[50];
    wsprintf(ach, TEXT("Ref = %ld, App\r\n"), m_cRef+1); 
    OutputDebugString(ach); 
#endif  

    return ++m_cRef;
}

STDMETHODIMP_(ULONG)
CApplication::Release(void)
{
#ifdef _DEBUG  
    TCHAR ach[50];
    wsprintf(ach, TEXT("Ref = %ld, App\r\n"), m_cRef-1); 
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
 * CApplication::GetTypeInfoCount
 *
 * Purpose:
 *  Implements IDispatch::GetTypeInfoCount.
 *
 */
STDMETHODIMP
CApplication::GetTypeInfoCount(UINT FAR* pctinfo)
{
    *pctinfo = 1;
    return NOERROR;
}

/*
 * CApplication::GetTypeInfo
 *
 * Purpose:
 *  Implements IDispatch::GetTypeInfo. 
 *
 */
STDMETHODIMP
CApplication::GetTypeInfo(
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
 * CApplication::GetIDsOfNames
 *
 * Purpose:
 *  Implements IDispatch::GetIDsOfNames.  The standard implementation, DispGetIDsOfNames,
 *  is used.
 *
 */
STDMETHODIMP 
CApplication::GetIDsOfNames(
      REFIID riid,
      OLECHAR FAR* FAR* rgszNames,
      UINT cNames,
      LCID lcid,
      DISPID FAR* rgdispid)
{
    return DispGetIDsOfNames(m_ptinfo, rgszNames, cNames, rgdispid);
}

/*
 * CApplication::Invoke
 *
 * Purpose:
 *  Implements IDispatch::Invoke.  The standard implementation, DispInvoke,
 *  is used.
 *
 */
STDMETHODIMP
CApplication::Invoke(
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
 * CApplication::get_Application, get_FullName, get_Name, get_Parent, get_Visible, put_Visible, Quit 
 *
 * Purpose:
 *  Implements the standard Application, FullName, Name, Parent & Visible properties
 *  and the Quit method. 
 *
 */
STDMETHODIMP
CApplication::get_Application(IApplication FAR* FAR* ppApplication)
{
    HRESULT hr;
    
    hr = QueryInterface(IID_IDispatch, (void FAR* FAR*)ppApplication); 
    if (FAILED(hr))
        return RaiseException(IDS_Unexpected, IID_IApplication); 
    return NOERROR;
}

STDMETHODIMP
CApplication::get_FullName(BSTR FAR* pbstr)
{
    *pbstr = SysAllocString(m_bstrFullName);   
    return NOERROR;
}

STDMETHODIMP
CApplication::get_Name(BSTR FAR* pbstr)
{
    *pbstr = SysAllocString(m_bstrName); 
    return NOERROR; 
}

STDMETHODIMP
CApplication::get_Parent(IApplication FAR* FAR* ppApplication)      
{
    HRESULT hr;
    
    hr = QueryInterface(IID_IDispatch, (void FAR* FAR*)ppApplication); 
    if (FAILED(hr))
        return RaiseException(IDS_Unexpected, IID_IApplication); 
    return NOERROR;
}

STDMETHODIMP
CApplication::put_Visible(VARIANT_BOOL bVisible)
{
    ShowWindow(bVisible ? SW_SHOW : SW_HIDE);  
    return NOERROR;
} 

STDMETHODIMP
CApplication::get_Visible(VARIANT_BOOL FAR* pbVisible)
{
    *pbVisible = m_bVisible;     
    return NOERROR;
}

STDMETHODIMP
CApplication::Quit()
{
    // CoDisconnectObject has no effect for an inproc server.  So the controller
    // will GP fault if it attempts to access the object (including calling IUnknown::Release())
    // after Quit has been called. For a local server, CoDisconnectObject will disconnect
    // the object from external connections. So the controller will get an RPC error if
    // it access the object after calling Quit. The controller will not GP fault in this case. 
    CoDisconnectObject((LPUNKNOWN)this, 0);  
    PostMessage(m_hwnd, WM_CLOSE, 0, 0L);
    return NOERROR;                                     
} 

/*
 * CApplication::get_Pane
 *
 * Purpose:
 *  Returns pane object.
 *
 */      
STDMETHODIMP
CApplication::get_Pane(IPane FAR* FAR* ppPane)
{
    HRESULT hr;
    
    hr = m_pPane->QueryInterface(IID_IDispatch, (void FAR* FAR*)ppPane); 
    if (FAILED(hr))
        return RaiseException(IDS_Unexpected, IID_IApplication); 
    return NOERROR;
}

/*
 * CApplication::CreateLine
 *
 * Purpose:
 *  Returns a newly created line object with no start or end point.
 *
 */  
STDMETHODIMP
CApplication::CreateLine(ILine FAR* FAR* ppLine)
{
    CLine FAR* pline = NULL;
    HRESULT hr;
    
    // Create new item and QI for IDispatch   
    hr = CLine::Create(&pline);
    if (FAILED(hr)) 
        {hr = RaiseException(IDS_OutOfMemory, IID_IApplication); goto error;} 
              
    hr = pline->QueryInterface(IID_IDispatch, (void FAR* FAR*)ppLine); 
    if (FAILED(hr)) 
        {hr = RaiseException(IDS_Unexpected, IID_IApplication); goto error;}
    return NOERROR;
    
error: 
    if (pline)
        delete pline;       
    return hr;     
}

/*
 * CApplication::CreateLine
 *
 * Purpose:
 *  Returns a newly created point object intialized to (0,0).
 *
 */ 
STDMETHODIMP
CApplication::CreatePoint(IPoint FAR* FAR* ppPoint)
{
    CPoint FAR* ppoint = NULL;
    HRESULT hr;
    
    // Create new item and QI for IDispatch   
    hr = CPoint::Create(&ppoint);
    if (FAILED(hr))
        {hr = RaiseException(IDS_OutOfMemory, IID_IApplication); goto error;}          
        
    hr = ppoint->QueryInterface(IID_IDispatch, (void FAR* FAR*)ppPoint); 
    if (FAILED(hr))
        {hr = RaiseException(IDS_Unexpected, IID_IApplication); goto error;}
    return NOERROR;
    
error: 
    if (ppoint)
        delete ppoint;        
    return hr;     
}   

/* 
 *
 * The following methods are not exposed through Automation
 *
 */

STDMETHODIMP_(void)
CApplication::Draw()
{
   m_pPane->Draw();
}

/*
 * CApplication::OnSize
 *
 * Purpose:
 *  Called when application window receives WM_SIZE.
 *
 */ 
STDMETHODIMP_(void)
CApplication::OnSize(unsigned int nWidth, unsigned int nHeight) 
{
   m_pPane->OnSize(nWidth, nHeight);
} 

STDMETHODIMP_(void)
CApplication::ShowWindow(int nCmdShow)
{   
    // Return if curently hidden and asked to hide or currently visible
    // and asked to show.
    if ((!m_bVisible && nCmdShow == SW_HIDE) || (m_bVisible && nCmdShow != SW_HIDE))
        return; 
    
    m_bVisible = (nCmdShow == SW_HIDE) ? FALSE : TRUE;
    
    // The Automation object shutdown behavior is as follows:
    // 1. If the object application is visible, it shuts down only in response to an
    // explicit user command (File/Exit) or it's programmatic equivalent (for example
    // the Quit method of the Application object).
    // 2. If the object application is not visible, it goes away when it's last
    // object is released.   
    //   
    // CoLockObjectExternal can be used to increment the ref count of the application object
    // when it is visible. This will implement shutdown behavior 1. When the application
    // goes invisible, CoLockObjectExternal is used to decrement the ref count. This will
    // implement shutdown behavior 2.
    
    if (m_bVisible)
        CoLockObjectExternal(this, TRUE /*fLock*/, TRUE/*ignored when fLock==TRUE*/);
    else CoLockObjectExternal(this, FALSE/*fLock*/, TRUE/*fLastLockReleases*/);  
    ::ShowWindow (m_hwnd, nCmdShow);
}

STDMETHODIMP_(void)
CApplication::CreateAndDrawLine()
{   
    LINEINFO lineinfo;
    CLine FAR* pLine = NULL;
    CPoint FAR* pPointStart = NULL;
    CPoint FAR* pPointEnd = NULL; 
    ILines FAR* pLines = NULL; 
    int nRet;     
    HRESULT hr;
                  
    nRet = DialogBoxParam(m_hinst, MAKEINTRESOURCE(IDD_DRAWLINE), m_hwnd, 
                      (DLGPROC)DrawLineDialogFunc, (LPARAM)(LPLINEINFO)&lineinfo);    
    if (nRet != IDOK) 
        return;
    hr = CLine::Create(&pLine);
    if (FAILED(hr))  
        goto error;
    hr = CPoint::Create(&pPointStart);
    if (FAILED(hr)) 
        goto error; 
    hr = CPoint::Create(&pPointEnd);
    if (FAILED(hr))
        goto error;

    pPointStart->put_x(lineinfo.ptStart.x);
    pPointStart->put_y(lineinfo.ptStart.y); 
    pPointEnd->put_x(lineinfo.ptEnd.x);
    pPointEnd->put_y(lineinfo.ptEnd.y);   

    pLine->putref_StartPoint(pPointStart);  
    pLine->putref_EndPoint(pPointEnd);  
    pLine->put_Thickness(lineinfo.nThickness);
    pLine->put_Color(lineinfo.colorref);
    
    hr = m_pPane->get_Lines(&pLines); 
    if (FAILED(hr)) 
        goto error; 
    hr = pLines->Add(pLine); 
    if (FAILED(hr)) 
        goto error;  
    pLines->Release();
    return;

error:
    if (pLine) delete pLine;
    if (pPointStart) delete pPointStart;
    if (pPointEnd) delete pPointEnd; 
    if (pLines) pLines->Release();   
    MessageBox(m_hwnd, TEXT("Cannot create Line"), FROM_OLE_STRING(m_bstrName), MB_OK);
}

STDMETHODIMP_(void)
CApplication::ClearPane()  
{
    m_pPane->Clear();
}  

