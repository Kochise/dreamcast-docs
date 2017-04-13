/*==========================================================================
 *
 *  Copyright (C) 1997 Microsoft Corporation.  All Rights Reserved.
 *
 *  File:       server.cpp
 *  Content:	Slot machine server using DirectPlay.
 *
 ***************************************************************************/

#include <windows.h>
#include <windowsx.h>
#include <stdio.h>

#include "dpslots.h"
#include "resource.h"

// constants
const UINT	MAX_RECORD_LENGTH	= 256;			// max database record size
const DWORD	INDEX_JACKPOT		= 3;			// index of jackpot image
const DWORD	INDEX_SPOILER		= 5;			// index of spoiler image

// window messages
const UINT	WM_USER_ADDSTRING = WM_USER + 257;	// add string to log window

// structures
typedef struct {
	DWORD	dwBalance;							// account record from database
} ACCOUNTINFO, *LPACCOUNTINFO;

// globals
HWND			ghServerWnd = NULL;				// main window
FILE			*glpFile = NULL;				// database file

// prototypes
HRESULT			HandleBalanceRequest(LPDPLAYINFO lpDPInfo, LPMSG_BALANCEREQUEST lpBalance, DPID idTo);
HRESULT			HandleSpinRequest(LPDPLAYINFO lpDPInfo, LPMSG_SPINREQUEST lpBalance, DPID idTo);
void			LogRequest(LPSTR lpszFormat, LPDPACCOUNTDESC lpAccountDesc, DWORD dwValue);
LONG			GetAmountWonOrLost(DWORD dwAmountBet, DWORD dwIndex[]);
FILE*			OpenAccountDB(LPSTR lpszDBName);
void			CloseAccountDB(FILE *lpFile);
BOOL			QueryAccount(FILE *lpFile, LPSTR lpszAccountID, LPACCOUNTINFO lpAccountInfo);
BOOL			UpdateAccount(FILE *lpFile, LPSTR lpszAccountID, LPACCOUNTINFO lpAccountInfo);
HRESULT			GetAccountDesc(LPDPLAYINFO lpDPInfo, DPID idPlayer, LPDPACCOUNTDESC *lplpAccountDesc);

BOOL CALLBACK ServerWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static LPDPLAYINFO	lpDPInfo = NULL;
	static UINT			idTimer = 0;
	static FILE			*lpFile = NULL;
	DWORD				dwTextLen;

    switch(uMsg)
    {
    case WM_INITDIALOG:
        // save the connection info pointer
        lpDPInfo = (LPDPLAYINFO) lParam;

		// store global window
		ghServerWnd = hWnd;

		// open account database
		glpFile = OpenAccountDB(gszDatabaseName);
		break;

    case WM_DESTROY:
		// stop the timer
		if (idTimer)
		{
			KillTimer(hWnd, idTimer); 
			idTimer = 0;
		}

		// close account database
		if (glpFile)
			CloseAccountDB(glpFile);

		ghServerWnd = NULL;
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
        case IDCANCEL:
			EndDialog(hWnd, FALSE);
            break;
		}
		break;
	}

    // Allow for default processing
    return FALSE;
}

void ServerApplicationMessage(LPDPLAYINFO lpDPInfo, LPDPMSG_GENERIC lpMsg, DWORD dwMsgSize,
							  DPID idFrom, DPID idTo)
{
	switch (lpMsg->dwType)
	{
    case BALANCEREQUEST:

		HandleBalanceRequest(lpDPInfo, (LPMSG_BALANCEREQUEST)lpMsg, idFrom);
        break;

    case SPINREQUEST:

		HandleSpinRequest(lpDPInfo, (LPMSG_SPINREQUEST)lpMsg, idFrom);
        break;

    default:
        break; 
	}
}

