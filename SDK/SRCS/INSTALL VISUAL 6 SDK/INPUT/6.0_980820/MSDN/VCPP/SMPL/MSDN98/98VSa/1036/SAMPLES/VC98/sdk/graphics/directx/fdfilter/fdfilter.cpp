//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 1996-1997 Microsoft Corporation. All Rights Reserved.
//
// File:	FDFILTER.CPP
// Contents:	General routines related to the Full-Duplex Filter Sample
//
// Description:	This file includes the window procedures and initialization
//		and destruction code.
//

#define __DEFINE_GLOBAL_VARIABLES__
#include "fdfilter.h"
#undef __DEFINE_GLOBAL_VARIABLES__
#include "fdaudio.h"
#include "filter.h"

#include <commctrl.h>

static BOOL InitInstance( HINSTANCE, HINSTANCE, LPSTR, int );

static void DestroyInstance( void );

HINSTANCE g_hDSoundLib;	// module handle to dsound.dll.

///////////////////////////////////////////////////////////////////////////////
// DestroyInstance()
//
//    Does all of the cleanup for an instance of the application.
//
static void DestroyInstance( void )
    {
	DestroyBuffers();
	CloseDSCDevice(FALSE);
	CloseDSDevice();
    if( NULL != gpwfxOutput )
	{
	delete gpwfxOutput;
	gpwfxOutput = NULL;
	}
    if( NULL != gpFilter )
	{
	delete gpFilter;
	gpFilter = NULL;
	}
    if( NULL != gpdsddOutputDevices )
	{
	ClearDSDeviceList( &gpdsddOutputDevices );
	}

	if( NULL != gpdsddInputDevices )
	{
	ClearDSDeviceList( &gpdsddInputDevices );
	}

	// wait for the thread to quit
	if( NULL != ghThread )
	{
		// Set the Terminate Event so the thread will quit
		SetEvent( grgEventNotify[iEventTerminate] );

		WaitForSingleObject( ghThread, INFINITE );
		CloseHandle( ghThread );
	}

	for(int i = 0; i < NUM_EVENTS; i++ )
	{
		if( NULL != grgEventNotify[i] )
			CloseHandle( grgEventNotify[i] );
	}
    // Get rid of the critical section object
    DeleteCriticalSection( &gcsBufferData );
    }


//////////////////////////////////////////////////////////////////////////////
// InitInstance()
//
//    This function is responsible for all initialization that must occur
// when a new instance of our application is started.
//
static BOOL InitInstance( HINSTANCE hInstance, LPSTR lpszCommandLine, int cmdShow )
    {
    // Used to protect buffer data from multi-threaded access
    InitializeCriticalSection( &gcsBufferData );

    if(( ghMainWnd = CreateDialog( ghInst, MAKEINTRESOURCE(IDD_MAIN), NULL, (DLGPROC)MainDlgProc )) == NULL )
	{
	DPF( 0, "Call to CreateDialog() failed." );
	DestroyInstance();
	return FALSE;
	}

    HMENU hSysMenu = GetSystemMenu( ghMainWnd, FALSE );
    EnableMenuItem( hSysMenu, SC_MAXIMIZE, MF_BYCOMMAND | MF_GRAYED );
    EnableMenuItem( hSysMenu, SC_SIZE, MF_BYCOMMAND | MF_GRAYED );

    /* Continue doing other initialization stuff */
    if( !InitSoundDevices( TRUE ))
	{
	DPF( 0, "Call to InitSoundDevices() failed." );
	goto II_ExitError;
	}

    ShowWindow( ghMainWnd, cmdShow );
    UpdateWindow( ghMainWnd );

    return TRUE;    // TRUE indicates success

II_ExitError:
    if( NULL != ghMainWnd )
	{
	DestroyWindow( ghMainWnd );
	ghMainWnd = NULL;
	}

    return FALSE;   // FALSE indicates failure on initialization
    }	// InitInstance()


