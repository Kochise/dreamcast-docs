/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999,2000 Microsoft Corporation

Module Name:

    InitPC.cpp

Abstract:

    PC specific initialization code. Includes startup
	configuration dialog.

-------------------------------------------------------------------*/

#include "DC.h"
#include "DCGraphics.h"
#include "DCSound.h"
#include "DCInput.h"
#include "DCTimer.h"
#include "DCNetwork.h"
#include "DCSound.h"

// Configuration.
static int ResX,ResY;
static BOOL Bits32,Windowed,TripleBuffer;
static BOOL Network,Server;
static int ComPort;

//************************************************************************
// Code for handling the config dialog box.
//************************************************************************
static struct
{
	char *Desc;
	int  X,Y;
} Resolutions[]=
{
	{"640 x 480",640,480},	
	{"800 x 600",800,600},	
	{"1024 x 768",1024,768},	
	{"1152 x 864",1152,864},	
	{"1280 x 1024",1280,1024},
	{"1600 x 1200",1600,1200},
	{NULL,0,0}
};

// Centres a Window on the screen.
static void CentreWindow(HWND hWnd)
{
	int x,y;
	RECT WR;
	
	GetWindowRect(hWnd,&WR);
	x=(GetSystemMetrics(SM_CXFULLSCREEN)+WR.left-WR.right)/2;
	y=(GetSystemMetrics(SM_CYFULLSCREEN)+
	   GetSystemMetrics(SM_CYCAPTION) +WR.top-WR.bottom)/2;
	SetWindowPos(hWnd,0,x,y,0,0,SWP_NOACTIVATE | SWP_NOSIZE | SWP_NOZORDER);
}

