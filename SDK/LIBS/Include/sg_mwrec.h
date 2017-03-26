/*
 *  Middleware Library
 *  Copyright (c) 1998 SEGA
 *  
 *		Middleware Record
 *
 *  Module  : Library Header File
 *  File    : SG_MWREC.H
 *  Create  : 1999-06-01
 *  Modify  : 1999-10-06
 *  Note    :
 */

#ifndef	_SG_MWREC_H_
#define	_SG_MWREC_H_

/*	Version No.	*/
#define		MWD_REC_VER		"1.01"

/***************************************************************************
 *      Include file
 ***************************************************************************/
#include <sg_xpt.h>
#include <sj.h>

/***************************************************************************
 *      MACRO CONSTANT
 ***************************************************************************/
/*	Max number of MWREC handle	*/
#define		MWD_REC_MAX_OBJ			(32)

/*	Error Code					*/
#define		MWD_REC_ERR_OK			( 0)
#define		MWD_REC_ERR_NG			(-1)
#define		MWD_REC_ERR_FATAL		(-2)
#define		MWD_REC_ERR_INTERNAL	(-3)
#define		MWD_REC_ERR_PRM			(-4)

/***************************************************************************
 *      Enumarate Constants
 ***************************************************************************/
/*	Status of MWREC handles		*/
typedef	enum	_mwe_rec_stat	{
	MWE_REC_STAT_STOP = (0),				/*	Stop						*/
	MWE_REC_STAT_PREP,						/*	Preparing					*/
	MWE_REC_STAT_RECORD,					/*	Recording					*/
	MWE_REC_STAT_RECEND,					/*	End of recording			*/
	MWE_REC_STAT_ERROR						/*	Error was occured			*/
}	MWE_REC_STAT;

/***************************************************************************
 *      Process MACRO
 ***************************************************************************/

/***************************************************************************
 *      Data type declaration
 ***************************************************************************/
/*	MWREC handle				*/
#ifndef	MWREC_DEFINED
#define	MWREC_DEFINED

/*	Virtual function table		*/
typedef	struct	{
	struct	_mwrec_if	*vtbl;
}	MW_REC_OBJ, *MWREC;
#endif

/*	Callback function of error	*/
typedef	void (*MW_REC_ERRFN)(void *obj, char *ecode);

/*	MWREC Interface function	*/
typedef	struct	_mwrec_if	{
	void (*QueryInterface)();				/*	for COM compatibility		*/
	void (*AddRef)();						/*	for COM compatibility		*/
	void (*Release)();						/*	for COM compatibility		*/
	/*== Function of MWREC =================================================*/
	/*	V-sync function														*/
	/*	This function is called by user while v-sync interrupt.				*/
	void (*VsyncHndl)(MWREC rec);
	/*	execute encoding on frame											*/
	/*	This function is called by user from mail-loop.						*/
	void (*ExecSvrHndl)(MWREC rec);
	/*	destroy MWREC handle												*/
	void (*Destroy)(MWREC rec);
	/*	start recording by file name										*/
	void (*StartFname)(MWREC rec, Sint8 *fname);
	/*	start recording by stream joint										*/
	void (*StartSj)(MWREC rec, SJ sj);
	/*	start recording by memory											*/
	void (*StartMem)(MWREC rec, void *addr, Sint32 len);
	/*	stop recording														*/
	void (*Stop)(MWREC rec);
	/*	get status of MWREC handle											*/
	MWE_REC_STAT (*GetStat)(MWREC rec);
	/*	Set pause switch.  sw=0(Continue), 1(Pause)							*/
	void (*Pause)(MWREC rec, Sint32 sw);
}	MWS_REC_IF;

/***************************************************************************
 *		Variable Declaration
 ***************************************************************************/

/***************************************************************************
 *      Function Declaration
 ***************************************************************************/
/*	V-sync function											*/
/*	This function is called by user while v-sync interrupt.	*/
#define	mwRecVsyncHndl(rec)			(*(rec)->vtbl->VsyncHndl)((rec))

/*	Execute encoding one frame								*/
/*	This function is called by user mail-loop.				*/
#define	mwRecExecSvrHndl(rec)		(*(rec)->vtbl->ExecSvrHndl)((rec))

/*	Destroy MWREC handle									*/
#define	mwRecDestroy(rec)			(*(rec)->vtbl->Destroy)((rec))

/*	Start recording by file name							*/
#define	mwRecStartFname(rec, fname)	(*(rec)->vtbl->StartFname)((rec), (fname))

/*	Start recording by stream joint							*/
#define	mwRecStartSj(rec, sj)		(*(rec)->vtbl->StartSj)((rec), (sj))

/*	Start recording by memory								*/
#define	mwRecStartMem(rec, addr, len)	\
									(*(rec)->vtbl->StartMem)((rec), (addr), (len))

/*	Stop recording											*/
#define	mwRecStop(rec)				(*(rec)->vtbl->Stop)((rec))

/*	Get status of MWREC handle								*/
#define	mwRecGetStat(rec)			(*(rec)->vtbl->GetStat)((rec))

/*	Set pause switch.  sw=0(Continue), 1(Pause)				*/
#define	mwRecPause(rec, sw)			(*(rec)->vtbl->Pause)((rec), (sw))

/*	Register error function									*/
void	mwRecEntryErrFunc(MW_REC_ERRFN errfn, void *obj);

/*	Execute server function									*/
void	mwRecExecServer(void);

#endif	/*	_SG_MWREC_H_	*/
