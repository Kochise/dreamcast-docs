/*==========================================================================
 *
 *  Copyright (C) 1996-1997 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       bellhop.cpp
 *  Content:	Simple lobby program using DirectPlay.
 *
 ***************************************************************************/

#define INITGUID
#include "bellhop.h"
#include "resource.h"

enum {
	WM_USER_ADDSTRING	= WM_USER+257,	// window message to add string to chat string list
	WM_USER_UPDATE						// window message to update lobby display
};

// globals
HANDLE			ghReceiveThread = NULL;			// handle of receive thread
DWORD			gidReceiveThread = 0;			// id of receive thread
HANDLE			ghKillReceiveEvent = NULL;		// event used to kill receive thread
HWND			ghMainWnd = NULL;				// main window
HINSTANCE		ghInstance;						// application instance

//EXTERNs
BOOL FAR PASCAL DirectPlayEnumConnectionsCallback(	LPCGUID lpguidSP, LPVOID lpConnection, 
															DWORD dwSize, LPCDPNAME lpName, 
															DWORD dwFlags, LPVOID lpContext);
HRESULT	GetConnection(HWND hWnd,  int idCombo, LPVOID *lplpConnection);
HRESULT	GetConnectionSPGuid(HWND hWnd, int idCombo, GUID *lpGuidSP);



///////////////////////////////////////////////////////////////////////////////////////
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   LPSTR lpCmdLine, int nCmdShow )
{
	DPLAYINFO	DPInfo;
	int			iResult = 0;
	HRESULT		hr;

	ghInstance = hInstance;

	// Initialize COM library
	hr = CoInitialize(NULL);
	if FAILED(hr)
		goto FAILURE;

	// setup the connection
	hr = SetupConnection(hInstance, &DPInfo);
	if FAILED(hr)
		goto FAILURE;

	// show the chat window
	iResult = DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_LOBBYDIALOG), NULL, (DLGPROC) LobbyWndProc, (LPARAM) &DPInfo);

FAILURE:
	// shut down the connection
	hr = ShutdownConnection(&DPInfo);

	// Uninitialize the COM library
	CoUninitialize();

	return (iResult);
}

///////////////////////////////////////////////////////////////////////////////////////
BOOL CALLBACK LobbyWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static LPDPLAYINFO	lpDPInfo;
	DWORD				dwTextLen;

    switch(uMsg)
    {

    case WM_INITDIALOG:
		{
			HDC hDC;
			int xPixelsPerInch,
				yPixelsPerInch;
			RECT rect;

			// Save the connection info pointer
			lpDPInfo = (LPDPLAYINFO) lParam;

			// Get the dialog spacing info
			hDC = GetDC(hWnd);
			xPixelsPerInch = GetDeviceCaps(hDC, LOGPIXELSX);
			yPixelsPerInch = GetDeviceCaps(hDC, LOGPIXELSY);
			ReleaseDC(hWnd, hDC);
			lpDPInfo->xSpacing = xPixelsPerInch / 8;
			lpDPInfo->ySpacing = yPixelsPerInch / 8;
			lpDPInfo->xHalfSplitWidth = xPixelsPerInch / 12;

			GetClientRect(hWnd, &rect);
            lpDPInfo->xPaneSplit = ((rect.right - rect.left) - (2 * lpDPInfo->xSpacing )) / 3 
									- lpDPInfo->xHalfSplitWidth;	

			// Create the tree control
			lpDPInfo->lpGroupTree = new CGroupTree;
			lpDPInfo->lpGroupTree->Init(	GetDlgItem(hWnd, IDT_MESSAGEVIEW), 
											lpDPInfo->lpDirectPlay3A,
											lpDPInfo->dpidPlayer);
			lpDPInfo->lpGroupTree->Refresh();
			lpDPInfo->lpGroupTree->CreatePlayer( lpDPInfo->dpidPlayer, NULL, lpDPInfo->dwPlayerFlags );

			// store global window
			ghMainWnd = hWnd;

			// initiallize lobby
			InitializeLobby(hWnd, lpDPInfo);

			OnSize( hWnd, lpDPInfo );
		}
        break;

    case WM_DESTROY:
		ghMainWnd = NULL;
        break;

    case WM_SIZE:
        OnSize(hWnd, lpDPInfo);
        break;

    case WM_LBUTTONDOWN:
        lpDPInfo->bSplitMove = TRUE;
        SetCapture(hWnd);
        break;

    case WM_LBUTTONUP:
		if (lpDPInfo->bSplitMove)
		{
			lpDPInfo->bSplitMove = FALSE;
			ReleaseCapture();
		}
		else
		{
			lpDPInfo->lpGroupTree->OnLButtonUp();
		}
        break;

    case WM_MOUSEMOVE:
        if(lpDPInfo->bSplitMove)
        {
			// track mouse movement while adjusting the divider
            RECT    rect;
            // change the value from unsigned to signed
            int     x = (int)(short)LOWORD(lParam);

            GetClientRect(hWnd, &rect);
            if (rect.left > x)
            {
                x = rect.left;
            }
            else if (rect.right < x)
            {
                x = rect.right;
            }
            lpDPInfo->xPaneSplit = (x - lpDPInfo->xHalfSplitWidth - (lpDPInfo->xSpacing * 2));
            OnSize(hWnd, lpDPInfo);
        }
		else
		{
			lpDPInfo->lpGroupTree->OnMouseMove(LOWORD(lParam), HIWORD(lParam) );
		}
        break;


	// this is a user-defined message used to add strings to the log window
	case WM_USER_ADDSTRING:
		// get length of text in log window
		dwTextLen = SendDlgItemMessage(hWnd, IDC_LOGEDIT, WM_GETTEXTLENGTH,
									   (WPARAM) 0, (LPARAM) 0);

		// put selection at end
		dwTextLen = SendDlgItemMessage(hWnd, IDC_LOGEDIT, EM_SETSEL,
									   (WPARAM) dwTextLen, (LPARAM) dwTextLen);

		// add string in lParam to log window
		SendDlgItemMessage(hWnd, IDC_LOGEDIT, EM_REPLACESEL,
							(WPARAM) FALSE, (LPARAM) lParam);
		GlobalFreePtr((LPVOID) lParam);
		break;


    case WM_COMMAND:
        switch(LOWORD(wParam))
        {
        case ID_ROOT_CREATEGROUP:
			DoCreateRoom(hWnd, lpDPInfo);
			break;			

        case ID_GROUP_CONNECTIONSETTINGS:
			DoGroupConnectionSettings(hWnd, lpDPInfo);
			break;			

        case ID_DESTROYGROUP:
			DoDeleteRoom(hWnd, lpDPInfo);
			break;			

        case ID_PLAYERINGROUP_DELETEPLAYERFROMGROUP:
			DoDeletePlayerFromGroup(hWnd, lpDPInfo);
			break;			

        case ID_CREATEGROUPINGROUP:
			DoCreateTable(hWnd, lpDPInfo);
			break;			

        case ID_SHORTCUT_DELETEGROUPFROMGROUP:
			DoDeleteTable(hWnd, lpDPInfo);
			break;			

        case ID_GROUP_STARTSESSION:
			DoLaunch(hWnd, lpDPInfo);
			break;			

        case ID_PLAYER_SETPLAYERNAME:
		case ID_PLAYERINGROUP_SETPLAYERNAME:
        case ID_GROUP_SETGROUPNAME:
			lpDPInfo->lpGroupTree->EditLabel();
			break;			

        case IDC_SENDBUTTON:
			SendChatMessage(hWnd, lpDPInfo);
			break;			

        case IDCANCEL:
			EndDialog(hWnd, FALSE);
            break;

        case ID_ROOT_ENUMRECURSIVE:
			lpDPInfo->lpGroupTree->Refresh( );
	 		lpDPInfo->lpGroupTree->CreatePlayer( lpDPInfo->dpidPlayer, NULL, lpDPInfo->dwPlayerFlags );
           break;

		case ID_ROOT_ENUMGROUPS:
			lpDPInfo->lpGroupTree->Refresh( FALSE );
	 		lpDPInfo->lpGroupTree->CreatePlayer( lpDPInfo->dpidPlayer, NULL, lpDPInfo->dwPlayerFlags );
           break;

		}
		break;

	case WM_NOTIFY :
		 return lpDPInfo->lpGroupTree->OnWM_NOTIFY( wParam, lParam );
		break;

	case WM_MENUSELECT:
		return FALSE;
		break;
	}

    // Allow for default processing
    return FALSE;
}

