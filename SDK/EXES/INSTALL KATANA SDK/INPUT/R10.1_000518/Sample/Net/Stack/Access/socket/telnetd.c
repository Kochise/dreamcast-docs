/*
//      telnetd
//
//      TCP/IPìÆçÏämîFópÇÃTELNETD
//      ->socketìÆçÏämîFóp
//      copyright(c) 1996-1998 access co.,ltd
*/
#define DREAMCAST
/*#define   WINDOWS*/
/*#define   UNIX*/

#include    <stdio.h>
#include    <stdarg.h>

#ifdef DREAMCAST
#include <shinobi.h>

#include    <types.h>
#include    <socket.h>
#include    <sock_errno.h>
#endif

#ifdef WINDOWS
#include <sys/types.h>
#include <stdio.h>
#include <windows.h>
#include <winsock.h>
#include <sock_errno.h>
#endif

#ifdef UNIX
#include    <stdio.h>
#include    <string.h>
#include    <sys/time.h>
#include    <sys/types.h>
#include    <sys/socket.h>
#include    <netinet/in.h>
#include    <netdb.h>
#include    <sock_errno.h>
#endif

#ifdef DREAMCAST
void DebugPrint(char *in_format, ...);
#else
#define DebugPrint  printf
#endif

#if 0
#define DP(args)    DebugPrint args
#else
#define DP(args)
#endif

/* Telnet Option Specifications list */

#define IAC             255     /* Interpreted As Command */
#define IAC_SE          240     /* Subnegotiation End */
#define IAC_NOP         241     /* No Operation */
#define IAC_DM          242     /* Data Mark */
#define IAC_BRK         243     /* Break */
#define IAC_IP          244     /* Interrupt Process */
#define IAC_AO          245     /* Abort Output */
#define IAC_AYT         246     /* Are You There */
#define IAC_EC          247     /* Erase Character */
#define IAC_EL          248     /* Erase Line */
#define IAC_GA          249     /* Go Ahead */
#define IAC_SB          250     /* Subnegotiation Begin */
#define IAC_WILL        251     /* Will */
#define IAC_WONT        252     /* Won't */
#define IAC_DO          253     /* Do */
#define IAC_DONT        254     /* Don't */
#define IAC_IAC         255     /* DATA 255 */

#define OPS_TRBIN       0       /* transmit binary */
#define OPS_ECHO        1       /* echo */
#define OPS_RCP         2       /* prepare to reconnect */
#define OPS_SUPGA       3       /* suppress go ahead */
#define OPS_NAMS        4       /* negotiate approximate message size */
#define OPS_STATUS      5       /* status */
#define OPS_TIMARK      6       /* timing mark */
#define OPS_RCTE        7       /* remote controlled transmission and echo */
#define OPS_NAOL        8       /* negotiate about output line-width */
#define OPS_NAOP        9       /* negotiate about output page-size */
#define OPS_NAOCRD      10      /* negotiate about output CR disposition */
#define OPS_NAOHTS      11      /* negotiate about output HTAB */
#define OPS_NAOHTD      12      /* negotiate about output HTAB disposition */
#define OPS_NAOFE       13      /* negotiate about output FF disposition */
#define OPS_NAOVT       14      /* negotiate about VTAB */
#define OPS_NAOVTD      15      /* negotiate about output VTAB disposition */
#define OPS_NAOLF       16      /* negotiate about output LF disposition */
#define OPS_EASCII      17      /* extend ascii */
#define OPS_LOGOUT      18      /* logout */
#define OPS_BM          19      /* byte macro */
#define OPS_DET         20      /* data entry terminal */
#define OPS_SUPDUP      21      /* SUPDUP */
#define OPS_SUPOUT      22      /* SUPDUP output */
#define OPS_SNDLOC      23      /* send location */
#define OPS_TTYPE       24      /* terminal type */
#define OPS_EOREC       25      /* end of record */
#define OPS_TUID        26      /* TACACS user identification */
#define OPS_OUTMR       27      /* output marking */
#define OPS_EXOPL       255     /* extended options list */

#if 0
#define TN_PORT 0x17            /* telnet§Œ•›°º•»»÷πÊ */
#else
#define TN_PORT 0x1700          /* telnet§Œ•›°º•»»÷πÊ */
#endif

#define far
#define intproc     AT_apiCall

u_char iac_accept[] = {
    IAC_DO,
    IAC_DONT,
    IAC_WILL,
    IAC_WONT
    };

