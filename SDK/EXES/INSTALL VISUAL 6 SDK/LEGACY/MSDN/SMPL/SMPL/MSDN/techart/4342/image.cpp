#include "stdafx.h"
#include "cgl.h"
#include "image.h"

#include <math.h>

//
// RGB color structure that stores colors in R-G-B order in
// memory instead of the B-G-R format used by RGBTRIPLE.
//
typedef struct _CGLRGBTRIPLE { 
    BYTE rgbRed;
    BYTE rgbGreen;
  	BYTE rgbBlue;
} CGLRGBTRIPLE;

//
//	Constructor
//
CGLImage::CGLImage()
{
	m_iHeight = 0 ;
	m_iWidth = 0 ;
	m_pBits = NULL ;
}

void CGLImage::SpecialCreate(int w, int h, void* pBits)
{
	m_iHeight = h ;
	m_iWidth = w ;
	m_PixelFormat = GL_RGB ;

	int iImageSize = m_iWidth * m_iHeight * sizeof(CGLRGBTRIPLE) ;
	m_pBits = malloc(iImageSize) ;
	memcpy(m_pBits, pBits, iImageSize) ;
}
//
// Destructor
//
CGLImage::~CGLImage()
{
	CleanUp() ;
}

//
// CleanUp: Allows loading an image without deleting object.
//
void CGLImage::CleanUp()
{
	//
	// Is an image already loaded?
	//
	if (m_pBits) 
	{
		// cleanup previous image
		free(m_pBits);		
		m_pBits = NULL ;
		m_iHeight = 0 ;
		m_iWidth = 0 ;
	}
}

//
// Load Windows DIB using filename.
//
BOOL CGLImage::Load(LPCTSTR filename, TRANSLATEMETHOD enumMethod)
{
	CleanUp() ;

	//
	// Create a DIB using Nigel's Animation Library/
	//
	CDIB aDib ;
	BOOL bResult = aDib.Load(filename) ;
	if (!bResult) return FALSE ;
   
	//
	// Translate Dib using one of three methods.
	//
 	Translate(aDib, enumMethod) ;

	return TRUE ;
}

//
// Load Windows DIB using resource id.
// The DIB is placed in the .rc2 file with the name DIB.
// Ex. IDR_SPLASH DIB res\splash.dib. 
// See Nigel Thompson's Animate library.
//
BOOL CGLImage::Load(WORD wResId, TRANSLATEMETHOD enumMethod)
{
	CleanUp() ;

	//
	// Create a DIB using Nigel's Animation Library
	//
	CDIB aDib ;
	BOOL bResult = aDib.Load(wResId) ;
	if (!bResult) return FALSE ;
	
	//
	// Translate Dib using one of three methods.
	//
 	Translate(aDib, enumMethod) ;

	return TRUE ;
}


//
// Translate: Select the translate method and translate.
//
void CGLImage::Translate(CDIB& aDib, TRANSLATEMETHOD enumMethod)
{
 	// Get width and heigth in pixels.
	m_iWidth 		= aDib.GetWidth() ;	 
	m_iHeight 		= aDib.GetHeight() ;

	//
	// Create a palette from the colors in the dib.
	//
	CDIBPal aPalSrc ;
	aPalSrc.Create(&aDib) ;

	//
	// Translate using one of three methods.
	//
 	m_enumMethod = enumMethod;
	switch(m_enumMethod)
	{
	case TRANS_GDI:
		m_PixelFormat = GL_RGBA ;		// Uses a 32bpp image format.
		TranslateByGDI(aDib, aPalSrc) ;
		break ;
	case TRANS_BOTH:
		m_PixelFormat = GL_RGB ;
		TranslateByBoth(aDib, aPalSrc) ;	
		break;
	case TRANS_DIY:
	default: 
		m_PixelFormat = GL_RGB ;
		TranslateByYourself(aDib, aPalSrc) ;
	}

}

