/* CPICSR.C */
/* (C) COPYRIGHT DATA CONNECTION LIMITED 1993 */

/*****************************************************************************/
/* Change History                                                            */
/*                                                                           */
/*       30/06/93 NGR Created.                                               */
/*****************************************************************************/

/*****************************************************************************/
/*                                                                           */
/* ROUTINE : CPICSR                                                          */
/*                                                                           */
/* FUNCTION: This file contains the main routines for CPI-C versions of the  */
/*           send and receive TPs.                                           */
/*           sending and receiving TPs SENDTP and RECVTP                     */
/*                                                                           */
/* INPUTS  : C:\CPICSEND.CFG (file) (documented below)                       */
/*           C:\CPICRECV.CFG (file) (documented below)                       */
/*           Note files are in executable's directory in WIN32               */
/*                                                                           */
/* OUTPUTS : CPICSEND.OUT                                                    */
/*           CPICRECV.OUT                                                    */
/*                                                                           */
/*****************************************************************************/

/*****************************************************************************/
/* Configuration files:                                                      */
/*                                                                           */
/* Configuration file is C:\CPICSEND.CFG or CPICRECV.CFG which contains      */
/* the following, one per line in any order. If not present then the given   */
/* default is assumed.                                                       */
/*                                                                           */
/* ResultFile = <Name of file for results, default C:\CPIC(SEND/RECV).OUT>   */
/* NumConversations = <Number of conversations to be done, default = 1>      */
/* LocalTPName = <Name to be used for TP started, default SENDTP/RECVTP>     */
/* WaitMode = Yes/No/Block (default = No)                                    */
/*            Yes      - Verbs are non-blocking but completed via CMWAIT     */
/*            No       - Verbs are completed via posted Windows messages     */
/*            Block    - All verbs are blocking                              */
/*                                                                           */
/* The following only apply to CPICSEND:                                     */
/* SymDestName = <symbolic destination name, default = CPICRECV>             */
/* NumSends = <number of CMSEND verbs per conversation, default = 2>         */
/* ConfirmEvery = <number of CMSEND verbs between CMCFMs, default = 1>       */
/* SendSize = <number of bytes per CMSEND, default = 1024>                   */
/*                                                                           */
/* The following only applies to CPICRECV:                                   */
/* LocalTPName = <Name to be used for CMSLTP verb, default CPICRECV          */
/*                                                                           */
/* If NumConversations is zero, then the TPs will do an infinite number of   */
/* conversations.                                                            */
/* If NumSends is zero, then CPICSEND will never CMDEAL the first            */
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
#include <wincpic.h>
#include "cpicsr.h"


