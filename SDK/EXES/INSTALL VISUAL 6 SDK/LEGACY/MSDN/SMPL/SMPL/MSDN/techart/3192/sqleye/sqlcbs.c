//****************************** Module Header *******************************
//
// Function : ClientWndProc
//
// Description: This module defines all the child windows procs
//
// Author PeterWil 1994, Microsoft Ltd.
//*****************************************************************************
#define     DBNTWIN32

// Standard compiler and SQL header files
#include    <stdlib.h>
#include    <stdio.h>
#include    <string.h>
#include    <windows.h>
#include    <sqlfront.h>
#include    <sqldb.h>
#include    <srv.h>

// Application specific header files
#include    "sqleye.h"
#include    "sqlcbs.h"
#include    "rowstuff.h"

// Some auto bits
BOOL    bAutoScroll = TRUE;
BOOL    bAutoTile   = TRUE;
BOOL    bStartMin   = TRUE;
BOOL    bGhosts     = FALSE;

// These are created in SQLEYE as part of the initialisation
extern HICON  hiAwake, hiAsleep, hiIn, hiOut, hiWaiting, hiRPC, hiGhost, hiStats, hiConnect;
extern HANDLE ghwndMain;
extern HWND   hwndClient;
extern HANDLE ghModule;

extern LOG    Log;

// define the font to be used in the display
#define THEFONT ANSI_FIXED_FONT

// Used to make sure we don't go on until after WM_CREATE completes
// (need to protect hClientDataInit, szAppName)
HANDLE    InitMDI_SEM; 
HANDLE    hClientDataInit;
char      *szAppName;

// Prototype local functions
PCLIENTINFO FindClientInfo(HWND hwnd);
void ReleaseClientInfo(HWND hwnd);
void FreeClientInfo(HWND hwnd);

#pragma check_stack( off )  // turn off stack checking

//****************************** Function Header ******************************
//
// Function : ClientWndProc
//
// Description: Handles MDI clients
//
//*****************************************************************************
int WINAPI ClientWndProc(HWND hwnd, UINT message,DWORD wParam,LONG lParam)

