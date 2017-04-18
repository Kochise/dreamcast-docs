/***************************************************************************
 *
 *  Copyright (C) 2000 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       SRSLog.cpp
 *  Content:    main window procedure
 *
 ***************************************************************************/
#include <stdio.h>
#include "SRSLog.h"
#include "AboutBox.h"
#include "SettingDlg.h"
#include "Registry.h"
#include "SRSdisconnect.h"

#define SRS_USER_ITEM_SZ4096 (SRS_USER_ITEM_SZ * 4096)

// dialog box message
#define DIALOGBOXMES0	"サーバーのIPアドレスを設定してください\n"																			\
						"IPアドレスが間違っていると正しく動作しない場合があります"															\
						"コマンドラインから\"ipconfig\"と入力すると正しいIPアドレスがわかります"
#define DIALOGBOXMES1	"レジストリ登録されていません\n"																					\
						"初期値を設定して起動します"
#define DIALOGBOXMES2	"すべてのSRSプロセスを終了しますか？\n"

/*------------------------------------------------------------------------------

	main

------------------------------------------------------------------------------*/
int WINAPI WinMain( HINSTANCE hCurInst, HINSTANCE hPrevInst, LPSTR lpsCmdLine, int nCmdShow )
{
	MSG msg;

	hInst = hCurInst;
	if ( ! InitApp( hCurInst, WndProc, szClassName ) ) return FALSE;
	if ( ! InitInstance( hCurInst, nCmdShow ) ) return FALSE;
	while( GetMessage( &msg, NULL, 0, 0 ) )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}
	return msg.wParam;
}

//
// Require comctl32.dll version 4.71 or above!!!
//
// Entry Window Class
//
BOOL InitApp( HINSTANCE hInst, WNDPROC fnWndProc, LPCTSTR szClassNm )
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = fnWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon( hInst, "SRSLOG" );
	wc.hCursor = LoadCursor( NULL, IDC_ARROW );
	wc.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
	wc.lpszMenuName = "SRSLOG";
	wc.lpszClassName = (LPCSTR) szClassNm;
	wc.hIconSm = wc.hIcon;
	return( RegisterClassEx( &wc ) );
}

//
// Instance initialization
//
BOOL InitInstance( HINSTANCE hInst, int nCmdShow )
{
	HWND hWnd;

	hWnd = CreateWindow( szClassName, "SRSlog", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 660, 400, NULL, NULL, hInst, NULL );
	if ( ! hWnd ) return FALSE;
	ShowWindow( hWnd, nCmdShow );
	UpdateWindow( hWnd );
	return TRUE;
}

