/*+==========================================================================
  File:      GUITEXT.H

  Summary:   Include file for the CGuiText C++ class. A GuiText is a C++
             object that encapsulates and displays edited text in a
             separate window. The text is edited in a standard Win32
             multi-line edit control which is a child window occupying
             the entire client area of a separate window. The separate
             window is based on APPUTIL's CVirWindow. CGuiText is derived
             from CVirWindow and extends it.

             GuiText is anchored to the Windows GUI (Graphical User
             Interface) environment. This GuiText object relies on a text
             object that is instantiated as a COM object (a COTextPage) in
             a separate In-process server, PERTEXT, to store the page's
             text data.

             For a comprehensive tutorial code tour of GUITEXT's contents
             and offerings see the tutorial PERCLIEN.HTM file. For
             more specific technical details on the internal workings see
             the comments dispersed throughout the GUITEXT source code.

  Classes:   CGuiText.

  Origin:    5-25-97: atrent - Editor inheritance from GUIPAPER.H in the
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


#if !defined(GUITEXT_H)
#define GUITEXT_H


#if defined(__cplusplus)


/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CGuiText

  Summary:  Class to encapsulate the displayable Graphical User Interface
            (GUI) for functioning text edit control objects in separate
            windows. Such a window has its own menu and window procedure.
            CGuiText is derived from APPUTIL's CVirWindow and thus
            inherits all the features and benefits of CVirWindow.

  Methods:  CGuiText
              Constructor.
            ~CGuiText
              Destructor.
            HRESULT OpenWin(
                      IStorage* pIStorage_Root,
                      WCHAR* pwszPageTitle,
                      WCHAR* pwszDataName);
              Get CGuiText started. Create Window. Make subordinate objects.
            HRESULT TopWin(void);
              Bring the CGuiText window to the on-screen top.
            HRESULT ResizeWin(WORD wWidth, WORD wHeight);
              Resize the current CGuiText window. Pass to edit control too.
            HRESULT Renumber(INT iPage);
              Re-assign the current dynamic page number of this page.
            HRESULT ReleasePage(void);
              Release the root storage held by this text page.
            HRESULT RestorePage(IStorage* pIStorage_Root);
              Restore the root storage for a new compound file.
            HRESULT Close();
              Close this page & window.
            HRESULT Save(void);
              Use COTextPage's IPersistStreamInit to save the text page.
            INT AskSave(void);
              If text changed ask user if save. Save text user says yes.
            HRESULT Delete(void);
              Delete the stored text page. Close page if open in window.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class CGuiText : public CVirWindow
{
  public:
    // Constructor and Destructor override those in CVirWindow.
    CGuiText(HINSTANCE hInst, HWND hWndApp, INT iPage);
    ~CGuiText(void);

    // The public CGuiText methods that extend CVirWindow.
    HRESULT OpenWin(
              IStorage* pIStorage_Root,
              WCHAR* pwszPageTitle,
              WCHAR* pwszDataName);
    HRESULT TopWin(void);
    HRESULT ResizeWin(WORD wWidth, WORD wHeight);
    HRESULT Renumber(INT iPage);
    HRESULT ReleasePage(void);
    HRESULT RestorePage(IStorage* pIStorage_Root);
    HRESULT Close();
    HRESULT Save(void);
    INT     AskSave(void);
    HRESULT Delete(void);

  protected:
    LRESULT WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

  private:
    // Private methods.
    HRESULT Clear(void);
    HRESULT Load(void);
    IConnectionPoint* GetConnectionPoint(REFIID riid);
    HRESULT ConnectSink(void);
    HRESULT DisconnectSink(void);
    HRESULT InitEditMenu(HMENU hEditMenu);
    LRESULT DoCommand(WPARAM wParam, LPARAM lParam);

    // Private data members.
    HWND m_hWndApp;              // Handle of the parent app window.
    RECT m_WinRect;              // GuiText Window position rectangle.
    HWND m_hWndEdit;             // Text edit control window handle.
    CTextWin* m_pTextWin;        // Text edit control window C++ object.
    IStorage* m_pIStorage_Root;  // IStorage on the root storage.
    ITextPage* m_pITextPage;     // ITextPage on the COTextPage COM object.
    INT m_iPage;                 // Page Number of this text page.
    CLSID m_CidTextPage;         // The Class ID for COTextPage objects.
    WCHAR m_wszDataName[PAGE_NAME_SIZE]; // Page DataName.
    IUnknown* m_pCOTextPageSink; // Interface to TextPageSink COM object.
    DWORD m_dwTextPageSink;      // Sink connection key.
    BOOL m_bChanged;             // Was textwin data changed?
};


#endif // __cplusplus

#endif // GUITEXT.H
