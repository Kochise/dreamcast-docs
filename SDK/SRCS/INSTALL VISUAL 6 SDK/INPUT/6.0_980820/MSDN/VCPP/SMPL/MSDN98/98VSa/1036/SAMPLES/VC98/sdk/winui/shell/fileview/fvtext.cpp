//THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
//ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
//THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//
// Copyright  1994-1996  Microsoft Corporation.  All Rights Reserved.
//
//    PROGRAM: FVTEXT.CPP        
//
//    PURPOSE:  Sample FileViewer for text files to integrate with the Explorer.  This sample serves as a 
//    framework for custom viewers.  Initialization and other low-use functions are in FVMISC.CPP.
//
//    PLATFORMS:    Windows 95
//
//    FUNCTIONS:    
//   
//
//    SPECIAL INSTRUCTIONS: N/A
//

#include "fileview.h"

//
//   FUNCTION: CFileViewer::CFileViewer    
//
//   PURPOSE: Constructor for the CFileViewer class.  Initializes all variables.
//
//   PARAMETERS: 
//    pUnkOuter - LPUNKNOWN of a controlling unknown.
//    hInst - HINSTANCE of the module we're in
//    pfnDestroy - LPFNDESTROYED to call when an object is destroyed.
//
CFileViewer::CFileViewer(LPUNKNOWN pUnkOuter, HINSTANCE hInst, PFNDESTROYED pfnDestroy)
{
    m_cRef=0;
    m_pUnkOuter=pUnkOuter;
    m_hInst=hInst;
    m_pfnDestroy=pfnDestroy;
    m_lpfsi = NULL;

    //MODIFY:  Change this CLSID to your own
    m_clsID=CLSID_FileViewerText;

    m_pszPath=NULL;
    m_grfMode=0L;
    m_fLoadCalled=FALSE;
    m_fShowInit=FALSE;
    m_fPostQuitMsg=TRUE;

    //NULL any contained interfaces initially.
    m_pIPersistFile=NULL;
    m_pIFileViewer=NULL;
    m_pvsi = NULL;

    m_pST=NULL;
    m_pSH=NULL;
    m_fClassReg=FALSE;

    m_hWnd=NULL;
    m_hWndOld = NULL;
    m_hWndToolbar=NULL;
    m_hWndStatus=NULL;
    m_hWndViewport=NULL;

    //MODIFY:  Initalize viewer-specific values
    m_hMemText=NULL;
    m_hFont=NULL;
    m_xPos=0;
    m_yPos=0;
    return;
}

//
//   FUNCTION:  CFileViewer::~CFileViewer
//
//   PURPOSE:   Destructor:deletes all the windows, all allocations, cleans up objects, and
//   frees the filename copied in IPersistFile::Load.
//
CFileViewer::~CFileViewer(void)
{
    //MODIFY:  m_hMemText and m_hFont are viewer-specific.
    if (NULL!=m_hMemText)
        GlobalFree(m_hMemText);

    if (NULL!=m_hFont)
        DeleteObject(m_hFont);

    //MODIFY:  Do any other viewer-specific cleanup
    //Destroying the parent destroys the children as well
    if (NULL!=m_hWnd)
    {
        m_fPostQuitMsg = FALSE;    // Destroy from here implies not from our loop
        DestroyWindow(m_hWnd);
    }

     // Unregistering the classes is important for DLL's because we
     // should not assume that whoever loaded us (the task) is going
     // to quit anytime soon and unregister the class.  Normally
     // QVStub is going to quit, but a test app like TestFV does not
     // which can cause some development headaches.
    if (m_fClassReg)
        {
        UnregisterClass(String(IDS_CLASSFRAME),    m_hInst);
        UnregisterClass(String(IDS_CLASSVIEWPORT), m_hInst);
        }

    if (NULL!=m_pSH)
        delete m_pSH;

    if (NULL!=m_pST)
        delete m_pST;

    //Free the pathname string from IPersistFile::Load if we got one
    MemFree(m_pszPath);

    //Free contained interfaces.
    if (NULL!=m_pIPersistFile)
        delete m_pIPersistFile;

    if (NULL!=m_pIFileViewer)
        delete m_pIFileViewer;
    if (NULL!=m_lpfsi)
        m_lpfsi->Release();

    return;
}

