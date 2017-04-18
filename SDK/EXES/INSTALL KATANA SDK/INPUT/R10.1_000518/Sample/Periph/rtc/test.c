/*
    Shinobi AICA RTC Sample

    COPYRIGHT (C) SEGA ENTERSRISES,LTD.

    Date:
    1998/11/2
    1999/1/11 added comments by SEKI Masahiro
    1999/1/11 fixed displaying usrDisplayAgeOfMoon by SEKI Masahiro
*/

#include <shinobi.h>

SYS_RTC_DATE myDate;		/* for displaying date information */
SYS_RTC_DATE restoreDate;	/* for restoring date to time when a sample begins */
Sint32 cursorPos;			/* cursor position */

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
    njInitVertexBuffer( 10000, 0, 1000000, 0, 0);
    njInitPrint(NULL, 0, 0);
    njPrintSize(14);
	syG2SysInit( NULL );
	njSetBackColor(0x00000000, 0x00000000, 0x000000FF);

	syRtcInit();
	syRtcGetDate( &myDate );
	syRtcGetDate( &restoreDate );	/* save time when a sample begins */
	cursorPos = 0;
}

void usrDisplayDayOfWeek( Sint32 x, Sint32 y, SYS_RTC_DATE *date )
{
	char *week[] = { "SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT", "ERR" };

	if( date->dayofweek > 6 ) {
		njPrintC( NJM_LOCATION(x,y), week[7] );
	} else {
		njPrintC( NJM_LOCATION(x,y), week[date->dayofweek] );
	}
}

void usrDisplayAgeOfMoon( Sint32 x, Sint32 y, SYS_RTC_DATE *date )
{
	Sint32 i;
	if( date->ageofmoon > (Uint8)29 ) {
		njPrintC( NJM_LOCATION(x,y), "===============" );
	} else {
		if( date->ageofmoon<=15 ) {
			for( i=0; i<date->ageofmoon; i++ ) {
				njPrintC( NJM_LOCATION(x+i,y), "*" );
			}
			for( ;i<=15; i++ ) {
				njPrintC( NJM_LOCATION(x+i,y), "_" );
			}
		} else {
			for( i=0; i<(30-date->ageofmoon); i++ ) {
				njPrintC( NJM_LOCATION(x+15-i,y), "*" );
			}
			for( ;i<=15; i++ ) {
				njPrintC( NJM_LOCATION(x+15-i,y), "_" );
			}
		}
	}
}

void usrDisplayDate( Sint32 x, Sint32 y, SYS_RTC_DATE *date )
{
	Sint32 stat;
	njPrintC( NJM_LOCATION(x,y+1), "Age Of Moon" );
	usrDisplayAgeOfMoon( x+12, y+1, date );

	/* check server function status */
	stat = syRtcGetStat();
	if( stat & 1 ) {
		njPrintC( NJM_LOCATION(x,y+2), "PASSIVE" );
	} else {
		njPrintC( NJM_LOCATION(x,y+2), "ACTIVE" );
	}

	njPrintD( NJM_LOCATION(x,y), date->year, 4 );
	x+=4;
	njPrintC( NJM_LOCATION(x++,y), "/" );
	njPrintD( NJM_LOCATION(x,y), date->month, 2 );
	x+=2;
	njPrintC( NJM_LOCATION(x++,y), "/" );
	njPrintD( NJM_LOCATION(x,y), date->day, 2 );
	x+=2;
	njPrintC( NJM_LOCATION(x++,y), "(" );
	usrDisplayDayOfWeek( x, y, date );
	x += 3;
	njPrintC( NJM_LOCATION(x++,y), ")" );

	njPrintC( NJM_LOCATION(x++,y), " " );
	njPrintD( NJM_LOCATION(x,y), date->hour, 2);
	x+=2;
	njPrintC(NJM_LOCATION(x++,y), ":");
	njPrintD( NJM_LOCATION(x,y), date->minute, 2);
	x+=2;
	njPrintC(NJM_LOCATION(x++,y), ":");
	njPrintD( NJM_LOCATION(x,y), date->second, 2);
}

