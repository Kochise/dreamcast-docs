/*
      GD-DA TEST
*/

/*                 */
/* Include headers */
/*                 */
#include <shinobi.h>
#include <sg_sd.h>
#include "ginsu.h"

#include "sndutls.h"

/*                   */
/* Declare Prototype */
/*                   */
void SoundInit( void );
int SoundMain( PDS_PERIPHERAL * );
void main( void );

/*                 */
/* Function Define */
/*                 */
void GddaEasyPan( Sint32 pan ) {
  pan += 0x40;
  if ( pan <= 0 ) pan = 1;
  if ( pan > 0x7f ) pan = 0x7f;
  sdGddaSetPan( pan, -( 0x80 - pan ) );
}

void GddaEasyVol( Sint32 vol ) {
  if ( vol > 0x7f ) vol = 0x7f;
  else if ( vol < 0 ) vol = 0;
  sdGddaSetVol( vol, vol );
}

int SoundMain( PDS_PERIPHERAL *pad ) {
  static Sint32 pan = 0;
  static Sint32 vol = 0x7f;
  SDS_GDDA_STAT st;
  Sint32        play;
  Sint32        pl, pr, vl, vr;

  char *mes[] = { "STOP", "PLAY" };

  /* Get GD drive status */
  if ( gdFsGetDrvStat() != GDD_DRVSTAT_PLAY ) 
  {
    play = 0;
  } 
  else 
  {
    play = 1;
  }
  
  if ( pad->on & PDD_DGT_TA ) 
  {
	  return -1;
  } 
  else if ( pad->press & PDD_DGT_ST ) 
  {  
	 if ( play == 0 ) 
	{
      gdFsDaPlay(gsGDDALogicalToPhysical(4), gsGDDALogicalToPhysical(4), 0 );
      GddaEasyVol( 0x7f );
      GddaEasyPan( 0 );
      pan = 0;
      vol = 0x7f;
    } 
	
	else 
	{
      GddaEasyPan( 0 );
      pan = 0;
      vol = 0;
      gdFsDaStop();
      GddaEasyVol( vol );
    }
  }

  else if ( pad->on & PDD_DGT_KR ) 
  {
    if ( ++pan > 0x7f ) pan = 0x7f;
    GddaEasyPan( pan );
  } 
  
  else if ( pad->on & PDD_DGT_KL ) 
  {
    if ( --pan < -0x7f ) pan = -0x7f;
    GddaEasyPan( pan );
  }

  if ( pad->on & PDD_DGT_KU ) 
  {
    if ( ++vol > 0x7f ) vol = 0x7f;
    GddaEasyVol( vol );
  } 
  
  else if ( pad->on & PDD_DGT_KD ) 
  {
    if ( --vol < 0 ) vol = 0;
    GddaEasyVol( vol );
  }
  
  sdGddaGetStat( &st );

  njPrint( NJM_LOCATION( 10, 11 ), "Set Pan   :%d", pan );
  njPrint( NJM_LOCATION( 10, 12 ), "Set Volume:%d", vol );
  njPrint( NJM_LOCATION( 10, 13 ), "Real Pan value   :%d, %d", st.m_LeftPan, st.m_RightPan );
  njPrint( NJM_LOCATION( 10, 14 ), "Real Volume value:%d, %d ", st.m_LeftVol, st.m_RightVol );
  njPrintC( NJM_LOCATION( 10, 16 ), mes[ play ] );

  return 1;
}

void main(void)
{
  static Sint32  i = 0;
  PDS_PERIPHERAL *pad;
  GDFS           sys;
  int            cont;

#ifdef __GNUC__
	shinobi_workaround();
#endif
  gsInit();

  /* Initialize System */
  njSetBorderColor( 0x00000000 );

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

  gdFsChangeDir(gsGetBasePath());

  njInitVertexBuffer( 20000, 0, 20000, 0, 0 );
  njInitPrint( NULL, 0, NJD_TEXFMT_ARGB_1555 );
  njSetBackColor( 0x00000000, 0x00000000, 0x000000FF );

  SoundInitialize( "MANATEE.DRV", "STREAM.MLT" );
  GddaEasyPan( 0 );
  GddaEasyVol( 0x7f );
  sys = gdFsGetSysHn();
  /* Request update drive status to GD drive */
  gdFsReqDrvStat();

  while ( 1 ) {
    pad = (PDS_PERIPHERAL *) pdGetPeripheral( PDD_PORT_A0 );
    njPrintC( NJM_LOCATION( 10, 3 ), "GDDA Test" );
    njPrintH( NJM_LOCATION( 0, 5 ), i++, 8 );
    SoundLibVer( 4, 7 );
    SoundDrvVer( 4, 8 );
    SoundDrvStat( 4, 9 );
    /* Waiting for finish to request update status */
    while ( gdFsGetStat( sys ) != GDD_STAT_COMPLETE );
    cont = SoundMain( pad );
	if (cont==-1)
	{
		break;
	}
    
	/* Request update drive status to GD drive */
    gdFsReqDrvStat();

    sdSysServer();
    njWaitVSync();

  }

	njExitPrint();
	sbExitSystem();
	gsExit();
}

/******************************* end of file *******************************/
