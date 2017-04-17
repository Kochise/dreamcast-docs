/***************************************************************************
 *
 *  Copyright (C) 1999 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       SRLdebug.h
 *  Content:    Lobby client debug tools include
 *                                           
 ***************************************************************************/
#ifndef _SRL_DEBUG_H_
#define _SRL_DEBUG_H_

//=================================
//  動作OS
//=================================
//#define  WINCE				// Windows CE の場合に有効にする

//=================================
//  追加定義（WindowsCE用）
//=================================
#ifdef WINCE 

#include "winsock.h"
#include "winuser.h"

#undef  SW_HIDE
#define SW_HIDE 0

#undef  STARTF_USESHOWWINDOW
#define STARTF_USESHOWWINDOW 1

#undef  WM_COMMAND
#define WM_COMMAND WM_USER+10

#endif

// デバッグモード
#define SRL_DBG_TRACE_ERROR	 0					// 出力なし
#define SRL_DBG_TRACE_1  	 1					// メッセージ表示あり
#define SRL_DBG_TRACE_2  	 2					// メッセージ表示あり
#define SRL_DBG_TRACE_3  	 3					// メッセージ表示あり



/*======================
 関数宣言
======================*/
__declspec( dllexport )void __stdcall SRL_Dbg_WriteData( char *lpTitle, char *lpData, size_t sSize, char *lpMode );
__declspec( dllexport )void __stdcall SRL_Dbg_WriteLog( char *lpstrMsg );

__declspec( dllexport )void __stdcall SRL_Dbg_DebugPrintf(int iTraceLevel, IN PTCHAR pszFormat,...);
__declspec( dllexport )int __stdcall SRL_Dbg_GetRegDebug( LPCTSTR lpBuff );

// 内部関数
int  SRL_Dbg_RegGetInfoBinary( LPCTSTR lpRegKey, LPCTSTR lpReg, LPCTSTR lpBuff, DWORD dwSize );

//=================================
//  定義
//=================================
// 出力ファイル名
#define	OUT_FILE_LOG	"CLIENT_log.log"
#define	OUT_FILE_DATA	"CLIENT_data.log"

#endif
