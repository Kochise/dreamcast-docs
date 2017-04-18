/*
 *  Middleware Library
 *  Copyright (c) 1998 SEGA
 *  
 *		Middleware Play
 *
 *  Module  : Library Header File
 *  File    : SG_MWPLY.H
 *  Create  : 1998-07-25
 *  Modify  : 1999-05-20
 *  Note    :
 */

#ifndef _SG_MWPLY_H_
#define _SG_MWPLY_H_

/*	Version No.	*/
#define		MWD_PLY_VER		"2.05"

/***************************************************************************
 *      Include file
 ***************************************************************************/

#include <sg_xpt.h>
#include <sj.h>

/***************************************************************************
 *      MACRO CONSTANT
 ***************************************************************************/

/*	Library ID					*/
#define	MWD_PLY_LID	{ \
	0xa99e5b80, 0x09f9, 0x11d2, \
	0xa5, 0xa0, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00 \
}

/* 
 * VBLANK割り込みによる呼び出し関数のプライオリティ
 * 注意：ミドルウェアライブラリは以下の値に統一する
 * Priority of function called when V-sync interrpt
 * Notice: We select the following values uniformly in Middleware.
 */
#define	MWD_PLY_PRI_VBLNK		(0x70)

/*	Max number of MWPLY handle	*/
#define	MWD_PLY_MAX_OBJ		(32)

/*	Error Code					*/
#define	MWD_PLY_ERR_OK			(0)
#define	MWD_PLY_ERR_NG			(-1)
#define	MWD_PLY_ERR_FATAL		(-2)
#define	MWD_PLY_ERR_INTERNAL	(-3)
#define	MWD_PLY_ERR_PRM			(-4)

#define	MWD_PLY_ERR_NOHN		(-11)
#define	MWD_PLY_ERR_NULHN		(-12)

/*	GSC Error  					*/
#define	MWD_PLY_ERR_GSC_INIT	(-101)
#define	MWD_PLY_ERR_GSC_OPFN	(-102)
#define	MWD_PLY_ERR_GSC_START	(-103)
#define	MWD_PLY_ERR_GSC_OPENAGAIN	(-104)

/*	SJ Error					*/
#define	MWD_PLY_ERR_SJ_FATAL	(-201)

/*	Channel Value				*/
#define MWD_CH_L				(0)
#define MWD_CH_R				(1)

/*	Panpot Value				*/
#define	MWD_PAN_LEFT			(-15)
#define	MWD_PAN_CENTER			(0)
#define	MWD_PAN_RIGHT			(15)
#define	MWD_PAN_AUTO			(-128)

/***************************************************************************
 *      Enumarate Constants
 ***************************************************************************/

/*	Status of MWPLY handles		*/
typedef	enum _mwe_ply_stat {
	MWE_PLY_STAT_STOP		= (0),		/*	stoped						*/
	MWE_PLY_STAT_PREP		= (1),		/*	preparing					*/
	MWE_PLY_STAT_PLAYING	= (2),		/*	playing						*/
	MWE_PLY_STAT_PLAYEND	= (3),		/*	end of playing				*/
	MWE_PLY_STAT_ERROR		= (4)		/*	error was occured			*/
} MWE_PLY_STAT;

/***************************************************************************
 *      Process MACRO
 ***************************************************************************/

/*	Convert mwGetTime()'s return-value to second	*/
#define	MWD_PLY_TIME2SEC(ncount, tscale)	((ncount) / (tscale))

/*	Convert mwGetTime()'s return-value to milli-second	*/
#define	MWD_PLY_TIME2MSEC(ncount, tscale)	((1000 * (ncount)) / (tscale))

/***************************************************************************
 *      Data type declaration
 ***************************************************************************/

/*	MWPLY handle				*/
#ifndef MWPLY_DEFINED
#define MWPLY_DEFINED

/*	Virtual function table		*/
typedef struct {
	struct _mwply_if *vtbl;
} MW_PLY_OBJ;
typedef MW_PLY_OBJ *MWPLY;
#endif

/*	Callback function of error	*/
typedef void (*MW_PLY_ERRFN)(void *obj, char *ecode);

