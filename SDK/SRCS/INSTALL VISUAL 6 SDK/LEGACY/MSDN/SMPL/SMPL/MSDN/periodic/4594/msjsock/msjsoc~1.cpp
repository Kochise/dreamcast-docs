// MSJSockCtl.cpp : Implementation of the CMSJSockCtrl OLE control class.

#include "stdafx.h"
#include "MSJSock.h"
#include "MSJSockCtl.h"
#include "MSJSockPpg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(CMSJSockCtrl, COleControl)

extern CMSJSockApp theApp;
LPBYTE pm_szBuf;


/////////////////////////////////////////////////////////////////////////////
// Message map

BEGIN_MESSAGE_MAP(CMSJSockCtrl, COleControl)
	//{{AFX_MSG_MAP(CMSJSockCtrl)
	// NOTE - ClassWizard will add and remove message map entries
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
	ON_MESSAGE(WSCB_GETHOST, OnGetHostCB)
	ON_MESSAGE(WSCB_ASELECT, OnASelectCB)
	ON_OLEVERB(AFX_IDS_VERB_EDIT, OnEdit)
	ON_OLEVERB(AFX_IDS_VERB_PROPERTIES, OnProperties)
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Dispatch map

BEGIN_DISPATCH_MAP(CMSJSockCtrl, COleControl)
	//{{AFX_DISPATCH_MAP(CMSJSockCtrl)
	DISP_PROPERTY_EX(CMSJSockCtrl, "Version", GetVersion, SetVersion, VT_I2)
	DISP_PROPERTY_EX(CMSJSockCtrl, "SystemStatus", GetSystemStatus, SetSystemStatus, VT_BSTR)
	DISP_PROPERTY_EX(CMSJSockCtrl, "MaxSockets", GetMaxSockets, SetMaxSockets, VT_I2)
	DISP_PROPERTY_EX(CMSJSockCtrl, "HiVersion", GetHiVersion, SetHiVersion, VT_I2)
	DISP_PROPERTY_EX(CMSJSockCtrl, "Description", GetDescription, SetDescription, VT_BSTR)
	DISP_FUNCTION(CMSJSockCtrl, "CreateSocket", CreateSocket, VT_I4, VTS_NONE)
	DISP_FUNCTION(CMSJSockCtrl, "gethostbyname", gethostbyname, VT_HANDLE, VTS_BSTR)
	DISP_FUNCTION(CMSJSockCtrl, "getservbyname", getservbyname, VT_I2, VTS_BSTR)
	DISP_FUNCTION(CMSJSockCtrl, "AsyncSelect", AsyncSelect, VT_I4, VTS_I4 VTS_I4)
	DISP_FUNCTION(CMSJSockCtrl, "connect", connect, VT_HANDLE, VTS_I4 VTS_I2 VTS_HANDLE)
	//}}AFX_DISPATCH_MAP
	DISP_FUNCTION_ID(CMSJSockCtrl, "AboutBox", DISPID_ABOUTBOX, AboutBox, VT_EMPTY, VTS_NONE)
END_DISPATCH_MAP()


/////////////////////////////////////////////////////////////////////////////
// Event map

BEGIN_EVENT_MAP(CMSJSockCtrl, COleControl)
	//{{AFX_EVENT_MAP(CMSJSockCtrl)
	EVENT_CUSTOM("Connect", FireConnect, VTS_HANDLE)
	EVENT_CUSTOM("RecvData", FireRecvData, VTS_HANDLE  VTS_BSTR)
	EVENT_CUSTOM("SockError", FireSockError, VTS_HANDLE  VTS_I2)
	EVENT_CUSTOM("GotHost", FireGotHost, VTS_HANDLE)
	//}}AFX_EVENT_MAP
END_EVENT_MAP()


/////////////////////////////////////////////////////////////////////////////
// Property pages

// TODO: Add more property pages as needed.  Remember to increase the count!
BEGIN_PROPPAGEIDS(CMSJSockCtrl, 1)
	PROPPAGEID(CMSJSockPropPage::guid)
END_PROPPAGEIDS(CMSJSockCtrl)


/////////////////////////////////////////////////////////////////////////////
// Initialize class factory and guid

IMPLEMENT_OLECREATE_EX(CMSJSockCtrl, "MSJSOCK.MSJSockCtrl.1",
	0x9e638963, 0x2c21, 0x11cf, 0xa0, 0x18, 0x44, 0x45, 0x53, 0x54, 0, 0)


/////////////////////////////////////////////////////////////////////////////
// Type library ID and version

IMPLEMENT_OLETYPELIB(CMSJSockCtrl, _tlid, _wVerMajor, _wVerMinor)


/////////////////////////////////////////////////////////////////////////////
// Interface IDs

const IID BASED_CODE IID_DMSJSock =
		{ 0x9e638961, 0x2c21, 0x11cf, { 0xa0, 0x18, 0x44, 0x45, 0x53, 0x54, 0, 0 } };
