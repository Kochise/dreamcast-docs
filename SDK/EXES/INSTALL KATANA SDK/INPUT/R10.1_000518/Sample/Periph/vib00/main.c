#include "shinobi.h"
#include "sg_pdvib.h"

Uint32 port[] = { 
  PDD_PORT_A1, PDD_PORT_A2,
  PDD_PORT_B1, PDD_PORT_B2,
  PDD_PORT_C1, PDD_PORT_C2,
  PDD_PORT_D1, PDD_PORT_D2,
};
Sint8 *portlit[] = {
  "A1", "A2",
  "B1", "B2",
  "C1", "C2",
  "D1", "D2",
};

typedef struct portinfo {
  PDS_VIBUNITINFO unitinfo[ 16 ];
  PDS_VIBINFO     info;
  Sint32          stat;
} PortInfo;

PortInfo pinfo[ 8 ];

void sbInit( void ) {
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

  for ( i = 0 ; i < sizeof( pinfo ) / sizeof( PortInfo ) ; ++i ) {
    pinfo[ i ].stat = 0;
  }
}

Sint32 enum_func( Uint32 unit, Sint32 stat, const PDS_VIBUNITINFO *info, Uint32 para ) {

  if ( stat == PDD_VIBERR_OK ) {
    pinfo[ para ].unitinfo[ unit ].position    = info->position;
    pinfo[ para ].unitinfo[ unit ].axis        = info->axis;
    pinfo[ para ].unitinfo[ unit ].pow_enable  = info->pow_enable;
    pinfo[ para ].unitinfo[ unit ].cont_enable = info->cont_enable;
    pinfo[ para ].unitinfo[ unit ].dir_enable  = info->dir_enable;
    pinfo[ para ].unitinfo[ unit ].wave_enable = info->wave_enable;
    pinfo[ para ].unitinfo[ unit ].min_freq    = info->min_freq;
    pinfo[ para ].unitinfo[ unit ].max_freq    = info->max_freq;
    pinfo[ para ].stat = 1;
  } else if ( stat == PDD_VIBERR_NO_VIBRATOR ) {
    pinfo[ para ].stat = 0;
  }
  return PDD_VIBRET_OK;
}

void ShowVibStat( PortInfo *info, PDS_VIBPARAM *para, Sint32 *x, Sint32 *y, Sint32 i ) {
  Sint32 yy = *y;
  njPrint( NJM_LOCATION( *x, yy + 0 ), "PORT %s IMFORMATION", portlit[ i ] );
  njPrint( NJM_LOCATION( *x, yy + 1 ), "NUMBER OF VIBRATION UNIT:%d", info->info.units );
  njPrint( NJM_LOCATION( *x, yy + 2 ), "NUMBER OF UNITS TO SET SAME TIME:%d", info->info.se_units );
  njPrint( NJM_LOCATION( *x, yy + 3 ), "INTERVAL (ANALOG R):%d", para->inc );
  njPrint( NJM_LOCATION( *x, yy + 4 ), "FREQUENCY(ANALOG L):%d", para->freq );
  njPrint( NJM_LOCATION( *x, yy + 5 ), "POWER    (ANALOG X):%d", para->power );
  *y += 7;
}

Sint32 sbMain() {
  Sint32         num = sizeof( port ) / sizeof( Uint32 );
  volatile Sint32         i, j;
  PDS_PERIPHERAL *pad;
  volatile PDS_VIBPARAM   param[ 15 ];
  Sint32         x = 2, y = 6, ret;

  njPrint( NJM_LOCATION( 10, 4 ), "-- VIBRATION MODULE SAMPLE --" );

  for ( i = 0 ; i < num ; ++i ) {
    pad = pdGetPeripheral( ( ( i / 2 ) * 6 ) );
    if ( pad->info->type != 0 ) {
      if ( pdVibIsReady( port[ i ] ) == TRUE ) {
        if ( pinfo[ i ].stat == 0 ) {
          if ( pdVibGetInfo( port[ i ], &pinfo[ i ].info ) == PDD_VIBERR_OK ) {
            if ( pdVibEnumerateUnit( port[ i ], enum_func, i ) != PDD_VIBERR_OK ) {
              njPrint( NJM_LOCATION( x, y ), "CAN'T GET STATUS" );
            }
          }
        } else {
          for ( j = 0 ; j < pinfo[ i ].info.se_units ; ++j ) {
            param[ j ].unit = j + 1;
            if ( pinfo[ i ].unitinfo[ j + 1 ].cont_enable == 1 ) {
              param[ j ].flag = 0;
              param[ j ].inc  =( 0x00ff & ( pad->r >> 5 ) );
              if ( pad->press & PDD_DGT_TA ) {
                param[ j ].flag = PDD_VIB_FLAG_CONTINUOUS;
                param[ j ].inc  = 0;
              } else if ( pad->press & PDD_DGT_TB ) {
                param[ j ].flag = PDD_VIB_FLAG_EXHALATION | PDD_VIB_FLAG_CONTINUOUS;
                param[ j ].inc  = pad->r >> 5;
              } else if ( pad->press & PDD_DGT_TX ) {
                param[ j ].flag = PDD_VIB_FLAG_CONVERGENCE | PDD_VIB_FLAG_CONTINUOUS;
                param[ j ].inc  = pad->r >> 5;
              }
            } else {
              param[ j ].flag = 0;
              param[ j ].inc  = 0;
            }
            if ( pinfo[ i ].unitinfo[ j + 1 ].pow_enable == 1 ) {
              param[ j ].power = pad->x1 / 16;
            }
            param[ j ].freq = ( pinfo[ i ].unitinfo[ j + 1 ].max_freq - pinfo[ i ].unitinfo[ j + 1 ].min_freq ) * pad->l / 255 + pinfo[ i ].unitinfo[ j + 1 ].min_freq;
          }
          ShowVibStat( &pinfo[ i ], &param[ 0 ], &x, &y, i );
        }
        if ( pad->press & ( PDD_DGT_TA | PDD_DGT_TB | PDD_DGT_TX ) ) {
          syCacheOCWB( param, sizeof( PDS_VIBPARAM ) * 16 );
          ret = pdVibStart( port[ i ], param, pinfo[ i ].info.se_units );
          if ( ret != PDD_VIBERR_OK ) {
            njPrint( NJM_LOCATION( x, y ), "OOPS! CAN'T VIBRATE" );
            y += 2;
          }
        }
        if ( pad->press & PDD_DGT_ST ) {
          for ( j = 0 ; j < pinfo[ i ].info.se_units ; ++j ) {
            param[ j ].power = 0;
          }
          ret = pdVibStart( port[ i ], param, pinfo[ i ].info.se_units );
          if ( ret != PDD_VIBERR_OK ) {
            njPrint( NJM_LOCATION( x, y ), "OOPS! CAN'T STOP TO VIBRATE" );
            y += 2;
          }
        }
      }
    } else {
      pinfo[ i ].stat = 0;
    }
  }
  return -1;
}

void sbExit( void ) {
  sbExitSystem();
}

void main( void ) {
#ifdef __GNUC__
	shinobi_workaround();
#endif
  while( -1 ) {
    sbInit();

    while( sbMain() < 0 ) {
      njWaitVSync();
    }

    sbExit();
  }
}
