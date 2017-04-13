/*****************************************************************************
*
*  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
*  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
*  TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR
*  A PARTICULAR PURPOSE.
*
*  Copyright (C) 1993 - 1997 Microsoft Corporation. All Rights Reserved.
*
*****************************************************************************/

// tridee.c
//
HBRUSH WINAPI TrideeCreate (
   HWND   hWnd);

BOOL WINAPI TrideeDestroy (
   HWND   hWnd);

VOID WINAPI TrideeWellShadow (
   HDC    hDC,
   LPRECT lprc);

int WINAPI DisplayAbout(
   HWND  hWnd);

BOOL WINAPI AboutDlgProc(
   HWND   hDlg, 
   UINT   wMsgID,
   WPARAM wParam, 
   LPARAM lParam);
   
BOOL WINAPI GetWindowPos(
   LPRECT lprc);
   
BOOL WINAPI SaveWindowPos(
   LPRECT lprc);
