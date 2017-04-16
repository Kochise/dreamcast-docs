// RegisterPerfmonObject.cpp : Implementation of CRegisterPerfmonObject
#include "stdafx.h"
#include "RegPCtrs.h"
#include "RegPObj.h"
#include "PerfIntf.h" 
#include "PerfIds.c"

/////////////////////////////////////////////////////////////////////////////
// CRegisterPerfmonObject

const CString CRegisterPerfmonObject::hdrFileName = "counters.h";
const CString CRegisterPerfmonObject::iniFileName = "counters.ini";
const CString CRegisterPerfmonObject::english = "009";
const CString CRegisterPerfmonObject::define  = "#define ";
const CString CRegisterPerfmonObject::name  = "_name=";
const CString CRegisterPerfmonObject::help  = "_help=";

STDMETHODIMP CRegisterPerfmonObject::Register(BSTR appName, BSTR collectionGUID)
{
	m_appName = appName;
	m_strClsid = collectionGUID;

	_bstr_t strClsid(collectionGUID);
	HRESULT hRes = CLSIDFromString(strClsid, &m_clsid);

	AddPerformanceKey();
	AddPerformanceData();
	return S_OK;
}

STDMETHODIMP CRegisterPerfmonObject::Unregister(BSTR appName)
{
	m_appName = appName;
	UnlodCtr();
	return S_OK;
}

//TODO: return errors, etc ...
bool CRegisterPerfmonObject::AddPerformanceKey()
{
	// add the application key
	CRegKey appKey;
	CString appKeyName = "SYSTEM\\CurrentControlSet\\Services\\" + m_appName;
	LONG status = appKey.Create(HKEY_LOCAL_MACHINE, appKeyName);

	if (status != ERROR_SUCCESS) return false;


	// add the performance subkey
	CRegKey perfKey;
	status = perfKey.Create(HKEY_LOCAL_MACHINE, appKeyName + "\\Performance");
	if (status != ERROR_SUCCESS) 
	{
		appKey.Close();
		return false;
	}

	// add keys to hook the extcounters dll
	perfKey.SetValue("ClosePerfData", "Close");     
	perfKey.SetValue("CollectPerfData", "Collect");
	perfKey.SetValue("OpenPerfData", "Open");
	perfKey.SetValue("extcounters.dll", "Library");
	perfKey.SetValue((LPCTSTR)m_strClsid, "CollectionComponent"); 

	// add the linkage key
	CRegKey linkKey;
	status = linkKey.Create(HKEY_LOCAL_MACHINE, appKeyName + "\\Linkage");
	if (status != ERROR_SUCCESS) 
	{
		appKey.Close();
		perfKey.Close();
		return false;
	}

	long i = 10;
	_bstr_t temp(m_appName);
	LPWSTR pTemp = (wchar_t *)temp;
	RegSetValueEx(linkKey.m_hKey, "Export", 0, REG_BINARY, (LPBYTE)pTemp, (temp.length()*2)+1); //why do I have to *2 for multi-byte?
	return true;
}

