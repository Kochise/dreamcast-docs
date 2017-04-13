/*+==========================================================================
  File:      LISTWIN.CPP

  Summary:   Implementation of the C++ object that encapsulates the
             list box control window that displays the page list.

  Classes:   CListWin.

  Functions: none.

  Origin:    5-24-97: atrent - Editor Inheritance from CMsgLog in
             APPUTIL.CPP.

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

/*---------------------------------------------------------------------------
  We include WINDOWS.H for all Win32 applications.
  We include TCHAR.H for general Unicode/Ansi prototype of utility
    functions like wvsprintf.
  We include APPUTIL.H because we will be building this application using
    the convenient Virtual Window and Dialog classes and other
    utility functions in the APPUTIL Library (ie, APPUTIL.LIB).
  We include LISTWIN.H for the defines and the CListWin class declaration
    needed in LISTWIN.
---------------------------------------------------------------------------*/
#include <windows.h>
#include <tchar.h>
#include <apputil.h>
#include "listwin.h"


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CListWin::Create

  Summary:  Creates the ListBox as a child window to fill the client area
            of the specified parent window or to exist as a separate
            window owned by the parent window.

  Args:     HINSTANCE hInst,
              Instance handle of the application.
            HWND hWndparent,
              Window handle for the parent window of the listbox.
            BOOL bSeparate)
              Flag to create the listbox as a separate window.  FALSE
              means fit the child window to fill the client area of the
              parent window. TRUE means the window is a separate (but
              owned) window.

  Returns:  BOOL
              TRUE if successful; FALSE if not.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
