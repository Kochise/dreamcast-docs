// dibpal.cpp : implementation file
// @doc

#include "stdafx.h"
#include "animate.h"

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

/*
@mfunc BOOL | CDIBPal | Create | Constructs a CDIBPal object.
@syntax BOOL Create(CDIB* pDIB);
@syntax BOOL Create(BITMAPINFO* pBMI);
@syntax BOOL Create(RGBQUAD* pRGB, int iClrs);
@parm CDIB* | pDIB | A pointer to a CDIB object containing the color table
tto be used to create the palette.
@parm BITMAPINFO* | pBMI | A pointer to a BITMAPINFO structure containing
the color table to create the palette from.
@parm RGBQUAD* | pRGB | A pointer to an array of RGBQUAD structures
describing the colors for the palette.
@parm int | iClrs | The number of entries int he RGBQUAD array.
@rdesc The return value is TRUE if the function succeeds, FALSE if not.
@xref <c CDIBPal>
*/

BOOL CDIBPal::Create(CDIB *pDIB)
{
    int iColors = pDIB->GetNumClrEntries();
    if (! iColors) return FALSE;

    // get a pointer to the RGB quads in the color table
    RGBQUAD* pRGB = pDIB->GetClrTabAddress();

    return Create(pRGB, iColors);
}

BOOL CDIBPal::Create(BITMAPINFO* pBMI)
{
    if (!pBMI) return FALSE;
    int iColors = CDIB::NumDIBColorEntries(pBMI);
    RGBQUAD* pRGB = (LPRGBQUAD)(((BYTE *)(pBMI)) 
                  + sizeof(BITMAPINFOHEADER));
    return Create(pRGB, iColors);
}

BOOL CDIBPal::Create(RGBQUAD* pRGB, int iClrs)
{
    if (iClrs == 0) return FALSE;
    if (!pRGB) return FALSE;

    // allocate a log pal and fill it with the color table info
    LOGPALETTE *pPal = (LOGPALETTE *) malloc(sizeof(LOGPALETTE) 
                     + iClrs * sizeof(PALETTEENTRY));
    if (!pPal) {
        TRACE("Out of memory for logpal");
        return FALSE;
    }
    pPal->palVersion = 0x300; // Windows 3.0
    pPal->palNumEntries = (WORD) iClrs; // table size
    for (int i = 0; i < iClrs; i++) {
        pPal->palPalEntry[i].peRed = pRGB[i].rgbRed;
        pPal->palPalEntry[i].peGreen = pRGB[i].rgbGreen;
        pPal->palPalEntry[i].peBlue = pRGB[i].rgbBlue;
        pPal->palPalEntry[i].peFlags = 0;
    }
    if (m_hObject != NULL) {
        HGDIOBJ hOldPal = Detach();
        ::DeleteObject(hOldPal);
    }    
    BOOL bResult = CreatePalette(pPal);
    free (pPal);
    return bResult;
}

/////////////////////////////////////////////////////////////////////////////
// CDIBPal commands

/*
@mfunc int | CDIBPal | GetNumColors | Get the number of colors in
the palette.
@syntax int GetNumColors();
@rdesc The return value is the number of colors in the palette.
@xref <c CDIBPal>
*/

int CDIBPal::GetNumColors()
{
    int iColors = 0;
    if (!GetObject(sizeof(iColors), &iColors)) {
        TRACE("Failed to get num pal colors");
        return 0;
    }
    return iColors;
}

/*
@mfunc void | CDIBPal | Draw | Draw a representation of the palette.
@syntax void Draw(CDC* pDC, CRect* pRect, BOOL bBkgnd = FALSE);
@syntax void Draw(HDC hDC, RECT* pRect, BOOL bBkgnd = FALSE);
@parm CDC* | pDC | A pointer to a CDC object on which the palette is
to be drawn.
@parm HDC | hDC | The DC on which the palette is to be drawn.
@parm RECT* | pRect | A pointer to a RECT desribing the area
of the CDC to be used for drawing the palette.
@parm CRect* | pRect | A pointer to a CRect object desribing the area
of the CDC to be used for drawing the palette.
@parm BOOL | bBkgnd | Used to determine if the palette will be selected
as a background or foreground palette. 
@comm By default the palette is selected as foreground if the application
is in the foreground.  Setting bBkgnd to TRUE will force the palette to
be realized in the background. The palette is always drawn as a 16 by 16
grid. The first palette color is shown in the top-left grid square. The next
color is shown to its right and so on.
@rdesc There is no return value. 
@xref <c CDIBPal>
*/

