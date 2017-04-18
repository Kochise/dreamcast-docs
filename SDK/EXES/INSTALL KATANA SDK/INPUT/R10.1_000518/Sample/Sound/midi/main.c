/*
      Direct MIDI Test
*/

/*                 */
/* Include headers */
/*                 */
#include <shinobi.h>

#include "sndutls.h"

  SDMIDI       midi_handle0;
  SDMIDI       midi_handle1;
  SDMIDI       midi_handle2;


/*                   */
/* Declare Prototype */
/*                   */
void UserVBlankIn( void );
void SoundInit( void );
void SoundMain( PDS_PERIPHERAL * );
void main( void );

/*                 */
/* Function Define */
/*                 */
void UserVBlankIn() {
  /* Call Sound Server */
  sdSysServer();
}



void SoundInit() {
  SDMIDI         midi_handle;
  SDS_MIDI_MES   midi;

  SoundInitialize( "MANATEE.DRV", "MIDI.MLT" );

}



void SoundMain( PDS_PERIPHERAL *pad ) {
  SDS_MIDI_MES midi;
  GDFS         fd;
  SDE_ERR		err;
  SDS_MIDI_STAT stat;
  Uint8 stop_f = 0;
  static Uint8 n_on = 0;
  static Uint8 n_ps = 0;
  char *str[] = { "STOP", "PLAY_A", "PLAY_B", "PLAY_X" };


/* ここで演奏終了をチェックしたい */
  if ( n_on != 0 ) {
	err = sdMidiGetStat( midi_handle0, &stat );
	if ( !(stat.m_Flg & SDD_PORT_FLG_PLAY)&&(n_on == 1) ) {
		stop_f = 1;
	}
	err = sdMidiGetStat( midi_handle1, &stat );
	if ( !(stat.m_Flg & SDD_PORT_FLG_PLAY)&&(n_on == 2) ) {
		stop_f = 1;
	}
	err = sdMidiGetStat( midi_handle2, &stat );
	if ( !(stat.m_Flg & SDD_PORT_FLG_PLAY)&&(n_on == 3) ) {
		stop_f = 1;
	}
  }


/* START キー で演奏停止 */
  if ( (pad->press & PDD_DGT_ST) || (stop_f == 1) ) {
    if ( n_on != 0 ) {
		err = sdMidiStop( midi_handle0 );
		err = sdMidiStop( midi_handle1 );
		err = sdMidiStop( midi_handle2 );
		n_on = 0;
		n_ps = 0;
    }
  }

/* A ボタン でシーケンス番号1スタート */
  if ( pad->press & PDD_DGT_TA ) {
    if ( n_on == 0 ) {
		err = sdMidiPlay( midi_handle0, 0, 0, 0 );
		n_on = 1;
		njWaitVSync();	/* SoundLibraryからDriverへのデータ渡し時間まち(1V-Int)これの為に画面が点滅します */
    }
  }

/* B ボタン でシーケンス番号2スタート */
  if ( pad->press & PDD_DGT_TB ) {
    if ( n_on == 0 ) {
		err = sdMidiPlay( midi_handle1, 0, 1, 0 );
		n_on = 2;
		njWaitVSync();	/* SoundLibraryからDriverへのデータ渡し時間まち(1V-Int)これの為に画面が点滅します */
    }
  }

/* C ボタン でシーケンス番号3スタート */
  if ( pad->press & PDD_DGT_TX ) {
    if ( n_on == 0 ) {
		err = sdMidiPlay( midi_handle2, 0, 2, 0 );
		n_on = 3;
		njWaitVSync();	/* SoundLibraryからDriverへのデータ渡し時間まち(1V-Int)これの為に画面が点滅します */
    }
  }

/* Y ボタン で一時停止/再開 */
  if (( pad->press & PDD_DGT_TY )&&( n_on != 0 )) {
    if ( n_ps == 0 ) {
    	switch(n_on){
    	case 1:
    		sdMidiPause( midi_handle0 );
    		break;
    	case 2:
    		sdMidiPause( midi_handle1 );
    		break;
    	case 3:
    		sdMidiPause( midi_handle2 );
    		break;
    	}
		n_ps = 1;
		njWaitVSync();	/* SoundLibraryからDriverへのデータ渡し時間まち(1V-Int)これの為に画面が点滅します */
    }
    else{
    	switch(n_on){
    	case 1:
    		sdMidiContinue( midi_handle0 );
    		break;
    	case 2:
    		sdMidiContinue( midi_handle1 );
    		break;
    	case 3:
    		sdMidiContinue( midi_handle2 );
    		break;
    	}
		n_ps = 0;
		njWaitVSync();	/* SoundLibraryからDriverへのデータ渡し時間まち(1V-Int)これの為に画面が点滅します */
    }
  }

/* 状態の描画 */
	njPrintC( NJM_LOCATION( 5, 10 ), "Play Status:" );
	njPrintC( NJM_LOCATION( 18, 10 ), str[ n_on ] );
	if(n_ps == 1){
		njPrintC( NJM_LOCATION( 25, 10 ), "PAUSE" );
	}
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
  sdMidiOpenPort( &midi_handle0 );
  sdMidiOpenPort( &midi_handle1 );
  sdMidiOpenPort( &midi_handle2 );


  while ( 1 ) {

	/*pad情報取得*/
    pad = pdGetPeripheral( PDD_PORT_A0 );
	/* 状態の描画 */
    njPrintC( NJM_LOCATION( 5, 4 ), "-- Send Direct MIDI Message Test --" );
    njPrintC( NJM_LOCATION( 5, 6 ), "START:A B X Button" );
    njPrintC( NJM_LOCATION( 5, 7 ), "STOP :START Button" );
    njPrintC( NJM_LOCATION( 5, 8 ), "PAUSE:  Y   Button" );
    SoundLibVer( 5, 12 );
    SoundDrvVer( 5, 13 );
    SoundDrvStat( 5, 14 );

    SoundMain( pad );

    njWaitVSync();	/* 画面描画の為の物 */
  }

  sdMidiClosePort( midi_handle0 );
  sdMidiClosePort( midi_handle1 );
  sdMidiClosePort( midi_handle2 );

}

/******************************* end of file *******************************/
