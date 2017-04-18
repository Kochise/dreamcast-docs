/*==========================================================================
 *
 *  Copyright (C) 1995-1997 Microsoft Corporation. All Rights Reserved.
 *
 *  File:       shell.c
 *  Content:    Direct Sound show-off.
 *  This app basically uses the direct sound api's and pops up some
 *  controls that the user can play with at runtime to change
 *  the sound frequency, panning, volume, etc.   It has a few
 *  other functions built in.
 *
 *  This app also takes a couple command-line parameters.  The format is:
 *
 *	DSShow [/PLAY [/LOOP]] [file] [file] ...
 *
 *    Specifying /PLAY causes any specified files to be played as they're
 * opened.  Adding the /LOOP causes them to loop as well.  /LOOP without
 * /PLAY means nothing.  Everything else is assumed to be one or more file
 * names.  Filenames can be enclosed in quotes.  This also means you can
 * drag and drop files onto the program's icon
 *
 *
 ***************************************************************************/

#define INITGUID
#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <commdlg.h>
#include <stdio.h>

#include <mmsystem.h>
#include <mmreg.h>
#include <msacm.h>
#include <dsound.h>


#include "wassert.h"
#include "wave.h"

#include "resource.h"
#include "shell.h"
#include "dsenum.h"


// =======================================================================
/* Procedure called when the application is loaded for the first time */
// =======================================================================
BOOL ClassInit( hInstance )
HANDLE hInstance;
{
    WNDCLASS    myClass;
	    
    myClass.hCursor             = LoadCursor( NULL, IDC_ARROW );
    myClass.hIcon               = LoadIcon( hInstance, MAKEINTRESOURCE(IDI_ICON3));
    myClass.lpszMenuName        = MAKEINTRESOURCE(IDR_MAINMENU);
    myClass.lpszClassName       = (LPSTR)szAppName;
    myClass.hbrBackground       = (HBRUSH)(COLOR_WINDOW);
    myClass.hInstance           = hInstance;
    myClass.style               = CS_HREDRAW | CS_VREDRAW;
    myClass.lpfnWndProc         = WndProc;
    myClass.cbClsExtra          = 0;
    myClass.cbWndExtra          = 0;

    if (!RegisterClass( &myClass ) )
       return FALSE;

    return TRUE;        /* Initialization succeeded */
}


// =======================================================================
/* This "hook procedure" is called by the common dialog code for certain
 *   events that may occur during the life of our nested dialog structure.
 *	 We nest the Explorer style dialog inside our file open dialog so we
 *   can addd a check box for stick buffers.
 */
 // =======================================================================
UINT CALLBACK FileOpenCustomTemplateDlgProc( hDlg, message, wParam, lParam )
HWND hDlg;
UINT message;
WPARAM wParam;
LPARAM lParam;
{
    static LPOPENFILENAME   lpofn = NULL;

    switch( message )
    {
    case WM_INITDIALOG:
        lpofn = (LPOPENFILENAME)lParam;
		
        /* Set the flag to match the current state of the check box control */
        *((LPBOOL)lpofn->lCustData) = SendDlgItemMessage( hDlg, IDC_FONEST_STICKY,
                                                            BM_GETCHECK, 0, 0 );
        return TRUE;

    case WM_NOTIFY:
        switch(((LPOFNOTIFY)lParam)->hdr.code)
        {
        case CDN_SELCHANGE:
            /* Use this area to process anything that must be updated when the
             * user changes the selection in the Common Dialog Box.
             *   NOTE: Provided only for informational purposes
             */
            return FALSE;

        case CDN_FILEOK:
            /* We can do lots of things in this notification message.  The most
             * important is that we can decide whether the Common Dialog call will
             * go through or whether it will fail.  I decided to handle the checkbox
             * control in this one place versus 4 others... -PRN
             */
            Assert( lpofn != NULL );
            *((LPBOOL)lpofn->lCustData) = SendDlgItemMessage( hDlg, IDC_FONEST_STICKY,
                                                                BM_GETCHECK, 0, 0 );
            /* Returning zero signifies that we "approve" of the OK command,
             * and allows the common dialog to finish.
             */
            return FALSE;
        }
        /* Let the default dialog do/continue processing */
        return FALSE;
    }
    return FALSE;
}


// =======================================================================
// =======================================================================
int PASCAL WinMain( hInstance, hPrevInstance, lpszCmdLine, cmdShow )
HINSTANCE hInstance, hPrevInstance;
LPSTR lpszCmdLine;
int cmdShow;
{
    MSG   msg;
    HWND  hWnd;

    // We must call this to ensure the common controls are setup for
    // this application
    InitCommonControls();

    if (!hPrevInstance) {
	/* Call initialization procedure if this is the first instance */
    if (!ClassInit( hInstance ))
	    return FALSE;
	}

    
    hWnd = CreateWindow((LPSTR)szAppName,
						(LPSTR)szMessage,
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,    
						CW_USEDEFAULT,    
						DX_MINWINDOW,     
						DY_MINWINDOW,     
						(HWND)NULL,        
						(HMENU)NULL,      
						(HANDLE)hInstance, 
						(LPSTR)NULL        
						);

    if (!hWnd) return (int)msg.wParam;

    // Make a long line across the top.
    CreateWindow(
	"STATIC", 
	"", 
	WS_CHILD | WS_VISIBLE | SS_ETCHEDHORZ, 
	0,
	0,
	8000, 
	2,              
	hWnd, 
	(HMENU)0, 
	hInst, 
	NULL);
	

    /* Save instance handle for DialogBox */
    hInst = hInstance;
    
    ShowWindow( hWnd, cmdShow );

    if( lpszCmdLine && *lpszCmdLine )
        if( !ParseCommandLine( lpszCmdLine ))
	    goto Exit_WinMain;
    
    /* Polling messages from event queue */
    while (GetMessage((LPMSG)&msg, NULL, 0, 0)) {
	TranslateMessage((LPMSG)&msg);
	DispatchMessage((LPMSG)&msg);
	}

Exit_WinMain:
    DestroyWindow(hWnd);
    UnregisterClass(szAppName, hInstance);
    return (int)msg.wParam;
}

// =======================================================================
/*  This function updates the status window by writing the specified
    string to the window, prepended by a string indicating whether
    the buffer is in hardware or software
*/
// =======================================================================
void UpdateStatus(FILEINFO *pFileInfo, DWORD dwStatus)
{
    TCHAR szStatus[200];
    DWORD dwPlay, dwWrite;
    HRESULT hr;

    lstrcpy(szStatus, pFileInfo->fHardware ? szHW : szSW);
    if (dwStatus & DSBSTATUS_BUFFERLOST)
    {
    lstrcat(szStatus, szLost);
    SendMessage(pFileInfo->hWndStatus_TXT, WM_SETTEXT, 0, (LPARAM)szStatus);
    }
    else if (dwStatus & DSBSTATUS_PLAYING)
    {
    lstrcat(szStatus, szPlaying);
    SendMessage(pFileInfo->hWndStatus_TXT, WM_SETTEXT, 0, (LPARAM)szStatus);
    }
    else
    {
    lstrcat(szStatus, szStopped);
    SendMessage(pFileInfo->hWndStatus_TXT, WM_SETTEXT, 0, (LPARAM)szStatus);
    }

    if (pFileInfo->fSticky)
	{
	lstrcat(szStatus, szSticky);
    SendMessage(pFileInfo->hWndStatus_TXT, WM_SETTEXT, 0, (LPARAM)szStatus);
	}
    hr = IDirectSoundBuffer_GetCurrentPosition(pFileInfo->pDSB, &dwPlay, &dwWrite);
    if (DS_OK == hr) {
    wsprintf(szStatus, szFmtPlayPosition, dwPlay);
    SendMessage(pFileInfo->hWndPlayPosition_TXT, WM_SETTEXT, 0, (LPARAM)szStatus);
    wsprintf(szStatus, szFmtWritePosition, dwWrite);
    SendMessage(pFileInfo->hWndWritePosition_TXT, WM_SETTEXT, 0, (LPARAM)szStatus);
    }

    return;
}

// =======================================================================
/*  This function updates the main window title to show some
    relevant information about the direct sound object
*/
// =======================================================================
void UpdateMainStatus()
{
    DSCAPS  dsc;
    TCHAR   szTitle[200];
    
    // Update main window title with some relevant info
    dsc.dwSize = sizeof(dsc);
    IDirectSound_GetCaps(gpds, &dsc);
    wsprintf(szTitle, "%s : free hw memory = %dKb, free hw buffers = %d",
	 szMessage, (dsc.dwFreeHwMemBytes+512)/1024,
	 dsc.dwFreeHwMixingAllBuffers);
    SendMessage(hWndMain, WM_SETTEXT, 0, (LPARAM)szTitle);
    return;
}


