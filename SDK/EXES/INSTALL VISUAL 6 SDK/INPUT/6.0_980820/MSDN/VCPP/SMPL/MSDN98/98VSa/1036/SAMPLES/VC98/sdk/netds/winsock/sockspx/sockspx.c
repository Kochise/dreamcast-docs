/******************************************************************************\
*       This is a part of the Microsoft Source Code Samples.
*       Copyright 1996-1997 Microsoft Corporation.
*       All rights reserved.
*       This source code is only intended as a supplement to
*       Microsoft Development Tools and/or WinHelp documentation.
*       See these sources for detailed information regarding the
*       Microsoft samples programs.
\******************************************************************************/


/*
Module Name:

    sockspx.c

Abstract:

    This module illustrates the Win32 Winsock APIs over IPX/SPX protocol
    sequence.

    This example implements a client and a server. This example can use IPX,
    SPX as well as SPXII protocol sequences. The example has a number command
    line options. For example,

    -s To run the example as a server.
	
    -c To run the example as a client.
    
    -e <Endpoint> To specify an end point of your choice. This is a mandatory
	parameter. Servers use this as the socket number to listen on, clients use
	it as the socket number to connect to, on a specified host.

    -n <ServerIpxAddress> To specify the server's IPX address. This is used by
	clients. The address must be spcified as <NetworkNumber.NodeNumber> 
	format, for example AABBCCDD.AABBCCDDEEFF.
	
    -l <LocalIpxAddress> To specify the local IPX address. This is used by
	clients and servers. The address must be spcified as <NetworkNumber.
	NodeNumber> format, for example AABBCCDD.AABBCCDDEEFF. If an IPX address
	is not specified the created sockets are bound to the default interface,
	00000000.000000000000.

    -p <d or s or p> To specify the protocol sequence to be used. 
	'd' - datagram support, in this case IPX protocol sequence is used. 
	's' - SOCK_STREAM/SPXII protocol sequence is used(default protocol).
	'p' - SOCK_SEQPACKET/SPXII protocol sequence isused.
	   
    -m To Enumerate Local Addresses. This example can be used only to 
	enumerate the local IPX adapters. This may be important before running the
	client to know the server's IPX address.
       
	To run the application as a server, the following command line can be 
	specified:
    
	sockspx -s -e 8000 -p s
	
	To run the application to act as a client, the following command line can be
	specified:
	
	sockspx -c -n AABBCCDD.AABBCCDDEEFF -e 8000 -p s
    
	To enumerate the local IPX adapters, the following command line will have
	to be specified:
	
	sockspx -m
	  
    
Author:

    Rajesh Dadhia (rajeshd) 05-Mar-96

Revision History:

*/

#include <stdio.h>
#include <windows.h>
#include <winsock.h>
#include <wsipx.h>
#include <wsnwlink.h> 

#define MAX_DATA_LEN 80

BOOL __stdcall
CtrlCHandler (
    DWORD dwEvent
    );

void __stdcall
EnumerateAdapters ( void );

void  __stdcall
DoServer ( void );

void __stdcall 
DoClient ( void );

void __stdcall
DoStartup ( void );

void __stdcall
CreateSocket ( void );

void __stdcall
BindSocket ( 
    SOCKADDR_IPX *psa, 
    LPSTR lpsAddress,
    LPSTR lpsEndpoint
    );

void _stdcall
FillIpxAddress ( 
    SOCKADDR_IPX *psa, 
    LPSTR lpsAddress,
    LPSTR lpsEndpoint
    );

INT __stdcall 
SendData (
    SOCKET s, 
    CHAR *pchBuffer 
    );

INT __stdcall
ReceiveData (
    SOCKET s, 
    CHAR *pchBuffer
    );

INT __stdcall
SendDatagram (
    SOCKET s, 
    CHAR *pchBuffer, 
    SOCKADDR_IPX *psa
    );

INT __stdcall
ReceiveDatagarm (
    SOCKET s, 
    CHAR *pchBuffer, 
    SOCKADDR_IPX *psa, 
    INT *pcb );