{
    int         nPaintBeg,nPaintEnd;
    PCLIENTINFO pInfo;
    PAINTSTRUCT ps;
    HDC         hdc;
    TEXTMETRIC  tm;
    HFONT       hfont;
    int         RowCounter;
    int         Y_co_ordinate;
    char        *psz, sz[] = " ";
    int         nVScrollInc = 0;

    switch (message)
    {
        case WM_COMMAND:
        switch (LOWORD(wParam))
            {

            // Use the ACTIVE Icon
            case IDM_ACTIVE_ICON:
            if ((pInfo = FindClientInfo(hwnd)) != NULL)
            {
                pInfo->iIconType = IDM_ACTIVE_ICON;
                if (IsIconic(hwnd)) 
                    InvalidateRect(hwnd, NULL, TRUE);
                ReleaseClientInfo(hwnd);
            }
            return 0L;

            // Use the INACTIVE Icon
            case IDM_INACTIVE_ICON:
            if ((pInfo = FindClientInfo(hwnd)) != NULL)
            {
                pInfo->iIconType = IDM_INACTIVE_ICON;
                if (IsIconic(hwnd)) 
                    InvalidateRect(hwnd, NULL, TRUE);
                ReleaseClientInfo(hwnd);
            }
            return 0L;

            // Use the IN Icon
            case IDM_IN_ICON:
            if ((pInfo = FindClientInfo(hwnd)) != NULL)
            {
                pInfo->iIconType = IDM_IN_ICON;
                if (IsIconic(hwnd)) 
                    InvalidateRect(hwnd, NULL, TRUE);
                ReleaseClientInfo(hwnd);
            }
            return 0L;

            // Use the OUT Icon
            case IDM_OUT_ICON:
            if ((pInfo = FindClientInfo(hwnd)) != NULL)
            {
                pInfo->iIconType = IDM_OUT_ICON;
                if (IsIconic(hwnd)) 
                    InvalidateRect(hwnd, NULL, TRUE);
                ReleaseClientInfo(hwnd);
            }
            return 0L;

            // Use the RPC Icon
            case IDM_RPC_ICON:
            if ((pInfo = FindClientInfo(hwnd)) != NULL)
            {
                pInfo->iIconType = IDM_RPC_ICON;
                if (IsIconic(hwnd)) 
                    InvalidateRect(hwnd, NULL, TRUE);
                ReleaseClientInfo(hwnd);
            }
            return 0L;

            default:
            return DefFrameProc(hwnd,  hwndClient, message, wParam, lParam);
            }

         // Initialize the data structures needed 
         case WM_CREATE:
             // add the data to the window
            SetWindowLong(hwnd, GWL_USERDATA, (LONG)hClientDataInit);

            if ((pInfo = FindClientInfo(hwnd)) != NULL)
            {
                // Setup the application specific icons for the particular child
                // (don't worry if Extract Icon fails it just sets it to Null, the default icon)
                // Have a look in the map file
                {
                    FILE *fMapFile;
                    CHAR szAppNameMap[MAXAPPNAME+1],szFileName[MAXFILENAME+1];
                    unsigned int nIcon=0;
                    pInfo->hAppIcon = NULL;
                    // Open the file read only
                    if (fMapFile = fopen("sqleye.map","r"))
                    {
                        // read the pairs
                        while ( (fscanf(fMapFile,"%[^\t]\t%[^\n]\n",szAppNameMap,szFileName ) == 2) &&
                            !pInfo->hAppIcon )
                            // if it matches load the icon from the file
                            if (!strcmp(szAppName,szAppNameMap))
                                pInfo->hAppIcon = ExtractIcon(ghModule,szFileName,0);
                    // close the file
                    fclose(fMapFile);
                    } // if the file doesn't exist then just ignore it
                }

                hdc = GetDC(hwnd);
                // get the right font
                hfont = GetStockObject(THEFONT);
                SelectObject(hdc, hfont);
                // find out about the font
                GetTextMetrics(hdc, (LPTEXTMETRIC)&tm);
                pInfo->cyChar = tm.tmHeight + tm.tmExternalLeading;
                pInfo->cxChar = tm.tmAveCharWidth;
                pInfo->cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * pInfo->cxChar / 2;
                // Set up some of the data structure
                pInfo->hwnd        = hwnd;
                pInfo->iCurrentRow = 0;
                pInfo->iIconType   = IDM_CONNECT_ICON;
                // To allow for new rows added since the last 
                // WM_PAINT a fraction of which appear on the screen 
                // and need to be drawn before we scroll
                pInfo->ExtraRect.top    = pInfo->cyClient - (pInfo->cyChar);
                pInfo->ExtraRect.bottom = pInfo->cyClient;
                pInfo->ExtraRect.left   = 0;
                pInfo->ExtraRect.right  = pInfo->cxClient;

                // Set the clear buffer flag to false
                pInfo->bClearBuf = FALSE;

                DeleteObject(hfont);
                ReleaseDC(hwnd,hdc);
                ReleaseClientInfo(hwnd);
            }
            // Other threads can now use hClientData 
            ReleaseSemaphore(InitMDI_SEM, 1, NULL);
            return 0L;
        
        case WM_SIZE:
            if ((pInfo = FindClientInfo(hwnd)) != NULL)
            {
                // make a note of the display size
                pInfo->cyClient = HIWORD(lParam);
                pInfo->cxClient = LOWORD(lParam);

                // make a note of how many rows are displayed on the screen
                pInfo->iDisplayedVRows = pInfo->cyClient  / pInfo->cyChar;
                pInfo->iDisplayedHRows = pInfo->cxClient / pInfo->cxCaps;

                // work out the maximum scroll positions
                pInfo->iMaxVScrollPos = max(0,pInfo->iCurrentRow-pInfo->iDisplayedVRows);
                pInfo->iMaxHScrollPos = max(0,pInfo->iMaxHorRow -pInfo->iDisplayedHRows);

                // set up the vertical scroll bar sizes
                SetScrollRange(hwnd, SB_VERT, 0, pInfo->iMaxVScrollPos, FALSE);
                if (pInfo->iVScrollPos > pInfo->iMaxVScrollPos)
                    pInfo->iVScrollPos = pInfo->iMaxVScrollPos;
                SetScrollPos  (hwnd, SB_VERT, pInfo->iVScrollPos, TRUE);

                // set up the horizontal scroll bar sizes
                SetScrollRange(hwnd, SB_HORZ, 0, pInfo->iMaxHScrollPos, FALSE);
                if (pInfo->iHScrollPos > pInfo->iMaxHScrollPos)
                    pInfo->iHScrollPos = pInfo->iMaxHScrollPos;
                SetScrollPos  (hwnd, SB_HORZ, pInfo->iHScrollPos, TRUE);

                if (bAutoTile) PostMessage(ghwndMain,WM_COMMAND,IDM_TILE,0L);

                // To allow for new rows added since the last 
                // WM_PAINT a fraction of which appear on the screen 
                // and need to be drawn before we scroll
                pInfo->ExtraRect.top    = pInfo->cyClient - (pInfo->cyChar);
                pInfo->ExtraRect.bottom = pInfo->cyClient;
                pInfo->ExtraRect.left   = 0;
                pInfo->ExtraRect.right  = pInfo->cxClient;
                ReleaseClientInfo(hwnd);
            }
            return DefMDIChildProc(hwnd, message, wParam, lParam);

        case WM_VSCROLL:
            if ((pInfo = FindClientInfo(hwnd)) != NULL)
            {
                switch(LOWORD(wParam))
                {
                    case SB_TOP:
                        nVScrollInc = -pInfo->iVScrollPos;
                        break;

                    case SB_BOTTOM:
                        nVScrollInc = pInfo->iMaxVScrollPos - pInfo->iVScrollPos;
                        break;

                    case SB_LINEUP:
                        nVScrollInc = -1;
                        break;

                    case SB_LINEDOWN:
                        nVScrollInc = 1;
                        break;

                    case SB_PAGEUP:
                        nVScrollInc = min(-1,-(int)(pInfo->cyClient / pInfo->cyChar));
                        break;

                    case SB_PAGEDOWN:
                        nVScrollInc = max(1,pInfo->cyClient / pInfo->cyChar);
                        break;

                    case SB_THUMBTRACK :
                        nVScrollInc = HIWORD(wParam) - pInfo->iVScrollPos;
                        break;

                    default:
                        nVScrollInc = 0;
                        break;
                }

                if (nVScrollInc)
                  if (nVScrollInc = max(-pInfo->iVScrollPos, 
                    min(nVScrollInc, pInfo->iMaxVScrollPos - pInfo->iVScrollPos)))
                    {
                        if (!IsIconic(hwnd))
                        {
                            // To allow for new rows added since the last 
                            // WM_PAINT a fraction of which appear on the screen 
                            // and need to be drawn before we scroll to avoid gaps
                            InvalidateRect(hwnd,&(pInfo->ExtraRect),FALSE);
                            UpdateWindow(hwnd);

                            ScrollWindow(hwnd,0,-pInfo->cyChar*nVScrollInc,NULL,NULL);
                            pInfo->iVScrollPos += nVScrollInc;
                            UpdateWindow(hwnd);
                            SetScrollPos(hwnd, SB_VERT, pInfo->iVScrollPos, TRUE);
                            
                        } else {
                            pInfo->iVScrollPos += nVScrollInc;
                            SetScrollPos(hwnd, SB_VERT, pInfo->iVScrollPos, TRUE);
                        }
                    }
                ReleaseClientInfo(hwnd);
            }
            return 0L;

        case WM_HSCROLL:
            if ((pInfo = FindClientInfo(hwnd)) != NULL)
            {
                switch(LOWORD(wParam))
                {
                    case SB_LINEUP:
                        pInfo->iHScrollPos -= 1;
                        break;

                    case SB_LINEDOWN:
                        pInfo->iHScrollPos += 1;
                        break;

                    case SB_PAGEUP:
                        pInfo->iHScrollPos -= pInfo->cyClient / pInfo->cyChar;
                        break;

                    case SB_PAGEDOWN:
                        pInfo->iHScrollPos += pInfo->cyClient / pInfo->cyChar;
                        break;

                    case SB_THUMBTRACK :
                        pInfo->iHScrollPos = HIWORD(wParam);
                        break;

                    default:
                        break;
                }

                pInfo->iHScrollPos = max(0, min(pInfo->iHScrollPos, pInfo->iMaxHorRow));

                if (pInfo->iHScrollPos != GetScrollPos(hwnd, SB_HORZ))
                {
                    SetScrollRange(hwnd, SB_HORZ, 0, pInfo->iMaxHorRow, FALSE);
                    SetScrollPos(hwnd, SB_HORZ, pInfo->iHScrollPos, TRUE);
                    InvalidateRect(hwnd, NULL, TRUE);
                }
                ReleaseClientInfo(hwnd);
            }
            return 0L;

        case WM_ERASEBKGND: 
            // Set the right background color when minimised
            if (IsIconic(hwnd))
            {
                HBRUSH hbOldBrush,hbTempBrush;
                LRESULT RetCode;
                hbTempBrush = CreateSolidBrush(GetSysColor(COLOR_APPWORKSPACE));
                hbOldBrush  = (HBRUSH)SetClassLong(hwnd,GCL_HBRBACKGROUND,(long)hbTempBrush);
                RetCode     = DefFrameProc(hwnd,hwndClient,message,wParam,lParam);
                SetClassLong(hwnd,GCL_HBRBACKGROUND,(long)hbOldBrush);
                DeleteObject(hbTempBrush);
                return RetCode;
            }
            else
                return  DefFrameProc(hwnd,  hwndClient, message, wParam, lParam);

        case WM_MOVE:
                if (bAutoTile) PostMessage(ghwndMain,WM_COMMAND,IDM_TILE,0L);
                return  DefFrameProc(hwnd,  hwndClient, message, wParam, lParam);
                    
        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);
            if ((pInfo = FindClientInfo(hwnd)) != NULL)
            { 
                hfont = GetStockObject(THEFONT);
                SelectObject(hdc, hfont);
                SetBkColor(hdc, GetSysColor(COLOR_WINDOW));

                if (IsIconic(hwnd))
                {
                    // It's minimised

                    // Erase the background
                    DefWindowProc(hwnd,WM_ICONERASEBKGND,(WORD)ps.hdc,0);

                    // Draw the background icon
                    if (pInfo->hAppIcon)
                        // Draw the Icon specific to the application
                        DrawIcon(hdc,0,0,pInfo->hAppIcon);
                    else
                        // Draw the default face Icon
                        DrawIcon(hdc,0,0,hiAsleep);

                    // draw an overlay icon if one required
                    switch (pInfo->iIconType)
                    {
                        case IDM_ACTIVE_ICON:
                            if (pInfo->hAppIcon)
                                // If the application has it's own Icon display the hour glass
                                DrawIcon(hdc,0,0,hiWaiting);
                            else
                                // If using the default face Icon the open the eyes
                                DrawIcon(hdc,0,0,hiAwake);
                            break;

                        // Overlay the Connect diagram
                        case IDM_CONNECT_ICON:
                            if (!pInfo->hAppIcon) DrawIcon(hdc,0,0,hiAwake);
                            DrawIcon(hdc,0,0,hiConnect);
                            break;

                        // Overlay the IN arrow
                        case IDM_IN_ICON:
                            if (!pInfo->hAppIcon) DrawIcon(hdc,0,0,hiAwake);
                            DrawIcon(hdc,0,0,hiIn);
                            break;

                        // Overlay the OUT arrow
                        case IDM_OUT_ICON:
                            if (!pInfo->hAppIcon) DrawIcon(hdc,0,0,hiAwake);
                            DrawIcon(hdc,0,0,hiOut);
                            break;

                        // Overlay the RPC diagram
                        case IDM_RPC_ICON:
                            if (!pInfo->hAppIcon) DrawIcon(hdc,0,0,hiAwake);
                            DrawIcon(hdc,0,0,hiRPC);
                            break;

                        // Overlay the GHOST diagram
                        case IDM_GHOST_ICON:
                            DrawIcon(hdc,0,0,hiGhost);
                            break;
                    }
               } else {
                    // If it's not Iconic the we want to draw the data

                    // Work out what area to draw
                    nPaintBeg = max(0,pInfo->iVScrollPos+(ps.rcPaint.top/pInfo->cyChar));

                    // +1 to allow for partial rows
                    nPaintEnd = min(pInfo->iCurrentRow,pInfo->iVScrollPos + 
                                (ps.rcPaint.bottom/pInfo->cyChar)+1);

                    // Set the starting point
                    Y_co_ordinate = (nPaintBeg - pInfo->iVScrollPos)*pInfo->cyChar;
                                    
                    // Draw out the rows
                    for (RowCounter=nPaintBeg; RowCounter<nPaintEnd; RowCounter++)
                    {
                        if (pInfo->pszRow[RowCounter] != NULL)
                        {
                            // Set the right color
                            SetTextColor(hdc, pInfo->color[RowCounter]);

                            // decide if we need to draw it
                            if ((int)strlen(pInfo->pszRow[RowCounter]) < pInfo->iHScrollPos)
                                psz = sz;
                            else
                            {
                                psz = pInfo->pszRow[RowCounter];
                                psz += pInfo->iHScrollPos;
                            }

                            // Draw it out using the tab stuff
                            TabbedTextOut(hdc, 1, Y_co_ordinate, psz, strlen(psz), 0, NULL, 0);
                        } else {
                            // if there is no line then there was a memory error when trying to store it
                            // let the users know that there is a line missing
                            SetTextColor(hdc, colorRed);
                            TabbedTextOut(hdc, 1, Y_co_ordinate, "MISSING ROW", 11, 0, NULL, 0);
                        }
                        // Move where we draw down a line
                        Y_co_ordinate += pInfo->cyChar;
                    }
                }
                ReleaseClientInfo(hwnd); 
                DeleteObject(hfont);
            }
            EndPaint(hwnd, &ps);
            return 0L;

        case WM_CLOSE:
            if ((pInfo = FindClientInfo(hwnd)) != NULL)
            {
                // We can only close the window IFF we have control
                // i.e. the iIconType = IDM_GHOST_ICON
                if (pInfo->iIconType == IDM_GHOST_ICON)
                {
                    // Destroy any Icon we created with ExtractIcon
                    if (pInfo->hAppIcon) 
                        if (!DestroyIcon(pInfo->hAppIcon))
                            ERRBOX("Error Destroying Application Icon");
                    // Clear the memory used by the data
                    ClearBuffers(pInfo);
                    ReleaseClientInfo(hwnd);
                    // Clear the structure that controlled the data
                    FreeClientInfo(hwnd);
                    if (bAutoTile) PostMessage(ghwndMain,WM_COMMAND,IDM_TILE,0L);
                    return  DefMDIChildProc(hwnd, message, wParam, lParam);
                } else {
                    MSGBOX("Cannot delete windows for active connections (Only ghosts)");
                    ReleaseClientInfo(hwnd);
                    return 0;
                }
            } else return 0;

        
        // Let's keep the system menu correct
        case WM_INITMENU:
        {
            HMENU hMenu;

            if (hMenu = GetSystemMenu (hwnd, FALSE))
            {
                if (bAutoTile)
                {
                    EnableMenuItem (hMenu, SC_MOVE,     MF_BYCOMMAND | MF_GRAYED);
                    EnableMenuItem (hMenu, SC_SIZE,     MF_BYCOMMAND | MF_GRAYED);
                    EnableMenuItem (hMenu, SC_MAXIMIZE, MF_BYCOMMAND | MF_GRAYED);
                }
            
                if ((pInfo = FindClientInfo(hwnd)) != NULL)
                {
                    if (pInfo->iIconType != IDM_GHOST_ICON)
                        EnableMenuItem (hMenu, SC_CLOSE, MF_BYCOMMAND | MF_GRAYED);
                    else
                        EnableMenuItem (hMenu, SC_CLOSE, MF_BYCOMMAND | MF_ENABLED);
                    ReleaseClientInfo(hwnd);
                }
            } else ERRBOX("Could not get the handle to the system menu");
        }
        return 0;

    default:
        return DefMDIChildProc(hwnd, message, wParam, lParam);
    }

}