///////////////////////////////////////////////////////////////////////////////////////
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

	// if there is no lobby connection, ask the user for settings
	hr = ConnectUsingDialog(hInstance, lpDPInfo);
	if FAILED(hr)
		goto FAILURE;

	return (DP_OK);	

FAILURE:
	ShutdownConnection(lpDPInfo);

	return (hr);
}

///////////////////////////////////////////////////////////////////////////////////////
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
			IDirectPlay3_DestroyPlayer(lpDPInfo->lpDirectPlay3A, lpDPInfo->dpidPlayer);
			lpDPInfo->dpidPlayer = 0;
		}
		IDirectPlay3_Close(lpDPInfo->lpDirectPlay3A);
		IDirectPlay3_Release(lpDPInfo->lpDirectPlay3A);
		lpDPInfo->lpDirectPlay3A = NULL;

		IDirectPlayLobby_Release(lpDPInfo->lpDirectPlayLobby2A);
		lpDPInfo->lpDirectPlayLobby2A = NULL;

	}

	if (lpDPInfo->hPlayerEvent)
	{
		CloseHandle(lpDPInfo->hPlayerEvent);
		lpDPInfo->hPlayerEvent = NULL;
	}

	if (lpDPInfo->lpGroupTree)
	{
		delete lpDPInfo->lpGroupTree;
		lpDPInfo->lpGroupTree = NULL;
	}
	return (DP_OK);
}

///////////////////////////////////////////////////////////////////////////////////////
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

