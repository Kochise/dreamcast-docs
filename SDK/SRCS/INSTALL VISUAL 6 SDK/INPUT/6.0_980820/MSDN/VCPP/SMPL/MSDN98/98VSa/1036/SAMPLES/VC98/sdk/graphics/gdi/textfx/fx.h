/*****************************************************************************\
*       This is a part of the Microsoft Source Code Samples.
*       Copyright (C) 1992-1997 Microsoft Corporation.
*       All rights reserved.
*       This source code is only intended as a supplement to
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the
*       Microsoft samples programs.
\*****************************************************************************/
/*****************************************************************************
 *																			 *
 *	FX.H     										                         *
 *																			 *
 *	PURPOSE:  Routines for rendering text with stange effects                *
 *																			 *
 ****************************************************************************/

#include <windows.h>

#define MAXFILLPOINTS 64000

BOOL FillOut(LPPOINT*, LPDWORD);
BOOL RenderPathPoints(HDC, LPPOINT, LPBYTE, int, BOOL);
BOOL RenderAndFillPath(HDC, LPPOINT, LPBYTE, int);
BOOL TextEffect(HDC, LPPOINT, LPPOINT, DWORD, DWORD, LPSTR, BOOL);
