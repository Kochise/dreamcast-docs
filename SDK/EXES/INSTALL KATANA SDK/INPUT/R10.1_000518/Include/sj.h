#ifndef _SJ_H_INCLUDED
#define _SJ_H_INCLUDED
/****************************************************************************/
/*																			*/
/*					ストリームジョイントライブラリヘッダ					*/
/*						 SJ (Stream Joint) Library							*/
/*																			*/
/*				 1998.4.14			written by M.Oshimi						*/
/*																			*/
/****************************************************************************/

#define	SJ_VER	"5.53"		/* Version number */

/***********************************************************************
 *		処理マクロ
 *		Process MACRO
 ***********************************************************************/

/* 整数アドレスのポインタ型への変換 */
#define SJ_VOID_PTR(adr)	((void *)(adr))

/* 下位nビットをゼロにする
 * 　1,2,8,16ビットの場合、SHは、目的のレジスタだけ使用して2命令で処理
 * できるので、シフト処理にする。
 * 　3～7ビットの場合、SHは、-128までは命令コードにイミディエイトデータ
 * を格納できるので、マスク処理にする。1命令または2命令。
 * 　その他の場合、状況に応じて最適とは限らないが、シフト処理にしておく。
 */
#define SJ_OFF_LSB(val, n)	((((unsigned long)(val)) >> (n)) << (n))
#define SJ_OFF_LSB1(val)	((((unsigned long)(val)) >> (1)) << (1))
#define SJ_OFF_LSB2(val)	((((unsigned long)(val)) >> (2)) << (2))
#define SJ_OFF_LSB3(val)	(((unsigned long)(val)) & (0xfffffff8))
#define SJ_OFF_LSB4(val)	(((unsigned long)(val)) & (0xfffffff0))
#define SJ_OFF_LSB5(val)	(((unsigned long)(val)) & (0xffffffe0))
#define SJ_OFF_LSB6(val)	(((unsigned long)(val)) & (0xffffffc0))
#define SJ_OFF_LSB7(val)	(((unsigned long)(val)) & (0xffffff80))
#define SJ_OFF_LSB8(val)	((((unsigned long)(val)) >> (8)) << (8))
#define SJ_OFF_LSB16(val)	((((unsigned long)(val)) >> (16)) << (16))

/* ポインタを2,4,8,16,32byte境界まで戻す（注意：結果は(void*)型） */
#define SJ_BACK_BND2(ptr)	SJ_VOID_PTR(SJ_OFF_LSB1(ptr))
#define SJ_BACK_BND4(ptr)	SJ_VOID_PTR(SJ_OFF_LSB2(ptr))
#define SJ_BACK_BND8(ptr)	SJ_VOID_PTR(SJ_OFF_LSB3(ptr))
#define SJ_BACK_BND16(ptr)	SJ_VOID_PTR(SJ_OFF_LSB4(ptr))
#define SJ_BACK_BND32(ptr)	SJ_VOID_PTR(SJ_OFF_LSB5(ptr))

/* ポインタを2,4,8,16,32byte境界まで進める（注意：結果は(void*)型） */
#define SJ_FORE_BND2(ptr)	SJ_BACK_BND2( ((unsigned long)(ptr)) +  1)
#define SJ_FORE_BND4(ptr)	SJ_BACK_BND4( ((unsigned long)(ptr)) +  3)
#define SJ_FORE_BND8(ptr)	SJ_BACK_BND8( ((unsigned long)(ptr)) +  7)
#define SJ_FORE_BND16(ptr)	SJ_BACK_BND16(((unsigned long)(ptr)) + 15)
#define SJ_FORE_BND32(ptr)	SJ_BACK_BND32(((unsigned long)(ptr)) + 31)

/* 32byte境界の領域確保のために、領域サイズを水増しする */
#define SJ_SIZ_BND32(siz)	((siz) + 32)

/* SJバッファアドレスの32バイト境界の取得 */
#define	SJ_ADR_BND32(adr)	SJ_FORE_BND32(adr)

/* 境界内の先端と個数から終端を求める */
#define SJ_GET_ENDPOS(bgn, num)		((bgn) + (num) - 1)

/* 境界内の個数（境界値：bgn <= end） */
#define SJ_INNER_NUM(bgn, end)		((end) - (bgn) + 1)

/* 境界内の判定（境界値：bgn <= x <= end） */
#define SJ_IS_INNER(x, bgn, end) ( ((x) >= (bgn)) && ((x) <= (end)) )

/***********************************************************************
 *		データ型
 *		Data type declaration
 ***********************************************************************/