//
// Window Procedure
//
LRESULT CALLBACK WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	RECT rc;
	switch( msg )
	{
	case WM_COMMAND:
		switch( LOWORD( wParam ) )
		{
		case IDM_EXIT:
			SendMessage( hWnd, WM_CLOSE, 0, 0 );
			break;
		case IDM_UPDATEVIEW:
			ReadUserFile();
			break;
		case IDM_ABOUT:
			DialogBox( hInst, "ABOUTDLG", hWnd, (DLGPROC) AboutDlgProc );
			break;
		case IDM_DBGNOTHING:
			if ( user_counter == 0 )
			{
				SetDebugInfo( 0 );
				CheckMenuRadioItem( GetMenu( hWnd ), IDM_DBGNOTHING, IDM_DGBTRACE, IDM_DBGNOTHING, MF_BYCOMMAND );
			}
			break;
		case IDM_DBGALL:
			if ( user_counter == 0 )
			{
				SetDebugInfo( 1 );
				CheckMenuRadioItem( GetMenu( hWnd ), IDM_DBGNOTHING, IDM_DGBTRACE, IDM_DBGALL, MF_BYCOMMAND );
			}
			break;
		case IDM_DBGFILE:
			if ( user_counter == 0 )
			{
				SetDebugInfo( 2 );
				CheckMenuRadioItem( GetMenu( hWnd ), IDM_DBGNOTHING, IDM_DGBTRACE, IDM_DBGFILE, MF_BYCOMMAND );
			}
			break;
		case IDM_DGBTRACE:
			if ( user_counter == 0 )
			{
				SetDebugInfo( 3 );
				CheckMenuRadioItem( GetMenu( hWnd ), IDM_DBGNOTHING, IDM_DGBTRACE, IDM_DGBTRACE, MF_BYCOMMAND );
			}
			break;
		case IDM_SETCOMMON:		// Common setting dialog
			if ( DialogBox( hInst, "SETTINGDLG", hWnd, (DLGPROC) SettingDlgProc ) == IDOK )
			{
				DeleteAllItem( hTree );
				AddItem( hTree );
			}
			break;
		case IDM_AUTOUPDATE0:
			KillTimer( hWnd, AUTOUPDATETIMER );
			CheckMenuRadioItem( GetMenu( hWnd ), IDM_AUTOUPDATE0, IDM_AUTOUPDATE5, IDM_AUTOUPDATE0, MF_BYCOMMAND );
			auto_update = 0;
			break;
		case IDM_AUTOUPDATE1:
			KillTimer( hWnd, AUTOUPDATETIMER );
			CheckMenuRadioItem( GetMenu( hWnd ), IDM_AUTOUPDATE0, IDM_AUTOUPDATE5, IDM_AUTOUPDATE1, MF_BYCOMMAND );
			auto_update = 1;
			SetTimer( hWnd, AUTOUPDATETIMER, 60000 * auto_update, NULL );
			break;
		case IDM_AUTOUPDATE2:
			KillTimer( hWnd, AUTOUPDATETIMER );
			CheckMenuRadioItem( GetMenu( hWnd ), IDM_AUTOUPDATE0, IDM_AUTOUPDATE5, IDM_AUTOUPDATE2, MF_BYCOMMAND );
			auto_update = 2;
			SetTimer( hWnd, AUTOUPDATETIMER, 60000 * auto_update, NULL );
			break;
		case IDM_AUTOUPDATE3:
			KillTimer( hWnd, AUTOUPDATETIMER );
			CheckMenuRadioItem( GetMenu( hWnd ), IDM_AUTOUPDATE0, IDM_AUTOUPDATE5, IDM_AUTOUPDATE3, MF_BYCOMMAND );
			auto_update = 3;
			SetTimer( hWnd, AUTOUPDATETIMER, 60000 * auto_update, NULL );
			break;
		case IDM_AUTOUPDATE4:
			KillTimer( hWnd, AUTOUPDATETIMER );
			CheckMenuRadioItem( GetMenu( hWnd ), IDM_AUTOUPDATE0, IDM_AUTOUPDATE5, IDM_AUTOUPDATE4, MF_BYCOMMAND );
			auto_update = 4;
			SetTimer( hWnd, AUTOUPDATETIMER, 60000 * auto_update, NULL );
			break;
		case IDM_AUTOUPDATE5:
			KillTimer( hWnd, AUTOUPDATETIMER );
			CheckMenuRadioItem( GetMenu( hWnd ), IDM_AUTOUPDATE0, IDM_AUTOUPDATE5, IDM_AUTOUPDATE5, MF_BYCOMMAND );
			auto_update = 5;
			SetTimer( hWnd, AUTOUPDATETIMER, 60000 * auto_update, NULL );
			break;

		case IDM_AUTODISCONNECT0:
			CheckMenuRadioItem( GetMenu( hWnd ), IDM_AUTODISCONNECT0, IDM_AUTODISCONNECT20, IDM_AUTODISCONNECT0, MF_BYCOMMAND );
			disconnecttime = 0;
			break;
		case IDM_AUTODISCONNECT3:
			CheckMenuRadioItem( GetMenu( hWnd ), IDM_AUTODISCONNECT0, IDM_AUTODISCONNECT20, IDM_AUTODISCONNECT3, MF_BYCOMMAND );
			disconnecttime = 3;
			break;
		case IDM_AUTODISCONNECT4:
			CheckMenuRadioItem( GetMenu( hWnd ), IDM_AUTODISCONNECT0, IDM_AUTODISCONNECT20, IDM_AUTODISCONNECT4, MF_BYCOMMAND );
			disconnecttime = 4;
			break;
		case IDM_AUTODISCONNECT5:
			CheckMenuRadioItem( GetMenu( hWnd ), IDM_AUTODISCONNECT0, IDM_AUTODISCONNECT20, IDM_AUTODISCONNECT5, MF_BYCOMMAND );
			disconnecttime = 5;
			break;
		case IDM_AUTODISCONNECT10:
			CheckMenuRadioItem( GetMenu( hWnd ), IDM_AUTODISCONNECT0, IDM_AUTODISCONNECT20, IDM_AUTODISCONNECT10, MF_BYCOMMAND );
			disconnecttime = 10;
			break;
		case IDM_AUTODISCONNECT15:
			CheckMenuRadioItem( GetMenu( hWnd ), IDM_AUTODISCONNECT0, IDM_AUTODISCONNECT20, IDM_AUTODISCONNECT15, MF_BYCOMMAND );
			disconnecttime = 15;
			break;
		case IDM_AUTODISCONNECT20:
			CheckMenuRadioItem( GetMenu( hWnd ), IDM_AUTODISCONNECT0, IDM_AUTODISCONNECT20, IDM_AUTODISCONNECT20, MF_BYCOMMAND );
			disconnecttime = 20;
			break;

		// Receive a command from SRSlobby
		case (WM_USER + 2):
			switch( lParam )
			{
			case IF_REQ_USER_ENTRY:		// 0x111 User entry
				user_counter++;
				EnableMenuItem( GetMenu( hWnd ), IDM_SETCOMMON, MF_GRAYED );
				EnableMenuItem( GetMenu( hWnd ), IDM_DBGNOTHING, MF_GRAYED );
				EnableMenuItem( GetMenu( hWnd ), IDM_DBGALL, MF_GRAYED );
				EnableMenuItem( GetMenu( hWnd ), IDM_DBGFILE, MF_GRAYED );
				EnableMenuItem( GetMenu( hWnd ), IDM_DGBTRACE, MF_GRAYED );
				break;
			case IF_REQ_USER_DELETE:	// 0x112 User delete
				user_counter--;
				if ( user_counter == 0 )
				{
					EnableMenuItem( GetMenu( hWnd ), IDM_SETCOMMON, MF_ENABLED );
					EnableMenuItem( GetMenu( hWnd ), IDM_DBGNOTHING, MF_ENABLED );
					EnableMenuItem( GetMenu( hWnd ), IDM_DBGALL, MF_ENABLED );
					EnableMenuItem( GetMenu( hWnd ), IDM_DBGFILE, MF_ENABLED );
					EnableMenuItem( GetMenu( hWnd ), IDM_DGBTRACE, MF_ENABLED );
				}
				break;
			default:
				break;
			}
			break;
		case (WM_USER + 3):
			ReadUserFile();
			break;
		case (WM_USER + 4):
			{
				WORD wID = g_wID;
				g_wID = 0xffff;
				return (LRESULT) wID;
			}
		}
		break;
	case WM_TIMER:
		{
			switch( wParam )
			{
			case OPENINGTIMER:
				ShowWindow( hWnd, SW_SHOW );
				KillTimer( hWnd, OPENINGTIMER );
				break;
			case AUTOUPDATETIMER:
				ReadUserFile();
				break;
			default:
				KillTimer( hWnd, (UINT) wParam );
			}
		}
		break;
	case WM_CREATE:
		user_counter = 0;

		// Registry Check
		if ( IsRegistryEntry() )
		{
			MessageBox( hWnd, DIALOGBOXMES1, szClassName, MB_OK | MB_ICONEXCLAMATION );
			SetRegistryDefault();
		}
		{
			int i;
			i = GetDebugInfo();
			if ( SRSLog_IPLoad() == 0 )
			{
				MessageBox( hWnd, DIALOGBOXMES0, szClassName, MB_OK | MB_ICONEXCLAMATION );
				DialogBox( hInst, "ABOUTDLG", hWnd, (DLGPROC) AboutDlgProc );
			}
			// Check a menu item
			CheckMenuRadioItem( GetMenu( hWnd ), IDM_DBGNOTHING, IDM_DGBTRACE, IDM_DBGNOTHING + i, MF_BYCOMMAND );
		}

		frame = GetSystemMetrics( SM_CXSIZEFRAME );

		GetWindowRect( hWnd, &rc );
		x0 = rc.right - rc.left;
		y0 = rc.bottom - rc.top;
		GetClientRect( hWnd, &rc );
		x1 = 130;
		y1 = rc.bottom + frame * 2;
		SetTimer( hWnd, OPENINGTIMER, 1000, NULL );

		InitApp( hInst, ChildProcL, "child_L" );
		hChildL = CreateWindow( "child_L", "", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_THICKFRAME, -frame, -frame, x1, y1, hWnd, (HMENU) 1, hInst, NULL );
		GetClientRect( hWnd, &rc );
		x2 = rc.right - x1 + frame;
		y2 = rc.bottom;
		InitApp( hInst, ChildProcR, "child_R" );
		hChildR = CreateWindow( "child_R", "", WS_CHILD | WS_VISIBLE, x1 - frame, 0, x2, y2, hWnd, (HMENU) 2, hInst, NULL );

		SRSLog_RegLoad();
		CheckMenuRadioItem( GetMenu( hWnd ), IDM_AUTOUPDATE0, IDM_AUTOUPDATE5, IDM_AUTOUPDATE0 + auto_update, MF_BYCOMMAND );
		{
			UINT i;
			switch( disconnecttime )
			{
			case 0:
				i = IDM_AUTODISCONNECT0;
				break;
			case 3:
				i = IDM_AUTODISCONNECT3;
				break;
			case 4:
				i = IDM_AUTODISCONNECT4;
				break;
			case 5:
				i = IDM_AUTODISCONNECT5;
				break;
			case 10:
				i = IDM_AUTODISCONNECT10;
				break;
			case 15:
				i = IDM_AUTODISCONNECT15;
				break;
			case 20:
				i = IDM_AUTODISCONNECT20;
				break;
			default:
				i = IDM_AUTODISCONNECT0;
				break;
			}
			CheckMenuRadioItem( GetMenu( hWnd ), IDM_AUTODISCONNECT0, IDM_AUTODISCONNECT20, i, MF_BYCOMMAND );
		}
		if ( auto_update > 0 )
		{
			SetTimer( hWnd, AUTOUPDATETIMER, 60000 * auto_update, NULL );
		}
		break;

	case WM_SIZE:
		bParentSizeChange = TRUE;
		GetWindowRect( hWnd, &rc );
		x0 = rc.right - rc.left;
		if ( x0 <= x1 ) x1 = x0 - frame;
		y0 = rc.bottom - rc.top;
		GetClientRect( hWnd, &rc );
		y1 = rc.bottom + frame * 2;
		x2 = rc.right - x1 + frame;
		y2 = rc.bottom;

		MoveWindow( hChildL, -frame, -frame, x1, y1, TRUE );
		MoveWindow( hChildR, x1 - frame , 0, x2, y2, TRUE );
		bParentSizeChange = FALSE;
		break;
	case WM_CLOSE:
		SRSLog_RegSave();
		if ( MessageBox( hWnd, DIALOGBOXMES2, szClassName, MB_YESNO | MB_ICONEXCLAMATION ) == IDYES )
		{
			SRSdisconnect( 0, IF_REQ_TERMINATE );
		}
		DestroyWindow( hWnd );
		break;
	case WM_DESTROY:
		PostQuitMessage( 0 );
		break;
	default:
		return( DefWindowProc( hWnd, msg, wParam, lParam ) );
	}
	return 0;
}