const IID BASED_CODE IID_DMSJSockEvents =
		{ 0x9e638962, 0x2c21, 0x11cf, { 0xa0, 0x18, 0x44, 0x45, 0x53, 0x54, 0, 0 } };


/////////////////////////////////////////////////////////////////////////////
// Control type information

// Important: make sure OLEMISC_INVISIBLEATRUNTIME is not included.
//    This would cause the control not to have an hWnd at runtime;
//    we want one, but we want it hidden.

static const DWORD BASED_CODE _dwMSJSockOleMisc =
	OLEMISC_ACTIVATEWHENVISIBLE |
	OLEMISC_SETCLIENTSITEFIRST |
	OLEMISC_INSIDEOUT |
	OLEMISC_CANTLINKINSIDE |
	OLEMISC_RECOMPOSEONRESIZE;

IMPLEMENT_OLECTLTYPE(CMSJSockCtrl, IDS_MSJSOCK, _dwMSJSockOleMisc)


/////////////////////////////////////////////////////////////////////////////
// CMSJSockCtrl::CMSJSockCtrlFactory::UpdateRegistry -
// Adds or removes system registry entries for CMSJSockCtrl

BOOL CMSJSockCtrl::CMSJSockCtrlFactory::UpdateRegistry(BOOL bRegister)
{
	if (bRegister)
		return AfxOleRegisterControlClass(
			AfxGetInstanceHandle(),
			m_clsid,
			m_lpszProgID,
			IDS_MSJSOCK,
			IDB_MSJSOCK,
			TRUE,                       //  Insertable
			_dwMSJSockOleMisc,
			_tlid,
			_wVerMajor,
			_wVerMinor);
	else
		return AfxOleUnregisterClass(m_clsid, m_lpszProgID);
}


/////////////////////////////////////////////////////////////////////////////
// CMSJSockCtrl::CMSJSockCtrl - Constructor

CMSJSockCtrl::CMSJSockCtrl()
{
	InitializeIIDs(&IID_DMSJSock, &IID_DMSJSockEvents);
}


/////////////////////////////////////////////////////////////////////////////
// CMSJSockCtrl::~CMSJSockCtrl - Destructor

CMSJSockCtrl::~CMSJSockCtrl()
{
}


/////////////////////////////////////////////////////////////////////////////
// CMSJSockCtrl::OnDraw - Drawing function

void CMSJSockCtrl::OnDraw(
			CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid)
{
	// Hide the control at runtime

	if (m_hWnd != NULL)
		ShowWindow(SW_HIDE);
	else
	{
		// Draw something at design-time
		pdc->FillRect(rcBounds, CBrush::FromHandle((HBRUSH)GetStockObject(WHITE_BRUSH)));
		pdc->Ellipse(rcBounds);
	}
}


/////////////////////////////////////////////////////////////////////////////
// CMSJSockCtrl::DoPropExchange - Persistence support

void CMSJSockCtrl::DoPropExchange(CPropExchange* pPX)
{
	ExchangeVersion(pPX, MAKELONG(_wVerMinor, _wVerMajor));
	COleControl::DoPropExchange(pPX);

	// TODO: Call PX_ functions for each persistent custom property.

}


/////////////////////////////////////////////////////////////////////////////
// CMSJSockCtrl::OnResetState - Reset control to default state

void CMSJSockCtrl::OnResetState()
{
	COleControl::OnResetState();  // Resets defaults found in DoPropExchange

	// TODO: Reset any other control state here.
}


/////////////////////////////////////////////////////////////////////////////
// CMSJSockCtrl::AboutBox - Display an "About" box to the user

void CMSJSockCtrl::AboutBox()
{
	CDialog dlgAbout(IDD_ABOUTBOX_MSJSOCK);
	dlgAbout.DoModal();
}


/////////////////////////////////////////////////////////////////////////////
// CMSJSockCtrl message handlers

// Get the current Windows Sockets version from the info returned at startup

short CMSJSockCtrl::GetVersion() 
{
	return theApp.Sock()->wVersion;
}

void CMSJSockCtrl::SetVersion(short nNewValue) 
{
	// Read/only property, so do nothing.
}

// Get the current system status from the info returned at startup

BSTR CMSJSockCtrl::GetSystemStatus() 
{
	CString s;
	s = theApp.Sock()->szSystemStatus;
	return s.AllocSysString();
}

void CMSJSockCtrl::SetSystemStatus(LPCTSTR lpszNewValue) 
{
	// Read/only property, so do nothing.
}

// Get the maximum sockets allowed on this control

short CMSJSockCtrl::GetMaxSockets() 
{
	return theApp.Sock()->iMaxSockets;
}

void CMSJSockCtrl::SetMaxSockets(short nNewValue) 
{
	// Read/only property, so do nothing.
}

// Get the highest allowed version from the info returned at startup

short CMSJSockCtrl::GetHiVersion() 
{
	return theApp.Sock()->wHighVersion;
}

void CMSJSockCtrl::SetHiVersion(short nNewValue) 
{
	// Read/only property, so do nothing.
}

// Get the Windows Sockets description from the startup info

