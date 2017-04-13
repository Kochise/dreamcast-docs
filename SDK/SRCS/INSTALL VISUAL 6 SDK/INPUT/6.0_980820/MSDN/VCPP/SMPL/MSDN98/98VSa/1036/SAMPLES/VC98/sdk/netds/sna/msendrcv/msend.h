/* msend.h */
/* (C) COPYRIGHT DATA CONNECTION LIMITED 1994 */

/*****************************************************************************/
/* Change History                                                            */
/*                                                                           */
/*       11/01/94 DK  Created                                                */
/*       14/04/94 DK  Name table added for tracing                           */
/*****************************************************************************/

/*****************************************************************************/
/* static configuration constants                                            */
/*****************************************************************************/
#define MAX_SEND_PER_THREAD 64

/*****************************************************************************/
/* global critical section                                                   */
/*****************************************************************************/
CRITICAL_SECTION runsem;

/*****************************************************************************/
/* APPC verb control block and macros for manipulation of vcb                */
/*****************************************************************************/
#define CLEARVCB memset(vcbptr,0,sizeof(VCB));
#define P_TPS(X)    ((struct tp_started *)X)
#define P_TPE(X)    ((struct tp_ended *)X)

#define P_M_ALC(X)  ((struct mc_allocate *)X)
#define P_M_CNF(X)  ((struct mc_confirm *)X)
#define P_M_DAL(X)  ((struct mc_deallocate *)X)
#define P_M_SDD(X)  ((struct mc_send_data *)X)

typedef struct vcb
{
  union
  {
    struct appc_hdr             hdr;
    struct tp_started           tpstart;
    struct tp_ended             tpend;
    struct mc_allocate          allocate;
    struct mc_confirm           confirm;
    struct mc_deallocate        deallocate;
    struct mc_send_data         snddata;
  } U_VCB;
} VCB;

/*****************************************************************************/
/* structures for convert verb                                               */
/*****************************************************************************/
struct convert cnvt;
char * cnvtptr;

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
  unsigned short SendSize;
  unsigned short SendCount;
  unsigned short ConfirmCount;
  BOOL           TPEnded;
  BOOL           Deallocated;
  BOOL           Counted;
  HANDLE         hEvent;
  VCB            vcb;
} CONVCB;

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
unsigned short NumSends;
unsigned short SendSize;
unsigned short NumSendConvs;
unsigned short ConfirmEvery;

/*****************************************************************************/
/* Global Variables                                                          */
/*****************************************************************************/
unsigned short NumRalcs;                /* number of receive_allocs issued   */
unsigned short ThreadCount;             /* total thread count                */
unsigned short SendThreads;             /* count of send threads             */
unsigned short SimSendConvs;            /* number of simultaneous send convs */
unsigned short SendConvs;               /* number of send convs completed    */

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
/* Character for filling buffer                                              */
/*****************************************************************************/
char datach;

/*****************************************************************************/
/* Windows stuff                                                             */
/*****************************************************************************/
HWND hWndMain;
char title[40]={'\0'};
#define OUTPUTNUMBER sprintf(title,"thrd simS done  %d  %d  %d", \
                     ThreadCount,SimSendConvs,SendConvs);  \
                     SetWindowText(hWndMain,title);

/*****************************************************************************/
/* Function Prototypes                                                       */
/*****************************************************************************/
int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow);
BOOL InitializeWinMain(HINSTANCE hInstance);
LONG PASCAL TPWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void InitializeMain(void);
BOOL IssueSendVerb(CONVCB * convptr);
BOOL ProcessReturns(CONVCB * convptr);
void ReadConfig(void);
void CONV_A_TO_E(char * string,int length);
void CONV_E_TO_A(char * string,int length);
int  ReadString(char * lpValueName, char FAR * lpData, int maxlen);
void PadString(char * string, int length);
void Build_TP_STARTED(CONVCB * convptr);
void Build_TP_ENDED(CONVCB * convptr);
void Build_MC_ALLOCATE(CONVCB * convptr);
void Build_MC_CONFIRM(CONVCB * convptr);
void Build_MC_DEALLOCATE(CONVCB * convptr);
void Build_MC_SEND_DATA(CONVCB * convptr);
void GenerateData(CONVCB * convptr);
DWORD WINAPI SendThread(DWORD k);

