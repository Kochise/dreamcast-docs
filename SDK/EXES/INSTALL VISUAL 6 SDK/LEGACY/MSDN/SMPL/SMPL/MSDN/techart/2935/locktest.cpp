/****************************************************************************************/
/*     Written by Ruediger R. Asche for the MSDN CD, 1994.                              */
/*     The usual disclaimers apply.                                                     */
/****************************************************************************************/


#include <stdio.h>       // for the printf function -- be sure to link against a multithreaded library!
#include <windows.h>  // for the CreateThread etc. function
#include <stdlib.h>	  // for the rand() prototype
#include "locks.h"    // defines the structure and API definitions
#include <mmsystem.h>

#define GROUPS 2    // we have 2 groups of objects here...
#define NUMBEROFTHREADS 3  // we want three of each group
#define DELAY 50
#define DELAYBIAS 50
#define TESTLOOPS 200
signed long iSanity[GROUPS];

HANDLE hResumeEvent;

class ThreadInfo
{public:
 int iID;
 CompoundSynch *csSynch;
 ThreadInfo(int i,CompoundSynch *csArg)
 { iID = i;
   csSynch = csArg;
 };
};

long WINAPI ThreadFn(ThreadInfo *lpArg)
{ int iID, iLoop, iTest;
  long lWaitTime=0;
  long lWaitSum=0;
  long lTurnAround;
  long lMaxWait=0;
  long lMinWait=10000;
  long lGotItRightAway=0;
  int  iGoofUp=0;
  iID = lpArg->iID;
  CompoundSynch *csSynch;
  csSynch = lpArg->csSynch;
  WaitForSingleObject(hResumeEvent,INFINITE);   // to synch up all of the threads...
  lTurnAround= timeGetTime();
  for (iLoop = 0; iLoop < TESTLOOPS; iLoop++)
  { lWaitTime = timeGetTime();

// beginning of critical code!

    csSynch->Claim(iID);    // identify yourself...
    lWaitTime = timeGetTime() - lWaitTime;
    InterlockedIncrement(&iSanity[iID]);  // do the sanity check...
	if (!lWaitTime) lGotItRightAway++;
    lMaxWait= lMaxWait > lWaitTime ? lMaxWait : lWaitTime;
	lMinWait= lMinWait < lWaitTime ? lMinWait : lWaitTime;
    Sleep(DELAY-DELAYBIAS+(rand()%(2*DELAYBIAS)));
	for (iTest = 0; iTest < GROUPS; iTest++)
	 { if (iTest == iID) continue;
       if (iSanity[iTest] > 0)
	     iGoofUp++;
     };
	lWaitSum+=lWaitTime;
    InterlockedDecrement(&iSanity[iID]);
    csSynch->Release(iID);

// critical code is done with here...

    Sleep(DELAY-DELAYBIAS+(rand()%(2*DELAYBIAS)));
 };   // end of for loop
lTurnAround= (timeGetTime() - lTurnAround)/TESTLOOPS;
if (iGoofUp >0) 
  printf ("goofup!!! Threads of more than one group in the lock %d times\n\r",iGoofUp);
printf ("Avg. turnaround for thread of grp %d : %8ld ms; avg wait: %lf ms, min %ld, max %ld, aces: %ld\n\r",iID,lTurnAround,(float)lWaitSum/(float)TESTLOOPS,lMinWait,lMaxWait,lGotItRightAway);
delete lpArg;
return(0); 
}

void RunTestForOneObjectType(CompoundSynch *csObject, char *szTitleOfTest)
{
HANDLE hThreads[NUMBEROFTHREADS][GROUPS];
int iLoop, iInnerLoop;
long lOldElapseTime, lNewElapseTime;
unsigned long iDummyID;
printf(szTitleOfTest);
printf("\n\r");
if (!csObject->Initialize(GROUPS)) return;
hResumeEvent = CreateEvent(NULL,TRUE,FALSE,NULL);  // manual, initially blocking
// this samples the time before start of the test suite
lOldElapseTime = timeGetTime();
// create the threads
for (iLoop = 0; iLoop <GROUPS; iLoop++)
{  iSanity[iLoop] = 0; 
   for (iInnerLoop = 0; iInnerLoop < NUMBEROFTHREADS; iInnerLoop++)
   hThreads[iInnerLoop][iLoop] = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)ThreadFn,
     (void *)new ThreadInfo(iLoop,csObject),0,&iDummyID);
};
// start all threads
SetEvent(hResumeEvent);
// now wait for termination
WaitForMultipleObjects(GROUPS*NUMBEROFTHREADS,(const HANDLE *)hThreads,TRUE,INFINITE);
// measure elapsed time
lNewElapseTime = timeGetTime();
lNewElapseTime -= lOldElapseTime;
// clean up
for (iLoop = 0; iLoop < GROUPS; iLoop++)
  for (iInnerLoop; iInnerLoop< NUMBEROFTHREADS; iInnerLoop++)
   CloseHandle(hThreads[iInnerLoop][iLoop]);
printf ("Total elapsed time: %8ld ms; per loop: %ld\n\r",lNewElapseTime,lNewElapseTime/TESTLOOPS);
CloseHandle(hResumeEvent);
csObject->Cleanup();
delete csObject;
}


main()
{
RunTestForOneObjectType(new(CUnsafe),"Testing unsafe solution:");
RunTestForOneObjectType(new(CMutex),"Testing mutex solution:");
RunTestForOneObjectType(new(CCritSect),"Testing crit sect solution:");
RunTestForOneObjectType(new(CEvents),"Testing event solution:");
RunTestForOneObjectType(new(CSemaphor),"Testing semaphor solution:");
RunTestForOneObjectType(new(CWFMO),"Testing WFMO solution:");
RunTestForOneObjectType(new(CRWLock),"Testing reader/writer lock solution:");
RunTestForOneObjectType(new(CCCR),"Testing cond. crit. region solution:");

return 0;
}
