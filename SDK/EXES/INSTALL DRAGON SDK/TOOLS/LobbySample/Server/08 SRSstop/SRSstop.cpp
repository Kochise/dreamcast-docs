/***************************************************************************
 *
 *  Copyright (C) 1999 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       SRSstop.cpp
 *
 *  Content:    Lobby server terminate command サーバ終了コマンド
 *
 ***************************************************************************/
/*================================
    インクルード
==================================*/
#include <windows.h>
#include <stdio.h>

#include "SRScom.h"
#include "SRSdebug.h"

//////////////////////
// Additional Info.
// fixed... 2000.1.21 メモリリークバグ - chiba
// fixed... 2000.1.24 サーバーIPアドレス取得方法変更 - chiba
//

HKEY ghKey;

LONG RegistryOpen()
{
	return RegOpenKeyEx( HKEY_LOCAL_MACHINE, "SOFTWARE\\LOBBY SERVER", 0, KEY_ALL_ACCESS, &ghKey );
}

void RegistryClose()
{
	if ( ghKey )
	{
		RegCloseKey( ghKey );
		ghKey = NULL;
	}
}

void RegistryGetValue( char *str, char *dst )
{
	char temp[MAX_PATH];
	DWORD dw;
	dw = MAX_PATH;
	RegQueryValueEx( ghKey, str, NULL, NULL, (LPBYTE) &temp, &dw );
	strcpy( dst, temp );
}

DWORD SRSLog_IPLoad()
{
	char str[MAX_PATH];
	DWORD bi1, bi2, bi3, bi4;
	bi1 = bi2 = bi3 =  bi4 = 0;
	if ( RegistryOpen() ) return 0;
	RegistryGetValue( "IP Address", str );
	RegistryClose();
	sscanf( str, "%d.%d.%d.%d", &bi1, &bi2, &bi3, &bi4 );
	return ((bi1 & 0xff) | ((bi2 & 0xff) << 8) | ((bi3 & 0xff) << 16) | ((bi4 & 0xff) << 24));
}

