/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1997 - 1998 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          ExplorerBar.cpp
   
   Description:   Implements CExplorerBar

**************************************************************************/

/**************************************************************************
   #include statements
**************************************************************************/

#include "ExplrBar.h"
#include "Guid.h"

/**************************************************************************

   CExplorerBar::CExplorerBar()

**************************************************************************/

CExplorerBar::CExplorerBar()
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

   CExplorerBar::~CExplorerBar()

**************************************************************************/

CExplorerBar::~CExplorerBar()
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

   CExplorerBar::QueryInterface

**************************************************************************/

STDMETHODIMP CExplorerBar::QueryInterface(REFIID riid, LPVOID *ppReturn)
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

   CExplorerBar::AddRef

**************************************************************************/

STDMETHODIMP_(DWORD) CExplorerBar::AddRef()
{
return ++m_ObjRefCount;
}


/**************************************************************************

   CExplorerBar::Release

**************************************************************************/

STDMETHODIMP_(DWORD) CExplorerBar::Release()
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

   CExplorerBar::GetWindow()
   
**************************************************************************/

STDMETHODIMP CExplorerBar::GetWindow(HWND *phWnd)
{
*phWnd = m_hWnd;

return S_OK;
}

/**************************************************************************

   CExplorerBar::ContextSensitiveHelp()
   
**************************************************************************/

