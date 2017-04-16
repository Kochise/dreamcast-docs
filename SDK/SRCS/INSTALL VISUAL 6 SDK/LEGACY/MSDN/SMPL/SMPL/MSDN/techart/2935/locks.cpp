/****************************************************************************************/
/*     Written by Ruediger R. Asche for the MSDN CD, 1994.                              */
/*     The usual disclaimers apply.                                                     */
/****************************************************************************************/

#include <windows.h>
#include <stdio.h>
#include "locks.h"

/*****************************************************************************************/
/*           Implementation of the Unsafe solution                                       */
/*****************************************************************************************/


BOOL CUnsafe::Initialize(int i) {return TRUE;};
void CUnsafe::Cleanup() {};
void CUnsafe::Claim(int i) {};
void CUnsafe::Release(int i) {};

/*****************************************************************************************/
/*           Implementation of the mutex solution                                        */
/*****************************************************************************************/


BOOL CMutex::Initialize(int i)
{ hMutex = CreateMutex(NULL,FALSE,NULL);
  if (!hMutex) return FALSE;
  return (TRUE);
};
void CMutex::Cleanup()
{ CloseHandle(hMutex);
};
void CMutex::Claim(int i)
{ WaitForSingleObject(hMutex,INFINITE);
};
void CMutex::Release(int i)
{ ReleaseMutex(hMutex);
};

/*****************************************************************************************/
/*           Implementation of the critical section solution                             */
/*****************************************************************************************/


BOOL CCritSect::Initialize(int i)
{ // note: we don't do any error checking here. Better do that in real life
  int iLoop;
  iGroupNo = i;
  csShields = (CRITICAL_SECTION *)
    VirtualAlloc(0,sizeof(CRITICAL_SECTION)*i,MEM_COMMIT,PAGE_READWRITE);
  pCounters = (long *) 
    VirtualAlloc(0,sizeof(long)*i,MEM_COMMIT,PAGE_READWRITE);
  for (iLoop = 0; iLoop < i; iLoop++)
    {InitializeCriticalSection(&csShields[iLoop]);
     pCounters[iLoop] = -1;
    };  
  hMutex = CreateEvent(NULL,FALSE,TRUE,NULL);
  return (TRUE);
};

void CCritSect::Cleanup()
{ int iLoop;
  for (iLoop = 0;iLoop<iGroupNo;iLoop++)
    DeleteCriticalSection(&csShields[iLoop]);
  CloseHandle(hMutex);
  VirtualFree((LPVOID)csShields,sizeof(CRITICAL_SECTION)*iGroupNo , 
              MEM_DECOMMIT);
  VirtualFree((LPVOID)pCounters,sizeof(long)*iGroupNo ,
              MEM_DECOMMIT);
};


void CCritSect::Claim(int i)
{ EnterCriticalSection(&csShields[i]);
  if (InterlockedIncrement(&pCounters[i]) == 0)
    WaitForSingleObject(hMutex, INFINITE);
  LeaveCriticalSection(&csShields[i]);
};

void CCritSect::Release(int i)
{EnterCriticalSection(&csShields[i]);
  if (InterlockedDecrement(&pCounters[i]) < 0)
     SetEvent(hMutex);
  LeaveCriticalSection(&csShields[i]);
};

/*****************************************************************************************/
/*           Implementation of the Event solution                                        */
/*****************************************************************************************/


BOOL CEvents::Initialize(int i)
{ // note: we don't do any error checking here. Better do that in real life
  int iLoop;
  iGroupNo = i;
  hEvents = (HANDLE *)
    VirtualAlloc(0,sizeof(HANDLE)*i,MEM_COMMIT,PAGE_READWRITE);
  pCounters = (long *) 
    VirtualAlloc(0,sizeof(long)*i,MEM_COMMIT,PAGE_READWRITE);
  for (iLoop = 0; iLoop < i; iLoop++)
    {hEvents[iLoop]=CreateEvent(NULL,TRUE,FALSE,NULL);
     pCounters[iLoop] = -1;
    };  
  hMutex = CreateEvent(NULL,FALSE,TRUE,NULL);
  return (TRUE);
};

void CEvents::Cleanup()
{ int iLoop;
  for (iLoop = 0;iLoop<iGroupNo;iLoop++)
    CloseHandle(hEvents[iLoop]);
  CloseHandle(hMutex);
  VirtualFree((LPVOID)hEvents,sizeof(HANDLE)*iGroupNo , 
              MEM_DECOMMIT);
  VirtualFree((LPVOID)pCounters,sizeof(int)*iGroupNo ,
              MEM_DECOMMIT);
};

