/******************************Module*Header*******************************\
* Module Name: dibmp.c
*
* Contains functions that manipulate the DIB color
*
* Copyright (C) 1993-1997 Microsoft Corporation
*
* These functions will be called from the ChildWndProc() as it processes
* the corresponding WM_COMMAND message for changing the color of the bitmap.
*
* iCreatePenFrPal() is called by InitializeApp() for creating pens based on
* either system or custom palette.
*
* Dependencies:
*       none
*
\**************************************************************************/
#include <windows.h>
#include <stdio.h>
#include "julia.h"
#include "dibmp.h"

#define CYCLETHRD

//#define DEBUG

#ifndef DEBUG
   #undef OutputDebugString
   #define OutputDebugString(LPCSTR)
#endif

extern HPALETTE        ghPal, ghPalOld;
extern HWND ghwndMain;
extern HWND ghwndClient;
extern HANDLE hQuitEvent;
extern char   gtext[256];
extern HANDLE ghAccel;
BOOL bValidMode(INT);
BOOL bColor2BW(PBITMAPINFO);
BOOL bChangeDIBColor(HDC, PINFO, INT);
BOOL bColorShift(PBITMAPINFO);
BOOL bColorReplace(PBITMAPINFO);
BOOL bColorCycle(HDC, RECT, PBYTE, PBITMAPINFO, PINFO);
BOOL bCycle(HWND);
BOOL bColor2Mono(HDC, PINFO, PBITMAPINFO);
INT  iCreatePenFrPal(HDC, PVOID *, INT, HPALETTE *);
HPALETTE CopyPalette(HPALETTE);
extern PINFO pGetInfoData(HWND);
extern BOOL bReleaseInfoData(HWND);

