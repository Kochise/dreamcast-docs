// dibpal.cpp : implementation file
//

#include "stdafx.h"
#include "dibpal.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDIBPal

CDIBPal::CDIBPal()
{
}

CDIBPal::~CDIBPal()
{
}

// Create a palette from the color table in a DIB
BOOL CDIBPal::Create(CDIB *pDIB)
{
    LOGPALETTE *pPal;
    RGBQUAD *pRGB;
    DWORD dwColors, dw;

    // get a pointer to the RGB quads and the number of colors
    // in the color table (we don't do 24 bit stuff here)
    pRGB = pDIB->GetClrTabAddress();
    dwColors = pDIB->GetNumClrEntries();
    // Check we got a color table
    if (! dwColors) {
        TRACE("No color table");   
        return FALSE;
    }

    // allocate a log pal and fill it with the color table info
    pPal = (LOGPALETTE *) malloc(sizeof(LOGPALETTE) + dwColors * sizeof(PALETTEENTRY));
    if (!pPal) {
        TRACE("Out of memory for logpal");
        return FALSE;
    }
    pPal->palVersion = 0x300; // Windows 3.0
    pPal->palNumEntries = (WORD) dwColors; // table size
    for (dw=0; dw<dwColors; dw++) {
        pPal->palPalEntry[dw].peRed = pRGB[dw].rgbRed;
        pPal->palPalEntry[dw].peGreen = pRGB[dw].rgbGreen;
        pPal->palPalEntry[dw].peBlue = pRGB[dw].rgbBlue;
        pPal->palPalEntry[dw].peFlags = 0;
    }
    BOOL bResult = CreatePalette(pPal);
    free (pPal);
    return bResult;
}

/////////////////////////////////////////////////////////////////////////////
// CDIBPal commands

// Modify a palette to have the system colors in the first 
// and last few positions.
BOOL CDIBPal::SetSysPalColors()
{
    BOOL bResult = FALSE;
    int i, iSysColors, iPalEntries;
    HPALETTE hpalOld;

    // Get a screen DC to work with
   HWND hwndActive = NULL ; //DER ::GetActiveWindow();
   //DER ASSERT(hwndActive);
    HDC hdcScreen = ::GetDC(hwndActive);
    ASSERT(hdcScreen);

    // Make sure we are on a palettized device
    if (!GetDeviceCaps(hdcScreen, RASTERCAPS) & RC_PALETTE) {
        TRACE("Not a palettized device");
        goto abort;
    }

    // Get the number of system colors and the number of palette entries
    // Note that on a palletized device the number of colors is the
    // number of guaranteed colors.  I.e. the number of reserved system colors
    iSysColors = GetDeviceCaps(hdcScreen, NUMCOLORS);
    iPalEntries = GetDeviceCaps(hdcScreen, SIZEPALETTE);

    // if there are more than 256 colors we are wasting our time
    if (iSysColors > 256) goto abort;

    // Now we force the palette manager to reset its tables so that
    // the next palette to be realized will get its colors in the order they are 
    // in the logical palette. This is done by changing the number of
    // reserved colors.
    SetSystemPaletteUse(hdcScreen, SYSPAL_NOSTATIC);
    SetSystemPaletteUse(hdcScreen, SYSPAL_STATIC);

    // Select our palette into the screen DC and realize it so that
    // its colors will be entered into the free slots in the physical palette
    hpalOld = ::SelectPalette(hdcScreen,
                              (HPALETTE)m_hObject, // our hpal
                              FALSE);
    ::RealizePalette(hdcScreen);
    // Now replace the old palette (but don't realize it)
    ::SelectPalette(hdcScreen, hpalOld, FALSE);

    // The physical palette now has our colors set in place and its own
    // reserved colors at either end.  We can grab the lot now
    PALETTEENTRY pe[256];
    GetSystemPaletteEntries(hdcScreen, 
                            0,
                            iPalEntries,
                            pe);

    // Set the PC_NOCOLLAPSE flag for each of our colors so that GDI
    // won't merge them together.  Be careful not to set PC_NOCOLLAPSE for the 
    // sys color entries or we'll get multpile copies of these colors in
    // the palette when we realize it.
    for (i = 0; i < iSysColors/2; i++) {
        pe[i].peFlags = 0;
    }
    for (; i < iPalEntries-iSysColors/2; i++) {
        pe[i].peFlags = PC_NOCOLLAPSE;
    }
    for (; i < iPalEntries; i++) {
        pe[i].peFlags = 0;
    }

    // Resize the palette in case it was smaller
    ResizePalette(iPalEntries);

    // Update the palette entries with what is now in the physical palette
    SetPaletteEntries(0, iPalEntries, pe);
    bResult = TRUE;

abort:
    ::ReleaseDC(hwndActive, hdcScreen);
    return bResult;
}