//////////////////////////////////////////////////////////////////////////////
// WinMain()
//
//   Main entry point for this program's execution.  Everything starts here.
//
int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
						LPSTR lpszCmdLine, int cmdShow)
    {
    MSG   msg;

    DbgInitialize( TRUE );

    InitCommonControls();

    // Save instance handle
    ghInst = hInstance;

	// Load dsound.dll
	g_hDSoundLib = LoadLibrary("DSOUND.DLL");
	if (g_hDSoundLib == NULL)
	{
		MessageBox(ghMainWnd, "Could not load DSOUND.DLL", gszAppName, MB_OK);
		return 0;
	}

    if (!InitInstance(hInstance, lpszCmdLine, cmdShow))
	{
		FreeLibrary(g_hDSoundLib);
		return 0;
	}

    /* Polling messages from event queue */
    while (GetMessage((LPMSG)&msg, NULL, 0, 0))
	{
	// Only Translate and Dispatch the message if it's not going
	// to one of our many modeless dialog windows
	if( !IsDialogMessage( ghMainWnd, &msg ))
	    {
	    TranslateMessage((LPMSG)&msg);
	    DispatchMessage((LPMSG)&msg);
	    }
	}

	FreeLibrary(g_hDSoundLib);
    return (int)msg.wParam;
    }	// WinMain()


