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
**  OLE Automation Hello 2.0 Application.
**
**  hello.cpp
**
**  CHello implementation
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
#include "hello.h"

/*
 * CHello::Create
 *
 * Purpose:
 *  Creates an instance of the Hello Application object and initializes it.
 *
 * Parameters:
 *  hinst      HINSTANCE of application.
 *  lpszHelloMessage Initial Hello message. 
 *  pphello    Returns Hello automation object.
 *
 * Return Value:
 *  HRESULT
 *
 */
HRESULT 
CHello::Create(HINSTANCE hinst, LPTSTR lpszHelloMessage, CHello FAR* FAR* pphello) 
{   
    TCHAR ach[STR_LEN];   
    TCHAR achFullName[260];
    HRESULT hr;
    CHello FAR* phello = NULL;   
    HWND hwnd;
     
    *pphello = NULL;
    
    // Create Hello Application object
    phello = new CHello();
    if (phello == NULL)
        goto error;
   
    // Create Main Window
    hwnd = CreateDialog(hinst, MAKEINTRESOURCE(IDD_MAINWINDOW), NULL, NULL);
    if (!hwnd)
    {
        hr = E_OUTOFMEMORY;    
        goto error;
    }  
     
    phello->m_cRef = 0;
    phello->m_bVisible = FALSE;
    phello->m_hwnd = hwnd;     
    phello->m_hinst = hinst;
    
    // FullName
    GetModuleFileName(hinst, achFullName, sizeof(achFullName)); 
    phello->m_bstrFullName = SysAllocString(TO_OLE_STRING(achFullName));
    if (NULL == phello->m_bstrFullName)
    {
        hr = E_OUTOFMEMORY;    
        goto error;
    }   
    // Name
    LoadString(hinst, IDS_Name, ach, sizeof(ach));  
    phello->m_bstrName = SysAllocString(TO_OLE_STRING(ach));
    if (NULL == phello->m_bstrName)
    {
        hr = E_OUTOFMEMORY;    
        goto error;
    } 
    // ProgID 
    LoadString(hinst, IDS_ProgID, ach, sizeof(ach));  
    phello->m_bstrProgID = SysAllocString(TO_OLE_STRING(ach));
    if (NULL == phello->m_bstrProgID)
    {
        hr = E_OUTOFMEMORY;    
        goto error;
    }   
    // Hello Message
    phello->m_bstrHelloMsg = SysAllocString(TO_OLE_STRING(lpszHelloMessage));
    if (NULL == phello->m_bstrHelloMsg)
    {
        hr = E_OUTOFMEMORY;    
        goto error;
    }
    
    // Load type information from type library. If required, notify user on failure. 
    hr = LoadTypeInfo(&phello->m_ptinfo, IID_IHello);
    if (FAILED(hr)) 
    {
        
        LoadString(hinst, IDS_ErrorLoadingTypeLib, ach, sizeof(ach));
        MessageBox(NULL, ach, FROM_OLE_STRING(phello->m_bstrName), MB_OK);
        goto error;
    }
         
    *pphello = phello;
    return NOERROR;
    
error:                        
    if (phello == NULL) return E_OUTOFMEMORY;    
    if (phello->m_bstrFullName) SysFreeString(phello->m_bstrFullName);  
    if (phello->m_bstrName) SysFreeString(phello->m_bstrName); 
    if (phello->m_bstrProgID) SysFreeString(phello->m_bstrProgID);                     
    if (phello->m_bstrHelloMsg) SysFreeString(phello->m_bstrHelloMsg);      
    if (phello->m_ptinfo) phello->m_ptinfo->Release();
    
    // Set to NULL to prevent destructor from attempting to free again
    phello->m_bstrFullName = NULL;
    phello->m_bstrName = NULL;
    phello->m_bstrProgID = NULL;
    phello->m_bstrHelloMsg = NULL;
    phello->m_ptinfo = NULL;
    
    delete phello;
    return hr;
}

