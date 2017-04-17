/********************************************************************
 * dialer.cpp
 *
 * Description
 *    CDialer - class that handles dialing up, connecting, and 
 *    hanging up RAS connections (to ISP or LAN connetion).
 ********************************************************************/

/********************************************************************
 * Includes
 ********************************************************************/
#include "headers.h"            // common headers
#include "raserror.h"           // RAS defines
#include "dialer.h"             // CDialer
#include "winsock.h"            // communications
#include "draw.h"               // DDraw helpers
#include "resource.h"           // resource IDs

/********************************************************************
 * Defines
 ********************************************************************/
#define RASDIAL_NAME            TEXT("HtmlSamp_Dialer") // RAS entry
#define ISP_DEFAULT             TEXT("HtmlSamp_ISP")    // RAS entry

#define X_WAIT          195     // position of wait screen
#define Y_WAIT          178	
#define W_WAIT          250
#define H_WAIT          124

/********************************************************************
 * Enums
 ********************************************************************/
enum RASLABEL {                 // RAS entry label list
                RAS_NAME,
                RAS_COUNTRYCODE,
                RAS_AREACODE,
                RAS_PHONE,
                RAS_ALTPHONE,
                RAS_DIALMODE,
                RAS_SPECIFICIPADDR,
                RAS_IPADDR,
                RAS_SPECIFICNAMESERVERS,
                RAS_DNSADDR,
                RAS_ALTDNSADDR,
                RAS_WINSADDR,
                RAS_ALTWINSADDR,
                RAS_DEVICETYPE,
                RAS_DEVICENAME,
                RAS_IPHEADERCOMPRESSION,
                RAS_SWCOMPRESSION,
                RAS_USECOUNTRYANDAREACODES,
                RAS_USERNAME,
                RAS_PASSWORD,
                RAS_DOMAIN,
                RAS_BAUDRATE
#ifdef SLIP_SUPPORTED
               ,RAS_FRAMING
#endif
              };

typedef struct {
                RASLABEL iRasLabel;
                LPCTSTR  lpValue;
               } RASVALUE;

/********************************************************************
 * Structures
 ********************************************************************/
// This structure defines RAS connection properties
// Games may customize this array for their own ISP connection
#if 1   // sample for Null Modem Connection
RASVALUE aRasValue[] = { { RAS_NAME,                    ISP_DEFAULT },
                         { RAS_DEVICETYPE,              TEXT("direct") },
                         { RAS_DEVICENAME,              TEXT("NullModem") },
                         { RAS_SPECIFICIPADDR,          TEXT("Y") },
                         { RAS_IPADDR,                  TEXT("192.100.100.2") },
                         { RAS_SPECIFICNAMESERVERS,     TEXT("N") },
                         { RAS_IPHEADERCOMPRESSION,     TEXT("Y") },
                         { RAS_SWCOMPRESSION,           TEXT("Y") },
                         { RAS_USERNAME,                TEXT("guest") },
                         { RAS_BAUDRATE,                TEXT("19200") }
                       };
#else   // sample for Dial-Up ISP Connection
        // no need to define any NULL entry
RASVALUE aRasValue[] = { { RAS_NAME,                    ISP_DEFAULT },
                         { RAS_SPECIFICIPADDR,          TEXT("N") },
                         { RAS_IPADDR,                  TEXT("") },
                         { RAS_SPECIFICNAMESERVERS,     TEXT("Y") },
                         { RAS_DNSADDR,                 TEXT("<DNS>") },
                         { RAS_ALTDNSADDR,              TEXT("<Alt DNS>") },
                         { RAS_WINSADDR,                TEXT("") },
                         { RAS_ALTWINSADDR,             TEXT("") },
                         { RAS_DEVICETYPE,              TEXT("modem") },
                         { RAS_DEVICENAME,              TEXT("Sega-DreamcastBuiltIn") },
                         { RAS_IPHEADERCOMPRESSION,     TEXT("Y") },
                         { RAS_SWCOMPRESSION,           TEXT("Y") },
                         { RAS_USECOUNTRYANDAREACODES,  TEXT("N") },
                         { RAS_COUNTRYCODE,             TEXT("") },
                         { RAS_AREACODE,                TEXT("") },
                         { RAS_PHONE,                   TEXT("<Phone Number>") },
                         { RAS_ALTPHONE,                TEXT("") },
                         { RAS_DIALMODE,                TEXT("") },
                         { RAS_USERNAME,                TEXT("<User Name>") },
                         { RAS_PASSWORD,                TEXT("<Password>") },
                         { RAS_DOMAIN,                  TEXT("") },
                         { RAS_BAUDRATE,                TEXT("57600") }
                       };
