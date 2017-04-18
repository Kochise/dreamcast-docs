//
// Ext Counters
//
#include "stdafx.h"
#include <winperf.h>
#include "ExtCounters.h"
#include "PerfIds.c"    

CComModule _Module; // so ATL can build
//
// CPerfmonObject
//
CPerfmonObject::CPerfmonObject()
	: m_pPerfmonObject(NULL),
	  m_pPerfCounterDefs(NULL),
	  m_numCounters(0),
	  m_counters()
{
}

CPerfmonObject::~CPerfmonObject()
{
	if (m_pPerfCounterDefs)
	{
		delete [] m_pPerfCounterDefs;
	}

	//
	// Release the counter interface pointers
	//
	vector<IPerfmonCounter *>::const_iterator counterIter;
	for (counterIter = m_counters.begin(); counterIter != m_counters.end(); counterIter++)
	{
		IPerfmonCounter *pCounter = *counterIter;
		pCounter->Release();
	}

	if (m_pPerfmonObject)
	{
		m_pPerfmonObject->Release();
	}
}

bool CPerfmonObject::Init(LPWSTR pAppName)
{
	HRESULT hRes = S_OK;

	//
	// Open the registry key for this app
	//
	CRegKey hKeyDriverPerf;
	_bstr_t appName(pAppName);
	_bstr_t appPerfKey("SYSTEM\\CurrentControlSet\\Services\\"+ appName + "\\Performance");

	LONG status = hKeyDriverPerf.Open(HKEY_LOCAL_MACHINE, appPerfKey);
    if (status != ERROR_SUCCESS)
	{
		hKeyDriverPerf.Close();
		return false;
	}

	//
	// Get the clsid of the collection component from the registry
	//
	CLSID clsid;
	const unsigned long clsidStrSize = 128;
	char clsidStr[clsidStrSize];
	status = hKeyDriverPerf.QueryValue(clsidStr, "CollectionComponent", const_cast<unsigned long *>(&clsidStrSize));
	if (status != ERROR_SUCCESS)
	{
		hKeyDriverPerf.Close();
		return false;
	}

	hRes = AfxGetClassIDFromString(clsidStr, &clsid);
	if (FAILED(hRes)) return false;

	//
	// Create the component that will supply us with the perfmon object interface
	//
	hRes = CoCreateInstance(clsid, NULL, CLSCTX_SERVER, IID_IPerfmonObject, (void**)&m_pPerfmonObject);

	if (FAILED(hRes)) return false;

	//
	// Initialize lpPerfmonData.  Read the first counter and help values
	// from the registry and initialize the object and counter data structures
	// for use during collection.
	//
    DWORD dwFirstCounter;
    DWORD dwFirstHelp;

	status = hKeyDriverPerf.QueryValue(dwFirstCounter, "First Counter");
	if (status != ERROR_SUCCESS)
	{
		hKeyDriverPerf.Close();
		return false;
	}

	status = hKeyDriverPerf.QueryValue(dwFirstHelp, "First Help");
	if (status != ERROR_SUCCESS)
	{
		hKeyDriverPerf.Close();
		return false;
	}
     
 	InitializePerfmonData(dwFirstCounter, dwFirstHelp);

    hKeyDriverPerf.Close(); 

	return true;
}

