WINDS Remote Transport


SUMMARY
=======

The Remote.Xp sample is a remote transport provider (XPWDSR) implemented
in C++. This transport demonstrates the following extended MAPI features:

 - Support for the REMOTE interface for slow-link connection to a remote host.
   This includes implementation of the IMAPIFolder methods needed to interact
   with a client remote viewer application.
 - Support for deferred delivery mechanism for scheduled message submission to
   a remote host at a user-settable upload time.
 - Support for forced immediate connection and submission (using the
   FlushQueues method implemented in the IMAPIStatus object) in response to
   Deliver Mail Now and Transfer Mail in the Microsoft Exchange Client.
 - How to implement server-based messaging.
 - Real-world working mail transport which sends messages to a Windows NT
   workstation or server running the Windows Developer Support (WINDS) Sample
   Server Messaging Host included with this and other MAPI samples.
 - Use of the Transport Neutral Encapsulation Format (TNEF) interface to
   encapsulate ALL the message properties.
 - How to implement the IMAPIStatus interface for client access to transport
   status.
 - Multithread safe.
 - Configuration dialogs.
 - Generation of delivery and non-delivery reports.
 - Support for the profile Wizard for interactive profile configuration.
 - Support for the WINDS address type.
 - Support for background download and FlushQueues spooler interaction for
   spooler-marshalled remote connections.
 - Single binary file for Windows NT and Windows 95.

MORE INFORMATION
================

This program requires:

    Windows NT 3.51 (or later) or Windows 95,
    The MAPI 1.0 SDK included in the Win32 SDK,
    Microsoft Visual C++ version 2.1 (or later.)

Optionally, the Win32 SDK tools with the MIDL compiler.

This sample uses RPCs over named pipes to establish connections with the
remote server. For convenience to customers without the full Win32 SDK, we
have provided the MIDL compiler-generated C and header files (WINDS.H,
WINDS_S.C, and WINDS_C.C) along with the IDL and ACF files. If you make changes
to the IDL or ACF, you'll NEED to recompile them using the MIDL compiler
available only in the Win32 SDK and Visual C++ 4.0 and later.

Building the Sample Code
------------------------

The sample remote transport provider has only been compiled and tested under
Windows NT 3.51 and Windows 95, there are no plans for a Windows 3.1x (16-bit)
release of this sample.

Users should update the project file dependencies as soon as the files are
copied to your machine. Use the PROJECTS.UPDATE DEPENDENCIES options in the
Visual C++ Developer Studio.

This sample was developed using Microsoft Visual C++ 2.x. Its associated
makefile is XPWDSR32.MAK. Traces can be enabled for Release builds by defining
ENABLE_DEBUG_OUTPUT in the preprocessor symbols define in the project settings
menu.

A command-line compiler-independent MAKE file has been provided for users of
command-line tools.

Configuration
-------------

Use the MERGEINI.EXE utility from the MAPI PDK to merge this transport's
message service INF file, XPWDSR.INF, with the MAPISVC.INF file:

    MERGEINI  {full-path}\XPWDSR.INF -m -q

for example:

    MERGEINI  C:\SAMPLES\MAPI\XPWDSR\XPWDSR.INF -m -q

You will then need to configure a profile that includes this transport. When
you create a new profile, the Profile Wizard will detect this transport and set
the initial properties through the wizard pages.

XPWDSR has two property sheets for interactive configuration which are
accessible through the service provider logon, through the ServiceEntry call
and through the IMAPIStatus::SettingsDialog method. The sample also defines
custom properties for the configuration options so they may be set and
retrieved programmatically.

User Account Configuration Page
-------------------------------

Server Name: This is the network UNC (Universal Naming Convention) name of
the machine where the user account is. The server machine MUST be running the
WINDS Sample Server Messaging Host application prior to the provider setup.

Mailbox Name: The mailbox name is the name of the account on the remote server.
To select a mailbox or change the current one, click on Browse and select a
name from the list that will appear. Once selected, you will be asked to enter
the password for the mailbox. For new mailboxes, the default password is
PASSWORD. If the list of mailboxes is empty or you don't find the one for you,
then a new account must be created on the server program. This field cannot be
edited manually by the user.

Full Name: This is the complete name of the owner of the mailbox selected. This
field is updated automatically when a new mailbox is selected. This information
cannot be edited manually.

