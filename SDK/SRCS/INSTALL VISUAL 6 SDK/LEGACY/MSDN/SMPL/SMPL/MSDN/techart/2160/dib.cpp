// dib.cpp : implementation file
//
// Note that the color table is always 256 entries irrespective of being
// created from a file with less.
//

#include "stdafx.h"
#include "dib.h"
#include "malloc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDIB

IMPLEMENT_SERIAL(CDIB, CObject, 0 /* schema number*/ )

// Create a small DIB here so m_pDIB is always valid
CDIB::CDIB()
{
    m_pDIB = NULL;
    Create(16, 16);
}

CDIB::~CDIB()
{
    // free the memory
    if (m_pDIB != NULL) free(m_pDIB);
}

// Copy constructor
CDIB::CDIB(const CDIB &dib)
{
    if (dib.m_pDIB == NULL) {
        m_pDIB = NULL;
    } else {
        m_pDIB = (LPBYTE) malloc(_msize(dib.m_pDIB));
        memcpy(m_pDIB, dib.m_pDIB, _msize(dib.m_pDIB));
    }
}

// assignment operator
CDIB &CDIB::operator=(const CDIB &dib)
{
    // delete any existing stuff (Don't reuse since we might
    // waste a lot of memory)
    if (m_pDIB) free(m_pDIB);
    // create the new stuff
    m_pDIB = (LPBYTE) malloc(_msize(dib.m_pDIB));
    memcpy(m_pDIB, dib.m_pDIB, _msize(dib.m_pDIB));
    return *this;
}

/////////////////////////////////////////////////////////////////////////////
// CDIB serialization

// DIB is stored as a DWORD size value followed by the bits of the 
// packed DIB structure.
void CDIB::Serialize(CArchive& ar)
{
    DWORD dwSize;

    if (ar.IsStoring())
    {
        if (!m_pDIB) return; // nothing to store
        dwSize = _msize(m_pDIB); // size of block
        ASSERT(dwSize);
        ar << dwSize;
        ar.Write(m_pDIB, dwSize);
    }
    else
    {
        // get the block size
        ar >> dwSize;
        if (dwSize == 0) return; // nothing to load
        // allocate the memory
        m_pDIB = (LPBYTE) malloc(dwSize);
        if (!m_pDIB) {
            TRACE("Out of memory for DIB");
            return;
        }
        DWORD dw = ar.Read(m_pDIB, dwSize);
        if (dw != dwSize) {
            TRACE("Error reading DIB");
        }
    }
}

/////////////////////////////////////////////////////////////////////////////
// Private functions

static BOOL IsWinDIB(LPBITMAPINFOHEADER pBIH)
{
    ASSERT(pBIH);
    if (pBIH->biSize != sizeof(BITMAPINFOHEADER)) {
        return FALSE;
    }
    return TRUE;
}

static int NumDIBColorEntries(LPBITMAPINFO pBmpInfo) 
{
    LPBITMAPINFOHEADER pBIH;
    LPBITMAPCOREHEADER pBCH;
    int iColors, iBitCount;

    ASSERT(pBmpInfo);

    pBIH = &(pBmpInfo->bmiHeader);
    pBCH = (LPBITMAPCOREHEADER) pBIH;

    // start off by assuming the color table size from
    // the bit per pixel field
    if (IsWinDIB(pBIH)) {
        iBitCount = pBIH->biBitCount;
    } else {
        iBitCount = pBCH->bcBitCount;
    }

    switch (iBitCount) {
    case 1:
        iColors = 2;
        break;
    case 4:
        iColors = 16;
        break;
    case 8:
        iColors = 256;
        break;
    case 24:
    default:
        iColors = 0;
        break;
    }

    // If this is a Windows DIB, then the color table length
    // is determined by the biClrUsed field
    if (IsWinDIB(pBIH)) {
        if (pBIH->biClrUsed != 0) {
            iColors = pBIH->biClrUsed;
        }
    }

    return iColors;
}


/////////////////////////////////////////////////////////////////////////////
// CDIB commands

