/*
 * FRAMEWIN.CPP
 * Sample Code Class Libraries
 *
 * Frame window procedure used with the CFrame class as well as
 * the implementation of CDocumentAdviseSink that the frame is
 * interested in.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include <windows.h>
#include "classlib.h"


/*
 * FrameWndProc
 *
 * Purpose:
 *  Frame window class procedure that allows a derivation of these
 *  classes to hook and process any messages desired.  Otherwise this
 *  handles standard commands as well as the status line and menus.
 */

LRESULT APIENTRY FrameWndProc(HWND hWnd, UINT iMsg
    , WPARAM wParam, LPARAM lParam)
    {
    PCFrame         pFR;
    PCClient        pCL=NULL;
    WORD            dx, dy;
    LRESULT         lRet;

    pFR=(PCFrame)GetWindowLong(hWnd, FRAMEWL_STRUCTURE);

    if (NULL!=pFR)
        {
        //Call the hook and return its value if it tells us to.
        if (pFR->FMessageHook(hWnd, iMsg, wParam, lParam, &lRet))
            return lRet;

        //Otherwise copy the CClient pointer and continue.
        pCL=pFR->m_pCL;
        }

    switch (iMsg)
        {
        case WM_NCCREATE:
            pFR=(PCFrame)((LPCREATESTRUCT)lParam)->lpCreateParams;

            SetWindowLong(hWnd, FRAMEWL_STRUCTURE, (LONG)pFR);
            return DefWindowProc(hWnd, iMsg, wParam, lParam);

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        case WM_CLOSE:
            //Don't close if any children cancel the operation.
            pFR->m_fClosing=TRUE;

            if (!pCL->QueryCloseAllDocuments(TRUE, TRUE))
                {
                pFR->m_fClosing=FALSE;
                break;
                }

            //Destroy everything.
            DestroyWindow(hWnd);
            break;


        case WM_QUERYENDSESSION:
            return pCL->QueryCloseAllDocuments(TRUE, TRUE);


        case WM_ERASEBKGND:
            //Our client area is never visible, so don't flash
            return TRUE;


        case WM_SIZE:
            pFR->m_fSizing=TRUE;
            dx=LOWORD(lParam);
            dy=HIWORD(lParam);

            //Change the gizmobar and StatStrip widths to match
            pFR->m_pTB->OnSize(hWnd);
            pFR->m_pSL->OnSize(hWnd);

            pCL->OnSize(0, pFR->m_cyBar, dx
                , dy-pFR->m_cyBar-CYSTATSTRIP);

            pFR->m_fSizing=FALSE;
            break;


        case WM_INITMENUPOPUP:
            //Skip the system menu
            if (TRUE==(BOOL)HIWORD(lParam))
                break;

            //Go handle graying menu items appropriately.
            pFR->UpdateMenus((HMENU)wParam, (UINT)LOWORD(lParam));
            break;


        case WM_MENUSELECT:
            pFR->m_pSL->MenuSelect(wParam, lParam);
            break;


        case WM_DESTROYCLIPBOARD:
            //When we empty contents, disable the paste button
            pFR->m_pTB->Enable(IDM_EDITPASTE, FALSE);
            break;


        case WM_COMMAND:
            return pFR->OnCommand(hWnd, wParam, lParam);


        default:
            //Don't try using CClient unless we have one.
            if (NULL!=pCL)
                {
                return pCL->DefaultFrameProc(hWnd, iMsg, wParam
                    , lParam);
                }
            else
                return DefWindowProc(hWnd, iMsg, wParam, lParam);
        }

    return 0L;
    }






/*
 * AboutProc
 *
 * Purpose:
 *  Dialog procedure for the omnipresent About box.
 *
 * Parameters:
 *  The standard.
 *
 * Return Value:
 *  The value to be returned through the DialogBox call that
 *  created the dialog.
 *
 */

BOOL APIENTRY AboutProc(HWND hDlg, UINT iMsg
    , WPARAM wParam, LPARAM lParam)
    {
    switch (iMsg)
        {
        case WM_INITDIALOG:
            return TRUE;

        case WM_COMMAND:
            switch (LOWORD(wParam))
                {
                case IDOK:
                    EndDialog(hDlg, TRUE);
                }
            break;
        }
    return FALSE;
    }





