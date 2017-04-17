/***************************************************************************
 *
 *  Copyright (C) 1999 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       SRSinitial.cpp
 *					SRS_Ini_Server			(サーバ初期化)
 *					SRS_Ini_GetPort			(空きポート獲得)
 *					SRS_Ini_UsePort			(使用中ポート獲得)
 *					SRS_Ini_ReleasePort		(使用ポート解放)
 *					SRS_Ini_TermProc		(Lobbyプロセス回収)
 *					SRS_Ini_CreateLobby		(ロビープロセス生成)
 *					SRS_Ini_CreateProcess	(プロセス生成)
 *
 *  Content:    Lobby server 初期設定＆接続要求待ちプロセス
 *
 ***************************************************************************/
/*================================
    インクルード
==================================*/
#include <windows.h>
#include <stdio.h>

#include "SRScom.h"
#include "SRSdebug.h"
#include "SRSregistry.h"
#include "SRSmanage.h"
#include "SRSinitial.h"

/*================================
    グローバル域
==================================*/
SOCKET 	AcceptClientSd;					//接続聴取用ソケットディスクリプタ
SOCKET 	ClientSd;						//クライアントソケットディスクリプタ
struct	SRS_PORT_LIST 	*lpPortList;	//	ポート番号リストポインタ

HKEY ghKey = NULL;

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
     関数   ：初期設定＆接続要求待ち
			（サーバ初期設定と Lobbyクライアントからの接続要求を待つ）
     入力   ：なし
     出力   ：なし
     戻り値 ：正常 0
              異常 -1

