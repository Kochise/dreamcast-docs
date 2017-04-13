MAPI Sample Message Store


The DOCFile.Ms sample demonstrates how to use a sample message store.

The message store is based on the file system. Each folder is a directory
and each message is a file. Additional files hold properties of folders
and of the message store itself.

Files
-----

File          Description

*.FLD         Folder.
*.MSG         Message.
FOLDER.PRP    Folder properties (any folder).
MSGSTORE.PRP  Message store properties (root folder only).
RECFLDR.STG   Receive folder settings (root folder only).
CONTENTS.TBL  Folder contents table cache.
OUTGOING.TBL  Outgoing queue table cache (root folder only).
*.TMP         Message in composition.
*.RRT         Read receipt.

Entry IDs
---------

A sample store entry ID contains the path of the item to which it refers,
relative to the store root directory. This enables a sample message store
to be copied usnig the file system with relative impunity (except to a
subdirectory of another sample message store).

The sample message store does not distinguish between short- and long-term
entry IDs.

Message on Storage
------------------

The IMAPIProp interface for all objects relies heavily upon the IMessage
interface implemented in IMSG.DLL, which in turn is based upon OLE 2.0
docfiles (the IStorage interface).

Interface Lifetime and Cross-referencing
----------------------------------------

The sample message store links child objects back to their parents, for
leak detection and invalidation when the parent object is closed before
the child. Opening a table on an object (such as a folder) and then
closing the folder invalidates the object, but not the table. This method
is slightly more sophisticated than simply incrementing the object reference
count when the table is opened.

Contents and Hierarchy Tables
-----------------------------

The IMAPITable interface for contents and hierarchy tables relies upon the
IMAPITableData interface in MAPIU.DLL; the size of a folder is therefore
limited to the amount of RAM available for the contents table. Initially,
a contents table is created by scanning the directory for .MSG files,
extracting some properties from each file, and writing a row for each
message to the table data object. To speed up subsequent open operations,
the table is then written out to a .TBL file, and the .TBL file is carefully
kept up to date by subsequent changes in the folder. Hierarchy tables are not
cached; the sample message store uses notification internally to keep them
up to date while they are open.

Supported Features
------------------

Basic operations. The sample message store supports reading, creating,
modifying, and deleting messages; browsing, creating, and deleting folders;
submitting outbound message to transports; and associating all types of
attachments with messages. Multivalued properties are supported for all
objects. The sample message store can be used as the default message store
for a MAPI client.

Copy operations. The sample message store supports moving and copying
messages and folders. These operations are delegated to MAPI support
functions unless an operation occurs entirely within one sample message store.

Event notification. The sample message store supports event notification on
tables (again, courtesy of IMAPITableData). Object notifications and new-mail
notifications are not supported.

Multithread safety. On 32-bit Windows platforms, all sample message store
interfaces protect themselves from concurrent access by multiple threads.

Cross-platform support. The sample message store source code generates
executable files for Windows 3.X, Windows 95, and Windows NT 3.5 and above
from a single set of source files.

Unsupported Features
--------------------

Named properties (GetNamesFromIDs and GetIDsFromNames methods of IMAPIProp).

Searches (SetSearchCriteria method of IMAPIFolder).

Categorization of contents tables.

Folder-associated information (MAPI_ASSOCIATED, DEL_ASSOCIATED flags).

IMAPIStatus interface.

ServiceEntry interface for configuration.

Certain other methods are unsupported, including IMAPIFolder::OpenProperty
and IMsgStore::CopyTo.

Configuration
-------------

The sample message store has two configurable properties: the path to the
store root directory and a password. Configuration is supported at service
provider logon only.

Known Problems
--------------

No error message appears if a user types the wrong password when logging
onto a sample message store.

Named properties in folder contents tables are not handled correctly. The
store should not allow them, because every message has a different property
name to ID mapping; but they are allowed.

PR_NULL is handled incorrectly in IMAPIProps::GetProps. It should create 
a placeholder in the returned property value array with PR_NULL for the
property tag. In fact, it places an error value (with MAPI_E_NOT_FOUND)
in the property value array and returns MAPI_W_ERRORS_RETURNED from
GetProps.

Installation
------------

To install the sample message store you have to

1. Merge the file smpms.inf with the mapisvc.inf located in your windows
   system directory. You can do it using mergeini utility that comes with
   MAPI SDK. The syntax is "mergeini -m smpms.inf".

2. Copy smpms(32).dll to the windows system directory.

3. Add the sample store to any MAPI profile using the Mail and Fax control
   panel applet.
