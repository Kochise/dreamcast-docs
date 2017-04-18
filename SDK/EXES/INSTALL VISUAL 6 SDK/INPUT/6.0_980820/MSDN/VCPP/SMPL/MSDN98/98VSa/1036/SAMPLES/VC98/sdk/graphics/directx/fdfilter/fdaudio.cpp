//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 1996-1997 Microsoft Corporation. All Rights Reserved.
//
// File:	FDAUDIO.CPP
// Contents:	Audio related routines for full-duplex device usage
//
// Description:	This file includes functionality for enumerating devices &
//		formats, initializing devices and buffers, and the CALLBACK
//		procedures for dealing with full duplex.
//


// So we can get the IID_IDirectSoundNotify and GUID_NULL GUID declared
#define	INITGUID
#include <objbase.h>
#include <cguid.h>

#include "fdfilter.h"
#include "fdaudio.h"
#include "filter.h"

static BOOL IsDSDeviceInList(LPGUID, PDSDEVICEDESC );
static BOOL EnumDSDevices( void );
static BOOL EnumDSCDevices( void );
static BOOL CALLBACK DSEnumProc( LPGUID, LPCSTR, LPCSTR, LPVOID );
static BOOL InitInputDevice(void);
static BOOL InitPrimarySoundBuffer( void );
static void ProcessInput( DWORD );

extern HINSTANCE g_hDSoundLib;
typedef HRESULT (WINAPI * PFN_DSCREATE)(LPGUID lpguid, LPDIRECTSOUND * ppDS, IUnknown FAR * pUnkOuter);
typedef BOOL (WINAPI * PFN_DSENUMERATE)(LPDSENUMCALLBACK lpDSEnumCallback, LPVOID lpContext);
typedef HRESULT (WINAPI * PFN_DSCCREATE)(LPGUID lpGUID,	LPDIRECTSOUNDCAPTURE *lplpDSC,LPUNKNOWN pUnkOuter);
typedef BOOL (WINAPI * PFN_DSCENUMERATE)(LPDSENUMCALLBACK lpDSEnumCallback,LPVOID lpContext);

//////////////////////////////////////////////////////////////////////////////
//
//
//
//
static BOOL InitSoundData( BOOL fAllowFormatCancel, BOOL fReset )
	{
    if( NULL == gpwfxOutput )
	{
	gpwfxOutput = new WAVEFORMATEX;
	if( NULL == gpwfxOutput )
	    goto ISD_Fail;
	ZeroMemory( gpwfxOutput, sizeof(WAVEFORMATEX));
	gpwfxOutput->wFormatTag = WAVE_FORMAT_PCM;
	DPF( 3, "Created gpwfxOutput" );
	DPWFX( 3, gpwfxOutput );
	}

    if( NULL == gpwfxInput )
	{
	gpwfxInput = new WAVEFORMATEX;
	if( NULL == gpwfxInput )
	    goto ISD_Fail;
	ZeroMemory( gpwfxInput, sizeof(WAVEFORMATEX));
	gpwfxInput->wFormatTag = WAVE_FORMAT_PCM;
	DPF( 3, "Created gpwfxInput" );
	DPWFX( 3, gpwfxInput );
	}

    EnumDSDevices();
    if( NULL == gpdsddOutputDevices )
	{
	MessageBox( ghMainWnd, "No DirectSound devices are available!", gszAppName, MB_OK );
	goto ISD_Fail;
	}

    EnumDSCDevices();
	if( NULL == gpdsddInputDevices )
	{
	MessageBox( ghMainWnd, "No DirectSoundCapture devices are available!", gszAppName, MB_OK );
	goto ISD_Fail;
	}

    if( !DialogBox( ghInst, MAKEINTRESOURCE(IDD_DEVICES),
		    ghMainWnd, (DLGPROC)SelectDevicesDlgProc ))
	goto ISD_Fail;

	if( fReset )
	{
    StopBuffers();
    DestroyBuffers();
    CloseDSCDevice(FALSE);
    CloseDSDevice();
	}

	if( !InitPrimarySoundBuffer())
	goto ISD_Fail;

	if( !InitInputDevice() )
	goto ISD_Fail;

    if( !DialogBoxParam( ghInst, MAKEINTRESOURCE(IDD_FORMATS),
			    ghMainWnd, (DLGPROC)SelectFormatsDlgProc,
			    (LPARAM)fAllowFormatCancel ))
	goto ISD_Fail;

    return TRUE;

ISD_Fail:
    return FALSE;
	}

