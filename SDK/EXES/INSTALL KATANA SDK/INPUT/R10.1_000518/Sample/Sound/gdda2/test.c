/*
	Gdfs Sample

	COPYRIGHT (C) SEGA ENTERSRISES,LTD.

	Da play sample

	1998.9.27
*/

#include <shinobi.h>
#include <sg_sd.h>

#include "sddrv.h"


/*** variables ***/

Sint32 toc_buf[102];



/*** subroutine ***/

/* calc the end sector of track */
Sint32 calctrackend(Sint32 track)
{
	Sint32 tend;
	
	if (track < 3) return 0;
	
	if (track == 99) {
		/* get the start fad of leadout */
		tend = toc_buf[101] & 0x00ffffff;
		
	} else {
		if (toc_buf[track] == 0xffffffff) {
			/* get the start fad of leadout */
			tend = toc_buf[101] & 0x00ffffff;
			
		} else {
			/* get the start fad of next track */
			tend = toc_buf[track] & 0x00ffffff;
			
			/* if next track is a data track, subtract 1 second from that */
			if (((toc_buf[track] >> 24) & 0xff) == 0x41) {
				tend -= 75;
			}
		}
	}
	
	/* subtract 2 second */
	tend -= 75*2;
	
	return tend;
}

#if 0
void SoundInit(void *ptr)
{
	SDMEMBLK memblk = NULL;
	
	/*
	 *  Initialize Sound library
	 */
	sdLibInit( NULL, 0, 0);
	
	/* 
	 *  Download and Initialize Sound driver.
	 */
	/* Create Memory block handle */
	sdMemBlkCreate( &memblk);
	/* Setting Memoby block handle */
	sdMemBlkSetPrm( memblk, ptr, 0, SDD_MEMBLK_SYNC_FUNC, NULL);
	/* Initialize Sound driver */
	sdDrvInit( memblk);
	
	sdMemBlkDestroy( memblk);
}
#endif

/*** main routine ***/


void njUserInit(void)
{
    /* Check the cable for NTSC/PAL or VGA.. works properly for SCART. */
    switch (syCblCheck())
	{
        /* Initialize the display device and set the frame buffer based on the video mode. */
        case SYE_CBL_NTSC:  /* U.S./North America NTSC (60Hz) and Brazil PAL-M (60Hz). */
            sbInitSystem (NJD_RESOLUTION_640x480_NTSCNI, NJD_FRAMEBUFFER_MODE_RGB565, 1);
            break;
        case SYE_CBL_PAL:   /* Europe PAL (50Hz) and Argentina PAL-N (50Hz). */
            sbInitSystem (NJD_RESOLUTION_640x544_PALNI, NJD_FRAMEBUFFER_MODE_RGB565, 1);
            break;
        case SYE_CBL_VGA:   /* Standard VGA. */
            sbInitSystem (NJD_RESOLUTION_VGA, NJD_FRAMEBUFFER_MODE_RGB565, 1);
            break;
        default:
            syBtExit();     /* Unknown video type, return to Dreamcast BootROM. */
	}
    njSetBorderColor( 0x00000000 ) ;
    njInitVertexBuffer( 131072, 0, 131072, 0, 0);
    njInitPrint(NULL, 0, 0);
    njPrintSize(14);

	njSetBackColor(0x00000000,0x00000000,0x000000FF);

//      SoundInit(&g_manatee_drv);
        SoundInitialize( "MANATEE.DRV", "STREAM.MLT" );
}


enum main_mode {
	MAIN_INI,
	MAIN_STANDBY,
	MAIN_PLAY_IN,
	MAIN_PLAY,
	MAIN_PAUSE_IN,
	MAIN_PAUSE,
	MAIN_STOP,
	MAIN_END
};


