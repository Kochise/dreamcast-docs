/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    CWND.cpp

Abstract:

    This file contains functions which manage the candidate selection window (CWND).

Environment:

     Runs on Dreamcast under Windows CE.

-------------------------------------------------------------------*/


#include "precomp.hxx"


// global variables
HWND                g_hwndCWND = NULL;                  // handle to CWND's window
HFONT               g_hfontCWND = NULL;
CWNDKEY             g_pskCurrentCWND[TOTAL_CWND_KEYS];  // array of CWND keys
WORD                g_cCurrentCWNDKeys = 0;             // number of keys in CWND
WORD                g_uFocusCWNDKey = 0;                // index of key which has the focus rect
WORD                g_uTopCWNDKey = 0;                  // the top displayed row of the scrolling
WORD                g_xCWNDCursor = 0;                  // x cursor position
WORD                g_yCWNDCursor = 0;                  // y cursor position
BOOL                g_bCWNDactive = FALSE;              // is the CWND active
LPDIRECTDRAWSURFACE g_lpddsCWND = NULL;                 // CWND's offscreen surface


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CWNDCreate

Description:

    This function initializes the contents of the CWND, and calls the
    CWNDCreateWindow and CWNDRender functions.

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL CWNDCreate(void)
{

    WORD i;
    DDSURFACEDESC       ddsd;
    HRESULT             hr;

    // initialize the CWND to contain only space characters, and to have dimensions of
    // one row by one column
    for (i=0; i<TOTAL_CWND_KEYS; i++) {
        g_pskCurrentCWND[i].szKeyString[1] = '\0';
        g_pskCurrentCWND[i].szKeyString[MAX_CHARS_ON_KEY] = '\0';
        g_pskCurrentCWND[i].dxColumns = 1;
        g_pskCurrentCWND[i].dyRows = 1;
        g_pskCurrentCWND[i].xGridLocation = (BYTE)(i % CWND_COLUMNS);
        g_pskCurrentCWND[i].yGridLocation = (BYTE)(i / CWND_COLUMNS);
    }

    // initialize the cursor to the first position in the CWND
    g_xCWNDCursor = 0;
    g_yCWNDCursor = 0;
    g_uFocusCWNDKey =  0;

    // create the CWND window
    if (!CWNDCreateWindow()) {
        return(0);
    }

    // Create offscreen surface.
    ddsd.dwSize = sizeof( ddsd );
    ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT | DDSD_WIDTH;
    ddsd.dwWidth = CWND_WIDTH;
    ddsd.dwHeight = CWND_HEIGHT;       
    ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN;
    hr = g_lpdd->CreateSurface (&ddsd, &g_lpddsCWND, NULL);
    if (hr != DD_OK) {
        OutputDebugString (TEXT("Create offscreen surface failed.\r\n"));
        return FALSE;
    }

    if (g_hfontCWND == NULL) {
        g_hfontCWND = CreateChineseFont(CWND_FONTSIZE);
        if (g_hfontCWND == NULL) {
            g_hfontCWND = g_hfontDefault;
        }
    }

    return(TRUE);


} // CWNDCreate


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CWNDWndProc

Description:

    This is the callback function for messages sent to the CWND.

Return Value:
    0 if message is processed, DefWindowProc's return value otherwise.

-------------------------------------------------------------------*/
LRESULT CALLBACK CWNDWndProc(HWND   hwnd,    // handle to window
                             UINT   uMsg,    // message identifier
                             WPARAM wParam,  // first message parameter
                             LPARAM lParam)  // second message parameter
{
    if (hwnd == g_hwndCWND) {
        switch (uMsg) 
        {
        case WM_KEYDOWN:
            return(0);
            break;
        case WM_CHAR:
            return(0);
            break;
        }
    }
    return (DefWindowProc(hwnd, uMsg, wParam, lParam));
} // CWNDWindowProc


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CWNDUpdateFocusRect