//////////////////////////////////////////////////////////////////////////////
// MainDlgProc()
//
//    This the equivalent of a main window procedure, except our main window
// is really a dialog box.
//
BOOL CALLBACK MainDlgProc( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam )
    {
    static HWND	hInputDeviceText, hInputFormatText, hEnableCheck, hFilterCombo;
    static HWND	hOutputDeviceText, hPrimaryFormatText, hSecondaryFormatText;

    DWORD   dwCode;
    int	    ndx;
	    
    switch( message )
	{
	case WM_INITDIALOG:
	    hInputDeviceText = GetDlgItem( hDlg, IDC_MAIN_INPUTDEVICE_TEXT );
	    hInputFormatText = GetDlgItem( hDlg, IDC_MAIN_INPUTFORMAT_TEXT );
	    hOutputDeviceText = GetDlgItem( hDlg, IDC_MAIN_OUTPUTDEVICE_TEXT );
	    hPrimaryFormatText = GetDlgItem( hDlg, IDC_MAIN_PRIMARYFORMAT_TEXT );
	    hSecondaryFormatText = GetDlgItem( hDlg, IDC_MAIN_SECONDARYFORMAT_TEXT );
	    hFilterCombo = GetDlgItem( hDlg, IDC_MAIN_FILTER_COMBO );
	    hEnableCheck = GetDlgItem( hDlg, IDC_MAIN_ENABLEFILTER_CHECK );

	    ndx = ComboBox_AddString( hFilterCombo, "None (pass-through)" );
	    ComboBox_SetItemData( hFilterCombo, ndx, 0 );

	    ComboBox_SetCurSel( hFilterCombo, ndx );

	    ndx = ComboBox_AddString( hFilterCombo, "Gargle" );
	    ComboBox_SetItemData( hFilterCombo, ndx, 1 );


	    EnterCriticalSection( &gcsBufferData );
	    if( NULL != gpFilter )
		delete gpFilter;
	    gpFilter = new CFilter;
	    LeaveCriticalSection( &gcsBufferData );
	    break;
	    
	case WM_PAINT:
	    {
	    PAINTSTRUCT	ps;
	    char	szFormat[64];

	    BeginPaint( hDlg, &ps );
	    if( NULL != gpdsddIn )
		Static_SetText( hInputDeviceText, gpdsddIn->pszDeviceDesc );
	    if( NULL != gpdsddOut )
		Static_SetText( hOutputDeviceText, gpdsddOut->pszDeviceDesc );

	    FormatCodeToText( gdwInputFormat, szFormat, sizeof(szFormat));
	    Static_SetText( hInputFormatText, szFormat );

	    FormatCodeToText( gdwOutputFormat, szFormat, sizeof(szFormat));
	    Static_SetText( hPrimaryFormatText, szFormat );

	    FormatCodeToText( gdwInputFormat, szFormat, sizeof(szFormat));
	    Static_SetText( hSecondaryFormatText, szFormat );

	    EndPaint( hDlg, &ps );
	    }
	    break;

	case WM_COMMAND:
	    switch( LOWORD(wParam))
		{
		case IDC_MAIN_FILTER_COMBO:
		    if( HIWORD( wParam ) == CBN_SELCHANGE )
			{
			if(( ndx = ComboBox_GetCurSel( hFilterCombo )) == -1 )
			    break;
			dwCode = ComboBox_GetItemData( hFilterCombo, ndx );
			if( 0 == dwCode )
			    {
			    EnterCriticalSection( &gcsBufferData );
			    if( NULL != gpFilter )
				delete gpFilter;
			    gpFilter = new CFilter;
			    LeaveCriticalSection( &gcsBufferData );
			    }
			if( 1 == dwCode )
			    {
			    EnterCriticalSection( &gcsBufferData );
			    if( NULL != gpFilter )
				delete gpFilter;
			    gpFilter = (CFilter *)new CGargle( gpwfxInput->nSamplesPerSec,
								gpwfxInput->nChannels,
								gpwfxInput->wBitsPerSample / 8 );
			    LeaveCriticalSection( &gcsBufferData );
			    }
			}
		    break;

		case IDC_MAIN_ENABLEFILTER_CHECK:
			if (NULL == gpdscbInput)
				break;
		    if( Button_GetCheck( hEnableCheck ))
			{
			// Put our hands over our eyes and hold our breaths,
			// here comes the data!
			if( !gfBuffersInitialized )
			    InitBuffers();
			StartBuffers();
			}
		    else
			{
			StopBuffers();
			}
		    break;

		case ID_SETTINGS_DEVICES:
		    if( FAILED( ReOpenSoundDevices( FALSE )))
			break;

		    Button_SetCheck( hEnableCheck, FALSE );

		    EnterCriticalSection( &gcsBufferData );
		    if( gpFilter )
			gpFilter->SetFormat( gpwfxInput );
		    LeaveCriticalSection( &gcsBufferData );
		    InvalidateRect( hDlg, NULL, FALSE );
		    UpdateWindow( hDlg );
		    break;

		case ID_SETTINGS_FORMATS:
		    if( Button_GetCheck( hEnableCheck ))
			{
			Button_SetCheck( hEnableCheck, FALSE );
			StopBuffers();
			}
			CloseDSCDevice(TRUE);
		    DestroyBuffers();

			DialogBoxParam( ghInst, MAKEINTRESOURCE(IDD_FORMATS),
				    ghMainWnd, (DLGPROC)SelectFormatsDlgProc, 0L );
		    InvalidateRect( hDlg, NULL, FALSE );
		    UpdateWindow( hDlg );

		    EnterCriticalSection( &gcsBufferData );
		    if( gpFilter )
			gpFilter->SetFormat( gpwfxInput );
		    LeaveCriticalSection( &gcsBufferData );
		    break;

		case ID_HELP_ABOUT:
		    DialogBox( ghInst, MAKEINTRESOURCE(IDD_ABOUT),
					    ghMainWnd, (DLGPROC)AboutDlgProc );
		    break;

		case ID_FILE_EXIT:
		case IDCANCEL:
		    // Be sure to stop the buffers when we're done
		    StopBuffers();
		    DestroyWindow( hDlg );
		    break;
		    
		default:
		    return FALSE;
		}
	    break;

	case WM_DESTROY:
	    DestroyInstance();
	    PostQuitMessage(0);
	    break;

	default:
	    return FALSE;
	}

    return TRUE;
    }


//////////////////////////////////////////////////////////////////////////////
// AboutDlgProc()
//
//    Small dialog procedure for the About Box.
//
BOOL CALLBACK AboutDlgProc( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam )
    {
    if( message == WM_COMMAND && LOWORD(wParam) == IDOK )
	{
	EndDialog( hDlg, FALSE );
	return TRUE;
	}
    else
	return FALSE;
    }


