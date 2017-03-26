/*
 *  Shinobi Library
 *  Copyright (c) 1998 SEGA
 *
 *       Maple Driver
 *
 *  Module  : Library Header File
 *  File    : kaede.h
 *  Create  : 1998-03-25
 *  Modify  : 1999-01-19
 *  Version : 1.43
 *  Note    :
 */


#ifndef _KAEDE_H_
#define _KAEDE_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/*
 * C VIRTUAL TYPES DEFINITIONS
 */

#include <sg_xpt.h>


/*
 * GLOBAL DEFINES/MACROS DEFINES
 */

/******** デバイス最大数 ***************************************************/
#define KDD_DEV_MAX 24


/******** デバイス番号定義 *************************************************/
#define KDD_DEV_0      0                      /* デバイス  0               */
#define KDD_DEV_1      1                      /* デバイス  1               */
#define KDD_DEV_2      2                      /* デバイス  2               */
#define KDD_DEV_3      3                      /* デバイス  3               */
#define KDD_DEV_4      4                      /* デバイス  4               */
#define KDD_DEV_5      5                      /* デバイス  5               */
#define KDD_DEV_6      6                      /* デバイス  6               */
#define KDD_DEV_7      7                      /* デバイス  7               */
#define KDD_DEV_8      8                      /* デバイス  8               */
#define KDD_DEV_9      9                      /* デバイス  9               */
#define KDD_DEV_10    10                      /* デバイス  10              */
#define KDD_DEV_11    11                      /* デバイス  11              */
#define KDD_DEV_12    12                      /* デバイス  12              */
#define KDD_DEV_13    13                      /* デバイス  13              */
#define KDD_DEV_14    14                      /* デバイス  14              */
#define KDD_DEV_15    15                      /* デバイス  15              */
#define KDD_DEV_16    16                      /* デバイス  16              */
#define KDD_DEV_17    17                      /* デバイス  17              */
#define KDD_DEV_18    18                      /* デバイス  18              */
#define KDD_DEV_19    19                      /* デバイス  19              */
#define KDD_DEV_20    20                      /* デバイス  20              */
#define KDD_DEV_21    21                      /* デバイス  21              */
#define KDD_DEV_22    22                      /* デバイス  22              */
#define KDD_DEV_23    23                      /* デバイス  23              */

#define KDD_DEV_A0     0                      /* デバイス  0               */
#define KDD_DEV_A1     1                      /* デバイス  1               */
#define KDD_DEV_A2     2                      /* デバイス  2               */
#define KDD_DEV_A3     3                      /* デバイス  3               */
#define KDD_DEV_A4     4                      /* デバイス  4               */
#define KDD_DEV_A5     5                      /* デバイス  5               */
#define KDD_DEV_B0     6                      /* デバイス  6               */
#define KDD_DEV_B1     7                      /* デバイス  7               */
#define KDD_DEV_B2     8                      /* デバイス  8               */
#define KDD_DEV_B3     9                      /* デバイス  9               */
#define KDD_DEV_B4    10                      /* デバイス  10              */
#define KDD_DEV_B5    11                      /* デバイス  11              */
#define KDD_DEV_C0    12                      /* デバイス  12              */
#define KDD_DEV_C1    13                      /* デバイス  13              */
#define KDD_DEV_C2    14                      /* デバイス  14              */
#define KDD_DEV_C3    15                      /* デバイス  15              */
#define KDD_DEV_C4    16                      /* デバイス  16              */
#define KDD_DEV_C5    17                      /* デバイス  17              */
#define KDD_DEV_D0    18                      /* デバイス  18              */
#define KDD_DEV_D1    19                      /* デバイス  19              */
#define KDD_DEV_D2    20                      /* デバイス  20              */
#define KDD_DEV_D3    21                      /* デバイス  21              */
#define KDD_DEV_D4    22                      /* デバイス  22              */
#define KDD_DEV_D5    23                      /* デバイス  23              */