//////////////////////////////////////////////////////////////////////////////
//
//
//
//
BOOL InitSoundDevices( BOOL fAllowFormatCancel )
    {
	int	i;
	DWORD	dwThreadID;

	ZeroMemory(grgEventNotify, sizeof(grgEventNotify));
	for( i = 0; i < NUM_EVENTS; i++ )
	{
	grgEventNotify[i] = CreateEvent(NULL, FALSE, FALSE, NULL);
	if( NULL == grgEventNotify[i] )
		goto ISD_Fail;
	}

	ghThread = CreateThread( NULL, 0, ThreadProcessInput,
							 NULL, 0, &dwThreadID );
	if( NULL == ghThread )
		goto ISD_Fail;

	return InitSoundData( fAllowFormatCancel, FALSE );

ISD_Fail:
    return FALSE;
    }


BOOL ReOpenSoundDevices( BOOL fAllowFormatCancel )
    {
	return InitSoundData( fAllowFormatCancel, TRUE );
    }

//////////////////////////////////////////////////////////////////////////////
//
//
//
//
static BOOL IsDSDeviceInList( LPGUID lpguidDevice, PDSDEVICEDESC pdsddList )
    {
    PDSDEVICEDESC pdsdd = pdsddList;

    while( pdsdd )
	{
	// This works because operator== is overloaded for GUIDS
	if( NULL == lpguidDevice )
	    {
	    if( pdsdd->guDevice == GUID_NULL )
		return TRUE;
	    }
	else if( pdsdd->guDevice == *lpguidDevice )
	    return TRUE;

	pdsdd = pdsdd->pNext;
	}
    return FALSE;
    }


//////////////////////////////////////////////////////////////////////////////
// EnumDSDevices()
//
//    Enumerates the DirectSound devices with the help of DirectSoundEnumerate
// and DSEnumProc.  Adds entries to a global list about each device.
//
static BOOL EnumDSDevices( void )
    {
	PFN_DSENUMERATE pfn_DSEnumerate;

	// Get a pointer to DirectSoundEnumerate()
	pfn_DSEnumerate = (PFN_DSENUMERATE)GetProcAddress(g_hDSoundLib, "DirectSoundEnumerateA");
	
	if (pfn_DSEnumerate == NULL)
	{
        MessageBox(ghMainWnd, "DSOUND.DLL does not implement DirectSoundEnumerate()", gszAppName, MB_OK);		
	}
	else
	{
		(*pfn_DSEnumerate)(DSEnumProc, &gpdsddOutputDevices);
	}

    return TRUE;
    }


//////////////////////////////////////////////////////////////////////////////
// EnumDSCDevices()
//
//    Enumerates the DirectSoundCapture devices with the help of
// DirectSoundCaptureEnumerate and DSEnumProc.
// Adds entries to a global list about each device.
//
static BOOL EnumDSCDevices( void )
    {
	PFN_DSCENUMERATE pfn_DSCEnumerate;
	
	// Get a pointer to DirectSoundEnumerate()
	pfn_DSCEnumerate = (PFN_DSCENUMERATE)GetProcAddress(g_hDSoundLib, "DirectSoundCaptureEnumerateA");
	
	if (pfn_DSCEnumerate == NULL)
	{
        MessageBox(ghMainWnd, "DSOUND.DLL does not implement DirectSoundCaptureEnumerate(). The system may not have DirectX 5.0 installed.", gszAppName, MB_OK);		
	}
	else
	{
		(*pfn_DSCEnumerate)(DSEnumProc, &gpdsddInputDevices);
	}

    return TRUE;
    }