// =======================================================================
/*  This routine will set up everything needed for the app to run.

    Input:
	hWnd                - App main window handle

    Output:
	None.

*/
// =======================================================================
int AppInit(HWND hWnd)
{
    UINT            cT;
    DSBUFFERDESC    dsbd;
    BOOL	    fUseGuid;
    HRESULT         hr;
    DWORD           dw;

    // Set up the global window handle.
    hWndMain = hWnd;

    // Set up the global File...Open dialog's start directory
    GetMediaStartPath();

    // Set up the file info header
    FileInfoFirst.pNext = NULL;
    FileInfoFirst.pwfx = NULL;
    FileInfoFirst.cox = COX_STARTCONTROL;
    FileInfoFirst.coy = COY_STARTCONTROL;

    // Clear the coordinate buffer.  Used to find the next available
    // position to use for a new control.  -1 is the invalid value.
    for (cT=0; cT<MAXCONTROLS; cT++) rgfcoxAvail[cT] = FALSE;

    // Setup the timer...
    if ((dwTimer = SetTimer(hWnd, 1, TIMERPERIOD, NULL)) == 0) 
	{
		MessageBox(hWnd, "Cannot allocate timer, aborting", "DirectSound Demo", MB_OK|MB_ICONSTOP);
		return -1;
    }

    // Now set up all the direct sound stuff...

    // Get the largest waveformatex structure.
    if (MMSYSERR_NOERROR != acmMetrics(NULL, ACM_METRIC_MAX_SIZE_FORMAT, &dw))
    {
	MessageBox(hWnd, "ACM Metrics failed, aborting", "DirectSound Demo",
		   MB_OK|MB_ICONSTOP);
	return -1;
    }


    // Setup the format, frequency, volume, etc.
    if ((FileInfoFirst.pwfx = GlobalAllocPtr(GPTR, dw)) == NULL)
    {
	MessageBox(hWnd, "Out of Memory", "DirectSound Demo",
		   MB_OK|MB_ICONSTOP);
	return -1;
    }



    FileInfoFirst.pwfx->wFormatTag = WAVE_FORMAT_PCM;
    FileInfoFirst.pwfx->nChannels = 2;
    FileInfoFirst.pwfx->nSamplesPerSec = 22050;
    FileInfoFirst.pwfx->nAvgBytesPerSec = 22050*2*2;
    FileInfoFirst.pwfx->nBlockAlign = 4;
    FileInfoFirst.pwfx->wBitsPerSample = 16;
    FileInfoFirst.pwfx->cbSize = 0;
    
#ifdef STARTEIGHTBITS

    FileInfoFirst.pwfx->wFormatTag = WAVE_FORMAT_PCM;
    FileInfoFirst.pwfx->nChannels = 2;
    FileInfoFirst.pwfx->nSamplesPerSec = 22050;
    FileInfoFirst.pwfx->nAvgBytesPerSec = 22050*1*2;
    FileInfoFirst.pwfx->nBlockAlign = 2;
    FileInfoFirst.pwfx->wBitsPerSample = 8;
    FileInfoFirst.pwfx->cbSize = 0;
#endif

#ifdef STARTMONO    
    FileInfoFirst.pwfx->wFormatTag = WAVE_FORMAT_PCM;
    FileInfoFirst.pwfx->nChannels = 1;
    FileInfoFirst.pwfx->nSamplesPerSec = 22050;
    FileInfoFirst.pwfx->nAvgBytesPerSec = 22050*1*2;
    FileInfoFirst.pwfx->nBlockAlign = 2;
    FileInfoFirst.pwfx->wBitsPerSample = 16;
    FileInfoFirst.pwfx->cbSize = 0;
#endif
    
    // Optionally enumerate DSOUND devices and allow the user to pick one...

    if (!SUCCEEDED(CoInitialize(NULL))) {
	MessageBox(hWnd, "Failed to initialize COM library", "DirectSound Demo", MB_OK | MB_ICONSTOP);
	return -1;
    }
    
    fEnumDrivers = (BOOL)GetProfileInt( "DSSHOW", "EnumDrivers", FALSE );
	fUseGuid = (fEnumDrivers && !DoDSoundEnumerate(&guID));

	// Create the direct sound object.
    hr = CoCreateInstance(&CLSID_DirectSound, NULL, CLSCTX_INPROC_SERVER,
			  &IID_IDirectSound, &gpds);

    if (SUCCEEDED(hr) && (NULL != gpds))
	{
		hr = IDirectSound_Initialize(gpds, fUseGuid ? &guID : NULL);
		if (SUCCEEDED(hr)) 
		{
			// Note we need to set the level to be priority to set the
			// format of the primary buffer
			hr = IDirectSound_SetCooperativeLevel(gpds, hWndMain, DSSCL_PRIORITY);
			if (SUCCEEDED(hr)) 
			{

			// Set up the primary direct sound buffer.
			ZeroMemory(&dsbd, sizeof(dsbd));
			dsbd.dwSize = sizeof(dsbd);
			dsbd.dwFlags = DSBCAPS_PRIMARYBUFFER;
    
			hr = IDirectSound_CreateSoundBuffer(gpds, &dsbd, &(FileInfoFirst.pDSB), NULL);
			if (SUCCEEDED(hr)) 
			{
				hr = IDirectSoundBuffer_Play(FileInfoFirst.pDSB, 0, 0, DSBPLAY_LOOPING);
				if (SUCCEEDED(hr)) 
				{
					UpdateMainStatus();
				} 
				else 
				{
					MessageBox(hWnd, "Cannot play primary buffer","DirectSound Demo", MB_OK|MB_ICONSTOP);
					IDirectSoundBuffer_Release(FileInfoFirst.pDSB);
					FileInfoFirst.pDSB = NULL;
			    }		
			} 
			else 
			{
				MessageBox(hWnd, "Cannot create primary buffer","DirectSound Demo", MB_OK|MB_ICONSTOP);
			}
	    } 
		else 
		{
		MessageBox(hWnd, "DirectSound SetCooperativeLevel failed","DirectSound Demo", MB_OK|MB_ICONSTOP);
	    }
	} //initialize
	else 
	{
	    MessageBox(hWnd, "Failed to Initialize DirectSound object", "DirectSound Demo", MB_OK | MB_ICONSTOP);
	}

	if (!SUCCEEDED(hr)) 
	{
	    IDirectSound_Release(gpds);
	    gpds = NULL;
	}

 } 
else 
{
	MessageBox(hWnd, "Failed to create DirectSound COM object",
		   "DirectSound Demo", MB_OK | MB_ICONSTOP);
}

if (SUCCEEDED(hr)) 
{
	return 0;
} 
else 
{
	CoUninitialize();
	return -1;
}
}

// =======================================================================
/*  This will destroy all the created objects, allocated memory, etc.  Must be called
    before termination of app.

    Input:
	hWnd                - Window handle of main window

    Output:
	None.

*/
// =======================================================================
void AppDestroy( HWND hWnd )
{

    HRESULT     hr = 0;

    if (dwTimer != 0)
    {
	KillTimer(hWnd, dwTimer);
	dwTimer = 0;
    }


    StopAllDSounds(hWnd, &FileInfoFirst);
    FreeAllList(hWnd, &FileInfoFirst);


    // Destroy the direct sound buffer.
    if(FileInfoFirst.pDSB != NULL) 
    {
	IDirectSoundBuffer_Stop(FileInfoFirst.pDSB);
	IDirectSoundBuffer_Release(FileInfoFirst.pDSB);
	FileInfoFirst.pDSB = NULL;
    }

    // Destroy the direct sound object.
    if (gpds != NULL)
    {
	IDirectSound_Release(gpds);
	gpds = NULL;
	CoUninitialize();
    }

    if (FileInfoFirst.pwfx != NULL)
    {
	GlobalFreePtr(FileInfoFirst.pwfx);
	FileInfoFirst.pwfx = NULL;
    }

    if (FileInfoFirst.pbData != NULL)
    {
	GlobalFreePtr(FileInfoFirst.pbData);
	FileInfoFirst.pbData = NULL;
    }

    WriteProfileString( "DSSHOW", "EnumDrivers", fEnumDrivers ? "1" : "0" );

}

// =======================================================================
/* Procedures which make up the window class. */
// =======================================================================
long FAR PASCAL WndProc( hWnd, message, wParam, lParam )
HWND hWnd;
unsigned message;
WPARAM wParam;
LPARAM lParam;
{



    switch (message)
	{

	case WM_CREATE:
	    if (AppInit(hWnd)) return (-1);
	    break;

	case WM_TIMER:  
	    if (!UIMainWindowTimerHandler(hWnd, wParam, lParam))
		return(DefWindowProc(hWnd, message, wParam, lParam));                           
	    break;
	    
    
	case WM_HSCROLL:
	    if (!UIMainWindowHSBHandler(hWnd, wParam, lParam))
		return(DefWindowProc(hWnd, message, wParam, lParam));
		    
	    break;

	case WM_VSCROLL:
	    if (!UIMainWindowVSBHandler(hWnd, wParam, lParam))
		return(DefWindowProc(hWnd, message, wParam, lParam));
	    break;
		    

		case WM_INITMENU:
			if((HMENU)wParam != GetMenu( hWnd ))
			    break;
			CheckMenuItem((HMENU)wParam, IDPD_ENUMDRIVERS,
				fEnumDrivers ? MF_CHECKED : MF_UNCHECKED );
			break;

		case WM_COMMAND:
	    if (!UIMainWindowCMDHandler(hWnd, wParam, lParam))
		return(DefWindowProc(hWnd, message, wParam, lParam));
	    break;
	    
	    break;
	
	/*case WM_PAINT:
	    {           
	    
	    break;
	    }*/


	case WM_DESTROY:
	    AppDestroy(hWnd);
	    PostQuitMessage( 0 );
	    break;
	
	default:
	    return DefWindowProc( hWnd, message, wParam, lParam );
	    break;
	    
	}
    
    return(0L);
}

// =======================================================================
/*  This routine will pop up the open file dialog and open a file, and make any internal
    arrangements so we know the file is loaded.

    Input:
	hWnd            -   Handle of parent window.

    Output:
	None.

*/
// =======================================================================
void PD_FileOpen( HWND hWnd )
{

    char            szFileName[MAX_PATH];
    UINT            cSamples;
    FILEINFO        *pFileInfo                  = NULL;
    int             nFileName;
    BOOL            fSticky;

    if (GetNumControls(&FileInfoFirst) >= MAXCONTROLS)
    {
    MessageBox(hWnd, "No more controls allowed",
	   "Hold on a sec...", MB_OK);
    return;
    }

    // Open the file, and check its format, etc.
    if (OpenFileDialog(hWnd, szFileName, &nFileName, &fSticky))
    {

    // Allocate the memory for the structure.
    if ((pFileInfo = GlobalAllocPtr(GPTR, sizeof(FILEINFO))) == NULL)
    {
	MessageBox(hWnd, "Cannot add this file",
	       "Out of Memory", MB_OK|MB_ICONSTOP);
	goto ERROR_DONE_ROUTINE;
    }

    pFileInfo->pbData   = NULL;
    pFileInfo->pwfx     = NULL;
    pFileInfo->pDSB     = NULL;
    pFileInfo->fSticky  = fSticky;
    strcpy(pFileInfo->szFileName, szFileName);
    
    if (WaveLoadFile(szFileName, &pFileInfo->cbSize, 
	    &cSamples, &pFileInfo->pwfx, &pFileInfo->pbData) != 0)
    {
	MessageBox(hWnd, "Bad wave file or file too big to fit in memory",
		"Cannot load wave", MB_OK|MB_ICONSTOP);
	goto ERROR_DONE_ROUTINE;
    }

    GetNextControlCoords(&FileInfoFirst,
		     &pFileInfo->cox, &pFileInfo->coy);

    if (NewDirectSoundBuffer(pFileInfo) != 0)
    {
	MessageBox(hWnd, "Cannot create new buffer",
	       "Direct Sound Error", MB_OK|MB_ICONSTOP);
	goto ERROR_DONE_ROUTINE;
    }
	
    Assert(pFileInfo->pbData != NULL);

    // If we fail after this, make sure to update the list!!!
    if (AddToList(&FileInfoFirst, pFileInfo) != 0)
    {
	MessageBox(hWnd, "Cannot add file to list",
		   "Out of Memory", MB_OK|MB_ICONSTOP);
	goto ERROR_DONE_ROUTINE;
    }

    pFileInfo->nFileName = nFileName;
    CreateControl(hWnd, pFileInfo, pFileInfo->pwfx->nSamplesPerSec,
	      (MAXPAN_TB-MINPAN_TB)/2, MINVOL_TB );
    ChangeOutputVol(pFileInfo);
    ChangeOutputFreq(pFileInfo);
    ChangeOutputPan(pFileInfo);
    UpdateMainStatus();

    }

    goto DONE_ROUTINE;
	   
ERROR_DONE_ROUTINE:
    if (pFileInfo != NULL)
    {
	
    ReleaseDirectSoundBuffer(pFileInfo);

    if (pFileInfo->pwfx != NULL)
    {
	GlobalFreePtr(pFileInfo->pwfx);
	    
    }
    if (pFileInfo->pbData != NULL)
    {
	GlobalFreePtr(pFileInfo->pbData);           
    }

    GlobalFreePtr(pFileInfo);
    pFileInfo = NULL;
    }

DONE_ROUTINE:
    return;

}

