#ifndef	_CRI_SAN_H_INCLUDED
#define	_CRI_SAN_H_INCLUDED
/****************************************************************************/
/*																			*/
/*			$title$ 簡易アニメーション ライブラリ							*/
/*				SAN (Simple Animation) Library								*/
/*																			*/
/*			Copyright (c) 1999 CSK Research Institute						*/
/*				1998.7.28		written by S.Hosaka							*/
/*																			*/
/****************************************************************************/

/****************************************************************************/
/*      インクルードファイル												*/
/*      Include file														*/
/****************************************************************************/

/****************************************************************************/
/*		定数マクロ															*/
/*		MACRO CONSTANT														*/
/****************************************************************************/

/*	Version No.					*/
#define	SAN_VER					"1.08"

/*	ハンドルの個数				*/
/*	Maximum number of handle	*/
#define	SAN_OBJ_MAX				(4)

/*	合成モード					*/
/*	Composite mode				*/
#define SAN_COMPO_OPEQ			(0x0000)	/*	不透明						*/
											/*	Opaque						*/
#define SAN_COMPO_TRNSP			(0x0001)	/*	透明 (頂点αのみ)			*/
											/*	Translucent					*/
#define SAN_COMPO_ADD			(0x0002)	/*	加算合成					*/
											/*	Add							*/
#define SAN_COMPO_LUMI			(0x0004)	/*	ルミネッセンス合成			*/
											/*	Luminous					*/
#define SAN_COMPO_ALPH3			(0x0005)	/*	3値アルファ合成				*/
											/*	3 step alpha				*/
#define SAN_COMPO_ALPH5			(0x0006)	/*	5値アルファ合成				*/
											/*	5 step alpha				*/
#define SAN_COMPO_ALPH256		(0x0007)	/*	フルアルファ合成			*/
											/*	256 step alpha				*/
#define SAN_COMPO_MIX			SAN_COMPO_LUMI
											/*	Mixing composite mode		*/

/*	輝度						*/
/*	Brightness					*/
#define	SAN_BRIGHT_MAX			(255)
#define	SAN_BRIGHT_MIN			(0)
#define	SAN_BRIGHT_SRF_MAX		(1.0f)
#define	SAN_BRIGHT_SRF_MIN		(0.0f)

/*	輝度のデフォルト値									*/
/*	Sofdecのデフォルト値(sfdfx_mw.hで定義)				*/
/*	Default value of brightness							*/
/*	It is same with Sofdec(definition in sfdfx_mw.h)	*/
#ifndef MWD_DFL_BRIGHT
#define MWD_DFL_BRIGHT			(0xe0)
#endif

/*	輝度オフセットのデフォルト値						*/
/*	Sofdecのデフォルト値(sfdfx_mw.hで定義)				*/
/*	Default value of brightness offset					*/
/*	It is same with Sofdec(definition in sfdfx_mw.h)	*/
#ifndef MWD_DFL_BRIGHT_OFST
#define MWD_DFL_BRIGHT_OFST		(6)
#endif

/*	表示スクリーンの奥行き	*/
/*	Depth of screen			*/
#define	SAN_DLZ_MAX				(65536.0f)	/*	奥							*/
											/*	inmost						*/
#define	SAN_DLZ_MIN				(1.0f)		/*	手前						*/
											/*	this side					*/

/*	表示スクリーンの奥行きのデフォルト値		*/
/*	Default value of screen depth				*/
#define SAN_DEF_DLZ				(65536.0f)

/****************************************************************************/
/*		列挙定数															*/
/*		Enumarate Constants													*/
/****************************************************************************/

/****************************************************************************/
/*		処理マクロ															*/
/*		Process MACRO														*/
/****************************************************************************/

/****************************************************************************/
/*		データ型															*/
/*      Data type declaration												*/
/****************************************************************************/

