/*
 * CLIENT.CPP
 * Patron Chapter 22
 *
 * Implementation of the CPatronClient class that just makes sure
 * we get a CPatronDoc on doc creation and that we initialize fully.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "patron.h"


/*
 * CPatronClient::CPatronClient
 * CPatronClient::~CPatronClient
 *
 * Constructor Parameters:
 *  hInst           HINSTANCE of the application.
 *  pFR             PCFrame to the frame object.
 */

CPatronClient::CPatronClient(HINSTANCE hInst, PCFrame pFR)
    : CClient(hInst, pFR)
    {
    return;
    }


CPatronClient::~CPatronClient(void)
    {
    return;
    }





/*
 * CPatronClient::CreateCDocument
 *
 * Purpose:
 *  Constructs a new document specific to the application.
 *
 * Parameters:
 *  None
 *
 * Return Value:
 *  PCDocument      Pointer to the new document object.
 */

PCDocument CPatronClient::CreateCDocument(void)
    {
    return (PCDocument)(new CPatronDoc(m_hInst, m_pFR, m_pAdv));
    }



//CHAPTER22MOD
/*
 * CPatronClient::SetMenu
 *
 * Purpose:
 *  Changes the frame-level menu, isolating the rest of the
 *  application from MDI/SDI considerations.
 *
 * Parameters:
 *  hWndFrame       HWND of the frame window.
 *  hMenu           HMENU to set in the frame for the current
 *                  document.
 *  hMenuWin        HMENU of the window menu.
 *
 * Return Value:
 *  None
 */

void CPatronClient::SetMenu(HWND hWndFrame, HMENU hMenu
    , HMENU hMenuWin)
    {
   #ifdef MDI
     MDISETMENU(m_hWnd, hMenu, hMenuWin);
     MDIREFRESHMENU(m_hWnd);
   #else
    if (NULL!=hMenu)
        ::SetMenu(hWndFrame, hMenu);
   #endif

    DrawMenuBar(hWndFrame);
    return;
    }





/*
 * CPatronClient::MoveWithoutFamily
 *
 * Purpose:
 *  This specific in-place activation function applies moves the
 *  client window but to leave all child windows within it exactly
 *  where they are to keep in-place objects in the same absolute
 *  screen position.
 *
 * Parameters:
 *  prc             LPRECT containing the new space for the client
 *  dx, dy          ints specifying how much to move the client
 *
 * Return Value:
 *  None
 */

void CPatronClient::MoveWithoutFamily(LPRECT prc, int dx, int dy)
    {
    RECT        rc;
    HWND        hWndFrame;
    HWND        hWnd;
    POINT       pt;

    hWndFrame=GetParent(m_hWnd);
    SendMessage(hWndFrame, WM_SETREDRAW, FALSE, 0L);

    ShowWindow(m_hWnd, SW_HIDE);
    SetWindowPos(m_hWnd, NULL, prc->left, prc->top
        , prc->right-prc->left, prc->bottom-prc->top
        , SWP_NOZORDER | SWP_NOACTIVATE);

    //Move all children of the client
    hWnd=GetWindow(m_hWnd, GW_CHILD);

    while (NULL!=hWnd)
        {
        GetWindowRect(hWnd, &rc);
        SETPOINT(pt, rc.left, rc.top);
        ScreenToClient(m_hWnd, &pt);

        if (pt.x!=dx && pt.y!=dy && !IsZoomed(hWnd))
            {
            //Move window in the opposite direction as the client
            SetWindowPos(hWnd, NULL, pt.x-dx, pt.y-dy
                , rc.right-rc.left, rc.bottom-rc.top
                , SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOSIZE);
            }

        hWnd=GetWindow(hWnd, GW_HWNDNEXT);
        }

    SendMessage(hWndFrame, WM_SETREDRAW, TRUE, 0L);
    ShowWindow(m_hWnd, SW_SHOW);

    return;
    }



/*
 * CPatronClient::CallContextHelpOnDocuments
 *
 * Purpose:
 *  Calls IOleInPlaceUIWindow->ContextSensitiveHelp for each
 *  document window as required in an MDI container.  This does
 *  nothing in SDI.
 *
 * Parameters:
 *  fEnterMode      BOOl to pass to the documents
 *
 * Return Value:
 *  None
 */

void CPatronClient::CallContextHelpOnDocuments(BOOL fEnterMode)
    {
    LPOLEINPLACEUIWINDOW    pUIWin;
    HWND                    hWndT;
    PCPatronDoc             pDoc;

    //Loop through the documents calling their functions.
    hWndT=GetWindow(m_hWnd, GW_CHILD);

    for ( ; hWndT; hWndT=GetWindow(hWndT, GW_HWNDNEXT))
        {
        //Skip if icon title window
        if (NULL!=GetWindow(hWndT, GW_OWNER))
            continue;

        pDoc=(PCPatronDoc)SendMessage(hWndT, DOCM_PDOCUMENT
            , 0, 0L);

        if (NULL==pDoc)
            continue;

        pDoc->QueryInterface(IID_IOleInPlaceUIWindow
            , (PPVOID)&pUIWin);

        if (NULL==pUIWin)
            continue;

        pUIWin->ContextSensitiveHelp(fEnterMode);
        pUIWin->Release();
        }

    return;
    }


//End CHAPTER22MOD
