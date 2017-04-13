Sample Property Sheet Extension


SUMMARY
=======

The PropSh.Ext sample demonstrates how to implement custom property sheet
extensions for the Microsoft Exchange Client. In particular, it demonstrates
adding a custom property page that displays summary sheet information for
Microsoft Office documents in a message store.  It adds the custom page when
viewing properties with a message of class IPM.Document.


MORE INFORMATION
================

This sample requires Microsoft Windows NT 3.51 or Windows 95, the MAPI 1.0
(Extended MAPI) PDK (Build 410 or above), Microsoft Visual C++ version 2.0
(or later), and the Win32 SDK for Windows NT and Windows 95.

To configure Exchange to use the client extension, place the following
REG_SZ entry in the system registry in:
HKEY_LOCAL_MACHINE\Software\Microsoft\Exchange\Client\Extensions:

    Sample Property Extension=4.0;c:\<path>\EPRSHT32.DLL;1;00000000000100

You can leave out an explicit path to EPRSHT32.DLL if it resides in a
directory listed in the system's PATH.

Exchange client extensions are designed using OLE's Component Object Model.
The client calls methods which are provided in the extension. In some calls
to the extension interface, a pointer to a callback interface
(IExchExtCallback) for the extension to call back into the Exchange client.
For more information read "Extending the Microsoft Exchange Client" in the
MAPI PDK documentation.

This sample implements two interface objects, IExchExt and
IExchExtPropertySheets. The extension responds to IExchExtPropertySheets
methods called by the Exchange client to append a property page if the selected
message object is a IPM.Document class message.

MAPI stores Microsoft Office documents as a set of properties with the
summary sheet information is retained as named properties. The sample
extracts the property IDs from the names the first time it displays the
properties for an Office document with the GetIDsFromNames.  After that, it
stores and reuses those ids until the Exchange client is closed.

The summary info custom property page displays information in read-only edit
controls. The information is read from pointers to elements of a SPropValue
array filled by the GetProps function. If a particular property is not found,
the string "No <property>" is diplayed in the corresponding field. The
field will be blank if the property is found but is an empty string. Each time
the summary info page is activated without closing the property sheet dialog,
the controls are re-initialized with the same data. The SPropValue array is
freed when the property sheet dialog is closed.

The Help button is available for the summary info page and will display About
information in the sample extension in a message box.

To demonstrate the functionality of the extension, drag a Microsoft Office
document that has summary sheet information into a folder in the Microsoft
Exchange client. Then select the document and press Alt+ENTER or choose
Properties... from the File menu in Exchange.
