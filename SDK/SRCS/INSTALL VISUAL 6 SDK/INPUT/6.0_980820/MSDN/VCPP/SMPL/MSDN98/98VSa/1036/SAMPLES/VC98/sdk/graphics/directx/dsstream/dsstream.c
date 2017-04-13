/*==========================================================================
 *
 *  Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.
 *
 *  File:   dsstream.c
 *  Content:   Illustrates streaming data from a disk WAVE file to a
 *             DirectSound secondary buffer for playback.
 *
 ***************************************************************************/
#define WIN32_LEAN_AND_MEAN
#define INITGUID
#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>
#include <dsound.h>
#include <commctrl.h>
#include <commdlg.h>
#include <memory.h>
#include <cderr.h>

#include "dsstream.h"
#include "wassert.h"

char szAppClass[] = "DSStreamWndClass";
char szAppName[]  = "DSStream";

char szAppTitle[64];
char szAppCaption[64];
char szPan[32];
char szVolume[32];
char szFrequency[32];
char szProgress[32];
char szOpenFilter[128];
char szOpenDLGTitle[64];


char szTemp[256];
char szDebug[128];
char szFileBuffer[MAX_PATH];
char szFileTitle[MAX_PATH];
char szCDStartPath[MAX_PATH];	        // The path to start the Open dialog in
 
// Registry Key and Value names that allow us to retrive a path something like
// "C:\DXSDK\SDK\MEDIA", but matching the current install.
static const TCHAR gszRegKeyDirect3D[] = TEXT("Software\\Microsoft\\Direct3D");
static const TCHAR gszRegValueD3DPath[] = TEXT("D3D Path");

// Size of longest token below
#define MAX_TOKEN_LEN	7


static TCHAR gszPlayToken[] = TEXT("PLAY");
static TCHAR gszLoopToken[] = TEXT("LOOP");
static TCHAR gszCloseToken[] = TEXT("CLOSE");
static TCHAR gszStickyToken[] = TEXT("STICKY");
static TCHAR gszGlobalToken[] = TEXT("GLOBAL");

LPDIRECTSOUND		lpDS = NULL;
LPDIRECTSOUNDBUFFER	lpDSBStreamBuffer = NULL;
LPDIRECTSOUNDNOTIFY lpDirectSoundNotify = NULL;

WAVEINFOCA		wiWave;

HWND	hWndMain, hWndPan, hWndPanText, hWndVol, hWndVolText, hWndFreqText;
HWND	hWndBar, hWndPlay, hWndStop, hWndLoopCheck, hWndFreq, hWndProg;
HWND	hWndProgText;

#ifdef DEBUG
HWND			hWndList;
#endif

HINSTANCE	hInst;

static BOOL	bFileOpen = FALSE, bPlaying = FALSE;
static BOOL     bEnumDrivers = FALSE, gfCloseOnDone = FALSE;
static UINT     uTimerID = 0, uLastPercent = 100;
static GUID     guID;
static DWORD	gdwFocus = 0;

static BOOL InitApp( HINSTANCE );
static BOOL InitInstance( HINSTANCE, int );
static void BuildTitleBarText( void );
// Call this in initialization to set the szCDStartPath[] global variable
static void GetMediaStartPath( void );
static void FillDataBuffer( void );
static void LoadFromCommandLine( LPSTR lpszCmd );
extern void UpdateProgressBar(void);
/******************************************************************************
 * WinMain()
 *
 * Entry point for all Windows programs - performs initialization, message loop
 */
int PASCAL WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
					LPSTR lpCmdLine, int nCmdShow )
    {
    MSG     msg;

    hInst = hInstance;

    /* Make sure the common controls are loaded for our use */
    InitCommonControls();


    if( !hPrevInstance )
        if( !InitApp( hInstance ))
            {
            ErrorMessageBox( IDS_ERROR_APPINIT, MB_ICONSTOP );
            return( FALSE );
	    }

    if( !InitInstance( hInstance, nCmdShow ))
        {
        ErrorMessageBox( IDS_ERROR_INSTANCEINIT, MB_ICONSTOP );
        return( FALSE );
	}

    // We know how to take exactly one file name from the command-line and open
    // it as a file to play.  We can also accept a couple command like /play,
    // /close, and /loop
    if( lpCmdLine[0] )
	LoadFromCommandLine( lpCmdLine );

    while( GetMessage((LPMSG)&msg, NULL, 0, 0 ))
        {
        TranslateMessage( &msg );
        DispatchMessage( &msg );
        }

    UnregisterClass( szAppClass, hInstance );
    return( msg.wParam );
    } /* End of WinMain() */


/*****************************************************************************/
/* InitApp()								     */
/* 									     */
/*   Inits things that only need to be created once for the this application */
/* (like creating the window class).					     */
/*****************************************************************************/
static BOOL InitApp( HINSTANCE hInstance )
    {
    WNDCLASS	wc;

    /* Set up and register a window class */
    wc.style		= CS_HREDRAW | CS_VREDRAW;
    wc.lpszClassName	= szAppClass;
    wc.lpfnWndProc	= (WNDPROC)MainWindowProc;
    wc.cbClsExtra	= 0;
    wc.cbWndExtra	= sizeof( DWORD );
    wc.hInstance	= hInstance;
    wc.hIcon            = LoadIcon( hInstance, MAKEINTRESOURCE( IDI_ICON1 ));
    wc.hCursor		= LoadCursor( NULL, IDC_ARROW );
    wc.hbrBackground	= (HBRUSH)(COLOR_WINDOW);
    wc.lpszMenuName	= MAKEINTRESOURCE( IDR_MAINMENU );

    if( !RegisterClass( &wc ))
        {
	ErrorMessageBox( IDS_ERROR_REGISTERCLASS, MB_ICONSTOP );
        return( FALSE );
        }
    return( TRUE );
    } /* End of InitApp() */


