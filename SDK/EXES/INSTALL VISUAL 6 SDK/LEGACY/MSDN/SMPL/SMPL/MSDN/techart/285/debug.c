#include "debug.h"

// local functions
BOOL WINAPI DebugEventThread (DBGPROCESS *);
BOOL WINAPI CreateDebugEvents (LPHANDLE, DWORD);
void WINAPI ExitDebuggeeProcess (DBGPROCESS *);
void WINAPI AddNode (DBGPROCESS *, DWORD, int, HANDLE, LPTHREAD_START_ROUTINE);
void WINAPI RemoveNode (DBGPROCESS *, DWORD);
void WINAPI SuspendDebuggeeProcess (DBGPROCESS *);
void WINAPI ResumeDebuggeeProcess (DBGPROCESS *);


// start debug thread, and return event active handle
DBGPROCESS WINAPI *StartDebugger (
    char	*lpszModule,
    LPHANDLE	lpDbgEvents)
{
    DWORD	  TID;
    HANDLE	  hDebugHeap;
    DBGPROCESS	  *lpDbgProcess;
    char	  szEvent[MAX_PATH];
    HANDLE	  hEvent;

    // allocate serialized heap for debugging this process and all of its
    //	threads.  the first thread is automatic as part of the process init.
    //	each new thread requires another DBGTHREAD structure heap allocation
    if (!(hDebugHeap = HeapCreate (0,
				   sizeof (DBGPROCESS) + sizeof (DBGTHREAD),
				   0)))
	return NULL;
    lpDbgProcess = (DBGPROCESS *)HeapAlloc (hDebugHeap, 0, sizeof (DBGPROCESS));
    lpDbgProcess->hDbgHeap = hDebugHeap;

    // store module name in dbgprocess structure
    strcpy (lpDbgProcess->szModule, lpszModule);

    // create initialize event
    LoadString (GetModuleHandle (NULL),
		IDS_DBGEVNTINITACK,
		szEvent,
		MAX_PATH);
    hEvent = CreateEvent (NULL, TRUE, FALSE, szEvent);

    // create debug thread
    if (!(CreateThread ((LPSECURITY_ATTRIBUTES)NULL,
			4096,
			(LPTHREAD_START_ROUTINE)DebugEventThread,
			(LPVOID)lpDbgProcess,
			0,
			&TID)))
	return NULL;

    // wait for debugger to complete initialization before opening debug events
    WaitForSingleObject (hEvent, INFINITE);
    CloseHandle (hEvent);

    // create unique debug events using debuggee process ID
    if (!CreateDebugEvents (lpDbgEvents, lpDbgProcess->dwProcessID))
	return NULL;

    // successfull thread and event start
    return lpDbgProcess;
}



// function notifies debug thread to terminate, frees handles, and destroys heap
void WINAPI CloseDebugger (
    DBGPROCESS *lpDbgProcess,
    LPHANDLE   hDbgEvents)
{
    char    szEvent[MAX_PATH];
    HANDLE  hEvent;
    int     i;

    // create acknowledge close event
    LoadString (GetModuleHandle (NULL), IDS_DBGEVNTCLOSEACK, szEvent, MAX_PATH);
    hEvent = CreateEvent (NULL, TRUE, FALSE, szEvent);

    // set close event for debug thread and wait for acknowledge
    SetEvent (hDbgEvents[CLOSEDEBUGGER]);
    WaitForSingleObject (hEvent, INFINITE);

    // close all event handles
    for (i=0; i<nDEBUGEVENTS; i++)
	CloseHandle (hDbgEvents[i]);
    CloseHandle (hEvent);

    // destroy this debug heap
    HeapDestroy (lpDbgProcess->hDbgHeap);
}