//****************************** Function Header ******************************
//
// Function : CreateMDI
//
// Description: Creates child MDI window
//
//*****************************************************************************
HWND CreateMDI(HANDLE hClient, char *szTitle, char *szApp)
{
    MDICREATESTRUCT mdicreate;
    int iSize,iPos;
    HWND TheHWND;

    if (!hClient) return NULL;

    iPos  = CW_USEDEFAULT;
    iSize = CW_USEDEFAULT;

    // Set up the info we need to create the client window
    mdicreate.szClass = "sqleyeClientClass";
    mdicreate.szTitle = szTitle;
    mdicreate.hOwner  = ghModule;
    mdicreate.x       = iPos;
    mdicreate.y       = iPos;
    mdicreate.cx      = iSize;
    mdicreate.cy      = iSize;

    // if we want to start the child windows minimized then change the style
    if (bStartMin)
        mdicreate.style   = WS_HSCROLL | WS_VSCROLL | WS_MINIMIZE;
    else
        mdicreate.style   = WS_HSCROLL | WS_VSCROLL;
    mdicreate.lParam  = 0L;

    // Don't let anyone else in here
    // START OF CRITICAL SECTION
    // We need to protect hClientInfo + szAppName until after WM_CREATE has finished
    // (WM_CREATE releases this semaphore for us)
    WaitForSingleObject(InitMDI_SEM, (DWORD)SRV_INDEFINITE_WAIT);
    hClientDataInit = hClient;
    szAppName = szApp;

    // Create the Child Window
    TheHWND= (HANDLE) SendMessage(hwndClient,
        WM_MDICREATE,
        0L,
        (LONG)(LPMDICREATESTRUCT)&mdicreate);
    // CRITICAL SECTION ENDS IN WM_CREATE

    // Test if we failed to create it
    if (TheHWND == NULL)
    {
        ERRBOX("Failed in Creating Child Window!");
        return TheHWND;
    }

    return TheHWND;
}

