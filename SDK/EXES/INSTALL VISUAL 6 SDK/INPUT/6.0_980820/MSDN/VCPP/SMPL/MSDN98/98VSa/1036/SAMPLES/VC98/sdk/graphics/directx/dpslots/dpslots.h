/*==========================================================================
 *
 *  Copyright (C) 1997 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       dpslots.h
 *  Content:	common dpslots headers
 *
 ***************************************************************************/

#define IDIRECTPLAY2_OR_GREATER
#include <dplay.h>
#include <dplobby.h>

// constants
#define NUMWHEELS			    3		// no. wheels
#define SLOTSPERWHEEL		    6		// no. slots per wheel
#define MAXSTRLEN				200		// max size of a string
#define DEFAULTDATABASE			"slotsdb.txt" // default name of database file

// flags to use when creating players
#define CLIENTPLAYERFLAGS			0
#define SERVERPLAYERFLAGS			(DPPLAYER_SERVERPLAYER)

// flags to use when sending messages
#define NONSECURESENDFLAGS			(DPSEND_GUARANTEED)
#define SECURESENDFLAGS				(DPSEND_GUARANTEED |	\
									 DPSEND_SIGNED |		\
									 DPSEND_ENCRYPTED)
#define SENDFLAGS(bIsSecure)		((bIsSecure) ? SECURESENDFLAGS : NONSECURESENDFLAGS)

// flags to use when creating sessions
#define NONSECURESESSIONFLAGS		(DPSESSION_KEEPALIVE |		\
									 DPSESSION_CLIENTSERVER)
#define SECURESESSIONFLAGS			(DPSESSION_KEEPALIVE |		\
									 DPSESSION_CLIENTSERVER |	\
									 DPSESSION_SECURESERVER)
#define SESSIONFLAGS(bIsSecure)		((bIsSecure) ? SECURESESSIONFLAGS : NONSECURESESSIONFLAGS)

// client messages
#define BALANCEREQUEST			300		// request for account balance
#define SPINREQUEST				302		// request for spin

// server messages
#define BALANCERESPONSE			400		// account balance reply
#define SPINRESPONSE			401		// spin reply

// structure used to store DirectPlay information
typedef struct {
	LPDIRECTPLAY3A	lpDirectPlay3A;		// IDirectPlay3A interface pointer
	HANDLE			hPlayerEvent;		// player event to use
	DPID			dpidPlayer;			// ID of player created
	BOOL			bIsHost;			// TRUE if we are hosting the session
	BOOL			bIsSecure;			// TRUE if session is secure
} DPLAYINFO, *LPDPLAYINFO;

// message structures

// used to request the results of a wager
typedef struct {
    DWORD   dwType;						// message type
    DWORD   dwAmountBet;				// amount to wager
} MSG_SPINREQUEST, *LPMSG_SPINREQUEST;

// response to wager request
typedef struct {
    DWORD   dwType;						// message type
	HRESULT	hr;							// result of request
	LONG	dwAmountWonOrLost;			// amount won or lost
    DWORD   dwBalance;					// current balance after wager
    DWORD   dwIndex[NUMWHEELS];			// slot settings
} MSG_SPINRESPONSE, *LPMSG_SPINRESPONSE;

// used to request current balance
typedef struct {
    DWORD	dwType;						// message type
} MSG_BALANCEREQUEST, *LPMSG_BALANCEREQUEST;

// response to balance request
typedef struct {
    DWORD	dwType;						// message type
	HRESULT	hr;							// result of request
    DWORD	dwBalance;					// current balance
} MSG_BALANCERESPONSE, *LPMSG_BALANCERESPONSE;

// guid for this application
// {EC4F7AA0-E1E0-11d0-9C50-00A0C905425E}
DEFINE_GUID(DPSLOTS_GUID, 
0xec4f7aa0, 0xe1e0, 0x11d0, 0x9c, 0x50, 0x0, 0xa0, 0xc9, 0x5, 0x42, 0x5e);

// globals
extern HINSTANCE		ghInstance;		// instance of application
extern CHAR				gszDatabaseName[MAXSTRLEN];

// common prototypes
extern HRESULT			ConnectUsingLobby(LPDPLAYINFO lpDPInfo);
extern HRESULT			ConnectUsingDialog(HINSTANCE hInstance, LPDPLAYINFO lpDPInfo);
extern void				ErrorBox(LPSTR lpszErrorStr, HRESULT hr);
extern void				CheckDlgItem(HWND hDlg, int nIDDlgItem, BOOL bCheck);
extern BOOL				DlgItemIsChecked(HWND hDlg, int nIDDlgItem);
extern void				EnableDlgButton(HWND hDlg, int nIDDlgItem, BOOL bEnable);

// client prototypes
extern BOOL CALLBACK	ClientWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
extern void				ClientSystemMessage(LPDPLAYINFO lpDPInfo, LPDPMSG_GENERIC lpMsg, DWORD dwMsgSize,
											DPID idFrom, DPID idTo);
extern void				ClientApplicationMessage(LPDPLAYINFO lpDPInfo, LPDPMSG_GENERIC lpMsg, DWORD dwMsgSize,
												 DPID idFrom, DPID idTo);
// server prototypes
extern BOOL CALLBACK	ServerWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
extern void				ServerSystemMessage(LPDPLAYINFO lpDPInfo, LPDPMSG_GENERIC lpMsg, DWORD dwMsgSize,
											DPID idFrom, DPID idTo);
extern void				ServerApplicationMessage(LPDPLAYINFO lpDPInfo, LPDPMSG_GENERIC lpMsg, DWORD dwMsgSize,
												 DPID idFrom, DPID idTo);