// local function creates debug event objects for thread synchronization
BOOL WINAPI CreateDebugEvents (
    LPHANDLE	lpDbgEvents,
    DWORD	dwProcessID)
{
    char    szEvent[MAX_PATH];
    char    Buff[15];


    LoadString (GetModuleHandle (NULL), IDS_DBGEVNTACTIVE, szEvent, sizeof (szEvent));
    strcat (szEvent, itoa (dwProcessID, Buff, 10));
    if (!(lpDbgEvents[DEBUGACTIVE] = CreateEvent ((LPSECURITY_ATTRIBUTES)NULL,
						  TRUE,
						  TRUE,
						  szEvent)))
	return FALSE;

    LoadString (GetModuleHandle (NULL), IDS_DBGEVNTCLOSE, szEvent, sizeof (szEvent));
    strcat (szEvent, itoa (dwProcessID, Buff, 10));
    if (!(lpDbgEvents[CLOSEDEBUGGER] = CreateEvent ((LPSECURITY_ATTRIBUTES)NULL,
						   TRUE,
						   FALSE,
						   szEvent)))
	{
	CloseHandle (lpDbgEvents[DEBUGACTIVE]);
	return FALSE;
	}

    LoadString (GetModuleHandle (NULL), IDS_DBGEVNTSTOP, szEvent, sizeof (szEvent));
    strcat (szEvent, itoa (dwProcessID, Buff, 10));
    if (!(lpDbgEvents[SUSPENDDEBUGGER] = CreateEvent ((LPSECURITY_ATTRIBUTES)NULL,
						      TRUE,
						      FALSE,
						      szEvent)))
	{
	CloseHandle (lpDbgEvents[DEBUGACTIVE]);
	CloseHandle (lpDbgEvents[CLOSEDEBUGGER]);
	return FALSE;
	}

    LoadString (GetModuleHandle (NULL), IDS_DBGEVNTSTART, szEvent, sizeof (szEvent));
    strcat (szEvent, itoa (dwProcessID, Buff, 10));
    if (!(lpDbgEvents[RESUMEDEBUGGER] = CreateEvent ((LPSECURITY_ATTRIBUTES)NULL,
						     TRUE,
						     FALSE,
						     szEvent)))
	{
	CloseHandle (lpDbgEvents[DEBUGACTIVE]);
	CloseHandle (lpDbgEvents[CLOSEDEBUGGER]);
	CloseHandle (lpDbgEvents[SUSPENDDEBUGGER]);
	return FALSE;
	}

    // success
    return TRUE;
}



