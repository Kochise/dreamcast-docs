/*
 *  AVE-TCP 3.1 SDK source code.       
 *
 * 	at_pltfm.h
 *
 *	移植プラットフォーム依存ヘッダファイル
 *
 *	Copyright (C) 1998 ACCESS CO.,LTD.
 */

#ifdef __cplusplus	/* Support for C++ */
extern "C" {
#endif /* __cplusplus */

#ifndef AT_PLTFRM_H
#define AT_PLTFRM_H

/* サンプルプラットフォーム */

/* プラットフォーム別includeファイル */
/* #    include <memory.h>	/* memset(), memcpy() */

/* 定数の定義 */
/* #define AT_LITTLE_ENDIAN	/* バイトオーダ : コンパイル時に指定すること */

/* 
 *  データ型の定義 
 *  注: 以下は、
 *  ・void型を持ち、
 *  ・データのサイズが
 *  char: 1byte, int: 2byte, long int: 4byte
 *  のアーキテクチャを想定している。
 */

/* 基本型 */
typedef void AT_VOID;                 /* void型 */

/* 整数型 */
typedef unsigned char AT_UBYTE;       /* 8bit符号なし整数 */
typedef char AT_SBYTE;                /* 8bit符号つき整数 */
typedef unsigned short int AT_UINT16; /* 16bit符号なし整数 */
typedef short int AT_SINT16;          /* 16bit符号つき整数 */
typedef unsigned long int AT_UINT32;  /* 32bit符号なし整数 */
typedef long int AT_SINT32;           /* 32bit符号つき整数 */

/* タスク戻り値の型 */
typedef AT_VOID AT_TASK; 
#define AT_VOLATILE volatile

/* デバッグ出力 */
#define AT_DEBUG_LOG(title, fmt, arg) (title, fmt, arg) /* 評価だけ。*/

#endif /* AT_PLTFRM_H */
#ifdef __cplusplus
} /* End of extern "C" { */
#endif /* __cplusplus */