/*	MWPLY Interface function  	*/
typedef struct _mwply_if {
	void (*QueryInterface)();		/*	for COM compatibility	*/
	void (*AddRef)();				/*	for COM compatibility	*/
	void (*Release)();				/*	for COM compatibility	*/
	/*== Functions of MWPLY	====================================*/ 
	/*	V-sync function 										*/
	/*	This function is called by user while v-sync interrupt.	*/
	void (*VsyncHndl)(MWPLY ply);
	/*	execute decoding one frame								*/
	/*	This function is called by user from main-loop.			*/ 
	void (*ExecSvrHndl)(MWPLY ply);
	/*	destroy MWPLY handle									*/
	void (*Destroy)(MWPLY ply);
	/*	start playing by file name 								*/
	void (*StartFname)(MWPLY ply, Sint8 *fname);
	/*	stop playing  											*/
	void (*Stop)(MWPLY ply);
	/*	get status of MWPLY handle								*/
	MWE_PLY_STAT (*GetStat)(MWPLY ply);
	/*	get playing time										*/
	/*	if playing movie is 30 fps, *tscale is 30 and 			*/
	/*		*ncount is total number of displayed frames			*/ 
	void (*GetTime)(MWPLY ply, Sint32 *ncount, Sint32 *tscale);
	/*	Set pause switch.  sw=0(Continue), 1(Pause)				*/
	void (*Pause)(MWPLY ply, Sint32 sw);
	/*	Set Output Volume (vol= 0 to -960)						*/
	void (*SetOutVol)(MWPLY ply, Sint32 vol);
	/*	Get Output Volume (return value= 0 to -960)				*/
	Sint32 (*GetOutVol)(MWPLY ply);
	/*	Set output panpot chno=0(Mono/Left),1(Right)			*/
	/*	pan = +15(Right),0(Center),-15(Left),-128(Auto)			*/
	void (*SetOutPan)(MWPLY ply, Sint32 chno, Sint32 pan);
	/*	Get output panpot chno=0(Mono/Left),1(Right)			*/
	Sint32 (*GetOutPan)(MWPLY ply, Sint32 chno);
	/*	start playing by stream joint							*/
	void (*StartSj)(MWPLY ply, SJ sji);
	/*	start playing by memory									*/
	void (*StartMem)(MWPLY ply, void *addr, Sint32 len);
} MWD_IF;

/***************************************************************************
 *		Variable Declaration
 ***************************************************************************/

/***************************************************************************
 *      Function Declaration
 ***************************************************************************/

/*	V-sync function 										*/
/*	This function is called by user while v-sync interrupt.	*/
#define mwPlyVsyncHndl(ply)			(*(ply)->vtbl->VsyncHndl)((ply))

/*	Execute decoding one frame								*/
/*	This function is called by user from main-loop.			*/ 
#define mwPlyExecSvrHndl(ply)		(*(ply)->vtbl->ExecSvrHndl)((ply))

/*	Destroy MWPLY handle									*/
#define mwPlyDestroy(ply)			(*(ply)->vtbl->Destroy)((ply))

/*	Start playing by file name 								*/
#define mwPlyStartFname(ply, fname)	(*(ply)->vtbl->StartFname)((ply), (fname))

/*	Stop playing  											*/
#define mwPlyStop(ply)				(*(ply)->vtbl->Stop)((ply))

/*	Get status of MWPLY handle								*/
#define mwPlyGetStat(ply)			(*(ply)->vtbl->GetStat)((ply))

/*	Get playing time										*/
/*	If playing movie is 30 fps, *tscale is 30 and 			*/
/*		*ncount is total number of displayed frames			*/ 
#define mwPlyGetTime(ply, ncount, tscale)	\
							(*(ply)->vtbl->GetTime)((ply), (ncount), (tscale))

/*	Set pause switch.  sw=0(Continue), 1(Pause)				*/
#define	mwPlyPause(ply, sw)			(*(ply)->vtbl->Pause)((ply), (sw))

/*	Set Output Volume (vol= 0 to -960)						*/
#define mwPlySetOutVol(ply, vol)	(*(ply)->vtbl->SetOutVol)((ply), (vol))

/*	Get Output Volume (return value= 0 to -960)				*/
#define mwPlyGetOutVol(ply)			(*(ply)->vtbl->GetOutVol)((ply))

/*	Set output panpot c=0(Mono/Left),1(Right)				*/
/*	p = +15(Right),0(Center),-15(Left),-128(Auto)			*/
#define mwPlySetOutPan(ply, c, p)	(*(ply)->vtbl->SetOutPan)((ply), (c), (p))

/*	Get output panpot c=0(Mono/Left),1(Right)				*/
#define mwPlyGetOutPan(ply, c)     (*(ply)->vtbl->GetOutPan)((ply), (c))

/*	Start playing by stream joint							*/
#define mwPlyStartSj(ply, sji)     (*(ply)->vtbl->StartSj)((ply), (sji))

/*	Start playing by memory									*/
#define	mwPlyStartMem(ply, addr, len)		\
								   (*(ply)->vtbl->StartMem)((ply), (addr), (len))

#ifdef __cplusplus
extern "C" {
#endif

/*	Frame start					*/
void mwPlyStartFrame(void);
/*	Register error function		*/
void mwPlyEntryErrFunc(MW_PLY_ERRFN errfn, void *obj);
/*	Execute server function		*/
void mwPlyExecServer(void);

/*	Execute Idle Server		*/
void mwExecIdleSvr(void);

/*	Return to main fiber	*/
void mwReturnToMain(void);

/*	Return to main fiber from interrupt	*/
void mwReturnToMainFromIntr(void);

/*	Config using WaitVsyncCallback of Kamui/Kamui2 */
void mwMngConfigUsingKmWaitVsyncCb(Sint32 flag);

#ifdef __cplusplus
}
#endif

#endif	/* _SG_MWPLY_H_ */
