/*+==========================================================================
  File:      GUIPAPER.H

  Summary:   Include file for the CGuiPaper C++ class. A GuiPaper is a C++
             object that displays and stores mouse movements as free-form
             line drawing or "scribbling" in the client area of a
             designated window. GuiPaper is anchored to the Windows GUI
             (Graphical User Interface) environment. This GuiPaper object
             relies on a virtual Paper object that is instantiated as a
             COM object (a COPaper) in a separate In-process server,
             STOSERVE, to store the "ink" data that is drawn.

             For a comprehensive tutorial code tour of GUIPAPER's contents
             and offerings see the tutorial STOCLIEN.HTM file. For
             more specific technical details on the internal workings see
             the comments dispersed throughout the GUIPAPER source code.

  Classes:   CGuiPaper.

  Origin:    6-10-96: atrent - Editor inheritance from GUIBALL.H in the
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

#if !defined(GUIPAPER_H)
#define GUIPAPER_H

#if defined(__cplusplus)


#define PAP_EXT "PAP"
#define PAP_FILE_EXT ".PAP"


/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CGuiPaper

  Summary:  Class to encapsulate the displayable Graphical User Interface
            GUI Paper object.

  Methods:  CGuiPaper
              Constructor.
            ~CGuiPaper
              Destructor.
            BOOL Init(HINSTANCE hInst, HWND hWnd, TCHAR* pszCmdLineFile);
              Initialize the GuiPaper.
            HRESULT DrawOn(void);
              Lock paper for drawing.
            HRESULT DrawOff(void);
              Unlock paper for drawing.
            HRESULT ClearWin(void);
              Clear display window but retain ink data.
            HRESULT PaintWin(void);
              Clear window and Repaint the window with ink data.
            HRESULT Erase(void);
              Erase current drawn content and clear display window.
            HRESULT Resize(WORD wWidth, WORD wHeight);
              Resize the display window.
            HRESULT InkSaving(BOOL bInkSaving);
              Turn Ink data saving in COPaper on and off.
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
            HRESULT ConnectPaperSink(void);
              Connect the PaperSink to the server COPaper source.
            HRESULT DisconnectPaperSink(void);
              Disconnect the PaperSink from the server COPaper source.
            IConnectionPoint* GetConnectionPoint(REFIID riid);
              Private method to obtain a connection point interface.
            HRESULT Load(void);
              Load Ink Data from current compound file.
            HRESULT Save(void);
              Save existing Ink Data to current compound file.
            INT AskSave(void);
              Check if new ink data, ask user, save if user says to.
            HRESULT Open(void);
              Common dialog. Open existing Ink Data compound file.
            HRESULT SaveAs(void);
              Common dialog. Save current Ink Data file in renamed file.
            COLORREF PickColor(void);
              Common dialog. Ask user to choose new pen color.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class CGuiPaper
{
  public:
    CGuiPaper(void);
    ~CGuiPaper(void);
    BOOL Init(HINSTANCE hInst, HWND hWnd, TCHAR* pszCmdLineFile);
    HRESULT DrawOn(void);
    HRESULT DrawOff(void);
    HRESULT ClearWin(void);
    HRESULT PaintWin(void);
    HRESULT Erase(void);
    HRESULT Resize(WORD wWidth, WORD wHeight);
    HRESULT InkSaving(BOOL bInkSaving);
    HRESULT InkWidth(SHORT nInkWidth);
    HRESULT InkColor(COLORREF crInkColor);
    HRESULT InkStart(SHORT nX, SHORT nY);
    HRESULT InkDraw(SHORT nX, SHORT nY);
    HRESULT InkStop(SHORT nX, SHORT nY);
    HRESULT ConnectPaperSink(void);
    HRESULT DisconnectPaperSink(void);
    HRESULT Load(void);
    HRESULT Save(void);
    INT     AskSave(void);
    HRESULT Open(void);
    HRESULT SaveAs(void);
    COLORREF PickColor(void);

  private:
    HINSTANCE  m_hInst;
    HWND       m_hWnd;
    HDC        m_hDC;
    RECT       m_WinRect;
    IPaper*    m_pIPaper;
    SHORT      m_nLockKey;
    HPEN       m_hPen;
    SHORT      m_nInkWidth;
    COLORREF   m_crInkColor;
    BOOL       m_bInkSaving;
    BOOL       m_bInking;
    BOOL       m_bPainting;
    POINT      m_OldPos;
    IUnknown*  m_pCOPaperSink;
    DWORD      m_dwPaperSink;
    BOOL       m_bDirty;
    CPapFile*    m_pPapFile;
    OPENFILENAME m_ofnFile;
    TCHAR        m_szFileFilter[MAX_PATH];
    TCHAR        m_szFileName[MAX_PATH];
    TCHAR        m_szFileTitle[MAX_PATH];
    CHOOSECOLOR  m_ChooseColor;
    COLORREF     m_acrCustColors[16];

    IConnectionPoint* GetConnectionPoint(REFIID riid);
};


#endif // __cplusplus

#endif
