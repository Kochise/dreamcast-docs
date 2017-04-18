/* 
 * File: sg_Cache.h
 * Desc: RAW CACHE library
 * Auth: Jiro Terakwa(SYSTEM R&D)
 * Create: 1998/03/25 Jiro Terakawa: Ver. 1.00
 * Change: add cacheOCI(), cacheICI() (1998/03/16 Jiro Terakawa)
 *         1998/05/01 coding standard. Ver. 1.10
 * Note: Manuplate CCR is allowed only from codes running on P2 area.
 *
 */
#ifndef _SG_CACHE_H_
#define _SG_CACHE_H_

#define  SYD_CACHE_FORM_IC_INDEX  0x00008000
#define  SYD_CACHE_FORM_OC_INDEX  0x00000080
#define  SYD_CACHE_FORM_IC_ENABLE 0x00000100
#define  SYD_CACHE_FORM_OC_ENABLE 0x00000001
#define  SYD_CACHE_FORM_OC_RAM    0x00000020
#define  SYD_CACHE_FORM_P1_CB     0x00000004
#define  SYD_CACHE_FORM_P0_WT     0x00000002

typedef Uint32 SY_CACHE_FORM;

/* Change CCR is only allowed for code on P2 area */
#define syCacheInit(a) \
  (((Void (*)(SY_CACHE_FORM))((Uint32)syCacheInit_P2_|0xA0000000))(a))

#define syCacheICI() \
  (((Void (*)(Void))((Uint32)syCacheICI_P2_|0xA0000000))())

#define syCacheOCI() \
  (((Void (*)(Void))((Uint32)syCacheOCI_P2_|0xA0000000))())

/* decralation of functions */
Void syCacheInit_P2_(SY_CACHE_FORM form);
Void syCacheICI_P2_(Void);
Void syCacheOCI_P2_(Void);
Void syCacheOCBI(Void *address, Uint32 size);
Void syCacheOCBP(Void *address, Uint32 size);
Void syCacheOCWB(Void *address, Uint32 size);
Void syCachePREF(Void *address, Uint32 size);
Void syCacheMOVCAL(Void *address, Uint32 data);
Void syCachePurgeAll(Void);
Void syCacheAllocCacheRAM(Void **address, Uint32 block);
Void syCacheFreeCacheRAM(Void *address);

#endif /* _SG_CACHE_H_ */
