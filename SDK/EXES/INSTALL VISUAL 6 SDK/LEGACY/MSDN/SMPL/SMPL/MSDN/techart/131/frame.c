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
This file contains the code which maintains the Frame window.
This file does not contain any Entry Points. 
*/

//---------------------------------------------------------------------------

BOOL GLOBAL Frame_Initialize(APP* papp)
{
    WNDCLASS cls;

    cls.hCursor 	= LoadCursor(NULL, IDC_ARROW);
    cls.hIcon           = LoadIcon(papp->hinst, MAKEINTRESOURCE(IDR_FRAMEICON));
    cls.lpszMenuName    = MAKEINTRESOURCE(IDR_FRAMEMENU);
    cls.hInstance       = papp->hinst;
    cls.lpszClassName   = "Zusammen_Frame";
    cls.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
    cls.lpfnWndProc     = Frame_WndProc;
    cls.style           = CS_DBLCLKS;
    cls.cbWndExtra      = sizeof(FRAME _near*);
    cls.cbClsExtra	= 0;

    if (!RegisterClass(&cls))
        return FALSE;

    return TRUE;
}

void GLOBAL Frame_Terminate(APP* papp)
{
}


HWND GLOBAL Frame_CreateWindow( LPCSTR lpszText, int x, int y,
		int cx, int cy, HINSTANCE hinst)
{
    return CreateWindowEx(
            0L, "Zusammen_Frame", lpszText,
            WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
            x, y, cx, cy,
				NULL, NULL, hinst, NULL);
}