/*	データラインの定義		*/
/*	Data line definition	*/
#define	SJ_LIN_FREE	(0)			/*	データチャンクライン				*/
								/*	Data chunk line						*/
#define	SJ_LIN_DATA	(1)			/*	フリーチャンクライン				*/
								/*	Free chunk line						*/

#define SJ_ERR_FATAL		(-1)
#define SJ_ERR_INTERNAL		(-2)
#define SJ_ERR_PRM			(-3)

#ifndef UUID_DEFINED
#define UUID_DEFINED
typedef struct _UUID {
    unsigned long Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char Data4[8];
} UUID;
#define uuid_t UUID
#endif

/*	データチャンク	*/
/*	Data chunk		*/
#ifndef SJCK_DEFINED
#define SJCK_DEFINED
typedef struct {
	char *data;					/*	開始アドレス						*/
								/*	Begin address						*/
	long len;					/*	バイト数							*/
								/*	Size of chunk length				*/
} SJCK;
#endif

/*	ライブラリハンドル	*/
/*	SJ handle			*/
typedef struct {
	struct _sj_vtbl *vtbl;		/*	インタフェース						*/
								/*	Interfaces							*/
} SJ_OBJ;
#ifndef SJ_DEFINED
#define SJ_DEFINED
typedef SJ_OBJ *SJ;
#endif

/*	インタフェース関数  				*/
/*	Interface functions					*/
typedef struct _sj_vtbl {
	void (*QueryInterface)();		/*		for COM compatibility			*/
	void (*AddRef)();				/*		for COM compatibility			*/
	void (*Release)();				/*		for COM compatibility			*/
	void (*Destroy)(SJ sj);			/*		ハンドルの消去					*/
									/*		Destroys specified SJ handle	*/
	UUID *(*GetUuid)(SJ sj);		/*		UUIDの取得						*/
									/*		Get a UUID						*/
	void (*Reset)(SJ sj);			/*		リセット						*/
									/*		Resets SJ						*/
	/*	チャンクの取得	(FIFOの先頭から取得)								*/
	/*	Get a chunk	(Get chunk from top of FIFO)							*/
	void (*GetChunk)(SJ sj, long id, long nbyte, SJCK *ck);
	/*	チャンクを戻す　(FIFOの先頭に挿入)	
	/*	Unget a chunk	(Insert chunk in top of FIFO)						*/
	void (*UngetChunk)(SJ sj, long id, SJCK *ck);
	/*	チャンクを挿入	(FIFOの最後に挿入)									*/
	/*	Put a chunk	(Insert chunk in last of FIFO)						*/
	void (*PutChunk)(SJ sj, long id, SJCK *ck);
	/*	取得できるデータのバイト数の取得									*/
	/*	Get the data number which can be got								*/
	long (*GetNumData)(SJ sj, long id);
	/*	チャンクの取得可能の判定											*/
	/*	Check whether can get chunk											*/
	long (*IsGetChunk)(SJ sj, long id, long nbyte, long *rbyte);
	/*	エラー発生時に起動する関数の登録									*/
	/*	Entry error callback function										*/
	void (*EntryErrFunc)(SJ sj,
					void (*func)(void *obj, long ecode), void *obj);
} SJ_IF;
typedef SJ_IF *SJIF;

/*	ストリームジョイントの消去												*/
/*	Destroys specified SJ handle											*/
#define SJ_Destroy(sj) \
		(*(sj)->vtbl->Destroy)(sj)
/*	ストリームジョイントのリセット											*/
/*	Resets SJ																*/
#define SJ_Reset(sj) \
		(*(sj)->vtbl->Reset)(sj)
/*	チャンクの取得															*/
/*	Get a chunk																*/
#define SJ_GetChunk(sj, id, nbyte, ck) \
		(*(sj)->vtbl->GetChunk)(sj, id, nbyte, ck)
/*	チャンクを戻す															*/
/*	Unget a chunk 															*/
#define SJ_UngetChunk(sj, id, ck) \
		(*(sj)->vtbl->UngetChunk)(sj, id, ck)
/*	チャンクを挿入															*/
/*	Put a chunk																*/
#define SJ_PutChunk(sj, id, ck) \
		(*(sj)->vtbl->PutChunk)(sj, id, ck)
/*	取得可能なデータのバイト数を求める										*/
/*	Get the data number which can be got									*/
#define SJ_GetNumData(sj, id) \
		(*(sj)->vtbl->GetNumData)(sj, id)
/*	ストリームジョイントUUIDの取得 (UUIDへのアドレス)						*/
/*	Get a UUID																*/
#define SJ_GetUuid(sj) \
		(*(sj)->vtbl->GetUuid)(sj)
