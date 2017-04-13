/*
 -  X P L O G G E R . C
 -
 *  Purpose:
 *      Code to support the Log File for the Sample Transport Provider.
 *
 *  Copyright 1992-1995 Microsoft Corporation.  All Rights Reserved.
 */

#include "xppch.h"

static HANDLE hLogHandle = INVALID_HANDLE_VALUE;
static DWORD dwLogLowWater = 0;
static DWORD dwLogHiWater = (DWORD) -1;
static TCHAR chLogFileName[MAX_PATH];

#define BUFSIZE 255             /* Size of buffer to use for LogPrintf */
static TCHAR _xpbuf[BUFSIZE];


/*
 -  InitTransportLog
 -
 *  Purpose:
 *      Called by TransportLogon() logic to start logging.
 *
 *  Parameters:
 *      lpxpl               Session object. We'll need it
 *                          to get the logfile name and
 *                          size constraints.
 *      ulFlags             Flags. Not used at present.
 *
 *  Returns:
 *      hLogHandle          Handle of open Log File.
 *      dwLogLowWater       "Low Water Mark" of Log File.
 *      dwLogHiWater        "High Water Mark" of Log File.
 *      chLogFileName       Filename of open Log File.
 *
 *  Operation:
 *      If a file is already open, this transport session doesn't want to log
 *      events, or the filename given is null, return to caller.  Open the 
 *      file and save the filename into chLogFileName. Store water marks into 
 *      the appropriate variables. Save the handle.  We grab the Critical
 *      Section here because it is possible to Init the logging at times
 *      other than TransportLogon.  This makes it necessary to protect this
 *      section of code.
 */

void
InitTransportLog(LPXPL lpxpl, ULONG ulFlags)
{
    LPSPropValue lpPropArray = lpxpl->lpPropArray;
    ULONG ulSessFlags;
    LPTSTR lpszFileName;
    HANDLE hTempHandle;
    DWORD dwOffset;
    ULONG ulLow, ulHigh;

    /*  Use the critical section here */

    EnterCriticalSection(&(lpxpl->lpxppParent->csTransport));

    /*  Are we already logging? If so there's nothing to do here. */

    if (hLogHandle != INVALID_HANDLE_VALUE)
    {
        DebugTrace("Already logging to %s\n", chLogFileName);
        goto ret;
    }

    /*  Logging isn't on. Would this session like it turned on? */

    ulSessFlags = (ArrayIndex(PR_SAMPLE_FLAGS, lpPropArray)).Value.ul;
    if (!(ulSessFlags & PR_SAMPLE_FLAG_LOG_EVENTS))
    {
        DebugTrace("Log flag isn't on, logfile won't be opened\n");
        goto ret;
    }

    /*  We're going to log if we can. Get the filename and see if it
        makes any sense. If so, try to open it. */

    lpszFileName = (ArrayIndex(PR_SAMPLE_LOGFILE, lpPropArray)).Value.LPSZ;
    if (!lpszFileName || !*lpszFileName)
    {
        DebugTrace("LogFile name wasn't given, logfile won't be opened\n");
        goto ret;
    }

    hTempHandle = CreateFile(lpszFileName,
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ,
        NULL,
        OPEN_ALWAYS,
        FILE_FLAG_WRITE_THROUGH | FILE_FLAG_RANDOM_ACCESS,
        NULL);

    if (hTempHandle == INVALID_HANDLE_VALUE)
    {
        DebugTrace("Error %x opening logfile\n", GetLastError());
        goto ret;
    }

    /*  The log file is open. Seek to the end so we can resume logging. */

    dwOffset = SetFilePointer(hTempHandle, 0L, NULL, FILE_END);
    if (dwOffset == -1)
    {
        DebugTrace("Error %x seeking to end of logfile\n", GetLastError());
        CloseHandle(hTempHandle);
        goto ret;
    }

    /*  Get the relevant data into the local structures. */

    lstrcpy(chLogFileName, lpszFileName);
    hLogHandle = hTempHandle;

    ulLow = (ArrayIndex(PR_SAMPLE_LOGLOWWATER, lpPropArray)).Value.ul;
    ulHigh = (ArrayIndex(PR_SAMPLE_LOGHIGHWATER, lpPropArray)).Value.ul;
    if (ulHigh)
    {
        dwLogHiWater = ulHigh * 1024;
        dwLogLowWater = ulLow * 1024;
    }

ret:

    /*  Release the critical section */

    LeaveCriticalSection(&(lpxpl->lpxppParent->csTransport));

    return;
}


