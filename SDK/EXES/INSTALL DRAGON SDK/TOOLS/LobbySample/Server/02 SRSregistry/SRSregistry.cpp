/***************************************************************************
 *
 *  Copyright (C) 1999 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       SRSregistry.cpp
 *                	SRS_Reg_GetInfo	      : レジストリ項目（キャラクタ）参照
 *                	SRS_Reg_SetInfo	      : レジストリ項目（キャラクタ）設定
 *                	SRS_Reg_GetInfoBinary : レジストリ項目（バイナリ）参照
 *                	SRS_Reg_SetInfoBinary : レジストリ項目（バイナリ）設定
 *                	SRS_Reg_GetInfoDWORD  : レジストリ項目（DWORD）参照
 *                	SRS_Reg_SetInfoDWORD  : レジストリ項目（DWORD）設定
 *                  SRS_Reg_GetLobbyInfo  : レジストリ項目（ロビー情報）参照
 *                  SRS_Reg_GetGameInfo   : レジストリ項目（ゲーム情報）参照
 *                  SRS_Reg_GetComInfo    : レジストリ項目（共通情報）参照
 *                  SRS_Reg_Log           : ログ情報通知
 *
 *  Content:    Lobby server & Lobby Client common tools 
 *
 ***************************************************************************/
//================================
// インクルード      
//================================
#include <windows.h>
#include <stdio.h>

#include "SRScom.h"
#include "SRSdebug.h"
#include "SRSregistry.h"

//=================================
// ローカル関数
//=================================
WORD SRS_Reg_STRINGtoWORD( char *lpBuff );

/*=============================================================================
     関数   ：レジストリ情報設定
			（指定されたレジストリ内に文字列情報を設定する）

     入力   ：lpRegKey（設定レジストリキー）
			  lpReg   （設定レジストリ項目）
			  lpBuff  （設定情報格納域ポインタ）

     出力   ：なし

     戻り値 ：正常 0
              異常 -1

==============================================================================*/
__declspec( dllexport )int __stdcall SRS_Reg_SetInfo( char *lpRegKey,char *lpReg,char *lpBuff )
{
    LONG    lRtn=0;                     // LONG型復帰値
	DWORD	dwRtn;
    HKEY    hKey;                       // 問い合わせるキーのハンドル
    DWORD   dwDisposition;              // 
	char	cMsg[256];

    /*==========================================*/
    /*   キーのオープン（存在しない場合は作成） */
    /*==========================================*/
    lRtn = RegCreateKeyEx( HKEY_LOCAL_MACHINE, lpRegKey, 0, NULL, 
                           REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL,
                           &hKey, &dwDisposition );    
    if( lRtn != ERROR_SUCCESS )
    {
		dwRtn = GetLastError( );
		SRS_Dbg_WriteLog( cMsg );
		sprintf( cMsg, "SRS_Reg_SetInfo : RegCreateKeyEx Error %d %s\n",dwRtn, lpRegKey ); 
		return( -1 );
    }

    /*==================================*/
    /*   値とデータの設定               */
    /*==================================*/
    lRtn = RegSetValueEx( hKey, lpReg, 0, REG_SZ, (LPBYTE)lpBuff, (strlen(lpBuff))+1 );
    if( lRtn != ERROR_SUCCESS )
    {
		dwRtn = GetLastError( );
		sprintf( cMsg, "SRS_Reg_SetInfo : RegSetValueEx Error %d %s ",dwRtn, lpReg );
		SRS_Dbg_WriteLog( cMsg );
        RegCloseKey( hKey );
        return( -1 );
    }
    RegCloseKey( hKey );
    return( 0 );
}

