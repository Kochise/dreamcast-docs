/*==========================================================================
 *
 *  Copyright (C) 1995 Microsoft Corporation. All Rights Reserved.
 *
 *  File:       ds3dutil.c
 *  Content:    Routines for dealing with sounds from resources
 *              The last 3 functions (the wave file parsing code)
 *              are copied from dsutil.cpp
 *
 *
 ***************************************************************************/
#include <tchar.h>
#include <dsound.h>
#include "ds3dutil.h"
//*************************** FUNCTION PROTOTYPES **************************/
BOOL DSParseWaveResource(void *pvRes, WAVEFORMATEX **ppWaveHeader,
                         BYTE **ppbWaveData,DWORD *pcbWaveSize);
BOOL DSGetWaveResource ( HMODULE hModule, LPCTSTR lpName,
                         WAVEFORMATEX **ppWaveHeader, BYTE **ppbWaveData,
                         DWORD *pcbWaveSize);
BOOL DSFillSoundBuffer(  IDirectSoundBuffer *pDSB, BYTE *pbWaveData, DWORD cbWaveSize);
BOOL DSReloadSoundBuffer(IDirectSoundBuffer *pDSB, LPCTSTR lpName);

//*************************** GLOBAL VARIABLES **************************/

_TCHAR gszWaveString[5] = _T("WAVE");

/*****************************************************************************
FUNCTION:  WaveInit

PURPOSE:   Loads a WAVEDATA struct with the named WAVE resource.

PARAMETERS:
lplpWD  A pointer to a WAVEDATA struct.

lpDS:   A pointer to an IDirectSound object.  This object must be,
        initialized BEFORE being passed to this function, and MUST have been
        initialized with the DSBCAPS_CTRL3D flag.

lpName: A string that contains the name of the .WAV resource.
*****************************************************************************/
BOOL WaveInit(LPWAVEDATA *lplpWD, LPDIRECTSOUND lpDS, LPCTSTR lpName)                   
{
DSBUFFERDESC dsBD = {0};
BYTE *pbWaveData=NULL;
LPWAVEDATA lpWD;

    lpWD = (*lplpWD) = (LPWAVEDATA)malloc(sizeof(WAVEDATA));
    lpWD->lpDirectSoundBuffer = NULL;
    lpWD->lpName = NULL;
    lpWD->lpDS = NULL;

    #ifndef UNICODE
        lpWD->lpName = (LPTSTR)malloc(strlen(lpName) + 1);
    #else
        lpWD->lpName = (LPTSTR)malloc(2*(wcslen(lpName) + 1));
    #endif
    if (lpWD->lpName != NULL)
    {
        _tcscpy(lpWD->lpName, lpName);
        
        if (DSGetWaveResource(NULL, lpName, &dsBD.lpwfxFormat, &pbWaveData, &dsBD.dwBufferBytes))
        {
            dsBD.dwSize = sizeof(DSBUFFERDESC);
            dsBD.dwFlags = DSBCAPS_STATIC     | DSBCAPS_GETCURRENTPOSITION2  | DSBCAPS_CTRL3D;
            if (DS_OK == IDirectSound_CreateSoundBuffer(lpDS, &dsBD, &lpWD->lpDirectSoundBuffer, NULL))
            {
                if (DSFillSoundBuffer(lpWD->lpDirectSoundBuffer, pbWaveData, dsBD.dwBufferBytes))
                {
                    lpWD->lpDS = lpDS; //also copy the DirectSoundObject
                    return(TRUE);
                }
                IDirectSoundBuffer_Release(lpWD->lpDirectSoundBuffer);
                lpWD->lpDirectSoundBuffer = NULL;
            }
        }
        free(lpWD->lpName);        
        lpWD->lpName = NULL;
    }
    free(*lplpWD);
    *lplpWD = NULL;
    return(FALSE);
};        