/******** ポート番号定義 ***************************************************/
#define KDD_PORT_A    0                       /* ポートA                   */
#define KDD_PORT_B    1                       /* ポートB                   */
#define KDD_PORT_C    2                       /* ポートC                   */
#define KDD_PORT_D    3                       /* ポートD                   */

/******** ファンクション定義 ***********************************************/
#define KDD_FUNC_CONTROLLER     0x00000001  /* 標準コントローラ            */
#define KDD_FUNC_STORAGE        0x00000002  /* ストレージ                  */
#define KDD_FUNC_LCD            0x00000004  /* LCD                         */
#define KDD_FUNC_TIMER          0x00000008  /* タイマ                      */
#define KDD_FUNC_SOUNDINPUT     0x00000010  /* 音声入力                    */
#define KDD_FUNC_ARGUN          0x00000020  /* AR-Gun                      */
#define KDD_FUNC_KEYBOARD       0x00000040  /* キーボード                  */
#define KDD_FUNC_LIGHTGUN       0x00000080  /* Light-Gun                   */
#define KDD_FUNC_VIBRATION      0x00000100  /* 振動                        */

/******** レスポンスコード *************************************************/
#define KDD_RES_DEVICESTATUS       0x05   /* Device Status                 */
#define KDD_RES_DEVICEALLSTATUS    0x06   /* Device All Status             */
#define KDD_RES_DEVICEREPLY        0x07   /* Device Reply                  */
#define KDD_RES_DATATRANSFER       0x08   /* Data Transfer                 */
#define KDD_RES_NORESPONSE         0xff   /* 応答なし                      */
#define KDD_RES_FUNCTIONUNKNOWN    0xfe   /* Function Type Unknown         */
#define KDD_RES_COMMANDUNKNOWN     0xfd   /* Command Unknown               */
#define KDD_RES_TRANSMITAGAIN      0xfc   /* Transmit Again                */
#define KDD_RES_FILEERROR          0xfb   /* File Error                    */
#define KDD_RES_LCDERROR           0xfa   /* LCD Error                     */
#define KDD_RES_ARERROR            0xf9   /* AR Error                      */

/******** ファンクションエラーコード ***************************************/
#define KDD_ERR_OK            0           /* エラーなし                    */
#define KDD_ERR_PARTITION     (1 << 0)    /* パーティションエラー          */
#define KDD_ERR_PHASE         (1 << 1)    /* フェイズエラー                */
#define KDD_ERR_BLOCK         (1 << 2)    /* ブロックエラー                */
#define KDD_ERR_WRITE         (1 << 3)    /* ライトエラー                  */
#define KDD_ERR_LENGTH        (1 << 4)    /* データ長エラー                */
#define KDD_ERR_CRC           (1 << 5)    /* CRCエラー                     */

/******** エリアコード *****************************************************/
#define KDD_AREA_USA          (1 << 0)    /* 北アメリカ地区                */
#define KDD_AREA_JAPAN        (1 << 1)    /* 日本地区                      */
#define KDD_AREA_ASIA         (1 << 2)    /* アジア地区                    */
#define KDD_AREA_EUROPE       (1 << 3)    /* ヨーロッパ地区                */
#define KDD_AREA_RESERVED1    (1 << 4)    /* 予約地区1                     */
#define KDD_AREA_RESERVED2    (1 << 5)    /* 予約地区2                     */
#define KDD_AREA_RESERVED3    (1 << 6)    /* 予約地区3                     */
#define KDD_AREA_RESERVED4    (1 << 7)    /* 予約地区4                     */

/******** コネクタ接続方向 *************************************************/
#define KDD_CONDIR_TOPSIDE      0         /* 上                            */
#define KDD_CONDIR_BOTTOMSIDE   1         /* 下                            */
#define KDD_CONDIR_LEFTSIDE     2         /* 左                            */
#define KDD_CONDIR_RIGHTSIDE    3         /* 右                            */

