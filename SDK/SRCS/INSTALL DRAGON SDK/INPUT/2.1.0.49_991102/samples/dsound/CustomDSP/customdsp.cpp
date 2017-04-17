/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    CustomDSP.cpp

Abstract:

    CustomDSP Application

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "CustomDSP.hpp"

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++
HWND      g_hwndApp;                                // HWND of the application
HINSTANCE g_hinst;                                  // HINSTANCE of the application

// ++++ Local Variables +++++++++++++++++++++++++++++++++++++++++++++
LPDIRECTSOUNDBUFFER g_pdsbToPlay;

// ++++ Local Functions +++++++++++++++++++++++++++++++++++++++++++++
BOOL SetMixerSettings();
BOOL ChangeDSPSettings(LPTSTR lpEffect);

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    CleanUp

Description:

    Cleans up after the application is done.  Frees allocated memory

Arguments:

    None
  
Return Value:

    None

-------------------------------------------------------------------*/
void
CleanUp()
{
    if (g_pdsbToPlay)
        g_pdsbToPlay->Release();

    if (g_pds)
        g_pds->Release();
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    WinMain

Description:

    This is the entrypoint for this sample app.  Load the specified
    sound file and play it.

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
    int   i;
    TCHAR szFile[MAX_PATH], szEffect[MAX_PATH], *pTok;
    DWORD dwAttributes;

    // Store Instance handle for use later...
    g_hinst = hInstance;

    // Set g_hwndApp to NULL so that we can properly set the DirectSound
    // CooperativeLevel in InitDirectSound.  A normal application would
    // set g_hwndApp to the HWND of the window that the app renders into
    g_hwndApp = NULL;

    // Initialize DirectSound
    if (!InitDirectSound())
    {
        RetailOutput(TEXT("Unable to Initialize DirectSound\r\n"));
        return 1;
    }

	pTok = _tcstok(lpCmdLine, TEXT(" "));

	if(pTok != NULL) {
		lstrcpy(szFile, pTok);

	    dwAttributes = GetFileAttributes(szFile);
		if (dwAttributes == 0xFFFFFFFF || dwAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			// The file was not specified using the full path; check to see if the filename
			// specified exists in the Flat Release directory
			lstrcpy(szFile, TEXT("\\PC\\Samples\\"));
			lstrcat(szFile, pTok);

		    dwAttributes = GetFileAttributes(szFile);
			if (dwAttributes == 0xFFFFFFFF || dwAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				// The file wasn't there either - this sample doesn't support loading from other
				// default directories, so report usage and exit
				pTok = NULL;
			}
			else {
				pTok = _tcstok(NULL, TEXT(" "));
			}
		}
		else {
			pTok = _tcstok(NULL, TEXT(" "));
		}

		if(pTok != NULL) {
			lstrcpy(szEffect, pTok);

			dwAttributes = GetFileAttributes(szEffect);
			if (dwAttributes == 0xFFFFFFFF || dwAttributes & FILE_ATTRIBUTE_DIRECTORY) {
				// The file was not specified using the full path; check to see if the filename
				// specified exists in the Flat Release directory
				lstrcpy(szEffect, TEXT("\\PC\\Samples\\"));
				lstrcat(szEffect, pTok);

				dwAttributes = GetFileAttributes(szEffect);
				if (dwAttributes == 0xFFFFFFFF || dwAttributes & FILE_ATTRIBUTE_DIRECTORY) {
					// The file wasn't there either - this sample doesn't support loading from other
					// default directories, so report usage and exit
					pTok = NULL;
				}
			}
		}
	}

    // If necessary, report usage and exit
    if (pTok == NULL)
    {
        RetailOutput(TEXT("Error:  Filename not specified.\r\n"));
        RetailOutput(TEXT("File must either be specified with full path, or must reside in\r\n"));
        RetailOutput(TEXT("your <WCEDreamcastSDK>\\release\\(retail,debug)\\Samples directory.\r\n\r\n"));

        RetailOutput(TEXT("Usage:   s CustomDSP <WAV filename> <DSP filename>\r\n\r\n"));

        RetailOutput(TEXT("Example: s CustomDSP jump.wav q_tunnel.fpb\r\n"));
        RetailOutput(TEXT("Example: s CustomDSP \\PC\\Samples\\jump.wav \\PC\\Samples\\q_tunnel.fpb\r\n"));
        goto done;
    }
    
    // Load the specified sound
    g_pdsbToPlay = LoadSoundBuffer(szFile);
    if (!g_pdsbToPlay)
    {
        RetailOutput(TEXT("Unable to load wave file\r\n"));
        goto done;
    }

    // Play the sound twice without the custom DSP settings
    for (i = 0; i < 2; i++)
    {
        // Rewind the test sound (necessary?)
        g_pdsbToPlay->SetCurrentPosition(0);

        // Play the test sound
        g_errLast = g_pdsbToPlay->Play(0, 0, 0);
        if (CheckError(TEXT("Play Sound")))
            goto done;

        // Sleep for a second to let the sound finish playing
        Sleep(1000);
    }

    // Now play the sound twice with the custom DSP settings for comparison

    // Enable CustomDSP
    ChangeDSPSettings(szEffect);
    SetMixerSettings();

    for (i = 0; i < 2; i++)
    {
        // Rewind the test sound (necessary?)
        g_pdsbToPlay->SetCurrentPosition(0);

        // Play the test sound
        g_errLast = g_pdsbToPlay->Play(0, 0, 0);
        if (CheckError(TEXT("Play Sound")))
            goto done;

        // Sleep for a second to let the sound finish playing
        Sleep(1000);
    }

done:

    // Release objects that we created.
    CleanUp();

    RetailOutput(TEXT("\r\nApp exited...\r\n"));

    return 0;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    ChangeDSPSettings

Description:

    Sample code to show how to load a DSP file

Arguments:

    None
  
Return Value:

    TRUE on success, FALSE on failure

-------------------------------------------------------------------*/
BOOL
ChangeDSPSettings(LPTSTR lpEffect)
{
    IKsPropertySet       *pps;
    DIRECTSOUND_DSPPROPS dsdsp;

    // This dsp file has no 4 channel qsound
    dsdsp.imixerQSoundStart = 12;
    dsdsp.imixerQSoundEnd	= 15;

    // Load the custom DSP files - note that these must be in the image.
    if (!LoadDSPFiles(lpEffect, TEXT("\\pc\\samples\\drewfx.fob"),
        &dsdsp.pbDspData1, &dsdsp.cbDspData1, &dsdsp.pbDspData2, &dsdsp.cbDspData2))
    {
        RetailOutput(TEXT("Failed to Load DSP files - make sure they are in the image\r\n"));
        return FALSE;
    }

    g_errLast = g_pds->QueryInterface(IID_IKsPropertySet, (void **)&pps);
    if (CheckError(TEXT("QueryInterface for IKsPropertySet")))
        return FALSE;

    g_errLast = pps->Set(DSPROPSETID_SetDspProgram, TRUE, &dsdsp, sizeof(dsdsp), NULL, 0);
    if (CheckError(TEXT("Set DSP Program")))
        return FALSE;

    pps->Release();
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    SetMixerSettings

Description:

    Sample code to show how to set the advanced mixer settings

Arguments:

    None
  
Return Value:

    TRUE on success, FALSE on failure

-------------------------------------------------------------------*/
BOOL
SetMixerSettings()
{
    IKsPropertySet *pps;
    DIRECTSOUNDBUFFER_MIXERPROPS dsbmp;

    g_errLast = g_pdsbToPlay->QueryInterface(IID_IKsPropertySet, (void **)&pps);
    if (CheckError(TEXT("QueryInterface for IKsPropertySet")))
        return FALSE;

    // Fill in the Mixerprops fields
    dsbmp.imixerLeftorMono      = 0;    // mixer # 0 
    dsbmp.imixerRight           = 0;    // mixer # 0 
    dsbmp.fUseVolume            = TRUE;
    dsbmp.sndvolDspLeftorMono   = 15;   // full volume thru sound effect
    dsbmp.sndvolNoDspLeftorMono = 0; 
    dsbmp.sndvolDspRight        = 15;   // full volume thru sound effect
    dsbmp.sndvolNoDspRight      = 0;

    g_errLast = pps->Set(DSPROPSETID_MixerProp, TRUE, &dsbmp, sizeof(dsbmp), NULL, 0);
    if (CheckError(TEXT("Set MixerProp")))
        return FALSE;

    RetailOutput(TEXT("[0] %d [1] %d [2] %d [3] %d [4] %d \r\n"), dsbmp.imixerLeftorMono, dsbmp.sndvolDspLeftorMono,
                 dsbmp.sndvolNoDspLeftorMono, dsbmp.sndvolDspRight, dsbmp.sndvolNoDspRight);

    pps->Release();
    return TRUE;
}