//
// TranslateByYourself: Translation code is all here.
//
void CGLImage::TranslateByYourself(CDIB& aDib, CDIBPal& aPalSrc)
{
	int nBitsPerPix = aDib.GetBitsPerPixel() ;
	void* pBits 	= aDib.GetBitsAddress();
	int storageWidth = aDib.GetStorageWidth() ; // storage width is in BYTES!

	// Allocate space for the resulting image.                            
	CGLRGBTRIPLE* pGLRGB = 
			(CGLRGBTRIPLE*)malloc(m_iWidth*m_iHeight*sizeof(CGLRGBTRIPLE));
	CGLRGBTRIPLE* pDest = pGLRGB ;

	switch(nBitsPerPix)
	{
	case 24:
		{
			// Translate from 24 bpp.
			RGBTRIPLE* pSrc = (RGBTRIPLE*) pBits ;
			int widthDiff = storageWidth - m_iWidth*sizeof(RGBTRIPLE) ;
			for(int j = 0 ; j < m_iHeight ; j++)
			{
				for(int i = 0 ; i < m_iWidth ; i++)
				{
					// Change from B-G-R to R-G-B format.
					pDest->rgbRed = pSrc->rgbtRed ;
					pDest->rgbGreen = pSrc->rgbtGreen ;
					pDest->rgbBlue = pSrc->rgbtBlue ;
					pDest++ ;
					pSrc++ ;			
				}
				// Remove DWORD alignment padding.
				pSrc = (RGBTRIPLE*)( (BYTE*)pSrc + widthDiff) ;
			}
		}
		break ;
	case 8:
		{
			BYTE* pSrc = (BYTE*) pBits ;
			RGBQUAD* pClrTab = aDib.GetClrTabAddress() ;
			int widthDiff = storageWidth - m_iWidth ;
			for(int j = 0 ; j < m_iHeight ; j++)
			{
				for(int i = 0 ; i < m_iWidth ; i++)
				{
					// Lookup RGBQUAD at index in the source.
					// Change to CGLRGBTRIPLE.
					pDest->rgbRed = pClrTab[*pSrc].rgbRed ;
					pDest->rgbGreen = pClrTab[*pSrc].rgbGreen ;
					pDest->rgbBlue = pClrTab[*pSrc].rgbBlue ;
					pDest++ ;
					pSrc++ ;			
				}
				// Remove DWORD alignment padding.
				pSrc += widthDiff ;
			}
		}
		break ;
	case 4:
		{
			BYTE* pSrc2 = (BYTE*) pBits ;
			BYTE* pSrc;
			BYTE bySrc ;
			RGBQUAD* pClrTab = aDib.GetClrTabAddress() ;
			for(int j = 0 ; j < m_iHeight ; j++)
			{
				int iPixelCount = 0 ;
				pSrc = pSrc2 ;
				for(int i = 0 ; i < storageWidth ; i++)
				{
					bySrc = ((*pSrc) >> 4) & 15;
					pDest->rgbRed 	= pClrTab[bySrc].rgbRed ;
					pDest->rgbGreen = pClrTab[bySrc].rgbGreen ;
					pDest->rgbBlue 	= pClrTab[bySrc].rgbBlue ;
					pDest++ ;							
					iPixelCount++ ;
					if (iPixelCount >= m_iWidth) break ;

					bySrc = (*pSrc) & 15;
					pDest->rgbRed 	= pClrTab[bySrc].rgbRed ;
					pDest->rgbGreen = pClrTab[bySrc].rgbGreen ;
					pDest->rgbBlue 	= pClrTab[bySrc].rgbBlue ;
					pDest++ ; 
					pSrc++ ;
					iPixelCount++ ;
					if (iPixelCount >= m_iWidth) break ;
				}
				pSrc2 += storageWidth ;
			}
		}
		break ;
	default:
		ASSERT(0) ;
	}

	// Setup Bits to point to memory we allocated.
	m_pBits = (BYTE*)pGLRGB ;	
}

