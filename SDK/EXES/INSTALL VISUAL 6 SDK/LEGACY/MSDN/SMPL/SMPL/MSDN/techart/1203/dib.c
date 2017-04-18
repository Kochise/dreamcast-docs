/*
    dib.c

    DIB routines

*/

#include "global.h"

//
// Load a DIB file.
// If pszDIB is NULL or empty, a dialog is presented to choose the file
// The DIB structure pointed to by pDIB is filled in with the info
// on the DIB.  A single memory chunk is used for the whole DIB 
// keeping the DIB in CF_DIB (packed DIB) format.
//

PDIB LoadDIB(LPSTR pszPath)
{
    char szFile[_MAX_PATH];
    int fd;
    OFSTRUCT os;
    BITMAPFILEHEADER BmpFileHdr;
    BITMAPINFOHEADER BmpInfoHdr;
    BITMAPCOREHEADER BmpCoreHdr;
    WORD wColors, wColorTableSize, wBytes, w;
    DWORD dwBISize, dwBitsSize, dwBytes, dwSize;
    LPBITMAPINFO pBmpInfo = NULL;
    HPSTR pBits = NULL;
    BOOL bIsPM = FALSE;
    RGBTRIPLE rgbt;
    LPRGBQUAD lpRGB;

    if (!pszPath || !lstrlen(pszPath)) {

        //
        // Show the file open dialog
        //

        if (!PromptForFileName(hwndMain, 
                               hAppInstance, 
                               szFile,
                               sizeof(szFile), 
                               "Open File", 
                               szOpenFilter,
                               "dib",
                               PFFN_OPENFILE | PFFN_UPPERCASE)) {
            return NULL;
        }

    } else {

        lstrcpy(szFile, pszPath);

    }

    //
    // try to open the file in read mode
    //

    fd = OpenFile(szFile, &os, OF_READ);
    if (fd < 1) {
        dprintf1("Failed to open %s", (LPSTR)szFile);
        goto $abort;
    }

    dprintf2("Loading: %s", (LPSTR)szFile);

    //
    // read the file header to get the file size and to
    // find where the bits start in the file
    //

    wBytes = _lread(fd, (LPSTR)&BmpFileHdr, sizeof(BmpFileHdr)); 
    if (wBytes != sizeof(BmpFileHdr)) {
        dprintf1("Failed to read file header");
        goto $abort;
    }

    //
    // check we have the magic 'BM' at the start
    //

    if (BmpFileHdr.bfType != 0x4D42) {
        dprintf1("Not a bitmap file");
        goto $abort;
    }

    //
    // make a wild guess that the file is in Windows DIB
    // format and read the BITMAPINFOHEADER.  If it turns
    // out to be a PM DIB file we'll convert it later.
    //

    wBytes = _lread(fd, (LPSTR)&BmpInfoHdr, sizeof(BmpInfoHdr)); 
    if (wBytes != sizeof(BmpInfoHdr)) {
        dprintf1("Failed to read BITMAPINFOHEADER");
        goto $abort;
    }

    //
    // check we got a real Windows DIB file
    //

    if (BmpInfoHdr.biSize != sizeof(BITMAPINFOHEADER)) {
        dprintf3("File is not Windows DIB format");
        if (BmpInfoHdr.biSize != sizeof(BITMAPCOREHEADER)) {
            dprintf1("File is not Windows or PM DIB format");
            goto $abort;
        }

        //
        // set a flag to convert PM file to Win format later
        //

        bIsPM = TRUE;

        //
        // back up the file pointer and read the BITMAPCOREHEADER
        // and create the BITMAPINFOHEADER from it
        //

        _llseek(fd, sizeof(BITMAPFILEHEADER), SEEK_SET);

        wBytes = _lread(fd, (LPSTR)&BmpCoreHdr, sizeof(BmpCoreHdr)); 
        if (wBytes != sizeof(BmpCoreHdr)) {
            dprintf1("Failed to read BITMAPCOREHEADER");
            goto $abort;
        }

        BmpInfoHdr.biSize = sizeof(BITMAPINFOHEADER);
        BmpInfoHdr.biWidth = (DWORD) BmpCoreHdr.bcWidth;
        BmpInfoHdr.biHeight = (DWORD) BmpCoreHdr.bcHeight;
        BmpInfoHdr.biPlanes = BmpCoreHdr.bcPlanes;
        BmpInfoHdr.biBitCount = BmpCoreHdr.bcBitCount;
        BmpInfoHdr.biCompression = BI_RGB;
        BmpInfoHdr.biSizeImage = 0;
        BmpInfoHdr.biXPelsPerMeter = 0;
        BmpInfoHdr.biYPelsPerMeter = 0;
        BmpInfoHdr.biClrUsed = 0;
        BmpInfoHdr.biClrImportant = 0;

    }

    //
    // ok so we got a real DIB file so work out 
    // how much memory we need for the BITMAPINFO
    // structure, color table and bits.  Allocate it,
    // copy the BmpInfoHdr we have so far 
    // and then read in the color table from the file
    //

    wColors = NumDIBColorEntries((LPBITMAPINFO) &BmpInfoHdr);
    wColorTableSize = wColors * sizeof(RGBQUAD);
    dwBitsSize = BmpFileHdr.bfSize - BmpFileHdr.bfOffBits;
    dwBISize = (DWORD) sizeof(BITMAPINFOHEADER)    
           + (DWORD) wColorTableSize;
    dwSize = dwBISize + dwBitsSize;

    if (dwSize > 65536L) {
        dprintf2("WARNING: DIB > 64k");
    }

    //
    // allocate and lock the memory
    //

    pBmpInfo = (LPBITMAPINFO) ALLOCATE(dwSize);
    if (!pBmpInfo) {
        dprintf1("Out of memory for DIB");
        goto $abort;
    }

    //
    // copy the header we already have
    //

    hmemcpy((HPSTR) pBmpInfo, (HPSTR) &BmpInfoHdr, sizeof(BITMAPINFOHEADER));

    //
    // now read the color table in from the file
    //

    if (bIsPM == FALSE) {

        //
        // read the color table from the file
        //

        wBytes = _lread(fd,
                        ((LPSTR) pBmpInfo) + sizeof(BITMAPINFOHEADER),
                        wColorTableSize);
    
        if (wBytes != wColorTableSize) {
            dprintf1("Failed to read color table");
            goto $abort;
        }

    } else {

        //
        // read each color table entry in turn and convert it
        // to Win DIB format as we go
        //

        lpRGB = (LPRGBQUAD) ((LPSTR) pBmpInfo + sizeof(BITMAPINFOHEADER));
        for (w=0; w<wColors; w++) {
            wBytes = _lread(fd, (LPSTR) &rgbt, sizeof(RGBTRIPLE));
            if (wBytes != sizeof(RGBTRIPLE)) {
                dprintf1("Failed to read RGBTRIPLE");
                goto $abort;
            }
            lpRGB->rgbBlue = rgbt.rgbtBlue;
            lpRGB->rgbGreen = rgbt.rgbtGreen;
            lpRGB->rgbRed = rgbt.rgbtRed;
            lpRGB->rgbReserved = 0;
            lpRGB++;
        }
    }

    //
    // now we just have to read the bits from the file
    //

    pBits = (LPSTR) pBmpInfo 
          + sizeof(BITMAPINFOHEADER)
          + wColors * sizeof(RGBQUAD);

    //
    // seek to the bits in the file
    //

    _llseek(fd, BmpFileHdr.bfOffBits, SEEK_SET);

    //
    // read the bits
    //

    dwBytes = _hread(fd, pBits, dwBitsSize);
    if (dwBytes != dwBitsSize) {
        dprintf1("Failed to read bits");
        goto $abort;
    }

#ifdef DEBUG
    ShowInfo(pBmpInfo);
#endif

    //
    // done with the file
    //

    _lclose(fd);


    //
    // make sure it's a 256 color DIB
    //

    if (pBmpInfo->bmiHeader.biBitCount != 8) {
        Message(0, "%u bit DIBs are not supported", (UINT)pBmpInfo->bmiHeader.biBitCount);
        goto $abort;
    }

    //
    // make sure it's not RLE
    //

    if (pBmpInfo->bmiHeader.biCompression != BI_RGB) {
        Message(0, "Compressed (RLE) DIBs are not supported");
        goto $abort;
    }

    //
    // Copy the return info
    //

    return (PDIB) pBmpInfo;


$abort: // crap out

    if (pBmpInfo) FREE(pBmpInfo);
    if (fd >= 1) _lclose(fd);

    Message(0, "Unable to load file");

    return NULL;
}

