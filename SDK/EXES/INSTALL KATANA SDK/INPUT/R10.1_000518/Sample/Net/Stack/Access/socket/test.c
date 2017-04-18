/*
 * socket test
 * test.c
 * Copyright 1998 ACCESS CO.,LTD. All right reserved.
 *
 * 1998.11.21 kiryu
 *
 */


#define DREAMCAST
/*#define   WINDOWS*/
/*#define   UNIX*/

#ifdef DREAMCAST
#include    <stdio.h>
#include    <stdarg.h>
#include    <shinobi.h>

#include <types.h>
#include <socket.h>
#include <netdb.h>
#include <in.h>
#include <dns.h>
#include <sock_errno.h>

#ifdef errno
#undef errno
#endif
#define errno sock_errno
/* extern volatile int sock_errno; */
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

#define errno sock_errno
/* extern int  sock_errno; */
#endif

#ifndef DREAMCAST
char scif_get();
#endif

/*
 * SH4 SCIF(FIFO)
 * Srial Debug Input/Output Interface
 *
 */

#define CR      0x0d                /* Carrige rerun */
#define LF      0x0a                /* Line feed */
#define BS      0x08                /* Back space */

#ifdef DREAMCAST
void DebugPrint(char *in_format, ...);
#define printf  DebugPrint
#else
#define DebugPrint  printf
#endif

char *DebugGets();

static void command_exec();

void test_accept();
void test_bind();
void test_connect();
void test_getpeername();
void test_getsockname();
void test_getsockopt();
void test_setsockopt();
void test_listen();
void test_recv();
void test_recvfrom();
void test_select();
void test_send();
void test_sendto();
void test_shutdown();
void test_socket();
void test_sock_close();
void test_sock_read();
void test_sock_write();
void test_gethostbyname();
void test_htonl();
void test_htons();
void test_ntohl();
void test_ntohs();

int  test_fd_set();
void select_main();

void test_tmr();

static void menu();
#define MAX_MESSAGE     128

#ifdef DREAMCAST
void test()
{
    char            msg[MAX_MESSAGE];
    char            rcv_data;
    char            send_data[3];
    int             i;
    extern *vSyncCallbackProc();
    send_data[1] = 0;

    i = 0;

    menu();
    while (1) {
        if (scif_isget()) {                     /* Is received data ? */
            if (i < MAX_MESSAGE) {
                msg[i] = (char)scif_get();      /* Copy receive data */
                rcv_data = msg[i];              /* copy */
                switch (rcv_data) {
                    case (int)CR: {
                        msg[i] = 0;
                        DebugPrint("\r\n");     /* echo back */
                        command_exec(msg);
                        memset(msg, 0, MAX_MESSAGE);
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
                        DebugPrint(send_data);          /* echo back */
                        i++;
                    }
                }
            }
        }
        else {
            vsWaitVSync(1);
        }
    }
}
#else
void main()
{
    static char s[128];
    char    *ret;
#ifdef WINDOWS
    WORD    wVerReq;
    WSADATA wsadata;
    int     err;

    wVerReq = MAKEWORD(1, 1);
    err = WSAStartup(wVerReq, &wsadata);
    if (err != 0) {
        return;
    }
#endif

    menu();
    while (1) {
        /*ret = gets(s);*/
        ret = fgets(s, 128, stdin);
        command_exec(s);
    }
}
#endif

#ifdef DREAMCAST
char *DebugGets()
{
    static char     msg[MAX_MESSAGE];
    char            rcv_data;
    char            send_data[3];
    int             i;
    extern *vSyncCallbackProc();

    i = 0;
    send_data[0] = 0;
    send_data[1] = 0;
    send_data[2] = 0;
    send_data[3] = 0;

    while (1) {
        if (scif_isget()) {
            if (i < MAX_MESSAGE) {
                msg[i] = (char)scif_get();
                rcv_data = msg[i];
                switch (rcv_data) {
                    case (int)CR: {
                        msg[i] = 0;
                        DebugPrint("\r\n");
                        return msg;
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
                        DebugPrint(send_data);
                        i++;
                    }
                }
            }
        }
        else {
            (*vSyncCallbackProc)();
            ;
        }
    }
}
#else
char *DebugGets()
{
    static char buff[128];
    char    c = 0;
    char    *ptr;
    int     i;

    memset(buff, 0, 128);
    i = 0;
    while (1) {
        c = getchar();
        if (c != '\n') {
            buff[i] = c;
            i++;
        }
        else {
            break;
        }
        if (i > 128) {
            buff[127] = 0;
            break;
        }
    }
    return (char *)buff;
}

#endif

#ifndef DREAMCAST
int scif_isget()
{
    return 1;
}