void __stdcall
DoCleanup ( void );

void __stdcall
CheckParameters (
    INT argc, 
    CHAR **argv
    );

BOOL __stdcall
CheckProtocol(
    CHAR chProtocol
	);

void __stdcall
Usage (
    CHAR *pszProgramName
    );

void __stdcall 
PrintError (
    CHAR *lpszRoutine,
    CHAR *lpszCallName,
    DWORD dwError
    );

void __stdcall
PrintIpxAddress(
    CHAR *lpsNetnum,
    CHAR *lpsNodenum
    );

void __stdcall
AtoH(
    CHAR *szDest, 
    CHAR *szSource,
    INT iCount
    );

UCHAR __stdcall
BtoH(
    CHAR ch
	);

//
// Global Variables
//

// Role of the Application 
BOOL fServer = TRUE,

// Enumerate the Local Adapters 
     fEnumerate = FALSE,

// WSAStartup () was sucessfull 
     fStarted = FALSE;

// Global socket handles 
SOCKET sock = INVALID_SOCKET,
       newsock = INVALID_SOCKET;

// Server's IPX address string
CHAR *pszServerAddress,

// Local IPX address string 
     *pszLocalAddress,

// Server's Endpoint(socket) string 
     *pszServerEndpoint,

// Protocol type (Datagram, Stream, Sequenced Packet)
     chProtocol = 's';

void __cdecl
main (
    INT argc,
    CHAR **argv
    )
{
    
    //
    // Install the CTRL+BREAK Handler
    //
    if ( FALSE == SetConsoleCtrlHandler ( (PHANDLER_ROUTINE) CtrlCHandler,
					  TRUE 
					  ) ) 
    {
	PrintError ( "main", "SetConsoleCtrlHandler", GetLastError ( ) );
    }
	
    //
    // Parse the command line parameters
    //
    CheckParameters ( argc, argv );

    //
    // Check to see if the role of the application is to enumerate local 
    // adapters
    //
    if ( TRUE == fEnumerate )
    {
	EnumerateAdapters ( );
	return;
    }

    //
    // Act as a server
    //
    if( TRUE == fServer )
    {
	DoServer ( );
	return;
    }
	
    //
    // Act as client
    //
    else
    {
	DoClient ( );
	return;
    }                                                       
}

//
// CtrlCHandler () intercepts the CTRL+BREAK or CTRL+C events and calls the
// cleanup routines
//
BOOL __stdcall
CtrlCHandler (
    DWORD dwEvent
	)
{
  
    if ( ( CTRL_C_EVENT == dwEvent ) || ( CTRL_BREAK_EVENT == dwEvent ) )
    {
	DoCleanup ( );    
    }

    return FALSE;
}
  
//
// EnumerateAdapters () will enumerate the available IPX adapters and print
// the addresses
//
void __stdcall
EnumerateAdapters ( void )
{
  SOCKADDR_IPX sa_ipx;
  IPX_ADDRESS_DATA ipx_data;
  INT iRetVal, cb, nAdapters, i=0;
	
    //        
    // Initialize the Winsock 1.1 DLL
    //
    DoStartup ( );

    //
    // Create a local socket
    //
    chProtocol = 'd';
    CreateSocket ( );
	
    //
    // Bind to a local address and endpoint
    //
    BindSocket ( &sa_ipx, NULL, NULL );
    
    //
    // Call getsockopt() see the total number of adapters
    //
    cb = sizeof ( nAdapters );
    iRetVal = getsockopt ( sock, 
			   NSPROTO_IPX, 
			   IPX_MAX_ADAPTER_NUM,
			   (CHAR *) &nAdapters,
			   &cb 
			   );
    
    if ( SOCKET_ERROR == iRetVal )
    {
	PrintError ( "EnumerateAdapters", 
		     "getsockopt", 
		     WSAGetLastError ( ) 
		     );
    }
    fprintf ( stdout, "Total number of adapters -> %d\n", nAdapters );

    //
    // Get the address of each adapter
    //
    while ( nAdapters > 0 )
    {                                                
	memset ( &ipx_data, 0, sizeof ( ipx_data ) );
	ipx_data.adapternum = (nAdapters -1);
	cb = sizeof ( ipx_data );
			
	iRetVal = getsockopt ( sock,
			       NSPROTO_IPX,
			       IPX_ADDRESS,
			       (CHAR *) &ipx_data,
			       &cb 
			       );

	if ( SOCKET_ERROR == iRetVal )
	{
	    PrintError ( "EnumerateAdapters", 
			 "getsockopt", 
			 WSAGetLastError ( ) 
			 );
	}
	    
	//   
	// Print each address
	//
	PrintIpxAddress ( ipx_data.netnum, ipx_data.nodenum );
	nAdapters--;                                                         
    }
    
    //
    // Call the cleanup routine
    //
    DoCleanup ( );
    return;
}

