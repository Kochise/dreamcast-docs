// dib.cpp : implementation file
//
// @doc

#include "stdafx.h"
#include "animate.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDIB

IMPLEMENT_SERIAL(CDIB, CObject, 0 /* schema number*/ )

/*
@mfunc void | CDIB | CDIB | Constructs a CDIB object.
@syntax CDIB(); 
@comm A 16 by 16 DIB is created with a gray scale color table.
@xref <c CDIB> <mf CDIB::Create>
*/

// Create a small DIB here so m_pBMI and m_pBits are always valid
CDIB::CDIB()
{
    m_pBMI = NULL;
    m_pBits = NULL;
    m_bMyBits = TRUE;
    Create(16, 16);
}

/*
@mfunc void | CDIB | ~CDIB | Constructs a CDIB object.
@syntax ~CDIB(); 
@comm The object is destroyed.
@xref <c CDIB>
*/

CDIB::~CDIB()
{
    // free the memory
    if (m_pBMI != NULL) free(m_pBMI);
    if (m_bMyBits && (m_pBits != NULL)) free(m_pBits);
}

/////////////////////////////////////////////////////////////////////////////
// CDIB serialization

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
// static functions

BOOL CDIB::IsWinDIB(BITMAPINFOHEADER* pBIH)
{
    ASSERT(pBIH);
    if (((BITMAPCOREHEADER *)pBIH)->bcSize == sizeof(BITMAPCOREHEADER)) {
        return FALSE;
    }
    return TRUE;
}

int CDIB::NumDIBColorEntries(BITMAPINFO *pBmpInfo) 
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
    // is determined by the biClrUsed field if it is non-zero
    if (IsWinDIB(pBIH) && (pBIH->biClrUsed != 0)) {
        iColors = pBIH->biClrUsed;
    }

    // BUGFIX 18 Oct 94 NigelT
    // Make sure the value is reasonable since some products
    // will write out more then 256 colors for an 8 bpp DIB!!!
    int iMax = 0;
    switch (iBitCount) {
    case 1:
        iMax = 2;
        break;
    case 4:
        iMax = 16;
        break;
    case 8:
        iMax = 256;
        break;
    default:
        iMax = 0;
        break;
    }
    if (iMax) {
        if (iColors > iMax) {
            TRACE("Invalid color count");
            iColors = iMax;
        }
    }

    return iColors;
}


/////////////////////////////////////////////////////////////////////////////
// CDIB commands

/*
@mfunc void | CDIB | Create | Creates a CDIB object.
@syntax BOOL Create(int iWidth, int iHeight, CPalette* pPal = NULL); 
@syntax BOOL Create(int iWidth, int iHeight, HPALETTE hPal); 
@syntax BOOL Create(BITMAPINFO* pBMI, BYTE* pBits, BOOL bOwnBits = FALSE);
@syntax BOOL Create(BITMAPINFO* pPackedDIB);
@parm int | iWidth | The width of the new DIB.
@parm int | iHeight | The height of the new DIB.
@parm CPalette* | pPal | An optional pointer to a palette.
@parm HPALETTE | hPal | Handle to a palette.
@parm BITMAPINFO* | pBMI | Pointer to a BITMAPINFO structure.
@parm BYTE* | pBits | Pointer to a buffer containing the DIB bits.
@parm BOOL | bOwnBits | If TRUE, the DIB will free the bits when it is 
destroyed. If FALSE, the bits remain the property of the caller.
@parm BITMAPINFO* | pPackedDIB | Pointer to a packed DIB structure.
@comm If no palette is supplied, the DIB is created with a gray 
scale wash color table. The palette is used only to set the DIb's color 
table. If pBits is used, then the DIB will not delete these bits when the
the DIB obejct is destroyed.
@xref <c CDIB>
*/