/******************************Public*Routine******************************\
*
* bChangeDIBColor
*
* Effects: Main entry point for the color changing operations.  It
*          1. validates the operation
*          2. retrieves the bitmap info from the graphics engine
*          3. dispatches the call to the right function
*          4. saves the resulting bitmap
*          5. updates the screen
\**************************************************************************/
BOOL bChangeDIBColor(HDC hDC, PINFO pInfo, INT iMode)
{
    BOOL                 bSuccess;
    HBITMAP              hTmpBmp, hBmpOld;
    PBITMAPINFO          pbmi;
    PBYTE                pBits;
    BITMAPINFO           bmi;
    PBYTE                pjTmp, pjTmpBmi;
    ULONG                sizBMI;
    RECT                 rc;
    BOOL                 bCycle;


    bSuccess = TRUE;
    if (!pInfo->hBmpSaved) 
	{
        MessageBox(ghwndMain, GetStringRes(IDS_NO_BITMAP), NULL, MB_OK);
        return FALSE;
    }

    if (!bValidMode(iMode)) 
	{
        OutputDebugString ("bChangeDIBColor: invalid mode!");
        return FALSE;
    }

    if (pInfo->hPal) {
        HPALETTE hPalOld;
        int     ii;

        hPalOld = SelectPalette(hDC, pInfo->hPal, FALSE);
        ii = RealizePalette(hDC);

        if (ii){
            UpdateColors (hDC);
        }

    }

    //
    // Let the graphics engine to retrieve the dimension of the bitmap for us
    // GetDIBits uses the size to determine if it's BITMAPCOREINFO or BITMAPINFO
    // if BitCount != 0, color table will be retrieved
    //
    bmi.bmiHeader.biSize = 0x28;              // GDI need this to work
    bmi.bmiHeader.biBitCount = 0;             // don't get the color table
    if ((GetDIBits(hDC, pInfo->hBmpSaved, 0, 0, (LPSTR)NULL, &bmi, DIB_RGB_COLORS)) == 0) 
	{
        OutputDebugString ("GetDIBits failed!");
        return FALSE;
    }

    //
    // Now that we know the size of the image, alloc enough memory to retrieve
    // the actual bits
    //
    if ((pBits = (PBYTE)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT,
                bmi.bmiHeader.biSizeImage)) == NULL) 
	{
        return FALSE;
    }

    //
    // Note: 24 bits per pixel has no color table.  So, we don't have to
    // allocate memory for retrieving that.  Otherwise, we do.
    //
    pbmi = &bmi;                                      // assume no color table
    if (bmi.bmiHeader.biBitCount != 24) {             // has color table
        sizBMI = sizeof(BITMAPINFO)+sizeof(RGBQUAD)*(1<<bmi.bmiHeader.biBitCount);
        //
        // I need more memory for the color table
        //
        if ((pbmi = (PBITMAPINFO)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT, sizBMI )) == NULL) 
		{
            bSuccess = FALSE;
            goto ErrExit1;
        }

        //
        // Now that we've a bigger chunk of memory, let's copy the Bitmap
        // info header data over
        //
        pjTmp = (PBYTE)pbmi;
        pjTmpBmi = (PBYTE)&bmi;
        sizBMI = sizeof(BITMAPINFOHEADER);

        while(sizBMI--)
        {
            *(((PBYTE)pjTmp)++) = *((pjTmpBmi)++);
        }

    }

    //
    // Bitmap can't be selected into a DC when calling GetDIBits
    // Assume that the hDC is the DC where the bitmap would have been selected
    // if indeed it has been selected
    //
    if (hTmpBmp = CreateCompatibleBitmap(hDC, pbmi->bmiHeader.biWidth, pbmi->bmiHeader.biHeight)) {
        hBmpOld = SelectObject(hDC, hTmpBmp);
        if ((GetDIBits(hDC, pInfo->hBmpSaved, 0, pbmi->bmiHeader.biHeight, (LPSTR)pBits, pbmi, DIB_RGB_COLORS))==0)
		{
            bSuccess = FALSE;
            goto ErrExit4;
        }
    } else 
	{
        OutputDebugString ("Failed in creating bitmap!");
        bSuccess = FALSE;
        goto ErrExit3;
    }

    bCycle = FALSE;
    switch (iMode) {
        case MM_BW:
            if ((!bColor2Mono(hDC, pInfo, pbmi)) ||
                (pInfo->hBmpMono == NULL)) 
			{
                OutputDebugString ("Failed in Color2Mono!");
                bSuccess = FALSE;
                goto ErrExit4;
            }
            pInfo->bUseMono = TRUE;
            break;
        case MM_SHIFT:

            if (!bColorShift(pbmi)) 
			{
                OutputDebugString ("Failed in ColorShift!");
                bSuccess = FALSE;
                goto ErrExit4;
            }
            break;
        case MM_CUSTOM:
            bColorReplace(pbmi);
            break;

        case MM_CYCLE:
            bCycle = TRUE;
            break;

        default:
            bSuccess = FALSE;
            break;
    }

    if (SetDIBits(hDC, pInfo->hBmpSaved, 0, pbmi->bmiHeader.biHeight, (LPSTR)pBits,
            pbmi, DIB_RGB_COLORS) == 0) 
	{
        bSuccess = FALSE;
        goto ErrExit4;
    }

    if (bCycle)
        pInfo->bSetDIBsToDevice = TRUE;

#if 0
    if (pInfo->bSetDIBsToDevice && !pInfo->bUseMono) {
        //GetWindowRect(pInfo->hwnd, &rc);
        GetClientRect(pInfo->hwnd, &rc);
        //SetMapMode(hDC, MM_TEXT);

        //if (SetDIBitsToDevice(hDC, 0, 0, rc.right-rc.left, rc.bottom-rc.top,
        //     0, 0, 0, pbmi->bmiHeader.biHeight, (LPSTR)pBits, pbmi, DIB_RGB_COLORS) == 0) {
        //    MessageBox(ghwndMain, "Failed in SetDIBitsToDevice!", "Error", MB_OK);
		//    MessageBox(ghwndMain, "SetDIBitsToDevice でエラーが発生しました!", "エラー", MB_OK);
        //    bSuccess = FALSE;
        //    goto ErrExit4;
        //}
    } else 
	{
#endif
        InvalidateRect(pInfo->hwnd, NULL, FALSE);
//  }

    if (bCycle) {
        //
        // This is commented out because I don't want the system colors
        // be affected by color cycling
        //
        //SetSystemPaletteUse(hDC, SYSPAL_NOSTATIC);
        bColorCycle(hDC, rc, pBits, pbmi, pInfo);
        //SetSystemPaletteUse(hDC, SYSPAL_STATIC);
    }

ErrExit4:
    SelectObject(hDC, hBmpOld);
    DeleteObject(hTmpBmp);
ErrExit3:
    GlobalFree(pbmi);
ErrExit1:
    GlobalFree(pBits);
    return bSuccess;
}


