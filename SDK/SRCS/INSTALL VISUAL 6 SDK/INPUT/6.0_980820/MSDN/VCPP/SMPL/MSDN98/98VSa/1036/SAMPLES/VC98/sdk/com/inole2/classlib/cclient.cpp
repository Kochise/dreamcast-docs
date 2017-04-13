/*
 * CCLIENT.CPP
 * Sample Code Class Libraries
 *
 * Implementation of the CClient class that handles an SDI or MDI
 * client area window.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include <windows.h>
#include "classlib.h"
#include <dbgout.h>


/*
 * CClient::CClient
 * CClient::~CClient
 *
 * Constructor Parameters:
 *  hInst           HINSTANCE of the application.
 *  pFR             PCFrame of the frame object.
 */

CClient::CClient(HINSTANCE hInst, PCFrame pFR)
    : CWindow(hInst)
    {
    m_pFR=pFR;
    m_cDoc=0;
    m_pDocLast=NULL;
    m_hListDocs=NULL;
    m_pAdv=NULL;
    return;
    }


CClient::~CClient(void)
    {
    if (NULL!=m_hListDocs)
        DestroyWindow(m_hListDocs);

    if (NULL!=m_pAdv)
        delete m_pAdv;

    return;
    }





/*
 * CClient::Init
 *
 * Purpose:
 *  Creates a client area window sensitive to SDI or MDI
 *  (compile-time) as well as performng other internal
 *  initialization.
 *
 * Parameters:
 *  hMenuWindow     HWND of the Window menu on the frame.
 *  pRect           LPRECT containing the desired window rectangle.
 *
 * Return Value:
 *  BOOL            TRUE if the function succeeded, FALSE otherwise.
 */

BOOL CClient::Init(HMENU hMenuWindow, LPRECT pRect)
    {
    HWND                hWndFrame;
    LPTSTR              pszClass;
    DWORD               dwStyle;
    CLIENTCREATESTRUCT  ccs;

    hWndFrame=m_pFR->Window();

   #ifdef MDI
    ccs.hWindowMenu =hMenuWindow;
    ccs.idFirstChild=ID_MDICHILDMIN;
    pszClass=TEXT("mdiclient");
    dwStyle=MDIS_ALLCHILDSTYLES;
   #else
    //SDI
    pszClass=SZCLASSSDICLIENT;
    dwStyle=0L;
   #endif

    m_hWnd=CreateWindow(pszClass, pszClass, dwStyle | WS_CHILD
        | WS_CLIPCHILDREN | WS_VISIBLE | WS_CLIPSIBLINGS
        , pRect->left, pRect->top, pRect->right-pRect->left
        , pRect->bottom-pRect->top, hWndFrame, NULL, m_hInst
        , &ccs);

    if (NULL==m_hWnd)
        return FALSE;

    //Create the hidden listbox for managing our list of documents
    m_hListDocs=CreateWindow(TEXT("listbox"), TEXT("Document List")
        , WS_POPUP | LBS_OWNERDRAWFIXED, 0, 0, 100, 100
        , HWND_DESKTOP, NULL, m_hInst, NULL);

    if (NULL==m_hListDocs)
        return FALSE;

    /*
     * Create an advise sink for the frame.  If this fails, then
     * we'll just do without it.
     */
    m_pAdv=new CDocumentAdviseSink(m_pFR);

    return TRUE;
    }





/*
 * CClient::CreateDoc (Internal)
 * CClient::CreateCDocument (Virtual)
 *
 * Purpose:
 *  Constructs a new document.  This function is overridable so an
 *  app can use the default CClient but create a derived document
 *  class.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  PCDocument      Pointer to the new document object.
 */

PCDocument CClient::CreateDoc(void)
    {
    PCDocument  pDoc;

    pDoc=CreateCDocument();
    m_pDocLast=pDoc;

    return pDoc;
    }

PCDocument CClient::CreateCDocument(void)
    {
    return new CDocument(m_hInst, m_pFR, m_pAdv);
    }



/*
 * CClient::Frame
 * CClient::DocumentCount
 * CClient::DocumentList
 *
 * Purpose:
 *  Trivial members to provide public access to various members.
 */

PCFrame CClient::Frame(void)
    {
    return m_pFR;
    }

