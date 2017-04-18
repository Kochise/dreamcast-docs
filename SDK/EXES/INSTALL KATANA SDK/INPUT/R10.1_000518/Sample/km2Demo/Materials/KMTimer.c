/*****************************************************************************
  Name : KMTimer.c
  Date : August 1998
  Platform : ANSI compatible
 
  * Description : 
  This file is part of the KAMUI TOOLS library (KMTools.lib) used
  with the SDK demos for PowerVR series 2.

  Set of SH4-Clock functions.
 
******************************************************************************/

#include "KMTools.h"

#define TOCR	0xFFD80000
#define TSTR	0xFFD80004
#define TCOR0	0xFFD80008
#define TCNT0	0xFFD8000C
#define TCR0	0xFFD80010
#define TCOR1	0xFFD80014
#define TCNT1	0xFFD80018
#define TCR1	0xFFD8001C
#define IPRA	0xFFD00004
#define	SEC_DEF	(25000000/2)		/* SH4-Clock 200MHz */


typedef struct _LARGE_INTEGER { /* li */
	unsigned long LowPart;
	long  HighPart;
} LARGE_INTEGER;


/* Private functions */
void			InitTimerSH4				(void);
int				QueryPerformanceFrequency	(LARGE_INTEGER *lpli);
int				QueryPerformanceCounter		(LARGE_INTEGER *lpli);
unsigned long	timeGetTime					(void);

/*----------------------------------------------------------------------*/
/*  Function Name   :                                                   */
/*  Inputs          :                                                   */  
/*  Outputs         :                                                   */
/*  Returns         :                                                   */
/*  Globals Used    :                                                   */
/*  Description     :                                                   */
/*----------------------------------------------------------------------*/
void InitTimerSH4(void)
{
	static int InitDone = 0;

	if (!InitDone) {
		InitDone = 1;
		*(unsigned char *)TSTR	= 0x00;			/* Timer stop */
		*(unsigned char *)TOCR	= 0x01;
		*(unsigned short *)TCR0 = 0x0000;		/* UNIE */
		*(unsigned long *)TCOR0 = 12500000/2;
		*(unsigned long *)TCNT0 = 12500000/2;
		*(unsigned short *)TCR1 = 0x0000;
		*(unsigned long *)TCOR1 = 0xffffffff;
		*(unsigned long *)TCNT1 = 0xffffffff;
		*(unsigned char *)TSTR	= 0x03;			/* Timer start */
	}
}

/*----------------------------------------------------------------------*/
/*  Function Name   :                                                   */
/*  Inputs          :                                                   */  
/*  Outputs         :                                                   */
/*  Returns         :                                                   */
/*  Globals Used    :                                                   */
/*  Description     :                                                   */
/*----------------------------------------------------------------------*/
int QueryPerformanceFrequency(LARGE_INTEGER *lpli)
{
	InitTimerSH4();
	lpli->LowPart = SEC_DEF;
	return 1;
}
/*----------------------------------------------------------------------*/
/*  Function Name   :                                                   */
/*  Inputs          :                                                   */  
/*  Outputs         :                                                   */
/*  Returns         :                                                   */
/*  Globals Used    :                                                   */
/*  Description     :                                                   */
/*----------------------------------------------------------------------*/
int QueryPerformanceCounter(LARGE_INTEGER *lpli)
{
	lpli->LowPart = 0xFFFFFFFFUL - (*(unsigned long*)(TCNT1));
	return 1;
}
/*----------------------------------------------------------------------*/
/*  Function Name   :                                                   */
/*  Inputs          :                                                   */  
/*  Outputs         :                                                   */
/*  Returns         :                                                   */
/*  Globals Used    :                                                   */
/*  Description     :                                                   */
/*----------------------------------------------------------------------*/
unsigned long timeGetTime(void)
{
	static unsigned long	t = 0;

	return t++;
}
/*----------------------------------------------------------------------*/
/*  Function Name   :                                                   */
/*  Inputs          :                                                   */  
/*  Outputs         :                                                   */
/*  Returns         :                                                   */
/*  Globals Used    :                                                   */
/*  Description     :                                                   */
/*----------------------------------------------------------------------*/
double KMTimerGetFPS (void)
{

static	int			frame = 0;				
static	int			frame_2 = 0;			
static	int			pcount_f = 0;				
static	double		nFPS;				
static	double		aFPS;					
static	double		MxFPS;					
static	double		MnFPS;
static  long		freqi;			
static	long 		Time3i;				
static	double		OldTime3;			
static	double		Time3;					
static	double		freq;				
static	double		nowTime;			
static	double		maxTime = 0.00001;				
static	double		minTime = 99999;			
static	double		totalTime = 0;			
static	double		aveTime;		

	if (frame==0)
	{
		pcount_f = QueryPerformanceFrequency((LARGE_INTEGER*)&freqi);
		if(pcount_f) 
		{	
			QueryPerformanceCounter((LARGE_INTEGER*)&Time3i);	
			freq = 1000.0f / (double)freqi;						
			OldTime3 = Time3 = (double)Time3i * freq;			
		}
		else Time3 = (double)timeGetTime();						
	}

	if(pcount_f) {
		QueryPerformanceCounter((LARGE_INTEGER*)&Time3i);	
		OldTime3 = Time3; Time3 = (double)Time3i * freq;
	}
	else {
		OldTime3 = Time3; Time3 = (double)timeGetTime();	
	}

	nowTime = Time3 - OldTime3;					
	if(nowTime > maxTime) maxTime = nowTime;	
	if(nowTime < minTime) minTime = nowTime;	

	totalTime += nowTime;								
	aveTime = totalTime / ((double)frame + 1.0f);	

	nFPS  = 1000.0f / (double)nowTime;
	aFPS  = 1000.0f / (double)aveTime;
	MxFPS = 1000.0f / (double)minTime;
	MnFPS = 1000.0f / (double)maxTime;

	frame++;
	if(frame > 1000000) {	
		frame = 0;
		totalTime = 0;
		frame_2++;
	}

	return nFPS;
}

