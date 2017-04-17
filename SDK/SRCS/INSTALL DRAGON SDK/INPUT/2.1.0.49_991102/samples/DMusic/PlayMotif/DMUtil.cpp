/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    DMUtil.cpp

Abstract:

    DirectMusic functionality

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "PlayMotif.hpp"
//#include <direct.h>

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++

IDirectMusicLoader*      g_pdmloader      = NULL;
IDirectMusicPerformance* g_pmdperformance = NULL;
IDirectMusicSegment*     g_pdmsegment     = NULL;
IDirectMusicStyle*       g_pdmstyle       = NULL;
TCHAR                    g_rgtszMotifName[9][MAX_PATH];

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    InitDirectMusic

Description:

    Initilizes DirectMusic

Arguments:

    TCHAR *tszSearchDir   - The directory to search for the file

    THCAR *tszFile        - The file to search for.  Any internally referenced
                            files must also be in the search directory.

Return Value:

    TRUE on success, FALSE on failure

-------------------------------------------------------------------*/
BOOL
InitDirectMusic(TCHAR *tszSearchDir, TCHAR *tszFile)
{
    HRESULT hr;
    GUID    guid;
    DWORD   dwIndex;

    // Initialize COM
    hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    if (FAILED(hr))
	{
        RetailOutput(TEXT("Could not initialize COM\r\n"));
        return FALSE;
	}

    // Create loader object
    hr = CoCreateInstance( CLSID_DirectMusicLoader, NULL, CLSCTX_INPROC,
                           IID_IDirectMusicLoader, (void**)&g_pdmloader );
    if (FAILED(hr))
	{
        RetailOutput(TEXT("Could not create DMusic Loader\r\n"));
        return FALSE;
	}

    // Create performance object
    hr = CoCreateInstance( CLSID_DirectMusicPerformance, NULL, CLSCTX_INPROC,
                           IID_IDirectMusicPerformance, (void**)&g_pmdperformance );
    if (FAILED(hr))
	{
        RetailOutput(TEXT("Could not create DMusic Performance\r\n"));
        return FALSE;
	}

    // Initialize the software synthesizer
    if (!InitializeSynth())
        return FALSE;

    // Load the segment
    if (!LoadSegment(tszSearchDir, tszFile))
        return FALSE;

    // Set the segment to repeat many times
    g_pdmsegment->SetRepeats(200);

    // Get the Style from the Segment by calling the Segment's GetData() with the data type
    // GUID_StyleTrackStyle. 0xffffffff indicates to look at Tracks in all TrackGroups in the
    // segment.  The first 0 indicates to retrieve the Style from the first Track in the
    // indicated TrackGroup. The second 0 indicates to retrieve the Style from the beginning
    // of the Segment, i.e. time 0 in Segment time.  If this Segment was loaded from a Section
    // file, there is only one Style and it is at time 0.  Note that the GetData() call with
    // GUID_IDirectMusicStyle assumes the third parameter is the address of a pointer to an
    // IDirectMusicStyle.
    guid = GUID_IDirectMusicStyle;
    g_errLast = g_pdmsegment->GetParam( guid, 0xffffffff, 0, 0, NULL, (void*)&g_pdmstyle );
    if (CheckError(TEXT("GetParam")))
        return FALSE;

    // Play the segment and wait. The DMUS_SEGF_BEAT indicates to play on the next beat
    // if there is a segment currently playing. The first 0 indicates to play (on the next
    // beat from) now.  The final NULL means do not return an IDirectMusicSegmentState* in
    // the last parameter.
    g_pmdperformance->PlaySegment( g_pdmsegment, DMUS_SEGF_BEAT, 0, NULL );

    // Get the names of the Motifs from the Style. Styles may have any number of Motifs,
    // but for simplicity's sake only get a maximum of 9 here.
    for( dwIndex = 0; dwIndex < 9; dwIndex++ )
    {
        if( S_OK != g_pdmstyle->EnumMotif( dwIndex, g_rgtszMotifName[dwIndex] ))
        {
            g_rgtszMotifName[dwIndex][0] = 0;
            break;
        }
    }

    return TRUE;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    PlayMotif

Description:

    Play the named Motif from the Style in the Performance

Arguments:

    TCHAR *ptszMotifName   - name of the Motif to play

Return Value:

    TRUE on success, FALSE on failure

-------------------------------------------------------------------*/
BOOL
PlayMotif( TCHAR* ptszMotifName )
{
    IDirectMusicSegment* pSeg;
    HRESULT              hr;

    // Get the Motif Segment from the Style, setting it to play once through (no repeats.) Check
    // for S_OK specifically, because GetMotif() returns S_FALSE if it doesn't find the Motif.
    hr = g_pdmstyle->GetMotif( ptszMotifName, &pSeg );
    if( S_OK == hr )
    {
        // Play the segment. The PSF_BEAT indicates to play on the next beat if there is a segment
        // currently playing. PSF_SECONDARY means to play the segment as a secondary segment, which
        // plays on top of the currently playing primary segment. The first 0 indicates to play (on
        // the next beat from) now.  The final NULL means do not return an IDirectMusicSegmentState*
        // in the last parameter.
        g_pmdperformance->PlaySegment(pSeg, DMUS_SEGF_BEAT | DMUS_SEGF_SECONDARY,  0,  NULL);
        pSeg->Release();
    }

    return TRUE;
}


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    InitializeSynth

Description:

    Initialize the software synthesizer into the performance. This
    function also calls IDirectMusicPerformance::Init to initialize the
    performance and create the DirectMusic object

Arguments:

    None

Return Value:

    TRUE on success, FALSE on failure

-------------------------------------------------------------------*/
BOOL
InitializeSynth()
{
    IDirectMusic*     pDM;
    IDirectMusicPort* pPort = NULL;
    DMUS_PORTPARAMS   dmos;
    GUID              guidSink;

    // Initialize the performance. Have the performance create the
    // DirectMusic object by setting pDM to NULL. It is needed to
    // create the port.
    pDM = NULL;
    g_errLast = g_pmdperformance->Init( &pDM, NULL, NULL );
    if (CheckError(TEXT("Initialize Performance")))
        return FALSE;

    // Set autodownloading to be on.  This will cause DLS instruments to be downloaded
	// whenever a segment is played, and unloaded whenever it stops.  Please see the
	// DirectMusic documentation for more information.
	BOOL fAutoDownload = TRUE;
	g_pmdperformance->SetGlobalParam(GUID_PerfAutoDownload,&fAutoDownload,sizeof(BOOL));

    // Create the software synth port.  An alternate, easier method is to call
    // pPerf->AddPort(NULL), which automatically creates the synth port, adds it to the
    // performance, and assigns PChannels.
    memset(&dmos, 0, sizeof(DMUS_PORTPARAMS) );
    dmos.dwSize = sizeof(DMUS_PORTPARAMS);
    dmos.dwChannelGroups = 1;                       // create 1 channel groups on the port
    dmos.dwValidParams = DMUS_PORTPARAMS_CHANNELGROUPS;

    memset(&guidSink, 0, sizeof(GUID) );

    g_errLast = pDM->CreatePort( CLSID_DirectMusicSynth, &dmos, &pPort, NULL );
    if (CheckError(TEXT("Create Port")))
        return FALSE;

    g_errLast = pDM->Activate( TRUE );
    if (CheckError(TEXT("Activate DMusic")))
        return FALSE;

    // Succeeded in creating the port. Add the port to the Performance with five groups of 16 midi channels.
    g_errLast = g_pmdperformance->AddPort( pPort );
    if (CheckError(TEXT("Add Port")))
        return FALSE;

    // Assign a block of 16 PChannels to this port. Block 0, port pPort, and group 1 means to assign
    // PChannels 0-15 to group 1 on port pPort. PChannels 0-15 correspond to the standard 16 MIDI channels.
    g_pmdperformance->AssignPChannelBlock( 0, pPort, 1 );

    // Release the port since the performance now has its own reference.
    pPort->Release();

    // Release the DirectMusic object. The performance has its own reference and we just needed
    // it to call CreatePort.
    pDM->Release();

    return TRUE;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    LoadSegment

Description:

    Change the loader's current search directory and load the Sample.sgt
    segment. The segment internally references the Sample.sty style and
    Sample.dls downloadable sample file. When the loader loads the
    segment, it also loads the internally referenced files from the search
    directory. If fUseCWD is TRUE, use the current working directory.
    Otherwise, use the path referenced by the DirectMusic/Media registry key.

Arguments:

    TCHAR *tszSearchDir   - The directory to search for the file

    THCAR *tszFile        - The file to search for.  Any internally referenced
                            files must also be in the search directory.

Return Value:

    TRUE on success, FALSE on failure

-------------------------------------------------------------------*/
BOOL
LoadSegment(TCHAR *tszSearchDir, TCHAR *tszFile)
{
    DMUS_OBJECTDESC ObjDesc;                // Object descriptor for pLoader->GetObject()

    g_pdmloader->SetSearchDirectory( GUID_DirectMusicAllTypes, tszSearchDir, FALSE );

    // Now load the segment file.  Sections load as type Segment, as do MIDI files, for example.
    ObjDesc.guidClass = CLSID_DirectMusicSegment;
    ObjDesc.dwSize = sizeof(DMUS_OBJECTDESC);
    _tcscpy( ObjDesc.wszFileName, tszFile);
    ObjDesc.dwValidData = DMUS_OBJ_CLASS | DMUS_OBJ_FILENAME;

    g_errLast = g_pdmloader->GetObject( &ObjDesc, IID_IDirectMusicSegment, (void**)&g_pdmsegment );
    if (g_errLast != 0 && g_errLast != DMUS_S_PARTIALLOAD)
    {
        RetailOutput(TEXT("ERROR:  PlayMotif could not load the segment: %s\r\n\r\n"), tszFile);
        RetailOutput(TEXT("        Make sure the segment file is located in the directory\r\n"));
        RetailOutput(TEXT("        specified by the search path (%s).\r\n"), tszSearchDir);
        RetailOutput(TEXT("        If your search path is \\Windows, then the files need\r\n"));
        RetailOutput(TEXT("        to be added to the BIN image using the Image Configuration\r\n"));
        RetailOutput(TEXT("        tool.  See the readme.txt for this sample for more information.\r\n"));
        
        return FALSE;
	}

    return TRUE;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    FreeDirectMusic

Description:

    Releases structures created by DirectMusic.

Arguments:

    None

Return Value:

    None

-------------------------------------------------------------------*/
void
FreeDirectMusic()
{
    if(g_pdmsegment != NULL)
    {
        // Release the Segment
        g_pdmsegment->Release();
    }

    if(g_pmdperformance != NULL)
    {
        // If there is any music playing, stop it.
        g_pmdperformance->Stop( NULL, NULL, 0, 0 );

        // CloseDown and Release the performance object
        g_pmdperformance->CloseDown();
        g_pmdperformance->Release();
    }

    if(g_pdmloader != NULL)
    {
        // Release the loader object
        g_pdmloader->Release();
    }

    // Release COM
    CoUninitialize();
}
