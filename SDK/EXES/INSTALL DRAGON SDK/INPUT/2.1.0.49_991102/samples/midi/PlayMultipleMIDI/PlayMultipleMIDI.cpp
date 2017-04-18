/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    PlayMultipleMIDI.cpp

Abstract:

    PlayMultipleMIDI Sample Application - shows how to play multiple
    MIDI files simultaneously

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "PlayMultipleMIDI.hpp"

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++
HINSTANCE g_hinstApp;                     // HINSTANCE of the application

// A sequence of time-stamped MIDI bytes to set all instrument banks
// on all channels to bank 0.  These are simply a series of channel
// bank select controller messages to set the bank MSB and LSB to 0

// NOTE: eventually, Dreamcast tonebanks should support the use of a
// mapping table to allow arbitrary bank/program assignments of instruments
// in a tonebank.  If and when that happens, this will not be necessary.
// A mapping table will be loaded along with the tonebank instead.
BYTE g_rgbInitTonebank[] =
{
	0x00, 0xb0, 0x20, 0x00, 0x00, 0xb1, 0x20, 0x00,
	0x00, 0xb2, 0x20, 0x00, 0x00, 0xb3, 0x20, 0x00,
	0x00, 0xb4, 0x20, 0x00, 0x00, 0xb5, 0x20, 0x00,
	0x00, 0xb6, 0x20, 0x00, 0x00, 0xb7, 0x20, 0x00,
	0x00, 0xb8, 0x20, 0x00, 0x00, 0xb9, 0x20, 0x01,
	0x00, 0xba, 0x20, 0x00, 0x00, 0xbb, 0x20, 0x00,
	0x00, 0xbc, 0x20, 0x00, 0x00, 0xbd, 0x20, 0x00,
	0x00, 0xbe, 0x20, 0x00, 0x00, 0xbf, 0x20, 0x00,
};

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    WinMain

Description:

    This is the entrypoint for this sample app.

Arguments:

    hInstance           - HInstance of the process

    hPrev               - HInstance of another process running the program

    LPTSTR lpCmdLine    - Pointer to command line string

    nCmdShow            - Whether the app should be shown (ignored)

Return Value:

    We normally return the wParam value from the WM_QUIT message.  If
    there's a failure upon initialization, we just return 0.

