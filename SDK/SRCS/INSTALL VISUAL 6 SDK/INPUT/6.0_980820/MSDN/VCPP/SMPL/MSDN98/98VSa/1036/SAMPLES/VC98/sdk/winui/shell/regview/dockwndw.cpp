/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1997 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          DockWndw.cpp
   
   Description:   Implements CDockingWindow

**************************************************************************/

/**************************************************************************
   #include statements
**************************************************************************/

#include "DockWndw.h"

#if (_WIN32_IE >= 0x0400)

/**************************************************************************

   CDockingWindow::CDockingWindow()

**************************************************************************/

CDockingWindow::CDockingWindow(CShellView *pView, HWND hwndCommand)
{
m_pView = pView;
if(m_pView)
   {
   m_pView->AddRef();
   }
else
   {
   delete this;
   return;
   }

m_pSite = NULL;

m_hWnd = NULL;

m_hwndCommand = hwndCommand;

m_bFocus = FALSE;

m_rcDisplay.left = 0;
m_rcDisplay.top = 0;
m_rcDisplay.right = 0;
m_rcDisplay.bottom = 0;

m_ObjRefCount = 1;
g_DllRefCount++;
}

/**************************************************************************

   CDockingWindow::~CDockingWindow()

**************************************************************************/

CDockingWindow::~CDockingWindow()
{
if(m_pView)
   {
   m_pView->Release();
   }

g_DllRefCount--;
}

///////////////////////////////////////////////////////////////////////////
//
// IUnknown Implementation
//

/**************************************************************************

   CDockingWindow::QueryInterface

**************************************************************************/

STDMETHODIMP CDockingWindow::QueryInterface(REFIID riid, LPVOID *ppReturn)
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

if(*ppReturn)
   {
   (*(LPUNKNOWN*)ppReturn)->AddRef();
   return S_OK;
   }

return E_NOINTERFACE;
}                                             

/**************************************************************************

   CDockingWindow::AddRef

**************************************************************************/

STDMETHODIMP_(DWORD) CDockingWindow::AddRef()
{
return ++m_ObjRefCount;
}


/**************************************************************************

   CDockingWindow::Release

**************************************************************************/

STDMETHODIMP_(DWORD) CDockingWindow::Release()
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

   CDockingWindow::GetWindow()
   
**************************************************************************/

STDMETHODIMP CDockingWindow::GetWindow(HWND *phWnd)
{
*phWnd = m_hWnd;

return S_OK;
}

/**************************************************************************

   CDockingWindow::ContextSensitiveHelp()
   
**************************************************************************/

STDMETHODIMP CDockingWindow::ContextSensitiveHelp(BOOL fEnterMode)
{
return E_NOTIMPL;
}

///////////////////////////////////////////////////////////////////////////
//
// IDockingWindow Implementation
//

/**************************************************************************

   CDockingWindow::ShowDW()
   
**************************************************************************/

STDMETHODIMP CDockingWindow::ShowDW(BOOL fShow)
{
//if our window doesn't exist yet, create it now
if(!m_hWnd && m_pSite)
   {
   HRESULT  hr;

   //if our window class has not been registered, then do so
   WNDCLASS wc;
   if(!GetClassInfo(g_hInst, SHTB_CLASS_NAME, &wc))
      {
      ZeroMemory(&wc, sizeof(wc));
      wc.style          = CS_HREDRAW | CS_VREDRAW;
      wc.lpfnWndProc    = (WNDPROC)WndProc;
      wc.cbClsExtra     = 0;
      wc.cbWndExtra     = 0;
      wc.hInstance      = g_hInst;
      wc.hIcon          = NULL;
      wc.hCursor        = LoadCursor(NULL, IDC_ARROW);
      wc.hbrBackground  = (HBRUSH)CreateSolidBrush(RGB(192, 0, 0));
      wc.lpszMenuName   = NULL;
      wc.lpszClassName  = SHTB_CLASS_NAME;
      
      if(!RegisterClass(&wc))
         {
         //if this fails, CreateWindow will fail, so don't sweat it
         }
      }

   //get our parent window
   hr = m_pSite->GetWindow(&m_hwndParent);
   if(SUCCEEDED(hr))
      {
      RECT  rc;

      GetClientRect(m_hwndParent, &rc);

      //create the window - use zero for pos and size - it will get positioned and sized below
      CreateWindowEx(   WS_EX_CLIENTEDGE,
                        SHTB_CLASS_NAME,
                        NULL,
                        WS_CHILD | WS_CLIPSIBLINGS,
                        0,
                        0,
                        0,
                        0,
                        m_hwndParent,
                        NULL,
                        g_hInst,
                        (LPVOID)this);
      
      if(!m_hWnd)
         return E_FAIL;
      
      NegotiateBorderSpace(m_pSite);
      }
   }

if(m_hWnd && m_pSite)
   {
   BORDERWIDTHS   bwRequest = {0, 0, 0, 0};

   if(fShow)
      {
      //position the window - m_rcDisplay was set up in NegotiateBorderSpace
      MoveWindow( m_hWnd,
                  m_rcDisplay.left,
                  m_rcDisplay.top,
                  m_rcDisplay.right,
                  m_rcDisplay.bottom,
                  TRUE);
   
      //show our window
      ShowWindow(m_hWnd, SW_SHOW);
      }
   else
      {
      //hide our window
      ShowWindow(m_hWnd, SW_HIDE);

      //release our border space - bwRequest was initialized above
      m_pSite->SetBorderSpaceDW((IDockingWindow*)this, &bwRequest);
      }
   }

return S_OK;
}

