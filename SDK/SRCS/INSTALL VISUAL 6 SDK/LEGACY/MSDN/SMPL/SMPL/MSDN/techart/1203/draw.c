/*
    draw.c

    Drawing routines

    If SHOWCLIP is defined then it will draw rectangles around regions 
    drawn on the off-screen DC in one color and regions draw to the main
    window in another color to show what's going on.

*/

#include "global.h"

#define CYAN RGB(0,255,255)
#define MAGENTA RGB(255,0,255)

//
// local data
//

static DRAWRECTLIST DrawList;

//
// local functions
//

static void DrawRect(HDC hDC, int x1, int y1, int x2, int y2, COLORREF col);




//
// Render a DIB to the off-screen DC
// Note that because the off-screen DC belongs to the DIB driver
// which is *not* a palettized device, we do not select/realize
// any palette.  If this routine were altered to render the DIB to
// an arbitrary DC then code would be needed to select/realize the
// palette before calling StretchDIBits and unselect it after the call.
// You must use DIB_RGB_COLORS here as the DIB driver (being a 
// non-paletized device) can't handle DIB_PAL_COLORS and GDI will try
// to be helpful and map them to some random RGB values.
//
// This routine was replaced by RenderDIBBitsOffScreen but is left
// here as an example of how StretchDIbits could be used
//

void RenderDIBOffScreen(PDIB pDIB, int iX, int iY, LPRECT prcClip)
{
    DWORD dwTicks;
    int xs, ys, xd, yd, w, h;

    DBGSET(0x08);

    dprintf4("RenderDIB()");
    dwTicks = timeGetTime();

    if (!hdcOffScreen) return;

    w = DIB_WIDTH(pDIB);
    xd = iX;
    xs = 0;
    if (prcClip) {
        if (prcClip->left > iX) {
            xd += prcClip->left - iX;
            xs += prcClip->left - iX;
            w -= prcClip->left - iX;
        }
        if (xd+w > prcClip->right) {
            w -= xd+w - prcClip->right;    
        }
    }

    h = DIB_HEIGHT(pDIB);
    yd = iY;
    ys = 0;
    if (prcClip) {
        if (prcClip->top > iY) {
            yd += prcClip->top - iY;
            h -= prcClip->top - iY;
        }
        if (iY+h > prcClip->bottom) {
            ys = iY+h - prcClip->bottom;
            h -= iY+h - prcClip->bottom;
        }
    }

    ASSERT(DIB_PBITS(pDIB));

    StretchDIBits(hdcOffScreen,
                xd,                     // dest x
                yd,                     // dest y
                w,                      // dest width
                h,                      // dest height
                xs,                     // src x
                ys,                     // src y
                w,                      // src width
                h,                      // src height
                DIB_PBITS(pDIB),        // bits
                DIB_PBI(pDIB),          // BITMAPINFO
                DIB_RGB_COLORS,
                SRCCOPY);               // rop

    if (bShowUpdateRects && prcClip) {
        DrawRect(hdcOffScreen, xd+1, yd+1, xd+w-2, yd+h-2, CYAN);
    }

    dprintf4("DIB render took %lu ms", timeGetTime() - dwTicks);

    DBGCLEAR(0x08);
}

//
// Render a DIB to the off-screen DC by just copying its bits.
// Note that the DIB and the off-screen DIb must be the same format
// (we only do 8 bpp) and *must* be using the same color table since
// no mapping will be done
//

