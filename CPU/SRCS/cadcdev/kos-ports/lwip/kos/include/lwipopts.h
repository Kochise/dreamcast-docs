/*
 * Copyright (c) 2001, 2002 Swedish Institute of Computer Science.
 * All rights reserved. 
 * 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT 
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 * 
 * Author: Adam Dunkels <adam@sics.se>
 *
 */

/* Modified for KOS by Dan Potter */

#ifndef __LWIPOPTS_H__
#define __LWIPOPTS_H__

#define NO_SYS 0
#define LWIP_CALLBACK_API 1

/* -------- TCP Timer Intervals ------- */
#if 0
#define TCP_TMR_INTERVAL       1    /* The TCP timer interval in
                                       milliseconds. */

#define TCP_FAST_INTERVAL      2    /* the fine grained timeout in
                                       milliseconds */

#define TCP_SLOW_INTERVAL      5    /* the coarse grained timeout in
                                       milliseconds */
#endif

#define TCP_TMR_INTERVAL	100
#define TCP_FAST_INTERVAL	100
#define TCP_SLOW_INTERVAL	100

/* ---------- Memory options ---------- */
/* MEM_ALIGNMENT: should be set to the alignment of the CPU for which
   lwIP is compiled. 4 byte alignment -> define MEM_ALIGNMENT to 4, 2
   byte alignment -> define MEM_ALIGNMENT to 2. */
#define MEM_ALIGNMENT           4

/* MEM_SIZE: the size of the heap memory. If the application will send
a lot of data that needs to be copied, this should be set high. */
#define MEM_SIZE                512 * 1024

/* MEMP_NUM_PBUF: the number of memp struct pbufs. If the application
   sends a lot of data out of ROM (or other static memory), this
   should be set high. */
#define MEMP_NUM_PBUF           32
/* MEMP_NUM_UDP_PCB: the number of UDP protocol control blocks. One
   per active UDP "connection". */
#define MEMP_NUM_UDP_PCB        8
/* MEMP_NUM_TCP_PCB: the number of simulatenously active TCP
   connections. */
#define MEMP_NUM_TCP_PCB        8
/* MEMP_NUM_TCP_PCB_LISTEN: the number of listening TCP
   connections. */
#define MEMP_NUM_TCP_PCB_LISTEN 16
/* MEMP_NUM_TCP_SEG: the number of simultaneously queued TCP
   segments. */
#define MEMP_NUM_TCP_SEG        255

/* The following four are used only with the sequential API and can be
   set to 0 if the application only will use the raw API. */
/* MEMP_NUM_NETBUF: the number of struct netbufs. */
//#define MEMP_NUM_NETBUF         64
/* MEMP_NUM_NETCONN: the number of struct netconns. */
//#define MEMP_NUM_NETCONN        64
/* MEMP_NUM_APIMSG: the number of struct api_msg, used for
   communication between the TCP/IP stack and the sequential
   programs. */
//#define MEMP_NUM_API_MSG        64
/* MEMP_NUM_TCPIPMSG: the number of struct tcpip_msg, which is used
   for sequential API communication and incoming packets. Used in
   src/api/tcpip.c. */
//#define MEMP_NUM_TCPIP_MSG      64
/* MEMP_NUM_SYS_TIMEOUT: the number of simulateously active
   timeouts. */
//#define MEMP_NUM_SYS_TIMEOUT    16

#define MEM_RECLAIM	1
#define MEMP_RECLAIM	1

/* ---------- Pbuf options ---------- */
/* PBUF_POOL_SIZE: the number of buffers in the pbuf pool. */
#define PBUF_POOL_SIZE          512

/* PBUF_POOL_BUFSIZE: the size of each pbuf in the pbuf pool. */
#define PBUF_POOL_BUFSIZE       1536

/* PBUF_LINK_HLEN: the number of bytes that should be allocated for a
   link level header. */
#define PBUF_LINK_HLEN          16

/* #define SYS_LIGHTWEIGHT_PROT	1 */

/* ---------- TCP options ---------- */
#define LWIP_TCP                1
#define TCP_TTL                 255

/* Controls if TCP should queue segments that arrive out of
   order. Define to 0 if your device is low on memory. */
#define TCP_QUEUE_OOSEQ         1

/* TCP Maximum segment size. */
#define TCP_MSS                 1476

/* TCP sender buffer space (bytes). */
#define TCP_SND_BUF             187452

/* TCP sender buffer space (pbufs). This must be at least = 2 *
   TCP_SND_BUF/TCP_MSS for things to work. */
#define TCP_SND_QUEUELEN        2 * TCP_SND_BUF/TCP_MSS

/* TCP receive window. */
#define TCP_WND                 65535

/* Maximum number of retransmissions of data segments. */
#define TCP_MAXRTX              12

/* Maximum number of retransmissions of SYN segments. */
#define TCP_SYNMAXRTX           4

/* ---------- ARP options ---------- */
#define ARP_TABLE_SIZE 10
#define ARP_QUEUEING 1