void CEvents::Claim(int i)
{ if (InterlockedIncrement(&pCounters[i]) == 0)
   { WaitForSingleObject(hMutex, INFINITE);
     SetEvent(hEvents[i]);
   };
  WaitForSingleObject(hEvents[i],INFINITE);
};

void CEvents::Release(int i)
{ if (InterlockedDecrement(&pCounters[i]) < 0)
   { ResetEvent(hEvents[i]);
     SetEvent(hMutex);
   };
};

/*****************************************************************************************/
/*           Implementation of the Semaphor solution                                     */
/*****************************************************************************************/
#define SEMCOUNT 2

BOOL CSemaphor::Initialize(int i)
{ // note: we don't do any error checking here. Better do that in real life
  int iLoop;
  iGroupNo = i;
  hEvents = (HANDLE *)
    VirtualAlloc(0,sizeof(HANDLE)*i,MEM_COMMIT,PAGE_READWRITE);
  hSemaphores = (HANDLE *)
    VirtualAlloc(0,sizeof(HANDLE)*i,MEM_COMMIT,PAGE_READWRITE);
  pCounters = (long *) 
    VirtualAlloc(0,sizeof(long)*i,MEM_COMMIT,PAGE_READWRITE);
  for (iLoop = 0; iLoop < i; iLoop++)
    {hEvents[iLoop]=CreateEvent(NULL,TRUE,FALSE,NULL);
     hSemaphores[iLoop]=CreateSemaphore(NULL,SEMCOUNT,SEMCOUNT,NULL);
     pCounters[iLoop] = -1;
    };  

  hMutex = CreateEvent(NULL,FALSE,TRUE,NULL);
  return (TRUE);
};

void CSemaphor::Cleanup()
{ int iLoop;
  for (iLoop = 0;iLoop<iGroupNo;iLoop++)
    {CloseHandle(hEvents[iLoop]);
	 CloseHandle(hSemaphores[iLoop]);
	};
  CloseHandle(hMutex);
  VirtualFree((LPVOID)hEvents,sizeof(HANDLE)*iGroupNo , 
              MEM_DECOMMIT);
  VirtualFree((LPVOID)hSemaphores,sizeof(HANDLE)*iGroupNo , 
              MEM_DECOMMIT);
  VirtualFree((LPVOID)pCounters,sizeof(int)*iGroupNo ,
              MEM_DECOMMIT);
};

void CSemaphor::Claim(int i)
{ if (InterlockedIncrement(&pCounters[i]) == 0)
   { WaitForSingleObject(hMutex, INFINITE);
     SetEvent(hEvents[i]);
   };
  WaitForSingleObject(hEvents[i],INFINITE);
  WaitForSingleObject(hSemaphores[i],INFINITE);
};

void CSemaphor::Release(int i)
{ ReleaseSemaphore(hSemaphores[i],1,0);
  if (InterlockedDecrement(&pCounters[i]) < 0)
   { ResetEvent(hEvents[i]);
     SetEvent(hMutex);
   };
};

/*****************************************************************************************/
/*           Implementation of the WFMO solution                                         */
/*****************************************************************************************/


BOOL CWFMO::Initialize(int i)
{ // note: we don't so any error checking here. Better do that in real life
  int iLoop;
  iGroupNo = i;
  hEvents = (HANDLE *)
    VirtualAlloc(0,sizeof(HANDLE)*i,MEM_COMMIT,PAGE_READWRITE);
  pCounters = (long *) 
    VirtualAlloc(0,sizeof(long)*i,MEM_COMMIT,PAGE_READWRITE);
  pHandleArrays = (PHANDLE *)VirtualAlloc(0,sizeof(PHANDLE)*i,MEM_COMMIT,PAGE_READWRITE);
  hMutex = CreateEvent(NULL,FALSE,TRUE,NULL);
  for (iLoop = 0; iLoop < i; iLoop++)
    {hEvents[iLoop]=CreateEvent(NULL,TRUE,FALSE,NULL);
     pCounters[iLoop] = -1;
     (pHandleArrays)[iLoop] = (PHANDLE)VirtualAlloc(0,sizeof(HANDLE)*2,MEM_COMMIT,PAGE_READWRITE);
     ((pHandleArrays)[iLoop])[0]= hMutex;
	 ((pHandleArrays)[iLoop])[1]= hEvents[iLoop];
    };  
  return (TRUE);
};

void CWFMO::Cleanup()
{ int iLoop;
  for (iLoop = 0;iLoop<iGroupNo;iLoop++)
    CloseHandle(hEvents[iLoop]);
  CloseHandle(hMutex);
  VirtualFree((LPVOID)hEvents,sizeof(HANDLE)*iGroupNo , 
              MEM_DECOMMIT);
  VirtualFree((LPVOID)pCounters,sizeof(int)*iGroupNo ,
              MEM_DECOMMIT);
// clean up the rest here too...
};