//CDocumentAdviseSink implementation for the frame window.



/*
 * CDocumentAdviseSink::CDocumentAdviseSink
 *
 * Purpose:
 *  Constructs an advise object storing a pointer for the caller's
 *  use.
 *
 * Parameters:
 *  pv              LPVOID to store in this object
 */

CDocumentAdviseSink::CDocumentAdviseSink(LPVOID pv)
    {
    m_pv=pv;
    return;
    }




/*
 * CDocumentAdviseSink::OnDataChange
 *
 * Purpose:
 *  Informs the frame that document data changed so we may need to
 *  update some of our UI.
 *
 * Parameters:
 *  pDoc            PCDocument notifying us.
 *
 * Return Value:
 *  None
 */

void CDocumentAdviseSink::OnDataChange(PCDocument pDoc)
    {
    PCFrame     pFR=(PCFrame)m_pv;

    pFR->OnDocumentDataChange(pDoc);
    return;
    }








/*
 * CDocumentAdviseSink::OnCloseRequest
 *
 * Purpose:
 *  A document was closed by the user so we have to effect it here.
 *
 * Parameters:
 *  pDoc            PCDocument notifying us.
 *
 * Return Value:
 *  None
 */

void CDocumentAdviseSink::OnCloseRequest(PCDocument pDoc)
    {
    PCFrame     pFR=(PCFrame)m_pv;

    //Ask if you want to save.
    if (!pFR->m_pCL->FCleanVerify(pDoc))
        return;

    pFR->m_pCL->CloseDocument(pDoc);
    pFR->UpdateToolbar();

    return;
    }






/*
 * CDocumentAdviseSink::OnSizeChange
 *
 * Purpose:
 *  Notifies us that the document was resized.
 *
 * Parameters:
 *  pDoc            PCDocument notifying us.
 *  pRect           LPRECT of the new document window size.
 *
 * Return Value:
 *  None
 */

void CDocumentAdviseSink::OnSizeChange(PCDocument pDoc, LPRECT pRect)
    {
    PCFrame     pFR=(PCFrame)m_pv;
   #ifndef MDI
    RECT        rc;
    DWORD       dwStyle;
   #endif

    //MDI, do nothing.  In SDI, resize the frame to match
   #ifdef MDI
    return;
   #else
    //If we caused this from our own WM_SIZE, skip out.
    if (pFR->m_fSizing)
        return;

    //Get the document's screen rectangle.
    GetWindowRect(pDoc->Window(), &rc);

    //Adjust for GizmoBar
    rc.top-=pFR->m_cyBar;

    //Adjust for StatStrip
    rc.bottom+=CYSTATSTRIP;

    //Adjust for our window
    dwStyle=GetWindowLong(pFR->m_hWnd, GWL_STYLE);
    AdjustWindowRect(&rc, dwStyle, TRUE);

    //This causes sizing of all other tools.
    SetWindowPos(pFR->m_hWnd, NULL, rc.left, rc.top, rc.right-rc.left
        , rc.bottom-rc.top, SWP_NOZORDER | SWP_NOACTIVATE);

    return;
   #endif
    }




/*
 * CDocumentAdviseSink::OnCaptionChange
 *
 * Purpose:
 *  Notifies us that we should update the caption bars used on this
 *  document.
 *
 * Parameters:
 *  pDoc            PCDocument notifying us.
 *
 * Return Value:
 *  None
 */

void CDocumentAdviseSink::OnCaptionChange(PCDocument pDoc)
    {
    PCFrame     pFR=(PCFrame)m_pv;

   #ifdef MDI
    pFR->WindowTitleSet(pDoc, TRUE);
   #else
    pFR->WindowTitleSet(pDoc, FALSE);
   #endif

    return;
    }





/*
 * CDocumentAdviseSink::OnActivate
 *
 * Purpose:
 *  Notifies us that we should update any user interface that
 *  depends on the active document.
 *
 * Parameters:
 *  pDoc            PCDocument notifying us.
 *
 * Return Value:
 *  None
 */

void CDocumentAdviseSink::OnActivate(PCDocument pDoc)
    {
    PCFrame     pFR=(PCFrame)m_pv;

    pFR->OnDocumentActivate(pDoc);
    return;
    }
