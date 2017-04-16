extern "C"
{
#include "stdio.h"
#include <windows.h>
#include "thrdlib.h"
}

extern "C"
{
BOOL WINAPI DllMain (HINSTANCE hDLL, DWORD dwReason, LPVOID lpReserved)
{
  switch (dwReason)
  {
    case DLL_PROCESS_ATTACH:
	default:
   return( TRUE );
  };  
}
}

ConcurrentExecution::ConcurrentExecution(int iMaxNumberOfThreads)
{// BUGBUG - make this minimum of passed value and MAX_WAIT_THREADS
 m_iMaxArraySize = iMaxNumberOfThreads;
 m_hThreadArray = (HANDLE *)VirtualAlloc(NULL,m_iMaxArraySize*sizeof(HANDLE),
	                         MEM_COMMIT,PAGE_READWRITE);
 m_hObjectArray = (DWORD *)VirtualAlloc(NULL,m_iMaxArraySize*sizeof(DWORD),
	                         MEM_COMMIT,PAGE_READWRITE);
 // if this allocation fails, the member functions will tell you...
};
ConcurrentExecution::~ConcurrentExecution()
{
 if (m_hThreadArray) VirtualFree(m_hThreadArray,m_iMaxArraySize*sizeof(HANDLE),
	                           MEM_DECOMMIT);
 if (m_hObjectArray) VirtualFree(m_hObjectArray,m_iMaxArraySize*sizeof(DWORD),
	                           MEM_DECOMMIT);
};

/* we know that below code works semantically, but the performance is just terrible. So we archive this and branch off the code tree with a new algorithm...
BOOL ConcurrentExecution::DoForAllObjects(int iNoOfObjects,long *ObjectArray,
		                 CONCURRENT_EXECUTION_ROUTINE pObjectProcessor,
						 CONCURRENT_FINISHING_ROUTINE pObjectTerminated)
{
 int iLoop,iEndLoop;
 DWORD iThread;
 DWORD iArrayIndex;
 DWORD dwReturnCode;

 //_asm int 3;
// first, assume that unless we balance off the number of threads,
// we will always have constantly m_iMaxArraySize elements to work with.
 m_iCurrentArraySize = m_iMaxArraySize;
 m_iCurrentNumberOfThreads = iNoOfObjects;
// BUGBUG - we will later on stipulate that iCurrentNumberOfThreads
// can change dynamically, which will break this code...
  for (iLoop = 0; iLoop < m_iCurrentNumberOfThreads; iLoop++)
	{HANDLE hNewThread;
// as long as there is space left in the array, simply fill it up...
		if (iLoop < m_iCurrentArraySize)
				     iArrayIndex = iLoop;
// array is full. Wait until one slot opens up, then fill the slot in with the
// next object.
// BUGBUG: If there are fewer threads than slots in the array,
// this test will fail...
		else
			{
			 iArrayIndex = WaitForMultipleObjects(
				   m_iCurrentArraySize,m_hThreadArray,FALSE,INFINITE);
			 if (iArrayIndex == WAIT_FAILED)   // uh-oh...
				{
				 MessageBeep(0);
				 return(FALSE);  // BUGBUG: must jump to a cleanup routine
				};
			 GetExitCodeThread(m_hThreadArray[iArrayIndex],&dwReturnCode); //error
			 CloseHandle(m_hThreadArray[iArrayIndex]);
	        };
		LARGE_INTEGER li,li1;
		char szBuf[100];
		QueryPerformanceCounter(&li1);

// at this point, we have a free slot. Now create a new thread to fill in there.
	    hNewThread = CreateThread(NULL,0,pObjectProcessor,(LPVOID)ObjectArray[iLoop],
		     0,(LPDWORD)&iThread);
		QueryPerformanceCounter(&li);
		sprintf(szBuf,"creating %d at %d %8lu\n",iLoop,li1.HighPart,li1.LowPart);
		OutputDebugString(szBuf);
		sprintf(szBuf,"created %d at %d %8lu\n",iLoop,li.HighPart,li.LowPart);
		OutputDebugString(szBuf);
// now call the callback to inform the caller that one thread has finished.
// Note that we do this after creating the new thread so that if the processing
// of the routine is lengthy, we can still do stuff with the new object...
// This code is somewhat questionable because I do the test twice...
		if (iLoop >= m_iCurrentArraySize)
		 pObjectTerminated((void *)m_hObjectArray[iArrayIndex],(void *)dwReturnCode);

		if (!hNewThread)  // here we need to jump to a cleanup routine...
	   MessageBox(GetFocus(),"Failed","CreateThread",MB_OK);
	else
// in the m_hObjectArray, we keep track of what object is in what slot at any 
// time...
	   {
	    m_hThreadArray[iArrayIndex] = hNewThread;
		m_hObjectArray[iArrayIndex] = ObjectArray[iLoop];
	   };
	 };
// We are now processing the last few threads. Clean up. 
	iEndLoop = min(m_iCurrentArraySize,m_iCurrentNumberOfThreads);
// iEndloop now has the number of remaining elements 
	for (iLoop=iEndLoop;iLoop>0;iLoop--)
// due to the semantics of the WFSO function, we must "backfill"
// the array before we go on waiting...
// in GUIGREP, we didn't do that because there was no terminator function,
// so the thread function implicitly did the post-processing. Thus, as long
// as no threads queued up anymore, we could just wait. In this case, however,
// we must continue processing threads as soon as they are finished... 
    {
	 iArrayIndex=WaitForMultipleObjects(iLoop, m_hThreadArray,FALSE,INFINITE);
	 if (iArrayIndex==WAIT_FAILED)
	 {
		  GetLastError();
		  _asm int 3;	    // do something intelligent here...
	 };
	  GetExitCodeThread(m_hThreadArray[iArrayIndex],&dwReturnCode);  // error?
	  if (!CloseHandle(m_hThreadArray[iArrayIndex]))
	    MessageBox(GetFocus(),"Can't delete thread!","",MB_OK); // make this better...

     pObjectTerminated((void *)m_hObjectArray[iArrayIndex],(void *)dwReturnCode);
	 if (iArrayIndex==iLoop-1) continue;   // we are fine here; no backfilling in need
	 m_hThreadArray[iArrayIndex]=m_hThreadArray[iLoop-1];
	 m_hObjectArray[iArrayIndex]=m_hObjectArray[iLoop-1];
	};
  return TRUE;

};

*/