/*
 * CHello::CHello
 *
 * Purpose:
 *  Constructor for CHello object. Initializes members to NULL.
 *
 */
#pragma warning (disable : 4355)
CHello::CHello() : m_SupportErrorInfo(this, IID_IHello)
#pragma warning (default : 4355)
{   
    extern ULONG g_cObj;
     
    m_hwnd = NULL;
    m_bstrFullName = NULL;
    m_bstrName = NULL;
    m_bstrProgID = NULL;
    m_bstrHelloMsg = NULL;
    m_ptinfo = NULL; 
    m_bVisible = 0;
}

/*
 * CHello::~CHello
 *
 * Purpose:
 *  Destructor for CHello object. 
 *
 */
CHello::~CHello()
{ 
     extern ULONG g_cObj;
     
     if (m_bstrFullName) SysFreeString(m_bstrFullName);
     if (m_bstrName) SysFreeString(m_bstrName);
     if (m_bstrProgID) SysFreeString(m_bstrProgID);
     if (m_bstrHelloMsg) SysFreeString(m_bstrHelloMsg);          
     if (m_ptinfo) m_ptinfo->Release();
     if (IsWindow(m_hwnd)) DestroyWindow(m_hwnd);
}

/*
 * CHello::QueryInterface, AddRef, Release
 *
 * Purpose:
 *  Implements IUnknown::QueryInterface, AddRef, Release
 *
 */
STDMETHODIMP
CHello::QueryInterface(REFIID iid, void FAR* FAR* ppv) 
{   
    *ppv = NULL;
    
    if (iid == IID_IUnknown || iid == IID_IDispatch || iid == IID_IHello  ) 
        *ppv = this;   
    else if (iid == IID_ISupportErrorInfo)
        *ppv = &m_SupportErrorInfo;
    else return E_NOINTERFACE; 

    AddRef();
    return NOERROR;    
}


STDMETHODIMP_(ULONG)
CHello::AddRef(void)
{
#ifdef _DEBUG  
    TCHAR ach[50];
    wsprintf(ach, TEXT("AddRef: Ref = %ld, Hello\r\n"), m_cRef+1); 
    OutputDebugString(ach); 
#endif  

    return ++m_cRef;
}