BSTR CMSJSockCtrl::GetDescription() 
{
	CString s;

	s = theApp.Sock()->szDescription;
	return s.AllocSysString();
}

void CMSJSockCtrl::SetDescription(LPCTSTR lpszNewValue) 
{
	// Read/only property, so do nothing.
}

// Create a socket - wrap the socket() API call

long CMSJSockCtrl::CreateSocket() 
{
	SOCKET hSock;

	hSock = ::socket(AF_INET, SOCK_STREAM, 0);

	if (hSock <= 0)
		return -1;
	else
    	return hSock;
}

// Convert a host string to its IP address

OLE_HANDLE CMSJSockCtrl::gethostbyname(LPCTSTR host) 
{
	pm_szBuf = (LPBYTE) GlobalAllocPtr(GHND, 2048);

    HANDLE hTask = WSAAsyncGetHostByName(m_hWnd, WSCB_GETHOST, host, 
                                         (char FAR *) pm_szBuf, 2048);

	return (OLE_HANDLE) hTask;
}

// Wait for the GetHostByName to return info. This maps WSCB_GETHOST
// into the OnGetHostCB message handler.

afx_msg LONG CMSJSockCtrl::OnGetHostCB(UINT wParam, LONG lParam)
{
	HANDLE hTask = (HANDLE) wParam;
	UINT   wserr = HIWORD(lParam);
	UINT   uCode = LOWORD(lParam);

	LPVOID lphe;

	u_long addr;
	hostent he;
	sockaddr_in ca;

	// If the call didn't return an error, call GotHost in the
	// container program.

	if (wserr == WSANOERROR)
	{
		lphe = (LPVOID) GlobalAllocPtr(GHND, sizeof(hostent));

		memcpy(lphe, (LPVOID) pm_szBuf, sizeof(hostent));
		FireGotHost((OLE_HANDLE) lphe);
		   
		return TRUE;
	}
	else // call SockError in the container
		FireSockError((OLE_HANDLE) hTask, wserr);

	return TRUE;
}

// Handle all messages requested by a WSAAsyncSelect call

afx_msg LONG CMSJSockCtrl::OnASelectCB(UINT wParam, LONG lParam)
{
	HANDLE hTask = (HANDLE) wParam;
	UINT   wserr = HIWORD(lParam);
	UINT   uCode = LOWORD(lParam);

	u_long addr;
	hostent he;
	sockaddr_in ca;

	switch (uCode)
	{
		// If a connect message comes back, fire the Connect event
		case FD_CONNECT:
	  		if (wserr != WSANOERROR)
				FireSockError((OLE_HANDLE) hTask, wserr);
			else
			{
				FireConnect((OLE_HANDLE) hTask);
			}
			break;

		// Not yet handling a close message
		case FD_CLOSE:
			break;

		// When data is incoming, call the RecvData event
		case FD_READ:
		{
			FireRecvData((OLE_HANDLE) hTask, NULL);
			break;
		}

		// Not yet handling a ready to write message
		case FD_WRITE:
			break;

		// Not yet handling an out of band data message
		case FD_OOB:
			break;

		// Not yet handling an accept message
		case FD_ACCEPT:
			break;

		default:
			break;
	}

	return TRUE;
}

// Wrap the getservbyname function - returning a port ID when
// given a service like "finger." This only handles tcp now, not
// udp.

short CMSJSockCtrl::getservbyname(LPCTSTR service) 
{
	short port;
	LPSERVENT servent;

	servent = ::getservbyname(service, "tcp");
	port = servent->s_port;

	// Convert the port from network byte order to host
	// machine byte order and return.
	return ntohs(port);
}

// Wrap the WSAAsyncSelect call for the container's sake. This
// automatically routes incoming messages to this control's
// window.

long CMSJSockCtrl::AsyncSelect(long socket, long msg) 
{
	return WSAAsyncSelect(socket, m_hWnd, WSCB_ASELECT, msg);
}

// Wrap the functions needed to perform a connect to a port/host.

OLE_HANDLE CMSJSockCtrl::connect(long socket, short port, OLE_HANDLE phostent) 
{
	hostent he;
	u_long addr;
	sockaddr_in ca;

	// Copy the hostent data handle from the container to a real
	// hostent structure.

	memcpy((LPVOID) &he, (LPVOID) phostent, sizeof(hostent));

	// Get the IP address from the hostent.

	addr = (*(u_long FAR *) he.h_addr_list[0]);

	// Fill in the sockaddr_structure so we can connect to
	// the specific port and IP address
	ca.sin_family      = AF_INET;
	ca.sin_port	       = htons(port); // Convert from our format to net format
	ca.sin_addr.s_addr = addr;
			   
	// Make the control watch for connections
	WSAAsyncSelect(socket, m_hWnd, WSCB_ASELECT, FD_CONNECT);

	// Call the API connect() function, returning immediately.
	// The container will get a Connect event when the
	// connection is complete.

	return ::connect(socket, (LPSOCKADDR) &ca, sizeof(sockaddr_in));
}
