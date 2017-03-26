/*
 *-----------------------------------------------------------------------------
 *  FILE: sh4scif.h
 *
 *      Copyright(c) 1998 SEGA System R&D Dept.
 *
 *  PURPOSE:
 *
 *      SH4-SCIF 簡易通信ライブラリヘッダ
 *
 *  DESCRIPTION:
 *
 *  AUTHOR(S):
 *
 *      1998/5/19  S.Uchida Ver 0.00
 *
 *  MOD HISTORY:
 *
 *-----------------------------------------------------------------------------
 */

#ifndef _SH4SCIF_H_
#define _SH4SCIF_H_

/* SH-4 200MHz */
enum SCI_SPEED {
	BPS_9600   = 0xa2,
	BPS_19200  = 0x50,
	BPS_38400  = 0x28,
	BPS_57600  = 0x1a,
	BPS_115200 = 0x0d,
	BPS_AUTO   = -1
};

extern long scif_init(void* rcvbuf, long rcvsize, void* sndbuf, long sndsize);
extern long scif_open(long brr);
extern void scif_putq(char data);
extern long scif_close(void);
extern long scfi_TxFreeSize(void);
extern long scif_isget(void);
extern short scif_get(void);
extern long scif_isbreak(void);

#endif /* _SH4SCIF_H_ */