// main daddyo thread that is the debugger residing over a debuggee
BOOL WINAPI DebugEventThread (
    DBGPROCESS	  *lpDbgProcess)
{
    DEBUG_EVENT 	   de;
    HANDLE		   hDbgEvent[nDEBUGEVENTS];
    HANDLE		   hEvent;
    char		   szEvent[MAX_PATH];
    STARTUPINFO 	   si;
    PROCESS_INFORMATION    pi;


    // initialize process startup information
    si.cb	       = sizeof (si);
    si.lpReserved      = NULL;
    si.lpDesktop       = NULL;
    si.lpTitle	       = NULL;
    si.dwX	       = 0;
    si.dwY	       = 0;
    si.dwXSize	       = 0;
    si.dwYSize	       = 0;
    si.dwXCountChars   = 0;
    si.dwYCountChars   = 0;
    si.dwFillAttribute = 0;
    si.dwFlags	       = STARTF_FORCEONFEEDBACK | STARTF_USESHOWWINDOW;
    si.wShowWindow     = SW_SHOWNORMAL;
    si.cbReserved2     = 0;
    si.lpReserved2     = NULL;

    // create debug process on module name
    if (!CreateProcess (lpDbgProcess->szModule,
			NULL,
			(LPSECURITY_ATTRIBUTES)NULL,
			(LPSECURITY_ATTRIBUTES)NULL,
			FALSE,
			DEBUG_PROCESS,
			NULL,
			NULL,
			(LPSTARTUPINFO)&si,
			(LPPROCESS_INFORMATION)&pi))
	{
	MessageBox (NULL, "Error starting debug process", "Error", MB_OK);
	return FALSE;
	}

    // add initial thread to linked list
    AddNode (lpDbgProcess,
	     pi.dwThreadId,
	     GetThreadPriority (pi.hThread),
	     pi.hThread,
	     NULL);

    // store process info
    lpDbgProcess->dwProcessID = pi.dwProcessId;
    lpDbgProcess->dwThreadID = pi.dwThreadId;
    lpDbgProcess->hProcess = pi.hProcess;
    lpDbgProcess->dwPriority = GetPriorityClass (pi.hProcess);

    // signal completion of initialization to calling thread
    LoadString (GetModuleHandle (NULL),
		IDS_DBGEVNTINITACK,
		szEvent,
		MAX_PATH);
    hEvent = OpenEvent (EVENT_ALL_ACCESS, FALSE, szEvent);
    SetEvent (hEvent);
    CloseHandle (hEvent);

    // open debug events
    CreateDebugEvents (hDbgEvent, lpDbgProcess->dwProcessID);

    // start debug event loop
    while (TRUE)
	{
	int    nIndex;

	// wait for debugger active
	switch (nIndex = WaitForMultipleObjects (nDEBUGEVENTS, hDbgEvent, FALSE, INFINITE))
	    {
	    case CLOSEDEBUGGER:
		{
		int    i;

		/* terminate debuggee process */
		TerminateProcess (lpDbgProcess->hProcess, 0);

		// signal close acknowledge event
		LoadString (GetModuleHandle (NULL),
			    IDS_DBGEVNTCLOSEACK,
			    szEvent,
			    MAX_PATH);

		hEvent = OpenEvent (EVENT_ALL_ACCESS, FALSE, szEvent);
		SetEvent (hEvent);

		// close all debug events
		for (i=0; i<nDEBUGEVENTS; i++)
		    CloseHandle (hDbgEvent[i]);
		CloseHandle (hEvent);

		// exit debugger now
		return TRUE;
		}
		break;

	    case SUSPENDDEBUGGER:
		SuspendDebuggeeProcess (lpDbgProcess);
		ResetEvent (hDbgEvent[DEBUGACTIVE]);
		ResetEvent (hDbgEvent[SUSPENDDEBUGGER]);
		break;

	    case RESUMEDEBUGGER:
		ResumeDebuggeeProcess (lpDbgProcess);
		SetEvent (hDbgEvent[DEBUGACTIVE]);
		ResetEvent (hDbgEvent[RESUMEDEBUGGER]);
		break;

	    case DEBUGACTIVE:
		// if debug active
		if ((WaitForDebugEvent (&de, (DWORD)100)))
		    {
		    if (de.dwProcessId == lpDbgProcess->dwProcessID)
			{
			switch (de.dwDebugEventCode)
			    {
			    case EXCEPTION_DEBUG_EVENT:
				AppendEditText (lpDbgProcess->hWnd,
						de.u.Exception.ExceptionRecord.ExceptionCode,
						NULL);
				break;

			    case CREATE_PROCESS_DEBUG_EVENT:
				/* add process information to linked list */
				lpDbgProcess->hFile =
				    de.u.CreateProcessInfo.hFile;
				lpDbgProcess->lpImage =
				    de.u.CreateProcessInfo.lpBaseOfImage;
				lpDbgProcess->dwDbgInfoOffset =
				    de.u.CreateProcessInfo.dwDebugInfoFileOffset;
				lpDbgProcess->nDbgInfoSize =
				    de.u.CreateProcessInfo.nDebugInfoSize;

				/* add start address of initial thread */
				lpDbgProcess->lpThreads->lpStartAddress =
				    de.u.CreateProcessInfo.lpStartAddress;

				AppendEditText (lpDbgProcess->hWnd,
						de.dwDebugEventCode + RCBUG,
						NULL);
				break;

			    case CREATE_THREAD_DEBUG_EVENT:
				/* add new thread to linked list */
				AddNode (lpDbgProcess,
					 de.dwThreadId,
					 GetThreadPriority (de.u.CreateThread.hThread),
					 de.u.CreateThread.hThread,
					 de.u.CreateThread.lpStartAddress);
				AppendEditText (lpDbgProcess->hWnd,
						de.dwDebugEventCode + RCBUG,
						NULL);
				break;

			    case EXIT_PROCESS_DEBUG_EVENT:
				AppendEditText (lpDbgProcess->hWnd,
						de.dwDebugEventCode + RCBUG,
						NULL);

				AppendEditText (lpDbgProcess->hWnd,
						IDS_PROCESSENDED,
						NULL);
				PostMessage (lpDbgProcess->hWnd, WM_CLOSE, 0, 0);
				break;

			    case EXIT_THREAD_DEBUG_EVENT:
				/* remove this thread from linked list */
				RemoveNode (lpDbgProcess, de.dwThreadId);
				AppendEditText (lpDbgProcess->hWnd,
						de.dwDebugEventCode + RCBUG,
						NULL);
				break;

			    case RIP_EVENT:
				{
				char	*lpszBuffer;

				/* standard rip event message */
				AppendEditText (lpDbgProcess->hWnd,
						de.dwDebugEventCode + RCBUG,
						NULL);

				/* check severity type of this rip event */
				switch (de.u.RipInfo.dwType)
				    {
				    case 1:
					AppendEditText (lpDbgProcess->hWnd,
							RIP_EVENT_LEVEL_1,
							NULL);
					break;

				    case 2:
					AppendEditText (lpDbgProcess->hWnd,
							RIP_EVENT_LEVEL_2,
							NULL);
					break;

				    case 3:
					AppendEditText (lpDbgProcess->hWnd,
							RIP_EVENT_LEVEL_3,
							NULL);
					break;
				    }

				/* get formatted message from system */
				FormatMessage (FORMAT_MESSAGE_ALLOCATE_BUFFER |
					       FORMAT_MESSAGE_FROM_SYSTEM,
					       NULL,
					       de.u.RipInfo.dwError,
					       MAKELONG (MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), 0),
					       lpszBuffer,
					       0,
					       NULL);
				AppendEditText (lpDbgProcess->hWnd,
						0,
						lpszBuffer);
				LocalFree ((HLOCAL)lpszBuffer);
				}
				break;

			    case LOAD_DLL_DEBUG_EVENT:
			    case UNLOAD_DLL_DEBUG_EVENT:
			    case OUTPUT_DEBUG_STRING_EVENT:
				AppendEditText (lpDbgProcess->hWnd,
						de.dwDebugEventCode + RCBUG,
						NULL);
				break;

			    default:
				AppendEditText (lpDbgProcess->hWnd,
						IDS_UNKNOWNDEBUGEVENT,
						NULL);
				break;
			    }
			}
		    else
			/* notify of sibling process debug event */
			AppendEditText (lpDbgProcess->hWnd,
					de.dwDebugEventCode + IDS_SIBLING,
					NULL);

		    ContinueDebugEvent (de.dwProcessId, de.dwThreadId, DBG_CONTINUE);
		    }
		break;
	    }

	}

    return TRUE;
}




