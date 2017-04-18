/***************************************************************************
 *
 *  Copyright (C) 2000 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       SettingDlg.h
 *  Content:    Setting Dialog header
 *
 ***************************************************************************/
#ifndef __SETTINGDLG_H__
#define __SETTINGDLG_H__

#include <windows.h>
#include <commctrl.h>
#include "resource.h"

extern HINSTANCE hInst;

typedef struct {
	int user;
	int lobby;
	int group;
	int game;
} MAXNUM;

LRESULT CALLBACK SettingDlgProc( HWND, UINT, WPARAM, LPARAM );

#endif __SETTINGDLG_H__