// Create a new empty 8bpp DIB with a 256 entry color table
// pPal is optional
BOOL CDIB::Create(int iWidth, int iHeight, CPalette* pPal)
{
#if 0
    // delete any existing stuff
    if (m_pBMI != NULL) free(m_pBMI);
    if (m_bMyBits && (m_pBits != NULL)) free(m_pBits);

    // allocate memory for the header
    m_pBMI = (BITMAPINFO *) malloc(sizeof(BITMAPINFOHEADER)
                                  + 256 * sizeof(RGBQUAD));
    if (!m_pBMI) {
        TRACE("Out of memory for DIB header");
        return FALSE;
    }

    // allocate memory for the bits (DWORD aligned)
    int iBitsSize = ((iWidth + 3) & ~3) * iHeight;
    m_pBits = (BYTE *)malloc(iBitsSize);
    if (!m_pBits) {
        TRACE("Out of memory for DIB bits");
        free(m_pBMI);
        m_pBMI = NULL;
        return FALSE;
    }
    m_bMyBits = TRUE;

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
    RGBQUAD* prgb = GetClrTabAddress();
    for (int i = 0; i < 256; i++) {
        prgb->rgbBlue = prgb->rgbGreen = prgb->rgbRed = (BYTE) i;
        prgb->rgbReserved = 0;
        prgb++;
    }

    // if a palette was supplied, grab its colors
    if (pPal) {
        int iColors = 0;
        if (!pPal->GetObject(sizeof(iColors), &iColors)) {
            TRACE("Failed to get num palette colors");
            return FALSE;
        }
        ASSERT(iColors);
        PALETTEENTRY pe[256];
        pPal->GetPaletteEntries(0, iColors, pe);
        RGBQUAD* pctThis = GetClrTabAddress();
        for (i = 0; i < iColors; i++) {
            pctThis->rgbRed = pe[i].peRed;    
            pctThis->rgbGreen = pe[i].peGreen;    
            pctThis->rgbBlue = pe[i].peBlue;
            pctThis++;    
        }
        pBI->biClrUsed = iColors;
    }

    // set all the bits to a known state (black)
    memset(m_pBits, 0, iBitsSize);

    return TRUE;
#else
    HPALETTE hPal = NULL;
    if (pPal) hPal = (HPALETTE) pPal->m_hObject;
    return Create(iWidth, iHeight, hPal);
#endif
}

BOOL CDIB::Create(int iWidth, int iHeight, HPALETTE hPal)
{
    // delete any existing stuff
    if (m_pBMI != NULL) free(m_pBMI);
    if (m_bMyBits && (m_pBits != NULL)) free(m_pBits);

    // allocate memory for the header
    m_pBMI = (BITMAPINFO *) malloc(sizeof(BITMAPINFOHEADER)
                                  + 256 * sizeof(RGBQUAD));
    if (!m_pBMI) {
        TRACE("Out of memory for DIB header");
        return FALSE;
    }

    // allocate memory for the bits (DWORD aligned)
    int iBitsSize = ((iWidth + 3) & ~3) * iHeight;
    m_pBits = (BYTE *)malloc(iBitsSize);
    if (!m_pBits) {
        TRACE("Out of memory for DIB bits");
        free(m_pBMI);
        m_pBMI = NULL;
        return FALSE;
    }
    m_bMyBits = TRUE;

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
    RGBQUAD* prgb = GetClrTabAddress();
    for (int i = 0; i < 256; i++) {
        prgb->rgbBlue = prgb->rgbGreen = prgb->rgbRed = (BYTE) i;
        prgb->rgbReserved = 0;
        prgb++;
    }

    // if a palette was supplied, grab its colors
    if (hPal) {
        int iColors = 0;
        if (!::GetObject(hPal, sizeof(iColors), &iColors)) {
            TRACE("Failed to get num palette colors");
            return FALSE;
        }
        ASSERT(iColors);
        PALETTEENTRY pe[256];
        ::GetPaletteEntries(hPal, 0, iColors, pe);
        RGBQUAD* pctThis = GetClrTabAddress();
        for (i = 0; i < iColors; i++) {
            pctThis->rgbRed = pe[i].peRed;    
            pctThis->rgbGreen = pe[i].peGreen;    
            pctThis->rgbBlue = pe[i].peBlue;
            pctThis++;    
        }
        pBI->biClrUsed = iColors;
    }

    // set all the bits to a known state (black)
    memset(m_pBits, 0, iBitsSize);

    return TRUE;
}