void WINAPI SuspendDebuggeeProcess (
    DBGPROCESS	  *lppr)
{
    DBGTHREAD	 *lpth = (DBGTHREAD *)lppr->lpThreads;

    while (lpth)
	{
	SuspendThread (lpth->hThread);
	lpth = (DBGTHREAD *)lpth->Next;
	}
}




void WINAPI ResumeDebuggeeProcess (
    DBGPROCESS	  *lppr)
{
    DBGTHREAD	 *lpth = (DBGTHREAD *)lppr->lpThreads;

    while (lpth)
	{
	ResumeThread (lpth->hThread);
	lpth = (DBGTHREAD *)lpth->Next;
	}
}




void WINAPI AddNode (
    DBGPROCESS		      *lppr,
    DWORD		      dwThreadId,
    int 		      nPriority,
    HANDLE		      hThread,
    LPTHREAD_START_ROUTINE    lpStart)
{
    DBGTHREAD	 *lpth;
    DBGTHREAD	 *pNode = lppr->lpThreads;

    /* allocate thread node off heap */
    lpth = (DBGTHREAD *)HeapAlloc (lppr->hDbgHeap, 0, sizeof (DBGTHREAD));

    /* initialize thread data */
    lpth->lpStartAddress = lpStart;
    lpth->dwThreadID = dwThreadId;
    lpth->nPriority = nPriority;
    lpth->hThread = hThread;
    lpth->bfActive = TRUE;
    lpth->Next = NULL;

    /* set linked list pointers */
    while (pNode && pNode->Next)
	pNode = (DBGTHREAD *)pNode->Next;

    if (!pNode)
	lppr->lpThreads = lpth;
    else
	(DBGTHREAD *)pNode->Next = lpth;
}




