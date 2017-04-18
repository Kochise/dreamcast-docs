/*
 *  debug.c
 *  Copyright 1997,98 ACCESS CO.,LTD.
 *  All rights reserved.
 */

#include    <shinobi.h>

#include    <stdio.h>
#include    <stdarg.h>

/*
 * SH4 SCIF(FIFO内臓シリアル・コミュニケーション・インターフェイス)
 * シリアル・デバッグ入／出力ドライバ
 *
 */

#define CR      0x0d                /* キャリッジ・リターン */
#define LF      0x0a                /* ライン・フィード */
#define BS      0x08                /* バック・スペース */

void DebugPrint(char *in_format, ...);
void debug(void);
void command_exec(char *msg);

static void set_date(char *msg);
static void date(void);

#define MAX_MESSAGE     128
char            msg[MAX_MESSAGE];
void debug(void)
{
    char            rcv_data;
    char            send_data[3];
    int             i;

    send_data[1] = 0;

    i = 0;

    DebugPrint("\r\nDebug TASK Ver. 1.00 start !!!");
    DebugPrint("\r\nCopyright (C) 1998 ACCESS CO., LTD.");
    DebugPrint("\r\n> ");
    while (1) {
        if (scif_isget()) {                     /* 受信データある? */
            if (i < MAX_MESSAGE) {
                msg[i] = (char)scif_get();      /* 受信データコピー */
                rcv_data = msg[i];              /* メッセージ格納 */
                switch (rcv_data) {
                    case (int)CR: {
                        msg[i] = 0;
                        DebugPrint("\r\n");     /* エコーバック */
                        command_exec(msg);
                        send_data[0] = 0;
                        send_data[1] = 0;
                        i = 0;
                        break;
                    }
                    case (int)BS: {
                        if (i > 0) {
                            send_data[0] = BS;
                            send_data[1] = ' ';
                            send_data[2] = BS;
                            send_data[3] = 0;
                            DebugPrint(send_data);
                            send_data[0] = 0;
                            send_data[1] = 0;
                            send_data[2] = 0;
                            send_data[3] = 0;
                            i--;
                        }
                        break;
                    }
                    default: {
                        send_data[0] = rcv_data;
                        DebugPrint(send_data);          /* エコーバック */
                        i++;
                    }
                }
            }
        }
        else {
            /* なにもしない */
            vsWaitVSync(1);
        }
    }
}

void command_exec(char *msg)
{
    int     ret;
    extern void test(void);

    if (strcmp(msg, "test") == 0) {
        test();
    }

    if (strcmp(msg, "date") == 0) {
        date();
    }

    else if (strncmp(msg, "date 1", 6) == 0) {
        set_date(msg);
    }

    else {
        DebugPrint("not found\r\n");
    }
    DebugPrint("> ");
}

/******************************************************************************
 * 本ファイルでローカルなデバッグ用関数の定義セクション
 *****************************************************************************/

/* 指定されたin_formatの書式指定に従って、その後にある可変引数のパラメー
   タを評価してシリアルポートに出力する */
void
DebugPrint(char *in_format, ...)
{
    static char msg[8192];
    va_list ap;
    char *p;

    /* printfの書式にしたがって出力文字列を作成する */
    va_start(ap, in_format);
    vsprintf(msg, in_format, ap);
    va_end(ap);

    /* 出力(改行文字だけは特別にCR/LFを出力)する */
    for (p = msg; *p != 0; p++)
    {
        if (*p == '\n')
        {
            scif_putq('\r');
        }
        scif_putq(*p);
    }
}

static void date(void)
{
    SYS_RTC_DATE    date;

    /* 現在時刻表示 */
    syRtcGetDate(&date);
    DebugPrint("%4d/%02d/%02d %2d:%02d:%02d\n",
        date.year, date.month, date.day, date.hour, date.minute,
        date.second);
}

static void set_date(char *msg)
{
    int     year, month, day, hour, minute, second;
    SYS_RTC_DATE    date;

    sscanf((msg + 5), "%d %d %d %d %d %d", &year, &month, &day, &hour, &minute,
        &second);

    date.year = year;
    date.month = month;
    date.day = day;
    date.hour = hour;
    date.minute = minute;
    date.second = second;

    syRtcSetDate(&date);

}