/* ---------- IP options ---------- */
/* Define IP_FORWARD to 1 if you wish to have the ability to forward
   IP packets across network interfaces. If you are going to run lwIP
   on a device with only one network interface, define this to 0. */
#define IP_FORWARD              0

/* If defined to 1, IP options are allowed (but not parsed). If
   defined to 0, all packets with IP options are dropped. */
#define IP_OPTIONS              1

#define IP_REASSEMBLY	1
#define IP_FRAG		1

/* ---------- ICMP options ---------- */
#define ICMP_TTL                255


/* ---------- DHCP options ---------- */
/* Define LWIP_DHCP to 1 if you want DHCP configuration of
   interfaces. DHCP is not implemented in lwIP 0.5.1, however, so
   turning this on does currently not work. */
#define LWIP_DHCP               0

/* 1 if you want to do an ARP check on the offered address
   (recommended). */
#define DHCP_DOES_ARP_CHECK     1

/* ---------- UDP options ---------- */
#define LWIP_UDP                1
#define UDP_TTL                 255


/* ---------- PPP options ---------- */
#define PPP_SUPPORT		1
#define NUM_PPP			1
#define PAP_SUPPORT		1
#define CHAP_SUPPORT		0
#define MSCHAP_SUPPORT		0
#define CBCP_SUPPORT		0
#define CCP_SUPPORT		0
#define VJ_SUPPORT		1
#define MD5_SUPPORT		1

#define FSM_DEFTIMEOUT		6
#define FSM_DEFMAXTERMREQS	2
#define FSM_DEFMAXCONFREQS	10
#define FSM_DEFMAXNAKLOOPS	5
#define UPAP_DEFTIMEOUT		6
#define UPAP_DEFREQTIME		30
#define CHAP_DEFTIMEOUT		6
#define CHAP_DEFTRANSMITS	10

#define LCP_ECHOINTERVAL	0
#define LCP_MAXECHOFAILS	3
#define PPP_MAXIDLEFLAG		100

#define PPP_MTU			1500
#define PPP_MAXMTU		1500
#define PPP_MINMTU		64
#define PPP_MRU			1500
#define PPP_MAXMRU		1500
#define PPP_DEFMRU		296
#define PPP_MINMRU		128

#define MAXNAMELEN		256
#define MAXSECRETLEN		256

/* ---------- Statistics options ---------- */
/*#define STATS*/

#ifdef STATS
#define LINK_STATS
#define IP_STATS
#define ICMP_STATS
#define UDP_STATS
#define TCP_STATS
#define MEM_STATS
#define MEMP_STATS
#define PBUF_STATS
#define SYS_STATS
#endif /* STATS */

/* Debugging */
#define DBG_FLAG_COMMON	(DBG_OFF | DBG_TRACE | DBG_LEVEL_WARNING)

#define DBG_TYPES_ON                    DBG_TRACE
#define DEMO_DEBUG                      DBG_FLAG_COMMON
#define ETHARP_DEBUG                    DBG_FLAG_COMMON
#define NETIF_DEBUG                     DBG_FLAG_COMMON
#define PBUF_DEBUG                      DBG_FLAG_COMMON
#define API_LIB_DEBUG                   DBG_FLAG_COMMON
#define API_MSG_DEBUG                   DBG_FLAG_COMMON
#define SOCKETS_DEBUG                   DBG_FLAG_COMMON
#define ICMP_DEBUG                      DBG_FLAG_COMMON
#define INET_DEBUG                      DBG_FLAG_COMMON
#define IP_DEBUG                        DBG_FLAG_COMMON
#define IP_REASS_DEBUG                  DBG_FLAG_COMMON
#define MEM_DEBUG                       DBG_FLAG_COMMON
#define MEMP_DEBUG                      DBG_FLAG_COMMON
#define SYS_DEBUG                       DBG_FLAG_COMMON
#define TCP_DEBUG                       DBG_FLAG_COMMON
#define TCP_INPUT_DEBUG                 DBG_FLAG_COMMON
#define TCP_FR_DEBUG                    DBG_FLAG_COMMON
#define TCP_RTO_DEBUG                   DBG_FLAG_COMMON
#define TCP_REXMIT_DEBUG                DBG_FLAG_COMMON
#define TCP_CWND_DEBUG                  DBG_FLAG_COMMON
#define TCP_WND_DEBUG                   DBG_FLAG_COMMON
#define TCP_OUTPUT_DEBUG                DBG_FLAG_COMMON
#define TCP_RST_DEBUG                   DBG_FLAG_COMMON
#define TCP_QLEN_DEBUG                  DBG_FLAG_COMMON
#define UDP_DEBUG                       DBG_FLAG_COMMON
#define TCPIP_DEBUG                     DBG_FLAG_COMMON
#define PPP_DEBUG                       DBG_FLAG_COMMON
#define SLIP_DEBUG                      DBG_FLAG_COMMON
#define DHCP_DEBUG                      DBG_FLAG_COMMON
#define DBG_MIN_LEVEL                   DBG_LEVEL_WARNING

#define LWIP_DEBUG 1

#endif /* __LWIPOPTS_H__ */
