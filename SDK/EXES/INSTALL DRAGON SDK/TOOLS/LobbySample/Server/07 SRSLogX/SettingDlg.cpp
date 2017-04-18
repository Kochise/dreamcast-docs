/***************************************************************************
 *
 *  Copyright (C) 2000 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       SettingDlg.cpp
 *  Content:    Setting Dialog class for SRSlog
 *
 ***************************************************************************/
#include <stdio.h>
#include "SettingDlg.h"
#include "Registry.h"

// dialog box message
#define DIALOGBOXTITLE		"SRSlog"
#define DIALOGBOXMES0		"Please customize lobby server for each game title.\n"
#define DIALOGBOXMES1		"標準設定に戻してよろしいですか？"
#define DIALOGBOXMES2		"設定の変更をレジストリに反映しますか？"
#define DIALOGBOXMES3		"　レジストリに変更を加えました。設定をサーバーアプリケーション全体に反映するため\n"			\
							"SRSstopでサーバーアプリケーションをいったん終了しSRSinitialを再起動してください。\n"			\
							"ここで再起動されない場合、サーバーアプリケーションの動作保証はしません。"
#define DIALOGBOXMES4		"　クライアントが１人でも登録されている間は設定を変更できません。\n"							\
							"この処理を続けますか？"

// SRS user,lobby,group,game min/max number
#define RANGEUSERMIN	1
#define RANGEUSERMAX	64
#define RANGELOBBYMIN	1
#define RANGELOBBYMAX	64
#define RANGEGROUPMIN	1
#define RANGEGROUPMAX	4
#define RANGEGAMEMIN	1
#define RANGEGAMEMAX	1

// default value
#define DEFAULTUSER		8
#define DEFAULTLOBBY	8
#define DEFAULTGROUP	4
#define DEFAULTGAME		1
#define DEFAULTPORT		1002

// user window message
#define WM_UPDATE			WM_USER+16
#define WM_DEFAULTSETTINGS	WM_USER+17
#define WM_WRITEREGISTRY	WM_USER+18

extern int user_counter;

// global
MAXNUM maxnum;
int portnumber;
BOOL applysettings;