//
// TranslateByGDI: Translate Using GDI.
//
void CGLImage::TranslateByGDI(CDIB& aDib, CDIBPal& aPalSrc)
{
	//
	// Allocate memory for new DIB section header.
	// Include room for 3 RGBQUAD color masks. BITMAPINFO already includes
	// one RGBQUAD.
	//
	const int BITMAPINFO_QUAD_SIZE = sizeof(BITMAPINFO) + 2 * sizeof(RGBQUAD);
	BYTE* abBitmapInfo[BITMAPINFO_QUAD_SIZE] ;
    BITMAPINFO* pBMI = (BITMAPINFO*) abBitmapInfo;
    memset(pBMI, 0, BITMAPINFO_QUAD_SIZE );

    // fill in the header info 
    pBMI->bmiHeader.biSize 			= sizeof(BITMAPINFOHEADER);
    pBMI->bmiHeader.biWidth 		= m_iWidth;
    pBMI->bmiHeader.biHeight 		= m_iHeight;
    pBMI->bmiHeader.biPlanes 		= 1;
    pBMI->bmiHeader.biBitCount 		= 32 ; 			 // Must use 32 bpps 
    pBMI->bmiHeader.biCompression  	= BI_BITFIELDS ; // to use this flag.

	//
	// Rearrange RGB component storage from BGR to RGB.
	// Does not work on Windows 95.
	//
	pBMI->bmiColors[0].rgbBlue 	= 0xff ; // Store red in blue's normal position.
	pBMI->bmiColors[1].rgbGreen = 0xff ; // Green stays same.
	pBMI->bmiColors[2].rgbRed 	= 0xff ; // Store blue in red's normal position.

	//
	// Create the new 32 bpp DIB section.
	//
    CDC dc;
    dc.CreateCompatibleDC(NULL);
	BYTE* pBits ;
    HBITMAP hbmBuffer = CreateDIBSection(dc.GetSafeHdc(),
                                   pBMI,
                                   DIB_RGB_COLORS,
                                   (VOID **) &pBits,
                                   NULL,
                                   0);
	
	// Select DIB into DC.
    HBITMAP hbmOld = (HBITMAP)::SelectObject(dc.GetSafeHdc(), hbmBuffer);

	// Blt the Windows DIB into our new DIB    
   	dc.SelectPalette(&aPalSrc,0) ;
	dc.RealizePalette() ;
	aDib.Draw(&dc,0,0) ; // Use Nigel's Animation class.
   	GdiFlush() ;

	//
	// Copy the bits out of the DIB section and into a block of memory pointed to by m_pBits.
	// This allows us to delete the DIB section since we don't need it.
	// Its possible to keep the DIB section around and use pBits directly.
	// Copying the bits out into a new block of memory makes TranslateByGDI parallel 
	// TranslateByYourself and TranslateByBoth resulting in a simpler CGLImage class.
	//
	int iImageSize = m_iWidth * m_iHeight * sizeof(RGBQUAD) ;
	m_pBits = malloc(iImageSize) ;
	memcpy(m_pBits, pBits, iImageSize) ;

	//
	// Get rid of all the GDI stuff.
	//
    if (hbmOld)
        (HBITMAP)::SelectObject(dc.GetSafeHdc(), hbmOld);

	DeleteObject(hbmBuffer) ;
}


//
// TranslateByBoth: Uses GDI to translate from ? bpp to 32 bpps.
// Uses my own code to translate from 32 bpps in B-G-R format to
// 24 bpp in R-G-B format. 
//
void CGLImage::TranslateByBoth(CDIB& aDib, CDIBPal& aPalSrc)
{
	TRACE0("TranslateByBoth\r\n") ;
	//
	// Allocate memory for new DIB section. 
	// No color table is needed.
	//
	const int BITMAPINFOHEADER_SIZE = sizeof(BITMAPINFOHEADER) ;
	BYTE* abBitmapInfo[BITMAPINFOHEADER_SIZE] ;
    BITMAPINFOHEADER* pBMIH = (BITMAPINFOHEADER*)abBitmapInfo;
    memset(pBMIH, 0, BITMAPINFOHEADER_SIZE);

    // fill in the header info 
    pBMIH->biSize 			= sizeof(BITMAPINFOHEADER);
    pBMIH->biWidth 			= m_iWidth;
    pBMIH->biHeight 		= m_iHeight;
    pBMIH->biPlanes 		= 1;
    pBMIH->biBitCount 		= 32 ; // Use 32 bpp to avoid boundary alignment issues.
    pBMIH->biCompression  	= BI_RGB ; 

	//
	// Create the new 32 bpp DIB section.
	//
    CDC dc;
    dc.CreateCompatibleDC(NULL);
	BYTE* pBits ;
    HBITMAP hbmBuffer = CreateDIBSection(dc.GetSafeHdc(),
                                   (BITMAPINFO*)pBMIH,
                                   DIB_RGB_COLORS,
                                   (VOID **) &pBits,
                                   NULL,
                                   0);
	// Select DIB into DC.
    HBITMAP hbmOld = (HBITMAP)::SelectObject(dc.GetSafeHdc(), hbmBuffer);
   
	// Blt the Windows DIB into our new DIB    
   	dc.SelectPalette(&aPalSrc,0) ;
	dc.RealizePalette() ;
	aDib.Draw(&dc,0,0) ;
   	GdiFlush() ;

	//
	// Copy the bits out of the DIB Section. 
	// Change from 32 bpp BGR to 24 bpp RGB.
	//
	int iImageSize = m_iWidth * m_iHeight * sizeof(CGLRGBTRIPLE) ;
	m_pBits = malloc(iImageSize) ;

	RGBQUAD* pSrc = (RGBQUAD*)pBits ;
	CGLRGBTRIPLE* pDest = (CGLRGBTRIPLE*) m_pBits ;
	for (int i = 0 ; i < m_iWidth*m_iHeight ; i++)
	{
		pDest->rgbRed = pSrc->rgbRed ;
		pDest->rgbGreen = pSrc->rgbGreen ;
		pDest->rgbBlue = pSrc->rgbBlue ;
		pDest++ ;
		pSrc++ ;
	}

	//
	// Get rid of all the GDI stuff.
	//
    if (hbmOld)
        (HBITMAP)::SelectObject(dc.GetSafeHdc(), hbmOld);

	DeleteObject(hbmBuffer) ;
}

