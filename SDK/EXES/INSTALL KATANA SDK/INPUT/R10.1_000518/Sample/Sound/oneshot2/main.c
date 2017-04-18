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

SDSHOT hn[ 8 ];
/*                 */
/* Function Define */
/*                 */
void UserVBlankIn() {
  /* Call Sound Server */
  sdSysServer();
}

void SoundInit() {
  Sint32 i;

  SoundInitialize( "MANATEE.DRV", "ONESHOT.MLT" );
  for ( i = 0 ; i < 8 ; ++i ) {
    sdShotOpenPort( &hn[ i ] );
  }
}

void SoundMain( PDS_PERIPHERAL *pad ) {
  SDE_ERR       err;
  Sint32        i, j;
  SDS_SHOT_STAT stat[ 8 ];
  Sint8         *msg[] = { "Play", "Pause", "Stop" };
  Sint32        selpos[] = { 23, 32, 42, 54 };
  static Sint32 music[ 8 ] = { 0, 1, 2, 3, 4, 5, 6, 7 };
  static Sint32 vol[ 8 ] = { 0, 0, 0, 0, 0, 0, 0, 0 };
  static Sint32 pan[ 8 ] = { 0, 0, 0, 0, 0, 0, 0, 0 };
  static Sint32 pitch[ 8 ] = { 0, 0, 0, 0, 0, 0, 0, 0 };
  static Uint32 pos = 0;
  static Uint32 sel = 0;

  if ( pad->press & PDD_DGT_KU ) {
    pos = ( --pos + 8 ) % 8;
  }
  if ( pad->press & PDD_DGT_KD ) {
    pos = ( ++pos + 8 ) % 8;
  }
  if ( pad->press & PDD_DGT_KR ) {
    sel = ( ++sel + 4 ) % 4;
  }
  if ( pad->press & PDD_DGT_KL ) {
    sel = ( --sel + 4 ) % 4;
  }
  if ( pad->on & PDD_DGT_TL ) {
    switch ( sel ) {
    case 0:
      if ( --music[ pos ] < 0 ) music[ pos ] = 0;
      break;
    case 1:
      if ( --vol[ pos ] < -0x7f ) vol[ pos ] = -0x7f;
      sdShotSetVol( hn[ pos ], vol[ pos ], 0 );
      break;
    case 2:
      if ( --pan[ pos ] < -0x7f ) pan[ pos ] = -0x7f;
      sdShotSetPan( hn[ pos ], pan[ pos ], 0 );
      break;
    case 3:
      if ( ( pitch[ pos ] -= 10 ) < -0x7fff ) pitch[ pos ] = -0x7fff;
      sdShotSetPitch( hn[ pos ], pitch[ pos ], 0 );
      break;
    }
  }
  if ( pad->on & PDD_DGT_TR ) {
    switch ( sel ) {
    case 0:
      if ( ++music[ pos ] > 7 ) music[ pos ] = 7;
      break;
    case 1:
      if ( ++vol[ pos ] > 0x7f ) vol[ pos ] = 0x7f;
      sdShotSetVol( hn[ pos ], vol[ pos ], 0 );
      break;
    case 2:
      if ( ++pan[ pos ] > 0x7f ) pan[ pos ] = 0x7f;
      sdShotSetPan( hn[ pos ], pan[ pos ], 0 );
      break;
    case 3:
      if ( ( pitch[ pos ] += 10 ) > 0x7fff ) pitch[ pos ] = 0x7fff;
      sdShotSetPitch( hn[ pos ], pitch[ pos ], 0 );
      break;
    }
  }
  if ( pad->press & PDD_DGT_TX ) {
    switch ( sel ) {
    case 0:
      if ( --music[ pos ] < 0 ) music[ pos ] = 0;
      break;
    case 1:
      if ( --vol[ pos ] < -0x7f ) vol[ pos ] = -0x7f;
      sdShotSetVol( hn[ pos ], vol[ pos ], 0 );
      break;
    case 2:
      if ( --pan[ pos ] < -0x7f ) pan[ pos ] = -0x7f;
      sdShotSetPan( hn[ pos ], pan[ pos ], 0 );
      break;
    case 3:
      if ( --pitch[ pos ] < -0x7fff ) pitch[ pos ] = -0x7fff;
      sdShotSetPitch( hn[ pos ], pitch[ pos ], 0 );
      break;
    }
  }
  if ( pad->press & PDD_DGT_TY ) {
    switch ( sel ) {
    case 0:
      if ( ++music[ pos ] > 7 ) music[ pos ] = 7;
      break;
    case 1:
      if ( ++vol[ pos ] > 0x7f ) vol[ pos ] = 0x7f;
      sdShotSetVol( hn[ pos ], vol[ pos ], 0 );
      break;
    case 2:
      if ( ++pan[ pos ] > 0x7f ) pan[ pos ] = 0x7f;
      sdShotSetPan( hn[ pos ], pan[ pos ], 0 );
      break;
    case 3:
      if ( ++pitch[ pos ] > 0x7fff ) pitch[ pos ] = 0x7fff;
      sdShotSetPitch( hn[ pos ], pitch[ pos ], 0 );
      break;
    }
  }
  if ( pad->press & PDD_DGT_ST ) {
    switch ( sel ) {
    case 0:
      music[ pos ] = pos;
      break;
    case 1:
      vol[ pos ] = 0;
      sdShotSetVol( hn[ pos ], vol[ pos ], 0 );
      break;
    case 2:
      pan[ pos ] = 0;
      sdShotSetPan( hn[ pos ], pan[ pos ], 0 );
      break;
    case 3:
      pitch[ pos ] = 0;
      sdShotSetPitch( hn[ pos ], pitch[ pos ], 0 );
      break;
    }
  }
  for( i = 0 ; i < 8 ; ++i ) {
    njPrint( NJM_LOCATION( 5, 9 + i * 2 ), "Port %d:", i );
    sdShotGetStat( hn[ i ], &stat[ i ] );
    if ( stat[ i ].m_Flg & SDD_PORT_FLG_PLAY ) j = 0;
    else j = 2;
    if ( stat[ i ].m_Flg & SDD_PORT_FLG_PAUSE ) j = 1;
    njPrint( NJM_LOCATION( 13, 9 + i * 2 ), "%s",msg[ j ] );
    njPrint( NJM_LOCATION( 18, 9 + i * 2 ), "Song: %d", music[ i ] );
    njPrint( NJM_LOCATION( 27, 9 + i * 2 ), "Vol:%4d  Pan:%4d  Pitch:%6d", vol[ i ], pan[ i ], pitch[ i ] );
  }
  njPrint( NJM_LOCATION( 3, 9 + pos * 2 ), ">" );
  njPrint( NJM_LOCATION( selpos[ sel ], 9 + pos * 2 + 1 ), "^^^" );
  if ( pad->press & PDD_DGT_TA ) {
    if ( stat[ pos ].m_Flg & SDD_PORT_FLG_PLAY ) {
      sdShotStop( hn[ pos ] );
    } else {
      sdShotPlay( hn[ pos ], 0, music[ pos ], 0 );
    }
  }
}

void main(void)
{
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
    njInitVertexBuffer( 50000, 0, 50000, 0, 0);
    njInitPrint(NULL, 0, NJD_TEXFMT_ARGB_1555);
    njPrintSize(14);

  njSetBackColor( 0x00000000, 0x00000000, 0x000000FF );

  SoundInit();
  njSetVSyncFunction( UserVBlankIn );

  while ( 1 ) {
    pad = pdGetPeripheral( PDD_PORT_A0 );
    njPrintC( NJM_LOCATION( 5, 3 ), "-- Oneshot Test Sample --" );
    njPrintC( NJM_LOCATION( 5, 4 ), "Up/Down:Select Port" );
    njPrintC( NJM_LOCATION( 5, 5 ), "A      :Play One Shot" );
    njPrintC( NJM_LOCATION( 5, 6 ), "X/Y    :Set Value" );
    njPrintC( NJM_LOCATION( 5, 7 ), "L/R    :Set Value" );

    SoundMain( pad );
    SoundLibVer( 7, 27 );
    SoundDrvVer( 7, 28 );
    SoundDrvStat( 7, 29 );
    njWaitVSync();
  }
}

/******************************* end of file *******************************/
