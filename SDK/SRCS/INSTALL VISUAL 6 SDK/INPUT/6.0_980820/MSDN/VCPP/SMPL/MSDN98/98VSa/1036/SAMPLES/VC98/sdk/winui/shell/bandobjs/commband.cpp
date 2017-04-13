/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1997 - 1998 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          CommBand.cpp
   
   Description:   Implements CCommBand

**************************************************************************/

/**************************************************************************
   #include statements
**************************************************************************/

#include "CommBand.h"
#include "Guid.h"

/**************************************************************************

   CCommBand::CCommBand()

**************************************************************************/

CCommBand::CCommBand()
{
m_pSite = NULL;

m_hWnd = NULL;
m_hwndParent = NULL;

m_bFocus = FALSE;

m_dwViewMode = 0;
m_dwBandID = 0;

m_ObjRefCount = 1;
g_DllRefCount++;
}

/**************************************************************************

   CCommBand::~CCommBand()

**************************************************************************/

CCommBand::~CCommBand()
{
//this should have been freed in a call to SetSite(NULL), but just to be safe
if(m_pSite)
   {
   m_pSite->Release();
   m_pSite = NULL;
   }

g_DllRefCount--;
}

///////////////////////////////////////////////////////////////////////////
//
// IUnknown Implementation
//

/**************************************************************************

   CCommBand::QueryInterface

**************************************************************************/

STDMETHODIMP CCommBand::QueryInterface(REFIID riid, LPVOID *ppReturn)
{
*ppReturn = NULL;

//IUnknown
if(IsEqualIID(riid, IID_IUnknown))
   {
   *ppReturn = this;
   }

//IOleWindow
else if(IsEqualIID(riid, IID_IOleWindow))
   {
   *ppReturn = (IOleWindow*)this;
   }

//IDockingWindow
else if(IsEqualIID(riid, IID_IDockingWindow))
   {
   *ppReturn = (IDockingWindow*)this;
   }   

//IInputObject
else if(IsEqualIID(riid, IID_IInputObject))
   {
   *ppReturn = (IInputObject*)this;
   }   

//IObjectWithSite
else if(IsEqualIID(riid, IID_IObjectWithSite))
   {
   *ppReturn = (IObjectWithSite*)this;
   }   

//IDeskBand
else if(IsEqualIID(riid, IID_IDeskBand))
   {
   *ppReturn = (IDeskBand*)this;
   }   

//IPersist
else if(IsEqualIID(riid, IID_IPersist))
   {
   *ppReturn = (IPersist*)this;
   }   

//IPersistStream
else if(IsEqualIID(riid, IID_IPersistStream))
   {
   *ppReturn = (IPersistStream*)this;
   }   

//IContextMenu
else if(IsEqualIID(riid, IID_IContextMenu))
   {
   *ppReturn = (IContextMenu*)this;
   }   

if(*ppReturn)
   {
   (*(LPUNKNOWN*)ppReturn)->AddRef();
   return S_OK;
   }

return E_NOINTERFACE;
}                                             

/**************************************************************************

   CCommBand::AddRef

**************************************************************************/

STDMETHODIMP_(DWORD) CCommBand::AddRef()
{
return ++m_ObjRefCount;
}


/**************************************************************************

   CCommBand::Release

**************************************************************************/

STDMETHODIMP_(DWORD) CCommBand::Release()
{
if(--m_ObjRefCount == 0)
   {
   delete this;
   return 0;
   }
   
return m_ObjRefCount;
}

///////////////////////////////////////////////////////////////////////////
//
// IOleWindow Implementation
//

/**************************************************************************

   CCommBand::GetWindow()
   
**************************************************************************/

STDMETHODIMP CCommBand::GetWindow(HWND *phWnd)
{
*phWnd = m_hWnd;

return S_OK;
}

/**************************************************************************

   CCommBand::ContextSensitiveHelp()
   
**************************************************************************/

