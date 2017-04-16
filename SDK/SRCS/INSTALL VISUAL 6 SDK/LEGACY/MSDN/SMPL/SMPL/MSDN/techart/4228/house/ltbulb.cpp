// ltbulb.cpp

#include "stdafx.h"
#include "ltbulb.h"

CLightBulb::CLightBulb()
{
    m_pPal = NULL;
}

CLightBulb::~CLightBulb()
{
}

BOOL CLightBulb::Create(UINT uiResourceID, CPalette* pPal/*= NULL*/)
{
    // Try to load the image resource
    if (!m_dibImage.Load(uiResourceID)) return FALSE;

    // if a palette was supplied, map the image colors to the palette
    m_pPal = pPal;
    if (pPal) {
        m_dibImage.MapColorsToPalette(pPal);
    }

    return TRUE;
}

void CLightBulb::Draw(CDC* pDC, int x, int y)
{
    // Get a copy of the background the same size as the image
    int w = m_dibImage.GetWidth();
    int h = m_dibImage.GetHeight();
    CDIBSurface dsBuffer;
    dsBuffer.Create(w, h, m_pPal);
    CDC* pDCBuf = dsBuffer.GetDC();
    CPalette* pOldPal = NULL;
    if (m_pPal) {
        pDCBuf->SelectPalette(m_pPal, FALSE);
        pDCBuf->RealizePalette();
    }
    pDCBuf->BitBlt(0, 0,
                   w, h,
                   pDC,
                   x, y,
                   SRCCOPY);

    // Flush the GDI queue before we do a direct pixel operation
    ::GdiFlush();

    // Get the palette index of the top left pixel which defines
    // the image transparency color
    BYTE* pPixel = (BYTE*) m_dibImage.GetPixelAddress(0, 0);
    ASSERT(pPixel);

    // Draw the image transparently to the buffer
    m_dibImage.CopyBits(&dsBuffer,
                        0, 0,
                        w, h,
                        0, 0,
                        PALETTEINDEX(*pPixel));

    // Now copy the composite image back to the main DC
    pDC->BitBlt(x, y,
                w, h,
                pDCBuf,
                0, 0,
                SRCCOPY);

    // tidy up
    if (pOldPal) pDCBuf->SelectPalette(pOldPal, FALSE);

}