/**************************************************************************

   CDockingWindow::CloseDW()
   
**************************************************************************/

STDMETHODIMP CDockingWindow::CloseDW(DWORD dwReserved)
{
if(m_pSite)
   {
   ShowDW(FALSE);

   if(IsWindow(m_hWnd))
      DestroyWindow(m_hWnd);
   
   m_pSite->Release();
   m_pSite = NULL;
   }

return S_OK;
}

/**************************************************************************

   CDockingWindow::ResizeBorderDW()
   
**************************************************************************/

STDMETHODIMP CDockingWindow::ResizeBorderDW(LPCRECT prcBorder, IUnknown* punkSite, BOOL fReserved)
{
IDockingWindowSite   *pSite = NULL;

//if punkSite is not NULL, use it to negotiate our border space
if(punkSite)
   {
   if(FAILED(punkSite->QueryInterface(IID_IDockingWindowSite, (LPVOID*)&pSite)))
      {
      return E_FAIL;
      }
   }
else if(m_pSite)
   {
   pSite = m_pSite;
   pSite->AddRef();
   }

if(pSite)
   {
   HRESULT  hr = E_FAIL;

   if(NegotiateBorderSpace(pSite, prcBorder))
      {
      //updated our window's position
      ShowDW(TRUE);
      hr = S_OK;
      }
   
   pSite->Release();
   return hr;
   }
return E_FAIL;
}

///////////////////////////////////////////////////////////////////////////
//
// IInputObject Implementation
//

/**************************************************************************

   CDockingWindow::UIActivateIO()
   
**************************************************************************/

STDMETHODIMP CDockingWindow::UIActivateIO(BOOL fActivate, LPMSG pMsg)
{
if(fActivate)
   SetFocus(m_hWnd);

return S_OK;
}

/**************************************************************************

   CDockingWindow::HasFocusIO()
   
   If this window or one of its decendants has the focus, return S_OK. Return 
   S_FALSE if we don't have the focus.

**************************************************************************/

STDMETHODIMP CDockingWindow::HasFocusIO(void)
{
if(m_bFocus)
   return S_OK;

return S_FALSE;
}

/**************************************************************************

   CDockingWindow::TranslateAcceleratorIO()
   
   If the accelerator is translated, return S_OK or S_FALSE otherwise.

**************************************************************************/

STDMETHODIMP CDockingWindow::TranslateAcceleratorIO(LPMSG pMsg)
{
return S_FALSE;
}

///////////////////////////////////////////////////////////////////////////
//
// IObjectWithSite implementations
//

/**************************************************************************

   CDockingWindow::SetSite()
   
**************************************************************************/

STDMETHODIMP CDockingWindow::SetSite(IUnknown* punkSite)
{
if(m_pSite)
   {
   m_pSite->Release();
   m_pSite = NULL;
   }

//If punkSite is not NULL, we are connecting to the site.
if(punkSite)
   {
   if(SUCCEEDED(punkSite->QueryInterface(IID_IDockingWindowSite, (LPVOID*)&m_pSite)))
      {
      return S_OK;
      }
   }

return S_OK;
}

