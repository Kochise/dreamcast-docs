/*==========================================================================
 *
 *  Copyright (C) 1997 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       dpslots.cpp
 *  Content:	common dpslots code
 *
 ***************************************************************************/

#include <windows.h>
#include <windowsx.h>
#include <stdio.h>

#include "dpslots.h"
#include "resource.h"

// globals
HANDLE			ghReceiveThread = NULL;			// handle of receive thread
DWORD			gidReceiveThread = 0;			// id of receive thread
HANDLE			ghKillReceiveEvent = NULL;		// event used to kill receive thread
HINSTANCE		ghInstance = NULL;				// application instance
CHAR			gszDatabaseName[MAXSTRLEN];		// database name

// prototypes
HRESULT			SetupConnection(HINSTANCE hInstance, LPDPLAYINFO lpDPInfo);
HRESULT			ShutdownConnection(LPDPLAYINFO lpDPInfo);
DWORD WINAPI	ReceiveThread(LPVOID lpThreadParameter);
HRESULT			ReceiveMessage(LPDPLAYINFO lpDPInfo);
void			HandleSystemMessage(LPDPLAYINFO lpDPInfo, LPDPMSG_GENERIC lpMsg, DWORD dwMsgSize,
									DPID idFrom, DPID idTo);
void			HandleApplicationMessage(LPDPLAYINFO lpDPInfo, LPDPMSG_GENERIC lpMsg, DWORD dwMsgSize,
										 DPID idFrom, DPID idTo);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine, int nCmdShow )
{
	DPLAYINFO	DPInfo;
	int			iResult = 0;
	HRESULT		hr;

	ghInstance = hInstance;
	srand(GetTickCount());
	lstrcpy(gszDatabaseName, DEFAULTDATABASE);

	// Initialize COM library
	hr = CoInitialize(NULL);
	if (FAILED(hr))
		goto FAILURE;

	// setup the connection
	hr = SetupConnection(hInstance, &DPInfo);
	if FAILED(hr)
		goto FAILURE;

	// show the server window
	if (DPInfo.bIsHost)
	{
		iResult = DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_SERVERDIALOG), NULL, (DLGPROC) ServerWndProc, (LPARAM) &DPInfo);
	}

	// show the client window
	else
	{
		iResult = DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_CLIENTDIALOG), NULL, (DLGPROC) ClientWndProc, (LPARAM) &DPInfo);
	}

FAILURE:
	// shut down the connection
	hr = ShutdownConnection(&DPInfo);

	// Uninitialize the COM library
	CoUninitialize();

	return (iResult);
}

HRESULT SetupConnection(HINSTANCE hInstance, LPDPLAYINFO lpDPInfo)
{
	HRESULT		hr;

	ZeroMemory(lpDPInfo, sizeof(DPLAYINFO));

	// create event used by DirectPlay to signal a message has arrived
	lpDPInfo->hPlayerEvent = CreateEvent(NULL,		// no security
										 FALSE,		// auto reset
										 FALSE,		// initial event reset
										 NULL);		// no name
	if (lpDPInfo->hPlayerEvent == NULL)
	{
		hr = DPERR_NOMEMORY;
		goto FAILURE;
	}

	// create event used to signal that the receive thread should exit
	ghKillReceiveEvent = CreateEvent(NULL,		// no security
									 FALSE,		// auto reset
									 FALSE,		// initial event reset
									 NULL);		// no name
	if (ghKillReceiveEvent == NULL)
	{
		hr = DPERR_NOMEMORY;
		goto FAILURE;
	}

	// create thread to receive player messages
	ghReceiveThread = CreateThread(NULL,			// default security
								   0,				// default stack size
								   ReceiveThread,	// pointer to thread routine
								   lpDPInfo,		// argument for thread
								   0,				// start it right away
								   &gidReceiveThread);
	if (ghReceiveThread == NULL)
	{
		hr = DPERR_NOMEMORY;
		goto FAILURE;
	}

	// try to connect using the lobby
	hr = ConnectUsingLobby(lpDPInfo);
	if FAILED(hr)
	{
		// if the error returned is DPERR_NOTLOBBIED, that means we
		// were not launched by a lobby and we should ask the user for
		// connection settings. If any other error is returned it means
		// we were launched by a lobby but there was an error making the
		// connection.

		if (hr != DPERR_NOTLOBBIED)
			ErrorBox("Could not connect using lobby because of error 0x%08X", hr);

		// if there is no lobby connection, ask the user for settings
		hr = ConnectUsingDialog(hInstance, lpDPInfo);
		if FAILED(hr)
			goto FAILURE;
	}

	return (DP_OK);	

FAILURE:
	ShutdownConnection(lpDPInfo);

	return (hr);
}

HRESULT ShutdownConnection(LPDPLAYINFO lpDPInfo)
{
	if (ghReceiveThread)
	{
		// wake up receive thread and wait for it to quit
		SetEvent(ghKillReceiveEvent);
		WaitForSingleObject(ghReceiveThread, INFINITE);

		CloseHandle(ghReceiveThread);
		ghReceiveThread = NULL;
	}

	if (ghKillReceiveEvent)
	{
		CloseHandle(ghKillReceiveEvent);
		ghKillReceiveEvent = NULL;
	}

	if (lpDPInfo->lpDirectPlay3A)
	{
		if (lpDPInfo->dpidPlayer)
		{
			lpDPInfo->lpDirectPlay3A->DestroyPlayer(lpDPInfo->dpidPlayer);
			lpDPInfo->dpidPlayer = 0;
		}
		lpDPInfo->lpDirectPlay3A->Close();
		lpDPInfo->lpDirectPlay3A->Release();
		lpDPInfo->lpDirectPlay3A = NULL;
	}

	if (lpDPInfo->hPlayerEvent)
	{
		CloseHandle(lpDPInfo->hPlayerEvent);
		lpDPInfo->hPlayerEvent = NULL;
	}

	return (DP_OK);
}

