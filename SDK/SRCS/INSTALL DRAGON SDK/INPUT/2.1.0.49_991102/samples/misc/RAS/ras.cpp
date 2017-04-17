/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    RAS.cpp

Abstract:

    RAS Application

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "RAS.hpp"

// ++++ Global Variables ++++++++++++++++++++++++++++++++++++++++++++
HWND      g_hwndApp;                                // HWND of the application
HINSTANCE g_hinst;                                  // HINSTANCE of the application
BOOL      g_fExit = FALSE;                          // TRUE when app should exist

// ++++ Enumerated Types ++++++++++++++++++++++++++++++++++++++++++++

// Commands that the user can specify
enum eCommand {ecmdConnect, ecmdListConnections, ecmdDisconnect, ecmdInvalid};

// ++++ Types +++++++++++++++++++++++++++++++++++++++++++++++++++++++

// Structure used to convert RAS status codes to their string representations
typedef struct _RAS_STATE_STR
{
    DWORD dwRasState;
    LPTSTR szState;
} RAS_STATE_STR, *PRAS_STATE_STRING;

// ++++ Local Variables +++++++++++++++++++++++++++++++++++++++++++++

TCHAR     g_tszAppName[] = TEXT("RAS");        // The App's Name

// Array of RAS status code --> String Representations.
RAS_STATE_STR g_rgrasstates[] =
{
    {RASCS_OpenPort,            TEXT("OpenPort")},
    {RASCS_PortOpened,          TEXT("PortOpened")},
    {RASCS_ConnectDevice,       TEXT("ConnectDevice")},
    {RASCS_DeviceConnected,     TEXT("DeviceConnected")},
    {RASCS_AllDevicesConnected, TEXT("AllDevicesConnected")},
    {RASCS_Authenticate,        TEXT("Authenticate")},
    {RASCS_AuthNotify,          TEXT("AuthNotify")},
    {RASCS_AuthRetry,           TEXT("AuthRetry")},
    {RASCS_AuthCallback,        TEXT("AuthCallback")},
    {RASCS_AuthChangePassword,  TEXT("AuthChangePassword")},
    {RASCS_AuthProject,         TEXT("AuthProject")},
    {RASCS_AuthLinkSpeed,       TEXT("AuthLinkSpeed")},
    {RASCS_AuthAck,             TEXT("AuthAck")},
    {RASCS_ReAuthenticate,      TEXT("ReAuthenticate")},
    {RASCS_Authenticated,       TEXT("Authenticated")},
    {RASCS_PrepareForCallback,  TEXT("PrepareForCallback")},
    {RASCS_WaitForModemReset,   TEXT("WaitForModemReset")},
    {RASCS_WaitForCallback,     TEXT("WaitForCallback")},
    {RASCS_Projected,           TEXT("Projected")},
    {RASCS_Interactive,         TEXT("Interactive")},
    {RASCS_RetryAuthentication, TEXT("RetryAuthentication")},
    {RASCS_CallbackSetByCaller, TEXT("CallbackSetByCaller")},
    {RASCS_PasswordExpired,     TEXT("PasswordExpired")},
    {RASCS_Connected,           TEXT("Connected")},
    {RASCS_Disconnected,        TEXT("Disconnected")},
    {(DWORD)-1,                 TEXT("Unknown RAS Connection State")}
};

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    GetStateStr

Description:

    Converts the passed-in RAS state code to it's string representation

Arguments:

    DWORD dwState       - State to convert to string representation
  
Return Value:

    String representation of 'dwState'