void CDIBPal::Draw(CDC* pDC, CRect* pRect, BOOL bBkgnd)
{
#if 0
    int iColors = GetNumColors();
    CPalette *pOldPal = pDC->SelectPalette(this, bBkgnd);
    pDC->RealizePalette();
    int i, j, top, left, bottom, right;
    for (j=0, top=0; j<16 && iColors; j++, top=bottom) {
        bottom = (j+1) * pRect->bottom / 16 + 1;
        for(i=0, left=0; i<16 && iColors; i++, left=right) {
            right = (i+1) * pRect->right / 16 + 1;
            CBrush br (PALETTEINDEX(j * 16 + i));
            CBrush *brold = pDC->SelectObject(&br);
            pDC->Rectangle(left-1, top-1, right, bottom);
            pDC->SelectObject(brold);
            iColors--;
        }
    }
    pDC->SelectPalette(pOldPal, FALSE);
#else
    Draw(pDC->GetSafeHdc(), pRect, bBkgnd);
#endif
}


void CDIBPal::Draw(HDC hDC, RECT* pRect, BOOL bBkgnd)
{
    int iColors = GetNumColors();
    HPALETTE hOldPal = ::SelectPalette(hDC, (HPALETTE)m_hObject, bBkgnd);
    ::RealizePalette(hDC);
    int i, j, top, left, bottom, right, w, h;
    w = pRect->right - pRect->left;
    h = pRect->bottom - pRect->top;
    for (j=0, top=pRect->top; j<16 && iColors; j++, top=bottom) {
        bottom = pRect->top + (j+1) * h / 16 + 1;
        for(i=0, left=pRect->left; i<16 && iColors; i++, left=right) {
            right = pRect->left + (i+1) * w / 16 + 1;
            CBrush br (PALETTEINDEX(j * 16 + i));
            HBRUSH brold = (HBRUSH)::SelectObject(hDC, br.m_hObject);
            ::Rectangle(hDC, left-1, top-1, right, bottom);
            ::SelectObject(hDC, brold);
            iColors--;
        }
    }
    ::SelectPalette(hDC, hOldPal, FALSE);
}

/*
@mfunc BOOL | CDIBPal | SetSysPalColors | Create an identity palette.
@syntax BOOL SetSysPalColors();
@comm By default the palette is selected as foreground if the application
is in the foreground.  Setting bBkgnd to TRUE will force the palette to
be realized in the background. The palette is always drawn as a 16 by 16
grid. The first palette color is shown in the top-left grid square. The next
color is shown to its right and so on. 
@rdesc The return value is TRUE if the function succeeds, FALSE if not.
@xref <c CDIBPal>
*/

BOOL CDIBPal::SetSysPalColors()
{
    BOOL bResult = FALSE;
    int i, iSysColors, iPalEntries;
    HPALETTE hpalOld;

    // Get a screen DC to work with
    HWND hwndActive = ::GetActiveWindow();
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

/*
@mfunc BOOL | CDIBPal | Load | Load a palette from a file.
@syntax BOOL Load(const char* pszFileName);
@syntax BOOL Load(CFile* fp);
@syntax BOOL Load(UINT hFile);
@syntax BOOL Load(HMMIO hmmio);
@parm char* | pszFileName | The name of the file to load the palette from.
@parm CFile* | fp | A pointer to an open CFile object to load the palette from.
@parm UINT | hFile | An open file handle to load the palette from.
@parm HMMIO | hmmio | A HMMIO handle to load the palette from.
@rdesc The return value is TRUE if the function succeeds, FALSE if not.
@xref <c CDIBPal>
*/

// Load a palette from a named file
BOOL CDIBPal::Load(const char *pszFileName)
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
                           "Palette files (*.PAL)|*.PAL|All files (*.*)|*.*||");
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

// Load a palette from an open CFile object
BOOL CDIBPal::Load(CFile *fp)
{
    return Load(fp->m_hFile);
}

// Load a palette from an open file handle
BOOL CDIBPal::Load(UINT hFile)
{
    HMMIO hmmio;
    MMIOINFO info;
    memset(&info, 0, sizeof(info));
    info.adwInfo[0] = hFile;
    hmmio = mmioOpen(NULL,
                     &info,
                     MMIO_READ | MMIO_ALLOCBUF);
    if (!hmmio) {
        TRACE("mmioOpen failed");
        return FALSE;
    }
    BOOL bResult = Load(hmmio);
    mmioClose(hmmio, MMIO_FHOPEN);
    return bResult;
}

