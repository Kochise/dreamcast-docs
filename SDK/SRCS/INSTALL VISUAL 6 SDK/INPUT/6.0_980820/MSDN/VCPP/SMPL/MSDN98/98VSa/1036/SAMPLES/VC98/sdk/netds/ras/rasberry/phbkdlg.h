// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993-1997  Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:   phbkdlg.h
//
//  PURPOSE:  contains phbkdlg declarations
//

#ifndef _PHBKDLG_H
#define _PHBKDLG_H

//-------------------------------------------------------------------------
//  phbkdlg dialog defines.

#define IDL_ENTRY       400
#define IDB_DIAL        401
#define IDC_USECURRENT  402

extern BOOL g_bUseCurrent;

#ifdef WIN16
// Dialog box procedures must be exported in 16-bit applications for Windows.
LRESULT CALLBACK __export PhbkDlg(HWND, UINT, WPARAM, LPARAM);
#else
LRESULT CALLBACK PhbkDlg(HWND, UINT, WPARAM, LPARAM);
#endif

#endif

