/********************************************************************
 *  Shinobi Library Sample
 *  Copyright (c) 1998 SEGA
 *
 *  Library : Controller Library
 *  Module  : Keyboard Functions
 *  File    : keyboard.h
 *  Date    : 1999-05-27
 *  Version : 1.00
 *  Note    : This file provides a middle level keyboard interface
 *            to your application.
 ********************************************************************/

#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <shinobi.h>

#define KC_ALT   0x4000
#define KC_SHIFT 0x2000
#define KC_CTRL  0x1000
#define KC_S1    0x0800
#define KC_S2    0x8000

/******** キーボード管理用構造体 *******************************************/
/******** Keyboard management structure ************************************/
typedef struct {
	Uint8 used;             /* 使用中フラグ                                */
	                        /* Used flag                                   */
	Uint8 ready;            /* キーボードが接続されているか                */
	                        /* Is keyboard connected?                      */
	Uint8 rate;             /* キーリピート間隔(フレーム数)                */
	                        /* Typematic rate(frame)                       */
	Uint8 delay;            /* リピート開始ディレイ(フレーム数)            */
	                        /* Typematic delay(frame)                      */
	Uint8 rate_count;       /* リピート用ワーク                            */
	                        /* Typematic rate work                         */
	Uint8 delay_count;      /* ディレイ用ワーク                            */
	                        /* Typematic delay work                        */
	Uint8 repeat_flag;      /* リピートフラグ                              */
	                        /* Key repeat flag                             */
	Uint8 predata;          /* 前回のキーコード                            */
	                        /* Last key code                               */
	Uint8 old_data[8];      /* 前回のキーデータ８バイト                    */
	                        /* Last raw key data (8 bytes)                 */
	Uint32 port;            /* ポート番号(PDD_PORT_A0/B0/C0/D0)            */
	                        /* Port number(PDD_PORT_A0/B0/C0/D0)           */
	Uint32 putp;            /* キーバッファ書き込みポインタ                */
	                        /* Key buffer write pointer                    */
	Uint32 getp;            /* キーバッファ読み出しポインタ                */
	                        /* Key buffer read pointer                     */
	Uint16* buf;            /* キーバッファアドレス                        */
	                        /* Key buffer address                          */
	Uint32 bufsize;         /* キーバッファサイズ                          */
	                        /* key buffer size                             */
	PDS_KEYBOARD* rawdata;  /* キーボードデータへのポインタ                */
	                        /* Raw keyboard data pointer                   */
	Uint8** keytbl;         /* キー変換テーブルへのポインタ                */
	                        /* Key conversion table pointer                */
} KEYBOARD;


/******** キーボードハンドル ***********************************************/
/******** Keyboard handle **************************************************/
typedef KEYBOARD* HKBD;


/*
 *  PROTOTYPES
 */

void KbdInit(void);
void kbdSetKeyTable(HKBD hKbs, const char** keytbl);
void KbdSetState(HKBD hKbd, Uint8 rate, Uint8 delay);
void KbdGetState(HKBD hKbd, Uint8* rate, Uint8* delay);
Sint32 KbdIsHit(HKBD hKbd);
Sint32 KbdIsReady(HKBD hKbd);
HKBD KbdCreate(Uint32 port);
void KbdDestroy(HKBD kbd);
Uint16 KbdGetChar(HKBD hKbd);
const PDS_KEYBOARD* KbdGetRawData(HKBD kbd);
void KbdServer(void);


#endif /* _KEYBOARD_H_ */
