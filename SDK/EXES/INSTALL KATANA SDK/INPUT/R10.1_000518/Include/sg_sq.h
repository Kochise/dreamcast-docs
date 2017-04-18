/* 
 * File: sg_Sq.h
 * Desc: RAW SQ (store queue) library
 * Auth: Jiro Terakwa(SYSTEM R&D)
 * Create: 1998/03/25 Jiro Terakawa: Ver. 1.0
 * Change: 1998/04/27 Add sqStart utility func.
 *         1998/05/01 coding standard.
 * Func:
 * Note:
 *
 */
#ifndef _SG_SQ_H_
#define _SG_SQ_H_

#define  SYD_SQNUM_0  1
#define  SYD_SQNUM_1  2
#define  SYD_SQNUM_01 3

typedef Sint8 SY_SQNUM;

/* decralation of functions */

Void sySqInit(Void);

Void sySqFinish(Void);

#define sySqOpen(sqNum) \
  set_imask(15)

#define sySqClose(sqNum) \
  set_imask(0)

#if 0
Void *sySqStart(Uint32 *size, Void *dstArray);
#else
Void *sySqStart(Void *dstArray);
#endif

Void *sySqEnd(Void *sqArray);

#endif /* _SG_SQ_H_ */