/*=============================================================================
     関数   ：レジストリ情報参照
			（指定されたレジストリ内の情報を参照する）

     入力   ：lpRegKey（参照レジストリキー）
			  lpReg   （参照レジストリ項目）
			  lpBuff  （結果格納域ポインタ）

     出力   ：lpRegBuff（参照結果）

     戻り値 ：正常 0
              異常 -1

==============================================================================*/
__declspec( dllexport )int __stdcall SRS_Reg_GetInfo( char *lpRegKey,char *lpReg, char *lpBuff )
{
    LONG    lRtn;                       // 
    HKEY    hKey;                       // 問い合わせるキーのハンドル
    DWORD   dwSize;                     // レジストリ参照用パラメタ
    char    cMsg[256]; 				    //

    //===========================================
    // 指定キーオープン
    //===========================================
    lRtn = RegOpenKeyEx( HKEY_LOCAL_MACHINE, lpRegKey, 0, KEY_READ, &hKey );
    if( lRtn != ERROR_SUCCESS )     // オープン失敗？
    {
        sprintf( cMsg, "SRS_Reg_GetInfo : RegOpenKeyEx Error(%d) %s", lRtn, lpRegKey );
        SRS_Dbg_WriteLog( cMsg );
        return( -1 );
    }
    dwSize = 256;
    //===========================================
    // 設定値獲得 
    //===========================================
    lRtn = RegQueryValueEx( hKey, lpReg, NULL, NULL, (unsigned char *)lpBuff, &dwSize );
    if( lRtn != ERROR_SUCCESS )         // 獲得失敗か？
    {
        // キーのハンドル解放
        RegCloseKey( hKey );
        if( lRtn == ERROR_MORE_DATA )   // バッファ長不足か？
        {
            // バッファ長不足時は必要な長さがdwSizeに入ってくる
            sprintf( cMsg, "SRS_Reg_GetInfo : MORE_DATA %d %s %s",dwSize,lpRegKey, lpReg );
        }
        else
        {
            sprintf( cMsg,"SRS_Reg_GetInfo : RegQueryValueEx Error(%d) %s %s",lRtn,lpRegKey,lpReg);
        }
        SRS_Dbg_WriteLog( cMsg );
        return( -1 );
    }
    RegCloseKey( hKey );

    return( 0 );
}

