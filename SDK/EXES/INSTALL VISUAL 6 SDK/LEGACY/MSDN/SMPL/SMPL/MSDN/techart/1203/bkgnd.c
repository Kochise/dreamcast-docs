/*
    bkgnd.c

    Background image routines
*/

#include "global.h"

//
// Load a new background image.
// All current sprites are deleted.
// The current palette is created from the palette found in the DIB
// The window size is adjusted to fit the new image.
// A new off-screen DIB DC is created to match the size of the bkgnd
// The bkgnd is rendered to the os DIB and the screen repainted
// if requested
//

void LoadBackground(LPSTR pszPath, BOOL bUpdateScreen)
{
    RECT rcWnd;
    LPWORD pIndex;
    int i;

    dprintf2("LoadBackground(%s)", pszPath ? pszPath : "NULL");

    //
    // Delete the current sprite set
    //

    DeleteSpriteList();

    //
    // Nuke any old DIB
    //

    DeleteDIB(pdibBkGnd);

    //
    // Try to load the new DIB
    //

    pdibBkGnd = LoadDIB(pszPath);
    if (!pdibBkGnd) {
        return;
    }

    //
    // Create a new palette based on the background DIB
    //

    if (hpalCurrent) DeleteObject(hpalCurrent);
    hpalCurrent = CreateDIBPalette(pdibBkGnd);
    SetSysPalColors(hpalCurrent);

    //
    // Adjust the window to fit the new background. But not
    // too teeny weeny.
    //

    rcWnd.top = 0;
    rcWnd.left = 0;
    rcWnd.right = max (DIB_WIDTH(pdibBkGnd), 150);
    rcWnd.bottom = max(DIB_HEIGHT(pdibBkGnd), 100);
    AdjustWindowRect(&rcWnd, WS_OVERLAPPEDWINDOW, TRUE);
    SetWindowPos(hwndMain,
                 NULL,
                 0,
                 0,
                 rcWnd.right-rcWnd.left,
                 rcWnd.bottom-rcWnd.top,
                 SWP_NOACTIVATE | SWP_NOMOVE);

    //
    // Delete any existing off-screen DC and its DIB
    //

    if (hdcOffScreen) {
        DeleteDC(hdcOffScreen);
        hdcOffScreen = NULL;
    }

    DeleteDIB(pdibOffScreen);

    //
    // Create a new off-screen DC using the DIB driver which 
    // has the same size as the background DIB and the same color
    // organization.  The data is in CF_DIB format with the bits
    // immediately following the header.
    //

    pdibOffScreen = CreateCompatibleDIB(pdibBkGnd);
    if (!pdibOffScreen) {
        dprintf1("Failed to create off-screen DIB");
        return;
    }

    //
    // Create a DIB driver DC
    //

    hdcOffScreen = CreateDC("DIB", NULL, NULL, (LPSTR)pdibOffScreen);
    if (!hdcOffScreen) {
        dprintf1("Failed to create off-screen DC");
    } else {
        dprintf3("Off-screen DC created");
    }

#ifdef DEBUG

    //
    // Show what the DIB device driver supports
    //

    {

        WORD wCaps;

        wCaps = GetDeviceCaps(hdcOffScreen, RASTERCAPS);
        if (wCaps & RC_DI_BITMAP) {
            dprintf3("DIB driver DC supports GetDIBits and SetDIBits");
        } else {
            dprintf3("DIB driver DC doesn't support GetDIBits or SetDIBits");
        }
        if (wCaps & RC_DIBTODEV) {
            dprintf3("DIB driver DC supports SetDIBitsToDevice");
        } else {
            dprintf3("DIB driver DC doesn't support SetDIBitsToDevice");
        }
        if (wCaps & RC_STRETCHDIB) {
            dprintf3("DIB driver DC supports StretchDIBits");
        } else {
            dprintf3("DIB driver DC doesn't support StretchDIBits");
        }
        wCaps = GetDeviceCaps(hdcOffScreen, CAPS1);
        if (wCaps & C1_TRANSPARENT) {
            dprintf3("DIB driver DC supports transparency");
        } else {
            dprintf3("DIB driver DC doesn't support transparency");
        }
    }

#endif // DEBUG

    //
    // Create a new 1:1 lookup table so we can use DIB_PAL_COLORS
    // when we call StretchDIBits to blt data from the off-screen
    // DC to the window DC.
    //

    if (!pPalClrTable) {
        pPalClrTable = (LPBITMAPINFO) ALLOCATE(sizeof(BITMAPINFOHEADER)
                                               + 256 * sizeof(WORD));
        if (!pPalClrTable) {
            dprintf1("Out of memory for 1:1 clr table");
            return;
        }
    }

    //
    // Set up the table to match the off-screen DIB
    // by copying the BITMAPINFOHEADER and building a 1:1 color table
    //

    _fmemcpy(pPalClrTable,
             pdibOffScreen,
             sizeof(BITMAPINFOHEADER));

    pIndex = (LPWORD)((LPSTR)pPalClrTable + sizeof(BITMAPINFOHEADER));
    for (i=0; i<256; i++) {
        *pIndex++ = (WORD) i;
    }

    //
    // Draw the background to the off-screen DIB
    // and update the screen if required
    //

    Redraw(NULL, bUpdateScreen);

}
