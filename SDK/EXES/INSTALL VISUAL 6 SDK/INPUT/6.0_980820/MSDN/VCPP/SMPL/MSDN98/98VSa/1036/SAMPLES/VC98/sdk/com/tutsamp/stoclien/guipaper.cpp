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
             as a COM object in a separate thread-safe In-process server,
             STOSERVE.

             For a comprehensive tutorial code tour of GUIPAPER's contents
             and offerings see the tutorial STOCLIEN.HTM file. For more
             specific technical details on the internal workings see the
             comments dispersed throughout the GUIPAPER source code.

  Classes:   CGuiPaper.

  Origin:    6-10-96: atrent - Editor inheritance from GUIBALL.CPP in the
             CONCLIEN source.

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
  We include IPAPER.H and PAPGUIDS.H for the common Paper-related Interface
    class, GUID, and CLSID specifications.
  We include PAPFILE.H because it has the C++ class used for compound file
    storage of Drawing Paper Data.
  We include GUIPAPER.H because it has the C++ class used for GUI display
    of the drawing Paper.
  We include SINK.H because it has the C++ class used for the sink that
    receives event notifications from the COPaper object in the server.
  We include STOCLIEN.H because it has class and resource definitions
    specific to this STOCLIEN application.
---------------------------------------------------------------------------*/
#include <windows.h>
#include <ole2.h>
#include <olectl.h>
#include <commdlg.h>
#include <tchar.h>
#include <apputil.h>
#include <ipaper.h>
#include <papguids.h>
#include "papfile.h"
#include "guipaper.h"
#include "sink.h"
#include "stoclien.h"


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiPaper::CGuiPaper

  Summary:  Constructor.

  Args:     void

  Modifies: ...

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CGuiPaper::CGuiPaper(void)
{
  m_hWnd       = NULL;
  m_hInst      = NULL;
  m_hDC        = NULL;
  m_pIPaper    = NULL;
  m_nLockKey   = 0;
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
  m_pPapFile   = NULL;

  // Init the file name for title display to <MyModule>.<EXT>.
  if (GetModuleFileName(m_hInst, m_szFileName, MAX_PATH))
  {
    _tsplitpath(m_szFileName, NULL, NULL, m_szFileTitle, NULL);
    lstrcat(m_szFileTitle, TEXT(PAP_FILE_EXT));
  }

  // Ensure the m_szFileName OFN member variable string is NULL.
  m_szFileName[0] = 0;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiPaper::~CGuiPaper

  Summary:  Destructor.

  Args:     void

  Modifies: ...

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CGuiPaper::~CGuiPaper(void)
{
  BOOL bOk = TRUE;

  if (m_pIPaper)
  {
    // Make sure we unlock the paper object.
    m_pIPaper->Unlock(m_nLockKey);

    // Just to make sure, turn off Ink Saving.
    m_bInkSaving = FALSE;

    // Disconnect all Sinks--currently only one: PaperSink. This officially
    // stops all PaperSink notifications.
    DisconnectPaperSink();

    // Delete the Pen object.
    if (m_hPen)
      DeleteObject(m_hPen);

    // Release the reference to the PaperSink object.
    RELEASE_INTERFACE(m_pCOPaperSink);

    // Release the main interface pointer copy held in CGuiPaper.
    RELEASE_INTERFACE(m_pIPaper);

    // Delete the CPapFile object.
    DELETE_POINTER(m_pPapFile);
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
            TCHAR* pszCmdLineFile)
              Pointer to file name for an initial file to load that was
              specified on the app command line.

  Modifies: ...

  Returns:  BOOL
              TRUE for success; FALSE for fail.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
BOOL CGuiPaper::Init(
       HINSTANCE hInst,
       HWND hWnd,
       TCHAR* pszCmdLineFile)
{
  BOOL bOk = FALSE;
  HRESULT hr;
  BOOL bFirst;
  COPaperSink* pCob = NULL;
  HCURSOR hCurPrev;
  HCURSOR hCurWait = LoadCursor(NULL, IDC_WAIT);

  if (hInst && hWnd)
  {
    m_hInst = hInst;
    m_hWnd = hWnd;

    // Get and save our private display Device Context.
    m_hDC = GetDC(m_hWnd);

    // Change cursor to the hour glass. Init could take awhile.
    hCurPrev = SetCursor(hCurWait);

    // Fill in the Open File Name Common Dialog's OPENFILENAME structure.
    m_ofnFile.lStructSize = sizeof(OPENFILENAME);
    m_ofnFile.hwndOwner = hWnd;
    m_ofnFile.hInstance = hInst;
    m_ofnFile.lpstrCustomFilter = NULL;
    m_ofnFile.nMaxCustFilter = 0;
    m_ofnFile.nFilterIndex = 1;
    m_ofnFile.lpstrFile = m_szFileName;
    m_ofnFile.nMaxFile = MAX_PATH;
    m_ofnFile.lpstrInitialDir = TEXT(".");
    m_ofnFile.lpstrFileTitle = m_szFileTitle;
    m_ofnFile.nMaxFileTitle = MAX_PATH;
    m_ofnFile.lpstrDefExt = TEXT(PAP_EXT);

    if (LoadString(m_hInst, IDS_OFN_PAPFILES, m_szFileFilter, MAX_PATH))
      m_ofnFile.lpstrFilter = m_szFileFilter;
    else
      m_ofnFile.lpstrFilter = TEXT(OFN_DEFAULTFILES_STR);

    // Call COM service to create a COPaper instance. We are not
    // aggregating it so we ask for its IPaper interface directly.
    hr = CoCreateInstance(
           CLSID_DllPaper,
           NULL,
           CLSCTX_INPROC_SERVER,
           IID_IPaper,
           (PPVOID)&m_pIPaper);
    if (SUCCEEDED(hr))
    {
      // Init the COPaper object.
      GetClientRect(hWnd, &m_WinRect);
      hr = m_pIPaper->InitPaper(&m_WinRect, &bFirst);
      if (SUCCEEDED(hr))
      {
        // We can now allow ink saving.
        m_bInkSaving = TRUE;

        // If this is not first init then resize this client's window to
        // match what the COPaper object is using for its size.
        if (!bFirst)
          SetWindowPos(
            m_hWnd,
            HWND_TOP,
            0,
            0,
            m_WinRect.right,
            m_WinRect.bottom,
            SWP_NOMOVE | SWP_NOZORDER);

        // Create the PapFile object so we can store paper data in
        // compound files.
        m_pPapFile = new CPapFile;
        if (NULL != m_pPapFile)
        {
          if (FileExist(pszCmdLineFile))
          {
            // If the user specified a file name on the app's command
            // invocation line then use that name if it actually refers
            // to an existing file. If not then ignore it.
            lstrcpy(m_szFileName, pszCmdLineFile);
            lstrcpy(m_szFileTitle, pszCmdLineFile);
          }
          else
          {
            // Build a path to where the default application .PAP file
            // should be. It should be in the same directory as the .EXE
            // as the appname with an .PAP extension.
            MakeFamilyPath(m_hInst, m_szFileName, TEXT(PAP_FILE_EXT));
          }

          // Init the CPapFile object. Init will do the AddRef on the
          // m_pIPaper copy that is passed.
          hr = m_pPapFile->Init(m_szFileName, m_pIPaper);
          if (SUCCEEDED(hr))
          {
            // Create the COPaperSink object to receive COPaper events.
            pCob = new COPaperSink(NULL, this);
            if (NULL != pCob)
            {
              // Save a pointer to the COPaperSink IUnknown interface.
              // AddRef because of this saved copy.
              m_pCOPaperSink = pCob;
              m_pCOPaperSink->AddRef();
            }
            else
              hr = E_OUTOFMEMORY;
          }
        }
        else
          hr = E_OUTOFMEMORY;
      }

      bOk = SUCCEEDED(hr);
    }

    // Set Cursor back to what it was.
    SetCursor(hCurPrev);
  }

  return (bOk);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiPaper::DrawOn

  Summary:  Lock the paper object for drawing by this client.

  Args:     void.

  Modifies: ...

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiPaper::DrawOn(void)
{
  HRESULT hr;

  // If we are not already locked for drawing then do so.
  if (!m_nLockKey)
    hr = m_pIPaper->Lock(&m_nLockKey);

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiPaper::DrawOff

  Summary:  Unlock the paper object for drawing by this client.

  Args:     void.

  Modifies: ...

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiPaper::DrawOff(void)
{
  HRESULT hr = NOERROR;

  // If we are not already unlocked for drawing then do so.
  if (m_nLockKey)
  {
    hr = m_pIPaper->Unlock(m_nLockKey);
    if (SUCCEEDED(hr))
      m_nLockKey = 0;
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiPaper::ClearWin

  Summary:  Clear display window but don't erase drawn data.

  Args:     void.

  Modifies: ...

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
  Method:   CGuiPaper::PaintWin

  Summary:  Clears window background and repaints the current drawing
            on the paper. Relies on connectable object technology.
            The Redraw method in the COPaper object sends event
            notifications to this client in order to achieve a
            repaint of the drawing.  CGuiPaper does not have a copy of
            the drawing data--only the COPaper component in the server
            has that.

  Args:     void

  Modifies: ...

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiPaper::PaintWin(void)
{
  HRESULT hr = E_FAIL;
  COLORREF crInkColor;
  SHORT nInkWidth;

  if (m_pIPaper && !m_bPainting && !m_bInking)
  {
    m_bPainting = TRUE;
    // Save and restore ink color and width since redraw otherwise
    // ends up changing these values in CGuiPaper.
    crInkColor = m_crInkColor;
    nInkWidth = m_nInkWidth;
    hr = m_pIPaper->Redraw(m_nLockKey);
    m_nInkWidth = nInkWidth;
    m_crInkColor = crInkColor;
    m_bPainting = FALSE;
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiPaper::Erase

  Summary:  Erase content of the drawing paper and clear display window.

  Args:     void.

  Modifies: ...

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiPaper::Erase(void)
{
  HRESULT hr = E_FAIL;

  if(m_nLockKey)
  {
    if (m_pIPaper)
      hr = m_pIPaper->Erase(m_nLockKey);
    if (SUCCEEDED(hr))
    {
      ClearWin();
      m_bDirty = TRUE;
    }
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiPaper::Resize

  Summary:  Resizes current drawing paper rectangle.

  Args:     WORD wWidth
              New window width. Max X coord.
            WORD wHeight
              New window height. Max Y coord.

  Modifies: ...

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiPaper::Resize(
                     WORD wWidth,
                     WORD wHeight)
{
  if(m_nLockKey)
  {
    // Store the new window size and mark dirty.
    m_WinRect.right = wWidth;
    m_WinRect.bottom = wHeight;
    m_bDirty = TRUE;
  }

  return NOERROR;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiPaper::InkSaving

  Summary:  Tell CGuiPaper whether ink data is being saved in the Paper
            object.

  Args:     BOOL bInkSaving
              TRUE means save in COPaper object; FALSE means not.

  Modifies: ...

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiPaper::InkSaving(
                     BOOL bInkSaving)
{
  m_bInkSaving = bInkSaving;

  return NOERROR;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiPaper::InkWidth

  Summary:  Changes current ink width.

  Args:     SHORT nInkWidth
              New ink width in pixels.

  Modifies: ...

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiPaper::InkWidth(
                     SHORT nInkWidth)
{
  if (nInkWidth)
    m_nInkWidth = nInkWidth;

  return NOERROR;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiPaper::InkColor

  Summary:  Changes current ink color.

  Args:     COLORREF crInkColor
              RGB color ref value (eg, RGB(0,0,0) is black).

  Modifies: ...

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

  Modifies: ...

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiPaper::InkStart(
                     SHORT nX,
                     SHORT nY)
{
  HRESULT hr = E_FAIL;

  if (m_nLockKey || (!m_nLockKey && !m_bInkSaving))
  {
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
      if (m_pIPaper && m_bInkSaving)
      {
        hr = m_pIPaper->InkStart(
                          m_nLockKey,
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

  Modifies: ...

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
      m_pIPaper->InkDraw(m_nLockKey, nX, nY);
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

  Modifies: ...

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
      m_pIPaper->InkStop(m_nLockKey, nX, nY);
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

  Modifies: ...

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
  hr = m_pIPaper->QueryInterface(
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

  Modifies: ...

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

  Modifies: ...

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

  Summary:  Load paper data from the current compound file.

  Args:     void.

  Modifies: ...

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiPaper::Load(void)
{
  HRESULT hr = E_FAIL;
  HCURSOR hCurWait = LoadCursor(NULL, IDC_WAIT);
  HCURSOR hCurPrev;
  TCHAR szTitle[MAX_PATH + 32];

  if (NULL != m_pPapFile)
  {
    // Change cursor to the hour glass.
    hCurPrev = SetCursor(hCurWait);

    // Ask the PapFile object to load the paper data from current compound
    // file.
    hr = m_pPapFile->Load(m_nLockKey, NULL);
    if (SUCCEEDED(hr))
    {
      // Set Main Window Title.
      lstrcpy(szTitle, TEXT(MAIN_APP_NAME_STR));
      lstrcat(szTitle, m_szFileTitle);
      SetWindowText(m_hWnd, szTitle);
      m_bDirty = FALSE;
    }

    // Set Cursor back to what it was.
    SetCursor(hCurPrev);
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiPaper::Save

  Summary:  Calls on CPapFile to save the current drawing's paper data in
            the current compound file.

  Args:     void.

  Modifies: ...

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiPaper::Save(void)
{
  HRESULT hr = E_FAIL;
  HCURSOR hCurWait = LoadCursor(NULL, IDC_WAIT);
  HCURSOR hCurPrev;

  if (NULL != m_pPapFile)
  {
    // Change cursor to the hour glass.
    hCurPrev = SetCursor(hCurWait);

    // Ask the PapFile object to save itself. NULL for file name means
    // save current file.
    hr = m_pPapFile->Save(m_nLockKey, NULL);
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
      lstrcpy(szMsg, m_szFileName);
      lstrcat(szMsg, szAsk);
      // Display AskSaveDlg to user. Ask if he wants to save.
      iAns = MessageBox(
               m_hWnd,
               szMsg,
               szTitle,
               MB_YESNOCANCEL | MB_ICONEXCLAMATION);
      if (IDYES == iAns)
      {
        // Tell CPapFile to save itself to the current compound file.
        Save();
      }
    }
  }

  return iAns;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiPaper::Open

  Summary:  If current data has been modified then ask user if he wants to
            first save it to the current file. Then use Open File Name
            common dialog to ask user for a new file name to load. If user
            chooses a file name then load the paper data from that
            compound file.

  Args:     void.

  Modifies: ...

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiPaper::Open(void)
{
  HRESULT hr = NOERROR;
  TCHAR szFileName[MAX_PATH];
  TCHAR szTitle[MAX_PATH];
  HCURSOR hCurWait = LoadCursor(NULL, IDC_WAIT);
  HCURSOR hCurPrev;
  BOOL bOpen;

  // If current data is dirty then ask user if he wants to save it first.
  if (IDCANCEL != AskSave())
  {
    // Use the Open File Name common dialog to get file name from user.
    // Set the dialog's file filter and title.
    szFileName[0] = 0;
    m_ofnFile.lpstrFile = szFileName;
    if (LoadString(m_hInst, IDS_OFN_PAPOPEN, szTitle, sizeof(szTitle)))
      m_ofnFile.lpstrTitle = szTitle;
    m_ofnFile.Flags = OFN_HIDEREADONLY | OFN_FILEMUSTEXIST;

    // Call up the dialog to get a file name from the user.
    m_bPainting = TRUE;
    bOpen = GetOpenFileName(&m_ofnFile);
    m_bPainting = FALSE;
    if (bOpen)
    {
      // Change cursor to the hour glass.
      hCurPrev = SetCursor(hCurWait);

      // Tell CPapFile object to load the paper data from the newly
      // chosen compound file.
      hr = m_pPapFile->Load(m_nLockKey, szFileName);
      if (SUCCEEDED(hr))
      {
        // Remember the new current compound file name.
        lstrcpy(m_szFileName, szFileName);

        // Set Main Window Title.
        lstrcpy(szFileName, TEXT(MAIN_APP_NAME_STR));
        lstrcat(szFileName, m_szFileTitle);
        SetWindowText(m_hWnd, szFileName);

        m_bDirty = FALSE;
      }

      // Set Cursor back to what it was.
      SetCursor(hCurPrev);
    }
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiPaper::SaveAs

  Summary:  Use the File SaveAs common dialog to ask user for a new file
            name to save to. Then save the current paper data to the
            specified compound file. That file becomes the new current
            file. The previously open file is left unchanged since the
            last save to it.

  Args:     void.

  Modifies: ...

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiPaper::SaveAs(void)
{
  HRESULT hr = E_FAIL;
  TCHAR szFileName[MAX_PATH];
  TCHAR szTitle[MAX_PATH];
  HCURSOR hCurWait = LoadCursor(NULL, IDC_WAIT);
  HCURSOR hCurPrev;
  BOOL bOpen;

  // Use the File Save As common dialog to get file name from user.
  // Set the dialog's file filter and title.
  szFileName[0] = 0;
  m_ofnFile.lpstrFile = szFileName;
  if (LoadString(m_hInst, IDS_OFN_PAPSAVE, szTitle, sizeof(szTitle)))
    m_ofnFile.lpstrTitle = szTitle;
  m_ofnFile.Flags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;

  // Call up the dialog to get a file name from the user.
  m_bPainting = TRUE;
  bOpen = GetSaveFileName(&m_ofnFile);
  m_bPainting = FALSE;
  if (bOpen)
  {
    // Change cursor to the hour glass.
    hCurPrev = SetCursor(hCurWait);

    // Tell CPapFile object to save the paper data to the newly
    // chosen compound file.
    hr = m_pPapFile->Save(m_nLockKey, szFileName);
    if (SUCCEEDED(hr))
    {
      // Remember the new current compound file name.
      lstrcpy(m_szFileName, szFileName);

      // Set Main Window Title.
      lstrcpy(szFileName, TEXT(MAIN_APP_NAME_STR));
      lstrcat(szFileName, m_szFileTitle);
      SetWindowText(m_hWnd, szFileName);

      m_bDirty = FALSE;
    }

    // Set Cursor back to what it was.
    SetCursor(hCurPrev);
  }

  return hr;
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