LRESULT CALLBACK ChildProcL( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	static int selection = -1;
	RECT rc;
	HWND hParent;

	switch( msg )
	{
	case WM_CREATE:
		InitCommonControls();
		hTree = CreateWindow( WC_TREEVIEW, "", WS_CHILD | WS_BORDER | WS_VISIBLE | TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT, 0, 0, 0, 0, hWnd, (HMENU) ID_MYTREE, hInst, NULL );
		AddItem( hTree );
		break;

	case WM_NOTIFY:
		if ( wParam == ID_MYTREE )
		{
			int i;
			i = TreeViewGetCurSel();
			if ( selection != i )
			{
				selection = i;
				ReadUserFile();
			}
		}
		break;
	case WM_SIZE:
		if ( ! bParentSizeChange )
		{
			hParent = GetParent( hWnd );
			GetWindowRect( hWnd, &rc );
			x1 = rc.right - rc.left;
			y1 = rc.bottom - rc.top;
			GetClientRect( hParent, &rc );
			x2 =  rc.right - x1 + frame;
			y2 = rc.bottom;
			MoveWindow( hChildR, x1 - frame, 0, x2, y2, TRUE );
		}
		MoveWindow( hTree, 0, 0, LOWORD(lParam), HIWORD(lParam), TRUE );
		break;
	default:
		return( DefWindowProc( hWnd, msg, wParam, lParam ) );
	}
	return 0;
}