void WINAPI RemoveNode (
    DBGPROCESS	  *lppr,
    DWORD	  dwThreadId)
{
    DBGTHREAD	 *pNode = lppr->lpThreads;
    DBGTHREAD	 *lpth;

    while (pNode->Next &&
	   ((DBGTHREAD *)(pNode->Next))->dwThreadID != dwThreadId)
	pNode = (DBGTHREAD *)pNode->Next;

    if (pNode->Next)
	{
	lpth = (DBGTHREAD *)pNode->Next;
	pNode->Next = ((DBGTHREAD *)(pNode->Next))->Next;
	HeapFree (lppr->hDbgHeap, 0, (LPSTR)lpth);
	}

    else if (pNode->dwThreadID == dwThreadId)
	{
	lpth = pNode;
	lppr->lpThreads = NULL;
	HeapFree (lppr->hDbgHeap, 0, (LPSTR)lpth);
	}
}




BOOL WINAPI DuplicateDebugData (
    DBGPROCESS	  *lpDbgProcess,
    DBGPROCESS	  **lpDupProcess)
{
    HANDLE	   hHeap;
    DBGTHREAD	   *lpDbgThread,
		   *lpDupThread,
		   *lpEnd;

    /* allocate heap */
    if (!(hHeap = HeapCreate (0,
			      sizeof (DBGPROCESS) + sizeof (DBGTHREAD),
			      0)))
	return FALSE;
    *lpDupProcess = (DBGPROCESS *)HeapAlloc (hHeap, 0, sizeof (DBGPROCESS));
    lpDupThread = (DBGTHREAD *)HeapAlloc (hHeap, 0, sizeof (DBGTHREAD));

    /* copy process and initial thread structure over via pointer copy */
    **lpDupProcess = *lpDbgProcess;
    *lpDupThread = *(lpDbgProcess->lpThreads);

    /* update heap handle and thread list pointer */
    (*lpDupProcess)->hDbgHeap = hHeap;
    (*lpDupProcess)->lpThreads = lpDupThread;

    /* allocate each thread structure node */
    lpDbgThread = (DBGTHREAD *)lpDbgProcess->lpThreads;
    lpEnd = lpDupThread;
    while (lpDbgThread->Next)
	{
	lpDupThread = (DBGTHREAD *)HeapAlloc (hHeap, 0, sizeof (DBGTHREAD));
	*lpDupThread = *(DBGTHREAD *)(lpDbgThread->Next);
	lpEnd->Next = (LPDBGTHREAD)lpDupThread;
	lpEnd = (DBGTHREAD *)lpEnd->Next;
	lpDbgThread = (DBGTHREAD *)lpDbgThread->Next;
	}
}



void WINAPI FreeDebugData (
    DBGPROCESS	  *lpGarbage)
{
    /* destroy heap */
    HeapDestroy (lpGarbage->hDbgHeap);
}
