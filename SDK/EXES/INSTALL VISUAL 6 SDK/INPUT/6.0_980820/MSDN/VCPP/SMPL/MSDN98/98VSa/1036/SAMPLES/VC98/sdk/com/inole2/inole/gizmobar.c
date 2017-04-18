/*
 * GIZMOBAR.C
 *
 * Contains the main window procedure of the GizmoBar control
 * that handles mouse logic and Windows messages.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#include "inoledll.h"


//In GIZMO.C
extern TOOLDISPLAYDATA g_tdd;


/*
 * GizmoBarPAllocate
 *
 * Purpose:
 *  Allocates and initializes the control's primary data structure
 *  for each window that gets created.
 *
 * Parameters:
 *  pfSuccess       int * indicating success of the function.
 *  hWnd            HWND that is tied to this structure.
 *  hInst           HINSTANCE of the DLL.
 *  hWndAssociate   HWND to which we send messages.
 *  dwStyle         DWORD initial style.
 *  uState          UINT initial state.
 *  uID             UINT identifier for this window.
 *
 * Return Value:
 *  PGIZMOBAR       If NULL returned then GizmoBarPAllocate could not
 *                  allocate memory.  If a non-NULL pointer is
 *                  returned with *pfSuccess, then call GizmoBarPFree
 *                  immediately.  If you get a non-NULL pointer and
 *                  *pfSuccess==TRUE then the function succeeded.
 */

PGIZMOBAR GizmoBarPAllocate(int *pfSuccess, HWND hWnd
    , HINSTANCE hInst, HWND hWndAssociate, DWORD dwStyle
    , UINT uState , UINT uID)
    {
    PGIZMOBAR     pGB;

    if (NULL==pfSuccess)
        return NULL;

    *pfSuccess=FALSE;

    //Allocate the structure
    pGB=(PGIZMOBAR)(void *)LocalAlloc(LPTR, CBGIZMOBAR);

    if (NULL==pGB)
        return NULL;

    //Initialize LibMain parameter holders.
    pGB->hWnd         =hWnd;
    pGB->hInst        =hInst;
    pGB->hWndAssociate=hWndAssociate;
    pGB->dwStyle      =dwStyle;
    pGB->uState       =uState;
    pGB->uID          =uID;
    pGB->fEnabled     =TRUE;

    pGB->crFace=GetSysColor(COLOR_BTNFACE);
    pGB->hBrFace=CreateSolidBrush(pGB->crFace);

    if (NULL==pGB->hBrFace)
        return pGB;

    pGB->hFont=GetStockObject(SYSTEM_FONT);

    *pfSuccess=TRUE;
    return pGB;
    }




/*
 * GizmoBarPFree
 *
 * Purpose:
 *  Reverses all initialization done by GizmoBarPAllocate, cleaning
 *  up any allocations including the application structure itself.
 *
 * Parameters:
 *  pGB             PGIZMOBAR to the control's structure
 *
 * Return Value:
 *  PGIZMOBAR       NULL if successful, pGB if not, meaning we
 *                  couldn't free some allocation.
 */

PGIZMOBAR GizmoBarPFree(PGIZMOBAR pGB)
    {
    if (NULL==pGB)
        return NULL;

    /*
     * Free all the gizmos we own.  When we call GizmoPFree we always
     * free the first one in the list which updates pGB->pGizmos for
     * us, so we just have to keep going until pGizmos is NULL,
     * meaning we're at the end of the list.
     */
    while (NULL!=pGB->pGizmos)
        GizmoPFree(&pGB->pGizmos, pGB->pGizmos);

    if (NULL!=pGB->hBrFace)
        DeleteObject(pGB->hBrFace);

    /*
     * Notice that since we never create a font, we aren't
     * responsible for our hFont member.
     */

    return (PGIZMOBAR)(void *)LocalFree((HLOCAL)(UINT)(LONG)pGB);
    }








/*
 * GizmoBarWndProc
 *
 * Purpose:
 *  Window Procedure for the GizmoBar custom control.  Handles all
 *  messages like WM_PAINT just as a normal application window would.
 *  Any message not processed here should go to DefWindowProc.
 *
 * Parameters:
 *  Standard
 *
 * Return Value:
 *  Standard
 */

