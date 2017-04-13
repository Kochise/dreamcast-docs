/*==========================================================================
 *
 *  Copyright (C) 1997 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       client.cpp
 *  Content:	Slot machine client using DirectPlay.
 *
 ***************************************************************************/

#include <windows.h>
#include <windowsx.h>
#include <stdio.h>

#include "dpslots.h"
#include "resource.h"

// constants
const DWORD SLOTWIDTH			= 110;			// width of slot
const DWORD SLOTHEIGHT			= 119;			// height of slot
const DWORD SLOTBORDER			= 9;			// space between slots
const DWORD REVSPERSECOND		= 1;			// no. revolutions per second
const DWORD PIXELSPERSLOT		= SLOTHEIGHT - SLOTBORDER;		// no. vertical pixels per slot
const DWORD PIXELSPERREV		= PIXELSPERSLOT * SLOTSPERWHEEL;// no. vertical pixels drawn per revolution
const DWORD PIXELSPERSECOND		= PIXELSPERREV * REVSPERSECOND;	// no. vertical pixels drawn per second
const UINT	TIMERID				= 1;			// timer ID to use
const UINT	TIMERINTERVAL		= 50;			// timer interval
const UINT	MAXSTRING			= 200;			// max size of a string

// window messages
const UINT	WM_USER_UPDATEBALANCE = WM_USER + BALANCERESPONSE;
const UINT	WM_USER_STARTSPINNING = WM_USER + SPINRESPONSE;

// structures
typedef struct {
	DWORD	dwIndex;							// index of wheel slot to show
    DWORD	dwStartTicks;						// time wheel started spinning
	DWORD	dwDuration;							// duration wheel should spin
} WHEELINFO, *LPWHEELINFO;

// globals
HWND			ghClientWnd = NULL;				// main window

// prototypes
HRESULT			SendBalanceRequest(LPDPLAYINFO lpDPInfo);
HRESULT			SendSpinRequest(LPDPLAYINFO lpDPInfo, DWORD dwAmountBet);
void			DrawWheels(LPWHEELINFO lpWheels, HBITMAP hWheelBitmap,
						   HDC hDC, LPRECT lpBoundsRect);
void			StartSpinning(LPWHEELINFO lpWheels);
BOOL			SpinWheels(HWND hWnd, LPWHEELINFO lpWheels, HBITMAP hWheelBitmap);

