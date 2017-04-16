// MSJSock.h : main header file for MSJSOCK.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMSJSockApp : See MSJSock.cpp for implementation.

class CMSJSockApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();

	LPWSADATA Sock() { return &m_wsa; };

protected:
	WSADATA m_wsa;
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

#define IDP_SOCKETS_INIT_FAILED         104