void RenderDIBBitsOffScreen(PDIB pDIB, int x, int y, LPRECT prcClip,
                            BYTE bTranClr, BOOL bTrans)
{
    RECT rcDraw, rcDIB;
    HPBYTE pStartS;
    HPBYTE pStartD;
    long lScanS, lScanD;

    DBGSET(0x08);

    //
    // Intersect the clip rect with the off-screen DIB to make
    // sure we don't try to draw to any invalid coords
    //

    rcDraw.top = rcDraw.left = 0;
    rcDraw.right = DIB_WIDTH(pdibOffScreen) - 1;
    rcDraw.bottom = DIB_HEIGHT(pdibOffScreen) - 1;

    if (prcClip) {
        if (!IntersectRect(&rcDraw, &rcDraw, prcClip)) return;
    }

    //
    // Intersect the clip rect with the DIB rect
    //

    rcDIB.left = x;
    rcDIB.right = x + DIB_WIDTH(pDIB) - 1;
    rcDIB.top = y;
    rcDIB.bottom = y + DIB_HEIGHT(pDIB) - 1;

    if (!IntersectRect(&rcDraw, &rcDraw, &rcDIB)) return;

    //
    // We have a sprite which is at least partially visible in
    // the clip rect
    // Calculate the address of the first pixel of the bottom 
    // scan line
    //

    pStartS = GetDIBPixelAddress(pDIB,
                                 rcDraw.left - x,
                                 rcDraw.bottom - y);
    ASSERT(pStartS);

    //
    // Calculate the address of the off-screen DIB
    //

    pStartD = GetDIBPixelAddress(pdibOffScreen,
                                 rcDraw.left,
                                 rcDraw.bottom);


    //
    // Calculate the scan line width of the DIBs
    //

    lScanS = DIB_STORAGEWIDTH(pDIB);
    lScanD = DIB_STORAGEWIDTH(pdibOffScreen);

    if (!bTrans) {

        //
        // Copy the bits without transparency
        //

        CopyDIBBits(pStartD, 
                    pStartS, 
                    rcDraw.right - rcDraw.left + 1,
                    rcDraw.bottom - rcDraw.top + 1,
                    lScanD,
                    lScanS);

    } else {

        TransCopyDIBBits(pStartD, 
                         pStartS, 
                         rcDraw.right - rcDraw.left + 1,
                         rcDraw.bottom - rcDraw.top + 1,
                         lScanD,
                         lScanS,
                         bTranClr);

    }


    if (bShowUpdateRects) {
        DrawRect(hdcOffScreen, 
                 rcDraw.left+1,
                 rcDraw.top+1,
                 rcDraw.right-2,
                 rcDraw.bottom-2,
                 CYAN);
    }

    DBGCLEAR(0x08);
}

//
// Render a sprite to a DC
//

void RenderSpriteOffScreen(PSPRITE pSprite, LPRECT prcClip)
{
    RECT rc;

    if (!hdcOffScreen) return;

    DBGSET(0x04);
    dprintf4("RenderSprite()");

    //
    // See if the sprite rect is visible in the clip rect
    //

    if (prcClip) {
        GetSpriteRect(pSprite, &rc);
        if (!IntersectRect(&rc, &rc, prcClip)) {
            return;
        }
    }

#ifdef USESTRETCHDIBITS // old slow way

    SetBkColor(hdcOffScreen, pSprite->rgbTopLeft);
    SetBkMode(hdcOffScreen, NEWTRANSPARENT);

    RenderDIBOffScreen(pSprite->pDIB,
                       pSprite->x,
                       pSprite->y,
                       prcClip);
              
    SetBkMode(hdcOffScreen, OPAQUE);

#else // doing our own bit copy - faster

    RenderDIBBitsOffScreen(pSprite->pDIB,
                           pSprite->x,
                           pSprite->y,
                           prcClip,
                           pSprite->bTopLeft,
                           TRUE); // transparent

#endif

    DBGCLEAR(0x04);
}

//
// Process WM_PAINT messages for the main window
// We simply copy the clip rectangle from the off-screen DC
// to the window DC by calling StretchDIBits.  We use the
// DIB_PAL_COLORS option to avoid a color match and use the
// 1:1 color table so that the index values stay the same.
//

void Paint(HDC hDC, LPRECT prcClip)
{
    int w, h, xs, ys, xd, yd;
    HPALETTE hOldPal;
    DWORD dwStart, dwReal;

    DBGSET(0x10);
    if (prcClip) {
        dprintf2("Paint(%d,%d,%d,%d)",
                 prcClip->left,
                 prcClip->top,
                 prcClip->right,
                 prcClip->bottom);
    } else {
        dprintf2("Paint(NULL)");
    }

    if (!hdcOffScreen) {
        dprintf1("No off-screen DC to paint from");
        return;
    }

    dwStart = timeGetTime();

    //
    // Copy the update rectangle from the off-screen DC
    // to the window DC. Note that DIB origin is lower left
    // corner.
    //

    if (prcClip) {
        w = prcClip->right - prcClip->left;
        h = prcClip->bottom - prcClip->top;
        xs = xd = prcClip->left;
        yd = prcClip->top;
        ys = DIB_HEIGHT(pdibOffScreen) - prcClip->bottom;
    } else {

        w = DIB_WIDTH(pdibOffScreen);
        h = DIB_HEIGHT(pdibOffScreen);
        xs = xd = ys = yd = 0;
    }


    if (hpalCurrent) {
        hOldPal = SelectPalette(hDC, hpalCurrent, 0);
        RealizePalette(hDC);
    }
    dwReal = timeGetTime();
    dprintf4(" Palette sel/real took %lu ms.", dwReal - dwStart);

    ASSERT(pPalClrTable);
    StretchDIBits(hDC,              // dest dc
                xd,                 // dest x
                yd,                 // dest y
                w,                  // dest width
                h,                  // dest height
                xs,                 // src x
                ys,                 // src y
                w,                  // src width
                h,                  // src height
                DIB_PBITS(pdibOffScreen), // bits
                pPalClrTable,       // BITMAPINFO
                DIB_PAL_COLORS,     // options
                SRCCOPY);           // rop

    dprintf4(" StretchDIBits took %lu ms", timeGetTime() - dwReal);

    if (bShowUpdateRects) {
        DrawRect(hDC, xd, yd, xd+w, yd+h, MAGENTA);
    }

    if (hOldPal) SelectPalette(hDC, hOldPal, 0);

    DBGCLEAR(0x10);
}