/*=============================================================================
     関数   ：Lobbyサーバ プロセス終了
			（Lobby要求待ちプロセスへの終了通知をおこなう）
     入力   ：なし
     出力   ：なし
     戻り値 ：正常 0
              異常 -1

==============================================================================*/
int WINAPI WinMain( HINSTANCE hInstanc,HINSTANCE hPrevInstanc,
					LPSTR lpszCmdLin,int nCmdSho )
{
	SOCKET	ServerSd;			
	int 	iResult;							//
	int 	iSendLen;							// 送信データ長
	int 	iSendData;							// 送信データ長（カウント用）
    PHOSTENT lphostent;     					// ホスト情報の構造体ポインタ
	struct	SRS_IF_FIX *lpIfFix;				//
	char	cIfFix[256];						//
	char	cServerName[32];					//
	char	cDummyBuff[16];						//
	char	cMsg[256];

	// select用変数   
//	struct fd_set *lpReadFds = new struct fd_set;		//ｿｹｯﾄﾃﾞｽｸﾌﾟﾘﾀ集合
//	struct timeval *lpSockTime = new struct timeval;	//タイマ構造体
	struct timeval *lpConnectTime = new struct timeval;	//select用タイマ構造体
	struct fd_set *lpWriteFds = new struct fd_set;		//ｿｹｯﾄﾃﾞｽｸﾌﾟﾘﾀの集合（書き込み状態参照）
	// socket用
	WORD      wVersionRequested = MAKEWORD(1, 1);		// Winsock 1.1 を要求
	WSADATA   wsaData;									// Winsock の詳細
	SOCKADDR_IN   ClientAddr;							//クライアント側のアドレス構造体
	SOCKADDR_IN   ServerAddr;							//サーバ側のアドレス構造体
	u_long ulCmdArg = 1;								//ブロッキングモード


	/*==================================*/
	/* ソケット初期化                   */
	/*==================================*/
	iResult = WSAStartup( wVersionRequested, &wsaData );
	if ( iResult != 0 )
	{
		iResult = WSAGetLastError();
		sprintf( cMsg, "SRSstop : WSAStartup error:%d", iResult );
		SRS_Dbg_WriteLog( cMsg );
		goto ERRORRET;
//		return( -1 );
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
		sprintf( cMsg, "SRSstop : bind error:%d", iResult );
		SRS_Dbg_WriteLog( cMsg );

		iResult = closesocket(ServerSd);
		goto ERRORRET;
//		return( -1 );
	}
	// アドレス構造体にサーバアドレス情報を書き込む
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(SRS_PORT_SERVER);
    gethostname( cServerName, sizeof(cServerName) );
    lphostent = gethostbyname(cServerName);
    memcpy( (char *)&ServerAddr.sin_addr.s_addr, *lphostent->h_addr_list, 4);
	{
		//IPアドレスをレジストリからゲットしてみる。違ったらレジストリのほうを使う。
		DWORD ip;
		ip = SRSLog_IPLoad();
		if ( ip != 0 )
		{
			if ( ip != ServerAddr.sin_addr.s_addr )
			{
				sprintf( cMsg, "SRSstop : IP error:Sock[%d.%d.%d.%d] Reg[%d.%d.%d.%d]", (ServerAddr.sin_addr.s_addr & 0xff), ((ServerAddr.sin_addr.s_addr >> 8) & 0xff), ((ServerAddr.sin_addr.s_addr >> 16) & 0xff), ((ServerAddr.sin_addr.s_addr >> 24) & 0xff), (ip & 0xff), ((ip >> 8) & 0xff), ((ip >> 16) & 0xff), ((ip >> 24) & 0xff) );
				SRS_Dbg_WriteLog( cMsg );
				ServerAddr.sin_addr.s_addr = ip;
			}
		}
	}
/*
	{
		char str[MAX_PATH];
		sprintf( str, "%d.%d.%d.%d", (ServerAddr.sin_addr.s_addr & 0xff), ((ServerAddr.sin_addr.s_addr >> 8) & 0xff), ((ServerAddr.sin_addr.s_addr >> 16) & 0xff), ((ServerAddr.sin_addr.s_addr >> 24) & 0xff) );
		MessageBox( NULL, cServerName, str, MB_OK );
	}
*/
	//　コネクション確立　
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

			SRS_Dbg_WriteLog( "SRSstop : select" );
			iResult = select(0, NULL, lpWriteFds, NULL, lpConnectTime);

			//　タイムアウトまたはエラーの場合
			if( (iResult == 0) || (iResult == SOCKET_ERROR) )
			{
				sprintf( cMsg, "SRSstop : select error %d", iResult );
				SRS_Dbg_WriteLog( cMsg );
				iResult = closesocket(ServerSd);
				goto ERRORRET;
//				return( -1 );
			}
		}
		else
		{
			// ブロック以外のエラー
			sprintf( cMsg, "SRSstop : connect error %d", iResult );
			SRS_Dbg_WriteLog( cMsg );
			iResult = closesocket(ServerSd);
			goto ERRORRET;
//			return( -1 );
		}
	}

	/*==================================*/
	/* 要求送信				  			*/
	/*==================================*/
	//　要求作成
	memset( cIfFix, 0, 256 );
	lpIfFix = (struct SRS_IF_FIX *)cIfFix;
	lpIfFix->IF_wRequest = IF_REQ_TERMINATE;

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
		sprintf( cMsg,"SRSstop : Send error :%d", iResult );
		SRS_Dbg_WriteLog( cMsg );
		closesocket( ServerSd );
		goto ERRORRET;
//		return( -1 );
	}

	/*==================================*/
	/* 要求到達チェック  				*/
	/*==================================*/
	// クライアント側がコネクションを解放するまで待つ
	iResult = recv( ServerSd, cDummyBuff, 16, 0 );

	SRS_Dbg_WriteLog( "SRSstop OK" );
	closesocket( ServerSd );

	delete lpConnectTime;
	delete lpWriteFds;

	return( 0 );

ERRORRET:
	delete lpConnectTime;
	delete lpWriteFds;

	return ( -1 );
}
