/*++

Copyright 1996-1997 Microsoft Corporation

Module Name:

    comm.c

Abstract:

    Implements a set of common operations for socket communication

Revision History:

--*/

#include <windows.h>
#include <winsock.h>
#include <stdio.h>
#include <stdlib.h>
#include "comm.h"

BOOL InitWinsock ()
{
	int nRes;
	WSADATA wsaData;
	WORD wVerRequested = 0x0101; // ver 1.1

	// Init the sockets interface
	nRes = WSAStartup (wVerRequested, &wsaData);
	if (nRes)  {
		fprintf (stderr, "Couldn't init winsock: %d\n", nRes);
		return(FALSE);
	}

	return(TRUE);
}

BOOL TermWinsock ()
{
	if (SOCKET_ERROR == WSACleanup ())
		return(FALSE);
	else
		return(TRUE);
}

BOOL SendMsg (SOCKET s, PBYTE pBuf, DWORD cbBuf)
/*++

 Routine Description:

    Sends a message over the socket by first sending a DWORD that
	represents the size of the message followed by the message itself.

 Return Value:

    Returns TRUE is successful; otherwise FALSE is returned.

--*/
{
	if (0 == cbBuf)
		return(TRUE);

	// send the size of the message
	//
	if (!SendBytes (s, (PBYTE)&cbBuf, sizeof (cbBuf)))
		return(FALSE);
	
	// send the body of the message
	//
	if (!SendBytes (s, pBuf, cbBuf))
		return(FALSE);

	return(TRUE);
}	

BOOL ReceiveMsg (SOCKET s, PBYTE pBuf, DWORD cbBuf, DWORD *pcbRead)
/*++

 Routine Description:

    Receives a message over the socket.  The first DWORD in the message
	will be the message size.  The remainder of the bytes will be the
	actual message.

 Return Value:

    Returns TRUE is successful; otherwise FALSE is returned.

--*/
{
	DWORD cbRead;
	DWORD cbData;

	// find out how much data is in the message
	//	
	if (!ReceiveBytes (s, (PBYTE)&cbData, sizeof (cbData), &cbRead))
		return(FALSE);
	
	if (sizeof (cbData) != cbRead)
		return(FALSE);
	
	// Read the full message
	//
	if (!ReceiveBytes (s, pBuf, cbData, &cbRead))
		return(FALSE);
	
	if (cbRead != cbData)
		return(FALSE);

	*pcbRead = cbRead;

	return(TRUE);
}	

BOOL SendBytes (SOCKET s, PBYTE pBuf, DWORD cbBuf)
{
	PBYTE pTemp = pBuf;
	int cbSent, cbRemaining = cbBuf;

	if (0 == cbBuf)
		return(TRUE);
		
	while (cbRemaining) {
		cbSent = send (s, pTemp, cbRemaining, 0);
		if (SOCKET_ERROR == cbSent) {
			fprintf (stderr, "send failed: %u\n", GetLastError ());
			return FALSE;
		}

		pTemp += cbSent;
		cbRemaining -= cbSent;
	}

	return TRUE;
}

BOOL ReceiveBytes (SOCKET s, PBYTE pBuf, DWORD cbBuf, DWORD *pcbRead)
{
	PBYTE pTemp = pBuf;
	int cbRead, cbRemaining = cbBuf;

	while (cbRemaining) {
		cbRead = recv (s, pTemp, cbRemaining, 0);
		if (0 == cbRead)
			break;

		if (SOCKET_ERROR == cbRead) {
			fprintf (stderr, "recv failed: %u\n", GetLastError ());
			return FALSE;
		}

		cbRemaining -= cbRead;
		pTemp += cbRead;
	}

	*pcbRead = cbBuf - cbRemaining;

	return TRUE;
}

