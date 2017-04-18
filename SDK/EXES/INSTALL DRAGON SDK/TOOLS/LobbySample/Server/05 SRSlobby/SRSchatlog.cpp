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

//
//	チャットログ出力先
#define	FILE_CHATLOG		"..\\Log\\Chat%02d%02d%02d.log"

/*====================================================================
 *	ローカル関数
 ====================================================================*/
int SRS_Dbg_GetRegChatlog( char *lpBuff );

/*====================================================================
     関数   ：チャットログ出力

     入力   ：lpstrMsg    チャットメッセージ
     出力   ：なし
     戻り値 ：なし
====================================================================*/
void SRS_Chat_WriteLog(int ip, LPSTR lpstrMsg)
{
	int			iRtn;
    FILE        *fFp = (FILE *)NULL;
    SYSTEMTIME  lpst;                    /* システム時間構造体のアドレス */
	char        cLogfile[256];
    char        cDate[32];
    char        cBuff[16];
	char        *ipaddr = (char *)&ip;

	memset( cBuff, 0, sizeof(cBuff) );
	iRtn = SRS_Dbg_GetRegChatlog( cBuff );			// チャットログ情報参照
	if( strcmp(cBuff, SRS_DBG_CHATLOG_NONE) == 0 )	// 出力なし？
	{
		return;
	}

	//
	GetLocalTime(&lpst);
	
	//
	//	ログファイルの作成
	//	１日単位でログファイルを作成する
	sprintf(cLogfile, FILE_CHATLOG, lpst.wYear % 100, lpst.wMonth, lpst.wDay);
    if ((fFp = fopen(cLogfile, "a")) == NULL)
		return;
	
	//	ログフォーマット
	//	hh:mm:ss.mmm 255.255.255.0 <メッセージ>
	//	  送信時間     送信元IP
	//	メッセージの中に送信先IDを含む（仮）
	sprintf(cDate, "%02d:%02d:%02d.%03d %d.%d.%d.%d ",
	               lpst.wHour, lpst.wMinute, lpst.wSecond, lpst.wMilliseconds,
	               ipaddr[0], ipaddr[1], ipaddr[2], ipaddr[3]);

	fputs(cDate, fFp);
	fputs(lpstrMsg, fFp);
	fputc('\n', fFp);
	
	fclose( fFp );

	return;
}


/*=============================================================================
     関数   ：チャットログ情報参照
			（レジストリ内のチャットログ情報を参照する）

     入力   ：lpBuff  （結果格納域ポインタ）

     出力   ：lpRegBuff（参照結果）

     戻り値 ：正常 0
              異常 -1

==============================================================================*/
int SRS_Dbg_GetRegChatlog( char *lpBuff )
{
    LONG    lRtn;                       // 
    HKEY    hKey;                       // 問い合わせるキーのハンドル
    DWORD   dwSize;                     // レジストリ参照用パラメタ

    //===========================================
    // 指定キーオープン
    //===========================================
    lRtn = RegOpenKeyEx( HKEY_LOCAL_MACHINE, SRS_REG_KEY_CHATLOG, 0, KEY_READ, &hKey );
    if( lRtn != ERROR_SUCCESS )     // オープン失敗？
    {
        return( -1 );
    }
    dwSize = 256;
    //===========================================
    // 指定項目参照 
    //===========================================
    lRtn = RegQueryValueEx( hKey, SRS_REG_CHATLOG_MODE, NULL, NULL, (unsigned char *)lpBuff, &dwSize );
    if( lRtn != ERROR_SUCCESS )         // 獲得失敗か？
    {
        // キーのハンドル解放
        RegCloseKey( hKey );
        return( -1 );
    }
    RegCloseKey( hKey );

    return( 0 );
}