//
// DoServer () performs the connection-less/connection-oriented server
// related tasks
//
void  __stdcall
DoServer ( void )
{                        
  // Address structures for the client and the server
  SOCKADDR_IPX sa_ipx, sa_ipx_client;     

  // Buffer for the received/sent data
  CHAR chBuffer[MAX_DATA_LEN];

  INT iRetVal, cb;
	
    DoStartup ( );
   
    CreateSocket ( );

    //
    // Bind to a local address and endpoint
    //
    BindSocket ( &sa_ipx, pszLocalAddress, pszServerEndpoint);

    //
    // Check the Specified protocol. Call listen(), accept() if a connection 
    // oriented protocol is specified
    //
    if ( 'd' != chProtocol   )
    {
	iRetVal = listen ( sock, 5 );
	
	if ( SOCKET_ERROR == iRetVal )
	{
	    PrintError ( "DoServer", "listen", WSAGetLastError ( ) );
	}
	    
	fprintf ( stdout, "Waiting for a Connection...\n");
	fprintf ( stdout, "Press <CTRL+C> or <CTRL+BREAK> to exit\n");
	//
	// Wait for a connection
	//
	cb = sizeof ( sa_ipx_client );
	newsock = accept ( sock, 
			   (SOCKADDR *) &sa_ipx_client, 
			   &cb 
			   );
	
	if ( INVALID_SOCKET == newsock )
	{
	    PrintError ( "DoServer", "accept", WSAGetLastError ( ) );
	}
	    
	//
	// Print the address of connected client
	//
	fprintf ( stdout, "Connected to Client Address - " );
	PrintIpxAddress ( sa_ipx_client.sa_netnum, sa_ipx_client.sa_nodenum );

	//
	// Receive data on newly created socket
	//
	iRetVal = ReceiveData ( newsock, chBuffer );
		
	//
	// Print the contents of received data
	//
	chBuffer[iRetVal] = '\0';
	fprintf ( stdout,"%d bytes of data received->%s\n",iRetVal, chBuffer );
	strcpy ( chBuffer, "Hello SPX Client" ); 
	
	//
	// Send data on newly created socket
	//
	iRetVal = SendData ( newsock, chBuffer );
	fprintf ( stdout, "%d bytes of data sent\n", iRetVal );
    }
    //
    // Server will receive and send datagrams
    //
    else 
    {
	//
	// Receive a datagram on the bound socket
	//
	cb = sizeof ( sa_ipx_client );
	iRetVal = ReceiveDatagarm ( sock, chBuffer, &sa_ipx_client, &cb );

	//
	// Print the contents of received datagram and the senders address
	//
	fprintf ( stdout, "Message Received from Client Address - " );
	PrintIpxAddress( sa_ipx_client.sa_netnum, sa_ipx_client.sa_nodenum );
	chBuffer[iRetVal] = '\0';
	fprintf( stdout, "Data Received->%s\n", chBuffer );
	fprintf( stdout,"%d bytes of data received->%s\n",iRetVal, chBuffer );
	
	//
	// Send a datagram on the bound socket to the client
	//
	strcpy ( chBuffer, "Hello IPX Client" ); 
	iRetVal = SendDatagram (sock, chBuffer, &sa_ipx_client );
	fprintf( stdout, "%d bytes of data sent\n", iRetVal );
    }

    // 
    // Call the cleanup routine
    //
    DoCleanup ( );
    return;
}