/*
 -  DeInitTransportLog
 -
 *  Purpose:
 *      Called by DeinitTransport() to turn off all session logging.
 *
 *  Parameters:
 *      ulFlags             Flags. Not used at present.
 *
 *  Returns:
 *      none.
 *
 *  Operation:
 *      If we have a file open, try to close it. Reinitialize structures
 *      whether we succeeded or not.
 */

void
DeInitTransportLog(ULONG ulFlags)
{
    if (hLogHandle != INVALID_HANDLE_VALUE)
    {
        if (!CloseHandle(hLogHandle))
            DebugTrace("Unable to close logfile %s\n", chLogFileName);

        hLogHandle = INVALID_HANDLE_VALUE;
        dwLogHiWater = (DWORD) -1L;
        dwLogLowWater = 0;
        *chLogFileName = '\0';
    }
}


/*
 -  PrintfTransportLog
 -
 *  Purpose:
 *      Called by various parts of the Transport to log information (if
 *      logging is currently active).
 *
 *  Parameters:
 *      fmt                 Start of variable argument list.
 *
 *  Returns:
 *      none.
 *
 *  Operation:
 *      Format the input data and call PutsTransportLog to write to logfile.
 *      Current maximum length permitted is 255 characters (and is NOT
 *      protected!).
 */

void __cdecl
PrintfTransportLog(LPTSTR fmt,...)
{
    va_list marker;

    va_start(marker, fmt);

    if (hLogHandle != INVALID_HANDLE_VALUE)
    {
        if (wvsprintf((LPTSTR) _xpbuf, fmt, marker))
            PutsTransportLog((LPTSTR) _xpbuf);
    }

    va_end(marker);
}


/*
 -  PutsTransportLog
 -
 *  Purpose:
 *      Called mostly by PrintfTransportLog. Writes a single line to the
 *      logfile if it's open.
 *
 *  Parameters:
 *      str                 String that wants to be written.
 *
 *  Returns:
 *      none.
 *
 *  Operation:
 *      If we have set a high water mark, get the current logfile size. If it
 *      exceeds the high water mark, move back by the amount of the low water
 *      mark, find a line ending, read everything to the end, write to the
 *      front of the file, and truncate to that location.
 *
 *      Create a line consisting of the date and time, the input string, and
 *      line ending characters. Write this line to the logfile.
 */

