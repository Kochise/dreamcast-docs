/******************************************************************************
 *
 * name:    sock_test.c
 *
 * purpose: SOCKET LIB TEST
 *
 * socket libraryのtest routineである。
 * 旧sock_test1.c～sock_test19.cをsock_test.cとして
 * 統合した。 1998.11.14 by kiryu
 *
 *
 *      Copyright (C) 1993-1998 by ACCESS CO.,LTD.
 *
 *****************************************************************************/


#include <types.h>
#include <socket.h>
#include <sock_errno.h>
#include "usrUtl.h"


/* 固有ヘッダの引用 */
#include <aveppp.h>         /* pppのAPI定義を取り込む */

#include <vsyncpro.h>       /* 簡易V-SYNCスレッドマネージャのヘッダ */

/* 標準ヘッダの引用 */
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdarg.h>
#include <shinobi.h>

#include <dns.h>            /* DNSのAPI定義を取り込む */

void DebugPrint(char *in_format, ...);  /* From dbg.c. */


/******************************************************************************
 * 本ファイル内で共有される変数の定義セクション
 *****************************************************************************/

/* ログインするためのスクリプト */
static const char login_script[] =
    "send\"AT&F\\r\"\n"         /* 'AT&F'を送って工場出荷時の設定に戻す */
    "wait\"OK\\r\\n\",5\n"      /* 'OK'が返ってくるのを待つ */
    "send \"ATX3&C1&D2\\r\"\n"  /* 'ATX3&C1&D2'を送る */
    "wait\"OK\\r\\n\",5\n";     /* 'OK'が返ってくるのを待つ */

/* ダイアリングのためのスクリプト */
static const char dialing_script[] =
    "dial\"%t\"\n";             /* 電話番号をダイアルする */

/* ログインで使われる電話番号 */
static char telephon_no[64];

/* ログインで使われるユーザー名 */
static char login_user[64];

/* ログインで使われるパスワード */
static char login_password[64];

/* DNSのドメイン名 */
static wave_char DnsName[128];

/* DNSサーバのIPアドレス */
static wave_32bit PPP_DnsServer1 = 0;


/******************************************************************************
 * 本ファイルでローカルなTCP/IP呼び出し関数の定義セクション
 *****************************************************************************/

/* TCP/IPプロトコルスタックを初期化する */
static short avetcp_initialize(void)
{
    AT_init(0);
    return 0;
}


/* プロトコルスタックを終了する */
void avetcp_terminate(void)
{
    AT_disp(0);
}


/******************************************************************************
 * PPPを使う関数の定義セクション
 *****************************************************************************/

/* シリアルの通信仕様を決定する */
static void
setup_serial_spec(AvepppSerialParam *serial)
{
    serial->speed         = 5;    // speed 0-6 : 2400,4800,9600,19200,38400,57600(,115200)
    serial->stop          = 0;    // stop bit 0:1bit, 1:2bit
    serial->parity        = 2;    // parity 0:even, 1:odd, 2:none
    serial->flow          = 2;    // flow control 0:non, 1:RTS, 2:DTR
    serial->databit       = 0;    // data size 0:8bit, 1:7bit
}

/* 電話番号仕様を決定する */
static void
setup_telephone_spec(AvepppTelephoneParam *telephone)
{
    telephone->dialtype       = 0;        // Dial type 0:TONE, 1:PULSE
    telephone->outside_line   = 0;        // Use Outside line (no)
    telephone->timeout        = 60;       // timeout
    telephone->dial_retry     = 0;        // redial tries (none)
    telephone->dial_interval  = 30;       // redial interval
    telephone->outside_number = UUGetOutsideLine();       // outside line number ("0,")
}