//
// DoClient () performs the connection-less/connection-oriented client
// related tasks
//
void __stdcall 
DoClient ( void )
{                                                
  // Address structures for the client and the server
  SOCKADDR_IPX sa_ipx, sa_ipx_server;     
    
  // Buffer for the received/sent data
  CHAR chBuffer[MAX_DATA_LEN];            
		 
  INT iRetVal, cb;
	
    DoStartup ( ) ;
	
    CreateSocket ( );
    
    //
    // Bind to a local address and endpoint
    //
    BindSocket ( &sa_ipx, pszLocalAddress, NULL);

    
    if ( NULL == pszServerEndpoint )
    {
	fprintf ( stdout, "Server Endpoint must be specified....Exiting\n");
	DoCleanup ( );
	exit ( 1 );
    }

    //
    // Fill the sa_ipx_server address address with server address and endpoint
    //
    if ( NULL != pszServerAddress )
    {
	FillIpxAddress ( &sa_ipx_server, pszServerAddress, pszServerEndpoint );
    }
    else
    {
	fprintf ( stdout, "Server Address must be specified....Exiting\n");
	DoCleanup ( );
	exit ( 1 );
    }
	
    //
    // Check the Specified protocol. Call connect() if a connection oriented 
    // protocol is specified
    //
    if ( chProtocol != 'd' )
    {
	fprintf(stdout, "Connecting to Server -");
	PrintIpxAddress ( sa_ipx_server.sa_netnum, sa_ipx_server.sa_nodenum );
	    
	//
	// Connect to the server
	//
	iRetVal = connect ( sock, 
			    (SOCKADDR *) &sa_ipx_server,
			    sizeof sa_ipx_server
			    );
	
	if ( SOCKET_ERROR == iRetVal )
	{
	    PrintError ( "DoClient", "connect", WSAGetLastError ( ) );
	}
		   
	fprintf ( stdout, "Connected to Server Address - " );
	PrintIpxAddress( sa_ipx_server.sa_netnum, sa_ipx_server.sa_nodenum );

	//
	// Send data to the specfied server
	//
	strcpy ( chBuffer, "Hello SPX Server" ); 
	iRetVal = SendData ( sock, chBuffer );
	fprintf( stdout, "%d bytes of data sent\n", iRetVal );
		
	//
	// Receive data from the server
	//
	iRetVal = ReceiveData ( sock, chBuffer );
		
	//
	// Print the contents of received data
	//
	chBuffer[iRetVal] = '\0';
	fprintf( stdout, "%d bytes of data received->%s\n", iRetVal,chBuffer);
    }
    else
    {
	//
	// Send a datagram to the specified server
	//
	strcpy ( chBuffer, "Hello IPX Server" ); 
	iRetVal = SendDatagram ( sock, chBuffer, &sa_ipx_server );
	fprintf ( stdout, "%d bytes of data sent\n", iRetVal );

	//
	// Receive a datagram from the server
	//
	cb = sizeof sa_ipx_server;
	iRetVal = ReceiveDatagarm ( sock, chBuffer, &sa_ipx_server, &cb );
		
	//
	// Print the contents of received data
	//
	chBuffer[iRetVal] = '\0';
	fprintf ( stdout, "%d bytes of data received->%s\n",iRetVal,chBuffer);
    }
	
    //
    // Call the cleanup routine
    //
    DoCleanup ( );

    return;
}

//
// DoStartup() initializes the Winsock DLL with Winsock version 1.1
//
void __stdcall
DoStartup ( void )
{
  WSADATA wsaData;
  INT iRetVal;

    iRetVal = WSAStartup ( MAKEWORD ( 1,1 ), &wsaData );
	
    if ( 0 != iRetVal)
    {
	    PrintError ( "DoStartup", "WSAStartup", iRetVal );
    }
    
    /* Set the global flag */
    fStarted = TRUE;
 
    return;
}