// Load a DIB from an open file.
// Note that we always create a 256 color table even if the color
// table in the file has less entries
BOOL CDIB::Load(CFile *fp)
{
    BOOL bIsPM = FALSE;
    LPBITMAPINFO pBmpInfo = NULL;

    // read the file header to get the file size and to
    // find where the bits start in the file
    BITMAPFILEHEADER BmpFileHdr;
    int iBytes;
    iBytes = fp->Read(&BmpFileHdr, sizeof(BmpFileHdr));
    if (iBytes != sizeof(BmpFileHdr)) {
        TRACE("Failed to read file header");
        goto $abort;
    }

    // check we have the magic 'BM' at the start
    if (BmpFileHdr.bfType != 0x4D42) {
        TRACE("Not a bitmap file");
        goto $abort;
    }

    // make a wild guess that the file is in Windows DIB
    // format and read the BITMAPINFOHEADER.  If it turns
    // out to be a PM DIB file we'll convert it later.
    BITMAPINFOHEADER BmpInfoHdr;
    iBytes = fp->Read(&BmpInfoHdr, sizeof(BmpInfoHdr)); 
    if (iBytes != sizeof(BmpInfoHdr)) {
        TRACE("Failed to read BITMAPINFOHEADER");
        goto $abort;
    }

    // check we got a real Windows DIB file
    if (BmpInfoHdr.biSize != sizeof(BITMAPINFOHEADER)) {
        if (BmpInfoHdr.biSize != sizeof(BITMAPCOREHEADER)) {
            TRACE(" File is not Windows or PM DIB format");
            goto $abort;
        }

        // set a flag to convert PM file to Win format later
        bIsPM = TRUE;

        // back up the file pointer and read the BITMAPCOREHEADER
        // and create the BITMAPINFOHEADER from it
        fp->Seek(sizeof(BITMAPFILEHEADER), CFile::begin);
        BITMAPCOREHEADER BmpCoreHdr;
        iBytes = fp->Read(&BmpCoreHdr, sizeof(BmpCoreHdr)); 
        if (iBytes != sizeof(BmpCoreHdr)) {
            TRACE("Failed to read BITMAPCOREHEADER");
            goto $abort;
        }

        BmpInfoHdr.biSize = sizeof(BITMAPINFOHEADER);
        BmpInfoHdr.biWidth = (int) BmpCoreHdr.bcWidth;
        BmpInfoHdr.biHeight = (int) BmpCoreHdr.bcHeight;
        BmpInfoHdr.biPlanes = BmpCoreHdr.bcPlanes;
        BmpInfoHdr.biBitCount = BmpCoreHdr.bcBitCount;
        BmpInfoHdr.biCompression = BI_RGB;
        BmpInfoHdr.biSizeImage = 0;
        BmpInfoHdr.biXPelsPerMeter = 0;
        BmpInfoHdr.biYPelsPerMeter = 0;
        BmpInfoHdr.biClrUsed = 0;
        BmpInfoHdr.biClrImportant = 0;
    }

    // ok so we've got a real DIB file so work out 
    // how much memory we need for the BITMAPINFO
    // structure, color table and bits.  Allocate it,
    // copy the BmpInfoHdr we have so far 
    // and then read in the color table from the file
    int iColors;
    int iColorTableSize;
    int iFileColorTableSize;
    iColors = NumDIBColorEntries((LPBITMAPINFO) &BmpInfoHdr);
    // We always create a 256 color table. Reset the header
    BmpInfoHdr.biClrUsed = 256;
    iColorTableSize = 256 * sizeof(RGBQUAD);
    iFileColorTableSize = iColors * sizeof(RGBQUAD);
    int iBitsSize;
    int iBISize;
    int iSize;
    iBitsSize = BmpFileHdr.bfSize - BmpFileHdr.bfOffBits;
    iBISize = sizeof(BITMAPINFOHEADER)    
           + iColorTableSize;
    iSize = iBISize + iBitsSize;

    // allocate the memory
    pBmpInfo = (LPBITMAPINFO) malloc(iSize);
    if (!pBmpInfo) {
        TRACE("Out of memory for DIB");
        goto $abort;
    }
    // zero it for fun
    memset(pBmpInfo, 0, iSize);

    // copy the header we already have
    memcpy(pBmpInfo, &BmpInfoHdr, sizeof(BITMAPINFOHEADER));

    // now read the color table in from the file
    if (bIsPM == FALSE) {
        // read the color table from the file
        iBytes = fp->Read(((LPBYTE) pBmpInfo) + sizeof(BITMAPINFOHEADER),
                             iFileColorTableSize);
        if (iBytes != iFileColorTableSize) {
            TRACE("Failed to read color table");
            goto $abort;
        }
    } else {
        // read each PM color table entry in turn and convert it
        // to Win DIB format as we go
        LPRGBQUAD lpRGB;
        lpRGB = (LPRGBQUAD) ((LPBYTE) pBmpInfo + sizeof(BITMAPINFOHEADER));
        int i;
        RGBTRIPLE rgbt;
        for (i=0; i<iColors; i++) {
            iBytes = fp->Read(&rgbt, sizeof(RGBTRIPLE));
            if (iBytes != sizeof(RGBTRIPLE)) {
                TRACE("Failed to read RGBTRIPLE");
                goto $abort;
            }
            lpRGB->rgbBlue = rgbt.rgbtBlue;
            lpRGB->rgbGreen = rgbt.rgbtGreen;
            lpRGB->rgbRed = rgbt.rgbtRed;
            lpRGB->rgbReserved = 0;
            lpRGB++;
        }
    }

    // now we just have to read the bits from the file
    LPBYTE pBits;
    pBits = (LPBYTE) pBmpInfo 
          + sizeof(BITMAPINFOHEADER)
          + 256 * sizeof(RGBQUAD);

    // seek to the bits in the file
    fp->Seek(BmpFileHdr.bfOffBits, CFile::begin);

    // read the bits
    iBytes = fp->Read(pBits, iBitsSize);
    if (iBytes != iBitsSize) {
        TRACE("Failed to read bits");
        goto $abort;
    }

    // make sure it's a 256 color DIB
    if (pBmpInfo->bmiHeader.biBitCount != 8) {
        AfxMessageBox("Only 8 bit DIBs are supported");
        goto $abort;
    }

    // make sure it's not RLE
    if (pBmpInfo->bmiHeader.biCompression != BI_RGB) {
        AfxMessageBox("Compressed (RLE) DIBs are not supported");
        goto $abort;
    }

    // Everything went OK
    if (m_pDIB) free(m_pDIB);
    m_pDIB = (LPBYTE) pBmpInfo; // point to the start of the block
    return TRUE;
                
$abort: // something went wrong
    if (pBmpInfo) free(pBmpInfo);
    return FALSE;    
}

