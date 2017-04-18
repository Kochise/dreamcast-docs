/*
    util.c

    Some functions with no better place to be than here.
*/

#include "global.h"

//
// Attempt to get the POINTL field from the CF_OBJECTDESCRIPTOR
// of a data object.  Returns 0,0 if anything fails.
// Returned coordinates are in MMTEXT format.
//

void GetObjectDescriptorPointAndSize(LPDATAOBJECT pData,
                                     POINT FAR *ppt,
                                     int FAR *lpw,
                                     int FAR *lph)
{
    HGLOBAL hGlobal;
    LPOBJECTDESCRIPTOR lpOD;
    CLIPFORMAT fmt;
    STGMEDIUM stg;
    POINT pt;

    dprintf2("GetObjectDescriptorPoint");

    ppt->x = ppt->y = 0;

    fmt = NULL;

    stg.tymed = TYMED_HGLOBAL;
    stg.hGlobal = NULL;
    stg.pUnkForRelease = NULL;

    hGlobal = OleStdFillObjectDescriptorFromData(pData,
                                                 &stg,
                                                 &fmt);

    if (!hGlobal || !(fmt = gcfObjectDescriptor)) {
        dprintf3(" no object descriptor found");
        return;
    }
    lpOD = (LPOBJECTDESCRIPTOR) GlobalLock(hGlobal);
    if (lpOD) {

        pt.x = (int) lpOD->pointl.x;
        pt.y = (int) lpOD->pointl.y;
        *lpw = (int) lpOD->sizel.cx;
        *lph = (int) lpOD->sizel.cy;
        dprintf3(" pt (HIMETRIC): (%d,%d) %d x %d",
                  pt.x, pt.y, *lpw, *lph);

        //
        // Convert HIMETRIC coords to TEXT
        //

        pt.x = MulDiv(pt.x,
                      iLogPixelsX,
                      2540);
        pt.y = MulDiv(pt.y,
                      iLogPixelsY,
                      2540);
        *lpw = MulDiv(*lpw,
                      iLogPixelsX,
                      2540);
        *lph = MulDiv(*lph,
                      iLogPixelsY,
                      2540);

        dprintf3(" pt (TEXT): (%d,%d) %d x %d",
                  pt.x, pt.y, *lpw, *lph);
        GlobalUnlock(hGlobal);
        *ppt = pt;

    }
    GlobalFree(hGlobal);
}

//
// Draw a rubber band on a window
//

void DrawBand(HWND hWnd, LPRECT prc)
{
    HDC hDC;
    HBRUSH hbrNull, hbrOld;

    hDC = GetDC(hWnd);
    hbrNull = GetStockObject(NULL_BRUSH);
    hbrOld = SelectObject(hDC, hbrNull);
    SetROP2(hDC, R2_NOT);
    Rectangle(hDC,
              prc->left, 
              prc->top,
              prc->right,
              prc->bottom);
    SelectObject(hDC, hbrOld);
    ReleaseDC(hWnd, hDC);
}