//
// CreateSocket() creates an endpoint (socket) and assigns the returned value
// from socket() to the global socket descriptor 'sock'. The actual protocol
// specified on the command line is checked, in order to make the socket()
// call correctly.
//
void __stdcall
CreateSocket ( void )
{
    sock = socket ( AF_IPX,
		    chProtocol == 'd' ? SOCK_DGRAM : 
		    ( chProtocol == 's'  ? SOCK_STREAM : SOCK_SEQPACKET),
		    chProtocol == 'd' ? NSPROTO_IPX : NSPROTO_SPXII
		    );
    
    if ( INVALID_SOCKET == sock )
    {
	PrintError ( "CreateSocket", "socket", WSAGetLastError ( ) );
    }
    
    return;
}

//
// BindSocket() binds the global socket descriptor 'sock' to the specified
// address. If an endpoint is specified it uses that or it binds to a system 
// assigned port.
//
void __stdcall
BindSocket ( 
    SOCKADDR_IPX *psa, 
	LPSTR lpsAddress,
	LPSTR lpsEndpoint
	)
{
  INT iRetVal;

    //
    // Fill the givenSOCKADDR_IPX structure
    //
    FillIpxAddress ( psa, lpsAddress, lpsEndpoint );

    iRetVal = bind ( sock, 
		     (SOCKADDR *) psa, 
		     sizeof (SOCKADDR_IPX) 
		     );
    
    if ( SOCKET_ERROR == iRetVal )
    {
	PrintError ( "BindSocket", "bind", WSAGetLastError ( ) );
    }

    // 
    // Print the address we are bound to. If a particular interface is not
    // mentioned in the BindSocket() call, this may print the address as
    // 00000000.0000000000000000. This is because of the fact that an 
    // interface is picked only when the actual connection establishment 
    // occurs, in case of connection oriented socket.
    //
    fprintf ( stdout, "Bound to Local Address - " );
    PrintIpxAddress( psa->sa_netnum, psa->sa_nodenum );
	
    return;
}

//
// FillIpxAddress() fills a structure of type SOCKADDR_IPX with relevant
// address-family, network number, node number and socket (endpoint)
// parameters.
//
void _stdcall
FillIpxAddress ( 
    SOCKADDR_IPX *psa, 
    LPSTR lpsAddress,
    LPSTR lpsEndpoint
    )
{
  // Location of the separator
  LPSTR pszPoint;                 
  
    ZeroMemory ( psa, sizeof ( SOCKADDR_IPX ) );
	
    psa->sa_family = AF_IPX;
	
    //
    // Check if an address is specified
    //
    if ( NULL != lpsAddress )
    {
	//
	// Get the offset for node number/network number separator
	//
	pszPoint = strchr ( lpsAddress, '.' );

	if ( NULL == pszPoint )
	{
	    fprintf ( stderr, "IPX Address does not have a separator\n");
	    DoCleanup ( );
	    exit ( 1 );
	}

	//
	// covert the address in the  string format to binary format
	//
	AtoH ( (CHAR *) psa->sa_netnum, lpsAddress, 4 );
	AtoH ( (CHAR *) psa->sa_nodenum, pszPoint + 1, 6 );
	
    }
    
    if ( NULL != lpsEndpoint )
    {
	    psa->sa_socket = (USHORT) atoi ( lpsEndpoint );
    }
	
    return;
}

//
// SendData() is generic rotuine to send some data over a 
// connection-oriented IPX socket.
//
INT __stdcall 
SendData (
    SOCKET s, 
    CHAR *pchBuffer 
    )
{
  INT iRetVal;
	
    iRetVal = send ( s, 
		     pchBuffer,  
		     strlen ( pchBuffer ), 
		     0
		     );
	
    if ( SOCKET_ERROR == iRetVal )
    {
	PrintError ( "SendData", "send", WSAGetLastError ( ) );
    }
    
    //
    // return the total number of bytes sent
    //
    return iRetVal;
}