//
//   FUNCTION: CFileViewer::FileShowInit    
//
//   PURPOSE:Provides the implementation of IFileViewer::ShowInitialize that performs 
//   anything subject to failure. This function creates the main window, initializes the toolbar,
//   initializes the status bar controls, sets the initial menu state, creates the viewport window, and
//   loads the accelerators.
//
//   RETURN VALUE:
//
//   HRESULT         NOERROR or an appropriate error code.
//
STDMETHODIMP CFileViewer::FileShowInit(LPFILEVIEWERSITE lpfsi)
{
    HRESULT         hr;
    HMENU           hMenu;

    //MODIFY:  Do pre-show initialization here.
    if (m_lpfsi != lpfsi)
    {
        if (NULL!=m_lpfsi)
            m_lpfsi->Release();

        m_lpfsi = lpfsi;
        lpfsi->AddRef();
    }

    //Default error code
    hr=ResultFromScode(E_OUTOFMEMORY);

    //Create the main window passing "this" to it
    m_hWndOld = m_hWnd;
    m_hWnd=CreateWindow(String(IDS_CLASSFRAME)
        , String(IDS_CAPTION), WS_MINIMIZEBOX | WS_OVERLAPPEDWINDOW
        | WS_CLIPCHILDREN, CW_USEDEFAULT , CW_USEDEFAULT, 350, 450
        , NULL, NULL, m_hInst, (LPVOID)this);

    if (NULL==m_hWnd)
        {
        ODS("CFileViewer::FileShow failed to create main window.");
        return hr;
        }

    // Let us accept files.
    DragAcceptFiles(m_hWnd, TRUE);

    if (!FInitFrameControls())
        {
        ODS("CFileViewer::FileShow failed to create frame tools.");
        return hr;
        }

    //Set initial view menu item checks
    hMenu=GetMenu(m_hWnd);
    CheckMenuItem(hMenu, IDM_VIEWTOOLBAR, MF_BYCOMMAND | MF_CHECKED);
    CheckMenuItem(hMenu, IDM_VIEWSTATUSBAR, MF_BYCOMMAND | MF_CHECKED);

    m_fToolsVisible=TRUE;
    m_fStatusVisible=TRUE;

    m_pSH->MessageDisplay(ID_MSGREADY);

     // ViewportResize puts the viewport window created here
     // in the right location, so we don't have to worry
     // about initial position.
    //BUGBUG:  Not getting proportional thumbs here.

    m_hWndViewport=CreateWindowEx(WS_EX_CLIENTEDGE
        , String(IDS_CLASSVIEWPORT), "Viewport"
        , WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL
        , 0, 0, 100, 100, m_hWnd, (HMENU)ID_VIEWPORT
        , m_hInst, (LPVOID)this);

    if (NULL==m_hWndViewport)
        {
        ODS("CFileViewer::FileShow failed to create viewport.");
        return hr;
        }

    ViewportResize();

     // Go load the file.  This means pulling into memory whatever
     // is necessary for the initial display.
    hr=FileLoad();

    if (FAILED(hr))
        {
        ODS("CFileViewer::FileShow failed to load file.");
        return hr;
        }

    m_hAccel=LoadAccelerators(m_hInst
        , MAKEINTRESOURCE(IDR_ACCELERATORS));

    //Tell IFileViewer::Show it's OK to call it
    m_fShowInit=TRUE;
    return NOERROR;
}

