/*
 * File: sg_Chain.h
 * Desc: interrupt chain handler library
 * Auth: Jiro Terakwa(SYSTEM R&D)
 * Create: 1998/03/25 Jiro Terakawa: Ver. 1.00
 * Change: 1998/05/01 Jiro Terakawa: Ver. 1.10
 *            rewrite as coding standard.
 */
#ifndef _SG_CHAIN_H_
#define _SG_CHAIN_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* PVR */
#define SYD_CHAIN_EVENT_IML6_NRM    0x0900
#define SYD_CHAIN_EVENT_IML6_VBLANK 0x0900 /* this shuld be registered to KAMUI */
#define SYD_CHAIN_EVENT_IML6_HBLANK 0x0920 /* this shuld be registered to KAMUI */
/* NRM */
#define SYD_CHAIN_EVENT_IML4_NRM    0x0A00
#define SYD_CHAIN_EVENT_IML4_MPDMAE 0x0A00
#define SYD_CHAIN_EVENT_IML4_MPVOVR 0x0A20
#define SYD_CHAIN_EVENT_IML4_CDDMAE 0x0A40
#define SYD_CHAIN_EVENT_IML4_AICADM 0x0A60
#define SYD_CHAIN_EVENT_IML4_EX0DMA 0x0A80
#define SYD_CHAIN_EVENT_IML4_EX1DMA 0x0AA0
#define SYD_CHAIN_EVENT_IML4_DADMAE 0x0AC0
/* EXT */
#define SYD_CHAIN_EVENT_IML4_EXT    0x0B00
#define SYD_CHAIN_EVENT_IML4_CD     0x0B00
#define SYD_CHAIN_EVENT_IML4_AICA   0x0B20
#define SYD_CHAIN_EVENT_IML4_MODEM  0x0B40
#define SYD_CHAIN_EVENT_IML4_EDEV   0x0B60

typedef Sint16 SY_CHAIN_EVENT;

typedef struct SYS_CHAIN_ISR_{
  Void (*usrIsr)(Void *);
  struct SYS_CHAIN_ISR_ *next;
  Void *arg;
  Uint32 priority;
} SYS_CHAIN_ISR;

typedef Uint32 SYCHAIN;

Void syChainInit(Void);
Void syChainFinish(Void);
SYCHAIN syChainAddHandler(SY_CHAIN_EVENT event,
			 Void (*usrIsr)(Void *),
			 Uint32 priority,
			 Void *arg);
Void syChainDeleteHandler(SYCHAIN chain);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _SG_CHAIN_H_ */