==============================================================================*/
int WINAPI WinMain( HINSTANCE hInstanc,HINSTANCE hPrevInstanc,
					LPSTR lpszCmdLin,int nCmdSho )
{
	SOCKADDR_IN addr;
	SOCKADDR_IN clientAddr;					//ソケットアドレス
	IN_ADDR clientIn;						//
	int 	nClientAddrLen;					//ソケットアドレスの長さ					
	WORD 	wVersionRequested = MAKEWORD(1, 1);	// Winsock 1.1 を要求
	WSADATA wsaData;						// Winsock の詳細
	int 	nBytesRecv;
	int 	iRecvBytes;
	int 	nResult;
	int		iRtn;
	int		iResult;						//結果用変数
	int		iSendData;						//send用 送信バイト数（結果）
	int		iSendLen;						//send用 送信バイト数
	int		iSendSize;						//送信データ長

	int		iLoopOut;						// 要求待ち終了情報
	int		iClientIp;						// クライアントＩＰアドレス
	int		iPort;							// ポート番号
	struct 	SRS_IF_FIX	*lpIfFix;			//
	struct	SRS_IF_CONNECT	*lpIfConnect;	//
	struct	SRS_REG_INFO *lpRegInfo;		//
	unsigned char	cIp[8];
	char	cIfFix[256];					// インタフェース域
	char	cRegInfo[SRS_REG_INFO_SZ];		//
	char	cSendMessage[SRS_MAX_LOGMSG];	//
	char	cMsg[256];						//

//=================================================================================
//
//		通信環境設定
//
//=================================================================================
	CopyFile( OUT_FILE_LOG, OUT_FILE_LOGBACK, FALSE );
	CopyFile( OUT_FILE_DATA, OUT_FILE_DATABACK, FALSE );
	DeleteFile( OUT_FILE_LOG );			// ログファイル削除
	DeleteFile( OUT_FILE_DATA );		// データファイル削除
	
	//======================================
	//  サーバ環境初期化
	//======================================
	iRtn = SRS_Ini_Server( );			// サーバ初期設定
	if( iRtn != 0 )						// 初期設定失敗？
	{
//		sprintf( cMsg, "SRS_Ini_Server error" );
//		SRS_Dbg_WriteLog( cMsg );
		iRtn = SRS_Reg_Log( 0 );
		return( -1 );
	}

	//=================================
	// ソケット初期化
	//=================================
	if( WSAStartup( wVersionRequested, &wsaData ) != 0 ) 
	{
//		nResult = WSAGetLastError();
//		sprintf( cMsg, "SRS_Ini_main : socket ready error:%d",errno);
//		SRS_Dbg_WriteLog( cMsg );
		iRtn = SRS_Reg_Log( 0 );
		return( -1 );
	}
	//=================================
	//　ソケット生成
	//=================================
	AcceptClientSd = socket( AF_INET, SOCK_STREAM, 0 );
	
	if( AcceptClientSd == INVALID_SOCKET )	// ソケット生成失敗
	{
//		errno = WSAGetLastError();
//		sprintf( cMsg, "SRS_Ini_Main : socket error %d",errno);
//		SRS_Dbg_WriteLog( cMsg );
		iRtn = SRS_Reg_Log( 0 );
		return( -1 );
	}
	addr.sin_family = AF_INET;
	addr.sin_port = htons( SRS_PORT_SERVER );			
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	//===================================
	// ソケットバインド 
	//===================================
	nResult = bind( AcceptClientSd, (LPSOCKADDR)&addr, sizeof(addr) );
	if(  nResult == SOCKET_ERROR )
	{
//		nResult = WSAGetLastError();
//		sprintf( cMsg, "SRS_Ini_main : bind error:%d", nResult );
//		SRS_Dbg_WriteLog( cMsg );
		closesocket( AcceptClientSd );
		iRtn = SRS_Reg_Log( 0 );
		return( -1 );
	}
	//===================================
	//　接続を聴取する 
	//===================================
//  NOTE :
//    バックログは、WinSockが過剰な資源を割当てることを防止する保護網として動作する。
//    １階の処理間隔内に５以上の接続がくるとクライアントに WSAECONNREFUSED(10061：接続拒否）
//    が通知される。

	nResult = listen( AcceptClientSd , 5 );	//バックログとしてキューには５つまでが積まれる
	if( nResult == SOCKET_ERROR )
	{
//		nResult = WSAGetLastError();
//		sprintf( cMsg, "SRS_Ini_main : listen error %d",nResult);
//		SRS_Dbg_WriteLog( cMsg );
		closesocket( AcceptClientSd );
		iRtn = SRS_Reg_Log( 0 );
		return( -1 );
	}

	//==========================================================================
	//
	//	要求待ち合わせ
	//
	//==========================================================================
	for( iLoopOut = 0 ; iLoopOut == 0 ; )
	{
//		GetPrivateProfileString( "Message", "Message", "メッセージが登録されていません", cSendMessage, sizeof(cSendMessage), ".\\message.txt");
//		SRS_Dbg_WriteLog( cSendMessage );

		//==========================================
		// クライアント受信用コネクション確立待ち
		//==========================================
		nClientAddrLen = sizeof( clientAddr );
//		SRS_Dbg_WriteLog( "SRS_Ini_main : accept" );
		ClientSd = accept( AcceptClientSd, (LPSOCKADDR)&clientAddr, &nClientAddrLen );
		if( ClientSd == INVALID_SOCKET )
		{
//			nResult = WSAGetLastError();
//			sprintf( cMsg, "SRS_Ini_main : accept(RcvClient)error:%d", nResult );
//			SRS_Dbg_WriteLog( cMsg );
			closesocket( AcceptClientSd );
			iRtn = SRS_Reg_Log( 0 );
			return( -1 );
		}

		// ４バイトのＩＰアドレスをＩＰアドレス構造体にコピーする
 		memcpy( &clientIn, &clientAddr.sin_addr.s_addr, 4 );
		memcpy( (char *)&iClientIp, &clientIn, 4 );

		//==========================================
		// 要求受信
		//==========================================
//		SRS_Dbg_WriteLog( "SRS_Ini_main : recv" );
		iRecvBytes = 0;
		nBytesRecv = 0;
		do
		{
			nBytesRecv = recv( ClientSd, cIfFix, SRS_IF_FIX_SZ, 0 );
//			sprintf( cMsg, "SRS_Ini_main : Recv %d bytes", nBytesRecv );
//			SRS_Dbg_WriteLog( cMsg );

			iRecvBytes += nBytesRecv;
//			sprintf( cMsg, "SRS_Ini_main : ********* %d", iRecvBytes );
//			SRS_Dbg_WriteLog( cMsg );
		}while( (nBytesRecv != SOCKET_ERROR) &&  nBytesRecv != 0 && iRecvBytes != SRS_IF_FIX_SZ );
		lpIfFix = (struct SRS_IF_FIX *)cIfFix;
//		sprintf( cMsg, "SRS_Ini_main : %04x, %04x, %08x, %08x, %08x", lpIfFix->IF_wRequest, lpIfFix->IF_wResult, lpIfFix->IF_iInformationSize, lpIfFix->IF_iPortNo, lpIfFix->IF_iIp );
//		SRS_Dbg_WriteLog( cMsg );

		if( nBytesRecv == SOCKET_ERROR)
		{
//			nResult = WSAGetLastError();
//			sprintf( cMsg, "SRS_Ini_main : recv error:%d", nResult );
//			SRS_Dbg_WriteLog( cMsg );
			closesocket( ClientSd );
			closesocket( AcceptClientSd );
			iRtn = SRS_Reg_Log( 0 );
			return( -1 );
		}
//		SRS_Dbg_WriteData( "SRS_Ini_main : recv SRS_IF_FIX", cIfFix, SRS_IF_FIX_SZ, "ab" );
//		SRS_Dbg_WriteLog( "SRS_Ini_main : clear 2!" );

		//===================================================
		//  受信要求判定
		//===================================================
		lpIfFix = (struct SRS_IF_FIX *)cIfFix;
		lpIfFix->IF_iIp = iClientIp;		// クライアントＩＰアドレス設定
		memset( cIp, 0, 8 );
		memcpy( cIp, (char *)&iClientIp, 4 );
//		sprintf( cMsg, "SRS_Ini_main : clear 3! [%d]", lpIfFix->IF_wRequest );
//		SRS_Dbg_WriteLog( cMsg );
		switch( lpIfFix->IF_wRequest )
		{
			//==================================
			// 接続要求  受信
			//==================================
			case	IF_REQ_CONNECT      :

						sprintf( cMsg, "SRS_Ini_main：接続要求受信 IP=%d.%d.%d.%d", cIp[0],cIp[1],cIp[2],cIp[3] );
						SRS_Dbg_WriteLog( cMsg );

						iPort = SRS_Ini_GetPort( iClientIp );	// 空きポート検索
						if( iPort == -1 )						// 検索失敗？
						{
							//　応答作成（異常応答：最大値オーバ）
							lpIfFix->IF_wResult = IF_CMP_MAXOVER;
							lpIfFix->IF_iInformationSize = 0;
							iSendSize = SRS_IF_FIX_SZ;
						}
						else
						{	
							//====================================
							//  Ｌｏｂｂｙプロセス生成
							//====================================
							iRtn = SRS_Ini_CreateLobby( iPort );
							if( iRtn == 0 )						// 生成成功？
							{
								//　応答作成（正常応答）
								lpIfFix->IF_wResult = IF_CMP_SUCCESS;
								lpIfFix->IF_iInformationSize = SRS_IF_CONNECT_SZ;
								lpIfFix->IF_iPortNo = iPort;	// ポート番号設定
								lpRegInfo = (struct SRS_REG_INFO *)cRegInfo;
								iRtn = SRS_Reg_GetComInfo( lpRegInfo );
								lpIfConnect = (struct SRS_IF_CONNECT *)lpIfFix->IF_cInformation;
								lpIfConnect->IF_CN_wMaxUser = lpRegInfo->wMaxUser;
								lpIfConnect->IF_CN_wMaxLobby = lpRegInfo->wMaxLobby;
								lpIfConnect->IF_CN_wMaxGroup = lpRegInfo->wMaxGroup;
								lpIfConnect->IF_CN_wMaxGame = lpRegInfo->wMaxGame;
								lstrcpy( lpIfConnect->IF_CN_cMessage, cSendMessage);

								iSendSize = SRS_IF_FIX_SZ + SRS_IF_CONNECT_SZ;
								//
								// トレース出力
								//
//								memset( cMsg, 0, 256 );
//								sprintf( cMsg, "接続要求を受け付けた。（クライアントＩＰ=%d.%d.%d.%d 割付ポート=%04d）", cIp[0],cIp[1],cIp[2],cIp[3],iPort );
//    							iRtn = SRS_Reg_Log( cMsg );
//								SRS_Dbg_WriteLog( cMsg );
							}
							else
							{
								//　応答作成（異常応答：Lobbyプロセス起動エラー）
								lpIfFix->IF_wResult = IF_CMP_PROCERR;
								lpIfFix->IF_iInformationSize = 0;
								iSendSize = SRS_IF_FIX_SZ;
							}
						}
						//===================================
						//  応答送信
						//===================================
//						sprintf( cMsg, "SRS_Ini_main : 応答送信" );	
//						SRS_Dbg_WriteLog( cMsg );
//						SRS_Dbg_WriteData( cMsg, (char *)lpIfFix, iSendSize , "ab" );
						iSendLen = 0;
						do
						{
							iSendData = send( ClientSd, (char*)cIfFix, iSendSize, 0 );
							iSendLen += iSendData;								
						}while( (iSendData != SOCKET_ERROR) && (iSendLen != iSendSize) );

						if ( iSendData == SOCKET_ERROR )
						{
//							iResult = WSAGetLastError();
//							sprintf( cMsg,"SRS_Ini_main : Send error :%d", iResult );
//							SRS_Dbg_WriteLog( cMsg );
							closesocket( AcceptClientSd );
							closesocket( ClientSd );
							iRtn = SRS_Reg_Log( 0 );
							return( -1 );
						}
						closesocket( ClientSd );
						break;

			//==================================
			// 解放要求  受信
			//==================================
			case	IF_REQ_DISCONNECT	:	
//						SRS_Dbg_WriteLog( "SRS_Ini_main ： 切断要求  受信" );
						iPort = lpIfFix->IF_iPortNo;
//						sprintf( cMsg, "解放要求を受け付けた。（クライアントＩＰ=%d.%d.%d.%d 割付ポート=%04d）", cIp[0],cIp[1],cIp[2],cIp[3],iPort );
//						iRtn = SRS_Reg_Log( cMsg );
//						SRS_Dbg_WriteLog( cMsg );
						closesocket( ClientSd );
						iRtn = SRS_Ini_TermProc( iPort );		// Lobbyプロセス回収
//						SRS_Dbg_WriteLog( "SRS_Ini_main : SRS_Ini_TermProc終了" );
						iRtn = SRS_Ini_ReleasePort( iPort );	// ポート解放
//						SRS_Dbg_WriteLog( "SRS_Ini_main : SRS_Ini_ReleasePort終了" );
						break;

			//==================================
			// 終了要求  受信
			//==================================
			case	IF_REQ_TERMINATE	:	
//						SRS_Dbg_WriteLog( "SRS_Ini_main ： 終了要求  受信" );
						for( ; ; )
						{	
							iPort = SRS_Ini_UsePort( );				// 使用中ポート検索
							if( iPort == -1 )						// 使用中ポートなし？
							{
								break;
							}
							closesocket( ClientSd );
							iRtn = SRS_Ini_TermProc( iPort );		// Lobbyプロセス回収
							iRtn = SRS_Ini_ReleasePort( iPort );	// ポート解放
						}
						iLoopOut = 1;
						break;

			//==================================
			// システムエラー
			//==================================
			default						:
//						sprintf( cMsg, "SRS_Ini_main：未定義要求(%04x)受信",lpIfFix->IF_wRequest);
//						SRS_Dbg_WriteLog( cMsg );
						iLoopOut = 1;
						closesocket( AcceptClientSd );
						closesocket( ClientSd );
						break;
		}
		closesocket( ClientSd );
//		SRS_Dbg_WriteLog( "SRS_Ini_main : 次の要求待ちへ" );
	}

	closesocket( AcceptClientSd );
	iRtn = SRS_Reg_Log( 0 );
//	SRS_Dbg_WriteLog( "SRS_Ini_main : サーバ停止" );

	// 1.31.2000 added...
	if ( lpPortList )
	{
		free( lpPortList );
		lpPortList = NULL;
	}
	return( 0 );
}