// Load a DIB from a disk file.  If no file name is given, show
// an open file dialog to get one.
BOOL CDIB::Load(LPSTR pszFileName)
{
    CString strFile;    

    if ((pszFileName == NULL) 
    ||  (strlen(pszFileName) == 0)) {

        // Show an open file dialog to get the name
        CFileDialog dlg   (TRUE,    // open
                           NULL,    // no default extension
                           NULL,    // no initial file name
                           OFN_FILEMUSTEXIST
                             | OFN_HIDEREADONLY,
                           "Image files (*.DIB, *.BMP)|*.DIB;*.BMP|All files (*.*)|*.*||");
        if (dlg.DoModal() == IDOK) {
            strFile = dlg.GetPathName();
        } else {
            return FALSE;
        }
    } else {
    
        // copy the supplied file path
        strFile = pszFileName;                    
    }

    // Try to open the file for read access
    CFile file;
    if (! file.Open(strFile,
                    CFile::modeRead | CFile::shareDenyWrite)) {
        AfxMessageBox("Failed to open file");
        return FALSE;
    }

    BOOL bResult = Load(&file);
    file.Close();
    if (!bResult) AfxMessageBox("Failed to load file");
    return bResult;
}


// Get a pointer to a pixel
// NOTE: DIB scan lines are DWORD aligned.  The scan line 
// storage width may be wider than the scan line image width
// so calc the storage width by rounding the image width 
// to the next highest dword value
LPBYTE CDIB::GetPixelAddress(int x, int y)
{
    LPBYTE p;
    int iWidth;

    // make sure it's in range and if not return zero
    if ((x >= DibWidth()) 
    || (y >= DibHeight())) {
        TRACE("Attempt to get out of range pixel addr");
        return NULL;
    }

    // Calculate the scan line storage width
    iWidth = GetStorageWidth();
    p = m_pDIB 
        + sizeof(BITMAPINFOHEADER)
        + 256 * sizeof(RGBQUAD)     // always 256 colors
        + (DibHeight()-y-1) * iWidth + x;
    return p;
}