BOOL CALLBACK ClientWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static LPDPLAYINFO			lpDPInfo = NULL;
	static UINT					idTimer = 0;
	static HBITMAP				hWheelBitmap = NULL;
	static WHEELINFO			WheelInfo[NUMWHEELS];
	static MSG_SPINRESPONSE		SpinResponse;
	CHAR						szStr[MAXSTRING];
	DWORD						i;
	DWORD						dwAmountBet;

    switch(uMsg)
    {
    case WM_INITDIALOG:
        // save the connection info pointer
        lpDPInfo = (LPDPLAYINFO) lParam;

		// store global window
		ghClientWnd = hWnd;

		// get slots bitmap
		hWheelBitmap = LoadBitmap(ghInstance, MAKEINTRESOURCE(IDB_SLOTSBITMAP));

		// initialize slots
		for (i = 0; i < NUMWHEELS; i++)
			WheelInfo[i].dwIndex = ((DWORD)rand()) % SLOTSPERWHEEL;

        // get starting balance
		SendBalanceRequest(lpDPInfo);
		break;

    case WM_DESTROY:
		// stop the timer
		if (idTimer)
		{
			KillTimer(hWnd, idTimer); 
			idTimer = 0;
		}

		// free the bitmap handle
		if (hWheelBitmap)
		{
			DeleteObject(hWheelBitmap);
			hWheelBitmap = NULL;
		}
		ghClientWnd = NULL;
        break;

	case WM_USER_UPDATEBALANCE:

		// balance is in lParam
        sprintf(szStr, "$%4d", lParam);

        // display new balance
		SetDlgItemText(hWnd, IDC_EDIT_BALANCE, szStr);
		break;

	case WM_USER_STARTSPINNING:

		// copy spin response message from lParam
		SpinResponse = *((LPMSG_SPINRESPONSE) lParam);
		GlobalFreePtr((LPVOID) lParam);	// free memory

		// check for valid spin
		if FAILED(SpinResponse.hr)
		{
			SetDlgItemText(hWnd, IDC_RESULTEDIT, "You don't have enough money!");
		}
		else
		{
			// copy slot settings specified by server
			for (i = 0; i < NUMWHEELS; i++)
				WheelInfo[i].dwIndex = SpinResponse.dwIndex[i];

			// clear win or lose
			SetDlgItemText(hWnd, IDC_RESULTEDIT, "");

			// start things spinning
			StartSpinning(WheelInfo);
			idTimer = SetTimer(hWnd, TIMERID, TIMERINTERVAL, NULL);

			// disable spin button while spinning
			EnableDlgButton(hWnd, IDC_SPINBUTTON, FALSE);
		}
		break;

	case WM_TIMER:
		// readraw any spinning wheels
		if (!SpinWheels(hWnd, WheelInfo, hWheelBitmap))
		{
			KillTimer(hWnd, idTimer); 
			idTimer = 0;

			// display amount won or lost
			if (SpinResponse.dwAmountWonOrLost > 0)
			{
				sprintf(szStr,"You win $%d!", SpinResponse.dwAmountWonOrLost);
				PlaySound(MAKEINTRESOURCE(IDR_WINWAVE), ghInstance, SND_ASYNC | SND_RESOURCE);
			}
			else if (SpinResponse.dwAmountWonOrLost < 0)
			{
				sprintf(szStr,"You lose $%d!", -SpinResponse.dwAmountWonOrLost);
				PlaySound(MAKEINTRESOURCE(IDR_LOSEWAVE), ghInstance, SND_ASYNC | SND_RESOURCE);
			}
			else
			{
				strcpy(szStr, "");
			}

			// display win or loss
			SetDlgItemText(hWnd, IDC_RESULTEDIT, szStr);

			PostMessage(hWnd, WM_USER_UPDATEBALANCE, (WPARAM) 0, (LPARAM) SpinResponse.dwBalance);

			// enable spin button again
			EnableDlgButton(hWnd, IDC_SPINBUTTON, TRUE);
		}
		break;

    case WM_DRAWITEM:
		{
			DRAWITEMSTRUCT	*diInfo;

			diInfo = (DRAWITEMSTRUCT *) lParam;

			switch (diInfo->CtlID)
			{
			case IDC_SLOTS:
				if (diInfo->itemAction == ODA_DRAWENTIRE)
				{
					DrawWheels(WheelInfo, hWheelBitmap, diInfo->hDC, &diInfo->rcItem);
				}
				break;
			}
		}
		break;

	case WM_COMMAND:
        switch(LOWORD(wParam))
        {
		case IDC_SPINBUTTON:
			// find out how much was bet
			dwAmountBet = 0;

			// one dollar
			if (DlgItemIsChecked(hWnd, IDC_BET1CHECK))
				dwAmountBet += 1;

			// five dollars
			if (DlgItemIsChecked(hWnd, IDC_BET2CHECK))
				dwAmountBet += 5;

			// ten dollars
			if (DlgItemIsChecked(hWnd, IDC_BET3CHECK))
				dwAmountBet += 10;

			// ask server for results of spin using this bet
            SendSpinRequest(lpDPInfo, dwAmountBet);            
			break;

        case IDCANCEL:
			EndDialog(hWnd, FALSE);
            break;
		}
		break;
	}

    // Allow for default processing
    return FALSE;
}