/******************************Public*Routine******************************\
*
* bValidMode
*
* Effects: validates the change mode for ChangeDIBColor function
*          returns TRUE if mode is valid.  Otherwise, FALSE
\**************************************************************************/
BOOL bValidMode(INT iMode)
{
    if ((iMode == MM_BW)     || (iMode == MM_SHIFT) ||
        (iMode == MM_CUSTOM) || (iMode == MM_CYCLE))
        return TRUE;
    else
        return FALSE;
}

/******************************Public*Routine******************************\
*
* bColor2BW
*
* Effects: changes the color table in the bitmapinfo to black and white
*
* Warnings: doesn't check if pbmi is valid or not
\**************************************************************************/
BOOL bColor2BW(PBITMAPINFO pbmi)
{
    INT iEntry;

    //
    // CR! What's the right behavior?  Maybe I should convert this to a
    // monochrome bitmap.  This will be very useful in MaskBlt().
    //
    iEntry = 1<<pbmi->bmiHeader.biBitCount;
    while (--iEntry >= 0) {
        if (iEntry <= iEntry / 2) {
                pbmi->bmiColors[iEntry].rgbBlue     = 0x00;
                pbmi->bmiColors[iEntry].rgbGreen    = 0x00;
                pbmi->bmiColors[iEntry].rgbRed      = 0x00;
                pbmi->bmiColors[iEntry].rgbReserved = 0x00;
         } else {
                pbmi->bmiColors[iEntry].rgbBlue     = 0xFF;
                pbmi->bmiColors[iEntry].rgbGreen    = 0xFF;
                pbmi->bmiColors[iEntry].rgbRed      = 0xFF;
                pbmi->bmiColors[iEntry].rgbReserved = 0x00;
        }
    }
    return TRUE;
}


/******************************Public*Routine******************************\
*
* bColorShift
*
* Effects: Shifting entries of the color table
*
\**************************************************************************/

BOOL bColorShift(PBITMAPINFO pbmi)
{
    INT iEntry;
    RGBQUAD     Tmp;

    iEntry = 1<<pbmi->bmiHeader.biBitCount;

    Tmp.rgbBlue     = pbmi->bmiColors[iEntry-1].rgbBlue;
    Tmp.rgbGreen    = pbmi->bmiColors[iEntry-1].rgbGreen;
    Tmp.rgbRed      = pbmi->bmiColors[iEntry-1].rgbRed;
    Tmp.rgbReserved = pbmi->bmiColors[iEntry-1].rgbReserved;

    while (--iEntry > 0) {
         pbmi->bmiColors[iEntry].rgbBlue     =
            pbmi->bmiColors[iEntry-1].rgbBlue;
         pbmi->bmiColors[iEntry].rgbGreen    =
            pbmi->bmiColors[iEntry-1].rgbGreen;
         pbmi->bmiColors[iEntry].rgbRed      =
            pbmi->bmiColors[iEntry-1].rgbRed;
         pbmi->bmiColors[iEntry].rgbReserved =
            pbmi->bmiColors[iEntry-1].rgbReserved;
    }
    pbmi->bmiColors[0].rgbBlue     = Tmp.rgbBlue;
    pbmi->bmiColors[0].rgbGreen    = Tmp.rgbGreen;
    pbmi->bmiColors[0].rgbRed      = Tmp.rgbRed;
    pbmi->bmiColors[0].rgbReserved = Tmp.rgbReserved;
    return TRUE;

}

BOOL bColorReplace(PBITMAPINFO pbmi)
{
    return FALSE;
    UNREFERENCED_PARAMETER(pbmi);
}

/******************************Public*Routine******************************\
*
* bColorCycle
*
* Effects:  Create a logical palette with a good spread of color
*           Animate the palette, shift the palette entries and animate
*           again for 256 times altogether.
*           This creates the color cycling effect.
*
* Warnings: Only works in device that support palette.
\**************************************************************************/

