// VBUTIL.C - Example DLL for Visual Basic applications.

//@B VBUtil
#include "vbutil.h"

HINSTANCE hInst;

// This function is the library entry point. It's technically 
// optional for 32-bit programs, but you'll have more options later 
// if you define it. 

BOOL WINAPI DllMain(HINSTANCE hInstA, DWORD dwReason, LPVOID lpvReserved)
{
	switch (dwReason) {
	case DLL_PROCESS_ATTACH:
		// The DLL is being mapped into the process's address space
		// Do any additional initialization here
		hInst = hInstA;
	   	break;

	case DLL_THREAD_ATTACH:
		// A thread is being created
	    break;

	case DLL_THREAD_DETACH:
		// A thread is exiting cleanly
	    break;

	case DLL_PROCESS_DETACH:
		// The DLL is being unmapped from the process's address space
		// Do any additional cleanup here
		hInst = 0;
	    break;
	}

	return TRUE;
}
//@E VBUtil

// 16-bit version for comparison
#if 0
int PASCAL LibMain(HINSTANCE hInstA, WORD wDataSeg, 
				   WORD cbHeapSize, LPSTR lpCmdLine)
{
	if (cbHeapSize != 0)
		UnlockData(0);
	hInst = hInstA;

	// Do any additional 16-bit server initialization here
	
	return hInst;
}

int FAR PASCAL WEP(int bSystemExit)
{
	// Do any additional 16-bit server cleanup here
	hInst = 0;		
	return 1;
}            
#endif

//@B ErrorHandler
void ErrorHandler(Long e)
{
    DWORD err = 0;
    if (e >= 0) {        
        err = (DWORD)e;
    } else {
        err = HResultToErr(e);
    }
    SetLastError((DWORD)err);
}
//@E ErrorHandler

DWORD HResultToErr(Long e)
{
    ASSERT(e < 0);

    switch (e) {
    case E_INVALIDARG:
        return ERROR_INVALID_PARAMETER;
    case E_OUTOFMEMORY:
        return ERROR_NOT_ENOUGH_MEMORY;
    case DISP_E_BADINDEX:
        return ERROR_INVALID_INDEX;
    case DISP_E_TYPEMISMATCH:
        return ERROR_INVALID_DATATYPE;
    case DISP_E_EXCEPTION:
        return ERROR_EXCEPTION_IN_SERVICE;
    case DISP_E_BADVARTYPE:
        return ERROR_INVALID_DATATYPE;
    case DISP_E_ARRAYISLOCKED:
        return ERROR_LOCKED;
    case E_UNEXPECTED:
        return ERROR_INVALID_DATA;
    case DISP_E_OVERFLOW:
        return ERROR_ARITHMETIC_OVERFLOW;
    case E_ACCESSDENIED:
        return ERROR_ACCESS_DENIED;
    case E_POINTER:
        return ERROR_INVALID_ADDRESS;
    case E_HANDLE:
        return ERROR_INVALID_HANDLE;
    case E_ABORT:
        return ERROR_OPERATION_ABORTED;
    case E_FAIL:
        return ERROR_GEN_FAILURE;
    }
    return ERROR_INVALID_DATA;
}
