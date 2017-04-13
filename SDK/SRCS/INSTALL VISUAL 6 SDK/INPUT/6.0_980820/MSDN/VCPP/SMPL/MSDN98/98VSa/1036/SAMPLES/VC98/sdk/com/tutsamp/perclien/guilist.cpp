/*+==========================================================================
  File:      GUILIST.CPP

  Summary:   Implementation file for the CGuiList C++ class. A GuiList is
             a C++ object that displays a list of pages that are kept in a
             compound file. The CGuiList provides the main application
             window for the PERCLIEN application. During the operation of
             this application CGuiList is used to manage a list of
             editable pages. These pages have their own child windows. For
             example, GUIDRAW.CPP codes the drawing page window and
             GUITEXT.CPP codes the text page window. CGuiList is anchored
             to the Windows GUI (Graphical User Interface) environment--it
             retains knowledge of window handles and device contexts on
             the local machine. This GuiList object relies on a virtual
             List object for persistent storage of the list of pages.
             This virtual List object (a COPageList) is instantiated
             as a COM object in a separate In-process server, PERSERVE.

             For a comprehensive tutorial code tour of GUILIST's contents
             and offerings see the tutorial PERCLIEN.HTM file. For more
             specific technical details on the internal workings see the
             comments dispersed throughout the GUILIST source code.

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

/*--------------------------------------------------------------------------
  We include WINDOWS.H for all Win32 applications.
  We include OLE2.H because we will be calling the COM/OLE Libraries.
  We include OLECTL.H because it has definitions for connectable objects.
  We include COMMDLG.H because we will be using the Open File and
    potentially other Common dialogs.
  We include TCHAR.H for general Unicode/Ansi prototype of utility
    functions like _tsplitpath, etc.
  We include APPUTIL.H because we will be building this application using
    the convenient Virtual Window and Dialog classes and other
    utility functions in the APPUTIL Library (ie, APPUTIL.LIB).
  We include IPAGES.H and PAGEGUID.H for the common page-related Interface
    class, GUID, and CLSID specifications.
  We include RESDEF.H because it has class and resource definitions
    specific to this application.
  We include PAGEFILE.H because it has the C++ class used for compound file
    storage of page list ata.
  We include LISTWIN.H because CGuiList creates and uses a CListWin to
    manage a standard list box window.
  We include GUILIST.H because it has the C++ class used for GUI display
    of the page List.
  We include LISTSINK.H because it has the C++ class used for the sink
    that receives event notifications from COPageList in the server.
  We include TEXTWIN.H because it has the C++ class that encapsulates
    the standard multi-line text editing window/control.
  We include GUITEXT.H because it has the C++ class used for GUI display
    of text pages.
  We include TEXTSINK.H because it has the C++ class used for the sink
    that receives event notifications from COTextPage in the server.
  We include GUIDRAW.H because it has the C++ class used for GUI display
    of drawing pages.
  We include DRAWSINK.H because it has the C++ class used for the sink
    that receives event notifications from CODrawPage in the server.
  We include PERCLIEN.H because it has the class declarations for the
    main window of this application.
---------------------------------------------------------------------------*/
#include <windows.h>
#include <ole2.h>
#include <olectl.h>
#include <commdlg.h>
#include <tchar.h>
#include <apputil.h>
#include <ipages.h>
#include <pageguid.h>
#include "resdef.h"
#include "pagefile.h"
#include "listwin.h"
#include "guilist.h"
#include "listsink.h"
#include "textwin.h"
#include "guitext.h"
#include "textsink.h"
#include "guidraw.h"
#include "drawsink.h"
#include "perclien.h"


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiList::CGuiList

  Summary:  Constructor.

  Args:     void

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CGuiList::CGuiList(void)
{
  m_hWnd            = NULL;
  m_hInst           = NULL;
  m_pIPageList      = NULL;
  m_pIStorage_Root  = NULL;
  m_pCOPageListSink = NULL;
  m_dwPageListSink  = 0;
  m_pListWin        = NULL;
  m_pPageFile       = NULL;
  m_bChanged        = FALSE;

  // Init the file name for title display to <MyModule>.<EXT>.
  if (GetModuleFileName(m_hInst, m_szFileName, MAX_PATH))
  {
    _tsplitpath(m_szFileName, NULL, NULL, m_szFileTitle, NULL);
    lstrcat(m_szFileTitle, TEXT(PAG_FILE_EXT));
  }

  // Ensure the m_szFileName OFN member variable string is NULL.
  m_szFileName[0] = 0;

  // Zero the open list array.
  memset(m_paOpenList, 0, OPENLIST_SIZE * sizeof(OPENITEM));
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiList::~CGuiList

  Summary:  Destructor.

  Args:     void

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CGuiList::~CGuiList(void)
{
  if (m_pIPageList)
  {
    // Use CGuiList's Close method to close down the PageList. This
    // disconnects the Sink, performs final release of the COPageList
    // object, and closes the file by releasing the IStorage for the file.
    Close();

    // Release the reference to the PageListSink object.
    RELEASE_INTERFACE(m_pCOPageListSink);

    // Delete the CPageFile object.
    DELETE_POINTER(m_pPageFile);

    // Delete the CListWin object.
    DELETE_POINTER(m_pListWin);
  }
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiList::Init

  Summary:  Get CGuiList started. Make any subordinate objects, like
            COPageList, CListWin, and CPageFile, and get them started.

  Args:     HINSTANCE hInst
              Handle to the application instance.
            HWND hWnd
              Handle of the display window. Part of what makes CGuiList
              a GUI kind of thing.
            TCHAR* pszCmdLineFile)
              Pointer to file name for an initial file to load that was
              specified on the app command line.

  Returns:  BOOL
              TRUE for success; FALSE for fail.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
BOOL CGuiList::Init(
       HINSTANCE hInst,
       HWND hWnd,
       TCHAR* pszCmdLineFile)
{
  BOOL bOk = FALSE;
  HRESULT hr;
  COPageListSink* pCob = NULL;
  HCURSOR hCurPrev;
  HCURSOR hCurWait = LoadCursor(NULL, IDC_WAIT);

  if (hInst && hWnd)
  {
    m_hInst = hInst;
    m_hWnd = hWnd;

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
    m_ofnFile.lpstrDefExt = TEXT(PAG_EXT);

    if (LoadString(m_hInst, IDS_OFN_PAGFILES, m_szFileFilter, MAX_PATH))
      m_ofnFile.lpstrFilter = m_szFileFilter;
    else
      m_ofnFile.lpstrFilter = TEXT(OFN_DEFAULTFILES_STR);

    // Create the CPageFile object so we can store page list data in
    // .PAG compound files.
    m_pPageFile = new CPageFile;
    if (NULL != m_pPageFile)
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
        // Build a path to where the default application .PAG file
        // should be. It should be in the same directory as the .EXE
        // as the appname with an .PAG extension.
        MakeFamilyPath(m_hInst, m_szFileName, TEXT(PAG_FILE_EXT));
      }

      // Init the CPageFile object.
      hr = m_pPageFile->Init(m_szFileName);
      if (SUCCEEDED(hr))
      {
        // Create the CListWin object so we can show page list data
        // in a list box window.
        m_pListWin = new CListWin;
        if (NULL != m_pListWin)
        {
          if (m_pListWin->Create(m_hInst, m_hWnd, FALSE))
          {
            // Create the COPageListSink object to receive PageList events.
            pCob = new COPageListSink(NULL, this);
            if (NULL != pCob)
            {
              // Save a pointer to the COPageListSink IUnknown interface.
              // AddRef because of this saved copy. Released in destructor.
              m_pCOPageListSink = pCob;
              m_pCOPageListSink->AddRef();
              bOk = TRUE;
            }
          }
        }
      }
    }

    // Set Cursor from hourglass back to what it was.
    SetCursor(hCurPrev);
  }

  return (bOk);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiList::GetConnectionPoint

  Summary:  Internal private method to obtain a connection point interface.

  Args:     REFIID riid
              IID of the requested connection point Interface.

  Returns:  IConnectionPoint*
              Requested IConnectionPoint interface pointer. NULL if none.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