BOOL CListWin::Create(
       HINSTANCE hInst,
       HWND hWndParent,
       BOOL bSeparate)
{
  BOOL bResult = FALSE;
  HWND hWnd;
  RECT rect;
  DWORD dwStyle = WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | LBS_NOTIFY |
                    LBS_NOINTEGRALHEIGHT;
  TCHAR* pszTitle = bSeparate ? TEXT("Page List") : NULL;

  dwStyle |= bSeparate ? WS_OVERLAPPEDWINDOW : WS_CHILD;

  if (IsWindow(hWndParent))
  {
    GetClientRect(hWndParent, &rect);

    // Create the ListBox window.
    hWnd = ::CreateWindowEx(
               0,                // Extended Window Style
               TEXT("LISTBOX"),  // Class Name
               pszTitle,         // Window Title
               dwStyle,          // The window style
               0,                // (x,y)=Upper left of Parent window
               0,
               rect.right,       // Width; Fill Client Window
               rect.bottom,      // Height
               hWndParent,       // Parent Window Handle
               (HMENU) IDC_LISTWIN, // No menu but rig ID for notifications.
               hInst,            // App Instance Handle
               NULL);            // Window Creation Data

    if (NULL != hWnd)
    {
      // Remember the window handle of this listbox window.
      m_hWnd = hWnd;
      // Remember the instance of this application.
      m_hInst = hInst;
      // Remember if this is a separate window (bSeparate==TRUE).
      m_bSeparate = bSeparate;
      // Return success.
      bResult = TRUE;
    }
  }

  return (bResult);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CListWin::SetCurSel

  Summary:  Sets the current selection to the specified list item. Also
            sets keyboard focus to the ListWin listbox.

  Args:     INT iIndex
              Zero-based Listbox Index of the selection to set.

  Returns:  BOOL
              TRUE.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
BOOL CListWin::SetCurSel(
       INT iIndex)
{
  BOOL bOk = FALSE;

  if (IsWindow(m_hWnd))
  {
    iIndex = ::SendMessage(
                 m_hWnd,
                 LB_SETCURSEL,
                 iIndex,
                 0);
    if (LB_ERR != iIndex && iIndex >= 0)
    {
      ::SetFocus(m_hWnd);
      bOk = TRUE;
    }
  }

  return bOk;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CListWin::GetCurSel

  Summary:  Gets the index (page number) of the current listbox selection.

  Args:     INT* piPage
              Address of output INT Page number variable.

  Returns:  BOOL
              TRUE.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
BOOL CListWin::GetCurSel(
       INT* piPage)
{
  BOOL bOk = FALSE;
  INT iIndex;

  if (IsWindow(m_hWnd))
  {
    iIndex = ::SendMessage(
                 m_hWnd,
                 LB_GETCURSEL,
                 0,
                 0);
    if (LB_ERR != iIndex && iIndex >= 0)
    {
      *piPage = iIndex;
      bOk = TRUE;
    }
  }

  return bOk;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CListWin::AddFmt

  Summary:  Add a printf-style formatted message as a separate line in the
            ListWin listbox.

  Args:     LPTSTR szFmt
              The format/message string to control the display line.
            [...]
              Arguments to match those specified in the format string.

  Returns:  BOOL
              TRUE if successful; FALSE if not.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
BOOL CListWin::AddFmt(
       LPTSTR szFmt,
       ...)
{
  BOOL bResult = FALSE;
  va_list arglist;
  va_start(arglist, szFmt);
  TCHAR szLine[MAX_STRING_LENGTH];
  INT iIndex;

  // Use the format string and arguments to format the line text.
  wvsprintf(szLine, szFmt, arglist);

  // Send the newly formated message string to the ListWin listbox.
  if (IsWindow(m_hWnd))
  {
    ::SendMessage(
        m_hWnd,
        LB_ADDSTRING,
        0,
        (LPARAM)szLine);
    iIndex = ::SendMessage(
                 m_hWnd,
                 LB_GETCOUNT,
                 0,
                 0);
    if (LB_ERR != iIndex && iIndex > 0)
    {
      --iIndex;
      ::SendMessage(
          m_hWnd,
          LB_SETCURSEL,
          (WPARAM)iIndex,
          0);
    }
    bResult = TRUE;
  }

  return (bResult);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CListWin::InsertFmt

  Summary:  Insert a printf-style formatted entry as a separate line in
            the ListWin listbox at the given index.

  Args:     SHORT nIndex,
              Index in the Listbox at which to perform the insert.
            LPTSTR szFmt
              The format/message string to control the display line.
            [...]
              Arguments to match those specified in the format string.

  Returns:  BOOL
              TRUE if successful; FALSE if not.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
BOOL CListWin::InsertFmt(
       INT iIndex,
       LPTSTR szFmt,
       ...)
{
  BOOL bResult = FALSE;
  va_list arglist;
  va_start(arglist, szFmt);
  TCHAR szLine[MAX_STRING_LENGTH];
  INT iNewItem;

  // Use the format string and arguments to format the line text.
  wvsprintf(szLine, szFmt, arglist);

  // Send the newly formated message string to the ListWin Listbox.
  if (IsWindow(m_hWnd))
  {
    iNewItem = ::SendMessage(
                   m_hWnd,
                   LB_INSERTSTRING,
                   iIndex,
                   (LPARAM)szLine);
    if (LB_ERR != iNewItem && iNewItem > 0)
    {
      ::SendMessage(
          m_hWnd,
          LB_SETCURSEL,
          (WPARAM)iNewItem,
          0);
    }
    bResult = TRUE;
  }

  return (bResult);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CListWin::Resize

  Summary:  Resizes the listbox to a new width and height.  Called during
            the parent window's WM_SIZE to fit the listbox to the client
            area of the parent window.  It only honors this request if it
            is an integral child window.

  Args:     INT nWidth
              New width in pixels of the listbox.
            INT nHeight
              New height in pixels of the listbox.

  Returns:  BOOL
              TRUE if successful; FALSE if not.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
BOOL CListWin::Resize(
       INT nWidth,
       INT nHeight)
{
  BOOL bResult = FALSE;

  if (!m_bSeparate)
    bResult = ::MoveWindow(m_hWnd, 0, 0, nWidth, nHeight, TRUE);

  return (bResult);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CListWin::Clear

  Summary:  Clears all displayh lines from the ListWin listbox.

  Args:     void

  Returns:  BOOL
              TRUE.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
BOOL CListWin::Clear(
       void)
{
  if (IsWindow(m_hWnd))
    ::SendMessage(
        m_hWnd,
        LB_RESETCONTENT,
        0,
        0);

  return (TRUE);
}