LRESULT WINAPI GizmoBarWndProc(HWND hWnd, UINT iMsg
    , WPARAM wParam, LPARAM lParam)
    {
    BOOL            fSuccess;
    BOOL            fTemp;
    LPCREATESTRUCT  pCreate;
    PGIZMOBAR       pGB;
    PGIZMO          pGizmo;
    RECT            rc;
    POINT           pt;
    short           x, y;
    COLORREF        cr;

    COMMANDPARAMS(wID, wCode, hWndMsg);

    pGB=(PGIZMOBAR)GetWindowLong(hWnd, GBWL_STRUCTURE);

    //Pass control messages onto another function for processing.
    if (iMsg >= WM_USER)
        return GBMessageHandler(hWnd, iMsg, wParam, lParam, pGB);

    switch (iMsg)
        {
        case WM_NCCREATE:
            pCreate=(LPCREATESTRUCT)lParam;

            pGB=GizmoBarPAllocate(&fSuccess, hWnd
                , pCreate->hInstance, pCreate->hwndParent
                , pCreate->style, 0, (UINT)pCreate->hMenu);

            if (!fSuccess)
                {
                GizmoBarPFree(pGB);
                return -1L;
                }
            else
                SetWindowLong(hWnd, GBWL_STRUCTURE, (LONG)pGB);

            return DefWindowProc(hWnd, iMsg, wParam, lParam);


        case WM_DESTROY:
            /*
             * We want to clean up before DestroyWindow nukes all the
             * children, so WM_DESTROY is a better to do it than
             * WM_NCDESTROY.
             */
            GizmoBarPFree(pGB);
            break;


        case WM_ERASEBKGND:
            /*
             * Eat this message to avoid erasing portions that
             * we are going to repaint in WM_PAINT.  Part of a
             * change-state-and-repaint strategy is to rely on
             * WM_PAINT to do anything visual, which includes
             * erasing invalid portions.  Letting WM_ERASEBKGND
             * erase the background is redundant.
             */
            return TRUE;

       #ifdef WIN32
        case WM_CTLCOLORBTN:
        case WM_CTLCOLORSTATIC:
            fTemp=TRUE;
       #else
        case WM_CTLCOLOR:
            //Change the color of static text on the GizmoBar.
            fTemp=(HIWORD(lParam)==CTLCOLOR_STATIC
                || HIWORD(lParam)==CTLCOLOR_BTN);
       #endif

            if (fTemp)
                {
                cr=GetSysColor(COLOR_BTNFACE);
                SetTextColor((HDC)wParam
                    , GetSysColor(COLOR_BTNTEXT));
                SetBkColor((HDC)wParam, cr);

                /*
                 * If the system colors have changed, then crFace
                 * will not be equal to COLOR_BTNFACE, so we
                 * reinitialize the background brush.  This scheme
                 * handles system color changes appropriately
                 * without processing WM_WININICHANGE and without
                 * blindly creating a new brush on every WM_CTLCOLOR
                 * message.
                 */
                if (cr!=pGB->crFace)
                    {
                    pGB->crFace=cr;

                    if (NULL!=pGB->hBrFace)
                        DeleteObject(pGB->hBrFace);

                    pGB->hBrFace=CreateSolidBrush(pGB->crFace);
                    }

                return (LONG)(UINT)pGB->hBrFace;
                }

            return DefWindowProc(hWnd, iMsg, wParam, lParam);


        case WM_PAINT:
            GizmoBarPaint(hWnd, pGB);
            break;


        case WM_SETFONT:
            /*
             * wParam has the new font that we now send to all other
             * windows controls in us.  We control repaints here to
             * prevent a lot of repainting for each control.
             */
            DefWindowProc(hWnd, WM_SETREDRAW, FALSE, 0L);

            if ((WPARAM)NULL!=wParam)
                {
                pGB->hFont=(HFONT)wParam;
                GizmoPEnum(&pGB->pGizmos, FEnumChangeFont
                    , (DWORD)(LPTSTR)pGB);

                DefWindowProc(hWnd, WM_SETREDRAW, TRUE, 0L);
                InvalidateRect(hWnd, NULL, FALSE);
                UpdateWindow(hWnd);
                }

            break;


        case WM_GETFONT:
            return (LRESULT)(UINT)pGB->hFont;


        case WM_ENABLE:
            /*
             * wParam has the new enable flag that we use to enable
             * or disable ALL controls in us at one time.  We also
             * turn the redraw off to prevent a lot of flicker.
             */
            DefWindowProc(hWnd, WM_SETREDRAW, FALSE, 0L);

            pGB->fEnabled=(BOOL)wParam;
            GizmoPEnum(&pGB->pGizmos, FEnumEnable
                , (DWORD)(LPTSTR)pGB);

            DefWindowProc(hWnd, WM_SETREDRAW, TRUE, 0L);
            InvalidateRect(hWnd, NULL, FALSE);
            UpdateWindow(hWnd);
            break;


        case WM_CANCELMODE:
            pGizmo=pGB->pGizmoTrack;

            pGB->fTracking=FALSE;
            pGB->fMouseOut=FALSE;

            if (NULL!=pGizmo)
                GizmoPStateSet(hWnd, pGizmo, COMMANDBUTTON_UP);

            ReleaseCapture();
            break;


        case WM_LBUTTONDBLCLK:
        case WM_LBUTTONDOWN:
            //Get the mouse coordinates.
            x=LOWORD(lParam);
            y=HIWORD(lParam);


            /*
             * See if we hit a command or attribute gizmo or not.
             * Anything else that is a control will get the message
             * instead of us anyway, so we don't have to check.
             * FEnumHitTest also validates drawn gizmos, enabled, and
             * visible, so we don't.
             */
            pGizmo=GizmoPEnum(&pGB->pGizmos, FEnumHitTest, lParam);

            if (NULL==pGizmo)
                break;          //Didn't hit one matching our needs.

            /*
             * Inform the associate that a command was hit like a
             * menu item.
             */
            if (NULL!=pGB->hWndAssociate)
                {
                if (pGizmo->fNotify)
                    {
                    SendMenuSelect(pGB->hWndAssociate, pGizmo->uID
                        , 0, 0);
                    }
                }

            /*
             * We hit a button.  If it's a command or attribute,
             * then change the state and start tracking.
             */
            pGB->fTracking=TRUE;
            pGB->pGizmoTrack=pGizmo;
            pGB->fMouseOut=FALSE;
            SetCapture(hWnd);

            pGizmo->uStateOrg=pGizmo->uState;
            GizmoPStateSet(hWnd, pGizmo, ATTRIBUTEBUTTON_MOUSEDOWN);

            break;


        case WM_MOUSEMOVE:
            POINTFROMLPARAM(pt, lParam);

            if (!pGB->fTracking)
                break;

            pGizmo=pGB->pGizmoTrack;
            SetRect(&rc, pGizmo->x, pGizmo->y, pGizmo->x+pGizmo->dx
                , pGizmo->y+pGizmo->dy);

            fTemp=pGB->fMouseOut;
            pGB->fMouseOut=!PtInRect(&rc, pt);

            //If the mouse went out, change state to the original.
            if (!fTemp && pGB->fMouseOut)
                {
                GizmoPStateSet(hWnd, pGizmo, pGizmo->uStateOrg);

                if (NULL!=pGB->hWndAssociate)
                    {
                    //Notify that we left the button
                    if (pGizmo->fNotify)
                        SendMenuSelect(pGB->hWndAssociate, 0, ~0, 0);
                    }
                }

            if (fTemp && !pGB->fMouseOut)
                {
                GizmoPStateSet(hWnd, pGizmo
                    , ATTRIBUTEBUTTON_MOUSEDOWN);

                if (NULL!=pGB->hWndAssociate)
                    {
                    //Notify that we pressed down again
                    if (pGizmo->fNotify)
                        {
                        SendMenuSelect(pGB->hWndAssociate
                            , pGizmo->uID , 0, 0);
                        }
                    }
                }

            break;


        case WM_LBUTTONUP:
            if (!pGB->fTracking)
                break;

            pGB->fTracking=FALSE;
            pGizmo=pGB->pGizmoTrack;
            ReleaseCapture();


            /*
             * Repaint if we were actually below the mouse when this
             * occurred.  For command buttons, pop the button up.
             * For attributes, either toggle the state (inclusive
             * buttons) or check the selected one (exclusive buttons)
             */

            if (!pGB->fMouseOut)
                {
                //Command buttons always come up.
                if (GIZMOTYPE_BUTTONCOMMAND==pGizmo->iType)
                    GizmoPStateSet(hWnd, pGizmo, COMMANDBUTTON_UP);

                //Attribute inclusive buttons toggle
                if (GIZMOTYPE_BUTTONATTRIBUTEIN==pGizmo->iType)
                    {
                    GizmoPCheck(hWnd, pGizmo, !(BUTTONGROUP_DOWN
                        & pGizmo->uStateOrg));
                    }

                //Attribure exclusive buttons are always checked.
                if (GIZMOTYPE_BUTTONATTRIBUTEEX==pGizmo->iType)
                    GizmoPCheck(hWnd, pGizmo, TRUE);

                //Only send messages if notify is ON.
                if (NULL!=pGB->hWndAssociate && pGizmo->fNotify)
                    {
                    SendMenuSelect(pGB->hWndAssociate, 0, ~0, 0);
                    SendCommand(pGB->hWndAssociate, pGizmo->uID
                        , BN_CLICKED, hWnd);
                    }
                }

            break;


        case WM_COMMAND:
            //Pass control messages on if the gizmo's notify is ON.
            if (NULL!=pGB->hWndAssociate)
                {
                pGizmo=PGizmoFromHwndID(hWnd, wID);

                if (NULL!=pGizmo)
                    {
                    if (pGizmo->fNotify)
                        {
                        SendMessage(pGB->hWndAssociate, iMsg, wParam
                            , lParam);
                        }
                    }
                }
            break;

        default:
            return DefWindowProc(hWnd, iMsg, wParam, lParam);
        }

    return 0L;
    }