Description:

    This function redraws the key that last had a focus rectangle and the
    key which now has a focus rectangle to reflect any change in the location
    of the focus rectangle.  The focus rectangle is the highlighted square 
    surrounding the key which is the current location of the CWND joystick.

Return Value:

    none

-------------------------------------------------------------------*/
void CWNDUpdateFocusRect(WORD iKeyTop,
                         WORD iCWNDNewFocus)
{
    if (iCWNDNewFocus != 0xffff && iCWNDNewFocus != g_uFocusCWNDKey) {
        if (g_uFocusCWNDKey != 0xffff) {
            // render the key which used to have a focus rectangle
            CWNDRenderKey(g_lpddsCWND, g_uFocusCWNDKey, FALSE, iKeyTop);
        }

        // put the new focus rectangle location into the global variable which
        // stores the focus rect's location
        g_uFocusCWNDKey = iCWNDNewFocus;

        // render the key which now has a focus rectangle
        CWNDRenderKey(g_lpddsCWND, g_uFocusCWNDKey, TRUE, iKeyTop);
    }
} // CWNDUpdateFocusRect


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CWNDFindKeyUnderCursor

Description:

    This function searches the CWND array to find which index of this array
    corresponds to the current location of the x and y CWND cursors.

Return Value:

    Index of current key if one is found, 0xffff otherwise.

-------------------------------------------------------------------*/
WORD CWNDFindKeyUnderCursor(void)
{

    WORD            iKeyCurrent;
    CWNDKEY*        psk;

    // loop through the CWND
    for (iKeyCurrent = 0 ; iKeyCurrent < g_cCurrentCWNDKeys ; iKeyCurrent++) {
        psk = &g_pskCurrentCWND[iKeyCurrent];
        // find out if x and y cursors fall in the boundaries of this key
        if ((psk->xGridLocation <= g_xCWNDCursor) &&
            (g_xCWNDCursor < (psk->xGridLocation + psk->dxColumns)) &&
            (psk->yGridLocation <= g_yCWNDCursor) &&
            (g_yCWNDCursor < (psk->yGridLocation + psk->dyRows))) {
            return iKeyCurrent;
        }
    }

    return 0xffff;
} // CWNDFindKeyUnderCursor


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CWNDCreateWindow

Description:

    This function registers a window class, and creates a window for
    the CWND.

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL CWNDCreateWindow(void)
{
    WNDCLASS            wc;

    // Set up and register window class.
    wc.style            = NULL;
    wc.lpfnWndProc      = CWNDWndProc;
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hInstance        = g_hInstance;
    wc.hIcon            = NULL;
    wc.hCursor          = NULL;
    wc.hbrBackground    = NULL;
    wc.lpszMenuName     = NULL;
    wc.lpszClassName    = TEXT("CWND");
    
    if (!RegisterClass(&wc)) {
        OutputDebugString(TEXT("RegisterClass failed.\r\n"));
        return FALSE;
    }
    
    // Create the CWND window.
    g_hwndCWND = CreateWindowEx(0,
                                TEXT("CWND"),
                                TEXT("CWND"),
                                WS_VISIBLE,
                                0,
                                0,
                                GetSystemMetrics(SM_CXSCREEN),
                                GetSystemMetrics(SM_CYSCREEN),
                                NULL,
                                NULL,
                                g_hInstance,
                                NULL);

    if (!g_hwndCWND) {
        OutputDebugString(TEXT("CWNDCreateWindow failed.\r\n"));
        return FALSE;
    }

    // Success!
    return TRUE;

} // CWNDCreateWindow


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CWNDDestroy

Description:

    This function cleans up the CWND.
Return Value:

    none

-------------------------------------------------------------------*/
void CWNDDestroy(void)
{
    // destroy the kanji window
    if (g_hwndCWND) 
        DestroyWindow(g_hwndCWND);

    // release the offscreen surface
    if (g_lpddsCWND) 
        g_lpddsCWND->Release();

    if (g_hfontCWND && g_hfontCWND != g_hfontDefault) {
        DeleteObject(g_hfontCWND);
        g_hfontCWND = NULL;
    }

} // CWNDDestroy


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CWNDGetData

