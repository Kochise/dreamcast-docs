/*
 *		Users Functions Header
 */

/*	Initialize Video library and set display mode	*/
void *UsrInitVideo(Sint32 *mode, Sint32 *frame, Sint32 *count,Sint32 *latency);

/*	Finalize Video library and SHINOBI	*/
void UsrFinishVideo(void);

/*	Wait V-sync interrupt	*/
void UsrWaitVsync(void);

/*	Set V-sync interrupt callback function	*/
void UsrSetVsyncFunc(void (*func)(void));

/*	Print string for debug	*/
long UsrPrintf(long lx, long ly, char *fmt,...);

/***
*			Audio Functions
***/

/*	Initialize sound library and load sound driver	*/
void UsrInitSound(void);

/*	Finalize sound system	*/
void UsrFinishSound(void);

/***
*			Utility functions
***/

/*	Check Door Status	*/
void UsrCheckDoorOpen(void);

/*	Load data to memory	*/
void *UsrLoadFile(char *fname, long *len);

/*	Convert from sampling frequency and counter to time(hour,min,sec,frame)	*/
void UsrSfcnt2time(long sf, long ncnt, long *hh, long *mm, long *ss, long *ff);

