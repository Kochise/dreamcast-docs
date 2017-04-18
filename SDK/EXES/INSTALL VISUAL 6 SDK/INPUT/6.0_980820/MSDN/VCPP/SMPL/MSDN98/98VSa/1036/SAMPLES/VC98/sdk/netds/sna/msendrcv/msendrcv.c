/* msendrcv.c */
/* (C) COPYRIGHT DATA CONNECTION LIMITED 1994 */

/*****************************************************************************/
/* Change History                                                            */
/*                                                                           */
/*       11/01/94 DK  Created                                                */
/*       15/03/94 DK  Thread priorities added and signalled event goes to    */
/*                    back of the list (for WaitForMultipleObjects)          */
/*       14/04/94 DK  OutputResults fixed to not use global variable and     */
/*                    so that output is done for received conversations only */
/*****************************************************************************/

/*****************************************************************************/
/* If you want internal tracing, #define SRTRC here                          */
/*****************************************************************************/
//#define SRTRC

/*****************************************************************************/
/*                                                                           */
/* ROUTINE : SEND and RECEIVE using event completion                         */
/*                                                                           */
/* FUNCTION: This file contains the routines for a multi-threaded routine    */
/*           which uses asynchronous APPC calls with event completion        */
/*           to send and receive data.                                       */
/*                                                                           */
/*           It requires another copy of itself on another machine to run    */
/*           or it can send and receive to itself.                           */
/*                                                                           */
/* INPUTS  : MSENDRCV.CFG (file) (documented below)                          */
/*                                                                           */
/* OUTPUTS : MSENDRCV.OUT                                                    */
/*           MSENDRCV.TRC                                                    */
/*                                                                           */
/*****************************************************************************/

/*****************************************************************************/
/* Operation:                                                                */
/*                                                                           */
/* This is a Windows NT application which runs in a minimized window.        */
/*                                                                           */
/* Thread structure:                                                         */
/*                                                                           */
/*   A receive_allocate thread                                               */
/*     This thread issues a receive_allocate and, when it completes, hands   */
/*     it to a receive thread.  It then waits for the receive thread to      */
/*     accept the conversation.  This thread uses event completion, but      */
/*     its operation is essentially synchronous.                             */
/*                                                                           */
/*   A variable number of send threads                                       */
/*     Each send thread processes a variable number of conversations and     */
/*     issues a WaitForMultipleObjects to wait for completion of any of its  */
/*     send operations.  Each conversation starts with TP_STARTED, followed  */
/*     by MC_ALLOCATE and MC_CONFIRM.  Then it issues MC_SEND_DATA verbs     */
/*     to send data.  MC_CONFIRMs are issued at configurable intervals.      */
/*     If a confirm fails, an attempt is made to restart the conversation    */
/*     after five seconds.                                                   */
/*                                                                           */
/*   A variable number of receive threads                                    */
/*     Each receive thread processes a variable number of conversations and  */
/*     issues a WaitForMultipleObjects call to wait for completion of any    */
/*     one of its receive operations or for a request for a new conversation */
/*     from the receive_allocate thread.  It sets a second event to tell the */
/*     receive_allocate thread that it has accepted the conversation.        */
/*     Each conversation issues MC_RECEIVE_AND_WAIT verbs to receive data.   */
/*     If confirmation is requested, an MC_CONFIRM verb is issued.           */
/*                                                                           */
/*   Note:  this program is compatible with the single-threaded versions of  */
/*   send and receive, which can be run for example on WIN16 clients.        */
/*                                                                           */
/*****************************************************************************/

/*****************************************************************************/
/* Configuration file:                                                       */
/*                                                                           */
/* The configuration file is called MSENDRCV.CFG and must reside in the      */
/* same directory as the program.  It contains the following, in any order.  */
/* If any parameter is omitted, the default is assumed.                      */
/*                                                                           */
/* ResultFile = <Name of file for results, default MSENDRCV.OUT>             */
/* TraceFile = <Name of file for tracing, default MSENDRCV.TRC>              */
/* LocalTPName = <Name used for receive_allocate, default MSENDRCVTP>        */
/* RemoteTPName = <Name used for allocate, default MSENDRCVTP>               */
/* LocalLUAlias = <Alias for local LU, default SENDLU>                       */
/* RemoteLUAlias = <Alias for remote LU, default RECVLU>                     */
/* ModeName = <Mode Name, default #INTER>                                    */
/*                                                                           */
/* NumRcvConvs = <Number of conversations to be received, default = 4>       */
/* NumRcvThreads = <Number of receive threads, default = 2>                  */
/* NumSendConvs = <Number of conversations to be received, default = 4>      */
/* NumSends = <number of SEND_DATA verbs per conversation, default = 8>      */
/* ConfirmEvery = <number of SEND_DATA verbs between CONFIRMs, default = 2>  */
/* SendSize = <number of bytes per SEND_DATA, default = 256>                 */
/*                                                                           */
/* The name used for TP_STARTED is fixed at MSENDRCV.                        */
/*                                                                           */
/* If NumRcvConvs is zero, the TP will keep issuing receive_allocates.       */
/* If NumSends is zero, the TP will never DEALLOCATE a conversation.         */
/* If ConfirmEvery is zero, the TP will not issue CONFIRM verbs except       */
/*    after the MC_ALLOCATE.                                                 */
/* If ConfirmEvery is non-zero, the TP issues a CONFIRM verbs ConfirmEvery   */
/*    sends.                                                                 */
/* If NumRcvConvs is non-zero and NumRcvThreads is greater than NumRcvConvs, */
/*    NumRcvThreads is reduced to NumRcvConvs.                               */
/* If NumRcvConvs is non-zero and NumRcvThreads*63 < NumRcvConvs,            */
/*    NumRcvThreads is increased to NumRcvConvs / 63 + 1.                    */
/*                                                                           */
/* Configuration constants (in msendrcv.h)                                   */
/*                                                                           */
/* #define MAX_RECEIVE_THREADS  Max number of receive threads          (64)  */
/* #define MAX_RCV_PER_THREAD   Max conversations per receive thread   (63)  */
/* #define MAX_SEND_PER_THREAD  Max conversations per send thread      (64)  */
/*                                                                           */
/* MAX_RCV_PER_THREAD and MAX_SEND_PER_THREAD are constrained by the limit   */
/* of 64 objects that can be waited for in WaitForMultipleObjects.           */
/*                                                                           */
/*****************************************************************************/

#include <windows.h>
HINSTANCE hInst;
BOOL verbs_started = FALSE;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winappc.h>
#include <wincsv.h>
#include "msendrcv.h"

/*****************************************************************************/
/* Trace macros                                                              */
/*****************************************************************************/
#ifdef SRTRC
#define SRTROPEN() t = fopen(TraceFile,"w");
#define SRTRFLUSH() fflush(t);
#define SRTRCLOSE() fclose(t);
#define SRTRACE fprintf
#else
#define SRTROPEN()
#define SRTRFLUSH()
#define SRTRCLOSE()
#define SRTRACE 1 ? (void) 0 : fprintf
#endif

