/***************************************************************************
 *
 *  Copyright (C) 1999 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       SRSlobby.cpp
 *					SRS_Lby_GetPort			(空きポート獲得)
 *
 *  Content:    Lobby Server  Lobbyクライアント要求処理プロセス
 *
 ***************************************************************************/
/*================================
    インクルード
==================================*/
#include <windows.h>
#include <stdio.h>

#include "SRScom.h"
#include "SRSdebug.h"
#include "SRSmanage.h"
#include "SRSlobby.h"
#include "SRSnetwork.h"

BOOL InitInstance( HINSTANCE hInst, int nCmdShow )
{
	HWND hWnd;

	hWnd = CreateWindow( "SRSlobby", "SRSlobby", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, NULL, NULL, hInst, NULL );
	if ( ! hWnd ) return FALSE;
	ShowWindow( hWnd, nCmdShow );
	UpdateWindow( hWnd );
	return TRUE;
}

BOOL InitApp( HINSTANCE hInst, WNDPROC fnWndProc, LPCTSTR szClassNm )
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = fnWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = NULL;
	wc.hCursor = NULL;
	wc.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "SRSlobby";
	wc.hIconSm = wc.hIcon;
	return ( RegisterClassEx( &wc ) );
}

//ウィンドウプロシージャ
LRESULT CALLBACK WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg )
	{
	case WM_CREATE:
		break;
	case WM_CLOSE:
		DestroyWindow( hWnd );
		break;
	case WM_DESTROY:
		break;
	default:
		return( DefWindowProc( hWnd, msg, wParam, lParam ) );
	}
	return 0;
}