/*****************************************************************************
FUNCTION:   WaveGetBuffers

PARAMS:     lplpWD:
                A pointer to a WAVEDATA struct.
            lplpDirectSoundBuffer:
                The address of a pointer to a DirectSoundBuffer Interface.                
            lplpDirectSound3DBuffer:
                The address of a pointer to a DirectSound3DBuffer Interface.
            bOurShip:
                A Boolean telling whether the ship requesting the sound
                buffers is OUR ship.  If it is our ship, then instead of
                duplicating sound buffers for it we just copy the global
                pointers in.  That way we make sure that the global
                pointers are actually being put to good use before we
                go allocating more resources.
                
            
            Both of these must be Release()'d after their use.
                
PURPOSE:    Gives the caller back two interface pointers:  one to a regular
            DirectSoundBuffer interface and one to a 3D buffer interface.  These
            MUST be Released() by the caller.

RETURNS:    Should return TRUE, unless something really catastrophic has happened.

NOTES:      BOTH of these Interfaces MUST be ->Release()'d when the object
            or whatever is done using them.  Otherwise the buffer they point
            to will just hang around and waste memory.  This wastes processing time,
            since each buffer is checked by the mixer quite frequently to see if it
            is playing.

            Defaults:  Both Position and Velocity vectors are set to (0,0,0).
            
**************************************************************************************/ 
BOOL WaveGetBuffers (LPWAVEDATA lpWD,
                    LPDIRECTSOUNDBUFFER   *lplpDirectSoundBuffer,
                    LPDIRECTSOUND3DBUFFER *lplpDirectSound3DBuffer,
                    BOOL bOurShip)
{
DSBCAPS dsbc; //in case there's a problem duplicating hardware buffer
DSBUFFERDESC dsBD   ={0};
BYTE *pbWaveData    =NULL;

    *lplpDirectSoundBuffer = NULL;
    *lplpDirectSound3DBuffer = NULL;
    //so if we get to "failed:", we know what worked and what didn't.
    if (bOurShip)
    {//This is OUR ship, so we'll copy the buffer pointer.
        *lplpDirectSoundBuffer   = lpWD->lpDirectSoundBuffer;
    }
    else
    {
        //This is not our ship, so we'll have to dup a buffer or create a new one.
        if (DS_OK!=IDirectSound_DuplicateSoundBuffer(lpWD->lpDS, lpWD->lpDirectSoundBuffer, lplpDirectSoundBuffer))
        {
            //degrading to software
            dsbc.dwSize = sizeof(dsbc);
            if (DS_OK!=IDirectSoundBuffer_GetCaps(lpWD->lpDirectSoundBuffer, &dsbc))
            {
                goto failed;
            }
            //was the original one in hardware?
            if (DSBCAPS_LOCHARDWARE & dsbc.dwFlags)
            {
                //It's a HARDWARE buffer? Then we need to create a software sound
                //buffer, not duplicate this hardware one.
                if (DSGetWaveResource(NULL, lpWD->lpName, &dsBD.lpwfxFormat, &pbWaveData, &dsBD.dwBufferBytes))
                {
                    dsBD.dwSize = sizeof(DSBUFFERDESC);
                    dsBD.dwFlags = DSBCAPS_STATIC | DSBCAPS_GETCURRENTPOSITION2  | DSBCAPS_CTRL3D;
                    if (DS_OK == IDirectSound_CreateSoundBuffer(lpWD->lpDS, &dsBD, lplpDirectSoundBuffer, NULL))
                    {
                        if (!DSFillSoundBuffer(*lplpDirectSoundBuffer, pbWaveData, dsBD.dwBufferBytes))
                        {//DSFillSoundBuffer failed when creating software buffer for ship.                                   
                            goto failed;
                        }
                    }
                    else
                    {//CreateSoundBuffer failed when creating software buffer for ship.                        
                        goto failed;
                    }
                }
                else 
                {//GetWaveResource failed trying to duplicating a SOFTWARE buffer for ship.                    
                    goto failed;
                }
            }
            else
            {//it wasn't even trying to duplicate a hardware buffer, and
             //could not duplicate a software buffer.
                goto failed;
            }
        } //end the duplicate-regular-soundbuffer part.
    }


    //now we'll try to get a 3D buffer.
    if (DS_OK==IDirectSoundBuffer_QueryInterface(*lplpDirectSoundBuffer, &IID_IDirectSound3DBuffer, (void **)lplpDirectSound3DBuffer)) 
    {            
        return TRUE; //buffer was allocated!!!!
    }
    else
    {
    //Query for a 3D SoundBuffer Failed!!
        goto failed;
    }


failed:
    if (*lplpDirectSoundBuffer!=NULL)
    {
        if (!bOurShip)
            IDirectSoundBuffer_Release(*lplpDirectSoundBuffer);
        *lplpDirectSoundBuffer=NULL;
    }

    if (*lplpDirectSound3DBuffer!=NULL)
    {
        IDirectSoundBuffer_Release(*lplpDirectSound3DBuffer);
        *lplpDirectSound3DBuffer=NULL;
    }
    return FALSE;
};