Change Mailbox Password: Click on this button to change the password for this
mailbox. You will be asked to type the old password, a new password, and then
confirm the new password.

Using Local Network (LAN): This is the option to use if the machine is directly
hooked to on the network there is a connection to the server machine at all
times. If this option is selected, when running, the provider will install
notification links with the remote system allowing the provider to update
internal data dynamically as the data changes on the server, and to react to
changes or commands from the server.

Remote - With Local Address Book Directory: This setting instructs the provider
to adjust itself to use local data and to defer communication with the server
until the user changes the connection mode. This mode is useful if the server
or the clientmachine are not on a persistent connection link with each other.
If this option is selected the provider will not know of changes that occur on
the server to cached data.

Message Transport Configuration Page
------------------------------------

Automatic Remote Uploads At: The daily time when the transport will submit
all the messages it has deferred. At this time it will connect to the server
and submit all the messages in a batch. The time must be entered in the
24-hour format, i.e. 12:00 AM is 0:00. 10:30 PM is 22:30, etc.

When Connected: If this option is selected, after the messages have been
uploaded at the scheduled time, the transport will request to update the
message headers.

Note: Prior to installing this transport into a profile, the WINDS Sample
Server Messaging Host should be running in the remote (or local) computer.
See the readme file in the above sample for instructions on compiling,
installing, and using it.

Address Format
--------------

This transport supports the address type WINDS. When creating new one-off
entries in an address book (i.e. the Personal Address Book), this is the
value for the Address Type field. Email addresses for this transport look
like this:

    \\server-name\mailbox-name

The backslashes are literals, while the server-name and mailbox-name should
be replaced with the server and mailbox name you wish to send to.

Note: When typing one-off addresses in the Exchange client, you must double
the backslashes, like this:

    [WINDS:\\\\myserver\\mymailbox]

This is because the client treats the backslash as an escape character.

Remote Access
-------------

The main difference between this transport and a non-remote transport is the
ability to schedule mail transmission and to preview the header information
of messages residing in a user's remote mailbox. Outgoing messages aren't
transmitted at time of submission, but are queued by the spooler until the
scheduled delivery time occurs. This is known as deferred submission. As long
as the message is deferred, it stays in the user's local message store and the
spooler retains responsibility. The spooler maintains an internal queue of
deferred messages which it empties at the scheduled upload time, passing each
message in sequence to the transport for delivery.

Inbound messages stay in the user's mailbox on the remote server until
explicitly downloaded. This transport supports the Remote Viewer semantics,
where the user can request the transport to connect to the server and
retrieve a table of mail headers of messages in the user's remote mailbox. The
remote viewer lets the user mark those rows of the header table he wishes to
download. Rows are marked for move, delete, or copy operations according to
which operation the user wants to perform on the corresponding message.
Downloads are started explicitly, not scheduled, since the user has to
explicitly mark the rows of the table that are to be downloaded.

The download table is a contents table of a MAPI folder that is returned by
the IMAPIStatus object. This folder has no objects in it, but only exists to
provide the contents table. When the user marks messages for download in the
Remote Viewer, the corresponding row in the table has the PR_MSG_STATUS
property set to a bitmask indicating the requested operation. To obtain the
data for the header table, the transport makes an RPC to the server
requesting the name of a named pipe. The server creates the pipe and
returns the name. The transport then opens its end of the pipe and streams
the actual data over it. This data is used to populate the contents table.

Download Semantics
------------------

A user request to start downloading marked messages causes the transport's
IMAPIStatus::ValidateState method to be called with the
PROCESS_XP_HEADER_CACHE flag passed. At this point the download table is
walked and each marked entry is added to a list of messages to be
downloaded. When the list has been constructed, an RPC is made to the server
to obtain the name of a named pipe over which to stream the data.

The transport opens the pipe and requests the first message in the to-download
list. The transport uses a simple form of handshaking: control messages are
passed first to tell the server what the operation is, ACK the request, and get
the size of the following stream. Transmission errors can be reported in these
messages also. An error causes the message-in-transit to be dropped and the
next one started.

When a message is downloaded, its storage is backed by a temporary file which
is created on the fly to hold the incoming stream. When the message stream
arrives successfully on the client side, its to-download list node is moved
to a just-downloaded list. If the user logs off the session before the
just-dowloaded list is processed, the downloaded file is kept in a to-do
directory which will be processed in the next session logon.

