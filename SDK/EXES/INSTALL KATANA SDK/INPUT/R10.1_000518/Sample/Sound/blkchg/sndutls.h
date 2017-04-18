#ifndef __SNDUTLS_H__

#include <shinobi.h>
#include <sg_sd.h>

/* Declare Prototype */
void   SoundDrvStat( Sint32, Sint32 );
void   SoundDrvVer( Sint32, Sint32 );
void   SoundStatus( Sint32, Sint32 );
Uint32 AttachSector( Sint32 );
void   SoundInitialize( const char *, const char * );
void   PrgStop( void );

#define __SNDUTLS_H__
#endif