/*
 * GizmoBarPaint
 *
 * Purpose:
 *  Handles all WM_PAINT messages for the control and paints either
 *  the entire thing or just one GizmoBar button if pGB->pGizmoPaint
 *  is non-NULL.
 *
 * Parameters:
 *  hWnd            HWND Handle to the control.
 *  pGB             PGIZMOBAR control data pointer.
 *
 * Return Value:
 *  None
 */

void GizmoBarPaint(HWND hWnd, PGIZMOBAR pGB)
    {
    RECT            rc;
    HDC             hDC;
    HBRUSH          hBr=NULL;
    HPEN            hPen=NULL;
    PAINTGIZMO      pg;

    hDC=BeginPaint(hWnd, &pg.ps);
    GetClientRect(hWnd, &rc);

    /*
     * The only part of the frame we need to draw is the bottom line,
     * so we inflate the rectangle such that all other parts are
     * outside the visible region.
     */
    hBr=CreateSolidBrush(GetSysColor(COLOR_BTNFACE));

    if (NULL!=hBr)
        SelectObject(hDC, hBr);

    hPen=CreatePen(PS_SOLID, 1, GetSysColor(COLOR_WINDOWFRAME));

    if (NULL!=hPen)
        SelectObject(hDC, hPen);

    Rectangle(hDC, rc.left-1, rc.top-1, rc.right+1, rc.bottom);


    /*
     * All that we have to do to draw the controls is start through
     * the list, ignoring anything but buttons, and calling BTTNCUR's
     * UIToolButtonDraw for buttons.  Since we don't even have to
     * track positions of things, we can just use an enum.
     */

    UIToolConfigureForDisplay(&pg.tdd);
    GizmoPEnum(&pGB->pGizmos, FEnumPaintGizmos, (DWORD)(LPTSTR)&pg);

    //Clean up
    EndPaint(hWnd, &pg.ps);

    if (NULL!=hBr)
        DeleteObject(hBr);

    if (NULL!=hPen)
        DeleteObject(hPen);

    return;
    }





