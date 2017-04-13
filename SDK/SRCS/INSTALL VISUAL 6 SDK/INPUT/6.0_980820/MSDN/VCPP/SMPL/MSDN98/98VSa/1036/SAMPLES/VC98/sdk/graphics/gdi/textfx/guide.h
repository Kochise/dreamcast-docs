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
 *	GUIDE.H  										                         *
 *																			 *
 *	PURPOSE:  Routines for reading and displaying guide lines				 *
 *																			 *
 ****************************************************************************/

#define MAXGUIDESEGMENTS 1000  // Max number of segments to read from user

BOOL GetGuideLine(HWND, LPPOINT*, LPDWORD);
BOOL ShowGuide(HDC, LPPOINT, DWORD);
