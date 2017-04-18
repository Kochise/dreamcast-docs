/******************************Module*Header*******************************\
* Module Name: loadbmp.c
*
* Contains function that loads a bitmap file
*
* Created: 08-Jan-1992 11:06:37
*
* Copyright (C) 1993-1997 Microsoft Corporation
*
* Contains the main routine for loading a DI bitmap file.
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

extern HWND ghwndMain;
BOOL bSelectDIBPal(HDC, PINFO, LPBITMAPINFO, BOOL);
BOOL bFreeRleFile(PINFO);
BOOL LoadBitmapFile(HDC, PINFO, PSTR);

/******************************Public*Routine******************************\
*
* LoadBitmapFile
*
* Effects:  Loads the bitmap from file and put into pInfo->hBmpSaved
*
* Warnings: pszFileName contains the full path
*
\**************************************************************************/

BOOL LoadBitmapFile(HDC hDC, PINFO pInfo, PSTR pszFileName)
{
    BOOL            bSuccess;
    HANDLE          hFile, hMapFile;
    LPVOID          pMapFile;
    LPBITMAPINFOHEADER pbmh;
    LPBITMAPINFO    pbmi;
    PBYTE           pjTmp;
    ULONG           sizBMI;
    INT             iNumClr;
    BOOL            bCoreHdr;
    PFILEINFO       pFileInfo;


    bSuccess = TRUE;

    if ((hFile = CreateFile(pszFileName, GENERIC_READ, FILE_SHARE_READ, NULL,
            OPEN_EXISTING, FILE_ATTRIBUTE_READONLY, NULL)) == (HANDLE)-1) 
	{
        OutputDebugString("Fail in file open");
        bSuccess = FALSE;
        goto ErrExit1;
    }

    //
    // Create a map file of the opened file
    //
    if ((hMapFile = CreateFileMapping(hFile, NULL,
                             PAGE_READONLY, 0, 0, NULL)) == (HANDLE)-1) 
	{
        OutputDebugString("Fail in creating map file");
        bSuccess = FALSE;
        goto ErrExit2;

    }

    //
    // Map a view of the whole file
    //
    if ((pMapFile = MapViewOfFile(hMapFile, FILE_MAP_READ, 0, 0, 0)) == NULL) 
	{
        OutputDebugString("Fail in mapping view of the Map File object");
        bSuccess = FALSE;
        goto ErrExit3;
    }

    //
    // Saving the DIB file handle, etc in pInfo...
    // freeing existing objects, if any
    //
    bFreeRleFile(pInfo);
    pFileInfo = &(pInfo->RleData.rgFileInfo[0]);
    pFileInfo->hFile      = hFile;
    pFileInfo->hMapFile   = hMapFile;
    pFileInfo->lpvMapView = pMapFile;

    //
    // First check that it is a bitmap file
    //
    if (*((PWORD)pMapFile) != 0x4d42)  // 'BM'
	{              
        MessageBox(ghwndMain, 
			       GetStringRes (IDS_ERR_NOT_A_DIB),
				   NULL, MB_OK);
        bSuccess = FALSE;
        goto ErrExit3;
    }

    //
    // The file header doesn't end on DWORD boundary...
    //
    pbmh = (LPBITMAPINFOHEADER)((PBYTE)pMapFile + sizeof(BITMAPFILEHEADER));

    {
        BITMAPCOREHEADER bmch, *pbmch;
        BITMAPINFOHEADER bmih, *pbmih;
        PBYTE            pjTmp;
        ULONG            ulSiz;

        pbmch = &bmch;
        pbmih = &bmih;

        pjTmp = (PBYTE)pbmh;
        ulSiz = sizeof(BITMAPCOREHEADER);
        while (ulSiz--) {
            *(((PBYTE)pbmch)++) = *(((PBYTE)pjTmp)++);
        }

        pjTmp = (PBYTE)pbmh;
        ulSiz = sizeof(BITMAPINFOHEADER);
        while (ulSiz--) {
            *(((PBYTE)pbmih)++) = *(((PBYTE)pjTmp)++);
        }

        //
        // Use the size to determine if it is a BitmapCoreHeader or
        // BitmapInfoHeader
        //
        // Does PM supports 16 and 32 bpp? How?
        //
        if (bmch.bcSize == sizeof(BITMAPCOREHEADER))
        {
            WORD wBitCount;

            wBitCount = bmch.bcBitCount;
            iNumClr = ((wBitCount == 24) ? 0 : (1 << wBitCount));
            sizBMI = sizeof(BITMAPCOREHEADER)+sizeof(RGBTRIPLE)*iNumClr;
            bCoreHdr = TRUE;
        }
        else            // BITMAPINFOHEADER
        {
            WORD wBitCount;

            wBitCount = bmih.biBitCount;
            switch (wBitCount) {
                case 16:
                case 32:
                    sizBMI = sizeof(BITMAPINFOHEADER)+sizeof(DWORD)*3;
                    break;
                case 24:
                    sizBMI = sizeof(BITMAPINFOHEADER);
                    break;
                default:
                    iNumClr = (1 << wBitCount);
                    sizBMI = sizeof(BITMAPINFOHEADER)+sizeof(RGBQUAD)*iNumClr;
                    break;
            }
            bCoreHdr = FALSE;
        }

    }

    if ((pbmi = (LPBITMAPINFO) LocalAlloc(LMEM_FIXED,sizBMI)) == NULL) 
	{
        bSuccess = FALSE;
        goto ErrExit3;
    }

    //
    // Make sure we pass in a DWORD aligned BitmapInfo to CreateDIBitmap
    // Otherwise, exception on the MIPS platform
    // CR!!!  Equivalent to memcpy
    //
    pjTmp = (PBYTE)pbmi;

    while(sizBMI--)
    {
        *(((PBYTE)pjTmp)++) = *(((PBYTE)pbmh)++);
    }

    //
    // assuming CreateDIBitmap() is doing a byte fetch...
    //
    pMapFile = (PBYTE)pMapFile + ((BITMAPFILEHEADER *)pMapFile)->bfOffBits;

    //
    // Select the palette into the DC first before CreateDIBitmap()
    //
    bSelectDIBPal(hDC, pInfo, pbmi, bCoreHdr);
    if ((pInfo->hBmpSaved = CreateDIBitmap(hDC, (LPBITMAPINFOHEADER)pbmi,
                        CBM_INIT, pMapFile, pbmi, DIB_RGB_COLORS)) == NULL) 
	{
        OutputDebugString("Fail in creating DIB bitmap from file!");
        bSuccess = FALSE;
        goto ErrExit4;
    }

    //
    // Saving the DIB...free memory when the windows is closed.
    //
    pInfo->RleData.rgpjFrame[0] = pMapFile;
    pInfo->RleData.rgpbmi[0]    = pbmi;
    pInfo->RleData.pbmi         = (PBITMAPINFO) &(pInfo->RleData.rgpbmi[0]);
    pInfo->RleData.ulFrames     = 1;
    pInfo->RleData.ulFiles      = 1;

    // set flag to use original DIB as source for blting so HT can be done
    pInfo->bUseDIB = TRUE;

    pInfo->bCoreHdr = bCoreHdr;

    return (bSuccess);

ErrExit4:
    LocalFree(pbmi);
ErrExit3:
    CloseHandle(hMapFile);
ErrExit2:
    CloseHandle(hFile);
ErrExit1:

    return (bSuccess);

}
