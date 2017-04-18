/*
	GDFS Streaming sample

	COPYRIGHT (C) SEGA ENTERSRISES,LTD.

	1999.01.19
*/

#include <shinobi.h>
#include "msg.h"
#include "fstr.h"


#define  WAIT_LOOP  if (--wait < 0) mode++

char msgbuf[80];

Sint32 readBuf[2048];


#define MAX_STREAM  8

/* stream buffers */
StrBuf strbuf[MAX_STREAM] = {
	/* 全セクタ数、バック可能セクタ数、読み込み許可セクタ数、バッファのポインタ */
	/* total sectors, sectors for backtrack, limit for pre-load, pointer of buffer */
	{  24,  4,  20, NULL },
	{  48,  8,  36, NULL },
	{  96, 16,  60, NULL },
	{ 192, 32, 120, NULL },
	{  24,  2,  20, NULL },
	{  48,  4,  36, NULL },
	{  96,  6,  50, NULL },
	{ 192,  8, 100, NULL },
};


char *strFiles[MAX_STREAM] = {
	"S0000.",
	"S0001.",
	"S0002.",
	"S0003.",
	"S0004.",
	"S0005.",
	"S0006.",
	"S0007.",
};


enum main_mode {
	MAIN_INI,
	MAIN_INI_WAIT,
	MAIN_TEST,
	MAIN_TEST2,
	MAIN_TEST3,
	MAIN_TEST4,
	MAIN_END
};


void njUserInit(void)
{
	Sint32 i;

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
    njInitVertexBuffer( 100000, 0, 100000, 0, 0);
    njInitPrint(NULL, 0, 0);
    njPrintSize(14);
	njSetBackColor(0x00000000, 0x00000000, 0x000000FF);
	
	initMsg();
	
	/* init about stream */
	for (i = 0; i < MAX_STREAM; i++) {
		/* alloc buffers */
		strbuf[i].buf = syMalloc(strbuf[i].total * STR_SCTSIZE);
		if (strbuf[i].buf == NULL) while (1);
	}
	
	StrInit(MAX_STREAM, strbuf);
}


Sint32 njUserMain(void)
{
	static Sint32 vcnt = 0;
	static Sint32 mode = 0;
	static Sint32 wait;
	static Sint32 try = 0;
	static STRHN shn[MAX_STREAM];
	Sint32 i;
	
	njPrintC(NJM_LOCATION(4,  2), "GDFS Streaming Sample");
	njPrintH(NJM_LOCATION(30,  2), vcnt++, 6);
	
	switch (mode) {
	case MAIN_INI:
		wait = 120;
		
		for (i = 0; i < MAX_STREAM; i++) shn[i] = NULL;
		
		mode++;
		break;
		
	case MAIN_INI_WAIT:
		WAIT_LOOP;
		break;
		
	case MAIN_TEST:
		putMsg("Start:");
		
		try++;
		
		for (i = 0; i < MAX_STREAM; i++) {
			shn[i] = StrOpen(strFiles[i], NULL);
#if 0
			sprintf(msgbuf, "OpenStreamFile[%d] \"%s\"", i+1, strFiles[i]);
			putMsg(msgbuf);
#endif
		}
		
		wait = 120;
		
		mode++;
		break;
		
	case MAIN_TEST2:
		if (wait > 0) {
			/* pause */
			wait--; break;
		} else {
			Sint32 alleof;
			
			alleof = 1;
			for (i = 0; i < MAX_STREAM; i++) {
				Sint32 n;
				n = StrFread(readBuf, 4, (rand() % 512) + 4, shn[i]);
				
				if (StrFeof(shn[i]) == FALSE) alleof = 0;
			}
			
			if (alleof) mode++;
		}
		break;
		
	case MAIN_TEST3:
		for (i = 0; i < MAX_STREAM; i++) {
			StrClose(shn[i]);
			shn[i] = NULL;
		}
		
		putMsg("End:");
		
		wait = 120;
		mode++;
		break;
		
	case MAIN_TEST4:
		WAIT_LOOP;
		
		break;
	
	case MAIN_END:
		mode = MAIN_TEST;
		break;
	}
	
	/* Stream Server */
	StrServer();
	
	/* display info */
	njPrint(NJM_LOCATION(2, 4), "TRY: %d", try);
	
	for (i = 0; i < MAX_STREAM; i++) {
		njPrint(NJM_LOCATION(2, 6+i), "%d:", i+1);
		
		if (shn[i] != NULL) {
			Sint32 tpct;
			Sint32 crest;
			Sint32 bemp;
			
			if (shn[i]->rdsct > 0) {
				njPrint(NJM_LOCATION(30, 6+i), "%4dR", shn[i]->rdsct);
			}
			
			tpct = shn[i]->cur * 1000 / shn[i]->filesize;
			crest = shn[i]->top - shn[i]->cur;
			if (crest == 0 && shn[i]->cur < shn[i]->filesize) bemp = '*';
			else bemp = ' ';
			njPrint(NJM_LOCATION(6, 6+i), "%4d/1000  %6d %c", tpct, crest, bemp);
		}
	}
	
	
	/* draw Message */
	drawMsg(2, 18);
	
	return NJD_USER_CONTINUE;
}


void njUserExit(void)
{
	njExitPrint();
	sbExitSystem();
}


/* eof */