/*=============================================================================
     関数   ：サーバ初期設定（サーバ動作環境の初期設定をおこなう）
     入力   ：なし
     出力   ：なし
     戻り値 ：正常 0
              異常 -1

==============================================================================*/
int	SRS_Ini_Server( void )
{
	int		iRtn;								//
	int		iAllocSize;							// 獲得領域サイズ
	int		iPortCount;							// 準備ポート数
	int		iPortNo;							// ポート番号
	int		iItem;								//
	struct	SRS_REG_INFO *lpRegInfo;			// サーバ共通情報域ポインタ
	char	cPort[4];							//
	char	cRegInfo[SRS_REG_INFO_SZ];			// 共通管理情報域
	char	cMsg[256];

	//=============================================
	//  ログメッセージ環境初期化
	//=============================================
	iRtn = SRS_Ini_CreateProc( SRS_CREATE_ASYNC, SRS_PROC_LOG );
	//=============================================
	//  サーバ情報初期化
	//=============================================
	iRtn = SRS_Mng_Startup( );
	if( iRtn == -1 )								// 初期化失敗？
	{
//		SRS_Dbg_WriteLog( "SRS_Mng_Startup error" );
		return( -1 );
	}
	//=============================================
	//  ポートリスト作成
	//=============================================
	lpRegInfo = (struct SRS_REG_INFO *)cRegInfo;
	iRtn = SRS_Reg_GetComInfo( lpRegInfo );		// 共通管理情報域取り込み
	if( iRtn == -1 )							// 取り込み失敗？
	{
//		sprintf( cMsg, "SRS_Ini_Server : SRS_Reg_GetComInfo error" );
//		SRS_Dbg_WriteLog( cMsg );
		return( -1 );
	}

	lpPortList = 0;
	iPortCount = lpRegInfo->wMaxUser;				// 最大ユーザ数設定	
	iAllocSize = SRS_PORT_LIST_SZ + (SRS_PORT_ITEM_SZ * iPortCount);    
	lpPortList = (struct SRS_PORT_LIST *)malloc( iAllocSize );
	if( lpPortList == 0 )							// 獲得失敗？
	{
//		sprintf( cMsg, "SRS_PORT_LIST alloc error" );
//		SRS_Dbg_WriteLog( cMsg );
		return( -1 );
	}
	memset( (char *)lpPortList, 0, iAllocSize );
	//
	// ポート番号設定
	//
	iRtn = SRS_Reg_GetInfo( SRS_REG_KEY_COM, SRS_REG_CLIENTPORT, cPort );	// 先頭ポート番号獲得
	if( iRtn == 0 )
	{
		sscanf( cPort, "%d", &iPortNo );
	}
	else
	{
		iPortNo = 7100;								// デフォルト予約ポート先頭番号設定
	}
	lpPortList->PL_iItemNo = iPortCount;			// ポート数設定
	for( iItem = 0 ; iItem < iPortCount ; iItem++ )
	{
		lpPortList->PL_Item[iItem].PI_iPort = iPortNo;
		iPortNo = iPortNo + 1;						// ポート番号更新
	}
//	sprintf( cMsg, "Port-List size=%04x", iAllocSize );
//	SRS_Dbg_WriteData( cMsg, (char *)lpPortList, iAllocSize, "ab" );
	return( 0 );
}

