/***************************************************************************
 *
 *  Copyright (C) 1999 Microsoft Corporation.  All Rights Reserved.
 *
 *  File : testrun.cpp  
 *  Test application to lobby server
 *
 ***************************************************************************/
#include "testrun.h"
#include "LSPlobby.h"

#define		USERAS		0				// for RAS connection
#define		SERVER_IP	"157.60.52.194"	// IP address of Lobby server 

// GLOVAL AREA
TCHAR	*szUser,*szClient,*szGroup;
GUID guidGame = GUID_NULL;
char	g_ClientName[32];

typedef struct {
    GUID    guidInstance;
    DWORD   dwFlags;
} SESSION_INFO, *LPSESSION_INFO;

LPGUID						g_lpGuid;				// Testrun's GUID
LPDIRECTPLAY3               g_lpDP;
HINSTANCE                   g_hInstApp;
HWND                        g_hWnd;
GUID                        g_guidSession;
HANDLE                      g_AsyncEvent;
HANDLE						g_hReceiveEvent;
HANDLE						g_hReceiveThread;
BOOL						g_bKillThread;
HRASCONN hRasConn;
DPID g_idPlayer;
DPID g_idGroup;
LPTSTR g_szUser;
HWND g_hwndDlg;
DPID g_idPlayer2;
DPID  g_idGroup2;
DPID  g_idGroup3;


// {022AFE1-87B6-11D3-ADF6-0020AF6849EF}
const GUID TESTRUN_GUID =
{ 0x22a0fe1, 0x87b6, 0x11d3, 0xad, 0xf6, 0x0, 0x20, 0xaf, 0x68, 0x49, 0xef};

//  17AF6382-87AF-11D3-ADF6-0020AF6849EF
const GUID GUID_LobbyProvider =
{   0x17af6382, 0x87af, 0x11d3, { 0xad, 0xf6, 0x0, 0x20, 0xaf, 0x68, 0x49, 0xef } };

extern "C" int WINAPI
/***************************************/
/*     Sample Program  MAIN Process    */
/***************************************/
_tWinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    TCHAR *argv[20];
	static TCHAR  szUserBuffer[20];
	static TCHAR  szGroupBuffer[20];
    static TCHAR  szClientBuffer[20];
    char  cServerIP[32];
    int argc, i, result;

	OutputDebugString(TEXT("##### _tWinMain: Start #####\n")); 

    argc = CreateArgvArgc(TEXT("testrun"), argv, lpCmdLine);

    szUser = szClient = szGroup = NULL;

    if (argc == 1)
    {
        Usage();
    }
    else
    {
        for (i = 1; i < argc; i++)
        {
            if (*argv[i] == TEXT('-'))
            {
                switch(argv[i][1])
                {
                case TEXT('u'):			// User Name
                    i++;
                    if (i == argc)                    {
                        Output(TEXT("missing -u argument\r\n"));
                    }
                    else
                    {
                        szUser = argv[i];
                    }
                    break;

                case TEXT('g'):		// Group Name
                    i++;
                    if (i == argc)
                    {
                        Output(TEXT("missing -g argument\r\n"));
                    }
                    else
                    {
                        szGroup = argv[i];
                    }
                    break;

                case TEXT('c'):		// client name
	                i++;
                    if (i == argc)
                    {
                        Output(TEXT("missing -c argument\r\n"));
                    }
                    else
                    {
                        szClient = argv[i];
				       Output(TEXT("##### Lobby option requires that ClientName=%s\n"),szClient);
                    }
                    break;

                default:
                    Output(TEXT("bad option '%c'\r\n"), argv[i][1]);
                    Usage();
                }
            }
            else
            {
                Output(TEXT("encountered unexpected character '%c'\r\n"),argv[i][1]);
                Usage();
            }
        }
    }
	// Set Client name
	if (szClient == NULL)
    {
		memset(g_ClientName,NULL,sizeof(g_ClientName));
        if (RegGetClientID((LPCHAR)g_ClientName) == TRUE)
		{
			mbstowcs(szClientBuffer,g_ClientName,strlen(g_ClientName));
		}
		else
		{
	      wsprintf(szClientBuffer, TEXT("Client%d"), GetCurrentProcessId());
		}
		szClient = szClientBuffer;
	    Output(TEXT("No clientname was specified.  Launching to connect lobby as client '%s'\r\n"), szClient);

    }
	else
	{
		wcstombs(g_ClientName,szClient,32);			// convert to MultiByte code 
	}
	// Set use name
	if (szUser == NULL)
    {
        wsprintf(szUserBuffer, TEXT("User%d"), GetCurrentProcessId());
        szUser = szUserBuffer;
        Output(TEXT("No username was specified.  Launching to connect Lobby as user '%s'\r\n"), szUser);
    }
	// Set group name
	if (szGroup == NULL)
    {
        wsprintf(szGroupBuffer, TEXT("Group%d"), GetCurrentProcessId());
        szGroup = szGroupBuffer;
        Output(TEXT("No groupname was specified.  Launching to connect Lobby as group '%s'\r\n"), szGroup);
    }
	// Set Client data to REG
	memset(cServerIP,NULL,sizeof(cServerIP));
	memcpy(cServerIP,SERVER_IP,sizeof(SERVER_IP));
    Output(TEXT("###### SERVER IP length=%d \n"), sizeof(SERVER_IP));
	if (SetRegInformation((LPSTR)g_ClientName, (LPSTR)cServerIP) != TRUE)
	{
        Output(TEXT("SetRegInformation: Error return \n"));
		return FALSE;
    }

	result = StartConnectViaLobbyServer(hInstance, szUser);
    return result;
}


int CreateArgvArgc(TCHAR *pProgName, TCHAR *argv[20], TCHAR *pCmdLine)
{
	TCHAR		*pEnd;
	int			argc = 0;

	// Insert the program name as argc 1
	argv[argc++] = pProgName;

	while (*pCmdLine != TEXT('\0')) {
		// Skip to first whitespace.
		while (_istspace (*pCmdLine)) {
			pCmdLine++;
		}

		// Break at EOL
		if (*pCmdLine == TEXT('\0')) {
			break;
		}

		// Check for '' or "" in the future....
		
		// Find the end.
		for (pEnd = pCmdLine; !_istspace(*pEnd) && (*pEnd != TEXT('\0'));) {
			pEnd++;
		}

		if (*pEnd != TEXT('\0')) {
			*pEnd = TEXT('\0');
			pEnd++;
		}
		
		argv[argc] = pCmdLine;

		argc++;
		pCmdLine = pEnd;
	}
	return argc;
}

void Output(const TCHAR *pwszFormat,...)
{
    TCHAR wszBuf[1024];
    va_list args;

    va_start(args, pwszFormat);
    wvsprintf(wszBuf, pwszFormat, args);
    va_end(args);

    OutputDebugString(wszBuf);
}

VOID Usage()
{
    Output(TEXT("usage: testrun  [-c ClientName] [-u UserName] [-g GroupName] \r\n"));
    //ExitProcess(1);
}

BOOL FAR PASCAL EnumAppCallback(LPCDPLAPPINFO lpAppInfo, LPVOID lpContext, DWORD dwFlags)
{
	OutputDebugString(TEXT("##### EnumAppCallback: Start #####\n"));
    if (lpContext == NULL)
    {
        Output(TEXT("	'%s'\r\n"), lpAppInfo->lpszAppName);
        return TRUE;
    }
    else
    {
        TCHAR *szGame;

        szGame = (TCHAR *) lpContext;
#ifdef UNICODE
        if (!lstrcmpi(szGame, lpAppInfo->lpszAppName))
#else
        if (!lstrcmpi(szGame, lpAppInfo->lpszAppNameA))
#endif
        {
            guidGame = lpAppInfo->guidApplication;
            return FALSE;
        }
        else
        {
            return TRUE;
        }
    }
}