int GetPastTime( LPSYSTEMTIME lpdesttime )
{
	SYSTEMTIME systime;
	double pvtime1, pvtime2;
	GetLocalTime( &systime );
	SystemTimeToVariantTime( &systime, &pvtime1 );
	SystemTimeToVariantTime( lpdesttime, &pvtime2 );
	return (int) ((pvtime1 - pvtime2) / VARIANT_VALUE);
}

LRESULT CALLBACK ChildProcR( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg )
	{
	case WM_COMMAND:
		switch( wParam )
		{
		case IDC_PROPERTY:
			{
				SRS_USER_ITEM info;
				char str[512];
				int i;

				i = ListView_GetNextItem( hList, -1, LVNI_SELECTED );
				if ( i != -1 )
				{
					ListView_GetItemText( hList, i, 0, str, 512 );
					GetUserStrInfoFromClientName( str, &info );
					i = GetPastTime( &info.USI_time );
					sprintf( str,	"CLIENT=\"%s\"\n"
									"USERNAME=\"%s\"\n"
									"IP= %d.%d.%d.%d\n"
									"PORT= %d\n"
									"User ID= %d\n"
									"Game ID= %d\n"
									"Lobby ID= %d\n"
									"Group ID= %d\n"
									"Time = %d:%02d\n",
									info.USI_cClientName, info.USI_cUserName,
									info.USI_iIp & 0xff, (info.USI_iIp >> 8) & 0xff, (info.USI_iIp >> 16) & 0xff, (info.USI_iIp >> 24) & 0xff,
									info.USI_iPort, info.USI_wUserID, info.USI_wGameID, info.USI_wLobbyID, info.USI_wGroupID,
									i / 60, i % 60
							);
					MessageBox( hWnd, str, szClassName, MB_OK );
				}
			}
			break;
		case IDC_DELETE:
			{
				SRS_USER_ITEM info;
				char str[512];
				int i;

				i = ListView_GetNextItem( hList, -1, LVNI_SELECTED );
				if ( i != -1 )
				{
					ListView_GetItemText( hList, i, 0, str, 512 );
					GetUserStrInfoFromClientName( str, &info );
					g_wID = info.USI_wUserID;
					if ( SRSdisconnect( info.USI_iPort ) != 0 ){}
				}
			}
			break;
		}
		break;
	case WM_TIMER:
		{
			SRS_USER_ITEM info;
			int i, j;
			switch( wParam )
			{
			case AUTODISCONNECT:
				for( i = 1; i < 4096; i++ )
				{
					if ( GetUserStrInfo( i, &info ) == FALSE ) break;
					j = GetPastTime( &info.USI_time );
					// Auto disconnect
					if ( disconnecttime > 0 )
					{
						if ( j >= 60 * disconnecttime )
						{
							if ( info.USI_iIp && info.USI_wUserID > 0 && info.USI_iPort > 0 )
							{
//								char str[260];
								g_wID = info.USI_wUserID;
//								sprintf( str, "%d - %d", g_wID, info.USI_iPort );
								if ( SRSdisconnect( (info.USI_iPort) ) != 0 )
								{
//									MessageBox( NULL, "切断失敗", str, MB_OK );
								}
//								else
//								{
//									MessageBox( NULL, "成功", str, MB_OK );
//								}
//								sprintf( str, "No.%d\nClient=%s\nUser=%s\nIP=%08X\nPort=%d", info.USI_wUserID, info.USI_cClientName, info.USI_cUserName, info.USI_iIp, info.USI_iPort );
//								MessageBox( NULL, str, "", MB_OK );
							}
						}
					}
				}
				break;
			default:
				KillTimer( hWnd, (UINT) wParam );
			}
		}
		break;
	case WM_CONTEXTMENU:
		{
			LV_HITTESTINFO hi;
			HMENU hMenu, hSubMenu;
			hi.pt.x = LOWORD( lParam );
			hi.pt.y = HIWORD( lParam );
			ScreenToClient( hList, &hi.pt );
			if ( ListView_HitTest( hList, &hi ) > -1 )
			{
				hMenu = LoadMenu( hInst, "SRSLOGPOPUP" );
				hSubMenu = GetSubMenu( hMenu, 0 );
				TrackPopupMenu( hSubMenu, TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON, LOWORD( lParam ), HIWORD( lParam ), 0, hWnd, NULL );
				DestroyMenu( hMenu );
			}
		}
		return TRUE;
	case WM_CLOSE:
		KillTimer( hWnd, AUTODISCONNECT );
		break;
	case WM_CREATE:
		InitCommonControls();
		hList = CreateWindow( WC_LISTVIEW, "", WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SINGLESEL, 0, 0, 0, 0, hWnd, (HMENU) ID_MYLIST, hInst, NULL );
		InsColumn( "Client name", 100, 0 );
		InsColumn( "User name", 100, 1 );
		InsColumn( "IP Address", 90, 2 );
		InsColumn( "Port", 40, 3 );
		InsColumn( "Last Access time", 116, 4 );
		InsColumn( "Status", 60, 5 );
		SetTimer( hWnd, AUTODISCONNECT, 60000, NULL );
		break;
	case WM_SIZE:
		MoveWindow( hList, 0, 0, LOWORD(lParam), HIWORD(lParam), TRUE );
		break;
	default:
		return( DefWindowProc( hWnd, msg, wParam, lParam ) );
	}
	return 0;
}