/*=============================================================================
     関数   ：空きポート名通知（使用可能なサーバポート番号を通知する）
     入力   ：iClientIp  クライアントＩＰアドレス
     出力   ：なし
     戻り値 ：正常 （ポート番号）
              異常  -1

==============================================================================*/
int SRS_Ini_GetPort( int iClientIp )
{
	int		iPort;									//
	int		iItem;									//

	//======================================
	//  割り当て済判定
	//======================================
	if( lpPortList == 0 )							// ポートリストなし？
	{
//		SRS_Dbg_WriteLog( "Port list error" );
		return( -1 );								// システムエラー
	}
	// ＩＰアドレスが既に割り当たっている場合は同一ポートを割り当てる
	for( iItem = 0 ; iItem < lpPortList->PL_iItemNo ; iItem++ )
	{
		if( lpPortList->PL_Item[iItem].PI_iIp == iClientIp )	// 同一ＩＰ？
		{
			iPort = lpPortList->PL_Item[iItem].PI_iPort;
			return( iPort );
		}
	}

	//======================================
	//  未使用ポート検索
	//======================================
	for( iItem = 0 ; iItem < lpPortList->PL_iItemNo ; iItem++ )
	{
		if( lpPortList->PL_Item[iItem].PI_iIp == 0 )	// 未使用ポート？
		{
			iPort = lpPortList->PL_Item[iItem].PI_iPort;
			lpPortList->PL_Item[iItem].PI_iIp = iClientIp;
			return( iPort );
		}
	}
	// 未使用ポートなし
	return( -1 );
}

