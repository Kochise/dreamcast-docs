// dib.cpp : implementation file
//
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

// Create a small DIB here so m_pBMI and m_pBits are always valid
CDIB::CDIB()
{
    m_pBMI = NULL;
    m_pBits = NULL;
    m_bMyBits = TRUE;
    Create(16, 16);
}

CDIB::~CDIB()
{
    // free the memory
    if (m_pBMI != NULL) free(m_pBMI);
    if (m_bMyBits && (m_pBits != NULL)) free(m_pBits);
}

// Copy constructor
CDIB::CDIB(const CDIB &dib)
{
    m_pBMI = (BITMAPINFO *) malloc(_msize(dib.m_pBMI));
    memcpy(m_pBMI, dib.m_pBMI, _msize(dib.m_pBMI));
    m_pBits = (BYTE *)malloc(_msize(dib.m_pBits));
    memcpy(m_pBits, dib.m_pBits, _msize(dib.m_pBits));
    m_bMyBits = TRUE;
}

// assignment operator
CDIB &CDIB::operator=(const CDIB &dib)
{
    // delete any existing stuff (Don't reuse since we might
    // waste a lot of memory)
    if (m_pBMI != NULL) free(m_pBMI);
    if (m_bMyBits && (m_pBits != NULL)) free(m_pBits);
    // create the new stuff
    m_pBMI = (BITMAPINFO *) malloc(_msize(dib.m_pBMI));
    memcpy(m_pBMI, dib.m_pBMI, _msize(dib.m_pBMI));
    m_pBits = (BYTE *)malloc(_msize(dib.m_pBits));
    memcpy(m_pBits, dib.m_pBits, _msize(dib.m_pBits));
    m_bMyBits = TRUE;
    return *this;
}

/////////////////////////////////////////////////////////////////////////////
// CDIB serialization

// DIB is stored as a standard Windows bitmap file 
void CDIB::Serialize(CArchive& ar)
{
    ar.Flush();
    CFile *fp = ar.GetFile();

    if (ar.IsStoring()) {
        Save(fp);
    } else {
        Load(fp);
    }
}

/////////////////////////////////////////////////////////////////////////////
// Private functions

static BOOL IsWinDIB(BITMAPINFOHEADER *pBIH)
{
    ASSERT(pBIH);
    if (((BITMAPCOREHEADER *)pBIH)->bcSize == sizeof(BITMAPCOREHEADER)) {
        return FALSE;
    }
    return TRUE;
}