//
// ReceiveData() is generic rotuine to receive some data over a 
// connection-oriented IPX socket.
//
INT __stdcall
ReceiveData (
    SOCKET s, 
    CHAR *pchBuffer
    )
{
  INT iRetVal;
		
    iRetVal = recv ( s, 
		     pchBuffer, 
		     MAX_DATA_LEN, 
		     0
		     );
    
    if ( SOCKET_ERROR == iRetVal )
    {
	PrintError ( "ReceiveData", "recv", WSAGetLastError ( ) );
    }
    
    //
    // return the total number of bytes received
    //
    return iRetVal;
}

//
// SendDatagram() is generic rotuine to send a datagram to a
// specifid host.
//
INT __stdcall
SendDatagram (
    SOCKET s, 
    CHAR *pchBuffer, 
    SOCKADDR_IPX *psa
    )
{
  INT iRetVal;

    iRetVal = sendto ( s, 
		       pchBuffer,  
		       strlen ( pchBuffer ), 
		       0,
		       (SOCKADDR *) psa,
		       sizeof ( SOCKADDR_IPX )
		       );
 
    if ( SOCKET_ERROR == iRetVal )
    {
	    PrintError ( "SendDatagram", "sendto", WSAGetLastError ( ) );
    }
	
    /* return the total number of bytes sent in the datagram */
    return iRetVal;     
 }

//
// ReceiveDatagram() is generic rotuine to receive a datagram from a
// specifid host.
//
INT __stdcall
ReceiveDatagarm (
    SOCKET s, 
    CHAR *pchBuffer, 
    SOCKADDR_IPX *psa, 
    INT *pcb )
{
  INT iRetVal;
    
    iRetVal = recvfrom ( s, 
			 pchBuffer, 
			 MAX_DATA_LEN, 
			 0,
			 (SOCKADDR *) psa,
			 pcb
			 );
    
    if ( SOCKET_ERROR == iRetVal )
    {
	    PrintError ( "ReceiveDatagram", "recvfrom", WSAGetLastError ( ) );
    }
	
    //
    // return the total number of bytes received in the datagram
    //
    return iRetVal;
}
			 
//
// DoCleanup () will close the sockets which were opened successfully using 
// a call to socket (). Additionally, it will call WSACleanup (), if a call
// to WSAStartup () was made successfully.
//
void __stdcall
DoCleanup ( void )
{
    if ( INVALID_SOCKET != sock )
    {
	    closesocket ( sock );
    }

    if ( INVALID_SOCKET != newsock )
    {
	    closesocket ( sock );
    }

    if ( TRUE == fStarted )
    {
	    WSACleanup ( );
    }

    fprintf ( stdout, "DONE\n");

    return;
}

//
// CheckParameters() parses the command line parametrs.
//
void __stdcall
CheckParameters (
    INT argc, 
    CHAR **argv
    )
{
    INT i;
	
    for ( i = 1; i < argc; i++ ) 
    {
	if ( ( *argv[i] == '-') || ( *argv[i] == '/' ) ) 
	{
	    switch ( tolower ( *( argv[i]+1 ) ) ) 
	    {
	    
		//
		// Role of the application - server
		//
		case 's':                            
		    fServer = TRUE;
		    break;
	    
		//
		// Role of the application - client
		//
		case 'c':                            
		    fServer = FALSE;
		    break;
	    
		//
		// Store a pointer to the server endpoint
		//
		case 'e':
		    pszServerEndpoint = argv[++i];   
		    break;
	    
		//
		// Store a pointer to the server address
		//
		case 'n':
		    pszServerAddress = argv[++i];    
		    break;
						 
		//
		// Store a pointer to the local address
		//
		case 'l':
		    pszLocalAddress = argv[++i];     
		    break;

	    
		//
		// Set the flag to indicate enumeration of local adapters
		//
		case 'm':
		    fEnumerate = TRUE;               
		    break;

		//
		// Read and validate the protocol specified
		//
		case 'p':
		    chProtocol = tolower ( *argv[++i] );
		    if ( FALSE == CheckProtocol ( chProtocol ) )
		    {
			fprintf ( stderr, "UnKnown protcol specified\n\n");
			Usage ( argv[0] );
		    }
		    break;
	    //
	    // Help
	    //
	    case 'h':
	    case '?':
	    default:
		Usage ( argv[0] );
	    }
	}
	//
	// Help
	//
	else
	    Usage ( argv[0] );
    }    
    return;
}