HRESULT StartApplication(LPDIRECTPLAYLOBBY2 lpLobby, LPDPLCONNECTION lpConnection)
{
    HANDLE hEvent;
    HRESULT hr;
    PBYTE pBuffer = NULL;
    DWORD dwAppId, dwBufferSize;

	OutputDebugString(TEXT("##### StartApplication: Start #####\n")); 
	pBuffer = (PBYTE) LocalAlloc(LMEM_FIXED, 100);
    dwBufferSize = 100;
    ASSERT(pBuffer);

    hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (hEvent == NULL)
    {
        return E_FAIL;
    }
	OutputDebugString(TEXT("##### StartApplication: CreateEvent Finished \n")); 

    hr = lpLobby->RunApplication(0, &dwAppId, lpConnection, hEvent);
    if (FAILED(hr))
    {
        ErrorDsp(TEXT("RunApplication failed: %s \n"), hr);
        goto out;
    }
	OutputDebugString(TEXT("##### StartApplication: RunApplication Finished \n")); 

    while (1)
    {
        LPDPLMSG_GENERIC lpMsg;
        DWORD dwMessageFlags, dwSize;

        WaitForSingleObject(hEvent, INFINITE);

        dwSize = dwBufferSize;
        hr = lpLobby->ReceiveLobbyMessage(0, dwAppId, &dwMessageFlags, pBuffer, &dwSize);
        while (hr != DPERR_NOMESSAGES)
        {
            if (SUCCEEDED(hr))
            {
                lpMsg = (LPDPLMSG_GENERIC) pBuffer;
                switch(lpMsg->dwType)
                {
                case DPLSYS_CONNECTIONSETTINGSREAD:
                    Output(TEXT("Game read the connection settings\r\n"));
                    goto out;
                    break;
                case DPLSYS_DPLAYCONNECTFAILED:
                    Output(TEXT("Game failed to connect to session\r\n"));
                    goto out;
                    break;
                case DPLSYS_DPLAYCONNECTSUCCEEDED:
                    Output(TEXT("Game connected to session\r\n"));
                    goto out;
                    break;
                case DPLSYS_APPTERMINATED:
                    Output(TEXT("Game terminated\r\n"));
                    goto out;
                    break;
                default:
                    Output(TEXT("Lobby message %d received\r\n"),lpMsg->dwType);
                }
            }
            else if (hr == DPERR_BUFFERTOOSMALL)
            {
                pBuffer = (PBYTE) LocalReAlloc(pBuffer, dwSize, LMEM_MOVEABLE);
                ASSERT(pBuffer);
                dwBufferSize = dwSize;
            }
            else if (FAILED(hr))
            {
                goto out;
            }
        }
    }

  out:
    if (pBuffer)
    {
        LocalFree(pBuffer);
    }

    CloseHandle(hEvent);
    return hr;
}


/***********************************************/
/*    Lobby API object init
/***********************************************/
HRESULT ConnectToLobby(void)
{
    DPCOMPOUNDADDRESSELEMENT AddressArray[1];
    LPDIRECTPLAYLOBBY lpDPL1;
    LPDIRECTPLAYLOBBY2 lpDPL = NULL;
    LPDIRECTPLAY lpDP;
    PBYTE pBuffer;
    GUID guidNull = GUID_NULL;
    DWORD dwSize;
    HRESULT hr;

	OutputDebugString(TEXT("##### ConnectToLobby: Start #####\n"));
	//====================================
	// Get DirectPlay Interface
	//====================================
    hr = DirectPlayCreate(&guidNull, &lpDP, NULL);
    if (FAILED(hr))
    {
		Output(TEXT("ConnectToLobby: DirectPlayCreate Failed Start %x \n"),hr);
        return hr;
    }

#ifdef UNICODE
    hr = lpDP->QueryInterface(IID_IDirectPlay3, (LPVOID *) &g_lpDP);
#else
    hr = lpDP->QueryInterface(IID_IDirectPlay3A, (LPVOID *) &g_lpDP);
#endif
    lpDP->Release();
    if (FAILED(hr))
    {
		Output(TEXT("ConnectToLobby:ConnectToLobby: QueryInterface Failed %x \n"),hr);
        return hr;
    }

	//====================================
	//  Get DirectPlayLobby Interface
	//====================================
    Output(TEXT("ConnectToLobby: DirectPlayLobbyCreate Start\n"));
    hr = DirectPlayLobbyCreate(NULL, &lpDPL1, NULL, NULL, 0);
    if (FAILED(hr))
    {
        Output(TEXT("ConnectToLobby:DirectPlayLobbyCreate failed: %x\r\n"), hr);
        return hr;
    }

#ifdef UNICODE
    hr = lpDPL1->QueryInterface(IID_IDirectPlayLobby2, (LPVOID *) &lpDPL);
#else
    hr = lpDPL1->QueryInterface(IID_IDirectPlayLobby2A, (LPVOID *) &lpDPL);
#endif
    lpDPL1->Release();
    if (FAILED(hr))
    {
        Output(TEXT("ConnectToLobby:Couldn't get Lobby2 interface: %x\r\n"), hr);
        return hr;
    }

	//====================================
	// Create DirectPlay address
	//====================================
#if 1
    AddressArray[0].guidDataType = DPAID_LobbyProvider;
    AddressArray[0].dwDataSize = sizeof(GUID);
    AddressArray[0].lpData = (LPVOID) &GUID_LobbyProvider;
    hr = lpDPL->CreateCompoundAddress( AddressArray, 1, NULL, &dwSize );
#else
    hr = lpDPL->CreateAddress( GUID_LobbyProvider, DPAID_LobbyProvider, NULL, 0, NULL, &dwSize);
#endif
    if (hr != DPERR_BUFFERTOOSMALL)
    {
        Output(TEXT("ConnectToLobby:Unable to create address1: %x\r\n"), hr);
        goto out;
    }
    Output(TEXT("CreateAddress1 SUCCESS get size=%d\n"),dwSize);

    pBuffer = (PBYTE) LocalAlloc(LMEM_FIXED, dwSize);
    if (pBuffer == NULL)
    {
        Output(TEXT("ConnectToLobby:Unable to create address2: %x\r\n"), hr);
        goto out;
    }

	// Get DirectPlay address
#if 1
    hr = lpDPL->CreateCompoundAddress( AddressArray, 1, pBuffer, &dwSize);
#else
    hr = lpDPL->CreateAddress(GUID_LobbyProvider, DPAID_LobbyProvider, NULL, 0, pBuffer, &dwSize);

#endif
    if (FAILED(hr))
    {
        Output(TEXT("ConnectToLobby:Unable to create address3: %x\r\n"), hr);
        goto out;
    }
    Output(TEXT("CreateAddress2 SUCCESS \n"));
    Output(TEXT("pBuffer =0x%X%X%X%X%X%X%X%X%X%X%X%X%X%X%X%X%X%X%X%X\n"),
		*pBuffer,*(pBuffer+1),
		*(pBuffer+2),*(pBuffer+3),
		*(pBuffer+4),*(pBuffer+5),
		*(pBuffer+6),*(pBuffer+7),
		*(pBuffer+8),*(pBuffer+9),
		*(pBuffer+10),*(pBuffer+11),
		*(pBuffer+12),*(pBuffer+13),
		*(pBuffer+14),*(pBuffer+15),
		*(pBuffer+16),*(pBuffer+17),
		*(pBuffer+18),*(pBuffer+19));

	//====================================
	// Init DirectPlay connection
	//====================================
    hr = g_lpDP->InitializeConnection(pBuffer, 0);
    if (FAILED(hr))
    {
		Sleep(5000);
        Output(TEXT("\nUnable to initialize connection: %x\r\n"), hr);
		ErrorDsp(TEXT("???? ConnectToLobby: InitializeConnection Error %s \n"),hr);
    }

  out:
    if (lpDPL)
    {
        lpDPL->Release();
    }

	OutputDebugString(TEXT("##### ConnectToLobby: End #####\n"));

    return hr;
}