UINT CClient::DocumentCount(void)
    {
    return m_cDoc;
    }

HWND CClient::DocumentList(void)
    {
    return m_hListDocs;
    }




/*
 * CClient::TranslateAccelerator
 *
 * Purpose:
 *  Provides an isolated system accelerator translation as necessary
 *  for the client window.  In MDI this calls TranslateMDISysAccel
 *  but is a NOP in SDI.
 *
 * Parameters:
 *  pMsg            LPMSG to the message from GetMessage
 *
 * Return Value:
 *  BOOL            TRUE if the accelerator was translated and
 *                  processed, FALSE otherwise.
 */

BOOL CClient::TranslateAccelerator(LPMSG pMsg)
    {
   #ifdef MDI
    return TranslateMDISysAccel(m_hWnd, pMsg);
   #else
    return FALSE;
   #endif
    }





/*
 * CClient::DefFrameProc
 *
 * Purpose:
 *  Encapsulates which default message procedure to call for a frame
 *  window: SDI (DefWindowProc) or MDI (DefFrameProc).
 *
 * Parameters:
 *  hWnd            HWND of the frame
 *  iMsg            UINT of the message
 *  wParam          WPARAM of the message
 *  lParam          LPARAM of the message
 *
 * Return Value:
 *  LRESULT         Return value for the message.
 */

LRESULT CClient::DefaultFrameProc(HWND hWnd, UINT iMsg, WPARAM wParam
    , LPARAM lParam)
    {
   #ifdef MDI
    return (DefFrameProc(hWnd, m_hWnd, iMsg, wParam, lParam));
   #else
    return (DefWindowProc(hWnd, iMsg, wParam, lParam));
   #endif
    }





/*
 * CClient::OnWindowCommand
 *
 * Purpose:
 *  Handles Window menu commands for MDI situations.  This is a NOP
 *  in SDI.
 *
 * Parameters:
 *  uCommand        UINT command to execute:
 *                      WM_MDICASCADE
 *                      WM_MDITILE
 *                      WM_MDIICONARRANGE
 *
 *  uOption         UINT optional parameter for WM_MDITILE, either
 *                  MDITILE_HORIZONTAL or MDITILE_VERTICAL.
 *
 * Return Value:
 *  None
 */

void CClient::OnWindowCommand(UINT uCommand, UINT uOption)
    {
    SendMessage(m_hWnd, uCommand, (WPARAM)uOption, 0L);
    return;
    }







/*
 * CClient::OnSize
 *
 * Purpose:
 *  Handles resizing the client window when the frame is resized.
 *
 * Parameters:
 *  x, y            UINT new location of the window.
 *  cx, cy          UINT new dimensions of the window.
 *
 * Return Value:
 *  None
 */

void CClient::OnSize(UINT x, UINT y, UINT cx, UINT cy)
    {
    SetWindowPos(m_hWnd, NULL, x, y, cx, cy
        , SWP_NOZORDER | SWP_NOACTIVATE);
    return;
    }






/*
 * CClient::NewDocument
 *
 * Purpose:
 *  Creates a new blank document in the client space.  See
 *  CloseDocument for the opposite effect.
 *
 * Parameters:
 *  fVisible        BOOL indicating if the document is to be visible
 *                  or not.
 *
 * Return Value:
 *  PCDocument      Pointer to the new document object.
 */

