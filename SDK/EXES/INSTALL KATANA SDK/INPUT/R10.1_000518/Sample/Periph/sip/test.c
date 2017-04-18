/*
	Ninja Sample

	COPYRIGHT (C) SEGA ENTERSRISES,LTD.

	Print Sample for SET5

	1998.6.4
	1998-09-09 for NTSC TV by SEKI Masahiro
	1998-11-15 for SBFOV by SEKI Masahiro
*/

#include <shinobi.h>
#include <wssip.h>

/*** defines ***/
#define USER_SMPBUF_BLK_SIZE (2205)     /* 0.2 sec of 11025Hz */
#define USER_SMPBUF_BLK_NUM  (10)

/*** switches ***/

/*** prototype functions ***/
Sint32 user_main();
void displaySamplingData16( Sint16 *p, Sint32 num, Sint32 limit );
void displayBufStat( Sint32 x, Sint32 y, Sint32 stat );
void operateSip( Sint32 stat );
void displayWrRdPostion( Sint32 x, Sint32 y );

#define TMP_BUFFER_SIZE (0x100)
#if 1 /* 19981110 */
Sint16 tmpBuffer[TMP_BUFFER_SIZE];
#endif
volatile Sint32 gVblankCount = 0;		/* V-Blank Counter */
WSBUF gWsbuf;							/* global handle for one SIP */
WSSTM gWsstm;							/* blogal handle for one proccess */
Sint16 gSamplingBuffer[USER_SMPBUF_BLK_SIZE * USER_SMPBUF_BLK_NUM];
Sint16 gVoiceBuffer[USER_SMPBUF_BLK_SIZE * USER_SMPBUF_BLK_NUM * 20]; /* 40 sec of 11025Hz */
Sint32 gVBindex;

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
    njInitVertexBuffer( 100000, 0, -100000, 0, 0);
    njInitPrint(NULL, 0, 0);
    njPrintSize(14);
	njSetBackColor(0x00000000, 0x00000000, 0x000000FF);
	wsInit();
	{ /* create handle */
		WSS_BUF_PRM parameter;

		/* set parameters to a WSB handle */
		parameter.sfreq   = WSD_BUF_SFREQ_11KHZ;
		parameter.bps     = WSD_BUF_BPS_16BIT;
		parameter.blksize = USER_SMPBUF_BLK_SIZE * sizeof(Sint16);
		parameter.nblk    = USER_SMPBUF_BLK_NUM;
#if 1 /* 19981211 */
		parameter.gain    = (WSD_BUF_GAIN_MAX + WSD_BUF_GAIN_MIN)/2; /* medium */
#else
		parameter.gain    = WSD_BUF_GAIN_MAX ;
#endif
		parameter.bufptr  = (void *)gSamplingBuffer;
		/* create a WSBUF handle */
		/* for A2 port */
		gWsbuf = wsBufCreate( WSD_DEV_A2, parameter );
		/* create a WSSGM handle */
		gWsstm = wsStmCreate( gWsbuf );
	}
	{ /* clear gVoiceBuffer with 0x11 for debug */
		memset( gVoiceBuffer, 0x11, sizeof(gVoiceBuffer) );
		gVBindex = 0;
	}
#if 1 /* 19981110 */
	{ /*** clear tmpBuffer with 0x11 for debug */
		memset( tmpBuffer, 0x11, sizeof( tmpBuffer ) );
		memset( gSamplingBuffer, 0xbb, sizeof( gSamplingBuffer ) );
	}
#endif
}

volatile Sint32 i = 0;

Sint32 njUserMain(void)
{
	user_main();

	njPrintC(NJM_LOCATION(1, 2), "WSSIP SAMPLE");
	njPrintH(NJM_LOCATION(14, 2), i++, 8);
	njPrintPeripheralInfo(NJM_LOCATION( 0, 3), NJD_PORT_A0);
	return NJD_USER_CONTINUE;
}