void ClientApplicationMessage(LPDPLAYINFO lpDPInfo, LPDPMSG_GENERIC lpMsg, DWORD dwMsgSize,
							  DPID idFrom, DPID idTo)
{
	switch (lpMsg->dwType)
	{
    case BALANCERESPONSE:
        {
            LPMSG_BALANCERESPONSE lpBalance = (LPMSG_BALANCERESPONSE)lpMsg;

 			PostMessage(ghClientWnd, WM_USER_UPDATEBALANCE, (WPARAM) 0, (LPARAM) lpBalance->dwBalance);
        }
        break;

    case SPINRESPONSE:
        {
            LPMSG_SPINRESPONSE lpSpin = (LPMSG_SPINRESPONSE)lpMsg;
            LPMSG_SPINRESPONSE lpSpinCopy;

			// make a copy of the message so we can pass it to the wndproc
			lpSpinCopy = (LPMSG_SPINRESPONSE) GlobalAllocPtr(GHND, sizeof(MSG_SPINRESPONSE));
			if (lpSpinCopy == NULL)
				break;

			*lpSpinCopy = *lpSpin;

            PostMessage(ghClientWnd, WM_USER_STARTSPINNING, (WPARAM) 0, (LPARAM) lpSpinCopy);
        }
        break;

    default:
        break; 
	}
}

void ClientSystemMessage(LPDPLAYINFO lpDPInfo, LPDPMSG_GENERIC lpMsg, DWORD dwMsgSize,
						 DPID idFrom, DPID idTo)
{
    // The body of each case is there so you can set a breakpoint and examine
    // the contents of the message received.
	switch (lpMsg->dwType)
	{
	case DPSYS_CREATEPLAYERORGROUP:
        {
            LPDPMSG_CREATEPLAYERORGROUP lp = (LPDPMSG_CREATEPLAYERORGROUP) lpMsg;
        }
		break;

	case DPSYS_DESTROYPLAYERORGROUP:
        {
            LPDPMSG_DESTROYPLAYERORGROUP lp = (LPDPMSG_DESTROYPLAYERORGROUP)lpMsg;
        }
		break;

	case DPSYS_ADDPLAYERTOGROUP:
        {
            LPDPMSG_ADDPLAYERTOGROUP lp = (LPDPMSG_ADDPLAYERTOGROUP)lpMsg;
        }
		break;

	case DPSYS_DELETEPLAYERFROMGROUP:
        {
            LPDPMSG_DELETEPLAYERFROMGROUP lp = (LPDPMSG_DELETEPLAYERFROMGROUP)lpMsg;
        }
		break;

	case DPSYS_SESSIONLOST:
        {
            LPDPMSG_SESSIONLOST lp = (LPDPMSG_SESSIONLOST)lpMsg;
        }
		break;

	case DPSYS_HOST:
        {
            LPDPMSG_HOST	lp = (LPDPMSG_HOST)lpMsg;
        }
		break;

	case DPSYS_SETPLAYERORGROUPDATA:
        {
            LPDPMSG_SETPLAYERORGROUPDATA lp = (LPDPMSG_SETPLAYERORGROUPDATA)lpMsg;
        }
		break;

	case DPSYS_SETPLAYERORGROUPNAME:
        {
            LPDPMSG_SETPLAYERORGROUPNAME lp = (LPDPMSG_SETPLAYERORGROUPNAME)lpMsg;
        }
		break;

	case DPSYS_SECUREMESSAGE:
        {
            LPDPMSG_SECUREMESSAGE lp = (LPDPMSG_SECUREMESSAGE)lpMsg;

			ClientApplicationMessage(lpDPInfo, (LPDPMSG_GENERIC) lp->lpData, lp->dwDataSize,
							  lp->dpIdFrom, idTo);

        }
		break;
	}
}

HRESULT SendBalanceRequest(LPDPLAYINFO lpDPInfo)
{
    MSG_BALANCEREQUEST	Msg;

    ZeroMemory(&Msg, sizeof(MSG_BALANCEREQUEST));
    Msg.dwType = BALANCEREQUEST;

    return (lpDPInfo->lpDirectPlay3A->Send(lpDPInfo->dpidPlayer,
						DPID_SERVERPLAYER, SENDFLAGS(lpDPInfo->bIsSecure),
						&Msg, sizeof(MSG_BALANCEREQUEST)));
}

HRESULT SendSpinRequest(LPDPLAYINFO lpDPInfo, DWORD dwAmountBet)
{
    MSG_SPINREQUEST		Msg;

    ZeroMemory(&Msg, sizeof(MSG_SPINREQUEST));
    Msg.dwType = SPINREQUEST;
	Msg.dwAmountBet = dwAmountBet;

    return (lpDPInfo->lpDirectPlay3A->Send(lpDPInfo->dpidPlayer,
						DPID_SERVERPLAYER, SENDFLAGS(lpDPInfo->bIsSecure),
						&Msg, sizeof(MSG_SPINREQUEST)));
}

