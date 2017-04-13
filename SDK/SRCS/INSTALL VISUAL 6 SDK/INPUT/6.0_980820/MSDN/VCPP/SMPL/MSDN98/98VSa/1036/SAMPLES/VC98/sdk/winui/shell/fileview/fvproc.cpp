//THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
//ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
//THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//
// Copyright  1994-1996  Microsoft Corporation.  All Rights Reserved.
//
//	PROGRAM:FVPROC.CPP		
//
//	PURPOSE:  Window procedures for main window and About box of the
// sample FileViewer for text files.
//
//	PLATFORMS:	Windows 95
//
//	SPECIAL INSTRUCTIONS: N/A
//
//Always include the master FileViewer source include file here.
#include "fileview.h"

//
//   FUNCTION: 	 FileViewerFrameProc
//
//   PURPOSE:  Standard window procedure for the text file viewer frame window.
//  Processes menu commands, acclerators, and handles resizing of
//  the window  
//
long WINAPI FileViewerFrameProc(HWND hWnd, UINT iMsg, WPARAM wParam
    , LPARAM lParam)
    {
    LONG            lRet;
    PCFileViewer    pObj;
    LPTOOLTIPTEXT   pTTT;

    //This is invalid until WM_NCCREATE is called.
    pObj=(PCFileViewer)GetWindowLong(hWnd, FVWL_OBJECTPOINTER);

    switch (iMsg)
        {
        case WM_NCCREATE:
            //Save the the CFileViewer object pointer we're passed
            lRet=(LONG)((LPCREATESTRUCT)lParam)->lpCreateParams;
            SetWindowLong(hWnd, FVWL_OBJECTPOINTER, lRet);
            return DefWindowProc(hWnd, iMsg, wParam, lParam);

        case WM_COMMAND:
            pObj->OnCommand(LOWORD(wParam), HIWORD(wParam), (HWND)lParam);
            break;

        case WM_NOTIFY:
             // The toolbar, created with TBSTYLE_TOOLTIPS, will
             // send notifications for each button.  lParam will
             // be an LPTOOLTIPTEXT in such a case, but even when
             // the structure is something different it will always
             // have a hdr field of type NMHDR as the first field
             // which we use to see if it comes from the toolbar.
             // The notification we want is TTN_NEEDTEXT.
            pTTT=(LPTOOLTIPTEXT)lParam;

            if (NULL==pTTT)
                return 0L;

            if (TTN_NEEDTEXT==pTTT->hdr.code)
                pTTT->lpszText=pObj->PszToolTip(pTTT->hdr.idFrom);

            return 0L;


        case WM_CLOSE:
            DestroyWindow(hWnd);
            break;

    case WM_DESTROY:
            if (NULL != pObj)
            {
                ODSu("FileViewerFrameProc Quit? ", pObj->m_fPostQuitMsg);
                if (pObj->m_fPostQuitMsg)
                    PostQuitMessage(0);
                pObj->m_fPostQuitMsg = TRUE;    // One shot that it did not...

                if (pObj->m_hWnd == hWnd)
                    pObj->m_hWnd = NULL;        // Don't try to destory this again...
            }
            break;

        case WM_SIZE:
            //Resize frame tools and viewport
            pObj->ChildrenResize();
            break;

        case WM_MENUSELECT:
            //Win32 Parameters are wItem, wFlags, and hMenu
            pObj->m_pSH->MenuSelect(LOWORD(wParam)
                , HIWORD(wParam), (HMENU)lParam);
            break;

        case WM_DROPFILES:
            // We have a new file dropped on us so we need to pass this
            // information back to the caller of the viewer...
            pObj->DropFiles((HDROP)wParam);
            break;

        default:
            return DefWindowProc(hWnd, iMsg, wParam, lParam);
        }

    return 0L;
    }