void CPerfmonObject::InitializePerfmonData(DWORD dwFirstCounter, DWORD dwFirstHelp)
{
	long objectIndex = 0;
	HRESULT hRes = S_OK;

	//
	// Initialize PERF_OBJECT_TYPE. Get the object index and the number of counters from
	// the collection component
	//
	hRes = m_pPerfmonObject->GetIndex(&objectIndex);
	_ASSERTE(SUCCEEDED(hRes));

	hRes = m_pPerfmonObject->GetNumCounters(&m_numCounters);
	_ASSERTE(SUCCEEDED(hRes));

	//
	// This is the total length of the data passed to perfmon.  At this point we compute,
	// the length of the known structures.  Later, we will add the length of the data
	//
	long structureLength = sizeof(PERF_OBJECT_TYPE) + 
		                     (m_numCounters * sizeof(PERF_COUNTER_DEFINITION));

	m_perfObjectType.TotalByteLength      = structureLength;
	m_perfObjectType.DefinitionLength     = structureLength;
	m_perfObjectType.HeaderLength         = sizeof(PERF_OBJECT_TYPE);
	m_perfObjectType.ObjectNameTitleIndex = (objectIndex + dwFirstCounter);
	m_perfObjectType.ObjectNameTitle      = NULL;
	m_perfObjectType.ObjectHelpTitleIndex = (objectIndex + dwFirstHelp);
	m_perfObjectType.ObjectHelpTitle      = NULL;
	m_perfObjectType.DetailLevel          = PERF_DETAIL_NOVICE;
	m_perfObjectType.NumCounters          = m_numCounters;
	m_perfObjectType.DefaultCounter       = 0;
	m_perfObjectType.NumInstances         = 0;
	m_perfObjectType.CodePage             = 0;
	m_perfObjectType.PerfTime.LowPart     = 0; 
	m_perfObjectType.PerfTime.HighPart    = 0; 
	m_perfObjectType.PerfFreq.LowPart     = 0;
	m_perfObjectType.PerfTime.HighPart    = 0;
	
	//
	// Initialize the PERF_COUNTER_DEFINITION structures
	//
	_ASSERTE(!m_pPerfCounterDefs);
	m_pPerfCounterDefs = new PERF_COUNTER_DEFINITION[m_numCounters];

	//
	// Get the enumeration of counters interface
	//
	VARIANT v;
	::VariantInit(&v);

	IUnknown *pUnk = NULL;
	hRes = m_pPerfmonObject->GetCounters(&pUnk);
	_ASSERTE(SUCCEEDED(hRes));

	IEnumVARIANT *pCounters = NULL;
	hRes = pUnk->QueryInterface(IID_IEnumVARIANT, (void **)&pCounters);
	_ASSERTE(SUCCEEDED(hRes));

	pUnk->Release();

	//
	// The size of the data to be collected must include the PERF_COUNTER_BLOCK
	// structure
	//
	long sizeofData = sizeof(PERF_COUNTER_BLOCK);

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

		VARTYPE varType;
		hRes = pICounter->GetDataType((short *)&varType);
		_ASSERTE(SUCCEEDED(hRes));

		m_pPerfCounterDefs[i].ByteLength             = sizeof(PERF_COUNTER_DEFINITION);
		m_pPerfCounterDefs[i].CounterNameTitleIndex  = (counterIndex + dwFirstCounter);
		m_pPerfCounterDefs[i].CounterNameTitle       = NULL;
		m_pPerfCounterDefs[i].CounterHelpTitleIndex  = (counterIndex + dwFirstHelp);
		m_pPerfCounterDefs[i].CounterHelpTitle       = NULL;
		m_pPerfCounterDefs[i].DefaultScale           = 0;  
		m_pPerfCounterDefs[i].DetailLevel            = PERF_DETAIL_NOVICE;
		m_pPerfCounterDefs[i].CounterType            = PERF_COUNTER_RAWCOUNT;
		m_pPerfCounterDefs[i].CounterSize            = CounterSizeFromVarType(varType);
		m_pPerfCounterDefs[i].CounterOffset          = sizeofData;

		i++;
		sizeofData += CounterSizeFromVarType(varType);

		//
		// Save the inteface pointer on a vector so we don't have to get it from the
		// collection component every time Collect is called
		// 
		m_counters.push_back(pICounter);

		//
		// Clear the variant so we can reuse it
		//
		::VariantClear(&v);
	}

	pCounters->Release();

	structureLength += sizeofData;

	//
	// Initialize the PERF_COUNTER_BLOCK structure and fix up the sizes we
	// couldn't finish before
	//
	m_perfCounterBlock.ByteLength = sizeofData;
	m_perfObjectType.TotalByteLength      = structureLength;

	//
	// Save the size needed so we don't have to recompute it during collection
	//
	m_sizeNeeded = structureLength;
}