// Create a CDIB structure from existing header and bits. The DIB
// won't delete the bits and makes a copy of the header.
BOOL CDIB::Create(BITMAPINFO* pBMI, BYTE* pBits, BOOL bOwnBits/*= FALSE*/)
{
    ASSERT(pBMI);
    ASSERT(pBits);
    if (m_pBMI != NULL) free(m_pBMI);
    m_pBMI = (BITMAPINFO*) malloc(sizeof(BITMAPINFOHEADER)
                                  + 256 * sizeof(RGBQUAD));
    ASSERT(m_pBMI);
    // BUGBUG This will probably fail for < 256 color headers
    memcpy(m_pBMI, pBMI, sizeof(BITMAPINFOHEADER)+
             NumDIBColorEntries(pBMI) * sizeof(RGBQUAD));

    if (m_bMyBits && (m_pBits != NULL)) free(m_pBits);
    m_pBits = pBits;
    m_bMyBits = bOwnBits;
    return TRUE;
}

// Create a CDIB from a packed DIB structure
BOOL CDIB::Create(BITMAPINFO* pPackedDIB)
{
    ASSERT(pPackedDIB);
    // compute the address of the bits
    BYTE* pBits = (BYTE*) pPackedDIB
                + sizeof(BITMAPINFOHEADER)
                + NumDIBColorEntries(pPackedDIB) * sizeof(RGBQUAD);

    return Create(pPackedDIB, pBits, FALSE);
}


/*
@mfunc void | CDIB | Load | Load a DIB from a file or resource.
@syntax BOOL Load(CFile *fp); 
@syntax BOOL Load(const char* pszFileName);
@syntax BOOL Load(WORD wResid);
@parm CFile* | fp | Pointer to an open CFile object.
@parm LPSTR | pszFileName | The name of the file to load the DIB from.
@parm WORD | wResid | A resource ID to load the DIB from.
@rdesc The return value is TRUE if the DIB is loaded, FALSE if not.
@comm The file may be in either Windows DIB format or Presentation
Manager DIB format.
@xref <c CDIB>
*/

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

    // Work out how much memory we need for the BITMAPINFO
    // structure, color table and then for the bits.  
    // Allocate the memory blocks, copy the BmpInfoHdr we have so far 
    // and then read in the color table from the file.
    int iColors;
    int iColorTableSize;
    iColors = NumDIBColorEntries((LPBITMAPINFO) &BmpInfoHdr);
    iColorTableSize = iColors * sizeof(RGBQUAD);
    int iBitsSize;
    int iBISize;
    // always allocate enough room for 256 entries
    iBISize = sizeof(BITMAPINFOHEADER)    
           + 256 * sizeof(RGBQUAD);
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
BOOL CDIB::Load(const char* pszFileName)
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
        return FALSE;
    }

    BOOL bResult = Load(&file);
    file.Close();
    return bResult;
}