/* PPPの接続仕様を決定する */
static void
setup_connection_spec(AvepppConnectionParam *pppconection)
{
    pppconection->recognize        = 4;            // user authorization, 0:PAP,1:chat,2:CHAP
    pppconection->mru              = 1500;         // maximum receiving bytes
    pppconection->magic_number     = 0x12345678;   // magic number
    pppconection->acfcomp          = 0;            // HDLC header compression (enable)
    pppconection->protocomp        = 0;            // PPP header compression (enable)
    pppconection->vjcomp           = 0;            // IPCP IP-TCP header compression (enable)
}

/* PPPのオープンパラメータを設定する */
static void
setup_ppp(AvepppOpenParam *iparam)
{
    /* Call function to ISP information. */
    UUInitISPInfo(UU_ACCESS);

    //strcpy(telephon_no, "5552112");
    //strcpy(login_user, "sega");
    //strcpy(login_password, "dreamcast");

    iparam->login_script1 = (char *) login_script;
    iparam->login_script2 = (char *) dialing_script;
    iparam->telephone_number = (char *) UUGetPrimaryNumber();
    iparam->login = (char *) UUGetLoginID();
    iparam->password = (char *) UUGetPassword();
}

/* プロトコルを初期して回線(PPP層)を接続する */
static int
dialing(void)
{
    AvepppOpenParam iparam;         /* オープンのパラメータ */

    AvepppSerialParam serpara;      /* シリアルの設定 */
    AvepppTelephoneParam telepara;  /* 電話番号の設定 */
    AvepppConnectionParam cnepara;  /* 接続の設定 */

    AvepppStatus statpara;          /* PPPのステータス */

    /* シリアルの設定を作成 */
    setup_serial_spec(&serpara);

    /* 電話番号の設定を作成 */
    setup_telephone_spec(&telepara);

    /* 接続の設定を作成 */
    setup_connection_spec(&cnepara);

    /* PPPのオープンパラメータを作成 */
    iparam.serial = &serpara;
    iparam.telephone = &telepara;
    iparam.pppconection = &cnepara;
    setup_ppp(&iparam);

    /* PPPを初期化する */
    AvepppInitialize();

    /* TCP/IPを初期化する */
    avetcp_initialize();

    /* DNSの設定 */
    strcpy(DnsName, "");
    PPP_DnsServer1 = ((202 << 0) + (232 << 8) + (2 << 16) + (38 << 24));

    /* DNSを初期化する */
    ADNS_Initialize(DnsName, PPP_DnsServer1, PPP_DnsServer1);

    /* PPPを接続する(ダイアリングが開始される) */
    AvepppOpen(&iparam);

    /* PPPの接続完了まで待つ */
    for (;;)
    {
        vsWaitVSync(100);

        /* PPPの状態を得る */
        AvepppGetStatus(&statpara);

        /* 接続完了ならばループを脱出 */
        if (statpara.phase == AvepppConnectEstablished) break;

        /* 接続に失敗したらエラー処理へ */
        if (statpara.phase == AvepppConnectFail
            || statpara.phase == AvepppConnectDisconnected) goto error;
    }
    return 0;

error:
    return -1;
}

/* PPPの切断処理 */
void
disconnect(void)
{
    AvepppStatus statpara;

    /* PPPを切断させる */
    AvepppClose(0);

    /* PPPの切断が確認されるまで待つ*/
    for (;;)
    {
        vsWaitVSync(100);

        /* PPPの状態を得て、切断状態になったらループを脱出 */
        AvepppGetStatus(&statpara);
        if (statpara.phase == AvepppConnectUnused) break;
    }

    /* DNSの終了処理を行う */
    ADNS_Finalize();

    /* TCPの終了処理を行う */
    avetcp_terminate();

    /* PPPの終了処理を行う */
    AvepppTerminate();
}


/******************************************************************************
 * 忍ライブラリとのインターフェース
 *****************************************************************************/