// =======================================================================
/*  This routine will initialize a new direct sound buffer,
    set the data in the buffer, 
    set the rate, format, etc...

    Input:
	pFileInfo   -   Pointer to file info with all
	nessecary info filled, 
	like pbData, cbData, etc...

    Output:
	0 if successful, else the error code.

*/
// =======================================================================
int NewDirectSoundBuffer(FILEINFO *pFileInfo)
{

    DSBUFFERDESC        dsbd;
    DSBCAPS         dsbc;
    HRESULT         hr;
    BYTE            *pbData         = NULL;
    BYTE            *pbData2        = NULL;
    DWORD           dwLength;
    DWORD           dwLength2;

    // Set up the direct sound buffer. 
    memset(&dsbd, 0, sizeof(DSBUFFERDESC));
    dsbd.dwSize                 = sizeof(DSBUFFERDESC);
    dsbd.dwFlags                = 0;
    dsbd.dwFlags                |= DSBCAPS_STATIC;
    // Use new GetCurrentPosition() accuracy (DirectX 2 feature)
    dsbd.dwFlags                |= DSBCAPS_CTRLDEFAULT | DSBCAPS_GETCURRENTPOSITION2;
    if (pFileInfo->fSticky)
        dsbd.dwFlags |= DSBCAPS_STICKYFOCUS;
    dsbd.dwBufferBytes               = pFileInfo->cbSize;
    dsbd.lpwfxFormat            = pFileInfo->pwfx;
    if ((hr = gpds->lpVtbl->CreateSoundBuffer(gpds,
			  &dsbd,
			  &(pFileInfo->pDSB),
			  NULL )) != 0)
	{
	goto ERROR_IN_ROUTINE;
	}

    // Ok, lock the sucker down, and copy the memory to it.
    if ((hr = pFileInfo->pDSB->lpVtbl->Lock(pFileInfo->pDSB,
			0,
			pFileInfo->cbSize,
			&pbData,
			&dwLength,
			&pbData2,
			&dwLength2,
					    0L)) != 0)
    {
    goto ERROR_IN_ROUTINE;
    }

    Assert(pbData != NULL);
    memcpy(pbData, pFileInfo->pbData, pFileInfo->cbSize);

    // Ok, now unlock the buffer, we don't need it anymore.
    if ((hr = pFileInfo->pDSB->lpVtbl->Unlock(pFileInfo->pDSB,
					      pbData, pFileInfo->cbSize,
					      NULL, 0)) != 0)
    {
    goto ERROR_IN_ROUTINE;
    }

    pbData = NULL;

    if ((hr = pFileInfo->pDSB->lpVtbl->SetVolume(pFileInfo->pDSB,
	    MAXVOL_VAL)) != 0)
    {
    goto ERROR_IN_ROUTINE;
    }

    if ((hr = pFileInfo->pDSB->lpVtbl->SetPan(pFileInfo->pDSB,
	    MIDPAN_VAL)) != 0)
    {
    goto ERROR_IN_ROUTINE;
    }

    dsbc.dwSize = sizeof(dsbc);
    if (hr = IDirectSoundBuffer_GetCaps(pFileInfo->pDSB, &dsbc))
    {
    goto ERROR_IN_ROUTINE;
    }

    if (dsbc.dwFlags & DSBCAPS_LOCHARDWARE) {
    pFileInfo->fHardware = TRUE;
    } else {
    pFileInfo->fHardware = FALSE;
    }

    goto DONE_ROUTINE;

ERROR_IN_ROUTINE:
    if (pbData != NULL)
    {
    hr = pFileInfo->pDSB->lpVtbl->Unlock(pFileInfo->pDSB, pbData,
						pFileInfo->cbSize, NULL, 0);
    pbData = NULL;
    }

    if (pFileInfo->pDSB != NULL)
    {
    pFileInfo->pDSB->lpVtbl->Release(pFileInfo->pDSB);
    pFileInfo->pDSB = NULL;
    }
    
DONE_ROUTINE:

    return(hr); 

}

// =======================================================================
/*  This routine will release a direct sound buffer,
    freeing up memory, resources, 
    whatever.

    Input:
	pFileInfo   -   Pointer to the file info,
		with the proper stuff set.

    Output: 
	0 if successful, else the error code.

*/
// =======================================================================
int ReleaseDirectSoundBuffer( FILEINFO *pFileInfo )
{

    if (pFileInfo->pDSB != NULL)
    {
    pFileInfo->pDSB->lpVtbl->Release(pFileInfo->pDSB);
    pFileInfo->pDSB = NULL; 
    }

    return(0);

}

// =======================================================================
/*  This routine will find the next x and y coordinates to
    write the control to.
    The rgfcoxAvail is an array of booleans.
    If false, then the index can be 
    used as an x coordinate.

    Input:
	pFileInfoHead - Header of the linked list.
	pcox, pcoy    - Filled upon return with next
		coordinates to use.
	
    Output:
	Only pcox and pcoy change.
	
*/
// =======================================================================	
void GetNextControlCoords(                     
		    FILEINFO    *pFileInfoHead, 
		    int         *pcox, 
		    int         *pcoy
		    )
{
    UINT            cT;

    for (cT=0; cT<MAXCONTROLS; cT++)
    {
    if (rgfcoxAvail[cT] == FALSE)
    {
	rgfcoxAvail[cT] = TRUE;
	break;
    }
	    
    }

    if (cT == MAXCONTROLS)
    {
    Assert(FALSE);
    // Couldn't find a place to put control, shouldn't happen though.
    cT = 666;       // Well, at least put it off screen.
    }

    *pcox = cT*DX_CONTROLSPACING+COX_STARTCONTROL;      //Offsetting the text from the border
    *pcoy = COY_STARTCONTROL;
    

}

