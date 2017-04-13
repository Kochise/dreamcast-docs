/*+==========================================================================
  File:      GUIDRAW.CPP

  Summary:   Implementation file for the CGuiDraw C++ class. A GuiDraw is
             a C++ object that is anchored to the Windows GUI (Graphical
             User Interface) environment--it retains knowledge of window
             handles and device contexts in the current application. This
             GuiDraw object relies on a drawing object for storage of the
             drawing data. This drawing page object (a CODrawPage object)
             is instantiated as a COM object in a separate In-process
             server, PERDRAW.

             For a comprehensive tutorial code tour of GUIDRAW's contents
             and offerings see the tutorial PERCLIEN.HTM file. For more
             specific technical details on the internal workings see the
             comments dispersed throughout the GUIDRAW source code.

  Classes:   CGuiDraw.

  Origin:    5-20-97: atrent - Editor inheritance from GUIPAPER.CPP in the
             STOCLIEN source.

----------------------------------------------------------------------------
  This file is part of the Microsoft COM Tutorial Code Samples.

  Copyright (C) Microsoft Corporation, 1997.  All rights reserved.

  This source code is intended only as a supplement to Microsoft
  Development Tools and/or on-line documentation.  See these other
  materials for detailed information regarding Microsoft code samples.

  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
  PARTICULAR PURPOSE.
==========================================================================+*/

