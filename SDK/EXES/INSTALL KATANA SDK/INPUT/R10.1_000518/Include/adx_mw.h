/*
 *  Middleware Library
 *  Copyright (c) 1998 SEGA
 *  
 *		ADX Talk Middleware Library
 *
 *  Module  : Library Header File
 *  File    : ADX_MW.H
 *  Create  : 1999-04-23
 *  Modify  : 2000-01-12
 *  Note    :
 */

#ifndef	_ADX_MW_H_
#define	_ADX_MW_H_

/***************************************************************************
 *      Include file
 ***************************************************************************/
#include	<cri_adxt.h>

/***************************************************************************
 *      MACRO CONSTANT
 ***************************************************************************/
/*	Maximum sampling frequency			*/
#define	MWD_ADXT_MAX_SFREQ		ADXT_MAX_SFREQ

/*	Play method of ADX Talk Middleware	*/
#define	MWD_ADXT_PLY_STM		ADXT_PLY_STM	/*	Stream play from CD-ROM	*/
/*	Calc work area						*/
#define	MWD_ADXT_CALC_WORK		ADXT_CALC_WORK

/*	Mode of error recovery				*/
#define	MWD_ADXT_RMODE_NOACT	ADXT_RMODE_NOACT
#define	MWD_ADXT_RMODE_STOP		ADXT_RMODE_STOP
#define	MWD_ADXT_RMODE_REPLAY	ADXT_RMODE_REPLAY

/*	ADX Encoder memory limit			*/
#define	MWD_ADXE_MEMORY_LIMIT	(18)

/***************************************************************************
 *      Enumarate Constants
 ***************************************************************************/

/***************************************************************************
 *      Process MACRO
 ***************************************************************************/
#define	MWD_ADXE_CALC_WORK(n)		(28 * n)

/***************************************************************************
 *      Data type declaration
 ***************************************************************************/
typedef struct {
	Sint32	maxch;
	void	*work;
	Sint32	worksize;
	Sint32	rcvrmode;
} MWS_PLY_CPRM_ADX;

#ifdef	__cplusplus
extern	"C"	{
#endif	/*	__cplusplus		*/

/***************************************************************************
 *		Variable Declaration
 ***************************************************************************/
extern	ECAIF	mwg_ecaif_adxenc;

/***************************************************************************
 *      Function Declaration
 ***************************************************************************/
/*	Initialization of library	*/
void	mwPlyInitAdx(void);
/*	Termination of library		*/
void	mwPlyFinishAdx(void);
/*	Creation of handle			*/
MWPLY	mwPlyCreateAdx(MWS_PLY_CPRM_ADX *cprm);

/*	Initialize ADXENC Library				*/
#define	mwRecInitAdx(mode)		mwRcaInit(mode, &mwg_ecaif_adxenc)

/*	Finish using ADXENC Library				*/
#define	mwRecFinishAdx()		mwRcaFinish(&mwg_ecaif_adxenc)

/*	Create MWREC handle for ADXENC Library	*/
#define	mwRecCreateAdx(cprm)	mwRcaCreate(cprm, &mwg_ecaif_adxenc)

#ifdef	__cplusplus
}
#endif	/*	__cplusplus		*/
#endif	/*	_ADX_MW_H_	*/
