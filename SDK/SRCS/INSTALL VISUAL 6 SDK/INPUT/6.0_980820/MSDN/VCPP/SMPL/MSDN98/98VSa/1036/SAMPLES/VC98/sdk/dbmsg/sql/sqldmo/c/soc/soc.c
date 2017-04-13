#include <stdio.h>

#define INITGUID
#define INC_OLE2
#include <windows.h>

#include <sqloleid.h>
#include <sqlole.h>

// This sample demonstrates how to program SQLOLE in C.  Differences from C++ are noted.
int main (void)
{
	// Variables must be defined at beginning of block, rather than at point of initialization.
	// (If this is done later, the compiler error message is very unhelpful in this case).
	LPSQLOLESERVER pSQL = NULL;
	HRESULT hr;
	if FAILED(hr = CoInitialize (NULL))
	{
		printf("CoInitialize Failed\n");
		return (0);
	}
	printf("Hello\n");

	// Must use '&' operator on IID's in C; C++ uses references for these.
	if FAILED(hr = CoCreateInstance(&CLSID_SQLOLEServer, NULL, CLSCTX_INPROC_SERVER,
		&IID_ISQLOLEServer, (LPVOID*)&pSQL))
	{
		printf("CoCreateInstance Failed\n");
		return (0);
	}

	// The returned pointer from SQLOLE is interpreted as a pointer to an array of function pointers,
	// which are the C equivalent of C++'s "virtual function table", or vtbl.  Hence in this code,
	// pSQL is a pointer to a pointer to a function table, and the additional indirection of including
	// the actual vtbl pointer (->lpVtbl) is necessary.  Also, the pSQL pointer must be explicitly passed
	// to the called function in C; in C++, this is done implicitly as the "this" pointer.
	pSQL->lpVtbl->SetLoginTimeout(pSQL, 10);

	if FAILED(hr = pSQL->lpVtbl->Connect(pSQL, "tedhar2","sa",""))
	{
		HRESULT h = HRESULT_CODE(hr);
		printf("Connect failed\n");
	}
	else
	{
		SQLOLE_BSTR name;
		pSQL->lpVtbl->GetName(pSQL, &name);
		printf("%s\n", name);
		SQLOLEFreeString(name);
	}

	pSQL->lpVtbl->Release(pSQL);
	CoUninitialize ();
	printf("Goodbye\n");
	return (0);
}
