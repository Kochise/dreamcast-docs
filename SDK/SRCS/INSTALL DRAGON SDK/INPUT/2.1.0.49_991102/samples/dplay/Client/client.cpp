/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    Client.cpp

Abstract:

    Client DirectPlay Application

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "initguid.h"
#include "dplay.h"
#include "dplobby.h"

#include "Client.h"



#ifndef UNDER_CE

extern "C"
{
WINBASEAPI
LPWSTR
WINAPI
GetCommandLineW(
    VOID
    );

WINUSERAPI
BOOL
WINAPI
ShowWindow(
    HWND hWnd,
    int nCmdShow);

WINUSERAPI
BOOL
WINAPI
UpdateWindow(
    HWND hWnd);
}

#ifndef WS_CAPTION
#define WS_CAPTION          0x00C00000L     /* WS_BORDER | WS_DLGFRAME  */
#define WS_SYSMENU          0x00080000L
#endif
#endif

// We hardcode use of the WSOCK TCP/IP SP
GUID GUID_WSOCK =
{ 0x36E95EE0, 0x8577, 0x11cf, { 0x96, 0xc, 0x0, 0x80, 0xc7, 0x53, 0x4e, 0x82 } };

const GUID GUID_NULL =
{ 0x0, 0x0, 0x0, { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0} };

GUID guidGame = GUID_NULL;

// {A139B272-192E-11d3-A25D-08002BC3C934}
static const GUID GUID_APPLICATION = 
{ 0xa139b272, 0x192e, 0x11d3, { 0xa2, 0x5d, 0x8, 0x0, 0x2b, 0xc3, 0xc9, 0x34 } };

void Usage()
{
    Output(TEXT("usage: Client host_name_or_ip_address\r\n"));
    Output(TEXT("                To join a session, provide the name or ip address of the host.\r\n"));
	Output(TEXT("                To host a session, run the game with no arguments.\r\n"));
}



GUID guidSession = GUID_NULL;

BOOL FAR PASCAL EnumSessionsCallback(  LPCDPSESSIONDESC2 lpThisSD,  
									  LPDWORD lpdwTimeOut,  DWORD dwFlags,  LPVOID lpContext  )
{
	BOOL fRet = TRUE;
	if(lpThisSD)
	{
		guidSession = lpThisSD->guidInstance;
		fRet = FALSE; // Stop the enumeration.
	}
	return fRet;
}


//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) 
	{
		case WM_KEYDOWN:
			switch (wParam)
			{
				case VK_ESCAPE:
				case VK_F12:
					DestroyWindow(hWnd);
					return 0;
			} // switch (wParam)
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}



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

    Returns 0.

-------------------------------------------------------------------*/
int WINAPI
WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
#ifdef UNDER_CE
    LPWSTR lpCmdLine,
#else
    LPSTR lpCmdLineA,