#endif

/********************************************************************
 * CDialer::CDialer
 *
 * Description
 *    Constructor. Registers window for dialing message reception.
 *    Initializes RAS dialing entry in master phone book.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    N/A
 ********************************************************************/
CDialer::CDialer(void)
{
    // initialize window class for window to receive RAS messages
    WNDCLASS wc;
    wc.style            = 0;
    wc.lpfnWndProc      = (WNDPROC)WndProc;
    wc.cbClsExtra       = 0;
    wc.cbWndExtra       = 0;
    wc.hInstance        = g_hInstance;
    wc.hIcon            = 0;
    wc.hCursor          = 0;
    wc.hbrBackground    = NULL;
    wc.lpszMenuName     = 0;
    wc.lpszClassName    = RASDIAL_NAME;
    RegisterClass(&wc);

    // initialize internal data
    _fInit              = TRUE;
    _fConnect           = FALSE;
    _hRasConn           = NULL;
    _achEntryName[0]    = TEXT('\0');

    // check if connection entry is already defined in master Phone Entry
    // otherwise, add new entry base on aRasEntry
    _tcscpy(_achEntryName, ISP_DEFAULT);
    RASDIALPARAMS RasDialParams;
    if (InitDialParams(RasDialParams) == E_FAIL && InitRasEntry() == E_FAIL)
    {
        _fInit = FALSE;
    }
}

/********************************************************************
 * CDialer::~CDialer
 *
 * Description
 *    Destructor. Hangs up connection.
 *
 * Parameters
 *    N/A
 * 
 * Returns
 *    N/A
 ********************************************************************/
CDialer::~CDialer(void)
{
    // disconnect
    HangUp();
}

/********************************************************************
 * CDialer::Dial
 *
 * Description
 *    Connects through RAS if not already connected.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    S_OK     connected okay or already connected
 *    S_FALSE  could not connect
 *    E_FAIL   could not initialize
 ********************************************************************/
