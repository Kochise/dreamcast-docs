/*+==========================================================================
  File:      GUIDRAW.H

  Summary:   Include file for the CGuiDraw C++ class. A GuiDraw is a C++
             object that displays and stores mouse movements as free-form
             line drawing or "scribbling" in the client area of a separate
             window. GuiDraw is anchored to the Windows GUI (Graphical
             User Interface) environment. This GuiDraw object relies on a
             virtual Drawing Paper object that is instantiated as a COM
             object (a CODrawPage) in a separate In-process server,
             PERDRAW, to store the "ink" data that is drawn.

             For a comprehensive tutorial code tour of GUIDRAW's contents
             and offerings see the tutorial PERCLIEN.HTM file. For
             more specific technical details on the internal workings see
             the comments dispersed throughout the GUIDRAW source code.

  Classes:   CGuiDraw.

  Origin:    5-24-97: atrent - Editor inheritance from GUIPAPER.H in the
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


#if !defined(GUIDRAW_H)
#define GUIDRAW_H


#if defined(__cplusplus)

// Some compile-time constants for ink thickness in pixels.
enum
{
  INK_THIN = 2,
  INK_MEDIUM = 10,
  INK_THICK = 20
};


/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CGuiDraw

  Summary:  Class to encapsulate the displayable Graphical User Interface
            (GUI) for functioning drawing objects in separate windows.
            Such a window has its own menu and window procedure. CGuiDraw
            is derived from APPUTIL's CVirWindow and thus inherits all the
            features and benefits of CVirWindow.

  Methods:  CGuiDraw
              Constructor.
            ~CGuiDraw
              Destructor.
            BOOL OpenWin(
                   IStorage* pIStorage_Page,
                   WCHAR* pwszPageTitle,
                   WCHAR* pwszDataName);
              Open the drawing window of this CGuiDraw object.
            HRESULT TopWin(void);
              Make this the topmost window on the screen.
            HRESULT ResizeWin(WORD wWidth, WORD wHeight);
              Resize the display window.
            HRESULT ClearWin(void);
              Clear display window but retain ink data.
            HRESULT PaintWin(void);
              Clear window and Repaint the window with ink data.
            HRESULT InkSaving(BOOL bInkSaving);
              Turn Ink data saving in on and off.
            HRESULT InkWidth(SHORT nInkWidth);
              Set current ink line width for drawing.
            HRESULT InkColor(COLORREF crInkColor);
              Set current ink color for drawing.
            HRESULT InkStart(SHORT nX, SHORT nY);
              Start ink drawing sequence.
            HRESULT InkDraw(SHORT nX, SHORT nY);
              Draw ink sequence data.
            HRESULT InkStop(SHORT nX, SHORT nY);
              Stop ink drawing sequence.
            HRESULT Renumber(INT iPage);
              Re-assign the current dynamic page number for this page.
            HRESULT ReleasePage(void);
              Release all substorages for this draw page.
            HRESULT RestorePage(IStorage* pIStorage_Page);
              Reopen all substorages for the draw page.
            HRESULT Close(void);
              Close this draw page window and it's open substorages.
            HRESULT Save(void);
              Save existing Ink Data to the page's substorage.
            INT AskSave(void);
              Check if new ink data, ask user, save if user says to.
            HRESULT Delete(void);
              Delete the entire substorage for this draw page. Close Window.
            HRESULT Clear(void);
              Clear content of this draw page; clear window.
            COLORREF PickColor(void);
              Common dialog. Ask user to choose new pen color.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class CGuiDraw : public CVirWindow
{
  public:
    // Constructor and Destructor override those in CVirWindow.
    CGuiDraw(HINSTANCE hInst, HWND hWndApp, INT iPage);
    ~CGuiDraw(void);

    // The public CGuiDraw methods that extend CVirWindow.
    HRESULT  OpenWin(
               IStorage* pIStorage_Page,
               WCHAR* pwszPageTitle,
               WCHAR* pwszDataName);
    HRESULT  TopWin(void);
    HRESULT  ResizeWin(WORD wWidth, WORD wHeight);
    HRESULT  ClearWin(void);
    HRESULT  PaintWin(void);
    HRESULT  InkSaving(BOOL bInkSaving);
    HRESULT  InkWidth(SHORT nInkWidth);
    HRESULT  InkColor(COLORREF crInkColor);
    HRESULT  InkStart(SHORT nX, SHORT nY);
    HRESULT  InkDraw(SHORT nX, SHORT nY);
    HRESULT  InkStop(SHORT nX, SHORT nY);
    HRESULT  Renumber(INT iPage);
    HRESULT  ReleasePage(void);
    HRESULT  RestorePage(IStorage* pIStorage_Page);
    HRESULT  Close(void);
    HRESULT  Save(void);
    INT      AskSave(void);
    HRESULT  Delete(void);
    HRESULT  Clear(void);
    COLORREF PickColor(void);

  protected:
    LRESULT  WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

  private:
    // Private methods.
    HRESULT  Load(void);
    LRESULT  DoCommand(WPARAM wParam, LPARAM lParam);
    IConnectionPoint* GetConnectionPoint(REFIID riid);
    HRESULT  ConnectSink(void);
    HRESULT  DisconnectSink(void);

    // Private data members.
    HWND       m_hWndApp;        // Handle of the parent app window.
    RECT       m_WinRect;        // GuiDraw Window position rectangle.
    HDC        m_hDC;            // GuiDraw window drawing device context.
    HPEN       m_hPen;           // Handle to the drawing pen.
    SHORT      m_nInkWidth;      // Current ink pen drawing width.
    COLORREF   m_crInkColor;     // Current ink pen drawing color.
    BOOL       m_bInkSaving;     // TRUE=>inking is to be saved.
    BOOL       m_bInking;        // TRUE=>inking sequence in progress.
    BOOL       m_bPainting;      // TRUE=>painting in progress.
    POINT      m_OldPos;         // Old Position.
    IStorage*  m_pIStorage_Root; // IStorage on the client's root storage.
    IStorage*  m_pIStorage_Page; // IStorage on the page's drawing storage.
    IDrawPage* m_pIDrawPage;     // IDrawPage on the CODrawPage COM object.
    CLSID      m_CidDrawPage;    // The Class ID for CODrawPage objects.
    WCHAR      m_wszDataName[PAGE_NAME_SIZE]; // Page DataName.
    INT        m_iPage;          // Page Number of this text page.
    WORD       m_wWidth;         // Window width.
    WORD       m_wHeight;        // Window height.
    TEXTMETRIC m_tm;             // Text metric for display of text using DC.
    CHOOSECOLOR m_ChooseColor;   // Choose color dialog structure.
    COLORREF   m_acrCustColors[16]; // Custom color array for Choose Color.
    IUnknown*  m_pCODrawPageSink; // Interface to DrawPageSink COM object.
    DWORD      m_dwDrawPageSink;  // DrawPageSink connection key.
};


#endif // __cplusplus

#endif // GUIDRAW.H