///////////////////////////////////////////////////////////////////////////////////////
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

			hr = IDirectPlay3_Receive(lpDPInfo->lpDirectPlay3A, &idFrom, &idTo, DPRECEIVE_ALL,
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
			// update the tree view UI.
			lpDPInfo->lpGroupTree->Update( lpvMsgBuffer );

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

///////////////////////////////////////////////////////////////////////////////////////
void HandleApplicationMessage(LPDPLAYINFO lpDPInfo, LPDPMSG_GENERIC lpMsg, DWORD dwMsgSize,
							  DPID idFrom, DPID idTo)
{
	// Any messages received from the lobby server would be handled here.
	// In this case, we don't have any
}

///////////////////////////////////////////////////////////////////////////////////////
void HandleSystemMessage(LPDPLAYINFO lpDPInfo, LPDPMSG_GENERIC lpMsg, DWORD dwMsgSize,
						 DPID idFrom, DPID idTo)
{
	LPSTR		lpszStr = NULL;

    // The body of each case is there so you can set a breakpoint and examine
    // the contents of the message received.
	switch (lpMsg->dwType)
	{
	case DPSYS_STARTSESSION:
		{
			LPDPMSG_STARTSESSION	lp = (LPDPMSG_STARTSESSION) lpMsg;

			HandleStartSession(lp->lpConn, lpDPInfo);
		}
		break;

	case DPSYS_CREATEPLAYERORGROUP:
        {
            LPDPMSG_CREATEPLAYERORGROUP		lp = (LPDPMSG_CREATEPLAYERORGROUP) lpMsg;
			LPSTR							lpszName, lpszDisplayFormat;
            
			if (lp->dwPlayerType == DPPLAYERTYPE_PLAYER)
				lpszDisplayFormat = "Player \"%s\" created\r\n";
			else if (lp->dwPlayerType == DPPLAYERTYPE_GROUP)
				lpszDisplayFormat = "Group \"%s\" created\r\n";
			else
				lpszDisplayFormat = "Unknown object \"%s\" created\r\n";

			// get pointer to player name
			if (lp->dpnName.lpszShortNameA)
				lpszName = lp->dpnName.lpszShortNameA;
			else
				lpszName = "unknown";

			// allocate space for string
			lpszStr = (LPSTR) GlobalAllocPtr(GHND, lstrlen(lpszDisplayFormat) +
												   lstrlen(lpszName) + 1);
			if (lpszStr == NULL)
				break;

			// build string
			wsprintf(lpszStr, lpszDisplayFormat, lpszName);
        }
		break;

	case DPSYS_DESTROYPLAYERORGROUP:
        {
            LPDPMSG_DESTROYPLAYERORGROUP	lp = (LPDPMSG_DESTROYPLAYERORGROUP)lpMsg;
			LPSTR							lpszName, lpszDisplayFormat;
            
			if (lp->dwPlayerType == DPPLAYERTYPE_PLAYER)
				lpszDisplayFormat = "Player \"%s\" destroyed\r\n";
			else if (lp->dwPlayerType == DPPLAYERTYPE_GROUP)
				lpszDisplayFormat = "Group \"%s\" destroyed\r\n";
			else
				lpszDisplayFormat = "Unknown object \"%s\" destroyed\r\n";

			// get pointer to player name
			if (lp->dpnName.lpszShortNameA)
				lpszName = lp->dpnName.lpszShortNameA;
			else
				lpszName = "unknown";

			// allocate space for string
			lpszStr = (LPSTR) GlobalAllocPtr(GHND, lstrlen(lpszDisplayFormat) +
												   lstrlen(lpszName) + 1);
			if (lpszStr == NULL)
				break;

			// build string
			wsprintf(lpszStr, lpszDisplayFormat, lpszName);
        }
		break;

	case DPSYS_ADDPLAYERTOGROUP:
	case DPSYS_DELETEPLAYERFROMGROUP:
        {
            LPDPMSG_ADDPLAYERTOGROUP		lpAddMsg = (LPDPMSG_ADDPLAYERTOGROUP)lpMsg;
            LPDPMSG_DELETEPLAYERFROMGROUP	lpDeleteMsg = (LPDPMSG_DELETEPLAYERFROMGROUP)lpMsg;
			DPID							dpidPlayer, dpidGroup;
			LPSTR							lpszPlayerName, lpszGroupName;
			LPDPNAME						lpPlayerName, lpGroupName;
			LPSTR							lpszDisplayFormat;
            HRESULT							hr;

			if (lpMsg->dwType == DPSYS_ADDPLAYERTOGROUP)
			{
				dpidPlayer = lpAddMsg->dpIdPlayer;
				dpidGroup = lpAddMsg->dpIdGroup;
				lpszDisplayFormat = "Player \"%s\" added to group \"%s\"\r\n";
			}
			else
			{
				dpidPlayer = lpDeleteMsg->dpIdPlayer;
				dpidGroup = lpDeleteMsg->dpIdGroup;
				lpszDisplayFormat = "Player \"%s\" removed from group \"%s\"\r\n";
			}

			// get pointer to player name
			hr = GetPlayerName(lpDPInfo->lpDirectPlay3A, dpidPlayer, &lpPlayerName);
			if FAILED(hr)
			{
				// A failure may mean that the player has been deleted
				// since we began processing this message
				lpPlayerName = NULL;
			}

			if ((lpPlayerName) && (lpPlayerName->lpszShortNameA))
				lpszPlayerName = lpPlayerName->lpszShortNameA;
			else
				lpszPlayerName = "unknown";

			// get pointer to group name
			hr = GetGroupName(lpDPInfo->lpDirectPlay3A, dpidGroup, &lpGroupName);
			if FAILED(hr)
			{
				// A failure may mean that the group has been deleted
				// since we began processing this message
				lpGroupName = NULL;
			}

			if ((lpGroupName) && (lpGroupName->lpszShortNameA))
				lpszGroupName = lpGroupName->lpszShortNameA;
			else
				lpszGroupName = "unknown";


			// allocate space for string
			lpszStr = (LPSTR) GlobalAllocPtr(GHND, lstrlen(lpszDisplayFormat) +
												   lstrlen(lpszPlayerName) +
												   lstrlen(lpszGroupName) + 1);
			// build string
			if (lpszStr)
				wsprintf(lpszStr, lpszDisplayFormat, lpszPlayerName, lpszGroupName);

			// free data we allocated
			if (lpPlayerName)
				GlobalFreePtr(lpPlayerName);
			if (lpGroupName)
				GlobalFreePtr(lpGroupName);
        }
		break;

	case DPSYS_ADDGROUPTOGROUP:
	case DPSYS_DELETEGROUPFROMGROUP:
        {
            LPDPMSG_ADDGROUPTOGROUP		lpAddMsg = (LPDPMSG_ADDGROUPTOGROUP)lpMsg;
            LPDPMSG_DELETEGROUPFROMGROUP	lpDeleteMsg = (LPDPMSG_DELETEGROUPFROMGROUP)lpMsg;
			DPID							dpidParentGroup, dpidGroup;
			LPSTR							lpszParentGroupName, lpszGroupName;
			LPDPNAME						lpParentGroupName, lpGroupName;
			LPSTR							lpszDisplayFormat;
            HRESULT							hr;

			if (lpMsg->dwType == DPSYS_ADDGROUPTOGROUP)
			{
				dpidGroup = lpAddMsg->dpIdGroup;
				dpidParentGroup = lpAddMsg->dpIdParentGroup;
				lpszDisplayFormat = "Group \"%s\" added to group \"%s\"\r\n";
			}
			else
			{
				dpidParentGroup = lpDeleteMsg->dpIdParentGroup;
				dpidGroup = lpDeleteMsg->dpIdGroup;
				lpszDisplayFormat = "Group \"%s\" removed from group \"%s\"\r\n";
			}

			// get pointer to player name
			hr = GetGroupName(lpDPInfo->lpDirectPlay3A, dpidParentGroup, &lpParentGroupName);
			if FAILED(hr)
				lpParentGroupName = NULL;

			if ((lpParentGroupName) && (lpParentGroupName->lpszShortNameA))
				lpszParentGroupName = lpParentGroupName->lpszShortNameA;
			else
				lpszParentGroupName = "unknown";

			// get pointer to group name
			hr = GetGroupName(lpDPInfo->lpDirectPlay3A, dpidGroup, &lpGroupName);
			if FAILED(hr)
				lpGroupName = NULL;

			if ((lpGroupName) && (lpGroupName->lpszShortNameA))
				lpszGroupName = lpGroupName->lpszShortNameA;
			else
				lpszGroupName = "unknown";

			// allocate space for string
			lpszStr = (LPSTR) GlobalAllocPtr(GHND, lstrlen(lpszDisplayFormat) +
												   lstrlen(lpszParentGroupName) +
												   lstrlen(lpszGroupName) + 1);
			// build string
			if (lpszStr)
				wsprintf(lpszStr, lpszDisplayFormat, lpszGroupName, lpszParentGroupName );

			// free data we allocated
			if (lpParentGroupName)
				GlobalFreePtr(lpParentGroupName);
			if (lpGroupName)
				GlobalFreePtr(lpGroupName);
        }
		break;

	case DPSYS_SESSIONLOST:
        {
            LPDPMSG_SESSIONLOST lp = (LPDPMSG_SESSIONLOST)lpMsg;
			LPSTR			szDisplayFormat = "Session lost.\r\n";

			// allocate space for string
			lpszStr = (LPSTR) GlobalAllocPtr(GHND, lstrlen(szDisplayFormat) + 1);
			if (lpszStr == NULL)
				break;

			// build string
			lstrcpy(lpszStr, szDisplayFormat);
        }
		break;

	case DPSYS_HOST:
        {
            LPDPMSG_HOST	lp = (LPDPMSG_HOST)lpMsg;
			LPSTR			szDisplayFormat = "You have become the host\r\n";

			// allocate space for string
			lpszStr = (LPSTR) GlobalAllocPtr(GHND, lstrlen(szDisplayFormat) + 1);
			if (lpszStr == NULL)
				break;

			// build string
			lstrcpy(lpszStr, szDisplayFormat);

			// we are now the host
			lpDPInfo->bIsHost = TRUE;
        }
		break;

	case DPSYS_SETPLAYERORGROUPDATA:
        {
            LPDPMSG_SETPLAYERORGROUPDATA lp = (LPDPMSG_SETPLAYERORGROUPDATA)lpMsg;
        }
		break;

	case DPSYS_SETPLAYERORGROUPNAME:
        {
            LPDPMSG_SETPLAYERORGROUPNAME lp = (LPDPMSG_SETPLAYERORGROUPNAME)lpMsg;
        }
		break;

	case DPSYS_CHAT:
        {
            LPDPMSG_CHAT	lp = (LPDPMSG_CHAT)lpMsg;
			DWORD			dwSize = lstrlen( lp->lpChat->lpszMessageA ) + 12;
							//Allow extra room for "{whisper} ", in case this message
							//was sent just to me.

			// allocate space for string
			lpszStr = (LPSTR) GlobalAllocPtr( GHND, dwSize );

			if (lpszStr == NULL)
				break;

			if (NULL == lp->idToGroup)
			{
				//This message was sent just to me, not to a whole group
				lstrcpy( lpszStr, "{whisper} " );
				lstrcat( lpszStr, lp->lpChat->lpszMessageA );
			}
			else
			{
				// build string
				lstrcpy(lpszStr, lp->lpChat->lpszMessageA);
			}
        }
		break;

	}

	// post string to chat window
	if (lpszStr)
	{
		// make sure window is still valid
		if (ghMainWnd)
			PostMessage(ghMainWnd, WM_USER_ADDSTRING, (WPARAM) 0, (LPARAM) lpszStr);
		else
			GlobalFreePtr(lpszStr);
	}

}

///////////////////////////////////////////////////////////////////////////////////////
HRESULT GetPlayerName(LPDIRECTPLAY3A lpDirectPlay3A, DPID dpidPlayer,
					  LPDPNAME *lplpName)
{
	LPDPNAME	lpName = NULL;
	DWORD		dwNameSize;
	HRESULT		hr;

	// get size of player name data
	hr = IDirectPlay3_GetPlayerName(lpDirectPlay3A, dpidPlayer, NULL, &dwNameSize);
	if (hr != DPERR_BUFFERTOOSMALL)
		goto FAILURE;

	// make room for it
	lpName = (LPDPNAME) GlobalAllocPtr(GHND, dwNameSize);
	if (lpName == NULL)
	{
		hr = DPERR_OUTOFMEMORY;
		goto FAILURE;
	}

	// get player name data
	hr = IDirectPlay3_GetPlayerName(lpDirectPlay3A, dpidPlayer, lpName, &dwNameSize);
	if FAILED(hr)
		goto FAILURE;

	// return pointer to name structure
	*lplpName = lpName;

	return (DP_OK);

FAILURE:
	if (lpName)
		GlobalFreePtr(lpName);

	return (hr);
}

///////////////////////////////////////////////////////////////////////////////////////
HRESULT GetGroupName(LPDIRECTPLAY3A lpDirectPlay3A, DPID dpidGroup,
					 LPDPNAME *lplpName)
{
	LPDPNAME	lpName = NULL;
	DWORD		dwNameSize;
	HRESULT		hr;

	// get size of player name data
	hr = IDirectPlay3_GetGroupName(lpDirectPlay3A, dpidGroup, NULL, &dwNameSize);
	if (hr != DPERR_BUFFERTOOSMALL)
		goto FAILURE;

	// make room for it
	lpName = (LPDPNAME) GlobalAllocPtr(GHND, dwNameSize);
	if (lpName == NULL)
	{
		hr = DPERR_OUTOFMEMORY;
		goto FAILURE;
	}

	// get player name data
	hr = IDirectPlay3_GetGroupName(lpDirectPlay3A, dpidGroup, lpName, &dwNameSize);
	if FAILED(hr)
		goto FAILURE;

	// return pointer to name structure
	*lplpName = lpName;

	return (DP_OK);

FAILURE:
	if (lpName)
		GlobalFreePtr(lpName);

	return (hr);
}

///////////////////////////////////////////////////////////////////////////////////////
void InitializeLobbyGroupWindow(HWND hWnd, LPLOBBYGROUPCONTEXT lpContext)
{
	HRESULT			hr = DPERR_GENERIC;
	ENUMCONNSTRUCT	enStruct;

	if (lpContext->dpidRoom == 0)
		SetWindowText(hWnd, "Create Room");
	else
		SetWindowText(hWnd, "Create Table");

	// initialize max players
	SetDlgItemInt(hWnd, IDC_MAXPLAYERSEDIT, 0, FALSE);

	// put all the DirectPlay applications in a combo box
	lpContext->lpDPInfo->lpDirectPlayLobby2A->EnumLocalApplications(EnumApp, hWnd, 0);
	SendDlgItemMessage(hWnd, IDC_APPCOMBO, CB_SETCURSEL, (WPARAM) 0, (LPARAM) 0);

	// put all the available connections in a combo box
	enStruct.hWnd = hWnd;
	enStruct.idCombo = IDC_GROUPCONNECTIONSPCOMBO;

	hr = IDirectPlay3_EnumConnections(	lpContext->lpDPInfo->lpDirectPlay3A, 
										&BELLHOP_GUID, 
										DirectPlayEnumConnectionsCallback,
										&enStruct, DPCONNECTION_DIRECTPLAY );

	SendDlgItemMessage(hWnd, IDC_GROUPCONNECTIONSPCOMBO, CB_SETCURSEL, (WPARAM) 0, (LPARAM) 0);
	return;

}

///////////////////////////////////////////////////////////////////////////////////////
HRESULT CreateLobbyGroup(HWND hWnd, LPLOBBYGROUPCONTEXT lpContext)
{
	CHAR				szShortName[MAXSTRLEN],
						szLongName[MAXSTRLEN],
						szPassword[MAXSTRLEN];
	DPNAME				dpName;
	DWORD				dwMaxPlayers;
	DPID				dpID;
	DPLCONNECTION		dplconn;
	DPSESSIONDESC2		dpsess;
	HRESULT				hr;
	DWORD				dwFlags = 0;

	// get strings from dialog
	GetDlgItemText(hWnd, IDC_SHORTNAMEEDIT, szShortName, MAXSTRLEN);
	GetDlgItemText(hWnd, IDC_LONGNAMEEDIT, szLongName, MAXSTRLEN);

	if (BST_CHECKED == SendDlgItemMessage( hWnd, IDC_STAGINGAREA, BM_GETCHECK, 0, 0 ))
	{
		GetDlgItemText(hWnd, IDC_PASSWORDEDIT, szPassword, MAXSTRLEN);
		dwMaxPlayers = GetDlgItemInt(hWnd, IDC_MAXPLAYERSEDIT, NULL, FALSE);
		dwFlags = DPGROUP_STAGINGAREA;
	}

	// build a dpname structure
	ZeroMemory(&dpName, sizeof(DPNAME));
	dpName.dwSize = sizeof(DPNAME);
	dpName.lpszShortNameA = szShortName;
	dpName.lpszLongNameA = szLongName;

	// create a root group
	if (lpContext->dpidRoom == 0)
	{
		hr = IDirectPlay3_CreateGroup(lpContext->lpDPInfo->lpDirectPlay3A,
					&dpID, &dpName, NULL, 0, dwFlags);
	}

	// create the table group
	else
	{
		hr = IDirectPlay3_CreateGroupInGroup(	lpContext->lpDPInfo->lpDirectPlay3A,
												lpContext->dpidRoom, 
												&dpID, &dpName, 
												NULL, 0, dwFlags);
	}

	if FAILED(hr)
		goto FAILURE;

	if ( DPGROUP_STAGINGAREA & dwFlags )
	{
		
		// Fill out the DPSESSIONDESC2 structure
		ZeroMemory( &dpsess, sizeof(DPSESSIONDESC2) );
		dpsess.dwSize = sizeof( DPSESSIONDESC2 );
		dpsess.dwFlags = DPSESSION_KEEPALIVE | DPSESSION_MIGRATEHOST;

		CoCreateGuid(&(dpsess.guidInstance));

		GetComboBoxGuid(hWnd, IDC_APPCOMBO, &dpsess.guidApplication);

		dpsess.dwMaxPlayers = dwMaxPlayers;
		dpsess.dwCurrentPlayers = 0;
		dpsess.lpszSessionNameA = dpName.lpszShortNameA;
		if (lstrlen(szPassword))
			dpsess.lpszPasswordA = szPassword;

		// Fill out the DPLCONNECTION structure
		ZeroMemory( &dplconn, sizeof(DPLCONNECTION) );
		dplconn.dwSize = sizeof( DPLCONNECTION );
		dplconn.lpSessionDesc = &dpsess;

		GetConnectionSPGuid(hWnd, IDC_GROUPCONNECTIONSPCOMBO, &dplconn.guidSP);

		// The rest of the DPLCONNECTION structure gets 
		// filled in by the lobby

		hr = IDirectPlay3_SetGroupConnectionSettings(lpContext->lpDPInfo->lpDirectPlay3A,
													 0, dpID, &dplconn );

		if FAILED(hr)
			goto FAILURE;
	}

FAILURE:
	return (hr);
}

///////////////////////////////////////////////////////////////////////////////////////
BOOL CALLBACK LobbyGroupWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LPLOBBYGROUPCONTEXT	lpContext = (LPLOBBYGROUPCONTEXT) GetWindowLong(hWnd, DWL_USER);

    switch(uMsg)
    {
      case WM_INITDIALOG:

			// context passed in lParam
			lpContext = (LPLOBBYGROUPCONTEXT) lParam;

            // save the globals with the window
			SetWindowLong(hWnd, DWL_USER, (LONG) lpContext);
            
			// Initialize dialog with appropriate information
			InitializeLobbyGroupWindow(hWnd, lpContext);
            break;

        case WM_DESTROY:
			{
				WPARAM	index;
				LRESULT	lpData;

				// destroy the GUID's stored with each app name
				index = 0;
				while (TRUE)
				{
					lpData = SendDlgItemMessage(hWnd, IDC_APPCOMBO, CB_GETITEMDATA, (WPARAM) index, 0);
					if ((lpData == CB_ERR) || (lpData == 0))
						break;

					GlobalFreePtr((LPVOID) lpData);
					index += 1;
				}

				// destroy the connection info in the combo box.
				index = 0;
				while (TRUE)
				{
					lpData = SendDlgItemMessage(hWnd, IDC_GROUPCONNECTIONSPCOMBO, CB_GETITEMDATA, (WPARAM) index, 0);
					if ((lpData == CB_ERR) || (lpData == 0))
						break;

					GlobalFreePtr((LPVOID) lpData);
					index += 1;
				}
			}
            break;

        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
				case IDOK:
					// save changes they made
					CreateLobbyGroup(hWnd, lpContext);
                    // Return success
                    EndDialog(hWnd, TRUE);

                    break;

				case IDCANCEL:
                    // Return failure
                    EndDialog(hWnd, FALSE);

                    break;

				case IDC_STAGINGAREA:
					{
						int i = SendDlgItemMessage( hWnd, IDC_STAGINGAREA, BM_GETCHECK, 0, 0 );
						EnableWindow( GetDlgItem( hWnd, IDC_PASSWORDEDIT ), (BST_CHECKED==i));
						EnableWindow( GetDlgItem( hWnd, IDC_APPCOMBO ), (BST_CHECKED==i));
						EnableWindow( GetDlgItem( hWnd, IDC_MAXPLAYERSEDIT ), (BST_CHECKED==i));
						EnableWindow( GetDlgItem( hWnd, IDC_GROUPCONNECTIONSPCOMBO ), (BST_CHECKED==i));
					}
					break;

            }

            break;
    }

    // Allow for default processing
    return FALSE;
}

