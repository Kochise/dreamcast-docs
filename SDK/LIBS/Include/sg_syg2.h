/****************************************************
 *													*
 *	Dreamcast G2 Library							*
 *			Library Development Kit					*
 *													*
 *			Copyright 1998 (C)SEGA Enterprises		*
 *			Programmed By T.Jokagi					*
 *													*
 ****************************************************/

#ifndef	_SG_SYG2_H_
#define	_SG_SYG2_H_

#include	<sg_xpt.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*****************************************************
 *
 *	定数定義
 *
 */
#define SYD_G2_MAJOR_VER    (0x01)
#define	SYD_G2_MINOR_VER	(0x01)
#define	SYD_G2_DEBUG_VER	(0x12)
#define	SYD_G2_VER_STRING	"1.01.12"

/*****************************************************
 *
 *	データタイプ定義
 *
 */

/********************************
 *
 *	列挙体タイプ定義
 *
 */
enum SYE_G2_ERR
{
	SYE_G2_ERR_NOTHING				= 0x00000000,	/*	エラー無し  */
	SYE_G2_ERR_MODE_ILLEGAL			= 0x00010010,	/*	DMAのモード指定が以上  */
	SYE_G2_ERR_G2_ADR_NULL			= 0x00020000,	/*	G2アドレス指定がNULL  */
	SYE_G2_ERR_G2_ADR_ILLEGAL		= 0x00020001,	/*	G2アドレス指定が異常  */
	SYE_G2_ERR_ROOT_BUS_ADR_NULL	= 0x00030000,	/*	G2アドレス指定がNULL  */
	SYE_G2_ERR_ROOT_BUS_ADR_ILLEGAL	= 0x00030001,	/*	G2アドレス指定が異常  */
	SYE_G2_ERR_DMA_ALREADY_OPEN		= 0x00090101,	/*	G2 DMAは使用中  */
	SYE_G2_ERR_DMA_NOT_OPEN			= 0x00090102,	/*	G2 DMAは未使用  */
	SYE_G2_ERR_DMA_SUSPEND			= 0x00090140,	/*	G2 DMAはサスペンド中  */
	SYE_G2_ERR_DMA_BUSY				= 0x00090180,	/*	G2 DMAは動作中  */
	SYE_G2_ERR_UNKNOW				= 0x7FFFFFFF	/*	未知のエラー  */
};
typedef enum SYE_G2_ERR	SYE_G2_ERR;

enum SYE_G2_DATA_WIDTH
{
	SYE_G2_DATA_WIDTH_8BIT	= 0x01,		/*	データは8ビット幅  */
	SYE_G2_DATA_WIDTH_16BIT	= 0x02,		/*	データは16ビット幅  */
	SYE_G2_DATA_WIDTH_32BIT	= 0x04		/*	データは32ビット幅  */
};
typedef enum SYE_G2_DATA_WIDTH	SYE_G2_DATA_WIDTH;

enum SYE_G2_ADR_MODE
{
	SYE_G2_ADR_MODE_FIX,	/*	アドレス固定  */
	SYE_G2_ADR_MODE_ADD,	/*	アドレス加算  */
	SYE_G2_ADR_MODE_SUB		/*	アドレス減算  */
};
typedef enum SYE_G2_ADR_MODE	SYE_G2_ADR_MODE;

/*******************************************
 *
 *	DMAチャンネル定義
 */
enum SYE_G2_DMA_TYPE
{
	SYE_G2_DMA_TYPE_AICA,	/*	AICA DMA	*/
	SYE_G2_DMA_TYPE_EXT0,	/*	EXT0 DMA	*/
	SYE_G2_DMA_TYPE_EXT1,	/*	EXT1 DMA	*/
	SYE_G2_DMA_TYPE_DEV		/*	Dev DMA		*/
};
typedef enum SYE_G2_DMA_TYPE	SYE_G2_DMA_TYPE;

enum SYE_G2_DMA_DIR
{
	SYE_G2_DMA_DIR_ROOT_TO_G2,		/*	ルートバスからG2バス  */
	SYE_G2_DMA_DIR_G2_TO_ROOT		/*	G2バスからルートバス  */
};
typedef enum SYE_G2_DMA_DIR	SYE_G2_DMA_DIR;

enum SYE_G2_DMA_TRIGGER
{
	SYE_G2_DMA_TRIGGER_CPU = 0x00000000,	/*	CPU にてG2 DMAを起動  */
	SYE_G2_DMA_TRIGGER_INT = 0x00000002		/*	割り込み信号にてG2 DMAを起動  */
};
typedef enum SYE_G2_DMA_TRIGGER	SYE_G2_DMA_TRIGGER;

enum SYE_G2_DMA_STAT
{
	SYE_G2_DMA_STAT_STOP,		/*	止まっている  */
	SYE_G2_DMA_STAT_PROGRESS,	/*	動作中で実際に動いている  */
	SYE_G2_DMA_STAT_SUSPEND,	/*	動作中で一時停止している  */
	SYE_G2_DMA_STAT_REMAIN,		/*	まだ動いてない  */
	SYE_G2_DMA_STAT_FINISHED	/*	転送は終了  */
};
typedef enum SYE_G2_DMA_STAT	SYE_G2_DMA_STAT;

/********************************
 *
 *	単純タイプ定義
 *
 */
typedef	Void	( *SYE_G2_CALLBACK_FUNC)( Void *arg);

/********************************
 *
 *	構造体タイプ定義
 *
 */
struct SYS_G2_DMA_HANDLE
{
	Void	*m_Member;
};
typedef struct SYS_G2_DMA_HANDLE	*SYG2DMA;

