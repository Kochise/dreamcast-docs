// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993-1997  Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:   statdlg.h
//
//  PURPOSE:  contains statdlg declarations
//

#ifndef _STATDLG_H
#define _STATDLG_H

//-------------------------------------------------------------------------
//  Status dialog defines.

#define IDE_CONNECTION  500
#define IDE_STATUS      501
#define IDE_DEVICE      502
#define IDE_ERROR       503
#define IDE_TYPE        504
#define IDB_REFRESH     510


#ifdef WIN16
// Dialog box procedures must be exported in 16-bit applications for Windows.
LRESULT CALLBACK __export StatDlg(HWND, UINT, WPARAM, LPARAM);
#else
LRESULT CALLBACK StatDlg(HWND, UINT, WPARAM, LPARAM);
#endif

#endif