char scif_get()
{
    return getchar();
}
#endif

/*
 * command execition
 */

static void command_exec(msg)
char    *msg;
{
    int     ret;
    extern void td_main();

    if (strncmp(msg, "10", 2) == 0) {
        test_recvfrom();
    }

    else if (strncmp(msg, "11", 2) == 0) {
        test_select();
    }

    else if (strncmp(msg, "12", 2) == 0) {
        test_send();
    }

    else if (strncmp(msg, "13", 2) == 0) {
        test_sendto();
    }

    else if (strncmp(msg, "14", 2) == 0) {
        test_shutdown();
    }

    else if (strncmp(msg, "15", 2) == 0) {
        test_socket();
    }

    else if (strncmp(msg, "16", 2) == 0) {
        ;
    }

    else if (strncmp(msg, "17", 2) == 0) {
        test_sock_close();
    }

    else if (strncmp(msg, "18", 2) == 0) {
        test_sock_read();
    }

    else if (strncmp(msg, "19", 2) == 0) {
        test_sock_write();
    }

    else if (strncmp(msg, "20", 2) == 0) {
        test_gethostbyname();
    }

    else if (strncmp(msg, "22", 2) == 0) {
        ;
    }

    else if (strncmp(msg, "1", 1) == 0) {
        test_accept();
    }

    else if (strncmp(msg, "2", 1) == 0) {
        test_bind();
    }

    else if (strncmp(msg, "3", 1) == 0) {
        test_connect();
    }

    else if (strncmp(msg, "4", 1) == 0) {
        test_getpeername();
    }

    else if (strncmp(msg, "5", 1) == 0) {
        test_getsockname();
    }

    else if (strncmp(msg, "6", 1) == 0) {
        test_getsockopt();
    }

    else if (strncmp(msg, "7", 1) == 0) {
        test_setsockopt();
    }

    else if (strncmp(msg, "8", 1) == 0) {
        test_listen();
    }

    else if (strncmp(msg, "9", 1) == 0) {
        test_recv();
    }

    else if (strncmp(msg, "a", 1) == 0) {
#ifdef DREAMCAST
        test_tmr();
#endif
    }

    else if (strncmp(msg, "t", 1) == 0) {
        td_main();
    }

    else if (strncmp(msg, "s", 1) == 0) {
        select_main();
    }

    else if (strncmp(msg, "d", 1) == 0) {
        /* PPPの接続をきる */
#ifdef DREAMCAST
        disconnect();
#endif
        ;
    }
    menu();
}

/*
 * socket test menu
 */

static void menu()
{
    DebugPrint("\r\n*** socket test menu ***\r\n");

    /*          0         1         2         3         4         5         6         7         8 */
    /*          012345678901234567890123456789012345678901234567890123456789012345678901234567890 */
    /*          *       *       *       *       *       *       *       *       *       *       * */
    /*          *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   *   * */
    DebugPrint("1.accept() 2.bind() 3.connect() 4.getpeername() 5.getsockname() 6.getsockopt()\n");
    DebugPrint("7.setsockopt() 8.listen() 9.recv() 10.recvfrom() 11.select() 12.send()\n");
    DebugPrint("13.sendto() 14.shutdown() 15.socket() 17.sock_close()\n");
    DebugPrint("18.sock_read() 19.sock_write() 20.gethostbyname() t.telnetd d.disconnect() \n");
    DebugPrint("> ");
}

/*
 * 1.accept()
 */
void test_accept()
{
    char    *msg;
    int     s;
    struct sockaddr     addr;
    int     addrlen;
    int     ret;
    u_short port;
    u_char  ip_addr[4];

    DebugPrint("socket = ");
    msg = DebugGets();
    sscanf(msg, "%d", &s);
    addrlen = sizeof(struct sockaddr);

    ret = accept(s, &addr, &addrlen);
    DebugPrint("ret = %d\n", ret);
    if (ret >= 0) {
        DebugPrint("sa_family = %d\n", addr.sa_family);
        memcpy(&port, (void *)&(addr.sa_data[0]), 2);
        DebugPrint("port = %d\n", ntohs(port));
        memcpy(ip_addr, &(addr.sa_data[2]), 4);
        DebugPrint("addr = %d.%d.%d.%d\n", ip_addr[0], ip_addr[1], ip_addr[2],
            ip_addr[3]);
        DebugPrint("ret = %d\n", ret);
    }
    else {
        DebugPrint("errno = %d\n", errno);
    }
}

/*
 * 2.bind()
 */
