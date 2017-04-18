/********************************************************************************************/
/* CONFIDENTIAL AND PROPRIETARY:                                                            */
/*      Copyright 2000, Sega of America.  All rights reserved.                              */
/*      This sample source code is provided for demonstration purposes only.                */
/*      Use and distribution of Sega proprietary material is governed by                    */
/*      developer licensing agreement.                                                      */
/********************************************************************************************/

/********************************************************************************************/
/* Name:     Mw_wav.c                                                                       */
/* Title:    Middleware Wave Player Example                                                 */
/* Author:   Joe Votour                                                                     */
/* Created:  February 17, 2000                                                              */
/*                                                                                          */
/* Version:  1.0                                                                            */
/* Platform: Dreamcast | Set5.24 | Shinobi | Kamui2 | Audio64                               */
/*                                                                                          */
/* Description:                                                                             */
/* This program will play a wave (WAV) file using the Middleware libraries.  This program   */
/* is an update of the mw_wav01 program, updated to use Kamui2 and Audio64 (AC or AM layer).*/
/*                                                                                          */
/* History:                                                                                 */
/*      02/17/2000 - Initial version							    */
/********************************************************************************************/

/********************************************************************************************/
/* Include (header) files								    */
/********************************************************************************************/
#include	<shinobi.h>
#include	<sg_mw.h>
#include	<string.h>

#include	"usr.h"

/********************************************************************************************/
/* Macros										    */
/********************************************************************************************/

/* Invert flag (ON/OFF) */
#define NOT_FLAG(flag)		(((flag) == OFF) ? ON : OFF)

/********************************************************************************************/
/* Global structures									    */
/********************************************************************************************/
typedef struct {
	Sint32	term_flag;			// Application terminate flag
	Sint32	disp_flag;			// Display information flag
	Sint32	pause;				// Pause flag
	char	*fname;				// File name
	MWPLY	ply;				// Player
	MWS_PLY_CPRM cprm;			// Create parameter
} AP_OBJ, *AP;

AP_OBJ ap_obj = {
	OFF,					// Execute App.
	ON,					// Display Info.
	OFF,					// Pause off
	"SAMPLE.WAV",				// File name
	NULL,					// Player
};

/********************************************************************************************/
/* Callback function for handling errors in Middleware					    */
/********************************************************************************************/
void ap_mw_err_func(void *obj, char *errmsg)
{
	AP ap=(AP)obj;
	for (;;);
}

/********************************************************************************************/
/* Initialize Middleware WAV playing software						    */
/********************************************************************************************/
void ApInitMw(AP ap)
{
	mwPlyInitWav(MWD_PLY_SVR_VSYNC);
}

/********************************************************************************************/
/* Middleware shutdown									    */
/********************************************************************************************/
void ApFinishMw(AP ap)
{
	mwPlyFinishWav();
}

/********************************************************************************************/
/* Start the Middleware WAV playing							    */
/********************************************************************************************/
void ApStart(AP ap)
{
	MWS_PLY_CPRM	*cprm = &ap->cprm;

	memset(cprm, 0, sizeof(cprm));
	cprm->size = MWD_PLY_CALC_AWORK(MWD_PLY_MIN_AWORK);
	cprm->buf = syMalloc(cprm->size);
	cprm->sample = MWD_PLY_SAMPLE_NUM;
	ap->ply = mwPlyCreateWav(cprm);
	if (ap->ply == NULL)
		for (;;)
			;
	mwPlyStartFname(ap->ply, ap->fname);
}

/********************************************************************************************/
/* Stop playing the WAV file								    */
/********************************************************************************************/
void ApStop(AP ap)
{
	mwPlyStop(ap->ply);
	mwPlyDestroy(ap->ply);
	ap->ply = NULL;
	syFree(ap->cprm.buf);
	ap->cprm.buf = NULL;
}

/********************************************************************************************/
/* Display information (filename and time played)					    */
/********************************************************************************************/
void ap_disp_info(AP ap)
{
	Sint32	time, tunit, hh, mm, ss, ff;

	mwPlyGetTime(ap->ply, &time, &tunit);
	UsrSfcnt2time(tunit, time, &hh, &mm, &ss, &ff);
	UsrPrintf(0, 0, "File: %s  Time:%02d:%02d:%02d.%02d", ap->fname, hh, mm, ss, ff);

}

/********************************************************************************************/
/* Handle pausing of stream and end of stream conditions				    */
/********************************************************************************************/
Sint32 ApExec(AP ap)
{
	const PDS_PERIPHERAL	*per;
	MWPLY			ply=ap->ply;
	MWE_PLY_STAT		stat;

	per = pdGetPeripheral(PDD_PORT_A0);
	if (per->press & PDD_DGT_ST) {
		ap->pause = NOT_FLAG(ap->pause);
		mwPlyPause(ply, ap->pause);				
	}
	/*	Release pause status	*/
	if (per->press & PDD_DGT_TA)
		ap->disp_flag = NOT_FLAG(ap->disp_flag);
	if (per->press & PDD_DGT_TB)
		return FALSE;

	/*	Checking status	*/
	stat = mwPlyGetStat(ply);
	if ((stat == MWE_PLY_STAT_PLAYEND) || (stat == MWE_PLY_STAT_ERROR))
		return FALSE;
	if ( ap->disp_flag == ON )
		ap_disp_info(ap);

	return TRUE;
}

/********************************************************************************************/
/* Check for errors in GD filesystem (i.e. door open)					    */
/********************************************************************************************/
void ApGdErrFunc(void *obj, Sint32 errcode)
{
	AP ap=(AP)obj;
	if (errcode == GDD_ERR_TRAYOPEND || errcode == GDD_ERR_UNITATTENT)
		ap->term_flag = ON;
}

/********************************************************************************************/
/* V-Sync interrupt callback handler							    */
/********************************************************************************************/
void ApVsyncFunc(void)
{
	UsrCheckDoorOpen();
}

/********************************************************************************************/
/* Main function									    */
/********************************************************************************************/
void main(void)
{
	AP ap=&ap_obj;
	void *vtxbuf;
	Sint32 mode, frame, count, latency;
	Bool ret;

#ifdef __GNUC__
	shinobi_workaround();
#endif

	vtxbuf = UsrInitVideo(&mode, &frame, &count, &latency);	// Init the display

	gdFsEntryErrFuncAll((void *)ApGdErrFunc, ap);		// Setup the GDFS callback
	UsrInitSound();						// Init the sound
	UsrSetVsyncFunc((void (*)(void))ApVsyncFunc);		// Register V-Sync interrupt function
	ApInitMw(ap);						// Initialize Middleware

	while ( ap->term_flag == OFF ) {
		ApStart(ap);					// Start playing the stream
		while (1) {
			UsrBeginDraw();
			ret = ApExec(ap);			// Execute the main loop
			UsrEndDraw();
			if ( ret == FALSE || ap->term_flag == ON )
				break;
			UsrWaitVBlank();
		}
		ApStop(ap);					// Stop the stream
	}
	ApFinishMw(ap);						// Terminate Middleware
	UsrFinishSound();					// Shutdown sound system
	syBtExit();						// Exit to BootROM
}

/* End of file */