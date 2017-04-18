/******************************Module*Header*******************************\
* Module Name: bndscan.c
*
* Contains the boundary scaning functions
*
* Created: 14-Apr-1992 10:59:52
*
* Copyright (C) 1993-1997 Microsoft Corporation
*
\**************************************************************************/
#include <windows.h>
#include <stdio.h>
#include "jtypes.h"
#include "bndscan.h"

BOOL	bBoundaryScanFix(PINFO);
LPPOINT pptTrace(LONG, LONG, PINFO, INT *, HDC);
DWORD	dwGetNextBoundaryPoint(DWORD, POINT, LPPOINT, PINFO);
BOOL	bEscape(POINT, LONG, LONG, LONG, LONG, int, RECT);
BOOL	bDirToPt(DWORD, POINT, LPPOINT);
DWORD   dwShift(DWORD, int, int);

/******************************Public*Routine******************************\
*
* bBoundaryScanFix
*
* Effects:  Traces the outline of the mandelbrot set.  Currently,
*           1. Uses the old method to set the color of each pixel
*           2. Remember the first pixel from top that doesn't escape
*              st we can do boundary trace later.
*           3. When the whole set is done, do boundary trace.
*           4. Store the boundary points in an array. Then build a path.
*           5. Converts the path to region and then select the region as
*              current clip region.
*
* Warnings: Only traces the first non-singular pixel island from top.
\**************************************************************************/

BOOL bBoundaryScanFix(PINFO pInfo)
{
    DWORD       dwTick1;
    int         m, n, o, p;
    HDC         hDC;
    RECT        rc;
    LONG        c1, c2;
    LONG        x0, y0;
    int         iIteration;
    LPPOINT     lpPt;
    int 	iCount;
    POINT	Pt;
    BOOL        bFirstPtSet;

    pInfo->bMandel = TRUE;
    pInfo->bDrawing = TRUE;
    bFirstPtSet = FALSE;
    iIteration = pInfo->iIteration;
    hDC = GetDC(pInfo->hwnd);
    GetClientRect(pInfo->hwnd, &rc);

    dwTick1 = GetTickCount();
    for (n=rc.bottom/2; n<=rc.bottom; n++) {
	c2 = y0 = XformFix(n, rc.top, rc.bottom, pInfo->lyFrom, pInfo->lyTo);

        for (m=rc.left; m<=rc.right; m++) {
	    c1 = x0 = XformFix(m, rc.left, rc.right, pInfo->lxFrom, pInfo->lxTo);
	    Pt.x = m;
	    Pt.y = n;
	    if (bEscape(Pt, x0, y0, c1, c2, iIteration, rc)) {
                //SetPixel(hDC, m, n, 0x000000ff);
            } else {

                if (!bFirstPtSet)
                {
                    o = m;
                    p = n;
                    bFirstPtSet = TRUE;
                }
                goto BOUNDTRACE;
            }
        }
    }

BOUNDTRACE:

    SelectObject(hDC, hpnBlack);
    if ((lpPt = pptTrace(o, p, pInfo, &iCount, hDC)) == NULL)
    {
        m = o+1;

        for (n=p; n<=rc.bottom; n++) {
	    c2 = y0 = XformFix(n, rc.top, rc.bottom, pInfo->lyFrom, pInfo->lyTo);

            while (m <= rc.right)
            {
	        c1 = x0 = XformFix(m, rc.left, rc.right, pInfo->lxFrom, pInfo->lxTo);
	        Pt.x = m;
	        Pt.y = n;

	        if (!bEscape(Pt, x0, y0, c1, c2, iIteration, rc))
                {
                    o = m;
                    p = n;
                    goto BOUNDTRACE;
                }

                m++;
            }
            m = rc.left;
        }
    }

    if (!BeginPath(hDC)) {
        sprintf( gtext,"Failing in BeginPath!\n");
        OutputDebugString( gtext );
    }

    MoveToEx(hDC, m, n, NULL);
    Polyline(hDC, lpPt, iCount);

    if (EndPath(hDC)) {
        StrokePath(hDC);
    }

    //
    // Stroking discards the path
    //
    if (!BeginPath(hDC)) {
        sprintf( gtext,"Failing in BeginPath!\n");
        OutputDebugString( gtext );
    }

    MoveToEx(hDC, m, n, NULL);
    Polyline(hDC, lpPt, iCount);

    if (EndPath(hDC)) {
        //
        // Convert the path to region
        //
        pInfo->hRgnPath = PathToRegion(hDC);

#if 0
        //
        // Can't use SelectClipPath to set the clipping region here
        // because we are on a different thread.  This is only a cached DC.
        //
        if (SelectClipPath(hDC, RGN_COPY)) {

            // Testing if the clip region is effective or not
            //
            //MoveToEx(hDC, 0, 0, NULL);
            //GetClientRect(pInfo->hwnd, &rc);
            //LineTo(hDC, rc.right, rc.bottom);
        }
#endif
    }

    if (pInfo->hRgnPath != (HRGN) NULL) {
        //
        // let the main thread who owns the DC to set the clipping region.
        //
        SendMessage(ghwndMain, WM_COMMAND, MM_SELCLIPRGN, 0L);
    }

    pInfo->dwElapsed = GetTickCount() - dwTick1;
    pInfo->hBmpSaved = SaveBitmap(pInfo->hwnd, pInfo->hPal);
    pInfo->bDrawing = FALSE;

    ReleaseDC(pInfo->hwnd, hDC);
    //
    // GlobalAlloc was called in pptTrace for storing the boundary points
    //
    GlobalFree((HANDLE) lpPt);
    ExitThread(0);
    return TRUE;
}