//
//   FUNCTION:      CFileViewer::FileShow
//
//   PURPOSE: Displays the viewing window and enters a message loop.  This function must not fail.  
//
//   PARAMETERS: 
//   pvsi - LPFVSHOWINFO indicates how to initially show the FileViewer window.
//
//   RETURN VALUE:
//    HRESULT  - NOERROR always
//
STDMETHODIMP CFileViewer::FileShow(LPFVSHOWINFO pvsi)
{
    MSG             msg;

    // We need to handle the case where the ShowInitialize may have
    // failed and we set the hwnd to NULL and the hwndOld is not NULL.
    // and the FVSIF_NEWFAILED is set.  In this case set the hwnd Back
    // to the old hwnd...
    if ((pvsi->dwFlags & FVSIF_NEWFAILED) && (m_hWnd == NULL))
    {
        m_hWnd = m_hWndOld;
    }

    if (!IsWindow (m_hWnd))
            return ResultFromScode(E_UNEXPECTED);

    m_pvsi = pvsi;

    // If the new failed flag was passed to us we know that we got here
    // because we tried to view a file and it failed, so simply go back
    // to message loop...
    if ((pvsi->dwFlags & FVSIF_NEWFAILED) == 0)
    {
        if (pvsi->dwFlags & FVSIF_RECT)
            SetWindowPos(m_hWnd, NULL, pvsi->rect.left, pvsi->rect.top,
                    pvsi->rect.right - pvsi->rect.left, pvsi->rect.bottom - pvsi->rect.top,
                    SWP_NOZORDER | SWP_NOACTIVATE);
        ShowWindow(m_hWnd, pvsi->iShow);

        if (SW_HIDE!=pvsi->iShow)
        {
            SetForegroundWindow(m_hWnd);
            UpdateWindow(m_hWnd);
        }

        // If there is an Old window destroy it now
        // It would be nicer to reuse the window!
        if (pvsi->dwFlags & FVSIF_PINNED)
        {
            m_lpfsi->SetPinnedWindow(NULL);
            m_lpfsi->SetPinnedWindow(m_hWnd);

            HMENU hMenu=GetMenu(m_hWnd);
            CheckMenuItem(hMenu, IDM_VIEWREPLACE, MF_BYCOMMAND|MF_CHECKED);
        }

        if (SW_HIDE!=pvsi->iShow)
            UpdateWindow(m_hWnd);

        if ((NULL!=m_hWndOld) && IsWindow(m_hWndOld))
        {
            ODS("CFileViewer::FileShow Destroy Previous hwnd");
            m_fPostQuitMsg = FALSE; // Don't destroy the queue for this one.
            DestroyWindow(m_hWndOld);
            m_hWndOld = NULL;
        }

        if (NULL!=pvsi->punkRel)
        {
            ODSlu("CFileViewer::FileShow Release of previous viewers punkRel(%x)", pvsi->punkRel);
            pvsi->punkRel->Release();
            pvsi->punkRel = NULL;
        }
    }

    while (GetMessage(&msg, NULL, 0,0 ))
        {
        if (!TranslateAccelerator(m_hWnd, m_hAccel, &msg))
            {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            }
        // If there is a new file bail out now.
        if (m_pvsi->dwFlags & FVSIF_NEWFILE)
            break;
        }

    //MODIFY:  Perform cleanup here.
    return NOERROR;
}

//
//   FUNCTION:     CFileViewer::PrintTo
//
//   PURPOSE:  Provides the implementation of IFileViewer::PrintTo that
//  prints the file to a given printer driver, suppressing UI
//  if necessary.  This function currently does nothing.
//
//   PARAMETERS: 
//    pszDriver - LPSTR with the path of the driver to use.  If NULL, use the default driver.
//    fSuppressUI - BOOL indicating if this function is to show any  UI or not.
//
//   RETURN VALUE:
//   HRESULT - NOERROR on success, error code otherwise.
//
STDMETHODIMP CFileViewer::PrintTo(LPSTR pszDriver, BOOL fSuppressUI)
    {
    //Printing not implemented in this sample
    //MODIFY:  Add your printing code here.
    return ResultFromScode(E_NOTIMPL);
}