-------------------------------------------------------------------*/
LPTSTR
GetStateStr(DWORD dwState)
{
    DWORD i;

    for (i = 0; g_rgrasstates[i].dwRasState != (DWORD)-1; i++)
    {
        if (g_rgrasstates[i].dwRasState == dwState)
            break;
    }

    return g_rgrasstates[i].szState;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    WndProc

Description:

    Window message processing routine for the main application window.
    The main purpose of this function is to exit the app when the user
    presses <Escape> or <F12>.

Arguments:

    HWND hWnd           - Window handle

    UINT uMessage       - Message identifier
  
    WPARAM wParam       - First message parameter
    
    LPARAM lParam       - Second message parameter
  
Return Value:

    Zero if the message was processed.  The return value from 
    DefWindowProc otherwise.

-------------------------------------------------------------------*/
LRESULT CALLBACK
WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
    RASCONNSTATE RasState;

    switch (uMessage)
    {
    case WM_RASDIALEVENT:
        RasState = (RASCONNSTATE)wParam;

        switch (RasState)
        {
        case RASCS_AuthNotify:
            RetailOutput(TEXT("%s: Ecode=%d"), GetStateStr(RasState), lParam);
            switch (lParam) {
                case ERROR_RESTRICTED_LOGON_HOURS:
                    RetailOutput(TEXT("\tAUTH_ERR_REST_HOUR"));
                    break;

                case ERROR_ACCT_DISABLED:
                    RetailOutput(TEXT("\tAUTH_ERR_ACCT_DISABLED"));
                    break;

                case ERROR_PASSWD_EXPIRED:
                    RetailOutput(TEXT("\tAUTH_ERR_PWD_EXP"));
                    break;

                case ERROR_NO_DIALIN_PERMISSION:
                    RetailOutput(TEXT("\tAUTH_ERR_NO_DIALIN"));
                    break;

                case ERROR_CHANGING_PASSWORD:
                    RetailOutput(TEXT("\tAUTH_ERR_CHG_PWD"));
                    break;

                default:
                    RetailOutput(TEXT("\tAUTH_ERR_UNKNOWN"));
            }
            break;

        case RASCS_Connected:
            RetailOutput(TEXT("Connected"));
            g_fExit = TRUE;
            break;

        case RASCS_Disconnected:
            RetailOutput(TEXT("Disconnected: Ecode %d"), lParam);
            g_fExit = TRUE;
            break;

        default:
            RetailOutput(GetStateStr(RasState));
            break;
        }
        RetailOutput(TEXT("\n"));
        break;

    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
        case VK_F12:
            g_fExit = TRUE;
            return 0;
        } // switch (wParam)
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0L;

    } // switch (message)

    return DefWindowProc (hWnd, uMessage, wParam, lParam);
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    AppInit

Description:

    This function registers a window class, and creates a window for
    the application.

Arguments:

    hPrev               - Hinstance of another process running the program

    nCmdShow            - Whether the app should be shown (ignored)

Return Value:

    TRUE on success, FALSE on failure.

