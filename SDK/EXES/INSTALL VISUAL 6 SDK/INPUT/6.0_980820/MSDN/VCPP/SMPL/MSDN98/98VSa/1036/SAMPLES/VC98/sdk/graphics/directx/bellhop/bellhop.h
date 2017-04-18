/*==========================================================================
 *
 *  Copyright (C) 1996-1997 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       bellhop.h
 *  Content:	Header file for bellhop.cpp
 *
 ***************************************************************************/

#define IDIRECTPLAY2_OR_GREATER
#include <windows.h>
#include <windowsx.h>
#include <dplay.h>
#include <dplobby.h>
#include "CGRpTree.h"

// constants
const DWORD MAXPLAYERS = 10;			// max no. players in the session
const DWORD MAXSTRLEN = 200;			// max. size of a string

// structure used to store DirectPlay information
typedef struct {
	LPDIRECTPLAY3A		lpDirectPlay3A;			// IDirectPlay3A interface pointer
	LPDIRECTPLAYLOBBY2A	lpDirectPlayLobby2A;	// IDirectPlayLobby2A interface pointer
	HANDLE				hPlayerEvent;			// player event to use
	DPID				dpidPlayer;				// ID of player created
	BOOL				bIsHost;				// TRUE if we are hosting the session
	BOOL				bSecureSession;			// TRUE if the session is secure.
	DWORD				dwPlayerFlags;
	CGroupTree	*		lpGroupTree;
	int					xPaneSplit;
	int					xHalfSplitWidth;
	int					ySpacing;
	int					xSpacing;
	BOOL				bSplitMove;
	char				szSecureName[256];
	char				szSecurePassword[256];
	char				szSecureDomain[256];
} DPLAYINFO, *LPDPLAYINFO;

typedef struct {
	HWND	hWnd;
	int		idCombo;
} ENUMCONNSTRUCT, *LPENUMCONNSTRUCT;

typedef struct {
	GUID	guidSP;
	BYTE	Connection[1];
} CONNECTIONINFO, *LPCONNECTIONINFO;

typedef struct {
	GUID	guidInstance;
	DWORD	dwFlags;
} SESSIONINFO, *LPSESSIONINFO;

typedef struct {
	LPDPLAYINFO		lpDPInfo;
	DPID			dpidRoom;
} LOBBYGROUPCONTEXT, *LPLOBBYGROUPCONTEXT;

typedef struct {
	GUID	guidApplication;
	CHAR	szAppName[MAXSTRLEN];
} APPNAMECONTEXT, *LPAPPNAMECONTEXT;

// guid for this application
// {4BF5D540-BDA5-11d0-9C4F-00A0C905425E}
DEFINE_GUID(BELLHOP_GUID, 
0x4bf5d540, 0xbda5, 0x11d0, 0x9c, 0x4f, 0x0, 0xa0, 0xc9, 0x5, 0x42, 0x5e);

// prototypes
extern HRESULT	CreateDirectPlayInterface(LPDIRECTPLAY3A *lplpDirectPlay3A );
extern HRESULT	CreateDirectPlayLobbyInterface(LPDIRECTPLAYLOBBY2A *lplpDirectPlayLobby2A );
extern HRESULT	ConnectUsingDialog(HINSTANCE hInstance, LPDPLAYINFO lpDPInfo);
extern void		ErrorBox(LPSTR lpszErrorStr, HRESULT hr);

// prototypes BELLHOP.CPP
BOOL CALLBACK	LobbyWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK	ConnectionSettingsDialogProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HRESULT			SetupConnection(HINSTANCE hInstance, LPDPLAYINFO lpDPInfo);
HRESULT			ShutdownConnection(LPDPLAYINFO lpDPInfo);
DWORD WINAPI	ReceiveThread(LPVOID lpThreadParameter);
HRESULT			ReceiveMessage(LPDPLAYINFO lpDPInfo);
void			HandleApplicationMessage(LPDPLAYINFO lpDPInfo, LPDPMSG_GENERIC lpMsg, DWORD dwMsgSize,
										 DPID idFrom, DPID idTo);
void			HandleSystemMessage(LPDPLAYINFO lpDPInfo, LPDPMSG_GENERIC lpMsg, DWORD dwMsgSize,
									DPID idFrom, DPID idTo);
HRESULT			GetPlayerName(LPDIRECTPLAY3A lpDirectPlay3A, DPID dpidPlayer,
							  LPDPNAME *lplpName);
HRESULT			GetGroupName(LPDIRECTPLAY3A lpDirectPlay3A, DPID dpidGroup,
							 LPDPNAME *lplpName);
HRESULT			NewChatString(LPDIRECTPLAY3A lpDirectPlay3A, DPID dpidPlayer,
							  LPSTR lpszMsg, LPSTR *lplpszStr);
HRESULT			DoCreateRoom(HWND hWnd, LPDPLAYINFO lpDPInfo);
HRESULT			DoDeleteRoom(HWND hWnd, LPDPLAYINFO lpDPInfo);
HRESULT			DoCreateTable(HWND hWnd, LPDPLAYINFO lpDPInfo);
HRESULT			DoDeleteTable(HWND hWnd, LPDPLAYINFO lpDPInfo);
HRESULT			DoDeletePlayerFromGroup(HWND hWnd, LPDPLAYINFO lpDPInfo);
HRESULT			DoLaunch(HWND hWnd, LPDPLAYINFO lpDPInfo);
HRESULT			DoGroupConnectionSettings(HWND hWnd, LPDPLAYINFO lpDPInfo);
HRESULT			InitializeLobby(HWND hWnd, LPDPLAYINFO lpDPInfo);
HRESULT			UpdateLobbyDisplay(HWND hWnd, LPDPLAYINFO lpDPInfo);
void			UpdateButtons(HWND hWnd, LPDPLAYINFO lpDPInfo);
HRESULT			SendChatMessage(HWND hWnd, LPDPLAYINFO lpDPInfo);

extern void		EnableDlgButton(HWND hWnd, int nIDDlgItem, BOOL bEnable);
void			HandleStartSession(LPDPLCONNECTION lpConn, LPDPLAYINFO lpDPInfo );
BOOL FAR PASCAL	EnumApp(LPCDPLAPPINFO lpAppInfo, LPVOID lpContext, DWORD dwFlags);
HRESULT			GetComboBoxGuid(HWND hWnd, LONG iDialogItem, LPGUID lpguidReturn);
HRESULT			GetLocalAppName(LPDIRECTPLAYLOBBY lpIDPL,
								LPGUID lpguidApplication, LPSTR lpszAppName);
void			LogString(LPSTR lpszDisplayFormat, LPSTR lpszDataStr);
void			OnSize(HWND hWnd, LPDPLAYINFO lpDPInfo);

// Globals
extern HINSTANCE ghInstance;

