/***************************************************************************
 *
 *  Copyright (C) 1999 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       SRSnetwork.cpp
 *
 *                  SRS_Net_Open 	 : コネクション準備
 *                  SRS_Net_Close    : コネクション解放
 *                  SRS_Net_RcvReq 	 : クライアント要求受信待ち
 *                  SRS_Net_SendReq  : 要求応答送信
 *
 *  Content:    Lobby server ネットワーク制御ライブラリ
 *
 ***************************************************************************/
/*================================
    インクルード
==================================*/
#include <windows.h>
#include <stdio.h>

#include "SRScom.h"
#include "SRSdebug.h"
#include "SRSnetwork.h"

/*================================
  グローバル域
==================================*/
SOCKET	AcceptClientSd;			//接続聴取用ソケットディスクリプタ
SOCKET	RcvClientSd;			//受信用ソケットディスクリプタ
SOCKET	SendClientSd;			//受信用ソケットディスクリプタ
/*=============================================================================
     関数   ：コネクション準備
             （対 Lobbyクライアント用のコネクションを準備する）
     入力   ：iPort      ポート番号
     出力   ：なし
     戻り値 ：正常  0
              異常 -1

==============================================================================*/
__declspec( dllexport )int __stdcall SRS_Net_Open( int iPort )
{
	SOCKADDR_IN addr;
	WORD 	wVersionRequested = MAKEWORD(1, 1);	// Winsock 1.1 を要求
	WSADATA wsaData;						// Winsock の詳細
	int		iResult;						//
	char	cMsg[256];						//

	//=================================
	// ソケット初期化
	//=================================
	if( WSAStartup( wVersionRequested, &wsaData ) != 0 ) 
	{
		iResult = WSAGetLastError();
		sprintf( cMsg, "SRS_Net_RcvReq : socket ready error:%d",iResult );
		SRS_Dbg_WriteLog( cMsg );
		return( -1 );
	}
	//=================================
	//　ソケット生成
	//=================================
	AcceptClientSd = socket( AF_INET, SOCK_STREAM, 0 );
	
	if( AcceptClientSd == INVALID_SOCKET )	// ソケット生成失敗
	{
		iResult = WSAGetLastError();
		sprintf( cMsg, "SRS_Ini_Main : socket error %d", iResult);
		SRS_Dbg_WriteLog( cMsg );
		return( -1 );
	}
	addr.sin_family = AF_INET;
	addr.sin_port = htons( iPort );			
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	//===================================
	// ソケットバインド 
	//===================================
	iResult = bind( AcceptClientSd, (LPSOCKADDR)&addr, sizeof(addr) );
	if(  iResult == SOCKET_ERROR )
	{
		iResult = WSAGetLastError();
		sprintf( cMsg, "SRS_Net_RcvReq : bind error:%d", iResult );
		SRS_Dbg_WriteLog( cMsg );
		closesocket( AcceptClientSd );
		return( -1 );
	}
	return( 0 );
}

/*=============================================================================
     関数   ：コネクション解放（Lobby クライアントとのコネクションを解放する）
     入力   ：なし
     出力   ：なし
     戻り値 ：正常 0
              異常 -1

==============================================================================*/
__declspec( dllexport )int __stdcall SRS_Net_Close( void )
{
	int		iRtn;
	char	cMsg[256];
	//====================================
	//  ソケット解放
	//====================================
	closesocket( AcceptClientSd );		// 接続聴取用ソケット解放
	closesocket( RcvClientSd );			// 受信用ソケット解放
	closesocket( SendClientSd );		// 送信用ソケット解放

	iRtn = WSACleanup();
	if( iRtn == SOCKET_ERROR )
	{
		iRtn = WSAGetLastError();
		sprintf( cMsg, "SRS_Net_Close :Socket CleanUp error:%d\n", iRtn );
		return( -1 );
	}

	return( 0 );
}