/****************************************************************/
/*    Connect to Lobby server and Disconnect from lobby server  */
/****************************************************************/
int StartConnectViaLobbyServer(HINSTANCE hInstance, LPTSTR szUser)
{
    HRESULT hr;
    int result = 1;
    int g_Ras = 0;

    OutputDebugString(TEXT("##### StartGameViaLobbyServer: Start #####\n"));
    g_hInstApp = hInstance;

#if USERAS
    /********************************/
    /* Connect RAS server           */
    /********************************/
    hr = ConnectToRas();
    if (FAILED(hr))
    {
		OutputDebugString(TEXT("????? StartGameViaLobbyServer: ConnectToRas Error\n"));
        goto out;
    }
    g_Ras = 1;
#endif

    /********************************/
    /* Create lobby object          */
    /********************************/
    OutputDebugString(TEXT("StartGameViaLobbyServer: ConnectToLobby Start\n"));
    hr = ConnectToLobby();
    if (FAILED(hr))
    {
		OutputDebugString(TEXT("????? StartGameViaLobbyServer: ConnectToLobby Error\n"));
        goto out;
    }

    /********************************/
    /* Connect to lobby server      */
    /********************************/
    OutputDebugString(TEXT("StartGameViaLobbyServer: TestLobbyServer Start\n"));
    hr = TestLobbyServer();
    if (hr != TRUE)
    {
		OutputDebugString(TEXT("????? StartGameViaLobbyServer: TestLobbyServer Error\n"));
        goto out;
    }

  out:
    if (g_lpDP)
    {
        g_lpDP->Release();
    }

#if USERAS
    if (g_Ras)
    {
		DisconnectToRas();
    }
#endif

    if (FAILED(hr))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}



