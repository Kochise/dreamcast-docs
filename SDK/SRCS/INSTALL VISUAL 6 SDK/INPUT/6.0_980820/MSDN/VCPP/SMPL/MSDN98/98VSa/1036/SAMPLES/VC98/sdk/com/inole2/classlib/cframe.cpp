/*
 * CFRAME.CPP
 * Sample Code Class Libraries
 *
 * Generic CFrame class that manages either SDI or MDI clients as
 * well as typical File, Edit, Window, and Help commands.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include <windows.h>
#include <memory.h>

extern "C"
    {
    #include <commdlg.h>
    }

#include "classlib.h"



/*
 * CFrame::CFrame
 * CFrame::~CFrame
 *
 * Constructor Parameters:
 *  hInst           HINSTANCE from WinMain
 *  hInstPrev       HINSTANCE from WinMain
 *  pszCmdLine      LPSTR from WinMain
 *  nCmdShow        int from WinMain
 */

CFrame::CFrame(HINSTANCE hInst, HINSTANCE hInstPrev
    , LPSTR pszCmdLine, int nCmdShow)
    : CWindow(hInst)
    {
    m_hInstPrev =hInstPrev;
    m_nCmdShow  =nCmdShow;

   #ifdef WIN32
    //This gives us the Unicode version if necessary
    m_pszCmdLine=GetCommandLine();
   #else
    m_pszCmdLine=pszCmdLine;
   #endif

    m_ppszCmdArgs=NULL;
    m_cCmdArgs=0;
    m_fCmdsParsed=FALSE;

    m_fLastEnable=(BOOL)-1; //Uninitialized
    m_fLastPaste =(BOOL)-1; //Uninitialized

    m_phMenu=NULL;
    m_hBmp  =NULL;
    m_pST   =NULL;

    m_pTB   =NULL;
    m_pSL   =NULL;
    m_pCL   =NULL;
    return;
    }



CFrame::~CFrame(void)
    {
    m_fClosing=TRUE;

    //Accelerators freed automatically.

    //Free the toolbar bitmaps
    if (NULL!=m_hBmp)
        DeleteObject(m_hBmp);

    if (NULL!=m_pCL)
        delete m_pCL;

    if (NULL!=m_pSL)
        delete m_pSL;

    if (NULL!=m_pTB)
        delete m_pTB;

    //Free the menu handle array
    if (NULL!=m_phMenu)
        delete []((UINT *)m_phMenu);

    //Free the stringtable.
    if (NULL!=m_pST)
        delete m_pST;

    //Free the command-line argument pointer array
    if (NULL!=m_ppszCmdArgs)
        delete []m_ppszCmdArgs;

    m_fClosing=FALSE;
    return;
    }


/*
 * CFrame::ParseCommandLine
 *
 * Purpose:
 *  Before other initialization, parse the command line arguments
 *  since derived classes may need the arguments before calling
 *  Init below.
 *
 * Return Value:
 *  BOOL            TRUE if parsing succeeded, FALSE otherwise.
 */

BOOL CFrame::ParseCommandLine(void)
    {
    LPTSTR     *ppsz=NULL;
    LPTSTR      psz, pszT;
    int         cArgs=0;

    if (m_fCmdsParsed)
        return TRUE;

    psz=PszWhiteSpaceScan(m_pszCmdLine, TRUE);

   #ifdef WIN32
    //Skip the first argument which is the EXE name in Win32
    psz=PszWhiteSpaceScan(psz, FALSE);
    psz=PszWhiteSpaceScan(psz, TRUE);
   #endif

    for (pszT=psz; *pszT!=0; )
        {
        cArgs++;

        //Skip to the end of this argument
        pszT=PszWhiteSpaceScan(pszT, FALSE);

        //Stop if we hit the end of the string
        if ((TCHAR)0==*pszT)
            break;

        //Skip whitespace to the next argument
        pszT=PszWhiteSpaceScan(pszT, TRUE);
        }

    /*
     * Now allocate a pointer array to each argument in the
     * command line and null terminate each argument.
     */
    if (0!=cArgs)
        {
        int i;

        ppsz=new LPTSTR[cArgs];

        if (NULL==ppsz)
            return FALSE;

        for (i=0; i < cArgs; i++)
            {
            ppsz[i]=psz;

            psz=PszWhiteSpaceScan(psz, FALSE);

            if ((TCHAR)0!=*psz)
                pszT=psz;

            psz=PszWhiteSpaceScan(psz, TRUE);
            *pszT=(TCHAR)0;
            }
        }

    m_ppszCmdArgs=ppsz;
    m_cCmdArgs=cArgs;
    m_fCmdsParsed=TRUE;
    return TRUE;
    }





