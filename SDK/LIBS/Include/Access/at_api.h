/*
 *
 *    AVETCP API related definitions
 *
 *    at_api.h
 *
 *    Copyright (C) 1998 ACCESS CO.,LTD.
 */

#ifdef __cplusplus /* Support for C++ */
extern "C" {
#endif /* __cplusplus */

#ifndef HEAD_OF_AVETCPAP
#define HEAD_OF_AVETCPAP

#include "at_types.h"

/* Function Code Spec */

#define	GETCONFIG       0x4101
#define	SETASR          0x4102
#define	IFCONFIG        0x4105
#define	IFDOWN          0x4106

#define	TCP_OPEN        0x4110
#define	TCP_POPEN       0x4111
#define	TCP_ACCEPT      0x4112
#define	TCP_CLOSE       0x4113
#define	TCP_SHUTDOWN    0x4114
#define	TCP_ABORT       0x4115
#define	TCP_GETADDR     0x4116
#define	TCP_STAT        0x4117
#define	TCP_SEND        0x4118
#define	TCP_RECEIVE     0x4119
#define	TCP_CANCEL      0x411a
#define	TCP_SEND_F      0x411b

#define	UDP_OPEN        0x4120
#define	UDP_SEND        0x4121
#define	UDP_CLOSE       0x4113

#define	ROUTE_ADD       0x4130
#define	ROUTE_DEL       0x4131
#define	ROUTE_LIST      0x4132

/* Error Code Spec */

#define SUCCESS                 (  0)
#define API_PENDING             ( -1) /* 0xffff */
#define API_PORTFULL            ( -2) /* 0xfffe */
#define API_DUPSOCK             ( -3) /* 0xfffd */
#define API_INVALIDHANDLE       ( -4) /* 0xfffc */
#define API_SENDPENDING         ( -5) /* 0xfffb */
#define API_CONNRESET           ( -6) /* 0xfffa */
#define API_UNREACHABLE         ( -7) /* 0xfff9 */
#define API_RECVFIN             ( -8) /* 0xfff8 */
#define API_RECVPENDING         ( -9) /* 0xfff7 */
#define API_PORTCLOSED          (-10) /* 0xfff6 */
#define	API_TIMEOUT             (-11) /* 0xfff5 */
#define API_NOBUF               (-12) /* 0xfff4 */
#define API_BADOPT              (-13) /* 0xfff3 */
#define API_GENERAL             (-16) /* 0xfff0 */
#define API_UNSUPPORTEDFUNC     (-16) /* 0xfff0 */

/* ASR event code */

/* for TCP module */

#define ASR_ESTABLISHED        1
#define ASR_FIN                2
#define ASR_DISCONNECT         4
#define ASR_RST                10
#define ASR_TIMEOUT            11
#define ASR_HOST               12
#define ASR_PORT               13

/* for UDP module */

#define ASR_ADDR_UNREACH       128
#define ASR_ADDR_PORT_UNREACH  129 

/* for common */

#define ASR_LAST               255

/* AVE-TCP API Function */

/* API Call */
extern AT_SINT16 AT_apiCall(AT_UINT16 code, AT_VOID *inp, AT_VOID *outp);
/* Initialize  */
extern AT_SINT16 AT_init(AT_VOID *initArg);
/* Dispose */
extern AT_SINT16 AT_disp(AT_VOID *dispArg);

/* Parameter Structures */

/* general/common command */

typedef struct _AT_config {
    AT_NINT32 ip_addr;    /* IP アドレス（ネットワークオーダ）*/
    AT_NINT32 netmask;    /* サブネットマスク */
    AT_NINT32 broadcast;  /* ブロードキャストアドレス */
}AT_config;

typedef struct _AT_configptr{
    AT_VOID *config_ptr;  /* コンフィグレーションブロックのアドレス */
}AT_configptr;

typedef struct _AT_setasr {
    AT_SINT16 nh;         /* ネットハンドル */
    AT_VOID (* asraddr)(AT_SINT16, AT_SINT16);
                          /* ASR ルーチンのアドレス */
}AT_setasr;

typedef struct _AT_ifconfigparam {
    AT_SINT16 if_num;     /* インタフェース番号（０のみサポート） */
    AT_NINT32 ip_addr;    /* IP アドレス */
    AT_NINT32 netmask;    /* サブネットマスク */
    AT_NINT32 broadcast;  /* ブロードキャストアドレス */
}AT_ifconfigupparam;

typedef struct _AT_ifconfigdownparam {
    AT_SINT16 if_num;     /* インタフェース番号（０のみサポート） */
}AT_ifconfigdownparam;

/* TCP command */

typedef struct _AT_openparam {
    AT_NINT32 youraddr;   /* 相手の IP アドレス */
    AT_NINT16 yourport;   /* 相手のポート番号 */
    AT_NINT16 myport;     /* 自分のポート番号 */
    AT_UBYTE reserve1;    /* 未使用領域 */
    AT_UBYTE ttl;         /* Time to live */
    AT_UBYTE svctype;     /* Service type */
    AT_UBYTE df_flag;     /* Don't Fragment flag */
    AT_SINT16 reserve2;   /* 未使用領域 */
    AT_VOID *reserve3;     /* 未使用領域 */
    AT_VOID (* asraddr)(AT_SINT16, AT_SINT16);
                          /* ASR ルーチンのアドレス */
}AT_openparam;

typedef struct _AT_popenparam {
    AT_NINT32 youraddr;   /* 相手の IP アドレス */
    AT_NINT16 yourport;   /* 相手のポート番号 */
    AT_NINT16 myport;     /* 自分のポート番号 */
    AT_UBYTE reserve1;    /* 未使用領域 */
    AT_UBYTE ttl;         /* Time to live */
    AT_UBYTE svctype;     /* Service type */
    AT_UBYTE df_flag;     /* Don't Fragment flag */
    AT_SINT16 reserve2;   /* 未使用領域 */
    AT_VOID *reserve3;     /* 未使用領域 */
}AT_popenparam;

typedef struct _AT_acceptparam {
    AT_SINT16 nh;         /* ネットハンドル */
    AT_VOID (* notifyaddr)(AT_SINT16, AT_SINT16, AT_UINT32, AT_UINT16, AT_UINT16);
                          /* notify ルーチンのアドレス */
    AT_VOID (* asraddr)(AT_SINT16, AT_SINT16);
                          /* ASR ルーチンのアドレス */
}AT_acceptparam;

typedef struct _AT_nhparam {
    AT_SINT16 nh;         /* ネットハンドル */
}AT_nhparam;

typedef struct _AT_getaddr_r{
    AT_NINT32 ipaddr;     /* 相手のＩＰアドレス */
    AT_NINT16 myport;     /* 自分のポート番号 */
    AT_NINT16 yourport;   /* 相手のポート番号 */
}AT_getaddr_r;

typedef struct _AT_stat_r{
    AT_UINT16 stat;       /* コネクションの状態 */
    AT_UINT16 reserve;    /* 未使用領域 */
    AT_UINT16 sendwin;    /* 送信ウインドウの残量 */
    AT_UINT16 recvwin;    /* 到着済み受信データ量 */
}AT_stat_r;

typedef struct _AT_sendparam {
    AT_SINT16 nh;         /* ネットハンドル */
    AT_VOID (* notifyaddr)(AT_SINT16, AT_SINT16);
                          /* notify ルーチンのアドレス */
    AT_UBYTE reserve;     /* 未使用領域 */
    AT_UBYTE bufnum;      /* 使用するバッファ数 */
    struct {
        AT_SINT16 len;    /* データ長 */
        AT_UBYTE  *buf;   /* データアドレス */
    }buffers[1];          /* Variable length array 1～4 */
}AT_sendparam;

typedef struct _AT_rcvparam {
    AT_SINT16 nh;         /* ネットハンドル */
    AT_SINT16 len;        /* バッファ長 */
    AT_UBYTE  *buf;       /* バッファアドレス */
    AT_VOID (* notifyaddr)(AT_SINT16, AT_SINT16, AT_SINT16);
                          /* notify ルーチンのアドレス */
}AT_rcvparam;

typedef struct _AT_cancelparam {
    AT_SINT16 nh;         /* ネットハンドル */
    AT_SINT16 what;       /* キャンセル対象 */
}AT_cancelparam ;

typedef struct _AT_sendfparam {
    AT_SINT16 nh;         /* ネットハンドル */
    AT_VOID (* notifyaddr)(AT_SINT16, AT_SINT16, AT_UBYTE *);
                          /* notify ルーチンのアドレス */
    AT_UBYTE reserve;     /* 未使用領域 */
    AT_SINT16 len;        /* データ長 */
    AT_UBYTE  *buf;       /* データアドレス */
}AT_sendfparam;

/* UDP command */

typedef struct _AT_UDPPRM {
    AT_SINT16 handle;     /* ネットハンドル */
    AT_VOID *buf;         /* データアドレス */
    AT_SINT16 len;        /* データ長 */
    AT_NINT32 srcaddr;    /* 送信元の IP アドレス */
    AT_NINT16 srcport;    /* 送信元のポート番号 */
    AT_UBYTE *usrbuff;    /* バッファアドレス */
} AT_UDPPRM;

typedef struct _AT_uopenparam {
    AT_NINT32 youraddr;   /* 相手の IP address */
    AT_NINT16 yourport;   /* 相手のポート番号 */
    AT_NINT16 myport;     /* 自分のポート番号 */
    AT_UBYTE reserve1;    /* 未使用領域 */
    AT_UBYTE ttl;         /* Time to live */
    AT_UBYTE svctype;     /* Service type */
    AT_UBYTE df_flag;     /* Don't Fragment flag */
    AT_SINT16 reserve2;   /* 未使用領域 */
    AT_VOID  *reserve3;   /* 未使用領域 */
    AT_VOID (* asraddr)(AT_SINT16, AT_SINT16);
                          /* ASR ルーチンのアドレス */
    AT_SINT16 (* receiver)(AT_SINT16, AT_UDPPRM *);
                          /* レシーバルーチンのアドレス */
}AT_uopenparam;

typedef struct _AT_usendparam {
    AT_SINT16 nh;        /* ネットハンドル */
    AT_NINT32 youraddr;  /* 相手の IP アドレス */
    AT_NINT16 yourport;  /* 相手のポート番号 */
    AT_UBYTE bufnum;     /* 使用するバッファ数 */
    struct {
        AT_SINT16 len;   /* データ長 */
        AT_UBYTE *buf;   /* データアドレス */
    }buffers[1];         /* Variable length array 1～4 */
}AT_usendparam;

typedef struct _AT_addrtparam {
    AT_NINT32 dstaddr;   /* 相手の IP アドレス */
    AT_NINT32 gtwayaddr; /* ゲートウェイアドレス */
    AT_SINT16 reserve;   /* 未使用領域 */
}AT_addrtparam;

typedef struct _AT_delrtparam {
    AT_NINT32 dstaddr;   /* 相手の IP アドレス */
    AT_NINT32 gtwayaddr; /* ゲートウェイアドレス */
}AT_delrtparam;

typedef struct _AT_RouteEntry {
    AT_NINT32 dstaddr;   /* 相手の IP アドレス */
    AT_NINT32 gtwayaddr; /* ゲートウェイアドレス */
    AT_UINT16 reserve1;  /* 未使用領域 */
    AT_UINT16 reserve2;  /* 未使用領域 */
    AT_UINT16 reserve3;  /* 未使用領域 */
} AT_RouteEntry;

typedef struct _AT_lstrtparam {
    AT_SINT16 len;       /* データ長 */
    AT_RouteEntry *buf;     /* データアドレス */
}AT_lstrtparam;

#endif /* HEAD_OF_AVETCPAP */
#ifdef __cplusplus
} /* End of extern "C" { */
#endif /* __cplusplus */