//===============================================
//	Connect to external lobby server
//===============================================
HRESULT TestLobbyServer(void)
{
    static DPSESSIONDESC2 sessionDesc;
    static TCHAR	tcServerIP[] = {TEXT(SERVER_IP)};		
    static char	ServerIP[] = {SERVER_IP};
	static LPCTSTR	lpServerIP = (LPCTSTR)ServerIP;
    CDPName dpnPlayer;
    CDPName dpnGroup;
	HRESULT	hr;
	TCHAR	tcDebugData[40];
	static TCHAR	tcClientName[32];
	char	cUserName[32];
	char	cClientName[32];
	char	cGroupName[32];
	char	cUserData[20];
	char	cPassword[8];
	DWORD		dwSize;
	LPDPNAME	 lpPlayerName;
	LPDPNAME	 lpGroupName;
	LPLSP_PLAYERDATA lpPlayerData;
	LPLSP_GROUPDATA lpGroupData;
	int		i,iCnt;

    Output(TEXT("##### TestLobbyServer: Start ##### \n"));

	//==============================
	// Init session area
	//==============================
    g_lpGuid = (LPGUID) &TESTRUN_GUID;
	memset(&sessionDesc, 0, sizeof(sessionDesc));
    sessionDesc.dwSize = sizeof(DPSESSIONDESC2);
	sessionDesc.guidApplication = *g_lpGuid;
	memset(cPassword,NULL,sizeof(cPassword));
	sessionDesc.dwMaxPlayers = 0;

	//==============================
	// Create Player Get Event
	//==============================
    g_hReceiveEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
    if (g_hReceiveEvent == NULL)
    {
		Output(TEXT("???? TestLobbyServer: CreateEvent Error %x\n"),hr);
		return FALSE;
    }

	//==============================
	// Start receive thread
	//==============================
    hr = StartReceiveThread();
    if (FAILED(hr))
    {
		Output(TEXT("???? TestLobbyServer: StartReceiveThread Error %x\n"),hr);
        return FALSE;
    }


	//==============================
	// DPlay Open()API
	//==============================
    Output(TEXT("//==========================\n")
		   TEXT("// OPEN START\n")
           TEXT("//==========================\n"));
    memset(tcDebugData, 0, sizeof(tcDebugData));
	mbstowcs(tcDebugData,(char *)LSP_REG_SERVERIP,strlen((char *)LSP_REG_SERVERIP));
    Output(TEXT("TestLobbyServer: Open Start size = %d IP=%s \n"), sessionDesc.dwSize,tcDebugData);
//		sessionDesc.lpszSessionName = (LPWSTR)lpServerIP;
    hr = g_lpDP->Open(&sessionDesc, DPOPEN_CREATE);
    if (FAILED(hr))
    {
		ErrorDsp(TEXT("???? TestLobbyServer: Open Error %s \n"),hr);
        return FALSE;
    }

    //=======================
	//  Create User on Lobby
	//=======================
	memset(&dpnPlayer, 0, sizeof(dpnPlayer));
	dpnPlayer.dwSize = sizeof(dpnPlayer);
	wcstombs(cUserName,szUser,32);			// convert to 2Byte code 
	wcstombs(cClientName,szClient,32);
	dpnPlayer.lpszShortNameA = cUserName;
	dpnPlayer.lpszLongNameA = cUserName;
//		dpnPlayer.lpszLongNameA = cClientName;
    Output(TEXT("//==========================\n")
		   TEXT("// CREATE USER START\n")
           TEXT("//==========================\n"));
    Output(TEXT("##### TestLobbyServer: CreatePlayer Start cName=%s pName=%s \n"), szClient, szUser);
    hr = g_lpDP->CreatePlayer(&g_idPlayer, &dpnPlayer, g_hReceiveEvent, NULL, 0, 0);
    if (FAILED(hr))
    {
		ErrorDsp(TEXT("???? TestLobbyServer: CreatePlayer Error %s\n"),hr);
        return FALSE;
    }
    Output(TEXT("!!!!! TestLobbyServer: CreatePlayer SUCCESS pID=0x%X \n"), g_idPlayer);

    //=======================
	//  Create Group
	//=======================
	memset(&dpnGroup, 0, sizeof(dpnGroup));
	dpnGroup.dwSize = sizeof(dpnGroup);
	wcstombs(cGroupName,szGroup,32);
	dpnGroup.lpszShortNameA = cGroupName;
	dpnGroup.lpszLongNameA = cGroupName;
    Output(TEXT("//==========================\n")
		   TEXT("// CreateGroup START\n")
           TEXT("//==========================\n"));
    Output(TEXT("TestLobbyServer: CreateGroup Start gName=%s \n"), szGroup);
    hr = g_lpDP->CreateGroup(&g_idGroup, &dpnGroup, NULL, 0, 0); 
    if (FAILED(hr))
    {
		ErrorDsp(TEXT("???? TestLobbyServer: CreateGroup Error %s\n"),hr);
    }
	else
	{
		Output(TEXT("!!!!! TestLobbyServer: CreateGroup Success groupID=0x%X \n"), g_idGroup);
	}
    
	//=======================
	//  Get group list
	//=======================
    Output(TEXT("//==========================\n")
		   TEXT("// EnumGroups1 START\n")
           TEXT("//==========================\n"));
    Output(TEXT("TestLobbyServer: EnumGroup Start \n"));
    hr = g_lpDP->EnumGroups(NULL,(LPDPENUMPLAYERSCALLBACK2)EnumGroupsCallback, (LPVOID)"GROUP LIST CALL BACK(NULL=DEFAULT)", NULL);
    if (FAILED(hr))
    {
		ErrorDsp(TEXT("???? TestLobbyServer: EnumGroup Error %s \n"),hr);
    }
	else
	{
		Output(TEXT("TestLobbyServer: EnumGroup Success \n"));
	}

	//=======================
	//  Get Player name
	//=======================
    Output(TEXT("//==========================\n")
		   TEXT("// GetPlayerName START\n")
           TEXT("//==========================\n"));
    Output(TEXT("TestLobbyServer: GetPlayerName Start PID=0x%X\n"),g_idPlayer);
    hr = g_lpDP->GetPlayerName(g_idPlayer, NULL, (LPDWORD)&dwSize);
	if (hr != DPERR_BUFFERTOOSMALL)
    {
		ErrorDsp(TEXT("????? TestLobbyServer: GetPlayerName ERROR %s \n"),hr);
    }
	else
	{
		Output(TEXT("!!!!!! TestLobbyServer: GetPlayerName Get Size SUCCESS size=%d \n"), dwSize);
		lpPlayerName = (LPDPNAME)LocalAlloc(LMEM_FIXED,dwSize);
		if (lpPlayerName != NULL)
		{
	        hr = g_lpDP->GetPlayerName(g_idPlayer, (LPVOID)lpPlayerName, (LPDWORD)&dwSize); 
			if (FAILED(hr))
			{
				ErrorDsp(TEXT("???? TestLobbyServer: GetPlayerName ERROR %s \n"),hr);
			}
			else
			{
				Output(TEXT("!!!!!! TestLobbyServer: GetPlayerName SUCCESS size=%d \n"),dwSize);
				memset(&tcDebugData, 0, sizeof(tcDebugData));
				mbstowcs(tcDebugData,lpPlayerName->lpszLongNameA,strlen(lpPlayerName->lpszLongNameA));
				Output(TEXT("TestLobbyServer: GetPlayerName lpPlayerName->lpszLongNameA=%s \n"), tcDebugData);
				memset(&tcDebugData, 0, sizeof(tcDebugData));
				mbstowcs(tcDebugData,lpPlayerName->lpszShortNameA,strlen(lpPlayerName->lpszShortNameA));
				Output(TEXT("TestLobbyServer: GetPlayerName lpPlayerName->lpszShortNameA=%s \n"), tcDebugData);
			}
			LocalFree((LPVOID)lpPlayerName);
		}
	}

    //=======================
	//  Get group name
	//=======================
    Output(TEXT("//==========================\n")
		   TEXT("// GetGroupName START\n")
           TEXT("//==========================\n"));
    Output(TEXT("TestLobbyServer: GetGroupName Start GID=0x%X\n"),g_idGroup);
	hr = g_lpDP->GetGroupName(g_idGroup, NULL, (LPDWORD)&dwSize); 
	if (hr != DPERR_BUFFERTOOSMALL)
	{
		ErrorDsp(TEXT("????? TestLobbyServer: GetGroupName ERROR %s \n"),hr);
    }
	else
	{
		Output(TEXT("!!!!!! TestLobbyServer: GetGroupName Get Size SUCCESS size=%d \n"),dwSize);
		lpGroupName = (LPDPNAME)LocalAlloc(LMEM_FIXED,dwSize);
		if (lpGroupName != NULL)
		{
	        hr = g_lpDP->GetGroupName(g_idGroup,(LPDPNAME)lpGroupName, (LPDWORD)&dwSize);
			if (FAILED(hr))
			{
				ErrorDsp(TEXT("???? TestLobbyServer: GetGroupName ERROR %s \n"),hr);
			}
			else
			{
				Output(TEXT("!!!!!! TestLobbyServer: GetGroupName SUCCESS size=%d \n"),dwSize);
				memset(&tcDebugData, 0, sizeof(tcDebugData));
				mbstowcs(tcDebugData,lpGroupName->lpszLongNameA,strlen(lpGroupName->lpszLongNameA));
				Output(TEXT("TestLobbyServer: GetGroupName lpGroupName->lpszLongNameA=%s \n"),tcDebugData);
				memset(&tcDebugData, 0, sizeof(tcDebugData));
				mbstowcs(tcDebugData,lpGroupName->lpszShortNameA,strlen(lpGroupName->lpszShortNameA));
				Output(TEXT("TestLobbyServer: GetGroupName lpGroupName->lpszShortNameA=%s \n"),tcDebugData);
			}
			LocalFree((LPVOID)lpGroupName);
		}
	}

	//=======================
	//  Set game data 
	//=======================
	memset(cUserData,NULL,sizeof(cUserData));
	memcpy(cUserData,(char *)"USER FIX DATA",sizeof("USER FIX DATA"));
    memset(tcDebugData, 0, sizeof(tcDebugData));
	mbstowcs(tcDebugData,(char *)cUserData,strlen((char *)cUserData));

    Output(TEXT("//==========================\n")
		   TEXT("// SetPlayerData START\n")
           TEXT("//==========================\n"));
    Output(TEXT("TestLobbyServer: SetPlayerData Start uData=%s \n"),tcDebugData);
    hr = g_lpDP->SetPlayerData(g_idPlayer,(LPVOID)cUserData, (DWORD)strlen(cUserData),(DWORD)NULL);
    if (FAILED(hr))
	{
		ErrorDsp(TEXT("???? TestLobbyServer: SetPlayerData Error %s\n"),hr);
	}
	else
	{
		Output(TEXT("!!!!! TestLobbyServer: SetPlayerData Success \n"));
	}

	//===============================================================
	//  Get all player list from lobby server
	//===============================================================
    Output(TEXT("//==========================\n")
		   TEXT("// GetPlayerData START\n")
           TEXT("//==========================\n"));
    Output(TEXT("###### TestLobbyServer: GetPlayerData Start PID=0x%X ######\n"),g_idPlayer);
	hr = g_lpDP->GetPlayerData(g_idPlayer,NULL,(LPDWORD)&dwSize, 0);
    Output(TEXT("############### TestLobbyServer: GetPlayerData Finished ######### \n"));
	if (hr != DPERR_BUFFERTOOSMALL)
    {
        ErrorDsp(TEXT("????? TestLobbyServer: GetPlayerData ERROR %s \n"),hr);
    }
	else
	{
		Output(TEXT("!!!!!! TestLobbyServer: GetPlayerData Get Size SUCCESS size=%d \n"),dwSize);
		lpPlayerData = (LPLSP_PLAYERDATA)LocalAlloc(LMEM_FIXED,dwSize);
		if (lpPlayerData != NULL)
		{
	        hr = g_lpDP->GetPlayerData(g_idPlayer,(LPVOID)lpPlayerData,(LPDWORD)&dwSize, 0);
			if (FAILED(hr))
			{
				ErrorDsp(TEXT("???? TestLobbyServer: GetPlayerData ERROR %s \n"),hr);
			}
			else
			{
				Output(TEXT("!!!!!! TestLobbyServer: GetPlayerData SUCCESS size=%d \n"),dwSize);
				iCnt = lpPlayerData->dwPlayerCount;
				Output(TEXT("TestLobbyServer: GetPlayerData Get PlayerCnt = %d ID=0x%X \n"),
				iCnt,lpPlayerData->dwPlayerID);
				for (i = 0; i < iCnt ; i++)
				{
					memset(tcDebugData,NULL,sizeof(tcDebugData));
					mbstowcs(tcDebugData,(char *)lpPlayerData->useritem[i].USI_cUserName,strlen((char *)lpPlayerData->useritem[i].USI_cUserName));
					Output(TEXT("TestLobbyServer: GetPlayerData Get Player[%d] ID=0x%X name=%s \n"),i,lpPlayerData->useritem[i].USI_wUserID,tcDebugData);
					memset(tcDebugData,NULL,sizeof(tcDebugData));
					mbstowcs(tcDebugData,(char *)lpPlayerData->useritem[i].USI_cUserArea,strlen((char *)lpPlayerData->useritem[i].USI_cUserArea));
					Output(TEXT("TestLobbyServer: GetPlayerData UserData = %s \n"),tcDebugData);
				}
			}
			LocalFree(lpPlayerData);
		}
	}

	//==========================================
	//  Get all group list from lobby server
	//==========================================
    Output(TEXT("//==========================\n")
	TEXT("// GetGroupData START\n")
    TEXT("//==========================\n"));
    Output(TEXT("###### TestLobbyServer: GetGroupData Start PID=0x%X ######\n"),g_idGroup);
    hr = g_lpDP->GetGroupData(g_idGroup,NULL,(LPDWORD)&dwSize, 0);
	if (hr != DPERR_BUFFERTOOSMALL)
    {
		ErrorDsp(TEXT("????? TestLobbyServer: GetGroupData1 ERROR %s \n"),hr);
    }
	else
	{
		Output(TEXT("!!!!!! TestLobbyServer: GetGroupData1 Get Size SUCCESS size=%d \n"),dwSize);
		lpGroupData = (LPLSP_GROUPDATA)LocalAlloc(LMEM_FIXED,dwSize);
		if (lpGroupData != NULL)
		{
			hr = g_lpDP->GetGroupData(g_idGroup,(LPVOID)lpGroupData,(LPDWORD)&dwSize, 0);
			if (FAILED(hr))
			{
				ErrorDsp(TEXT("???? TestLobbyServer: GetGroupData1 ERROR %s \n"),hr);
			}
			else
			{
				int		i,iCnt;
				Output(TEXT("!!!!!! TestLobbyServer: GetGroupData1 SUCCESS size=%d \n"),dwSize);
				iCnt = lpGroupData->dwGroupCount;
				Output(TEXT("TestLobbyServer: GetGroupData1 Get GroupCnt = %d ID=0x%X \n"),iCnt,lpGroupData->dwGroupID);
				for (i = 0; i < iCnt ; i++)
				{
					memset(tcDebugData,NULL,sizeof(tcDebugData));
					mbstowcs(tcDebugData,(char *)lpGroupData->groupitem[i].GPI_cGroupName,strlen((char *)lpGroupData->groupitem[i].GPI_cGroupName));
					Output(TEXT("TestLobbyServer: GetGroupData1 Get Group[%d] ID=0x%X name=%s \n"),i,lpGroupData->groupitem[i].GPI_wGroupID,tcDebugData);
				}
			}
			LocalFree(lpGroupData);
		}
	}

	//===============================
	//  Add player to group
	//===============================
    Output(TEXT("//==========================\n")
		   TEXT("// AddPlayerToGroup START\n")
           TEXT("//==========================\n"));
    Output(TEXT("TestLobbyServer: AddPlayerToGroup Start gId=0x%X pId=0x%X \n"),g_idGroup,g_idPlayer);
	hr = g_lpDP->AddPlayerToGroup(g_idGroup,g_idPlayer);
    if (FAILED(hr))
    {
		ErrorDsp(TEXT("???? TestLobbyServer: AddPlayerToGroup Error %s \n"),hr);
    }
	else
	{
		Output(TEXT("TestLobbyServer: AddPlayerToGroup Success groupID=0x%X \n"),g_idGroup);
	}


	//=======================
	//  Get group list
	//=======================
    Output(TEXT("//==========================\n")
		   TEXT("// EnumGroups1(NULL=DEFAULT) START\n")
           TEXT("//==========================\n"));
    Output(TEXT("TestLobbyServer: EnumGroup Start \n"));
    hr = g_lpDP->EnumGroups(NULL,(LPDPENUMPLAYERSCALLBACK2)EnumGroupsCallback,(LPVOID)"GROUP LIST CALL BACK(NULL=DEFAULT)",NULL);
    if (FAILED(hr))
    {
		ErrorDsp(TEXT("???? TestLobbyServer: EnumGroup Error %s \n"),hr);
    }
	else
	{
		Output(TEXT("TestLobbyServer: EnumGroup Success \n"));
	}

	//==================================
	//  Get player list in group
	//==================================
    Output(TEXT("//==========================\n")
		   TEXT("//  EnumGroupPlayers START\n")
           TEXT("//==========================\n"));
    Output(TEXT("TestLobbyServer:  EnumGroupPlayers gID=0x%X \n"),g_idGroup);
    hr = g_lpDP->EnumGroupPlayers(g_idGroup,NULL,(LPDPENUMPLAYERSCALLBACK2)EnumPlayersCallback2,(LPVOID)"PLAYERSINGROUP LIST CALL BACK",NULL);
    if (FAILED(hr))
    {
		ErrorDsp(TEXT("???? TestLobbyServer: EnumGroupPlayers Error %s \n"),hr);
    }
	else
	{
		Output(TEXT("TestLobbyServer: EnumGroupPlayers Success \n"));
	}

	//=================================
	//  Delete player from group
	//=================================
    Output(TEXT("//==========================\n")
		   TEXT("// DeletePlayerFromGroup START\n")
           TEXT("//==========================\n"));
    Output(TEXT("TestLobbyServer: DeletePlayerFromGroup Start gId=0x%X pId=0x%X \n"),g_idGroup,g_idPlayer);
	hr = g_lpDP->DeletePlayerFromGroup(g_idGroup,g_idPlayer);
    if (FAILED(hr))
    {
		ErrorDsp(TEXT("???? TestLobbyServer: DeletePlayerFromGroup Error %s\n"),hr);
    }
	else
	{
		Output(TEXT("TestLobbyServer: DeletePlayerFromGroup Success groupID=0x%X \n"),(int)g_idGroup);
	}
    
	//=======================
	//  Delete group
	//=======================
    Output(TEXT("//==========================\n")
		   TEXT("// DestroyGroup START\n")
           TEXT("//==========================\n"));
    Output(TEXT("CHECK Group INFO TestLobbyServer: DestroyGroup Start gId=0x%X \n"),g_idGroup);
    hr = g_lpDP->DestroyGroup(g_idGroup);
    if (FAILED(hr))
    {
		ErrorDsp(TEXT("???? TestLobbyServer: DestroyGroup Error %s\n"),hr);
    }
	else
	{
		Output(TEXT("TestLobbyServer: DestroyGroup Success groupID=0x%X \n"),(int)g_idGroup);
	}

	//=======================
	//  Delete player
	//=======================
    Output(TEXT("//==========================\n")
		   TEXT("// DestroyPlayer START\n")
           TEXT("//==========================\n"));
	Output(TEXT(" TestLobbyServer: DestroyPlayer Start playerID=0x%X \n"),g_idPlayer);
    hr = g_lpDP->DestroyPlayer(g_idPlayer);
    if (FAILED(hr))
    {
		ErrorDsp(TEXT("???? TestLobbyServer: DestroyPlayer1 Error %s\n"),hr);
    }
	else
	{
		Output(TEXT("######## TestLobbyServer: DestroyPlayer1 Success playID=0x%X \n"),g_idPlayer);
	}

    //=======================
	//  DPlay API() Close
	//=======================
    Output(TEXT("//==========================\n")	
		   TEXT("// Close START\n")
           TEXT("//==========================\n"));
	Output(TEXT("TestLobbyServer: Close Start \n"));
    hr = g_lpDP->Close();
    if (FAILED(hr))
    {
		ErrorDsp(TEXT("???? TestLobbyServer: Close Error %s\n"),hr);
        return FALSE;
    }
	Output(TEXT("#### TestLobbyServer: Close SUCCESS !!!!\n"));
    return TRUE;
}