/*
 * CFrame::Init
 *
 * Purpose:
 *  Initializer for a CFrame object containing anything prone to
 *  failure.
 *
 * Parameters:
 *  pFI             PFRAMEINIT containing initialization parameters.
 *
 * Return Value:
 *  BOOL            TRUE if initialization succeeded, FALSE
 *                  otherwise. If FALSE is returned, the caller must
 *                  guarantee that the destructor is called promptly
 *                  to insure cleanup.
 */

BOOL CFrame::Init(PFRAMEINIT pFI)
    {
    RECT                rc;
    HMENU               hMenu;
    UINT                uTemp;
    TOOLDISPLAYDATA     tdd;

    m_fInit=TRUE;

    //1.  Create our stringtable
    m_pST=new CStringTable(m_hInst);

    if (!m_pST->Init(pFI->idsMin, pFI->idsMax))
        return FALSE;


    /*
     * 2.  Register the classes we need for this application.
     *     We have our main (frame) window, document windows (for
     *     either MDI or SDI, and Polyline windows which are the
     *     editing controls.  This separate virtual function allows
     *     applications to add additional classes.
     */
    if (NULL==m_hInstPrev)
        {
        if (!RegisterAllClasses())
            return FALSE;
        }


    /*
     * 3.  Create the main window, the toolbar, and the status line.
     */
    m_pCL=NULL;

    m_hWnd=CreateWindow(SZCLASSFRAME, PSZ(IDS_CAPTION)
        , WS_MINIMIZEBOX | WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN
        , pFI->x, pFI->y, pFI->cx, pFI->cy
        , NULL, NULL, m_hInst, this);

    if (NULL==m_hWnd)
        return FALSE;

    GetClientRect(m_hWnd, &rc);

    UIToolConfigureForDisplay(&tdd);
    m_dxB=tdd.cxButton;
    m_dyB=tdd.cyButton;
    m_cyBar=tdd.cyBar;

    m_pTB=new CToolBar(m_hInst);

    if (!m_pTB->Init(m_hWnd, ID_GIZMOBAR, m_cyBar))
        return FALSE;

    m_pSL=new CStatusLine(m_hInst);

    if (!m_pSL->Init(m_hWnd, ID_STATSTRIP, CYSTATSTRIP))
        return FALSE;


    //Initialize the status line for automated WM_MENUSELECT processing
    if (!m_pSL->MessageMap(m_hWnd, m_hInst, IDR_STATMESSAGEMAP
        , pFI->idsStatMin, pFI->idsStatMax, CCHMESSAGEMAX
        , pFI->idStatMenuMin, pFI->idStatMenuMax, ID_MESSAGEREADY
        , ID_MESSAGEEMPTY, ID_MENUSYS))
        return FALSE;

    rc.top+=m_cyBar;

    /*
     * 4.  Create the client window that owns documents.  This
     *     client also creates an advise sink and gives it to
     *     each document to notify the frame of events.
     *
     *     Also allocate space for the menu handle array and store
     *     the popup handles.  Get the menu handle of the Window
     *     menu specifically for later processing.
     */

    m_pCL=CreateCClient();
    hMenu=GetMenu(m_hWnd);

   #ifdef MDI
    //Save this for UpdateMenus.  Stays NULL in SDI
    m_hMenuWindow=GetSubMenu(hMenu, pFI->iPosWindowMenu);
   #endif

    if (!m_pCL->Init(m_hMenuWindow, &rc))
        return FALSE;

    m_phMenu=new HMENU[pFI->cMenus];

    for (uTemp=0; uTemp < pFI->cMenus; uTemp++)
        m_phMenu[uTemp]=GetSubMenu(hMenu, uTemp);


    /*
     * 5.  Initialize fancy things like the toolbar.  If a derived
     *     class wants more tool images, they can copy the first
     *     two in the standard image set and this code will still
     *     load it.  This code just won't reference it.
     */

    m_hBmp=LoadBitmap(m_hInst, MAKEINTRESOURCE(tdd.uIDImages));

    if (NULL==m_hBmp)
        return FALSE;

    //Create all the tools, and uninitialize working flags
    CreateToolbar();
    UpdateToolbar();
    m_fLastEnable=(BOOL)-1; //Uninitialized
    m_fLastPaste =(BOOL)-1; //Uninitialized

    m_hAccel=LoadAccelerators(m_hInst
        , MAKEINTRESOURCE(IDR_ACCELERATORS));

    if (NULL==m_hAccel)
        return FALSE;

    /*
     * 6.  In the default implementation PreShowInit does not do
     *     anything, but is called here to allow derivations to
     *     hook the function and modify m_nCmdShow before we
     *     call ShowWindow.  This is one such place where OLE affects
     *     a derivation, because servers will change m_nCmdShow to
     *     SW_HIDE if started with -Embedding.
     */
    if (!PreShowInit())
        return FALSE;


    /*
     * 7.  Handle window visibility appropriately after giving
     *     PreShowInit a chance to modify it.
     */
    ShowWindow(m_hWnd, m_nCmdShow);
    UpdateWindow(m_hWnd);


    /*
     * 8.  Parse the command line and take appropriate action.  The
     *     derived class may have called ParseCommandLine earlier, so
     *     m_fCmdsParsed tells us if we still need to call it.
     */
    if (!m_fCmdsParsed)
        ParseCommandLine();

    OpenInitialFiles();

    m_fInit=FALSE;
    return TRUE;
    }





