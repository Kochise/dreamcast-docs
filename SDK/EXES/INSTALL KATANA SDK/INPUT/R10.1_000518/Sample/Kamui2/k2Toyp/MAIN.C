#define _STRICT_UNION_
#define _CLX_
#define _CLX2_

#include <shinobi.h>
#include <kamui2.h>
#include <sg_sycbl.h>

extern int		frame, FogAutoChange;
extern KMDWORD	FogDensity, FogD;

Int UserMain(void);
Int UserInit(void);
Int Kamui_Init(void);
void NextFrame(void);
void ReadMaple(void);
void PALExtCallbackFunc(PVOID pCallbackArguments); 

void	Check_Status(KMSTATUS status, char *func);
void	DisplayInformation	(void);

void main(void)
{

#ifdef __GNUC__
	shinobi_workaround();
#endif
    /* Check the cable for NTSC/PAL or VGA.. works properly for SCART. */
    switch (syCblCheck())
	{
        /* Initialize the display device and set the frame buffer based on the video mode. */
        case SYE_CBL_NTSC:  /* U.S./North America NTSC (60Hz) and Brazil PAL-M (60Hz). */
            sbInitSystem (KM_DSPMODE_NTSCNI640x480, KM_DSPBPP_RGB565, 1);
            break;
        case SYE_CBL_PAL:   /* Europe PAL (50Hz) and Argentina PAL-N (50Hz).*/
            sbInitSystem (KM_DSPMODE_PALNI640x480EXT, KM_DSPBPP_RGB565, 1);

			/*	Change the PAL height ratio */
			kmSetPALEXTCallback(PALExtCallbackFunc,NULL);
			kmSetDisplayMode (KM_DSPMODE_PALNI640x480EXT, KM_DSPBPP_RGB565, TRUE, FALSE);

            break;
        case SYE_CBL_VGA:   /* Standard VGA. */
            sbInitSystem (KM_DSPMODE_VGA, KM_DSPBPP_RGB565, 1);
            break;
        default:
            syBtExit();     /* Unknown video type, return to Dreamcast BootROM. */
	}

	UserInit();

	/* Render Loop */
	while(UserMain())
	{
		pdExecPeripheralServer();
	}
	sbExitSystem();
}

/*------------------------------------------------------------*/
/*  Function Name   : PALExtCallbackFunc                      */
/*  Inputs          : pCallbackArguments                      */  
/*  Outputs         : None                                    */
/*  Returns         : None                                    */
/*  Globals Used    :                                         */
/*  Description     : PAL mode callback (set the height ratio)*/ 
/*------------------------------------------------------------*/

VOID STATIC	PALExtCallbackFunc(PVOID pCallbackArguments)
{
PKMPALEXTINFO	pInfo;

	pInfo = (PKMPALEXTINFO)pCallbackArguments;
	pInfo->nPALExtMode = KM_PALEXT_HEIGHT_RATIO_1_133;	   //for PAL extended mode
	return;
}




Int UserInit(void)
{
	Kamui_Init();
}

Int UserMain(void)
{
	KMSTATUS	status;

	ReadMaple();
	NextFrame();
		/* Change fog density */
		if(((frame % 400) == 0)&&(FogAutoChange == 1))
		{
			FogDensity += FogD;	/* FF09 - FF0D */
			if(FogDensity > 0xFF0E) { FogDensity = 0xFF0D; FogD = -FogD; }
			if(FogDensity < 0xFF09) { FogDensity = 0xFF0A; FogD = -FogD; }
			status = kmSetFogDensity(FogDensity);
			Check_Status(status, "kmSetFogDensity");
			DisplayInformation ();
		}
	return 1;
}