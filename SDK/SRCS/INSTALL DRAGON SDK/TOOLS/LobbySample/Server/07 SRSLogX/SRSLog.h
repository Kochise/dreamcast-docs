/***************************************************************************
 *
 *  Copyright (C) 2000 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       SRSLog.h
 *  Content:    main window header
 *
 ***************************************************************************/
#ifndef __SRSLOG_H__
#define __SRSLOG_H__

#include <windows.h>
#include <commctrl.h>
#include "resource.h"

#include "SRScom.h"
#include "SRSdebug.h"
#include "SRSmanage.h"

#define FORCC(A) (A >> 24 | (A >> 8) & 0xff00 | (A << 8) & 0xff0000 | A << 24 )
#define ID_MYTREE 10000
#define ID_MYLIST 10001
#define OPENINGTIMER 1
#define AUTOUPDATETIMER 2
#define AUTODISCONNECT 3
#define VARIANT_VALUE 0.00001157407407407
#define SKIP176 176

LRESULT CALLBACK WndProc( HWND, UINT, WPARAM, LPARAM );
LRESULT CALLBACK ChildProcL( HWND, UINT, WPARAM, LPARAM );
LRESULT CALLBACK ChildProcR( HWND, UINT, WPARAM, LPARAM );
BOOL InitApp( HINSTANCE, WNDPROC, LPCTSTR );
BOOL InitInstance( HINSTANCE, int );
void AddItem( HWND );
void DeleteAllItem( HWND );
int GetMyFrameWidth( HWND );
void InsColumn( char*, int, int );
void InsertList( char*, char*, char*, char*, char*, char* );
BOOL DeleteList( char* );
BOOL DeleteAllList();
BOOL ReadUserFile();
BOOL GetUserStrInfoFromClientName( char*, SRS_USER_ITEM* );
BOOL GetUserStrInfo( int, SRS_USER_ITEM* );
int GetPastTime( LPSYSTEMTIME );
int TreeViewGetCurSel();

char szClassName[] = "SRSLogV2";	// Window Class
int x0, y0, x1, y1, x2, y2;
int frame;
HWND hChildL;
HWND hChildR;
HWND hTree;
HWND hList;
HINSTANCE hInst;
int user_counter;
int auto_update;
int disconnecttime;
BOOL bParentSizeChange = FALSE;
WORD g_wID = 0xffff;

#endif __SRSLOG_H__
