/********************************************************************
 *  Shinobi Library Sample
 *  Copyright (c) 1998 SEGA
 *
 *  Library : Controller Library
 *  Module  : Controller distinction
 *  File    : perchk.c
 *  Date    : 1999-01-28
 *  Version : 1.01
 *  Note    :
 ********************************************************************/

#include "perchk.h"


/*===============================================================*/
/* コントローラの持っているボタン                                */
/* Which button does controller have ?                           */
/*===============================================================*/

#define BT(a)     PDD_DEV_SUPPORT_##a


/* 標準コントローラに付いているボタン */
/* Dreamcast controller               */
#define BT_CONTROLLER   (BT(TA)  | BT(TB)  | BT(TX)  | BT(TY)  | BT(ST)  | \
                         BT(KU)  | BT(KD)  | BT(KL)  | BT(KR)  | \
                         BT(AX1) | BT(AY1) | BT(AL)  | BT(AR))

/* レーシングコントローラに付いているボタン */
/* Racing controller                      */
#define BT_RACING       (BT(TA)  | BT(TB)  | BT(ST)  | \
                         BT(KU)  | BT(KD)  | BT(KL)  | BT(KR)  | \
                         BT(AX1) | BT(AL)  | BT(AR))

/* アーケードスティックに付いているボタン */
/* Arcade stick                           */
#define BT_STICK        (BT(TA)  | BT(TB)  | BT(TC)  | \
                         BT(TX)  | BT(TY)  | BT(TZ)  | BT(ST)  | \
                         BT(KU)  | BT(KD)  | BT(KL)  | BT(KR))

/* 釣りコントローラに付いているボタン */
/* Fishing controller                 */
#define BT_FISHING      (BT(TA)  | BT(TB)  | BT(TX)  | BT(TY)  | BT(ST)  | \
                         BT(KU)  | BT(KD)  | BT(KL)  | BT(KR)  | \
                         BT(AX1) | BT(AY1) | BT(AL)  | BT(AR)  | \
                         BT(AX2) | BT(AY2) | BT(AL)  | BT(AR))



/*===============================================================*/
/* ペリフェラル判別テーブル                                      */
/*   ・このテーブルにある順番どおりに、持っているボタンを判定し  */
/*     どのコントローラが接続されているかを判別します。          */
/*   ・将来ボタン数の増えたコントローラに対応するため、ボタンの  */
/*     判定は "==" で行わず、ビットマスクを取って行います。      */
/*   ・このテーブルでは、アーケードスティックを最優先で判定し、  */
/*     釣りコン、標準コントローラ、ハンドルと続きます。          */
/*   ・アプリケーションによって、このテーブルを変更する必要が    */
/*     あるでしょう。                                            */
/*   ・基本的に、ボタン数の多い（条件の厳しい）コントローラから  */
/*     判定するようなテーブルにしてください。                    */
/*   ・釣りコンは、標準コントローラにあるボタンをすべて持つため  */
/*     釣りコン対応ソフトならば標準コントローラよりも優先度を    */
/*     高く、非対応ソフトならば低くしてください。                */
/*   ・キーボード、ガンコントローラはこのテーブルとは別に判定を  */
/*     行います。                                                */
/*   ・特定アプリケーション向けの専用コントローラを判別する場合  */
/*     は、まずこのテーブルを利用した判別を行う前にペリフェラル  */
/*     名称等で専用コントローラかどうかを判別してください。専用  */
/*     コントローラでない場合は、このテーブルで判別を行って      */
/*     ください。                                                */
/*===============================================================*/

typedef struct {
	Uint32 no;                           /* Peripheral No,       */
	Uint32 button;                       /* Buttons              */
} CONTROLLER;


static const CONTROLLER ControllerTbl[] = {
	{PER_STICK,      BT_STICK},          /* Arcade Stick         */
	{PER_FISHING,    BT_FISHING},        /* Fishing Controller   */
	{PER_CONTROLLER, BT_CONTROLLER},     /* Dreamcast Controller */
	{PER_RACING,     BT_RACING},         /* Racing Controller    */
};

#define TABLE_SIZE (sizeof(ControllerTbl) / sizeof(ControllerTbl[0]))

/*===============================================================*/
/* ペリフェラルの判別                                            */
/*   ・まず未接続かどうかを判定します。次にキーボードかどうか、  */
/*     ガンコントローラかどうかを判定します。                    */
/*   ・ガンコントローラは、ライトガンとコントローラの、２つの    */
/*     タイプを併せ持ちますが、ここではライトガンタイプを見る    */
/*     ことにより判別を行っています。                            */
/*   ・コントローラタイプであった場合には、持っているボタンを    */
/*     チェックし、コントローラの種別を判別します。              */
/* Peripheral distinction                                        */
/*===============================================================*/

Sint32 CheckController(Uint32 port)
{
	const PDS_PERIPHERAL* per;
	const CONTROLLER* ctl;
	Sint32 i;

	per = pdGetPeripheral(port);

	ctl = ControllerTbl;

	if (per->info->type == 0) {
		/* 何も接続されていない     */
		/* No controller connected. */
		return PER_NONE;
	} else if (per->info->type & PDD_DEVTYPE_KEYBOARD) {
		/* キーボードだった       */
		/* Keyboard is connected. */
		return PER_KEYBOARD;
	} else if (per->info->type & PDD_DEVTYPE_LIGHTGUN) {
		/* ガンコントローラだった       */
		/* Gun controller is connected. */
		return PER_GUN;
	} else if (per->info->type & PDD_DEVTYPE_CONTROLLER) {
			/* コントローラ系だったので、ボタンを判別 */
			/* Controller is connected. Check button. */
		for (i = 0; i < TABLE_SIZE; i++, ctl++) {
			if ((per->support & ctl->button) == ctl->button) {
				return ctl->no;
			}
		}
	}

	/* テーブルにないコントローラが接続されている       */
	/* Controller which is not on a table is connected. */
	return PER_UNKNOWN;
}


