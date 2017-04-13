#include <atldbcli.h>

#if 1
class CProduct
{
public:
	long    nProductID;
	char*   pName;
	long    nUnitsInStock;
	long    nReorderLevel;

	BEGIN_ACCESSOR_MAP(CProduct, 1)
		BEGIN_ACCESSOR(0, false)
			COLUMN_ENTRY(1, nProductID)
			COLUMN_ENTRY_TYPE(2, DBTYPE_STR | DBTYPE_BYREF, pName)
			COLUMN_ENTRY(7, nUnitsInStock)
			COLUMN_ENTRY(9, nReorderLevel)
		END_ACCESSOR();
	END_ACCESSOR_MAP()

	DEFINE_COMMAND(CProduct, _T("SELECT * FROM Products"))
};
#else
class CProduct
{
public:
	long id;
	char Name[80];
	char PhoneNumber[50];
	char Location[50];
	char Title[50];
	char Company[50];
	char Email[50];

	BEGIN_COLUMN_MAP(CProduct)
		COLUMN_ENTRY(1, id)
		COLUMN_ENTRY(2, Name)
		COLUMN_ENTRY(3, PhoneNumber)
		COLUMN_ENTRY(4, Location)
		COLUMN_ENTRY(5, Title)
		COLUMN_ENTRY(6, Company)
		COLUMN_ENTRY(7, Email)
	END_COLUMN_MAP()
};
#endif

void ProcessRecord(CProduct& product);

class CMyRowset : public CRowset
{
public:
	HRESULT MoveAndProcess()
	{
		CProduct product;
		HRESULT hr;
		hr = MoveNext();
		if (hr == S_OK)
		{
			hr = GetDataHere(&product);
			ATLASSERT(SUCCEEDED(hr));
			ProcessRecord(product);
		}
		return hr;
	}
};

ULONG WINAPI ReadTable(CTable<CAccessor<CProduct>, CMyRowset>* pProduct)
{
	CMyRowset rowset = *((CMyRowset*)pProduct);
	HRESULT   hr;
	ULONG     nRows = 0;

	while ((hr=rowset.MoveAndProcess()) == S_OK)
	{
		nRows++;
	}
	ATLTRACE("Thread %d processed %d records. Last HRESULT = %X\n", GetCurrentThreadId(), nRows, hr);
	return nRows;
}

void ProcessRecord(CProduct& product)
{
	DWORD dwThreadId = GetCurrentThreadId();
	ATLTRACE("%d, %4d, %s\n", dwThreadId, product.nProductID, product.pName);
}

HRESULT ReadRecords(int nThreads, DWORD* pdwTime, DWORD* pRowsProcessed)
{
	CDataSource     db;
	CSession        session;
	CTable<CAccessor<CProduct>, CMyRowset>  product;
	HRESULT         hr;
	DWORD           dwTime;

	ATLTRACE("DoStuff: Started\n");
	hr = db.Open(_T("MSDASQL"), _T("OLE_DB_NWind_Jet"));
	ATLASSERT(SUCCEEDED(hr));
	if (FAILED(hr))
		return hr;

	hr = session.Open(db);
	ATLASSERT(SUCCEEDED(hr));
	if (FAILED(hr))
		return hr;

	CDBPropSet propset(DBPROPSET_ROWSET);
	propset.AddProperty(DBPROP_CANHOLDROWS, true);

	hr = product.Open(session, _T("Products"), &propset);
	ATLASSERT(SUCCEEDED(hr));
	if (FAILED(hr))
		return hr;

	DWORD  idThread;
	int i;
	HANDLE* phThread = new HANDLE[nThreads];
	if (phThread == NULL)
		return E_FAIL;

	dwTime = GetTickCount();
	for (i=0; i<nThreads; i++)
	{
		*(phThread+i) = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ReadTable, &product, 0, &idThread);
		if (*(phThread+i) == NULL)
			ATLTRACE(_T("Couldn't create thread %d\n"), i);
	}

	// Ensure all threads are finished before we end
	WaitForMultipleObjects(nThreads, phThread, TRUE, INFINITE);
	// Return the total time
	*pdwTime = GetTickCount() - dwTime;

	DWORD nTotalRows = 0, nRows;
	for (i=0; i<nThreads; i++)
	{
		GetExitCodeThread(*(phThread + i), &nRows);
		nTotalRows += nRows;
		CloseHandle(*(phThread + i));
	}
	*pRowsProcessed = nTotalRows;
	ATLTRACE("DoStuff: Ended\n");
	return S_OK;
}