void njUserExit(void)
{
	sbExitSystem();
}

Sint32 user_main( void )
{
	Sint32 sipStat;
	Uint32 overflow;
#if 1 /* 19981115 */
	Sint32 sipOverflow;
#endif

	sipStat = wsBufGetStat( gWsbuf );

	displayBufStat( 18, 3, sipStat );

	overflow = wsStmIsOverflow( gWsstm );
	if( overflow == TRUE ) {
		njPrintC( NJM_LOCATION(23, 2), "OVERFLOW!!!" );
	} else {
		njPrintC( NJM_LOCATION(23, 2), "NO OVERFLOW" );
	}

	sipOverflow = wsBufGetSBFOV( gWsbuf );
	if( sipOverflow == TRUE ) {
		njPrintC( NJM_LOCATION(23, 3), "SBFOV OVER!" );
	} else {
		njPrintC( NJM_LOCATION(23, 3), "SBFOV OK..." );
	}

	displayWrRdPostion( 18, 8 );

	operateSip( sipStat );

	return 0;
}

void displayPower( Sint16 x, Sint16 y, Sint32 num, Sint16 *buff )
{
	Sint32 i;
	Uint32 total;

	total = 0;
	for( i=0; i<num; i++ ) {
		total += ((Uint32)ABS(*buff) * (Uint32)ABS(*buff)) ;
		buff++;
	}
	total /= num;
#if 1
	njPrintC( NJM_LOCATION(x,y), "POWER:" );
	njPrintH( NJM_LOCATION(x+6,y), total, 8 );
#else
	total /= (0x7fff * 0x7fff / 0x0010);
	for( i=0; i<total; i++ ) {
		njPrintC( NJM_LOCATION(x+i,y), "+" );
	}
	for( ;i<0x0010; i++ ) {
		njPrintC( NJM_LOCATION(x+i,y), "|" );
	}
#endif
}

extern Sint32 wsEncodeGain( Sint32 );
void displayGain( Sint16 x, Sint16 y, Sint32 gain )
{
	njPrintC( NJM_LOCATION(x,y), "GAIN:" );
	njPrintH( NJM_LOCATION(x+5,y), gain, 2 );
	njPrintH( NJM_LOCATION(x+8,y), wsEncodeGain( gain ), 8 );
}

void displaySamplingData16( Sint16 *p, Sint32 num, Sint32 limit )
{
	njPrintC( NJM_LOCATION(17,4), "NUM=" );
	njPrintH( NJM_LOCATION(21,4), num, 8 );
	njPrintC( NJM_LOCATION(17,5), "LIM=" );
	njPrintH( NJM_LOCATION(21,5), limit, 8 );
	if( num <= 0 ) {
		njPrintC( NJM_LOCATION(17,6), "NO SAMPLING DATA" );
	} else {
		njPrintC( NJM_LOCATION(17,6), "SAMPLING NOW    " );
	}
}

void displayBufStat( Sint32 x, Sint32 y, Sint32 stat )
{
	switch( stat ){
	case WSD_STAT_DISCNCT:
		njPrintC( NJM_LOCATION(x, y), "DISCNCT" );
		break;
	case WSD_STAT_STOP:
		njPrintC( NJM_LOCATION(x, y), "STOP   " );
		break;
	case WSD_STAT_REC:
		njPrintC( NJM_LOCATION(x, y), "REC    " );
		break;
	case WSD_STAT_ERR:
		njPrintC( NJM_LOCATION(x, y), "ERR    " );
		break;
	case WSD_STAT_RETRY:
		njPrintC( NJM_LOCATION(x, y), "RETRY  " );
		break;
	case WSD_STAT_RESTART:
		njPrintC( NJM_LOCATION(x, y), "RESTART" );
		break;
	default:
		njPrintC( NJM_LOCATION(x, y), "ERR2   " );
		break;
	}
}

