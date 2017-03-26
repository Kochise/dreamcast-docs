/*
 *  Middleware Library
 *  Copyright (c) 1998 SEGA
 *  
 *		MPEG/Audio
 *
 *  Module  : Library Header File
 *  File    : MPA_MW.H
 *  Create  : 1999-03-10
 *  Modify  : 1999-06-09
 *  Note    :
 */

#ifndef	_MPA_MW_H_
#define	_MPA_MW_H_

/***************************************************************************
 *      Process MACRO
 ***************************************************************************/

#define	MWD_MPA_CALC_WORK(n)		((6952) * n)

#define	MWD_MPA_EXTRA_SIZE			(1152 * 2)

#ifdef	__cplusplus
extern	"C"	{
#endif	/*	__cplusplus		*/

/***************************************************************************
 *		Variable Declaration
 ***************************************************************************/

extern	DCAIF	mwg_dcaif_mpa;

/***************************************************************************
 *      Function Declaration
 ***************************************************************************/

/*	Initialize MPEG/Audio Library			*/
#define	mwPlyInitMpa(mode)			mwPlaInit(mode, &mwg_dcaif_mpa)

/*	Finish using MPEG/Audio Library			*/
#define	mwPlyFinishMpa()			mwPlaFinish(&mwg_dcaif_mpa)

/*	Create MWPLY handle for MPEG/Audio		*/
#define	mwPlyCreateMpa(cprm)		mwPlaCreate(cprm, &mwg_dcaif_mpa)

#ifdef	__cplusplus
}
#endif	/*	__cplusplus		*/
#endif	/*	_MPA_MW_H_	*/