PCDocument CClient::NewDocument(BOOL fVisible)
    {
    MDICREATESTRUCT mcs;
    HWND            hWndDoc;
    PCDocument      pDoc, pDocTemp;
    DOCUMENTINIT    di;
    BOOL            fCreate=TRUE;
   #ifdef MDI
    DWORD           dw;
   #endif

   #ifdef MDI
    //In MDI we create a new CDocument
    pDoc=CreateDoc();  //This could create a derived class...
   #else
    //In SDI we close the one we have and create a new one.
    pDoc=ActiveDocument();

    if (NULL!=pDoc)
        CloseDocument(pDoc);

    pDoc=CreateDoc();
   #endif

    if (NULL==pDoc)
        return NULL;

    if (fCreate)
        {
        /*
         * We implement this by having the client window actually
         * create the windows instead of using the CDocument
         * initializer.  Reason being is that we ask the client to
         * actually create the window using WM_MDICREATE (which works
         * for our SDI client as well. Since we need to conditionally
         * compile for MDI or SDI here, we create a window before
         * calling the document constructor.
         */

        mcs.szTitle=TEXT("");
        mcs.szClass=SZCLASSDOCUMENT;
        mcs.hOwner =m_hInst;
        mcs.lParam =(LPARAM)pDoc;

        mcs.x =CW_USEDEFAULT;
        mcs.cx=CW_USEDEFAULT;
        mcs.y =CW_USEDEFAULT;
        mcs.cy=CW_USEDEFAULT;

        /*
         * Set the style of the window, controlling visiblity.
         * WS_CLIPCHILDREN is important to prevent unnecessary
         * flashing of document contents that we'll usually fill
         * with some editor window.
         */
       #ifdef MDI
        mcs.style=WS_CHILD | WS_SYSMENU | WS_CAPTION
            | WS_CLIPSIBLINGS| WS_THICKFRAME | WS_MINIMIZEBOX
            | WS_MAXIMIZEBOX| WS_CLIPCHILDREN
            | ((fVisible) ? WS_VISIBLE : 0L);

        //If the current document is maxmized, maximize this one
       #ifdef WIN32
        pDocTemp=ActiveDocument();

        if (NULL!=pDocTemp)
            {
            dw=GetWindowLong(pDocTemp->Window(), GWL_STYLE);
            mcs.style |= (dw & WS_MAXIMIZE);
            }
       #else
        pDocTemp=NULL;
        dw=SendMessage(m_hWnd, WM_MDIGETACTIVE, 0, 0L);

        if (HIWORD(dw))
            mcs.style |= WS_MAXIMIZE;
       #endif //WIN32

       #else
        mcs.style=WS_CHILD | WS_CLIPCHILDREN
            | ((fVisible) ? WS_VISIBLE : 0L);
       #endif //MDI

        //Tell the Client window to create the child
        hWndDoc=(HWND)(UINT)SendMessage(m_hWnd, WM_MDICREATE, 0
            , (LONG)&mcs);


        di.idsMin=IDS_STANDARDDOCMIN;
        di.idsMax=IDS_STANDARDDOCMAX;
        di.hWndDoc=hWndDoc;

        if (!pDoc->Init(&di))
            {
            if (m_pDocLast==pDoc)
                m_pDocLast=NULL;

            SendMessage(m_hWnd, WM_MDIDESTROY, (WPARAM)hWndDoc, 0L);
            delete pDoc;
            return NULL;
            }
        }

    m_cDoc++;

    /*
     * Add this document to the end of our list.  This list is
     * maintained strictly in the order of creation.
     */
    SendMessage(m_hListDocs, LB_ADDSTRING, 0, (LONG)pDoc);

    //Update menus and gizmos for the new document if visible
    if (fVisible)
        m_pFR->UpdateToolbar();

    return pDoc;
    }







/*
 * CClient::ActiveDocument
 *
 * Purpose:
 *  Returns the active document window (encapsulates WM_MDIGETACTIVE)
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  PCDocument      Pointer to the active document object.
 */

PCDocument CClient::ActiveDocument(void)
    {
    PCDocument  pDoc=NULL;
    HWND        hWnd;

    hWnd=(HWND)(UINT)SendMessage(m_hWnd, WM_MDIGETACTIVE, 0, 0L);

    if (NULL!=hWnd)
        pDoc=(PCDocument)SendMessage(hWnd, DOCM_PDOCUMENT, 0, 0L);
    else
        pDoc=m_pDocLast;

    return pDoc;
    }




/*
 * CClient::ShowDocument
 *
 * Purpose:
 *  Shows or hides a document.
 *
 * Parameters:
 *  pDoc            PCDocument to show or hide.
 *  fShow           BOOL indicating whether to show or hide the
 *                  document.
 *
 * Return Value:
 *  BOOL            Previous shown state of the document.
 */

