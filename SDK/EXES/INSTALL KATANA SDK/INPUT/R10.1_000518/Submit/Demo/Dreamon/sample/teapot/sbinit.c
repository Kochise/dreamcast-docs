/*
** sbinit.c Ver.0.60  1998/8/28
** Copyright (C) 1998 SEGA Enterprises Co.,Ltd
** All Rights Reserved
*/

#include <shinobi.h>      /* 忍ヘッダファイル                         */
#include <sg_syhw.h>      /* ハードウェア初期化ライブラリ             */

#define P1AREA   0x80000000

extern Uint8* _BSG_END;   /* BSG/BSG32セクションの終了アドレス        */

/* ワークRAMの終了アドレス                                            */
#define WORK_END (((Uint32)_BSG_END) & 0xe0000000 | 0x0d000000)




/* ここの記述は、ライブラリ使用者のシステムに合わせて                 */
/* 変更することができます。                                           */
/* 変更の際は関連ドキュメントを参照し、各項目を適切に修正してください */

/***** GDファイルシステムを使うかどうか *******************************/
#define USE_GDFS 1        /* 0...使わない                             */
                          /* 1...使う(DEFALUT)                        */

/***** Bセクションの終わりをヒープの先頭とするか **********************/
#define USE_B_END 1       /* 0...しない                               */
                          /* 1...する(DEFALUT)                        */
/* Bセクションの終わりをヒープの先頭としない場合、                    */
/* HEAP_SIZE にヒープ容量を定義してください。                         */


/* GD:同時に開くことのできる最大ファイル数 */
#define FILES 8

/* GD:カレントディレクトリバッファ */
#define BUFFERS 1024

/* syMalloc()で確保できる合計容量(約4MB)                              */
/* (Bセクションの終わりをヒープの先頭としない場合のみ有効)            */
#if !USE_B_END
#define HEAP_SIZE 0x00400000
#endif









/* グローバルワークの宣言 */

Uint8 gMapleRecvBuf[1024 * 24 * 2 + 32];
Uint8 gMapleSendBuf[1024 * 24 * 2 + 32];

#if USE_GDFS
Uint8 gdfswork[GDFS_WORK_SIZE(FILES) + 32];
Uint8 gdfscurdir[GDFS_DIRREC_SIZE(BUFFERS) + 32];
#endif

/* syMalloc()の管理下に置くヒープの先頭アドレス */
#if USE_B_END
#define HEAP_AREA ((void*)((((Uint32)_BSG_END | P1AREA) & 0xffffffe0) + 0x20))
#define HEAP_SIZE (WORK_END - (Uint32)HEAP_AREA)
#else
#define HEAP_AREA ((void*)((Uint32)WORK_END - (Uint32)HEAP_SIZE))
#endif

/*
** アプリケーションの初期化関数
** 引数はnjInitSystem()互換
*/
void sbInitSystem(Int mode, Int frame, Int count)
{
	/* 標準的な初期化処理を行います。                             */
	/* この設定で、多くのアプリケーションが最大のパフォーマンスを */
	/* 得ることができます。                                       */
	/* 特に理由のない限り、ここの記述を修正しないでください。     */
	/* 修正する場合は、各ライブラリの仕様を十分理解した上、       */
	/* ライブラリ使用者の責任において修正してください。           */

	/* 割り込み禁止 */
	set_imask(15);

	/* ハードウェアの初期化 */
	syHwInit();

	/* メモリ管理の初期化 */
	syMallocInit(HEAP_AREA, HEAP_SIZE);

	/* Ninja/Kamuiの初期化 */
	njInitSystem(mode, frame, count);

	/* ハードウェアの初期化その２ */
	syHwInit2();

	/* コントローラライブラリの初期化 */
	pdInitPeripheral(PDD_PLOGIC_ACTIVE, gMapleRecvBuf, gMapleSendBuf);

	/* RTCライブラリの初期化 */
	syRtcInit();

	/* 割り込み許可 */
	set_imask(0);

#if USE_GDFS
	/* GDファイルシステムの初期化                               */
	/* ここでは、gdFsInit()が成功するまで無限にリトライします。 */
	/* 実際のアプリケーションでは、トレイオープン等のチェックを */
	/* 必ず行ってください。                                     */
	{
		Uint8* wk;
		Uint8* dir;
		Sint32 err;

		wk  = (Uint8*)(((Uint32)gdfswork & 0xffffffe0) + 0x20);
		dir = (Uint8*)(((Uint32)gdfscurdir & 0xffffffe0) + 0x20);

		do {
			err = gdFsInit(FILES, wk, BUFFERS, dir);
		} while (err != GDD_ERR_OK);
	}
#endif

	/* その他の初期化                                           */
	/* 上にないその他のライブラリの初期化、および               */
	/* ユーザーで行うべき初期化がある場合、ここに記述できます。 */

	;

}


/*
** アプリケーションの終了関数
*/

void sbExitSystem(void)
{

#if USE_GDFS
	/* GDファイルシステムの終了処理 */
	gdFsFinish();
#endif

	/* RTCライブラリの終了処理 */
	syRtcFinish();

	/* コントローラライブラリの終了処理 */
	pdExitPeripheral();

	/* Ninja/Kamuiの終了処理 */
	njExitSystem();

	/* メモリ管理の終了処理 */
	syMallocFinish();

	/* ハードウェアの終了処理 */
	syHwFinish();

	/* 割り込み禁止 */
	set_imask(15);
}


/******************************* end of file *******************************/