//////////////////////////////////////////////////////////////////////////////
// InitInputDevice()
//
//    Creates and initializes the input device for the application.
//
static BOOL InitInputDevice( void )
	{
	HRESULT	dsrval;
	PFN_DSCCREATE	pfn_DSCCreate;

	// create a DirectSoundCapture object.
	pfn_DSCCreate = (PFN_DSCCREATE)GetProcAddress(g_hDSoundLib, "DirectSoundCaptureCreate");
	if (pfn_DSCCreate == NULL)
	{
        MessageBox(ghMainWnd, "DSOUND.DLL does not implement DirectSoundCaptureCreate(). The system may not have DirectX 5.0 installed.", gszAppName, MB_OK);		
		goto IID_ExitError;
	}
	else
	{
		if (FAILED(dsrval = (*pfn_DSCCreate)(&gpdsddIn->guDevice, &gpdsc, NULL)))
		{
			DPF( 0, "Couldn't open DirectSoundCapture device (%s)", TranslateDSError(dsrval));
			goto IID_ExitError;
		}
	}
	return TRUE;

IID_ExitError:
	return FALSE;
	}

//////////////////////////////////////////////////////////////////////////////
// InitPrimarySoundBuffer()
//
//    Creates and initializes the primary sound buffer for the application.
// We need the primary buffer in order to get the 3D listener interface and
// also to select output format type.
//
static BOOL InitPrimarySoundBuffer( void )
    {
    HRESULT	    dsrval;
    DSBUFFERDESC    dsbd;
	PFN_DSCREATE	pfn_DSCreate;

    ZeroMemory( &dsbd, sizeof(DSBUFFERDESC));
    
    dsbd.dwSize = sizeof(DSBUFFERDESC);
    dsbd.dwFlags = DSBCAPS_CTRL3D | DSBCAPS_PRIMARYBUFFER;

	// Create a directsound object.
	pfn_DSCreate = (PFN_DSCREATE)GetProcAddress(g_hDSoundLib, "DirectSoundCreate");
	if (pfn_DSCreate == NULL)
	{
		MessageBox(ghMainWnd, "DSOUND.DLL does not implement DirectSoundCreate()", gszAppName, MB_OK);
		goto IPSB_ExitError;
	}
	else
	{
		if (FAILED(dsrval = (*pfn_DSCreate)(&gpdsddOut->guDevice, &gpds, NULL)))
		{
			DPF( 0, "Couldn't open DirectSound device (%s)", TranslateDSError(dsrval));
			goto IPSB_ExitError;
		}
	}

    if( FAILED( dsrval = gpds->SetCooperativeLevel( ghMainWnd, DSSCL_PRIORITY )))
	{
	DPF( 0, "Couldn't get PRIORITY cooperative level (%s)", TranslateDSError(dsrval));
	goto IPSB_ExitError;
	}

    if( FAILED( dsrval = gpds->CreateSoundBuffer( &dsbd, &gpdsbPrimary, NULL )))
	{
	DPF( 0, "Couldn't create primary buffer (%s)", TranslateDSError(dsrval));
	goto IPSB_ExitError;
	}

    return TRUE;

IPSB_ExitError:
    if( NULL != gpdsbPrimary )
	{
	DPF( 1, "Releasing Primary in InitPrimarySoundBuffer() error cleanup" );
	gpdsbPrimary->Release();
	gpdsbPrimary = NULL;
	}
    if( NULL != gpds )
	{
	DPF( 1, "Releasing DSound object in InitPrimarySoundBuffer() error cleanup" );
	gpds->Release();
	gpds= NULL;
	}

    return FALSE;
    }


//////////////////////////////////////////////////////////////////////////////
// DSEnumProc()
//
//   DirectSoundXXXEnumerate() callback procedure which fills the DSDEVICEDESC list
// with data about available devices.
//
static BOOL CALLBACK DSEnumProc( LPGUID lpguidDevice, LPCSTR lpszDesc,
                                LPCSTR lpszDrvName, LPVOID lpContext )
    {
    PDSDEVICEDESC   pdsddNew;
    PDSDEVICEDESC   *ppdsddList = (PDSDEVICEDESC *)lpContext;

    if( !IsDSDeviceInList( lpguidDevice, *ppdsddList ))
	{
	if(( pdsddNew = new DSDEVICEDESC ) == NULL )
	    {
	    return TRUE;
	    }

	ZeroMemory( pdsddNew, sizeof(DSDEVICEDESC));

	if( NULL != lpguidDevice )
	    pdsddNew->guDevice = *lpguidDevice;
	else
	    pdsddNew->guDevice = GUID_NULL;

	if(( pdsddNew->pszDeviceDesc = new char[lstrlen(lpszDesc)+1]) == NULL )
	    {
	    delete pdsddNew;
	    return TRUE;
	    }
	lstrcpy( pdsddNew->pszDeviceDesc, lpszDesc );

	pdsddNew->pNext = *ppdsddList;
	*ppdsddList = pdsddNew;
	}

    return TRUE;
    }


