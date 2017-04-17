/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    PlayMIDI.cpp

Abstract:

    PlayMIDI Application

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "PlayMIDI.hpp"

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++
HINSTANCE g_hinstApp;                     // HINSTANCE of the application

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
    MIDIPROPTIMEDIV mptd;                                    // Time division variables
    HANDLE    hevent;                                        // Event handle used for synchronization with MIDI playback
    UINT imidiOutput, imidiTonebank, imidiTonebankDrum; // MIDI device IDs
    DWORD     imidiCur, imidiMax;                            // MIDI device IDs
    MIDIHDR   mhOutput, mhTonebank, mhTonebankDrum;          // MIDIHDR structures
    HMIDIOUT  hmo, hmoDrum;                                  // MIDI device handles
    HMIDISTRM hms;                                           // MIDI device handle
    WORD      td;                                            // Time division variables
    BYTE      *pbTonebankNew     = NULL;                     // Pointers to new copies of data used
    BYTE      *pbTonebankDrumNew = NULL;                     // Pointers to new copies of data used
	TCHAR     szFilename[MAX_PATH];                          // Command line parsing variables
    BOOL      fFoundOutput       = FALSE;
    BOOL      fFoundTonebank     = FALSE;
    BOOL      fTemp              = TRUE;
    BOOL      fSuccess           = FALSE;
    DWORD     dwAttributes;

    // Remember the application instance handle
    g_hinstApp = hInstance;

    // Initialize the MIDIHDR structures
    memset(&mhOutput, 0, sizeof(mhOutput));
    memset(&mhTonebank, 0, sizeof(mhTonebank));
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
    for (imidiCur = 0; (!fFoundOutput || !fFoundTonebank) && (imidiCur < imidiMax); imidiCur++)
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
            if (!fFoundOutput)
            {
                imidiOutput = imidiCur;
                fFoundOutput = TRUE;
            }
        }
        else
        {
            // If it does, and we still need a tonebank device, remember it
            if (!fFoundTonebank)
            {
                imidiTonebank = imidiCur;
                fFoundTonebank = TRUE;
            }
        }
    }

    // By the time we get here, we should have one of each
    if (!fFoundOutput || !fFoundTonebank)
    {
        RetailOutput(TEXT("Failed to find at least one of the MIDI devices needed"));
        goto done;
    }

    // Open the MIDI device for playing the sequence
    g_errLast = midiStreamOpen(&hms, &imidiOutput, 1, (DWORD)hevent, (DWORD)NULL, CALLBACK_EVENT);
    if (CheckError(TEXT("Open MIDI stream for sequence")))
        goto done;

    // Set the MIDI stream to receive SMF format rather than the Windows default MIDIEVENT format
    g_errLast = midiStreamProperty(hms, (LPBYTE)&fTemp, MIDIPROP_SET | MIDIPROP_SMF);
    if (CheckError(TEXT("Set the SMF property of the MIDI stream")))
        goto done;

    // Set the MIDI stream to map program changes to the General MIDI tonebanks
    g_errLast = midiStreamProperty(hms, (LPBYTE)&fTemp, MIDIPROP_SET | MIDIPROP_GENERALMIDI);
    if (CheckError(TEXT("Set the General MIDI property of the MIDI stream")))
        goto done;

    // Open a tonebank MIDI out port
    g_errLast = midiOutOpen(&hmo, imidiTonebank, (DWORD)NULL, (DWORD)NULL, 0);
    if (CheckError(TEXT("Open MIDI out port for tonebank")))
        goto done;

    // Open a tonebank MIDI out port for the drums
    imidiTonebankDrum = imidiTonebank + 1;
    g_errLast = midiOutOpen(&hmoDrum, imidiTonebankDrum, (DWORD)NULL, (DWORD)NULL, 0);
    if (CheckError(TEXT("Open MIDI out port for drum tonebank")))
        goto done;

    if (*lpCmdLine == NULL)
    {
        // The user must specify a filename
        RetailOutput(TEXT("Error:  Filename not specified.\r\n"));
        RetailOutput(TEXT("File must either be specified with full path, or must reside in\r\n"));
        RetailOutput(TEXT("your <WCEDreamcastSDK>\\release\\(retail,debug)\\Samples directory.\r\n\r\n"));

        RetailOutput(TEXT("Usage:   s PlayMIDI <MIDI filename>\r\n\r\n"));

        RetailOutput(TEXT("Example: s PlayMIDI canyon.mid\r\n"));
        RetailOutput(TEXT("Example: s PlayMIDI \\PC\\Samples\\canyon.mid\r\n"));
        goto done;
    }

    // Get the desired filename from the command line
    lstrcpy(szFilename, lpCmdLine);

    // Check to see if the file is specified using the full path (ie "\windows\test.mpg")
    dwAttributes = GetFileAttributes(szFilename);
    if (dwAttributes == 0xFFFFFFFF || dwAttributes & FILE_ATTRIBUTE_DIRECTORY)
    {
        // The file was not specifies using the full path; check to see if the filename
        // specified exists in the Flat Release directory
        lstrcpy(szFilename, TEXT("\\PC\\Samples\\"));
        lstrcat(szFilename, lpCmdLine);
        dwAttributes = GetFileAttributes(szFilename);
        if (dwAttributes == 0xFFFFFFFF || dwAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            // The file wasn't there either - this sample doesn't support loading from other
            // default directories, so report usage and exit
            RetailOutput(TEXT("Error:  Specified media file (%s) not found.\r\n"), szFilename);
            RetailOutput(TEXT("File must either be specified with full path, or must reside in\r\n"));
            RetailOutput(TEXT("your <WCEDreamcastSDK>\\release\\(retail,debug)\\Samples directory.\r\n\r\n"));

            RetailOutput(TEXT("Usage:   s PlayMIDI <MIDI filename>\r\n\r\n"));

            RetailOutput(TEXT("Example: s PlayMIDI canyon.mid\r\n"));
            RetailOutput(TEXT("Example: s PlayMIDI \\PC\\Samples\\canyon.mid\r\n"));
            goto done;
        }
    }

    // Load the sequence into memory
    memset(&mhOutput, 0, sizeof(mhOutput));
    if (!LoadSequence(szFilename, &mhOutput, &td))
    {
        RetailOutput(TEXT("Failed to load MIDI sequence"));
        goto done;
    }

    // Make sure the time division property of the MIDI stream is set
    mptd.cbStruct = sizeof(mptd);
    mptd.dwTimeDiv = td;
    g_errLast = midiStreamProperty(hms, (LPBYTE)&mptd, MIDIPROP_SET | MIDIPROP_TIMEDIV);
    if (CheckError(TEXT("Set time division property of the MIDI stream")))
        goto done;

    // Load the tonebank into memory
    if (!LoadTonebank(TEXT("test_tonebank"), &mhTonebank))
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

    // Allocate a 32-byte aligned memory block and copy the tonebank to it
    pbTonebankNew = AllocAligned(mhTonebank.dwBufferLength, 32);
    if (pbTonebankNew == NULL)
    {
        RetailOutput(TEXT("Failed to allocate aligned block for tonebank"));
        goto done;
    }
    memcpy(pbTonebankNew, mhTonebank.lpData, mhTonebank.dwBufferLength);
    mhTonebank.lpData = (char*)pbTonebankNew;

    // Allocate a 32-byte aligned memory block and copy the tonebank to it
    pbTonebankDrumNew = AllocAligned(mhTonebankDrum.dwBufferLength, 32);
    if (pbTonebankDrumNew == NULL)
    {
        RetailOutput(TEXT("Failed to allocate aligned block for drum tonebank"));
        goto done;
    }
    memcpy(pbTonebankDrumNew, mhTonebankDrum.lpData, mhTonebankDrum.dwBufferLength);
    mhTonebankDrum.lpData = (char*)pbTonebankDrumNew;

    // Copy MIDI sequence to sound RAM
    g_errLast = midiOutPrepareHeader((HMIDIOUT)hms, &mhOutput, sizeof(mhOutput));
    if (CheckError(TEXT("Prepare MIDIHDR for MIDI sequence")))
        goto done;

    // Don't try this on the desktop!  It only works on Dreamcast because
    // after the header's been prepared, the sequence data has been copied
    // to the sound RAM and the system RAM copy is no longer needed.
    FreeSequence((BYTE*)mhOutput.lpData);

    // Copy tonebank to sound RAM
    g_errLast = midiOutPrepareHeader(hmo, &mhTonebank, sizeof(mhTonebank));
    if (CheckError(TEXT("Prepare MIDIHDR for tonebank")))
        goto done;

    // Copy drum tonebank to sound RAM
    g_errLast = midiOutPrepareHeader(hmoDrum, &mhTonebankDrum, sizeof(mhTonebankDrum));
    if (CheckError(TEXT("Prepare MIDIHDR for drum tonebank")))
        goto done;

    // Set tonebank
    mhTonebank.dwFlags |= MHDR_GENERALMIDI;
    g_errLast = midiOutLongMsg(hmo, &mhTonebank, sizeof(mhTonebank));
    if (CheckError(TEXT("Select tonebank")))
        goto done;

    // Set drum tonebank
    mhTonebankDrum.dwFlags |= (MHDR_GENERALMIDI | MHDR_GMDRUM);
    g_errLast = midiOutLongMsg(hmoDrum, &mhTonebankDrum, sizeof(mhTonebankDrum));
    if (CheckError(TEXT("Select drum tonebank")))
        goto done;

    // Get the MIDI sequence into the playback queue
    g_errLast = midiStreamOut(hms, &mhOutput, sizeof(mhOutput));
    if (CheckError(TEXT("Queue up playback of MIDI sequence")))
        goto done;

    // Start the MIDI stream (this is where the MIDI actually starts playing)
    // NOTE: You can restart the stream before calling midiStreamOut.  Either way works fine
    g_errLast = midiStreamRestart(hms);
    if (CheckError(TEXT("Restart MIDI stream")))
        goto done;

    RetailOutput(TEXT("Playing \"%s\""), szFilename);

    // Wait until the MIDI sequence has finished playing
    while (!(mhOutput.dwFlags & MHDR_DONE))
    {
        WaitForSingleObject(hevent, INFINITE);
    }

