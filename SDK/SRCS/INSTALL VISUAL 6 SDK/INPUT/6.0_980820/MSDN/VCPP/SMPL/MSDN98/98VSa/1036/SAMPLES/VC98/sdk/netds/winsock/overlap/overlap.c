/******************************************************************************\
* Sample demonstrating use of Events in Overlapped (Asynchronous) I/O
*
* This code uses AcceptEx()
* YOU MUST HAVE SERVICE PACK 3 on NT 3.51 to use it !!!
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
#include <mswsock.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DEFAULT_PORT 5001
#define MAX_IO_PEND 10		// maximum pending I/O requests

#define OP_READ 0x10
#define OP_WRITE 0x20

#define xmalloc(s) HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,(s))
#define xfree(p)   HeapFree(GetProcessHeap(),0,(p))

//
// This structure keeps some useful information
//
typedef struct _socklist {
	SOCKET sock;
	OVERLAPPED *overlap;
	char Buffer[128];
}Socklist;

int curr_size; //current number of handles we are intersted in

int DoWait(HANDLE *,Socklist *) ;
void HandleEvent(int , HANDLE *,Socklist *) ;

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

	char *interface= NULL;
	char *Buffer = xmalloc(256);
	unsigned short port=DEFAULT_PORT;
	int i;
	struct sockaddr_in local;
	WSADATA wsaData;
	SOCKET listen_socket, accept_sock;
	OVERLAPPED *Overlap;
	DWORD bytes_read;
	DWORD lasterror;
	//
	// Handles is the array that stores the Event Handles

	HANDLE Handles[MAX_IO_PEND] ;

	//
	// socklist is a parallel array that keeps state information for
	// each Handle.
	Socklist socklist[MAX_IO_PEND];

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

	local.sin_family = AF_INET;
	local.sin_addr.s_addr = (!interface)?INADDR_ANY:inet_addr(interface); 

	/* 
	 * Port MUST be in Network Byte Order
	 */
	local.sin_port = htons(port);

	listen_socket = socket(AF_INET,SOCK_STREAM,0); // TCP socket
	if(listen_socket == INVALID_SOCKET) {
		fprintf(stderr,"socket() failed with error %d\n",WSAGetLastError());
		WSACleanup();
		return -1;
	}
	

	if (bind(listen_socket,(struct sockaddr*)&local,sizeof(local) ) 
		== SOCKET_ERROR) {
		fprintf(stderr,"bind() failed with error %d\n",WSAGetLastError());
		WSACleanup();
		return -1;
	}


	if (listen(listen_socket,5) == SOCKET_ERROR) {
		fprintf(stderr,"listen() failed with error %d\n",WSAGetLastError());
		WSACleanup();
		return -1;
	}
	printf("%s: Listening on port %d\n",argv[0],port);
		
	//
	// Add the listening socket to our state information for the handle.
	//
	socklist[0].sock = listen_socket;

	curr_size =1;

	for(i=1;i<MAX_IO_PEND;i++)
		Handles[i] = INVALID_HANDLE_VALUE;

	//
	// The structure of the following loop is very similar to a situation
	// where select() might be used. 
	// We use WaitForSingleObject to multiplex between incoming/outgoing
	// data on existing connections.
	//
	// We don't queue an AcceptEx() until someone actually connects to 
	// the previous socket. This is to keep the code simple, not a limitation
	// of the API itself.

	while(1) {

		// create a socket for AcceptEx()

		accept_sock = socket(AF_INET,SOCK_STREAM,0);

		//
		// Allocate an overlapped structure.
		// We use the Offset field to keep track of the socket handle
		// we have accpeted a connection on, since there is no other
		// way to pass information to GetOverlappedResult()
		//
		Overlap = xmalloc(sizeof(OVERLAPPED));
		Overlap->Offset = accept_sock;

		Overlap->hEvent = CreateEvent(NULL,
									 TRUE,//manual reset
									 FALSE, // initially non-signalled
									 NULL);

		if (!Overlap->hEvent) {
			fprintf(stderr,"CreateEvent failed %d\n",GetLastError());
			return -1;
		}
		//
		// Set the appropriate array members
		//
		Handles[0] = Overlap->hEvent;
		socklist[0].overlap = Overlap;

		// AcceptEx()
		if (!AcceptEx(listen_socket,
					  accept_sock,
					  Buffer,
					  0, // read nothing from the socket
					  sizeof(struct sockaddr_in) +16,
					  sizeof(struct sockaddr_in) +16,
					  &bytes_read,
					  Overlap)){
			lasterror=WSAGetLastError();
			if(lasterror!=ERROR_IO_PENDING){
				fprintf(stderr,"acceptex failed %d\n",lasterror);
				return -1;
			}
		}
		//
		// This loop simple checks the handles to see which one is 
		// signalled. 
		// If error, exit. 
		// If there is a new incoming connection, we break to the outer loop
		// queue another AcceptEx()
		//
		while(1){
			i = DoWait(Handles,socklist);
			if (i<0)
				break;
			HandleEvent(i,Handles,socklist);
			if (i ==0)
				break;
		};
		if (i < 0)
			return -1;

	}
}
/*
 * This is the main function that handles all the events occuring on the
 * different handles we are watching.
 *
 * Parameters:
 *          index: Index into the Handles[] array. Returned by DoWait()
 *          Handles: Array of Event Handles we are watching
 *          socklist: Helper parallel array of state information
 *
 */
