#include <windows.h>

// **************************************************************************-
//
// Function: DllMain(HANDLE, DWORD, LPVOID)
//
// **************************************************************************-
//
// Description:
//
// This is the main initialization routine called by the NT kernel when
// a new thread requests use of the DLL.  It's also called when a thread
// stops using the DLL.  A parameter passed to the function identifies the
// reason for calling.
//
// **************************************************************************-

BOOL APIENTRY DllMain(HANDLE hDLL, DWORD dwReason, LPVOID lpReserved)
{
    // Nothing to initialize.
    return TRUE;
}
