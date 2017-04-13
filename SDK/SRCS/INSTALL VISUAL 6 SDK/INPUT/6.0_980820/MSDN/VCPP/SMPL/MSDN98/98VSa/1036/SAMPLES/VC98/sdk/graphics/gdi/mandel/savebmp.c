/******************************Module*Header*******************************\
* Module Name: savebmp.c
*
*
* Created: 06-Jan-1992 10:59:36
*
* Copyright (C) 1993-1997 Microsoft Corporation
*
* Contains the main routine, SaveBitmapFile, for saving a DDB into file
* in DIB format.
*
* Dependencies:
*
*   (#defines)
*   (#includes)
*       #include <windows.h>
*       #include "jtypes.h"
*
\**************************************************************************/
#include <windows.h>
#include "julia.h"

extern HPALETTE ghPal;
extern HWND ghwndMain;
extern char   gtext[256];
BOOL SaveBitmapFile(HDC, HBITMAP, PSTR);
// void ErrorOut(char errstring[30]);

/******************************Public*Routine******************************\
* SaveBitmapFile
*
*
* Effects: Save pInfo->hBmpSaved into disk specified by pszFileName
*
* Warnings: assumes hBmpSaved is not selected into window's DC other than
*           pInfo->hwnd's DC
*
\**************************************************************************/