#endif
    int nShowCmd
    )
{
#ifndef UNDER_CE
	LPWSTR lpCmdLine;
	lpCmdLine = GetCommandLineW();

	// Skip the program name
	while(*lpCmdLine && *lpCmdLine != ' ')
		lpCmdLine++;

	// Skip blanks
	while(*lpCmdLine && *lpCmdLine == ' ')
		lpCmdLine++;
#endif

    if(lpCmdLine && (*lpCmdLine == '/' || *lpCmdLine == '-' || *lpCmdLine == '\0'))
    {
        Usage();
    }
    else
    {
		HRESULT hr = S_OK;
		LPDIRECTPLAY pDirectPlay = NULL;
		LPDIRECTPLAY4 pDirectPlay4 = NULL;

		LPDIRECTPLAYLOBBY pDirectPlayLobby = NULL;
		LPDIRECTPLAYLOBBY3 pDirectPlayLobby3 = NULL;

		DWORD *pdwAddress = NULL;
		DWORD dwSize;

		WNDCLASS wc;
		HWND hWnd;


		if(FAILED(hr = DirectPlayLobbyCreate(NULL, &pDirectPlayLobby, NULL, NULL, NULL)))
		{
			Output(TEXT("Failed to create a DirectPlayLobby object"));
			goto exit;
		}
		if(FAILED(pDirectPlayLobby->QueryInterface(IID_IDirectPlayLobby3, (void **)&pDirectPlayLobby3)))
		{
			Output(TEXT("Failed to create a DirectPlayLobby3 object"));
			goto exit;
		}

		GUID guidSP = GUID_NULL;
		hr = DirectPlayCreate(&guidSP, &pDirectPlay, NULL);

		if(FAILED(hr))
		{
			Output(TEXT("Failed to create a DirectPlay object"));
			goto exit;
		}
		if(FAILED(pDirectPlay->QueryInterface(IID_IDirectPlay4, (void **)&pDirectPlay4)))
		{
			Output(TEXT("Failed to create a DirectPlay4 object"));
			goto exit;
		}

		hr = pDirectPlayLobby->CreateAddress(GUID_WSOCK, DPAID_INetW, lpCmdLine, 
							(wcslen(lpCmdLine)+1) * sizeof(WCHAR), pdwAddress, &dwSize);
		if(hr == DPERR_BUFFERTOOSMALL)
		{
			// We are going to create and host a new session.
			DPSESSIONDESC2 sessionDesc;
			memset(&sessionDesc, 0, sizeof(DPSESSIONDESC2));
			sessionDesc.dwSize = sizeof(DPSESSIONDESC2);
			sessionDesc.guidApplication = GUID_APPLICATION;

			pdwAddress = (DWORD *) malloc(dwSize);
			hr = pDirectPlayLobby->CreateAddress(GUID_WSOCK, DPAID_INetW, lpCmdLine, 
								(wcslen(lpCmdLine)+1) * sizeof(WCHAR), pdwAddress, &dwSize);

			if(FAILED(hr))
				goto exit;

			hr = pDirectPlay4->InitializeConnection(pdwAddress, 0);
			
			free(pdwAddress);

			if(FAILED(hr))
				goto exit;

			hr = pDirectPlay4->EnumSessions(&sessionDesc, 0, EnumSessionsCallback, NULL, DPENUMSESSIONS_AVAILABLE);
			if(FAILED(hr) || guidSession == GUID_NULL)
				goto exit;

			sessionDesc.guidInstance = guidSession;
			hr = pDirectPlay4->Open(&sessionDesc, DPOPEN_JOIN);

			if(FAILED(hr))
				goto exit;
		}

		// Windowing stuff

		wc.style			= 0;
		wc.lpfnWndProc		= (WNDPROC)WndProc;
		wc.cbClsExtra		= 0;
		wc.cbWndExtra		= 0;
		wc.hInstance		= hInstance;
		wc.hIcon			= NULL;
		wc.hCursor			= NULL;
		wc.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
		wc.lpszMenuName		= NULL;
		wc.lpszClassName	= TEXT("Client");

		RegisterClass(&wc);


		DWORD dwStyle;
#ifndef UNDER_CE
		dwStyle = WS_CAPTION | WS_SYSMENU;
#else
		dwStyle = WS_VISIBLE;
#endif

		hWnd = CreateWindowEx(0, TEXT("Client"), TEXT("Client"), dwStyle,
		  0, 0, 640, 480, NULL, NULL, hInstance, NULL);

		if(!hWnd)
			goto exit;

#ifndef UNDER_CE
		ShowWindow(hWnd, TRUE);
		UpdateWindow(hWnd);
#endif

		MainLoop(pDirectPlay4);

		// Now close the session.
		pDirectPlay4->Close();

exit:
		if(FAILED(hr))
			Output(TEXT("Error code is %x"), hr);

		if(pDirectPlay)
		{
			pDirectPlay->Release();
			pDirectPlay = NULL;
		}
		if(pDirectPlay4)
		{
			pDirectPlay4->Release();
			pDirectPlay4 = NULL;
		}

		if(pDirectPlayLobby)
		{
			pDirectPlayLobby->Release();
			pDirectPlayLobby = NULL;
		}
		if(pDirectPlayLobby3)
		{
			pDirectPlayLobby3->Release();
			pDirectPlayLobby3 = NULL;
		}

	}

    return 0;
}


void
Output(
    const TCHAR *pwszFormat,
    ...
    )
{
    TCHAR wszBuf[1024];
    va_list args;

    va_start(args, pwszFormat);
    wvsprintf(wszBuf, pwszFormat, args);
    va_end(args);

    OutputDebugString(wszBuf);
}

void MainLoop(LPDIRECTPLAY4 pDP)
{

	DPID playerID;
	HRESULT hr = DP_OK;

	hr = pDP->CreatePlayer(&playerID,
						NULL, // Player name
						NULL, // hEvent for receiving messages for this player
						NULL, // Initial data
						0,	  // Size of initial Data
						0);	  // Player type: default.

	if(FAILED(hr))
		return;

	int sleep=0;
	int t=0;
	UINT tReceived[2];
	DWORD dwBufferSize;
	DPID idFrom, idTo;

	MSG msg;

	while(true)
	{

		// Main message loop:
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
				return;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}


		if(sleep >= 1000)	// Send a message every second
		{
			hr = pDP->Send(playerID,				// ID from
						DPID_SERVERPLAYER,	// ID to
						0,					// Default flags
						&t,					// Data
						sizeof(t));			// Size of Data
			t++;
			sleep=0;
		}


		do
		{
			dwBufferSize = sizeof(tReceived);
			hr = pDP->Receive(&idFrom, &idTo, DPRECEIVE_ALL, tReceived, &dwBufferSize);

			if(hr == DPERR_BUFFERTOOSMALL)
			{
				BYTE *pBuffer = (BYTE *) malloc(dwBufferSize);
				hr = pDP->Receive(&idFrom, &idTo, DPRECEIVE_ALL, pBuffer, &dwBufferSize);
				free(pBuffer);
			}

			if(hr == DP_OK)
			{
				if(idFrom != DPID_SYSMSG)
					Output(TEXT("Message received: %d, from player %d.\r\n"), tReceived[1], tReceived[0]);
				else
					Output(TEXT("Received system message.\r\n"));
			}
		} while(hr == S_OK);


		// Loop every 1/10th of a second
		Sleep(100);
		sleep += 100;
	}

	return;
}