//
//   FUNCTION:      CFileViewer::FileLoad
//
//   PURPOSE: Loads the file with the path in m_pszPath and places the
//   contents into the m_hWndViewport window.  This function can load
//   a compound file with a "Text" stream or text from a .TXT file.
//
HRESULT CFileViewer::FileLoad(void)
{
    HRESULT     hr;
    HGLOBAL     hMem=NULL;
    LPSTR       psz;
    OLECHAR     szwFile[512];

    //MODIFY: Load your own file type here.
    if (NULL==m_pszPath)
        return ResultFromScode(E_UNEXPECTED);

     // This FileViewer is registered for a .TXT extension that
     // is either in a compound file (single stream called "Text"
     // or in a flat text file.  This sample is meant to show
     // how to open and work with both types of files.
    //Make Unicode copy of filename
    mbstowcs(szwFile, m_pszPath, sizeof(szwFile));

     // CAREFUL:  StgIsStorageFile returns S_FALSE if not--
     //           don't use SUCCEEDED to test the return value!
    if (NOERROR==StgIsStorageFile(szwFile))
        {
        LPSTORAGE   pIStorage=NULL;
        LPSTREAM    pIStream=NULL;
        STATSTG     stat;

        //Case for a compound file, open it and the text stream
        hr=StgOpenStorage(szwFile, NULL, m_grfMode, NULL, 0
            , &pIStorage);

        if (FAILED(hr))
            {
            ODS("CFileViewer::FileLoad failed StgOpenStorage");
            return hr;
            }

        mbstowcs(szwFile, "Text", sizeof(szwFile));

        hr=pIStorage->OpenStream(szwFile, 0, STGM_DIRECT | STGM_READ
            | STGM_SHARE_EXCLUSIVE, 0, &pIStream);

        if (SUCCEEDED(hr))
            {
            //Determine the amount of text and allocate memory
            hr=pIStream->Stat(&stat, STATFLAG_NONAME);

            if (SUCCEEDED(hr))
                {
                hMem=GlobalAlloc(GHND, stat.cbSize.LowPart+1);

                if (NULL!=hMem)
                    {
                     // Now load the text into the controls.
                     // GlobalLock will always work because we
                     // allocated at least 1 byte.
                    psz=(LPSTR)GlobalLock(hMem);
                    hr=pIStream->Read((LPVOID)psz
                        , stat.cbSize.LowPart, NULL);
                    GlobalUnlock(hMem);
                    }
                else
                    {
                    ODS("CFileViewer::FileLoad failed to allocate memory");
                    hr=ResultFromScode(E_OUTOFMEMORY);
                    }
                }

            pIStream->Release();
            }
        else
            {
            ODS("CFileViewer::FileLoad failed StgOpenStorage");
            }

        pIStorage->Release();
        }
    else
        {
        int         hFile=NULL;
        OFSTRUCT    of;
        DWORD       cb, cbRead;

         // Case for straight text file, open and read.  In opening
         // the file, mask off the upper word or m_grfMode which
         // contains the compound file specific flags.  The lower
         // word has OpenFile flags (consistent between
         // StgOpenStorage and OpenFile).
        hFile=OpenFile(m_pszPath, &of
            , (UINT)(m_grfMode & 0x0000FFFF));

        if (HFILE_ERROR==hFile)
            {
            ODS("CFileViewer::FileLoad failed OpenFile");
            return ResultFromScode(STG_E_FILENOTFOUND);
            }

        //Scan to end and then back to determine file size.
        cb=_llseek(hFile, 0L, 2);
        _llseek(hFile, 0L, 0);

        hMem=GlobalAlloc(GHND, cb+1);

        if (NULL!=hMem)
            {
             // Now load the text into the controls.  GlobalLock will
             // always work because we allocated at least 1 byte
            psz=(LPSTR)GlobalLock(hMem);
            cbRead=_lread(hFile, psz, (UINT)cb);
            GlobalUnlock(hMem);

            hr=ResultFromScode((cb==cbRead) ? S_OK : STG_E_READFAULT);
            }
        else
            {
            ODS("CFileViewer::FileLoad failed to allocate memory");
            hr=ResultFromScode(E_OUTOFMEMORY);
            }

        _lclose(hFile);
        }

    //Set edit control to read-only:  no modifications allowed!
    if (SUCCEEDED(hr) && NULL!=hMem)
        {
        if (NULL!=m_hMemText)
            GlobalFree(m_hMemText);

        //Make the text current and repaint.
        m_hMemText=hMem;
        InvalidateRect(m_hWndViewport, NULL, TRUE);
        UpdateWindow(m_hWndViewport);
        }

    return hr;
}