/*
 * CFrame::CreateCClient
 *
 * Purpose:
 *  Creates a CClient object for use in this frame.  This function
 *  is overrided by derived classes to create a different type of
 *  CClient.
 *
 * Return Value:
 *  PCClient         Pointer to the new CClient object.
 */

PCClient CFrame::CreateCClient(void)
    {
    return new CClient(m_hInst, this);
    }







/*
 * CFrame::RegisterAllClasses
 *
 * Purpose:
 *  Registers all classes used in this application.
 *
 * Return Value:
 *  BOOL            TRUE if registration succeeded, FALSE otherwise.
 */

BOOL CFrame::RegisterAllClasses(void)
    {
    WNDCLASS        wc;

    //Field that are the same for all windows.
    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.hInstance     = m_hInst;
    wc.cbClsExtra    = 0;

    //Register the Frame window
    wc.lpfnWndProc   = FrameWndProc;
    wc.cbWndExtra    = CBFRAMEWNDEXTRA;
    wc.hIcon         = LoadIcon(m_hInst, TEXT("Icon"));
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE+1);
    wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MENU);
    wc.lpszClassName = SZCLASSFRAME;

    if (!RegisterClass(&wc))
        return FALSE;

   #ifndef MDI
    wc.lpfnWndProc   = SDIClientWndProc;
    wc.cbWndExtra    = CBCLIENTWNDEXTRA;
    wc.hIcon         = NULL;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = SZCLASSSDICLIENT;

    if (!RegisterClass(&wc))
        return FALSE;
   #endif

    wc.lpfnWndProc   = DocumentWndProc;
    wc.cbWndExtra    = CBDOCUMENTWNDEXTRA;
    wc.hIcon         = LoadIcon(m_hInst
                           , MAKEINTRESOURCE(IDR_DOCUMENTICON));
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = SZCLASSDOCUMENT;

    if (!RegisterClass(&wc))
        return FALSE;

    return TRUE;
    }





/*
 * CFrame::PreShowInit
 *
 * Purpose:
 *  Called from Init before intially showing the window.  We do
 *  whatever else we want here, modifying nCmdShow as necessary
 *  which affects ShowWindow in Init.
 *
 * Return Value:
 *  BOOL            TRUE if this initialization succeeded, FALSE
 *                  otherwise.
 */

BOOL CFrame::PreShowInit(void)
    {
    return TRUE;
    }







/*
 * CFrame::OpenInitialFiles
 *
 * Purpose:
 *  Opens any files that were present on the command line.
 */

void CFrame::OpenInitialFiles(void)
    {
    UINT        i;
    PCDocument  pDoc;

    //Create a new document if we have nothing specific to open
    if (0==m_cCmdArgs)
        {
        pDoc=m_pCL->NewDocument(TRUE);

        if (NULL!=pDoc)
            pDoc->Load(TRUE, NULL);

        UpdateToolbar();
        return;
        }

    //Iterate over the arguments and see if there's any filenames
    for (i=0; i < m_cCmdArgs; i++)
        {
        LPTSTR      psz=m_ppszCmdArgs[i];

        if (NULL==psz)
            break;

        //Skip switches prefixed with / and -
        if ((TCHAR)0!=*psz && TEXT('/')!=*psz && TEXT('-')!=*psz)
            {
            pDoc=m_pCL->NewDocument(TRUE);

            if (NULL!=pDoc)
                pDoc->Load(TRUE, psz);
            }

        UpdateToolbar();
        }

    return;
    }




/*
 * CFrame::CreateToolbar
 *
 * Purpose:
 *  Procedure to create all the necessary toolbar buttons.
 *
 * Return Value:
 *  UINT            Number of tools added to the bar.
 */

