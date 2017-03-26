/*
 *  Shinobi Library
 *  Copyright (c) 1998 SEGA
 *  
 *       Timer Uint
 *
 *  Module  : Library Header File
 *  File    : sg_sytmr.h
 *  Create  : 1998-03-03
 *  Modify  : 1998-06-05
 *  Version : 1.00
 *  Note    :
 */


#ifndef _SG_SYTMU_H_
#define _SG_SYTMU_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/******* counter clock define **********************************************/
#define SYD_TMR_CLOCK_P4        (0)         /* PÉ”/4                       */
#define SYD_TMR_CLOCK_P16       (1)         /* PÉ”/16                      */
#define SYD_TMR_CLOCK_P64       (2)         /* PÉ”/64                      */
#define SYD_TMR_CLOCK_P256      (3)         /* PÉ”/256                     */
#define SYD_TMR_CLOCK_P1024     (4)         /* PÉ”/1024                    */
typedef Uint16 SY_TMR_CLOCK;

/******* initialize ********************************************************/
void syTmrInit(void);

/******* API ***************************************************************/
/* free running timer */
Uint32 syTmrGetCount(void);
Uint32 syTmrDiffCount(Uint32, Uint32);
Uint32 syTmrCountToMicro(Uint32);
Uint32 syTmrMicroToCount(Uint32);
/* general purpose timer */
void syTmrGenStart(void);
void syTmrGenStop(void);
void syTmrGenSetInt(void(*)(void *), void *);
void syTmrGenCancelInt(void);
void syTmrGenSetClock(SY_TMR_CLOCK);
void syTmrGenSetCount(Uint32);
Uint32 syTmrGenGetCount(void);
Uint32 syTmrGenMicroToCount(Uint32, SY_TMR_CLOCK);
Uint32 syTmrGenCountToMicro(Uint32, SY_TMR_CLOCK);
Uint32 syTmrGenDiffCount(Uint32, Uint32);

#ifdef __cplusplus
	   }
#endif /* __cplusplus */

#endif /* _SG_SYTMU_H_ */

/******************************* end of file *******************************/
