#define UNICODE
#define _UNICODE
#include <windows.h>
#include <initguid.h>
#include <tchar.h>
#include <sqloleid.h>
#include <sqlole.h>

int main (void)
{
	HRESULT hr;
	if FAILED(hr = CoInitialize (NULL))
	{
		_tprintf(TEXT("CoInitialize Failed\n"));
		return (0);
	}

	LPSQLOLESERVER pSQLServer = NULL;
	if FAILED(hr = CoCreateInstance(CLSID_SQLOLEServer, NULL, CLSCTX_INPROC_SERVER,
		IID_ISQLOLEServer, (LPVOID*)&pSQLServer))
	{
		_tprintf(TEXT("CoCreateInstance Failed\n"));
		return (0);
	}

	pSQLServer->SetLoginTimeout(10);
	
	if FAILED(hr = pSQLServer->Connect(TEXT(""),TEXT("sa"),TEXT("")))
	{
		_tprintf(TEXT("Connect failed\n"));
		LPSUPPORTERRORINFO pSEI = NULL;
		if SUCCEEDED(pSQLServer->QueryInterface(IID_ISupportErrorInfo, (LPVOID*)&pSEI))
		{
			if SUCCEEDED(pSEI->InterfaceSupportsErrorInfo(IID_ISQLOLEServer))
			{
				LPERRORINFO pEI = NULL;
				GetErrorInfo (0, &pEI);
				SQLOLE_BSTR strDescription, strSource;
				pEI->GetDescription (&strDescription);
				pEI->GetSource (&strSource);
				_tprintf(TEXT("%s returned error %d: %s\n"),
					strSource,
					SCODE_CODE(hr),
					strDescription);
				pEI->Release ();
			}
		}
		else
		{
			_tprintf(TEXT("Error %d\n"), HRESULT_CODE(hr));
		}
		pSEI->Release ();
	} 
	else
	{
		SQLOLE_BSTR str;
		pSQLServer->GetVersionString(&str);
		_tprintf(TEXT("%s\n"),str);
		LPSQLOLEAPPLICATION pApp = NULL;
		pSQLServer->GetApplication(&pApp);
		pApp->GetName(&str);
		_tprintf(TEXT("%s\n"),str);
		SysFreeString((BSTR)str);

		LONG ver;
		pSQLServer->GetVersionMajor(&ver);
		_tprintf(TEXT("%d\n"),ver);

	}

	pSQLServer->Release ();
	
	CoUninitialize ();
	return (0);
}