UINT CFrame::CreateToolbar(void)
    {
    UINT            uState=GIZMO_NORMAL;
    UINT            utCmd =GIZMOTYPE_BUTTONCOMMAND;
    UINT            utEx  =GIZMOTYPE_BUTTONATTRIBUTEEX;

    //File New, Open, Close, Save, Import
    m_pTB->Add(utCmd, 0, IDM_FILENEW,   m_dxB, m_dyB, NULL, NULL
        , 3, uState);
    m_pTB->Add(utCmd, 1, IDM_FILEOPEN,  m_dxB, m_dyB, NULL, NULL
        , 4, uState);
    m_pTB->Add(utCmd, 2, IDM_FILECLOSE, m_dxB, m_dyB, NULL, m_hBmp
        , 0, uState);
    m_pTB->Add(utCmd, 3, IDM_FILESAVE,  m_dxB, m_dyB, NULL, NULL
        , 5, uState);

    //Separator
    m_pTB->Add(GIZMOTYPE_SEPARATOR,   4, 0, 6, m_dyB, NULL, NULL
        , 0, uState);

    //Edit Undo, Cut, Copy, Paste
    m_pTB->Add(utCmd, 5, IDM_EDITUNDO,  m_dxB, m_dyB, NULL, m_hBmp
        , 1, uState);
    m_pTB->Add(utCmd, 6, IDM_EDITCUT,   m_dxB, m_dyB, NULL, NULL
        , 0, uState);
    m_pTB->Add(utCmd, 7, IDM_EDITCOPY,  m_dxB, m_dyB, NULL, NULL
        , 1, uState);
    m_pTB->Add(utCmd, 8, IDM_EDITPASTE, m_dxB, m_dyB, NULL, NULL
        , 2, uState);

    return 9;
    }



/*
 * CFrame::MessageLoop
 *
 * Purpose:
 *  Spins in a standard message loop (with accelerators) until
 *  WM_QUIT is found after which it returns.
 *
 * Return Value:
 *  WPARAM          Contents of msg.wParam from WM_QUIT.
 */

WPARAM CFrame::MessageLoop(void)
    {
    MSG     msg;

    while (GetMessage(&msg, NULL, 0,0 ))
        {
        if (!m_pCL->TranslateAccelerator(&msg))
            {
            if (!TranslateAccelerator(m_hWnd, m_hAccel, &msg))
                {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
                }
            }
        }

    return msg.wParam;
    }






/*
 * CFrame::FMessageHook
 *
 * Purpose:
 *  Provides a derivation of the base CFrame class to hook all
 *  messages to the window procedure for special processing.
 *  WM_COMMAND is NOT sent here as that goes through OnCommand
 *  instead.
 *
 * Parameters:
 *  <WndProc Parameters>
 *  pLRes           LRESULT * in which to store the return value
 *                  for the message.
 *
 * Return Value:
 *  BOOL            TRUE to prevent further processing, FALSE
 *                  otherwise.
 */

BOOL CFrame::FMessageHook(HWND hWnd, UINT iMsg, WPARAM wParam
    , LPARAM lParam, LRESULT *pLRes)
    {
    *pLRes=0;
    return FALSE;
    }






/*
 * CFrame::OnCommand
 *
 * Purpose:
 *  WM_COMMAND handler for the frame window so derivations can
 *  process their messages and then pass the standard commands (like
 *  file open and save) on to the base class.
 *
 * Parameters:
 *  hWnd            HWND of the frame window.
 *  wParam          WPARAM of the message.
 *  lParam          LPARAM of the message.
 *
 * Return Value:
 *  LRESULT         Return value for the message.
 */

