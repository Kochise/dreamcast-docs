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
This file contains the code to setup and initialize the
client window.
*/

BOOL GLOBAL Client_Initialize (APP* papp)
{
    WNDCLASS cls;

    cls.hCursor 	= LoadCursor(NULL, IDC_ARROW);
    cls.hIcon           = NULL;
    cls.lpszMenuName    = NULL;
    cls.hInstance       = papp->hinst;
    cls.lpszClassName   = "Zusammen_Client";
    cls.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
    cls.lpfnWndProc     = Client_WndProc;
    cls.style           = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
    cls.cbWndExtra      = 0;
    cls.cbClsExtra	= 0;

    if (!RegisterClass(&cls))
        return FALSE;

    return TRUE;
}

void GLOBAL Client_Terminate (APP* papp)
{
}

HWND GLOBAL Client_CreateWindow (HWND hwndParent, int x, int y, int cx, int cy )
{

	return CreateWindowEx(
				 0L, 			    // extendedStyle
            "Zusammen_Client",               // class name
            NULL,                           // text
            WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL,
            x, y, cx, cy,                   // x, y, cx, cy
            hwndParent,                     // hwndParent
				NULL,									  // hmenu
            g_app.hinst,                    // hInstance
            0L);                         // lpCreateParams
}

void GLOBAL Client_OnDestroy (HWND hwnd)
{
}