// load a DIB from a resource id
// Note that we make a copy of tyhe resource image for two reasons.  
// a) it is by default wriote-protected and if we alter that and write
// to it (to map colors) then we can never get it back as it was in the EXE.
// b) There are some ptr alignment probs. on MIOPS and Alpha which are 
// simplified if we can copy the header sections of the image.
// In practice the EXE is simply mapped in to memory and some arb address
// so copying the bits is realy not less efficient than reading them from a file.
BOOL CDIB::Load(WORD wResid)
{
    ASSERT(wResid);
    HINSTANCE hInst = AfxGetResourceHandle();
    HRSRC hrsrc = ::FindResource(hInst, MAKEINTRESOURCE(wResid), "DIB");
    if (!hrsrc) {
        TRACE("DIB resource not found");
        return FALSE;
    }
    HGLOBAL hg = LoadResource(hInst, hrsrc);
    if (!hg) {
        TRACE("Failed to load DIB resource");
        return FALSE;
    }
#if 0
    BYTE* pRes = (BYTE*) LockResource(hg);
    ASSERT(pRes);
    int iSize = ::SizeofResource(hInst, hrsrc);

    // Mark the resource pages as read/write so we can alter the DIB 
    // if we need to later
    DWORD dwOldProt;
    BOOL b = ::VirtualProtect(pRes,
                              iSize,
                              PAGE_READWRITE,
                              &dwOldProt);
    ASSERT(b);

    // now create the CDIB object. We will create a new header from the 
    // data in the resource image but just use the bits as they are in
    // the resource

    BITMAPFILEHEADER* pFileHdr = (BITMAPFILEHEADER*)pRes;
    ASSERT(pFileHdr->bfType == 0x4D42); // BM file
    BITMAPINFOHEADER* pInfoHdr = (BITMAPINFOHEADER*) (pRes + sizeof(BITMAPFILEHEADER));
    ASSERT(pInfoHdr->biSize == sizeof(BITMAPINFOHEADER));  // must be a Win DIB
    BYTE* pBits = pRes + pFileHdr->bfOffBits;
    return Create((BITMAPINFO*)pInfoHdr, pBits);
#else
    BITMAPFILEHEADER* pFileHdr = (BITMAPFILEHEADER*)  LockResource(hg);
    ASSERT(pFileHdr);
    ASSERT(pFileHdr->bfType == 0x4D42); // BM file

    // Allocate memory for the new header and color table
    if (m_pBMI != NULL) free(m_pBMI);
    m_pBMI = (BITMAPINFO*) malloc(sizeof(BITMAPINFOHEADER)
                                  + 256 * sizeof(RGBQUAD));
    ASSERT(m_pBMI);

    // Copy the header
    BITMAPINFO* pBMI = (BITMAPINFO*) ((BYTE*) pFileHdr + sizeof(BITMAPFILEHEADER)); 
    memcpy(m_pBMI,
           pBMI, 
           sizeof(BITMAPINFOHEADER));

    // Copy the colors that are present
    RGBQUAD* pRGB = GetClrTabAddress();
    memset(pRGB,
           0,
           256 * sizeof(RGBQUAD)); // make then all black
    memcpy(pRGB,
           (BYTE*) pBMI + sizeof(BITMAPINFOHEADER),
           NumDIBColorEntries(m_pBMI) * sizeof(RGBQUAD));

    // Allocate memory for the bits (DWORD aligned)
    if (m_bMyBits && (m_pBits != NULL)) free (m_pBits);
    int iBitsSize = ((DibWidth() + 3) & ~3) * DibHeight();
    m_pBits = (BYTE *) malloc(iBitsSize);
    if (!m_pBits) {
        TRACE("Out of memory for DIB bits");
        free(m_pBMI);
        m_pBMI = NULL;
        return FALSE;
    }
    m_bMyBits = TRUE;

    // Copy the bits
    memcpy(m_pBits,
           (BYTE*)pFileHdr + pFileHdr->bfOffBits,
           iBitsSize);
    return TRUE;
#endif
    // Note: not required to unlock or free the resource in Win32
}

/*
@mfunc void | CDIB | Draw | Draw the DIB to a given CDC.
@syntax void Draw(CDC* pDC, int x, int y); 
@syntax void Draw(HDC hDC, int x, int y); 
@parm CDC* | pDC | Pointer to a CDC object to draw to.
@parm HDC | hDC |  The DC to draw to.
@parm int | x | The X coordinate of the DC at which the top-left
corner of the DIB will be drawn..
@parm int | y | The Y coordinate of the DC at which the top-left
corner of the DIB will be drawn..
@rdesc There is no return value.
@comm The DIB is drawn using StretchDIBits with DIB_RGB_COLORS so
the operation is not fast.
@xref <c CDIB>
*/

void CDIB::Draw(CDC *pDC, int x, int y)
{
    Draw(pDC->GetSafeHdc(), x, y);
}

void CDIB::Draw(HDC hDC, int x, int y)
{
    ::StretchDIBits(hDC,
                  x,                        // dest x
                  y,                        // dest y
                  DibWidth(),               // dest width
                  DibHeight(),              // dest height
                  0,                        // src x
                  0,                        // src y
                  DibWidth(),               // src width
                  DibHeight(),              // src height
                  GetBitsAddress(),         // bits
                  GetBitmapInfoAddress(),   // BITMAPINFO
                  DIB_RGB_COLORS,           // options
                  SRCCOPY);                 // rop
}

/*
@mfunc int | CDIB | GetNumClrEntries | Get the number of color table
entries.
@syntax int GetNumClrEntries(); 
@rdesc The return value is the number of entries in the color table.
@xref <c CDIB>
*/
int CDIB::GetNumClrEntries()
{
    return NumDIBColorEntries(m_pBMI);
}