/*=============================================================================
     関数   ：Lobbyプロセス初期化 ＆ クライアント要求待ちプロセス
			（Lobbyプロセス初期設定と Lobbyクライアント要求の処理をおこなう）
     入力   ：なし
     出力   ：なし
     戻り値 ：正常 0
              異常 -1

==============================================================================*/
int WINAPI WinMain( HINSTANCE hInstanc,HINSTANCE hPrevInstanc,
					LPSTR lpszCmdLin,int nCmdSho )
{
	int		iRtn;								//
	int		iNameLen;							// 
	int		iPort;								// 要求待ち合わせポート番号
	int		iNo;								// 
	int		iRcvSize;							// 受信データ長
	size_t	szSize;								//
	struct	SRS_IF_FIX *lpIfFix;				// インタフェース域ポインタ
	LPTSTR	lpProcName;							// プロセス名ポインタ
	char	*lpRcvBuff;							// 受信バッファ域ポインタ
	char	cProcName[256];						// プロセス名域
	char	cMsg[256];
	HWND hEvent;
	hEvent = FindWindow( "SRSLogV2", "SRSlog" );

//	if ( ! InitApp( hInstanc, WndProc, "SRSlobby" ) ) return FALSE;
//	if ( ! InitInstance( hInstanc, nCmdSho ) ) return FALSE;

	//========================================
	// ポート番号獲得
	//========================================
	memset( cProcName, 0, 256 );				//
	lpProcName = GetCommandLine();				// コマンドライン獲得
	sprintf( cProcName, "%s",lpProcName );		//
	iNameLen = strlen( SRS_PROC_LOBBY );		// 基本名長獲得

	//
	// 番号変換（４桁キャラクタ→バイナリ数値）
	//
	iNo = (int)(cProcName[iNameLen] & 0x0f);	// ４桁目
	iPort = iNo * 1000;							// 
	iNo = (int)(cProcName[iNameLen+1] & 0x0f);	// ３桁目
	iPort = iPort + (iNo * 100);				// 
	iNo = (int)(cProcName[iNameLen+2] & 0x0f);	// ２桁目
	iPort = iPort + (iNo * 10);					// 
	iNo = (int)(cProcName[iNameLen+3] & 0x0f);	// １桁目
	iPort = iPort + iNo;						// 

	//======================================== 
	// Lobbyサーバ環境設定
	//========================================
	//
	//  管理情報環境設定
	//
	iRtn = SRS_Mng_GetInfo( SRS_INFO_GET );		// 管理情報取り込み
	if( iRtn != 0 )								// 取り込み失敗？
	{
		sprintf( cMsg, "SRS_Lby_Main : SRS_Mng_GetInfo error" );
		SRS_Dbg_WriteLog( cMsg );				
		return( -1 );
	}
	//
	//  ネットワーク環境設定
	//
	lpRcvBuff = (char *)malloc( SRS_MAX_RCV );	// 受信バッファ獲得
	if( lpRcvBuff == NULL )
	{
		sprintf( cMsg, "SRS_Lby_main : malloc error" );
		SRS_Dbg_WriteLog( cMsg );				
		SRS_Lby_Term( iPort );					// ロビー資源回収
		return( -1 );
	}
	memset( lpRcvBuff, 0, SRS_MAX_RCV );

	iRtn = SRS_Net_Open( iPort );				// コネクション準備
	if( iRtn == -1 )							// 通信異常？
	{
		SRS_Lby_Term( iPort );					// ロビー資源回収
		return( -1 );
	}
	//========================================
	// 要求待ち
	//========================================
	for( ; ; )
	{
		szSize = SRS_MAX_RCV;
		iRcvSize = SRS_Net_RcvReq( (char *)lpRcvBuff, szSize  );	// クライアント要求待ち
		if( iRcvSize == -1 )											// 通信異常？
		{	
			iRtn = SRS_Net_Close( );									// コネクション解放
			sprintf( cMsg, "SRS_Lby_Main : SRS_Net_Receive error" );
			SRS_Dbg_WriteLog( cMsg );				
			SRS_Lby_Term( iPort );										// ロビー資源回収
			return( -1 );				
		}
		//=======================================
		//  受信要求判定
		//=======================================

		lpIfFix = (struct SRS_IF_FIX *)lpRcvBuff;

		// リクエストをSRSLogに送る
		SendMessage( hEvent, WM_COMMAND, (WPARAM)WM_USER+2, (LPARAM)lpIfFix->IF_wRequest );

		switch( lpIfFix->IF_wRequest )
		{
			case	IF_REQ_ALL			: 	// 全情報参照
						iRtn = SRS_Lby_ReqAll( lpIfFix );
						break;

			case	IF_REQ_USER_ENTRY	:	// ユーザ登録
						iRtn = SRS_Lby_ReqUserEntry( lpIfFix );
						break;

			case	IF_REQ_USER_DELETE	:	// ユーザ削除
						iRtn = SRS_Lby_ReqUserDelete( lpIfFix );
						break;

			case	IF_REQ_LOBBY_ENTRY	:	// ロビーユーザ参加
						iRtn = SRS_Lby_ReqLobbyEntry( lpIfFix );
						break;

			case	IF_REQ_LOBBY_DEFECT	:	// ロビーユーザ脱退
						iRtn = SRS_Lby_ReqLobbyDefect( lpIfFix );
						break;

			case	IF_REQ_GROUP_MAKE	:	// グループ作成
						iRtn = SRS_Lby_ReqGroupMake( lpIfFix );
						break;

			case	IF_REQ_GROUP_JOIN	:	// グループ参加
						iRtn = SRS_Lby_ReqGroupJoin( lpIfFix );
						break;

			case	IF_REQ_GROUP_DEFECT	:	// グループ脱退
						iRtn = SRS_Lby_ReqGroupDefect( lpIfFix );
						break;

			case	IF_REQ_GAME_JOIN	:	// ゲーム参加
						iRtn = SRS_Lby_ReqGameJoin( lpIfFix );
						break;

			case	IF_REQ_GAME_DEFECT	:	// ゲーム脱退
						iRtn = SRS_Lby_ReqGameDefect( lpIfFix );
						break;

			case	IF_REQ_GAME_START	:	// ゲーム開始
						iRtn = SRS_Lby_ReqGameStart( lpIfFix );
						break;

			case	IF_REQ_GAME_END		:	// ゲーム終了
						iRtn = SRS_Lby_ReqGameEnd( lpIfFix );
						break;

			case	IF_REQ_SENDMSG		:	// メッセージ送信
						iRtn = SRS_Lby_ReqSendMsg( lpIfFix );
						break;

			case	IF_REQ_SAVE_INFO	:	// 固有情報待避
						iRtn = SRS_Lby_ReqSaveInfo( lpIfFix );
						break;

			case	IF_REQ_TERMINATE	:	// 終了通知
				{

//					char str[260];
//						WORD wID = SRS_Mng_GetUserByIP( lpIfFix->IF_iIp );
//						*((LPWORD) (lpIfFix->IF_cInformation)) = wID;
//						sprintf( str, "%d - %08x", wID, lpIfFix->IF_iIp );
//						MessageBox( NULL, str, "", MB_OK );
//						*((LPWORD) (lpIfFix->IF_cInformation)) = 1;
						*((LPWORD) (lpIfFix->IF_cInformation)) = (WORD) SendMessage( hEvent, WM_COMMAND, (WPARAM)WM_USER+4, 0 );

//						lpIfFix->IF_wRequest = IF_REQ_USER_DELETE;
						sprintf( cMsg, "SRSlobby : 終了前処理 IP=%08x", lpIfFix->IF_iIp );
						SRS_Dbg_WriteLog( cMsg );

						SRS_Lby_ReqUserDeleteEX( lpIfFix );
						iRtn = SRS_Net_Close( );
						SRS_Dbg_WriteLog( "SRSlobby : 終了通知" );
						SendMessage( hEvent, WM_COMMAND, (WPARAM)WM_USER+3, 0 );
						ExitProcess( 0 );
				}
			default						:   // システムエラー
						iRtn = SRS_Lby_ReqSeqError( lpIfFix );	 // 要求シーケンスエラー
						SRS_Dbg_WriteLog( "SRSlobby : システムエラー " );
						break;
		}

		// 千葉が追加
		{
			WORD wID;

			wID = SRS_Mng_GetUserByIP( lpIfFix->IF_iIp );
			if ( wID != SRS_WORD_ERROR )
			{
				SRS_Mng_PutPort( iPort, wID );
				SRS_Mng_PutInfo( wID );
			}

			// SRSLogの表示をアップデートする
			if ( lpIfFix->IF_wRequest == IF_REQ_USER_ENTRY || lpIfFix->IF_wRequest == IF_REQ_USER_DELETE )
				SendMessage( hEvent, WM_COMMAND, (WPARAM)WM_USER+3, 0 );
		}

		//
		//  通信異常判定
		//
		if( iRtn != 0 )				// 通信異常発生？
		{
			SRS_Lby_Term( iPort );	// ロビー資源回収
			break;
		}
	}
	//========================================
	// 対クライアント通信環境回収
	//========================================
	iRtn = SRS_Net_Close( );
	return( 0 );
}