void test_bind()
{
    char    *msg;
    int     s;
    struct sockaddr_in      addr;
    int     addrlen;
    int     ret;
    u_short family;
    u_short port;
    u_short port_work;
    u_char  ip_addr[4];
    int     tmp_0;
    int     tmp_1;
    int     tmp_2;
    int     tmp_3;
    u_long  address;

    DebugPrint("socket = ");
    msg = DebugGets();
    sscanf(msg, "%d", &s);

    addrlen = sizeof(struct sockaddr);

    DebugPrint("family(AF_INET:2) = ");
    msg = DebugGets();
    sscanf(msg, "%d", &tmp_0);
    family = (short)tmp_0;
    addr.sin_family = family;

    DebugPrint("port = ");
    msg = DebugGets();
    sscanf(msg, "%d", &tmp_0);
    port = (short)tmp_0;
    port_work = htons(port);
    memcpy(&(addr.sin_port), &port_work, 2);

    DebugPrint("ip address(xxx.xxx.xxx.xxx) = ");
    msg = DebugGets();
#ifdef UNIX
    address = inet_addr(msg);
    memcpy(&(addr.sin_addr.s_addr), &address, 4);
#else
    sscanf(msg, "%d.%d.%d.%d", &tmp_0, &tmp_1, &tmp_2, &tmp_3);
    ip_addr[0] = (u_char)tmp_0;
    ip_addr[1] = (u_char)tmp_1;
    ip_addr[2] = (u_char)tmp_2;
    ip_addr[3] = (u_char)tmp_3;
    memcpy(&(addr.sin_addr.s_addr), ip_addr, 4);
#endif

#if 0
    DebugPrint("s = %d\n", s);
    DebugPrint("addr.sin_family = %d\n", addr.sin_family);
    DebugPrint("addr.sin_port = %d\n", (u_short)addr.sin_port);
    DebugPrint("addr.sin_addr.s_addr = %08x\n", (u_long)addr.sin_addr.s_addr);
#endif

    ret = bind(s, (struct sockaddr *)&addr, sizeof(addr));

    DebugPrint("ret = %d\n", ret);
    if (ret < 0) {
        DebugPrint("errno = %d\n", errno);
    }
}

/*
 * 3.connect()
 */
void test_connect()
{
    char    *msg;
    int     s;
    struct sockaddr     addr;
    int     addrlen;
    int     ret;
    u_short family;
    u_short port;
    u_short port_work;
    u_char  ip_addr[4];
    int     tmp_0;
    int     tmp_1;
    int     tmp_2;
    int     tmp_3;

    DebugPrint("socket = ");
    msg = DebugGets();
    sscanf(msg, "%d", &s);

    addrlen = sizeof(struct sockaddr);

    DebugPrint("family(AF_INET:2) = ");
    msg = DebugGets();
    sscanf(msg, "%d", &tmp_0);
    addr.sa_family = (u_short)tmp_0;

    DebugPrint("port = ");
    msg = DebugGets();
    sscanf(msg, "%d", &tmp_0);
    port = (u_short)tmp_0;
    port_work = htons(port);
    memcpy(&(addr.sa_data[0]), &port_work, 2);

    DebugPrint("ip address(xxx.xxx.xxx.xxx) = ");
    msg = DebugGets();
    sscanf(msg, "%d.%d.%d.%d", &tmp_0, &tmp_1, &tmp_2, &tmp_3);
    ip_addr[0] = (u_char)tmp_0;
    ip_addr[1] = (u_char)tmp_1;
    ip_addr[2] = (u_char)tmp_2;
    ip_addr[3] = (u_char)tmp_3;
    memcpy(&(addr.sa_data[2]), ip_addr, 4);

    ret = connect(s, &addr, addrlen);

    DebugPrint("ret = %d\n", ret);
    if (ret < 0) {
        DebugPrint("errno = %d\n", errno);
    }
}

/*
 * 4.getpeername()
 */
void test_getpeername()
{
    char    *msg;
    int     s;
    struct sockaddr     addr;
    int     addrlen;
    int     ret;
    u_short port;
    u_char  ip_addr[4];

    DebugPrint("socket = ");
    msg = DebugGets();
    sscanf(msg, "%d", &s);

    addrlen = sizeof(struct sockaddr);

    ret = getpeername(s, &addr, &addrlen);

    if (ret == 0) {
        DebugPrint("ret = 0\n");
        DebugPrint("family = %d\n", addr.sa_family);
        memcpy(&port, &(addr.sa_data[0]), 2);
        DebugPrint("port = %d\n", ntohs(port));
        DebugPrint("ip address = %d.%d.%d.%d\n", (u_char)addr.sa_data[2],
            (u_char)addr.sa_data[3], (u_char)addr.sa_data[4],
            (u_char)addr.sa_data[5]);
        DebugPrint("addrlen = %d\n", addrlen);
    }
    else {
        DebugPrint("ret = %d\n", ret);
        DebugPrint("errno = %d\n", errno);
    }
}

