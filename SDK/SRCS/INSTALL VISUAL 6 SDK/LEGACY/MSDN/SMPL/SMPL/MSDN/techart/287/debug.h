#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#define IDC_EDIT		     5000

#define IDR_DEBUGICON		     10
#define IDR_MAINICON		     20
#define IDR_DEBUGMENU		     30
#define IDR_DEBUGDIALOG 	     40

#define IDS_FRAMECLASS			     1000
#define IDS_DEBUGCLASS			     1001
#define IDS_DEBUGDLGTITLE		     1030
#define IDS_MDICLASS			     1002
#define IDS_CAPTION			     1003
#define IDS_EXEFILEEXT			     1004
#define IDS_FILEOPENTITLE		     1005
#define IDS_LOGFILEEXT			     1006
#define IDS_SAVEASTITLE 		     1007
#define IDS_INIFILE			     1008
#define IDS_EXITYESNO			     1009
#define IDS_ERRORCAPTION		     1010
#define IDS_CANTDBGFILE 		     1011
#define IDS_UNAVAILABLE 		     1012
#define IDS_HEAPCREATEFAILED		     1013
#define IDS_DBGEVNTCLOSEACK		     1014
#define IDS_DBGEVNTACTIVE		     1015
#define IDS_DBGEVNTCLOSE		     1016
#define IDS_DBGEVNTSUSPEND		     1017
#define IDS_DBGEVNTRESUME		     1018
#define IDS_DBGEVNTSETTHREAD		     1019
#define IDS_DBGEVNTINITACK		     1020
#define IDS_DBGEVNTSTOP 		     1021
#define IDS_DBGEVNTSTART		     1022
#define IDS_DBGEVNTSETPROCESS		     1023
#define IDS_SAVEFILE			     1024
#define IDS_SIBLING			     0x0000F000L
#define IDS_UNKNOWNDEBUGEVENT		     1026
#define IDS_PROCESSENDED		     1027
#define RIP_EVENT_LEVEL_1		     3030
#define RIP_EVENT_LEVEL_2		     3031
#define RIP_EVENT_LEVEL_3		     3032
#define RCBUG				     0x0000F000

#define IDM_PROCESSLOAD 		     2000
#define IDM_PROCESSCLOSE		     2001
#define IDM_PROCESSSTART		     2002
#define IDM_PROCESSSTOP 		     2003
#define IDM_PROCESSPRIORITIES		     2004
#define IDM_PROCESSEXIT 		     2008
#define IDM_EDITCUT			     2010
#define IDM_EDITCOPY			     2011
#define IDM_EDITPASTE			     2012
#define IDM_EDITCLEAR			     2013
#define IDM_EDITSAVEAS			     2014
#define IDM_VIEWTHREAD			     2031
#define IDM_VIEWPROCESS 		     2032
#define IDM_WINDOWCASCADE		     2040
#define IDM_WINDOWTILE			     2041
#define IDM_WINDOWARRANGE		     2042
#define IDM_HELPCONTENTS		     2050
#define IDM_HELPSEARCH			     2051
#define IDM_HELPONHELP			     2052
#define IDM_HELPABOUT			     2053
#define IDM_FIRSTCHILD			     3000

#define IDC_THREADLIST			     4001
#define IDC_THREADSUSPEND		     4002
#define IDC_THREADRESUME		     4003

#define IDC_THREADBASE			     5000
#define IDC_THREADCRITICAL		     IDC_THREADBASE + THREAD_PRIORITY_TIME_CRITICAL
#define IDC_THREADHIGHEST		     IDC_THREADBASE + THREAD_PRIORITY_HIGHEST
#define IDC_THREADABOVE 		     IDC_THREADBASE + THREAD_PRIORITY_ABOVE_NORMAL
#define IDC_THREADNORMAL		     IDC_THREADBASE + THREAD_PRIORITY_NORMAL
#define IDC_THREADBELOW 		     IDC_THREADBASE + THREAD_PRIORITY_BELOW_NORMAL
#define IDC_THREADLOWEST		     IDC_THREADBASE + THREAD_PRIORITY_LOWEST
#define IDC_THREADIDLE			     IDC_THREADBASE + THREAD_PRIORITY_IDLE

#define IDC_PROCESSBASE 		     6000
#define IDC_PROCESSREAL 		     IDC_PROCESSBASE + REALTIME_PRIORITY_CLASS
#define IDC_PROCESSHIGH 		     IDC_PROCESSBASE + HIGH_PRIORITY_CLASS
#define IDC_PROCESSNORMAL		     IDC_PROCESSBASE + NORMAL_PRIORITY_CLASS
#define IDC_PROCESSIDLE 		     IDC_PROCESSBASE + IDLE_PRIORITY_CLASS


#define DEBUGCXB	    0
#define DEBUGWXB	    8
#define WXB_LPDBGPROCESS    0
#define WXB_LPDBGEVENTS     4


// define event handle array indeces
#define CLOSEDEBUGGER	     0
#define SUSPENDDEBUGGER      1
#define RESUMEDEBUGGER	     2
#define DEBUGACTIVE	     3
#define nDEBUGEVENTS	     4


// define structures for debugging processes and threads
typedef struct DBGTHREAD    *LPDBGTHREAD;
typedef struct tagDbgThread
    {
    HANDLE		      hThread;
    DWORD		      dwThreadID;
    LPTHREAD_START_ROUTINE    lpStartAddress;
    BOOL		      bfActive;
    int 		      nPriority;
    LPDBGTHREAD 	      Next;
    }DBGTHREAD;

typedef struct tagDbgProcess
    {
    HANDLE	 hDbgHeap;
    DWORD	 dwProcessID;
    DWORD	 dwThreadID;
    HANDLE	 hProcess;
    HANDLE	 hFile;
    LPVOID	 lpImage;
    DWORD	 dwDbgInfoOffset;
    DWORD	 nDbgInfoSize;
    DBGTHREAD	 *lpThreads;
    HWND	 hWnd;
    DWORD	 dwPriority;
    char	 szModule[MAX_PATH];
    }DBGPROCESS;


// function prototypes and globals in main.c
LONG WINAPI FrameWndProc (HWND, UINT, UINT, LONG);
LONG WINAPI DebugWndProc (HWND, UINT, UINT, LONG);
void WINAPI AppendEditText (HWND, UINT, char *);

// function prototypes for dbfile.c
BOOL WINAPI GetFileName (HWND, char *);
void WINAPI GetFileFromPath (char *, char *);
BOOL WINAPI SaveFile (HWND);

// function prototypes for debug.c
DBGPROCESS WINAPI *StartDebugger (char *, LPHANDLE);
void WINAPI CloseDebugger (DBGPROCESS *, LPHANDLE);
BOOL WINAPI DuplicateDebugData (DBGPROCESS *, DBGPROCESS **);
void WINAPI FreeDebugData (DBGPROCESS *);

// function protorypes for dbdlg.c
BOOL WINAPI PriorityDlgProc (HWND, UINT, UINT, LONG);