/*--------------------------------------------------------------------------
  We include WINDOWS.H for all Win32 applications.
  We include OLE2.H because we will be calling the COM/OLE Libraries.
  We include OLECTL.H because it has definitions for connectable objects.
  We include COMMDLG.H because we will be using the Open File,
    Choose Color, and potentially other Common dialogs.
  We include APPUTIL.H because we will be building this application using
    the convenient Virtual Window and Dialog classes and other
    utility functions in the APPUTIL Library (ie, APPUTIL.LIB).
  We include IPAGES.H and PAGEGUID.H for the common drawing-related
    Interface class, GUID, and CLSID specifications.
  We include RESDEF.H because it has the resource definitions specific
    to this application.
  We include GUIDRAW.H because it has the C++ class used for GUI display
    of the drawing page.
  We include DRAWSINK.H because it has the C++ class used for the sink that
    receives event notifications from the CODrawPage object in the server.
---------------------------------------------------------------------------*/
#include <windows.h>
#include <ole2.h>
#include <olectl.h>
#include <apputil.h>
#include <ipages.h>
#include <pageguid.h>
#include "resdef.h"
#include "guidraw.h"
#include "drawsink.h"


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiDraw::CGuiDraw

  Summary:  Constructor.

  Args:     void

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CGuiDraw::CGuiDraw(HINSTANCE hInst, HWND hWndApp, INT iPage)
{
  m_hInst           = hInst;
  m_hWndApp         = hWndApp;
  m_iPage           = iPage;
  m_hWnd            = NULL;
  m_wszDataName[0]  = 0;
  m_pIStorage_Root  = NULL;
  m_pIStorage_Page  = NULL;
  m_pIDrawPage      = NULL;
  m_hDC             = NULL;
  m_hPen            = NULL;
  m_nInkWidth       = INK_THIN;
  m_crInkColor      = RGB(0,0,0);
  m_bInkSaving      = FALSE;
  m_bInking         = FALSE;
  m_bPainting       = FALSE;
  m_OldPos.x        = 0;
  m_OldPos.y        = 0;
  m_pCODrawPageSink = NULL;
  m_dwDrawPageSink  = 0;

  // Save the ClassID of DrawPages using an overloaded '=' operator.
  m_CidDrawPage = CLSID_DrawPage;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiDraw::~CGuiDraw

  Summary:  Destructor.

  Args:     void

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CGuiDraw::~CGuiDraw(void)
{
  // CGuiDraw is derived from CVirWindow which traps the WM_DESTROY
  // message and causes a delete of CGuiDraw which in turn causes this
  // destructor to run. The WM_DESTROY results when the window is destoyed
  // after a close of the window.

  // Just to make sure, turn off Ink Saving.
  m_bInkSaving = FALSE;

  // Disconnect the Sink in the client from the connection points in
  // the server.
  DisconnectSink();

  // Delete the Pen object.
  if (m_hPen)
    DeleteObject(m_hPen);

  // Release the interface held on the DrawPageSink object.
  RELEASE_INTERFACE(m_pCODrawPageSink);

  // Destroy the existing CODrawPage by releasing the IDrawPage interface.
  RELEASE_INTERFACE(m_pIDrawPage);

  // Release the interface held on the page's storage.
  RELEASE_INTERFACE(m_pIStorage_Page);

  // Release the interface held on the root storage.
  RELEASE_INTERFACE(m_pIStorage_Root);

  // Tell main app that this text page is gone.
  PostMessage(m_hWndApp, WM_USER_PAGECLOSED, 0, m_iPage);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiDraw::Load

  Summary:  Load DrawPage data from the appropriate substorage under
            the root storage. If there is no existing substorage then
            create and initialize a new one.

  Args:     void.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiDraw::Load(void)
{
  HRESULT hr = E_FAIL;
  IPersistStorage* pIPersistStorage;

  // Can't do anything without a root storage.
  if (NULL != m_pIStorage_Root)
  {
    // Use the root IStorage to open the nested substorage for this
    // particular DrawPage. Load the drawing data from the substorage.
    // This load internally uses the IPersistStorage features in a
    // created CODrawPage object to reconstitute the object from
    // persistent storage. CODrawPage handles its own persistence that
    // is client-controlled via its exposed IPersistStorage interface.

    // Open the single storage named by m_wszDataName. It is under
    // the root storage. The client here is in charge of the underlying
    // storage that the client asks CODrawPage to use.
    hr = m_pIStorage_Root->OpenStorage(
           m_wszDataName,
           NULL,
           STGM_READWRITE | STGM_DIRECT | STGM_SHARE_EXCLUSIVE,
           NULL,
           0,
           &m_pIStorage_Page);
    if (SUCCEEDED(hr))
    {
      // If the storage already exists, read the ClassID for the class of
      // component objects that can deal with DrawPage data.
      hr = ReadClassStg(m_pIStorage_Page, &m_CidDrawPage);
      if (SUCCEEDED(hr))
      {
        // Now use the obtained Class ID to create a CODrawPage
        // object. Initially ask for the IDrawPage interface.
        hr = CoCreateInstance(
               m_CidDrawPage,
               NULL,
               CLSCTX_INPROC_SERVER,
               IID_IDrawPage,
               (PPVOID)&m_pIDrawPage);
        if (SUCCEEDED(hr))
        {
          // We have a new CODrawPage object. Now obtain the
          // IPersistStorage interface on it. At this point in the
          // client we are assuming that CODrawPage objects use only
          // the IPersistStorage interface for their persistence.
          hr = m_pIDrawPage->QueryInterface(
                 IID_IPersistStorage,
                 (PPVOID)&pIPersistStorage);
          if (SUCCEEDED(hr))
          {
            // And as expected by this client, CODrawPage exposes
            // the IPersistStorage interface. Now use this interface
            // to ask the CODrawPage object to load the drawing data.
            hr = pIPersistStorage->Load(m_pIStorage_Page);

            // Done with IPersistStorage for now so release it.
            pIPersistStorage->Release();
          }
        }
      }
    }
    else
    {
      // If there was no existing page substorage then create a new one.
      hr = m_pIStorage_Root->CreateStorage(
             m_wszDataName,
             STGM_CREATE | STGM_READWRITE | STGM_DIRECT | STGM_SHARE_EXCLUSIVE,
             0,
             0,
             &m_pIStorage_Page);
      if (SUCCEEDED(hr))
      {
        // Write the ClassID of the CODrawPage component object class.
        hr = WriteClassStg(m_pIStorage_Page, m_CidDrawPage);
        if (SUCCEEDED(hr))
        {
          // Now use the Class ID to create a CODrawPage
          // object. Initially ask for the IDrawPage interface.
          hr = CoCreateInstance(
                 m_CidDrawPage,
                 NULL,
                 CLSCTX_INPROC_SERVER,
                 IID_IDrawPage,
                 (PPVOID)&m_pIDrawPage);
          if (SUCCEEDED(hr))
          {
            // We have a new CODrawPage object. Now obtain the
            // IPersistStorage interface on it. At this point in the
            // client we are assuming that CODrawPage objects use only
            // the IPersistStorage interface for their persistence.
            hr = m_pIDrawPage->QueryInterface(
                   IID_IPersistStorage,
                   (PPVOID)&pIPersistStorage);
            if (SUCCEEDED(hr))
            {
              // And as expected by this client, CODrawPage supports
              // the IPersistStorage interface. Now use this interface
              // to ask the CODrawPage object to initialize a new empty
              // drawing page and save it into the substorage.
              hr = pIPersistStorage->InitNew(m_pIStorage_Page);

              // Done with IPersistStorage for now so release it.
              pIPersistStorage->Release();
            }
          }
        }

        if (FAILED(hr))
          m_pIStorage_Page->DestroyElement(m_wszDataName);
      }
    }
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiDraw::OpenWin

  Summary:  Get CGuiDraw started. Make any subordinate objects, like
            CODrawPage and get them started. Create the window. Read the
            page's drawing data from the specified root storage using the
            specified substorage name.

  Args:     IStorage* pIStorage_Root,
              Root storage of the compound file containing the drawing
              page.
            WCHAR* pwszPageTitle,
              The user-displayable title for the drawing page. Generally
              used in the window's title bar.
            WCHAR* pwszDataName)
              The internal storage name of the substorage holding the
              drawing page.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiDraw::OpenWin(
          IStorage* pIStorage_Root,
          WCHAR* pwszPageTitle,
          WCHAR* pwszDataName)
{
  HRESULT hr = E_FAIL;
  HWND hWnd = NULL;
  CODrawPageSink* pCobSink = NULL;
  HCURSOR hCurPrev;
  HCURSOR hCurWait = LoadCursor(NULL, IDC_WAIT);
  TCHAR szTitle[32+PAGE_TITLE_SIZE];

  if (m_hInst && m_hWndApp && pwszDataName)
  {
    // Change cursor to the hour glass. This open could take awhile.
    hCurPrev = SetCursor(hCurWait);

    // Set title string empty to start.
    szTitle[0] = 0;

    lstrcpy(szTitle, TEXT(DRAW_WINDOW_NAME_STR));
#if defined(UNICODE)
    if (NULL != pwszPageTitle)
      lstrcat(szTitle, pwszPageTitle);
    lstrcpy(m_wszDataName, pwszDataName);
#else
    {
      CHAR szAnsi[PAGE_TITLE_SIZE];

      // Convert PageTitle from Unicode to Ansi.
      if (NULL != pwszPageTitle)
      {
        UcToAnsi(pwszPageTitle, szAnsi, PAGE_TITLE_SIZE);
        lstrcat(szTitle, szAnsi);
      }
      // Copy/save DataName.
      memcpy(m_wszDataName, pwszDataName, PAGE_NAME_SIZE*sizeof(WCHAR));
    }
#endif
    // Create the main GuiDraw Window. Size the window reasonably. The
    // Create method sets both m_hInst and m_hWnd.
    hWnd = Create(
             TEXT(DRAW_WINDOW_CLASS_NAME_STR),
             szTitle,
             WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX
               | WS_MAXIMIZEBOX | WS_THICKFRAME,
             CW_USEDEFAULT,
             CW_USEDEFAULT,
             ::GetSystemMetrics(SM_CXSCREEN)*1/3,
             ::GetSystemMetrics(SM_CYSCREEN)*1/3,
             m_hWndApp,
             NULL,
             m_hInst);
    if (NULL != hWnd)
    {
      // Get and save our private display Device Context.
      m_hDC = GetDC(hWnd);

      // Save an interface pointer to the root IStorage and AddRef it.
      m_pIStorage_Root = pIStorage_Root;
      m_pIStorage_Root->AddRef();

      // Now use CGuiDraw::Load to load the drawing window from the named
      // substorage under the root storage. This either opens and loads
      // the existing substorage or creates a new one.
      hr = Load();
      if (SUCCEEDED(hr))
      {
        // We loaded or created the Drawing Page storage and have a
        // CODrawPage component to manage the loaded drawing data.

        // Create the CODrawPageSink object to receive DrawPage events.
        pCobSink = new CODrawPageSink(NULL, this);
        if (NULL != pCobSink)
        {
          // Save a pointer to the CODrawPageSink IUnknown interface.
          // AddRef because of this saved copy. Released in destructor.
          m_pCODrawPageSink = pCobSink;
          m_pCODrawPageSink->AddRef();

          // If we created and reconstituted a CODrawPage object from a
          // persistent storage, then connect the sinks in the client
          // to the connection sources in the server.
          hr = ConnectSink();

          // Ensure the new window is shown on screen.
          ::ShowWindow(m_hWnd, SW_SHOWNORMAL);
          ::UpdateWindow(m_hWnd);
        }
        else
          hr = E_OUTOFMEMORY;
      }

      if (SUCCEEDED(hr))
      {
        // We can now allow ink saving as well.
        m_bInkSaving = TRUE;
      }
      else
      {
        // If can't open, display an error dialog and close this window.
        HrMsgId(m_hInst, m_hWnd, IDS_OPENDRAWPAGE, hr);
        PostMessage(m_hWnd, WM_CLOSE, 0, 0);
      }
    }

    // Set Cursor from hourglass back to what it was.
    SetCursor(hCurPrev);
  }

  return (hr);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiDraw::TopWin

  Summary:  Bring this GuiDraw window to the top over any other windows
            that are on-screen.

  Args:     void.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiDraw::TopWin(
          void)
{
  HRESULT hr = E_FAIL;

  if (IsWindow(m_hWnd))
  {
    BringWindowToTop(m_hWnd);
    hr = NOERROR;
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiDraw::ResizeWin

  Summary:  Resizes current drawing page rectangle.

  Args:     WORD wWidth
              New window width. Max X coord.
            WORD wHeight
              New window height. Max Y coord.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiDraw::ResizeWin(
                     WORD wWidth,
                     WORD wHeight)
{
  HRESULT hr;

  // Store the new window size.
  m_WinRect.right = wWidth;
  m_WinRect.bottom = wHeight;

  // Tell CODrawPage about new size.
  hr = m_pIDrawPage->Resize(wWidth, wHeight);

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiDraw::ClearWin

  Summary:  Clear display window but don't delete drawn data.

  Args:     void.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiDraw::ClearWin(void)
{
  HRESULT hr = E_FAIL;
  RECT WinRect;

  if(!m_bInking)
  {
    // Get our window's client area rectangle.
    GetClientRect(m_hWnd, &WinRect);

    // Fill that rectangle with pixels of default white paint.
    FillRect(m_hDC, &WinRect, GETCLASSBRUSH(m_hWnd));

    hr = NOERROR;
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiDraw::PaintWin

  Summary:  Clears window background and repaints the current drawing in
            the window. Relies on connectable object technology. The
            Redraw method in the CODrawPage object sends event
            notifications to this client in order to achieve a repaint of
            the drawing. CGuiDraw does not have a copy of the drawing
            data--only the CODrawPage component in the server has that
            in a potentially shared central location.

  Args:     void

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiDraw::PaintWin(void)
{
  HRESULT hr = E_FAIL;
  COLORREF crInkColor;
  SHORT nInkWidth;

  if (m_pIDrawPage && !m_bPainting && !m_bInking)
  {
    m_bPainting = TRUE;
    // Save and restore ink color and width since redraw otherwise
    // ends up changing these values in CGuiDraw.
    crInkColor = m_crInkColor;
    nInkWidth = m_nInkWidth;
    hr = m_pIDrawPage->Redraw();
    m_nInkWidth = nInkWidth;
    m_crInkColor = crInkColor;
    m_bPainting = FALSE;
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiDraw::InkSaving

  Summary:  Tell CGuiDraw whether ink data is being saved in the DrawPage
            object.

  Args:     BOOL bInkSaving
              TRUE means save in CODrawPage object; FALSE means not.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiDraw::InkSaving(
          BOOL bInkSaving)
{
  m_bInkSaving = bInkSaving;

  return NOERROR;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiDraw::InkWidth

  Summary:  Changes current ink line width.

  Args:     SHORT nInkWidth
              New ink line width in pixels.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiDraw::InkWidth(
          SHORT nInkWidth)
{
  if (nInkWidth)
    m_nInkWidth = nInkWidth;

  return NOERROR;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiDraw::InkColor

  Summary:  Changes current ink color.

  Args:     COLORREF crInkColor
              RGB color ref value (eg, RGB(0,0,0) is black).

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiDraw::InkColor(
          COLORREF crInkColor)
{
  m_crInkColor = crInkColor;

  return NOERROR;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiDraw::InkStart

  Summary:  Starts an ink drawing sequence at the specified coordinates in
            the current color with the current width.

  Args:     SHORT nX,
              X coordinate in window rectangle of start point.
            SHORT nY
              Y coordinate in window rectangle of start point.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiDraw::InkStart(
                     SHORT nX,
                     SHORT nY)
{
  HRESULT hr = E_FAIL;

  // Start an ink drawing sequence only if one is not in progress.
  if (!m_bInking)
  {
    // Remember start position.
    m_OldPos.x = nX;
    m_OldPos.y = nY;

    // Delete old pen.
    if (m_hPen)
      DeleteObject(m_hPen);

    // Create and select the new drawing pen.
    m_hPen = CreatePen(PS_SOLID, m_nInkWidth, m_crInkColor);
    SelectObject(m_hDC, m_hPen);

    hr = NOERROR;

    // Ask the DrawPage object to mark the start of the ink drawing
    // sequence in the current ink color.
    if (m_pIDrawPage && m_bInkSaving)
    {
      // Save this start point in CODrawPage.
      hr = m_pIDrawPage->InkStart(nX, nY, m_nInkWidth, m_crInkColor);
      // Capture the Mouse.
      SetCapture(m_hWnd);
      // Tell main app this page was changed.
      PostMessage(m_hWndApp, WM_USER_PAGECHANGED, 0, m_iPage);
    }

    // Set inking flag to TRUE.
    m_bInking = TRUE;
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiDraw::InkDraw

  Summary:  Draws and saves ink data during the currently active ink
            drawing sequence.

  Args:     SHORT nX,
              X coordinate in window rectangle of start point.
            SHORT nY
              Y coordinate in window rectangle of start point.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiDraw::InkDraw(
                     SHORT nX,
                     SHORT nY)
{
  if (m_bInking)
  {
    // Start this ink line at previous old position.
    MoveToEx(m_hDC, m_OldPos.x, m_OldPos.y, NULL);

    // Assign new old position and draw the new line.
    LineTo(m_hDC, m_OldPos.x = nX, m_OldPos.y = nY);

    // Ask the DrawPage object to save this data.
    if (m_bInkSaving)
      m_pIDrawPage->InkDraw(nX, nY);
  }

  return NOERROR;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiDraw::InkStop

  Summary:  Stops the currently active ink drawing sequence.

  Args:     SHORT nX,
              X coordinate in window rectangle of start point.
            SHORT nY
              Y coordinate in window rectangle of start point.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiDraw::InkStop(
                     SHORT nX,
                     SHORT nY)
{
  if (m_bInking)
  {
    // Start this ink line at previous old position.
    MoveToEx(m_hDC, m_OldPos.x, m_OldPos.y, NULL);

    // Draw the last line.
    LineTo(m_hDC, nX, nY);

    // Turn off inking.
    m_bInking = FALSE;

    // Ask the DrawPage object to mark the stop of the ink drawing sequence.
    if (m_bInkSaving)
    {
      m_pIDrawPage->InkStop(nX, nY);
      // Free the mouse.
      ReleaseCapture();
    }
  }

  return NOERROR;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiDraw::Renumber

  Summary:  Re-assign the current dynamic page number for this page.

  Args:     INT iPage
              New page number.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiDraw::Renumber(
          INT iPage)
{
  HRESULT hr = NOERROR;

  m_iPage = iPage;

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiDraw::ReleasePage

  Summary:  Release all substorages for the draw page. Sets the CODrawPage
            object to the HandsOff state.

  Args:     none.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiDraw::ReleasePage(
          void)
{
  HRESULT hr = E_FAIL;
  IPersistStorage* pIPersistStorage;

  if (NULL != m_pIDrawPage)
  {
    hr = m_pIDrawPage->QueryInterface(
           IID_IPersistStorage,
           (PPVOID)&pIPersistStorage);
    if (SUCCEEDED(hr))
    {
      // Tell the CODrawPage object to release all hold it may have
      // on storage.
      hr = pIPersistStorage->HandsOffStorage();

      // Done with IPersistStorage for now so release it.
      pIPersistStorage->Release();
    }
  }

  // Release the interface on the page's storage held by CGuiDraw.
  RELEASE_INTERFACE(m_pIStorage_Page);

  // Release the interface held on the root storage by CGuiDraw.
  RELEASE_INTERFACE(m_pIStorage_Root);

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiDraw::RestorePage

  Summary:  Reopens all substorages for the draw page. Sets the CODrawPage
            object back to the Scribble state by calling SaveCompleted.

  Args:     IStorage* pIStorage_Root
              New root storage for the draw page.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiDraw::RestorePage(
          IStorage* pIStorage_Root)
{
  HRESULT hr = E_POINTER;
  IPersistStorage* pIPersistStorage;

  if (NULL != pIStorage_Root)
  {
    // Save the new interface pointer to the root IStorage and AddRef it.
    m_pIStorage_Root = pIStorage_Root;
    m_pIStorage_Root->AddRef();

    hr = m_pIDrawPage->QueryInterface(
           IID_IPersistStorage,
           (PPVOID)&pIPersistStorage);
    if (SUCCEEDED(hr))
    {
      // ReOpen the single substorage named by m_wszDataName. This is
      // the storage where the draw page is stored. It is under the
      // root storage. The client here is in charge of the underlying
      // storage that the client asks CODrawPage to use.
      hr = m_pIStorage_Root->OpenStorage(
             m_wszDataName,
             NULL,
             STGM_READWRITE | STGM_DIRECT | STGM_SHARE_EXCLUSIVE,
             NULL,
             0,
             &m_pIStorage_Page);
      if (SUCCEEDED(hr))
      {
        // Tell the CODrawPage object that the client is done with its
        // use of storage. Thus CODrawPage will re-open all necessary
        // substorages and switch to the Scribble state.
        hr = pIPersistStorage->SaveCompleted(m_pIStorage_Page);

        // Done with IPersistStorage for now so release it.
        pIPersistStorage->Release();
      }
    }
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiDraw::Close

  Summary:  Close this page window and thus the drawing page's substorages.

  Args:     void.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiDraw::Close(void)
{
  HRESULT hr = NOERROR;

  // Close the GuiDraw window. This will cause a delete of this CGuiDraw.
  ::PostMessage(m_hWnd, WM_CLOSE, 0, 0);

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiDraw::Save

  Summary:  Uses CODrawPage's IPersistStorage interface to save the
            drawing data in the drawing page's substorage.

  Args:     void.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiDraw::Save(
          void)
{
  HRESULT hr = E_FAIL;
  HCURSOR hCurWait = LoadCursor(NULL, IDC_WAIT);
  HCURSOR hCurPrev;
  IPersistStorage* pIPersistStorage;

  if (NULL != m_pIStorage_Page && NULL != m_pIDrawPage)
  {
    // Change cursor to the hour glass.
    hCurPrev = SetCursor(hCurWait);

    // Tell the CODrawPage object to save itself
    // (via its IPersistStorage interface).
    hr = m_pIDrawPage->QueryInterface(
           IID_IPersistStorage,
           (PPVOID)&pIPersistStorage);
    if (SUCCEEDED(hr))
    {
      // Perform the save with fSameAsLoad==TRUE.
      hr = pIPersistStorage->Save(m_pIStorage_Page, TRUE);
      if (SUCCEEDED(hr))
      {
        // This is the general save by the client. In the case of
        // this application the client does not need to do any other
        // intermediate save or write operations to the compound file
        // prior to informing the server that client save operations
        // are completed.
        hr = pIPersistStorage->SaveCompleted(NULL);
      }

      // Done with IPersistStorage for now so release it.
      pIPersistStorage->Release();
    }

    // Set Cursor back to what it was.
    SetCursor(hCurPrev);
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiDraw::AskSave

  Summary:  Checks dirty flag (ie, if current drawing data was modified
            and is out of sync with the DrawPage data stored in the page's
            storage). If dirty, then ask user in simple dialog if he wants
            to save new data. If he says yes, then save the current
            DrawPage data into its storage.

  Args:     void.

  Returns:  INT
              Value returned from the Win32 MessageBox function.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
INT CGuiDraw::AskSave(void)
{
  int iAns = IDNO;
  HRESULT hr;
  TCHAR szTitle[MAX_STRING_LENGTH];
  TCHAR szAsk[MAX_STRING_LENGTH];
  TCHAR szMsg[MAX_PATH + MAX_STRING_LENGTH];
  IPersistStorage* pIPersistStorage;

  hr = m_pIDrawPage->QueryInterface(
           IID_IPersistStorage,
           (PPVOID)&pIPersistStorage);
  if (SUCCEEDED(hr))
  {
    // Ask the DrawPage object if it is dirty.
    if (S_FALSE != pIPersistStorage->IsDirty())
    {
      // The current data is dirty; ask user if he wants to save it.
      if (LoadString(m_hInst, IDS_DRAW_PAGE, szTitle, MAX_STRING_LENGTH)
          && LoadString(m_hInst, IDS_ASK_SAVE, szAsk, MAX_STRING_LENGTH))
      {
        lstrcpy(szMsg, szTitle);
        lstrcat(szMsg, szAsk);
        // Display AskSaveDlg to user. Ask if he wants to save.
        iAns = MessageBox(
                 m_hWnd,
                 szMsg,
                 szTitle,
                 MB_YESNOCANCEL | MB_ICONEXCLAMATION);
        switch (iAns)
        {
          case IDYES:
            // Tell CGuiDraw to save itself to file storage.
            Save();
            break;
          case IDNO:
            // User clicked No. So don't save; abandon changes.
            break;
          case IDCANCEL:
          default:
            break;
        }
      }
    }

    // Done with IPersistStorage for now so release it.
    pIPersistStorage->Release();
  }

  return iAns;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiDraw::Delete

  Summary:  Delete the stored DrawPage. Shuts down the drawing page and
            window. Disconnects the Sink and does final release of the
            CODrawPage object.

  Args:     void.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiDraw::Delete(void)
{
  HRESULT hr = E_FAIL;
  HCURSOR hCurWait = LoadCursor(NULL, IDC_WAIT);
  HCURSOR hCurPrev;

  if (NULL != m_pIStorage_Root && NULL != m_pIDrawPage)
  {
    // Change cursor to the hour glass.
    hCurPrev = SetCursor(hCurWait);

    // Clear the draw page.
    m_pIDrawPage->Clear(FALSE);

    // Destroy the entire drawpage's storage.
    hr = m_pIStorage_Root->DestroyElement(m_wszDataName);

    // Set Cursor back to what it was.
    SetCursor(hCurPrev);
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiDraw::Clear

  Summary:  Clear content of the drawing page and clear display window.

  Args:     void.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiDraw::Clear(void)
{
  HRESULT hr = E_FAIL;

  if (m_pIDrawPage)
    hr = m_pIDrawPage->Clear(TRUE);
  if (SUCCEEDED(hr))
  {
    ClearWin();
    // Tell main app if this page was changed.
    PostMessage(m_hWndApp, WM_USER_PAGECHANGED, 0, m_iPage);
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiDraw::PickColor

  Summary:  Uses the Choose Color common dialog to ask user for new
            Pen color. Return that new color.

  Args:     void.

  Returns:  COLORREF
              New chosen color.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COLORREF CGuiDraw::PickColor(void)
{
  COLORREF crNewColor = m_crInkColor;
  SHORT i;

  // Init the custom color array with gray colors.
  for (i=0; i<16; i++)
    m_acrCustColors[i] = RGB(i*16, i*16, i*16);

  // Init the Choose Color structure.
  m_ChooseColor.lStructSize = sizeof(CHOOSECOLOR);
  m_ChooseColor.hwndOwner = m_hWnd;
  m_ChooseColor.hInstance = (HWND) m_hInst;
  m_ChooseColor.rgbResult = m_crInkColor;
  m_ChooseColor.lpCustColors = (DWORD*) m_acrCustColors;
  m_ChooseColor.Flags = CC_PREVENTFULLOPEN | CC_RGBINIT;
  m_ChooseColor.lCustData = 0L;
  m_ChooseColor.lpfnHook = NULL;
  m_ChooseColor.lpTemplateName = NULL;

  if (ChooseColor(&m_ChooseColor))
    crNewColor = m_ChooseColor.rgbResult;

  return crNewColor;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiDraw::GetConnectionPoint

  Summary:  Internal private method to obtain a connection point interface.

  Args:     REFIID riid
              IID of the requested connection point Interface.

  Returns:  IConnectionPoint*
              Requested IConnectionPoint interface pointer. NULL if none.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
IConnectionPoint* CGuiDraw::GetConnectionPoint(
                    REFIID riid)
{
  IConnectionPoint* pIConnectionPoint = NULL;
  IConnectionPointContainer* pIConnectionPointContainer = NULL;
  IConnectionPoint* pIConnPt;
  HRESULT hr;

  // First query the object for its Connection Point Container. This
  // essentially asks the object in the server if it is connectable.
  hr = m_pIDrawPage->QueryInterface(
         IID_IConnectionPointContainer,
         (PPVOID)&pIConnectionPointContainer);
  if SUCCEEDED(hr)
  {
    // Find the requested Connection Point. This AddRef's the
    // returned pointer.
    hr = pIConnectionPointContainer->FindConnectionPoint(riid, &pIConnPt);
    if (SUCCEEDED(hr))
      pIConnectionPoint = pIConnPt;

    RELEASE_INTERFACE(pIConnectionPointContainer);
  }

  return pIConnectionPoint;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiDraw::ConnectSink

  Summary:  Connect the client's DrawPageSink to the server's
            CODrawPage source.

  Args:     void

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiDraw::ConnectSink(void)
{
  HRESULT hr = E_FAIL;
  DWORD dwKey;
  IConnectionPoint* pIConnectionPoint = NULL;

  if (!m_dwDrawPageSink)
  {
    // Get the DrawPage Sink connection point in the server.
    pIConnectionPoint = GetConnectionPoint(IID_IDrawPageSink);
    if (NULL != pIConnectionPoint)
    {
      // Connect the server's object to the DrawPage Sink in this client.
      hr = pIConnectionPoint->Advise(m_pCODrawPageSink, &dwKey);
      if (SUCCEEDED(hr))
        m_dwDrawPageSink = dwKey;

      RELEASE_INTERFACE(pIConnectionPoint);
    }
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiDraw::DisconnectSink

  Summary:  Disconnect the client DrawPageSink from the server
            CODrawPage source.

  Args:     void.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiDraw::DisconnectSink(void)
{
  HRESULT hr = E_FAIL;
  IConnectionPoint* pIConnectionPoint;

  if (m_dwDrawPageSink)
  {
    // Get the DrawPage Sink connection point.
    pIConnectionPoint = GetConnectionPoint(IID_IDrawPageSink);
    if (NULL != pIConnectionPoint)
    {
      // Disconnect the object in the server from the DrawPage Sink in
      // this client.
      hr = pIConnectionPoint->Unadvise(m_dwDrawPageSink);
      if (SUCCEEDED(hr))
        m_dwDrawPageSink = 0;

      RELEASE_INTERFACE(pIConnectionPoint);
    }
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiDraw::DoCommand

  Summary:  Dispatch and handle the main menu and other commands.

  Args:     WPARAM wParam,
              First message parameter.
            LPARAM lParam)
              Second message parameter.

  Returns:  LRESULT
              Standard Windows WindowProc return value.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CGuiDraw::DoCommand(
          WPARAM wParam,
          LPARAM lParam)
{
  LRESULT lResult = FALSE;
  HMENU hMenu = ::GetMenu(m_hWnd);

  switch (LOWORD(wParam))
  {
    //----------------------------------------------------------------------
    // Handle Drawing Menu Commands.
    //----------------------------------------------------------------------
    case IDM_DRAW_SAVE:
      // Ask the GuiDraw object to save the current drawing.
      Save();
      break;
    case IDM_DRAW_CLEAR:
      // Ask GuiDraw object to clear its current content and if it can,
      // clear drawing display window.
      Clear();
      break;
    case IDM_DRAW_EXIT:
      // The user commands us to exit this page so we tell the
      // window to close itself.
      ::PostMessage(m_hWnd, WM_CLOSE, 0, 0);
      break;

    //----------------------------------------------------------------------
    // Handle Pen Menu Commands.
    //----------------------------------------------------------------------
    case IDM_PEN_COLOR:
      // Select Ink drawing color using ChooseColor common dialog.
      {
        COLORREF crNewColor = PickColor();
        InkColor(crNewColor);
      }
      break;
    case IDM_PEN_THIN:
      // Select thin Ink width. Set menu check indicator.
      {
        HRESULT hr;
        HMENU hMenu  = ::GetMenu(m_hWnd);
        BOOL bOn = ::GetMenuState(
                       hMenu,
                       IDM_PEN_THIN,
                       MF_BYCOMMAND) & MF_CHECKED;
        if (!bOn)
        {
          hr = InkWidth(INK_THIN);
          if (SUCCEEDED(hr))
          {
            ::CheckMenuItem(
                hMenu,
                IDM_PEN_THIN,
                MF_BYCOMMAND | MF_CHECKED);
            ::CheckMenuItem(
                hMenu,
                IDM_PEN_MEDIUM,
                MF_BYCOMMAND | MF_UNCHECKED);
            ::CheckMenuItem(
                hMenu,
                IDM_PEN_THICK,
                MF_BYCOMMAND | MF_UNCHECKED);
          }
        }
      }
      break;
    case IDM_PEN_MEDIUM:
      // Select medium Ink width. Set menu check indicator.
      {
        HRESULT hr;
        HMENU hMenu  = ::GetMenu(m_hWnd);
        BOOL bOn = ::GetMenuState(
                       hMenu,
                       IDM_PEN_MEDIUM,
                       MF_BYCOMMAND) & MF_CHECKED;
        if (!bOn)
        {
          hr = InkWidth(INK_MEDIUM);
          if (SUCCEEDED(hr))
          {
            ::CheckMenuItem(
                hMenu,
                IDM_PEN_MEDIUM,
                MF_BYCOMMAND | MF_CHECKED);
            ::CheckMenuItem(
                hMenu,
                IDM_PEN_THICK,
                MF_BYCOMMAND | MF_UNCHECKED);
            ::CheckMenuItem(
                hMenu,
                IDM_PEN_THIN,
                MF_BYCOMMAND | MF_UNCHECKED);
          }
        }
      }
      break;
    case IDM_PEN_THICK:
      // Select thick Ink width. Set menu check indicator.
      {
        HRESULT hr;
        HMENU hMenu  = ::GetMenu(m_hWnd);
        BOOL bOn = ::GetMenuState(
                       hMenu,
                       IDM_PEN_THICK,
                       MF_BYCOMMAND) & MF_CHECKED;
        if (!bOn)
        {
          hr = InkWidth(INK_THICK);
          if (SUCCEEDED(hr))
          {
            ::CheckMenuItem(
                hMenu,
                IDM_PEN_THICK,
                MF_BYCOMMAND | MF_CHECKED);
            ::CheckMenuItem(
                hMenu,
                IDM_PEN_MEDIUM,
                MF_BYCOMMAND | MF_UNCHECKED);
            ::CheckMenuItem(
                hMenu,
                IDM_PEN_THIN,
                MF_BYCOMMAND | MF_UNCHECKED);
          }
        }
      }
      break;

    //----------------------------------------------------------------------
    // Handle Help Menu Commands. Pass these commands on to main app.
    //----------------------------------------------------------------------
    case IDM_DHELP_CONTENTS:
      PostMessage(m_hWndApp, WM_COMMAND, (WPARAM) IDM_HELP_CONTENTS, 0);
      break;
    case IDM_DHELP_TUTORIAL:
      PostMessage(m_hWndApp, WM_COMMAND, (WPARAM) IDM_HELP_TUTORIAL, 0);
      break;
    case IDM_DHELP_TUTSERVER:
      PostMessage(m_hWndApp, WM_COMMAND, (WPARAM) IDM_HELP_PERDRAW, 0);
      break;
    case IDM_DHELP_READSOURCE:
      PostMessage(m_hWndApp, WM_COMMAND, (WPARAM) IDM_HELP_READSOURCE, 0);
      break;
    case IDM_DHELP_ABOUT:
      PostMessage(m_hWndApp, WM_COMMAND, (WPARAM) IDM_HELP_ABOUT, 0);
      break;

    default:
      // Defer all messages NOT handled here to the Default Window Proc.
      lResult = ::DefWindowProc(m_hWnd, WM_COMMAND, wParam, lParam);
      break;
  }

  return(lResult);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiDraw::WindowProc

  Summary:  Main window procedure for this window object.  See CVirWindow
            in the APPUTIL library (APPUTIL.H and APPUTIL.CPP) for details
            on how this method gets called by the global WindowProc.

  Args:     UINT uMsg,
              Windows message that is "sent" to this window.
            WPARAM wParam,
              First message parameter.
            LPARAM lParam)
              Second message parameter.

  Returns:  LRESULT
              Standard Windows WindowProc return value.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CGuiDraw::WindowProc(
          UINT uMsg,
          WPARAM wParam,
          LPARAM lParam)
{
  LRESULT lResult = FALSE;

  switch (uMsg)
  {
    case WM_CREATE:
      break;

    case WM_ACTIVATE:
      // If we were newly activated by a mouse click then don't just sit
      // there--re-paint. This is needed when another window was topped
      // over part of this DrawPage window and the user then topped the
      // DrawPage using a mouse click on the visible part of this window.
      // In any case also let the windows default WindowProc handle this
      // message to set keyboard focus to the newly active window.
      if (WA_CLICKACTIVE == LOWORD(wParam))
        PaintWin();
      lResult = ::DefWindowProc(m_hWnd, uMsg, wParam, lParam);
      break;

    case WM_MEASUREITEM:
      // Get setup for painting text in this window. For later evolution.
      {
        LPMEASUREITEMSTRUCT lpmis = (LPMEASUREITEMSTRUCT) lParam;
        lpmis->itemHeight = m_tm.tmHeight + m_tm.tmExternalLeading;
        lpmis->itemWidth = m_wWidth;
        lResult = TRUE;
      }

    case WM_SIZE:
      // Handle a resize of this window.
      ResizeWin(LOWORD(lParam), HIWORD(lParam));
      break;

    case WM_PAINT:
      // If something major happened repaint the whole window.
      {
        PAINTSTRUCT ps;

        if(BeginPaint(m_hWnd, &ps))
        {
          PaintWin();
          EndPaint(m_hWnd, &ps);
        }
      }
      break;

    case WM_LBUTTONDOWN:
      // Start sequence of ink drawing to the paper.
      InkStart(LOWORD(lParam), HIWORD(lParam));
      break;

    case WM_MOUSEMOVE:
      // Draw inking sequence data.
      InkDraw(LOWORD(lParam), HIWORD(lParam));
      break;

    case WM_LBUTTONUP:
      // Stop an ink drawing sequence.
      InkStop(LOWORD(lParam), HIWORD(lParam));
      break;

    case WM_COMMAND:
      // Dispatch and handle any Menu and command messages received.
      lResult = DoCommand(wParam, lParam);
      break;

    case WM_CHAR:
      if (wParam == 0x1b)
      {
        // Exit this app if user hits ESC key.
        ::PostMessage(m_hWnd, WM_CLOSE, 0, 0);
      }
      break;

    case WM_CLOSE:
      // The user selected Close on the drawing window's System menu
      // or Exit on the File menu.
      // If there is data that has not been saved then ask user
      // if it should be saved. If user cancels then cancel the exit.
      if (IDCANCEL == AskSave())
        break;
    case WM_QUIT:
      // Bring the main app window to top when this drawing window goes away.
      BringWindowToTop(m_hWndApp);
      // If the app is being quit then close any associated help windows.
      // For future evolution.
    default:
      // Defer all messages NOT handled above to the Default Window Proc.
      lResult = ::DefWindowProc(m_hWnd, uMsg, wParam, lParam);
      break;
  }

  return(lResult);
}