/*
 * 5.getsockname()
 */
void test_getsockname()
{
    char    *msg;
    int     s;
    struct sockaddr     addr;
    int     addrlen;
    int     ret;
    u_short port;

    DebugPrint("socket = ");
    msg = DebugGets();
    sscanf(msg, "%d", &s);

    addrlen = sizeof(struct sockaddr);

    ret = getsockname(s, &addr, &addrlen);

    if (ret == 0) {
        DebugPrint("ret = 0\n");
        DebugPrint("family = %d\n", addr.sa_family);
        memcpy(&port, &(addr.sa_data[0]), 2);
        DebugPrint("port = %d\n", ntohs(port));
        DebugPrint("ip address = %d.%d.%d.%d\n", (u_char)addr.sa_data[2],
            (u_char)addr.sa_data[3], (u_char)addr.sa_data[4],
            (u_char)addr.sa_data[5]);
        DebugPrint("addrlen = %d\n", addrlen);
    }
    else {
        DebugPrint("ret = %d\n", ret);
        DebugPrint("errno = %d\n", errno);
    }
}

/*
 * 6.getsockopt()
 */
void test_getsockopt()
{
    char    *msg;
    int     s;
    int     ret;
    int     level;
    int     optname;
    short   optval;
    int     optlen;

    DebugPrint("socket = ");
    msg = DebugGets();
    sscanf(msg, "%d", &s);

    DebugPrint("level(SOL_SOCKET:-1) = ");
    msg = DebugGets();
    sscanf(msg, "%d", &level);

    DebugPrint("optname(SO_NOBLK:512, SO_OOBINLINE:256) = ");
    msg = DebugGets();
    sscanf(msg, "%d", &optname);

    ret = getsockopt(s, SOL_SOCKET, optname, (char *)&optval, &optlen);

    if (ret == 0) {
        DebugPrint("ret = 0\n");
        DebugPrint("optval = %d\n", optval);
        DebugPrint("optlen = %d\n", optlen);
    }
    else {
        DebugPrint("ret = %d\n", ret);
        DebugPrint("errno = %d\n", errno);
    }
}

/*
 * 7.setsockopt()
 */
void test_setsockopt()
{
    char    *msg;
    int     s;
    int     ret;
    int     level;
    int     optname;
    short   optval;
    int     optlen;
    int     tmp;

    DebugPrint("socket = ");
    msg = DebugGets();
    sscanf(msg, "%d", &s);

    DebugPrint("level(SOL_SOCKET:-1) = ");
    msg = DebugGets();
    sscanf(msg, "%d", &level);

    DebugPrint("optname(SO_NOBLK:512, SO_OOBINLINE:256) = ");
    msg = DebugGets();
    sscanf(msg, "%d", &optname);

    DebugPrint("optval(0, 1) = ");
    msg = DebugGets();
    sscanf(msg, "%d", &tmp);
    optval = (short)tmp;

    DebugPrint("optlen(2) = ");
    msg = DebugGets();
    sscanf(msg, "%d", &optlen);

    ret =  setsockopt(s, SOL_SOCKET, optname, (char *)&optval, optlen);
    DebugPrint("ret = %d\n", ret);
    if (ret < 0) {
        DebugPrint("errno = %d\n", errno);
    }
}

/*
 * 8.listen()
 */
void test_listen()
{
    char    *msg;
    int     s;
    int     ret;
    int     backlog;

    DebugPrint("socket = ");
    msg = DebugGets();
    sscanf(msg, "%d", &s);

    DebugPrint("backlog = ");
    msg = DebugGets();
    sscanf(msg, "%d", &backlog);

    ret = listen(s, backlog);

    DebugPrint("ret = %d\n", ret);
    if (ret < 0) {
        DebugPrint("errno = %d\n", errno);
    }
}

/*
 * 9.recv()
 */
void test_recv()
{
    char    *msg;
    int     s;
    int     ret;
    static char     buff[4096];
    int     len;
    int     flags;
    int     i;
    int     j;
    int     size;

    DebugPrint("socket = ");
    msg = DebugGets();
    sscanf(msg, "%d", &s);

    DebugPrint("len = ");
    msg = DebugGets();
    sscanf(msg, "%d", &len);

    DebugPrint("flags(0) = ");
    msg = DebugGets();
    sscanf(msg, "%d", &flags);

    ret = recv(s, buff, len, flags);

    if (ret >= 0) {
        size = ret;
        DebugPrint("ret = %d\n", ret);
        i = 0;
        for (; ;) {
            for (j = 0; ((j < 16) && (size > 0)); j++) {
                DebugPrint("%02x ", (u_char)buff[i]);
                i++;
                size--;
            }
            DebugPrint("\n");
            if (size <= 0) {
                break;
            }
        }
    }
    else {
        DebugPrint("ret = %d\n", ret);
        DebugPrint("errno = %d\n", errno);
    }
}