/*------------------------------------------------------------------------------

	Main proc

------------------------------------------------------------------------------*/
LRESULT CALLBACK SettingDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg )
	{
	case WM_COMMAND:
		switch( LOWORD(wParam) )
		{
		case IDOK:
			{
				int retVal;
				if ( user_counter > 0 )
				{
					if ( MessageBox( hDlg, DIALOGBOXMES4, DIALOGBOXTITLE, MB_YESNO ) == IDNO )
					{
						EndDialog( hDlg, IDNO );
					}
				}
				retVal = MessageBox( hDlg, DIALOGBOXMES2, DIALOGBOXTITLE, MB_YESNOCANCEL );
				if ( retVal == IDYES )
				{
					SendMessage( hDlg, WM_WRITEREGISTRY, 0, 0 );
					MessageBox( hDlg, DIALOGBOXMES3, DIALOGBOXTITLE, MB_OK | MB_ICONEXCLAMATION );
					EndDialog( hDlg, IDOK );
				}
				if ( retVal == IDNO )
				{
					EndDialog( hDlg, IDNO );
				}
			}
			break;
		case IDCANCEL:
			EndDialog( hDlg, IDCANCEL );
			break;
		case IDC_DEFAULTSETTING:
			if ( MessageBox( hDlg, DIALOGBOXMES1, DIALOGBOXTITLE, MB_YESNO ) == IDYES )
			{
				SendMessage( hDlg, WM_DEFAULTSETTINGS, 0, 0 );
			}
			break;
		default:
			return FALSE;
		}
		break;
	case WM_INITDIALOG:
		{
			ENTRYINFO gameinfo;
			maxnum.user = GetMaxUserNum();
			maxnum.lobby = GetMaxLobbyNum();
			maxnum.group = GetMaxGroupNum();
			maxnum.game = GetMaxGameNum();
			portnumber = GetPortNum();
			applysettings = GetSendMode();
			GetGameInfo( 1, &gameinfo );
			SetDlgItemText( hDlg, IDC_GAMETITLE, gameinfo.name );
			SetDlgItemText( hDlg, IDC_ATTENTION, DIALOGBOXMES0 );
			SendMessage( hDlg, WM_UPDATE, 0, 0 );
		}
		return FALSE;
	case WM_HSCROLL:
		{
			int i;
			i = SendMessage( (HWND) lParam, TBM_GETPOS, 0, 0 );
			if ( (HWND) lParam == GetDlgItem( hDlg, IDC_MAXUSER_SLIDER ) )
			{
				SetDlgItemInt( hDlg, IDC_MAXUSER_EDIT, i, TRUE );
			}
			else if ( (HWND) lParam == GetDlgItem( hDlg, IDC_MAXLOBBY_SLIDER ) )
			{
				SetDlgItemInt( hDlg, IDC_MAXLOBBY_EDIT, i, TRUE );
			}
			else if ( (HWND) lParam == GetDlgItem( hDlg, IDC_MAXGROUP_SLIDER ) )
			{
				SetDlgItemInt( hDlg, IDC_MAXGROUP_EDIT, i, TRUE );
			}
			else if ( (HWND) lParam == GetDlgItem( hDlg, IDC_MAXGAME_SLIDER ) )
			{
				SetDlgItemInt( hDlg, IDC_MAXGAME_EDIT, i, TRUE );
			}
			break;
		}
		break;
	case WM_DEFAULTSETTINGS:
		maxnum.user = DEFAULTUSER;
		maxnum.lobby = DEFAULTLOBBY;
		maxnum.group = DEFAULTGROUP;
		maxnum.game = DEFAULTGAME;
		portnumber = DEFAULTPORT;
		applysettings = FALSE;
		SendMessage( hDlg, WM_UPDATE, 0, 0 );
		break;
	case WM_UPDATE:
		SendMessage( GetDlgItem( hDlg, IDC_MAXUSER_SLIDER ), TBM_SETRANGE, TRUE, MAKELONG( RANGEUSERMIN, RANGEUSERMAX ) );
		SendMessage( GetDlgItem( hDlg, IDC_MAXLOBBY_SLIDER ), TBM_SETRANGE, TRUE, MAKELONG( RANGELOBBYMIN, RANGELOBBYMAX ) );
		SendMessage( GetDlgItem( hDlg, IDC_MAXGROUP_SLIDER ), TBM_SETRANGE, TRUE, MAKELONG( RANGEGROUPMIN, RANGEGROUPMAX ) );
		SendMessage( GetDlgItem( hDlg, IDC_MAXGAME_SLIDER ), TBM_SETRANGE, TRUE, MAKELONG( RANGEGAMEMIN, RANGEGAMEMAX ) );
		SendMessage( GetDlgItem( hDlg, IDC_MAXUSER_SLIDER ), TBM_SETPOS, TRUE, maxnum.user );
		SendMessage( GetDlgItem( hDlg, IDC_MAXLOBBY_SLIDER ), TBM_SETPOS, TRUE, maxnum.lobby );
		SendMessage( GetDlgItem( hDlg, IDC_MAXGROUP_SLIDER ), TBM_SETPOS, TRUE, maxnum.group );
		SendMessage( GetDlgItem( hDlg, IDC_MAXGAME_SLIDER ), TBM_SETPOS, TRUE, maxnum.game );

		if ( maxnum.user < RANGEUSERMIN ) maxnum.user = RANGEUSERMIN;
		else if ( maxnum.user > RANGEUSERMAX ) maxnum.user = RANGEUSERMAX;
		if ( maxnum.lobby < RANGELOBBYMIN ) maxnum.lobby = RANGELOBBYMIN;
		else if ( maxnum.lobby > RANGELOBBYMAX ) maxnum.lobby = RANGELOBBYMAX;
		if ( maxnum.group < RANGEGROUPMIN ) maxnum.group = RANGEGROUPMIN;
		else if ( maxnum.group > RANGEGROUPMAX ) maxnum.group = RANGEGROUPMAX;
		if ( maxnum.game < RANGEGAMEMIN ) maxnum.game = RANGEGAMEMIN;
		else if ( maxnum.game > RANGEGAMEMAX ) maxnum.game = RANGEGAMEMAX;

		if ( applysettings ) CheckDlgButton( hDlg, IDC_APPLYSETTINGS, BST_CHECKED );

		SetDlgItemInt( hDlg, IDC_MAXUSER_EDIT, maxnum.user, TRUE );
		SetDlgItemInt( hDlg, IDC_MAXLOBBY_EDIT, maxnum.lobby, TRUE );
		SetDlgItemInt( hDlg, IDC_MAXGROUP_EDIT, maxnum.group, TRUE );
		SetDlgItemInt( hDlg, IDC_MAXGAME_EDIT, maxnum.game, TRUE );
		SetDlgItemInt( hDlg, IDC_PORTNUM, portnumber, TRUE );
		break;
	case WM_WRITEREGISTRY:
		{
			char str[MAX_PATH];
			int i, lobby, game;
			ENTRYINFO entryinfo;

			SetPortNum( (int) GetDlgItemInt( hDlg, IDC_PORTNUM, NULL, TRUE ) );
			SetMaxUserNum( (int) GetDlgItemInt( hDlg, IDC_MAXUSER_EDIT, NULL, TRUE ) );
			SetMaxLobbyNum( lobby = (int) GetDlgItemInt( hDlg, IDC_MAXLOBBY_EDIT, NULL, TRUE ) );
			SetMaxGroupNum( (int) GetDlgItemInt( hDlg, IDC_MAXGROUP_EDIT, NULL, TRUE ) );
			SetMaxGameNum( game = (int) GetDlgItemInt( hDlg, IDC_MAXGAME_EDIT, NULL, TRUE ) );
			SetSendMode( (int) IsDlgButtonChecked( hDlg, IDC_APPLYSETTINGS ) );
			entryinfo.max_entry = game;
			GetDlgItemText( hDlg, IDC_GAMETITLE, entryinfo.name, MAX_PATH );
			for( i = 1; i <= 1; i++ )
			{
				SetGameInfo( i, &entryinfo );
			}
			for( i = 1; i <= lobby; i++ )
			{
				entryinfo.max_entry = lobby;
				sprintf( str, "lobby%02d", i );
				strcpy( entryinfo.name, str );
				SetLobbyInfo( i, &entryinfo );
			}
		}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}
