/*
 *  Shinobi Library
 *  Copyright (c) 1998 SEGA
 *
 *       Peripheral
 *
 *  Module  : Library Header File
 *  File    : sg_pad.h
 *  Create  : 1998-03-25
 *  Modify  : 1999-05-27
 *  Version : 1.50
 *  Note    :
 */

#ifndef _SG_PAD_H_
#define _SG_PAD_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <sg_xpt.h>

/*
 *  DEFINES / MACROS
 */

/******** ポート番号定数 ***************************************************/
/******** Control port number **********************************************/
#define PDD_PORT_A0    0                   /* Port A0                      */
#define PDD_PORT_A1    1                   /* Port A1                      */
#define PDD_PORT_A2    2                   /* Port A2                      */
#define PDD_PORT_A3    3                   /* Port A3                      */
#define PDD_PORT_A4    4                   /* Port A4                      */
#define PDD_PORT_A5    5                   /* Port A5                      */
#define PDD_PORT_B0    6                   /* Port B0                      */
#define PDD_PORT_B1    7                   /* Port B1                      */
#define PDD_PORT_B2    8                   /* Port B2                      */
#define PDD_PORT_B3    9                   /* Port B3                      */
#define PDD_PORT_B4   10                   /* Port B4                      */
#define PDD_PORT_B5   11                   /* Port B5                      */
#define PDD_PORT_C0   12                   /* Port C0                      */
#define PDD_PORT_C1   13                   /* Port C1                      */
#define PDD_PORT_C2   14                   /* Port C2                      */
#define PDD_PORT_C3   15                   /* Port C3                      */
#define PDD_PORT_C4   16                   /* Port C4                      */
#define PDD_PORT_C5   17                   /* Port C5                      */
#define PDD_PORT_D0   18                   /* Port D0                      */
#define PDD_PORT_D1   19                   /* Port D1                      */
#define PDD_PORT_D2   20                   /* Port D2                      */
#define PDD_PORT_D3   21                   /* Port D3                      */
#define PDD_PORT_D4   22                   /* Port D4                      */
#define PDD_PORT_D5   23                   /* Port D5                      */

/******** ボタン・レバーサポート状態 ***************************************/
/******** Which button does controller have ? ******************************/
#define PDD_DEV_SUPPORT_AY2   (1 << 21)    /* アナログ軸Y2を持つ           */
                                           /* Analog axis Y2               */
#define PDD_DEV_SUPPORT_AX2   (1 << 20)    /* アナログ軸X2を持つ           */
                                           /* Analog axis X2               */
#define PDD_DEV_SUPPORT_AY1   (1 << 19)    /* アナログ軸Y1を持つ           */
                                           /* Analog axis Y1               */
#define PDD_DEV_SUPPORT_AX1   (1 << 18)    /* アナログ軸X1を持つ           */
                                           /* Analog axis X1               */
#define PDD_DEV_SUPPORT_AL    (1 << 17)    /* アナログ軸Lを持つ            */
                                           /* Analog trigger L             */
#define PDD_DEV_SUPPORT_AR    (1 << 16)    /* アナログ軸Rを持つ            */
                                           /* Analog trigger R             */
#define PDD_DEV_SUPPORT_KRB   (1 << 15)    /* デジタル十字キーB右を持つ    */
                                           /* Right button B               */
#define PDD_DEV_SUPPORT_KLB   (1 << 14)    /* デジタル十字キーB左を持つ    */
                                           /* Left button B                */
#define PDD_DEV_SUPPORT_KDB   (1 << 13)    /* デジタル十字キーB下を持つ    */
                                           /* Down button B                */
#define PDD_DEV_SUPPORT_KUB   (1 << 12)    /* デジタル十字キーB上を持つ    */
                                           /* Up button B                  */
#define PDD_DEV_SUPPORT_TD    (1 << 11)    /* Dボタンを持つ                */
                                           /* D button                     */
#define PDD_DEV_SUPPORT_TX    (1 << 10)    /* Xボタンを持つ                */
                                           /* X button                     */
#define PDD_DEV_SUPPORT_TY    (1 <<  9)    /* Yボタンを持つ                */
                                           /* Y button                     */
#define PDD_DEV_SUPPORT_TZ    (1 <<  8)    /* Zボタンを持つ                */
                                           /* Z button                     */
#define PDD_DEV_SUPPORT_KR    (1 <<  7)    /* デジタル十字キーA右を持つ    */
                                           /* Right button A               */
