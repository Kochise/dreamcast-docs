Sample Server Messaging Host


The Remote.Srv sample serves as the server based message repository
for MAPI 1.0 transports that handle the Windows Developer Supprt (WINDS)
address type. This program simulates a foreign messaging system.
WINDS also acts as the server host for address book with a global address list.
The global address list is the list of recipients in the WINDS host. Since
WINDS supports gateways, foreign message recipients appear in the user
directories of the gateways currently installed.

Requirements
------------

To build this program you must have:

    Windows NT 3.5 (or later),
    Microsoft Visual C++ version 2.0 (or later) or the Win32 SDK tools.

This sample uses RPC over named pipes to establish connections with remote
clients.

Building the Sample Code
------------------------

This sample runs under Windows NT 3.5x on Intel x86, MIPS R4xxx and Digital
AXP platforms.

If you are using Microsoft Visual C++, update the project file dependencies
as soon as the files are copied to your machine. Use the PROJECTS.UPDATE
DEPENDENCIES options in the Developer Studio.

This sample was developed using Microsoft Visual C++ 2.x. The associated
makefile is WINDSSRV.MAK for the service component and WINDSADM for the
remote administrator component. Traces can be enabled for Release builds by
defining ENABLE_DEBUG_OUTPUT in the preprocessor symbols define in the
project settings menu.

A command-line compiler-independent makefile has been provided for users
of command-line tools. The command line tool will, by default build a
DEBUG version of both components. If NODEBUG is defined, a RELEASE version
of the both components will be built.

Usage
-----

There are two pieces for the WINDS server sample. The WINDS service component
and the WINDS administrator component.

WINDS Service Installation
--------------------------

The WINDS service performs the actual processing. It can be run on a
Windows NT machine on any platform. To install the service, simply run the
built executable from the command line with the INSTALL option:

    C:\SAMPLES\MAPI\WINDS> WINDSSRV INSTALL

This will add the service to the registry and start the service immediately.
Note that you must be in the directory where the service executable is.

To stop and remove the server from the system use the REMOVE option:

    C:\SAMPLES\MAPI\WINDS> WINDSSRV  REMOVE

If the service is run without parameters, a window will come up for
interactive configuration (install and removal).

The WINDS service supports interaction with the Services Applet in the
control panel so it can be started, stopped, paused, resumed, and queried
using the standard UI.

Once the WINDS Service is installed, it can run unattended, even when no one
is logged into the Windows NT machine.

The service does not expose any UI for normal interaction and administration.
All of this is done through the WINDS Administrator program (explained below),
either by running it on the same machine where the WINDS service is running
or across the network.

WINDS Administrator
-------------------

Some of the menu items and property pages maybe grayed out because they have
not been implemented yet.

The WINDS administrator is a program that can be run on the same machine
where the WINDS service is running or across the network.

The administrator can be run on Windows NT (workstation or server) or from
Windows 95. The executable is single binary for all Intel Win32 platfoms,
so there is no need to rebuild it for Windows 95 once built for Windows NT
or vice versa.

The administrator is a graphical interface to the data stored in the WINDS
Server. Through this program, you can create and control the list of user
mailboxes, distribution lists, and public folders. You can also manage the
gateways and do other administrative tasks on the WINDS server, remotely,
through a graphical interface.

Debug Traces and Asserts
------------------------

This sample uses several output debug string functions in the Win32
environment to avoid attaching the DLL to any debugger. By default, the trace
messages are output to a debug terminal attached to COM1 with settings at
9600, N, 8, 1. The debug messages can also be written to a log file whose
default location is C:\MAPILOG.TXT. The file TRACES.CPP defines some macros
that can be easily modified for different communications settings, output
port, and log file name. It also implements a macro (ASSERT) and function that
test the validity of a given statement. If the assertion fails, the
user/developer has the opportunity to break into the debugger at the exact
point where the assertion occurred.

The debug routines are found in the TRACES.CPP and TRACES.H files.

To enable the TRACExx functions in the TRACES.CPP files, define the
ENABLE_DEBUG_OUTPUT macro during compilation. These functions work in DEBUG
or RELEASE builds. You can only enable/disable traces at compile time
through ENABLE_DEBUG_OUTPUT. There is no run time switch to enable or
disable the traces.

TRACES.CPP implements an ASSERT macro which evaluates an expression
expecting a TRUE result, i.e. ASSERT (expression) will interrupt execution
if the expression is NOT TRUE (non-zero).

The ASSERT macro displays the line and source code file name where the
assertion failed and writes the result to a debug trace. The assert
information is also written to the log file.

By default, if an assertion fails, a dialog will come up and interrupt
execution until a selection is made to break into the debugger or ignore the
assertion.