/*
@mfunc BOOL | CDIB | MapColorsToPalette | Map the colors in the DIB
to a given palette.
@syntax BOOL MapColorsToPalette(CPalette* pPal);
@syntax BOOL MapColorsToPalette(HPALETTE hPal);
@parm CPalette* | pPal | A pointer to the palette that the DIB
colors are to be mapped to. 
@parm HPALETTE | hPal | A palette that the DIB
colors are to be mapped to. 
@rdesc The return value is TRUE if the colors are mapped, FALSE if an error
occurs.
@comm This function assumes all CDIB objects have 256 color table entries.
@xref <c CDIB>
*/

BOOL CDIB::MapColorsToPalette(HPALETTE hPal)
{
    return CDIB::MapColorsToPalette(CPalette::FromHandle(hPal));
}

BOOL CDIB::MapColorsToPalette(CPalette *pPal)
{
    if (!pPal) {
        TRACE("No palette to map to");
        return FALSE;
    }

    // Get the number of colors in the palette
    int iPalColors = 0;
    if (!pPal->GetObject(sizeof(iPalColors), &iPalColors)) {
        TRACE("Failed to get num pal colors");
        return FALSE;
    }
    PALETTEENTRY pe[256];
    pPal->GetPaletteEntries(0, iPalColors, pe);

    ASSERT(m_pBMI);
    ASSERT(m_pBits);
    LPRGBQUAD pctThis = GetClrTabAddress();
    ASSERT(pctThis);

    // build an index translation table to map this DIBs colors
    // to those in the palette
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
    BYTE *pBits = (BYTE *)GetBitsAddress();
    int iSize = StorageWidth() * DibHeight();
    switch (m_pBMI->bmiHeader.biBitCount) {
    case 4:
        while (iSize--) {
            BYTE b1 = *pBits;
            BYTE b2 = imap[b1 & 0xF];
            b1 = imap[b1 >> 4];
            *pBits = (b1 << 4) | b2;
            pBits++;
        }
        break;
    case 8:
        while (iSize--) {
            *pBits = imap[*pBits];
            pBits++;
        }
        break;
    case 24: {
        int iWidth =DibWidth();
        int iHeight = DibHeight();
        for (int iLine = 0; iLine < iHeight; iLine++) {
            BYTE* pPixel = (BYTE*) GetPixelAddress(0, iLine);
            ASSERT(pPixel);
            for (int iPixel = 0; iPixel < iWidth; iPixel++) {
                BYTE Blue = *pPixel;
                BYTE Green = pPixel[1];
                BYTE Red = pPixel[2];
                int index = pPal->GetNearestPaletteIndex(RGB(Red, Green, Blue));
                *pPixel++ = pe[index].peBlue;
                *pPixel++ = pe[index].peGreen;
                *pPixel++ = pe[index].peRed;
            }
        }
        } break;
    default:
        ASSERT(0);
        return FALSE;
    }
     

    // Reset the DIB color table so that its RGB values match
    // those in the palette
    pctThis = GetClrTabAddress();
    for (i = 0; i < iPalColors; i++) {
        pctThis->rgbRed = pe[i].peRed;    
        pctThis->rgbGreen = pe[i].peGreen;    
        pctThis->rgbBlue = pe[i].peBlue;
        pctThis->rgbReserved = 0;
        pctThis++;    
    }

    // reset the rest of the table to zero
    while (i < 256) {
        pctThis->rgbRed = 0;    
        pctThis->rgbGreen = 0;    
        pctThis->rgbBlue = 0;
        pctThis->rgbReserved = 0;
        pctThis++;
        i++;    
    }

    // Set how many colors are in use now
    m_pBMI->bmiHeader.biClrUsed = iPalColors;
    return TRUE;
}

/*
@mfunc void* | CDIB | GetPixelAddress | Get a pointer to a given pixel.
@syntax void* GetPixelAddress(int x, int y);
@parm int | x | The x coordinate of the pixel. 
@parm int | y | The y coordinate of the pixel. 
@rdesc The return value is the address of the pixel or NUL if the coordinates are 
invalid. Note that for 1 and 4 bpp DIBs the pixel address is that of
the byte containing the pixel. You must compute the actual pixel mask yourself.
@comm NOTE: DIB scan lines are DWORD aligned.  The scan line 
storage width may be wider than the scan line image width
so calculate the storage width by rounding the image width 
to the next highest dword value.
@xref <c CDIB>
*/

