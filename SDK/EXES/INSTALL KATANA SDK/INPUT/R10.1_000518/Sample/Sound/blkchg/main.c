/*
      Bank Change Test
*/

/*                 */
/* Include headers */
/*                 */
#include <shinobi.h>
#include "sndutls.h"

/* defines */
#define MAX_OF_FX 1 

/*                   */
/* Declare Prototype */
/*                   */
void UserVBlankIn( void );
void SoundInit( void );
void SoundMain( PDS_PERIPHERAL * );
void setpan( Sint8 *, Sint8 );
void main( void );

static SDMIDI midi_handle;
static SDSHOT shot_handle;

/*                 */
/* Function Define */
/*                 */
void UserVBlankIn() {
  /* Call Sound Server */
  sdSysServer();
}

void LoadBank( const char *name, SDE_DATA_TYPE type, Sint8 num ) {
  SDMEMBLK       mem_blk;
  GDFS           fd;
  char           *mlt;
  Sint32         mlt_size;
  Uint32         size;

  /*                      */
  /* Load Bank File */
  /*                      */
  if ( ( fd = gdFsOpen( name, NULL ) ) != NULL ) {
    {
      gdFsGetFileSize( fd, &mlt_size );
      size = AttachSector( mlt_size );
      mlt = ( char * )syMalloc( size * sizeof( char ) );
      gdFsRead( fd, size / GDD_FS_SCTSIZE, mlt );
      sdMemBlkCreate( &mem_blk );
      sdMemBlkSetPrm( mem_blk, mlt, mlt_size, SDD_MEMBLK_SYNC_FUNC, NULL );
      sdBankDownload( mem_blk, type, num );
      sdMemBlkDestroy( mem_blk );

    }
    gdFsClose( fd );
  }
  syFree( mlt );
}

void SoundMain( PDS_PERIPHERAL *pad ) {
  static Sint8  num = 0;
  static Uint8  base = 0;
  static Sint32 mstatus = 0, ostatus = 0;
  GDFS          fd;
  char          *msg[] = { "STOP", "PLAY" };

  if ( pad->press & PDD_DGT_ST ) {
    if ( base == 0 ) {
      if ( mstatus == 0 ) {
        /* Sequence play */
        sdMidiPlay( midi_handle, 0, 0, 0 );
        mstatus = 1; 
      } else {
        sdMidiStop( midi_handle );
        mstatus = 0; 
      }
    } else {
      /* OneShot play */
      if ( ostatus == 1 ) {
        sdShotStop( shot_handle );
        ostatus = 0;
      } else { 
        sdShotPlay( shot_handle, 0, num, 0 );
        ostatus = 1;
      }  
    }
  }

  /* Change One shot song number */
  if ( pad->press & PDD_DGT_KL ) {
    if ( ++num > 3 ) num = 3;
  }
  if ( pad->press & PDD_DGT_KR ) {
    if ( --num < 0 ) num = 0;
  }

  /* Change FX Program number */
  if ( pad->press & PDD_DGT_KU ) {
    base = ++base % 2;
  }
  if ( pad->press & PDD_DGT_KD ) {
    base = --base % 2;
  }

  /* Load individual bank data */
  if ( pad->press & PDD_DGT_TX ) {
    if ( mstatus == 1 ) {
      sdMidiStop( midi_handle );
      njWaitVSync();
      mstatus = 0; 
    }
    LoadBank( "DEMO.MPB", SDE_DATA_TYPE_MIDI_PRG_BANK, 0 );
    LoadBank( "DEMO.MSB", SDE_DATA_TYPE_MIDI_SEQ_BANK, 0 );
  } else if ( pad->press & PDD_DGT_TY ) {
    if ( mstatus == 1 ) {
      sdMidiStop( midi_handle );
      njWaitVSync();
      mstatus = 0; 
    }
    LoadBank( "MUSIC.MPB", SDE_DATA_TYPE_MIDI_PRG_BANK, 0 );
    LoadBank( "MUSIC.MSB", SDE_DATA_TYPE_MIDI_SEQ_BANK, 0 );
  }

  njPrintC( NJM_LOCATION( 5, 10 + base ), ">" );
  njPrintC( NJM_LOCATION( 16, 10 ), msg[ mstatus ] );
  njPrintD( NJM_LOCATION( 16, 10 + 1 ), num, 1 );

}
 
void main(void)
{
  Int            y = 0, x = 0;
  static Sint32  i = 0;
  PDS_PERIPHERAL *pad;

#ifdef __GNUC__
	shinobi_workaround();
#endif

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

  SoundInitialize( "MANATEE.DRV", "BCHG.MLT" );
  /* Prepare MIDI and One shot port */
  sdMidiOpenPort( &midi_handle );
  sdShotOpenPort( &shot_handle );

  njSetVSyncFunction( UserVBlankIn );

  while ( 1 ) {
    pad = pdGetPeripheral( PDD_PORT_A0 );
    njPrintC( NJM_LOCATION( 5, 3 ), "-- Bank Change Test --" );
    njPrintC( NJM_LOCATION( 5, 4 ), "START     : Play music" );
    njPrintC( NJM_LOCATION( 5, 5 ), "X         : Sequence A" );
    njPrintC( NJM_LOCATION( 5, 6 ), "Y         : Sequence B" );
    njPrintC( NJM_LOCATION( 7, 10 ), "MIDI:" );
    njPrintC( NJM_LOCATION( 7, 11 ), "One Shot:" );
    SoundLibVer( 4, 13 );
    SoundDrvVer( 4, 14 );
    SoundDrvStat( 4, 15 );

    SoundMain( pad );

    njWaitVSync();
  }
}

/******************************* end of file *******************************/
