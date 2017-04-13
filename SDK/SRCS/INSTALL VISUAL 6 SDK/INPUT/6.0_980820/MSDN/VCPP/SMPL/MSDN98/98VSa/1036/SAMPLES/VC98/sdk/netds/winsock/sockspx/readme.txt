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