struct SYS_G2_VER
{
	Sint8	m_MajorVer;	/*	メジャーバージョン  */
	Sint8	m_MinorVer;	/*	マイナーバージョン  */
	Sint8	m_DebugVer;	/*	デバグバージョン  */
	Sint8	rsv;		/*	リザーブ  */
};
typedef struct SYS_G2_VER	SYS_G2_VER;

/*****************************************************
 *
 *	プロトタイプ宣言
 *
 */
/*
 *	システムAPI
 */
/*	初期化  */
EXTERN SYE_G2_ERR	syG2SysInit( Void *prm_ptr);
/*	終了  */
EXTERN SYE_G2_ERR	syG2SysFinish( Void);
/*	バージョン取得  */
EXTERN SYE_G2_ERR	syG2SysGetVer( SYS_G2_VER *lib_ver);
/*	割込み禁止使用モード  */
EXTERN SYE_G2_ERR	syG2SysSetInterruptMask( Bool flg);
/*	ライブラリリザルトウォッチ変数登録（使えません）  */
EXTERN SYE_G2_ERR	syG2SysSetResultWatch( SYE_G2_ERR *result_watch_ptr);

/*
 *	G2コモンコントロールAPI
 */
/*	G2バスのステータス取得  */
EXTERN SYE_G2_ERR	syG2BusGetStat( Uint32 *stat);

/*
 *	SH-4での読み書きAPI
 */
/*	SH-4でのG2バスの読み込み  */
EXTERN SYE_G2_ERR	syG2Read( Void *g2_adr, Void *buf_ptr, SYE_G2_DATA_WIDTH data_width, Sint32 data_num, SYE_G2_ADR_MODE src_mode,  SYE_G2_ADR_MODE dst_mode);
/*	SH-4でのG2バスの書き込み  */
EXTERN SYE_G2_ERR	syG2Write( Void *buf_ptr, Void *g2_adr, SYE_G2_DATA_WIDTH data_width, Sint32 data_num, SYE_G2_ADR_MODE src_mode,  SYE_G2_ADR_MODE dst_mode);

/*
 *	FIFO関係API
 */
/*	AICA FIFOの状態取得  */
EXTERN SYE_G2_ERR	syG2AicaFifoIsEmpty( Bool *flg);
/*	G2 FIFOの状態取得  */
EXTERN SYE_G2_ERR	syG2FifoIsEmpty( Bool *flg);
/*	AICA FIFOのエンプティ待ち  */
EXTERN SYE_G2_ERR	syG2AicaFifoWaitEmpty( Void);
/*	AICA FIFOのエンプティ待ち回数の取得  */
EXTERN SYE_G2_ERR	syG2AicaFifoGetWaitCounter( Uint32 *count_num);
/*	G2 FIFOのエンプティ待ち  */
EXTERN SYE_G2_ERR	syG2FifoWaitEmpty( Void);
/*	G2 FIFOのエンプティ待ち回数の取得  */
EXTERN SYE_G2_ERR	syG2FifoGetWaitCounter( Uint32 *count_num);

/*
 *	G2 DMA関係API
 */
/*	G2 DMAアクセス権取得  */
EXTERN SYE_G2_ERR	syG2DmaOpen( SYG2DMA *handle, SYE_G2_DMA_TYPE);
/*	G2 DMAアクセス権開放  */
EXTERN SYE_G2_ERR	syG2DmaClose( SYG2DMA handle);
/*	G2 DMAパラメータ設定  */
EXTERN SYE_G2_ERR	syG2DmaSetPrm( SYG2DMA handle, Void *g2_adr, Void *root_bus_adr, Sint32 sz, SYE_G2_DMA_DIR dir, Bool transfer_ctl, Bool suspend_mode, SYE_G2_CALLBACK_FUNC callback, Void *callback_1st_arg);
/*	G2 DMAステータス取得  */
EXTERN SYE_G2_ERR	syG2DmaGetStat( SYG2DMA handle, SYE_G2_DMA_STAT *dma_stat);
/*	G2 DMAトリガ  */
EXTERN SYE_G2_ERR	syG2DmaTrigger( SYG2DMA handle, SYE_G2_DMA_TRIGGER triger_mode);
/*	G2 DMA一時停止  */
EXTERN SYE_G2_ERR	syG2DmaSuspend( SYG2DMA handle);
/*	全てのG2 DMA一時停止  */
EXTERN SYE_G2_ERR	syG2DmaSuspendAll( Void);
/*	G2 DMA停止  */
EXTERN SYE_G2_ERR	syG2DmaStop( SYG2DMA handle);
/*	全てのG2 DMA停止  */
EXTERN SYE_G2_ERR	syG2DmaStopAll( Void);
/*	G2 DMA一時停止解除  */
EXTERN SYE_G2_ERR	syG2DmaResume( SYG2DMA handle);
/*	全てのG2 DMA一時停止解除  */
EXTERN SYE_G2_ERR	syG2DmaResumeAll( Void);
/*	DMAが起動中かどうかチェック  */
EXTERN SYE_G2_ERR	syG2DmaIsBusy( SYG2DMA handle, Bool *flg);
/*	G2 DMAの起動回数の取得  */
EXTERN SYE_G2_ERR	syG2DmaGetTriggerCounter( SYE_G2_DMA_TYPE type, Uint32 *counter);
/*	G2 DMAの終了割り込み回数の取得  */
EXTERN SYE_G2_ERR	syG2DmaGetEndCounter( SYE_G2_DMA_TYPE type, Uint32 *counter);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif	/*	#ifndef	_SG_SYG2_H_  */

/*****************************************************
 *
 *	外部変数宣言
 *
 */

/*EOF*/