//
// CheckProtocol() checks if a valid protocol is specified on the command
// line.
//
BOOL __stdcall
CheckProtocol(
    CHAR chProtocol
	)
{
    if ( 'd' != chProtocol && 's' != chProtocol && 'p' != chProtocol )
    {
	return FALSE;
    }

    return TRUE;
}

//
// Display the usage of command line parameters.
//
void __stdcall
Usage (
    CHAR *pszProgramName
    )
{
    fprintf ( stderr,"Usage:  %s\n", pszProgramName );
    fprintf ( stderr, 
	    "\t-s or -c (s - server, c - client, default - server)\n" );
    fprintf ( stderr, "\t-e <Endpoint>\n" );
    fprintf ( stderr, "\t-n <ServerIpxAddress>\n" );    
    fprintf ( stderr, "\t-l <LocalIpxAddress>\n" );    
    fprintf ( stderr,
	"\t-p <d or s or p> ( d - datagram, s - stream, p - sequenced packet)\n" );
    fprintf ( stderr, "\t-m To Enumerate Local Addresses\n" );
       
    exit ( 1 );
}

//
// PrintError () is a generic routine to print the Winsock or Win32 
// error codes for the errors occurred during relevant calls.
// If an error occurs, the error code is printed, cleanup routine is 
// called and the application exits.
//
void __stdcall 
PrintError (
    CHAR *lpszRoutine,
    CHAR *lpszCallName,
    DWORD dwError
    )
{
    fprintf ( stderr,
	      "The Call to %s() in the Routine %s() failed with Error %d\n",
	      lpszCallName, 
	      lpszRoutine, 
	      dwError
	      );

    DoCleanup ( );
    exit ( 1 );
}

//
// Print an IPX address.
// 
void __stdcall
PrintIpxAddress(
    CHAR *lpsNetnum,
    CHAR *lpsNodenum
    )
{
  INT i;
	
    for ( i = 0; i < 4; i++ )
    {
	fprintf ( stdout, "%02X", (UCHAR) lpsNetnum[i] );
    }
	
    fprintf ( stdout, "." );
    
    for ( i = 0; i < 6; i++ )
    {
	fprintf ( stdout, "%02X", (UCHAR) lpsNodenum[i] );
    }

    fprintf ( stdout, "\n" );

    return;
}

//
// AtoH () coverts the IPX address specified in the string(ascii) format to 
// the binary(hexadecimal) format.
//
void __stdcall
AtoH(
    CHAR *szDest, 
    CHAR *szSource,
    INT iCount
    )
{
    while (iCount--)
    {
	*szDest++ = ( BtoH ( *szSource++ ) << 4 ) + BtoH ( *szSource++ );
    }
    return;
}

//
// BtoH () returns the equivalent binary value for an individual
// character specified in the ascii format.
//
UCHAR __stdcall
BtoH(
    CHAR ch
    )
{

    if ( ch >= '0' && ch <= '9' )
    {
	    return ( ch - '0' );
    }

    if ( ch >= 'A' && ch <= 'F' )
    {
	    return ( ch - 'A' + 0xA );
    }

    if (ch >= 'a' && ch <= 'f' )
    {
	    return ( ch - 'a' + 0xA );
    }
	
    //
    // Illegal values in the IPX address will not be excepted
    //
    fprintf( stderr, 
    "Illegal value specified in  one of the IPX Addresses-BtoH Failed\n" );
	
    DoCleanup ( );

    exit ( 1 );
}