u_char iac_reject[] = {
    IAC_DONT,
    IAC_DO,
    IAC_WONT,
    IAC_WILL
    };

u_char iac_initbuf[16] = {
    IAC,IAC_WILL, OPS_ECHO,
    IAC,IAC_WILL,OPS_SUPGA
    };

/* kiryu */
int gDebug1 = 0;
int gDebug2 = 0;
int gDebug3 = 0;
int gDebug4 = 0;
int gDebug5 = 0;

/* ÉvÉçÉgÉ^ÉCÉvêÈåæ */
void putstring(char far *);
void put_echo(u_char far *);
void close_func(void);
void td_main(void);
void tn_recv(int);
void tn_recv_iac(int);
u_char tn_getchar(int);
int  fstrlen(u_char far *);

void test_tcpopen(void);
void getstring(char *s);

u_char  iac_buf3[3];
int   tn_fin_rst;
int   done_nego;
short accept_newnh;
short recv_len;
volatile int    done ;
static short nh, l_nh;

int   do_echo_flag;
int   do_sga_flag;

short  cmdlen;
u_char  work[80];
u_char cmdline[80];

int     s1;
int     s2;

int terminate_flag = 0;

void putstring(char far *s)
{
    int len;

    if (*s) {
        len = fstrlen((u_char far *)s);
       send(s2, (char *)s, len, 0);
    }
}

void put_echo(u_char far *s)
{
    int len;

    if (*s) {
        len = fstrlen(s);
        send(s2, (char *)s, len, 0);
    }
}

void put_char(u_char c)
{
    u_short cc;

    *(u_char far *)&cc = c;

    send(s2, (char *)&cc, 1, 0);
}


void close_func(void)
{
    done = 1;
}


/* TELNETDÇÃÉÅÉCÉìä÷êî */
void td_main(void)
{
    short stat;
    int ret;
    int drop_nh;
    int accept_flag;

    struct sockaddr_in  sin;
    struct sockaddr_in  my_addr;
    int     len;

    short   port;

    u_long  ip_address;
    u_char  ip_addr[4];

    DP(("td_main() start !!!\r\n"));

    l_nh = -1;
    accept_flag = 0;
    accept_newnh = -1;

    gDebug1 = 1;

#ifdef DREAMCAST
    ip_address = DL_GetIpAddress();
    memcpy(ip_addr, &ip_address, 4);
    DP(("telnetd started.\n"));
    DebugPrint("My ip address is %d.%d.%d.%d\r\n", (u_char)ip_addr[0],
        (u_char)ip_addr[1], (u_char)ip_addr[2], (u_char)ip_addr[3]);
#endif

    terminate_flag = 0;
    while (1) {
        tn_fin_rst = 0; /* FIN */
        done_nego = 0;
        done = 0;
        cmdlen = 0;

        /* É\ÉPÉbÉgÇçÏê¨Ç∑ÇÈ */
        s1 = socket(AF_INET, SOCK_STREAM, 0);
        DP(("socket() s1 = %d\n", s1));

        if (s1 < 0) {
            DP(("socket() error\n"));
            return;
        }

        /* BINDÇ∑ÇÈ */
        sin.sin_family = AF_INET;
        sin.sin_port = htons(0x0017);
        sin.sin_addr.s_addr = htonl(INADDR_ANY);

        /* bind */
        ret = bind(s1, (struct sockaddr *)&sin, sizeof(sin));
        DP(("bind() ret = %d\n", ret));

        if (ret < 0) {
            DP(("bind() error\n"));
            return;
        }

        /* listen */
        ret = listen(s1, 5);
        DP(("listen() ret = %d\n", ret));

        if (ret < 0) {
            DP(("listen() error\n"));
            return;
        }

        /* accept */
        len = sizeof(struct sockaddr_in);
        s2 = accept(s1, (struct sockaddr *)&my_addr, &len);
        DP(("accept() s2 = %d\n", s2));

        if (s2 < 0) {
            DP(("accept() error\n"));
            return;
        }

        /* ÉlÉSÉVÉGÅ[ÉVÉáÉì */
        ret = send(s2, (char *)iac_initbuf, 6, 0);

        while (done_nego == 0) {
            tn_recv(s2);
        }

        DP(("6 "));
        putstring("Telnetd for TCP/IP Ver3.2(SH4)\r\n");
        putstring("Copyright (C) 1996,97,98 ACCESS CO.,LTD.\r\n");
        putstring("\r\ntelnet> ");

        while (done == 0 && tn_fin_rst == 0) {
            tn_recv(s2);
        }
#ifdef DREAMCAST
        sock_close(s1);
        sock_close(s2);
#endif
#ifdef WINDOWS
        closesocket(s1);
        closesocket(s2);
#endif
#ifdef UNIX
        close(s1);
        close(s2);
#endif
        if (terminate_flag == 1) {
            return;
        }
    }
}