void operateSip( Sint32 stat )
{
	NJS_PERIPHERAL *pad;
	Sint32 numSample, numLimit;
#if 0 /* 19981110 */
	Sint16 tmpBuffer[TMP_BUFFER_SIZE];
#endif
	static Sint32 overflowCheck = TRUE;

	pad = njGetPeripheral( NJD_PORT_A0 );
	numLimit = 255 - ((Sint32)(pad->r)/8)*8 +1;
	displayGain( 18, 15, wsBufGetAmpGain(gWsbuf) );
	wsBufSetAmpGain( gWsbuf,
		WSD_BUF_GAIN_MAX - (Sint32)(pad->l)*(WSD_BUF_GAIN_MAX-WSD_BUF_GAIN_MIN)/255);

	if( pad->press & NJD_DGT_TX ) {
		if( overflowCheck == TRUE ) {
			overflowCheck = FALSE;
		} else {
			overflowCheck = TRUE;
		}
	}
	if( overflowCheck == TRUE ) {
		njPrintC( NJM_LOCATION(17,7), "OVERFLOW CHECK" );
	}

	if( stat == WSD_STAT_REC ) {
		Uint32 overflowFlag;
		if( overflowCheck == TRUE ) { /* check overflow */
			overflowFlag = wsStmIsOverflow( gWsstm );
			if( overflowFlag == TRUE ) {
				WSBUF wsbuf;
				WSS_POS tmppos;
				WSS_POS marginpos = {0,0x400};
				wsbuf = wsStmGetWsbuf( gWsstm );
				tmppos = wsBufGetWrPos( wsbuf );
				tmppos = wsPosMinus( tmppos, marginpos );
				/* seek reading position to the end before marginpos samples */
				wsStmSeekRdPos( gWsstm, tmppos, WSD_STM_SEEK_SET );
				wsStmClearOverflow( gWsstm );
			}
		}
		numSample = wsStmCopyPcm( gWsstm, (void *)tmpBuffer, numLimit * sizeof(Sint16) );
		/*** display sampling data ***/
		displaySamplingData16( tmpBuffer, numSample, numLimit );
		wsStmAddRdPos( gWsstm, numSample );
		if( (gVBindex + numSample) < (sizeof(gVoiceBuffer)>>1) ) {
			memcpy( (void *)&(gVoiceBuffer[gVBindex]), (void *)tmpBuffer, numSample << 1 );
			gVBindex += numSample;
		}
		displayPower( 18, 14, numSample, tmpBuffer );
	}

	if( pad->press & NJD_DGT_TA ) {
		wsBufStart( gWsbuf );
	} else {
		if( pad->press & NJD_DGT_TB ) {
			wsBufStop( gWsbuf );
		}
	}
}

void displayWrRdPostion( Sint32 x, Sint32 y )
{
	WSS_POS wr, rd;
	WSS_POS df;

	wr = wsBufGetWrPos( gWsbuf );
	rd = wsStmGetRdPos( gWsstm );
	df = wsPosMinus( wr, rd );
	njPrintC( NJM_LOCATION(x  , y  ), "W POS" );
	njPrintH( NJM_LOCATION(x  , y+1), wr.high, 8 );
	njPrintC( NJM_LOCATION(x+8, y+1), "," );
	njPrintH( NJM_LOCATION(x+9, y+1), wr.low, 8 );
	njPrintC( NJM_LOCATION(x  , y+2), "R POS" );
	njPrintH( NJM_LOCATION(x  , y+3), rd.high, 8 );
	njPrintC( NJM_LOCATION(x+8, y+3), "," );
	njPrintH( NJM_LOCATION(x+9, y+3), rd.low, 8 );
	njPrintC( NJM_LOCATION(x  , y+4), "DIFFERENCE" );
	njPrintH( NJM_LOCATION(x  , y+5), df.high, 8 );
	njPrintC( NJM_LOCATION(x+8, y+5), "," );
	njPrintH( NJM_LOCATION(x+9, y+5), df.low, 8 );
}
