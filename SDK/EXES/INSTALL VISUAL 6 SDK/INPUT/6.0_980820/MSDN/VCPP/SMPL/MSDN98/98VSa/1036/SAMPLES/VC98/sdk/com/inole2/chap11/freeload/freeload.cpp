/*
 * FREELOAD.CPP
 * Freeloader Chapter 11
 *
 * Freeloader application that uses OLE's data cache
 * to provide free drawing and serialization services for
 * bitmaps and metafiles.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#define INITGUIDS
#include "freeload.h"


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
    PCFreeloaderFrame   pFR;
    FRAMEINIT           fi;
    WPARAM              wRet;

    SETMESSAGEQUEUE(96);

    pFR=new CFreeloaderFrame(hInst, hPrev, pszCmdLine, nCmdShow);

    if (NULL==pFR)
        return -1;

    fi.idsMin=IDS_STANDARDFRAMEMIN;
    fi.idsMax=IDS_STANDARDFRAMEMAX;
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
    if (pFR->FInit(&fi))
        wRet=pFR->MessageLoop();

    delete pFR;
    return wRet;
    }





/*
 * CFreeloaderFrame::CFreeloaderFrame
 * CFreeloaderFrame::~CFreeloaderFrame
 *
 * Constructor Parameters:
 *  hInst           HINSTANCE from WinMain
 *  hInstPrev       HINSTANCE from WinMain
 *  pszCmdLine      LPSTR from WinMain
 *  nCmdShow        int from WInMain
 */

CFreeloaderFrame::CFreeloaderFrame(HINSTANCE hInst
    , HINSTANCE hInstPrev, LPSTR pszCmdLine, int nCmdShow)
    : CFrame(hInst, hInstPrev, pszCmdLine, nCmdShow)
    {
    m_fInitialized=FALSE;
    return;
    }


CFreeloaderFrame::~CFreeloaderFrame(void)
    {
    if (m_fInitialized)
        OleUninitialize();

    return;
    }




/*
 * CFreeloaderFrame::FInit
 *
 * Purpose:
 *  Call CoInitialize then calling down into the base class
 *  initialization.
 *
 * Parameters:
 *  pFI             PFRAMEINIT containing initialization
 *                  parameters.
 *
 * Return Value:
 *  BOOL            TRUE if initialization succeeded,
 *                  FALSE otherwise.
 */

BOOL CFreeloaderFrame::FInit(PFRAMEINIT pFI)
    {
    CHECKVER_OLE;

    if (FAILED(OleInitialize(NULL)))
        return FALSE;

    m_fInitialized=TRUE;

    return CFrame::Init(pFI);
    }





/*
 * CFreeloaderFrame::CreateCClient
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

PCClient CFreeloaderFrame::CreateCClient(void)
    {
    return (PCClient)(new CFreeloaderClient(m_hInst, this));
    }





/*
 * CFreeloaderFrame::OnCommand
 *
 * Purpose:
 *  WM_COMMAND handler for the Cosmo frame window that just
 *  processes the line menu and the color menu leaving the
 *  CFrame to do everything else.
 *
 * Parameters:
 *  hWnd            HWND of the frame window.
 *  wParam          WPARAM of the message.
 *  lParam          LPARAM of the message.
 *
 * Return Value:
 *  LRESULT         Return value for the message.
 */

LRESULT CFreeloaderFrame::OnCommand(HWND hWnd, WPARAM wParam
    , LPARAM lParam)
    {
    PCFreeloaderDoc     pDoc;

    COMMANDPARAMS(wID, wCode, hWndMsg);

    /*
     * Don't bother with anything during first initialization,
     * skipping many toolbar notifications.
     */
    if (m_fInit)
        return 0L;

    switch (wID)
        {
        case IDM_EDITSIZETOGRAPHIC:
            pDoc=(PCFreeloaderDoc)m_pCL->ActiveDocument();

            if (NULL!=pDoc)
                pDoc->SizeToGraphic(FALSE);
            break;

        default:
           CFrame::OnCommand(hWnd, wParam, lParam);
        }

    return 0L;
    }





/*
 * CFreeloaderFrame::UpdateMenus
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

void CFreeloaderFrame::UpdateMenus(HMENU hMenu, UINT iMenu)
    {
    //Edit menu:  check if the document can size to the graphic
    if (m_phMenu[1]==hMenu)
        {
        PCFreeloaderDoc pDoc;
        BOOL            fEnable=FALSE;

        pDoc=(PCFreeloaderDoc)m_pCL->ActiveDocument();

        if (NULL!=pDoc)
            fEnable=pDoc->SizeToGraphic(TRUE);

        EnableMenuItem(hMenu, IDM_EDITSIZETOGRAPHIC, MF_BYCOMMAND
            | ((fEnable) ? MF_ENABLED : MF_DISABLED | MF_GRAYED));
        }

    CFrame::UpdateMenus(hMenu, iMenu);
    return;
    }
