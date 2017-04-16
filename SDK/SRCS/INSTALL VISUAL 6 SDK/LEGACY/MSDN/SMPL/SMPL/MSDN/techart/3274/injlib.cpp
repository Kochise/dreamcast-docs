#include "stdafx.h"
#include <windows.h>

#include "injlib.h"

//  This stuff is basically stolen from Jeffrey Richter...
//

PVOID AllocProcessMemory (HANDLE hProcess, DWORD dwNumBytes) 
{
  CONTEXT Context;
  DWORD dwThreadId, dwNumBytesXferred, dwError;
  HANDLE hThread;
  HINSTANCE hinstKrnl = GetModuleHandle(__TEXT("Kernel32"));
  PVOID pvMem;
  MEMORY_BASIC_INFORMATION mbi;
  BOOL fOk = FALSE;	// Assume failure
  __try {
		 hThread = CreateRemoteThread(hProcess, NULL,dwNumBytes + sizeof(HANDLE),
                       (LPTHREAD_START_ROUTINE)GetProcAddress(hinstKrnl, "ExitThread"),0,					
                             CREATE_SUSPENDED,&dwThreadId);	
         if (hThread == NULL) 
         {	
          dwError = GetLastError();
          __leave;
         }
         Context.ContextFlags = CONTEXT_CONTROL;
         if (!GetThreadContext(hThread, &Context))
          __leave;
         if (sizeof(mbi) != VirtualQueryEx(hProcess,(PDWORD) STACKPTR(Context) - 1, 
             &mbi, sizeof(mbi)))
          __leave;
         pvMem = (PVOID) mbi.BaseAddress;
         fOk = WriteProcessMemory(hProcess, pvMem, &hThread,sizeof(hThread), &dwNumBytesXferred);
         if (!fOk) 
          __leave;
 // Point past the thread's handle.
         pvMem = (PVOID) ((PHANDLE) pvMem + 1);
         }
  __finally 
         {
          if (!fOk) 
            {
             if (hThread) ResumeThread(hThread);
             pvMem = NULL;
            }
         }		
  return(pvMem);
}


//////////////////////////////////////////////////////////////


BOOL FreeProcessMemory (HANDLE hProcess, PVOID pvMem) 
{ BOOL fOk;
  HANDLE hThread;
  DWORD dwNumBytesXferred;
// Get the handle of the remote thread from the block of 
// memory.
  pvMem = (PVOID) ((PHANDLE) pvMem - 1);
  fOk = ReadProcessMemory(hProcess, pvMem, &hThread,sizeof(hThread),&dwNumBytesXferred);
  if (fOk) 
  {
   if (ResumeThread(hThread) == 0xffffffff) {
// Resume failed.  Probably because the handle is
// bad because the app overwrote the memory contents.  
   fOk = FALSE;
  }
  CloseHandle(hThread);
  }
  return(fOk);
}
