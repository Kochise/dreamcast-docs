/***************************************************************************
 *
 *  Copyright (C) 1999 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       SRScom.cpp
 *                	SRS_ComWriteData	: トレース出力
 *					SRS_ComWriteLog		: ダンプ出力
 *  Content:    Lobby server & Lobby Client debug tools
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

/*====================================================================
     関数   ：トレース出力（任意トレースをファイルに出力する）

     入力   ：lpstrMsg    出力メッセージ
     出力   ：なし
     戻り値 ：なし
====================================================================*/
__declspec( dllexport )void __stdcall SRS_Dbg_WriteLog( LPSTR lpstrMsg )
{
    size_t      szSize = 0;
    size_t      szBlock = 1;
    int         iRet = 0;
	int			iLevel = 0;
	int			iRtn;
    FILE        *fFp = (FILE *)NULL;
    SYSTEMTIME  lpst;                    /* システム時間構造体のアドレス */
	DWORD		dwDefault = 0;
	char		cFilePath[256];
    char        cDate[32];
    char        cBuff[16];

	memset( cBuff, 0, sizeof(cBuff) );
	iRtn = SRS_Dbg_GetRegDebug( cBuff );			// デバッグ情報参照
	if( strcmp(cBuff, SRS_DBG_MODE_NO) == 0 )		// 出力なし？
	{
		return;
	}
	if( (strcmp(cBuff, SRS_DBG_MODE_FILE) != 0) &&	// 未定義モード？
		(strcmp(cBuff, SRS_DBG_MODE_TRC) != 0)  &&
		(strcmp(cBuff, SRS_DBG_MODE_MSG) != 0) )
	{
		return;
	}
	if( strcmp(cBuff, SRS_DBG_MODE_MSG) == 0 )	// メッセージ表示あり？
	{
		MessageBox( NULL,lpstrMsg,"debug message", MB_OK );
	}					

	strcpy( cFilePath, OUT_FILE_LOG ); 
    fFp = fopen( cFilePath, "a");
	if( fFp == (FILE *)NULL )
		return;
	//
	//  日時設定
	//
	GetLocalTime(&lpst);
	memset( cBuff, 0, sizeof(cBuff) );
	memset( cDate, 0, sizeof(cDate) );
	itoa( lpst.wYear, cBuff, 10 );
	strcpy( cDate, cBuff );
	strcat( cDate, "." );

	memset( cBuff, 0, sizeof(cBuff) );
	itoa( lpst.wMonth, cBuff, 10 );
	if( lpst.wMonth < 10 )
		strcat( cDate, "0" );
	strcat( cDate, cBuff );
	strcat( cDate, "." );

	memset( cBuff, 0, sizeof(cBuff) );
	itoa( lpst.wDay, cBuff, 10 );
	if( lpst.wDay < 10 )
		strcat( cDate, "0" );
	strcat( cDate, cBuff );
	strcat( cDate, " " );

	memset( cBuff, 0, sizeof(cBuff) );
	itoa( lpst.wHour, cBuff, 10 );
	if( lpst.wHour < 10 )
		strcat( cDate, "0" );
	strcat( cDate, cBuff );
	strcat( cDate, ":" );

	memset( cBuff, 0, sizeof(cBuff) );
	itoa( lpst.wMinute, cBuff, 10 );
	if( lpst.wMinute < 10 )
		strcat( cDate, "0" );
	strcat( cDate, cBuff );
	strcat( cDate, ":" );

	memset( cBuff, 0, sizeof(cBuff) );
	itoa( lpst.wSecond, cBuff, 10 );
	if( lpst.wSecond < 10 )
		strcat( cDate, "0" );
	strcat( cDate, cBuff );
	strcat( cDate, " " );
	memset( cBuff, 0, sizeof(cBuff) );
	itoa( lpst.wMilliseconds, cBuff, 10 );
	if( lpst.wMilliseconds < 10 )
		strcat( cDate, "00" );
	else if( lpst.wMilliseconds < 100 )
		strcat( cDate, "0" );
	strcat( cDate, cBuff );
	strcat( cDate, "  " );     
	szSize = strlen( cDate );
	fwrite( cDate, szSize, szBlock, fFp );
	szSize = strlen( (char *)lpstrMsg );
	fwrite( (char *)lpstrMsg, szSize, szBlock, fFp );
	memset( cBuff, 0, sizeof(cBuff) );
	strcpy( cBuff, "\n" );
	fwrite( (char *)cBuff, 1, szBlock, fFp );
	
	fclose( fFp );

	return;
}

