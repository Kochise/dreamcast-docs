/*
 *  Middleware Library
 *  Copyright (c) 1998 SEGA
 *  
 *      Middleware Library
 *
 *  Module  : Library Header File
 *  File    : SG_MW.H
 *  Create  : 1998-04-21
 *  Modify  : 1999-10-12
 *  Note    :
 */

#ifndef _SG_MW_H_
#define _SG_MW_H_

/*	Version No.	*/
#define	MWD_VER		"2.30"

/***************************************************************************
 *      Include file
 ***************************************************************************/

/*	Declearation for Stream Joint							*/
#include	"SJ.H"
/*	Middleware Player										*/
#include	"SG_MWPLY.H"
/*	Declearation for Audio Decoder							*/
#include	"PLA_MW.H"
/*	Middleware Recoder										*/
#include	"SG_MWREC.H"
/*	Declearation for Audio Encoder							*/
#include	"RCA_MW.H"
/*	Declearation for MPEG Sofdec							*/
#include	"SFDFX_MW.H"
/*	Declearation for TrueMotion								*/
#include	"TM_MW.H"
/*	Declearation for WAVE Player							*/
#include	"WAV_MW.H"
/*	Declearation for MPEG/Audio								*/
#include	"MPA_MW.H"
/*	Declearation for ADX Player (Middleware Intreface)		*/
#include	"ADX_MW.H"
/*	Declearation for ADX Player								*/
#include	"CRI_ADXT.H"
/*	Declearation for ADX File System						*/
#include	"CRI_ADXF.H"
/*	Declearation for ADX File System						*/
#include	"CRI_LSC.H"
/*	Declearation for ADX File System						*/
#include	"CRI_SAN.H"

/***************************************************************************
 *      Middleware Common Function  (Middleware Manager's Function)
 ***************************************************************************/

/*	Callback function of error	*/
typedef void (*MW_ERRFN)(void *obj, char *emsg);

/*	ミドルウェアメインサーバー関数				*/
/*	Server Function called from main routine	*/
void mwExecMainServer(void);

/*	エラー処理関数の登録						*/
/*	Entry error callback  function 				*/
void mwEntryErrFunc(MW_ERRFN errfn, void *obj);

/*	ミドルウェアライブラリの初期化				*/
/*	Initilize Middleware System					*/
void mwInitSystem(void);

/*	ミドルウェアライブラリの終了				*/
/*	Exit Middleware System						*/
void mwExitSystem(void);

/*	Audio64のためのサウンドリソースの設定		*/
/*	Set up the sound resouces for Audio64		*/
void mwSetupAudio64(void *sound_ram_ptr, Uint32 sound_ram_size,
											Uint32 port[], Uint32 nport);

#endif     /*  _SG_MW2_H_	*/