BOOL CClient::ShowDocument(PCDocument pDoc, BOOL fShow)
    {
    BOOL        fRet;

    if (NULL==pDoc)
        return FALSE;

    fRet=IsWindowVisible(pDoc->Window());

    ShowWindow(pDoc->Window(), fShow ? SW_SHOW : SW_HIDE);

    MDIREFRESHMENU(m_hWnd);     //Macro in book1632.h
    DrawMenuBar(m_pFR->Window());

    SendMessage(m_hWnd, WM_MDIACTIVATE, (WPARAM)pDoc->Window(), 0L);

    //Update toolbar if we're changing a document's visibility
    if (fShow != fRet)
        m_pFR->UpdateToolbar();

    return fRet;
    }






/*
 * CClient::SDIVerify
 *
 * Purpose:
 *  In MDI, this is a NOP, but in SDI checks if the user has dirtied
 *  and wants to save the current document before blasting it away.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if the operation calling us can proceed,
 *                  FALSE to abort the operation.
 */

BOOL CClient::SDIVerify(void)
    {
   #ifdef MDI
    return TRUE;
   #else
    PCDocument      pDoc;

    pDoc=ActiveDocument();

    /*
     * In SDI, we'll erase the current, so verify if we have one
     * before continuing.  If we don't have any document, then we
     * don't have a problem.
     */

    if (NULL==pDoc)
        return TRUE;

    return FCleanVerify(pDoc);
   #endif
    }






/*
 * CClient::CloseDocument
 *
 * Purpose:
 *  Closes a document created with NewDocument.
 *
 * Parameters:
 *  pDoc            PCDocument of the document to close.
 *
 * Return Value:
 *  UINT            New count of open documents.
 */

UINT CClient::CloseDocument(PCDocument pDoc)
    {
    HWND        hWndT;
    UINT        i;

    if (NULL==pDoc)
        return m_cDoc;

    /*
     * Again, since the client window controlled document creation
     * we destroy the document window here instead of asking the
     * document to do it for us.  Once we're rid of the window then
     * we can use the destructor.
     */

    hWndT=pDoc->Window();

    //Don't delete unowned windows.
    if (GetParent(hWndT)!=m_hWnd)
        return m_cDoc;

    //Remove this document from our list.
    for (i=0; i < m_cDoc; i++)
        {
        PCDocument  pDocTemp;

        if (LB_ERR==SendMessage(m_hListDocs, LB_GETTEXT
            , i, (LONG)&pDocTemp))
            continue;

        if (pDoc==pDocTemp)
            SendMessage(m_hListDocs, LB_DELETESTRING, i, 0L);
        }

    m_cDoc--;

    //Update window text.  Maxed MDI windows handled automatically.
   #ifdef MDI
    m_pFR->WindowTitleSet(NULL, TRUE);
   #else
    m_pFR->WindowTitleSet(NULL, FALSE);
   #endif

    if (m_pDocLast==pDoc)
        m_pDocLast=NULL;

    //Let the document clean up first, then we can nuke the window.
    SendMessage(m_hWnd, WM_MDIDESTROY, (WPARAM)hWndT, 0L);
    delete pDoc;

    return m_cDoc;
    }







/*
 * CClient::QueryCloseAllDocuments
 *
 * Purpose:
 *  Ask every document window we have in us if we can close them
 *  down.  We use this when exiting the entire application.
 *
 * Parameters:
 *  fClose          BOOL indicating if we should query close on the
 *                  documents or acutally close them.
 *  fSaveChanges    BOOL indicating if we should prompt for saving
 *                  changes before closing.
 *
 * Return Value:
 *  BOOL            TRUE if we can close, FALSE otherwise.
 */

BOOL CClient::QueryCloseAllDocuments(BOOL fClose, BOOL fSaveChanges)
    {
    UINT        i;
    UINT        cDoc;
    PCDocument  pDoc;

    cDoc=(UINT)SendMessage(m_hListDocs, LB_GETCOUNT, 0, 0L);

    for (i=0; i < cDoc; i++)
        {
        if (LB_ERR!=SendMessage(m_hListDocs, LB_GETTEXT, 0
            , (LONG)&pDoc))
            {
            if (fClose)
                {
                if (fSaveChanges)
                    {
                    if (!FCleanVerify(pDoc))
                        return FALSE;
                    }

                CloseDocument (pDoc);
                }
            else
                {
                if (!(BOOL)SendMessage(pDoc->Window(), WM_QUERYENDSESSION
                    , 0, 0))
                    return FALSE;
                }
            }
        }

    return TRUE;
    }