/*=============================================================================
     関数   ：レジストリ共通情報参照
			（レジストリ内の共通情報を参照する）

     入力   ：lpRegInfo（共通情報格納域ポインタ）

     出力   ：lpRegInfo（参照結果）

     戻り値 ：正常 0
              異常 -1

==============================================================================*/
__declspec( dllexport )int __stdcall SRS_Reg_GetComInfo( struct SRS_REG_INFO *lpRegInfo )
{
    LONG    lRtn;                       // 
	int		iRtn;						//
	int		iMax;						// 最大値
    HKEY    hKey;                       // 問い合わせるキーのハンドル
    DWORD   dwSize;                     // レジストリ参照用パラメタ
    char    *lpBuff;                    // レジストリ参照用パラメタ
    char    cBuff[8];	 			    //
    char    cMsg[256]; 				    //

    //===========================================
    // 共通情報オープン
    //===========================================
    lRtn = RegOpenKeyEx( HKEY_LOCAL_MACHINE, SRS_REG_KEY_COM, 0, KEY_READ, &hKey );
    if( lRtn != ERROR_SUCCESS )     // オープン失敗？
    {
        sprintf( cMsg, "SRS_Reg_GetCominfo : RegOpenKeyEx Error(%d) %s", lRtn, SRS_REG_KEY_COM );
        SRS_Dbg_WriteLog( cMsg );
        return( -1 );
    }
	lpBuff = cBuff;

    //===========================================
    // 最大登録ユーザ数参照 
    //===========================================

	memset( cBuff, 0, sizeof(cBuff) );
    dwSize = (DWORD)sizeof(cBuff);
    lRtn = RegQueryValueEx( hKey,SRS_REG_MAXUSER,NULL,NULL,(unsigned char *)lpBuff, &dwSize );
    if( lRtn != ERROR_SUCCESS )         // 獲得失敗か？
    {
        // キーのハンドル解放
        RegCloseKey( hKey );
        if( lRtn == ERROR_MORE_DATA )   // バッファ長不足か？
        {
            // バッファ長不足時は必要な長さがdwSizeに入ってくる
            sprintf( cMsg, "SRS_Reg_GetComInfo : MORE_DATA %d %s %s",
												dwSize,SRS_REG_KEY_COM, SRS_REG_MAXUSER );
        }
        else
        {
            sprintf( cMsg, "SRS_Reg_GetComInfo : RegQueryValueEx Error(%d) %s %s",
												 lRtn,SRS_REG_KEY_COM, SRS_REG_MAXUSER );
        }
        SRS_Dbg_WriteLog( cMsg );
        return( -1 );
    }
	iRtn = sscanf( lpBuff, "%d", &iMax );
	lpRegInfo->wMaxUser = (WORD)iMax;			// 最大登録ユーザ数設定

    //===========================================
    // 最大登録ロビー数参照 
    //===========================================
	memset( cBuff, 0, sizeof(cBuff) );
    dwSize = (DWORD)sizeof(cBuff);
    lRtn = RegQueryValueEx( hKey,SRS_REG_MAXLOBBY,NULL,NULL,(unsigned char *)lpBuff, &dwSize );
    if( lRtn != ERROR_SUCCESS )         // 獲得失敗か？
    {
        // キーのハンドル解放
        RegCloseKey( hKey );
        if( lRtn == ERROR_MORE_DATA )   // バッファ長不足か？
        {
            // バッファ長不足時は必要な長さがdwSizeに入ってくる
            sprintf( cMsg, "SRS_Reg_GetComInfo : MORE_DATA %d %s %s",
												dwSize,SRS_REG_KEY_COM, SRS_REG_MAXLOBBY );
        }
        else
        {
            sprintf( cMsg, "SRS_Reg_GetComInfo : RegQueryValueEx Error(%d) %s %s",
												 lRtn,SRS_REG_KEY_COM, SRS_REG_MAXLOBBY );
        }
        SRS_Dbg_WriteLog( cMsg );
        return( -1 );
    }
	iRtn = sscanf( lpBuff, "%d", &iMax );
	lpRegInfo->wMaxLobby = (WORD)iMax;			// 最大登録ロビー数設定

    //===========================================
    // 最大登録ゲーム数参照 
    //===========================================
	memset( cBuff, 0, sizeof(cBuff) );
    dwSize = sizeof(cBuff);
    lRtn = RegQueryValueEx( hKey,SRS_REG_MAXGAME,NULL,NULL,(unsigned char *)lpBuff, &dwSize );
    if( lRtn != ERROR_SUCCESS )         // 獲得失敗か？
    {
        // キーのハンドル解放
        RegCloseKey( hKey );
        if( lRtn == ERROR_MORE_DATA )   // バッファ長不足か？
        {
            // バッファ長不足時は必要な長さがdwSizeに入ってくる
            sprintf( cMsg, "SRS_Reg_GetComInfo : MORE_DATA %d %s %s",
												dwSize,SRS_REG_KEY_COM, SRS_REG_MAXGAME );
        }
        else
        {
            sprintf( cMsg, "SRS_Reg_GetComInfo : RegQueryValueEx Error(%d) %s %s",
												 lRtn,SRS_REG_KEY_COM, SRS_REG_MAXGAME );
        }
        SRS_Dbg_WriteLog( cMsg );
        return( -1 );
    }
	iRtn = sscanf( lpBuff, "%d", &iMax );
	lpRegInfo->wMaxGame = (WORD)iMax;			// 最大登録ゲーム数設定

    //===========================================
    // 最大登録グループ数参照 
    //===========================================
	memset( cBuff, 0, sizeof(cBuff) );
    dwSize = sizeof(cBuff);
    lRtn = RegQueryValueEx( hKey,SRS_REG_MAXGROUP,NULL,NULL,(unsigned char *)lpBuff, &dwSize );
    if( lRtn != ERROR_SUCCESS )         // 獲得失敗か？
    {
        // キーのハンドル解放
        RegCloseKey( hKey );
        if( lRtn == ERROR_MORE_DATA )   // バッファ長不足か？
        {
            // バッファ長不足時は必要な長さがdwSizeに入ってくる
            sprintf( cMsg, "SRS_Reg_GetComInfo : MORE_DATA %d %s %s",
												dwSize,SRS_REG_KEY_COM, SRS_REG_MAXGROUP );
        }
        else
        {
            sprintf( cMsg, "SRS_Reg_GetComInfo : RegQueryValueEx Error(%d) %s %s",
												 lRtn,SRS_REG_KEY_COM, SRS_REG_MAXGROUP );
        }
        SRS_Dbg_WriteLog( cMsg );
        return( -1 );
    }
	iRtn = sscanf( lpBuff, "%d", &iMax );
	lpRegInfo->wMaxGroup = (WORD)iMax;			// 最大登録グループ数設定

    RegCloseKey( hKey );

    return( 0 );
}