#define PDD_DEV_SUPPORT_KL    (1 <<  6)    /* デジタル十字キーA左を持つ    */
                                           /* Left button A                */
#define PDD_DEV_SUPPORT_KD    (1 <<  5)    /* デジタル十字キーA下を持つ    */
                                           /* Down button A                */
#define PDD_DEV_SUPPORT_KU    (1 <<  4)    /* デジタル十字キーA上を持つ    */
                                           /* UP button A                  */
#define PDD_DEV_SUPPORT_ST    (1 <<  3)    /* スタートボタンを持つ         */
                                           /* Start button                 */
#define PDD_DEV_SUPPORT_TA    (1 <<  2)    /* Aボタンを持つ                */
                                           /* A button                     */
#define PDD_DEV_SUPPORT_TB    (1 <<  1)    /* Bボタンを持つ                */
                                           /* B button                     */
#define PDD_DEV_SUPPORT_TC    (1 <<  0)    /* Cボタンを持つ                */
                                           /* C button                     */

/******** ボタン定数 *******************************************************/
/******** Button ***********************************************************/
#define PDD_DGT_TL    (1 << 17)            /* Lボタン(エミュレーション)    */
                                           /* L button(emulation)          */
#define PDD_DGT_TR    (1 << 16)            /* Rボタン(エミュレーション)    */
                                           /* R button(emulation)          */
#define PDD_DGT_KRB   (1 << 15)            /* デジタル十字キーB右          */
                                           /* Right button B               */
#define PDD_DGT_KLB   (1 << 14)            /* デジタル十字キーB左          */
                                           /* Left button B                */
#define PDD_DGT_KDB   (1 << 13)            /* デジタル十字キーB下          */
                                           /* Down button B                */
#define PDD_DGT_KUB   (1 << 12)            /* デジタル十字キーB上          */
                                           /* Up button B                  */
#define PDD_DGT_TD    (1 << 11)            /* Dボタン                      */
                                           /* D button                     */
#define PDD_DGT_TX    (1 << 10)            /* Xボタン                      */
                                           /* X button                     */
#define PDD_DGT_TY    (1 <<  9)            /* Yボタン                      */
                                           /* Y button                     */
#define PDD_DGT_TZ    (1 <<  8)            /* Zボタン                      */
                                           /* Z button                     */
#define PDD_DGT_KR    (1 <<  7)            /* デジタル十字キーA右          */
                                           /* Right button A               */
#define PDD_DGT_KL    (1 <<  6)            /* デジタル十字キーA左          */
                                           /* Left button A                */
#define PDD_DGT_KD    (1 <<  5)            /* デジタル十字キーA下          */
                                           /* Down button A                */
#define PDD_DGT_KU    (1 <<  4)            /* デジタル十字キーA上          */
                                           /* Up button A                  */
#define PDD_DGT_ST    (1 <<  3)            /* スタートボタン               */
                                           /* Start button                 */
#define PDD_DGT_TA    (1 <<  2)            /* Aボタン                      */
                                           /* A button                     */
#define PDD_DGT_TB    (1 <<  1)            /* Bボタン                      */
                                           /* B button                     */
#define PDD_DGT_TC    (1 <<  0)            /* Cボタン                      */
                                           /* C button                     */

/******** エラー定数 *******************************************************/
/******** Error code *******************************************************/
#define PDD_ERR_OK       0x00000000        /* エラーなし                   */
                                           /* No error                     */
#define PDD_ERR_RETRY    0xff0000fc        /* Transmit Againによるリトライ */
                                           /* Retry error                  */
#define PDD_ERR_GENERIC  0xff000000        /* 未定義エラー                 */
                                           /* Undefined error              */

/******** 論理モード定数 ***************************************************/
/******** Logic mode *******************************************************/
#define PDD_PLOGIC_ACTIVE    0             /* 正論理(デフォルト)           */
                                           /* Active logic(default)        */
#define PDD_PLOGIC_NEGATIVE  1             /* 負論理                       */
                                           /* Negative logic               */

/******** Maple モード定数 *************************************************/
/******** Maple mode *******************************************************/
#define PDD_MODE_TYPE_A      1             /* MapleタイプA(SET4用)         */
                                           /* Maple type A (fot SET4)      */
#define PDD_MODE_TYPE_B      0             /* MapleタイプB(SET5以降用)     */
                                           /* Maple type B (fot SET5,DC)   */

