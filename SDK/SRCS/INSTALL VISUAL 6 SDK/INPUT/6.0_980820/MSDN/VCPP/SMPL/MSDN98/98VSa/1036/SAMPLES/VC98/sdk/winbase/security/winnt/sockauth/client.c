/*++

Copyright 1996-1997 Microsoft Corporation

Module Name:

    client.c

Abstract:

    A command line app that establishes an authenticated connection
	with a server.

Revision History:

--*/

#include <windows.h>
#include <winsock.h>
#include <stdio.h>
#include <stdlib.h>
#include "security.h"
#include "comm.h"

BOOL ConnectAuthSocket (LPCSTR szServer, SOCKET *s);
BOOL CloseAuthSocket (SOCKET s);
BOOL DoAuthentication (SOCKET s);

static PBYTE g_pInBuf = NULL;
static PBYTE g_pOutBuf = NULL;
static DWORD g_cbMaxMessage = 0;
static unsigned short g_usPort = 2000;

void main(int argc, char *argv[])
{
	SOCKET s;
	int cbRead;
	char achData[BUFSIZ];

	if (argc < 2)  {
		fprintf (stderr, "usage: %s <server>\n", argv[0]);
		fprintf (stderr, " example: %s winbase\n", argv[0]);
		exit (EXIT_FAILURE);
	}

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

	// connect to server
	//
	if (!ConnectAuthSocket (argv[1], &s))
		exit (EXIT_FAILURE);

	while (1) {
		// read from the socket
		//
		if (!ReceiveBytes (s, achData, BUFSIZ, &cbRead))
			break;

		if (0 == cbRead)
			break;

		// display the results
		//
		printf ("%.*s", cbRead, achData);
	}

	printf ("\n");

	// terminate
	//
	CloseAuthSocket (s);

	TermPackage ();

	TermWinsock ();

	free (g_pInBuf);
	free (g_pOutBuf);

	exit (EXIT_SUCCESS);
}

BOOL ConnectAuthSocket (LPCSTR szServer, SOCKET *s)
/*++

 Routine Description:

    Establishes an authenticated socket connection with a server and
	initializes any needed security package resources.

 Return Value:

    Returns TRUE is successful; otherwise FALSE is returned.

--*/
{
	SOCKET sockServer;
	unsigned long ulAddress;
	struct hostent *pHost;
	SOCKADDR_IN sin;
	DWORD dwRes;

	// lookup the address for the server name
	//
	ulAddress = inet_addr (szServer);
	if (INADDR_NONE == ulAddress) {
		pHost = gethostbyname (szServer);
		if (NULL == pHost) {
			dwRes = GetLastError ();
			fprintf (stderr, "Unable to resolve host name: %u\n", dwRes);
			return(FALSE);
		}

		memcpy((char FAR *)&ulAddress, pHost->h_addr, pHost->h_length);
	}

	// create the socket
	//
	sockServer = socket (PF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == sockServer) {
		fprintf (stderr, "Unable to create socket: %u\n", GetLastError ());
		return(FALSE);
	}

	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = ulAddress;
	sin.sin_port = htons (g_usPort);

	// connect to remote endpoint
	//
	if (connect (sockServer, (LPSOCKADDR) &sin, sizeof (sin))) {
		fprintf (stderr, "connect failed: %u\n", GetLastError ());
		closesocket (sockServer);
		return(FALSE);
	}

	// Make this an authenticated connection
	//
	if (!InitSession (sockServer)) {
		closesocket (sockServer);
		return(FALSE);
	}

	if (!DoAuthentication (sockServer)) {
		closesocket (sockServer);
		return(FALSE);
	}

	*s = sockServer;

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

    Manges the authentication conversation with the server via the
    supplied socket handle.

 Return Value:

    Returns TRUE is successful; otherwise FALSE is returned.

--*/
{
	BOOL done = FALSE;
	DWORD cbOut, cbIn;

	cbOut = g_cbMaxMessage;
	if (!GenClientContext (s, NULL, 0, g_pOutBuf, &cbOut, &done))
		return(FALSE);
	
	if (!SendMsg (s, g_pOutBuf, cbOut))
		return(FALSE);

	while (!done) {
		if (!ReceiveMsg (s, g_pInBuf, g_cbMaxMessage, &cbIn))
			return(FALSE);

		cbOut = g_cbMaxMessage;
		if (!GenClientContext (s, g_pInBuf, cbIn, g_pOutBuf, &cbOut, &done))
			return(FALSE);

		if (!SendMsg (s, g_pOutBuf, cbOut))
			return(FALSE);
	}

	return(TRUE);
}
