// MSJSock.cpp : Implementation of CMSJSockApp and DLL registration.

#include "stdafx.h"
#include "MSJSock.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CMSJSockApp NEAR theApp;

const GUID CDECL BASED_CODE _tlid =
		{ 0x9e638960, 0x2c21, 0x11cf, { 0xa0, 0x18, 0x44, 0x45, 0x53, 0x54, 0, 0 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


////////////////////////////////////////////////////////////////////////////
// CMSJSockApp::InitInstance - DLL initialization

BOOL CMSJSockApp::InitInstance()
{
	BOOL bInit = COleControlModule::InitInstance();

	// Normally we'd call WSAStartup, but AfxSocketInit
	// wraps the call for us and takes care of some of the
	// version checking automatically.

	if (bInit)
	{
		if (!AfxSocketInit(&m_wsa))
		{
			AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
			return FALSE;
		}
	}

	return bInit;
}


////////////////////////////////////////////////////////////////////////////
// CMSJSockApp::ExitInstance - DLL termination

int CMSJSockApp::ExitInstance()
{
	AfxSocketTerm();
	return COleControlModule::ExitInstance();
}


/////////////////////////////////////////////////////////////////////////////
// DllRegisterServer - Adds entries to the system registry

STDAPI DllRegisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(TRUE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}


/////////////////////////////////////////////////////////////////////////////
// DllUnregisterServer - Removes entries from the system registry

STDAPI DllUnregisterServer(void)
{
	AFX_MANAGE_STATE(_afxModuleAddrThis);

	if (!AfxOleUnregisterTypeLib(_tlid))
		return ResultFromScode(SELFREG_E_TYPELIB);

	if (!COleObjectFactoryEx::UpdateRegistryAll(FALSE))
		return ResultFromScode(SELFREG_E_CLASS);

	return NOERROR;
}