BOOL ConcurrentExecution::DoSerial(int iNoOfObjects,long *ObjectArray,
		                 CONCURRENT_EXECUTION_ROUTINE pProcessor,
						 CONCURRENT_FINISHING_ROUTINE pTerminator)
{ 
    for (int iLoop=0;iLoop<iNoOfObjects;iLoop++)
    {
     pTerminator((LPVOID)ObjectArray[iLoop],(LPVOID)pProcessor((LPVOID)ObjectArray[iLoop]));
    };
 return TRUE;

};


// This routine loops through all the objects on the current list and
// executes the processor function for each, then calls the terminator
// function as soon as each thread is done... 

int ConcurrentExecution::DoForAllObjects(int iNoOfObjects,long *ObjectArray,
		                 CONCURRENT_EXECUTION_ROUTINE pObjectProcessor,
						 CONCURRENT_FINISHING_ROUTINE pObjectTerminated)
{
 int iLoop,iEndLoop;
 DWORD iThread;
 DWORD iArrayIndex;
 DWORD dwReturnCode;
 DWORD iCurrentArrayLength=0;
 BOOL bWeFreedSomething;
     char szBuf[70];

// LARGE_INTEGER li1[30],li25[30],li21[30],li22[30],li2;
 m_iCurrentNumberOfThreads=iNoOfObjects;

// first, assume that unless we balance off the number of threads,
// we will always have constantly m_iMaxArraySize elements to work with.
// BUGBUG - we will later on stipulate that iCurrentNumberOfThreads
// can change dynamically, which will break this code...
 HANDLE *hPnt=(HANDLE *)VirtualAlloc(NULL,m_iCurrentNumberOfThreads*sizeof(HANDLE),MEM_COMMIT,PAGE_READWRITE);
 for(iLoop=0;iLoop<m_iCurrentNumberOfThreads;iLoop++)
 hPnt[iLoop] = CreateThread(NULL,0,pObjectProcessor,(LPVOID)ObjectArray[iLoop],
		     CREATE_SUSPENDED,(LPDWORD)&iThread); // don't forget to handle errors here.
  for (iLoop = 0; iLoop < m_iCurrentNumberOfThreads; iLoop++)
	{
	 HANDLE hNewThread;
	 bWeFreedSomething=FALSE;
// if array is empty, allocate one slot and boogie.
     if (!iCurrentArrayLength)
     {
      iArrayIndex = 0;
	  iCurrentArrayLength=1;
	 }
	 else
	 {
// first check if we can recycle any slot. We prefer to do this before we
// look for a new slot so that we can invoke the old thread's terminator right
// away...
      iArrayIndex=WaitForMultipleObjects(iCurrentArrayLength,
		                                 m_hThreadArray,FALSE,0);
	  if (iArrayIndex==WAIT_TIMEOUT)  // no slot free...
	  {
       {
       if (iCurrentArrayLength >= m_iMaxArraySize)
       {
		iArrayIndex= WaitForMultipleObjects(iCurrentArrayLength,
		                                 m_hThreadArray,FALSE,INFINITE);
		bWeFreedSomething=TRUE;
       }
	   else // we could free up a slot somewhere, so go for it...
       {
        iCurrentArrayLength++;
        iArrayIndex=iCurrentArrayLength-1;
       }; // else iArrayIndex points to a thread that has been nuked
       };
      }
      else bWeFreedSomething = TRUE;
	 }; // at this point, iArrayIndex contains a valid index to store the
	    // new thread in.
	 hNewThread = hPnt[iLoop];
     ResumeThread(hNewThread);
     if (bWeFreedSomething)
       { 
         GetExitCodeThread(m_hThreadArray[iArrayIndex],&dwReturnCode); //error
		 CloseHandle(m_hThreadArray[iArrayIndex]);
		 pObjectTerminated((void *)m_hObjectArray[iArrayIndex],(void *)dwReturnCode);
       };
     m_hThreadArray[iArrayIndex] = hNewThread;
     m_hObjectArray[iArrayIndex] = ObjectArray[iLoop];
  }; // end of for loop
// We are now processing the last few threads. Clean up. 
	iEndLoop = iCurrentArrayLength;
// iEndloop now has the number of remaining elements 
	for (iLoop=iEndLoop;iLoop>0;iLoop--)
// due to the semantics of the WFSO function, we must "backfill"
// the array before we go on waiting...
// in GUIGREP, we didn't do that because there was no terminator function,
// so the thread function implicitly did the post-processing. Thus, as long
// as no threads queued up anymore, we could just wait. In this case, however,
// we must continue processing threads as soon as they are finished... 
    {
	 iArrayIndex=WaitForMultipleObjects(iLoop, m_hThreadArray,FALSE,INFINITE);
	 if (iArrayIndex==WAIT_FAILED)
	 {
		  GetLastError();
		  _asm int 3;	    // do something intelligent here...
	 };
	  GetExitCodeThread(m_hThreadArray[iArrayIndex],&dwReturnCode);  // error?
	  if (!CloseHandle(m_hThreadArray[iArrayIndex]))
	    MessageBox(GetFocus(),"Can't delete thread!","",MB_OK); // make this better...

     pObjectTerminated((void *)m_hObjectArray[iArrayIndex],(void *)dwReturnCode);
	 if (iArrayIndex==iLoop-1) continue;   // we are fine here; no backfilling in need
	 m_hThreadArray[iArrayIndex]=m_hThreadArray[iLoop-1];
	 m_hObjectArray[iArrayIndex]=m_hObjectArray[iLoop-1];
	};
 if (hPnt) VirtualFree(hPnt,m_iCurrentNumberOfThreads*sizeof(HANDLE),
	                           MEM_DECOMMIT);

  return iCurrentArrayLength;

};
BOOL ConcurrentExecution::AddObject(void *pObject)
{
   return TRUE;
};