/*
 * FEnumPaintGizmos
 *
 * Purpose:
 *  Enumeration callback for all the gizmos we know about in order to
 *  draw them.
 *
 * Parameters:
 *  pGizmo          PGIZMO to draw.
 *  iGizmo          UINT index on the GizmoBar of this gizmo.
 *  dw              DWORD extra data passed to GizmoPEnum, in our
 *                  case a pointer to a PAINTGIZMO structure.
 *
 * Return Value:
 *  BOOL            TRUE to continue the enumeration, FALSE
 *                  otherwise.
 */

BOOL WINAPI FEnumPaintGizmos(PGIZMO pGizmo, UINT iGizmo, DWORD dw)
    {
    PPAINTGIZMO     ppg=(PPAINTGIZMO)dw;
    RECT            rc, rcI;

    //Only draw those marked for repaint.
    if ((GIZMOTYPE_DRAWN & pGizmo->iType))
        {
        SetRect(&rc, pGizmo->x, pGizmo->y
            , pGizmo->x+pGizmo->dx, pGizmo->y+pGizmo->dy);

        //Only draw gizmos in the repaint area
        if (IntersectRect(&rcI, &rc, &ppg->ps.rcPaint))
            {
            UIToolButtonDraw(ppg->ps.hdc, pGizmo->x, pGizmo->y
                , pGizmo->dx, pGizmo->dy, pGizmo->hBmp
                , pGizmo->cxImage, pGizmo->cyImage, pGizmo->iBmp
                , (UINT)pGizmo->uState, &ppg->tdd);
            }
        }

    return TRUE;
    }





