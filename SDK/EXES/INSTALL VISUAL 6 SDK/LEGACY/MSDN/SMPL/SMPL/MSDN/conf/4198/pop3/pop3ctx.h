//+---------------------------------------------------------------------------
//
//  Microsoft Windows
//  Copyright (C) Microsoft Corporation, 1992 - 1993.
//
//  File:       pop3ctx.h
//
//  Contents:
//
//  Classes:
//
//  Functions:
//
//  History:    1-06-95   RichardW   Created
//
//----------------------------------------------------------------------------

#ifndef __POP3CTX_H__
#define __POP3CTX_H__

#define POP3_MESSAGE_DELETE     0x00000001  // Message has been "deleted"

typedef enum _LAST_CLIENT_IO {
    ClientIoRead,
    ClientIoWrite,
    ClientIoTransmitFile
} LAST_CLIENT_IO, *PLAST_CLIENT_IO;

typedef struct _CLIENT_CONTEXT {
    SOCKET Socket;
    PVOID Context;
    LAST_CLIENT_IO LastClientIo;
    DWORD BytesReadSoFar;
    HANDLE TransmittedFile;
    HANDLE TransmittedBuffer;
    OVERLAPPED Overlapped;
    CHAR Buffer[8192];
} CLIENT_CONTEXT, *PCLIENT_CONTEXT;

typedef struct _PopMessageHeader {
    DWORD       Flags;                  // Flags about this message
    DWORD       Size;                   // Size of this message
    PWSTR       pszFileName;            // File name containing message
} PopMessageHeader, * PPopMessageHeader;

typedef struct _PopMailDirectory {
    DWORD               Flags;          // Flags about this directory
    DWORD               cMessages;      // Number of messages
    DWORD               NextMessage;    // Next message number
    DWORD               TotalSize;      // Total size of directory, in bytes
    DWORD               cAvailMessages; // Number of messages not deleted
    DWORD               AvailSize;      // Size of available messages
    PWSTR               pBaseDir;       // Base directory
    PPopMessageHeader   Messages;       // Array of message headers
} PopMailDirectory, * PPopMailDirectory;

typedef enum _PopState {
    PopNegotiate,
    PopAuthorization,                   // Authorization State (wait for USER)
    PopAuthorization2,                  // Waiting for PASS
    PopTransact,                        // Transact State
    PopUpdate,                          // Update state
    PopShutdown                         // Rundown state
} PopState, * PPopState;


#define USERNAME_LENGTH 32
typedef struct _PopContext {
    PopState            State;          // State of the connection
    HANDLE              hUserToken;     // Token for impersonation
    HANDLE              hDirectoryLock; // Lock for directory
    DWORD               LastError;      // Last error occurred
    DWORD               RetryCount;     // Number of retries
    PPopMailDirectory   pDirectory;     // Directory for retrieval
    CHAR                UserName[USERNAME_LENGTH];   // User Name for auth
} PopContext, * PPopContext;

typedef enum _Pop3Disposition {
    Pop3_Discard,                       // Discard the request
    Pop3_SendError,                     // Send the error string
    Pop3_SendBuffer,                    // Send the buffer returned
    Pop3_SendFile,                      // Send the File returned
    Pop3_SendBufferThenFile,            // Send the buffer, then the file
    Pop3_SendFileThenBuffer             // Send the file, then the buffer
} Pop3Disposition;

typedef Pop3Disposition
(* Pop3DispatchFn)(
    PPopContext pContext,               // Client's connection context
    PUCHAR      InputBuffer,            // Buffer sent from client
    DWORD       InputBufferLen,         // Size of buffer
    PHANDLE     SendHandle,             // Handle of file to send
    PUCHAR *    OutputBuffer,           // Output buffer to send
    PDWORD      OutputBufferLen         // Size of output buffer
    );

Pop3Disposition
HeloDispatch(
    PPopContext pContext,
    PUCHAR      InputBuffer,
    DWORD       InputBufferLen,
    PHANDLE     SendHandle,
    PUCHAR *    OutputBuffer,
    PDWORD      OutputBufferLen
    );

Pop3Disposition
UserDispatch(
    PPopContext pContext,
    PUCHAR      InputBuffer,
    DWORD       InputBufferLen,
    PHANDLE     SendHandle,
    PUCHAR *    OutputBuffer,
    PDWORD      OutputBufferLen
    );

Pop3Disposition
PassDispatch(
    PPopContext pContext,
    PUCHAR      InputBuffer,
    DWORD       InputBufferLen,
    PHANDLE     SendHandle,
    PUCHAR *    OutputBuffer,
    PDWORD      OutputBufferLen
    );

Pop3Disposition
QuitDispatch(
    PPopContext pContext,
    PUCHAR      InputBuffer,
    DWORD       InputBufferLen,
    PHANDLE     SendHandle,
    PUCHAR *    OutputBuffer,
    PDWORD      OutputBufferLen
    );

Pop3Disposition
StatDispatch(
    PPopContext pContext,
    PUCHAR      InputBuffer,
    DWORD       InputBufferLen,
    PHANDLE     SendHandle,
    PUCHAR *    OutputBuffer,
    PDWORD      OutputBufferLen
    );

Pop3Disposition
ListDispatch(
    PPopContext pContext,
    PUCHAR      InputBuffer,
    DWORD       InputBufferLen,
    PHANDLE     SendHandle,
    PUCHAR *    OutputBuffer,
    PDWORD      OutputBufferLen
    );

Pop3Disposition
RetrDispatch(
    PPopContext pContext,
    PUCHAR      InputBuffer,
    DWORD       InputBufferLen,
    PHANDLE     SendHandle,
    PUCHAR *    OutputBuffer,
    PDWORD      OutputBufferLen
    );

Pop3Disposition
DeleDispatch(
    PPopContext pContext,
    PUCHAR      InputBuffer,
    DWORD       InputBufferLen,
    PHANDLE     SendHandle,
    PUCHAR *    OutputBuffer,
    PDWORD      OutputBufferLen
    );

Pop3Disposition
LastDispatch(
    PPopContext pContext,
    PUCHAR      InputBuffer,
    DWORD       InputBufferLen,
    PHANDLE     SendHandle,
    PUCHAR *    OutputBuffer,
    PDWORD      OutputBufferLen
    );

Pop3Disposition
RsetDispatch(
    PPopContext pContext,
    PUCHAR      InputBuffer,
    DWORD       InputBufferLen,
    PHANDLE     SendHandle,
    PUCHAR *    OutputBuffer,
    PDWORD      OutputBufferLen
    );


#endif