/******************************Public*Routine******************************\
*
* pptTrace
*
* Effects:  Given a boundary point, traces the whole boundary of the
*           set by calling dwGetNextBoundaryPoint() repeatedly.  Returns
*           a pointer to an array of boundary points and also the count
*           of boundary points in the array, if successful.  Otherwise,
*           returns null.
*           m, n is the x, y coordinates of the pixel of the initial
*           boundary point.
*
* Warnings:
*
* History:
*  20-Feb-1992 -by- Petrus Wong
* Wrote it.
\**************************************************************************/

LPPOINT pptTrace(LONG m, LONG n, PINFO pInfo, INT * piCount, HDC hDC)
{
    DWORD        dwFace;
    LPPOINT      lpPt, lpTmpPt;
    POINT        Init;
    int          iNumPt;

    //
    // MAXPOINT points should be enough for storing the boundary for now.  If
    // it's not enough, it is more likely that it is an error.
    //
    if ((lpPt = (PPOINT) GlobalAlloc(GMEM_FIXED, MAXPOINT * sizeof(POINT))) == NULL) 
	{
        return (LPPOINT) NULL;
    }
    lpTmpPt = lpPt;
    lpPt->x = Init.x = m;
    lpPt->y = Init.y = n;
    lpPt++;
    iNumPt = 1;
    dwFace = dwGetNextBoundaryPoint(EAST, Init, lpPt, pInfo);
    //
    // If can't find next boundary point, return null
    //
    if (dwFace == 0)
        return((LPPOINT)NULL);
//#if 0
    //
    // remove the ifdef if we wanted to see the boundary as we trace
    //
    MoveToEx(hDC, Init.x, Init.y, NULL);
    LineTo(hDC, lpPt->x, lpPt->y);
//#endif
    //
    // Keep looking for next boundary point until I get back to where I
    // started or exceeding MAXPOINT points
    //
    while ((iNumPt < MAXPOINT) &&
           ((lpPt->x != lpTmpPt->x) || (lpPt->y != lpTmpPt->y))) {
        Init.x = lpPt->x;
        Init.y = lpPt->y;
        lpPt++;
        iNumPt++;
	dwFace = dwGetNextBoundaryPoint(dwFace, Init, lpPt, pInfo);
        //
        // If can't find next boundary point, return null
        //
        if (dwFace == 0)
            return((LPPOINT)NULL);
//#if 0
        //
        // remove the ifdef if we wanted to see the boundary as we trace
        //
        MoveToEx(hDC, Init.x, Init.y, NULL);
        LineTo(hDC, lpPt->x, lpPt->y);
//#endif

    }
    //
    // It is more likely that it is an error of the algorithm, if ever happens.
    //
    if (iNumPt >= MAXPOINT) 
	{
		OutputDebugString ("Not enough memory!!");
    }
    *piCount = iNumPt;
    return (LPPOINT) lpTmpPt;
}


/******************************Public*Routine******************************\
*
* dwGetNextBoundaryPoint
*
* Effects:  Start checking the 8 neighbors in clockwise direction.  Returns
*           the first neighbor that does not escape.
*           dwFace      where we face
*           InitPt      where we are right now in pixel coordinates
*
* Warnings: assumes that we start at a boundary point.  Does not trace into
*           a bay if the entrance closed. Ie, it cuts cycle.
*
* History:
*  12-Feb-1992 -by- Petrus Wong
* Wrote it.
\**************************************************************************/