DWORD WINAPI ReceiveThreadStub(LPVOID lpContext)
{
	OutputDebugString(TEXT("##### ReceiveThreadStub Start #####\n")); 
    return ReceiveThread();
}

VOID KillReceiveThread(void)
{
    if (g_hReceiveThread)
    {
        g_bKillThread = TRUE;
        SetEvent(g_hReceiveEvent);
        Output(TEXT("Waiting for Receive thread to die\r\n"));
        WaitForSingleObject(g_hReceiveThread, INFINITE);
        Output(TEXT("Waiting for Receive thread to die: Done\r\n"));
    }
}

DWORD ReceiveThread(VOID)
{
    PBYTE pBuffer;
    DWORD dwBufferSize;

	OutputDebugString(TEXT("##### ReceiveThread Start #####\n")); 
    pBuffer = (PBYTE) LocalAlloc(LMEM_FIXED, 100);
    ASSERT(pBuffer);
    dwBufferSize = 100;

    for (;;)
    {
        HRESULT hr = S_OK;
        DWORD dwFrom, dwTo, dwSize, dwResult;

        Output(TEXT("sleeping on receive event\r\n"));
        dwResult = WaitForSingleObject(g_hReceiveEvent, INFINITE);
        ASSERT(dwResult == WAIT_OBJECT_0);

        Output(TEXT("waking on receive event\r\n"));

        if (g_bKillThread)
        {
            break;
        }

        dwFrom = DPID_SYSMSG;
        dwSize = dwBufferSize;
        hr = g_lpDP->Receive(&dwFrom, &dwTo, DPRECEIVE_FROMPLAYER,pBuffer, &dwSize);

        while (hr != DPERR_NOMESSAGES)
        {
            if (SUCCEEDED(hr))
            {
                Output(TEXT("HandleMSG\r\n"));
                if (((LPDPMSG_GENERIC) pBuffer)->dwType == DPSYS_STARTSESSION)
                {
                    HandleSysMessage(pBuffer, dwSize);
                    pBuffer = (PBYTE) LocalAlloc(LMEM_FIXED, dwBufferSize);
                    ASSERT(pBuffer);
                }
                else
                {
                    HandleSysMessage(pBuffer, dwSize);
                }
            }
            else if (hr == DPERR_BUFFERTOOSMALL)
            {
                Output(TEXT("Receive buffer too small, reallocating\r\n"));
                pBuffer = (PBYTE) LocalReAlloc(pBuffer, dwSize, LMEM_MOVEABLE);
                ASSERT(pBuffer);
                dwBufferSize = dwSize;
            }
            else if (FAILED(hr))
            {
                Output(TEXT("Receive *FAILED*: %x\r\n"), hr);
                goto out;
            }

            dwFrom = DPID_SYSMSG;
            dwSize = dwBufferSize;
            hr = g_lpDP->Receive(&dwFrom, &dwTo, DPRECEIVE_FROMPLAYER,pBuffer, &dwSize);

        }

        Output(TEXT("No more messages\r\n"));

    }
  out:
    if (pBuffer != NULL)
    {
        LocalFree(pBuffer);
    }
    return 0;
}