//
// Delete a DIB
//

void DeleteDIB(PDIB pDIB)
{
    if (!pDIB) return;

    FREE(pDIB);

}

//
// Check for a windows DIB
//

BOOL IsWinDIB(LPBITMAPINFOHEADER pBIH)
{
    if (pBIH->biSize != sizeof(BITMAPINFOHEADER)) {
        return FALSE;
    }
    return TRUE;
}

//
// The the value (color index) of a DIB pixel
// NOTE: DIB scan lines are DWORD aligned.  The scan line 
// storage width may be wider than the scan line image width
// so calc the storage width by rounding the image width 
// to the next highest dword value
//

HPSTR GetDIBPixelAddress(PDIB pDIB, int x, int y)
{
    HPSTR p;
    long lWidth;

    //
    // make sure it's in range and if not return zero
    //

    if ((x < 0)
    || (y < 0)
    || (x >= DIB_WIDTH(pDIB)) 
    || (y >= DIB_HEIGHT(pDIB))) {
        dprintf1("Attempt to get out of range pixel addr");
        return NULL;
    }

    //
    // Calculate the scan line storage width
    //

    lWidth = DIB_STORAGEWIDTH(pDIB);

    ASSERT(lWidth <= DIB_WIDTH(pDIB) + 3);
    ASSERT(lWidth >= DIB_WIDTH(pDIB));

    p = (HPSTR) DIB_PBITS(pDIB);
    p += (long)(DIB_HEIGHT(pDIB)-y-1) * lWidth + (long)x;

    return p;
}