/*	簡易アニメーションファイルヘッダ	*/
/*	SAN file header						*/
typedef struct {
	char id_hdr[4];						/*	ヘッダチャンクID("SAN ")		*/
										/*	Header chunk ID ("SAN ")		*/
	long len_hdr;						/*	ヘッダチャンクサイズ			*/
										/*	Header chunk size				*/
	char id_fmt[4];						/*	フォーマットID					*/
										/*	Format ID						*/
	long npic;							/*	ピクチャ数						*/
										/*	Number of picture				*/
	long sx;							/*	横方向のサイズ					*/
										/*	Width of video					*/
	long sy;							/*	縦方向のサイズ					*/
										/*	Height of video					*/
	long psize;							/*	１ピクチャのバイト数			*/
										/*	Byte per picture				*/
	long vsize;							/*	映像データのバイト数			*/
										/*	Video size (byte)				*/
	long msize;							/*	マスクデータのバイト数			*/
										/*	Mask size (byte)				*/
	char mskflg;						/*	マスクデータがあるか否か		*/
										/*	Mask data flag					*/
	char valph;							/*	映像データ内のα値(0 or 3 or 5)	*/
										/*	Alpha value in video data(0/3/5)*/
	short compo_mode;					/*	合成モード						*/
										/*	Composite mode					*/
	long rsv2[4];						/*	予約領域 2						*/
										/*	Reserved						*/
	char id_dat[4];						/*	データチャンクID				*/
										/*	Data chunk ID					*/
	long len_dat;						/*	データチャンクサイズ			*/
										/*	Data chunk size (byte)			*/
	long data;							/*	データ本体						*/
										/*	Data							*/
} SAN_HDR;
typedef	SAN_HDR	*SANHDR;

/*	簡易アニメーションハンドル			*/
/*	SAN handle							*/
#ifndef SAN_DEFINED
#define SAN_DEFINED
typedef void *SAN;
#endif

/*	サーフェス情報構造体				*/
/*	Surface information					*/
typedef struct {
	void	*srf;						/*	サーフェス						*/
										/*	Surface							*/
	long	width;						/*	有効サーフェスサイズ 幅			*/
										/*	Width of valid surface			*/
	long	height;						/*	有効サーフェスサイズ 高さ		*/
										/*	Height of valid surface			*/
} SAN_PIC;

/*	エラー登録関数						*/
/*	Error entry function				*/
typedef void (*SAN_ERRFN)(void *obj, char *msg);

/****************************************************************************/
/*		変数宣言															*/
/*		Variable Declaration												*/
/****************************************************************************/

/****************************************************************************/
/*		関数の宣言															*/
/*      Function Declaration												*/
/****************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*==========================================================================*/
/*	初期化と終了処理														*/
/*	Initialize and Finalize of Library										*/
/*==========================================================================*/

/*	ライブラリの初期化						*/
/*  Initialization of library				*/
void SAN_Init(void);

/*	ライブラリの終了処理					*/
/*  Termination of library					*/
void SAN_Finish(void);

/*	ライブラリの初期化(for Kamui)			*/
/*  Initialization of library(for Kaumi)	*/
void SAN_InitKm(void);

/*	ライブラリの終了処理(for Kamui)			*/
/*  Termination of library(for Kaumi)		*/
void SAN_FinishKm(void);

/*	頂点バッファの設定	*/
/*	Set vertex buffer	*/
void SAN_SetVertexBuffer(void *vbuf);

/*==========================================================================*/
/*	基本動作																*/
/*	Basic Control															*/
/*==========================================================================*/

/*	作業領域サイズの計算					*/
/*	Calculation of working area size		*/
long SAN_CalcWorkSize(long ntex);

/*	作業領域サイズの計算(for alpha)				*/
/*	Calculation of working area size(for alpha)	*/
long SAN_CalcWorkSizeAlph(long ntex, long alph_flg);

/*	ハンドルの生成							*/
/*	Creation of Handle						*/
SAN SAN_Create(void *sandat, long ntex, void *wk);

/*	ハンドルの消去							*/
/*	Destroy of Handle						*/
void SAN_Destroy(SAN san);

/*	YUV420データのV-RAMへの転送				*/
/*	Transfer YUV420 data to V-RAM			*/
void SAN_LoadTex(SAN san, long sno, long dno);

/*	テクスチャの表示						*/
/*	Draw texture							*/
void SAN_Draw(SAN san, long dno);

/*	ピクチャ数の取得						*/
/*	Get number of picture in SAN data		*/
long SAN_GetNumPic(SAN san);