void* CDIB::GetPixelAddress(int x, int y)
{
    int iWidth;
    // make sure it's in range and if not return zero
    if ((x >= DibWidth()) 
    || (y >= DibHeight())) {
        TRACE("Attempt to get out of range pixel addr");
        return NULL;
    }

    // Calculate the scan line storage width
    iWidth = StorageWidth();
    switch (m_pBMI->bmiHeader.biBitCount) {
    case 1:
        return m_pBits + (DibHeight()-y-1) * iWidth + (x+7)/8 ;
    case 4:
        return m_pBits + (DibHeight()-y-1) * iWidth + (x+3)/4;
    case 8:
        return m_pBits + (DibHeight()-y-1) * iWidth + x;
    case 16:
        return m_pBits + (DibHeight()-y-1) * iWidth + x*2;
    case 24:
        return m_pBits + (DibHeight()-y-1) * iWidth + x*3;
    case 32:
    default:
        TRACE("Unsupported format");
        ASSERT(0);
        return NULL;
    }
}

/*
@mfunc void | CDIB | GetRect | Get the bounding rectangle.
@syntax void GetRect(CRect* pRect);
@parm CRect* | pRect | Pointer to a CRect oject to receive the result. 
@rdesc There is no return value.
@xref <c CDIB>
*/

void CDIB::GetRect(RECT* pRect)
{
    pRect->top = 0;
    pRect->left = 0;
    pRect->bottom = DibHeight();
    pRect->right = DibWidth();
}

/*
@mfunc void | CDIB | CopyBits | Copy a rectangle of the DIB to another DIB.
@syntax void CopyBits(CDIB* pdibDest, int xd, int yd,
int w, int h, int xs, int ys, COLORREF clrTrans = 0xFFFFFFFF);
@parm CDIB* | pdibDest | Pointer to the destination DIB.
@parm int | xd | The x coordinate of the top-left corner of
the destiantion rectangle.
@parm int | yd | The y coordinate of the top-left corner of
the destiantion rectangle.
@parm int | w | The width of the rectangle to be copied.
@parm int | h | The height of the rectangle to be copied.
@parm int | xs | The x coordinate of the top-left corner of
the source rectangle.
@parm int | ys | The y coordinate of the top-left corner of
the source rectangle.
@parm COLORREF | clrTrans | If this optional paramter is supplied 
@rdesc There is no return value.
@comm Note: Only 8bpp DIBs are supported.
@xref <c CDIB> <mf CDIB::StretchBits>
*/