///////////////////////////////////////////////////////////////////////////////////////
HRESULT DoGroupConnectionSettings(HWND hWnd, LPDPLAYINFO lpDPInfo)
{
	LOBBYGROUPCONTEXT	context;

	context.lpDPInfo = lpDPInfo;
	context.dpidRoom = lpDPInfo->lpGroupTree->GetDPIDOfCurrentSelection();

	if (DialogBoxParam(ghInstance, MAKEINTRESOURCE(IDD_CONNECTIONSETTINGSDIALOG), hWnd,
					  (DLGPROC) ConnectionSettingsDialogProc, (LPARAM) &context))
	{
		// something changed
		// We could update a status bar here.
	}

	return (DP_OK);
}

///////////////////////////////////////////////////////////////////////////////////////
HRESULT DoCreateRoom(HWND hWnd, LPDPLAYINFO lpDPInfo)
{
	LOBBYGROUPCONTEXT	context;

	context.lpDPInfo = lpDPInfo;
	context.dpidRoom = (DPID) 0;

	if (DialogBoxParam(ghInstance, MAKEINTRESOURCE(IDD_LOBBYGROUPDIALOG), hWnd,
					  (DLGPROC) LobbyGroupWndProc, (LPARAM) &context))
	{
		// something changed
		// We could update a status bar here.
	}

	return (DP_OK);
}