/*****************************************************************************
FUNCTION:  WaveFree

PURPOSE:   When this is called, we HOPE that all the buffers
           (both the normal and the 3D ones) duplicated from "lpDirectSoundBuffer"
           in the function WaveGetBuffers() have been ->Release()'d.  This frees
           up the original buffer (lpDirectSoundBuffer) that all the other buffers
           have been duplicated from.
*****************************************************************************/ 
void WaveFree(LPWAVEDATA lpWD)
{
    if (lpWD!=NULL)
    {
        if (lpWD->lpDirectSoundBuffer != NULL)
          IDirectSoundBuffer_Release(lpWD->lpDirectSoundBuffer);
        if (lpWD->lpName != NULL)
            free(lpWD->lpName);
        free(lpWD);
    }
};

/*****************************************************************************
FUNCTION:   WaveReload

PURPOSE:    This reloads the wave's sound effect.
*****************************************************************************/
BOOL WaveReload(LPWAVEDATA lpWD)
{
    return DSReloadSoundBuffer(lpWD->lpDirectSoundBuffer, lpWD->lpName);
};



/*****************************************************************************
FUNCTION:  DSGetWaveResource

PURPOSE:   Sets the following:
            a. A pointer to a WAV file header structure
            b. A pointer to the WAV file data.
            c. A DWORD which is the length of the data (in bytes, not samples)
*****************************************************************************/
BOOL DSGetWaveResource(HMODULE hModule, LPCTSTR lpName,
                       WAVEFORMATEX **ppWaveHeader, BYTE **ppbWaveData,
                       DWORD *pcbWaveSize)
{
    HRSRC hResInfo;
    HGLOBAL hResData;
    void *pvRes;
    

    if (((hResInfo = FindResource(hModule, lpName, gszWaveString)) != NULL) &&
        ((hResData = LoadResource(hModule, hResInfo)) != NULL) &&
        ((pvRes = LockResource(hResData)) != NULL) &&        
        DSParseWaveResource(pvRes, ppWaveHeader, ppbWaveData, pcbWaveSize))
    {
        return TRUE;
    }
    return FALSE;
}




