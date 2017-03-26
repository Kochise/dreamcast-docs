/*
 *
 *    AVEPPP API related definitions
 *
 *    aveppp.h
 *
 *    Copyright (C) 1998-1999 ACCESS CO.,LTD.
 */

/* $Header: /NetFront/TCP/dm_sdk/ppp/aveppp.h 2     99/12/06 11:22 Hamamoto $ */

#ifdef __cplusplus /* Support for C++ */
extern "C" {
#endif /* __cplusplus */

#ifndef AVEPPP_H
#define AVEPPP_H

#ifndef N_LONG_DEFINED
#define N_LONG_DEFINED
typedef unsigned long n_long;
typedef unsigned short n_short;
#endif

/*
 * <ppp/pppapi.h>にも同種の構造体が定義されているので注意
 * 両者は一致している必要がある
 */

typedef struct AvepppSerialParam {
	short speed;			/* ボーレート 0:2400, 1:4800, 2:9600, */
							/* 3:19200, 4:38400 5:57600 (,6:115200) */
	short stop;				/* ストップビット 0:1bit, 1:2bit */
	short parity;			/* パリティ 0:even, 1:odd, 2:none */
	short databit;			/* データ長 0:8bit, 1:7bit */
	short flow;				/* ハードフロー制御 0:non, 1:RTS, 2:DTR */
	long reserved_1;		/* 拡張用０にする */
	long reserved_2;		/* 拡張用０にする */
} AvepppSerialParam;

typedef struct AvepppTelephoneParam {
	short dialtype;			/* ダイアルタイプ 0:TONE, 1:PULSE */
	short outside_line;		/* 外線(0発信) 0:なし 1:あり */
	short timeout;			/* 通信中タイムアウト(秒) */
	short dial_retry;		/* ダイアルリトライ回数 1～99 */
	short dial_interval;	/*	ダイアルリトライ間隔(秒) 30以上を推奨 */
	char* outside_number;	/* 外線(０発信)番号の文字列 */
	long reserved_1;		/* 拡張用０にする */
	long reserved_2;		/* 拡張用０にする */
} AvepppTelephoneParam;

typedef struct AvepppConnectionParam {
	n_long his_ip;			/* 接続先IPアドレス(未使用) */
	n_long my_ip;			/* 自分のIPアドレス(未使用) */
	short recognize;		/* ユーザ認証 0:PAP, 1:chat, 2:CHAP, */
							/*			  3:接続先の指定による */
	short mru;				/* 最大受信バイト数 2048以下(無効時1500) */
	long magic_number;		/* マジックナンバー 16進8桁 */
	short acfcomp;			/* HDLCヘッダの圧縮 0:enable, 1:disable */
	short protocomp;		/* PPPヘッダの圧縮 0:enable, 1:disable */
	short vjcomp;			/* IPCPのP-TCPヘッダの圧縮 0:enable, 1:disable */
	long reserved_1;		/* 拡張用０にする */
	long reserved_2;		/* 拡張用０にする */
} AvepppConnectionParam;

typedef struct AvepppOpenParam {
	struct AvepppSerialParam* serial;
	struct AvepppTelephoneParam* telephone;
	struct AvepppConnectionParam* pppconection;
	char* login_script1;	/* ログインスクリプト1(モデム初期化用) */
	char* login_script2;	/* ログインスクリプト2(プロバイダ用) */
	char* telephone_number; /* 相手先電話番号 */
	char* login;			/* ログイン名 */
	char* password;			/* パスワード */
	char* signup;			/* サインアップ */
	long reserved_1;		/* 拡張用０にする */
	long reserved_2;		/* 拡張用０にする */
} AvepppOpenParam;

enum {
	AvepppConnectUnused,			/* 未オープン */
	AvepppConnectOpenStandby,		/* オープンリクエスト後実行待ち */
	AvepppConnectDialing,			/* ダイアリング */
	AvepppConnectAuthen,			/* 認証処理中 */
	AvepppConnectEstablished,		/* オープン完了 */
	AvepppConnectDisconnected,		/* 相手から切断された */
	AvepppConnectCloseStandby,		/* 切断処理中 */
	AvepppConnectOnhooking,			/* 回線切断処理中 */
	AvepppConnectFail				/* 接続失敗 */
};

enum {
	AvepppErrorNon,
	AvepppErrorModem,
	AvepppErrorBusy,
	AvepppErrorNoDialTone,
	AvepppErrorScript,
	AvepppErrorLcp,
	AvepppErrorAuth,
	AvepppErrorIpcp,
	AvepppErrorTcp
};

typedef struct AvepppStatus {
	n_long	his_ip;			/* 接続先ＩＰ */
	n_long	my_ip;			/* 自分のＩＰ */
	short	phase;			/* 動作フェーズ */
	long baud_rate;
	short port_inuse;		/* モデム使用中 */
	short last_error;
} AvepppStatus;

short AvepppInitialize(void);
short AvepppInitialize2(char *TxBuf, char *RxBuf,
						int TxBufSize, int RxBufSize); /*hamamoto 1999.11.16*/
void AvepppTerminate(void);
void AvepppSetDisconnectScript(char* p);
#ifndef DNSGET	/* horiuchi 1997041600 */
#else
void AvepppSetDns(
	long myip, long hisip,
	long mydns1, long mydns2, long hisdns1, long hisdns2
);
void AvepppGetDns(
	long* myip, long* hisip,
	long* mydns1, long* mydns2, long* hisdns1, long* hisdns2
);
#endif
short AvepppOpen(const AvepppOpenParam*);
short AvepppClose(short);
short AvetcpAbort(short nh);
short AvepppGetStatus(AvepppStatus*);

#endif

#ifdef __cplusplus
} /* End of extern "C" { */
#endif /* __cplusplus */