Description:

    Get the candidate data of CWND.

Return Value:

    none

-------------------------------------------------------------------*/
BOOL CWNDGetData(void)
{
    HWND            hwndFocus = GetFocus();
    BOOL            fRet = FALSE;
    DWORD           i;

    HIMC            hIMC;
    LPINPUTCONTEXT  lpIMC;
    LPCANDIDATEINFO lpCandInfo;
    LPCANDIDATELIST lpCandList;

    
    hIMC = (HIMC)ImmGetContext(hwndFocus);
    if (!hIMC) {
        return fRet;
    }

    lpIMC = (LPINPUTCONTEXT)ImmLockIMC(hIMC);
    if (!lpIMC) {
        goto GetDataRelectIMC;
    }

    if (!lpIMC->hCandInfo) {
        goto GetDataUnlockIMC;
    }

    lpCandInfo = (LPCANDIDATEINFO)ImmLockIMCC(lpIMC->hCandInfo);
    if (!lpCandInfo) {
        goto GetDataUnlockIMC;
    }

    lpCandList = (LPCANDIDATELIST)((LPBYTE)lpCandInfo + lpCandInfo->dwOffset[0]);

    g_cCurrentCWNDKeys = (WORD)lpCandList->dwCount;
    g_uFocusCWNDKey = (WORD)lpCandList->dwSelection;
    g_uTopCWNDKey = (WORD)lpCandList->dwPageStart;

    g_xCWNDCursor = g_pskCurrentCWND[g_uFocusCWNDKey].xGridLocation;
    g_yCWNDCursor = g_pskCurrentCWND[g_uFocusCWNDKey].yGridLocation;

    for (i=0; i < lpCandList->dwCount; i++) {
        g_pskCurrentCWND[i].szKeyString[0] =
            *(LPTSTR)((LPBYTE)lpCandList + lpCandList->dwOffset[i]);
    }

    fRet = TRUE;

GetDataUnlockIMC:
    ImmUnlockIMC(hIMC);

GetDataRelectIMC:
    ImmReleaseContext(hwndFocus, hIMC);

    return fRet;
} // CWNDGetData


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CWNDGetChange

Description:

    Get the information of CWND.

Return Value:

    none

-------------------------------------------------------------------*/
void CWNDGetChange(void)
{
    HWND            hwndFocus = GetFocus();
    HIMC            hIMC;
    LPINPUTCONTEXT  lpIMC;
    LPCANDIDATEINFO lpCandInfo;
    LPCANDIDATELIST lpCandList;

    hIMC = ImmGetContext(hwndFocus);
    if (!hIMC) {
        return;
    }

    lpIMC = (LPINPUTCONTEXT)ImmLockIMC(hIMC);
    if (!lpIMC) {
        goto GetInfoReleaseIMC;
    }

    if (!lpIMC->hCandInfo) {
        goto GetInfoUnlockIMC;
    }

    lpCandInfo = (LPCANDIDATEINFO)ImmLockIMCC(lpIMC->hCandInfo);
    if (!lpCandInfo) {
        goto GetInfoUnlockIMC;
    }

    lpCandList = (LPCANDIDATELIST)((LPBYTE)lpCandInfo + lpCandInfo->dwOffset[0]);

    g_uFocusCWNDKey = (WORD)lpCandList->dwSelection;
    g_uTopCWNDKey = (WORD)lpCandList->dwPageStart;

    g_xCWNDCursor = g_pskCurrentCWND[g_uFocusCWNDKey].xGridLocation;
    g_yCWNDCursor = g_pskCurrentCWND[g_uFocusCWNDKey].yGridLocation;


GetInfoUnlockIMC:
    ImmUnlockIMC(hIMC);

GetInfoReleaseIMC:
    ImmReleaseContext(hwndFocus, hIMC);

    CWNDRender(g_uTopCWNDKey);

    return;
} // CWNDChange


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CWNDSetChange

