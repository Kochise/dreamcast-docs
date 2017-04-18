/*
      One Shot Test
*/

/*                 */
/* Include headers */
/*                 */
#include <shinobi.h>

#include "sndutls.h"

/* Defines */
#define NUMBER_OF_SHOT 7

/*                   */
/* Declare Prototype */
/*                   */
void UserVBlankIn( void );
void SoundInit( void );
void SoundMain( PDS_PERIPHERAL * );
void main( void );

SDSHOT        oneshot_handle;
/*                 */
/* Function Define */
/*                 */
void UserVBlankIn() {
  /* Call Sound Server */
  sdSysServer();
}

void SoundInit() {
  SoundInitialize( "MANATEE.DRV", "ONESHOT.MLT" );
}

void SoundMain( PDS_PERIPHERAL *pad ) {
  SDE_ERR       err;
  static Uint16 number = 0;
  static Uint16 fx = 0;
  char *msg[] = { "FX Off", "FX On" };

  if ( pad->press & PDD_DGT_ST ) {
    /* Oneshot play */
    sdShotPlay( oneshot_handle, 0, number, 0  );
  } else if ( pad->press & PDD_DGT_KD ) {
     if ( ++number > NUMBER_OF_SHOT ) number = NUMBER_OF_SHOT;
  } else if ( pad->press & PDD_DGT_KU ) {
    if ( number == 0 ) number = 0;
    else --number;
  }

  njPrintC( NJM_LOCATION( 5, 8 ), "Music No is:" );
  njPrintH( NJM_LOCATION( 18, 8 ), number, 2 );
}

void main(void)
{
  static Sint32  i = 0;
  PDS_PERIPHERAL *pad;

#ifdef __GNUC__
	shinobi_workaround();
#endif

  /* Initialize System */
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
    njInitVertexBuffer( 20000, 0, 20000, 0, 0);
    njInitPrint(NULL, 0, NJD_TEXFMT_ARGB_1555);
    njPrintSize(14);
  njSetBackColor( 0x00000000, 0x00000000, 0x000000FF );

  SoundInit();
  njSetVSyncFunction( UserVBlankIn );

  sdShotOpenPort( &oneshot_handle );
  while ( 1 ) {
    pad = pdGetPeripheral( PDD_PORT_A0 );
    njPrintC( NJM_LOCATION( 5, 3 ), "-- Oneshot Test Sample --" );
    njPrintC( NJM_LOCATION( 5, 4 ), "Up/Down:Select Music" );
    njPrintC( NJM_LOCATION( 5, 5 ), "START  :Play One Shot" );
    SoundLibVer( 5, 10 );
    SoundDrvVer( 5, 11 );
    SoundDrvStat( 5, 12 );

    SoundMain( pad );

    njWaitVSync();
  }
  sdShotClosePort( oneshot_handle );
}

/******************************* end of file *******************************/