-------------------------------------------------------------------*/
BOOL 
AppInit(HINSTANCE hPrev, int nCmdShow)
{
    WNDCLASS cls;          

    if (!hPrev)
    {
        //  Register a class for the main application window
        cls.hCursor        = NULL;
        cls.hIcon          = NULL;
        cls.lpszMenuName   = NULL;
        cls.hbrBackground  = NULL;
        cls.hInstance      = g_hinst;
        cls.lpszClassName  = g_tszAppName;
        cls.lpfnWndProc    = (WNDPROC)WndProc;
        cls.style          = 0;
        cls.cbWndExtra     = 0;
        cls.cbClsExtra     = 0;

        if (!RegisterClass(&cls))
            return FALSE;
    }

    g_hwndApp = CreateWindowEx (0, g_tszAppName, g_tszAppName, WS_VISIBLE, 
                                0, 0, 640, 480, NULL, NULL, g_hinst, NULL);

    return TRUE;
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    OutputUsage

Description:

    Dumps usage information to the debugger

Arguments:

    None
    
Return Value:

    None

-------------------------------------------------------------------*/
void
OutputUsage()
{
    RetailOutput(TEXT("Usage:\r\n"));
    RetailOutput(TEXT("    s ras entryname [username [password]] [/DOMAIN:domain] [/DEBUG:num]\r\n"));
    RetailOutput(TEXT("    s ras [entryname] /DISCONNECT\r\n"));
    RetailOutput(TEXT("    s ras\r\n\r\n"));
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Function:

    ParseCommandLine

Description:

    Parses the command line, fills in the specified RASDIALPARAMS
    structure, and determines the command the user specified

Arguments:

    LPTSTR        pCmdLine        - Command line to parse

    RASDIALPARAMS *prasdialparams - Structure to fill.
    
Return Value:

    Command that the user specified

-------------------------------------------------------------------*/
eCommand
ParseCommandLine(LPTSTR pCmdLine, RASDIALPARAMS *prasdialparams)
{
    eCommand ecmd = ecmdListConnections;
    int nParmNum = 0;
    BOOL fPassword;
    int i;

    // Parse the command line
    while (*pCmdLine != TEXT('\0'))
    {
        // Skip leading whitespace
        while (*pCmdLine == TEXT(' '))
            pCmdLine++;

        if ((*pCmdLine == TEXT('-')) || (*pCmdLine == TEXT('/')))
        {
            // Done with EntryName/UserName/Password
            nParmNum = 3;
            pCmdLine++;
            if (!_tcsnicmp(pCmdLine, TEXT("Domain:"), 6))
            {
                // Copy the domain name over
                pCmdLine += 7;
                for (i = 0; *pCmdLine && (*pCmdLine != TEXT(' ')); i++)
                    prasdialparams->szDomain[i] = *pCmdLine++;
                prasdialparams->szDomain[i] = TEXT('\0');

            }
            else if (!_tcsnicmp(pCmdLine, TEXT("Disconnect"), 10))
            {
                ecmd = ecmdDisconnect;
                pCmdLine += 10;
            }
        }
        else if (nParmNum == 0)
        {
            ecmd = ecmdConnect;

            // Get the entryname
            if (*pCmdLine == TEXT('"'))
            {
                pCmdLine++;
                for (i = 0; (*pCmdLine != TEXT('\0')) && (*pCmdLine != TEXT('"')); i++)
                    prasdialparams->szEntryName[i] = *pCmdLine++;

                if (*pCmdLine == TEXT('"'))
                    pCmdLine++;
            }
            else
            {
                for (i = 0; (*pCmdLine != TEXT('\0')) && (*pCmdLine != TEXT(' ')); i++)
                    prasdialparams->szEntryName[i] = *pCmdLine++;
            }
            prasdialparams->szEntryName[i] = TEXT('\0');

            // Load the dial params for this entry
            RasGetEntryDialParams(NULL, prasdialparams, &fPassword);

            RetailOutput(TEXT("Opened RasEntry '%s', UserName='%s' PW='%s' Domain='%s'\n"),
                            prasdialparams->szEntryName, prasdialparams->szUserName,
                            prasdialparams->szPassword, prasdialparams->szDomain);
            // Prepare for UserName
            nParmNum = 1;
        }
        else if (nParmNum == 1)
        {
            for (i = 0; *pCmdLine && (*pCmdLine != TEXT(' ')) ; i++)
                prasdialparams->szUserName[i] = *pCmdLine++;
            prasdialparams->szUserName[i] = TEXT('\0');

            // Prepage for Password
            nParmNum = 2;
        }
        else if (nParmNum == 2)
        {
            for (i = 0; *pCmdLine && (*pCmdLine != TEXT(' ')); i++)
                prasdialparams->szPassword[i] = *pCmdLine++;
            prasdialparams->szPassword[i] = TEXT('\0');

            // All done with normal params
            nParmNum = 3;
        }
        else
        {
            RetailOutput(TEXT("Invalid cmdline '%s'\n"), pCmdLine);
            OutputUsage();
            return ecmdInvalid;
        }
    }

    return ecmd;
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

    We normally return the wParam value from the WM_QUIT message.  If
    there's a failure upon initialization, we just return 0.

-------------------------------------------------------------------*/
extern "C" int APIENTRY 
WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR pCmdLine, int nCmdShow)
{
    RASDIALPARAMS rasdialparams;
    RASCONN       *prasconn;
    HRASCONN      hRasConn;
    BYTE          byRasConnData[10 * sizeof(RASCONN)];
    DWORD         nDefaultEntries;
    RASENTRYNAME  *rgrasentrynames;
    RASCONNSTATUS rasconnstatus;
    eCommand      ecmd;
    DWORD         nConnections, nSize, nEntries;
    MSG           msg;
    DWORD         i;

    memset(&rasdialparams, 0, sizeof(rasdialparams));
    rasdialparams.dwSize = sizeof(rasdialparams);

    // Parse the command line to get the entry information
    ecmd = ParseCommandLine(pCmdLine, &rasdialparams);

    // This will create the default entries if the key does not exist
    RasEnumEntries(NULL, NULL, NULL, &nDefaultEntries, NULL);

    // Get the current number of RAS connections
    prasconn = (RASCONN*)byRasConnData;
    prasconn->dwSize = sizeof(RASCONN);
    nConnections = 0;
    nSize = sizeof(byRasConnData);
    if (RasEnumConnections(prasconn, &nSize, &nConnections) != SUCCESS)
    {
        RetailOutput(TEXT("Error in RasEnumConnections (0x%08x)\r\n"), GetLastError());
        return 1;
    }

    switch (ecmd)
    {
    case ecmdDisconnect:
        if (rasdialparams.szEntryName)
        {
            // A particular entry name was specified.  See if the name exists
            for (i = 0; i < nConnections; i++)
            {
                if (!_tcscmp(rasdialparams.szEntryName, prasconn[i].szEntryName))
                    break;
            }
            if (i == nConnections)
            {
                RetailOutput(TEXT("Error - specified entry name ('%s') not found\r\n"), rasdialparams.szEntryName);
                return 1;
            }
            hRasConn = prasconn[i].hrasconn;
        }
        else
        {
            // No particular entry name was specified - disconnect the first one
            if (nConnections < 1)
            {
                RetailOutput(TEXT("Error - there are no connections to disconnect\r\n"));
                return 1;
            }
            hRasConn = prasconn[0].hrasconn;
        }

        // Hangup the RAS connection
        RetailOutput(TEXT("Disconnecting 0x%08x ('%s')\r\n"), hRasConn, rasdialparams.szEntryName);
        RasHangUp(hRasConn);
        break;

    case ecmdListConnections:
        // List all entries
        rgrasentrynames = (RASENTRYNAME*)LocalAlloc(LPTR, nDefaultEntries);
        if (!rgrasentrynames)
        {
            RetailOutput(TEXT("Error - Out of memory allocating entries\r\n"));
            return 1;
        }
        rgrasentrynames[0].dwSize = sizeof(RASENTRYNAME);

        if (RasEnumEntries(NULL, NULL, rgrasentrynames, &nDefaultEntries, &nEntries) != SUCCESS)
        {
            RetailOutput(TEXT("Error - failure in RasEnumEntries\r\n"));
            return 1;
        }
        RetailOutput(TEXT("%d Entries available:\r\n"), nEntries);

        for (i = 0; i < nEntries; i++)
            RetailOutput(TEXT("  '%s'\r\n"), rgrasentrynames[i].szEntryName);
        
        LocalFree(rgrasentrynames);

        // List all connections
        RetailOutput(TEXT("\r\n%d active connections\r\n"), nConnections);
        for (i = 0; i < nConnections; i++)
        {
            rasconnstatus.dwSize = sizeof(rasconnstatus);
            if (RasGetConnectStatus(prasconn[i].hrasconn, &rasconnstatus) != SUCCESS)
            {
                RetailOutput(TEXT("Error - failure in RasGetConnectStatus\r\n"));
                return 1;
            }

            RetailOutput(TEXT("  0x%08x '%s': %s\r\n"), prasconn[i].hrasconn, prasconn[i].szEntryName,
                         GetStateStr(rasconnstatus.rasconnstate));
            RetailOutput(TEXT("  Error=%d DeviceName='%s' DeviceType='%s'\r\n"), rasconnstatus.dwError,
                         rasconnstatus.szDeviceName, rasconnstatus.szDeviceType);
        }
        break;

    case ecmdConnect:
        // Connect to existing RAS entry
        RetailOutput(TEXT("Dialing RAS entry '%s', UserName='%s' Password='%s' Domain='%s'\r\n"),
                     rasdialparams.szEntryName, rasdialparams.szUserName, rasdialparams.szPassword, rasdialparams.szDomain);

        // Call initialization procedure
        if (!AppInit(hPrevInstance,nCmdShow))
            return 0L;

        rasdialparams.dwSize = sizeof(rasdialparams);

        if (RasDial(NULL, NULL, &rasdialparams, 0xFFFFFFFF, g_hwndApp, &hRasConn) != SUCCESS)
        {
            RetailOutput(TEXT("Error - failure in RasDial\r\n"));
            return 1;
        }
        RetailOutput(TEXT("RasDial successful, hRasConn = 0x%08x\r\n"), hRasConn);

        // Wait around until the connection is made or an error is reported - 'g_fExit' is set at that point
        while (!g_fExit)
        {
            if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
            {
                // There's a message waiting in the queue for us.  Retrieve
                // it and dispatch it, unless it's a WM_QUIT.
                if (msg.message == WM_QUIT)
                break;

                TranslateMessage(&msg); 
                DispatchMessage(&msg);
            }
        }
    
        // When done, destroy the window
        DestroyWindow(g_hwndApp);
        break;
    }

    RetailOutput(TEXT("\r\nApp exited...\r\n"));

    return 0;
}