/*=============================================================================
     関数   ：クライアント要求受信待ち
             （Lobby クライアントからの要求を待ち合わせる）
     入力   ：lpRcvData  受信データ域ポインタ
			  szSize     受信データ域長	
     出力   ：なし
     戻り値 ：正常 受信データ長
              異常 -1

==============================================================================*/
__declspec( dllexport )int __stdcall SRS_Net_RcvReq( char *lpRcvData, size_t szSize )
{
	SOCKADDR_IN clientAddr;						// ソケットアドレス
	IN_ADDR clientIn;							//
	int 	nClientAddrLen;						// ソケットアドレスの長さ					
	WORD 	wVersionRequested = MAKEWORD(1, 1);	// Winsock 1.1 を要求
	int 	nBytesRecv;							// 受信バイト数
	int 	iRecvBytes;							// 合計受信バイト数
	int 	nResult;							// 
	int		iRequestSize;						// 要求データサイズ
	struct	SRS_IF_FIX *lpIfFix;				//
	char	cMsg[256];							//

	//===================================
	//　接続を聴取する 
	//===================================
	nResult = listen( AcceptClientSd , 5 );	//キューには５つまでが積まれる
	if( nResult == SOCKET_ERROR )
	{
		nResult = WSAGetLastError();
		sprintf( cMsg, "SRS_Net_RcvReq : listen error %d",nResult);
		SRS_Dbg_WriteLog( cMsg );
		closesocket( AcceptClientSd );
		return( -1 );
	}

	nClientAddrLen = sizeof( clientAddr );

	//==========================================
	// クライアント受信用コネクション確立待ち
	//==========================================
	SRS_Dbg_WriteLog( "SRS_Net_RcvReq : accept" );
	RcvClientSd = accept( AcceptClientSd, (LPSOCKADDR)&clientAddr, &nClientAddrLen );
	if( RcvClientSd == INVALID_SOCKET )
	{
		nResult = WSAGetLastError();
		sprintf( cMsg, "SRS_Net_RcvReq : accept(RcvClient)error:%d", nResult );
		SRS_Dbg_WriteLog( cMsg );
		closesocket( AcceptClientSd );
		return( -1 );
	}

	// ４バイトのＩＰアドレスをＩＰアドレス構造体にコピーする
	memcpy( &clientIn, &clientAddr.sin_addr.s_addr, 4 );

	//==========================================
	// 要求受信（共通域）
	//==========================================
	for( iRecvBytes = 0, nBytesRecv = 0 ; iRecvBytes < (SRS_IF_FIX_SZ - 4); )
	{
		nBytesRecv = recv( RcvClientSd, lpRcvData, szSize, 0 );
		if( nBytesRecv == SOCKET_ERROR )	// 通信異常？
		{
			nResult = WSAGetLastError();
			sprintf( cMsg, "SRS_Net_RcvReq : recv error:%d", nResult );
			SRS_Dbg_WriteLog( cMsg );
			closesocket( RcvClientSd );
			closesocket( AcceptClientSd );
			return( -1 );
		}
		sprintf( cMsg, "SRS_Net_RcvReq : Recv %d bytes", nBytesRecv );
		SRS_Dbg_WriteLog( cMsg );
		iRecvBytes += nBytesRecv;
	}  
	//==========================================
	// 要求受信（固有域）
	//==========================================
	lpIfFix = (struct SRS_IF_FIX *)lpRcvData;
	iRequestSize = SRS_IF_FIX_SZ - 4 + lpIfFix->IF_iInformationSize;	// 要求データ長算出
	for(  ; iRecvBytes < iRequestSize ; )
	{
		nBytesRecv = recv( RcvClientSd, lpRcvData, szSize, 0 );
		if( nBytesRecv == SOCKET_ERROR )	// 通信異常？
		{
			nResult = WSAGetLastError();
			sprintf( cMsg, "SRS_Net_RcvReq : recv error:%d", nResult );
			SRS_Dbg_WriteLog( cMsg );
			closesocket( RcvClientSd );
			closesocket( AcceptClientSd );
			return( -1 );
		}
		sprintf( cMsg, "SRS_Net_RcvReq : Recv %d bytes", nBytesRecv );
		SRS_Dbg_WriteLog( cMsg );
		iRecvBytes += nBytesRecv;
	}
	memcpy( (char *)&lpIfFix->IF_iIp, &clientAddr.sin_addr.s_addr, 4 );	// クライアントIP設定

	SRS_Dbg_WriteData( "SRS_Net_RcvReq : 要求受信", lpRcvData, iRequestSize, "ab" );

	closesocket( RcvClientSd );
	return( iRecvBytes );
}