bool CRegisterPerfmonObject::AddPerformanceData()
{
	//
	// Create the collection component
	//
	IPerfmonObject *pPerfmonObject = NULL;
	HRESULT hRes = CoCreateInstance(m_clsid, NULL, CLSCTX_SERVER, IID_IPerfmonObject, (void**)&pPerfmonObject);

	if (FAILED(hRes)) return false;

	// 
	// Generate the header file and the .ini file and call the lodctr api
	//
	CStdioFile hdrFile(hdrFileName,  CFile::modeCreate | CFile::modeWrite | CFile::typeText );
	CStdioFile iniFile(iniFileName,  CFile::modeCreate | CFile::modeWrite | CFile::typeText );

	//
	// Intro sections of .ini file
	//
	iniFile.WriteString("[info]\n");
	iniFile.WriteString(CString("drivername=") + m_appName + CString("\n"));
	iniFile.WriteString(CString("symbolfile=") + hdrFileName + CString("\n\n"));
	iniFile.WriteString("[languages]\n");
	iniFile.WriteString(english + CString("=English\n\n"));
	iniFile.WriteString("[text]\n");

	long objectIndex = 0;
	hRes = pPerfmonObject->GetIndex(&objectIndex);
	_ASSERTE(SUCCEEDED(hRes));
	
	BSTR bstrName;
	hRes = pPerfmonObject->GetName(&bstrName); 
    _ASSERTE(SUCCEEDED(hRes));

	BSTR bstrHelpText;
	hRes = pPerfmonObject->GetHelp(&bstrHelpText);
	_ASSERTE(SUCCEEDED(hRes));
	
	LPTSTR pszName     = ConvertBSTRToString(bstrName);
	LPTSTR pszHelpText = ConvertBSTRToString(bstrHelpText);

	//
	// Object #define
	//
	hdrFile.WriteString(define);
	hdrFile.WriteString(pszName); 
	CString objectNumStr; objectNumStr.Format(" %ld\n", objectIndex);
	hdrFile.WriteString(objectNumStr);
	
	//
	// object name, and help
	//
	iniFile.WriteString(pszName); iniFile.WriteString(CString("_")+english); iniFile.WriteString(name); iniFile.WriteString(pszName);     iniFile.WriteString("\n");
	iniFile.WriteString(pszName); iniFile.WriteString(CString("_")+english); iniFile.WriteString(help); iniFile.WriteString(pszHelpText); iniFile.WriteString("\n");

	delete [] pszName;
	delete [] pszHelpText;

	//
	// Iterate through each counter, adding entries to the header and ini files
	//
	VARIANT v;
	::VariantInit(&v);

	IUnknown *pUnk = NULL;
	hRes = pPerfmonObject->GetCounters(&pUnk);
	_ASSERTE(SUCCEEDED(hRes));

	IEnumVARIANT *pCounters = NULL;
	hRes = pUnk->QueryInterface(IID_IEnumVARIANT, (void **)&pCounters);
	_ASSERTE(SUCCEEDED(hRes));

	pUnk->Release();

	long i = 0;
	while (pCounters->Next(1, &v, NULL) == S_OK)
	{
		IDispatch *pDispatch = V_DISPATCH(&v);;
		IPerfmonCounter *pICounter = NULL;

		hRes = pDispatch->QueryInterface(IID_IPerfmonCounter, (void **)&pICounter);
		_ASSERTE(SUCCEEDED(hRes));
		
		long counterIndex = 0;
		hRes = pICounter->GetIndex(&counterIndex);
		_ASSERTE(SUCCEEDED(hRes));

		hRes = pICounter->GetName(&bstrName);
		_ASSERTE(SUCCEEDED(hRes));

		hRes = pICounter->GetHelp(&bstrHelpText);
		_ASSERTE(SUCCEEDED(hRes));

		pszName     = ConvertBSTRToString(bstrName);
		pszHelpText = ConvertBSTRToString(bstrHelpText);

		//
		// Counter #define
		//
		hdrFile.WriteString(define);
		hdrFile.WriteString(pszName); 
		CString counterNumStr; counterNumStr.Format(" %ld\n", counterIndex);
		hdrFile.WriteString(counterNumStr);

		//
		// object name, and help
		//
		iniFile.WriteString(pszName); iniFile.WriteString(CString("_")+english); iniFile.WriteString(name); iniFile.WriteString(pszName);     iniFile.WriteString("\n");
		iniFile.WriteString(pszName); iniFile.WriteString(CString("_")+english); iniFile.WriteString(help); iniFile.WriteString(pszHelpText); iniFile.WriteString("\n");

		delete [] pszName;
		delete [] pszHelpText;

		pICounter->Release();

		//
		// Clear the variant so we can reuse it
		//
		::VariantClear(&v);
	}

	pPerfmonObject->Release(); 

	//
	// Call unlodctr/lodctr to add the counter data to the registry
	//
	UnlodCtr();
	LodCtr();

	return true;
}

void CRegisterPerfmonObject::UnlodCtr()
{
	WinExec(CString("unlodctr ") + m_appName, SW_HIDE);
}

void CRegisterPerfmonObject::LodCtr()
{
	WinExec(CString("lodctr ") + iniFileName, SW_HIDE);
}

STDMETHODIMP CRegisterPerfmonObject::InterfaceSupportsErrorInfo(REFIID riid)
{
	static const IID* arr[] = 
	{
		&IID_IRegisterPerfmonObject,
	};
	for (int i=0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		if (InlineIsEqualGUID(*arr[i],riid))
			return S_OK;
	}
	return S_FALSE;
}