DWORD CPerfmonObject::CounterSizeFromVarType(VARTYPE varType)
{
	// TODO: support other types
	return sizeof(DWORD);
}

void CPerfmonObject::SetDataAndAdvancePointer(VARIANT& v, LPDWORD& pCounterData)
{
	*pCounterData = V_I4(&v); //TODO: support other types
	pCounterData++;

	return;
}

//
// CExtCountersModule
//
bool CExtCountersModule::InitPerfmonObject(LPWSTR pAppName)
{
	return m_perfmonObject.Init(pAppName);
}

//
// DLL Entry Points
//
PM_OPEN_PROC    OpenFinPerfData;
PM_COLLECT_PROC CollectFinPerfData;
PM_CLOSE_PROC   CloseFinPerfData;

CExtCountersModule cntrsModule;

DWORD APIENTRY OpenPerfData(LPWSTR lpDeviceNames)
{
	HRESULT hRes = S_OK;

	//
	// Initialize COM
	//
	hRes = CoInitializeEx(0, COINIT_MULTITHREADED);
	if (FAILED(hRes)) return hRes;

	//
	// Initialize the perfmon object in the module
	//
	if (!cntrsModule.InitPerfmonObject(lpDeviceNames)) return E_FAIL;

    return ERROR_SUCCESS;
}

DWORD APIENTRY CollectPerfData(
    LPWSTR  lpValueName,
    LPVOID  *lppData,
    LPDWORD lpcbTotalBytes,
    LPDWORD lpNumObjectTypes
)
{
	PERF_OBJECT_TYPE *pObjectType = (PERF_OBJECT_TYPE *) *lppData;

	CPerfmonObject& perfmonObject = cntrsModule.GetPerfmonObject();

    if ( *lpcbTotalBytes < perfmonObject.GetSizeNeeded() ) {
        *lpcbTotalBytes = (DWORD) 0;
        *lpNumObjectTypes = (DWORD) 0;
        return ERROR_MORE_DATA;
    }

    //
    // Copy the (constant, initialized) Object Type and counter definitions
    //  to the caller's data buffer
    //
    memmove(pObjectType,
       perfmonObject.GetObjectType(),
       sizeof(PERF_OBJECT_TYPE));

	PERF_COUNTER_DEFINITION *pCounterDef = (PERF_COUNTER_DEFINITION *) (&pObjectType[1]);

	memmove(pCounterDef,
       perfmonObject.GetCounterDefs(),
       (sizeof(PERF_OBJECT_TYPE) * perfmonObject.GetNumCounters()));

	PERF_COUNTER_BLOCK *pPerfCounterBlock = (PERF_COUNTER_BLOCK *) (&pCounterDef[perfmonObject.GetNumCounters()]);

	memmove(pPerfCounterBlock,
       perfmonObject.GetCounterBlock(),
       sizeof(PERF_COUNTER_BLOCK));

    LPDWORD pCounterData = (LPDWORD) (&pPerfCounterBlock[1]);

	//
	// Get the data for each counter
	//
	VARIANT v;
	::VariantInit(&v);

	vector<IPerfmonCounter *>& counters= perfmonObject.GetCounterInterfaces();
	vector<IPerfmonCounter *>::const_iterator counterIter;
	for (counterIter = counters.begin(); counterIter != counters.end(); counterIter++)
	{
		IPerfmonCounter *pCounter = *counterIter;
		pCounter->Collect(&v);
		perfmonObject.SetDataAndAdvancePointer(v, pCounterData);
	}

	//
	// Aim the pointer given to us by perfmon at the next available
	// byte
	//
    *lppData = (PVOID) ++pCounterData;
 
    *lpNumObjectTypes = 1; //We only support one object

    *lpcbTotalBytes = perfmonObject.GetSizeNeeded(); 

	return ERROR_SUCCESS;
}

DWORD APIENTRY ClosePerfData()
{
	CoUninitialize();
	return 0;
}
