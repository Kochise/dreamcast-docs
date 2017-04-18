// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993-1997  Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:   dialdlg.h
//
//  PURPOSE:  contains dialdlg declarations
//

#ifndef _DIALDLG_H
#define _DIALDLG_H

//-------------------------------------------------------------------------
//  Dialing dialog defines.

#define IDT_MESSAGE     300


#ifdef WIN16
// Dialog box procedures must be exported in 16-bit applications for Windows.
LRESULT CALLBACK __export DialDlg(HWND, UINT, WPARAM, LPARAM);
#else
LRESULT CALLBACK DialDlg(HWND, UINT, WPARAM, LPARAM);
#endif

#endif