// =======================================================================
/*  CreateControl

    This will create the control used for the window, actually it is a
    bundle of controls put together.  I was thinking of a good way to
    figure out id codes for the controls but found no good way except a
    "funny" way...I'm going to use the x coordinate of the control as the
    id for the first control, then id+1 for the second control.  Since
    all the controls have different x coordinates, this is fine, as long
    as the # of windows in the control is not more than the spacing of
    the controls.

    Input:
	hWnd                -   Parent Window.
	pFileInfo           -   Pointer to FileInfo structure with the cox and coy filled.
	dwFreq, dwPan, dwVol-   Default track bar values.

    Output:
	0 if successful, else the error code.

*/
// =======================================================================
int CreateControl(HWND hWnd, FILEINFO *pFileInfo, DWORD dwFreq,DWORD dwPan, DWORD dwVol)
{
    int		cox, coy;
    int     coxOld, coyOld;
    int     nError = 0;
    DWORD	idBase;
    SIZE    Size;       
    HDC     hDC = NULL;
	DWORD dwMinFreq, dwMaxFreq;

    /* Figure out the values of dwPan and dwVol that the track bars like */

    idBase = pFileInfo->cox;
    Assert(pFileInfo != NULL);
    cox = pFileInfo->cox+DX_TEXTSPACING;
    coy = pFileInfo->coy+DY_TEXTSPACING;        //We may have to shift this

    coxOld = cox;
    coyOld = coy;
	coy -= 8;                       //We must adjust to fit the text in the border

    if ((hDC = GetDC(hWnd)) == NULL)
	{
	nError = -1;
	goto DONE_ROUTINE;
	}


    if (!GetTextExtentPoint32(hDC, pFileInfo->szFileName+pFileInfo->nFileName, strlen(pFileInfo->szFileName+pFileInfo->nFileName), &Size))
	{
	nError = -1;
	goto DONE_ROUTINE;
	}

    //Creates the Filename window
    if ((pFileInfo->hWndFileName_TXT = CreateWindow(
	"STATIC", 
	pFileInfo->szFileName+pFileInfo->nFileName, 
	WS_CHILD | WS_VISIBLE | SS_LEFTNOWORDWRAP, 
	cox,
	coy,                                                                    
	DX_FILENAME_TXT,                                                                        
	Size.cy,              
	hWnd, 
	(HMENU)0, 
	hInst, 
	NULL)) == NULL)
	{
	nError = -1;
	goto DONE_ROUTINE;
	}   
																		//Create line under Filename            
    cox += DX_LOOPEDSPACING;
    coy += Size.cy + DY_TEXTSPACING + DY_LOOPEDSPACING;

    if ((pFileInfo->hWndFileName_EDGE = CreateWindow(
	"STATIC", 
	"", 
	WS_CHILD | WS_VISIBLE | SS_ETCHEDHORZ, 
	cox,
	coy - (DY_LOOPEDSPACING+DY_TEXTSPACING)/2,
	DX_LINEEDGE, 
	DY_LINEEDGE,                
	hWnd, 
	(HMENU)0, 
	hInst, 
	NULL)) == NULL)
	{
	nError = -1;
	goto DONE_ROUTINE;
	}   

    // Now create status if required.
    
    #ifdef SHOWSTATUS   

    if (!GetTextExtentPoint32(hDC, szPlaying, strlen(szPlaying), &Size))
	{
	nError = -1;
	goto DONE_ROUTINE;
	}


    //Creates Status Window
    if ((pFileInfo->hWndStatus_TXT = CreateWindow(
	"STATIC", 
	"",
	WS_CHILD | WS_VISIBLE | SS_LEFTNOWORDWRAP, 
	cox,
	coy,
	DX_STATUS_TXT, 
	Size.cy, // + DY_TEXTSPACING,               
	hWnd, 
	(HMENU)0, 
	hInst, 
	NULL)) == NULL)
	{
	nError = -1;
	goto DONE_ROUTINE;
	}   

    cox += DX_LOOPEDSPACING;
    coy += Size.cy + DY_TEXTSPACING + DY_LOOPEDSPACING;

    //Create line under Status
    if ((pFileInfo->hWndStatus_EDGE = CreateWindow(
	"STATIC", 
	"", 
	WS_CHILD | WS_VISIBLE | SS_ETCHEDHORZ, 
	cox,
	coy - (DY_LOOPEDSPACING+DY_TEXTSPACING)/2,
	DX_LINEEDGE, 
	DY_LINEEDGE,                
	hWnd, 
	(HMENU)0, 
	hInst, 
	NULL)) == NULL)
	{
	nError = -1;
	goto DONE_ROUTINE;
	}

    //Creates PlayPos Window
    if ((pFileInfo->hWndPlayPosition_TXT = CreateWindow(
	"STATIC", "",
	WS_CHILD | WS_VISIBLE | SS_LEFTNOWORDWRAP,
	cox, 
	coy,
	DX_STATUS_TXT, 
	Size.cy,
	hWnd, 
	NULL, 
	hInst, 
	NULL)) == NULL)
    {
	nError = -1;
	goto DONE_ROUTINE;
    }

    cox += DX_LOOPEDSPACING;
    coy += Size.cy + DY_TEXTSPACING + DY_LOOPEDSPACING; //Create line under PlayPos
    
    if ((pFileInfo->hWndPlayPosition_EDGE = CreateWindow(
	"STATIC", "", 
	WS_CHILD | WS_VISIBLE | SS_ETCHEDHORZ, 
	cox, 
	coy - (DY_LOOPEDSPACING+DY_TEXTSPACING)/2,
	DX_LINEEDGE, 
	DY_LINEEDGE,               
	hWnd, 
	NULL, 
	hInst, 
	NULL)) == NULL)
    {
	nError = -1;
	goto DONE_ROUTINE;
    }
    
    //Creates WritePos Window
    if ((pFileInfo->hWndWritePosition_TXT = CreateWindow(
	"STATIC", "",
	WS_CHILD | WS_VISIBLE | SS_LEFTNOWORDWRAP,
	cox, 
	coy,
	DX_STATUS_TXT, 
	Size.cy,
	hWnd, 
	NULL, 
	hInst, 
	NULL)) == NULL)
    {
	nError = -1;
	goto DONE_ROUTINE;
    }

    cox += DX_LOOPEDSPACING;
    coy += Size.cy + DY_TEXTSPACING + DY_LOOPEDSPACING;
    
    //Create line under WritePos
    if ((pFileInfo->hWndWritePosition_EDGE = CreateWindow(
	"STATIC", "", 
	WS_CHILD | WS_VISIBLE | SS_ETCHEDHORZ, 
	cox, 
	coy - (DY_LOOPEDSPACING+DY_TEXTSPACING)/2,
	DX_LINEEDGE,
	DY_LINEEDGE,               
	hWnd,
	NULL, 
	hInst, 
	NULL)) == NULL)
    {
	nError = -1;
	goto DONE_ROUTINE;
    }
    
    #endif      
	
    //Set up the Freq Text
    if (!GetTextExtentPoint32(hDC, szFreq, strlen(szFreq), &Size))
	{
	nError = -1;
	goto DONE_ROUTINE;
	}

    // Make the frequency text there.
    if ((pFileInfo->hWndFreq_TXT = CreateWindow(
	"STATIC", 
	szFreq, 
	WS_CHILD | WS_VISIBLE | SS_LEFTNOWORDWRAP, 
	cox,
	coy,
	DX_FREQ_TXT, 
	Size.cy,                
	hWnd, 
	(HMENU)0, 
	hInst, 
	NULL)) == NULL)
	{
	nError = -1;
	goto DONE_ROUTINE;
	}   

    coy += Size.cy;

    // Make the frequency trackbar.
    if ((pFileInfo->hWndFreq_TB = CreateWindow(
	TRACKBAR_CLASS, 
	"", 
	WS_CHILD | WS_VISIBLE | TBS_HORZ | TBS_BOTH, 
	cox,
	coy,
	DX_FREQ_TB, 
	DY_FREQ_TB,             
	hWnd, 
	(HMENU)(idBase+idFreqTB), 
	hInst, 
	NULL)) == NULL)
	{
	nError = -1;
	goto DONE_ROUTINE;
	}   

	// get the min and max range that the sound card supports.
	// If the buffer is in hardware query the card, else use
	// our ifdef'd values.
	if (pFileInfo->fHardware)
	{
		DSCAPS dsc;
		memset(&dsc, 0, sizeof(DSCAPS));
		dsc.dwSize = sizeof(DSCAPS);
	    nError = IDirectSound_GetCaps(gpds, &dsc);
		Assert(nError == DS_OK);
		dwMinFreq = dsc.dwMinSecondarySampleRate;
		dwMaxFreq = dsc.dwMaxSecondarySampleRate;
	}
	else
	{	
		dwMinFreq = DSBFREQUENCY_MIN;	
		dwMaxFreq = DSBFREQUENCY_MAX;
	}

	SendMessage(pFileInfo->hWndFreq_TB, TBM_SETRANGEMIN, FALSE, dwMinFreq / FREQFACTOR );
	SendMessage(pFileInfo->hWndFreq_TB, TBM_SETRANGEMAX, FALSE, dwMaxFreq / FREQFACTOR );
	
    SendMessage(pFileInfo->hWndFreq_TB, TBM_SETPAGESIZE, 0, FREQPAGE );
    SendMessage(pFileInfo->hWndFreq_TB, TBM_SETPOS, TRUE, (dwFreq + FREQADD)/FREQFACTOR);
    pFileInfo->dwFreq = dwFreq;


    coy += DY_FREQ_TB+DY_PANSPACING;    

    if ((pFileInfo->hWndFreq_EDGE = CreateWindow(
	"STATIC", 
	"", 
	WS_CHILD | WS_VISIBLE | SS_ETCHEDHORZ, 
	cox,
	coy - (DY_PANSPACING+DY_TEXTSPACING)/2,
	DX_LINEEDGE, 
	DY_LINEEDGE,                
	hWnd, 
	(HMENU)0, 
	hInst, 
	NULL)) == NULL)
	{
	nError = -1;
	goto DONE_ROUTINE;
	}   

    //Adjusts the relative position of the Text    
    coy -= (((DY_PANSPACING+DY_TEXTSPACING)/2)-((DY_LOOPEDSPACING+DY_TEXTSPACING)/2));

    if (!GetTextExtentPoint32(hDC, szPan, strlen(szPan), &Size))
	{
	nError = -1;
	goto DONE_ROUTINE;
	}


    // Make the pan text there.
    if ((pFileInfo->hWndPan_TXT = CreateWindow(
	"STATIC", 
	szPan, 
	WS_CHILD | WS_VISIBLE | SS_LEFTNOWORDWRAP, 
	cox,
	coy,
	DX_PAN_TXT, 
	Size.cy,                
	hWnd, 
	(HMENU)0, 
	hInst, 
	NULL)) == NULL)
	{
	nError = -1;
	goto DONE_ROUTINE;
	}   

    coy += Size.cy;

    // Make the pan trackbar.
    if ((pFileInfo->hWndPan_TB = CreateWindow(
	TRACKBAR_CLASS, 
	"", 
	WS_CHILD | WS_VISIBLE | TBS_HORZ | TBS_BOTH, 
	cox,
	coy,
	DX_PAN_TB, 
	DY_PAN_TB,              
	hWnd, 
	(HMENU)(idBase+idPanTB), 
	hInst, 
	NULL)) == NULL)
	{
	nError = -1;
	goto DONE_ROUTINE;
	}   

    SendMessage(pFileInfo->hWndPan_TB, TBM_SETRANGE, FALSE, MAKELONG(MINPAN_TB, MAXPAN_TB)); 
    SendMessage(pFileInfo->hWndPan_TB, TBM_SETPOS, TRUE, dwPan);
	SendMessage(pFileInfo->hWndPan_TB, TBM_SETPAGESIZE, 0, PANPAGE );
    pFileInfo->dwPan = dwPan;


    coy += DY_PAN_TB + DY_VOLSPACING;

    if ((pFileInfo->hWndPan_EDGE = CreateWindow(
	"STATIC", 
	"", 
	WS_CHILD | WS_VISIBLE | SS_ETCHEDHORZ, 
	cox,
	coy - (DY_VOLSPACING+DY_TEXTSPACING)/2,
	DX_LINEEDGE, 
	DY_LINEEDGE,                
	hWnd, 
	(HMENU)0, 
	hInst, 
	NULL)) == NULL)
	{
	nError = -1;
	goto DONE_ROUTINE;
	}   

    //Adjusts the relative position of the Text
    coy -= (((DY_PANSPACING+DY_TEXTSPACING)/2)-((DY_LOOPEDSPACING+DY_TEXTSPACING)/2));

    if (!GetTextExtentPoint32(hDC, szVolume, strlen(szVolume), &Size))
	{
	nError = -1;
	goto DONE_ROUTINE;
	}

    // Make the volume text there.
    if ((pFileInfo->hWndVol_TXT = CreateWindow(
	"STATIC", 
	szVolume, 
	WS_CHILD | WS_VISIBLE | SS_LEFTNOWORDWRAP, 
	cox,
	coy,
	DX_VOL_TXT, 
	Size.cy,                
	hWnd, 
	(HMENU)idBase, 
	hInst, 
	NULL)) == NULL)
	{
	nError = -1;
	goto DONE_ROUTINE;
	}   

    coy += Size.cy;

    // Make the volume trackbars.
    // Create main volume bar.
    if ((pFileInfo->hWndVolM_TB = CreateWindow(
	TRACKBAR_CLASS, 
	"", 
	WS_CHILD | WS_VISIBLE | TBS_VERT | TBS_BOTH, 
	cox,
	coy,
	DX_VOL_TB, 
	DY_VOL_TB,              
	hWnd, 
	(HMENU)(idBase+idVolMTB), 
	hInst, 
	NULL)) == NULL)
	{
	nError = -1;
	goto DONE_ROUTINE;
	}   

    SendMessage(pFileInfo->hWndVolM_TB, TBM_SETRANGE, FALSE, MAKELONG(MINVOL_TB, MAXVOL_TB)); 
    SendMessage(pFileInfo->hWndVolM_TB, TBM_SETPOS, TRUE, dwVol);
    pFileInfo->dwVol = MAXVOL_TB - dwVol;



    // Now the left volume.
    if ((pFileInfo->hWndVolL_TB = CreateWindow(
	TRACKBAR_CLASS, 
	"", 
	WS_CHILD | WS_VISIBLE |WS_DISABLED| TBS_VERT | TBS_BOTH, 
	cox+DX_VOL_TB+DX_VOLSPACING_TB,
	coy,
	DX_VOL_TB, 
	DY_VOL_TB,              
	hWnd, 
	(HMENU)(idBase+idVolLTB), 
	hInst, 
	NULL)) == NULL)
	{
	nError = -1;
	goto DONE_ROUTINE;
	}   

    SendMessage(pFileInfo->hWndVolL_TB, TBM_SETRANGE, FALSE, MAKELONG(MINVOL_TB, MAXVOL_TB)); 
    SendMessage(pFileInfo->hWndVolL_TB, TBM_SETPOS, TRUE, MAXVOL_TB);

    if ((pFileInfo->hWndVolL_TXT = CreateWindow(
	"STATIC", 
	"L", 
	WS_CHILD | WS_VISIBLE | SS_LEFTNOWORDWRAP, 
	cox+DX_VOL_TB*3/2+DX_VOLSPACING_TB/2,
	coy+DY_VOL_TB+DY_VOLSPACINGY,
	DX_VOLUMECHAR, 
	Size.cy,                
	hWnd, 
	(HMENU)0, 
	hInst, 
	NULL)) == NULL)
	{
	nError = -1;
	goto DONE_ROUTINE;
	}   


    // And right volume.
    if ((pFileInfo->hWndVolR_TB = CreateWindow(
	TRACKBAR_CLASS, 
	"", 
	WS_CHILD | WS_VISIBLE | WS_DISABLED | TBS_VERT | TBS_BOTH, 
	cox+DX_VOL_TB*2+DX_VOLSPACING_TB*2,
	coy,
	DX_VOL_TB, 
	DY_VOL_TB,              
	hWnd, 
	(HMENU)(idBase+idVolRTB), 
	hInst, 
	NULL)) == NULL)
	{
	nError = -1;
	goto DONE_ROUTINE;
	}   

    SendMessage(pFileInfo->hWndVolR_TB,
	    TBM_SETRANGE, FALSE, MAKELONG(MINVOL_TB, MAXVOL_TB)); 
    SendMessage(pFileInfo->hWndVolR_TB,
	    TBM_SETPOS, TRUE, MAXVOL_TB);

    if ((pFileInfo->hWndVolR_TXT = CreateWindow(
	"STATIC", 
	"R", 
	WS_CHILD | WS_VISIBLE | SS_LEFTNOWORDWRAP, 
	cox+DX_VOL_TB*5/2+DX_VOLSPACING_TB/2+2,
			    // +2 to look nice.
	coy+DY_VOL_TB+DY_VOLSPACINGY,
	DX_VOLUMECHAR, 
	Size.cy,                
	hWnd, 
	(HMENU)0, 
	hInst, 
	NULL)) == NULL)
	{
	nError = -1;
	goto DONE_ROUTINE;
	}   

 
    coy += DY_VOL_TB + DY_BEFOREFIRSTBUTTON;    //Line under L & R

    if ((pFileInfo->hWndVol_EDGE = CreateWindow(
	"STATIC", 
	"", 
	WS_CHILD | WS_VISIBLE | SS_ETCHEDHORZ, 
	cox,
	coy - (DY_BEFOREFIRSTBUTTON)/2,
	DX_LINEEDGE, 
	DY_LINEEDGE,                
	hWnd, 
	(HMENU)0, 
	hInst, 
	NULL)) == NULL)
	{
	nError = -1;
	goto DONE_ROUTINE;
	}   



    if (!GetTextExtentPoint32(hDC, szPlay, strlen(szPlay), &Size))
	{
	nError = -1;
	goto DONE_ROUTINE;
	}


    //Create Play Button
    if ((pFileInfo->hWndPlay_BN = CreateWindow(
	"BUTTON", 
	szPlay, 
	WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 
	cox,
	coy,
	DX_BUTTONSPACING, 
	Size.cy + DY_BUTTONSPACING,             
	hWnd, 
	(HMENU)(idBase+idPlayBN), 
	hInst, 
	NULL)) == NULL)
	{
	nError = -1;
	goto DONE_ROUTINE;
	}       

    //coy += Size.cy + DY_BUTTONSPACING + DY_BETWEENBUTTONS;
    
    if (!GetTextExtentPoint32(hDC, szPlay, strlen(szPlay), &Size))
	{
	nError = -1;
	goto DONE_ROUTINE;
	}
     
    //Make Remove button
    if ((pFileInfo->hWndRemove_BN = CreateWindow(
	"BUTTON", 
	szRemove, 
	WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 
	cox + DX_BUTTONSPACING + DY_BETWEENBUTTONS,
	coy,
	DX_BUTTONSPACING, 
	Size.cy + DY_BUTTONSPACING,             
	hWnd, 
	(HMENU)(idBase+idRemoveBN), 
	hInst, 
	NULL)) == NULL)
	{
	nError = -1;
	goto DONE_ROUTINE;
	}       

    coy += Size.cy + DY_BUTTONSPACING+ DY_BETWEENBUTTONS;


    //Set up Looped Checkbox 
    if (!GetTextExtentPoint32(hDC, szLooped, strlen(szLooped), &Size))
	{
	nError = -1;
	goto DONE_ROUTINE;
	}

    //Create Looped Checkbox window
    if ((pFileInfo->hWndLooped_BN = CreateWindow(
	"BUTTON", 
	szLooped, 
	WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, 
	cox,
	coy,
	DX_LOOPED_TXT, 
	Size.cy + DY_TEXTSPACING -2,               
	hWnd, 
	(HMENU)(idBase+idLoopedBN), 
	hInst, 
	NULL)) == NULL)
	{
	nError = -1;
	goto DONE_ROUTINE;
	}       
	  

    // Don't need the between buttons spacing
    //  because there are no more controls.
    coy += Size.cy;// + DY_BUTTONSPACING; //+ DY_BETWEENBUTTONS;

    if ((pFileInfo->hWndWhole_EDGE = CreateWindow(
	"STATIC", 
	"", 
	WS_CHILD | WS_VISIBLE | SS_ETCHEDFRAME, 
	coxOld-DX_FRAMEEDGE,
	coyOld-DY_FRAMEEDGE,
	DX_CONTROLSPACING-DX_FRAMEEDGEINNER, 
	coy - coyOld + DY_FRAMEEDGE*2,              
	hWnd, 
	(HMENU)0, 
	hInst, 
	NULL)) == NULL)
	{
	nError = -1;
	goto DONE_ROUTINE;
	}   

    
    SetAllText(pFileInfo);
    UpdateLRVolume(pFileInfo);

    
DONE_ROUTINE:   
    if (hDC != NULL)
    {
	if (ReleaseDC(hWnd, hDC) == 0)
	{
	nError = -1;
	goto DONE_ROUTINE;
	}
    }

    return(nError);

}

