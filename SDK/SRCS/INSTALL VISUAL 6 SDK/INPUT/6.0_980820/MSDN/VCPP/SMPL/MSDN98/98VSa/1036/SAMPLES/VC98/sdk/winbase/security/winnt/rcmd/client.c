/*++

Copyright 1996 - 1997 Microsoft Corporation

Module Name:

    client.c

Abstract:

    This sample illustrates a simple client side of the DuplicateTokenEx()
    server sample.

    This client functions correctly on the following platforms:
    Windows NT 3.5
    Windows NT 3.51
    Windows NT 4.0
    Windows 95

Author:

    Scott Field (sfield)    02-Apr-96

--*/

#include <windows.h>
#include <stdio.h>

DWORD
WINAPI
ReadFunc(
    LPVOID lpParam
    );

DWORD
WINAPI
WriteFunc(
    LPVOID lpParam
    );

void
DisplayWinError(
    LPSTR szAPI,    // pointer to Ansi function name
    DWORD dwError   // DWORD WinError
    );

#define RTN_OK 0
#define RTN_USAGE 1
#define RTN_ERROR 13

int
__cdecl
main(
    int argc,
    char *argv[]
    )
{
    HANDLE hFileRead;
    HANDLE hFileWrite;

    HANDLE hThread;
    DWORD dwThreadId;

    CHAR PipeIn[255];
    CHAR PipeOut[255];

    if(argc == 1) {
        printf("Usage: %s <\\\\server\n", argv[0]);
        printf("  %s \\\\WINBASE (remote server is \\\\winbase)\n", argv[0]);
        printf("  %s \\\\. (local server)\n",   argv[0]);
        return RTN_USAGE;
    }

    //
    // build Pipe names
    //
    wsprintf(PipeIn, "%s\\pipe\\rcmd_out", argv[1]);
    wsprintf(PipeOut, "%s\\pipe\\rcmd_in", argv[1]);

    //
    // wait for the outbound (inbound on server-side) pipe to be available
    //
    WaitNamedPipe(PipeOut, NMPWAIT_WAIT_FOREVER);

    hFileWrite = CreateFile(
        PipeOut,
        GENERIC_WRITE,
        0, // exclusive open
        NULL,
        OPEN_EXISTING,
        SECURITY_SQOS_PRESENT | SECURITY_IMPERSONATION, // server can impersonate
        NULL
        );

    if(hFileWrite == INVALID_HANDLE_VALUE) {
        DisplayWinError("CreateFile", GetLastError());
        return RTN_ERROR;
    }

    //
    // wait for the inbound (outbound on server-side) pipe to be available
    // we time-out in 5 seconds because the server should be ready for us
    // right-away
    //
    WaitNamedPipe(PipeIn, 5 * 1000);

    hFileRead = CreateFile(
        PipeIn,
        GENERIC_READ,
        0, // exclusive open
        NULL,
        OPEN_EXISTING,
        0,
        NULL
        );

    if(hFileRead == INVALID_HANDLE_VALUE) {
        DisplayWinError("CreateFile", GetLastError());
        return RTN_ERROR;
    }

    //
    // start a thread to handle stdin redirection to the pipe
    //
    hThread = CreateThread(
        NULL,
        0,
        WriteFunc,
        (LPVOID)hFileWrite, // parm
        0,
        &dwThreadId
        );

    if(hThread == NULL) {
        DisplayWinError("CreateThread", GetLastError());
        return RTN_ERROR;
    }

    //
    // handle stdout redirection
    //
    ReadFunc((LPVOID)hFileRead);

    //
    // if the read returned, kill the write, cleanup, and then exit
    //
    TerminateThread(hThread, 0xFFFFFFFF);
    CloseHandle(hThread);

    CloseHandle(hFileRead);
    CloseHandle(hFileWrite);

    return RTN_OK;
}

DWORD
WINAPI
ReadFunc(
    LPVOID lpParam
    )
{
    #define BUFFER_SIZE 4096

    HANDLE hFile = (HANDLE)lpParam;
    BYTE lpBuffer[BUFFER_SIZE];

    DWORD dwBytesRead;
    DWORD dwBytesWritten;

    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    DWORD dwLastError;

    while (1) {
        if(!ReadFile(
            hFile,
            lpBuffer,
            BUFFER_SIZE,
            &dwBytesRead,
            NULL
            )) {
            dwLastError = GetLastError();

            if(dwLastError == ERROR_NO_DATA) continue;
            if(dwLastError != ERROR_MORE_DATA) break;
        }

        if(!WriteFile(
            hStdOut,
            lpBuffer,
            dwBytesRead,
            &dwBytesWritten,
            NULL
            )) break;
    }

    return GetLastError();
}

DWORD
WINAPI
WriteFunc(
    LPVOID lpParam
    )
{
    HANDLE hPipe = (HANDLE)lpParam;

    BYTE lpBuffer[ 1 ]; // change this later

    DWORD dwBytesRead;
    DWORD dwBytesWritten;

    HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);

    while (1) {
        //
        // TODO rework this loop to be line-based.
        // this would entail doing the console buffering outselves.
        //
        if(!ReadFile(
            hStdIn,
            lpBuffer,
            1,
            &dwBytesRead,
            NULL
            )) break;

        if(!WriteFile(
            hPipe,
            lpBuffer,
            dwBytesRead,
            &dwBytesWritten,
            NULL
            )) break;
    }

    return GetLastError();
}

void
DisplayWinError(
    LPSTR szAPI,    // pointer to Ansi function name
    DWORD dwError   // DWORD WinError
    )
{
    LPSTR MessageBuffer;
    DWORD dwBufferLength;

    //
    // TODO get this fprintf out of here!
    //
    fprintf(stderr,"%s error!\n", szAPI);

    if(dwBufferLength=FormatMessageA(
            FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_FROM_SYSTEM,
            NULL,
            dwError,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPSTR) &MessageBuffer,
            0,
            NULL
            ))
    {
        DWORD dwBytesWritten; // unused

        //
        // Output message string on stderr
        //
        WriteFile(
                GetStdHandle(STD_ERROR_HANDLE),
                MessageBuffer,
                dwBufferLength,
                &dwBytesWritten,
                NULL
                );

        //
        // free the buffer allocated by the system
        //
        LocalFree(MessageBuffer);
    }
}