Processing the just-downloaded list occurs in the same manner as for a
non-deferred message; each message is pumped through the spooler's
StartMessage loop. The spooler is notified that new mail has arrived by
setting the STATUS_INBOUND_FLUSH in the PR_STATUS_CODE bit in the status table
row. This causes the spooler to start requesting messages from the XP (by
calling StartMessage). We stream the message in from the temp file, decode the
TNEF stream into the passed MAPI message object, remove the non-transmittable
properties, set the transport computed properties, delete the temporary file,
and remove that message's node from the just-downloaded list. When the list is
empty, we signal the spooler to stop requesting incoming messages by clearing
the STATUS_INBOUND_FLUSH bit and passing back the untouched message object in
StartMessage.

Upload Semantics
----------------

Uploading messages works in a similar fashion except that we initiate the
process based on the time of day. The user configuration specifies a daily
upload time which is saved in the profile section. The XP can be in several
states with respect to the upload operation. When the upload time arrives, the
state changes from WAITING to PROCESSING_TIMER_EVENT.

When a message is submitted by the user, SubmitMessage is called and the
message is passed to us by the spooler. If our state is WAITING, we return
without doing anything. In the subsequent call to EndMessage, we check the
state and if we're WAITING, pass back END_DONT_RESEND. This signals the
spooler to queue this message until later requested.

A timer event is initialized on logon with the interval between the current
time and the upload time. When the timer expires, the spooler is notified to
start submitting the earlier deferred messages from its internal queue. We get
called again at SubmitMessage and are passed each message that's dequeued.
In SubmitMessage, we check our state, recognize that we're being called this
time to send the message, take responsibility (PR_RESPONSIBILITY), and go ahead
and deliver it. We also change our status to STATUS_OUTBOUND_FLUSH to signal
the spooler to keep calling our SubmitMessage method as long as it's queue is
not empty. In the subsequent EndMessage, we check our state, realize that a
message has just been dequeued and sent, decrement our counter and pass back
0. When the spooler has dequeued the last message, it callls TranportNotify,
passing NOTIFY_END_OUTBOUND_FLUSH and we change state back to WAITING.

After the transport has finished uploading the messages at the scheduled time,
we also request to get a new table of message headers on the server. This table
is downloaded to the local file and if the remote viewer is displayed, the
table of contents is refreshed.

Aborting Message Delivery
-------------------------

Once deferred, a message can be aborted any time before the actual delivery.
This happens if the user opens or deletes the message before it's sent. The
XP gets called at TransportNotify with NOTIFY_ABORT_DEFERRED. The spooler
will remove this message from its internal queue and we won't be called at
SubmitMessage for it.

Debug Traces and Asserts
------------------------

This sample uses several output debug string functions in the Win32
environment to avoid attaching the DLL to any debugger. By default, the trace
messages are output to a debug terminal attached to COM1 with settings at
9600, N, 8, 1. The debug messages can also be written to a log file whose
default location is C:\MAPILOG.TXT. The file TRACES.CPP defines some macros
that can be easily modified for different communications settings, output port,
and log file name. It also implements a macro (ASSERT) and function that test
the validity of a given statement. If the assertion fails, the user/developer
has the opportunity to break into the debugger at the exact point where the
assertion occurred.

The debug routines are found in the TRACES.CPP and TRACES.H files.

To enable the TRACExx functions in the TRACES.CPP files, define the
ENABLE_DEBUG_OUTPUT macro during compilation. These functions work in DEBUG or
RELEASE builds. You can only enable/disable traces at compile time through
ENABLE_DEBUG_OUTPUT. There is no run time switch to enable or disable the
traces.

TRACES.CPP implements an ASSERT macro which test a evaluates an expression
expecting a TRUE result, i.e. ASSERT (expression) will interrupt execution if the expression is NOT TRUE (non-zero).

The ASSERT macro informs the line and source code file name where the assertion
failed and writes the result to a debug trace. The assert information is also
written to the log file.

Also the this file implements a variation of assert: ASSERTMSG (expression,
user-message) which behaves identical to ASSERT except that is the assertion
fails, the message string is printed along with the assertion line and file
information.

By default, if an assertion fails, a dialog will come up and interrupt
execution until a selection is made to break into the debugger or ignore the
assertion.