/*
 * 10.recvfrom()
 */
void test_recvfrom()
{
    char    *msg;
    int     s;
    struct sockaddr     addr;
    int     addrlen;
    int     ret;
    u_short family;
    u_short port;
    u_short port_work;
    static char     buff[1472];
    int     len;
    int     flags;
    int     i;
    int     j;
    int     size;

    DebugPrint("socket = ");
    msg = DebugGets();
    sscanf(msg, "%d", &s);

    DebugPrint("len = ");
    msg = DebugGets();
    sscanf(msg, "%d", &len);

    DebugPrint("flags(0) = ");
    msg = DebugGets();
    sscanf(msg, "%d", &flags);

    addrlen = sizeof(struct sockaddr);

    ret = recvfrom(s, buff, len, flags, &addr, &addrlen);
    size = ret;

    if (ret >= 0) {
        DebugPrint("ret = %d\n", ret);
        DebugPrint("family = %d\n", addr.sa_family);
        memcpy(&port, &(addr.sa_data[0]), 2);
        DebugPrint("port = %d\n", ntohs(port));
        DebugPrint("ip address = %d.%d.%d.%d\n", (u_char)addr.sa_data[2],
            (u_char)addr.sa_data[3], (u_char)addr.sa_data[4],
            (u_char)addr.sa_data[5]);
        DebugPrint("addrlen = %d\n", addrlen);
        i = 0;
        for (; ;) {
            for (j = 0; ((j < 16) && (size > 0)); j++) {
                DebugPrint("%02x ", (u_char)buff[i]);
                i++;
                size--;
            }
            DebugPrint("\n");
            if (size <= 0) {
                break;
            }
        }
    }
    else {
        DebugPrint("ret = %d\n", ret);
        DebugPrint("errno = %d\n", errno);
    }
}

/*
 * 11.select()
 */
void test_select()
{
    char    *msg;
    int     ret;
    int     fd;
    int     width;
    long    tmp;
    struct timeval  timeout;
    static fd_set   readfds;
    static fd_set   writefds;
    static fd_set   exceptfds;
    static fd_set   *rfd, *wfd, *efd;

    while (1) {
        DebugPrint("1.readfds 2.writefds 3.exceptfds 4.select() q.quit = ");
        msg = DebugGets();
        if (strncmp(msg, "1", 1) == 0) {
            if (test_fd_set(&readfds) == -1) {
				rfd = NULL;
			}
			else {
				rfd = &readfds;
			}
        }
        else if (strncmp(msg, "2", 1) == 0) {
			if (test_fd_set(&writefds) == -1) {
				wfd = NULL;
			}
			else {
				wfd = &writefds;
			}
        }
        else if (strncmp(msg, "3", 1) == 0) {
            if (test_fd_set(&exceptfds) == -1) {
				efd = NULL;
			}
			else {
				efd = &exceptfds;
			}
        }
        else if (strncmp(msg, "4", 1) == 0) {
            DebugPrint("width(1-256) = ");
            msg = DebugGets();
            sscanf(msg, "%d", &width);

            DebugPrint("timeout sec(-1:NULL) = ");
            msg = DebugGets();
            sscanf(msg, "%d", &tmp);
            timeout.tv_sec = tmp;

            DebugPrint("timeout micro sec(-1:NULL) = ");
            msg = DebugGets();
            sscanf(msg, "%d", &tmp);
            timeout.tv_usec = tmp;

            if ((timeout.tv_sec == -1) && (timeout.tv_usec == -1)) {
                ret = select(width, rfd, wfd, efd, NULL);
            }
            else {
                ret = select(width, rfd, wfd, efd, &timeout);
            }
            DebugPrint("ret = %d\n", ret);
            if (ret < 0) {
                DebugPrint("errno = %d\n", errno);
            }
        }
        else if (strncmp(msg, "q", 1) == 0) {
            break;
        }
    }
}