/* 忍ライブラリの初期化 */
void njUserInit(void)
{
    /* Check the cable for NTSC/PAL or VGA.. works properly for SCART. */
    switch (syCblCheck())
	{
        /* Initialize the display device and set the frame buffer based on the video mode. */
        case SYE_CBL_NTSC:  /* U.S./North America NTSC (60Hz) and Brazil PAL-M (60Hz). */
            sbInitSystem (NJD_RESOLUTION_640x480_NTSCNI, NJD_FRAMEBUFFER_MODE_RGB565, 1);
            break;
        case SYE_CBL_PAL:   /* Europe PAL (50Hz) and Argentina PAL-N (50Hz). */
            sbInitSystem (NJD_RESOLUTION_640x544_PALNI, NJD_FRAMEBUFFER_MODE_RGB565, 1);
            break;
        case SYE_CBL_VGA:   /* Standard VGA. */
            sbInitSystem (NJD_RESOLUTION_VGA, NJD_FRAMEBUFFER_MODE_RGB565, 1);
            break;
        default:
            syBtExit();     /* Unknown video type, return to Dreamcast BootROM. */
	}
    njSetBorderColor( 0x00000000 ) ;
    njSetBackColor( 0xff0000ff,0xff0000ff,0xff000000 );
    njInitVertexBuffer(800000, 0, 200000, 0, 0);
    njInitPrint(NULL, 0, 0);
	njPrintSize(16);
}

/* 忍ライブラリの終了処理 */
void njUserExit(void)
{
    njExitPrint();

    sbExitSystem();

    /* 戻ってきたときに備えて無限ループで停止するコードを置く */
    for (;;)
        ;
}

/******************************************************************************
 * 外部公開する関数の定義セクション
 *****************************************************************************/

/*extern void sock_test1(void);*/

/* テストのメインルーチン */
Sint32 njUserMain(void)
{
    int i;
    extern void debug();
    extern void td_main();

    unsigned int    count1;
    unsigned int    count2;
    unsigned int    count;
    unsigned int    micro;

    void *vSyncCallbackProc(void);

    /* Serial debug interface. */
    dbInit();

    /*vsInitVSyncProc(0);*/
    vsInitVSyncProc(vSyncCallbackProc);

    DebugPrint ("\n*** START TEST PROGRAM ***\n");

    vsWaitVSync(1);

    /*return 0;*/

    /*debug();*/

    /* ダイアリングしてPPPを接続状態にする */
    if (dialing() < 0)
    {
        DebugPrint ("\n*** Error occur: can't connect PPP\n");
        goto error;
    }
    DebugPrint ("\n*** PPP CONNECTED ***\n");

    /* socketライブラリtest */

    DebugPrint ("\n");

    debug();
    /*td_main();*/

    DebugPrint ("\n*** TCP/IP TESTED ***\n");

 error:
    /* PPPの接続をきる */
    disconnect();

    DebugPrint ("\n*** PPP DIS-CONNECTED ***\n");

    return NJD_USER_EXIT;
}

/*
 * PPP/TCPがブロック処理を行っているとき呼び出す処理
 */
void *vSyncCallbackProc(void)
{
    unsigned int    count;
    SYS_RTC_DATE    date;

    /* タイマ表示 */
    count = syTmrGetCount();
    njPrint(NJM_LOCATION(4, 8), "Timer is %08x", count);

    njPrintC(NJM_LOCATION(4,10),"Connect Set5 serial output to PC");
    njPrintC(NJM_LOCATION(4,11),"to control socket test remotely.");

    njPrintC(NJM_LOCATION(4,13),"Set TERMINAL to 57600 bps");
    njPrintC(NJM_LOCATION(4,14),"  (8-N-1 HW Flow)");
    njPrintC(NJM_LOCATION(4,16),"Type TEST when connected.");

    /* 現在時刻表示 */
    syRtcGetDate(&date);
    njPrint(NJM_LOCATION(4, 18), "%4d/%02d/%02d %2d:%02d:%02d",
        date.year, date.month, date.day, date.hour, date.minute,
        date.second);

    njWaitVSync();

}