void cmd_exec(u_char c)
{
#ifdef DREAMCAST
    SYS_RTC_DATE    date;
#endif
    char            work[64];
    if(cmdlen > 80){
        putstring("\r\ntelnet> ");
        cmdlen = 0;
        return;
    }

    if(c == 0x0d || c == 0x0a){
        c = 0;
    }
    else {
        put_char(c);
    }
    cmdline[cmdlen++] = c;

    if(c == 0){
        if(strcmp(cmdline,"quit") == 0){
            putstring("\r\nbye bye ");
            done = 1;
            return;
        }

        if(strcmp(cmdline,"exit") == 0){
            done = 1;
            terminate_flag = 1;
            return;
        }

        else if(strcmp(cmdline,"date") == 0){
#ifdef DREAMCAST
            /* åªç›éûçèï\é¶ */
            syRtcGetDate(&date);
            sprintf(work, "\r\n%4d/%02d/%02d %2d:%02d:%02d",
                date.year, date.month, date.day, date.hour, date.minute,
                date.second);
            putstring(work);
#else
            putstring("\r\nNot support");
#endif
        }
        else if(cmdlen > 1){
            putstring("\r\nwhat ? ");
        }

        putstring("\r\ntelnet> ");
        cmdlen = 0;
    }
}

void tn_recv(int s)
{
    u_char c;

    c = tn_getchar(s);
    if (tn_fin_rst) {
        return;
    }

    if (c == IAC) {
        tn_recv_iac(s);
    }
    else {
        cmd_exec(c);
    }
}


/*
 * IACΩËÕ */
void tn_recv_iac(int s)
{
    u_char iac_verb;
    u_char iac_option;

    iac_verb = tn_getchar(s);
    if (tn_fin_rst) {
        return;
    }

    switch(iac_verb) {
    case IAC_IAC:
        put_char(iac_verb);
        return;
    case IAC_WILL:
    case IAC_WONT:
    case IAC_DO:
    case IAC_DONT:
        iac_option = tn_getchar(s);
        if (tn_fin_rst) {
            return;
        }
        break;
    default:
        iac_option = tn_getchar(s);
        return;
    }

    switch(iac_option) {
    case OPS_ECHO:
        switch(iac_verb) {
        case IAC_DO:
            if (do_echo_flag ) {
                return;
            }
            do_echo_flag = 1;
            iac_buf3[1] = IAC_WILL;
            break;
        case IAC_DONT:
            iac_buf3[1] = IAC_WONT;
            break;
        case IAC_WILL:
            iac_buf3[1] = IAC_WONT;
            break;
        case IAC_WONT:
            iac_buf3[1] = IAC_WILL;
            break;
        default:
            return;
        }
        break;
    case OPS_SUPGA:
        switch(iac_verb) {
        case IAC_DO:
        case IAC_DONT:
            if (do_echo_flag) {
                return;
            }
            do_echo_flag = 1;
            iac_buf3[1] = IAC_WILL;
            break;
        case IAC_WILL:
            iac_buf3[1] = IAC_WONT;
            break;
        case IAC_WONT:
            iac_buf3[1] = IAC_WILL;
            break;
        default:
            return;
        }
        break;
    default:
        switch(iac_verb) {
        case IAC_WILL:
            iac_buf3[1] = IAC_DONT;
            break;
        case IAC_DO:
            iac_buf3[1] = IAC_WONT;
            break;
        case IAC_WONT:
        case IAC_DONT:
            return;
        }
    }
    iac_buf3[0] = IAC;
    iac_buf3[2] = iac_option;
    send(s, (char *)iac_buf3, 3, 0);
    done_nego = 1;
}


u_char tn_getchar(int s)
{
    unsigned char   c;
    int     ret;

    ret = recv(s, (char *)&c, 1, 0);
    /*DP(("recv() = %d data = %02x\n", ret, (unsigned char)c));*/

    if (ret > 0) {
        return c;
    }
    else {
        tn_fin_rst = 1;
        return 0;
    }
}

int fstrlen(u_char far *dst)
{
    int len;

    for (len = 0; *dst != '\0'; dst++, len++);

    return len;
}