///////////////////////////////////////////////////////////////////////////////////////
HRESULT DoDeleteRoom(HWND hWnd, LPDPLAYINFO lpDPInfo)
{
	DPID				dpidRoom;
	HRESULT				hr = DP_OK;

	dpidRoom = lpDPInfo->lpGroupTree->GetDPIDOfCurrentSelection();

	// delete the group
	hr = IDirectPlay3_DestroyGroup(lpDPInfo->lpDirectPlay3A, dpidRoom);

	return (hr);
}

///////////////////////////////////////////////////////////////////////////////////////
HRESULT DoDeletePlayerFromGroup(HWND hWnd, LPDPLAYINFO lpDPInfo)
{
	DPID				dpidRoom,
						dpidPlayer;
	HRESULT				hr = DP_OK;

	dpidRoom = lpDPInfo->lpGroupTree->GetDPIDOfCurrentSelectionParent();
	dpidPlayer = lpDPInfo->lpGroupTree->GetDPIDOfCurrentSelection();

	// delete the player from the group
	hr = IDirectPlay3_DeletePlayerFromGroup(lpDPInfo->lpDirectPlay3A, dpidRoom, dpidPlayer );

	return (hr);
}

///////////////////////////////////////////////////////////////////////////////////////
HRESULT DoCreateTable(HWND hWnd, LPDPLAYINFO lpDPInfo)
{
	LOBBYGROUPCONTEXT	context;


	context.lpDPInfo = lpDPInfo;
	context.dpidRoom = lpDPInfo->lpGroupTree->GetDPIDOfCurrentSelection();

	DialogBoxParam(ghInstance, MAKEINTRESOURCE(IDD_LOBBYGROUPDIALOG), hWnd,
					  (DLGPROC) LobbyGroupWndProc, (LPARAM) &context);
	return (DP_OK);
}