void AddItem( HWND hTree )
{
	HTREEITEM hGame;
	TV_INSERTSTRUCT tv;
	int i, lobby;
	ENTRYINFO entryinfo;

	memset( (char *) &tv, '\0', sizeof(tv) );

	tv.hInsertAfter = TVI_LAST;
	tv.item.mask = TVIF_TEXT;
	tv.hParent = TVI_ROOT;

	// use game1 only
	GetGameInfo( 1, &entryinfo );
	if ( strlen( entryinfo.name ) == 0 )
	{
		strcpy( entryinfo.name, "Game Title" );
	}

	tv.item.pszText = entryinfo.name;
	hGame = TreeView_InsertItem( hTree, &tv );

	lobby = GetMaxLobbyNum();
	for( i = 1; i <= lobby; i++ )
	{
		GetLobbyInfo( i, &entryinfo );
		if ( strlen( entryinfo.name ) == 0 )
		{
			sprintf( entryinfo.name, "lobby%02d", i );
		}
		tv.hParent = hGame;
		tv.item.pszText = entryinfo.name;
		TreeView_InsertItem( hTree, &tv );
	}
}

void DeleteAllItem( HWND hTree )
{
	TreeView_DeleteAllItems( hTree );
}

void InsColumn( char *str, int cx, int iSub )
{
	LV_COLUMN col;
	col.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	col.fmt = LVCFMT_LEFT;
	col.cx = cx;
	col.pszText = str;
	col.iSubItem = iSub;
	ListView_InsertColumn( hList, iSub, &col );
}