// =======================================================================
/*  This will add to the linked list of FileInfo's.
    The FileInfo's keep track of the
    files loaded, and this is done in a linked list format

    Input:
	pFileInfoHead   -   Top of linked list.
	pFileInfo   -   Pointer to entry to add.

    Output:
	0 if successful, else the error code.

*/      
// =======================================================================
int AddToList(FILEINFO *pFileInfoHead, FILEINFO *pFileInfo)
{
    pFileInfo->pNext = NULL;    
    pFileInfo->fPlaying = FALSE;

    while (pFileInfoHead->pNext != NULL)
	{
	pFileInfoHead = pFileInfoHead->pNext;
	}

    pFileInfoHead->pNext = pFileInfo;

    return(0);

}

// =======================================================================
/*  This routine will get the number of controls in the window.
    Can be used to determine new size of window.

    Input:
	pFileInfoHead           -   Header of linked list.

    Output:
	# of controls.
*/
// =======================================================================
int GetNumControls( FILEINFO *pFileInfoHead )
{

    int cT  = 0;

    while (pFileInfoHead->pNext != NULL)
    {
    pFileInfoHead = pFileInfoHead->pNext;
    cT++;
    }

    return(cT);

}

// =======================================================================
/*  This routine will free the whole linked list in pFileInfoFirst,
    including all the
    memory used by the wave file, waveformatex structure, etc.
*/
// =======================================================================
int FreeAllList(HWND hWnd, FILEINFO *pFileInfoFirst)
{

    FILEINFO        *pFileInfo, *pFileNext;
    UINT        cT;

    Assert(pFileInfoFirst != NULL);
    pFileInfo = pFileInfoFirst->pNext;

    while (pFileInfo != NULL)
    {
    ReleaseDirectSoundBuffer(pFileInfo);
    GlobalFreePtr(pFileInfo->pwfx);
    GlobalFreePtr(pFileInfo->pbData);
    pFileNext = pFileInfo->pNext;
    GlobalFreePtr(pFileInfo);
    pFileInfo = pFileNext;
    }

    for (cT=0; cT<MAXCONTROLS; cT++)
    rgfcoxAvail[cT] = FALSE;



    return(0);          


}

// =======================================================================
/*  This routine will remove an entry from the list, i.e. will remove
    pFileInfo and all its allocated memory from the list pointed by the header
    by pFileInfoHead

    Input:
	pFileInfo               -   Pointer to entry to remove.
	pFileInfoHead           -   Head, first entry.

    Output:
	0 if successful, else the error.

*/
// =======================================================================
int RemoveFromList(FILEINFO *pFileInfo, FILEINFO *pFileInfoHead)
{

    FILEINFO        *pFileNext;

    Assert(pFileInfoHead != NULL);

    // This used to be pFileInfoHead != NULL
    while (pFileInfoHead->pNext != NULL)
	{
	if (pFileInfoHead->pNext == pFileInfo)
	    {
	    Assert(pFileInfo->cox/DX_CONTROLSPACING < MAXCONTROLS);
	    rgfcoxAvail[pFileInfo->cox/DX_CONTROLSPACING] = FALSE;
	   
	    DestroyWindow(pFileInfo->hWndFileName_TXT); 
	    DestroyWindow(pFileInfo->hWndFreq_TB);      
	    DestroyWindow(pFileInfo->hWndFreq_TXT);     
	    DestroyWindow(pFileInfo->hWndPan_TB);           
	    DestroyWindow(pFileInfo->hWndPan_TXT);      
	    DestroyWindow(pFileInfo->hWndVol_TXT);      
	    DestroyWindow(pFileInfo->hWndVolL_TB);      
	    DestroyWindow(pFileInfo->hWndVolR_TB);      
	    DestroyWindow(pFileInfo->hWndVolM_TB);      
	    DestroyWindow(pFileInfo->hWndLooped_BN);        
	    DestroyWindow(pFileInfo->hWndPlay_BN);      
	    DestroyWindow(pFileInfo->hWndRemove_BN);
	    DestroyWindow(pFileInfo->hWndFileName_EDGE);
	    DestroyWindow(pFileInfo->hWndLooped_EDGE);  
	    DestroyWindow(pFileInfo->hWndFreq_EDGE);        
	    DestroyWindow(pFileInfo->hWndPan_EDGE);     
	    DestroyWindow(pFileInfo->hWndVol_EDGE);     
	    DestroyWindow(pFileInfo->hWndWhole_EDGE);       
	    DestroyWindow(pFileInfo->hWndVolL_TXT);     
	    DestroyWindow(pFileInfo->hWndVolR_TXT);     
	    #ifdef SHOWSTATUS
	    DestroyWindow(pFileInfo->hWndStatus_TXT);
	    DestroyWindow(pFileInfo->hWndStatus_EDGE);
	    DestroyWindow(pFileInfo->hWndPlayPosition_TXT);
	    DestroyWindow(pFileInfo->hWndPlayPosition_EDGE);
	    DestroyWindow(pFileInfo->hWndWritePosition_TXT);
	    DestroyWindow(pFileInfo->hWndWritePosition_EDGE);
	    #endif




	    GlobalFree(pFileInfoHead->pNext->pwfx);
	    GlobalFree(pFileInfoHead->pNext->pbData);
	    pFileNext = pFileInfoHead->pNext->pNext;
	    GlobalFreePtr(pFileInfoHead->pNext);
	    pFileInfoHead->pNext = pFileNext;                                                         
	    break;
	    }
	pFileInfoHead = pFileInfoHead->pNext;
	}

    return(0);
}

// =======================================================================
/*  This will pop up the open file dialog and allow the user to pick one file. 
    
    Input:  
	hWnd            -   Handle of parent window.
	pszFileName         -   String to store filename in, must be at least MAX_PATH long.


    Output:
	TRUE if a file was  picked successfully, else FALSE (user didn't pick a file)

 */
// =======================================================================
BOOL OpenFileDialog(HWND hWnd, LPSTR pszFileName, int *nFileName, LPBOOL lpfSticky)
{
    BOOL            fReturn,
		    fValid;
    OPENFILENAME    ofn;                

    pszFileName[0]          = 0;

    ofn.lStructSize         = sizeof(ofn);
    ofn.hwndOwner           = hWnd;
    ofn.hInstance           = hInst;
    ofn.lpstrFilter         = "Wave Files\0*.wav\0All Files\0*.*\0\0";
    ofn.lpstrCustomFilter   = NULL;
    ofn.nMaxCustFilter      = 0;
    ofn.nFilterIndex        = 1;
    ofn.lpstrFile           = pszFileName;
    ofn.nMaxFile            = MAX_PATH;
    ofn.lpstrFileTitle      = NULL;
    ofn.nMaxFileTitle       = 0;
    ofn.lpstrInitialDir     = gszCDStartPath;
    ofn.lpstrTitle          = "File Open";
    ofn.Flags               = OFN_FILEMUSTEXIST | OFN_EXPLORER
                                | OFN_ENABLETEMPLATE | OFN_ENABLEHOOK | OFN_HIDEREADONLY;
    ofn.nFileOffset         = 0;
    ofn.nFileExtension      = 0;
    ofn.lpstrDefExt         = "wav";
    ofn.lCustData           = (LONG)lpfSticky;
    ofn.lpfnHook            = FileOpenCustomTemplateDlgProc;
    ofn.lpTemplateName      = MAKEINTRESOURCE(IDD_FILEOPEN_NEST);
				
    fValid = FALSE;
    do   {    
	
    if (fReturn = GetOpenFileName(&ofn))
    {                               
	// Set the start path for the next time this dialog is opened
        lstrcpy( gszCDStartPath, pszFileName );
        gszCDStartPath[ofn.nFileOffset] = '\0';

	fValid = IsValidWave(pszFileName);
	if (!fValid)
	{
	MessageBox(hWnd, "Wave files must be PCM format!",
	       "Invalid Wave File", MB_OK|MB_ICONSTOP);
	}
	else
	*nFileName = ofn.nFileOffset;
    }
    else fValid = TRUE;         // Force break out of loop.
    
    } while (!fValid);

    return(fReturn);     

}

// =======================================================================
/*  This function will determine if the filename passed
    in is a valid wave for this
    app, that is a PCM wave.

    Input:
	pszFileName -   FileName to check.

    Output:
	FALSE if not a valid wave, TRUE if it is.
    
*/
// =======================================================================
BOOL IsValidWave(LPSTR pszFileName)
{ 
    BOOL            fReturn     = FALSE;
    int             nError      = 0;
    HMMIO           hmmio;
    MMCKINFO        mmck;
    WAVEFORMATEX    *pwfx;

    if ((nError = WaveOpenFile(pszFileName, &hmmio, &pwfx, &mmck)) != 0)
	{       
	goto ERROR_IN_ROUTINE;
	}

    if (pwfx->wFormatTag != WAVE_FORMAT_PCM) 
	{
	goto ERROR_IN_ROUTINE;
	}

    WaveCloseReadFile(&hmmio, &pwfx);

    fReturn = TRUE;

ERROR_IN_ROUTINE:
    return(fReturn);    

}

// =======================================================================
// =======================================================================
BOOL UIMainWindowVSBHandler(HWND hWnd, WPARAM wParam, LPARAM lParam)
{

    FILEINFO    *pFileInfo;
    BOOL        fReturn             = FALSE;

    pFileInfo = FileInfoFirst.pNext;

    Assert(pFileInfo != NULL);

    while (pFileInfo != NULL)
    {

    if ((HWND)lParam == pFileInfo->hWndVolM_TB)
    {
	pFileInfo->dwVol = MAXVOL_TB -
	SendMessage(pFileInfo->hWndVolM_TB, TBM_GETPOS, 0, 0);
	ChangeOutputVol(pFileInfo);
	SetAllText(pFileInfo);
	UpdateLRVolume(pFileInfo);
	fReturn = TRUE;
    }

    pFileInfo = pFileInfo->pNext;
    
    }

    return (fReturn);

}