//
//   FUNCTION:  ViewportWndProc	
//
//   PURPOSE: Window procedure for the viewport window.  The viewport in
//  this example just does draws the text into itself using an
//  edit control.  
//
//   COMMENTS:
//   This will need to be modified for your file viewer.
//
long WINAPI ViewportWndProc(HWND hWnd, UINT iMsg, WPARAM wParam
    , LPARAM lParam)
    {
    LONG            lRet;
    PCFileViewer    pObj;
    PAINTSTRUCT     ps;

    //This is invalid until WM_NCCREATE is called.
    pObj=(PCFileViewer)GetWindowLong(hWnd, VPWL_OBJECTPOINTER);

    switch (iMsg)
        {
        case WM_NCCREATE:
            //Save the the CFileViewer object pointer we're passed
            lRet=(LONG)((LPCREATESTRUCT)lParam)->lpCreateParams;
            SetWindowLong(hWnd, VPWL_OBJECTPOINTER, lRet);
            return DefWindowProc(hWnd, iMsg, wParam, lParam);

        case WM_PAINT:
            BeginPaint(hWnd, &ps);

            if (NULL!=pObj->m_hMemText)
                {
                LPSTR       psz;
                RECT        rc;
                HFONT       hFont;

                GetClientRect(hWnd, &rc);

                SetTextColor(ps.hdc, GetSysColor(COLOR_WINDOWTEXT));
                SetBkColor(ps.hdc, GetSysColor(COLOR_WINDOW));
                hFont=(HFONT)SelectObject(ps.hdc, pObj->m_hFont);

                psz=(LPSTR)GlobalLock(pObj->m_hMemText);

                 // We can use the client area rectangle here for
                 // drawing since we also use DT_NOCLIP, so we'll
                 // always draw all over the client area.
                OffsetRect(&rc, -pObj->m_xPos, -pObj->m_yPos);
                DrawText(ps.hdc, psz, -1, &rc, DT_LEFT
                    | DT_NOCLIP| DT_EXPANDTABS);

                GlobalUnlock(pObj->m_hMemText);
                SelectObject(ps.hdc, hFont);
                }
            EndPaint(hWnd, &ps);
            break;

        case WM_MOUSEMOVE:
             // If this message is already displayed, CStatusHelper
             // will just ignore this call and return very fast.
            pObj->m_pSH->MessageDisplay(ID_MSGCHOOSEOPEN);
            break;

        case WM_RBUTTONDOWN:
            {
            HMENU           hMenu, hMenuRes;
            POINT           pt;
            UINT            i, cItems;

            //Load our context menu.
            hMenuRes=LoadMenu(pObj->m_hInst
                , MAKEINTRESOURCE(IDR_MENUVIEWPORT));

            if (NULL==hMenuRes)
                break;

             // Make a copy popup menu because you cannot
             // use a resource-loaded menu with TrackPopupMenu.
            cItems=GetMenuItemCount(hMenuRes);
            hMenu=CreatePopupMenu();

            for (i=0; i < cItems; i++)
                {
                char    szItem[80];
                int     id, uFlags;

                GetMenuString(hMenuRes, i, szItem, sizeof(szItem)
                    , MF_BYPOSITION);
                id=GetMenuItemID(hMenuRes, i);

                uFlags=(0==id) ? MF_SEPARATOR : MF_STRING | MF_ENABLED;
                AppendMenu(hMenu, uFlags, id, szItem);
                }

            DestroyMenu(hMenuRes);

            pt.x=LOWORD(lParam);
            pt.y=HIWORD(lParam);
            ClientToScreen(hWnd, &pt);

            //Messages sent to frame window from this menu.
            TrackPopupMenu(hMenu, TPM_LEFTALIGN | TPM_RIGHTBUTTON
                , pt.x, pt.y, 0, pObj->m_hWnd, NULL);

            DestroyMenu(hMenu);
            }
            break;

        case WM_HSCROLL:
        case WM_VSCROLL:
            {
            int             iTmp;
            UINT            idScroll;
            SCROLLINFO      si;

            idScroll=(WM_HSCROLL==iMsg) ? SB_HORZ : SB_VERT;

            si.cbSize = sizeof(SCROLLINFO);
            si.fMask = SIF_PAGE | SIF_POS | SIF_RANGE;
            GetScrollInfo(hWnd, idScroll, &si);

            iTmp=si.nPos;

            switch (LOWORD(wParam))
                {
                case SB_LINEUP:     si.nPos -= 20;  break;
                case SB_PAGEUP:     si.nPos -=si.nPage;  break;
                case SB_LINEDOWN:   si.nPos += 20;  break;
                case SB_PAGEDOWN:   si.nPos +=si.nPage;  break;

                case SB_THUMBPOSITION:
                case SB_THUMBTRACK:
                    si.nPos=HIWORD(wParam);
                    break;
                }

            si.nPos=max(si.nMin, min(si.nPos, si.nMax));

            if (si.nPos!=iTmp)
                {
                //Set the new position and scroll the window
                SetScrollPos(hWnd, idScroll, si.nPos, TRUE);

                if (SB_HORZ==idScroll)
                    {
                    pObj->m_xPos=si.nPos;
                    ScrollWindow(hWnd, iTmp-si.nPos, 0, NULL, NULL);
                    }
                else
                    {
                    pObj->m_yPos=si.nPos;
                    ScrollWindow(hWnd, 0, iTmp-si.nPos, NULL, NULL);
                    }

                UpdateWindow(hWnd);
                }
            }
            break;

        default:
            return DefWindowProc(hWnd, iMsg, wParam, lParam);
        }

    return 0L;
    }
//
//   FUNCTION: 	AboutProc
//
//   PURPOSE:  Dialog procedure for the omnipresent About box. 
//
BOOL APIENTRY AboutProc(HWND hDlg, UINT iMsg, WPARAM wParam
    , LPARAM lParam)
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
                    break;
                }
            break;

        case WM_CLOSE:
            EndDialog(hDlg, FALSE);
            break;
        }
    return FALSE;
    }