/*****************************************************************************/
/* WinMain - reads initialization info and controls message loop             */
/*           NT version                                                      */
/*****************************************************************************/
int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow)
{

  MSG msg;
  DWORD Tid;
  int i;
  DWORD NumConvs;
  HANDLE ThreadHandle;

  hInst = hInstance;

  InitializeMain();

  if (!InitializeWinMain(hInstance))
  {
    return (FALSE);
  }

  ReadConfig();
  SRTROPEN()

  /***************************************************************************/
  /* Create two events for each receive thread                               */
  /***************************************************************************/
  for (i = 0; i < NumRcvThreads; i++)
  {
    /*************************************************************************/
    /* Create an event for kicking the receive thread                        */
    /*************************************************************************/
    RcvThreadArray[i].convptr = NULL;
    RcvThreadArray[i].event1 = CreateEvent(NULL,FALSE,FALSE,NULL);
    RcvThreadArray[i].event2 = CreateEvent(NULL,FALSE,FALSE,NULL);
  }

  /***************************************************************************/
  /* Create receive threads                                                  */
  /***************************************************************************/
  for (i = 0; i < NumRcvThreads; i++)
  {
    SRTRACE(t,"Created event handles %p %p for receive thread %d\n",
            RcvThreadArray[i].event1, RcvThreadArray[i].event2,i);

    /*************************************************************************/
    /* Create the thread                                                     */
    /*************************************************************************/
    ThreadHandle = CreateThread(NULL,
                                16000,
                                (LPTHREAD_START_ROUTINE)ReceiveThread,
                                (void *)i,
                                0,
                                &Tid);
    if (ThreadHandle == NULL)
    {
      GetLastError();
      DebugBreak();
    }
    SetThreadPriority(ThreadHandle,THREAD_PRIORITY_LOWEST);
    SRTRACE(t,"Created receive thread %d with priority %d\n",
            i,GetThreadPriority(ThreadHandle));
    CloseHandle(ThreadHandle);
  }

  /***************************************************************************/
  /* Create receive_allocate thread                                          */
  /***************************************************************************/
  if (NumRcvThreads > 0)
  {
    ThreadHandle = CreateThread(NULL,
                                16000,
                                (LPTHREAD_START_ROUTINE)RcvAllocThread,
                                NULL,
                                0,
                                &Tid);
    if (ThreadHandle == NULL)
    {
      GetLastError();
      DebugBreak();
    }
    SetThreadPriority(ThreadHandle,THREAD_PRIORITY_NORMAL);
    SRTRACE(t,"Created receive allocate thread with priority %d\n",
            GetThreadPriority(ThreadHandle));
    CloseHandle(ThreadHandle);
  }

  /***************************************************************************/
  /* Create enough send threads to process conversations                     */
  /***************************************************************************/
  i = NumSendConvs;
  while (i > 0)
  {
    NumConvs = (i > 64) ? 64 : i;
    ThreadHandle = CreateThread(NULL,
                                16000,
                                (LPTHREAD_START_ROUTINE)SendThread,
                                (void *)NumConvs,
                                0,
                                &Tid);
    if (ThreadHandle == NULL)
    {
      GetLastError();
      DebugBreak();
    }
    SetThreadPriority(ThreadHandle,THREAD_PRIORITY_BELOW_NORMAL);
    SRTRACE(t,"Created send thread with %d conversations and priority %d\n",
            NumConvs,GetThreadPriority(ThreadHandle));
    CloseHandle(ThreadHandle);
    i -= NumConvs;
  }

  /***************************************************************************/
  /* Windows processing loop                                                 */
  /***************************************************************************/
  while(GetMessage(&msg,NULL,0,0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  WinAPPCCleanup();
  OutputResults();
  SRTRFLUSH()
  SRTRCLOSE()
  DeleteCriticalSection(&runsem);
  return msg.wParam;         /* save exit parameter for return               */

}

/*****************************************************************************/
/* RcvAllocThread - separate thread for receive_allocates                    */
/*****************************************************************************/
DWORD WINAPI RcvAllocThread()
{
  /***************************************************************************/
  /* Local variables                                                         */
  /***************************************************************************/
  CONVCB * convptr;
  struct appc_hdr * vcbptr;
  unsigned short ThreadNo;
  unsigned short NextReceive = 0;
  BOOL   RcvAllocEnded = FALSE;
  DWORD rc;
  SYSTEMTIME st;

  /***************************************************************************/
  /* Count threads within critical section                                   */
  /***************************************************************************/
  EnterCriticalSection(&runsem);
  ThreadCount++;
  ThreadNo = ThreadCount;
  LeaveCriticalSection(&runsem);

  SRTRACE(t,"Thread %d (ralc) Started\n",ThreadNo);

  /***************************************************************************/
  /* Loop round until the required number of conversations have been         */
  /* allocated                                                               */
  /***************************************************************************/
  while ((NumRcvConvs == 0) || (NumRalcs < NumRcvConvs))
  {
    /*************************************************************************/
    /* Make a conversation control block                                     */
    /*************************************************************************/
    convptr = malloc (sizeof(CONVCB));
    convptr->thread       = ThreadNo;
    convptr->conv         = 0;
    convptr->TPid[0]      = '\0';
    convptr->Convid       = 0;
    convptr->async_corr   = 0;
    convptr->SendCount    = 0;
    convptr->RcvCount     = 0;
    convptr->ConfirmCount = 0;
    convptr->TPEnded      = FALSE;
    convptr->Deallocated  = FALSE;
    convptr->DataPtr      = malloc(RcvSize);
    vcbptr = (struct appc_hdr *) &convptr->vcb;
    memset(vcbptr,0,sizeof(VCB));
    strcpy (convptr->type,"ralc");

    /*************************************************************************/
    /* Create an event                                                       */
    /*************************************************************************/
    convptr->hEvent = CreateEvent(NULL,FALSE,FALSE,NULL);
    SRTRACE(t,"Thread %d (ralc) convptr %p\n",ThreadNo,convptr);
    SRTRACE(t,"Thread %d (ralc) event handle %p\n",ThreadNo,convptr->hEvent);

    /*************************************************************************/
    /* Build a receive_allocate                                              */
    /*************************************************************************/
    Build_RECEIVE_ALLOCATE (convptr);

    /*************************************************************************/
    /* Issue receive_allocate using event notification                       */
    /*************************************************************************/
    convptr->async_corr = WinAsyncAPPCEx(convptr->hEvent,
                                         (long)(char *)(vcbptr));
//  SRTRACE(t,"Thread %d (ralc) Receive_Allocate issued corr %p\n",
//          ThreadNo,convptr->async_corr);
    SRTRFLUSH()
    if (convptr->async_corr == 0)
    {
      SRTRACE(t,"Thread %d (ralc) WinAsync call %x failed zero corr %p\n",
              ThreadNo,vcbptr->opcode,convptr->async_corr);
      break;
    }
    else
    {
      /***********************************************************************/
      /* Wait for event completion                                           */
      /***********************************************************************/
      rc = WaitForSingleObject(convptr->hEvent,INFINITE);
      if (rc == WAIT_FAILED)
      {
        rc = GetLastError();
        SRTRACE(t,"Thread %d (ralc) wait for event_1 %p failed with rc %d\n",
                ThreadNo,convptr->hEvent,rc);
        break;
      }
      if (vcbptr->primary_rc != AP_OK)
      {
        SRTRACE(t,"Thread %d (ralc) WinAsync error: %s prc %4.4x src %8.8x\n",
                ThreadNo,VerbName[vcbptr->opcode],
                APPC_FLIPI(vcbptr->primary_rc),
                APPC_FLIPL(vcbptr->secondary_rc));
        break;
      }
      else
      {
        NumRalcs++;
        SRTRACE(t,"Thread %d (ralc) Receive_Allocate %d completed\n",
                ThreadNo,NumRalcs);

        /*********************************************************************/
        /* give it to a receive thread by kicking event 1                    */
        /*********************************************************************/
        RcvThreadArray[NextReceive].convptr = convptr;
//      SRTRACE(t,"Thread %d (ralc) convptr %p\n",ThreadNo,convptr);
//      SRTRACE(t,"Thread %d (ralc) kicking receive thread %d\n",
//              ThreadNo,NextReceive);
//      SRTRACE(t,"Thread %d (ralc) setting event_1 %p\n",ThreadNo,
//              RcvThreadArray[NextReceive].event1);
        rc = SetEvent (RcvThreadArray[NextReceive].event1);
        if (rc == FALSE)
        {
          rc = GetLastError();
          SRTRACE(t,"Thread %d (ralc) setting event_1 %p failed with rc %d\n",
                  ThreadNo,RcvThreadArray[NextReceive].event1,rc);
          break;
        }

        /*********************************************************************/
        /* wait for receive thread to release event 2                        */
        /*********************************************************************/
//      SRTRACE(t,"Thread %d (ralc) waiting for event_2 %d\n",ThreadNo,
//              RcvThreadArray[NextReceive].event2);
        rc = WaitForSingleObject(RcvThreadArray[NextReceive].event2,INFINITE);
        if (rc == WAIT_FAILED)
        {
          rc = GetLastError();
          SRTRACE(t,"Thread %d (ralc) wait for event_2 %p failed with rc %d\n",
                  ThreadNo,RcvThreadArray[NextReceive].event2,rc);
          break;
        }

        /*********************************************************************/
        /* ready for next receive allocate                                   */
        /*********************************************************************/
        NextReceive++;
        if (NextReceive == NumRcvThreads)
        {
          NextReceive = 0;
        }
      }
    }
  }

  /***************************************************************************/
  /* Kick receive threads for last time in case they are idle                */
  /* convptr is set to NULL to indicate this final kick                      */
  /***************************************************************************/
  SRTRACE(t,"Thread %d (ralc) last kicks\n",ThreadNo);
  for (NextReceive = 0; NextReceive < NumRcvThreads; NextReceive++)
  {
    RcvThreadArray[NextReceive].convptr = NULL;
    rc = SetEvent (RcvThreadArray[NextReceive].event1);
  }

  /***************************************************************************/
  /* Count threads within critical section                                   */
  /***************************************************************************/
  EnterCriticalSection(&runsem);
  ThreadCount--;
  GetLocalTime(&st);
  SRTRACE(t,"Thread %d (ralc) Exit at %d:%d:%d: ThreadCount %d\n",
          ThreadNo,st.wHour,st.wMinute,st.wSecond,ThreadCount);
  if (ThreadCount == 0)
  {
    PostMessage(hWndMain, WM_CLOSE, 0, 0);
  }
  LeaveCriticalSection(&runsem);
  return(0);
}

/*****************************************************************************/
/* ReceiveThread - service thread which processes multiple conversations     */
/*****************************************************************************/
DWORD WINAPI ReceiveThread(DWORD k)
{
  /***************************************************************************/
  /* Separate variables for each instance of this thread                     */
  /***************************************************************************/
  DWORD ObjIndex;
  DWORD i;
  DWORD j;
  DWORD rc;
  unsigned short NumConvs = 0;
  unsigned short RcvMax = 0;
  unsigned short ThreadNo;
  unsigned short RcvThreadNo;
  CONVCB * ConvptrArray [MAX_RCV_PER_THREAD+2];
  HANDLE EventArray [MAX_RCV_PER_THREAD+2];
  SYSTEMTIME st;

  EventArray[0] = RcvThreadArray[k].event1;
  ConvptrArray[0] = NULL;
  for (i = 1; i < MAX_RCV_PER_THREAD+2; i++)
  {
    EventArray[i] = NULL;
    ConvptrArray[i] = NULL;
  }

  /***************************************************************************/
  /* Count threads                                                           */
  /***************************************************************************/
  EnterCriticalSection(&runsem);
  ThreadCount++;
  RcvThreads++;
  ThreadNo = ThreadCount;
  RcvThreadNo = RcvThreads;
  OUTPUTNUMBER
  LeaveCriticalSection(&runsem);

  SRTRACE(t,"Thread %d (recv) Started\n",k);
  SRTRACE(t,"Thread %d (recv) has event handles %p %p\n",k,
          RcvThreadArray[k].event1,RcvThreadArray[k].event2);

  /***************************************************************************/
  /* Loop round until finished                                               */
  /***************************************************************************/
  while (TRUE)
  {
    /*************************************************************************/
    /* Wait for event completion                                             */
    /*************************************************************************/
//  SRTRACE(t,"Thread %d (recv) waiting for %d events to complete\n",
//          k,NumConvs+1);
    ObjIndex = WaitForMultipleObjects(NumConvs+1,EventArray,FALSE,INFINITE);
    if (ObjIndex == WAIT_FAILED)
    {
      rc = GetLastError();
      SRTRACE(t,"Thread %d (recv) wait for %d events failed with rc %d\n",
              k,NumConvs+1,rc);
      for (j = 0; j <= NumConvs; j++)
      {
        SRTRACE(t,"Thread %d (recv) event %d has handle %p\n",
                k,j,EventArray[j]);
      }
      break;
    }
    ObjIndex -= WAIT_OBJECT_0;
//  SRTRACE(t,"Thread %d (recv) event %d has completed\n",k,ObjIndex);
    if (ObjIndex == 0)
    {
      /***********************************************************************/
      /* final kick from receive_allocate thread - terminate if idle         */
      /***********************************************************************/
      if (RcvThreadArray[k].convptr == NULL)
      {
        SRTRACE(t,"Thread %d (recv) ralc thread terminating\n",k);
        SRTRACE(t,"Thread %d (recv) NumRalcs %d NumRcvConvs %d NumConvs %d\n",
                k,NumRalcs,NumRcvConvs,NumConvs);
        if (NumConvs == 0)
        {
          break;
        }
        else
        {
          continue;
        }
      }
      else
      {
        /*********************************************************************/
        /* new conversation - save convptr and release rcv_alloc thread      */
        /*********************************************************************/
        SRTRACE(t,"Thread %d (recv) new conversation\n",k);

        /*********************************************************************/
        /* select next entry in the convptr array as conversation index      */
        /*********************************************************************/
        NumConvs++;
        i = NumConvs;

        /*********************************************************************/
        /* set up convptr array                                              */
        /* save service thread number and slot number in convcb for tracing  */
        /* add event to event array                                          */
        /*********************************************************************/
        ConvptrArray[i] = RcvThreadArray[k].convptr;
//      SRTRACE(t,"Thread %d:%d (recv) using convptr %p\n",k,i,ConvptrArray[i]);
        ConvptrArray[i]->thread = (unsigned short)k;
        ConvptrArray[i]->conv   = (unsigned short)i;
        strcpy (ConvptrArray[i]->type,"recv");
        EventArray[i] = ConvptrArray[i]->hEvent;
        EnterCriticalSection(&runsem);
        SimRcvConvs++;
        OUTPUTNUMBER
        SRTRACE(t,"Thread %d:%d (recv) NumConvs %d SimRcvConvs %d\n",
                k,i,NumConvs,SimRcvConvs);
        LeaveCriticalSection(&runsem);

        /*********************************************************************/
        /* release receive_allocate thread                                   */
        /*********************************************************************/
//      SRTRACE(t,"Thread %d:%d (recv) setting event_2 %p\n",
//              k,i,RcvThreadArray[k].event2);
        rc = SetEvent (RcvThreadArray[k].event2);
        if (rc == FALSE)
        {
          rc = GetLastError();
          SRTRACE(t,"Thread %d:%d (recv) setting event_2 %p failed with rc %d\n",
                  k,i,RcvThreadArray[k].event2,rc);
          break;
        }
      }
    }
    else
    {
      /***********************************************************************/
      /* Object index locates existing conversation                          */
      /***********************************************************************/
      i = ObjIndex;
    }

    /*************************************************************************/
    /* Issue the next verb                                                   */
    /*************************************************************************/
//  SRTRACE(t,"Thread %d:%d (recv) issuing next verb\n",
//          k,ConvptrArray[i]->conv);
    ConvptrArray[i]->TPEnded = IssueRcvVerb(ConvptrArray[i]);
    if (ConvptrArray[i]->TPEnded)
    {
      /***********************************************************************/
      /* end of conversation                                                 */
      /***********************************************************************/
      SRTRACE(t,"Thread %d:%d (recv) conversation completed\n",
              k,ConvptrArray[i]->conv);
      NumConvs--;
      EnterCriticalSection(&runsem);
      SimRcvConvs--;
      RcvConvs++;
      OUTPUTNUMBER
      SRTRACE(t,"Thread %d:%d (recv) NumConvs %d SimRcvConvs %d RcvConvs %d\n",
              k,ConvptrArray[i]->conv,NumConvs,SimRcvConvs,RcvConvs);
      SRTRACE(t,"Thread %d:%d (recv) NumRalcs %d NumRcvConvs %d NumConvs %d\n",
              k,ConvptrArray[i]->conv,NumRalcs,NumRcvConvs,NumConvs);
      LeaveCriticalSection(&runsem);

      /***********************************************************************/
      /* free resources                                                      */
      /***********************************************************************/
      SRTRACE(t,"Thread %d:%d (recv) clearing entry %d\n",
              k,ConvptrArray[i]->conv,i);
      CloseHandle(ConvptrArray[i]->hEvent);
      free (ConvptrArray[i]->DataPtr);
      free (ConvptrArray[i]);
      ConvptrArray[i] = NULL;
      EventArray[i]   = NULL;

      /***********************************************************************/
      /* if the required number of conversations have been allocated and     */
      /* this thread has just finished its last conversation, end loop       */
      /***********************************************************************/
      if ((NumRcvConvs > 0) && (NumRalcs == NumRcvConvs) && (NumConvs == 0))
      {
        break;
      }

      /***********************************************************************/
      /* the event array cannot have holes in it, so shuffle up the          */
      /* pointers and events                                                 */
      /* note that this means convptr->conv no longer matches i              */
      /* which is why tracing uses ConvptrArray[i]->conv                     */
      /***********************************************************************/
      for (j = i; j <= NumConvs; j++)
      {
        ConvptrArray [j] = ConvptrArray [j+1];
        EventArray [j] = EventArray [j+1];
      }
      ConvptrArray [NumConvs+1] = NULL;
      EventArray [NumConvs+1] = NULL;
    }
    else
    {
      /***********************************************************************/
      /* to stop one conversation getting an unfair share of the time,       */
      /* move this conversation to the end and shuffle up the pointers.      */
      /* note that this means convptr->conv no longer matches i              */
      /* which is why tracing uses ConvptrArray[i]->conv                     */
      /***********************************************************************/
      ConvptrArray [NumConvs+1] = ConvptrArray [i];
      EventArray [NumConvs+1] = EventArray [i];
      for (j = i; j <= NumConvs; j++)
      {
        ConvptrArray [j] = ConvptrArray [j+1];
        EventArray [j] = EventArray [j+1];
      }
      ConvptrArray [NumConvs+1] = NULL;
      EventArray [NumConvs+1] = NULL;
    }
  }

  /***************************************************************************/
  /* Count threads within critical section                                   */
  /***************************************************************************/
  EnterCriticalSection(&runsem);
  ThreadCount--;
  RcvThreads--;
  GetLocalTime(&st);
  SRTRACE(t,"Thread %d (recv) Exit at %d:%d:%d: ThreadCount %d\n",
          k,st.wHour,st.wMinute,st.wSecond,ThreadCount);
  OUTPUTNUMBER
  if (ThreadCount == 0)
  {
    PostMessage(hWndMain, WM_CLOSE, 0, 0);
  }
  LeaveCriticalSection(&runsem);
  return(0);
}

/*****************************************************************************/
/* SendThread - thread which processes multiple conversations                */
/*****************************************************************************/
DWORD WINAPI SendThread(DWORD NumConvs)
{
  /***************************************************************************/
  /* Separate variables for each instance of this thread                     */
  /***************************************************************************/
  CONVCB * convptr;
  struct appc_hdr * vcbptr;
  unsigned short ThreadNo;
  unsigned short SendThreadNo;
  DWORD ObjIndex;
  DWORD i;
  DWORD j;
  DWORD rc;
  CONVCB * ConvptrArray [MAX_SEND_PER_THREAD+1];
  HANDLE EventArray [MAX_SEND_PER_THREAD+1];
  SYSTEMTIME st;

  for (i = 0; i < MAX_SEND_PER_THREAD+1; i++)
  {
    ConvptrArray[i] = NULL;
    EventArray[i] = NULL;
  }

  /***************************************************************************/
  /* Count threads within critical section                                   */
  /***************************************************************************/
  EnterCriticalSection(&runsem);
  ThreadCount++;
  SendThreads++;
  ThreadNo = ThreadCount;
  SendThreadNo = SendThreads;
  OUTPUTNUMBER
  LeaveCriticalSection(&runsem);

  for (i = 0; i < NumConvs; i++)
  {
    /*************************************************************************/
    /* Make a conversation control block                                     */
    /*************************************************************************/
    convptr = malloc (sizeof(CONVCB));
    convptr->thread       = SendThreadNo;
    convptr->conv         = (unsigned short)i;
    convptr->async_corr   = 0;
    convptr->TPid[0]      = '\0';
    convptr->Convid       = 0;
    convptr->SendCount    = 0;
    convptr->ConfirmCount = 0;
    convptr->TPEnded      = FALSE;
    convptr->Deallocated  = FALSE;
    convptr->Counted      = FALSE;
    convptr->SendSize     = SendSize;
    convptr->DataPtr      = malloc(convptr->SendSize);
    vcbptr = (struct appc_hdr *) &convptr->vcb;
    memset(vcbptr,0,sizeof(VCB));
    strcpy (convptr->type,"send");
//  SRTRACE(t,"Thread %d:%d (send) has convptr %p\n",
//          SendThreadNo,i,convptr);

    /*************************************************************************/
    /* Create an event                                                       */
    /*************************************************************************/
    convptr->hEvent = CreateEvent(NULL,FALSE,FALSE,NULL);
    SRTRACE(t,"Thread %d:%d (send) has event handle %p\n",
            SendThreadNo,i,convptr->hEvent);

    /*************************************************************************/
    /* Add to arrays                                                         */
    /*************************************************************************/
    ConvptrArray[i] = convptr;
    EventArray[i]   = convptr->hEvent;

    /*************************************************************************/
    /* Build a tp_started                                                    */
    /*************************************************************************/
    Build_TP_STARTED(convptr);
    SRTRFLUSH()

    /*************************************************************************/
    /*PERF* Don't re-generate data each time we issue a send!                */
    /*************************************************************************/
    GenerateData(convptr);

    /*************************************************************************/
    /* Issue tp_started                                                      */
    /*************************************************************************/
    convptr->async_corr = WinAsyncAPPCEx(convptr->hEvent,
                                         (long)(char *)(vcbptr));
//  SRTRACE(t,"Thread %d:%d (send) tp_started issued corr %p\n",
//          SendThreadNo,i,convptr->async_corr);
    SRTRFLUSH()
    if (convptr->async_corr == 0)
    {
      SRTRACE(t,"Thread %d:%d (send) WinAsync call %x failed corr %p\n",
              SendThreadNo,i,vcbptr->opcode,convptr->async_corr);
      convptr->TPEnded = TRUE;
    }
  }

  /***************************************************************************/
  /* Loop round until finished                                               */
  /***************************************************************************/
  while (TRUE)
  {
    /*************************************************************************/
    /* Wait for event completion                                             */
    /*************************************************************************/
//  SRTRACE(t,"Thread %d (send) waiting for %d events to complete\n",
//          SendThreadNo,NumConvs);
    ObjIndex = WaitForMultipleObjects(NumConvs,EventArray,FALSE,INFINITE);
    if (ObjIndex == WAIT_FAILED)
    {
      rc = GetLastError();
      SRTRACE(t,"Thread %d (send) wait for %d events failed with rc %d\n",
              SendThreadNo,NumConvs,rc);
      for (j = 0; j < NumConvs; j++)
      {
        SRTRACE(t,"Thread %d (send) event %d has handle %p\n",
                SendThreadNo,j,EventArray[j]);
      }
      break;
    }

    /*************************************************************************/
    /* Get index to conversation array                                       */
    /*************************************************************************/
    i = ObjIndex - WAIT_OBJECT_0;
//  SRTRACE(t,"Thread %d:%d (send) event %d has completed\n",
//          SendThreadNo,ConvptrArray[i]->conv,i);

    /*************************************************************************/
    /* Issue the next verb                                                   */
    /*************************************************************************/
//  SRTRACE(t,"Thread %d:%d (send) issuing next send verb\n",
//          SendThreadNo,ConvptrArray[i]->conv);
    ConvptrArray[i]->TPEnded = IssueSendVerb(ConvptrArray[i]);

    if (ConvptrArray[i]->TPEnded)
    {
      /***********************************************************************/
      /* end of conversation                                                 */
      /***********************************************************************/
      NumConvs--;
      SRTRACE(t,"Thread %d:%d (send) conversation completed: NumConvs %d\n",
              SendThreadNo,ConvptrArray[i]->conv,NumConvs);

      /***********************************************************************/
      /* free resources                                                      */
      /***********************************************************************/
      CloseHandle(ConvptrArray[i]->hEvent);
      free (ConvptrArray[i]->DataPtr);
      free (ConvptrArray[i]);
      ConvptrArray[i] = NULL;
      EventArray[i]   = NULL;

      /***********************************************************************/
      /* if all conversations have completed, end loop                       */
      /***********************************************************************/
      if (NumConvs == 0)
      {
        break;
      }
      /***********************************************************************/
      /* the event array cannot have holes in it, so shuffle up the          */
      /* pointers and events                                                 */
      /* note that this means convptr->conv no longer matches i              */
      /* which is why tracing uses ConvptrArray[i]->conv                     */
      /***********************************************************************/
      for (j = i; j < MAX_SEND_PER_THREAD - 1; j++)
      {
        ConvptrArray [j] = ConvptrArray [j+1];
        EventArray [j] = EventArray [j+1];
      }
      ConvptrArray [MAX_SEND_PER_THREAD-1] = NULL;
      EventArray [MAX_SEND_PER_THREAD-1] = NULL;
    }
    else
    {
      /***********************************************************************/
      /* to stop one conversation getting an unfair share of the time,       */
      /* move this conversation to the end and shuffle up the pointers.      */
      /* note that this means convptr->conv no longer matches i              */
      /* which is why tracing uses ConvptrArray[i]->conv                     */
      /***********************************************************************/
      ConvptrArray [NumConvs] = ConvptrArray [i];
      EventArray [NumConvs] = EventArray [i];
      for (j = i; j < NumConvs; j++)
      {
        ConvptrArray [j] = ConvptrArray [j+1];
        EventArray [j] = EventArray [j+1];
      }
      ConvptrArray [NumConvs] = NULL;
      EventArray [NumConvs] = NULL;
    }
  }

  /***************************************************************************/
  /* Count threads within critical section                                   */
  /***************************************************************************/
  EnterCriticalSection(&runsem);
  ThreadCount--;
  SendThreads--;
  GetLocalTime(&st);
  SRTRACE(t,"Thread %d (send) Exit at %d:%d:%d: ThreadCount %d\n",
          SendThreadNo,st.wHour,st.wMinute,st.wSecond,ThreadCount);
  OUTPUTNUMBER
  if (ThreadCount == 0)
  {
    PostMessage(hWndMain, WM_CLOSE, 0, 0);
  }
  LeaveCriticalSection(&runsem);
  return(0);
}

/*****************************************************************************/
/* InitializeWinMain - does the windows bits of initialisation               */
/*****************************************************************************/
BOOL InitializeWinMain(HINSTANCE hInstance)
{
  WAPPCDATA APPCData;
  WNDCLASS class;
  #define WinAPPCVERSION  0x0001

  /***************************************************************************/
  /* Startup WinAPPC                                                         */
  /***************************************************************************/
  if (WinAPPCStartup(WinAPPCVERSION,&APPCData))
  {
    return (FALSE);
  }

  /***************************************************************************/
  /* Register Window Class for our icon                                      */
  /***************************************************************************/

  class.style = 0;
  class.lpfnWndProc   = (WNDPROC)TPWndProc;
  class.cbClsExtra    = (DWORD)0;
  class.cbWndExtra    = (DWORD)0;
  class.hInstance     = hInstance;
  class.hIcon         = LoadIcon(hInstance,"MainIcon");
  class.hCursor       = LoadCursor(NULL, IDC_ARROW);
  class.hbrBackground = GetStockObject(WHITE_BRUSH);
  class.lpszMenuName  = (LPSTR) NULL;
  class.lpszClassName = (LPSTR) "MSENDRCV\0";

  if (!RegisterClass(&class))
  {
    return (FALSE);
  }

  /***************************************************************************/
  /* Create the window                                                       */
  /***************************************************************************/
  sprintf(title,"APPC Send/Receive TP\0");

  if ((hWndMain = CreateWindow("MSENDRCV\0",      /* window class            */
      title,                                      /* window name             */
      WS_MINIMIZE|WS_OVERLAPPEDWINDOW,            /* window style            */
      0,                                          /* x position              */
      0,                                          /* y position              */
      10,                                         /* width                   */
      10,                                         /* height                  */
      NULL,                                       /* parent handle           */
      NULL,                                       /* menu or child ID        */
      hInstance,                                  /* instance                */
      NULL))                                      /* additional info         */
      == NULL)
  {
    return (FALSE);
  }

  ShowWindow(hWndMain, SW_MINIMIZE);

  return(TRUE);

}

/*****************************************************************************/
/* Window proc for the iconised window                                       */
/*****************************************************************************/
LONG PASCAL TPWndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
  switch (message)
  {
    case WM_CREATE:
      break;

    case WM_QUERYOPEN:
      /***********************************************************************/
      /* Prevent the window being opened                                     */
      /***********************************************************************/
      break;

    case WM_CLOSE:
      return DefWindowProc(hWnd, message, wParam, lParam);
      break;

    case WM_DESTROY:
      PostQuitMessage(0);
      break;

    default:
      return DefWindowProc(hWnd, message, wParam, lParam);
      break;
  }
  return 0l;
}

/*****************************************************************************/
/* InitializeMain - blanks out variables not set in ReadConfig               */
/*****************************************************************************/
void InitializeMain()
{
  RcvThreads  = 0;
  SendThreads = 0;
  ThreadCount = 0;
  NumResults  = 0;
  cnvtptr     = (char *)&cnvt;

  datach      = 'A';

  InitializeCriticalSection(&runsem);
}

/*****************************************************************************/
/* IssueSendVerb - looks at the verb which has just completed and does the   */
/*                 next one                                                  */
/*****************************************************************************/
BOOL IssueSendVerb(CONVCB * convptr)
{
  BOOL TPEnded;
  struct appc_hdr * vcbptr;

//SRTRACE(t,"Thread %d (send) IssueSendVerb\n",convptr->thread);
  TPEnded = FALSE;
  vcbptr = (struct appc_hdr *) &convptr->vcb;
  if (vcbptr->opcode != 0x0000)
  {
    TPEnded = ProcessReturns(convptr);
  }
  if (!TPEnded)
  {
    switch (vcbptr->opcode)
    {
      case 0x0000:
        Build_TP_STARTED(convptr);

        /*********************************************************************/
        /*PERF* Don't re-generate data each time we issue a send!            */
        /*********************************************************************/
        GenerateData(convptr);
        break;

      case AP_TP_STARTED:
        Build_MC_ALLOCATE(convptr);
        break;

      case AP_M_ALLOCATE:
        if (vcbptr->primary_rc == AP_OK)
        {
          /*******************************************************************/
          /* confirm before the first send to find out if anyone there       */
          /*******************************************************************/
          Build_MC_CONFIRM(convptr);
        }
        else
        {
          /*******************************************************************/
          /* allocate timed out or connection is for incoming call           */
          /* if there are no conversations active, try again in 5 seconds    */
          /* otherwise retry immediately - someone must be out there         */
          /*******************************************************************/
          if (SimSendConvs == 0)
          {
            SRTRACE(t,"Thread %d:%d (send) wait 5 seconds before retry\n",
                    convptr->thread,convptr->conv);
            Sleep (5000);
          }
          SRTRACE(t,"Thread %d:%d (send) retrying\n",
                  convptr->thread,convptr->conv);
          Build_MC_ALLOCATE(convptr);
        }
        break;

      case AP_M_SEND_DATA:
        convptr->SendCount++;
        convptr->ConfirmCount++;
        if ((NumSends != 0) && (convptr->SendCount == NumSends))
        {
          /*******************************************************************/
          /* all sends done - deallocate                                     */
          /*******************************************************************/
          Build_MC_DEALLOCATE(convptr);
        }
        else if ((ConfirmEvery != 0) &&
                 (convptr->ConfirmCount == ConfirmEvery))
        {
          /*******************************************************************/
          /* time to confirm                                                 */
          /*******************************************************************/
          Build_MC_CONFIRM(convptr);
        }
        else
        {
          /*******************************************************************/
          /* just send more data                                             */
          /*******************************************************************/
          Build_MC_SEND_DATA(convptr);
        }
        break;

      case AP_M_CONFIRM:
        if (vcbptr->primary_rc == AP_OK)
        {
          if (convptr->SendCount == 0)
          {
            convptr->Counted = TRUE;
            EnterCriticalSection(&runsem);
            SimSendConvs++;
            OUTPUTNUMBER
            SRTRACE(t,"Thread %d (send) SimSendConvs %d\n",
                    convptr->thread,SimSendConvs);
            LeaveCriticalSection(&runsem);
          }
          convptr->ConfirmCount=0;
          Build_MC_SEND_DATA(convptr);
        }
        else
        {
          /*******************************************************************/
          /* if there are no conversations active, try again in 5 seconds    */
          /* otherwise retry immediately - someone must be out there         */
          /*******************************************************************/
          if (SimSendConvs == 0)
          {
            SRTRACE(t,"Thread %d:%d (send) wait 5 seconds before retry\n",
                    convptr->thread,convptr->conv);
            Sleep (5000);
          }
          SRTRACE(t,"Thread %d:%d (send) retrying\n",
                  convptr->thread,convptr->conv);
          Build_MC_ALLOCATE(convptr);
        }
        break;

      case AP_M_DEALLOCATE:
        Build_TP_ENDED(convptr);
        break;

      case AP_TP_ENDED:
        /*********************************************************************/
        /* quit                                                              */
        /*********************************************************************/
        TPEnded = TRUE;
        break;

      default:
        /*********************************************************************/
        /* What is this verb then ??                                         */
        /*********************************************************************/
        TPEnded = TRUE;
        DebugBreak();
        break;

    } /* Op-code switch */

  }

  /***************************************************************************/
  /* If send conversation has finished and was counted, count it down        */
  /***************************************************************************/
  if (TPEnded && convptr->Counted)
  {
    EnterCriticalSection(&runsem);
    SimSendConvs--;
    OUTPUTNUMBER
    SRTRACE(t,"Thread %d (send) SimSendConvs %d\n",
            convptr->thread,SimSendConvs);
    LeaveCriticalSection(&runsem);
  }

  /***************************************************************************/
  /* Now go ahead and issue the verb, if we're not finished                  */
  /***************************************************************************/
  if (!TPEnded)
  {
    convptr->async_corr = WinAsyncAPPCEx(convptr->hEvent,
                                         (long)(char *)(vcbptr));
    if (convptr->async_corr == 0)
      {
        SRTRACE(t,"Thread %d (send) WinAsync call %x failed corr %p\n",
                convptr->thread,vcbptr->opcode,
                convptr->async_corr);
        convptr->TPEnded = TRUE;
      }
  }

  SRTRFLUSH()
  return(TPEnded);

} /* Issue send verb */

/*****************************************************************************/
/* IssueRcvVerb - looks at the verb which has just completed and does the    */
/*                 next one                                                  */
/*****************************************************************************/
BOOL IssueRcvVerb(CONVCB * convptr)
{
  BOOL TPEnded;
  struct appc_hdr * vcbptr;

//SRTRACE(t,"Thread %d:%d (recv) IssueRcvVerb\n",
//        convptr->thread,convptr->conv);
  TPEnded = FALSE;
  vcbptr = (struct appc_hdr *) &convptr->vcb;
  if (vcbptr->opcode != 0x0000)
  {
    TPEnded = ProcessReturns(convptr);
  }
  if (!TPEnded)
  {
    switch (vcbptr->opcode)
    {
      case 0x0000:
        Build_RECEIVE_ALLOCATE(convptr);
        break;

      case AP_RECEIVE_ALLOCATE:
        StartConversation(convptr);
        Build_MC_RECEIVE_AND_WAIT(convptr);
        break;

      case AP_M_RECEIVE_AND_WAIT:
        if ((P_M_RAW(vcbptr)->what_rcvd == AP_DATA_COMPLETE) ||
            (P_M_RAW(vcbptr)->what_rcvd == AP_DATA_COMPLETE_CONFIRM) ||
            (P_M_RAW(vcbptr)->what_rcvd == AP_DATA_COMPLETE_CONFIRM_DEALL))
        {
          convptr->RcvCount++;
        }
        if ((P_M_RAW(vcbptr)->primary_rc == AP_DEALLOC_NORMAL))
        {
          /*******************************************************************/
          /* Issue TP_ENDED every time conversation deallocated              */
          /*******************************************************************/
          EndConversation(convptr);
          Build_TP_ENDED(convptr);
        }
        else if ((P_M_RAW(vcbptr)->what_rcvd == AP_CONFIRM_WHAT_RECEIVED) ||
                 (P_M_RAW(vcbptr)->what_rcvd == AP_DATA_COMPLETE_CONFIRM))
        {
          Build_MC_CONFIRMED(convptr);
          convptr->Deallocated = FALSE;
        }
        else if ((P_M_RAW(vcbptr)->what_rcvd == AP_CONFIRM_DEALLOCATE) ||
                 (P_M_RAW(vcbptr)->what_rcvd == AP_DATA_COMPLETE_CONFIRM_DEALL))
        {
          Build_MC_CONFIRMED(convptr);
          convptr->Deallocated = TRUE;
        }
        else
        {
          Build_MC_RECEIVE_AND_WAIT(convptr);
        }
        break;

      case AP_M_CONFIRMED:
        if (convptr->Deallocated)
        {
          /*******************************************************************/
          /* Issue TP_ENDED every time conversation deallocated              */
          /*******************************************************************/
          EndConversation(convptr);
          Build_TP_ENDED(convptr);
        }
        else
        {
          Build_MC_RECEIVE_AND_WAIT(convptr);
        }
        break;

      case AP_TP_ENDED:
        /*********************************************************************/
        /* set TPEnded                                                       */
        /*********************************************************************/
        TPEnded = TRUE;
        break;

      default:
        /*********************************************************************/
        /* What is this verb then ??                                         */
        /*********************************************************************/
        TPEnded = TRUE;
        DebugBreak();
        break;

    } /* Op-code switch */
    SRTRFLUSH()

  }

  /***************************************************************************/
  /* Now go ahead and issue the verb, if we're not finished                  */
  /***************************************************************************/
  if (!TPEnded)
  {
    convptr->async_corr = WinAsyncAPPCEx(convptr->hEvent,
                          (long)(char *)(vcbptr));
    if (convptr->async_corr == 0)
    {
      SRTRACE(t,"Thread %d:%d (recv) WinAsync call %x failed corr %p\n",
              convptr->thread,convptr->conv,
              vcbptr->opcode,convptr->async_corr);
      convptr->TPEnded = TRUE;
    }
  }

  SRTRFLUSH()
  return(TPEnded);

} /* Issue receive verb */

/*****************************************************************************/
/* Build routines to build all required verbs                                */
/*****************************************************************************/

void Build_TP_STARTED(CONVCB * convptr)
{
  TP_STARTED * vcbptr;
  SRTRACE(t,"Thread %d:%d (%s) Build_TP_Started\n",
          convptr->thread,convptr->conv,convptr->type);
  vcbptr = (TP_STARTED *) &(convptr->vcb);

  CLEARVCB

  vcbptr->opcode = AP_TP_STARTED;
  memcpy(&(vcbptr->lu_alias), LocalLUAlias, 8);
  memcpy(&(vcbptr->tp_name), TPName, 64);
}

void Build_TP_ENDED(CONVCB * convptr)
{
  TP_ENDED * vcbptr;
  SRTRACE(t,"Thread %d:%d (%s) Build_TP_Ended\n",
          convptr->thread,convptr->conv,convptr->type);
  vcbptr = (TP_ENDED *) &(convptr->vcb);

  CLEARVCB

  vcbptr->opcode = AP_TP_ENDED;
  memcpy(&(vcbptr->tp_id), convptr->TPid, 8);
  vcbptr->type = AP_SOFT;
}

void Build_RECEIVE_ALLOCATE(CONVCB * convptr)
{
  RECEIVE_ALLOCATE * vcbptr;
  SRTRACE(t,"Thread %d:%d (%s) Build_Receive_Allocate\n",
          convptr->thread,convptr->conv,convptr->type);
  vcbptr = (RECEIVE_ALLOCATE *) &(convptr->vcb);

  CLEARVCB

  vcbptr->opcode = AP_RECEIVE_ALLOCATE;
  memcpy(vcbptr->tp_name, LocalTPName, 64);
}

void Build_MC_ALLOCATE(CONVCB * convptr)
{
  MC_ALLOCATE * vcbptr;
  SRTRACE(t,"Thread %d:%d (%s) Build_MC_Allocate\n",
          convptr->thread,convptr->conv,convptr->type);
  vcbptr = (MC_ALLOCATE *) &(convptr->vcb);

  CLEARVCB

  vcbptr->opcode = AP_M_ALLOCATE;
  vcbptr->opext = AP_MAPPED_CONVERSATION;
  memcpy(vcbptr->tp_id,convptr->TPid, 8);
  vcbptr->sync_level = AP_CONFIRM_SYNC_LEVEL;
  vcbptr->rtn_ctl = AP_WHEN_SESSION_ALLOCATED;
  memcpy(vcbptr->plu_alias, RemoteLUAlias, 8);
  memcpy(vcbptr->mode_name, ModeName, 8);
  memcpy(vcbptr->tp_name, RemoteTPName, 64);
  vcbptr->security = AP_NONE;
}

void Build_MC_CONFIRM(CONVCB * convptr)
{
  MC_CONFIRM * vcbptr;
//SRTRACE(t,"Thread %d:%d (%s) Build_MC_Confirm\n",
//        convptr->thread,convptr->conv,convptr->type);
  vcbptr = (MC_CONFIRM *) &(convptr->vcb);

  CLEARVCB

  vcbptr->opcode = AP_M_CONFIRM;
  vcbptr->opext = AP_MAPPED_CONVERSATION;
  memcpy(vcbptr->tp_id,convptr->TPid, 8);
  vcbptr->conv_id = convptr->Convid;
}

void Build_MC_CONFIRMED(CONVCB * convptr)
{
  MC_CONFIRMED * vcbptr;
//SRTRACE(t,"Thread %d:%d (%s) Build_MC_Confirmed\n",
//        convptr->thread,convptr->conv,convptr->type);
  vcbptr = (MC_CONFIRMED *) &(convptr->vcb);

  CLEARVCB

  vcbptr->opcode = AP_M_CONFIRMED;
  vcbptr->opext = AP_MAPPED_CONVERSATION;
  memcpy(&(vcbptr->tp_id),convptr->TPid, 8);
  vcbptr->conv_id = convptr->Convid;
}

void Build_MC_DEALLOCATE(CONVCB * convptr)
{
  MC_DEALLOCATE * vcbptr;
  SRTRACE(t,"Thread %d:%d (%s) Build_MC_Deallocate\n",
          convptr->thread,convptr->conv,convptr->type);
  vcbptr = (MC_DEALLOCATE *) &(convptr->vcb);

  CLEARVCB

  vcbptr->opcode = AP_M_DEALLOCATE;
  vcbptr->opext = AP_MAPPED_CONVERSATION;
  memcpy(&(vcbptr->tp_id),convptr->TPid, 8);
  vcbptr->conv_id = convptr->Convid;
  if (ConfirmEvery == 0)
  {
     vcbptr->dealloc_type = AP_FLUSH;
  }
  else
  {
     vcbptr->dealloc_type = AP_SYNC_LEVEL;
  }
}

void Build_MC_RECEIVE_AND_WAIT(CONVCB * convptr)
{
  MC_RECEIVE_AND_WAIT * vcbptr;
//SRTRACE(t,"Thread %d:%d (%s) Build_MC_Receive_And_Wait\n",
//        convptr->thread,convptr->conv,convptr->type);
  vcbptr = (MC_RECEIVE_AND_WAIT *) &(convptr->vcb);

  CLEARVCB

  vcbptr->opcode = AP_M_RECEIVE_AND_WAIT;
  vcbptr->opext = AP_MAPPED_CONVERSATION;
  memcpy(&(vcbptr->tp_id),convptr->TPid, 8);
  vcbptr->conv_id = convptr->Convid;
  vcbptr->rtn_status = AP_YES;
  vcbptr->max_len = RcvSize;
  vcbptr->dptr = convptr->DataPtr;
}

void Build_MC_SEND_DATA(CONVCB * convptr)
{
  MC_SEND_DATA * vcbptr;
//SRTRACE(t,"Thread %d:%d (%s) Build_MC_Send_Data\n",
//        convptr->thread,convptr->conv,convptr->type);
  vcbptr = (MC_SEND_DATA *) &(convptr->vcb);

  CLEARVCB

  //  PERF - GenerateData();

  vcbptr->opcode = AP_M_SEND_DATA;
  vcbptr->opext = AP_MAPPED_CONVERSATION;
  memcpy(&(vcbptr->tp_id),convptr->TPid, 8);
  vcbptr->conv_id = convptr->Convid;
  vcbptr->dlen = convptr->SendSize;
  vcbptr->dptr = convptr->DataPtr;
  vcbptr->type = AP_NONE;
}

/*****************************************************************************/
/* ProcessReturns - Checks return codes from the last verb to complete and   */
/*                  saves conversation id and tp id in the conversation cb   */
/*****************************************************************************/
BOOL ProcessReturns(CONVCB * convptr)
{
  BOOL TPEnded = FALSE;
  struct appc_hdr * vcbptr;
  SYSTEMTIME st;

//SRTRACE(t,"Thread %d:%d (%s) ProcessReturns\n",
//        convptr->thread,convptr->conv,convptr->type);
  vcbptr = (struct appc_hdr *) &(convptr->vcb);

  GetLocalTime(&st);
  if (vcbptr->primary_rc != AP_OK)
  {
    SRTRACE(t,"Thread %d:%d (%s) error: %s prc %4.4x src %8.8x at %d:%d:%d\n",
            convptr->thread,convptr->conv,convptr->type,
            VerbName[vcbptr->opcode],
            APPC_FLIPI(vcbptr->primary_rc),APPC_FLIPL(vcbptr->secondary_rc),
            st.wHour,st.wMinute,st.wSecond);
    if ((vcbptr->opcode == AP_M_RECEIVE_AND_WAIT) &&
        (vcbptr->primary_rc == AP_DEALLOC_NORMAL))
    {
      SRTRACE(t,"Thread %d:%d (%s) MC_RECEIVE_AND_WAIT completed with DEALLOC_NORMAL\n",\
              convptr->thread,convptr->conv,convptr->type);
    }
    else if ((vcbptr->opcode == AP_M_CONFIRM) &&
             (vcbptr->primary_rc == AP_ALLOCATION_ERROR))
    {
      SRTRACE(t,"Thread %d:%d (%s) MC_CONFIRM completed with ALLOCATION_ERROR\n",
              convptr->thread,convptr->conv,convptr->type);
    }
    else if ((vcbptr->opcode == AP_M_ALLOCATE) &&
             (vcbptr->primary_rc == AP_ALLOCATION_ERROR))
    {
      SRTRACE(t,"Thread %d:%d (%s) MC_ALLOCATE completed with ALLOCATION_ERROR\n",
              convptr->thread,convptr->conv,convptr->type);
    }
    else
    {
      TPEnded = TRUE;
      SRTRACE(t,"Thread %d:%d (%s) unexpected error on %s - set TPEnded\n",
              convptr->thread,convptr->conv,convptr->type,
              VerbName[vcbptr->opcode]);
    }
  }
  else
  {
    switch (vcbptr->opcode)
    {
      case AP_TP_STARTED:
        SRTRACE(t,"Thread %d:%d (%s) TP_Started completed at %d:%d:%d\n",
                convptr->thread,convptr->conv,convptr->type,
                st.wHour,st.wMinute,st.wSecond);
        memcpy(convptr->TPid,&(P_TPS(vcbptr)->tp_id),8);
        break;

      case AP_TP_ENDED:
        SRTRACE(t,"Thread %d:%d (%s) TP_Ended completed at %d:%d:%d\n",
                convptr->thread,convptr->conv,convptr->type,
                st.wHour,st.wMinute,st.wSecond);
        break;

      case AP_RECEIVE_ALLOCATE:
        SRTRACE(t,"Thread %d:%d (%s) Receive_Allocate completed at %d:%d:%d\n",
                convptr->thread,convptr->conv,convptr->type,
                st.wHour,st.wMinute,st.wSecond);
        memcpy(convptr->TPid,&(P_RAL(vcbptr)->tp_id),8);
        convptr->Convid = P_RAL(vcbptr)->conv_id;
        break;

      case AP_M_ALLOCATE:
        SRTRACE(t,"Thread %d:%d (%s) MC_Allocate completed at %d:%d:%d\n",
                convptr->thread,convptr->conv,convptr->type,
                st.wHour,st.wMinute,st.wSecond);
        convptr->Convid = P_M_ALC(vcbptr)->conv_id;
        break;

      case AP_M_SEND_DATA:
//      SRTRACE(t,"Thread %d:%d (%s) MC_Send_Data completed at %d:%d:%d\n",
//              convptr->thread,convptr->conv,convptr->type,
//              st.wHour,st.wMinute,st.wSecond);
        break;

      case AP_M_DEALLOCATE:
SRTRACE(t,"Thread %d:%d (%s) MC_Deallocate completed at %d:%d:%d: send count %d\n",
                convptr->thread,convptr->conv,convptr->type,
                st.wHour,st.wMinute,st.wSecond,
                convptr->SendCount);
        convptr->Convid = 0;
        break;

      case AP_M_CONFIRM:
SRTRACE(t,"Thread %d:%d (%s) MC_Confirm completed at %d:%d:%d: send count %d\n",
                convptr->thread,convptr->conv,convptr->type,
                st.wHour,st.wMinute,st.wSecond,
                convptr->SendCount);
        break;

      case AP_M_RECEIVE_AND_WAIT:
//      SRTRACE(t,"Thread %d:%d (%s) MC_Receive_And_Wait completed at %d:%d:%d\n",
//              convptr->thread,convptr->conv,convptr->type,
//              st.wHour,st.wMinute,st.wSecond);
        break;

      case AP_M_CONFIRMED:
SRTRACE(t,"Thread %d:%d (%s) MC_Confirmed completed at %d:%d:%d: receive count %d\n",
                convptr->thread,convptr->conv,convptr->type,
                st.wHour,st.wMinute,st.wSecond,
                convptr->RcvCount);
        break;

      default:
        SRTRACE(t,"Thread %d:%d (%s) UNKNOWN opcode - set TPEnded\n",
                convptr->thread,convptr->conv,convptr->type);
        TPEnded = TRUE;
        DebugBreak();
        break;
    }
  }
  SRTRFLUSH()
  return(TPEnded);
}

/*****************************************************************************/
/* ReadConfig - Reads config info from MSENDRCV.CFG and allocates buffer for */
/*              sending                                                      */
/*****************************************************************************/
void ReadConfig()
{
  char buffer[200];

  if (!ReadString("ResultFile",FileName,60))
  {
    strcpy(FileName,"MSENDRCV.OUT");
  }

  if (!ReadString("TraceFile",TraceFile,60))
  {
    strcpy(TraceFile,"MSENDRCV.TRC");
  }

  strcpy(TPName,"MSENDRCV");
  PadString(TPName,64);
  CONV_A_TO_E(TPName,64);

  if (!ReadString("LocalTPName",LocalTPName,64))
  {
    strcpy(LocalTPName,"MSENDRCVTP");
  }
  PadString(LocalTPName,64);
  CONV_A_TO_E(LocalTPName,64);

  if (!ReadString("RemoteTPName",RemoteTPName,64))
  {
    strcpy(RemoteTPName,"MSENDRCVTP");
  }
  PadString(RemoteTPName,64);
  CONV_A_TO_E(RemoteTPName,64);

  if (!ReadString("LocalLUAlias",LocalLUAlias,8))
  {
    strcpy(LocalLUAlias,"SENDLU");
  }
  PadString(LocalLUAlias,8);

  if (!ReadString("RemoteLUAlias",RemoteLUAlias,8))
  {
    strcpy(RemoteLUAlias,"RECVLU");
  }
  PadString(RemoteLUAlias,8);

  if (!ReadString("ModeName",ModeName,8))
  {
    strcpy(ModeName,"#INTER");
  }
  PadString(ModeName,8);
  CONV_A_TO_E(ModeName,8);

  NumSends=8;
  if (ReadString("NumSends",buffer,200))
  {
    NumSends=atoi(buffer);
  }

  ConfirmEvery=2;
  if (ReadString("ConfirmEvery",buffer,200))
  {
    ConfirmEvery=atoi(buffer);
  }

  SendSize=256;
  if (ReadString("SendSize",buffer,200))
  {
    SendSize=atoi(buffer);
  }

  RcvSize=4096;
  if (ReadString("RcvSize",buffer,200))
  {
    RcvSize=atoi(buffer);
  }

  NumRcvThreads = 2;
  if (ReadString("NumRcvThreads",buffer,200))
  {
    NumRcvThreads=atoi(buffer);
  }

  NumSendConvs = 4;
  if (ReadString("NumSendConvs",buffer,200))
  {
    NumSendConvs=atoi(buffer);
  }

  NumRcvConvs = 4;
  if (ReadString("NumRcvConvs",buffer,200))
  {
    NumRcvConvs=atoi(buffer);
  }
  NumRalcs = 0;
  RcvConvs = 0;

  ResultBuf = (NumRcvConvs == 0) ?
              NULL : malloc(NumRcvConvs * sizeof(RESULT));
  ResultPtr = ResultBuf;

  if (NumRcvConvs > 0 && NumRcvThreads * 63 < NumRcvConvs)
  {
    NumRcvThreads = NumRcvConvs / 63 + 1;
  }

  if (NumRcvConvs > 0 && NumRcvThreads > NumRcvConvs)
  {
    NumRcvThreads = NumRcvConvs;
  }
}

/*****************************************************************************/
/* CONV_A_TO_E - ASCII to EBCDIC conversion routine                          */
/*****************************************************************************/
void CONV_A_TO_E(char * string,int length)
{
  memset(cnvtptr,0,sizeof(cnvt));

  cnvt.opcode       = SV_CONVERT;
  cnvt.direction    = SV_ASCII_TO_EBCDIC;
  cnvt.char_set     = SV_AE;

  cnvt.len          = length;
  cnvt.source       = string;
  cnvt.target       = string;

  ACSSVC_C((long)(char *) (cnvtptr));
}

/*****************************************************************************/
/* CONV_E_TO_A - EBCDIC to ASCII conversion routine                          */
/*****************************************************************************/
void CONV_E_TO_A(char * string,int length)
{
  memset(cnvtptr,0,sizeof(cnvt));

  cnvt.opcode       = SV_CONVERT;
  cnvt.direction    = SV_EBCDIC_TO_ASCII;
  cnvt.char_set     = SV_AE;
  cnvt.len          = length;
  cnvt.source       = string;
  cnvt.target       = string;

  ACSSVC_C((long)(char *) (cnvtptr));
}

/*****************************************************************************/
/* StartConversation - Record start time for this conversation               */
/*****************************************************************************/
void StartConversation(CONVCB * convptr)
{
  convptr->ConvStarted = GetTickCount();
}

/*****************************************************************************/
/* EndConversation - Calculate elapsed time for this conversation            */
/*****************************************************************************/
void EndConversation(CONVCB * convptr)
{
  if (ResultPtr != NULL)
  {
    /*************************************************************************/
    /* Make sure we don't go over the end of the allocated area              */
    /*************************************************************************/
    if (NumResults < NumRcvConvs)
    {
      *ResultPtr++ = (GetTickCount() - convptr->ConvStarted);
      NumResults++;
    }
    else
    {
      SRTRACE(t,"Thread %d:%d Too many calls to EndConversation\n",
              convptr->thread,convptr->conv);
    }
  }
}

/*****************************************************************************/
/* GenerateData    - Fill in data buffer                                     */
/*****************************************************************************/
void GenerateData(CONVCB * convptr)
{
  int i;
  int div;
  int rem;
  char * dptr;

  dptr = convptr->DataPtr;
  div = convptr->SendSize / 5;
  rem = convptr->SendSize % 5;

  for (; div--;)
  {
    for (i=4; i--; *dptr++ = datach);
    *dptr++ = '.';
  }
  for (; rem--; *dptr++ = datach);

  EnterCriticalSection(&runsem);
  datach = (datach=='Z' ? 'A' : datach + 1);
  LeaveCriticalSection(&runsem);
}

/*****************************************************************************/
/* OutputResults - dump the times of conversations to file                   */
/*****************************************************************************/
void OutputResults()
{
  FILE *h = NULL;
  RESULT * ptr = NULL;
  unsigned short i = 0;

  h = fopen(FileName,"w");
  if (h != NULL)
  {
    fprintf(h,"\nMSENDRCV Results\n----------------\n\n");
    CONV_E_TO_A(LocalTPName,64);
    fprintf(h,"Local TP Name              = %.64s\n",LocalTPName);
    CONV_E_TO_A(RemoteTPName,64);
    fprintf(h,"Remote TP Name             = %.64s\n",RemoteTPName);
    fprintf(h,"Local LU Alias             = %.8s\n",LocalLUAlias);
    fprintf(h,"Remote LU Alias            = %.8s\n",RemoteLUAlias);
    CONV_E_TO_A(ModeName,8);
    fprintf(h,"ModeName                   = %.8s\n",ModeName);
    fprintf(h,"No. of receive threads     = %d\n",NumRcvThreads);
    fprintf(h,"No. of send conversations  = %d\n",NumSendConvs);
    fprintf(h,"Sends per conversation     = %d\n",NumSends);
    fprintf(h,"Sends between confirms     = %d\n",ConfirmEvery);
    fprintf(h,"Bytes per send             = %d\n",SendSize);
    fprintf(h,"No. of rcv convs started   = %d\n",NumRalcs);
    fprintf(h,"No. of rcv convs completed = %d\n",RcvConvs);
    fprintf(h,"\n");

    ptr = ResultBuf;
    while (ptr < ResultPtr)
    {
      fprintf(h,"Conversation number %d, time = %.3f seconds\n",i++,
                                                (((float) *ptr++) / 1000.0 ));
    }
    fclose(h);
  }
}

/*****************************************************************************/
/* ReadString - Get a line of text from the config file                      */
/*****************************************************************************/
int ReadString(char * lpValueName,char * lpData, int maxlen)
{
  char       buffer[200];
  char      *p = NULL;
  FILE      *h = NULL;
  BOOL       match = FALSE;
  BOOL       eof   = FALSE;
  int        rc = 0;
  int        ch = 0;
  int        i = 0;
  BOOL       gotdata = FALSE;
  char       separators[] = " =\t\n";

  GetModuleFileName( hInst, buffer, sizeof(buffer) );
  lstrcpy( buffer+lstrlen(buffer) - 4, ".CFG" );
  h = fopen( buffer, "r" );
  buffer[0] = '\0';

  lpValueName=strupr(lpValueName);

  if (h != NULL)
  {
    while ((!match) && (!eof))
    {
      /***********************************************************************/
      /* Use fgetc to read a line of text from the file                      */
      /***********************************************************************/
      for (i=0; (i<sizeof(buffer))     &&
                ((ch=getc(h)) != EOF)  &&
                ((char)ch != '\n');
                                   i++)
      {
        buffer[i] = (char)ch;
      }
      if ((char)ch == '\n')
      {
        buffer[i++] = (char)ch;
      }
      if (ch == EOF)
      {
        eof = TRUE;
      }
      else
      {
        /*********************************************************************/
        /* Compare the first token in the line read with the requested parm  */
        /*********************************************************************/
        if (!strcmpi(strupr(strtok(buffer, separators)), lpValueName))
        {
          match = TRUE;
          /*******************************************************************/
          /* Get a pointer to the second token (the value we want)           */
          /*******************************************************************/
          p = strtok(NULL, separators);

          /*******************************************************************/
          /* Copy the data IF there is some                                  */
          /*******************************************************************/
          if (p != NULL)
          {
            /*****************************************************************/
            /* Force a NULL after the second token                           */
            /*****************************************************************/
            strtok(NULL, separators);

            /*****************************************************************/
            /* Copy the data                                                 */
            /*****************************************************************/
            strncpy(lpData, p, maxlen);
            gotdata = TRUE;
          }
          else
          {
            gotdata = FALSE;
          }
        }
      }
    }

    if (gotdata)
    {
      rc = 1;
    }

    fclose(h);

  }

  return(rc);
}

/*****************************************************************************/
/* PadString - Remove terminating NULL  and pad on the right with spaces     */
/*****************************************************************************/
void PadString(char * string,int length)
{
  char * p;
  if ((p=memchr(string,'\0',length)) != NULL)
  {
    while (p < string+length)
    {
      *p++=' ';
    }
  }
}