void CWFMO::Claim(int i)
{  if (WaitForMultipleObjects(2,pHandleArrays[i],FALSE,INFINITE) == WAIT_OBJECT_0)
    SetEvent(hEvents[i]); 
     InterlockedIncrement(&pCounters[i]);
};

void CWFMO::Release(int i)
{ ResetEvent(hEvents[i]);
  if (InterlockedDecrement(&pCounters[i]) < 0)
     SetEvent(hMutex);
     else SetEvent(hEvents[i]);
};

/*****************************************************************************************/
/*           Implementation of the Reader/Writer lock solution                           */
/*****************************************************************************************/


#define WRITER 0
#define READER 1


BOOL CRWLock::Initialize(int i)
{ // note: we don't so any error checking here. Better do that in real life
  hReaderEvent=CreateEvent(NULL,TRUE,FALSE,NULL);
  hMutex = CreateEvent(NULL,FALSE,TRUE,NULL);
  hWriterMutex = CreateMutex(NULL,FALSE,NULL);
  iCounter = -1;
  return (TRUE);
};

void CRWLock::Cleanup()
{ CloseHandle(hReaderEvent);
  CloseHandle(hMutex);
  CloseHandle(hWriterMutex);
};

void CRWLock::Claim(int i)
{ 
 if (i== WRITER)
 {  
    WaitForSingleObject(hWriterMutex,INFINITE);
	WaitForSingleObject(hMutex, INFINITE);
 }
 else
 {   
 if (InterlockedIncrement(&iCounter) == 0)
      { WaitForSingleObject(hMutex, INFINITE);
        SetEvent(hReaderEvent);
      };
 WaitForSingleObject(hReaderEvent,INFINITE);
 };
};

void CRWLock::Release(int i)
{ if (i == WRITER)
  { 
	  SetEvent(hMutex);
	  ReleaseMutex(hWriterMutex);
  }
  else
  if (InterlockedDecrement(&iCounter) < 0)
     { ResetEvent(hReaderEvent);
       SetEvent(hMutex);
     };
};

/*****************************************************************************************/
/*           Implementation of the conditional critical region solution                  */
/*****************************************************************************************/


BOOL CCCR::Initialize(int i)
{ // note: we don't so any error checking here. Better do that in real life
  int iLoop;
  iGroupNo = i;
  if (i>2) return FALSE;   // we currently hardcode the thing for two groups
  hAlwaysTrue = CreateEvent(NULL,TRUE,TRUE,NULL);
  hEvents = (HANDLE *)
    VirtualAlloc(0,sizeof(HANDLE)*i*2,MEM_COMMIT,PAGE_READWRITE);
  pCounters = (long *) 
    VirtualAlloc(0,sizeof(long)*i,MEM_COMMIT,PAGE_READWRITE);
  for (iLoop = 0; iLoop < i; iLoop++)
    {hEvents[iLoop*2]=CreateEvent(NULL,TRUE,TRUE,NULL);
	 hEvents[iLoop*2+1]=hAlwaysTrue;
     pCounters[iLoop] = -1;
    };
  InitializeCriticalSection(&csAtomizer);  
  return (TRUE);
};

void CCCR::Cleanup()
{ int iLoop;
  DeleteCriticalSection(&csAtomizer);
  CloseHandle(hAlwaysTrue);
  for (iLoop = 0;iLoop<iGroupNo;iLoop++)
    CloseHandle(hEvents[iLoop*2]);
  VirtualFree((LPVOID)hEvents,sizeof(HANDLE)*iGroupNo*2 , 
              MEM_DECOMMIT);
  VirtualFree((LPVOID)pCounters,sizeof(int)*iGroupNo ,
              MEM_DECOMMIT);
};

void CCCR::Claim(int i)
{ 
  TryAgain:
 EnterCriticalSection(&csAtomizer);
  switch(WaitForMultipleObjects(2,&hEvents[((i+1)%2)*2],FALSE,INFINITE))
    { case WAIT_OBJECT_0:     // the event of the other group
        if (InterlockedIncrement(&pCounters[i]) == 0)
          ResetEvent(hEvents[i*2]);
        LeaveCriticalSection(&csAtomizer);
		break;
	  case WAIT_OBJECT_0+1:	  // hAlwaysTrue
	    LeaveCriticalSection(&csAtomizer);
		goto TryAgain;
	  case WAIT_FAILED:
	    printf("Error returning from WFMO: %d",GetLastError());
		break;
	};
};

void CCCR::Release(int i)
{ EnterCriticalSection(&csAtomizer);
  if (InterlockedDecrement(&pCounters[i]) < 0)
     SetEvent(hEvents[i*2]);
  LeaveCriticalSection(&csAtomizer);
};







