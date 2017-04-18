#include "stdafx.h"
#include "cgl.h"

//
// RGBA Palette support code
//
unsigned char CGL::m_threeto8[8] = {
    0, 0111>>1, 0222>>1, 0333>>1, 0444>>1, 0555>>1, 0666>>1, 0377
};
unsigned char CGL::m_twoto8[4] = {
   0, 0x55, 0xaa, 0xff
};
unsigned char CGL::m_oneto8[2] = {
    0, 255
};

int CGL::m_defaultOverride[13] = {
    0, 3, 24, 27, 64, 67, 88, 173, 181, 236, 247, 164, 91
};

PALETTEENTRY CGL::m_defaultPalEntry[20] = {
    { 0,   0,   0,    0 }, //0
    { 0x80,0,   0,    0 }, 
    { 0,   0x80,0,    0 }, 
    { 0x80,0x80,0,    0 }, 
    { 0,   0,   0x80, 0 },
    { 0x80,0,   0x80, 0 },
    { 0,   0x80,0x80, 0 },
    { 0xC0,0xC0,0xC0, 0 }, //7

    { 192, 220, 192,  0 }, //8
    { 166, 202, 240,  0 },
    { 255, 251, 240,  0 },
    { 160, 160, 164,  0 }, //11

    { 0x80,0x80,0x80, 0 }, //12
    { 0xFF,0,   0,    0 },
    { 0,   0xFF,0,    0 },
    { 0xFF,0xFF,0,    0 },
    { 0,   0,   0xFF, 0 },
    { 0xFF,0,   0xFF, 0 },
    { 0,   0xFF,0xFF, 0 },
    { 0xFF,0xFF,0xFF, 0 }  //19
  };

//
//
//
unsigned char CGL::ComponentFromIndex(int i, UINT nbits, UINT shift)
{
    unsigned char val = (unsigned char) (i >> shift);
    switch (nbits) {

    case 1:
        val &= 0x1;
        return m_oneto8[val];

    case 2:
        val &= 0x3;
        return m_twoto8[val];

    case 3:
        val &= 0x7;
        return m_threeto8[val];

    default:
        return 0;
    }
}

//
// CreateRGBPalette
//
BOOL CGL::CreatePalette()
{
	//
	// Check to see if we need a palette
	//
   PIXELFORMATDESCRIPTOR pfd;
   int n = GetPixelFormat(m_pdc->m_hDC);
   DescribePixelFormat(m_pdc->m_hDC, n, sizeof(PIXELFORMATDESCRIPTOR), &pfd);
	
	// Palette needed for color index mode.
	BOOL bColorIndex = (pfd.iPixelType & PFD_TYPE_COLORINDEX) ;
	// Palette needed for 8bpp DIBs. PFD_NEED_PALETTE is not set.
	BOOL b8bppDIB = (m_bDrawToBitmap) && (pfd.cColorBits == 8) ;
	if ( (pfd.dwFlags & PFD_NEED_PALETTE) || 
		 (b8bppDIB) ||
		 (bColorIndex))
	{
		TRACE0("Creating palette\r\n") ;
	    // allocate a log pal and fill it with the color table info
		int iPalSize = sizeof(LOGPALETTE) + 256 * sizeof(PALETTEENTRY) ;
      LOGPALETTE* pPal = (LOGPALETTE*) malloc(iPalSize);
		memset(pPal, 0, iPalSize) ;
		 
	   if (!pPal) 
	   {
	       TRACE("Out of memory for logpal");
	       return FALSE;
	   }
	   pPal->palVersion = 0x300; // Windows 3.0
	   pPal->palNumEntries = 256; // table size

		if (bColorIndex)
		{
			// Let user create palette for color index mode
			OnCreatePaletteCI(pPal) ;
		}
		else
		{
			//
			// Create RGB Palette
			//
			ASSERT( pfd.cColorBits == 8) ;
		   n = 1 << pfd.cColorBits;
		   for (int i=0; i<n; i++)
		   {
		        pPal->palPalEntry[i].peRed =
		                ComponentFromIndex(i, pfd.cRedBits, pfd.cRedShift);
		        pPal->palPalEntry[i].peGreen =
		                ComponentFromIndex(i, pfd.cGreenBits, pfd.cGreenShift);
		        pPal->palPalEntry[i].peBlue =
		                ComponentFromIndex(i, pfd.cBlueBits, pfd.cBlueShift);
		        pPal->palPalEntry[i].peFlags = 0;
		    }

			//
			// Fix up color table with system colors.
			//
		   if ((pfd.cColorBits == 8)                           &&
		       (pfd.cRedBits   == 3) && (pfd.cRedShift   == 0) &&
		       (pfd.cGreenBits == 3) && (pfd.cGreenShift == 3) &&
		       (pfd.cBlueBits  == 2) && (pfd.cBlueShift  == 6)
		      )
		   {
			   for (int j = 1 ; j <= 12 ; j++)
			          pPal->palPalEntry[m_defaultOverride[j]] = m_defaultPalEntry[j];
			}
		}	
	    // Delete any existing GDI palette
		if (m_pPal) delete m_pPal ;
		m_pPal = new CPalette ;

	   BOOL bResult = m_pPal->CreatePalette(pPal);
	   free (pPal);

		// Select and Realize Palette
		if (!m_bDrawToBitmap)	// BIT 
		{
	   		m_pOldPal = m_pdc->SelectPalette(m_pPal, 0);
	   		m_pdc->RealizePalette();
		}

	    return bResult;
	}
	else
		return FALSE ;
}
