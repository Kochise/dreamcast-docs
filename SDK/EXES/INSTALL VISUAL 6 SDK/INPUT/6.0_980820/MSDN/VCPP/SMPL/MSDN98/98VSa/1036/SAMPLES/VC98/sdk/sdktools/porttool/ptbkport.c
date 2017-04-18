
/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples. 
*       Copyright (C) 1993-96 Microsoft Corporation.
*       All rights reserved. 
*       This source code is only intended as a supplement to 
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the 
*       Microsoft samples programs.
\******************************************************************************/

#include "porttool.h"
#include "port.h"


/* define line types returned from GetNextLine */
#define VALID_LINE	 0
#define COMMENT_LINE	 1
#define EOF_LINE	 2

#define CARRIAGE_RETURN  13
#define LINE_FEED	 10

/* define worker functions for this module */
int  WINAPI GetNextLine (char *, int, char *, char *, BOOL *);
int  WINAPI NextLineLength (char *, char *, int);
BOOL WINAPI BkFilePortThread (LPBKPORTFILESTRUCT);
void WINAPI DateTimeStamp (char *);



/* function creates a background porting thread */
HANDLE WINAPI StartBkPortThread (LPBKPORTFILESTRUCT    lpBkPort)
{
    DWORD    id;

    /* create thread with initial structure */
    return (lpBkPort->hThread = CreateThread ((LPSECURITY_ATTRIBUTES)NULL,
				      4096,
				      (LPTHREAD_START_ROUTINE)BkFilePortThread,
				      (LPVOID)lpBkPort,
				      0,
				      &id));
}