/*=============================================================================
     関数   ：使用中ポート番号通知（使用中ポート番号を通知する）
     入力   ：なし
     出力   ：なし
     戻り値 ：正常    （ポート番号）
              異常  -1（使用中ポートなし）

==============================================================================*/
int SRS_Ini_UsePort( void )
{
	int		iPort;									//
	int		iItem;									//

	//======================================
	//  割り当て済判定
	//======================================
	if( lpPortList == 0 )							// ポートリストなし？
	{
//		SRS_Dbg_WriteLog( "Port list error" );
		return( -1 );								// システムエラー
	}
	// ＩＰアドレスが既に割り当たっているポートを検索する
	for( iItem = 0 ; iItem < lpPortList->PL_iItemNo ; iItem++ )
	{
		if( lpPortList->PL_Item[iItem].PI_iIp != 0 )	// 使用中ポート？
		{
			iPort = lpPortList->PL_Item[iItem].PI_iPort;
			return( iPort );
		}
	}
	// 使用ポートなし
	return( -1 );
}

/*=============================================================================
     関数   ：ポート返却（使用中ポート番号を返却する）
     入力   ：iPort  ポート番号
     出力   ：なし
     戻り値 ：正常  0
              異常  -1(システムエラー)

==============================================================================*/
int	SRS_Ini_ReleasePort( int iPort )
{
	int		iItem;		
	char	cPort[8];				// ポート番号
	char	cLobbyProc[256];		// 削除 Lobbyプロセス名

	//======================================
	//  返却ポート検索
	//======================================
	for( iItem = 0 ; iItem < lpPortList->PL_iItemNo ; iItem++ )
	{
		if( lpPortList->PL_Item[iItem].PI_iPort == iPort )	
		{
			lpPortList->PL_Item[iItem].PI_iIp = 0;		// ＩＰアドレスクリア
			//======================================
			//  該当Lobbyプロセス削除
			//======================================
			memset( cLobbyProc, 0, 256 );
			memset( cPort, 0, 8 );
			strcpy( cLobbyProc, SRS_PROC_LOBBY );	// 削除プロセス名生成
			sprintf( cPort, "%04d", iPort );		//
			strcat( cLobbyProc, cPort );			//
			strcat( cLobbyProc, ".exe" );			//
			DeleteFile( cLobbyProc );				// プロセス削除
			return( 0 );
		}
	}
	return( -1 );									// システムエラー
}