/**************************************************************************

   CDockingWindow::GetSite()
   
**************************************************************************/

STDMETHODIMP CDockingWindow::GetSite(REFIID riid, LPVOID *ppvReturn)
{
*ppvReturn = NULL;

if(m_pSite)
   return m_pSite->QueryInterface(riid, ppvReturn);

return E_FAIL;
}

///////////////////////////////////////////////////////////////////////////
//
// private method implementations
//

/**************************************************************************

   CDockingWindow::WndProc()
   
**************************************************************************/

LRESULT CALLBACK CDockingWindow::WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
CDockingWindow  *pThis = (CDockingWindow*)GetWindowLong(hWnd, GWL_USERDATA);

switch (uMessage)
   {
   case WM_NCCREATE:
      {
      LPCREATESTRUCT lpcs = (LPCREATESTRUCT)lParam;
      pThis = (CDockingWindow*)(lpcs->lpCreateParams);
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

   CDockingWindow::OnPaint()
   
**************************************************************************/

LRESULT CDockingWindow::OnPaint(void)
{
PAINTSTRUCT ps;
RECT        rc;

BeginPaint(m_hWnd, &ps);

GetClientRect(m_hWnd, &rc);
SetTextColor(ps.hdc, RGB(0, 0, 0));
SetBkMode(ps.hdc, TRANSPARENT);
DrawText(ps.hdc, TEXT("IDockingWindow"), -1, &rc, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
EndPaint(m_hWnd, &ps);

return 0;
}

/**************************************************************************

   CDockingWindow::OnCommand()
   
**************************************************************************/

LRESULT CDockingWindow::OnCommand(WPARAM wParam, LPARAM lParam)
{
/*
Since this is a toolbar object, we need to forward all WM_COMMAND messages to 
our assigned command window.
*/
return SendMessage(m_hwndCommand, WM_COMMAND, wParam, lParam);
}

/**************************************************************************

   CDockingWindow::FocusChange()
   
**************************************************************************/

void CDockingWindow::FocusChange(BOOL bFocus)
{
m_bFocus = bFocus;

//inform the input object site that the focus has changed
IInputObjectSite  *pios;

if(SUCCEEDED(m_pSite->QueryInterface(IID_IInputObjectSite, (LPVOID*)&pios)))
   {
   pios->OnFocusChangeIS((IDockingWindow*)this, bFocus);
   pios->Release();
   }
}

/**************************************************************************

   CDockingWindow::OnSetFocus()
   
**************************************************************************/

LRESULT CDockingWindow::OnSetFocus(void)
{
FocusChange(TRUE);

m_pView->OnActivate(SVUIA_ACTIVATE_FOCUS);

return 0;
}

/**************************************************************************

   CDockingWindow::OnKillFocus()
   
**************************************************************************/

LRESULT CDockingWindow::OnKillFocus(void)
{
FocusChange(FALSE);

m_pView->OnDeactivate();

return 0;
}

/**************************************************************************

   CDockingWindow::NegotiateBorderSpace()
   
**************************************************************************/

BOOL CDockingWindow::NegotiateBorderSpace(IDockingWindowSite *pSite, LPCRECT prcBorder)
{
HRESULT        hr;
BORDERWIDTHS   bwRequest = {0, 0, 0, 0};

bwRequest.top = TOOLBAR_HEIGHT;

hr = pSite->RequestBorderSpaceDW((IDockingWindow*)this, &bwRequest);
if(SUCCEEDED(hr))
   {
   hr = pSite->SetBorderSpaceDW((IDockingWindow*)this, &bwRequest);
   if(SUCCEEDED(hr))
      {
      RECT  rcTemp;

      if(!prcBorder)
         {
         hr = pSite->GetBorderDW((IDockingWindow*)this, &rcTemp);
         if(SUCCEEDED(hr))
            {
            prcBorder = &rcTemp;
            }
         }
         
      if(prcBorder)
         {
         //set up our display rectangle
         m_rcDisplay.left = prcBorder->left;
         m_rcDisplay.top = prcBorder->top;
         m_rcDisplay.right = prcBorder->right - prcBorder->left;
         m_rcDisplay.bottom = bwRequest.top;
         
         return TRUE;
         }
      }
   }

return FALSE;
}


#endif   //(_WIN32_IE >= 0x0400)