//////////////////////////////////////////////////////////////////////////////
//
//
//
//
void ClearDSDeviceList( PDSDEVICEDESC *ppdsdd )
    {
    PDSDEVICEDESC   pdsddCur, pdsddTemp;

    pdsddCur = *ppdsdd;

    while( pdsddCur )
	{
	if( NULL != pdsddCur->pszDeviceDesc )
	    delete[] pdsddCur->pszDeviceDesc;

	pdsddTemp = pdsddCur->pNext;
	delete pdsddCur;
	pdsddCur = pdsddTemp;
	}
    *ppdsdd = NULL;
    }

//////////////////////////////////////////////////////////////////////////////
//
//
//
//
void FillDeviceCombo( HWND hCombo, PDSDEVICEDESC pdsddDevices )
    {
    PDSDEVICEDESC   pdsdd = pdsddDevices;
    int		    idx;

    if( NULL == hCombo )
	return;

    while( pdsdd )
	{
	idx = ComboBox_InsertString( hCombo, -1, pdsdd->pszDeviceDesc );
	ComboBox_SetItemData( hCombo, idx, pdsdd );
	pdsdd = pdsdd->pNext;
	}
    if( NULL != pdsddDevices )
	ComboBox_SetCurSel( hCombo, 0 );
    }

//////////////////////////////////////////////////////////////////////////////
//
//
//
//
void ScanAvailableDSFormats( void )
    {
    WAVEFORMATEX    wfx;
    HRESULT	    dsrval;
    HCURSOR	    hCursor;
    int		    i;

    DPF( 3, "Scanning %u DirectSound formats for availability", NUM_FORMATCODES );
    if( NULL == gpds || NULL == gpdsbPrimary )
	{
        for( i = 0; i < NUM_FORMATCODES; i++ )
	    aOutputFormats[i].fEnabled = FALSE;
	return;
	}

    // This might take a second or two, so throw up the hourglass
    hCursor = GetCursor();
    SetCursor( LoadCursor( NULL, IDC_WAIT ));

    ZeroMemory( &wfx, sizeof(wfx));
    wfx.wFormatTag = WAVE_FORMAT_PCM;
 
    for( i = 0; i < NUM_FORMATCODES; i++ )
	{
	FormatCodeToWFX( aOutputFormats[i].dwCode, &wfx );

	if( FAILED( dsrval = gpdsbPrimary->SetFormat( &wfx )))
	    {
	    DPF( 5, "Failed with SetFormat() for %u format", aOutputFormats[i].dwCode );
	    aOutputFormats[i].fEnabled = FALSE;
	    }
	else
	    {
	    DPF( 5, "Succeeded with SetFormat() for %u format", aOutputFormats[i].dwCode );
	    aOutputFormats[i].fEnabled = TRUE;
	    }
	}
    SetCursor( hCursor );
    }


