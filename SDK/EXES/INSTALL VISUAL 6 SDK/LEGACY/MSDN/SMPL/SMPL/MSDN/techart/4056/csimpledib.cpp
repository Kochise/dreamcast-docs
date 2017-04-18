#include "stdafx.h"
#include "CSimpleDIB.h"

//
// Construction
//
CSimpleDIB::CSimpleDIB()
	: m_sizeDIB(0,0) 
{
	m_hbmp = NULL ;
	m_pBits = NULL ;
	m_pdc = NULL ;
}

//
// Destruction.
//
CSimpleDIB::~CSimpleDIB()
{
	destroy() ;
}


//
//	Destruction helper.
//
void CSimpleDIB::destroy()
{
    // Select the old bitmap back into the buffer DC.
    if (m_hbmOld)
    {
        ::SelectObject(m_pdc->GetSafeHdc(), m_hbmOld);
    }

	// Delete bitmap.
	if (m_hbmp) DeleteObject(m_hbmp);

	// Delete DC.
	if (m_pdc) delete m_pdc ;
}

//
// Create a DIB section cx X cy X ibitcount.
//
void CSimpleDIB::Create(int cx, int cy, int ibitcount) 
{
   ASSERT((ibitcount == 8) || (ibitcount == 16) || (ibitcount = 24))	;
   ASSERT(cx > 0);
   ASSERT(cy > 0);

   // Destroy parts of objects if we are recreating it.
   if ((m_pdc != NULL) || (m_hbmp != NULL)) destroy() ;

   // Save size for drawing later.
   m_sizeDIB.cx = cx ;
   m_sizeDIB.cy = cy ;

   // Create a BITMAPINFOHEADER structure to describe the DIB
   BITMAPINFOHEADER BIH ;
   int iSize = sizeof(BITMAPINFOHEADER) ;
   memset(&BIH, 0, iSize);

   // Fill in the header info.
   BIH.biSize = iSize;
   BIH.biWidth = cx;
   BIH.biHeight = cy;
   BIH.biPlanes = 1;
   BIH.biBitCount = ibitcount;
   BIH.biCompression = BI_RGB;

   // Create a new DC.
   m_pdc = new CDC ;
   m_pdc->CreateCompatibleDC(NULL);

   // Create the DIB section.
   m_hbmp = CreateDIBSection( m_pdc->GetSafeHdc(),
                           	(BITMAPINFO*)&BIH,
                           	DIB_PAL_COLORS,
                           	&m_pBits,
                           	NULL,
                           	0);

    ASSERT(m_hbmp);
    ASSERT(m_pBits);

    // Select the new bitmap into the buffer DC
    if (m_hbmp)
    {
        m_hbmOld = (HBITMAP)::SelectObject(m_pdc->GetSafeHdc(),
                                           m_hbmp);
    }
     
}

//
// BitBlt DIB section to the screen. Does not mess with the palette.
//
void CSimpleDIB::Draw(CDC* pdcDest, int x, int y) 
{
    // Note: you do not need to select the palette into
    // the memory DC because the DIB section is using palette
    // index values not colors
    pdcDest->BitBlt( x, y,
                     m_sizeDIB.cx, m_sizeDIB.cy,
                     m_pdc,
                     0, 0,
                     SRCCOPY);

}

//
// Set the color table in the DIB section.
//
void CSimpleDIB::SetPalette(CPalette* pPal)
{
    ASSERT(pPal);

    // get the colors from the palette
    int iColors = 0;
    pPal->GetObject(sizeof(iColors), &iColors);
    ASSERT(iColors > 0);
    PALETTEENTRY* pPE = new PALETTEENTRY[iColors];
    pPal->GetPaletteEntries(0, iColors, pPE);

    // Build a table of RGBQUADS
    RGBQUAD* pRGB = new RGBQUAD[iColors];
    ASSERT(pRGB);
    for (int i = 0; i < iColors; i++) {
        pRGB[i].rgbRed = pPE[i].peRed;
        pRGB[i].rgbGreen = pPE[i].peGreen;
        pRGB[i].rgbBlue = pPE[i].peBlue;
        pRGB[i].rgbReserved = 0;
    }
    
    ::SetDIBColorTable(m_pdc->GetSafeHdc(),
                       0, iColors,
                       pRGB);

    delete [] pRGB;
    delete [] pPE;
}