/*=============================================================================
     関数    ：レジストリロビー固有情報参照
			 （レジストリ内のロビー固有情報を参照する）

     入力    ：lpRegInfoLobby（ロビー固有情報格納域ポインタ）
               iCount        （最大ロビー数）
     出力    ：lpRegInfoLobby（参照結果：ロビー固有情報 x 最大ロビー数）

     戻り値  ：正常 0
               異常 -1
 	 特記事項：格納域サイズは、”１ロビー固有情報域 x 最大ロビー数”分以上を
               保証する事

==============================================================================*/
__declspec( dllexport )int __stdcall SRS_Reg_GetLobbyInfo( int iCount, 
                                     struct SRS_REG_INFO_LOBBY *lpRegInfoLobby )
{
    LONG    lRtn;                       //
	int		iRtn;						//
	int		iLoop;						//
	WORD	wMax;						// 最大人数
    HKEY    hKey;                       // 問い合わせるキーのハンドル
    DWORD   dwSize;                     // レジストリ参照用パラメタ
    char    *lpBuff;                    // レジストリ参照用パラメタ
    char    cBuff[256]; 			    //
	char	cKeyLobby[256];				//
    char    cMsg[256]; 				    //
	struct	SRS_REG_INFO_LOBBY *lpLobbyInfo;
	
	//=========================================
	//  全Lobby固有情報獲得
	//=========================================
	lpLobbyInfo = lpRegInfoLobby;
	for( iLoop = 0 ; iLoop < iCount;  )
	{
		memset( cKeyLobby, 0, sizeof(cKeyLobby));
		strcpy( cKeyLobby, SRS_REG_KEY_LOBBY );
		sprintf( cMsg, "%d",iLoop + 1 );
		strcat( cKeyLobby, cMsg );		// ロビー固有情報キー作成
	    //===========================================
    	// LOBBY固有情報オープン
    	//===========================================
    	lRtn = RegOpenKeyEx( HKEY_LOCAL_MACHINE, cKeyLobby, 0, KEY_READ, &hKey );
    	if( lRtn != ERROR_SUCCESS )    				// オープン失敗？
   	 	{
    	    sprintf( cMsg, "SRS_Reg_GetLobbyInfo : RegOpenKeyEx Error(%d) %s", lRtn, cKeyLobby );
    	    SRS_Dbg_WriteLog( cMsg );
        	return( -1 );
		}
		lpBuff = cBuff;
   		dwSize = sizeof(cBuff);

    	//===========================================
    	// ロビー名参照 
    	//===========================================
		memset( cBuff, 0, sizeof(cBuff));
    	lRtn = RegQueryValueEx( hKey,SRS_REG_NAME,NULL,NULL,(unsigned char *)lpBuff, &dwSize );
    	if( lRtn != ERROR_SUCCESS )         // 獲得失敗か？
   	 	{
    	    // キーのハンドル解放
        	RegCloseKey( hKey );
        	if( lRtn == ERROR_MORE_DATA )   // バッファ長不足か？
        	{
            	// バッファ長不足時は必要な長さがdwSizeに入ってくる
            	sprintf( cMsg, "SRS_Reg_GetLobbyInfo : MORE_DATA %d %s %s",
												dwSize, cKeyLobby, SRS_REG_NAME );
        	}
        	else
       	 	{
            	sprintf( cMsg, "SRS_Reg_GetLobbyInfo : RegQueryValueEx Error(%d) %s %s",
												 lRtn, cKeyLobby, SRS_REG_NAME );
	        }
    	    SRS_Dbg_WriteLog( cMsg );
        	return( -1 );
    	}
		memset( lpLobbyInfo->cName, 0, SRS_MAX_NAME_LOBBY );
		strcpy( lpLobbyInfo->cName, lpBuff );		// ロビー名設定

    	//===========================================
    	// 最大ロビー内人数参照 
    	//===========================================
		memset( cBuff, 0, sizeof(cBuff) );
    	lRtn = RegQueryValueEx( hKey,SRS_REG_MAXENTRY,NULL,NULL,(unsigned char *)lpBuff, &dwSize );
    	if( lRtn != ERROR_SUCCESS )         // 獲得失敗か？
    	{
        	// キーのハンドル解放
        	RegCloseKey( hKey );
        	if( lRtn == ERROR_MORE_DATA )   // バッファ長不足か？
        	{
           		// バッファ長不足時は必要な長さがdwSizeに入ってくる
            	sprintf( cMsg, "SRS_Reg_GetLobbyInfo : MORE_DATA %d %s %s",
												dwSize, cKeyLobby, SRS_REG_MAXENTRY );
       		}
        	else
        	{
            	sprintf( cMsg, "SRS_Reg_GetLobbyInfo : RegQueryValueEx Error(%d) %s %s",
												 lRtn, cKeyLobby, SRS_REG_MAXENTRY );
        	}
        	SRS_Dbg_WriteLog( cMsg );
        	return( -1 );
    	}
		iRtn = sscanf( lpBuff, "%d", &wMax );
		lpLobbyInfo->wMaxUser = wMax;			// 最大ロビー内人数設定
	    RegCloseKey( hKey );
		lpLobbyInfo = lpLobbyInfo + 1;				// 情報域ポイント更新
		iLoop++;
	}
    return( 0 );
}
/*=============================================================================
     関数    ：レジストリゲーム固有情報参照
			 （レジストリ内のゲーム固有情報を参照する）

     入力    ：lpRegInfoGame （ロビー固有情報格納域ポインタ）
               iCount        （最大ゲーム数）
     出力    ：lpRegInfoGame （参照結果：ゲーム固有情報 x 最大ゲーム数）

     戻り値  ：正常 0
               異常 -1
 	 特記事項：格納域サイズは、”１ゲーム固有情報域 x 最大ゲーム数”分以上を
               保証する事

==============================================================================*/
__declspec( dllexport )int __stdcall SRS_Reg_GetGameInfo( int iCount, 
                                     struct SRS_REG_INFO_GAME *lpRegInfoGame )
{
    LONG    lRtn;                       //
	int		iRtn;						//
	int		iLoop;						//
	WORD	wMax;						// 最大人数
    HKEY    hKey;                       // 問い合わせるキーのハンドル
    DWORD   dwSize;                     // レジストリ参照用パラメタ
    char    *lpBuff;                    // レジストリ参照用パラメタ
    char    cBuff[256]; 			    //
	char	cKeyGame[256];				//
    char    cMsg[256]; 				    //
	struct	SRS_REG_INFO_GAME *lpGameInfo;
	
