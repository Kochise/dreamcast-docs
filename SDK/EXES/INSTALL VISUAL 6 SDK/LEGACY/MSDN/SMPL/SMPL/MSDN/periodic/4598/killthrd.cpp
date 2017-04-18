/******************************************************************************
Module name: KillThrd.CPP
Notices:     Written 1995 by Jeffrey Richter
Purpose:     Functions to kill a worker thread clenaly.
******************************************************************************/


#define STRICT
#include <windows.h>
#include "Process.h"    // For _beginthreadex
#include "KillThrd.h"


///////////////////////////////////////////////////////////////////////////////


// Used to store a pointer to the worker thread's internal data structure
// Allocated in KillThrd_CreateThread
static int gs_nTlsIndex = TLS_OUT_OF_INDEXES;


// Internal data structure used by the worker thread. 
typedef struct {
   HANDLE                 m_hmtxControl;     // Used to coordinate access to
                                             // the other objects
   HANDLE                 m_hmtxDelay;       // Delay death when owned
   DWORD                  m_dwDelayCount;    // # of times to delay death
   HANDLE                 m_heventEnd;       // The killing was queued
   LPTHREAD_START_ROUTINE m_lpStartAddress;  // Worker thread function
   LPVOID                 m_lpParameter;     // Worker thread parameter
   LPVOID                 m_lpThunk;         // Pointer to the SEH thunks
   HANDLE                 m_hFileMap;        // File mapping handle
} KILLTHRD_WORKERINFO, *PKILLTHRD_WORKERINFO;



// Internal structure of the exception handler chain
// This structure is documented, compiler writers need
// this information, but it's missing from the header files

typedef struct _EXCEPTIONREGISTRATIONRECORD {
   _EXCEPTIONREGISTRATIONRECORD *pexrr;
   PVOID pvHandler; // pointer to the exception handler function
} EXCEPTIONREGISTRATIONRECORD, *PEXCEPTIONREGISTRATIONRECORD;

// This marks the end of the chain
const PEXCEPTIONREGISTRATIONRECORD pexrrEndMark =
   (PEXCEPTIONREGISTRATIONRECORD) 0xFFFFFFFF;

// This is the lowest shared address
const PVOID pvSharedMin = (PVOID) 0x80000000;

// Code for thunks
static const BYTE abMovAxImm[] = {(BYTE) '\xB8'};  // MOV EAX, imm
static const BYTE abJmpAx[]    = 
   {(BYTE) '\xFF', (BYTE) '\xE0'};                  // JMP EAX


// Structure of thunk. We use byte arrays to avoid any posibility
// of alignment problems (we do NOT want alignment).
typedef struct {
   BYTE abMovAxImm[sizeof(abMovAxImm)];
   BYTE abJmpAddr[sizeof(PROC)];  // Size of a function pointer
   BYTE abJmpAx[sizeof(abJmpAx)];
} EXCEPTTHUNK, *PEXCEPTTHUNK;


///////////////////////////////////////////////////////////////////////////////


