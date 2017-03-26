/*
 * File: sg_Mmu.h
 * Desc: RAW MMU library
 * Auth: Jiro Terakwa(SYSTEM R&D)
 * Create: 1998/03/25 Jiro Terakawa: Ver. 1.0
 * Change: 1998/05/01 coding standard.
 *
 * Func:
 * Note:
 *
 */
#ifndef _SG_MMU_H_
#define _SG_MMU_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

typedef Uint32 SYMMU;

#define  SYD_MMU_PAGESIZE_1K  1
#define  SYD_MMU_PAGESIZE_4K  2
#define  SYD_MMU_PAGESIZE_64K 3
#define  SYD_MMU_PAGESIZE_1M  4
typedef Sint8 SY_MMU_PAGESIZE;

#define  MMU_CACHEE_WT (0x08|0x00)
#define  MMU_CACHEE_WB (0x08|0x01)
#define  MMU_CACHED    (0x00|0x00)
typedef Sint8 SY_MMU_CACHE;

/* decralation of functions */

Void syMmuInit(Uint8 urb);
SYMMU syMmuAddEntry(Void *paddress, Void *vaddress, SY_MMU_PAGESIZE size);
Void syMmuDeleteEntry(SYMMU mmuPageNum);
Void syMmuCacheCtrl(SYMMU mmuPageNum, SY_MMU_CACHE cacheCtrl);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _SG_MMU_H_ */