void HandleEvent(int index, HANDLE *Handles,Socklist *socklist) {
	
	OVERLAPPED *Overlap;
	SOCKET newsock;
	DWORD bytes,overlap_err=0,lasterr;

	Overlap = socklist[index].overlap;
	//
	// Check the specified handle
	//
	// If a socket is closed by the other side, the error returned is
	// ERROR_NETNAM_DELETED
	//
	if(!GetOverlappedResult(Handles[index], Overlap, &bytes, TRUE) ) {
		fprintf(stderr,"GetOverlappedResult failed with error %d\n",
					overlap_err=GetLastError());
		if (overlap_err  != ERROR_NETNAME_DELETED) 
			return;
	}
	newsock = Overlap->Offset;
	//
	// If the other side closed the connection, close our socket and 
	// move the last element of the Handles[] array into our 
	// index.
	//
	// The array compaction is done so that we only pass valid handles
	// in the first "curr_size" elements of the array to
	// WaitForMultipleObjects(). The function will fail otherwise.


	// We should NEVER get this for our listening socket
	if (index && overlap_err == ERROR_NETNAME_DELETED) {
		closesocket(newsock);
		xfree(Overlap);
		Handles[index] = Handles[curr_size-1];
		socklist[index] = socklist[curr_size-1];
		curr_size--;
		return;
	}

	if( (index ==0) ) { //listening socket
		if (curr_size >= MAX_IO_PEND) {
			fprintf(stderr,"Too many pending requests\n");
			return;
		}
		//
		// Get the event handle used to queue the AcceptEx(),
		// and re-use it to queue a ReadFile on the socket.
		//

		Handles[curr_size] = Overlap->hEvent;
		socklist[curr_size].overlap = Overlap;

		//
		// The OffsetHigh field is used to keep track of what we are doing.
		// This enables us to alternate ReadFile and WriteFile on a 
		// connection

		Overlap->OffsetHigh = OP_READ;

		if (!ReadFile((HANDLE)newsock, socklist[curr_size].Buffer,
						sizeof(socklist[curr_size].Buffer),
						&bytes,
						Overlap) ) {
			lasterr = GetLastError();

			// Handle ERROR_NETNAME_DELETED specially
			// Other errors are Not Good
			//
			if (lasterr && lasterr != ERROR_IO_PENDING &&
				lasterr != ERROR_NETNAME_DELETED ) {
				fprintf(stderr,"Inital ReadFile failed %d\n");
				return;
			}
			if (lasterr == ERROR_NETNAME_DELETED) {
				closesocket(newsock);
				xfree(Overlap);
				Handles[index] = Handles[curr_size];
				socklist[index] = socklist[curr_size];
				curr_size--;
				return;
			}

		}
		//
		// Increment the last valid handle location in the Handles
		// array.
		curr_size++;
		return;
	}
	//
	// This possibly indicates a closed socket.
	//
	if (  (bytes == 0 ) && (Overlap->OffsetHigh == OP_READ) ){
		closesocket(newsock);
		xfree(Overlap);
		Handles[index] = Handles[curr_size];
		socklist[index] = socklist[curr_size];
		curr_size--;
		return;
	}
	//
	//  If the previos operation was an OP_READ, queue WriteFile on the
	//  socket
	//
	if (Overlap->OffsetHigh == OP_READ) { // ReadFile was queued
		printf("Read buffer [%s]\n",socklist[index].Buffer);
		printf("Echoing back to client\n");
		if (!WriteFile((HANDLE)newsock, socklist[index].Buffer,
						sizeof(socklist[index].Buffer),
						&bytes,
						Overlap) ) {
			lasterr = GetLastError();
			if (lasterr && lasterr != ERROR_IO_PENDING &&
				lasterr != ERROR_NETNAME_DELETED ) {
				fprintf(stderr,"WriteFile failed %d\n");
				ExitProcess(1);
			}
			if ( (lasterr == ERROR_NETNAME_DELETED) || (!lasterr)) {
					closesocket(newsock);
					xfree(Overlap);
					Handles[index] = Handles[curr_size];
					socklist[index] = socklist[curr_size];
					curr_size--;
					return;
			}
		}
		Overlap->OffsetHigh = OP_WRITE;
		return;
	}
	//
	// If we had a WriteFile queued, now do a ReadFile
	//
	else if (Overlap->OffsetHigh == OP_WRITE) { // WriteFile was queued
		printf("Wrote %d bytes\n",bytes);
		printf("Queueing read\n");
		if (!ReadFile((HANDLE)newsock, socklist[index].Buffer,
						sizeof(socklist[index].Buffer),
						&bytes,
						Overlap) ) {
			lasterr =GetLastError();
			if (lasterr && lasterr != ERROR_IO_PENDING) {
				if (lasterr == ERROR_NETNAME_DELETED) {
					closesocket(newsock);
					xfree(Overlap);
					Handles[index] = Handles[curr_size];
					socklist[index] = socklist[curr_size];
					curr_size--;
					return;
				}
				fprintf(stderr,"ReadFile failed %d\n",GetLastError());
				ExitProcess(1);
			}
		}
		Overlap->OffsetHigh = OP_READ;
		return;
	}
	else {
		fprintf(stderr,"Unknown operation queued\n");
	}
	
}
//
// This is the wait function used to keep track of events
//
int DoWait(HANDLE *Handles,Socklist *socklist ) {

	DWORD wait_rc;
	HANDLE hTemp;
	Socklist socklTemp;

	int i;

	//
	// Rotate the array, beginning at index 1, by one element.
	// This ensures that all handles get a fair chance to be serviced.
	//
	// There is no way to detect how many handles were signalled when
	// WaitForMultipleObjects() returns. We simply pick the first one and 
	// come back to this function later
	// Without the rotation below, this has the potential for starving
	// connections accepted later.
	//
	// Index 0 is avoided, since it is our listening socket. 
	//
	for(i=1;i<curr_size-1;i++){

		hTemp = Handles[i+1];
		Handles[i+1] = Handles[i];
		Handles[i] = hTemp;

		socklTemp = socklist[i+1];
		socklist[i+1] = socklist[i];
		socklist[i] = socklTemp;
	}

	wait_rc = WaitForMultipleObjects(curr_size,Handles,FALSE,
		INFINITE);

	if (wait_rc == WAIT_FAILED) {
		fprintf(stderr,"Wait failed Error %d\n",GetLastError());
		return -1;
	}

	return (wait_rc - WAIT_OBJECT_0);
}