static int NumDIBColorEntries(LPBITMAPINFO pBmpInfo) 
{
    BITMAPINFOHEADER *pBIH;
    BITMAPCOREHEADER *pBCH;
    int iColors, iBitCount;

    ASSERT(pBmpInfo);

    pBIH = &(pBmpInfo->bmiHeader);
    pBCH = (BITMAPCOREHEADER *) pBIH;

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
BOOL CDIB::Load(CFile *fp)
{
    BOOL bIsPM = FALSE;
    BITMAPINFO *pBmpInfo = NULL;
    BYTE *pBits = NULL;

    // get the current file position
    DWORD dwFileStart = fp->GetPosition();

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
        fp->Seek(dwFileStart + sizeof(BITMAPFILEHEADER), CFile::begin);
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
    // structure, color table and then for the bits.  
    // Allocate the memory blocks.
    // copy the BmpInfoHdr we have so far 
    // and then read in the color table from the file.
    int iColors;
    int iColorTableSize;
    iColors = NumDIBColorEntries((LPBITMAPINFO) &BmpInfoHdr);
    iColorTableSize = iColors * sizeof(RGBQUAD);
    int iBitsSize;
    int iBISize;
    iBISize = sizeof(BITMAPINFOHEADER)    
           + iColorTableSize;
    iBitsSize = BmpFileHdr.bfSize - 
                BmpFileHdr.bfOffBits;

    // allocate the memory for the header
    pBmpInfo = (LPBITMAPINFO) malloc(iBISize);
    if (!pBmpInfo) {
        TRACE("Out of memory for DIB header");
        goto $abort;
    }

    // copy the header we already have
    memcpy(pBmpInfo, &BmpInfoHdr, sizeof(BITMAPINFOHEADER));

    // now read the color table in from the file
    if (bIsPM == FALSE) {
        // read the color table from the file
        iBytes = fp->Read(((LPBYTE) pBmpInfo) + sizeof(BITMAPINFOHEADER),
                             iColorTableSize);
        if (iBytes != iColorTableSize) {
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

    // allocate the memory for the bits
    // and read the bits from the file
    pBits = (BYTE *) malloc(iBitsSize);
    if (!pBits) {
        TRACE("Out of memory for DIB bits");
        goto $abort;
    }

    // seek to the bits in the file
    fp->Seek(dwFileStart + BmpFileHdr.bfOffBits, CFile::begin);

    // read the bits
    iBytes = fp->Read(pBits, iBitsSize);
    if (iBytes != iBitsSize) {
        TRACE("Failed to read bits");
        goto $abort;
    }

    // Everything went OK
    if (m_pBMI != NULL) free(m_pBMI);
    m_pBMI = pBmpInfo; 
    if (m_bMyBits && (m_pBits != NULL)) free (m_pBits);
    m_pBits = pBits;
    m_bMyBits = TRUE;
    return TRUE;
                
$abort: // something went wrong
    if (pBmpInfo) free(pBmpInfo);
    if (pBits) free (pBits);
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

// Save a DIB to a disk file
// This is somewhat simplistic because we only deal with 256 color DIBs
// and we always write a 256 color table
BOOL CDIB::Save(CFile *fp)
{
    BITMAPFILEHEADER bfh;

    // construct the file header
    bfh.bfType = 0x4D42; // 'BM'
    bfh.bfSize = 
        sizeof(BITMAPFILEHEADER) +
        sizeof(BITMAPINFOHEADER) +
        256 * sizeof(RGBQUAD) +
        GetStorageWidth() * DibHeight();
    bfh.bfReserved1 = 0;
    bfh.bfReserved2 = 0;
    bfh.bfOffBits =
        sizeof(BITMAPFILEHEADER) +
        sizeof(BITMAPINFOHEADER) +
        256 * sizeof(RGBQUAD);

    // write the file header
    int iSize = sizeof(bfh);
    TRY {
        fp->Write(&bfh, iSize);
    } CATCH(CFileException, e) {
        TRACE("Failed to write file header");
        return FALSE;
    } END_CATCH

    // write the BITMAPINFO
    // Note: we assume there are always 256 colors in the
    // color table
    ASSERT(m_pBMI);
    iSize = 
        sizeof(BITMAPINFOHEADER) +
        256 * sizeof(RGBQUAD);
    TRY {
        fp->Write(m_pBMI, iSize);
    } CATCH(CFileException, e) {
        TRACE("Failed to write BITMAPINFO");
        return FALSE;
    } END_CATCH

    // write the bits
    iSize = GetStorageWidth() * DibHeight();
    TRY {
        fp->Write(m_pBits, iSize);
    } CATCH(CFileException, e) {
        TRACE("Failed to write bits");
        return FALSE;
    } END_CATCH

    return TRUE;
}

// Save a DIB to a disk file.  If no file name is given, show
// a save file dialog to get one.
BOOL CDIB::Save(LPSTR pszFileName)
{
    CString strFile;    

    if ((pszFileName == NULL) 
    ||  (strlen(pszFileName) == 0)) {

        // Show a save file dialog to get the name
        CFileDialog dlg   (FALSE,   // save
                           NULL,    // no default extension
                           NULL,    // no initial file name
                           OFN_OVERWRITEPROMPT
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

    // Try to open the file for write access
    CFile file;
    if (! file.Open(strFile,
                    CFile::modeReadWrite
                     | CFile::modeCreate
                     | CFile::shareExclusive)) {
        AfxMessageBox("Failed to open file");
        return FALSE;
    }

    BOOL bResult = Save(&file);
    file.Close();
    if (!bResult) AfxMessageBox("Failed to save file");
    return bResult;
}

// Get a pointer to a pixel
// NOTE: DIB scan lines are DWORD aligned.  The scan line 
// storage width may be wider than the scan line image width
// so calc the storage width by rounding the image width 
// to the next highest dword value
BYTE *CDIB::GetPixelAddress(int x, int y)
{
    int iWidth;
    ASSERT(m_pBMI->bmiHeader.biBitCount == 8);
    // make sure it's in range and if not return zero
    if ((x >= DibWidth()) 
    || (y >= DibHeight())) {
        TRACE("Attempt to get out of range pixel addr");
        return NULL;
    }

    // Calculate the scan line storage width
    iWidth = GetStorageWidth();
    return m_pBits + (DibHeight()-y-1) * iWidth + x;
}

// Get the value (color index) of a pixel
// Note that this only works for 8 bpp
BYTE CDIB::GetPixelValue(int x, int y)
{
    BYTE *p;
    ASSERT(m_pBMI->bmiHeader.biBitCount == 8);

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

    ASSERT(m_pBMI->bmiHeader.biBitCount == 8);
    value = GetPixelValue(x, y);
    quad = GetClrTabAddress()[value];
    clr = RGB(quad.rgbRed, quad.rgbGreen, quad.rgbBlue);
    return clr;
}

// get a pointer to the color table
LPRGBQUAD CDIB::GetClrTabAddress()
{
    ASSERT(m_pBMI);
    return (LPRGBQUAD)(((BYTE *)(m_pBMI)) + sizeof(BITMAPINFOHEADER));
}

// get the number of color table entries
int CDIB::GetNumClrEntries()
{
    return NumDIBColorEntries(m_pBMI);
}

// Create a new empty 8 bpp DIB
BOOL CDIB::Create(int iWidth, int iHeight)
{
    // delete any existing stuff
    if (m_pBMI != NULL) free(m_pBMI);
    if (m_bMyBits && (m_pBits != NULL)) free(m_pBits);

    m_pBMI = (BITMAPINFO *) malloc(sizeof(BITMAPINFOHEADER)
                                  + 256 * sizeof(RGBQUAD));
    if (!m_pBMI) {
        TRACE("Out of memory for DIB header");
        return FALSE;
    }
    m_pBits = (BYTE *)malloc(((iWidth + 3) & ~3) * iHeight);
    if (!m_pBits) {
        TRACE("Out of memory for DIB bits");
        free(m_pBMI);
        m_pBMI = NULL;
        return FALSE;
    }

    // fill in the header info
    BITMAPINFOHEADER *pBI = (BITMAPINFOHEADER *) m_pBMI;
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
    RGBQUAD *prgb = GetClrTabAddress();
    for (int i = 0; i < 256; i++) {
        prgb->rgbBlue = prgb->rgbGreen = prgb->rgbRed = (BYTE) i;
        prgb->rgbReserved = 0;
        prgb++;
    }

    // fill the bits with something to show of the current color table
    // NOTE: You can nuke this once everything works
    BYTE *pBits;
    int x, y;
    for (y = 0; y < iHeight; y++) {
        pBits = GetPixelAddress(0, y);
        for (x = 0; x < iWidth; x++) {
            *pBits++ = (BYTE)(y * 256 / iHeight);
        }
    }
    return TRUE;
}

// Create a CDIB structure from existing header and bits. The DIB
// won't delete the bits and makes a copy of the header.
BOOL CDIB::Create(BITMAPINFO *pBMI, BYTE *pBits)
{
    ASSERT(pBMI);
    ASSERT(pBits);
    if (m_pBMI != NULL) free(m_pBMI);
    m_pBMI = (BITMAPINFO *) malloc(sizeof(BITMAPINFOHEADER)
                                   + 256 * sizeof(RGBQUAD));
    ASSERT(m_pBMI);
    // BUGBUG This will probably fail for < 256 color headers
    memcpy(m_pBMI, pBMI, sizeof(BITMAPINFOHEADER)+
             NumDIBColorEntries(pBMI) * sizeof(RGBQUAD));

    if (m_bMyBits && (m_pBits != NULL)) free(m_pBits);
    m_pBits = pBits;
    m_bMyBits = FALSE; // we can't delete the bits
    return TRUE;
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
    ASSERT(m_pBMI->bmiHeader.biBitCount == 8);
    ASSERT(m_pBMI);
    ASSERT(m_pBits);
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
    BYTE *pBits = GetBitsAddress();
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
    ASSERT(m_pBMI->bmiHeader.biBitCount == 8);
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