void CDIB::CopyBits(CDIB* pdibDest, 
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
    BYTE* pSrc = (BYTE*)GetPixelAddress(xs, ys + h - 1);
    ASSERT(pSrc);
    BYTE* pDest = (BYTE*)pdibDest->GetPixelAddress(xd, yd + h - 1);
    ASSERT(pDest);

    // get the scan line widths of each DIB
    int iScanS = StorageWidth();
    int iScanD = pdibDest->StorageWidth();

    if (clrTrans == 0xFFFFFFFF) {
        // copy the lines
        while (h--) {
            memcpy(pDest, pSrc, w);
            pSrc += iScanS;
            pDest += iScanD;
        }
    } else {
        // copy lines with transparency
        // Note: We only accept a PALETTEINDEX description
        // for the color definition
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

/*
@mfunc void | CDIB | StretchBits | Stretch a rectangle of the DIB to another DIB.
@syntax void StretchBits(CDIB* pdibDest, int xd, int yd,
int wd, int hd, int xs, int ys, int ws, int hs, COLORREF clrTrans = 0xFFFFFFFF);
@parm CDIB* | pdibDest | Pointer to the destination DIB.
@parm int | xd | The x coordinate of the top-left corner of
the destiantion rectangle.
@parm int | yd | The y coordinate of the top-left corner of
the destiantion rectangle.
@parm int | wd | The width of the destination rectangle.
@parm int | hd | The height of the destination rectangle.
@parm int | xs | The x coordinate of the top-left corner of
the source rectangle.
@parm int | ys | The y coordinate of the top-left corner of
the source rectangle.
@parm int | ws | The width of the source rectangle.
@parm int | hs | The height of the source rectangle.
@parm COLORREF | clrTrans | If this optional paramter is supplied 
@rdesc There is no return value.
@comm Note: Only 8bpp DIBs are supported.
@xref <c CDIB> <mf CDIB::CopyBits>
*/

void CDIB::StretchBits(CDIB* pdibDest, 
                       int xd, int yd,
                       int wd, int hd,
                       int xs, int ys,
                       int ws, int hs,
                       COLORREF clrTrans)
{
    ASSERT(m_pBMI->bmiHeader.biBitCount == 8);
    ASSERT(pdibDest);
    // test for silly cases
    if (wd == 0 || hd == 0 || ws == 0 || hs == 0) return;

    if (wd == ws*2 && hd == hs*2) {
        DoubleBits(pdibDest, xd, yd, xs, ys, ws, hs, clrTrans);
        return;
    }

    // get pointers to the start points in the source
    // and destination DIBs. Note that this will be the bottom left
    // corner of the DIB as the scan lines are reversed in memory
    BYTE* pSrc = (BYTE*)GetPixelAddress(xs, ys + hs - 1);
    ASSERT(pSrc);
    BYTE* pDest = (BYTE*)pdibDest->GetPixelAddress(xd, yd + hd - 1);
    ASSERT(pDest);

    // get the scan line widths of each DIB
    int iScanS = StorageWidth();
    int iScanD = pdibDest->StorageWidth();

    if (clrTrans == 0xFFFFFFFF) {
        // stretch the lines
        int iSrcLinePrev = -1;
        for (int iDstLine = yd + hd - 1; iDstLine >= yd; iDstLine--) {
            int iSrcLine = ys + ((iDstLine - yd) * hs / hd);
            if (iSrcLine == iSrcLinePrev) {
                memcpy(pDest, pDest - iScanD, wd);
            } else {
                pSrc = (BYTE*)GetPixelAddress(xs, iSrcLine);
                BYTE* pd = pDest;
                for (int i = 0; i < wd; i++) {
                    BYTE* ps = pSrc + (i * ws / wd);
                    *pd++ = *ps;
                }
            }
            iSrcLinePrev = iSrcLine;
            pDest += iScanD;
        }
    } else {
        // stretch lines with transparency
        // Note: We only accept a PALETTEINDEX description
        // for the color definition
        ASSERT((clrTrans & 0xFF000000) == 0x01000000);
        BYTE bTransClr = LOBYTE(LOWORD(clrTrans));

        for (int iDstLine = yd + hd - 1; iDstLine >= yd; iDstLine--) {
            int iSrcLine = ys + ((iDstLine - yd) * hs / hd);
            pSrc = (BYTE*)GetPixelAddress(xs, iSrcLine);
            BYTE* pd = pDest;
            for (int i = 0; i < wd; i++) {
                BYTE* ps = pSrc + (i * ws / wd);
                if (*ps != bTransClr) {
                    *pd++ = *ps;
                } else {
                    pd++;
                }
            }
            pDest += iScanD;
        }
    }
}          

/*
@mfunc void | CDIB | DoubleBits | Stretch a rectangle of the DIB
by a facotr of 2 to another DIB.
@syntax void DoubleBits(CDIB* pdibDest, int xd, int yd,
int xs, int ys, int ws, int hs, COLORREF clrTrans = 0xFFFFFFFF);
@parm CDIB* | pdibDest | Pointer to the destination DIB.
@parm int | xd | The x coordinate of the top-left corner of
the destiantion rectangle.
@parm int | yd | The y coordinate of the top-left corner of
the destiantion rectangle.
@parm int | xs | The x coordinate of the top-left corner of
the source rectangle.
@parm int | ys | The y coordinate of the top-left corner of
the source rectangle.
@parm int | ws | The width of the source rectangle to be copied.
@parm int | hs | The height of the source rectangle to be copied.
@parm COLORREF | clrTrans | If this optional paramter is supplied 
@rdesc There is no return value.
@comm Note: Only 8bpp DIBs are supported.
@xref <c CDIB> <mf CDIB::StretchBits>
*/

void CDIB::DoubleBits(CDIB* pdibDest, 
                    int xd, int yd,
                    int xs, int ys,
                    int ws, int hs,
                    COLORREF clrTrans)
{
    ASSERT(m_pBMI->bmiHeader.biBitCount == 8);
    ASSERT(pdibDest);
    // test for silly cases
    if (ws == 0 || hs == 0) return;

    // get pointers to the start points in the source
    // and destination DIBs. Note that this will be the bottom left
    // corner of the DIB as the scan lines are reversed in memory
    BYTE* pSrc = (BYTE*)GetPixelAddress(xs, ys + hs - 1);
    ASSERT(pSrc);
    BYTE* pDest = (BYTE*)pdibDest->GetPixelAddress(xd, yd + hs*2 - 1);
    ASSERT(pDest);

    // get the scan line widths of each DIB
    int iScanS = StorageWidth();
    int iScanD = pdibDest->StorageWidth();

    BYTE* pd;
    BYTE* ps;
    int i;
    if (clrTrans == 0xFFFFFFFF) {
        // copy the lines
        while (hs--) {
            pd = pDest;
            ps = pSrc;
            for (i = 0; i < ws; i++) {
                *pd++ = *ps;
                *pd++ = *ps++;
            }
            pDest += iScanD;
            pd = pDest;
            ps = pSrc;
            for (i = 0; i < ws; i++) {
                *pd++ = *ps;
                *pd++ = *ps++;
            }
            pDest += iScanD;
            pSrc += iScanS;
        }
    } else {
        // copy lines with transparency
        // Note: We only accept a PALETTEINDEX description
        // for the color definition
        ASSERT((clrTrans & 0xFF000000) == 0x01000000);
        BYTE bTransClr = LOBYTE(LOWORD(clrTrans));
        while (hs--) {
            BYTE* pd = pDest;
            BYTE* ps = pSrc;
            for (int i = 0; i < ws; i++) {
                if (*ps != bTransClr) {
                    *pd++ = *ps;
                    *pd++ = *ps++;
                } else {
                    pd += 2;
                    ps++;
                }
            }
            pDest += iScanD;
            pd = pDest;
            ps = pSrc;
            for (i = 0; i < ws; i++) {
                if (*ps != bTransClr) {
                    *pd++ = *ps;
                    *pd++ = *ps++;
                } else {
                    pd += 2;
                    ps++;
                }
            }
            pDest += iScanD;
            pSrc += iScanS;
        }
    }
}          

/*
@mfunc BOOL | CDIB | Save | Save a DIB to a file.
@syntax BOOL Save(CFile *fp); 
@syntax BOOL Save(const char* pszFileName);
@parm CFile* | fp | Pointer to an open CFile object.
@parm LPSTR | pszFileName | The name of the file to save the DIB to.
@rdesc The return value is TRUE if the DIB is saved, FALSE if not.
@comm The file  in always created in the Windows DIB format.
@xref <c CDIB>
*/
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
        StorageWidth() * DibHeight();
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
    iSize = StorageWidth() * DibHeight();
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
BOOL CDIB::Save(const char* pszFileName)
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

/*
@mfunc BOOL | CDIB | SetColorTable | Set the color table.
@syntax BOOL SetColorTable(CPalette* pPal); 
@parm CPalette* | pPal | Pointer to palette containing the set of 
colors.
@rdesc The return value is TRUE if the color table
is set, FALSE if not.
@comm Note that the DIB pixel values are not altered by this function
but changing the color table will effectivly alter the colors of the DIB 
in some circumstances.
@xref <c CDIB>
*/
BOOL CDIB::SetColorTable(CPalette* pPal)
{
    if (!pPal) return FALSE;

    // Get the number of colors in the palette
    int iColors = 0;
    if (!pPal->GetObject(sizeof(iColors), &iColors)) {
        TRACE("Failed to get num pal colors");
        return FALSE;
    }

    // get the palette colors
    PALETTEENTRY pe[256];
    pPal->GetPaletteEntries(0, iColors, pe);

    // put them into the color table
    RGBQUAD* pRGB = GetClrTabAddress();
    for (int i = 0; i < iColors; i++) {
        pRGB->rgbRed = pe[i].peRed;
        pRGB->rgbGreen = pe[i].peGreen;
        pRGB->rgbBlue = pe[i].peBlue;
        pRGB++;
    }

    BITMAPINFO* pBMI = GetBitmapInfoAddress();
    pBMI->bmiHeader.biClrUsed = iColors;

    return TRUE;
}
