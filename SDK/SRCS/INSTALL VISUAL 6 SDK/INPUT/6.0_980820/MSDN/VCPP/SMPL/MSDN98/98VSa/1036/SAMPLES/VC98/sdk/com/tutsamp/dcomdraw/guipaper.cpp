/*+==========================================================================
  File:      GUIPAPER.CPP

  Summary:   Implementation file for the CGuiPaper C++ class. A GuiPaper
             is a C++ object that displays mouse movement as free-form
             drawing in the client area of a designated window (much like
             common scribble sample programs except that COM technology is
             used throughout to construct this functionality). CGuiPaper
             is anchored to the Windows GUI (Graphical User Interface)
             environment--it retains knowledge of window handles and
             device contexts on the local machine. This GuiPaper object
             relies on a virtual paper object for storage of the drawing
             data. This virtual Paper object (a COPaper) is instantiated
             as a COM object in a separate thread-safe out-of-process
             server, DCDSERVE.

             For a comprehensive tutorial code tour of GUIPAPER's contents
             and offerings see the tutorial DCOMDRAW.HTM file. For more
             specific technical details on the internal workings see the
             comments dispersed throughout the GUIPAPER source code.

  Classes:   CGuiPaper.

  Origin:    8-23-97: atrent - Editor inheritance from GUIBALL.CPP in the
             CONCLIEN source. [Revised]

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
  We include TCHAR.H for general Unicode/Ansi prototype of utility
    functions like _tsplitpath, etc.
  We include APPUTIL.H because we will be building this application using
    the convenient Virtual Window and Dialog classes and other
    utility functions in the APPUTIL Library (ie, APPUTIL.LIB).
  We include PAPINT.H and PAPGUIDS.H for the common Paper-related Interface
    class, GUID, and CLSID specifications.
  We include GUIPAPER.H because it has the C++ class used for GUI display
    of the drawing Paper.
  We include SINK.H because it has the C++ class used for the sink that
    receives event notifications from the COPaper object in the server.
  We include DCOMDRAW.H because it has class and resource definitions
    specific to this DCOMDRAW application.
---------------------------------------------------------------------------*/
#include <windows.h>
#include <ole2.h>
#include <olectl.h>
#include <commdlg.h>
#include <tchar.h>
#include <apputil.h>
#include <papint.h>
#include <papguids.h>
#include "guipaper.h"
#include "sink.h"
#include "dcomdraw.h"


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiPaper::CGuiPaper

  Summary:  Constructor.

  Args:     void

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CGuiPaper::CGuiPaper(void)
{
  m_hWnd       = NULL;
  m_hInst      = NULL;
  m_hDC        = NULL;
  m_pISharePaper = NULL;
  m_hPen       = NULL;
  m_nInkWidth  = INK_THIN;
  m_crInkColor = RGB(0,0,0);
  m_bInkSaving = FALSE;
  m_bInking    = FALSE;
  m_bPainting  = FALSE;
  m_OldPos.x   = 0;
  m_OldPos.y   = 0;
  m_pCOPaperSink = NULL;
  m_dwPaperSink = 0;
  m_bDirty     = FALSE;

  m_PenCur = PENCUR_OFF | PENCUR_THIN;
  m_hPenCurN = NULL;
  m_hPenCurT = NULL;
  m_hPenCurM = NULL;
  m_hPenCurF = NULL;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiPaper::~CGuiPaper

  Summary:  Destructor.

  Args:     void

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CGuiPaper::~CGuiPaper(void)
{
  BOOL bOk = TRUE;

  if (m_pISharePaper)
  {
    // Just to make sure, turn off Ink Saving.
    m_bInkSaving = FALSE;

    // Make sure we unlock the paper object.
    m_pISharePaper->Lock(FALSE);

    // Disconnect all Sinks--currently only one: PaperSink. This officially
    // stops all PaperSink notifications.
    DisconnectPaperSink();

    // Delete the Pen object.
    if (m_hPen)
      DeleteObject(m_hPen);

    // Release the reference to the PaperSink object.
    RELEASE_INTERFACE(m_pCOPaperSink);

    // Release the main interface pointer copy held in CGuiPaper.
    RELEASE_INTERFACE(m_pISharePaper);
  }
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiPaper::Init

  Summary:  Get CGuiPaper started. Make any subordinate objects, like
            COPaper and CPapFile, and get them started.

  Args:     HINSTANCE hInst
              Handle to the application instance.
            HWND hWnd
              Handle of the display window. Part of what makes CGuiPaper
              a GUI kind of thing.

  Returns:  BOOL
              TRUE for success; FALSE for fail.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
BOOL CGuiPaper::Init(
       HINSTANCE hInst,
       HWND hWnd)
{
  BOOL bOk = FALSE;
  HRESULT hr;
  BOOL bFirst;
  COPaperSink* pCobSink = NULL;
  HCURSOR hCurPrev;
  HCURSOR hCurWait = LoadCursor(NULL, IDC_WAIT);

  if (hInst && hWnd)
  {
    m_hInst = hInst;
    m_hWnd = hWnd;

    // Load the pen cursors.
    m_hPenCurN = LoadCursor(m_hInst, TEXT("PenCurN"));
    m_hPenCurT = LoadCursor(m_hInst, TEXT("PenCurT"));
    m_hPenCurM = LoadCursor(m_hInst, TEXT("PenCurM"));
    m_hPenCurF = LoadCursor(m_hInst, TEXT("PenCurF"));

    // Get and save our private display Device Context.
    m_hDC = GetDC(m_hWnd);

    // Change cursor to the hour glass. Init could take awhile.
    hCurPrev = SetCursor(hCurWait);

    // Call COM service to create a COPaper instance. We are not
    // aggregating it so we ask for its ISharePaper interface directly.
    hr = CoCreateInstance(
           CLSID_SharePaper,
           NULL,
           CLSCTX_LOCAL_SERVER,
           IID_ISharePaper,
           (PPVOID)&m_pISharePaper);
    if (SUCCEEDED(hr))
    {
      // Init the COPaper object.
      GetClientRect(hWnd, &m_WinRect);
      hr = m_pISharePaper->InitPaper(&m_WinRect, &bFirst);
      if (SUCCEEDED(hr))
      {
        // Resize this client's window to match what the COPaper
        // object returned for its size.
        ResizeWin(m_WinRect.right, m_WinRect.bottom);

        // Create the COPaperSink object to receive COPaper events.
        pCobSink = new COPaperSink(NULL, this);
        if (NULL != pCobSink)
        {
          // Save a pointer to the COPaperSink IUnknown interface.
          // AddRef because of this saved copy.
          m_pCOPaperSink = pCobSink;
          m_pCOPaperSink->AddRef();
        }
        else
          hr = E_OUTOFMEMORY;
      }

      bOk = SUCCEEDED(hr);
    }
    else
      HrMsg(hWnd, TEXT(LOCAL_CREATE_ERR_STR), hr);

    // Set Cursor back to what it was.
    SetCursor(hCurPrev);
  }

  return (bOk);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiPaper::SetPenCur

  Summary:  Set the pen cursor.

  Args:     USHORT usPenCurNew
              Or'd bits for the pen cursor.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiPaper::SetPenCur(
          USHORT usPenCurNew)
{
  HRESULT hr = E_FAIL;
  USHORT usPenCurW;

  usPenCurW = m_PenCur & (PENCUR_THIN | PENCUR_MEDIUM | PENCUR_THICK);

  switch (usPenCurNew)
  {
    case PENCUR_OFF:
     hr = (m_PenCur & PENCUR_ON) ? NOERROR : E_FAIL;
     m_PenCur = usPenCurW;
     SetClassLong(m_hWnd, GCL_HCURSOR, (LONG)m_hPenCurN);
     break;
    case PENCUR_ON:
     hr = (m_PenCur & PENCUR_ON) ? E_FAIL: NOERROR;
     m_PenCur = PENCUR_ON | usPenCurW;
     switch (usPenCurW)
     {
       case PENCUR_THICK:
         SetClassLong(m_hWnd, GCL_HCURSOR, (LONG)m_hPenCurF);
         break;
       case PENCUR_MEDIUM:
         SetClassLong(m_hWnd, GCL_HCURSOR, (LONG)m_hPenCurM);
         break;
       case PENCUR_THIN:
       default:
         SetClassLong(m_hWnd, GCL_HCURSOR, (LONG)m_hPenCurT);
         break;
     }
     break;
    case PENCUR_THICK:
     hr = (usPenCurW & PENCUR_THICK) ? E_FAIL: NOERROR;
     m_PenCur = (m_PenCur & PENCUR_ON);
     m_PenCur |= PENCUR_THICK;
     SetClassLong(m_hWnd, GCL_HCURSOR, (LONG)m_hPenCurF);
     break;
    case PENCUR_MEDIUM:
     hr = (usPenCurW & PENCUR_MEDIUM) ? E_FAIL: NOERROR;
     m_PenCur = (m_PenCur & PENCUR_ON);
     m_PenCur |= PENCUR_MEDIUM;
     SetClassLong(m_hWnd, GCL_HCURSOR, (LONG)m_hPenCurM);
     break;
    case PENCUR_THIN:
     hr = (usPenCurW & PENCUR_THIN) ? E_FAIL: NOERROR;
     m_PenCur = (m_PenCur & PENCUR_ON);
     m_PenCur |= PENCUR_THIN;
     SetClassLong(m_hWnd, GCL_HCURSOR, (LONG)m_hPenCurT);
     break;
    default:
     break;
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiPaper::Lock

  Summary:  Lock the paper object for drawing by this client.

  Args:     BOOL bLock
              TRUE => lock the paper. FALSE => unlock the paper.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiPaper::Lock(
          BOOL bLock)
{
  HRESULT hr = NOERROR;
  HMENU hMenu = ::GetMenu(m_hWnd);

  if (bLock)
  {
    // If we are not already locked for drawing then do so.
    if (!m_bLocked)
    {
      hr = m_pISharePaper->Lock(TRUE);
      if (SUCCEEDED(hr))
      {
        // Set Main Window Title.
        SetWindowText(m_hWnd, TEXT(MAIN_WINDOW_MASTER_STR));
        // Set the menu check marks.
        ::CheckMenuItem(
            hMenu,
            IDM_DRAW_MASTER,
            MF_BYCOMMAND | MF_CHECKED);
        ::CheckMenuItem(
            hMenu,
            IDM_DRAW_SLAVE,
            MF_BYCOMMAND | MF_UNCHECKED);
        // Set the Pen cursor on.
        SetPenCur(PENCUR_ON);
        m_bLocked = TRUE;
        // We have siezed control of the pen and can now allow ink saving.
        m_bInkSaving = TRUE;
        m_bDirty = TRUE;
      }
      else
      {
        // Set Main Window Title.
        SetWindowText(m_hWnd, TEXT(MAIN_WINDOW_SLAVE_STR));
        // Set the menu check marks.
        ::CheckMenuItem(
            hMenu,
            IDM_DRAW_MASTER,
            MF_BYCOMMAND | MF_UNCHECKED);
        ::CheckMenuItem(
            hMenu,
            IDM_DRAW_SLAVE,
            MF_BYCOMMAND | MF_CHECKED);
        // Set the Pen cursor off.
        SetPenCur(PENCUR_OFF);
      }
    }
  }
  else
  {
    // If we are not already unlocked for drawing then do so.
    if (m_bLocked)
    {
      // AskSave();
      hr = m_pISharePaper->Lock(FALSE);
      if (SUCCEEDED(hr))
      {
        // Set Main Window Title.
        SetWindowText(m_hWnd, TEXT(MAIN_WINDOW_SLAVE_STR));
        // Set the menu check marks.
        ::CheckMenuItem(
            hMenu,
            IDM_DRAW_MASTER,
            MF_BYCOMMAND | MF_UNCHECKED);
        ::CheckMenuItem(
            hMenu,
            IDM_DRAW_SLAVE,
            MF_BYCOMMAND | MF_CHECKED);
        // Set the Pen cursor off.
        SetPenCur(PENCUR_OFF);
        m_bLocked = FALSE;
        m_bInkSaving = FALSE;
        m_bDirty = FALSE;
      }
    }
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiPaper::Master

  Summary:  Return TRUE if this client is the master client that owns
            the drawing paper.

  Args:     void.

  Returns:  BOOL
              TRUE => This client is master.  FALSE => Not master.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
BOOL CGuiPaper::Master(void)
{
  BOOL bMaster = m_bLocked && m_bInkSaving;

  return bMaster;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiPaper::ClearWin

  Summary:  Clear display window but don't erase drawn data.

  Args:     void.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiPaper::ClearWin(void)
{
  HRESULT hr = E_FAIL;
  RECT  WinRect;

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
  Method:   CGuiPaper::ResizeWin

  Summary:  Resize display window.

  Args:     LONG lWidth
              New window width. Max X coord.
            LONG lHeight
              New window height. Max Y coord.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiPaper::ResizeWin(
                     LONG lWidth,
                     LONG lHeight)
{
  HRESULT hr = NOERROR;

  if(!m_bInking)
  {
    SetWindowPos(
      m_hWnd,
      HWND_TOP,
      0,
      0,
      6+lWidth,
      50+lHeight,
      SWP_NOMOVE | SWP_NOZORDER);
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiPaper::PaintWin

  Summary:  Repaints the current drawing in the drawing window.

  Args:     void

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiPaper::PaintWin(void)
{
  HRESULT hr = E_FAIL;
  COLORREF crInkColorTmp;
  SHORT nInkWidthTmp;
  BOOL bInkSavingTmp;
  LONG i;
  SHORT nInkType;
  SHORT nX;
  SHORT nY;
  SHORT nInkWidth;
  COLORREF crInkColor;

  if (m_pISharePaper && !m_bPainting && !m_bInking)
  {
    hr = NOERROR;
    m_bPainting = TRUE;
    // Save and restore ink color and width since redraw otherwise
    // ends up changing these values in CGuiPaper.
    crInkColorTmp = m_crInkColor;
    nInkWidthTmp = m_nInkWidth;
    bInkSavingTmp = m_bInkSaving;
    m_bInkSaving = FALSE;
    for (i = 0; SUCCEEDED(hr); i++)
    {
      hr = m_pISharePaper->GetInk(
             i,
             &nInkType,
             &nX,
             &nY,
             &nInkWidth,
             &crInkColor);
      if (SUCCEEDED(hr))
      {
        switch (nInkType)
        {
          case INKTYPE_START:
            m_nInkWidth = nInkWidth;
            m_crInkColor = crInkColor;
            InkStart(nX, nY);
            break;
          case INKTYPE_DRAW:
            InkDraw(nX, nY);
            break;
          case INKTYPE_STOP:
            InkStop(nX, nY);
            break;
          default:
            break;
        }
      }
    }
    m_nInkWidth = nInkWidthTmp;
    m_crInkColor = crInkColorTmp;
    m_bInkSaving = bInkSavingTmp;
    m_bPainting = FALSE;
    hr = NOERROR;
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiPaper::Erase

  Summary:  Erase content of the drawing paper and clear display window.

  Args:     void.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiPaper::Erase(void)
{
  HRESULT hr = E_FAIL;

  if (Master())
  {
    if (m_pISharePaper)
      hr = m_pISharePaper->Erase();
    if (SUCCEEDED(hr))
    {
      ClearWin();
      m_bDirty = TRUE;
    }
  }
  else
    ClearWin();

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiPaper::Resize

  Summary:  Resizes current drawing paper rectangle.

  Args:     LONG lWidth
              New window width. Max X coord.
            LONG lHeight
              New window height. Max Y coord.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiPaper::Resize(
                     LONG lWidth,
                     LONG lHeight)
{
  HRESULT hr = NOERROR;

  if (Master())
  {
    if (m_pISharePaper)
    {
      hr = m_pISharePaper->Resize(lWidth, lHeight);
      if (SUCCEEDED(hr))
        m_bDirty = TRUE;
    }
  }
  else
    ResizeWin(lWidth, lHeight);

  if (SUCCEEDED(hr))
  {
    // Store the new window size.
    m_WinRect.right = lWidth;
    m_WinRect.bottom = lHeight;
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiPaper::InkWidth

  Summary:  Changes current ink width and sets the visable pen cursor
            based on the width.

  Args:     SHORT nInkWidth
              New ink width in pixels.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiPaper::InkWidth(
                     SHORT nInkWidth)
{
  HRESULT hr = E_FAIL;

  switch (nInkWidth)
  {
    case INK_THIN:
      if (!(m_PenCur & (PENCUR_THIN)))
        hr = SetPenCur(PENCUR_THIN);
      break;
    case INK_MEDIUM:
      if (!(m_PenCur & (PENCUR_MEDIUM)))
        hr = SetPenCur(PENCUR_MEDIUM);
      break;
    case INK_THICK:
      if (!(m_PenCur & (PENCUR_THICK)))
        hr = SetPenCur(PENCUR_THICK);
      break;
    default:
      break;
  }

  if (SUCCEEDED(hr))
    m_nInkWidth = nInkWidth;

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiPaper::InkColor

  Summary:  Changes current ink color.

  Args:     COLORREF crInkColor
              RGB color ref value (eg, RGB(0,0,0) is black).

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiPaper::InkColor(
                     COLORREF crInkColor)
{
  m_crInkColor = crInkColor;

  return NOERROR;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiPaper::InkStart

  Summary:  Starts an ink drawing sequence in the current color.

  Args:     SHORT nX,
              X coordinate in window rectangle of start point.
            SHORT nY
              Y coordinate in window rectangle of start point.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiPaper::InkStart(
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

    // Ask the Paper object to mark the start of the ink drawing
    // sequence in the current ink color.
    if (m_pISharePaper && m_bInkSaving)
    {
      hr = m_pISharePaper->InkStart(
              nX,
              nY,
              m_nInkWidth,
              m_crInkColor);
      // Capture the Mouse.
      SetCapture(m_hWnd);

      // We've modified the ink data--it is now "dirty" with
      // respect to the compound file image. Set dirty flag.
      m_bDirty = TRUE;
    }

    // Set inking flag to TRUE.
    m_bInking = TRUE;
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiPaper::InkDraw

  Summary:  Draws and saves ink data during the currently active ink
            drawing sequence.

  Args:     SHORT nX,
              X coordinate in window rectangle of start point.
            SHORT nY
              Y coordinate in window rectangle of start point.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiPaper::InkDraw(
                     SHORT nX,
                     SHORT nY)
{
  if (m_bInking)
  {
    // Start this ink line at previous old position.
    MoveToEx(m_hDC, m_OldPos.x, m_OldPos.y, NULL);

    // Assign new old position and draw the new line.
    LineTo(m_hDC, m_OldPos.x = nX, m_OldPos.y = nY);

    // Ask the Paper object to save this data.
    if (m_bInkSaving)
      m_pISharePaper->InkDraw(nX, nY);
  }

  return NOERROR;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiPaper::InkStop

  Summary:  Stops the currently active ink drawing sequence.

  Args:     SHORT nX,
              X coordinate in window rectangle of start point.
            SHORT nY
              Y coordinate in window rectangle of start point.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiPaper::InkStop(
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

    // Ask the Paper object to mark the stop of the ink drawing sequence.
    if (m_bInkSaving)
    {
      m_pISharePaper->InkStop(nX, nY);
      // Free the mouse.
      ReleaseCapture();
    }
  }

  return NOERROR;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiPaper::GetConnectionPoint

  Summary:  Internal private method to obtain a connection point interface.

  Args:     REFIID riid
              IID of the requested connection point Interface.

  Returns:  IConnectionPoint*
              Requested IConnectionPoint interface pointer. NULL if none.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
IConnectionPoint* CGuiPaper::GetConnectionPoint(
                    REFIID riid)
{
  IConnectionPoint* pConnPoint = NULL;
  IConnectionPointContainer* pConnPointContainer = NULL;
  IConnectionPoint* pConnPt;
  HRESULT hr;

  // First query the object for its Connection Point Container. This
  // essentially asks the object in the server if it is connectable.
  hr = m_pISharePaper->QueryInterface(
         IID_IConnectionPointContainer,
         (PPVOID)&pConnPointContainer);
  if SUCCEEDED(hr)
  {
    // Find the requested Connection Point. This AddRef's the
    // returned pointer.
    hr = pConnPointContainer->FindConnectionPoint(riid, &pConnPt);
    if (SUCCEEDED(hr))
      pConnPoint = pConnPt;

    RELEASE_INTERFACE(pConnPointContainer);
  }

  return pConnPoint;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiPaper::ConnectPaperSink

  Summary:  Connect the PaperSink to the server COPaper source.

  Args:     void

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiPaper::ConnectPaperSink(void)
{
  HRESULT hr = E_FAIL;
  DWORD dwKey;
  IConnectionPoint* pConnPoint;

  if (!m_dwPaperSink)
  {
    // Get the Paper Sink connection point.
    pConnPoint = GetConnectionPoint(IID_IPaperSink);
    if (NULL != pConnPoint)
    {
      // Connect the object in the server to the Paper Sink in this client.
      hr = pConnPoint->Advise(m_pCOPaperSink, &dwKey);
      if (SUCCEEDED(hr))
        m_dwPaperSink = dwKey;

      RELEASE_INTERFACE(pConnPoint);
    }
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiPaper::DisconnectPaperSink

  Summary:  Disconnect the PaperSink from the server COPaper source.

  Args:     void.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiPaper::DisconnectPaperSink(void)
{
  HRESULT hr = E_FAIL;
  IConnectionPoint* pConnPoint;

  if (m_dwPaperSink)
  {
    // Get the Paper Sink connection point.
    pConnPoint = GetConnectionPoint(IID_IPaperSink);
    if (NULL != pConnPoint)
    {
      // Disconnect the object in the server from the Paper Sink in
      // this client.
      hr = pConnPoint->Unadvise(m_dwPaperSink);
      if (SUCCEEDED(hr))
        m_dwPaperSink = 0;

      RELEASE_INTERFACE(pConnPoint);
    }
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiPaper::Load

  Summary:  Load drawing data from the current compound file (local
            or remote).

  Args:     void.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiPaper::Load(void)
{
  HRESULT hr = E_FAIL;
  HCURSOR hCurWait = LoadCursor(NULL, IDC_WAIT);
  HCURSOR hCurPrev;
  RECT WinRect;

  if (NULL != m_pISharePaper)
  {
    // Change cursor to the hour glass.
    hCurPrev = SetCursor(hCurWait);

    // Ask the COPaper object to load the paper data from its
    // current compound file.
    m_bPainting = TRUE;
    hr = m_pISharePaper->Load(&WinRect);
    m_bPainting = FALSE;
    if (SUCCEEDED(hr))
    {
      if (WinRect.right == m_WinRect.right
          || WinRect.bottom == m_WinRect.bottom)
        PaintWin();
      else
      {
        m_WinRect.right = WinRect.right;
        m_WinRect.bottom = WinRect.bottom;
        hr = ResizeWin(m_WinRect.right, m_WinRect.bottom);
      }
      m_bDirty = FALSE;
    }

    // Set Cursor back to what it was.
    SetCursor(hCurPrev);
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiPaper::LoadLocal

  Summary:  Load drawing data from the local DCDSERVE server.

  Args:     void.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiPaper::LoadLocal(void)
{
  HRESULT hr;
  BOOL bFirst;

  // Make sure we unlock the paper object.
  Lock(FALSE);

  // Disconnect all Sinks--currently only one: PaperSink. This
  // officially stops all PaperSink notifications.
  hr = DisconnectPaperSink();

  // Release the main interface pointer copy held in CGuiPaper.
  // This causes destruction (in the server) of the current
  // COPaper object.
  RELEASE_INTERFACE(m_pISharePaper);

  // Call COM service to create a new COPaper instance. We are
  // not aggregating it so we ask for its IShare Paper interface
  // directly.
  hr = CoCreateInstance(
         CLSID_SharePaper,
         NULL,
         CLSCTX_LOCAL_SERVER,
         IID_ISharePaper,
         (PPVOID)&m_pISharePaper);
  if (SUCCEEDED(hr))
  {
    // Init the COPaper object.
    GetClientRect(m_hWnd, &m_WinRect);
    hr = m_pISharePaper->InitPaper(&m_WinRect, &bFirst);
    if (SUCCEEDED(hr))
    {
      // Reconnect all Sinks--currently only one: PaperSink.
      // This restores all PaperSink notifications.
      hr = ConnectPaperSink();
      if (SUCCEEDED(hr))
      {
        if (bFirst)
        {
          // Lock and load.
          Lock(TRUE);
          hr = Load();
        }
        else
        {
          Lock(FALSE);
          // If this is not first init then resize this client's window
          // to match what the COPaper object is using for its size.
          hr = ResizeWin(m_WinRect.right, m_WinRect.bottom);
          PaintWin();
        }
      }
    }
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiPaper::LoadRemote

  Summary:  Load the shared drawing from a DCDSERVE server on a remote
            machine that the user specifies by name in a dialog.

  Args:     void

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiPaper::LoadRemote(void)
{
  HRESULT hr = NOERROR;
  BOOL bFirst;
  COPaperSink* pCobSink = NULL;
  HCURSOR hCurPrev;
  HCURSOR hCurWait = LoadCursor(NULL, IDC_WAIT);
  COSERVERINFO* pServerInfo = &g_ServerInfo;
  MULTI_QI qiRes;
  int iAns;
  CDlgLoadRemote dlgLoadRemote;

  // Ask user for the remote machine name. Cancel this whole load if
  // he cancels the dialog.
  iAns = dlgLoadRemote.ShowDialog(
           m_hInst,
           MAKEINTRESOURCE(IDD_LOAD_REMOTE),
           m_hWnd);
  // Ensure a remote machine name was specified by user.
  if (IDOK == iAns && pServerInfo->pwszName[0])
  {
    hr = E_FAIL;
    // Unload the existing COPaper object.
    if (m_pISharePaper)
    {
      // Ask User if save is desired.
      AskSave();

      // Change cursor to the hour glass.
      hCurPrev = SetCursor(hCurWait);

      // Clear the window of the previous drawing.
      ClearWin();

      // Make sure we unlock the paper object.
      Lock(FALSE);

      // Disconnect all Sinks--currently only one: PaperSink. This
      // officially stops all PaperSink notifications.
      hr = DisconnectPaperSink();

      // Release the main interface pointer copy held in CGuiPaper.
      // This causes destruction (in the server) of the current
      // COPaper object.
      RELEASE_INTERFACE(m_pISharePaper);
    }

    // Load a new COPaper from the server on a user-specifed remote machine.

    // Call COM service to create an instance of the remote COPaper
    // COM object. We are not aggregating this new object (viz, the
    // NULL parameter), so we ask for its IShareDraw interface directly.
    qiRes.pIID = &IID_ISharePaper;
    qiRes.pItf = NULL;
    qiRes.hr = 0;
    hr = CoCreateInstanceEx(
           CLSID_SharePaper,
           NULL,
           CLSCTX_REMOTE_SERVER,
           pServerInfo,
           1,
           &qiRes);
    if (SUCCEEDED(hr))
    {
      hr = qiRes.hr;
      if (SUCCEEDED(hr))
      {
        // Grab our copy of the returned interface pointer. An AddRef was
        // done by CoCreateInstanceEx on this interface pointer.
        m_pISharePaper = (ISharePaper*)qiRes.pItf;

        // Init the newly created COPaper object.
        GetClientRect(m_hWnd, &m_WinRect);
        hr = m_pISharePaper->InitPaper(&m_WinRect, &bFirst);
        if (SUCCEEDED(hr))
        {
          // Reconnect all Sinks--currently only one: PaperSink.
          // This restores all PaperSink notifications.
          hr = ConnectPaperSink();
          if (SUCCEEDED(hr))
          {
            if (bFirst)
            {
              // Lock and load.
              Lock(TRUE);
              hr = Load();
            }
            else
            {
              Lock(FALSE);
              // If this is not first init then resize this client's
              // window to match what the remote COPaper object is
              // using for its window size.
              hr = ResizeWin(m_WinRect.right, m_WinRect.bottom);
            }
            PaintWin();
          }
        }
      }
    }

    if (FAILED(hr))
    {
      HrMsg(m_hWnd, TEXT(REMOTE_CREATE_ERR_STR), hr);

      // If error with remote load then restore local drawing.
      hr = LoadLocal();
    }

    // Set Cursor back to what it was.
    SetCursor(hCurPrev);
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiPaper::Save

  Summary:  Calls on COPaper to save the current drawing's paper data in
            its current compound file.

  Args:     void.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiPaper::Save(void)
{
  HRESULT hr = E_FAIL;
  HCURSOR hCurWait = LoadCursor(NULL, IDC_WAIT);
  HCURSOR hCurPrev;

  if (NULL != m_pISharePaper)
  {
    // Change cursor to the hour glass.
    hCurPrev = SetCursor(hCurWait);

    // Ask the COPaper object to save itself to its current compound file.
    hr = m_pISharePaper->Save();
    if (SUCCEEDED(hr))
      m_bDirty = FALSE;

    // Set Cursor back to what it was.
    SetCursor(hCurPrev);
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiPaper::AskSave

  Summary:  Checks dirty flag (ie, if current displayed paper data was
            modified and is out of sync with the paper data stored in a
            compound file). If dirty, then ask user in simple dialog if he
            wants to save new data. If he says yes, then save the current
            paper data into the current compound file.

  Args:     void.

  Returns:  INT
              Value returned from the Win32 MessageBox function.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
INT CGuiPaper::AskSave(void)
{
  int iAns = IDNO;
  TCHAR szTitle[MAX_STRING_LENGTH];
  TCHAR szAsk[MAX_STRING_LENGTH];
  TCHAR szMsg[MAX_PATH + MAX_STRING_LENGTH];

  // If current data is dirty then ask user if he wants to save it.
  if (m_bDirty)
  {
    if (LoadString(m_hInst, IDS_DRAWING_CHANGED, szTitle, MAX_STRING_LENGTH)
        && LoadString(m_hInst, IDS_ASK_SAVE, szAsk, MAX_STRING_LENGTH))
    {
      lstrcpy(szMsg, TEXT(MAIN_WINDOW_TITLE_STR));
      lstrcat(szMsg, szAsk);
      // Display AskSaveDlg to user. Ask if he wants to save.
      iAns = MessageBox(
               m_hWnd,
               szMsg,
               szTitle,
               MB_YESNOCANCEL | MB_ICONEXCLAMATION);
      if (IDYES == iAns)
      {
        // Tell COPaper to save itself to its current compound file.
        Save();
      }
    }
  }

  return iAns;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiPaper::PickColor

  Summary:  Uses the Choose Color common dialog to ask user for new
            Pen color. Return that new color.

  Args:     void.

  Returns:  COLORREF
              New chosen color.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
COLORREF CGuiPaper::PickColor(void)
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