/*=============================================================================
     関数    ：Lobbyプロセス生成
     入力    ：iPort  ポート番号
     出力    ：なし
     戻り値  ：正常  0
               異常  -1 (生成失敗)
	 特記事項：起動するLobbyプロセス名は基本名にポート番号を付加した名前になる
                 (例：SRSlobby7000.exe)

==============================================================================*/
int	SRS_Ini_CreateLobby( int iPort )
{
	int		iRtn;
	BOOL	fRtn;
	DWORD	dwRtn;
	char	cPort[8];				// ポート番号
	char	cNewLobbyProc[256];		// 起動 Lobbyプロセス名
	char	cLobbyProc[256];		// 元 Lobbyプロセス名
	char	cMsg[256];

	//======================================
	//  起動Lobbyプロセス名生成
	//======================================
	memset( cNewLobbyProc, 0, 256 );
	memset( cPort, 0, 8 );
	strcpy( cNewLobbyProc, SRS_PROC_LOBBY );	// プロセス固定名設定
	sprintf( cPort, "%04d", iPort );
	strcat( cNewLobbyProc, cPort );
	strcat( cNewLobbyProc, ".exe" );
	//=======================================
	// プロセス名変更
	//=======================================
	memset( cLobbyProc, 0, 256 );
	strcpy( cLobbyProc, SRS_PROC_LOBBY );		// 元プロセス名設定
	strcat( cLobbyProc, ".exe" );

	fRtn = DeleteFile( cNewLobbyProc );
	if( fRtn == FALSE )
	{
		dwRtn = GetLastError( );
		if( dwRtn != ERROR_FILE_NOT_FOUND )
		{
//			sprintf( cMsg, "DeleteFile error %d %s", dwRtn, cNewLobbyProc );
//			SRS_Dbg_WriteLog( cMsg );
			iRtn = SRS_Ini_TermProc( iPort );		// Lobbyプロセス強制終了
			return( -1 );
		}
	}

	fRtn = CopyFile( cLobbyProc, cNewLobbyProc, TRUE );
	if( fRtn == FALSE )		// 変更失敗？
    {
//		dwRtn = GetLastError( );
//		sprintf( cMsg, "CopyFile error %d %s %s", dwRtn, cLobbyProc, cNewLobbyProc );
//		SRS_Dbg_WriteLog( cMsg );
		return( -1 );
	}
	//=======================================
	// プロセス起動（未完了型）
	//=======================================
	sprintf( cMsg, "SRS_Ini_CreateProc %s", cNewLobbyProc );
	iRtn = SRS_Ini_CreateProc( SRS_CREATE_ASYNC, cNewLobbyProc );
	return( iRtn );
}
/*====================================================================
     関数   ：プロセス生成（指定プロセスを起動する）
	 入力   ：iMode				プロセス生成モード
								SRS_CREATE_SYNC  : 同期  （完了復帰）
								SRS_CREATE_ASYNC : 非同期（未完了復帰）
			  lpstrCommandLine  コマンドライン
　   出力   ：なし
　   戻り値 ： 0  (正常)
              -1  (異常)

====================================================================*/
int SRS_Ini_CreateProc( int iMode, char *lpCommandLine )
{
	BOOL    cprc;								// 復帰値
	STARTUPINFO StartInfo;   					// 起動情報域
    PROCESS_INFORMATION ProcInfo;				// プロセス情報域

	DWORD	dwExitCode;							// 終了状態を受け取るアドレス
	//
	// CreateProcessパラメタ
	//
    LPCTSTR lpszImageName = NULL;				// モジュール名のアドレス
	LPCTSTR lpszCommandLine;					// コマンドラインのアドレス
    LPSECURITY_ATTRIBUTES lpsaProcess = NULL;	// プロセスセキュリティ属性のアドレス
    LPSECURITY_ATTRIBUTES lpsaThread = NULL;	// スレッドセキュリティ属性のアドレス
    BOOL fInheritHandles = TRUE;				// 新プロセスのハンドル継承
    DWORD fdwCreate = 0;						// 作成フラグ
    LPVOID lpvEnvironment = NULL;				// 新環境ブロックアドレス
    LPCTSTR lpszCurDir = NULL;					// 現ディレクトリ名アドレス
    LPSTARTUPINFO lpsiStartInfo = &StartInfo;	// STARTUPINFOのアドレス
    LPPROCESS_INFORMATION lppiProcInfo =		// プロセス情報域のアドレス
									 &ProcInfo;
	//
	// コマンドライン設定
	//
	lpszCommandLine = lpCommandLine;			// コマンドラインアドレス設定
	//
	//  起動情報設定
	//
    ZeroMemory(&StartInfo, sizeof(StartInfo));	// 起動情報域初期化
    StartInfo.cb = sizeof(StartInfo);			// 起動情報域サイズ設定
    StartInfo.lpReserved = NULL;				// 
    StartInfo.lpDesktop = NULL;					// デスクトップ名指定なし
    StartInfo.lpTitle = NULL;					// タイトル表示なし
    StartInfo.dwFlags = STARTF_USESHOWWINDOW;	// wShowWindow有効
    StartInfo.wShowWindow = SW_HIDE;			// ウィンドウ非表示
    StartInfo.cbReserved2 = 0;					//
    StartInfo.lpReserved2 = NULL;				//
	//
	// プロセス生成（起動）
	//
    cprc = CreateProcess( lpszImageName,
                		  (char *)lpszCommandLine,
                          lpsaProcess,
                          lpsaThread,
                          fInheritHandles,
                          fdwCreate,
                          lpvEnvironment,
                          lpszCurDir,
                          lpsiStartInfo,
                          lppiProcInfo );
    if ( cprc == TRUE )						// 生成成功？
	{
		if( iMode == SRS_CREATE_SYNC )		// 同期モード？
    	{
			//
			// 完了待ち
			//
			dwExitCode = STILL_ACTIVE;
			while( dwExitCode == STILL_ACTIVE )
			{
   				WaitForSingleObject( ProcInfo.hProcess, INFINITE );
				GetExitCodeProcess( ProcInfo.hProcess, &dwExitCode );
				if( dwExitCode != 0 )
				{
			    	return( -1 );
				}
			}
		}
		return( 0 );
    }
    return( -1 );
}
/*=============================================================================
     関数   ：Lobbyプロセス強制終了
			（Lobbyプロセスの強制終了をおこなう）
     入力   ：iPort	（ポート番号）
     出力   ：なし
     戻り値 ：正常 0
              異常 -1

==============================================================================*/
int SRS_Ini_TermProc( int iPort )
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
	iResult = WSAStartup( wVersionRequested, &wsaData );
	if ( iResult != 0 )
	{
//		iResult = WSAGetLastError();
//		sprintf( cMsg, "SRS_Ini_TermProc : WSAStartup error:%d", iResult );
//		SRS_Dbg_WriteLog( cMsg );
		return( -1 );
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
//		iResult = WSAGetLastError();
//		sprintf( cMsg, "SRS_Ini_TermProc : bind error:%d", iResult );
//		SRS_Dbg_WriteLog( cMsg );

		iResult = closesocket(ServerSd);
		return( -1 );
	}
	// アドレス構造体にサーバアドレス情報を書き込む
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(iPort);
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
//				sprintf( cMsg, "SRS_Ini_TermProc : IP error:Sock[%d.%d.%d.%d] Reg[%d.%d.%d.%d]", (ServerAddr.sin_addr.s_addr & 0xff), ((ServerAddr.sin_addr.s_addr >> 8) & 0xff), ((ServerAddr.sin_addr.s_addr >> 16) & 0xff), ((ServerAddr.sin_addr.s_addr >> 24) & 0xff), (ip & 0xff), ((ip >> 8) & 0xff), ((ip >> 16) & 0xff), ((ip >> 24) & 0xff) );
//				SRS_Dbg_WriteLog( cMsg );
				ServerAddr.sin_addr.s_addr = ip;
			}
		}
	}
		
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