//****************************** Function Header ******************************
//
// Function : FindClientInfo
//
// Description: Finds and locks a client info data structure, given an hwnd
//
//*****************************************************************************
PCLIENTINFO FindClientInfo(HWND hwnd)
{
    PCLIENTINFO pInfo;
    HANDLE hInfo;

    // find handle and lock it
    if ( (hInfo = (HANDLE) GetWindowLong(hwnd, (int)GWL_USERDATA)) == NULL)
    {
        MessageBox(ghwndMain, "Failed to get handle", "Error", MB_OK);
            return NULL;
    } else {
        if ( (pInfo = LocalLock(hInfo))==NULL)
        {
            MessageBox(ghwndMain, "Failed in LocalLock!", "Error", MB_OK);
                return NULL;
        }
    }

    return pInfo;
}

//****************************** Function Header ******************************
//
// Function : ReleaseClientInfo
//
// Description: Finds and releases a client info data structure, given an hwnd
//
//*****************************************************************************
void ReleaseClientInfo(HWND hwnd)
{
    HANDLE hInfo;

    // find handle and unlock it
    if ( (hInfo = (HANDLE) GetWindowLong(hwnd, (int)GWL_USERDATA)) == NULL)
    {
        MessageBox(ghwndMain, "Failed to get handle", "Error", MB_OK);
            return;
    } else 
        LocalUnlock(hInfo);
}