/*****************************************************************************/
/* WinMain - reads initialisation info and controls message loop             */
/*           NT and Win16 version                                            */
/*****************************************************************************/
int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow)
{

  MSG msg;

  hInst = hInstance;

  ReadConfig();

  if (!InitialiseWinMain(hInstance))
  {
     return (FALSE);
  }

  InitialiseMain();

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
   WCPICDATA CPICData;
   WNDCLASS class;
   #define WinCPICVERSION  0x0001

   /**************************************************************************/
   /* Startup WinAPPC                                                        */
   /**************************************************************************/
   if (WinCPICStartup(WinCPICVERSION,&CPICData))
   {
      return (FALSE);
   }

   if ( (ASYNC_COMPLETE =
         RegisterWindowMessage(WIN_CPIC_ASYNC_COMPLETE_MESSAGE)) == 0 )
   {
      return (0);
   }

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
   class.lpszClassName = (LPSTR) "CPICSR\0";

   if (!RegisterClass(&class))
   {
     return (FALSE);
   }

   /**************************************************************************/
   /* Create the window                                                      */
   /**************************************************************************/
#ifdef CPICSEND
   sprintf(title,"CPI-C Send TP\0");
#else
   sprintf(title,"CPI-C Receive TP\0");
#endif

   if ((hWndMain = CreateWindow("CPICSR\0",        /* window class           */
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

   /**************************************************************************/
   /* Specify the window handle to be used, if this is NULL then we must use */
   /* Wait_For_Conversation to wait for the verb to complete.                */
   /**************************************************************************/
   xchwnd((wait_mode || blocking) ? NULL : hWndMain, &return_code);
#ifndef CPICSEND
   /**************************************************************************/
   /* Specify our local TP name. Note that because we have done this, the    */
   /* cmaccp will return asynchronously using the current notification type  */
   /**************************************************************************/
   {
      CM_INT32 temp_length;
      CM_INT32 temp_return_code;
      temp_length = strlen(LocalTPName);
      cmsltp(LocalTPName,&temp_length,&temp_return_code);
   }
#endif

   return(TRUE);

}

/*****************************************************************************/
/* Window proc for the iconised window                                       */
/*****************************************************************************/
LONG FAR PASCAL TPWndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
   if (message == ASYNC_COMPLETE)
   {
      return_code = (CM_RETURN_CODE) wParam;
      IssueNextVerb();
   }
   else
   {
      switch (message)
      {
         case WM_CREATE:
            /*****************************************************************/
            /* Post a message to ourselves to kick off the first verb        */
            /*****************************************************************/
            PostMessage(hWnd, ASYNC_COMPLETE, 0, 0);
            break;

         case WM_QUERYOPEN:
            /*****************************************************************/
            /* Prevent the window being opened                               */
            /*****************************************************************/
            break;

         case WM_CLOSE:
            TPDead = TRUE;
            WinCPICCleanup();
            OutputResults();
            return DefWindowProc(hWnd, message, wParam, lParam);
            break;

         case WM_DESTROY:
            PostQuitMessage(0);
            break;

         default:
            return DefWindowProc(hWnd, message, wParam, lParam);
            break;
      }
   }
   return 0l;
}

/*****************************************************************************/
/* InitialiseMain - blanks out variables and allocates buffers.              */
/*****************************************************************************/
void InitialiseMain()
{
   TPDead = FALSE;
   FirstConv = TRUE;
   last_verb = 0;
   ConvCount = 0;

   DataPtr = malloc((size_t) SendSize);
#ifdef CPICSEND
   GenerateData();
   SendCount = 0;
   ConfirmCount = 0;
#else
   Deallocated = FALSE;
#endif

   ResultBuf = (NumConversations == 0) ?
               NULL : malloc(NumConversations * sizeof(RESULT));
   ResultPtr = ResultBuf;

}

/*****************************************************************************/
/* IssueNextVerb - looks at the verb which has just completed and does the   */
/*                 next one                                                  */
/*****************************************************************************/
void IssueNextVerb()
{
   unsigned char wait_conv_ID[8];
   CM_INT32 wait_return_code;
   /**************************************************************************/
   /* last_verb = 0 is special case, before any verb has been issued.        */
   /**************************************************************************/
   if (last_verb != 0)
   {
      ProcessReturns();
   }
   if (!TPDead)
   {
      switch (last_verb)
      {
         case 0x0000:
#ifdef CPICSEND
            NewConversation();
            Do_cminit();
#else
            Do_cmaccp();
#endif
            break;

#ifdef CPICSEND
         case C_INIT:
            /*****************************************************************/
            /* Set the processing mode for this conversation to non-blocking */
            /* we have already used xchwnd to set the window handle (or to   */
            /* NULL it for WAIT mode)                                        */
            /*****************************************************************/
            {
               CM_INT32 receive_type = (blocking) ? CM_BLOCKING :
                                                    CM_NON_BLOCKING ;
               CM_INT32 temp_return_code;
               cmspm(conversation_ID, &receive_type, &temp_return_code);
            }
            /*****************************************************************/
            /* Set the sync level for this conversation                      */
            /*****************************************************************/
            {
               CM_INT32 sync_level;
               CM_INT32 temp_return_code;
               sync_level = (ConfirmEvery == 0) ? CM_NONE : CM_CONFIRM;
               cmssl(conversation_ID, &sync_level, &temp_return_code);
            }
            Do_cmallc();
            break;

         case C_ALLC:
            Do_cmsend();
            break;

         case C_SEND:
            SendCount++;
            ConfirmCount++;
            if ((NumSends != 0) && (SendCount == NumSends))
            {
               Do_cmdeal();
            }
            else if ((ConfirmEvery != 0) && (ConfirmCount == ConfirmEvery))
            {
               Do_cmcfm();
            }
            else
            {
               Do_cmsend();
            }
            break;

         case C_CFM:
            ConfirmCount=0;
            Do_cmsend();
            break;

         case C_DEAL:
            if ((NumConversations !=0) && (ConvCount == NumConversations))
            {
               NewConversation();
               TPDead = TRUE;
            }
            else
            {
#if 0
            /*****************************************************************/
            /* Enable this to check Startup/Cleanup in loop                  */
            /*****************************************************************/
  			   WCPICDATA CPICData;
  				WinCPICCleanup();
  				WinCPICStartup(WinCPICVERSION,&CPICData);
#endif
               NewConversation();
               Do_cminit();
            }
            break;

#else
         case C_ACCP:
            NewConversation();
            Do_cmrcv();
            break;

         case C_RCV:
            if (return_code == CM_DEALLOCATED_NORMAL)
            {
               if ((NumConversations != 0) && (ConvCount < NumConversations))
               {
                  Do_cmaccp();
               }
               else
               {
                  NewConversation();
                  TPDead = TRUE;
               }
            }
            else if (status_received == CM_CONFIRM_RECEIVED)
            {
               Do_cmcfmd();
               Deallocated = FALSE;
            }
            else if (status_received == CM_CONFIRM_DEALLOC_RECEIVED)
            {
               Do_cmcfmd();
               Deallocated = TRUE;
            }
            else
            {
               Do_cmrcv();
            }
            break;

         case C_CFMD:
            if (Deallocated)
            {
               if ((NumConversations != 0) && (ConvCount < NumConversations))
               {
                  Do_cmaccp();
               }
               else
               {
                  NewConversation();
                  TPDead = TRUE;
               }
            }
            else
            {
               Do_cmrcv();
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

      } /* last_verb switch */

   } /* TPDead after previous verb */
   if (!TPDead)
   {
      /***********************************************************************/
      /* If the verb just issued has already completed, then post ourselves  */
      /* a message to kick off the next verb.                                */
      /* Otherwise, if the async mode being used is WAIT, then issue a       */
      /* Wait_For_Conversation verb and then post ourselves a message        */
      /* If the async mode is POST then WinCPIC will post a message for us   */
      /***********************************************************************/
      if (return_code != CM_OPERATION_INCOMPLETE)
      {
         PostMessage(hWndMain, ASYNC_COMPLETE, (WPARAM)return_code,
                                      (LPARAM)((void FAR *)&conversation_ID));
      }
      else if (wait_mode)
      {
         cmwait(wait_conv_ID, &return_code, &wait_return_code);
         /********************************************************************/
         /* We don't bother checking the wait_conv_ID since we only have one */
         /* conversation in progress.                                        */
         /********************************************************************/
         PostMessage(hWndMain, ASYNC_COMPLETE, (WPARAM)return_code,
                                      (LPARAM)((void FAR *)&conversation_ID));
      }
   }
   else
   {
      /***********************************************************************/
      /* If we have finished then post ourselves a close message. Note that  */
      /* WinCPICCleanup will be done in the WM_CLOSE processing, so that the */
      /* case where the user closes the application prematurely is caught    */
      /***********************************************************************/
      PostMessage(hWndMain, WM_CLOSE, 0, 0);
   }
} /* Issue next verb */

#ifdef CPICSEND
void Do_cminit()
{
   cminit(conversation_ID,SymDestName,&return_code);
   last_verb = C_INIT;
}

void Do_cmallc()
{
   cmallc(conversation_ID,&return_code);
   last_verb = C_ALLC;
}

void Do_cmdeal()
{
   cmdeal(conversation_ID,&return_code);
   last_verb = C_DEAL;
}

void Do_cmsend()
{
   cmsend(conversation_ID,DataPtr,&SendSize,&request_to_send_received,
                                                                 &return_code);
   last_verb = C_SEND;
}

void Do_cmcfm()
{
   cmcfm(conversation_ID,&request_to_send_received,&return_code);
   last_verb = C_CFM;
}

#else

void Do_cmaccp()
{
   cmaccp(conversation_ID,&return_code);
   last_verb = C_ACCP;
}

void Do_cmrcv()
{
   cmrcv(conversation_ID,DataPtr,&SendSize,&data_received,&received_length,
                      &status_received,&request_to_send_received,&return_code);
   last_verb = C_RCV;
}

void Do_cmcfmd()
{
   cmcfmd(conversation_ID,&return_code);
   last_verb = C_CFMD;
}
#endif

/*****************************************************************************/
/* ProcessReturns - Checks return codes from the last verb to complete and   */
/*                  saves off any useful information. If the return code is  */
/*                  bad then we just die.                                    */
/*****************************************************************************/
void ProcessReturns()
{
   if ( (return_code != CM_OK) &&
       !( (last_verb == C_RCV) &&
          (return_code == CM_DEALLOCATED_NORMAL) ) )
   {
      TPDead = TRUE;
   }
}

/*****************************************************************************/
/* ReadConfig - Reads config info from SENDTP.CFG also allocates buffer for  */
/*              sending                                                      */
/*****************************************************************************/
void ReadConfig()
{
   char buffer[200];

#ifdef CPICSEND

   if (!ReadString("ResultFile",FileName,20))
   {
      strcpy(FileName,"C:\\CPICSEND.OUT");
   }
   if (!ReadString("SymDestName",SymDestName,8))
   {
      strcpy(SymDestName,"CPICRECV");
   }
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

#else

   SendSize = 0x7FFF;
   if (!ReadString("ResultFile",FileName,20))
   {
      strcpy(FileName,"C:\\CPICRECV.OUT");
   }
   if (!ReadString("LocalTPName",LocalTPName,64))
   {
      strcpy(LocalTPName,"CPICRECV");
   }

#endif

   wait_mode = FALSE;                                                  /*BLOK*/
   blocking  = FALSE;                                                  /*BLOK*/
   if (ReadString("WaitMode",buffer,200))                              /*BLOK*/
   {                                                                   /*BLOK*/
      wait_mode = (*(strupr(buffer)) != 'N');  /* Yes or Blocking */   /*BLOK*/
#ifdef CPICSEND                                                        /*BLOK*/
      blocking  = (*(strupr(buffer)) == 'B');  /* Blocking  */         /*BLOK*/
#endif                                                                 /*BLOK*/
   }                                                                   /*BLOK*/

   NumConversations=1;
   if (ReadString("NumConversations",buffer,200))
   {
      NumConversations=atoi(buffer);
   }

}

/*****************************************************************************/
/* NewConversation - Reset and record timers for this conversation.          */
/*****************************************************************************/
void NewConversation()
{
   RESULT NewTime;

#ifdef CPICSEND
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

#ifdef CPICSEND
/*****************************************************************************/
/* GenerateData    - Fill in data buffer                                     */
/*****************************************************************************/
void GenerateData()
{
   int i;
   int div;
   int rem;
   char * dptr;

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
#endif

/*****************************************************************************/
/* ReadString - Get a line of text from the config file.                     */
/*****************************************************************************/
int ReadString(char * lpValueName,char * lpData, int maxlen)
{
   char       buffer[200];
   char       value[200];
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
#ifdef CPICSEND
   h = fopen("C:\\cpicsend.cfg", "r");
#else
   h = fopen("C:\\cpicrecv.cfg", "r");
#endif
#endif                                                                 /*PATH*/

   strupr(strcpy(value,lpValueName));

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
#ifdef CPICSEND
     fprintf(h,"CPICSEND Results\n----------------\n\n");
     fprintf(h,"Symbolic destination name = %s\n",SymDestName);
     fprintf(h,"Number of conversations = %d\n",NumConversations);
     fprintf(h,"Sends per conversation  = %d\n",NumSends);
     fprintf(h,"Sends between confirms  = %d\n",ConfirmEvery);
     fprintf(h,"Bytes per send          = %d\n",SendSize);
     fprintf(h,"Wait mode               = %s\n",(wait_mode ? "Yes" : "No"));
     fprintf(h,"Blocking                = %s\n",(blocking  ? "Yes" : "No"));
     fprintf(h,"\n");
#else
     fprintf(h,"CPICRECV Results\n----------------\n\n");
     fprintf(h,"Local TP Name           = %s\n",LocalTPName);
     fprintf(h,"Number of conversations = %d\n",NumConversations);
     fprintf(h,"Wait mode               = %s\n",(wait_mode ? "Yes" : "No"));
     fprintf(h,"\n");
#endif

     ptr = ResultBuf;
     while (ptr < ResultPtr)
     {
       fprintf(h,"Conversation number %d, time = %.3f seconds\n",i++,
                                              (((float) *ptr++) / 1000.0 ));
     }
     fclose(h);
   }
}

