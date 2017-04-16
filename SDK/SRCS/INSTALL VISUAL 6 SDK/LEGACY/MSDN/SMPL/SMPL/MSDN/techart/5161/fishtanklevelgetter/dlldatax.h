#if !defined(AFX_DLLDATAX_H__7F0DFA9D_F56D_11D0_A980_0020182A7050__INCLUDED_)
#define AFX_DLLDATAX_H__7F0DFA9D_F56D_11D0_A980_0020182A7050__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifdef _MERGE_PROXYSTUB

extern "C" 
{
BOOL WINAPI PrxDllMain(HINSTANCE hInstance, DWORD dwReason, 
	LPVOID lpReserved);
STDAPI PrxDllCanUnloadNow(void);
STDAPI PrxDllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv);
STDAPI PrxDllRegisterServer(void);
STDAPI PrxDllUnregisterServer(void);
}

#endif

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLLDATAX_H__7F0DFA9D_F56D_11D0_A980_0020182A7050__INCLUDED_)
