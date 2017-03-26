/*
	dns.h
	Copyright (C) 1996,97 ACCESS Co.,Ltd.
	All rights reserved.
*/

/* $Header: /NetFront/TCP/dm_sdk/dns/dns.h 3     99/01/19 18:12 Ueda $ */

#ifdef __cplusplus /* Support for C++ */
extern "C" {
#endif /* __cplusplus */

#ifndef __DNS_H__
#define __DNS_H__

#define DNS_STANDALONE 1

#if DNS_STANDALONE

/*                  */
/* basic definition */
/*                  */

/* null pointer */

#ifndef nil
#define nil 0
#endif

/* boolean */

#ifndef bool
#define bool int
#endif

#ifndef false
#define false 0
#endif

#ifndef true
#define true (!false)
#endif

/* integer */

/* 8 bit unsigned integer */
#ifndef wave_byte
#define wave_byte unsigned char
#endif

/* 16 bit signed integer */
#ifndef wave_short
#define wave_short signed short
#endif

/* 32 bit signed integer */
#ifndef wave_int
#define wave_int signed long 
#endif

/* bit flag */

/* 8 bit unsigned integer */
#ifndef wave_8bit
#define wave_8bit unsigned char
#endif

/* 16 bit unsigned integer */
#ifndef wave_16bit
#define wave_16bit unsigned short
#endif

/* 32 bit signed integer */
#ifndef wave_32bit
#define wave_32bit unsigned long
#endif

/* character and string */
#ifndef wave_char
#define wave_char wave_byte
#endif

#ifndef WAVE_TEXT
#define WAVE_TEXT(textliteral) ((wave_char *)(textliteral))
#endif

#ifndef WAVE_CHAR
#define WAVE_CHAR(charliteral) (charliteral)
#endif

#define kWave_MaxHostNameLen 1024

/*       */
/* error */
/*       */

enum {
    eOK         = 0,
    eGeneric    = -1,
    eWouldBlock = -2,
    eMemory     = -3,
    eIO         = -4,
    eNotFound   = -5,
    eTimedOut   = -6
};

#else /* not standalone */ 

#include <wave/wave.h>
#include <wave/iwave.h>

#endif /* DNS_STANDALONE */

/* asynchronous version */

void ADNS_Initialize(wave_char *in_def_domain, wave_32bit in_prim_svr, wave_32bit in_sec_svr);
void ADNS_Finalize();
wave_int ADNS_GetTicket(wave_char *in_host);
void ADNS_ReleaseTicket(wave_int in_ticket_id);
wave_int ADNS_LookUp(wave_int in_ticket_id, wave_byte *out_addr);
void ADNS_GetTicketInfo(wave_int in_ticket_id, wave_char **out_host);

/* synchronous version */

unsigned long DNS_GetAddress(char *in_host);

#endif /* __DNS_H__ */

#ifdef __cplusplus
} /* End of extern "C" { */
#endif /* __cplusplus */