-------------------------------------------------------------------*/
extern "C" int APIENTRY 
WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    MIDIPROPTIMEDIV mptd;                            // Time division variables
    HANDLE    hevent;                                // Event handle used for synchronization with MIDI playback
    UINT      imidiOutput1, imidiOutput2;            // MIDI device IDs
    UINT      imidiTonebank1, imidiTonebank2;        // MIDI device IDs
    DWORD     imidiCur, imidiMax;                    // MIDI device IDs
    MIDIHDR   mhOutput1, mhOutput2;                  // MIDIHDR structures
    MIDIHDR   mhTonebankMelodic, mhTonebankDrum;     // MIDIHDR structures
    HMIDIOUT  hmo1, hmo2;                            // MIDI device handles
    HMIDISTRM hms1, hms2;                            // MIDI device handle
    WORD      td1, td2;                              // Time division variables
    BYTE      *pbSequence1New    = NULL;             // Pointers to new copies of data used
    BYTE      *pbSequence2New    = NULL;             // Pointers to new copies of data used
    BYTE      *pbTonebankMelodicNew = NULL;          // Pointers to new copies of data used
    BYTE      *pbTonebankDrumNew = NULL;             // Pointers to new copies of data used
    BOOL      fFoundOutput1      = FALSE;
    BOOL      fFoundOutput2      = FALSE;
    BOOL      fFoundTonebank1    = FALSE;
    BOOL      fSMF               = TRUE;
    BOOL      fFoundTonebank2    = FALSE;
    BOOL      fTemp              = TRUE;
    BOOL      fSuccess           = FALSE;
    DWORD     tickCur, tickStop;
    BOOL      fDone1 = FALSE, fDone2 = FALSE;

    // Remember the application instance handle
    g_hinstApp = hInstance;

    // Initialize the MIDIHDR structures
    memset(&mhOutput1, 0, sizeof(mhOutput1));
    memset(&mhOutput2, 0, sizeof(mhOutput2));
    memset(&mhTonebankMelodic, 0, sizeof(mhTonebankMelodic));
    memset(&mhTonebankDrum, 0, sizeof(mhTonebankDrum));

    // Create the event handle used for synchronization with MIDI playback
    hevent = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (hevent == NULL)
    {
        RetailOutput(TEXT("Couldn't create the event handle"));
        goto done;
    }

    // Query the MIDI subsystem for the number of MIDI devices
    // NOTE: On Dreamcast, this will always be 32 -- 16 sequencing devices, and
    //       16 devices used to manage the tonebank slots
    imidiMax = midiOutGetNumDevs();
    if (imidiMax == 0)
    {
        RetailOutput(TEXT("No devices found on system"));
        goto done;
    }

    // Enumerate the devices, finding the first sequencing device and the first tonebank device
    for (imidiCur = 0; (!fFoundOutput1 || !fFoundOutput2 || !fFoundTonebank1 || !fFoundTonebank2) &&
                       (imidiCur < imidiMax); imidiCur++)
    {
        MIDIOUTCAPS moc;

        // Query the MIDI subsystem for the device capabilities
        g_errLast = midiOutGetDevCaps(imidiCur, &moc, sizeof(moc));
        if (CheckError(TEXT("Get Device Capabilities")))
            goto done;

        // Check to see if this device understands MIDI sequences
        if (moc.dwSupport & MIDICAPS_STREAM)
        {
            // If it does, and we still need one of those, remember it
            if (!fFoundOutput1)
            {
                imidiOutput1  = imidiCur;
                fFoundOutput1 = TRUE;
            }
            else if (!fFoundOutput2)
            {
                imidiOutput2  = imidiCur;
                fFoundOutput2 = TRUE;
            }
        }
        else
        {
            // If it does, and we still need a tonebank device, remember it
            if (!fFoundTonebank1)
            {
                imidiTonebank1  = imidiCur;
                fFoundTonebank1 = TRUE;
            }
            else if (!fFoundTonebank2)
            {
                imidiTonebank2  = imidiCur;
                fFoundTonebank2 = TRUE;
            }
        }
    }

    // By the time we get here, we should have one of each
    if (!fFoundOutput1 || !fFoundOutput2 || !fFoundTonebank1 || !fFoundTonebank2)
    {
        RetailOutput(TEXT("Failed to find at least one of the MIDI devices needed"));
        goto done;
    }

    // Open the MIDI device for playing the first sequence
    g_errLast = midiStreamOpen(&hms1, &imidiOutput1, 1, (DWORD)hevent, (DWORD)NULL, CALLBACK_EVENT);
    if (CheckError(TEXT("Open MIDI stream for sequence")))
        goto done;

    // Open the MIDI device for playing the second sequence
    g_errLast = midiStreamOpen(&hms2, &imidiOutput2, 1, (DWORD)hevent, (DWORD)NULL, CALLBACK_EVENT);
    if (CheckError(TEXT("Open MIDI stream for sequence")))
        goto done;

    // Set the MIDI stream to receive SMF format rather than the Windows default MIDIEVENT format
    g_errLast = midiStreamProperty(hms1, (LPBYTE)&fSMF, MIDIPROP_SET | MIDIPROP_SMF);
    if (CheckError(TEXT("Set the SMF property of the MIDI stream")))
        goto done;

    g_errLast = midiStreamProperty(hms2, (LPBYTE)&fSMF, MIDIPROP_SET | MIDIPROP_SMF);
    if (CheckError(TEXT("Set the SMF property of the MIDI stream")))
        goto done;

    // Open a tonebank MIDI out port for the melodic instruments
    g_errLast = midiOutOpen(&hmo1, imidiTonebank1, (DWORD)NULL, (DWORD)NULL, 0);
    if (CheckError(TEXT("Open MIDI out port for tonebank")))
        goto done;

    // Open a tonebank MIDI out port for the drum instruments
    g_errLast = midiOutOpen(&hmo2, imidiTonebank2, (DWORD)NULL, (DWORD)NULL, 0);
    if (CheckError(TEXT("Open MIDI out port for drum tonebank")))
        goto done;

    // Load the first sequence into memory
    if (!LoadSequence(TEXT("test_sequence"), &mhOutput1, &td1))
    {
        RetailOutput(TEXT("Failed to load MIDI sequence"));
        goto done;
    }

    // Load the second sequence into memory
    if (!LoadSequence(TEXT("test_sequence2"), &mhOutput2, &td2))
    {
        RetailOutput(TEXT("Failed to load MIDI sequence"));
        goto done;
    }

    // Make sure the time division property of the MIDI streams is set
    mptd.cbStruct = sizeof(mptd);
    mptd.dwTimeDiv = td1;
    g_errLast = midiStreamProperty(hms1, (LPBYTE)&mptd, MIDIPROP_SET | MIDIPROP_TIMEDIV);
    if (CheckError(TEXT("Set time division property of the MIDI stream")))
        goto done;

    mptd.dwTimeDiv = td2;
    g_errLast = midiStreamProperty(hms2, (LPBYTE)&mptd, MIDIPROP_SET | MIDIPROP_TIMEDIV);
    if (CheckError(TEXT("Set time division property of the MIDI stream")))
        goto done;

    // Load the melodic instrument tonebank into memory
    if (!LoadTonebank(TEXT("test_tonebank"), &mhTonebankMelodic))
    {
        RetailOutput(TEXT("Failed to load the tonebank"));
        goto done;
    }

    // Load the drum tonebank into memory
    if (!LoadTonebank(TEXT("test_drums"), &mhTonebankDrum))
    {
        RetailOutput(TEXT("Failed to load the drum tonebank"));
        goto done;
    }

    // Convert to 32-byte aligned, so that it can be DMA'ed.  Note that in real life, this 
    // may not gain you anything.  That is, if you've already got a perfectly good pointer
    // to your tonebank data that you could use, you might waste more time aligning it,
    // preparing for DMA'ing, and then going through the thread blocking and switching so
    // that something else can run.  This is especially true for smaller blocks, but might
    // even be true for large ones.  Don't assume DMA will always win.  It is done here
    // simply to demonstrate one way to ensure that DMA is being used

    // For both tonebanks, Allocate a 32-byte aligned memory block and copy the tonebank to it
    pbTonebankMelodicNew = AllocAligned(mhTonebankMelodic.dwBufferLength, 32);
    if (pbTonebankMelodicNew == NULL)
    {
        RetailOutput(TEXT("Failed to allocate aligned block for tonebank"));
        goto done;
    }
    memcpy(pbTonebankMelodicNew, mhTonebankMelodic.lpData, mhTonebankMelodic.dwBufferLength);
    mhTonebankMelodic.lpData = (char*)pbTonebankMelodicNew;

    // Allocate a 32-byte aligned memory block and copy the tonebank to it
    pbTonebankDrumNew = AllocAligned(mhTonebankDrum.dwBufferLength, 32);
    if (pbTonebankDrumNew == NULL)
    {
        RetailOutput(TEXT("Failed to allocate aligned block for drum tonebank"));
        goto done;
    }
    memcpy(pbTonebankDrumNew, mhTonebankDrum.lpData, mhTonebankDrum.dwBufferLength);
    mhTonebankDrum.lpData = (char*)pbTonebankDrumNew;
    
    // For both sequences, allocate a 32-byte aligned memory block into which
    // our modified MIDI sequence can be kept
    pbSequence1New = AllocAligned(mhOutput1.dwBufferLength + sizeof(g_rgbInitTonebank), 32);
    if (pbSequence1New == NULL)
    {
        RetailOutput(TEXT("Failed to allocate aligned block for first MIDI sequence"));
        goto done;
    }
    memcpy(pbSequence1New, g_rgbInitTonebank, sizeof(g_rgbInitTonebank));
    memcpy(pbSequence1New + sizeof(g_rgbInitTonebank), mhOutput1.lpData, mhOutput1.dwBufferLength);
    mhOutput1.lpData = (char*)pbSequence1New;
    mhOutput1.dwBufferLength += sizeof(g_rgbInitTonebank);

    pbSequence2New = AllocAligned(mhOutput2.dwBufferLength + sizeof(g_rgbInitTonebank), 32);
    if (pbSequence2New == NULL)
    {
        RetailOutput(TEXT("Failed to allocate aligned block for second MIDI sequence"));
        goto done;
    }
    memcpy(pbSequence2New, g_rgbInitTonebank, sizeof(g_rgbInitTonebank));
    memcpy(pbSequence2New + sizeof(g_rgbInitTonebank), mhOutput2.lpData, mhOutput2.dwBufferLength);
    mhOutput2.lpData = (char*)pbSequence2New;
    mhOutput2.dwBufferLength += sizeof(g_rgbInitTonebank);

    // Copy MIDI sequences to sound RAM
    g_errLast = midiOutPrepareHeader((HMIDIOUT)hms1, &mhOutput1, sizeof(mhOutput1));
    if (CheckError(TEXT("Prepare MIDIHDR for first MIDI sequence")))
        goto done;

    g_errLast = midiOutPrepareHeader((HMIDIOUT)hms2, &mhOutput2, sizeof(mhOutput2));
    if (CheckError(TEXT("Prepare MIDIHDR for second MIDI sequence")))
        goto done;

    // Copy tonebanks to sound RAM
    g_errLast = midiOutPrepareHeader(hmo1, &mhTonebankMelodic, sizeof(mhTonebankMelodic));
    if (CheckError(TEXT("Prepare MIDIHDR for melodic tonebank")))
        goto done;

    g_errLast = midiOutPrepareHeader(hmo2, &mhTonebankDrum, sizeof(mhTonebankDrum));
    if (CheckError(TEXT("Prepare MIDIHDR for drum tonebank")))
        goto done;

    // Set tonebank
    g_errLast = midiOutLongMsg(hmo1, &mhTonebankMelodic, sizeof(mhTonebankMelodic));
    if (CheckError(TEXT("Select melodic tonebank")))
        goto done;

    g_errLast = midiOutLongMsg(hmo2, &mhTonebankDrum, sizeof(mhTonebankDrum));
    if (CheckError(TEXT("Select drum tonebank")))
        goto done;

    // Get the MIDI sequences into the playback queues
    g_errLast = midiStreamOut(hms1, &mhOutput1, sizeof(mhOutput1));
    if (CheckError(TEXT("Queue up playback of first MIDI sequence")))
        goto done;
    
    g_errLast = midiStreamOut(hms2, &mhOutput2, sizeof(mhOutput2));
    if (CheckError(TEXT("Queue up playback of second MIDI sequence")))
        goto done;

    // Start the MIDI streams (this is where the MIDI actually starts playing)
    // NOTE: You can restart the stream before calling midiStreamOut.  Either way works fine
    g_errLast = midiStreamRestart(hms2);
    if (CheckError(TEXT("Restart second MIDI stream")))
        goto done;

    g_errLast = midiStreamRestart(hms1);
    if (CheckError(TEXT("Restart first MIDI stream")))
        goto done;

    // Wait until the MIDI sequences have finished playing or 3 minutes have gone by
    tickCur  = GetTickCount();
    tickStop = tickCur + 180000;
    while (!(fDone1 && fDone2) && (tickCur < tickStop))
    {
        MMTIME mmtime;

        // Wait for somthing to happen
        WaitForSingleObject(hevent, 15000);

        RetailOutput(TEXT("MIDI event signaled"));
        if (!fDone1 && mhOutput1.dwFlags & MHDR_DONE)
        {
            RetailOutput(TEXT("    First MIDI sequence completed"));
            fDone1 = TRUE;
        }
        if (!fDone2 && mhOutput2.dwFlags & MHDR_DONE)
        {
            RetailOutput(TEXT("    Second MIDI sequence completed"));
            fDone2 = TRUE;
        }

        mmtime.wType = TIME_BYTES;
        if (midiStreamPosition(hms1, &mmtime, sizeof(mmtime)) == MMSYSERR_NOERROR)
        {
            if (mmtime.wType == TIME_BYTES)
                RetailOutput(TEXT("Current position of first sequence: byte %08x\r\n"), mmtime.u.cb);
            else
                RetailOutput(TEXT("midiStreamPosition(hms1...) didn't return bytes\r\n"));
        }
        else
            RetailOutput(TEXT("midiStreamPosition(hms1...) failed!\r\n"));

        mmtime.wType = TIME_BYTES;
        if (midiStreamPosition(hms2, &mmtime, sizeof(mmtime)) == MMSYSERR_NOERROR)
        {
            if (mmtime.wType == TIME_BYTES)
                RetailOutput(TEXT("Current position of second sequence: byte %08x"), mmtime.u.cb);
            else
                RetailOutput(TEXT("midiStreamPosition(hms2...) didn't return bytes"));
        }
        else
            RetailOutput(TEXT("midiStreamPosition(hms2...) failed!"));

        tickCur = GetTickCount();
    }
    RetailOutput(TEXT("Done waiting for MIDI sequences"));
    if (!fDone1 || !fDone2)
        RetailOutput(TEXT("Didn't receive completion notification for all sequences"));


    // If we get this far, everything went perfectly
    fSuccess = TRUE;