/*
 * CClient::FCleanVerify
 *
 * Purpose:
 *  Checks if the document under scrutiny is dirty or not.  If so,
 *  then we ask the user if they want to save it.  If not, then we
 *  just return TRUE.  Note that a hidden document is always considered
 *  clean.
 *
 * Parameters:
 *  pDoc            PCDocument under consideration.
 *
 * Return Value:
 *  BOOL            TRUE if the document is clean, saved, or the user
 *                  doesn't want to save it.  FALSE if the user
 *                  presses Cancel or the document was not saved.
 */

BOOL CClient::FCleanVerify(PCDocument pDoc)
    {
    TCHAR           szFile[CCHPATHMAX];
    LPTSTR          psz=szFile;

    if (NULL==pDoc)
        return TRUE;

    if (!IsWindowVisible(pDoc->Window()))
        return TRUE;

    //Nothing to do if we're clean.
    if (!pDoc->FDirtyGet())
        return TRUE;

    //Get the filename and send to the frame for asking the question.
    *psz=0;
    pDoc->FilenameGet(psz, CCHPATHMAX);

    return m_pFR->AskAndSave(psz);
    }






/*
 * SDIClientWndProc
 *
 * Purpose:
 *  SDI client window class that will create one document for us,
 *  emulating the functions of an MDI client but with only one doc.
 */

LRESULT APIENTRY SDIClientWndProc(HWND hWnd, UINT iMsg
    , WPARAM wParam, LPARAM lParam)
    {
    HWND                hWndDoc;
    LPMDICREATESTRUCT   pMCS;
    RECT                rc;

    hWndDoc=(HWND)GetWindowLong(hWnd, CLIENTWL_HWNDDOC);

    switch (iMsg)
        {
        case WM_CREATE:
            SetWindowLong(hWnd, CLIENTWL_HWNDDOC, 0L);
            break;

        case WM_SIZE:
            if (NULL!=hWndDoc)
                {
                //Change the document window to match
                SetWindowPos(hWndDoc, NULL, 0,  0, LOWORD(lParam)
                    , HIWORD(lParam), SWP_NOMOVE | SWP_NOZORDER
                    | SWP_NOACTIVATE);
                }
            break;


        case WM_MDICREATE:
            pMCS=(LPMDICREATESTRUCT)lParam;

            //We only ate one *visible* document in SDI cases.
            if (NULL!=hWndDoc && (WS_VISIBLE & pMCS->style))
                return (LONG)(UINT)hWndDoc;

            /*
             * For our one visible window, we set this as the active
             * window.  For hidden windows, we return their window
             * handle but don't change the 'active' window we store.
             *
             * Note that we force SDI documents to fill the client
             * area.
             */

            GetClientRect(hWnd, &rc);

            hWndDoc=CreateWindowEx(WS_EX_NOPARENTNOTIFY
                , pMCS->szClass, pMCS->szTitle, pMCS->style
                , rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top
                , hWnd, (HMENU)ID_DOCUMENT, (HINSTANCE)pMCS->hOwner
                , pMCS);


            if (WS_VISIBLE & pMCS->style)
                {
                ShowWindow(hWndDoc, SW_SHOW);
                SetWindowLong(hWnd, CLIENTWL_HWNDDOC
                    , (LONG)(UINT)hWndDoc);
                }

            return (LONG)(UINT)hWndDoc;


        case WM_MDIACTIVATE:
            /*
             * Make the new window the active one.  The NEWMDIACTIVE
             * macro is wParam in Win16, lParam in Win32.
             */
            SetWindowLong(hWnd, CLIENTWL_HWNDDOC,(LONG)NEWMDIACTIVE);
            break;


        case WM_MDIGETACTIVE:
            return (LONG)(UINT)hWndDoc;


        case WM_MDIDESTROY:
            //The only windows we should destroy are children of us.
            if (GetParent((HWND)wParam)==hWnd)
                {
                DestroyWindow((HWND)wParam);

                /*
                 * If this is the visible window, clear out the
                 * window word.
                 */
                if ((HWND)wParam==hWndDoc)
                    SetWindowLong(hWnd, CLIENTWL_HWNDDOC, 0L);
                }
            break;

        default:
            return DefWindowProc(hWnd, iMsg, wParam, lParam);
        }

    return 0L;
    }