//
//	DrawPixels
//
void CGLImage::DrawPixels(CGL* pGL)
{
	ASSERT((m_iWidth != 0) && (m_iHeight !=0)) ;
	ASSERT(m_pBits) ;
	pGL->MakeCurrent() ;
	GLint iAlign ;
	glGetIntegerv(GL_UNPACK_ALIGNMENT, &iAlign) ; 
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glDrawPixels(m_iWidth, m_iHeight, m_PixelFormat, GL_UNSIGNED_BYTE, m_pBits) ;

    glPixelStorei(GL_UNPACK_ALIGNMENT, iAlign);	
}

//
// TexMapScalePow2 - Scale image to power of 2 height and width
//
BOOL CGLImage::TexMapScalePow2(CGL* pGL)
{
    GLint glMaxTexDim ;
    double xPow2, yPow2;
    int ixPow2, iyPow2;
    int xSize2, ySize2;

    glGetIntegerv(GL_MAX_TEXTURE_SIZE, &glMaxTexDim);
	glMaxTexDim = min(128, glMaxTexDim);

    if (m_iWidth <= glMaxTexDim)
        xPow2 = log((double)m_iWidth) / log(2.0);
    else
        xPow2 = log((double)glMaxTexDim) / log(2.0);

    if (m_iHeight <= glMaxTexDim)
        yPow2 = log((double)m_iHeight) / log(2.0);
    else
        yPow2 = log((double)glMaxTexDim) / log(2.0);

    ixPow2 = (int)xPow2;
    iyPow2 = (int)yPow2;

    if (xPow2 != (double)ixPow2)
        ixPow2++;
    if (yPow2 != (double)iyPow2)
        iyPow2++;

    xSize2 = 1 << ixPow2;
    ySize2 = 1 << iyPow2;
	
    BYTE *pData = (BYTE*)malloc(xSize2 * ySize2 * 3 * sizeof(BYTE));
    if (!pData) return FALSE;

	pGL->MakeCurrent() ;
    gluScaleImage(GL_RGB, m_iWidth, m_iHeight,
                  GL_UNSIGNED_BYTE, m_pBits,
                  xSize2, ySize2, GL_UNSIGNED_BYTE,
                  pData);

	pGL->OutputGlError("CGLImage::TexMapScalePow2") ;

	free(m_pBits);
	m_pBits = pData; 
	m_iWidth = xSize2 ;
	m_iHeight = ySize2 ;

	return TRUE ;
} 

void CGLImage::TexImage2D(CGL* pGL)
{
	ASSERT((m_iWidth != 0) && (m_iHeight !=0)) ;
	ASSERT(m_pBits) ;

	// m_iWidth and m_iHeight must be power of 2.
	pGL->MakeCurrent() ;
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage2D( 	GL_TEXTURE_2D,			// Reserved 
    				0, 						// Level
    				3, 						// Compents for modulating and blending
    				m_iWidth, m_iHeight,    // Width and height
                  	0, 						// Border size
                  	m_PixelFormat, 			// GL_RGB or GL_RGBA
                  	GL_UNSIGNED_BYTE, 		// Data type of pixel values
                  	m_pBits					// Pixel values
                  	);    
	pGL->OutputGlError("CGLImage::TexImage2D") ;

}


/*
    if( textureQuality == TEX_HIGH ) {
        gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image->sizeX, image->sizeY,
             	 	  GL_RGB, GL_UNSIGNED_BYTE, image->data);
    }
    else {
*/
