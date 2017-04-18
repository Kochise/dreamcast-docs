/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1997 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          OleDocVw.cpp
   
   Description:   COleDocumentView implementation.

**************************************************************************/

/**************************************************************************
   #include statements
**************************************************************************/

#include "OleDocVw.h"
#include <windowsx.h>

/**************************************************************************

   COleDocumentView::COleDocumentView()

**************************************************************************/

COleDocumentView::COleDocumentView(COleDocument *pOleDoc)
{
OutputDebugString(TEXT("COleDocumentView's constructor\n"));

m_pInPlaceSite = NULL;
m_pInPlaceFrame = NULL;
m_pInPlaceUIWindow = NULL;
m_hwndView = NULL;
m_fUIActive = FALSE;
m_fInPlaceActive = FALSE;
m_hSharedMenu = NULL;
m_hOleMenu = NULL;

m_pOleDoc = pOleDoc;

CreateViewWindow();
}

/**************************************************************************

   COleDocumentView::~COleDocumentView()

**************************************************************************/

COleDocumentView::~COleDocumentView()
{
OutputDebugString(TEXT("COleDocumentView's destructor\n"));

if(m_pInPlaceFrame)
   m_pInPlaceFrame->Release();

if(m_pInPlaceUIWindow)
   m_pInPlaceUIWindow->Release();

if(m_pInPlaceSite)
   m_pInPlaceSite->Release();
}

///////////////////////////////////////////////////////////////////////////
//
// IUnknown Implementation
//

/**************************************************************************

   COleDocumentView::QueryInterface

**************************************************************************/

STDMETHODIMP COleDocumentView::QueryInterface(  REFIID riid, 
                                                LPVOID *ppReturn)
{
OutputDebugString(TEXT("COleDocumentView::QueryInterface\n"));

return m_pOleDoc->QueryInterface(riid, ppReturn);
}                                             

/**************************************************************************

   COleDocumentView::AddRef

**************************************************************************/

STDMETHODIMP_(DWORD) COleDocumentView::AddRef()
{
OutputDebugString(TEXT("COleDocumentView::AddRef\n"));

return m_pOleDoc->AddRef();
}


/**************************************************************************

   COleDocumentView::Release

**************************************************************************/

STDMETHODIMP_(DWORD) COleDocumentView::Release()
{
OutputDebugString(TEXT("COleDocumentView::Release\n"));

return m_pOleDoc->Release();
}

/**************************************************************************

   COleDocumentView::SetInPlaceSite()
   
**************************************************************************/

STDMETHODIMP COleDocumentView::SetInPlaceSite(IOleInPlaceSite *pNewSite)
{
OutputDebugString(TEXT("COleDocumentView::SetInPlaceSite\n"));

//clean up previous site if it exists
if(m_pInPlaceSite)
   {
   if(m_fUIActive)
      {
      DeactivateUI();
      }
   
   if(m_fInPlaceActive)
      {
      DeactivateInPlace();
      }
   
   if(m_pInPlaceFrame)
      {
      m_pInPlaceFrame->Release();
      m_pInPlaceFrame = NULL;
      }
   
   if(m_pInPlaceUIWindow)
      {
      m_pInPlaceUIWindow->Release();
      m_pInPlaceUIWindow = NULL;
      }
   
   m_pInPlaceSite->Release();
   m_pInPlaceSite = NULL;
   }

m_pInPlaceSite = pNewSite;

if(m_pInPlaceSite)
   {
   m_pInPlaceSite->AddRef();

   RECT  rcClip;

   m_FrameInfo.cb = sizeof(m_FrameInfo);
   
   m_pInPlaceSite->GetWindowContext(   &m_pInPlaceFrame,
                                       &m_pInPlaceUIWindow,
                                       &m_Rect,
                                       &rcClip,
                                       &m_FrameInfo);
   }

return S_OK;
}

/**************************************************************************

   COleDocumentView::GetInPlaceSite()
   
**************************************************************************/

