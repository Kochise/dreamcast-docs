#ifndef DS3DUTIL_HEADER
#define DS3DUTIL_HEADER

/*==========================================================================
 *
 *  Copyright (C) 1995 Microsoft Corporation. All Rights Reserved.
 *
 *  File:       ds3dutil.h
 *  Content:    Header file prototyping routines for dealing with
 *              sounds from resources.   Much of this stuff
 *              (especially the wave file parsing code) is copied
 *              from dsutil.cpp
 *
 *
 ***************************************************************************/
#include <dsound.h>

typedef struct
{
LPDIRECTSOUNDBUFFER lpDirectSoundBuffer;
LPTSTR lpName;
LPDIRECTSOUND lpDS;
}
WAVEDATA, *LPWAVEDATA;


BOOL WaveInit(LPWAVEDATA *lplpWD, LPDIRECTSOUND lpDS, LPCTSTR lpName);
BOOL WaveGetBuffers(LPWAVEDATA lpWD,
                    LPDIRECTSOUNDBUFFER   *ppDirectSoundBuffer,
                    LPDIRECTSOUND3DBUFFER *ppDirectSound3DBuffer,
                    BOOL bOurShip);
void WaveFree(LPWAVEDATA lpWD);
BOOL WaveReload(LPWAVEDATA lpWD);


#endif