// Get the width of one storage line which is the image width rounded
// up to the nearest DWORD
int CDIB::GetStorageWidth()
{
    return (DibWidth() + 3) & ~3;
}

// Get the value (color index) of a pixel
BYTE CDIB::GetPixelValue(int x, int y)
{
    LPBYTE p;

    p = GetPixelAddress(x, y);
    if (!p) {
        TRACE("Out of range pixel coords");
        return 0;
    }
    return *p;
}

// color (RGB value) of a pixel
COLORREF CDIB::GetPixelColor(int x, int y)
{
    BYTE value;
    RGBQUAD quad;
    COLORREF clr;

    ASSERT(m_pDIB);
     value = GetPixelValue(x, y);
    quad = GetClrTabAddress()[value];
    clr = RGB(quad.rgbRed, quad.rgbGreen, quad.rgbBlue);
    return clr;
}

// get a pointer to the color table
LPRGBQUAD CDIB::GetClrTabAddress()
{
    if (!m_pDIB) return NULL;
    return (LPRGBQUAD)(((LPBYTE)((LPBITMAPINFO)(m_pDIB))) + sizeof(BITMAPINFOHEADER));
}

// get the number of color table entries
int CDIB::GetNumClrEntries()
{
    return NumDIBColorEntries((LPBITMAPINFO) m_pDIB);
}

// Create a new empty DIB
BOOL CDIB::Create(int iWidth, int iHeight)
{
    int iSize;

    // delete any existing stuff
    if (m_pDIB) free(m_pDIB);

    // calc the size of the memory block
    iSize = sizeof(BITMAPINFOHEADER)    
           + 256 * sizeof(RGBQUAD)
           + ((iWidth + 3) & ~3) * iHeight;

    m_pDIB = (LPBYTE) malloc(iSize);
    if (!m_pDIB) {
        TRACE("Out of memory");
        return FALSE;
    }

    // fill in the header info
    LPBITMAPINFOHEADER pBI = (LPBITMAPINFOHEADER) m_pDIB;
    pBI->biSize = sizeof(BITMAPINFOHEADER);
    pBI->biWidth = iWidth;
    pBI->biHeight = iHeight;
    pBI->biPlanes = 1;
    pBI->biBitCount = 8;
    pBI->biCompression = BI_RGB;
    pBI->biSizeImage = 0;
    pBI->biXPelsPerMeter = 0;
    pBI->biYPelsPerMeter = 0;
    pBI->biClrUsed = 0;
    pBI->biClrImportant = 0;

    // create an arb color table (gray scale)
    LPRGBQUAD prgb = GetClrTabAddress();
    for (int i = 0; i < 256; i++) {
        prgb->rgbBlue = prgb->rgbGreen = prgb->rgbRed = (BYTE) i;
        prgb->rgbReserved = 0;
        prgb++;
    }

    // fill the bits with something to show of the current color table
    // NOTE: You can nuke this once everything works
    LPBYTE pBits;
    int x, y;
    for (y = 0; y < iHeight; y++) {
        pBits = GetPixelAddress(0, y);
        for (x = 0; x < iWidth; x++) {
            *pBits++ = (BYTE)(y * 256 / iHeight);
        }
    }
    return TRUE;
}

// get a pointer to the bits
LPBYTE CDIB::GetBitsAddress()
{
    ASSERT(m_pDIB);
    return m_pDIB
           + sizeof(BITMAPINFOHEADER)
           + 256 * sizeof(RGBQUAD);     // always 256 colors
}

// get the bounding rect
void CDIB::GetRect(LPRECT pRect)
{
    pRect->top = 0;
    pRect->left = 0;
    pRect->bottom = DibHeight();
    pRect->right = DibWidth();
}