/* independent thread function that performs background file porting */
BOOL WINAPI BkFilePortThread (
    LPBKPORTFILESTRUCT	  lpBkPort)
{
    HANDLE	hEvents[nBKPORTEVENTS];
    HANDLE	hFile;
    OFSTRUCT	of;
    DWORD	nFileSize;
    DWORD       nBytes;
    HANDLE	hFileBuffer;
    char	*lpFile, *lpFilePtr;
    WORD	wComplete, wIssues = 0;
    int 	nLines = 0;
    BOOL	bCommentOn;
    HANDLE	hLine;
    HANDLE	hToken, hIssue, hSuggest, hHelp;
    RESULT	rIssue;
    char	*lpLine;
    char	szHeader[MAX_PATH], szToken[50], szIssue[50], szdt[50],
		szSuggest[50], szHelp[50], szHelpFile[50], szEOL[50], szNL[5];


    /* adjust our priority to below normal */
    SetThreadPriority (GetCurrentThread (), THREAD_PRIORITY_BELOW_NORMAL);

    /* attach our thread input to the parent thread so we can post messages directly */
    AttachThreadInput (GetCurrentThreadId (),
		       GetWindowThreadProcessId (lpBkPort->hDlg, NULL),
		       TRUE);

    /* load file comment strings */
    LoadString (GetModuleHandle (NULL), IDS_BKPORTNEWLINE, szNL, 5);
    LoadString (GetModuleHandle (NULL), IDS_BKPORTHEADER, szHeader, MAX_PATH);
    LoadString (GetModuleHandle (NULL), IDS_BKPORTTOKEN, szToken, 50);
    LoadString (GetModuleHandle (NULL), IDS_BKPORTISSUE, szIssue, 50);
    LoadString (GetModuleHandle (NULL), IDS_BKPORTSUGGEST, szSuggest, 50);
    LoadString (GetModuleHandle (NULL), IDS_BKPORTHELP, szHelp, 50);
    LoadString (GetModuleHandle (NULL), IDS_BKPORTHELPFILE, szHelpFile, 50);
    LoadString (GetModuleHandle (NULL), IDS_BKPORTEOL, szEOL, 50);

    /* initialize wait events for communication between threads */
    if (!CreateEvents (hEvents, lpBkPort))
	return FALSE;

    /* open file for porting and read into buffer */
    if ((int)(hFile = (HANDLE)OpenFile (lpBkPort->szFilePath, &of, OF_READWRITE)) == -1)
	{
	DestroyEvents (hEvents);
	return FALSE;
	}

    /* global allocate buffer for file */
    if (!(hFileBuffer = GlobalAlloc (GPTR, (nFileSize = GetFileSize (hFile, NULL))+1)) ||
	!(lpFile = (char *)GlobalLock (hFileBuffer)))
	{
	CloseHandle (hFile);
	DestroyEvents (hEvents);
	return FALSE;
	}

    /* allocate initial line buffer of reasonable size */
    hLine = GlobalAlloc (GMEM_MOVEABLE, 1024);

    /* allocate local memory segments for porttool RESULT strings */
    if (!(rIssue.lpszToken = LocalLock (hToken = LocalAlloc (LHND, MAXTOKENLEN))) ||
	!(rIssue.lpszHelpStr = LocalLock (hHelp = LocalAlloc (LHND, MAXHELPLEN))) ||
	!(rIssue.lpszIssue = LocalLock (hIssue = LocalAlloc (LHND, MAXISSUELEN))) ||
	!(rIssue.lpszSuggest = LocalLock (hSuggest = LocalAlloc (LHND, MAXSUGGESTLEN))))
	{
	CloseHandle (hFile);
	GlobalUnlock (lpFile);
	GlobalFree (hFileBuffer);
	DestroyEvents (hEvents);
	GlobalFree (hLine);
	return FALSE;
	}

    /* read entire file into buffer and zero terminate */
    ReadFile (hFile, lpFile, nFileSize, &nBytes, NULL);
    lpFile[nFileSize] = 0;
    lpFilePtr = lpFile;

    /* if bytes read not equal to size of file, abort */
    if (nBytes != nFileSize)
	{
	CloseHandle (hFile);
	GlobalUnlock (lpFile);
	GlobalFree (hFileBuffer);
	DestroyEvents (hEvents);
	GlobalFree (hLine);
	return FALSE;
	}

    /* reset file to size zero before beginning porting */
    SetFilePointer (hFile, 0, NULL, FILE_BEGIN);
    SetEndOfFile (hFile);
    WriteFile (hFile, szHeader, strlen (szHeader), &nBytes, NULL);
    WriteFile (hFile, lpBkPort->szFile, strlen (lpBkPort->szFile), &nBytes, NULL);
    WriteFile (hFile, szEOL, strlen (szEOL), &nBytes, NULL);
    WriteFile (hFile, szNL, strlen (szNL), &nBytes, NULL);

    while (TRUE)
	{
	/* wait 1ms for either abort or status events to signal */
	switch (WaitForMultipleObjects (nBKPORTEVENTS, hEvents, FALSE, 1))
	    {
	    case BKPORT_ABORT:
		{
		char	szAbort[MAX_PATH];

		/* create time and date */
		DateTimeStamp (szdt);

		/* write header line */
		WriteFile (hFile, szHeader, strlen (szHeader), &nBytes, NULL);
		WriteFile (hFile, szdt, strlen (szdt), &nBytes, NULL);
		WriteFile (hFile, szEOL, strlen (szEOL), &nBytes, NULL);
		WriteFile (hFile, szNL, strlen (szNL), &nBytes, NULL);

		/* load abort string and write to file */
		LoadString (GetModuleHandle (NULL),
			    IDS_BKPORTABORT,
			    szAbort,
			    MAX_PATH);
		WriteFile (hFile, szAbort, strlen (szAbort), (LPDWORD)&nBytes, NULL);

		/* write rest of file to disk */
		WriteFile (hFile,
			   (VOID *)lpFilePtr,
			   (nFileSize - (lpFilePtr-lpFile)),
			   (LPDWORD)&nBytes,
			   NULL);

		/* clean up */
		CloseHandle (hFile);
		GlobalUnlock (lpFile);
		GlobalFree (hFileBuffer);
		GlobalFree (hLine);
		DestroyEvents (hEvents);

		/* free RESULT strings */
		LocalUnlock (hToken); LocalFree (hToken);
		LocalUnlock (hHelp); LocalFree (hHelp);
		LocalUnlock (hIssue); LocalFree (hIssue);
		LocalUnlock (hSuggest); LocalFree (hSuggest);

		/* exit thread */
		return FALSE;
		}
		break;

	    case BKPORT_STATUS:
		/* post message to parent thread with status info */
		PostMessage (lpBkPort->hDlg,
			     UM_STATUSUPDATE,
			     MAKELONG (wIssues, wComplete),
			     nLines);
		break;

	    case WAIT_TIMEOUT:
		/* if we timed out ignore */
		break;

	    default:
		/* anything else is an error */
		ErrorNotify (lpBkPort->hDlg, GetLastError ());
		goto DONE;
		break;
	    }

	/* reset line buffer */
	GlobalReAlloc (hLine,
		       NextLineLength (lpFilePtr, lpFile, nFileSize),
		       GMEM_MOVEABLE);
	lpLine = (char *)GlobalLock (hLine);
	*lpLine = 0;

	/* get next line from  file buffer */
	switch (GetNextLine (lpFile, nFileSize, lpFilePtr, lpLine, &bCommentOn))
	    {
	    /* check valid strings for porting issues */
	    case VALID_LINE:
		/* initialize rIssue string lengths */
		*(WORD *)rIssue.lpszToken = MAXTOKENLEN;
		*(WORD *)rIssue.lpszHelpStr = MAXHELPLEN;
		*(WORD *)rIssue.lpszIssue = MAXISSUELEN;
		*(WORD *)rIssue.lpszSuggest = MAXSUGGESTLEN;

		if (CheckString (lpLine, lpBkPort->dwPTFlags, &rIssue))
		    {
		    /* create time and date */
		    DateTimeStamp (szdt);

		    /* write header line */
		    WriteFile (hFile, szNL, strlen (szNL), &nBytes, NULL);
		    WriteFile (hFile, szHeader, strlen (szHeader), &nBytes, NULL);
		    WriteFile (hFile, szdt, strlen (szdt), &nBytes, NULL);
		    WriteFile (hFile, szEOL, strlen (szEOL), &nBytes, NULL);

		    /* write token line */
		    WriteFile (hFile, szToken, strlen (szToken), &nBytes, NULL);
		    WriteFile (hFile,
			       rIssue.lpszToken,
			       strlen (rIssue.lpszToken),
			       &nBytes,
			       NULL);
		    WriteFile (hFile, szEOL, strlen (szEOL), &nBytes, NULL);

		    /* write issue line */
		    WriteFile (hFile, szIssue, strlen (szIssue), &nBytes, NULL);
		    WriteFile (hFile,
			       rIssue.lpszIssue,
			       strlen (rIssue.lpszIssue),
			       &nBytes,
			       NULL);
		    WriteFile (hFile, szEOL, strlen (szEOL), &nBytes, NULL);

		    /* if suggestion */
		    if (*(rIssue.lpszSuggest))
			{
			WriteFile (hFile, szSuggest, strlen (szSuggest), &nBytes, NULL);
			WriteFile (hFile,
				   rIssue.lpszSuggest,
				   strlen (rIssue.lpszSuggest),
				   &nBytes,
				   NULL);
			WriteFile (hFile, szEOL, strlen (szEOL), &nBytes, NULL);
			}

		    /* if help string */
		    if (*(rIssue.lpszSuggest))
			{
			WriteFile (hFile, szHelp, strlen (szHelp), &nBytes, NULL);
			WriteFile (hFile,
				   rIssue.lpszHelpStr,
				   strlen (rIssue.lpszHelpStr),
				   &nBytes,
				   NULL);
			WriteFile (hFile, szHelpFile, strlen (szHelpFile), &nBytes, NULL);
			WriteFile (hFile, szEOL, strlen (szEOL), &nBytes, NULL);
			}

		    wIssues++;
		    }

	    case COMMENT_LINE:
		/* write line to file whether comment or not */
		WriteFile (hFile, lpLine, strlen (lpLine), &nBytes, NULL);
		break;

	    case EOF_LINE:
		if (*lpLine)
		    WriteFile (hFile, lpLine, strlen (lpLine), &nBytes, NULL);
		goto DONE;
		break;
	    }

	/* unlock line buffer */
	GlobalUnlock (hLine);

	/* update status counts */
	lpFilePtr += strlen (lpLine);
	nLines++;
	wComplete = (WORD)(((lpFilePtr-lpFile)*100)/nFileSize);
	}

DONE:
    /* clean up */
    CloseHandle (hFile);
    GlobalUnlock (lpFile);
    GlobalFree (hFileBuffer);
    GlobalFree (hLine);
    DestroyEvents (hEvents);

    /* free RESULT strings */
    LocalUnlock (hToken); LocalFree (hToken);
    LocalUnlock (hHelp); LocalFree (hHelp);
    LocalUnlock (hIssue); LocalFree (hIssue);
    LocalUnlock (hSuggest); LocalFree (hSuggest);

    /* send message to parent that thread is dead */
    PostMessage (lpBkPort->hDlg,
		 UM_THREADCOMPLETE,
		 (WPARAM)lpBkPort->hThread,
		 0);

    /* exit thread */
    return TRUE;
}