int test_fd_set(fd_set *fdset)
{
    char    *msg;
    int     fd;
    int     ret;

    while (1) {
        DebugPrint("1.FD_SET() 2.FD_CLR 3.FD_ISSET() 4.FD_ZERO 5.NULL q.quit = ");
        msg = DebugGets();

        if (strncmp(msg, "1", 1) == 0) {
            DebugPrint("fd = ");
            msg = DebugGets();
            sscanf(msg, "%d", &fd);
            if (fd == 0) {
                FD_SET(fd, (fd_set *)0);
            }
            else {
                FD_SET(fd, fdset);
            }
        }
        else if (strncmp(msg, "2", 1) == 0) {
            DebugPrint("fd = ");
            msg = DebugGets();
            sscanf(msg, "%d", &fd);
            FD_CLR(fd, fdset);
        }
        else if (strncmp(msg, "3", 1) == 0) {
            DebugPrint("fd = ");
            msg = DebugGets();
            sscanf(msg, "%d", &fd);
            ret = FD_ISSET(fd, fdset);
            DebugPrint("ret = %d\n", ret);
        }
        else if (strncmp(msg, "4", 1) == 0) {
            FD_ZERO(fdset);
        }
        else if (strncmp(msg, "5", 1) == 0) {
            return (-1);
        }
        else if (strncmp(msg, "q", 1) == 0) {
            break;
        }
    }
	return (0);
}

/*
 * 12.send()
 */
void test_send()
{
    char    *msg;
    int     s;
    int     ret;
    static char buff[4096];
    int     tmp;
    int     len;
    int     flags;
    int     i;
    char    c;

    c = 0;
    for (i = 0; i < 4096; i++) {
        buff[i] = c;
        c++;
    }

    DebugPrint("socket = ");
    msg = DebugGets();
    sscanf(msg, "%d", &s);

    for (i = 0; i < 4096; i++) {
        DebugPrint("buff[%d] = ", i);
        msg = DebugGets();
        sscanf(msg, "%02x", &tmp);
        if (*msg == '.') {
            break;
        }
        buff[i] = (char)tmp;
    }

    DebugPrint("len = ");
    msg = DebugGets();
    sscanf(msg, "%d", &len);

    DebugPrint("flags(0) = ");
    msg = DebugGets();
    sscanf(msg, "%d", &flags);

    ret = send(s, buff, len, flags);

    DebugPrint("ret = %d\n", ret);
    if (ret < 0) {
        DebugPrint("errno = %d\n", errno);
    }
}

/*
 * 13.sendto()
 */
void test_sendto()
{
    char    *msg;
    int     s;
    int     ret;
    static char buff[1472];
    int     tmp;
    int     len;
    int     flags;
    int     i;
    char    c;
    struct sockaddr     addr;
    int     addrlen;
    u_short port;
    u_short port_work;
    u_short family;
    u_char  ip_addr[4];
    int     tmp_0;
    int     tmp_1;
    int     tmp_2;
    int     tmp_3;

    c = 0;
    for (i = 0; i < 1472; i++) {
        buff[i] = c;
        c++;
    }

    DebugPrint("socket = ");
    msg = DebugGets();
    sscanf(msg, "%d", &s);

    for (i = 0; i < 1472; i++) {
        DebugPrint("buff[%d] = ", i);
        msg = DebugGets();
        sscanf(msg, "%02x", &tmp);
        if (*msg == '.') {
            break;
        }
        buff[i] = (char)tmp;
    }

    DebugPrint("len = ");
    msg = DebugGets();
    sscanf(msg, "%d", &len);

    DebugPrint("flags(0) = ");
    msg = DebugGets();
    sscanf(msg, "%d", &flags);

    addrlen = sizeof(struct sockaddr);

    DebugPrint("family(AF_INET:2) = ");
    msg = DebugGets();
    sscanf(msg, "%d", &tmp_0);
    family = (short)tmp_0;
    addr.sa_family = family;

    DebugPrint("port = ");
    msg = DebugGets();
    sscanf(msg, "%d", &tmp_0);
    port = (short)tmp_0;
    port_work = htons(port);
    memcpy(&(addr.sa_data[0]), &port_work, 2);

    DebugPrint("ip address(xxx.xxx.xxx.xxx) = ");
    msg = DebugGets();
    sscanf(msg, "%d.%d.%d.%d", &tmp_0, &tmp_1, &tmp_2, &tmp_3);
    ip_addr[0] = (u_char)tmp_0;
    ip_addr[1] = (u_char)tmp_1;
    ip_addr[2] = (u_char)tmp_2;
    ip_addr[3] = (u_char)tmp_3;
    memcpy(&(addr.sa_data[2]), ip_addr, 4);

    ret = sendto(s, buff, len, flags, &addr, addrlen);
    DebugPrint("ret = %d\n", ret);
    if (ret >= 0) {
        DebugPrint("family = %d\n", addr.sa_family);
        memcpy(&port, &(addr.sa_data[0]), 2);
        DebugPrint("port = %d\n", ntohs(port));
        DebugPrint("ip address = %d.%d.%d.%d\n", (u_char)addr.sa_data[2],
            (u_char)addr.sa_data[3], (u_char)addr.sa_data[4],
            (u_char)addr.sa_data[5]);
        DebugPrint("addrlen = %d\n", addrlen);
    }
    else {
        DebugPrint("errno = %d\n", errno);
    }
}

