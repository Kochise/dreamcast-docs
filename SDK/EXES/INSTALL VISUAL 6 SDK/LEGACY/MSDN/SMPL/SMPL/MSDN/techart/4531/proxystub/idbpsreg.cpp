#include <windows.h>
#include <ole2.h>

#include "..\interface\idb.h"

#define _T(x) x

HRESULT RegisterInterface(LPCTSTR lpszName, LPCTSTR lpszIID, int nMethods, LPCTSTR lpszPSCLSID) {
	TCHAR szKey[120];
	HKEY hKeyInterface;
	DWORD dwDisposition;

	lstrcpy(szKey, _T("Interface\\"));
	lstrcat(szKey, lpszIID);

	// Write: HKEY_CLASSES_ROOT\Interface\<lpszIID> - "", <lpszName>
	if (RegCreateKeyEx(HKEY_CLASSES_ROOT, 
			szKey, 
			NULL, _T(""), REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, 
			&hKeyInterface, &dwDisposition)!=ERROR_SUCCESS) {
		return E_UNEXPECTED;
		}
	if (RegSetValueEx(hKeyInterface, _T(""), NULL, REG_SZ, (BYTE*) lpszName, (lstrlen(lpszName)+1)*sizeof(TCHAR))!=ERROR_SUCCESS) {
		RegCloseKey(hKeyInterface);
		return E_UNEXPECTED;
		}

	// Write: HKEY_CLASSES_ROOT\Interface\<lpszIID>\NumMethods - "", <nMethods>
	HKEY hKeyMethods;
	if (RegCreateKeyEx(hKeyInterface, 
			_T("NumMethods"), 
			NULL, _T(""), REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, 
			&hKeyMethods, &dwDisposition)!=ERROR_SUCCESS) {
		RegCloseKey(hKeyInterface);
		return E_UNEXPECTED;
		}

	wsprintf(szKey, "%d", nMethods);
	if (RegSetValueEx(hKeyMethods, _T(""), NULL, REG_SZ, (BYTE*) szKey, (lstrlen(szKey)+1)*sizeof(TCHAR))!=ERROR_SUCCESS) {
		RegCloseKey(hKeyInterface);
		RegCloseKey(hKeyMethods);
		return E_UNEXPECTED;
		}

	// Write: HKEY_CLASSES_ROOT\Interface\<lpszIID>\ProxyStubClsid32 - "", <lpszPSCLSID>
	HKEY hKeyPSCLSID;
	if (RegCreateKeyEx(hKeyInterface, 
			_T("ProxyStubClsid32"), 
			NULL, _T(""), REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, 
			&hKeyPSCLSID, &dwDisposition)!=ERROR_SUCCESS) {
		RegCloseKey(hKeyInterface);
		RegCloseKey(hKeyMethods);
		return E_UNEXPECTED;
		}

	if (RegSetValueEx(hKeyPSCLSID, _T(""), NULL, REG_SZ, (BYTE*) lpszPSCLSID, (lstrlen(lpszPSCLSID)+1)*sizeof(TCHAR))!=ERROR_SUCCESS) {
		RegCloseKey(hKeyInterface);
		RegCloseKey(hKeyMethods);
		RegCloseKey(hKeyPSCLSID);
		return E_UNEXPECTED;
		}
	RegCloseKey(hKeyInterface);
	RegCloseKey(hKeyMethods);
	RegCloseKey(hKeyPSCLSID);
	return NO_ERROR;
}

HRESULT UnregisterInterface(LPCTSTR lpszIID) {
	TCHAR szKey[120];
	TCHAR szKeyTemp[120];

	lstrcpy(szKey, _T("Interface\\"));
	lstrcat(szKey, lpszIID);

	lstrcpy(szKeyTemp, szKey);
	lstrcat(szKeyTemp, _T("\\NumMethods"));
	if (RegDeleteKey(HKEY_CLASSES_ROOT, szKeyTemp)!=ERROR_SUCCESS) {
		return E_UNEXPECTED;
		}

	lstrcpy(szKeyTemp, szKey);
	lstrcat(szKeyTemp, _T("\\ProxyStubClsid32"));
	if (RegDeleteKey(HKEY_CLASSES_ROOT, szKeyTemp)!=ERROR_SUCCESS) {
		return E_UNEXPECTED;
		}

	if (RegDeleteKey(HKEY_CLASSES_ROOT, szKey)!=ERROR_SUCCESS) {
		return E_UNEXPECTED;
		}
	return NO_ERROR;
}

