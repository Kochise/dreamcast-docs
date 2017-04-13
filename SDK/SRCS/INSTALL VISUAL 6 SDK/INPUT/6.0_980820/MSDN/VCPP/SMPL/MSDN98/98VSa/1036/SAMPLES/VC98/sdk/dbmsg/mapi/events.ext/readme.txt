Custom Message Event Extension


SUMMARY
=======

The Events.Ext sample demonstrates how to implement a custom message event
extension for the Microsoft Exchange Client. In particular, it demonstrates:

  - reading message text before displayed in the read note form
  - reading message text as it is submitted to MAPI

This sample uses a very basic form of signing a message. A checksum on the
message as it is written is stored as a custom property. Upon reading the
message, the extension verifies the checksum and displays one of two
possible outcomes: the message has been verified with correct contents, or
the message text has been altered.

MORE INFORMATION
================

This sample requires Microsoft Windows NT 3.51 or Windows 95, the MAPI 1.0
(Extended MAPI) PDK (Build 410 or above),  Microsoft Visual C++ version 2.0
(or later), and the Win32 SDK for Windows NT and Windows 95.

Configuration
-------------

To configure Exchange to use the client extension, place the following
REG_SZ entry in the system registry in:
HKEY_LOCAL_MACHINE\Software\Microsoft\Exchange\Client\Extensions

    Samp Ext=4.0;C:\MAPISAMP\EVENTEXT\EVEXT32.DLL;1;00000111111100

You can leave out an explicit path to EVEXT32.DLL if it resides in a
directory listed in the system PATH.

Exchange client extensions are designed using OLE's Component Object Model.
The client calls methods which are provided in the extension. In some calls
to the extension interface, a pointer to a callback interface
(IExchExtCallback) is given for the extension to call back into the
Exchange client. For more information read "Extending the Microsoft Exchange
Client" in the MAPI PDK documentation.

This sample extension includes the implementation of a property page
displayed in the Tools Option property sheet to either enable or disable
signatures. The sample will check a flag before calculating or verifying
checksums.

GetObject is used during the OnWriteComplete and OnRead methods to obtain
the message body. The checksum is calculated and written as a custom
property of a message when the Send button is clicked. The checksum is
recalculated and verified when a message is read. For large messages, the
checksum may take a few seconds depending on the size of the message and the
speed of the machine.

During the case that a message is found to have "altered" text according
to the checksum, the extension gives the user a choice whether to continue
to read the message or not. If not, an error return value is set in the
OnRead method to be used by the OnReadComplete method. Returning
MAPI_E_CALL_FAILED from OnReadComplete causes Exchange to call OnReadComplete
again with ulFlags parameter set to an error. The parameter is ignored by
this sample and returning MAPI_E_CALL_FAILED causes Exchange to not display
the read note form.

This sample also supports the "Reply to Sender" context and signs the
reply when enabled. Replying to a non-signed message while the signatures
are enabled adds a signature to the entire message, counting original
message and reply. Replying to a signed message while the signature is
disabled removes the original signature.

The logic for signing is only calculating the checksum on the PR_BODY
message property. The extension does not take "quirks" of certain providers
into its logic and the extension will interpret that a message was "altered"
when in fact it has not. Two examples are the MSPERR Transport and the MSMail
provider. With the MSPeer transport, it will add the text
"*** End of message ***" at the end of the message. The checksum does not
include this upon sending. The MSMail provider strips whitespace at the end
of a line just before the carriage return characters (CRLF). When sending,
the checksum calculation includes the whitespace. So the checksum verification
upon reading will not match with the stored checksum property. If you write a
message without placing any spaces just before a carriage return, or just
allow the richedit control wordwrap, the checksums will be equal.