/******** モードタイプ定数 *************************************************/
#define KDD_MODE_OPTIMIZE    0            /* 最適化モード                  */
#define KDD_MODE_NOPCOUNT    1            /* NOP挿入回数                   */
#define KDD_MODE_TIMEOUT     2            /* タイムアウトまでの時間        */
#define KDD_MODE_SPEED       3            /* 通信速度                      */
#define KDD_MODE_DREQCOUNT   4            /* 拡張デバイスへのDev.Req.回数  */
#define KDD_MODE_DEVENDIAN   5            /* デバイスエンディアン          */
#define KDD_MODE_DEBUG       6            /* デバッグモード                */
#define KDD_MODE_ROOTPLAY    7            /* ROOTデバイスT.O.許容回数      */
#define KDD_MODE_GUNMODE     8            /* ガンモード                    */
#define KDD_MODE_AUTOFLASH   9            /* ガンモード時の自動フラッシュ  */

/******** 最適化モード *****************************************************/
#define KDD_OPTIMIZE_NONE   0             /* 最適化なし                    */
#define KDD_OPTIMIZE_8MS    1             /* VBlank In手前8msで開始        */
#define KDD_OPTIMIZE_4MS    2             /* VBlank In手前4msで開始        */
#define KDD_OPTIMIZE_2MS    3             /* VBlank In手前2msで開始        */
#define KDD_OPTIMIZE_1MS    4             /* VBlank In手前1msで開始        */

/******** 通信速度 *********************************************************/
#define KDD_SPEED_2MBPS   0x00000000      /* 2MBPS                         */
#define KDD_SPEED_1MBPS   0x00000100      /* 1MBPS                         */
#define KDD_SPEED_4MBPS   0x00000200      /* 4MBPS                         */
#define KDD_SPEED_8MBPS   0x00000300      /* 8MBPS                         */

/******** ガンモード *******************************************************/
#define KDD_GUNMODE_OFF   0x00000000      /* 通常モード                    */
#define KDD_GUNMODE_A     0x00000001      /* PORT Aガンモード              */
#define KDD_GUNMODE_B     0x00000002      /* PORT Bガンモード              */
#define KDD_GUNMODE_C     0x00000004      /* PORT Cガンモード              */
#define KDD_GUNMODE_D     0x00000008      /* PORT Dガンモード              */
#define KDD_GUNMODE_ALL   0x0000000f      /* 全ポートガンモード            */

/******** デバイスエンディアン *********************************************/
#define KDD_DEVENDIAN_LITTLE   0          /* リトルエンディアン            */
#define KDD_DEVENDIAN_BIG      1          /* ビッグエンディアン            */

/******** デバッグ *********************************************************/
#define KDD_DEBUG_OFF   0                 /* デバッグOFF                   */
#define KDD_DEBUG_ON    1                 /* デバッグON                    */

/******** ポート管理構造体 *************************************************/
typedef struct {
	Uint8 lmon;                 /* 物理接続状態ビット                      */
	Uint8 lmold;                /* 前フレームでの物理接続状態ビット        */
	Uint8 lmcon;                /* 物理接続状態 OFF->ON 変化ビット         */
	Uint8 lmremv;               /* 物理接続状態 ON->OFF 変化ビット         */
	Uint32 playcount;           /* 予約                                    */
} KDS_PORT;

/******** デバイス管理構造体 ***********************************************/
typedef struct {
	Uint8 on;                   /* 論理接続状態フラグ                      */
	Uint8 old;                  /* 前フレームでの論理接続状態              */
	Uint8 connect;              /* 論理接続状態 OFF->ON変化フラグ          */
	Uint8 remove;               /* 論理接続状態 ON->OFF変化フラグ          */
	Uint8 response;             /* レスポンスコード                        */
	Uint8 dst_ap;               /* 転送先AP                                */
	Uint8 src_ap;               /* 転送元AP                                */
	Uint8 datasize;             /* データサイズ(ロングワード数)            */
	void* recvdata;             /* 受信データのアドレス                    */
	Sint32 errcode;             /* ファンクションエラーコード              */
	Uint32 reserved[2];         /* 予約                                    */
} KDS_DEVICE;