LRESULT CFrame::OnCommand(HWND hWnd, WPARAM wParam, LPARAM lParam)
    {
    PCDocument      pDoc;
    TCHAR           szFile[CCHPATHMAX];
    BOOL            fOK;
    UINT            uTemp;
    UINT            uType;
    PCHourglass     pHour;

    COMMANDPARAMS(wID, wCode, hWndMsg);

    /*
     * Don't bother with anything during first initialization,
     * skipping many toolbar notifications.
     */
    if (m_fInit)
        return 0L;

    pDoc=m_pCL->ActiveDocument();


    switch (wID)
        {
        case IDM_FILENEW:
            if (!m_pCL->SDIVerify())
                break;

            pHour=new CHourglass;
            pDoc=m_pCL->NewDocument(TRUE);

            //Insure the document is untitled.
            if (NULL!=pDoc)
                pDoc->Load(TRUE, NULL);

            delete pHour;
            break;


        case IDM_FILEOPEN:
            if (!m_pCL->SDIVerify())
                break;

            szFile[0]=0;
            fOK=SaveOpenDialog(szFile, CCHPATHMAX, IDS_FILEOPEN
                , TRUE, &uType);

            if (!fOK)
                return 0L;

            pDoc=m_pCL->NewDocument(FALSE);

            if (NULL==pDoc)
                return 0L;

            pHour=new CHourglass;
            uTemp=pDoc->Load(TRUE, szFile);
            delete pHour;

            pDoc->ErrorMessage(uTemp);

            //Close the new doc on failure, show on success.
            if (DOCERR_NONE!=uTemp)
                m_pCL->CloseDocument(pDoc);
            else
                m_pCL->ShowDocument(pDoc, TRUE);

            return (DOCERR_NONE==uTemp);


        case IDM_FILECLOSE:
            //Ask if you want to save.
            if (!m_pCL->FCleanVerify(pDoc))
                return 0L;

            m_pCL->CloseDocument(pDoc);
            UpdateToolbar();
            break;


        case IDM_FILESAVE:
            //If we get this from the toolbar, we may need Save As
            fOK=pDoc->FQuerySave();

            if (fOK)
                {
                //Save using current document name and version
                pHour=new CHourglass;
                uTemp=pDoc->Save(0, NULL);
                delete pHour;

                pDoc->ErrorMessage(uTemp);
                return (DOCERR_NONE==uTemp);
                }

            //FALL through to File/Save As for no name documents.


        case IDM_FILESAVEAS:
            //Go get a filename, then save it.
            pDoc->FilenameGet(szFile, CCHPATHMAX);

            fOK=SaveOpenDialog(szFile, CCHPATHMAX, IDS_FILESAVEAS
                , FALSE, &uType);

            if (!fOK)
                return 0L;

            pHour=new CHourglass;
            uTemp=pDoc->Save(uType, szFile);
            delete pHour;
            pDoc->ErrorMessage(uTemp);
            return (DOCERR_NONE==uTemp);


        case IDM_FILEEXIT:
            PostMessage(hWnd, WM_CLOSE, 0, 0L);
            break;


        case IDM_EDITCUT:
        case IDM_EDITCOPY:
            pHour=new CHourglass;
            pDoc->Clip(hWnd, (IDM_EDITCUT==wID));
            delete pHour;

            //Update the toolbar as appropriate.
            m_pTB->Enable(IDM_EDITPASTE, pDoc->FQueryPaste());
            break;


        case IDM_EDITUNDO:
            pDoc->Undo();
            break;

        case IDM_EDITPASTE:
            pHour=new CHourglass;
            pDoc->Paste(hWnd);
            delete pHour;
            break;


        //These commands don't happen in SDI builds; not on the menu
        case IDM_WINDOWCASCADE:
            m_pCL->OnWindowCommand(WM_MDICASCADE, 0);
            break;

        case IDM_WINDOWTILEHORZ:
            m_pCL->OnWindowCommand(WM_MDITILE, MDITILE_HORIZONTAL);
            break;

        case IDM_WINDOWTILEVERT:
            m_pCL->OnWindowCommand(WM_MDITILE, MDITILE_VERTICAL);
            break;

        case IDM_WINDOWICONS:
            m_pCL->OnWindowCommand(WM_MDIICONARRANGE, 0);
            break;

        case IDM_HELPABOUT:
            DialogBox(m_hInst, MAKEINTRESOURCE(IDD_ABOUT)
                , m_hWnd, (DLGPROC)AboutProc);
            break;

        default:
           return m_pCL->DefaultFrameProc(hWnd, WM_COMMAND, wParam
               , lParam);
        }

    return 0L;
    }





/*
 * CFrame::OnDocumentDataChange
 *
 * Purpose:
 *  Most of the CDocumentAdviseSink notifications we get are fairly
 *  standard implementations.  When data in the document changes,
 *  however, there's probably more special things we can do, so we
 *  keep this simple case simple with this hook, not forcing a
 *  derived class to reimplement CDocumentAdviseSink.
 *
 * Parameters:
 *  pDoc            PCDocument notifying the sink.
 */

void CFrame::OnDocumentDataChange(PCDocument pDoc)
    {
    return;
    }





/*
 * CFrame::OnDocumentActivate
 *
 * Purpose:
 *  Most of the CDocumentAdviseSink notifications we get are fairly
 *  standard implementations.  When the current document changes,
 *  however, there's probably more UI that frame derivations need
 *  to do, so we allow the hook here.
 *
 * Parameters:
 *  pDoc            PCDocument notifying the sink.
 */