///////////////////////////////////////////////////////////////////////////////////////
HRESULT DoDeleteTable(HWND hWnd, LPDPLAYINFO lpDPInfo)
{
	DPID				dpidRoom,
						dpidShortcut;
	HRESULT				hr = DP_OK;

	dpidRoom = lpDPInfo->lpGroupTree->GetDPIDOfCurrentSelectionParent();
	dpidShortcut = lpDPInfo->lpGroupTree->GetDPIDOfCurrentSelection();

	// delete the player from the group
	hr = IDirectPlay3_DeleteGroupFromGroup(lpDPInfo->lpDirectPlay3A, dpidRoom, dpidShortcut );
	return (hr);
}

///////////////////////////////////////////////////////////////////////////////////////
HRESULT DoLaunch(HWND hWnd, LPDPLAYINFO lpDPInfo)
{
	DPID				dpidRoom;
	HRESULT				hr = DPERR_GENERIC;

	dpidRoom = lpDPInfo->lpGroupTree->GetDPIDOfCurrentSelection();

	hr = IDirectPlay3_StartSession(lpDPInfo->lpDirectPlay3A, 0, dpidRoom); 

	return (hr);
}

///////////////////////////////////////////////////////////////////////////////////////
HRESULT InitializeLobby(HWND hWnd, LPDPLAYINFO lpDPInfo)
{
	DPNAME		name;
	DPID		dpID;
	HRESULT		hr = DP_OK;

	if (lpDPInfo->bIsHost)
	{	
		// add some groups to start with
		ZeroMemory(&name, sizeof(DPNAME));
		name.dwSize = sizeof(DPNAME);

		name.lpszShortNameA = "Golf Shack";
		hr = IDirectPlay3_CreateGroup(lpDPInfo->lpDirectPlay3A, &dpID, &name, NULL, 0, 0);
		if FAILED(hr)
			goto FAILURE;

		name.lpszShortNameA = "Monster Truck Rally";
		hr = IDirectPlay3_CreateGroup(lpDPInfo->lpDirectPlay3A, &dpID, &name, NULL, 0, 0);
		if FAILED(hr)
			goto FAILURE;

		name.lpszShortNameA = "Club Hellbender";
		hr = IDirectPlay3_CreateGroup(lpDPInfo->lpDirectPlay3A, &dpID, &name, NULL, 0, 0);
		if FAILED(hr)
			goto FAILURE;
	}

FAILURE:
	return (hr);
}

///////////////////////////////////////////////////////////////////////////////////////
void LogString(LPSTR lpszDisplayFormat, LPSTR lpszDataStr)
{
	LPSTR	lpszStr;

		// allocate space for string
	lpszStr = (LPSTR) GlobalAllocPtr(GHND, lstrlen(lpszDisplayFormat) +
										   lstrlen(lpszDataStr) + 1);
	if (lpszStr == NULL)
		return;

	// build string
	wsprintf(lpszStr, lpszDisplayFormat, lpszDataStr);

	// post string to chat window
	// make sure window is still valid
	if (ghMainWnd)
		PostMessage(ghMainWnd, WM_USER_ADDSTRING, (WPARAM) 0, (LPARAM) lpszStr);
	else
		GlobalFreePtr(lpszStr);
}

///////////////////////////////////////////////////////////////////////////////////////
HRESULT SendChatMessage(HWND hWnd, LPDPLAYINFO lpDPInfo)
{
	LPSTR				lpszChatStr = NULL;
	LPSTR				lpszStr = NULL;
	LONG				lStrLen;
	HRESULT				hr;
	DPCHAT				dpc;
	DPID				dpidTarget;

	// get length of item text
	lStrLen = SendDlgItemMessage(hWnd, IDC_SENDEDIT, WM_GETTEXTLENGTH,
								(WPARAM) 0, (LPARAM) 0);

	// make room for it
	lpszChatStr = (LPSTR) GlobalAllocPtr(GHND, lStrLen + 1);
	if (lpszChatStr == NULL)
	{
		hr = DPERR_OUTOFMEMORY;
		goto FAILURE;
	}

	// get item text
	lStrLen = GetDlgItemText(hWnd, IDC_SENDEDIT, lpszChatStr, lStrLen + 1);

	// create string to display this text
	hr = NewChatString(lpDPInfo->lpDirectPlay3A, lpDPInfo->dpidPlayer, lpszChatStr, &lpszStr);
	if FAILED(hr)
		goto FAILURE;

	// setup the DPCHAT struct
	memset(&dpc, 0, sizeof(DPCHAT));
	dpc.dwSize = sizeof(DPCHAT);
	dpc.lpszMessageA = lpszStr;
	BRANCHSTRUCT	bs;
	
	dpidTarget = lpDPInfo->lpGroupTree->GetDPIDOfCurrentSelection( &bs );

	hr = IDirectPlay3_SendChatMessage(lpDPInfo->lpDirectPlay3A, lpDPInfo->dpidPlayer,
			dpidTarget, DPSEND_GUARANTEED, &dpc);


	if FAILED(hr)
		goto FAILURE;

	// display this string
	PostMessage(hWnd, WM_USER_ADDSTRING, (WPARAM) 0, (LPARAM) lpszStr);
	lpszStr = NULL;						// set to NULL so we don't delete it below

FAILURE:
	if (lpszChatStr)
		GlobalFreePtr(lpszChatStr);

	if (lpszStr)
		GlobalFreePtr(lpszStr);

	SetDlgItemText(hWnd, IDC_SENDEDIT, "");

	return (hr);
}

