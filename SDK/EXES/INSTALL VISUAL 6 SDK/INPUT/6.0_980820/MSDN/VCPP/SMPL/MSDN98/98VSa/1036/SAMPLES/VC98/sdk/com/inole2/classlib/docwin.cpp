/*
 * DOCWIN.CPP
 * Sample Code Class Libraries
 *
 * Window procedure for document windows.
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
 * DocumentWndProc
 *
 * Purpose:
 *  Document window class that contains a polyline but does not own
 *  things like the gizmobar.
 *
 *  We handle all commands from menus and gizmobars as well as
 *  notifications from the polyline itself.  The frame window
 *  just makes sure that commands and such are dispatched here
 *  as necessary, especially in an MDI case.
 */

LRESULT APIENTRY DocumentWndProc(HWND hWnd, UINT iMsg
    , WPARAM wParam, LPARAM lParam)
    {
    PCDocument      pDoc;
    BOOL            fOK=FALSE;
    LPARAM          lTemp;
    LRESULT         lRet;

    pDoc=(PCDocument)GetWindowLong(hWnd, DOCWL_STRUCTURE);

    if (NULL!=pDoc)
        {
        //Call the hook and return its value if it tells us to.
        if (pDoc->FMessageHook(hWnd, iMsg, wParam, lParam, &lRet))
            return lRet;
        }


    switch (iMsg)
        {
        case WM_CREATE:
            /*
             * Save our object pointer with this window.  We have to
             * do this inside this message since we don't get the
             * MDICREATESTRUCT anywhere else.
             */

            lTemp=(LPARAM)((LPCREATESTRUCT)lParam)->lpCreateParams;
            pDoc=(PCDocument)(((LPMDICREATESTRUCT)lTemp)->lParam);
            SetWindowLong(hWnd, DOCWL_STRUCTURE, (LONG)pDoc);
            break;


        case WM_CLOSE:
            //Tell our main window to close us
            if (NULL!=pDoc->m_pAdv)
                pDoc->m_pAdv->OnCloseRequest(pDoc);

            break;


        case WM_QUERYENDSESSION:
            return TRUE;    //Right now we can always close.


        case DOCM_PDOCUMENT:
            //Return our object pointer
            return (LONG)pDoc;

        case WM_MDIACTIVATE:
            /*
             * NEWMDIACTIVE isolates wParam/lParam differences
             * between Win16 and Win32.
             */
            if (0!=NEWMDIACTIVE && NULL!=pDoc->m_pAdv)
                pDoc->m_pAdv->OnActivate(pDoc);

            break;

        case WM_MENUSELECT:
            {
            PCStatusLine    pSL;

            pSL=pDoc->m_pFR->StatusLine();

            if (NULL!=pSL)
                pSL->MenuSelect(wParam, lParam);

            }
            break;

        default:
            return DEFDOCUMENTPROC(hWnd, iMsg, wParam, lParam);
        }

    return 0L;
    }
