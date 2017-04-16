typedef DWORD (WINAPI *CONCURRENT_EXECUTION_ROUTINE)
        (LPVOID lpParameterBlock);
typedef DWORD (WINAPI *CONCURRENT_FINISHING_ROUTINE)
		(LPVOID lpParameterBlock,LPVOID lpResultCode);
     



class 
#ifdef APP_CALLING
__declspec(dllimport)
#else
__declspec(dllexport) 
#endif
ConcurrentExecution
{
private:
	HANDLE *m_hThreadArray;
	DWORD *m_hObjectArray;
	int m_iMaxArraySize;
	int m_iCurrentNumberOfThreads;
// iCurrentArraySize is the current number of
// entries in the thread array. We allow a
// "balance set manager" to dynamically update this
// value as the balance changes
	int m_iCurrentArraySize;
public:
	ConcurrentExecution(int iMaxNumberOfThreads);
	~ConcurrentExecution();
	int DoForAllObjects(int iNoOfObjects,long *ObjectArray,
		                 CONCURRENT_EXECUTION_ROUTINE pObjectProcessor,
						 CONCURRENT_FINISHING_ROUTINE pObjectTerminated);
    BOOL DoSerial(int iNoOfObjects, long *ObjectArray,
                  CONCURRENT_EXECUTION_ROUTINE pObjectProcessor,
                  CONCURRENT_FINISHING_ROUTINE pObjectTerminated);
    BOOL AddObject(void *pObject);
};