/*****************************************************************************
FUNCTION:   DSParseWaveResource

PURPOSE:    This does the real meat of the file parsing, and is called by
            DSGetWaveResource
*****************************************************************************/
BOOL DSParseWaveResource(void *pvRes, WAVEFORMATEX **ppWaveHeader,
                         BYTE **ppbWaveData,DWORD *pcbWaveSize)
{
    DWORD *pdw;
    DWORD *pdwEnd;
    DWORD dwRiff;
    DWORD dwType;
    DWORD dwLength;

    if (ppWaveHeader)
        *ppWaveHeader = NULL;

    if (ppbWaveData)
        *ppbWaveData = NULL;

    if (pcbWaveSize)
        *pcbWaveSize = 0;

    pdw = (DWORD *)pvRes;
    dwRiff = *pdw++;
    dwLength = *pdw++;
    dwType = *pdw++;

    if (dwRiff != mmioFOURCC('R', 'I', 'F', 'F'))
        goto exit;      // not even RIFF

    if (dwType != mmioFOURCC('W', 'A', 'V', 'E'))
        goto exit;      // not a WAV

    pdwEnd = (DWORD *)((BYTE *)pdw + dwLength-4);

    while (pdw < pdwEnd)
    {
        dwType = *pdw++;
        dwLength = *pdw++;

        switch (dwType)
        {
        case mmioFOURCC('f', 'm', 't', ' '):
            if (ppWaveHeader && !*ppWaveHeader)
            {
                if (dwLength < sizeof(WAVEFORMAT))
                    goto exit;      // not a WAV

                *ppWaveHeader = (WAVEFORMATEX *)pdw;

                if ((!ppbWaveData || *ppbWaveData) &&
                    (!pcbWaveSize || *pcbWaveSize))
                {
                    return TRUE;
                }
            }
            break;

        case mmioFOURCC('d', 'a', 't', 'a'):
            if ((ppbWaveData && !*ppbWaveData) ||
                (pcbWaveSize && !*pcbWaveSize))
            {
                if (ppbWaveData)
                    *ppbWaveData = (LPBYTE)pdw;

                if (pcbWaveSize)
                    *pcbWaveSize = dwLength;

                if (!ppWaveHeader || *ppWaveHeader)
                    return TRUE;
            }
            break;
        }

        pdw = (DWORD *)((BYTE *)pdw + ((dwLength+1)&~1));
    }

exit:
    return FALSE;
}



/*****************************************************************************
FUNCTION:   DSFillSoundBuffer

PURPOSE:    Given an already-initialized DirectSoundBuffer, and pointer to
            some sound data, and the sound data's size, this writes the data
            to the DirectSoundBuffer.
*****************************************************************************/
BOOL DSFillSoundBuffer(IDirectSoundBuffer *pDSB, BYTE *pbWaveData, DWORD cbWaveSize)
{
    if (pDSB && pbWaveData && cbWaveSize)
    {
        LPVOID pMem1, pMem2;
        DWORD dwSize1, dwSize2;

        if (SUCCEEDED(IDirectSoundBuffer_Lock(pDSB, 0, cbWaveSize,
            &pMem1, &dwSize1, &pMem2, &dwSize2, 0)))
        {
            ZeroMemory(pMem1, dwSize1);
            CopyMemory(pMem1, pbWaveData, dwSize1);

            if ( 0 != dwSize2 )
                CopyMemory(pMem2, pbWaveData+dwSize1, dwSize2);

            IDirectSoundBuffer_Unlock(pDSB, pMem1, dwSize1, pMem2, dwSize2);
            return TRUE;
        }
    }
    return FALSE;
}


/*****************************************************************************
FUNCTION:   DSReloadSoundBuffer

PURPOSE:    If an application with WRITE_PRIMARY takes the focus from our
            humble window, then our secondary sound buffers become "lost" and
            we must call restore and re-fill them.
*****************************************************************************/
BOOL DSReloadSoundBuffer(IDirectSoundBuffer *pDSB, LPCTSTR lpName)
{
    BOOL result=FALSE;
    BYTE *pbWaveData;
    DWORD cbWaveSize;

    if (DSGetWaveResource(NULL, lpName, NULL, &pbWaveData, &cbWaveSize))
    {
        if (SUCCEEDED(IDirectSoundBuffer_Restore(pDSB)))
	    {
        if (DSFillSoundBuffer(pDSB, pbWaveData, cbWaveSize))
            {
	        result = TRUE;
            }
        }

    }
    return result;
}