//////////////////////////////////////////////////////////////////////////////
// CancelWarningDlgProc()
//
//    Small dialog procedure for the Formats DLG's cancel warning box.
//
BOOL CALLBACK CancelWarningDlgProc( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam )
    {
    if( message == WM_COMMAND && LOWORD(wParam) == IDOK )
	{
	EndDialog( hDlg, TRUE );
	return TRUE;
	}
    else if( message == WM_COMMAND && LOWORD(wParam) == IDCANCEL )
	{
	EndDialog( hDlg, FALSE );
	return TRUE;
	}
    else
	return FALSE;
    }


//////////////////////////////////////////////////////////////////////////////
// FormatCodeToText()
//
//    This function reads format codes and puts out a text string for them.
// It does not check for invalid codes.  FALSE return means the buffer was
// invalid in some way, TRUE means success.
//
BOOL FormatCodeToText( DWORD dwFormat, LPSTR lpszBuf, int nBufSize )
    {
    DWORD   dwFreq;

    // The longest string we'll ever put in is 21 characters (including NULL)
    if( NULL == lpszBuf || nBufSize < 21 )
	return FALSE;

    // Extract the sample rate
    dwFreq = FC_GETFREQCODE(dwFormat);
    dwFreq = ( dwFreq == 8 ? 8000 : (dwFreq / 11) * 11025);

    wsprintf( lpszBuf, "%u Hz, %u-bit %s", dwFreq, FC_GETBITS(dwFormat),
		FC_GETCHANNELS(dwFormat) == 1 ? "Mono" : "Stereo" );

    return TRUE;
    }


//////////////////////////////////////////////////////////////////////////////
// FormatCodeToWFX()
//
//    This function reads format codes and fills most of the fields of a
// WAVEFORMATEX structure based on the values read.  It does not fill the
// wFormatTag or cbSize members.
//
BOOL FormatCodeToWFX( DWORD dwFormat, PWAVEFORMATEX pwfx )
    {
    DWORD   dwFreq;

    if( NULL == pwfx )
	return FALSE;

    // Extract the sample rate
    dwFreq = FC_GETFREQCODE(dwFormat);
    pwfx->nSamplesPerSec = ( dwFreq == 8 ? 8000 : (dwFreq / 11) * 11025);

    pwfx->wBitsPerSample = (WORD)FC_GETBITS(dwFormat);
    pwfx->nChannels = (WORD)FC_GETCHANNELS(dwFormat);

    // The nBlockAlign calculation below only works for whole-byte samples
    ASSERT( pwfx->wBitsPerSample % 8 == 0 );

    pwfx->nBlockAlign = pwfx->nChannels * (pwfx->wBitsPerSample / 8);
    pwfx->nAvgBytesPerSec = pwfx->nBlockAlign * pwfx->nSamplesPerSec;

    return TRUE;
    }


//////////////////////////////////////////////////////////////////////////////
// DisableFormatCode()
//
//    Disables the given format code
//
void DisableFormatCode( PFORMATDATA pfd, DWORD dwCode )
    {
    int	i;

    for( i = 0; i < NUM_FORMATCODES; i++ )
	{
	if( pfd[i].dwCode == dwCode )
	    {
	    pfd[i].fEnabled = FALSE;
	    break;
	    }
	}
    }


//////////////////////////////////////////////////////////////////////////////
// FillFormatListBox()
//
//    This little helper function takes an array FORMATDATA structures and
// fills the given ListBox with text/data entries that represent all the
// formats.
//
void FillFormatListBox( PFORMATDATA pfd, HWND hList )
    {
    char    szFormat[64];

    for( int i = 0; i < NUM_FORMATCODES; i++ )
	{
	if( pfd[i].fEnabled )
	    {
	    FormatCodeToText( pfd[i].dwCode, szFormat, sizeof(szFormat));
	    ListBox_SetItemData( hList, ListBox_AddString( hList, szFormat),
				    pfd[i].dwCode );
	    }
	}
    }