/******** デバイス情報構造体 ***********************************************/
typedef struct {
	Uint32 function;            /* ファンクション                          */
	Uint8 fd[3][4];             /* ファンクション定義ブロックデータ        */
	Uint8 is_root;              /* ルートデバイスかどうかを表す            */
	Uint8 area_code;            /* エリアコード                            */
	Uint8 connector_dir[2];     /* 拡張コネクタ方向                        */
	char product_name[32];      /* 製品名                                  */
	char license[64];           /* ライセンス                              */
	Uint16 stdby_pow;           /* スタンバイ消費電流                      */
	Uint16 max_pow;             /* 最大消費電流                            */
} KDS_DEVICEINFO;

/******** コントローラ情報構造体 *******************************************/
typedef struct {
	Uint32 button;              /* 持っているボタン                        */
} KDS_CONTROLLERINFO;

/******** LCD情報構造体 ****************************************************/
#define KDD_LCD_NORMALLYWHITE 0 /* Normally White                          */
#define KDD_LCD_NORMALLYBLACK 1 /* Normally Black                          */
#define KDD_LCD_HV_00         0 /* データ並びはタイプ'00'                  */
#define KDD_LCD_HV_01         1 /* データ並びはタイプ'01'                  */
#define KDD_LCD_HV_10         2 /* データ並びはタイプ'10'                  */
#define KDD_LCD_HV_11         3 /* データ並びはタイプ'11'                  */

typedef struct {
	Uint16 partition;           /* パーティション数                        */
	Uint16 blocksize;           /* 1ブロックのバイト数                     */
	Uint16 writecount;          /* 1ブロックライト回数                     */
	Uint8  direction;           /* ピクセルの並びH/V                       */
	Uint8  normally;            /* Normally Black/White                    */
} KDS_LCDINFO;

/******** ストレージ情報構造体 *********************************************/
#define KDD_STORAGE_REMOVABLE 1 /* リムーバブルメディアである              */

typedef struct {
	Uint16 partition;           /* パーティション数                        */
	Uint16 blocksize;           /* 1ブロックのバイト数                     */
	Uint16 writecount;          /* 1ブロックライト回数                     */
	Uint16 readcount;           /* 1ブロックリード回数                     */
	Uint16 removable;           /* リムーバブルメディアかどうか            */
	Uint16 reserved;            /* 予約                                    */
} KDS_STORAGEINFO;

/******** タイマ情報構造体 *************************************************/
typedef struct {
	Uint8 write_timer;          /* 書き込み可能タイマ                      */
	Uint8 read_timer;           /* 読み込み可能タイマ                      */
	Uint8 button;               /* 持っているボタン                        */
	Uint8 alarm;                /* 持っているアラーム                      */
} KDS_TIMERINFO;

/******** SIP情報構造体 ****************************************************/
#define KDD_SIP_GETSAMPLINGDATA 1 /* Get Sampling Dataサブコマンドを持つ   */
#define KDD_SIP_BASICCONTROL    2 /* Basic Controlサブコマンドを持つ       */
#define KDD_SIP_AMPCONTROL      4 /* AMP Controlサブコマンドを持つ         */
#define KDD_SIP_TESTMODE        8 /* Test Modeサブコマンドを持つ           */

typedef struct {
	Uint32 function;            /* 持っている機能                          */
} KDS_SIPINFO;

/******** GUN情報構造体 ****************************************************/
typedef struct {
	Uint32 button;              /* 持っているボタン                        */
} KDS_GUNINFO;

/******** 振動情報構造体 ***************************************************/
typedef struct {
	Uint32 vn;                  /* 振動ユニットの個数                      */
	Uint32 se;                  /* 同時設定可能なユニットの個数            */
} KDS_VIBRATIONINFO;

