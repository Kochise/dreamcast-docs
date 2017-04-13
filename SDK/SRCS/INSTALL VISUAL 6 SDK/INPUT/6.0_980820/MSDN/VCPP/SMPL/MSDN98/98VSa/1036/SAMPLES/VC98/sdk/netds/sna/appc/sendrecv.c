/* sendrecv.c */
/* (C) COPYRIGHT DATA CONNECTION LIMITED 1993 */

/*****************************************************************************/
/* Change History                                                            */
/*                                                                           */
/*       04/05/93 NGR Created.                                               */
/* TPED  26/05/93 SW  RECVTP must issue TP_ENDED after each conversation     */
/* PERF  24/06/93 SW  Don't regenerate data for each SEND verb               */
/* FILE  02/07/93 NGR Don't attempt to close NULL file handle                */
/* PATH  10/08/93 NGR Gord's changes to get config from current directory    */
/*****************************************************************************/

/*****************************************************************************/
/*                                                                           */
/* ROUTINE : SENDRECV                                                        */
/*                                                                           */
/* FUNCTION: This file contains the main routines for a simple bulk data     */
/*           sending and receiving TPs SENDTP and RECVTP                     */
/*                                                                           */
/* INPUTS  : SENDTP.CFG (file) (documented below)                            */
/*           RECVTP.CFG (file) (documented below)                            */
/*                                                                           */
/* OUTPUTS : SENDTP.OUT                                                      */
/*           RECVTP.OUT                                                      */
/*                                                                           */
/*****************************************************************************/

/*****************************************************************************/
/* Operation:                                                                */
/*                                                                           */
/* SENDTP                                                                    */
/* DOS and OS/2. Simple command line TP which simply allocates, does the     */
/* specified number of send_data and then deallocates. Done via a while loop */
/* which makes calls to IssueNextVerb.                                       */
/*                                                                           */
/* RECVTP                                                                    */
/* As SENDTP, but it receive_allocates, then receive_and_waits until it gets */
/* deallocated. Repeat this NumConversation times.                           */
/*                                                                           */
/* NT and Win16. Simple windows apps which use the async verbs and control   */
/* operation via the window proc of a minimised window. This proc makes      */
/* calls to IssueNextVerb on receipt of an async_complete message            */
/*                                                                           */
/* IssueNextVerb uses the opcode of the verb which just completed to         */
/* decide what to issue next, and calls the appropriate do_ routine to fill  */
/* in the vcb, it then calls the appropriate APPC entry point.               */
/*                                                                           */
/* Send TP will initially issue a SEND_CONVERSATION verb in order to send    */
/* the number of conversations to be done to the Recv TP which expect this   */
/* to be sent to it.                                                         */
/*                                                                           */
/* The applications will terminate if they encounter an error and do not     */
/* produce diagnostic output so the APPC API trace is the best place to look */
/*****************************************************************************/

/*****************************************************************************/
/* Configuration files:                                                      */
/*                                                                           */
/* Configuration file is C:\SENDTP.CFG or RECVTP.CFG which contains          */
/* the following, one per line in any order. If not present then the given   */
/* default is assumed.                                                       */
/*                                                                           */
/* ResultFile = <Name of file for results, default C:\(SEND/RECV)TP.OUT>     */
/* LocalTPName = <Name to be used for TP started, default SENDTP/RECVTP>     */
/*                                                                           */
/* The following only apply to SENDTP                                        */
/*                                                                           */
/* NumConversations = <Number of conversations to be done, default = 1>      */
/* LocalLUAlias = <Alias for local LU (!), default SENDLU>                   */
/* RemoteLUAlias = <Alias for remote LU (!!), default RECVLU>                */
/* ModeName = <!?! default #INTER>                                           */
/* RemoteTPName = <name of the TP, default RECVTP>                           */
/* NumSends = <number of SEND_DATA verbs per conversation, default = 2>      */
/* ConfirmEvery = <number of SEND_DATA verbs between CONFIRMs, default = 1>  */
/* SendSize = <number of bytes per SEND_DATA, default = 1024>                */
/* SendConversation = <use the SEND_CONVERSATION verb, default = no>         */
/*                                                                           */
/* Note that if SendConversation is used then NumSends is irrelevant, the TP */
/* will simply do NumConversations SEND_CONVERSATION verbs                   */
/* If NumConversations is zero, then the TPs will do an infinite number of   */
/* conversations.                                                            */
/* If NumSends is zero, then SENDTP will never DEALLOCATE the first          */
/* conversation.                                                             */
/* If ConfirmEvery is zero, then SENDTP will not issue CONFIRM verbs.        */
/*****************************************************************************/
#if (defined(WINDOWS)||defined(WIN32))
#include <windows.h>
HINSTANCE hInst;
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winappc.h>
#include <wincsv.h>
#include "sendrecv.h"