STDMETHODIMP COleDocumentView::GetInPlaceSite(IOleInPlaceSite **ppInPlaceSite)
{
OutputDebugString(TEXT("COleDocumentView::GetInPlaceSite\n"));

HRESULT  hr = E_FAIL;

*ppInPlaceSite = m_pInPlaceSite;

if(*ppInPlaceSite)
   {
   (*ppInPlaceSite)->AddRef();
   hr = S_OK;
   }

return hr;
}

/**************************************************************************

   COleDocumentView::GetDocument()
   
**************************************************************************/

STDMETHODIMP COleDocumentView::GetDocument(IUnknown **ppUnk)
{
OutputDebugString(TEXT("COleDocumentView::GetDocument\n"));

*ppUnk = m_pOleDoc;

if(*ppUnk)
   (*ppUnk)->AddRef();

return S_OK;
}

/**************************************************************************

   COleDocumentView::SetRect()
   
**************************************************************************/

STDMETHODIMP COleDocumentView::SetRect(LPRECT pRect)
{
OutputDebugString(TEXT("COleDocumentView::SetRect - "));

if(!pRect)
   return E_INVALIDARG;

m_Rect = *pRect;

TCHAR szText[MAX_PATH];
wsprintf(szText, TEXT("%d, %d, %d, %d\n"), m_Rect.left, m_Rect.top, m_Rect.right, m_Rect.bottom);
OutputDebugString(szText);

MoveWindow(m_hwndView, m_Rect.left, m_Rect.top, m_Rect.right, m_Rect.bottom, TRUE);

return S_OK;
}

/**************************************************************************

   COleDocumentView::GetRect()
   
**************************************************************************/

STDMETHODIMP COleDocumentView::GetRect(LPRECT pRect)
{
OutputDebugString(TEXT("COleDocumentView::GetRect\n"));

if(!pRect)
   return E_INVALIDARG;

*pRect = m_Rect;

return S_OK;
}

/**************************************************************************

   COleDocumentView::SetRectComplex()
   
**************************************************************************/

STDMETHODIMP COleDocumentView::SetRectComplex(  LPRECT prcView, 
                                                LPRECT prcHScroll, 
                                                LPRECT prcVScroll, 
                                                LPRECT prcSizeBox)
{
OutputDebugString(TEXT("COleDocumentView::SetRectComplex\n"));

return E_NOTIMPL;
}

/**************************************************************************

   COleDocumentView::Show()
   
**************************************************************************/

STDMETHODIMP COleDocumentView::Show(BOOL bShow)
{
OutputDebugString(TEXT("COleDocumentView::Show\n"));

if(bShow)
   {
   //if the object is not in-place active, make it that way
   if(!m_fInPlaceActive)
      ActivateInPlace();

   //show the window
   BringWindowToTop(m_hwndView);
   ShowWindow(m_hwndView, SW_SHOW);
   UpdateWindow(m_hwndView);
   }
else
   {
   //if the object is UI active, make remove that state
   if(m_fUIActive)
      DeactivateUI();

   //hide the window
   ShowWindow(m_hwndView, SW_HIDE);
   }

return S_OK;
}

/**************************************************************************

   COleDocumentView::UIActivate()
   
**************************************************************************/

STDMETHODIMP COleDocumentView::UIActivate(BOOL bActivate)
{
OutputDebugString(TEXT("COleDocumentView::UIActivate\n"));

if(bActivate)
   {
   return ActivateUI();
   }

return DeactivateUI();
}

/**************************************************************************

   COleDocumentView::ActivateUI()
   
**************************************************************************/

STDMETHODIMP COleDocumentView::ActivateUI()
{
OutputDebugString(TEXT("COleDocumentView::ActivateUI\n"));

//set the active object
//either one of these could be good
if(m_pInPlaceFrame)
   {
   m_pInPlaceFrame->SetActiveObject(m_pOleDoc->m_pOleInPlaceActiveObject, NULL);
   }

if(m_pInPlaceUIWindow)
   {
   m_pInPlaceUIWindow->SetActiveObject(m_pOleDoc->m_pOleInPlaceActiveObject, NULL);
   }
      
if(m_pInPlaceSite)
   {
   m_fUIActive = TRUE;

   ActivateInPlace();
      
   m_pInPlaceSite->OnUIActivate();

   MergeMenus();

   SetFocus(m_hwndView);
   }

return S_OK;
}