//////////////////////////////////////////////////////////////////////////////
// SelectDevicesDlgProc()
//
//    Procedure for the dialog which queries the user for device selection.
//
BOOL CALLBACK SelectDevicesDlgProc( HWND hDlg, UINT message,
				    WPARAM wParam, LPARAM lParam )
    {
    static HWND	hDirectSoundCaptureCombo, hDirectSoundCombo;

    switch( message )
	{
	case WM_INITDIALOG:
	    hDirectSoundCaptureCombo = GetDlgItem( hDlg, IDC_DEVICES_DIRECTSOUNDCAPTURE_COMBO );
	    hDirectSoundCombo = GetDlgItem( hDlg, IDC_DEVICES_DIRECTSOUND_COMBO );

	    FillDeviceCombo( hDirectSoundCaptureCombo, gpdsddInputDevices );
	    FillDeviceCombo( hDirectSoundCombo, gpdsddOutputDevices );
	    break;

	case WM_COMMAND:
	    switch( LOWORD(wParam))
		{
		case IDOK:
		    gpdsddIn = (PDSDEVICEDESC)ComboBox_GetItemData( hDirectSoundCaptureCombo,
					ComboBox_GetCurSel(hDirectSoundCaptureCombo));
		    gpdsddOut = (PDSDEVICEDESC)ComboBox_GetItemData( hDirectSoundCombo,
					ComboBox_GetCurSel(hDirectSoundCombo));
		    EndDialog( hDlg, TRUE );
		    break;
		case IDCANCEL:
		    EndDialog( hDlg, FALSE );
		    break;
		default:
		    return FALSE;
		}
	    break;

	default:
	    return FALSE;
	}
    return TRUE;
    }


