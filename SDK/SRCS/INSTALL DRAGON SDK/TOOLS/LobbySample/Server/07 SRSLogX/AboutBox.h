/***************************************************************************
 *
 *  Copyright (C) 2000 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       AboutBox.h
 *  Content:    About dialog header
 *
 ***************************************************************************/
#ifndef __ABOUTBOX_H__
#define __ABOUTBOX_H__

#include <windows.h>

void WriteIPAddress( HWND );
void ReadIPAddress( HWND );
LRESULT CALLBACK AboutDlgProc( HWND, UINT, WPARAM, LPARAM );

#endif __ABOUTBOX_H__
