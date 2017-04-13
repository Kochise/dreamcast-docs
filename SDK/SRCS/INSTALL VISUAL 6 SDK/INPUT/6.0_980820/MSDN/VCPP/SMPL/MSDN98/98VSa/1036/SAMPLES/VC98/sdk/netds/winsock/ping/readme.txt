
This sample illustrates the use of SOCK_RAW in Winsock 2.0 on Windows NT in 
order to write an ICMP_ECHO utility (commonly seen in the 'ping' program  on 
various systems).


Usage:
	ping <hostname/IP address> <packet size>

	Sends ICMP echo requests to host specified by the first argument. If a
	packet size is specified, a buffer of that size is sent. The default size
	is 32 bytes.