/**************************************************************************

   COleDocumentView::DeactivateUI()
   
**************************************************************************/

STDMETHODIMP COleDocumentView::DeactivateUI()
{
OutputDebugString(TEXT("COleDocumentView::DeactivateUI\n"));

m_fUIActive = FALSE;
   
RemoveMenus();
      
//remove the active object
//either one of these could be good
if(m_pInPlaceFrame)
   {
   m_pInPlaceFrame->SetActiveObject(NULL, NULL);
   }

if(m_pInPlaceUIWindow)
   {
   m_pInPlaceUIWindow->SetActiveObject(NULL, NULL);
   }

if(m_pInPlaceSite)
   {
   m_pInPlaceSite->OnUIDeactivate(FALSE);
   }

return S_OK;
}

/**************************************************************************

   COleDocumentView::Open()
   
**************************************************************************/

STDMETHODIMP COleDocumentView::Open(void)
{
OutputDebugString(TEXT("COleDocumentView::Open\n"));

return S_OK;
}

/**************************************************************************

   COleDocumentView::CloseView()
   
**************************************************************************/

STDMETHODIMP COleDocumentView::CloseView(DWORD dwReserved)
{
OutputDebugString(TEXT("COleDocumentView::CloseView\n"));

SetInPlaceSite(NULL);

return S_OK;
}

/**************************************************************************

   COleDocumentView::SaveViewState()
   
**************************************************************************/

STDMETHODIMP COleDocumentView::SaveViewState(IStream *pStream)
{
OutputDebugString(TEXT("COleDocumentView::SaveViewState\n"));

return E_NOTIMPL;
}

/**************************************************************************

   COleDocumentView::ApplyViewState()
   
**************************************************************************/

STDMETHODIMP COleDocumentView::ApplyViewState(IStream *pStream)
{
OutputDebugString(TEXT("COleDocumentView::ApplyViewState\n"));

return E_NOTIMPL;
}

/**************************************************************************

   COleDocumentView::Clone()
   
**************************************************************************/

STDMETHODIMP COleDocumentView::Clone(IOleInPlaceSite *pIPSite, IOleDocumentView **ppView)
{
OutputDebugString(TEXT("COleDocumentView::Clone\n"));

*ppView = NULL;

return E_NOTIMPL;
}

/**************************************************************************

   COleDocumentView::ActivateInPlace()
   
**************************************************************************/

STDMETHODIMP COleDocumentView::ActivateInPlace()
{
OutputDebugString(TEXT("COleDocumentView::ActivateInPlace\n"));

m_fInPlaceActive = TRUE;

if(m_pInPlaceSite) 
   {
   // tell the site we are in-place activating
   m_pInPlaceSite->OnInPlaceActivate();

   HWND  hwndParent;
   m_pInPlaceSite->GetWindow(&hwndParent);
   SetParent(m_hwndView, hwndParent);

   //show the view
   Show(TRUE);
   }

return S_OK;
}

/**************************************************************************

   COleDocumentView::DeactivateInPlace()
   
**************************************************************************/

STDMETHODIMP COleDocumentView::DeactivateInPlace()
{
OutputDebugString(TEXT("COleDocumentView::InPlaceDeactivate\n"));

//UI deactivate, if necessary and hide the view window
Show(FALSE);

m_fInPlaceActive = FALSE;

if(m_pInPlaceSite) 
   {
   // tell the site we are in-place deactivating
   m_pInPlaceSite->OnInPlaceDeactivate();
   }

//set the parent to NULL
SetParent(m_hwndView, GetDesktopWindow());

return S_OK;
}

/**************************************************************************

   COleDocumentView::CreateDocWindow()
   
**************************************************************************/