/*****************************************************************************/
/* InitInstance()							     */
/* 									     */
/* Performs initialization that must be done for each application instance.  */
/* 									     */
/*****************************************************************************/
static BOOL InitInstance( HINSTANCE hInstance, int nCmdShow )
    {
    HWND	hWnd;
    HRESULT	dsRetVal;
    RECT	crect;
    int		cx, cy;
    UINT	uCharsRead;
    BOOL	fUseGuid = FALSE;
    HMENU	hSysMenu;

    DbgInitialize( TRUE );

    // Initialize the Media start path for common open boxes
    GetMediaStartPath();
 
    LoadString( hInstance, IDS_APP_TITLE, szAppTitle, sizeof(szAppTitle));
    LoadString( hInstance, IDS_APP_CAPTION, szAppCaption, sizeof(szAppCaption));
    LoadString( hInstance, IDS_TBTITLE_PAN, szPan, sizeof(szPan));
    LoadString( hInstance, IDS_TBTITLE_VOLUME, szVolume, sizeof(szVolume));
    LoadString( hInstance, IDS_TBTITLE_FREQUENCY,
    					    szFrequency, sizeof(szFrequency));
    LoadString( hInstance, IDS_TBTITLE_PROGRESS,
    					    szProgress, sizeof(szProgress));
    LoadString( hInstance, IDS_OPEN_DLGTITLE,
    					szOpenDLGTitle, sizeof(szOpenDLGTitle));
/* This is a little trick designed to allow us to load a common dialog box
 * filter string, which is really a concatentation of several NULL-terminated
 * strings. Note that while is is possible to enter something else into the
 * resource as placeholders for the NULL characters, this has the undesireable
 * effect of forcing us to search-and-replace byte-by-byte and doesn't make it
 * as easy to internationalize our strings...
 */
    memset( szOpenFilter, 0, sizeof(szOpenFilter));
    uCharsRead = LoadString( hInstance, IDS_OPEN_FILTER1,
				szOpenFilter, sizeof(szOpenFilter)) + 1;
    uCharsRead += LoadString( hInstance, IDS_OPEN_FILTER2,
    				&szOpenFilter[uCharsRead],
    				sizeof(szOpenFilter) - uCharsRead ) + 1;
    uCharsRead += LoadString( hInstance, IDS_OPEN_FILTER3,
    				&szOpenFilter[uCharsRead],
    				sizeof(szOpenFilter) - uCharsRead ) + 1;
    LoadString( hInstance, IDS_OPEN_FILTER4,
    				&szOpenFilter[uCharsRead],
    				sizeof(szOpenFilter) - uCharsRead );

    /* Calculate the size of the client window */
    cx = CONTROL_SPACE_CX + 2*BORDER_SPACE_CX + BUTTON_CX + PAN_TB_CX
	+ 2*GetSystemMetrics( SM_CXBORDER ) + PAN_TEXT_CX + TEXT_SPACE_CX;

    cy = 2*(BORDER_SPACE_CY + GetSystemMetrics( SM_CYBORDER ))
	+ PAN_TB_CY + VOL_TB_CY + FREQ_TB_CY + PROG_TB_CY
	+ GetSystemMetrics( SM_CYMENU ) + 3*CONTROL_SPACE_CY
	+ GetSystemMetrics( SM_CYCAPTION );

    /* Create an application window */
#ifdef DEBUG
    hWnd = CreateWindow( szAppClass,		/* class name */
			szAppCaption,		/* caption for window */
			WS_OVERLAPPEDWINDOW	/* style */
			 & ~WS_THICKFRAME | WS_BORDER,
			CW_USEDEFAULT,		/* x position */
			CW_USEDEFAULT,		/* y position */
			cx,			/* width */
			cy + 200,               /* height */
			NULL,			/* parent window */
			NULL,			/* menu */
			hInstance,		/* instance */
			NULL );			/* parms */
#else
    hWnd = CreateWindow( szAppClass,		/* class name */
			szAppCaption,		/* caption for window */
			WS_OVERLAPPEDWINDOW	/* style */
			 & ~WS_THICKFRAME | WS_BORDER,
			CW_USEDEFAULT,		/* x position */
			CW_USEDEFAULT,		/* y position */
			cx,			/* width */
			cy,			/* height */
			NULL,			/* parent window */
			NULL,			/* menu */
			hInstance,		/* instance */
			NULL );			/* parms */
#endif

    if( !hWnd )
        {
	ErrorMessageBox( IDS_ERROR_MAINWNDCREATE, MB_ICONSTOP );
        return( FALSE );
	}

    hWndMain = hWnd;
    GetClientRect( hWndMain, &crect );

    // Apparently WM_INITMENU isn't called for the main window's context version
    // of the system menu, so we must gray these at startup as well.
    hSysMenu = GetSystemMenu( hWndMain, FALSE );
    EnableMenuItem( hSysMenu, SC_SIZE, MF_BYCOMMAND | MF_GRAYED );
    EnableMenuItem( hSysMenu, SC_MAXIMIZE, MF_BYCOMMAND | MF_GRAYED );

#ifdef DEBUG
    cy = 2*BORDER_SPACE_CY + PAN_TB_CY + VOL_TB_CY + FREQ_TB_CY + PROG_TB_CY
    		+ 3*CONTROL_SPACE_CY;

    hWndList = CreateWindow( "listbox", NULL, WS_CHILD | WS_VISIBLE
    				| LBS_NOINTEGRALHEIGHT | WS_VSCROLL,
				0, cy, crect.right-crect.left,
				crect.bottom - crect.top - cy,
				hWnd, NULL, hInstance, NULL );
#endif

    /* Create some controls for things like volume, panning, etc. */
    if( CreateChildren( crect ))
        return( FALSE );

    ShowWindow( hWnd, nCmdShow );
    UpdateWindow( hWnd );

    /* Create the main DirectSound object */

    bEnumDrivers = GetProfileInt( "DSSTREAM", "EnumDrivers", FALSE );
    if( bEnumDrivers && !DoDSoundEnumerate( &guID ))
	{
	fUseGuid = TRUE;
	}
    dsRetVal = DirectSoundCreate( fUseGuid ? &guID : NULL, &lpDS, NULL );

    
    if( dsRetVal != DS_OK )
        {
        ErrorMessageBox( IDS_ERROR_DSCREATE, MB_ICONSTOP );
        return( FALSE );
        }

    dsRetVal = lpDS->lpVtbl->SetCooperativeLevel( lpDS,
                                                hWndMain,
                                                DSSCL_NORMAL );
    if( dsRetVal != DS_OK )
        {
        ErrorMessageBox( IDS_ERROR_DSCOOPERATIVE, MB_ICONSTOP );
        return( FALSE );
        }


    return( TRUE );
    } /* End of InitInstance() */


