//
// ExtCounters 
//
#ifndef _EXTCNTRS
#define _EXTCNTRS

#include "PerfIntf.h"

//
// CPerfmonObject represents a custom object being added as a perfmon counter.  This class
// contains information about the custom object needed to interface between the collection 
// interface (IPerfmonObject) and performance monitor
//
class CPerfmonObject
{
public:
	CPerfmonObject();
	virtual ~CPerfmonObject(); 

	//
	// This method attempts to create the object specified by the clsid. This object is used
	// to collect the data. Initialization is done here rather than in the constructor so that errors can be
	// returned to the caller.  
	//
	bool Init(LPWSTR pAppName); 

	long                       GetSizeNeeded() const  { return m_sizeNeeded; }
	PERF_OBJECT_TYPE		  *GetObjectType()        { return &m_perfObjectType; }
	PERF_COUNTER_DEFINITION   *GetCounterDefs() const { return m_pPerfCounterDefs; }
	PERF_COUNTER_BLOCK		  *GetCounterBlock()      { return &m_perfCounterBlock; }
	long					   GetNumCounters() const { return m_numCounters; }
	vector<IPerfmonCounter *>& GetCounterInterfaces() { return m_counters; }
	void SetDataAndAdvancePointer(VARIANT& v, LPDWORD& pCounterData);
	BOOL operator==(const CPerfmonObject& rhs) const { return m_pPerfmonObject == rhs.m_pPerfmonObject; }

private:
	void InitializePerfmonData(DWORD dwFirstCounter, DWORD dwFirstHelp);
	DWORD CounterSizeFromVarType(VARTYPE varType);


	IPerfmonObject           *m_pPerfmonObject;    // the COM interface to use for collecting the data
	PERF_OBJECT_TYPE          m_perfObjectType;    // the perfmon structure describing this object
	PERF_COUNTER_DEFINITION  *m_pPerfCounterDefs;  // an array of perfmon structures describing each counter
	PERF_COUNTER_BLOCK        m_perfCounterBlock;  // the perfmon structure that is placed just before the counter data
	long                      m_sizeNeeded;        // the size of the block of memory handed to perfmon
	long                      m_numCounters;       // the number of counters
	vector<IPerfmonCounter *> m_counters;          // interface pointers for all the 
};


BOOL operator<(CPerfmonObject const& lhs, CPerfmonObject const& rhs);

//
// CExtCountersModule is the module class for the dll.  An instance of this class is delcared
// globally (cntrsModule).
//
class CExtCountersModule
{
public:

	bool InitPerfmonObject(LPWSTR pAppName);
	CPerfmonObject& GetPerfmonObject() { return m_perfmonObject; }

private:
	CPerfmonObject m_perfmonObject;
};

#endif // _EXTCNTRS