Sample Transport


The peer.xp sample is a transport service provider (SMPXP.DLL).

Peer-to-Peer
------------

The sample peer-to-peer transport transmits messages as files and uses
network file paths as its e-mail addresses. Each user has an inbound message
directory and an outbound message directory; the user e-mail address is the
network path to the inbound directory. The transport creates an outbound
message in each recipient's inbound directory (obtained from the recipient's
address).

Not Peer-to-Peer
----------------

If peer-to-peer transmission is disabled (this is a configuration option), the
transport simply leaves outbound messages in the outbound directory and
collects inbound messages from the inbound directory. It does not attempt
delivery. This mode can be used as the first of two stages, where the second
stage moves messages to and from the network.

Addressing
----------

In peer mode, the network path of the user's inbound directory is the e-mail
address. Network paths are normally Universal Naming Convention (UNC) paths,
but an MS-DOS drive and directory path can also be used.

Message in TNEF
---------------

A small set of message properties, including recipients, subject, and message
text, are encoded as text for transmission. Other message properties are
encapsulated in a binary file in the Transport Neutral Encapsulation Format
(TNEF), using functions supplied in TNEF.DLL. This division approximates
the division of properties that real transports must often make, where those
properties understood by non-MAPI clients must be encoded in a transport-
specific format and the remainder can be left to the TNEF.

Interface Lifetime and Cross-Referencing
----------------------------------------

Interfaces created by the transport in response to service provider interface
(SPI) calls, including status interfaces, are hooked to the transport logon
object and invalidated when MAPI logs off the transport. The provider INIT
object is an exception, as you might expect.

Address Type and UID
--------------------

The transport handles a single e-mail address type, which is configurable.
It does not handle any UIDs, that is, it does not call SetProviderUID.

Per-recipient and per-message Option Support
--------------------------------------------

The transport supports deferred delivery of messages on a per-recipient
basis, as well as on a per-message basis.

Supported Features
------------------

Basic features. The sample transport supports sending, receiving, and polling
for new messages.

Configuration. Interactive and programmatic configuration of 14 parameters
is supported.

Status interface. The sample transport supports all methods of the IMAPIStatus
interface, except property setting.

Multithread safety. MAPI carefully limits the exposure of transports to access
by multiple threads of execution on Win32 platforms. The sample transport
protects itself against concurrency problems in the remaining cases where they
might arise (in the status interface, for instance).

Cross-platform support. The sample transport generates executable files for
Windows 3.X, Windows 95, and Windows NT 3.5 and later from a single set of
source files.

Event logging. The sample transport supports event logging to a text file.
The file is automatically limited to a specified size. All transport sessions
use the same file.

Unsupported Features
--------------------

Asynchronous detection of incoming messages. The transport design does not
lend itself to asynchronous detection because the file system does not notify
the transport when new messages arrive.

Address Format
--------------

This transport supports a single address type whose name is configurable.
MSPEER is commonly chosen; this is the type supported by the sample address
book. When creating new one-off entries in an address book (i.e. the Personal
Address Book), this is the value for the Address Type field. Email addresses
for this transport look like DOS file paths. They can be either UNC paths,
or ordinary fully qualified paths:

    \\server-name\share-name\directory-name\...drive-letter:directory-name\...

Note: When typing one-off addresses in the Exchange client, you must double the
backslashes, like this:

    [MSPEER:\\\\server-name\\share-name\\directory\\...]

This is because the client treats the backslash as an escape character.

Configuration
-------------

The sample transport has a three-page property sheet interface for interactive
configuration, which is accessible through service provider logon, through
the ServiceEntry call, and through the IMAPIStatus::SettingsDialog method.
The configurable parameters appear following. The sample transport also
defines a property tag for each parameter so that parameters may be set
programmatically through ServiceEntry calls; see the SMPXP.H header file.

General Page
------------

Log Events. If this check box is selected, the transport logs events to the
log file specified on the Logging page. Otherwise, logging is disabled.

Peer to Peer Enabled. If this check box is selected, the transport attempts
to deliver outbound messages to the directory specified by the e-mail address.
Otherwise, outbound messages are simply placed in the user's own outbound
directory.

Logon UI Always. If this check box is selected, the transport always brings
up this dialog box the first time you log on. If Save Dialog Settings is also
selected, the dialog box comes up filled with the previously entered
information. If Logon UI Always is not selected, no dialog box appears at
logon, and the transport uses saved settings instead.

Save Dialog Settings. If checked, the transport saves the contents of the
dialog box in your MAPI profile. Otherwise, the dialog box contents are used
until you log off from MAPI and then discarded.

WGAP Filename. This edit control contains a name which could be used by an
application to designate resources owned by this user of the peer-to-peer
transport. No known application uses it.

WGAP Directory. This edit control contains the path to a directory which
could be used by an application to store files owned by this user of the
peer-to-peer transport. No known application uses it.

Peer to Peer Page
-----------------

Display Name. This edit control contains the user's full name. This item
appears in the From field of any messages sent using the peer-to-peer transport.

E-mail Type. This edit control contains the type component of the user's e-mail
address. Users who intend to exchange messages with the peer-to-peer transport
should agree on a common value for this item. MSPEER, which is supported by the
the sample address book, is a common choice.

E-mail Address. This edit control contains a network path, preferably a UNC
path, to the user's inbound directory. This item is the return address in
messages sent from this session.

Inbound Msg Dir. This edit control contains a path, preferably a local path,
to the user's inbound directory. This item does not appear in messages; the
transport simply uses it as a location to poll for inbound messages.

Outbound Msg Dir. This edit control contains a path, preferably a local path,
to the user's outbound directory.

Logging Page
------------

Logfile Name. This edit control contains a path to the text file the transport
uses for event logging. If Log Events is checked on the General page, the
transport writes a line of text to this file for each event.

Log High Water Mark. This edit control contains the maximum size of the log
file, in kilobytes. If the log file grows beyond this size, it is truncated.

Log Low Water Mark. This edit control contains the size in kilobytes to which
the log file is truncated when it grows beyond the high-water mark.

Known Problems
--------------

Self-relative UNC paths on Windows for Workgroups. If the user's inbound
directory is shared from the workstation using Windows for Workgroups and the
e-mail address is a UNC path, sending messages to oneself from this
workstation might not work.

Installation
------------

To install the sample transport you have to

1. Merge the file smpxp.inf with the mapisvc.inf located in your windows
   system directory. You can do this using the mergeini utility that comes
   with the MAPI SDK. The syntax is "mergeini -m smpxp.inf".

2. Copy smpxp(32).dll to the windows system directory.

3. Add the sample transport to any MAPI profile using the Mail and Fax
   control panel applet.