///////////////////////////////////////////////////////////////////////////////////////
HRESULT NewChatString(LPDIRECTPLAY3A lpDirectPlay3A, DPID dpidPlayer,
					  LPSTR lpszMsg, LPSTR *lplpszStr)
{
	LPDPNAME	lpName = NULL;
	LPSTR		lpszStr = NULL;
	LPSTR		lpszPlayerName;
	LPSTR		szDisplayFormat = "%s>\t%s\r\n";
	HRESULT		hr;
	
	// get name of player
	hr = GetPlayerName(lpDirectPlay3A, dpidPlayer, &lpName);
	if FAILED(hr)
		goto FAILURE;

	if (lpName->lpszShortNameA)
		lpszPlayerName = lpName->lpszShortNameA;
	else
		lpszPlayerName = "unknown";

	// allocate space for display string
	lpszStr = (LPSTR) GlobalAllocPtr(GHND, lstrlen(szDisplayFormat) +
										   lstrlen(lpszPlayerName) +
										   lstrlen(lpszMsg) + 1);
	if (lpszStr == NULL)
	{
		hr = DPERR_OUTOFMEMORY;
		goto FAILURE;
	}

	// build string
	wsprintf(lpszStr, szDisplayFormat, lpszPlayerName, lpszMsg);

	*lplpszStr = lpszStr;
	lpszStr = NULL;

FAILURE:
	if (lpszStr)
		GlobalFreePtr(lpszStr);
	
	if (lpName)
		GlobalFreePtr(lpName);

	return (hr);
}


///////////////////////////////////////////////////////////////////////////////////////
HRESULT WaitForRunMsg( DWORD dwAppId, HANDLE hReceiveEvent, LPDWORD lpdwStatus, LPDPLAYINFO lpDPInfo )
{
	LPVOID              lpvMsg          = NULL;
    DWORD               dwMsgFlags;
	DWORD				dwMsgSize		= 0;
	BOOL				bContinue		= TRUE;
	BOOL				bNotFinished	= TRUE;
    HRESULT             hr				= E_FAIL;

	// For this function, we could have spun a seperate thread or integrated
	// the app/lobby client messaging into the main receive thread. 
	// For simplicity sake, the app/lobby client messaging loop is contained below. 

	// There are seven possible states that get us out of this function: 
	//	1. receive DPLSYS_DPLAYCONNECTSUCCEEDED
	//  2. receive DPLSYS_DPLAYCONNECTFAILED
	//  3. (Option) timeout waiting for hReceiveEvent
	//  4. DPERR_OUTOFMEMORY
	//  5. We receive an unexpected player-to-player msg.
	//  6. The app terminated.
	//  7. We get a system message we don't know about.
	//  8. We get an error calling receive

	*lpdwStatus = 0;

	while (bNotFinished)
	{
		if (hReceiveEvent)
		{
			if (WAIT_TIMEOUT == WaitForSingleObject( hReceiveEvent, 20000 ))
			{
				hr = DPERR_TIMEOUT;
				bNotFinished = FALSE;
				break;
			}
		}

		do
		{
			hr =IDirectPlayLobby_ReceiveLobbyMessage(	lpDPInfo->lpDirectPlayLobby2A, 
														0, dwAppId, &dwMsgFlags, 
														lpvMsg, &dwMsgSize);

			switch( hr )
			{
				case DPERR_BUFFERTOOSMALL:
					{
						if (lpvMsg)
						{
							GlobalFreePtr( lpvMsg );
							lpvMsg = NULL;
						}

						lpvMsg = GlobalAllocPtr(GHND, dwMsgSize);
						if(!lpvMsg)
						{	hr = DPERR_OUTOFMEMORY;
							goto end;
						}
					}
					break;

				case DP_OK:
				{
					// This better be a system message
					if(!(dwMsgFlags & DPLAD_SYSTEM))
					{
						LPDPMSG_GENERIC lp = (LPDPMSG_GENERIC) lpvMsg;
						hr = DPERR_GENERIC;
						goto end;
					}

					if ( lpvMsg )
					{
						// Switch on the system message type
						*lpdwStatus = *(LPDWORD)lpvMsg;

						switch(*lpdwStatus)
						{
							case DPLSYS_APPTERMINATED:
								// App shut down
								bNotFinished = FALSE;
								bContinue = FALSE;
								break;

							case DPLSYS_CONNECTIONSETTINGSREAD:
								break;

							case DPLSYS_DPLAYCONNECTSUCCEEDED:
							case DPLSYS_DPLAYCONNECTFAILED:
								bNotFinished = FALSE;
								break;

							default:
								// RUNDPMSGLOG: Unexpected system message type
								hr = DPERR_GENERIC;
								bContinue = FALSE;
								bNotFinished = FALSE;
								break;
						}
					}
				}
				break;

				case DPERR_NOMESSAGES:
					// There are no messages left. 
					// We need to stop and wait for another
					bContinue = FALSE;
					break;

				default:
					goto end;
					break;
			}

		} while( bContinue );
	}

end:
	
	// Free resources
    GlobalFreePtr( lpvMsg );

    // Return 
    return (DPERR_NOMESSAGES == hr ? DP_OK : hr );
}

///////////////////////////////////////////////////////////////////////////////////////
void HandleStartSession(LPDPLCONNECTION lpConn, LPDPLAYINFO lpDPInfo )
{
	DWORD				dwAppID;
	CHAR				szStr[MAXSTRLEN];
	HRESULT				hr;
	HANDLE				hEvent = CreateEvent( NULL, FALSE, FALSE, NULL );
	DWORD				dwStatus = 0;
	
	if (hEvent)
	{
		// display name of application to launch
		hr = GetLocalAppName(lpDPInfo->lpDirectPlayLobby2A, 
						&lpConn->lpSessionDesc->guidApplication, szStr);

		if FAILED(hr)
			lstrcpy(szStr, "unknown");
		
		LogString("Launching \"%s\"...\r\n", szStr);
		
		// Call RunApplication
		hr = IDirectPlayLobby_RunApplication(lpDPInfo->lpDirectPlayLobby2A, 0, &dwAppID, lpConn, hEvent );

		if FAILED(hr)
		{
			ErrorBox("Could not launch application because of error 0x%08X", hr);
		}
		else
		{
			// Wait for the app to launch
			hr = WaitForRunMsg( dwAppID, hEvent, &dwStatus, lpDPInfo );
		}

		CloseHandle( hEvent );
	}

} // HandleStartSession