void
PutsTransportLog(LPTSTR str)
{
    DWORD cWritten;
    SYSTEMTIME stOurTime;
    TCHAR tchData[512];
    HGLOBAL hGlobal = (HGLOBAL) 0L;
    LPVOID lpvBuf = NULL;

    if (hLogHandle == INVALID_HANDLE_VALUE)
        return;

    /*  See if we want to be adjusting the file size. */

    if (dwLogHiWater != -1)
    {
        DWORD finfo;

        /*  Get the current file size */

        finfo = GetFileSize(hLogHandle, NULL);

        if (finfo == 0xFFFFFFFF)
        {
            DebugTrace("Error %x getting logfile info\n", GetLastError());
            DeInitTransportLog(LOG_DEINIT_HURRY);
            return;
        }

        /*  Is it time to trim back? If so, let's do it. */

        if (finfo > dwLogHiWater)
        {
            DWORD dwOffset;
            ULONG ulT, ulLowWater;
            char *lpbT;

            /*  Allocate a buffer to read dwLogLowWater bytes. If
                dwLogLowWater > 32K, use 32K. */

            ulLowWater = (dwLogLowWater > 32000L ? 32000L : dwLogLowWater);
            if (ulLowWater == 0L)
                goto Truncate;

            hGlobal = GlobalAlloc(GPTR, (UINT) ulLowWater);
            if (hGlobal == NULL)
            {
                DebugTrace("Attempt to GlobalAlloc %l bytes for lowwater buffer failed\n", ulLowWater);
                goto Truncate;
            }

            lpvBuf = (LPVOID) GlobalLock(hGlobal);
            if (lpvBuf == NULL)
            {
                DebugTrace("Attempt to Lock allocated memory buffer failed\n");
                goto Truncate;
            }

            /*  Reposition the pointer back by the size of ulLowWater. */

            dwOffset = SetFilePointer(hLogHandle, 0L - ulLowWater, NULL, FILE_CURRENT);
            if (dwOffset == -1)
            {
                DebugTrace("Error %x seeking to low water mark\n", GetLastError());
                DeInitTransportLog(LOG_DEINIT_HURRY);
                return;
            }

            /*  Read (ulLowWater) bytes from that position. */

            if (!ReadFile(hLogHandle, lpvBuf, ulLowWater, &cWritten, NULL))
            {
                DebugTrace("Attempt to read %l bytes for low water copy failed, error = %lx\n", ulLowWater, GetLastError());
                goto Truncate;
            }

            Assert(cWritten == ulLowWater);

            /*  Find the first newline from that point */

            for (ulT = 0, lpbT = (char *)lpvBuf; ulT < ulLowWater; lpbT++, ulT++)
            {
                if (*lpbT == '\n')
                    break;
            }

            /* Did the search fail? If so, truncate the file to zero. */

            if (ulT == ulLowWater)
            {
                ulLowWater = 0L;
Truncate:
                /*  We failed for some reason. Deallocate the buffer if
                    any and truncate the file to ulLowWater. */

                if (lpvBuf)
                    GlobalUnlock(hGlobal);
                if (hGlobal)
                    (void)GlobalFree(hGlobal);

                dwOffset = SetFilePointer(hLogHandle, ulLowWater, NULL, FILE_BEGIN);
                if (dwOffset == -1)
                {
                    DebugTrace("Error %x seeking to low water mark\n", GetLastError());
                    DeInitTransportLog(LOG_DEINIT_HURRY);
                    return;
                }
                goto Adjusted;
            }

            /*  We found a newline. Skip over it and write the remaining
                data from the file start, if any. */

            ulT++;
            lpbT++;

            dwOffset = SetFilePointer(hLogHandle, 0L, NULL, FILE_BEGIN);
            if (dwOffset == -1)
            {
                if (lpvBuf)
                    GlobalUnlock(hGlobal);
                if (hGlobal)
                    (void)GlobalFree(hGlobal);

                DebugTrace("Error %x seeking to file start\n", GetLastError());
                DeInitTransportLog(LOG_DEINIT_HURRY);
                return;
            }

            if (ulT < ulLowWater)
            {
                cWritten = 0;
                WriteFile(hLogHandle, (LPVOID) lpbT, (DWORD) (ulLowWater - ulT), &cWritten, NULL);
                Assert((cWritten + ulT) == ulLowWater);
            }

            GlobalUnlock(hGlobal);
            GlobalFree(hGlobal);

Adjusted:
            if (!SetEndOfFile(hLogHandle))
            {
                DebugTrace("Error %x setting EOF\n", GetLastError());
                DeInitTransportLog(LOG_DEINIT_HURRY);
                return;
            }
        }
    }

    /* We can't handle more than 490 characters on a input line. */

    Assert(lstrlen(str) < 490L);

    GetLocalTime(&stOurTime);
    wsprintf(tchData, TEXT("%04d/%02d/%02d %02d:%02d:%02d %s\r\n"),
        stOurTime.wYear, stOurTime.wMonth, stOurTime.wDay,
        stOurTime.wHour, stOurTime.wMinute, stOurTime.wSecond,
        str);

    WriteFile(hLogHandle, tchData, (DWORD) (lstrlen(tchData) * sizeof(TCHAR)), &cWritten, NULL);
}
