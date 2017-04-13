/*++

Copyright 1996-1997 Microsoft Corporation

Module Name:

    server.c

Abstract:

    A command line app that establishes an authenticated connection
	with a client.

Revision History:

--*/

#include <windows.h>
#include <winsock.h>
#include <stdio.h>
#include <stdlib.h>
#include "security.h"
#include "comm.h"

BOOL AcceptAuthSocket (SOCKET *s);
BOOL CloseAuthSocket (SOCKET s);
BOOL DoAuthentication (SOCKET s);

static PBYTE g_pInBuf = NULL;
static PBYTE g_pOutBuf = NULL;
static DWORD g_cbMaxMessage = 0;
static unsigned short g_usPort = 2000;

void main ()
{
	char szUser[80];
	DWORD cbUser = 80;
	SOCKET s;

	// initialize
	//
	if (!InitWinsock ())
		exit (EXIT_FAILURE);

	if (!InitPackage (&g_cbMaxMessage))
		exit (EXIT_FAILURE);

	g_pInBuf = (PBYTE) malloc (g_cbMaxMessage);
	g_pOutBuf = (PBYTE) malloc (g_cbMaxMessage);
	if (NULL == g_pInBuf || NULL == g_pOutBuf)
		exit (EXIT_FAILURE);

	// Make an authenticated connection with client
	//
	if (!AcceptAuthSocket (&s))
		exit (EXIT_FAILURE);

	// impersonate the client
	//
	if (!ImpersonateContext (s))
		exit (EXIT_FAILURE);

	// get the user name
	//
	if (!GetUserName (szUser, &cbUser))
		exit (EXIT_FAILURE);

	// revert to self
	//
	if (!RevertContext (s))
		exit (EXIT_FAILURE);

	// send user name to client
	//
	if (!SendBytes (s, szUser, cbUser))
		exit (EXIT_FAILURE);

	// terminate and cleanup
	//
	CloseAuthSocket (s);

	TermPackage ();

	TermWinsock ();

	free (g_pInBuf);
	free (g_pOutBuf);

	exit (EXIT_SUCCESS);
}

BOOL AcceptAuthSocket (SOCKET *s)
/*++

 Routine Description:

    Establishes an authenticated socket connection with a client and
	initializes any needed security package resources.

 Return Value:

    Returns TRUE is successful; otherwise FALSE is returned.

--*/
{
	SOCKET sockListen;
	SOCKET sockClient;
	SOCKADDR_IN sin;
	int nRes;

	// create listening socket
	//
	sockListen = socket (PF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == sockListen)  {
		fprintf (stderr, "Failed to create socket: %u\n", GetLastError ());
		return(FALSE);
	}

	// bind to local port
	//
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = 0;
    sin.sin_port = htons(g_usPort);
	nRes = bind (sockListen, (LPSOCKADDR) &sin, sizeof (sin));
	if (SOCKET_ERROR == nRes)  {
		fprintf (stderr, "bind failed: %u\n", GetLastError ());
		return(FALSE);
	}

	// listen for client
	//
	nRes = listen (sockListen, 1);
	if (SOCKET_ERROR == nRes)  {
		fprintf (stderr, "listen failed: %u\n", GetLastError ());
		return(FALSE);
	}

	// accept client
	//
	sockClient = accept (sockListen, NULL, NULL);
	if (INVALID_SOCKET == sockClient)  {
		fprintf (stderr, "accept failed: %u\n", GetLastError ());
		return(FALSE);
	}

	closesocket (sockListen);

	if (!InitSession (sockClient))
		return(FALSE);

	if (!DoAuthentication (sockClient))
		return(FALSE);

	// return socket
	//
	*s = sockClient;

	return(TRUE);
}	

BOOL CloseAuthSocket (SOCKET s)
/*++

 Routine Description:

    Closes a socket and releases security resources associated with
	the socket

 Return Value:

    Returns TRUE is successful; otherwise FALSE is returned.

--*/
{
	TermSession (s);
	shutdown (s, 2);
	closesocket (s);
	return(TRUE);
}	

BOOL DoAuthentication (SOCKET s)
/*++

 Routine Description:

    Manges the authentication conversation with the client via the
    supplied socket handle.

 Return Value:

    Returns TRUE is successful; otherwise FALSE is returned.

--*/
{
	DWORD cbIn, cbOut;
	BOOL done = FALSE;
	
	do {
		if (!ReceiveMsg (s, g_pInBuf, g_cbMaxMessage, &cbIn))
			return(FALSE);
		
		cbOut = g_cbMaxMessage;
		if (!GenServerContext (s, g_pInBuf, cbIn, g_pOutBuf, &cbOut, &done))
			return(FALSE);
		
		if (!SendMsg (s, g_pOutBuf, cbOut))
			return(FALSE);
	}
	while(!done);

	return(TRUE);
}	
