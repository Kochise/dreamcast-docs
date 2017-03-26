/*
 *  Middleware Library
 *  Copyright (c) 1998 SEGA
 *  
 *		Audio Player
 *
 *  Module  : Library Header File
 *  File    : PLA_MW.H
 *  Create  : 1999-01-20
 *  Modify  : 1999-09-21
 *  Note    :
 */

#ifndef	_PLA_MW_H_
#define	_PLA_MW_H_

/***************************************************************************
 *      Include file
 ***************************************************************************/

/***************************************************************************
 *      MACRO CONSTANT
 ***************************************************************************/

/*	Decoder Error						*/
#define	MWD_PLY_ERR_WAV_INIT	(-301)			/*	Initialize Error		*/
#define	MWD_PLY_ERR_WAV_NOTYPE	(-302)			/*							*/
#define	MWD_PLY_ERR_WAV_ERRFN	(-303)			/*							*/
#define	MWD_PLY_ERR_WAV_FINISH	(-304)			/*	Finish Error			*/
#define	MWD_PLY_ERR_WAV_CREATE	(-305)			/*	Handle Create Error		*/
#define	MWD_PLY_ERR_WAV_DSTRY	(-306)			/*	Handle Destroy Error	*/
#define	MWD_PLY_ERR_WAV_START	(-307)			/*	Decode Start Error		*/
#define	MWD_PLY_ERR_WAV_STOP	(-308)			/*	Decode Stop Error		*/

/*	Audio Renderer Error				*/
#define	MWD_PLY_ERR_RNA_INIT	(-401)
#define	MWD_PLY_ERR_RNA_FINISH	(-402)
#define	MWD_PLY_ERR_RNA_CREATE	(-403)
#define	MWD_PLY_ERR_RNA_DSTRY	(-404)
#define	MWD_PLY_ERR_RNA_START	(-405)
#define	MWD_PLY_ERR_RNA_STOP	(-406)
#define	MWD_PLY_ERR_RNA_PRM		(-407)

/*	Maximum number of GSC handle		*/
#define	MWD_GSCHN_MAX			(1)

#define	MWD_PLY_SVR_VSYNC		(0)
#define	MWD_PLY_SVR_MAIN		(1)

/*	The next symbol is eliminated in the future.	*/
#define	MWD_PLY_AT_EXEC_VSYNC	MWD_PLY_SVR_VSYNC
#define	MWD_PLY_MN_EXEC_VSYNC	MWD_PLY_SVR_MAIN

/*	Calculation of Buffer size(byte)	*/
#define	MWD_PLY_CALC_AWORK(n)	((2048*(n))+32)
#define	MWD_PLY_ALLOC_SJBUF(n)	MWD_PLY_CALC_AWORK(n)

/*	Minimum size of buffer(sector)		*/
#define	MWD_PLY_MIN_AWORK		(48)
#define	MWD_PLY_ALLOC_LIMIT		MWD_PLY_MIN_AWORK

/*	Default extra size of buffer		*/
#define	MWD_PLY_EXTRA_SIZE		(0)

/*	Default Start Sample Num			*/
#define	MWD_PLY_SAMPLE_NUM		(8192)

/*	Default memory limit				*/
#define	MWD_PLY_MEMORY_LIMIT	(0)

/***************************************************************************
 *      Enumarate Constants
 ***************************************************************************/

/***************************************************************************
 *      Process MACRO
 ***************************************************************************/

/***************************************************************************
 *      Data type declaration
 ***************************************************************************/

typedef struct {
	Uint8	*buf;
	Sint32	size;
	Sint32	*libwork;
	Sint32	extsize[2];
	Sint32	sample;
	Sint32	limit;
} MWS_PLY_CPRM;

typedef	void	*DCAIF;

#ifdef	__cplusplus
extern	"C"	{
#endif	/*	__cplusplus		*/

/***************************************************************************
 *		Variable Declaration
 ***************************************************************************/

/***************************************************************************
 *      Function Declaration
 ***************************************************************************/

/*	Initialization of library	*/
void	mwPlaInit(Sint32 mode, DCAIF iftbl);
/*	Termination of library		*/
void	mwPlaFinish(DCAIF iftbl);
/*	Creation of handle			*/
MWPLY	mwPlaCreate(MWS_PLY_CPRM *cprm, DCAIF iftbl);

#ifdef	__cplusplus
}
#endif	/*	__cplusplus		*/
#endif	/*	_PLA_MW_H_	*/