//
//   FUNCTION:     CFileViewer::OnCommand
//
//   PURPOSE: WM_COMMAND message handler for a FileViewer window.  
//
//   PARAMETERS: 
//       wID             WORD ID of the command.
//  wCode           WORD notification code with the command
//  hWndCtl         HWND sending the message (if a control)
//
void CFileViewer::OnCommand(WORD wID, WORD wCode, HWND hWndCtl)
{
    //MODIFY:  Do your command processing here.
    switch (wID)
        {
        case IDM_FILEOPENAS:
            if (FOpenAs())
                PostMessage(m_hWnd, WM_CLOSE, 0, 0L);
            break;

        case IDM_FILEPAGESETUP:
            //Not implemented in this sample
            break;

        case IDM_FILEPRINT:
            //Not implemented in this sample
            break;

        case IDM_FILEEXIT:
            PostMessage(m_hWnd, WM_CLOSE, 0, 0L);
            break;

        case IDM_VIEWTOOLBAR:
            m_fToolsVisible=!m_fToolsVisible;

            CheckMenuItem(GetMenu(m_hWnd), IDM_VIEWTOOLBAR
                , MF_BYCOMMAND | (m_fToolsVisible
                ? MF_CHECKED : MF_UNCHECKED));

            ShowWindow(m_hWndToolbar, m_fToolsVisible
                ? SW_SHOW : SW_HIDE);

            //Resize the viewport window
            ViewportResize();
            break;

        case IDM_VIEWSTATUSBAR:
            m_fStatusVisible=!m_fStatusVisible;

            CheckMenuItem(GetMenu(m_hWnd), IDM_VIEWSTATUSBAR
                , MF_BYCOMMAND | (m_fStatusVisible
                ? MF_CHECKED : MF_UNCHECKED));

            ShowWindow(m_hWndStatus, m_fStatusVisible
                ? SW_SHOW : SW_HIDE);

            //Resize the viewport window
            ViewportResize();
            break;
        case IDM_VIEWREPLACE:
            // Switch the Replace mode
            ReplaceWindowModeChange();
            break;
        case IDM_VIEWFONT:
            FontChange(VIEWFONT_SELECT);
            break;

        case IDM_VIEWFONTINCREASE:
            FontChange(VIEWFONT_INCREASESIZE);
            break;

        case IDM_VIEWFONTDECREASE:
            FontChange(VIEWFONT_DECREASESIZE);
            break;

        case IDM_HELPCONTENTS:
            MessageBox(m_hWnd, String(IDS_NOHELP)
                , String(IDS_CAPTION), MB_OK);
            break;

        case IDM_HELPABOUT:
            DialogBox(m_hInst, MAKEINTRESOURCE(IDD_ABOUT), m_hWnd
                , (DLGPROC)AboutProc);
            break;
        }

    return;
}

