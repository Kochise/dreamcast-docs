/* sendrecv.h */
/* (C) COPYRIGHT DATA CONNECTION LIMITED 1993 */

/*****************************************************************************/
/* Change History                                                            */
/*                                                                           */
/*       04/05/93 NGR Created.                                               */
/* OUT1  02/07/93 NGR Change output string                                   */
/*****************************************************************************/

/* Global variables */

#ifdef DOS5
  #include <os2.h>
  #include <time.h>

  #define GetTickCount clock

#endif

typedef unsigned long RESULT;

#ifdef SENDTP
union
{
   struct appc_hdr             hdr;
   struct tp_started           tpstart;
   struct mc_send_conversation sndconv;
   struct mc_allocate          allocate;
   struct mc_send_data         snddata;
   struct mc_deallocate        deallocate;
   struct mc_confirm           confirm;
   struct tp_ended             tpend;
} vcb;
#else
union
{
   struct appc_hdr             hdr;
   struct receive_allocate     rcvalloc;
   struct mc_receive_and_wait  rcvwait;
   struct mc_confirmed         confirmed;
   struct tp_ended             tpend;
} vcb;
#endif
char FAR * vcbptr;

struct convert cnvt;
char FAR * cnvtptr;

char LocalTPName[64];
unsigned short SendSize;
unsigned short NumConversations;
BOOL TPDead;
BOOL FirstConv;
char FAR * DataPtr;
RESULT ConvStarted;
RESULT FAR * ResultPtr;
RESULT FAR * ResultBuf;
char FileName[60];
unsigned short ConvCount;
char TPid[8];
unsigned long Convid;

#ifdef SENDTP
char LocalLUAlias[8];
char RemoteLUAlias[8];
char ModeName[8];
char RemoteTPName[64];
unsigned short NumSends;
unsigned short ConfirmEvery;
BOOL SendConversation;
char datach;
unsigned short SendCount;
unsigned short ConfirmCount;
#else
BOOL Deallocated;
BOOL GotNumConv;
int GetStage;
#endif

#if (defined(WINDOWS)||defined(WIN32))
HWND hWndMain;
HANDLE async_corr;
unsigned short ASYNC_COMPLETE;
char title[30]={'\0'};
#endif

/* Function prototypes */

#ifndef SYNC
int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow);
BOOL InitialiseWinMain(HINSTANCE hInstance);
LONG FAR PASCAL TPWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
#else
void main( int argc, char FAR * argv[]);
#endif
void InitialiseMain(void);
void IssueNextVerb(void);
void ProcessReturns(void);
void ReadConfig(void);
void CONV_A_TO_E(char FAR * string,int length);
void CONV_E_TO_A(char FAR * string,int length);
void NewConversation(void);
int ReadString(char FAR * lpValueName, char FAR * lpData, int maxlen);
void PadString(char FAR * string, int length);
void OutputResults(void);
void Build_TP_ENDED(void);
#ifdef SENDTP
void Build_TP_STARTED(void);
void Build_MC_ALLOCATE(void);
void Build_MC_DEALLOCATE(void);
void Build_MC_SEND_DATA(void);
void Build_MC_SEND_CONVERSATION(void);
void Build_MC_CONFIRM(void);
void GenerateData(void);
void Send_Run_Details(void);
#else
void Build_RECEIVE_ALLOCATE(void);
void Build_MC_RECEIVE_AND_WAIT(void);
void Build_MC_CONFIRMED(void);
void Get_Run_Details(void);
#endif

/* Macros */

#define CLEARVCB memset(vcbptr,0,sizeof(vcb));
#ifdef SYNC
#define OUTPUTNUMBER printf("Conversation %d\n",ConvCount);
#else
#ifdef SENDTP
#define OUTPUTNUMBER sprintf(title,"APPC Send TP %d",ConvCount); \
                     SetWindowText(hWndMain,title);
#else
#define OUTPUTNUMBER sprintf(title,"APPC Receive TP %d",ConvCount); \
                     SetWindowText(hWndMain,title);
#endif
#endif
