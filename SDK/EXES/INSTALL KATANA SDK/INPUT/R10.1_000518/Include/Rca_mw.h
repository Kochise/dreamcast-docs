/*
 *  Middleware Library
 *  Copyright (c) 1998 SEGA
 *  
 *		Audio Recorder
 *
 *  Module  : Library Header File
 *  File    : RCA_MW.H
 *  Create  : 1999-06-01
 *  Modify  : 1999-09-21
 *  Note    :
 */

#ifndef	_RCA_MW_H_
#define	_RCA_MW_H_

/***************************************************************************
 *      Include file
 ***************************************************************************/

/***************************************************************************
 *      MACRO CONSTANT
 ***************************************************************************/

#define	MWD_REC_SVR_VSYNC		(0)
#define	MWD_REC_SVR_MAIN		(1)

/*	Minimum size of buffer(sector)		*/
#define	MWD_REC_MIN_AWORK		(48)

/*	Default extra size of buffer		*/
#define	MWD_REC_EXTRA_SIZE		(0)

/*	Device ID							*/
#define	MWD_REC_DEV_A1			(1)
#define	MWD_REC_DEV_A2			(2)
#define	MWD_REC_DEV_B1			(7)
#define	MWD_REC_DEV_B2			(8)
#define	MWD_REC_DEV_C1			(13)
#define	MWD_REC_DEV_C2			(14)
#define	MWD_REC_DEV_D1			(19)
#define	MWD_REC_DEV_D2			(20)

/*	Sampling Frequency					*/
#define	MWD_REC_SFREQ_11KHZ		(0)			/*	11025 Hz sampling			*/
#define	MWD_REC_SFREQ_8KHZ		(1)			/*	 8000 Hz sampling			*/

/*	Bits per Sampling					*/
#define	MWD_REC_BPS_16BIT		(0)			/*	16bit linear sampling		*/
#define	MWD_REC_BPS_8BIT		(1)			/*	8bit u-law codec sampling	*/

/*	Amp Gain							*/
#define	MWD_REC_GAIN_MAX		(16)		/*	Maximum Value				*/
#define	MWD_REC_GAIN_MIN		(-15)		/*	Minimum Value				*/


/***************************************************************************
 *      Enumarate Constants
 ***************************************************************************/

/***************************************************************************
 *      Process MACRO
 ***************************************************************************/
/*	Calculation of Buffer size(byte)	*/
#define	MWD_REC_CALC_AWORK(n)	((2048*(n))+32)

/***************************************************************************
 *      Data type declaration
 ***************************************************************************/

typedef struct {
	Uint8			*buf;
	Sint32			size;
	Sint32			maxch;
	Sint32			*libwork;
	Sint32			extsize[2];
	Sint32			devno;
	Sint32			sfreq;
	Sint32			bps;
	Sint32			gain;
	Sint32			limit;
} MWS_REC_CPRM;

typedef	void	*ECAIF;

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
void	mwRcaInit(Sint32 mode, ECAIF iftbl);
/*	Termination of library		*/
void	mwRcaFinish(ECAIF iftbl);
/*	Creation of handle			*/
MWREC	mwRcaCreate(MWS_REC_CPRM *cprm, ECAIF iftbl);

#ifdef	__cplusplus
}
#endif	/*	__cplusplus		*/
#endif	/*	_RCA_MW_H_		*/