BOOL bColorCycle(HDC hDC, RECT rc, PBYTE pBits, PBITMAPINFO pbmi, PINFO pInfo)
{
    INT             iEntry, i, iNumClr;
    PLOGPALETTE     plogPat;
    ULONG           ulSize;
    BOOL            bSuccess;
    HPALETTE        hPal, hPalOld;
    PALETTEENTRY    peTemp;

#ifdef CYCLETHRD
    DWORD           dwWait;
#else
    MSG             msg;
#endif
    BOOL            bQuit;

//UINT uRC;

    bSuccess = TRUE;
    iEntry = 1<<pbmi->bmiHeader.biBitCount;

    iNumClr = 236;          // 256 minus 20 reserved colors
    ulSize = sizeof(LOGPALETTE)+sizeof(PALETTEENTRY)*256;

    if ((plogPat = (PLOGPALETTE) GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT, ulSize)) == NULL) 
	{
        bSuccess = FALSE;
        goto ErrExit1;
    }

    plogPat->palVersion = 0x300;
    plogPat->palNumEntries = (WORD) 256;

    {
    int     iFirst, iSecond, iInc;

        iFirst = iNumClr/3;
        iSecond = iFirst * 2;
        iInc = (iNumClr <= 256) ? 3 : 1;

        for (i = 0; i < iNumClr; i++) {
            if (i < iFirst) {
                plogPat->palPalEntry[i+10].peBlue   = 255-(i+1)*iInc;
                plogPat->palPalEntry[i+10].peGreen  = 0;
                plogPat->palPalEntry[i+10].peRed    = (i+1)*iInc;
                plogPat->palPalEntry[i+10].peFlags  = PC_RESERVED;
                continue;
            }
            if (i < iSecond) {
                plogPat->palPalEntry[i+10].peBlue   = 0;
                plogPat->palPalEntry[i+10].peGreen  = (i+1-iFirst)*iInc;
                plogPat->palPalEntry[i+10].peRed    = 255-(i+1-iFirst)*iInc;
                plogPat->palPalEntry[i+10].peFlags  = PC_RESERVED;
                continue;
            }
            plogPat->palPalEntry[i+10].peBlue   = (i+1-iSecond)*iInc;
            plogPat->palPalEntry[i+10].peGreen  = 255-(i+1-iSecond)*iInc;
            plogPat->palPalEntry[i+10].peRed    = 0;
            plogPat->palPalEntry[i+10].peFlags  = PC_RESERVED;
        }
    }

    if ((hPal = CreatePalette(plogPat)) == (HPALETTE) NULL) 
	{
        bSuccess = FALSE;
        goto ErrExit2;
    }

    pInfo->hCyclePal = hPal;

    hPalOld = SelectPalette(hDC, hPal, FALSE);
    RealizePalette(hDC);


#ifndef CYCLETHRD

    bQuit = FALSE;
    while (TRUE && !bQuit) {

        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            //sprintf( gtext,"msg = %lx\n", msg.message);
            //OutputDebugString( gtext );

            if ((msg.message == WM_QUIT) || (msg.message == WM_CLOSE) ||
                ((msg.message == WM_SYSCOMMAND) && (msg.wParam == SC_CLOSE))) {
                sprintf( gtext,"msg = %lx, wPram = %lx\n", msg.message, msg.wParam);
                OutputDebugString( gtext );
                bQuit = TRUE;
                PostMessage(msg.hwnd, msg.message, msg.wParam, msg.lParam);
            } else {
                if (!TranslateAccelerator( ghwndMain, ghAccel, &msg) &&
                    !TranslateMDISysAccel(  ghwndClient, &msg)          ) {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
           }
        }

#else
    bQuit = FALSE;
    while (TRUE) {
        //
        // If parent gets a WM_CLOSE, we will return
        //
        dwWait = WaitForSingleObject(pInfo->hQuitEvent, 0);
        if (dwWait == WAIT_TIMEOUT) 
		{
            MessageBox(ghwndMain, 
				       GetStringRes(IDS_CYCLE_THREAD_QUIT),
					   GetStringRes (IDS_CYCLE_THREAD), MB_OK);
            break;
        }
#endif
        if (!pInfo->bClrCycle) {
            sprintf( gtext,"NOT to animate palette\n");
            OutputDebugString( gtext );
            bQuit = TRUE;
        }

        if (!bQuit) {
            sprintf( gtext,"About to animate palette\n");
            OutputDebugString( gtext );

            peTemp = plogPat->palPalEntry[10];
            for (i = 0; i < iNumClr; i++) {
                plogPat->palPalEntry[i+10] = plogPat->palPalEntry[i+10+1];
            }
            plogPat->palPalEntry[i-1+10] = peTemp;

            if (!AnimatePalette(hPal, 0, 256, plogPat->palPalEntry)) {
                sprintf( gtext,"Anmiate palette failed\n");
                OutputDebugString( gtext );
            }
            Sleep(50);

//
// This is not needed anymore starting from build 475 14-Jun-1993
//
#if 0
            //
            // Not realizing stops color-cycling after moving back into
            // foreground
            //
            if ((uRC = RealizePalette(hDC)) == GDI_ERROR) {
                sprintf( gtext,"Realize palette failed\n");
                OutputDebugString( gtext );
            }

            if (!UpdateColors(hDC)) {
                sprintf( gtext,"Update Colors failed\n");
                OutputDebugString( gtext );
            }
#endif
        }

    }

    SelectPalette(hDC, hPalOld, 0);
    DeleteObject(hPal);
ErrExit2:
    GlobalFree(plogPat);
ErrExit1:
    return bSuccess;

}