//			SRS_Dbg_WriteLog( "SRS_Ini_TermProc : select" );
			iResult = select(0, NULL, lpWriteFds, NULL, lpConnectTime);

			//　タイムアウトまたはエラーの場合
			if( (iResult == 0) || (iResult == SOCKET_ERROR) )
			{
//				sprintf( cMsg, "SRS_Ini_TermProc : select error %d", iResult );
//				SRS_Dbg_WriteLog( cMsg );
				iResult = closesocket(ServerSd);
				return( -1 );
			}
		}
		else
		{
			// ブロック以外のエラー
//			sprintf( cMsg, "SRS_Ini_TermProc : connect error %d", iResult );
//			SRS_Dbg_WriteLog( cMsg );
			iResult = closesocket(ServerSd);
			return( -1 );
		}
	}

	/*==================================*/
	/* 要求送信				  			*/
	/*==================================*/
	//　要求作成
	memset( cIfFix, 0, 256 );
	lpIfFix = (struct SRS_IF_FIX *)cIfFix;
	lpIfFix->IF_wRequest = IF_REQ_TERMINATE;	// 終了通知

	//  要求送信
	iSendLen = 0;
	do
	{
		iSendData = send( ServerSd, (char*)cIfFix, SRS_IF_FIX_SZ, 0 );
		iSendLen += iSendData;								
	}while( (iSendData != SOCKET_ERROR) && (iSendLen != SRS_IF_FIX_SZ) );

	if ( iSendData == SOCKET_ERROR )
	{
//		iResult = WSAGetLastError();
//		sprintf( cMsg,"SRS_Ini_TermProc : Send error :%d", iResult );
//		SRS_Dbg_WriteLog( cMsg );
		closesocket( ServerSd );
		return( -1 );
	}

	/*==================================*/
	/* 要求到達チェック  				*/
	/*==================================*/
	// クライアント側がコネクションを解放するまで待つ
	iResult = recv( ServerSd, cDummyBuff, 16, 0 );

//	SRS_Dbg_WriteLog( "SRS_Ini_TermProc OK" );
	closesocket( ServerSd );

	return( 0 );
}