/******** ガンモード定数 ***************************************************/
/******** Gun mode *********************************************************/
#define PDD_GUNMODE_OFF   0x00000000       /* 通常モード                   */
                                           /* Normal mode (not gun mode)   */
#define PDD_GUNMODE_A     0x00000001       /* PORT Aガンモード             */
                                           /* Port A gun mode              */
#define PDD_GUNMODE_B     0x00000002       /* PORT Bガンモード             */
                                           /* Port B gun mode              */
#define PDD_GUNMODE_C     0x00000004       /* PORT Cガンモード             */
                                           /* Port C gun mode              */
#define PDD_GUNMODE_D     0x00000008       /* PORT Dガンモード             */
                                           /* Port D gun mode              */
#define PDD_GUNMODE_ALL   0x0000000f       /* 全ポートガンモード           */
                                           /* All ports gun mode           */

/******** ワーク容量計算 ***************************************************/
/******** Calculate work size **********************************************/
#define PDM_WORK_SIZE(num) ((num) * 1024 * 2)


/*
 *  PERIPHERAL INFO
 */

/******** ペリフェラルタイプ ***********************************************/
/******** Peripheral type **************************************************/
#define PDD_DEVTYPE_CONTROLLER   (1 << 0)  /* コントローラ                 */
                                           /* Controller                   */
#define PDD_DEVTYPE_STORAGE      (1 << 1)  /* ストレージ                   */
                                           /* Storage                      */
#define PDD_DEVTYPE_LCD          (1 << 2)  /* LCD                          */
                                           /* LCD                          */
#define PDD_DEVTYPE_TIMER        (1 << 3)  /* タイマ                       */
                                           /* Timer                        */
#define PDD_DEVTYPE_SOUNDINPUT   (1 << 4)  /* 音声入力                     */
                                           /* Sound input device           */
#define PDD_DEVTYPE_KEYBOARD     (1 << 6)  /* キーボード                   */
                                           /* Keyboard                     */
#define PDD_DEVTYPE_LIGHTGUN     (1 << 7)  /* ライトガン                   */
                                           /* Light gun controller         */
#define PDD_DEVTYPE_VIBRATION    (1 << 8)  /* 振動デバイス                 */
                                           /* Vibration device             */

/******** エリアコード *****************************************************/
/******** Area code ********************************************************/
#define PDD_DEVAREA_USA          (1 << 0)  /* 北アメリカ地区               */
                                           /* North America                */
#define PDD_DEVAREA_JAPAN        (1 << 1)  /* 日本地区                     */
                                           /* Japan                        */
#define PDD_DEVAREA_ASIA         (1 << 2)  /* アジア地区                   */
                                           /* Asia                         */
#define PDD_DEVAREA_EUROPE       (1 << 3)  /* ヨーロッパ地区               */
                                           /* Europe                       */
#define PDD_DEVAREA_RESERVED1    (1 << 4)  /* 予約地区1                    */
                                           /* Reserved area 1              */
#define PDD_DEVAREA_RESERVED2    (1 << 5)  /* 予約地区2                    */
                                           /* Reserved area 2              */
#define PDD_DEVAREA_RESERVED3    (1 << 6)  /* 予約地区3                    */
                                           /* Reserved area 3              */
#define PDD_DEVAREA_RESERVED4    (1 << 7)  /* 予約地区4                    */
                                           /* Reserved area 4              */

/******** コネクタの向き ***************************************************/
/******** Connector direction **********************************************/
#define PDD_CONDIR_TOPSIDE       0         /* 上                           */
                                           /* Top side                     */
#define PDD_CONDIR_BOTTOMSIDE    1         /* 下                           */
                                           /* Bottom side                  */
#define PDD_CONDIR_LEFTSIDE      2         /* 左                           */
                                           /* Left side                    */
#define PDD_CONDIR_RIGHTSIDE     3         /* 右                           */
                                           /* Right side                   */


/*
 *  TYPEDEFS
 */

/******** ペリフェラル情報構造体 *******************************************/
/******** Peripheral information structure *********************************/
typedef struct {
	Uint32 type;                /* ペリフェラルのタイプ                    */
	                            /* Peripheral type                         */
	Uint32 reserved[3];         /* 予約                                    */
	                            /* Reserved                                */
	Uint8 is_root;              /* ルートデバイスかどうかを表す            */
	                            /* Is root device ?                        */
	Uint8 area_code;            /* エリアコード                            */
	                            /* Area code                               */
	Uint8 connector_dir[2];     /* コネクタの向き                          */
	                            /* Connector direction                     */
	char product_name[32];      /* 製品名                                  */
	                            /* Product name                            */
	char license[64];           /* ライセンス                              */
	                            /* License string                          */
	Uint16 stdby_pow;           /* スタンバイ消費電流                      */
	                            /* Standby power                           */
	Uint16 max_pow;             /* 最大消費電流                            */
	                            /* Max power                               */
} PDS_PERIPHERALINFO;

