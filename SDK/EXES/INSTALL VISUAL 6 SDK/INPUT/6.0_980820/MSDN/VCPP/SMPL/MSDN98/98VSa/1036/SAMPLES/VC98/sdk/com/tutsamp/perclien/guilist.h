/*+==========================================================================
  File:      GUILIST.H

  Summary:   Include file for the CGuiList C++ class. A GuiList is a C++
             object that encapsulates and displays a page list. The list
             is held in a standard listbox control which is a child window
             occupying the entire client area of PERCLIEN's main
             application window.

             GuiList is anchored to the Windows GUI (Graphical User
             Interface) environment. This GuiList object relies on a List
             object that is instantiated as a COM object (a COPageList) in
             a separate In-process server, PERSERVE, to store the page
             list data.

             For a comprehensive tutorial code tour of GUILIST's contents
             and offerings see the tutorial PERCLIEN.HTM file. For
             more specific technical details on the internal workings see
             the comments dispersed throughout the GUILIST source code.

  Classes:   CGuiList.

  Origin:    5-20-97: atrent - Editor inheritance from GUIPAPER.CPP in the
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


#if !defined(GUILIST_H)
#define GUILIST_H

#if defined(__cplusplus)

// PageList file extensions.
#define PAG_EXT "PAG"
#define PAG_FILE_EXT ".PAG"

// List display line format strings.
#define PAGE_OPEN_STR "+"
#define PAGE_CLOSED_STR "-"
#define TYPE_TEXT_STR "T"
#define TYPE_DRAWING_STR "D"
#define TYPE_UNKNOWN_STR "?"
#define PAGE_UNTITLED_STR "Untitled"
#define LISTWIN_FMT_STR "%s %u %s: %s"

// Allocation sizes for the OpenList array.
enum
{
  OPENLIST_SIZE = 31
};

// The OpenList item structure.
typedef struct _OPENITEM
{
  SHORT     nType;                       // Page Type.
  INT       iPage;                       // Page Number.
  void*     pGuiPage;                    // Page Gui C++ object.
} OPENITEM;


/*C+C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C+++C
  Class:    CGuiList

  Summary:  Class to encapsulate the displayable Graphical User Interface
            GUI List object. This List object uses the standard Win32
            listbox control to display page items.

  Methods:  CGuiList
              Constructor.
            ~CGuiList
              Destructor.
            BOOL Init(HINSTANCE hInst, HWND hWnd, TCHAR* pszCmdLineFile);
              Initialize the GuiList; create subordinate objects, etc.
            HRESULT ConnectSink(void);
              Connect the PageListSink to the server COPageList event source.
            HRESULT DisconnectSink(void);
              Disconnect the PageListSink from the server COPageList source.
            HRESULT Resize(WORD wWidth, WORD wHeight);
              Resize the display window.
            HRESULT Show(INT iNewSel);
              Show the content of the page list; put content in listbox.
            HRESULT Load(void);
              Load PageList Data from current compound file.
            HRESULT Save(void);
              Save existing PageList Data to current compound file.
            INT AskSave(void);
              Check if new PageList data, ask user, save if user says to.
            HRESULT Close(void);
              Close this page list window; file save & file close if needed.
            HRESULT Open(void);
              Common dialog. Open existing .PAG compound file. Load PageList.
            HRESULT SaveAs(void);
              Common dialog. Save current PageList Data in renamed file.
            HRESULT New(void);
              Common dialog. Create new empty page list and file.
            HRESULT PageTitle(void);
              Dialog box. Edit a new title for the currently select page.
            HRESULT PageOpen(void);
              Open and load currently selected page in separate window.
            HRESULT PageAdd(SHORT nPageType);
              Add new page to the page list, create new separate window.
            HRESULT PageDelete(void);
              Delete currently selected page. Close its window if needed.
            HRESULT PageChanged(INT iPage);
              Set page changed status for this page to TRUE.
            HRESULT PageClosed(INT iPage);
              Mark this page as closed in the dynamic open item array.
C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C---C-C*/
class CGuiList
{
  public:
    CGuiList(void);
    ~CGuiList(void);
    BOOL    Init(HINSTANCE hInst, HWND hWnd, TCHAR* pszCmdLineFile);
    HRESULT ConnectSink(void);
    HRESULT DisconnectSink(void);
    HRESULT Resize(WORD wWidth, WORD wHeight);
    HRESULT Show(INT iNewSel);
    HRESULT Load(void);
    HRESULT Save(void);
    INT     AskSave(void);
    HRESULT Close(void);
    HRESULT Open(void);
    HRESULT SaveAs(void);
    HRESULT New(void);
    HRESULT PageTitle(void);
    HRESULT PageOpen(void);
    HRESULT PageAdd(SHORT nPageType);
    HRESULT PageDelete(void);
    HRESULT PageChanged(INT iPage);
    HRESULT PageClosed(INT iPage);

  private:
    // Private methods.
    HRESULT GetOpenItem(
              INT iPage,
              SHORT* pnType,
              PPVOID ppGuiPage,
              BOOL* pAddOk);
    HRESULT AddOpenItem(INT iPage, SHORT nType, void* pGuiPage);
    HRESULT DeleteOpenItem(INT iPage);
    HRESULT RenumOpenItems(INT iPage);
    HRESULT CloseOpenItem(INT iPage);
    HRESULT SaveOpenPages(void);
    HRESULT CloseOpenPages(void);
    HRESULT CloseTextPages(void);
    HRESULT ReleaseOpenPages(void);
    HRESULT RestoreOpenPages(IStorage* pIStorage_Root);
    IConnectionPoint* GetConnectionPoint(REFIID riid);

    // Private data members.
    HINSTANCE    m_hInst;
    HWND         m_hWnd;
    RECT         m_WinRect;
    IPageList*   m_pIPageList;
    OPENITEM     m_paOpenList[OPENLIST_SIZE];
    CListWin*    m_pListWin;
    IStorage*    m_pIStorage_Root;
    CPageFile*   m_pPageFile;
    OPENFILENAME m_ofnFile;
    TCHAR        m_szFileFilter[MAX_PATH];
    TCHAR        m_szFileName[MAX_PATH];
    TCHAR        m_szFileTitle[MAX_PATH];
    IUnknown*    m_pCOPageListSink;
    DWORD        m_dwPageListSink;
    BOOL         m_bChanged;
};


#endif // __cplusplus

#endif