//
// The the value (color index) of a DIB pixel
//

BYTE GetDIBPixelValue(PDIB pDIB, int x, int y)
{
    HPSTR p;

    p = GetDIBPixelAddress(pDIB, x, y);

    if (!p) {

        dprintf1("Out of range pixel coords");
        return 0;
    }

    return *p;
}

//
// Return the Color of a DIB pixel
//

COLORREF GetDIBPixelColor(PDIB pDIB, int x, int y)
{
    BYTE value;
    RGBQUAD quad;
    COLORREF clr;

    value = GetDIBPixelValue(pDIB, x, y);
    quad = (DIB_PCLRTAB(pDIB))[value];
    clr = RGB(quad.rgbRed, quad.rgbGreen, quad.rgbBlue);

    return clr;
}

//
// Show some DIB info
//

void ShowInfo(LPBITMAPINFO lpBmpInfo)
{
    LPBITMAPINFOHEADER lpBmpInfoHdr;

    lpBmpInfoHdr = &lpBmpInfo->bmiHeader;

    dprintf4("BITMAPINFOHEADER:");
//  dprintf4("  biSize:          %lu", lpBmpInfoHdr->biSize);
    dprintf4("  biWidth:         %lu", lpBmpInfoHdr->biWidth);
    dprintf4("  biHeight:        %lu", lpBmpInfoHdr->biHeight);
    dprintf4("  biPlanes:        %u", lpBmpInfoHdr->biPlanes);
    dprintf4("  biBitCount:      %u", lpBmpInfoHdr->biBitCount);
    switch (lpBmpInfoHdr->biCompression) {
    case BI_RGB:
        dprintf4("  biCompression:   none");
        break;
    case BI_RLE8:
        dprintf4("  biCompression:   RLE 8");
        break;
    case BI_RLE4:
        dprintf4("  biCompression:   RLE 4");
        break;
    default:
        dprintf4("  biCompression:   unknown: %8.8XH", lpBmpInfoHdr->biCompression);
        break;
    }
    dprintf4("  biSizeImage:     %lu", lpBmpInfoHdr->biSizeImage);
//  dprintf4("  biXPelsPerMeter: %lu", lpBmpInfoHdr->biXPelsPerMeter);
//  dprintf4("  biYPelsPerMeter: %lu", lpBmpInfoHdr->biYPelsPerMeter);
    dprintf4("  biClrUsed:       %lu", lpBmpInfoHdr->biClrUsed);
//  dprintf4("  biClrImportant:  %lu", lpBmpInfoHdr->biClrImportant);

}