void WINAPI DateTimeStamp (
    char    *lpszDT)
{
    SYSTEMTIME	  dt;
    char	  Buff[10];

    /* create time and date stamp */
    GetSystemTime (&dt);

    //
    // On Japanese system change the date display order,
    //  we should do this right w/ locales eventually.
    //
    if (PRIMARYLANGID(GetUserDefaultLangID ()) == LANG_JAPANESE) {

      strcpy (lpszDT, itoa (dt.wYear, Buff, 10));
      strcat (lpszDT, "/");
      strcat (lpszDT, itoa (dt.wMonth, Buff, 10));
      strcat (lpszDT, "/");
      strcat (lpszDT, itoa (dt.wDay, Buff, 10));
    } else {
      strcpy (lpszDT, itoa (dt.wMonth, Buff, 10));
      strcat (lpszDT, "/");
      strcat (lpszDT, itoa (dt.wDay, Buff, 10));
      strcat (lpszDT, "/");
      strcat (lpszDT, itoa (dt.wYear, Buff, 10));
    }

    strcat (lpszDT, "    ");
    strcat (lpszDT, itoa (dt.wHour, Buff, 10));
    strcat (lpszDT, ":");
    strcat (lpszDT, itoa (dt.wMinute, Buff, 10));
}





BOOL WINAPI CreateEvents (
    HANDLE		  *lphEvents,
    LPBKPORTFILESTRUCT	  lpBkPort)
{
    char    szEvent[MAX_PATH];


    LoadString (GetModuleHandle (NULL), IDS_BKPORTABORT, szEvent, MAX_PATH);
    strcat (szEvent, lpBkPort->szFile);
    if (!(lphEvents[BKPORT_ABORT] = CreateEvent (NULL, TRUE, FALSE, szEvent)))
	return FALSE;

    LoadString (GetModuleHandle (NULL), IDS_BKPORTSTATUS, szEvent, MAX_PATH);
    strcat (szEvent, lpBkPort->szFile);
    if (!(lphEvents[BKPORT_STATUS] = CreateEvent (NULL, TRUE, FALSE, szEvent)))
	{
	CloseHandle (lphEvents[BKPORT_ABORT]);
	return FALSE;
	}

    /* return success */
    return TRUE;
}




