#include "stdafx.h"
#include "dbsrvimp.h"

ULONG g_dwRefCount=0;

// Create a new database object and return a pointer to it
HRESULT CDBSrvFactory::CreateInstance(IUnknown *pUnkOuter, REFIID riid, void** ppObject) {
	if (pUnkOuter!=NULL) {
		return CLASS_E_NOAGGREGATION;
		}
  CDB* pDB=new CDB;
	if (FAILED(pDB->QueryInterface(riid, ppObject))) {
		delete pDB;
		*ppObject=NULL;
		return E_NOINTERFACE;
		}
  return NO_ERROR;
}

HRESULT	CDBSrvFactory::LockServer(BOOL fLock) {
	if (fLock) {
		InterlockedIncrement((long*) &g_dwRefCount);
		}
	else {
		InterlockedDecrement((long*) &g_dwRefCount);
		}
	return NO_ERROR;
}

CDBSrvFactory::CDBSrvFactory() {
	m_dwRefCount=0;
}

HRESULT CDBSrvFactory::QueryInterface(REFIID riid, void** ppObject) {
	if (riid==IID_IUnknown || riid==IID_IClassFactory) {
		*ppObject=(IDB*) this;
		}
	else {
		return E_NOINTERFACE;
		}
	AddRef();
	return NO_ERROR;
}

ULONG CDBSrvFactory::AddRef() {
#ifndef LOCALSERVER
	InterlockedIncrement((long*) &g_dwRefCount);
#endif
	InterlockedIncrement((long*) &m_dwRefCount);
	return m_dwRefCount;
}

ULONG CDBSrvFactory::Release() {
	ULONG dwRefCount=m_dwRefCount-1;
#ifndef LOCALSERVER
	InterlockedDecrement((long*) &g_dwRefCount);
#endif
	if (InterlockedDecrement((long*) &m_dwRefCount)==0) {
		delete this;
		return 0;
		}
	return dwRefCount;
}

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, void** ppObject) {
	if (rclsid==CLSID_DBSAMPLE) {
		CDBSrvFactory *pFactory= new CDBSrvFactory;
		if (FAILED(pFactory->QueryInterface(riid, ppObject))) {
			delete pFactory;
			*ppObject=NULL;
			return E_INVALIDARG;
			}
		}
	else { // here you could check for additional CLSID's you DLL may provide
		return CLASS_E_CLASSNOTAVAILABLE;
		}
	return NO_ERROR;
}

HRESULT _stdcall DllCanUnloadNow() {
	if (g_dwRefCount) {
		return S_FALSE;
		}
	else {
		return S_OK;
		}
}

STDAPI DllRegisterServer(void) {
	HKEY hKeyCLSID, hKeyInproc32;
	DWORD dwDisposition;

	if (RegCreateKeyEx(HKEY_CLASSES_ROOT, 
			_T("CLSID\\{30DF3430-0266-11cf-BAA6-00AA003E0EED}"), 
			NULL, _T(""), REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, 
			&hKeyCLSID, &dwDisposition)!=ERROR_SUCCESS) {
		return E_UNEXPECTED;
		}

	if (RegSetValueEx(hKeyCLSID, _T(""), NULL, REG_SZ, (BYTE*) _T("DB Sample Server"), sizeof(_T("DB Sample Server")))!=ERROR_SUCCESS) {
		RegCloseKey(hKeyCLSID);
		return E_UNEXPECTED;
		}

	HMODULE hModule;
#ifndef LOCALSERVER
	if (RegCreateKeyEx(hKeyCLSID, 
			"InprocServer32", 
			NULL, _T(""), REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, 
			&hKeyInproc32, &dwDisposition)!=ERROR_SUCCESS) {
		RegCloseKey(hKeyCLSID);
		return E_UNEXPECTED;
		}

	hModule=GetModuleHandle(_T("DB.DLL"));
	if (!hModule) {
		RegCloseKey(hKeyInproc32);
		RegCloseKey(hKeyCLSID);
		return E_UNEXPECTED;
		}
#else
	if (RegCreateKeyEx(hKeyCLSID, 
			_T("LocalServer32"), 
			NULL, _T(""), REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, 
			&hKeyInproc32, &dwDisposition)!=ERROR_SUCCESS) {
		RegCloseKey(hKeyCLSID);
		return E_UNEXPECTED;
		}
	hModule=NULL; // GetModuleFileName will return name of current process
#endif
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
	return NOERROR;
}

STDAPI DllUnregisterServer(void) {
	if (RegDeleteKey(HKEY_CLASSES_ROOT, 
			_T("CLSID\\{30DF3430-0266-11cf-BAA6-00AA003E0EED}\\InprocServer32"))!=ERROR_SUCCESS) {
		return E_UNEXPECTED;
		}
	if (RegDeleteKey(HKEY_CLASSES_ROOT, 
			_T("CLSID\\{30DF3430-0266-11cf-BAA6-00AA003E0EED}"))!=ERROR_SUCCESS) {
		return E_UNEXPECTED;
		}
	return NOERROR;
}
