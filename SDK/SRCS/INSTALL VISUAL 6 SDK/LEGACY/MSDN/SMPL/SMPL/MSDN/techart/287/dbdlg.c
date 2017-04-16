#include "debug.h"


int WINAPI GetBasePriority (DWORD, int);
void WINAPI MakeThreadListItem (char *, DWORD, BOOL, DWORD, int);
void WINAPI UncheckThreadPriorityBtn (HWND);


/* process/thread priority control dialog */
BOOL WINAPI PriorityDlgProc (
    HWND    hDlg,
    UINT    uMsg,
    UINT    uParam,
    LONG    lParam)
{
       BOOL	     bRet = TRUE;
static DBGPROCESS    *lpDbgProcess;

    switch (uMsg)
	{
	case WM_INITDIALOG:
	    {
	    DBGTHREAD	 *lpDbgThread;
	    char	 szThreadStr[50];
	    HANDLE	 hChild;
	    int 	 nTabs[2];
	    char	 szDialogTitle[MAX_PATH];
	    char	 szModule[MAX_PATH];

	    /* save debug information in static pointer */
	    lpDbgProcess = (DBGPROCESS *)lParam;

	    /* set title of dialog with module name */
	    LoadString (GetModuleHandle (NULL),
			IDS_DEBUGDLGTITLE,
			szDialogTitle,
			MAX_PATH);
	    GetFileFromPath (lpDbgProcess->szModule, szModule);
	    strcat (szDialogTitle, szModule);
	    SetWindowText (hDlg, szDialogTitle);

	    /* set tab positions for list box */
	    hChild = GetDlgItem (hDlg, IDC_THREADLIST);
	    nTabs[0] = 40;
	    nTabs[1] = 100;
	    SendMessage (hChild, LB_SETTABSTOPS, 2, (LPARAM)&nTabs);

	    /* load list box with thread information */
	    lpDbgThread = (DBGTHREAD *)lpDbgProcess->lpThreads;
	    while (lpDbgThread)
		{
		MakeThreadListItem (szThreadStr,
				    lpDbgThread->dwThreadID,
				    lpDbgThread->bfActive,
				    lpDbgProcess->dwPriority,
				    lpDbgThread->nPriority);

		/* add string to list box */
		SendMessage (hChild, LB_ADDSTRING, 0, (LPARAM)szThreadStr);

		/* increment thread node pointer */
		lpDbgThread = (DBGTHREAD *)lpDbgThread->Next;
		}

	    /* initialize listbox to first thread */
	    SendMessage (hChild, LB_SETCURSEL, 0, 0);

	    /* initialize priority class radio buttons */
	    SendMessage (GetDlgItem (hDlg, IDC_PROCESSBASE+lpDbgProcess->dwPriority),
			 BM_SETCHECK,
			 1,
			 0);

	    /* initialize thread priority radio buttons */
	    lpDbgThread = (DBGTHREAD *)lpDbgProcess->lpThreads;
	    SendMessage (GetDlgItem (hDlg, IDC_THREADBASE+lpDbgThread->nPriority),
			 BM_SETCHECK,
			 1,
			 0);
	    }
	    break;

	case WM_COMMAND:
	    switch (LOWORD (uParam))
		{
		case IDC_THREADSUSPEND:
		case IDC_THREADRESUME:
		    {
		    int    i;
		    int    nThread = SendMessage (GetDlgItem (hDlg, IDC_THREADLIST),
						  LB_GETCURSEL,
						  0,
						  0);
		    DBGTHREAD	 *lpDbgThread = (DBGTHREAD *)lpDbgProcess->lpThreads;
		    char	 szThreadItem[50];

		    for (i=0; i<nThread; i++)
			lpDbgThread = (DBGTHREAD *)lpDbgThread->Next;

		    if (uParam == IDC_THREADSUSPEND)
			lpDbgThread->bfActive = FALSE;
		    else
			lpDbgThread->bfActive = TRUE;

		    /* update thread string base priority */
		    MakeThreadListItem (szThreadItem,
					lpDbgThread->dwThreadID,
					lpDbgThread->bfActive,
					lpDbgProcess->dwPriority,
					lpDbgThread->nPriority);

		    /* update list box with new item */
		    SendMessage (GetDlgItem (hDlg, IDC_THREADLIST),
				 WM_SETREDRAW,
				 0,
				 0);
		    SendMessage (GetDlgItem (hDlg, IDC_THREADLIST),
				 LB_INSERTSTRING,
				 nThread,
				 (LPARAM)szThreadItem);
		    SendMessage (GetDlgItem (hDlg, IDC_THREADLIST),
				 LB_DELETESTRING,
				 nThread+1,
				 (LPARAM)szThreadItem);
		    SendMessage (GetDlgItem (hDlg, IDC_THREADLIST),
				 WM_SETREDRAW,
				 1,
				 0);
		    }
		    break;

		case IDC_THREADCRITICAL:
		case IDC_THREADHIGHEST:
		case IDC_THREADABOVE:
		case IDC_THREADNORMAL:
		case IDC_THREADBELOW:
		case IDC_THREADLOWEST:
		case IDC_THREADIDLE:
		    if (HIWORD(uParam) == BN_CLICKED)
			{
			int    i;
			int    nThread = SendMessage (GetDlgItem (hDlg, IDC_THREADLIST),
						      LB_GETCURSEL,
						      0,
						      0);
			DBGTHREAD    *lpDbgThread = (DBGTHREAD *)lpDbgProcess->lpThreads;
			char	     szThreadItem[50];

			for (i=0; i<nThread; i++)
			    lpDbgThread = (DBGTHREAD *)lpDbgThread->Next;

			/* update thread priority for this thread */
			lpDbgThread->nPriority = uParam - IDC_THREADBASE;

			/* update thread string base priority */
			MakeThreadListItem (szThreadItem,
					    lpDbgThread->dwThreadID,
					    lpDbgThread->bfActive,
					    lpDbgProcess->dwPriority,
					    lpDbgThread->nPriority);

			/* update list box with new item */
			SendMessage (GetDlgItem (hDlg, IDC_THREADLIST),
				     WM_SETREDRAW,
				     0,
				     0);
			SendMessage (GetDlgItem (hDlg, IDC_THREADLIST),
				     LB_INSERTSTRING,
				     nThread,
				     (LPARAM)szThreadItem);
			SendMessage (GetDlgItem (hDlg, IDC_THREADLIST),
				     LB_DELETESTRING,
				     nThread+1,
				     (LPARAM)szThreadItem);
			SendMessage (GetDlgItem (hDlg, IDC_THREADLIST),
				     WM_SETREDRAW,
				     1,
				     0);
			}
		    break;

		case IDC_PROCESSREAL:
		case IDC_PROCESSHIGH:
		case IDC_PROCESSNORMAL:
		case IDC_PROCESSIDLE:
		    if (HIWORD(uParam) == BN_CLICKED)
			{
			char	     szThreadItem[50];
			DBGTHREAD    *lpDbgThread = (DBGTHREAD *)lpDbgProcess->lpThreads;
			int	     nCurSel = SendMessage (GetDlgItem (hDlg, IDC_THREADLIST),
							    LB_GETCURSEL,
							    0,
							    0);

			/* set new priority class in debug data */
			lpDbgProcess->dwPriority = uParam - IDC_PROCESSBASE;

			/* refresh entire list box base priorities*/
			SendMessage (GetDlgItem (hDlg, IDC_THREADLIST),
				     WM_SETREDRAW,
				     0,
				     0);
			SendMessage (GetDlgItem (hDlg, IDC_THREADLIST),
				     LB_RESETCONTENT,
				     0,
				     0);

			while (lpDbgThread)
			    {
			    MakeThreadListItem (szThreadItem,
						lpDbgThread->dwThreadID,
						lpDbgThread->bfActive,
						lpDbgProcess->dwPriority,
						lpDbgThread->nPriority);

			    /* update list box with new item */
			    SendMessage (GetDlgItem (hDlg, IDC_THREADLIST),
					 LB_ADDSTRING,
					 0,
					 (LPARAM)szThreadItem);

			    lpDbgThread = (DBGTHREAD *)lpDbgThread->Next;
			    }

			SendMessage (GetDlgItem (hDlg, IDC_THREADLIST),
				     WM_SETREDRAW,
				     1,
				     0);
			SendMessage (GetDlgItem (hDlg, IDC_THREADLIST),
				     LB_SETCURSEL,
				     0,
				     0);
			}
		    break;

		case IDC_THREADLIST:
		    if (HIWORD (uParam) == LBN_SELCHANGE)
			{
			int    nThread = SendMessage (GetDlgItem (hDlg, IDC_THREADLIST),
						      LB_GETCURSEL,
						      0,
						      0);
			DBGTHREAD    *lpDbgThread = (DBGTHREAD *)lpDbgProcess->lpThreads;

			while (nThread--)
			    lpDbgThread = (DBGTHREAD *)lpDbgThread->Next;

			UncheckThreadPriorityBtn (hDlg);
			SendMessage (GetDlgItem (hDlg, IDC_THREADBASE+lpDbgThread->nPriority),
				     BM_SETCHECK,
				     1,
				     0);
			}
		    break;

		case IDOK:
		case IDCANCEL:
		    EndDialog (hDlg, LOWORD (uParam) == IDOK);
		    break;
		}
	    break;

	default:
	    bRet = FALSE;
	    break;
	}

    // return (message was processed);
    return bRet;
}