#define RECTWIDTH(lpRect)     ((lpRect)->right - (lpRect)->left)
#define RECTHEIGHT(lpRect)    ((lpRect)->bottom - (lpRect)->top)

BOOL PaintBitmap(HDC hDC, LPRECT lpDCRect, HBITMAP hDDB,  LPRECT lpDDBRect)
{
    HDC         hMemDC;            // Handle to memory DC
    HBITMAP     hOldBitmap;        // Handle to previous bitmap
    BOOL        bSuccess = FALSE;  // Success/fail flag

    // Create a memory DC

    hMemDC = CreateCompatibleDC(hDC);

    // If this failed, return FALSE

    if (!hMemDC)
        return FALSE;

    // Select bitmap into the memory DC

    hOldBitmap = (HBITMAP) SelectObject (hMemDC, hDDB);

    // Make sure to use the stretching mode best for color pictures

    SetStretchBltMode (hDC, COLORONCOLOR);

    // Determine whether to call StretchBlt() or BitBlt()
    if ((RECTWIDTH(lpDCRect)  == RECTWIDTH(lpDDBRect)) &&
            (RECTHEIGHT(lpDCRect) == RECTHEIGHT(lpDDBRect)))
        bSuccess = BitBlt(hDC, lpDCRect->left, lpDCRect->top,
                lpDCRect->right - lpDCRect->left,
                lpDCRect->bottom - lpDCRect->top, hMemDC, lpDDBRect->left,
                lpDDBRect->top, SRCCOPY);
    else
        bSuccess = StretchBlt(hDC, lpDCRect->left,  lpDCRect->top, 
                lpDCRect->right - lpDCRect->left,
                lpDCRect->bottom - lpDCRect->top, hMemDC, lpDDBRect->left, 
                lpDDBRect->top,  lpDDBRect->right - lpDDBRect->left,
                lpDDBRect->bottom - lpDDBRect->top, SRCCOPY);

    // Clean up

    SelectObject(hMemDC, hOldBitmap);

    DeleteDC(hMemDC);

    // Return with success/fail flag

    return bSuccess;
}

void DrawWheels(LPWHEELINFO lpWheels, HBITMAP hWheelBitmap, HDC hDC, LPRECT lpBoundsRect)
{
	RECT			rectDC, rectSlot;
	DWORD			dwWidth, dwHeight, dwXOffset, dwYOffset;
	DWORD			i;

	if (hWheelBitmap == NULL)
		return;

	dwWidth = lpBoundsRect->right - lpBoundsRect->left;
	dwHeight = lpBoundsRect->bottom - lpBoundsRect->top;

	dwXOffset = (dwWidth - (SLOTWIDTH * NUMWHEELS)) / (NUMWHEELS + 1);
	dwYOffset = (dwHeight - SLOTHEIGHT) / 2;

	SetRect(&rectDC, dwXOffset, dwYOffset,
			dwXOffset + SLOTWIDTH, dwYOffset + SLOTHEIGHT);

	for (i = 0; i < NUMWHEELS; i++)
	{
		SetRect(&rectSlot, 0, 0, SLOTWIDTH, SLOTHEIGHT);
		OffsetRect(&rectSlot, 0, lpWheels[i].dwIndex * PIXELSPERSLOT);

		PaintBitmap(hDC, &rectDC, hWheelBitmap, &rectSlot);

		OffsetRect(&rectDC, SLOTWIDTH + dwXOffset, 0);
	}
}

void StartSpinning(LPWHEELINFO lpWheels)
{
	DWORD	i;

	for (i = 0; i < NUMWHEELS; i++)
	{
		lpWheels[i].dwStartTicks = GetTickCount();
		lpWheels[i].dwStartTicks -= lpWheels[i].dwIndex * PIXELSPERSLOT * 1000 / PIXELSPERREV;
		lpWheels[i].dwDuration = 1000 * (i + 1) + 1000;
	}
}