HRESULT StartReceiveThread(VOID)
{
    DWORD dwThreadId;

	OutputDebugString(TEXT("##### StartReceiveThread Start #####\n")); 
    g_hReceiveThread = CreateThread(NULL,0,ReceiveThreadStub,(LPVOID) StartReceiveThread,0,&dwThreadId);
    if (g_hReceiveThread == NULL)
    {
        return E_FAIL;
    }

    return S_OK;
}


VOID HandleSysMessage(PBYTE pBuffer, DWORD dwMessageSize)
{
    LPDPMSG_GENERIC lpMsg;
	TCHAR	tcDebugData[40];

	Output(TEXT("##### HandleSysMessage Start size=%d #####\n"),dwMessageSize); 
    if (dwMessageSize < sizeof(DPMSG_GENERIC))
    {
        return;
    }

    lpMsg = (LPDPMSG_GENERIC) pBuffer;
	MsgDsp(TEXT("-----> HandleSysMessage: Recieve Msg = %s \n"),lpMsg->dwType);
	if (lpMsg->dwType == DPSYS_CREATEPLAYERORGROUP)
	{

		LPDPMSG_CREATEPLAYERORGROUP lpGroupMsg;
		lpGroupMsg = (LPDPMSG_CREATEPLAYERORGROUP)lpMsg;
		if ((lpGroupMsg->dpnName.lpszLongNameA == NULL) ||
		    (lpGroupMsg->dpnName.lpszShortNameA == NULL))
		{
			Output(TEXT("DPMSG_CREATE_PLAYER NAME is NULL \n"));
			return;
		}


		memset(tcDebugData,NULL,sizeof(tcDebugData));
		mbstowcs(tcDebugData,lpGroupMsg->dpnName.lpszLongNameA,strlen(lpGroupMsg->dpnName.lpszLongNameA));
		if (lpGroupMsg->dwPlayerType == DPPLAYERTYPE_PLAYER)
		{
			Output(TEXT("DPMSG_CREATE_PLAYER PlayerType=0x%X dpId=0x%X dpName=%s \n"),lpGroupMsg->dwPlayerType,lpGroupMsg->dpId,tcDebugData);
			Output(TEXT("DPMSG_CREATE_PLAYER dpIdParent=0x%X dbFlags=0x%X \n"),lpGroupMsg->dpIdParent,lpGroupMsg->dwFlags);
		}
		else
		{
			Output(TEXT("DPMSG_CREATE_GROUP PlayerType=0x%X dpId=0x%X dpName=%s \n"),lpGroupMsg->dwPlayerType,lpGroupMsg->dpId,tcDebugData);
			Output(TEXT("DPMSG_CREATE_GROUP dpIdParent=0x%X dbFlags=0x%X \n"),lpGroupMsg->dpIdParent,lpGroupMsg->dwFlags);
		}
	}		
	Output(TEXT("##### HandleSysMessage Finished #####\n")); 
    return;
}

void	MsgDsp(TCHAR *tcMessage, DWORD dwMsgId)
{
	TCHAR	*lpMsg;
	lpMsg = MsgSet(dwMsgId);
	if (lpMsg == NULL)
	{
		Output(TEXT("-----> HandleSysMessage: Undefine Recieve MsgID = 0x%X \n"),dwMsgId);
	}
	else
	{
		Output(tcMessage,lpMsg);
	}
}

TCHAR	*MsgSet(DWORD	dwMsgId)
{
	switch (dwMsgId){
		case DPSET_REMOTE:					return TEXT("DPSET_REMOTE");
		case DPSET_LOCAL:					return TEXT("DPSET_LOCAL");
		case DPSET_GUARANTEED:				return TEXT("DPSET_GUARANTEED");
		case DPSYS_CREATEPLAYERORGROUP:   	return TEXT("DPSYS_CREATEPLAYERORGROUP");
		case DPSYS_DESTROYPLAYERORGROUP:    return TEXT("DPSYS_DESTROYPLAYERORGROUP");
		case DPSYS_ADDPLAYERTOGROUP:       	return TEXT("DPSYS_ADDPLAYERTOGROUP");
		case DPSYS_DELETEPLAYERFROMGROUP:  	return TEXT("DPSYS_DELETEPLAYERFROMGROUP");
		case DPSYS_SESSIONLOST:      		return TEXT("DPSYS_SESSIONLOST");
		case DPSYS_HOST:					return TEXT("DPSYS_HOST");
		case DPSYS_SETPLAYERORGROUPDATA:    return TEXT("DPSYS_SETPLAYERORGROUPDATA");
		case DPSYS_SETPLAYERORGROUPNAME:	return TEXT("DPSYS_SETPLAYERORGROUPNAME");
		case DPSYS_SETSESSIONDESC:          return TEXT("DPSYS_SETSESSIONDESC");
		case DPSYS_ADDGROUPTOGROUP:         return TEXT("DPSYS_ADDGROUPTOGROUP");
		case DPSYS_DELETEGROUPFROMGROUP:    return TEXT("DPSYS_DELETEGROUPFROMGROUP");
		case DPSYS_SECUREMESSAGE:           return TEXT("DPSYS_SECUREMESSAGE");
		case DPSYS_STARTSESSION:			return TEXT("DPSYS_STARTSESSION");
		case DPSYS_CHAT:					return TEXT("DPSYS_CHAT");
	}
	
	return NULL;

}