void InsertList( char *str1, char *str2, char *str3, char *str4, char *str5, char *str6 )
{
	LV_ITEM item;
	int num;

	num = ListView_GetItemCount( hList );
	item.mask = LVIF_TEXT;
	item.pszText = str1;
	item.iItem = num;
	item.iSubItem = 0;
	ListView_InsertItem( hList, &item );
	item.pszText = str2;
	item.iSubItem = 1;
	ListView_SetItem( hList, &item );
	item.pszText = str3;
	item.iSubItem = 2;
	ListView_SetItem( hList, &item );
	item.pszText = str4;
	item.iSubItem = 3;
	ListView_SetItem( hList, &item );
	item.pszText = str5;
	item.iSubItem = 4;
	ListView_SetItem( hList, &item );
	item.pszText = str6;
	item.iSubItem = 5;
	ListView_SetItem( hList, &item );
}

BOOL DeleteList( char *username )
{
	char str[MAX_PATH];
	int i, num;
	BOOL retVal;

	retVal = FALSE;
	num = ListView_GetItemCount( hList );
	for( i = 0; i < num; i++ )
	{
		str[0] = '\0';
		ListView_GetItemText( hList, i, 0, str, MAX_PATH );
		if ( strlen( str ) )
		{
			if ( ! strcmp( username, str ) )
			{
				ListView_DeleteItem( hList, i );
				retVal = TRUE;
				break;
			}
		}
	}
	return retVal;
}

