POP3 Sample


The POP3 sample includes a server that sets up a listening socket on the 
POP3 port, then loops, accepting incoming connections from clients. Whenever 
the server gets a connection, it sends a greeting message and starts a read 
operation on the newly connected socket.