TCHAR	*ErrorSet(HRESULT	hr)
{
	switch (hr){
		case DP_OK:						    return TEXT("DP_OK");		
		case DPERR_ALREADYINITIALIZED:      return TEXT("DPERR_ALREADYINITIALIZED");
		case DPERR_ACCESSDENIED:            return TEXT("DPERR_ACCESSDENIED");
		case DPERR_ACTIVEPLAYERS:           return TEXT("DPERR_ACTIVEPLAYERS");
		case DPERR_BUFFERTOOSMALL:          return TEXT("DPERR_BUFFERTOOSMALL");
		case DPERR_CANTADDPLAYER:           return TEXT("DPERR_CANTADDPLAYER");
		case DPERR_CANTCREATEGROUP:         return TEXT("DPERR_CANTCREATEGROUP");
		case DPERR_CANTCREATEPLAYER:        return TEXT("DPERR_CANTCREATEPLAYER");
		case DPERR_CANTCREATESESSION:       return TEXT("DPERR_CANTCREATESESSION");
		case DPERR_CAPSNOTAVAILABLEYET:     return TEXT("DPERR_CAPSNOTAVAILABLEYET");
		case DPERR_EXCEPTION:               return TEXT("DPERR_EXCEPTION");
		case DPERR_GENERIC:                 return TEXT("DPERR_GENERIC");
		case DPERR_INVALIDFLAGS:            return TEXT("DPERR_INVALIDFLAGS");
		case DPERR_INVALIDOBJECT:           return TEXT("DPERR_INVALIDOBJECT");
		case DPERR_INVALIDPARAM:            return TEXT("DPERR_INVALIDPARAM");
		case DPERR_INVALIDPLAYER:           return TEXT("DPERR_INVALIDPLAYER");
		case DPERR_INVALIDGROUP:            return TEXT("DPERR_INVALIDGROUP");
		case DPERR_NOCAPS:                  return TEXT("DPERR_NOCAPS");
		case DPERR_NOCONNECTION:            return TEXT("DPERR_NOCONNECTION");
		case DPERR_NOMEMORY:                return TEXT("DPERR_NOMEMORY");
		case DPERR_NOMESSAGES:              return TEXT("DPERR_NOMESSAGES");
		case DPERR_NONAMESERVERFOUND:       return TEXT("DPERR_NONAMESERVERFOUND");
		case DPERR_NOPLAYERS:               return TEXT("DPERR_NOPLAYERS");
		case DPERR_NOSESSIONS:              return TEXT("DPERR_NOSESSIONS");
		case DPERR_SENDTOOBIG:			    return TEXT("DPERR_SENDTOOBIG");
		case DPERR_TIMEOUT:				    return TEXT("DPERR_TIMEOUT");
		case DPERR_UNAVAILABLE:			    return TEXT("DPERR_UNAVAILABLE");
		case DPERR_UNSUPPORTED:			    return TEXT("DPERR_UNSUPPORTED");
		case DPERR_BUSY:				    return TEXT("DPERR_BUSY");
		case DPERR_USERCANCEL:              return TEXT("DPERR_USERCANCEL");
		case DPERR_NOINTERFACE:             return TEXT("DPERR_NOINTERFACE");
		case DPERR_CANNOTCREATESERVER:      return TEXT("DPERR_CANNOTCREATESERVER");
		case DPERR_PLAYERLOST:              return TEXT("DPERR_PLAYERLOST");
		case DPERR_SESSIONLOST:             return TEXT("DPERR_SESSIONLOST");
		case DPERR_UNINITIALIZED:           return TEXT("DPERR_UNINITIALIZED");
		case DPERR_NONEWPLAYERS:            return TEXT("DPERR_NONEWPLAYERS");
		case DPERR_INVALIDPASSWORD:         return TEXT("DPERR_INVALIDPASSWORD");
		case DPERR_CONNECTING:              return TEXT("DPERR_CONNECTING");
		case DPERR_BUFFERTOOLARGE:          return TEXT("DPERR_BUFFERTOOLARGE");
		case DPERR_CANTCREATEPROCESS:       return TEXT("DPERR_CANTCREATEPROCESS");
		case DPERR_APPNOTSTARTED:           return TEXT("DPERR_APPNOTSTARTED");
		case DPERR_INVALIDINTERFACE:        return TEXT("DPERR_INVALIDINTERFACE");
		case DPERR_NOSERVICEPROVIDER:       return TEXT("DPERR_NOSERVICEPROVIDER");
		case DPERR_UNKNOWNAPPLICATION:      return TEXT("DPERR_UNKNOWNAPPLICATION");
		case DPERR_NOTLOBBIED:              return TEXT("DPERR_NOTLOBBIED");
		case DPERR_SERVICEPROVIDERLOADED:   return TEXT("DPERR_SERVICEPROVIDERLOADED");
		case DPERR_ALREADYREGISTERED:	    return TEXT("DPERR_ALREADYREGISTERED");
		case DPERR_NOTREGISTERED:		    return TEXT("DPERR_NOTREGISTERED");
		case DPERR_AUTHENTICATIONFAILED:    return TEXT("DPERR_AUTHENTICATIONFAILED");
		case DPERR_CANTLOADSSPI:            return TEXT("DPERR_CANTLOADSSPI");
		case DPERR_ENCRYPTIONFAILED:        return TEXT("DPERR_ENCRYPTIONFAILED");
		case DPERR_SIGNFAILED:				return TEXT("DPERR_SIGNFAILED");
		case DPERR_CANTLOADSECURITYPACKAGE:	return TEXT("DPERR_CANTLOADSECURITYPACKAGE");
		case DPERR_ENCRYPTIONNOTSUPPORTED:	return TEXT("DPERR_ENCRYPTIONNOTSUPPORTED");
		case DPERR_CANTLOADCAPI:			return TEXT("DPERR_CANTLOADCAPI");
		case DPERR_NOTLOGGEDIN:             return TEXT("DPERR_NOTLOGGEDIN");
		case DPERR_LOGONDENIED:             return TEXT("DPERR_LOGONDENIED");
	}
	return TEXT("undefine ERROR");
}

void	ErrorDsp(TCHAR *tcMessage, HRESULT	hr)
{
	Output(tcMessage,ErrorSet(hr));
}

bool	RegGetClientID( LPCHAR lpClientID )
{
	DWORD size = 8;
	unsigned char *p = (unsigned char *)lpClientID;
	FirmwareGetSerialNumber(p, &size);
	return TRUE;
}


BOOL FAR PASCAL	EnumPlayersCallback2( DPID dpId, DWORD dwPlayerType, LPCDPNAME lpName, DWORD dwFlags, LPVOID lpContext)
{

	TCHAR	tcDebugData[40];

	Output(TEXT("#### EnumPlayersCallback2 : Start #####\n"));
	Output(TEXT("EnumPlayersCallback2 : dpId= 0x%X \n"),dpId);
	Output(TEXT("EnumPlayersCallback2 : dwPlayerType= 0x%X \n"),dwPlayerType);
	Output(TEXT("EnumPlayersCallback2 : lpName->dwSize  = %d \n"),lpName->dwSize);
	memset(tcDebugData,NULL,sizeof(tcDebugData));
	mbstowcs(tcDebugData,lpName->lpszShortNameA,strlen(lpName->lpszShortNameA));
	Output(TEXT("EnumPlayersCallback2 : lpName->lpszShortNameA = %s \n"),tcDebugData);
	memset(tcDebugData,NULL,sizeof(tcDebugData));
	mbstowcs(tcDebugData,lpName->lpszLongNameA,strlen(lpName->lpszLongNameA));
	Output(TEXT("EnumPlayersCallback2 : lpName->lpszLongNameA = %s \n"),tcDebugData);
	memset(tcDebugData,NULL,sizeof(tcDebugData));
	mbstowcs(tcDebugData,(char *)lpContext,strlen((char *)lpContext));
	Output(TEXT("EnumPlayersCallback2 : lpContext = %s \n"),tcDebugData);
	return TRUE;

}

BOOL PASCAL EnumGroupsCallback(DPID dpId, DWORD dwPlayerType, LPCDPNAME lpName, DWORD dwFlags, LPVOID lpContext)
{
	TCHAR	tcDebugData[80];

	OutputDebugString(TEXT("##### EnumGroupsCallback Start #####\n")); 
	Output(TEXT("EnumGroupsCallback : dpId= 0x%X \n"),dpId);
	Output(TEXT("EnumGroupsCallback : dwPlayerType= 0x%X \n"),dwPlayerType);
	Output(TEXT("EnumGroupsCallback : lpName->dwSize  = %d \n"),lpName->dwSize);
	memset(tcDebugData,NULL,sizeof(tcDebugData));
	if ((lpName->lpszShortNameA == NULL) || (lpName->lpszLongNameA == NULL))
	{
		Output(TEXT("EnumGroupsCallback : lpName->lpszLongNameA = NULL\n"));
		return TRUE;
	}

	mbstowcs(tcDebugData,lpName->lpszShortNameA,strlen(lpName->lpszShortNameA));
	Output(TEXT("EnumGroupsCallback : lpName->lpszShortNameA = %s \n"),tcDebugData);
	memset(tcDebugData,NULL,sizeof(tcDebugData));
	mbstowcs(tcDebugData,lpName->lpszLongNameA,strlen(lpName->lpszLongNameA));
	Output(TEXT("EnumGroupsCallback : lpName->lpszLongNameA = %s \n"),tcDebugData);
	memset(tcDebugData,NULL,sizeof(tcDebugData));
	mbstowcs(tcDebugData,(char *)lpContext,strlen((char *)lpContext));
	Output(TEXT("EnumGroupsCallback : lpContext = %s \n"),tcDebugData);
    return TRUE;
}