// Dialog handler for configuration screen.
BOOL CALLBACK ConfigDialogProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	int i;

	switch (uMsg)
	{
		case WM_INITDIALOG:
			CentreWindow(hWnd);
			// Init drop box.
			for (i=0;Resolutions[i].Desc!=NULL;i++)
				SendDlgItemMessage(hWnd,IDC_RESOLUTION,CB_ADDSTRING,0,
								  (LPARAM)(LPSTR)Resolutions[i].Desc);	
			// Select an item in drop box.
			SendDlgItemMessage(hWnd,IDC_RESOLUTION,CB_SETCURSEL,
							   2,0);

			// Init com port drop box.
			for (i=0;i<4;i++)
			{
				TCHAR Buffer[7];
				wsprintf(Buffer,TEXT("COM%i"),i+1);
				SendDlgItemMessage(hWnd,IDC_COMPORT,CB_ADDSTRING,0,
								  (LPARAM)Buffer);
			}
			// Select an item in drop box.
			SendDlgItemMessage(hWnd,IDC_COMPORT,CB_SETCURSEL,
							   0,0);

			// Init radio buttons.
			SendDlgItemMessage(hWnd,IDC_16BIT,
							   BM_SETCHECK,BST_CHECKED,0);
			SendDlgItemMessage(hWnd,IDC_32BIT,
							   BM_SETCHECK,BST_UNCHECKED,0);
			SendDlgItemMessage(hWnd,IDC_WINDOWED,
							   BM_SETCHECK,BST_UNCHECKED,0);
			SendDlgItemMessage(hWnd,IDC_TRIPLE_BUFFER,
							   BM_SETCHECK,BST_CHECKED,0);
			SendDlgItemMessage(hWnd,IDC_NETWORK,
							   BM_SETCHECK,BST_UNCHECKED,0);
			SendDlgItemMessage(hWnd,IDC_SERVER,
							   BM_SETCHECK,BST_UNCHECKED,0);
			SendDlgItemMessage(hWnd,IDC_CLIENT,
							   BM_SETCHECK,BST_UNCHECKED,0);
			SendDlgItemMessage(hWnd,IDC_LOW_DETAIL,
							   BM_SETCHECK,BST_UNCHECKED,0);
			SendDlgItemMessage(hWnd,IDC_HIGH_DETAIL,
							   BM_SETCHECK,BST_CHECKED,0);
			
			// Disable drop box and server/client selection.
			EnableWindow(GetDlgItem(hWnd,IDC_COMPORT),FALSE);
			EnableWindow(GetDlgItem(hWnd,IDC_SERVER),FALSE);
			EnableWindow(GetDlgItem(hWnd,IDC_CLIENT),FALSE);

			// Init variables.
			ResX=1024;
			ResY=768;
			Bits32=FALSE;
			Windowed=FALSE;
			TripleBuffer=TRUE;
			Network=FALSE;
			ComPort=1;
			Server=FALSE;
			gHighDetail=TRUE;
			gHighTextureDetail=TRUE;
#ifdef _DEBUG
			// In debug builds, default to windowed mode, 1024x768.
			ConfigDialogProc(hWnd,WM_COMMAND,IDC_WINDOWED,0);
#endif
			return 1;
		case WM_CLOSE:
			// Close the dialog box
			EndDialog(hWnd,FALSE);
			return 1;

		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
				case IDSTART:
					// Close the dialog box
					EndDialog(hWnd,TRUE);
					break;
				case IDEXIT:
					// Close the dialog box
					EndDialog(hWnd,FALSE);
					break;
				case IDC_RESOLUTION:
					// Get resolution selection.
					i=SendDlgItemMessage(hWnd,IDC_RESOLUTION,CB_GETCURSEL,
										 0,0);
					ResX=Resolutions[i].X;
					ResY=Resolutions[i].Y;
					break;
				case IDC_16BIT:
					// Change to 16 bit.
					SendDlgItemMessage(hWnd,IDC_16BIT,
									   BM_SETCHECK,BST_CHECKED,0);
					SendDlgItemMessage(hWnd,IDC_32BIT,
									   BM_SETCHECK,BST_UNCHECKED,0);
					Bits32=FALSE;
					break;
				case IDC_32BIT:
					// Change to 32 bit.
					SendDlgItemMessage(hWnd,IDC_16BIT,
									   BM_SETCHECK,BST_UNCHECKED,0);
					SendDlgItemMessage(hWnd,IDC_32BIT,
									   BM_SETCHECK,BST_CHECKED,0);
					Bits32=TRUE;
					break;
				case IDC_WINDOWED:
					if (Windowed)
					{
						// Disable windowed mode.
						Windowed=FALSE;
						SendDlgItemMessage(hWnd,IDC_WINDOWED,
										   BM_SETCHECK,BST_UNCHECKED,0);
						// Enable bit depth settings.
						EnableWindow(GetDlgItem(hWnd,IDC_16BIT),TRUE);
						EnableWindow(GetDlgItem(hWnd,IDC_32BIT),TRUE);
						EnableWindow(GetDlgItem(hWnd,IDC_TRIPLE_BUFFER),TRUE);
						// Restore settings for bit depth.
						SendDlgItemMessage(hWnd,IDC_16BIT,
										   BM_SETCHECK,(Bits32)?BST_UNCHECKED:BST_CHECKED,0);
						SendDlgItemMessage(hWnd,IDC_32BIT,
										   BM_SETCHECK,(Bits32)?BST_CHECKED:BST_UNCHECKED,0);
						SendDlgItemMessage(hWnd,IDC_TRIPLE_BUFFER,
										   BM_SETCHECK,(TripleBuffer) ? BST_CHECKED : BST_UNCHECKED,0);
					}
					else
					{
						// Enabled windowed mode.
						Windowed=TRUE;
						SendDlgItemMessage(hWnd,IDC_WINDOWED,
										   BM_SETCHECK,BST_CHECKED,0);
						// Uncheck both bit depth settings.
						SendDlgItemMessage(hWnd,IDC_16BIT,
										   BM_SETCHECK,BST_UNCHECKED,0);
						SendDlgItemMessage(hWnd,IDC_32BIT,
										   BM_SETCHECK,BST_UNCHECKED,0);
						SendDlgItemMessage(hWnd,IDC_TRIPLE_BUFFER,
										   BM_SETCHECK,BST_UNCHECKED,0);
						// Disable bit depth settings.
						EnableWindow(GetDlgItem(hWnd,IDC_16BIT),FALSE);
						EnableWindow(GetDlgItem(hWnd,IDC_32BIT),FALSE);
						EnableWindow(GetDlgItem(hWnd,IDC_TRIPLE_BUFFER),FALSE);
					}
					break;
				case IDC_TRIPLE_BUFFER:
					TripleBuffer=(TripleBuffer) ? FALSE : TRUE;
					SendDlgItemMessage(hWnd,IDC_TRIPLE_BUFFER,
									   BM_SETCHECK,(TripleBuffer) ? BST_CHECKED : BST_UNCHECKED,0);
					break;
				case IDC_NETWORK:
					Network=(Network) ? FALSE : TRUE;
					SendDlgItemMessage(hWnd,IDC_NETWORK,
									   BM_SETCHECK,(Network) ? BST_CHECKED : BST_UNCHECKED,0);
					EnableWindow(GetDlgItem(hWnd,IDC_COMPORT),Network);
					EnableWindow(GetDlgItem(hWnd,IDC_SERVER),Network);
					EnableWindow(GetDlgItem(hWnd,IDC_CLIENT),Network);
					SendDlgItemMessage(hWnd,IDC_SERVER,
									   BM_SETCHECK,(Server && Network) ? BST_CHECKED : BST_UNCHECKED,0);
					SendDlgItemMessage(hWnd,IDC_CLIENT,
									   BM_SETCHECK,(!Server && Network) ? BST_CHECKED : BST_UNCHECKED,0);
					break;
				case IDC_COMPORT:
					ComPort=1+SendDlgItemMessage(hWnd,IDC_COMPORT,CB_GETCURSEL,
												 0,0);
					break;
				case IDC_SERVER:
					Server=TRUE;
					SendDlgItemMessage(hWnd,IDC_SERVER,
									   BM_SETCHECK,BST_CHECKED,0);
					SendDlgItemMessage(hWnd,IDC_CLIENT,
									   BM_SETCHECK,BST_UNCHECKED,0);
					break;
				case IDC_CLIENT:
					Server=FALSE;
					SendDlgItemMessage(hWnd,IDC_SERVER,
									   BM_SETCHECK,BST_UNCHECKED,0);
					SendDlgItemMessage(hWnd,IDC_CLIENT,
									   BM_SETCHECK,BST_CHECKED,0);
					break;
				case IDC_LOW_DETAIL:
					// Change to low detail.
					SendDlgItemMessage(hWnd,IDC_LOW_DETAIL,
									   BM_SETCHECK,BST_CHECKED,0);
					SendDlgItemMessage(hWnd,IDC_HIGH_DETAIL,
									   BM_SETCHECK,BST_UNCHECKED,0);
					gHighDetail=FALSE;
					gHighTextureDetail=FALSE;
					break;
				case IDC_HIGH_DETAIL:
					// Change to high detail.
					SendDlgItemMessage(hWnd,IDC_LOW_DETAIL,
									   BM_SETCHECK,BST_UNCHECKED,0);
					SendDlgItemMessage(hWnd,IDC_HIGH_DETAIL,
									   BM_SETCHECK,BST_CHECKED,0);
					gHighDetail=TRUE;
					gHighTextureDetail=TRUE;
					break;
			}
			return 1;
	}

	return 0;
}

