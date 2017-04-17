/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1996-1997 Microsoft Corporation

Module Name:

    ddutil.cxx

Abstract:

    This contains helper routines for loading bitmaps and palettes
    from resources.

Environment:

    Dragon emulation under Windows 95.

-------------------------------------------------------------------*/

// Include files
#include "precomp.hxx"


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    GetPointerToBitmapFile

Description:

    Given a resource name, this function returns a pointer to the raw
    data for that resource.  The resource must be listed in the .RC file
    as RCDATA.

Return Value:

    Pointer to the first byte of raw data for the specified resource.

-------------------------------------------------------------------*/
void *
GetPointerToBitmapFile (
    HINSTANCE hinstApp,     // instance handle of the app
    LPCTSTR szName)         // name of RCDATA resource in RC file
{
    HRSRC       hrsrc;
    HGLOBAL     hglobal;
    TCHAR       outbuf[256];

    // Handles obtained through FindResource and LoadResource do not have
    // to be freed or released.  This is done automatically.

    // Find the resource.
    hrsrc = FindResource (hinstApp, szName, RT_RCDATA);
    if (hrsrc == NULL) {
        wsprintf (outbuf, TEXT("ERROR: Could not find resource \"%s\".\r\n"), szName);
        OutputDebugString (outbuf);
        OutputDebugString (TEXT("Please include bitmaps in your RC file as type RCDATA.\r\n"));
        return NULL;
    }

    // Load the resource.
    hglobal = LoadResource (hinstApp, hrsrc);
    if (hglobal == NULL) {
        OutputDebugString (TEXT("Could not load resource.\r\n"));
        return NULL;
    }

    // Get pointer to raw data in resource.
    return LockResource (hglobal);
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    GetPointerToBitmapBits

Description:

    Given a pointer to the very first byte of a .BMP file (which is
    essentially a pointer to the BITMAPFILEHEADER structure), this
    routine returns a pointer to the pixel data for the bitmap.

Return Value:

    Pointer to the first pixel in the bitmap.

-------------------------------------------------------------------*/
BYTE *
GetPointerToBitmapBits (
    void *pbmpfileheader)   // pointer to start of bitmap file
{
    return ((BYTE *) pbmpfileheader) + 
        ((BITMAPFILEHEADER *) pbmpfileheader)->bfOffBits;
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    DDUtilLoadBitmap

Description:

    Creates a DirectDraw offscreen surface from a bitmap resource.

Return Value:

    On success, returns a pointer to the newly created surface.  On
    failure, returns NULL.

-------------------------------------------------------------------*/
extern "C" LPDIRECTDRAWSURFACE 
DDUtilLoadBitmap (
    HINSTANCE hinstApp,     // instance handle of the app
    LPDIRECTDRAW pdd,       // pointer to app's DirectDraw object interface
    LPCTSTR szBitmap)       // name of RCDATA resource in RC file
{
    DDSURFACEDESC       ddsd;
    LPDIRECTDRAWSURFACE pddsNew;
    HRESULT             hr;
    BITMAPFILEHEADER    *pbmpfileheader;
    BITMAPINFOHEADER    bmpinfoheader;

    // Obtain a pointer to the raw data for the bitmap file which is
    // in the resource section of our app.  The first structure in any
    // .BMP file is a BITMAPFILEHEADER.
    pbmpfileheader = (BITMAPFILEHEADER *) GetPointerToBitmapFile (hinstApp, szBitmap);
    if (pbmpfileheader == NULL) {
        return NULL;
    }

    // The next structure in the file is a BITMAPINFOHEADER.  We do a memcpy
    // to a local structure in order to avoid DWORD-alignment problems on the
    // SH3 processor.
    memcpy (&bmpinfoheader, (pbmpfileheader + 1), sizeof(bmpinfoheader));

    // Create an offscreen DirectDraw surface of the same size as the bitmap.
    memset(&ddsd, 0, sizeof(ddsd));
    ddsd.dwSize = sizeof(ddsd);
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
    ddsd.dwWidth = bmpinfoheader.biWidth;
    ddsd.dwHeight = bmpinfoheader.biHeight;

    hr = pdd->CreateSurface (&ddsd, &pddsNew, NULL);
    if (hr != DD_OK) {
        OutputDebugString (TEXT("Could not create offscreen surface.\r\n"));
        return NULL;
    }

    // Copy the contents of the bitmap into the newly created surface.
    if (!DDUtilCopyBitmap(hinstApp, pddsNew, szBitmap, 0, 0,
                          bmpinfoheader.biWidth, bmpinfoheader.biHeight)) {

        // Copying the bitmap failed.  Release the newly created surface.
        pddsNew->Release ();
        return NULL;
    }

    return pddsNew;
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    DDUtilCopyBitmap

Description:

    Copies the image in a bitmap resource into a DirectDraw surface.
    This routine can handle same->same or 8bpp->16bpp.  It is not
    optimized at all, and therefore should not be called frequently.
    Pass in zero for dxWidth or dyHeight to copy the entire bitmap.

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
extern "C" BOOL 
DDUtilCopyBitmap (
    HINSTANCE hinstApp,             // instance handle of the app
    LPDIRECTDRAWSURFACE pddsDest,   // destination surface to copy bitmap
    LPCTSTR szBitmap,               // name of RCDATA resource in RC file
    unsigned int xSrc,              // x-coordinate of upper-left corner in bitmap
    unsigned int ySrc,              // y-coordinate of upper-left corner in bitmap
    unsigned int dxWidth,           // number of pixels along x-axis to copy to surface
    unsigned int dyHeight)          // number of pixels along y-axis to copy to surface
{
    DDSURFACEDESC       ddsd;
    DDCOLORKEY          ddck;
    HRESULT             hr;
    HRESULT             hrColorKey;
    unsigned int        x, y;
    BITMAPFILEHEADER    *pbmpfileheader;
    BITMAPINFOHEADER    *pbmpinfoheader;
    BITMAPINFOHEADER    bmi;
    RGBQUAD             *pbmiColors;
    RGBQUAD             argb[256];
    BYTE                *pSourceBits;
    BYTE                *pDestBits;

    // Get source and destination bit depths.
    #define bppSource       (bmi.biBitCount)
    #define bppDest         (ddsd.ddpfPixelFormat.dwRGBBitCount)

    // Get source and destination strides.
    #define dwSourceStride  ((unsigned int) (((bmi.biWidth * bppSource / 8) + 3) & (~3)))
    #define dwDestStride    ((unsigned int) (ddsd.lPitch))

    // Get source and destination bitmap widths.
    #define dwSourceWidth   ((unsigned int) (bmi.biWidth))
    #define dwDestWidth     ((unsigned int) (ddsd.dwWidth))

    // Get source and destination bitmap heights.
    #define dwSourceHeight  ((unsigned int) (bmi.biHeight))
    #define dwDestHeight    ((unsigned int) (ddsd.dwHeight))

    // Make sure this surface is restored.
    pddsDest->Restore();

    // Obtain a pointer to the raw data for the bitmap file which is
    // in the resource section of our app.  The first structure in any
    // .BMP file is a BITMAPFILEHEADER.
    pbmpfileheader = (BITMAPFILEHEADER *) GetPointerToBitmapFile (hinstApp, szBitmap);
    if (pbmpfileheader == NULL) {
        return FALSE;
    }

    // The next structure in the file is a BITMAPINFOHEADER.
    pbmpinfoheader = (BITMAPINFOHEADER *) (pbmpfileheader + 1);

    // We copy the structure into a local variable to avoid DWORD-alignment
    // problems on some processors.
    memcpy (&bmi, pbmpinfoheader, sizeof(BITMAPINFOHEADER));

    // If the source bitmap happens to be 8bpp, this is where the colortable
    // would be located.
    pbmiColors = (RGBQUAD *) (pbmpinfoheader + 1);

    // Get a pointer to the actual pixel data in the source bitmap.
    pSourceBits = GetPointerToBitmapBits ((void *) pbmpfileheader);

    // Lock surface, get pointer to destination surface bits.
    ddsd.dwSize = sizeof(ddsd);
    hr = pddsDest->Lock (NULL, &ddsd, DDLOCK_WAIT, NULL);
    if (hr != DD_OK) {
        OutputDebugString (TEXT("Could not lock surface.\r\n"));
        return FALSE;
    }
    pDestBits = (BYTE *) ddsd.lpSurface;

    // Get the colorkey from the destination DDraw surface.  Use this
    // to set the alpha channel, if one exists.  That way, we can use
    // alpha-blended blts (hardware) instead of colorkey blts (software)
    // on the PowerVR architecture.
    hrColorKey = pddsDest->GetColorKey (DDCKEY_SRCBLT, &ddck);

    // If caller passed in zero for the width/height, use the width/height
    // of the source or destination surface, whichever is smaller.  __min
    // macro is from stdlib.h.
    if (dxWidth == 0) {
        dxWidth = __min(dwSourceWidth, dwDestWidth);
    }
    if (dyHeight == 0) {
        dyHeight = __min(dwSourceHeight, dwDestHeight);
    }

    // Verify that the dimensions of the blt are valid.
    if (((xSrc + dxWidth) > dwSourceWidth) ||
        ((ySrc + dyHeight) > dwSourceHeight) ||
        (dxWidth > dwDestWidth) ||
        (dyHeight > dwDestHeight)) {

        pddsDest->Unlock (ddsd.lpSurface);
        OutputDebugString (TEXT("Blt dimensions are invalid.\r\n"));
        return FALSE;
    }        

    // Adjust the source pointer according to the starting x, y position.
    pSourceBits += ((xSrc * bppSource / 8) + (ySrc * dwSourceStride));

    if (bppSource == bppDest) {

        // Source and destination bit depths are identical.

        for (y = 0 ; y < dyHeight ; y++) {

            // Copy a single row from source bitmap to dest surface.
            memcpy (pDestBits, pSourceBits, dxWidth * bppSource / 8);

            // Move pointers down one row each.
            pDestBits += dwDestStride;
            pSourceBits += dwSourceStride;

        }

    } else if ((bppSource == 8) && (bppDest == 16)) {
        
        BYTE        *pSourcePixel;
        WORD        *pDestPixel;

        // We can do an 8->16 blt, but it's going to be really really slow.  Also,
        // the only 16bpp formats we support are 5-6-5 and 5-5-5.

        // Again, we copy the entire colortable from the bitmap resource to
        // a local array to avoid DWORD-alignment problems on some processors.
        memcpy (argb, pbmiColors, 256 * sizeof(RGBQUAD));

        if ((ddsd.ddpfPixelFormat.dwRBitMask == 0xF800) &&
            (ddsd.ddpfPixelFormat.dwGBitMask == 0x07E0) &&
            (ddsd.ddpfPixelFormat.dwBBitMask == 0x001F)) {

            // We have a 5-6-5 format for the destination surface.

            // Loop through all rows.
            for (y = 0 ; y < dyHeight ; y++) {

                pSourcePixel = pSourceBits;
                pDestPixel = (WORD *) pDestBits;

                // Loop through all pixels in the row.
                for (x = 0 ; x < dxWidth ; x++) {
            
                    *pDestPixel = 
                        (((argb[*pSourcePixel].rgbRed) & 0xF8) << 8) |
                        (((argb[*pSourcePixel].rgbGreen) & 0xFC) << 3) |
                        (((argb[*pSourcePixel].rgbBlue) & 0xF8) >> 3);

                    pDestPixel++;
                    pSourcePixel++;    
                }

                // Move pointers down one row each.
                pDestBits += dwDestStride;
                pSourceBits += dwSourceStride;
            }

        } else if ((ddsd.ddpfPixelFormat.dwRBitMask == 0x7C00) &&
            (ddsd.ddpfPixelFormat.dwGBitMask == 0x03E0) &&
            (ddsd.ddpfPixelFormat.dwBBitMask == 0x001F)) {

            // We have a 5-5-5 format for the destination surface.

            // Loop through all rows.
            for (y = 0 ; y < dyHeight ; y++) {

                pSourcePixel = pSourceBits;
                pDestPixel = (WORD *) pDestBits;

                // Loop through all pixels in the row.
                for (x = 0 ; x < dxWidth ; x++) {
            
                    *pDestPixel = 
                        (((argb[*pSourcePixel].rgbRed) & 0xF8) << 7) |
                        (((argb[*pSourcePixel].rgbGreen) & 0xF8) << 2) |
                        (((argb[*pSourcePixel].rgbBlue) & 0xF8) >> 3);

                    if ((*pDestPixel != ddck.dwColorSpaceLowValue) ||
                        (hrColorKey != DD_OK))
                    {
                        // This pixel is not the color of the colorkey, or there
                        // is no colorkey set on this surface.  Set the alpha
                        // channel to opaque.
                        *pDestPixel |= 0x8000;
                    } 

                    pDestPixel++;
                    pSourcePixel++;    
                }

                // Move pointers down one row each.
                pDestBits += dwDestStride;
                pSourceBits += dwSourceStride;
            }

        } else {
            
            // We have an unsupported 16bpp format for destination surface.

            pddsDest->Unlock (ddsd.lpSurface);
            OutputDebugString (TEXT("16bpp formats other than 565 or 555 are not supported.\r\n"));
            return FALSE;
        }

    } else {

        // The only conversion blt we can do is 8->16.  The caller is requesting
        // something else.

        pddsDest->Unlock (ddsd.lpSurface);
        OutputDebugString (TEXT("Conversion blt not supported.\r\n"));
        return FALSE;
    }

    // Unlock the offscreen surface.
    hr = pddsDest->Unlock (ddsd.lpSurface);
    if (hr != DD_OK) {
        OutputDebugString (TEXT("Could not unlock surface.\r\n"));
        return FALSE;
    }

    // Success!
    return TRUE;
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    DDUtilLoadPalette

Description:

    Creates a DirectDraw palette object based on the colortable in a 
    bitmap resource.

Return Value:

    Returns pointer to newly created DirectDraw palette on success.
    NULL on failure.

-------------------------------------------------------------------*/
extern "C" LPDIRECTDRAWPALETTE
DDUtilLoadPalette (
    HINSTANCE hinstApp,     // instance handle of the app
    LPDIRECTDRAW pdd,       // pointer to app's DirectDraw object interface
    LPCTSTR szBitmap)       // name of RCDATA resource in RC file
{
    LPDIRECTDRAWPALETTE pddpal;
    int                 i;
    int                 iEntries;
    PALETTEENTRY        ape[256];
    HRESULT             hr;
    BITMAPFILEHEADER    *pbmpfileheader;
    BITMAPINFOHEADER    *pbmpinfoheader;
    BITMAPINFOHEADER    bmi;
    RGBQUAD             *prgbquad;
    RGBQUAD             argb[256];

    // Obtain a pointer to the raw data for the bitmap file which is
    // in the resource section of our app.  The first structure in any
    // .BMP file is a BITMAPFILEHEADER.
    pbmpfileheader = (BITMAPFILEHEADER *) GetPointerToBitmapFile (hinstApp, szBitmap);
    if (pbmpfileheader == NULL) {
        return NULL;
    }

    // The next structure in the file is a BITMAPINFOHEADER.
    pbmpinfoheader = (BITMAPINFOHEADER *) (pbmpfileheader + 1);
    
    // We copy the structure into a local variable to avoid DWORD-alignment
    // problems on some processors.
    memcpy (&bmi, pbmpinfoheader, sizeof(BITMAPINFOHEADER));

    // The bitmap must be 8bpp for this function to make any sense.
    if (bmi.biBitCount > 8) {
        OutputDebugString (TEXT("Can't create palette from a non-8bpp bitmap.\r\n"));
        return NULL;
    }

    // Figure out how many palette entries are actually in the bitmap.
    iEntries = (bmi.biClrUsed == 0) ? (1 << bmi.biBitCount) : (bmi.biClrUsed);

    // Find the color table.
    prgbquad = (RGBQUAD *) (pbmpinfoheader + 1);
    
    // Again, we copy the entire array locally to avoid DWORD-alignment
    // problems on some processors.
    memcpy (argb, prgbquad, iEntries * sizeof(RGBQUAD));

    // A DIB color table has its colors stored BGR not RGB, so we can't do
    // a simple memcpy.
    for (i = 0 ; i < iEntries ; i++) {
        ape[i].peRed   = argb[i].rgbRed;
        ape[i].peGreen = argb[i].rgbGreen;
        ape[i].peBlue  = argb[i].rgbBlue;
        ape[i].peFlags = 0;
    }

    // Set the remaining palette entries to black.
    for (i = iEntries ; i < 256 ; i++) {
        ape[i].peRed   = 0;
        ape[i].peGreen = 0;
        ape[i].peBlue  = 0;
        ape[i].peFlags = 0;
    }

    // Create the DirectDraw palette.
    hr = pdd->CreatePalette (DDPCAPS_8BIT, ape, &pddpal, NULL);
    if (hr != DD_OK) {
        OutputDebugString (TEXT("CreatePalette failed.\r\n"));
        return NULL;
    }

    // Return DirectDraw palette interface pointer.
    return pddpal;
}