BOOL PASCAL EnumSessionsCallback(LPCDPSESSIONDESC2 lpSData, LPDWORD lpdwTimeOut, DWORD dwFlag, LPVOID lpText)
{
	TCHAR	tcDebugData[80];

	OutputDebugString(TEXT("##### EnumSessionsCallback Start #####\n")); 
	Output(TEXT("EnumSessionsCallback : lpSData->dwSize  = %d flag=0x%X \n"),lpSData->dwSize,lpSData->dwFlags);
	memset(tcDebugData,NULL,sizeof(tcDebugData));
	mbstowcs(tcDebugData,lpSData->lpszSessionNameA,strlen(lpSData->lpszSessionNameA));
	Output(TEXT("EnumSessionsCallback : lpSData->lpszSessionNameA = %s \n"),tcDebugData);

	Output(TEXT("EnumSessionsCallback : lpSData->guidInstance = 0x%X \n"),lpSData->guidInstance);
	Output(TEXT("EnumSessionsCallback : lpSData->guidApplication = 0x%X \n"),lpSData->guidApplication);
	Output(TEXT("EnumSessionsCallback : lpSData->dwCurrentPlayers = %d \n"),lpSData->dwCurrentPlayers);
	Output(TEXT("EnumSessionsCallback : lpSData->dwMaxPlayers = %d \n"),lpSData->dwMaxPlayers);

	memset(tcDebugData,NULL,sizeof(tcDebugData));
	mbstowcs(tcDebugData,(char *)lpText,strlen((char *)lpText));
	Output(TEXT("EnumSessionsCallback : lpText = %s \n"),tcDebugData);
    return TRUE;
}

/*=========================*/
/*   Set Client name       */
/*=========================*/
BOOL	SetRegInformation(LPSTR lpClientName, LPSTR	lpSeverIP)
{
    LONG    lRtn=0;
	DWORD	dwRtn;
    HKEY    hKey;
    DWORD   dwDisposition;

    lRtn = RegCreateKeyEx( HKEY_LOCAL_MACHINE, LSP_REG_KEY_COM, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, &dwDisposition );    
    if( lRtn != ERROR_SUCCESS )
    {
		dwRtn = GetLastError( );
		Output(TEXT("SetRegInformation : RegCreateKeyEx Error %d key=%s\n"), dwRtn, LSP_REG_KEY_COM);
		return FALSE;
    }

    lRtn = RegSetValueEx( hKey, LSP_REG_CLIENT, 0, REG_SZ, (LPBYTE)lpClientName, strlen((const char *)lpClientName)+1 );
    if( lRtn != ERROR_SUCCESS )
    {
		dwRtn = GetLastError( );
		Output(TEXT("SetRegInformation : RegSetValueEx Error %d key=%s \n"), dwRtn, LSP_REG_CLIENT);
        RegCloseKey( hKey );
        return FALSE;
    }

    lRtn = RegSetValueEx( hKey, LSP_REG_SERVERIP, 0, REG_SZ, (LPBYTE)lpSeverIP, strlen((const char *)lpSeverIP)+1 );
    if( lRtn != ERROR_SUCCESS )
    {
		dwRtn = GetLastError( );
		Output(TEXT("SetRegInformation : RegSetValueEx Error %d key=%s \n"), dwRtn, LSP_REG_SERVERIP);
        RegCloseKey( hKey );
        return FALSE;
    }
    RegCloseKey( hKey );
	
	return TRUE;
}


/********************************/
/* Connect to RAS               */
/********************************/
HRESULT  ConnectToRas(void)
{
    DWORD ParmNum = 0;
    DWORD RetVal;
    RASDIALPARAMS RasDialParams;
    BOOL fNoWin = FALSE;

	BOOL	bOk;
    HKEY hKeyInfo;
    NetworkInfo NetInfo;
	LONG nError;
    DWORD cbInfoSize;
    DWORD dwType;

	OutputDebugString(TEXT("##### ConnectToRas: Start ##### \n"));
    bOk = FlashLoadNetworkInfo(NULL,sizeof(NetworkInfo),NULL);
    if (!bOk) 
	{
        Output(TEXT("???? ConnectToRas:FlashLoadNetworkInfo failed with error %d\n"),GetLastError());
		return FALSE;
    }

    nError = RegOpenKeyEx(HKEY_LOCAL_MACHINE,REG_KEY_NETWORK_INFO,0,KEY_READ,&hKeyInfo);
    if (nError != ERROR_SUCCESS) 
	{
        Output(TEXT("????? ConnectToRas: RegOpenKeyEx failed with error code %d\n"),nError);
        return FALSE;
    }

    cbInfoSize = sizeof(NetworkInfo);
    nError = RegQueryValueEx(hKeyInfo,REG_VAL_NETWORK_INFO,0,&dwType,(LPBYTE)&NetInfo,&cbInfoSize);
    if (nError == ERROR_SUCCESS) 
	{
        if (dwType == REG_BINARY && cbInfoSize == sizeof(NetworkInfo)) 
		{
            Output(TEXT("ConnectToRas:Sega Passport:\n"));
        } 
		else 
		{
            Output(TEXT("???? ConnectToRas:unknown passport format\n"));
        }
    } 
	else 
	{
        Output(TEXT("???? ConnectToRas:no valid passport found\n"));
    }


    RegCloseKey(hKeyInfo);

    memset((char *)&RasDialParams, 0, sizeof(RasDialParams));
    RasDialParams.dwSize = sizeof(RasDialParams);
    memcpy(RasDialParams.szEntryName,TEXT("ISP0"),sizeof(TEXT("ISP0")));
    mbstowcs(RasDialParams.szPhoneNumber,NetInfo.isp_info2.accessPointNumber[0],strlen(NetInfo.isp_info2.accessPointNumber[0]));
    mbstowcs(RasDialParams.szUserName,NetInfo.isp_info2.loginId,strlen(NetInfo.isp_info2.loginId));
    mbstowcs(RasDialParams.szPassword,NetInfo.isp_info2.loginPasswd,strlen(NetInfo.isp_info2.loginPasswd));
    Output(TEXT("ConnectToRas: RasDial2 TEL=%s\n"),RasDialParams.szPhoneNumber);
    Output(TEXT("ConnectToRas: RasDial2 User=%s\n"),RasDialParams.szUserName);
    Output(TEXT("ConnectToRas: RasDial2 PASS=%s\n"),RasDialParams.szPassword);

	memset(&hRasConn,NULL,sizeof(hRasConn));

	OutputDebugString(TEXT("ConnectToRas: RasDial Start \n"));
    RetVal = RasDial(NULL, NULL, &RasDialParams, 0xFFFFFFFF, NULL, &hRasConn);

    if (RetVal == 0) 
	{
		OutputDebugString(TEXT("!!!!! ConnectToRas: RasDial SUCCESS !!!!!!\n"));
        Output(TEXT("ConnectToRas RasDial successful, hRasConn = 0x%08X \n"), hRasConn);
    } 
	else 
	{
        Output(TEXT("????? ConnectToRas Error from RasDial=0x%X\n"), RetVal);
		if (RetVal == ERROR_NOT_ENOUGH_MEMORY)
		{
	        Output(TEXT("????? ConnectToRas Error from RasDial=ERROR_NOT_ENOUGH_MEMORY \n"));
		}
		else
		{
	        Output(TEXT("????? ConnectToRas Error from RasDial= NOT ERROR_NOT_ENOUGH_MEMORY \n"));
		}
        if (hRasConn != NULL)
		{
			RasHangUp(hRasConn);
			Output(TEXT("????? ConnectToRas : CALL RasHangUp\n"));
			return FALSE;

        }
    }
	OutputDebugString(TEXT("##### ConnectToRas : Finished\n"));
    return TRUE;
}

/********************************/
/* Disconnect from RAS          */
/********************************/
HRESULT	DisconnectToRas(void)
{
	DWORD dwRet;

	Output(TEXT("##### RasDisconnect : Start\n"));
	dwRet = RasHangUp(hRasConn);
	if (dwRet != 0)
	{
		Output(TEXT("????? RasDisconnect : RasHangUp Error\n"));
		return FALSE;
	}
	Output(TEXT("##### RasDisconnect : RasHangUp SUCCESS\n"));
	return TRUE;
}

/* end of file */



/* end of file */