/*	エラー発生時に起動するコールバック関数の登録							*/
/*	Entry error callback function											*/
#define SJ_EntryErrFunc(sj, f, o) \
		(*(sj)->vtbl->EntryErrFunc)(sj, f, o)
/*	チャンクの取得可能の判定 												*/
/*	Check whether can get chunk												*/
#define SJ_IsGetChunk(sj, id, nbyte, rbyte) \
			(*(sj)->vtbl->IsGetChunk)(sj, id, nbyte, rbyte)

/****************************************************************************
 *		関数の宣言
 *		Function Declaration
 ****************************************************************************/

#ifdef		__cplusplus
extern	"C" {
#endif

/*	$func$ チャンクの分解
 * [書　式] void SJ_SplitChunk(SJCK *ck, long nbyte,
 *													SJCK *ck1, SJCK *ck2);
 * [入　力] ck		: 分解対象となるチャンク
 *			nbyte	: ck1 のバイト数
 * [出　力] ck1		: 分解された前半のチャンク
 *			ck2		: 分解された後半のチャンク
 * [関数値] ck2	チャンクのバイト数
 * [機　能] ckチャンクをck1チャンクとck2チャンクに分解する。
 *			ck1チャンクは、nbyte の長さになる。
 *			ck1チャンクの大きさが、nbyte に満たない場合は、分解されず、
 *			ck2チャンクの長さは、0となる。
 *			ck1とckは、同じものを指定しても良い。
 *			単に分解する場合は、以下のように記述する。
 *				SJCK_SplitChunk(&ck, 100, &ck, &ck2);
 *  
 * [Inputs  ] ck	: Target chunk
 *			  nbyte	: Size of ck1(byte)
 * [Outputs ] ck1	: Split chunk of the first half
 *			  ck2	: Split chunk of the latter half
 * [Return  ] None
 * [Function] Split a chunk.
 */
void SJ_SplitChunk(SJCK *ck, long nbyte, SJCK *ck1, SJCK *ck2);

/***
*		リングバッファタイプのストリームジョイント
*		Stream joint of Ring buffer types
***/

/*	初期化																	*/
/*	Initialize																*/
void SJRBF_Init(void);
/*	終了処理																*/
/*	Finish																	*/
void SJRBF_Finish(void);
/*	リングバッファの生成													*/
/*	Create a Ring buffer													*/
SJ SJRBF_Create(char *buf, long bsize, long xsize);

/***
*		メモリタイプのストリームジョイント
*		Stream joint of Memory buffer types
***/

/*	初期化																	*/
/*	Initialize																*/
void SJMEM_Init(void);
/*	終了処理																*/
/*	Finish																	*/
void SJMEM_Finish(void);
/*	メモリストリームの生成													*/
/*	Create a Memory buffer													*/
SJ SJMEM_Create(char *data, long bsize);

/***
*		汎用ストリームジョイント
*		General Stream joint		
***/

/*	チャンクの結合モード		*/
/*	Combination mode of chunk	*/
#define	SJUNI_MODE_SEPA			(0)
#define	SJUNI_MODE_JOIN			(1)

#define	SJUNI_CALC_WORK(nck)	((nck)*16)

/*	初期化																	*/
/*	Initialize																*/
void SJUNI_Init(void);
/*	終了処理																*/
/*	Finish																	*/
void SJUNI_Finish(void);
/*	汎用ストリームジョイントの生成											*/
/*	Create a Stream joint													*/
SJ SJUNI_Create(long mode, char *work, long wksize);
/*	チャンク数の取得														*/
/*	Get chunk number														*/
long SJUNI_GetNumChunk(SJ sj, long id);
/*	チェインプール数の取得													*/
/*	Get Chain pool	number													*/
long SJUNI_GetNumChainPool(SJ sj);

#if 0
/*	GetChunk関数が呼ばれたときのコールバック関数の登録						*/
void SJUNI_EntryGetFunc(SJ sj, long id, void (*f)(void *o, SJCK *ck), void *o);
/*	PutChunk関数が呼ばれたときのコールバック関数の登録						*/
void SJUNI_EntryPutFunc(SJ sj, long id, void (*f)(void *o, SJCK *ck), void *o);
/*	UngetChunk関数が呼ばれたときのコールバック関数の登録					*/
void SJUNI_EntryUngetFunc(SJ sj, long id, void (*f)(void *o, SJCK *ck), void *o);
#endif

#ifdef		__cplusplus
}
#endif

#endif     /*  #ifndef _SJ_H_INCLUDED	*/