	//=========================================
	//  全GAME固有情報獲得
	//=========================================
	lpGameInfo = lpRegInfoGame;
	for( iLoop = 0 ; iLoop < iCount; iLoop++ )
	{
		memset( cKeyGame, 0, sizeof(cKeyGame) );
		strcpy( cKeyGame, SRS_REG_KEY_GAME );
		sprintf( cMsg, "%d",iLoop + 1 );
		strcat( cKeyGame, cMsg );			// ゲーム固有情報キー作成
	    //===========================================
    	// GAME固有情報オープン
    	//===========================================
    	lRtn = RegOpenKeyEx( HKEY_LOCAL_MACHINE, cKeyGame, 0, KEY_READ, &hKey );
    	if( lRtn != ERROR_SUCCESS )     			// オープン失敗？
   	 	{
    	    sprintf( cMsg, "SRS_Com_GetGameInfo : RegOpenKeyEx Error(%d) %s", lRtn, cKeyGame );
    	    SRS_Dbg_WriteLog( cMsg );
        	return( -1 );
		}
		lpBuff = cBuff;
   		dwSize = 256;

    	//===========================================
    	// ゲーム名参照 
    	//===========================================
		memset( cBuff, 0, sizeof(cBuff) );
    	lRtn = RegQueryValueEx( hKey,SRS_REG_NAME,NULL,NULL,(unsigned char *)lpBuff, &dwSize );
    	if( lRtn != ERROR_SUCCESS )         // 獲得失敗か？
   	 	{
    	    // キーのハンドル解放
        	RegCloseKey( hKey );
        	if( lRtn == ERROR_MORE_DATA )   // バッファ長不足か？
        	{
            	// バッファ長不足時は必要な長さがdwSizeに入ってくる
            	sprintf( cMsg, "SRS_Com_GetGameInfo : MORE_DATA %d %s %s",
												dwSize, cKeyGame, SRS_REG_NAME );
        	}
        	else
       	 	{
            	sprintf( cMsg, "SRS_Com_GetGameInfo : RegQueryValueEx Error(%d) %s %s",
												 lRtn, cKeyGame, SRS_REG_NAME );
	        }
    	    SRS_Dbg_WriteLog( cMsg );
        	return( -1 );
    	}
		memset( lpGameInfo->cName, 0, SRS_MAX_NAME_GAME );
		strcpy( lpGameInfo->cName, lpBuff );		// ゲーム名設定

    	//===========================================
    	// 最大参加人数参照 
    	//===========================================
		memset( cBuff, 0, sizeof(cBuff) );
    	lRtn = RegQueryValueEx( hKey,SRS_REG_MAXENTRY,NULL,NULL,(unsigned char *)lpBuff, &dwSize );
    	if( lRtn != ERROR_SUCCESS )         // 獲得失敗か？
    	{
        	// キーのハンドル解放
        	RegCloseKey( hKey );
        	if( lRtn == ERROR_MORE_DATA )   // バッファ長不足か？
        	{
           		// バッファ長不足時は必要な長さがdwSizeに入ってくる
            	sprintf( cMsg, "SRS_Com_GetGameInfo : MORE_DATA %d %s %s",
												dwSize, cKeyGame, SRS_REG_MAXENTRY );
       		}
        	else
        	{
            	sprintf( cMsg, "SRS_Com_GetGameInfo : RegQueryValueEx Error(%d) %s %s",
												 lRtn, cKeyGame, SRS_REG_MAXENTRY );
        	}
        	SRS_Dbg_WriteLog( cMsg );
        	return( -1 );
    	}
		iRtn = sscanf( lpBuff, "%d", &wMax );
		lpGameInfo->wMaxUser = wMax;			// 最大参加人数設定
	    RegCloseKey( hKey );
		lpGameInfo = lpGameInfo + 1;			// 情報域ポイント更新
	}
    return( 0 );
}
/*=============================================================================
     関数   ：レジストリ情報設定（バイナリ）
			（指定されたレジストリ内に情報を設定する）

     入力   ：lpRegKey（設定レジストリキー）
			  lpReg   （設定レジストリ項目）
			  lpBuff  （設定情報格納域ポインタ）
			  dwSize  （設定有効長）

     出力   ：なし

     戻り値 ：正常 0
              異常 -1

==============================================================================*/
__declspec( dllexport )int __stdcall SRS_Reg_SetInfoBinary( char *lpRegKey, char *lpReg, char *lpBuff, DWORD dwSize )
{
    LONG    lRtn=0;                     // LONG型復帰値
	DWORD	dwRtn;
    HKEY    hKey;                       // 問い合わせるキーのハンドル
    DWORD   dwDisposition;              // 
	char	cMsg[256];

    /*==========================================*/
    /*   キーのオープン（作成） 				*/
    /*==========================================*/
    lRtn = RegCreateKeyEx( HKEY_LOCAL_MACHINE, lpRegKey, 0, NULL, 
                           REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL,
                           &hKey, &dwDisposition );    
    if( lRtn != ERROR_SUCCESS )
    {
		dwRtn = GetLastError( );
        sprintf( cMsg, "SRS_Reg_SetInfoBinary : RegQueryValueEx Error %d", dwRtn );
        SRS_Dbg_WriteLog( cMsg );
		
        return( -1 );
    }
    /*==================================*/
    /*   値とデータの設定               */
    /*==================================*/

    lRtn = RegSetValueEx( hKey, lpReg, 0, REG_BINARY, 
            (const unsigned char *)lpBuff, dwSize );
    if( lRtn != ERROR_SUCCESS )
    {
		dwRtn = GetLastError( );
        sprintf( cMsg, "SRS_Reg_SetInfoBinary : RegSetValueEx Error %d", dwRtn );
        SRS_Dbg_WriteLog( cMsg );
        RegCloseKey( hKey );
        return( -1 );
    }
    RegCloseKey( hKey );
    return( 0 );
}
/*=============================================================================
     関数   ：レジストリ情報参照（バイナリ）
			（指定されたレジストリ内の情報を参照する）

     入力   ：lpRegKey（参照レジストリキー）
			  lpReg   （参照レジストリ項目）
			  lpBuff  （結果格納域ポインタ）
			  dwSize  （格納域サイズ）

     出力   ：lpRegBuff（参照結果）

     戻り値 ：正常 0
              異常 -1

==============================================================================*/
 __declspec( dllexport )int __stdcall SRS_Reg_GetInfoBinary( char *lpRegKey,char *lpReg, char *lpBuff, DWORD dwSize )
{
    LONG    lRtn;                       // 
	DWORD	dwRtn;
    HKEY    hKey;                       // 問い合わせるキーのハンドル
	char	cMsg[256];					//

    //===========================================
    // 指定キーオープン
    //===========================================
    lRtn = RegOpenKeyEx( HKEY_LOCAL_MACHINE, lpRegKey, 0, KEY_READ, &hKey );
    if( lRtn != ERROR_SUCCESS )     // オープン失敗？
    {
		dwRtn = GetLastError();
		sprintf( cMsg, "SRS_Reg_GetInfoBinary : RegOpenKeyEx Error %d", dwRtn );
        SRS_Dbg_WriteLog( cMsg );
        return( -1 );
    }
    //===========================================
    // 設定値参照 
    //===========================================
    lRtn = RegQueryValueEx( hKey, lpReg, NULL, NULL, (unsigned char *)lpBuff, &dwSize );
    if( lRtn != ERROR_SUCCESS )         // 獲得失敗か？
    {
        // キーのハンドル解放
        RegCloseKey( hKey );
        if( lRtn == ERROR_MORE_DATA )   // バッファ長不足か？
        {
            // バッファ長不足時は必要な長さがdwSizeに入ってくる
            sprintf( cMsg, "SRS_Reg_GetInfoBinary : MORE_DATA %d", dwSize );
            SRS_Dbg_WriteLog( cMsg );
        }
        else
        {
			dwRtn = GetLastError();
            sprintf( cMsg,"SRS_Reg_GetInfoBinary : RegQueryValueEx Error %d",dwRtn );
			SRS_Dbg_WriteLog( cMsg );
        }
        return( -1 );
    }
    RegCloseKey( hKey );

    return( 0 );
}