/*==========================================================================*/
/*	表示制御																*/
/*	Display Control															*/
/*==========================================================================*/

/*	表示位置の設定							*/
/*	Set location of the display				*/
void SAN_SetDispPos(SAN san, float lx, float ly);

/*	表示サイズの設定						*/
/*	Set size of the display					*/
void SAN_SetDispSize(SAN san, float sx, float sy);

/*	表示スクリーンの奥行き値の設定			*/
/*	Get Z coordinary of screen				*/
void SAN_SetDispZ(SAN san, float z);

/*	表示スクリーンの奥行き値の取得	(z:1.0-65536.0)	*/
/*	Get Z coordinary of screen	(z:1.0-65536.0)		*/
float SAN_GetDispZ(SAN san);

/*	輝度の設定 (val= 0-255)					*/
/*	Set brightness (val= 0-255)				*/
void SAN_SetDispBright(SAN san, long val);

/*	輝度の取得								*/
/*	Get brightness							*/
long SAN_GetDispBright(SAN san);

/*	輝度のオフセット設定 (val= 0-255)		*/
/*	Set brightness offset (value= 0-255)	*/
void SAN_SetDispBrightOfst(SAN san, long val);

/*	輝度オフセットの取得					*/
/*	Get brightness offset					*/
long SAN_GetDispBrightOfst(SAN san);

/*==========================================================================*/
/*	サーフェス制御															*/
/*	Surface Control															*/
/*==========================================================================*/

/*	サーフェスポイント用バッファサイズの計算	*/
/*	Calcuration size of surface point buffer 	*/
long SAN_CalcSrfBufSize(SAN san, long npnt);

/*	サーフェスポイント用バッファの設定			*/
/*	Set surface point buffer					*/
void SAN_SetSrfPntBuf(SAN san, long npnt, void *buf, long bsize);

/*	表示位置の設定								*/
/*	Set display position of surface point		*/
void SAN_SetSrfPos(SAN san, unsigned long no, float lx, float ly, float lz);

/*	表示位置の取得								*/
/*	Get display position of surface point		*/
void SAN_GetSrfPos(SAN san, unsigned long no, float *lx, float *ly, float *lz);

/*	輝度の設定									*/
/*	Set brightness of surface point				*/
void SAN_SetSrfBright(SAN san, unsigned long no,
									float a, float r, float g, float b);

/*	輝度の取得									*/
/*	Get brightness of surface point				*/
void SAN_GetSrfBright(SAN san, unsigned long no,
									float *a, float *r, float *g, float *b);

/*	輝度オフセットの設定						*/
/*	Set brightness offset of surface point		*/
void SAN_SetSrfBrightOfst(SAN san, unsigned long no,
									float a, float r, float g, float b);

/*	輝度オフセットの取得						*/
/*	Get brightness offset of surface point		*/
void SAN_GetSrfBrightOfst(SAN san, unsigned long no,
									float *a, float *r, float *g, float *b);

/*	イメージ位置の設定							*/
/*	Set image position of surface point			*/
void SAN_SetImgPos(SAN san, unsigned long no, float lx, float ly);

/*	イメージ位置の取得							*/
/*	Get image position of surface point			*/
void SAN_GetImgPos(SAN san, unsigned long no, float *lx, float *ly);

/*	イメージサイズの取得						*/
/*	Get image size								*/
void SAN_GetImgSize(SAN san, long *isx, long *isy);

/*==========================================================================*/
/*	テクスチャ																*/
/*	Texture																	*/
/*==========================================================================*/

/*	ビデオピクチャの取得	*/
void SAN_GetVideoPic(SAN san, long dno, SAN_PIC *pic);

/*	マスクピクチャの取得	*/
void SAN_GetMskPic(SAN san, long dno, SAN_PIC *pic);

/*==========================================================================*/
/*	エラー処理																*/
/*	Error																	*/
/*==========================================================================*/

/*	エラー処理関数の登録						*/
/*	Entrying function when error happened		*/
void SAN_EntryErrFunc(SAN_ERRFN errfn, void *obj);


#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif	/* _CRI_SAN_H_INCLUDED */