/******** 通信状況構造体 ***************************************************/
typedef struct {
	Uint32 send_count;          /* 合計送信回数                            */
	Uint32 recv_count;          /* 合計受信回数                            */
	Uint32 vbin_count;          /* VBlank割り込みハンドラが呼ばれた回数    */
	Uint32 dmaend_count;        /* MPDMAE割り込みハンドラが呼ばれた回数    */
	Uint32 cannot_send_count;   /* 送信関数がエラーを返した回数            */
	Uint32 blocked_count;       /* VBlank割り込みハンドラがブロックした回数*/
	Uint32 total_vover_count;   /* 合計VBlankオーバー回数                  */
	Uint32 error_count[4];      /* 合計エラー回数(IA, OR, FIFO, COM)       */
	Uint16 send_line[2];        /* 最新の送信スタートHライン               */
	Uint16 recv_line[2];        /* 最新の受信割り込みHライン               */
	Uint16 vover_count[2];      /* 最新の送受信のVBlankオーバー回数        */
} KDS_SYSTEMINFO;

/******** ガンモード状況構造体 *********************************************/
typedef struct {
	Uint32 enable;              /* ガンモードかどうか                      */
	Uint32 port;                /* ガンモードに設定されているポート        */
	Uint32 current_port;        /* 最新の送受信でデータが更新されたポート  */
	Uint32 last_port;           /* 前回のポート                            */
} KDS_GUNMODEINFO;



/******** プロトタイプ *****************************************************/

/*------- システム関数 ----------------------------------------------------*/
Sint32 kdInitSystem(void* recvbuf, void* sendbuf);
void kdExitSystem(void);
const KDS_SYSTEMINFO* kdGetSystemInfo(void);
Sint32 kdInitSystemEx(Sint32* devmap, void** recvbuf, void* sendbuf,
																Sint32 num);

/*------- フレーム関数 ----------------------------------------------------*/
Sint32 kdMakeFrame(void);
Sint32 kdSendFrame(void);
Sint32 kdRecvFrame(void);

/*------- モード設定関数 --------------------------------------------------*/
Sint32 kdSetDriverMode(Sint32 type, Sint32 mode);
Sint32 kdGetDriverMode(Sint32 type);

/*------- デバイス管理関数 ------------------------------------------------*/
const KDS_DEVICE* kdGetDevice(Sint32 device);
const KDS_DEVICEINFO* kdGetDeviceInfo(Sint32 device);
const KDS_PORT* kdGetPortStatus(Sint32 port);
Sint32 kdGetStatus(Sint32 device, Sint32 seq);
Sint32 kdIsChanged(Sint32 device);
void kdRecognizeChanged(Sint32 device);

/*------- コマンド発行関数 ------------------------------------------------*/
Sint32 kdSetDeviceRequest(Sint32 device);
Sint32 kdSetAllStatusRequest(Sint32 device);
Sint32 kdSetDeviceReset(Sint32 device);
Sint32 kdSetDeviceKill(Sint32 device);
Sint32 kdSetGetCondition(Sint32 device, Sint32 func);
Sint32 kdSetGetMediaInfo(Sint32 device, Sint32 func, Sint32 pt);
Sint32 kdSetBlockRead(Sint32 device, Sint32 func, Sint32 pt,
											Sint32 phase, Sint32 block);
Sint32 kdSetBlockWrite(Sint32 device, Sint32 func, Sint32 pt,
					Sint32 phase, Sint32 block, const void* src, Sint32 size);
Sint32 kdSetGetLastError(Sint32 device, Sint32 func, Sint32 pt,
											Sint32 phase, Sint32 block);
Sint32 kdSetARControl(Sint32 device, const void* buf);
Sint32 kdSetFT4Control(Sint32 device, const void* buf);
Sint32 kdSetSetCondition(Sint32 device, Sint32 func, const void* buf,
																Sint32 size);