void WINAPI UncheckThreadPriorityBtn (
    HWND    hDlg)
{
    /* uncheck whatever button is already checked */
    if (SendMessage (GetDlgItem (hDlg,
				 IDC_THREADBASE + THREAD_PRIORITY_TIME_CRITICAL),
		     BM_GETCHECK, 0, 0))
	SendMessage (GetDlgItem (hDlg,
				 IDC_THREADBASE+THREAD_PRIORITY_TIME_CRITICAL),
		     BM_SETCHECK, 0, 0);
    if (SendMessage (GetDlgItem (hDlg,
				 IDC_THREADBASE + THREAD_PRIORITY_HIGHEST),
		     BM_GETCHECK, 0, 0))
	SendMessage (GetDlgItem (hDlg,
				 IDC_THREADBASE + THREAD_PRIORITY_HIGHEST),
		     BM_SETCHECK, 0, 0);
    if (SendMessage (GetDlgItem (hDlg,
				 IDC_THREADBASE + THREAD_PRIORITY_ABOVE_NORMAL),
		     BM_GETCHECK, 0, 0))
	SendMessage (GetDlgItem (hDlg,
				 IDC_THREADBASE + THREAD_PRIORITY_ABOVE_NORMAL),
		     BM_SETCHECK, 0, 0);
    if (SendMessage (GetDlgItem (hDlg,
				 IDC_THREADBASE + THREAD_PRIORITY_NORMAL),
		     BM_GETCHECK, 0, 0))
	SendMessage (GetDlgItem (hDlg,
				 IDC_THREADBASE + THREAD_PRIORITY_NORMAL),
		     BM_SETCHECK, 0, 0);
    if (SendMessage (GetDlgItem (hDlg,
				 IDC_THREADBASE + THREAD_PRIORITY_BELOW_NORMAL),
		     BM_GETCHECK, 0, 0))
	SendMessage (GetDlgItem (hDlg,
				 IDC_THREADBASE + THREAD_PRIORITY_BELOW_NORMAL),
		     BM_SETCHECK, 0, 0);
    if (SendMessage (GetDlgItem (hDlg,
				 IDC_THREADBASE + THREAD_PRIORITY_LOWEST),
		     BM_GETCHECK, 0, 0))
	SendMessage (GetDlgItem (hDlg,
				 IDC_THREADBASE + THREAD_PRIORITY_LOWEST),
		     BM_SETCHECK, 0, 0);
    if (SendMessage (GetDlgItem (hDlg,
				 IDC_THREADBASE + THREAD_PRIORITY_IDLE),
		     BM_GETCHECK, 0, 0))
	SendMessage (GetDlgItem (hDlg,
				 IDC_THREADBASE + THREAD_PRIORITY_IDLE),
		     BM_SETCHECK, 0, 0);
}