DWORD WINAPI ReceiveThread(LPVOID lpThreadParameter)
{
    LPDPLAYINFO	lpDPInfo = (LPDPLAYINFO) lpThreadParameter;
	HANDLE		eventHandles[2];

	eventHandles[0] = lpDPInfo->hPlayerEvent;
	eventHandles[1] = ghKillReceiveEvent;

	// loop waiting for player events. If the kill event is signaled
	// the thread will exit
	while (WaitForMultipleObjects(2, eventHandles, FALSE, INFINITE) == WAIT_OBJECT_0)
	{
		// receive any messages in the queue
		ReceiveMessage(lpDPInfo);
	}

	ExitThread(0);

	return (0);
}

HRESULT ReceiveMessage(LPDPLAYINFO lpDPInfo)
{
	DPID				idFrom, idTo;
	LPVOID				lpvMsgBuffer;
	DWORD				dwMsgBufferSize;
	HRESULT				hr;

	lpvMsgBuffer = NULL;
	dwMsgBufferSize = 0;

	// loop to read all messages in queue
	do
	{
		// loop until a single message is successfully read
		do
		{
			// read messages from any player, including system player
			idFrom = 0;
			idTo = 0;

			hr = lpDPInfo->lpDirectPlay3A->Receive(&idFrom, &idTo, DPRECEIVE_ALL,
												   lpvMsgBuffer, &dwMsgBufferSize);

			// not enough room, so resize buffer
			if (hr == DPERR_BUFFERTOOSMALL)
			{
				if (lpvMsgBuffer)
					GlobalFreePtr(lpvMsgBuffer);
				lpvMsgBuffer = GlobalAllocPtr(GHND, dwMsgBufferSize);
				if (lpvMsgBuffer == NULL)
					hr = DPERR_OUTOFMEMORY;
			}
		} while (hr == DPERR_BUFFERTOOSMALL);

		if ((SUCCEEDED(hr)) &&							// successfully read a message
			(dwMsgBufferSize >= sizeof(DPMSG_GENERIC)))	// and it is big enough
		{
			// check for system message
			if (idFrom == DPID_SYSMSG)
			{
				HandleSystemMessage(lpDPInfo, (LPDPMSG_GENERIC) lpvMsgBuffer,
									dwMsgBufferSize, idFrom, idTo);
			}
			else
			{
				HandleApplicationMessage(lpDPInfo, (LPDPMSG_GENERIC) lpvMsgBuffer,
										 dwMsgBufferSize, idFrom, idTo);
			}
		}
	} while (SUCCEEDED(hr));

	// free any memory we created
	if (lpvMsgBuffer)
		GlobalFreePtr(lpvMsgBuffer);

	return (DP_OK);
}

void HandleSystemMessage(LPDPLAYINFO lpDPInfo, LPDPMSG_GENERIC lpMsg, DWORD dwMsgSize,
						 DPID idFrom, DPID idTo)
{
	if (lpDPInfo->bIsHost)
	{
		ServerSystemMessage(lpDPInfo, lpMsg, dwMsgSize, idFrom, idTo);
	}
	else
	{
		ClientSystemMessage(lpDPInfo, lpMsg, dwMsgSize, idFrom, idTo);
	}
}

void HandleApplicationMessage(LPDPLAYINFO lpDPInfo, LPDPMSG_GENERIC lpMsg, DWORD dwMsgSize,
							  DPID idFrom, DPID idTo)
{
	// When using a secure session we should not get any messages here
	// because encrypted messages come through as system messages. Therefore,
	// it is a security hole to process messages here.

	if (lpDPInfo->bIsSecure)
		return;

	if (lpDPInfo->bIsHost)
	{
		ServerApplicationMessage(lpDPInfo, lpMsg, dwMsgSize, idFrom, idTo);
	}
	else
	{
		ClientApplicationMessage(lpDPInfo, lpMsg, dwMsgSize, idFrom, idTo);
	}
}

void ErrorBox(LPSTR lpszErrorStr, HRESULT hr)
{
	CHAR	szStr[200];

	wsprintf(szStr, lpszErrorStr, hr);

	MessageBox(NULL, szStr, "Error", MB_OK);
}

void CheckDlgItem(HWND hDlg, int nIDDlgItem, BOOL bCheck)
{
	SendDlgItemMessage(hDlg, nIDDlgItem, BM_SETCHECK,
					   (WPARAM) ((bCheck) ?  BST_CHECKED : BST_UNCHECKED), (LPARAM) 0);
}

BOOL DlgItemIsChecked(HWND hDlg, int nIDDlgItem)
{
	return ((SendDlgItemMessage(hDlg, nIDDlgItem, BM_GETCHECK, (WPARAM) 0, (LPARAM) 0) == BST_CHECKED) ? TRUE : FALSE);
}

void EnableDlgButton(HWND hDlg, int nIDDlgItem, BOOL bEnable)
{
	EnableWindow(GetDlgItem(hDlg, nIDDlgItem), bEnable);
}