//////////////////////////////////////////////////////////////////////////////
//
//
//
//
void ScanAvailableDSCFormats( void )
    {
    WAVEFORMATEX    wfx;
    HRESULT	    dsrval;
    HCURSOR	    hCursor;
    int		    i;
	DSCBUFFERDESC	dscbd;
	LPDIRECTSOUNDCAPTUREBUFFER	pdscb;

    DPF( 3, "Scanning %u DirectSoundCapture formats for availability", NUM_FORMATCODES );
    if( NULL == gpdsc )
	{
        for( i = 0; i < NUM_FORMATCODES; i++ )
	    aInputFormats[i].fEnabled = FALSE;
	return;
	}

    // This might take a second or two, so throw up the hourglass
    hCursor = GetCursor();
    SetCursor( LoadCursor( NULL, IDC_WAIT ));

    for( i = 0; i < NUM_FORMATCODES; i++ )
	aOutputFormats[i].fEnabled = FALSE;

    ZeroMemory( &wfx, sizeof(wfx));
    wfx.wFormatTag = WAVE_FORMAT_PCM;
 
    for( i = 0; i < NUM_FORMATCODES; i++ )
	{
	FormatCodeToWFX( aInputFormats[i].dwCode, &wfx );

	ZeroMemory(&dscbd, sizeof(dscbd));
	dscbd.dwSize = sizeof(dscbd);
	dscbd.dwBufferBytes = wfx.nAvgBytesPerSec;
	dscbd.lpwfxFormat = &wfx;

	pdscb = NULL;

	if ((dsrval = gpdsc->CreateCaptureBuffer(&dscbd, &pdscb, NULL)))
	    {
	    DPF( 5, "Failed with DirectSoundCapture::CreateCaptureBuffer() for %u format", aInputFormats[i].dwCode );
	    aInputFormats[i].fEnabled = FALSE;
	    }
	else
	    {
	    DPF( 5, "Succeeded with DirectSoundCapture::CreateCaptureBuffer() for %u format", aInputFormats[i].dwCode );
	    pdscb->Release();
	    aInputFormats[i].fEnabled = TRUE;
	    }
	}

    SetCursor( hCursor );
    }


//////////////////////////////////////////////////////////////////////////////
//
//
//
//
void CloseDSDevice( void )
    {
    if( NULL != gpdsbOutput )
	{
	gpdsbOutput->Release();
	gpdsbOutput = NULL;
	}
    if( NULL != gpdsbPrimary )
	{
	gpdsbPrimary->Release();
	gpdsbPrimary = NULL;
	}
    if( NULL != gpds )
	{
	gpds->Release();
	gpds = NULL;
	}
    }


//////////////////////////////////////////////////////////////////////////////
//
//
//
//
void CloseDSCDevice( BOOL fBufferOnly )
    {
	if( NULL != gpdscbInput )
	{
	gpdscbInput->Release();
	gpdscbInput = NULL;
	}
	if( (NULL != gpdsc) && !fBufferOnly )
	{
	gpdsc->Release();
	gpdsc = NULL;
	}
    }

//////////////////////////////////////////////////////////////////////////////
//
//
//
//
BOOL InitBuffers( void )
    {
    HRESULT	    dsrval;
	int			i;
	LPDIRECTSOUNDNOTIFY	pdsn;

    if( gfBuffersInitialized )
	return TRUE;
	if (NULL == gpdscbInput)
		return FALSE;

    EnterCriticalSection( &gcsBufferData );

	ZeroMemory(grgdsbpn, sizeof(grgdsbpn));

	for( i = 0; i < NUM_BUFFERS; i++ )
	{
		grgdsbpn[i].dwOffset = (gcbBufferSize * i) + gcbBufferSize - 1;
		grgdsbpn[i].hEventNotify = grgEventNotify[i];
	}
	grgdsbpn[i].dwOffset = DSBPN_OFFSETSTOP;
	grgdsbpn[i].hEventNotify = grgEventNotify[i];
	
	if( FAILED( dsrval = gpdscbInput->QueryInterface(IID_IDirectSoundNotify, (LPVOID *)&pdsn ) ) )
	{
	DPF( 0, "Unable to QI for IDirectSoundNotify on input (%s)", TranslateDSError(dsrval));
	goto Abort_InitBuffers;
	}
	dsrval = pdsn->SetNotificationPositions(NUM_POSNOTIFS, grgdsbpn);
	pdsn->Release();
	if( FAILED( dsrval ) )
	{
	DPF( 0, "Unable to SetNotificationPositions on input (%s)", TranslateDSError(dsrval));
	goto Abort_InitBuffers;
	}

	ZeroMemory( &gdsbdOutput, sizeof(gdsbdOutput));
    gdsbdOutput.dwSize = sizeof(gdsbdOutput);
    gdsbdOutput.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_GLOBALFOCUS;
    gdsbdOutput.dwBufferBytes = NUM_BUFFERS * gcbBufferSize / 2;
    // We want the format of this secondary to match the format of the input
    // data.  This lets us blindly copy the data out and DSound worries about
    // matching the bits and channels to our desired primary buffer format.
    gdsbdOutput.lpwfxFormat = gpwfxInput;

    if( FAILED( dsrval = gpds->CreateSoundBuffer( &gdsbdOutput, &gpdsbOutput, NULL )))
	{
	DPF( 0, "Unable to create sound buffer for output (%s)", TranslateDSError(dsrval));
	goto Abort_InitBuffers;
	}

    InterlockedExchange( &gfBuffersInitialized, TRUE );
    LeaveCriticalSection( &gcsBufferData );
    return TRUE;

Abort_InitBuffers:
    // TODO: If there were any buffers put out, we must Reset to get them back
    ASSERT( DestroyBuffers());
    LeaveCriticalSection( &gcsBufferData );
    return FALSE;
    }


