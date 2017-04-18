// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (C) 1993-1997  Microsoft Corporation.  All Rights Reserved.
//
//  MODULE:   authdlg.h
//
//  PURPOSE:  contains authdlg declarations
//

#ifndef _AUTHDLG_H
#define _AUTHDLG_H

//-------------------------------------------------------------------------
//  Authentication dialog defines.

#define IDE_USERNAME  600
#define IDE_PASSWORD  601
#define IDE_DOMAIN    602


#ifdef WIN16
// Dialog box procedures must be exported in 16-bit applications for Windows.
LRESULT CALLBACK __export AuthDlg(HWND, UINT, WPARAM, LPARAM);
#else
LRESULT CALLBACK AuthDlg(HWND, UINT, WPARAM, LPARAM);
#endif

#endif