BOOL SpinWheels(HWND hWnd, LPWHEELINFO lpWheels, HBITMAP hWheelBitmap)
{
	HDC				hDC;
	RECT			rectBounds;
	LPRECT			lpBoundsRect;
	RECT			rectDC, rectSlot;
	DWORD			dwWidth, dwHeight, dwXOffset, dwYOffset, dwYStart;
	DWORD			i, dwTicks, dwStoppedCount;

	if (hWheelBitmap == NULL)
		return (FALSE);

	hDC = GetWindowDC(GetDlgItem(hWnd, IDC_SLOTS));
	if (hDC == NULL)
		return (FALSE);

	if (!GetWindowRect(GetDlgItem(hWnd, IDC_SLOTS), &rectBounds))
		return (FALSE);

	lpBoundsRect = &rectBounds;

	dwWidth = lpBoundsRect->right - lpBoundsRect->left;
	dwHeight = lpBoundsRect->bottom - lpBoundsRect->top;

	dwXOffset = (dwWidth - (SLOTWIDTH * NUMWHEELS)) / (NUMWHEELS + 1);
	dwYOffset = (dwHeight - SLOTHEIGHT) / 2;

	SetRect(&rectDC, dwXOffset, dwYOffset,
			dwXOffset + SLOTWIDTH, dwYOffset + SLOTHEIGHT);

	dwStoppedCount = 0;
	for (i = 0; i < NUMWHEELS; i++)
	{
		if (lpWheels[i].dwDuration == 0)
		{
			dwStoppedCount++;
		}
		else
		{
			dwTicks = GetTickCount() - lpWheels[i].dwStartTicks;
			dwYStart = (dwTicks * PIXELSPERSECOND) / 1000;
			dwYStart %= PIXELSPERREV;

			if (dwTicks >= lpWheels[i].dwDuration)
			{
//				lpWheels[i].value = ((dwYStart + (PIXELSPERSLOT - 1)) / PIXELSPERSLOT) % SLOTSPERWHEEL;

				SetRect(&rectSlot, 0, 0, SLOTWIDTH, SLOTHEIGHT);
				OffsetRect(&rectSlot, 0, lpWheels[i].dwIndex * PIXELSPERSLOT);
				PaintBitmap(hDC, &rectDC, hWheelBitmap, &rectSlot);

				lpWheels[i].dwDuration = 0;
                if (dwStoppedCount == (NUMWHEELS - 1))
                    PlaySound(MAKEINTRESOURCE(IDR_STOPWAVE), ghInstance, SND_RESOURCE);
                else
                    PlaySound(MAKEINTRESOURCE(IDR_STOPWAVE), ghInstance, SND_ASYNC | SND_RESOURCE);
            }
			else
			{
				SetRect(&rectSlot, 0, 0, SLOTWIDTH, SLOTHEIGHT);
				OffsetRect(&rectSlot, 0, dwYStart);
				if (rectSlot.bottom > PIXELSPERREV)
				{
					RECT	rectSlotTmp, rectDCTmp;
					DWORD	height;

					// copy from bottom end of bitmap
					height = PIXELSPERREV - rectSlot.top;
					rectSlotTmp = rectSlot;
					rectSlotTmp.bottom = rectSlotTmp.top + height;
					rectDCTmp = rectDC;
					rectDCTmp.bottom = rectDCTmp.top + height;
					PaintBitmap(hDC, &rectDCTmp, hWheelBitmap, &rectSlotTmp);

					height = rectSlot.bottom - PIXELSPERREV;
					rectSlotTmp = rectSlot;
					rectSlotTmp.top = 0;
					rectSlotTmp.bottom = height;
					rectDCTmp = rectDC;
					rectDCTmp.top = rectDCTmp.bottom - height;
					PaintBitmap(hDC, &rectDCTmp, hWheelBitmap, &rectSlotTmp);
				}
				else
					PaintBitmap(hDC, &rectDC, hWheelBitmap, &rectSlot);
			}
		}
		OffsetRect(&rectDC, SLOTWIDTH + dwXOffset, 0);
	}

	return (dwStoppedCount != NUMWHEELS);
}