/*
 * 14.shutdown()
 */
void test_shutdown()
{
    char    *msg;
    int     s;
    int     ret;
    int     how;

    DebugPrint("socket = ");
    msg = DebugGets();
    sscanf(msg, "%d", &s);

    DebugPrint("how(0:can't recv, 1:can't send, 2:can't recv/send) = ");
    msg = DebugGets();
    sscanf(msg, "%d", &how);

    ret = shutdown(s, how);

    DebugPrint("ret = %d\n", ret);
    if (ret < 0) {
        DebugPrint("errno = %d\n", errno);
    }
}

/*
 * 15.socket()
 */
void test_socket()
{
    int     domain;
    int     type;
    int     protocol;
    char    *msg;
    int     ret;

    DebugPrint("domain(AF_INET:2) = ");
    msg = DebugGets();
    sscanf(msg, "%d", &domain);

    DebugPrint("type(SOCK_STREAM:1, SOCK_DGRAM:2) = ");
    msg = DebugGets();
    sscanf(msg, "%d", &type);

    DebugPrint("protocol(0) = ");
    msg = DebugGets();
    sscanf(msg, "%d", &protocol);

    ret = socket(domain, type, protocol);

    DebugPrint("ret = %d\n", ret);
    if (ret < 0) {
        DebugPrint("errno = %d\n", errno);
    }
}

#if 0
/*
 * 16.sock_closeall()
 */
void test_sock_closeall()
{
    int     socket;
    char    *msg;
    int     ret;

#ifdef DREAMCAST
    ret = sock_closeall();
    DebugPrint("ret = %d\n", ret);
#else
    DebugPrint("Not support.\n");
#endif
}
#endif

/*
 * 17.sock_close()
 */
void test_sock_close()
{
    int     socket;
    char    *msg;
    int     ret;

    DebugPrint("socket = ");
    msg = DebugGets();
    sscanf(msg, "%d", &socket);

#ifdef DREAMCAST
    ret = sock_close(socket);
#endif

#ifdef WINDOWS
    ret = closesocket(socket);
#endif

#ifdef UNIX
    ret = close(socket);
#endif

    DebugPrint("ret = %d\n", ret);
    if (ret < 0) {
        DebugPrint("errno = %d\n", errno);
    }
}

/*
 * 18.sock_read()
 */
void test_sock_read()
{
    char    *msg;
    int     s;
    int     ret;
    static char     buff[4096];
    int     len;
    int     i;
    int     j;
    int     size;

#ifdef WINDOWS
    DebugPrint("Not support.\n");
    return;
#else

    DebugPrint("socket = ");
    msg = DebugGets();
    sscanf(msg, "%d", &s);

    DebugPrint("len = ");
    msg = DebugGets();
    sscanf(msg, "%d", &len);

#ifdef DREAMCAST
    ret = sock_read(s, buff, len);
#endif
#ifdef UNIX
    ret = read(s, buff, len);
#endif
    if (ret >= 0) {
        size = ret;
        DebugPrint("ret = %d\n", ret);
        i = 0;
        for (; ;) {
            for (j = 0; ((j < 16) && (size > 0)); j++) {
                DebugPrint("%02x ", (u_char)buff[i]);
                i++;
                size--;
            }
            DebugPrint("\n");
            if (size <= 0) {
                break;
            }
        }
    }
    else {
        DebugPrint("ret = %d\n", ret);
        DebugPrint("errno = %d\n", errno);
    }
#endif
}

/*
 * 19.sock_write()
 */
void test_sock_write()
{
    char    *msg;
    int     s;
    int     ret;
    static char buff[4096];
    int     tmp;
    int     len;
    int     i;
    char    c;

#ifdef WINDOWS
    DebugPrint("Not support.\n");
    return;
#else
    c = 0;
    for (i = 0; i < 4096; i++) {
        buff[i] = c;
        c++;
    }

    DebugPrint("socket = ");
    msg = DebugGets();
    sscanf(msg, "%d", &s);

    for (i = 0; i < 4096; i++) {
        DebugPrint("buff[%d] = ", i);
        msg = DebugGets();
        sscanf(msg, "%02x", &tmp);
        if (*msg == '.') {
            break;
        }
        buff[i] = (char)tmp;
    }

    DebugPrint("len = ");
    msg = DebugGets();
    sscanf(msg, "%d", &len);

#ifdef DREAMCAST
    ret = sock_write(s, buff, len);
#endif
#ifdef UNIX
    ret = write(s, buff, len);
#endif

    DebugPrint("ret = %d\n", ret);
    if (ret < 0) {
        DebugPrint("errno = %d\n", errno);
    }
#endif
}