#if defined(DOS5) || defined(DOS)
#define SYNC
#endif

#ifdef WINDOWS
#define memset(x,y,z) _fmemset(x,y,z)
#define memchr(x,y,z) _fmemchr(x,y,z)
#define strupr(x) _fstrupr(x)
#define strcmpi(x,y) _fstricmp(x,y)
#define strncpy(x,y,z) _fstrncpy(x,y,z)
#endif

#ifdef SYNC
/*****************************************************************************/
/* main - reads initialisation info and creates threads                      */
/*        DOS & OS\2 version                                                 */
/*****************************************************************************/
void main( int argc, char FAR * argv[])
{

#if defined(WIN32) || defined(WINDOWS)
  WAPPCDATA APPCData;
  WNDCLASS class;
  #define WinAPPCVERSION  0x0001

  /**************************************************************************/
  /* Startup WinAPPC                                                        */
  /**************************************************************************/
  if (WinAPPCStartup(WinAPPCVERSION,&APPCData))
  {
     return (FALSE);
  }
#endif

  printf("\n\n\n\n\n\n\n");
#ifdef SENDTP
  printf("SENDTP - APPC Bulk data send program to be used with RECVTP\n");
#else
  printf("RECVTP - APPC Bulk data recv program to be used with SENDTP\n");
#endif
  printf("^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\n\n");


  InitialiseMain();
  ReadConfig();

  while (!TPDead)
  {
     IssueNextVerb();
  }
#ifdef SENDTP
  OutputResults();
#endif

#if defined(WIN32) || defined(WINDOWS)
  WinAPPCCleanup();
#endif

  printf("Finished");

}
#else
/*****************************************************************************/
/* WinMain - reads initialisation info and controls message loop             */
/*           NT and Win16 version                                            */
/*****************************************************************************/
int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow)
{

  MSG msg;

  hInst = hInstance;

  InitialiseMain();

  if (!InitialiseWinMain(hInstance))
  {
     return (FALSE);
  }

  ReadConfig();

  while(GetMessage(&msg,NULL,0,0))
  {
     TranslateMessage(&msg);
     DispatchMessage(&msg);
  }

  return msg.wParam;         /* save exit parameter for return               */

}