WORD NumDIBColorEntries(LPBITMAPINFO lpBmpInfo) 
{
    LPBITMAPINFOHEADER lpBIH;
    LPBITMAPCOREHEADER lpBCH;
    WORD wColors, wBitCount;

    if (!lpBmpInfo) {
        dprintf1("NULL arg to NumDIBColorEntries()");
        return 0;
    }

    lpBIH = &(lpBmpInfo->bmiHeader);
    lpBCH = (LPBITMAPCOREHEADER) lpBIH;

    //
    // start off by assuming the color table size from
    // the bit per pixel field
    //

    if (IsWinDIB(lpBIH)) {
        wBitCount = lpBIH->biBitCount;
    } else {
        wBitCount = lpBCH->bcBitCount;
    }

    switch (wBitCount) {
    case 1:
        wColors = 2;
        break;
    case 4:
        wColors = 16;
        break;
    case 8:
        wColors = 256;
        break;
    case 24:
    default:
        wColors = 0;
        break;
    }

    //
    // If this is a Windows DIB, then the color table length
    // is determined by the biClrUsed field
    //

    if (IsWinDIB(lpBIH)) {
        if (lpBIH->biClrUsed != 0) {
            wColors = (WORD)lpBIH->biClrUsed;
        }
    }

    return wColors;
}

//
// Create a DIB the same size and organization as another one
//

PDIB CreateCompatibleDIB(PDIB pOld)
{
    PDIB pNew;

    pNew = ALLOCATE(SIZE(pOld));

    if (!pNew) {
        dprintf1("No memory for new DIB");
        return NULL;
    }

    //
    // Copy the bitmap info 
    //

    _fmemcpy(pNew,
             pOld, 
             DIB_BISIZE(pOld));

    return pNew;
}

//
// Map the color table of one DIB to the color table of
// another DIB.  This is used to enure that all sprite DIBs
// are using the same color table as the background DIB so that 
// when we copy sprite DIB bits to the off-screen DIB the colors
// will be correct.
// Note: This is not neccessary if all the sprite DIBs are created 
// with the same palette at authoring time.
//

void MapDIBColorTable(PDIB pdibObj, PDIB pdibRef)
{
    PDIB pdibOS;
    LPRGBQUAD pqOS, pqR;
    HDC hdcDIB;
    HPBYTE pBitsS, pBitsD;
    long lScanS;

    //
    // Create a DIB compatible with the object DIB
    // and copy the color table of the reference DIB to it
    //

    pdibOS = CreateCompatibleDIB(pdibObj);
    if (!pdibOS) return;

    pqOS = DIB_PCLRTAB(pdibOS);
    pqR = DIB_PCLRTAB(pdibRef);
    _fmemcpy(pqOS, pqR, 256 * sizeof(RGBQUAD));

    //
    // Create a DIB Driver DC from the new DIB
    //

    hdcDIB = CreateDC("DIB", NULL, NULL, (LPSTR)pdibOS);
    if (!hdcDIB) {
        dprintf1("Failed to create off-screen DC");
        return;
    }

    //
    // Render the object DIB to the off-screen DC using
    // DIB_RGB_COLORS to get the correct color mapping
    //

    StretchDIBits(hdcDIB,
                0,                      // dest x
                0,                      // dest y
                DIB_WIDTH(pdibOS),      // dest width
                DIB_HEIGHT(pdibOS),     // dest height
                0,                      // src x
                0,                      // src y
                DIB_WIDTH(pdibObj),     // src width
                DIB_HEIGHT(pdibObj),    // src height
                DIB_PBITS(pdibObj),     // bits
                DIB_PBI(pdibObj),       // BITMAPINFO
                DIB_RGB_COLORS,
                SRCCOPY);               // rop
    //
    // Now copy the bits back from the off-screen DIB
    // to the original DIB
    //

    pBitsS = DIB_PBITS(pdibOS);
    pBitsD = DIB_PBITS(pdibObj);

    lScanS = DIB_STORAGEWIDTH(pdibOS);

    hmemcpy(pBitsD, pBitsS, lScanS * DIB_HEIGHT(pdibOS));

    //
    // Delete the off-screen DC and DIB
    //

    DeleteDC(hdcDIB);
    DeleteDIB(pdibOS);



}