STDMETHODIMP_(ULONG)
CHello::Release(void)
{
#ifdef _DEBUG  
    TCHAR ach[50];
    wsprintf(ach, TEXT("Release: Ref = %ld, Hello\r\n"), m_cRef-1); 
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
 * CHello::GetTypeInfoCount
 *
 * Purpose:
 *  Implements IDispatch::GetTypeInfoCount.
 *
 */
STDMETHODIMP
CHello::GetTypeInfoCount(UINT FAR* pctinfo)
{
    *pctinfo = 1;
    return NOERROR;
}

/*
 * CHello::GetTypeInfo
 *
 * Purpose:
 *  Implements IDispatch::GetTypeInfo. 
 *
 */
STDMETHODIMP
CHello::GetTypeInfo(
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
 * CHello::GetIDsOfNames
 *
 * Purpose:
 *  Implements IDispatch::GetIDsOfNames.  The standard implementation, DispGetIDsOfNames,
 *  is used.
 *
 */
STDMETHODIMP 
CHello::GetIDsOfNames(
      REFIID riid,
      OLECHAR FAR* FAR* rgszNames,
      UINT cNames,
      LCID lcid,
      DISPID FAR* rgdispid)
{
    return DispGetIDsOfNames(m_ptinfo, rgszNames, cNames, rgdispid);
}

/*
 * CHello::Invoke
 *
 * Purpose:
 *  Implements IDispatch::Invoke.  The standard implementation, DispInvoke,
 *  is used.
 *
 */
STDMETHODIMP
CHello::Invoke(
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
 * CHello::put_HelloMessage, get_HelloMessage, SayHello
 *
 * Purpose:
 *  Implements the standard Application, FullName, Name, Parent & Visible properties
 *  and the Quit method. 
 *
 */
STDMETHODIMP 
CHello::get_Application(IHello FAR* FAR* ppHello)
{
    HRESULT hr;
    
    *ppHello = NULL;
    
    hr = QueryInterface(IID_IDispatch, (void FAR* FAR*)ppHello);  
    if (FAILED(hr))
        return RaiseException(IDS_Unexpected, IID_IHello); 
    return hr;
}

STDMETHODIMP
CHello::get_FullName(BSTR FAR* pbstr)
{
    *pbstr = SysAllocString(m_bstrFullName);   
    return NOERROR;
}

STDMETHODIMP
CHello::get_Name(BSTR FAR* pbstr)
{
    *pbstr = SysAllocString(m_bstrName);   
    return NOERROR;
}

STDMETHODIMP
CHello::get_Parent(IHello FAR* FAR* ppHello)
{
    HRESULT hr;
    
    *ppHello = NULL;
    
    hr = QueryInterface(IID_IDispatch, (void FAR* FAR*)ppHello);   
    if (FAILED(hr))
        return RaiseException(IDS_Unexpected, IID_IHello); 
    return NOERROR;
}

STDMETHODIMP
CHello::put_Visible(VARIANT_BOOL bVisible)
{
    ShowWindow(bVisible ? SW_SHOW : SW_HIDE);  
    return NOERROR;
}

STDMETHODIMP
CHello::get_Visible(VARIANT_BOOL FAR* pbool)
{
    *pbool =  m_bVisible;  
    return NOERROR;
}

STDMETHODIMP
CHello::Quit() 
{
    // CoDisconnectObject has no effect for an inproc server.  So the controller
    // will GP fault if it attempts to access the object (including calling IUnknown::Release())
    // after Quit has been called. For a local server, CoDisconnectObject will disconnect
    // the object from external connections. So the controller will get an RPC error if
    // it accesses the object after calling Quit and controller will not GP fault. 
    CoDisconnectObject((LPUNKNOWN)this, 0);  
    PostMessage(m_hwnd, WM_CLOSE, 0, 0L);
    return NOERROR;           
} 

/*
 * CHello::put_HelloMessage, get_HelloMessage, SayHello
 *
 * Purpose:
 *  Implements the HelloMessage property and the SayHello method.
 *
 */    
STDMETHODIMP
CHello::put_HelloMessage(BSTR bstrMessage)
{
    SysReAllocString(&m_bstrHelloMsg, bstrMessage);   
    return NOERROR; 
}

STDMETHODIMP
CHello::get_HelloMessage(BSTR FAR* pbstrMessage)
{   
    *pbstrMessage = SysAllocString(m_bstrHelloMsg);
    return NOERROR; 
}

STDMETHODIMP
CHello::SayHello()
{    
    SetDlgItemText(m_hwnd, IDC_HELLODISPLAY, FROM_OLE_STRING(m_bstrHelloMsg));       
    return NOERROR;
}

STDMETHODIMP_(void)
CHello::ShowWindow(int nCmdShow)
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


/*
 * ISupportErrorInfo implementation
 *
 */
CSupportErrorInfo::CSupportErrorInfo(IUnknown FAR* punkObject, REFIID riid)
{
    m_punkObject = punkObject; 
    m_iid = riid;
}         

STDMETHODIMP
CSupportErrorInfo::QueryInterface(REFIID iid, void FAR* FAR* ppv) 
{   
    return m_punkObject->QueryInterface(iid, ppv);    
}


STDMETHODIMP_(ULONG)
CSupportErrorInfo::AddRef(void)
{
    return m_punkObject->AddRef();
}

STDMETHODIMP_(ULONG)
CSupportErrorInfo::Release(void)
{
    return m_punkObject->Release();
} 

STDMETHODIMP
CSupportErrorInfo::InterfaceSupportsErrorInfo(REFIID riid)  
{
    return (riid == m_iid) ? NOERROR : S_FALSE;
}
