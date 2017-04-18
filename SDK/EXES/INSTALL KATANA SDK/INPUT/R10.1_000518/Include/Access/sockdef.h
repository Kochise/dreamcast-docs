/************************************************************************/
/*    AVE-TCP Socket Library        sockdef.h         92/04/15          */
/*       Copyright (C) 1992 ACCESS CO.,LTD.                             */
/************************************************************************/
/*                                                                    */
/*            ソケットライブラリー・定義用ヘッダー                    */
/*                                                                    */

#ifdef __cplusplus /* Support for C++ */
extern "C" {
#endif /* __cplusplus */

/*#include <dos.h>*/
#include <in.h>

typedef u_char      n_char;     /* for convenience ... */
typedef u_short     n_short;    /* byte order is NETWORK order */
typedef u_long      n_long;

#define  NULL    0
#ifdef MSC
#define FAR far
#else
#define FAR
#endif


/***   最大値の定義   ***/
#define MAX_SOCK    10
#define MAX_RECV    10
#define MAX_BUFLEN  1536
#define MAX_ALIAS   10

/***   ファイル名の定義   ***/
#define HOSTSFN "HOSTS"
#define NTWKSFN "networks"
#define PRTCSFN "protocols"
#define SRVCSFN "services"

/***   ソケット状態フラグの定義   ***/
#define S_NULL      0
#define S_SOCKET    1
#define S_BIND      2
#define S_CONNECT   3
#define S_LISTEN    4
#define S_ACCEPT    5
#define S_CONNECT_W 6
#define S_CONNECT_W2    6

/***   オプション設定領域   ***/
struct  option{
    short   so_dontroute;
    short   so_oobinline;
    short   so_noblk;
    } ;

/***   ソケット属性設定領域   ***/
typedef struct  {
    short   num;            /* socket number */
    short   nethand;        /* net handle */
    short   nethand_accept;     /* net handle ( accept ) */
    short   s_status;       /* socket status */
    short   r_status;       /* socket read status */
    short   r_data_num;     /* number of data for read */
    short   w_status;       /* socket write status */
    short   domain;
    short   type;
    short   protocol;
    unsigned short  yourport;
    unsigned long   youraddr;
    struct  sockaddr_in name;
    short   namelen;
    struct  option  option;
    } SOCK_ATRB;

/***   レシーブ用テーブル   ***/
typedef struct  {
    short   usable;         /* socket usable flag */
    short   sock_no;        /* socket number */
    short   datalen;        /* receive data length */
    long    youraddr;       /* 相手の IP address */
    short   yourport;       /* 相手の port number */
    char    buff[MAX_BUFLEN];   /* receive buffer */
    struct  SOCK_RECV *before;      /* address of before data */
    struct  SOCK_RECV *after;       /* address of after data */
    } SOCK_RECV;

/* macros to break MS C "far" pointers into their segment and offset
 * components
 */

#define FP_SEG(fp) (*((unsigned *)&(fp) + 1))
#define FP_OFF(fp) (*((unsigned *)&(fp)))

/***   関数名の定義   ***/
#include <sockfunc.h>

#ifdef __cplusplus
} /* End of extern "C" { */
#endif /* __cplusplus */