//****************************** Function Header ******************************
//
// Function : FreeClientInfo
//
// Description: Finds and frees a client info data structure, given an hwnd
//
//*****************************************************************************
void FreeClientInfo(HWND hwnd)
{
    HANDLE hInfo;

    // find handle and free the memory
    if ( (hInfo = (HANDLE) GetWindowLong(hwnd, (int)GWL_USERDATA)) == NULL)
    {
        MessageBox(ghwndMain, "Failed to get handle", "Error", MB_OK);
            return;
    } else 
        LocalFree(hInfo);
}

//****************************** Function Header ******************************
//
// Function : ChangeIcon
//
// Description: Changes an MDI childs Icon type, returns the old icon type
//
//*****************************************************************************
int ChangeIcon(HANDLE hInfo, int iNewIcon)
{
    PCLIENTINFO pInfo;
    int         iOldIcon;

    if (!hInfo)
        {
        ERRBOX("Invalid handle when changing icon type");
        return IDM_INACTIVE_ICON;
        }

    if ( (pInfo = LocalLock(hInfo)) == NULL)
        {
        ERRBOX("Error locking handle when changing icon type");
        return IDM_INACTIVE_ICON;
        }

    iOldIcon = pInfo->iIconType;
    SendMessage(pInfo->hwnd,WM_COMMAND,iNewIcon,0L);
    LocalUnlock(hInfo);

    return iOldIcon;
}

