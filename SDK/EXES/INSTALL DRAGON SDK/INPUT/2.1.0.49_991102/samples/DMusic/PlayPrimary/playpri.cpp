//-----------------------------------------------------------------------------
// File: PlayPri.cpp
//
// Desc: Plays a Primary Segment using DirectMusic
//
//
// Copyright (c) 1998 Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------


#include <objbase.h>
#include <initguid.h>
//#include <direct.h>
#include <dmusicc.h>
#include <dmusici.h>
#include "PlayPri.h"

// Both Borland CBuilder3 and Watcom C++ 11 have "chdir" defined incorrectly
// So the code below changes chdir only for MSVC++.
#if	(defined(_MSC_VER))
#define chdir   _chdir
#endif

//-----------------------------------------------------------------------------
// Global variables for the DirectMusic sample
//-----------------------------------------------------------------------------
IDirectMusicLoader*      g_pLoader;
IDirectMusicPerformance* g_pPerformance;
IDirectMusicSegment*     g_pSegment;

//-----------------------------------------------------------------------------
// Name: InitDirectMusic()
// Desc: Initilizes DirectMusic
//-----------------------------------------------------------------------------
HRESULT InitDirectMusic(LPTSTR pszPath)
{
    HRESULT hr;

    // Initialize COM
    hr = CoInitializeEx( NULL, COINIT_MULTITHREADED );
    if(FAILED(hr))
    {
        RetailOutput(TEXT("Could not initialize COM\r\n"));
        return hr;
	}

    // Create loader object
    hr = CoCreateInstance(CLSID_DirectMusicLoader, NULL, CLSCTX_INPROC,
                          IID_IDirectMusicLoader, (void**)&g_pLoader);
    if(FAILED(hr))
    {
        RetailOutput(TEXT("Could not create DMusic Loader\r\n"));
        return hr;
	}

    // Create performance object
    hr = CoCreateInstance(CLSID_DirectMusicPerformance, NULL, CLSCTX_INPROC,
                          IID_IDirectMusicPerformance, (void**)&g_pPerformance);
    if(FAILED(hr))
    {
        RetailOutput(TEXT("Could not create DMusic Performance\r\n"));
        return hr;
	}

    // Initialize the performance with defaults
    // Please refer to the PlayMotf example for a more flexible, yet slightly
    // more complicated, way of doing this.
    hr = g_pPerformance->Init(NULL, NULL, NULL);
    if(FAILED(hr))
    {
        RetailOutput(TEXT("Could not initialize performance\r\n"));
        return hr;
	}
    // Set autodownloading to be on.  This will cause DLS instruments to be downloaded
	// whenever a segment is played, and unloaded whenever it stops.  Please see the
	// DirectMusic documentation for more information.
	BOOL fAutoDownload = TRUE;
    g_pPerformance->SetGlobalParam(GUID_PerfAutoDownload, &fAutoDownload, sizeof(BOOL));

    hr = g_pPerformance->AddPort(NULL);

    if(FAILED(hr))
	{
        RetailOutput(TEXT("Could not add port to performance\r\n"));
        return hr;
	}

    RetailOutput(TEXT("Setting DMusic search directory to: %s\r\n"), pszPath);
    g_pLoader->SetSearchDirectory(GUID_DirectMusicAllTypes, pszPath, FALSE);

    return S_OK;
}

//-----------------------------------------------------------------------------
// Name: FreeDirectMusic()
// Desc: Releases DirectMusic
//-----------------------------------------------------------------------------
HRESULT FreeDirectMusic()
{
    if(g_pSegment != NULL)
    {
        // Release the Segment
        g_pSegment->Release();
    }

    if(g_pPerformance != NULL)
    {
        // If there is any music playing, stop it.
        g_pPerformance->Stop(NULL, NULL, 0, 0);

        // CloseDown and Release the performance object
        g_pPerformance->CloseDown();
        g_pPerformance->Release();
    }

    if(g_pLoader != NULL)
    {
        // Release the loader object
        g_pLoader->Release();
    }

    // Release COM
    CoUninitialize();

    return S_OK;
}

HRESULT PlaySegment(LPTSTR pszSegment, int nRepeats)
{
    HRESULT hr;
    DMUS_OBJECTDESC ObjDesc; // Object descriptor for pLoader->GetObject()

    // now load the segment file.
    // sections load as type Segment, as do MIDI files, for example.
    ObjDesc.guidClass = CLSID_DirectMusicSegment;
    ObjDesc.dwSize = sizeof(DMUS_OBJECTDESC);
    lstrcpy(ObjDesc.wszFileName, pszSegment);
    ObjDesc.dwValidData = DMUS_OBJ_CLASS | DMUS_OBJ_FILENAME;

    hr = g_pLoader->GetObject(&ObjDesc, IID_IDirectMusicSegment, (void**)&g_pSegment);
    if(FAILED(hr))
    {
        RetailOutput(TEXT("ERROR:  PlayPrimary could not load the segment: %s\r\n\r\n"), pszSegment);
        RetailOutput(TEXT("        Make sure the segment file is located in the directory\r\n"));
        RetailOutput(TEXT("        specified by the search path (default is \\Windows).\r\n"));
        RetailOutput(TEXT("        If your search path is \\Windows, then the files need\r\n"));
        RetailOutput(TEXT("        to be added to the BIN image using the Image Configuration\r\n"));
        RetailOutput(TEXT("        tool.  See the readme.txt for this sample for more information.\r\n"));

        return hr;
	}

    // set the segment to repeat many times
    g_pSegment->SetRepeats(nRepeats);

    HANDLE hNotify = CreateEvent(NULL, FALSE, FALSE, NULL);
    DMUS_NOTIFICATION_PMSG* pNotifyMsg;

    if(hNotify == NULL)
    {
        RetailOutput(TEXT("Couldn't allocate notification event.\r\n"));
        FreeDirectMusic();
        return FALSE;
    }
    g_pPerformance->SetNotificationHandle(hNotify, 0);
    g_pPerformance->AddNotificationType(GUID_NOTIFICATION_SEGMENT);

    // Play the segment and wait. The DMUS_SEGF_BEAT indicates to play on the
    // next beat if there is a segment currently playing. The first 0 indicates
    // to play (on the next beat from) now.
    // The final NULL means do not return an IDirectMusicSegmentState* in
    // the last parameter.
    RetailOutput(TEXT("Playing segment: %s\r\n"), pszSegment);
    g_pPerformance->PlaySegment(g_pSegment, DMUS_SEGF_BEAT, 0, NULL);

    for(;;)
    {
        WaitForSingleObject(hNotify, INFINITE);
        hr = g_pPerformance->GetNotificationPMsg(&pNotifyMsg);
        if(hr == S_OK)
        {
            if(pNotifyMsg->dwNotificationOption == DMUS_NOTIFICATION_SEGEND)
            {
                g_pPerformance->FreePMsg((DMUS_PMSG*)pNotifyMsg);
                break;
            }
            g_pPerformance->FreePMsg((DMUS_PMSG*)pNotifyMsg);
        }
    }
    RetailOutput(TEXT("Done playing segment\r\n"));

    return S_OK;
}