// =======================================================================
/*  This routine will handle all the calls to the WM_HSCROLL
    for the main window, that
    is, all the horizontal scrollbar (and trackbar) messages.

    Input:
	Standard parameters (minus the "message" parameter)
	for a window callback, though
	this is called from the window callback.

    Output:
	FALSE if the message isn't processed, else TRUE if it is.
	If FALSE, the
	return procedure should call the default windows procedure.
*/
// =======================================================================
BOOL UIMainWindowHSBHandler(HWND hWnd, WPARAM wParam, LPARAM lParam)
{

    FILEINFO    *pFileInfo;
    BOOL        fReturn             = FALSE;

    pFileInfo = FileInfoFirst.pNext;
    
    Assert(pFileInfo != NULL);

    while (pFileInfo != NULL)
    {

    if ((HWND)lParam == pFileInfo->hWndFreq_TB)
    {
	pFileInfo->dwFreq = (SendMessage(pFileInfo->hWndFreq_TB,
			TBM_GETPOS, 0, 0) * FREQFACTOR) - FREQADD;
	ChangeOutputFreq(pFileInfo);
	SetAllText(pFileInfo);          
	fReturn = TRUE;
    }

    else if ((HWND)lParam == pFileInfo->hWndPan_TB)
    {
	pFileInfo->dwPan = SendMessage(pFileInfo->hWndPan_TB,
		       TBM_GETPOS, 0, 0);
	ChangeOutputPan(pFileInfo);
	SetAllText(pFileInfo);
	UpdateLRVolume(pFileInfo);
	fReturn = TRUE;
    }

    pFileInfo = pFileInfo->pNext;
    
    }

    return (fReturn);
	


}

// =======================================================================
/*  This routine will handle all the calls to the WM_COMMAND
    for the main window.

    Input:
    Standard parameters (minus the "message" parameter)
    for a window callback, though
    this is called from the window callback.

    Output:
	FALSE if the message isn't processed, else TRUE if it is.
	If FALSE, the
	return procedure should call the default windows procedure.
	

*/
// =======================================================================
BOOL UIMainWindowCMDHandler(HWND hWnd, WPARAM wParam, LPARAM lParam)
{

    BOOL        fReturn     = FALSE;
    FILEINFO        *pFileInfo;
    FILEINFO        *pFileInfoNext;
    DWORD       dwLooping;

    pFileInfo = FileInfoFirst.pNext;
    while (pFileInfo != NULL)
    {
    
    pFileInfoNext = pFileInfo->pNext;
    
    if ((HWND)lParam == pFileInfo->hWndLooped_BN)
    {
	pFileInfo->fLooped = SendMessage(pFileInfo->hWndLooped_BN,
			 BM_GETCHECK, 0, 0);
	// If it is playing then reset the looping to be proper
	if( pFileInfo->fPlaying ) {
	if( pFileInfo->fLooped ) {
	    dwLooping = DSBPLAY_LOOPING;
	} else {
		    dwLooping = 0;
	}
		pFileInfo->pDSB->lpVtbl->Play(pFileInfo->pDSB,
						0, 0, dwLooping );
	} 
	fReturn = TRUE;
    }
    else if ((HWND)lParam == pFileInfo->hWndPlay_BN)
    {
	if (pFileInfo->fPlaying)
	{
	if (StopDSound(hWnd, pFileInfo) == 0)
	{
	    SendMessage((HWND)lParam,
		WM_SETTEXT, 0, (LPARAM)(LPCTSTR)szPlay);

#ifdef SHOWSTATUS
	    UpdateStatus(pFileInfo, 0);
#endif
	    
	    fReturn = TRUE;
	    break;
	}
	
	}
	else            
	{
	if (StartDSound(hWnd, pFileInfo) == 0)
	{
	    SendMessage((HWND)lParam,
		WM_SETTEXT, 0, (LPARAM)(LPCTSTR)szStop);
#ifdef SHOWSTATUS
	    UpdateStatus(pFileInfo, DSBSTATUS_PLAYING);
#endif
		    
	    fReturn = TRUE;
	    break;
	}
	
	}
	fReturn = TRUE;
    }
	
    else if ((HWND)lParam == pFileInfo->hWndRemove_BN)
    {
	ReleaseDirectSoundBuffer(pFileInfo);
	RemoveFromList(pFileInfo, &FileInfoFirst);
        UpdateMainStatus();
	
	fReturn = TRUE;
    }
	

    pFileInfo = pFileInfoNext;
    
    }
    
    if (!fReturn)
    {

    switch(wParam)
    {

	case IDPD_FILE_EXIT:    
	PostMessage(hWnd, WM_CLOSE, 0, 0);
	break;

	case IDPD_FILE_OPEN:
	PD_FileOpen(hWnd);
	break;
	    
	case IDPD_HELP_ABOUT:
	DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUT),
	      hWnd, (DLGPROC)DLGHelpAbout);
	break;

	case IDPD_OPTIONS_OUTPUTTYPE:
	DialogBox(hInst, MAKEINTRESOURCE(IDD_OUTPUTBUFFERTYPE),
	      hWnd, (DLGPROC)DLGOutputBufferType);
	break;

	case IDPD_CHECKLATENCY:
	StopAllDSounds(hWnd, &FileInfoFirst);
	// Now fake that we're on in each voice so the
	//timer will update the 
	// strings in the window.
	pFileInfo = FileInfoFirst.pNext;
	while (pFileInfo != NULL)
	{                                           
	    pFileInfo->fPlaying = TRUE;
	    pFileInfo = pFileInfo->pNext;       
	}

	DialogBox(hInst, MAKEINTRESOURCE(IDD_CHECKLATENCY),
	      hWnd, (DLGPROC)DLGCheckLatency);
	break;

	    case IDPD_ENUMDRIVERS:
		fEnumDrivers = !fEnumDrivers;
		if( fEnumDrivers )
		    {
		    MessageBox( hWnd,
		    "Drivers will not be enumerated until DSSHOW is run again.",
		    szAppName, MB_OK );
		    }
		break;

	default:
	return(FALSE);
	
    }
    }

    return(TRUE);


}

// =======================================================================
/*  This routine will handle the timer messages.

    Input:
	Standard input.

    Output: 
	TRUE if processed message, otherwise FALSE
*/
// =======================================================================
BOOL UIMainWindowTimerHandler(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    FILEINFO        *pFileInfo;
    BOOL            fReturn             = FALSE;
    DWORD           dwStatus            = 0;

    for (pFileInfo = FileInfoFirst.pNext; pFileInfo != NULL; pFileInfo = pFileInfo->pNext)
    {
    HRESULT hr;

    hr = IDirectSoundBuffer_GetStatus(pFileInfo->pDSB, &dwStatus);
    if (DS_OK != hr) continue;

    if (dwStatus & DSBSTATUS_BUFFERLOST) {
	LPBYTE pbData, pbData2;
	DWORD  dwLength, dwLength2;
	
	//
	//  Restore the buffer, rewrite data, and play
	//
	hr = IDirectSoundBuffer_Restore(pFileInfo->pDSB);
	if (DS_OK == hr) {

	hr = IDirectSoundBuffer_Lock(pFileInfo->pDSB, 0,
			 pFileInfo->cbSize,
			 &pbData, &dwLength,
			 &pbData2, &dwLength2,
			 0);

	if (DS_OK == hr) {
	
	    Assert(pbData != NULL);
	    Assert(pFileInfo->pbData != NULL);
	    memcpy(pbData, pFileInfo->pbData, pFileInfo->cbSize);

	    hr = IDirectSoundBuffer_Unlock(pFileInfo->pDSB,
				       pbData, dwLength,
				       NULL, 0);

	    if (DS_OK == hr) {

	    if (pFileInfo->fPlaying) {
		if (pFileInfo->fLooped) {
		IDirectSoundBuffer_Play( pFileInfo->pDSB, 0, 0,
					 DSBPLAY_LOOPING );
		} else {
		IDirectSoundBuffer_Play( pFileInfo->pDSB, 0, 0,
					 0 );
		}
	    }

	    IDirectSoundBuffer_GetStatus(pFileInfo->pDSB, &dwStatus);

	    }
	}
	}
    }

#ifdef SHOWSTATUS
    UpdateStatus(pFileInfo, dwStatus);
#endif

    if (!(dwStatus & DSBSTATUS_BUFFERLOST))
    {
	if ((pFileInfo->fPlaying) && (!(dwStatus & DSBSTATUS_PLAYING)) )
	{
	if (StopDSound(hWnd, pFileInfo) == 0)
	{
	    SendMessage(pFileInfo->hWndPlay_BN,
		WM_SETTEXT, 0, (LPARAM)(LPCTSTR)szPlay);
	}
	}
    }

    pFileInfo->fLost = dwStatus & DSBSTATUS_BUFFERLOST;

    fReturn = TRUE;
    }

    return (fReturn);

}   



// =======================================================================
/*  This routine will start a sound to be played.  
    Input:
	hWnd        -   Of parent window.
	pFileInfo   -   Pointer to file to start,
		which is loaded and the
		data is filled in the structure,
		such as pbData, 
		etc.

    Output:
	0 if successful, else the error code.
*/
// =======================================================================
int StartDSound(HWND hWnd, FILEINFO *pFileInfo)
{
    HRESULT     hr              = 0;
    DWORD           dwLooped;
    DWORD           dwStatus                = 0;

    // Already playing?

    // Start sound here....
    dwLooped = 0;
    if (pFileInfo->fLooped) {
    dwLooped = DSBPLAY_LOOPING;
    }
		    

    if ((hr = pFileInfo->pDSB->lpVtbl->GetStatus(pFileInfo->pDSB,
			 &dwStatus)) == 0)
    {
    if ((dwStatus&DSBSTATUS_PLAYING) == DSBSTATUS_PLAYING)
    {
	// Don't bother playing, just restart
	if ((hr = pFileInfo->pDSB->lpVtbl->SetCurrentPosition(
	    pFileInfo->pDSB, 0)) != 0)
	{
	MessageBox(hWnd, "Cannot set current position",
	       "Direct Sound Error", MB_OK);
	}
    }
    // Yes gotos are bad but this is real life not school.
    else goto PLAY_THE_THING;           
    }
    
    else
    {
PLAY_THE_THING:
    if ((hr = pFileInfo->pDSB->lpVtbl->Play(pFileInfo->pDSB,
					    0, 0, dwLooped)) != 0)
    {
    MessageBox(hWnd, "Cannot start playing",
	   "Direct Sound Error", MB_OK);
    }
    else
    pFileInfo->fPlaying = TRUE;
    }

    return(hr);


}

// =======================================================================
/*  This routine will stop a sound which is playing.

    Input:
	hWnd        - Of parent window.
	pFileInfo       - Pointer to file to stop playing.

    Output:
	0 if successful, else the error code.

*/
// =======================================================================
int StopDSound(HWND hWnd, FILEINFO *pFileInfo)
{
    HRESULT     hr          = 0;

    if (!pFileInfo->fPlaying)
    return(0);
	   

    // Stop sound here...
    if ((hr = pFileInfo->pDSB->lpVtbl->Stop(pFileInfo->pDSB)) != 0) 
    {
    MessageBox(hWnd, "Cannot stop sound",
	   "Direct Sound Error", MB_OK);        
    }
    else
    pFileInfo->fPlaying = FALSE;    

    return(hr);

}