/*=============================================================================
     関数   ：レジストリ情報設定（ＤＷＯＲＤ）
			（指定されたレジストリ内にＤＷＯＲＤ情報を設定する）

     入力   ：lpRegKey（設定レジストリキー）
			  lpReg   （設定レジストリ項目）
			  dwInfo  （設定情報）

     出力   ：なし

     戻り値 ：正常 0
              異常 -1

==============================================================================*/
__declspec( dllexport )int __stdcall SRS_Reg_SetInfoDWORD( char *lpRegKey,
                                                           char *lpReg,
                                                           DWORD dwInfo )
{
    LONG    lRtn=0;                     // LONG型復帰値
	DWORD	dwRtn;
    HKEY    hKey;                       // 問い合わせるキーのハンドル
    DWORD   dwDisposition;              // 
	char	cMsg[256];

    /*==========================================*/
    /*   キーのオープン（作成） 				*/
    /*==========================================*/
    lRtn = RegCreateKeyEx( HKEY_LOCAL_MACHINE, lpRegKey, 0, NULL, 
                           REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL,
                           &hKey, &dwDisposition );    
    if( lRtn != ERROR_SUCCESS )
    {
		dwRtn = GetLastError( );
		sprintf( cMsg, "SRS_Reg_SetInfoDWORD : RegCreateKeyEx Error %d",dwRtn );
		SRS_Dbg_WriteLog( cMsg );
		
        return( -1 );
    }
    /*==================================*/
    /*   値とデータの設定               */
    /*==================================*/

    lRtn = RegSetValueEx( hKey, lpReg, 0, REG_DWORD, (LPBYTE)&dwInfo, (DWORD)4 );
    if( lRtn != ERROR_SUCCESS )
    {
		dwRtn = GetLastError( );
		sprintf( cMsg,"SRS_Reg_SetInfoDWORD : RegSetValueEx Error %d",dwRtn ); 
		SRS_Dbg_WriteLog( cMsg );
        RegCloseKey( hKey );
        return( -1 );
    }
    RegCloseKey( hKey );
    return( 0 );
}
/*=============================================================================
     関数   ：レジストリ情報参照（ＤＷＯＲＤ）
			（指定されたレジストリ内のＤＷＯＲＤ情報を参照する）

     入力   ：lpRegKey（参照レジストリキー）
			  lpReg   （参照レジストリ項目）

     出力   ：なし

     戻り値 ：正常 参照値
              異常 -1

==============================================================================*/
__declspec( dllexport )DWORD __stdcall SRS_Reg_GetInfoDWORD( char *lpRegKey, char *lpReg)
 {
    LONG    lRtn;                       // 
	DWORD	dwRtn;
	DWORD	dwInfo;
	DWORD	dwSize;
    HKEY    hKey;                       // 問い合わせるキーのハンドル
	char	cMsg[256];

    //===========================================
    // 指定キーオープン
    //===========================================
    lRtn = RegOpenKeyEx( HKEY_LOCAL_MACHINE, lpRegKey, 0, KEY_READ, &hKey );
    if( lRtn != ERROR_SUCCESS )     // オープン失敗？
    {
		dwRtn = GetLastError();
		sprintf( cMsg, "SRS_Reg_GetInfoDWORD : RegOpenKeyEx Error %d",dwRtn );
		SRS_Dbg_WriteLog( cMsg );
        return( -1 );
    }
    //===========================================
    // 設定値参照 
    //===========================================
	dwSize = 4;
    lRtn = RegQueryValueEx( hKey, lpReg, NULL, NULL, (LPBYTE)&dwInfo, &dwSize );
    if( lRtn != ERROR_SUCCESS )         // 獲得失敗か？
    {
        // キーのハンドル解放
        RegCloseKey( hKey );
        if( lRtn == ERROR_MORE_DATA )   // バッファ長不足か？
        {
            // バッファ長不足時は必要な長さがdwSizeに入ってくる
			sprintf( cMsg,"SRS_Reg_GetInfoDWORD : MORE_DATA %d",dwSize ); 
			SRS_Dbg_WriteLog( cMsg );
        }
        else
        {
			dwRtn = GetLastError();
			sprintf( cMsg,"SRS_Reg_GetInfoDWORD : RegQueryValueEx Error %d",dwRtn );
			SRS_Dbg_WriteLog( cMsg );
        }
        return( -1 );
    }
    RegCloseKey( hKey );

    return( dwInfo );
}