HRESULT CDialer::Dial(void)
{
    HRESULT hr;

    // check if this Dialer instance is already connect
    if (_fConnect && _hRasConn)
    {
        return S_OK;
    }

    // check if other Dialer instance has connected
    hr = IsConnect();
    if (hr == S_OK)
    {
        return hr;
    }

    // load Dial Information Parameters
    RASDIALPARAMS RasDialParams;
    if (InitDialParams(RasDialParams) == E_FAIL)
    {
        return E_FAIL;
    }

    // create Dialing message receiver window
    HWND hWnd = CreateWindow(RASDIAL_NAME, RASDIAL_NAME,
                             0, 0, 0, 5, 5, NULL, NULL, g_hInstance, NULL);
    if (hWnd)
    {
        SetWindowLong(hWnd, GWL_USERDATA, (LPARAM)this);
    }

    // make Dial request
    RasDialParams.dwSize = sizeof(RASDIALPARAMS);
    DWORD RetVal = RasDial(NULL, NULL, &RasDialParams, 0xFFFFFFFF, hWnd, &_hRasConn);

    IDirectDrawSurface *pDDSBitmap = CreateBitmapSurface(MAKEINTRESOURCE(IDB_WAIT), W_WAIT, H_WAIT,  FALSE, 0);
    if (pDDSBitmap)
    {
        DrawWaitScreen(X_WAIT, Y_WAIT, W_WAIT, H_WAIT, pDDSBitmap);
        pDDSBitmap->Release();
    }

    // dont allow screen updates (keep wait screen displayed)
    LockScreen();

    if (RetVal == SUCCESS && hWnd)
    {
        MSG msg;

        // waiting for connection...
        while (GetMessage(&msg, hWnd, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    // allow screen updates
    UnlockScreen();

    // check if Dial failed
    if (RetVal != SUCCESS || !_fConnect)
    {
        if (_hRasConn != NULL)
        {
            RasHangUp(_hRasConn);
        }
    }

    return (_fConnect ? S_OK : S_FALSE);
}

/********************************************************************
 * CDialer::HangUp
 *
 * Description
 *    Disconnects.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    None
 ********************************************************************/
void CDialer::HangUp(void)
{
    // disconnect if connection exists
    if (_hRasConn)
    {
        RasHangUp(_hRasConn);
        _hRasConn = NULL;
        _fConnect = FALSE;
    }
}

/********************************************************************
 * CDialer::IsInit
 *
 * Description
 *    Returns dialer initialization state.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    S_OK     initialization successful
 *    S_FALSE  initialization failed
 ********************************************************************/
HRESULT CDialer::IsInit(void)
{
    return _fInit ? S_OK : S_FALSE;
}

/********************************************************************
 * CDialer::IsConnect
 *
 * Description
 *    Returns dialer connection state.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    S_OK     is connected
 *    S_FALSE  is disconnected
 *    E_FAIL   could not obtain state
 ********************************************************************/
HRESULT CDialer::IsConnect(void)
{
    // get the current list of connections
    RASCONN   RasConnData[10];
    LPRASCONN pRasConn    = RasConnData;
    DWORD     Connections = 0;
    DWORD     cb          = sizeof(RasConnData);
    pRasConn->dwSize      = sizeof(RASCONN);

    // obtain number of current connections
    if (RasEnumConnections(pRasConn, &cb, &Connections) == SUCCESS)
    {
        for (WORD i = 0; i < Connections; i++)
        {
            // if EntryName is matched, verify the connection state
            if (!_tcsicmp(_achEntryName, pRasConn[i].szEntryName))
            {
                RASCONNSTATUS RasConnStatus;
                RasConnStatus.dwSize = sizeof(RASCONNSTATUS);
                if (RasGetConnectStatus(pRasConn[i].hrasconn,
                                        &RasConnStatus) == SUCCESS)
                {
                    return RasConnStatus.rasconnstate == RASCS_Connected
                           ? S_OK : S_FALSE;
                }
            }
        }
    }

    return E_FAIL;
}

/********************************************************************
 * CDialer::WndProc
 *
 * Description
 *    Window procedure for dialer window to receive RAS messages.
 *
 * Parameters
 *    hWnd     window receiving message
 *    wMsg     ID of message
 *    wParam   message data
 *    lParam   message data
 * 
 * Returns
 *    0        handled messages
 *    other    result of DefWindowProc
 ********************************************************************/
// Dialer message receiver WndProc
LRESULT CDialer::WndProc(HWND hWnd, UINT wMsg, WPARAM wParam, LPARAM lParam)
{
    CDialer *pDialer = (CDialer *)GetWindowLong(hWnd, GWL_USERDATA);

    switch (wMsg)
    { 
        // handle RAS message
        case WM_RASDIALEVENT:
            switch ((RASCONNSTATE)wParam)
            {
                case RASCS_Connected:
                    pDialer->_fConnect = TRUE;
                case RASCS_Disconnected:
                    DestroyWindow(hWnd);
                    break;
            }
            return TRUE;

        // get out of waiting message loop
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        default:
            return DefWindowProc(hWnd, wMsg, wParam, lParam);
    }
}

/********************************************************************
 * CDialer::InitDialParams
 *
 * Description
 *    Loads dial information parameters.
 *
 * Parameters
 *    RasDialParms Filled with RAS parameters
 * 
 * Returns
 *    S_OK         parameter retrieval successful
 *    E_FAIL       parameter retrieval failed
 ********************************************************************/
HRESULT CDialer::InitDialParams(RASDIALPARAMS &RasDialParams)
{
    // initialize structure
    memset((char *)&RasDialParams, 0, sizeof(RASDIALPARAMS));
    RasDialParams.dwSize = sizeof(RASDIALPARAMS);
    _tcscpy(RasDialParams.szEntryName, _achEntryName);

    // load the dial params for this entry
    BOOL fPassword;
    if (RasGetEntryDialParams(NULL, &RasDialParams, &fPassword) == SUCCESS)
    {
        return S_OK;
    }
    else
    {
        return E_FAIL;
    }
}

/********************************************************************
 * CDialer::InitRasEntry
 *
 * Description
 *    Adds a RAS entry to the master RAS phone book.
 *
 * Parameters
 *    None
 * 
 * Returns
 *    S_OK     RAS entry addtion to phone book sucessful
 *    E_FAIL   RAS entry addtion to phone book failed
 ********************************************************************/
HRESULT CDialer::InitRasEntry(void)
{
    #define MAX_LINE 256
    #define MAX_ALTPHONE MAX_LINE
    DWORD           cb;
    RASENTRY        RasEntry;
    RASDIALPARAMS   RasDialParams;
    char            szString[MAX_LINE];
    DWORD           BaudRate      = 0;
    TCHAR           szAltPhone[MAX_ALTPHONE];
    DWORD           nAltPhoneSize = 0;
    TCHAR          *pch;
    LPBYTE          pRasEntryEx   = NULL;

    // get a default RasEntry
    RasEntry.dwSize = sizeof(RASENTRY);
    cb = sizeof(RASENTRY);
    RasGetEntryProperties (NULL, TEXT(""), &RasEntry, &cb, NULL, NULL);
    ASSERT(RasEntry.dwAlternateOffset == 0);
    ASSERT(RasEntry.dwReserved1 == 0);
    memset ((char *)&RasDialParams, 0, sizeof(RasDialParams));

    // find parameters
    for (SHORT iRasValue = 0; iRasValue < sizeof(aRasValue)/sizeof(RASVALUE);
         iRasValue++)
    {
        RASLABEL iRasLabel = aRasValue[iRasValue].iRasLabel;
        LPCTSTR  lpValue   = aRasValue[iRasValue].lpValue;

        switch(iRasLabel)
        {
            case RAS_NAME:
                _tcsncpy(_achEntryName, lpValue, RAS_MaxEntryName);
                break;
            case RAS_COUNTRYCODE:
                RasEntry.dwCountryCode = _ttol(lpValue);
                break;
            case RAS_AREACODE:
                _tcsncpy (RasEntry.szAreaCode, lpValue, RAS_MaxAreaCode);
                break;
            case RAS_PHONE:
                _tcsncpy (RasEntry.szLocalPhoneNumber, lpValue, RAS_MaxPhoneNumber);
                break;
            case RAS_ALTPHONE:
                RasEntry.dwAlternateOffset = sizeof(RASENTRY);
                _tcsncpy (szAltPhone, lpValue, MAX_ALTPHONE - 2);
                szAltPhone[MAX_ALTPHONE - 2] = (TCHAR)NULL;
                szAltPhone[MAX_ALTPHONE - 1] = (TCHAR)NULL;
                nAltPhoneSize = (_tcslen(szAltPhone) + 2) * sizeof(TCHAR);
                pch = szAltPhone;
                while (*pch != (TCHAR)NULL)
                {
                    if (*pch == TEXT('.'))
                    {
                        *pch = (TCHAR)NULL;
                    }
                    pch++;
                }
                break;
            case RAS_DIALMODE:
                RasEntry.dwReserved1 = _ttol(lpValue);
                break;
            case RAS_SPECIFICIPADDR:
                if ((*lpValue == 'y') || (*lpValue == 'Y'))
                    RasEntry.dwfOptions |= RASEO_SpecificIpAddr;
                else
                    RasEntry.dwfOptions &= ~(RASEO_SpecificIpAddr);
                break;
            case RAS_IPADDR:
                wcstombs (szString, lpValue, _tcslen(lpValue)+1);
                *((u_long *)&(RasEntry.ipaddr)) = htonl(inet_addr (szString));
                break;
            case RAS_SPECIFICNAMESERVERS:
                if ((*lpValue == 'y') || (*lpValue == 'Y'))
                    RasEntry.dwfOptions |= RASEO_SpecificNameServers;
                else
                    RasEntry.dwfOptions &= ~(RASEO_SpecificNameServers);
                break;
            case RAS_DNSADDR:
                wcstombs (szString, lpValue, _tcslen(lpValue)+1);
                *((u_long *)&(RasEntry.ipaddrDns)) = htonl(inet_addr (szString));
                break;
            case RAS_ALTDNSADDR:
                wcstombs (szString, lpValue, _tcslen(lpValue)+1);
                *((u_long *)&(RasEntry.ipaddrDnsAlt)) = htonl(inet_addr (szString));
                break;
            case RAS_WINSADDR:
                wcstombs (szString, lpValue, _tcslen(lpValue)+1);
                *((u_long *)&(RasEntry.ipaddrWins)) = htonl(inet_addr (szString));
                break;
            case RAS_ALTWINSADDR:
                wcstombs (szString, lpValue, _tcslen(lpValue)+1);
                *((u_long *)&(RasEntry.ipaddrWinsAlt)) = htonl(inet_addr (szString));
                break;
            case RAS_DEVICETYPE:
                _tcsncpy (RasEntry.szDeviceType, lpValue, RAS_MaxDeviceType + 1);
                break;
            case RAS_DEVICENAME:
                _tcsncpy (RasEntry.szDeviceName, lpValue, RAS_MaxDeviceName + 1);
                break;
            case RAS_IPHEADERCOMPRESSION:
                if ((*lpValue == 'y') || (*lpValue == 'Y'))
                    RasEntry.dwfOptions |= RASEO_IpHeaderCompression;
                else
                    RasEntry.dwfOptions &= ~(RASEO_IpHeaderCompression);
                break;
            case RAS_SWCOMPRESSION:
                if ((*lpValue == 'y') || (*lpValue == 'Y'))
                    RasEntry.dwfOptions |= RASEO_SwCompression;
                else
                    RasEntry.dwfOptions &= ~(RASEO_SwCompression);
                break;
            case RAS_USECOUNTRYANDAREACODES:
                if ((*lpValue == 'y') || (*lpValue == 'Y'))
                    RasEntry.dwfOptions |= RASEO_UseCountryAndAreaCodes;
                else
                    RasEntry.dwfOptions &= ~(RASEO_UseCountryAndAreaCodes);
                break;
            case RAS_USERNAME:
                _tcsncpy (RasDialParams.szUserName, lpValue, UNLEN);
                break;
            case RAS_PASSWORD:
                _tcsncpy (RasDialParams.szPassword, lpValue, PWLEN);
                break;
            case RAS_DOMAIN:
                _tcsncpy (RasDialParams.szDomain, lpValue, DNLEN);
                break;
            case RAS_BAUDRATE:
                BaudRate = _ttol (lpValue);
                break;
#ifdef SLIP_SUPPORTED
            case RAS_FRAMING:
                if ((*lpValue == 's') || (*lpValue == 'S'))
                {
                    RasEntry.dwFramingProtocol = RASFP_Slip;
                }
                break;
#endif
        }
    }

    // entry name is required
    if (_achEntryName[0] == TEXT('\0'))
    {
        return E_FAIL;
    }

    // add entry properties
    ASSERT(nAltPhoneSize == 0 ||
           RasEntry.dwAlternateOffset >= sizeof(RASENTRY));
    pRasEntryEx = (LPBYTE)LocalAlloc(LMEM_FIXED, sizeof(RASENTRY) + nAltPhoneSize);
    ASSERT(pRasEntryEx != NULL);
    memcpy(pRasEntryEx, &RasEntry, sizeof(RASENTRY));
    memcpy(pRasEntryEx + sizeof(RASENTRY), szAltPhone, nAltPhoneSize);

    if (RasSetEntryProperties (NULL, _achEntryName, (LPRASENTRY)pRasEntryEx,
                               sizeof(RasEntry) + nAltPhoneSize, NULL, 0))
    {
        LocalFree(pRasEntryEx);
        return E_FAIL;
    }
    LocalFree(pRasEntryEx);

    // add phone entry
    RasDialParams.dwSize = sizeof(RASDIALPARAMS);
    _tcscpy(RasDialParams.szEntryName, _achEntryName);
    RasSetEntryDialParams(NULL, &RasDialParams, FALSE);
	
    if (BaudRate)
    {
        DCB   Dcb;
        HKEY  hDeviceKey;
        DWORD dwLenSettings = sizeof(Dcb);
        TCHAR achDevice[32] = TEXT("Modem\\");
        _tcscat(achDevice, RasEntry.szDeviceName);

        // write settings to registry
        if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
                         achDevice,
                         0,
                         KEY_READ | KEY_WRITE,
                         &hDeviceKey) == ERROR_SUCCESS)
        {
            HRESULT hr = E_FAIL;
            if (RegQueryValueEx(hDeviceKey,
                                TEXT("Settings"),
                                NULL,
                                NULL,
                                (LPBYTE)&Dcb,
                                &dwLenSettings) == ERROR_SUCCESS)
            {
                Dcb.BaudRate = BaudRate;
                if (RegSetValueEx(hDeviceKey,
                                  TEXT("Settings"),
                                  0,
                                  REG_BINARY,
                                  (const BYTE *)&Dcb,
                                  sizeof(DCB)) == ERROR_SUCCESS)
                {
                    // failed to write registry
                    hr = S_OK;
                }
            }
            RegCloseKey(hDeviceKey);
            return hr;
        }
        else
        {
            // failed to access registry
            return E_FAIL;
        }
    }

    return S_OK;
}