// =======================================================================
/*  This routine will stop all the sounds which are playing.

    Input:
	hWnd        - Of parent window.
	pFileInfo   - Pointer to file to stop playing.
		(i.e. the head)

    Output:
	0 if successful, else the error code.

*/
// =======================================================================
int StopAllDSounds(HWND hWnd, FILEINFO *pFileInfo)
{
    while (pFileInfo->pNext != NULL)
	{
	StopDSound(hWnd, pFileInfo->pNext);
	pFileInfo = pFileInfo->pNext;       
	}

    return(0);

}



// =======================================================================
/*  This routine will set the freq, vol and pan slider text
    according to the value 
    passed in.

    Input:
	pFileInfo   -   File pointer to set frequency for.

    The dwFreq in the pFileInfo structure must be set.
    This also uses the window handle
    in the pFileInfo structure.
    
    Output:
	None.
*/
// =======================================================================
void SetAllText(FILEINFO    *pFileInfo)
{
    char            szBufT[128];

    sprintf(szBufT, "%s: %lu Hz     ",
	szFreq, pFileInfo->dwFreq);
    SetWindowText(pFileInfo->hWndFreq_TXT, szBufT);

    // Change PAN val to show full range
    sprintf(szBufT, "%s: %ld", szPan,
	(((LONG)(pFileInfo->dwPan) + SHIFTPAN_TB) * MULTPAN_TB ) );
    SetWindowText(pFileInfo->hWndPan_TXT, szBufT);

    // Change VOLUME val to show full range
    sprintf(szBufT, "%s: %ld", szVolume,
	(((LONG)(pFileInfo->dwVol) + SHIFTVOL_TB) * MULTVOL_TB ));
    SetWindowText(pFileInfo->hWndVol_TXT, szBufT);


}

// =======================================================================
/*  This routine will update the left and right
    volume according to main volume 
    and pan.

    Input:
	pFileInfo   - Pointer to fileinfo to update.

    Output:
	Nothing worth using.
*/
// =======================================================================
void UpdateLRVolume(FILEINFO *pFileInfo)
{

    int             volLeft, volRight;

    if (pFileInfo->dwPan < MIDPAN_TB)
    {
    volLeft = pFileInfo->dwVol;
    volRight = (((int)pFileInfo->dwPan)
	    *(int)pFileInfo->dwVol)/((int)MIDPAN_TB);
    }
    else
    {
    volLeft = ((((int)pFileInfo->dwPan - MAXPAN_TB)*-1)
	   *(int)pFileInfo->dwVol)/((int)MIDPAN_TB);
    volRight = pFileInfo->dwVol;
    }

	

    SendMessage(pFileInfo->hWndVolL_TB, TBM_SETPOS, TRUE, MAXVOL_TB-volLeft);
    SendMessage(pFileInfo->hWndVolR_TB, TBM_SETPOS, TRUE, MAXVOL_TB-volRight);
    
	

}

// =======================================================================
/*  This will change the output panning position for a certain FILEINFO.
    This is 
    done by sending messages to the direct sound driver 

    Input:  
	pFileInfo   -   FileInfo to set.  This must contain the
		panning value to set.

    Output:
	0 if successful, else the error code.

*/
// =======================================================================
int ChangeOutputPan(FILEINFO *pFileInfo)
{

    HRESULT     hr      = 0;

    // Change PAN val  since TB does not go full range
    if ((hr = pFileInfo->pDSB->lpVtbl->SetPan(pFileInfo->pDSB,
	(((pFileInfo->dwPan) + SHIFTPAN_TB) * MULTPAN_TB) )) != 0)
    {
	goto ERROR_DONE_ROUTINE;
    }

ERROR_DONE_ROUTINE:
    return(hr);

}

// =======================================================================
/*  This will change the output freq for a certain FILEINFO.  This is 
    done by sending messages to the direct sound driver 

    Input:  
	pFileInfo                   -   FileInfo to set.  This must contain the
					freq value to set.

    Output:
	0 if successful, else the error code.

*/
// =======================================================================
int ChangeOutputFreq(FILEINFO *pFileInfo)
{

    HRESULT     hr      = 0;

    if ((hr = pFileInfo->pDSB->lpVtbl->SetFrequency(pFileInfo->pDSB, pFileInfo->dwFreq)) != 0)
	{
	goto ERROR_DONE_ROUTINE;
	}

ERROR_DONE_ROUTINE:
    return(hr);

}



// =======================================================================
/*  This will change the output vol for a certain FILEINFO.  This is 
    done by sending messages to the direct sound driver 

    Input:  
	pFileInfo                   -   FileInfo to set.  This must contain the
					freq value to set.

    Output:
	0 if successful, else the error code.

*/
// =======================================================================
int ChangeOutputVol(FILEINFO *pFileInfo)
{

    HRESULT     hr      = 0;

    // Shift VOLUME val by 4 bits since TB does not go full range
    if ((hr = pFileInfo->pDSB->lpVtbl->SetVolume(pFileInfo->pDSB,
	(((pFileInfo->dwVol) + SHIFTVOL_TB) * MULTVOL_TB) )) != 0)
	{
	goto ERROR_DONE_ROUTINE;
	}

ERROR_DONE_ROUTINE:
    return(hr);

}


// =======================================================================
/*  This is the dialog box handler for the check latency dialog box.

    Input:
	Standard dialog box input.

    Output:
	Standard dialog box output.

*/
// =======================================================================
long FAR PASCAL DLGCheckLatency(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

    static HWND     hWndFiles_LB;
    FILEINFO        *pFileInfo              = NULL;
    int         nSelected;
    int         cT;


    switch(uMsg)
    {
    case WM_INITDIALOG:
	hWndFiles_LB = GetDlgItem(hWnd, IDC_FILES_LB);
	
	pFileInfo = FileInfoFirst.pNext;
	while (pFileInfo != NULL)
	{               
	SendMessage(hWndFiles_LB,
		LB_ADDSTRING,
		0,
		(LPARAM)(pFileInfo->szFileName
		     + pFileInfo->nFileName));
		pFileInfo = pFileInfo->pNext;       
	}

	break;      
	
    case WM_COMMAND:
	switch(wParam)
	{
	case ID_DONE:                   
	    PostMessage(hWnd, WM_CLOSE, 0, 0);
	    break;
	    
	case ID_PLAY:                       
	    if ((nSelected = SendMessage(hWndFiles_LB,
			 LB_GETCURSEL, 0, 0))
		!= LB_ERR)
	    {
	    for (cT=0, pFileInfo = FileInfoFirst.pNext;
		pFileInfo != NULL;
		pFileInfo = pFileInfo->pNext, cT++)
	    {
		if (cT == nSelected)
		{
		StartDSound(hWnd, pFileInfo);
		break;
		}
	    }
	    
	    }
		    
	    break;
		    
	case ID_STOP:
	    StopAllDSounds(hWnd, &FileInfoFirst);
	    break;
	    
	default:
	    break;
	    
	}
	break;

    case WM_CLOSE:
	StopAllDSounds(hWnd, &FileInfoFirst);
	EndDialog(hWnd, 0);
	break;

    default:
	return(0);
	break;               
	
    }
    
    return(1);

}


// =======================================================================
/*  The help about dialog procedure.  
    
    Input:
	Standard windows dialog procedure.

    Output:
	Standard windows dialog procedure.

*/
// =======================================================================
long FAR PASCAL DLGHelpAbout(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
    case WM_INITDIALOG:
	break;      
	
    case WM_COMMAND:
	switch(wParam)
	{
	case ID_OK:                 
	    PostMessage(hWnd, WM_CLOSE, 0, 0);
	    break;
	    
	default:
	    break;
	    
	}
	break;
	
    case WM_CLOSE:
	EndDialog(hWnd, 0);
	break;

    default:
	return(0);
	break;               

    }
    
    return(1);

}


// =======================================================================
/*  The help about dialog procedure.  
    
    Input:
	Standard windows dialog procedure.

    Output:
	Standard windows dialog procedure.

*/
// =======================================================================
long FAR PASCAL DLGOutputBufferType(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam)
{

    static HWND     hWndFormats_LB          = NULL;
    int         cT;
    int         nSelection;

	     
    switch(uMsg)
    {
    case WM_INITDIALOG:
	// Get the windows we need.
	hWndFormats_LB = GetDlgItem(hWnd, IDC_FORMATS);
	
	// Put the strings in the list box.
	for (cT=0; cT<C_DROPDOWNPCMFORMATS; cT++)
	SendMessage(hWndFormats_LB,
		LB_ADDSTRING, 0, (LPARAM)rgszTypes[cT]);

	// Get the current format and highlight it in the list box.
	if ((nSelection = FormatToIndex(hWnd, &FileInfoFirst)) != LB_ERR)
	{
	SendMessage(hWndFormats_LB, LB_SETCURSEL, nSelection, 0);
	}


	break;      
	
    case WM_COMMAND:
	    switch(LOWORD(wParam))
	{
		case IDC_FORMATS:
		    if( HIWORD( wParam ) == LBN_DBLCLK )
			{
			SendMessage( hWnd, WM_COMMAND, MAKEWPARAM( ID_OK, 0 ),
									0L );
			}
		    break;

		case ID_OK:
	    if ((nSelection = SendMessage(hWndFormats_LB,
		LB_GETCURSEL, 0, 0)) != LB_ERR)
	    {
	    if (IndexToFormat(hWnd, &FileInfoFirst, nSelection)
		    == 0)
		PostMessage(hWnd, WM_CLOSE, 0, 0);
	    }
	    break;
		
	case ID_CANCEL:                 
	    PostMessage(hWnd, WM_CLOSE, 0, 0);
	    break;

	case ID_APPLY:                  
	    if ((nSelection = SendMessage(hWndFormats_LB,
		LB_GETCURSEL, 0, 0)) != LB_ERR)
	    IndexToFormat(hWnd, &FileInfoFirst, nSelection);
			
	    break;


	default:
	    break;

	}
	break;

    case WM_CLOSE:
	EndDialog(hWnd, 0);
	break;

    default:
	return(0);
	break;               

    }
		
    return(1);

}

// =======================================================================
/*  This routine will determine the output format in
    terms of an integer from the
    current output rate, type, etc.
    stored in the direct sound routines.   Integer
    values designate the string # in rgszTypes,
    i.e. index 0 is 8000kHz, 8 bit mono, 
    etc...

    Input:
	hWnd    - Handle of the current window.
	pFileInfo   - Pointer to the file info to retrieve the format for.

    Output:
	The index of the format, LB_ERR if undetermined.

*/
// =======================================================================
int FormatToIndex(HWND hWnd, FILEINFO *pFileInfo)
{

    WAVEFORMATEX    wfx;
    DWORD       dwWaveStyle;
    DWORD       dwSize;
    int         nError              = 0;

    // Get the format.
    if ((nError = pFileInfo->pDSB->lpVtbl->GetFormat(pFileInfo->pDSB,
	    &wfx, sizeof(wfx), &dwSize)) != 0)
    {
    goto ERROR_IN_ROUTINE;
    }
    if( dwSize > sizeof( wfx ) ) {
    nError = DSERR_GENERIC;
    goto ERROR_IN_ROUTINE;
    }


    // Change wfx to an integer.
    // Assume theres an error and check all parameters to 
    // see if its valid.
    nError = LB_ERR;
    dwWaveStyle = 0;

    if (wfx.wFormatTag != WAVE_FORMAT_PCM)
	   goto ERROR_IN_ROUTINE;

    // Check the channels
	switch (wfx.nChannels)
	{
	case 1:
		break;

	case 2:
	    dwWaveStyle |= 1;
		break;

    default:
		goto ERROR_IN_ROUTINE;
	}

    // Check the bits...
	switch (wfx.wBitsPerSample)
	{
	case 8:
		break;

	case 16:
		dwWaveStyle |= 2;
		break;

    default:
		goto ERROR_IN_ROUTINE;
    }

    // Check the rate.
	switch(wfx.nSamplesPerSec)
	{
	case 8000:
		break;

	case 11025:
	    dwWaveStyle |= 4;
		break;

	case 22050:
	    dwWaveStyle |= 8;
		break;

	case 44100:
	    dwWaveStyle |= 12;
		break;

    default:
		goto ERROR_IN_ROUTINE;
    }

    nError = (int)dwWaveStyle;

ERROR_IN_ROUTINE:
    return(nError);
}