BOOL DeleteAllList()
{
	return ListView_DeleteAllItems( hList );
}

int TreeViewGetCurSel()
{
    HTREEITEM hItem;
	int sel;

	hItem = TreeView_GetSelection( hTree );
	if ( hItem )
	{
	    HTREEITEM hItemParent;
		hItemParent = TreeView_GetParent( hTree, hItem );
		if ( hItemParent )
		{
			sel = 0;
			while( 1 )
			{
				sel++;
				hItem = TreeView_GetPrevSibling( hTree, hItem );
				if ( ! hItem ) break;
			}
		}
		else
		{
			sel = 0;
		}
	}
	else
	{
		sel = -1;
	}
	return sel;
}

BOOL ReadUserFile()
{
	DeleteAllList();
	int		i, sel;
	BOOL	fRtn;
	DWORD	dwRtn;
	DWORD	dwReadByte;
	HANDLE	hHandle;
	SRS_USER_ITEM *user_info;
	char cMsg[200];

	user_info = new SRS_USER_ITEM[4096];
	ZeroMemory( user_info, SRS_USER_ITEM_SZ4096 );
	i = 50;
	while( i-- )
	{
		hHandle = CreateFile( SRS_PATH_USER, GENERIC_READ, 0, (LPSECURITY_ATTRIBUTES) NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, (HANDLE) NULL );
		if ( hHandle != INVALID_HANDLE_VALUE )
		{
			break;
		}
		Sleep( 100 );
	}
	if ( i <= 0 )
	{
		// Time out...
		goto RETFALSE;
	}

	// Read User-items from the file.
	fRtn = 0;
	SetFilePointer( hHandle, SKIP176, NULL, FILE_BEGIN );
	fRtn = ReadFile( hHandle, user_info, SRS_USER_ITEM_SZ4096, &dwReadByte, NULL );
	if ( fRtn == FALSE )
	{
		dwRtn = GetLastError();
		sprintf( cMsg, "ReadFile error %d %s", dwRtn, SRS_PATH_USER );
		MessageBox( NULL, cMsg, "error", MB_OK );
		CloseHandle( hHandle );
RETFALSE:
		delete user_info;
		return FALSE;
	}
	fRtn = CloseHandle( hHandle );

	sel = TreeViewGetCurSel();
	if ( sel > 0 )
	{
		sel--;
		for( i = 0; i < 4096; i++ )
		{
			char client_str[SRS_MAX_NAME_CLIENT + 1];
			char user_str[SRS_MAX_NAME_USER + 1];
			char ip_str[32];
			char port_str[32];
			char time_str[32];
			char status_str[32];
			ZeroMemory( client_str, SRS_MAX_NAME_CLIENT + 1 );
			ZeroMemory( user_str, SRS_MAX_NAME_USER + 1 );
			strncpy( client_str, user_info[i].USI_cClientName, SRS_MAX_NAME_CLIENT );
			strncpy( user_str, user_info[i].USI_cUserName, SRS_MAX_NAME_USER );
			sprintf( ip_str, "%u.%u.%u.%u", user_info[i].USI_iIp & 0xff, (user_info[i].USI_iIp >> 8) & 0xff, (user_info[i].USI_iIp >> 16) & 0xff, (user_info[i].USI_iIp >> 24) & 0xff );
			sprintf( port_str, "%4d", user_info[i].USI_iPort );
			sprintf( time_str, "%4d/%2d/%2d %2d:%02d:%02d", user_info[i].USI_time.wYear, user_info[i].USI_time.wMonth, user_info[i].USI_time.wDay, user_info[i].USI_time.wHour, user_info[i].USI_time.wMinute, user_info[i].USI_time.wSecond );
			switch( user_info[i].USI_dwCondetion )
			{
			case FORCC(0x0100):
				sprintf( status_str, "Lobby" );
				break;
			case FORCC(0x0201):
				sprintf( status_str, "Host" );
				break;
			case FORCC(0x0202):
				sprintf( status_str, "Group" );
				break;
			case FORCC(0x0300):
				sprintf( status_str, "Game" );
				break;
			default:
				continue;
			}
			if ( user_info[i].USI_wLobbyID == (WORD) sel )
			{
				InsertList( client_str, user_str, ip_str, port_str, time_str, status_str );
			}
		}
	}
	delete user_info;
	return TRUE;
}