void ServerSystemMessage(LPDPLAYINFO lpDPInfo, LPDPMSG_GENERIC lpMsg, DWORD dwMsgSize,
						 DPID idFrom, DPID idTo)
{
    // The body of each case is there so you can set a breakpoint and examine
    // the contents of the message received.
	switch (lpMsg->dwType)
	{
	case DPSYS_CREATEPLAYERORGROUP:
        {
            LPDPMSG_CREATEPLAYERORGROUP lp = (LPDPMSG_CREATEPLAYERORGROUP) lpMsg;
        }
		break;

	case DPSYS_DESTROYPLAYERORGROUP:
        {
            LPDPMSG_DESTROYPLAYERORGROUP lp = (LPDPMSG_DESTROYPLAYERORGROUP)lpMsg;
        }
		break;

	case DPSYS_ADDPLAYERTOGROUP:
        {
            LPDPMSG_ADDPLAYERTOGROUP lp = (LPDPMSG_ADDPLAYERTOGROUP)lpMsg;
        }
		break;

	case DPSYS_DELETEPLAYERFROMGROUP:
        {
            LPDPMSG_DELETEPLAYERFROMGROUP lp = (LPDPMSG_DELETEPLAYERFROMGROUP)lpMsg;
        }
		break;

	case DPSYS_SESSIONLOST:
        {
            LPDPMSG_SESSIONLOST lp = (LPDPMSG_SESSIONLOST)lpMsg;
        }
		break;

	case DPSYS_HOST:
        {
            LPDPMSG_HOST	lp = (LPDPMSG_HOST)lpMsg;
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

	case DPSYS_SECUREMESSAGE:
        {
            LPDPMSG_SECUREMESSAGE lp = (LPDPMSG_SECUREMESSAGE)lpMsg;

			ServerApplicationMessage(lpDPInfo, (LPDPMSG_GENERIC) lp->lpData, lp->dwDataSize,
							  lp->dpIdFrom, idTo);

        }
		break;
	}
}

HRESULT HandleBalanceRequest(LPDPLAYINFO lpDPInfo, LPMSG_BALANCEREQUEST lpBalance, DPID idTo)
{
    MSG_BALANCERESPONSE	Msg;
	LPDPACCOUNTDESC		lpAccountDesc = NULL;
	ACCOUNTINFO			AccountInfo;
	HRESULT				hr;

	// create balance response message
	ZeroMemory(&Msg, sizeof(MSG_BALANCERESPONSE));
	Msg.dwType = BALANCERESPONSE;

	// get account description for this player
	hr = GetAccountDesc(lpDPInfo, idTo, &lpAccountDesc);
    if FAILED(hr)
		goto FAILURE;

	// get account information from database using account ID
	if ((glpFile == NULL) ||
		(!QueryAccount(glpFile, lpAccountDesc->lpszAccountIDA, &AccountInfo)))
	{
		hr = DPERR_ACCESSDENIED;
		goto FAILURE;
	}

	// return balance from database
	Msg.dwBalance = AccountInfo.dwBalance;

FAILURE:
	Msg.hr = hr;

	if FAILED(Msg.hr)
		LogRequest("Balance request for \"%s\" failed: 0x%08X\r\n", lpAccountDesc, Msg.hr);
	else
		LogRequest("Balance request for \"%s\" returned $%d\r\n", lpAccountDesc, Msg.dwBalance);

	if (lpAccountDesc)
		GlobalFreePtr(lpAccountDesc);

	// send the message
    return (lpDPInfo->lpDirectPlay3A->Send(lpDPInfo->dpidPlayer,
						idTo, SENDFLAGS(lpDPInfo->bIsSecure),
						&Msg, sizeof(MSG_BALANCERESPONSE)));
}

HRESULT HandleSpinRequest(LPDPLAYINFO lpDPInfo, LPMSG_SPINREQUEST lpSpin, DPID idTo)
{
    MSG_SPINRESPONSE	Msg;
	LPDPACCOUNTDESC		lpAccountDesc = NULL;
	ACCOUNTINFO			AccountInfo;
	DWORD				i;
	HRESULT				hr;

	// create spin response message
    ZeroMemory(&Msg, sizeof(MSG_SPINRESPONSE));
    Msg.dwType = SPINRESPONSE;

	// get account description for this player
	hr = GetAccountDesc(lpDPInfo, idTo, &lpAccountDesc);
    if FAILED(hr)
		goto FAILURE;

	// get account information from database using account ID
	if ((glpFile == NULL) ||
		(!QueryAccount(glpFile, lpAccountDesc->lpszAccountIDA, &AccountInfo)))
	{
		hr = DPERR_ACCESSDENIED;
		goto FAILURE;
	}

	// bet exceeds balance in database
	if (lpSpin->dwAmountBet > AccountInfo.dwBalance)
	{
		hr = DPERR_UNAVAILABLE;
		goto FAILURE;
	}

	// generate new slot settings
	for (i = 0; i < NUMWHEELS; i++)
		Msg.dwIndex[i] = ((DWORD)rand()) % SLOTSPERWHEEL;

	// determine amount won or lost
	Msg.dwAmountWonOrLost = GetAmountWonOrLost(lpSpin->dwAmountBet, Msg.dwIndex);

	// update account info in database for this player
	AccountInfo.dwBalance += Msg.dwAmountWonOrLost;

	if (!UpdateAccount(glpFile, lpAccountDesc->lpszAccountIDA, &AccountInfo))
	{
		hr = DPERR_ACCESSDENIED;
		goto FAILURE;
	}

	// send new balance back
    Msg.dwBalance = AccountInfo.dwBalance;

FAILURE:
	Msg.hr = hr;

	if FAILED(Msg.hr)
		LogRequest("Spin request for \"%s\" failed: 0x%08X\r\n", lpAccountDesc, Msg.hr);
	else
		LogRequest("Spin request for \"%s\" returned $%d\r\n", lpAccountDesc, Msg.dwAmountWonOrLost);

	if (lpAccountDesc)
		GlobalFreePtr(lpAccountDesc);

	// send the message
    return (lpDPInfo->lpDirectPlay3A->Send(lpDPInfo->dpidPlayer,
						idTo, SENDFLAGS(lpDPInfo->bIsSecure),
						&Msg, sizeof(MSG_SPINRESPONSE)));
}

void LogRequest(LPSTR lpszFormat, LPDPACCOUNTDESC lpAccountDesc, DWORD dwValue)
{
	LPSTR	lpszStr;
	LPSTR	lpszAccountID;

	// make sure we have an account ID
	if (lpAccountDesc == NULL)
		lpszAccountID = "unknown";
	else
		lpszAccountID = lpAccountDesc->lpszAccountIDA;

	// create a buffer for the output string, account string and a numeric value
	lpszStr = (LPSTR) GlobalAllocPtr(GHND, strlen(lpszFormat) + strlen(lpszAccountID) + 10);
	if (lpszStr == NULL)
		return;

	// format the string to log
	wsprintf(lpszStr, lpszFormat, lpszAccountID, dwValue);

	// log it - main wnd proc will dispose of the string
	PostMessage(ghServerWnd, WM_USER_ADDSTRING, (WPARAM) 0, (LPARAM) lpszStr);
}

LONG GetAmountWonOrLost(DWORD dwAmountBet, DWORD dwIndex[])
{
	LONG    nMultiplier;

	// check for jackpot
	if ((dwIndex[0] == INDEX_JACKPOT) &&
		(dwIndex[1] == INDEX_JACKPOT) &&
		(dwIndex[2] == INDEX_JACKPOT))
	{
		nMultiplier = 100;
	}

	// three in a row
	else if ((dwIndex[0] == dwIndex[1]) &&
			 (dwIndex[1] == dwIndex[2]))
	{
		nMultiplier = 25;
	}

	// first two match
	else if (dwIndex[0] == dwIndex[1])
	{
		nMultiplier = 5;
	}

	// you lose!
	else
		nMultiplier = -1;

	// any spoiler and you lose
	if ((dwIndex[0] == INDEX_SPOILER) ||
		(dwIndex[1] == INDEX_SPOILER) ||
		(dwIndex[2] == INDEX_SPOILER))
	{
		nMultiplier = -1;
	}

	// return amount won or lost
	return (dwAmountBet * nMultiplier);
}

FILE* OpenAccountDB(LPSTR lpszDBName)
{
	FILE	*lpFile;

	lpFile = fopen(lpszDBName, "r+b");

	return (lpFile);
}

void CloseAccountDB(FILE *lpFile)
{
	fclose(lpFile);
}

BOOL GetRecord(FILE *lpFile, LPSTR lpszKey, LPSTR lpszRecord)
{
	rewind(lpFile);
	while (fgets(lpszRecord, MAX_RECORD_LENGTH, lpFile))
	{
		_strupr(lpszRecord);
		if (!strncmp(lpszRecord, lpszKey, strlen(lpszKey)))
			return (TRUE);
	}

	return (FALSE);
}

BOOL PutRecord(FILE *lpFile, LPSTR lpszKey, LPSTR lpszRecord)
{
	CHAR	szLine[MAX_RECORD_LENGTH];
	DWORD	dwRecordIndex;

	rewind(lpFile);
	dwRecordIndex = 0;
	while (fgets(szLine, MAX_RECORD_LENGTH, lpFile))
	{
		_strupr(szLine);
		if (!strncmp(szLine, lpszKey, strlen(lpszKey)))
		{
			fseek(lpFile, dwRecordIndex, SEEK_SET);
			fputs(lpszRecord, lpFile);
			return (TRUE);
		}
		dwRecordIndex += strlen(szLine);
	}

	return (FALSE);
}

BOOL QueryAccount(FILE *lpFile, LPSTR lpszAccountID, LPACCOUNTINFO lpAccountInfo)
{
    CHAR	szBuffer[MAX_RECORD_LENGTH];
    CHAR	*lpToken;

    if (!GetRecord(lpFile, lpszAccountID, szBuffer))
    {
        return FALSE;
    }

    lpToken = strtok(szBuffer, ",");
    if (lpToken)
    {
        lpToken = strtok(NULL, "\n");
        if (lpToken)
        {
            lpAccountInfo->dwBalance = atoi(lpToken);
        }
    }

    return TRUE;
}

BOOL UpdateAccount(FILE *lpFile, LPSTR lpszAccountID, LPACCOUNTINFO lpAccountInfo)
{
    CHAR	szBuffer[MAX_RECORD_LENGTH];

    if (!GetRecord(lpFile, lpszAccountID, szBuffer))
    {
        return FALSE;
    }

	sprintf(szBuffer, "%s,%8d", lpszAccountID, lpAccountInfo->dwBalance);
	return (PutRecord(lpFile, lpszAccountID, szBuffer));
}

HRESULT GetSecureAccountDesc(LPDPLAYINFO lpDPInfo, DPID idPlayer, LPDPACCOUNTDESC *lplpAccountDesc)
{
	LPDPACCOUNTDESC		lpAccountDesc = NULL;
	DWORD				dwAccountDescSize;
	HRESULT				hr;

	// get size of account description
	hr = lpDPInfo->lpDirectPlay3A->GetPlayerAccount(idPlayer, 0,
									NULL, &dwAccountDescSize);
	if (hr != DPERR_BUFFERTOOSMALL)
		goto FAILURE;

	// make room for it
	lpAccountDesc = (LPDPACCOUNTDESC) GlobalAllocPtr(GHND, dwAccountDescSize);
	if (lpAccountDesc == NULL)
	{
		hr = DPERR_OUTOFMEMORY;
		goto FAILURE;
	}

	// get the account description for this player
	hr = lpDPInfo->lpDirectPlay3A->GetPlayerAccount(idPlayer, 0,
									lpAccountDesc, &dwAccountDescSize);
	if FAILED(hr)
		goto FAILURE;

	// return account description
	_strupr(lpAccountDesc->lpszAccountIDA);
	*lplpAccountDesc = lpAccountDesc;
	lpAccountDesc = NULL;

FAILURE:
	if (lpAccountDesc)
		GlobalFreePtr(lpAccountDesc);

	return (hr);
}

HRESULT GetUnsecureAccountDesc(LPDPLAYINFO lpDPInfo, DPID idPlayer, LPDPACCOUNTDESC *lplpAccountDesc)
{
	LPDPACCOUNTDESC		lpAccountDesc = NULL;
	DWORD				dwAccountDescSize;
	LPDPNAME			lpName;
	HRESULT				hr;

	// get size of player name
	hr = lpDPInfo->lpDirectPlay3A->GetPlayerName(idPlayer,
									NULL, &dwAccountDescSize);
	if (hr != DPERR_BUFFERTOOSMALL)
		goto FAILURE;

	// make room for it
	lpAccountDesc = (LPDPACCOUNTDESC) GlobalAllocPtr(GHND, sizeof(DPACCOUNTDESC) + dwAccountDescSize);
	if (lpAccountDesc == NULL)
	{
		hr = DPERR_OUTOFMEMORY;
		goto FAILURE;
	}

	// get the player name
	lpName = (LPDPNAME) (((LPSTR)lpAccountDesc) + sizeof(DPACCOUNTDESC));
	hr = lpDPInfo->lpDirectPlay3A->GetPlayerName(idPlayer,
									lpName, &dwAccountDescSize);
	if FAILED(hr)
		goto FAILURE;

	// return account description
	lpAccountDesc->lpszAccountIDA = lpName->lpszShortNameA;
	_strupr(lpAccountDesc->lpszAccountIDA);
	*lplpAccountDesc = lpAccountDesc;
	lpAccountDesc = NULL;

FAILURE:
	if (lpAccountDesc)
		GlobalFreePtr(lpAccountDesc);

	return (hr);
}

HRESULT GetAccountDesc(LPDPLAYINFO lpDPInfo, DPID idPlayer, LPDPACCOUNTDESC *lplpAccountDesc)
{
	HRESULT		hr;

	if (lpDPInfo->bIsSecure)
	{
		hr = GetSecureAccountDesc(lpDPInfo, idPlayer, lplpAccountDesc);
	}
	else
	{
		hr = GetUnsecureAccountDesc(lpDPInfo, idPlayer, lplpAccountDesc);
	}

	return (hr);
}
