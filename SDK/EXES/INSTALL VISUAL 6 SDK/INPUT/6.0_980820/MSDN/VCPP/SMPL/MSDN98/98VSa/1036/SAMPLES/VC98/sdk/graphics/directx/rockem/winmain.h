/*==========================================================================
 *
 *  Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.
 *
 *  File: winmain.h
 *
 ***************************************************************************/

#ifndef __WINMAIN_H
#define __WINMAIN_H

void		RegError(char *sErr);

BOOL		InitClass(HINSTANCE hInst);
BOOL		InitWindow(HINSTANCE hInst, int nCmdShow);
long FAR PASCAL	WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
int FAR PASCAL	WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow);	

#endif