//////////////////////////////////////////////////////////////////////////////
//
//
//
//
BOOL StartBuffers( void )
    {
    if( NULL == gpdscbInput || NULL == gpdsbOutput )
	return FALSE;

    gpdscbInput->Start( DSCBSTART_LOOPING );
    
    // Rewind the output buffer, fill it with silence, and play it
    gpdsbOutput->SetCurrentPosition( 0 );
    WriteSilenceToOutput( 0, gdsbdOutput.dwBufferBytes );
    gpdsbOutput->Play( 0, 0, DSBPLAY_LOOPING );
    return TRUE;
    }


//////////////////////////////////////////////////////////////////////////////
//
//
//
//
BOOL StopBuffers( void )
    {
    if( NULL == gpdscbInput || NULL == gpdsbOutput )
	return FALSE;

    gpdscbInput->Stop();
    gpdsbOutput->Stop();

	return TRUE;
    }


//////////////////////////////////////////////////////////////////////////////
//
//
//
//
BOOL DestroyBuffers( void )
    {
	ZeroMemory( grgdsbpn, sizeof(grgdsbpn) );
    if( NULL != gpdsbOutput )
	{
	gpdsbOutput->Release();
	gpdsbOutput = NULL;
	}
    InterlockedExchange( &gfBuffersInitialized, FALSE );
    return TRUE;
    }


//////////////////////////////////////////////////////////////////////////////
//
//
//
//
BOOL WriteSilenceToOutput( DWORD dwStart, DWORD cbLength )
    {
    PBYTE   pb1, pb2;
    DWORD   cb1, cb2;

    if(( !dwStart && !cbLength ) || NULL == gpdsbOutput
			|| NULL == gdsbdOutput.lpwfxFormat )
	return FALSE;

    if( SUCCEEDED( gpdsbOutput->Lock( dwStart, cbLength, (LPVOID*)&pb1, &cb1, (LPVOID*)&pb2, &cb2, 0 )))
	{
	FillMemory( pb1, cb1, (gdsbdOutput.lpwfxFormat->wBitsPerSample == 8) ? 128 : 0 );
	if( NULL != pb2 && cb2 )
	    FillMemory( pb2, cb2, (gdsbdOutput.lpwfxFormat->wBitsPerSample == 8) ? 128 : 0 );

	gpdsbOutput->Unlock( pb1, cb1, pb2, cb2 );
	return TRUE;
	}

    return FALSE;
    }


