/*
 *  Middleware Library
 *  Copyright (c) 1998 SEGA
 *  
 *		Wave Player
 *
 *  Module  : Library Header File
 *  File    : WAV_MW.H
 *  Create  : 1998-09-01
 *  Modify  : 1999-06-09
 *  Note    :
 */

#ifndef	_WAV_MW_H_
#define	_WAV_MW_H_

#ifdef	__cplusplus
extern	"C"	{
#endif	/*	__cplusplus		*/

/*	Version No.		*/
#define		MWD_WAV_VER		"1.13"

/***************************************************************************
 *		Variable Declaration
 ***************************************************************************/

extern	DCAIF	mwg_dcaif_wav;

/***************************************************************************
 *      Function Declaration
 ***************************************************************************/

/*	Initialize Wave-Decode Library		*/
#define	mwPlyInitWav(mode)			mwPlaInit(mode, &mwg_dcaif_wav)

/*	Finish using Wave-Decode Library	*/
#define	mwPlyFinishWav()			mwPlaFinish(&mwg_dcaif_wav)

/*	Create MWPLY handle for Wave-Deocde	*/
#define	mwPlyCreateWav(cprm)		mwPlaCreate(cprm, &mwg_dcaif_wav)

#ifdef	__cplusplus
}
#endif	/*	__cplusplus		*/
#endif	/*	_WAV_MW_H_	*/