// Load a palette from an open MMIO handle
BOOL CDIBPal::Load(HMMIO hmmio)
{
    // Check it's a RIFF PAL file
    MMCKINFO ckFile;
    ckFile.fccType = mmioFOURCC('P','A','L',' ');
    if (mmioDescend(hmmio,
                    &ckFile,
                    NULL,
                    MMIO_FINDRIFF) != 0) {
        TRACE("Not a RIFF or PAL file");
        return FALSE;
    }
    // Find the 'data' chunk
    MMCKINFO ckChunk;
    ckChunk.ckid = mmioFOURCC('d','a','t','a');
    if (mmioDescend(hmmio,
                    &ckChunk,
                    &ckFile,
                    MMIO_FINDCHUNK) != 0) {
        TRACE("No data chunk in file");
        return FALSE;
    }
    // allocate some memory for the data chunk
    int iSize = ckChunk.cksize;
    void *pdata = malloc(iSize);
    if (!pdata) {
        TRACE("No mem for data");
        return FALSE;
    }
    // read the data chunk
    if (mmioRead(hmmio,
                 (char *)pdata,
                 iSize) != iSize) {
        TRACE("Failed to read data chunk");
        free(pdata);
        return FALSE;
    }
    // The data chunk should be a LOGPALETTE structure
    // which we can create a palette from
    LOGPALETTE* pLogPal = (LOGPALETTE*)pdata;
    if (pLogPal->palVersion != 0x300) {
        TRACE("Invalid version number");
        free(pdata);
        return FALSE;
    }
    // Get the number of entries
    int iColors = pLogPal->palNumEntries;
    if (iColors <= 0) {
        TRACE("No colors in palette");
        free(pdata);
        return FALSE;
    }
    return CreatePalette(pLogPal);
}

/*
@mfunc BOOL | CDIBPal | Save | Save a palette to a file.
@syntax BOOL Save(const char* pszFileName = NULL);
@syntax BOOL Save(CFile* fp);
@syntax BOOL Save(UINT hFile);
@syntax BOOL Save(HMMIO hmmio);
@parm const char* | pszFileName | The name of a file to save the palette
to.  If no filename is given a File Save dialog box is presented to the 
user to get the name. 
@parm CFile* | fp | A pointer to an open CFile object to save the palette to.
@parm UINT | hFile | An open file handle to save the palette to.
@parm HMMIO | hmmio | A HMMIO handle to save the palette to.
@rdesc The return value is TRUE if the function succeeds, FALSE if not.
@xref <c CDIBPal>
*/

// Save a palette to a disk file.  If no file name is given, show
// a save file dialog to get one.
BOOL CDIBPal::Save(const char* pszFileName/*= NULL*/)
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
                           "Palette files (*.PAL)|*.PAL|All files (*.*)|*.*||");
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

// Save a palette to an open CFile object
BOOL CDIBPal::Save(CFile *fp)
{
    return Save(fp->m_hFile);
}

// Save a palette to an open file handle
BOOL CDIBPal::Save(UINT hFile)
{
    HMMIO hmmio;
    MMIOINFO info;
    memset(&info, 0, sizeof(info));
    info.adwInfo[0] = hFile;
    hmmio = mmioOpen(NULL,
                     &info,
                     MMIO_WRITE | MMIO_CREATE | MMIO_ALLOCBUF);
    if (!hmmio) {
        TRACE("mmioOpen failed");
        return FALSE;
    }
    BOOL bResult = Save(hmmio);
    mmioClose(hmmio, MMIO_FHOPEN);
    return bResult;
}

// Save a palette to an open MMIO handle
BOOL CDIBPal::Save(HMMIO hmmio)
{
    // Create a RIFF chunk for a PAL file
    MMCKINFO ckFile;
    ckFile.cksize = 0; // corrected later
    ckFile.fccType = mmioFOURCC('P','A','L',' ');
    if (mmioCreateChunk(hmmio,
                        &ckFile,
                        MMIO_CREATERIFF) != 0) {
        TRACE("Failed to create RIFF-PAL chunk");
        return FALSE;
    }
    // create the LOGPALETTE data which will become
    // the data chunk
    int iColors = GetNumColors();
    ASSERT(iColors > 0);
    int iSize = sizeof(LOGPALETTE)
                + (iColors-1) * sizeof(PALETTEENTRY);
    LOGPALETTE* plp = (LOGPALETTE*) malloc(iSize);
    ASSERT(plp);
    plp->palVersion = 0x300;
    plp->palNumEntries = iColors;
    GetPaletteEntries(0, iColors, plp->palPalEntry);
    // create the data chunk
    MMCKINFO ckData;
    ckData.cksize = iSize; 
    ckData.ckid = mmioFOURCC('d','a','t','a');
    if (mmioCreateChunk(hmmio,
                        &ckData,
                        0) != 0) {
        TRACE("Failed to create data chunk");
        return FALSE;
    }
    // write the data chunk
    if (mmioWrite(hmmio,
                 (char*)plp,
                 iSize) != iSize) {
        TRACE("Failed to write data chunk");
        free(plp);
        return FALSE;
    }
    free(plp);
    // Ascend from the data chunk which will correct the length
    mmioAscend(hmmio, &ckData, 0);
    // Ascend from the RIFF/PAL chunk
    mmioAscend(hmmio, &ckFile, 0);

    return TRUE;
}

