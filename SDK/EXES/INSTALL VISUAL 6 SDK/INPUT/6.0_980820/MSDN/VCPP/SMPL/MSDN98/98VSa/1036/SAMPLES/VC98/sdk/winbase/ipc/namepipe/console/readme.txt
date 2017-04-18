Nmpipe.c is a simple, console named pipe sample demonstrating the "thread per
client" method of a named pipe client/server architecture. This sample
application demonstrates how to create and connect clients from a server
application, and how to wait for and connect to pipes from a client
application.

To compile the application for simultaneous reading and writing, uncomment the
"#define OVERPAPED_IO TRUE" statement in nmpipe.c. For one-way pipe operations,
uncomment the "#define OVERLAPPED_IO FALSE" statement.

The sample can be started either as a server or as a client. To start the
sample as the server, use the /s parameter. To start the sample as a client,
use /c. Following either /s or /c should be a string to write to the pipe.
Strings with spaces should be quoted. Following the string is an optional
parameter that specifies the full name of the pipe to create or connect to. If
none is given, a default pipe name is used.

For example, to start a server and client:

nmpipe /s "hello from the server " \\.\pipe\testpipe
nmpipe /c client \\.\pipe\testpipe

If OVERLAPPED_IO is defined as TRUE, this will cause the client and server to
write their respective strings to each other over the named pipe. If
OVERLAPPED_IO is defined as FALSE, then the client will only write and the
server will only read.

Note that Windows 95 cannot create named pipes, so the /s (run as server) flag
will cause errors on the CreateNamedPipe call under Windows 95. In addition,
Windows 95 does not support overlapped I/O on named pipes; if the app is
compiled with OVERLAPPED_IO defined as TRUE, errors will result from the
CreateFile calls, which use the FILE_FLAG_OVERLAPPED flag in this case. So be
sure to define OVERLAPPED_IO as FALSE before compiling on Windows 95.