void usrOperate( Sint32 x, Sint32 y, SYS_RTC_DATE *date )
{
	NJS_PERIPHERAL *pad;

	/*** display current date ***/
	usrDisplayDate( x, y+1, &myDate );

	/* display cursor */
	switch( cursorPos ) {
	case 0:
		njPrintC( NJM_LOCATION(x,y), "vvvv" );
		break;
	case 1:
		njPrintC( NJM_LOCATION(x+5,y), "vv" );
		break;
	case 2:
		njPrintC( NJM_LOCATION(x+8,y), "vv" );
		break;
	case 3:
		njPrintC( NJM_LOCATION(x+16,y), "vv" );
		break;
	case 4:
		njPrintC( NJM_LOCATION(x+19,y), "vv" );
		break;
	case 5:
		njPrintC( NJM_LOCATION(x+22,y), "vv" );
		break;
	default:
		cursorPos = 0;
		njPrintC( NJM_LOCATION(x,y), "vvvv" );
		break;
	}

	pad = njGetPeripheral( NJD_PORT_A0 );
	switch( pad->press ) {
	case PDD_DGT_TX:
		syRtcFinish();
		break;
	case PDD_DGT_TY:
		syRtcInit();
		break;
	case PDD_DGT_TR:
		syRtcGetDate( date );
		break;
	case PDD_DGT_TB:
		/* switch server function status */
		if( (syRtcGetStat() & 1) == SYD_RTC_STAT_ACTIVE ) {
			syRtcSetServerMode( SYD_RTC_STAT_PASSIVE );
		} else {
			syRtcSetServerMode( SYD_RTC_STAT_ACTIVE );
		}
		break;
	case PDD_DGT_TA:
		/* set RTC date to user date */
		{
			Uint32 count;
			syRtcSetDate( &myDate );
			syRtcDateToCount( &myDate, &count );
			syRtcCountToDate( count, &myDate );
		}
		break;
	case PDD_DGT_ST:
		/* set RTC date to time when sample begins */
		{
			Uint32 count;
			syRtcSetDate( &restoreDate );
			syRtcDateToCount( &restoreDate, &count );
			syRtcCountToDate( count, &myDate );
		}
		break;
	case PDD_DGT_KU:
		/* change date */
		/* not check that the date exists */
		switch( cursorPos ) {
		case 0:
			myDate.year ++;
			break;
		case 1:
			myDate.month ++;
			break;
		case 2:
			myDate.day ++;
			break;
		case 3:
			myDate.hour ++;
			break;
		case 4:
			myDate.minute ++;
			break;
		case 5:
			myDate.second ++;
			break;
		}
		break;
	case PDD_DGT_KD:
		/* change date */
		/* not check that the date exists */
		switch( cursorPos ) {
		case 0:
			myDate.year --;
			break;
		case 1:
			myDate.month --;
			break;
		case 2:
			myDate.day --;
			break;
		case 3:
			myDate.hour --;
			break;
		case 4:
			myDate.minute --;
			break;
		case 5:
			myDate.second --;
			break;
		}
		break;
	case PDD_DGT_KR:
		/* change cursor */
		cursorPos ++;
		if( cursorPos > 5 ) {
			cursorPos = 0;
		}
		break;
	case PDD_DGT_KL:
		/* change cursor */
		if( cursorPos < 1 ) {
			cursorPos = 6;
		}
		cursorPos --;
		break;
	default:
		break;
	}
}

void usrDisplayCompare( Sint32 x, Sint32 y, SYS_RTC_DATE *date1, SYS_RTC_DATE *date2 )
{
	switch( syRtcCompareDate( date1, date2 ) ) {
	case -1:
		njPrintC( NJM_LOCATION(x,y), "SMALL" );
		break;
	case 0:
		njPrintC( NJM_LOCATION(x,y), "EQUAL" );
		break;
	case 1:
		njPrintC( NJM_LOCATION(x,y), "BIG" );
		break;
	default:
		njPrintC( NJM_LOCATION(x,y), "ERROR" );
		break;
	}
}

extern volatile Uint32 sygRtcCount;

Sint32 njUserMain(void)
{
	Sint32 y=0,x = 0;
	static Sint32 i;
	SYS_RTC_DATE date;

	njPrintC(NJM_LOCATION(1,6), "RTC SAMPLE");
	njPrintH(NJM_LOCATION(14,6),i++, 8);

	njPrintC( NJM_LOCATION(3,15), "CHANGE" );
	usrOperate( 3, 16, &date );

	if( syRtcGetStat() & SYD_RTC_STAT_PASSIVE ) {
		/* nothing */
	} else {
		syRtcGetDate( &date );
	}

	usrDisplayDate( 3, 8, &date );
	njPrintH( NJM_LOCATION(3, 11), sygRtcCount, 8 );	/* for debug */

	usrDisplayCompare( 3, 20, &myDate, &date );

	return NJD_USER_CONTINUE;
}

void njUserExit(void)
{
	syRtcFinish();

	sbExitSystem();
}
