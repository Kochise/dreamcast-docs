/* cpicsr.h */
/* (C) COPYRIGHT DATA CONNECTION LIMITED 1993 */

/*****************************************************************************/
/* Change History                                                            */
/*                                                                           */
/*       30/06/93 NGR Created.                                               */
/*****************************************************************************/

/* Global variables */

BOOL TPDead;
BOOL FirstConv;
CM_INT32 return_code;
CM_INT32 request_to_send_received;
int last_verb;
char * DataPtr;
unsigned short ConvCount;
unsigned char conversation_ID[8];
HWND hWndMain;
unsigned short ASYNC_COMPLETE;
char title[30]={'\0'};
typedef DWORD RESULT;
RESULT ConvStarted;
RESULT * ResultPtr;
RESULT * ResultBuf;

#ifdef CPICSEND
char datach;
unsigned short SendCount;
unsigned short ConfirmCount;
#else
CM_INT32 status_received;
CM_INT32 data_received;
CM_INT32 received_length;
BOOL Deallocated;
#endif

/* Config parameters */

CM_INT32 SendSize;
unsigned short NumConversations;
BOOL wait_mode;
BOOL blocking;
char FileName[60];
#ifdef CPICSEND
char SymDestName[9];
unsigned short NumSends;
unsigned short ConfirmEvery;
#else
char LocalTPName[64];
#endif

/* Function prototypes */

int PASCAL WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow);
BOOL InitialiseWinMain(HINSTANCE hInstance);
LONG FAR PASCAL TPWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void InitialiseMain(void);
void IssueNextVerb(void);
void ProcessReturns(void);
void ReadConfig(void);
void NewConversation(void);
int ReadString(char * lpValueName, char * lpData, int maxlen);
void PadString(char * string, int length);
void OutputResults(void);
void Build_TP_ENDED(void);
void GenerateData(void);
void Do_cminit(void);
void Do_cmallc(void);
void Do_cmsend(void);
void Do_cmrcv(void);
void Do_cmcfm(void);
void Do_cmcfmd(void);
void Do_cmdeal(void);
void Do_cmaccp(void);


/* Macros */
#define C_INIT 1
#define C_ALLC 2
#define C_SEND 3
#define C_CFM  4
#define C_RCV  5
#define C_ACCP 6
#define C_CFMD 7
#define C_DEAL 8

#ifdef CPICSEND
#define OUTPUTNUMBER sprintf(title,"CPI-C Send TP %d",ConvCount); \
                     SetWindowText(hWndMain,title);
#else
#define OUTPUTNUMBER sprintf(title,"CPI-C Receive TP %d",ConvCount); \
                     SetWindowText(hWndMain,title);
#endif