/*=============================================================================
     関数    ：解放要求代行
			  （Lobbyクライアントに代わりに解放要求を発行する）
     入力    ：iPort  (クライアント通知ポート番号)
     出力    ：なし
     戻り値  ：なし

==============================================================================*/
void SRS_Lby_Term( int iPort )
{
	struct	SRS_IF_FIX	*lpIfFix;		//
	char 	cIfFix[256];				//
	char	cMsg[256];

	// socket用
	SOCKET	ServerSd;								//
	int 	iResult;								//
	int 	iSendLen;								// 送信データ長
	int 	iSendData;								// 送信データ長（カウント用）
	WORD    wVersionRequested = MAKEWORD(1, 1);		// Winsock 1.1 を要求
	WSADATA wsaData;								// Winsock の詳細
	SOCKADDR_IN   ClientAddr;						//クライアント側のアドレス構造体
	SOCKADDR_IN   ServerAddr;						//サーバ側のアドレス構造体
	u_long ulCmdArg = 1;							//ブロッキングモード
    PHOSTENT lphostent; 							//ホスト情報の構造体ポインタ
	char	cServerName[32];						//
	char	cDummyBuff[16];							//
	DWORD	dwSize;									//

	if( 0 == 0 )
		return;
	//========================================
	//  コネクション確立
	//========================================
	// select用変数   
	struct fd_set *lpReadFds = new struct fd_set;		//ｿｹｯﾄﾃﾞｽｸﾌﾟﾘﾀ集合
	struct timeval *lpSockTime = new struct timeval;	//タイマ構造体
	struct timeval *lpConnectTime = new struct timeval;	//select用タイマ構造体
	struct fd_set *lpWriteFds = new struct fd_set;		//ｿｹｯﾄﾃﾞｽｸﾌﾟﾘﾀの集合（書き込み状態参照）

	/*==================================*/
	/* ソケット初期化                   */
	/*==================================*/
	iResult = WSAStartup( wVersionRequested, &wsaData );
	if ( iResult != 0 )
	{
		iResult = WSAGetLastError();
		sprintf( cMsg, "SRS_Lby_Term : WSAStartup error:%d", iResult );
		SRS_Dbg_WriteLog( cMsg );
		return;
	}

	ServerSd = socket( AF_INET, SOCK_STREAM, 0 );	//サーバ送信用ソケット作成

	/*==================================*/
	/* セッション確立 		 			*/
	/*==================================*/
	// アドレス構造体にクライアントアドレス情報を書き込む
	ClientAddr.sin_family = AF_INET;
	ClientAddr.sin_port = 0;							// ポート割り当て（0:任意の未使用のポート）
	ClientAddr.sin_addr.s_addr = htonl(INADDR_ANY);	

	// ソケットにアドレスをバインドする
	iResult = bind( ServerSd, (LPSOCKADDR)&ClientAddr, sizeof(ClientAddr));
	if( iResult == SOCKET_ERROR )
	{
		iResult = WSAGetLastError();
		sprintf( cMsg, "SRS_Lby_Term : bind error:%d", iResult );
		SRS_Dbg_WriteLog( cMsg );

		iResult = closesocket(ServerSd);
		return;
	}
	// アドレス構造体にサーバアドレス情報を書き込む
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(SRS_PORT_SERVER);
	memset( cServerName, 0, sizeof(cServerName) );
	dwSize = (DWORD)sizeof(cServerName);
    GetComputerName( cServerName, &dwSize );	// サーバ名獲得
    lphostent = gethostbyname(cServerName);		// IPアドレス獲得
    memcpy( (char *)&ServerAddr.sin_addr.s_addr, *lphostent->h_addr_list, 4);

	//　コネクション確立　
	SRS_Dbg_WriteLog( "SRS_Lby_Term : connect" );
	iResult = connect( ServerSd, (LPSOCKADDR)&ServerAddr, sizeof(ServerAddr) );
	if( iResult == SOCKET_ERROR )
	{
		iResult = WSAGetLastError();			//エラー詳細を獲得
		if( iResult == WSAEWOULDBLOCK )			//ソケットエラーがブロックの場合
		{
			FD_ZERO(lpWriteFds);				//ソケットデスクプリタの集合を初期化
			FD_SET(ServerSd, lpWriteFds);	//監視するソケットを設定

			// selectによる監視
			lpConnectTime->tv_sec = 10;			//秒
			lpConnectTime->tv_usec = 0;			//ミリ秒

			SRS_Dbg_WriteLog( "SRS_Lby_Term : select" );
			iResult = select(0, NULL, lpWriteFds, NULL, lpConnectTime);

			//　タイムアウトまたはエラーの場合
			if( (iResult == 0) || (iResult == SOCKET_ERROR) )
			{
				sprintf( cMsg, "SRS_Lby_Term : select error %d", iResult );
				SRS_Dbg_WriteLog( cMsg );
				iResult = closesocket(ServerSd);
				return;
			}
		}
		else
		{
			// ブロック以外のエラー
			sprintf( cMsg, "SRS_Lby_Term : connect error %d", iResult );
			SRS_Dbg_WriteLog( cMsg );
			iResult = closesocket(ServerSd);
			return;
		}
	}

	/*==================================*/
	/* 要求送信				  			*/
	/*==================================*/
	//　要求作成
	memset( cIfFix, 0, 256 );
	lpIfFix = (struct SRS_IF_FIX *)cIfFix;
	lpIfFix->IF_wRequest = IF_REQ_DISCONNECT;
	lpIfFix->IF_iPortNo = iPort;

	//  要求送信
	iSendLen = 0;
	do
	{
		iSendData = send( ServerSd, (char*)cIfFix, SRS_IF_FIX_SZ, 0 );
		iSendLen += iSendData;								
	}while( (iSendData != SOCKET_ERROR) && (iSendLen != SRS_IF_FIX_SZ) );

	if ( iSendData == SOCKET_ERROR )
	{
		iResult = WSAGetLastError();
		sprintf( cMsg,"SRS_Lby_Term : Send error :%d", iResult );
		SRS_Dbg_WriteLog( cMsg );
	}
	/*==================================*/
	/* 要求到達チェック  				*/
	/*==================================*/
	// クライアント側がコネクションを解放するまで待つ
	iResult = recv( ServerSd, cDummyBuff, 16, 0 );

	closesocket( ServerSd );
	return;
}