/*=============================================================================
     関数   ：情報送信（Lobby クライアントへ情報を送信する）
     入力   ：lpSendData  送信データ域ポインタ
			  iSize		  送信データ長	
     出力   ：なし
     戻り値 ：正常 0
              異常 -1

==============================================================================*/
__declspec( dllexport )int __stdcall SRS_Net_SendReq( int iClientIP, char *lpSendData, size_t szSize )
{
	SOCKET	ClientSd;							//
	int 	iResult;							//
	int 	iSendLen;							// 送信データ長
	int 	iSendData;							// 送信データ長（カウント用）
	char	cDummyBuff[16];						// 要求到達待ち用ダミーバッファ
	char	cMsg[256];

	// select用変数   
	struct fd_set *lpReadFds = new struct fd_set;		//ｿｹｯﾄﾃﾞｽｸﾌﾟﾘﾀ集合
	struct timeval *lpSockTime = new struct timeval;	//タイマ構造体
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
	sprintf( cMsg, "SRS_Net_SendReq :送信要求 %d bytes", szSize );
	SRS_Dbg_WriteLog( cMsg );
	SRS_Dbg_WriteData( "SRS_Net_SendReq :送信要求", lpSendData, szSize, "ab" );

	iResult = WSAStartup( wVersionRequested, &wsaData );
	if ( iResult != 0 )
	{
		iResult = WSAGetLastError();
		sprintf( cMsg, "SRS_Net_SendReq : WSAStartup error:%d", iResult );
		SRS_Dbg_WriteLog( cMsg );
		return( -1 );
	}

	ClientSd = socket( AF_INET, SOCK_STREAM, 0 );	//クライアント送信用ソケット作成

	/*==================================*/
	/* セッション確立 		 			*/
	/*==================================*/
	// アドレス構造体にクライアントアドレス情報を書き込む
	ClientAddr.sin_family = AF_INET;
	ClientAddr.sin_port = 0;							// ポート割り当て（0:任意の未使用のポート）
	ClientAddr.sin_addr.s_addr = htonl(INADDR_ANY);	

	// ソケットにアドレスをバインドする
	iResult = bind( ClientSd, (LPSOCKADDR)&ClientAddr, sizeof(ClientAddr));
	if( iResult == SOCKET_ERROR )
	{
		iResult = WSAGetLastError();
		sprintf( cMsg, "SRS_Net_SendReq : bind error:%d", iResult );
		SRS_Dbg_WriteLog( cMsg );

		iResult = closesocket(ClientSd);
		return( -1 );
	}
	// アドレス構造体にサーバアドレス情報を書き込む
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons( SRS_PORT_CLIENT );		
	ServerAddr.sin_addr.s_addr = iClientIP;	

	//　コネクション確立　
	SRS_Dbg_WriteLog( "SRS_Net_SendReq : connect" );
	iResult = connect( ClientSd, (LPSOCKADDR)&ServerAddr, sizeof(ServerAddr) );
	if( iResult == SOCKET_ERROR )
	{
		iResult = WSAGetLastError();			//エラー詳細を獲得
		if( iResult == WSAEWOULDBLOCK )			//ソケットエラーがブロックの場合
		{
			FD_ZERO(lpWriteFds);				//ソケットデスクプリタの集合を初期化
			FD_SET(ClientSd, lpWriteFds);	//監視するソケットを設定

			// selectによる監視
			lpConnectTime->tv_sec = 10;			//秒
			lpConnectTime->tv_usec = 0;			//ミリ秒

			sprintf( cMsg, "SRS_Net_SendReq : select wait=%d秒", lpConnectTime->tv_sec );
			SRS_Dbg_WriteLog( cMsg );
			iResult = select(0, NULL, lpWriteFds, NULL, lpConnectTime);

			//　タイムアウトまたはエラーの場合
			if( (iResult == 0) || (iResult == SOCKET_ERROR) )
			{
				sprintf( cMsg, "SRS_Net_SendReq : select error %d", iResult );
				SRS_Dbg_WriteLog( cMsg );
				iResult = closesocket(ClientSd);
				return( -1 );
			}
		}
		else
		{
			// ブロック以外のエラー
			sprintf( cMsg, "SRS_Net_SendReq : connect error %d", iResult );
			SRS_Dbg_WriteLog( cMsg );
			iResult = closesocket(ClientSd);
			return( -1 );
		}
	}
	/*==================================*/
	/* 要求（応答）送信		  			*/
	/*==================================*/
	for( iSendLen = 0 ; iSendLen < (int)szSize ; )
	{
		iSendData = send( ClientSd, (char*)lpSendData, szSize, 0 );
		if ( iSendData == SOCKET_ERROR )
		{
			iResult = WSAGetLastError();
			sprintf( cMsg,"SRS_Net_SendReq : Send error :%d", iResult );
			SRS_Dbg_WriteLog( cMsg );
			closesocket( ClientSd );
			return( -1 );
		}
		iSendLen += iSendData;
		sprintf( cMsg, "SRS_Net_SendReq : Send %d/%d bytes",iSendLen, szSize );
		SRS_Dbg_WriteLog( cMsg );
	}
	/*==================================*/
	/* 要求到達チェック  				*/
	/*==================================*/
	// クライアント側がコネクションを解放するまで待つ
	iResult = recv( ClientSd, cDummyBuff, 16, 0 );
	closesocket( ClientSd );
	return( 0 );
}