IConnectionPoint* CGuiList::GetConnectionPoint(
                    REFIID riid)
{
  IConnectionPoint* pConnPoint = NULL;
  IConnectionPointContainer* pConnPointContainer = NULL;
  IConnectionPoint* pConnPt;
  HRESULT hr;

  // First query the object for its Connection Point Container. This
  // essentially asks the object in the server if it is connectable.
  hr = m_pIPageList->QueryInterface(
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
  Method:   CGuiList::ConnectSink

  Summary:  Connect the PageListSink to the server COPageList event
            source.

  Args:     void

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiList::ConnectSink(void)
{
  HRESULT hr = E_FAIL;
  DWORD dwKey;
  IConnectionPoint* pConnPoint;

  if (!m_dwPageListSink)
  {
    // Get the PageList Sink connection point in the server.
    pConnPoint = GetConnectionPoint(IID_IPageListSink);
    if (NULL != pConnPoint)
    {
      // Connect the server's object to the PageList Sink in this client.
      hr = pConnPoint->Advise(m_pCOPageListSink, &dwKey);
      if (SUCCEEDED(hr))
        m_dwPageListSink = dwKey;

      RELEASE_INTERFACE(pConnPoint);
    }
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiList::DisconnectSink

  Summary:  Disconnect the PageListSink from the server COPageList event
            source.

  Args:     void.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiList::DisconnectSink(void)
{
  HRESULT hr = E_FAIL;
  IConnectionPoint* pConnPoint;

  if (m_dwPageListSink)
  {
    // Get the PageList Sink connection point.
    pConnPoint = GetConnectionPoint(IID_IPageListSink);
    if (NULL != pConnPoint)
    {
      // Disconnect the object in the server from the PageList Sink in
      // this client.
      hr = pConnPoint->Unadvise(m_dwPageListSink);
      if (SUCCEEDED(hr))
        m_dwPageListSink = 0;

      RELEASE_INTERFACE(pConnPoint);
    }
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiList::Resize

  Summary:  Handle a user-initiated Resize of the app's main window.
            Pass this resize on to the child list box window.

  Args:     WORD wWidth,
              New width of window in pixels.
            WORD wHeight)
              New height of window in pixels.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiList::Resize(
          WORD wWidth,
          WORD wHeight)
{
  HRESULT hr = E_FAIL;
  BOOL bOk = FALSE;

  bOk = m_pListWin->Resize(wWidth, wHeight);
  if (bOk)
    hr = NOERROR;

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiList::Show

  Summary:  Show the content of the page list by putting the list content
            into a standard list box control/window.

  Args:     INT iNewSel)
              The highlighted current selection index in the list.
              If < 0 then use/restore the current list box selection.
              If >= 0 then set the selection to the index specified.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiList::Show(
          INT iNewSel)
{
  HRESULT hr = E_FAIL;
  INT iPage = 0;
  INT iCurSel;
  BOOL bDone = FALSE;
  BOOL bOpen = FALSE;
  SHORT nType = PAGETYPE_NONE;
  WCHAR wszTitle[PAGE_TITLE_SIZE];
  WCHAR wszDataName[PAGE_NAME_SIZE];
  TCHAR szOpen[4];
  TCHAR szType[4];

  // Get currently selected page index.
  if (iNewSel < 0)
    m_pListWin->GetCurSel(&iCurSel);
  else
    iCurSel = iNewSel;

  // First clear all ListWin display content.
  m_pListWin->Clear();

  // Now loop. Ask COPageList for all Page List items and add
  // display entries for them in ListWin.
  while (!bDone)
  {
    hr = m_pIPageList->Get(iPage, &bOpen, &nType, wszTitle, wszDataName);
    if (SUCCEEDED(hr))
    {
      if (bOpen)
        lstrcpy(szOpen, TEXT(PAGE_OPEN_STR));
      else
        lstrcpy(szOpen, TEXT(PAGE_CLOSED_STR));

      switch (nType)
      {
        case PAGETYPE_TEXT:
          lstrcpy(szType, TEXT(TYPE_TEXT_STR));
          break;
        case PAGETYPE_DRAWING:
          lstrcpy(szType, TEXT(TYPE_DRAWING_STR));
          break;
        default:
          lstrcpy(szType, TEXT(TYPE_UNKNOWN_STR));
          break;
      }
#if defined(UNICODE)
      hr = m_pListWin->AddFmt(
                         TEXT(LISTWIN_FMT_STR),
                         szOpen,
                         iPage,
                         szType,
                         wszTitle);
#else
      {
        CHAR szTitle[PAGE_TITLE_SIZE];

        UcToAnsi(wszTitle, szTitle, 0);
        hr = m_pListWin->AddFmt(
                           TEXT(LISTWIN_FMT_STR),
                           szOpen,
                           iPage,
                           szType,
                           szTitle);
      }
#endif
      iPage++;
    }
    else
    {
      hr = NOERROR;
      bDone = TRUE;
    }
  }

  // Restore currently selected page index.
  m_pListWin->SetCurSel(iCurSel);

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiList::GetOpenItem

  Summary:  Private method. Get the open item for a specified page. Also
            indicate whether the open array can accept any new open items.

  Args:     INT iPage,
              The requested page number of the page to get. Can be -1
              indicating that only the AddOk status is requested.
            SHORT* pnPageType,
              Address of the output page type variable for the requested
              open page item. Can be NULL indicating no request.
            PPVOID ppGuiPage,
              Address of the output pointer variable that receives a
              pointer to the C++ object that controls the page's window.
              Can be NULL indicating no request.
            BOOL* pAddOk)
              Address of the output BOOL variable that, if TRUE, signals
              the caller whether any new items can be added/opened.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiList::GetOpenItem(
          INT iPage,
          SHORT* pnPageType,
          PPVOID ppGuiPage,
          BOOL* pAddOk)
{
  HRESULT hr = E_FAIL;
  SHORT nOpenType;
  INT i;
  BOOL bAddOk = FALSE;

  // Loop thru the open list array and find the open page.
  for (i=0; i<OPENLIST_SIZE; i++)
  {
    nOpenType = m_paOpenList[i].nType;

    if (!bAddOk && pAddOk != NULL && nOpenType == PAGETYPE_NONE)
      *pAddOk = bAddOk = TRUE;

    if (nOpenType != PAGETYPE_NONE && m_paOpenList[i].iPage == iPage)
    {
      if (E_FAIL == hr)
      {
        if (NULL != pnPageType)
          *pnPageType = m_paOpenList[i].nType;
        if (NULL != ppGuiPage)
          *ppGuiPage = m_paOpenList[i].pGuiPage;
        hr = NOERROR;
      }
    }
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiList::AddOpenItem

  Summary:  Private method. Add a new open item to the open item array.

  Args:     INT iPage,
              Page number of new open item.
            SHORT nPageType,
              Page type of new open item.
            void* pGuiPage)
              Pointer to window control C++ object (eg, pGuiText).

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiList::AddOpenItem(
          INT iPage,
          SHORT nPageType,
          void* pGuiPage)
{
  HRESULT hr = E_FAIL;
  SHORT nOpenType;
  INT i;

  // Loop thru the open list array and find an empty slot.
  for (i=0; i<OPENLIST_SIZE; i++)
  {
    nOpenType = m_paOpenList[i].nType;

    if (nOpenType == PAGETYPE_NONE)
    {
      m_paOpenList[i].nType = nPageType;
      m_paOpenList[i].iPage = iPage;
      m_paOpenList[i].pGuiPage = pGuiPage;
      hr = NOERROR;
      break;
    }
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiList::DeleteOpenItem

  Summary:  Private method. Delete the specified open item from the
            open item array.

  Args:     INT iPage,
              Dynamic number of page to delete.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiList::DeleteOpenItem(
          INT iPage)
{
  HRESULT hr = E_FAIL;
  SHORT nOpenType;
  INT i;

  // Loop thru the open list array and find the open page.
  for (i=0; i<OPENLIST_SIZE; i++)
  {
    nOpenType = m_paOpenList[i].nType;

    if (nOpenType != PAGETYPE_NONE && m_paOpenList[i].iPage == iPage)
    {
      // When found, mark the item as PAGETYPE_DELETED.
      m_paOpenList[i].nType = PAGETYPE_DELETED;
      hr = NOERROR;
      break;
    }
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiList::RenumOpenItems

  Summary:  Private method. Renumber appropriate items in the open item
            array to account for a permanently deleted page.

  Args:     INT iPage,
              Dynamic number of deleted page.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiList::RenumOpenItems(
          INT iPage)
{
  HRESULT hr = NOERROR;
  SHORT nOpenType = PAGETYPE_NONE;
  INT i, iPg;
  CGuiText* pGuiText;
  CGuiDraw* pGuiDraw;

  // Renumber the remaining open pages to account for a permanently
  // deleted page.
  for (i=0; i<OPENLIST_SIZE; i++)
  {
    nOpenType = m_paOpenList[i].nType;
    iPg = m_paOpenList[i].iPage;

    if (nOpenType != PAGETYPE_NONE && iPg >= 0 && iPg > iPage)
    {
      if (iPg > 0)
      {
        iPg--;
        m_paOpenList[i].iPage = iPg;
        // Tell the open pages that they have a new dynamic page number.
        switch (nOpenType)
        {
          case PAGETYPE_TEXT:
            pGuiText = (CGuiText*) m_paOpenList[i].pGuiPage;
            if (NULL != pGuiText)
              hr = pGuiText->Renumber(iPg);
            break;
          case PAGETYPE_DRAWING:
            pGuiDraw = (CGuiDraw*) m_paOpenList[i].pGuiPage;
            if (NULL != pGuiDraw)
              hr = pGuiDraw->Renumber(iPg);
            break;
          default:
            break;
        }
      }
    }
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiList::CloseOpenItem

  Summary:  Private method. Delete the open item for the specified page
            in the open item array.

  Args:     INT iPage,
              Dynamic number of page open item to delete.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiList::CloseOpenItem(
          INT iPage)
{
  HRESULT hr = E_FAIL;
  SHORT nOpenType = PAGETYPE_NONE;
  INT i;

  // Loop thru the open list array and find the open page entry.
  for (i=0; i<OPENLIST_SIZE; i++)
  {
    nOpenType = m_paOpenList[i].nType;

    if (nOpenType != PAGETYPE_NONE && m_paOpenList[i].iPage == iPage)
    {
      // When found, mark the item as PAGETYPE_NONE.
      m_paOpenList[i].nType = PAGETYPE_NONE;
      hr = NOERROR;
      break;
    }
  }

  // Renumber the remaining open pages to account for a permanently
  // deleted page.
  if (SUCCEEDED(hr) && PAGETYPE_DELETED == nOpenType)
    RenumOpenItems(iPage);

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiList::SaveOpenPages

  Summary:  Private method. Loop through the open list and save all
            open pages.

  Args:     void.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiList::SaveOpenPages(void)
{
  HRESULT hr = E_FAIL;
  SHORT nOpenType;
  CGuiText* pGuiText;
  CGuiDraw* pGuiDraw;
  INT i;

  // Loop thru the open list array and save all open pages.
  for (i=0; i<OPENLIST_SIZE; i++)
  {
    nOpenType = m_paOpenList[i].nType;

    switch (nOpenType)
    {
      case PAGETYPE_TEXT:
        pGuiText = (CGuiText*) m_paOpenList[i].pGuiPage;
        if (NULL != pGuiText)
          hr = pGuiText->Save();
        break;
      case PAGETYPE_DRAWING:
        pGuiDraw = (CGuiDraw*) m_paOpenList[i].pGuiPage;
        if (NULL != pGuiDraw)
          hr = pGuiDraw->Save();
        break;
      default:
        break;
    }
  }

  if (SUCCEEDED(hr))
  {
    // All open pages saved so clear any changed flag.
    m_bChanged = FALSE;
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiList::CloseOpenPages

  Summary:  Private method. Loop through the open list and close all
            open pages.

  Args:     void.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiList::CloseOpenPages(void)
{
  HRESULT hr = E_FAIL;
  SHORT nOpenType;
  INT i;
  CGuiText* pGuiText;
  CGuiDraw* pGuiDraw;

  // Loop thru the open list array and close all open pages.
  for (i=0; i<OPENLIST_SIZE; i++)
  {
    nOpenType = m_paOpenList[i].nType;

    switch (nOpenType)
    {
      case PAGETYPE_TEXT:
        pGuiText = (CGuiText*) m_paOpenList[i].pGuiPage;
        if (NULL != pGuiText)
        {
          hr = pGuiText->Close();
          if (SUCCEEDED(hr))
          {
            m_paOpenList[i].nType = PAGETYPE_NONE;
          }
        }
        break;
      case PAGETYPE_DRAWING:
        pGuiDraw = (CGuiDraw*) m_paOpenList[i].pGuiPage;
        if (NULL != pGuiDraw)
        {
          hr = pGuiDraw->Close();
          if (SUCCEEDED(hr))
          {
            m_paOpenList[i].nType = PAGETYPE_NONE;
          }
        }
        break;
      default:
        break;
    }
  }

  if (SUCCEEDED(hr))
  {
    m_bChanged = FALSE;
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiList::ReleaseOpenPages

  Summary:  Private method. Loop throught the open list array and
            release storage for all open pages.

  Args:     void.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiList::ReleaseOpenPages(void)
{
  HRESULT hr = E_FAIL;
  SHORT nOpenType;
  INT i;
  CGuiText* pGuiText;
  CGuiDraw* pGuiDraw;

  // Loop thru the open list array and release all open page storage.
  for (i=0; i<OPENLIST_SIZE; i++)
  {
    nOpenType = m_paOpenList[i].nType;

    switch (nOpenType)
    {
      case PAGETYPE_TEXT:
        pGuiText = (CGuiText*) m_paOpenList[i].pGuiPage;
          hr = pGuiText->ReleasePage();
        break;
      case PAGETYPE_DRAWING:
        pGuiDraw = (CGuiDraw*) m_paOpenList[i].pGuiPage;
        if (NULL != pGuiDraw)
          hr = pGuiDraw->ReleasePage();
        break;
      default:
        break;
    }
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiList::RestoreOpenPages

  Summary:  Private method. Loop through the open list array and reopen
            storage for the open pages. Use the specified root storage.

  Args:     IStorage* pIStorage_Root)
              Root storage for the compound file containing the pages.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiList::RestoreOpenPages(
          IStorage* pIStorage_Root)
{
  HRESULT hr = E_FAIL;
  SHORT nOpenType;
  INT i;
  CGuiText* pGuiText;
  CGuiDraw* pGuiDraw;

  // Loop thru the open list array and reopen storage for the open pages.
  for (i=0; i<OPENLIST_SIZE; i++)
  {
    nOpenType = m_paOpenList[i].nType;

    switch (nOpenType)
    {
      case PAGETYPE_TEXT:
        pGuiText = (CGuiText*) m_paOpenList[i].pGuiPage;
        if (NULL != pGuiText)
        {
          hr = pGuiText->RestorePage(pIStorage_Root);
          if (SUCCEEDED(hr))
          {
            // Make sure the Text page in the reopend storage
            // matches the Text page object data in RAM.
            hr = pGuiText->Save();
          }
        }
        break;
      case PAGETYPE_DRAWING:
        pGuiDraw = (CGuiDraw*) m_paOpenList[i].pGuiPage;
        if (NULL != pGuiDraw)
        {
          hr = pGuiDraw->RestorePage(pIStorage_Root);
          if (SUCCEEDED(hr))
          {
            // Make sure the Draw page in the reopend storage
            // matches the Draw page object data in RAM.
            hr = pGuiDraw->Save();
          }
        }
        break;
      default:
        break;
    }
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiList::Load

  Summary:  Load PageList data from the current compound file.

  Args:     void.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiList::Load(void)
{
  HRESULT hr = E_FAIL;
  HCURSOR hCurWait = LoadCursor(NULL, IDC_WAIT);
  HCURSOR hCurPrev;
  TCHAR szTitle[MAX_PATH + 32];

  if (NULL != m_pPageFile)
  {
    // Change cursor to the hour glass.
    hCurPrev = SetCursor(hCurWait);

    // Ask the PageFile object to load the PageList data from the current
    // compound file. This load internally uses IPersist* features in a
    // COPageList object that is created and reconstituted from
    // persistent storage.
    hr = m_pPageFile->Load(NULL, &m_pIStorage_Root, &m_pIPageList);
    if (SUCCEEDED(hr))
    {
      // If we created and reconstituted a COPageList object then
      // connect the sinks in the client to the connection sources
      // in the server.
      hr = ConnectSink();
      if (SUCCEEDED(hr))
      {
        // Set Main Window Title.
        lstrcpy(szTitle, TEXT(MAIN_APP_NAME_STR));
        lstrcat(szTitle, m_szFileTitle);
        SetWindowText(m_hWnd, szTitle);

        // Set focus to ListWin and select first item in list.
        m_pListWin->SetCurSel(0);

        // Newly loaded file isn't changed yet.
        m_bChanged = FALSE;
      }
    }

    // Set Cursor back to what it was.
    SetCursor(hCurPrev);
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiList::Save

  Summary:  Calls on CPageFile to save the current PageList data in
            the current compound file.

  Args:     void.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiList::Save(void)
{
  HRESULT hr = E_FAIL;
  HCURSOR hCurWait = LoadCursor(NULL, IDC_WAIT);
  HCURSOR hCurPrev;

  if (NULL != m_pPageFile)
  {
    // Change cursor to the hour glass.
    hCurPrev = SetCursor(hCurWait);

    // Save any open pages if needed.
    SaveOpenPages();

    // Ask the PageFile object to save itself to the current file.
    hr = m_pPageFile->Save(m_pIStorage_Root, m_pIPageList);
    if (SUCCEEDED(hr))
      m_bChanged = FALSE;

    // Set Cursor back to what it was.
    SetCursor(hCurPrev);
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiList::AskSave

  Summary:  Checks if any open pages were changed or if the PageList dirty
            flag is set. The dirty flag is TRUE if the current PageList
            data was modified and is out of sync with the PageList data
            stored in the compound file. If a page was changed or if the
            PageList is dirty, then ask user in a simple dialog if he
            wants to save everthing. If he says yes, then save the current
            PageList data into the current compound file and tell any
            changed open pages to do the same.

  Args:     void.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
int CGuiList::AskSave(void)
{
  int iAns = IDNO;
  HRESULT hr;
  TCHAR szTitle[MAX_STRING_LENGTH];
  TCHAR szAsk[MAX_STRING_LENGTH];
  TCHAR szMsg[MAX_PATH + MAX_STRING_LENGTH];
  IPersistStream* pIPersistStream;

  hr = m_pIPageList->QueryInterface(
           IID_IPersistStream,
           (PPVOID)&pIPersistStream);
  if (SUCCEEDED(hr))
  {
    // Did any page change or is the PageList object dirty?
    if (m_bChanged || S_FALSE != pIPersistStream->IsDirty())
    {
      // The current data is dirty; ask user if he wants to save it.
      if (LoadString(m_hInst, IDS_FILE_CHANGED, szTitle, MAX_STRING_LENGTH)
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
        switch (iAns)
        {
          case IDYES:
            // Tell CPageFile to save itself to the current compound file.
            // Save any changed open pages as well.
            Save();
            break;
          case IDNO:
            // User clicked No. So don't save; abandon changes.
            m_bChanged = FALSE;
            break;
          case IDCANCEL:
          default:
            break;
        }
      }
    }

    // Done with IPersistStream for now so release it.
    pIPersistStream->Release();
  }

  return iAns;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiList::Close

  Summary:  Close down the existing Page List. This saves the current file
            if needed, disconnects the sinks, releases the COPageList COM
            object, and closes the file by releasing the IStorage.

  Args:     void.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiList::Close(void)
{
  HRESULT hr = NOERROR;
  TCHAR szTitle[MAX_PATH];
  HCURSOR hCurWait = LoadCursor(NULL, IDC_WAIT);
  HCURSOR hCurPrev;

  // Change cursor to the hour glass.
  hCurPrev = SetCursor(hCurWait);

  // Save the page list into the existing .PAG file if needed.
  m_pPageFile->Save(m_pIStorage_Root, m_pIPageList);

  // Disconnect the Sink in the client from the connection points in
  // the server.
  DisconnectSink();

  // Close the file by releasing the root IStorage.
  RELEASE_INTERFACE(m_pIStorage_Root);

  // Destroy the existing COPageList by releasing the IPageList interface.
  RELEASE_INTERFACE(m_pIPageList);

  // Set Main Window Title.
  lstrcpy(szTitle, TEXT(MAIN_APP_NAME_STR));
  lstrcat(szTitle, TEXT(NOFILE_STR));
  SetWindowText(m_hWnd, szTitle);

  // Set Cursor back to what it was.
  SetCursor(hCurPrev);

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiList::Open

  Summary:  If current PageList data has been modified then ask user if he
            wants to first save it to the current file. Then use Open File
            Name common dialog to ask user for a new file name to load. If
            user chooses a file name then load the PageList data from that
            compound file.

  Args:     void.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiList::Open(void)
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
    if (LoadString(m_hInst, IDS_OFN_PAGOPEN, szTitle, sizeof(szTitle)))
      m_ofnFile.lpstrTitle = szTitle;
    m_ofnFile.Flags = OFN_HIDEREADONLY | OFN_FILEMUSTEXIST;

    // Call up the dialog to get a file name from the user.
    bOpen = GetOpenFileName(&m_ofnFile);
    if (bOpen)
    {
      // Change cursor to the hour glass.
      hCurPrev = SetCursor(hCurWait);

      // Close any open pages.
      CloseOpenPages();

      // Close down the existing Page List. This saves the current
      // file if needed, disconnects the sinks, releases the
      // COPageList COM object, and closes the file by releasing
      // the root IStorage.
      Close();

      // Tell CPageFile object to load the Page List data from the newly
      // chosen compound file. This creates a new COPageList object.
      hr = m_pPageFile->Load(szFileName, &m_pIStorage_Root, &m_pIPageList);
      if (SUCCEEDED(hr))
      {
        // Connect the sinks in the client to the connection sources
        // in the server.
        hr = ConnectSink();
        if (SUCCEEDED(hr))
        {
          // Remember the new current compound file name.
          lstrcpy(m_szFileName, szFileName);

          // Set Main Window Title.
          lstrcpy(szFileName, TEXT(MAIN_APP_NAME_STR));
          lstrcat(szFileName, m_szFileTitle);
          SetWindowText(m_hWnd, szFileName);

          // Set focus to ListWin and select first item in list and
          // show the newly loaded page list.
          Show(0);
        }
      }

      // Set Cursor back to what it was.
      SetCursor(hCurPrev);
    }
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiList::SaveAs

  Summary:  Use the File SaveAs common dialog to ask user for a new file
            name to save to. Then save the current PageList data to the
            specified compound file. That file becomes the new current
            file. The previously open file is closed and left unchanged
            since the last save to it.

  Args:     void.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiList::SaveAs(void)
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
  if (LoadString(m_hInst, IDS_OFN_PAGSAVE, szTitle, sizeof(szTitle)))
    m_ofnFile.lpstrTitle = szTitle;
  m_ofnFile.Flags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;

  // Call up the dialog to get a file name from the user.
  bOpen = GetSaveFileName(&m_ofnFile);
  if (bOpen)
  {
    // Change cursor to the hour glass.
    hCurPrev = SetCursor(hCurWait);

    // No need to close any open page windows. But we do need to
    // release the existing Storage interfaces that are held for
    // those pages. For Drawing pages supporting IPersistStorage this
    // eventually calls HandsOffStorage on all the open draw pages.
    hr = ReleaseOpenPages();

    // Do the final close of the root storage of the existing file.
    RELEASE_INTERFACE(m_pIStorage_Root);

    // All open storages/streams in the file are released and closed.
    // Now copy a clone of the existing file (for the SaveAs).
    if (CopyFile(m_szFileName, szFileName, FALSE))
    {
      // Tell CPageFile object to save the PageList data to the newly
      // copied compound file.
      hr = m_pPageFile->SaveAs(szFileName, m_pIPageList, &m_pIStorage_Root);
      if (SUCCEEDED(hr))
      {
        // Client is done changing the file from underneath the open
        // pages. Now re-open storage for the existing open pages
        // using the data storages in the new file. For Drawing pages
        // that support IPersistStorage this eventually calls
        // SaveCompleted on all the open draw pages.
        hr = RestoreOpenPages(m_pIStorage_Root);
        if (SUCCEEDED(hr))
        {
          // Remember the new current compound file name.
          lstrcpy(m_szFileName, szFileName);

          // Set Main Window Title.
          lstrcpy(szFileName, TEXT(MAIN_APP_NAME_STR));
          lstrcat(szFileName, m_szFileTitle);
          SetWindowText(m_hWnd, szFileName);

          // Restored pages are assumed to match their file image.
          m_bChanged = FALSE;
        }
      }
    }

    // Set Cursor back to what it was.
    SetCursor(hCurPrev);
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiList::New

  Summary:  If current PageList data has been modified then ask user if he
            wants to first save it to the current file. Then use the
            SaveAs File Name common dialog to ask user for a new file name
            to Create. If user chooses a file name then create an empty
            new PageList compound file using the file name specified.

  Args:     void.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiList::New(void)
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
    // Use the File Save As common dialog to get file name from user.
    // Set the dialog's file filter and title.
    szFileName[0] = 0;
    m_ofnFile.lpstrFile = szFileName;
    if (LoadString(m_hInst, IDS_OFN_PAGSAVE, szTitle, sizeof(szTitle)))
      m_ofnFile.lpstrTitle = szTitle;
    m_ofnFile.Flags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;

    // Call up the dialog to get a file name from the user.
    bOpen = GetSaveFileName(&m_ofnFile);
    if (bOpen)
    {
      // Change cursor to the hour glass.
      hCurPrev = SetCursor(hCurWait);

      // Close any open pages.
      CloseOpenPages();

      // Close down the existing Page List. This saves the current
      // file if needed, disconnects the sinks, releases the COPageList
      // COM object, and closes the file by releasing the IStorage.
      Close();

      // Tell CPageFile object to create a new empty .PAG compound
      // file using the specified file name. This also creates
      // a new COPageList object.
      hr = m_pPageFile->New(szFileName, &m_pIStorage_Root, &m_pIPageList);
      if (SUCCEEDED(hr))
      {
        // Connect the sinks in the client to the connection sources
        // in the server.
        hr = ConnectSink();
        if (SUCCEEDED(hr))
        {
          // Remember the new current compound file name.
          lstrcpy(m_szFileName, szFileName);

          // Set Main Window Title.
          lstrcpy(szFileName, TEXT(MAIN_APP_NAME_STR));
          lstrcat(szFileName, m_szFileTitle);
          SetWindowText(m_hWnd, szFileName);

          // Set focus to ListWin and select first item in list and
          // show the newly loaded page list.
          Show(0);
        }
      }

      // Set Cursor back to what it was.
      SetCursor(hCurPrev);
    }
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiList::PageTitle

  Summary:  Uses a dialog box to edit the title of the currently selected
            page list item.

  Args:     void.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiList::PageTitle(void)
{
  HRESULT hr = E_FAIL;
  BOOL bOk;
  INT iOk, iPage;
  CDlgPageProps dlgPageProps;
  WCHAR wszPageTitle[PAGE_TITLE_SIZE];

  bOk = m_pListWin->GetCurSel(&iPage);
  if (bOk)
  {
    // Get the Page List title for this page number.
#if defined(UNICODE)
    hr = m_pIPageList->Get(iPage, NULL, NULL, g_szPageTitle, NULL);
#else
    hr = m_pIPageList->Get(iPage, NULL, NULL, wszPageTitle, NULL);
    if (SUCCEEDED(hr))
      UcToAnsi(wszPageTitle, g_szPageTitle, PAGE_TITLE_SIZE);
#endif

    // Ask the user for the new title of the page in the Page
    // Properties dialog.
    iOk = dlgPageProps.ShowDialog(
            m_hInst,
            MAKEINTRESOURCE(IDD_PAGE_PROPS),
            m_hWnd);
    if (iOk)
    {
      // If the user clicked Ok, then a new title was edited.
      // Ask the COPageList object to set the new title.
      // Use the Title entered by the user.
#ifdef UNICODE
      hr = m_pIPageList->Set(iPage, 0, g_szPageTitle);
#else
      // Convert to Unicode if we are compiled for Ansi.
      AnsiToUc(g_szPageTitle, wszPageTitle, PAGE_TITLE_SIZE);
      hr = m_pIPageList->Set(iPage, 0, wszPageTitle);
#endif
    }
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiList::PageOpen

  Summary:  Opens and loads the page object associated with the currently
            selected page list item. A separate window is used for
            editing the data of the loaded page.

  Args:     void.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiList::PageOpen(void)
{
  HRESULT hr = E_FAIL;
  BOOL bOk;
  INT iPage;
  SHORT nType;
  WCHAR wszTitle[PAGE_TITLE_SIZE];
  WCHAR wszDataName[PAGE_NAME_SIZE];
  void* pGuiPage;
  CGuiText* pGuiText;
  CGuiDraw* pGuiDraw;

  bOk = m_pListWin->GetCurSel(&iPage);
  if (bOk)
  {
    hr = GetOpenItem(iPage, &nType, &pGuiPage, &bOk);
    if (FAILED(hr))
    {
      // Failed means this page is not already open for editing.
      if (bOk)
      {
        // bOk means there is room for another open page, Get the page's
        // DataName and Title from the COPageList COM object and then
        // Create the separate edit window.
        hr = m_pIPageList->Get(iPage, NULL, &nType, wszTitle, wszDataName);
        if (SUCCEEDED(hr))
        {
          switch (nType)
          {
            case PAGETYPE_TEXT:
              pGuiText = new CGuiText(m_hInst, m_hWnd, iPage);
              if (NULL != pGuiText)
              {
                hr = pGuiText->OpenWin(m_pIStorage_Root, wszTitle, wszDataName);
                if (SUCCEEDED(hr))
                {
                  // Add an entry to the open list for the newly opened page.
                  hr = AddOpenItem(iPage, nType, pGuiText);
                }
              }
              else
                hr = E_OUTOFMEMORY;
              break;
            case PAGETYPE_DRAWING:
              pGuiDraw = new CGuiDraw(m_hInst, m_hWnd, iPage);
              if (NULL != pGuiDraw)
              {
                hr = pGuiDraw->OpenWin(m_pIStorage_Root, wszTitle, wszDataName);
                if (SUCCEEDED(hr))
                {
                  // Add an entry to the open list for the newly opened page.
                  hr = AddOpenItem(iPage, nType, pGuiDraw);
                }
              }
              else
                hr = E_OUTOFMEMORY;
              break;
            default:
              break;
          }
        }
      }
      else
      {
        // Put up error message box saying that ther are too many
        // open pages.
        ErrorBox(m_hInst, m_hWnd, IDS_TOOMANYOPEN);
      }
    }
    else
    {
      // The page is already open. Bring its window to top.
      switch (nType)
      {
        case PAGETYPE_TEXT:
          pGuiText = (CGuiText*) pGuiPage;
          if (NULL != pGuiText)
            hr = pGuiText->TopWin();
          break;
        case PAGETYPE_DRAWING:
          pGuiDraw = (CGuiDraw*) pGuiPage;
          if (NULL != pGuiDraw)
            hr = pGuiDraw->TopWin();
          break;
        default:
          break;
      }
    }
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiList::PageAdd

  Summary:  Add a new page of specified type to the page list. First
            creates the new page using the appropriate server and then
            adds an appropriate entry in the page list.

  Args:     SHORT nPageType
              The page type (eg, PAGETYPE_DRAWING).

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiList::PageAdd(
          SHORT nPageType)
{
  HRESULT hr = E_FAIL;
  BOOL bOk;
  WCHAR wszTitle[PAGE_TITLE_SIZE];
  WCHAR wszDataName[PAGE_NAME_SIZE];
  INT iPg;
  CGuiText* pGuiText;
  CGuiDraw* pGuiDraw;

  GetOpenItem(-1, NULL, NULL, &bOk);
  if (bOk)
  {
    // If there is room for another open page.
    // Ask the COPageList object to add a new page of the specified type.
    // Use "Untitled" as the default title.
#ifdef UNICODE
    hr = m_pIPageList->Add(-1, nPageType, TEXT(PAGE_UNTITLED_STR), &iPg);
#else
    {
      WCHAR wszPageTitle[PAGE_TITLE_SIZE];

      // Convert to Unicode if we are compiled for Ansi.
      AnsiToUc(TEXT(PAGE_UNTITLED_STR), wszPageTitle, PAGE_TITLE_SIZE);
      hr = m_pIPageList->Add(-1, nPageType, wszPageTitle, &iPg);
    }
#endif

    if (SUCCEEDED(hr))
    {
      // Open the new page for editing. Get the page's DataName and Title
      // and then Create the separate edit window.
      hr = m_pIPageList->Get(iPg, NULL, NULL, wszTitle, wszDataName);
      switch (nPageType)
      {
        case PAGETYPE_TEXT:
          pGuiText = new CGuiText(m_hInst, m_hWnd, iPg);
          if (NULL != pGuiText)
          {
            hr = pGuiText->OpenWin(m_pIStorage_Root, wszTitle, wszDataName);
            if (SUCCEEDED(hr))
            {
              // Add the newly opened page to the open list.
              hr = AddOpenItem(iPg, nPageType, pGuiText);
            }
          }
          else
            hr = E_OUTOFMEMORY;
          break;
        case PAGETYPE_DRAWING:
          pGuiDraw = new CGuiDraw(m_hInst, m_hWnd, iPg);
          if (NULL != pGuiDraw)
          {
            hr = pGuiDraw->OpenWin(m_pIStorage_Root, wszTitle, wszDataName);
            if (SUCCEEDED(hr))
            {
              // Add the newly opened page to the open list.
              hr = AddOpenItem(iPg, nPageType, pGuiDraw);
            }
          }
          else
            hr = E_OUTOFMEMORY;
          break;
        default:
          break;
      }
    }
  }
  else
  {
    // Put up error message box saying that ther are too many
    // open pages.
    ErrorBox(m_hInst, m_hWnd, IDS_TOOMANYOPEN);
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiList::PageDelete

  Summary:  Delete the page that corresponds to the currently selected
            page list item.

  Args:     void.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiList::PageDelete(void)
{
  HRESULT hr = E_FAIL;
  BOOL bOk;
  INT iPage;
  SHORT nType;
  WCHAR wszDataName[PAGE_NAME_SIZE];
  CGuiText* pGuiText = NULL;
  CGuiDraw* pGuiDraw = NULL;

  bOk = m_pListWin->GetCurSel(&iPage);
  if (bOk)
  {
    // Get the page's Type.
    hr = m_pIPageList->Get(iPage, NULL, &nType, NULL, wszDataName);
    if (SUCCEEDED(hr))
    {
      switch (nType)
      {
        case PAGETYPE_TEXT:
          hr = GetOpenItem(iPage, NULL, (void**)&pGuiText, NULL);
          if (SUCCEEDED(hr))
          {
            hr = pGuiText->Delete();
            if (SUCCEEDED(hr))
            {
              // Mark the open item as deleted. This will force a later
              // renumber of open page numbers to account for the
              // permanently missing page. This renumber will occur in
              // the PageClosed method when the page is closed.
              hr = DeleteOpenItem(iPage);
              // Now Close the GuiText window.
              pGuiText->Close();
            }
          }
          else
          {
            // If not open, just destroy the entire text page's stream.
            hr = m_pIStorage_Root->DestroyElement(wszDataName);
            if (SUCCEEDED(hr))
            {
              // Renumber any open pages as needed.
              hr = RenumOpenItems(iPage);
            }
          }
          break;
        case PAGETYPE_DRAWING:
          hr = GetOpenItem(iPage, NULL, (void**)&pGuiDraw, NULL);
          if (SUCCEEDED(hr))
          {
            hr = pGuiDraw->Delete();
            if (SUCCEEDED(hr))
            {
              // Mark the open item as deleted. This will force a later
              // renumber of open page numbers to account for the
              // permanently missing page. This renumber will occur in
              // the PageClosed method when the page is closed.
              hr = DeleteOpenItem(iPage);
              // Now Close the GuiDraw window.
              pGuiDraw->Close();
            }
          }
          else
          {
            // If not open, just destroy the entire draw page's storage.
            hr = m_pIStorage_Root->DestroyElement(wszDataName);
            if (SUCCEEDED(hr))
            {
              // Renumber any open pages as needed.
              hr = RenumOpenItems(iPage);
            }
          }
          break;
        default:
          break;
      }
    }

    if (SUCCEEDED(hr))
    {
      // Finally, delete the page from the page list.
      hr = m_pIPageList->Delete(iPage);
    }
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiList::PageChanged

  Summary:  An open page was changed.

  Args:     INT iPage)
              Page number of the page that changed.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiList::PageChanged(
         INT iPage)
{
  HRESULT hr = NOERROR;;

  m_bChanged |= TRUE;

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiList::PageClosed

  Summary:  A page editing window was closed.

  Args:     INT iPage)
              Page number of the page that was closed.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiList::PageClosed(
         INT iPage)
{
  HRESULT hr;

  // Mark the open item for the page as closed in the open item array.
  hr = CloseOpenItem(iPage);

  return hr;
}