//////////////////////////////////////////////////////////////////////////////
// SelectFormatsDlgProc()
//
//   Procedure the format selection dialog.
//
BOOL CALLBACK SelectFormatsDlgProc( HWND hDlg, UINT message,
				    WPARAM wParam, LPARAM lParam )
    {
    static HWND	hOutputList, hInputList, hOK;
    static BOOL	fAllowFormatCancel = FALSE;
    HRESULT	dsrval;
    DWORD	dwOutFormat, dwInFormat;
    int		ndx;

    switch( message )
	{
	case WM_INITDIALOG:
	    hOutputList = GetDlgItem( hDlg, IDC_FORMATS_OUTPUT_LISTBOX );
	    hInputList = GetDlgItem( hDlg, IDC_FORMATS_INPUT_LISTBOX );
	    hOK = GetDlgItem( hDlg, IDOK );

	    if( NULL == gpds || NULL == gpdsbPrimary || NULL == gpdsc )
		{
		EndDialog( hDlg, FALSE );
		return FALSE;
		}
	    ScanAvailableDSFormats();
	    FillFormatListBox( aOutputFormats, hOutputList );
	    if( !ListBox_GetCount( hOutputList ))
		{
		MessageBox( ghMainWnd, "Warning: no output formats available",
				gszAppName, MB_OK );
		EndDialog( hDlg, FALSE );
		return FALSE;
		}
	    // lParam is a BOOL flag, which is TRUE if cancel is "allowed". If
	    // the app is running and the devices are selected, the user clearly
	    // must select a set of formats or else end the application.
	    fAllowFormatCancel = (BOOL)lParam;
		
	    break;

	case WM_COMMAND:
	    switch( LOWORD(wParam))
		{
		case IDC_FORMATS_INPUT_LISTBOX:
		    if( ListBox_GetCurSel( hOutputList ) != -1 &&
				    ListBox_GetCurSel( hInputList ) != -1 )
			Button_Enable( hOK, TRUE );
		    else
			Button_Enable( hOK, FALSE );
		    break;

		case IDC_FORMATS_OUTPUT_LISTBOX:
		    if( HIWORD(wParam) == LBN_SELCHANGE )
			{
			dwOutFormat = ListBox_GetItemData( hOutputList,
					    ListBox_GetCurSel( hOutputList ));
			FormatCodeToWFX( dwOutFormat, gpwfxOutput );
			DPF( 3, "Formats DLG: Setting gpwfxOutput" );
			DPWFX( 3, gpwfxOutput );
			if( FAILED( dsrval = gpdsbPrimary->SetFormat( gpwfxOutput )))
			    {
			    DPF( 1, "Formats DLG: Failed to set DSound primary to %lu (%s)",
					dwOutFormat, TranslateDSError(dsrval));
			    FormatCodeToWFX( gdwOutputFormat, gpwfxOutput );
			    DPF( 1, "Formats DLG: Attempting to reset gpwfxOutput" );
			    DPWFX( 1, gpwfxOutput );
			    if( FAILED( dsrval = gpdsbPrimary->SetFormat( gpwfxOutput )))
				{
				DPF( 0, "Formats DLG: Failed to set OLD format (%lu) on primary (%s)",
					    gdwOutputFormat, gpwfxOutput );
				// TODO: Finish this handler
				}
			    ndx = ListBox_FindItemData( hOutputList, -1, gdwOutputFormat );
			    ListBox_SetCurSel( hOutputList, ndx );
			    // TODO: Find the item corresponding to the old format
			    //       and select it back? (without re-entering this code)
			    }
			else
			    {
			    gdwOutputFormat = dwOutFormat;

			    ScanAvailableDSCFormats();
			    ListBox_ResetContent( hInputList );
			    FillFormatListBox( aInputFormats, hInputList );
			    }
			Button_Enable( hOK, FALSE );
			}
		    break;

		case IDOK:
		    ndx = ListBox_GetCurSel( hOutputList );
		    // OK button should be disabled unless there's a selection
		    // in both listboxes
		    ASSERT( ndx != -1 );

		    dwOutFormat = ListBox_GetItemData( hOutputList, ndx );
		    FormatCodeToWFX( dwOutFormat, gpwfxOutput );
		    // We shouldn't get to this dialog if there's no output
		    ASSERT( NULL != gpds && NULL != gpdsbPrimary );
		    if(( dsrval = gpdsbPrimary->SetFormat( gpwfxOutput )))
			{
			DPF( 0, "Can't set format %lu (%s)",
					dwOutFormat, TranslateDSError(dsrval));
			goto Abort_OK;
			}
		    else
			{
			gdwOutputFormat = dwOutFormat;
			}

		    ndx = ListBox_GetCurSel( hInputList );
		    // OK button should be disabled unless there's a selection
		    // in both listboxes
		    ASSERT( ndx != -1 );

		    dwInFormat = ListBox_GetItemData( hInputList, ndx );
		    FormatCodeToWFX( dwInFormat, gpwfxInput );

			{
				DSCBUFFERDESC	dscbd = {0};

				gcbBufferSize = max( 4096, gpwfxInput->nAvgBytesPerSec / 8 );
				gcbBufferSize -= gcbBufferSize % gpwfxInput->nBlockAlign;
				DPF( 1, "Set input buffer size to %lu bytes", gcbBufferSize );

				dscbd.dwSize = sizeof(dscbd);
				dscbd.dwBufferBytes = gcbBufferSize * NUM_BUFFERS;
				dscbd.lpwfxFormat = gpwfxInput;

				if ((dsrval = gpdsc->CreateCaptureBuffer(&dscbd, &gpdscbInput, NULL)))
				{
				DPF( 0, "Unable to open selected input device! format = %lu, dsrval = %lu", dwInFormat, dsrval );
				goto Abort_OK;
				}
				else
				{
				gdwInputFormat = dwInFormat;
				}
			}

		    EndDialog( hDlg, TRUE );
	    Abort_OK:
		    break;
		case IDCANCEL:
		    if( fAllowFormatCancel )
			EndDialog( hDlg, FALSE );
		    else
			{
			if( !DialogBox( ghInst,
					MAKEINTRESOURCE(IDD_CANCELWARNING),
					ghMainWnd, (DLGPROC)CancelWarningDlgProc ))
			    {
			    EndDialog( hDlg, FALSE );
			    PostMessage( ghMainWnd, WM_DESTROY, 0, 0 );
			    return FALSE;
			    }
			}
		    break;

		default:
		    return FALSE;
		}
	    break;

	default:
	    return FALSE;
	}
    return TRUE;
    }