///////////////////////////////////////////////////////////////////////////////////////
BOOL FAR PASCAL EnumApp(LPCDPLAPPINFO lpAppInfo, LPVOID lpContext, DWORD dwFlags)
{
    HWND			hWnd = (HWND)lpContext;
    LRESULT			iIndex;
	LPGUID			lpGuid;

	// store application name in combo box
	iIndex = SendDlgItemMessage(hWnd, IDC_APPCOMBO, CB_ADDSTRING, 0, (LPARAM) lpAppInfo->lpszAppNameA);
	if (iIndex == LB_ERR)
		goto Failure;

	// make space for application GUID
	lpGuid = (LPGUID) GlobalAllocPtr(GHND, sizeof(GUID));
	if (lpGuid == NULL)
		goto Failure;

	// store pointer to GUID in combo box
	*lpGuid = lpAppInfo->guidApplication;
	SendDlgItemMessage(hWnd, IDC_APPCOMBO, CB_SETITEMDATA, (WPARAM) iIndex, (LPARAM) lpGuid);

Failure:
    return (TRUE);
}

///////////////////////////////////////////////////////////////////////////////////////
HRESULT GetComboBoxGuid(HWND hWnd, LONG iDialogItem, LPGUID lpguidReturn)
{
	LONG	iIndex;

	// get index of selected item
	iIndex = SendDlgItemMessage(hWnd, iDialogItem, CB_GETCURSEL,
								(WPARAM) 0, (LPARAM) 0);
	if (iIndex == CB_ERR)
		return (DPERR_GENERIC);

	// get data associated with this item
	iIndex = SendDlgItemMessage(hWnd, iDialogItem, CB_GETITEMDATA,
								(WPARAM) iIndex, (LPARAM) 0);
	if ((iIndex == CB_ERR) || (iIndex == 0))
		return (DPERR_GENERIC);

	// data is a pointer to a guid
	*lpguidReturn = *((LPGUID) iIndex);

	return (DP_OK);
}

///////////////////////////////////////////////////////////////////////////////////////
BOOL FAR PASCAL GetLocalAppNameCallback(LPCDPLAPPINFO lpAppInfo, LPVOID lpContext, DWORD dwFlags)
{
    LPAPPNAMECONTEXT	lpAppNameContext = (LPAPPNAMECONTEXT) lpContext;

	if (IsEqualGUID(lpAppInfo->guidApplication, lpAppNameContext->guidApplication))
	{
		lstrcpy(lpAppNameContext->szAppName, lpAppInfo->lpszAppNameA);
		return (FALSE);
	}

    return (TRUE);
}

///////////////////////////////////////////////////////////////////////////////////////
HRESULT GetLocalAppName(LPDIRECTPLAYLOBBY lpIDPL,
						LPGUID lpguidApplication, LPSTR lpszAppName)
{
	HRESULT			hr;
	APPNAMECONTEXT	AppNameContext;

	ZeroMemory(&AppNameContext, sizeof(APPNAMECONTEXT));
	AppNameContext.guidApplication = *lpguidApplication;

	// search local apps for matching guid
	hr = IDirectPlayLobby_EnumLocalApplications(lpIDPL, GetLocalAppNameCallback, &AppNameContext, 0);
	if FAILED(hr)
		goto FAILURE;

	// no local app found matching this guid
	if (lstrlen(AppNameContext.szAppName) == 0)
	{
		hr = DPERR_GENERIC;
		goto FAILURE;
	}

	// return name
	lstrcpy(lpszAppName, AppNameContext.szAppName);

FAILURE:
	return (hr);
}

///////////////////////////////////////////////////////////////////////////////////////
void ErrorBox(LPSTR lpszErrorStr, HRESULT hr)
{
	char	szStr[MAXSTRLEN];

	wsprintf(szStr, lpszErrorStr, hr);

	MessageBox(NULL, szStr, "Error", MB_OK);
}

///////////////////////////////////////////////////////////////////////////////////////
void OnSize(HWND hWnd, LPDPLAYINFO lpDPInfo)
{
    HDWP hDWP;
    RECT ClientRect;
    int Height;
	int xSpacing = lpDPInfo->xSpacing;
	int ySpacing = lpDPInfo->ySpacing;
    HWND hKeyTreeWnd;
    HWND hValueListWnd;
	HWND hMsgEditWnd;
	HWND hSendButtonWnd;
    int x;
    int dx;
	RECT SendButtonRect;
	int sendbuttonwidth;
	int sendbuttonheight;

    if (IsIconic(hWnd))
        return;

    if ((hDWP = BeginDeferWindowPos(4)) != NULL)
    {
        //  Data structure used when calling GetEffectiveClientRect (which takes into
        //  account space taken up by the toolbars/status bars).  First half of the
        //  pair is zero when at the end of the list, second half is the control id.
        int s_EffectiveClientRectData[] = {
            1, 0,                               //  For the menu bar, but is unused
            0, 0                                //  First zero marks end of data
        };

        GetEffectiveClientRect(hWnd, &ClientRect, s_EffectiveClientRectData);
        Height = ClientRect.bottom - ClientRect.top - (ySpacing * 5);

		// Resize the tree control
		hKeyTreeWnd = GetDlgItem( hWnd, IDT_MESSAGEVIEW );

        DeferWindowPos(hDWP, hKeyTreeWnd, NULL, 
			xSpacing, ClientRect.top + ySpacing, 
			lpDPInfo->xPaneSplit, Height, 
			SWP_NOZORDER | SWP_NOACTIVATE);

        x = lpDPInfo->xPaneSplit + lpDPInfo->xHalfSplitWidth * 2;
        dx = ClientRect.right - ClientRect.left - x - xSpacing;

        // Resize the logging window
		hValueListWnd = GetDlgItem( hWnd, IDC_LOGEDIT );

        DeferWindowPos(hDWP, hValueListWnd, NULL, 
			x, ClientRect.top+ySpacing, 
			dx, Height,
            SWP_NOZORDER | SWP_NOACTIVATE);

        // move the Send button, its size is constant
		hSendButtonWnd = GetDlgItem( hWnd, IDC_SENDBUTTON);

		GetWindowRect( hSendButtonWnd, &SendButtonRect );
		sendbuttonwidth = SendButtonRect.right - SendButtonRect.left; 
		sendbuttonheight = SendButtonRect.bottom - SendButtonRect.top; 

        DeferWindowPos(hDWP, hSendButtonWnd, NULL, 
			ClientRect.right - ( sendbuttonwidth + xSpacing ), 
			ClientRect.bottom - ( sendbuttonheight + ySpacing ), 
			sendbuttonwidth, 
			sendbuttonheight,
            SWP_NOZORDER | SWP_NOACTIVATE);

        // Resize and move the message edit control
		hMsgEditWnd = GetDlgItem( hWnd, IDC_SENDEDIT );

        DeferWindowPos(hDWP, hMsgEditWnd, NULL, 
			ClientRect.left + xSpacing, 
			ClientRect.bottom - ( sendbuttonheight + ySpacing ), 
			ClientRect.right - ClientRect.left - (sendbuttonwidth + xSpacing * 3), 
			sendbuttonheight,
            SWP_NOZORDER | SWP_NOACTIVATE);

		EndDeferWindowPos(hDWP);
    }
}