/*
 * FEnumChangeFont
 *
 * Purpose:
 *  Enumeration callback for all the gizmos we know about in order to
 *  send a new font to them that's stored in PGIZMOBAR in dw.
 *
 * Parameters:
 *  pGizmo          PGIZMO to draw.
 *  iGizmo          UINT index on the GizmoBar of this gizmo.
 *  dw              DWORD extra data passed to GizmoPEnum, in our
 *                  case the GizmoBar's pGB.
 *
 * Return Value:
 *  BOOL            TRUE to continue the enumeration, FALSE otherwise.
 */

BOOL WINAPI FEnumChangeFont(PGIZMO pGizmo, UINT iGizmo, DWORD dw)
    {
    PGIZMOBAR   pGB=(PGIZMOBAR)dw;

    //Only need to change fonts in windowed controls using WM_SETFONT
    if (NULL!=pGizmo->hWnd)
        {
        SendMessage(pGizmo->hWnd, WM_SETFONT
            , (WPARAM)pGB->hFont, 1L);
        }

    return TRUE;
    }






/*
 * FEnumEnable
 *
 * Purpose:
 *  Enumeration callback for all the gizmos we know about in order to
 *  enable or disable them from the WM_ENABLE message.
 *
 * Parameters:
 *  pGizmo          PGIZMO to draw.
 *  iGizmo          UINT index on the GizmoBar of this gizmo.
 *  dw              DWORD extra data passed to GizmoPEnum, in our
 *                  case the GizmoBar's pGB.
 *
 * Return Value:
 *  BOOL            TRUE to continue the enumeration, FALSE
 *                  otherwise.
 */

BOOL WINAPI FEnumEnable(PGIZMO pGizmo, UINT iGizmo, DWORD dw)
    {
    PGIZMOBAR   pGB=(PGIZMOBAR)dw;
    BOOL        fEnable=pGB->fEnabled;

    //NOTE:  This code is duplicated in GBGizmoEnable in API.C
    if (NULL!=pGizmo->hWnd)
        EnableWindow(pGizmo->hWnd, fEnable);
    else
        {
        //If we're not down, command and attribute buttons act same.
        if (!(BUTTONGROUP_DOWN & pGizmo->uState))
            {
            GizmoPStateSet(pGB->hWnd, pGizmo, fEnable
                ? COMMANDBUTTON_UP : COMMANDBUTTON_DISABLED);
            }
        else
            {
            /*
             * Attribute buttons are a little more sensitive
             * with DOWNDISABLED
             */
            GizmoPStateSet(pGB->hWnd, pGizmo, fEnable
                ? ATTRIBUTEBUTTON_DOWN
                : ATTRIBUTEBUTTON_DOWNDISABLED);
            }
        }

    return TRUE;
    }







/*
 * FEnumHitTest
 *
 * Purpose:
 *  Enumeration callback for all the gizmos we know about in order to
 *  hit-test them.
 *
 * Parameters:
 *  pGizmo          PGIZMO to draw.
 *  iGizmo          UINT index on the GizmoBar of this gizmo.
 *  dw              DWORD extra data passed to GizmoPEnum, in our
 *                  case the hDC on which to draw.
 *
 * Return Value:
 *  BOOL            TRUE to continue the enumeration, FALSE
 *                  otherwise.
 */

BOOL WINAPI FEnumHitTest(PGIZMO pGizmo, UINT iGizmo, DWORD dw)
    {
    RECT  rc;
    POINT pt;

    POINTFROMLPARAM(pt, dw);
	
    /*
     * Hit tests have to happen on visible, enabled, and drawn
     * controls only.
     */
    if (GIZMOTYPE_DRAWN & pGizmo->iType && !pGizmo->fHidden
        && !(BUTTONGROUP_DISABLED & pGizmo->uState))
        {
        SetRect(&rc, pGizmo->x, pGizmo->y
            , pGizmo->x+pGizmo->dx, pGizmo->y+pGizmo->dy);

        //Stop enumeration if we have a hit.
        return !PtInRect(&rc, pt);
        }

    return TRUE;
    }
