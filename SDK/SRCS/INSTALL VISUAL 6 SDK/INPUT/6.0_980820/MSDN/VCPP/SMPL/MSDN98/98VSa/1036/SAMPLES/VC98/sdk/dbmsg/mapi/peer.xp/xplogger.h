/*
 -  X P L O G G E R . H
 -
 *  Purpose:
 *      Logfile definitions for Sample Transport Provider.
 *
 *  Copyright 1992-1995 Microsoft Corporation.  All Rights Reserved.
 */

/* Start up the logging function if indicated and not already
   started on another session. Called at logon time. */

void InitTransportLog (LPXPL lpSession, ULONG ulFlags);

/* Shut down the logging function if started. Called at
   Deinit time. */

void DeInitTransportLog (ULONG ulFlags);

/* One flag value is defined -- a "do it quickly" bit. */

#define LOG_DEINIT_HURRY (ULONG)(0x00000001)

/* Log a formatted line. Always called; determination of
   whether the file is open happens at the lower level. */

void __cdecl PrintfTransportLog (LPTSTR fmt,...);

/* Log a line of text. Always called. */

void PutsTransportLog (LPTSTR str);
