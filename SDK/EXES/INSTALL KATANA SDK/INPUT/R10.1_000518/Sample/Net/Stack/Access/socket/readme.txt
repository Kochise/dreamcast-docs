
Socket SDK for Dreamcast (Beta Version) Release Notes
=====================================================

1.Overview
----------

    This is a release note for the Socket library SDK for Dreamcast developers 
    (Beta version).

    This SDK contains the socket library, socket library testing source programs,
    and socket library sample source programs.

1.1 Difference with the previous release (Alpha version)

    - The select() function is not supported. 
    - Bugs discovered in SEGA testing since release of the alpha version have 
      been fixed.


2.Using the sample programs
---------------------------

2.1 Preparation

    - Prepare a terminal which supports the 57600 bps communication speed
      (The socket testing program must be run via the terminal software 
      application.)

    - Connect to the serial port on the rear side of SET5.
    - Set up the terminal software application using the following parameters:
    Baud rate:57600
    Data:8 bit
    pality:none
    Stop:1 bit
    Flow control:none

2.2 Operation

    Connect to the above mentioned terminal software application. If its settings
    are correct, the test program will run to display a prompt waiting for input.
    
    Here, type "test".
    The socket test menu appears and testing starts.

    The terminal software application runs as follows:


*** START TEST PROGRAM ***

*** PPP CONNECTED ***


Debug TASK Ver. 1.00 start !!!
Copyright (C) 1998 ACCESS CO., LTD.
> test

*** socket test menu ***
1.accept() 2.bind() 3.connect() 4.getpeername() 5.getsockname() 6.getsockopt()
7.setsockopt() 8.listen() 9.recv() 10.recvfrom() 11.select() 12.send()
13.sendto() 14.shutdown() 15.socket() 17.sock_close()
18.sock_read() 19.sock_write() 20.gethostbyname() t.telnetd d.disconnect()
>

     From here on, testing of the socket library can be performed in an 
     interactive way.

2.3 "telnetd" sample program

     If "t." is selected, the "telentd" sample program will run using the socket 
     library.

     When "telnedt" is working, your IP address will appear on the console. Now, 
     connect to the IP address from the telent client.
     

     The commands that can be received are listed below:

     date ... Displays the current date of Dreamcast.
     quit ... Closes the connection. (Re-connection is possible.)
     exit ... Closes the connection. (Returns to the menu.)


2.Supported by the socket library
---------------------------------

     The select() function, though not supported in the previous version (Alpha 
     version), is not supported.
     * However, because the parameter "execeptfds" of the select() is not 
       supported, be sure to specify the NULL pointer.


3.About non-blocking of functions
---------------------------------

    This section explains about the non-blocking functions. Within the socket 
    library, there is a possibility that the following functions may be blocked:
    accept(), connect(), recv(), recvfrom(), sock_read()

    Before using these functions, by specifying non-blocking at setsockopt(), 
    these functions can operate in the non-blocking mode.

    Also, if timeout is specified at select(), the possibility of blocking may 
    arise. by setting 0 to uv_usec and tv_sec, it can be used in non-blocking 
    (polling) mode.

    In the non-blocking mode, if a function returns a value, the value will be 
    -1 and errno:
    errno:EINPROGRESS. (Refer to errno.h.)
    The timing for determining normal termination is when polling is called again
    and normal termination is returned.

    See the screen copy below on the program execution.

*** socket test menu ***
1.accept() 2.bind() 3.connect() 4.getpeername() 5.getsockname() 6.getsockopt()
7.setsockopt() 8.listen() 9.recv() 10.recvfrom() 11.select() 12.send()
13.sendto() 14.shutdown() 15.socket() 17.sock_close()
18.sock_read() 19.sock_write() 20.gethostbyname() t.telnetd d.disconnect()
> 15
domain(AF_INET:2) = 2
type(SOCK_STREAM:1, SOCK_DGRAM:2) = 1
protocol(0) = 0
ret = 1 ... Create socket

*** socket test menu ***
1.accept() 2.bind() 3.connect() 4.getpeername() 5.getsockname() 6.getsockopt()
7.setsockopt() 8.listen() 9.recv() 10.recvfrom() 11.select() 12.send()
13.sendto() 14.shutdown() 15.socket() 17.sock_close()
18.sock_read() 19.sock_write() 20.gethostbyname() t.telnetd d.disconnect()
> 7
socket = 1
level(SOL_SOCKET:-1) = -1
optname(SO_NOBLK:512, SO_OOBINLINE:256) = 512
optval(0, 1) = 1
optlen(2) = 2
ret = 0 ... Specify NON-BLOCKING

*** socket test menu ***
1.accept() 2.bind() 3.connect() 4.getpeername() 5.getsockname() 6.getsockopt()
7.setsockopt() 8.listen() 9.recv() 10.recvfrom() 11.select() 12.send()
13.sendto() 14.shutdown() 15.socket() 17.sock_close()
18.sock_read() 19.sock_write() 20.gethostbyname() t.telnetd d.disconnect()
> 3
socket = 1
family(AF_INET:2) = 2
port = 7
ip address(xxx.xxx.xxx.xxx) = 157.78.65.241
ret = -1
errno = 36 ... EINPROGRESS is returned.

*** socket test menu ***
1.accept() 2.bind() 3.connect() 4.getpeername() 5.getsockname() 6.getsockopt()
7.setsockopt() 8.listen() 9.recv() 10.recvfrom() 11.select() 12.send()
13.sendto() 14.shutdown() 15.socket() 17.sock_close()
18.sock_read() 19.sock_write() 20.gethostbyname() t.telnetd d.disconnect()
> 3
socket = 1
family(AF_INET:2) = 2
port = 7
ip address(xxx.xxx.xxx.xxx) = 157.78.65.241
ret = 0 ... Connection terminates normally.

*** socket test menu ***
1.accept() 2.bind() 3.connect() 4.getpeername() 5.getsockname() 6.getsockopt()
7.setsockopt() 8.listen() 9.recv() 10.recvfrom() 11.select() 12.send()
13.sendto() 14.shutdown() 15.socket() 17.sock_close()
18.sock_read() 19.sock_write() 20.gethostbyname() t.telnetd d.disconnect()
> 3
socket = 1
family(AF_INET:2) = 2
port = 7
ip address(xxx.xxx.xxx.xxx) = 157.78.65.241
ret = -1
errno = 56 ... While this is unnecessary, if it is called again even though 
it has terminated normally, error will result.

    This happens in the same way with the other functions. 


4.Other information
-------------------

    If <stdio.h> is included in the application
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#inlcude    <stdio.h>
....
#inluce     "errno.h"
    Include the header files in the above order.
    ~~~~~~~~~~~~~~~~~~~~~~~~~~~
    This is because in <stdio.h>
#define errno   _errno
    is defined and used in 
    "errno.h" as in 
#define _errno  errno
    If the inclusion order is wrong, the value of errno will not be displayed 
    correctly.


5.Final note
------------

    This is a beta version release.
    Even though basic operational check on the normal system/error system of the 
    stream and datagram has been done, the test is still not sufficient enough. 
    If there is any problem, please send in your report.


