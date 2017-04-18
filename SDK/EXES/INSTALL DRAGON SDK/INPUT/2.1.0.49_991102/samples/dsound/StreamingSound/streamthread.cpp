/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    StreamThread.cpp

Abstract:

    This is the thread that handles all of the currently playing sounds.
        
-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "StreamingSound.hpp"

BOOL g_fDonePlaying = FALSE;                // Set to TRUE to indicate completion of sound.

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    StreamThread

Description:

    This is the background thread function which streams the current
    background sound.

Arguments:

    int nUnused     -- Necessary variable for thread function, which we don't need

Return Value:

    0

-------------------------------------------------------------------*/
DWORD
StreamThread(int nUnused)
{
    DWORD fPlaying;
    BYTE  bySilence = 0x80;
    BOOL  fSilence = FALSE;
    BYTE  *pbyBlock1;
    BYTE  *pbyBlock2;
    DWORD ibRead, ibWrite, cbToLock = BUFFERSIZE/2, cbRead;
    DWORD nBytes1, nBytes2;

    while (TRUE)
    {
        // Check if there is a sound to play in the background (streamed).
        if (g_fPlayBackgroundSound)
        {
            // The background sound buffer (g_pdsbBackground) is a 1 second long buffer.
            // It works by playing 500 ms of sound while loading the other 500 ms, and
            // then swapping sides.  As such, we will wait here until one of the sound
            // buffer's predefined events (hit halfway mark, hit end of buffer) occurs.
            WaitForSingleObject(g_hSoundNotifyEvent, INFINITE);
            
            if (g_fExiting)
            {
                // Tell the sound to stop
                if (g_pdsbBackground)
                    g_pdsbBackground->Stop();

                // The sound has stopped playing.  Set the appropriate event so that the
                // app can tell it's actually done
                SetEvent(g_hSoundDoneEvent);

                // Break out of this while() loop and exit the thread.
                break;
            }

            // Check to see if it's current state is "playing"
            g_errLast = g_pdsbBackground->GetStatus(&fPlaying);
            if (CheckError(TEXT("IDirectSoundBuffer::GetStatus")))
                return 0;

            if (fPlaying)
            {
                // Find out where we currently are playing, and where we last wrote
                g_errLast = g_pdsbBackground->GetCurrentPosition(&ibRead, &ibWrite);
                if (CheckError(TEXT("IDirectSoundBuffer::GetCurrentPosition")))
                    return 0;
        
                // Lock the next half of the sound buffer
                g_errLast = g_pdsbBackground->Lock(ibWrite, cbToLock, (void **)&pbyBlock1, 
                                                   &nBytes1, (void **)&pbyBlock2, &nBytes2, 0);
                if (CheckError(TEXT("IDirectSoundBuffer::Lock")))
                    return 0;

                // fSilence is true if we hit the end of the sound file on the
                // last pass through here.  In that case, fill both blocks with "silence"
                // and stop the sound from playing.
                if (fSilence)
                {
                    memset(pbyBlock1, bySilence, nBytes1);
                    memset(pbyBlock2, bySilence, nBytes2);

                    // After filling it, stop playing
                    g_errLast = g_pdsbBackground->Stop();
                }
                else
                {
                    // Read the next chunk of bits from the sound file
                    ReadFile(g_hSoundFile, pbyBlock1, nBytes1, &cbRead, NULL);
                    if (nBytes1 != cbRead)
                    {
                        // The file has less data than the size of the first block, so fill the
                        // remainder with silence - also fill the second block with silence
                        memset(pbyBlock1 + cbRead, bySilence, nBytes1 - cbRead);
                        memset(pbyBlock2, bySilence, nBytes2);

                        // Next time through, just play silence.
                        fSilence = TRUE;
                    }
                    else
                    {
                        // If there is a second block, then read more of the sound file into that block.
                        if (nBytes2)
                        {
                            ReadFile(g_hSoundFile, pbyBlock2, nBytes2, &cbRead, NULL);
                            if (nBytes2 != cbRead)
                            {
                                // The file has less data than the size of the second block, so
                                // fill the remainder with silence.
                                memset(pbyBlock2 + cbRead, bySilence, nBytes2 - cbRead);

                                // next time through, just play silence
                                fSilence = TRUE;
                            }
                        }
                    }
                }

                // Done with the sound buffer, so unlock it.
                g_errLast = g_pdsbBackground->Unlock(pbyBlock1, nBytes1, pbyBlock2, nBytes2);
                if (CheckError(TEXT("IDirectSoundBuffer::Unlock")))
                    return 0;
            }
            else
            {
                // The sound has stopped playing.  Set the appropriate event so that the
                // app can tell it's actually done
                SetEvent(g_hSoundDoneEvent);
                g_fDonePlaying = TRUE;
            }
        }
        else
        {
            // App doesn't have a sound to play - don't do anything
        }
    }
    return 0;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    WaitUntilSoundDone

Description:

    Blocks until the background sound's "Done" event triggers; at that
    point we return.

Arguments:

    None

Return Value:

    None

-------------------------------------------------------------------*/
void
WaitUntilSoundDone()
{
    // Sit back and wait until the StreamingThread function has finished playing the background
    // sound - at that point, this event will get set.
    WaitForSingleObject(g_hSoundDoneEvent, INFINITE );
}
