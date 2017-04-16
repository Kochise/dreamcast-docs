/*
    print.c

    Printing support

    For an example we render the text in pFileData
    into the printer DC

*/

#include "global.h"

void Print(HDC hDC)
{
    RECT rc;

    dprintf2("Print");


    //
    // Set the bounding rectangle
    //

    rc.left = rc.top = 0;
    rc.right = GetDeviceCaps(hDC, HORZRES);
    rc.bottom = GetDeviceCaps(hDC, VERTRES);

    //
    // Set up the printer
    //

    Escape(hDC, STARTDOC, lstrlen(szAppName), (LPSTR)szAppName, NULL);

    //
    // Draw the image in the DC
    //














    //
    // Tell the printer it's the end of the page
    //

    Escape(hDC, NEWFRAME, 0, NULL, NULL);

    //
    // Tell the printer it's the end of the document
    //

    Escape(hDC, ENDDOC, 0, NULL, NULL);

}
