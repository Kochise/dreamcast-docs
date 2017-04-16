/******************************************************************************
Module name: DelExe.c
Written by:  Jeffrey Richter
Note:        This function works on Windows 95 but does NOT work on Windows NT.
******************************************************************************/


#define STRICT
#include <Windows.h>
#include <tchar.h>


///////////////////////////////////////////////////////////////////////////////


#include "DelExe.h"


///////////////////////////////////////////////////////////////////////////////


// Prototypes for functions that we explicitly import from Kernel32.DLL
typedef BOOL (WINAPI *PROCFREELIBRARY)(HINSTANCE);
typedef BOOL (WINAPI *PROCDELETEFILE)(LPCTSTR);
typedef BOOL (WINAPI *PROCREMOVEDIRECTORY)(LPCTSTR);
typedef VOID (WINAPI *PROCEXITPROCESS)(DWORD);


// Data structure containing all the information we need to delete ourself,
// remove our containing directory, and terminate ourself.
typedef struct {

   HINSTANCE hinstExe;
   PROCFREELIBRARY pfnFreeLibrary;

   PROCDELETEFILE pfnDeleteFile;
   TCHAR szFile[_MAX_PATH];

   PROCREMOVEDIRECTORY pfnRemoveDirectory;
   TCHAR szDir[_MAX_PATH];

   PROCEXITPROCESS pfnExitProcess;
   DWORD dwExitCode;
} DELEXEINFO, *PDELEXEINFO;

typedef VOID (WINAPI *PROCDELEXE)(PDELEXEINFO);


///////////////////////////////////////////////////////////////////////////////


// Code to be injected into our own address space.
static void WINAPI DelExeInjCode (PDELEXEINFO pdei) {

   // Remove the EXE file from our address space
	pdei->pfnFreeLibrary(pdei->hinstExe);

   // Delete the EXE file now that it is no longer in use
	pdei->pfnDeleteFile(pdei->szFile);

	if (pdei->pfnRemoveDirectory != NULL) {
      // Remove the directory (which is now empty)
		pdei->pfnRemoveDirectory(pdei->szDir);
	}

   // Terminate our process
	pdei->pfnExitProcess(pdei->dwExitCode);
}


///////////////////////////////////////////////////////////////////////////////


// This function just marks the end of the previous function
static void WINAPI AfterDelExeInjCode (void) {
}


///////////////////////////////////////////////////////////////////////////////


void WINAPI DeleteExecutable (DWORD dwExitCode, BOOL fRemoveDir) {

	HINSTANCE hinstKrnl = GetModuleHandle(__TEXT("KERNEL32"));
	HANDLE hheap = GetProcessHeap();

   // Calculate the number of bytes in the DelExeInjCode function.
   const int cbFuncSize = ((LPBYTE)(DWORD)
      AfterDelExeInjCode - (LPBYTE)(DWORD) DelExeInjCode);

	DELEXEINFO dei;

   // From our process's default heap, allocate memory where we can 
   // inject our own function.
	PROCDELEXE pfnDelExe = HeapAlloc(hheap, HEAP_ZERO_MEMORY, cbFuncSize);

   // Inject the DelExeInjCode function into the memory block
	memcpy(pfnDelExe, DelExeInjCode, cbFuncSize);

   // Initialize the DELEXEINFO structure.
	dei.hinstExe = GetModuleHandle(NULL);
	dei.pfnFreeLibrary = (PROCFREELIBRARY) 
      GetProcAddress(hinstKrnl, "FreeLibrary");

   // Assume that the subdirectory is NOT to be removed.
	dei.pfnRemoveDirectory = NULL;
#ifdef UNICODE
	dei.pfnDeleteFile = (PROCDELETEFILE) 
      GetProcAddress(hinstKrnl, "DeleteFileW");
#else
	dei.pfnDeleteFile = (PROCDELETEFILE) 
      GetProcAddress(hinstKrnl, "DeleteFileA");
#endif
	GetModuleFileName(dei.hinstExe, dei.szFile, _MAX_PATH);

   if (fRemoveDir) {

      // The subdirectory should be removed.
#ifdef UNICODE
		dei.pfnRemoveDirectory = (PROCREMOVEDIRECTORY) 
         GetProcAddress(hinstKrnl, "RemoveDirectoryW");
#else
		dei.pfnRemoveDirectory = (PROCREMOVEDIRECTORY) 
         GetProcAddress(hinstKrnl, "RemoveDirectoryA");
#endif
		lstrcpy(dei.szDir, dei.szFile);
		*_tcsrchr(dei.szDir, __TEXT('\\')) = 0;
   }

	dei.pfnExitProcess = (PROCEXITPROCESS) 
      GetProcAddress(hinstKrnl, "ExitProcess");
	dei.dwExitCode = dwExitCode;

	pfnDelExe(&dei);
	// We never get here because pfnDelExe never returns
}


///////////////////////////////// End of File /////////////////////////////////
