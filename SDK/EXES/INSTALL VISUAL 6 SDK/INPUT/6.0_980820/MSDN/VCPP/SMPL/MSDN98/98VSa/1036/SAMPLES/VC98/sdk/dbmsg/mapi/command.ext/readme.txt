Custom Command Extentions


SUMMARY
=======

The Command.Ext sample demonstrates how to implement custom command extensions
for the Microsoft Exchange Client. In particular, it demonstrates:

  - adding a menu command
  - adding a toolbar button
  - disabling/enabling the menu item and toolbar item depending what object
    is selected in the viewer
  - making MAPI calls from an extension
  - extending a command in the Main Viewer and the Search Viewer dialog
  - F1 response for context help on the menu item
  - Implementing custom Tooltip and Status Bar text

The custom command displays the number of subfolders, read messages, and
unread messages in a selected folder.

MORE INFORMATION
================

This sample requires Microsoft Windows NT 3.51 or Windows 95, the MAPI 1.0
PDK, Microsoft Visual C++ version 2.0 (or later), and the Win32 SDK.


To configure Microsoft Exchange to use the client extension, place the
following REG_SZ entry in the system registry in
HKEY_LOCAL_MACHINE\Software\Microsoft\Exchange\Client\Extensions:

    Sample Command Extension=4.0;c:\<path>\CMDEXT32.dll;1;01010000000000

You can leave out an explicit path to CMDEXT32.DLL if it resides in a
directory listed in the system PATH.

Exchange client extensions are designed using OLE's Component Object Model.
The client calls methods which are provided in the extension. In some
calls to the extension interface, a pointer to a callback interface
(IExchExtCallback) for the extension to call back into the Exchange client.
For more information read "Extending the Microsoft Exchange Client" in the
MAPI PDK documentation.

This sample implements three interface objects: IExchExt, IExchExtCommands,
and IExchExtUserEvents. To extend the command set of Exchange, it is
necessary to provide implementations for IExchExt and IExchExtCommands.
It is optional to provide implementation for IExchExtUserEvents. This sample
implements IExchExtUserEvents to enable or disable the custom command,
depending on what object the user is selecting in the Exchange main viewer.
The menu item is always enabled in the Search Folder Dialog.

The custom command is available in both the Main viewer and the Search
Folder Dialog. The IExchExtCommands provides an interface for the client to
display context help on the custom menu item and to display tooltip text and
status window text.  Select the custom menu item and press F1 to pop-up an
About dialog box.

This extension works in two different contexts, main viewer and search dialog.
For each context an extension supports, a complete set of interface objects
is created. In this sample, the MyExchExt, MyExchExtCommands and
MyExchExtUserEvents objects are created once for the main viewer context and
once for the search dialog. However, because there is only one
implementation for all contexts, there is a context flag data member which
indicates which context Exchange is calling from.

A context in many cases corresponds to a user interface. For example, the
search viewer is one context and the main viewer is another. QueryInterface
is called for each IID for each context. In this example, QueryInterface is
called each time for all IIDs in the main viewer context when
Exchange first starts. QueryInterface is called again each time for all
IIDs in the search viewer context. For each of the contexts, a unique pointer
to the MyExchExtCommands and MyExchExtUserEvents objects is returned to
Exchange in the QueryInterface call. Then when Exchange is calling
DoCommands from the search viewer, it is calling the one using the interface
pointer returned to it through QueryInterface in the search viewer context.
And when Exchange is calling DoCommands from the main viewer, it is calling
the one using the interface pointer returned to it through QueryInterface in
the main viewer context.