void CFrame::OnDocumentActivate(PCDocument pDoc)
    {
    return;
    }






/*
 * CFrame::SaveOpenDialog
 *
 * Purpose:
 *  Invokes the COMMDLG.DLL GetOpenFileName dialog and retrieves
 *  a filename for saving or opening.
 *
 * Parameters:
 *  pszFile         LPTSTR buffer to receive the entered filename.
 *  cchFile         UINT length of pszFile
 *  idsCaption      UINT of  string to use in the caption bar.
 *  fOpen           BOOL indicating if we want file open or save.
 *  puType          UINT * in which we store the selected type.
 *                  Can be NULL.
 *
 * Return Value:
 *  BOOL            TRUE if the function retrieved a filename,
 *                  FALSE if the user pressed CANCEL.
 */

BOOL CFrame::SaveOpenDialog(LPTSTR pszFile, UINT cchFile
    , UINT idsCaption, BOOL fOpen, UINT *puType)
    {
    OPENFILENAME        ofn;
    TCHAR               szFilter[80];
    UINT                cch;
    BOOL                fRet;
   #ifdef DEBUG
    DWORD               dwErr;
   #endif

    if (NULL==pszFile)
        return FALSE;

    memset(&ofn, 0, sizeof(OPENFILENAME));
    ofn.lStructSize      =sizeof(OPENFILENAME);
    ofn.hwndOwner        =m_hWnd;

    if (fOpen)
        lstrcpy(szFilter, PSZ(IDS_FILEOPENFILTER));
    else
        lstrcpy(szFilter, PSZ(IDS_FILESAVEFILTER));

    cch=lstrlen(szFilter);
    ReplaceCharWithNull(szFilter, szFilter[cch-1]);

    ofn.lpstrFilter      =szFilter;
    ofn.nFilterIndex     =1L;

    ofn.lpstrTitle       =PSZ(idsCaption);
    ofn.lpstrFile        =pszFile;
    ofn.nMaxFile         =cchFile;

    ofn.lpstrDefExt      =PSZ(IDS_DEFEXT);

    if (fOpen)
        {
        ofn.Flags=OFN_HIDEREADONLY | OFN_FILEMUSTEXIST;
        fRet=GetOpenFileName(&ofn);
        }
    else
        {
        ofn.Flags=OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
        fRet=GetSaveFileName(&ofn);
        }

    if (fRet || NULL!=puType)
        *puType=(UINT)ofn.nFilterIndex;

   #ifdef DEBUG
    dwErr=CommDlgExtendedError();
   #endif
    return fRet;
    }






/*
 * CFrame::ReplaceCharWithNull
 *
 * Purpose:
 *  Walks a null-terminated string and replaces a given character
 *  with a zero for use with the SaveOpenDialog member.
 *
 * Parameters:
 *  psz             LPTSTR to the string to process.
 *  ch              int character to replace.
 *
 * Return Value:
 *  int             Number of characters replaced.  -1 if psz is NULL
 */

UINT CFrame::ReplaceCharWithNull(LPTSTR psz, int ch)
    {
    UINT            cChanged=0;

    if (NULL==psz)
        return 0;

    while ((TCHAR)0!=*psz)
        {
        if (ch==*psz)
            {
            *psz=0;
            cChanged++;
            }

        psz++;
        }

    return cChanged;
    }






/*
 * CFrame::PszWhiteSpaceScan
 *
 * Purpose:
 *  Skips characters in a string until a whitespace or non-whitespace
 *  character is seen.  Whitespace is defined as \n, \r, \t, or ' '.
 *
 * Parameters:
 *  psz             LPTSTR to string to manipulate
 *  fSkip           BOOL  TRUE if we want to skip whitespace.
 *                  FALSE if we want to skip anything but whitespace.
 *
 * Return Value:
 *  LPTSTR          Pointer to first character in the string that
 *                  either non-whitespace (fSkip=TRUE) or
 *                  whitespace (fSkip=FALSE), which may be the
 *                  null terminator.
 */

LPTSTR CFrame::PszWhiteSpaceScan(LPTSTR psz, BOOL fSkip)
    {
    TCHAR       ch;
    BOOL        fWhite;

    while (ch=*psz)
        {
        //Not too sure how this localizes...
        fWhite=(TEXT('\n')==ch || TEXT('\r')==ch
            || TEXT('\t')==ch || TEXT(' ')==ch);

        //Too bad C doesn't have a logical XOR (^^) operator.
        if ((fSkip && !fWhite) || (!fSkip && fWhite))
            break;

        psz++;
        }

    return psz;
    }






//PUBLIC FUNCTIONS