Description:

    Get the information of CWND.

Return Value:

    none

-------------------------------------------------------------------*/
void CWNDSetChange(void)
{
    HWND            hwndFocus = GetFocus();
    HIMC            hIMC;
    LPINPUTCONTEXT  lpIMC;
    LPCANDIDATEINFO lpCandInfo;
    LPCANDIDATELIST lpCandList;

    hIMC = ImmGetContext(hwndFocus);
    if (!hIMC) {
        return;
    }

    lpIMC = (LPINPUTCONTEXT)ImmLockIMC(hIMC);
    if (!lpIMC) {
        goto GetInfoReleaseIMC;
    }

    if (!lpIMC->hCandInfo) {
        goto GetInfoUnlockIMC;
    }

    lpCandInfo = (LPCANDIDATEINFO)ImmLockIMCC(lpIMC->hCandInfo);
    if (!lpCandInfo) {
        goto GetInfoUnlockIMC;
    }

    lpCandList = (LPCANDIDATELIST)((LPBYTE)lpCandInfo + lpCandInfo->dwOffset[0]);

    lpCandList->dwSelection = (DWORD)g_uFocusCWNDKey;
    lpCandList->dwPageStart = (DWORD)g_uTopCWNDKey;

GetInfoUnlockIMC:
    ImmUnlockIMC(hIMC);

GetInfoReleaseIMC:
    ImmReleaseContext(hwndFocus, hIMC);

    CWNDRender(g_uTopCWNDKey);

    return;
} // CWNDChange


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CWNDUpdate

Description:

    This function re-renders the CWND.

Return Value:

    none

-------------------------------------------------------------------*/
void CWNDUpdate(void)
{
    static BOOL bLastActive = g_bCWNDactive;
    static BOOL bLastHWKBDPresent = g_fHardwareKeyboardPresent;
    
    // if the KWND shifted to active or to not active, then reset the iKeyTop to 0
    if (g_bCWNDactive != bLastActive) {
        g_uTopCWNDKey = 0;
        if (bLastActive == FALSE) {
            CWNDRender(g_uTopCWNDKey);
            bLastHWKBDPresent = g_fHardwareKeyboardPresent;
        }
        bLastActive = g_bCWNDactive; 
    }

    if (g_fHardwareKeyboardPresent != bLastHWKBDPresent){
        if (g_bCWNDactive) {
            if (g_fHardwareKeyboardPresent) {
                CWNDSetChange();
            } else {
                CWNDGetChange();
            }
        }
        bLastHWKBDPresent = g_fHardwareKeyboardPresent;
    }

    if (g_fHardwareKeyboardPresent)
        return;

    if (g_bCWNDactive) {
        CWNDReadDirectInputDevices(&g_uTopCWNDKey);
    }

} // CWNDUpdate


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CWNDBlt

Description:

    This function renders the CWND.

Return Value:

    none

-------------------------------------------------------------------*/
void CWNDBlt(LPDIRECTDRAWSURFACE lpDDSBack)
{
    if (!g_bCWNDactive) {
        return;
    }

    WORD wCWNDXCoord;

    RECT rc;
    rc.left = 0;
    rc.top = 0;
    rc.right = CWND_WIDTH;
    rc.bottom = CWND_HEIGHT;

    if ((g_wRWNDXCoord + RWND_WIDTH + CWND_GAP + CWND_WIDTH) > EDITBOX_WIDTH) {
        wCWNDXCoord = g_wRWNDXCoord - CWND_WIDTH - CWND_GAP;
    } else {
        wCWNDXCoord = g_wRWNDXCoord + RWND_WIDTH + CWND_GAP;
    }

    if (lpDDSBack) {
        lpDDSBack->BltFast(wCWNDXCoord, CWND_TOPEDGE, g_lpddsCWND, &rc,
                           DDBLTFAST_NOCOLORKEY|DDBLTFAST_WAIT);
    }
} // CWNDBlt

