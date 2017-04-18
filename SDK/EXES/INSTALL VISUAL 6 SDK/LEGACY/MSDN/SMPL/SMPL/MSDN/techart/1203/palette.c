/*

    palette.c


    DIB palette routines

*/

#include "global.h"

HPALETTE CreateWinDIBPalette(LPBITMAPINFO lpBmpInfo);
HPALETTE CreatePMDIBPalette(LPBITMAPINFO lpBmpInfo);

//
// Create a palette for a DIB
//

HPALETTE CreateDIBPalette(LPBITMAPINFO lpBmpInfo)
{
    LPBITMAPINFOHEADER lpBmpInfoHdr;
    HANDLE hPalMem;
    LOGPALETTE *pPal;
    HPALETTE hPal;
    LPRGBQUAD lpRGB;
    int iColors, i;

    //
    // validate the header
    //

    lpBmpInfoHdr = (LPBITMAPINFOHEADER) lpBmpInfo;
    if (!IsWinDIB(lpBmpInfoHdr)) {
        dprintf1("Invalid lpBmpInfoHdr");
        return NULL;
    }

    //
    // get a pointer to the RGB quads and the number of colors
    // in the color table (we don't do 24 bit stuff here)
    //

    lpRGB = (LPRGBQUAD)((LPSTR)lpBmpInfoHdr + (WORD)lpBmpInfoHdr->biSize);

    iColors = NumDIBColorEntries(lpBmpInfo);

    //
    // Check we got a color table
    //

    if (!iColors) {
        dprintf1("No color table");   
        return NULL;
    }

    //
    // allocate a log pal and fill it with the color table info
    //

    hPalMem = LocalAlloc(LMEM_MOVEABLE, sizeof(LOGPALETTE) + iColors * sizeof(PALETTEENTRY));
    if (!hPalMem) {
        dprintf1("Out of local memory for logpal");
        return NULL;
    }
    pPal = (LOGPALETTE *) LocalLock(hPalMem);
    pPal->palVersion = 0x300; // Windows 3.0
    pPal->palNumEntries = iColors; // table size
    for (i=0; i<iColors; i++) {
        pPal->palPalEntry[i].peRed = lpRGB[i].rgbRed;
        pPal->palPalEntry[i].peGreen = lpRGB[i].rgbGreen;
        pPal->palPalEntry[i].peBlue = lpRGB[i].rgbBlue;
        pPal->palPalEntry[i].peFlags = 0;
    }

    hPal = CreatePalette(pPal);
    LocalUnlock(hPalMem);
    LocalFree(hPalMem);

    return hPal;
}

HPALETTE CopyPalette(HPALETTE hSrcPal) 
{
    HANDLE hPalMem;
    LOGPALETTE *pPal;
    HPALETTE hDstPal;
    int iEntries;


    GetObject(hSrcPal, sizeof(iEntries), (LPSTR)&iEntries); // get no. of pal colors
    if (!iEntries) return NULL;

    hPalMem = LocalAlloc(LMEM_MOVEABLE, sizeof(LOGPALETTE) + iEntries * sizeof(PALETTEENTRY));
    if (!hPalMem) {
        dprintf1("\nOut of local memory for logpal");
        return NULL;
    }
    pPal = (LOGPALETTE *) LocalLock(hPalMem);
    pPal->palVersion = 0x300; // Windows 3.0
    pPal->palNumEntries = iEntries; // table size
    GetPaletteEntries(hSrcPal, 0, iEntries, pPal->palPalEntry);

    hDstPal = CreatePalette(pPal);
    LocalUnlock(hPalMem);
    LocalFree(hPalMem);

    return hDstPal;
}

//
// Modify a palette to have the system colors in the first 
// and last 10 positions
//

void SetSysPalColors(HPALETTE hPal)
{
    HANDLE hPalMem;
    LOGPALETTE *pPal;
    int iEntries;
    HDC hdcScreen;

    dprintf2("SetSysPalColors");

    //
    // Create a log palette with 256 entries
    //

    hPalMem = LocalAlloc(LMEM_MOVEABLE, 
                         sizeof(LOGPALETTE) + 256 * sizeof(PALETTEENTRY));
    if (!hPalMem) {
        dprintf1("\nOut of local memory for logpal");
        return;
    }

    //
    // Set the palette info from the supplied palette
    //

    pPal = (LOGPALETTE *) LocalLock(hPalMem);
    pPal->palVersion = 0x300; // Windows 3.0
    GetObject(hPal, sizeof(iEntries), (LPSTR)&iEntries);
    pPal->palNumEntries = iEntries; // table size
    GetPaletteEntries(hPal, 0, iEntries, pPal->palPalEntry);

#ifdef DEBUG
    {
        int i;

        dprintf3(" Before...");
        for (i=0; i<10; i++) {
            dprintf3("  %d  %u,%u,%u",
                    i,
                    pPal->palPalEntry[i].peRed,
                    pPal->palPalEntry[i].peGreen,
                    pPal->palPalEntry[i].peBlue);
        }
        for (i=246; i<256; i++) {
            dprintf3("  %d  %u,%u,%u",
                    i,
                    pPal->palPalEntry[i].peRed,
                    pPal->palPalEntry[i].peGreen,
                    pPal->palPalEntry[i].peBlue);
        }
    }
#endif // DEBUG

    //
    // Copy the low 10 and high ten system palette entries
    //

    hdcScreen = GetDC(NULL);
    GetSystemPaletteEntries(hdcScreen, 0, 10, pPal->palPalEntry);
    GetSystemPaletteEntries(hdcScreen, 246, 10, &(pPal->palPalEntry[246]));
    ReleaseDC(NULL, hdcScreen);

#ifdef DEBUG
    {
        int i;

        dprintf3(" After...");
        for (i=0; i<10; i++) {
            dprintf3("  %d  %u,%u,%u",
                    i,
                    pPal->palPalEntry[i].peRed,
                    pPal->palPalEntry[i].peGreen,
                    pPal->palPalEntry[i].peBlue);
        }
        for (i=245; i<256; i++) {
            dprintf3("  %d  %u,%u,%u",
                    i,
                    pPal->palPalEntry[i].peRed,
                    pPal->palPalEntry[i].peGreen,
                    pPal->palPalEntry[i].peBlue);
        }
    }
#endif // DEBUG

    //
    // Write the modified entries back to the palette
    //

    SetPaletteEntries(hPal, 0, 256, pPal->palPalEntry);


    LocalUnlock(hPalMem);
    LocalFree(hPalMem);

}

//
// Process palette messages
//

LRESULT PaletteMessage(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{
    HDC hDC;
    int i;
    HPALETTE hOldPal;


    switch (msg) {
    case WM_PALETTECHANGED:

        //
        // Someone changed the palette. See if was us.
        //

        if ((HWND)wParam == hWnd) {

            return (LRESULT) 0; // nothing to do (it was us)
        }

        // else drop through

    case WM_QUERYNEWPALETTE:

        //
        // We are going active so realize our palette
        //

        if (hpalCurrent) {
            dprintf2("Realizing palette");
            hDC = GetDC(hWnd);
            hOldPal = SelectPalette(hDC, hpalCurrent, 0);
            i = RealizePalette(hDC);
            ReleaseDC(hWnd, hDC);
            if (i > 0) {

                //
                // some colors changed so we need to do a repaint
                //

                dprintf2("Repainting with new palette");
                InvalidateRect(hWnd, NULL, TRUE); // repaint the lot
                return TRUE; // say we did something
            }
        }

        break;

    default:
        break;
    }

    return 0l; // say we did nothing
}