/**************************************************************************\
* EnumCloseGhosts
*
* Call back function to close Ghost windows
*
\**************************************************************************/
BOOL CALLBACK EnumCloseGhosts(HWND hwnd, LPARAM lParam)
{
    PCLIENTINFO pInfo;
    BOOL    bCloseIt;
    
    // check if this is an icon title
    if (GetWindow (hwnd, GW_OWNER)) return TRUE;

    if ((pInfo = FindClientInfo(hwnd)) != NULL)
    {
        // We can only close the window IFF we're a ghost
        // i.e. the iIconType = IDM_GHOST_ICON
        bCloseIt = (pInfo->iIconType == IDM_GHOST_ICON);
        ReleaseClientInfo(hwnd);

        if (bCloseIt) PostMessage(hwnd,WM_CLOSE,0,0);
    }
    return TRUE;
}

/**************************************************************************\
* EnumClearBuffers
*
* Call back function to clear the buffers
*
\**************************************************************************/
BOOL CALLBACK EnumClearBuffers(HWND hwnd, LPARAM lParam)
{
    PCLIENTINFO pInfo;
    
    // check if this is an icon title
    if (GetWindow (hwnd, GW_OWNER)) return TRUE;

    if ((pInfo = FindClientInfo(hwnd)) != NULL)
    {
        pInfo->bClearBuf = TRUE;
        ReleaseClientInfo(hwnd);
    }
    return TRUE;
}

#pragma check_stack()   // set stack checking to its default setting
