/*
 * PATRON.CPP
 * Patron Chapter 1
 *
 * Frame window class for Patron.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "patron.h"


/*
 * WinMain
 *
 * Purpose:
 *  Main entry point of application.  Should register the app class
 *  if a previous instance has not done so and do any other one-time
 *  initializations.
 */

int PASCAL WinMain (HINSTANCE hInst, HINSTANCE hPrev
    , LPSTR pszCmdLine, int nCmdShow)
    {
    PCPatronFrame   pFR;
    FRAMEINIT       fi;
    WPARAM          wRet=0;

    //Attempt to allocate and initialize the application
    pFR=new CPatronFrame(hInst, hPrev, pszCmdLine, nCmdShow);

    if (NULL==pFR)
        return -1;

    fi.idsMin=IDS_FRAMEMIN;
    fi.idsMax=IDS_FRAMEMAX;
    fi.idsStatMin=IDS_STATMESSAGEMIN;
    fi.idsStatMax=IDS_STATMESSAGEMAX;
    fi.idStatMenuMin=ID_MENUFILE;
    fi.idStatMenuMax=ID_MENUHELP;
    fi.iPosWindowMenu=WINDOW_MENU;
    fi.cMenus=CMENUS;

    fi.x=CW_USEDEFAULT;
    fi.y=CW_USEDEFAULT;
    fi.cx=CW_USEDEFAULT;
    fi.cy=CW_USEDEFAULT;

    //If we can initialize pFR, start chugging messages
    if (pFR->Init(&fi))
        wRet=pFR->MessageLoop();

    delete pFR;
    return wRet;
    }




/*
 * CPatronFrame::CPatronFrame
 * CPatronFrame::~CPatronFrame
 *
 * Constructor Parameters:
 *  hInst           HINSTANCE from WinMain
 *  hInstPrev       HINSTANCE from WinMain
 *  pszCmdLine      LPSTR from WinMain
 *  nCmdShow        int from WInMain
 */

CPatronFrame::CPatronFrame(HINSTANCE hInst, HINSTANCE hInstPrev
    , LPSTR pszCmdLine, int nCmdShow)
    : CFrame(hInst, hInstPrev, pszCmdLine, nCmdShow)
    {
    return;
    }


CPatronFrame::~CPatronFrame(void)
    {
    return;
    }




/*
 * CPatronFrame::CreateCClient
 *
 * Purpose:
 *  Constructs a new client specific to the application.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  PCClient        Pointer to the new client object.
 */

PCClient CPatronFrame::CreateCClient(void)
    {
    return (PCClient)(new CPatronClient(m_hInst, this));
    }






/*
 * CPatronFrame::RegisterAllClasses
 *
 * Purpose:
 *  Registers all classes used in this application.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  BOOL            TRUE if registration succeeded, FALSE otherwise.
 */

BOOL CPatronFrame::RegisterAllClasses(void)
    {
    WNDCLASS        wc;

    //First let the standard frame do its thing
    if (!CFrame::RegisterAllClasses())
        return FALSE;

    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.hInstance     = m_hInst;
    wc.cbClsExtra    = 0;
    wc.lpfnWndProc   = PagesWndProc;
    wc.cbWndExtra    = CBPAGESWNDEXTRA;
    wc.hIcon         = NULL;
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = SZCLASSPAGES;

    if (!RegisterClass(&wc))
        return FALSE;

    return TRUE;
    }





/*
 * CPatronFrame::OnCommand
 *
 * Purpose:
 *  WM_COMMAND handler for the Patron frame window that processes
 *  extra File menu items as well as the Page menu.
 *
 * Parameters:
 *  hWnd            HWND of the frame window.
 *  wParam          WPARAM of the message.
 *  lParam          LPARAM of the message.
 *
 * Return Value:
 *  LRESULT         Return value for the message.
 */

LRESULT CPatronFrame::OnCommand(HWND hWnd, WPARAM wParam
    , LPARAM lParam)
    {
    PCPatronDoc     pDoc;

    COMMANDPARAMS(wID, wCode, hWndMsg);

    /*
     * Don't bother with anything during first initialization,
     * skipping many toolbar notifications.
     */
    if (m_fInit)
        return 0L;

    pDoc=(PCPatronDoc)m_pCL->ActiveDocument();

    switch (wID)
        {
        case IDM_FILEPRINT:
            pDoc->Print(m_hWnd);
            return 0L;

        case IDM_FILEPRINTERSETUP:
            pDoc->PrinterSetup(m_hWnd, FALSE);
            return 0L;


        case IDM_PAGENEWPAGE:
            pDoc->NewPage();
            break;

        case IDM_PAGEDELETEPAGE:
            pDoc->DeletePage();
            break;

        case IDM_PAGENEXTPAGE:
            pDoc->NextPage();
            break;

        case IDM_PAGEPREVIOUSPAGE:
            pDoc->PreviousPage();
            break;


        case IDM_PAGEFIRSTPAGE:
            pDoc->FirstPage();
            break;

        case IDM_PAGELASTPAGE:
            pDoc->LastPage();
            break;


        default:
           return CFrame::OnCommand(hWnd, wParam, lParam);
        }

    return 0L;
    }








/*
 * CPatronFrame::CreateToolbar
 *
 * Purpose:
 *  Procedure to create all the necessary toolbar buttons.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  UINT            Number of tools added to the bar.
 */