/****************************************************************************/
/* MainWindowProc()                                                         */
/*                                                                          */
/*    Messages for our main window are handled here                         */
/*                                                                          */
/****************************************************************************/
LRESULT CALLBACK MainWindowProc( HWND hWnd, unsigned uMsg,
						WPARAM wParam, LPARAM lParam )
    {
#ifndef DEBUG
    LPMINMAXINFO lpMinMax;
#endif
    DWORD   dwCDErr = 0, dwProg;
    float   fPercent;
    UINT    uPercent;
    BOOL    bResult = FALSE;
    int	    nChkErr;
    HRESULT dsrval;

    switch( uMsg )
        {
        case WM_DSSTREAM_PROGRESS:
            dwProg = (DWORD)lParam;
		    dwProg  = dwProg % wiWave.mmckInRIFF.cksize;
            fPercent = (float)((dwProg * 100)/ wiWave.mmckInRIFF.cksize);  
            SendMessage( hWndProg, TBM_SETPOS,TRUE, (DWORD)(float)(fPercent*(float)PROG_MULTIPLIER));
            uPercent = (UINT)fPercent;
			wsprintf( szTemp, "%s: %u%%", szProgress, uPercent );
			Static_SetText( hWndProgText, szTemp );
			break;

         /*	This message will be posted by the helper DLL when the TimeFunc
         * is done streaming the WAVE file. It serves as notification that the
         * caller should terminate WAVE playback and end the MM timer event.
         */
        case WM_DSSTREAM_DONE:
            /* Emulate a WM_COMMAND to ourselves */
			DPF(0, "received a dsstream_done message");
            PostMessage( hWnd, WM_COMMAND, MAKEWPARAM( IDM_STOP, 0 ), 0L );
            break;

#ifdef DEBUG
        case WM_DSSTREAM_DEBUG:
            if( LOWORD(wParam) == DEBUGF_PLAYPOSITION )
                {
                wsprintf( szDebug, "pp = %li", lParam );
                ListBox_AddString( hWndList, szDebug );
                DPF( 4, szDebug );
                }
            else if( LOWORD(wParam) == DEBUGF_WRITEPOSITION )
                {
                wsprintf( szDebug, "wp = %li", lParam );
                ListBox_AddString( hWndList, szDebug );
                DPF( 4, szDebug );
                }
            else if( LOWORD(wParam) == DEBUGF_NEXTWRITE )
                {
                wsprintf( szDebug, "nw = %li", lParam );
                ListBox_AddString( hWndList, szDebug );
                DPF( 4, szDebug );
                }
            else if( LOWORD(wParam) == DEBUGF_SKIP )
                {
                ListBox_AddString( hWndList, "Skipped segment read" );
                DPF( 5, szDebug );
                }
            break;
#endif

        case WM_COMMAND:
            switch( LOWORD( wParam ))
                {
                case IDM_FILE_OPEN:
                    {
                    OPENFILENAME	ofn;
					/*
					 * Clear out and fill in an OPENFILENAME structure in preparation
					 * for creating a common dialog box to open a file.
					 */
                    memset( &ofn, 0, sizeof(OPENFILENAME));
                    ofn.lStructSize	= sizeof(OPENFILENAME);
                    ofn.hwndOwner	= hWnd;
                    ofn.hInstance	= hInst;
                    ofn.lpstrFilter	= szOpenFilter;
                    ofn.nFilterIndex	= 1;
                    szFileBuffer[0]	= '\0';
                    ofn.lpstrFile	= szFileBuffer;
                    ofn.nMaxFile	= sizeof(szFileBuffer);
					ofn.lpstrFileTitle	= szFileTitle;
					ofn.nMaxFileTitle	= sizeof(szFileTitle);
 					ofn.lpstrInitialDir = szCDStartPath;
                    ofn.lpstrDefExt	= "WAV";
                    ofn.lpstrTitle	= szOpenDLGTitle;
                    ofn.Flags		= OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;

                    bResult = GetOpenFileName( &ofn ); /* Do the dialog box */
					/*
					 *	A return of TRUE indicates that the user did not select a filename.
					 * The possible reasons are: Cancel was clicked, or an error occured.
					 * If Cancel was clicked, the CommDlgExtendedError() function will not
					 * return a valid code.  For anything else, an error code will come back.
					 */
                    if( bResult == FALSE )
                        {
                        dwCDErr = CommDlgExtendedError();
                        if( dwCDErr )
                            {
                            /* Handle a common dialog box error */
                            HandleCommDlgError( dwCDErr );
                            }
                        else	/* Clicked Cancel, so finish msg processing */
                            return( 0 );
                        }
                    else
                        {
						// Copy the directory name we opened from so that we start there
						// next time we open the dialog box...
						lstrcpy( szCDStartPath, szFileBuffer );
						szCDStartPath[ofn.nFileOffset] = '\0';

                        if( bFileOpen )
                            {
						// Before we force a close, disable auto close
						// because the user has picked a new file and is
						// obviously not ready for us to go away yet.
						    gfCloseOnDone = FALSE;
						/* Need to close the previous file before we open a new one.  The best
						 * way to do this is by faking a menu command, so that we only have the
						 * actual code in one place and it can easily be changed.
						 */
                            SendMessage( hWnd, WM_COMMAND,
                            		MAKEWPARAM( IDM_FILE_CLOSE, 0 ), 0L );
                            }
					
							if(( nChkErr = StreamBufferSetup()) != 0 )
                            {
					            // Error opening the WAVE file so abort
							    break;
                            }
                        else
                            {
                            bFileOpen = TRUE;
                            EnableMenuItem( GetMenu( hWnd ), IDM_PLAY,
                            			MF_BYCOMMAND | MF_ENABLED );
                            EnableWindow( hWndPlay, TRUE );
                            EnableMenuItem( GetMenu( hWnd ), IDM_FILE_CLOSE,
                            			MF_BYCOMMAND | MF_ENABLED );
                            DrawMenuBar( hWnd );
							BuildTitleBarText();
                            }
                        }
                    }
                    break;

                case IDM_FILE_CLOSE:
                    SendMessage( hWnd, WM_COMMAND,
                    		MAKEWPARAM( IDM_STOP,
                                            DSSTREAM_STOPF_NOREOPEN ), 0L );
		    BuildTitleBarText();
                    break;

                case IDM_OPTIONS_ENUMDRIVERS:
                    bEnumDrivers = !bEnumDrivers;
                    if( bEnumDrivers )
                        {
                        LoadString( hInst, IDS_ENUMWARNING, szTemp, sizeof(szTemp));
                        MessageBox( hWnd, szTemp, szAppCaption, MB_OK );
                        }
                    break;

                case IDM_HELP_ABOUT:
                    DialogBox( hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWndMain,
                    		(DLGPROC)DLG_About );
                    break;

                case IDC_LOOPCHECK:
                    wiWave.bLoopFile = !wiWave.bLoopFile;
                    Button_SetCheck( hWndLoopCheck, wiWave.bLoopFile );
                    if( !bPlaying && bFileOpen )
                        ResetWavePlayer();
                    break;

                case IDM_PLAY:
					DPF(0, "In idm_play");
                    if( bPlaying )
		    		{
						gfCloseOnDone = FALSE;
						SendMessage( hWnd, WM_COMMAND, MAKEWPARAM( IDM_STOP, 0 ), 0L );
					}

                    if( bFileOpen && lpDSBStreamBuffer )
                    {
						dsrval = SetupNotifications();
						if (dsrval != DS_OK)
						{
							DPF(0, "In Play command, setupnotifications failed");
							break;
						}

                        // Ensure that position is at 0, ready to go
                        dsrval = lpDSBStreamBuffer->lpVtbl->SetCurrentPosition(lpDSBStreamBuffer, 0 );
						ASSERT(dsrval == DS_OK);
#ifdef DEBUG
						{
							DWORD dwWrite, dwPlay;
						dsrval = lpDSBStreamBuffer->lpVtbl->GetCurrentPosition(lpDSBStreamBuffer, &dwPlay, &dwWrite);
						ASSERT(dsrval == DS_OK);
						if (dwPlay != 0)
							DPF(0, "Couldn't set pos to 0");
						}
#endif 
						wiWave.bDonePlaying = FALSE;
						DPF(0, "calling play()");
                        dsrval = lpDSBStreamBuffer->lpVtbl->Play( lpDSBStreamBuffer,0, 0, DSBPLAY_LOOPING );                                                      
                    }
                    else
                    {
                        bPlaying = FALSE;
                        break;
                    }

                    bPlaying = TRUE;
					EnableWindow(hWndPlay,FALSE);
					EnableMenuItem(GetMenu( hWnd ), IDM_PLAY, MF_BYCOMMAND | MF_GRAYED );
                    EnableMenuItem(GetMenu( hWnd ), IDM_STOP, MF_BYCOMMAND | MF_ENABLED );
                    EnableWindow( hWndStop, TRUE );
                    DrawMenuBar( hWnd );
                    break;


                case IDM_STOP:
					DPF(0, "received a idm_stop");
					if (gfCloseOnDone)
						wiWave.bDonePlaying = TRUE;
                    if( bPlaying )
                        {
							bPlaying = FALSE;
							dsrval = lpDSBStreamBuffer->lpVtbl->Stop( lpDSBStreamBuffer );
							EnableMenuItem(GetMenu( hWnd ), IDM_STOP,MF_BYCOMMAND | MF_GRAYED );                                            
							EnableWindow(hWndStop, FALSE );
							DrawMenuBar( hWnd );
                        }
						// Short circuit to allow command-line forced shutdown
						if(!( HIWORD(wParam) & DSSTREAM_STOPF_NOREOPEN ) && !gfCloseOnDone )							
						{
							ResetWavePlayer();
				            EnableMenuItem(GetMenu( hWnd ), IDM_PLAY, MF_BYCOMMAND | MF_ENABLED );
							EnableWindow(hWndPlay, TRUE);
							DrawMenuBar( hWnd );
							break;
						}
	                    else
                        {
                        if( bFileOpen )
                            {
								DPF(0, "In Stop: Closing read file");
								WaveCloseReadFile( &wiWave.hmmio, &wiWave.pwfx );                                                            
								if (lpDirectSoundNotify)
									dsrval = lpDirectSoundNotify->lpVtbl->Release(lpDirectSoundNotify);
								lpDirectSoundNotify = NULL;

								if( lpDSBStreamBuffer )
									dsrval = lpDSBStreamBuffer->lpVtbl->Release(lpDSBStreamBuffer );
								lpDSBStreamBuffer = NULL;
					
								bFileOpen = FALSE;
								// The file is closed, so disable the close option
								EnableMenuItem( GetMenu( hWnd ), IDM_FILE_CLOSE,
												MF_BYCOMMAND | MF_GRAYED );
								EnableMenuItem( GetMenu( hWnd ), IDM_PLAY,
												MF_BYCOMMAND | MF_GRAYED );
								EnableWindow( hWndPlay, FALSE );
								DrawMenuBar( hWnd );
								PostMessage( hWnd, WM_DSSTREAM_PROGRESS, 0L, 0L );
								if( gfCloseOnDone &&
									!(HIWORD(wParam) && DSSTREAM_STOPF_NOEXIT))
								SendMessage( hWnd, WM_COMMAND,
									MAKEWPARAM( IDM_FILE_EXIT, 0 ), 0L );
	                            }
				            }
					    break;

                case IDM_FILE_EXIT:
                    DestroyWindow( hWnd );
                    break;
                }
            break;
#ifndef DEBUG
        case WM_GETMINMAXINFO:
    /*
     * We know exactly how big this window should be, and it's sort of a
     * little pop-up control panel, so we can disable window sizing by
     * forcing all the minimum and maximum sizes to be the calculated size.
     */
            lpMinMax = (LPMINMAXINFO)lParam;

            lpMinMax->ptMaxSize.x = CONTROL_SPACE_CX + 2*BORDER_SPACE_CX
                                    + BUTTON_CX + PAN_TB_CX + PAN_TEXT_CX
                                    + TEXT_SPACE_CX
                                    + 2*GetSystemMetrics( SM_CXBORDER );
            lpMinMax->ptMaxSize.y = 2*(BORDER_SPACE_CY
                                    + GetSystemMetrics( SM_CYBORDER ))
                                    + PAN_TB_CY + VOL_TB_CY + FREQ_TB_CY
                                    + PROG_TB_CY + 3*CONTROL_SPACE_CY
                                    + GetSystemMetrics( SM_CYMENU )
                                    + GetSystemMetrics( SM_CYCAPTION );

            lpMinMax->ptMinTrackSize.x = lpMinMax->ptMaxTrackSize.x
			                            = lpMinMax->ptMaxSize.x;

            lpMinMax->ptMinTrackSize.y = lpMinMax->ptMaxTrackSize.y
			                            = lpMinMax->ptMaxSize.y;
            break;
#endif
        case WM_HSCROLL:
            if(((HWND)lParam == hWndPan) && lpDSBStreamBuffer )
                {
                HandlePanScroll( (int)LOWORD(wParam), (int)HIWORD(wParam));
                }
            else if(((HWND)lParam == hWndVol) && lpDSBStreamBuffer )
                {
                HandleVolScroll( (int)LOWORD(wParam), (int)HIWORD(wParam));
                }
            else if(((HWND)lParam == hWndFreq) && lpDSBStreamBuffer )
                {
                HandleFreqScroll( (int)LOWORD(wParam), (int)HIWORD(wParam));
                }
            break;

        case WM_INITMENU:
	    {
	    HMENU	hSysMenu = GetSystemMenu( hWnd, FALSE );

	    EnableMenuItem( hSysMenu, SC_MAXIMIZE, MF_BYCOMMAND | MF_GRAYED );
	    EnableMenuItem( hSysMenu, SC_SIZE, MF_BYCOMMAND | MF_GRAYED );

	    if((HMENU)wParam != GetMenu( hWnd ))
                break;
            CheckMenuItem((HMENU)wParam, IDM_OPTIONS_ENUMDRIVERS,
                                bEnumDrivers ? MF_CHECKED : MF_UNCHECKED );
	    }
            break;

        case WM_DESTROY:
			/*
			 * Free all the DirectSound objects we created
			 */
	    SendMessage( hWnd, WM_COMMAND,
                          MAKEWPARAM( IDM_STOP, DSSTREAM_STOPF_NOREOPEN
						| DSSTREAM_STOPF_NOEXIT ), 0 );


            if( lpDS ) dsrval = lpDS->lpVtbl->Release( lpDS );

            WriteProfileString( "DSSTREAM", "EnumDrivers",
                                        bEnumDrivers ? "1" : "0" );

            PostQuitMessage( 0 );
            break;

        default:
            return DefWindowProc( hWnd, uMsg, wParam, lParam );
        }
    return 0L;
    } /* WindowProc */


