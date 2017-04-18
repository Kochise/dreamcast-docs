/*==========================================================================
 *
 *  Copyright (C) 1995 Microsoft Corporation. All Rights Reserved.
 *
 *  File:       sfx.c
 *  Content:    Routines
 *
 *
 ***************************************************************************/
#include "resource.h"
#include "duel.h"
#include "ds3dutil.h"
#include "sfx.h"

/***************************** EXTERNALS ***************************/
extern  HWND ghWndMain;

/******************************* GLOBAL VARIABLES ***************************/
LPDIRECTSOUND                           glpDirectSound;
LPDIRECTSOUND3DLISTENER                      glpDirectSound3DListener;
LPDIRECTSOUNDBUFFER                     glpPrimaryBuffer;
LPWAVEDATA                              gSoundEffect[MAX_SOUNDS];

_TCHAR *szResourceName[MAX_SOUNDS] =
{_T("BFIRE"),  //Bullet Firing
 _T("SBOOM"),  //Ship Exploding
 _T("SENGINE"),//Ship Engine
 _T("SSTART"), //Starting Engine
 _T("SSTOP"),  //Stopping Engine (key 5)
 _T("SBOUNCE"),//Bouncing off a block or window edge
 _T("LBOOM")}; //Block destruction

BOOL gbSoundInitialized = FALSE; //did the sound engine initialize or not?

/***************************** FUNCTION PROTOTYPES **************************/
BOOL Init_Sounds(void);
void Free_Sounds(void);
BOOL Init_Globals(void);
void Free_Globals(void);

/****************************************************************************
FUNCTION:   InitSfx


PURPOSE:    Initializes global variables, then loads the gSoundEffect "objects"
            with sound data.  This should always return TRUE.  If for some reason
            sound can't be initialized, then it will note that fact and still
            return TRUE.
*****************************************************************************/
BOOL InitSfx(void)
{
if (Init_Globals())
    {
    if (Init_Sounds())
        {
        gbSoundInitialized=TRUE;
        return TRUE;
        }
    Free_Globals();
    }
gbSoundInitialized = FALSE;
return TRUE;
};



/****************************************************************************
FUNCTION:   CleanupSfx

PURPOSE:    Frees everything that was allocated by InitSfx, if it was 
            successfully initialized in the beginning.
*****************************************************************************/
void CleanupSfx(void)
{
if (gbSoundInitialized)
    {
    Free_Sounds();
    Free_Globals();
    }
};

/****************************************************************************
FUNCTION:   Init_Globals

PURPOSE:    Initializes the three main global variables. After this is done,
            we should have allocated:
            a. A DirectSound Object
            b. A DirectSound3DListener Object
            c. A Primary Buffer (16 bit, stereo, 22050khz)

            These are all global.
*****************************************************************************/
BOOL Init_Globals(void)
{
PCMWAVEFORMAT pcmwf;
DSBUFFERDESC dsbdesc;

if (DS_OK == DirectSoundCreate(NULL, &glpDirectSound, NULL))
    {
    memset(&pcmwf, 0, sizeof(PCMWAVEFORMAT));
    pcmwf.wf.wFormatTag = WAVE_FORMAT_PCM;
    pcmwf.wf.nChannels = 2;
    pcmwf.wf.nSamplesPerSec = 22050;
    pcmwf.wf.nBlockAlign = 4;
    pcmwf.wf.nAvgBytesPerSec = pcmwf.wf.nSamplesPerSec * pcmwf.wf.nBlockAlign;
    pcmwf.wBitsPerSample = 16;
    memset(&dsbdesc, 0, sizeof(DSBUFFERDESC));
    dsbdesc.dwSize = sizeof(DSBUFFERDESC);
    dsbdesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRL3D;
    dsbdesc.dwBufferBytes = 0; //dwBufferBytes and lpwfxFormat must be set this way.
    dsbdesc.lpwfxFormat = NULL;

    if (DS_OK== IDirectSound_SetCooperativeLevel(glpDirectSound, ghWndMain,DSSCL_NORMAL))    
        {
        if (DS_OK== IDirectSound_CreateSoundBuffer(glpDirectSound, &dsbdesc, &glpPrimaryBuffer, NULL))
            {
            if (DS_OK==glpPrimaryBuffer->lpVtbl->QueryInterface(glpPrimaryBuffer, &IID_IDirectSound3DListener, (void **)&glpDirectSound3DListener))
                {
                if (DS_OK==IDirectSound3DListener_SetPosition(glpDirectSound3DListener, 0.f, 0.f, -1.f, DS3D_DEFERRED))
                    {
                    if (DS_OK==IDirectSound3DListener_SetDopplerFactor(glpDirectSound3DListener, 9.9f ,DS3D_DEFERRED))
                        {
                        if (DS_OK==IDirectSound3DListener_SetRolloffFactor(glpDirectSound3DListener, 0.25f ,DS3D_DEFERRED))
                            {
                            if (DS_OK==IDirectSound3DListener_CommitDeferredSettings(glpDirectSound3DListener))
                                {
                                return TRUE;
                                }
                            }
                        }
                    }
                IDirectSound3DListener_Release(glpDirectSound3DListener);
                }
            glpPrimaryBuffer->lpVtbl->Release(glpPrimaryBuffer);
            }        
        }
    IDirectSound_Release(glpDirectSound);
    }
return (FALSE);
};


/*****************************************************************************
FUNCTION:   Free_Globals

PURPOSE:    Frees up all three of the global interfaces that were created by
            Init_Globabls.

    NOTES:      Free_Sounds MUST be called before this.
*****************************************************************************/
void Free_Globals(void)
{
if (glpPrimaryBuffer!=NULL)
    glpPrimaryBuffer->lpVtbl->Release(glpPrimaryBuffer);
if (glpDirectSound3DListener!=NULL)
    IDirectSound3DListener_Release(glpDirectSound3DListener);
if (glpDirectSound!=NULL)
    IDirectSound_Release(glpDirectSound);
};


/****************************************************************************
FUNCTION:   Init_Sounds

PURPOSE:    Loads the gSoundEffect array (of sound objects) with the correct
            data from the WAVE resources, so that only a GetBuffers call needs
            to be made to get access to the sound effects.

NOTES:      If this fails, all sound objects will end up uninitialized.
            Init_Globals MUST be called before this function.
*****************************************************************************/
BOOL Init_Sounds(void)
{
int i;

for (i=0; i<MAX_SOUNDS; i++)
    {
    if (FALSE==WaveInit(&gSoundEffect[i], glpDirectSound, szResourceName[i]))    
        {
        gSoundEffect[i] = NULL;
        for (--i; i>=0; i--)
            {
            WaveFree(gSoundEffect[i]);
            gSoundEffect[i] = NULL;
            }
        ShowError(IDS_DSOUND_LOADWAVES);
        return FALSE;
        }
    }
return TRUE;
};

/*****************************************************************************
FUNCTION:   Free_Sounds

PURPOSE:    Frees up any sound objects that were loaded into memory.
*****************************************************************************/
void Free_Sounds(void)
{int i;

for (i=0; i<MAX_SOUNDS; i++)
    {
    if (gSoundEffect[i]!=NULL)
        {
        WaveFree(gSoundEffect[i]);
        gSoundEffect[i] = NULL;
        }
    }
};