Sint32 njUserMain(void)
{
	static Sint32 mode = 0;
	static Sint32 vcnt = 0;
	static Sint32 track = 3;
	static Sint32 time = 0;
	static Sint32 repeat = 0;
	const PDS_PERIPHERAL* per;
	static Sint32 getinfo = 0;
	static Sint32 release = 0;
	static GDFS_DAINFO dainfo;
	
	vcnt++;
	
	/* get padinfo */
	per = pdGetPeripheral(PDD_PORT_A0);
	
	if (getinfo) {
		/* check the dainfo */
		GDFS sys;
		Sint32 stat;
		
		sys = gdFsGetSysHn();
		stat = gdFsGetStat(sys);
		if (stat != GDD_STAT_BUSY) getinfo = 0;
		
		if (stat == GDD_STAT_COMPLETE) time = dainfo.min * 60 + dainfo.sec;
	}
	sdGddaSetVol( 0x7F, 0x7F );
	sdSysServer();

	switch (mode){
	case MAIN_INI:
		/* read toc */
		gdFsGetToc(1, toc_buf);
		
		mode++;
		break;
	
	case MAIN_STANDBY:
		time = 0;
		njPrintC(NJM_LOCATION(2,12), "STOP");
		
		if (per->press & PDD_DGT_KU) {
			if (track < 100) track++;
			
		} else if (per->press & PDD_DGT_KD) {
			if (track > 3) track--;
			
		} else if (per->press & PDD_DGT_TX) {
			repeat ^= 1;
			
		} else if (per->press & PDD_DGT_TA) {
			mode = MAIN_PLAY_IN;
		}
		break;
	
	case MAIN_PLAY_IN:
		njPrintC(NJM_LOCATION(2,12), "PLAY");
		
		if (getinfo == 0) {
			gdFsDaPlay(track, track, 0);
			mode = MAIN_PLAY;
		}
		break;
	
	case MAIN_PLAY:
		njPrintC(NJM_LOCATION(2,12), "PLAY");
		
		{
			Sint32 drvstat;
			drvstat = gdFsGetDrvStat();
			
			if (drvstat != GDD_DRVSTAT_PLAY && drvstat != GDD_DRVSTAT_BUSY
				&& drvstat != GDD_DRVSTAT_CANTREAD) {
				
				time = 0;
				if (release == 1) {
					/* procedure from releasing */
					release = 0;
					
					/* repeat */
					if (repeat) mode = MAIN_PLAY_IN;
					break;
					
				} else {
					/* normal end */
					mode = MAIN_STANDBY;
					break;
				}
			}
		}
		
		if (per->press & PDD_DGT_TA) {
			mode = MAIN_PAUSE_IN;
			
		} else if (per->press & PDD_DGT_TB) {
			mode = MAIN_STOP;
		}
		break;
	
	case MAIN_PAUSE_IN:
		if (getinfo == 0) {
			if (gdFsDaPause() == GDD_ERR_OK) mode = MAIN_PAUSE;
		}
		break;
	
	case MAIN_PAUSE:
		if (vcnt & 0x20) njPrintC(NJM_LOCATION(2,12), "PAUSE");
		
		if (getinfo == 0) {
			if (per->press & PDD_DGT_TA) {
				Sint32 tend;
				
				tend = calctrackend(track);
				
				/* play from paused sector to end sector */
				gdFsDaPlaySct(dainfo.fad, tend, 0);
				release = 1;
				mode = MAIN_PLAY;
				
			} else if (per->press & PDD_DGT_TB) {
				mode = MAIN_STOP;
			}
		}
		break;
	
	case MAIN_STOP:
		if (getinfo == 0) {
			if (gdFsDaPause() == GDD_ERR_OK) {
				release = 0;
				time = 0;
				dainfo.fad = 0;
				mode = MAIN_STANDBY;
			}
		}
		break;
	
	default:
		break;
	}
	
	/* get dainfo */
	if (getinfo == 0) {
		if (mode == MAIN_PLAY) {
			if (gdFsDaGetInfo(&dainfo) == GDD_ERR_OK) getinfo = 1;
		}
	}
	
	njPrintC(NJM_LOCATION(2,2), "GDFS DA-PLAY SAMPLE");
	
	njPrintC(NJM_LOCATION(2,20), "A ... PLAY/PAUSE");
	njPrintC(NJM_LOCATION(2,21), "B ... STOP");
	njPrintC(NJM_LOCATION(2,22), "X ... REPEAT");
	
	njPrintC(NJM_LOCATION(2,6), "Track ");
	njPrintD(NJM_LOCATION(10,6), track, 2);
	njPrintC(NJM_LOCATION(2,7), "Time  ");
	njPrintD(NJM_LOCATION(10,7), time / 60,  3);
	njPrintC(NJM_LOCATION(13,7), ":");
	njPrintD(NJM_LOCATION(14,7), time % 60,  2);
	if (repeat) njPrintC(NJM_LOCATION(2,9), "Repeat");
	
	return NJD_USER_CONTINUE;
}


void njUserExit(void)
{
	njExitPrint();
	sbExitSystem();
}

/* eof */