static PVOID CreateExceptionHandlerThunks (PHANDLE phFileMap) {

   // This functions works around a problem that only exists on Windows 95
   // when KillThrd_Kill interrupts the worker thread while in a system
   // call. When an exception is raised from within a system call on
   // Windows 95, only system exception handlers are called, user exception
   // handlers are not.  This can prevent KillThrd_ThreadFunc from handling
   // the SE_KILLLTHREAD exception. We are able to trick the system into
   // behaving as if all the handlers are system handlers by creating
   // thunks in shared memory to call the actual exception handlers.

   // WARNING: Windows 95 was trying to protect us but we are defeating it.
   // The system may be in an unusual state when the exception filters and
   // handlers are processed. You should be sure they do not delay the
   // termination of the thread.

   PVOID pvRet = NULL;
   PEXCEPTIONREGISTRATIONRECORD pexrrHead;
   PEXCEPTIONREGISTRATIONRECORD pexrrCur;
   PEXCEPTTHUNK pThunk;
   OSVERSIONINFO osvi;
   osvi.dwOSVersionInfoSize = sizeof(osvi);
   GetVersionEx(&osvi);
   BOOL fIsWin95 = (osvi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS);
   int nThunkCnt;

   if (fIsWin95) {
      // Get the head of the SEH handler chain
      __asm mov eax, fs:[0]
      __asm mov pexrrHead, eax

      // First calculate the number of thunks we need to create
      pexrrCur = pexrrHead;
      nThunkCnt = 0;
      while (pexrrEndMark != pexrrCur) {
         // Don't thunk system handlers,
         if (pexrrCur->pvHandler < pvSharedMin) {
            nThunkCnt++;
         }
         pexrrCur = pexrrCur->pexrr;
      }

      // Allocate shared storage for the thunks (+1 for sentinel value)

      *phFileMap = CreateFileMapping((HANDLE) 0xFFFFFFFF, NULL, PAGE_READWRITE,
         0, (nThunkCnt + 1) * sizeof(EXCEPTTHUNK), NULL);

      if (NULL != *phFileMap) {
         pvRet = MapViewOfFile(*phFileMap, FILE_MAP_WRITE, 0, 0, 0);

         if (NULL == pvRet) {
            CloseHandle(*phFileMap);
            *phFileMap = NULL;
         } else {
            pThunk = (PEXCEPTTHUNK) pvRet;
            pexrrCur = pexrrHead;

            while (0 < nThunkCnt) {
               // Only thunk user handlers
               if (pexrrCur->pvHandler < pvSharedMin) {
                  // Build the thunk in shared memory

                  CopyMemory(pThunk->abMovAxImm, abMovAxImm,
                     sizeof(pThunk->abMovAxImm));
                  CopyMemory(pThunk->abJmpAddr, &pexrrCur->pvHandler,
                     sizeof(pThunk->abJmpAddr));
                  CopyMemory(pThunk->abJmpAx, abJmpAx,
                     sizeof(pThunk->abJmpAx));

                  // Make the execption record point to thunk
                  pexrrCur->pvHandler = (PVOID) pThunk;

                  pThunk++;
                  nThunkCnt--;
               }
               pexrrCur = pexrrCur->pexrr;
            }
            // Null terminate list
            FillMemory(pThunk, sizeof(pThunk), 0);
         }
      }
   }
   return(pvRet);
}


///////////////////////////////////////////////////////////////////////////////


static void DeleteExceptionHandlerThunks (PVOID pvThunk, HANDLE hFileMap) {

   PEXCEPTIONREGISTRATIONRECORD pexrrCur;
   PEXCEPTTHUNK pThunk;
   PEXCEPTTHUNK pThunkCur;
   int nThunkCnt = 0;

   if (NULL != pvThunk) {
      // Get the head of the SEH handler chain
      __asm mov eax, fs:[0]
      __asm mov pexrrCur, eax

      pThunk = (PEXCEPTTHUNK) pvThunk;

      // Count he number of entries in the null terminated thunk list
      while ('\0' != pThunk[nThunkCnt].abMovAxImm[0]) {
         nThunkCnt++;
      }

      // Loop through the exception handler list
      while (pexrrEndMark != pexrrCur) {
         if ((PVOID) pThunk <= pexrrCur->pvHandler &&
            pexrrCur->pvHandler < (PVOID) &pThunk[nThunkCnt]) {

            // This exception handler is pointing into our thunk table
            // unthunk the entry
            pThunkCur = (PEXCEPTTHUNK) pexrrCur->pvHandler;
            CopyMemory(&pexrrCur->pvHandler, pThunkCur->abJmpAddr,
               sizeof(pexrrCur->pvHandler));
         }
         pexrrCur = pexrrCur->pexrr;
      }

      UnmapViewOfFile(pvThunk);
   }

   if (NULL != hFileMap) {
      CloseHandle(hFileMap);
   }
}


///////////////////////////////////////////////////////////////////////////////


// Wraper function for the worker thread. The new thread starts here because
// we need to wrap the call to the actual worker thread function in an SEH
// __try block and to perform cleanup just before the thread dies.  The 
// address of the KILLTHRD_WORKERINFO structure is saved in 
// thread local storage.
static UINT WINAPI KillThrd_ThreadFunc (PVOID pvParam) {

   PKILLTHRD_WORKERINFO pktwi = (PKILLTHRD_WORKERINFO) pvParam;
   DWORD dwExitCode = 0;

   __try {
      __try {
         // The index is allocated in KillThrd_CreateThread
         TlsSetValue(gs_nTlsIndex, pktwi);
         dwExitCode = pktwi->m_lpStartAddress(pktwi->m_lpParameter);
      }

      // If the exception occurs because our thread is forcibly being
      // killed, execute our handler (the system does a global unwind first).
      __except ((GetExceptionCode() == SE_KILLTHREAD)
         ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH) {

         DeleteExceptionHandlerThunks(pktwi->m_lpThunk, pktwi->m_hFileMap);
      }
   }
   __finally {
      // This executes even if the thread is dying.
      CloseHandle(pktwi->m_hmtxDelay);
      CloseHandle(pktwi->m_heventEnd);
      CloseHandle(pktwi->m_hmtxControl);
      free(pktwi);
   }
   return(dwExitCode);
}


