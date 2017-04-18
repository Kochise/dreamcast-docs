/******************************************************************************\
* simples.c - Simple TCP/UDP server using Winsock 1.1
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
#define DEFAULT_PROTO SOCK_STREAM // TCP

void Usage(char *progname) {
	fprintf(stderr,"Usage\n%s -p [protocol] -e [endpoint] -i [interface]\n",
		progname);
	fprintf(stderr,"Where:\n\tprotocol is one of TCP or UDP\n");
	fprintf(stderr,"\tendpoint is the port to listen on\n");
	fprintf(stderr,"\tinterface is the ipaddr (in dotted decimal notation)");
	fprintf(stderr," to bind to\n");
	fprintf(stderr,"Defaults are TCP,5001 and INADDR_ANY\n");
	WSACleanup();
	exit(1);
}
int main(int argc, char **argv) {

	char Buffer[128];
	char *interface= NULL;
	unsigned short port=DEFAULT_PORT;
	int retval;
	int fromlen;
	int i;
	int socket_type = DEFAULT_PROTO;
	struct sockaddr_in local, from;
	WSADATA wsaData;
	SOCKET listen_socket, msgsock;

	/* Parse arguments */
	if (argc >1) {
		for(i=1;i <argc;i++) {
			if ( (argv[i][0] == '-') || (argv[i][0] == '/') ) {
				switch(tolower(argv[i][1])) {
					case 'p':
						if (!stricmp(argv[i+1], "TCP") )
							socket_type = SOCK_STREAM;
						else if (!stricmp(argv[i+1], "UDP") )
							socket_type = SOCK_DGRAM;
						else
							Usage(argv[0]);
						i++;
						break;

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

	local.sin_family = AF_INET;
	local.sin_addr.s_addr = (!interface)?INADDR_ANY:inet_addr(interface); 

	/* 
	 * Port MUST be in Network Byte Order
	 */
	local.sin_port = htons(port);

	listen_socket = socket(AF_INET, socket_type,0); // TCP socket
	
	if (listen_socket == INVALID_SOCKET){
		fprintf(stderr,"socket() failed with error %d\n",WSAGetLastError());
		WSACleanup();
		return -1;
	}
	//
	// bind() associates a local address and port combination with the
	// socket just created. This is most useful when the application is a 
	// server that has a well-known port that clients know about in advance.
	//

	if (bind(listen_socket,(struct sockaddr*)&local,sizeof(local) ) 
		== SOCKET_ERROR) {
		fprintf(stderr,"bind() failed with error %d\n",WSAGetLastError());
		WSACleanup();
		return -1;
	}

	//
	// So far, everything we did was applicable to TCP as well as UDP.
	// However, there are certain steps that do not work when the server is
	// using UDP.
	//

	// We cannot listen() on a UDP socket.

	if (socket_type != SOCK_DGRAM) {
		if (listen(listen_socket,5) == SOCKET_ERROR) {
			fprintf(stderr,"listen() failed with error %d\n",WSAGetLastError());
			WSACleanup();
			return -1;
		}
	}
	printf("%s: 'Listening' on port %d, protocol %s\n",argv[0],port,
		(socket_type == SOCK_STREAM)?"TCP":"UDP");
	while(1) {
		fromlen =sizeof(from);
		//
		// accept() doesn't make sense on UDP, since we do not listen()
		//
		if (socket_type != SOCK_DGRAM) {
			msgsock = accept(listen_socket,(struct sockaddr*)&from, &fromlen);
			if (msgsock == INVALID_SOCKET) {
				fprintf(stderr,"accept() error %d\n",WSAGetLastError());
				WSACleanup();
				return -1;
			}
			printf("accepted connection from %s, port %d\n", 
						inet_ntoa(from.sin_addr),
						htons(from.sin_port)) ;
			
		}
		else
			msgsock = listen_socket;

		//
		// In the case of SOCK_STREAM, the server can do recv() and 
		// send() on the accepted socket and then close it.

		// However, for SOCK_DGRAM (UDP), the server will do
		// recvfrom() and sendto()  in a loop.

		if (socket_type != SOCK_DGRAM)
			retval = recv(msgsock,Buffer,sizeof (Buffer),0 );
		else {
			retval = recvfrom(msgsock,Buffer,sizeof (Buffer),0,
				(struct sockaddr *)&from,&fromlen);
			printf("Received datagram from %s\n",inet_ntoa(from.sin_addr));
		}
			
		if (retval == SOCKET_ERROR) {
			fprintf(stderr,"recv() failed: error %d\n",WSAGetLastError());
			closesocket(msgsock);
			continue;
		}
		if (retval == 0) {
			printf("Client closed connection\n");
			closesocket(msgsock);
			continue;
		}
		printf("Received %d bytes, data [%s] from client\n",retval,Buffer);

		printf("Echoing same data back to client\n");
		if (socket_type != SOCK_DGRAM)
			retval = send(msgsock,Buffer,sizeof(Buffer),0);
		else
			retval = sendto(msgsock,Buffer,sizeof (Buffer),0,
				(struct sockaddr *)&from,fromlen);
		if (retval == SOCKET_ERROR) {
			fprintf(stderr,"send() failed: error %d\n",WSAGetLastError());
		}
		if (socket_type != SOCK_DGRAM){
			printf("Terminating connection\n");
			closesocket(msgsock);
		}
		else 
			printf("UDP server looping back for more requests\n");
		continue;
	}
}
