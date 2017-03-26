/*
	Ninja Library

	COPYRIGHT (C) SEGA ENTERPRISES,LTD.
*/

#ifndef _NINJAPAD_H_
#define _NINJAPAD_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <sg_pad.h>

/*
 *  DEFINES / MACROS
 */

/******** ポート番号定数 ***************************************************/
#define NJD_PORT_A0   PDD_PORT_A0              /* ポートA0                 */
#define NJD_PORT_A1   PDD_PORT_A1              /* ポートA1                 */
#define NJD_PORT_A2   PDD_PORT_A2              /* ポートA2                 */
#define NJD_PORT_A3   PDD_PORT_A3              /* ポートA3                 */
#define NJD_PORT_A4   PDD_PORT_A4              /* ポートA4                 */
#define NJD_PORT_A5   PDD_PORT_A5              /* ポートA5                 */
#define NJD_PORT_B0   PDD_PORT_B0              /* ポートB0                 */
#define NJD_PORT_B1   PDD_PORT_B1              /* ポートB1                 */
#define NJD_PORT_B2   PDD_PORT_B2              /* ポートB2                 */
#define NJD_PORT_B3   PDD_PORT_B3              /* ポートB3                 */
#define NJD_PORT_B4   PDD_PORT_B4              /* ポートB4                 */
#define NJD_PORT_B5   PDD_PORT_B5              /* ポートB5                 */
#define NJD_PORT_C0   PDD_PORT_C0              /* ポートC0                 */
#define NJD_PORT_C1   PDD_PORT_C1              /* ポートC1                 */
#define NJD_PORT_C2   PDD_PORT_C2              /* ポートC2                 */
#define NJD_PORT_C3   PDD_PORT_C3              /* ポートC3                 */
#define NJD_PORT_C4   PDD_PORT_C4              /* ポートC4                 */
#define NJD_PORT_C5   PDD_PORT_C5              /* ポートC5                 */
#define NJD_PORT_D0   PDD_PORT_D0              /* ポートD0                 */
#define NJD_PORT_D1   PDD_PORT_D1              /* ポートD1                 */
#define NJD_PORT_D2   PDD_PORT_D2              /* ポートD2                 */
#define NJD_PORT_D3   PDD_PORT_D3              /* ポートD3                 */
#define NJD_PORT_D4   PDD_PORT_D4              /* ポートD4                 */
#define NJD_PORT_D5   PDD_PORT_D5              /* ポートD5                 */

/******** ボタン・レバーサポート状態 ***************************************/
#define NJD_DEV_SUPPORT_AY2 PDD_DEV_SUPPORT_AY2 /* アナログ軸Y2を持つ      */
#define NJD_DEV_SUPPORT_AX2 PDD_DEV_SUPPORT_AX2 /* アナログ軸X2を持つ      */
#define NJD_DEV_SUPPORT_AY1 PDD_DEV_SUPPORT_AY1 /* アナログ軸Y1を持つ      */
#define NJD_DEV_SUPPORT_AX1 PDD_DEV_SUPPORT_AX1 /* アナログ軸X1を持つ      */
#define NJD_DEV_SUPPORT_AL  PDD_DEV_SUPPORT_AL  /* アナログ軸Lを持つ       */
#define NJD_DEV_SUPPORT_AR  PDD_DEV_SUPPORT_AR  /* アナログ軸Rを持つ       */
#define NJD_DEV_SUPPORT_KRB PDD_DEV_SUPPORT_KRB /* 十字キーB右を持つ       */
#define NJD_DEV_SUPPORT_KLB PDD_DEV_SUPPORT_KLB /* 十字キーB左を持つ       */
#define NJD_DEV_SUPPORT_KDB PDD_DEV_SUPPORT_KDB /* 十字キーB下を持つ       */
#define NJD_DEV_SUPPORT_KUB PDD_DEV_SUPPORT_KUB /* 十字キーB上を持つ       */
#define NJD_DEV_SUPPORT_TD  PDD_DEV_SUPPORT_TD  /* Dボタンを持つ           */
#define NJD_DEV_SUPPORT_TX  PDD_DEV_SUPPORT_TX  /* Xボタンを持つ           */
#define NJD_DEV_SUPPORT_TY  PDD_DEV_SUPPORT_TY  /* Yボタンを持つ           */
#define NJD_DEV_SUPPORT_TZ  PDD_DEV_SUPPORT_TZ  /* Zボタンを持つ           */
#define NJD_DEV_SUPPORT_KR  PDD_DEV_SUPPORT_KR  /* 十字キーA右を持つ       */
#define NJD_DEV_SUPPORT_KL  PDD_DEV_SUPPORT_KL  /* 十字キーA左を持つ       */
#define NJD_DEV_SUPPORT_KD  PDD_DEV_SUPPORT_KD  /* 十字キーA下を持つ       */
#define NJD_DEV_SUPPORT_KU  PDD_DEV_SUPPORT_KU  /* 十字キーA上を持つ       */
#define NJD_DEV_SUPPORT_ST  PDD_DEV_SUPPORT_ST  /* スタートボタンを持つ    */
#define NJD_DEV_SUPPORT_TA  PDD_DEV_SUPPORT_TA  /* Aボタンを持つ           */
#define NJD_DEV_SUPPORT_TB  PDD_DEV_SUPPORT_TB  /* Bボタンを持つ           */
#define NJD_DEV_SUPPORT_TC  PDD_DEV_SUPPORT_TC  /* Cボタンを持つ           */

