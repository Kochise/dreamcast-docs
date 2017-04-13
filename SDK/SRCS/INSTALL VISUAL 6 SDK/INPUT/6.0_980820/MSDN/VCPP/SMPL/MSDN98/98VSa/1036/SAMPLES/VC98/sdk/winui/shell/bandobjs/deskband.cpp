/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1997 - 1998 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          DeskBand.cpp
   
   Description:   Implements CDeskBand

**************************************************************************/

/**************************************************************************
   #include statements
**************************************************************************/

#include "DeskBand.h"
#include "Guid.h"

/**************************************************************************

   CDeskBand::CDeskBand()

**************************************************************************/

CDeskBand::CDeskBand()
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

   CDeskBand::~CDeskBand()

**************************************************************************/

CDeskBand::~CDeskBand()
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

   CDeskBand::QueryInterface

**************************************************************************/

STDMETHODIMP CDeskBand::QueryInterface(REFIID riid, LPVOID *ppReturn)
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

   CDeskBand::AddRef

**************************************************************************/

STDMETHODIMP_(DWORD) CDeskBand::AddRef()
{
return ++m_ObjRefCount;
}


/**************************************************************************

   CDeskBand::Release

**************************************************************************/

STDMETHODIMP_(DWORD) CDeskBand::Release()
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

   CDeskBand::GetWindow()
   
**************************************************************************/

STDMETHODIMP CDeskBand::GetWindow(HWND *phWnd)
{
*phWnd = m_hWnd;

return S_OK;
}

/**************************************************************************

   CDeskBand::ContextSensitiveHelp()
   
**************************************************************************/