/*=============================================================================
     関数   ：SRS_Reg_Log（ログ情報を通知する）
     入力   ：lpLog（ログ情報） *ＮＵＬＬポインタの場合は終了通知（WM_DESTROY)
     出力   ：なし
     戻り値 ：０（正常）
              -1（異常）
=============================================================================*/
__declspec( dllexport )int __stdcall SRS_Reg_Log( char *lpLog )
{
	HWND	hEvent;
	int		iRtn;

	//========================================
	//  イベント通知
	//========================================
	//hEvent = FindWindow( "#32770", "SRSlog" );
	hEvent = FindWindow( "SRSLogV2", "SRSlog" );
	if( hEvent == NULL )
	{
		return( -1 );
	}
	if( lpLog == NULL )		// 終了通知？
	{
		SendMessage( hEvent, WM_DESTROY, (WPARAM)(SRS_MSG_LOG), 0 );
		return( 0 );
	}
	iRtn = SRS_Reg_SetInfo( SRS_REG_KEY_LOGGING, SRS_REG_LOGMSG, lpLog );
	if( iRtn == -1 )
	{
		return( -1 );
	}
	SendMessage( hEvent, WM_COMMAND, (WPARAM)(SRS_MSG_LOG), 0 );
	return( 0 );
}

/*=============================================================================
     関数   ：10進文字列→WORD値変換
			（指定された１０進文字列をＷＯＲＤ型に変換する）
     入力   ：lpBuff（変換文字列ポインタ）
     出力   ：なし
     戻り値 ：正常 WORD型変換値
              異常 -1

==============================================================================*/
WORD SRS_Reg_STRINGtoWORD( char *lpBuff )
{
	int		iStrLen;
	int		i;
	WORD	wValue;
	WORD	wTotalValue;
	char	cNo;
	char	cString[256];

	memset( cString, 0, 256 );
	iStrLen = strlen( lpBuff );			// 文字数
	memcpy( cString, lpBuff, iStrLen );
	wTotalValue = 0;
	for( i = 1 ; iStrLen > 0 ; i = i * 10 )
	{
		iStrLen --;
		cNo = cString[iStrLen];
		cNo = cNo - 0x30;
		wValue = (WORD)cNo * i;
		wTotalValue = wTotalValue + wValue;
	}
	return( wTotalValue );
}