//************************************************************************
// Global functions.
//************************************************************************
// Shutowns down video, audio etc.
void SystemShutdown(void)
{
	// Shutdown input.
	ShutdownInput(gGraphics.GetAppWindow());

	// Shutdown audio.
	ShutdownSound(gGraphics.GetAppWindow());

	// Shutdown video.
	gGraphics.Shutdown();

	// Shutdown the network.
	ShutdownNetwork();
	
	// Shutdown timer.
	ShutdownTimer();

	// Shutdown noise.
	ShutdownNoise();
}

// Gets settings and then initializes video, audio etc.
BOOL SystemInitialize(void)
{
	// Init noise functions.
	if (!InitNoise())
		return FALSE;

	// Initlialize timer functions.
	if (!InitTimer())
	{
		SystemShutdown();
		return FALSE;
	}

	// Put up a dialog box so the user can select a configuration.
	// We should really enumerate the hardware capabilities here and
	// only display what the hardware can do. Instead we'll let the
	// the user select anything and give an error message if that fails.
	if (DialogBox(gHInstance,
				   MAKEINTRESOURCE(IDD_CONFIG),
				   HWND_DESKTOP,
				   ConfigDialogProc)==FALSE)
		return FALSE;	// User exited.
	

	// Initialize the network.
	if (Network)
	{
		if (!InitNetwork(Server,ComPort))
		{
			SystemShutdown();
			return FALSE;
		}
	}

	// Initialize video by Initializing graphics class.
	if (!gGraphics.Initialize(NULL,
							  ResX,
							  ResY,
							  (Bits32) ? 32 : 16,
							  Windowed,
							  TripleBuffer))
	{
		// Shutdown anything that got initialized.
		SystemShutdown();
		return FALSE;
	}

	// Initialize audio.
	if (!InitSound(gGraphics.GetAppWindow()))
	{
		SystemShutdown();
		return FALSE;
	}

	// Initialize input.
	if (!InitInput(gGraphics.GetAppWindow()))
	{
		SystemShutdown();
		return FALSE;
	}

	return TRUE;
}
