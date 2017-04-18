/*++

Copyright 1996-1997 Microsoft Corporation

Module Name:

    comm.h

Abstract:

    Some common functions for sockets

Revision History:

--*/

BOOL InitWinsock ();
BOOL TermWinsock ();
BOOL SendMsg (SOCKET s, PBYTE pBuf, DWORD cbBuf);
BOOL ReceiveMsg (SOCKET s, PBYTE pBuf, DWORD cbBuf, DWORD *pcbRead);
BOOL SendBytes (SOCKET s, PBYTE pBuf, DWORD cbBuf);
BOOL ReceiveBytes (SOCKET s, PBYTE pBuf, DWORD cbBuf, DWORD *pcbRead);

