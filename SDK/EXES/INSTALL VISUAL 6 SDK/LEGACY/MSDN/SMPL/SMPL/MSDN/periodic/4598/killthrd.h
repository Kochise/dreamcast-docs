/******************************************************************************
Module name: KillThrd.H
Notices: Written 1995 by Jeffrey Richter
******************************************************************************/


///////////////////////////////////////////////////////////////////////////////
// The kill thread software exception code


// Useful macro for creating our own software exception codes
#define MAKESOFTWAREEXCEPTION(Severity, Facility, Exception) \
   ((DWORD) ( \
   /* Severity code */     (Severity  <<  0) |     \
   /* MS(0) or Cust(1) */  (1         << 29) |     \
   /* Reserved(0) */       (0         << 28) |     \
   /* Facility code */     (Facility  << 16) |     \
   /* Exception code */    (Exception <<  0)))


// Our very own software exception. This exception is raised
// when a thread is being killed.
#define SE_KILLTHREAD   \
   MAKESOFTWAREEXCEPTION(ERROR_SEVERITY_ERROR, FACILITY_NULL, 1)


///////////////////////////////////////////////////////////////////////////////
// Functions called by the control thread


// Data structure returned to the control thread.
// The control thread should only ever manipulate the
// m_hThread member directly.  Never touch the other members.
typedef struct {
   HANDLE   m_hThread;     // Handle of worker thread
   HANDLE   m_hmtxControl; // Used to coordinate access the other objects
   HANDLE   m_hmtxDelay;   // Queue killing when owned
   HANDLE   m_heventEnd;   // The killing was queued
} KILLTHRD, *PKILLTHRD;


// Creates a worker thread that can be killed at any time
PKILLTHRD WINAPI KillThrd_CreateThread (
   LPSECURITY_ATTRIBUTES lpThreadAttributes, DWORD dwStackSize, 
   LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, 
   DWORD dwCreationFlags, LPDWORD lpThreadId);

// Kills the worker thread
void WINAPI KillThrd_Kill (PKILLTHRD pkt);

// Frees the resources allocated by KillThrd_CreateThread
VOID WINAPI KillThrd_Close (PKILLTHRD pkt);


///////////////////////////////////////////////////////////////////////////////
// Functions called by the worker thread


// Delays the death of the worker until a known "safe" time
void WINAPI KillThrd_DelayDeath (BOOL fBlock);


///////////////////////////////// End of File /////////////////////////////////