static void ProcessInput( DWORD iEvent )
{
    static	DWORD dwWritePosition = 0xFFFFFFFF;
    HRESULT	dsrval;
	PBYTE	pb1, pb2;
	DWORD	cb1, cb2;
	BOOL	fRestoredBuffer = FALSE;
	LPBYTE	pbInput1 = NULL;
	DWORD	cbInput1;
	LPBYTE	pbInput2;
	DWORD	cbInput2;
	DWORD	ibInputStart;
	DWORD	cbInputEnd;

	if( NULL == gpdscbInput )
	{
		return;
	}

	EnterCriticalSection( &gcsBufferData );

	if( NUM_BUFFERS == iEvent )
	{
		dwWritePosition = 0xFFFFFFFF;
		goto WIC_SkipDataProcessing;
	}
	else if( iEvent > 0 )
	{
		ibInputStart = grgdsbpn[iEvent-1].dwOffset+1;
	}
	else
	{
		ibInputStart = 0;
	}
	cbInputEnd = grgdsbpn[iEvent].dwOffset + 1 - ibInputStart;

	dsrval = gpdscbInput->Lock(ibInputStart, cbInputEnd,
							   (LPVOID *)&pbInput1, &cbInput1, (LPVOID *)&pbInput2, &cbInput2, 0);
	if( FAILED(dsrval) )
	{
		DPF( 0, "Couldn't Lock input buffer. (%s)", TranslateDSError(dsrval));
		goto WIC_SkipDataProcessing;
	}

	if( (NULL != pbInput2) || (0 != cbInput2) )
	{
		DPF( 0, "Second input buffer pointer is non-NULL");
	}

	if( NULL != gpdsbOutput )
	{
		DWORD dwStatus;
		if( FAILED( dsrval = gpdsbOutput->GetStatus( &dwStatus )))
		{
			DPF( 0, "Unable to get buffer status. (%s)", TranslateDSError(dsrval));
			goto WIC_SkipDataProcessing;
		}
		if( dwStatus & DSBSTATUS_BUFFERLOST )
		{
			if( FAILED( dsrval = gpdsbOutput->Restore()))
			{
				DPF( 0, "Couldn't Restore output buffer. (%s)", TranslateDSError(dsrval));
				goto WIC_SkipDataProcessing;
			}
			dwWritePosition = 0;
			fRestoredBuffer = TRUE;
		}
		else
		{
			if( dwWritePosition == 0xFFFFFFFF )
			{
				DWORD	dwPlay, dwWrite;

				gpdsbOutput->GetCurrentPosition( &dwPlay, &dwWrite );

				// Need to add some extra to make sure we're ahead
				// of the write cursor
				dwWritePosition = dwWrite + (2*gcbBufferSize);
				while( dwWritePosition >= gdsbdOutput.dwBufferBytes )
					dwWritePosition -= gdsbdOutput.dwBufferBytes;
			}
		}

		if( SUCCEEDED( gpdsbOutput->Lock( dwWritePosition,
			cbInput1,
			(LPVOID *)&pb1, &cb1, (LPVOID *)&pb2, &cb2, 0 )))
		{
			if( NULL != pb1 && NULL != gpFilter )
			{
				gpFilter->Transform( pbInput1, cb1, pb1 );
			}
			if( cb2 && NULL != pb2 && NULL != gpFilter )
			{
				gpFilter->Transform( pbInput1 + cb1,
					cbInput1 - cb1, pb2 );
			}
			gpdsbOutput->Unlock( pb1, cb1, pb2,
				cbInput1 - cb1 );
			dwWritePosition += cbInput1;
			while( dwWritePosition >= gdsbdOutput.dwBufferBytes )
				dwWritePosition -= gdsbdOutput.dwBufferBytes;
		}
		if( fRestoredBuffer )
		{
			gpdsbOutput->SetCurrentPosition( 0 );
			if( FAILED( dsrval = gpdsbOutput->Play( 0, 0, DSBPLAY_LOOPING )))
				DPF( 0, "Unable to restart restored buffer. (%s)", TranslateDSError(dsrval));
			dwWritePosition = 0xFFFFFFFF;
		}
	}
WIC_SkipDataProcessing:
	if( NULL != pbInput1 )
		gpdscbInput->Unlock(pbInput1, cbInput1, pbInput2, cbInput2);
	LeaveCriticalSection( &gcsBufferData );
}

DWORD WINAPI ThreadProcessInput( LPVOID )
{
	DWORD	dwResult;

	while( TRUE )
	{
		dwResult = WaitForMultipleObjects( NUM_EVENTS, grgEventNotify,
										   FALSE, INFINITE );

		// Terminate processing?
		if( (WAIT_OBJECT_0 + iEventTerminate) == dwResult )
		{
			break;
		}

		if( (WAIT_OBJECT_0 <= dwResult) && (dwResult <= (WAIT_OBJECT_0 + iEventReset)) )
		{
			ProcessInput( dwResult - WAIT_OBJECT_0 );
		}
	}

	return 0;
}