STDAPI DllRegisterServer(void) {
	HKEY hKeyCLSID, hKeyInproc32;
	DWORD dwDisposition;

	if (RegCreateKeyEx(HKEY_CLASSES_ROOT, 
			_T("CLSID\\{30DF3432-0266-11cf-BAA6-00AA003E0EED}"), 
			NULL, _T(""), REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, 
			&hKeyCLSID, &dwDisposition)!=ERROR_SUCCESS) {
		return E_UNEXPECTED;
		}

	if (RegSetValueEx(hKeyCLSID, _T(""), NULL, REG_SZ, (BYTE*) "DB Sample ProxyStub", sizeof("DB Sample ProxyStub"))!=ERROR_SUCCESS) {
		RegCloseKey(hKeyCLSID);
		return E_UNEXPECTED;
		}

	if (RegCreateKeyEx(hKeyCLSID, 
			_T("InprocServer32"), 
			NULL, _T(""), REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, 
			&hKeyInproc32, &dwDisposition)!=ERROR_SUCCESS) {
		RegCloseKey(hKeyCLSID);
		return E_UNEXPECTED;
		}

	HMODULE hModule=GetModuleHandle(_T("IDBPS.DLL"));
	if (!hModule) {
		RegCloseKey(hKeyInproc32);
		RegCloseKey(hKeyCLSID);
		return E_UNEXPECTED;
		}
	TCHAR szName[MAX_PATH+1];
	if (GetModuleFileName(hModule, szName, sizeof(szName))==0) {
		RegCloseKey(hKeyInproc32);
		RegCloseKey(hKeyCLSID);
		return E_UNEXPECTED;
		}
	if (RegSetValueEx(hKeyInproc32, _T(""), NULL, REG_SZ, (BYTE*) szName, sizeof(TCHAR)*(lstrlen(szName)+1))!=ERROR_SUCCESS) {
		RegCloseKey(hKeyInproc32);
		RegCloseKey(hKeyCLSID);
		return E_UNEXPECTED;
		}
	RegCloseKey(hKeyInproc32);
	RegCloseKey(hKeyCLSID);

	RegisterInterface(_T("IDB"),       _T("{30DF3432-0266-11cf-BAA6-00AA003E0EED}"), 10, _T("{30DF3432-0266-11cf-BAA6-00AA003E0EED}"));
	RegisterInterface(_T("IDBAccess"), _T("{30DF3433-0266-11cf-BAA6-00AA003E0EED}"), 5,  _T("{30DF3432-0266-11cf-BAA6-00AA003E0EED}"));
	RegisterInterface(_T("IDBManage"), _T("{30DF3434-0266-11cf-BAA6-00AA003E0EED}"), 5,  _T("{30DF3432-0266-11cf-BAA6-00AA003E0EED}"));
	RegisterInterface(_T("IDBInfo"),   _T("{30DF3435-0266-11cf-BAA6-00AA003E0EED}"), 6,  _T("{30DF3432-0266-11cf-BAA6-00AA003E0EED}"));
	return NOERROR;
}

STDAPI DllUnregisterServer(void) {
	if (RegDeleteKey(HKEY_CLASSES_ROOT, 
			_T("CLSID\\{30DF3432-0266-11cf-BAA6-00AA003E0EED}\\InprocServer32"))!=ERROR_SUCCESS) {
		return E_UNEXPECTED;
		}
	if (RegDeleteKey(HKEY_CLASSES_ROOT, 
			_T("CLSID\\{30DF3432-0266-11cf-BAA6-00AA003E0EED}"))!=ERROR_SUCCESS) {
		return E_UNEXPECTED;
		}
	UnregisterInterface(_T("{30DF3432-0266-11cf-BAA6-00AA003E0EED}"));
	UnregisterInterface(_T("{30DF3433-0266-11cf-BAA6-00AA003E0EED}"));
	UnregisterInterface(_T("{30DF3434-0266-11cf-BAA6-00AA003E0EED}"));
	UnregisterInterface(_T("{30DF3435-0266-11cf-BAA6-00AA003E0EED}"));
	return NOERROR;
}
