/*+==========================================================================
  File:      TEXTWIN.H

  Summary:   Include file for the CTextWin C++ object that encapsulates
             the multi-line edit control that displays the edited text for
             a text page.

  Classes:   CTextWin

  Functions: none.

  Origin:    5-25-97: atrent - Editor Inheritance from CListWin in
             LISTWIN.H

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
#ifndef TEXTWIN_H
#define TEXTWIN_H

#define MAX_TEXT_SIZE 4095

// TextWin command IDs.
#define IDC_TEXTWIN 7100

#ifdef __cplusplus


/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CTextWin

  Summary:  Class for the text edit control window used for editing
            text pages.

  Methods:  CTextWin
              Constructor.
            ~CTextWin
              Destructor.
            HRESULT Init(HINSTANCE hInst,HWND hWndParent,HWND* phWndEdit);
              Create & initialize the text edit control as child window.
            HRESULT GetLength(INT* piTextLength);
              Get length of current text content in edit control.
            HRESULT GetText(WCHAR* pwszText);
              Get the text content of the edit control.
            HRESULT PutText(WCHAR* pwszText, INT iTextLength);
              Puts text content into the text edit control.
            HRESULT Resize(INT nWidth, INT nHeight);
              Resizes the edit control to a new width and height in pixels.
            HRESULT Clear(void);
              Clears/deletes all text content in the edit control.
            HRESULT EditUndo(void);
              Tell text edit control to undo last operation.
            HRESULT EditSelectAll(void);
              Tell text edit control to select all text in it.
            HRESULT EditCut(void);
              Tell text edit control to cut selected text to clipboard.
            HRESULT EditCopy(void);
              Tell text edit control to copy selected text to clipboard.
            HRESULT EditPaste(void);
              Tell text edit control to paste clipboard contents into
              edit control.
            HRESULT EditDelete(void);
              Tell text edit control to delete currently selected text.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class CTextWin
{
  public:
    // Constructor and Destructor.
    CTextWin();
    ~CTextWin();

    // The methods to function the text edit control window.
    HRESULT Init(
              HINSTANCE hInst,
              HWND hWndParent,
              HWND* phWndEdit);
    HRESULT GetLength(INT* piTextLength);
    HRESULT GetText(WCHAR* pwszText);
    HRESULT PutText(WCHAR* pwszText, INT iTextLength);
    HRESULT Resize(INT nWidth, INT nHeight);
    HRESULT Clear(void);
    HRESULT EditUndo(void);
    HRESULT EditSelectAll(void);
    HRESULT EditCut(void);
    HRESULT EditCopy(void);
    HRESULT EditPaste(void);
    HRESULT EditDelete(void);

  private:
    // Private data members.
    HINSTANCE m_hInst;         // App Instance Handle.
    HWND m_hWnd;               // Handle of the edit control window.
    WORD m_wWidth;             // Window rect width.
    WORD m_wHeight;            // Window rect height.
};


#endif //__cplusplus

#endif //TEXTWIN_H