BOOL GetUserStrInfoFromClientName( char *cmpstr, SRS_USER_ITEM *info )
{
	SRS_USER_ITEM user_info;
	char cMsg[200];
	HANDLE hHandle;
	int i;
	BOOL fRtn, retVal;
	DWORD dwReadByte;

	ZeroMemory( info, SRS_USER_ITEM_SZ );
	ZeroMemory( &user_info, SRS_USER_ITEM_SZ );

	retVal = FALSE;
	fRtn = 0;
	i = 50;
	while( i-- )
	{
		hHandle = CreateFile( SRS_PATH_USER, GENERIC_READ, 0, (LPSECURITY_ATTRIBUTES) NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, (HANDLE) NULL );
		if ( hHandle != INVALID_HANDLE_VALUE ) break;
		Sleep( 100 );
	}
	if ( i > 0 )
	{
		SetFilePointer( hHandle, SKIP176, NULL, FILE_BEGIN );
		for( i = 0; i < 4096; i++ )
		{
			fRtn = ReadFile( hHandle, &user_info, SRS_USER_ITEM_SZ, &dwReadByte, NULL );
			if ( dwReadByte < SRS_USER_ITEM_SZ ) goto RETFALSE;
			if ( fRtn == FALSE )
			{
				UINT dwRtn;
				dwRtn = GetLastError();
				sprintf( cMsg, "ReadFile error %d %s", dwRtn, SRS_PATH_USER );
				MessageBox( NULL, cMsg, "error", MB_OK );
RETFALSE:
				CloseHandle( hHandle );
				break;
			}
			if ( strncmp( user_info.USI_cClientName, cmpstr, SRS_MAX_NAME_CLIENT ) == 0 )
			{
				memcpy( info, &user_info, SRS_USER_ITEM_SZ );
				retVal = TRUE;
				break;
			}
		}
		fRtn = CloseHandle( hHandle );
	}
	return retVal;
}

BOOL GetUserStrInfo( int user, SRS_USER_ITEM *info )
{
	SRS_USER_ITEM user_info;
	char cMsg[200];
	HANDLE hHandle;
	int i;
	BOOL fRtn, retVal;
	DWORD dwReadByte;

	ZeroMemory( info, SRS_USER_ITEM_SZ );
	ZeroMemory( &user_info, SRS_USER_ITEM_SZ );

	retVal = FALSE;
	fRtn = 0;
	i = 50;
	while( i-- )
	{
		hHandle = CreateFile( SRS_PATH_USER, GENERIC_READ, 0, (LPSECURITY_ATTRIBUTES) NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, (HANDLE) NULL );
		if ( hHandle != INVALID_HANDLE_VALUE ) break;
		Sleep( 100 );
	}
	if ( i > 0 )
	{
		if ( SetFilePointer( hHandle, (user - 1) * SRS_USER_ITEM_SZ + SKIP176, NULL, FILE_BEGIN ) != 0xffffffff )
		{
			fRtn = ReadFile( hHandle, &user_info, SRS_USER_ITEM_SZ, &dwReadByte, NULL );
			if ( fRtn == FALSE )
			{
				UINT dwRtn;
				dwRtn = GetLastError();
				sprintf( cMsg, "ReadFile error %d %s", dwRtn, SRS_PATH_USER );
				MessageBox( NULL, cMsg, "error", MB_OK );
			}
			else if ( dwReadByte == SRS_USER_ITEM_SZ )
			{
				memcpy( info, &user_info, SRS_USER_ITEM_SZ );
				retVal = TRUE;
			}
		}
		fRtn = CloseHandle( hHandle );
	}
	return retVal;
}