// Map the colors in a DIB to a given palette.  We assume 256
BOOL CDIB::MapColorsToPalette(CPalette *pPal)
{
    if (!pPal) {
        TRACE("No palette to map to");
        return FALSE;
    }
    ASSERT(m_pDIB);
    LPRGBQUAD pctThis = GetClrTabAddress();
    ASSERT(pctThis);
    // build an index translation table to map this DIBs colors
    // to those of the reference DIB
    BYTE imap[256];
    int iChanged = 0; // for debugging only
    for (int i = 0; i < 256; i++) {
        imap[i] = (BYTE) pPal->GetNearestPaletteIndex(
                            RGB(pctThis->rgbRed,
                                pctThis->rgbGreen,
                                pctThis->rgbBlue));
        pctThis++;
        if (imap[i] != i) iChanged++; // for debugging
    }
    // now map the DIB bits
    LPBYTE pBits = GetBitsAddress();
    int iSize = GetStorageWidth() * DibHeight();
    while (iSize--) {
        *pBits = imap[*pBits];
        pBits++;
    }
    // Now reset the DIB color table so that its RGB values match
    // those in the palette
    PALETTEENTRY pe[256];
    pPal->GetPaletteEntries(0, 256, pe);
    pctThis = GetClrTabAddress();
    for (i = 0; i < 256; i++) {
        pctThis->rgbRed = pe[i].peRed;    
        pctThis->rgbGreen = pe[i].peGreen;    
        pctThis->rgbBlue = pe[i].peBlue;
        pctThis++;    
    }
    return TRUE;
}

// Draw the DIB to a given DC
void CDIB::Draw(CDC *pDC, int x, int y)
{
    StretchDIBits(pDC->GetSafeHdc(),
                  x,                        // dest x
                  y,                        // dest y
                  DibWidth(),                 // dest width
                  DibHeight(),                // dest height
                  0,                        // src x
                  0,                        // src y
                  DibWidth(),                 // src width
                  DibHeight(),                // src height
                  GetBitsAddress(),         // bits
                  GetBitmapInfoAddress(),   // BITMAPINFO
                  DIB_RGB_COLORS,           // options
                  SRCCOPY);                 // rop
}

// Copy a rectangle of the DIB to another DIB
void CDIB::CopyBits(CDIB *pdibDest, 
                    int xd, int yd,
                    int w, int h,
                    int xs, int ys,
                    COLORREF clrTrans)
{
    ASSERT(pdibDest);
    // test for silly cases
    if (w == 0 || h == 0) return;

    // get pointers to the start points in the source
    // and destination DIBs. Note that this will be the bottom left
    // corner of the DIB as the scan lines are reversed in memory
    BYTE *pSrc = GetPixelAddress(xs, ys + h - 1);
    ASSERT(pSrc);
    BYTE *pDest = pdibDest->GetPixelAddress(xd, yd + h - 1);
    ASSERT(pDest);

    // get the scan line widths of each DIB
    int iScanS = GetStorageWidth();
    int iScanD = pdibDest->GetStorageWidth();

    if (clrTrans == 0xFFFFFFFF) {
        // not transparent - copy the lines
        while (h--) {
            memcpy(pDest, pSrc, w);
            pSrc += iScanS;
            pDest += iScanD;
        }
    } else {
        // copy lines with transparency
        // BUGBUG: We only accept a PALETTEINDEX description
        // for the color right now
        ASSERT((clrTrans & 0xFF000000) == 0x01000000);
        BYTE bTransClr = LOBYTE(LOWORD(clrTrans));
        int iSinc = iScanS - w; // source inc value
        int iDinc = iScanD - w; // dest inc value
        int iCount;
        BYTE pixel;
        while (h--) {
            iCount = w;    // no of pixels to scan
            while (iCount--) {
                pixel = *pSrc++;
                // only copy pixel if not transparent
                if (pixel != bTransClr) {
                    *pDest++ = pixel;
                } else {
                    pDest++;
                }
            }
            // move on to the next line
            pSrc += iSinc;
            pDest += iDinc;
        }
    }
}