/*
 * CFrame::AskAndSave
 *
 * Purpose:
 *  If a document is closed and is dirty the client window we own
 *  will get the document's filename and call us here.  We will
 *  ask the user if they want to save that file and if so, send a
 *  message to our frame window to execute the Save command.
 *
 * Parameters:
 *  pszDoc          LPTSTR name of the document.  If the first
 *                  character is 0 then we use (Untitled).
 *
 * Return Value:
 *  BOOL            TRUE if the user saved or didn't; FALSE on
 *                  if the user pressed cancel.
 */

BOOL CFrame::AskAndSave(LPTSTR pszDoc)
    {
    BOOL            fRet=TRUE;
    UINT            uRet;
    TCHAR           szTemp[CCHFILENAMEMAX+100];

    if (NULL==pszDoc)
        return FALSE;

    if ((TCHAR)0==*pszDoc)
        pszDoc=PSZ(IDS_UNTITLED);
    else
        {
        GetFileTitle(pszDoc, szTemp, CCHFILENAMEMAX);
        lstrcpy(pszDoc, szTemp);
        }

    wsprintf(szTemp, PSZ(IDS_FILEDIRTY), pszDoc);

    uRet=MessageBox(m_hWnd, szTemp, PSZ(IDS_CAPTION)
        , MB_YESNOCANCEL | MB_ICONEXCLAMATION);

    /*
     * If the user wants to save, tell the window to execute the
     * command.
     */
    if (IDYES==uRet)
        {
        /*
         * The following is code taken from IDM_SAVE and IDM_SAVEAS
         * cases inside OnCommand above.  It's copied here to
         * allow processing of the return value from pDoc->Save.
         */
        PCDocument      pDoc;
        TCHAR           szFile[CCHPATHMAX];
        BOOL            fOK;
        UINT            uTemp;
        UINT            uType;
        PCHourglass     pHour;

        pDoc=m_pCL->ActiveDocument();

        fOK=pDoc->FQuerySave();

        if (fOK)
            {
            //Save using current document name and version
            pHour=new CHourglass;
            uTemp=pDoc->Save(0, NULL);
            delete pHour;

            pDoc->ErrorMessage(uTemp);

            //This return code is for CFrame::AskAndSave
            return (DOCERR_NONE==uTemp);
            }

        //Go get a filename, then save it.
        pDoc->FilenameGet(szFile, CCHPATHMAX);

        fOK=SaveOpenDialog(szFile, CCHPATHMAX, IDS_FILESAVEAS
            , FALSE, &uType);

        if (!fOK)
            return 0L;

        pHour=new CHourglass;
        uTemp=pDoc->Save(uType, szFile);
        delete pHour;
        pDoc->ErrorMessage(uTemp);

        return (DOCERR_NONE==uTemp);
        }

    //TRUE for No, False for Cancel
    return (IDCANCEL!=uRet);
    }





/*
 * CFrame::UpdateMenus
 *
 * Purpose:
 *  Handles the WM_INITMENU message for the frame window.  Depending
 *  on the existence of an active window, menu items are selectively
 *  enabled and disabled.
 *
 * Parameters:
 *  hMenu           HMENU of the menu to intialize
 *  iMenu           UINT position of the menu.
 */

void CFrame::UpdateMenus(HMENU hMenu, UINT iMenu)
    {
    PCDocument  pDoc;
    BOOL        fOK=FALSE;
    UINT        uTemp;
    UINT        uTempE;
    UINT        uTempD;

    pDoc=m_pCL->ActiveDocument();

    uTempE=MF_ENABLED | MF_BYCOMMAND;
    uTempD=MF_DISABLED | MF_GRAYED | MF_BYCOMMAND;
    uTemp=((NULL!=pDoc) ? uTempE : uTempD);

    /*
     * File menu:  If there is no current document window, disable
     * Close, Save, and Save As.  If there is a document but
     * it doesn't have a filename, disable save.
     */
    if (m_phMenu[0]==hMenu)
        {
        EnableMenuItem(hMenu, IDM_FILECLOSE,  uTemp);
        EnableMenuItem(hMenu, IDM_FILESAVE,   uTemp);
        EnableMenuItem(hMenu, IDM_FILESAVEAS, uTemp);

        if (NULL!=pDoc)
            fOK=pDoc->FQuerySave();

        EnableMenuItem(hMenu, IDM_FILESAVE, (fOK) ? uTempE : uTempD);
        }


    /*
     * Edit menus:  If there's no document, disable all of it.
     * If there's a document but no clipboard format available,
     * disable paste only.
     */
    if (m_phMenu[1]==hMenu)
        {
        EnableMenuItem(hMenu, IDM_EDITUNDO,  uTemp);
        EnableMenuItem(hMenu, IDM_EDITCOPY,  uTemp);
        EnableMenuItem(hMenu, IDM_EDITCUT,   uTemp);

        /*
         * Paste has two dependencies; format available and an open
         * document
         */
        if (NULL!=pDoc)
            fOK=pDoc->FQueryPaste();

        fOK &=(uTemp==uTempE);
        EnableMenuItem(hMenu,IDM_EDITPASTE, (fOK) ? uTempE : uTempD);
        }


   #ifdef MDI
    //Window menu:  no document, no commands
    if (m_hMenuWindow==hMenu)
        {
        EnableMenuItem(hMenu, IDM_WINDOWCASCADE,  uTemp);
        EnableMenuItem(hMenu, IDM_WINDOWTILEHORZ, uTemp);
        EnableMenuItem(hMenu, IDM_WINDOWTILEVERT, uTemp);
        EnableMenuItem(hMenu, IDM_WINDOWICONS,    uTemp);
        }
   #endif

    return;
    }









