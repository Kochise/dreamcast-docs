/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    PlayMultipleSoundsThread.cpp

Abstract:

    This is the thread that handles all of the currently playing sounds.
        
-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "PlayMultipleSounds.hpp"

// ++++ Local Variables +++++++++++++++++++++++++++++++++++++++++++++

// Create an empty sound buffer for each of the mixer's 16 channels.
// When a particular sound is to be played, it's associated sound buffer (NOT
// one of these 16) is duplicated to the first empty CurrentlyPlaying sound
// buffer.  A slightly more optimal implementation of this would be to use
// a linked list rather than a 16-element array.
IDirectSoundBuffer *g_pdsbCurrentlyPlaying[16];

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    PlayingSoundThread

Description:

    This is the background thread function which keeps track of free
    sound buffers for the 'AddSound' function below.  When a sound
    has stopped playing, this thread releases the sound buffer and sets
    the appropriate slot to NULL so that another new sound can use
    the slot.

Arguments:

    int nUnused     -- Necessary variable for thread function, which we don't need

Return Value:

    0

-------------------------------------------------------------------*/
DWORD
PlayingSoundThread(int nUnused)
{
    int  i;
    unsigned long fPlaying;

    // Initialize the empty ("Currently Playing") sound buffers
    for (i = 0; i < 16; i++)
        g_pdsbCurrentlyPlaying[i] = NULL;

    while (TRUE)
    {
        // Loop through all of the "CurrentlyPlaying" buffers - if any of them
        // ARE currently playing (ie non-NULL), then check their status.  If finished,
        // then empty out the buffer
        for (i = 0; i < 16; i++)
        {
            if (g_pdsbCurrentlyPlaying[i] != NULL)
            {
                // This buffer has a sound!  Check if it's finished...
                g_errLast = g_pdsbCurrentlyPlaying[i]->GetStatus(&fPlaying);
                if (CheckError(TEXT("IDirectSoundBuffer::GetStatus")))
                    return 0;

                if (!fPlaying)
                {
                    // The sound has finished - Release it
                    g_pdsbCurrentlyPlaying[i]->Release();

                    // Set it to NULL so that a new sound can be placed in here if necessary.
                    g_pdsbCurrentlyPlaying[i] = NULL;
                }
            }
        }
    }

    // If here, then the app is closing, and this thread should shut down.

    // Release any still-existing sound buffers
    for (i = 0; i < 16; i++)
    {
        fPlaying = TRUE;
        while (fPlaying)
        {
            // Check if it's still playing; if so, wait for it to end.
            g_errLast = g_pdsbCurrentlyPlaying[i]->GetStatus(&fPlaying);
            if (CheckError(TEXT("IDirectSoundBuffer::GetStatus")))
                return 0;
        }

        // Sound is done playing
        g_pdsbCurrentlyPlaying[i]->Release();       
    }
    return 0;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    AddSound

Description:

    Searches the list of sound slots and places this sound in the 
    first empty slot it finds.  If there are no slots, then it does
    not play the sound.  A better (but more complex) approach would
    be to track the priority and origination time of each sound, and
    remove the oldest sound without a high priority.  This can be done
    by using a linked list instead of a 16-element array; add sounds to
    the end of the list as they are requested, and the list will automatically
    be ordered by time; just search for the first one of low enough priority
    and release it.

Arguments:

    IDirectSoundBuffer *pdsb        - Pointer to the sound buffer to play

Return Value:

    TRUE if the sound was added properly and will play, FALSE if either
    an error occurred, or all sound slots are already full.

-------------------------------------------------------------------*/
BOOL
AddSound(IDirectSoundBuffer *pdsb)
{
    int i;

    // Find an empty sound buffer.  If none is found, then don't add the sound.
    for (i = 0; i < 16; i++)
    {
        if (g_pdsbCurrentlyPlaying[i] == NULL)
        {
            IDirectSoundBuffer *pdsbTemp;

            // Found one!  Copy the passed-in DirectSoundBuffer to the empty temporary one
            g_errLast = g_pds->DuplicateSoundBuffer(pdsb, &pdsbTemp);
            if (CheckError(TEXT("Duplicate Sound buffer")))
                return FALSE;

            // Play the test sound
            g_errLast = pdsbTemp->Play(0, 0, 0);
            if (CheckError(TEXT("Play Sound")))
                return 1;

            // Don't set the global DirectSound buffer slot to the new sound *until* it's started
            // playing, otherwise the sound-tracking thread may see that it isn't currently playing
            // *before* we start it playing, and would then assume the sound is done, and delete it,
            // before it ever even got started!
            g_pdsbCurrentlyPlaying[i] = pdsbTemp;

            return TRUE;            
        }
    }

    return FALSE;
}