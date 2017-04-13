/*+==========================================================================
  File:      LISTWIN.H

  Summary:   Include file for the C++ object that encapsulates the
             list box control that displays the page list.

  Classes:   CListWin

  Functions: none.

  Origin:    5-25-97: atrent - Editor Inheritance from CMsgLog in
             APPUTIL.H.

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

// Don't allow recursive includes of this file.
#ifndef LISTWIN_H
#define LISTWIN_H

#define MAXLINE_SIZE 128
#define MAX_SHOW_LINES 200

// ListWin command IDs.
#define IDC_LISTWIN 7000


#ifdef __cplusplus


/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CListWin

  Summary:  Class for the PageList display Listbox window.

  Methods:  CListWin
              Constructor.
            ~CListWin
              Destructor.
            BOOL Create(HINSTANCE hInst, HWND hWndParent, BOOL bSeparate);
              Creates the CListWin List Box as a separate child window.
            BOOL SetCurSel(INT iIndex);
              Set current selection to specified list item. Zero-based.
            BOOL GetCurSel(INT* piIndex);
              Get the index (page number) of current listbox selection.
            BOOL AddFmt(LPTSTR szFmt, ...);
              Add a printf-style formatted string as new line in listbox.
            BOOL InsertFmt(INT iIndex, LPTSTR szFmt, ...);
              Insert a printf-style formatted line in the listbox.
            BOOL Resize(INT nWidth, INT nHeight);
              Resizes the ListWin listbox to a new width and height.
            BOOL Clear(void);
              Clears all display lines from the ListWin.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class CListWin
{
public:
  // Constructor.
  CListWin()
  {
    m_hInst = NULL;
    m_hWnd = NULL;
    m_bSeparate = FALSE;
  };

  ~CListWin()
  {
  };

  BOOL Create(HINSTANCE hInst, HWND hWndParent, BOOL bSeparate);
  BOOL SetCurSel(INT iIndex);
  BOOL GetCurSel(INT* piIndex);
  BOOL AddFmt(LPTSTR szFmt, ...);
  BOOL InsertFmt(INT iIndex, LPTSTR szFmt, ...);
  BOOL Resize(INT nWidth, INT nHeight);
  BOOL Clear(void);

private:
  // Remember the App Instance Handle.
  HINSTANCE m_hInst;
  // Remember the handle of the listbox window.
  HWND m_hWnd;
  // Remember if CListWin was created as separate window.
  BOOL m_bSeparate;
};


#endif //__cplusplus

#endif //LISTWIN_H
