/*+==========================================================================
  File:      GUIPAPER.H

  Summary:   Include file for the CGuiPaper C++ class. A GuiPaper is a C++
             object that displays and stores mouse movements as free-form
             line drawing or "scribbling" in the client area of a
             designated window. GuiPaper is anchored to the Windows GUI
             (Graphical User Interface) environment. This GuiPaper object
             relies on a virtual Paper object that is instantiated as a
             COM object (a COPaper) in a separate out-of-process server,
             DCDSERVE, to store the "ink" data that is drawn.

             For a comprehensive tutorial code tour of GUIPAPER's contents
             and offerings see the tutorial DCOMDRAW.HTM file. For
             more specific technical details on the internal workings see
             the comments dispersed throughout the GUIPAPER source code.

  Classes:   CGuiPaper.

  Origin:    8-23-97: atrent - Editor inheritance from GUIBALL.H in the
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

#if !defined(GUIPAPER_H)
#define GUIPAPER_H

#if defined(__cplusplus)


/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CGuiPaper

  Summary:  Class to encapsulate the displayable Graphical User Interface
            GUI Paper object.

  Methods:  CGuiPaper
              Constructor.
            ~CGuiPaper
              Destructor.
            BOOL Init(HINSTANCE hInst, HWND hWnd);
              Initialize the GuiPaper.
            HRESULT SetPenCur(USHORT usPenCurNew);
              Set the pen width and pen On/Off.
            HRESULT Lock(BOOL bLock);
              Lock or unlock paper for drawing. Master client has lock.
            BOOL    Master(void);
              Return TRUE if this client is the owning master client.
            HRESULT ResizeWin(LONG lWidth, LONG lHeight);
              Resize the display window.
            HRESULT ClearWin(void);
              Clear display window but retain ink data.
            HRESULT PaintWin(void);
              Clear window and Repaint the window with ink data.
            HRESULT Erase(void);
              Erase current drawn content and clear display window.
            HRESULT Resize(LONG lWidth, LONG lHeight);
              Resize the display rectangle of the drawing.
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
            HRESULT Load(void);
              Load ink data from current compound file (local or remote).
            HRESULT LoadLocal(void);
              Unload current drawing and Load drawing from local
              DCDSERVE server.
            HRESULT LoadRemote(void);
              Unload current drawing paper and reload from a DCDSERVE
              located on a remote machine. User gives remote machine
              name in a dialog.
            HRESULT Save(void);
              Save existing Ink Data to current compound file.
            INT AskSave(void);
              Check if new ink data, ask user, save if user says to.
            COLORREF PickColor(void);
              Common dialog. Ask user to choose new pen color.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class CGuiPaper
{
  public:
    CGuiPaper(void);
    ~CGuiPaper(void);
    BOOL Init(HINSTANCE hInst, HWND hWnd);
    HRESULT SetPenCur(USHORT usPenCurNew);
    HRESULT Lock(BOOL bLock);
    BOOL    Master(void);
    HRESULT ResizeWin(LONG lWidth, LONG lHeight);
    HRESULT ClearWin(void);
    HRESULT PaintWin(void);
    HRESULT Erase(void);
    HRESULT Resize(LONG lWidth, LONG lHeight);
    HRESULT InkWidth(SHORT nInkWidth);
    HRESULT InkColor(COLORREF crInkColor);
    HRESULT InkStart(SHORT nX, SHORT nY);
    HRESULT InkDraw(SHORT nX, SHORT nY);
    HRESULT InkStop(SHORT nX, SHORT nY);
    HRESULT ConnectPaperSink(void);
    HRESULT DisconnectPaperSink(void);
    HRESULT Load(void);
    HRESULT LoadLocal(void);
    HRESULT LoadRemote(void);
    HRESULT Save(void);
    INT     AskSave(void);
    COLORREF PickColor(void);

  private:
    HINSTANCE    m_hInst;
    HWND         m_hWnd;
    HDC          m_hDC;
    RECT         m_WinRect;
    ISharePaper* m_pISharePaper;
    HPEN         m_hPen;
    USHORT       m_PenCur;
    HCURSOR      m_hPenCurN;
    HCURSOR      m_hPenCurT;
    HCURSOR      m_hPenCurM;
    HCURSOR      m_hPenCurF;
    SHORT        m_nInkWidth;
    COLORREF     m_crInkColor;
    BOOL         m_bLocked;
    BOOL         m_bInkSaving;
    BOOL         m_bInking;
    BOOL         m_bPainting;
    POINT        m_OldPos;
    IUnknown*    m_pCOPaperSink;
    DWORD        m_dwPaperSink;
    BOOL         m_bDirty;
    CHOOSECOLOR  m_ChooseColor;
    COLORREF     m_acrCustColors[16];

    IConnectionPoint* GetConnectionPoint(REFIID riid);
};


#endif // __cplusplus

#endif