STDMETHODIMP CExplorerBar::ContextSensitiveHelp(BOOL fEnterMode)
{
return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////
//
// IDockingWindow Implementation
//

/**************************************************************************

   CExplorerBar::ShowDW()
   
**************************************************************************/

STDMETHODIMP CExplorerBar::ShowDW(BOOL fShow)
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

   CExplorerBar::CloseDW()
   
**************************************************************************/

STDMETHODIMP CExplorerBar::CloseDW(DWORD dwReserved)
{
ShowDW(FALSE);

if(IsWindow(m_hWnd))
   DestroyWindow(m_hWnd);

m_hWnd = NULL;
   
return S_OK;
}

/**************************************************************************

   CExplorerBar::ResizeBorderDW()
   
**************************************************************************/

STDMETHODIMP CExplorerBar::ResizeBorderDW(   LPCRECT prcBorder, 
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

   CExplorerBar::UIActivateIO()
   
**************************************************************************/

STDMETHODIMP CExplorerBar::UIActivateIO(BOOL fActivate, LPMSG pMsg)
{
if(fActivate)
   SetFocus(m_hWnd);

return S_OK;
}

/**************************************************************************

   CExplorerBar::HasFocusIO()
   
   If this window or one of its decendants has the focus, return S_OK. Return 
   S_FALSE if we don't have the focus.

**************************************************************************/

STDMETHODIMP CExplorerBar::HasFocusIO(void)
{
if(m_bFocus)
   return S_OK;

return S_FALSE;
}

/**************************************************************************

   CExplorerBar::TranslateAcceleratorIO()
   
   If the accelerator is translated, return S_OK or S_FALSE otherwise.

**************************************************************************/

STDMETHODIMP CExplorerBar::TranslateAcceleratorIO(LPMSG pMsg)
{
return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////
//
// IObjectWithSite implementations
//

/**************************************************************************

   CExplorerBar::SetSite()
   
**************************************************************************/

STDMETHODIMP CExplorerBar::SetSite(IUnknown* punkSite)
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

   CExplorerBar::GetSite()
   
**************************************************************************/

STDMETHODIMP CExplorerBar::GetSite(REFIID riid, LPVOID *ppvReturn)
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

   CExplorerBar::GetBandInfo()
   
**************************************************************************/

STDMETHODIMP CExplorerBar::GetBandInfo(DWORD dwBandID, DWORD dwViewMode, DESKBANDINFO* pdbi)
{
if(pdbi)
   {
   m_dwBandID = dwBandID;
   m_dwViewMode = dwViewMode;

   if(pdbi->dwMask & DBIM_MINSIZE)
      {
      pdbi->ptMinSize.x = MIN_SIZE_X;
      pdbi->ptMinSize.y = MIN_SIZE_Y;
      }

   if(pdbi->dwMask & DBIM_MAXSIZE)
      {
      pdbi->ptMaxSize.x = -1;
      pdbi->ptMaxSize.y = -1;
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
      lstrcpyW(pdbi->wszTitle, L"Sample Explorer Bar");
      }

   if(pdbi->dwMask & DBIM_MODEFLAGS)
      {
      pdbi->dwModeFlags = DBIMF_VARIABLEHEIGHT;
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

   CExplorerBar::GetClassID()
   
**************************************************************************/

STDMETHODIMP CExplorerBar::GetClassID(LPCLSID pClassID)
{
*pClassID = CLSID_SampleExplorerBar;

return S_OK;
}

/**************************************************************************

   CExplorerBar::IsDirty()
   
**************************************************************************/

STDMETHODIMP CExplorerBar::IsDirty(void)
{
return S_FALSE;
}

/**************************************************************************

   CExplorerBar::Load()
   
**************************************************************************/

STDMETHODIMP CExplorerBar::Load(LPSTREAM pStream)
{
return S_OK;
}

/**************************************************************************

   CExplorerBar::Save()
   
**************************************************************************/

STDMETHODIMP CExplorerBar::Save(LPSTREAM pStream, BOOL fClearDirty)
{
return S_OK;
}

/**************************************************************************

   CExplorerBar::GetSizeMax()
   
**************************************************************************/

STDMETHODIMP CExplorerBar::GetSizeMax(ULARGE_INTEGER *pul)
{
return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////
//
// IContextMenu Implementation
//

/**************************************************************************

   CExplorerBar::QueryContextMenu()

**************************************************************************/

STDMETHODIMP CExplorerBar::QueryContextMenu( HMENU hMenu,
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
               "&Sample Explorer Bar Command");

   return MAKE_HRESULT(SEVERITY_SUCCESS, 0, USHORT(IDM_COMMAND + 1));
   }

return MAKE_HRESULT(SEVERITY_SUCCESS, 0, USHORT(0));
}

/**************************************************************************

   CExplorerBar::InvokeCommand()

**************************************************************************/

STDMETHODIMP CExplorerBar::InvokeCommand(LPCMINVOKECOMMANDINFO lpcmi)
{
switch (LOWORD(lpcmi->lpVerb))
   {
   case IDM_COMMAND:
      MessageBox(lpcmi->hwnd, TEXT("Explorer Bar Command selected."), TEXT("Sample Explorer Bar"), MB_OK | MB_ICONINFORMATION);
      break;

   default:
      return E_INVALIDARG;
   }

return NOERROR;
}

/**************************************************************************

   CExplorerBar::GetCommandString()

**************************************************************************/

STDMETHODIMP CExplorerBar::GetCommandString( UINT idCommand,
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
            lstrcpy(lpszName, TEXT("Explorer Bar command help text"));
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

   CExplorerBar::WndProc()
   
**************************************************************************/

LRESULT CALLBACK CExplorerBar::WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
CExplorerBar  *pThis = (CExplorerBar*)GetWindowLong(hWnd, GWL_USERDATA);

switch (uMessage)
   {
   case WM_NCCREATE:
      {
      LPCREATESTRUCT lpcs = (LPCREATESTRUCT)lParam;
      pThis = (CExplorerBar*)(lpcs->lpCreateParams);
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

   CExplorerBar::OnPaint()
   
**************************************************************************/

LRESULT CExplorerBar::OnPaint(void)
{
PAINTSTRUCT ps;
RECT        rc;

BeginPaint(m_hWnd, &ps);

GetClientRect(m_hWnd, &rc);
SetTextColor(ps.hdc, RGB(255, 255, 255));
SetBkMode(ps.hdc, TRANSPARENT);
DrawText(ps.hdc, TEXT("Sample Explorer Bar"), -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

EndPaint(m_hWnd, &ps);

return 0;
}

/**************************************************************************

   CExplorerBar::OnCommand()
   
**************************************************************************/

LRESULT CExplorerBar::OnCommand(WPARAM wParam, LPARAM lParam)
{
return 0;
}

/**************************************************************************

   CExplorerBar::FocusChange()
   
**************************************************************************/

void CExplorerBar::FocusChange(BOOL bFocus)
{
m_bFocus = bFocus;

//inform the input object site that the focus has changed
if(m_pSite)
   {
   m_pSite->OnFocusChangeIS((IDockingWindow*)this, bFocus);
   }
}

/**************************************************************************

   CExplorerBar::OnSetFocus()
   
**************************************************************************/

LRESULT CExplorerBar::OnSetFocus(void)
{
FocusChange(TRUE);

return 0;
}

/**************************************************************************

   CExplorerBar::OnKillFocus()
   
**************************************************************************/

LRESULT CExplorerBar::OnKillFocus(void)
{
FocusChange(FALSE);

return 0;
}

/**************************************************************************

   CExplorerBar::RegisterAndCreateWindow()
   
**************************************************************************/

BOOL CExplorerBar::RegisterAndCreateWindow(void)
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
   if(!GetClassInfo(g_hInst, EB_CLASS_NAME, &wc))
      {
      ZeroMemory(&wc, sizeof(wc));
      wc.style          = CS_HREDRAW | CS_VREDRAW | CS_GLOBALCLASS;
      wc.lpfnWndProc    = (WNDPROC)WndProc;
      wc.cbClsExtra     = 0;
      wc.cbWndExtra     = 0;
      wc.hInstance      = g_hInst;
      wc.hIcon          = NULL;
      wc.hCursor        = LoadCursor(NULL, IDC_ARROW);
      wc.hbrBackground  = (HBRUSH)CreateSolidBrush(RGB(0, 0, 192));
      wc.lpszMenuName   = NULL;
      wc.lpszClassName  = EB_CLASS_NAME;
      
      if(!RegisterClass(&wc))
         {
         //If RegisterClass fails, CreateWindow below will fail.
         }
      }

   RECT  rc;

   GetClientRect(m_hwndParent, &rc);

   //Create the window. The WndProc will set m_hWnd.
   CreateWindowEx(   0,
                     EB_CLASS_NAME,
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