/******** ペリフェラルデータ構造体 *****************************************/
/******** Peripheral structure *********************************************/
typedef struct {
	Uint32 id;                            /* デバイスID(参照しないで下さい)*/
	                                      /* Device ID(Please do not refer)*/
	Uint32 support;                       /* ボタンのサポート情報          */
	                                      /* Buttons controller has        */
	Uint32 on;                            /* 現在押されているボタン        */
	                                      /* Buttons pressed               */
	Uint32 off;                           /* 現在放されているボタン        */
	                                      /* Buttons released              */
#ifdef USE_UNION
	union {
		Uint32 push;                      /* 現在押された瞬間にあるボタン  */
		                                  /* Buttons pressed now(edge)     */
#endif
		Uint32 press;
#ifdef USE_UNION
	};
#endif
#ifdef USE_UNION
	union {
		Uint32 pull;                      /* 現在放された瞬間にあるボタン  */
		                                  /* Buttons released now(edge     */
#endif
		Uint32 release;
#ifdef USE_UNION
	};
#endif
	Uint16 r;                             /* 軸データR     (     0～255  ) */
	                                      /* R Trigger     (     0- 255  ) */
	Uint16 l;                             /* 軸データL     (     0～255  ) */
	                                      /* L Trigger     (     0- 255  ) */
	Sint16 x1;                            /* 軸データX1    (  -128～127  ) */
	                                      /* Axis X1       (  -128- 127  ) */
	Sint16 y1;                            /* 軸データY1    (  -128～127  ) */
	                                      /* Axis Y1       (  -128- 127  ) */
	Sint16 x2;                            /* 軸データX2    (  -128～127  ) */
	                                      /* Axis X2       (  -128- 127  ) */
	Sint16 y2;                            /* 軸データY2    (  -128～127  ) */
	                                      /* Axis Y2       (  -128- 127  ) */
	char* name;                           /* デバイス名称                  */
	                                      /* Controller name               */
	void* extend;                         /* 拡張データアドレス            */
	                                      /* Extended data address         */
	Uint32 old;                           /* 予約                          */
	                                      /* Reserved                      */
	PDS_PERIPHERALINFO* info;             /* ペリフェラル情報へのポインタ  */
	                                      /* Pointer to peripheral info.   */
} PDS_PERIPHERAL;


/*--------------------------------------------------------------------------*/

/*
 *  PROTOTYPES
 */

void pdInitPeripheral(Sint32 logic, void* recvbuf, void* sendbuf);
void pdInitPeripheralEx(Sint32 logic, Sint32* permap,
							void** recvbuf, void* sendbuf, Sint32 num);
void pdExitPeripheral(void);
void pdExecPeripheralServer(void);
void pdExecPeripheralServerUser(void);
const PDS_PERIPHERAL* pdGetPeripheral(Uint32 port);
Sint32 pdGetPeripheralError(Uint32 port);
const PDS_PERIPHERALINFO* pdGetPeripheralInfo(Uint32 port);
void pdSetMode(Sint32 mode);
Sint32 pdGetMode(void);
void pdSetOptimize(Uint32 count);
Uint32 pdGetOptimize(void);
void pdSetThreshold(Uint8 on, Uint8 off);

void pdSetIntFunction(void (*func)(void));
const PDS_PERIPHERAL* pdGetPeripheralDirect(Uint32 port,
					PDS_PERIPHERAL* buf, void* rawdata, void* rawinfo);


void pdGunEnter(Uint32 portbit);
void pdGunLeave(void);
Sint32 pdGunCheck(void);
void pdGunGetPosition(Sint32* x, Sint32* y);
Sint32 pdGunGetLatchedPort(void);
void pdGunSetFlashColor(Uint32 color);
Uint32 pdGunGetFlashColor(void);
void pdGunSetRapid(Uint32 port, Uint32 num);
void pdGunSetTrigger(Uint32 port);
void pdGunSetCallback(Sint32 (*func)(void));

/*--------------------------------------------------------------------------*/


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _SG_PAD_H_ */