//
// Draw a rectangle border of a given color
//

static void DrawRect(HDC hDC, int x1, int y1, int x2, int y2, COLORREF col)
{
    HPEN hpenCol, hpenOld;
    HBRUSH hbrOld;

    dprintf3("DrawRect(%d,%d,%d,%d)", x1, y1, x2, y2);

    hpenCol = CreatePen(PS_SOLID, 2, col);
    hpenOld = SelectObject(hDC, hpenCol);
    hbrOld = SelectObject(hDC, GetStockObject(NULL_BRUSH));
    Rectangle(hDC, x1, y1, x2, y2);
    SelectObject(hDC, hpenOld);
    SelectObject(hDC, hbrOld);
    DeleteObject(hpenCol);
}

//
// Update sprite positions (just for silly effect)
//

void UpdatePositions()
{
    static DWORD dwLast, dwNow;

    PSPRITE pSprite;
    BOOL bChanged = FALSE;
    RECT rcPos;

    DBGSET(0x01);

    if (dwLast) {
        dwNow = timeGetTime();
        dprintf4("Update interval: %lu ms", dwNow-dwLast);
        dwLast = dwNow;
    } else {
        dwLast = timeGetTime();
    }

    pSprite = pSpriteList;
    while (pSprite) {

        if (pSprite->vx || pSprite->vy) {

            GetSpriteRect(pSprite, &rcPos);
            Redraw(&rcPos, NO_UPDATE);

            pSprite->x += pSprite->vx;
            if ((pSprite->vx < 0) && (pSprite->x + pSprite->width < 0)) {
                pSprite->x = DIB_WIDTH(pdibBkGnd);
            } else if ((pSprite->vx > 0) && (pSprite->x > DIB_WIDTH(pdibBkGnd))) {
                pSprite->x = - (int)pSprite->width;
            }

            pSprite->y += pSprite->vy;
            if ((pSprite->vy < 0) && (pSprite->y + pSprite->height < 0)) {
                pSprite->y = DIB_HEIGHT(pdibBkGnd);
            } else if ((pSprite->vy > 0) && (pSprite->y > DIB_HEIGHT(pdibBkGnd))) {
                pSprite->y = - (int) pSprite->height;
            }

            GetSpriteRect(pSprite, &rcPos);
            Redraw(&rcPos, NO_UPDATE);

            bChanged = TRUE;
        }

        pSprite = pSprite->pNext;
    }

    if (bChanged) {
        Redraw(&rcPos, UPDATE_SCREEN); // ask for the last one again
    }
    DBGCLEAR(0x01);
}

//
// Fill the off screen DIB with a set pattern (for palette testing)
//

void FillBkGnd()
{
    int x, y, i, j, w, h;
    BYTE color;
    HPSTR hpBits;

    dprintf2("FillBkGnd()");

    if (!pdibOffScreen) {
        dprintf1("No os DIB");
        return;
    }

    w = DIB_WIDTH(pdibOffScreen);
    h = DIB_HEIGHT(pdibOffScreen);

    dprintf3(" %u x %u. Addr: %8.8lXH", w, h, DIB_PBITS(pdibOffScreen));

    ASSERT(w);
    ASSERT(h);

    hpBits = (HPSTR) DIB_PBITS(pdibOffScreen);
    for (y=0; y<h; y++) {
        j = 15 - (y * 16 / h);

        for (x=0; x<w; x++) {
            i = x * 16 / w;

            color = (BYTE) (j * 16 + i);

            *hpBits++ = color;

        }
    }

    //
    // Force a redraw
    //

    InvalidateRect(hwndMain, NULL, FALSE);

}

//
// Render the background and sprite set and repaint the window
// if required.
// If the NO_UPDATE option is requested, the clip rectangle
// is added to the redraw list.  When an update is requested,
// the redraw list is merged and all the rectangles in it
// redrawn.  The list is reset to empty.
//