/*****************************************************************************/
/* InitialiseWinMain - does the windows bits of initialisation               */
/*****************************************************************************/
BOOL InitialiseWinMain(HINSTANCE hInstance)
{
   WAPPCDATA APPCData;
   WNDCLASS class;
   #define WinAPPCVERSION  0x0001

   /**************************************************************************/
   /* Startup WinAPPC                                                        */
   /**************************************************************************/
   if (WinAPPCStartup(WinAPPCVERSION,&APPCData))
   {
      return (FALSE);
   }

   if ( (ASYNC_COMPLETE =
         RegisterWindowMessage(WIN_APPC_ASYNC_COMPLETE_MESSAGE)) == 0 )
   {
      return (0);
   }

   async_corr=0;

   /**************************************************************************/
   /* Register Window Class for our icon                                     */
   /**************************************************************************/

   class.style = 0;
   class.lpfnWndProc   = (WNDPROC)TPWndProc;
   class.cbClsExtra    = (DWORD)0;
   class.cbWndExtra    = (DWORD)0;
   class.hInstance     = hInstance;
   class.hIcon         = LoadIcon(hInstance,"MainIcon");
   class.hCursor       = LoadCursor(NULL, IDC_ARROW);
   class.hbrBackground = GetStockObject(WHITE_BRUSH);
   class.lpszMenuName  = (LPSTR) NULL;
   class.lpszClassName = (LPSTR) "SENDRECV\0";

   if (!RegisterClass(&class))
   {
     return (FALSE);
   }

   /**************************************************************************/
   /* Create the window                                                      */
   /**************************************************************************/
#ifdef SENDTP
   sprintf(title,"APPC Send TP\0");
#else
   sprintf(title,"APPC Receive TP\0");
#endif

   if ((hWndMain = CreateWindow("SENDRECV\0",      /* window class           */
       title,                                      /* window name            */
       WS_MINIMIZE|WS_OVERLAPPEDWINDOW,            /* window style           */
       0,                                          /* x position             */
       0,                                          /* y position             */
       10,                                         /* width                  */
       10,                                         /* height                 */
       NULL,                                       /* parent handle          */
       NULL,                                       /* menu or child ID       */
       hInstance,                                  /* instance               */
       NULL))                                      /* additional info        */
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
LONG FAR PASCAL TPWndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
   if (message == ASYNC_COMPLETE)
   {
      if (wParam != (WPARAM) async_corr)
      {
         /*****************************************************************/
         /* This is not the correlator we were expecting, so we must die. */
         /*****************************************************************/
         TPDead = TRUE;
#ifdef WIN32
         DebugBreak();
#endif
      }
      else
      {
#ifdef SENDTP
         IssueNextVerb();
#else
         if (!GotNumConv)
         {
            /*****************************************************************/
            /* We are still in the process of getting the number of convs to */
            /* be done, so do the next stage of this. Note if all is not OK  */
            /* then we just die.                                             */
            /*****************************************************************/
            Get_Run_Details();
            if (TPDead)
            {
               PostMessage(hWndMain, WM_CLOSE, 0, 0);
            }
         }
         else
         {
            IssueNextVerb();
         }
#endif
      }
   }
   else
   {
      switch (message)
      {
         case WM_CREATE:
            /*****************************************************************/
            /* Post a message to ourselves to kick off the first verb        */
            /*****************************************************************/
            vcb.hdr.opcode = 0x0000;
            async_corr = 0;
            PostMessage(hWnd, ASYNC_COMPLETE, (WPARAM)async_corr,
                                                 (LPARAM)(char FAR *)(vcbptr));
            break;

         case WM_QUERYOPEN:
            /*****************************************************************/
            /* Prevent the window being opened                               */
            /*****************************************************************/
            break;

         case WM_CLOSE:
            TPDead = TRUE;
            WinAPPCCleanup();
#ifdef SENDTP
            OutputResults();
#endif
            return DefWindowProc(hWnd, message, wParam, lParam);
            break;

         case WM_DESTROY:
			if( DataPtr != NULL )
			{
#ifdef WINDOWS
				GlobalUnlock(LOWORD(GlobalHandle(SELECTOROF(DataPtr))));
				GlobalFree(LOWORD(GlobalHandle(SELECTOROF(DataPtr))));
#else
 #ifdef WIN32
 				free(DataPtr);
 #else
	 			DosFreeSeg(selector);
 #endif
#endif
			}
            PostQuitMessage(0);
            break;

         default:
            return DefWindowProc(hWnd, message, wParam, lParam);
            break;
      }
   }
   return 0l;
}

#endif

/*****************************************************************************/
/* InitialiseMain - blanks out variables.                                    */
/*****************************************************************************/
void InitialiseMain()
{
   NumConversations=0;
   FirstConv=TRUE;
   memset(LocalTPName,0,64);
   ConvCount=0;
   Convid=0;
   SendSize=0;
   memset(TPid,0,8);
   TPDead=FALSE;
   vcbptr=(char *)&vcb;
   cnvtptr=(char *)&cnvt;

#ifdef SENDTP
   NumSends=0;
   SendConversation=0;
   ConfirmEvery=0;
   SendCount=0;
   ConfirmCount=0;
   datach='A';

   memset(LocalLUAlias,0,8);
   memset(RemoteLUAlias,0,8);
   memset(ModeName,0,8);
   memset(RemoteTPName,0,64);
#else
   GotNumConv = FALSE;
   GetStage = 0;
#endif


}

/*****************************************************************************/
/* IssueNextVerb - looks at the verb which has just completed and does the   */
/*                 next one                                                  */
/*****************************************************************************/
void IssueNextVerb()
{
   if (vcb.hdr.opcode != 0x0000)
   {
      ProcessReturns();
   }
   if (!TPDead)
   {
      switch (vcb.hdr.opcode)
      {
         case 0x0000:
#ifdef SENDTP
            Build_TP_STARTED();

            /**************************************************************/
            /*PERF* Don't re-generate data each time we issue a send!     */
            /**************************************************************/
            GenerateData();

#else
            Build_RECEIVE_ALLOCATE();
#endif
            break;

#ifdef SENDTP
         case AP_TP_STARTED:
            if (ConvCount == 0)
            {
               Send_Run_Details();
            }
            if (!TPDead)
            {
               NewConversation();
               if (SendConversation)
               {
                  Build_MC_SEND_CONVERSATION();
               }
               else
               {
                  Build_MC_ALLOCATE();
               }
            }
            break;

         case AP_M_ALLOCATE:
            Build_MC_SEND_DATA();
            break;

         case AP_M_SEND_DATA:
            SendCount++;
            ConfirmCount++;
            if ((NumSends != 0) && (SendCount == NumSends))
            {
               Build_MC_DEALLOCATE();
            }
            else if ((ConfirmEvery != 0) && (ConfirmCount == ConfirmEvery))
            {
               Build_MC_CONFIRM();
            }
            else
            {
               Build_MC_SEND_DATA();
            }
            break;

         case AP_M_SEND_CONVERSATION:
            if ((NumConversations != 0) && (ConvCount == NumConversations))
            {
               NewConversation();
               Build_TP_ENDED();
            }
            else
            {
               NewConversation();
               Build_MC_SEND_CONVERSATION();
            }
            break;

         case AP_M_CONFIRM:
            ConfirmCount=0;
            Build_MC_SEND_DATA();
            break;

         case AP_M_DEALLOCATE:
            if ((NumConversations !=0) && (ConvCount == NumConversations))
            {
               NewConversation();
               Build_TP_ENDED();
            }
            else
            {
               NewConversation();
               Build_MC_ALLOCATE();
            }
            break;

         case AP_TP_ENDED:
            /**************************************************************/
            /*TPED* Quit out and die if SENDTP                            */
            /**************************************************************/
            TPDead = TRUE;
            break;
#else
         case AP_RECEIVE_ALLOCATE:
            NewConversation();
            Build_MC_RECEIVE_AND_WAIT();
            break;

         case AP_M_RECEIVE_AND_WAIT:
            if ((vcb.rcvwait.primary_rc == AP_DEALLOC_NORMAL))
            {
               /*************************************************************/
               /*TPED* Issue TP_ENDED every time conversation deallocated   */
               /*************************************************************/
               Build_TP_ENDED();
            }
            else if ((vcb.rcvwait.what_rcvd == AP_CONFIRM_WHAT_RECEIVED) ||
                     (vcb.rcvwait.what_rcvd == AP_DATA_COMPLETE_CONFIRM))
            {
               Build_MC_CONFIRMED();
               Deallocated = FALSE;
            }
            else if ((vcb.rcvwait.what_rcvd == AP_CONFIRM_DEALLOCATE) ||
                     (vcb.rcvwait.what_rcvd == AP_DATA_COMPLETE_CONFIRM_DEALL))
            {
               Build_MC_CONFIRMED();
               Deallocated = TRUE;
            }
            else
            {
               Build_MC_RECEIVE_AND_WAIT();
            }
            break;

         case AP_M_CONFIRMED:
            if (Deallocated)
            {
               /*************************************************************/
               /*TPED* Issue TP_ENDED every time conversation deallocated   */
               /*************************************************************/
               Build_TP_ENDED();
            }
            else
            {
               Build_MC_RECEIVE_AND_WAIT();
            }
            break;

         case AP_TP_ENDED:
            /**************************************************************/
            /*TPED* If not completed all conversations,  issue RCV_ALLOC  */
            /**************************************************************/
            if ((NumConversations != 0) && (ConvCount < NumConversations))
            {
               Build_RECEIVE_ALLOCATE();
            }
            else
            {
               TPDead = TRUE;
            }
            break;
#endif

         default:
            /*****************************************************************/
            /* What is this verb then ??                                     */
            /*****************************************************************/
            TPDead = TRUE;
#ifdef WIN32
            DebugBreak();
#endif
            break;

      } /* Op-code switch */

   } /* TPDead after previous verb */

   /**************************************************************************/
   /* Now go ahead and issue the verb, if we're not dead.                    */
   /**************************************************************************/
   if (!TPDead)
   {
#ifdef SYNC
      APPC((long)(vcbptr));
#else
      async_corr=WinAsyncAPPC(hWndMain, (long)(char FAR *)(vcbptr));
#endif
   }
#ifndef SYNC
   else
   {
      PostMessage(hWndMain, WM_CLOSE, 0, 0);
   }
#endif
} /* Issue next verb */

#ifdef SENDTP
void Build_TP_STARTED()
{
   CLEARVCB

   vcb.tpstart.opcode = AP_TP_STARTED;
   memcpy(&(vcb.tpstart.lu_alias), LocalLUAlias, 8);
   memcpy(&(vcb.tpstart.tp_name), LocalTPName, 64);

}

void Build_MC_ALLOCATE()
{
   CLEARVCB

   vcb.allocate.opcode = AP_M_ALLOCATE;
   vcb.allocate.opext = AP_MAPPED_CONVERSATION;
   memcpy(&(vcb.allocate.tp_id),TPid, 8);
   vcb.allocate.sync_level = AP_CONFIRM_SYNC_LEVEL;
   vcb.allocate.rtn_ctl = AP_WHEN_SESSION_ALLOCATED;
   memcpy(&(vcb.allocate.plu_alias), RemoteLUAlias, 8);
   memcpy(&(vcb.allocate.mode_name), ModeName, 8);
   memcpy(&(vcb.allocate.tp_name), RemoteTPName, 64);
   vcb.allocate.security = AP_NONE;

}

void Build_MC_DEALLOCATE()
{
   CLEARVCB

   vcb.deallocate.opcode = AP_M_DEALLOCATE;
   vcb.deallocate.opext = AP_MAPPED_CONVERSATION;
   memcpy(&(vcb.deallocate.tp_id), TPid, 8);
   vcb.deallocate.conv_id = Convid;
   if (ConfirmEvery == 0)
   {
      vcb.deallocate.dealloc_type = AP_FLUSH;
   }
   else
   {
      vcb.deallocate.dealloc_type = AP_SYNC_LEVEL;
   }

}

void Build_MC_SEND_DATA()
{
   CLEARVCB

   //  PERF - GenerateData();

   vcb.snddata.opcode = AP_M_SEND_DATA;
   vcb.snddata.opext = AP_MAPPED_CONVERSATION;
   memcpy(&(vcb.snddata.tp_id), TPid, 8);
   vcb.snddata.conv_id = Convid;
   vcb.snddata.dlen = SendSize;
   vcb.snddata.dptr = DataPtr;
   vcb.snddata.type = AP_NONE;
}

void Build_MC_SEND_CONVERSATION()
{
   CLEARVCB

   // PERF - GenerateData();

   vcb.sndconv.opcode = AP_M_SEND_CONVERSATION;
   vcb.sndconv.opext = AP_MAPPED_CONVERSATION;
   memcpy(&(vcb.sndconv.tp_id), TPid, 8);
   vcb.sndconv.rtn_ctl = AP_WHEN_SESSION_ALLOCATED;
   memcpy(&(vcb.sndconv.plu_alias), RemoteLUAlias, 8);
   memcpy(&(vcb.sndconv.mode_name), ModeName, 8);
   memcpy(&(vcb.sndconv.tp_name), RemoteTPName, 64);
   vcb.sndconv.security = AP_NONE;
   vcb.sndconv.dlen = SendSize;
   vcb.sndconv.dptr = DataPtr;
}

void Build_MC_CONFIRM()
{
   CLEARVCB

   vcb.confirm.opcode = AP_M_CONFIRM;
   vcb.confirm.opext = AP_MAPPED_CONVERSATION;
   memcpy(&(vcb.confirm.tp_id), TPid, 8);
   vcb.confirm.conv_id = Convid;
}
#else

void Build_RECEIVE_ALLOCATE()
{
   CLEARVCB

   vcb.rcvalloc.opcode = AP_RECEIVE_ALLOCATE;
   memcpy(&(vcb.rcvalloc.tp_name), LocalTPName, 64);
}

void Build_MC_RECEIVE_AND_WAIT()
{
   CLEARVCB

   vcb.rcvwait.opcode = AP_M_RECEIVE_AND_WAIT;
   vcb.rcvwait.opext = AP_MAPPED_CONVERSATION;
   memcpy(&(vcb.rcvwait.tp_id),TPid,8);
   vcb.rcvwait.conv_id = Convid;
   vcb.rcvwait.rtn_status = AP_YES;
   vcb.rcvwait.max_len = 0xFFFF;
   vcb.rcvwait.dptr = DataPtr;
}

void Build_MC_CONFIRMED()
{
   CLEARVCB

   vcb.confirmed.opcode = AP_M_CONFIRMED;
   vcb.confirmed.opext = AP_MAPPED_CONVERSATION;
   memcpy(&(vcb.confirmed.tp_id),TPid,8);
   vcb.confirmed.conv_id = Convid;
}
#endif

void Build_TP_ENDED()
{
   CLEARVCB

   vcb.tpend.opcode = AP_TP_ENDED;
   memcpy(&(vcb.tpend.tp_id), TPid, 8);
   vcb.tpend.type = AP_SOFT;
}

#ifdef SENDTP
void Send_Run_Details()
{
   /**************************************************************************/
   /* Issues a Send_Conversation verb to send the number of conversations to */
   /* be done to the other side.                                             */
   /**************************************************************************/
   CLEARVCB

   vcb.sndconv.opcode = AP_M_SEND_CONVERSATION;
   vcb.sndconv.opext = AP_MAPPED_CONVERSATION;
   memcpy(&(vcb.sndconv.tp_id), TPid, 8);
   vcb.sndconv.rtn_ctl = AP_WHEN_SESSION_ALLOCATED;
   memcpy(&(vcb.sndconv.plu_alias), RemoteLUAlias, 8);
   memcpy(&(vcb.sndconv.mode_name), ModeName, 8);
   memcpy(&(vcb.sndconv.tp_name), RemoteTPName, 64);
   vcb.sndconv.security = AP_NONE;
   vcb.sndconv.dlen = sizeof(unsigned short);
   vcb.sndconv.dptr = DataPtr;
#ifdef WIN32
   *((unsigned short UNALIGNED *) DataPtr) = NumConversations;
#else
   *((unsigned short far *)DataPtr) = NumConversations;
#endif

   APPC((long)(vcbptr));
   if (vcb.sndconv.primary_rc != AP_OK)
   {
      TPDead = TRUE;
   }
}
#else
void Get_Run_Details()
{
   /**************************************************************************/
   /* Issues a Receive_Allocate and Receive_and_wait verb to get the number  */
   /* of conversations to be done.                                           */
   /* Returns true if this was successful, false otherwise.                  */
   /**************************************************************************/
   switch (GetStage)
   {
      case 0:

         CLEARVCB
         vcb.rcvalloc.opcode = AP_RECEIVE_ALLOCATE;
         memcpy(&(vcb.rcvalloc.tp_name), LocalTPName, 64);
         async_corr=WinAsyncAPPC(hWndMain, (long)(char FAR *)(vcbptr));
         GetStage = 1;
         break;

      case 1:

         if (vcb.rcvalloc.primary_rc != AP_OK)
         {
            TPDead = TRUE;
         }
         else
         {
            memcpy(TPid,&(vcb.rcvalloc.tp_id),8);
            Convid = vcb.rcvalloc.conv_id;
            CLEARVCB
            vcb.rcvwait.opcode = AP_M_RECEIVE_AND_WAIT;
            vcb.rcvwait.opext = AP_MAPPED_CONVERSATION;
            memcpy(&(vcb.rcvwait.tp_id),TPid,8);
            vcb.rcvwait.conv_id = Convid;
            vcb.rcvwait.rtn_status = AP_YES;
            vcb.rcvwait.max_len = sizeof(unsigned short);
            vcb.rcvwait.dptr = DataPtr;
            async_corr=WinAsyncAPPC(hWndMain, (long)(char FAR *)(vcbptr));
            GetStage = 2;
         }
         break;

      case 2:

         if (vcb.rcvwait.primary_rc != AP_DEALLOC_NORMAL)
         {
            TPDead = TRUE;
         }
         else
         {
#ifdef WIN32
            NumConversations = *((unsigned short UNALIGNED *)DataPtr);
#else
            NumConversations = *((unsigned short far *)DataPtr);
#endif
            CLEARVCB
            vcb.tpend.opcode = AP_TP_ENDED;
            memcpy(&(vcb.tpend.tp_id), TPid, 8);
            vcb.tpend.type = AP_SOFT;
            async_corr=WinAsyncAPPC(hWndMain, (long)(char FAR *)(vcbptr));
            GetStage = 3;
         }
         break;

      case 3:

         if (vcb.tpend.primary_rc != AP_OK)
         {
            TPDead = TRUE;
         }
         else
         {
            GotNumConv = TRUE;
            vcb.hdr.opcode = 0x0000;
            async_corr = 0;
            PostMessage(hWndMain, ASYNC_COMPLETE, (WPARAM)async_corr,
                                                 (LPARAM)(char FAR *)(vcbptr));
         }
         break;
   }
}
#endif


/*****************************************************************************/
/* ProcessReturns - Checks return codes from the last verb to complete and   */
/*                  saves off any useful information. If the return code is  */
/*                  bad then we just die.                                    */
/*****************************************************************************/
void ProcessReturns()
{
   if ( (  vcb.hdr.primary_rc != AP_OK) &&
       !( (vcb.hdr.opcode == AP_M_RECEIVE_AND_WAIT)&&
          (vcb.hdr.primary_rc == AP_DEALLOC_NORMAL)  )  )
   {
      TPDead = TRUE;
   }
   else
   {
      switch (vcb.hdr.opcode)
      {
         case AP_TP_ENDED:
            break;
#ifdef SENDTP
         case AP_TP_STARTED:
            memcpy(TPid,&(vcb.tpstart.tp_id),8);
            break;

         case AP_M_SEND_CONVERSATION:
            break;

         case AP_M_ALLOCATE:
            Convid = vcb.allocate.conv_id;
            break;

         case AP_M_SEND_DATA:
            break;

         case AP_M_DEALLOCATE:
            Convid = 0;
            break;

         case AP_M_CONFIRM:
            break;
#else
         case AP_RECEIVE_ALLOCATE:
            memcpy(TPid,&(vcb.rcvalloc.tp_id),8);
            Convid = vcb.rcvalloc.conv_id;
            break;

         case AP_M_RECEIVE_AND_WAIT:
            break;

         case AP_M_CONFIRMED:
            break;
#endif
         default:
            TPDead = TRUE;
#ifdef WIN32
            DebugBreak();
#endif
            break;
      }
   }
}

/*****************************************************************************/
/* ReadConfig - Reads config info from SENDTP.CFG also allocates buffer for  */
/*              sending                                                      */
/*****************************************************************************/
void ReadConfig()
{
#ifdef SENDTP
   char buffer[200];
#endif
#ifdef DOS5
   unsigned short selector;
#endif

   SendSize = 0xFFFF;

   if (!ReadString("LocalTPName",LocalTPName,64))
   {
#ifdef SENDTP
      strncpy(LocalTPName,"SENDTP",6);
#else
      strncpy(LocalTPName,"RECVTP",6);
#endif
   }
   PadString(LocalTPName,64);
   CONV_A_TO_E(LocalTPName,64);

#ifdef SENDTP
   if (!ReadString("ResultFile",FileName,60))
   {
      strcpy(FileName,"C:\\SENDTP.OUT");
   }
   NumConversations=1;
   if (ReadString("NumConversations",buffer,200))
   {
      NumConversations=atoi(buffer);
   }
   if (!ReadString("LocalLUAlias",LocalLUAlias,8))
   {
      strncpy(LocalLUAlias,"SENDLU",8);
   }
   PadString(LocalLUAlias,8);
   if (!ReadString("RemoteLUAlias",RemoteLUAlias,8))
   {
      strncpy(RemoteLUAlias,"RECVLU",8);
   }
   PadString(RemoteLUAlias,8);
   if (!ReadString("ModeName",ModeName,8))
   {
      strncpy(ModeName,"#INTER",8);
   }
   PadString(ModeName,8);
   CONV_A_TO_E(ModeName,8);
   if (!ReadString("RemoteTPName",RemoteTPName,64))
   {
      strncpy(RemoteTPName,"RECVTP",6);
   }
   PadString(RemoteTPName,64);
   CONV_A_TO_E(RemoteTPName,64);
   NumSends=2;
   if (ReadString("NumSends",buffer,200))
   {
      NumSends=atoi(buffer);
   }
   ConfirmEvery=1;
   if (ReadString("ConfirmEvery",buffer,200))
   {
      ConfirmEvery=atoi(buffer);
   }
   SendSize=1024;
   if (ReadString("SendSize",buffer,200))
   {
      SendSize=atoi(buffer);
   }
   SendConversation=FALSE;
   if (ReadString("SendConversation",buffer,200))
   {
      SendConversation = (*(strupr(buffer)) == 'Y');
   }
#endif
#ifdef DOS5
   DosAllocSeg(SendSize,&selector,1);
   DataPtr = MAKEP(selector,0);
#else
 #ifdef WIN32
   DataPtr = malloc(SendSize);
 #else
   DataPtr = (char far *)GlobalLock(GlobalAlloc(GPTR,SendSize));
 #endif
#endif
   ResultBuf = (NumConversations == 0) ?
               NULL : malloc(NumConversations * sizeof(RESULT));
   ResultPtr = ResultBuf;
}

/*****************************************************************************/
/* CONV_A_TO_E - ASCII to EBCDIC conversion routine.                         */
/*****************************************************************************/
void CONV_A_TO_E(char FAR * string,int length)
{
   memset(cnvtptr,0,sizeof(cnvt));

   cnvt.opcode       = SV_CONVERT;
   cnvt.direction    = SV_ASCII_TO_EBCDIC;
   cnvt.char_set     = SV_AE;

   cnvt.len          = length;
   cnvt.source       = string;
   cnvt.target       = string;

   ACSSVC_C((long)(char far *) (cnvtptr));      /* Call ACSSVC - go convert! */
}

/*****************************************************************************/
/* CONV_E_TO_A - EBCDIC to ASCII conversion routine.                         */
/*****************************************************************************/
void CONV_E_TO_A(char FAR * string,int length)
{
   memset(cnvtptr,0,sizeof(cnvt));

   cnvt.opcode       = SV_CONVERT;
   cnvt.direction    = SV_EBCDIC_TO_ASCII;
   cnvt.char_set     = SV_AE;
   cnvt.len          = length;
   cnvt.source       = string;
   cnvt.target       = string;

   ACSSVC_C((long)(char FAR *) (cnvtptr));      /* Call ACSSVC - go convert! */
}



/*****************************************************************************/
/* NewConversation - Reset and record timers for this conversation.          */
/*****************************************************************************/
void NewConversation()
{
   RESULT NewTime;

#ifdef SENDTP
   SendCount = 0;
   ConfirmCount =0;
#endif

   if (FirstConv)
   {
      FirstConv = FALSE;
      ConvStarted = GetTickCount();
   }
   else if (ResultPtr != NULL)
   {
      *ResultPtr++ = ((NewTime = GetTickCount()) - ConvStarted);
      ConvStarted = NewTime;
   }
   ConvCount++;
   OUTPUTNUMBER
}

#ifdef SENDTP
/*****************************************************************************/
/* GenerateData    - Fill in data buffer                                     */
/*****************************************************************************/
void GenerateData()
{
   int i;
   int div;
   int rem;
   char FAR * dptr;

   dptr = DataPtr;
   div = SendSize / 5;
   rem = SendSize % 5;

   for (; div--;)
   {
      for (i=4; i--; *dptr++ = datach);
      *dptr++ = '.';
   }
   for (; rem--; *dptr++ = datach);

   datach = (datach=='Z' ? 'A' : datach + 1);
}

/*****************************************************************************/
/* OutputResults - dump the times of conversations to file                   */
/*****************************************************************************/
void OutputResults()
{
  FILE *h = NULL;
  RESULT FAR * ptr = NULL;
  unsigned short i = 0;
  RESULT TotalTime=0;

  h = fopen(FileName,"w");
  if (h != NULL)
  {
    fprintf(h,"SENDTP Results\n--------------\n\n");
    CONV_E_TO_A(LocalTPName,64);
    fprintf(h,"Local TP Name           = %.64s\n",LocalTPName);
    CONV_E_TO_A(RemoteTPName,64);
    fprintf(h,"Remote TP Name          = %.64s\n",RemoteTPName);
    fprintf(h,"Local LU Alias          = %.8s\n",LocalLUAlias);
    fprintf(h,"Remote LU Alias         = %.8s\n",RemoteLUAlias);
    CONV_E_TO_A(ModeName,8);
    fprintf(h,"ModeName                = %.8s\n",ModeName);
    fprintf(h,"Number of conversations = %d\n",NumConversations);
    if (!SendConversation)
    {
       fprintf(h,"Sends per conversation  = %d\n",NumSends);
       fprintf(h,"Sends between confirms  = %d\n",ConfirmEvery);
    }
    fprintf(h,"Bytes per send          = %d\n",SendSize);
    fprintf(h,"Use SEND_CONVERSATION   = %s\n",(SendConversation ? "Yes":"No"));
    fprintf(h,"\n");

    ptr = ResultBuf;
    while (ptr < ResultPtr)
    {
		TotalTime += *ptr;
      fprintf(h,"Conversation number %d, time = %.3f seconds\n",i++,
                                                (((float) *ptr++) / 1000.0 ));
	  
    }
	fprintf( h,"Total Time in Conversation = %.3f seconds\n",(((float)TotalTime)/1000.0) );
    fclose(h);                                                        /*FILE*/
  }
}

#endif

/*****************************************************************************/
/* ReadString - Get a line of text from the config file.                     */
/*****************************************************************************/
int ReadString(char FAR * lpValueName,char FAR * lpData, int maxlen)
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

#if (defined(WINDOWS)||defined(WIN32))                                 /*PATH*/
                                                                       /*PATH*/
	GetModuleFileName( hInst, buffer, sizeof(buffer) );                /*PATH*/
	lstrcpy( buffer+lstrlen(buffer) - 4, ".CFG" );                     /*PATH*/
	h = fopen( buffer, "r" );                                          /*PATH*/
	buffer[0] = '\0';                                                  /*PATH*/
                                                                       /*PATH*/
#else                                                                  /*PATH*/
#ifdef SENDTP
   h = fopen("C:\\sendtp.cfg", "r");
#else
   h = fopen("C:\\recvtp.cfg", "r");
#endif
#endif                                                                 /*PATH*/

   lpValueName=strupr(lpValueName);

   if (h != NULL)
   {
      while ((!match) && (!eof))
      {
         /********************************************************************/
         /* Use fgetc to read a line of text from the file.                  */
         /********************************************************************/
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
            /*****************************************************************/
            /* Compare the 1st token in the line read with the requested     */
            /* param.                                                        */
            /*****************************************************************/
            if (!strcmpi(strupr(strtok(buffer, separators)), lpValueName))
            {
               match = TRUE;
               /**************************************************************/
               /* Get a pointer to the 2nd token (the value we want)         */
               /**************************************************************/
               p = strtok(NULL, separators);

               /**************************************************************/
               /* Copy the data IF there is some.                            */
               /**************************************************************/
               if (p != NULL)
               {
                  /***********************************************************/
                  /* Force a NULL after the 2nn token                        */
                  /***********************************************************/
                  strtok(NULL, separators);

                  /***********************************************************/
                  /* Copy the data                                           */
                  /***********************************************************/
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
void PadString(char FAR * string,int length)
{
   char FAR * p;
   if ((p=memchr(string,'\0',length)) != NULL)
   {
      while (p < string+length)
      {
         *p++=' ';
      }
   }
}