DWORD dwGetNextBoundaryPoint(DWORD dwFace, POINT InitPt, LPPOINT lpPt, PINFO pInfo)
{
    BOOL    bEsc;
    DWORD   dwExplore;
    DWORD   dwEnd;
    int     i;
    NODE    arg[8];
    POINT   BndPt;
    LONG    lx, c1, ly, c2;
    RECT    rc;

    GetClientRect(pInfo->hwnd, &rc);
    //
    // Start exploring clockwise, ending at where we came from
    //
    dwExplore = dwShift(dwFace, RIGHT, 3);
    dwEnd = dwShift(dwFace, LEFT, 4);
    i = 0;
    bDirToPt(dwExplore, InitPt, &BndPt);
    c1 = lx = XformFix(BndPt.x, rc.left, rc.right, pInfo->lxFrom, pInfo->lxTo);
    c2 = ly = XformFix(BndPt.y, rc.top, rc.bottom, pInfo->lyFrom, pInfo->lyTo);

    while (bEsc = bEscape(BndPt, lx, ly, c1, c2, pInfo->iIteration, rc)) {
        arg[i].dwDirection = dwExplore;
        arg[i].bEscape     = TRUE;

        i++;

        if (dwExplore == dwEnd)
            break;

        dwExplore = dwShift(dwExplore, LEFT, 1);
	bDirToPt(dwExplore, InitPt, &BndPt);
	c1 = lx = XformFix(BndPt.x, rc.left, rc.right, pInfo->lxFrom, pInfo->lxTo);
	c2 = ly = XformFix(BndPt.y, rc.top, rc.bottom, pInfo->lyFrom, pInfo->lyTo);

    }

    if (bEsc) {
        return 0L;
    }

    arg[i].dwDirection = dwExplore;
    arg[i].bEscape     = FALSE;

    bDirToPt(arg[i].dwDirection, InitPt, lpPt);

    return arg[i].dwDirection;
}



/******************************Public*Routine******************************\
*
* bEscape
*
* Effects: Test if the point excapes based on the number of iterations
*
* Warnings:
*
* History:
*  16-Feb-1993      Petrus Wong     9.23 fix
*  20-Feb-1992 -by- Petrus Wong
* Wrote it.
\**************************************************************************/

BOOL bEscape(POINT Pt, LONG x, LONG y, LONG c1, LONG c2, int iIteration, RECT rc)
{
    LONG x1, y1, z;
    BOOL bEscape;
    int i;

    bEscape = FALSE;

    //
    // Treat points outside of client rect as escaping
    //
    if ((Pt.x < rc.left)   || (Pt.x > rc.right-1) ||
        (Pt.y > rc.bottom-1) || (Pt.y < rc.top))     {
        return TRUE;
    }
    for (i=1; i<=iIteration; i++) {
        x1 = lMul(x - y, x + y) + c1;
        y1 = (lMul(x, y) * 2) + c2;
        x = x1;
        y = y1;                             //    2       2     2 1/2     2
        z = lMul(x, x) + lMul(y, y);        // |Z|  = ((x1  + x2 )   ) > 2

        if (z > 33554432) {
            bEscape = TRUE;
            break;
        }
    }
    return bEscape;
}

/******************************Public*Routine******************************\
*
* bDirToPt
*
* Effects: Returns the pixel coordinates based the direction we are facing
*          and our current position
*
* Warnings:
*
* History:
*  20-Feb-1992
* Wrote it.
\**************************************************************************/

BOOL bDirToPt(DWORD dwDirection, POINT InitPt, LPPOINT lpPt)
{
    BOOL bSuccess;

    bSuccess = TRUE;
    switch ((LONG)dwDirection) {
        case EAST:
            lpPt->x = InitPt.x+1;
            lpPt->y = InitPt.y;
            break;
        case SOUTHEAST:
            lpPt->x = InitPt.x+1;
            lpPt->y = InitPt.y+1;
            break;
        case SOUTH:
            lpPt->x = InitPt.x;
            lpPt->y = InitPt.y+1;
            break;
        case SOUTHWEST:
            lpPt->x = InitPt.x-1;
            lpPt->y = InitPt.y+1;
            break;
        case WEST:
            lpPt->x = InitPt.x-1;
            lpPt->y = InitPt.y;
            break;
        case NORTHWEST:
            lpPt->x = InitPt.x-1;
            lpPt->y = InitPt.y-1;
            break;
        case NORTH:
            lpPt->x = InitPt.x;
            lpPt->y = InitPt.y-1;
            break;
        case NORTHEAST:
            lpPt->x = InitPt.x+1;
            lpPt->y = InitPt.y-1;
            break;
        default:
            bSuccess = FALSE;
            break;
    }
    return bSuccess;
}

/******************************Public*Routine******************************\
*
* dwShift
*                                     NORTH
*                           NW        0x0040        NE
*                               0x0020      0x0080
* Effects:      WEST    0x0010          *           0x0001  EAST
*                               0x0008      0x0002
*                           SW        0x0004        SE
*                                     SOUTH
*
*               Shift dwOpnd left or right by iNum.
*               dwOpnd contains the above values. The shift operation is
*               closed.
*
\**************************************************************************/

DWORD dwShift(DWORD dwOpnd, int iDir, int iNum)
{
    DWORD dwTmp;

    dwTmp = ((dwOpnd << 8) | dwOpnd);
    switch ((LONG)iDir) {
	case LEFT:
            dwTmp = dwTmp << iNum;
	    dwTmp = dwTmp & 0x0ff00;
            dwTmp = dwTmp >> 8;
            break;
	case RIGHT:
            dwTmp = dwTmp >> iNum;
            dwTmp = dwTmp & 0x0ff;
            break;
	default:
            dwTmp = 0L;
	    break;
    }
    return dwTmp;
}
