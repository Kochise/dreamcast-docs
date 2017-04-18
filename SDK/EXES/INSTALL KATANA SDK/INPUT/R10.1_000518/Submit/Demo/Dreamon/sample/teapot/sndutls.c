/*
    This program is sound utility program.
    Uses on Sound sample.
*/
# include "sndutls.h"
/*
    AttachSector

    Name: AttachSector
    Synopsis:
        AttachSector( Sint32 size )
    Description:
        Normaly GD File system read file unit of sector, but file size not always
        sector size boundary. AttachSector fix any size of data to sector boundary
        size. This function mostly uses on memory allcation size.
*/
Uint32 AttachSector( Sint32 size ) {
  Uint32 ret;
  ret = ( size + GDD_FS_SCTSIZE - 1 ) / GDD_FS_SCTSIZE;
  return ret * GDD_FS_SCTSIZE;
}

/*
    SoundInitialize

    Name: SoundInitialize
    Synopsis:
        SoundInitialize( const char *DrvName, const char *MltName )
    Description:
        SoundInitialize read sound driver and multi unit file from GD-ROM,
        and Initialize all sound sysytem such as hup driver and transfer data.
*/
void SoundInitialize( const char *DrvName, const char *MltName ) {
  char           *gSndDrvPtr;
  Sint32         gSndDrvSize;
  SDMEMBLK       mem_blk;
  GDFS           fd;
  char           *mlt;
  Sint32         mlt_size;
  Uint32         size;

  /* Load Sound Driver */
  if ( ( fd = gdFsOpen( DrvName, NULL ) ) != NULL ) {
    {
      gdFsGetFileSize( fd, &gSndDrvSize );
      size = AttachSector( gSndDrvSize );
      gSndDrvPtr = ( char * )syMalloc( size * sizeof( char ) );
      gdFsRead( fd, size / GDD_FS_SCTSIZE, gSndDrvPtr );
    }
    gdFsClose( fd );
  } else PrgStop();

  /*                                 */
  /* Initialize sound library module */
  /*                                 */
  sdLibInit( NULL, 0, 0 );
  sdMemBlkCreate( &mem_blk );
  {
    /* Initialize sound driver */
    sdMemBlkSetPrm( mem_blk, gSndDrvPtr, gSndDrvSize, SDD_MEMBLK_SYNC_FUNC, NULL );
    sdDrvInit( mem_blk);

    /*                      */
    /* Load Multi Unit File */
    /*                      */
    if ( ( fd = gdFsOpen( MltName, NULL ) ) != NULL ) {
      {
        gdFsGetFileSize( fd, &mlt_size );
        size = AttachSector( mlt_size );
        mlt = ( char * )syMalloc( size * sizeof( char ) );
        gdFsRead( fd, size / GDD_FS_SCTSIZE, mlt );
        sdMemBlkSetPrm( mem_blk, mlt, mlt_size, SDD_MEMBLK_SYNC_FUNC, NULL );
        sdDownloadMultiUnit( mem_blk );
      }
      gdFsClose( fd );
    } else PrgStop();
  }
  sdMemBlkDestroy( mem_blk );

  syFree( gSndDrvPtr );
  syFree( mlt );

}

/*
    SoundDrvStat

    Name: SoundDrvStat
    Synopsis:
        SoundDrvStat( Sint32 x, Sint32 y )
    Description:
        SoundDrvStat shows sound driver status at any position in display.
*/
void SoundDrvStat( Sint32 x, Sint32 y ) {
  Uint32 drv_counter;

  sdDrvGetExecuteCounter( &drv_counter );

  njPrintC( NJM_LOCATION( x, y ), "Sound Driver Counter:" );
  njPrintH( NJM_LOCATION( x + 22, y ), drv_counter, 8 );

}

/*
    SoundDrvStat

    Name: SoundDrvVer
    Synopsis:
        SoundDrvVer( Sint32 x, Sint32 y )
    Description:
        SoundDrvVer shows sound driver Version at any position in display.
*/
void SoundDrvVer( Sint32 x, Sint32 y ) {
  SDS_VER ver;

  sdDrvGetVer( &ver );

  njPrint( NJM_LOCATION( x, y ), "Driver Version: %1d.%02x.%02x", ver.m_MajorVer, ver.m_MinorVer, ver.m_DebugVer );
}

/*
    SoundLibVer

    Name: SoundLibVer
    Synopsis:
        SoundLibVer( Sint32 x, Sint32 y )
    Description:
        SoundLibVer shows sound driver Version at any position in display.
*/
void SoundLibVer( Sint32 x, Sint32 y ) {
  SDS_VER ver;

  sdLibGetVer( &ver );

  njPrint( NJM_LOCATION( x, y ), "Library Version: %1d.%02x.%02x", ver.m_MajorVer, ver.m_MinorVer, ver.m_DebugVer );
}

/*
    SoundStatus

    Name: SoundStatus
    Synopsis:
       SoundStatus( Sint32, Sint32 );
    Description:
       SoundStatus shows any status such as sequence status and oneshot.
       Sound driver have 16 ports at every styles. This function shows these
       address and size of all ports.
*/
void SoundStatus( Sint32 x, Sint32 y )
{
  Sint32 i;
  Sint32 adr, size;

  njPrintC( NJM_LOCATION( x, y++ ), "Show Memory Map..." );

  njPrintC( NJM_LOCATION( x, y++ ), "MIDI Sequence Bank : No.  Address  Size" );
  for ( i = 0 ; i < 0x10 ; i++ ) {
    sdSndMemGetBankStat( SDE_DATA_TYPE_MIDI_SEQ_BANK, i, &adr, &size );
    njPrintH( NJM_LOCATION( x + 21, y ), i, 4 );
    njPrintH( NJM_LOCATION( x + 26, y ), adr, 8 );
    njPrintH( NJM_LOCATION( x + 35, y++ ), size, 8 );
  }

  njPrintC( NJM_LOCATION( x, ++y ), "MIDI Program Bank :  No.  Address  Size" );
  ++y;
  for ( i = 0 ; i < 0x10 ; i++ ) {
    sdSndMemGetBankStat( SDE_DATA_TYPE_MIDI_PRG_BANK, i, &adr, &size );
    njPrintH( NJM_LOCATION( x + 21, y ), i, 4 );
    njPrintH( NJM_LOCATION( x + 26, y ), adr, 8 );
    njPrintH( NJM_LOCATION( x + 35, y++ ), size, 8 );
  }

  njPrintC( NJM_LOCATION( x, ++y ), "One Shot Bank     :  No.  Address  Size" );
  for ( i = 0 ; i < 0x10 ; i++ ) {
    sdSndMemGetBankStat( SDE_DATA_TYPE_SHOT_BANK, i, &adr, &size );
    njPrintH( NJM_LOCATION( x + 21, y ), i, 4 );
    njPrintH( NJM_LOCATION( x + 26, y ), adr, 8 );
    njPrintH( NJM_LOCATION( x + 35, y++ ), size, 8 );
  }
}

void PrgStop( void ) {
  while ( -1 );
}