done:

    // Clean up
    if (hmo1 != NULL)
    {
        // Unprepare header; this frees up the audio RAM used by the tonebank
        if (mhTonebankMelodic.dwFlags & MHDR_PREPARED)
        {
            g_errLast = midiOutUnprepareHeader(hmo1,
            &mhTonebankMelodic, sizeof(mhTonebankMelodic));
            if (g_errLast != MMSYSERR_NOERROR)
                RetailOutput(TEXT("Failed to unprepare melodic tonebank MIDIHDR"));
        }

        // If we allocated a new block of RAM for the tonebank, free it
        if (pbTonebankMelodicNew != NULL)
            FreeAligned(pbTonebankMelodicNew);

        // Close the MIDI out port.  This is very important; if all ports are not closed before
        // the program exits, no other Dreamcast program will be able to use *any* audio
        g_errLast = midiOutClose(hmo1);
        if (g_errLast != MMSYSERR_NOERROR)
            RetailOutput(TEXT("Failed to close tonebank MIDI port"));
    }

    if (hmo2 != NULL)
    {
        // Unprepare header; this frees up the audio RAM used by the tonebank
        if (mhTonebankDrum.dwFlags & MHDR_PREPARED)
        {
            g_errLast = midiOutUnprepareHeader(hmo2,
            &mhTonebankDrum, sizeof(mhTonebankDrum));
            if (g_errLast != MMSYSERR_NOERROR)
                RetailOutput(TEXT("Failed to unprepare drum tonebank MIDIHDR"));
        }

        // If we allocated a new block of RAM for the tonebank, free it
        if (pbTonebankDrumNew != NULL)
            FreeAligned(pbTonebankDrumNew);

        // Close the MIDI out port.  This is very important; if all ports are not closed before
        // the program exits, no other Dreamcast program will be able to use *any* audio
        g_errLast = midiOutClose(hmo2);
        if (g_errLast != MMSYSERR_NOERROR)
            RetailOutput(TEXT("Failed to close drum tonebank MIDI port"));
    }

    if (hms1 != NULL)
    {
        // Unprepare header; this frees up the audio RAM used by the sequence
        if (mhOutput1.dwFlags & MHDR_PREPARED)
        {
            if (!(mhOutput1.dwFlags & MHDR_DONE))
            {
                g_errLast = midiStreamStop(hms1);
                if (g_errLast != MMSYSERR_NOERROR)
                    RetailOutput(TEXT("First MIDI sequence not done yet, and couldn't stop it\r\n"));
            }
            g_errLast = midiOutUnprepareHeader((HMIDIOUT)hms1,
            &mhOutput1, sizeof(mhOutput1));
            if (g_errLast != MMSYSERR_NOERROR)
                RetailOutput(TEXT("Failed to unprepare first MIDI sequence MIDIHDR"));
        }

        // If we allocated a new block of RAM for the sequence, free it
        if (pbSequence1New != NULL)
            FreeAligned(pbSequence1New);

        // Close the MIDI stream port.  See warning above about what happens if all
        // the ports that have been opened are not closed before program exit
        g_errLast = midiStreamClose(hms1);
        if (g_errLast != MMSYSERR_NOERROR)
            RetailOutput(TEXT("Failed to close first MIDI stream port"));
    }

    if (hms2 != NULL)
    {
        // Unprepare header; this frees up the audio RAM used by the sequence
        if (mhOutput2.dwFlags & MHDR_PREPARED)
        {
            if (!(mhOutput2.dwFlags & MHDR_DONE))
            {
                g_errLast = midiStreamStop(hms2);
                if (g_errLast != MMSYSERR_NOERROR)
                    RetailOutput(TEXT("second MIDI sequence not done yet, and couldn't stop it\r\n"));
            }
            g_errLast = midiOutUnprepareHeader((HMIDIOUT)hms2,
            &mhOutput2, sizeof(mhOutput2));
            if (g_errLast != MMSYSERR_NOERROR)
                RetailOutput(TEXT("Failed to unprepare second MIDI sequence MIDIHDR"));
        }

        // If we allocated a new block of RAM for the sequence, free it
        if (pbSequence2New != NULL)
            FreeAligned(pbSequence2New);

        // Close the MIDI stream port.  See warning above about what happens if all
        // the ports that have been opened are not closed before program exit
        g_errLast = midiStreamClose(hms2);
        if (g_errLast != MMSYSERR_NOERROR)
            RetailOutput(TEXT("Failed to close second MIDI stream port"));
    }

    /* Free the event handle used to synchronize with MIDI playback */
    CloseHandle(hevent);

    RetailOutput(TEXT("\r\nApp exited...\r\n"));

    return 1;
}
