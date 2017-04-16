// COPYRIGHT:
//
//   (C) Copyright Microsoft Corp. 1993.  All rights reserved.
//
//   You have a royalty-free right to use, modify, reproduce and
//   distribute the Sample Files (and/or any modified version) in
//   any way you find useful, provided that you agree that
//   Microsoft has no warranty obligations or liability for any
//   Sample Application Files which are modified.

#include "zusammen.h"
/*
This file handles all messages for the Frame Window.
It has one entry point which is the Window Procedure for the
Frame Window.
*/

//-----Local Function Prototypes------------------------------------------	  
//	  
BOOL LOCAL Frame_OnCreate(PTRFRAME pfrm, CREATESTRUCT FAR* lpCreateStruct);
void LOCAL Frame_OnDestroy(PTRFRAME pfrm);

BOOL LOCAL Frame_OnQueryEndSession(PTRFRAME pfrm);
void LOCAL Frame_OnEndSession(PTRFRAME pfrm, BOOL fEnding);
void LOCAL Frame_OnClose(PTRFRAME pfrm);

void LOCAL Frame_OnSize(PTRFRAME pfrm, UINT state, int cx, int cy);
void LOCAL Frame_OnPaint(PTRFRAME pfrm);
BOOL LOCAL Frame_OnEraseBkgnd(PTRFRAME pfrm, HDC hdc);
void LOCAL Frame_OnActivate(PTRFRAME pfrm, UINT state, HWND hwndActDeact, BOOL fMinimized);

void LOCAL Frame_OnCommand(PTRFRAME pfrm, int id, HWND hwndCtl, UINT codeNotify);

//---------------------------------------------------------------------------

LRESULT ENTRY Frame_WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    PTRFRAME pfrm = (PTRFRAME)GetWindowWord(hwnd, 0);

    if (pfrm == NULL)
    {
        if (msg == WM_NCCREATE)
        {
            pfrm = (PTRFRAME)LocalAlloc(LMEM_FIXED | LMEM_ZEROINIT, sizeof(FRAME));

            if (pfrm == NULL)
                return (LRESULT)FALSE;

            pfrm->hwnd = hwnd;
            SetWindowWord(hwnd, 0, (WORD)(PTRFRAME)pfrm);
        }
        else
        {
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }
    }

    if (msg == WM_NCDESTROY)
    {
        LocalFree((HLOCAL)pfrm);
        pfrm = NULL;
        SetWindowWord(hwnd, 0, (WORD)(PTRFRAME)pfrm);
    }
	 
    switch (msg)
    {
        HANDLE_MSG(pfrm, WM_CREATE, Frame_OnCreate);
        HANDLE_MSG(pfrm, WM_DESTROY, Frame_OnDestroy);

        HANDLE_MSG(pfrm, WM_CLOSE, Frame_OnClose);
        HANDLE_MSG(pfrm, WM_QUERYENDSESSION, Frame_OnQueryEndSession);
        HANDLE_MSG(pfrm, WM_ENDSESSION, Frame_OnEndSession);

        HANDLE_MSG(pfrm, WM_PAINT, Frame_OnPaint);
        HANDLE_MSG(pfrm, WM_ERASEBKGND, Frame_OnEraseBkgnd);

        HANDLE_MSG(pfrm, WM_SIZE, Frame_OnSize);

        HANDLE_MSG(pfrm, WM_ACTIVATE, Frame_OnActivate);

        HANDLE_MSG(pfrm, WM_COMMAND, Frame_OnCommand);
    default:
		 return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}

BOOL LOCAL Frame_OnCreate(PTRFRAME pfrm, CREATESTRUCT FAR* lpCreateStruct)
{
    pfrm->hwndClient = Client_CreateWindow(pfrm->hwnd,
        0, 0, 0, 0 );

    return pfrm->hwndClient != NULL;
}

void LOCAL Frame_OnDestroy(PTRFRAME pfrm)
{
}

void LOCAL Frame_OnClose(PTRFRAME pfrm)
{
    PostQuitMessage(0);
}

BOOL LOCAL Frame_OnQueryEndSession(PTRFRAME pfrm)
{
    return FORWARD_WM_QUERYENDSESSION(pfrm->hwndClient, SendMessage);
}

void LOCAL Frame_OnEndSession(PTRFRAME pfrm, BOOL fEnding)
{
    FORWARD_WM_ENDSESSION(pfrm->hwndClient, fEnding,SendMessage );
}

void LOCAL Frame_OnPaint(PTRFRAME pfrm)
{
    PAINTSTRUCT ps;
    HDC hdc;
    RECT rc;

    hdc = BeginPaint(pfrm->hwnd, &ps);

    GetClientRect(pfrm->hwnd, &rc);

    FillRect(hdc, &rc, GetStockBrush(LTGRAY_BRUSH));

    EndPaint(pfrm->hwnd, &ps);
}

BOOL LOCAL Frame_OnEraseBkgnd(PTRFRAME pfrm, HDC hdc)
{
    return FORWARD_WM_ERASEBKGND(pfrm->hwnd, hdc, DefWindowProc);
}

void LOCAL Frame_OnSize(PTRFRAME pfrm, UINT state, int cx, int cy)
{
    SetWindowPos(pfrm->hwndClient, NULL,
            0, 0, cx, cy,
            SWP_NOACTIVATE | SWP_NOZORDER);
}

void LOCAL Frame_OnActivate(PTRFRAME pfrm, UINT state, HWND hwndActDeact, BOOL fMinimized)
{
    switch (state)
    {
    case WA_INACTIVE:
	break;

    case WA_ACTIVE:
        SetFocus(pfrm->hwndClient);
        break;

    case WA_CLICKACTIVE:
	break;
    }
}

void LOCAL Frame_OnCommand(PTRFRAME pfrm, int id, HWND hwndCtl, UINT code)
{
    switch (id)
    {
    case CMD_FILEEXIT:
			 PostQuitMessage(0);
	 break;

    default:
        //
        // Pass commands not handled by frame on to the client
        //
        FORWARD_WM_COMMAND(pfrm->hwndClient, id, hwndCtl, code,SendMessage);
	break;
    }
}