/*
 * 20.gethostbyname()
 */
void test_gethostbyname()
{
    struct hostent  *host;
    char    *ip_addr;
    char    *msg;
    char    name[128];

    DebugPrint("name = ");
    msg = DebugGets();
    sscanf(msg, "%s", name);

    host = gethostbyname(name);
    if (host != (struct hostent *)0) {
        DebugPrint("host name = %s\n", host->h_name);
        DebugPrint("host address type = %d\n", host->h_addrtype);
        DebugPrint("length = %d\n", host->h_length);
        ip_addr = (char *)*(host->h_addr_list);
        DebugPrint("ip address = %d.%d.%d.%d\n", (u_char)ip_addr[0],
            (u_char)ip_addr[1], (u_char)ip_addr[2], (u_char)ip_addr[3]);
    }
}



void select_main()
{
    char    *msg;
    int     ret;
    static char     data[1514];
    int     error;
    int     s;
    struct sockaddr addr;
    struct sockaddr fsin;
    u_short port;
    u_long  ip_addr;
    static int  bBroadcast = 1;
    u_long      one = 1;
    fd_set  afds;
    fd_set  rfds;
    int     nfds;
    int     ssock;
    int     alen;
    int     fd;
    int     tmp;
    int     *ptr;

    struct timeval  timeout;

#ifdef WINDOWS
    WORD    wVerReq;
    WSADATA wsadata;

    wVerReq = MAKEWORD(1, 1);
    error = WSAStartup(wVerReq, &wsadata);
    if (error != 0) {
        return;
    }
#endif
    /* ソケットを作成 */
    s = socket(AF_INET, SOCK_STREAM, 0);
    if(s < 0){
        printf("socket error");
            return;
    }

    addr.sa_family = AF_INET;

    DebugPrint("port = ");
    msg = DebugGets();
    sscanf(msg, "%d", &tmp);

    port = htons((short)tmp);
    memcpy(&(addr.sa_data[0]), &port, 2);
    ip_addr = INADDR_ANY;
    memcpy(&(addr.sa_data[2]), &ip_addr, 4);

    /* BIND */
    ret = bind(s, &addr, sizeof(addr));
    if (ret != 0) {
        printf("bind error = %d\n", errno);
    }

    /* LISTEN */
    ret = listen(s, 16);
    if (ret < 0) {
        printf("listen error = %d\n", errno);
    }

    nfds = FD_SETSIZE;

    printf("nfds = %d\n", nfds);

    FD_ZERO(&afds);
    FD_SET(s, &afds);

/*DebugPrint("a fds_bits[0] = %08x\n", afds.fds_bits[0]);*/
    ret = FD_ISSET(s, &afds);
    DebugPrint("ret = %d\n", ret);

#if 0
    while (1) {
        ssock = accept(s, 0, 0);
        if (ssock != INVALID_SOCKET) {
            printf("accept socket = %d\n", ssock);
        }
    }
#endif
    while (1) {
        memcpy((char *)&rfds, (char *)&afds, sizeof(rfds));
/*DebugPrint("r fds_bits[0] = %08x\n", rfds.fds_bits[0]);*/
        timeout.tv_sec = 60;
        timeout.tv_usec = 0;
        ret = select(nfds, &rfds, (fd_set *)0, (fd_set *)0,
            (struct timeval *)&timeout);
        printf("select ret = %d\n", ret);
        if (ret < 0) {
            printf("ret = %d\n", ret);
            printf("select error = %d\n", errno);
            ptr = (int *)&errno;
            printf("ptr = %08x\n", ptr);
            return;
        }
        if (FD_ISSET(s, &rfds)) {
            alen = sizeof(fsin);
            ssock = accept(s, &fsin, &alen);
            printf("ssock = %d\n", ssock);
            if (ssock < 0) {
                printf("accept error = %d\n", errno);
                return;
            }
            FD_SET(ssock, &afds);
        }
        printf("???");
        for (fd = 0; fd < 256; fd++) {
            if (fd != s && FD_ISSET(fd, &afds)) {
                printf("fd = %d is accept\n", fd);
            }
        }
        break;
    }
}

#ifdef DREAMCAST
void x_dummy();
void test_tmr()
{
    unsigned int    count1, count2, count, micro;

    count1 = syTmrGetCount();

    x_dummy();

    count2 = syTmrGetCount();

    count = syTmrDiffCount(count1, count2);

    micro = syTmrCountToMicro(count);

    DebugPrint("time = %d micro sec\n", micro);

}

void x_dummy()
{
    int     i, a, b;

    for (i = 0; i < 1000000; i++) {
        a = b;
    }
}

#endif
