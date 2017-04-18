/*+==========================================================================
  File:      TEXTWIN.CPP

  Summary:   Implementation of the CTextWin C++ object that encapsulates
             the the text edit control window used to edit text pages.

  Classes:   CTextWin.

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
  We include TEXTWIN.H for the defines and the CTextWin class
    declaration needed in TEXTWIN.
---------------------------------------------------------------------------*/
#include <windows.h>
#include <tchar.h>
#include <apputil.h>
#include "textwin.h"


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CTextWin::CTextWin

  Summary:  CTextWin Constructor.

  Args:     .

  Returns:  .
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CTextWin::CTextWin()
{
  m_hInst = NULL;
  m_hWnd = NULL;
  m_wWidth = 0;
  m_wHeight = 0;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CMainWindow::~CMainWindow

  Summary:  CMainWindow Destructor.

  Args:     .

  Returns:  .
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CTextWin::~CTextWin()
{
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CTextWin::Init

  Summary:  Initializes the Text Edit Control Window. Creates this window
            as a child window and fits it to fill the client area of the
            specified parent window.

  Args:     HINSTANCE hInst,
              Instance handle of the application.
            HWND hWndparent,
              Window handle for the parent window of the listbox.
            HWND* phWndEdit)
              Address of variable that is assigned the window handle
              of the new text window (edit control window).

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CTextWin::Init(
          HINSTANCE hInst,
          HWND hWndParent,
          HWND* phWndEdit)
{
  HRESULT hr = E_FAIL;
  BOOL bResult = FALSE;
  HWND hWnd;
  RECT rect;
  DWORD dwStyle = WS_VISIBLE | WS_CHILD | WS_VSCROLL | ES_MULTILINE
                  | ES_LEFT | ES_AUTOVSCROLL | ES_AUTOHSCROLL;

  if (IsWindow(hWndParent))
  {
    GetClientRect(hWndParent, &rect);

    // Create the edit control window.
    hWnd = ::CreateWindowEx(
               0,                // Extended Window Style
               TEXT("EDIT"),     // Class Name
               NULL,             // Window Title
               dwStyle,          // The window style
               0,                // (x,y)=Upper left of Parent window
               0,
               rect.right,       // Width; Fill Client Window
               rect.bottom,      // Height
               hWndParent,       // Parent Window Handle
               (HMENU) IDC_TEXTWIN, // No menu but rig ID for notifications.
               hInst,            // App Instance Handle
               NULL);            // Window Creation Data
    if (NULL != hWnd)
    {
      // Set keyboard focus to this TextWin edit control.
      SetFocus(hWnd);
      // Remember the instance of this application.
      m_hInst = hInst;
      // Remember the window handle of this edit window.
      m_hWnd = hWnd;
      // Assign the window handle to the caller's variable.
      if (NULL != phWndEdit)
        *phWndEdit = hWnd;
      // Return success.
      hr = NOERROR;
    }
  }

  return (hr);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CTextWin::GetLength

  Summary:  Gets the length of the text content in the edit control.

  Args:     INT* piTextLength
              Address of INT variable that is assigned the length.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CTextWin::GetLength(
          INT* piTextLength)
{
  HRESULT hr = E_POINTER;
  INT iLen;

  if (NULL != piTextLength)
  {
    // Set output in case of error.
    *piTextLength = 0;

    hr = E_FAIL;
    if (IsWindow(m_hWnd))
    {
      iLen = ::SendMessage(m_hWnd, WM_GETTEXTLENGTH, 0, 0);

      if (iLen >= 0)
      {
        // Assign caller's variable.
        *piTextLength = iLen;
        hr = NOERROR;
      }
    }
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CTextWin::GetText

  Summary:  Gets the text content of the edit control.

  Args:     WCHAR* pwszText
              Address of output string buffer that is assigned the text.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CTextWin::GetText(
          WCHAR* pwszText)
{
  HRESULT hr = E_POINTER;
  INT iTextLength;

  if (NULL != pwszText)
  {
    // Set output in case of error.
    pwszText[0] = 0;

    if (IsWindow(m_hWnd))
    {
      hr = GetLength(&iTextLength);
      if (SUCCEEDED(hr) && iTextLength >= 0)
      {
#if defined(UNICODE)
        ::SendMessage(
            m_hWnd,
            WM_GETTEXT,
            iTextLength+1,
            (LPARAM) pwszText);
#else
        CHAR* pszText;

        // Allocate some temporary space for the text.
        pszText = new CHAR[iTextLength+2];
        if (NULL != pszText)
        {
          // Get the text from the the edit control.
          ::SendMessage(
              m_hWnd,
              WM_GETTEXT,
              iTextLength+1,
              (LPARAM) pszText);
          AnsiToUc(pszText, pwszText, iTextLength);
          // Delete the temporary text buffer.
          delete [] pszText;
        }
        else
          hr = E_OUTOFMEMORY;
#endif
      }
    }
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CTextWin::PutText

  Summary:  Puts text content into the edit control. Also
            sets keyboard focus to the TextWin edit control.

  Args:     WCHAR* pwszText
              Pointer to Zero-terminated wide character string.
            INT iTextLength)
              The length of the text data in characters including the
              terminating 0.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CTextWin::PutText(
          WCHAR* pwszText,
          INT iTextLength)
{
  HRESULT hr = E_POINTER;
  LRESULT lr;

  if (IsWindow(m_hWnd) && NULL != pwszText)
  {
#if defined(UNICODE)
    // Send the text to the edit control.
    lr = ::SendMessage(
             m_hWnd,
             WM_SETTEXT,
             0,
             (LPARAM) pwszText);
    hr = lr ? NOERROR : E_FAIL;
#else
    CHAR* pszText;

    // Allocate some temporary space for the text.
    pszText = new CHAR[iTextLength+2];
    if (NULL != pszText)
    {
      UcToAnsi(pwszText, pszText, 0);
      // Send the text to the edit control.
      lr = ::SendMessage(
               m_hWnd,
               WM_SETTEXT,
               0,
               (LPARAM) pszText);
      hr = lr ? NOERROR : E_FAIL;
      // Delete the temporary text buffer.
      delete [] pszText;
    }
    else
      hr = E_OUTOFMEMORY;
#endif
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CTextWin::Resize

  Summary:  Resizes the edit control to a new width and height.  Called
            during the parent window's WM_SIZE to fit the control to the
            client area of the parent window.  It only honors this request
            if it is an integral child window.

  Args:     INT nWidth
              New width in pixels of the edit control.
            INT nHeight
              New height in pixels of the edit control.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CTextWin::Resize(
          INT nWidth,
          INT nHeight)
{
  HRESULT hr = E_POINTER;
  BOOL bResult = FALSE;

  if (IsWindow(m_hWnd))
  {
    bResult = ::MoveWindow(m_hWnd, 0, 0, nWidth, nHeight, TRUE);

    hr = bResult ? NOERROR : E_FAIL;
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CTextWin::Clear

  Summary:  Clears/Deletes all text content in the edit control. The
            content is cut to the windows clipboard.

  Args:     void

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CTextWin::Clear(
          void)
{
  HRESULT hr;

  hr = EditSelectAll();
  if (SUCCEEDED(hr))
    hr = EditDelete();

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CTextWin::EditUndo

  Summary:  Tell text edit control to undo last operation.

  Args:     void

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CTextWin::EditUndo(
          void)
{
  HRESULT hr = E_FAIL;

  if (IsWindow(m_hWnd))
  {
    ::SendMessage(m_hWnd, WM_UNDO, 0, 0);
    hr = NOERROR;
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CTextWin::EditSelectAll

  Summary:  Tell text edit control to select all text in it.

  Args:     void

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CTextWin::EditSelectAll(
          void)
{
  HRESULT hr = E_FAIL;

  if (IsWindow(m_hWnd))
  {
    ::SendMessage(m_hWnd, EM_SETSEL, 0, -1);
    hr = NOERROR;
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CTextWin::EditCut

  Summary:  Tell edit control to cut currently selected text to the
            windows clipboard.

  Args:     void

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CTextWin::EditCut(
          void)
{
  HRESULT hr = E_FAIL;

  if (IsWindow(m_hWnd))
  {
    ::SendMessage(m_hWnd, WM_CUT, 0, 0);
    hr = NOERROR;
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CTextWin::EditCopy

  Summary:  Tell edit control to copy currently selected text to the
            windows clipboard.

  Args:     void

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CTextWin::EditCopy(
          void)
{
  HRESULT hr = E_FAIL;

  if (IsWindow(m_hWnd))
  {
    ::SendMessage(m_hWnd, WM_COPY, 0, 0);
    hr = NOERROR;
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CTextWin::EditPaste

  Summary:  Tell edit control to paste the content of the windows
            clipboard into the text edit control at the current
            caret location.

  Args:     void

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CTextWin::EditPaste(
          void)
{
  HRESULT hr = E_FAIL;

  if (IsWindow(m_hWnd))
  {
    ::SendMessage(m_hWnd, WM_PASTE, 0, 0);
    hr = NOERROR;
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CTextWin::EditDelete

  Summary:  Tell the edit control to delete the currently selected text.

  Args:     void

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CTextWin::EditDelete(
          void)
{
  HRESULT hr = E_FAIL;

  if (IsWindow(m_hWnd))
  {
    ::SendMessage(m_hWnd, WM_CLEAR, 0, 0);
    hr = NOERROR;
  }

  return hr;
}
