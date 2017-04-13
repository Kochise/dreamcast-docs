/* mrcv.h */
/* (C) COPYRIGHT DATA CONNECTION LIMITED 1994 */

/*****************************************************************************/
/* Change History                                                            */
/*                                                                           */
/*       11/01/94 DK  Created                                                */
/*       14/04/94 DK  Name table added for tracing                           */
/*****************************************************************************/

/*****************************************************************************/
/* static configuration constants                                            */
/* Note that MAX_RCV_PER_SERVICE cannot exceed 63, because we cannot wait    */
/*      on more than 64 events (and one extra event is needed for receive)   */
/*****************************************************************************/
#define MAX_RCV_PER_THREAD  63
#define MAX_RECEIVE_THREADS 64

/*****************************************************************************/
/* global critical section                                                   */
/*****************************************************************************/
CRITICAL_SECTION runsem;

/*****************************************************************************/
/* APPC verb control block and macros for manipulation of vcb                */
/*****************************************************************************/
#define CLEARVCB memset(vcbptr,0,sizeof(VCB));
#define P_TPE(X)    ((struct tp_ended *)X)
#define P_RAL(X)    ((struct receive_allocate *)X)

#define P_M_CFD(X)  ((struct mc_confirmed *)X)
#define P_M_DAL(X)  ((struct mc_deallocate *)X)
#define P_M_RAW(X)  ((struct mc_receive_and_wait *)X)

typedef struct vcb
{
  union
  {
    struct appc_hdr             hdr;
    struct receive_allocate     rcvalloc;
    struct tp_ended             tpend;
    struct mc_confirmed         confirmed;
    struct mc_deallocate        deallocate;
    struct mc_receive_and_wait  rcvwait;
  } U_VCB;
} VCB;

/*****************************************************************************/
/* structures for convert verb                                               */
/*****************************************************************************/
struct convert cnvt;
char * cnvtptr;

/*****************************************************************************/
/* for outputting results                                                    */
/*****************************************************************************/
typedef unsigned long RESULT;
RESULT * ResultPtr;
RESULT * ResultBuf;
short    NumResults;

/*****************************************************************************/
/* conversation control block - one per conversation                         */
/*****************************************************************************/
typedef struct convcb
{
  char           TPid[8];
  char           type[8];
  unsigned long  Convid;
  HANDLE         async_corr;
  char *         DataPtr;
  unsigned short thread;
  unsigned short conv;
  unsigned short RcvCount;
  BOOL           TPEnded;
  BOOL           Deallocated;
  RESULT         ConvStarted;
  HANDLE         hEvent;
  VCB            vcb;
} CONVCB;

/*****************************************************************************/
/* structures for receive threads                                            */
/*****************************************************************************/
typedef struct rcv_thread
{
  HANDLE event1;
  HANDLE event2;
  CONVCB * convptr;
} RCV_THREAD;

RCV_THREAD RcvThreadArray [MAX_RECEIVE_THREADS];

/*****************************************************************************/
/* File Names and handle for trace file                                      */
/*****************************************************************************/
char FileName [60];
char TraceFile[60];
FILE *t = NULL;

/*****************************************************************************/
/* APPC Names from configuration file                                        */
/*****************************************************************************/
char TPName[64];
char LocalTPName[64];
char LocalLUAlias[8];
char RemoteLUAlias[8];
char ModeName[8];
char RemoteTPName[64];

/*****************************************************************************/
/* Global Variables from configuration file                                  */
/*****************************************************************************/
unsigned short NumRcvThreads;
unsigned short NumRcvConvs;
unsigned short RcvSize;

/*****************************************************************************/
/* Global Variables                                                          */
/*****************************************************************************/
unsigned short NumRalcs;                /* number of receive_allocs issued   */
unsigned short RcvConvs;                /* number of conversations completed */
unsigned short ThreadCount;             /* total thread count                */
unsigned short RcvThreads;              /* count of receive threads          */
unsigned short SimRcvConvs;             /* number of simultaneous rcv convs  */

/*****************************************************************************/
/* Names of verbs for tracing                                                */
/*****************************************************************************/
char *VerbName[] =
{
  "UNKNOWN_VERB",                       /* 0x0000                            */
  "MC_ALLOCATE",                        /* 0x0001                            */
  "UNKNOWN_VERB",                       /* 0x0002                            */
  "MC_CONFIRM",                         /* 0x0003                            */
  "MC_CONFIRMED",                       /* 0x0004                            */
  "MC_DEALLOCATE",                      /* 0x0005                            */
  "MC_FLUSH",                           /* 0x0006                            */
  "MC_GET_ATTRIBUTES",                  /* 0x0007                            */
  "UNKNOWN_VERB",                       /* 0x0008                            */
  "UNKNOWN_VERB",                       /* 0x0009                            */
  "MC_PREPARE_TO_RECEIVE",              /* 0x000a                            */
  "MC_RECEIVE_AND_WAIT",                /* 0x000b                            */
  "MC_RECEIVE_IMMEDIATE",               /* 0x000c                            */
  "MC_RECEIVE_AND_POST",                /* 0x000d                            */
  "MC_REQUEST_TO_SEND",                 /* 0x000e                            */
  "MC_SEND_DATA",                       /* 0x000f                            */
  "MC_SEND_ERROR",                      /* 0x0010                            */
  "UNKNOWN_VERB",                       /* 0x0011                            */
  "MC_TEST_RTS",                        /* 0x0012                            */
  "TP_ENDED",                           /* 0x0013                            */
  "TP_STARTED",                         /* 0x0014                            */
  "UNKNOWN_VERB",                       /* 0x0015                            */
  "RECEIVE_ALLOCATE",                   /* 0x0016                            */
  "UNKNOWN_VERB",                       /* 0x0017                            */
  "MC_SEND_CONVERSATION"                /* 0x0018                            */
};

/*****************************************************************************/
/* Windows stuff                                                             */
/*****************************************************************************/
HWND hWndMain;
char title[30]={'\0'};
#define OUTPUTNUMBER sprintf(title,"thrd simR done  %d  %d  %d", \
                     ThreadCount,SimRcvConvs,RcvConvs);  \
                     SetWindowText(hWndMain,title);

/*****************************************************************************/
/* Function Prototypes                                                       */
/*****************************************************************************/
int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow);
BOOL InitializeWinMain(HINSTANCE hInstance);
LONG PASCAL TPWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void InitializeMain(void);
BOOL IssueRcvVerb(CONVCB * convptr);
BOOL ProcessReturns(CONVCB * convptr);
void ReadConfig(void);
void CONV_A_TO_E(char * string,int length);
void CONV_E_TO_A(char * string,int length);
void StartConversation(CONVCB * convptr);
void EndConversation(CONVCB * convptr);
int  ReadString(char * lpValueName, char FAR * lpData, int maxlen);
void PadString(char * string, int length);
void OutputResults(void);
void Build_RECEIVE_ALLOCATE(CONVCB * convptr);
void Build_TP_ENDED(CONVCB * convptr);
void Build_MC_CONFIRMED(CONVCB * convptr);
void Build_MC_DEALLOCATE(CONVCB * convptr);
void Build_MC_RECEIVE_AND_WAIT(CONVCB * convptr);
DWORD WINAPI RcvAllocThread();
DWORD WINAPI ReceiveThread(DWORD k);