///////////////////////////////////////////////////////////////////////////////


// Use this function instead of CreateThread to start a killable thread.
// The parameters to this function match CreateThread.  The caller is 
// responsible for calling KillThrd_Close to free the allocated resources.
PKILLTHRD WINAPI KillThrd_CreateThread (
   LPSECURITY_ATTRIBUTES lpThreadAttributes, DWORD dwStackSize, 
   LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, 
   DWORD dwCreationFlags, LPDWORD lpThreadId) {

   PKILLTHRD pkt = NULL;
   PKILLTHRD_WORKERINFO pktwi = NULL;

   // If this is the first time this function is called, allocate
   // a thread local storage slot.
   if (gs_nTlsIndex == TLS_OUT_OF_INDEXES)
      gs_nTlsIndex = TlsAlloc();

   // Use calloc instead of malloc because it zeros the memory block
   // Note: Error check should be done here!
   pkt = (PKILLTHRD) calloc(1, sizeof(KILLTHRD));
   pktwi = (PKILLTHRD_WORKERINFO) calloc(1, sizeof(KILLTHRD_WORKERINFO));

   pktwi->m_lpStartAddress = lpStartAddress;
   pktwi->m_lpParameter = lpParameter;
   pktwi->m_dwDelayCount = 0;
   pktwi->m_lpThunk = NULL;
   pktwi->m_hFileMap = NULL;

   pktwi->m_hmtxControl = CreateMutex(NULL, FALSE, NULL);
   pktwi->m_hmtxDelay = CreateMutex(NULL, FALSE, NULL);
   pktwi->m_heventEnd = CreateEvent(NULL, TRUE, FALSE, NULL);


   // Duplicate the handles so the control thread and the worker
   // thread each have their own set of process-relative handles which
   // they are responsible for closing.  The actual kernel objects will
   // not be destroyed until both handles are closed.
   DuplicateHandle(GetCurrentProcess(), pktwi->m_hmtxControl,
      GetCurrentProcess(), &pkt->m_hmtxControl, 0, FALSE, 
      DUPLICATE_SAME_ACCESS);

   DuplicateHandle(GetCurrentProcess(), pktwi->m_hmtxDelay,
      GetCurrentProcess(), &pkt->m_hmtxDelay, 0, FALSE,
      DUPLICATE_SAME_ACCESS);

   DuplicateHandle(GetCurrentProcess(), pktwi->m_heventEnd,
      GetCurrentProcess(), &pkt->m_heventEnd, 0, FALSE,
      DUPLICATE_SAME_ACCESS);

   // Start the thread at our wrapper function, KillThrd_ThreadFunc,
   // which then calls lpStartAddress
   pkt->m_hThread = (HANDLE) _beginthreadex(lpThreadAttributes,
      dwStackSize, KillThrd_ThreadFunc, pktwi, dwCreationFlags,
      (PUINT) lpThreadId);

   // The control thread uses pkt to kill the worker thread using
   // KillThrd_Kill and must free this resouce by calling KillThrd_Close.
   return(pkt);
}


///////////////////////////////////////////////////////////////////////////////


// When the control thread is done with pkt, it must call this function to
// close the handles and free the memory.
VOID WINAPI KillThrd_Close (PKILLTHRD pkt) {

   if (pkt != NULL) {
      if (pkt->m_hThread     != NULL) CloseHandle(pkt->m_hThread);
      if (pkt->m_hmtxDelay   != NULL) CloseHandle(pkt->m_hmtxDelay);
      if (pkt->m_heventEnd   != NULL) CloseHandle(pkt->m_heventEnd);
      if (pkt->m_hmtxControl != NULL) CloseHandle(pkt->m_hmtxControl);
      free(pkt);
   }
}


///////////////////////////////////////////////////////////////////////////////


// Terminate the worker thread by getting it to execute this function 
static void WINAPI KillThrd_ForceDeath (void) {


   // Get the address of the worker thread's internal data block. This was
   // set by KillThrd_ThreadFunc
   PKILLTHRD_WORKERINFO pktwi =
      (PKILLTHRD_WORKERINFO) TlsGetValue(gs_nTlsIndex);

   // Work around Windows 95 execption handling problem
   pktwi->m_lpThunk = CreateExceptionHandlerThunks(&pktwi->m_hFileMap);

   RaiseException(SE_KILLTHREAD, EXCEPTION_NONCONTINUABLE, 0, NULL);
   // RaiseException never returns
}