/*====================================================================
     関数   ：ダンプ出力（任意領域をファイルにバイナリ出力する）

     入力   ：lpstrTitle    タイトル
              lpstrData		出力対象域へのポインタ
			  sSize			有効長
			  lpMode		出力形式（fopen mode パラメタへの指定値）
                               "a" :追加
                               "w" :上書き
                               "b" : BINARY
							*通常は、"ab"または"wb"を指定する
    出力   ：なし
     戻り値 ：なし
====================================================================*/
__declspec( dllexport )void __stdcall SRS_Dbg_WriteData( char *lpstrTitle,
											    		 char *lpstrData,
     													 size_t sSize,
														 char *lpMode )
{
    size_t      szBlock = 1;
    int         iRet = 0;
    SYSTEMTIME  lpst;                    /* システム時間構造体のアドレス */
	FILE        *fFp = (FILE *)NULL;
	int			iLen;
	int			iLevel = 0;
	int			iRtn;
	DWORD		dwDefault = 0;
	char		cFilePath[256];
    char        cDate[32];
	char		cTitle[128];
	char		cBuff[16];

	memset( cBuff, 0, sizeof(cBuff) );
	iRtn = SRS_Dbg_GetRegDebug( cBuff );			// デバッグ情報参照
	if( (strcmp(cBuff, SRS_DBG_MODE_NO) == 0) ||	// 出力なし？
		(strcmp(cBuff, SRS_DBG_MODE_TRC) == 0) ) 
	{
		return;
	}
	if( (strcmp(cBuff, SRS_DBG_MODE_FILE) != 0) &&	// 未定義モード？
		(strcmp(cBuff, SRS_DBG_MODE_MSG) != 0) )
	{
		return;
	}
	//
	//  日時設定
	//
	GetLocalTime(&lpst);
	memset( cBuff, 0, sizeof(cBuff) );
	memset( cDate, 0, sizeof(cDate) );
	itoa( lpst.wYear, cBuff, 10 );
	strcpy( cDate, cBuff );
	strcat( cDate, "." );

	memset( cBuff, 0, sizeof(cBuff) );
	itoa( lpst.wMonth, cBuff, 10 );
	if( lpst.wMonth < 10 )
		strcat( cDate, "0" );
	strcat( cDate, cBuff );
	strcat( cDate, "." );

	memset( cBuff, 0, sizeof(cBuff) );
	itoa( lpst.wDay, cBuff, 10 );
	if( lpst.wDay < 10 )
		strcat( cDate, "0" );
	strcat( cDate, cBuff );
	strcat( cDate, " " );

	memset( cBuff, 0, sizeof(cBuff) );
	itoa( lpst.wHour, cBuff, 10 );
	if( lpst.wHour < 10 )
		strcat( cDate, "0" );
	strcat( cDate, cBuff );
	strcat( cDate, ":" );

	memset( cBuff, 0, sizeof(cBuff) );
	itoa( lpst.wMinute, cBuff, 10 );
	if( lpst.wMinute < 10 )
		strcat( cDate, "0" );
	strcat( cDate, cBuff );
	strcat( cDate, ":" );

	memset( cBuff, 0, sizeof(cBuff) );
	itoa( lpst.wSecond, cBuff, 10 );
	if( lpst.wSecond < 10 )
		strcat( cDate, "0" );
	strcat( cDate, cBuff );
	strcat( cDate, " " );
	memset( cBuff, 0, sizeof(cBuff) );
	itoa( lpst.wMilliseconds, cBuff, 10 );
	if( lpst.wMilliseconds < 10 )
		strcat( cDate, "00" );
	else if( lpst.wMilliseconds < 100 )
		strcat( cDate, "0" );
	strcat( cDate, cBuff );
	strcat( cDate, "  " );     

	//
	//  領域出力
	//
	memset( cFilePath, 0, sizeof(cFilePath) );
	strcpy( cFilePath, OUT_FILE_DATA ); 
	fFp = fopen( cFilePath, lpMode );
	if( fFp == (FILE *)NULL )
		return;
	memset( cTitle, 0, sizeof(cTitle) );
	sprintf( cTitle, "### %s %s ###", lpstrTitle, cDate );
	iLen = strlen( cTitle );
	fwrite( cTitle, iLen, szBlock, fFp );
	fwrite( lpstrData, sSize, szBlock, fFp );
	fclose( fFp );
	return;
}

/*=============================================================================
     関数   ：デバッグ情報参照
			（レジストリ内のデバッグ情報を参照する）

     入力   ：lpBuff  （結果格納域ポインタ）

     出力   ：lpRegBuff（参照結果）

     戻り値 ：正常 0
              異常 -1

==============================================================================*/
int SRS_Dbg_GetRegDebug( char *lpBuff )
{
    LONG    lRtn;                       // 
    HKEY    hKey;                       // 問い合わせるキーのハンドル
    DWORD   dwSize;                     // レジストリ参照用パラメタ

    //===========================================
    // 指定キーオープン
    //===========================================
    lRtn = RegOpenKeyEx( HKEY_LOCAL_MACHINE, SRS_REG_KEY_DEBUG, 0, KEY_READ, &hKey );
    if( lRtn != ERROR_SUCCESS )     // オープン失敗？
    {
        return( -1 );
    }
    dwSize = 256;
    //===========================================
    // 指定項目参照 
    //===========================================
    lRtn = RegQueryValueEx( hKey, SRS_REG_MODE, NULL, NULL, (unsigned char *)lpBuff, &dwSize );
    if( lRtn != ERROR_SUCCESS )         // 獲得失敗か？
    {
        // キーのハンドル解放
        RegCloseKey( hKey );
        return( -1 );
    }
    RegCloseKey( hKey );

    return( 0 );
}
