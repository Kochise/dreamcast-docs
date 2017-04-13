/*+==========================================================================
  File:      GUITEXT.CPP

  Summary:   Implementation file for the CGuiText C++ class. A GuiText is
             a C++ object that encapsulates the human interface for
             editing the text of a persistent text object.

             CGuiText is anchored to the Windows GUI (Graphical User
             Interface) environment--it retains knowledge of window
             handles and device contexts on the local machine. This
             GuiText object relies on a persistent Text object for storage
             of the text data. This text object (a COTextPage object) is
             instantiated as a COM object in a separate thread-safe
             In-process server, PERTEXT.

             For a comprehensive tutorial code tour of GUITEXT's contents
             and offerings see the tutorial PERCLIEN.HTM file. For more
             specific technical details on the internal workings see the
             comments dispersed throughout the GUITEXT source code.

  Classes:   CGuiText.

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
  We include APPUTIL.H because we will be building this application using
    the convenient Virtual Window and Dialog classes and other
    utility functions in the APPUTIL Library (ie, APPUTIL.LIB).
  We include IPAGES.H and PAGEGUID.H for the common page-related Interface
    class, GUID, and CLSID specifications.
  We include RESDEF.H because it has the resource definitions specific
    to this application.
  We include TEXTWIN.H because CGuiText creates and uses a CTextWin to
    encapsulate a multiline edit control/window.
  We include GUITEXT.H because it has the C++ class used for GUI display
    of the edited text.
  We include TEXTSINK.H because it has the C++ class used for the sink that
    receives event notifications from the COTextPage object in the server.
---------------------------------------------------------------------------*/
#include <windows.h>
#include <ole2.h>
#include <olectl.h>
#include <apputil.h>
#include <ipages.h>
#include <pageguid.h>
#include "resdef.h"
#include "textwin.h"
#include "guitext.h"
#include "textsink.h"


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiText::CGuiText

  Summary:  Constructor.

  Args:     void

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CGuiText::CGuiText(HINSTANCE hInst, HWND hWndApp, INT iPage)
{
  m_hInst           = hInst;
  m_hWndApp         = hWndApp;
  m_hWnd            = NULL;
  m_iPage           = iPage;
  m_wszDataName[0]  = 0;
  m_pTextWin        = NULL;
  m_pIStorage_Root  = NULL;
  m_pITextPage      = NULL;
  m_pCOTextPageSink = NULL;
  m_dwTextPageSink  = 0;
  m_bChanged        = FALSE;

  // Save the ClassID of TextPages using overloaded '=' operator.
  m_CidTextPage = CLSID_TextPage;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiText::~CGuiText

  Summary:  Destructor.

  Args:     void

  Returns:  void
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
CGuiText::~CGuiText(void)
{
  // CGuiText is derived from CVirWindow which traps the WM_DESTROY
  // message and causes a delete of CGuiText which in turn causes this
  // destructor to run. The WM_DESTROY results when the window is destoyed
  // after a close of the window.

  // Disconnect the Sink in the client from the connection points in
  // the server.
  DisconnectSink();

  // Release the interface held on the TextPageSink object.
  RELEASE_INTERFACE(m_pCOTextPageSink);

  // Destroy the existing COTextPage by releasing the ITextPage interface.
  RELEASE_INTERFACE(m_pITextPage);

  // Release the interface held on the root storage.
  RELEASE_INTERFACE(m_pIStorage_Root);

  // Delete the CTextWin object (edit control window).
  DELETE_POINTER(m_pTextWin);

  // Tell main app that this text page is gone.
  PostMessage(m_hWndApp, WM_USER_PAGECLOSED, 0, m_iPage);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiText::Clear

  Summary:  Internal private method to clear (erase) the text content of
            both the current text edit window as well as the COTextPage
            server.

  Args:     void.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiText::Clear(
          void)
{
  HRESULT hr = E_FAIL;

  if (NULL != m_pTextWin && NULL != m_pITextPage)
  {
    m_pTextWin->Clear();
    m_pITextPage->Clear(TRUE);
    m_bChanged = TRUE;
    // Tell main app if this page was changed.
    PostMessage(m_hWndApp, WM_USER_PAGECHANGED, 0, m_iPage);
    hr = NOERROR;
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiText::Load

  Summary:  Load TextPage data from the current storage Stream.

  Args:     void.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiText::Load(void)
{
  HRESULT hr = E_FAIL;
  IStream* pIStream;
  IPersistStreamInit* pIPersistStreamInit;

  // Can't do anything without a root storage.
  if (NULL != m_pIStorage_Root)
  {
    // Use the root IStorage to open the existing stream for
    // this particular Text Page. Load the data for the text page from
    // the stream. This load internally uses the IPersistStreamInit
    // features in a COTextPage object that is created and reconstituted
    // from persistent storage.

    // Open the single stream named by m_wszDataName. It is under
    // the root storage.
    hr = m_pIStorage_Root->OpenStream(
           m_wszDataName,
           0,
           STGM_READWRITE | STGM_DIRECT | STGM_SHARE_EXCLUSIVE,
           0,
           &pIStream);
    if (SUCCEEDED(hr))
    {
      // Read the ClassID for the class of Component Objects that can deal
      // with Text Page data.
      hr = ReadClassStm(pIStream, &m_CidTextPage);
      if (SUCCEEDED(hr))
      {
        // Now use the obtained Class ID to create a COTextPage
        // object. Initially ask for the ITextPage interface.
        hr = CoCreateInstance(
               m_CidTextPage,
               NULL,
               CLSCTX_INPROC_SERVER,
               IID_ITextPage,
               (PPVOID)&m_pITextPage);
        if (SUCCEEDED(hr))
        {
          // We have a new COTextPage object. Now obtain the
          // IPersistStreamInit interface on it. At this point in the
          // client we are assuming that COTextPage uses only the
          // IPersistStreamInit interface for its persistence.
          hr = m_pITextPage->QueryInterface(
                 IID_IPersistStreamInit,
                 (PPVOID)&pIPersistStreamInit);
          if (SUCCEEDED(hr))
          {
            // And as expected by this client, COTextPage exposes
            // the IPersistStreamInit interface. Now use this interface
            // to ask the COTextPage object to load the Text Page data.
            hr = pIPersistStreamInit->Load(pIStream);

            // Done with IPersistStreamInit for now so release it.
            pIPersistStreamInit->Release();
          }
        }
      }
      // Done with the interface held on the stream.
      pIStream->Release();
    }
    else
    {
      // If there was no existing Stream then create a new one.
      hr = m_pIStorage_Root->CreateStream(
             m_wszDataName,
             STGM_CREATE | STGM_READWRITE | STGM_DIRECT | STGM_SHARE_EXCLUSIVE,
             0,
             0,
             &pIStream);
      if (SUCCEEDED(hr))
      {
        // Write the ClassID of the COTextPage component object class.
        hr = WriteClassStm(pIStream, m_CidTextPage);
        if (SUCCEEDED(hr))
        {
          // Now use the Class ID to create a COTextPage
          // object. Initially ask for the ITextPage interface.
          hr = CoCreateInstance(
                 m_CidTextPage,
                 NULL,
                 CLSCTX_INPROC_SERVER,
                 IID_ITextPage,
                 (PPVOID)&m_pITextPage);
          if (SUCCEEDED(hr))
          {
            // We have a new COTextPage object. Now obtain the
            // IPersistStreamInit interface on it. At this point in the
            // client we are assuming that COTextPage uses only the
            // IPersistStreamInit interface for its persistence.
            hr = m_pITextPage->QueryInterface(
                   IID_IPersistStreamInit,
                   (PPVOID)&pIPersistStreamInit);
            if (SUCCEEDED(hr))
            {
              // And as expected by this client, COTextPage supports
              // the IPersistStreamInit interface. Now use this interface
              // to ask the COTextPage object to initialize a new empty
              // text page. Then save it into the stream.
              hr = pIPersistStreamInit->InitNew();
              if (SUCCEEDED(hr))
                hr = pIPersistStreamInit->Save(pIStream, TRUE);

              // Done with IPersistStreamInit for now so release it.
              pIPersistStreamInit->Release();
            }
          }
        }

        // Done with the interface held on the stream.
        pIStream->Release();

        if (FAILED(hr))
          m_pIStorage_Root->DestroyElement(m_wszDataName);
      }
    }
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiText::OpenWin

  Summary:  Get CGuiText started. Make any subordinate objects, like
            COTextPage and CTextWin and get them started. Create the
            window. Read the page's text data from the specified stream
            and put it in the edit control.

  Args:     IStorage* pIStorage_Root,
              Root storage of the compound file containing the text page.
            WCHAR* pwszPageTitle,
              The user-displayable title for the text page. Generally
              used in the window's title bar.
            WCHAR* pwszDataName)
              The internal storage name of the stream holding the
              text page.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiText::OpenWin(
          IStorage* pIStorage_Root,
          WCHAR* pwszPageTitle,
          WCHAR* pwszDataName)
{
  HRESULT hr = E_FAIL;
  HWND hWnd = NULL;
  COTextPageSink* pCobSink = NULL;
  HCURSOR hCurPrev;
  HCURSOR hCurWait = LoadCursor(NULL, IDC_WAIT);
  TCHAR szTitle[32+PAGE_TITLE_SIZE];
  INT iTextLength;
  WCHAR* pwszText;

  if (m_hInst && m_hWndApp && pwszDataName)
  {
    // Change cursor to the hour glass. This open could take awhile.
    hCurPrev = SetCursor(hCurWait);

    // Set title string empty to start.
    szTitle[0] = 0;

    lstrcpy(szTitle, TEXT(TEXT_WINDOW_NAME_STR));
#if defined(UNICODE)
    if (NULL != pwszPageTitle)
      lstrcat(szTitle, pwszPageTitle);
    lstrcpy(m_wszDataName, pwszDataName);
#else
    {
      CHAR szAnsi[PAGE_TITLE_SIZE];

      // Convert PageTitle from Unicode to Ansi.
      if (NULL != pwszPageTitle)
      {
        UcToAnsi(pwszPageTitle, szAnsi, PAGE_TITLE_SIZE);
        lstrcat(szTitle, szAnsi);
      }
      // Copy/save DataName.
      memcpy(m_wszDataName, pwszDataName, PAGE_NAME_SIZE*sizeof(WCHAR));
    }
#endif
    // Create the main GuiText Window. Size the window reasonably. The
    // Create method sets both m_hInst and m_hWnd.
    hWnd = Create(
             TEXT(TEXT_WINDOW_CLASS_NAME_STR),
             szTitle,
             WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX
               | WS_MAXIMIZEBOX | WS_THICKFRAME,
             CW_USEDEFAULT,
             CW_USEDEFAULT,
             ::GetSystemMetrics(SM_CXSCREEN)*1/3,
             ::GetSystemMetrics(SM_CYSCREEN)*1/3,
             m_hWndApp,
             NULL,
             m_hInst);
    if (NULL != hWnd)
    {
      // Create the CTextWin object so we can edit/show text data
      // in the text window using a standard text edit control.
      m_pTextWin = new CTextWin;
      if (NULL != m_pTextWin)
      {
        // Init the CTextWin. This creates the subordinate edit control
        // window and fits it into the client area of the main edit window.
        hr = m_pTextWin->Init(m_hInst, m_hWnd, &m_hWndEdit);
        if (SUCCEEDED(hr))
        {
          // Save an interface pointer to the root IStorage
          // and AddRef it.
          m_pIStorage_Root = pIStorage_Root;
          pIStorage_Root->AddRef();

          // Now load the text edit control from the named stream in the
          // root storage. This either opens and loads the existing
          // stream or creates a new one.
          hr = Load();
          if (SUCCEEDED(hr))
          {
            // We loaded or created the Text Page stream and have a
            // COTextPage component to manage the text data.

            // Create the COTextPageSink object to receive TextPage events.
            pCobSink = new COTextPageSink(NULL, this);
            if (NULL != pCobSink)
            {
              // Save a pointer to the COTextPageSink IUnknown interface.
              // AddRef because of this saved copy. Released in destructor.
              m_pCOTextPageSink = pCobSink;
              m_pCOTextPageSink->AddRef();

              // Ask the COTextPage for the text data and pass it on to
              // the Edit control managed by CTextWin.

              // First ask for the size (in WCHARs) of the text data.
              hr = m_pITextPage->GetLength(&iTextLength);
              if (SUCCEEDED(hr))
              {
                // Allocate some temporary space for the text.
                pwszText = new WCHAR[iTextLength+4];
                if (NULL != pwszText)
                {
                  // Zero the text string.
                  memset(pwszText, 0, (iTextLength+2) * sizeof(WCHAR));

                  // Get the text from the COTextPage object.
                  hr = m_pITextPage->GetText(pwszText);
                  if (SUCCEEDED(hr))
                  {
                    // Put the text into the edit control.
                    hr = m_pTextWin->PutText(pwszText, iTextLength);
                    if (SUCCEEDED(hr))
                    {
                      // Ensure the new window is shown on screen.
                      ::ShowWindow(m_hWnd, SW_SHOWNORMAL);
                      ::UpdateWindow(m_hWnd);
                    }
                  }
                  // Delete the temporary string buffer.
                  delete [] pwszText;
                }
                else
                  hr = E_OUTOFMEMORY;
              }
            }
            else
              hr = E_OUTOFMEMORY;
          }
        }
      }
      else
        hr = E_OUTOFMEMORY;

      if (SUCCEEDED(hr))
      {
        // If we created and reconstituted a COTextPage object from
        // persistent stream storage then connect the sinks in the client
        // to the connection sources in the server.
        hr = ConnectSink();
      }
      else
      {
        HrMsgId(m_hInst, m_hWnd, IDS_OPENTEXTPAGE, hr);
        PostMessage(m_hWnd, WM_CLOSE, 0, 0);
      }
    }

    // Set Cursor from hourglass back to what it was.
    SetCursor(hCurPrev);
  }

  return (hr);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiText::TopWin

  Summary:  Brings the CGuiText window to the top of the z-order of the
            the windows.

  Args:     void.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiText::TopWin(
          void)
{
  HRESULT hr = E_FAIL;

  if (IsWindow(m_hWnd))
  {
    BringWindowToTop(m_hWnd);
    hr = NOERROR;
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiText::ResizeWin

  Summary:  Resize the current CGuiText window. Pass this resize on to the
            text edit control child window.

  Args:     WORD wWidth,
              New window width in pixels.
            WORD wHeight)
              New window height in pixels.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiText::ResizeWin(
          WORD wWidth,
          WORD wHeight)
{
  HRESULT hr;

  // Tell Text Edit window  about new size.
  hr = m_pTextWin->Resize(wWidth, wHeight);

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiText::Renumber

  Summary:  Re-assign the current dynamic page number for this page.

  Args:     INT iPage
              New page number.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiText::Renumber(
          INT iPage)
{
  HRESULT hr = NOERROR;

  m_iPage = iPage;

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiText::ReleasePage

  Summary:  Release the root storage held by the Text page.

  Args:     none.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiText::ReleasePage(
          void)
{
  HRESULT hr = E_FAIL;

  // Release the interface held on the root storage by CGuiText.
  RELEASE_INTERFACE(m_pIStorage_Root);

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiText::RestorePage

  Summary:  Restores the root storage interface for a new file.

  Args:     IStorage* pIStorage_Root
              New storage for the Text page.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiText::RestorePage(
          IStorage* pIStorage_Root)
{
  HRESULT hr = E_POINTER;

  if (NULL != pIStorage_Root)
  {
    // Save the new interface pointer to the root IStorage
    // and AddRef it.
    m_pIStorage_Root = pIStorage_Root;
    m_pIStorage_Root->AddRef();
    hr = NOERROR;
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiText::Save

  Summary:  Uses COTextPage's IPersistStreamInit interface to save the
            text data in the text page's stream.

  Args:     void.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiText::Save(void)
{
  HRESULT hr = E_FAIL;
  HCURSOR hCurWait = LoadCursor(NULL, IDC_WAIT);
  HCURSOR hCurPrev;
  INT iTextLength;
  WCHAR* pwszText;
  LARGE_INTEGER liSeek;
  IStream* pIStream;
  IPersistStreamInit* pIPersistStreamInit;

  if (NULL != m_pIStorage_Root && NULL != m_pITextPage)
  {
    // Change cursor to the hour glass.
    hCurPrev = SetCursor(hCurWait);

    // Open the single stream named by m_wszDataName. It is under
    // the root storage.
    hr = m_pIStorage_Root->OpenStream(
           m_wszDataName,
           0,
           STGM_READWRITE | STGM_DIRECT | STGM_SHARE_EXCLUSIVE,
           0,
           &pIStream);
    if (SUCCEEDED(hr))
    {
      // First ask the edit control how long its text data is.
      hr = m_pTextWin->GetLength(&iTextLength);
      if (SUCCEEDED(hr))
      {
        // Allocate some temporary space for the text.
        pwszText = new WCHAR[iTextLength+4];
        if (NULL != pwszText)
        {
          // Zero the text string.
          memset(pwszText, 0, (iTextLength+2) * sizeof(WCHAR));

          // Get the text from the the edit control.
          hr = m_pTextWin->GetText(pwszText);
          if (SUCCEEDED(hr))
          {
            // Put the text into the COTextPage object.
            hr = m_pITextPage->PutText(pwszText, iTextLength);
            if (SUCCEEDED(hr))
            {
              // Clear the TextWin changed flag.
              m_bChanged = FALSE;

              // Tell the COTextPage object to save itself
              // (via its IPersistStreamInit interface).
              hr = m_pITextPage->QueryInterface(
                     IID_IPersistStreamInit,
                     (PPVOID)&pIPersistStreamInit);
              if (SUCCEEDED(hr))
              {
                // Recue Stream to start of page text data.
                LISet32(liSeek, sizeof(CLSID));
                hr = pIStream->Seek(liSeek, STREAM_SEEK_SET, NULL);
                if (SUCCEEDED(hr))
                  hr = pIPersistStreamInit->Save(pIStream, TRUE);

                // Done with IPersistStreamInit for now so release it.
                pIPersistStreamInit->Release();
              }
            }
          }
          // Delete the temporary text buffer.
          delete [] pwszText;
        }
        else
          hr = E_OUTOFMEMORY;
      }
      // Done with the interface held on the stream.
      pIStream->Release();
    }

    // Set Cursor back to what it was.
    SetCursor(hCurPrev);
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiText::AskSave

  Summary:  Check if user edited any changes in the edit window. Also
            checks dirty flag (ie, if current TextPage data was modified
            and is out of sync with the TextPage data stored in the
            compound file). If changed or dirty, then ask user in simple
            dialog if he wants to save new data. If he says yes, then save
            the current TextPage data into the current compound file.

  Args:     void.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
int CGuiText::AskSave(void)
{
  int iAns = IDNO;
  HRESULT hr;
  TCHAR szTitle[MAX_STRING_LENGTH];
  TCHAR szAsk[MAX_STRING_LENGTH];
  TCHAR szMsg[MAX_PATH + MAX_STRING_LENGTH];
  IPersistStreamInit* pIPersistStreamInit;

  hr = m_pITextPage->QueryInterface(
           IID_IPersistStreamInit,
           (PPVOID)&pIPersistStreamInit);
  if (SUCCEEDED(hr))
  {
    // If changed or if the TextPage object is dirty.
    if (m_bChanged || S_FALSE != pIPersistStreamInit->IsDirty())
    {
      // The current data was changed; ask user if he wants to save it.
      if (LoadString(m_hInst, IDS_TEXT_PAGE, szTitle, MAX_STRING_LENGTH)
          && LoadString(m_hInst, IDS_ASK_SAVE, szAsk, MAX_STRING_LENGTH))
      {
        lstrcpy(szMsg, szTitle);
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
            // Tell CGuiText to save itself to the current text page stream.
            Save();
            break;
          case IDNO:
            // User clicked No. So don't save; abandon changes.
            break;
          case IDCANCEL:
          default:
            break;
        }
      }
    }

    // Done with IPersistStreamInit for now so release it.
    pIPersistStreamInit->Release();
  }

  return iAns;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiText::Close

  Summary:  Close this page.

  Args:     void.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiText::Close(
          void)
{
  HRESULT hr = NOERROR;

  // Close the GuiText window. This will cause a delete of this CGuiText.
  ::PostMessage(m_hWnd, WM_CLOSE, 0, 0);

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiText::Delete

  Summary:  Delete the stored Text Page. Shuts down the text page and edit
            windows. Disconnects the Sink and does final release of the
            COTextPage object.

  Args:     void.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiText::Delete(void)
{
  HRESULT hr = E_FAIL;
  HCURSOR hCurWait = LoadCursor(NULL, IDC_WAIT);
  HCURSOR hCurPrev;

  // Change cursor to the hour glass.
  hCurPrev = SetCursor(hCurWait);

  // Clear the text page.
  if (NULL != m_pTextWin && NULL != m_pITextPage)
  {
    m_pTextWin->Clear();
    m_pITextPage->Clear(FALSE);
    m_bChanged = FALSE;
  }

  // Destroy the entire text page's stream.
  hr = m_pIStorage_Root->DestroyElement(m_wszDataName);

  // Set Cursor back to what it was.
  SetCursor(hCurPrev);

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiText::GetConnectionPoint

  Summary:  Internal private method to obtain a connection point interface.

  Args:     REFIID riid
              IID of the requested connection point Interface.

  Returns:  IConnectionPoint*
              Requested IConnectionPoint interface pointer. NULL if none.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
IConnectionPoint* CGuiText::GetConnectionPoint(
                    REFIID riid)
{
  IConnectionPoint* pConnPoint = NULL;
  IConnectionPointContainer* pConnPointContainer = NULL;
  IConnectionPoint* pConnPt;
  HRESULT hr;

  // First query the object for its Connection Point Container. This
  // essentially asks the object in the server if it is connectable.
  hr = m_pITextPage->QueryInterface(
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
  Method:   CGuiText::ConnectSink

  Summary:  Connect the TextPageSink to the server COTextPage event
            source.

  Args:     void

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiText::ConnectSink(void)
{
  HRESULT hr = E_FAIL;
  DWORD dwKey;
  IConnectionPoint* pConnPoint;

  if (!m_dwTextPageSink)
  {
    // Get the Text Page Sink connection point in the server.
    pConnPoint = GetConnectionPoint(IID_ITextPageSink);
    if (NULL != pConnPoint)
    {
      // Connect the server's object to the Text Page Sink in this client.
      hr = pConnPoint->Advise(m_pCOTextPageSink, &dwKey);
      if (SUCCEEDED(hr))
        m_dwTextPageSink = dwKey;

      RELEASE_INTERFACE(pConnPoint);
    }
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiText::DisconnectSink

  Summary:  Disconnect the Text Page from the server COTextPage event
            source.

  Args:     void.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiText::DisconnectSink(void)
{
  HRESULT hr = E_FAIL;
  IConnectionPoint* pConnPoint;

  if (m_dwTextPageSink)
  {
    // Get the TextPage Sink connection point.
    pConnPoint = GetConnectionPoint(IID_ITextPageSink);
    if (NULL != pConnPoint)
    {
      // Disconnect the object in the server from the Text Page Sink in
      // this client.
      hr = pConnPoint->Unadvise(m_dwTextPageSink);
      if (SUCCEEDED(hr))
        m_dwTextPageSink = 0;

      RELEASE_INTERFACE(pConnPoint);
    }
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiText::InitEditMenu

  Summary:  Init the Parent Window's Edit menu for edit operations.

  Args:     HMENU hEditMenu)
              Handle of the Edit Menu of the parent window.

  Returns:  HRESULT
              Standard result code. NOERROR for success.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
HRESULT CGuiText::InitEditMenu(
          HMENU hEditMenu)
{
  HRESULT hr = E_FAIL;
  INT iSelect, iEnable;

  if (IsWindow(m_hWnd))
  {
    // Enable/Disable the Undo choice.
    EnableMenuItem(
      hEditMenu,
      IDM_EDIT_UNDO,
      SendMessage(m_hWndEdit, EM_CANUNDO, 0, 0) ? MF_ENABLED : MF_GRAYED);

    // Enable/Disable the Paste choice.
    EnableMenuItem(
      hEditMenu,
      IDM_EDIT_PASTE,
      IsClipboardFormatAvailable(CF_TEXT) ? MF_ENABLED : MF_GRAYED);

    // Enable/Disable the Cut, Copy, Delete choices.
    iSelect = SendMessage(m_hWndEdit, EM_GETSEL, 0, 0);
    iEnable = (HIWORD(iSelect) == LOWORD(iSelect)) ? MF_GRAYED : MF_ENABLED;
    EnableMenuItem(hEditMenu, IDM_EDIT_CUT, iEnable);
    EnableMenuItem(hEditMenu, IDM_EDIT_COPY, iEnable);
    EnableMenuItem(hEditMenu, IDM_EDIT_DELETE, iEnable);

    hr = NOERROR;
  }

  return hr;
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiText::DoCommand

  Summary:  Dispatch and handle the main menu and other commands.

  Args:     WPARAM wParam,
              First message parameter.
            LPARAM lParam)
              Second message parameter.

  Returns:  LRESULT
              Standard Windows WindowProc return value.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CGuiText::DoCommand(
          WPARAM wParam,
          LPARAM lParam)
{
  LRESULT lResult = FALSE;
  HMENU hMenu  = ::GetMenu(m_hWnd);

  switch (LOWORD(wParam))
  {
    //----------------------------------------------------------------------
    // Handle Text Menu Commands.
    //----------------------------------------------------------------------
    case IDM_TEXT_SAVE:
      Save();
      break;
    case IDM_TEXT_CLEAR:
      Clear();
      break;
    case IDM_TEXT_EXIT:
      // The user commands us to exit this page so we tell the
      // window to close itself.
      ::PostMessage(m_hWnd, WM_CLOSE, 0, 0);
      break;

    //----------------------------------------------------------------------
    // Handle Edit Menu Commands.
    //----------------------------------------------------------------------
    case IDM_EDIT_UNDO:
      m_pTextWin->EditUndo();
      break;
    case IDM_EDIT_SELECTALL:
      m_pTextWin->EditSelectAll();
      break;
    case IDM_EDIT_CUT:
      m_pTextWin->EditCut();
      break;
    case IDM_EDIT_COPY:
      m_pTextWin->EditCopy();
      break;
    case IDM_EDIT_PASTE:
      m_pTextWin->EditPaste();
      break;
    case IDM_EDIT_DELETE:
      m_pTextWin->EditDelete();
      break;

    //----------------------------------------------------------------------
    // Handle Help Menu Commands. Pass these commands on to main app.
    //----------------------------------------------------------------------
    case IDM_THELP_CONTENTS:
      PostMessage(m_hWndApp, WM_COMMAND, (WPARAM) IDM_HELP_CONTENTS, 0);
      break;
    case IDM_THELP_TUTORIAL:
      PostMessage(m_hWndApp, WM_COMMAND, (WPARAM) IDM_HELP_TUTORIAL, 0);
      break;
    case IDM_THELP_TUTSERVER:
      PostMessage(m_hWndApp, WM_COMMAND, (WPARAM) IDM_HELP_PERTEXT, 0);
      break;
    case IDM_THELP_READSOURCE:
      PostMessage(m_hWndApp, WM_COMMAND, (WPARAM) IDM_HELP_READSOURCE, 0);
      break;
    case IDM_THELP_ABOUT:
      PostMessage(m_hWndApp, WM_COMMAND, (WPARAM) IDM_HELP_ABOUT, 0);
      break;

    //----------------------------------------------------------------------
    // Handle TextWin Commands (ie, from the child edit control).
    //----------------------------------------------------------------------
    case IDC_TEXTWIN:
      switch (HIWORD(wParam))
      {
        case EN_CHANGE:
          if (!m_bChanged)
          {
            m_bChanged = TRUE;
            // Tell main app if this page was changed.
            PostMessage(m_hWndApp, WM_USER_PAGECHANGED, 0, m_iPage);
          }
          break;
        case EN_MAXTEXT:
        case EN_ERRSPACE:
          ErrorBox(m_hInst, m_hWnd, IDS_PAGEFULL);
          break;
        default:
          break;
      }
      break;

    default:
      // Defer all messages NOT handled here to the Default Window Proc.
      lResult = ::DefWindowProc(m_hWnd, WM_COMMAND, wParam, lParam);
      break;
  }

  return(lResult);
}


/*M+M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M+++M
  Method:   CGuiText::WindowProc

  Summary:  Main window procedure for this window object.  See CVirWindow
            in the APPUTIL library (APPUTIL.CPP) for details on how this
            method gets called by the global WindowProc.

  Args:     UINT uMsg,
              Windows message that is "sent" to this window.
            WPARAM wParam,
              First message parameter.
            LPARAM lParam)
              Second message parameter.

  Returns:  LRESULT
              Standard Windows WindowProc return value.
M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M---M-M*/
LRESULT CGuiText::WindowProc(
          UINT uMsg,
          WPARAM wParam,
          LPARAM lParam)
{
  LRESULT lResult = FALSE;

  switch (uMsg)
  {
    case WM_CREATE:
      break;

    case WM_SIZE:
      // Handle a resize of this window.
      // Inform CGuiText and CTextWin of the change.
      ResizeWin(LOWORD(lParam), HIWORD(lParam));
      break;

    case WM_INITMENUPOPUP:
      // Enable Edit Menu items.
      if (LOWORD(lParam) == 1)
        InitEditMenu((HMENU) wParam);
      break;

    case WM_COMMAND:
      // Dispatch and handle any Menu and command messages received.
      lResult = DoCommand(wParam, lParam);
      break;

    case WM_CHAR:
      if (wParam == 0x1b)
      {
        // Exit this app if user hits ESC key.
        ::PostMessage(m_hWnd, WM_CLOSE, 0, 0);
      }
      break;

    case WM_CLOSE:
      // The user selected Close on the main window's System menu
      // or Exit on the File menu.
      // If there is data that has not been saved then ask user
      // if it should be saved. If user cancels then cancel the exit.
      if (IDCANCEL == AskSave())
        break;
    case WM_QUIT:
      BringWindowToTop(m_hWndApp);
      // If the app is being quit then close any associated help windows.
      // For later evolution...
    default:
      // Defer all messages NOT handled above to the Default Window Proc.
      lResult = ::DefWindowProc(m_hWnd, uMsg, wParam, lParam);
      break;
  }

  return(lResult);
}