/*****************************************************************************/
/* DLG_About()                                                               */
/*                                                                           */
/*   Dialog procedure for the Help...About... box which simply pops up a     */
/* little copyright message and brief program description.                   */
/*                                                                           */
/*****************************************************************************/
BOOL CALLBACK DLG_About( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
    {
    switch( msg )
        {
        case WM_INITDIALOG:
            break;

        case WM_COMMAND:
            switch( LOWORD(wParam))
                {
                case IDOK:
                    EndDialog( hDlg, FALSE );
                    return( TRUE );

                default:
                    break;
                }
            break;

        default:
            return( FALSE );
        }

    return( FALSE );
    }


/*****************************************************************************/
/* HandleCommDlgError()                                                      */
/*                                                                           */
/*    The function translates extended common dialog error codes into a      */
/* string resource ID, loads that string from our module, and displays it in */
/* a message box. This implementation only covers the general CD error codes.*/
/*                                                                           */
/*****************************************************************************/
int HandleCommDlgError( DWORD dwError )
    {
    char szTitle[128];
    UINT uMsgID;

    if( dwError == CDERR_DIALOGFAILURE )
        uMsgID = IDS_CDERR_DIALOGFAILURE;
    else
        uMsgID = (UINT)dwError + IDS_CDERR_GENERAL_BASE;

    LoadString( hInst, uMsgID, szTemp, sizeof(szTemp));
    LoadString( hInst, IDS_CDERR_TITLESTRING, szTitle, sizeof(szTitle));
    MessageBox( GetActiveWindow(), szTemp, szTitle,
                    MB_OK | MB_ICONEXCLAMATION );
		
    return( 0 );
    }


/*****************************************************************************/
/* StreamBufferSetup()                                                       */
/*                                                                           */
/* This function uses the filename stored in the global character array to*/
/* open a WAVE file. Then it creates a secondary DirectSoundBuffer object    */
/* which will later be used to stream that file from disk during playback.   */
/*                                                                           */
/*****************************************************************************/
int StreamBufferSetup( void )
    {
    DSBUFFERDESC dsbd;
    HRESULT      dsRetVal;

    int nChkErr;
	int nRem;

    /* This portion of the WAVE I/O is patterned after what's in DSTRWAVE, which
     * was in turn adopted from WAVE.C which is part of the DSSHOW sample.
     */

    if(( nChkErr = WaveOpenFile( szFileBuffer, &wiWave.hmmio, &wiWave.pwfx, &wiWave.mmckInRIFF )) != 0 )
        {
        ErrorMessageBox( IDS_ERROR_WAVEFILEOPEN, MB_ICONEXCLAMATION );
        return( ERR_WAVE_OPEN_FAILED );
        }

    if( wiWave.pwfx->wFormatTag != WAVE_FORMAT_PCM )
        {
        ErrorMessageBox( IDS_ERROR_WAVENOTPCM, MB_ICONEXCLAMATION );
        WaveCloseReadFile( &wiWave.hmmio, &wiWave.pwfx );
        return( ERR_WAVE_INVALID_FORMAT );
		}
    // Seek to the data chunk. mmck.ckSize will be the size of all the data in the file.
    if(( nChkErr = WaveStartDataRead( &wiWave.hmmio, &wiWave.mmck, &wiWave.mmckInRIFF )) != 0 )
        {
        ErrorMessageBox( IDS_ERROR_WAVESEEKFAILED, MB_ICONEXCLAMATION );
        WaveCloseReadFile( &wiWave.hmmio, &wiWave.pwfx );
        return( ERR_WAVE_CORRUPTED_FILE );
        }
	
    // Calculate a buffer length 3 sec. long. This should be an integral number of the
	// number of bytes in one notification period. 
	wiWave.dwNotifySize = wiWave.pwfx->nSamplesPerSec * 3 * (DWORD)wiWave.pwfx->nBlockAlign;
	wiWave.dwNotifySize = wiWave.dwNotifySize/NUM_PLAY_NOTIFICATIONS;
	// the notify size should be an intergral multiple of the nBlockAlignvalue.
	if ((nRem = wiWave.dwNotifySize%(DWORD)wiWave.pwfx->nBlockAlign) != 0)
	{
		wiWave.dwNotifySize += (wiWave.pwfx->nBlockAlign - nRem);
	}
	wiWave.dwBufferSize = wiWave.dwNotifySize * NUM_PLAY_NOTIFICATIONS;	
    DPF(0, "BufferSize = %lu ", wiWave.dwBufferSize);

#ifdef DEBUG
    wsprintf( szDebug, "BufferSize = %lu", wiWave.dwBufferSize );
    ListBox_AddString( hWndList, szDebug );
#endif

     //Create the secondary DirectSoundBuffer object to receive our sound data.
    memset( &dsbd, 0, sizeof( DSBUFFERDESC ));
    dsbd.dwSize = sizeof( DSBUFFERDESC );
    // Use new GetCurrentPosition() accuracy (DirectX 2 feature)
    dsbd.dwFlags = DSBCAPS_CTRLPOSITIONNOTIFY| DSBCAPS_CTRLDEFAULT | DSBCAPS_GETCURRENTPOSITION2 | gdwFocus;
    dsbd.dwBufferBytes = wiWave.dwBufferSize;

    //Set Format properties according to the WAVE file we just opened
    dsbd.lpwfxFormat = wiWave.pwfx;
    
	dsRetVal = lpDS->lpVtbl->CreateSoundBuffer( lpDS, &dsbd,&lpDSBStreamBuffer,NULL );						
    if( dsRetVal != DS_OK )
        {
        ErrorMessageBox( IDS_ERROR_DSBCREATE, MB_ICONEXCLAMATION );
        return( ERR_CREATEDSB_FAILED );
        }

    wiWave.lpDSBStreamBuffer = lpDSBStreamBuffer;
    wiWave.bFoundEnd = FALSE;
	wiWave.dwNextWriteOffset = 0;
    wiWave.bLoopFile = Button_GetCheck( hWndLoopCheck );

	// now get the pointer to the notification interface.
	dsRetVal = IDirectSoundNotify_QueryInterface(lpDSBStreamBuffer, &IID_IDirectSoundNotify, &((LPVOID)lpDirectSoundNotify));
	if (dsRetVal != DS_OK)
	{	
		ErrorMessageBox(IDS_ERROR_QINOTIFY_FAILED, MB_ICONEXCLAMATION);
	    return (dsRetVal);
    }

	// Fill data in the buffer.
    FillDataBuffer();	

	// we're set to play now.
    wiWave.bDonePlaying = FALSE;

#ifdef DEBUG
    wsprintf( szDebug, "wiWave.dwBufferSize = %lu", wiWave.dwBufferSize );
    DPF( 3, "StreamBufferSetup Debug" );
    DPF( 3, szDebug );
#endif

    SendMessage( hWndVol, TBM_SETPOS, TRUE, VOL_MAX );
    SendMessage( hWndPan, TBM_SETPOS, TRUE, PAN_CENTER );
    SendMessage( hWndFreq, TBM_SETPOS, TRUE,(LPARAM)wiWave.pwfx->nSamplesPerSec / FREQ_MULTIPLIER );
    PostMessage( hWndMain, WM_DSSTREAM_PROGRESS, 0L, 0L );
    UpdateFromControls();
    return( 0 );
    }


/*****************************************************************************/
/* ResetWavePlayer()                                                         */
/*                                                                           */
/*  Performs a subset of the above operations (in StreamBufferSetup). Things */
/* not done include creating a DSB and opening the file (it's already open). */
/*                                                                           */
/*****************************************************************************/
void ResetWavePlayer( void )
    {
	int nChkErr = DS_OK;
	DPF(1, "Resetting wave player");
	ASSERT(bPlaying == FALSE);

    /* Seek to the data chunk */
    if(( nChkErr = WaveStartDataRead( &wiWave.hmmio, &wiWave.mmck, &wiWave.mmckInRIFF )) != 0 )
        {
		// This shouldn't happen, since we've done this before.
        DPF(0, "Error seeking to file in ResetWavePlayer");
		return;	
        }

    wiWave.bFoundEnd = FALSE;
	wiWave.dwNextWriteOffset = 0;
	
	DPF(0, "Reset: Filldatabuffer");
    FillDataBuffer();

    wiWave.bDonePlaying = FALSE;
    PostMessage( hWndMain, WM_DSSTREAM_PROGRESS, 0L, 0L );
    }


/*****************************************************************************/
/* FillDataBuffer()                                                          */
/*                                                                           */
/*   This function fills the sound buffer with a block of data, starting at  */
/* the current read position.  The entire buffer is filled.                  */
/*                                                                           */
/*****************************************************************************/
 void FillDataBuffer( void )
 {
    LPBYTE  lpWrite1, lpWrite2;
    DWORD	dwLen1, dwLen2;
    UINT	uActualBytesWritten;
    int		nChkErr;
    HRESULT	dsRetVal;
	DWORD dwBytes = wiWave.dwBufferSize; 

	// This is the initial read. So we fill the entire buffer.
	// This will not wrap around so the 2nd pointers will be NULL.
    dsRetVal = lpDSBStreamBuffer->lpVtbl->Lock( lpDSBStreamBuffer, 0, dwBytes,
												&((LPVOID)lpWrite1), &dwLen1,
												&(LPVOID)lpWrite2, &dwLen2, 0 );
	ASSERT(lpWrite2 == NULL);	
	ASSERT(dwLen2 == 0);

	if (dwLen1 != dwBytes)
	{
		DPF(0, "FillDataBuffer: dwBytes != dwLen1");
	}


    if( dsRetVal != DS_OK )
	{
		ASSERT(FALSE);
		return; 
	}

	ASSERT(dwLen1);
	ASSERT( NULL != lpWrite1 );
	ASSERT(wiWave.dwNextWriteOffset < wiWave.dwBufferSize);

    nChkErr = WaveReadFile( wiWave.hmmio, (UINT)dwLen1, lpWrite1,
                            &wiWave.mmck, &uActualBytesWritten );
	// if the number of bytes written is less than the 
	// amount we requested, we have a short file.
	if (uActualBytesWritten < dwLen1)
	{
		DPF(0, "FillDataBuffer: Actual written is less than dwlen1");
		if (!wiWave.bLoopFile)
		{
			// we set the bFoundEnd flag if the length is less than
			// one notify period long which is when the first notification comes in.
			// The next notification will then call send a message to process a stop. 
			if (uActualBytesWritten < wiWave.dwNotifySize)
				wiWave.bFoundEnd = TRUE;
			// Fill in silence for the rest of the buffer.
				DPF(0, "Filling in silence");
				FillMemory(lpWrite1+uActualBytesWritten, dwLen1-uActualBytesWritten, 
						(BYTE)(wiWave.pwfx->wBitsPerSample == 8 ? 128 : 0));
		}
		else
		{
			// we are looping.
			UINT uWritten = uActualBytesWritten;	// from previous call above.
			while (uWritten < dwLen1)
			{	// this will keep reading in until the buffer is full. For very short files.
				nChkErr = WaveStartDataRead( &wiWave.hmmio, &wiWave.mmck, &wiWave.mmckInRIFF );
				ASSERT(nChkErr == 0);	// we've already this before so shouldn't fail.
				nChkErr = WaveReadFile(wiWave.hmmio, (UINT)dwLen1-uWritten, 
								lpWrite1 + uWritten, &wiWave.mmck, &uActualBytesWritten);
				uWritten += uActualBytesWritten;
			} // while
			ASSERT(wiWave.bFoundEnd == FALSE);
		} // else
	}

		// now unlock the buffer.
	dsRetVal = lpDSBStreamBuffer->lpVtbl->Unlock( lpDSBStreamBuffer, (LPVOID)lpWrite1, dwLen1,		NULL, 0 );
                                                                             
	wiWave.dwNextWriteOffset += dwLen1;	
	// this is a circular buffer. Do mod buffersize.
	if (wiWave.dwNextWriteOffset >= wiWave.dwBufferSize)
		wiWave.dwNextWriteOffset -= wiWave.dwBufferSize; 

	DPF(3, "Setting dwProgress = 0");
	wiWave.dwProgress = 0;
	wiWave.dwLastPos = 0;
}


/*****************************************************************************/
/* CreateChildren()                                                          */
/*                                                                           */
/*   This function creates a bunch of child controls for the main window.    */
/* Most of them are used for controling various things about a playing sound */
/* file, like volume and panning. Returns FALSE if no errors, TRUE otherwise.*/
/*                                                                           */
/*****************************************************************************/
int CreateChildren( RECT crect )
    {
    SIZE  Size;
    HDC   hDC;
    int	  x, y;
    UINT  uType;
    char  szTemplate[128], szType[32];
    LPSTR lpszControl;

    LoadString( hInst, IDS_ERROR_CHILDTEMPLATE, szTemplate, sizeof(szTemplate));

    /* Don't handle failure for this one, because the app will still run fine */
    hWndBar = CreateWindow( "static", NULL,
                            WS_CHILD | WS_VISIBLE | SS_ETCHEDHORZ,
                            0, 0, crect.right, 2, hWndMain,
                            (HMENU)0, hInst, NULL );

    hDC = GetDC( hWndMain );
    if( !GetTextExtentPoint32( hDC, szPan, strlen(szPan), &Size ))
        {
        ErrorMessageBox( IDS_ERROR_GETTEXTEXTENT, MB_ICONEXCLAMATION );
        ReleaseDC( hWndMain, hDC );
        return( TRUE );
        }
    ReleaseDC( hWndMain, hDC );

    y = BORDER_SPACE_CY;

    /* STATIC control -- text label for the pan trackbar */
    if(( hWndPanText = CreateWindow( "static", szPan,
                                    WS_CHILD | WS_VISIBLE | SS_LEFTNOWORDWRAP, 
                                    BORDER_SPACE_CX + PAN_TB_CX + TEXT_SPACE_CX,
                                    y + (PAN_TB_CY - Size.cy)/2,
                                    PAN_TEXT_CX, Size.cy,
                                    hWndMain, (HMENU)0, hInst, NULL)) == NULL )
        {
        lpszControl = szPan;
	uType = IDS_ERROR_STATICTEXT;
        goto DISPLAY_CREATE_FAILURE;
        }

    /* PAN (left to right balance) trackbar control */
    if(( hWndPan = CreateWindow( TRACKBAR_CLASS, NULL,
                                WS_CHILD | WS_VISIBLE | TBS_HORZ | TBS_BOTTOM,
                                BORDER_SPACE_CX,
                                y, PAN_TB_CX, PAN_TB_CY,
                                hWndMain, (HMENU)0, hInst, NULL)) == NULL )
        {
        lpszControl = szPan;
	uType = IDS_ERROR_TRACKBAR;
        goto DISPLAY_CREATE_FAILURE;
	}

    SendMessage( hWndPan, TBM_SETRANGE, FALSE, MAKELONG( PAN_MIN, PAN_MAX )); 
    SendMessage( hWndPan, TBM_SETPOS, TRUE, PAN_CENTER );
    SendMessage( hWndPan, TBM_SETPAGESIZE, 0L, PAN_PAGESIZE );

    y += PAN_TB_CY + CONTROL_SPACE_CY;

    /* STATIC control -- text label for the volume trackbar */
    if(( hWndVolText = CreateWindow( "static", szVolume,
                                    WS_CHILD | WS_VISIBLE | SS_LEFTNOWORDWRAP, 
                                    BORDER_SPACE_CX + VOL_TB_CX + TEXT_SPACE_CX,
                                    y + (VOL_TB_CY - Size.cy)/2,
                                    VOL_TEXT_CX, Size.cy,
                                    hWndMain, (HMENU)0, hInst, NULL)) == NULL )
        {
        lpszControl = szVolume;
	uType = IDS_ERROR_STATICTEXT;
        goto DISPLAY_CREATE_FAILURE;
	}

    /* Create the VOLUME trackbar */
    if(( hWndVol = CreateWindow( TRACKBAR_CLASS, NULL,
                                WS_CHILD | WS_VISIBLE | TBS_HORZ | TBS_BOTTOM,
                                BORDER_SPACE_CX,
                                y, VOL_TB_CX, VOL_TB_CY,
                                hWndMain, (HMENU)0, hInst, NULL)) == NULL )
        {
        lpszControl = szVolume;
	uType = IDS_ERROR_TRACKBAR;
        goto DISPLAY_CREATE_FAILURE;
	}

    SendMessage( hWndVol, TBM_SETRANGE, FALSE,
                                        MAKELONG( VOL_MIN, VOL_MAX ));
    SendMessage( hWndVol, TBM_SETPOS, TRUE, VOL_MAX );
    SendMessage( hWndVol, TBM_SETPAGESIZE, 0L, VOL_PAGESIZE );

    y += VOL_TB_CY + CONTROL_SPACE_CY;

    /* STATIC control -- text label for the frequency trackbar */
    if(( hWndFreqText = CreateWindow( "static", szFrequency,
                                    WS_CHILD | WS_VISIBLE | SS_LEFTNOWORDWRAP, 
                                    BORDER_SPACE_CX + FREQ_TB_CX + TEXT_SPACE_CX,
                                    y + (FREQ_TB_CY - Size.cy)/2,
                                    FREQ_TEXT_CX, Size.cy,
                                    hWndMain, (HMENU)0, hInst, NULL)) == NULL )
        {
        lpszControl = szFrequency;
	uType = IDS_ERROR_STATICTEXT;
        goto DISPLAY_CREATE_FAILURE;
	}

    /* Create the FREQUENCY trackbar */
    if(( hWndFreq = CreateWindow( TRACKBAR_CLASS, NULL,
                                WS_CHILD | WS_VISIBLE | TBS_HORZ | TBS_BOTTOM,
                                BORDER_SPACE_CX,
                                y, FREQ_TB_CX, FREQ_TB_CY,
                                hWndMain, (HMENU)0, hInst, NULL)) == NULL )
        {
        lpszControl = szFrequency;
	uType = IDS_ERROR_TRACKBAR;
        goto DISPLAY_CREATE_FAILURE;
	}

    SendMessage( hWndFreq, TBM_SETRANGE, FALSE, MAKELONG( FREQ_MIN, FREQ_MAX ));
    SendMessage( hWndFreq, TBM_SETPOS, TRUE, FREQ_MAX );
    SendMessage( hWndFreq, TBM_SETPAGESIZE, 0L, FREQ_PAGESIZE );

    y += FREQ_TB_CY + CONTROL_SPACE_CY;

    /* STATIC control -- text label for the progress trackbar */
    if(( hWndProgText = CreateWindow( "static", szProgress,
                                    WS_CHILD | WS_VISIBLE | SS_LEFTNOWORDWRAP, 
                                    BORDER_SPACE_CX + PROG_TB_CX + TEXT_SPACE_CX,
                                    y + (PROG_TB_CY - Size.cy)/2,
                                    PROG_TEXT_CX, Size.cy,
                                    hWndMain, (HMENU)0, hInst, NULL)) == NULL )
        {
        lpszControl = szProgress;
	uType = IDS_ERROR_STATICTEXT;
        goto DISPLAY_CREATE_FAILURE;
	}

    /* Create the PROGRESSS trackbar */
    if(( hWndProg = CreateWindow( TRACKBAR_CLASS, NULL,
                                WS_CHILD | WS_VISIBLE | TBS_HORZ
				| TBS_BOTTOM | WS_DISABLED,
                                BORDER_SPACE_CX,
                                y, PROG_TB_CX, PROG_TB_CY,
                                hWndMain, (HMENU)0, hInst, NULL)) == NULL )
        {
        lpszControl = szProgress;
	uType = IDS_ERROR_TRACKBAR;
        goto DISPLAY_CREATE_FAILURE;
	}

    SendMessage( hWndProg, TBM_SETRANGE,
    			FALSE, MAKELPARAM( PROG_MIN, PROG_MAX ));
    SendMessage( hWndProg, TBM_SETPOS, TRUE, 0L );

    x = BORDER_SPACE_CX + PAN_TEXT_CX + TEXT_SPACE_CX
    		+ PAN_TB_CX + CONTROL_SPACE_CX;
    y += PROG_TB_CY;
    y -= 2*(BUTTON_CY + BUTTON_SPACE_CY) + CHECK_CY;

    /* Create the LOOPED CHECKBOX */
    LoadString( hInst, IDS_CHECK_LOOPED, szTemp, sizeof(szTemp));
    if(( hWndLoopCheck = CreateWindow( "button", szTemp,
                                WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
                                x, y, CHECK_CX, CHECK_CY, hWndMain,
                                (HMENU)IDC_LOOPCHECK, hInst, NULL )) == NULL )
        {
        lpszControl = szTemp;
	uType = IDS_ERROR_CHECK;
        goto DISPLAY_CREATE_FAILURE;
	}
    y += CHECK_CY + BUTTON_SPACE_CY;

    /* Create the PLAY BUTTON */
    LoadString( hInst, IDS_BUTTON_PLAY, szTemp, sizeof(szTemp));
    if(( hWndPlay = CreateWindow( "button", szTemp,
                                    WS_CHILD | WS_VISIBLE | WS_DISABLED,
                                    x, y, BUTTON_CX, BUTTON_CY, hWndMain,
                                    (HMENU)IDM_PLAY, hInst, NULL )) == NULL )
        {
        lpszControl = szTemp;
	uType = IDS_ERROR_BUTTON;
        goto DISPLAY_CREATE_FAILURE;
	}
    y += BUTTON_CY + BUTTON_SPACE_CY;

    /* Create the STOP BUTTON */
    LoadString( hInst, IDS_BUTTON_STOP, szTemp, sizeof(szTemp));
    if(( hWndStop = CreateWindow( "button", szTemp,
                                    WS_CHILD | WS_VISIBLE | WS_DISABLED,
                                    x, y, BUTTON_CX, BUTTON_CY, hWndMain,
                                    (HMENU)IDM_STOP, hInst, NULL )) == NULL )
        {
        lpszControl = szTemp;
	uType = IDS_ERROR_BUTTON;
        goto DISPLAY_CREATE_FAILURE;
	}

    UpdateFromControls();
    goto RETURN_NORMAL;

DISPLAY_CREATE_FAILURE:
    LoadString( hInst, uType, szType, sizeof(szType));
    wsprintf( szTemp, szTemplate, lpszControl, szType );
    MessageBox( GetActiveWindow(), szTemp,
                        szAppTitle, MB_OK | MB_ICONEXCLAMATION );
    return( TRUE );

RETURN_NORMAL:
    return( FALSE );
    }


/********************************************************************************/
/* UpdateFromControls()                                                         */
/*                                                                              */
/*    This function gets all the required values from the DirectSoundBuffer and */
/* updates the screen interface controls.                                       */
/*                                                                              */
/********************************************************************************/
void UpdateFromControls( void )
    {
    long	lPan, lVol, lFreq;
    HRESULT hr;

    lPan = (LONG)SendMessage( hWndPan, TBM_GETPOS, (WPARAM)0, (LPARAM)0 );
    lVol = (LONG)SendMessage( hWndVol, TBM_GETPOS, (WPARAM)0, (LPARAM)0 );
    lFreq = (LONG)SendMessage( hWndFreq, TBM_GETPOS, (WPARAM)0, (LPARAM)0 );

    /* Set the volume and then the pan */
    if( lpDSBStreamBuffer )
        {
        /* Set the volume */
        wsprintf( szTemp, "%s: %lidB", szVolume,
                                            ( lVol + VOL_SHIFT ) / VOL_DIV );
        Static_SetText( hWndVolText, szTemp );

        hr = lpDSBStreamBuffer->lpVtbl->SetVolume( lpDSBStreamBuffer,
                                            (((lVol+VOL_SHIFT) * VOL_MULT)) );
        if( hr != 0 )
            DPF( 0, "Unable to SetVolume in UpdateFromControls()" );
        else
            {
            wsprintf( szDebug, "Set volume to %lidB",
                                            ( lVol + VOL_SHIFT ) / VOL_DIV );
            DPF( 3, szDebug );
            }

        /* Set the Pan */
        wsprintf( szTemp, "%s: %lidB", szPan, ( lPan + PAN_SHIFT ) / PAN_DIV );
        Static_SetText( hWndPanText, szTemp );

        hr = lpDSBStreamBuffer->lpVtbl->SetPan( lpDSBStreamBuffer,
                                            (((lPan+PAN_SHIFT) * PAN_MULT)) );
        if( hr != 0 )
            DPF( 0, "Unable to SetPan in UpdateFromControls()" );
        else
            {
            wsprintf( szDebug, "Set pan to %lidB",
                                            ( lPan + PAN_SHIFT ) / PAN_DIV );
            DPF( 3, szDebug );
            }

        /* Set the frequency */
        wsprintf( szTemp, "%s: %liHz", szFrequency, lFreq * FREQ_MULTIPLIER );
        Static_SetText( hWndFreqText, szTemp );

        hr = lpDSBStreamBuffer->lpVtbl->SetFrequency( lpDSBStreamBuffer,
                                                        lFreq * FREQ_MULTIPLIER);
        if( hr != 0 )
            DPF( 0, "Unable to SetFrequency in UpdateFromControls()" );
        else
            {
            wsprintf( szDebug, "Set frequency to %liHz", lFreq*FREQ_MULTIPLIER );
            DPF( 3, szDebug );
            }
        }
        return;
    }


/********************************************************************************/
/* HandlePanScroll()                                                            */
/*                                                                              */
/*   Handles the pan trackbar scroll when a WM_HSCROLL is received.             */
/*                                                                              */
/********************************************************************************/
void HandlePanScroll( int nCode, int nPos )
    {
    long  lPan, lDelta;

    lPan = (LONG)SendMessage( hWndPan, TBM_GETPOS, (WPARAM)0, (LPARAM)0 );

    switch( nCode )
        {
        case TB_LINEUP:
            if( lPan >= PAN_MIN - 1 )
                lDelta = -1;
            break;
        case TB_LINEDOWN:
            if( lPan <= PAN_MAX + 1 )
                lDelta = 1;
            break;
        case TB_PAGEUP:
            if( lPan >= PAN_MIN - PAN_PAGESIZE )
                lDelta = -16;
            break;
        case TB_PAGEDOWN:
            if( lPan <= PAN_MAX + PAN_PAGESIZE )
                lDelta = 16;
            break;
        case TB_ENDTRACK:
            return;
        default:
            lDelta = 0;
        }

    if( lDelta )
        SendMessage( hWndPan, TBM_SETPOS, TRUE, lPan + lDelta );
    else
        SendMessage( hWndPan, TBM_SETPOS, TRUE, (long)nPos );
    UpdateFromControls();
    }


/********************************************************************************/
/* HandleVolScroll()                                                            */
/*                                                                              */
/*   Handles the volume trackbar scrolling when a WM_HSCROLL is received.       */
/*                                                                              */
/********************************************************************************/
void HandleVolScroll( int nCode, int nPos )
    {
    long  lVol, lDelta;

    lVol = (LONG)SendMessage( hWndVol, TBM_GETPOS, (WPARAM)0, (LPARAM)0 );

    switch( nCode )
        {
        case TB_LINEDOWN:
            if( lVol <= VOL_MAX - 1 )
                lDelta = 1;
            break;
        case TB_LINEUP:
            if( lVol >= VOL_MIN + 1 )
                lDelta = -1;
            break;
        case TB_PAGEDOWN:
            if( lVol <= VOL_MAX - VOL_PAGESIZE )
                lDelta = 10;
            break;
        case TB_PAGEUP:
            if( lVol >= VOL_MIN + VOL_PAGESIZE )
                lDelta = -10;
            break;
        case TB_ENDTRACK:
            return;
        default:
            lDelta = 0;
        }

    if( lDelta )
        SendMessage( hWndVol, TBM_SETPOS, TRUE, (lVol + lDelta));
    else
        SendMessage( hWndVol, TBM_SETPOS, TRUE, (long)nPos );
    UpdateFromControls();
    }


/********************************************************************************/
/* HandleFreqScroll()                                                           */
/*                                                                              */
/*   Handles the volume trackbar scrolling when a WM_HSCROLL is received.       */
/*                                                                              */
/********************************************************************************/
void HandleFreqScroll( int nCode, int nPos )
    {
    long  lFreq, lDelta;

    lFreq = (LONG)SendMessage( hWndFreq, TBM_GETPOS, (WPARAM)0, (LPARAM)0 );

    switch( nCode )
        {
        case TB_LINEDOWN:
            if( lFreq <= FREQ_MAX-1 )
                lDelta = 1;
            break;
        case TB_LINEUP:
            if( lFreq >= FREQ_MIN+1 )
                lDelta = -1;
            break;
        case TB_PAGEDOWN:
            if( lFreq <= FREQ_MAX - FREQ_PAGESIZE )
                lDelta = 10;
            break;
        case TB_PAGEUP:
            if( lFreq >= FREQ_MIN + FREQ_PAGESIZE )
                lDelta = -10;
            break;
        case TB_ENDTRACK:
            return;
        default:
            lDelta = 0;
        }

    if( lDelta )
        SendMessage( hWndFreq, TBM_SETPOS, TRUE, (lFreq + lDelta));
    else
        SendMessage( hWndFreq, TBM_SETPOS, TRUE, (long)nPos );
    UpdateFromControls();
    }


/****************************************************************************/
/* ErrorMessageBox()                                                        */
/*                                                                          */
/*   A little routine to load error messages from the string resource table */
/* and pop them up in a MessageBox() for the world to see. The dwMBFlags    */
/* parameter allows the caller to specify the type of icon to use.          */
/*                                                                          */
/****************************************************************************/
void ErrorMessageBox( UINT uID, DWORD dwMBFlags )
    {
    LoadString( hInst, uID, szTemp, sizeof(szTemp));
    MessageBox( GetActiveWindow(), szTemp, szAppTitle, MB_OK | dwMBFlags );
    }


/****************************************************************************/
/* BuildTitleBar()                                                          */
/*                                                                          */
/*   Small routine to build and set the title bar text depending on whether */
/* or not a file is open.                                                   */
/****************************************************************************/
void BuildTitleBarText( void )
    {
    char szTitle[ sizeof(szAppCaption) + MAX_PATH + sizeof(" - ")];

    lstrcpy( szTitle, szAppCaption );
    if( bFileOpen )
	{
	lstrcat( szTitle, " - " );
	lstrcat( szTitle, szFileTitle );
	}
    SetWindowText( hWndMain, szTitle );
    }


/****************************************************************************/
/* GetMediaStartPath()                                                      */
/*                                                                          */
/*   This helper function attempts to get the media directory for Direct3D, */
/* which is where all the installed DX wave files go. If it can't find that */
/* it settles for the media sub-directory of the Windows directory.         */
/****************************************************************************/
void GetMediaStartPath( void )
    {
    HKEY    hReg;
    DWORD   cbStartPathLen;

    if( ERROR_SUCCESS != RegOpenKeyEx( HKEY_LOCAL_MACHINE,
			gszRegKeyDirect3D,
			0, KEY_READ, &hReg ))
	{
        goto REG_OPEN_FAILED;
	}
    else
	{
	// Query the Registry for the path to the media directory
	cbStartPathLen = sizeof( szCDStartPath );
	if( ERROR_SUCCESS != RegQueryValueEx( hReg, gszRegValueD3DPath,
				NULL, NULL,
				szCDStartPath, &cbStartPathLen ))
	    {
	    goto REG_OPEN_FAILED;
	    }
	RegCloseKey( hReg );
	hReg = NULL;
	}

    return;

REG_OPEN_FAILED:
    // Start off by getting the Windows directory -- we're trying to build a
    // file path like "C:\WINDOWS\MEDIA", but the WINDOWS directory could be
    // named anything, so we must ask.
    GetWindowsDirectory( szCDStartPath, sizeof(szCDStartPath));
    // If there's no trailing backslash, append one
    if( lstrcmp( &szCDStartPath[lstrlen(szCDStartPath)], TEXT("\\") ))
	lstrcat( szCDStartPath, TEXT("\\"));
    // Now add on the MEDIA part of the path
    lstrcat( szCDStartPath, TEXT("MEDIA"));
    }


void LoadFromCommandLine( LPSTR lpszCmd )
    {
    LPSTR lpsz = lpszCmd;
    LPSTR lpToken;
    BOOL  fStartPlaying = FALSE, fStartLooping = FALSE;
    char  szToken[MAX_TOKEN_LEN+1];
    int   i;

    if( !lpsz )
	return;

    // Clear leading spaces
    while( *lpsz == ' ' )
	lpsz++;
    
    // If we need to accept more command-line parameters later, we can
    // extend the code below into a loop that searchs for each one.
    while( *lpsz == '/' || *lpsz == '-' )
	{
	// Don't advance lpsz until we're sure we really should be reading
	// this string (i.e. we recognize that it's the play command
	lpToken = ++lpsz;
	for( i = 0; i < MAX_TOKEN_LEN; i++ )
	    {
	    if( !*lpToken || *lpToken == ' ' )
		break;
	    szToken[i] = *lpToken++;
	    }
	szToken[i] = 0;

	if( !lstrcmpi( szToken, gszPlayToken ))
	    {
	    // Automagically start playing the file
	    fStartPlaying = TRUE;
	    lpsz = lpToken;
	    }
	else if( !lstrcmpi( szToken, gszLoopToken ))
	    {
	    // Set the player in looping mode at startup
	    fStartLooping = TRUE;
	    lpsz = lpToken;
	    }
	else if( !lstrcmpi( szToken, gszStickyToken ))
	    {
	    // Use Sticky Focus for the buffer
	    gdwFocus = DSBCAPS_STICKYFOCUS;
	    lpsz = lpToken;
	    }
	else if( !lstrcmpi( szToken, gszGlobalToken ))
	    {
	    // Use Global Focus for the buffer
	    gdwFocus = DSBCAPS_GLOBALFOCUS;
	    lpsz = lpToken;
	    }
	else if( !lstrcmpi( szToken, gszCloseToken ))
	    {
	    // "/close" will cause the program to shutdown after it's done
	    // playing the file that was presumably loaded at the command-line
	    gfCloseOnDone = TRUE;
	    lpsz = lpToken;
	    }
	else
	    {
	    // Unrecognized parameter followed the slash, so skip over it
	    // and find the next break
	    while( *lpsz && *lpsz != ' ' )
		lpsz++;
	    }
	// Clear any spaces out again
	while( *lpsz == ' ' )
	    lpsz++;
	}

    // If that's all that was on the command-line, simply return
    if( !*lpsz )
	return;

    // ASSUMPTION: We assume that a single filename is the only remaining
    // parameter.  This works out okay because anything else will fail in the
    // file load inside StreamBufferSetup();
    lstrcpy( szFileBuffer, lpsz );

    // Search backwards and find the last backslash, stopping at the
    // beginning of the file name
    lpsz = &szFileBuffer[lstrlen(szFileBuffer)];

    while( lpsz > szFileBuffer )
	{
	if( *(lpsz-1) == '\\' )
	    {
	    break;
	    }
	lpsz--;
	}
    // Fake the szFileTitle, which normally gets set by the Common Dialog
    lstrcpy( szFileTitle, lpsz );
    lstrcpy( szCDStartPath, szFileBuffer );
    szCDStartPath[lpsz-szFileBuffer] = 0;

    if( fStartLooping )
	{
	// Allowing auto-close when the user will have plenty of time to click
	// stop would cause the app to shutdown right as they hit the button,
	// which is weird behavior.
	gfCloseOnDone = FALSE;
	Button_SetCheck( hWndLoopCheck, TRUE );
	}

    if( StreamBufferSetup() != 0 )
	{
	// Error opening the WAVE file so abort
	return;
	}
    else
	{
	bFileOpen = TRUE;
	EnableMenuItem( GetMenu( hWndMain ), IDM_PLAY,
			MF_BYCOMMAND | MF_ENABLED );
	EnableWindow( hWndPlay, TRUE );
	EnableMenuItem( GetMenu( hWndMain ), IDM_FILE_CLOSE,
			MF_BYCOMMAND | MF_ENABLED );
	DrawMenuBar( hWndMain );
	BuildTitleBarText();

	if( fStartPlaying )
	    SendMessage( hWndMain, WM_COMMAND, MAKEWPARAM( IDM_PLAY, 0 ), 0L );
	}
    }


// ==========================================================
// SetupNotifications
//	Sets notifications and also creates the events. 
// ==========================================================
int SetupNotifications(void)
{
	int hr = DS_OK;
	DSBPOSITIONNOTIFY dsbPosNotify[NUM_PLAY_NOTIFICATIONS +1 ];	
	DWORD dwSize = wiWave.dwNotifySize;	
	DWORD dwThreadId;
	int i;

	// Create the 2 events. One for Play one for stop.
	hNotifyEvent[0] = CreateEvent(NULL, FALSE, FALSE, NULL);
	ASSERT(hNotifyEvent[0]);
	hNotifyEvent[1] = CreateEvent(NULL, FALSE, FALSE, NULL);
	ASSERT(hNotifyEvent[1]);

		// setup the first one.	
	dsbPosNotify[0].dwOffset = dwSize;
	dsbPosNotify[0].hEventNotify = hNotifyEvent[0];
	DPF(0, "Set notifies for position %lu", dsbPosNotify[0].dwOffset);

	for (i = 1; i < NUM_PLAY_NOTIFICATIONS; i++)
	{
		dsbPosNotify[i].dwOffset = dsbPosNotify[i-1].dwOffset + dwSize;
		dsbPosNotify[i].hEventNotify = hNotifyEvent[0];				
		DPF(0, "Set notifies for positions %lu", dsbPosNotify[i].dwOffset);
	}

	dsbPosNotify[i-1].dwOffset -= 1;
	// set the stop notification.
	dsbPosNotify[i].dwOffset = DSBPN_OFFSETSTOP;
	dsbPosNotify[i].hEventNotify = hNotifyEvent[1];

	// Now create the thread to wait on the events created.
	if (CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)HandleNotifications, NULL, 0, &dwThreadId) == NULL)
	{
		DPF(0, "CreateThread failed");
		goto HandleErr;
	}
	else
		DPF(0, "Created thread");

	// setup notification
	hr = lpDirectSoundNotify->lpVtbl->SetNotificationPositions(lpDirectSoundNotify, 
																NUM_PLAY_NOTIFICATIONS +1,
																dsbPosNotify);

HandleErr:
	if (hr != DS_OK)
	{	if (hr == DSERR_INVALIDPARAM)
			DPF(0, "SetupNotificationPos failed. Invalid Param");
		if (hr == DSERR_OUTOFMEMORY)
			DPF(0, "SetupNotificationPos failed. OutOfMemory");
		CloseHandle(hNotifyEvent[0]);
		CloseHandle(hNotifyEvent[1]);
		hNotifyEvent[0] = hNotifyEvent[1] = (HANDLE)NULL;
	}
#ifdef DEBUG
	else
	{
		DPF(3, "SetNotificationPos succeeded.");
	}
#endif

	return (hr);
}
