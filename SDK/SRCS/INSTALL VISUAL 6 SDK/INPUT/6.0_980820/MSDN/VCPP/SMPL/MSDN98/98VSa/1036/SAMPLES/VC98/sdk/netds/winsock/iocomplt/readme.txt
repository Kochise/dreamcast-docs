Overlapped I/O Using I/O Completion Ports


The SOCKETS sample contains a simple Windows NT server that uses Windows 
sockets. It demonstrates overlapped I/O using I/O completion ports to 
receive ReadFile completion notification. An I/O completion port is the most 
efficient form of overlapped I/O. I/O completion ports were introduced in 
Windows NT 3.5.

CreateIoCompletionPort, as used in the server half of this sample, is only
supported on Windows NT.