/******************************Public*Routine******************************\
*
* bCycle
*
* Effects: Wrapper for doing color cycling in a separate thread
*          Called from MM_CYCLE
*
* Warnings: presents problem when the MDI child is closed if this thread
*           is not done yet.  We will have to wait until DeleteDC is
*           fully functional.
\**************************************************************************/
BOOL bCycle(HWND hwnd)
{
    HDC     hDC;
    PINFO   pInfo;

    if ((pInfo = pGetInfoData(hwnd)) == NULL) {
        return 0L;
    }

    hDC = GetDC(pInfo->hwnd);
    bChangeDIBColor(hDC, pInfo, MM_CYCLE);
    ReleaseDC(pInfo->hwnd, hDC);

    bReleaseInfoData(hwnd);

    ExitThread(0);
    return TRUE;
}


/******************************Public*Routine******************************\
*
* bColor2Mono
*
* Effects: Create a monochrome bitmap out of the colored one
*          Using a different a source background clr every time it is called
*          Saving the Monochrome bitmap in pInfo
*
* Warnings: It's more straight forward to use GetDIBits than this but
*           that means some big changes to the bChangeDIBColor.
*
\**************************************************************************/

BOOL bColor2Mono(HDC hDC, PINFO pInfo, PBITMAPINFO pbmi) {
    HDC     hDCMemDest, hDCMemSrc;
    HBITMAP hOldBmpDest, hOldBmpSrc;
    INT     iWidth, iHeight, iEntry;
    static INT iCount=0;


    iWidth = pbmi->bmiHeader.biWidth;
    iHeight = pbmi->bmiHeader.biHeight;

    if (pInfo->hBmpMono)
        DeleteObject(pInfo->hBmpMono);

    pInfo->hBmpMono = CreateBitmap(iWidth, iHeight, pbmi->bmiHeader.biPlanes, 1, NULL);
    if (pInfo->hBmpMono == NULL) {
        return(FALSE);
    }

    hDCMemDest = CreateCompatibleDC(hDC);
    hDCMemSrc  = CreateCompatibleDC(hDC);

    if (pInfo->hPal) {
        SelectPalette(hDCMemSrc, pInfo->hPal, FALSE);
        RealizePalette(hDCMemSrc);
    }

    iEntry = 1<<pbmi->bmiHeader.biBitCount;
    SetBkColor(hDCMemSrc, RGB( pbmi->bmiColors[iCount].rgbRed,
                               pbmi->bmiColors[iCount].rgbGreen,
                               pbmi->bmiColors[iCount].rgbBlue) );
    //SetBkColor(hDCMemDest, RGB( 0, 0, 0));
    //SetTextColor(hDCMemDest, RGB( 255, 255, 255));

    iCount++;
    if (iCount >= iEntry)
        iCount = 0;

    hOldBmpDest = SelectObject(hDCMemDest, pInfo->hBmpMono);
    hOldBmpSrc  = SelectObject(hDCMemSrc,  pInfo->hBmpSaved);
    BitBlt(hDCMemDest, 0, 0, iWidth, iHeight, hDCMemSrc, 0, 0, SRCCOPY);

    pInfo->hBmpMono = SelectObject(hDCMemDest, hOldBmpDest);
    SelectObject(hDCMemSrc, hOldBmpSrc);

    DeleteDC(hDCMemDest);
    DeleteDC(hDCMemSrc);

    return(TRUE);

}