STDMETHODIMP CCommBand::ContextSensitiveHelp(BOOL fEnterMode)
{
return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////
//
// IDockingWindow Implementation
//

/**************************************************************************

   CCommBand::ShowDW()
   
**************************************************************************/

STDMETHODIMP CCommBand::ShowDW(BOOL fShow)
{
if(m_hWnd)
   {
   if(fShow)
      {
      //show our window
      ShowWindow(m_hWnd, SW_SHOW);
      }
   else
      {
      //hide our window
      ShowWindow(m_hWnd, SW_HIDE);
      }
   }

return S_OK;
}

/**************************************************************************

   CCommBand::CloseDW()
   
**************************************************************************/

STDMETHODIMP CCommBand::CloseDW(DWORD dwReserved)
{
ShowDW(FALSE);

if(IsWindow(m_hWnd))
   DestroyWindow(m_hWnd);

m_hWnd = NULL;
   
return S_OK;
}

/**************************************************************************

   CCommBand::ResizeBorderDW()
   
**************************************************************************/

STDMETHODIMP CCommBand::ResizeBorderDW(   LPCRECT prcBorder, 
                                          IUnknown* punkSite, 
                                          BOOL fReserved)
{
/*
This method is never called for Band Objects.
*/
return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////
//
// IInputObject Implementation
//

/**************************************************************************

   CCommBand::UIActivateIO()
   
**************************************************************************/

STDMETHODIMP CCommBand::UIActivateIO(BOOL fActivate, LPMSG pMsg)
{
if(fActivate)
   SetFocus(m_hWnd);

return S_OK;
}

/**************************************************************************

   CCommBand::HasFocusIO()
   
   If this window or one of its decendants has the focus, return S_OK. Return 
   S_FALSE if we don't have the focus.

**************************************************************************/

STDMETHODIMP CCommBand::HasFocusIO(void)
{
if(m_bFocus)
   return S_OK;

return S_FALSE;
}

/**************************************************************************

   CCommBand::TranslateAcceleratorIO()
   
   If the accelerator is translated, return S_OK or S_FALSE otherwise.

**************************************************************************/

STDMETHODIMP CCommBand::TranslateAcceleratorIO(LPMSG pMsg)
{
return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////
//
// IObjectWithSite implementations
//

/**************************************************************************

   CCommBand::SetSite()
   
**************************************************************************/

STDMETHODIMP CCommBand::SetSite(IUnknown* punkSite)
{
//If a site is being held, release it.
if(m_pSite)
   {
   m_pSite->Release();
   m_pSite = NULL;
   }

//If punkSite is not NULL, a new site is being set.
if(punkSite)
   {
   //Get the parent window.
   IOleWindow  *pOleWindow;

   m_hwndParent = NULL;
   
   if(SUCCEEDED(punkSite->QueryInterface(IID_IOleWindow, (LPVOID*)&pOleWindow)))
      {
      pOleWindow->GetWindow(&m_hwndParent);
      pOleWindow->Release();
      }

   if(!m_hwndParent)
      return E_FAIL;

   if(!RegisterAndCreateWindow())
      return E_FAIL;

   //Get and keep the IInputObjectSite pointer.
   if(SUCCEEDED(punkSite->QueryInterface(IID_IInputObjectSite, (LPVOID*)&m_pSite)))
      {
      return S_OK;
      }
   
   return E_FAIL;
   }

return S_OK;
}

/**************************************************************************

   CCommBand::GetSite()
   
**************************************************************************/

STDMETHODIMP CCommBand::GetSite(REFIID riid, LPVOID *ppvReturn)
{
*ppvReturn = NULL;

if(m_pSite)
   return m_pSite->QueryInterface(riid, ppvReturn);

return E_FAIL;
}

///////////////////////////////////////////////////////////////////////////
//
// IDeskBand implementation
//

/**************************************************************************

   CCommBand::GetBandInfo()
   
**************************************************************************/

STDMETHODIMP CCommBand::GetBandInfo(DWORD dwBandID, DWORD dwViewMode, DESKBANDINFO* pdbi)
{
if(pdbi)
   {
   m_dwBandID = dwBandID;
   m_dwViewMode = dwViewMode;

   if(pdbi->dwMask & DBIM_MINSIZE)
      {
      pdbi->ptMinSize.x = 0;
      pdbi->ptMinSize.y = 30;
      }

   if(pdbi->dwMask & DBIM_MAXSIZE)
      {
      pdbi->ptMaxSize.x = -1;
      pdbi->ptMaxSize.y = 30;
      }

   if(pdbi->dwMask & DBIM_INTEGRAL)
      {
      pdbi->ptIntegral.x = 1;
      pdbi->ptIntegral.y = 1;
      }

   if(pdbi->dwMask & DBIM_ACTUAL)
      {
      pdbi->ptActual.x = 0;
      pdbi->ptActual.y = 0;
      }

   if(pdbi->dwMask & DBIM_TITLE)
      {
      lstrcpyW(pdbi->wszTitle, L"");
      }

   if(pdbi->dwMask & DBIM_MODEFLAGS)
      {
      pdbi->dwModeFlags = DBIMF_NORMAL;
      }
   
   if(pdbi->dwMask & DBIM_BKCOLOR)
      {
      //Use the default background color by removing this flag.
      pdbi->dwMask &= ~DBIM_BKCOLOR;
      }

   return S_OK;
   }

return E_INVALIDARG;
}

///////////////////////////////////////////////////////////////////////////
//
// IPersistStream implementations
// 
// This is only supported to allow the desk band to be dropped on the 
// desktop and to prevent multiple instances of the desk band from showing 
// up in the context menu. This desk band doesn't actually persist any data.
//

/**************************************************************************

   CCommBand::GetClassID()
   
**************************************************************************/

STDMETHODIMP CCommBand::GetClassID(LPCLSID pClassID)
{
*pClassID = CLSID_SampleCommBand;

return S_OK;
}

/**************************************************************************

   CCommBand::IsDirty()
   
**************************************************************************/

STDMETHODIMP CCommBand::IsDirty(void)
{
return S_FALSE;
}

/**************************************************************************

   CCommBand::Load()
   
**************************************************************************/

STDMETHODIMP CCommBand::Load(LPSTREAM pStream)
{
return S_OK;
}

/**************************************************************************

   CCommBand::Save()
   
**************************************************************************/

STDMETHODIMP CCommBand::Save(LPSTREAM pStream, BOOL fClearDirty)
{
return S_OK;
}

/**************************************************************************

   CCommBand::GetSizeMax()
   
**************************************************************************/

STDMETHODIMP CCommBand::GetSizeMax(ULARGE_INTEGER *pul)
{
return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////
//
// IContextMenu Implementation
//

/**************************************************************************

   CCommBand::QueryContextMenu()

**************************************************************************/

STDMETHODIMP CCommBand::QueryContextMenu( HMENU hMenu,
                                          UINT indexMenu,
                                          UINT idCmdFirst,
                                          UINT idCmdLast,
                                          UINT uFlags)
{
if(!(CMF_DEFAULTONLY & uFlags))
   {
   InsertMenu( hMenu, 
               indexMenu, 
               MF_STRING | MF_BYPOSITION, 
               idCmdFirst + IDM_COMMAND, 
               "&Sample Comm Band Command");

   return MAKE_HRESULT(SEVERITY_SUCCESS, 0, USHORT(IDM_COMMAND + 1));
   }

return MAKE_HRESULT(SEVERITY_SUCCESS, 0, USHORT(0));
}

/**************************************************************************

   CCommBand::InvokeCommand()

**************************************************************************/

STDMETHODIMP CCommBand::InvokeCommand(LPCMINVOKECOMMANDINFO lpcmi)
{
switch (LOWORD(lpcmi->lpVerb))
   {
   case IDM_COMMAND:
      MessageBox(lpcmi->hwnd, TEXT("Comm Band Command selected."), TEXT("Sample Comm Band"), MB_OK | MB_ICONINFORMATION);
      break;

   default:
      return E_INVALIDARG;
   }

return NOERROR;
}

/**************************************************************************

   CCommBand::GetCommandString()

**************************************************************************/

STDMETHODIMP CCommBand::GetCommandString( UINT idCommand,
                                          UINT uFlags,
                                          LPUINT lpReserved,
                                          LPSTR lpszName,
                                          UINT uMaxNameLen)
{
HRESULT  hr = E_INVALIDARG;

switch(uFlags)
   {
   case GCS_HELPTEXT:
      switch(idCommand)
         {
         case IDM_COMMAND:
            lstrcpy(lpszName, TEXT("Comm Band command help text"));
            hr = NOERROR;
            break;
         }
      break;
   
   case GCS_VERB:
      switch(idCommand)
         {
         case IDM_COMMAND:
            lstrcpy(lpszName, TEXT("command"));
            hr = NOERROR;
            break;
         }
      break;
   
   case GCS_VALIDATE:
      hr = NOERROR;
      break;
   }

return hr;
}

///////////////////////////////////////////////////////////////////////////
//
// private method implementations
//

/**************************************************************************

   CCommBand::WndProc()
   
**************************************************************************/

LRESULT CALLBACK CCommBand::WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
CCommBand  *pThis = (CCommBand*)GetWindowLong(hWnd, GWL_USERDATA);

switch (uMessage)
   {
   case WM_NCCREATE:
      {
      LPCREATESTRUCT lpcs = (LPCREATESTRUCT)lParam;
      pThis = (CCommBand*)(lpcs->lpCreateParams);
      SetWindowLong(hWnd, GWL_USERDATA, (LONG)pThis);

      //set the window handle
      pThis->m_hWnd = hWnd;
      }
      break;
   
   case WM_PAINT:
      return pThis->OnPaint();
   
   case WM_COMMAND:
      return pThis->OnCommand(wParam, lParam);
   
   case WM_SETFOCUS:
      return pThis->OnSetFocus();

   case WM_KILLFOCUS:
      return pThis->OnKillFocus();
   }

return DefWindowProc(hWnd, uMessage, wParam, lParam);
}

/**************************************************************************

   CCommBand::OnPaint()
   
**************************************************************************/

LRESULT CCommBand::OnPaint(void)
{
PAINTSTRUCT ps;
RECT        rc;

BeginPaint(m_hWnd, &ps);

GetClientRect(m_hWnd, &rc);
SetTextColor(ps.hdc, RGB(0, 0, 0));
SetBkMode(ps.hdc, TRANSPARENT);
DrawText(ps.hdc, TEXT("Sample Comm Band"), -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

EndPaint(m_hWnd, &ps);

return 0;
}

/**************************************************************************

   CCommBand::OnCommand()
   
**************************************************************************/

LRESULT CCommBand::OnCommand(WPARAM wParam, LPARAM lParam)
{
return 0;
}

/**************************************************************************

   CCommBand::FocusChange()
   
**************************************************************************/

void CCommBand::FocusChange(BOOL bFocus)
{
m_bFocus = bFocus;

//inform the input object site that the focus has changed
if(m_pSite)
   {
   m_pSite->OnFocusChangeIS((IDockingWindow*)this, bFocus);
   }
}

/**************************************************************************

   CCommBand::OnSetFocus()
   
**************************************************************************/

LRESULT CCommBand::OnSetFocus(void)
{
FocusChange(TRUE);

return 0;
}

/**************************************************************************

   CCommBand::OnKillFocus()
   
**************************************************************************/

LRESULT CCommBand::OnKillFocus(void)
{
FocusChange(FALSE);

return 0;
}

/**************************************************************************

   CCommBand::RegisterAndCreateWindow()
   
**************************************************************************/

BOOL CCommBand::RegisterAndCreateWindow(void)
{
//If the window doesn't exist yet, create it now.
if(!m_hWnd)
   {
   //Can't create a child window without a parent.
   if(!m_hwndParent)
      {
      return FALSE;
      }

   //If the window class has not been registered, then do so.
   WNDCLASS wc;
   if(!GetClassInfo(g_hInst, CB_CLASS_NAME, &wc))
      {
      ZeroMemory(&wc, sizeof(wc));
      wc.style          = CS_HREDRAW | CS_VREDRAW | CS_GLOBALCLASS;
      wc.lpfnWndProc    = (WNDPROC)WndProc;
      wc.cbClsExtra     = 0;
      wc.cbWndExtra     = 0;
      wc.hInstance      = g_hInst;
      wc.hIcon          = NULL;
      wc.hCursor        = LoadCursor(NULL, IDC_ARROW);
      wc.hbrBackground  = (HBRUSH)CreateSolidBrush(RGB(0, 192, 0));
      wc.lpszMenuName   = NULL;
      wc.lpszClassName  = CB_CLASS_NAME;
      
      if(!RegisterClass(&wc))
         {
         //If RegisterClass fails, CreateWindow below will fail.
         }
      }

   RECT  rc;

   GetClientRect(m_hwndParent, &rc);

   //Create the window. The WndProc will set m_hWnd.
   CreateWindowEx(   0,
                     CB_CLASS_NAME,
                     NULL,
                     WS_CHILD | WS_CLIPSIBLINGS | WS_BORDER,
                     rc.left,
                     rc.top,
                     rc.right - rc.left,
                     rc.bottom - rc.top,
                     m_hwndParent,
                     NULL,
                     g_hInst,
                     (LPVOID)this);
      
   }

return (NULL != m_hWnd);
}