Sint32 kdSetTransmitAgain(Sint32 device);
Sint32 kdSetResetPattern(Sint32 port);

/*------- デバイスサービス関数 --------------------------------------------*/
const Uint8* kdDevGetFD(const KDS_DEVICEINFO* dev, Uint32 func);
Sint32 kdDevGetControllerInfo(KDS_CONTROLLERINFO* sinfo,
											const KDS_DEVICEINFO* info);
Sint32 kdDevGetStorageInfo(KDS_STORAGEINFO* sinfo,
											const KDS_DEVICEINFO* info);
Sint32 kdDevGetSIPInfo(KDS_SIPINFO* sinfo, const KDS_DEVICEINFO* info);
Sint32 kdDevGetLCDInfo(KDS_LCDINFO* sinfo, const KDS_DEVICEINFO* info);
Sint32 kdDevGetTimerInfo(KDS_TIMERINFO* sinfo, const KDS_DEVICEINFO* info);
Sint32 kdDevGetGunInfo(KDS_GUNINFO* sinfo, const KDS_DEVICEINFO* info);
void kdGetGunPosition(Sint32* x, Sint32* y);
Sint32 kdGetGunLatchedPort(void);
void kdSetGunRapid(Uint32 port, Uint32 num);
Uint32 kdGetGunRapid(Uint32 port);
void kdSetGunTrigger(Uint32 port);
void kdSetGunCallback(Sint32 (*func)(void));

/*------- その他の関数 ----------------------------------------------------*/
void kdGetVersion(Sint32* major, Sint32* minor);
void kdSetHandler(Uint32 num, void (*func)(void));

/*------- コマンド発行関数(コールバック付き) ------------------------------*/
typedef void (*KD_CALLBACK)(Sint32 device, Sint32 seqno,
								KDS_DEVICE* dev, KDS_DEVICEINFO* info);
Sint32 kdSetCallback(Sint32 device, KD_CALLBACK func, Sint32 seqno);
Sint32 kdSetDeviceRequestEx(Sint32 device, KD_CALLBACK cbfunc);
Sint32 kdSetAllStatusRequestEx(Sint32 device, KD_CALLBACK cbfunc);
Sint32 kdSetDeviceResetEx(Sint32 device, KD_CALLBACK cbfunc);
Sint32 kdSetDeviceKillEx(Sint32 device, KD_CALLBACK cbfunc);
Sint32 kdSetGetConditionEx(Sint32 device, Sint32 func, KD_CALLBACK cbfunc);
Sint32 kdSetGetMediaInfoEx(Sint32 device, Sint32 func, Sint32 pt,
														KD_CALLBACK cbfunc);
Sint32 kdSetBlockReadEx(Sint32 device, Sint32 func, Sint32 pt,
							Sint32 phase, Sint32 block, KD_CALLBACK cbfunc);
Sint32 kdSetBlockWriteEx(Sint32 device, Sint32 func, Sint32 pt, Sint32 phase,
			Sint32 block, const void* src, Sint32 size, KD_CALLBACK cbfunc);
Sint32 kdSetGetLastErrorEx(Sint32 device, Sint32 func, Sint32 pt,
							Sint32 phase, Sint32 block, KD_CALLBACK cbfunc);
Sint32 kdSetARControlEx(Sint32 device, const void* buf, KD_CALLBACK cbfunc);
Sint32 kdSetFT4ControlEx(Sint32 device, const void* buf, KD_CALLBACK cbfunc);
Sint32 kdSetSetConditionEx(Sint32 device, Sint32 func, const void* buf,
											Sint32 size, KD_CALLBACK cbfunc);
Sint32 kdSetTransmitAgainEx(Sint32 device, KD_CALLBACK cbfunc);
Sint32 kdSetResetPatternEx(Sint32 port, KD_CALLBACK cbfunc);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _KAEDE_H_ */

/******************************* end of file *******************************/