BOOL SaveBitmapFile(HDC hDC, HBITMAP hBmp, PSTR pszFileName)
{
    int         hFile;
    OFSTRUCT    ofReOpenBuff;
    HBITMAP     hTmpBmp, hBmpOld;
    BOOL        bSuccess;
    BITMAPFILEHEADER    bfh;
    PBITMAPINFO pbmi;
    PBYTE       pBits;
    BITMAPINFO  bmi;
    PBYTE pjTmp, pjTmpBmi;
    ULONG sizBMI;


    bSuccess = TRUE;
#if 0
    if (ghPal) {
        SelectPalette(hDC, ghPal, FALSE);
        RealizePalette(hDC);
    }
#endif
    if (!hBmp) {
        MessageBox(ghwndMain, 
			       GetStringRes (IDS_NO_BITMAP_TO_SAVE),
				   NULL, MB_OK);
        return FALSE;
    }

    //
    // Let the graphics engine to retrieve the dimension of the bitmap for us
    // GetDIBits uses the size to determine if it's BITMAPCOREINFO or BITMAPINFO
    // if BitCount != 0, color table will be retrieved
    //
    bmi.bmiHeader.biSize = 0x28;              // GDI need this to work
    bmi.bmiHeader.biBitCount = 0;             // don't get the color table
    if ((GetDIBits(hDC, hBmp, 0, 0, (LPSTR)NULL, &bmi, DIB_RGB_COLORS)) == 0) {
       return FALSE;
    }

    //
    // Now that we know the size of the image, alloc enough memory to retrieve
    // the actual bits
    //
    if ((pBits = (PBYTE)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT,
                bmi.bmiHeader.biSizeImage)) == NULL) {
        return FALSE;
    }

    //
    // Note: 24 bits per pixel has no color table.  So, we don't have to
    // allocate memory for retrieving that.  Otherwise, we do.
    //
    pbmi = &bmi;                                      // assume no color table

    switch (bmi.bmiHeader.biBitCount) {
        case 24:                                      // has color table
            sizBMI = sizeof(BITMAPINFOHEADER);
            break;
        case 16:
        case 32:
            sizBMI = sizeof(BITMAPINFOHEADER)+sizeof(DWORD)*3;
            break;
        default:
            sizBMI = sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*(1<<bmi.bmiHeader.biBitCount);
            break;

    }

    //
    // Allocate memory for color table if it is not 24bpp...
    //
    if (sizBMI != sizeof(BITMAPINFOHEADER)) {
        ULONG       sizTmp;
        //
        // I need more memory for the color table
        //
        if ((pbmi = (PBITMAPINFO)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT, sizBMI )) == NULL) {
            bSuccess = FALSE;
            goto ErrExit1;
        }
        //
        // Now that we've a bigger chunk of memory, let's copy the Bitmap
        // info header data over
        //
        pjTmp = (PBYTE)pbmi;
        pjTmpBmi = (PBYTE)&bmi;
        sizTmp = sizeof(BITMAPINFOHEADER);

        while(sizTmp--)
        {
            *(((PBYTE)pjTmp)++) = *((pjTmpBmi)++);
        }
    }

    //
    // Let's open the file and get ready for writing
    //
    if ((hFile = OpenFile(pszFileName, (LPOFSTRUCT)&ofReOpenBuff,
                 OF_CREATE | OF_WRITE)) == -1) {
        MessageBox(ghwndMain, GetStringRes(IDS_FILE_OPEN_FAILED), 
				   NULL, MB_OK);
        goto ErrExit2;
    }

    //
    // But first, fill in the info for the BitmapFileHeader
    //
    bfh.bfType = 0x4D42;                            // 'BM'
    bfh.bfSize = sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+sizBMI+
        pbmi->bmiHeader.biSizeImage;
    bfh.bfReserved1 =
    bfh.bfReserved2 = 0;
    bfh.bfOffBits = sizeof(BITMAPFILEHEADER)+sizBMI;

    //
    // Write out the file header now
    //
    if (_lwrite(hFile, (LPSTR)&bfh, sizeof(BITMAPFILEHEADER)) == -1) {
        bSuccess = FALSE;
        goto ErrExit3;
    }

    //
    // Bitmap can't be selected into a DC when calling GetDIBits
    // Assume that the hDC is the DC where the bitmap would have been selected
    // if indeed it has been selected
    //
    if (hTmpBmp = CreateCompatibleBitmap(hDC, pbmi->bmiHeader.biWidth, pbmi->bmiHeader.biHeight)) {
        hBmpOld = SelectObject(hDC, hTmpBmp);
        if ((GetDIBits(hDC, hBmp, 0, pbmi->bmiHeader.biHeight, (LPSTR)pBits, pbmi, DIB_RGB_COLORS))==0){
            bSuccess = FALSE;
            goto ErrExit4;
        }
    } else {
        MessageBox(ghwndMain, 
			GetStringRes (IDS_BITMAP_NOT_CREATED),
			NULL, MB_OK);
        bSuccess = FALSE;
        goto ErrExit3;
    }

    //
    // Now write out the BitmapInfoHeader and color table, if any
    //
    if (_lwrite(hFile, (LPSTR)pbmi, sizBMI) == -1) {
        bSuccess = FALSE;
        goto ErrExit4;
    }

    //
    // write the bits also
    //
    if (_lwrite(hFile, (LPSTR)pBits, pbmi->bmiHeader.biSizeImage) == -1) {
        bSuccess = FALSE;
        goto ErrExit4;
    }


ErrExit4:
    SelectObject(hDC, hBmpOld);
    DeleteObject(hTmpBmp);
ErrExit3:
    _lclose(hFile);
ErrExit2:
    GlobalFree(pbmi);
ErrExit1:
    GlobalFree(pBits);
    return bSuccess;
}


#if 0 
/************************************************************************
 * void ErrorOut(char errstring[30])
 *
 * Purpose: Print out an meainful error code by means of
 *	  GetLastError and printf
 *
 * Inputs:  errstring - the action that failed, passed by the
 *		      calling proc.
 *
 * Returns: none
 *
 * Calls:   GetLastError
 *
 * History:
 * 09-13-91 Pete Grey   Created.
 *
\************************************************************************/


void ErrorOut(char errstring[30])
{
DWORD Error;
CHAR  str[80];

Error= GetLastError();
wsprintf((LPSTR) str, "Error on %s = %d\n", errstring, Error);
OutputDebugString(str);
}

#endif