/*
 * CLIP.C
 *
 * Functions to interact with the clipboard.
 *
 * Copyright(c) Microsoft Corp. 1992-1994 All Rights Reserved
 * Win32 version, January 1994
 */

#include <windows.h>
#include <ole.h>
#include "cosmo.h"
#include "oleglobl.h"



/*
 * FEditCut
 *
 * Purpose:
 *  Places a private format, a metafile, and a bitmap of the display
 *  on the clipboard and clears the editor window with the equivalent
 *  to complete the "Cut" operation.  This operation also sets the
 *  dirty flag through a call to FDirtySet.
 *
 * Parameters:
 *  pGlob           LPGLOBALS to the global variable block.
 *
 * Return Value:
 *  BOOL            TRUE if successful, FALSE otherwise.
 *
 */

BOOL WINAPI FEditCut(LPGLOBALS pGlob)
    {
    //Copy editor contents to the clipboard.
    if (!FEditCopy(pGlob, TRUE))
        return FALSE;

    //Clear out the editor contents.
    SendMessage(pGlob->hWndPolyline, PLM_POLYLINENEW, 0, 0L);
    FDirtySet(TRUE);
    return TRUE;
    }



/*
 * FEditCopy
 *
 * Purpose:
 *  Places a private format, a metafile, and a bitmap of the display
 *  on the clipboard.
 *
 *
 * Parameters:
 *  pGlob           LPGLOBALS to the global variable block.
 *  fCut            BOOL indicating if this copy is part of a Cut.
 *
 * Return Value:
 *  BOOL            TRUE if anything was successfully placed on the
 *                  clipboard, FALSE otherwise.
 *
 */

BOOL WINAPI FEditCopy(LPGLOBALS pGlob, BOOL fCut)
    {
    BOOL            fRet=TRUE;
    HGLOBAL         hMem;

    //Attempt to gain clipboard ownership.
    if (!OpenClipboard(pGlob->hWnd))
        return FALSE;

    //Clean out whatever junk is in the clipboard.
    EmptyClipboard();

    //Copy private data first.
    hMem=HGetPolyline(pGlob->hWndPolyline);

    //Copy private data (not "Native") we used prior to OLE.
    if (NULL!=hMem)
        SetClipboardData(pGlob->cfCosmo, hMem);
    else
        fRet &=FALSE;

#ifdef MAKEOLESERVER

    //Copy Native data.
    fRet &=FOLECopyNative(pOLE);

    //Copy "OwnerLink" data.
    fRet &=FOLECopyLink(pOLE, TRUE, pGlob->szFile);

#endif //MAKEOLESERVER

    //Send the METAFILEPICT to the clipboard if we have one.
    hMem=HGetMetafilePict(pGlob->hWndPolyline);

    if (NULL!=hMem)
        SetClipboardData(CF_METAFILEPICT, hMem);
    else
        fRet &=FALSE;

    //Send the bitmap to the clipboard if we can get one.
    hMem=HGetBitmap(pGlob->hWndPolyline);

    if (NULL!=hMem)
        SetClipboardData(CF_BITMAP, hMem);
    else
        fRet &=FALSE;

#ifdef MAKEOLESERVER

    //Copy "ObjectLink" data if we have a filename AND are not cutting.
    if (pGlob->fOpenFile && 0!=pGlob->szFile[0] && !fCut)
        {
        fRet &=FOLECopyLink(pOLE, FALSE, pGlob->szFile);
        }

#endif //MAKEOLESERVER

    //Free clipboard ownership.
    CloseClipboard();
    return fRet;
    }






/*
 * FEditPaste
 *
 * Purpose:
 *  Retrieves the private data format from the clipboard and sets it
 *  to the current figure in the editor window.
 *
 *  Note that if this function is called, then the clipboard format
 *  is available because the Paste menu item is only enabled if the
 *  format is present.
 *
 * Parameters:
 *  pGlob           LPGLOBALS to the global variable block.
 *
 * Return Value:
 *  BOOL            TRUE if successful, FALSE otherwise.
 *
 */

BOOL WINAPI FEditPaste(LPGLOBALS pGlob)
    {
    HGLOBAL         hMem;
    LPPOLYLINE      lppl;

    //Attempt to gain clipboard ownership.
    if (!OpenClipboard(pGlob->hWnd))
        return FALSE;

    hMem=GetClipboardData(pGlob->cfCosmo);

    if (NULL==hMem)
        {
        CloseClipboard();
        return FALSE;
        }

    lppl=(LPPOLYLINE)GlobalLock(hMem);

    //TRUE in wParam to cause PLN_SIZECHANGE notification
    SendMessage(pGlob->hWndPolyline, PLM_POLYLINESET, TRUE, (LONG)lppl);
    GlobalUnlock(hMem);

    FDirtySet(TRUE);
    CloseClipboard();
    return TRUE;
    }



/*
 * HGetPolyline
 *
 * Purpose:
 *  Allocates global memory and copies the current Polyline into it.
 *
 * Parameters:
 *  hWnd            HWND of the PolyLine window whose data we want.
 *
 * Return Value:
 *  HGLOBAL         Global handle if successful, NULL otherwise.
 */

HGLOBAL WINAPI HGetPolyline(HWND hWnd)
    {
    LPPOLYLINE  lppl;
    HGLOBAL     hMem;

    //Allocate a copy of the POLYLINE structure and set it as private data.
    hMem=GlobalAlloc(GMEM_DDESHARE | GMEM_MOVEABLE, CBPOLYLINE);

    if (NULL!=hMem)
        {
        lppl=(LPPOLYLINE)GlobalLock(hMem);
        SendMessage(hWnd, PLM_POLYLINEGET, 0, (LONG)lppl);
        GlobalUnlock(hMem);
        }

    return hMem;
    }



/*
 * HGetMetafilePict
 *
 * Purpose:
 *  Retrieves a metafile for the current polyline image.
 *
 * Parameters:
 *  hWnd            HWND of the PolyLine window whose image we want.
 *
 * Return Value:
 *  HGLOBAL         Global handle to a METAFILEPICT structure if
 *                  successful, NULL otherwise.
 */

HGLOBAL WINAPI HGetMetafilePict(HWND hWnd)
    {
    HGLOBAL     hMem;
    DWORD       dw;

    //Retrieve a METAFILEPICT structure for this object.
    dw=SendMessage(hWnd, PLM_METAFILEPICTGET, 0, 0L);
    hMem=(HGLOBAL)(UINT)dw;

    return hMem;
    }




/*
 * HGetBitmap
 *
 * Purpose:
 *  Retrieves a device-dependent bitmap for the current polyline image.
 *
 * Parameters:
 *  hWnd            HWND of the PolyLine window whose image we want.
 *
 * Return Value:
 *  HGLOBAL         Bitmap handle if successful, NULL otherwise.
 */

HGLOBAL WINAPI HGetBitmap(HWND hWnd)
    {
    HGLOBAL     hMem;
    DWORD       dw;

    dw=SendMessage(hWnd, PLM_BITMAPGET, 0, 0L);
    hMem=(HGLOBAL)(UINT)dw;

    return hMem;
    }