// =======================================================================
/*  This will convert an index (from a list box for instance)
    to a format by passing
    in the format to direct sound.

    Input:
	hWnd        -   Handle to window.
	pFileInfo   -   Pointer to current file info.
	index       -   Index value to convert to a
		    waveformat structure.

    Output:
	0 if successful, else the error code.
*/
// =======================================================================
int IndexToFormat(HWND hWnd, FILEINFO *pFileInfo, int index)
{

    int         nError      = 0;


    pFileInfo->pwfx->wFormatTag = WAVE_FORMAT_PCM;

    pFileInfo->pwfx->nChannels = 2;                                     // Assume stereo.
    if ((index%2) == 0)
    pFileInfo->pwfx->nChannels = 1;                                 // Its mono.
	
    // Assume 16 bit    
    pFileInfo->pwfx->nBlockAlign = 2*pFileInfo->pwfx->nChannels;
    pFileInfo->pwfx->wBitsPerSample = 16;
    if ((index%4) < 2) {
    // Its 8 bit.
    pFileInfo->pwfx->nBlockAlign = 1*pFileInfo->pwfx->nChannels;
    pFileInfo->pwfx->wBitsPerSample = 8;
    }
    
    pFileInfo->pwfx->nSamplesPerSec = 44100;    // Assume 44.1 kHz
    if (index < 4)
	pFileInfo->pwfx->nSamplesPerSec = 8000;
    else if (index < 8)
	pFileInfo->pwfx->nSamplesPerSec = 11025;
    else if (index < 12)
	pFileInfo->pwfx->nSamplesPerSec = 22050;
    
    
    pFileInfo->pwfx->nAvgBytesPerSec = pFileInfo->pwfx->nSamplesPerSec *
		       pFileInfo->pwfx->nBlockAlign;                                        
    pFileInfo->pwfx->cbSize = 0;

    if ((nError = pFileInfo->pDSB->lpVtbl->SetFormat(pFileInfo->pDSB,
			pFileInfo->pwfx)) != DS_OK)         {
	MessageBox(hWnd, "Cannot set format buffer",
	   "Direct Sound Error", MB_OK);
    goto ERROR_DONE_ROUTINE;

    }

ERROR_DONE_ROUTINE:
    return(nError);

}


// =======================================================================
/* GetMediaStartPath()                                                      */
/*                                                                          */
/*   This helper function attempts to get the media directory for Direct3D, */
/* which is where all the installed DX wave files go. If it can't find that */
/* it settles for the media sub-directory of the Windows directory.         */
// =======================================================================
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
	cbStartPathLen = sizeof( gszCDStartPath );
	if( ERROR_SUCCESS != RegQueryValueEx( hReg, gszRegValueD3DPath,
				NULL, NULL,
				gszCDStartPath, &cbStartPathLen ))
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
    GetWindowsDirectory( gszCDStartPath, sizeof(gszCDStartPath));
    // If there's no trailing backslash, append one
    if( lstrcmp( &gszCDStartPath[lstrlen(gszCDStartPath)], TEXT("\\") ))
	lstrcat( gszCDStartPath, TEXT("\\"));
    // Now add on the MEDIA part of the path
    lstrcat( gszCDStartPath, TEXT("MEDIA"));
    }


// =======================================================================
// fGetToken()
//
//    Parses the command-line string "in place" starting at pszStart.  A ptr
// to the start of the next token and it's length will be the out parameters,
// or NULL and 0 if no token.  Note that *ppszRet will NOT be NULL-terminated
// since the string is part of another string.  That's what then length is for.
//
// Returns: TRUE if a token was retrieved, or FALSE if there was no token.
// =======================================================================
BOOL fGetToken( PSTR pszStart, PSTR *ppszRet, int *pcchRet )
    {
    PSTR  pszCur = pszStart;
    PSTR  pszTokStart;

    if( !pszStart || NULL == ppszRet || NULL == pcchRet )
	return FALSE;

    // Skip leading whitespace
    while( *pszCur && (*pszCur == ' ' || *pszCur == '\t'))
	pszCur++;

    *ppszRet = NULL;
    *pcchRet = 0;

    if( *pszCur )
	{
	pszTokStart = pszCur;

	while( *pszCur && *pszCur != ' ' && *pszCur != '\t' )
	    pszCur++;

	*ppszRet = pszTokStart;
	*pcchRet = (int)(pszCur - pszTokStart);
	}

    if( *pcchRet != 0 )
	return TRUE;
    else
	return FALSE;
    }


// =======================================================================
// fMatchToken()
//
//    Attempts to match the first cchLen characters of pszDatum to the
// string at pszString.  The comparison is case-insensitive (this function
// is designed for command-line switch matching).
//
// Returns: TRUE if the first cchLen characters are a match, else FALSE.
// =======================================================================
BOOL fMatchToken( PSTR pszString, PSTR pszDatum, int cchLen )
    {
    int	i;

    for( i = 0; i < cchLen; i++ )
	{
	if( CharLower( (LPTSTR)MAKELONG( pszString[i], 0 ))
		    != CharLower( (LPTSTR)MAKELONG( pszDatum[i], 0 )))
	    return FALSE;
	}
    return TRUE;
    }


// =======================================================================
// ParseCommandLine()
//
//    Given a command-line string without the module name, this function will
// parse the command line and takes action on whatever it finds there.
//
// Returns: TRUE if successful, or FALSE if there was an error.
// =======================================================================
BOOL ParseCommandLine(LPSTR lpszCmdLine)
    {
    PSTR	pszCur,pszToken;
    PSTR	ppszFiles[MAXCONTROLS];
    BOOL	fStartPlaying = FALSE, fStartLooping = FALSE;
    int		cchTokLen = 0, i, nFilesFound;

    pszCur = lpszCmdLine;

    // First get all the command line switches
    while( fGetToken(pszCur, &pszToken, &cchTokLen) &&
	   (pszToken[0] == '/' || pszToken[0] == '-' ))
	{
	pszCur = pszToken + cchTokLen;
	pszToken++;

	if( fMatchToken( pszToken, "PLAY", 4 ))
	    {
	    fStartPlaying = TRUE;
	    }
	else if( fMatchToken( pszToken, "LOOP", 4 ))
	    {
	    fStartLooping = TRUE;
	    }
	else
	    {
	    // We don't recognize this mysterious switch, so eat it and move on
	    }
	}

    // Anything left on the command-line will be treated as a filename and
    // we'll attempt to open it after we've found them all
    nFilesFound = 0;
    while( fGetToken(pszCur, &pszToken, &cchTokLen) && nFilesFound < MAXCONTROLS )
	{
	pszCur = pszToken + cchTokLen;
	ppszFiles[nFilesFound] = GlobalAllocPtr( GPTR, (cchTokLen+1)*sizeof(char));
	// Copy the token out of the command-line string and into our buffer
	CopyMemory( ppszFiles[nFilesFound], pszToken, cchTokLen*sizeof(char));
	// Append a NULL terminator to what we just copied (to be safe)
	*(ppszFiles[nFilesFound] + cchTokLen) = 0;
	nFilesFound++;
	}
    // This function will take the array of strings we've created and open
    // each string as a file.  It will obey the global fStartPlaying and
    // fStartLooping flags we may have already set above
    if( nFilesFound )
	BatchOpenFiles( ppszFiles, nFilesFound, fStartPlaying, fStartLooping );

    // Free the space we allocated
    for( i = 0; i < nFilesFound; i++ )
	{
	GlobalFreePtr( ppszFiles[i] );
	ppszFiles[i] = NULL;
	}

    // Returning TRUE means the caller should continue doing what they
    // were doing: we succeeded.
    return TRUE;
    }


// =======================================================================
// BatchOpenFiles()
//
//    Takes an array of string pointers and tries to open each as a file to
// playback.  If fPlay is TRUE, the files will be played as they are being
// opened.  If fLoop is TRUE, they will also be set to loop.
//
// Returns: FALSE in the event of catastrophic failure, otherwise TRUE.
// =======================================================================
BOOL BatchOpenFiles( PSTR *ppszFiles, int nFiles, BOOL fPlay, BOOL fLoop )
    {
    int i;
    FILEINFO *pfi;
    DWORD cSamples;

    // Cap the number of files we can load out of the given set if we'd load
    // too many otherwise
    if( GetNumControls(&FileInfoFirst) + nFiles > MAXCONTROLS )
	nFiles = MAXCONTROLS - GetNumControls(&FileInfoFirst);
	
    for( i = 0; i < nFiles; i++ )
	{
	if(( pfi = GlobalAllocPtr(GPTR, sizeof(FILEINFO))) == NULL )
	    goto BOF_Fail;

	ZeroMemory( pfi, sizeof(FILEINFO));
	strcpy( pfi->szFileName, ppszFiles[i] );

	if( WaveLoadFile( ppszFiles[i], &pfi->cbSize, &cSamples,
			  &pfi->pwfx, &pfi->pbData ) != 0 )
	    goto BOF_LoopError;

	GetNextControlCoords( &FileInfoFirst, &pfi->cox, &pfi->coy );
	if( NewDirectSoundBuffer(pfi) != 0)
	    goto BOF_LoopError;
	Assert( pfi->pbData != NULL );

	if( AddToList( &FileInfoFirst, pfi ) != 0 )
	    goto BOF_LoopError;

	pfi->nFileName = 0;

	if( CreateControl( hWndMain, pfi, pfi->pwfx->nSamplesPerSec,
		       (MAXPAN_TB-MINPAN_TB)/2, MINVOL_TB ) != 0 )
	    {
	    ReleaseDirectSoundBuffer(pfi);
	    RemoveFromList( pfi, &FileInfoFirst );
	    // RemoveFromList will do all the cleanup
	    pfi = NULL;
	    goto BOF_LoopError;
	    }
	ChangeOutputVol(pfi);
	ChangeOutputFreq(pfi);
	ChangeOutputPan(pfi);

	// LOOP is only obeyed if PLAY was also specified
	if( fPlay )
	    {
	    if( fLoop )
		{
		pfi->fLooped = TRUE;
		SendMessage( pfi->hWndLooped_BN, BM_SETCHECK, TRUE, 0L );
		}
	    SendMessage( hWndMain, WM_COMMAND, 0, (LPARAM)pfi->hWndPlay_BN );
	    }

	// Avoid the in-loop error cleanup by using a continue statement here
	// to jump back up to the top
	continue;
	
	// Cleanup code in case we fail to open a particular file -- we should
	// just ignore this one and continue because we might still be able to
	// open other files
    BOF_LoopError:
	if( NULL != pfi )
	    {
	    if( NULL != pfi->pwfx )
		{
		GlobalFreePtr(pfi->pwfx);
		pfi->pwfx = NULL;
		}
	    if( NULL != pfi->pbData )
		{
		GlobalFreePtr(pfi->pbData);
		pfi->pbData = NULL;
		}

	    ReleaseDirectSoundBuffer(pfi);
	    GlobalFreePtr(pfi);
	    pfi = NULL;
	    }
	}

    UpdateMainStatus();

    return TRUE;

BOF_Fail:
    return FALSE;
    }