///////////////////////////////////////////////////////////////////////////////
// Macros used to abstract the instruction pointer register for the various
// CPU platforms.


#if defined(_X86_)
#define PROGCTR(Context)  (Context.Eip)
#endif

#if defined(_MIPS_)
#define PROGCTR(Context)  (Context.Fir)
#endif

#if defined(_ALPHA_)
#define PROGCTR(Context)  (Context.Fir)
#endif

#if defined(_PPC_)
#define PROGCTR(Context)  (Context.Iar)
#endif

#if !defined(PROGCTR)
#error Module contains CPU-specific code; modify and recompile.
#endif


///////////////////////////////////////////////////////////////////////////////


// The control thread calls this function to kill a worker thread.  If the
// worker thread is not currently protected by KillThrd_DelayDeath, we attempt
// to kill the thread now by suspending it, changing it's instruction pointer
// to KillThrd_ForceDeath, and resuming the thread.  Effectively we are raising
// an exception in the worker thread.  If the worker thread is protected by
// KillThrd_DelayDeath, we simply set an event and let the thread kill itself
// when it calls KillThrd_DelayDeath(FALSE) and ends its protection.
void WINAPI KillThrd_Kill (PKILLTHRD pkt) {

   WaitForSingleObject(pkt->m_hmtxControl, INFINITE);

   if (WaitForSingleObject(pkt->m_hmtxDelay, 0) == WAIT_TIMEOUT) {

      // The worker is delaying its death, set a flag that the worker
      // will check later.
      SetEvent(pkt->m_heventEnd);
   } else {

      // The worker can be terminated now!
      CONTEXT context;

      // Stop the worker thread
      SuspendThread(pkt->m_hThread);

      if (WaitForSingleObject(pkt->m_hThread, 0) == WAIT_TIMEOUT) {
         // The worker has not yet terminated

         // Get the worker thread's current CPU registers
         context.ContextFlags = CONTEXT_CONTROL;
         GetThreadContext(pkt->m_hThread, &context);

         // Change the instruction pointer to our function
         PROGCTR(context) = (DWORD) KillThrd_ForceDeath;
         SetThreadContext(pkt->m_hThread, &context);

         // Resuming the thread forces our function to be called which
         // rasies an SE_KILLTHREAD exception in the worker thread.
         ResumeThread(pkt->m_hThread);
      }
      ReleaseMutex(pkt->m_hmtxDelay);
   }
   ReleaseMutex(pkt->m_hmtxControl);
}


///////////////////////////////////////////////////////////////////////////////


// This function is used to allow the worker thread to protect sections of code
// from termination by the control thread.  Call KillThrd_DelayDeath(TRUE) to
// start protection from KillThrd_Kill and KillThrd_DelayDeath(FALSE) to end
// protection.  Multiple KillThrd_DelayDeath(TRUE) calls are allowed.  A delay
// count is maintained and the thread remains protected until the count is 0.
void WINAPI KillThrd_DelayDeath (BOOL fBlock) {

   // Get the address of the worker thread's internal data block. This was
   // set by KillThrd_ThreadFunc
   PKILLTHRD_WORKERINFO pktwi = 
      (PKILLTHRD_WORKERINFO) TlsGetValue(gs_nTlsIndex);

   WaitForSingleObject(pktwi->m_hmtxControl, INFINITE);

   if (fBlock) {

      // The worker wants to delay its death
      // We get and keep the m_hmtxDelay mutex while protected
      // from termination by KillThrd_Kill.
      WaitForSingleObject(pktwi->m_hmtxDelay, INFINITE);

      // Increment the delay death count
      pktwi->m_dwDelayCount++;
   } else {

      // The worker wants to allow its death
      // Decrement the delay death count
      pktwi->m_dwDelayCount--;
      ReleaseMutex(pktwi->m_hmtxDelay);

      // If the delay death count is zero and
      if ((pktwi->m_dwDelayCount == 0) &&
         (WaitForSingleObject(pktwi->m_heventEnd, 0) == WAIT_OBJECT_0)) {

         // The delay death count is zero AND KillThrd_Kill has been called.
         // Force us (the worker thread) to terminate now.
         KillThrd_ForceDeath();
      }
   }
   ReleaseMutex(pktwi->m_hmtxControl);
}


///////////////////////////////// End of File /////////////////////////////////