/******************************Public*Routine******************************\
*
* iCreatePenFrPal
*
* Effects: Create an array of pens from palette.
*          If device supports palette, then first creates a logical palette
*          with a good spread of color. Then select the logical palette into
*          the DC. Create pen that corresponds to each palette entry.
*          If system does not support palette, then use the system palette.
*
*          prghPen pointer to an array of hPen
*                  If this is NULL, the required size of the array is
*                  returned. If this is not NULL, the array will be filled
*                  with hPens.
*
*          returns the number of hPens created.
*
\**************************************************************************/
INT iCreatePenFrPal(HDC hDC, PVOID *prghPen, INT iWidth, HPALETTE *phPal)
{
    INT             iNumClr, iResult, i, iEntry;
    PLOGPALETTE     plogPat;
    ULONG           ulSize;

    iResult = 0;

    if (!((GetDeviceCaps(hDC, RASTERCAPS)) & RC_PALETTE)) {

        if (iNumClr = GetSystemPaletteEntries(hDC, 0, 0, NULL)) {
            if (prghPen == NULL) {
                return (iNumClr);
            }

            if (iWidth < 0) 
			{
                MessageBox(GetFocus(), GetStringRes (IDS_IVALID_PEN_WIDTH),
						   NULL, MB_OK);
                return 0L;
            }

            for (i = 0; i < iNumClr; i++) {
                prghPen[i] =
                     (PVOID) CreatePen(PS_SOLID, iWidth, PALETTEINDEX(i));
                iResult = i;
#if 0
                SelectObject(hDC, (HPEN)prghPen[i]);
                MoveToEx(hDC, i*iWidth, 0, NULL);
                LineTo(hDC, i*iWidth, 300);
#endif
            }
            return iResult;
        }

        // GetPaletteEntries returns 0
        iNumClr = 1 << GetDeviceCaps(hDC, BITSPIXEL);

        if (iNumClr <= 16) {
            sprintf( gtext,"Assertion failed: iCreatePenFrPal() \n");
            OutputDebugString( gtext);
            sprintf( gtext,"iNumClr <= 16! iNumClr = %d\n", iNumClr);
            OutputDebugString( gtext);
            return (iNumClr);
        }

        // Assuming at least 16 bit device
        //
        iNumClr = 768;      // COLORREF format: 0x00bbggrr r,g,b=[0,255]

        if (prghPen == NULL) {
            return (iNumClr);
        }

        if (iWidth < 0) 
		{
            MessageBox(GetFocus(), GetStringRes(IDS_IVALID_PEN_WIDTH),
					   NULL, MB_OK);
            return 0L;
        }

        for (i = 0; i < iNumClr; i++) {
            if (i < 256) {
                prghPen[i] =
                    (PVOID) CreatePen(PS_SOLID, iWidth, RGB(i,0,255-i));
                iResult = i;
#if 0
                SelectObject(hDC, (HPEN)prghPen[i]);
                MoveToEx(hDC, i*iWidth, 0, NULL);
                LineTo(hDC, i*iWidth, 300);
#endif
                continue;
            }

            if (i < 512) {
                prghPen[i] =
                    (PVOID) CreatePen(PS_SOLID, iWidth, RGB(511-i,i-256,0));
                iResult = i;
#if 0
                SelectObject(hDC, (HPEN)prghPen[i]);
                MoveToEx(hDC, i*iWidth, 0, NULL);
                LineTo(hDC, i*iWidth, 300);
#endif
                continue;
            }


            prghPen[i] =
                (PVOID) CreatePen(PS_SOLID, iWidth, RGB(0,767-i,i-512));
            iResult = i;
#if 0
            SelectObject(hDC, (HPEN)prghPen[i]);
            MoveToEx(hDC, i*iWidth, 0, NULL);
            LineTo(hDC, i*iWidth, 300);
#endif
        }

        return iResult;
    }

    //
    // Palette managed device
    //
    iEntry = iNumClr = 1 << GetDeviceCaps(hDC, BITSPIXEL);

    if (iNumClr > 256) {
        sprintf( gtext,"Assertion failed: iCreatePenFrPal() \n");
        OutputDebugString( gtext);
        sprintf( gtext,"iNumClr > 256! iNumClr = %d\n", iNumClr);
        OutputDebugString( gtext);
        iEntry=iNumClr = 256;
    }

    ulSize = sizeof(LOGPALETTE)+sizeof(PALETTEENTRY)*iNumClr;

    iNumClr -= GetDeviceCaps(hDC, NUMRESERVED);

    if (prghPen == NULL)
        return iNumClr;

    if ((plogPat = (PLOGPALETTE) GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT, ulSize)) == NULL) 
	{
        goto ErrExit1;
    }

    plogPat->palVersion = 0x300;
    plogPat->palNumEntries = (WORD) iEntry;

    {
    int     iFirst, iSecond, iInc;

        iFirst = iNumClr/3;
        iSecond = iFirst * 2;
        iInc = (iNumClr <= 256) ? 3 : 1;

        for (i = 0; i < iNumClr; i++) {
            if (i < iFirst) {
                plogPat->palPalEntry[i+10].peBlue   = 255-(i+1)*iInc;
                plogPat->palPalEntry[i+10].peGreen  = 0;
                plogPat->palPalEntry[i+10].peRed    = (i+1)*iInc;
                plogPat->palPalEntry[i+10].peFlags  = PC_RESERVED;
                continue;
            }
            if (i < iSecond) {
                plogPat->palPalEntry[i+10].peBlue   = 0;
                plogPat->palPalEntry[i+10].peGreen  = (i+1-iFirst)*iInc;
                plogPat->palPalEntry[i+10].peRed    = 255-(i+1-iFirst)*iInc;
                plogPat->palPalEntry[i+10].peFlags  = PC_RESERVED;
                continue;
            }
            plogPat->palPalEntry[i+10].peBlue   = (i+1-iSecond)*iInc;
            plogPat->palPalEntry[i+10].peGreen  = 255-(i+1-iSecond)*iInc;
            plogPat->palPalEntry[i+10].peRed    = 0;
            plogPat->palPalEntry[i+10].peFlags  = PC_RESERVED;
        }
    }

    DeleteObject(*phPal);

    if ((*phPal = CreatePalette(plogPat)) == (HPALETTE) NULL) 
	{
        goto ErrExit2;
    }
    if (*phPal) {
       SelectPalette(hDC, *phPal, FALSE);
       RealizePalette(hDC);
    }

    for (i = 0; i < iNumClr; i++) {
        HPEN    hPen;

        hPen = CreatePen(PS_SOLID, iWidth, PALETTEINDEX(i+10));
        prghPen[i] = (PVOID) hPen;
        iResult = i;
#if 0
        SelectObject(hDC, hPen);
        MoveToEx(hDC, i*iWidth, 0, NULL);
        LineTo(hDC, i*iWidth, 300);
#endif
    }

ErrExit2:
    GlobalFree(plogPat);
ErrExit1:
    return iResult;

}


/******************************Public*Routine******************************\
*
* HPALETTE CopyPalette
*
\**************************************************************************/

HPALETTE CopyPalette(HPALETTE hPalSrc)
{
    PLOGPALETTE     plogPal;
    PBYTE           pjTmp;
    int             iNumEntries=0;
    HPALETTE        hPal;

    if ((iNumEntries = GetPaletteEntries(hPalSrc, 0, iNumEntries, NULL)) == 0) 
	{
        OutputDebugString ("No entry in palette to copy!");
        return (HPALETTE) NULL;
    }

    if ((plogPal = (PLOGPALETTE)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT,
            sizeof(DWORD) + sizeof(PALETTEENTRY)*iNumEntries )) == NULL) 
	{
        return (HPALETTE) NULL;
    }

    plogPal->palVersion = 0x300;
    plogPal->palNumEntries = (WORD) iNumEntries;
    pjTmp = (PBYTE) plogPal;
    pjTmp += 8;
    GetPaletteEntries(hPalSrc, 0, iNumEntries, (PPALETTEENTRY)pjTmp);
    hPal = CreatePalette(plogPal);

    GlobalFree(plogPal);

    return hPal;
}