/*
 * CFrame::UpdateToolbar
 *
 * Purpose:
 *  Enables and disablest toolbar buttons depending on whether we
 *  have a document or not and depending on clipboard format
 *  availability.
 */

void CFrame::UpdateToolbar(void)
    {
    PCDocument  pDoc;
    BOOL        fEnable;

    pDoc=m_pCL->ActiveDocument();
    fEnable=(NULL!=pDoc);

    if (m_fLastEnable!=fEnable)
        {
        m_fLastEnable=fEnable;

        //No document, disable just about everything
        m_pTB->Enable(IDM_FILECLOSE,  fEnable);
        m_pTB->Enable(IDM_FILESAVE,   fEnable);

        m_pTB->Enable(IDM_EDITUNDO,  fEnable);
        m_pTB->Enable(IDM_EDITCUT,   fEnable);
        m_pTB->Enable(IDM_EDITCOPY,  fEnable);
        }

    //Special handling:  clipboard format available, enable paste
    if (NULL!=pDoc)
        fEnable &= pDoc->FQueryPaste();

    //Paste is not enabled unless there's a document too
    if (m_fLastPaste!=fEnable)
        {
        m_fLastPaste=fEnable;
        m_pTB->Enable(IDM_EDITPASTE, fEnable);
        }

    return;
    }








/*
 * CFrame::WindowTitleSet
 *
 * Purpose:
 *  Handles changing the caption bar of a document window.
 *
 * Parameters:
 *  pDoc            PCDocument of the document affected.  If NULL,
 *                  then we remove titles.
 *  fDocTitle       BOOL indicating to set the document or the main
 *                  window captions.  In MDI we may do either, this
 *                  is ignored in SDI.
 */

void CFrame::WindowTitleSet(PCDocument pDoc, BOOL fDocTitle)
    {
    TCHAR       szTitle[CCHPATHMAX];
    TCHAR       szFile[CCHPATHMAX];

    /*
     * Go grab the filename.  If we get an emtpy file back, then
     * we'll use (Untitled).  If we have a NULL document, then we'll
     * just set the title of the app back to having no filename.
     */
    if (NULL!=pDoc)
        {
        pDoc->FilenameGet(szTitle, CCHPATHMAX);

        if ((TCHAR)0==szTitle[0])
            lstrcpy(szFile, PSZ(IDS_UNTITLED));
        else
            {
            GetFileTitle(szTitle, szFile, sizeof(szFile));
           #ifndef WIN32
            AnsiUpper(szFile);
           #endif
            }
        }
    else
        szFile[0]=0;

   #ifndef MDI
    //SDI always titles the application window
    fDocTitle=FALSE;
   #endif

    if (fDocTitle)
        {
        if (NULL!=pDoc)
            SetWindowText(pDoc->Window(), szFile);
        }
    else
        {
        if ((TCHAR)0!=szFile[0])
            {
            wsprintf(szTitle, TEXT("%s - %s"), PSZ(IDS_CAPTION)
                , (LPTSTR)szFile);
            SetWindowText(m_hWnd, szTitle);
            }
        else
            SetWindowText(m_hWnd, PSZ(IDS_CAPTION));
        }

    return;
    }




/*
 * CFrame::StatusLine (inline)
 *
 * Purpose:
 *  Returns the status line object pointer to the caller so they can
 *  display status messages.
 *
 * Return Value:
 *  PCStatusLine    Pointer to the status line object.
 */

PCStatusLine inline CFrame::StatusLine(void)
    {
    return m_pSL;
    }