STDMETHODIMP COleDocumentView::CreateViewWindow()
{
OutputDebugString(TEXT("COleDocumentView::CreateViewWindow\n"));

WNDCLASS wc;

//if our window class has not been registered, then do so
if(!GetClassInfo(g_hInst, VIEW_CLASS_NAME, &wc))
   {
   ZeroMemory(&wc, sizeof(wc));
   wc.style          = CS_HREDRAW | CS_VREDRAW;
   wc.lpfnWndProc    = (WNDPROC)ViewWndProc;
   wc.cbClsExtra     = 0;
   wc.cbWndExtra     = 0;
   wc.hInstance      = g_hInst;
   wc.hIcon          = NULL;
   wc.hCursor        = LoadCursor(NULL, IDC_ARROW);
   wc.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
   wc.lpszMenuName   = NULL;
   wc.lpszClassName  = VIEW_CLASS_NAME;
   
   if(!RegisterClass(&wc))
      return E_FAIL;
   }

m_hwndView = CreateWindowEx(  WS_EX_CLIENTEDGE,
                              VIEW_CLASS_NAME,
                              NULL,
                              WS_CHILD | WS_CLIPSIBLINGS,
                              0,
                              0,
                              0,
                              0,
                              GetDesktopWindow(),
                              NULL,
                              g_hInst,
                              (LPVOID)this);
                           
if(!m_hwndView)
   {
   DWORD dwError = GetLastError();
   return E_FAIL;
   }

return S_OK;
}

/**************************************************************************

   COleDocumentView::ViewWndProc()
   
**************************************************************************/

LRESULT CALLBACK COleDocumentView::ViewWndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
COleDocumentView  *pThis = (COleDocumentView*)GetWindowLong(hWnd, GWL_USERDATA);

switch (uMessage)
   {
   case WM_NCCREATE:
      {
      LPCREATESTRUCT lpcs = (LPCREATESTRUCT)lParam;
      pThis = (COleDocumentView*)(lpcs->lpCreateParams);
      SetWindowLong(hWnd, GWL_USERDATA, (LONG)pThis);
      }
      break;

   case WM_CREATE:
      return pThis->OnCreate();
   
   case WM_COMMAND:
      return pThis->OnCommand(   GET_WM_COMMAND_ID(wParam, lParam), 
                                 GET_WM_COMMAND_CMD(wParam, lParam), 
                                 GET_WM_COMMAND_HWND(wParam, lParam));

   case WM_PAINT:
      return pThis->OnPaint();
   
   case WM_INITMENUPOPUP:
      return pThis->UpdateMenu((HMENU)wParam);
   
   }

return DefWindowProc(hWnd, uMessage, wParam, lParam);
}

/**************************************************************************

   COleDocumentView::OnCreate()
   
**************************************************************************/

LRESULT COleDocumentView::OnCreate(void)
{
return 0;
}

/**************************************************************************

   COleDocumentView::OnCommand()
   
**************************************************************************/

LRESULT COleDocumentView::OnCommand(UINT uID, UINT uCmd, HWND hwndCmd)
{
switch(uID)
   {
   case IDM_RED:
      m_pOleDoc->m_Color = RED_COLOR;
      InvalidateRect(m_hwndView, NULL, TRUE);
      UpdateWindow(m_hwndView);
      m_pOleDoc->m_fDirty = TRUE;
      break;

   case IDM_GREEN:
      m_pOleDoc->m_Color = GREEN_COLOR;
      InvalidateRect(m_hwndView, NULL, TRUE);
      UpdateWindow(m_hwndView);
      m_pOleDoc->m_fDirty = TRUE;
      break;

   case IDM_BLUE:
      m_pOleDoc->m_Color = BLUE_COLOR;
      InvalidateRect(m_hwndView, NULL, TRUE);
      UpdateWindow(m_hwndView);
      m_pOleDoc->m_fDirty = TRUE;
      break;

   }

return 0;
}

/**************************************************************************

   COleDocumentView::OnPaint()
   
**************************************************************************/