/******** ボタン定数 *******************************************************/
#define NJD_DGT_TL    PDD_DGT_TL           /* Lボタン(エミュレーション)    */
#define NJD_DGT_TR    PDD_DGT_TR           /* Rボタン(エミュレーション)    */
#define NJD_DGT_KRB   PDD_DGT_KRB          /* デジタル十字キーB右          */
#define NJD_DGT_KLB   PDD_DGT_KLB          /* デジタル十字キーB左          */
#define NJD_DGT_KDB   PDD_DGT_KDB          /* デジタル十字キーB下          */
#define NJD_DGT_KUB   PDD_DGT_KUB          /* デジタル十字キーB上          */
#define NJD_DGT_TD    PDD_DGT_TD           /* Dボタン                      */
#define NJD_DGT_TX    PDD_DGT_TX           /* Xボタン                      */
#define NJD_DGT_TY    PDD_DGT_TY           /* Yボタン                      */
#define NJD_DGT_TZ    PDD_DGT_TZ           /* Zボタン                      */
#define NJD_DGT_KR    PDD_DGT_KR           /* デジタル十字キーA右          */
#define NJD_DGT_KL    PDD_DGT_KL           /* デジタル十字キーA左          */
#define NJD_DGT_KD    PDD_DGT_KD           /* デジタル十字キーA下          */
#define NJD_DGT_KU    PDD_DGT_KU           /* デジタル十字キーA上          */
#define NJD_DGT_ST    PDD_DGT_ST           /* スタートボタン               */
#define NJD_DGT_TA    PDD_DGT_TA           /* Aボタン                      */
#define NJD_DGT_TB    PDD_DGT_TB           /* Bボタン                      */
#define NJD_DGT_TC    PDD_DGT_TC           /* Cボタン                      */


/*
 *  TYPEDEFS
 */

typedef PDS_PERIPHERAL NJS_PERIPHERAL;

#if 0
/******** ペリフェラルデータ構造体 *****************************************/
typedef struct {
	Uint32 id;                            /* デバイスID                    */
	Uint32 support;                       /* ボタンのサポート情報          */
	Uint32 on;                            /* 現在押されているボタン        */
	Uint32 off;                           /* 現在放されているボタン        */
#ifdef USE_UNION
	union {
		Uint32 push;                      /* 現在押された瞬間にあるボタン  */
#endif
		Uint32 press;
#ifdef USE_UNION
	};
#endif
#ifdef USE_UNION
	union {
		Uint32 pull;                      /* 現在放された瞬間にあるボタン  */
#endif
		Uint32 release;
#ifdef USE_UNION
	};
#endif
	Uint16 r;                             /* 軸データR     (     0～255  ) */
	Uint16 l;                             /* 軸データL     (     0～255  ) */
	Sint16 x1;                            /* 軸データX1    (  -128～127  ) */
	Sint16 y1;                            /* 軸データY1    (  -128～127  ) */
	Sint16 x2;                            /* 軸データX2    (  -128～127  ) */
	Sint16 y2;                            /* 軸データY2    (  -128～127  ) */
	char* name;                           /* デバイス名称                  */
	void* extend;                         /* 拡張データアドレス            */
	Uint32 old;                           /* 予約                          */
	PDS_PERIPHERALINFO* info;             /* ペリフェラル情報へのポインタ  */
} PDS_PERIPHERAL;
#endif


#define NJD_USER_CONTINUE  0
#define NJD_USER_EXIT      (-1)

extern const NJS_PERIPHERAL* njGetPeripheral(Uint32 port);
extern void njPrintPeripheralInfo(Int loc, Uint32 port);
extern void njUserInit(void);
extern Sint32 njUserMain(void);
extern void njUserExit(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _NINJAPAD_H_ */