//
//   FUNCTION:  CFileViewer::ChildrenResize    
//
//   PURPOSE:    Handles the situation when the FileViewer frame window was
//   resized. The toolbar, status bar and viewport are resized via a call to the 
//   the ViewportResize function.
//
//   COMMENTS:
//   Note that the toolbar and status bar are resized even when
//   they are not visible so we can just reshow them again when
//   necessary.
//
void CFileViewer::ChildrenResize(void)
{
    RECT        rc;

    GetClientRect(m_hWnd, &rc);

    //We resize toolbar and status bar regardless of visibility
    SetWindowPos(m_hWndToolbar, NULL, 0, 0
        , rc.right-rc.left, m_cyTools
        , SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);

    SetWindowPos(m_hWndStatus, NULL, 0, rc.bottom-m_cyStatus
        , rc.right-rc.left, m_cyStatus
        , SWP_NOZORDER | SWP_NOACTIVATE);

    ViewportResize();
    return;
}

//
//   FUNCTION: CFileViewer::ViewportResize    
//
//   PURPOSE: Updates the size and position of the viewport window
//   depending on visibility of the toolbar and status bar.  
//
void CFileViewer::ViewportResize(void)
{
    RECT        rc;
    UINT        dy1, dy2;

    GetClientRect(m_hWnd, &rc);

    dy1=m_fToolsVisible  ? m_cyTools  : 0;
    dy2=m_fStatusVisible ? m_cyStatus : 0;

    //We resize toolbar and status bar regardless of visibility
    SetWindowPos(m_hWndViewport, NULL, 0, dy1
        , rc.right-rc.left, rc.bottom-rc.top-dy1-dy2
        , SWP_NOZORDER | SWP_NOACTIVATE);

    ViewportScrollSet();
    return;
}

//
//   FUNCTION:     CFileViewer::ViewportScrollSet
//
//   PURPOSE:  Updates the scrollbar ranges in the viewport depending on
//   the current font in use and the size of the window.  
//
void CFileViewer::ViewportScrollSet(void)
{
    RECT        rc, rcFmt;
    LPSTR       psz;
    HDC         hDC;
    HFONT       hFont;
    SCROLLINFO  si;

    if (NULL==m_hMemText)
        return;

    psz=(LPSTR)GlobalLock(m_hMemText);
    hDC=GetDC(m_hWndViewport);
    hFont=(HFONT)SelectObject(hDC, m_hFont);

     // Set initially large formatting rectangle, and let
     // DrawText walk all over it.
    SetRect(&rcFmt, 0, 0, 32767, 32767);
    DrawText(hDC, psz, -1, &rcFmt, DT_LEFT | DT_CALCRECT
        | DT_EXPANDTABS);

    SelectObject(hDC, hFont);
    ReleaseDC(m_hWndViewport, hDC);

    GetClientRect(m_hWndViewport, &rc);

    //Scroll ranges are draw rect minus visible rect, +1 for buffer
    // First set the horizontal scrollbars information...
    si.cbSize = sizeof(si);
    si.fMask = SIF_RANGE | SIF_POS | SIF_PAGE;
    si.nMin = 0;
    si.nMax = (rcFmt.right-rcFmt.left)+1;
    si.nPage = rc.right;
    si.nPos = 0;
    SetScrollInfo(m_hWndViewport, SB_HORZ, &si, TRUE);
    m_xPos=0;

    // Now Set the vertical scrollbar
    si.nMax = (rcFmt.bottom-rcFmt.top)+1;
    si.nPage = rc.bottom;
    SetScrollInfo(m_hWndViewport, SB_VERT, &si, TRUE);
    m_yPos=0;

    GlobalUnlock(m_hMemText);
    return;
}

//
//   FUNCTION: CFileViewer::FOpenAs    
//
//   PURPOSE:  Attempts to launch an application to open the file for editing.  
//
//   RETURN VALUE:
//   BOOL -  TRUE if the application is opened in which case
//                  the FileViewer can shut down.  Otherwise FALSE
//                  meaning launching failed.
//
BOOL CFileViewer::FOpenAs(void)
{
    SHELLEXECUTEINFO sei = {sizeof(sei), 0, m_hWnd, "open",
            m_pszPath, NULL, NULL, SW_SHOWNORMAL, m_hInst};

    return ShellExecuteEx(&sei);
}