int WINAPI GetBasePriority (
    DWORD    dwPriClass,
    int      nPriThread)
{
    switch (dwPriClass)
	{
	case IDLE_PRIORITY_CLASS:
	    switch (nPriThread)
		{
		case THREAD_PRIORITY_TIME_CRITICAL:
		    return (15);
		    break;
		case THREAD_PRIORITY_HIGHEST:
		    return (5);
		    break;
		case THREAD_PRIORITY_ABOVE_NORMAL:
		    return (4);
		    break;
		case THREAD_PRIORITY_NORMAL:
		    return (3);
		    break;
		case THREAD_PRIORITY_BELOW_NORMAL:
		    return (2);
		    break;
		case THREAD_PRIORITY_LOWEST:
		    return (1);
		    break;
		case THREAD_PRIORITY_IDLE:
		    return (1);
		    break;
		}
	    break;

	case NORMAL_PRIORITY_CLASS:
	    switch (nPriThread)
		{
		case THREAD_PRIORITY_TIME_CRITICAL:
		    return (15);
		    break;
		case THREAD_PRIORITY_HIGHEST:
		    return (9);
		    break;
		case THREAD_PRIORITY_ABOVE_NORMAL:
		    return (8);
		    break;
		case THREAD_PRIORITY_NORMAL:
		    return (7);
		    break;
		case THREAD_PRIORITY_BELOW_NORMAL:
		    return (6);
		    break;
		case THREAD_PRIORITY_LOWEST:
		    return (5);
		    break;
		case THREAD_PRIORITY_IDLE:
		    return (1);
		    break;
		}
	    break;

	case HIGH_PRIORITY_CLASS:
	    switch (nPriThread)
		{
		case THREAD_PRIORITY_TIME_CRITICAL:
		    return (15);
		    break;
		case THREAD_PRIORITY_HIGHEST:
		    return (15);
		    break;
		case THREAD_PRIORITY_ABOVE_NORMAL:
		    return (14);
		    break;
		case THREAD_PRIORITY_NORMAL:
		    return (13);
		    break;
		case THREAD_PRIORITY_BELOW_NORMAL:
		    return (12);
		    break;
		case THREAD_PRIORITY_LOWEST:
		    return (11);
		    break;
		case THREAD_PRIORITY_IDLE:
		    return (1);
		    break;
		}
	    break;

	case REALTIME_PRIORITY_CLASS:
	    switch (nPriThread)
		{
		case THREAD_PRIORITY_TIME_CRITICAL:
		    return (31);
		    break;
		case THREAD_PRIORITY_HIGHEST:
		    return (26);
		    break;
		case THREAD_PRIORITY_ABOVE_NORMAL:
		    return (25);
		    break;
		case THREAD_PRIORITY_NORMAL:
		    return (24);
		    break;
		case THREAD_PRIORITY_BELOW_NORMAL:
		    return (23);
		    break;
		case THREAD_PRIORITY_LOWEST:
		    return (22);
		    break;
		case THREAD_PRIORITY_IDLE:
		    return (16);
		    break;
		}
	    break;
	}
}



void WINAPI MakeThreadListItem (
    char     *lpszThreadStr,
    DWORD    dwThreadID,
    BOOL     bfActive,
    DWORD    dwPriClass,
    int      nPriThread)
{
    char    NumBuff[10];

    /* make string with thread info */
    strcpy (lpszThreadStr, itoa (dwThreadID, NumBuff, 10));
    strcat (lpszThreadStr, "\t");
    if (bfActive)
	strcat (lpszThreadStr, "Active");
    else
	strcat (lpszThreadStr, "Suspended");
    strcat (lpszThreadStr, "\t");
    strcat (lpszThreadStr,
	    itoa (GetBasePriority (dwPriClass, nPriThread), NumBuff, 10));
}