void Redraw(LPRECT prcClip, BOOL bUpdate)
{
    PSPRITE pSprite, pLastSprite;
    HDC hDC;
    PDRAWRECT pDrawRect;
    RECT rcAll;

    DBGSET(0x02);

    //
    // add the rectangle to the list
    //

    if (prcClip) {
        AddDrawRectItem(&DrawList, prcClip);
    } else {

        //
        // if we have a background defined,
        // add a rectangle to cover it
        //

        if (pdibBkGnd) {
            rcAll.left = rcAll.top = 0;
            rcAll.right = DIB_WIDTH(pdibBkGnd);
            rcAll.bottom = DIB_HEIGHT(pdibBkGnd);
            AddDrawRectItem(&DrawList, &rcAll);
        }

    }

    //
    // If no update is requested, that's all there is
    //

    if (bUpdate == NO_UPDATE) return;

    //
    // make sure there is a background dib and dc
    //

    if (!pdibBkGnd || !hdcOffScreen) return;

    //
    // Merge the draw rect list and walk it doing redraws
    //

    MergeDrawRectList(&DrawList);

    //
    // Find the end of the sprite list
    //

    pLastSprite = pSpriteList;
    if (pLastSprite) {
        while (pLastSprite->pNext) pLastSprite = pLastSprite->pNext;
    }

    if (bUpdate == UPDATE_SCREEN) {
        hDC = GetDC(hwndMain);
    }

    //
    // walk the draw rect list
    //

    pDrawRect = DrawList.pHead;

    while (pDrawRect) {

        //
        // Render the background DIB to the off-screen DC
        //
    
#ifdef USESTRETCHDIBITS // old way

        RenderDIBOffScreen(pdibBkGnd, 0, 0, &(pDrawRect->rc));

#else // do our own faster thing

        RenderDIBBitsOffScreen(pdibBkGnd, 
                               0, 0, 
                               &(pDrawRect->rc),
                               0,
                               FALSE);
#endif
    
        //
        // Draw the sprites
        // Walk the list from the bottom (back) to the top (front)
        //

        pSprite = pLastSprite;
        while (pSprite) {
            RenderSpriteOffScreen(pSprite, &(pDrawRect->rc));
            pSprite = pSprite->pPrev;
        }
    
        //
        // see if we need to repaint
        //
    
        if (bUpdate == UPDATE_SCREEN) {
    
            Paint(hDC, &(pDrawRect->rc));
        }


        pDrawRect = pDrawRect->pNext;
    }

    if (bUpdate == UPDATE_SCREEN) {
        ReleaseDC(hwndMain, hDC);
    }

    //
    // empty the redraw list
    //

    EmptyDrawRectList(&DrawList);

    DBGCLEAR(0x02);
}

//
// Delete a draw rect item from a list
//

void DeleteDrawRectListItem(PDRAWRECTLIST pList, PDRAWRECT pItem)
{
    PDRAWRECT pPrev, pNext;

    pPrev = pItem->pPrev;
    pNext = pItem->pNext;

    if (pNext) {
        pNext->pPrev = pPrev;
    }

    if (pPrev) {
        pPrev->pNext = pNext;
    } else {
        pList->pHead = pNext;
    }

    LocalFree((HANDLE)(pItem));
}

//
// Empty an entire draw rect list
//

void EmptyDrawRectList(PDRAWRECTLIST pList)
{
    while (pList->pHead) DeleteDrawRectListItem(pList, pList->pHead);
}

//
// Add a rect to the top of the list
//

void AddDrawRectItem(PDRAWRECTLIST pList, LPRECT pRect)
{
    PDRAWRECT pItem;

    DBGSET(0x20);
    pItem = (PDRAWRECT) LocalAlloc(LPTR, sizeof(DRAWRECT));
    if (!pItem) {
        dprintf1("No memory for draw rect");
    } else {
        pItem->rc = *pRect;
        pItem->pNext = pList->pHead;
        pItem->pPrev = NULL;
        pList->pHead = pItem;
        if (pItem->pNext) {
            pItem->pNext->pPrev = pItem;
        }
    }
    DBGCLEAR(0x20);
}

//
// Merge together any overlapping rectangles in a list
// This isn't such a great piece of code.  If you're a link-list
// kind of guy - feel free to redo this and send me email
// telling me how cool it is now:  nigelt@microsoft.com :-)
//

void MergeDrawRectList(PDRAWRECTLIST pList)
{
    PDRAWRECT pItem1, pItem2, pNext;
    BOOL bChanged;
    RECT rcNew;

    if (!pList || !pList->pHead) return;

    DBGSET(0x40);
    do {
        bChanged = FALSE;

        pItem1 = pList->pHead;
        while (pItem1) {

            pItem2 = pItem1->pNext;
            while (pItem2) {

                if (IntersectRect(&rcNew, &(pItem1->rc), &(pItem2->rc))) {

                    UnionRect(&(pItem1->rc), &(pItem1->rc), &(pItem2->rc));
                    pNext = pItem2->pNext;
                    DeleteDrawRectListItem(pList, pItem2);
                    bChanged = TRUE;
                    break;
                }
                pItem2 = pItem2->pNext;
            }
            if (bChanged) break;
            pItem1 = pItem1->pNext;
        }
    } while (bChanged);
    DBGCLEAR(0x40);
}