void WINAPI DestroyEvents (
    HANDLE    *lphEvents)
{
    /* close event handles */
    CloseHandle (lphEvents[BKPORT_ABORT]);
    CloseHandle (lphEvents[BKPORT_STATUS]);
}




int WINAPI NextLineLength (
    char    *lpFilePtr,
    char    *lpFile,
    int     nFileSize)
{
    int    nCnt=0;
    char   *lpf = lpFilePtr;

    /* count all characters up to end of file or CR/LF sequence */
    while (lpf				 &&
	   lpf-lpFile < nFileSize	 &&
	   *lpf       != CARRIAGE_RETURN &&
	   *(lpf+1)   != LINE_FEED)
	{
	lpf++;
	nCnt++;
	}

    /* length plus 3 for CR/LF/0 terminator sequence */
    return nCnt + 3;
}




int WINAPI GetNextLine (
    char    *lpFile,
    int     nFileSize,
    char    *lpFilePtr,
    char    *lpLine,
    BOOL    *bCommentOn)
{
    char    *lpf = lpFilePtr;
    char    *lpl = lpLine;

    /* copy all characters up to end of file or CR/LF sequence */
    while (lpf				 &&
	   lpf-lpFile < nFileSize	 &&
	   *lpf       != CARRIAGE_RETURN &&
	   *(lpf+1)   != LINE_FEED)
	*lpl++ = *lpf++;

    /* check for end of buffer */
    if (lpf-lpFile >= nFileSize)
	return EOF_LINE;

    /* copy carriage return and line feed to line and terminate */
    *lpl++ = *lpf++;
    *lpl++ = *lpf++;
    *lpl = 0;

    /* increment lpl to first non space character in line */
    lpl = lpLine;
    while (*lpl == ' ')
	lpl++;

    /* see if single line comments exist */
    if (*lpl	 == '/' &&
	*(lpl+1) == '/')
	return COMMENT_LINE;

    /* see if comments begin */
    if (*lpl	 == '/'  &&
	*(lpl+1) == '*')
	*bCommentOn = TRUE;

    /* if comment on, see if it terminates yet */
    if (*bCommentOn)
	{
	lpl = lpLine;
	while (*lpl)
	    {
	    if (*lpl	 == '*'  &&
		*(lpl+1) == '/')
		{
		*bCommentOn = FALSE;
		break;
		}
	    lpl = CharNext(lpl);
	    }

	/* if more text on line, valid line */
	while (*lpl)
	    if (*lpl != '*'	 &&
		*(lpl+1) != '/')
		return VALID_LINE;
	    else
		return COMMENT_LINE;
	}

    /* if haven't returned yet, must be valid line */
    return VALID_LINE;
}
