/******************************************
*	testrun.h
*******************************************/
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <cguid.h>
#include <objbase.h>
#include <tchar.h>

#include <dplay.h>
#include <dplobby.h>
#include <ddraw.h>
#include <platutil.h>
#include <raserror.h>
#include <Ras.h>

#ifndef ASSERT
#define ASSERT(x) 
#endif

#define WINCEOEM	0


// Structure Define 
class CDPName : public DPNAME
{
public:
    CDPName(LPTSTR szShort = 0, LPTSTR szLong = 0)
    {
        dwSize = sizeof(DPNAME);
        dwFlags = 0;
#ifdef UNICODE
        lpszShortName = szShort;
        lpszLongName = szLong;
#else
        lpszShortNameA = szShort;
        lpszLongNameA = szLong;
#endif
    }
    VOID Set(LPTSTR szShort, LPTSTR szLong)
    {
#ifdef UNICODE
        lpszShortName = szShort;
        lpszLongName = szLong;
#else
        lpszShortNameA = szShort;
        lpszLongNameA = szLong;
#endif
    }
    LPTSTR Value()
    {
#ifdef UNICODE
        return lpszShortName;
#else
        return lpszShortNameA;
#endif
    }
};


// FUNCTION PROTOTYPE
int			CreateArgvArgc(TCHAR *pProgName, TCHAR *argv[20], TCHAR *pCmdLine);
int			StartConnectViaLobbyServer(HINSTANCE hInstance, LPTSTR szUser);
HRESULT		GetSessionInfo(HWND hWnd, LPGUID lpguidSessionInstance, LPDWORD lpdwFlags);
void		SelectSessionInstance(HWND hWnd, LPGUID lpguidSessionInstance);
HRESULT		TestLobbyServer(void);
HRESULT		ConnectToRas(void);
HRESULT		DisconnectToRas(void);
HRESULT		StartReceiveThread(void);
DWORD WINAPI ReceiveThreadStub(LPVOID lpContext);
VOID		KillReceiveThread(void);
DWORD		ReceiveThread(void);
VOID		HandleSysMessage(PBYTE pBuffer, DWORD dwMessageSize);
void		Output(const TCHAR *pwszFormat,...);
void		ErrorDsp(TCHAR *tcMessage, HRESULT	hr);
TCHAR		*ErrorSet(HRESULT	hr);
bool		RegGetClientID( LPCHAR lpClientID );
BOOL FAR PASCAL	EnumPlayersCallback2( DPID dpId, DWORD dwPlayerType, LPCDPNAME lpName, DWORD dwFlags, LPVOID lpContext);
BOOL PASCAL EnumGroupsCallback(DPID dpId, DWORD dwPlayerType, LPCDPNAME lpName,
                   DWORD dwFlags, LPVOID lpContext);
void		MsgDsp(TCHAR *tcMessage, DWORD dwMsgId);
TCHAR		*MsgSet(DWORD	dwMsgId);
BOOL PASCAL EnumSessionsCallback(LPCDPSESSIONDESC2 lpSData, LPDWORD lpdwTimeOut, DWORD dwFlag, LPVOID lpText);
BOOL	SetRegInformation(LPSTR lpClientName, LPSTR	lpSeverIP);
VOID Usage(void);

