/******************************************************************************\
* ioctl.c - TCP server
*
*       This is a part of the Microsoft Source Code Samples.
*       Copyright 1996-1997 Microsoft Corporation.
*       All rights reserved.
*       This source code is only intended as a supplement to
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the
*       Microsoft samples programs.
\******************************************************************************/



#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEFAULT_PORT 5001

int ReadAndEcho(SOCKET , char *,int ) ;
int WriteMessage(SOCKET , char *,int ) ;

void Usage(char *progname) {
	fprintf(stderr,"Usage\n%s -e [endpoint] -i [interface]\n",
		progname);
	fprintf(stderr,"Where:\n");
	fprintf(stderr,"\tendpoint is the port to listen on\n");
	fprintf(stderr,"\tinterface is the ipaddr (in dotted decimal notation)");
	fprintf(stderr," to bind to\n");
	fprintf(stderr,"Defaults are 5001 and INADDR_ANY\n");
	WSACleanup();
	exit(1);
}
int main(int argc, char **argv) {

	char Buffer[128];
	char *interface= NULL;
	unsigned short port=DEFAULT_PORT;
	int fromlen;
	int i, ioctl_opt =1;
	struct sockaddr_in local, from;
	WSADATA wsaData;
	SOCKET listen_socket, msgsock;
	fd_set readfds, writefds, exceptfds;

	/* Parse arguments */
	if (argc >1) {
		for(i=1;i <argc;i++) {
			if ( (argv[i][0] == '-') || (argv[i][0] == '/') ) {
				switch(tolower(argv[i][1])) {
					case 'i':
						interface = argv[++i];
						break;
					case 'e':
						port = atoi(argv[++i]);
						break;
					default:
						Usage(argv[0]);
						break;
				}
			}
			else
				Usage(argv[0]);
		}
	}
	
	if (WSAStartup(0x202,&wsaData) == SOCKET_ERROR) {
		fprintf(stderr,"WSAStartup failed with error %d\n",WSAGetLastError());
		WSACleanup();
		return -1;
	}
	
	if (port == 0){
		Usage(argv[0]);
	}

	//
	// The fd sets should be zeroed out before using them to prevent errors.
	FD_ZERO(&readfds);
	FD_ZERO(&writefds);
	FD_ZERO(&exceptfds);
	memset(Buffer,0,sizeof(Buffer));

	local.sin_family = AF_INET;

	//
	// bind to specific interface if desired.

	local.sin_addr.s_addr = (!interface)?INADDR_ANY:inet_addr(interface); 

	/* 
	 * Port MUST be in Network Byte Order
	 */
	local.sin_port = htons(port);

	listen_socket = socket(AF_INET, SOCK_STREAM,0); // TCP socket
	if (listen_socket == INVALID_SOCKET){
		fprintf(stderr,"socket() failed with error %d\n",WSAGetLastError());
		WSACleanup();
		return -1;
	}
	//
	// bind() associates a local address and port combination with the
	// socket just created. 

	if (bind(listen_socket,(struct sockaddr*)&local,sizeof(local) ) 
		== SOCKET_ERROR) {
		fprintf(stderr,"bind() failed with error %d\n",WSAGetLastError());
		WSACleanup();
		return -1;
	}

	//
	// start listening on the socket for incoming connections
	//
	if (listen(listen_socket,5) == SOCKET_ERROR) {
		fprintf(stderr,"listen() failed with error %d\n",WSAGetLastError());
		WSACleanup();
		return -1;
	}
	printf("%s: Listening on port %d\n",argv[0],port);

	//
	// Set the socket to non-blocking mode.
	//
	if (ioctlsocket(listen_socket,FIONBIO,&ioctl_opt) == SOCKET_ERROR) {
		fprintf(stderr,"ioctlsocket failed %d\n",WSAGetLastError());
		WSACleanup();
		return -1;
	}
	//
	// The structure of the loop below is very simple. We only accept one
	// connection at a time. As soon as another client connects, we
	// disconnect the first one, and start talking to the new client.
	// All this server does is to echo the data received on the socket
	// back to the client.
	//
	// This is not a very realistic server, but it does serve to show that
	// select() does not scale very well on win32. If we were dealing
	// with more than one client, we would have to have a list of sockets
	// that are in each fdset to be able to check them when select()
	// returns.
	//
	while(1) {

		//
		// A socket in the listen() state becomes ready to read when a
		// client connects to it. An accept() will complete without
		// blocking.
		// Since select sets the sockets that are ready to be read from or
		// written to, we have to include listen_socket in the fdset each time
		// through the loop.
		//

		FD_SET(listen_socket,&readfds);

		i = select(0,&readfds,&writefds,&exceptfds,NULL);
		if (i == SOCKET_ERROR) {
			fprintf(stderr,"select failed %d\n",WSAGetLastError());
		}
		if (i==0){
			fprintf(stderr,"Select returned no fds ready\n");
		}

		if (FD_ISSET(listen_socket, &readfds)){
			//
			// close the previous client socket. 
			// We must also clear it from the fdset to prevent select()
			// from failing.
			//
			closesocket(msgsock);
			FD_CLR(msgsock,&readfds);
			FD_CLR(msgsock,&writefds);
			fromlen = sizeof(from);
			msgsock= accept(listen_socket,(struct sockaddr*)&from,&fromlen);
			if (msgsock == INVALID_SOCKET) {
				fprintf(stderr,"accept failed %d\n",WSAGetLastError());
				WSACleanup();
				return -1;
			}
			FD_SET(msgsock,&writefds);
			FD_SET(msgsock,&readfds);
			continue;
		}
		if (FD_ISSET(msgsock,&readfds) ) {
			//
			// socket is ready to read, i.e., there is data on the socket.
			//
			if (ReadAndEcho(msgsock,Buffer,sizeof(Buffer))<0) {
				fprintf(stderr,"terminating connection\n");
				FD_CLR(msgsock,&readfds);
				FD_CLR(msgsock,&writefds);
				closesocket(msgsock);
				continue;
			}
		}
		if (FD_ISSET(msgsock,&writefds) ){
			if (WriteMessage(msgsock,Buffer,sizeof(Buffer)) <=0) {
				fprintf(stderr,"terminating connection\n");
				FD_CLR(msgsock,&readfds);
				FD_CLR(msgsock,&writefds);
				closesocket(msgsock);
				continue;
			}
		}
		FD_SET(msgsock,&writefds);
		FD_SET(msgsock,&readfds);
	}
}
int ReadAndEcho(SOCKET insock, char *Buffer,int size) {
	int rc;

	rc = recv(insock,Buffer,size,0);

	if (rc == SOCKET_ERROR) {
		fprintf(stderr,"recv() failed with error %d\n",WSAGetLastError());	
		return -1;
	}
	if (rc ==0) {
		fprintf(stderr,"Connection closed by client\n");
		return 0;
	}
	printf("Received [%s] from client\n",Buffer);
	return rc;
}
int WriteMessage(SOCKET outsock, char *Buffer,int size) {
	int rc;
	int lasterr;

	printf("Sending [%s] to client\n",Buffer);
	rc = send(outsock,Buffer,size, 0);

	if (rc == SOCKET_ERROR) {
	  lasterr = WSAGetLastError();
	  if (lasterr == WSAEWOULDBLOCK)
		return 0;
	  else {
		fprintf(stderr,"send() failed with error %d\n",lasterr);	
		return -1;
	  }
	}
	if (rc ==0) {
		fprintf(stderr,"Connection closed by client\n");
	}
	return rc;
}