done:

    // Clean up
    if (hmo != NULL)
    {
        // Unprepare header; this frees up the audio RAM used by the tonebank
        if (mhTonebank.dwFlags & MHDR_PREPARED)
        {
            g_errLast = midiOutUnprepareHeader(hmo, &mhTonebank, sizeof(mhTonebank));
            if (CheckError(TEXT("unprepare tonebank MIDIHDR")))
                return 1;
        }

        // If we allocated a new block of RAM for the tonebank, free it
        if (pbTonebankNew != NULL)
            FreeAligned(pbTonebankNew);

        // Close the MIDI out port.  This is very important; if all ports are not closed before 
        // the program exits, no other Dreamcast program will be able to use *any* audio
        g_errLast = midiOutClose(hmo);
        if (CheckError(TEXT("Close Drum tonebank MIDI port")))
            return 1;
    }

    if (hmoDrum != NULL)
    {
        // Unprepare header; this frees up the audio RAM used by the tonebank
        if (mhTonebankDrum.dwFlags & MHDR_PREPARED)
        {
            g_errLast = midiOutUnprepareHeader(hmoDrum, &mhTonebankDrum, sizeof(mhTonebankDrum));
            if (CheckError(TEXT("unprepare Drum tonebank MIDIHDR")))
                return 1;
        }

        // If we allocated a new block of RAM for the tonebank, free it
        if (pbTonebankDrumNew != NULL)
            FreeAligned(pbTonebankDrumNew);

        // Close the MIDI stream port.  See warning above about what happens if
        // all the ports that have been opened are not closed before program exit
        g_errLast = midiOutClose(hmoDrum);
        if (CheckError(TEXT("Close Drum tonebank MIDI port")))
            return 1;
    }

    if (hms != NULL)
    {
        // Unprepare header; this frees up the audio RAM used by the sequence
        if (mhOutput.dwFlags & MHDR_PREPARED)
        {
            g_errLast = midiOutUnprepareHeader((HMIDIOUT)hms, &mhOutput, sizeof(mhOutput));
            if (CheckError(TEXT("Unprepare MIDI Sequence MIDIHDR")))
                return 1;
        }

        // Close the MIDI stream port.  See warning above about what happens if all
        // the ports that have been opened are not closed before program exit
        g_errLast = midiStreamClose(hms);
        if (CheckError(TEXT("Close MIDI Stream port")))
            return 1;
    }

    // Free the event handle used to synchronize with MIDI playback
    CloseHandle(hevent);

    RetailOutput(TEXT("\r\nApp exited...\r\n"));

    return 1;
}