/*
@mfunc BOOL | CDIBPal | CreateWash | Create a color cube wash palette.
@syntax BOOL CreateWash();
@rdesc The return value is TRUE if the function succeeds, FALSE if not.
@comm This function creates a 256 color palette consisting of the 20
reserved system colors, a 6 by 6 by 6 RGB color cube and a 20 element 
gray scale. This isn't the best color cube in the world but it's sufficient 
for many simple purposes.
@xref <c CDIBPal>
*/

BOOL CDIBPal::CreateWash()
{
    // Get a screen DC to work with
    HDC hdcScreen = ::CreateCompatibleDC(NULL);
    ASSERT(hdcScreen);
    // allocate a log pal and fill it with the color table info
    LOGPALETTE* pPal = (LOGPALETTE*) malloc(sizeof(LOGPALETTE) 
                     + 256 * sizeof(PALETTEENTRY));
    if (!pPal) {
        TRACE("Out of memory for logpal");
        return FALSE;
    }
    pPal->palVersion = 0x300; // Windows 3.0
    pPal->palNumEntries = 256; // table size
    // Get the system colors in the first and last 10 slots
    ::GetSystemPaletteEntries(hdcScreen, 0, 10, &pPal->palPalEntry[0]);
    ::GetSystemPaletteEntries(hdcScreen, 246, 10, &pPal->palPalEntry[246]);
    // Create a color cube 6x6x6
    PALETTEENTRY* ppe = &pPal->palPalEntry[10];
    for (int r = 0; r < 6; r++) {
        for (int g = 0; g < 6; g++) {
            for (int b = 0; b < 6; b++) {
                ppe->peRed = r * 255 / 6;
                ppe->peGreen = g * 255 / 6;
                ppe->peBlue = b * 255 / 6;
                ppe->peFlags = PC_NOCOLLAPSE;
                ppe++;
            }
        }
    }
    // Create a grey scale
    for (int i = 0; i < 20; i++) {
        ppe->peRed = i * 255 / 20;
        ppe->peGreen = i * 255 / 20;
        ppe->peBlue = i * 255 / 20;
        ppe->peFlags = PC_NOCOLLAPSE;
        ppe++;
    }

    // Detach and delete any existing GDI palette
    if (m_hObject) {
        HGDIOBJ hPal = Detach();
        ASSERT(hPal);
        ::DeleteObject(hPal);
        ASSERT(m_hObject == NULL);
    }    
    BOOL bResult = CreatePalette(pPal);
    free (pPal);

    ::DeleteDC(hdcScreen);
    return bResult;
}

/*
@mfunc BOOL | CDIBPal | CreateSystemColorPalette | Create a color
palette from just the 20 system reserved colors.
@syntax BOOL CreateSystemColorPalette();
@rdesc The return value is TRUE if the function succeeds, FALSE if not.
@comm This function creates a 256 color palette consisting of the 20
reserved system colors, and the rest of the palette set to black. The entire palette 
is set so that a palette index value retrieved using GetNearestPaletteEntry
will map directly to the hardware palette index value for that color.
@xref <c CDIBPal>
*/

BOOL CDIBPal::CreateSystemColorPalette()
{
    // Get a screen DC to work with
    HDC hdcScreen = ::CreateCompatibleDC(NULL);
    ASSERT(hdcScreen);

    // allocate a log pal and fill it with the color table info
    int iSize = sizeof(LOGPALETTE) + 256 * sizeof(PALETTEENTRY);
    LOGPALETTE* pPal = (LOGPALETTE*) malloc(iSize);
    if (!pPal) {
        TRACE("Out of memory for logpal");
        return FALSE;
    }
    memset(pPal, 0, iSize);
    pPal->palVersion = 0x300; // Windows 3.0
    pPal->palNumEntries = 256; // table size
    // Get the system colors in the first and last 10 slots
    ::GetSystemPaletteEntries(hdcScreen, 0, 10, &pPal->palPalEntry[0]);
    ::GetSystemPaletteEntries(hdcScreen, 246, 10, &pPal->palPalEntry[246]);

    // Detach and delete any existing GDI palette
    if (m_hObject) {
        HGDIOBJ hPal = Detach();
        ASSERT(hPal);
        ::DeleteObject(hPal);
        ASSERT(m_hObject == NULL);
    }    
    BOOL bResult = CreatePalette(pPal);
    free (pPal);

    ::DeleteDC(hdcScreen);
    return bResult;
}