UINT CPatronFrame::CreateToolbar(void)
    {
    UINT            iLast;
    UINT            uState=GIZMO_NORMAL;
    UINT            utCmd =GIZMOTYPE_BUTTONCOMMAND;

    //Insert the standard ones.
    iLast=CFrame::CreateToolbar();

    //Remove Undo:  we don't use it.
    m_pTB->Remove(IDM_EDITUNDO);

    /*
     * Insert Print File Import in the 5th position and account
     * for it in iLast.
     */
    m_pTB->Add(utCmd, 4, IDM_FILEPRINT, m_dxB, m_dyB
        , NULL, NULL, 6, uState);

    iLast++;

    m_pTB->Add(GIZMOTYPE_SEPARATOR, iLast++, 0, 6, m_dyB
        , NULL, NULL, 0, uState);

    //Add New Page, and Delete Page
    m_pTB->Add(utCmd, iLast++, IDM_PAGENEWPAGE, m_dxB, m_dyB
        , NULL, m_hBmp, 2, uState);
    m_pTB->Add(utCmd, iLast++, IDM_PAGEDELETEPAGE, m_dxB, m_dyB
        , NULL, m_hBmp, 3, uState);

    m_pTB->Add(GIZMOTYPE_SEPARATOR, iLast++, 0, 6, m_dyB
        , NULL, NULL, 0, uState);

    //First, Prev, Next, Last pages.
    m_pTB->Add(utCmd, iLast++, IDM_PAGEFIRSTPAGE, m_dxB, m_dyB
        , NULL, m_hBmp, 4, uState);
    m_pTB->Add(utCmd, iLast++, IDM_PAGEPREVIOUSPAGE, m_dxB, m_dyB
        , NULL, m_hBmp, 5, uState);
    m_pTB->Add(utCmd, iLast++, IDM_PAGENEXTPAGE, m_dxB, m_dyB
        , NULL, m_hBmp, 6, uState);
    m_pTB->Add(utCmd, iLast++, IDM_PAGELASTPAGE, m_dxB, m_dyB
        , NULL, m_hBmp, 7, uState);

    return iLast;
    }







/*
 * CPatronFrame::UpdateMenus
 *
 * Purpose:
 *  Handles the WM_INITMENU message for the frame window.  Depending
 *  on the existence of an active window, menu items are selectively
 *  enabled and disabled.
 *
 * Parameters:
 *  hMenu           HMENU of the menu to intialize
 *  iMenu           UINT position of the menu.
 *
 * Return Value:
 *  None
 */

void CPatronFrame::UpdateMenus(HMENU hMenu, UINT iMenu)
    {
    PCPatronDoc     pDoc;
    BOOL            fOK=FALSE;
    BOOL            fCallDefault=TRUE;
    UINT            uTemp;
    UINT            uTempE;
    UINT            uTempD;

    pDoc=(PCPatronDoc)m_pCL->ActiveDocument();

    uTempE=MF_ENABLED | MF_BYCOMMAND;
    uTempD=MF_DISABLED | MF_GRAYED | MF_BYCOMMAND;
    uTemp=((NULL!=pDoc) ? uTempE : uTempD);

    //File menu
    if (m_phMenu[0]==hMenu)
        {
        EnableMenuItem(hMenu, IDM_FILEPRINT, uTemp);
        EnableMenuItem(hMenu, IDM_FILEPRINTERSETUP, uTemp);
        }

    //Page menu
    if (m_phMenu[2]==hMenu)
        {
        EnableMenuItem(hMenu, IDM_PAGENEWPAGE,      uTemp);
        EnableMenuItem(hMenu, IDM_PAGEDELETEPAGE,   uTemp);
        EnableMenuItem(hMenu, IDM_PAGENEXTPAGE,     uTemp);
        EnableMenuItem(hMenu, IDM_PAGEPREVIOUSPAGE, uTemp);
        EnableMenuItem(hMenu, IDM_PAGEFIRSTPAGE,    uTemp);
        EnableMenuItem(hMenu, IDM_PAGELASTPAGE,     uTemp);
        }


    if (fCallDefault)
        CFrame::UpdateMenus(hMenu, iMenu);

    return;
    }






/*
 * CPatronFrame::UpdateToolbar
 *
 * Purpose:
 *  Enables and disables tools depending on whether we have
 *  a document or not.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  None
 */

void CPatronFrame::UpdateToolbar(void)
    {
    PCDocument  pDoc;
    BOOL        fEnable;

    //Let the default hack on its tools.
    CFrame::UpdateToolbar();

    pDoc=m_pCL->ActiveDocument();
    fEnable=(NULL!=pDoc);

    //No document, disable just about everything
    m_pTB->Enable(IDM_FILEPRINT,        fEnable);
    m_pTB->Enable(IDM_FILEPRINTERSETUP, fEnable);

    m_pTB->Enable(IDM_PAGENEWPAGE,      fEnable);
    m_pTB->Enable(IDM_PAGEDELETEPAGE,   fEnable);
    m_pTB->Enable(IDM_PAGEFIRSTPAGE,    fEnable);
    m_pTB->Enable(IDM_PAGEPREVIOUSPAGE, fEnable);
    m_pTB->Enable(IDM_PAGENEXTPAGE,     fEnable);
    m_pTB->Enable(IDM_PAGELASTPAGE,     fEnable);

    return;
    }