STDMETHODIMP CDeskBand::ContextSensitiveHelp(BOOL fEnterMode)
{
return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////
//
// IDockingWindow Implementation
//

/**************************************************************************

   CDeskBand::ShowDW()
   
**************************************************************************/

STDMETHODIMP CDeskBand::ShowDW(BOOL fShow)
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

   CDeskBand::CloseDW()
   
**************************************************************************/

STDMETHODIMP CDeskBand::CloseDW(DWORD dwReserved)
{
ShowDW(FALSE);

if(IsWindow(m_hWnd))
   DestroyWindow(m_hWnd);

m_hWnd = NULL;
   
return S_OK;
}

/**************************************************************************

   CDeskBand::ResizeBorderDW()
   
**************************************************************************/

STDMETHODIMP CDeskBand::ResizeBorderDW(   LPCRECT prcBorder, 
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

   CDeskBand::UIActivateIO()
   
**************************************************************************/

STDMETHODIMP CDeskBand::UIActivateIO(BOOL fActivate, LPMSG pMsg)
{
if(fActivate)
   SetFocus(m_hWnd);

return S_OK;
}

/**************************************************************************

   CDeskBand::HasFocusIO()
   
   If this window or one of its decendants has the focus, return S_OK. Return 
   S_FALSE if we don't have the focus.

**************************************************************************/

STDMETHODIMP CDeskBand::HasFocusIO(void)
{
if(m_bFocus)
   return S_OK;

return S_FALSE;
}

/**************************************************************************

   CDeskBand::TranslateAcceleratorIO()
   
   If the accelerator is translated, return S_OK or S_FALSE otherwise.

**************************************************************************/

STDMETHODIMP CDeskBand::TranslateAcceleratorIO(LPMSG pMsg)
{
return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////
//
// IObjectWithSite implementations
//

/**************************************************************************

   CDeskBand::SetSite()
   
**************************************************************************/

STDMETHODIMP CDeskBand::SetSite(IUnknown* punkSite)
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

   CDeskBand::GetSite()
   
**************************************************************************/

STDMETHODIMP CDeskBand::GetSite(REFIID riid, LPVOID *ppvReturn)
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

   CDeskBand::GetBandInfo()
   
**************************************************************************/

STDMETHODIMP CDeskBand::GetBandInfo(DWORD dwBandID, DWORD dwViewMode, DESKBANDINFO* pdbi)
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
      lstrcpyW(pdbi->wszTitle, L"Sample Desk Band");
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

   CDeskBand::GetClassID()
   
**************************************************************************/

STDMETHODIMP CDeskBand::GetClassID(LPCLSID pClassID)
{
*pClassID = CLSID_SampleDeskBand;

return S_OK;
}

/**************************************************************************

   CDeskBand::IsDirty()
   
**************************************************************************/

STDMETHODIMP CDeskBand::IsDirty(void)
{
return S_FALSE;
}

/**************************************************************************

   CDeskBand::Load()
   
**************************************************************************/

STDMETHODIMP CDeskBand::Load(LPSTREAM pStream)
{
return S_OK;
}

/**************************************************************************

   CDeskBand::Save()
   
**************************************************************************/

STDMETHODIMP CDeskBand::Save(LPSTREAM pStream, BOOL fClearDirty)
{
return S_OK;
}

/**************************************************************************

   CDeskBand::GetSizeMax()
   
**************************************************************************/

STDMETHODIMP CDeskBand::GetSizeMax(ULARGE_INTEGER *pul)
{
return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////
//
// IContextMenu Implementation
//

/**************************************************************************

   CDeskBand::QueryContextMenu()

**************************************************************************/

STDMETHODIMP CDeskBand::QueryContextMenu( HMENU hMenu,
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
               "&Sample Desk Band Command");

   return MAKE_HRESULT(SEVERITY_SUCCESS, 0, USHORT(IDM_COMMAND + 1));
   }

return MAKE_HRESULT(SEVERITY_SUCCESS, 0, USHORT(0));
}

/**************************************************************************

   CDeskBand::InvokeCommand()

**************************************************************************/

STDMETHODIMP CDeskBand::InvokeCommand(LPCMINVOKECOMMANDINFO lpcmi)
{
switch (LOWORD(lpcmi->lpVerb))
   {
   case IDM_COMMAND:
      MessageBox(lpcmi->hwnd, TEXT("Desk Band Command selected."), TEXT("Sample Desk Band"), MB_OK | MB_ICONINFORMATION);
      break;

   default:
      return E_INVALIDARG;
   }

return NOERROR;
}

/**************************************************************************

   CDeskBand::GetCommandString()

**************************************************************************/

STDMETHODIMP CDeskBand::GetCommandString( UINT idCommand,
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
            lstrcpy(lpszName, TEXT("Desk Band command help text"));
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

   CDeskBand::WndProc()
   
**************************************************************************/

LRESULT CALLBACK CDeskBand::WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
CDeskBand  *pThis = (CDeskBand*)GetWindowLong(hWnd, GWL_USERDATA);

switch (uMessage)
   {
   case WM_NCCREATE:
      {
      LPCREATESTRUCT lpcs = (LPCREATESTRUCT)lParam;
      pThis = (CDeskBand*)(lpcs->lpCreateParams);
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

   CDeskBand::OnPaint()
   
**************************************************************************/

LRESULT CDeskBand::OnPaint(void)
{
PAINTSTRUCT ps;
RECT        rc;

BeginPaint(m_hWnd, &ps);

GetClientRect(m_hWnd, &rc);
SetTextColor(ps.hdc, RGB(0, 0, 0));
SetBkMode(ps.hdc, TRANSPARENT);
DrawText(ps.hdc, TEXT("Sample Desk Band"), -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

EndPaint(m_hWnd, &ps);

return 0;
}

/**************************************************************************

   CDeskBand::OnCommand()
   
**************************************************************************/

LRESULT CDeskBand::OnCommand(WPARAM wParam, LPARAM lParam)
{
return 0;
}

/**************************************************************************

   CDeskBand::FocusChange()
   
**************************************************************************/

void CDeskBand::FocusChange(BOOL bFocus)
{
m_bFocus = bFocus;

//inform the input object site that the focus has changed
if(m_pSite)
   {
   m_pSite->OnFocusChangeIS((IDockingWindow*)this, bFocus);
   }
}

/**************************************************************************

   CDeskBand::OnSetFocus()
   
**************************************************************************/

LRESULT CDeskBand::OnSetFocus(void)
{
FocusChange(TRUE);

return 0;
}

/**************************************************************************

   CDeskBand::OnKillFocus()
   
**************************************************************************/

LRESULT CDeskBand::OnKillFocus(void)
{
FocusChange(FALSE);

return 0;
}

/**************************************************************************

   CDeskBand::RegisterAndCreateWindow()
   
**************************************************************************/

BOOL CDeskBand::RegisterAndCreateWindow(void)
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
   if(!GetClassInfo(g_hInst, DB_CLASS_NAME, &wc))
      {
      ZeroMemory(&wc, sizeof(wc));
      wc.style          = CS_HREDRAW | CS_VREDRAW | CS_GLOBALCLASS;
      wc.lpfnWndProc    = (WNDPROC)WndProc;
      wc.cbClsExtra     = 0;
      wc.cbWndExtra     = 0;
      wc.hInstance      = g_hInst;
      wc.hIcon          = NULL;
      wc.hCursor        = LoadCursor(NULL, IDC_ARROW);
      wc.hbrBackground  = (HBRUSH)CreateSolidBrush(RGB(192, 0, 0));
      wc.lpszMenuName   = NULL;
      wc.lpszClassName  = DB_CLASS_NAME;
      
      if(!RegisterClass(&wc))
         {
         //If RegisterClass fails, CreateWindow below will fail.
         }
      }

   RECT  rc;

   GetClientRect(m_hwndParent, &rc);

   //Create the window. The WndProc will set m_hWnd.
   CreateWindowEx(   0,
                     DB_CLASS_NAME,
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