//
//   FUNCTION:     CFileViewer::FontChange
//
//   PURPOSE:  Either allows the user to choose a font or increments or
//  decrements the font size depending on uOpt.  This is all
//  handled in one function here because each operation
//  involves obtaining the current viewport font, messing with
//  it in some way, and setting a new font again.
//
//   PARAMETERS: 
//     uOpt          VIEWFONTOPTION of the way to change the font:
//                      VIEWFONT_SELECT     Display dialog
//                      VIEWFONT_INCREASE   Increase size by 2pt
//                      VIEWFONT_DECREASE   Decreate size by 2pt
//
void CFileViewer::FontChange(VIEWFONTOPTION uOpt)
{
    HFONT       hFont;
    LOGFONT     lf;
    CHOOSEFONT  cf;
    BOOL        fChange=TRUE;
    int         z;

     // We have a system font from the constructor, so m_hFont
     // will never be NULL, but assert it anyway.
    D(if (NULL==m_hFont) ODS("Assertion Failed:  m_hFont is NULL"););

    GetObject(m_hFont, sizeof(lf), &lf);
     // Each option is responsible for manipulating
     // the LOGFONT structure in some way.  If there
     // is nothing to do, they set fChange to FALSE
    switch (uOpt)
        {
        case VIEWFONT_SELECT:
            memset(&cf, 0, sizeof(CHOOSECOLOR));
            cf.lStructSize=sizeof(CHOOSECOLOR);
            cf.hwndOwner  =m_hWnd;
            cf.lpLogFont  =&lf;
            cf.nSizeMin   =FONTSIZETHRESHOLDMIN;
            cf.nSizeMax   =FONTSIZETHRESHOLDMAX;

            cf.Flags=CF_SCREENFONTS | CF_INITTOLOGFONTSTRUCT
                | CF_FORCEFONTEXIST;

            if (!ChooseFont(&cf))
                {
                D(DWORD dwErr=CommDlgExtendedError();
                ODSlu("FVTEXT.DLL:  ChooseFont failed with %lu", dwErr););

                fChange=FALSE;
                }

            break;


        case VIEWFONT_INCREASESIZE:
            //Convert logical size to point size.
            z=MulDiv(-lf.lfHeight, 72, m_cyPPI);

            //Vary the size increase depending on point size.
            if (z < FONTSIZETHRESHOLDMAX)
                {
                if (z < FONTSIZETHRESHOLDLOW)
                    z+=FONTSIZEDELTASMALL;
                else
                    {
                    if (z < FONTSIZETHRESHOLDMID)
                        z+=FONTSIZEDELTAMEDIUM;
                    else
                        z+=FONTSIZEDELTALARGE;
                    }

                //Convert point size to logical size.
                lf.lfHeight=MulDiv(-z, m_cyPPI, 72);
                }
            else
                fChange=FALSE;

            break;

        case VIEWFONT_DECREASESIZE:
            //Convert logical size to point size.
            z=MulDiv(-lf.lfHeight, 72, m_cyPPI);

            //Vary the size decrease depending on point size.
            if (z > FONTSIZETHRESHOLDMIN)
                {
                if (z > FONTSIZETHRESHOLDMID)
                    z-=FONTSIZEDELTALARGE;
                else
                    {
                    if (z > FONTSIZETHRESHOLDLOW)
                        z-=FONTSIZEDELTAMEDIUM;
                    else
                        z-=FONTSIZEDELTASMALL;
                    }

                //Convert point size to logical size.
                lf.lfHeight=MulDiv(-z, m_cyPPI, 72);
                }
            else
                fChange=FALSE;

            break;

        default:
            fChange=FALSE;
        }

    //Return now if we didn't change anything.
    if (!fChange)
        return;

    //Now switch fonts and update the viewport.
    hFont=CreateFontIndirect(&lf);

    if (NULL!=hFont)
        {
        if (NULL!=m_hFont)
            DeleteObject(m_hFont);

        m_hFont=hFont;

        ViewportScrollSet();

        //Repaint the viewport
        InvalidateRect(m_hWndViewport, NULL, TRUE);
        UpdateWindow(m_hWndViewport);
        }

    return;
}

