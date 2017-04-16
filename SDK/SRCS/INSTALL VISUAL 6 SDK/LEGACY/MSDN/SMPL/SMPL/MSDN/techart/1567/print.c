/*
    print.c

    Printing support

    For an example we render the object list to the printer DC
    This is WYSINWYG (What you see is *not* what you get) technology
    because a) it is easier to do and b) because it takes a lot
    less code than doing it right.

    The rectangles are rendered incorrectly because a) the scaling does not
    take into account the font metrics and b) because each rectangle
    is not clipped correctly from the ones 'above' it.

*/

#include "global.h"

void Print(HDC hDC)
{
    RECT rcPrint, rcApp;
    POBJECT pObj;

    dprintf2("Print");

    //
    // Set the bounding rectangle
    //

    rcPrint.left = rcPrint.top = 0;
    rcPrint.right = GetDeviceCaps(hDC, HORZRES);
    rcPrint.bottom = GetDeviceCaps(hDC, VERTRES);
    dprintf3(" Print rect is %u by %u", rcPrint.right, rcPrint.bottom);

    //
    // Do some stuff to set up the mapping mode and
    // stretch the window image to fit the paper.
    // This is n't the best we could do but it's cheap and easy.
    // We'll us MM_ISOTROPIC to give an arb. scale factor
    // but keep the aspect ratio the same.
    //

    SetMapMode(hDC, MM_ISOTROPIC);

    //
    // Set the window extent to the size of the application main 
    // window.
    //

    GetClientRect(ghwndMain, &rcApp);
    SetWindowExt(hDC, rcApp.right - rcApp.left, rcApp.bottom - rcApp.top);

    //
    // Set the viewport to the size of the paper
    //

    SetViewportExt(hDC, rcPrint.right, rcPrint.bottom);

    //
    // Set up the printer
    //

    Escape(hDC, STARTDOC, lstrlen(gszAppName), (LPSTR)gszAppName, NULL);

    //
    // Draw the image in the DC
    //

    pObj = gpObjList;
    while (pObj) {
        RenderObj(hDC, pObj);
        pObj = pObj->pNext;
    }

    //
    // Tell the printer it's the end of the page
    //

    Escape(hDC, NEWFRAME, 0, NULL, NULL);

    //
    // Tell the printer it's the end of the document
    //

    Escape(hDC, ENDDOC, 0, NULL, NULL);

}