LRESULT COleDocumentView::OnPaint(void)
{
PAINTSTRUCT ps;

BeginPaint(m_hwndView, &ps);

RECT  rc;
HBRUSH hBrush = CreateSolidBrush(m_pOleDoc->m_Color);
GetClientRect(m_hwndView, &rc);

FillRect(ps.hdc, &rc, hBrush);

DeleteObject(hBrush);

EndPaint(m_hwndView, &ps);

return 0;
}

/**************************************************************************

   COleDocumentView::MergeMenus()
   
**************************************************************************/

BOOL COleDocumentView::MergeMenus(void)
{
if(!m_hSharedMenu)
   {
   //  Create the menu resource
   m_hSharedMenu = CreateMenu();

   ZeroMemory(&m_mgw, sizeof(m_mgw));
   
   // have the contaner insert its menus
   if(SUCCEEDED(m_pInPlaceFrame->InsertMenus(m_hSharedMenu, &m_mgw)))
      {
      int   nFirstGroup = (int) m_mgw.width[0];
      HMENU hMenu,
            hSubMenu;
      TCHAR szText[MAX_PATH];

      hMenu = LoadMenu(g_hInst, MAKEINTRESOURCE(IDR_COLOR_MENU));
      hSubMenu = GetSubMenu(hMenu, 0);

      //get the menu item's text
      GetMenuString(hMenu, 0, szText, ARRAYSIZE(szText), MF_BYPOSITION);
   
      // insert the server menus
      InsertMenu( m_hSharedMenu, 
                  nFirstGroup, 
                  MF_BYPOSITION | MF_POPUP, 
                  (UINT)hSubMenu, 
                  szText);

      //update the OLEMENUGROUPWIDTHS structure
      m_mgw.width[1] += 1;
      m_mgw.width[3] += 0;
      m_mgw.width[5] += 0;
      }
   else
      {
      // Destroy the menu resource
      DestroyMenu(m_hSharedMenu);
      m_hSharedMenu = NULL;
      }
   }

if(!m_hOleMenu)
   {
   // tell OLE to create the menu descriptor
   m_hOleMenu = OleCreateMenuDescriptor(m_hSharedMenu, &m_mgw);
   }

m_pInPlaceFrame->SetMenu(m_hSharedMenu, m_hOleMenu, m_hwndView);

return TRUE;
}

/**************************************************************************

   COleDocumentView::RemoveMenus()
   
**************************************************************************/

BOOL COleDocumentView::RemoveMenus(void)
{
if(m_hSharedMenu)
   {
   int   nFirstGroup = (int) m_mgw.width[0];

   m_pInPlaceFrame->SetMenu(NULL, NULL, NULL);

   // remove the menus that we added
   RemoveMenu(m_hSharedMenu, nFirstGroup, MF_BYPOSITION);

   // have the container remove its menus
   m_pInPlaceFrame->RemoveMenus(m_hSharedMenu);

   // Destroy the menu resource
   DestroyMenu(m_hSharedMenu);

   m_hSharedMenu = NULL;
   }

if(m_hOleMenu)
   {
   // destroy the menu descriptor
   OleDestroyMenuDescriptor(m_hOleMenu);

   m_hOleMenu = NULL;
   }

return TRUE;
}

/**************************************************************************

   COleDocumentView::UpdateMenu()
   
**************************************************************************/

BOOL COleDocumentView::UpdateMenu(HMENU hMenu)
{
UINT  uCheck;

switch(m_pOleDoc->m_Color)
   {
   case RED_COLOR:
      uCheck = IDM_RED;
      break;

   case GREEN_COLOR:
      uCheck = IDM_GREEN;
      break;

   case BLUE_COLOR:
      uCheck = IDM_BLUE;
      break;

   default:
      uCheck = 0;
      break;
   }

return CheckMenuRadioItem( hMenu, 
                           IDM_RED, 
                           IDM_BLUE, 
                           uCheck, 
                           MF_BYCOMMAND);
}