//
//   FUNCTION:     CFileViewer::ReplaceWindowModeChange
//
//   PURPOSE: Sets the window to be pinned or not to be pinned.  When the
//   window is pinned, the caller of the viewers will attempt
//   to replace the contents of the window instead of creating
//   new windows.  
//
void CFileViewer::ReplaceWindowModeChange(void)
{
    HWND hwnd;
    UINT  uCheck = MF_BYCOMMAND;

    if (m_lpfsi)
    {
        m_lpfsi->GetPinnedWindow(&hwnd);
        if ((HWND)NULL==hwnd)
        {
            m_lpfsi->SetPinnedWindow(m_hWnd);
            uCheck = MF_BYCOMMAND | MF_CHECKED;
        }
        else
        {
            if (hwnd==m_hWnd)
                m_lpfsi->SetPinnedWindow(NULL);
        }

    }

    HMENU hMenu=GetMenu(m_hWnd);
    CheckMenuItem(hMenu, IDM_VIEWREPLACE, uCheck);
}

//
//   FUNCTION: CFileViewer::DropFiles    
//
//   PURPOSE:   Processes a drop 
//
BOOL    CFileViewer::DropFiles (HDROP hdrop)
{
    // We should now proces the files that were dropped on us
    char    szPath[MAX_PATH];
    int     cb;

    // For now only process the first file.
    if (DragQueryFile(hdrop, 0, szPath, sizeof(szPath)) > 0)
    {
        ODSsz("CFileViewer::DropFiles filename=%s", szPath);

        // Need to convert the string to ole string...
        cb = (lstrlen(szPath)+1) * sizeof(OLECHAR);
        mbstowcs(m_pvsi->strNewFile, szPath, cb);

        // Now get the window rectangle to use to display this in...
        GetWindowRect(m_hWnd, &m_pvsi->rect);
        m_pvsi->dwFlags |= (FVSIF_RECT | FVSIF_NEWFILE);

        // Should check for failure but now sure what to do with it anyway
        QueryInterface(IID_IUnknown, (LPVOID *)&m_pvsi->punkRel);
        ODSlu("CFileViewer::DropFiles Query Interface(%x)", m_pvsi->punkRel);
    }

    DragFinish(hdrop);
    return TRUE;
}

//
//   FUNCTION: CFileViewer::PszToolTip    
//
//   PURPOSE: Returns a string pointer to a tool tip for the given command
//   ID value.  When asked for a string we also display a similar
//   one in the status bar.  
//
//   PARAMETERS: 
//   uID - UINT of the toolbar button command.
//
//   RETURN VALUE:
//   LPSTR - Pointer to the string to display.
//
LPSTR CFileViewer::PszToolTip(UINT uID)
{
    UINT        iString, iStatusMsg;

    switch (uID)
        {
        case IDM_FILEOPENAS:
            iString=IDS_TOOLTIPOPENAS;
            iStatusMsg=IDM_FILEOPENAS;
            break;

        case IDM_VIEWFONTINCREASE:
            iString=IDS_TOOLTIPFONTINC;
            iStatusMsg=ID_TIPFONTINC;
            break;

        case IDM_VIEWFONTDECREASE:
            iString=IDS_TOOLTIPFONTDEC;
            iStatusMsg=ID_TIPFONTDEC;
            break;

        default:
            return NULL;
        }

    m_pSH->MessageDisplay(iStatusMsg);
    return String(iString);
}
